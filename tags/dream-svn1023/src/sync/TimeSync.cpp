/******************************************************************************\
 * Technische Universitaet Darmstadt, Institut fuer Nachrichtentechnik
 * Copyright (c) 2001-2014
 *
 * Author(s):
 *  Volker Fischer
 *
 * Description:
 *  Time synchronization
 * This module can have different amounts of input data. If two
 * possible FFT-window positions are found, the next time no new block is
 * requested.
 *
 * Robustness-mode detection
 *
 ******************************************************************************
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
\******************************************************************************/

#include "TimeSync.h"
#include "TimeSyncFilter.h"
#include <limits>

/* Implementation *************************************************************/

int CTimeSync::HilbertFilter()
{
    /* ---------------------------------------------------------------------
       Data must be band-pass-filtered before applying the algorithms,
       because we do not know which mode is active when we synchronize
       the timing and we must assume the worst-case, therefore use only
       from DC to 4.5 kHz. If the macro "USE_10_KHZ_HILBFILT" is defined,
       a bandwith of approx. 10 kHz is used. In this case, we have better
       performance with the most probable 10 kHz mode but may have worse
       performance with the 4.5 or 5 kHz modes (for the acquisition) */

    /* The FIR filter intermediate buffer must be adjusted to the new
       input block size since the size can be vary with time */
    CComplexVector cvecInpTmp(iInputBlockSize);

    /* Copy CVector data in CMatlibVector */
    for (int i = 0; i < iInputBlockSize; i++)
        cvecInpTmp[i] = (*pvecInputData)[i];

    /* Complex Hilbert filter. We use the copy constructor for storing
       the result since the sizes of the output vector varies with time.
       We decimate the signal with this function, too, because we only
       analyze a spectrum bandwith of approx. 5 [10] kHz */
    CComplexVector cvecOutTmp(FirFiltDec(cvecB, cvecInpTmp, cvecZ, iGrdcrrDecFact));

    /* Get size of new output vector */
    int iDecInpuSize = cvecOutTmp.GetSize();

    /* Copy data from Matlib vector in regular vector for storing in
       shift register
       TODO: Make vector types compatible (or maybe only use matlib vectors
       everywhere) */
    CVector<_COMPLEX> cvecOutTmpInterm(iDecInpuSize);
    for (int i = 0; i < iDecInpuSize; i++)
    {
        cvecOutTmpInterm[i] = cvecOutTmp[i];
//          float value[2] = {cvecOutTmp[i].real()/8192, cvecOutTmp[i].imag()/8192};
//          write(1000, &value, sizeof(value));
    }

    /* Write new block of data at the end of shift register */
    HistoryBufCorr.AddEnd(cvecOutTmpInterm, iDecInpuSize);

    return iDecInpuSize;
}

_REAL CTimeSync::calcFreqOffsetTrack()
{

    /* ---------------------------------------------------------------------
       Frequency offset tracking estimation method based on guard-interval
       correlation.
       Problem: The tracking frequency range is "GRDCRR_DEC_FACT"-times
       smaller than the one in the frequency domain tracking algorithm.
       Therefore, the acquisition unit must work more precisely
       (see FreqSyncAcq.h) */

    /* Guard-interval correlation at ML estimated timing position */
    /* Calculate start points for correlation. Consider delay from
       Hilbert-filter */
    const int iHalHilFilDelDec = iNumTapsHilbFilt / 2 / iGrdcrrDecFact;
    const int iCorrPosFirst = iDecSymBS + iHalHilFilDelDec;
    const int iCorrPosSec = iDecSymBS + iHalHilFilDelDec + iLenUsefPart[eSelectedMode];

    /* Actual correlation over entire guard-interval */
    CComplex cGuardCorrFreqTrack = 0.0;
    for (int i = 0; i < iLenGuardInt[eSelectedMode]; i++)
    {
        /* Use start point from ML timing estimation. The input stream is
           automatically adjusted to have this point at "iDecSymBS" */
        cGuardCorrFreqTrack += HistoryBufCorr[i + iCorrPosFirst] * Conj(HistoryBufCorr[i + iCorrPosSec]);
    }

    /* Average vector, real and imaginary part separately */
    IIR1(cFreqOffAv, cGuardCorrFreqTrack, rLamFreqOff);

    /* Calculate argument */
    const CReal rFreqOffsetEst = Angle(cFreqOffAv);

    /* Correct measurement average for actually applied frequency
       correction */
    cFreqOffAv *= CComplex(Cos(-rFreqOffsetEst), Sin(-rFreqOffsetEst));

    /* normalize estimate */
    return rFreqOffsetEst * rNormConstFOE;
}

void CTimeSync::guardIntervalCorrelation(vector<int> &iNewStartIndexField, int iDecInpuSize)
{

    /* Guard-interval correlation ----------------------------------- */

    /* Init start-index count */
    int iNewStIndCount = 0;

    /* We use the block in the middle of the buffer for observation */
    for (int i = iDecSymBS + iDecSymBS - iDecInpuSize; i < iDecSymBS + iDecSymBS; i++)
    {
        /* Only every "iStepSizeGuardCorr"'th value is calculated for
           efficiency reasons */
        if (i == iTimeSyncPos)
        {
            /* Do the following guard interval correlation for all
               possible robustness modes (this is needed for robustness
               mode detection) */
            for (int j = rm_low; j <= rm_high; j++)
            {
                /* Guard-interval correlation ----------------------- */
                /* Speed optimized calculation of the guard-interval
                   correlation. We devide the total block, which has to
                   be computed, in parts of length "iStepSizeGuardCorr".
                   The results of these blocks are stored in a vector.
                   Now, only one new part has to be calculated and one
                   old one has to be subtracted from the global result.
                   Special care has to be taken since "iGuardSize" must
                   not be a multiple of "iStepSizeGuardCorr". Therefore
                   the "if"-condition */
                /* First subtract correlation values shifted out */
                int pos = iPosInIntermCResBuf[j];
                cGuardCorr[j] -= veccIntermCorrRes[j][pos];
                rGuardPow[j] -=  vecrIntermPowRes[j][pos];

                /* Calculate new block and add in memory */
                for (int k = iLengthOverlap[j]; k < iLenGuardInt[j]; k++)
                {
                    /* Actual correlation */
                    int iCurPos = iTimeSyncPos + k;
                    int pos = iCurPos + iLenUsefPart[j];
                    if(pos>=HistoryBufCorr.Size())
                        break;
                    _COMPLEX hbc = HistoryBufCorr[iCurPos];
                    _COMPLEX hbc2 = HistoryBufCorr[pos];
                    cGuardCorrBlock[j] += hbc * Conj(hbc2);

                    /* Energy calculation for ML solution */
                    rGuardPowBlock[j] += SqMag(hbc) + SqMag(hbc2);

                    /* If one complete block is ready -> store it. We
                       need to add "1" to the k, because otherwise
                       "iLengthOverlap" would satisfy the
                       "if"-condition */
                    if (((k + 1) % iStepSizeGuardCorr) == 0)
                    {
                        int pii = iPosInIntermCResBuf[j];
                        veccIntermCorrRes[j][pii] = cGuardCorrBlock[j];

                        vecrIntermPowRes[j][pii] = rGuardPowBlock[j];

                        /* Add the new block to the global result */
                        cGuardCorr[j] += cGuardCorrBlock[j];
                        rGuardPow[j] += rGuardPowBlock[j];

                        /* Reset block result */
                        cGuardCorrBlock[j] = (CReal) 0.0;
                        rGuardPowBlock[j] = (CReal) 0.0;

                        /* Increase position pointer and test if wrap */
                        iPosInIntermCResBuf[j]++;
                        if (iPosInIntermCResBuf[j] == iLengthIntermCRes[j])
                            iPosInIntermCResBuf[j] = 0;
                    }
                }

                /* Save correlation results in shift register */
                for (int k = 0; k < iRMCorrBufSize - 1; k++)
                    vecrRMCorrBuffer[j][k] = vecrRMCorrBuffer[j][k + 1];

                /* ML solution */
                vecrRMCorrBuffer[j][iRMCorrBufSize - 1] =
                    abs(cGuardCorr[j] + cGuardCorrBlock[j]) -
                    (rGuardPow[j] + rGuardPowBlock[j]) / 2;
            }

            /* Energy of guard interval calculation and detection of
               peak is only needed if timing aquisition is true */
            if (bTimingAcqu)
            {
                /* Start timing detection not until initialization phase
                   is finished */
                if (iTiSyncInitCnt > 1)
                {
                    /* Decrease counter */
                    iTiSyncInitCnt--;
                }
                else
                {
                    /* Average the correlation results */
                    IIR1(vecCorrAvBuf[iCorrAvInd],
                         vecrRMCorrBuffer[eSelectedMode][iRMCorrBufSize - 1],
                         1 - rLambdaCoAv);


                    /* Energy of guard-interval correlation calculation
                       (this is simply a moving average operation) */
                    vecrGuardEnMovAv.Add(vecCorrAvBuf[iCorrAvInd]);


                    /* Taking care of correlation average buffer ---- */
                    /* We use a "cyclic buffer" structure. This index
                       defines the position in the buffer */
                    iCorrAvInd++;
                    if (iCorrAvInd == iMaxDetBufSize)
                    {
                        /* Adaptation of the lambda parameter for
                           guard-interval correlation averaging IIR
                           filter. With this adaptation we achieve
                           better averaging results. A lower bound is
                           defined for this parameter */
                        if (rLambdaCoAv <= 0.1)
                            rLambdaCoAv = 0.1;
                        else
                            rLambdaCoAv /= 2;

                        iCorrAvInd = 0;
                    }


                    /* Detection buffer ----------------------------- */
                    /* Update buffer for storing the moving average
                       results */
                    pMaxDetBuffer.AddEnd(vecrGuardEnMovAv.GetAverage());

                    /* Search for maximum */
                    int iMaxIndex = 0;
                    int rMaxValue = -numeric_limits<_REAL>::max(); /* Init value */
                    for (int k = 0; k < iMaxDetBufSize; k++)
                    {
                        if (pMaxDetBuffer[k] > rMaxValue)
                        {
                            rMaxValue = pMaxDetBuffer[k];
                            iMaxIndex = k;
                        }
                    }

                    /* If maximum is in the middle of the interval, mark
                       position as the beginning of the FFT window */
                    if (iMaxIndex == iCenterOfMaxDetBuf)
                    {
                        /* The optimal start position for the FFT-window
                           is the middle of the "MaxDetBuffer" */
                        iNewStartIndexField[iNewStIndCount] =
                            iTimeSyncPos * iGrdcrrDecFact -
                            iSymbolBlockSize / 2 -
                            /* Compensate for Hilbert-filter delay. The
                               delay is introduced in the downsampled
                               domain, therefore devide it by
                               "GRDCRR_DEC_FACT" */
                            iNumTapsHilbFilt / 2 / iGrdcrrDecFact;

                        iNewStIndCount++;
                    }
                }
            }

            /* Set position pointer to next step */
            iTimeSyncPos += iStepSizeGuardCorr;
        }
    }
    iNewStartIndexField.resize(iNewStIndCount);
}

ERobMode CTimeSync::detectRobustnessMode()
{
    /* Dp not start robustness mode detection until the buffer has filled */
    if (iRobModInitCnt > 1)
    {
        /* Decrease counter */
        iRobModInitCnt--;
        return RM_NO_MODE_DETECTED;
    }

    ERobMode iDetectedRModeInd= RM_NO_MODE_DETECTED;
    /* Correlation of guard-interval correlation with prepared
       cos-vector. Store highest peak */
    _REAL rMaxValRMCorr = (CReal) 0.0;
    CReal           rSecHighPeak;
    CRealVector     rResMode(NUM_ROBUSTNESS_MODES);
    for (int i = rm_low; i <= rm_high; i++)
    {
        /* Correlation with symbol rate frequency (Correlations
           must be normalized to be comparable!
           ("/ iGuardSizeX")) */
        rResMode[i] = Abs(Sum(vecrRMCorrBuffer[i] * vecrCos[i])) / iLenGuardInt[i];

        /* Search for maximum */
        if (rResMode[i] > rMaxValRMCorr)
        {
            rMaxValRMCorr = rResMode[i];
            iDetectedRModeInd = ERobMode(i);
        }
    }

    /* Get second highest peak */
    rSecHighPeak = (CReal) 0.0;
    for (int i = rm_low; i <= rm_high; i++)
    {
        if ((rResMode[i] > rSecHighPeak) && (iDetectedRModeInd != ERobMode(i)))
        {
            rSecHighPeak = rResMode[i];
        }
    }

    /* Find out if we have a reliable measure
       (distance to next peak) */
    if ((rMaxValRMCorr / rSecHighPeak) > THRESHOLD_RELI_MEASURE)
    {
        /* Reset aquisition flag for robustness mode detection */
        bRobModAcqu = false;

        return iDetectedRModeInd;
    }
    return RM_NO_MODE_DETECTED;
}

ETypeRxStatus CTimeSync::acquire(const vector<int> &iNewStartIndexField)
{
    ETypeRxStatus result = NOT_PRESENT;

    /* Use all measured FFT-window start points for determining the "real" one */
    for (unsigned int i = 0; i < iNewStartIndexField.size(); i++)
    {
        /* Check if new measurement is in range of predefined bound. This
           bound shall eliminate outliers for the calculation of the
           filtered result */
        if (((iNewStartIndexField[i] < (iCenterOfBuf + TIMING_BOUND_ABS)) &&
                (iNewStartIndexField[i] > (iCenterOfBuf - TIMING_BOUND_ABS))))
        {
            /* New measurement is in range -> use it for filtering */
            /* Low-pass filter detected start of frame */
            IIR1(rStartIndex, (CReal) iNewStartIndexField[i], LAMBDA_LOW_PASS_START);

            /* Reset counters for non-linear correction algorithm */
            iCorrCounter = 0;
            iAveCorr = 0;

            result = RX_OK;

            /* Acquisition was successful, reset init flag (just in case it
               was not reset by the non-linear correction unit */
            bInitTimingAcqu = false;
        }
        else
        {
            /* Non-linear correction of the filter-output to ged rid of
               large differences between current measurement and
               filter-output */
            iCorrCounter++;

            /* Average the NUM_SYM_BEFORE_RESET measurements for reset
               rStartIndex */
            iAveCorr += iNewStartIndexField[i];

            /* If pre-defined number of outliers is exceeded, correct */
            if (iCorrCounter > NUM_SYM_BEFORE_RESET)
            {
                /* If this is the first correction after an initialization
                   was done, reset flag and do not show red light */
                if (bInitTimingAcqu)
                {
                    /* Reset flag */
                    bInitTimingAcqu = false;

                    /* Right after initialization, the first estimate is
                       used for correction */
                    rStartIndex = (CReal) iNewStartIndexField[i];
                }
                else
                {
                    /* Correct filter-output */
                    rStartIndex = CReal(iAveCorr) / CReal(NUM_SYM_BEFORE_RESET + 1);
                    result = CRC_ERROR;
                }

                /* Reset counters */
                iCorrCounter = 0;
                iAveCorr = 0;
            }
            else
            {
                if (bInitTimingAcqu == false)
                {
                    result = DATA_ERROR;
                }
            }
        }

#ifdef _DEBUG_
        /* Save estimated positions of timing (acquisition) */
        static FILE* pFile = fopen("test/testtime.dat", "w");
        fprintf(pFile, "%d %d\n", iNewStartIndexField[i], iInputBlockSize);
        fflush(pFile);
#endif
    }
    return result;
}

void CTimeSync::ProcessDataInternal(CParameter& Parameters)
{
    int             iIntDiffToCenter;

    /* Init start index (in case no timing could be detected or init phase) */
    int iStartIndex = iSymbolBlockSize;

    /* Write new block of data at the end of shift register */
    HistoryBuf.AddEnd(*pvecInputData, iInputBlockSize);

    /* In case the time domain frequency offset estimation method is activated,
       the hilbert filtering of input signal must always be applied */
#ifdef USE_FRQOFFS_TRACK_GUARDCORR
    bool useTimeDomainFrequencyOffsetEstimation = true;
#else
    bool useTimeDomainFrequencyOffsetEstimation = false;
#endif

    /* Max number of detected peaks ("5" for safety reasons. Could be "2") */
    vector<int>    iNewStartIndexField(5);
    int iDecInpuSize=0;

    if (useTimeDomainFrequencyOffsetEstimation || bTimingAcqu || bRobModAcqu)
    {
        iDecInpuSize=HilbertFilter();
#ifdef USE_FRQOFFS_TRACK_GUARDCORR
        // Integrate the result for controlling the frequency offset
        Parameters.Lock();
        Parameters.rFreqOffsetTrack -= calcFreqOffsetTrack();
        Parameters.Unlock();
#endif
    }

    if (bTimingAcqu || bRobModAcqu)
    {
        /* Set position pointer back for this block */
        iTimeSyncPos -= iDecInpuSize;
        guardIntervalCorrelation(iNewStartIndexField, iDecInpuSize);
    }

    if (bRobModAcqu)
    {
        ERobMode eRM = detectRobustnessMode();
        if(eRM != RM_NO_MODE_DETECTED) {
            /* Set wave mode */
            Parameters.Lock();
            if (Parameters.SetWaveMode(eRM))
            {
                /* Reset output cyclic-buffer because wave mode has
                   changed and the data written in the buffer is not
                   valid anymore */
                SetBufReset1();
            }
            Parameters.Unlock();
        }
    }

    if (bTimingAcqu)
    {
        ETypeRxStatus status = acquire(iNewStartIndexField);
        /* GUI message that timing is ok */
        Parameters.Lock();
        Parameters.ReceiveStatus.TSync.SetStatus(status);
        Parameters.Unlock();

        /* Convert result to integer format for cutting out the FFT-window */
        iStartIndex = int(rStartIndex);
    }
    else
    {
        Parameters.Lock();
        /* Detect situation when acquisition was deactivated right now */
        if (bAcqWasActive)
        {
            bAcqWasActive = false;

            /* Reset also the tracking value since the tracking could not get
               right parameters since the timing was not yet correct */
            Parameters.iTimingOffsTrack = 0;
        }

        /* In case of tracking only, use final acquisition result "rStartIndex"
           (which is not updated any more) and add tracking correction */
        iStartIndex = int(rStartIndex) + Parameters.iTimingOffsTrack;

        /* Timing acquisition was successfully finished, show always green light */
        Parameters.ReceiveStatus.TSync.SetStatus(RX_OK);

        Parameters.Unlock();

#ifdef _DEBUG_
        /* Save estimated positions of timing (tracking) */
        static FILE* pFile = fopen("test/testtimetrack.dat", "w");
        static int iTimeTrackAbs = 0;
        iTimeTrackAbs += Parameters.iTimingOffsTrack; /* Integration */
        fprintf(pFile, "%d\n", iTimeTrackAbs);
        fflush(pFile);
#endif
    }


    /* -------------------------------------------------------------------------
       Cut out the estimated optimal time window and write it to the output
       vector. Add the acquisition and tracking offset together for the final
       timing */
    /* Check range of "iStartIndex" to prevent from vector overwrites. It must
       be larger than "0" since then the input block size would be also "0" and
       than the processing routine of the modul would not be called any more */
    const int i2SymBlSize = iSymbolBlockSize + iSymbolBlockSize;
    if (iStartIndex <= 0)
        iStartIndex = 1;
    if (iStartIndex >= i2SymBlSize)
        iStartIndex = i2SymBlSize;

    /* Cut out the useful part of the OFDM symbol */
    for (int k = iStartIndex; k < iStartIndex + iDFTSize; k++)
        (*pvecOutputData)[k - iStartIndex] = HistoryBuf[k];

    /* If synchronized DRM input stream is used, overwrite the detected
       timing */
    if (bSyncInput)
    {
        /* Set fixed timing position */
        iStartIndex = iSymbolBlockSize;

        /* Cut out guard-interval at right position -> no channel estimation
           needed when having only one path. No delay introduced in this
           module  */
        for (int k = iGuardSize; k < iSymbolBlockSize; k++)
        {
            (*pvecOutputData)[k - iGuardSize] =
                HistoryBuf[iTotalBufferSize - iInputBlockSize + k];
        }
    }


    /* -------------------------------------------------------------------------
       Adjust filtered measurement so that it is back in the center of the
       buffer */
    /* Integer part of the difference between filtered measurement and the
       center of the buffer */
    iIntDiffToCenter = iCenterOfBuf - iStartIndex;

    /* Set input block size for next block and reset filtered measurement. This
       is equal to a global shift of the observation window by the
       rearrangement of the filtered measurement */
    iInputBlockSize = iSymbolBlockSize - iIntDiffToCenter;

    /* In acquisition mode, correct start index */
    if (bTimingAcqu)
        rStartIndex += (CReal) iIntDiffToCenter;


    /* -------------------------------------------------------------------------
       The channel estimation needs information about timing corrections,
       because it is using information from the symbol memory. After a
       timing correction all old symbols must be corrected by a phase
       rotation as well */
    (*pvecOutputData).GetExData().iCurTimeCorr = iIntDiffToCenter;
}

void CTimeSync::InitInternal(CParameter& Parameters)
{
    Parameters.Lock();

    /* Get parameters from info class */
    iSampleRate = Parameters.GetSigSampleRate();
    int iMaxSymbolBlockSize;
    double vif;

    /* Set Hilbert-filter parameters according to sample rate */
# ifdef USE_10_KHZ_HILBFILT
    /* "GRDCRR_DEC_FACT": Downsampling factor. We only use approx. 6 [12] kHz for
       correlation, therefore we can use a decimation of 8 [4]
       (i.e., 48 kHz / 8 [4] = 6 [12] kHz). Must be 8 [4] since all symbol and
       guard-interval lengths at 48000 for all robustness modes are dividable
       by 8 [4] */
    int GRDCRR_DEC_FACT=                4;
    switch (iSampleRate)
    {
    case 24000:
        iNumTapsHilbFilt = NUM_TAPS_HILB_FILT_10_24;
        fHilLPProt = fHilLPProt10_24;
        break;
    case 48000:
        iNumTapsHilbFilt = NUM_TAPS_HILB_FILT_10_48;
        fHilLPProt = fHilLPProt10_48;
        break;
    case 96000:
        iNumTapsHilbFilt = NUM_TAPS_HILB_FILT_10_96;
        fHilLPProt = fHilLPProt10_96;
        break;
    case 192000:
        if(Parameters.GetWaveMode()==RM_ROBUSTNESS_MODE_E)
        {
            iNumTapsHilbFilt = NUM_TAPS_HILB_FILT_50_192;
            fHilLPProt = fHilLPProt50_192; // TODO MODE E - check parameters in TimeSyncFilter.m
        }
        else
        {
            iNumTapsHilbFilt = NUM_TAPS_HILB_FILT_10_192;
            fHilLPProt = fHilLPProt10_192;
        }
        break;
    case 384000:
        if(Parameters.GetWaveMode()==RM_ROBUSTNESS_MODE_E)
        {
            iNumTapsHilbFilt = NUM_TAPS_HILB_FILT_50_384;
            fHilLPProt = fHilLPProt50_384;
        }
        else
        {
            iNumTapsHilbFilt = NUM_TAPS_HILB_FILT_10_384;
            fHilLPProt = fHilLPProt10_384;
        }
        break;
    }
#else
    int GRDCRR_DEC_FACT=                8;
    switch (iSampleRate)
    {
    case 24000:
        iNumTapsHilbFilt = NUM_TAPS_HILB_FILT_5_24;
        fHilLPProt = fHilLPProt5_24;
        break;
    case 48000:
        iNumTapsHilbFilt = NUM_TAPS_HILB_FILT_5_48;
        fHilLPProt = fHilLPProt5_48;
        break;
    case 96000:
        iNumTapsHilbFilt = NUM_TAPS_HILB_FILT_5_96;
        fHilLPProt = fHilLPProt5_96;
        break;
    case 192000:
        iNumTapsHilbFilt = NUM_TAPS_HILB_FILT_5_192;
        fHilLPProt = fHilLPProt5_192;
        break;
    case 384000:
        iNumTapsHilbFilt = NUM_TAPS_HILB_FILT_5_384;
        fHilLPProt = fHilLPProt5_384;
        break;
    }
#endif

    if(Parameters.GetWaveMode()==RM_ROBUSTNESS_MODE_E)
    {
        bRobModAcqu = false;
        vif = VIRTUAL_INTERMED_FREQ_DRMPLUS;
        rm_low = RM_ROBUSTNESS_MODE_E;
        rm_high = RM_ROBUSTNESS_MODE_E;
        const int iFFTSizeN = fft_size(RM_ROBUSTNESS_MODE_E, iSampleRate);
        iMaxSymbolBlockSize = iFFTSizeN +
                              iFFTSizeN * propagationParams[RM_ROBUSTNESS_MODE_E].TgTu.val();
        /* Set step size of the guard-interval correlation */
        iStepSizeGuardCorr = STEP_SIZE_GUARD_CORR; // TODO MODE E (too large?)

        /* Adjusting GRDCRR_DEC_FACT to sample rate */
        iGrdcrrDecFact = ADJ_FOR_SRATE(GRDCRR_DEC_FACT, iSampleRate); // TODO MODE E
    }
    else
    {
        bRobModAcqu = true;
        vif = VIRTUAL_INTERMED_FREQ_DRM30;
        rm_low = RM_ROBUSTNESS_MODE_A;
        rm_high = RM_ROBUSTNESS_MODE_D;
        // for DRM30 max symbol size is with Robustness Mode A
        const int iRMAFFTSizeN = fft_size(RM_ROBUSTNESS_MODE_A, iSampleRate);
        iMaxSymbolBlockSize = iRMAFFTSizeN +
                              iRMAFFTSizeN * propagationParams[RM_ROBUSTNESS_MODE_A].TgTu.val();
        /* Set step size of the guard-interval correlation */
        iStepSizeGuardCorr = STEP_SIZE_GUARD_CORR;

        /* Adjusting GRDCRR_DEC_FACT to sample rate */
        iGrdcrrDecFact = ADJ_FOR_SRATE(GRDCRR_DEC_FACT, iSampleRate);
    }

    /* Init Hilbert filter. Since the frequency offset correction was
       done in the previous module, the offset for the filter is
       always "VIRTUAL_INTERMED_FREQ" */
    SetFilterTaps(vif / iSampleRate);

    iGuardSize = Parameters.CellMappingTable.iGuardSize;
    iDFTSize = Parameters.CellMappingTable.iFFTSizeN;
    iSymbolBlockSize = Parameters.CellMappingTable.iSymbolBlockSize;

    /* Decimated symbol block size */
    iDecSymBS = iSymbolBlockSize / iGrdcrrDecFact;

    /* We need at least two blocks of data for determining the timing */
    iTotalBufferSize = 2 * iSymbolBlockSize + iMaxSymbolBlockSize;
    int iCorrBuffSize = iTotalBufferSize / iGrdcrrDecFact;


    /* Size for moving average buffer for guard-interval correlation */
    iMovAvBufSize =
        (int) ((CReal) iGuardSize / iGrdcrrDecFact / iStepSizeGuardCorr);
    if(iMovAvBufSize==0)
        iMovAvBufSize = 1; // TODO MODE E

    /* Size of buffer, storing the moving-average results for
       maximum detection */
    iMaxDetBufSize =
        (int) ((CReal) iDecSymBS / iStepSizeGuardCorr);
    if(iMaxDetBufSize==0)
        iMaxDetBufSize = 1; // TODO MODE E

    /* Center of maximum detection buffer */
    iCenterOfMaxDetBuf = (iMaxDetBufSize - 1) / 2;

    /* Init Energy calculation after guard-interval correlation (moving
       average) */
    vecrGuardEnMovAv.Init(iMovAvBufSize);

    /* Start position of this value must be at the end of the observation
       window because we reset it at the beginning of the loop */
    iTimeSyncPos = 2 * iDecSymBS;

    /* Calculate center of buffer */
    iCenterOfBuf = iSymbolBlockSize;

    /* Init rStartIndex only if acquisition was activated */
    if (bTimingAcqu)
        rStartIndex = (CReal) iCenterOfBuf;

    /* Some inits */
    iAveCorr = 0;
    bInitTimingAcqu = true; /* Flag to show that init was done */

    /* Set correction counter so that a non-linear correction is performed right
       at the beginning */
    iCorrCounter = NUM_SYM_BEFORE_RESET;


    /* Allocate memory for vectors and zero out */
    HistoryBuf.Init(iTotalBufferSize, (CReal) 0.0);
    pMaxDetBuffer.Init(iMaxDetBufSize, (CReal) 0.0);
    HistoryBufCorr.Init(iCorrBuffSize, (CReal) 0.0);


    /* Inits for averaging the guard-interval correlation */
    vecCorrAvBuf.Init(iMaxDetBufSize, (CReal) 0.0);
    iCorrAvInd = 0;


    /* Set the selected robustness mode index */
    eSelectedMode = Parameters.GetWaveMode();

    /* Init init count for timing sync (one symbol) */
    iTiSyncInitCnt = iDecSymBS / iStepSizeGuardCorr;


    /* Inits for guard-interval correlation and robustness mode detection --- */
    /* Size for robustness mode correlation buffer */
    iRMCorrBufSize = int((CReal) NUM_BLOCKS_FOR_RM_CORR * iDecSymBS / iStepSizeGuardCorr);

    /* Init init count for robustness mode detection (do not use the very first
       block) */
    iRobModInitCnt = NUM_BLOCKS_FOR_RM_CORR + 1;

    for (int i = rm_low; i <= rm_high; i++)
    {
        cGuardCorr[i] = (CReal) 0.0;
        cGuardCorrBlock[i] = (CReal) 0.0;
        rGuardPow[i] = (CReal) 0.0;
        rGuardPowBlock[i] = (CReal) 0.0;
        iPosInIntermCResBuf[i] = 0;

        /* Set length of the useful part of the symbol and guard size */
        int iFFTSizeN = fft_size(i, iSampleRate);
        iLenUsefPart[i] = iFFTSizeN / iGrdcrrDecFact;
        double TgTu = propagationParams[i].TgTu.val();
        iLenGuardInt[i] = (int) ((CReal) iFFTSizeN * TgTu / iGrdcrrDecFact);

        /* Number of correlation result blocks to be stored in a vector. This is
           the total length of the guard-interval divided by the step size.
           Since the guard-size must not be a multiple of "iStepSizeGuardCorr",
           we need to cut-off the fractional part.
           For Mode E we get 0 so we need to reduce the step size
         */
        if(iStepSizeGuardCorr > iLenGuardInt[i]) {
            iStepSizeGuardCorr = iLenGuardInt[i];
        }
        iLengthOverlap[i] = iLenGuardInt[i] - iStepSizeGuardCorr;

        iLengthIntermCRes[i] = (int) ((CReal) iLenGuardInt[i] /
                                      iStepSizeGuardCorr);

        /* This length is the start point for the "for"-loop */
        iLengthOverlap[i] = iLenGuardInt[i] -
                            iStepSizeGuardCorr;

        /* Intermediate correlation results vector (init, zero out) */
        veccIntermCorrRes[i].Init(iLengthIntermCRes[i], (CReal) 0.0);
        vecrIntermPowRes[i].Init(iLengthIntermCRes[i], (CReal) 0.0);

        /* Allocate memory for correlation input buffers */
        vecrRMCorrBuffer[i].Init(iRMCorrBufSize);
        vecrRMCorrBuffer[i] = Zeros(iRMCorrBufSize);

        /* Calculate frequency bin size which has to be observed for each mode
         * ES 201 980 V4.1.1 Table 2.
           Mode A: f_A = 1 / T_s = 1 / 26.66 ms = 37.5 Hz
           Mode B: f_B = 1 / T_s = 1 / 26.66 ms = 37.5 Hz
           Mode C: f_C = 1 / T_s = 1 / 20 ms = 50 Hz
           Mode D: f_D = 1 / T_s = 1 / 16.66 ms = 60 Hz
           Mode E: f_E = 1 / T_s = 1 / 10.5 ms  = 95.24 Hz
           */
        int iObservedFreqBin = int(CReal(iRMCorrBufSize * STEP_SIZE_GUARD_CORR) / CReal(iLenUsefPart[i] + iLenGuardInt[i]));

        /* Tables for sin and cos function for the desired frequency band */
        /* First, allocate memory for vector */
        vecrCos[i].Init(iRMCorrBufSize);

        /* Build table */
        for (int j = 0; j < iRMCorrBufSize; j++)
        {

            _REAL rArgTemp = 2.0 * crPi / iRMCorrBufSize * j;

            vecrCos[i][j] = cos(rArgTemp * iObservedFreqBin);
        }
    }

#ifdef USE_FRQOFFS_TRACK_GUARDCORR
    /* Init vector for averaging the frequency offset estimation */
    cFreqOffAv = CComplex(0.0, 0.0);

    /* Init time constant for IIR filter for frequency offset estimation */
    rLamFreqOff = IIR1Lam(TICONST_FREQ_OFF_EST_GUCORR, _REAL(iSampleRate) / _REAL(iSymbolBlockSize));

    /* Nomalization constant for frequency offset estimation */
    rNormConstFOE = 1.0 / (2.0 * crPi * Parameters.CellMappingTable.iFFTSizeN * iGrdcrrDecFact);
#endif

    /* Define block-sizes for input and output */
    iInputBlockSize = iSymbolBlockSize; /* For the first loop */
    iOutputBlockSize = iDFTSize;

    Parameters.Unlock();
}

void CTimeSync::StartAcquisition()
{

// TODO: check which initialization should be done here and which should be
// moved to / from the "InitInternal()" function

    /* The regular acquisition flags */
    bTimingAcqu = true;

    /* Set the init flag so that the "rStartIndex" can be initialized with the
       center of the buffer and other important settings can be done */
    SetInitFlag();

    /* This second flag is to determine the moment when the acquisition just
       finished. In this case, the tracking value must be reset */
    bAcqWasActive = true;

    iCorrCounter = NUM_SYM_BEFORE_RESET;

    /* Reset the buffers which are storing data for correlation (for robustness
       mode detection) */
    //for (int i = 0; i < NUM_ROBUSTNESS_MODES; i++)
    //  vecrRMCorrBuffer[i] = Zeros(iRMCorrBufSize);

    /* Reset lambda for averaging the guard-interval correlation results */
    rLambdaCoAv = (CReal) 1.0;
    iCorrAvInd = 0;
}

void CTimeSync::SetFilterTaps(CReal rNewOffsetNorm)
{
#ifndef USE_10_KHZ_HILBFILT
    /* The filter should be on the right of the DC carrier in 5 kHz mode */
    rNewOffsetNorm += (CReal) HILB_FILT_BNDWIDTH_5 / 2 / iSampleRate;
#endif

    /* Calculate filter taps for complex Hilbert filter */
    cvecB.Init(iNumTapsHilbFilt);

    for (int i = 0; i < iNumTapsHilbFilt; i++)
        cvecB[i] = CComplex(
                       fHilLPProt[i] * Cos(2.0 * crPi * rNewOffsetNorm * i),
                       fHilLPProt[i] * Sin(2.0 * crPi * rNewOffsetNorm * i));

    /* Init state vector for filtering with zeros */
    cvecZ.Init(iNumTapsHilbFilt - 1, 0.0);
}

CTimeSync::CTimeSync() : iSampleRate(0), iGrdcrrDecFact(0),
    iNumTapsHilbFilt(0), fHilLPProt(NULL),
    iTimeSyncPos(0), bSyncInput(false), bTimingAcqu(false),
    bRobModAcqu(false), bAcqWasActive(false), rLambdaCoAv((CReal) 1.0),
    iLengthIntermCRes(NUM_ROBUSTNESS_MODES),
    iPosInIntermCResBuf(NUM_ROBUSTNESS_MODES),
    iLengthOverlap(NUM_ROBUSTNESS_MODES), iLenUsefPart(NUM_ROBUSTNESS_MODES),
    iLenGuardInt(NUM_ROBUSTNESS_MODES), cGuardCorr(NUM_ROBUSTNESS_MODES),
    cGuardCorrBlock(NUM_ROBUSTNESS_MODES), rGuardPow(NUM_ROBUSTNESS_MODES),
    rGuardPowBlock(NUM_ROBUSTNESS_MODES), vecrRMCorrBuffer()
{
}

/******************************************************************************\
 * Technische Universitaet Darmstadt, Institut fuer Nachrichtentechnik
 * Copyright (c) 2001
 *
 * Author(s):
 *	Volker Fischer, Ollie Haffenden
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

#ifndef __AUDIOSOURCEENCODER_H
# define __AUDIOSOURCEENCODER_H

#include "../GlobalDefinitions.h"
#include "../Parameter.h"
#include "../util/Modul.h"
#include "../util/CRC.h"
#include "../TextMessage.h"
#include "../resample/Resample.h"
#include "../datadecoding/DataEncoder.h"
#include "../util/Utilities.h"

#ifdef USE_FAAC_LIBRARY
# include <faac.h>
#else
# include "faac_dll.h"
#endif

/* Classes ********************************************************************/
class CAudioSourceEncoderImplementation
{
public:
	CAudioSourceEncoderImplementation();
	virtual ~CAudioSourceEncoderImplementation();

	void SetTextMessage(const string& strText);
	void ClearTextMessage();

	void SetPicFileName(const string& strFileName, const string& strFormat)
		{DataEncoder.GetSliShowEnc()->AddFileName(strFileName, strFormat);}
	void ClearPicFileNames()
		{DataEncoder.GetSliShowEnc()->ClearAllFileNames();}
	void SetPathRemoval(_BOOLEAN bRemovePath)
		{DataEncoder.GetSliShowEnc()->SetPathRemoval(bRemovePath);}
	_BOOLEAN GetTransStat(string& strCPi, _REAL& rCPe)
		{return DataEncoder.GetSliShowEnc()->GetTransStat(strCPi, rCPe);}

protected:
	CTextMessageEncoder		TextMessage;
	_BOOLEAN				bUsingTextMessage;
	CDataEncoder			DataEncoder;
	int						iTotPacketSize;
	_BOOLEAN				bIsDataService;
	int						iTotNumBitsForUsage;

	faacEncHandle			hEncoder;
	faacEncConfigurationPtr CurEncFormat;

	unsigned long			lNumSampEncIn;
	unsigned long			lMaxBytesEncOut;
	unsigned long			lEncSamprate;
	CVector<_BYTE>			aac_crc_bits;
	CVector<_SAMPLE>		vecsEncInData;
	CMatrix<_BYTE>			audio_frame;
	CVector<int>			veciFrameLength;
	int						iNumAACFrames;
	int						iAudioPayloadLen;
	int						iNumHigherProtectedBytes;

	_BOOLEAN				bFaacCodecSupported;
	CAudioResample			ResampleObj;
	CVector<_REAL>			vecTempResBufIn;
	CVector<_REAL>			vecTempResBufOut;

public:
		virtual void InitInternalTx(CParameter& Parameters, int &iInputBlockSize, int &iOutputBlockSize);
		virtual void InitInternalRx(CParameter& Parameters, int &iInputBlockSize, int &iOutputBlockSize);
		virtual void ProcessDataInternal(CParameter& Parameters, CVectorEx<_SAMPLE>* pvecInputData,
						CVectorEx<_BINARY>* pvecOutputData, int &iInputBlockSize, int &iOutputBlockSize);
};

class CAudioSourceEncoderRx : public CReceiverModul<_SAMPLE, _BINARY>
{
public:
	CAudioSourceEncoderRx() {}
	virtual ~CAudioSourceEncoderRx() {}

protected:
	CAudioSourceEncoderImplementation AudioSourceEncoderImpl;

	virtual void InitInternal(CParameter& Parameters)
	{
		AudioSourceEncoderImpl.InitInternalRx(Parameters, iInputBlockSize, iOutputBlockSize);
	}

	virtual void ProcessDataInternal(CParameter& Parameters)
	{
		AudioSourceEncoderImpl.ProcessDataInternal(Parameters, pvecInputData, pvecOutputData, iInputBlockSize, iOutputBlockSize);
	}
};

class CAudioSourceEncoder : public CTransmitterModul<_SAMPLE, _BINARY>
{
public:
	CAudioSourceEncoder() {}
	virtual ~CAudioSourceEncoder() {}

	void SetTextMessage(const string& strText) {AudioSourceEncoderImpl.SetTextMessage(strText);}
	void ClearTextMessage() {AudioSourceEncoderImpl.ClearTextMessage();}

	void SetPicFileName(const string& strFileName, const string& strFormat)
			{AudioSourceEncoderImpl.SetPicFileName(strFileName, strFormat);}

	void ClearPicFileNames() {AudioSourceEncoderImpl.ClearPicFileNames();}

	void SetPathRemoval(_BOOLEAN bRemovePath)
			{AudioSourceEncoderImpl.SetPathRemoval(bRemovePath);}

	_BOOLEAN GetTransStat(string& strCPi, _REAL& rCPe)
			{return AudioSourceEncoderImpl.GetTransStat(strCPi, rCPe);}

protected:
	CAudioSourceEncoderImplementation AudioSourceEncoderImpl;

	virtual void InitInternal(CParameter& Parameters)
	{
		AudioSourceEncoderImpl.InitInternalTx(Parameters, iInputBlockSize, iOutputBlockSize);
	}

	virtual void ProcessDataInternal(CParameter& Parameters)
	{
		AudioSourceEncoderImpl.ProcessDataInternal(Parameters, pvecInputData, pvecOutputData, iInputBlockSize, iOutputBlockSize);
	}

};

#endif

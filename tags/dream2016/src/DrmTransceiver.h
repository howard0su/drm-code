/******************************************************************************\
 *
 * Copyright (c) 2001-2014
 *
 * Author(s):
 *  David Flamand
 *
 * Description:
 *  DRM receiver-transmitter base class
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

#ifndef _DRM_TRANSCEIVER_H_
#define _DRM_TRANSCEIVER_H_

#include "Parameter.h"
#include "util/Settings.h"
#include "sound/soundinterface.h"

class CDRMTransceiver
{
public:
    CDRMTransceiver(CSettings* pSettings, CSoundInInterface* pSoundIn, CSoundOutInterface* pSoundOut, bool bTransmitter = false)
        : pSettings(pSettings), pSoundInInterface(pSoundIn), pSoundOutInterface(pSoundOut), bTransmitter(bTransmitter) {};
    virtual ~CDRMTransceiver() {};

    virtual void LoadSettings() = 0;
    virtual void SaveSettings() = 0;
    virtual void Start() = 0;

    virtual void Restart()
    {
        if (Parameters.eRunState == CParameter::RUNNING)
            Parameters.eRunState = CParameter::RESTART;
    }
    virtual void Stop()
    {
        Parameters.eRunState = CParameter::STOP_REQUESTED;
    }
    virtual CSettings*              GetSettings() {
        return pSettings;
    }
    virtual void                    SetSettings(CSettings* pNewSettings) {
        pSettings = pNewSettings;
    }
    virtual CParameter*             GetParameters() {
        return &Parameters;
    }
    virtual CSoundInInterface*      GetSoundInInterface() {
        return pSoundInInterface;
    }
    virtual CSoundOutInterface*     GetSoundOutInterface() {
        return pSoundOutInterface;
    }
    virtual bool                IsReceiver() const {
        return !bTransmitter;
    }
    virtual bool                IsTransmitter() const {
        return bTransmitter;
    }

protected:
    virtual void CloseSoundInterfaces()
    {
        pSoundInInterface->Close();
        pSoundOutInterface->Close();
    }
    CSettings*              pSettings;
    CParameter              Parameters;
    CSoundInInterface*      pSoundInInterface;
    CSoundOutInterface*     pSoundOutInterface;

private:
    const bool bTransmitter;
};

#endif

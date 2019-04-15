/******************************************************************************\
 * British Broadcasting Corporation
 * Copyright (c) 2009
 *
 * Author(s):
 *	 Julian Cable, David Flamand
 *
 * Description: MOT Slide Show Viewer
 *
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

#ifndef _SLIDESHOWVIEWER_H
#define _SLIDESHOWVIEWER_H

#include "ui_SlideShowViewer.h"
#include "../DrmReceiver.h"
#include "DialogUtil.h"
class CSettings;

class SlideShowViewer : public QDialog, Ui_SlideShowViewer
{
    Q_OBJECT

public:
    SlideShowViewer(CDRMReceiver&, CSettings&, QWidget* parent = 0);
    virtual ~SlideShowViewer();

protected:
    void                    SetImage(int);
    void                    UpdateButtons();
    void                    ClearMOTCache(CMOTDABDec *motdec);
    void                    GetServiceParams(uint32_t* iServiceID, bool* bServiceValid, QString* strLabel, ETypeRxStatus* eStatus=NULL, int* shortID=NULL, int* iPacketID=NULL);
    void                    UpdateWindowTitle(const uint32_t iServiceID, const bool bServiceValid, QString strLabel);
    QTimer                  Timer;
    QString                 strCurrentSavePath;
    CDRMReceiver&           receiver;
    CSettings&              settings;
    std::vector<QPixmap>    vecImages;
    std::vector<QString>    vecImageNames;
    int                     iCurImagePos;
    bool                    bClearMOTCache;
    uint32_t                iLastServiceID;
    uint32_t                iCurrentDataServiceID;
    bool                    bLastServiceValid;
    QString                 strLastLabel;
    CEventFilter            ef;

public slots:
    void OnTimer();
    void OnButtonStepBack();
    void OnButtonStepForward();
    void OnButtonJumpBegin();
    void OnButtonJumpEnd();
    void OnSave();
    void OnSaveAll();
    void OnClearAll();
    void showEvent(QShowEvent*);
    void hideEvent(QHideEvent*);
};

#endif

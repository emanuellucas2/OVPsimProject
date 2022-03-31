/* Copyright (c) 2007-2008 The Android Open Source Project
**
** This software is licensed under the terms of the GNU General Public
** License version 2, as published by the Free Software Foundation, and
** may be copied, distributed, and modified under those terms.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
*/

/*
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                          Thu Jun  3 10:26:23 2010
//
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"

#include "framebuffer.h"

#include "fbstate.h"

#define PREFIX                      "FRAME_BUFFER"
#define SCAN_DELAY_ATTRIBUTE        "period"
#define STATS_OUTPUT_RATE_ATTRIBUTE "statsOutput"
#define FRAME_TYPE_ATTRIBUTE        "frameType"

static double refreshPeriod = 20000; // TODO

fb_stateT     fbState;
QFrameBufferT qBuff;

//////////////////////////////// INTERCEPTED FUNCTIONs ////////////////////////

#define FAILED_TO_INTERCEPT bhmMessage("F", PREFIX "_FI", "Failed to intercept %s", __FUNCTION__)

//
// Start the display and set the system constants
//
void NOINLINE displayInit(
    const char *title,
    void       *fbStateAddress,
    void       *qBuffAddress,
    Uns32       diagnostics,
    Uns32       frameType
) {
    FAILED_TO_INTERCEPT;
}

//
// Set the base address of the video RAM
//
void NOINLINE setVideoBase(Uns32 baseAddress) {
    FAILED_TO_INTERCEPT;
}

//
// Use current RAM to update the screen.
// RAM is mapped into Host space.
//
void NOINLINE updateFrame(void) {
    FAILED_TO_INTERCEPT;
}

//
// Set the base address of the video RAM
//
void NOINLINE setTitle(const char * title) {
    FAILED_TO_INTERCEPT;
}

///////////////////////////////////////////////////////////////////////////////

static void refreshUpdateFrame() {

    if(fbState.need_update) {
        fbState.need_update = 0;
    }

    updateFrame();

}

//////////////////////////////// Callback stubs

PPM_REG_WRITE_CB(writeBASE) {
    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX, "%s 0x%x", __func__, data);

    Uns32 need_resize   = !fbState.base_valid;
    fbState.fb_base     = data;
    fbState.need_update = 1;
    fbState.base_valid  = 1;

    // Set video Base address
    setVideoBase(data);

    if (need_resize || fbState.need_update) {
        updateFrame();
    }

    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(writeBLANK) {
    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX, "%s %u", __func__, data);

    fbState.blank       = data;
    fbState.need_update = 1;
    *(Uns32*)user       = data;
}

PPM_REG_WRITE_CB(writeTITLE) {
    static Uns32 ptr=0;
    static char  title[36];

    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX, "%s %c", __func__, data&0xff);

    title[ptr] = data&0xff;
    if(data == 0) {
        // end of title update
        if(PSE_DIAG_LOW)
            bhmMessage("I", PREFIX, "%s Update Title '%s'", __func__, title);
        // update title
        setTitle(title);
        ptr=0;
    } else {
        ptr++;
    }

    if(ptr>35) {
        ptr=0;
        if(PSE_DIAG_LOW)
            bhmMessage("W", PREFIX, "%s title index exceeded max", __func__);
    }


    *(Uns32*)user = data;
}

static void refreshThread(void *user) {
    if (PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX "_RF", "refresh starting.");
    }
    while(1) {
        bhmWaitDelay (refreshPeriod);
        refreshUpdateFrame();
    }
}

Uns32 NOINLINE ImperasTestModeTimeout(double * timeout)
{
    FAILED_TO_INTERCEPT;
    return 0;
}

double ImperasTestTimeout = 0.0;
static void ImperasTestModeTimeoutThread(void *user) {
    bhmWaitDelay(ImperasTestTimeout*1000000); // timeout in seconds
    bhmFinish();
}

PPM_CONSTRUCTOR_CB(constructor) {

    if(ImperasTestModeTimeout(&ImperasTestTimeout)) {
        bhmCreateThread(ImperasTestModeTimeoutThread, 0, "ImperasTestModeTimeoutThread", 0);
    }

    Uns32 period;

    bhmUns32ParamValue(SCAN_DELAY_ATTRIBUTE,  &period);
    if(period==0) {
        bhmMessage("I", PREFIX, "Parameter " SCAN_DELAY_ATTRIBUTE " zero, auto refresh disabled");
    }

    refreshPeriod = period;

    char title[32] = "Frame Buffer";
    bhmStringParamValue("title", title, sizeof(title));

    Uns32 frameType;
    bhmUns32ParamValue(FRAME_TYPE_ATTRIBUTE,  &frameType);
    bhmMessage("I", PREFIX, "Parameter " FRAME_TYPE_ATTRIBUTE " %u", frameType);

    periphConstructor();

    displayInit(title, &fbState, &qBuff, diagnosticLevel, frameType);

    if(refreshPeriod != 0) {
        bhmCreateThread(refreshThread, 0, "refreshThread", 0);
    }
}

PPM_CONSTRUCTOR_CB(destructor) {
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}


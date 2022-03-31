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
//                           Imperas/OVP Generated
//                          Tue Sep 18 17:51:12 2012
//
////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include "pse.igen.h"

typedef struct outputPinS {
    const char  *name;
    ppmNetHandle netP;
    Uns32        value;
} outputPin, *outputPinP;

static outputPin BRGOUT = { "BRGOUT", 0, 0 };
static outputPin INTBRG = { "INTBRG", 0, 0 };

static Uns32  PCLK;
static double fBRGn;
static double microSecCB;

static bhmThreadHandle timerThreadHandle = 0;
static double threadDelay;

Uns32 pow2 (Uns32 pow) {
    Uns32 result = 0x1 << pow;
    return result;
}

//
// Only write when a value change occurs
//
static void doWriteNet(outputPinP pin, Uns32 value) {
    if (value != pin->value) {
        pin->value = value;
        ppmWriteNet(pin->netP, pin->value);
    }
}

static void doToggleNet(outputPinP pin) {
    doWriteNet(pin, !pin->value);
}

static void togglePorts() {
    if (PSE_DIAG_HIGH) {
        static float timestamp = 0;
        static Uns32 freq1, freq2;
        float dutycycle = bhmGetCurrentTime() - timestamp;

        freq1 = (1/(dutycycle*2))*1000; // in Khz

        if (freq1 != freq2) {
            bhmMessage("W", "BRG", "Freq out %dKhz -> %dKhz", freq2, freq1);
        }
        freq2 = freq1;
        timestamp = bhmGetCurrentTime();
    }

    if (BRGP0_reg0_data.PRSM.bits.BGCE) {
        doToggleNet(&BRGOUT);

        if (BRGP0_reg0_data.PRSM.bits.TODIS == 0) {
            doToggleNet(&INTBRG);
        }
    }
}

static void timerThread(void *user) {
    while (1) {
        bhmWaitDelay(threadDelay);
        if (PSE_DIAG_HIGH) bhmMessage("I", "BRG", "Timer Expired %f", bhmGetCurrentTime());

        togglePorts();
    }
}

static void stopTimer(void) {
    if (timerThreadHandle) {
        if (PSE_DIAG_HIGH) bhmMessage("I", "BRG", "Stop Timer %f", bhmGetCurrentTime());
        bhmDeleteThread(timerThreadHandle);
        timerThreadHandle = 0;
    }
}

static void startTimer(double delay) {
    stopTimer();
    threadDelay = delay;
    if (PSE_DIAG_HIGH) bhmMessage("I", "BRG", "Start Timer(%f) %f",  delay, bhmGetCurrentTime());
    timerThreadHandle = bhmCreateThread(timerThread, 0, "timer", 0);
}

void update_timer () {
    //
    // Calculate the Pre-scaling
    // PCLK = 16Mhz
    // fBRGn = PCLK / (2**k x N x 2)
    // k = BGCS
    // N = PRSCM

    Uns16 PRSCM = BRGP0_reg0_data.PRSCM.value;
    if (PRSCM == 0) {
        PRSCM = 256;
    }
    Uns64 div  = pow2(BRGP0_reg0_data.PRSM.bits.BGCS);
    div *= (PRSCM * 2);
    if (div) {
        fBRGn = PCLK / div;
    } else {
        fBRGn = 0;
    }
    microSecCB = (1 / fBRGn) * 1000000;

    //
    // Which outputs are enabled, and is counting enabled
    //
    if (BRGP0_reg0_data.PRSM.bits.BGCE) {
        //
        // Counting Enabled
        //
        if (BRGP0_reg0_data.PRSM.bits.TODIS) {
            //
            // Timer Out Disabled
            //
            doWriteNet(&BRGOUT, 0);
        }
        startTimer(microSecCB/2); // microSecCB for transition of output signals

    } else {
        //
        // Counting Disabled
        //
        doWriteNet(&BRGOUT, 0);
        doWriteNet(&INTBRG, 0);

        stopTimer();

    }

}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_WRITE_CB(writePRSCM) {
    *(Uns8*)user = (*(Uns8*)user & 0x0) | (data & 0xff);

    update_timer();
}

PPM_REG_WRITE_CB(writePRSM) {
    //
    // Check legal values
    //
    if (data & 0xe8) {
        bhmMessage("W", "BRG", "Register PRSM Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0xe8) | (data & 0x17);

    update_timer();
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();

    BRGOUT.netP = handles.BRGOUT;
    INTBRG.netP = handles.INTBRG;

    //
    // Get the PCLK attribute
    //
    if (!bhmUns32ParamValue("PCLK", &PCLK)){
        PCLK = pow2(25);  // default 32Mhz
    }

    update_timer();
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}


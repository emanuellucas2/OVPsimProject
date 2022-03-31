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
//                          Fri Jan  6 11:38:59 2012
//
////////////////////////////////////////////////////////////////////////////////

#define PREFIX "IMX6_WDOG"

#include "pse.igen.h"
#define BPORT1 0
#include "pse.macros.igen.h"

static bhmEventHandle  watchdogInterrupt, watchdogFailure, powerDownFailure;
static bhmThreadHandle watchdogThread, powerDownThread;

Uns32 lockSeq = 0;
Uns32 locks[2] = {0x5555, 0xaaaa};

// The timout to perform
double timeoutInterrupt  = 0;
double timeoutWatchdog   = 0.5;
#define TOUSEC 1000000

////////////////////////////////                ////////////////////////////////

void updateInterrupt() {

    if(bport1_ab_data.WDOG_WICR.bits.WIE && bport1_ab_data.WDOG_WICR.bits.WTIS) {
        // assert WDOG
        ppmWriteNet(handles.WDOG, 1);
    } else {
        // clear
        ppmWriteNet(handles.WDOG, 0);
    }

}
void updateStatus(Bool fail) {
    // update status register and interrupt
    // fail = 1 when watchdog expires
    // fail = 0 when reached interupt
    if (fail && bport1_ab_data.WDOG_WCR.bits.WDT) {

        // clear other bits
        bport1_ab_data.WDOG_WRSR.value &= ~(BPORT1_AB_WDOG_WRSR_POR  |
                                            BPORT1_AB_WDOG_WRSR_SFTW);
        // reset caused by Timeout
        bport1_ab_data.WDOG_WRSR.bits.TOUT = 1;
        bport1_ab_data.WDOG_WICR.bits.WTIS = 1;

        updateInterrupt();
    }
}

//
// WDOG Timer
//
void watchdogTimoutThread(void *user)
{
    double toWatchdogTimeout = timeoutWatchdog;

    // If timeout interrupt setup
    if(bport1_ab_data.WDOG_WICR.bits.WIE && timeoutInterrupt){
        if(PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX "_WT", "Start Watchdog Interrupt %3.1f Seconds", timeoutInterrupt);
        }
        bhmWaitDelay(timeoutInterrupt*TOUSEC);
        if(PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX "_WT", "Watchdog Interrupt at %.2f Seconds", bhmGetCurrentTime()/TOUSEC);
        }
        bhmTriggerEvent(watchdogInterrupt);
        updateStatus(0);

        // calculate remaining timeout to watchdog
        toWatchdogTimeout -= timeoutInterrupt;
    }

    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_WT", "Start Watchdog %3.1f Seconds", toWatchdogTimeout);
    }
    bhmWaitDelay(toWatchdogTimeout*TOUSEC);
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_WT", "Watchdog at %.2f Seconds", bhmGetCurrentTime()/TOUSEC);
    }
    bhmTriggerEvent(watchdogFailure);
    updateStatus(1);
    watchdogThread = 0;
}

//
// Power Down Timer
//
void powerDownTimeoutThread(void *user)
{
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_PDT", "Start Power Down Timer %3.1f Seconds", (double)(16));
    }

    // start a 16 second timeout
    bhmWaitDelay(16*TOUSEC);

    if(PSE_DIAG_MEDIUM) {
        bhmMessage("I", PREFIX "_PD", "Power Down Timer Failure at %.2f Seconds", bhmGetCurrentTime()/TOUSEC);
    }
    bhmTriggerEvent(powerDownFailure);
    updateStatus(1);
    powerDownThread = 0;
}

void updateTimeout() {
    // update timout value
    timeoutWatchdog = 0.5 * (bport1_ab_data.WDOG_WCR.bits.WT + 1 );

    if (bport1_ab_data.WDOG_WICR.bits.WIE) {
        // interrupt generation enabled before timeout
        timeoutInterrupt = timeoutWatchdog - (0.5*bport1_ab_data.WDOG_WICR.bits.WICT);
    } else {
        timeoutInterrupt = 0;
    }
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_TU", "Timeout updated. "
                               "To Interrupt %3.1f Seconds. "
                               "To Watchdog %3.1f Seconds",
                               timeoutInterrupt, timeoutWatchdog);
    }
    // has been enabled
    if(watchdogThread) {
        bhmDeleteThread(watchdogThread);
    }

    watchdogThread  = bhmCreateThread(watchdogTimoutThread, NULL, "Watchdog Timeout", 0);

}


//////////////////////////////// Callback stubs ////////////////////////////////

PPM_WRITE_CB(regNoDefinitionRead) {
    Uns32 offset = addr - handles.bport1;
    bhmMessage("W", PREFIX, "No Write Register Defined at offset 0x%04x", offset);
}

PPM_READ_CB(regNoDefinitionWrite) {
    Uns32 offset = addr - handles.bport1;
    bhmMessage("W", PREFIX, "No Read Register Defined at offset 0x%04x", offset);
    return 0;
}

PPM_REG_WRITE_CB(WriteWDOG_WCR) {

    *(Uns16*)user = data | 0x8f;    // mask write once bits (cannot be cleared until reset)
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_WR", "%s: 0x%04x", __FUNCTION__, *(Uns16*)user);
    }
    // assert watchdog signal
    ppmWriteNet(handles.WDOG, bport1_ab_data.WDOG_WCR.bits.WDA ? 0 : 1);

    if(!bport1_ab_data.WDOG_WCR.bits.SRS) {
        if(PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX "_SR", "Software Reset");
        }

        // clear other bits
        bport1_ab_data.WDOG_WRSR.value &= ~(BPORT1_AB_WDOG_WRSR_POR  |
                                            BPORT1_AB_WDOG_WRSR_TOUT);
        // indicate software reset
        bport1_ab_data.WDOG_WRSR.bits.SFTW = 1;

        // generate reset
        ppmWriteNet(handles.wdog_rst, 1);
        ppmWriteNet(handles.wdog_rst, 0);
    }
    if(bport1_ab_data.WDOG_WCR.bits.WDE && !(data & BPORT1_AB_WDOG_WCR_WDE)){

            updateTimeout();

    } else if(!bport1_ab_data.WDOG_WCR.bits.WDE && (data & BPORT1_AB_WDOG_WCR_WDE)){
        // has been disabled
        // TODO: When enabled start again from start or continue?
        if(watchdogThread) {
            bhmDeleteThread(watchdogThread);
        }
    }

}

PPM_REG_WRITE_CB(WriteWDOG_WICR) {

    *(Uns16*)user = (*(Uns16*)user & 0x7f00) | (data & 0x80ff);
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_WR", "%s: 0x%04x", __FUNCTION__, *(Uns16*)user);
    }
    if(bport1_ab_data.WDOG_WICR.bits.WIE && !(data & BPORT1_AB_WDOG_WICR_WIE)){
        // interrupt enabled
        updateTimeout();
    }
    if(data & BPORT1_AB_WDOG_WICR_WTIS) {
        // clear interrupt
        bport1_ab_data.WDOG_WICR.bits.WTIS = 0;
        updateInterrupt();
    }
}

PPM_REG_WRITE_CB(WriteWDOG_WMCR) {

    // If PDE is set allow software to clear
    if(bport1_ab_data.WDOG_WMCR.bits.PDE) {
        *(Uns16*)user = (*(Uns16*)user & 0xfffe) | (data & 0x1);
    }

    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_WR", "%s: 0x%04x", __FUNCTION__, *(Uns16*)user);
    }

    if(!bport1_ab_data.WDOG_WMCR.bits.PDE && powerDownThread) {
        // disable power down counter
        bhmDeleteThread(powerDownThread);
        powerDownThread=0;
    }
}

PPM_REG_WRITE_CB(WriteWDOG_WSR) {
    // YOUR CODE HERE (WriteWDOG_WSR)
    *(Uns16*)user = data;
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_WR", "%s: 0x%04x", __FUNCTION__, *(Uns16*)user);
    }
    if (bport1_ab_data.WDOG_WCR.bits.WDE) {
        // when enabled must go through sequence to update timer
        if (data == locks[lockSeq]) {
            lockSeq++;
            if(lockSeq >= 2) {
                // correct sequence complete
                updateTimeout();
                lockSeq = 0;
            }
        } else {
            if(PSE_DIAG_LOW) {
                bhmMessage("W", PREFIX "_LS", "%s: lock 0x%04x expected 0x%04x",
                        __FUNCTION__, *(Uns16*)user, locks[lockSeq]);
            }
            // check if it was the first in sequence
            if (data == locks[0]) {
                lockSeq = 1;
            } else {
                lockSeq = 0;
            }
        }
    } else {
        // when NOT enabled update timer
        updateTimeout();
    }
}


////////////////////////////////                ////////////////////////////////

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    // indicate power on reset
    bport1_ab_data.WDOG_WRSR.bits.POR = 1;

    watchdogFailure  = bhmCreateNamedEvent("watchdogFault", "Watchdog Timeout");
    powerDownFailure = bhmCreateNamedEvent("powerDownFault", "Power Down Timeout");

    powerDownThread  = bhmCreateThread(powerDownTimeoutThread, NULL, "Power Down Timeout", 0);

}

PPM_DESTRUCTOR_CB(destructor) {
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}


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
//
////////////////////////////////////////////////////////////////////////////////

#include <string.h>

#include "pse.igen.h"

#define PREFIX "SWDT"

#define MODE_ZEROACCESSKEY 0xABC
#define CONTROL_CKEY       0x0248
#define RESTART_RESTARTKEY 0x1999

#define statusWDZ     bport1_ab_data.STATUS.bits.WDZ
#define modeIRQLN     bport1_ab_data.MODE.bits.IRQLN
#define modeWDEN      bport1_ab_data.MODE.bits.WDEN
#define modeIRQEN     bport1_ab_data.MODE.bits.IRQEN
#define modeRSTEN     bport1_ab_data.MODE.bits.RSTEN
#define controlCRV    bport1_ab_data.CONTROL.bits.CRV
#define controlCLKSEL bport1_ab_data.CONTROL.bits.CLKSEL

double clockRate;                   // the PCLK rate (MHz)

bhmEventHandle watchdogTrigger;     // trigger when watchdog time out

double getTick() {
    Uns32 divider = 4096;
    switch (controlCLKSEL) {
        case 0:
            divider =   8;
            break;
        case 1:
            divider =  64;
            break;
        case 2:
            divider = 512;
            break;
        default:
            break;
    }

    return (double) (clockRate / divider);
}

void updateWatchdog() {
    double tick = getTick();

    double watchdogTimout = ((double)((controlCRV << 12) + 0xfff)) / tick;

    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_WD_SET", "Watchdog : %10.3f usec\n", watchdogTimout);
    }

    statusWDZ = 0; // indicate not zero
    bhmTriggerAfter(watchdogTrigger, watchdogTimout);
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_READ_CB(rdControl) {

    return *(Uns32*)user;
}

PPM_REG_READ_CB(rdStatus) {

    return *(Uns32*)user;
}

PPM_REG_WRITE_CB(wrControl) {
    bport1_ab_dataT tmp;
    tmp.CONTROL.value = data;
    if(tmp.CONTROL.bits.CKEY == CONTROL_CKEY) {
        controlCRV = tmp.CONTROL.bits.CRV;
        controlCLKSEL = tmp.CONTROL.bits.CLKSEL;
        if(PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX "_WRC", "CRV 0x%03x (%d) CLKSEL %d",
                    controlCRV,
                    controlCRV,
                    controlCLKSEL);
        }
    } else {
        if(PSE_DIAG_MEDIUM) {
            bhmMessage("W", PREFIX "_CTRL_KEY", "Incorrect key 0x%08x (0x%08x)",
                    tmp.CONTROL.bits.CKEY, CONTROL_CKEY);
        }
    }
}

PPM_REG_WRITE_CB(wrMode) {
    bport1_ab_dataT tmp;
    tmp.MODE.value = data;
    if(tmp.MODE.bits.ZKEY == MODE_ZEROACCESSKEY) {
        *(Uns32*)user = (*(Uns32*)user & 0xfffffe78) | (data & 0x187);
    } else {
        if(PSE_DIAG_MEDIUM) {
            bhmMessage("W", PREFIX "_MODE_KEY", "Incorrect key 0x%08x (0x%08x)",
                    tmp.MODE.bits.ZKEY, MODE_ZEROACCESSKEY);
        }
    }
}

PPM_REG_WRITE_CB(wrReStart) {
    bport1_ab_dataT tmp;
    tmp.RESTART.value = data;
    if(tmp.RESTART.bits.RSTKEY == RESTART_RESTARTKEY) {
        updateWatchdog();
    } else {
        if(PSE_DIAG_MEDIUM) {
            bhmMessage("W", PREFIX "_RESTART_KEY", "Incorrect key 0x%08x (0x%08x)",
                    tmp.RESTART.bits.RSTKEY, RESTART_RESTARTKEY);
        }
    }
}

PPM_READ_CB(regNoDefinitionRead) {
    Uns32 offset = addr - handles.bport1;
    bhmMessage("W", PREFIX, "No Read Register Defined at offset 0x%04x", offset);
    return 0;
}

PPM_WRITE_CB(regNoDefinitionWrite) {
    Uns32 offset = addr - handles.bport1;
    bhmMessage("W", PREFIX, "No Write Register Defined at offset 0x%04x", offset);
}

bhmThreadHandle thread;

//
// thread only gets launched at next quantum boundary
//
void watchdogThread(void* user) {

    if(PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX "_THRD", "Initialized");
    }

    while(1) {

        bhmWaitEvent(watchdogTrigger);

        if(PSE_DIAG_LOW) {
            bhmMessage("I", PREFIX "_WD_TRIG", "WatchDog Triggered WDEN %d IRQEN %d RSTEN %d",
                    modeWDEN, modeIRQEN, modeRSTEN);
        }

        statusWDZ = 1;  // reached zero

        if(modeWDEN) {
            if(modeRSTEN) {
                ppmWriteNet(handles.rst, 1);  // generate reset signal
                ppmWriteNet(handles.rst, 0);
            }
            if(modeIRQEN)  {
                ppmWriteNet(handles.wdo, 1);  // generate watchdog signal
                double delay = (modeIRQLN * 4) * clockRate;
                bhmWaitDelay(delay);
                ppmWriteNet(handles.wdo, 0);
            }
        }

    }
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();

    bhmDoubleParamValue("pclk", &clockRate); // MHz

    // create enable event
    watchdogTrigger = bhmCreateEvent();

    // create timer thread
    thread = bhmCreateThread(watchdogThread, 0, "watchdogThread", 0);

    if(PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX "_INIT", "Starting Up");
    }

}

PPM_DESTRUCTOR_CB(destructor) {
    bhmDeleteThread(thread);
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}


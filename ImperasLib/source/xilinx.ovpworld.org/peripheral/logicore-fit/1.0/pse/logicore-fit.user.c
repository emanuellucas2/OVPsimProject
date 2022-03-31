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

#include "pse.igen.h"

#define PREFIX "FIT"

bhmThreadHandle thread;

float uSDelay;

static void fitThread()
{
    float usDelayActual = uSDelay;
    for (;;) {
        if(uSDelay) {
            bhmWaitDelay(usDelayActual);    // reduce by one to account for interrupt pulse delay
        } else {
            if (PSE_DIAG_LOW) {
                bhmMessage("W", PREFIX"_DLY", "Delay not initialized at startup, using quantum delay");
            }
            bhmWaitDelay(QUANTUM_DELAY);
        }
        if (PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX"_PLS", "Interrupt (%f)", bhmGetLocalTime());
        }
        ppmWriteNet(handles.Interrupt, 1);  // pulse the interrupt line with a delay
        bhmWaitDelay(1);
        ppmWriteNet(handles.Interrupt, 0);  // ensure the receiver can see it as an edge or level
        usDelayActual = uSDelay - 1;        // account for delay between interrupt
    }
}

//////////////////////////////// Callback stubs ////////////////////////////////


PPM_NET_CB(Reset_Reset) {

    if(value == 0) {
        // Reset active
        if(thread) {
            // destroy thread (stop timer)
            bhmDeleteThread(thread);
        }
    } else {
        if(!thread) {
            // start new thread (start timer)
            // TODO: Not the timer thread will not be started until the next quantum boundary
            //       the initial delay will be longer than expected
            //       this is not expected to be an issue but could be fixed.
            thread = bhmCreateThread(fitThread,
                                     (void*) 0,
                                     "FIT Thread",
                                     0
                                     );
        }
    }
}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    // get the number of clocks after which to generate interrupt
    Uns32 clocks;
    bhmUns32ParamValue("C_NO_CLOCKS", &clocks);

    // get the clock rate in MHz
    Uns32 rate;
    bhmUns32ParamValue("CLOCK_RATE", &rate);

    // calculate the delay (simulation time in micro seconds)
    uSDelay = (float) clocks / (float) rate;
    if (PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX"_CFG", "Configured clocks %d, rate %d MHz, delay between interrupts %f",
                                       clocks, rate, uSDelay);
    }

    // Unused in this model
    Uns32 inaccurary;
    if(bhmUns32ParamValue("C_INACCURACY", &inaccurary) && PSE_DIAG_LOW) {
        bhmMessage("W", PREFIX"_NA", "The parameter C_INACCURACY has no effect in this model");
    }

    // generate the free running thread
    thread = bhmCreateThread(fitThread,
                             (void*) 0,
                             "FIT Thread",
                             0
                             );
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}


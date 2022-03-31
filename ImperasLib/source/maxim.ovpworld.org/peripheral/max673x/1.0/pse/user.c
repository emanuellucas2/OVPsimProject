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

#define PREFIX  "MAX673x"

//////////////////////////////// Callback stubs ////////////////////////////////

bhmThreadHandle thread;

bhmEventHandle watchdogTrigger;

double watchdogTimeout;  // value of current watchdog Timeout

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
            bhmMessage("I", PREFIX "_WD_TRIG", "WatchDog Triggered");
        }

        ppmWriteNet(handles.wdo, 1);

        if(PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX "_WD_TRIG", "LocalTime   : %10.3f\n", bhmGetLocalTime());
        }
    }
}


PPM_NET_CB(wdReset) {

// Delete and create a new thread each time OR (default) reset the trigger event
    // delete timer thread
//    bhmDeleteThread(thread);

    double flt_sim_now = bhmGetCurrentTime();
    double flt_cpu_now = bhmGetLocalTime();

    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_WD_SET", "LocalTime   : %10.3f\n", flt_cpu_now);
    }

    // Event or thread will not be scheduled until next quantum period (bhm Current Time)
    //   Time to next Quantum (flt_sim_now - flt_cpu_now)
    // NOTE: Quantum must ALWAYS be shorter than minimum system delay required!

    double usec_wait = watchdogTimeout - (flt_sim_now - flt_cpu_now);

    if (0 <= usec_wait) {
        if(PSE_DIAG_LOW) {
            bhmMessage("I", PREFIX "_WD_SET", "Wait Delay  : %10.3f usec \n", usec_wait);
        }
        bhmTriggerAfter(watchdogTrigger, usec_wait);

    } else {
        if(PSE_DIAG_LOW) {
            bhmMessage("W", PREFIX "__WD_SET", "Delay falls within current quantum period - trigger");
        }
        bhmTriggerEvent(watchdogTrigger);
    }
}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    double timeoutPeriod;

    bhmDoubleParamValue("InitialPeriod", &timeoutPeriod);       // seconds
    bhmDoubleParamValue("TimeoutPeriod", &watchdogTimeout);     // milli seconds

    // create enable event
    watchdogTrigger = bhmCreateEvent();

    // create timer thread
    thread = bhmCreateThread(watchdogThread, 0, "watchdogThread", 0);

    if(PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX "_INIT", "Watchdog Trigger: %10.3f Milliseconds"
                                        "(Initial Trigger %10.3f Seconds)",
                                         watchdogTimeout, timeoutPeriod);
    }

    bhmTriggerAfter(watchdogTrigger,timeoutPeriod * 1000 * 1000);   // Convert seconds to uSec
    watchdogTimeout = watchdogTimeout * 1000;                       // Convert milli seconds to uSec

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


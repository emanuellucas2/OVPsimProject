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
//                          Sat Jan 19 01:25:49 2013
//
////////////////////////////////////////////////////////////////////////////////

#include <math.h>

#include "pse.igen.h"

#define PREFIX "dw-apb-timer"

typedef struct timerDataS {

    Uns32           frequency;          // Frequency of timer in MHz
    Bool            timerExpired;       // status of timer
    Bool            irqValue;           // status of IRQ line
    bhmThreadHandle threadHandle;       // this timer's thread

    Uns32           startCount;         // Starting counter value
    Flt64           threadDelay;        // duration of timer in micro-seconds
    Flt64           threadStarted;      // bhm time when timer was started.

    Uns64           triggerCount;       // Count expirations seen during simulation

} timerData, *timerDataP;

static timerData timer;

//
// Get masked interrupt status for the timer
//
static Bool maskedInterruptStatus() {
    return timer.timerExpired && !bport1_timer1_data.controlreg.bits.interrupt_mask;
}

//
// Bring the interrupt net up to date
//
static void updateIRQ()
{
    // Assert interrupt when timer has expired and interrupts are not masked
    Bool assert = maskedInterruptStatus();

    if (timer.irqValue != assert) {

        // Status of irq line has changed
        if (PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX, "IRQ=%d", assert);
        }

        timer.irqValue  = assert;

        if (handles.irq) {
            ppmWriteNet(handles.irq, assert);
        }
    }
}

//
// timerThread - wait for time indicated by timer and set timerExpired
//
static void timerThread(void *user) {

    for (;;) {

        timer.threadStarted = bhmGetCurrentTime();

        if (PSE_DIAG_HIGH) {
            bhmMessage(
                "I", PREFIX,
                "timer started at %0.3fuS with delay %0.3fuS",
                timer.threadStarted, timer.threadDelay
            );
        }

        // Wait for timer to expire
        bhmWaitDelay(timer.threadDelay);

        timer.timerExpired = True;
        timer.triggerCount++;

        // Upon expiration new startCount depends on mode
        if ((bport1_timer1_data.controlreg.bits.mode)) {
            /* User defined mode */
            timer.startCount = bport1_timer1_data.loadcount.value;
        } else {
            /* Free running mode */
            timer.startCount = 0xffffffff;
        }

        if (PSE_DIAG_LOW) {
            bhmMessage(
                "I", PREFIX,
                "timer expired at %0.3fuS",
                bhmGetCurrentTime()
            );
        }

        updateIRQ();

    }
}

//
// Stop the thread if active.
//
static void stopThread() {

    if (timer.threadHandle) {
        bhmDeleteThread(timer.threadHandle);
        timer.threadHandle = 0;
        if (PSE_DIAG_LOW)
            bhmMessage("I", PREFIX, "Deleting timer thread\n");
    }

}

//
// start a new one.
//
static void startThread() {

    // Make sure any existing thread is stopped
    stopThread();

    if (PSE_DIAG_LOW)
        bhmMessage("I", PREFIX, "Creating thread: delay:%0.3fuS", timer.threadDelay);

    timer.threadHandle = bhmCreateThread(
        timerThread,
        (void*)0,
        "Timer",
        0
    );

}

//
// reset the timer because something has been re-programmed
//
static void recalibrate() {

    // set starting count and delay in microseconds (Note frequency is in MHz)
    timer.threadDelay = (Flt64) timer.startCount / (Flt64) timer.frequency;

    // Start new thread if enabled
    if (bport1_timer1_data.controlreg.bits.enable) {
        startThread();
    }

}

//////////////////////////////// Callback stubs ////////////////////////////////

//
// Compute current value for the timer based on difference between current time and when
// timer started. Note that bhmGetCurrentTime() always returns the same value within
// a simulation quantum, so the return value can only change across quantums
//
PPM_REG_READ_CB(Readcurrentval) {

    // NOTE: Flt64 result must be *rounded* when converted to Uns32, not
    // *truncated* (the C default)
    Flt64 now      = bhmGetCurrentTime();
    Flt64 elapsed  = now - timer.threadStarted;
    Uns32 ticks    = round(elapsed * timer.frequency);
    Uns32 result   = timer.startCount - ticks;

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "current time %0.3fuS, elapsed ticks %u",
                elapsed, result);
    }

    return result;
}

PPM_REG_READ_CB(Readeoi) {

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Read eoi - interrupt cleared");
    }

    timer.timerExpired = False;

    updateIRQ();

    return 0;

}

PPM_REG_READ_CB(Readintstat) {

    Bool intStatus = maskedInterruptStatus();

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Read intstat - interrupt status: %d", intStatus);
    }

    return intStatus ? 1 : 0;

}

PPM_REG_READ_CB(Readrawintstat) {

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Read rawintstat - raw interrupt status: %d", timer.timerExpired);
    }

    return timer.timerExpired ? 1 : 0;

}

#define CONTROL_WRITE_MASK 0x7

PPM_REG_WRITE_CB(Writecontrolreg) {

    Uns32 oldValue = bport1_timer1_data.controlreg.value;
    Uns32 newValue = (data & CONTROL_WRITE_MASK) | (oldValue & ~CONTROL_WRITE_MASK);

    if (oldValue != newValue) {

        if (PSE_DIAG_LOW) {
           bhmMessage("I", PREFIX, "controlreg changed from 0x%x to 0x%x", oldValue, newValue);
        }

        Bool oldEnable = bport1_timer1_data.controlreg.bits.enable != 0;

        bport1_timer1_data.controlreg.value = newValue;

        // startCount is set to value in loadcount reg when changed from disabled to enabled
        if (bport1_timer1_data.controlreg.bits.enable && !oldEnable) {
            timer.startCount = bport1_timer1_data.loadcount.value;
        }

        // interrupt is reset when timer is disabled
        if (!bport1_timer1_data.controlreg.bits.enable) {
            timer.timerExpired = 0;
        }

        recalibrate();
        updateIRQ();

    }
}

PPM_REG_WRITE_CB(Writeloadcount) {

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Write loadcount <= %u", data);
    }

    bport1_timer1_data.loadcount.value = data;

    if (bport1_timer1_data.controlreg.bits.enable) {

        // Documentation states you should not update loadcount while enabled
        bhmMessage("W", PREFIX, "loadcount register written while timer enabled\n");

        // Let new value take effect immediately
        recalibrate();
        updateIRQ();

    }
}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    // Set input frequency, default set in tcl defintion
    bhmUns32ParamValue("frequency", &timer.frequency);

    if (PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX, "Timer frequency %uMHz", timer.frequency);
    }

    // Make sure initial values are set
    recalibrate();
    updateIRQ();

}

PPM_DESTRUCTOR_CB(destructor) {
    if (PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX, "Timer events:%lld", timer.triggerCount);
    }
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}


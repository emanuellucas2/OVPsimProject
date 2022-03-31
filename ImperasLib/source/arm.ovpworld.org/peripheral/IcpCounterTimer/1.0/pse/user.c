/*
 * PIT
 *
 * Copyright (c) 2003 Fabrice Bellard
 * Copyright (c) 2006 Openedhand Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
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

#include <stdio.h>

#include "peripheral/bhm.h"
#include "pse.igen.h"

#define BPORT1 0
#include "pse.macros.igen.h"

typedef struct timerDataS {
    char            *name;;

    // user registers
    Uns32           control;
    Uns32           int_level;
    Uns32           frequency;      // read-only

    // intermediates
    Uns32           actualFrequency;
    Uns32           limit;

    Uns64           triggerCount;

    bhmThreadHandle threadHandle;   // this timer's thread
    Uns64           threadDelay;    // time this this thread runs again
    Uns64           threadStarted;  // bhm time when timer was started.
    bhmEventHandle  expired;        // user-view event

    struct {
        ppmNetHandle net;
        Bool         current;
    } irq;

} timerData, *timerDataP;

static timerData timers[3];

static const double factor = 10000000;

//
// Bring the output net up to date
//
static void updateIRQ(Uns8 timer)
{
    Bool v = True && (timers[timer].int_level && (timers[timer].control & BPORT1_AB_CONTROL0_IE));

    if (PSE_DIAG_HIGH)
        bhmMessage("I", "PIT", "IRQ=%d", v);

    if (timers[timer].irq.current != v) {
        timers[timer].irq.current  = v;
        if(timers[timer].irq.net) {
            ppmWriteNet(timers[timer].irq.net, v);
        }
    }
}

//
// Thread runs forever unless one-shot mode
//
static void timerThread(void *user) {
    Uns32 t = PTR_TO_UNS32(user);

    do {
        timers[t].threadStarted = bhmGetCurrentTime();
        bhmWaitDelay(timers[t].threadDelay);
        bhmTriggerEvent(timers[t].expired);
        timers[t].int_level = 1;
        timers[t].triggerCount++;
        if (PSE_DIAG_LOW)
            bhmMessage("I", "PIT", "timer %d expired", t);
        updateIRQ(t);
    } while ((timers[t].control & BPORT1_AB_CONTROL0_ONESHOT) == 0);
}

//
// If thread is already active, kill it
//
static void deleteThread(Uns32 t) {

    if (timers[t].threadHandle) {

        bhmDeleteThread(timers[t].threadHandle);
        timers[t].threadHandle = 0;

        if (PSE_DIAG_LOW)
            bhmMessage("I", "PIT", "Deleting thread %d\n", t);
    }
}

//
// Create a new timer thread
//
static void createThread(Uns32 t) {

    if (PSE_DIAG_LOW)
        bhmMessage("I", "PIT", "Creating thread:%s delay:%llduS", timers[t].name, timers[t].threadDelay);

    timers[t].threadHandle = bhmCreateThread(
        timerThread,
        UNS32_TO_PTR(t),
        timers[t].name,
        0
    );
}

//
// If thread is already active, kill it, then start a new one.
//
static void startThread(Uns32 t) {
    deleteThread(t);
    createThread(t);
}

//
// reset the timer because something has been re-programmed
//
static void recalibrate(Uns8 t, Bool reload) {
    Uns32 limit;

    if ((timers[t].control & BPORT1_AB_CONTROL0_PERIODIC) == 0) {
        /* Free running.  */
        if (timers[t].control & BPORT1_AB_CONTROL0_M32BIT)
            limit = 0xffffffff;
        else
            limit = 0xffff;
    } else {
        /* Periodic.  */
        limit = timers[t].limit;
    }
    double delay = limit * factor / timers[t].actualFrequency;
    timers[t].threadDelay = delay;

    if (timers[t].control & BPORT1_AB_CONTROL0_ENABLE) {
        startThread(t);
    }
}

//
// Callbacks
//
PPM_REG_READ_CB(readLimit) {
    Uns8 t = PTR_TO_UNS32(user);
    return timers[t].limit;
}

PPM_REG_READ_CB(readMIS) {
    Uns8 t = PTR_TO_UNS32(user);
    if (timers[t].control && BPORT1_AB_CONTROL0_IE)
        return 0;
    return timers[t].int_level;
}

//
// I think this returns number of counts till expiry
//
PPM_REG_READ_CB(readValue) {
    Uns8  t     = PTR_TO_UNS32(user);
    Uns64 now   = bhmGetCurrentTime();
    Uns64 diff  = timers[t].threadStarted + timers[t].threadDelay - now;
    return diff * timers[t].actualFrequency / factor;
}

PPM_REG_READ_CB(readControl) {
    Uns8 timer = PTR_TO_UNS32(user);
    return timers[timer].control;
}


PPM_REG_WRITE_CB(writeBG) {
    Uns8 t = PTR_TO_UNS32(user);
    timers[t].limit = data;
    recalibrate(t, 0);
    updateIRQ(t);
}

PPM_REG_WRITE_CB(writeClear) {
    Uns8 t = PTR_TO_UNS32(user);
    timers[t].int_level = 0;
    updateIRQ(t);
}

PPM_REG_WRITE_CB(writeControl) {
    Uns8 t = PTR_TO_UNS32(user);

    timers[t].control = data;
    Uns32 freq = timers[t].frequency;

    switch ((data >> 2) & 3) {
        case 1: freq >>= 4; break;
        case 2: freq >>= 8; break;
    }
    timers[t].actualFrequency = freq;
    if (PSE_DIAG_LOW)
        bhmMessage("I", "PIT", "WriteControl %d: Actual freq = %d", t, freq);
    recalibrate(t, 0);

    updateIRQ(t); // TODO: is this needed?
}

PPM_REG_WRITE_CB(writeLimit) {
    Uns8 t = PTR_TO_UNS32(user);
    timers[t].limit = data;
    recalibrate(t, 1);
    updateIRQ(t);
}

PPM_REG_WRITE_CB(writeValue) {
    bhmMessage("W", "PIT", "writing read-only timer register");
}


PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    timers[0].irq.net    = handles.irq0;
    timers[1].irq.net    = handles.irq1;
    timers[2].irq.net    = handles.irq2;

    timers[0].frequency  = 400000000;  // 40.0MHz (these numbers need to be 10x what I expected)
    timers[1].frequency  = 10000000;   // 1.0MHz
    timers[2].frequency  = 10000000;   // 1.0MHz

    timers[0].expired = bhmCreateNamedEvent("T0", "Timer0 has expired");
    timers[1].expired = bhmCreateNamedEvent("T1", "Timer1 has expired");
    timers[2].expired = bhmCreateNamedEvent("T2", "Timer2 has expired");

    timers[0].name = "tt0";
    timers[1].name = "tt1";
    timers[2].name = "tt2";

    int t;
    for(t = 0; t < 3; t++) {
        timers[t].control      = BPORT1_AB_CONTROL0_IE;
        timers[t].triggerCount = 0;
    }
}

PPM_DESTRUCTOR_CB(destructor) {
    if (PSE_DIAG_LOW) {
        int t;
        for(t = 0; t < 3; t++) {
            bhmMessage("I", "PIT", "Timer %d  events:%lld", t, timers[t].triggerCount);
        }
    }
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {

    Uns32 t;

    switch(phase) {

        case PPM_PRE_SAVE_RESTORE: {

            // first phase: delete any currently-active threads
            for(t=0; t<3; t++) {
                deleteThread(t);
            }

            break;
        }

        case PPM_POST_SAVE_RESTORE: {

            // second phase: create required threads
            for(t=0; t<3; t++) {
                if(timers[t].threadHandle) {
                    createThread(t);
                }
            }

            break;
        }
    }
}


/*
 * MC148818 RTC Emulator.
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


#include "peripheral/ppm.h"
#include "peripheral/bhm.h"
#include "peripheral/impTypes.h"

#include "pse.igen.h"

#define mr    bport1_ab_data.mr.value
#define lr    bport1_ab_data.lr.value
#define cr    bport1_ab_data.cr.value
#define im    bport1_ab_data.im.value
#define is    bport1_ab_data.is.value

static void interrupt(void);


static Uns32 ticks_per_sec = 10000000;
static Uns32 tick_offset   = 1293840000;  // Set inital date/time to 2011-01-01 00:00:00

static bhmThreadHandle timerThreadHandle = 0;
static Uns64 threadDelay;

static bhmEventHandle timerFired;

static void timerThread(void *user) {
    bhmWaitDelay(threadDelay);
    interrupt();
    // Cease to exist.
}

static void stopTimer(void) {
    if (timerThreadHandle) {
        bhmDeleteThread(timerThreadHandle);
        timerThreadHandle = 0;
    }
}

static void startTimer(Uns64 delay) {
    stopTimer();
    threadDelay = delay;
    bhmMessage("I", "PL031_ST", "Start timer for %lldus", delay);
    timerThreadHandle = bhmCreateThread(timerThread, 0, "timer", 0);
}

static void update(void)
{
    static Bool current = False;
    Bool new = (is & im) && True;
    if (new != current) {
        current = new;
        ppmWriteNet(handles.irq, current);
    }
}

static void interrupt(void)
{
    im = 1;
    bhmTriggerEvent(timerFired);
    update();
}

static Uns32 get_count(void)
{
    return tick_offset + (bhmGetCurrentTime() / ticks_per_sec);
}

static void set_alarm(void)
{
    Uns64  now   = bhmGetCurrentTime();
    Uns32  ticks = tick_offset + now / ticks_per_sec;

    /* The timer wraps around.  This subtraction also wraps in the same way,
       and gives correct results when alarm < now_ticks.  */
    ticks = mr - ticks;
    bhmMessage("I", "PL031_ALM", "Alarm set in %ud ticks", ticks);
    if (ticks == 0) {
        stopTimer();
        interrupt();
    } else {
        startTimer(now + ((Uns64)ticks * ticks_per_sec));
    }
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_READ_CB(readDR) {
    return get_count();
}

PPM_REG_READ_CB(readCR) {
    // always enabled
    return 1;
}

PPM_NBYTE_READ_CB(readID) {
    static const unsigned char id[] = {
        0x31, 0x10, 0x14, 0x00,         // Device ID
        0x0d, 0xf0, 0x05, 0xb1          // Cell   ID
    };

    Uns32 reg  = (offset-0xfe0)/0x4;
    *(Uns32*)data = id[reg];
}

PPM_REG_READ_CB(readMIS) {
    return is & im;
}


PPM_REG_WRITE_CB(writeICR) {
    is = 0;
    update();
}

PPM_REG_WRITE_CB(writeCR) {
    // No action
}

PPM_REG_WRITE_CB(writeIM) {
    im = data & 1;
    update();
}

PPM_REG_WRITE_CB(writeLR) {
    tick_offset += data - get_count();
}

PPM_REG_WRITE_CB(writeMR) {
    mr = data;
    set_alarm();
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();
    timerFired = bhmCreateNamedEvent("Fired", "Timer has expired");
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}


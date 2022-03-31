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

#define PREFIX "GPT"

typedef struct threadInfoS {
    double          timeout;            // The BHM Microsecond time
    double          start;              // BHM time when timer started
    Uns32           target;             // target count value
    Uns32           count;              // current count value
    Uns32           match;              // record the match register (if match)
    Bool            active;             // timer is running
    Bool            freeRun;            // free running
    bhmThreadHandle handle;             // timer thread handle
} threadInfoT;

threadInfoT tinfo;

// Available clock rate in MHz
Uns32 clockRate;
Uns32 clockRateParam;       // store parameter value
// CR CLKSRC definitions
#define CLKSRC_NO   0
#define CLKSRC_PCLK 1
#define CLKSRC_HIGH 2
#define CLKSRC_EXT  3
#define CLKSRC_LOW  4
#define CLKSRC_24M  5
// clock rate definitions
#define MHZ      1000000
#define CLK_24M 24000000
#define CLK_LOW    32000

// bits cleared on a SW reset
#define GPT_CR_SWRESETMASK 0xffffffd0

//
// Write the Interrupt if the value changes
//
void interruptSet(Uns32 value) {
    static Uns32 interrupt = 0;

    // only set interrupt if not already active
    if (interrupt != value) {
        interrupt = value;
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Setting int=%u (%e)\n", interrupt, bhmGetCurrentTime());

        ppmWriteNet(handles.interrupt, interrupt);
    }
}

#define INT_ROLLOVER  0x20
#define INT_INPCAPT2  0x10
#define INT_INPCAPT1  0x08
#define INT_OUTPCAPT3 0x04
#define INT_OUTPCAPT2 0x02
#define INT_OUTPCAPT1 0x01

void updateStatus(Uns32 intMask) {

    if(intMask) {
        // mask in new events
        bport1_ab_data.GPT_SR.value |= intMask;
    }

    // generate an interrupt if bit enabled
    if (bport1_ab_data.GPT_SR.value & bport1_ab_data.GPT_IR.value) {
        interruptSet(1);
    } else {
        // clear interrupt
        interruptSet(0);
    }
}

Uns32 getPrescale() {
    Uns32 prescale = 1;

    // TODO: select clock and prescale
    if(bport1_ab_data.GPT_CR.bits.CLKSRC == CLKSRC_24M) {
        // 24M clock
        prescale = (bport1_ab_data.GPT_PR.bits.PRESCALER24M + 1);
    } else {
        // selected clock
        prescale = (bport1_ab_data.GPT_PR.bits.PRESCALER + 1);
    }

    return prescale;
}

Uns32 getCountNow() {

    double now     = bhmGetLocalTime(); // current time

    if(tinfo.active) {
        double start   = tinfo.start;       // time when timer thread started
        Uns32  count   = tinfo.count;       // count value when timer thread started

        // a timer was started at start - so counter now depends how much time elapsed
        double timeChange = (now - start);
        // ticks per second
        double ticksPS = (double)clockRate / (double)getPrescale();
        // convert using Uns64 result to avoid overflow
        Uns64  ticks64 = (Uns64)(timeChange * (ticksPS / (double)MHZ));
        // update from the initial count value
        Uns64  value64 = ticks64 + count;
        Uns32  value   = value64 & 0xffffffff;   // 32-bit counter

        if (PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX, "Clock active : "
                                    "now %10.3f uS start %10.3f uS "
                                    "change %10.3f uS %u Count %u (0x08%x)",
                                    now, start, timeChange, (Uns32)ticks64, value, value);
        return value;
    } else {

        if (PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX, "Clock not active : "
                                    "now %10.3f Count %u (0x08%x)",
                                    now,
                                    bport1_ab_data.GPT_CNT.value,
                                    bport1_ab_data.GPT_CNT.value);
        // return the current counter value
        return bport1_ab_data.GPT_CNT.value;
    }
}

//
// Check the Compare regsiters to see which will be hit first
//
Uns32 getTarget (Uns32 current) {

    // default indicates counting to rollover
    tinfo.match  = 0;
    tinfo.target = -1;
    if((current < bport1_ab_data.GPT_OCR1.value ) &&
       (bport1_ab_data.GPT_OCR1.value < tinfo.target)) {
        tinfo.target = bport1_ab_data.GPT_OCR1.value;
        tinfo.match  = 1;
    }
    if((current < bport1_ab_data.GPT_OCR2.value ) &&
       (bport1_ab_data.GPT_OCR2.value < tinfo.target)) {
        tinfo.target = bport1_ab_data.GPT_OCR2.value;
        tinfo.match  = 2;
    }
    if((current < bport1_ab_data.GPT_OCR3.value ) &&
       (bport1_ab_data.GPT_OCR3.value < tinfo.target)) {
        tinfo.target = bport1_ab_data.GPT_OCR3.value;
        tinfo.match  = 3;
    }

    if (PSE_DIAG_HIGH) {
        if(tinfo.match == 0) {
            // run to overflow
            bhmMessage("I", PREFIX, "Timer target %u (overflow)",
                tinfo.target);
        } else {
            // run to OCR setting
            bhmMessage("I", PREFIX, "Timer target OCR%u %u",
                tinfo.match, tinfo.target);
        }
    }

    return tinfo.target;
}

double getTimeout (Uns32 current) {

    Uns32 target   = getTarget(current);
    Uns32 ticks    = target - current;

    double timeout = 0;     // uS period

    if(ticks > 0) {

        double ticksPS = (double)clockRate / (double)getPrescale();
        timeout = (double)(ticks) / (ticksPS / (double)MHZ);
    }
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Timer timeout %10.3f uS target %u current %u "
                                "clock %u Hz prescale %u",
                                timeout, target, current,
                                clockRate, getPrescale());
    }

    return timeout;
}

void timerExpired() {

    // update register value
    bport1_ab_data.GPT_CNT.value = getCountNow();

    switch(tinfo.match) {
        case 0:
            // rollover
            updateStatus(INT_ROLLOVER);
            bport1_ab_data.GPT_CNT.value = 0;
            break;
        case 1: // OCR1
        case 2: // OCR2
        case 3: // OCR3
            // check to see if we are free running or restart
            if(!bport1_ab_data.GPT_CR.bits.FRR) {
                // restart so reset count register
                bport1_ab_data.GPT_CNT.value = 0;
            }
            updateStatus(1<<(tinfo.match-1));
            break;
        default:
            bhmMessage("W", PREFIX, "Unexpected match expiration reason %d", tinfo.match);
            break;
    }
}

void timerThread(void *user) {

    do {

        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX,
                "Start Timer_Begin at %10.3f uS "
                "timeout %10.3f uS",
                     tinfo.start,
                     tinfo.timeout);

        // if no timeout set stop loop
        if(!tinfo.timeout) {
            if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX,"No timeout set - abort timer thread");
            break;
        }

        bhmWaitDelay(tinfo.timeout);

        double now = bhmGetCurrentTime();
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX,
                "End Timer Expired at %10.3f uS",now);

        timerExpired();

        tinfo.count   = bport1_ab_data.GPT_CNT.value;       // current count
        tinfo.timeout = getTimeout(tinfo.count);            // calculate next timeout
        tinfo.start   = now;                                // record start time

        // TODO: Check that we keep going if interval or freerun

    } while (bport1_ab_data.GPT_CR.bits.EN && tinfo.timeout);

    // complete
    if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Complete Timer Thread");
}

void timerStop() {

    static int cnt=0;
    if (tinfo.active || tinfo.handle) {
        if (PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX, "Timer Stop");
        cnt++;
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Delete Timer Thread cnt=%u", cnt);
        bhmDeleteThread(tinfo.handle);
        tinfo.handle = 0;
        tinfo.active = False;
    }
}

void timerStart() {

    tinfo.start = bhmGetLocalTime();            // get BHM time at which we start
    tinfo.count = bport1_ab_data.GPT_CNT.value; // record register value when started

    if (PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX, "Timer Start");

    tinfo.active = True;

    double timeout = getTimeout(tinfo.count);
    double nextQ   = bhmGetCurrentTime();

    // The initial timeout will not be set until next quantum at the bhmCurrentTime
    double toNextQuantum =  nextQ - tinfo.start;

    if (timeout > toNextQuantum) {
        if(toNextQuantum > 0)
            tinfo.timeout = timeout - toNextQuantum;
        else
            tinfo.timeout = timeout;

        if (PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX, "Create Timer Thread tinfo.timeout %10.3f uS "
                                    "(now %10.3f uS next %10.3f uS requested %10.3f uS)",
                                    tinfo.timeout,
                                    tinfo.start, bhmGetCurrentTime(), timeout);
        }

    } else {
        tinfo.timeout = 1;

        bhmMessage("W", PREFIX, "Create Timer Thread Not possible "
                                "Time now %10.3f uS "
                                "required timeout %10.3f uS "
                                "min possible %10.3f uS "
                                "to next Quantum at %10.3f uS"
                                ": Timeout is before next Quantum : "
                                "You should reduce Quantum size",
                                tinfo.start, timeout, toNextQuantum, nextQ);
    }
    tinfo.handle = bhmCreateThread(timerThread, 0, "Timer Thread", 0);
}

void updateTimer() {

    if (!bport1_ab_data.GPT_CR.bits.EN) {
        bport1_ab_data.GPT_CNT.value = getCountNow();
        timerStop();
    } else {
        timerStop();
        timerStart();
    }
}
//////////////////////////////// Callback stubs ////////////////////////////////

PPM_READ_CB(regNoDefinitionRead) {
    Uns32 offset = addr - handles.bport1;
    bhmMessage("W", PREFIX, "No Read Register Defined at offset 0x%04x", offset);
    return 0;
}

PPM_WRITE_CB(regNoDefinitionWrite) {
    Uns32 offset = addr - handles.bport1;
    bhmMessage("W", PREFIX, "No Write Register Defined at offset 0x%04x", offset);
}

PPM_REG_WRITE_CB(WriteGPT_CR) {

    Uns32 current = *(Uns32*)user;
    Uns32 new     = (*(Uns32*)user & 0x7800) | (data & 0xffff87ff);

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_WCR", "%10.3f uS: CR: Write 0x%x",
                bhmGetLocalTime(), new);
    }

    if (current != new) {
        *(Uns32*)user = new;

        if(!(current & 1) && bport1_ab_data.GPT_CR.bits.EN) {
            // Enabled, if ENMOD set then re-start from zero
            if(bport1_ab_data.GPT_CR.bits.ENMOD) {
                bport1_ab_data.GPT_CNT.value = 0;
            }
        }

        if(bport1_ab_data.GPT_CR.bits.SWR) {
            if(PSE_DIAG_HIGH)
                bhmMessage("I", PREFIX, "CR: Software Reset");

            bport1_ab_data.GPT_CR.value &= GPT_CR_SWRESETMASK;
            bport1_ab_data.GPT_CR.bits.SWR = 0;
        }

        // select the clock source
        if(bport1_ab_data.GPT_CR.bits.CLKSRC == CLKSRC_24M) {
            // 24Mhz
            clockRate = CLK_24M;
        } else if(bport1_ab_data.GPT_CR.bits.CLKSRC == CLKSRC_LOW) {
            // 32KHz
            clockRate = CLK_LOW;
        } else {
            // for others take the value from the parameter (default 33MHz)
            clockRate = clockRateParam;
        }

        updateTimer();
    }

    if(PSE_DIAG_MEDIUM) {
        bhmMessage("I", PREFIX, "CR: "
                    "OM3 %u OM2 %u OM1 %u "
                    "IM2 %u IM1 %u FRR %u CLKSRC %u ENMOD %u EN %u",
                    bport1_ab_data.GPT_CR.bits.OM3,
                    bport1_ab_data.GPT_CR.bits.OM2,
                    bport1_ab_data.GPT_CR.bits.OM1,
                    bport1_ab_data.GPT_CR.bits.IM2,
                    bport1_ab_data.GPT_CR.bits.IM1,
                    bport1_ab_data.GPT_CR.bits.FRR,
                    bport1_ab_data.GPT_CR.bits.CLKSRC,
                    bport1_ab_data.GPT_CR.bits.ENMOD,
                    bport1_ab_data.GPT_CR.bits.EN);
    }

}

PPM_REG_WRITE_CB(WriteGPT_IR) {
    *(Uns32*)user = (*(Uns32*)user & 0xffffffc0) | (data & 0x3f);
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_WIR", "%10.3f uS: IR: Write 0x%x",
                bhmGetLocalTime(), *(Uns32*)user);
    }
    updateStatus(0);
}

PPM_REG_WRITE_CB(WriteGPT_OCR1) {
    *(Uns32*)user = data;
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_WOCR1", "%10.3f uS: Write OCR1 %u",
                bhmGetLocalTime(), *(Uns32*)user);
    }
    updateTimer();
}

PPM_REG_WRITE_CB(WriteGPT_OCR2) {
    *(Uns32*)user = data;
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_WOCR2", "%10.3f uS: Write OCR2 %u",
                bhmGetLocalTime(), *(Uns32*)user);
    }
    updateTimer();
}

PPM_REG_WRITE_CB(WriteGPT_OCR3) {
    *(Uns32*)user = data;
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_WOCR3", "%10.3f uS: Write OCR3 %u",
                bhmGetLocalTime(), *(Uns32*)user);
    }
    updateTimer();
}

PPM_REG_WRITE_CB(WriteGPT_PR) {
    *(Uns32*)user = (*(Uns32*)user & 0xffff0000) | (data & 0xffff);
    if(PSE_DIAG_MEDIUM) {
        bhmMessage("I", PREFIX, "%10.3f uS: PR: SC24M %u SC %u",
                    bhmGetLocalTime(),
                    bport1_ab_data.GPT_PR.bits.PRESCALER24M,
                    bport1_ab_data.GPT_PR.bits.PRESCALER);
    }
    updateTimer();
}

PPM_REG_READ_CB(ReadGPT_CNT) {
    *(Uns32*)user = getCountNow();
    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX, "%10.3f uS: CNT: count %u",
                bhmGetLocalTime(), *(Uns32*)user);
    return *(Uns32*)user;
}

PPM_NET_CB(inputCapure) {
    static ppmNetValue lastValue = 0;
    // Only on a rising edge
    if((lastValue == 0) && (value == 1)) {
        lastValue = value;
        Uns32 channel = *(Uns32*) userData;
        Uns32 now = getCountNow();

        if(PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX, "Capture: channel %u count %u", channel, now);

        switch (channel) {
        case 1:
            bport1_ab_data.GPT_ICR1.value = now;
            break;
        case 2:
            bport1_ab_data.GPT_ICR2.value = now;
            break;
        default:
            bhmMessage("W", PREFIX, "Capture: Incorrect channel (%u)", channel);
            break;
        }
    }
}

PPM_REG_WRITE_CB(WriteGPT_SR) {
    Uns32 mask = data & 0x3f;
    Uns32 current = *(Uns32*)user;

    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX, "SR: clear 0x%x", mask);

    // clear bits set
    *(Uns32*)user = current & ~mask;
    updateStatus(0);
}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    // Setup the input clock rate
    bhmUns32ParamValue("clk", &clockRateParam);
    clockRate = clockRateParam;
}

PPM_DESTRUCTOR_CB(destructor) {
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}


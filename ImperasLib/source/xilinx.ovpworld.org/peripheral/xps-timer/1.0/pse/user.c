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
//                          Fri Jan  6 10:06:43 2012
//
////////////////////////////////////////////////////////////////////////////////

#include <string.h>

#include "pse.igen.h"
#include "bus.c.h"

#define PREFIX "xps-timer"

struct {
    Uns32 Interrupt;
    Uns32 Int[2];
} state;

//
// Shortcut for loading the TCSR[0:1] registers
//
typedef struct TCSRS {
    union {
        Uns32 value;
        struct {
            unsigned MDT   : 1;
            unsigned UDT   : 1;
            unsigned GENT  : 1;
            unsigned CAPT  : 1;
            unsigned ARHT  : 1;
            unsigned LOAD  : 1;
            unsigned ENIT  : 1;
            unsigned ENT   : 1;
            unsigned TINT  : 1;
            unsigned PWMA  : 1;
            unsigned ENALL : 1;
        } bits;
    };
} TCSRT;

typedef struct threadInfoS {
    bhmThreadHandle handle;
    Uns64 timeout;
    double start;           // time when start was requested
} threadInfoT;
threadInfoT tinfo[2];

void interruptEvaluate();
void interruptSet(Uns32 value);

void timerEnable(Uns32 tmr, Bool changed);
void timerStart(Uns32 tmr, Uns32 timeout);
void timerStop(Uns32 tmr);

double freq_mhz;    // the frequency of operation

// processor interface endian (big by default)
Bool bigEndian = True;

//
// Write the Interrupt if the value changes
//
void interruptSet(Uns32 value) {
    if (state.Interrupt != value) {
        state.Interrupt = value;
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Setting Interrupt=%d %e\n", state.Interrupt, bhmGetCurrentTime());
        ppmWriteNet(handles.Interrupt, state.Interrupt);
    }
}

void getTmrStatus(TCSRT *TCSR, Uns32 tmr) {
    if (tmr==0) {
        TCSR->value = plb_REG_data.TCSR0.value;
    } else {
        TCSR->value = plb_REG_data.TCSR1.value;
    }
}

void putTmrStatus(TCSRT *TCSR, Uns32 tmr) {
    if (tmr==0) {
        plb_REG_data.TCSR0.value = TCSR->value;
    } else {
        plb_REG_data.TCSR1.value = TCSR->value;
    }
}

void interruptEvaluate()
{
    Uns32 irq = 0;

    irq |= plb_REG_data.TCSR0.bits.T0INT && plb_REG_data.TCSR0.bits.ENIT0;
    irq |= plb_REG_data.TCSR1.bits.T1INT && plb_REG_data.TCSR1.bits.ENIT1;

    if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "interruptEvaluate irq=%d\n", irq);

    if (irq) {
        //
        // Generate timeout interrupt
        //
        interruptSet(1);
    } else if(ppmReadNet(handles.Interrupt)) {
        // clear interrupt (if set)
        interruptSet(0);
    }
}

void timerExpired(Uns32 tmr) {
    if (PSE_DIAG_HIGH) {
        double now = bhmGetCurrentTime();
        bhmMessage("I", PREFIX, "timerExpired tmr=%d time=%e\n", tmr, now);
    }

    TCSRT TCSR;
    getTmrStatus(&TCSR, tmr);

    //
    // Interrupt is active
    //
    TCSR.bits.TINT = 1;
    putTmrStatus(&TCSR, tmr);
    interruptEvaluate();
}

Uns32 getTimeout (Uns32 tmr) {
    Uns32 count;
    Uns32 TLR = (tmr == 0) ? plb_REG_data.TLR0.value : plb_REG_data.TLR1.value;

    TCSRT TCSR;
    getTmrStatus(&TCSR, tmr);

    if (TCSR.bits.UDT) {
        // Counting up
        count = TLR;
    } else {
        // Counting down
        count = ~0 - TLR;
    }
    return count;
}

void timerEnable(Uns32 tmr, Bool changed) {
    TCSRT TCSR;
    getTmrStatus(&TCSR, tmr);

    //
    // Some asserts
    //
    if (TCSR.bits.MDT) {
        bhmMessage("F", PREFIX, "Unsupported Mode Capture");
    }
    if (TCSR.bits.PWMA) {
        bhmMessage("F", PREFIX, "Unsupported Mode PWM");
    }

    //
    // Now setup the timer
    //
    if (changed || !TCSR.bits.ARHT) {
        timerStop(tmr);
        timerStart(tmr, getTimeout(tmr));
    }
}

void timerThread(void *user) {
    Uns32 tmr = PTR_TO_UNS32(user);
    TCSRT TCSR;
    getTmrStatus(&TCSR, tmr);

    double now    = bhmGetCurrentTime();
    double start  = tinfo[tmr].start;
    Uns64 timeout = tinfo[tmr].timeout;

    // check thread delayed start and try to account for the delay
    if((start<now) && ((now-start) < timeout)) {
        timeout -= (now-start);                       // reduce initial timeout by ammount of delayed start
    }

    do {

        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Start Timer_%d Request at %e Begin at %e timeout=%lld US", tmr, start, now, timeout);

        bhmWaitDelay(timeout);

        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "End Timer_%d Expired at %e", tmr, bhmGetCurrentTime());

        timerExpired(tmr);

        tinfo[tmr].start = bhmGetCurrentTime(); // record new start time if free running
        timeout          = tinfo[tmr].timeout;

        if(TCSR.bits.ARHT && PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX, "Re-Start Timer_%d at %e", tmr, tinfo[tmr].start);

    } while (TCSR.bits.ARHT);

    if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Thread Complete Timer_%d at %e", tmr, tinfo[tmr].start);
}

void timerStop(Uns32 tmr) {
    static int cnt=0;
    if (tinfo[tmr].handle) {
        cnt++;
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Delete Timer_%d Thread cnt=%d", tmr, cnt);
        bhmDeleteThread(tinfo[tmr].handle);
        tinfo[tmr].handle = 0;
    }
}

void timerStart(Uns32 tmr, Uns32 timeout) {
    static int cnt=0;
    const char *tn = tmr==0 ? "timer0" : "timer1";

    tinfo[tmr].timeout = timeout / freq_mhz;
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "tinfo[%d].timeout = %lld", tmr, tinfo[tmr].timeout);
        bhmMessage("I", PREFIX, "Create Timer_%d Thread cnt=%d", tmr, cnt);
    }

    cnt++;
    if (tinfo[tmr].handle) {
        bhmMessage("W", PREFIX, "Timer_%d Thread still active", tmr);
    }
    tinfo[tmr].start  = bhmGetLocalTime(); // record when start was requested
    tinfo[tmr].handle = bhmCreateThread(timerThread, UNS32_TO_PTR(tmr), tn, 0);
}

Uns32 clocksRemaining (Uns32 tmr) {
    TCSRT TCSR;
    getTmrStatus(&TCSR, tmr);

    double now     = bhmGetLocalTime();
    double start   = tinfo[tmr].start;
    double timeout = tinfo[tmr].timeout;
    double remain;
    
    // convert using Uns64 result to avoid overflow
    remain = (timeout - (now - start)) * freq_mhz;
    Uns64 value64 = remain;

    return value64;
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_READ_CB(ReadTCR0) {

    if (plb_REG_data.TCSR0.bits.ENT0) {
        Uns32 remain = clocksRemaining(0);

        if (!plb_REG_data.TCSR0.bits.UDT0) {
            remain = ~remain;
        }

        plb_REG_data.TCR0.value = remain;
    }

    if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Read TCR0=0x%08x", plb_REG_data.TCR0.value);

    return GETBE(bigEndian,plb_REG_data.TCR0.value);
}

PPM_REG_READ_CB(ReadTCR1) {
    if (plb_REG_data.TCSR1.bits.ENT1) {
        Uns32 remain = clocksRemaining(1);

        if (!plb_REG_data.TCSR1.bits.UDT1) {
            remain = ~remain;
        }

        plb_REG_data.TCR1.value = remain;
    }

    if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Read TCR1=0x%08x", plb_REG_data.TCR1.value);

    return GETBE(bigEndian,plb_REG_data.TCR1.value);
}

PPM_REG_READ_CB(ReadTCSR0) {
    if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Read TCSR0=0x%08x", plb_REG_data.TCSR0.value);
    return GETBE(bigEndian,plb_REG_data.TCSR0.value);
}

PPM_REG_READ_CB(ReadTCSR1) {
    if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Read TCSR1=0x%08x", plb_REG_data.TCSR1.value);
    return GETBE(bigEndian,plb_REG_data.TCSR1.value);
}

PPM_REG_READ_CB(ReadTLR0) {
    if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Read TLR0=0x%08x", plb_REG_data.TLR0.value);
    return GETBE(bigEndian,plb_REG_data.TLR0.value);
}

PPM_REG_READ_CB(ReadTLR1) {
    if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Read TLR1=0x%08x", plb_REG_data.TLR1.value);
    return GETBE(bigEndian,plb_REG_data.TLR1.value);
}


void WriteTCSR (void *addr, Uns32 bytes, void *user, Uns32 data) {
    Uns32 tmr = (PTR_TO_UNS32(user)) >> 4;

    TCSRT TCSRin, TCSRcurrent;
    TCSRin.value = GETLE(bigEndian,data);
    getTmrStatus(&TCSRcurrent, tmr);

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Write TCSR%d=0x%08x", tmr, TCSRin.value);
        bhmMessage("I", PREFIX, "    TCSR%d %s\n",                 tmr, TCSRin.bits.MDT   ? "Capture" : "Generate");
        bhmMessage("I", PREFIX, "    TCSR%d %s\n",                 tmr, TCSRin.bits.UDT   ? "Down"    : "Up");
        bhmMessage("I", PREFIX, "    TCSR%d %s\n",                 tmr, TCSRin.bits.GENT  ? "External": "Internal");
        bhmMessage("I", PREFIX, "    TCSR%d %s Capture\n",         tmr, TCSRin.bits.CAPT  ? "Enable"  : "Disable");
        bhmMessage("I", PREFIX, "    TCSR%d %s Counter/Capture\n", tmr, TCSRin.bits.ARHT  ? "Reload"  : "Hold");
        bhmMessage("I", PREFIX, "    TCSR%d %s Timer\n",           tmr, TCSRin.bits.LOAD  ? "Load"    : "No Load");
        bhmMessage("I", PREFIX, "    TCSR%d %s Interrupt\n",       tmr, TCSRin.bits.ENIT  ? "Enable"  : "Disable");
        bhmMessage("I", PREFIX, "    TCSR%d %s Timer\n",           tmr, TCSRin.bits.ENT   ? "Enable"  : "Disable");
        bhmMessage("I", PREFIX, "    TCSR%d %s T0INT\n",           tmr, TCSRin.bits.TINT  ? "Clear"   : "No Change");
        bhmMessage("I", PREFIX, "    TCSR%d %s PWM\n",             tmr, TCSRin.bits.PWMA  ? "Enable"  : "Disable");
        bhmMessage("I", PREFIX, "    TCSR%d %s All Timers\n",      tmr, TCSRin.bits.ENALL ? "Enable"  : "No Effect");
    }

    if (TCSRin.bits.TINT) {
        //
        // Clear The interrupt if active
        //
        TCSRin.bits.TINT = 0;
    } else {
        //
        // Otherwise unchanged
        //
        TCSRin.bits.TINT = TCSRcurrent.bits.TINT;
    }

    //
    // Put to timer channel status
    //
    putTmrStatus(&TCSRin, tmr);

    // See if interrupt still active
    interruptEvaluate();

    //
    // Enable All Timers
    //
    plb_REG_data.TCSR0.bits.ENALL = TCSRin.bits.ENALL;
    plb_REG_data.TCSR1.bits.ENALL = TCSRin.bits.ENALL;
    if (TCSRin.bits.ENALL) {

        plb_REG_data.TCSR0.bits.ENT0  = 1;
        plb_REG_data.TCSR1.bits.ENT1  = 1;

        //
        // Enable All Timers
        //
        timerEnable(0, True);
        timerEnable(1, True);

    } else if (TCSRin.bits.ENT) {

        //
        // Enable Timer
        //
        timerEnable(tmr, !TCSRcurrent.bits.ENT);
    }

    if (TCSRin.bits.LOAD) {
        //
        // Load Timer
        //
        if (tmr==0) {
            plb_REG_data.TCR0.value = plb_REG_data.TLR0.value;
        } else {
            plb_REG_data.TCR1.value = plb_REG_data.TLR1.value;
        }
    }

}

PPM_REG_WRITE_CB(WriteTCSR0) {
    WriteTCSR(addr, bytes, user, data);
    if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Write TCSR0=0x%08x", plb_REG_data.TCSR0.value);
}

PPM_REG_WRITE_CB(WriteTCSR1) {
    WriteTCSR(addr, bytes, user, data);
    if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Write TCSR1=0x%08x", plb_REG_data.TCSR1.value);
}

PPM_REG_WRITE_CB(WriteTLR0) {
    Uns32 d = GETLE(bigEndian,data);
    plb_REG_data.TLR0.value = d;
    if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Write TLR0=0x%08x", plb_REG_data.TLR0.value);
}

PPM_REG_WRITE_CB(WriteTLR1) {
    Uns32 d = GETLE(bigEndian,data);
    plb_REG_data.TLR1.value = d;
    if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Write TLR1=0x%08x", plb_REG_data.TLR0.value);
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();
    interruptSet(0);

    //
    // Clock frequency
    //
    Uns32 frequency;
    bhmUns32ParamValue("frequency", &frequency);
    freq_mhz = frequency / 1000000;

    // get endian
    char endian[16];
    if(bhmStringParamValue("endian", endian, sizeof(endian))) {
        if(!strcmp(endian, "little")) {
            bigEndian = False;
        }
    }

    if (PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX, "Model interface configured %s endian",
            bigEndian ? "big" : "little");

}

PPM_DESTRUCTOR_CB(destructor) {
    // YOUR CODE HERE (destructor)

    //
    // Clean up any threads left over
    //
    timerStop(0);
    timerStop(1);
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}


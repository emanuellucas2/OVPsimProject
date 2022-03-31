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

#include <stdio.h>
#include <string.h>

#include "pse.igen.h"

#define PREFIX "TTC"

Bool bigEndian;     // processor interface endian

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
threadInfoT tinfo[3];

Uns32 clockRate[3];     // clock rate in MHz

#define TIMER1    0
#define TIMER2    1
#define TIMER3    2

// Copied from pse.igen.h
typedef struct Counter_ControlS {
    union {
        Uns32 value;
        struct {
            unsigned DIS : 1;
            unsigned INT : 1;
            unsigned DEC : 1;
            unsigned MATCH : 1;
            unsigned RST : 1;
            unsigned WAVEN : 1;
            unsigned WAVPOL : 1;
        } bits;
    };
} Counter_ControlT, *Counter_ControlTP;

Counter_ControlT getControl(Uns32 tmr) {
    Counter_ControlT control;
    control.value = 0;
    switch (tmr) {
        case TIMER1:
            control.value = bport1_ab_data.Counter_Control_1.value;
            break;
        case TIMER2:
            control.value = bport1_ab_data.Counter_Control_2.value;
            break;
        case TIMER3:
            control.value = bport1_ab_data.Counter_Control_3.value;
            break;
        default:
            bhmMessage("E", PREFIX "_C", "%s: Got bad Timer number %d", __FUNCTION__, tmr);
            break;
    }
    return control;
}

void updateControl(Uns32 tmr, Uns32 value) {
    switch (tmr) {
        case TIMER1:
            bport1_ab_data.Counter_Control_1.value = value;
            break;
        case TIMER2:
            bport1_ab_data.Counter_Control_2.value = value;
            break;
        case TIMER3:
            bport1_ab_data.Counter_Control_3.value = value;
            break;
        default:
            bhmMessage("E", PREFIX "_C", "%s: Got bad Timer number %d", __FUNCTION__, tmr);
            break;
    }
}

void updateCounter(Uns32 tmr, Uns32 value) {
    switch (tmr) {
        case TIMER1:
            bport1_ab_data.Counter_Value_1.value = value;
            break;
        case TIMER2:
            bport1_ab_data.Counter_Value_2.value = value;
            break;
        case TIMER3:
            bport1_ab_data.Counter_Value_3.value = value;
            break;
        default:
            bhmMessage("E", PREFIX "_IC", "%s: Got bad Count register number %d", __FUNCTION__, tmr);
            break;
    }
}

void updateInterruptEnable(Uns32 tmr, Uns32 value) {
    switch (tmr) {
        case TIMER1:
            bport1_ab_data.Interrupt_Enable_1.value = value;
            break;
        case TIMER2:
            bport1_ab_data.Interrupt_Enable_2.value = value;
            break;
        case TIMER3:
            bport1_ab_data.Interrupt_Enable_3.value = value;
            break;
        default:
            bhmMessage("E", PREFIX "_IC", "%s: Got bad Interrupt Register number %d", __FUNCTION__, tmr);
            break;
    }
}

Uns32 getInterruptEnable(Uns32 tmr) {
    Uns32 value = 0;
    switch (tmr) {
        case TIMER1:
            value = bport1_ab_data.Interrupt_Enable_1.value;
            break;
        case TIMER2:
            value = bport1_ab_data.Interrupt_Enable_2.value;
            break;
        case TIMER3:
            value = bport1_ab_data.Interrupt_Enable_3.value;
            break;
        default:
            bhmMessage("E", PREFIX "_IC", "%s: Got bad Interrupt Register number %d", __FUNCTION__, tmr);
            break;
    }
    return value;
}


void updateInterruptRegister(Uns32 tmr, Uns32 value) {
    switch (tmr) {
        case TIMER1:
            bport1_ab_data.Interrupt_Register_1.value = value;
            break;
        case TIMER2:
            bport1_ab_data.Interrupt_Register_2.value = value;
            break;
        case TIMER3:
            bport1_ab_data.Interrupt_Register_3.value = value;
            break;
        default:
            bhmMessage("E", PREFIX "_IC", "%s: Got bad Interrupt Register number %d", __FUNCTION__, tmr);
            break;
    }
}

Uns32 getInterruptRegister(Uns32 tmr) {
    Uns32 value = 0;
    switch (tmr) {
        case TIMER1:
            value = bport1_ab_data.Interrupt_Register_1.value;
            break;
        case TIMER2:
            value = bport1_ab_data.Interrupt_Register_2.value;
            break;
        case TIMER3:
            value = bport1_ab_data.Interrupt_Register_3.value;
            break;
        default:
            bhmMessage("E", PREFIX "_IC", "%s: Got bad Interrupt Register number %d", __FUNCTION__, tmr);
            break;
    }
    return value;
}

Uns32 getPrescale(Uns32 tmr) {
    Uns32 prescale = 1;
    Uns32 PS_V = -1;
    switch (tmr) {
        case TIMER1:
            if(bport1_ab_data.Clock_Control_1.bits.PS_EN)
                PS_V = bport1_ab_data.Clock_Control_1.bits.PS_V;
            break;
        case TIMER2:
            if (bport1_ab_data.Clock_Control_2.bits.PS_EN)
                PS_V = bport1_ab_data.Clock_Control_2.bits.PS_V;
            break;
        case TIMER3:
            if(bport1_ab_data.Clock_Control_3.bits.PS_EN)
                PS_V = bport1_ab_data.Clock_Control_3.bits.PS_V;
            break;
        default:
            bhmMessage("E", PREFIX "_IC", "%s: Got bad Timer number %d", __FUNCTION__, tmr);
            break;
    }

    prescale = (1<<(PS_V+1));

    return prescale;
}

Uns32 getIntervalCounter(Uns32 tmr) {
    Uns32 intervalCounter = 0;
    switch (tmr) {
        case TIMER1:
            intervalCounter = bport1_ab_data.Interval_Counter_1.value;
            break;
        case TIMER2:
            intervalCounter = bport1_ab_data.Interval_Counter_2.value;
            break;
        case TIMER3:
            intervalCounter = bport1_ab_data.Interval_Counter_3.value;
            break;
        default:
            bhmMessage("E", PREFIX "_IC", "%s: Got bad Timer number %d", __FUNCTION__, tmr);
            break;
    }
    return intervalCounter;
}

Uns32 getCountValue(Uns32 tmr) {
    Uns32 counter = 0;
    switch (tmr) {
        case TIMER1:
            counter = bport1_ab_data.Counter_Value_1.value;
            break;
        case TIMER2:
            counter = bport1_ab_data.Counter_Value_2.value;
            break;
        case TIMER3:
            counter = bport1_ab_data.Counter_Value_3.value;
            break;
        default:
            bhmMessage("E", PREFIX "_IC", "%s: Got bad Timer number %d", __FUNCTION__, tmr);
            break;
    }
    return counter;
}

Uns32 getCountNow(Uns32 tmr) {

    double now     = bhmGetLocalTime();
    double start   = tinfo[tmr].start;
    double timeout = tinfo[tmr].timeout;
    Uns32  count   = tinfo[tmr].count;
    double remain  = 0;

    if(tinfo[tmr].active) {
        // a timer was started at start - so counter now depends how much time elapsed
        remain  = (now -start) * (double)clockRate[tmr] / (double)getPrescale(tmr);
        // update from the initial count value
        remain += count;

        // convert using Uns64 result to avoid overflow
        Uns64 value64 = remain;
        Uns32 value   = value64 & 0xffff;   // 16-bit counter

        if (PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX, "Clocks Remain %d "
                                    "now %10.3f uS start %10.3f uS "
                                    "timeout %10.3f uS remain %10.3f uS "
                                    "Count %lld (0x%08x %d)",
                                    tmr, now, start, timeout,
                                    remain, value64, value, value);


        Counter_ControlT control = getControl(tmr);

        if (control.bits.DEC) {
            // counting down
            value = ~value;
        }
        return value;
    } else {
        // return the current counter value
        return getCountValue(tmr);
    }

}

void updateCountNow(Uns32 tmr) {

    Uns32 value = getCountNow(tmr);

    // write value back to register
    updateCounter(tmr, value);
}

Uns32 match[3];
void getMatchRegs(Uns32 tmr) {

    switch(tmr) {
    case TIMER1:
        match[0] = bport1_ab_data.Match_1_Counter_1.value;
        match[1] = bport1_ab_data.Match_2_Counter_1.value;
        match[2] = bport1_ab_data.Match_3_Counter_1.value;
        break;
    case TIMER2:
        match[0] = bport1_ab_data.Match_1_Counter_2.value;
        match[1] = bport1_ab_data.Match_2_Counter_2.value;
        match[2] = bport1_ab_data.Match_3_Counter_2.value;
        break;
    case TIMER3:
        match[0] = bport1_ab_data.Match_1_Counter_3.value;
        match[1] = bport1_ab_data.Match_2_Counter_3.value;
        match[2] = bport1_ab_data.Match_3_Counter_3.value;
        break;
    default:
        bhmMessage("E", PREFIX "_C", "%s: Got bad Timer number %d", __FUNCTION__, tmr);
        break;
    }
}

Uns32 getTarget (Uns32 tmr) {

    Uns32 target = 0;

    Counter_ControlT control = getControl(tmr);

    tinfo[tmr].freeRun = 0; // clear freerun flag

    // interval mode
    if (control.bits.INT) {
        if (PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX, "Timer_%d interval mode", tmr);
        }

        // time out is to the interval counter value
        target = getIntervalCounter(tmr);
    } else if (control.bits.MATCH) {

        getMatchRegs(tmr);

        Uns32 i;
        Uns32 location=0;
        Uns32 rslt = match[0];
        for(i=1;i<3;i++) {
            if(control.bits.DEC) {
                // counting DOWN (find max)
                if(match[i]>rslt) {
                    rslt=match[i];
                    location=i+1;
                }
            } else {
                // counting UP (find min)
                if(match[i]<rslt) {
                    rslt=match[i];
                    location=i+1;
                }
            }
        }

        target           = match[location];
        tinfo[tmr].match = location;
        if (PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX, "Timer_%d match mode (%d)", tmr, location);
        }
    } else {
        if (PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX, "Timer_%d MAX count, freerun", tmr);
        }
        target = (1<< 16) - 1;  // 16 bit timer maximum
        tinfo[tmr].freeRun = 1;
    }

    tinfo[tmr].target = target;

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Timer_%d target %d", tmr, (Uns32)target);
    }

    return target;
}

double getTimeout (Uns32 tmr) {

    Uns32 target   = getTarget(tmr);
    Uns32 current  = getCountNow(tmr);
    Uns32 ticks    = target - current;
    double timeout = 0;

    if(ticks > 0) {
        timeout = (double)(ticks) / ((double)clockRate[tmr] / (double)getPrescale(tmr));
    }
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Timer_%d timeout %10.3f uS target %d current %d "
                                "clock %d MHz prescale %d",
                                tmr, timeout, target, current,
                                clockRate[tmr], getPrescale(tmr));
    }

    return timeout;
}

// set the reset value
void resetCounter(Uns32 tmr) {
    Uns32 value = 0;

    Counter_ControlT control = getControl(tmr);

    if (PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX, "Timer %d Reset", tmr);

    if(control.bits.INT) {
        // if interval timer set to interval time
        value = getIntervalCounter(tmr);
    } else {
        // not interval timer so 0 or -1 depending if up/down
        if(control.bits.DEC) {
            value = -1;
        }
    }
    // reset flag cleared
    control.bits.RST = 0;

    updateCounter(tmr, value);
    updateControl(tmr, control.value);
}

//
// Write the Interrupt if the value changes
//
void interruptSet(Uns32 tmr, Uns32 value) {
    static Uns32 interrupt[3] = {0,0,0};

    // only set interrupt if not already active
    if (interrupt[tmr] != value) {
        interrupt[tmr] = value;
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Setting int%d=%d (%e)\n", tmr, interrupt[tmr], bhmGetCurrentTime());
        switch (tmr) {
            case TIMER1:
                ppmWriteNet(handles.int1, interrupt[tmr]);
                break;
            case TIMER2:
                ppmWriteNet(handles.int2, interrupt[tmr]);
                break;
            case TIMER3:
                ppmWriteNet(handles.int3, interrupt[tmr]);
                break;
            default:
                bhmMessage("E", PREFIX "_C", "%s: Got bad Timer number %d", __FUNCTION__, tmr);
                break;
        }
    }
}

#define INT_EVENT    0x20
#define INT_OVERFLOW 0x10
#define INT_MATCH3   0x08
#define INT_MATCH2   0x04
#define INT_MATCH1   0x02
#define INT_INTERVAL 0x01

void updateStatus(Uns32 tmr, Uns32 intMask) {
    Uns32 enable = getInterruptEnable(tmr);
    Uns32 intreg = getInterruptRegister(tmr);

    if(intMask) {
        // mask in new events
        intreg |= intMask;

        // write back the register
        updateInterruptRegister(tmr, intreg);
    }

    // generate an interrupt if bit enabled
    if (intreg & enable) {
        interruptSet(tmr, 1);
    } else {
        // clear interrupt
        interruptSet(tmr, 0);
    }
}

void timerExpired(Uns32 tmr) {

    if (PSE_DIAG_HIGH) {
        double now = bhmGetLocalTime();
        bhmMessage("I", PREFIX, "timerExpired tmr=%d time=%e\n", tmr, now);
    }

    Counter_ControlT control = getControl(tmr);

    if(control.bits.INT) {
        // Interval
        updateStatus(tmr, INT_INTERVAL);

    } else if (control.bits.MATCH) {
        // match
        switch(tinfo[tmr].match) {
        case 0:
            updateStatus(tmr, INT_MATCH1);
            break;
        case 1:
            updateStatus(tmr, INT_MATCH3);
            break;
        case 2:
            updateStatus(tmr, INT_MATCH2);
            break;
        default:
            break;
        }

    } else {
        updateStatus(tmr, INT_OVERFLOW);
    }
}

void timerThread(void *user) {

    Uns32 tmr = PTR_TO_UNS32(user);
    Counter_ControlT control;

    do {

        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Start Timer_%d Begin at %10.3f uS "
                                                   "timeout %10.3f uS",
                                                   tmr, tinfo[tmr].start,
                                                   tinfo[tmr].timeout);

        if(tinfo[tmr].timeout)
            bhmWaitDelay(tinfo[tmr].timeout);

        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "End Timer_%d Expired at %10.3f uS",
                                                   tmr, bhmGetCurrentTime());

        timerExpired(tmr);

        control = getControl(tmr);

        tinfo[tmr].start   = bhmGetLocalTime();
        tinfo[tmr].count   = getCountValue(tmr);         // record register value when started
        tinfo[tmr].timeout = getTimeout(tmr);

        // TODO: Check that we keep going if interval or freerun

    } while ((tinfo[tmr].freeRun || control.bits.INT) && !control.bits.DIS && tinfo[tmr].timeout);

    // complete
    if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Complete Timer_%d Thread", tmr);
}

void timerStop(Uns32 tmr) {

    static int cnt=0;
    if (tinfo[tmr].active || tinfo[tmr].handle) {
        if (PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX, "Timer %d Stop", tmr);
        cnt++;
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Delete Timer_%d Thread cnt=%d", tmr, cnt);
        bhmDeleteThread(tinfo[tmr].handle);
        tinfo[tmr].handle = 0;
        tinfo[tmr].active = False;
    }
}

void timerStart(Uns32 tmr) {

    tinfo[tmr].start = bhmGetLocalTime();          // get BHM time at which we start
    tinfo[tmr].count = getCountValue(tmr);         // record register value when started


    Counter_ControlT control = getControl(tmr);
    if (!control.bits.DIS) {
        if (PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX, "Timer %d Start", tmr);

        tinfo[tmr].active = True;

        double timeout = getTimeout(tmr);
        double nextQ   = bhmGetCurrentTime();

        // The initial timeout will not be set until next quantum at the bhmCurrentTime
        double toNextQuantum =  nextQ - tinfo[tmr].start;

        if (timeout > toNextQuantum) {
            if(toNextQuantum > 0)
                tinfo[tmr].timeout = timeout - toNextQuantum;
            else
                tinfo[tmr].timeout = timeout;

            if (PSE_DIAG_HIGH) {
                bhmMessage("I", PREFIX, "Create Timer_%d Thread tinfo[%d].timeout %10.3f uS "
                                        "(now %10.3f uS next %10.3f uS initial %10.3f uS)",
                                        tmr, tmr, tinfo[tmr].timeout,
                                        tinfo[tmr].start, bhmGetCurrentTime(), timeout);
            }

            char tn[16];
            sprintf(tn, "Timer_%d", tmr);
            tinfo[tmr].handle = bhmCreateThread(timerThread, UNS32_TO_PTR(tmr), tn, 0);
        } else {
            if (PSE_DIAG_LOW) {
                bhmMessage("W", PREFIX, "Create Timer_%d Thread Not possible "
                                        "Time now %10.3f uS required timeout %10.3f uS "
                                        "next Quantum %10.3f uS "
                                        ": Timeout is before next Quantum : "
                                        "You should reduce Quantum size",
                                        tmr, tinfo[tmr].start, tinfo[tmr].timeout, nextQ);
            }
        }
    } else {
        if (PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX, "Timer %d Start when Disabled", tmr);
    }
}

// NOTE
// counter reset
// counter reset to 0 or 0xffff or interval value
void updateTimer(Uns32 tmr) {

    Counter_ControlT control = getControl(tmr);
    // check reset
    if (control.bits.RST) {
        resetCounter(tmr);
    }

    if (control.bits.DIS) {
        timerStop(tmr);
        updateCountNow(tmr);
    } else {
        timerStop(tmr);
        timerStart(tmr);
    }
}
//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_READ_CB(rdCurrent1) {
    Counter_ControlT control = getControl(TIMER1);

    if (!control.bits.DIS) {
        // Only update when enabled
        updateCountNow(TIMER1);
    }
    return *(Uns32*)user;
}

PPM_REG_READ_CB(rdCurrent2) {
    Counter_ControlT control = getControl(TIMER2);

    if (!control.bits.DIS) {
        // Only update when enabled
        updateCountNow(TIMER2);
    }
    return *(Uns32*)user;
}

PPM_REG_READ_CB(rdCurrent3) {
    Counter_ControlT control = getControl(TIMER3);

    if (!control.bits.DIS) {
        // Only update when enabled
        updateCountNow(TIMER3);
    }
    return *(Uns32*)user;
}


PPM_REG_READ_CB(rdInt1) {
    Uns32 current = *(Uns32*)user;
    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX, "Read and Clear Interrupt 0x%x (%d)", current, current);
    *(Uns32*)user = 0;
    updateStatus(TIMER1, 0); // clear asserted interrupt
    return current;
}

PPM_REG_READ_CB(rdInt2) {
    Uns32 current = *(Uns32*)user;
    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX, "Read and Clear Interrupt 0x%x (%d)", current, current);
    *(Uns32*)user = 0;
    updateStatus(TIMER2, 0); // clear asserted interrupt
    return current;
}

PPM_REG_READ_CB(rdInt3) {
    Uns32 current = *(Uns32*)user;
    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX, "Read and Clear Interrupt 0x%x (%d)", current, current);
    *(Uns32*)user = 0;
    updateStatus(TIMER3, 0); // clear asserted interrupt
    return current;
}

PPM_REG_WRITE_CB(wrInt) {
    if(PSE_DIAG_MEDIUM)
        bhmMessage("W", PREFIX, "No Write for Interrupt Register");
}

PPM_REG_WRITE_CB(wrClkCtrl1) {

    Uns32 current = *(Uns32*)user;
    Uns32 new     = (*(Uns32*)user & 0xffffff80) | (data & 0x7f);
    if (current != new) {
        *(Uns32*)user = new;
        updateTimer(TIMER1);
    }
}

PPM_REG_WRITE_CB(wrClkCtrl2) {

    Uns32 current = *(Uns32*)user;
    Uns32 new     = (*(Uns32*)user & 0xffffff80) | (data & 0x7f);
    if (current != new) {
        *(Uns32*)user = new;
        updateTimer(TIMER2);
    }
}

PPM_REG_WRITE_CB(wrClkCtrl3) {

    Uns32 current = *(Uns32*)user;
    Uns32 new     = (*(Uns32*)user & 0xffffff80) | (data & 0x7f);
    if (current != new) {
        *(Uns32*)user = new;
        updateTimer(TIMER3);
    }
}

PPM_REG_WRITE_CB(wrCntrCtrl1) {
    Uns32 current = *(Uns32*)user;
    Uns32 new     = (*(Uns32*)user & 0xffffff80) | (data & 0x7f);
    if (current != new) {
        *(Uns32*)user = new;
        updateTimer(TIMER1);
    }
}

PPM_REG_WRITE_CB(wrCntrCtrl2) {
    Uns32 current = *(Uns32*)user;
    Uns32 new     = (*(Uns32*)user & 0xffffff80) | (data & 0x7f);
    if (current != new) {
        *(Uns32*)user = new;
        updateTimer(TIMER2);
    }
}

PPM_REG_WRITE_CB(wrCntrCtrl3) {
    Uns32 current = *(Uns32*)user;
    Uns32 new     = (*(Uns32*)user & 0xffffff80) | (data & 0x7f);
    if (current != new) {
        *(Uns32*)user = new;
        updateTimer(TIMER3);
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

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();

    bhmUns32ParamValue("clk1", &clockRate[0]);
    bhmUns32ParamValue("clk2", &clockRate[1]);
    bhmUns32ParamValue("clk3", &clockRate[2]);

    // power on reset of counters
    bport1_ab_data.Counter_Control_1.bits.RST = 1;
    resetCounter(TIMER1);
    bport1_ab_data.Counter_Control_2.bits.RST = 1;
    resetCounter(TIMER2);
    bport1_ab_data.Counter_Control_3.bits.RST = 1;
    resetCounter(TIMER3);

    // get endian
    char endian[16];
    if(bhmStringParamValue("endian", endian, sizeof(endian))) {
        if(!strcmp(endian, "big")) {
            bigEndian = True;
        }
    }

}

PPM_DESTRUCTOR_CB(destructor) {
    // YOUR CODE HERE (destructor)
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}


/*
 * Copyright (c) 2011-2014 Posedge Software Inc., www.posedgesoft.com
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
#include <assert.h>
#include "pse.igen.h"

#define PREFIX "PIT"

#define NUM_TIMERS  4

typedef struct timerDataS {
    char            threadName[16];
    bhmThreadHandle threadHandle;       // using separate timer threads for now

    bhmEventHandle  overflowEvent;
    Uns64           expireTime;         // bhm time when timer will overflow

    ppmNetHandle    trigHandle;
    ppmNetHandle    irqHandle;
    Bool            irqAsserted;
} TimerDataT, *TimerDataTP;

typedef struct PitStateS {
    TimerDataT timers[NUM_TIMERS];
    bport1_ab_dataTP regs;
    Uns32 clkPeriod;                    // period of the clock input (ns)
} PitStateT, *PitStateTP;

static PitStateT pitState;


// helper defines to access timer registers and nets based on timer index and vice versa
#define TMR_REGS_STEP   ( (Uns8*)&((bport1_ab_dataTP)0)->LDVAL1 - (Uns8*)&((bport1_ab_dataTP)0)->LDVAL0 )
#define TMR_REGS(t)     ( (bport1_ab_dataTP)(((Uns8*)pitState.regs) + (t) * TMR_REGS_STEP) )
#define TMR_REG(t,r)    ( TMR_REGS(t)->r##0 )


#define TMR_NUM(addr,r) ( ((Uns8*)(addr) - (Uns8*)&pitState.regs->r##0) / TMR_REGS_STEP )
#define TMR_TRIG(t)     ( *(&handles.trg0 + t * (&handles.trg1 - &handles.trg0)) )
#define TMR_IRQ(t)      ( *(&handles.irq0 + t * (&handles.irq1 - &handles.irq0)) )


static inline Bool timerEnabled(unsigned int t)
{
    return (bport1_ab_data.MCR.bits.MDIS == 0) && (bport1_ab2_data[t].TCTRL.bits.TEN != 0);
}

static void updateTrigger(unsigned int t)
{
    ppmWriteNet(pitState.timers[t].trigHandle, 1U);
    if (PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX, "Trg%d asserted\n", t);

    ppmWriteNet(pitState.timers[t].trigHandle, 0U);
    if (PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX, "Trg%d de-asserted\n", t);
}

static void updateInt(unsigned int t)
{
    Bool irqWasAsserted = pitState.timers[t].irqAsserted;
    Bool irqAsserted    = bport1_ab2_data[t].TCTRL.bits.TIE && bport1_ab2_data[t].TFLG.bits.TIF;
    pitState.timers[t].irqAsserted = irqAsserted;
    if (irqAsserted != irqWasAsserted) {
        ppmWriteNet(pitState.timers[t].irqHandle, irqAsserted);
        if (PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX, "Irq%d %sasserted\n", t, (irqAsserted ? "" : "de-"));
    }
}

static void enableTimer(unsigned int t)
{
    Uns64 delay = ((Uns64)bport1_ab2_data[t].LDVAL.value + 1U) * pitState.clkPeriod / 1000U;
    delay = (delay < 1U) ? 1U : delay;
    bhmTriggerAfter(pitState.timers[t].overflowEvent, (double)delay);
    pitState.timers[t].expireTime = (Uns64)bhmGetCurrentTime() + delay;
    if (PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "Timer %d (re-)enabled. LDVAL is %u, expire time is %f us\n", t, bport1_ab2_data[t].LDVAL.value, (double)pitState.timers[t].expireTime);
}

static void disableTimer(unsigned int t)
{
    bhmTriggerAfter(pitState.timers[t].overflowEvent, 1.0e25); // TODO: use bhmCancelTrigger() when available
    if (PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "Timer %d disabled at %f us\n", t, bhmGetCurrentTime());
}

static void timerThread(void *user)
{
    Uns32 t = PTR_TO_UNS32(user);

    for (;;) {
        // wait for timer overflow
        bhmRestartReason rr = bhmWaitEvent(pitState.timers[t].overflowEvent);
        if (rr != BHM_RR_TRIGGERED)
            break;
        if (PSE_DIAG_MEDIUM)
            bhmMessage("I", PREFIX, "Timer %d expired at %f us\n", t, bhmGetCurrentTime());

        // process overflow
        updateTrigger(t);
        enableTimer(t);                         // reload timer
        bport1_ab2_data[t].TFLG.bits.TIF = 1U;  // raise the interrupt flag
        updateInt(t);
    }
}

static void pitInit(void)
{
    if (PSE_DIAG_LOW)
        bhmMessage("I", PREFIX, "Initializing model\n");

    // initialize PIT state info
    pitState.regs = &bport1_ab_data;

    Uns64 frequency;
    bhmUns64ParamValue("frequency", &frequency);
    frequency = frequency * (Uns64)1000000U;        // convert to Hz
    pitState.clkPeriod = 1000000000UL / frequency;  // clock period

    if (PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "clock period set to %dns\n", pitState.clkPeriod);

    // initialize timers state info, create threads
    int t;
    for (t=0; t<NUM_TIMERS; t++) {
        TimerDataTP timer = &pitState.timers[t];
        snprintf(timer->threadName, sizeof(timer->threadName), "PIT_Timer%d", t);
        timer->expireTime = (Uns64)(-1);
        timer->overflowEvent = bhmCreateEvent();
        timer->threadHandle = bhmCreateThread(timerThread, UNS32_TO_PTR(t), timer->threadName, 0);
        timer->trigHandle   = handles.trg[t];
        timer->irqHandle    = handles.irq[t];
        timer->irqAsserted = False;
    }
}

/* PPM callback functions */

PPM_NBYTE_VIEW_CB(viewCVAL)
{
    Uns32 block = (offset-0x100)/0x10;

    Uns32 cval = 0U;
    Uns32 t = block;
    if (timerEnabled(t)) {
        cval = (pitState.timers[t].expireTime - (Uns64)bhmGetCurrentTime()) * 1000U / pitState.clkPeriod;
    }
    
    *(Uns32*)data = (cval > 0U) ? (cval - 1U) : 0U;
}

PPM_NBYTE_READ_CB(readCVAL) {
    Uns32 val = 0U;
    viewCVAL(offset, &val, userData);
}

PPM_NBYTE_WRITE_CB(writeMCR) {
    // preserve current timer enable states
    int t;
    Bool oldTmrEn[NUM_TIMERS];
    for (t=0; t<NUM_TIMERS; t++) {
        oldTmrEn[t] = timerEnabled(t);
    }
    bport1_ab_data.MCR.value = *(Uns32*)data;

    // enable/disable timers as needed
    for (t=0; t<NUM_TIMERS; t++) {
        Bool newTmrEn = timerEnabled(t);
        if (newTmrEn && !oldTmrEn[t]) {
            enableTimer(t);
        } else if (!newTmrEn && oldTmrEn[t]) {
            disableTimer(t);
        }
    }
}

PPM_NBYTE_WRITE_CB(writeTCTRL) {

    Uns32 t = (offset-0x100)/0x10;

    // preserve current timer enable state
    Bool oldTmrEn = timerEnabled(t);

    bport1_ab2_data[t].TCTRL.value = *(Uns32*)data & 3;

    // enable/disable timer as needed
    Bool newTmrEn = timerEnabled(t);
    if (newTmrEn && !oldTmrEn) {
        enableTimer(t);
    }else if (!newTmrEn && oldTmrEn) {
        disableTimer(t);
    }
    updateInt(t);
}

PPM_NBYTE_WRITE_CB(writeTFLG) {

    Uns32 t = (offset-0x100)/0x10;
    bport1_ab2_data[t].TFLG.value &= ~*(Uns32*)data;
    updateInt(t);
}

PPM_CONSTRUCTOR_CB(constructor)
{
    periphConstructor();
    pitInit();
}



// Save / restore callbacks

PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}


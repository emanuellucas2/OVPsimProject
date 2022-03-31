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

#include "pse.igen.h"
#define FUNC_NAME __FUNCTION__
#define TODO bhmMessage("F", "TC", "TODO");

struct {
    Uns32 pins;
    Uns32 activeInt;
    Uns32 irq0, irq1, irq2;
} state;

//
// Write the irq0-2 if the value changes
//
void write_irq0(Uns32 value) {
    if (state.irq0 != value) {
        state.irq0 = value;
        if (PSE_DIAG_HIGH) bhmMessage("I", "TC", "Setting Interrupt IRQ0=%d\n", state.irq0);
        ppmWriteNet(handles.IRQ0, state.irq0);
    }
}
void write_irq1(Uns32 value) {
    if (state.irq1 != value) {
        state.irq1 = value;
        if (PSE_DIAG_HIGH) bhmMessage("I", "TC", "Setting Interrupt IRQ1=%d\n", state.irq1);
        ppmWriteNet(handles.IRQ1, state.irq1);
    }
}
void write_irq2(Uns32 value) {
    if (state.irq2 != value) {
        state.irq2 = value;
        if (PSE_DIAG_HIGH) bhmMessage("I", "TC", "Setting Interrupt IRQ2=%d\n", state.irq2);
        ppmWriteNet(handles.IRQ2, state.irq2);
    }
}

static bhmThreadHandle timerThreadHandle = 0;
static Uns64 threadDelay;

static void timerThread(void *user) {
    while (1) {
        bhmWaitDelay(threadDelay);

        if (PSE_DIAG_HIGH) bhmMessage("I", "TC", "Start Timer Expired");
        write_irq1(1);
        write_irq1(0);
    }

    // Call info
    //bhmTriggerEvent(timerFired);

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
    if (PSE_DIAG_HIGH) bhmMessage("I", "TC", "Start Timer for %lldus", delay);
    timerThreadHandle = bhmCreateThread(timerThread, 0, "timer", 0);
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_WRITE_CB(TC_BCR_wcb) {
    // YOUR CODE HERE (TC_BCR_wcb)
    bp1_REG_data.TC_BCR.value = data;
}

PPM_REG_WRITE_CB(TC_BMR_wcb) {
    // YOUR CODE HERE (TC_BMR_wcb)
    bp1_REG_data.TC_BMR.value = data;
}

PPM_REG_WRITE_CB(TC_CCR_wcb0) {
    // YOUR CODE HERE (TC_CCR_wcb0)
    bp1_REG_data.TC_CCR0.value = data;
    if (bp1_REG_data.TC_CCR0.bits.SWTRG == 1) {
        write_irq0(1);
        write_irq0(0);
    }
}

PPM_REG_WRITE_CB(TC_CCR_wcb1) {
    // YOUR CODE HERE (TC_CCR_wcb1)
    bp1_REG_data.TC_CCR1.value = data;
    if (bp1_REG_data.TC_CCR1.bits.SWTRG == 1) {
        write_irq1(1);
        write_irq1(0);
    }
}

PPM_REG_WRITE_CB(TC_CCR_wcb2) {
    // YOUR CODE HERE (TC_CCR_wcb2)
    bp1_REG_data.TC_CCR2.value = data;
    if (bp1_REG_data.TC_CCR2.bits.SWTRG == 1) {
        write_irq2(1);
        write_irq2(0);
    }
}

PPM_REG_WRITE_CB(TC_CMR_wcb0) {
    // YOUR CODE HERE (TC_CMR_wcb0)
    bp1_REG_data.TC_CMR0.value = data;
}

PPM_REG_WRITE_CB(TC_CMR_wcb1) {
    // YOUR CODE HERE (TC_CMR_wcb1)
    bp1_REG_data.TC_CMR1.value = data;
}

PPM_REG_WRITE_CB(TC_CMR_wcb2) {
    // YOUR CODE HERE (TC_CMR_wcb2)
    bp1_REG_data.TC_CMR2.value = data;
}

PPM_REG_WRITE_CB(TC_CVR_wcb0) {
    // YOUR CODE HERE (TC_CVR_wcb0)
    bp1_REG_data.TC_CVR0.value = data;
}

PPM_REG_WRITE_CB(TC_CVR_wcb1) {
    // YOUR CODE HERE (TC_CVR_wcb1)
    bp1_REG_data.TC_CVR1.value = data;
}

PPM_REG_WRITE_CB(TC_CVR_wcb2) {
    // YOUR CODE HERE (TC_CVR_wcb2)
    bp1_REG_data.TC_CVR2.value = data;
}

PPM_REG_WRITE_CB(TC_IDR_wcb0) {
    // YOUR CODE HERE (TC_IDR_wcb0)
    bp1_REG_data.TC_IDR0.value = data;
}

PPM_REG_WRITE_CB(TC_IDR_wcb1) {
    // YOUR CODE HERE (TC_IDR_wcb1)
    bp1_REG_data.TC_IDR1.value = data;
}

PPM_REG_WRITE_CB(TC_IDR_wcb2) {
    // YOUR CODE HERE (TC_IDR_wcb2)
    bp1_REG_data.TC_IDR2.value = data;
}

PPM_REG_WRITE_CB(TC_IER_wcb0) {
    // YOUR CODE HERE (TC_IER_wcb0)
    bp1_REG_data.TC_IER0.value = data;
}

PPM_REG_WRITE_CB(TC_IER_wcb1) {
    // YOUR CODE HERE (TC_IER_wcb1)
    bp1_REG_data.TC_IER1.value = data;
}

PPM_REG_WRITE_CB(TC_IER_wcb2) {
    // YOUR CODE HERE (TC_IER_wcb2)
    bp1_REG_data.TC_IER2.value = data;
}

PPM_REG_WRITE_CB(TC_RA_wcb0) {
    // YOUR CODE HERE (TC_RA_wcb0)
    bp1_REG_data.TC_RA0.value = data;
}

PPM_REG_WRITE_CB(TC_RA_wcb1) {
    // YOUR CODE HERE (TC_RA_wcb1)
    bp1_REG_data.TC_RA1.value = data;
}

PPM_REG_WRITE_CB(TC_RA_wcb2) {
    // YOUR CODE HERE (TC_RA_wcb2)
    bp1_REG_data.TC_RA2.value = data;
}

PPM_REG_WRITE_CB(TC_RB_wcb0) {
    // YOUR CODE HERE (TC_RB_wcb0)
    bp1_REG_data.TC_RB0.value = data;
}

PPM_REG_WRITE_CB(TC_RB_wcb1) {
    // YOUR CODE HERE (TC_RB_wcb1)
    bp1_REG_data.TC_RB1.value = data;
}

PPM_REG_WRITE_CB(TC_RB_wcb2) {
    // YOUR CODE HERE (TC_RB_wcb2)
    bp1_REG_data.TC_RB2.value = data;
}

PPM_REG_WRITE_CB(TC_RC_wcb0) {
    // YOUR CODE HERE (TC_RC_wcb0)
    bp1_REG_data.TC_RC0.value = data;
}

PPM_REG_WRITE_CB(TC_RC_wcb1) {
    // YOUR CODE HERE (TC_RC_wcb1)
    bp1_REG_data.TC_RC1.value = data;
    // Set a callback
    startTimer(data << bp1_REG_data.TC_CMR1.bits.TCCLKS);
}

PPM_REG_WRITE_CB(TC_RC_wcb2) {
    // YOUR CODE HERE (TC_RC_wcb2)
    bp1_REG_data.TC_RC2.value = data;
}

PPM_CONSTRUCTOR_CB(constructor) {
    // YOUR CODE HERE (pre constructor)
    periphConstructor();
    // YOUR CODE HERE (post constructor)

    write_irq0(0);
    write_irq1(0);
    write_irq2(0);
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}


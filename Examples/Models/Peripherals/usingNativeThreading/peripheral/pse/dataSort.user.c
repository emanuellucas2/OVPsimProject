/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                          Wed Aug 18 12:57:18 2010
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>

#include "peripheral/impTypes.h"
#include "peripheral/bhm.h"
#include "peripheral/ppm.h"

#include "dataSort.igen.h"

#define PREFIX "DATASORT"

#define THREAD_STACK      (2*1024)

typedef struct {
    bhmThreadHandle       thread;
    bhmEventHandle        start;
    Bool                  dataReady;
    Uns32                 stack[THREAD_STACK];
} channelState;

typedef struct {
    Bool                  initSH;
    Bool                  interruptState;
    Bool                  quantumDelay;
    Bool                  registerOnly;
    channelState          ch;
} datasortState, *datasortStateP;

datasortState state;

//
// Semihosted function: passes initialisation info
//
FUNCTOHOST(void, initSemiHost, Uns32 base, Uns32 size, Bool registerOnly)

//
// Semihosted function
//
FUNCTOHOST(void, runSort, void)

//
// Update interrupt line
//
static void updateInterrupt(void) {
    if (handles.INT) {
        if (state.ch.dataReady && !state.interruptState) {
            if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Interrupt signal asserted");
            ppmWriteNet(handles.INT, 1);
            state.interruptState = 1;
        } else if(!state.ch.dataReady && state.interruptState) {
            if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Interrupt signal de-asserted");
            ppmWriteNet(handles.INT, 0);
            state.interruptState = 0;
        }
    }
}

//
// Initialize semihost if not already done
//
static void initSH(void) {
    if(!state.initSH) {
        state.initSH = 1;
        initSemiHost(
            DATASORTSP_ab32ch0_data.srcAddr.value,
            DATASORTSP_ab32ch0_data.dataSize.value,
            state.registerOnly
        );
    }
}

//
// Start a data sort operation
//
static void startOp(void) {
    initSH();
    bhmTriggerEvent(state.ch.start);
}

PPM_REG_READ_CB(regRdStart) {
    return state.ch.dataReady;
}

PPM_REG_WRITE_CB(regWrStart) {

    DATASORTSP_ab8_data.start.value = data;

    if(DATASORTSP_ab8_data.start.value) {

        // writing non-zero starts the thread
        if (PSE_DIAG_MEDIUM) {
            bhmMessage(
                "I", PREFIX,
                "Write %d to reg start => GO\n",
                DATASORTSP_ab8_data.start.value
            );
        }
        startOp();

    } else {

        // writing zero clears the interrupt
        if (PSE_DIAG_MEDIUM) {
            bhmMessage(
                "I", PREFIX,
                "Write %d to reg start => CLR INT\n",
                DATASORTSP_ab8_data.start.value
            );
        }
        state.ch.dataReady = False;
        updateInterrupt();

    }
}

PPM_REG_READ_CB(regRdDataSize) {
    return DATASORTSP_ab32ch0_data.dataSize.value;
}

PPM_REG_WRITE_CB(regWrDataSize) {
    if (PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX, "regWrDataSize = 0x%x\n", data);
    DATASORTSP_ab32ch0_data.dataSize.value = data;
}

PPM_REG_READ_CB(regRdSrcAddr) {
    return DATASORTSP_ab32ch0_data.srcAddr.value;
}

PPM_REG_WRITE_CB(regWrSrcAddr) {
    if (PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX, "regWrSrcAddr = 0x%x\n", data);
    DATASORTSP_ab32ch0_data.srcAddr.value = data;
}

// Thread for each channel
static void channelThread(void *user) {

    for (;;) {
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Waiting\n");

        bhmWaitEvent(state.ch.start);

        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Started\n");

        // run native sort algorithm
        runSort();

        // wait for simulated time of 30 seconds, or for as long as required
        // for asynchronous threads to run
        bhmWaitDelay(state.quantumDelay ? QUANTUM_DELAY : 30000000);

        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Done\n");
        state.ch.dataReady = True;
        updateInterrupt();
    }
}

PPM_CONSTRUCTOR_CB(constructor) {

    if (PSE_DIAG_LOW) bhmMessage("I", PREFIX, "Constructor called\n");

    // Add peripheral components
    periphConstructor();

    // Initialize state
    state.initSH         = False;
    state.interruptState = False;
    bhmBoolParamValue("registeronly", &state.registerOnly);
    bhmBoolParamValue("quantumdelay", &state.quantumDelay);

    // Configure channel
    state.ch.start     = bhmCreateEvent();
    state.ch.dataReady = False;
    state.ch.thread    = bhmCreateThread(
                            channelThread,
                            0,
                            "datasortThread",
                            &state.ch.stack[THREAD_STACK]
                         );

}

PPM_DESTRUCTOR_CB(destructor) {

}

PPM_SAVE_STATE_FN(peripheralSaveState) {

}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {

}

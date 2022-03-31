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
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>

#include "pse.igen.h"

#define NUM_CHANNELS      2

typedef struct {
    bhmThreadHandle       thread;
    bhmEventHandle        start;
    Bool                  busy;
} channelState;

typedef struct {
    ppmAddressSpaceHandle readHandle;
    ppmAddressSpaceHandle writeHandle;
    ppmNetHandle          intTCHandle;
    Bool                  intTCAsserted;
    Bool                  inReset;
    channelState          ch[NUM_CHANNELS];
} dmaState, *dmaStateP;

static dmaState DMAState;

static void checkSize1(Uns32 bytes) {
    if(bytes != 1) {
        bhmMessage("E", "DMAC_WE1", "Access must be 1 byte");
    }
}

static void checkSize4(Uns32 bytes) {
    if(bytes != 4) {
        bhmMessage("E", "DMAC_WE1", "Access must be 4 bytes");
    }
}

static void startDMA(Uns8 ch)
{
    if(!DMACSP_ab32_data[ch].config.bits.halt
     && DMACSP_ab32_data[ch].config.bits.enable
     && !DMAState.ch[ch].busy) {
        bhmTriggerEvent(DMAState.ch[ch].start);
    }
}

PPM_NBYTE_WRITE_CB(TCclearWr) {
    checkSize1(bytes);
    DMACSP_ab8_data.intTCstatus.value = *(Uns8*)data;
}

PPM_NBYTE_WRITE_CB(configChWr) {
    checkSize4(bytes);
    Uns32 ch = PTR_TO_UNS32(userData);
    DMACSP_ab32_data[ch].config.value =  *(Uns32*)data;
    startDMA(ch);
}

PPM_NBYTE_WRITE_CB(configWr) {
    checkSize1(bytes);
    DMACSP_ab8_data.config.value = *(Uns8*)data;
}

static void dmaBurst(Uns32 channel)
{
    // this is where the dma will happen.
}
//
// Thread for each channel
// When it starts, it runs to the first 'wait' which is in this case bhmWaitEvent()
//
static void channelThread(void *user)
{
    Uns32 ch = PTR_TO_UNS32(user);
    for (;;) {
        if (PSE_DIAG_MEDIUM) bhmMessage("I", "DMAC", "ch %u waiting\n", ch);
        DMAState.ch[ch].busy = False;

        bhmWaitEvent(DMAState.ch[ch].start);
        {
            DMAState.ch[ch].busy = True;
            if (PSE_DIAG_MEDIUM) bhmMessage("I", "DMAC", "ch %u running\n", ch);

            // Perform DMA burst
            dmaBurst(ch);

            DMACSP_ab8_data.rawTCstatus.value |= (1 << ch);
            if (PSE_DIAG_MEDIUM) {
                bhmMessage("I", "DMAC",
                    "ch %u status=0x%x\n",
                    ch,
                    DMACSP_ab8_data.rawTCstatus.value
                );
            }
        }
    }
}

void userInit(void)
{
    Uns32 i;
    char threadName[32];

    DMAState.intTCAsserted = False;

    // Create threads for the channels
    for (i=0; i<NUM_CHANNELS; i++) {

        // Event to start the thread
        DMAState.ch[i].start = bhmCreateEvent();
        DMAState.ch[i].busy  = False;

        // create the thread
        sprintf(threadName, "ch%u", i);
        DMAState.ch[i].thread = bhmCreateThread(
            channelThread,
            UNS32_TO_PTR(i),
            threadName,
            0
        );
    }
}

PPM_CONSTRUCTOR_CB(constructor) {
    // YOUR CODE HERE (pre constructor)
    periphConstructor();
    // YOUR CODE HERE (post constructor)
    userInit();
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


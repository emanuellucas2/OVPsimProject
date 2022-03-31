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

//  Peripheral DMAC

#include <stdio.h>
#include <string.h>

#include "peripheral/impTypes.h"
#include "peripheral/bhm.h"
#include "peripheral/ppm.h"

#include "pse.igen.h"

#define NUM_CHANNELS      2
#define BYTES_PER_ACCESS  8

typedef struct {
    bhmThreadHandle       thread;
    bhmEventHandle        start;
    Bool                  busy;
} channelState;

typedef struct {
    Bool                  intTCAsserted;
    Bool                  inReset;
    channelState          chState[NUM_CHANNELS];
} dmaState;

static dmaState DMAState;

DMACSP_ab8_dataTP control;

typedef union {
    DMACSP_ab32ch0_dataT ch;    // Assumes ch0/1 are identical structures
    DMACSP_ab32ch0_dataT ch0;
    DMACSP_ab32ch1_dataT ch1;
} DMACSP_ab32ch, *DMACSP_ab32chP;

DMACSP_ab32chP ch[2];

static void updateInterrupts(void);
#ifndef ENDIANBIG
#define ENDIANBIG 0
#endif
static inline Uns32 byteSwap(Uns32 data){
    return SWAP_4_BYTE_COND(data, ENDIANBIG);
}

//
// any write will clear the TC register
//
PPM_REG_WRITE_CB(TCclearWr) {
    DMACSP_ab8_data.intTCstatus.value = 0;
}

static void writeAndStart(Uns8 channel, Uns32 data)
{
    ch[channel]->ch.config.value = byteSwap(data);
    if(!ch[channel]->ch.config.bits.halt && ch[channel]->ch.config.bits.enable && !DMAState.chState[channel].busy) {
        bhmTriggerEvent(DMAState.chState[channel].start);
    }
    updateInterrupts();
}

PPM_REG_WRITE_CB(configWr) {
    DMACSP_ab8_data.config.value = data;
}
//
// write config registers channel 0 and channel 1
//
PPM_REG_WRITE_CB(configChWr) {
    writeAndStart(PTR_TO_UNS32(user), data);
}

#define CH0_INT (1<<0)
#define CH1_INT (1<<1)

static void updateInterrupts(void)
{
    // Update intTCStatus from rawIntTCStatus
    Uns32 rawIntTCStatus = DMACSP_ab8_data.rawTCstatus.value;
    Uns32 intTCStatus = 0;

    if ((ch[0]->ch.config.bits.inten) && (rawIntTCStatus & CH0_INT)) {
        intTCStatus |= CH0_INT;
    }

    if ((ch[1]->ch.config.bits.inten) && (rawIntTCStatus & CH1_INT)) {
        intTCStatus |= CH1_INT;
    }
    DMACSP_ab8_data.intTCstatus.value = intTCStatus;

    // Update TC interrupt line
    if (handles.INTTC) {
        if (intTCStatus && !DMAState.intTCAsserted) {
            ppmWriteNet(handles.INTTC, 1);
            DMAState.intTCAsserted = True;
        } else if (!intTCStatus && DMAState.intTCAsserted) {
            ppmWriteNet(handles.INTTC, 0);
            DMAState.intTCAsserted = False;
        }
    }
}

static void dmaBurst(Uns32 channel)
{
    Uns32 bytes;
    Uns32 src;
    Uns32 dest;
    char buff[BYTES_PER_ACCESS];

    bytes = ch[channel]->ch.control.bits.transferSize;
    src   = ch[channel]->ch.srcAddr.value;
    dest  = ch[channel]->ch.dstAddr.value;
    Uns32 burst = 1 << DMACSP_ab8_data.config.bits.burstSize;

    if (PSE_DIAG_MEDIUM) {
        bhmMessage("I", "DMAC",
            "ch %u burst %u %u bytes from %08x to %08x\n",
            channel, burst, bytes, src, dest
        );
    }
    while (bytes) {
        Uns32 thisAccess = (bytes > burst) ? burst : bytes;
        ppmReadAddressSpace (handles.MREAD,  src,  thisAccess, buff);
        ppmWriteAddressSpace(handles.MWRITE, dest, thisAccess, buff);
        src   += thisAccess;
        dest  += thisAccess;
        bytes -= thisAccess;
        if (PSE_DIAG_HIGH) {
            bhmMessage("I", "DMAC",
                "ch %u access %u bytes from %08x to %08x\n",
                channel, thisAccess, src, dest
            );
        }
        ch[channel]->ch.srcAddr.value = src;
        ch[channel]->ch.dstAddr.value = dest;
        bhmWaitDelay(1);
    }
}

// Thread for each channel
static void channelThread(void *user)
{
    Uns32 ch = PTR_TO_UNS32(user);
    for (;;) {
        if (PSE_DIAG_MEDIUM) bhmMessage("I", "DMAC", "ch %u waiting\n", ch);
        DMAState.chState[ch].busy = False;

        bhmWaitEvent(DMAState.chState[ch].start);
        //bhmWaitDelay(100);
        if (DMAState.inReset) {
            if (PSE_DIAG_MEDIUM) bhmMessage("I", "DMAC", "In reset\n");
        } else {
            DMAState.chState[ch].busy = True;
            if (PSE_DIAG_MEDIUM) bhmMessage("I", "DMAC", "ch %u running\n", ch);

            // Perform DMA burst
            dmaBurst(ch);

            DMACSP_ab8_data.rawTCstatus.value |= (1 << ch);
            if (PSE_DIAG_MEDIUM)
                bhmMessage("I", "DMAC",
                    "ch %u status=0x%x\n",
                    ch,
                    DMACSP_ab8_data.rawTCstatus.value
                );
            updateInterrupts();
        }
    }
}

void userReset(Uns32 v) {
    memset(ch,        0, sizeof(ch));
    memset(&DMAState, 0, sizeof(DMAState));
    memset(&control,  0, sizeof(control));
    DMAState.inReset = v;
}

void userInit(void)
{
    Uns32 i;
    char threadName[32];

    if (PSE_DIAG_HIGH)
        bhmMessage("I", "PP_STUBS","User initialization\n");

    // USER INITIALIZATION
    if(!handles.MREAD) {
        bhmMessage("E", "DMAC", "Failed to open read port\n");
    }
    if(!handles.MWRITE) {
        bhmMessage("E", "DMAC", "Failed to open write port\n");
    }

    DMAState.intTCAsserted = False;

    // Initialize pointers
    control = &DMACSP_ab8_data;
    ch[0]   = (DMACSP_ab32chP) &DMACSP_ab32ch0_data;
    ch[1]   = (DMACSP_ab32chP) &DMACSP_ab32ch1_data;

    // Create threads for the channels
    for (i=0; i<NUM_CHANNELS; i++) {

        // Event to start the thread
        DMAState.chState[i].start = bhmCreateEvent();
        DMAState.chState[i].busy = False;

        sprintf(threadName, "ch%u", i);
        DMAState.chState[i].thread = bhmCreateThread(
            channelThread,
            UNS32_TO_PTR(i),
            threadName,
            0
        );
    }

}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();
    userInit();
}

PPM_DESTRUCTOR_CB(destructor) {
}

PPM_NET_CB(uReset) {
    userReset(value);
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}



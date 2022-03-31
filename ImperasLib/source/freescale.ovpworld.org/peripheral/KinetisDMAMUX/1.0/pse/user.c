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
#include <string.h>

#include "pse.igen.h"

//////////////////////////////// Callback stubs ////////////////////////////////
#define muxRegisters bport1_ab_dataT
#define THREAD_STACK (8*1024)

muxRegisters *muxReg;
static char *periphName = "KinetisDMAMUX";

typedef struct srcConfigS
{
    Uns32 dmaChannel;
    Uns32 lastRequestValue;
} srcConfigT, *srcConfigP;

Uns32 startDMAChannel = 0;

srcConfigT srcConfig[64];

/////////////////////////////////////////////////////////////
// Functions to access the CHCFG bit fields.
/////////////////////////////////////////////////////////////
static int isChannelEnabled(Uns32 chNum)
{
    return bport1_ab_data.CHCFG[chNum].value & 0x80;
}

// If we start using the trigger, uncomment this function to access the TRIG
// bitfield in the Channel configuration.
static int isTriggerEnabled(Uns32 chNum)
{
    // Only have triggers on first 4 channels. Ignore if not one of these.
    if (chNum > 4)
        return 0;

    return bport1_ab_data.CHCFG[chNum].value & 0x40;
}

static Uns32 sourceNum(Uns32 chNum)
{
    return bport1_ab_data.CHCFG[chNum].value  & 0x3f;
}


static int sendDMARequest(Uns32 chNum)
{
    if (chNum > 16) {
        return 1;
    }

    if (isChannelEnabled(chNum))
    {
        if (diagnosticLevel >= 2) {
            bhmMessage("I", periphName, "Sending DMA request on dmaChannel: %d", chNum + startDMAChannel);
        }
        ppmWriteNet(handles.eDMARequest, (ppmNetValue) (chNum + startDMAChannel));
    }
    else
        bhmMessage("W", periphName, "Attempting to sendDMA request on disabled channel: %d", chNum);

    return 0;
}

static void updateSrcConfig(Uns32 chNum, Uns32 data)
{
    Uns32 lastSrc = sourceNum(chNum);
    Uns32 newSrc = (data & 0x3f);

    // Clear the previous user of this channel, and set the new user.
    srcConfig[lastSrc].dmaChannel = (Uns32) -1;
    srcConfig[newSrc].dmaChannel = chNum;
}

PPM_NBYTE_WRITE_CB(dmamuxWrite) {
    Uns32 chNum = offset;

    if(bytes != 1) {
        bhmMessage("E", periphName, "Illegal write to DMA mux of %u bytes (only 1 allowed)", bytes);
        return;
    }
    Uns32 rdata = *(Uns8*)data;

    if (diagnosticLevel >= 2)
        bhmMessage("I", periphName, "Channel %d Config size = %d val = 0x%x", chNum, bytes, rdata);

    if ((chNum < 0) || (chNum > 16)) {
        bhmMessage("E", periphName, "Channel %d out of range", chNum);
        return;
    }

    updateSrcConfig(chNum, rdata);

    if (diagnosticLevel >= 3) {
        bhmMessage("I", periphName, "val = 0x%x", bport1_ab_data.CHCFG[0].value);
    }
}

PPM_NET_CB(dmaSrcRequest) {
    Uns32 srcRequest = PTR_TO_UNS32(userData);

    if (diagnosticLevel >= 2)
        bhmMessage("I", periphName, "Recieved dma request on Source Channel: %d, value = %d", srcRequest, (Uns32)value);

    if ((srcRequest < 0) || (srcRequest > 64))
        bhmMessage("F", periphName, "Source request channel out of range: %d", srcRequest);

    if (value == 0) {

        srcConfig[srcRequest].lastRequestValue = 0;

    } else if ((value == 1) && (srcConfig[srcRequest].lastRequestValue == 0)) {

        srcConfig[srcRequest].lastRequestValue = 1;
        if (sendDMARequest(srcConfig[srcRequest].dmaChannel)) {
            bhmMessage("W", periphName, "Error sending DMARequest: Source: %d  dmaChannel: %d", (Uns32)value, srcConfig[srcRequest].dmaChannel);
        }
    }
}

PPM_NET_CB(dmaTrgRequest) {
    Uns32 trgRequest = PTR_TO_UNS32(userData - 1);

    if (diagnosticLevel >= 3)
        bhmMessage("I", periphName, "Recieved triggered dma request on Source Channel: %d", trgRequest);

    if ((trgRequest < 0) || (trgRequest > 4))
        bhmMessage("W", periphName, "Trigger request out of range: %d", trgRequest);

    if (isTriggerEnabled(trgRequest))
    {
        bhmMessage("I", periphName, "send triggered dma request on Source Channel: %d", trgRequest);
        if (sendDMARequest(trgRequest))
            bhmMessage("W", periphName, "Error sending Triggered DMARequest: Trigger: %d", trgRequest);
    }
}

void userInit(void)
{
    if (diagnosticLevel >= 2)
        bhmMessage("I", periphName, "User Initialization: Starting DMAChannel = %d", startDMAChannel);

    muxReg = (muxRegisters *) &bport1_ab_data;

    memset(srcConfig, 0, sizeof(srcConfigT) * 64);

    // Set our internal array to unconnected.
    int ii;
    for (ii = 0; ii < 64; ii ++)
    {
        srcConfig[ii].dmaChannel = (Uns32) -1;
        srcConfig[ii].lastRequestValue = 0;
    }
}

PPM_CONSTRUCTOR_CB(constructor) {
    bhmUns32ParamValue("startDMAChannel", &startDMAChannel);
    periphConstructor();
    userInit();
}

// Save / restore callbacks

PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}


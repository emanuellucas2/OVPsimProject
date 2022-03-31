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
//                          Tue Sep 23 14:04:23 2014
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>

#include "pse.igen.h"

#define PREFIX "DMA"

#define NUM_CHANNELS          8
#define NUM_ADC_CHANNELS      2
#define MAX_BYTES_PER_ACCESS  8

static Uns32 ADCMA_ADDRESS[2]={0x0ffff22e, 0x0ffff26e};
#define MARBASE_ADDRESS   0x0fff0000

// Give a 'nice' name to the default generated
#define waitControlRegs DMAP0_abc_data
#define dmaByteRegs     DMAP1_abb_data
#define dmaWordRegs     DMAP1_abw_data

typedef struct {
    bhmThreadHandle       thread;
    bhmEventHandle        enable;
    bhmEventHandle        trigger;
    bhmEventHandle        transfer;
    Bool                  busy;
    Uns32                 srcAddr;
    Uns32                 tgtAddr;
    Uns32                 count;
    Bool                  incTgtAddr;
    Bool                  incSrcAddr;
    Bool                  incSize;
} channelState;

typedef struct {
    ppmAddressSpaceHandle portHandle;
    ppmNetHandle          intHandle[NUM_CHANNELS];
    Uns32                 intAsserted[NUM_CHANNELS];
    channelState          ch[NUM_CHANNELS];
} dmaStateT, *dmaStateTP;

dmaStateT DMAState;

static void updateStatus(Uns32 ch)
{
    if (PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX"_US", "Update status ch %d", ch);
    // set bit in status register to indicate transfer complete
    dmaByteRegs.DMASL.value |= (1 << ch);

    // Update interrupt line
    // Does writing/reading DMASL clear interrupt or pulse ok?
    if (DMAState.intHandle[ch]) {
            ppmWriteNet(DMAState.intHandle[ch], 1);
            if (PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX"_INT", "Interrupt line ch %d asserted (pulse)",ch);
            ppmWriteNet(DMAState.intHandle[ch], 0);
            DMAState.intAsserted[ch] = False;
    } else {
        bhmMessage("W", PREFIX"_IF", "Interrupt line ch %d not connected",ch);
    }
}


static void resetCounts(Uns32 ch) {
    switch (ch) {
        case 0:
        case 1:
            // Channel 0/1
            // channel destination register
            DMAState.ch[ch].tgtAddr = dmaWordRegs.MAR[ch].value + MARBASE_ADDRESS;
            // channel count register
            DMAState.ch[ch].count   = dmaByteRegs.DTCR[ch].value;
            DMAState.ch[ch].srcAddr = ADCMA_ADDRESS[ch];
            break;
        default:
            bhmMessage("E", PREFIX"_CH", "Configured with unsupported ADC channel %u", ch);
            break;
        }
}
// Thread for each channel
static void channelADCThread(void *user)
{
    Uns32 ch = PTR_TO_UNS32(user);
    unsigned char buff[MAX_BYTES_PER_ACCESS];

    if (PSE_DIAG_LOW) bhmMessage("I", PREFIX"_CH", "Configure ch %u ADC%u", ch, ch);

    resetCounts(ch);

    // 0,1 : ADC to RAM MARn (16-bit)
    // 2,3 : RAM MARn to Timer S start address SARn (16-bit)
    // 4,5 : CSIB, CSIE, UARTC to RAM MARn (8-bit/16-bit)
    // 6,7 : RAM MARn to CSIB, CSIE, UARTC (8-bit/16-bit)
    for (;;) {
        // Check still enabled
        DMAState.ch[ch].busy = False;
        if (!(dmaByteRegs.DMAMCL.value & (1<<ch))) {
            if (PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX, "ch %u waiting for enable", ch);

            bhmWaitEvent(DMAState.ch[ch].enable);

            resetCounts(ch); // reset counters

            DMAState.ch[ch].busy = True;
            if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "ch %u enabled", ch);
        } else if (DMAState.ch[ch].count == 0) {
            if (PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX, "ch %u waiting for transfer count", ch);
            bhmWaitEvent(DMAState.ch[ch].transfer);

            resetCounts(ch); // reset counters

        }
        // Perform DMA burst (access size set by register 8/16 bit)
        // burst bytes DMAState.ch[ch].DTCR
        // from I/O device (need address map in system)
        // to address in DMAState.ch[ch].MAR

        Uns32 src = DMAState.ch[ch].srcAddr;
        Uns32 thisAccess = 2;   // always 2 bytes transferred

        while (DMAState.ch[ch].count > 0) {
            if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "ch %u wait trigger", ch);
            bhmWaitEvent(DMAState.ch[ch].trigger);
            if (PSE_DIAG_HIGH) {
                bhmMessage("I", PREFIX"_XFR",
                    "ch %u access %u bytes from 0x%08x to 0x%08x (count remaining %d)",
                    ch, thisAccess, src, DMAState.ch[ch].tgtAddr, DMAState.ch[ch].count
                );
            }
            // Transfer the data
            ppmReadAddressSpace (DMAState.portHandle,   src, thisAccess, buff);
            if(PSE_DIAG_HIGH) {
                Uns32 it;
                for (it=0;it<thisAccess;it++){
                    bhmMessage("I", PREFIX"_XFRD", "  buff[%d]=0x%02x", it, buff[it]);
                }
            }
            Bool bret = ppmWriteAddressSpace(DMAState.portHandle, DMAState.ch[ch].tgtAddr, thisAccess, buff);
            if(PSE_DIAG_LOW)
                bhmMessage("I", PREFIX"_XFRD2", "  buff[0-1]=%d 0x%02x   DMAState.ch[ch].tgtAddr=%d 0x%02x tgtaddr:0x%x ret:%d",
                                *(unsigned short*)(UnsPS)buff, *(unsigned short*)(UnsPS)buff,
                                *(unsigned char*)(UnsPS)(DMAState.ch[ch].tgtAddr), *(unsigned char*)(UnsPS)(DMAState.ch[ch].tgtAddr),
               (DMAState.ch[ch].tgtAddr), bret);
            DMAState.ch[ch].tgtAddr  += thisAccess;
            DMAState.ch[ch].count -= 1;

            bhmWaitDelay(1);

            if (!(dmaByteRegs.DMAMCL.value & (1<<ch))) {
                // stop if the DMA channel is no longer enabled
                break;
            }
        }
        if (PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX, "ch %u complete", ch);
        updateStatus(ch);
    }
}

void userInit(void)
{
    Uns32 i;
    char threadName[32];

    if (PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX,"User initialization");

    DMAState.portHandle = handles.DMAPM;

    DMAState.intHandle[0] = handles.INTDMA[0];
    DMAState.intHandle[1] = handles.INTDMA[1];

    // Create threads for the ADC channels
    for (i=0; i<NUM_ADC_CHANNELS; i++) {

        // Event to start the thread
        DMAState.ch[i].enable = bhmCreateEvent();
        DMAState.ch[i].trigger = bhmCreateEvent();
        DMAState.ch[i].transfer = bhmCreateEvent();
        DMAState.ch[i].busy = False;

        sprintf(threadName, "adc-ch%u", i);
        DMAState.ch[i].thread = bhmCreateThread(
            channelADCThread,
            UNS32_TO_PTR(i),
            threadName,
            0
        );
    }
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_READ_CB(readDMADSCL) {
    // YOUR CODE HERE (readDMADSCL)
    return *(Uns8*)user;
}

PPM_REG_READ_CB(readDMAMCL) {
    // YOUR CODE HERE (readDMAMCL)
    return *(Uns8*)user;
}

PPM_REG_READ_CB(readDMASL) {
    // YOUR CODE HERE (readDMASL)
    return *(Uns8*)user;
}

PPM_REG_READ_CB(readDMAWC0) {
    // YOUR CODE HERE (readDMAWC0)
    return *(Uns16*)user;
}

PPM_REG_READ_CB(readDMAWC1) {
    // YOUR CODE HERE (readDMAWC1)
    return *(Uns16*)user;
}

PPM_NBYTE_READ_CB(readDTCR) {
    // YOUR CODE HERE (readDTCR)
    if(bytes != 1) {
        bhmMessage("E", "PPM_WNB", "Only 1 byte access permitted");
        return;
    }
    Uns32 reg   = (offset-(0x24+0x1c))/0x1;
    *(Uns8*)data = DMAP1_abb_data.DTCR[reg].value;
}

PPM_NBYTE_READ_CB(readDTFR) {
    // YOUR CODE HERE (readDTFR)
    if(bytes != 1) {
        bhmMessage("E", "PPM_WNB", "Only 1 byte access permitted");
        return;
    }
    Uns32 reg   = (offset-(0x24+0x5c))/0x1;
    *(Uns8*)data = DMAP1_abb_data.DTFR[reg].value;
}

PPM_NBYTE_READ_CB(readMAR) {

    if(bytes != 2) {
        bhmMessage("E", "PPM_WNB", "Only 2 byte access permitted");
        return;
    }
    Uns32 reg   = (offset-(0x0+0x0))/0x2;
    *(Uns16*)data = DMAP1_abw_data.MAR[reg].value;
}

PPM_NBYTE_READ_CB(readSAR) {
    // YOUR CODE HERE (readSAR)
    if(bytes != 1) {
        bhmMessage("E", "PPM_WNB", "Only 1 byte access permitted");
        return;
    }
    Uns32 reg   = (offset-(0x24+0x0))/0x1;
    *(Uns8*)data = DMAP1_abb_data.SAR[reg].value;
}

PPM_NET_CB(triggerADDMARQ0) {
    if(value) {
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX"_ADDMARQ0", "Trigger ADC0 (%d)", (Uns32)value);
        bhmTriggerEvent(DMAState.ch[0].trigger);
    }
}

PPM_NET_CB(triggerADDMARQ1) {
    if(value) {
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX"_ADDMARQ1", "Trigger ADC1 (%d)", (Uns32)value);
        bhmTriggerEvent(DMAState.ch[1].trigger);
    }
}

PPM_NET_CB(triggerINTBE0R) {
    if (PSE_DIAG_LOW) bhmMessage("W", PREFIX"_TRGNI", "Trigger INTBE0R Not Implemented (%d)", (Uns32)value);
}

PPM_NET_CB(triggerINTBE1R) {
    if (PSE_DIAG_LOW) bhmMessage("W", PREFIX"_TRGNI", "Trigger INTBE1R Not Implemented (%d)", (Uns32)value);
}

PPM_NET_CB(triggerINTCE0C) {
    if (PSE_DIAG_LOW) bhmMessage("W", PREFIX"_TRGNI", "Trigger INTCE0C Not Implemented (%d)", (Uns32)value);
}

PPM_NET_CB(triggerINTCE1C) {
    if (PSE_DIAG_LOW) bhmMessage("W", PREFIX"_TRGNI", "Trigger INTCE1C Not Implemented (%d)", (Uns32)value);
}

PPM_NET_CB(triggerINTTS0CD) {
    if (PSE_DIAG_LOW) bhmMessage("W", PREFIX"_TRGNI", "Trigger INTTS0CD Not Implemented (%d)", (Uns32)value);
}

PPM_NET_CB(triggerINTTS1CD) {
    if (PSE_DIAG_LOW) bhmMessage("W", PREFIX"_TRGNI", "Trigger INTTS1CD Not Implemented (%d)", (Uns32)value);
}

PPM_NET_CB(triggerINTUC0R) {
    if (PSE_DIAG_LOW) bhmMessage("W", PREFIX"_TRGNI", "Trigger INTUC0R Not Implemented (%d)", (Uns32)value);
}

PPM_NET_CB(triggerINTUC1R) {
    if (PSE_DIAG_LOW) bhmMessage("W", PREFIX"_TRGNI", "Trigger INTUC1R Not Implemented (%d)", (Uns32)value);
}

PPM_NET_CB(triggerINTUC2R) {
    if (PSE_DIAG_LOW) bhmMessage("W", PREFIX"_TRGNI", "Trigger INTUC2R Not Implemented (%d)", (Uns32)value);
}

PPM_REG_WRITE_CB(writeDMADSCL) {
    // YOUR CODE HERE (writeDMADSCL)
    if (PSE_DIAG_LOW)
        bhmMessage("W", PREFIX"_DMADSCLW", "No Behaviour Implemented");

    *(Uns8*)user = (*(Uns8*)user & 0xf) | (data & 0xf0);
}

//
// Only write when a value change occurs
//
static void setADCDMAEnable(Uns32 ch, Uns32 value) {
    if ((ch==0)||(ch==1)) {
        ppmNetHandle denNet = (ch == 0) ? handles.DMA0EN : handles.DMA1EN;

        Uns32 current = ppmReadNet(denNet);
        if (PSE_DIAG_MEDIUM)
            bhmMessage("I", PREFIX"_DMAEN", "Channel %d (%d) : Set DMAEN %d", ch, current, value);
        if (value != current) {
            ppmWriteNet(denNet, value);
        }
    }
}

PPM_REG_WRITE_CB(writeDMAMCL) {
    // YOUR CODE HERE (writeDMAMCL)
    // Can only change inactive channels
    Uns8 i;
    Uns16 mask = 0;
    Uns8 current = *(Uns8*)user;

    // Only inactive channels can be changed
    for (i=0;i<NUM_CHANNELS;i++) {
        if (!DMAState.ch[i].busy) {
            mask |= 1<<i;
        }
    }
    Uns8 new = data & mask;
    if (PSE_DIAG_LOW)
        bhmMessage("I", PREFIX"_DMAMCL", "Channel Mode Control update 0x%02x mask 0x%02x dmamcl 0x%02x->0x%02x", data, mask, current,new);

    *(Uns8*)user = new;
    // If the channel has gone from disabled to enabled we need to start the DMA
    // TODO: channels started in priority order?
    for (i=0;i<NUM_CHANNELS;i++) {
        if (!(current & (1<<i)) && (new & (1<<i))) {
            if (PSE_DIAG_HIGH)
                bhmMessage("I", PREFIX"_DMAEN", "Channel %d Enabled", i);
            setADCDMAEnable(i, 1);
            bhmTriggerEvent(DMAState.ch[i].enable);
        } else if (!(new & (1<<i))) {
           setADCDMAEnable(i, 0);
        }
    }
}

PPM_REG_WRITE_CB(writeDMASL) {
    // YOUR CODE HERE (writeDMASL)
    Uns8 current = *(Uns8*)user;
    // Can only clear (not set)
    current ^= data & 0xff;
    if (PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX"_DMASLW", "DMASL write 0x%02x, value 0x%02x->0x%02x", data, *(Uns8*)user, current);
    *(Uns8*)user = current;
}

PPM_REG_WRITE_CB(writeDMAWC0) {
    // YOUR CODE HERE (writeDMAWC0)
    if (PSE_DIAG_HIGH)
        bhmMessage("W", PREFIX"_DMAWC0W", "No Behaviour Implemented");
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writeDMAWC1) {
    // YOUR CODE HERE (writeDMAWC1)
    if (PSE_DIAG_HIGH)
        bhmMessage("W", PREFIX"_DMAWC1W", "No Behaviour Implemented");
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writeDTCR0) {
    *(Uns8*)user = data;
    if (data) {
        if (PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX"_DTCR0", "Set Count %d", data);
        bhmTriggerEvent(DMAState.ch[0].transfer);
    }
}

PPM_NBYTE_WRITE_CB(writeDTCR) {
    if(bytes != 1) {
        bhmMessage("E", "PPM_WNB", "Only 1 byte access permitted");
        return;
    }
    Uns32 reg   = (offset-(0x24+0x1c))/0x1;
    DMAP1_abb_data.DTCR[reg].value = *(Uns8*)data;

    if (*(Uns8*)data && (reg == 0)) {
        if (PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX"_DTCR0", "Set Count %d", *(Uns8*)data);
        bhmTriggerEvent(DMAState.ch[0].transfer);
    }
}

PPM_NBYTE_WRITE_CB(writeDTFR) {
    if(bytes != 1) {
        bhmMessage("E", "PPM_WNB", "Only 1 byte access permitted");
        return;
    }
    Uns32 reg   = (offset-(0x24+0x5c))/0x1;
    DMAP1_abb_data.DTFR[reg].value = *(Uns8*)data;
}

PPM_NBYTE_WRITE_CB(writeMAR) {
    if(bytes != 2) {
        bhmMessage("E", "PPM_WNB", "Only 2 byte access permitted");
        return;
    }
    Uns32 reg   = (offset-(0x0+0x0))/0x2;
    if(*(Uns16*)data && (reg == 0)) {
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX"_MAR0", "Target address written (0x%04x)", *(Uns16*)data);
    }
    DMAP1_abw_data.MAR[reg].value = *(Uns16*)data;
}


PPM_NBYTE_WRITE_CB(writeSAR) {
    if (PSE_DIAG_HIGH)
        bhmMessage("W", PREFIX"_SARW", "No Behaviour Implemented");

    if(bytes != 1) {
        bhmMessage("E", "PPM_WNB", "Only 1 byte access permitted");
        return;
    }
    Uns32 reg   = (offset-(0x24+0x0))/0x1;
    DMAP1_abb_data.SAR[reg].value = (DMAP1_abb_data.SAR[reg].value & 0xf0) | (*(Uns8*)data & 0xf);
}


PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    userInit();

}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}


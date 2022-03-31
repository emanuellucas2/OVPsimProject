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
#include "user_tcd.h"
#include "user_func.h"


// Provide a user friendly name for our register structure.
#define dmaRegisters bport1_ab_dataT

#define MAX_CHAN_NUM (31)

// Mapping of the dma registers and the per channel priority and TCD registers.
dmaRegisters *chReg;
dma_8bit_regsT dma8Bit;
dma_tcdT tcdReg[32];

typedef struct {
    Uns32               cancel;
    bhmThreadHandle     thread;
    bhmEventHandle      start;
} channelState, *channelStateP;

static channelState chState;
static char periphName[] = "KinetisDMA";

////////////////////////////////////////////////////////////////////////////////
// Internal Functions
////////////////////////////////////////////////////////////////////////////////

static void resetTCD(void)
{
    int ii;
    memset(tcdReg, 0, sizeof(dma_tcdT) * 32);

    for (ii = 0; ii < 32; ii++)
    {
        // PRE Per Section: 22.3.16, Reset values for CHPRI and GRPRI are the
        //  corresponding channel number: ie. for ch=32 GRPRI = 0b01, CHPRI = 0b1111
        tcdReg[ii].DMA_DCHPRI.value = (Uns8) ii;
        tcdReg[ii].dmaInterrupt = handles.dmaInterrupt_ch[ii];
    }
}

////////////////////////////////////////////////////////////////////////////////
// Set/Clear all bits in the ERR, EEI, ERQ, INT registers.
////////////////////////////////////////////////////////////////////////////////
static void setAllBits(Uns32 *reg, Uns32 value, const char *regName)
{
    if (value == 1)
    {
        if (diagnosticLevel >= 3)
            bhmMessage("I", "KinetisDMA", "Set all %s bits", regName);

        *reg = 0xffffffff;
    } else if (value == 0)
    {
        if (diagnosticLevel >= 3)
            bhmMessage("I", "KinetisDMA", "Clear all %s bits", regName);

        *reg = 0x0;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Set/Clear a single bit in the ERR, EEI, ERQ, INT registers.
////////////////////////////////////////////////////////////////////////////////
static void setBits(Uns32 *reg, Uns32 chNum, Uns32 value, const char *regName)
{
    Uns32 bitMask = (1 << chNum);
        
    if (value == 1)
    {
        if (diagnosticLevel >= 3)
            bhmMessage("I", "KinetisDMA", "Set %s bit 0x%x", regName, chNum);

        *reg |= bitMask;
    } else if (value == 0)
    {
        if (diagnosticLevel >= 3)
            bhmMessage("I", "KinetisDMA", "Clear %s bit 0x%x", regName, chNum);

        *reg &= ~bitMask;
    }
}

// return 1 if the channe is enabled, 0 otherwise.
static int isBitSet(Uns32 value, Uns32 chNum)
{
    Uns32 bitMask = 0x1 << chNum;
    return (value & bitMask);
}
//
// Pull the correct number of bytes to transfer out of the TCD register.
// Need to look at the EMLM value to determine if we are using Minor Loop
static Uns32 getNumBytes(Uns32 chNum)
{
    Uns32 retVal = 0;

    if (chReg->CR.bits.EMLM)
    {
        if ((tcdReg[chNum].TCD_NBYTES.bits.MLOFFNO.SMLOE == 0) &&
           (tcdReg[chNum].TCD_NBYTES.bits.MLOFFNO.DMLOE == 0))
        {
            retVal = tcdReg[chNum].TCD_NBYTES.bits.MLOFFNO.NBYTES;
        } else
        {
            retVal = tcdReg[chNum].TCD_NBYTES.bits.MLOFFYES.NBYTES;
        }
    } else
    {
        retVal = tcdReg[chNum].TCD_NBYTES.bits.MLNO.NBYTES;
    }

    return retVal;
}

////////////////////////////////
// DMA Request handling.
////////////////////////////////
static void processDMARequest(Uns32 chNum)
{
    if (diagnosticLevel >= 2)
        bhmMessage("I", periphName, "DMA requested on channel = %d", chNum);

    if (addRequest(chNum))
    {
        bhmMessage("W", periphName, "Unable to add to request queue");
        return;
    }

    bhmTriggerEvent(chState.start);
}

PPM_NET_CB(DMARequest) {
    Uns32 chNum = value; // convert the name for readability.
    if ((chNum < 0) || (chNum > 31))
    {
        bhmMessage("W", periphName, "DMA requested channel out of range: value = %d", chNum);
        return;
    }

    // If we get a hardware request, the channel's ERQ bit must be enabeled to trigger
    // a DMA request.
    if (isBitSet(chReg->ERQ.value, chNum))
    {
        processDMARequest(chNum);
    } else
    {
        bhmMessage("W", periphName, "DMA channel %d not enabled", chNum);
    }
}

static void checkCSRReg(Uns32 chNum)
{
    if (tcdReg[chNum].TCD_CSR.bits.START)
    {
        processDMARequest(chNum);
    }
}


static void dmaTCDSetStart(Uns32 allOrOne, Uns32 chNum)
{
    Uns32 ii;

    if (allOrOne)
    {
        for(ii = 0; ii < 32; ii++)
        {
            tcdReg[ii].TCD_CSR.bits.START = 1;
            checkCSRReg(ii);
        }
    } else
    {
        tcdReg[chNum].TCD_CSR.bits.START = 1;
        checkCSRReg(chNum);
    }
}

static void dmaTCDClearDone(Uns32 allOrOne, Uns32 chNum)
{
    Uns32 ii;

    if (allOrOne)
    {
        for(ii = 0; ii < 32; ii++)
        {
            tcdReg[ii].TCD_CSR.bits.DONE = 0;
            checkCSRReg(ii);
        }
    } else
    {
        tcdReg[chNum].TCD_CSR.bits.DONE = 0;
        checkCSRReg(chNum);
    }
}


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// Callback stubs ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////
// General 32 bit Register Callbacks (ERQ, EEI, INT, ERR, HRS)
////////////////////////////////
PPM_REG_READ_CB(regRead32) {
    Uns32 offset = PTR_TO_UNS32(addr) - PTR_TO_UNS32(handles.bport1);

    if (diagnosticLevel >= 3)
        bhmMessage("I", periphName, "Read Generic 32: offset = 0x%x  size = %d val = 0x%x", offset, bytes, *(Uns32*)user);

    return *(Uns32*)user;
}

PPM_REG_WRITE_CB(regWrite32) {
    Uns32 offset = PTR_TO_UNS32(addr) - PTR_TO_UNS32(handles.bport1);

    if (diagnosticLevel >= 3)
        bhmMessage("I", periphName, "Write Generic 32: offset = 0x%x  size = %d val = 0x%x", offset, bytes, data);
    *(Uns32*)user = (*(Uns32*)user & 0x0) | (data & 0xffffffff);
}

PPM_REG_WRITE_CB(regWrite1c) {
    Uns32 offset = PTR_TO_UNS32(addr) - PTR_TO_UNS32(handles.bport1);

    if (diagnosticLevel >= 3)
        bhmMessage("I", "KinetisDMA", "Write 1clear: offset = 0x%x  size = %d val = 0x%x", offset, bytes, data);

    *(Uns32*)user = (*(Uns32*)user & ~data);
}

////////////////////////////////
// ES Register Callbacks
////////////////////////////////
PPM_REG_READ_CB(regReadES) {
    // YOUR CODE HERE (regReadES)
    if (diagnosticLevel >= 3)
        bhmMessage("I", "KinetisDMA", "Read ES");
    return *(Uns32*)user;
}

////////////////////////////////
// CR Register Callbacks
////////////////////////////////
PPM_REG_READ_CB(regReadCR) {
    if (diagnosticLevel >= 3)
        bhmMessage("I", "KinetisDMA", "Read CR Val = 0x%x", *(Uns32*) user);
    return *(Uns32*)user;
}

PPM_REG_WRITE_CB(regWriteCR) {
    Uns32 offset = PTR_TO_UNS32(addr) - PTR_TO_UNS32(handles.bport1);

    if (diagnosticLevel >= 3)
        bhmMessage("I", "KinetisDMA", "Write CR: offset = 0x%x  size = %d val = 0x%x", offset, bytes, data);

    *(Uns32*)user = (*(Uns32*)user & 0xfffcf001) | (data & 0x30ffe);

    if ((data & 0x20000) || (data & 0x10000))
    {
        // Per Section: 22.3.1, need to cancel any active transfers. Reset the CX bit when completed.
        // Make sure we have active items in the queue before we try to cancel them
        if (data & 0x10000)
        {
            chReg->CR.bits.ECX = (unsigned) 0;
            if (! isEmptyQue())
                chState.cancel = 2;
        } else
        {
            chReg->CR.bits.CX = (unsigned) 0;
            if (! isEmptyQue())
                chState.cancel = 1;
        }
    }
}

////////////////////////////////
// DMA 8bit registers.
////////////////////////////////
PPM_REG_READ_CB(regReadZero) {
    // These always return 0.
    return *(Uns32*) 0x0;
}

PPM_REG_WRITE_CB(regSetGroup) {
    Uns32 offset = PTR_TO_UNS32(addr) - PTR_TO_UNS32(handles.bport1);

    if (bytes != 1)
    {
        bhmMessage("W", "KinetasDMA", "Attempting to write %d bytes to 1 byte register. offset = 0x%x", bytes, offset);
    }

    if (diagnosticLevel >= 3)
        bhmMessage("I", "KinetisDMA", "SetGroup: offset = 0x%x  size = %d val = 0x%x", offset, bytes, data);

    switch (offset) {
        case 0x18:
            dma8Bit.DMA_CEEI.value = (data & 0xdf);
            if (data >= 0x80) break;

            if (data == 0x40)
                setAllBits(&(chReg->EEI.value), 0, "EEI");
            else
                setBits(&(chReg->EEI.value), data, 0, "EEI");
            break;
        case 0x19:
            dma8Bit.DMA_SEEI.value = (data & 0xdf);
            if (data >= 0x80) break;
            if (data == 0x40)
                setAllBits(&(chReg->EEI.value), 1, "EEI");
            else
                setBits(&(chReg->EEI.value), data, 1, "EEI");
            break;
        case 0x1a:
            dma8Bit.DMA_CERQ.value = (data & 0xdf);
            if (data >= 0x80) break;
            if (data == 0x40)
                setAllBits(&(chReg->ERQ.value), 0, "ERQ");
            else
                setBits(&(chReg->ERQ.value), data, 0, "ERQ");
            break;
        case 0x1b:
            dma8Bit.DMA_SERQ.value = (data & 0xdf);
            if (data >= 0x80) break;
            if (data == 0x40)
                setAllBits(&(chReg->ERQ.value), 1, "ERQ");
            else
                setBits(&(chReg->ERQ.value), data, 1, "ERQ");
            break;
        case 0x1c:
            dma8Bit.DMA_CDNE.value = (data & 0xdf);
            if (data >= 0x80) break;
            dmaTCDClearDone((data & 0x40), (data & 0x1f));
            break;
        case 0x1d:
            dma8Bit.DMA_SSRT.value = (data & 0xdf);
            if (data >= 0x80) break;
            dmaTCDSetStart((data & 0x40), (data & 0x1f));
            break;
        case 0x1e:
            dma8Bit.DMA_CERR.value = (data & 0xdf);
            if (data >= 0x80) break;
            if (data == 0x40)
                setAllBits(&(chReg->ERR.value), 0, "ERR");
            else
                setBits(&(chReg->ERR.value), data, 0, "ERR");
            break;
        case 0x1f:
            dma8Bit.DMA_CINT.value = (data & 0xdf);
            if (data >= 0x80) break;
            if (data == 0x40)
                setAllBits(&(chReg->INT.value), 0, "INT");
            else
                setBits(&(chReg->INT.value), data, 0, "INT");
            break;
    }
}

////////////////////////////////
// Channel Priority Register Callbacks.
////////////////////////////////
//
// Channel numbers are reverse of the offset. So 0x100 is 3, while 0x103 is 0. Need to reverse these.

Uns32 regGetCHPRIChNum(Uns32 offset)
{
    int chMod[4] = {3, 1, -1, -3};
    int locOffset = offset - 0x100;

    return (locOffset + chMod[locOffset % 4]);
}

PPM_REG_READ_CB(regReadCHPRI) {
    Uns32 offset = PTR_TO_UNS32(addr) - PTR_TO_UNS32(handles.bport1);
    Uns32 chNum = regGetCHPRIChNum(offset); 
    Uns32 retVal = 0;

    if (chNum > MAX_CHAN_NUM)
    {
        bhmMessage("W", "KinetasDMA", "Ch. Priority Register: invalid chNum derived %d\n", chNum);
        retVal = (Uns32) -1;
    } else
    {
        if (bytes == 1)
        {
            retVal = tcdReg[chNum].DMA_DCHPRI.value;
            if (diagnosticLevel >= 3)
                bhmMessage("I", "KinetisDMA", "Read Ch. Priority: ch = %d val = 0x%x", chNum, retVal);
        } else
        {
            bhmMessage("W", "KinetasDMA", "Ch. Priority Register: Reading %d bytes to 1 byte register. ch = %d, offset = 0x%x", bytes, chNum, offset);
            retVal = (Uns32) -1;
        } 
    }

    return retVal;
}

PPM_REG_WRITE_CB(regWriteCHPRI) {
    Uns32 offset = PTR_TO_UNS32(addr) - PTR_TO_UNS32(handles.bport1);
    Uns32 chNum = regGetCHPRIChNum(offset); 

    if (bytes != 1)
        bhmMessage("W", "KinetasDMA", "Ch. Priority Register: Writing %d bytes to 1 byte register. ch = %d, offset = 0x%x", bytes, chNum, offset);

    if (chNum > MAX_CHAN_NUM)
    {
        bhmMessage("W", "KinetasDMA", "Ch. Priority Register: invalid chNum derived %d\n", chNum);
    } else
    {
        tcdReg[chNum].DMA_DCHPRI.value = (data & 0xcf);
        if (diagnosticLevel >= 3)
            bhmMessage("I", "KinetisDMA", "Write Ch. Priority: ch = %d newVal = 0x%x", chNum, data);
    }
}

////////////////////////////////
// TCD Register Callbacks
////////////////////////////////
PPM_REG_READ_CB(regReadTCD) {
    Uns32 offset = PTR_TO_UNS32(addr) - PTR_TO_UNS32(handles.bport1);
    Uns32 chNum = (offset - 0x1000) / 32;
    Uns32 baseOffset = (offset - 0x1000) - (32 * chNum);
    Uns32 retVal = 0;

    if (bytes != 4)
    {
        bhmMessage("W", periphName, "Attempting to read %d bytes on 4 byte register. Ch = %d, offset = 0x%x", bytes, chNum, baseOffset);
        return (Uns32) -1;
    }

    switch (baseOffset)
    {
        case 0x0: // SADDR
            retVal = tcdReg[chNum].TCD_SADDR.value;
            if (diagnosticLevel >= 3)
                bhmMessage("I", "KinetisDMA", "Read SADDR Ch = %d  size = %d val = 0x%x", chNum, bytes, retVal);
            break;
        case 0x8: // NBYTES
            retVal = tcdReg[chNum].TCD_NBYTES.value;
            if (diagnosticLevel >= 3)
                bhmMessage("I", "KinetisDMA", "Read NBYTES Ch = %d  size = %d val = 0x%x", chNum, bytes, retVal);
            break;
        case 0xc: // SLAST
            retVal = tcdReg[chNum].TCD_SLAST.value;
            if (diagnosticLevel >= 3)
                bhmMessage("I", "KinetisDMA", "Read SLAST Ch = %d  size = %d val = 0x%x", chNum, bytes, retVal);
            break;
        case 0x10: // DADDR
            retVal = tcdReg[chNum].TCD_DADDR.value;
            if (diagnosticLevel >= 3)
                bhmMessage("I", "KinetisDMA", "Read DADDR Ch = %d  size = %d val = 0x%x", chNum, bytes, retVal);
            break;
        case 0x18: // DLASTSGA
            retVal = tcdReg[chNum].TCD_DLASTSGA.value;
            if (diagnosticLevel >= 3)
                bhmMessage("I", "KinetisDMA", "Read DLASTSGA Ch = %d  size = %d val = 0x%x", chNum, bytes, retVal);
            break;
        default:
            bhmMessage("W", periphName, "Unhandled address in TCD block");
            break;  
    }

    return retVal;
}

PPM_REG_WRITE_CB(regWriteTCD) {
    Uns32 offset = PTR_TO_UNS32(addr) - PTR_TO_UNS32(handles.bport1);
    Uns32 chNum = (offset - 0x1000) / 32;
    Uns32 baseOffset = (offset - 0x1000) - (32 * chNum);

    if (bytes != 4)
        bhmMessage("W", periphName, "Illegal access on 32 bit register");

    switch (baseOffset)
    {
        case 0x0: // SADDR
            tcdReg[chNum].TCD_SADDR.value = (data & 0xffffffff);
            if (diagnosticLevel >= 3)
                bhmMessage("I", "KinetisDMA", "Write SADDR Ch = %d  size = %d val = 0x%x", chNum, bytes, data);
            break;
        case 0x8: // NBYTES
            tcdReg[chNum].TCD_NBYTES.value = (data & 0xffffffff);
            if (diagnosticLevel >= 3)
                bhmMessage("I", "KinetisDMA", "Write NBYTES Ch = %d  size = %d val = 0x%x", chNum, bytes, data);
            break;
        case 0xc: // SLAST
            tcdReg[chNum].TCD_SLAST.value = (data & 0xffffffff);
            if (diagnosticLevel >= 3)
                bhmMessage("I", "KinetisDMA", "Write SLAST Ch = %d  size = %d val = 0x%x", chNum, bytes, data);
            break;
        case 0x10: // DADDR
            tcdReg[chNum].TCD_DADDR.value = (data & 0xffffffff);
            if (diagnosticLevel >= 3)
                bhmMessage("I", "KinetisDMA", "Write DADDR Ch = %d  size = %d val = 0x%x", chNum, bytes, data);
            break;
        case 0x18: // DLASTSGA
            tcdReg[chNum].TCD_DLASTSGA.value = (data & 0xffffffff);
            if (diagnosticLevel >= 3)
                bhmMessage("I", "KinetisDMA", "Write DLASTSGA Ch = %d  size = %d val = 0x%x", chNum, bytes, data);
            break;
        default:
            bhmMessage("W", periphName, "Unhandled address in TCD block");
            break;  
    }
}

////////////////////////////////
// TCD 16 bit  Register Callbacks
////////////////////////////////
PPM_REG_READ_CB(regReadTCD16) {
    Uns32 retVal = 0;
    Uns32 offset = PTR_TO_UNS32(addr) - PTR_TO_UNS32(handles.bport1);
    Uns32 chNum = (offset - 0x1000) / 32;
    Uns32 baseOffset = (offset - 0x1000) - (32 * chNum);
    
    if (bytes == 2)
    {
        switch (baseOffset)
        {
            case 0x4:
                retVal = tcdReg[chNum].TCD_SOFF.value;
                if (diagnosticLevel >= 3)
                    bhmMessage("I", "KinetisDMA", "Read SOFF Ch = %d  size = %d val = 0x%x", chNum, bytes, retVal);
                break;
            case 0x6:
                retVal = tcdReg[chNum].TCD_ATTR.value;
                if (diagnosticLevel >= 3)
                    bhmMessage("I", "KinetisDMA", "Read ATTR Ch = %d  size = %d val = 0x%x", chNum, bytes, retVal);
                break;
            case 0x14:
                retVal = tcdReg[chNum].TCD_DOFF.value;
                if (diagnosticLevel >= 3)
                    bhmMessage("I", "KinetisDMA", "Read DOFF Ch = %d  size = %d val = 0x%x", chNum, bytes, retVal);
                break;
            case 0x16:
                retVal = tcdReg[chNum].TCD_CITER.value;
                if (diagnosticLevel >= 3)
                    bhmMessage("I", "KinetisDMA", "Read CITER Ch = %d  size = %d val = 0x%x", chNum, bytes, retVal);
            case 0x1c:
                retVal = tcdReg[chNum].TCD_CSR.value;
                if (diagnosticLevel >= 3)
                    bhmMessage("I", periphName, "Read CSR: bytes = %d, val = 0x%x", bytes, retVal);
                break;
            case 0x1e:
                retVal = tcdReg[chNum].TCD_BITER.value;
                if (diagnosticLevel >= 3)
                    bhmMessage("I", periphName, "Read BITER: bytes = %d, val = 0x%x", bytes, retVal);
                break;
            default:
                bhmMessage("W", periphName, "Unhandled address in TCD 16 bit read");
        } 
    } else
    {
        bhmMessage("W", periphName, "Attempting to read %d bytes from 2 byte register: ch = %d, offset = 0x%d",
                        bytes, chNum, offset);
        retVal = (Uns32) -1;
    }

    return retVal;
}

PPM_REG_WRITE_CB(regWriteTCD16) {
    Uns32 offset = PTR_TO_UNS32(addr) - PTR_TO_UNS32(handles.bport1);
    Uns32 chNum = (offset - 0x1000) / 32;
    Uns32 baseOffset = (offset - 0x1000) - (32 * chNum);

    if (bytes == 2)
    {
        switch (baseOffset)
        {
            case 0x4:
                tcdReg[chNum].TCD_SOFF.value = (data & 0xffff);
                if (diagnosticLevel >= 3)
                    bhmMessage("I", "KinetisDMA", "Write SOFF Ch = %d  size = %d val = 0x%x", chNum, bytes, data);
                break;
            case 0x6:
                tcdReg[chNum].TCD_ATTR.value = (data & 0xffff);
                if (diagnosticLevel >= 3)
                    bhmMessage("I", "KinetisDMA", "Write ATTR Ch = %d  size = %d val = 0x%x", chNum, bytes, data);
                break;
            case 0x14:
                tcdReg[chNum].TCD_DOFF.value = (data & 0xffff);
                if (diagnosticLevel >= 3)
                    bhmMessage("I", "KinetisDMA", "Write DOFF Ch = %d  size = %d val = 0x%x", chNum, bytes, data);
                break;
            case 0x16:
                if (data & 0x8000)
                    tcdReg[chNum].TCD_CITER.value = (data & 0xbfff);
                else
                    tcdReg[chNum].TCD_CITER.value = (data & 0xffff);
                if (diagnosticLevel >= 3)    
                    bhmMessage("I", "KinetisDMA", "Write CITER Ch = %d  size = %d val = 0x%x", chNum, bytes, data);
                break;
            case 0x1c:
                tcdReg[chNum].TCD_CSR.value = (data & 0xdfff);
                if (diagnosticLevel >= 3)
                    bhmMessage("I", "KinetisDMA", "Write CSR Ch = %d  size = %d val = 0x%x", chNum, bytes, data);
                checkCSRReg(chNum);
                break;
            case 0x1e:
                if (data & 0x8000)
                    tcdReg[chNum].TCD_BITER.value = (data & 0xbfff);
                else
                    tcdReg[chNum].TCD_BITER.value = (data & 0xffff);
                if (diagnosticLevel >= 3)
                    bhmMessage("I", "KinetisDMA", "Write BITER Ch = %d  size = %d val = 0x%x", chNum, bytes, data);
                break;
        } 
    } else
    {
        bhmMessage("W", "KinetisDMA", "Attempting to write %d bytes to 2 byte register, Ch = %d  offset = 0x%d", 
                bytes, chNum, offset);
    }
}

//////////////////////////////////////////////
//
//////////////////////////////////////////////
static void sendDMADoneInterrupt(Uns32 chNum)
{
    if (tcdReg[chNum].TCD_CSR.bits.INTMAJOR == 1)
    {
        if (diagnosticLevel >= 2)
            bhmMessage("I", periphName, "Send DMA Interrupt for channel = %d", chNum);

        ppmWriteNet(tcdReg[chNum].dmaInterrupt, 1);
        setBits(&(chReg->INT.value), chNum, 1, "INT");
    }
}

static void sendErrorInterrupt(Uns32 chNum)
{
    if (isBitSet(chReg->EEI.value, chNum))
    {
        ppmWriteNet(handles.errorInterrupt, 1);
    }
}

//////////////////////////////////////////////
// Verify that the address for src and destination make sense for the transfer sizes.
// set error bits if errors found.
//////////////////////////////////////////////
static int verifyChannel(Uns32 chNum)
{
    int retVal = 1; // Assume no errors.
    Uns32 sMod = 0;
    Uns32 dMod = 0;

    switch (tcdReg[chNum].TCD_ATTR.bits.SSIZE)
    {
        case 0x0:
            sMod = 1;
            break;
        case 0x1:
        case 0x2:
            sMod = 2;
            break;
        case 0x4:
            sMod = 4;
            break;
        default:
            chReg->ES.bits.ERRCHN = chNum;
            chReg->ES.bits.SAE = 1;
            chReg->ES.bits.VLD = 1;
            return 0;   // Exit on error, all others will show errors too.
    }

    switch (tcdReg[chNum].TCD_ATTR.bits.DSIZE)
    {
        case 0x0:
            dMod = 1;
            break;
        case 0x1:
        case 0x2:
            dMod = 2;
            break;
        case 0x4:
            dMod = 4;
            break;
        default:
            chReg->ES.bits.ERRCHN = chNum;
            chReg->ES.bits.DAE = 1;
            chReg->ES.bits.VLD = 1;
            return 0;   // Exit on error, all others will show errors too.
    }

    if ((tcdReg[chNum].TCD_SADDR.value % sMod) != 0)
    {
        chReg->ES.bits.SAE = 1;
        retVal = 0;
    }

    if ((tcdReg[chNum].TCD_SOFF.value % sMod) != 0)
    {
        chReg->ES.bits.SOE = 1;
        retVal = 0;
    }

    if ((tcdReg[chNum].TCD_DADDR.value % dMod) != 0)
    {
        chReg->ES.bits.DAE = 1;
        retVal = 0;
    }

    if ((tcdReg[chNum].TCD_DOFF.value % dMod) != 0)
    {
        chReg->ES.bits.DOE = 1;
        retVal = 0;
    }

    Uns32 numBytes = getNumBytes(chNum);
    if (((numBytes % sMod) != 0) && ((numBytes % dMod) != 0))
    {
        chReg->ES.bits.NCE = 1;
        retVal = 0;
    }

    // Set the channel number of the last error if one occurred.
    if (retVal == 0)
    {
        chReg->ES.bits.ERRCHN = chNum;
        chReg->ES.bits.VLD = 1;
    }

    return retVal;
}

static void doTransfer(Uns32 chNum, dma_tcdP xferTcd, Uns32 readSize, Uns32 numBytes)
{
    Uns8 buf[4];
    Uns32 byteCnt = 0;
    Uns32 readIdx;
    Uns32 writeIdx;
    Uns32 writeSize = 0;

    // Determine the destination size, source size is passed in.
    switch (xferTcd->TCD_ATTR.bits.DSIZE)
    {
        case 0x0:  // 8 - bit dest.
            writeSize = 1;
            if (diagnosticLevel >= 2)
                bhmMessage("I", periphName, "XFER: %d Bytes to %d bytes transfer: Ch = %d, Nbytes=%d", readSize, writeSize, chNum, numBytes);
            break;
        case 0x1:  // 16 - bit dest.
        case 0x4:  // 16 - bit burst:
            writeSize = 2;
            if (diagnosticLevel >= 2)
                bhmMessage("I", periphName, "XFER: %d Bytes to %d bytes transfer: Ch = %d, Nbytes=%d", readSize, writeSize, chNum, numBytes);
            break;
        case 0x2:  // 32 - bit dest.
            writeSize = 4;
            if (diagnosticLevel >= 2)
                bhmMessage("I", periphName, "XFER: %d Bytes to %d bytes transfer: Ch = %d, Nbytes=%d", readSize, writeSize, chNum, numBytes);
            break;
        default:
            break; // should be caught in verify sections.
    }

    while (byteCnt < numBytes)
    {
        if (diagnosticLevel >= 3)
            bhmMessage("I", periphName, "LOOP: Write start: bytes remaining: %d", numBytes - byteCnt);

        for (readIdx = 0; readIdx < writeSize;)
        {
            if (diagnosticLevel >= 3)
                bhmMessage("I", periphName, "LOOP: Reading %d bytes, srcAddr = 0x%x", readSize, xferTcd->TCD_SADDR.value);
            ppmReadAddressSpace(handles.MREAD, xferTcd->TCD_SADDR.value, readSize, &(buf[readIdx]));
            xferTcd->TCD_SADDR.value += xferTcd->TCD_SOFF.value;
            byteCnt += readSize;
            readIdx += readSize;
        }

        for (writeIdx = 0; writeIdx < readSize;)
        {
            if (diagnosticLevel >= 3)
                bhmMessage("I", periphName, "LOOP: Writing %d bytes, destAddr = 0x%x", writeSize, xferTcd->TCD_DADDR.value);
            ppmWriteAddressSpace(handles.MWRITE, xferTcd->TCD_DADDR.value, writeSize, &(buf[writeIdx]));
            xferTcd->TCD_DADDR.value += xferTcd->TCD_DOFF.value;
            writeIdx += writeSize;
        }

        if (diagnosticLevel >= 3)
            bhmMessage("I", periphName, "LOOP: Write Complete");
    }
}


static void DMA_Thread(void *user)
{
    for (;;)
    {
        if (diagnosticLevel >= 2)
            bhmMessage("I", "KinetisDMA", "DMA_Thread waiting...");

        bhmWaitEvent(chState.start);
        if (diagnosticLevel >= 2)
            bhmMessage("I", "KinetisDMA", "DMA_Thread triggered...");

        // A channel has requested service.
        Uns32 chNum = 0;
        dma_tcdT xferTcd;
        Uns32 numBytes;

        while (! isEmptyQue())
        {
            // Check to see if we have recieved transfer cancel request.
            if (chState.cancel > 0)
            {
                initRequestQue();

                // ECX transfer with error flags.
                if (chState.cancel == 1)
                {
                    chReg->ES.bits.ERRCHN = chNum;
                    chReg->ES.bits.ECX = 1;
                    chReg->ES.bits.VLD = 1;
                }
                chState.cancel = 0;
                continue;
            }

            if (popRequest(&chNum) != 0)
            {
                bhmMessage("W", periphName, "Error: No DMA Channel available on request queue");
                break;
            }

            if (diagnosticLevel >= 3)
                bhmMessage("I", periphName, "Servicing channel: %d", chNum);
    
            // Verify Channel TCD Data.
            if (! verifyChannel(chNum))
            {
                if (diagnosticLevel >= 2)
                    bhmMessage("W", periphName, "Channel configuration error: ES=0x%x", chReg->ES.value);

                sendErrorInterrupt(chNum);
                setBits(&(chReg->ERR.value), chNum, 1, "INT");
                tcdReg[chNum].TCD_CSR.bits.ACTIVE = 0;
                tcdReg[chNum].TCD_CSR.bits.DONE = 1;
                continue;
            }

            // Set the apprioriate csr Bits.
            tcdReg[chNum].TCD_CSR.bits.DONE = 0;
            tcdReg[chNum].TCD_CSR.bits.START = 0;
            tcdReg[chNum].TCD_CSR.bits.ACTIVE = 1;

            numBytes = getNumBytes(chNum);
            memcpy(&xferTcd, &(tcdReg[chNum]), sizeof(dma_tcdT));

            switch (tcdReg[chNum].TCD_ATTR.bits.SSIZE)
            {
                case 0x0:  // 8 - bit src.
                    doTransfer(chNum, &xferTcd, 1, numBytes);
                    break;
                case 0x1:  // 16 - bit src.
                case 0x4:  // 16 - bit burst:
                    doTransfer(chNum, &xferTcd, 2, numBytes);
                    break;
                case 0x2:  // 32 - bit src.
                    doTransfer(chNum, &xferTcd, 4, numBytes);
                    break;
                default:
                    break; // should be caught in verify sections.
            }

            // Set the next address value.
            tcdReg[chNum].TCD_SADDR.value = xferTcd.TCD_SADDR.value + xferTcd.TCD_SLAST.value;  
            tcdReg[chNum].TCD_DADDR.value = xferTcd.TCD_DADDR.value + xferTcd.TCD_DLASTSGA.value;   

            // TODO: Update CITER/BITER.

            tcdReg[chNum].TCD_CSR.bits.ACTIVE = 0;
            tcdReg[chNum].TCD_CSR.bits.DONE = 1;
            
            sendDMADoneInterrupt(chNum);
        }
    }
}

// Reset Net asserted, shut down any current transfers and reset 
// all of the required values.
PPM_NET_CB(DMAReset) {
    bhmMessage("I", periphName, " In DMAReset");

    if (! isEmptyQue())
    {
        chState.cancel = 2; // Shutdown any current transfer.
        bhmWaitDelay(5); // let any current transfers complete.
    }

    dma8Bit.DMA_SERQ.value = 0;
    dma8Bit.DMA_CERQ.value = 0;
    dma8Bit.DMA_SEEI.value = 0;
    dma8Bit.DMA_CEEI.value = 0;
    dma8Bit.DMA_CINT.value = 0;
    dma8Bit.DMA_CERR.value = 0;
    dma8Bit.DMA_SSRT.value = 0;
    dma8Bit.DMA_CDNE.value = 0;
    
    reset_Reset(1,0);
    resetTCD();
}

void userInit(void)
{
    char threadName[32];

    if (diagnosticLevel >= 2)
        bhmMessage("I", periphName, "User Initialization");

    initRequestQue();
    chReg =  (dmaRegisters *) &bport1_ab_data;
    resetTCD();
    memset(&dma8Bit, 0, sizeof(dma_8bit_regsT));

    // Setup control thread.
    chState.cancel = 0;
    chState.start = bhmCreateEvent();
    sprintf(threadName, "dmaCtrl");
    chState.thread = bhmCreateThread(
                DMA_Thread,
                (void*) 0,
                threadName,
                0
            );

}


PPM_CONSTRUCTOR_CB(constructor) {
    // YOUR CODE HERE (pre constructor)
    periphConstructor();

    // YOUR CODE HERE (post constructor)
    userInit();
}



// Save / restore callbacks

PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}


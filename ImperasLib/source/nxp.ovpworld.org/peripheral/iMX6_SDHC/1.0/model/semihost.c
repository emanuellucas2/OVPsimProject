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


#include <string.h>
#include <stdlib.h>
#include <unistd.h>

// VMI area includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiPSE.h"
#include "vmi/vmiRt.h"

// model includes
#include "../pse/pse.igen.h"
#define BPORT1 0
#include "../pse/pse.macros.igen.h"

#include "sd.h"

Uns32 byteCntCounter = 0;

typedef struct vmiosObjectS  {

    // PSE data domain (passed to read and write callbacks)
    memDomainP        pseDomain;

    memDomainP        portDomain;

    // diagnostics enabled
    Uns32             diag;

    // alias of internal structure of registers
    bport1_ab_dataT   bportRegs;
    Uns32            *fifoBuffer;

    Int32             fifo_pos;
    Int32             fifo_len;

    Uns32             fifo[FIFO_LEN];

    // sd card state
    SDState          *card;

    // driver state
    BlockDriverStateP bdrv;

    // Allows updating of net in PSE
    vmiProcessorP     processor;
    pseHandlesT       pse;
    const char *      pName;        // processor name, used for debug

} vmiosObject;

#define DES0_OWN   0x80000000
#define DES0_CES   0x40000000
#define DES0_ER    0x20
#define DES0_CH    0x10
#define DES0_FS    0x8
#define DES0_LD    0x4
#define DES0_DIC   0x2

#define DES1_BS2   0x3FFE000
#define DES1_BS1   0x1FFF

#define DES2_BAP1  0xFFFFFFFF
#define DES3_BAP2  0xFFFFFFFF

#define fifo_len   (object->fifo_len)
#define fifo_pos   (object->fifo_pos)
#define fifo       (object->fifo)

#define STR(_name)   (object->bportRegs. _name)

// Common naming here and in PSE
#define control    STR(uSDHC_SYS_CTRL)
#define protocol   STR(uSDHC_PROT_CTRL)
#define state      STR(uSDHC_PRES_STATE)
#define watermark  STR(uSDHC_WTMK_LVL)

#define cmdarg     STR(uSDHC_CMD_ARG)
#define command    STR(uSDHC_CMD_XFR_TYP)
#define response0  STR(uSDHC_CMD_RSP0)
#define response1  STR(uSDHC_CMD_RSP1)
#define response2  STR(uSDHC_CMD_RSP2)
#define response3  STR(uSDHC_CMD_RSP3)

#define dbaddr     STR(uSDHC_DS_ADDR)

#define status     STR(uSDHC_INT_STATUS)
#define enable     STR(uSDHC_INT_STATUS_EN)
#define mask       STR(uSDHC_INT_SIGNAL_EN)

//#define datacnt    STR(uSDHC_BLK_ATT)
//#define idsts      STR(IDSTS)
//#define bmod       STR(BMOD)
//#define blksiz     STR(BLKSIZ)
//#define pldmnd     STR(PLDMND)


Uns32 bytcnt = 0;

static void fifo_push(vmiosObjectP object, Uns32 value)
{
    Int16 n;

    if (fifo_len == FIFO_LEN) {
        if(DIAG_SEMIHOST_MED) vmiMessage("E", PREFIX, "FIFO overflow");
        return;
    }
    n = (fifo_pos + fifo_len) & (FIFO_LEN - 1);
    fifo_len++;
    fifo[n] = value;
//    status2 &= (~0x3FFE0000);
//    status2 |= (((n+1) << 17) & 0x3FFE0000);
//    if (DIAG_SEMIHOST_HIGH) vmiMessage("I", PREFIX, "FIFO (%d) push %08x %x %x", n, (int)value, status2, (((n+1) << 17) & 0x3FFE0000));
}


static Uns32 fifo_pop(vmiosObjectP object)
{
    if(DIAG_SEMIHOST_HIGH)
        vmiMessage("I", PREFIX, "%s: %s", object->pName, __FUNCTION__);

    Uns32 value;

    if (fifo_len == 0) {
        if(DIAG_SEMIHOST_MED) vmiMessage("E", PREFIX, "%s: FIFO underflow", object->pName);
        return 0;
    }
    value = fifo[fifo_pos];
    fifo_len--;
    fifo_pos = (fifo_pos + 1) & (FIFO_LEN - 1);
//    status2 &= (~0x3FFE0000);
//    status2 |= (((fifo_pos+1) << 17) & 0x3FFE0000);
//    if (DIAG_SEMIHOST_HIGH) vmiMessage("I", PREFIX, "FIFO pop (%d) %08x %x", fifo_pos, (int)value, status2);
    return value;
}


static void send_command(vmiosObjectP object)
{
    if(DIAG_SEMIHOST_HIGH)
        vmiMessage("I", PREFIX, "%s: %s", object->pName, __FUNCTION__);

    SDRequest  request;
    Uns8  response[16];

    request.cmd = command.bits.CMDINX;
    request.arg = cmdarg.value;

    if(DIAG_SEMIHOST_MED)
        vmiMessage("I", PREFIX, "Command %d %08x\n", request.cmd, request.arg);

    Int32 rlen = sd_do_command(object->card, &request, response, object->diag);
    if (rlen < 0)
        goto error;

    if (command.bits.RSPTYP) {
        if (rlen == 0 || (rlen == 4 && (command.bits.RSPTYP)))
            goto error;
        if (rlen != 4 && rlen != 16)
            goto error;
        response0.value = RWORD(0);
        if (rlen == 4) {
            response1.value = response2.value = response3.value = 0;
        } else {
            response1.value = RWORD(4);
            response2.value = RWORD(8);
            response3.value = RWORD(12) & ~1;
        }
        if(DIAG_SEMIHOST_MED)
            vmiMessage("I", PREFIX, "Response received\n");
    } else {
        if(DIAG_SEMIHOST_MED)
            vmiMessage("I", PREFIX, "Command sent\n");
    }
    return;

error:
    if(DIAG_SEMIHOST_MED)
        vmiMessage("I", PREFIX, "%s: Timeout (%d)", object->pName, rlen);

//    status |= BPORT1_AB_RINTSTS__BAR;
//    status |= BPORT1_AB_RINTSTS__CMD;
}

static void fifo_run(vmiosObjectP  object)
{
    if(DIAG_SEMIHOST_HIGH)
        vmiMessage("I", PREFIX, "%s: %s %d", object->pName, __FUNCTION__, bytcnt);
//    Int32 revdatacnt = datacnt;
//    Int32 bIndex = 0;
//    Uns8 byteBuffer[revdatacnt];
//    Uns8 *byteBufferPtr = byteBuffer;
//    Uns8 byteData;
//    Int32 desc[4];
//    Int32 buf1Size;
//    Int32 buf2Size;
//    Uns32 descAddress;
//    Int32 transferredByteCnt;
//    Int32 is_read;
//    Int32 limit;
//    Int32 n;
//    Int32 value;
//
//    status2 &= (~0x6);
//    is_read = (command & BPORT1_AB_CMD__RD_WR) == 0;
//
//    if ((byteCntCounter != 0) && (!is_read || sd_data_ready(object->card))
//#ifdef USELINUXHACK
//            && !linux_hack) {
//#else
//        ) {
//#endif
//        limit = is_read ? FIFO_LEN : 0;
//        n = 0;
//        value = 0;
//        if(DIAG_SEMIHOST_HIGH) vmiMessage("I", PREFIX, "%s: byteCntCounter %d fifo_len %d n %d bytcnt %d", __FUNCTION__, byteCntCounter, fifo_len, n, bytcnt);
//
//        while (byteCntCounter && ((fifo_len != limit) || (n > 0))) {
//            if (is_read) {
//                byteData = sd_read_data(object->card, object->diag);
//                value |= (Uns32)byteData << (n * 8);
//                byteBuffer[bIndex++] = byteData;
//                n++;
//                if ((n == 4) && !(bmod & BPORT1_AB_BMOD__DE)) {
//                    fifo_push(object, value);
//                    value = 0;
//                    n = 0;
//                }
//            } else if (!(bmod & BPORT1_AB_BMOD__DE)) {
//                if (n == 0) {
//                    value = fifo_pop(object);
//                    n = 4;
//                }
//                sd_write_data(object->card, value & 0xff, object->diag);
//                value >>= 8;
//                n--;
//            }
//            byteCntCounter--;
//        }
//
//        //It's host's responsible to read the left overs from the FIFO
//        if (n && is_read && !(bmod & BPORT1_AB_BMOD__DE)) {
//            fifo_push(object, value);
//        }
//
//        //DMA transfer
//        descAddress = dbaddr;
//        transferredByteCnt = 0;
//        if ((bmod & BPORT1_AB_BMOD__DE)) {
//            while((transferredByteCnt < revdatacnt)) {
//              vmirtReadNByteDomain(object->portDomain, descAddress, desc, 16, 0, False);
//              if (!(desc[0] & DES0_OWN)) {
//                  if(DIAG_SEMIHOST_MED) vmiMessage("I", PREFIX, "%s Descriptor not available due to OWN bit == 1", __FUNCTION__);
//                  break;
//              }
//              buf1Size = (desc[1] & DES1_BS1);
//              if (is_read) {
//                  vmirtWriteNByteDomain(object->portDomain, desc[2], (byteBufferPtr + transferredByteCnt), buf1Size, 0, False);
//              } else {
//                  bIndex = 0;
//                  Uns8 writeBuffer[buf1Size];
//                  vmirtReadNByteDomain(object->portDomain, desc[2], writeBuffer, buf1Size, 0, False);
//                  while (bIndex < buf1Size) {
//                      sd_write_data(object->card, writeBuffer[bIndex++] & 0xff, object->diag);
//                  }
//              }
//              transferredByteCnt += buf1Size;
//
//              //Set Own bit
//              desc[0] &= (~DES0_OWN);
//              vmirtWriteNByteDomain(object->portDomain, descAddress, desc, 4, 0, False);
//
//              //if using double buffer, DMA transfer to second buffer
//              //otherwise, continue transfer to next descriptor
//              if (!(desc[0] & DES0_CH)) {
//                  buf2Size = (desc[1] & DES1_BS2) >> 13;
//                  if (is_read) {
//                      vmirtWriteNByteDomain(object->portDomain, desc[3], (byteBufferPtr + transferredByteCnt), buf2Size, 0, False);
//                  } else {
//                      bIndex = 0;
//                      Uns8 writeBuffer[buf1Size];
//                      vmirtReadNByteDomain(object->portDomain, desc[2], writeBuffer, buf2Size, 0, False);
//                      while (bIndex < buf2Size) {
//                          sd_write_data(object->card, writeBuffer[bIndex++] & 0xff, object->diag);
//                      }
//                  }
//                  transferredByteCnt += buf2Size;
//                  descAddress += (bmod & BPORT1_AB_BMOD__DSL) >> 2;
//              } else {
//                  descAddress = desc[3];
//              }
//
//              if(DIAG_SEMIHOST_MED) vmiMessage("I", PREFIX, "%s Descriptor Tables: %x %x %x %x", __FUNCTION__, desc[0], desc[1], desc[2], desc[3]);
//            }
//
//            if (transferredByteCnt != revdatacnt) {
//                if(DIAG_SEMIHOST_MED) vmiMessage("I", PREFIX, "%s Warning: Transfer not complete", __FUNCTION__);
//            }
//            usleep(1000);
//            pldmnd = 0;
//        }
//    }
}

static void update_status(vmiosObjectP object)
{
    if(DIAG_SEMIHOST_HIGH)
        vmiMessage("I", PREFIX, "%s: %s", object->pName, __FUNCTION__);

//    if(DIAG_SEMIHOST_HIGH) vmiMessage("I", PREFIX, "%s: update status fifo_len = %x byteCntCounter = %x", __FUNCTION__, fifo_len, byteCntCounter);
//    status &= ~(S_RX_FIFO | S_TX_FIFO);
//
//    if (fifo_len == 0) {
//      status |= BPORT1_AB_RINTSTS__DTO;
//      status |= BPORT1_AB_RINTSTS__CMD;
//      if (bmod & BPORT1_AB_BMOD__DE) {
//        idsts |= ((BPORT1_AB_IDINTEN__TI) | (BPORT1_AB_IDINTEN__RI));
//      }
//      if(DIAG_SEMIHOST_MED) vmiMessage("I", PREFIX, "Data engine idle");
//    } else {
//        if (command & BPORT1_AB_CMD__DATA_EXPECTED) {
//          status |= BPORT1_AB_RINTSTS__CMD;
//          if (bmod & BPORT1_AB_BMOD__DE) {
//            fifo_len = 0;
//            if (byteCntCounter == 0) {
//                idsts |= ((BPORT1_AB_IDINTEN__TI) | (BPORT1_AB_IDINTEN__RI));
//                status |= BPORT1_AB_RINTSTS__DTO;
//            }
//          } else {
//              status |= BPORT1_AB_RINTSTS__DTO;
//          }
//        }
//        status |= (BPORT1_AB_RINTSTS__TXDR | BPORT1_AB_RINTSTS__RXDR);
//    }
//    if(DIAG_SEMIHOST_MED) vmiMessage("I", PREFIX, "%s status = %x idsts = %x byteCntCounter = %d", __FUNCTION__, status, idsts, byteCntCounter);


    status.bits.CC = 1; // indicate command complete

    // clear on response
    state.bits.CIHB = 0;
}

//
// Look for drives. Each is a file, named using the SD_DRIVE attribute
//
static void initDrive(vmiosObjectP object, const char *sdDrive, Uns32 delta)
{
    if(DIAG_SEMIHOST_HIGH)
        vmiMessage("I", PREFIX, "%s: %s", object->pName, __FUNCTION__);

    if (sdDrive) {
        object->bdrv = bdrv_open(0, sdDrive, 0, object->diag);
        if (object->bdrv) {
            if(DIAG_SEMIHOST_LOW) {
                vmiMessage("I", PREFIX, "SD Drive using file '%s'", sdDrive);
            }
        } else {
            if(DIAG_SEMIHOST_LOW) vmiMessage("E", PREFIX, "%s: Failed to open file '%s'", object->pName, sdDrive);
        }
    }

    if(delta) {
        if(DIAG_SEMIHOST_MED) vmiMessage("I", PREFIX, "%s: SD Drive using delta writes", object->pName);
        bdrvDelta(0, object->diag);
    }
}

static void update_interrupts(vmiosObjectP object)
{
    // clear any bits that are not enabled
    status.value &= ~enable.value;

    // interrupt if any bits set and not masked
    Bool i0 = (status.value & mask.value) && True;

    if(DIAG_SEMIHOST_MED) vmiMessage("I", PREFIX,
                "%s: %s Status = %08x, enable = %08x, signal = %08x, int = %u",
                    object->pName, __FUNCTION__, status.value, enable.value, mask.value, i0);

    vmiProcessorP proc = object->processor;
    pseHandlesT   pse  = object->pse;

    Bool currentIRQ = (vmirtReadNetPort(proc, pse.irq) != 0);

    if(i0 != currentIRQ) {
        vmirtWriteNetPort(proc, pse.irq, i0);
    }
}

static VMI_MEM_WATCH_FN(calledOnFIFOWrite) {

    vmiosObjectP object   = userData;

    if(DIAG_SEMIHOST_HIGH)
        vmiMessage("I", PREFIX, "%s: %s", object->pName, __FUNCTION__);

    if(DIAG_SEMIHOST_MED) vmiMessage("I", PREFIX, "%s: data size %d bytes with data: %x",
                object->pName, bytes, *(Uns8 *) value);

    if (byteCntCounter == 0) {
        if(DIAG_SEMIHOST_MED) vmiMessage("F", PREFIX, "%s: Unexpected FIFO write", object->pName);
    } else {
        Uns32 data = 0;
        switch(bytes) {
        case 1:
            data = *(Uns8 *) value;
            break;
        case 2:
            data = *(Uns16 *) value;
            break;
        case 4:
            data = *(Uns32 *) value;
            break;
        default:
            if(DIAG_SEMIHOST_MED) vmiMessage("F", PREFIX, "%s: Strange data size %d bytes", object->pName, bytes);
            break;
        }
        if(DIAG_SEMIHOST_HIGH) vmiMessage("I", PREFIX, "%s: %s 0x%08x", object->pName, __FUNCTION__, data);
        fifo_push(object, data);
        fifo_run(object);
        update_status(object);
        update_interrupts(object);
    }
}


static VMI_MEM_WATCH_FN(calledOnFIFORead) {

    vmiosObjectP object   = userData;

    if(DIAG_SEMIHOST_HIGH)
        vmiMessage("I", PREFIX, "%s: %s", object->pName, __FUNCTION__);

    if (fifo_len == 0) {
        if(DIAG_SEMIHOST_MED) vmiMessage("E", PREFIX, "%s: Unexpected FIFO read", object->pName);
            *(Uns32 *) value = 0;
    } else {
        Uns32 data = fifo_pop(object);
        fifo_run(object);
        update_status(object);
        update_interrupts(object);
        if(DIAG_SEMIHOST_HIGH) vmiMessage("I", PREFIX, "%s: %s 0x%08x", object->pName, __FUNCTION__, data);
        *(Uns32 *) value = data;
    }


}

//
// Called to initialise
//
static Uns32 initNative(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Addr          baseRegStruct,
    Addr          fifoBase,
    Uns32         fifoSize,
    Addr          driveNameAddress,
    Uns32         driveNameLen,
    Uns32         delta,
    Uns32         irq,
    Uns32         cardin,
    Uns32         wprot
) {
    if(DIAG_SEMIHOST_HIGH)
        vmiMessage("I", PREFIX, "%s: %s", object->pName, __FUNCTION__);

    object->pse.irq    = irq;
    object->pse.cardin = cardin;
    object->pse.wprot  = wprot;

    //
    // map the memory for the register structure
    //
    if(DIAG_SEMIHOST_LOW)
        vmiMessage("I", PREFIX, "%s: Map Register Structure: Base 0x0x"FMT_A08x, object->pName, baseRegStruct);

    bport1_ab_dataTP bportRegs = &object->bportRegs;
    Addr regTop               = baseRegStruct+sizeof(bport1_ab_dataT)-1;

    vmirtMapNativeMemory(object->pseDomain, baseRegStruct, regTop, bportRegs);

    char sdDrive[1024]; // this is BHM_MAX_PATH
    vmirtReadNByteDomain(object->pseDomain, driveNameAddress, sdDrive, driveNameLen , 0, True);
    sdDrive[driveNameLen] = 0; // terminate string

    if(DIAG_SEMIHOST_LOW)
        vmiMessage("I", PREFIX, "%s: SD Drive Init: %s, Delta %d, Base 0x0x"FMT_A08x, object->pName, sdDrive, delta, driveNameAddress);

    initDrive(object, strlen(sdDrive) ? sdDrive : NULL, delta);


    //
    // Now get the FIFO buffer mapped natively
    //
    if(DIAG_SEMIHOST_LOW)
        vmiMessage("I", PREFIX, "%s: FIFO Base 0x0x"FMT_A08x" Size 0x%0x", object->pName, fifoBase, fifoSize);

    // map the memory for the fifo
    object->fifoBuffer = calloc(fifoSize, sizeof(Uns8));
    Uns32 result = vmirtMapNativeMemory(object->pseDomain, fifoBase, fifoBase+fifoSize-1, object->fifoBuffer);

    vmirtAddWriteCallback(object->pseDomain, 0, fifoBase, fifoBase+fifoSize-1, calledOnFIFOWrite, object);
    vmirtAddReadCallback(object->pseDomain, 0, fifoBase, fifoBase+fifoSize-1, calledOnFIFORead, object);

    return result;
}

static void startSDNative(vmiProcessorP processor, vmiosObjectP object) {
    object->card = sd_init(processor, object->pse, object->bdrv ? object->bdrv : NULL, 0, 0, object->diag);
}

static void setNativeDiagnostics(vmiosObjectP object, Addr diagAddr, Uns32 currentDiag) {

    if(DIAG_SEMIHOST_HIGH)
        vmiMessage("I", PREFIX, "%s", __FUNCTION__);

    Uns32 *diag = &object->diag;

    // map the diagnostics variable
    vmirtMapNativeMemory(object->pseDomain, diagAddr, diagAddr+sizeof(Uns32)-1, diag);

    object->diag = currentDiag;

}

static void sendCommandNative(vmiosObjectP object) {

    if(DIAG_SEMIHOST_HIGH)
        vmiMessage("I", PREFIX, "%s: %s", object->pName, __FUNCTION__);

    send_command(object);
    fifo_run(object);
    update_status(object);
}

static void writeDCNative(vmiosObjectP object) {

    if(DIAG_SEMIHOST_HIGH)
        vmiMessage("I", PREFIX, "%s: %s", object->pName, __FUNCTION__);

    fifo_run(object);
    update_status(object);

}

static void updateBytCnt(vmiosObjectP object, Uns32 val) {
    if(DIAG_SEMIHOST_HIGH)
        vmiMessage("I", PREFIX, "%s: %s", object->pName, __FUNCTION__);

    byteCntCounter = val;
}

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(constructor) {

    object->pName = strdup(vmirtProcessorName(processor));

    if(DIAG_SEMIHOST_HIGH)
        vmiMessage("I", PREFIX, "%s: %s", object->pName, __FUNCTION__);

    // store the PSE data domain
    object->pseDomain = vmirtGetProcessorDataDomain(processor);

    // store the processor handle
    object->processor = processor;

    const char *portName = "mport";
    Addr lo, hi;
    Bool isMaster;
    Bool isDynamic;
    object->portDomain = vmipsePlatformPortAttributes (
            processor,
            portName,
            &lo,
            &hi,
            &isMaster,
            &isDynamic
    );

    if(DIAG_SEMIHOST_MED) vmiMessage("I", "INIT", "%s: '%s', hi 0x" FMT_Ax
                                                           " lo 0x" FMT_Ax
                                                    " master %u dynamic %u",
                    object->pName, portName, lo, hi, isMaster, isDynamic);

}

//
// Destructor
//
static VMIOS_DESTRUCTOR_FN(destructor) {
    if(DIAG_SEMIHOST_LOW)
        vmiMessage("I" ,PREFIX, "%s: Shutting down", object->pName);

    // TODO: should free memory allocated for FIFO
}


////////////////////////////////////////////////////////////////////////////////
// INTERCEPT ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString = VMI_VERSION,            // version string
    .modelType     = VMI_INTERCEPT_LIBRARY,  // type
    .packageName   = PREFIX,                 // description
    .objectSize    = sizeof(vmiosObject),    // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {    
        .vendor  = "nxp.ovpworld.org",
        .library = "peripheral",
        .name    = "iMX6_SDHC",
        .version = "1.0"
    },

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB = constructor,            // object constructor
    .destructorCB  = destructor,             // object destructor

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    // -------------------     ----------- ------  -----------------
    // Name                    Address     Opaque  Callback
    // -------------------     ----------- ------  -----------------
    .intercepts = {
        {"initNative",                  0, True,  VMIOS_ABI_INT('4', "poaa4a44kkk", initNative)},
        {"setNativeDiagnostics",        0, True,  VMIOS_ABI_INT(0,   "oa4",         setNativeDiagnostics)},
        {"startSDNative",               0, True,  VMIOS_ABI_INT(0,   "po",          startSDNative)},
        {"sendCommandNative",           0, True,  VMIOS_ABI_INT(0,   "o",           sendCommandNative)},
        {"writeDCNative",               0, True,  VMIOS_ABI_INT(0,   "o",           writeDCNative)},
        {"updateBytCnt",                0, True,  VMIOS_ABI_INT(0,   "o4",          updateBytCnt)},
        {0}
    }
};

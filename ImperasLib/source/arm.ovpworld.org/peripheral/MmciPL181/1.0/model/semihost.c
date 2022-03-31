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


#include <string.h>
#include <stdlib.h>

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
#include "../pse/user.defines.h"

#include "sd.h"

typedef struct vmiosObjectS  {

    // PSE data domain (passed to read and write callbacks)
    memDomainP        pseDomain;

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

} vmiosObject;

#define fifo_len   (object->fifo_len)
#define fifo_pos   (object->fifo_pos)
#define fifo       (object->fifo)

#define DIAG_SEMIHOST_HIGH ((object->diag >> 2) >= 3)
#define DIAG_SEMIHOST_MED  ((object->diag >> 2) >= 2)
#define DIAG_SEMIHOST_LOW  ((object->diag >> 2) >= 1)

#define STR(_name)   (object->bportRegs. _name .value)

#define power      STR(power)
#define clock      STR(clock)
#define cmdarg     STR(cmdarg)
#define command    STR(cmd)
#define respcmd    STR(respcmd)
#define response0  STR(response0)
#define response1  STR(response1)
#define response2  STR(response2)
#define response3  STR(response3)
#define datatimer  STR(datatimer)
#define datalength STR(datalength)
#define datactrl   STR(datactrl)
#define datacnt    STR(datacnt)
#define status     STR(status)
#define clear      STR(clear)
#define mask0      STR(mask0)
#define mask1      STR(mask1)
#define fifoCnt    STR(fifoCnt)

#define periphID0  STR(periphID0)
#define periphID1  STR(periphID1)
#define periphID2  STR(periphID2)
#define periphID3  STR(periphID3)
#define pCellID0   STR(pCellID0)
#define pCellID1   STR(pCellID1)
#define pCellID2   STR(pCellID2)
#define pCellID3   STR(pCellID3)

static void fifo_push(vmiosObjectP object, Uns32 value)
{
    int n;

    if (fifo_len == FIFO_LEN) {
        vmiMessage("E", PREFIX, "FIFO overflow");
        return;
    }
    n = (fifo_pos + fifo_len) & (FIFO_LEN - 1);
    fifo_len++;
    fifo[n] = value;
    if (DIAG_SEMIHOST_HIGH) vmiMessage("I", PREFIX, "FIFO (%d) push %08x", n, (int)value);
}

static Uns32 fifo_pop(vmiosObjectP object)
{
    if(DIAG_SEMIHOST_HIGH)
        vmiMessage("I", PREFIX, "%s", __FUNCTION__);

    Uns32 value;

    if (fifo_len == 0) {
        vmiMessage("E", PREFIX, "FIFO underflow");
        return 0;
    }
    value = fifo[fifo_pos];
    fifo_len--;
    fifo_pos = (fifo_pos + 1) & (FIFO_LEN - 1);
    if (DIAG_SEMIHOST_HIGH) vmiMessage("I", PREFIX, "FIFO pop (%d) %08x", fifo_pos, (int)value);
    return value;
}

static void send_command(vmiosObjectP object)
{
    if(DIAG_SEMIHOST_HIGH)
        vmiMessage("I", PREFIX, "%s", __FUNCTION__);

    SDRequest  request;
    Uns8  response[16];

    request.cmd = command & BPORT1_AB_CMD_C_INDEX;
    request.arg = cmdarg;
    if(DIAG_SEMIHOST_MED)
        vmiMessage("I", PREFIX, "Command %d %08x\n", request.cmd, request.arg);
    Int32 rlen = sd_do_command(object->card, &request, response, object->diag);
    if (rlen < 0)
        goto error;
    if (command & BPORT1_AB_CMD_C_RESPONSE) {
        if (rlen == 0 || (rlen == 4 && (command & BPORT1_AB_CMD_C_LONGRESP)))
            goto error;
        if (rlen != 4 && rlen != 16)
            goto error;
        response0 = RWORD(0);
        if (rlen == 4) {
            response1 = response2 = response3 = 0;
        } else {
            response1 = RWORD(4);
            response2 = RWORD(8);
            response3 = RWORD(12) & ~1;
        }
        if(DIAG_SEMIHOST_MED)
            vmiMessage("I", PREFIX, "Response received\n");
        status |= BPORT1_AB_STATUS_S_CMDRESPEND;
    } else {
        if(DIAG_SEMIHOST_MED)
            vmiMessage("I", PREFIX, "Command sent\n");
        status |= BPORT1_AB_STATUS_S_CMDSENT;
    }
    return;

error:
    if(DIAG_SEMIHOST_MED)
        vmiMessage("I", PREFIX, "Timeout\n");

    status |= BPORT1_AB_STATUS_S_CMDTIMEOUT;
}

static void update_status(vmiosObjectP object)
{
    if(DIAG_SEMIHOST_HIGH)
        vmiMessage("I", PREFIX, "%s", __FUNCTION__);

    if(DIAG_SEMIHOST_HIGH) vmiMessage("I", PREFIX, "%s: update status", __FUNCTION__);
    status &= ~(S_RX_FIFO | S_TX_FIFO);
    if (datacnt == 0) {
        status |= (BPORT1_AB_STATUS_S_DATAEND | BPORT1_AB_STATUS_S_DATABLOCKEND);
        if(DIAG_SEMIHOST_MED) vmiMessage("I", PREFIX, "Transfer Complete");
    }
    if (datacnt == 0 && fifo_len == 0) {
        datactrl &= ~BPORT1_AB_DATACTRL_D_ENABLE;
        if(DIAG_SEMIHOST_MED) vmiMessage("I", PREFIX, "Data engine idle");
    } else {

        Uns32 bits = BPORT1_AB_STATUS_S_TXACTIVE | BPORT1_AB_STATUS_S_RXACTIVE;
        if (fifo_len == 0) {
            bits |= BPORT1_AB_STATUS_S_TXFIFOEMPTY;
            bits |= BPORT1_AB_STATUS_S_RXFIFOEMPTY;
        } else {
            bits |= BPORT1_AB_STATUS_S_TXDATAAVLBL;
            bits |= BPORT1_AB_STATUS_S_RXDATAAVLBL;
        }
        if (fifo_len == 16) {
            bits |= BPORT1_AB_STATUS_S_TXFIFOFULL;
            bits |= BPORT1_AB_STATUS_S_RXFIFOFULL;
        }
        if (fifo_len <= 8) {
            bits |= BPORT1_AB_STATUS_S_TXFIFOHALFEMPTY;
        }
        if (fifo_len >= 8) {
            bits |= BPORT1_AB_STATUS_S_RXFIFOHALFFULL;
        }
        if (datactrl & BPORT1_AB_DATACTRL_D_DIRECTION) {
            bits &= S_RX_FIFO;
        } else {
            bits &= S_TX_FIFO;
        }
        status |= bits;
    }
}

static void fifo_run(vmiosObjectP  object)
{
    if(DIAG_SEMIHOST_HIGH)
        vmiMessage("I", PREFIX, "%s", __FUNCTION__);

    Int32 is_read = (datactrl & BPORT1_AB_DATACTRL_D_DIRECTION) != 0;
    if (datacnt != 0 && (!is_read || sd_data_ready(object->card))
#ifdef USELINUXHACK
            && !linux_hack) {
#else
        ) {
#endif

        Int32 limit = is_read ? FIFO_LEN : 0;
        Int32 n = 0;
        Uns32 value = 0;
        if(DIAG_SEMIHOST_HIGH) vmiMessage("I", PREFIX, "%s: datacnt %d fifo_len %d n %d", __FUNCTION__, datacnt, fifo_len, n);
        while (datacnt && ((fifo_len != limit) || (n > 0))) {
            if (is_read) {
                value |= (Uns32)sd_read_data(object->card, object->diag) << (n * 8);
                n++;
                if (n == 4) {
                    fifo_push(object, value);
                    value = 0;
                    n = 0;
                }
            } else {
                if (n == 0) {
                    value = fifo_pop(object);
                    n = 4;
                }
                sd_write_data(object->card, value & 0xff, object->diag);
                value >>= 8;
                n--;
            }
            datacnt--;
        }
        if (n && is_read) {
            fifo_push(object, value);
        }
    }
}

//
// Look for drives. Each is a file, named using the SD_DRIVE attribute
//
static void initDrive(vmiosObjectP object, const char *sdDrive, Uns32 delta)
{
    if(DIAG_SEMIHOST_HIGH)
        vmiMessage("I", PREFIX, "%s", __FUNCTION__);

    if (sdDrive) {
        object->bdrv = bdrv_open(0, sdDrive, 0, object->diag);
        if (object->bdrv) {
            if(DIAG_SEMIHOST_LOW) {
                vmiMessage("I", PREFIX, "SD Drive using file '%s'", sdDrive);
            }
        } else {
            vmiMessage("E", PREFIX, "Failed to open file '%s'", sdDrive);
        }
    }

    if(delta) {
        vmiMessage("I", PREFIX, "SD Drive using delta writes");
        bdrvDelta(0, object->diag);
    }
}

static void update_interrupts(vmiosObjectP object)
{
    vmiProcessorP proc = object->processor;
    pseHandlesT pse = object->pse;

    Bool currentIRQ0 = (vmirtReadNetPort(proc, pse.irq0) != 0);

    Bool currentIRQ1 = (vmirtReadNetPort(proc, pse.irq1) != 0);

    Bool i0 = (status & mask0) && True;
    Bool i1 = (status & mask1) && True;

    if(i0 != currentIRQ0) {
        vmirtWriteNetPort(proc, pse.irq0, i0);
    }
    if(i1 != currentIRQ1) {
        vmirtWriteNetPort(proc, pse.irq1, i1);
    }
}


static VMI_MEM_WATCH_FN(calledOnFIFOWrite) {

    vmiosObjectP object   = userData;

    if(DIAG_SEMIHOST_HIGH)
        vmiMessage("I", PREFIX, "%s", __FUNCTION__);

    if(DIAG_SEMIHOST_HIGH) vmiMessage("I", PREFIX, "%s", __FUNCTION__);
    if (datacnt == 0) {
        vmiMessage("F", PREFIX, "Unexpected FIFO write");
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
            vmiMessage("F", PREFIX, "Strange data size %d bytes", bytes);
            break;
        }
        if(DIAG_SEMIHOST_HIGH) vmiMessage("I", PREFIX, "%s 0x%08x", __FUNCTION__, data);
        fifo_push(object, data);
        fifo_run(object);
        update_status(object);
        update_interrupts(object);
    }

}

static VMI_MEM_WATCH_FN(calledOnFIFORead) {

    vmiosObjectP object   = userData;

    if(DIAG_SEMIHOST_HIGH)
        vmiMessage("I", PREFIX, "%s", __FUNCTION__);

    if (fifo_len == 0) {
            vmiMessage("E", PREFIX, "Unexpected FIFO read");
            *(Uns32 *) value = 0;
    } else {
        Uns32 data = fifo_pop(object);
        fifo_run(object);
        update_status(object);
        update_interrupts(object);
        if(DIAG_SEMIHOST_HIGH) vmiMessage("I", PREFIX, "%s 0x%08x", __FUNCTION__, data);
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
    Uns32         irq0,
    Uns32         irq1,
    Uns32         cardin,
    Uns32         wprot
) {

    if(DIAG_SEMIHOST_HIGH)
        vmiMessage("I", PREFIX, "%s", __FUNCTION__);

    object->pse.irq0   = irq0;
    object->pse.irq1   = irq1;
    object->pse.cardin = cardin;
    object->pse.wprot  = wprot;

    const char *name = vmirtProcessorName(processor);

    //
    // map the memory for the register structure
    //
    if(DIAG_SEMIHOST_LOW)
        vmiMessage("I", PREFIX, "%s: Map Register Structure: Base 0x"FMT_A08x, name, baseRegStruct);

    bport1_ab_dataTP bportRegs = &object->bportRegs;
    Addr regTop               = baseRegStruct+sizeof(bport1_ab_dataT)-1;

    vmirtMapNativeMemory(object->pseDomain, baseRegStruct, regTop, bportRegs);

    char sdDrive[1024]; // this is BHM_MAX_PATH
    vmirtReadNByteDomain(object->pseDomain, driveNameAddress, sdDrive, driveNameLen , 0, True);
    sdDrive[driveNameLen] = 0; // terminate string

    if(DIAG_SEMIHOST_LOW)
        vmiMessage("I", PREFIX, "%s: SD Drive Init: %s, Delta %d, Base 0x"FMT_A08x, name, sdDrive, delta, driveNameAddress);

    initDrive(object, strlen(sdDrive) ? sdDrive : NULL, delta);


    //
    // Now get the FIFO buffer mapped natively
    //
    if(DIAG_SEMIHOST_LOW)
        vmiMessage("I", PREFIX, "%s: FIFO Base 0x"FMT_A08x" Size 0x%0x", name, fifoBase, fifoSize);

    // map the memory for the fifo
    object->fifoBuffer = calloc(fifoSize, sizeof(Uns8));
    Uns32 result = vmirtMapNativeMemory(object->pseDomain, fifoBase, fifoBase+fifoSize-1, object->fifoBuffer);

    vmirtAddWriteCallback(object->pseDomain, 0, fifoBase, fifoBase+fifoSize-1, calledOnFIFOWrite, object);
    vmirtAddReadCallback(object->pseDomain, 0, fifoBase, fifoBase+fifoSize-1, calledOnFIFORead, object);

    return result;
}

static void startSDNative(vmiProcessorP processor, vmiosObjectP object) {
    object->card = sd_init(processor, object->pse, object->bdrv ? object->bdrv : NULL, 0, object->diag);
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
        vmiMessage("I", PREFIX, "%s", __FUNCTION__);

    send_command(object);
    fifo_run(object);
    update_status(object);

}

static void writeDCNative(vmiosObjectP object) {

    if(DIAG_SEMIHOST_HIGH)
        vmiMessage("I", PREFIX, "%s", __FUNCTION__);

    fifo_run(object);
    update_status(object);

}

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(constructor) {

    if(DIAG_SEMIHOST_HIGH)
        vmiMessage("I", PREFIX, "%s", __FUNCTION__);

    // store the PSE data domain
    object->pseDomain = vmirtGetProcessorDataDomain(processor);

    // store the processor handle
    object->processor = processor;

}

//
// Destructor
//
static VMIOS_DESTRUCTOR_FN(destructor) {
    if(DIAG_SEMIHOST_LOW)
        vmiMessage("I" ,PREFIX, "Shutting down");

    // TODO: should free memory allocated for FIFO

    //
    // Try shutting down drives
    //
    if (object->bdrv) {
        bdrv_close(object->bdrv);
    }
//    ???????
//    bdrvShutdown(object->diag);
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
        .vendor  = "arm.ovpworld.org",
        .library = "peripheral",
        .name    = "MmciPL181",
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
        {"initNative",                  0, True,  VMIOS_ABI_INT('4', "poaa4a44kkkk", initNative)},
        {"setNativeDiagnostics",        0, True,  VMIOS_ABI_INT(0,   "oa4",          setNativeDiagnostics)},
        {"startSDNative",               0, True,  VMIOS_ABI_INT(0,   "po",           startSDNative)},
        {"sendCommandNative",           0, True,  VMIOS_ABI_INT(0,   "o",            sendCommandNative)},
        {"writeDCNative",               0, True,  VMIOS_ABI_INT(0,   "o",            writeDCNative)},
        {0}
    }
};

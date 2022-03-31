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



/*
 * This is an example wrapper layer encapsulating a simple ISS model
 * Currently only simulation encapsulation is completed
 * Debug and VAP to be done
 */

#include <string.h>
#include <stdlib.h>

// XTernal Simulation Model types and function prototypes
#include "XTrisc32.h"

#include "hostapi/impAlloc.h"

// VMI includes
#include "vmi/vmiAttrs.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiTypes.h"
#include "vmi/vmiVersion.h"

#define CPU_PREFIX  "RISC32"
#define NUM_MEMBERS(_A) (sizeof(_A)/sizeof((_A)[0]))

//
// Structure type for XTernal model integration
//
typedef struct risc32S {
    // Foreign simulator handle
    risc32Handle handle;

    memDomainP   code, data;
    memEndian    endian;
    vmiBusPortP  busPorts;        // bus port descriptions

} risc32, *risc32P;

static void newBusPorts(risc32P risc32);
static void freeBusPorts(risc32P risc32);

#define VENDOR  "ovpworld.org"
#define LIBRARY "processor"
#define NAME    "risc32"
#define VERSION "1.0"
#define VARIANT "ISS"

VMI_PROC_INFO_FN(risc32ProcInfo) {
    static const vmiProcessorInfo info = {
        .vlnv.vendor      = VENDOR            ,
        .vlnv.library     = LIBRARY           ,
        .vlnv.name        = NAME              ,
        .vlnv.version     = VERSION           ,

        .elfCode          = 1234,
        .endianFixed      = False,
        .family           = "RISC32",
    };
    return &info;
}


//
// Read callback for a GPR
//
static VMI_REG_READ_FN(risc32RegRead) {
    risc32P risc32 = (risc32P)processor;
    XT_Value value = XT_readReg(risc32->handle, reg->gdbIndex);
    *(Uns32*)buffer = value.ivalue;

    return True;
}

//
// Write callback for a GPR
//
static VMI_REG_WRITE_FN(risc32RegWrite) {
    risc32P risc32 = (risc32P)processor;
    XT_Value value;
    value.ivalue = *(Uns32*)buffer;
    XT_writeReg(risc32->handle, reg->gdbIndex, value);

    return True;
}

//
// Read callback for PC
//
static VMI_REG_READ_FN(readPC) {
    *(Uns32*)buffer = (Uns32)vmirtGetPC(processor);
    return True;
}

//
// Write callback for PC
//
static VMI_REG_WRITE_FN(writePC) {
    vmirtSetPC(processor, *(Uns32*)buffer);
    return True;
}

int fetchMem (void *userdata, XT_Addr addr, XT_Value *value, XT_Bool trueAccess) {
    risc32P risc32 = (risc32P)userdata;
    XT_Value mem;

    mem.ivalue = vmirtRead4ByteDomain(risc32->code, addr, risc32->endian, trueAccess);
    *value = mem;

    return 0;
}

int readMem (void *userdata, XT_Addr addr, XT_Value *value, XT_Bool trueAccess) {
    risc32P risc32 = (risc32P)userdata;
    XT_Value mem;

    mem.ivalue = vmirtRead4ByteDomain(risc32->code, addr, risc32->endian, trueAccess);
    *value = mem;

    return 0;
}

int writeMem (void *userdata, XT_Addr addr, XT_Value value, XT_Bool trueAccess) {
    risc32P risc32 = (risc32P)userdata;
    vmirtWrite4ByteDomain(risc32->code, addr, risc32->endian, value.ivalue, trueAccess);

    return 0;
}

//
// risc32 constructor
//
static VMI_CONSTRUCTOR_FN(risc32Constructor) {
    risc32P risc32 = (risc32P)processor;
    risc32->handle = XT_constructor(risc32);
    newBusPorts(risc32);

}

//
// risc32 memory initialization
//
VMI_VMINIT_FN(risc32VMInit) {
    risc32P risc32 = (risc32P)processor;

    //
    // Get memory domains and endian
    //
    risc32->code   = vmirtGetProcessorCodeDomain(processor);
    risc32->data   = vmirtGetProcessorDataDomain(processor);
    risc32->endian = MEM_ENDIAN_LITTLE;

    //
    // Define memory callbacks for foreign simulator
    //
    XT_installFetchMemCB(risc32->handle, &fetchMem);
    XT_installReadMemCB(risc32->handle, &readMem);
    XT_installWriteMemCB(risc32->handle, &writeMem);
}

//
// risc32 core destructor
//
static VMI_DESTRUCTOR_FN(risc32Destructor) {
    risc32P risc32 = (risc32P)processor;
    freeBusPorts(risc32);
    XT_constructor(risc32->handle);
}

//
// Encapsulate simulation routine
//
static VMI_ENCAP_SIM_FN(risc32Simulate) {
    risc32P risc32 = (risc32P)processor;
    XT_Icount instructions;

    instructions = XT_run(risc32->handle, count);

    // get the status
    XT_StopReason stopReason = XT_getReason(risc32->handle);

    //
    // This will be enhanced to handle a stop reason
    //
    if (stopReason == XT_HALT) {
        vmirtHalt(processor);
        vmirtFinish(0);
    }

    // determine how many instructions passed
    return (Uns32)(instructions);
}

//
// Get executed instruction count
//
static VMI_ENCAP_ICOUNT_FN(risc32GetICount) {
    risc32P risc32 = (risc32P)processor;
    return XT_getIcount(risc32->handle);;
}

//
// Get current program counter
//
static VMI_ENCAP_GET_PC_FN(risc32GetPC) {
    risc32P risc32 = (risc32P)processor;
    XT_Value value = XT_readReg(risc32->handle, XT_REGPC);
    return value.ivalue;
}

//
// Static array holding information about the registers
//
static const vmiRegInfo registers[] = {
    {name: "r0",     gdbIndex: 0x0, usage: vmi_REG_NONE, bits: 32, access: vmi_RA_RW, readCB: risc32RegRead, writeCB: risc32RegWrite},
    {name: "r1",     gdbIndex: 0x1, usage: vmi_REG_NONE, bits: 32, access: vmi_RA_RW, readCB: risc32RegRead, writeCB: risc32RegWrite},
    {name: "r2",     gdbIndex: 0x2, usage: vmi_REG_NONE, bits: 32, access: vmi_RA_RW, readCB: risc32RegRead, writeCB: risc32RegWrite},
    {name: "r3",     gdbIndex: 0x3, usage: vmi_REG_NONE, bits: 32, access: vmi_RA_RW, readCB: risc32RegRead, writeCB: risc32RegWrite},
    {name: "r4",     gdbIndex: 0x4, usage: vmi_REG_NONE, bits: 32, access: vmi_RA_RW, readCB: risc32RegRead, writeCB: risc32RegWrite},
    {name: "r5",     gdbIndex: 0x5, usage: vmi_REG_NONE, bits: 32, access: vmi_RA_RW, readCB: risc32RegRead, writeCB: risc32RegWrite},
    {name: "r6",     gdbIndex: 0x6, usage: vmi_REG_NONE, bits: 32, access: vmi_RA_RW, readCB: risc32RegRead, writeCB: risc32RegWrite},
    {name: "r7",     gdbIndex: 0x7, usage: vmi_REG_NONE, bits: 32, access: vmi_RA_RW, readCB: risc32RegRead, writeCB: risc32RegWrite},
    {name: "pc",     gdbIndex: 0x8, usage: vmi_REG_PC,   bits: 32, access: vmi_RA_RW, readCB: readPC,        writeCB: writePC       },
    {name: "sp",     gdbIndex: 0x9, usage: vmi_REG_SP,   bits: 32, access: vmi_RA_RW, readCB: risc32RegRead, writeCB: risc32RegWrite},
    {name: "status", gdbIndex: 0xa, usage: vmi_REG_NONE, bits: 32, access: vmi_RA_RW, readCB: risc32RegRead, writeCB: risc32RegWrite},
    {0},
};

//
// Register structure iterator
//
static VMI_REG_INFO_FN(risc32RegInfo) {
    if(!prev) {
        return registers;
    } else if((prev+1)->name) {
        return prev+1;
    } else {
        return 0;
    }
}

//
// Return the endian of the processor
//
VMI_ENDIAN_FN(risc32GetEndian) {
    risc32P risc32 = (risc32P)processor;
    return risc32->endian;
}

//
// Template bus port list
//
const static vmiBusPort busPorts[] = {
    {"INSTRUCTION", vmi_BP_MASTER, vmi_DOM_CODE, {32,32}, 1},
    {"DATA"       , vmi_BP_MASTER, vmi_DOM_DATA, {32,32}, 0},
};

//
// Allocate bus port specifications
//
static void newBusPorts(risc32P risc32) {

    Uns32 i;

    risc32->busPorts = STYPE_CALLOC_N(vmiBusPort, NUM_MEMBERS(busPorts));

    for(i=0; i<NUM_MEMBERS(busPorts); i++) {
        risc32->busPorts[i] = busPorts[i];
    }
}

//
// Free bus port specifications
//
static void freeBusPorts(risc32P risc32) {

    if(risc32->busPorts) {
        STYPE_FREE(risc32->busPorts);
        risc32->busPorts = 0;
    }
}

//
// Get the next bus port
//
VMI_BUS_PORT_SPECS_FN(risc32GetBusPortSpec) {
    risc32P risc32 = (risc32P)processor;

    if(!prev) {

        // first port
        return risc32->busPorts;

    } else {

        // port other than the first
        Uns32 prevIndex = (prev-risc32->busPorts);
        Uns32 thisIndex = prevIndex+1;

        return (thisIndex<NUM_MEMBERS(busPorts)) ? &risc32->busPorts[thisIndex] : 0;
    }
}



static const char *dictNames[] = {"NORMAL", 0};

//
// Configuration block for instruction-accurate modelling
//
const vmiIASAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION & SIZE ATTRIBUTES
    ////////////////////////////////////////////////////////////////////////
    .versionString  = VMI_VERSION,                  // version string
    .dictNames      = dictNames,                    // null-terminated dictionary name list
    .cpuSize        = sizeof(risc32),               // full size of CPU object

    ////////////////////////////////////////////////////////////////////////
    // CREATE/DELETE ROUTINES
    ////////////////////////////////////////////////////////////////////////
    .constructorCB = risc32Constructor,             // constructor
    .vmInitCB      = risc32VMInit,                  // virtual memory initialization
    .destructorCB  = risc32Destructor,              // destructor

    ////////////////////////////////////////////////////////////////////////
    // REGISTER ACCESS SUPPORT ROUTINES (DEBUGGER & SEMIHOSTING)
    ////////////////////////////////////////////////////////////////////////
    .regInfoCB     = risc32RegInfo,                 // regInfo callback

    ////////////////////////////////////////////////////////////////////////
    // ENCAPSULATED EXTERNAL SIMULATOR SUPPORT
    ////////////////////////////////////////////////////////////////////////
    .encapSimCB    = risc32Simulate,                // simulate for a number of instructions
    .encapGetPCCB  = risc32GetPC,                   // get processor program counter
    .encapICountCB = risc32GetICount,               // get processor instruction count
    .getEndianCB   = risc32GetEndian,               // get processor endianness


    ////////////////////////////////////////////////////////////////////////
    // PORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .busPortSpecsCB = risc32GetBusPortSpec,


    ////////////////////////////////////////////////////////////////////////
    // SIMULATOR ENVIRONMENT SUPPORT
    ////////////////////////////////////////////////////////////////////////
    .procInfoCB    = risc32ProcInfo,                // get the procInfo structure

};


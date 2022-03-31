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

// standard includes
#include <stdio.h>

// VMI area includes
#include "vmi/vmiDbg.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiMt.h"

#include "or1kStructure.h"

/*
 *  Extend the OR1K with 16 32bit memory mapped registers
 *  That can be loaded or saved as one
 */


#define REGISTERS 16
#define REG_BYTES (REGISTERS*4)
#define ADDR_MASK 0x1F
#define ENDIAN    MEM_ENDIAN_BIG

// load or save all registers to memory using r1 as in the base address
#define LOAD_REGS   0xf7ff0ffc
#define SAVE_REGS   0xf7ff0ffd

typedef struct vmiosObjectS {

    // Domain of bus slave port used to read/write to the memory mapped registers
    memDomainP   slaveDomain;

    // Domain of bus master port used to when the memory mapped registers
    // are loaded or saved  as a block
    memDomainP   masterDomain;

    // register values
    Uns32        registers[REGISTERS];

    // the base address when the registers are memory mapped
    Addr         baseAddress;

} vmiosObject;

static vmiBusPort bps[] = {
    {
        .name        = "bpm",
        .description = "Port used to load or save the registers",
        .type        = vmi_BP_MASTER,
        .domainType  = vmi_DOM_OTHER
    },
    {
        .name        = "bps",
        .description = "Port used to access the registers",
        .type        = vmi_BP_SLAVE,
        .domainType  = vmi_DOM_OTHER,
        .maxAddress  = 0xfffffff
    },
    {
       0
    }
}; 

//
// Define the attributes value structure
//
typedef struct paramValuesS {

    VMI_UNS64_PARAM (baseAddress)

} paramValues, *paramValuesP;

//
// Formal parameter sets the base address of the memory mapped registers
//
static vmiParameter formals[] = {
    VMI_UNS64_PARAM_SPEC(paramValues, baseAddress, 0x80000000, 0, 0xFFFFFFFF, "base address of extension registers"),
    VMI_END_PARAM
};

//
// Iterate formals
//
static VMIOS_PARAM_SPEC_FN(getParamSpecs) {
    if(!prev) {
        prev = formals;
    } else {
        prev++;
    }
    if (prev->name) {
        return prev;
    } else {
        return 0;
    }
}

static VMIOS_PARAM_TABLE_SIZE_FN(getParamTableSize) {
    return sizeof(paramValues);
}

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(constructor) {

    // copy parameter to a safe place for futire reference
    paramValuesP p = parameterValues;
    object->baseAddress = p->baseAddress;
}

static inline Uns32 registerAddress(Addr busAddress) {

    busAddress &=  ADDR_MASK;
    busAddress >>= 2;
    if(busAddress > REGISTERS) {
        vmiMessage("F", "OR1K_EXT1", "Address calculation error");
    }
    return busAddress;
}

//
// reflect the read onto the master bus + 0x10000000
//
static VMI_MEM_READ_FN(readcb) {

    vmiosObjectP obj = userData;

    if(bytes == 4) {
        Uns32 index = registerAddress(address);
        *(Uns32*)value = obj->registers[index];
    } else {
        vmiMessage("F", "OR1K_EXT3", "Only 32bit reads supported");
    }
}

//
// reflect the write onto the master bus + 0x10000000
//
static VMI_MEM_WRITE_FN(writecb) {

    vmiosObjectP obj = userData;

    if(bytes == 4) {
        Uns32 index = registerAddress(address);
        Uns32 v =  *(Uns32*)value;
        //vmiMessage("I", "OR1K_EXT4", "Register[%u] gets 0x%x\n", index, v);
        obj->registers[index] = v;
    } else {
        vmiMessage("F", "OR1K_EXT5", "Only 32bit writes supported");
    }
}

static VMIOS_POST_CONSTRUCTOR_FN(postConstruct) {

    vmiBusPortP bps = vmirtGetBusPortByName(processor, "bps");
    if(bps) {
        object->slaveDomain = vmirtGetBusPortDomain(processor, bps);
    }

    vmiBusPortP bpm = vmirtGetBusPortByName(processor, "bpm");
    if(bpm) {
        object->masterDomain = vmirtGetBusPortDomain(processor, bpm);
    }
    if(bps && bpm) {
        vmirtMapCallbacks(object->slaveDomain,  object->baseAddress, object->baseAddress+REG_BYTES, readcb, writecb, object);
    }
}

//
// Bus port iterator callback
//
static VMIOS_BUS_PORT_SPECS_FN(iterBusPorts) {

    if(prev) {
        prev++;
    } else {
        prev = bps;
    }
    return (prev->name) ? prev : NULL;
}

static void loadRegs(vmiProcessorP processor, vmiosObjectP object) {

    or1kP or1k = (or1kP)processor;
    Uns32 addr = or1k->regs[1];

    vmiPrintf("Extension: load %u extregs from  0x%x\n", REGISTERS, addr);
    Uns32 i;
    for(i = 0; i < REGISTERS; i++, addr += 4) {
        object->registers[i] = vmirtRead4ByteDomain(object->masterDomain, addr, ENDIAN, MEM_AA_TRUE);
        vmiPrintf("Extension: reg[%u] load 0x%x from 0x%x\n", i, object->registers[i], (Uns32)addr);
    }
}

static void saveRegs(vmiProcessorP processor, vmiosObjectP object) {

    or1kP or1k = (or1kP)processor;
    Uns32 addr = or1k->regs[1];

    vmiPrintf("Extension: save %u extregs to 0x%x\n", REGISTERS, addr);

    Uns32 i;
    for(i = 0; i < REGISTERS; i++, addr += 4) {
        vmirtWrite4ByteDomain(object->masterDomain, addr, ENDIAN, object->registers[i], MEM_AA_TRUE);
    }
}

static VMIOS_MORPH_FN(extensionMorph) {

    Uns32 inst = vmicxtFetch4Byte(processor, thisPC);

    if(inst == LOAD_REGS) {
        vmimtArgProcessor();
        vmimtArgNatAddress(object);
        vmimtCall((vmiCallFn)loadRegs);
        *opaque = True;
    } else if (inst == SAVE_REGS) {
        vmimtArgProcessor();
        vmimtArgNatAddress(object);
        vmimtCall((vmiCallFn)saveRegs);
        *opaque = True;
    } else {
        // not my instruction, do nothing
        *opaque = False;
    }

    return 0;
}

static VMIOS_DISASSEMBLE_FN(extensionDisassemble) {

    Uns32 inst = vmicxtFetch4Byte(processor, thisPC);

    if(inst == LOAD_REGS) {
        return "ldextr";
    } else if (inst == SAVE_REGS) {
        return "svextr";
    } else {
        return 0;
    }
}

//static VMIOS_NEXT_PC_FN(nextPC) {
//
//    Uns32 inst = vmicxtFetch4Byte(processor, thisPC);
//
//    if(inst == LOAD_REGS || inst == SAVE_REGS) {
//        *nextPC = thisPC + 4;
//        return True;
//    }
//    return False;
//}

////////////////////////////////////////////////////////////////////////////////
// INTERCEPT ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString = VMI_VERSION,           // version string
    .modelType     = VMI_INTERCEPT_LIBRARY, // type
    .packageName   = "MPCorePorts",         // description
    .objectSize    = sizeof(vmiosObject),  // size in bytes of OSS object
    .allLevels     = True,                  // apply at all levels

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB     = constructor,   
    .postConstructorCB = postConstruct,        

    ////////////////////////////////////////////////////////////////////////
    // PORT ACCESS ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .busPortSpecsCB  = iterBusPorts,        // bus port callback

    ////////////////////////////////////////////////////////////////////////
    // PARAMETER CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    .paramSpecsCB     = getParamSpecs,          // iterate parameter declarations
    .paramValueSizeCB = getParamTableSize,      // get parameter table size

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB          = extensionMorph,                  // morph override callback
    .disCB            = extensionDisassemble,            // disassemble instruction
    //.nextPCCB         = nextPC,

     ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts    = {{0}}
};


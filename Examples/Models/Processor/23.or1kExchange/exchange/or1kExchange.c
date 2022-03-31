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
#include "vmi/vmiCxt.h"
#include "vmi/vmiDbg.h"
#include "vmi/vmiDecode.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiMt.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiVersion.h"


#define OR1K_GPR_NUM 32
#define OR1K_BITS    32

//
// Get native endianness
//
#ifdef HOST_IS_BIG_ENDIAN
    #define ENDIAN_NATIVE MEM_ENDIAN_BIG
#else
    #define ENDIAN_NATIVE MEM_ENDIAN_LITTLE
#endif

//
// Field extraction macros
//
#define WIDTH(_W, _ARG) ((_ARG) & ((1<<(_W))-1))
#define OPEX_A(_I)      WIDTH(5,(_I)>>16)
#define OPEX_B(_I)      WIDTH(5,(_I)>>11)
#define OPEX_I(_I)      ((WIDTH(5,(_I)>>21)<<11) | WIDTH(11,(_I)>>0))

//
// Define register indices of register groups local to this extension library
//
typedef enum localGroupE {
    LR_EXCH_GROUP,      // register counting number of exchanges
    LR_EXCH_GROUP_NUM,  // KEEP LAST: for sizing
} localGroup;

//
// Define register indices of registers local to this extension library
//
typedef enum localRegE {
    LR_EXCH_COUNT,      // register counting number of exchanges
    LR_EXCH_ADDR,       // register recording last exchange address
    LR_EXCH_RD,         // register recording last exchange value read
    LR_EXCH_WR,         // register recording last exchange value written
    LR_EXCH_NUM,        // KEEP LAST: for sizing
} localReg;

//
// Define register indices of net ports local to this extension library
//
typedef enum localNetE {
    LR_EXCH_NET,        // net to which exchCount is written
    LR_EXCH_NET_NUM,    // KEEP LAST: for sizing
} localNet;

//
// Define base index number for extension registers
//
#define LOCAL_INDEX 0x1000


////////////////////////////////////////////////////////////////////////////////
// TYPES
////////////////////////////////////////////////////////////////////////////////

typedef struct vmiosObjectS {

    // handles for the OR1K GPRs
    vmiRegInfoCP or1kRegs[OR1K_GPR_NUM];

    // enhanced instruction decode table
    vmidDecodeTableP table;

    // new 32-bit registers implemented by this extension library
    Uns32 exchCount;
    Uns32 exchAddress;
    Uns32 exchRDValue;
    Uns32 exchWRValue;

    // 32-bit temporaries implemented by this extension library
    Uns32 exchTmp;

    // net written with value of exchCount
    Uns32 exchCountNetHandle;

    // descriptions of registers and register groups
    vmiRegGroup localGroups[LR_EXCH_GROUP_NUM];
    vmiRegInfo  localRegs[LR_EXCH_NUM];

    // descriptions of nets
    vmiNetPort  localNetPorts[LR_EXCH_NET_NUM];

} vmiosObject;


////////////////////////////////////////////////////////////////////////////////
// ENHANCED DECODER
////////////////////////////////////////////////////////////////////////////////

//
// This macro adds a decode table entry for a specific instruction class
//
#define DECODE_ENTRY(_PRIORITY, _NAME, _FMT) \
    vmidNewEntryFmtBin(     \
        table,              \
        #_NAME,             \
        OR1K_EIT_##_NAME,   \
        _FMT,               \
        _PRIORITY           \
    )

//
// Enhanced nstruction type enumeration
//
typedef enum or1kEnhancedInstrTypeE {

    // exchange instruction
    OR1K_EIT_EXW,

    // KEEP LAST: for sizing the array
    OR1K_EIT_LAST

} or1kEnhancedInstrType;

//
// Create the OR1K decode table
//
static vmidDecodeTableP createDecodeTable(void) {

    vmidDecodeTableP table = vmidNewDecodeTable(OR1K_BITS, OR1K_EIT_LAST);

    // handle exchnage instruction
    DECODE_ENTRY(0, EXW, "|111101..........................|");

    return table;
}


////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(constructor) {

    Uns32 i;

    // get handles to the OR1K GPRs
    for(i=0; i<OR1K_GPR_NUM; i++) {
        char regName[8];
        sprintf(regName, "R%u", i);
        object->or1kRegs[i] = vmiosGetRegDesc(processor, regName);
    }

    // create enhanced instruction decoder
    object->table = createDecodeTable();

    // fill local group descriptors
    for(i=0; i<LR_EXCH_GROUP_NUM; i++) {

        vmiRegGroupP this = &object->localGroups[i];

        // this gives group names for exchange unit register groups
        static const char *localGroupNames[] = {
            [LR_EXCH_GROUP] = "Exchange_Unit",
        };

        this->name = localGroupNames[i];
    }

    // type used to describe extension registers
    typedef struct extRegDescS {
        const char *name;           // register name
        const char *description;    // register description
        Uns32      *value;          // pointer to register value
    } extRegDesc, *extRegDescP;

    // describe extension registers
    extRegDesc extRegs[] = {
        [LR_EXCH_COUNT] = {
            name        : "exchCount",
            description : "count of exchange instructions executed",
            value       : &object->exchCount
        },
        [LR_EXCH_ADDR] = {
            name        : "exchAddress",
            description : "last exchange address",
            value       : &object->exchAddress
        },
        [LR_EXCH_RD] = {
            name        : "exchRDValue",
            description : "last value read by exchange",
            value       : &object->exchRDValue
        },
        [LR_EXCH_WR] = {
            name        : "exchWRValue",
            description : "last value written by exchange",
            value       : &object->exchWRValue
        },
    };

    // fill local register descriptors
    for(i=0; i<LR_EXCH_NUM; i++) {

        vmiRegInfoP this = &object->localRegs[i];
        extRegDescP desc = &extRegs[i];

        this->name        = desc->name;
        this->description = desc->description;
        this->group       = &object->localGroups[LR_EXCH_GROUP];
        this->gdbIndex    = LOCAL_INDEX+i;
        this->access      = vmi_RA_RW;
        this->bits        = 32;
        this->raw         = vmimtGetExtReg(processor, desc->value);
    }

    // fill local net port descriptors
    {
        vmiNetPortP this = &object->localNetPorts[0];

        this->name   = "exchCountNet";
        this->type   = vmi_NP_OUTPUT;
        this->handle = &object->exchCountNetHandle;
    }
}


////////////////////////////////////////////////////////////////////////////////
// IMPLEMENTATION OF ENHANCED EXCHANGE INSTRUCTION
////////////////////////////////////////////////////////////////////////////////

//
// Emit code implementing exchange instruction
//
static void emitExchange(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Uns32         instruction
) {
    // get processor endianness for loads and stores
    memEndian     endian     = vmirtGetProcessorDataEndian(processor);
    memConstraint constraint = MEM_CONSTRAINT_ALIGNED;

    // extract instruction fields
    Uns32 ra = OPEX_A(instruction);
    Uns32 rb = OPEX_B(instruction);
    Int16 i  = OPEX_I(instruction);

    // create vmiReg objects addressing extension registers and temporaries
    // from processor context
    vmiReg exchCount   = vmimtGetExtReg (processor, &object->exchCount);
    vmiReg exchAddress = vmimtGetExtReg (processor, &object->exchAddress);
    vmiReg exchRDValue = vmimtGetExtReg (processor, &object->exchRDValue);
    vmiReg exchWRValue = vmimtGetExtReg (processor, &object->exchWRValue);
    vmiReg exchTmp     = vmimtGetExtTemp(processor, &object->exchTmp);

    // increment count of exchange instructions executed
    vmimtBinopRC(32, vmi_ADD, exchCount, 1, 0);

    // copy rb and ra processor GPRs to exchWRValue and exchAddress
    vmimtGetR(processor, 32, exchWRValue, object->or1kRegs[rb]);
    vmimtGetR(processor, 32, exchAddress, object->or1kRegs[ra]);

    // adjust address, including constant offset
    vmimtBinopRC(32, vmi_ADD, exchAddress, i, 0);

    // load exchTmp from exchAddress
    vmimtLoadRRO(32, 32, 0, exchTmp, exchAddress, endian, False, constraint);

    // store exchWRValue to exchAddress
    vmimtStoreRRO(32, 0, exchAddress, exchWRValue, endian, constraint);

    // copy exchTmp to exchRDValue
    vmimtMoveRR(32, exchRDValue, exchTmp);

    // copy exchTmp to processor GPR
    vmimtSetR(processor, 32, object->or1kRegs[rb], exchTmp);

    // write exchCountNet if required
    if(object->exchCountNetHandle) {
        vmimtArgProcessor();
        vmimtArgUns32(object->exchCountNetHandle);
        vmimtArgReg(32, exchCount);
        vmimtCallResultAttrs(
            (vmiCallFn)vmirtWriteNetPort, 0, VMI_NOREG, VMCA_NA
        );
    }
}

//
// Morpher callback implementing exchange instructions
//
static VMIOS_MORPH_FN(exchangeMorph) {

    // decode the instruction to get the type
    UnsPS                 instruction = vmicxtFetch4Byte(processor, thisPC);
    or1kEnhancedInstrType type        = vmidDecode(object->table, instruction);

    if(type==OR1K_EIT_EXW) {

        // instruction is enhanced exchange
        emitExchange(processor, object, instruction);

        // indicate standard behavior has been replaced
        *opaque = True;
    }

    // no intercept callback specified
    return 0;
}

//
// Return instruction address after passed program counter
//
static VMIOS_NEXT_PC_FN(exchangeNextPC) {

    // decode the instruction to get the type
    Uns32                 instruction = vmicxtFetch4Byte(processor, thisPC);
    or1kEnhancedInstrType type        = vmidDecode(object->table, instruction);

    if(type==OR1K_EIT_EXW) {
        *nextPC = thisPC+4;
        return True;
    } else {
        return False;
    }
}

//
// Disassembler callback disassembling exchange instructions
//
static VMIOS_DISASSEMBLE_FN(exchangeDisass) {

    // decode the instruction to get the type
    Uns32                 instruction = vmicxtFetch4Byte(processor, thisPC);
    or1kEnhancedInstrType type        = vmidDecode(object->table, instruction);

    if(type==OR1K_EIT_EXW) {

        // instruction is enhanced exchange
        static char buffer[256];

        // extract instruction fields
        Uns32 ra = OPEX_A(instruction);
        Uns32 rb = OPEX_B(instruction);
        Int16 i  = OPEX_I(instruction);

        sprintf(buffer, "%-8s 0x%x(r%u),r%u", "l.exw", i, ra, rb);

        return buffer;

    } else {

        // instruction not enhanced exchange
        return 0;
    }
}

//
// Register group iterator callback
//
static VMIOS_REG_GROUP_FN(exchangeIterRegGroup) {

    vmiRegGroupP first = object->localGroups;

    if(!prev) {
        return first;
    } else {
        localGroup nextIndex = (prev-first)+1;
        return nextIndex<LR_EXCH_GROUP_NUM ? first+nextIndex : 0;
    }
}

//
// Register iterator callback
//
static VMIOS_REG_INFO_FN(exchangeIterRegInfo) {

    vmiRegInfoP first = object->localRegs;

    if(type!=VMIRIT_NORMAL) {
        return 0;
    } else if(!prev) {
        return first;
    } else {
        localReg nextIndex = (prev-first)+1;
        return nextIndex<LR_EXCH_NUM ? first+nextIndex : 0;
    }
}

//
// Net port iterator callback
//
static VMIOS_NET_PORT_SPECS_FN(exchangeIterNetPorts) {

    vmiNetPortP first = object->localNetPorts;

    if(!prev) {
        return first;
    } else {
        localNet nextIndex = (prev-first)+1;
        return nextIndex<LR_EXCH_NET_NUM ? first+nextIndex : 0;
    }
}

////////////////////////////////////////////////////////////////////////////////
// INTERCEPT ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString = VMI_VERSION,           // version string
    .modelType     = VMI_INTERCEPT_LIBRARY, // type
    .packageName   = "Exchange",            // description
    .objectSize    = sizeof(vmiosObject),   // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB = constructor,           // object constructor

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB       = exchangeMorph,         // morph callback
    .nextPCCB      = exchangeNextPC,        // get next instruction address
    .disCB         = exchangeDisass,        // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // DEBUGGER INTEGRATION SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .regGroupCB    = exchangeIterRegGroup,  // regGroup callback
    .regInfoCB     = exchangeIterRegInfo,   // regInfo callback

    ////////////////////////////////////////////////////////////////////////
    // PORT ACCESS ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .netPortSpecsCB = exchangeIterNetPorts, // net port callback

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts    = {{0}}
};


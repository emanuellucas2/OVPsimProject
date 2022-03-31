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

// prefix for messages from this extension
#define CPU_PREFIX "FIFO"

// standard includes
#include <stdio.h>
#include <string.h>

// Imperas header files
#include "hostapi/impAlloc.h"

// VMI area includes
#include "vmi/vmiCxt.h"
#include "vmi/vmiDbg.h"
#include "vmi/vmiDecode.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiMt.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiDoc.h"
#include "vmi/vmiParameters.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiVersion.h"

// extension header files
#include "fifoConfig.h"
#include "fifoCSR.h"

// processor model header files
#include "extensionConfig.h"

// base model header files
#include "riscvCSRTypes.h"
#include "riscvDisassembleFormats.h"
#include "riscvStructure.h"


////////////////////////////////////////////////////////////////////////////////
// EXTENSION CSR IDENTIFIERS
////////////////////////////////////////////////////////////////////////////////

typedef enum extCSRIdE {

    // FIFO configuration control and status registers
    XCSR_ID (fifo_cfg),     // 0xFF0

    // keep last (used to define size of the enumeration)
    XCSR_ID (LAST)

} extCSRId;


////////////////////////////////////////////////////////////////////////////////
// FIFO EXTENSION OBJECT
////////////////////////////////////////////////////////////////////////////////

typedef struct vmiosObjectS {

    // Info for associated processor
    riscvP           riscv;

    // parameters
    vmiParameterP    parameters;

    // is this extension enabled?
    Bool             enabled;

    // temporary FIFO element
    Uns64            FIFOTmp;

    // configuration (including CSR reset values)
    fifoConfig       config;

    // extension CSR info
    fifoCSRs         csr;                   // FIFO extension CSR values
    riscvCSRAttrs    csrs[XCSR_ID(LAST)];   // modified CSR definitions

    // FIFO connections
    vmiFifoPortP     fifoPorts;             // fifo port descriptions
    vmiConnInputP    inputConn;             // input FIFO connection
    vmiConnOutputP   outputConn;            // output FIFO connection

    // extended instruction decode table
    vmidDecodeTableP decode32;

    // extension callbacks
    riscvExtCB       extCB;

} vmiosObject;


////////////////////////////////////////////////////////////////////////////////
// UTILITIES
////////////////////////////////////////////////////////////////////////////////

//
// Return FIFO configuration
//
static fifoConfigCP getExtConfig(riscvP riscv) {
    riscvExtConfigCP cfg = riscv->cb.getExtConfig(riscv, EXTID_FIFO);
    VMI_ASSERT(cfg, "FIFO config not found");
    return cfg->userData;
}


////////////////////////////////////////////////////////////////////////////////
// EXTENSION CSRS
////////////////////////////////////////////////////////////////////////////////

//
// CSR table
//
static const extCSRAttrs csrs[XCSR_ID(LAST)] = {

    //            name      num    arch extension attrs    description           rCB rwCB wCB
    XCSR_ATTR_T__(fifo_cfg, 0xFF0, 0,   EXT_FIFO, 0,0,0,0, "FIFO Configuration", 0,  0,   0)
};

//
// Validate the presence of one extension
//
#define EXTENSION_CHECK(_OBJ, _REQUIRED, _REG, _FIELD, _EXT) \
    if((_REQUIRED & _EXT) && !RD_XCSR_FIELD(object, _REG, _FIELD)) {    \
        return False;                                                   \
    }

//
// Indicate whether the FIFO extension is present
//
static Bool extensionPresent(vmiosObjectP object, fifoVariant required) {

    // validate FIFO register presence
    EXTENSION_CHECK(object, required, fifo_cfg, fifoPresent, EXT_FIFO);

    return True;
}

//
// Initialize CSR registers
//
static void fifoCSRInit(vmiosObjectP object) {

    riscvP   riscv = object->riscv;
    extCSRId id;

    // initialise CSR values that have configuration values defined
    WR_XCSR(object, fifo_cfg, object->config.csr.fifo_cfg.u64.bits);

    // register each CSR with the base model
    for(id=0; id<XCSR_ID(LAST); id++) {

        extCSRAttrsCP  src = &csrs[id];
        riscvCSRAttrs *dst = &object->csrs[id];

        if(extensionPresent(object, src->extension)) {
            riscv->cb.newCSR(dst, &src->baseAttrs, riscv, object);
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
// EXTENSION INSTRUCTION DECODE
////////////////////////////////////////////////////////////////////////////////

//
// This enumerates generic instructions
//
typedef enum riscvExtITypeE {

    // extension instructions
    EXT_IT_PUSHB,
    EXT_IT_POPB,

    // KEEP LAST
    EXT_IT_LAST

} riscvExtIType;

//
// This specifies attributes for each 32-bit opcode
//
const static riscvExtInstrAttrs attrsArray32[] = {
    //                                                                      |   dec      | rs1 |fn3| rd  | dec   |
    EXT_INSTRUCTION(EXT_IT_PUSHB, "pushb", RVANY, RVIP_RD_RS1_RS2, FMT_R1, "|000000000000|00000|000|.....|0001011|"),
    EXT_INSTRUCTION(EXT_IT_POPB,  "popb",  RVANY, RVIP_RD_RS1_RS2, FMT_R1, "|000000000000|00000|001|.....|0001011|"),
};

//
// Decode instruction at the given address
//
static riscvExtIType decode(
    riscvP             riscv,
    vmiosObjectP       object,
    riscvAddr          thisPC,
    riscvExtInstrInfoP info
) {
    return riscv->cb.fetchInstruction(
        riscv, thisPC, info, &object->decode32, attrsArray32, EXT_IT_LAST, 32
    );
}


////////////////////////////////////////////////////////////////////////////////
// EXTENSION INSTRUCTION DISASSEMBLY
////////////////////////////////////////////////////////////////////////////////

//
// Disassembler, VMI interface
//
static VMIOS_DISASSEMBLE_FN(fifoDisassemble) {

    riscvP            riscv  = (riscvP)processor;
    const char       *result = 0;
    riscvExtInstrInfo info;

    // action is only required if the instruction is implemented by this
    // extension
    if(decode(riscv, object, thisPC, &info) != EXT_IT_LAST) {
        result = riscv->cb.disassInstruction(riscv, &info, attrs);
    }

    return result;
}


////////////////////////////////////////////////////////////////////////////////
// BASE MODEL INSTUCTION UTILITY FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

//
// Return riscvRegDesc for the indexed register
//
inline static riscvRegDesc getRVReg(riscvExtMorphStateP state, Uns32 argNum) {
    return state->info.r[argNum];
}

//
// Return VMI register for the given abstract register
//
inline static vmiReg getVMIReg(riscvP riscv, riscvRegDesc r) {
    return riscv->cb.getVMIReg(riscv, r);
}


////////////////////////////////////////////////////////////////////////////////
// EXTENSION REGISTER ACCESS UTILITIES
////////////////////////////////////////////////////////////////////////////////

//
// Return VMI register for extension object field
//
inline static vmiReg getExtReg(vmiosObjectP object, void *field) {
    return vmimtGetExtReg((vmiProcessorP)(object->riscv), field);
}

//
// Return configured connection bits
//
inline static Uns32 getConnBits(vmiosObjectP object) {
    return object->config.FIFO_bits;
}

//
// Return VMI register for connection temporary
//
inline static vmiReg getFIFOTmp(vmiosObjectP object) {
    return getExtReg(object, &object->FIFOTmp);
}

//
// Return VMI register for input connection object
//
inline static vmiReg getInputConn(vmiosObjectP object) {
    return getExtReg(object, &object->inputConn);
}

//
// Return VMI register for output connection object
//
inline static vmiReg getOutputConn(vmiosObjectP object) {
    return getExtReg(object, &object->outputConn);
}


////////////////////////////////////////////////////////////////////////////////
// INSTRUCTION CALLBACKS
////////////////////////////////////////////////////////////////////////////////

//
// Emit code implementing blocking FIFO push
//
static EXT_MORPH_FN(emitPUSHB) {

    vmiosObjectP object   = state->object;
    riscvP       riscv    = state->riscv;
    riscvRegDesc rs       = getRVReg(state, 0);
    vmiReg       rsA      = getVMIReg(riscv, rs);
    vmiReg       conn     = getOutputConn(object);
    Uns32        bits     = getRBits(rs);
    Uns32        connBits = getConnBits(object);

    // zero-extend source value to temporary if connection is wider than GPR
    if(bits<connBits) {
        vmiReg tmp = getFIFOTmp(object);
        vmimtMoveExtendRR(connBits, tmp, bits, rsA, False);
        rsA = tmp;
    }

    // put value
    vmimtConnPutRB(connBits, conn, rsA, 0);
}

//
// Emit code implementing blocking FIFO pop
//
static EXT_MORPH_FN(emitPOPB) {

    vmiosObjectP object   = state->object;
    riscvP       riscv    = state->riscv;
    riscvRegDesc rd       = getRVReg(state, 0);
    vmiReg       rdA      = getVMIReg(riscv, rd);
    vmiReg       conn     = getInputConn(object);
    Uns32        bits     = getRBits(rd);
    Uns32        connBits = getConnBits(object);
    Uns32        tmpBits  = (connBits<bits) ? connBits : bits;
    vmiReg       tmp      = getFIFOTmp(object);

    // get value into temporary
    vmimtConnGetRB(connBits, tmp, conn, False, 0);

    // commit value, zero-extending if necessary
    vmimtMoveExtendRR(bits, rdA, tmpBits, tmp, False);
}


////////////////////////////////////////////////////////////////////////////////
// INSTRUCTION TRANSLATION
////////////////////////////////////////////////////////////////////////////////

//
// Dispatch table for instruction translation
//
const static riscvExtMorphAttr dispatchTable[] = {
    [EXT_IT_PUSHB] = {morph:emitPUSHB, variant:EXT_FIFO},
    [EXT_IT_POPB]  = {morph:emitPOPB,  variant:EXT_FIFO},
};

//
// Validate that the instruction is supported and enabled and return a reason
// string if not
//
static const char *getDisableReason(vmiosObjectP object, fifoVariant variant) {

    fifoVariant availableVariants = object->config.variant;
    const char *result            = 0;

    // validate feature is present
    if(!object->enabled || ((availableVariants & variant) != variant)) {
        result = "Unimplemented on this variant";
    }

    return result;
}

//
// Instruction translation
//
static VMIOS_MORPH_FN(fifoMorph) {

    riscvP             riscv = (riscvP)processor;
    riscvExtMorphState state = {riscv:riscv, object:object};

    // get instruction and instruction type
    riscvExtIType type = decode(riscv, object, thisPC, &state.info);

    // action is only required if the instruction is implemented by this
    // extension
    if(type != EXT_IT_LAST) {

        riscvExtMorphAttrCP attrs  = &dispatchTable[type];
        const char         *reason = getDisableReason(object, attrs->variant);

        // fill translation attributes
        state.attrs = attrs;

        // translate instruction
        riscv->cb.morphExternal(&state, reason, opaque);
    }

    // no callback function is required
    return 0;
}


////////////////////////////////////////////////////////////////////////////////
// EXTENSION DOCUMENTATION
////////////////////////////////////////////////////////////////////////////////

//
// Add documentation for fifo instructions
//
static void docFifo(
    vmiDocNodeP insts,
    const char *opcode,
    const char *decode,
    const char *desc
) {
    vmiDocNodeP inst = vmidocAddFields(insts, opcode, 32);

    // fields
    vmidocAddField(inst, "Custom0 0001011",     0, 7);
    vmidocAddField(inst, "Rdata",               7, 5);
    vmidocAddField(inst, decode,               12, 3);
    vmidocAddField(inst, "00000",              15, 5);
    vmidocAddField(inst, "00000",              20, 5);
    vmidocAddField(inst, "0000000",            25, 7);

    // description
    vmidocAddText(inst, desc);
}

//
// Add documentation for Custom instructions
//
static VMIOS_DOC_FN(fifoDoc) {

    if (object->enabled) {

        vmiDocNodeP custom = vmidocAddSection(0, "Instruction Extensions");

        // description
        vmidocAddText(
            custom,
            "RISCV processors may add various custom extensions to the basic "
            "RISC-V architecture. "
            "This processor has been extended, using an extension library, "
            "to add FIFO instructions to the Custom0 opcode space, "
            "and FIFO ports."
        );
        vmiDocNodeP insts = vmidocAddSection(
            custom, "Custom Instructions"
        );

        vmidocAddText(
            insts,
            "This model includes two FIFO instructions "
            "Note: these are blocking instructions.");

        docFifo(insts, "pushb", "000", "push(Rdata) - block if full");
        docFifo(insts, "popb",  "001", "pop(Rdata) - block if empty");

        vmidocProcessor(processor, custom);
    }
}


////////////////////////////////////////////////////////////////////////////////
// EXTENSION FIFO PORTS
////////////////////////////////////////////////////////////////////////////////

//
// Return number of members of an array
//
#define NUM_MEMBERS(_A) (sizeof(_A)/sizeof((_A)[0]))

//
// Return offset of the given field in the extension object
//
#define EXTENSION_FIELD_OFFSET(_F) ((void *)VMI_CPU_OFFSET(vmiosObjectP, _F))

//
// Template FIFO port list
//
static vmiFifoPort fifoPorts[] = {
    {"fifoPortIn" , vmi_FIFO_INPUT,  0, EXTENSION_FIELD_OFFSET(inputConn) },
    {"fifoPortOut", vmi_FIFO_OUTPUT, 0, EXTENSION_FIELD_OFFSET(outputConn)}
};

//
// Allocate FIFO port structure
//
static void newFifoPorts(vmiosObjectP object) {

    Uns32 connBits = getConnBits(object);
    Uns32 i;

    object->fifoPorts = STYPE_CALLOC_N(vmiFifoPort, NUM_MEMBERS(fifoPorts));

    for(i=0; i<NUM_MEMBERS(fifoPorts); i++) {

        object->fifoPorts[i] = fifoPorts[i];

        // correct FIFO port bit size
        object->fifoPorts[i].bits = connBits;

        // correct FIFO port handle
        Uns8 *raw = (Uns8*)(object->fifoPorts[i].handle);
        object->fifoPorts[i].handle = (void **)(raw + (UnsPS)object);
    }
}

//
// Get the next fifo port, if enabled
//
static VMIOS_FIFO_PORT_SPECS_FN(fifoGetPortSpec) {

    if (!object->enabled) {

        // Do not implement ports when not enabled
        return NULL;

    } else if(!prev) {

        // first port
        return object->fifoPorts;

    } else {

        // port other than the first
        Uns32 prevIndex = (prev-object->fifoPorts);
        Uns32 thisIndex = prevIndex+1;

        return (thisIndex<NUM_MEMBERS(fifoPorts)) ? &object->fifoPorts[thisIndex] : 0;
    }
}


////////////////////////////////////////////////////////////////////////////////
// EXTENSION PARAMETERS
////////////////////////////////////////////////////////////////////////////////

//
// Parameter value structure
//
typedef struct paramValuesS {

    // simulation controls
    VMI_UNS32_PARAM(FIFO_bits);

} paramValues, *paramValuesP;

//
// This function type is used to specify the default value for a parameter
//
#define EXT_PDEFAULT_FN(_NAME) void _NAME(fifoConfigCP cfg, vmiParameterP param)
typedef EXT_PDEFAULT_FN((*extPDefaultFn));

//
// Parameter list including variant information
//
typedef struct riscvParameterS {
    extPDefaultFn defaultCB;
    vmiParameter  parameter;
} riscvParameter, *riscvParameterP;

//
// Validate parameter type
//
#define CHECK_PARAM_TYPE(_P, _T, _NAME) VMI_ASSERT( \
    _P->type==_T,                                   \
    "parameter %s is not of "_NAME" type",          \
    _P->name                                        \
)

//
// Set Uns32 parameter default
//
static void setUns32ParamDefault(vmiParameterP param, Uns32 value) {
    CHECK_PARAM_TYPE(param, vmi_PT_UNS32, "Uns32");
    param->u.uns32Param.defaultValue = value;
}

//
// Macro to define a function to set an Uns64 CSR parameter value from the
// configuration
//
#define EXT_UNS32_PDEFAULT_CFG_FN(_NAME) EXT_PDEFAULT_FN(default_##_NAME) { \
    setUns32ParamDefault(param, cfg->_NAME);  \
}

//
// Set default value of raw Uns32 parameters
//
static EXT_UNS32_PDEFAULT_CFG_FN(FIFO_bits)

//
// Table of formal parameter specifications
//
static riscvParameter formals[] = {

    {default_FIFO_bits, VMI_UNS32_PARAM_SPEC (paramValues, FIFO_bits, 32, 8, 64, "Specify FIFO element bits")},

    // KEEP LAST
    {0,                 VMI_END_PARAM}
};

//
// Should this parameter be presented as a public one for the selected variant?
//
static Bool selectParameter(fifoConfigCP cfg, riscvParameterP param) {
    return True;
}

//
// Count the number of visible parameters
//
static Uns32 countParameters(fifoConfigCP cfg, riscvParameterP param) {

    Uns32 i = 0;

    while(param->parameter.name) {

        if(selectParameter(cfg, param)) {
            i++;
        }

        param++;
    }

    return i;
}

//
// Create parameter list applicable to the indicated variant
//
static vmiParameterP createParameterList(
    riscvP       riscv,
    vmiosObjectP object,
    fifoConfigCP cfg
) {
    riscvParameterP src = formals;
    vmiParameterP   dst;
    vmiParameterP   result;
    Uns32           i;

    // count the number of entries in the parameter list
    Uns32 entries = countParameters(cfg, src);

    // allocate the parameter list, including NULL terminator
    result = STYPE_CALLOC_N(vmiParameter, entries+1);

    // fill visible entries in the variant list
    for(i=0, dst=result; src->parameter.name; i++, src++) {

        if(selectParameter(cfg, src)) {

            *dst = src->parameter;

            // override default if required
            if(src->defaultCB) {
                src->defaultCB(cfg, dst);
            }

            dst++;
        }
    }

    // return resulting list
    return result;
}

//
// Iterate formals
//
static VMIOS_PARAM_SPEC_FN(fifoParamSpecs) {

    // create parameter definition list if required
    if(!object->parameters) {

        riscvP       riscv = (riscvP)processor;
        fifoConfigCP cfg   = getExtConfig(riscv);

        object->parameters = createParameterList(riscv, object, cfg);
    }

    vmiParameterP this = prev ? prev+1 : object->parameters;

    return this->name ? this : NULL;
}

//
// Return size of parameter structure
//
static VMIOS_PARAM_TABLE_SIZE_FN(fifoParamTableSize) {

    return sizeof(paramValues);
}


////////////////////////////////////////////////////////////////////////////////
// EXTENSION CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(fifoConstructor) {

    riscvP       riscv  = (riscvP)processor;
    paramValuesP params = parameterValues;

    object->riscv = riscv;

    // prepare client data
    object->extCB.clientData = object;

    // register extension with base model
    riscv->cb.registerExtCB(riscv, &object->extCB, EXTID_FIFO);

    // copy configuration from template
    object->config = *getExtConfig(riscv);

    // override parameterized values
    object->config.FIFO_bits = params->FIFO_bits;

    // initialize CSRs
    fifoCSRInit(object);

    // is extension enabled in config info?
    object->enabled = RD_XCSR_FIELD(object, fifo_cfg, fifoPresent);

    // create fifoPorts
    newFifoPorts(object);
}


////////////////////////////////////////////////////////////////////////////////
// EXTENSION ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString = VMI_VERSION,           // version string
    .modelType     = VMI_INTERCEPT_LIBRARY, // type
    .packageName   = "fifoExtensions",      // description
    .objectSize    = sizeof(vmiosObject),   // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB = fifoConstructor,       // object constructor
    .docCB         = fifoDoc,               // documentation constructor

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB       = fifoMorph,             // instruction translation callback
    .disCB         = fifoDisassemble,       // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // PORT ACCESS ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .fifoPortSpecsCB = fifoGetPortSpec,     // callback for next fifo port

    ////////////////////////////////////////////////////////////////////////
    // PARAMETER CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    .paramSpecsCB     = fifoParamSpecs,     // iterate parameter declarations
    .paramValueSizeCB = fifoParamTableSize, // get parameter table size

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts    = {{0}}
};


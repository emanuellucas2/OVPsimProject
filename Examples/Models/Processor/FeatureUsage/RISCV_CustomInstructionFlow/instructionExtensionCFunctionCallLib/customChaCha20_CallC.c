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

// VMI area includes
#include "vmi/vmiMt.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiDoc.h"

// RISCV Base Model inclusions
#include "riscvDisassembleFormats.h"
#include "riscvStructure.h"


//
// Identifier for this extension (required if mode than one closely-coupled
// extension is present)
//
#define EXTID_CHACHA 0xcaca


////////////////////////////////////////////////////////////////////////////////
// TYPES
////////////////////////////////////////////////////////////////////////////////

typedef struct vmiosObjectS {

    // Info for associated processor
    riscvP           riscv;

    // extended instruction decode table
    vmidDecodeTableP decode32;

    // extension callbacks
    riscvExtCB       extCB;

} vmiosObject;


////////////////////////////////////////////////////////////////////////////////
// EXTENSION INSTRUCTION DECODE
////////////////////////////////////////////////////////////////////////////////

//
// This enumerates generic instructions
//
typedef enum riscvExtITypeE {

    // extension instructions
    EXT_IT_CHACHA20QR1,
    EXT_IT_CHACHA20QR2,
    EXT_IT_CHACHA20QR3,
    EXT_IT_CHACHA20QR4,

    // KEEP LAST
    EXT_IT_LAST

} riscvExtIType;

//
// This specifies attributes for each 32-bit opcode
//
const static riscvExtInstrAttrs attrsArray32[] = {
    //                                                                                        |   dec | rs2 | rs1 |fn3| rd  | dec   |
    EXT_INSTRUCTION(EXT_IT_CHACHA20QR1, "chacha20qr1", RVANY, RVIP_RD_RS1_RS2, FMT_R1_R2_R3, "|0000000|.....|.....|000|.....|0001011|"),
    EXT_INSTRUCTION(EXT_IT_CHACHA20QR2, "chacha20qr2", RVANY, RVIP_RD_RS1_RS2, FMT_R1_R2_R3, "|0000000|.....|.....|001|.....|0001011|"),
    EXT_INSTRUCTION(EXT_IT_CHACHA20QR3, "chacha20qr3", RVANY, RVIP_RD_RS1_RS2, FMT_R1_R2_R3, "|0000000|.....|.....|010|.....|0001011|"),
    EXT_INSTRUCTION(EXT_IT_CHACHA20QR4, "chacha20qr4", RVANY, RVIP_RD_RS1_RS2, FMT_R1_R2_R3, "|0000000|.....|.....|011|.....|0001011|")
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
static VMIOS_DISASSEMBLE_FN(chachaDisassemble) {

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

//
// Do actions when a register is written (extending or NaN boxing, if
// required) using the given source register size
//
inline static void writeRegSize(
    riscvP       riscv,
    riscvRegDesc r,
    Uns32        srcBits,
    Bool         signExtend
) {
    riscv->cb.writeRegSize(riscv, r, srcBits, signExtend);
}


////////////////////////////////////////////////////////////////////////////////
// INSTRUCTION TRANSLATION
////////////////////////////////////////////////////////////////////////////////

static Uns32 qrN_c(Uns32 rs1, Uns32 rs2, Uns32 rotl) {
    return ((rs1 ^ rs2) << rotl) | ((rs1 ^ rs2) >> (32-rotl));
}

//
// Emit code implementing CHACHA20QR instruction with rotation passed as
// userData in morph attributes structure
//
static EXT_MORPH_FN(emitCHACHA20QR) {

    riscvP riscv = state->riscv;

    // get abstract register operands
    riscvRegDesc rd  = getRVReg(state, 0);
    riscvRegDesc rs1 = getRVReg(state, 1);
    riscvRegDesc rs2 = getRVReg(state, 2);

    // get VMI registers for abstract operands
    vmiReg rdA  = getVMIReg(riscv, rd);
    vmiReg rs1A = getVMIReg(riscv, rs1);
    vmiReg rs2A = getVMIReg(riscv, rs2);

    // emit embedded call to perform operation
    UnsPS rotl = (UnsPS)state->attrs->userData;
    Uns32 bits = 32;
    vmimtArgReg(bits, rs1A);
    vmimtArgReg(bits, rs2A);
    vmimtArgUns32(rotl);
    vmimtCallResult((vmiCallFn)qrN_c, bits, rdA);

    // handle extension of result if 64-bit XLEN
    writeRegSize(riscv, rd, bits, True);
}

//
// Dispatch table for instruction translation
//
const static riscvExtMorphAttr dispatchTable[] = {
    [EXT_IT_CHACHA20QR1] = {morph:emitCHACHA20QR, userData:(void *)16},
    [EXT_IT_CHACHA20QR2] = {morph:emitCHACHA20QR, userData:(void *)12},
    [EXT_IT_CHACHA20QR3] = {morph:emitCHACHA20QR, userData:(void *) 8},
    [EXT_IT_CHACHA20QR4] = {morph:emitCHACHA20QR, userData:(void *) 7},
};

//
// Instruction translation
//
static VMIOS_MORPH_FN(chachaMorph) {

    riscvP             riscv = (riscvP)processor;
    riscvExtMorphState state = {riscv:riscv, object:object};

    // decode instruction
    riscvExtIType type = decode(riscv, object, thisPC, &state.info);

    // action is only required if the instruction is implemented by this
    // extension
    if(type != EXT_IT_LAST) {

        // fill translation attributes
        state.attrs = &dispatchTable[type];

        // translate instruction
        riscv->cb.morphExternal(&state, 0, opaque);
    }

    // no callback function is required
    return 0;
}


////////////////////////////////////////////////////////////////////////////////
// DOCUMENTATION
////////////////////////////////////////////////////////////////////////////////

//
// Add documentation for ChaCha20 instructions
//
static void docChaCha20(
    vmiDocNodeP insts,
    const char *opcode,
    const char *decode,
    const char *desc
) {
    vmiDocNodeP inst = vmidocAddFields(insts, opcode, 32);

    // fields
    vmidocAddField(inst, "Custom0 0001011",     0, 7);
    vmidocAddField(inst, "Rd",                  7, 5);
    vmidocAddField(inst, decode,               12, 3);
    vmidocAddField(inst, "Rs1",                15, 5);
    vmidocAddField(inst, "Rs2",                20, 5);
    vmidocAddField(inst, "0000000",            25, 7);

    // description
    vmidocAddText(inst, desc);
}

//
// Add documentation for Custom instructions
//
static VMIOS_DOC_FN(chachaDoc) {

    vmiDocNodeP custom = vmidocAddSection(0, "Instruction Extensions");

    // description
    vmidocAddText(
        custom,
        "RISCV processors may add various custom extensions to the basic "
        "RISC-V architecture. "
        "This processor has been extended, using an extension library, "
        "to add several instruction using the Custom0 opcode."
    );
    vmiDocNodeP insts = vmidocAddSection(
        custom, "Custom Instructions"
    );

    vmidocAddText(
        insts,
        "This model includes four Chacha20 acceleration instructions "
        "(one for each rotate distance) are added to encode the XOR "
        "and ROTATE parts of the quarter rounds.");

    docChaCha20(insts, "chacha20qr1", "000 (QR1)", "dst = (src1 ^ src2) <<< 16");
    docChaCha20(insts, "chacha20qr2", "001 (QR2)", "dst = (src1 ^ src2) <<< 12");
    docChaCha20(insts, "chacha20qr3", "010 (QR3)", "dst = (src1 ^ src2) <<<  8");
    docChaCha20(insts, "chacha20qr4", "011 (QR4)", "dst = (src1 ^ src2) <<<  7");

    vmidocProcessor(processor, custom);
}


////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(chachaConstructor) {

    riscvP riscv = (riscvP)processor;

    object->riscv = riscv;

    // prepare client data
    object->extCB.clientData = object;

    // register extension with base model
    riscv->cb.registerExtCB(riscv, &object->extCB, EXTID_CHACHA);
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
    .packageName   = "ChaCha20",            // description
    .objectSize    = sizeof(vmiosObject),   // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB = chachaConstructor,     // object constructor
    .docCB         = chachaDoc,             // doc constructor

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB       = chachaMorph,           // instruction morph callback
    .disCB         = chachaDisassemble,     // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts    = {{0}}
};


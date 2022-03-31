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
#define CPU_PREFIX "ADD_INST"

// VMI area includes
#include "vmi/vmiMt.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"

// processor model header files
#include "extensionConfig.h"

// base model header files
#include "riscvDisassembleFormats.h"
#include "riscvStructure.h"


/*
DESCRIPTION
-----------
This example shows how to add custom instructions to a RISC-V model.

Each section below has further explanatory notes.
*/


////////////////////////////////////////////////////////////////////////////////
// EXTENSION OBJECT
////////////////////////////////////////////////////////////////////////////////

/*
NOTES
-----
1. This type holds all information added by an instance of this extension.
2. The decode32 field is required to implement instruction decode.
3. The extCB field holds function pointers and other data implementing
   communication between the base RISC-V model and the extension.
*/

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

/*
NOTES
-----
1. Enumeration riscvExtIType lists each distinct instruction type
2. There is am entry in attrsArray32 for each instruction type. Arguments are:
   2.1. Instruction enumeration member.
   2.2. Instruction opcode.
   2.3. Instruction restrictions (RVANY means unrestricted).
   2.4. Instruction argument pattern.
   2.5. Instruction disassembly format string.
   2.6. Instruction decode string (1/0 bits, . don't care bits and ignored |
        characters)
3. Interface function fetchInstruction decodes an instruction using the decode
   table, returning the enumeration member or EXT_IT_LAST if not decoded.
   Arguments are:
   3.1. The RISC-V processor.
   3.2. The instruction address.
   3.3. A structure of type riscvExtInstrInfoP filled with information about
        the instruction if it is decoded.
   3.4. A pointer to the decode table in the vmiosObject. fetchInstruction uses
        this to cache decode information.
   3.5. A pointer to the instruction table.
   3.6. A code to return if decode fails.
   3.7. The instruction size in bits.
*/

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
    EXT_INSTRUCTION(EXT_IT_CHACHA20QR1, "chacha20qr1", RVANY, RVIP_RD_RS1_RS2, FMT_R1_R2_R3, "|0000001|.....|.....|000|.....|0001011|"),
    EXT_INSTRUCTION(EXT_IT_CHACHA20QR2, "chacha20qr2", RVANY, RVIP_RD_RS1_RS2, FMT_R1_R2_R3, "|0000001|.....|.....|001|.....|0001011|"),
    EXT_INSTRUCTION(EXT_IT_CHACHA20QR3, "chacha20qr3", RVANY, RVIP_RD_RS1_RS2, FMT_R1_R2_R3, "|0000001|.....|.....|010|.....|0001011|"),
    EXT_INSTRUCTION(EXT_IT_CHACHA20QR4, "chacha20qr4", RVANY, RVIP_RD_RS1_RS2, FMT_R1_R2_R3, "|0000001|.....|.....|011|.....|0001011|")
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
// BASE MODEL INSTRUCTION UTILITY FUNCTIONS
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
static VMIOS_MORPH_FN(addInstructionsMorph) {

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
// EXTENSION INSTRUCTION DISASSEMBLY
////////////////////////////////////////////////////////////////////////////////

//
// Disassembler, VMI interface
//
static VMIOS_DISASSEMBLE_FN(addInstructionsDisassemble) {

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
// EXTENSION CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

/*
NOTES
-----
1. For use with this extension infrastructure, two things must be done in the
   constructor:
   1.1. The clientData pointer in the extCB interface object must be set to
        the vmiosObject;
   1.2. The extension interface must be registered with the base model using
        the registerExtCB interface function;
   Typically the constructor will also save a reference to the current
   processor and perform other initialisation, as shown below.
*/

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(addInstructionsConstructor) {

    riscvP riscv  = (riscvP)processor;

    object->riscv = riscv;

    // prepare client data
    object->extCB.clientData = object;

    // register extension with base model using unique ID
    riscv->cb.registerExtCB(riscv, &object->extCB, EXTID_ADDINST);
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
    .packageName   = "addCSRs",             // description
    .objectSize    = sizeof(vmiosObject),   // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB = addInstructionsConstructor,    // object constructor

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB       = addInstructionsMorph,          // instruction morph callback
    .disCB         = addInstructionsDisassemble,    // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts    = {{0}}
};


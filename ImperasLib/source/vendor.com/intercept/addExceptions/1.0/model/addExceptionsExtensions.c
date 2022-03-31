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
#define CPU_PREFIX "ADD_EXCEPT"

// VMI area includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiMt.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"

// processor model header files
#include "extensionConfig.h"

// base model header files
#include "riscvDisassembleFormats.h"
#include "riscvMessage.h"
#include "riscvStructure.h"


/*
DESCRIPTION
-----------
This example shows how to add custom exceptions to a RISC-V model. An
instruction is also added to trigger the new exception.

Each section below has further explanatory notes.
*/


////////////////////////////////////////////////////////////////////////////////
// CUSTOM EXCEPTION NUMBERS
////////////////////////////////////////////////////////////////////////////////

//
// Custom exceptions
//
typedef enum riscvExtExceptionE {
    EXT_E_EXCEPT24 = 24,
} riscvExtException;


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
// UTILITIES
////////////////////////////////////////////////////////////////////////////////

//
// Return current program counter
//
inline static Uns64 getPC(riscvP riscv) {
    return vmirtGetPC((vmiProcessorP)riscv);
}


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
    EXT_IT_EXCEPT24,

    // KEEP LAST
    EXT_IT_LAST

} riscvExtIType;

//
// This specifies attributes for each 32-bit opcode
//
const static riscvExtInstrAttrs attrsArray32[] = {
    //                                                                              |   dec | rs2 | rs1 |fn3| rd  | dec   |
    EXT_INSTRUCTION(EXT_IT_EXCEPT24, "except24", RVANY, RVIP_RD_RS1_RS2, FMT_NONE, "|0000001|00000|00000|100|00000|0001011|")
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
// INSTRUCTION TRANSLATION
////////////////////////////////////////////////////////////////////////////////

/*
NOTES
-----
1. This extension adds a single instruction, except24, which triggers the
   custom exception. The instruction is implemented by function takeExcept24.
*/

//
// Trigger custom exception 24
//
static void takeExcept24(riscvP riscv) {
    riscv->cb.takeException(riscv, EXT_E_EXCEPT24, 0);
}

//
// Emit code implementing trigger of custom exception
//
static EXT_MORPH_FN(emitEXCEPT24) {

    vmimtArgProcessor();
    vmimtCall((vmiCallFn)takeExcept24);
}

//
// Dispatch table for instruction translation
//
const static riscvExtMorphAttr dispatchTable[] = {
    [EXT_IT_EXCEPT24] = {morph:emitEXCEPT24},
};

//
// Instruction translation
//
static VMIOS_MORPH_FN(addExceptionsMorph) {

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
static VMIOS_DISASSEMBLE_FN(addExceptionsDisassemble) {

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
// TRAP NOTIFIER
////////////////////////////////////////////////////////////////////////////////

/*
NOTES
-----
1. This trap notifier is called whenever a trap occurs and gives the extension
   the opportunity to update state dependent on the trap. In this case, the
   notifier simple reports the trap without updating state.
*/

//
// Perform actions when an trap is taken
//
static RISCV_TRAP_NOTIFIER_FN(takeTrap) {

//  vmiosObjectP object = clientData;
    Uns64        pc     = getPC(riscv);
    Uns32        code   = RD_CSR_FIELD(riscv, mcause, ExceptionCode);

    if(code==EXT_E_EXCEPT24) {
        vmiMessage("I", CPU_PREFIX "_TRAP",
            SRCREF_FMT "TRAP:%u MODE:%u INTERRUPT:%u",
            SRCREF_ARGS(riscv, pc),
            code,
            mode,
            RD_CSR_FIELD(riscv, mcause, Interrupt)
        );
    }
}


////////////////////////////////////////////////////////////////////////////////
// EXCEPTION DEFINITIONS
////////////////////////////////////////////////////////////////////////////////

/*
NOTES
-----
1. This section describes the custom extension (wso that it is reported in
   documentation and can be used in other tools).
*/

//
// Fill one member of exceptions
//
#define EXT_EXCEPTION(_NAME, _DESC) { \
    name:#_NAME, code:EXT_E_##_NAME, description:_DESC,    \
}

//
// Table of exception descriptions
//
static const vmiExceptionInfo exceptions[] = {

    ////////////////////////////////////////////////////////////////////
    // EXCEPTIONS
    ////////////////////////////////////////////////////////////////////

    EXT_EXCEPTION (EXCEPT24, "Custom Exception 24"),

    ////////////////////////////////////////////////////////////////////
    // TERMINATOR
    ////////////////////////////////////////////////////////////////////

    {0}
};

//
// Return the first exception implemented by the derived model
//
static RISCV_FIRST_EXCEPTION_FN(firstException) {
    return exceptions;
}


////////////////////////////////////////////////////////////////////////////////
// EXTENSION CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

/*
NOTES
-----
1. For use with this extension infrastructure, three things must be done in the
   constructor:
   1.1. The clientData pointer in the extCB interface object must be set to
        the vmiosObject;
   1.2. The firstException field in the extCB interface object must be set to
        the table of exceptions implemented by this extension;
   1.3. The trapNotifier field in the extCB interface object can optionally be
        set to a notifier called whenever an exception occurs;
   1.4. The extension interface must be registered with the base model using
        the registerExtCB interface function;
   Typically the constructor will also save a reference to the current
   processor and perform other initialisation, as shown below.
*/

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(addExceptionsConstructor) {

    riscvP riscv  = (riscvP)processor;

    object->riscv = riscv;

    // prepare client data
    object->extCB.clientData = object;

    // install custom exceptions
    object->extCB.firstException = firstException;

    // install notifier when trap is taken
    object->extCB.trapNotifier = takeTrap;

    // register extension with base model using unique ID
    riscv->cb.registerExtCB(riscv, &object->extCB, EXTID_ADDEXCEPT);
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

    .constructorCB = addExceptionsConstructor,  // object constructor

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB       = addExceptionsMorph,        // instruction morph callback
    .disCB         = addExceptionsDisassemble,  // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts    = {{0}}
};


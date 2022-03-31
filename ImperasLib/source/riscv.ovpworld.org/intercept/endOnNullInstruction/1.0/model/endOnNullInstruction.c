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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

// VMI area includes
#include "vmi/vmiDecode.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiVersion.h"

#define PREFIX "END_NULL_INSTR"

#define UNUSED __attribute__((unused))

typedef struct vmiosObjectS {
} vmiosObject;

//
// Check for an opcode of 0x00000000 which indicates end of test
//
static Bool isEndtestInstr(vmiProcessorP processor, Addr thisPC) {

    Uns64 instr = 0;
    Uns32 bytes = vmicxtFetch(processor, thisPC, &instr);

    return bytes && (instr==0x00000000);
}

//
// Disassembler callback disassembling exchange instructions
//
static VMIOS_DISASSEMBLE_FN(riscvDisass) {

    if(isEndtestInstr(processor, thisPC)) {

        static char buffer[256];
        sprintf(buffer, "ENDTEST");

        return buffer;

    } else {

        // another instruction
        return 0;
    }
}

//
// Value passed in a0
//
static VMIOS_INTERCEPT_FN(riscvENDTEST) {

    // end the simulation
    vmirtStop();
}

static VMIOS_MORPH_FN(riscvMorph) {
    if(isEndtestInstr(processor, thisPC)) {
        *opaque = True;
        return riscvENDTEST;
    }
    return 0;
}

static
VMIOS_CONSTRUCTOR_FN(constructor)
{
}

static
VMIOS_DESTRUCTOR_FN(destructor)
{
}


////////////////////////////////////////////////////////////////////////////////
// INTERCEPT ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString  = VMI_VERSION,                // version string (THIS MUST BE FIRST)
    .modelType      = VMI_INTERCEPT_LIBRARY,      // type
    .packageName    = "endOnNullInstruction",     // description
    .objectSize     = sizeof(vmiosObject),        // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {
        .vendor  = "riscv.ovpworld.org",
        .library = "intercept",
        .name    = "endOnNullInstruction",
        .version = "1.0"
    },

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB  = constructor,                // object constructor
    .destructorCB   = destructor,                 // object destructor

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB        = riscvMorph,                 // morph callback
    .disCB          = riscvDisass,                // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts = {
        // -------------------   ----------- ------ -----------------
        // Name                  Address     Opaque Callback
        // -------------------   ----------- ------ -----------------
        {0}
    }
    ,
};

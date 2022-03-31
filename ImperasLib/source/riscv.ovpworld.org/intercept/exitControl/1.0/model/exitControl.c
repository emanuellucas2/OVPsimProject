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
#include <string.h>

// VMI area includes
#include "vmi/vmiDecode.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"

#define PREFIX "EXC"

// Possible result registers used for checking test pass/fail
#define GP_REG_NUMBER  3
#define A0_REG_NUMBER 10
#define T3_REG_NUMBER 28

typedef struct vmiosObjectS {
    Uns64 address;            // address if executed to stop on
    Bool  addressValid;       // set when address is valid

    vmiRegInfoCP     gp, a0, t3;    // VMI register information, extracted at start

    Uns32 ecallResultReg;       // Index of the register holding the result on ecall, for tests
    Bool  checkResultReg;       // Set when result register checking enabled
    Bool  stopTerminate;        // Set to stop execution on function terminate()
    Bool  stopWriteToHost;      // Set to stop execution on write_to_host()

    Uns64 opcode;               // opcode to test
    Bool  stopOnOpcode;         // when opcode contains a valid opcode test

    Bool passed;                // flag holding exit status for the test

} vmiosObject;

// Define the attributes value structure
typedef struct paramValuesS {

    VMI_STRING_PARAM(symbol);
    VMI_UNS64_PARAM(address);

    VMI_BOOL_PARAM(onWriteToHost);
    VMI_BOOL_PARAM(onTerminate);
    VMI_UNS32_PARAM(onOpcode);
    VMI_UNS32_PARAM(ecallResultReg);

} paramValues, *paramValuesP;

static vmiParameter formals[] = {
    VMI_STRING_PARAM_SPEC(paramValues, symbol,      0,                "symbol on which to exit simulation"),
    VMI_UNS64_PARAM_SPEC(paramValues,  address,     0, 0, VMI_MAXU64, "address on which to exit simulation"),

    VMI_BOOL_PARAM_SPEC(paramValues,   onWriteToHost, 0,                "if function write_tohost() is executed exit simulation"),
    VMI_BOOL_PARAM_SPEC(paramValues,   onTerminate,   0,                "if function terminate() is executed exit simulation"),
    VMI_UNS64_PARAM_SPEC(paramValues,  onOpcode,      0, 0, VMI_MAXU64, "if opcode is executed exit simulation"),
    VMI_UNS32_PARAM_SPEC(paramValues,  ecallResultReg,    0, 0, 31,   "Result Register, read on ecall, for RISCV.org Conformance Test reporting. 3=GP, 10=A0 or 28=T3"),

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
    return prev->name ? prev : 0;
}

//
// Return size of parameter structure
//
static VMIOS_PARAM_TABLE_SIZE_FN(getParamTableSize) {
    return sizeof(paramValues);
}

static VMIOS_INTERCEPT_FN(stopSimulation) {
    vmiMessage("I", PREFIX "_FS", "%s: Stopping at 0x" FMT_Ax, context, thisPC);
    vmirtFinish(0);
}


static void exit_status (Bool passed) {
    if (passed) {
        vmiPrintf("Test PASSED\n");
    } else {
        vmiPrintf("Test FAILED\n");
    }
    vmirtFinish(1);
}

//
// Function intercepts to determine end of simulation
//
static VMIOS_INTERCEPT_FN(write_tohostCB) {
    vmiMessage("I", PREFIX "_FW", "Intercept 'write_tohost'.");
    if(object->checkResultReg){
        exit_status(object->passed);
    }
    if(object->stopWriteToHost){
        vmirtFinish(1);
    }
}

static VMIOS_INTERCEPT_FN(terminateCB) {
    vmiMessage("I", PREFIX "_FT", "Intercept 'terminate'.");
    if(object->checkResultReg) {
        exit_status(object->passed);
    }
    if(object->stopTerminate){
        vmirtFinish(1);
    }
}

//
// Check args and print PASSED if OK
//
static VMIOS_INTERCEPT_FN(riscvECALL) {
    Uns64 rr = 0;   // result register content

    switch(object->ecallResultReg) {
    case GP_REG_NUMBER:
        vmiosRegRead(processor, object->gp, &rr);
        break;
    case A0_REG_NUMBER:
        vmiosRegRead(processor, object->a0, &rr);
        break;
    case T3_REG_NUMBER:
        vmiosRegRead(processor, object->t3, &rr);
        break;
    }

    rr = (Uns32)rr;

    if (rr == 0x1) {
        object->passed = True;
    } else {
        object->passed = False;
    }
}

static VMIOS_MORPH_FN(morphTime) {

    if (object->addressValid && (thisPC == object->address)) {
        *context  = "address match";
        *opaque   = False;
        *userData = 0L;
        return stopSimulation ;
    }

    if(object->checkResultReg) {
        const char *disass = vmirtDisassemble(processor, thisPC, DSA_UNCOOKED);

        if (!strncmp(disass, "ecall", strlen("ecall"))) {
            *opaque = False;
            return riscvECALL;
        }
    }

    if(object->stopOnOpcode) {

        Uns64 instruction = 0;
        Uns32 bytes       = vmicxtFetch(processor, thisPC, &instruction);

        if(bytes && (instruction == object->opcode)) {
            *context  = "opcode match";
            *opaque   = False;
            *userData = 0L;
            return stopSimulation ;
        }
    }

    return 0;
}

//
// Get RISC-V register using primary or alternate name
//
static vmiRegInfoCP getAltReg(
    vmiProcessorP processor,
    const char   *name1,
    const char   *name2
) {
    vmiRegInfoCP reg = vmirtGetRegByName(processor, name1);

    if(!reg) {
        reg = vmirtGetRegByName(processor, name2);
    }

    if(!reg) {
        vmiMessage("F", PREFIX, "Unable to find register %s/%s", name1, name2);
    }

    return reg;
}

static VMIOS_CONSTRUCTOR_FN(constructor)
{
    paramValuesP params = parameterValues;

    // Get processor register information
    object->gp    = getAltReg(processor, "gp", "x3");
    object->a0    = getAltReg(processor, "a0", "x10");
    object->t3    = getAltReg(processor, "t3", "x28");

    // Check for symbol or address to exit on
    if (params->symbol &&  params->address__set) {
        // Specify only one
        vmiMessage("E", PREFIX "_NV", "Please specify one of symbol or address");

    } else if (params->symbol) {
        // check for symbol to exit on

        Addr symbolAddress;
        // Lookup symbol address and get domain it is found in
        memDomainP symbolDomain = vmirtAddressLookup(processor, params->symbol, &symbolAddress);

        if (symbolDomain) {
            vmiMessage("I", PREFIX "_SYM", "Program will stop at symbol '%s' (0x" FMT_Ax ")", params->symbol, symbolAddress);
            object->address      = symbolAddress;
            object->addressValid = True;
        } else {
            // Failed to find the symbol in the loaded ELF
            vmiMessage("E", PREFIX "_SYMNF", "Cannot find symbol '%s'", params->symbol);
        }

    } else if (params->address__set) {
        // Check for address to exit on

        // Lookup code domain for processor
        memDomainP domain = vmirtGetProcessorExternalCodeDomain(processor);

        if (domain) {
            vmiMessage("I", PREFIX "_ADDR", "Program will stop at address 0x" FMT_Ax, params->address);
            object->address = params->address;
            object->addressValid = True;
        } else {
            // Failed to find the domain containing the address
            vmiMessage("E", PREFIX "_ADDRDF", "Cannot find code domain for address 0x" FMT_Ax, params->address);
        }
    }

    if(SETBIT(params->onTerminate))   object->stopTerminate   = True;
    if(SETBIT(params->onWriteToHost)) object->stopWriteToHost = True;

    if(SETBIT(params->onOpcode)) {
        object->stopOnOpcode = True;
        object->opcode = params->onOpcode;
    }

    if(SETBIT(params->ecallResultReg)) {
        object->checkResultReg = True;
        object->ecallResultReg = params->ecallResultReg;
        switch(object->ecallResultReg) {
            case GP_REG_NUMBER:
            case A0_REG_NUMBER:
            case T3_REG_NUMBER:
                break;
            default:
                vmiMessage("W", PREFIX "_EREG", "Ignored Result register %d. Use %d, %d or %d (default)",
                                    object->ecallResultReg,
                                    GP_REG_NUMBER, A0_REG_NUMBER, T3_REG_NUMBER);
                object->ecallResultReg = T3_REG_NUMBER;
                break;
        }
    }

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
    .packageName    = "exitControl",              // description
    .objectSize     = sizeof(vmiosObject),        // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {
        .vendor  = "riscv.ovpworld.org",
        .library = "intercept",
        .name    = "exitControl",
        .version = "1.0"
    },

    .morphCB        = morphTime,                  // morph callback
    .constructorCB  = constructor,                // object constructor


    ////////////////////////////////////////////////////////////////////////
    // PARAMETER CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    .paramSpecsCB     = getParamSpecs,          // iterate parameter declarations
    .paramValueSizeCB = getParamTableSize,      // get parameter table size

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts = {
        // -------------------   ----------- ------ -----------------
        // Name                  Address     Opaque Callback
        // -------------------   ----------- ------ -----------------
        { "write_tohost",        0,          False, write_tohostCB    },
        { "terminate",           0,          False, terminateCB       },
        {0}
    }
};

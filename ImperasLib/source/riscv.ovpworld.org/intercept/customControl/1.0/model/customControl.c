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

#define PREFIX "CUSTOM_CONTROL"

#define A0_REG_NUMBER 10

typedef struct vmiosObjectS {
    vmidDecodeTableP table;
    vmiRegInfoCP     a0;    // VMI register information, extracted at start

    struct {
        char *logfile;
        FILE *stream;
    } params;

} vmiosObject;

// Define the attributes value structure
typedef struct paramValuesS {
    VMI_STRING_PARAM(logfile);
    VMI_BOOL_PARAM(nouart);
    VMI_UNS32_PARAM(uartbase);
} paramValues, *paramValuesP;

static vmiParameter formals[] = {
    VMI_STRING_PARAM_SPEC(paramValues, logfile,  0, "Logfile for custom0 character stream"),
    VMI_BOOL_PARAM_SPEC(  paramValues, nouart,   0, "Remove UART from address range 0x10010000 to 0x1001000f"),
    VMI_UNS32_PARAM_SPEC( paramValues, uartbase, 0x10010000, 0, ((Uns32)(-1))-0x10, "Set the UART base address (default 0x10010000)"),
    VMI_END_PARAM
};

//
// This macro adds a decode table entry for a specific instruction class
//
#define DECODE_ENTRY(_PRIORITY, _NAME, _FMT) \
    vmidNewEntryFmtBin(     \
        table,              \
        #_NAME,             \
        RISCV_EIT_##_NAME,   \
        _FMT,               \
        _PRIORITY           \
    )

//
// Enhanced instruction type enumeration
//
typedef enum riscvEnhancedInstrTypeE {

    // custom instruction
    RISCV_EIT_CUSTOM0,

    // KEEP LAST: for sizing the array
    RISCV_EIT_LAST

} riscvEnhancedInstrType;

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

//
// Disassemble custom control instructions
//
static vmidDecodeTableP createDecodeTable(void) {

    vmidDecodeTableP table = vmidNewDecodeTable(32, RISCV_EIT_LAST);

    DECODE_ENTRY(0, CUSTOM0, "|00000000000001010010000000001011|");

    return table;
}

//
// Decode an extended instruction at the indicated address, or return
// RISCV_EIT_LAST if this is not an extended instruction
//
static riscvEnhancedInstrType getInstrType(
    vmiosObjectP  object,
    vmiProcessorP processor,
    Addr          thisPC
) {
    riscvEnhancedInstrType type  = RISCV_EIT_LAST;
    Uns64                  instr = 0;
    Uns32                  bytes = vmicxtFetch(processor, thisPC, &instr);

    if (bytes == 4) {
        type = vmidDecode(object->table, instr);
    }

    return type;
}

//
// Value passed in a0
//
static VMIOS_INTERCEPT_FN(riscvCUSTOM0) {

    Uns64 a0 = 0;
    vmiosRegRead(processor, object->a0, &a0);

    if(a0==0) {
        vmirtExit(processor);
    } else {
        vmiPrintf("%c", (char)a0);
        if (object->params.logfile) {
            fprintf(object->params.stream, "%c", (char)a0);
        }
    }
}

static VMIOS_MORPH_FN(riscvMorph) {

    riscvEnhancedInstrType type = getInstrType(object, processor, thisPC);

    if (type==RISCV_EIT_CUSTOM0) {
        *opaque = True;
        return riscvCUSTOM0;
    }

    return 0;
}

static VMI_MEM_WATCH_FN(test_putc) {
    char c = *(char *)value;
    vmiPrintf("%c", c);
}

static VMI_MEM_WATCH_FN(test_exit) {
    vmirtFinish(0);
}

static void uartHandler(vmiProcessorP processor, Uns32 base) {
    memDomainP domain = vmirtGetProcessorExternalDataDomain(processor);
    vmirtAddWriteCallback(
        domain,
        0,
        base,
        base + 0x0f,
        test_putc,
        0
    );
}

static void memHandler(vmiProcessorP processor) {

    Addr test_stdoutP;
    memDomainP domain1 = vmirtAddressLookup(processor, "_test_stdout", &test_stdoutP);
    if (domain1) {
        vmirtAddWriteCallback(
            domain1,
            0,
            test_stdoutP,
            test_stdoutP+1,
            test_putc,
            0
        );
    }

    Addr test_exitP;
    memDomainP domain2 = vmirtAddressLookup(processor, "_test_exit", &test_exitP);
    if (domain2) {
        vmirtAddFetchCallback(
            domain2,
            processor,
            test_exitP,
            test_exitP+1,
            test_exit,
            0
        );
    }
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
    object->a0    = getAltReg(processor, "a0", "x10");
    object->table = createDecodeTable();

    paramValuesP params      = parameterValues;
    object->params.logfile   = params->logfile;
    if (object->params.logfile) {
        object->params.stream = fopen(object->params.logfile, "w");
    }

    //
    // UART test_putc register at 0x10010000
    //
    if(SETBIT(params->nouart)){
        // disabled UART
        vmiMessage("I", PREFIX, "No UART 0x10010000 to 0x1001000f");
    } else {
        uartHandler(processor, params->uartbase);
    }

    //
    // Handle _test_stdout and _test_exit
    //
    memHandler(processor);
}

static VMIOS_DESTRUCTOR_FN(destructor) {
    if (object->params.logfile) {
        fclose(object->params.stream);
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
    .packageName    = "customControl",            // description
    .objectSize     = sizeof(vmiosObject),        // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {
        .vendor  = "riscv.ovpworld.org",
        .library = "intercept",
        .name    = "customControl",
        .version = "1.0"
    },

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB  = constructor,                // object constructor
    .destructorCB   = destructor,                 // object destructor

    ////////////////////////////////////////////////////////////////////////
    // PARAMETER CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    .paramSpecsCB     = getParamSpecs,          // iterate parameter declarations
    .paramValueSizeCB = getParamTableSize,      // get parameter table size


    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB        = riscvMorph,                 // morph callback

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts = {
        // -------------------   ----------- ------ -----------------
        // Name                  Address     Opaque Callback
        // -------------------   ----------- ------ -----------------
        {0}
    }
};

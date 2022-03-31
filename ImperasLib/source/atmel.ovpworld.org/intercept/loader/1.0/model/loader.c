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
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiVersion.h"

#define PREFIX "ATMEL_LOADER"

#define UNUSED __attribute__((unused))
typedef struct vmiosObjectS {
    vmiRegInfoCP arg0;
    FILE *kernelLog;
} vmiosObject;

/////////////////// Array of formal parameter specifications ///////////////////
///////////////////// Formal Parameter Variables structure /////////////////////

// Define the attributes value structure
typedef struct paramValuesS {

    VMI_STRING_PARAM(bootrom);

} paramValues, *paramValuesP;


//
// Define formals
//
static vmiParameter formals[] = {
    VMI_STRING_PARAM_SPEC(paramValues,bootrom, "boot.rom", "Override the default 'boot.rom' file for the boot rom"),
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

//
// Constructor, open boot.rom and load contents
//   addr        len         file        off(in file)
// { 0x01000000, 0x00400000, "boot.rom", 0x00300000 },
// { 0x01400000, 0x00400000, "boot.rom", 0x00000000 },
// { 0x04000000, 0x00400000, "boot.rom", 0x00000000 },
// Loaded ROM boot.rom to 0x01300000
// Loaded ROM boot.rom to 0x01400000
// Loaded ROM boot.rom to 0x04000000
static
VMIOS_CONSTRUCTOR_FN(constructor)
{
    Uns32 addr, len, off;
    char *mallocP;
    Uns32 readBytes;
    memDomainP domain = vmirtGetProcessorPhysicalDataDomain(processor);

    paramValuesP params = parameterValues;
    const char *bootRom="boot.rom";
    if(params->bootrom)
        bootRom=params->bootrom;
    
    FILE *bootLoader = fopen(bootRom, "rb");
    if (bootLoader) {
        vmiMessage("I", PREFIX, "Loading Contents from %s", bootRom);
        // load section 1 = 0x00400000 - 0x00300000 = 0x00100000 @ 0x01000000
        // size_t fread(void *ptr,                                         size_t size, size_t nmemb,                              FILE *stream);
        //        fread(state->mem.rom[bank] + (mem_banks[bank].off >> 2), 1,           mem_banks[bank].len - mem_banks[bank].off, f)
        // target size = len
        // Section 1

        addr=0x01000000; len=0x00400000; off=0x00300000;
        mallocP = (char *) calloc(1,len);
        readBytes = fread(mallocP, 1, len - off, bootLoader);
        vmiMessage("I", PREFIX, "Read %d bytes from %s, requested %d, written at 0x%08x", readBytes, bootRom, (len-off), (addr+off));
        vmirtWriteNByteDomain(domain, (Addr)(addr+off), mallocP, (Addr)readBytes, 0, False);
        free(mallocP);
        fclose(bootLoader);
        
        // Section 2
        bootLoader = fopen(bootRom, "rb");
        addr=0x01400000; len=0x00400000; off=0x00000000;
        mallocP = (char *) calloc(1,len);
        readBytes = fread(mallocP, 1, len - off, bootLoader);
        vmiMessage("I", PREFIX, "Read %d bytes from %s, requested %d, written at 0x%08x", readBytes, bootRom, (len-off), (addr+off));
        vmirtWriteNByteDomain(domain, (Addr)(addr+off), mallocP, (Addr)readBytes, 0, False);
        free(mallocP);
        fclose(bootLoader);
        
        // Section 3
        bootLoader = fopen(bootRom, "rb");
        addr=0x04000000; len=0x00400000; off=0x00000000;
        mallocP = (char *) calloc(1,len);
        readBytes = fread(mallocP, 1, len - off, bootLoader);
        vmiMessage("I", PREFIX, "Read %d bytes from %s, requested %d, written at 0x%08x", readBytes, bootRom, (len-off), (addr+off));
        vmirtWriteNByteDomain(domain, (Addr)(addr+off), mallocP, (Addr)readBytes, 0, False);
        free(mallocP);
        fclose(bootLoader);
        
    } else {
        vmiMessage("E", PREFIX, "No Boot rom file '%s' available", bootRom);
    }
    
    object->arg0 = vmiosGetRegDesc(processor, "r0");
}

static
VMIOS_DESTRUCTOR_FN(destructor)
{
    if (object->kernelLog) {
        fclose(object->kernelLog);
    }
}

//
// Intercept do_execve 
// looking for "/bin/sh halt"
//
static
VMIOS_INTERCEPT_FN(do_execveCB) {
    Uns32 arg0;
    memDomainP domain = vmirtGetProcessorDataDomain(processor);

    vmiosRegRead(processor, object->arg0, &arg0);
    const char *cmd = vmirtGetString(domain, arg0);
    if (strcmp(cmd, "/bin/halt") == 0) {
        vmirtFinish(0);
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
    .packageName    = "loader",                   // description
    .objectSize     = sizeof(vmiosObject),        // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {    
        .vendor  = "atmel.ovpworld.org",
        .library = "intercept",
        .name    = "loader",
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

    .morphCB        = 0,                          // morph callback
    .nextPCCB       = 0,                          // get next instruction address
    .disCB          = 0,                          // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts = {
        // -------------------   ----------- ------ -----------------
        // Name                  Address     Opaque Callback
        // -------------------   ----------- ------ -----------------
        {"do_execve",            0,          False, do_execveCB},
        {0}
    }
    ,
};

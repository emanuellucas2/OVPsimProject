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

// VMI area includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiVersion.h"

//
// Architecture is 32-bit by default
//
#ifndef MIPS_ARCH_BITS
    #define MIPS_ARCH_BITS 32
#endif

// Define architectural-width unsigned and signed types
#if MIPS_ARCH_BITS==32
    #define UnsArch Uns32
    #define IntArch Int32
    #define CPU_PREFIX "MIPS32/NEWLIB"
#endif
#if MIPS_ARCH_BITS==64
    #define UnsArch Uns64
    #define IntArch Int64
    #define CPU_PREFIX "MIPS64/NEWLIB"
#endif

// Message prefix

// Number of arguments passed in regs as defined by ABI
#define REG_ARG_NUM  3

// Number of file descriptors supported
#define FILE_DES_NUM 128

// Alternate name  that occurs in CodeSourcery Pro versions of libc
#define ALT_ERRNO_REF "_cslibc_global__errno"

////////////////////////////////////////////////////////////////////////////////
// TYPES
////////////////////////////////////////////////////////////////////////////////

//
// Define the attributes value structure
//
typedef struct paramValuesS {

    VMI_PTR_PARAM(userargv);
    VMI_PTR_PARAM(userenvp);

} paramValues, *paramValuesP;

typedef struct vmiosObjectS {

    // first three argument registers (standard ABI)
    vmiRegInfoCP args[REG_ARG_NUM];

    // return register (standard ABI)
    vmiRegInfoCP resultReg;

    // stack pointer register (standard ABI)
    vmiRegInfoCP argSP;
    char **argv, **envp;

    // Info for errno handling (set and used in newlibSemiHost.c.h)
    Addr         impurePtrAddr;
    memDomainP   impurePtrDomain;
    Addr         errnoAddr;
    memDomainP   errnoDomain;

    // file descriptor table (set and used in newlibSemiHost.c.h)
    Int32 fileDescriptors[FILE_DES_NUM];

} vmiosObject;

// mips32 and 64/newlib stat structure
typedef struct {      // mips32/mips64 offsets:
    Uns32   _u1;      //  0/0 :
    Uns32   mode;     //  4/4 : mode
    Uns32   _u2;      //  8/8 :
    Uns32   _u3;      // 12/12:
    UnsArch size;     // 16/16: size
    UnsArch atime;    // 20/24: atime
    UnsArch _u4;      // 24/32:
    UnsArch mtime;    // 28/40: mtime
    UnsArch _u5;      // 32/48:
    UnsArch ctime;    // 36/56: ctime
    UnsArch _u6;      // 40/64:
    UnsArch blksize;  // 44/72: blksize
    UnsArch blocks;   // 48/80: blocks
} newlibStat;

typedef newlibStat newlibStat64;

////////////////////////////////////////////////////////////////////////////////
// UTILITIES
////////////////////////////////////////////////////////////////////////////////

//
// Get the Constant pointer for the Stack Pointer
//
static vmiRegInfoCP getSPCP(
    vmiProcessorP processor,
    vmiosObjectP  object
) {
    return object->argSP;
}
//
// Get the Constant pointer for the register
//
static vmiRegInfoCP getArgCP(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Uns32         index
) {
    vmiRegInfoCP regCP = 0;

    if(index>=REG_ARG_NUM) {
        vmiMessage("P", CPU_PREFIX"_ANS",
            "No more than %u function arguments supported",
            REG_ARG_NUM
        );
        vmirtFinish(-1);

    } else {
        regCP = object->args[index];
    }
    return regCP;
}

//
// Read a function argument using the standard ABI
//
static void getArg(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Uns32         index,
    void         *result
) {
    if(index>=REG_ARG_NUM) {
        vmiMessage("P", CPU_PREFIX"_ANS",
            "No more than %u function arguments supported",
            REG_ARG_NUM
        );
        vmirtFinish(-1);
    } else {
        vmiRegInfoCP regCP = getArgCP(processor, object, index);
        vmiosRegRead(processor, regCP, result);
    }
}


////////////////////////////////////////////////////////////////////////////////
// Include code common to all newlib implementations
////////////////////////////////////////////////////////////////////////////////
#include "ovpworld.org/modelSupport/semihosting/1.0/model/newlib.c.h"

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR & DESTRUCTOR
////////////////////////////////////////////////////////////////////////////////

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(constructor) {

    paramValuesP params = parameterValues;

    // get parameters
    object->argv = params->userargv;
    object->envp = params->userenvp;

    // first three argument registers (p 32 ABI)
    object->args[0] = vmiosGetRegDesc(processor, "a0");
    object->args[1] = vmiosGetRegDesc(processor, "a1");
    object->args[2] = vmiosGetRegDesc(processor, "a2");

    // return register (p32 ABI)
    object->resultReg = vmiosGetRegDesc(processor, "a0");

    // Stack Pointer
    object->argSP = vmiosGetRegDesc(processor, "sp");

    // Sets up data common to all newlib implementations
    // Defined in newlibSemiHost.c.h
    setupNewlib(object, processor);
}

//
// Destructor
//
static VMIOS_DESTRUCTOR_FN(destructor) {
}


////////////////////////////////////////////////////////////////////////////////
// MIPS_SPECIFIC CALLBACKS
////////////////////////////////////////////////////////////////////////////////

//
// Intercept _mdi_getargs().
//
static VMIOS_INTERCEPT_FN(mdiGetArgsCB) {

    UnsArch zero = 0;
    int i;

    // set a0..a2 to 0
    for (i=0; i < 3; i++) {
        vmiosRegWrite(processor, object->args[i], &zero);
    }

    // write back result
    vmiosRegWrite(processor, object->resultReg, &zero);

}

//
// sim_get_mem_conf
//
static VMIOS_INTERCEPT_FN(getMemConfCB) {

    UnsArch infoAddr;
    memDomainP  domain = vmirtGetProcessorDataDomain(processor);
    memEndian   endian = vmirtGetProcessorDataEndian(processor);

    // The memory information consists of an array of 3 words:
    //   memInfoArr[0] = memory size  (we default to 512MB - the maximum size of KSEG0)
    //   memInfoArr[1] = i-cache size (we default to 0)
    //   memInfoArr[2] = d-cache size (we default to 0)
    // Ideally, values reflecting the configuration of the simulation
    // would be used.
    Uns32 memInfoArr[3] = {0x10000000, 0, 0};

    // obtain function arguments
    getArg(processor, object, 0, &infoAddr);

    // swap endianness if required
    if(endian != MEM_ENDIAN_NATIVE) {
        memInfoArr[0] = SWAP_4_BYTE(memInfoArr[0]);
        memInfoArr[1] = SWAP_4_BYTE(memInfoArr[1]);
        memInfoArr[2] = SWAP_4_BYTE(memInfoArr[2]);
    }

    vmirtWriteNByteDomain(
        domain, infoAddr, &memInfoArr, sizeof(memInfoArr), 0, MEM_AA_FALSE
    );
}

//
// Define formals
//
static vmiParameter formals[] = {
    VMI_PTR_PARAM_SPEC(paramValues, userargv, 0, "Pointer to argv structure"),
    VMI_PTR_PARAM_SPEC(paramValues, userenvp, 0, "Pointer to envp structure"),
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


////////////////////////////////////////////////////////////////////////////////
// INTERCEPT ATTRIBUTES
////////////////////////////////////////////////////////////////////////////////

vmiosAttr modelAttrs = {

    ////////////////////////////////////////////////////////////////////////
    // VERSION
    ////////////////////////////////////////////////////////////////////////

    .versionString  = VMI_VERSION,              // version string (THIS MUST BE FIRST)
    .modelType      = VMI_INTERCEPT_LIBRARY,    // type
    .packageName    = "Newlib",                 // description
    .objectSize     = sizeof(vmiosObject),      // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {    
        .vendor  = "mips.ovpworld.org",
        .library = "semihosting",
        .name    = "nanomipsNewlib",
        .version = "1.0"
    },

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB  = constructor,              // object constructor
    .destructorCB   = destructor,               // object destructor

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB        = 0,                        // morph callback
    .nextPCCB       = 0,                        // get next instruction address
    .disCB          = 0,                        // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // PARAMETER CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    .paramSpecsCB     = getParamSpecs,          // iterate parameter declarations
    .paramValueSizeCB = getParamTableSize,      // get parameter table size

     ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts = {
        // ----------------- ------- ------ -----------------
        // Name              Address Opaque Callback
        // ----------------- ------- ------ -----------------
        // MDI
        {  "_mdi_getargs",   0,      True,  mdiGetArgsCB     },
        {  "_mdi_exit",      0,      True,  exitCB,          },

        // Newlib
        {  "close",          0,      True,  closeCB          },
        {  "_exit",          0,      True,  exitCB           },
        {  "fstat",          0,      True,  fstatCB          },
        {  "gettimeofday",   0,      True,  gettimeofdayCB   },
        {  "kill",           0,      True,  killCB           },
        {  "lseek",          0,      True,  lseekCB          },
        {  "lstat",          0,      True,  lstatCB          },
        {  "open",           0,      True,  openCB           },
        {  "read",           0,      True,  readCB           },
        {  "stat",           0,      True,  statCB           },
        {  "time",           0,      True,  timeCB           },
        {  "times",          0,      True,  timesCB          },
        {  "unlink",         0,      True,  unlinkCB         },
        {  "write",          0,      True,  writeCB          },

        // MIPS specific
        {  "get_mem_info",   0,      True,  getMemConfCB     },

        //
        // Intercept main for argc, argv, env
        //
        { "main",              0,         False, mainStackInitCB },

        {  0                                                 },
    }
};


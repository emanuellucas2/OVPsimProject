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

// VMI area includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiVersion.h"

//
// Message prefix
//
#define CPU_PREFIX "V850_NEWLIB"

// Number of arguments passed in regs as defined by ABI
#define REG_ARG_NUM  3

// Number of file descriptors supported
#define FILE_DES_NUM 128

// Symbols have leading underscore
#define LEAD_US "_"

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

//
// v850/newlib stat structure
//
typedef struct {
    Uns32 _u1;      //  0:
    Uns32 mode;     //  4: mode
    Uns32 _u2;      //  8:
    Uns32 _u3;      // 12:
    Uns32 size;     // 16: size
    Uns32 atime;    // 20: atime
    Uns32 _u4;      // 24:
    Uns32 mtime;    // 28: mtime
    Uns32 _u5;      // 32:
    Uns32 ctime;    // 36: ctime
    Uns32 _u6;      // 40:
    Uns32 blksize;  // 44: blksize
    Uns32 blocks;   // 48: blocks
} newlibStat;

typedef newlibStat newlibStat64;

////////////////////////////////////////////////////////////////////////////////
// UTILITIES REQUIRED BY newlibSemiHost.c.h
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

    // first three argument registers (standard ABI)
    object->args[0] = vmiosGetRegDesc(processor, "R6");
    object->args[1] = vmiosGetRegDesc(processor, "R7");
    object->args[2] = vmiosGetRegDesc(processor, "R8");

    // return register (standard ABI)
    object->resultReg = vmiosGetRegDesc(processor, "R10");

    // Stack Pointer
    object->argSP = vmiosGetRegDesc(processor, "R3");

    // Sets up data common to all newlib implementations
    // Defined in newlibSemiHost.c.h
    setupNewlib(object, processor);
}

//
// Destructor
//
static VMIOS_DESTRUCTOR_FN(destructor) {
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
        .vendor  = "renesas.ovpworld.org",
        .library = "semihosting",
        .name    = "v850Newlib",
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
        //
        // newlib entries
        //
        { "__exit_halt",      0,      True,  exitCB         },
        { "__exit",           0,      True,  exitCB         },
        { "__open",           0,      True,  openCB         },
        { "__close",          0,      True,  closeCB        },
        { "__read",           0,      True,  readCB         },
        { "__write",          0,      True,  writeCB        },
        { "__lseek",          0,      True,  lseekCB        },
        { "__fstat",          0,      True,  fstatCB        },
        { "__lstat",          0,      True,  lstatCB        },
        { "__stat",           0,      True,  statCB         },
        { "__kill",           0,      True,  killCB         },
        { "_gettimeofday",    0,      True,  gettimeofdayCB },
        { "_times",           0,      True,  timesCB        },
        { "_unlink",          0,      True,  unlinkCB       },
        { "_time",            0,      True,  timeCB         },

        //
        // greenhills (additional) entries
        //
        { "_open",            0,      True,  openCB         },
        { "_close",           0,      True,  closeCB        },
        { "_read",            0,      True,  readCB         },
        { "_write",           0,      True,  writeCB        },
        { "_lseek",           0,      True,  lseekCB        },
        { "_fstat",           0,      True,  fstatCB        },
        { "_lstat",           0,      True,  lstatCB        },
        { "_stat",            0,      True,  statCB         },
        { "_kill",            0,      True,  killCB         },

        //
        // Intercept main for argc, argv, env
        //
        { "_main",            0,     False,  mainStackInitCB},

        { 0 },
    }
};


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


// Message prefix
#define CPU_PREFIX "ARC_NEWLIB"

// Number of arguments passed in regs as defined by ABI
#define REG_ARG_NUM  4

// Number of file descriptors supported
#define FILE_DES_NUM 128

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
// arc/newlib stat structure
//
typedef struct {
    Uns32 _u1;      //  0:
    Uns32 _u2;      //  4:
    Uns16 mode;     //  8: mode
    Uns16 _u3;      // 10:
    Uns32 _u4;      // 12:
    Uns32 _u5;      // 16:
    Uns32 size;     // 20: size
    Uns32 blksize;  // 24: blksize
    Uns32 blocks;   // 28: blocks
    Uns64 atime;    // 32: atime
    Uns64 mtime;    // 40: mtime
    Uns64 ctime;    // 48: ctime
} newlibStat;

typedef newlibStat newlibStat64;

//
// GNU ARC toolchain defines struct timeval tv_sec member as 'long long' (64 bits)
// so must override the default defined in newlib.c.h
// (Must be packed or struct gets padded to 16 bytes on 64 bit host
//  which leads to an overwrite in the simulated stack)
//
#define NEWLIB_TIMEVAL_DEFINED 1
typedef struct __attribute__ ((__packed__)) newlibTimeval {
    Uns64 tv_sec;     /* seconds */
    Uns32 tv_usec;    /* microseconds */
} newlibTimeval;

//
// GNU ARC toolchain uses non-standard values for these
//
#define TARGET_O_CREAT  0x0040
#define TARGET_O_APPEND 0x0400
#define TARGET_O_TRUNC  0x0200

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
    Uns32 i;
    for (i = 0; i < REG_ARG_NUM; i++) {
        char buf[8];
        snprintf(buf, sizeof(buf), "R%d", i);
        object->args[i] = vmiosGetRegDesc(processor, buf);

    }

    // return register (standard ABI)
    object->resultReg = vmiosGetRegDesc(processor, "R0");

    // Stack Pointer
    object->argSP = vmiosGetRegDesc(processor, "SP");

    // Sets up data common to all newlib implementations
    // Defined in newlibSemiHost.c.h
    setupNewlib(object, processor);
}

//
// Destructor
//
static VMIOS_DESTRUCTOR_FN(destructor) {
}

static vmiParameter formals[] = {
    VMI_PTR_PARAM_SPEC(paramValues, userargv,   0, "Pointer to argv structure" ),
    VMI_PTR_PARAM_SPEC(paramValues, userenvp,   0, "Pointer to envp structure" ),
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
        .vendor  = "arc.ovpworld.org",
        .library = "semihosting",
        .name    = "arcNewlib",
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
        { "_close",          0,      True,  closeCB        },
        { "_close_r",        0,      True,  close_rCB      },
        { "_exit_halt",      0,      True,  exitCB         },
        { "_exit",           0,      True,  exitCB         },
        { "_exit_r",         0,      True,  exitCB         },
        { "_fstat",          0,      True,  fstatCB        },
        { "_fstat_r",        0,      True,  fstat_rCB      },
        { "gettimeofday",    0,      True,  gettimeofdayCB },
        { "gettimeofday_r",  0,      True,  gettimeofday_rCB },
        { "_kill",           0,      True,  killCB         },
        { "_kill_r",         0,      True,  kill_rCB       },
        { "_lseek",          0,      True,  lseekCB        },
        { "_lseek_r",        0,      True,  lseek_rCB      },
        { "_lstat",          0,      True,  lstatCB        },
        { "_lstat_r",        0,      True,  lstat_rCB       },
        { "_open",           0,      True,  openCB         },
        { "_open_r",         0,      True,  open_rCB       },
        { "_read",           0,      True,  readCB         },
        { "_read_r",         0,      True,  read_rCB       },
        { "_stat",           0,      True,  statCB         },
        { "_stat_r",         0,      True,  stat_rCB       },
        { "time",            0,      True,  timeCB         },   // Not - no time_r is defined in reent.h
        { "times",           0,      True,  timesCB        },
        { "times_r",         0,      True,  times_rCB        },
        { "_unlink",         0,      True,  unlinkCB       },
        { "_unlink_r",       0,      True,  unlink_rCB     },
        { "_write",          0,      True,  writeCB        },
        { "_write_r",        0,      True,  write_rCB      },

        //
        // Intercept main for argc, argv, env
        //
        { "main",                       0,      False,  mainStackInitCB },

        { 0 },
    }
};


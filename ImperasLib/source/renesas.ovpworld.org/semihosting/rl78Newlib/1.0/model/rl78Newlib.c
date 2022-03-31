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
#define CPU_PREFIX "RL78_NEWLIB"

// Number of arguments passed in regs as defined by ABI
#define REG_ARG_NUM  0

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
//    vmiRegInfoCP args[REG_ARG_NUM];

    // return register (standard ABI)
    vmiRegInfoCP    reg_PSW;
    vmiRegInfoCP    reg_X[4];
    vmiRegInfoCP    reg_A[4];

    // stack pointer register (standard ABI)
    vmiRegInfoCP    reg_sp;
    Uns16            val_sp;

    memDomainP        domain;            // platform address space (guest)

    char **argv, **envp;

    // Info for errno handling (set and used in newlibSemiHost.c.h)
    Addr            impurePtrAddr;
    memDomainP        impurePtrDomain;
    Addr            errnoAddr;
    memDomainP        errnoDomain;

    // file descriptor table (set and used in newlibSemiHost.c.h)
    Int32            fileDescriptors[FILE_DES_NUM];

} vmiosObject;

//
// rl78/newlib stat structure
//
//typedef short __dev_t;
//typedef unsigned short ino_t;
//typedef unsigned int mode_t __attribute__ ((__mode__ (__SI__)));
//typedef unsigned short nlink_t;
//typedef unsigned short __uid_t;
//typedef unsigned short __gid_t;
//typedef long _off_t;
//typedef long time_t;
//
//# 25 "c:\\program files\\kpit\\gnurl78v15.01-elf\\rl78-elf\\rl78-elf\\include\\sys\\stat.h" 3
//
typedef struct {
    Uns16    st_dev;            // 0    //  dev_t st_dev;
    Uns16    st_ino;            // 2    //  ino_t st_ino;
    Uns16    mode;            // 4    //  mode_t st_mode;
    Uns16    st_nlink;        // 6    //  nlink_t st_nlink;
    Uns16    st_uid;            // 8    //  uid_t st_uid;
    Uns16    st_gid;            // 10    //  gid_t st_gid;
    Uns16    st_rdev;        // 12    //  dev_t st_rdev;
    Uns32    size;            // 16    //  off_t st_size;
    Uns32    atime;            // 20    //  time_t st_atime;
    Uns32    st_spare1;        // 24    //  long st_spare1;
    Uns32    mtime;            // 28    //  time_t st_mtime;
    Uns32    st_spare2;        // 32    //  long st_spare2;
    Uns32    ctime;            // 36    //  time_t st_ctime;
    Uns32    st_spare3;        // 40    //  long st_spare3;
    Uns32    blksize;        // 44    //  long st_blksize;
    Uns32    blocks;            // 48    //  long st_blocks;
    Uns32    st_spare4[2];    // 52    //  long st_spare4[2];
} newlibStat;

typedef newlibStat newlibStat64;

////////////////////////////////////////////////////////////////////////////////
// UTILITIES REQUIRED BY newlibSemiHost.c.h
////////////////////////////////////////////////////////////////////////////////


#define ARG_SIZE    2

//
// Read a function argument using the standard ABI
//
static void getArg(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Uns32         index,
    void         *result
) {
    vmirtRegRead (processor, object->reg_sp, &object->val_sp);
    //
    // This callback should create code to push function parameters before making
    // an Imperas intercepted call. The function parameters are presented using the
    // standard processor procedure call ABI. The function parameters are described
    // by the passed format string. This string can contain a sequence of any of the
    // following:
    //
    //      '4':    push Uns32 function argument using vmimtArgReg(32, ...)
    //      '8':    push Uns64 function argument using vmimtArgReg(64, ...)
    //      'a':    push address function argument using vmimtArgRegSimAddress(...)
    //      'd':    push Flt64 function argument using vmimtArgFlt64(...)
    //
    // For

    memDomainP domain = vmirtGetProcessorDataDomain(processor);

    Uns32 addr = 0xF0000 + object->val_sp + 4 + (ARG_SIZE * index);

    vmirtReadNByteDomain(        //memMapped vmirtReadNByteDomain(
        domain,                    //    memDomainP     domain,
        addr,                    //    Addr           simAddress,
        result,                    //    void          *buffer,
        ARG_SIZE,                //    Addr           size,
        0,                        //    memRegionPP    cachedRegion,
        MEM_AA_TRUE);            //    memAccessAttrs attrs
}


////////////////////////////////////////////////////////////////////////////////
// Include code common to all newlib implementations
////////////////////////////////////////////////////////////////////////////////
//#include "ovpworld.org/modelSupport/semihosting/1.0/model/newlib.c.h"
#include "newlib.c.h"

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
    object->reg_sp = vmiosGetRegDesc(processor, "SP");        // read register value via debugger I/F.

    object->reg_PSW  = vmiosGetRegDesc(processor, "PSW");
    object->reg_X[0] = vmiosGetRegDesc(processor, "X[RB0]");
    object->reg_X[1] = vmiosGetRegDesc(processor, "X[RB1]");
    object->reg_X[2] = vmiosGetRegDesc(processor, "X[RB2]");
    object->reg_X[3] = vmiosGetRegDesc(processor, "X[RB3]");
    object->reg_A[0] = vmiosGetRegDesc(processor, "A[RB0]");
    object->reg_A[1] = vmiosGetRegDesc(processor, "A[RB1]");
    object->reg_A[2] = vmiosGetRegDesc(processor, "A[RB2]");
    object->reg_A[3] = vmiosGetRegDesc(processor, "A[RB3]");

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

    .versionString  = VMI_VERSION,                // version string (THIS MUST BE FIRST)
    .modelType      = VMI_INTERCEPT_LIBRARY,    // type
    .packageName    = "Newlib",                    // description
    .objectSize     = sizeof(vmiosObject),        // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {
        .vendor  = "renesas.ovpworld.org",
        .library = "semihosting",
        .name    = "rl78Newlib",
        .version = "1.0"
    },

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB  = constructor,                // object constructor
    .destructorCB   = destructor,                // object destructor

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB        = 0,                        // morph callback
    .nextPCCB       = 0,                        // get next instruction address
    .disCB          = 0,                        // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // PARAMETER CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    .paramSpecsCB     = getParamSpecs,            // iterate parameter declarations
    .paramValueSizeCB = getParamTableSize,        // get parameter table size

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
        { "_write"          ,  0,  True ,  writeCB        },        // newlib-2.0.0/libgloss/rl78/write.c
        { "__exit"          ,  0,  True ,  exitCB            },        // newlib-2.0.0/libgloss/rl78/exit.S
        { "__open"          ,  0,  True ,  openCB            },        // newlib-2.0.0/libgloss/rl78/open.S
        { "__close"          ,  0,  True ,  closeCB        },        // newlib-2.0.0/libgloss/rl78/close.S
        { "__read"          ,  0,  True ,  readCB            },        // newlib-2.0.0/libgloss/rl78/read.S
        { "__lseek"          ,  0,  True ,  lseekCB        },        // newlib-2.0.0/libgloss/rl78/lseek.S
        { "__fstat"          ,  0,  True ,  fstatCB        },        // newlib-2.0.0/libgloss/rl78/fstat.S
        { "__stat"          ,  0,  True ,  statCB            },        // newlib-2.0.0/libgloss/rl78/stat.S
        { "__kill"          ,  0,  True ,  killCB            },        // newlib-2.0.0/libgloss/rl78/kill.S
        { "__gettimeofday",  0,  True ,  gettimeofdayCB    },        // newlib-2.0.0/libgloss/rl78/gettimeofday.S
        { "__times"          ,  0,  True ,  timesCB        },        // newlib-2.0.0/libgloss/rl78/times.S
        { "__unlink"      ,  0,  True ,  unlinkCB        },        // newlib-2.0.0/libgloss/rl78/unlink.S
        { "__time"          ,  0,  True ,  timeCB            },        // newlib-2.0.0/libgloss/rl78/time.S

        { "_exit"         ,  0,  True ,  exitCB         },      // use with CC-LR toolchain C Library

        //
        // Intercept main for argc, argv, env
        //
//        { "_main"          ,  0,     False,  mainStackInitCB},

        { 0 },
    }
};


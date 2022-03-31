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
// Architecture is 32-bit by default
//
#ifndef RISCV_ARCH_BITS
    #error undefined  RISCV_ARCH_BITS
#endif

// Define architectural-width unsigned and signed types
#if RISCV_ARCH_BITS==32
    #define UnsArch Uns32
    #define IntArch Int32
    #define FMT_ARCH_FMT_D     "%d"
    #define FMT_ARCH_FMT_X     "%x"
    #define CPU_PREFIX "RISCV32/NEWLIB"
#endif
#if RISCV_ARCH_BITS==64
    #define UnsArch Uns64
    #define IntArch Int64
    #define FMT_ARCH_FMT_D     FMT_64d
    #define FMT_ARCH_FMT_X     FMT_64x
    #define CPU_PREFIX "RISCV64/NEWLIB"
#endif

//
// This defines the number of file descriptors for this processor
//
#define FILE_DES_NUM 128

#define REG_ARG_NUM  5

//
// Implement optional exit return code checking
// (enabled by reportExitErrors parameter)
//
#define REPORT_EXIT_ERRORS

////////////////////////////////////////////////////////////////////////////////
// TYPES
////////////////////////////////////////////////////////////////////////////////

//
// Define the attributes value structure
//
typedef struct paramValuesS {

    VMI_PTR_PARAM(userargv);
    VMI_PTR_PARAM(userenvp);
    VMI_BOOL_PARAM(reportExitErrors);
    VMI_UNS64_PARAM(initsp);

} paramValues, *paramValuesP;

typedef struct vmiosObjectS {

    // first three argument registers (standard ABI)
    vmiRegInfoCP args[REG_ARG_NUM];

    // return register (standard ABI)
    vmiRegInfoCP resultReg;

    // stack pointer register (standard ABI)
    vmiRegInfoCP argSP;
    char **argv, **envp;

    // Report non-zero exit as simulator error when set
    Bool reportExitErrors;

    // Info for errno handling (set and used in newlibSemiHost.c.h)
    Addr         impurePtrAddr;
    memDomainP   impurePtrDomain;
    Addr         errnoAddr;
    memDomainP   errnoDomain;

    // pointer Top_of Heap
    UnsArch      heap;

    // file descriptor table (set and used in newlibSemiHost.c.h)
    Int32 fileDescriptors[FILE_DES_NUM];

} vmiosObject;

//
// riscv32/newlib stat structure
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

typedef struct {
    Uns64 size;
    Uns32 mode;
    Uns32 blksize;
    Uns32 blocks;
    Uns32 atime;
    Uns32 mtime;
    Uns32 ctime;
} newlibStat64;

//typedef struct {
//    Uns16 dev;
//    Uns16 ino;
//    Uns32 mode;
//    Uns16 nlink;
//    Uns16 uid;
//    Uns16 gid;
//    Uns16 rdev;
//    Uns64 size;
//    Uns64 atime;
//    Uns64 spare1;
//    Uns64 mtime;
//    Uns64 spare2;
//    Uns64 ctime;
//    Uns64 spare3;
//    Uns64 blksize;
//    Uns64 blocks;
//    Uns64 spare4[2];
//} newlibStat64;

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

//
// sbrk()
//
static VMIOS_INTERCEPT_FN(sbrkCB) {
    // size to increment passed as first argument
    UnsArch increment;
    getArg(processor, object, 0, &increment);

    Addr heap = object->heap;

    if (heap==0) {

        // First call - lookup symbol
        // Standard GNU toolchain linker scripts use "_end"
        // SiFive freedom-e-sdk bsp linker scripts use "metal_segment_heap_target_start"
        if ((vmirtAddressLookup(processor, "_end", &heap) == NULL) &&
            (vmirtAddressLookup(processor, "metal_segment_heap_target_start", &heap) == NULL)
        ) {
            vmiMessage("P", CPU_PREFIX"_MHS",
                "Missing _end or other symbol defining start of heap. sbrk() not supported"
            );
            vmirtFinish(-1);
        }

        // Round up to 4k page size
        heap += 0x1000 - 1;
        heap &= ~(0x1000 - 1);

        // Initial base of heap
        object->heap = heap;
    }

    if (STRACE) vmiPrintf("(STRACE) %x sbrk(%d)\n", (Uns32)heap, (Uns32)increment);

    // Move heap pointer past newly allocated memory
    object->heap += increment;

    // return pointer to beginning of newly allocated memory
    setResult(processor, object, heap);

}

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR & DESTRUCTOR
////////////////////////////////////////////////////////////////////////////////

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
        vmiMessage("F", CPU_PREFIX, "Unable to find register %s/%s", name1, name2);
    }

    return reg;
}

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(constructor) {

    paramValuesP params = parameterValues;

    // get parameters
    object->argv             = params->userargv;
    object->envp             = params->userenvp;
    object->reportExitErrors = params->reportExitErrors;

    // first three argument registers (standard ABI)
    object->args[0] = getAltReg(processor, "a0", "x10");
    object->args[1] = getAltReg(processor, "a1", "x11");
    object->args[2] = getAltReg(processor, "a2", "x12");
    object->args[3] = getAltReg(processor, "a3", "x13");
    object->args[4] = getAltReg(processor, "a4", "x14");

    // return register (standard ABI)
    object->resultReg = object->args[0];

    // stack pointer
    object->argSP = getAltReg(processor, "sp", "x2");

    if (params->SETBIT(initsp)) {
        // set initial value of stack pointer to provided address
        vmiosRegWrite(processor, object->argSP, &params->initsp);

    } else if(RISCV_ARCH_BITS==64) {
        // adjust initial value of stack pointer to valid physical memory address

        memDomainP domain  = vmirtGetProcessorExternalDataDomain(processor);
        Uns32      bits    = vmirtGetDomainAddressBits(domain);
        Uns64      spValue = (1ULL<<bits)-0x1000;

        vmiosRegWrite(processor, object->argSP, &spValue);
    }

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
    VMI_BOOL_PARAM_SPEC(paramValues, reportExitErrors, 0, "Report non-zero exit() return codes as simulator errors"),
    VMI_UNS64_PARAM_SPEC(paramValues, initsp, 0, 0, -1, "Stack Pointer initialization"),
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
// SAVE/RESTORE INTERFACE
// NOTE: State of files not saved so save/restore does not work for applications
//       that have opened files unless record/replay is also used
////////////////////////////////////////////////////////////////////////////////

//
// PK Semihost state save
//
VMIOS_SAVE_STATE_FN(riscvNewLibSaveCB) {
    vmirtSave(cxt, "heap", &object->heap, sizeof(object->heap));
}

//
// PK Semihost restore save
//
VMIOS_RESTORE_STATE_FN(riscvNewLibRestoreCB) {
    vmirtRestore(cxt, "heap", &object->heap, sizeof(object->heap));
}


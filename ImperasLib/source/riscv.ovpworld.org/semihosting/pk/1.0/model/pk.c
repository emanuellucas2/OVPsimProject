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

#include "syscall.h"

#define UnsArch Uns64
#define IntArch Int64
#define FMT_ARCH_FMT_D     FMT_64d
#define FMT_ARCH_FMT_X     FMT_64x
#define CPU_PREFIX         "RISCV/PK"

/*
 * Modified test mechanism to exit on execution of instruction at label write_tohost
 * may need to further enhance to see what is written to host ?
 */

#define FILE_DES_NUM 128
#define REG_ARG_NUM  8

#define RISCV_GPR_NUM 32
#define RISCV_BITS    32

//
// Implement optional exit return code checking
// (enabled by reportExitErrors parameter)
//
#define REPORT_EXIT_ERRORS

//
// Define the attributes value structure
//
typedef struct paramValuesS {
    VMI_PTR_PARAM(userargv);
    VMI_PTR_PARAM(userenvp);
    VMI_BOOL_PARAM(reportExitErrors);
    VMI_UNS64_PARAM(initsp);

    VMI_BOOL_PARAM(strace);
} paramValues, *paramValuesP;

#define UNUSED __attribute__((unused))
typedef struct vmiosObjectS {
    // argument registers (standard ABI)
    vmiRegInfoCP args[REG_ARG_NUM];
    // number of argument registers
    Uns32        numArgs;

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

    Int32 fileDescriptors[FILE_DES_NUM];

    Uns32 xlen;

    Bool strace;

    const char *fmtX, *fmtD;
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

typedef newlibStat newlibStat64;

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

    if(index>object->numArgs) {
        vmiMessage("P", CPU_PREFIX"_ANS",
            "No more than %u function arguments supported",
            object->numArgs
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
    if(index>object->numArgs) {
        vmiMessage("P", CPU_PREFIX"_ANS",
            "No more than %u function arguments supported",
            object->numArgs
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
// System call handler
//
#define SYSCALLDEF(_NAME) void SYSFN_ ## _NAME (  \
    vmiProcessorP processor,                      \
    vmiosObjectP  object,                         \
    Uns64 arg[]                                   \
)

#define SYSCALLFN(_NAME) SYSFN_ ## _NAME(processor, object, arg)

static SYSCALLDEF(exit) {
    IntArch code = arg[0];
    if (object->strace) vmiMessage("I", CPU_PREFIX, "SYSCALL(exit) = %d\n",
        (Uns32)code);
    vmirtExit(processor);
}

// int fstat(int fd, struct stat *buf);
static SYSCALLDEF(fstat) {
    IntArch fd = arg[0];
    UnsArch st = arg[1];
    UnsArch result;

    doFstat(processor, object, 0, fd, st);
    vmiosRegRead(processor, object->resultReg, &result);

    if (object->strace) vmiMessage("I", CPU_PREFIX, "SYSCALL(fstat, fd=%d, st=0x%08x) = %d\n",
        (Uns32)fd, (Uns32)st, (Uns32)result);
}

// int brk(void *addr);
static SYSCALLDEF(brk) {
    UnsArch addr = arg[0];
    UnsArch result;

    if (addr==0) {

        // Request for current top of heap
        if (object->heap != 0) {

            // Return last value set
            addr = object->heap;

        } else {

            // First call - lookup symbol to find base of heap
            // Standard GNU toolchain linker scripts use "_end"
            // SiFive freedom-e-sdk bsp linker scripts use "metal_segment_heap_target_start"
            Addr heap;
            if ((vmirtAddressLookup(processor, "_end", &heap) == NULL) &&
                (vmirtAddressLookup(processor, "metal_segment_heap_target_start", &heap) == NULL)
            ) {
                vmiMessage("P", CPU_PREFIX"_MHS",
                    "Missing _end or other symbol defining start of heap. sbrk() not supported"
                );
                vmirtFinish(-1);
            }

            // Round up to 4K page size
            heap += 0x1000 - 1;
            heap &= ~(0x1000 - 1);

            // Use initial base of heap
            addr = heap;
        }
    }

    // Set heap pointer to requested value
    object->heap = addr;

    // return pointer to top of heap
    setResult(processor, object, object->heap);
    vmiosRegRead(processor, object->resultReg, &result);

    if (object->strace) vmiMessage("I", CPU_PREFIX, "SYSCALL(brk, addr=0x%08x) = 0x%08X\n",
        (Uns32)arg[0], (Uns32)result);
}

// ssize_t write(int fd, const void *buf, size_t count);
static SYSCALLDEF(write) {
    IntArch fd    = arg[0];
    UnsArch buf   = arg[1];
    UnsArch count = arg[2];
    UnsArch result;

    doWrite(processor, object, 0, fd, buf, count);
    vmiosRegRead(processor, object->resultReg, &result);

    if (object->strace) vmiMessage("I", CPU_PREFIX, "SYSCALL(write, fd=%d, buf=0x%08x, count=%d) = %d\n",
        (Uns32)fd, (Uns32)buf, (Uns32)count, (Uns32)result);
}

// int close(int fd);
static SYSCALLDEF(close) {
    IntArch fd = arg[0];
    UnsArch result;

    doClose(processor, object, 0, fd);
    vmiosRegRead(processor, object->resultReg, &result);

    if (object->strace) vmiMessage("I", CPU_PREFIX, "SYSCALL(close, fd=%d) = %d\n",
        (Uns32)fd, (Uns32)result);
}

// int kill(pid_t pid, int sig);
static SYSCALLDEF(kill) {
    IntArch pid = arg[0];
    IntArch sig = arg[1];
    UnsArch result;

    doKill(processor, object, 0, pid);
    vmiosRegRead(processor, object->resultReg, &result);

    if (object->strace) vmiMessage("I", CPU_PREFIX, "SYSCALL(kill, fd=%d, sig=%d) = %d\n",
        (Uns32)pid, (Uns32)sig, (Uns32)result);
}

// time_t time(time_t *t)
static SYSCALLDEF(time) {
    IntArch time_t = arg[0];
    UnsArch result;

    doTime(processor, object, 0, time_t);
    vmiosRegRead(processor, object->resultReg, &result);

    if (object->strace) vmiMessage("I", CPU_PREFIX, "SYSCALL(time, time_t=0x%08x) = %d\n",
        (Uns32)time_t, (Uns32)result);
}

// gettimeofday (struct timeval *tv, struct timezone *tz)
static SYSCALLDEF(gettimeofday) {
    UnsArch tv = arg[0];
    UnsArch tz = arg[1];
    UnsArch result;

    doGettimeofday(processor, object, 0, tv);
    vmiosRegRead(processor, object->resultReg, &result);

    if (object->strace) vmiMessage("I", CPU_PREFIX, "SYSCALL(gettimeofday, tv=0x%08x, tz=0x%08x) = %d\n",
        (Uns32)tv, (Uns32)tz, (Uns32)result);
}

// off_t lseek (int fd, off_t offset, int whence)
static SYSCALLDEF(lseek) {
    IntArch fd     = arg[0];
    IntArch offset = arg[1];
    IntArch whence = arg[2];
    UnsArch result;

    doLseek(processor, object, 0, fd, offset, whence);
    vmiosRegRead(processor, object->resultReg, &result);

    if (object->strace) vmiMessage("I", CPU_PREFIX, "SYSCALL(lseek, fd=%d, offset=%d, whence=%d) = %d\n",
        (Uns32)fd, (Uns32)offset, (Uns32)whence, (Uns32)result);
}

// int = lstat (const char *file_name, struct stat *buf)
static SYSCALLDEF(lstat) {
    UnsArch file_name = arg[0];
    UnsArch buf       = arg[1];
    UnsArch result;

    doLstat(processor, object, 0, file_name, buf);
    vmiosRegRead(processor, object->resultReg, &result);

    if (object->strace) vmiMessage("I", CPU_PREFIX, "SYSCALL(lstat, file_name=0x%08x, buf=0x%08x) = %d\n",
        (Uns32)file_name, (Uns32)buf, (Uns32)result);
}

// int = open (const char *buf, int flags, int mode)
static SYSCALLDEF(open) {
    UnsArch buf    = arg[0];
    UnsArch flags  = arg[1];
    UnsArch mode   = arg[2];
    UnsArch result;

    doOpen(processor, object, "PK", 0, buf, flags, mode);

    vmiosRegRead(processor, object->resultReg, &result);

    if (object->strace) vmiMessage("I", CPU_PREFIX, "SYSCALL(open, buf=0x%08x, flags=%d, mode=%d) = %d\n",
        (Uns32)buf, (Uns32)flags, (Uns32)mode, (Uns32)result);
}

// ssize_t = read (int fd, void *buf, size_t count)
static SYSCALLDEF(read) {
    IntArch fd    = arg[0];
    UnsArch buf   = arg[1];
    IntArch count = arg[2];
    UnsArch result;

    doRead(processor, object, 0, fd, buf, count);
    vmiosRegRead(processor, object->resultReg, &result);

    if (object->strace) vmiMessage("I", CPU_PREFIX, "SYSCALL(read, fd=%d, buf=0x%08x, count=%d) = %d\n",
        (Uns32)fd, (Uns32)buf, (Uns32)count, (Uns32)result);
}

// int = stat (const char *file_name, struct stat *buf)
static SYSCALLDEF(stat) {
    UnsArch file_name = arg[0];
    UnsArch buf       = arg[1];
    UnsArch result;

    doStat(processor, object, 0, file_name, buf);
    vmiosRegRead(processor, object->resultReg, &result);

    if (object->strace) vmiMessage("I", CPU_PREFIX, "SYSCALL(stat, file_name=0x%08x, buf=0x%08x) = %d\n",
        (Uns32)file_name, (Uns32)buf, (Uns32)result);
}

// clock_t = times (struct tms *buf)
static SYSCALLDEF(times) {
    UnsArch buf = arg[0];
    UnsArch result;

    doTimes(processor, object, 0, buf);
    vmiosRegRead(processor, object->resultReg, &result);

    if (object->strace) vmiMessage("I", CPU_PREFIX, "SYSCALL(times, buf=0x%08x) = %d\n",
        (Uns32)buf, (Uns32)result);
}

#if (IMPERAS_LINUX==1)

#include <stdlib.h>

//
// unlink (char *filename)
//
static void doLink(
    vmiProcessorP processor,
    vmiosObjectP  object,
    UnsArch       reent,
    UnsArch       oldnameAddr,
    UnsArch       newnameAddr
) {

    // get file name from data domain
    memDomainP  domain   = vmirtGetProcessorDataDomain(processor);
    const char *oldname = vmirtGetString(domain, oldnameAddr);
    const char *newname = vmirtGetString(domain, newnameAddr);
    char command[strlen(oldname)+strlen(newname)+20];

    // implement unlink
    sprintf(command, "ln %s %s", oldname, newname);
    Int32 result = system(command);

    // return result
    setErrnoAndResult(processor, object, result, reent);
}

// int link(const char *oldname, const char *newname);
static SYSCALLDEF(link) {
    UnsArch oldname = arg[0];
    UnsArch newname = arg[1];
    UnsArch result;

    doLink(processor, object, 0, oldname, newname);
    vmiosRegRead(processor, object->resultReg, &result);

    if (object->strace) vmiMessage("I", CPU_PREFIX, "SYSCALL(link, oldname=0x%08x, newname=0x%08x) = %d\n",
        (Uns32)oldname, (Uns32)newname, (Uns32)result);
}

#endif

// int unlink(const char *pathname);
static SYSCALLDEF(unlink) {
    UnsArch pathname = arg[0];
    UnsArch result;

    doUnlink(processor, object, 0, pathname);
    vmiosRegRead(processor, object->resultReg, &result);

    if (object->strace) vmiMessage("I", CPU_PREFIX, "SYSCALL(unlink, pathname=0x%08x) = %d\n",
        (Uns32)pathname, (Uns32)result);
}

static SYSCALLDEF(unhandled) {
    UnsArch nr = arg[object->numArgs-1];
    vmiMessage("E", CPU_PREFIX, "SYSCALL(unhandled(nr=%d))\n", (Uns32)nr);
    vmirtFinish(-1);
}

//
// userData : 0=ecall 1=ebreak
//
static VMIOS_INTERCEPT_FN(riscvECALL) {
    Uns64 arg[8];

    //
    // RISCV ABI
    //   Integer calling convention Max 8 args (includes NR in arg7)
    //   ilp32e  calling convention Max 6 args (NR in t0)
    //
    Int8 i;
    for(i=0; i<object->numArgs; i++) {
        arg[i] = 0ULL;
        getArg(processor, object, i, &arg[i]);
    }

    Uns32 nr = arg[object->numArgs-1];
    if ((UnsPS)userData == 1) {
        // ebreak
        nr &= 0xFFFF; // Mask upper short
    }

    switch (nr) {
    case SYS_kill:
        SYSCALLFN(kill);
        break;
    case SYS_time:
        SYSCALLFN(time);
        break;
    case SYS_gettimeofday:
        SYSCALLFN(gettimeofday);
        break;
    case SYS_lseek:
        SYSCALLFN(lseek);
        break;
    case SYS_lstat:
        SYSCALLFN(lstat);
        break;
    case SYS_open:
        SYSCALLFN(open);
        break;
    case SYS_read:
        SYSCALLFN(read);
        break;
    case SYS_stat:
        SYSCALLFN(stat);
        break;
    case SYS_times:
        SYSCALLFN(times);
        break;
#if (IMPERAS_LINUX==1)
    case SYS_link:
        SYSCALLFN(link);
        break;
#endif
    case SYS_unlink:
        SYSCALLFN(unlink);
        break;
    case SYS_close:
        SYSCALLFN(close);
        break;
    case SYS_exit:
        SYSCALLFN(exit);
        break;
    case SYS_fstat:
        SYSCALLFN(fstat);
        break;
    case SYS_brk:
        SYSCALLFN(brk);
        break;
    case SYS_write:
        SYSCALLFN(write);
        break;
    default:
        // This should be configurable between opaque/transparent
        SYSCALLFN(unhandled);
        break;
    }
}

static VMIOS_MORPH_FN(riscvOSOperation) {
    const char *disass = vmirtDisassemble(processor, thisPC, DSA_UNCOOKED);

    if (!strncmp(disass, "ecall", strlen("ecall"))) {
        *opaque   = True;
        *userData = (void *)(UnsPS) 0;
        return riscvECALL;

    } else if (!strncmp(disass, "ebreak", strlen("ebreak"))) {
        *opaque   = True;
        *userData = (void *)(UnsPS) 1;
        return riscvECALL;
    }

    return 0;
}

static void getXlen(vmiProcessorP processor, vmiosObjectP object) {

    vmiRegInfoCP a0 = object->args[0];

    object->xlen = a0->bits;

    if (object->xlen==32) {
        object->fmtX = "0x%08x";
        object->fmtD = "%d";
    } else if (object->xlen==64) {
        object->fmtX = "0x"FMT_64x;
        object->fmtD = FMT_64d;
    } else {
        vmiMessage("E", CPU_PREFIX, "Unsupported xlen %u", object->xlen);   // LCOV_EXCL_LINE
        vmirtFinish(-1);                                                    // LCOV_EXCL_LINE
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
        vmiMessage("F", CPU_PREFIX, "Unable to find register %s/%s", name1, name2);
    }

    return reg;
}

static VMIOS_CONSTRUCTOR_FN(constructor) {

    // Read configuration parameters
    paramValuesP params = parameterValues;
    object->argv             = params->userargv;
    object->envp             = params->userenvp;
    object->reportExitErrors = params->reportExitErrors;
    object->strace           = params->strace;

    // first argument registers (standard ABI)
    object->args[0] = getAltReg(processor, "a0", "x10");
    object->args[1] = getAltReg(processor, "a1", "x11");
    object->args[2] = getAltReg(processor, "a2", "x12");
    object->args[3] = getAltReg(processor, "a3", "x13");
    object->args[4] = getAltReg(processor, "a4", "x14");
    object->args[5] = getAltReg(processor, "a5", "x15");

    // Check processor for E Extension
    Bool         extensionEPresent = False;
    vmiRegInfoCP misa              = vmirtGetRegByName(processor, "misa");

    // misa may be absent if Zicsr=0
    if(misa) {

        UnsArch misaValue;
        UnsArch mask = (1 << ('E' - 'A'));

        vmiosRegRead(processor, misa, &misaValue);
        if(mask & misaValue) {
            extensionEPresent = True;
        }
    }

    if (!extensionEPresent) {

        // Default integer calling convention if E Extension absent
        object->numArgs = REG_ARG_NUM;
        object->args[6] = getAltReg(processor, "a6", "x16");
        object->args[7] = getAltReg(processor, "a7", "x17");

    } else {

        // ilp32e calling convention
        object->numArgs = 7;
        object->args[6] = getAltReg(processor, "t0", "x5");
    }

    // return register (standard ABI)
    object->resultReg = object->args[0];

    // stack pointer
    object->argSP = getAltReg(processor, "sp", "x2");

    //
    // Are we connected to a 32, 64 or 128 bit processor
    //
    getXlen(processor, object);

    if (params->SETBIT(initsp)) {
        // set initial value of stack pointer to provided address
        vmiosRegWrite(processor, object->argSP, &params->initsp);

    } else {
        // adjust initial value of stack pointer to valid physical memory address

        memDomainP domain  = vmirtGetProcessorExternalDataDomain(processor);
        Uns32      bits    = vmirtGetDomainAddressBits(domain);
        Uns64      spValue = (1ULL<<bits)-0x1000;

        vmiosRegWrite(processor, object->argSP, &spValue);
    }

    // Sets up data common to all newlib implementations
    // Defined in newlibSemiHost.c.h
    setupDescriptors(object, processor);
}

static
VMIOS_DESTRUCTOR_FN(destructor)
{

}

//
// Define formals
//
static vmiParameter formals[] = {
    VMI_PTR_PARAM_SPEC(paramValues,   userargv, 0, "Pointer to argv structure"),
    VMI_PTR_PARAM_SPEC(paramValues,   userenvp, 0, "Pointer to envp structure"),
    VMI_BOOL_PARAM_SPEC(paramValues,  reportExitErrors, 0, "Report non-zero exit() return codes as simulator errors"),
    VMI_UNS64_PARAM_SPEC(paramValues, initsp,   0, 0, -1, "Stack Pointer initialization"),
    VMI_BOOL_PARAM_SPEC(paramValues,  strace,   0, "trace  proxy system calls (default)"),
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
VMIOS_SAVE_STATE_FN(pkSaveCB) {
    vmirtSave(cxt, "heap", &object->heap, sizeof(object->heap));
}

//
// PK Semihost restore save
//
VMIOS_RESTORE_STATE_FN(pkRestoreCB) {
    vmirtRestore(cxt, "heap", &object->heap, sizeof(object->heap));
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
    .packageName    = "ProxyKernel",              // description
    .objectSize     = sizeof(vmiosObject),        // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {
        .vendor  = "riscv.ovpworld.org",
        .library = "intercept",
        .name    = "pk",
        .version = "1.0"
    },

    ////////////////////////////////////////////////////////////////////////
    // SAVE/RESTORE ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .saveCB     = pkSaveCB,                     // model state save callback
    .restoreCB  = pkRestoreCB,                  // model state restore callback
    .srVersion  = 1,                            // model save/restore version

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .constructorCB  = constructor,              // object constructor
    .destructorCB   = destructor,               // object destructor

    ////////////////////////////////////////////////////////////////////////
    // PARAMETER CALLBACKS
    ////////////////////////////////////////////////////////////////////////

    .paramSpecsCB     = getParamSpecs,          // iterate parameter declarations
    .paramValueSizeCB = getParamTableSize,      // get parameter table size

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    .morphCB        = riscvOSOperation,         // morph callback

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    .intercepts = {
        // -------------------   ----------- ------ -----------------
        // Name                  Address     Opaque Callback
        // -------------------   ----------- ------ -----------------
        //
        // Intercept main for argc, argv, env
        //
        { "main",                   0,      False, mainStackInitCB  },

        {0}
    }
};

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

/*
 * Include this file in a Newlib SemiHost intercept library to implement
 * the newlib functions.
 *
 * Requires the following defined before the include:
 *
 *      #define FILE_DES_NUM <number of file descriptors
 *
 *      vmiosObject structure definition with the following defined:
 *          Addr         impurePtrAddr;
 *          memDomainP   impurePtrDomain;
 *          Addr         errnoAddr;
 *          memDomainP   errnoDomain;
 *          Int32        fileDescriptors[FILE_DES_NUM];
 *
 *       void getArg(vmiProcessorP processor, vmiosObjectP object, Uns32 index, void *result);
 *
 *       A typedef named "newlibStat" defining a target specific struct that includes
 *       the following members with the proper size and position for the target's "struct stat":
 *          mode. size, atime, mtime, ctime, blksize, blocks (unless NOSTAT_BLOCKS is defined)
 *
 */

#ifndef NEWLIB_SEMIHOST_C_H
#define NEWLIB_SEMIHOST_C_H

#include <errno.h>
#include <string.h>

// VMI area includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiVersion.h"

// Define LEAD_US as "_" for targets that add leading underscores to symbols
#ifndef LEAD_US
#define LEAD_US
#endif

//  Name and offset to use for reentrant newlib implementations
#ifndef REENT_ERRNO_REF
#define REENT_ERRNO_REF LEAD_US"_impure_ptr"
#endif
#ifndef GLOBAL_ERRNO_REF
#define GLOBAL_ERRNO_REF LEAD_US"_global_impure_ptr"
#endif
#ifndef ERRNO_OFFSET
#define ERRNO_OFFSET 0
#endif

// Alternate name to check for non-reentrant implementations
// e.g. CodeSourcery Pro versions of libc
#ifndef ERRNO_REF
#define ERRNO_REF LEAD_US"errno"
#endif

// Target's newlib file modes
#ifndef TARGET_S_IFDIR
#define TARGET_S_IFDIR  0x4000
#endif
#ifndef TARGET_S_IFREG
#define TARGET_S_IFREG  0x8000
#endif

// Target's newlib open() flags
#ifndef TARGET_O_CREAT
#define TARGET_O_CREAT  0x200
#endif
#ifndef TARGET_O_APPEND
#define TARGET_O_APPEND 0x008
#endif
#ifndef TARGET_O_TRUNC
#define TARGET_O_TRUNC  0x400
#endif

// Default mode to use for open() if one isn't passed in
#ifndef DEFAULT_OPEN_MODE
    #if IMPERAS_WINDOWS
        //#define OPEN_MODE _S_IREAD|_S_IWRITE
        #define DEFAULT_OPEN_MODE 0600
    #else
        //#define OPEN_MODE S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH
        #define DEFAULT_OPEN_MODE 0644
    #endif
#endif

// By default use 4 bytes for both tv_sec and tv_usec
// Override this for other sizes
#ifndef NEWLIB_TIMEVAL_DEFINED
typedef struct newlibTimeval {
    Uns32 tv_sec;     /* seconds */
    Uns32 tv_usec;    /* microseconds */
} newlibTimeval;
#endif

// Define default architectural-width unsigned and signed types
// (Defaults to 32, Override this for other sizes)
#define UnsArch Uns32        // In RL78, a pointer type size is 16 bit, and hardware address size is 20 bit.
#define IntArch Int16

#define STRACE 0

//
// Include the argc/argv/envp handling routines for main() interception
//
//#ifndef _INTERCEPT_MAIN_
//#define _INTERCEPT_MAIN_
//#endif
//#include "ovpworld.org/modelSupport/semihosting/1.0/model/argvenvp.c.h"
//#undef  _INTERCEPT_MAIN_

//
// Must be called from Constructor to setup variables in vmiosObject
//
static void setupNewlib(vmiosObjectP object, vmiProcessorP processor) {

    // Sanity check argument registers
//    vmiRegInfoCP lastArgReg = object->args[REG_ARG_NUM-1];
//    VMI_ASSERT(
//        lastArgReg,
//                "Incorrect argument registers, missing %d.",
//                REG_ARG_NUM-1
//    );
//    if(lastArgReg->bits!=sizeof(UnsArch)*8) {
//        vmiMessage("F", CPU_PREFIX"_REGWIDTH",
//                "Incompatible argument register width. Processor %u bits and loaded newlib semihost compiled for %u bits.",
//                lastArgReg->bits, (Uns32) sizeof(UnsArch)*8);
//    }

    // initialise stdin, stderr and stdout
    object->fileDescriptors[0] = vmiosGetStdin(processor);
    object->fileDescriptors[1] = vmiosGetStdout(processor);
    object->fileDescriptors[2] = vmiosGetStderr(processor);

    // initialise remaining file descriptors
    Uns32 i;
    for(i=3; i<FILE_DES_NUM; i++) {
        object->fileDescriptors[i] = -1;
    }

    // get __impure_ptr domain and address
    object->impurePtrDomain = vmirtAddressLookup(
        processor, REENT_ERRNO_REF, &object->impurePtrAddr        // 20bit
    );

    // If impure_ptr not found check for global_impure_ptr
    if (!object->impurePtrDomain) {
        object->impurePtrDomain = vmirtAddressLookup(
            processor, GLOBAL_ERRNO_REF, &object->impurePtrAddr
        );
    }

    // If impure_ptr and global_impure_ptr not found check for plain old errno, _errno or __errno
    if (!object->impurePtrDomain) {
        object->errnoDomain = vmirtAddressLookup(
            processor, ERRNO_REF, &object->errnoAddr
        );
    }
}


////////////////////////////////////////////////////////////////////////////////
// UTILITIES
////////////////////////////////////////////////////////////////////////////////

//
// Map from simulated file descriptor to native one
//
static Int32 mapFileDescriptor(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Uns32         i
) {

    Int32 fdNative = -1;

    if(i >= 0 && i<FILE_DES_NUM) {
        fdNative = object->fileDescriptors[i];
    }

    // Set errno if this is a bad descriptor
    if (fdNative == -1) {
        errno = EBADF;
    }

    return fdNative;

}

//
// Return the next available file descriptor
//
static Int32 newFileDescriptor(vmiosObjectP object, const char *context) {

    Int32 i;

    // find and return the first unused file descriptor
    for(i=0; i<FILE_DES_NUM; i++) {
        if(object->fileDescriptors[i]==-1) {
            return i;
        }
    }

    vmiMessage("P", CPU_PREFIX"_TMOF",
        "Too many open files in %s - semihosting supports up to %u",
        context, FILE_DES_NUM
    );

    errno = EMFILE;

    return -1;
}


#define GET_BIT(_R, _M) \
    (((_R) & (_M)) ? 1 : 0)

#define MASK_PSW_RBS1     0x00000020  // register bank select
#define MASK_PSW_RBS0     0x00000008  // register bank select

//
// Set the errno and return the result
//
static void setErrnoAndResult(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Int32         result,
    UnsArch       reentP
) {

    memDomainP domain = 0;
    UnsArch    errnoAddr;
    memEndian  endian = vmirtGetProcessorDataEndian(processor);

    // Get domain and address of errno in simulated memory

    if (reentP != 0) {

        // we were passed pointer to struct _reent so use that
        domain = vmirtGetProcessorDataDomain(processor);
        errnoAddr = reentP + ERRNO_OFFSET;

    } else if (object->impurePtrDomain) {

        UnsArch impurePtr = 0;

        // Using re-entrant errno
        domain = object->impurePtrDomain;

        // read address of the _reent structure
        vmirtReadNByteDomain(
            domain, object->impurePtrAddr, &impurePtr,
            2, 0, MEM_AA_FALSE
        );
        impurePtr = impurePtr | 0xF0000;

        // get address of errno field in _reent structure
        errnoAddr = impurePtr + ERRNO_OFFSET;

    } else if (object->errnoDomain){

        // No re-entrant errno - use legacy errno if present
        domain    = object->errnoDomain;
        errnoAddr = object->errnoAddr;

    } else {

        static Bool written = False;
        if (!written) {
            vmiMessage(
                "W", CPU_PREFIX"_NEU",
                "Unable to find symbol "REENT_ERRNO_REF" or "ERRNO_REF
                ". newlib errno will not be updated.\n"
            );
            written = True;
        }

    }

    // Write back errnum if domain is available
    if (domain) {
        Uns32 errnum = errno;
        vmirtWrite2ByteDomain(domain, errnoAddr, endian, errnum, MEM_AA_FALSE);    // @@@
    }

    // Write back result
    IntArch resultRegVal = result;
//  Uns32 val_PSW;
    Uns32 val_RBS;

//    vmirtRegRead (processor, object->reg_PSW, &val_PSW);
//  val_RBS = (GET_BIT(val_PSW, MASK_PSW_RBS1) << 1) | GET_BIT(val_PSW, MASK_PSW_RBS0);
    val_RBS = 1;        // R8, R9

    vmiosRegWrite(processor, object->reg_X[val_RBS], ((Uns8*) &resultRegVal) + 0);        // R8
    vmiosRegWrite(processor, object->reg_A[val_RBS], ((Uns8*) &resultRegVal) + 1);        // R9

}

//
// Convert a 2, 4 or 8 byte value to an Uns16
//
static Uns16 toUns16(void *val, size_t size) {
    Uns16 retval = 0;
    switch (size) {
        case 2  : retval = (Uns16) (*(Uns16 *)val); break;
        case 4  : retval = (Uns16) (*(Uns32 *)val); break;
        case 8  : retval = (Uns16) (*(Uns64 *)val); break;
        default : vmiMessage("F", CPU_PREFIX"_TU16", "Invalid member size"); break;
    }
    return retval;
}

//
// Convert a a 2, 4 or 8 byte value to an Uns32
//
static Uns32 toUns32(void *val, size_t size) {
    Uns32 retval = 0;
    switch (size) {
        case 2  : retval = (Uns32) (*(Uns16 *)val); break;
        case 4  : retval = (Uns32) (*(Uns32 *)val); break;
        case 8  : retval = (Uns32) (*(Uns64 *)val); break;
        default : vmiMessage("F", CPU_PREFIX"_TU32", "Invalid member size"); break;
    }
    return retval;
}

//
// Convert a a 2, 4 or 8 byte value to an Uns64
//
static Uns64 toUns64(void *val, size_t size) {
    Uns64 retval = 0;
    switch (size) {
        case 2  : retval = (Uns64) (*(Uns16 *)val); break;
        case 4  : retval = (Uns64) (*(Uns32 *)val); break;
        case 8  : retval = (Uns64) (*(Uns64 *)val); break;
        default : vmiMessage("F", CPU_PREFIX"_TU64", "Invalid member size"); break;
    }
    return retval;
}

//
// Set the member of the target struct to the value in the host struct,
// converting size and endianness as necessary
//
static void setTargetMember(
    void      *newlibValueP,
    size_t     newlibSize,
    void      *hostValueP,
    size_t     hostSize,
    memEndian  endian
) {

    switch (newlibSize) {
        case 2: {
            Uns16 val = toUns16(hostValueP, hostSize);
            *(Uns16 *)newlibValueP = SWAP_2_BYTE_COND(val, endian!=MEM_ENDIAN_NATIVE);
            break;
        }
        case 4: {
            Uns32 val = toUns32(hostValueP, hostSize);
            *(Uns32 *)newlibValueP = SWAP_4_BYTE_COND(val, endian!=MEM_ENDIAN_NATIVE);
            break;

        }
        case 8: {
            Uns64 val = toUns64(hostValueP, hostSize);
            *(Uns64 *)newlibValueP = SWAP_8_BYTE_COND(val, endian!=MEM_ENDIAN_NATIVE);
            break;

        }
        default : vmiMessage("F", CPU_PREFIX"_TU64", "Invalid member size"); break;
    }
}

//
// Copy data from the host stat buffer 'buf' to the target-specific
// stat structure in simulated memory at address 'bufAddr'
// Requires file including this file to define the newlibStat struct
//
//
static void transcribeStatData(
    vmiProcessorP processor,
    UnsArch       bufAddr,
    vmiosStatBufP buf
) {

    memDomainP domain  = vmirtGetProcessorDataDomain(processor);
    memEndian  endian  = vmirtGetProcessorDataEndian(processor);
    newlibStat stat    = {0};

    // convert from host mode to newlib mode
    // - host S_IFDIR converts to TARGET_S_IFDIR
    // - host S_IFREG converts to TARGET_S_IFREG
    buf->mode = (
        (buf->mode & 0x1ff) |
        ((buf->mode & VMIOS_S_IFDIR) ? TARGET_S_IFDIR : 0) |
        ((buf->mode & VMIOS_S_IFREG) ? TARGET_S_IFREG : 0)
    );

    // Copy over supported fields, converting sizes and endianness as necessary
    setTargetMember(&stat.mode,    sizeof(stat.mode),    &buf->mode,    sizeof(buf->mode),    endian);
    setTargetMember(&stat.size,    sizeof(stat.size),    &buf->size,    sizeof(buf->size),    endian);
    setTargetMember(&stat.atime,   sizeof(stat.atime),   &buf->atime,   sizeof(buf->atime),   endian);
    setTargetMember(&stat.ctime,   sizeof(stat.ctime),   &buf->ctime,   sizeof(buf->ctime),   endian);
    setTargetMember(&stat.mtime,   sizeof(stat.mtime),   &buf->mtime,   sizeof(buf->mtime),   endian);
    setTargetMember(&stat.blksize, sizeof(stat.blksize), &buf->blksize, sizeof(buf->blksize), endian);
#ifndef NO_STAT_BLOCKS
    setTargetMember(&stat.blocks,  sizeof(stat.blocks),  &buf->blocks,  sizeof(buf->blocks),  endian);
#endif

    // write stat struct into simulated memory
    vmirtWriteNByteDomain(domain, bufAddr, &stat, sizeof(stat), 0, MEM_AA_FALSE);

}

//
// Write data in the time buffer 'buf' back to simulation space at address
// 'bufAddr'
//
static void transcribeTimeData(
    vmiProcessorP processor,
    UnsArch       bufAddr,
    vmiosTimeBufP buf
) {
    memDomainP    domain = vmirtGetProcessorDataDomain(processor);
    memEndian     endian = vmirtGetProcessorDataEndian(processor);
    newlibTimeval tv    = {0};

    // Copy over fields, converting sizes and endianness as necessary
    setTargetMember(&tv.tv_sec,  sizeof(tv.tv_sec),  &buf->sec,  sizeof(buf->sec),  endian);
    setTargetMember(&tv.tv_usec, sizeof(tv.tv_usec), &buf->usec, sizeof(buf->usec), endian);

    // write values into simulated memory
    vmirtWriteNByteDomain(domain, bufAddr, &tv, sizeof(tv), 0, MEM_AA_FALSE);
}

//
// Write data in the times buffer 'buf' back to simulation space at address
// 'bufAddr'
//
static void transcribeTmsData(
    vmiProcessorP processor,
    UnsArch       bufAddr,
    Uns32         iCount
) {
    memDomainP domain = vmirtGetProcessorDataDomain(processor);
    memEndian  endian = vmirtGetProcessorDataEndian(processor);

    //# 9 "c:\\program files\\kpit\\gnurl78v15.01-elf\\rl78-elf\\rl78-elf\\include\\sys\\times.h" 2 3
    //
    //typedef unsigned long clock_t;
    //
    //struct tms {
    // clock_t tms_utime;
    // clock_t tms_stime;
    // clock_t tms_cutime;
    // clock_t tms_cstime;
    //};

    // newlib tms structure
    struct {
        Uns32 utime;    //  0: utime
        Uns32 ctime;    //  4: ctime
        Uns32 cutime;   //  8:
        Uns32 cstime;   // 12:
    } simTmsStruct = {0};

    // We only care about the utime field.
    simTmsStruct.utime = SWAP_4_BYTE_COND(iCount, endian!=MEM_ENDIAN_NATIVE);

    // write tms struct into simulated memory
    vmirtWriteNByteDomain(
        domain, bufAddr, &simTmsStruct, sizeof(simTmsStruct), 0, MEM_AA_FALSE
    );
}


////////////////////////////////////////////////////////////////////////////////
// INTERCEPT CALLBACKS IMPLEMENTING NEWLIB FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

// Allow all intercept functions to be unused
#ifndef UNUSED
#define UNUSED __attribute__((unused))
#endif

//
// exit
//
static UNUSED VMIOS_INTERCEPT_FN(exitCB) {
    vmirtExit(processor);
}

//
// open (const char *buf, int flags, int mode)
//
static void doOpen(
    vmiProcessorP processor,
    vmiosObjectP  object,
    const char   *context,
    UnsArch       reent,
    UnsArch       pathnameAddr,
    IntArch       flags,
    IntArch       mode
) {

    if (STRACE) vmiPrintf("(STRACE) open(pathname=0x%08x, flags=0x%08x, mode=0x%08x)\n", (Uns32)pathnameAddr, (Uns32)flags, (Uns32)mode);

    // get file name from data domain
    memDomainP  domain   = vmirtGetProcessorDataDomain(processor);
    const char *pathname = vmirtGetString(domain, pathnameAddr);

    // implement open - only certain flags are supported, and must be converted to VMIOS conventions
    Int32 vmiosFlags = (flags & 0x003)
                     | ((flags & TARGET_O_CREAT)  ? VMIOS_O_CREAT  : 0)
                     | ((flags & TARGET_O_APPEND) ? VMIOS_O_APPEND : 0)
                     | ((flags & TARGET_O_TRUNC)  ? VMIOS_O_TRUNC  : 0);

    Int32 result = vmiosOpen(processor, pathname, vmiosFlags, mode);

    if(result != -1) {

        // save file descriptor in simulated descriptor table
        Int32 fdMap = newFileDescriptor(object, context);
        if (fdMap != -1) {
            object->fileDescriptors[fdMap] = result;
        }

        // Return the fileDescriptor (or error)
        result = fdMap;

    }

    // return result
    setErrnoAndResult(processor, object, result, reent);

}

//
// open (const char *buf, int flags, int mode)
//
static UNUSED VMIOS_INTERCEPT_FN(openCB) {

    UnsArch pathnameAddr = 0;
    IntArch flags = 0;
    IntArch mode = DEFAULT_OPEN_MODE;

    // obtain function arguments
    getArg(processor, object, 0, &pathnameAddr);
    getArg(processor, object, 1, &flags);

#ifndef NO_OPEN_MODE_ARG
    getArg(processor, object, 2, &mode);
#endif

    pathnameAddr = pathnameAddr | 0xF0000;        // const char*

    doOpen(processor, object, context, 0, pathnameAddr, flags, mode);

}

//
// open_r (struct _reent *r, const char *buf, int flags, int mode)
//
static UNUSED VMIOS_INTERCEPT_FN(open_rCB) {

    UnsArch reent = 0;
    UnsArch pathnameAddr = 0;
    IntArch flags = 0;
    IntArch mode = DEFAULT_OPEN_MODE;

    // obtain function arguments
    getArg(processor, object, 0, &reent);
    getArg(processor, object, 1, &pathnameAddr);
    getArg(processor, object, 2, &flags);

#ifndef NO_OPEN_MODE_ARG
    getArg(processor, object, 3, &mode);
#endif

    reent        = reent        | 0xF0000;        // struct _reent*
    pathnameAddr = pathnameAddr | 0xF0000;        // const char*

    doOpen(processor, object, context, reent, pathnameAddr, flags, mode);

}

//
// close (int fd)
//
static void doClose(
    vmiProcessorP processor,
    vmiosObjectP  object,
    UnsArch       reent,
    IntArch       fd
) {

    if (STRACE) vmiPrintf("(STRACE) close(fd=%d)\n", (Uns32)fd);

    // implement close
    Int32 fdMap  = mapFileDescriptor(processor, object, fd);
    Int32 result = fdMap != -1 ? vmiosClose(processor, fdMap) : -1;

    // close out the semihosted file descriptor if success
    if(result != -1) {
        object->fileDescriptors[fd] = -1;
    }

    // return result
    setErrnoAndResult(processor, object, result, reent);
}

//
// close (int fd)
//
static UNUSED VMIOS_INTERCEPT_FN(closeCB) {

    IntArch fd = 0;

    // obtain function arguments
    getArg(processor, object, 0, &fd);

    doClose(processor, object, 0, fd);
}

//
// close_r (struct _reent *, int)
//
static UNUSED VMIOS_INTERCEPT_FN(close_rCB) {

    UnsArch reent = 0;
    IntArch fd = 0;

    // obtain function arguments
    getArg(processor, object, 0, &reent);
    getArg(processor, object, 1, &fd);

    reent = reent | 0xF0000;                // struct _reent*

    doClose(processor, object, reent, fd);
}

//
// unlink (char *filename)
//
static void doUnlink(
    vmiProcessorP processor,
    vmiosObjectP  object,
    UnsArch       reent,
    UnsArch       pathnameAddr
) {

    // get file name from data domain
    memDomainP  domain   = vmirtGetProcessorDataDomain(processor);
    const char *pathname = vmirtGetString(domain, pathnameAddr);

    // implement unlink
    Int32 result = vmiosUnlink(processor, pathname);

    // return result
    setErrnoAndResult(processor, object, result, reent);
}

//
// unlink (char *filename)
//
static UNUSED VMIOS_INTERCEPT_FN(unlinkCB) {

    UnsArch pathnameAddr = 0;

    // obtain function arguments
    getArg(processor, object, 0, &pathnameAddr);

    pathnameAddr = pathnameAddr | 0xF0000;    // char*

    doUnlink(processor, object, 0, pathnameAddr);
}

//
// unlink_r (struct _reent *rchar *filename)
//
static UNUSED VMIOS_INTERCEPT_FN(unlink_rCB) {

    UnsArch reent = 0;
    UnsArch pathnameAddr = 0;

    // obtain function arguments
    getArg(processor, object, 0, &reent);
    getArg(processor, object, 1, &pathnameAddr);

    reent        = reent        | 0xF0000;    // struct _reent*
    pathnameAddr = pathnameAddr | 0xF0000;    // char*

    doUnlink(processor, object, reent, pathnameAddr);
}

//
// read (int fd, void *buf, size_t count)
//
static void doRead(
    vmiProcessorP processor,
    vmiosObjectP  object,
    UnsArch       reent,
    IntArch       fd,
    UnsArch       buf,
    UnsArch       count
) {

    if (STRACE) vmiPrintf("(STRACE) read(fd=%d, count=%d)\n", (Uns32)fd, (Uns32)count);

    // implement read
    memDomainP domain = vmirtGetProcessorDataDomain(processor);
    Int32      fdMap  = mapFileDescriptor(processor, object, fd);
    Int32      result = fdMap != -1 ? vmiosRead(processor, fdMap, domain, buf, count) : -1;

    // return result
    setErrnoAndResult(processor, object, result, reent);
}

//
// read (int fd, void *buf, size_t count)
//
static UNUSED VMIOS_INTERCEPT_FN(readCB) {

    IntArch fd = 0;
    UnsArch buf = 0;
    UnsArch count = 0;

    // obtain function arguments
    getArg(processor, object, 0, &fd);
    getArg(processor, object, 1, &buf);
    getArg(processor, object, 2, &count);

    buf = buf | 0xF0000;                    // void*

    doRead(processor, object, 0, fd, buf, count);
}

//
// read_r (struct _reent *r, int fd, void *buf, size_t count)
//
static UNUSED VMIOS_INTERCEPT_FN(read_rCB) {

    UnsArch reent = 0;
    IntArch fd = 0;
    UnsArch buf = 0;
    UnsArch count = 0;

    // obtain function arguments
    getArg(processor, object, 0, &reent);
    getArg(processor, object, 1, &fd);
    getArg(processor, object, 2, &buf);
    getArg(processor, object, 3, &count);

    reent = reent | 0xF0000;                // struct _reent*
    buf   = buf   | 0xF0000;                // void*

    doRead(processor, object, reent, fd, buf, count);
}

//
// write (int fd, void *buf, size_t count)
//
static void doWrite(
        vmiProcessorP processor,
        vmiosObjectP  object,
        UnsArch       reent,
        IntArch       fd,
        UnsArch       buf,
        UnsArch       count
) {

    if (STRACE) vmiPrintf("(STRACE) write(fd=%d, count=%d)\n", (Uns32)fd, (Uns32)count);

    // implement write
    memDomainP domain = vmirtGetProcessorDataDomain(processor);
    Int32      fdMap  = mapFileDescriptor(processor, object, fd);
    Int32      result = fdMap != -1 ? vmiosWrite(processor, fdMap, domain, buf, count) : -1;

    // vmiPrintf("(STRACE) write(%d, %x, %d)\n", (Int32)fd, (Uns32)buf, (Uns32)count);

    // return result
    setErrnoAndResult(processor, object, result, reent);
}

//
// write (int fd, void *buf, size_t count)
//
static UNUSED VMIOS_INTERCEPT_FN(writeCB) {

    IntArch fd = 0;
    UnsArch buf = 0;
    UnsArch count = 0;

    // obtain function arguments
    getArg(processor, object, 0, &fd);
    getArg(processor, object, 1, &buf);
    getArg(processor, object, 2, &count);

    buf = buf | 0xF0000;                    // void*

    doWrite(processor, object, 0, fd, buf, count);
}

//
// write_r (struct _rent *r, int fd, void *buf, size_t count)
//
static UNUSED VMIOS_INTERCEPT_FN(write_rCB) {

    UnsArch reent = 0;
    IntArch fd = 0;
    UnsArch buf = 0;
    UnsArch count = 0;

    // obtain function arguments
    getArg(processor, object, 0, &reent);
    getArg(processor, object, 1, &fd);
    getArg(processor, object, 2, &buf);
    getArg(processor, object, 3, &count);

    reent = reent | 0xF0000;                // struct _reent*
    buf   = buf   | 0xF0000;                // void

    doWrite(processor, object, reent, fd, buf, count);
}

//
// lseek (int fd, off_t offset, int whence)
//
static void doLseek(
    vmiProcessorP processor,
    vmiosObjectP  object,
    UnsArch       reent,
    IntArch       fd,
    IntArch       offset,
    IntArch       whence
) {

    // implement lseek
    Int32 fdMap  = mapFileDescriptor(processor, object, fd);
    Int32 result = fdMap != -1 ? vmiosLSeek(processor, fdMap, offset, whence) : 1;

    // return result
    setErrnoAndResult(processor, object, result, reent);
}

//
// lseek (int fd, off_t offset, int whence)
//
static UNUSED VMIOS_INTERCEPT_FN(lseekCB) {

    IntArch fd = 0;
    IntArch offset = 0;
    IntArch whence = 0;

    // obtain function arguments
    getArg(processor, object, 0, &fd);
    getArg(processor, object, 1, &offset);
    getArg(processor, object, 2, &whence);

    doLseek(processor, object, 0, fd, offset, whence);
}

//
// lseek_r (struct _reent *, int, _off_t, int)
//
static UNUSED VMIOS_INTERCEPT_FN(lseek_rCB) {

    UnsArch reent = 0;
    IntArch fd = 0;
    IntArch offset = 0;
    IntArch whence = 0;

    // obtain function arguments
    getArg(processor, object, 0, &reent);
    getArg(processor, object, 1, &fd);
    getArg(processor, object, 2, &offset);
    getArg(processor, object, 3, &whence);

    reent = reent | 0xF0000;                    // struct _reent*

    doLseek(processor, object, reent, fd, offset, whence);
}

//
// fstat (int filedes, struct stat *buf)
//
static void doFstat(
    vmiProcessorP processor,
    vmiosObjectP  object,
    UnsArch       reent,
    IntArch       filedes,
    UnsArch       bufAddr
) {

    // implement fstat
    vmiosStatBuf statBuf = {0};
    Int32        fdMap   = mapFileDescriptor(processor, object, filedes);
    Int32        result  = fdMap != -1 ? vmiosFStat(processor, fdMap, &statBuf) : -1;

    // write back results
    if (result != -1) {
        transcribeStatData(processor, bufAddr, &statBuf);
    }
    setErrnoAndResult(processor, object, result, reent);
}

//
// fstat (int filedes, struct stat *buf)
//
static UNUSED VMIOS_INTERCEPT_FN(fstatCB) {

    IntArch filedes = 0;
    UnsArch bufAddr = 0;

    // obtain function arguments
    getArg(processor, object, 0, &filedes);
    getArg(processor, object, 1, &bufAddr);

    bufAddr = bufAddr | 0xF0000;                // struct stat*

    doFstat(processor, object, 0, filedes, bufAddr);
}

//
// fstat_r (struct _reent *r, int filedes, struct stat *buf)
//
static UNUSED VMIOS_INTERCEPT_FN(fstat_rCB) {

    UnsArch reent = 0;
    IntArch filedes = 0;
    UnsArch bufAddr = 0;

    // obtain function arguments
    getArg(processor, object, 0, &reent);
    getArg(processor, object, 1, &filedes);
    getArg(processor, object, 2, &bufAddr);

    reent   = reent   | 0xF0000;                // struct _reent*
    bufAddr = bufAddr | 0xF0000;                // struct stat*

   doFstat(processor, object, reent, filedes, bufAddr);
}

//
// stat (const char *file_name, struct stat *buf)
//
static void doStat(
    vmiProcessorP processor,
    vmiosObjectP  object,
    UnsArch       reent,
    UnsArch       file_nameAddr,
    UnsArch       bufAddr
) {

    // get file name from data domain
    memDomainP  domain    = vmirtGetProcessorDataDomain(processor);
    const char *file_name = vmirtGetString(domain, file_nameAddr);

    // implement stat
    vmiosStatBuf statBuf = {0};
    Int32        result  = vmiosStat(processor, file_name, &statBuf);

    // write back results
    if (result != -1) {
        transcribeStatData(processor, bufAddr, &statBuf);
    }
    setErrnoAndResult(processor, object, result, reent);
}

//
// stat (const char *file_name, struct stat *buf)
//
static UNUSED VMIOS_INTERCEPT_FN(statCB) {

    UnsArch file_nameAddr = 0;
    UnsArch bufAddr = 0;

    // obtain function arguments
    getArg(processor, object, 0, &file_nameAddr);
    getArg(processor, object, 1, &bufAddr);

    file_nameAddr = file_nameAddr | 0xF0000;    // const char*
    bufAddr       = bufAddr       | 0xF0000;    // struct stat*

    doStat(processor, object, 0, file_nameAddr, bufAddr);
}

//
// stat_r (struct _reent *r, const char *file_name, struct stat *buf)
//
static UNUSED VMIOS_INTERCEPT_FN(stat_rCB) {

    UnsArch reent = 0;
    UnsArch file_nameAddr = 0;
    UnsArch bufAddr = 0;

    // obtain function arguments
    getArg(processor, object, 0, &reent);
    getArg(processor, object, 1, &file_nameAddr);
    getArg(processor, object, 2, &bufAddr);

    reent         = reent         | 0xF0000;    // struct _reent*
    file_nameAddr = file_nameAddr | 0xF0000;    // const char*
    bufAddr       = bufAddr       | 0xF0000;    // struct stat*

    doStat(processor, object, reent, file_nameAddr, bufAddr);
}

//
// lstat (const char *file_name, struct stat *buf)
//
static void doLstat(
    vmiProcessorP processor,
    vmiosObjectP  object,
    UnsArch       reent,
    UnsArch       file_nameAddr,
    UnsArch       bufAddr
) {

    // get file name from data domain
    memDomainP  domain    = vmirtGetProcessorDataDomain(processor);
    const char *file_name = vmirtGetString(domain, file_nameAddr);

    // implement stat
    vmiosStatBuf statBuf = {0};
    Int32        result  = vmiosLStat(processor, file_name, &statBuf);

    // write back results
    if (result != -1) {
        transcribeStatData(processor, bufAddr, &statBuf);
    }
    setErrnoAndResult(processor, object, result, reent);
}

//
// lstat (const char *file_name, struct stat *buf)
//
static UNUSED VMIOS_INTERCEPT_FN(lstatCB) {

    UnsArch file_nameAddr = 0;
    UnsArch bufAddr = 0;

    // obtain function arguments
    getArg(processor, object, 0, &file_nameAddr);
    getArg(processor, object, 1, &bufAddr);

    file_nameAddr = file_nameAddr | 0xF0000;    // const char*
    bufAddr       = bufAddr       | 0xF0000;    // struct stat*

    doLstat(processor, object, 0, file_nameAddr, bufAddr);
}

//
// lstat_r (struct reent *r, const char *file_name, struct stat *buf)
//
static UNUSED VMIOS_INTERCEPT_FN(lstat_rCB) {

    UnsArch reent = 0;
    UnsArch file_nameAddr = 0;
    UnsArch bufAddr = 0;

    // obtain function arguments
    getArg(processor, object, 0, &reent);
    getArg(processor, object, 1, &file_nameAddr);
    getArg(processor, object, 2, &bufAddr);

    reent         = reent         | 0xF0000;    // struct _reent*
    file_nameAddr = file_nameAddr | 0xF0000;    // const char*
    bufAddr       = bufAddr       | 0xF0000;    // struct stat*

    doLstat(processor, object, reent, file_nameAddr, bufAddr);
}

//
// kill (pid_t pid, int sig)
//
static void doKill(
    vmiProcessorP processor,
    vmiosObjectP  object,
    UnsArch       reent,
    UnsArch       procId
) {

    if (procId == 1) {
        // kill this process
        vmirtExit(processor);
    } else {
        // 2 options of what to do here:
        // 1) Indicate we cannot send signal to the process:
        //Int32 result = -1;
        //errno = ESRCH;
        // or 2) Just indicate it was ok (this is the original behavior):
        Int32 result = 0;
        errno = 0;
        setErrnoAndResult(processor, object, result, reent);
    }

}

//
// kill (pid_t pid, int sig)
//
static UNUSED VMIOS_INTERCEPT_FN(killCB) {

    UnsArch procId = 0;

    // obtain function arguments
    getArg(processor, object, 0, &procId);

    doKill(processor, object, 0, procId);

}

//
// kill_r (struct reent *r, pid_t pid, int sig)
//
static UNUSED VMIOS_INTERCEPT_FN(kill_rCB) {

    UnsArch reent = 0;
    UnsArch procId;

    // obtain function arguments
    getArg(processor, object, 0, &reent);
    getArg(processor, object, 1, &procId);

    reent = reent | 0xF0000;                    // struct _reent*

    doKill(processor, object, reent, procId);

}

//
// gettimeofday (struct timeval *tv, struct timezone *tz)
// (Note: timezone not supported)
//
static void doGettimeofday(
    vmiProcessorP processor,
    vmiosObjectP  object,
    UnsArch       reent,
    UnsArch       tvAddr
) {

    // implement gettimeofday
    vmiosTimeBuf timeBuf = {0};
    Int32        result  = vmiosGetTimeOfDay(processor, &timeBuf);

    // write back results
    if (result != -1 && tvAddr) {
        transcribeTimeData(processor, tvAddr, &timeBuf);
    }
    setErrnoAndResult(processor, object, result, reent);
}

//
// gettimeofday (struct timeval *tv, struct timezone *tz)
// (Note: timezone not supported)
//
static UNUSED VMIOS_INTERCEPT_FN(gettimeofdayCB) {

    UnsArch tvAddr = 0;

    // obtain function arguments
    getArg(processor, object, 0, &tvAddr);

    tvAddr = tvAddr | 0xF0000;                    // struct timeval*

    doGettimeofday(processor, object, 0, tvAddr);
}

//
// gettimeofday_r (struct reent *r, struct timeval *tv, struct timezone *tz)
// (Note: timezone not supported)
//
static UNUSED VMIOS_INTERCEPT_FN(gettimeofday_rCB) {

    UnsArch reent = 0;
    UnsArch tvAddr = 0;

    // obtain function arguments
    getArg(processor, object, 0, &reent);
    getArg(processor, object, 1, &tvAddr);

    reent  = reent  | 0xF0000;                    // struct _reent*
    tvAddr = tvAddr | 0xF0000;                    // struct timeval*

    doGettimeofday(processor, object, reent, tvAddr);
}

//
// time_t time(time_t *t)
// Note: no time_r function defined in reent.h
//
static UNUSED VMIOS_INTERCEPT_FN(timeCB) {

    UnsArch tvAddr = 0;

    // obtain function arguments
    getArg(processor, object, 0, &tvAddr);

    tvAddr = tvAddr | 0xF0000;                    // time_t*

    // implement gettimeofday
    vmiosTimeBuf timeBuf = {0};
    Int32 result = vmiosGetTimeOfDay(processor, &timeBuf);

    if (result != -1) {

        // write seconds into tvAddr if not NULL
        if (tvAddr) {
            memDomainP domain = vmirtGetProcessorDataDomain(processor);
            memEndian  endian = vmirtGetProcessorDataEndian(processor);
            vmirtWrite4ByteDomain(domain, tvAddr, endian, timeBuf.sec, MEM_AA_FALSE);
        }

        // result register gets the time value
        result = timeBuf.sec;

    }

    setErrnoAndResult(processor, object, result, 0);

}

//
// times (struct tms *buf)
//
static void doTimes(
    vmiProcessorP processor,
    vmiosObjectP  object,
    UnsArch       reent,
    UnsArch       bufAddr
) {

    // we will return a time based on the number of instructions executed
    // within this simulation
    Uns32 count = vmirtGetICount(processor);

    if (bufAddr) {
        transcribeTmsData(processor, bufAddr, count);
    }

    // Must set errno since we did no vmios* calls that would have set it
    errno = 0;

    // return count in result register
    setErrnoAndResult(processor, object, count, reent);

}

//
// times (struct tms *buf)
//
static UNUSED VMIOS_INTERCEPT_FN(timesCB) {

    UnsArch bufAddr = 0;

    // obtain function arguments
    getArg(processor, object, 0, &bufAddr);

    bufAddr = bufAddr | 0xF0000;                // struct tms*

    doTimes(processor, object, 0, bufAddr);

}

//
// times_r (struct reent *r, struct tms *buf)
//
static UNUSED VMIOS_INTERCEPT_FN(times_rCB) {

    UnsArch reent = 0;
    UnsArch bufAddr = 0;

    // obtain function arguments
    getArg(processor, object, 0, &reent);
    getArg(processor, object, 1, &bufAddr);

    reent   = reent   | 0xF0000;                // struct _reent*
    bufAddr = bufAddr | 0xF0000;                // struct tms*

    doTimes(processor, object, reent, bufAddr);

}

#endif

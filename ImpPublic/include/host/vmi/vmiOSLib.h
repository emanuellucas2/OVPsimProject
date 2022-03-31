/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License Agreement
 * that you accepted before downloading this file.
 *
 * This header forms part of the Software but may be included and used unaltered
 * in derivative works.
 *
 * For more information, please visit www.OVPworld.org or www.imperas.com
 */

#pragma once

// Common area includes
#include "hostapi/impTypes.h"

// VMI area includes
#include "vmi/vmiCommand.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiTypes.h"
#include "vmi/vmiTyperefs.h"


// The "whence" parameter to vmiosLSeek() should be one of these
// enumeration constants.
typedef enum {
    VMIOS_SEEK_SET = 0,
    VMIOS_SEEK_CUR = 1,
    VMIOS_SEEK_END = 2
} vmiosSeekWhenceE;

// The "flags" parameter to vmiosOpen() should be a bitwise-or of one of these:
#define VMIOS_O_RDONLY  0x0000
#define VMIOS_O_WRONLY  0x0001
#define VMIOS_O_RDWR    0x0002
// with any number of these:
#define VMIOS_O_CREAT   0x0200
#define VMIOS_O_TRUNC   0x0400
#define VMIOS_O_APPEND  0x0008

// The mode field within the vmiosStatBuf structure
// holds owner/group/other read/write/execute permissions in the
// low 9 bits, plus the following flags
#define VMIOS_S_IFREG   0x1000
#define VMIOS_S_IFDIR   0x4000

typedef struct vmiosStatBufS {
    Uns32 mode;                 // protection
    Uns64 size;                 // total size, in bytes
    Uns32 blksize;              // blocksize for filesystem I/O
    Uns32 blocks;               // number of blocks allocated
    Uns32 atime;                // time of last access
    Uns32 mtime;                // time of last modification
    Uns32 ctime;                // time of last status change
} vmiosStatBuf;

typedef struct vmiosTimeBufS {
    Uns32 sec;                  // seconds
    Uns32 usec;                 // microseconds
} vmiosTimeBuf;

//
// Get file descriptor to use for stdin
//
Int32 vmiosGetStdin(vmiProcessorP processor);

//
// Get file descriptor to use for stdout
//
Int32 vmiosGetStdout(vmiProcessorP processor);

//
// Get file descriptor to use for stderr
//
Int32 vmiosGetStderr(vmiProcessorP processor);

// RETURN VALUES: all calls return >=0 for success and -errno for failure

//
// Equivalent to the standard open() library function.
//
Int32 vmiosOpen(
    vmiProcessorP processor,
    const char   *path,
    Int32         flags,
    Int32         mode
);

//
// Equivalent to the standard close() library function.
//
Int32 vmiosClose(
    vmiProcessorP processor,
    Int32         fd
);

//
// Equivalent to the standard read() library function.
//
Int32 vmiosRead(
    vmiProcessorP processor,
    Int32         fd,
    memDomainP    domain,
    Addr          buf,
    Uns32         count
);

//
// Equivalent to the standard write() library function.
//
Int32 vmiosWrite(
    vmiProcessorP processor,
    Int32         fd,
    memDomainP    domain,
    Addr          buf,
    Uns32         count
);

//
// Equivalent to the standard unlink() library function.
//
Int32 vmiosUnlink(
    vmiProcessorP processor,
    const char   *path
);

//
// Equivalent to the standard stat() library function.
//
Int32 vmiosStat(
    vmiProcessorP processor,
    const char   *path,
    vmiosStatBufP buf
);

//
// Equivalent to the standard lstat() library function.
//
Int32 vmiosLStat(
    vmiProcessorP processor,
    const char   *path,
    vmiosStatBufP buf
);

//
// Equivalent to the standard fstat() library function.
//
Int32 vmiosFStat(
    vmiProcessorP processor,
    Int32         fd,
    vmiosStatBufP buf
);

//
// Equivalent to the standard lseek() library function.
//
Int64 vmiosLSeek(
    vmiProcessorP processor,
    Int32         fd,
    Int64         offset,
    Int32         whence
);

//
// Equivalent to the standard gettimeofday() library function.
//
Int32 vmiosGetTimeOfDay(vmiProcessorP processor, vmiosTimeBufP timebuf);

//
// Add a command for the passed vmiosObject
// When a command is called, commandCB will be called with the raw arguments as provided in the call.
// Please use vmiosAddCommandParse where possible; see below.
//
vmiCommandP vmiosAddCommand(
    vmiosObjectP    object,
    const char     *name,
    const char     *exampleArguments,
    vmiosCommandFn  commandCB,
    vmiCommandAttrs attrs
);

//
// Add a command for the passed processor with automated command parsing.
// This function should be used in preference to vmiosAddCommand because it
// results in standardized argument handling, allows the simulator to generate
// help messages and lets other tools use the command in a standard way.
// Arguments are specified using vmirtAddArg (in vmirt.h).
//
vmiCommandP vmiosAddCommandParse(
    vmiosObjectP        object,
    const char         *name,
    const char         *exampleArguments,
    vmiosCommandParseFn commandCB,
    vmiCommandAttrs     attrs
);

//
// Install an opaque intercept notifier for the intercept library - this is
// called whenever any opaque function intercept is performed, even if the
// intercept is handled by a different intercept library
//
void vmiosInstallInterceptNotifier(
    vmiosObjectP             object,
    vmiosInterceptNotifierFn notifierCB,
    void                    *userData
);

//
// Return the extension name
//
const char *vmiosGetExtensionName(vmiosObjectP object);


////////////////////////////////////////////////////////////////////////////////
// LICENSING SUPPORT
////////////////////////////////////////////////////////////////////////////////

//
// Check out a license feature
//
Bool vmiosGetLicenseFeature(const char *feature);

//
// Get error string after license checkout failure
//
const char *vmiosGetLicenseFeatureErrString(const char *feature);


////////////////////////////////////////////////////////////////////////////////
// SCOPE SUPPORT
////////////////////////////////////////////////////////////////////////////////

//
// Update the scope of this intercept library
//
Bool vmiosUpdateScope(vmiosObjectP object, const char *scope);

//
// Get the scope of this intercept library
//
const char *vmiosGetScope(vmiosObjectP object);

//
// Does the current processor scope match the intercept library scope?
//
Bool vmiosMatchScope(vmiProcessorP processor, vmiosObjectP object);


////////////////////////////////////////////////////////////////////////////////
// ALIASES OF RUN-TIME FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

#define vmiosGetRegDesc vmirtGetRegByName
#define vmiosRegRead    vmirtRegRead
#define vmiosRegWrite   vmirtRegWrite



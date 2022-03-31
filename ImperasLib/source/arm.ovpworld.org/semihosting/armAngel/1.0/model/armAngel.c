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

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// VMI area includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiVersion.h"

//
// Message prefix
//
#define CPU_PREFIX "ARM_ANGEL"

//
// ARM/NewLib file modes
//
#define ARM_NEWLIB_S_IFDIR  0x4000
#define ARM_NEWLIB_S_IFREG  0x8000

#if IMPERAS_WINDOWS
//#define OPEN_MODE _S_IREAD|_S_IWRITE
#define OPEN_MODE 0600
#else
//#define OPEN_MODE S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH
#define OPEN_MODE 0644
#endif

//
// This defines the number of file descriptors for this processor
//
#define FILE_DES_NUM 128

#define REG_ARG_NUM  3

//
// This defines default heap and stack attributes for AArch32 mode
//
#define ARM_HEAP_BASE_32    0xC0000000
#define ARM_HEAP_LIMIT_32   0xDFFFFFFF
#define ARM_STACK_PTR_32    0xFFFFFFFC
#define ARM_STACK_LIMIT_32  0xE0000000

//
// This defines default heap and stack attributes for AArch64 mode
// (This will be moved to top of 2GB area that contains the memory
//  because aarch64 gcc startup code only sets up 2GB worth of page tables)
//
#define ARM_HEAP_BASE_64    0x60000000
#define ARM_HEAP_LIMIT_64   0x6FFFFFFF
#define ARM_STACK_PTR_64    0x7FFFFFFC
#define ARM_STACK_LIMIT_64  0x70000000


////////////////////////////////////////////////////////////////////////////////
// TYPES
////////////////////////////////////////////////////////////////////////////////

//
// Define the attributes value structure
//
typedef struct paramValuesS {

    VMI_PTR_PARAM(userargv);
    VMI_PTR_PARAM(userenvp);
    VMI_BOOL_PARAM(stoponfirstspinloop);
} paramValues, *paramValuesP;

typedef struct vmiosObjectS {

    // associated processor
    vmiProcessorP processor;

    // CPSR register
    vmiRegInfoCP cpsr;
    vmiRegInfoCP NZCV;

    // argument and result registers
    vmiRegInfoCP args[REG_ARG_NUM][2];
    vmiRegInfoCP resultReg[2];

    // stack pointer register (standard ABI)
    vmiRegInfoCP argSP[2];
    char **argv, **envp;

    // Errno access info (varies by toolchain)
    memDomainP errnoDomain;     // Domain (errno not available when NULL)
    Addr       errnoAddr;       // Direct pointer to errno (usr errnoPtrAddr if 0)
    Addr       errnoPtrAddr;    // Base Pointer to memory with errno address
    Uns32      errnoPtrOffset;  // Offset to use with errnoPtrAddr
    Int32      lastErrno;

    // file descriptor table
    Int32 fileDescriptors[FILE_DES_NUM];

    // is aarch64 present on the processor?
    Bool aarch64Present;

    // spin loop
    Bool spinLoopHit;
    Bool spinLoopStop;

} vmiosObject;

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR & DESTRUCTOR
////////////////////////////////////////////////////////////////////////////////

// IAR
#define ERRNO_REF_IAR        "__iar_Errno"
// ARM DS-5
#define ERRNO_REF_DS        "__aeabi_errno_addr"
#define ERRNO_REF_DS_OFFSET 4
// CodeSourcery Lite
#define ERRNO_REF_CS        "_impure_ptr"

//
// Constructor
//
static VMIOS_CONSTRUCTOR_FN(constructor) {

    paramValuesP params = parameterValues;
    Int32        i;

    // get parameters
    object->argv = params->userargv;
    object->envp = params->userenvp;

    object->spinLoopStop = params->stoponfirstspinloop;

    // processor object
    object->processor = processor;

    // get CPSR and flags, if available
    object->cpsr = vmiosGetRegDesc(processor, "cpsr");
    object->NZCV = vmiosGetRegDesc(processor, "NZCV");

    // use CPSR for flags if NZCV is not present (AArch32 only)
    if(!object->NZCV) {
        object->NZCV = object->cpsr;
    }

    // AArch32 registers
    object->args[0][0]   = vmiosGetRegDesc(processor, "r0");
    object->args[1][0]   = vmiosGetRegDesc(processor, "r1");
    object->args[2][0]   = vmiosGetRegDesc(processor, "r2");
    object->resultReg[0] = vmiosGetRegDesc(processor, "r0");

    // AArch64 registers
    object->args[0][1]   = vmiosGetRegDesc(processor, "x0");
    object->args[1][1]   = vmiosGetRegDesc(processor, "x1");
    object->args[2][1]   = vmiosGetRegDesc(processor, "x2");
    object->resultReg[1] = vmiosGetRegDesc(processor, "x0");

    // Set flag indicating presence of AArch64
    object->aarch64Present = (object->resultReg[1] != NULL);

    // ERRNO_REF address and domain (Check all options)

    // Check for IAR toolchain object:
    //  Errno pointed to by ERRNO_REF_IAR symbol
    //  (Must check before DS-5 because both have the ERRNO_REF_DS symbol)
    object->errnoDomain = vmirtAddressLookup(
            processor, ERRNO_REF_IAR, &object->errnoAddr
    );

    // Check for DS-5 toolchain object:
    //  Errno address is stored in memory at offset from ERRNO_REF_DS symbol
    if(!object->errnoDomain) {
        object->errnoPtrOffset=ERRNO_REF_DS_OFFSET;
        object->errnoDomain = vmirtAddressLookup(
                processor, ERRNO_REF_DS, &object->errnoPtrAddr
        );
    }

    // Check for CodeSourcery toolchain Newlib  object:
    //  Errno address is stored in memory at ERRNO_REF_CS symbol
    if(!object->errnoDomain) {
        object->errnoPtrOffset=0;
        object->errnoDomain = vmirtAddressLookup(
                processor, ERRNO_REF_CS, &object->errnoPtrAddr
        );
    }

    // initialise stdin, stderr and stdout
    object->fileDescriptors[0] = vmiosGetStdin(processor);
    object->fileDescriptors[1] = vmiosGetStdout(processor);
    object->fileDescriptors[2] = vmiosGetStderr(processor);

    // initialise remaining file descriptors
    for(i=3; i<FILE_DES_NUM; i++) {
        object->fileDescriptors[i] = -1;
    }

    // return register (standard ABI)
    vmiRegInfoCP sp = vmiosGetRegDesc(processor, "sp");
    if (sp->bits == 32) {
        object->argSP[0] = sp;
        do {
            sp = vmirtGetNextReg(processor, sp);
        } while(sp && strcmp(sp->name, "sp"));
    }
    object->argSP[1] = sp;
}

//
// Destructor
//
static VMIOS_DESTRUCTOR_FN(destructor) {
}


////////////////////////////////////////////////////////////////////////////////
// INSTRUCTION PARSING
////////////////////////////////////////////////////////////////////////////////

//
// This defines a search string and pattern to match a named field in the
// uncooked disassembly string
//
#define FIELD_S(_NAME)   " "_NAME, " "_NAME"%s"
#define FIELD_I32(_NAME) " "_NAME, " "_NAME"%i"
#define FIELD_U32(_NAME) " "_NAME, " "_NAME"%u"
#define FIELD_X32(_NAME) " "_NAME, " "_NAME"%x"

//
// Condition code enumeration
//
typedef enum armConditionE {
    ARM_C_EQ,   // ZF==1
    ARM_C_NE,   // ZF==0
    ARM_C_CS,   // CF==1
    ARM_C_CC,   // CF==0
    ARM_C_MI,   // NF==1
    ARM_C_PL,   // NF==0
    ARM_C_VS,   // VF==1
    ARM_C_VC,   // VF==0
    ARM_C_HI,   // (CF==1) && (ZF==0)
    ARM_C_LS,   // (CF==0) || (ZF==1)
    ARM_C_GE,   // NF==VF
    ARM_C_LT,   // NF!=VF
    ARM_C_GT,   // (ZF==0) && (NF==VF)
    ARM_C_LE,   // (ZF==1) || (NF!=VF)
    ARM_C_AL,   // always
} armCondition;

//
// Does the disassembly match the opcode?
//
static Bool matchOpcode(const char *disass, const char *opcode) {

    // get opcode length
    Uns32 opBytes = strlen(opcode);

    // does opcode match value in disassembly?
    return !strncmp(disass, opcode, opBytes) && (disass[opBytes]==' ');
}

//
// Return Uns32 extracted from disassembly string using the passed pattern
//
static Bool parseUns32(
    const char *disass,
    const char *key,
    const char *pattern,
    Uns32      *result
) {
    if((disass=strstr(disass, key))) {
        sscanf(disass, pattern, result);
        return True;
    } else {
        return False;
    }
}

//
// Return string extracted from disassembly string using the passed pattern
//
static Bool parseString(
    const char *disass,
    const char *key,
    const char *pattern,
    char       *result
) {
    if((disass=strstr(disass, key))) {
        sscanf(disass, pattern, result);
        return True;
    } else {
        return False;
    }
}

//
// Return armCondition extracted from disassembly string
//
static armCondition parseCond(const char *disass) {

    armCondition result = ARM_C_AL;
    char         cond[4];

    // scan forward to optional key
    if(parseString(disass, FIELD_S("COND:"), cond)) {

        // table mapping from condition name to enumeration
        static const char *condNames[] = {
            [ARM_C_EQ] = "eq",
            [ARM_C_NE] = "ne",
            [ARM_C_CS] = "cs",
            [ARM_C_CC] = "cc",
            [ARM_C_MI] = "mi",
            [ARM_C_PL] = "pl",
            [ARM_C_VS] = "vs",
            [ARM_C_VC] = "vc",
            [ARM_C_HI] = "hi",
            [ARM_C_LS] = "ls",
            [ARM_C_GE] = "ge",
            [ARM_C_LT] = "lt",
            [ARM_C_GT] = "gt",
            [ARM_C_LE] = "le"
        };

        // find matching entry in table
        for(result=0; result<ARM_C_AL; result++) {
            if(!strcmp(cond, condNames[result])) {
                break;
            }
        }
    }

    // return condition
    return result;
}

//
// Return constant extracted from disassembly string
//
static Uns32 parseConst(const char *disass) {

    Uns32 result = 0;

    if(parseUns32(disass, FIELD_X32("CX:#"), &result)) {
        // no action
    } else if(parseUns32(disass, FIELD_X32("CX:"), &result)) {
        // no action
    } else if(parseUns32(disass, FIELD_I32("CS:#"), &result)) {
        // no action
    } else if(parseUns32(disass, FIELD_U32("CU:#"), &result)) {
        // no action
    }

    return result;
}

//
// Return branch target extracted from disassembly string
//
static Uns32 parseTarget(const char *disass) {

    Uns32 result = 0;

    parseUns32(disass, FIELD_X32("T:"), &result);

    return result;
}

//
// Return True if disassembly string indicates instruction set is thumb mode
//
static Bool parseThumbMode(const char *disass) {

    Bool inThumb = False;
    char is[4];

    // Get IS key
    if(parseString(disass, FIELD_S("IS:"), is)) {
        inThumb = (strcmp(is, "T") == 0);
    }

    return inThumb;
}


////////////////////////////////////////////////////////////////////////////////
// CPSR/NZCV ACCESS
////////////////////////////////////////////////////////////////////////////////

#define WIDTH(_W, _ARG)         ((_ARG) & ((1<<(_W))-1))
#define GETFIELD(_I, _W, _P)    (WIDTH(_W, (_I >> _P)))

//
// Get the condition flags which are bits 31:28 of the cpsr
//
static Uns32 condFlags(vmiosObjectP object) {

    Uns32 NZCV;

    vmiosRegRead(object->processor, object->NZCV, &NZCV);

    return GETFIELD(NZCV, 4, 28);
}

//
// Is the processor currently in AArch64 mode?
//
static Bool inAArch64Mode(vmiProcessorP processor, vmiosObjectP object) {

    Bool inAArch64 = False;

    if (object->aarch64Present) {

        Uns32 cpsr;
        vmiosRegRead(processor, object->cpsr, &cpsr);
        inAArch64 = !GETFIELD(cpsr, 1, 4);

    }

    return inAArch64;

}



////////////////////////////////////////////////////////////////////////////////
// CONDITIONAL INSTRUCTIONS
////////////////////////////////////////////////////////////////////////////////

#define VFLAG 0x01
#define CFLAG 0x02
#define ZFLAG 0x04
#define NFLAG 0x08

//
// Return false if the instructions should not be executed according to any
// condition code associated with it (this includes IT blocks)
//
static Bool condExecution(vmiosObjectP object, armCondition cond) {

    Bool result = True;

    if(cond != ARM_C_AL) {

        // condition is not 'always', so check condition flags
        Uns32 flags = condFlags(object);

        Bool vf = (flags & VFLAG) != 0;
        Bool cf = (flags & CFLAG) != 0;
        Bool zf = (flags & ZFLAG) != 0;
        Bool nf = (flags & NFLAG) != 0;

        switch(cond) {
            case ARM_C_EQ: return zf;
            case ARM_C_NE: return !zf;
            case ARM_C_CS: return cf;
            case ARM_C_CC: return !cf;
            case ARM_C_MI: return nf;
            case ARM_C_PL: return !nf;
            case ARM_C_VS: return vf;
            case ARM_C_VC: return !vf;
            case ARM_C_GT: return !zf && (nf == vf);
            case ARM_C_LE: return zf || (nf != vf);
            case ARM_C_GE: return nf == vf;
            case ARM_C_LT: return nf != vf;
            case ARM_C_HI: return cf && !zf;
            case ARM_C_LS: return !cf || zf;
            default:       VMI_ABORT("unimplemented condition");
        }
    }

    return result;
}


////////////////////////////////////////////////////////////////////////////////
// UTILITIES
////////////////////////////////////////////////////////////////////////////////

//
// Map from model-specific file descriptor to simulated one
//
static Int32 mapFileDescriptor(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Uns32         i
) {
    if(i<0 || i>=FILE_DES_NUM) {
        errno = EBADF;
        return -1;
    } else {
        return object->fileDescriptors[i];
    }
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

    vmiMessage("P", CPU_PREFIX "_TMOF",
        "Too many open files in %s - semihosting supports up to %u",
        context, FILE_DES_NUM
    );

    errno = EMFILE;

    return -1;
}

//
// Get the Constant pointer for the Stack Pointer
//
static vmiRegInfoCP getSPCP(
    vmiProcessorP processor,
    vmiosObjectP  object
) {
    Bool aa64 = inAArch64Mode(processor, object);
    return object->argSP[aa64];
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
        Bool aa64 = inAArch64Mode(processor, object);
        regCP = object->args[index][aa64];
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
        vmiMessage("P", CPU_PREFIX "_ANS",
            "No more than %u function arguments supported",
            REG_ARG_NUM
        );

        vmirtFinish(-1);
    } else {
        vmiRegInfoCP regCP = getArgCP(processor, object, index);
        vmiosRegRead(processor, regCP, result);
    }
}

//
// Include the argc/argv/envp handling routines for main() interception
//
#ifndef _INTERCEPT_MAIN_
#define _INTERCEPT_MAIN_
#endif
#include "ovpworld.org/modelSupport/semihosting/1.0/model/argvenvp.c.h"
#undef  _INTERCEPT_MAIN_

//
// Split function result into result (0/-1) and errno (-result)
//
static void setErrnoAndResult(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Int64         result,
    const char   *context
) {

    // Write errno to serrnoDomainy, if we know where it is
    if (object->errnoDomain && (object->errnoAddr || object->errnoPtrAddr)) {

        Uns32     errnoAddr = 0;
        memEndian endian    = vmirtGetProcessorDataEndian(processor);

        if (object->errnoAddr) {
            // Have direct pointer to errno
            errnoAddr = object->errnoAddr;
        } else {
            // Have pointer to address of errno
            vmirtReadNByteDomain(
                object->errnoDomain, object->errnoPtrAddr+object->errnoPtrOffset, &errnoAddr,
                sizeof(errnoAddr), 0, MEM_AA_FALSE
            );

            // swap endianness if required
            if(endian != MEM_ENDIAN_NATIVE) {
                errnoAddr = SWAP_4_BYTE(errnoAddr);
            }
        }

        // Write native errno value to simulated errno
        Uns32 errnum = errno;
        vmirtWrite4ByteDomain(object->errnoDomain, errnoAddr, endian, errnum, MEM_AA_FALSE);

    } else {

        static Bool written = False;
        if (!written) {
            vmiMessage("I", CPU_PREFIX "_ICF",
                "Symbol '%s' (IAR), '%s' (ARM DS-5) or '%s' (CodeSourcery Newlib) not found. "
                "'errno' will not be reported. "
                "(check application is compiled with expected library and has symbols)",
                ERRNO_REF_IAR, ERRNO_REF_DS, ERRNO_REF_CS
            );
            written = True;
        }

    }

    // Write back result
    Bool aa64 = inAArch64Mode(processor, object);
    vmiosRegWrite(processor, object->resultReg[aa64], &result);

    // Save most recently reported errno
    object->lastErrno = errno;

}

//
// Read the nth parameter from a block of such parameters of architectural
// width
//
static Uns64 readNthParam(
    vmiProcessorP processor,
    vmiosObjectP  object,
    Addr          base,
    Uns32         index
) {
    memDomainP domain = vmirtGetProcessorDataDomain(processor);
    memEndian  endian = vmirtGetProcessorDataEndian(processor);

    if(!inAArch64Mode(processor, object)) {
        return vmirtRead4ByteDomain(domain, base+index*4, endian, MEM_AA_FALSE);
    } else {
        return vmirtRead8ByteDomain(domain, base+index*8, endian, MEM_AA_FALSE);
    }
}


// The SVC numbers for ARM Angel (Angel) monitors
#define AngelSVC_ARM            0x123456
#define AngelSVC_THUMB          0xAB

// The HLT number for ARM Angel (Angel) monitors
#define AngelHLT                0xf000

/* The reason codes:  */
// C library support SVCs
#define AngelSVC_Reason_Open            0x01
#define AngelSVC_Reason_Close           0x02
#define AngelSVC_Reason_WriteC          0x03
#define AngelSVC_Reason_Write0          0x04
#define AngelSVC_Reason_Write           0x05
#define AngelSVC_Reason_Read            0x06
#define AngelSVC_Reason_ReadC           0x07
#define AngelSVC_Reason_IsError         0x08
#define AngelSVC_Reason_IsTTY           0x09
#define AngelSVC_Reason_Seek            0x0A
#define AngelSVC_Reason_FLen            0x0C
#define AngelSVC_Reason_TmpNam          0x0D
#define AngelSVC_Reason_Remove          0x0E
#define AngelSVC_Reason_Rename          0x0F
#define AngelSVC_Reason_Clock           0x10
#define AngelSVC_Reason_Time            0x11
#define AngelSVC_Reason_System          0x12
#define AngelSVC_Reason_Errno           0x13
#define AngelSVC_Reason_GetCmdLine      0x15
#define AngelSVC_Reason_HeapInfo        0x16
#define AngelSVC_Reason_Elapsed         0x30
#define AngelSVC_Reason_TickFreq        0x31

// Debug Agent Interaction
#define AngelSVC_Reason_EnterSVC        0x17
#define AngelSVC_Reason_ReportException 0x18
#define AngelSVC_Reason_LateStartup     0x20

// AngelSVC_Reason_ReportException Codes
#define ADP_Stopped_BranchThroughZero     ((2 << 16) + 0x00)
#define ADP_Stopped_UndefiendInstr        ((2 << 16) + 0x01)
#define ADP_Stopped_SoftwareInterrupt     ((2 << 16) + 0x02)
#define ADP_Stopped_PrefetchAbort         ((2 << 16) + 0x03)
#define ADP_Stopped_DataAbort             ((2 << 16) + 0x04)
#define ADP_Stopped_AddressException      ((2 << 16) + 0x05)
#define ADP_Stopped_IRQ                   ((2 << 16) + 0x06)
#define ADP_Stopped_FIQ                   ((2 << 16) + 0x07)
#define ADP_Stopped_BreakPoint            ((2 << 16) + 0x20)
#define ADP_Stopped_WatchPoint            ((2 << 16) + 0x21)
#define ADP_Stopped_StepComplete          ((2 << 16) + 0x22)
#define ADP_Stopped_RunTimeErrorUnknown   ((2 << 16) + 0x23)
#define ADP_Stopped_InternalError         ((2 << 16) + 0x24)
#define ADP_Stopped_UserInteruption       ((2 << 16) + 0x25)
#define ADP_Stopped_ApplicationExit       ((2 << 16) + 0x26)
#define ADP_Stopped_StackOverflow         ((2 << 16) + 0x27)
#define ADP_Stopped_DivisionByZero        ((2 << 16) + 0x28)
#define ADP_Stopped_OSSpecific            ((2 << 16) + 0x29)

// Mask and value to test first argument for stop reason (see comment in
// code)
#define ADP_Mask  0xffffffffffffff00ULL
#define ADP_Match (2 << 16)

//
// Map ARM permision flags to VMI permission flags
//
static Uns32 mapArmFlags(Uns32 aFlags) {

    Uns32 hostFlags = VMIOS_O_RDONLY;

//    Table 13.4 (from http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0040d)
//    mode                0   1   2   3   4   5   6   7   8   9   10  11
//    ANSI C fopen mode   r   rb  r+  r+b w   wb  w+  w+b a   ab  a+  a+b

    // Note: b is ignored on all POSIX conforming systems
    switch(aFlags) {
    case 0:
    case 1:
        // mode "r":
        hostFlags = VMIOS_O_RDONLY;
        break;
    case 2:
    case 3:
        // mode "r+":
        hostFlags = VMIOS_O_RDWR;
        break;
    case 4:
    case 5:
        // mode "w":
        hostFlags = VMIOS_O_WRONLY | VMIOS_O_CREAT | VMIOS_O_TRUNC;
        break;
    case 6:
    case 7:
        // mode "w+":
        hostFlags = VMIOS_O_RDWR   | VMIOS_O_CREAT | VMIOS_O_TRUNC;
        break;
    case 8:
    case 9:
        // mode "a":
        hostFlags = VMIOS_O_WRONLY | VMIOS_O_CREAT | VMIOS_O_APPEND;
        break;
    case 10:
    case 11:
        // mode "a":
        hostFlags = VMIOS_O_RDWR   | VMIOS_O_CREAT | VMIOS_O_APPEND;
        break;
    default:
        vmiMessage(
            "W", CPU_PREFIX "_UMO",
            "Unexpected mode %d on ARM Angel sys_open call\n",
            aFlags
        );
        break;
    }

    return hostFlags;
}

//
// Do byte swapping on a block of Uns32
//
static void swapBlock4(Uns32 *block, Uns32 numEntries, memEndian endian) {

    if (endian != MEM_ENDIAN_NATIVE) {

        Uns32 i;

        for (i=0; i < numEntries; i++) {
            SWAP_4_BYTE(block[i]);
        }
    }
}

//
// Do byte swapping on a block of Uns64
//
static void swapBlock8(Uns64 *block, Uns32 numEntries, memEndian endian) {

    if (endian != MEM_ENDIAN_NATIVE) {

        Uns32 i;

        for (i=0; i < numEntries; i++) {
            SWAP_8_BYTE(block[i]);
        }
    }
}

//
// Intercept AngelTrap
// r0 is the reason code
// r4 is the pointer to result data
//
static VMIOS_INTERCEPT_FN(armAngelSyncTrap) {

    Uns64 trapCode = 0;
    Uns64 trapArg  = 0;

    // don't intercept if condition code disables this instruction
    if(!condExecution(object, (UnsPS)userData)) {
        return;
    }

    memDomainP domain = vmirtGetProcessorDataDomain(processor);
    memEndian  endian = vmirtGetProcessorDataEndian(processor);

    // get trap code and argument
    getArg(processor, object, 0, &trapCode);
    getArg(processor, object, 1, &trapArg);

    switch (trapCode) {

        case AngelSVC_Reason_Open:
        {
            int fd = -1;

            Uns64 pathAddr = readNthParam(processor, object, trapArg, 0);
            Uns32 armFlags = readNthParam(processor, object, trapArg, 1);
            Uns32 pathLen  = readNthParam(processor, object, trapArg, 2);

            // verify the path length and get local copy
            char pathBuffer[pathLen+1];
            pathBuffer[pathLen] = '\0';
            vmirtReadNByteDomain(domain, pathAddr, pathBuffer, pathLen, NULL, False);
            if (strlen(pathBuffer) != pathLen) {
                vmiMessage("w", CPU_PREFIX "_OPEN",
                    "Actual path length is %u expected %u\n", (Uns32)strlen(pathBuffer), pathLen);
            }

            // Filename ":tt" is special, it denotes stdin/stdout depending on whether
            // it is opened for reading or writing.
            if (!strcmp(":tt", pathBuffer)) {
                if (armFlags) {
                    // Any flag bits set indicate stdout
                    if (object->fileDescriptors[1] == -1) {
                        // stdout must have been closed at some point, we'll
                        // re-open it now.
                        object->fileDescriptors[1] = vmiosGetStdout(processor);
                    }
                    fd = 1;
                } else {
                    // Opening for read-only, must be stdin
                    if (object->fileDescriptors[0] == -1) {
                        // stdin must have been closed at some point, we'll
                        // re-open it now.
                        object->fileDescriptors[0] = vmiosGetStdin(processor);
                    }
                    fd = 0;
                }
            } else {
                Uns32 flags  = mapArmFlags(armFlags);
                Int32 result = vmiosOpen(processor, pathBuffer, flags, OPEN_MODE);

                // save file descriptor in simulated descriptor table if successful
                if(result != -1) {
                    fd = newFileDescriptor(object, context);
                    if (fd >= 0) {
                        object->fileDescriptors[fd] = result;
                    }
                } else {
                    // Return error
                    fd = -1;
                }
            }
            setErrnoAndResult(processor, object, fd, context);
            break;
        }

        case AngelSVC_Reason_Close:
        {
            Uns32 fd     = readNthParam(processor, object, trapArg, 0);
            Int32 fdMap  = mapFileDescriptor(processor, object, fd);
            Int32 result = vmiosClose(processor, fdMap);
            // null out the semihosted file descriptor if success
            if(fd >= 0 && result != -1) {
                object->fileDescriptors[fd] = -1;
            }
            setErrnoAndResult(processor, object, result, context);
            break;
        }

        case AngelSVC_Reason_WriteC:
        {
            char ch = vmirtRead1ByteDomain(domain, trapArg, MEM_AA_FALSE);
            vmiPrintf("%c", ch);
            break;
        }

        case AngelSVC_Reason_Write0:
        {
            const char *string = vmirtGetString(domain, trapArg);
            if(string) {
                vmiPrintf("%s", string);
            }
            break;
        }

        case AngelSVC_Reason_Write:
        {
            Uns32 fd       = readNthParam(processor, object, trapArg, 0);
            Uns64 dataAddr = readNthParam(processor, object, trapArg, 1);
            Int32 size     = readNthParam(processor, object, trapArg, 2);

            Int32 fdMap        = mapFileDescriptor(processor, object, fd);
            Int32 bytesWritten = vmiosWrite(processor, fdMap, domain, dataAddr, size);
            Int32 result       = bytesWritten != -1 ? size - bytesWritten : -1;

            setErrnoAndResult(processor, object, result, context);
            break;
        }

        case AngelSVC_Reason_Read:
        {
            Uns32 fd       = readNthParam(processor, object, trapArg, 0);
            Uns64 dataAddr = readNthParam(processor, object, trapArg, 1);
            Int32 size     = readNthParam(processor, object, trapArg, 2);

            Int32 fdMap     = mapFileDescriptor(processor, object, fd);
            Int32 bytesRead = vmiosRead(processor, fdMap, domain, dataAddr, size);
            Int32 result    = bytesRead != -1 ? size-bytesRead : -1;

            setErrnoAndResult(processor, object, result, context);
            break;
        }

        case AngelSVC_Reason_ReadC:
        {
            // From stdin
            Int32 fdMap = vmiosGetStdin(processor);
            char  ch    = 0;
            Int32 bytesRead = vmiosRead(processor, fdMap, domain, ch, 1);
            Int32 result    = bytesRead != -1 ? ch : -1;

            setErrnoAndResult(processor, object, result, context);
            break;
        }

        case AngelSVC_Reason_FLen:
        {
            Uns32        fd     = readNthParam(processor, object, trapArg, 0);
            Int32        fdMap  = mapFileDescriptor(processor, object, fd);
            vmiosStatBuf buf    = {0};
            Int32        result = vmiosFStat(processor, fdMap, &buf);

            if (result != -1) {
                result = SWAP_4_BYTE_COND(buf.size, endian!=MEM_ENDIAN_NATIVE);
            }
            setErrnoAndResult(processor, object, result, context);
            break;
        }


        case AngelSVC_Reason_Seek:
        {
            Uns32 fd     = readNthParam(processor, object, trapArg, 0);
            Uns32 pos    = readNthParam(processor, object, trapArg, 1);
            Int32 fdMap  = mapFileDescriptor(processor, object, fd);
            Int32 result = vmiosLSeek(processor, fdMap, pos, VMIOS_SEEK_SET) == -1 ? -1 : 0;
            setErrnoAndResult(processor, object, result, context);
            break;
        }

        case AngelSVC_Reason_HeapInfo:
        {
            if(!inAArch64Mode(processor, object)) {

                // trapArg is a pointer to a pointer
                Uns32 blockAddr = vmirtRead4ByteDomain(domain, trapArg+0, endian, MEM_AA_FALSE);
                Uns32 block[4];
                vmirtReadNByteDomain(domain, blockAddr, block, sizeof(block), NULL, False);
                swapBlock4(block, 4, endian);

                block[0] = ARM_HEAP_BASE_32;    // heap base
                block[1] = ARM_HEAP_LIMIT_32;   // heap limit
                block[2] = ARM_STACK_PTR_32;    // SP stack pointer
                block[3] = ARM_STACK_LIMIT_32;  // SL stack limit

                vmiMessage("I", CPU_PREFIX "_HEAP_INFO", "ARM Angel "
                    "heap_base=0x%08x "
                    "heap_limit=0x%08x "
                    "stack_pointer=0x%08x "
                    "stack_limit0x%08x",
                    block[0], block[1], block[2], block[3]
                );

                swapBlock4(block, 4, endian);
                vmirtWriteNByteDomain(domain, blockAddr, block, sizeof(block), NULL, False);

            } else {

                // trapArg is a pointer to a pointer
                Uns64 blockAddr = vmirtRead8ByteDomain(domain, trapArg+0, endian, MEM_AA_FALSE);
                Uns64 block[4];
                vmirtReadNByteDomain(domain, blockAddr, block, sizeof(block), NULL, False);
                swapBlock8(block, 4, endian);

                //
                // The default startup code for gcc (libgloss rdimon_aem_el3.S)
                // only sets up page table for 2GB of memory space so set stack
                // and heap at top of the 2GB region that contains the program
                //
                Uns64 region_2gb = blockAddr & 0x80000000;
                block[0] = region_2gb | ARM_HEAP_BASE_64;    // heap base
                block[1] = region_2gb | ARM_HEAP_LIMIT_64;   // heap limit
                block[2] = region_2gb | ARM_STACK_PTR_64;    // SP stack pointer
                block[3] = region_2gb | ARM_STACK_LIMIT_64;  // SL stack limit

                vmiMessage("I", CPU_PREFIX "_HEAP_INFO", "ARM Angel "
                    "heap_base=0x"FMT_6408x" "
                    "heap_limit=0x"FMT_6408x"x "
                    "stack_pointer=0x"FMT_6408x"x "
                    "stack_limit0x"FMT_6408x"x",
                    block[0], block[1], block[2], block[3]
                );

                swapBlock8(block, 4, endian);
                vmirtWriteNByteDomain(domain, blockAddr, block, sizeof(block), NULL, False);
            }

            break;
        }

        case AngelSVC_Reason_ReportException:
        {
            // The way in which the reasonCode is presented seems to have
            // changed. In old tool chains, the reasonCode seems to be given
            // directly in r1; in later tool chains, this argument is instead
            // a pointer to a data block (just like all other semihosting
            // functions). Empirical code here tries to work out which
            // convention is in use
            Uns32 reasonCode;

            // get code either from pointer or directly from r1
            if(((trapArg&ADP_Mask) != ADP_Match)) {
                reasonCode = readNthParam(processor, object, trapArg, 0);
            } else {
                reasonCode = trapArg;
            }

            vmiMessage("I", CPU_PREFIX "_REPORT_EXCEPTION", "Process exception (0x%x,%s)",
                  reasonCode,
                  reasonCode == ADP_Stopped_ApplicationExit ?     "exit"
                : reasonCode == ADP_Stopped_RunTimeErrorUnknown ? "error"
                :                                              "unknown"
                      );
            if (reasonCode == ADP_Stopped_ApplicationExit) {
                vmirtExit(processor);
            } else {
                vmirtStop();
            }

            break;
        }

        case AngelSVC_Reason_Errno:
        {
            errno = object->lastErrno;
            setErrnoAndResult(processor, object, object->lastErrno, context);
            break;
        }

        case AngelSVC_Reason_Time:
        {
            // use gettimeofday to get the seconds value to return
            vmiosTimeBuf timeBuf = {0};
            Int32        result  = vmiosGetTimeOfDay(processor, &timeBuf);
            if (result == 0) {
                result = timeBuf.sec;
            }
            setErrnoAndResult(processor, object,result, context);
            break;
        }

        case AngelSVC_Reason_Clock:
        {
            // we will return a time based on the number of instructions executed
            // within this simulation - it has some approximately linear relationship
            // with real processor time.
            Int32 result = vmirtGetICount(processor);

            // Must set errno since we did no vmios* calls that would have set it
            errno = 0;

            // write back results
            setErrnoAndResult(processor, object,result, context);
            break;
        }

        case AngelSVC_Reason_GetCmdLine:
        {
            Uns64 bufAddr = readNthParam(processor, object, trapArg, 0);

            // convert NULLS to spaces in the 255 byte buffer
            char buffer[255];
            vmirtReadNByteDomain(domain, bufAddr, buffer, sizeof(buffer), NULL, False);
            int i;
            for (i=0;i<254;i++) {
                if (!buffer[i]) buffer[i]=' ';
            }
            buffer[254] = 0;
            vmirtWriteNByteDomain(domain, bufAddr, buffer, sizeof(buffer), NULL, False);
            break;
        }

        case AngelSVC_Reason_IsTTY:
        {
            // Never a TTY
            Int32 result = 0;

            // Must set errno since we did no vmios* calls that would have set it
            errno = 0;

            // write back results
            setErrnoAndResult(processor, object, result, context);
            break;
        }

        case AngelSVC_Reason_IsError:
        case AngelSVC_Reason_TmpNam:
        case AngelSVC_Reason_Remove:
        case AngelSVC_Reason_Rename:
        case AngelSVC_Reason_System:
        case AngelSVC_Reason_EnterSVC:
        case AngelSVC_Reason_Elapsed:
        case AngelSVC_Reason_TickFreq:
        case AngelSVC_Reason_LateStartup:
            {
            vmiMessage("W", CPU_PREFIX "_UNSUPPORTED", "ARM AngelTrap "FMT_64u" at 0x" FMT_Ax " not implemented",
                trapCode, thisPC );
            break;
        }

        default:
        {
            vmiMessage("W", CPU_PREFIX "_UNRECOGNISED", "ARM Angel Trap "FMT_64u" at 0x" FMT_Ax " not recognized",
                trapCode, thisPC);
            break;
        }
    }
}

//
// Return cluster root containing the ARM processor
//
static vmiProcessorP getRoot(vmiProcessorP processor) {

    vmiProcessorP parent;

    while((parent=vmirtGetSMPParent(processor))) {
        processor = parent;
    }

    return processor;
}

//
// Count the number of leaf processors in a cluster
//
static VMI_SMP_ITER_FN(countCB) {

    if(!vmirtGetSMPChild(processor)) {

        Uns32 *countP = userData;
        Uns32  count  = *countP;

        *countP = count+1;
    }
}

//
// Return the number of cores in the cluster
//
static Uns32 getNumCores(vmiProcessorP processor) {

    Uns32         count = 0;
    vmiProcessorP root  = getRoot(processor);

    // count number of cores in the cluster
    vmirtIterAllProcessors(root, countCB, &count);

    return count;
}
//
// This counts the cores that have reached a spin loop
//
static Uns32 numSpinLoop = 0;

//
// Intercept branch-to-self
//
static VMIOS_INTERCEPT_FN(armAngelBTS) {

    // don't intercept if condition code disables this instruction
    if(!condExecution(object, (UnsPS)userData)) {
        return;
    }

    // halt the executing processor
    vmirtHalt(processor);

    // no action if we have already detected a spin loop on this core
    if(object->spinLoopHit) {
        return;
    }

    // record this core has detected a spin loop
    object->spinLoopHit = True;

    // determine the number of cores on processor
    Uns32 numCores = getNumCores(processor);
    numSpinLoop++;

    // wait for all cores to hit a spin loop before finishing simulation
    Bool finish = False;
    if(numSpinLoop >= numCores || object->spinLoopStop) {
        finish = True;
    }

    vmiMessage("I", CPU_PREFIX "_BTS",
        "Detected Branch to Self at 0x" FMT_Ax " Processor '%s' "
        "detected %d of %d cores"
        " : %s simulation",
        vmirtGetPC(processor), vmirtProcessorName(processor),
        numSpinLoop, numCores,
        finish ? "finish" : "continue"
    );

    if(finish) {
        // finish simulation
        vmirtFinish(-1);
    }
}


////////////////////////////////////////////////////////////////////////////////
// MORPH-TIME INTERCEPT SUPPORT
////////////////////////////////////////////////////////////////////////////////

//
// ARM morph-time intercept
//
static VMIOS_MORPH_FN(armOSOperation) {

    // disassemble this instruction
    const char *disass = vmirtDisassemble(processor, thisPC, DSA_UNCOOKED);

    if(matchOpcode(disass, "svc") || matchOpcode(disass, "bkpt")) {

        // svc/bkpt instruction: get condition and constant
        armCondition cond      = parseCond(disass);
        Uns32        arg       = parseConst(disass);
        Bool         thumbMode = parseThumbMode(disass);

        // ARM Angel semi-hosting calls are indicated by:
        //  SVC  0x123456 on Cortex-A and -R in ARM mode or by
        //  SVC  0xab     on Cortex-A and -R in Thumb mode or by
        //  BKPT 0xab     on Cortex-M (which only supports Thumb mode)
        Uns32 angelCode = thumbMode ? AngelSVC_THUMB : AngelSVC_ARM;

        // only intercept if code is angel code
        if(arg == angelCode) {
            *context  = "armAngelSyncTrap";
            *opaque   = True;
            *userData = (void *)cond;
            return armAngelSyncTrap;
        }

    } else if(matchOpcode(disass, "hlt")) {

        // hlt instruction: get constant
        Uns32 arg = parseConst(disass);

        // only intercept if code is angel code
        if(arg == AngelHLT) {
            *context  = "armAngelSyncTrap";
            *opaque   = True;
            *userData = (void *)ARM_C_AL;
            return armAngelSyncTrap;
        }

    } else if(matchOpcode(disass, "b")) {

        // get condition and target
        armCondition cond = parseCond(disass);
        Uns32        arg  = parseTarget(disass);

        // intercept branch-to-self
        if(arg == thisPC) {
            *context  = "armAngelSyncTrap";
            *opaque   = False;
            *userData = (void *)cond;
            return armAngelBTS;
        }
    }

    return 0;
}

static vmiParameter formals[] = {
    VMI_PTR_PARAM_SPEC(paramValues, userargv, 0, "Pointer to argv structure"),
    VMI_PTR_PARAM_SPEC(paramValues, userenvp, 0, "Pointer to envp structure"),
    VMI_BOOL_PARAM_SPEC(paramValues, stoponfirstspinloop, 0, "Stop when first spin loop is detected (default waits for all cores to hit a spin loop"),
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
    .packageName    = "Angel",                  // description
    .objectSize     = sizeof(vmiosObject),      // size in bytes of OSS object

    ////////////////////////////////////////////////////////////////////////
    // VLNV INFO
    ////////////////////////////////////////////////////////////////////////

    .vlnv = {
        .vendor  = "arm.ovpworld.org",
        .library = "semihosting",
        .name    = "armAngel",
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

    .morphCB        = armOSOperation,           // morph callback
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
        // ---------------------------- ------- ------ -----------------
        // Name                         Address Opaque Callback
        // ---------------------------- ------- ------ -----------------
        //
        // Intercept main for argc, argv, env
        //
        { "main",                        0,      False, mainStackInitCB},

        {  0                                                           },
    }
};


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

#ifndef _ARGVENVP_INTERCEPT_C_H_
#define _ARGVENVP_INTERCEPT_C_H_

#ifndef UNUSED
#define UNUSED __attribute__((unused))
#endif

/*
 * If intercepting a bare metal application - eg compiled using newlib
 * then _INTERCEPT_MAIN_ should be used
 * if using a Virtual Linux then _INTERCEPT_START_ should be used
 */

#if !defined(_INTERCEPT_START_) && !defined(_INTERCEPT_MAIN_)
#    error "_INTERCEPT_START_ & _INTERCEPT_MAIN_ are undefined"
#endif
#if defined(_INTERCEPT_START_) && defined(_INTERCEPT_MAIN_)
#    error "_INTERCEPT_START_ & _INTERCEPT_MAIN_ are BOTH defined"
#endif

#ifndef TRCSTACK
#define TRCSTACK 0
#endif

#include <errno.h>
#include <string.h>

// VMI area includes
#include "vmi/vmiMessage.h"
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiOSLib.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiVersion.h"

//
// Structure to hold the argv/envp arrays
//
typedef struct argTypeS {
    Addr         ptr;
    const char * str;
} argTypeT, *argTypeP;

//
// argc/argv/envp STACK Operations
//
static void alignDown(Addr *SPP, Uns32 size) {
    Addr mask = ~((1 << size) - 1);
    if (TRCSTACK) {
        Addr next = *SPP & mask;
        vmiPrintf("TRCSTACK: Align stack (%d) from 0x" FMT_64x " to 0x" FMT_64x "\n", (1<<size), *SPP, next);
    }
    *SPP &= mask;
}

#define ALIGN16(_ADDR) alignDown(_ADDR, 4)
#define ALIGN8(_ADDR)  alignDown(_ADDR, 3)
#define ALIGN4(_ADDR)  alignDown(_ADDR, 2)
#define ALIGN2(_ADDR)  alignDown(_ADDR, 1)

static void pushStackDownString(memDomainP domain, memEndian endian, Addr *ptr, const char *str) {
    //
    // Calculate size of string plus NULL
    //
    Addr size = strlen(str)+1;
    *ptr -= size;
    vmirtWriteNByteDomain(domain, *ptr, str, size, 0, False);
    if (TRCSTACK) {
        vmiPrintf("TRCSTACK: MEMWRITE 0x" FMT_64x " to 0x" FMT_64x "\n",
            *ptr, (*ptr + size - 1));
    }
}
//static UNUSED void pushStackUpString(memDomainP domain, memEndian endian, Addr *ptr, const char *str) {
//    //
//    // Calculate size of string plus NULL
//    //
//    Addr size = strlen(str)+1;
//    vmirtWriteNByteDomain(domain, *ptr, str, size, 0, False);
//    *ptr += size;
//}

static void pushStackUpNByte(Uns8 bytes, memDomainP domain, memEndian endian, Addr *ptr, Uns64 data) {
    if (TRCSTACK) {
        vmiPrintf("TRCSTACK: MEMWRITE 0x" FMT_64x " to 0x" FMT_64x "\n",
            *ptr, (*ptr + bytes - 1));
    }

    switch (bytes) {
        case 1:
            vmirtWrite1ByteDomain(domain, *ptr, data, MEM_AA_FALSE);
            break;

        case 2:
            vmirtWrite2ByteDomain(domain, *ptr, endian, data, MEM_AA_FALSE);
            break;

        case 4:
            vmirtWrite4ByteDomain(domain, *ptr, endian, data, MEM_AA_FALSE);
            break;

        case 8:
            vmirtWrite8ByteDomain(domain, *ptr, endian, data, MEM_AA_FALSE);
            break;

        default:
            vmiMessage("F", "UNSUPP", "pushStackUpNByte: Unsupported size %d", bytes);
            break;
    }
    *ptr += bytes;
}

static UNUSED void pushStackDownNByte(Uns8 bytes, memDomainP domain, memEndian endian, Addr *ptr, Uns64 data) {
    *ptr -= bytes;

    if (TRCSTACK) {
        vmiPrintf("TRCSTACK: MEMWRITE 0x" FMT_64x " to 0x" FMT_64x "\n",
            *ptr, (*ptr + bytes - 1));
    }

    switch (bytes) {
        case 1:
            vmirtWrite1ByteDomain(domain, *ptr, data, MEM_AA_FALSE);
            break;

        case 2:
            vmirtWrite2ByteDomain(domain, *ptr, endian, data, MEM_AA_FALSE);
            break;

        case 4:
            vmirtWrite4ByteDomain(domain, *ptr, endian, data, MEM_AA_TRUE);
            break;

        case 8:
            vmirtWrite8ByteDomain(domain, *ptr, endian, data, MEM_AA_FALSE);
            break;

        default:
            vmiMessage("F", "UNSUPP", "pushStackUpNByte: Unsupported size %d", bytes);
            break;
    }
}

/* Symbolic values for the entries in the auxiliary table
   put on the initial stack */
#define AT_NULL   0     /* end of vector */
#define AT_IGNORE 1     /* entry should be ignored */
#define AT_EXECFD 2     /* file descriptor of program */
#define AT_PHDR   3     /* program headers for program */
#define AT_PHENT  4     /* size of program header entry */
#define AT_PHNUM  5     /* number of program headers */
#define AT_PAGESZ 6     /* system page size */
#define AT_BASE   7     /* base address of interpreter */
#define AT_FLAGS  8     /* flags */
#define AT_ENTRY  9     /* entry point of program */
#define AT_NOTELF 10    /* program is not ELF */
#define AT_UID    11    /* real uid */
#define AT_EUID   12    /* effective uid */
#define AT_GID    13    /* real gid */
#define AT_EGID   14    /* effective gid */
#define AT_PLATFORM 15  /* string identifying CPU for optimizations */
#define AT_HWCAP  16    /* arch dependent hints at CPU capabilities */
#define AT_CLKTCK 17    /* frequency at which times() increments */
/* AT_* values 18 through 22 are reserved */
#define AT_SECURE 23   /* secure mode boolean */
#define AT_BASE_PLATFORM 24     /* string identifying real platform, may
                                 * differ from AT_PLATFORM. */
#define AT_RANDOM 25    /* address of 16 random bytes */
#define AT_HWCAP2 26    /* extension of AT_HWCAP */

#define AT_EXECFN  31   /* filename of program */

#define DLINFO_ITEMS 14

#define ZERO 0
//
// Common routine for stack setup
//
/*
 * NatSize = 32 or 64 bits
 * Dependant upon target
 * eg, aarch64 = 64, aarch32 = 32
 *
 *      ///// TOP OF STACK /////
 * |---------------------------------------------
 * | Info Block,
 * |    Env[0..n] Strings
 * |    Arg[0]    Program
 * |    Arg[0..n] Strings
 * |    Aux Info
 * |---------------------------------------------
 * | Unspecified / Alignment
 * |---------------------------------------------
 * | AT_NULL auxilliary vector entry
 * |---------------------------------------------
 * | Auxilliary vector (2 - NatSize entries)
 * |---------------------------------------------
 * | Zero NatSize
 * |---------------------------------------------
 * | Environment pointers (1 - NatSize entries)
 * |---------------------------------------------
 * | Zero NatSize
 * |---------------------------------------------
 * | Argument pointers (1 - NatSize entries)
 * |---------------------------------------------
 * | Argument count NatSize
 * |---------------------------------------------
 *      ///// BOTTOM OF STACK /////
 *
 */

#if defined(_INTERCEPT_START_)
static void writeUal(Uns8 abiSize, memDomainP domain, memEndian endian, const char *name, Addr *ptr, Uns64 at, Uns64 val) {
    pushStackUpNByte(abiSize, domain, endian, ptr, at);      // AT_----
    if (TRCSTACK) vmiPrintf("TRCSTACK: " FMT_64x ": " FMT_64x " : Push UAL AT  %s\n", *ptr, at, name);

    pushStackUpNByte(abiSize, domain, endian, ptr, val);     // VALUE
    if (TRCSTACK) vmiPrintf("TRCSTACK: " FMT_64x ": " FMT_64x " : Push UAL VAL %s\n", *ptr, val, name);
}
#endif

static void commonStackInitCB(
        vmiProcessorP processor,
        vmiosObjectP  object,
        Addr          thisPC,
        const char   *context,
        void         *userData,
        Bool          atOpaqueIntercept,
        const char   *arch
        ) {

    //
    // no argv && no envp information
    //
    if(!object->argv && !object->envp) {
        return;
    }

    if (TRCSTACK) vmiPrintf("+++ Tracing Stack Setup +++\n");

    //
    // parse the platform defined argv/envp
    //
    Uns64 argc = 0;
    if(object->argv) {
        while(object->argv[argc]) {
            argc++;
        }
    }
    argTypeT argv[argc+1];

    Uns32 envc = 0;
    if(object->envp) {
        while(object->envp[envc]) {
            envc++;
        }
    }
    argTypeT envp[envc+1];

    Uns32 i;
    for(i=0; i<argc; i++) {
        argv[i].str = object->argv[i];
        argv[i].ptr = 0;

        if (TRCSTACK) {
            vmiPrintf("TRCSTACK: Build argv[%d].str=%s\n", i, argv[i].str);
        }
    }
    argv[i].str = 0; // NULL Terminated
    argv[i].ptr = 0;

    for(i=0; i<envc; i++) {
        envp[i].str = object->envp[i];
        envp[i].ptr = 0;

        if (TRCSTACK) {
            vmiPrintf("TRCSTACK: Build envp[%d].str=%s\n", i, envp[i].str);
        }
    }
    envp[i].str = 0; // NULL Terminated
    envp[i].ptr = 0;

    //
    // Setup processors stack
    //
    memDomainP domain = vmirtGetProcessorDataDomain(processor);
    memEndian  endian = vmirtGetProcessorDataEndian(processor);

    Addr  SP  = 0;
    Addr *SPP = &SP;
    vmiRegInfoCP SPCP = getSPCP(processor, object);
    vmiosRegRead(processor, SPCP, SPP);

    //
    // Force SP to top of notional stack if uninitialized
    //
    if (TRCSTACK) vmiPrintf("TRCSTACK: SP value " FMT_64x "\n", SP);

    if (SP == 0) {
        SP = ~0;    // all 1's
        //SP >>= (64 - SPCP->bits); // Breaks --parallel
        SP >>= 32;
        if (TRCSTACK) vmiPrintf("TRCSTACK: Initialize SP to " FMT_64x "\n", SP);
        vmiosRegWrite(processor, SPCP, SPP);
    }

    Uns8 abiSize = SPCP->bits / 8;

    //
    // Align the stack 4 / 8 / 16 ?
    //

#if defined(_INTERCEPT_START_)
    //
    // Push a abiSize [end marker] ZERO/NULL at Top of stack
    // By inspection, it looks like abiSize is actually 4
    //
    pushStackDownNByte(4, domain, endian, SPP, ZERO);
    if (TRCSTACK) vmiPrintf("TRCSTACK: " FMT_64x ": " FMT_64x " : Push a NULL at TOS\n", SP, (Uns64)ZERO);
#endif

    //
    // push envp[0..n] strings onto the stack and store address on stack
    //
    Uns32 envc_i = 0;
    while (envp[envc_i].str) {
        pushStackDownString(domain, endian, SPP, envp[envc_i].str);
        if (TRCSTACK) vmiPrintf("TRCSTACK: " FMT_64x ": '%s' : Push env[%d]\n", SP, envp[envc_i].str, envc_i);

        envp[envc_i].ptr = SP;
        envc_i++;
    }

    //
    // push argv[0] strings onto the stack and store address on stack
    //
    if (argv[0].str) {
        pushStackDownString(domain, endian, SPP, argv[0].str);
        if (TRCSTACK) vmiPrintf("TRCSTACK: " FMT_64x ": '%s' : Push argv[0]\n", SP, argv[0].str);

        argv[0].ptr = SP;
    }

    //
    // push argv[0..n] onto the stack
    //
    Uns32 argc_i = 0;
    while (argv[argc_i].str) {
        pushStackDownString(domain, endian, SPP, argv[argc_i].str);
        if (TRCSTACK) vmiPrintf("TRCSTACK: " FMT_64x ": '%s' : Push argv[%d]\n", SP, argv[argc_i].str, argc_i);

        argv[argc_i].ptr = SP;
        argc_i++;
    }

    //
    // Aux Info
    //
#if defined(_INTERCEPT_START_)
    //
    // Push ARCH name
    //
    pushStackDownString(domain, endian, SPP, object->cinfo->at.platform);
    if (TRCSTACK) vmiPrintf("TRCSTACK: " FMT_64x ": '%s' : AUXV_AT_PLATFORM\n", SP, object->cinfo->at.platform);
    Addr AUXV_AT_PLATFORM_P = SP;

    //
    // Push 16 random bytes
    //
    Uns32 r = 0;
    for (r=0; r<16; r++) {
        pushStackDownNByte(1, domain, endian, SPP, object->cinfo->at.random[r]);
        if (TRCSTACK) vmiPrintf("TRCSTACK: " FMT_64x ": " FMT_64x " : AUX_AT_RANDOM[%d]\n", SP, object->cinfo->at.random[r], r);
    }
    Addr AUX_AT_RANDOM_P = SP;
#endif

    //
    // Now the pointers down from stack
    // padding(16 align)
    // AT_NULL  *abiSize
    // auxv ... *abiSize
    // NULL     *abiSize
    // envp ... *abiSize
    // NULL     *abiSize
    // argv ... *abiSize
    // argc     *abiSize (must be ALIGN16)
    //
    ALIGN16(SPP);
    //
    // argc+NULL + (argc*argv)+NULL + (envc*envp)+NULL + (auxc*auxv*2)+NULL
    //
    Uns64 space = 0;
#if defined(_INTERCEPT_MAIN_)
    space += (abiSize        + abiSize);  // argc+NULL
    space += (2*abiSize);                 // 2 NULL
    space += (argc*abiSize   + abiSize);  // (argc*argv)+NULL
    space += (envc*abiSize   + abiSize);  // (envc*envp)+NULL
#endif
#if defined(_INTERCEPT_START_)
    //
    // how many Aux vectors to handle ?
    //
    Uns64 auxc = DLINFO_ITEMS + 1;
    space += (abiSize        + abiSize);  // argc+NULL
    space += (argc*abiSize   + abiSize);  // (argc*argv)+NULL
    space += (envc*abiSize   + abiSize);  // (envc*envp)+NULL
    space += (auxc*abiSize*2 + abiSize);  // (auxc*auxv*2)+NULL
#endif

    //
    // tos points at where argc will go
    //
    Addr tos = SP - space;
    ALIGN16(&tos);
    Addr bound0 = SP;
    SP = tos;
    Uns32 idx;

    //
    // argc
    //
    pushStackUpNByte(abiSize, domain, endian, &tos, argc);
    if (TRCSTACK) vmiPrintf("TRCSTACK: " FMT_64x ": " FMT_64x " : Push argc\n", tos, (Uns64)argc);

    //
    // This is only done if the intercept is to main
    //
#if defined(_INTERCEPT_MAIN_)
    pushStackUpNByte(abiSize, domain, endian, &tos, ZERO); // Filled in by program main
    if (TRCSTACK) vmiPrintf("TRCSTACK: " FMT_64x ": " FMT_64x " : Push ZERO (Filled in by program main)\n", tos, (Uns64)ZERO);

    pushStackUpNByte(abiSize, domain, endian, &tos, ZERO); // Filled in by program main
    if (TRCSTACK) vmiPrintf("TRCSTACK: " FMT_64x ": " FMT_64x " : Push ZERO (Filled in by program main)\n", tos, (Uns64)ZERO);

    Addr argv0P = 0;
    Addr envp0P = 0;
#endif

    //
    // argv pointers
    //
    for (idx=0; idx<argc; idx++) {
#if defined(_INTERCEPT_MAIN_)
        if (idx == 0) {
            argv0P = tos;
        }
#endif
        pushStackUpNByte(abiSize, domain, endian, &tos, argv[idx].ptr);
        if (TRCSTACK) vmiPrintf("TRCSTACK: " FMT_64x ": " FMT_64x " : Push *argv[%d]\n", tos, argv[idx].ptr, idx);

    }
    pushStackUpNByte(abiSize, domain, endian, &tos, ZERO); // NULL
    if (TRCSTACK) vmiPrintf("TRCSTACK: " FMT_64x ": " FMT_64x " : Push NULL\n", tos, (Uns64)ZERO);

    //
    // envp pointers
    //
    for (idx=0; idx<envc; idx++) {
#if defined(_INTERCEPT_MAIN_)
        if (idx == 0) {
            envp0P = tos;
        }
#endif
        pushStackUpNByte(abiSize, domain, endian, &tos, envp[idx].ptr);
        if (TRCSTACK) vmiPrintf("TRCSTACK: " FMT_64x ": " FMT_64x " : Push *envp[%d]\n", tos, envp[idx].ptr, idx);

    }
    pushStackUpNByte(abiSize, domain, endian, &tos, ZERO); // NULL
    if (TRCSTACK) vmiPrintf("TRCSTACK: " FMT_64x ": " FMT_64x " : Push NULL\n", tos, (Uns64)ZERO);

#if defined(_INTERCEPT_START_)
    //
    // ELF Auxilliary Table
    //
    writeUal(abiSize, domain, endian, "AT_PLATFORM", &tos, AT_PLATFORM, AUXV_AT_PLATFORM_P);
  //writeUal(abiSize, domain, endian, "AT_HWCAP2",   &tos, AT_HWCAP2,   object->cinfo->at.hwcap2);
    writeUal(abiSize, domain, endian, "AT_RANDOM",   &tos, AT_RANDOM,   AUX_AT_RANDOM_P);
    writeUal(abiSize, domain, endian, "AT_CLKTCK",   &tos, AT_CLKTCK,   object->cinfo->at.clktck);
    writeUal(abiSize, domain, endian, "AT_HWCAP",    &tos, AT_HWCAP,    object->cinfo->at.hwcap);
    writeUal(abiSize, domain, endian, "AT_EGID",     &tos, AT_EGID,     object->cinfo->at.egid);
    writeUal(abiSize, domain, endian, "AT_GID",      &tos, AT_GID,      object->cinfo->at.gid);
    writeUal(abiSize, domain, endian, "AT_EUID",     &tos, AT_EUID,     object->cinfo->at.euid);
    writeUal(abiSize, domain, endian, "AT_UID",      &tos, AT_UID,      object->cinfo->at.uid);
    writeUal(abiSize, domain, endian, "AT_ENTRY",    &tos, AT_ENTRY,    object->cinfo->at.entry);
    writeUal(abiSize, domain, endian, "AT_FLAGS",    &tos, AT_FLAGS,    object->cinfo->at.flags);
    writeUal(abiSize, domain, endian, "AT_BASE",     &tos, AT_BASE,     object->cinfo->at.base);
    writeUal(abiSize, domain, endian, "AT_PAGESZ",   &tos, AT_PAGESZ,   object->cinfo->at.pagesz);
    writeUal(abiSize, domain, endian, "AT_PHNUM",    &tos, AT_PHNUM,    object->cinfo->at.phnum);
    writeUal(abiSize, domain, endian, "AT_PHENT",    &tos, AT_PHENT,    object->cinfo->at.phent);
    writeUal(abiSize, domain, endian, "AT_PHDR",     &tos, AT_PHDR,     object->cinfo->at.phdr);
    writeUal(abiSize, domain, endian, "AT_NULL",     &tos, AT_NULL,     ZERO);
#endif

    Addr bound1 = tos;
    if (bound1 > bound0) {
        vmiMessage("W", CPU_PREFIX "_STACK", "bound0=" FMT_64x " bound1=" FMT_64x "\n", bound0, bound1);
    }

    //
    // Now rewrite the Stack register
    //
    vmiosRegWrite(processor, SPCP, SPP);

#if defined(_INTERCEPT_MAIN_)
    //
    // Patch registers
    // int main (argc, char *argv[], char *envp[]
    //   arg[0] = argc
    //   arg[1] = argv
    //   arg[2] = envp
    //
    vmiosRegWrite(processor, getArgCP(processor, object, 0), &argc);
    vmiosRegWrite(processor, getArgCP(processor, object, 1), &argv0P);
    vmiosRegWrite(processor, getArgCP(processor, object, 2), &envp0P);

    //
    // the (_)environ variable should point at the start of the envp list
    //
    if(envp0P) {
        vmiSymbolCP environCP = vmirtGetSymbolByName(processor, "environ");
        if (!environCP) {
            environCP = vmirtGetSymbolByName(processor, "_environ");
        }
        if (environCP) {
            Addr environ = vmirtGetSymbolAddr(environCP);
            switch (abiSize) {
                case 4:
                    vmirtWrite4ByteDomain(domain, environ, endian, envp0P, MEM_AA_FALSE);
                    break;

                case 8:
                    vmirtWrite8ByteDomain(domain, environ, endian, envp0P, MEM_AA_FALSE);
                    break;

                default:
                    vmiMessage("F", "UNSUPP", "pushStackUpNByte: Unsupported size %d", abiSize);
                    break;
            }
        }
    }
#endif
}

static UNUSED VMIOS_INTERCEPT_FN(mainStackInitCB) {
    commonStackInitCB(processor, object, thisPC, context, userData, atOpaqueIntercept, "unknown");
}

#endif // _ARGVENVP_INTERCEPT_C_H_

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

#include "hostapi/impTypes.h"

/*
 * Interface from Mips32 processor cache model to an external Bus Interface Unit (BIU) model.
 *
 * Passes additional processor and cache information required to model the BIU.
 *
 */

#define CACHE_EXT_BIU_VERSION "0.1"

//
// Define architectural-width unsigned value type if required
//
#ifndef MIPS_UNS_ARCH
#ifndef MIPS_ARCH_BITS
    #define MIPS_ARCH_BITS 32
#endif
#if(MIPS_ARCH_BITS==32)
    #define MIPS_UNS_ARCH Uns32
#elif(MIPS_ARCH_BITS==64)
    #define MIPS_UNS_ARCH Uns64
#else
    #error "unsupported architecture bits"
#endif
typedef MIPS_UNS_ARCH mipsUnsArch, *mipsUnsArchP;
#endif

//
// Info passed for CACHE instructions
//
typedef struct cacheInstrInfoS {
    Uns32       cacheType;  // Which cache: 0=I, 1=D, 2=T, 3=S
    Uns32       cacheOp;    // Cache Instruction operation code
    mipsUnsArch effAddr;    // Effective address (index for index ops, PA for address ops)
    Uns32       cca;        // Cache Coherency Attribute (for address type ops only)
} cacheInstrInfoT, *cacheInstrInfoP;

//
// Prototype for function to be called when passing through CACHE instructions
// This function will be called as follows:
//
// For I and D CACHE instructions
//
//    If none of WST/SPR/ITC/DYT are set then these are handled internally by
//    the cache model, nothing is passed through to the BIU interface except,
//    for the 34Kn only, CACHE op 3 on a D cache is passed through.
//
//    If WST or DYT is set the instruction is a nop for I and D caches.
//
//    If SPR or ITC is set and the op is Index Load Tag or Index Store Tag then
//    the instruction is passed through.
//
//    If SPR is set and the op is Index Store Data then the instruction is
//    passed through (the documentation does not mention any support for
//    Index Store Data for ITC mode).
//
//    Note that on the 74K, the SPR bit is defined as a don't care for the
//    I cache, as defined on page 344 of MD00519-2B-74K-SUM-01.04.pdf,
//    so even if the SPR bit is set the normal CACHE instruction operations
//    will be performed (for the I cache only). No other variant specifies this.
//
// For S and T (L2/3) CACHE instructions
//
//    All are passed through, regardless of the ErrCtl mode.
//
// The value of the ErrCtl register is passed in so the callback can determine
// what function to perform based on the WST/SPR/ITC/DYT bits.
//
// Pointers to the xTagLo/xDataLo/xDataHi registers that correspond to the cache
// type in the instruction are passed in. These are pointers to the register
// values and may be both read and written by the callback function. Note that
// dataHiP will be NULL if info->cacheType is 1 (indicating a D Cache)
//
#define CACHE_INSTR_EXT_CB(_NAME) void _NAME( \
    cacheInstrInfoP info,    \
    Uns32           ErrCtl,  \
    mipsUnsArchP    tagLoP,  \
    mipsUnsArchP    dataLoP, \
    mipsUnsArchP    dataHiP, \
    void           *userData \
)
typedef CACHE_INSTR_EXT_CB((*cacheInstrExtCB));

//
// Prototype for function to be called when SYNC instruction is executed
// Also called when PREF instruction with a "nudge" hint is called for an
// address with a CCA of "uncached accelerated write"
//
// nudge is a boolean value that will be true when a PREF nudge is executed
// stype is the value of the stype field of the SYNC instruction when nudge is 0
//
#define SYNC_INSTR_EXT_CB(_NAME) void _NAME( \
        Uns32  nudge,   \
        Uns32  stype,   \
        void  *userData \
)
typedef SYNC_INSTR_EXT_CB((*syncInstrExtCB));

//
// The following structure should be allocated in the platform and a pointer to it passed in to
// the processor model with the "cacheextbiuinfo" user attribute.
//
// The structure will be updated  before each memory transaction, and the CACHE and SYNC
// instruction callbacks will be called if defined.
//
typedef struct cacheExtBIUInfoS {

    //
    // These members must be set by the external routine before initialization
    //
    const char     *version;            // Version string to insure linking compatible modules
    cacheInstrExtCB cacheInstrCB;       // Non-L1 CACHE instruction call back function
    syncInstrExtCB  syncInstrCB;        // SYNC instruction call back function
    void           *userData;           // External routine's private data, also passed into call backs

    //
    // These members will be set by the cache routines at initialization and will not change
    //
    Uns32    PRId;        // the COP0 PRId register value

    //
    // These members are set during memory read/write.
    // Values are valid only if "valid" is true
    // Note that "valid" will not be true during artifact accesses
    //
    Bool        valid;          // volatile data is currently valid
    Bool        isASetOrClr;    // Current instruction is ASET or ACLR
    Bool        isWlOrWr;       // Current instruction is LWL/LWR/SWL/SWR
    Bool        cacheLine;      // true when access is a cache line flush/fill

    //
    // The following fields are valid only when "cacheLine" is False:
    //
    Bool        configMM;           // The Config[MM] bit
    Bool        LLbit;              // The LLbit value - indicates an atomic memory transaction
    Uns32        cca;               // Coherent Cacheability Attribute for this access
    Uns32        curVPE;            // The TCBind[CurVPE] value identifying the VPE accessing the memory
    Uns32        curTC;             // The TCBind[CurTC]  value identifying the TC  accessing the memory
    Bool        isFetch;            // Access is an instruction fetch

} cacheExtBIUInfoT, *cacheExtBIUInfoP;

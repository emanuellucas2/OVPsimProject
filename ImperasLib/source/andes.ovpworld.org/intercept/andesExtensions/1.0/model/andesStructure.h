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

#pragma once

// model header files
#include "andesConfig.h"
#include "andesCSR.h"
#include "andesMode.h"

// base model header files
#include "riscvCSRTypes.h"
#include "riscvMode.h"
#include "riscvModelCallbacks.h"
#include "riscvTypeRefs.h"


////////////////////////////////////////////////////////////////////////////////
// PHYSICAL MEMORY ATTRIBUTE SUPPORT
////////////////////////////////////////////////////////////////////////////////

//
// Number of PMA entries
//
#define PMA_NUM 16

//
// PMA entry type
//
typedef enum pmaETYPE {
    PMAET_OFF,
    PMAET_TOR,
    PMAET_NA4,
    PMAET_NAPOT,
} pmaETYP;

//
// PMA memory type
//
typedef enum pmaMTYPE {
    PMAMT_Device_Non_bufferable                     =  0,
    PMAMT_Device_bufferable                         =  1,
    PMAMT_Memory_Non_cacheable_Non_bufferable       =  2,
    PMAMT_Memory_Non_cacheable_Bufferable           =  3,
    PMAMT_Memory_Write_through_No_allocate          =  4,
    PMAMT_Memory_Write_through_Read_allocate        =  5,
    PMAMT_Memory_Write_through_Write_allocate       =  6,
    PMAMT_Memory_Write_through_Read_Write_allocate  =  7,
    PMAMT_Memory_Write_back_No_allocate             =  8,
    PMAMT_Memory_Write_back_Read_allocate           =  9,
    PMAMT_Memory_Write_back_Write_allocate          = 10,
    PMAMT_Memory_Write_back_Read_and_Write_allocate = 11,
    PMAMT_Black_Hole                                = 15,
} pmaMTYP;

//
// PMP configuration entry structure
//
typedef union pmacfgElemU {
    Uns8 u8;
    struct {
        pmaETYP ETYP : 2;
        pmaMTYP MTYP : 4;
        Bool    NAMO : 1;
        Uns8    _u1  : 1;
    };
} pmacfgElem;

//
// Container for PMA configuration registers
//
typedef union riscvPMACFGU {
    Uns8  u8 [PMA_NUM];     // when viewed as bytes
    Uns32 u32[PMA_NUM/4];   // when viewed as words
    Uns64 u64[PMA_NUM/8];   // when viewed as double words
} riscvPMACFG;


////////////////////////////////////////////////////////////////////////////////
// PERFORMANCE MONITORS
////////////////////////////////////////////////////////////////////////////////

//
// This defines supported timers
//
typedef enum andesCounterIDE {
    AT_CY,          // cycle counter
    AT_TM,          // timer (unused)
    AT_IR,          // instruction counter
    AT_HPM3,        // hpmcounter3
    AT_HPM4,        // hpmcounter4
    AT_HPM5,        // hpmcounter5
    AT_HPM6,        // hpmcounter6
    AT_LAST         // KEEP LAST: for sizing
} andesCounterID;

//
// This defines supported timers
//
typedef enum andesCounterModeE {
    ACM_INACTIVE,   // counter inactive
    ACM_CY,         // counting cycles
    ACM_IR,         // counting instructions
} andesCounterMode;

//
// This holds state for a single counter
//
typedef struct andesCounterS {
    andesCounterID   id;        // counter ID
    vmiosObjectP     object;    // parent object
    vmiModelTimerP   vmi;       // VMI timer object
    Uns64            base;      // base value
    andesCounterMode mode;      // counter active mode
    Uns8             TYPE;      // Andes timer type code
    Uns8             SEL;       // Andes timer select code
} andesCounter, *andesCounterP;


////////////////////////////////////////////////////////////////////////////////
// EXTENSION OBJECT
////////////////////////////////////////////////////////////////////////////////

//
// Andes local memory domain management
//
typedef struct andesLMS {
    Uns32      bytes;
    memDomainP LMDomain;
} andesLM, andesLMP;

//
// Intercept object structure
//
typedef struct vmiosObjectS {

    // associated processor
    riscvP             riscv;

    // true processor registers
    andesCSRs          csr;
    andesCSRMasks      csrMask;

    // temporary used to record previous stack pointer when HSP enabled
    Uns64              oldSP;

    // modified CSR definitions
    riscvCSRAttrs      csrs[XCSR_ID(LAST)];

    // model support
    andesMode          mode;

    // parameters
    vmiParameterP      parameters;

    // configuration register defaults
    andesConfig        csrDefaults;

    // extension callbacks
    riscvExtCB         extCB;

    // ILM/DLM management
    andesLM            LM[2];
    memDomainP         physDomains[RISCV_MODE_LAST_BASE][2];

    // physical memory attribute support
    riscvPMACFG        pmacfg;              // pmacfg registers
    Uns64              pmaaddr[PMA_NUM];    // pmaaddr registers

    // performance monitors
    andesCounter       counters[AT_LAST];

    // override of default unaligned access behavior in base model load/store
    // instructions
    Bool               unaligned;

    // ACE extension object
    const char        *aceFile;
    ace_copilot_agentP aceAgent;
    ace_extP           aceExtension;
    Uns64              aceCause;

    // net ports added by this extension
    riscvNetPortP      netPorts;
    Uns32              ueiackHandle;
    Uns32              seiackHandle;
    Uns32              meiackHandle;

    // local temporaries
    Uns64              tmp[16];

} vmiosObject;



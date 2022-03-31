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
#include "sifiveConfig.h"
#include "sifiveCSR.h"

// base model header files
#include "riscvCSRTypes.h"
#include "riscvModelCallbacks.h"


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
        Uns8    _u1  : 2;
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
// EXTENSION OBJECT
////////////////////////////////////////////////////////////////////////////////

//
// Intercept object structure
//
typedef struct vmiosObjectS {

    // associated processor
    riscvP         riscv;

    // instance-specific variant
    sifiveVariant  variant;

    // parameters
    vmiParameterP  parameters;

    // true processor registers
    sifiveCSRs     csr;
    sifiveCSRMasks csrMask;

    // temporary used to record previous stack pointer when HSP enabled
    Uns64          oldSP;

    // modified CSR definitions
    riscvCSRAttrs  csrs[XCSR_ID(LAST)];

    // extension callbacks
    riscvExtCB     extCB;

} vmiosObject;



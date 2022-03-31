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

// base model header files
#include "riscvCSR.h"
#include "riscvModelCallbacks.h"
#include "riscvModelCallbackTypes.h"


////////////////////////////////////////////////////////////////////////////////
// CSR ENUMERATION
////////////////////////////////////////////////////////////////////////////////

typedef enum extCSRIdE {

    // SiFive Custom CSRs
    XCSR_ID (bpm),                  //0x7C0
    XCSR_ID (featureDisable),       //0x7C1
    XCSR_ID (PowerDial),            //0x7C8

    // keep last (used to define size of the enumeration)
    XCSR_ID (LAST)

} extCSRId;


// -----------------------------------------------------------------------------
// bpm              (id 0x7C0)
// -----------------------------------------------------------------------------

// 32-bit view
typedef struct {
   Uns32 bdp :  1;
   Uns32 _u1 : 31;
} CSR_REG_TYPE_32(bpm);

// define 32 bit-only type
CSR_REG_STRUCT_DECL_32(bpm);

// Define CSR number)
#define NUM_bpm 0x7c0

// define write masks
#define WM32_bpm 0x1
#define WM64_bpm 0x1


// -----------------------------------------------------------------------------
// featureDisable   (id 0x7C1)
// -----------------------------------------------------------------------------

// 32-bit view
typedef struct {
   Uns32 _u1 : 32;
} CSR_REG_TYPE_32(featureDisable);

// define 32 bit-only type
CSR_REG_STRUCT_DECL_32(featureDisable);

// Define CSR number)
#define NUM_featureDisable 0x7c1

// define write masks
#define WM32_featureDisable 0
#define WM64_featureDisable 0


// -----------------------------------------------------------------------------
// PowerDial        (id 0x7C8)
// -----------------------------------------------------------------------------

// 32-bit view
typedef struct {
   Uns32 IssueRate :  4;
   Uns32 _u1       : 28;
} CSR_REG_TYPE_32(PowerDial);

// define 32 bit-only type
CSR_REG_STRUCT_DECL_32(PowerDial);

// Define CSR number)
#define NUM_PowerDial 0x7c8

// define write masks
#define WM32_PowerDial 0xf
#define WM64_PowerDial 0xf


////////////////////////////////////////////////////////////////////////////////
// INITIALIZATION
////////////////////////////////////////////////////////////////////////////////

//
// Initialize CSR state
//
void sifiveCSRInit(vmiosObjectP object);


////////////////////////////////////////////////////////////////////////////////
// SYSTEM REGISTER CONTAINER
////////////////////////////////////////////////////////////////////////////////

//
// This type defines the CSRs implemented as true registers in the processor
// structure
//
typedef struct sifiveCSRsS {

    // MACHINE MODE CSRS
    CSR_REG_DECL(bpm);
    CSR_REG_DECL(featureDisable);
    CSR_REG_DECL(PowerDial);

} sifiveCSRs;


////////////////////////////////////////////////////////////////////////////////
// SYSTEM REGISTER WRITE MASKS
////////////////////////////////////////////////////////////////////////////////

//
// This type defines dynamic write masks for CSRs
//
typedef struct sifiveCSRMasksS {

    // MACHINE MODE CSRS
    CSR_REG_DECL(featureDisable);   // 0x7C1

} sifiveCSRMasks;


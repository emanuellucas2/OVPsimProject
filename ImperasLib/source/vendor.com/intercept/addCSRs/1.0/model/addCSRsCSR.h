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

// base processor model header files
#include "riscvCSR.h"


// -----------------------------------------------------------------------------
// custom_rw1_32    (id 0xBC0)
// -----------------------------------------------------------------------------

// 32-bit view
typedef struct {
    Uns32 F1  : 8;
    Uns32 _u1 : 8;
    Uns32 F3  : 8;
    Uns32 _u2 : 8;
} CSR_REG_TYPE_32(custom_rw1_32);

// define 32 bit type
CSR_REG_STRUCT_DECL_32(custom_rw1_32);

// define write masks
#define WM32_custom_rw1_32 0x00ff00ff
#define WM64_custom_rw1_32 0x00ff00ff

// -----------------------------------------------------------------------------
// custom_rw2_64    (id 0xBC1)
// -----------------------------------------------------------------------------

// 64-bit view
typedef struct {
    Uns32 F1  : 8;
    Uns32 _u1 : 8;
    Uns32 F3  : 8;
    Uns32 _u2 : 8;
    Uns32 F5  : 8;
    Uns32 _u3 : 8;
    Uns32 F7  : 8;
    Uns32 _u4 : 8;
} CSR_REG_TYPE_64(custom_rw2_64);

// define 32 bit type
CSR_REG_STRUCT_DECL_64(custom_rw2_64);

// define write masks
#define WM32_custom_rw2_64 0x00ff00ff
#define WM64_custom_rw2_64 0xff00ff0000ff00ffULL

// -----------------------------------------------------------------------------
// custom_ro1       (id 0xFC0)
// -----------------------------------------------------------------------------

// 64-bit view
typedef struct {
    Uns32 low  : 32;
    Uns32 high : 32;
} CSR_REG_TYPE_64(custom_ro1);

// define 32 bit type
CSR_REG_STRUCT_DECL_64(custom_ro1);

// define write masks
#define WM32_custom_ro1 0x0
#define WM64_custom_ro1 0x0

// -----------------------------------------------------------------------------
// custom_rw3_32    (id 0xBC2)
// -----------------------------------------------------------------------------

// 32-bit view
typedef struct {
    Uns32 A : 8;
    Uns32 B : 8;
    Uns32 C : 8;
    Uns32 D : 8;
} CSR_REG_TYPE_32(custom_rw3_32);

// define 32 bit type
CSR_REG_STRUCT_DECL_32(custom_rw3_32);

// define write masks
#define WM32_custom_rw3_32 -1
#define WM64_custom_rw3_32 -1

// -----------------------------------------------------------------------------
// custom_rw4_64    (id 0xBC3)
// -----------------------------------------------------------------------------

// 64-bit view
typedef struct {
    Uns32 E : 8;
    Uns32 F : 8;
    Uns32 G : 8;
    Uns32 H : 8;
    Uns32 I : 8;
    Uns32 J : 8;
    Uns32 K : 8;
    Uns32 L : 8;
} CSR_REG_TYPE_64(custom_rw4_64);

// define 32 bit type
CSR_REG_STRUCT_DECL_64(custom_rw4_64);

// define write masks
#define WM32_custom_rw4_64 -1
#define WM64_custom_rw4_64 -1


////////////////////////////////////////////////////////////////////////////////
// SYSTEM REGISTER CONTAINER
////////////////////////////////////////////////////////////////////////////////

//
// This type defines the CSRs implemented as true registers in the processor
// structure
//
typedef struct addCSRsCSRsS {
    CSR_REG_DECL (custom_rw1_32);    // 0xBC0
    CSR_REG_DECL (custom_rw2_64);    // 0xBC1
    CSR_REG_DECL (custom_rw3_32);    // 0xBC2
    CSR_REG_DECL (custom_rw4_64);    // 0xBC3
    CSR_REG_DECL (custom_ro1);       // 0xFC0
} addCSRsCSRs;



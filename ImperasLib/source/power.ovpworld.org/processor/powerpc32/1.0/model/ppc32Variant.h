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

#ifndef PPC32_VARIANT_H
#define PPC32_VARIANT_H

//
// bits  [15:0] indicate features
// bits [31:16] indicate processor type
//
typedef Uns32 ppc32Architecture;

//
// Base Enumerated Architecture types
//
#define FEATURE_I_B    0x0001
#define FEATURE_I_BCDA 0x0002
#define FEATURE_I_S    0x0004
#define FEATURE_I_E    0x0008
#define FEATURE_I_E_PC 0x0010
#define FEATURE_I_E_PD 0x0020
#define FEATURE_I_EC   0x0040
#define FEATURE_I_FP   0x0080
#define FEATURE_I_DFP  0x0100
#define FEATURE_I_MA   0x0200
#define FEATURE_I_SP   0x0400
#define FEATURE_I_V    0x0800
#define FEATURE_I_LMA  0x1000
#define FEATURE_I_WT   0x2000
#define FEATURE_I_VLE  0x4000

//
// GENERIC defines
//
#define VARIANT_UISA      (0x0001 << 16)
#define VARIANT_MPC82X   ((0x0002 << 16) | FEATURE_I_B | FEATURE_I_E | FEATURE_I_MA)
//#define VARIANT_MSPE     ((0x0002 << 16) | FEATURE_I_B | FEATURE_I_SP)
//#define VARIANT_MALTIVEC ((0x0004 << 16) | FEATURE_I_B | FEATURE_I_V)
//#define VARIANT_MVLE     ((0x0008 << 16) | FEATURE_I_VLE)
//#define VARIANT_MPOWER7  ((0x0010 << 16) | FEATURE_I_B | FEATURE_I_BCDA | FEATURE_I_E | FEATURE_I_FP | FEATURE_I_DFP | FEATURE_I_MA | FEATURE_I_S)
//#define VARIANT_ME500MC  ((0x0020 << 16) | FEATURE_I_B | FEATURE_I_E | FEATURE_I_E_PC | FEATURE_I_E_PD | FEATURE_I_EC)
//#define VARIANT_ME200Z3  ((0x0040 << 16) | FEATURE_I_VLE)

//
// Freescale defines
//
#define VARIANT_E200Z0 ((0x0002 << 16)| FEATURE_I_B)
#define VARIANT_E200Z1 ((0x0004 << 16)| FEATURE_I_B)
#define VARIANT_E200Z2 ((0x0008 << 16)| FEATURE_I_B)
#define VARIANT_E200Z3 ((0x0010 << 16)| FEATURE_I_B)
#define VARIANT_E200Z4 ((0x0020 << 16)| FEATURE_I_B)
#define VARIANT_E200Z5 ((0x0040 << 16)| FEATURE_I_B | FEATURE_I_MA | FEATURE_I_SP | FEATURE_I_V | FEATURE_I_LMA | FEATURE_I_VLE)
#define VARIANT_E200Z6 ((0x0080 << 16)| FEATURE_I_B | FEATURE_I_MA | FEATURE_I_SP | FEATURE_I_V | FEATURE_I_LMA | FEATURE_I_VLE)
#define VARIANT_E200Z7 ((0x0100 << 16)| FEATURE_I_B | FEATURE_I_MA | FEATURE_I_SP | FEATURE_I_V | FEATURE_I_LMA | FEATURE_I_VLE)


//
// IBM defines
//
#define VARIANT_M440 ((0x0002 << 16) | FEATURE_I_B)
#define VARIANT_M460 ((0x0004 << 16) | FEATURE_I_B)
#define VARIANT_M470 ((0x0008 << 16) | FEATURE_I_B)
#define VARIANT_M476 ((0x0010 << 16) | FEATURE_I_B | FEATURE_I_E | FEATURE_I_FP | FEATURE_I_LMA | FEATURE_I_MA)

#endif // PPC32_VARIANT_H

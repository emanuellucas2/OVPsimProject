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

#ifndef V850_VARIANT_H
#define V850_VARIANT_H

typedef enum v850ArchitectureE {
    //
    // Base Enumerated Architecture types
    //
    ISA_E0       = 0x00000001,
    ISA_E1       = 0x00000002,
    ISA_E2       = 0x00000004,
    ISA_E2M      = 0x00000008,
    ISA_E2R      = 0x00000010,
    ISA_E1_FP    = 0x00000020,
    ISA_E2_FP    = 0x00000040,
    ISA_E2_XCL   = 0x00000080,  // Exclusive to E2
    ISA_E3       = 0x00000100,
    ISA_E3_FP    = 0x00000200,

    //
    // Base Register Sets
    //
    VGPR         = 0x00010000,
    VE0          = 0x00020000,
    VE1          = 0x00040000,
    VE1F         = 0x00080000,
    VES          = 0x00100000,
    VE2          = 0x00200000,
    VE2M         = 0x00400000,
    VE2R         = 0x00800000,
    RHG3M        = 0x01000000,

    //
    // Variant Register Sets (Inclusive)
    //
    RGPR_VE0        = VGPR,
    RSYS_VE0        = VGPR | VE0,
    RSYS_VE0_E1     = VGPR | VE0 | VE1,
    RSYS_VE0_VE2R   = VGPR | VE0 | VE1 | VE1F | VES | VE2 | VE2M | VE2R,
    RSYS_VE0_RHG3M  = VGPR | VE0 | VE1 | VE1F | VES | VE2 | VE2M | VE2R | RHG3M,

    //
    // Variant Register Sets (Exclusive)
    //
    RSYS_VE2_VE2R   =                                 VE2 | VE2M | VE2R,
    RSYS_VE2R_RHG3M =                                              VE2R | RHG3M,
    RSYS_RHG3M      =                                                     RHG3M,

    //
    // Compound Enumerated Architecture types
    //
    V850         = VE0   | ISA_E0,
    V850E1       = VE1   | ISA_E0 | ISA_E1,
    V850E1F      = VE1F  | ISA_E0 | ISA_E1 | ISA_E1_FP,
    V850ES       = VES   | ISA_E0 | ISA_E1,
    V850E2       = VE2   | ISA_E0 | ISA_E1 | ISA_E2,
    V850E2M      = VE2M  | ISA_E0 | ISA_E1 | ISA_E2 | ISA_E2M,
    V850E2R      = VE2R  | ISA_E0 | ISA_E1 | ISA_E2 | ISA_E2M | ISA_E2R | ISA_E2_FP | ISA_E2_XCL,
    RH850G3M     = RHG3M | ISA_E0 | ISA_E1 | ISA_E2 | ISA_E2M | ISA_E2R | ISA_E2_FP | ISA_E3 | ISA_E3_FP,

} v850Architecture;

#endif // V850_VARIANT_H

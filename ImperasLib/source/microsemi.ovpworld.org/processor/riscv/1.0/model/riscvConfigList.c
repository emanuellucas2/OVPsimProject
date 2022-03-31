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

// model header files
#include "riscvConfig.h"
#include "riscvVariant.h"


//
// CoreRISCV variant documentation
//
static const char *specificDocsCoreRISCV[] = {
    "---- HB0761 CoreRISCV_AXI4 v2.0 HandbookCore",
    0
};

//
// MiV_RV32IMA variant documentation
//
static const char *specificDocsMiV_RV32IMA[] = {
    "---- HB0800 MiV_RV32IMA_L1_AHB v2.0 HandbookCore",
    0
};

//
// Defined configurations
//
static const riscvConfig configList[] = {

    {
        .name           = "CoreRISCV",
        .arch           = RV32IM,
        .archMask       = RV_ARCH_MASK_DEFAULT,
        .user_version   = RVUV_2_2,
        .priv_version   = RVPV_1_10,
        .tval_ii_code   = True,
        .counteren_mask = -1,
        .specificDocs   = specificDocsCoreRISCV,
    },

    {
        .name           = "MiV_RV32IMA",
        .arch           = RV32IMA,
        .archMask       = RV_ARCH_MASK_DEFAULT,
        .user_version   = RVUV_2_2,
        .priv_version   = RVPV_1_10,
        .counteren_mask = -1,
        .specificDocs   = specificDocsMiV_RV32IMA,
        .tval_ii_code   = True,
        .reset_address  = 0x60000000,
    },

    {0} // null terminator
};

//
// This returns the supported configuration list
//
riscvConfigCP riscvGetConfigList(riscvP riscv) {
    return configList;
}


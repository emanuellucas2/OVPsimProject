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
#include "extensionConfig.h"

// extension header files
#include "addCSRsConfig.h"
#include "tmConfig.h"
#include "fifoConfig.h"

// base model header files
#include "riscvConfig.h"
#include "riscvVariant.h"

//
// Defined extensions (null-terminated list)
//
static riscvExtConfigCP allExtensions[] = {

    // example adding CSRs
    &(const riscvExtConfig){
        .id       = EXTID_ADDCSR,
        .userData = &(const addCSRsConfig){
            .csr = {
                .custom_ro1 = {u32 : {bits : 0x12345678}}
            }
        }
    },

    // example adding instructions
    &(const riscvExtConfig){
        .id       = EXTID_ADDINST,
        .userData = 0
    },

    // example adding exceptions
    &(const riscvExtConfig){
        .id       = EXTID_ADDEXCEPT,
        .userData = 0
    },

    // example adding exceptions
    &(const riscvExtConfig){
        .id       = EXTID_ADDLOCALINT,
        .userData = 0
    },

    // transactional memory extension
    &(const riscvExtConfig){
        .id       = EXTID_TM,
        .userData = &(const tmConfig){
            .variant = EXT_ALL,
            .csr = {
                .tm_cfg = {u32 : {fields : {tmPresent:1}}}
            }
        }
    },

    // fifo extension
    &(const riscvExtConfig){
        .id        = EXTID_FIFO,
        .userData  = &(const fifoConfig){
            .variant   = EXT_FIFO,
            .FIFO_bits = 32,
            .csr = {
                .fifo_cfg = {u32 : {fields : {fifoPresent:1}}}
            }
        }
    },

    0 // KEEP LAST: terminator
};

//
// Defined configurations
//
static const riscvConfig configList[] = {

    {
        .name             = "RV32X",
        .arch             = ISA_U|RV32GC|ISA_X,
        .user_version     = RVUV_DEFAULT,
        .priv_version     = RVPV_DEFAULT,
        .tval_ii_code     = True,
        .ASID_bits        = 9,
        .local_int_num    = 7,         // enable local interrupts 16-22
        .unimp_int_mask   = 0x1f0000,  // int16-int20 absent
        .extensionConfigs = allExtensions,
    },

    {
        .name             = "RV64X",
        .arch             = ISA_U|RV64GC|ISA_X,
        .user_version     = RVUV_DEFAULT,
        .priv_version     = RVPV_DEFAULT,
        .tval_ii_code     = True,
        .ASID_bits        = 9,
        .local_int_num    = 7,         // enable local interrupts 16-22
        .unimp_int_mask   = 0x1f0000,  // int16-int20 absent
        .extensionConfigs = allExtensions
    },

    {0} // null terminator
};

//
// This returns the supported configuration list
//
riscvConfigCP riscvGetConfigList(riscvP riscv) {
    return configList;
}


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
#include "riscvVMConstants.h"

// extension header files
#include "sifiveConfig.h"
#include "sifiveVariant.h"

//
// Specify variant-specific documentation
//
#define SPECIFIC_DOC(_NAME) (const char *[]){_NAME, 0}

//
// Mandatory extension configuration macro
// - _VARIANT = 0 => No custom extension behavior
//
#define SIFIVE_EXTENSION(_VARIANT) \
    .extensionConfigs = (riscvExtConfigCP[]){ \
        &(const riscvExtConfig){ \
            .id       = SIFIVE_OVP_CONFIG_ID, \
            .userData = &(const sifiveConfig){ \
                .variant = _VARIANT, \
            } \
        }, \
        0 \
    }


// implemented in 21G1 silicon is v0.94 draft
// https://github.com/riscv/riscv-bitmanip/blob/64ff098dc0aec264b1c4cf359b30a67ec03bb718/bitmanip-draft.pdf
#define SIFIVE_BITMANIP_VERSION RVBV_0_94

#define SIFIVE_VENDOR_ID_2_SERIES             0x80000002
#define SIFIVE_VENDOR_ID_3_5_SERIES           0x00000001
#define SIFIVE_VENDOR_ID_7_SERIES             0x80000007
#define SIFIVE_VENDOR_ID_X200_SERIES          0x80000007
#define SIFIVE_VENDOR_ID_P500_SERIES          0x80000008
#define SIFIVE_JEDEC                          0x489
#define SIFIVE_21G1_02_00_LLAMA_02_00_GENERAL 0x04210427

//
// Vector configuration for SiFive cores
//
#define SIFIVE_VECTOR_CONFIG \
    .vect_version = RVVV_MASTER,                \
    .fp16_version = RVFP16_IEEE754,             \
    .Zvlsseg      = 1,                          \
    .Zvamo        = 1,                          \
    .Zvediv       = 0,                          \
    .Zvqmac       = 0,                          \
    .ELEN         = 64,                         \
    .SLEN         = 512,                        \
    .VLEN         = 512

//
// X280 variant documentation
//
static const char *specificDocsX280[] = {
    "---- Mongoose Specsheet 00.09 - Imperas",
    "---- SiFive X280 Core Complex Manual - 21G2.01.00",
    "---- Initial configuration definition - work in progress",
    0
};

//
// P550/650 variant documentation
//
static const char *specificDocsP550[] = {
    "---- Narwhal Specsheet 00.04",
    "---- SiFive P550 Core Complex Manual - 21G2.01.00",
    "---- Initial configuration definition - work in progress",
    0
};

//
// Defined configurations
//
static const riscvConfig configList[] = {

    {
        .name             = "E20",
        .arch             = RV32IMC|ISA_B,
        .archMask         = 0,  // MISA cannot be changed by software TODO: Update for correct bits that can change
        .archFixed        = ~(ISA_A|ISA_E|ISA_I|ISA_M|ISA_U|ISA_B),
        .bitmanip_version = SIFIVE_BITMANIP_VERSION,
        .bitmanip_absent  = ~(RVBS_Zba|RVBS_Zbb),
        .user_version     = RVUV_2_3,
        .priv_version     = RVPV_1_11,
        .rnmi_version     = RNMI_NONE,  // RNMI not present in this core
        .specificDocs     = SPECIFIC_DOC("SiFive E20 Manual v19.05"),
        .PMP_registers    = 0,
        .tval_ii_code     = True,
        .local_int_num    = 32,
        .time_undefined   = True,
        .lr_sc_grain      = 64,
        .tvec_align       = 64,
        .d_requires_f     = True,
        .mstatus_fs_mode  = RVFS_ALWAYS_DIRTY,
        .ecode_mask       = 0x1f,
        .ecode_nmi        = 2,
        .ecode_nmi_mask   = 0x3,
        .counteren_mask   = -1,

        // CLINT configuration
        .CLINT_address       = 0x02000000,

        // CLIC configuration
        .CLIC_version        = RVCLC_20180831,
        .CLICLEVELS          = 16,
        .CLICANDBASIC        = True,
        .CLICINTCTLBITS      = 5,
        .CLICCFGMBITS        = 0,
        .CLICCFGLBITS        = 2,
        .CLICSELHVEC         = True,
        .CLICXNXTI           = True,
        .intthresh_undefined = True,
        .mclicbase_undefined = True,
        .posedge_0_63        = 0x100f,

        // CSR configuration
        .csr = {
            .mclicbase = {u32 : {bits : 0x02800000}},
            .mvendorid = {u32 : {bits : SIFIVE_JEDEC}},
            .marchid   = {u32 : {bits : SIFIVE_VENDOR_ID_2_SERIES}},
            .mimpid    = {u32 : {bits : SIFIVE_21G1_02_00_LLAMA_02_00_GENERAL}},
        },

        SIFIVE_EXTENSION(S5V_PWRD)
    },

    {
        .name             = "E21",
        .arch             = RV32IMAC|ISA_U|ISA_B,
        .archMask         = 0,  // MISA cannot be changed by software TODO: Update for correct bits that can change
        .archFixed        = ~(ISA_U|ISA_E|ISA_I|ISA_M|ISA_F|ISA_D|ISA_A|ISA_B),
        .bitmanip_version = SIFIVE_BITMANIP_VERSION,
        .bitmanip_absent  = ~(RVBS_Zba|RVBS_Zbb),
        .user_version     = RVUV_2_3,
        .priv_version     = RVPV_1_11,
        .rnmi_version     = RNMI_0_2_1,
        .specificDocs     = SPECIFIC_DOC("SiFive E21 Manual v19.05"),
        .PMP_registers    = 8,
        .tval_ii_code     = True,
        .local_int_num    = 127,
        .time_undefined   = True,
        .lr_sc_grain      = 64,
        .tvec_align       = 64,
        .d_requires_f     = True,
        .mstatus_fs_mode  = RVFS_ALWAYS_DIRTY,
        .ecode_mask       = 0x1f,
        .ecode_nmi        = 2,
        .ecode_nmi_mask   = 0x3,
        .counteren_mask   = -1,

        // CLINT configuration
        .CLINT_address       = 0x02000000,

        // CLIC configuration
        .CLIC_version        = RVCLC_20180831,
        .CLICLEVELS          = 16,
        .CLICANDBASIC        = True,
        .CLICINTCTLBITS      = 5,
        .CLICCFGMBITS        = 0,
        .CLICCFGLBITS        = 2,
        .CLICSELHVEC         = True,
        .CLICXNXTI           = True,
        .intthresh_undefined = True,
        .mclicbase_undefined = True,
        .posedge_0_63        = 0x100f,

        // CSR configuration
        .csr = {
            .mclicbase = {u32 : {bits : 0x02800000}},
            .mvendorid = {u32 : {bits : SIFIVE_JEDEC}},
            .marchid   = {u32 : {bits : SIFIVE_VENDOR_ID_2_SERIES}},
            .mimpid    = {u32 : {bits : SIFIVE_21G1_02_00_LLAMA_02_00_GENERAL}},
        },

        SIFIVE_EXTENSION(S5V_PWRD)
    },

    {
        .name             = "E24",
        .arch             = RV32IMAC|ISA_U|ISA_F|ISA_B,
        .archMask         = 0,  // MISA cannot be changed by software TODO: Update for correct bits that can change
        .archFixed        = ~(ISA_A|ISA_B|ISA_M|ISA_F|ISA_D|ISA_U),
        .bitmanip_version = SIFIVE_BITMANIP_VERSION,
        .bitmanip_absent  = ~(RVBS_Zba|RVBS_Zbb),
        .user_version     = RVUV_2_3,
        .priv_version     = RVPV_1_11,
        .rnmi_version     = RNMI_0_2_1,
        .specificDocs     = SPECIFIC_DOC("SiFive E24 Manual v19.05"),
        .PMP_registers    = 8,
        .tval_ii_code     = True,
        .local_int_num    = 127,
        .time_undefined   = True,
        .lr_sc_grain      = 64,
        .tvec_align       = 64,
        .d_requires_f     = True,
        .mstatus_fs_mode  = RVFS_ALWAYS_DIRTY,
        .ecode_mask       = 0x1f,
        .ecode_nmi        = 2,
        .ecode_nmi_mask   = 0x3,
        .counteren_mask   = -1,

        // CLINT configuration
        .CLINT_address       = 0x02000000,

        // CLIC configuration
        .CLIC_version        = RVCLC_20180831,
        .CLICLEVELS          = 16,
        .CLICANDBASIC        = True,
        .CLICINTCTLBITS      = 5,
        .CLICCFGMBITS        = 0,
        .CLICCFGLBITS        = 2,
        .CLICSELHVEC         = True,
        .CLICXNXTI           = True,
        .intthresh_undefined = True,
        .mclicbase_undefined = True,
        .posedge_0_63        = 0x100f,

        // CSR configuration
        .csr = {
            .mclicbase = {u32 : {bits : 0x02800000}},
            .mvendorid = {u32 : {bits : SIFIVE_JEDEC}},
            .marchid   = {u32 : {bits : SIFIVE_VENDOR_ID_2_SERIES}},
            .mimpid    = {u32 : {bits : SIFIVE_21G1_02_00_LLAMA_02_00_GENERAL}},
        },

        SIFIVE_EXTENSION(S5V_PWRD)
    },

    {
        .name             = "E31",
        .arch             = RV32IMAC|ISA_U,
        .archMask         = 0,  // MISA cannot be changed by software TODO: Update for correct bits that can change
        .archFixed        = ~(ISA_E|ISA_I|ISA_A|ISA_U|ISA_M|ISA_F|ISA_D),
        .user_version     = RVUV_2_3,
        .priv_version     = RVPV_1_11,
        .rnmi_version     = RNMI_0_2_1,
        .specificDocs     = SPECIFIC_DOC("SiFive E31 Coreplex Manual v1p2"),
        .PMP_registers    = 8,
        .tval_ii_code     = True,
        .local_int_num    = 16,
        .time_undefined   = True,
        .lr_sc_grain      = 64,
        .tvec_align       = 64,
        .d_requires_f     = True,
        .mstatus_fs_mode  = RVFS_ALWAYS_DIRTY,
        .numHarts         = 1,  // override with numHarts parameter
        .ecode_mask       = 0x1f,
        .ecode_nmi        = 2,
        .ecode_nmi_mask   = 0x3,
        .counteren_mask   = -1,

        // CSR configuration
        .csr = {
            .mclicbase = {u32 : {bits : 0x02800000}},
            .mvendorid = {u32 : {bits : SIFIVE_JEDEC}},
            .marchid   = {u32 : {bits : SIFIVE_VENDOR_ID_3_5_SERIES}},
            .mimpid    = {u32 : {bits : SIFIVE_21G1_02_00_LLAMA_02_00_GENERAL}},
        },

        SIFIVE_EXTENSION(0)
    },

    {
        .name             = "E34",
        .arch             = RV32IMAC|ISA_U|ISA_F,
        .archMask         = 0,  // MISA cannot be changed by software TODO: Update for correct bits that can change
        .archFixed        = ~(ISA_A|ISA_U|ISA_M|ISA_F|ISA_D),
        .user_version     = RVUV_2_3,
        .priv_version     = RVPV_1_11,
        .rnmi_version     = RNMI_0_2_1,
        .specificDocs     = SPECIFIC_DOC("SiFive E34 Manual v19.05"),
        .PMP_registers    = 8,
        .tval_ii_code     = True,
        .local_int_num    = 16,
        .time_undefined   = True,
        .lr_sc_grain      = 64,
        .tvec_align       = 64,
        .d_requires_f     = True,
        .mstatus_fs_mode  = RVFS_ALWAYS_DIRTY,
        .numHarts         = 1,  // override with numHarts parameter
        .ecode_mask       = 0x1f,
        .ecode_nmi        = 2,
        .ecode_nmi_mask   = 0x3,
        .counteren_mask   = -1,

        // CSR configuration
        .csr = {
            .mclicbase = {u32 : {bits : 0x02800000}},
            .mvendorid = {u32 : {bits : SIFIVE_JEDEC}},
            .marchid   = {u32 : {bits : SIFIVE_VENDOR_ID_3_5_SERIES}},
            .mimpid    = {u32 : {bits : SIFIVE_21G1_02_00_LLAMA_02_00_GENERAL}},
        },

        SIFIVE_EXTENSION(0)
    },

    {
        .name             = "E51",
        .arch             = RV64IMAC|ISA_U,
        .archMask         = 0,  // MISA cannot be changed by software TODO: Update for correct bits that can change
        .archFixed        = ~(ISA_M|ISA_F|ISA_D),
        .user_version     = RVUV_2_3,
        .priv_version     = RVPV_1_11,
        .rnmi_version     = RNMI_0_2_1,
        .specificDocs     = SPECIFIC_DOC("SiFive E51 Core Complex Manual v1p2"),
        .PMP_registers    = 8,
        .tval_ii_code     = True,
        .local_int_num    = 16,
        .time_undefined   = True,
        .lr_sc_grain      = 64,
        .tvec_align       = 64,
        .d_requires_f     = True,
        .mstatus_fs_mode  = RVFS_ALWAYS_DIRTY,
        .numHarts         = 1,  // override with numHarts parameter
        .ecode_mask       = 0x1f,
        .ecode_nmi        = 2,
        .ecode_nmi_mask   = 0x3,
        .counteren_mask   = -1,

        // CSR configuration
        .csr = {
            .mclicbase = {u32 : {bits : 0x02800000}},
            .mvendorid = {u32 : {bits : SIFIVE_JEDEC}},
            .marchid   = {u32 : {bits : SIFIVE_VENDOR_ID_3_5_SERIES}},
            .mimpid    = {u32 : {bits : SIFIVE_21G1_02_00_LLAMA_02_00_GENERAL}},
        },
        .csrMask = {
            .mtvec = {u64 : {bits : 0x0000003fffffffffULL}},
        },

        SIFIVE_EXTENSION(0)
    },

    {
        .name             = "E76",
        .arch             = RV32IMAC|ISA_U|ISA_F,
        .archMask         = 0,  // MISA cannot be changed by software TODO: Update for correct bits that can change
        .archFixed        = ~(ISA_M|ISA_F|ISA_D|ISA_B|ISA_U),
        .bitmanip_version = SIFIVE_BITMANIP_VERSION,
        .bitmanip_absent  = ~(RVBS_Zba|RVBS_Zbb),
        .user_version     = RVUV_2_3,
        .priv_version     = RVPV_1_11,
        .rnmi_version     = RNMI_0_2_1,
        .specificDocs     = SPECIFIC_DOC("SiFive E76 Manual v19.05"),
        .PMP_registers    = 8,
        .tval_ii_code     = True,
        .local_int_num    = 16,
        .time_undefined   = True,
        .lr_sc_grain      = 64,
        .tvec_align       = 64,
        .d_requires_f     = True,
        .mstatus_fs_mode  = RVFS_ALWAYS_DIRTY,
        .numHarts         = 1,  // override with numHarts parameter
        .ecode_mask       = 0x1f,
        .ecode_nmi        = 2,
        .ecode_nmi_mask   = 0x3,
        .counteren_mask   = -1,

        // CSR configuration
        .csr = {
            .mclicbase = {u32 : {bits   : 0x02800000}},
            .mvendorid = {u32 : {bits : SIFIVE_JEDEC}},
            .marchid   = {u32 : {bits : SIFIVE_VENDOR_ID_7_SERIES}},
            .mimpid    = {u32 : {bits : SIFIVE_21G1_02_00_LLAMA_02_00_GENERAL}},
        },

        SIFIVE_EXTENSION(S5V_FDCP|S5V_CFLUSH|S5V_PWRD),
    },

    {
        .name             = "S21",
        .arch             = RV64IMAC|ISA_U|ISA_B,
        .archMask         = 0,  // MISA cannot be changed by software TODO: Update for correct bits that can change
        .archFixed        = ~(ISA_U|ISA_M|ISA_F|ISA_D|ISA_A|ISA_B),
        .bitmanip_version = SIFIVE_BITMANIP_VERSION,
        .bitmanip_absent  = ~(RVBS_Zba|RVBS_Zbb),
        .user_version     = RVUV_2_3,
        .priv_version     = RVPV_1_11,
        .rnmi_version     = RNMI_0_2_1,
        .specificDocs     = SPECIFIC_DOC("SiFive S21 Manual v19.05"),
        .PMP_registers    = 8,
        .tval_ii_code     = True,
        .local_int_num    = 127,
        .time_undefined   = True,
        .lr_sc_grain      = 64,
        .tvec_align       = 64,
        .d_requires_f     = True,
        .mstatus_fs_mode  = RVFS_ALWAYS_DIRTY,
        .numHarts         = 1,  // override with numHarts parameter
        .ecode_mask       = 0x1f,
        .ecode_nmi        = 2,
        .ecode_nmi_mask   = 0x3,
        .counteren_mask   = -1,

        // CLINT configuration
        .CLINT_address       = 0x02000000,

        // CLIC configuration
        .CLIC_version        = RVCLC_20180831,
        .CLICLEVELS          = 16,
        .CLICANDBASIC        = True,
        .CLICINTCTLBITS      = 5,
        .CLICCFGMBITS        = 0,
        .CLICCFGLBITS        = 2,
        .CLICSELHVEC         = True,
        .CLICXNXTI           = True,
        .intthresh_undefined = True,
        .mclicbase_undefined = True,
        .posedge_0_63        = 0x100f,

        // CSR configuration
        .csr = {
            .mclicbase = {u32 : {bits : 0x02800000}},
            .mvendorid = {u32 : {bits : SIFIVE_JEDEC}},
            .marchid   = {u32 : {bits : SIFIVE_VENDOR_ID_2_SERIES}},
            .mimpid    = {u32 : {bits : SIFIVE_21G1_02_00_LLAMA_02_00_GENERAL}},
        },
        .csrMask = {
            .mtvec = {u64 : {bits : 0x0000003fffffffffULL}},
        },

        SIFIVE_EXTENSION(S5V_PWRD)
    },

    {
        .name             = "S51",
        .arch             = RV64IMAC|ISA_U,
        .archMask         = 0,  // MISA cannot be changed by software TODO: Update for correct bits that can change
        .archFixed        = ~(ISA_U|ISA_A|ISA_M|ISA_F|ISA_D),
        .user_version     = RVUV_2_3,
        .priv_version     = RVPV_1_11,
        .rnmi_version     = RNMI_0_2_1,
        .specificDocs     = SPECIFIC_DOC("SiFive S51 (E51) Core Complex Manual v2p0"),
        .PMP_registers    = 8,
        .tval_ii_code     = True,
        .local_int_num    = 16,
        .time_undefined   = True,
        .lr_sc_grain      = 64,
        .tvec_align       = 64,
        .d_requires_f     = True,
        .mstatus_fs_mode  = RVFS_ALWAYS_DIRTY,
        .numHarts         = 1,  // override with numHarts parameter
        .ecode_mask       = 0x1f,
        .ecode_nmi        = 2,
        .ecode_nmi_mask   = 0x3,
        .counteren_mask   = -1,

        // CSR configuration
        .csr = {
            .mclicbase = {u32 : {bits : 0x02800000}},
            .mvendorid = {u32 : {bits : SIFIVE_JEDEC}},
            .marchid   = {u32 : {bits : SIFIVE_VENDOR_ID_3_5_SERIES}},
            .mimpid    = {u32 : {bits : SIFIVE_21G1_02_00_LLAMA_02_00_GENERAL}},
        },
        .csrMask = {
            .mtvec = {u64 : {bits : 0x0000003fffffffffULL}},
        },

        SIFIVE_EXTENSION(S5V_BPM|S5V_FDCP|S5V_CEASE)
    },

    {
        .name             = "S54",
        .arch             = RV64GC|ISA_U,
        .archMask         = 0,  // MISA cannot be changed by software TODO: Update for correct bits that can change
        .archFixed        = ~(ISA_U|ISA_A|ISA_M|ISA_F|ISA_D),
        .user_version     = RVUV_2_3,
        .priv_version     = RVPV_1_11,
        .rnmi_version     = RNMI_0_2_1,
        .specificDocs     = SPECIFIC_DOC("SiFive S54 Manual v19.05"),
        .PMP_registers    = 8,
        .tval_ii_code     = True,
        .local_int_num    = 16,
        .time_undefined   = True,
        .lr_sc_grain      = 64,
        .tvec_align       = 64,
        .d_requires_f     = True,
        .mstatus_fs_mode  = RVFS_ALWAYS_DIRTY,
        .numHarts         = 1,  // override with numHarts parameter
        .ecode_mask       = 0x1f,
        .ecode_nmi        = 2,
        .ecode_nmi_mask   = 0x3,
        .counteren_mask   = -1,

        // CSR configuration
        .csr = {
            .mclicbase = {u32 : {bits : 0x02800000}},
            .mvendorid = {u32 : {bits : SIFIVE_JEDEC}},
            .marchid   = {u32 : {bits : SIFIVE_VENDOR_ID_3_5_SERIES}},
            .mimpid    = {u32 : {bits : SIFIVE_21G1_02_00_LLAMA_02_00_GENERAL}},
        },
        .csrMask = {
            .mtvec = {u64 : {bits : 0x0000003fffffffffULL}},
        },

        SIFIVE_EXTENSION(0)
    },

    {
        .name             = "S76",
        .arch             = RV64GC|ISA_U|ISA_B,
        .archMask         = 0,  // MISA cannot be changed by software TODO: Update for correct bits that can change
        .archFixed        = ~(ISA_U|ISA_B|ISA_M|ISA_F|ISA_D),
        .bitmanip_version = SIFIVE_BITMANIP_VERSION,
        .bitmanip_absent  = ~(RVBS_Zba|RVBS_Zbb),
        .user_version     = RVUV_2_3,
        .priv_version     = RVPV_1_11,
        .rnmi_version     = RNMI_0_2_1,
        .specificDocs     = SPECIFIC_DOC("SiFive S76 Manual v19.05"),
        .PMP_registers    = 8,
        .tval_ii_code     = True,
        .local_int_num    = 16,
        .time_undefined   = True,
        .lr_sc_grain      = 64,
        .tvec_align       = 64,
        .d_requires_f     = True,
        .mstatus_fs_mode  = RVFS_ALWAYS_DIRTY,
        .numHarts         = 1,  // override with numHarts parameter
        .ecode_mask       = 0x1f,
        .ecode_nmi        = 2,
        .ecode_nmi_mask   = 0x3,
        .counteren_mask   = -1,

        // CSR configuration
        .csr = {
            .mclicbase = {u32 : {bits : 0x02800000}},
            .mvendorid = {u32 : {bits : SIFIVE_JEDEC}},
            .marchid   = {u32 : {bits : SIFIVE_VENDOR_ID_7_SERIES}},
            .mimpid    = {u32 : {bits : SIFIVE_21G1_02_00_LLAMA_02_00_GENERAL}},
        },
        .csrMask = {
            .mtvec = {u64 : {bits : 0x0000003fffffffffULL}},
        },

        SIFIVE_EXTENSION(S5V_FDCP|S5V_CFLUSH|S5V_PWRD),
    },

    {
        .name             = "U54",
        .arch             = RV64GC|ISA_U|ISA_S,
        .archMask         = 0,  // MISA cannot be changed by software TODO: Update for correct bits that can change
        .archFixed        = ~(ISA_A|ISA_M|ISA_F|ISA_D),
        .user_version     = RVUV_2_3,
        .priv_version     = RVPV_1_11,
        .rnmi_version     = RNMI_0_2_1,
        .specificDocs     = SPECIFIC_DOC("SiFive U54-MC Core Complex Manual v1p0"),
        .PMP_registers    = 8,
        .tval_ii_code     = True,
        .local_int_num    = 48,
        .time_undefined   = True,
        .lr_sc_grain      = 64,
        .tvec_align       = 64,
        .d_requires_f     = True,
        .mstatus_fs_mode  = RVFS_ALWAYS_DIRTY,
        .numHarts         = 1,  // override with numHarts parameter
        .Sv_modes         = RISCV_VMM_SV39,
        .ecode_mask       = 0x1f,
        .ecode_nmi        = 2,
        .ecode_nmi_mask   = 0x3,
        .counteren_mask   = -1,

        // CSR configuration
        .csr = {
            .mclicbase = {u32 : {bits : 0x02800000}},
            .mvendorid = {u32 : {bits : SIFIVE_JEDEC}},
            .marchid   = {u32 : {bits : SIFIVE_VENDOR_ID_3_5_SERIES}},
            .mimpid    = {u32 : {bits : SIFIVE_21G1_02_00_LLAMA_02_00_GENERAL}},
        },
        .csrMask = {
            .mtvec = {u64 : {bits : 0x0000003fffffffffULL}},
            .stvec = {u64 : {bits : 0xffffffffffffffffULL}},
        },

        SIFIVE_EXTENSION(S5V_BPM|S5V_FDCP|S5V_CFLUSH|S5V_CEASE)
    },

    {
        .name             = "U74",
        .arch             = RV64GC|ISA_U|ISA_S|ISA_B,
        .archMask         = 0,  // MISA cannot be changed by software TODO: Update for correct bits that can change
        .archFixed        = ~(ISA_M|ISA_F|ISA_D|ISA_B),
        .bitmanip_version = SIFIVE_BITMANIP_VERSION,
        .bitmanip_absent  = ~(RVBS_Zba|RVBS_Zbb),
        .user_version     = RVUV_2_3,
        .priv_version     = RVPV_1_11,
        .rnmi_version     = RNMI_0_2_1,
        .specificDocs     = SPECIFIC_DOC("SiFive U74 Manual v19.05"),
        .PMP_registers    = 8,
        .tval_ii_code     = True,
        .local_int_num    = 48,
        .time_undefined   = True,
        .lr_sc_grain      = 64,
        .tvec_align       = 64,
        .d_requires_f     = True,
        .mstatus_fs_mode  = RVFS_ALWAYS_DIRTY,
        .numHarts         = 1,  // override with numHarts parameter
        .Sv_modes         = RISCV_VMM_SV39,
        .ecode_mask       = 0x1f,
        .ecode_nmi        = 2,
        .ecode_nmi_mask   = 0x3,
        .counteren_mask   = -1,

        // CSR configuration
        .csr = {
            .mclicbase = {u32 : {bits : 0x02800000}},
            .mvendorid = {u32 : {bits : SIFIVE_JEDEC}},
            .marchid   = {u32 : {bits : SIFIVE_VENDOR_ID_7_SERIES}},
            .mimpid    = {u32 : {bits : SIFIVE_21G1_02_00_LLAMA_02_00_GENERAL}},
        },
        .csrMask = {
            .mtvec = {u64 : {bits : 0x0000003fffffffffULL}},
            .stvec = {u64 : {bits : 0xffffffffffffffffULL}},
        },

        SIFIVE_EXTENSION(S5V_BPM|S5V_FDCP|S5V_CFLUSH|S5V_CEASE|S5V_PWRD),
    },


    {
        .name            = "X280",
        .arch            = ISA_U|ISA_S|RV64GC|ISA_B|ISA_V,
        .archMask        = 0,
        .archFixed       = ~(ISA_A|ISA_M),
        .bitmanip_version = RVBV_0_94,
        .bitmanip_absent  = ~(RVBS_Zba|RVBS_Zbb),
        .user_version    = RVUV_2_3,
        .priv_version    = RVPV_1_11,
        .specificDocs    = specificDocsX280,
        .PMP_registers   = 8,
        .tval_ii_code    = True,
        .local_int_num   = 48,
        .time_undefined  = True,
        .lr_sc_grain     = 64,
        .tvec_align      = 64,
        .d_requires_f    = True,
        .mstatus_fs_mode = RVFS_ALWAYS_DIRTY,
        .Sv_modes        = RISCV_VMM_SV39|RISCV_VMM_SV48,
        .numHarts        = 1,  // override with numHarts parameter
        .ecode_mask      = 0x1f,
        .counteren_mask  = -1,
        .csrMask = {
            .mtvec = {u64 : {bits : 0x0000003fffffffffULL}},
            .stvec = {u64 : {bits : 0xffffffffffffffffULL}},
        },
        .csr = {
            .mvendorid = {u32 : {bits : SIFIVE_JEDEC}},
            .marchid   = {u32 : {bits : SIFIVE_VENDOR_ID_X200_SERIES}},
            .mimpid    = {u32 : {bits : 0x04210430}},
        },
        SIFIVE_VECTOR_CONFIG,
        SIFIVE_EXTENSION(S5V_INST | S5V_FDCP | S5V_BPM),
    },

    {
        .name            = "P550",
        .arch            = ISA_U|ISA_S|RV64GC|ISA_B,
        .archMask        = 0,
        .archFixed       = ~(ISA_A|ISA_M),
        .bitmanip_version = RVBV_0_94,
        .bitmanip_absent  = ~(RVBS_Zba|RVBS_Zbb),
        .user_version    = RVUV_2_3,
        .priv_version    = RVPV_1_11,
        .specificDocs    = specificDocsP550,
        .PMP_registers   = 8,
        .tval_ii_code    = True,
        .local_int_num   = 48,
        .time_undefined  = True,
        .lr_sc_grain     = 64,
        .tvec_align      = 64,
        .d_requires_f    = True,
        .mstatus_fs_mode = RVFS_ALWAYS_DIRTY,
        .Sv_modes        = RISCV_VMM_SV39|RISCV_VMM_SV48,
        .numHarts        = 1,  // override with numHarts parameter
        .ecode_mask      = 0x1f,
        .counteren_mask  = -1,
        .csrMask = {
            .mtvec = {u64 : {bits : 0x0000003fffffffffULL}},
            .stvec = {u64 : {bits : 0xffffffffffffffffULL}},
        },
        .csr = {
            .mvendorid = {u32 : {bits : SIFIVE_JEDEC}},
            .marchid   = {u32 : {bits : SIFIVE_VENDOR_ID_P500_SERIES}},
            .mimpid    = {u32 : {bits : 0x05210714}},
        },
        SIFIVE_EXTENSION(S5V_INST | S5V_FDCP | S5V_BPM),
    },

    {0} // null terminator
};

//
// This returns the supported configuration list
//
riscvConfigCP riscvGetConfigList(riscvP riscv) {
    return configList;
}


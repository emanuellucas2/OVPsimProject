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

// VMI header files
#include "vmi/vmiDoc.h"

// model header files
#include "andesConfig.h"
#include "andesVariant.h"

// base model header files
#include "riscvConfig.h"
#include "riscvVariant.h"


//
// Emit common restrictions
//
static void restrictionsCommon(riscvP riscv, vmiDocNodeP node) {

    vmidocAddText(
        node,
        "Andes-specific cache, local memory and ECC behavior is not yet "
        "implemented, except for CSR state."
    );

    vmidocAddText(
        node,
        "Andes Performance and Code Dense instructions and associated CSR "
        "state are implemented, but the EXEC.IT instruction supports in-memory "
        "table mode using the uitb CSR only (not hardwired mode)."
    );

    vmidocAddText(
        node,
        "PMP and PMA accesses that any-byte match but do not all-byte match "
        "are broken into separate smaller accesses that follow all-byte match "
        "rules."
    );
}

//
// Emit initial variant restrictions
//
static RV_DOC_FN(restrictionsInitial) {

    vmidocAddText(
        node,
        "This variant is under development. It may not be complete."
    );

    restrictionsCommon(riscv, node);
}
//
// Initial Variant
//
static const char *specificDocsInitial[] = {
    "---- This is an initial configuration for the variant",
    0
};

//
// Emit N-variant restrictions
//
static RV_DOC_FN(restrictionsN) {
    restrictionsCommon(riscv, node);
}

//
// Emit A-variant restrictions
//
static RV_DOC_FN(restrictionsA) {

    vmidocAddText(
        node,
        "This variant is under development. It includes Supervisor mode and "
        "associated standard RISC-V features, but some Andes-specific CSRs "
        "are not yet implemented."
    );

    restrictionsCommon(riscv, node);
}

//
// N25 variant documentation
//
static const char *specificDocsN25[] = {
    "---- AndesCore_N25_DS130_V1.0 DS130-10",
    "---- AndeStar V5 Instruction Extension Specification (UMxxx-0.4, 2018-05-30)",
    "---- AndeStar V5 Architecture and CSR Definitions (UM164-152, 2019-07-18)"
    "---- AndeStar V5 Vector INT4 Load Extension (v0.2)",
    "---- AndeStar V5 BFLOAT16 Conversion Extension (v0.4)",
    0
};

//
// NX25 variant documentation
//
static const char *specificDocsNX25[] = {
    "---- AndesCore_NX25_DS131_V1.0 DS131-10",
    "---- AndeStar V5 Instruction Extension Specification (UMxxx-0.4, 2018-05-30)",
    "---- AndeStar V5 Architecture and CSR Definitions (UM164-152, 2019-07-18)",
    "---- AndeStar V5 Vector INT4 Load Extension (v0.2)",
    "---- AndeStar V5 BFLOAT16 Conversion Extension (v0.4)",
    0
};

//
// A25 variant documentation
//
static const char *specificDocsA25[] = {
    "---- AndesCore_A25_DS141_V1.1 DS141-11",
    "---- AndeStar V5 Instruction Extension Specification (UMxxx-0.4, 2018-05-30)",
    "---- AndeStar V5 Architecture and CSR Definitions (UM164-152, 2019-07-18)",
    "---- AndeStar V5 Vector INT4 Load Extension (v0.2)",
    "---- AndeStar V5 BFLOAT16 Conversion Extension (v0.4)",
    0
};

//
// AX25 variant documentation
//
static const char *specificDocsAX25[] = {
    "---- AndesCore_AX25_DS142_V1.1 DS142-11",
    "---- AndeStar V5 Instruction Extension Specification (UMxxx-0.4, 2018-05-30)",
    "---- AndeStar V5 Architecture and CSR Definitions (UM164-152, 2019-07-18)",
    "---- AndeStar V5 Vector INT4 Load Extension (v0.2)",
    "---- AndeStar V5 BFLOAT16 Conversion Extension (v0.4)",
    0
};

//
// NX27 variant documentation
//
static const char *specificDocsNX27V[] = {
    "---- AndesCore_NX27V_DS168-V0.5 (DS168-05, 2021-05-28)",
    "---- AndeStar V5 Instruction Extension Specification (UM165-1.4, 2020-11-19)",
    "---- AndeStar V5 System Privileged Architecture and CSR Definitions (SPA_UM164_V1.5.27-20210609)",
    "---- AndeStar V5 Vector INT4 Load Extension (v0.2)",
    "---- AndeStar V5 BFLOAT16 Conversion Extension (v0.4)",
    0
};
//
// Common Andes variant configuration
//
#define ANDES_COMMON_CONFIG(_NAME, _ARCH, _NUMHARTS) \
    .name             = _NAME,                          \
    .arch             = _ARCH,                          \
    .numHarts         = _NUMHARTS,                      \
    .archMask         = RV_ARCH_MASK_DEFAULT,           \
    .user_version     = RVUV_2_2,                       \
    .priv_version     = RVPV_1_11,                      \
    .tval_ii_code     = True,                           \
    .counteren_mask   = 0x7f,                           \
    .trigger_num      = 4,                              \
    .tinfo            = 0x3d, /* types 0, 2, 3, 4, 5 */ \
    .mcontext_bits    = ((_ARCH)&RV64) ? 13 : 6,        \
    .scontext_bits    = ((_ARCH)&RV64) ? 34 : 16,       \
    .mvalue_bits      = ((_ARCH)&RV64) ? 13 : 6,        \
    .svalue_bits      = ((_ARCH)&RV64) ? 34 : 16,       \
    .mcontrol_maskmax = 63,                             \
    .external_int_id  = True

//
// Common settings for all Andes mmsc_cfg fields
//
#define ANDES_COMMON_MMSC_CFG \
        ECD   :1,             \
        PFT   :1,             \
        HSP   :1,             \
        VPLIC :1,             \
        EV5MPE:1,             \
        PMNDS :1

//
// Vector configuration for Andes cores
//
#define ANDES_VECTOR_CONFIG \
    .vect_version    = RVVV_0_8, \
    .Zvlsseg         = 0,        \
    .Zvamo           = 0,        \
    .Zvediv          = 0,        \
    .Zvqmac          = 1,        \
    .require_vstart0 = True,     \
    .unitStrideOnly  = True,     \
    .noFaultOnlyFirst= True,     \
    .ELEN            = 32,       \
    .SLEN            = 512,      \
    .VLEN            = 512

//
// Vector configuration for NX27V cores (2021-01-29 in specification)
//
#define ANDES_VECTOR_CONFIG_NX27V \
    .vect_version    = RVVV_1_0_20210130, \
    .Zvlsseg         = 0,                 \
    .Zvamo           = 0,                 \
    .Zvediv          = 0,                 \
    .Zvqmac          = 1,                 \
    .require_vstart0 = True,              \
    .unitStrideOnly  = False,             \
    .noFaultOnlyFirst= False,             \
    .ELEN            = 32,                \
    .SLEN            = 512,               \
    .VLEN            = 512

#define ANDES_CONFIG_AX45MP(_NUMHARTS)                                   \
    ANDES_COMMON_CONFIG(                                                 \
        "AX45MPx"#_NUMHARTS,                                             \
        ISA_U|ISA_S|RV64IMAC|ISA_F|ISA_D|ISA_N|ISA_X,                    \
        _NUMHARTS                                                        \
    ),                                                                   \
    .csr = {                                                             \
        .mvendorid   = {u64 : {bits   : 0x31e}},                         \
        .marchid     = {u64 : {bits   : 0x8000000000008a45ULL}},         \
        .mimpid      = {u64 : {bits   : 0x10}},                          \
        .mstatus     = {u64 : {fields : {MPP:3}}},                       \
    },                                                                   \
    .specificDocs    = specificDocsInitial,                              \
    .restrictionsCB  = restrictionsInitial,                              \
                                                                         \
    .extensionConfigs = (riscvExtConfigCP[]){                            \
                                                                         \
        &(const riscvExtConfig){                                         \
            .id             = ANDES_OVP_CONFIG_ID,                       \
            .userData       = &(const andesConfig){                      \
                .csr = {                                                 \
                    .micm_cfg= {                                         \
                        u32 : {                                          \
                            fields : {                                   \
                               SET:2, WAY:1, SZ:4, LCK:1,                \
                               LMB:1, LMSZ:10                            \
                            }                                            \
                        }                                                \
                    },                                                   \
                    .mdcm_cfg= {                                         \
                        u32 : {                                          \
                            fields : {                                   \
                               SET:1, WAY:3, SZ:4, LCK:1,                \
                               LMB:1, LMSZ:10                            \
                            }                                            \
                        }                                                \
                    },                                                   \
                    .mmsc_cfg= {                                         \
                        u64 : {                                          \
                            fields : {                                   \
                               ANDES_COMMON_MMSC_CFG,                    \
                               CCTLCSR:1, EDSP:1, DPMA:1,                \
                               L2CMP_CFG:1, L2C:1,                       \
                               CORE_PCLUS:_NUMHARTS-1                    \
                            }                                            \
                        }                                                \
                    },                                                   \
                },                                                       \
                .csrMask = {                                             \
                    .milmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}}, \
                    .mdlmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}}, \
                }                                                        \
            }                                                            \
        },                                                               \
        0                                                                \
    }

//
// Defined configurations
//
static const riscvConfig configList[] = {

    {
        ANDES_COMMON_CONFIG(
            "N25",
            ISA_U|RV32IMAC|ISA_X,
            0
        ),
        .csr = {
            .mvendorid   = {u32 : {bits   : 0x31e}},
            .marchid     = {u32 : {bits   : 0x10000025}},
            .mimpid      = {u32 : {bits   : 0x20}},
            .mstatus     = {u32 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsN25,
        .restrictionsCB  = restrictionsN,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .csr = {
                        .mmsc_cfg = {
                            u32 : {
                                fields : {
                                    ANDES_COMMON_MMSC_CFG
                                }
                            }
                        },
                    },
                    .csrMask = {
                        .milmb = {u32 : {fields : {ECCEN:-1, RWECC:-1, EN:-1}}},
                        .mdlmb = {u32 : {fields : {ECCEN:-1, RWECC:-1, EN:-1}}},
                    }
                }
            },

            0   // KEEP LAST: terminator
        }
    },
    {
        ANDES_COMMON_CONFIG(
            "NX25",
            ISA_U|RV64IMAC|ISA_X,
            0
        ),
        .csr = {
            .mvendorid   = {u64 : {bits   : 0x31e}},
            .marchid     = {u64 : {bits   : 0x1000000000008025ULL}},
            .mimpid      = {u64 : {bits   : 0x10}},
            .mstatus     = {u64 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsNX25,
        .restrictionsCB  = restrictionsN,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .csr = {
                        .mmsc_cfg = {
                            u32 : {
                                fields : {
                                    ANDES_COMMON_MMSC_CFG
                                }
                            }
                        },
                    },
                    .csrMask = {
                        .milmb = {u32 : {fields : {ECCEN:-1, RWECC:-1, EN:-1}}},
                        .mdlmb = {u32 : {fields : {ECCEN:-1, RWECC:-1, EN:-1}}},
                    }
                }
            },

            0   // KEEP LAST: terminator
        }
    },
    {
        ANDES_COMMON_CONFIG(
            "N25F",
            ISA_U|RV32IMAC|ISA_X|ISA_F|ISA_D,
            0
        ),
        .csr = {
            .mvendorid   = {u32 : {bits   : 0x31e}},
            .marchid     = {u32 : {bits   : 0x10000025}},
            .mimpid      = {u32 : {bits   : 0x20}},
            .mstatus     = {u32 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsN25,
        .restrictionsCB  = restrictionsN,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .csr = {
                        .micm_cfg  = {u32 : {bits   : 0x51acb}},
                        .mdcm_cfg  = {u32 : {bits   : 0x51ada}},
                        .mmsc_cfg  = {
                            u32 : {
                                fields : {
                                    ANDES_COMMON_MMSC_CFG,
                                    ECC:1, CCTLCSR:1, EFHW:1
                                }
                            }
                        },
                    },
                    .csrMask = {
                        .milmb = {u32 : {fields : {ECCEN:-1, RWECC:-1, EN:-1}}},
                        .mdlmb = {u32 : {fields : {ECCEN:-1, RWECC:-1, EN:-1}}},
                    }
                }
            },

            0   // KEEP LAST: terminator
        }
    },
    {
        ANDES_COMMON_CONFIG(
            "NX25F",
            ISA_U|RV64IMAC|ISA_X|ISA_F|ISA_D,
            0
        ),
        .csr = {
            .mvendorid   = {u64 : {bits   : 0x31e}},
            .marchid     = {u64 : {bits   : 0x1000000000008025ULL}},
            .mimpid      = {u64 : {bits   : 0x10}},
            .mstatus     = {u64 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsNX25,
        .restrictionsCB  = restrictionsN,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .csr = {
                        .mmsc_cfg = {
                            u32 : {
                                fields : {
                                    ANDES_COMMON_MMSC_CFG
                                }
                            }
                        },
                    },
                    .csrMask = {
                        .milmb = {u32 : {fields : {ECCEN:-1, RWECC:-1, EN:-1}}},
                        .mdlmb = {u32 : {fields : {ECCEN:-1, RWECC:-1, EN:-1}}},
                    }
                }
            },

            0   // KEEP LAST: terminator
        }
    },
    {
        ANDES_COMMON_CONFIG(
            "A25",
            ISA_U|ISA_S|RV32IMAC|ISA_X,
            RV_NUMHARTS_0
        ),
        .csr = {
            .mvendorid   = {u32 : {bits   : 0x31e}},
            .marchid     = {u32 : {bits   : 0x10000a25}},
            .mimpid      = {u32 : {bits   : 0x20}},
            .mstatus     = {u32 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsA25,
        .restrictionsCB  = restrictionsA,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .csr = {
                        .micm_cfg = {u64 : {bits   : 0x51acb}},
                        .mdcm_cfg = {u64 : {bits   : 0x51ada}},
                        .mmsc_cfg = {
                            u32 : {
                                fields : {
                                    ANDES_COMMON_MMSC_CFG,
                                    ECC:1, CCTLCSR:1, EFHW:1, EDSP:1
                                }
                            }
                        },
                    },
                    .csrMask = {
                        .milmb = {u32 : {fields : {ECCEN:-1, RWECC:-1, EN:-1}}},
                        .mdlmb = {u32 : {fields : {ECCEN:-1, RWECC:-1, EN:-1}}},
                    }
                }
            },

            0   // KEEP LAST: terminator
        }
    },
    {
        ANDES_COMMON_CONFIG(
            "AX25",
            ISA_U|ISA_S|RV64IMAC|ISA_X,
            RV_NUMHARTS_0
        ),
        .csr = {
            .mvendorid   = {u64 : {bits   : 0x31e}},
            .marchid     = {u64 : {bits   : 0x1000000000008a25ULL}},
            .mimpid      = {u64 : {bits   : 0x10}},
            .mstatus     = {u64 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsAX25,
        .restrictionsCB  = restrictionsA,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .csr = {
                        .micm_cfg= {u32 : {bits   : 0x51acb}},
                        .mdcm_cfg= {u32 : {bits   : 0x51ada}},
                        .mmsc_cfg = {
                            u32 : {
                                fields : {
                                    ANDES_COMMON_MMSC_CFG,
                                    ECC:1, CCTLCSR:1, EFHW:1, EDSP:1
                                }
                            }
                        },
                    },
                    .csrMask = {
                        .milmb = {u32 : {fields : {ECCEN:-1, RWECC:-1, EN:-1}}},
                        .mdlmb = {u32 : {fields : {ECCEN:-1, RWECC:-1, EN:-1}}},
                    }
                }
            },

            0   // KEEP LAST: terminator
        }
    },
    {
        ANDES_COMMON_CONFIG(
            "A25F",
            ISA_U|ISA_S|RV32IMAC|ISA_X|ISA_F|ISA_D,
            RV_NUMHARTS_0
        ),
        .csr = {
            .mvendorid   = {u32 : {bits   : 0x31e}},
            .marchid     = {u32 : {bits   : 0x10000a25}},
            .mimpid      = {u32 : {bits   : 0x20}},
            .mstatus     = {u32 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsA25,
        .restrictionsCB  = restrictionsA,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .csr = {
                        .mmsc_cfg = {
                            u32 : {
                                fields : {
                                    ANDES_COMMON_MMSC_CFG
                                }
                            }
                        },
                    },
                    .csrMask = {
                        .milmb = {u32 : {fields : {ECCEN:-1, RWECC:-1, EN:-1}}},
                        .mdlmb = {u32 : {fields : {ECCEN:-1, RWECC:-1, EN:-1}}},
                    }
                }
            },

            0   // KEEP LAST: terminator
        }
    },
    {
        ANDES_COMMON_CONFIG(
            "AX25F",
            ISA_U|ISA_S|RV64IMAC|ISA_X|ISA_F|ISA_D,
            RV_NUMHARTS_0
        ),
        .csr = {
            .mvendorid   = {u64 : {bits   : 0x31e}},
            .marchid     = {u64 : {bits   : 0x1000000000008a25ULL}},
            .mimpid      = {u64 : {bits   : 0x10}},
            .mstatus     = {u64 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsAX25,
        .restrictionsCB  = restrictionsA,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .csr = {
                        .mmsc_cfg = {
                            u32 : {
                                fields : {
                                    ANDES_COMMON_MMSC_CFG
                                }
                            }
                        },
                    },
                    .csrMask = {
                        .milmb = {u32 : {fields : {ECCEN:-1, RWECC:-1, EN:-1}}},
                        .mdlmb = {u32 : {fields : {ECCEN:-1, RWECC:-1, EN:-1}}},
                    }
                }
            },

            0   // KEEP LAST: terminator
        }
    },
    {
        // TODO: Implements DSP/SIMD P
        ANDES_COMMON_CONFIG(
            "NX27V",
            ISA_U|RV64IMAC|ISA_X|ISA_V|ISA_F|ISA_D,
            0
        ),
        .csr = {
            .mvendorid   = {u32 : {bits   : 0x31e}},
            .marchid     = {u32 : {bits   : 0x80008027}},
            .mimpid      = {u32 : {bits   : 0x80}},
            .mstatus     = {u32 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsNX27V,
        .restrictionsCB  = restrictionsN,
        ANDES_VECTOR_CONFIG_NX27V,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .PMA_grain  = 10,
                    .csr = {
                        .micm_cfg = {u32 : {bits : 0xada}},
                        .mdcm_cfg = {u32 : {bits : 0x6da}},
                        .mmsc_cfg = {
                            u32 : {
                                fields : {
                                    ANDES_COMMON_MMSC_CFG,
                                    ECC:1, CCTLCSR:1, DPMA:1,
                                    BF16CVT:1, ZFH:1, VL4:1, VECCFG:1, FINV:1
                                }
                            }
                        },
                        .mvec_cfg = {u32 : {bits : 0x28010}},
                    },
                    .csrMask = {
                        .milmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                        .mdlmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                    }
                }
            },
            0   // KEEP LAST: terminator
        }
    },

    //
    // Un-verfied initial placeholders below here
    //

    {
        ANDES_COMMON_CONFIG(
            "N22",
            ISA_U|RV32IMAC|ISA_X,
            0
        ),
        .csr = {
            .mvendorid   = {u32 : {bits   : 0x31e}},
            .marchid     = {u32 : {bits   : 0x80000022}},
            .mimpid      = {u32 : {bits   : 0x20}},
            .mstatus     = {u32 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsInitial,
        .restrictionsCB  = restrictionsInitial,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .csr = {
                        .mmsc_cfg = {
                            u32 : {
                                fields : {
                                    ANDES_COMMON_MMSC_CFG,
                                    CLIC:1, ECLIC:1
                                }
                            }
                        },
                        .micm_cfg = {u32 : {bits : 0x510cb}},
                        .mdcm_cfg = {u32 : {bits : 0x51000}},
                    },
                    .csrMask = {
                        .milmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                        .mdlmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                    }
                }
            },

            0   // KEEP LAST: terminator
        }
    },
    {
        ANDES_COMMON_CONFIG(
            "A27",
            ISA_U|ISA_S|RV32IMAC|ISA_F|ISA_D|ISA_X,
            RV_NUMHARTS_0
        ),
        .csr = {
            .mvendorid   = {u32 : {bits   : 0x31e}},
            .marchid     = {u32 : {bits   : 0x80000a27}},
            .mimpid      = {u32 : {bits   : 0x20}},
            .mstatus     = {u32 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsInitial,
        .restrictionsCB  = restrictionsInitial,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .csr = {
                        .micm_cfg = {u64 : {bits   : 0x5130b}},
                        .mdcm_cfg = {u64 : {bits   : 0x5131a}},
                        .mmsc_cfg = {
                            u32 : {
                                fields : {
                                    ANDES_COMMON_MMSC_CFG,
                                    CCTLCSR:1, EFHW:1, EDSP:1, DPMA:1
                                }
                            }
                        },
                    },
                    .csrMask = {
                        .milmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                        .mdlmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                    }
                }
            },

            0   // KEEP LAST: terminator
        }
    },
    {
        ANDES_COMMON_CONFIG(
            "A45",
            ISA_U|ISA_S|RV32IMAC|ISA_F|ISA_D|ISA_N|ISA_X,
            RV_NUMHARTS_0
        ),
        .csr = {
            .mvendorid   = {u32 : {bits   : 0x31e}},
            .marchid     = {u32 : {bits   : 0x80000a45}},
            .mimpid      = {u32 : {bits   : 0x20}},
            .mstatus     = {u32 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsInitial,
        .restrictionsCB  = restrictionsInitial,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .csr = {
                        .micm_cfg = {u64 : {bits   : 0x5130a}},
                        .mdcm_cfg = {u64 : {bits   : 0x51319}},
                        .mmsc_cfg = {
                            u32 : {
                                fields : {
                                    ANDES_COMMON_MMSC_CFG,
                                    CCTLCSR:1, EDSP:1, DPMA:1
                                }
                            }
                        },
                    },
                    .csrMask = {
                        .milmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                        .mdlmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                    }
                }
            },

            0   // KEEP LAST: terminator
        }
    },
    {
        ANDES_COMMON_CONFIG(
            "AX27",
            ISA_U|ISA_S|RV64IMAC|ISA_F|ISA_D|ISA_X,
            RV_NUMHARTS_0
        ),
        .csr = {
            .mvendorid   = {u64 : {bits   : 0x31e}},
            .marchid     = {u64 : {bits   : 0x8000000000008a27ULL}},
            .mimpid      = {u64 : {bits   : 0x10}},
            .mstatus     = {u64 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsInitial,
        .restrictionsCB  = restrictionsInitial,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .csr = {
                        .micm_cfg= {u32 : {bits   : 0x5130b}},
                        .mdcm_cfg= {u32 : {bits   : 0x5131a}},
                        .mmsc_cfg = {
                            u32 : {
                                fields : {
                                    ANDES_COMMON_MMSC_CFG,
                                    CCTLCSR:1, EFHW:1, EDSP:1, DPMA:1
                                }
                            }
                        },
                    },
                    .csrMask = {
                        .milmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                        .mdlmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                    }
                }
            },

            0   // KEEP LAST: terminator
        }
    },
    {
        ANDES_COMMON_CONFIG(
            "AX45",
            ISA_U|ISA_S|RV64IMAC|ISA_F|ISA_D|ISA_N|ISA_X,
            RV_NUMHARTS_0
        ),
        .csr = {
            .mvendorid   = {u64 : {bits   : 0x31e}},
            .marchid     = {u64 : {bits   : 0x8000000000008a45ULL}},
            .mimpid      = {u64 : {bits   : 0x10}},
            .mstatus     = {u64 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsInitial,
        .restrictionsCB  = restrictionsInitial,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .csr = {
                        .micm_cfg= {u32 : {bits   : 0x5130a}},
                        .mdcm_cfg= {u32 : {bits   : 0x51319}},
                        .mmsc_cfg = {
                            u32 : {
                                fields : {
                                    ANDES_COMMON_MMSC_CFG,
                                    CCTLCSR:1, EDSP:1, DPMA:1
                                }
                            }
                        },
                    },
                    .csrMask = {
                        .milmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                        .mdlmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                    }
                }
            },

            0   // KEEP LAST: terminator
        }
    },
    {   ANDES_CONFIG_AX45MP(1) },
    {   ANDES_CONFIG_AX45MP(2) },
    {   ANDES_CONFIG_AX45MP(4) },
    {
        ANDES_COMMON_CONFIG(
            "D25F",
            ISA_U|RV64IMAC|ISA_F|ISA_D|ISA_X,
            RV_NUMHARTS_0
        ),
        .csr = {
            .mvendorid   = {u64 : {bits   : 0x31e}},
            .marchid     = {u64 : {bits   : 0x80000025}},
            .mimpid      = {u64 : {bits   : 0x10}},
            .mstatus     = {u64 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsInitial,
        .restrictionsCB  = restrictionsInitial,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .csr = {
                        .micm_cfg= {u32 : {bits   : 0x51acb}},
                        .mdcm_cfg= {u32 : {bits   : 0x51ada}},
                        .mmsc_cfg = {
                            u32 : {
                                fields : {
                                    ANDES_COMMON_MMSC_CFG,
                                    ECC:1, CCTLCSR:1, EFHW:1, EDSP:1
                                }
                            }
                        },
                    },
                    .csrMask = {
                        .milmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                        .mdlmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                    }
                }
            },

            0   // KEEP LAST: terminator
        }
    },
    {
        ANDES_COMMON_CONFIG(
            "D45",
            ISA_U|ISA_S|RV64IMAC|ISA_F|ISA_D|ISA_N|ISA_X,
            RV_NUMHARTS_0
        ),
        .csr = {
            .mvendorid   = {u64 : {bits   : 0x31e}},
            .marchid     = {u64 : {bits   : 0x80000045ULL}},
            .mimpid      = {u64 : {bits   : 0x10}},
            .mstatus     = {u64 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsInitial,
        .restrictionsCB  = restrictionsInitial,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .csr = {
                        .micm_cfg= {u32 : {bits   : 0x51acb}},
                        .mdcm_cfg= {u32 : {bits   : 0x51ada}},
                        .mmsc_cfg = {
                            u32 : {
                                fields : {
                                    ANDES_COMMON_MMSC_CFG,
                                    ECC:1, CCTLCSR:1, EFHW:1, EDSP:1
                                }
                            }
                        },
                    },
                    .csrMask = {
                        .milmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                        .mdlmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                    }
                }
            },

            0   // KEEP LAST: terminator
        }
    },
    {
        ANDES_COMMON_CONFIG(
            "NX45",
            ISA_U|ISA_S|RV64GC|ISA_F|ISA_D|ISA_N|ISA_X,
            RV_NUMHARTS_0
        ),
        .csr = {
            .mvendorid   = {u64 : {bits   : 0x31e}},
            .marchid     = {u64 : {bits   : 0x8000000000008045ULL}},
            .mimpid      = {u64 : {bits   : 0x10}},
            .mstatus     = {u64 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsInitial,
        .restrictionsCB  = restrictionsInitial,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .csr = {
                        .micm_cfg= {u32 : {bits   : 0x5130a}},
                        .mdcm_cfg= {u32 : {bits   : 0x51319}},
                        .mmsc_cfg = {
                            u32 : {
                                fields : {
                                    ANDES_COMMON_MMSC_CFG,
                                    CCTLCSR:1, DPMA:1
                                }
                            }
                        },
                    },
                    .csrMask = {
                        .milmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                        .mdlmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                    }
                }
            },

            0   // KEEP LAST: terminator
        }
    },
    {
        ANDES_COMMON_CONFIG(
            "N45",
            ISA_U|ISA_S|RV64GC|ISA_F|ISA_D|ISA_N|ISA_X,
            RV_NUMHARTS_0
        ),
        .csr = {
            .mvendorid   = {u64 : {bits   : 0x31e}},
            .marchid     = {u64 : {bits   : 0x8000000000000045ULL}},
            .mimpid      = {u64 : {bits   : 0x10}},
            .mstatus     = {u64 : {fields : {MPP:3}}},
        },
        .specificDocs    = specificDocsInitial,
        .restrictionsCB  = restrictionsInitial,

        .extensionConfigs = (riscvExtConfigCP[]){

            &(const riscvExtConfig){
                .id             = ANDES_OVP_CONFIG_ID,
                .userData       = &(const andesConfig){
                    .csr = {
                        .micm_cfg= {u32 : {bits   : 0x5130a}},
                        .mdcm_cfg= {u32 : {bits   : 0x51319}},
                        .mmsc_cfg = {
                            u32 : {
                                fields : {
                                    ANDES_COMMON_MMSC_CFG,
                                    CCTLCSR:1, DPMA:1
                                }
                            }
                        },
                    },
                    .csrMask = {
                        .milmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                        .mdlmb    = {u32 : {fields : {ECCEN:-1, RWECC:-1}}},
                    }
                }
            },

            0   // KEEP LAST: terminator
        }
    },
    {0} // null terminator
};

//
// This returns the supported configuration list
//
riscvConfigCP riscvGetConfigList(riscvP riscv) {
    return configList;
}


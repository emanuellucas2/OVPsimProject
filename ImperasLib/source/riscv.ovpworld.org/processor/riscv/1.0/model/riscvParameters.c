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

// standard header files
#include <string.h>
#include <stdio.h>

// Imperas header files
#include "hostapi/impAlloc.h"

// VMI header files
#include "vmi/vmiAttrs.h"
#include "vmi/vmiParameters.h"
#include "vmi/vmiMessage.h"

// model header files
#include "riscvCluster.h"
#include "riscvCSR.h"
#include "riscvFunctions.h"
#include "riscvMessage.h"
#include "riscvParameters.h"
#include "riscvStructure.h"
#include "riscvUtils.h"
#include "riscvVariant.h"
#include "riscvVMConstants.h"


//
// Restrictions on parameters
//
typedef enum riscvParamVariantE {

    RVPV_ALL     = 0,           // present for all variants

                                // PARAMETER IDENTIFIERS
    RVPV_PRE     = (1<<0),      // identifies pre-parameter
    RVPV_VARIANT = (1<<1),      // identifies variant parameter
    RVPV_FP      = (1<<2),      // requires floating point unit
    RVPV_C       = (1<<3),      // requires compressed extension
    RVPV_D       = (1<<4),      // requires double floating point unit
    RVPV_A       = (1<<5),      // requires atomic instructions
    RVPV_K       = (1<<6),      // requires crypto extension
    RVPV_BK      = (1<<7),      // requires bitmanip or crypto extension
    RVPV_32      = (1<<8),      // present if XLEN=32
    RVPV_64      = (1<<9),      // present if XLEN=64
    RVPV_S       = (1<<10),     // requires Supervisor mode
    RVPV_SnotFP  = (1<<11),     // requires Supervisor mode and no floating point
    RVPV_U       = (1<<12),     // requires Supervisor mode
    RVPV_H       = (1<<13),     // requires Hypervisor mode
    RVPV_N       = (1<<14),     // requires User mode interrupts
    RVPV_M       = (1<<15),     // requires M extension
    RVPV_V       = (1<<16),     // requires Vector extension
    RVPV_P       = (1<<17),     // requires DSP extension
    RVPV_MPCORE  = (1<<18),     // present for multicore variants
    RVPV_NMBITS  = (1<<19),     // present if CLICCFGMBITS can be > 0
    RVPV_DEBUG   = (1<<20),     // present if debug mode implemented
    RVPV_TRIG    = (1<<21),     // present if triggers implemented
    RVPV_DBGT    = (1<<22),     // present if debug mode or triggers implemented
    RVPV_RNMI    = (1<<23),     // present if RNMI implemented
    RVPV_CLIC    = (1<<24),     // present if CLIC enabled
    RVPV_CLINT   = (1<<25),     // present if CLINT implemented
    RVPV_CLUSTER = (1<<26),     // present if a cluster
    RVPV_ROOTINT = (1<<27),     // present at root level only
    RVPV_CMOMP   = (1<<28),     // present if Zicbom/Zicbop implemented
    RVPV_CMOZ    = (1<<29),     // present if Zicboz implemented

                                // COMPOSITE PARAMETER IDENTIFIERS
    RVPV_ROOT    = RVPV_ROOTINT|RVPV_CLINT|RVPV_CLIC,
    RVPV_ROOTPRE = RVPV_ROOTINT|RVPV_PRE,
    RVPV_FPV     = RVPV_FP|RVPV_V,
    RVPV_CLIC_NM = RVPV_CLIC|RVPV_NMBITS,
    RVPV_CLIC_S  = RVPV_CLIC|RVPV_S,
    RVPV_CLIC_N  = RVPV_CLIC|RVPV_N,
    RVPV_KV      = RVPV_K|RVPV_V,
    RVPV_64S     = RVPV_64|RVPV_S,
    RVPV_64U     = RVPV_64|RVPV_U,
    RVPV_64H     = RVPV_64|RVPV_H,
    RVPV_TRIG_S  = RVPV_TRIG|RVPV_S,
    RVPV_TRIG_H  = RVPV_TRIG|RVPV_H,
    RVPV_32P     = RVPV_32|RVPV_P,

} riscvParamVariant;

//
// Supported Privileged Architecture variants
//
static vmiEnumParameter privVariants[] = {
    [RVPV_1_10] = {
        .name        = "1.10",
        .value       = RVPV_1_10,
        .description = "Privileged Architecture Version 1.10",
    },
    [RVPV_1_11] = {
        .name        = "1.11",
        .value       = RVPV_20190608,
        .description = "Deprecated and equivalent to 20190608",
    },
    [RVPV_20190405] = {
        .name        = "20190405",
        .value       = RVPV_20190608,
        .description = "Deprecated and equivalent to 20190608",
    },
    [RVPV_20190608] = {
        .name        = "20190608",
        .value       = RVPV_20190608,
        .description = "Privileged Architecture Version Ratified-IMFDQC-and-Priv-v1.11",
    },
    [RVPV_MASTER] = {
        .name        = "master",
        .value       = RVPV_MASTER,
        .description = "Privileged Architecture Master Branch (1.12 draft)",
    },
    // KEEP LAST: terminator
    {0}
};

//
// Supported User Architecture variants
//
static vmiEnumParameter userVariants[] = {
    [RVUV_2_2] = {
        .name        = "2.2",
        .value       = RVUV_2_2,
        .description = "User Architecture Version 2.2",
    },
    [RVUV_2_3] = {
        .name        = "2.3",
        .value       = RVUV_20191213,
        .description = "Deprecated and equivalent to 20191213",
    },
    [RVUV_20190305] = {
        .name        = "20190305",
        .value       = RVUV_20191213,
        .description = "Deprecated and equivalent to 20191213",
    },
    [RVUV_20191213] = {
        .name        = "20191213",
        .value       = RVUV_20191213,
        .description = "User Architecture Version 20191213",
    },
    // KEEP LAST: terminator
    {0}
};

//
// Supported Vector Architecture variants
//
static vmiEnumParameter vectorVariants[] = {
    [RVVV_0_7_1] = {
        .name        = "0.7.1-draft-20190605",
        .value       = RVVV_0_7_1,
        .description = "Vector Architecture Version 0.7.1-draft-20190605",
    },
    [RVVV_0_7_1_P] = {
        .name        = "0.7.1-draft-20190605+",
        .value       = RVVV_0_7_1_P,
        .description = "Vector Architecture Version 0.7.1-draft-20190605 "
                       "with custom features (not for general use)",
    },
    [RVVV_0_8_20190906] = {
        .name        = "0.8-draft-20190906",
        .value       = RVVV_0_8_20190906,
        .description = "Vector Architecture Version 0.8-draft-20190906",
    },
    [RVVV_0_8_20191004] = {
        .name        = "0.8-draft-20191004",
        .value       = RVVV_0_8_20191004,
        .description = "Vector Architecture Version 0.8-draft-20191004",
    },
    [RVVV_0_8_20191117] = {
        .name        = "0.8-draft-20191117",
        .value       = RVVV_0_8_20191117,
        .description = "Vector Architecture Version 0.8-draft-20191117",
    },
    [RVVV_0_8_20191118] = {
        .name        = "0.8-draft-20191118",
        .value       = RVVV_0_8_20191118,
        .description = "Vector Architecture Version 0.8-draft-20191118",
    },
    [RVVV_0_8] = {
        .name        = "0.8",
        .value       = RVVV_0_8,
        .description = "Vector Architecture Version 0.8",
    },
    [RVVV_0_9] = {
        .name        = "0.9",
        .value       = RVVV_0_9,
        .description = "Vector Architecture Version 0.9",
    },
    [RVVV_1_0_20210130] = {
        .name        = "1.0-draft-20210130",
        .value       = RVVV_1_0_20210130,
        .description = "Vector Architecture Version 1.0-draft-20210130",
    },
    [RVVV_1_0_20210608] = {
        .name        = "1.0-rc1-20210608",
        .value       = RVVV_1_0_20210608,
        .description = "Vector Architecture Version 1.0-rc1-20210608",
    },
    [RVVV_MASTER] = {
        .name        = "master",
        .value       = RVVV_MASTER,
        .description = "Vector Architecture Master Branch as of commit "
                       RVVV_MASTER_TAG" (this is subject to change)",
    },
    // KEEP LAST: terminator
    {0}
};

//
// Supported Bit Manipulation Architecture variants
//
static vmiEnumParameter bitmanipVariants[] = {
    [RVBV_0_90] = {
        .name        = "0.90",
        .value       = RVBV_0_90,
        .description = "Bit Manipulation Architecture Version v0.90-20190610",
    },
    [RVBV_0_91] = {
        .name        = "0.91",
        .value       = RVBV_0_91,
        .description = "Bit Manipulation Architecture Version v0.91-20190829",
    },
    [RVBV_0_92] = {
        .name        = "0.92",
        .value       = RVBV_0_92,
        .description = "Bit Manipulation Architecture Version v0.92-20191108",
    },
    [RVBV_0_93_DRAFT] = {
        .name        = "0.93-draft",
        .value       = RVBV_0_93_DRAFT,
        .description = "Bit Manipulation Architecture Version 0.93-draft-20200129",
    },
    [RVBV_0_93] = {
        .name        = "0.93",
        .value       = RVBV_0_93,
        .description = "Bit Manipulation Architecture Version v0.93-20210110",
    },
    [RVBV_0_94] = {
        .name        = "0.94",
        .value       = RVBV_0_94,
        .description = "Bit Manipulation Architecture Version v0.94-20210120",
    },
    [RVBV_1_0_0] = {
        .name        = "1.0.0",
        .value       = RVBV_1_0_0,
        .description = "Bit Manipulation Architecture Version 1.0.0",
    },
    [RVBV_MASTER] = {
        .name        = "master",
        .value       = RVBV_MASTER,
        .description = "Bit Manipulation Master Branch as of commit "
                       RVBV_MASTER_TAG" (this is subject to change)",
    },
    // KEEP LAST: terminator
    {0}
};

//
// Supported Hypervisor Architecture variants
//
static vmiEnumParameter hypervisorVariants[] = {
    [RVHV_0_6_1] = {
        .name        = "0.6.1",
        .value       = RVHV_0_6_1,
        .description = "Hypervisor Architecture Version 0.6.1",
    },
    // KEEP LAST: terminator
    {0}
};

//
// Supported Cryptographic Architecture variants
//
static vmiEnumParameter cryptoVariants[] = {
    [RVKV_0_7_2] = {
        .name        = "0.7.2",
        .value       = RVKV_0_7_2,
        .description = "Cryptographic Architecture Version 0.7.2",
    },
    [RVKV_0_8_1] = {
        .name        = "0.8.1",
        .value       = RVKV_0_8_1,
        .description = "Cryptographic Architecture Version 0.8.1",
    },
    [RVKV_0_9_0] = {
        .name        = "0.9.0",
        .value       = RVKV_0_9_0,
        .description = "Cryptographic Architecture Version 0.9.0",
    },
    [RVKV_0_9_2] = {
        .name        = "0.9.2",
        .value       = RVKV_0_9_2,
        .description = "Cryptographic Architecture Version 0.9.2",
    },
    [RVKV_1_0_0_RC1] = {
        .name        = "1.0.0-rc1",
        .value       = RVKV_1_0_0_RC1,
        .description = "Cryptographic Architecture Version 1.0.0-rc1",
    },
    [RVKV_1_0_0_RC5] = {
        .name        = "1.0.0-rc5",
        .value       = RVKV_1_0_0_RC5,
        .description = "Cryptographic Architecture Version 1.0.0-rc5",
    },
    // KEEP LAST: terminator
    {0}
};

//
// Supported DSP Architecture variants
//
static vmiEnumParameter DSPVariants[] = {
    [RVDSPV_0_5_2] = {
        .name        = "0.5.2",
        .value       = RVDSPV_0_5_2,
        .description = "DSP Architecture Version 0.5.2",
    },
    [RVDSPV_0_9_6] = {
        .name        = "0.9.6",
        .value       = RVDSPV_0_9_6,
        .description = "DSP Architecture Version 0.9.6",
    },
    // KEEP LAST: terminator
    {0}
};

//
// Supported debug mode variants
//
static vmiEnumParameter debugVariants[] = {
    [RVDBG_0_13_2] = {
        .name        = "0.13.2-DRAFT",
        .value       = RVDBG_0_13_2,
        .description = "RISC-V External Debug Support Version 0.13.2-DRAFT",
    },
    [RVDBG_0_14_0] = {
        .name        = "0.14.0-DRAFT",
        .value       = RVDBG_0_14_0,
        .description = "RISC-V External Debug Support Version 0.14.0-DRAFT",
    },
    [RVDBG_1_0_0] = {
        .name        = "1.0.0-STABLE",
        .value       = RVDBG_1_0_0,
        .description = "RISC-V External Debug Support Version 1.0.0-STABLE",
    },
    // KEEP LAST: terminator
    {0}
};

//
// Supported RNMI variants
//
static vmiEnumParameter rnmiVariants[] = {
    [RNMI_NONE] = {
        .name        = "none",
        .value       = RNMI_NONE,
        .description = "RNMI not implemented",
    },
    [RNMI_0_2_1] = {
        .name        = "0.2.1",
        .value       = RNMI_0_2_1,
        .description = "RNMI version 0.2.1",
    },
    // KEEP LAST: terminator
    {0}
};

//
// Supported CLIC variants
//
static vmiEnumParameter CLICVariants[] = {
    [RVCLC_20180831] = {
        .name        = "20180831",
        .value       = RVCLC_20180831,
        .description = "CLIC Version 20180831",
    },
    [RVCLC_0_9_20191208] = {
        .name        = "0.9-draft-20191208",
        .value       = RVCLC_0_9_20191208,
        .description = "CLIC Version 0.9-draft-20191208",
    },
    [RVCLC_MASTER] = {
        .name        = "master",
        .value       = RVCLC_MASTER,
        .description = "CLIC Master Branch as of commit "
                       RVCLC_MASTER_TAG" (this is subject to change)",
    },
    // KEEP LAST: terminator
    {0}
};

//
// Supported Xfinx variants
//
static vmiEnumParameter ZfinxVariants[] = {
    [RVZFINX_NA] = {
        .name        = "none",
        .value       = RVZFINX_NA,
        .description = "Zfinx not implemented",
    },
    [RVZFINX_0_4] = {
        .name        = "0.4",
        .value       = RVZFINX_0_4,
        .description = "Zfinx version 0.4",
    },
    [RVZFINX_0_41] = {
        .name        = "0.41",
        .value       = RVZFINX_0_41,
        .description = "Zfinx version 0.41",
    },
    // KEEP LAST: terminator
    {0}
};

//
// Supported Zcea variants
//
static vmiEnumParameter ZceaVariants[] = {
    [RVZCEA_NA] = {
        .name        = "none",
        .value       = RVZCEA_NA,
        .description = "Zcea not implemented",
    },
    [RVZCEA_0_50_1] = {
        .name        = "0.50.1",
        .value       = RVZCEA_0_50_1,
        .description = "Zcea version 0.50.1",
    },
    // KEEP LAST: terminator
    {0}
};

//
// Supported Zceb variants
//
static vmiEnumParameter ZcebVariants[] = {
    [RVZCEB_NA] = {
        .name        = "none",
        .value       = RVZCEB_NA,
        .description = "Zceb not implemented",
    },
    [RVZCEB_0_50_1] = {
        .name        = "0.50.1",
        .value       = RVZCEB_0_50_1,
        .description = "Zceb version 0.50.1",
    },
    // KEEP LAST: terminator
    {0}
};

//
// Supported Zcee variants
//
static vmiEnumParameter ZceeVariants[] = {
    [RVZCEE_NA] = {
        .name        = "none",
        .value       = RVZCEE_NA,
        .description = "Zcee not implemented",
    },
    [RVZCEE_1_0_0_RC] = {
        .name        = "1.0.0-rc",
        .value       = RVZCEE_1_0_0_RC,
        .description = "Zcee version 1.0.0-rc",
    },
    // KEEP LAST: terminator
    {0}
};

//
// Supported 16-bit floating point variants
//
static vmiEnumParameter fp16Variants[] = {
    [RVFP16_NA] = {
        .name        = "none",
        .value       = RVFP16_NA,
        .description = "No 16-bit floating point implemented",
    },
    [RVFP16_IEEE754] = {
        .name        = "IEEE754",
        .value       = RVFP16_IEEE754,
        .description = "IEEE 754 half precision implemented",
    },
    [RVFP16_BFLOAT16] = {
        .name        = "BFLOAT16",
        .value       = RVFP16_BFLOAT16,
        .description = "BFLOAT16 implemented",
    },
    // KEEP LAST: terminator
    {0}
};

//
// Specify effect of flag writes on FS
//
static vmiEnumParameter FSModes[] = {
    [RVFS_WRITE_NZ] = {
        .name        = "write_1",
        .value       = RVFS_WRITE_NZ,
        .description = "Any non-zero flag result sets mstatus.fs dirty",
    },
    [RVFS_WRITE_ANY] = {
        .name        = "write_any",
        .value       = RVFS_WRITE_ANY,
        .description = "Any write of flags sets mstatus.fs dirty",
    },
    [RVFS_ALWAYS_DIRTY] = {
        .name        = "always_dirty",
        .value       = RVFS_ALWAYS_DIRTY,
        .description = "mstatus.fs is either off or dirty",
    },
    // KEEP LAST: terminator
    {0}
};

//
// Specify Debug mode operation
//
static vmiEnumParameter DMModes[] = {
    [RVDM_NONE] = {
        .name        = "none",
        .value       = RVDM_NONE,
        .description = "Debug mode not implemented",
    },
    [RVDM_VECTOR] = {
        .name        = "vector",
        .value       = RVDM_VECTOR,
        .description = "Debug mode implemented by execution at vector",
    },
    [RVDM_INTERRUPT] = {
        .name        = "interrupt",
        .value       = RVDM_INTERRUPT,
        .description = "Debug mode implemented by interrupt",
    },
    [RVDM_HALT] = {
        .name        = "halt",
        .value       = RVDM_HALT,
        .description = "Debug mode implemented by halt",
    },
    // KEEP LAST: terminator
    {0}
};

//
// Specify behavior of MRET, SRET or URET in Debug mode
//
static vmiEnumParameter DERETModes[] = {
    [RVDRM_NOP] = {
        .name        = "nop",
        .value       = RVDRM_NOP,
        .description = "MRET, SRET or URET in Debug mode is a nop",
    },
    [RVDRM_JUMP] = {
        .name        = "jump_to_dexc_address",
        .value       = RVDRM_JUMP,
        .description = "MRET, SRET or URET in Debug mode jumps to dexc_address",
    },
    [RVDRM_TRAP] = {
        .name        = "trap_to_dexc_address",
        .value       = RVDRM_TRAP,
        .description = "MRET, SRET or URET in Debug mode traps to dexc_address",
    },
    // KEEP LAST: terminator
    {0}
};

//
// Supported Smepmp variants
//
static vmiEnumParameter SmepmpVariants[] = {
    [RVSP_NONE] = {
        .name        = "none",
        .value       = RVSP_NONE,
        .description = "Smepmp not implemented",
    },
    [RVSP_0_9_5] = {
        .name        = "0.9.5",
        .value       = RVSP_0_9_5,
        .description = "Smepmp version 0.9.5",
    },
    // KEEP LAST: terminator
    {0}
};

//
// Return the maximum number of bits that can be specified for CLICCFGMBITS
//
static Uns32 getCLICCFGMBITSMax(riscvConfigCP cfg) {
    riscvArchitecture arch = cfg->arch ? : -1;
    return (arch&ISA_S) ? 2 : (arch&ISA_N) ? 1 : 0;
}

//
// Return the maximum number of bits that can be specified for CLICCFGLBITS,
// ceil(lg2(CLICLEVELS))
//
static Uns32 getCLICCFGLBITSMax(riscvConfigCP cfg) {

    Uns32 max = 0;
    Uns32 try = 1;

    while(try<cfg->CLICLEVELS) {
        try *= 2;
        max++;
    }

    return max;
}

//
// This function type is used to specify the default value for a parameter
//
#define RISCV_PDEFAULT_FN(_NAME) void _NAME(riscvConfigCP cfg, vmiParameterP param)
typedef RISCV_PDEFAULT_FN((*riscvPDefaultFn));

//
// Parameter list including variant information
//
typedef struct riscvParameterS {
    riscvParamVariant variant;
    riscvPrivVer      minPV;
    riscvPDefaultFn   defaultCB;
    vmiParameter      parameter;
} riscvParameter, *riscvParameterP;

//
// Validate parameter type
//
#define CHECK_PARAM_TYPE(_P, _T, _NAME) VMI_ASSERT( \
    _P->type==_T,                                   \
    "parameter %s is not of "_NAME" type",          \
    _P->name                                        \
)

//
// Set enum parameter default
//
static void setEnumParamDefault(vmiParameterP param, Uns32 value) {
    CHECK_PARAM_TYPE(param, vmi_PT_ENUM, "Enum");
    param->u.enumParam.defaultValue = &param->u.enumParam.legalValues[value];
}

//
// Set Bool parameter default
//
static void setBoolParamDefault(vmiParameterP param, Bool value) {
    CHECK_PARAM_TYPE(param, vmi_PT_BOOL, "Bool");
    param->u.boolParam.defaultValue = value;
}

//
// Set Uns32 parameter default
//
static void setUns32ParamDefault(vmiParameterP param, Uns32 value) {
    CHECK_PARAM_TYPE(param, vmi_PT_UNS32, "Uns32");
    param->u.uns32Param.defaultValue = value;
}

//
// Set Uns64 parameter default
//
static void setUns64ParamDefault(vmiParameterP param, Uns64 value) {
    CHECK_PARAM_TYPE(param, vmi_PT_UNS64, "Uns64");
    param->u.uns64Param.defaultValue = value;
}

//
// Set Uns32 parameter maximum value
//
static void setUns32ParamMax(vmiParameterP param, Uns32 value) {
    CHECK_PARAM_TYPE(param, vmi_PT_UNS32, "Uns32");
    param->u.uns32Param.max = value;
}

//
// Set Flt64 parameter default
//
static void setFlt64ParamDefault(vmiParameterP param, Flt64 value) {
    CHECK_PARAM_TYPE(param, vmi_PT_DOUBLE, "Flt64");
    param->u.doubleParam.defaultValue = value;
}

//
// Macro to define a function to set a raw enum parameter value from the
// configuration
//
#define RISCV_ENUM_PDEFAULT_CFG_FN(_NAME) RISCV_PDEFAULT_FN(default_##_NAME) { \
    setEnumParamDefault(param, cfg->_NAME);  \
}

//
// Macro to define a function to set a raw Bool parameter value from the
// configuration
//
#define RISCV_BOOL_PDEFAULT_CFG_FN(_NAME) RISCV_PDEFAULT_FN(default_##_NAME) { \
    setBoolParamDefault(param, cfg->_NAME);  \
}

//
// Macro to define a function to set a raw Bool parameter value from the
// negation of a "no" prefixed equivalent in the configuration
//
#define RISCV_NOT_PDEFAULT_CFG_FN(_NAME) RISCV_PDEFAULT_FN(default_##_NAME) { \
    setBoolParamDefault(param, !cfg->no##_NAME);  \
}

//
// Macro to define a function to set a raw Uns32 parameter value from the
// configuration
//
#define RISCV_UNS32_PDEFAULT_CFG_FN(_NAME) RISCV_PDEFAULT_FN(default_##_NAME) { \
    setUns32ParamDefault(param, cfg->_NAME);  \
}

//
// Macro to define a function to set a raw Uns64 parameter value from the
// configuration
//
#define RISCV_UNS64_PDEFAULT_CFG_FN(_NAME) RISCV_PDEFAULT_FN(default_##_NAME) { \
    setUns64ParamDefault(param, cfg->_NAME);  \
}

//
// Set default value of raw enum parameters
//
static RISCV_ENUM_PDEFAULT_CFG_FN(user_version);
static RISCV_ENUM_PDEFAULT_CFG_FN(priv_version);
static RISCV_ENUM_PDEFAULT_CFG_FN(vect_version);
static RISCV_ENUM_PDEFAULT_CFG_FN(bitmanip_version);
static RISCV_ENUM_PDEFAULT_CFG_FN(hyp_version);
static RISCV_ENUM_PDEFAULT_CFG_FN(crypto_version);
static RISCV_ENUM_PDEFAULT_CFG_FN(dsp_version);
static RISCV_ENUM_PDEFAULT_CFG_FN(dbg_version);
static RISCV_ENUM_PDEFAULT_CFG_FN(rnmi_version);
static RISCV_ENUM_PDEFAULT_CFG_FN(Smepmp_version);
static RISCV_ENUM_PDEFAULT_CFG_FN(CLIC_version);
static RISCV_ENUM_PDEFAULT_CFG_FN(Zfinx_version);
static RISCV_ENUM_PDEFAULT_CFG_FN(Zcea_version);
static RISCV_ENUM_PDEFAULT_CFG_FN(Zceb_version);
static RISCV_ENUM_PDEFAULT_CFG_FN(Zcee_version);
static RISCV_ENUM_PDEFAULT_CFG_FN(fp16_version);
static RISCV_ENUM_PDEFAULT_CFG_FN(mstatus_fs_mode);
static RISCV_ENUM_PDEFAULT_CFG_FN(debug_mode);
static RISCV_ENUM_PDEFAULT_CFG_FN(debug_eret_mode);


//
// Set default value of raw Bool parameters
//
static RISCV_BOOL_PDEFAULT_CFG_FN(enable_expanded);
static RISCV_BOOL_PDEFAULT_CFG_FN(endianFixed);
static RISCV_BOOL_PDEFAULT_CFG_FN(updatePTEA);
static RISCV_BOOL_PDEFAULT_CFG_FN(updatePTED);
static RISCV_BOOL_PDEFAULT_CFG_FN(unaligned);
static RISCV_BOOL_PDEFAULT_CFG_FN(unalignedAMO);
static RISCV_BOOL_PDEFAULT_CFG_FN(wfi_is_nop);
static RISCV_BOOL_PDEFAULT_CFG_FN(mtvec_is_ro);
static RISCV_BOOL_PDEFAULT_CFG_FN(tval_zero);
static RISCV_BOOL_PDEFAULT_CFG_FN(tval_ii_code);
static RISCV_BOOL_PDEFAULT_CFG_FN(cycle_undefined);
static RISCV_BOOL_PDEFAULT_CFG_FN(time_undefined);
static RISCV_BOOL_PDEFAULT_CFG_FN(instret_undefined);
static RISCV_BOOL_PDEFAULT_CFG_FN(hpmcounter_undefined);
static RISCV_BOOL_PDEFAULT_CFG_FN(tinfo_undefined);
static RISCV_BOOL_PDEFAULT_CFG_FN(tcontrol_undefined);
static RISCV_BOOL_PDEFAULT_CFG_FN(mcontext_undefined);
static RISCV_BOOL_PDEFAULT_CFG_FN(scontext_undefined);
static RISCV_BOOL_PDEFAULT_CFG_FN(mscontext_undefined);
static RISCV_BOOL_PDEFAULT_CFG_FN(hcontext_undefined);
static RISCV_BOOL_PDEFAULT_CFG_FN(mnoise_undefined);
static RISCV_BOOL_PDEFAULT_CFG_FN(amo_trigger);
static RISCV_BOOL_PDEFAULT_CFG_FN(no_hit);
static RISCV_BOOL_PDEFAULT_CFG_FN(no_sselect_2);
static RISCV_BOOL_PDEFAULT_CFG_FN(enable_CSR_bus);
static RISCV_BOOL_PDEFAULT_CFG_FN(d_requires_f);
static RISCV_BOOL_PDEFAULT_CFG_FN(enable_fflags_i);
static RISCV_BOOL_PDEFAULT_CFG_FN(trap_preserves_lr);
static RISCV_BOOL_PDEFAULT_CFG_FN(xret_preserves_lr);
static RISCV_BOOL_PDEFAULT_CFG_FN(require_vstart0);
static RISCV_BOOL_PDEFAULT_CFG_FN(align_whole);
static RISCV_BOOL_PDEFAULT_CFG_FN(vill_trap);
static RISCV_BOOL_PDEFAULT_CFG_FN(external_int_id);
static RISCV_BOOL_PDEFAULT_CFG_FN(CLICANDBASIC);
static RISCV_BOOL_PDEFAULT_CFG_FN(CLICSELHVEC);
static RISCV_BOOL_PDEFAULT_CFG_FN(CLICXNXTI);
static RISCV_BOOL_PDEFAULT_CFG_FN(CLICXCSW);
static RISCV_BOOL_PDEFAULT_CFG_FN(externalCLIC);
static RISCV_BOOL_PDEFAULT_CFG_FN(tvt_undefined);
static RISCV_BOOL_PDEFAULT_CFG_FN(intthresh_undefined);
static RISCV_BOOL_PDEFAULT_CFG_FN(mclicbase_undefined);
static RISCV_BOOL_PDEFAULT_CFG_FN(mstatus_FS_zero);
static RISCV_BOOL_PDEFAULT_CFG_FN(MXL_writable);
static RISCV_BOOL_PDEFAULT_CFG_FN(SXL_writable);
static RISCV_BOOL_PDEFAULT_CFG_FN(UXL_writable);
static RISCV_BOOL_PDEFAULT_CFG_FN(VSXL_writable);
#if(ENABLE_SSMPU)
static RISCV_BOOL_PDEFAULT_CFG_FN(MPU_decompose);
#endif
static RISCV_BOOL_PDEFAULT_CFG_FN(PMP_decompose);
static RISCV_BOOL_PDEFAULT_CFG_FN(posedge_other);
static RISCV_BOOL_PDEFAULT_CFG_FN(poslevel_other);
static RISCV_BOOL_PDEFAULT_CFG_FN(tval_zero_ebreak);
static RISCV_BOOL_PDEFAULT_CFG_FN(Zmmul);
static RISCV_BOOL_PDEFAULT_CFG_FN(Zfhmin);
static RISCV_BOOL_PDEFAULT_CFG_FN(Zicbom);
static RISCV_BOOL_PDEFAULT_CFG_FN(Zicbop);
static RISCV_BOOL_PDEFAULT_CFG_FN(Zicboz);
static RISCV_BOOL_PDEFAULT_CFG_FN(Svpbmt);
static RISCV_BOOL_PDEFAULT_CFG_FN(Svinval);
static RISCV_BOOL_PDEFAULT_CFG_FN(use_hw_reg_names);

//
// Set default value of raw negated Bool parameters
//
static RISCV_NOT_PDEFAULT_CFG_FN(Zicsr);
static RISCV_NOT_PDEFAULT_CFG_FN(Zifencei);

//
// Set default value of raw Uns32 parameters
//
static RISCV_UNS32_PDEFAULT_CFG_FN(dcsr_ebreak_mask);
static RISCV_UNS32_PDEFAULT_CFG_FN(trigger_num);
static RISCV_UNS32_PDEFAULT_CFG_FN(mcontrol_maskmax);
static RISCV_UNS32_PDEFAULT_CFG_FN(tinfo);
static RISCV_UNS32_PDEFAULT_CFG_FN(tvec_align);
static RISCV_UNS32_PDEFAULT_CFG_FN(counteren_mask);
static RISCV_UNS32_PDEFAULT_CFG_FN(noinhibit_mask);
#if(ENABLE_SSMPU)
static RISCV_UNS32_PDEFAULT_CFG_FN(MPU_grain)
static RISCV_UNS32_PDEFAULT_CFG_FN(MPU_registers)
#endif
static RISCV_UNS32_PDEFAULT_CFG_FN(PMP_grain)
static RISCV_UNS32_PDEFAULT_CFG_FN(PMP_max_page)
static RISCV_UNS32_PDEFAULT_CFG_FN(CLICLEVELS);

//
// Set default value of raw Uns64 parameters
//
static RISCV_UNS64_PDEFAULT_CFG_FN(reset_address)
static RISCV_UNS64_PDEFAULT_CFG_FN(nmi_address)
static RISCV_UNS64_PDEFAULT_CFG_FN(nmiexc_address)
static RISCV_UNS64_PDEFAULT_CFG_FN(CLINT_address)
static RISCV_UNS64_PDEFAULT_CFG_FN(debug_address)
static RISCV_UNS64_PDEFAULT_CFG_FN(dexc_address)
static RISCV_UNS64_PDEFAULT_CFG_FN(unimp_int_mask)
static RISCV_UNS64_PDEFAULT_CFG_FN(force_mideleg)
static RISCV_UNS64_PDEFAULT_CFG_FN(force_sideleg)
static RISCV_UNS64_PDEFAULT_CFG_FN(no_ideleg)
static RISCV_UNS64_PDEFAULT_CFG_FN(no_edeleg)
static RISCV_UNS64_PDEFAULT_CFG_FN(posedge_0_63)
static RISCV_UNS64_PDEFAULT_CFG_FN(poslevel_0_63)
static RISCV_UNS64_PDEFAULT_CFG_FN(Svnapot_page_mask)

//
// Specify whether halt-precision floating point is implemented
//
static RISCV_PDEFAULT_FN(default_Zfh) {
    setBoolParamDefault(param, cfg->fp16_version==RVFP16_IEEE754);
}

//
// Specify whether D registers are used for parameter passing (ABI semihosting)
//
static RISCV_PDEFAULT_FN(default_ABI_d) {
    setBoolParamDefault(param, cfg->arch & ISA_D);
}

//
// Set default number of PMP registers
//
static RISCV_PDEFAULT_FN(default_PMP_registers) {

    setUns32ParamDefault(param, cfg->PMP_registers);
    setUns32ParamMax(param, (cfg->priv_version>=RVPV_1_12) ? 64 : 16);
}

//
// Set default value of numHarts
//
static RISCV_PDEFAULT_FN(default_numHarts) {

    Uns32 numHarts = cfg->numHarts;

    setUns32ParamDefault(param, numHarts==RV_NUMHARTS_0 ? 0 : numHarts);
}

//
// Set default value of Sv_modes
//
static RISCV_PDEFAULT_FN(default_Sv_modes) {

    Uns32 Sv_modes = cfg->Sv_modes;

    if(cfg->Sv_modes) {
        // no action
    } else if(cfg->arch & ISA_XLEN_64) {
        Sv_modes = RISCV_VMM_64;
    } else {
        Sv_modes = RISCV_VMM_32;
    }

    setUns32ParamDefault(param, Sv_modes);
}

//
// Set default value of lr_sc_grain
//
static RISCV_PDEFAULT_FN(default_lr_sc_grain) {

    setUns32ParamDefault(param, cfg->lr_sc_grain ? : 1);
}

//
// Set default value of misa_MXL
//
static RISCV_PDEFAULT_FN(default_misa_MXL) {

    setUns32ParamDefault(param, (cfg->arch & ISA_XLEN_64) ? 2 : 1);
}

//
// Set default value of misa_Extensions
//
static RISCV_PDEFAULT_FN(default_misa_Extensions) {

    setUns32ParamDefault(param, cfg->arch & ~cfg->archImplicit & ~ISA_XLEN_ANY);
}

//
// Set default value of misa_Extensions_mask
//
static RISCV_PDEFAULT_FN(default_misa_Extensions_mask) {

    // only bits that are non-zero in arch and not in archZero are writable
    setUns32ParamDefault(param, cfg->archMask & cfg->arch & ~cfg->archImplicit);
}

//
// Set default and maximum value of local_int_num
//
static RISCV_PDEFAULT_FN(default_local_int_num) {

    Uns32 maxLocal;

    if(cfg->CLICLEVELS) {
        maxLocal = 4096-16;
    } else if(cfg->arch & ISA_XLEN_64) {
        maxLocal = 48;
    } else {
        maxLocal = 16;
    }

    setUns32ParamDefault(param, cfg->local_int_num);
    setUns32ParamMax(param, maxLocal);
}

//
// Return XLEN all-ones right shifted by one
//
static Uns64 getXLMaskShr1(riscvConfigCP cfg) {
    return ((cfg->arch & ISA_XLEN_64) ? -1ULL : (Uns32)-1) >> 1;
}

//
// Set default value of ecode_mask
//
static RISCV_PDEFAULT_FN(default_ecode_mask) {

    Uns64 ecode_mask = cfg->ecode_mask;

    if(ecode_mask) {
        // use specified mask
    } else if(cfg->CLICLEVELS) {
        ecode_mask = 0xfff;
    } else {
        ecode_mask = getXLMaskShr1(cfg);
    }

    setUns64ParamDefault(param, ecode_mask);
}

//
// Set default value of ecode_nmi
//
static RISCV_PDEFAULT_FN(default_ecode_nmi) {

    Uns64 ecode_nmi = cfg->ecode_nmi;

    if(ecode_nmi) {
        // use specified mask
    } else if(cfg->CLICLEVELS) {
        ecode_nmi = 0xfff;
    }

    setUns64ParamDefault(param, ecode_nmi);
}

//
// Set default value of ecode_nmi_mask
//
static RISCV_PDEFAULT_FN(default_ecode_nmi_mask) {

    setUns64ParamDefault(param, cfg->ecode_nmi_mask ? : getXLMaskShr1(cfg));
}

//
// Set default and maximum value of mcontext_bits
//
static RISCV_PDEFAULT_FN(default_mcontext_bits) {

    setUns32ParamDefault(param, cfg->mcontext_bits);
    setUns32ParamMax(param, (cfg->arch&ISA_XLEN_64) ? 64 : 32);
}

//
// Set default and maximum value of scontext_bits
//
static RISCV_PDEFAULT_FN(default_scontext_bits) {

    setUns32ParamDefault(param, cfg->scontext_bits);
    setUns32ParamMax(param, (cfg->arch&ISA_XLEN_64) ? 64 : 32);
}

//
// Set default and maximum value of mvalue_bits
//
static RISCV_PDEFAULT_FN(default_mvalue_bits) {

    setUns32ParamDefault(param, cfg->mvalue_bits);
    setUns32ParamMax(param, (cfg->arch&ISA_XLEN_64) ? 13 : 6);
}

//
// Set default and maximum value of svalue_bits
//
static RISCV_PDEFAULT_FN(default_svalue_bits) {

    setUns32ParamDefault(param, cfg->svalue_bits);
    setUns32ParamMax(param, (cfg->arch&ISA_XLEN_64) ? 34 : 16);
}

//
// Set default and maximum value of ASID_bits
//
static RISCV_PDEFAULT_FN(default_ASID_bits) {

    setUns32ParamDefault(param, cfg->ASID_bits);
    setUns32ParamMax(param, (cfg->arch&ISA_XLEN_64) ? 16 : 9);
}

//
// Set default and maximum value of VMID_bits
//
static RISCV_PDEFAULT_FN(default_VMID_bits) {

    setUns32ParamDefault(param, cfg->VMID_bits);
    setUns32ParamMax(param, (cfg->arch&ISA_XLEN_64) ? 14 : 7);
}

//
// Set default value of CLICINTCTLBITS
//
static RISCV_PDEFAULT_FN(default_CLICINTCTLBITS) {

    setUns32ParamDefault(param, cfg->CLICINTCTLBITS ? : 2);
}

//
// Set default value of CLICVERSION
//
static RISCV_PDEFAULT_FN(default_CLICVERSION) {

    setUns32ParamDefault(param, cfg->CLICVERSION ? : 0x11);
}

//
// Set default and maximum value of CLICCFGMBITS
//
static RISCV_PDEFAULT_FN(default_CLICCFGMBITS) {

    Uns32 max   = getCLICCFGMBITSMax(cfg);
    Uns32 value = cfg->CLICCFGMBITS;

    setUns32ParamDefault(param, value<=max ? value : max);
    setUns32ParamMax(param, max);
}

//
// Set default and maximum value of CLICCFGLBITS
//
static RISCV_PDEFAULT_FN(default_CLICCFGLBITS){

    Uns32 max   = getCLICCFGLBITSMax(cfg);
    Uns32 value = cfg->CLICCFGLBITS;

    setUns32ParamDefault(param, value<=max ? value : max);
    setUns32ParamMax(param, max);
}

//
// Set default value for CLINT mtime counter frequency
//
static RISCV_PDEFAULT_FN(default_mtime_Hz) {
    setFlt64ParamDefault(param, cfg->mtime_Hz ? : 32768);
}

//
// Macro to define a function to set an Uns64 CSR parameter value from the
// configuration
//
#define RISCV_CSR_PDEFAULT_CFG_FN(_NAME) RISCV_PDEFAULT_FN(default_##_NAME) { \
    setUns64ParamDefault(param, cfg->csr._NAME._pad);  \
}

//
// Set default value of CSR parameters
//
static RISCV_CSR_PDEFAULT_CFG_FN(mvendorid)
static RISCV_CSR_PDEFAULT_CFG_FN(marchid)
static RISCV_CSR_PDEFAULT_CFG_FN(mimpid)
static RISCV_CSR_PDEFAULT_CFG_FN(mhartid)
static RISCV_CSR_PDEFAULT_CFG_FN(mconfigptr)
static RISCV_CSR_PDEFAULT_CFG_FN(mtvec)
static RISCV_CSR_PDEFAULT_CFG_FN(mclicbase)

//
// Macro to define a function to set an Uns64 CSR mask value from the
// configuration
//
#define RISCV_CSR_PMDEFAULT_CFG_FN(_NAME) RISCV_PDEFAULT_FN(default_##_NAME##_mask) { \
    setUns64ParamDefault(param, cfg->csrMask._NAME._pad);  \
}

//
// Set default value of CSR mask parameters
//
static RISCV_CSR_PMDEFAULT_CFG_FN(mtvec)
static RISCV_CSR_PMDEFAULT_CFG_FN(stvec)
static RISCV_CSR_PMDEFAULT_CFG_FN(utvec)
static RISCV_CSR_PMDEFAULT_CFG_FN(mtvt)
static RISCV_CSR_PMDEFAULT_CFG_FN(stvt)
static RISCV_CSR_PMDEFAULT_CFG_FN(utvt)

//
// Set default value of tdata1_mask
//
static RISCV_PDEFAULT_FN(default_tdata1_mask) {
    setUns64ParamDefault(param, cfg->csrMask.tdata1.u64.bits ? : -1);
}

//
// Set default values of mip_mask, sip_mask, uip_mask and hip_mask
//
static RISCV_PDEFAULT_FN(default_mip_mask) {
    setUns64ParamDefault(param, cfg->csrMask.mip.u64.bits ? : WM32_mip);
}
static RISCV_PDEFAULT_FN(default_sip_mask) {
    setUns64ParamDefault(param, cfg->csrMask.sip.u64.bits ? : WM32_sip);
}
static RISCV_PDEFAULT_FN(default_uip_mask) {
    setUns64ParamDefault(param, cfg->csrMask.uip.u64.bits ? : WM32_uip);
}
static RISCV_PDEFAULT_FN(default_hip_mask) {
    setUns64ParamDefault(param, cfg->csrMask.hip.u64.bits ? : WM32_hip);
}

//
// Set default value of envcfg_mask
//
static RISCV_PDEFAULT_FN(default_envcfg_mask) {
    setUns64ParamDefault(param, cfg->csrMask.envcfg.u64.bits ? : WM64_envcfg);
}

//
// Set default value of CSR sign-extend parameters
//
static RISCV_BOOL_PDEFAULT_CFG_FN(mtvec_sext);
static RISCV_BOOL_PDEFAULT_CFG_FN(stvec_sext);
static RISCV_BOOL_PDEFAULT_CFG_FN(utvec_sext);
static RISCV_BOOL_PDEFAULT_CFG_FN(mtvt_sext);
static RISCV_BOOL_PDEFAULT_CFG_FN(stvt_sext);
static RISCV_BOOL_PDEFAULT_CFG_FN(utvt_sext);

//
// Set default values of ELEN, SLEN, VLEN and SEW_min (Vector Extension)
//
static RISCV_PDEFAULT_FN(default_ELEN) {
    setUns32ParamDefault(param, cfg->ELEN ? : ELEN_DEFAULT);
}
static RISCV_PDEFAULT_FN(default_SLEN) {
    setUns32ParamDefault(param, cfg->SLEN ? : SLEN_DEFAULT);
}
static RISCV_PDEFAULT_FN(default_VLEN) {
    setUns32ParamDefault(param, cfg->VLEN ? : VLEN_DEFAULT);
}
static RISCV_PDEFAULT_FN(default_EEW_index) {
    setUns32ParamDefault(param, cfg->EEW_index);
}
static RISCV_PDEFAULT_FN(default_SEW_min) {
    setUns32ParamDefault(param, cfg->SEW_min ? cfg->SEW_min : SEW_MIN);
}

//
// Set default values of agnostic_ones, Zvlsseg, Zvamo and Zvediv (Vector
// Extension)
//
static RISCV_BOOL_PDEFAULT_CFG_FN(agnostic_ones);
static RISCV_BOOL_PDEFAULT_CFG_FN(Zvlsseg);
static RISCV_BOOL_PDEFAULT_CFG_FN(Zvamo);
static RISCV_BOOL_PDEFAULT_CFG_FN(Zvediv);
static RISCV_BOOL_PDEFAULT_CFG_FN(Zvqmac);

//
// Set vector extension embedded profile parameter default
//
static void setVProfileParamDefault(
    riscvConfigCP  cfg,
    vmiParameterP  param,
    riscvVectorSet option
) {
    CHECK_PARAM_TYPE(param, vmi_PT_BOOL, "Bool");
    param->u.boolParam.defaultValue = (cfg->vect_profile == option);
}

//
// Macro to define a function to set a raw Bool vector extension embedded
// profile parameter value from the configuration
//
#define RISCV_VPROF_PDEFAULT_CFG_FN(_NAME) RISCV_PDEFAULT_FN(default_##_NAME) { \
    setVProfileParamDefault(cfg, param, RVVS_##_NAME); \
}

//
// Set default values of vector extension embedded profile options
//
static RISCV_VPROF_PDEFAULT_CFG_FN(Zve32x);
static RISCV_VPROF_PDEFAULT_CFG_FN(Zve32f);
static RISCV_VPROF_PDEFAULT_CFG_FN(Zve64x);
static RISCV_VPROF_PDEFAULT_CFG_FN(Zve64f);
static RISCV_VPROF_PDEFAULT_CFG_FN(Zve64d);

//
// Set bit manipulation extension subset option parameter default
//
static void setBMSetParamDefault(
    riscvConfigCP    cfg,
    vmiParameterP    param,
    riscvBitManipSet option
) {
    CHECK_PARAM_TYPE(param, vmi_PT_BOOL, "Bool");
    param->u.boolParam.defaultValue = !(cfg->bitmanip_absent & option);
}

//
// Macro to define a function to set a raw Bool bit manipulation subset
// parameter value from the configuration
//
#define RISCV_BMSET_PDEFAULT_CFG_FN(_NAME) RISCV_PDEFAULT_FN(default_##_NAME) { \
    setBMSetParamDefault(cfg, param, RVBS_##_NAME); \
}

//
// Set default values of bit manipulation extension subset options
//
static RISCV_BMSET_PDEFAULT_CFG_FN(Zba);
static RISCV_BMSET_PDEFAULT_CFG_FN(Zbb);
static RISCV_BMSET_PDEFAULT_CFG_FN(Zbc);
static RISCV_BMSET_PDEFAULT_CFG_FN(Zbe);
static RISCV_BMSET_PDEFAULT_CFG_FN(Zbf);
static RISCV_BMSET_PDEFAULT_CFG_FN(Zbm);
static RISCV_BMSET_PDEFAULT_CFG_FN(Zbp);
static RISCV_BMSET_PDEFAULT_CFG_FN(Zbr);
static RISCV_BMSET_PDEFAULT_CFG_FN(Zbs);
static RISCV_BMSET_PDEFAULT_CFG_FN(Zbt);

//
// Set cryptographic extension subset option parameter default
//
static void setKSetParamDefault(
    riscvConfigCP  cfg,
    vmiParameterP  param,
    riscvCryptoSet option
) {
    CHECK_PARAM_TYPE(param, vmi_PT_BOOL, "Bool");
    param->u.boolParam.defaultValue = !(cfg->crypto_absent & option);
}

//
// Macro to define a function to set a raw Bool cryptographic subset parameter
// value from the configuration
//
#define RISCV_KSET_PDEFAULT_CFG_FN(_NAME) RISCV_PDEFAULT_FN(default_##_NAME) { \
    setKSetParamDefault(cfg, param, RVKS_##_NAME); \
}

//
// Set default values of cryptographic extension subset options
//
static RISCV_KSET_PDEFAULT_CFG_FN(Zbkb);
static RISCV_KSET_PDEFAULT_CFG_FN(Zbkc);
static RISCV_KSET_PDEFAULT_CFG_FN(Zbkx);
static RISCV_KSET_PDEFAULT_CFG_FN(Zkr);
static RISCV_KSET_PDEFAULT_CFG_FN(Zknd);
static RISCV_KSET_PDEFAULT_CFG_FN(Zkne);
static RISCV_KSET_PDEFAULT_CFG_FN(Zknh);
static RISCV_KSET_PDEFAULT_CFG_FN(Zksed);
static RISCV_KSET_PDEFAULT_CFG_FN(Zksh);
static RISCV_KSET_PDEFAULT_CFG_FN(Zkb);
static RISCV_KSET_PDEFAULT_CFG_FN(Zkg);

//
// Set DSP extension subset option parameter default
//
static void setPSetParamDefault(
    riscvConfigCP cfg,
    vmiParameterP param,
    riscvDSPSet   option
) {
    CHECK_PARAM_TYPE(param, vmi_PT_BOOL, "Bool");
    param->u.boolParam.defaultValue = !(cfg->dsp_absent & option);
}

//
// Macro to define a function to set a raw Bool cryptographic subset parameter
// value from the configuration
//
#define RISCV_PSET_PDEFAULT_CFG_FN(_NAME) RISCV_PDEFAULT_FN(default_##_NAME) { \
    setPSetParamDefault(cfg, param, RVPS_##_NAME); \
}

//
// Set default values of cryptographic extension subset options
//
static RISCV_PSET_PDEFAULT_CFG_FN(Zpsfoperand);

//
// Set default values of hypervisor extension subset options
//
static RISCV_BOOL_PDEFAULT_CFG_FN(xtinst_basic);

//
// Set default value and range of GEILEN
//
static RISCV_PDEFAULT_FN(default_GEILEN) {
    setUns32ParamDefault(param, cfg->GEILEN);
    setUns32ParamMax(param, (cfg->arch&ISA_XLEN_64)?63:31);
}

//
// Set default value of cmomp_bytes
//
static RISCV_PDEFAULT_FN(default_cmomp_bytes) {
    Uns32 cmomp_bytes = cfg->cmomp_bytes;
    setUns32ParamDefault(param, cmomp_bytes ? cmomp_bytes : RISCV_CBYTES);
}

//
// Set default value of cmoz_bytes
//
static RISCV_PDEFAULT_FN(default_cmoz_bytes) {
    Uns32 cmoz_bytes = cfg->cmoz_bytes;
    setUns32ParamDefault(param, cmoz_bytes ? cmoz_bytes : RISCV_CBYTES);
}

//
// This describes the parameter groups in the processor
//
typedef enum riscvParamGroupIdE {
    RV_PG_FUND,         // fundamental group
    RV_PG_ARTIF,        // simulation artifacts
    RV_PG_INTXC,        // interrupts and exceptions
    RV_PG_ICSRB,        // instruction and CSR behavior
    RV_PG_CSRDV,        // CSR defaults
    RV_PG_CSRMK,        // CSR masks
    RV_PG_MEM,          // memory
    RV_PG_FP,           // floating point
    RV_PG_B,            // bit manipulation extension
    RV_PG_C,            // compressed extension
    RV_PG_H,            // hypervisor extension
    RV_PG_K,            // cryptographic extension
    RV_PG_N,            // user-level interrupts extension
    RV_PG_P,            // DSP extension
    RV_PG_V,            // vector extension
    RV_PG_CLIC,         // fast interrupts
    RV_PG_DBG,          // debug extension
    RV_PG_TRIG,         // trigger module
    RV_PG_LAST          // KEEP LAST: for sizing
} riscvParamGroupId;

//
// This provides information about each group
//
static const vmiParameterGroup groups[RV_PG_LAST+1] = {
    [RV_PG_FUND]  = {name: "Fundamental"},
    [RV_PG_ARTIF] = {name: "Simulation_Artifact"},
    [RV_PG_INTXC] = {name: "Interrupts_Exceptions"},
    [RV_PG_ICSRB] = {name: "Instruction_CSR_Behavior"},
    [RV_PG_CSRDV] = {name: "CSR_Defauts"},
    [RV_PG_CSRMK] = {name: "CSR_Masks"},
    [RV_PG_MEM]   = {name: "Memory"},
    [RV_PG_FP]    = {name: "Floating_Point"},
    [RV_PG_B]     = {name: "Bit_Manipulation"},
    [RV_PG_C]     = {name: "Compressed"},
    [RV_PG_H]     = {name: "Hypervisor"},
    [RV_PG_K]     = {name: "Cryptographic"},
    [RV_PG_N]     = {name: "User_Level_Interrupts"},
    [RV_PG_P]     = {name: "DSP"},
    [RV_PG_V]     = {name: "Vector"},
    [RV_PG_CLIC]  = {name: "Fast_Interrupt"},
    [RV_PG_DBG]   = {name: "Debug"},
    [RV_PG_TRIG]  = {name: "Trigger"},
};

//
// Macro to specify a the group for a register
//
#define RV_GROUP(_G) &groups[RV_PG_##_G]

//
// Table of formal parameter specifications
//
static riscvParameter parameters[] = {

    // simulation controls
    {  RVPV_VARIANT, 0,         0,                            VMI_ENUM_GROUP_PARAM_SPEC  (riscvParamValues, variant,                 0,                         RV_GROUP(FUND),  "Selects variant (either a generic UISA or a specific model)")},
    {  RVPV_CLUSTER, 0,         0,                            VMI_STRING_GROUP_PARAM_SPEC(riscvParamValues, clusterVariants,         0,                         RV_GROUP(FUND),  "Specify a comma-separated list of variant names in this cluster")},
    {  RVPV_PRE,     0,         default_user_version,         VMI_ENUM_GROUP_PARAM_SPEC  (riscvParamValues, user_version,            userVariants,              RV_GROUP(FUND),  "Specify required User Architecture version")},
    {  RVPV_PRE,     0,         default_priv_version,         VMI_ENUM_GROUP_PARAM_SPEC  (riscvParamValues, priv_version,            privVariants,              RV_GROUP(FUND),  "Specify required Privileged Architecture version")},
    {  RVPV_V,       0,         default_vect_version,         VMI_ENUM_GROUP_PARAM_SPEC  (riscvParamValues, vector_version,          vectorVariants,            RV_GROUP(V),     "Specify required Vector Architecture version")},
    {  RVPV_BK,      0,         default_bitmanip_version,     VMI_ENUM_GROUP_PARAM_SPEC  (riscvParamValues, bitmanip_version,        bitmanipVariants,          RV_GROUP(B),     "Specify required Bit Manipulation Architecture version")},
    {  RVPV_H,       0,         default_hyp_version,          VMI_ENUM_GROUP_PARAM_SPEC  (riscvParamValues, hypervisor_version,      hypervisorVariants,        RV_GROUP(H),     "Specify required Hypervisor Architecture version")},
    {  RVPV_K,       0,         default_crypto_version,       VMI_ENUM_GROUP_PARAM_SPEC  (riscvParamValues, crypto_version,          cryptoVariants,            RV_GROUP(K),     "Specify required Cryptographic Architecture version")},
    {  RVPV_P,       0,         default_dsp_version,          VMI_ENUM_GROUP_PARAM_SPEC  (riscvParamValues, dsp_version,             DSPVariants,               RV_GROUP(P),     "Specify required DSP Architecture version")},
    {  RVPV_DBGT,    0,         default_dbg_version,          VMI_ENUM_GROUP_PARAM_SPEC  (riscvParamValues, debug_version,           debugVariants,             RV_GROUP(DBG),   "Specify required Debug Architecture version")},
    {  RVPV_PRE,     0,         default_rnmi_version,         VMI_ENUM_GROUP_PARAM_SPEC  (riscvParamValues, rnmi_version,            rnmiVariants,              RV_GROUP(INTXC), "Specify required RNMI Architecture version")},
    {  RVPV_ALL,     RVPV_1_12, default_Smepmp_version,       VMI_ENUM_GROUP_PARAM_SPEC  (riscvParamValues, Smepmp_version,          SmepmpVariants,            RV_GROUP(FUND),  "Specify required Smepmp Architecture version")},
    {  RVPV_CLIC,    0,         default_CLIC_version,         VMI_ENUM_GROUP_PARAM_SPEC  (riscvParamValues, CLIC_version,            CLICVariants,              RV_GROUP(CLIC),  "Specify required CLIC version")},
    {  RVPV_FPV,     0,         default_fp16_version,         VMI_ENUM_GROUP_PARAM_SPEC  (riscvParamValues, fp16_version,            fp16Variants,              RV_GROUP(V),     "Specify required 16-bit floating point format")},
    {  RVPV_FP,      0,         default_mstatus_fs_mode,      VMI_ENUM_GROUP_PARAM_SPEC  (riscvParamValues, mstatus_fs_mode,         FSModes,                   RV_GROUP(FP),    "Specify conditions causing update of mstatus.FS to dirty")},
    {  RVPV_PRE,     0,         default_debug_mode,           VMI_ENUM_GROUP_PARAM_SPEC  (riscvParamValues, debug_mode,              DMModes,                   RV_GROUP(DBG),   "Specify how Debug mode is implemented")},
    {  RVPV_DEBUG,   0,         default_debug_address,        VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, debug_address,           0, 0,          -1,         RV_GROUP(DBG),   "Specify address to which to jump to enter debug in vectored mode")},
    {  RVPV_DEBUG,   0,         default_dexc_address,         VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, dexc_address,            0, 0,          -1,         RV_GROUP(DBG),   "Specify address to which to jump on debug exception in vectored mode")},
    {  RVPV_DEBUG,   0,         default_debug_eret_mode,      VMI_ENUM_GROUP_PARAM_SPEC  (riscvParamValues, debug_eret_mode,         DERETModes,                RV_GROUP(DBG),   "Specify behavior for MRET, SRET or URET in Debug mode (nop, jump to dexc_address or trap to dexc_address)")},
    {  RVPV_DEBUG,   0,         default_dcsr_ebreak_mask,     VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, dcsr_ebreak_mask,        0, 0,          63,         RV_GROUP(DBG),   "Specify mask of dcsr.ebreak fields that reset to 1 (ebreak instructions enter Debug mode)")},
    {  RVPV_ALL,     0,         default_use_hw_reg_names,     VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, use_hw_reg_names,        False,                     RV_GROUP(ARTIF), "Specify whether to use hardware register names x0-x31 and f0-f31 instead of ABI register names")},
    {  RVPV_D,       0,         default_ABI_d,                VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, ABI_d,                   False,                     RV_GROUP(ARTIF), "Specify whether D registers are used for parameters (ABI SemiHosting)")},
    {  RVPV_ALL,     0,         0,                            VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, verbose,                 False,                     RV_GROUP(ARTIF), "Specify verbose output messages")},
    {  RVPV_ALL,     0,         0,                            VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, traceVolatile,           False,                     RV_GROUP(ARTIF), "Specify whether volatile registers (e.g. minstret) should be shown in change trace")},
    {  RVPV_MPCORE,  0,         default_numHarts,             VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, numHarts,                0, 0,          32,         RV_GROUP(FUND),  "Specify the number of hart contexts in a multiprocessor")},
    {  RVPV_S,       0,         default_updatePTEA,           VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, updatePTEA,              False,                     RV_GROUP(MEM),   "Specify whether hardware update of PTE A bit is supported")},
    {  RVPV_S,       0,         default_updatePTED,           VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, updatePTED,              False,                     RV_GROUP(MEM),   "Specify whether hardware update of PTE D bit is supported")},
    {  RVPV_ALL,     0,         default_unaligned,            VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, unaligned,               False,                     RV_GROUP(MEM),   "Specify whether the processor supports unaligned memory accesses")},
    {  RVPV_A,       0,         default_unalignedAMO,         VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, unalignedAMO,            False,                     RV_GROUP(MEM),   "Specify whether the processor supports unaligned memory accesses for AMO instructions")},
    {  RVPV_ALL,     0,         default_wfi_is_nop,           VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, wfi_is_nop,              False,                     RV_GROUP(ICSRB), "Specify whether WFI should be treated as a NOP (if not, halt while waiting for interrupts)")},
    {  RVPV_ALL,     0,         default_mtvec_is_ro,          VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, mtvec_is_ro,             False,                     RV_GROUP(INTXC), "Specify whether mtvec CSR is read-only")},
    {  RVPV_ALL,     0,         default_tvec_align,           VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, tvec_align,              0, 0,          (1<<16),    RV_GROUP(INTXC), "Specify hardware-enforced alignment of mtvec/stvec/utvec when Vectored interrupt mode enabled")},
    {  RVPV_ALL,     0,         default_counteren_mask,       VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, counteren_mask,          0, 0,          -1,         RV_GROUP(ICSRB), "Specify hardware-enforced mask of writable bits in mcounteren/scounteren registers")},
    {  RVPV_ALL,     0,         default_noinhibit_mask,       VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, noinhibit_mask,          0, 0,          -1,         RV_GROUP(ICSRB), "Specify hardware-enforced mask of always-zero bits in mcountinhibit register")},
    {  RVPV_ALL,     0,         default_mtvec_mask,           VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, mtvec_mask,              0, 0,          -1,         RV_GROUP(CSRMK), "Specify hardware-enforced mask of writable bits in mtvec register")},
    {  RVPV_S,       0,         default_stvec_mask,           VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, stvec_mask,              0, 0,          -1,         RV_GROUP(CSRMK), "Specify hardware-enforced mask of writable bits in stvec register")},
    {  RVPV_N,       0,         default_utvec_mask,           VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, utvec_mask,              0, 0,          -1,         RV_GROUP(CSRMK), "Specify hardware-enforced mask of writable bits in utvec register")},
    {  RVPV_CLIC,    0,         default_mtvt_mask,            VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, mtvt_mask,               0, 0,          -1,         RV_GROUP(CSRMK), "Specify hardware-enforced mask of writable bits in CLIC mtvt register")},
    {  RVPV_CLIC_S,  0,         default_stvt_mask,            VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, stvt_mask,               0, 0,          -1,         RV_GROUP(CSRMK), "Specify hardware-enforced mask of writable bits in CLIC stvt register")},
    {  RVPV_CLIC_N,  0,         default_utvt_mask,            VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, utvt_mask,               0, 0,          -1,         RV_GROUP(CSRMK), "Specify hardware-enforced mask of writable bits in CLIC utvt register")},
    {  RVPV_TRIG,    0,         default_tdata1_mask,          VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, tdata1_mask,             0, 0,          -1,         RV_GROUP(CSRMK), "Specify hardware-enforced mask of writable bits in Trigger Module tdata1 register")},
    {  RVPV_ALL,     0,         default_mip_mask,             VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, mip_mask,                WM32_mip,    0, -1,        RV_GROUP(CSRMK), "Specify hardware-enforced mask of writable bits in mip register")},
    {  RVPV_S,       0,         default_sip_mask,             VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, sip_mask,                WM32_sip,    0, -1,        RV_GROUP(CSRMK), "Specify hardware-enforced mask of writable bits in sip register")},
    {  RVPV_N,       0,         default_uip_mask,             VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, uip_mask,                WM32_uip,    0, -1,        RV_GROUP(CSRMK), "Specify hardware-enforced mask of writable bits in uip register")},
    {  RVPV_H,       0,         default_hip_mask,             VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, hip_mask,                WM32_hip,    0, -1,        RV_GROUP(CSRMK), "Specify hardware-enforced mask of writable bits in hip register")},
    {  RVPV_ALL,     RVPV_1_12, default_envcfg_mask,          VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, envcfg_mask,             WM64_envcfg, 0, -1,        RV_GROUP(CSRMK), "Specify hardware-enforced mask of writable bits in envcfg registers")},
    {  RVPV_ALL,     0,         default_mtvec_sext,           VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, mtvec_sext,              False,                     RV_GROUP(CSRMK), "Specify whether mtvec is sign-extended from most-significant bit")},
    {  RVPV_S,       0,         default_stvec_sext,           VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, stvec_sext,              False,                     RV_GROUP(CSRMK), "Specify whether stvec is sign-extended from most-significant bit")},
    {  RVPV_N,       0,         default_utvec_sext,           VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, utvec_sext,              False,                     RV_GROUP(CSRMK), "Specify whether utvec is sign-extended from most-significant bit")},
    {  RVPV_CLIC,    0,         default_mtvt_sext,            VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, mtvt_sext,               False,                     RV_GROUP(CSRMK), "Specify whether mtvt is sign-extended from most-significant bit")},
    {  RVPV_CLIC_S,  0,         default_stvt_sext,            VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, stvt_sext,               False,                     RV_GROUP(CSRMK), "Specify whether stvt is sign-extended from most-significant bit")},
    {  RVPV_CLIC_N,  0,         default_utvt_sext,            VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, utvt_sext,               False,                     RV_GROUP(CSRMK), "Specify whether utvt is sign-extended from most-significant bit")},
    {  RVPV_ALL,     0,         default_ecode_mask,           VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, ecode_mask,              0, 0,          -1,         RV_GROUP(INTXC), "Specify hardware-enforced mask of writable bits in xcause.ExceptionCode")},
    {  RVPV_ALL,     0,         default_ecode_nmi,            VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, ecode_nmi,               0, 0,          -1,         RV_GROUP(INTXC), "Specify xcause.ExceptionCode for NMI")},
    {  RVPV_RNMI,    0,         default_ecode_nmi_mask,       VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, ecode_nmi_mask,          0, 0,          -1,         RV_GROUP(INTXC), "Specify hardware-enforced mask of writable bits in mncause.ExceptionCode")},
    {  RVPV_ALL,     0,         default_tval_zero,            VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, tval_zero,               False,                     RV_GROUP(INTXC), "Specify whether mtval/stval/utval are hard wired to zero")},
    {  RVPV_ALL,     0,         default_tval_zero_ebreak,     VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, tval_zero_ebreak,        False,                     RV_GROUP(INTXC), "Specify whether mtval/stval/utval are set to zero by an ebreak")},
    {  RVPV_ALL,     0,         default_tval_ii_code,         VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, tval_ii_code,            False,                     RV_GROUP(INTXC), "Specify whether mtval/stval contain faulting instruction bits on illegal instruction exception")},
    {  RVPV_ALL,     0,         default_cycle_undefined,      VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, cycle_undefined,         False,                     RV_GROUP(ICSRB), "Specify that the cycle CSR is undefined")},
    {  RVPV_ALL,     0,         default_time_undefined,       VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, time_undefined,          False,                     RV_GROUP(ICSRB), "Specify that the time CSR is undefined")},
    {  RVPV_ALL,     0,         default_instret_undefined,    VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, instret_undefined,       False,                     RV_GROUP(ICSRB), "Specify that the instret CSR is undefined")},
    {  RVPV_ALL,     0,         default_hpmcounter_undefined, VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, hpmcounter_undefined,    False,                     RV_GROUP(ICSRB), "Specify that the hpmcounter CSRs are undefined")},
    {  RVPV_TRIG,    0,         default_tinfo_undefined,      VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, tinfo_undefined,         False,                     RV_GROUP(TRIG),  "Specify that the tinfo CSR is undefined")},
    {  RVPV_TRIG,    0,         default_tcontrol_undefined,   VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, tcontrol_undefined,      False,                     RV_GROUP(TRIG),  "Specify that the tcontrol CSR is undefined")},
    {  RVPV_TRIG,    0,         default_mcontext_undefined,   VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, mcontext_undefined,      False,                     RV_GROUP(TRIG),  "Specify that the mcontext CSR is undefined")},
    {  RVPV_TRIG,    0,         default_scontext_undefined,   VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, scontext_undefined,      False,                     RV_GROUP(TRIG),  "Specify that the scontext CSR is undefined")},
    {  RVPV_TRIG,    0,         default_mscontext_undefined,  VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, mscontext_undefined,     False,                     RV_GROUP(TRIG),  "Specify that the mscontext CSR is undefined (Debug Version 0.14.0 and later)")},
    {  RVPV_TRIG_H,  0,         default_hcontext_undefined,   VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, hcontext_undefined,      False,                     RV_GROUP(TRIG),  "Specify that the hcontext CSR is undefined")},
    {  RVPV_K,       0,         default_mnoise_undefined,     VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, mnoise_undefined,        False,                     RV_GROUP(K),     "Specify that the mnoise CSR is undefined")},
    {  RVPV_TRIG,    0,         default_amo_trigger,          VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, amo_trigger,             False,                     RV_GROUP(TRIG),  "Specify whether AMO load/store operations activate triggers")},
    {  RVPV_TRIG,    0,         default_no_hit,               VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, no_hit,                  False,                     RV_GROUP(TRIG),  "Specify that tdata1.hit is unimplemented")},
    {  RVPV_TRIG_S,  0,         default_no_sselect_2,         VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, no_sselect_2,            False,                     RV_GROUP(TRIG),  "Specify that textra.sselect=2 is not supported (no trigger match by ASID)")},
    {  RVPV_ALL,     0,         default_enable_CSR_bus,       VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, enable_CSR_bus,          False,                     RV_GROUP(ARTIF), "Add artifact CSR bus port, allowing CSR registers to be externally implemented")},
    {  RVPV_ALL,     0,         0,                            VMI_STRING_GROUP_PARAM_SPEC(riscvParamValues, CSR_remap,               "",                        RV_GROUP(ARTIF), "Comma-separated list of CSR number mappings, each of the form <csrName>=<number>")},
    {  RVPV_FP,      0,         default_d_requires_f,         VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, d_requires_f,            False,                     RV_GROUP(FP),    "If D and F extensions are separately enabled in the misa CSR, whether D is enabled only if F is enabled")},
    {  RVPV_FP,      0,         default_enable_fflags_i,      VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, enable_fflags_i,         False,                     RV_GROUP(FP),    "Whether fflags_i artifact register present (shows per-instruction floating point flags)")},
    {  RVPV_A,       0,         default_trap_preserves_lr,    VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, trap_preserves_lr,       False,                     RV_GROUP(INTXC), "Whether a trap preserves active LR/SC state")},
    {  RVPV_A,       0,         default_xret_preserves_lr,    VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, xret_preserves_lr,       False,                     RV_GROUP(INTXC), "Whether an xret instruction preserves active LR/SC state")},
    {  RVPV_V,       0,         default_require_vstart0,      VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, require_vstart0,         False,                     RV_GROUP(V),     "Whether CSR vstart must be 0 for non-interruptible vector instructions")},
    {  RVPV_V,       0,         default_align_whole,          VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, align_whole,             False,                     RV_GROUP(V),     "Whether whole-register load addresses must be aligned using the encoded EEW")},
    {  RVPV_V,       0,         default_vill_trap,            VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, vill_trap,               False,                     RV_GROUP(V),     "Whether illegal vtype values cause trap instead of setting vtype.vill")},
    {  RVPV_S,       0,         0,                            VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, ASID_cache_size,         8, 0,          256,        RV_GROUP(ARTIF), "Specifies the number of different ASIDs for which TLB entries are cached; a value of 0 implies no limit")},
    {  RVPV_PRE,     0,         default_trigger_num,          VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, trigger_num,             0, 0,          255,        RV_GROUP(TRIG),  "Specify the number of implemented hardware triggers")},
    {  RVPV_TRIG,    0,         default_tinfo,                VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, tinfo,                   0, 0,          0xffff,     RV_GROUP(TRIG),  "Override tinfo register (for all triggers)")},
    {  RVPV_TRIG,    0,         default_mcontext_bits,        VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, mcontext_bits,           0, 0,          0,          RV_GROUP(TRIG),  "Specify the number of implemented bits in mcontext")},
    {  RVPV_TRIG_S,  0,         default_scontext_bits,        VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, scontext_bits,           0, 0,          0,          RV_GROUP(TRIG),  "Specify the number of implemented bits in scontext")},
    {  RVPV_TRIG,    0,         default_mvalue_bits,          VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, mvalue_bits,             0, 0,          0,          RV_GROUP(TRIG),  "Specify the number of implemented bits in textra.mvalue (if zero, textra.mselect is tied to zero)")},
    {  RVPV_TRIG_S,  0,         default_svalue_bits,          VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, svalue_bits,             0, 0,          0,          RV_GROUP(TRIG),  "Specify the number of implemented bits in textra.svalue (if zero, textra.sselect is tied to zero)")},
    {  RVPV_TRIG,    0,         default_mcontrol_maskmax,     VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, mcontrol_maskmax,        0, 0,          63,         RV_GROUP(TRIG),  "Specify mcontrol.maskmax value")},
    {  RVPV_S,       0,         default_ASID_bits,            VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, ASID_bits,               0, 0,          0,          RV_GROUP(MEM),   "Specify the number of implemented ASID bits")},
    {  RVPV_H,       0,         default_VMID_bits,            VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, VMID_bits,               0, 0,          0,          RV_GROUP(H),     "Specify the number of implemented VMID bits")},
    {  RVPV_A,       0,         default_lr_sc_grain,          VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, lr_sc_grain,             1, 1,          (1<<16),    RV_GROUP(MEM),   "Specify byte granularity of ll/sc lock region (constrained to a power of two)")},
    {  RVPV_ALL,     0,         default_reset_address,        VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, reset_address,           0, 0,          -1,         RV_GROUP(INTXC), "Override reset vector address")},
    {  RVPV_ALL,     0,         default_nmi_address,          VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, nmi_address,             0, 0,          -1,         RV_GROUP(INTXC), "Override NMI vector address")},
    {  RVPV_RNMI,    0,         default_nmiexc_address,       VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, nmiexc_address,          0, 0,          -1,         RV_GROUP(INTXC), "Override RNMI exception vector address")},
    {  RVPV_ROOTPRE, 0,         default_CLINT_address,        VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, CLINT_address,           0, 0,          -1,         RV_GROUP(INTXC), "Specify base address of internal CLINT model (or 0 for no CLINT)")},
    {  RVPV_CLINT,   0,         default_mtime_Hz,             VMI_DBL_GROUP_PARAM_SPEC   (riscvParamValues, mtime_Hz,                0, 0,          1e9,        RV_GROUP(INTXC), "Specify clock frequency of CLINT mtime counter")},
#if(ENABLE_SSMPU)
    {  RVPV_S,       0,         default_MPU_grain,            VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, MPU_grain,               0, 0,          29,         RV_GROUP(MEM),   "Specify Ssmpu region granularity, G (0 => 4 bytes, 1 => 8 bytes, etc)")},
    {  RVPV_S,       0,         default_MPU_registers,        VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, MPU_registers,           0, 0,          64,         RV_GROUP(MEM),   "Specify the number of implemented Ssmpu address registers")},
    {  RVPV_S,       0,         default_MPU_decompose,        VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, MPU_decompose,           False,                     RV_GROUP(MEM),   "Whether unaligned Ssmpu accesses are decomposed into separate aligned accesses")},
#endif
    {  RVPV_ALL,     0,         default_PMP_grain,            VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, PMP_grain,               0, 0,          29,         RV_GROUP(MEM),   "Specify PMP region granularity, G (0 => 4 bytes, 1 => 8 bytes, etc)")},
    {  RVPV_ALL,     0,         default_PMP_registers,        VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, PMP_registers,           0, 0,          0,          RV_GROUP(MEM),   "Specify the number of implemented PMP address registers")},
    {  RVPV_ALL,     0,         default_PMP_max_page,         VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, PMP_max_page,            0, 0,          -1,         RV_GROUP(MEM),   "Specify the maximum size of PMP region to map if non-zero (may improve performance; constrained to a power of two)")},
    {  RVPV_ALL,     0,         default_PMP_decompose,        VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, PMP_decompose,           False,                     RV_GROUP(MEM),   "Whether unaligned PMP accesses are decomposed into separate aligned accesses")},
    {  RVPV_CMOMP,   0,         default_cmomp_bytes,          VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, cmomp_bytes,             0, 4,          32678,      RV_GROUP(MEM),   "Specify size of cache block for CMO management/prefetch instructions")},
    {  RVPV_CMOZ,    0,         default_cmoz_bytes,           VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, cmoz_bytes,              0, 4,          32678,      RV_GROUP(MEM),   "Specify size of cache block for CMO zero instructions")},
    {  RVPV_S,       0,         default_Sv_modes,             VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, Sv_modes,                0, 0,          (1<<16)-1,  RV_GROUP(MEM),   "Specify bit mask of implemented address translation modes (e.g. (1<<0)+(1<<8) indicates \"bare\" and \"Sv39\" modes may be selected in satp.MODE)")},
    {  RVPV_S,       0,         default_Svnapot_page_mask,    VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, Svnapot_page_mask,       0, 0,          -1,         RV_GROUP(MEM),   "Specify mask of implemented Svnapot intermediate page sizes (e.g. 1<<16 means 64KiB contiguous regions are supported)")},
    {  RVPV_S,       0,         default_Svpbmt,               VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Svpbmt,                  False,                     RV_GROUP(MEM),   "Specify that Svpbmt is implemented (page-based memory types)")},
    {  RVPV_S,       0,         default_Svinval,              VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Svinval,                 False,                     RV_GROUP(MEM),   "Specify that Svinval is implemented (fine-grained address translation cache invalidation)")},
    {  RVPV_ALL,     0,         default_local_int_num,        VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, local_int_num,           0, 0,          0,          RV_GROUP(INTXC), "Specify number of supplemental local interrupts")},
    {  RVPV_ALL,     0,         default_unimp_int_mask,       VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, unimp_int_mask,          0, 0,          -1,         RV_GROUP(INTXC), "Specify mask of unimplemented interrupts (e.g. 1<<9 indicates Supervisor external interrupt unimplemented)")},
    {  RVPV_ALL,     0,         default_force_mideleg,        VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, force_mideleg,           0, 0,          -1,         RV_GROUP(INTXC), "Specify mask of interrupts always delegated to lower-priority execution level from Machine execution level")},
    {  RVPV_S,       0,         default_force_sideleg,        VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, force_sideleg,           0, 0,          -1,         RV_GROUP(INTXC), "Specify mask of interrupts always delegated to User execution level from Supervisor execution level")},
    {  RVPV_ALL,     0,         default_no_ideleg,            VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, no_ideleg,               0, 0,          -1,         RV_GROUP(INTXC), "Specify mask of interrupts that cannot be delegated to lower-priority execution levels")},
    {  RVPV_ALL,     0,         default_no_edeleg,            VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, no_edeleg,               0, 0,          -1,         RV_GROUP(INTXC), "Specify mask of exceptions that cannot be delegated to lower-priority execution levels")},
    {  RVPV_ALL,     0,         default_external_int_id,      VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, external_int_id,         False,                     RV_GROUP(INTXC), "Whether to add nets allowing External Interrupt ID codes to be forced")},

    // fundamental configuration
    {  RVPV_ALL,     0,         0,                            VMI_ENDIAN_GROUP_PARAM_SPEC(riscvParamValues, endian,                                             RV_GROUP(FUND),  "Model endian")},
    {  RVPV_ALL,     0,         default_enable_expanded,      VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, enable_expanded,         False,                     RV_GROUP(FUND),  "Specify that 48-bit and 64-bit expanded instructions are supported")},
    {  RVPV_ALL,     0,         default_endianFixed,          VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, endianFixed,             False,                     RV_GROUP(FUND),  "Specify that data endianness is fixed (mstatus.{MBE,SBE,UBE} fields are read-only)")},

    // ISA configuration
    {  RVPV_PRE,     0,         default_misa_MXL,             VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, misa_MXL,                1, 1,          2,          RV_GROUP(FUND),  "Override default value of misa.MXL")},
    {  RVPV_PRE,     0,         default_misa_Extensions,      VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, misa_Extensions,         0, 0,          (1<<26)-1,  RV_GROUP(FUND),  "Override default value of misa.Extensions")},
    {  RVPV_PRE,     0,         0,                            VMI_STRING_GROUP_PARAM_SPEC(riscvParamValues, add_Extensions,          "",                        RV_GROUP(FUND),  "Add extensions specified by letters to misa.Extensions (for example, specify \"VD\" to add V and D features)")},
    {  RVPV_PRE,     0,         0,                            VMI_STRING_GROUP_PARAM_SPEC(riscvParamValues, sub_Extensions,          "",                        RV_GROUP(FUND),  "Remove extensions specified by letters from misa.Extensions (for example, specify \"VD\" to remove V and D features)")},
    {  RVPV_ALL,     0,         default_misa_Extensions_mask, VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, misa_Extensions_mask,    0, 0,          (1<<26)-1,  RV_GROUP(FUND),  "Override mask of writable bits in misa.Extensions")},
    {  RVPV_ALL,     0,         0,                            VMI_STRING_GROUP_PARAM_SPEC(riscvParamValues, add_Extensions_mask,     "",                        RV_GROUP(FUND),  "Add extensions specified by letters to mask of writable bits in misa.Extensions (for example, specify \"VD\" to add V and D features)")},
    {  RVPV_ALL,     0,         0,                            VMI_STRING_GROUP_PARAM_SPEC(riscvParamValues, sub_Extensions_mask,     "",                        RV_GROUP(FUND),  "Remove extensions specified by letters from mask of writable bits in misa.Extensions (for example, specify \"VD\" to remove V and D features)")},
    {  RVPV_PRE,     0,         0,                            VMI_STRING_GROUP_PARAM_SPEC(riscvParamValues, add_implicit_Extensions, "",                        RV_GROUP(FUND),  "Add extensions specified by letters to implicitly-present extensions not visible in misa.Extensions")},
    {  RVPV_PRE,     0,         0,                            VMI_STRING_GROUP_PARAM_SPEC(riscvParamValues, sub_implicit_Extensions, "",                        RV_GROUP(FUND),  "Remove extensions specified by letters from implicitly-present extensions not visible in misa.Extensions")},
    {  RVPV_ALL,     0,         default_Zicsr,                VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zicsr,                   False,                     RV_GROUP(FUND),  "Specify that Zicsr is implemented")},
    {  RVPV_ALL,     0,         default_Zifencei,             VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zifencei,                False,                     RV_GROUP(FUND),  "Specify that Zifencei is implemented")},
    {  RVPV_PRE,     0,         default_Zicbom,               VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zicbom,                  False,                     RV_GROUP(FUND),  "Specify that Zicbom is implemented")},
    {  RVPV_PRE,     0,         default_Zicbop,               VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zicbop,                  False,                     RV_GROUP(FUND),  "Specify that Zicbop is implemented")},
    {  RVPV_PRE,     0,         default_Zicboz,               VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zicboz,                  False,                     RV_GROUP(FUND),  "Specify that Zicboz is implemented")},
    {  RVPV_M,       0,         default_Zmmul,                VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zmmul,                   False,                     RV_GROUP(FUND),  "Specify that Zmmul is implemented")},
    {  RVPV_ALL,     0,         default_mvendorid,            VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, mvendorid,               0, 0,          -1,         RV_GROUP(CSRDV), "Override mvendorid register")},
    {  RVPV_ALL,     0,         default_marchid,              VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, marchid,                 0, 0,          -1,         RV_GROUP(CSRDV), "Override marchid register")},
    {  RVPV_ALL,     0,         default_mimpid,               VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, mimpid,                  0, 0,          -1,         RV_GROUP(CSRDV), "Override mimpid register")},
    {  RVPV_ALL,     0,         default_mhartid,              VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, mhartid,                 0, 0,          -1,         RV_GROUP(CSRDV), "Override mhartid register (or first mhartid of an incrementing sequence if this is an SMP variant)")},
    {  RVPV_ALL,     RVPV_1_12, default_mconfigptr,           VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, mconfigptr,              0, 0,          -1,         RV_GROUP(CSRDV), "Override mconfigptr register")},
    {  RVPV_ALL,     0,         default_mtvec,                VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, mtvec,                   0, 0,          -1,         RV_GROUP(CSRDV), "Override mtvec register")},
    {  RVPV_CLIC,    0,         default_mclicbase,            VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, mclicbase,               0, 0,          -1,         RV_GROUP(CLIC),  "Override mclicbase register")},
    {  RVPV_FP,      0,         0,                            VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, mstatus_FS,              0, 0,          3,          RV_GROUP(FP),    "Override default value of mstatus.FS (initial state of floating point unit)")},
    {  RVPV_V,       0,         0,                            VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, mstatus_VS,              0, 0,          3,          RV_GROUP(V),     "Override default value of mstatus.VS (initial state of vector unit)")},
    {  RVPV_SnotFP,  0,         default_mstatus_FS_zero,      VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, mstatus_FS_zero,         False,                     RV_GROUP(FP),    "Specify that mstatus.FS is hard-wired to zero")},
    {  RVPV_64,      0,         default_MXL_writable,         VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, MXL_writable,            False,                     RV_GROUP(CSRMK), "Specify that misa.MXL is writable (feature under development)")},
    {  RVPV_64S,     0,         default_SXL_writable,         VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, SXL_writable,            False,                     RV_GROUP(CSRMK), "Specify that mstatus.SXL is writable (feature under development)")},
    {  RVPV_64U,     0,         default_UXL_writable,         VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, UXL_writable,            False,                     RV_GROUP(CSRMK), "Specify that mstatus.UXL is writable (feature under development)")},
    {  RVPV_64H,     0,         default_VSXL_writable,        VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, VSXL_writable,           False,                     RV_GROUP(CSRMK), "Specify that hstatus.VSXL is writable (feature under development)")},
    {  RVPV_V,       0,         default_ELEN,                 VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, ELEN,                    0, ELEN_MIN,   ELEN_MAX,   RV_GROUP(V),     "Override ELEN (vector extension)")},
    {  RVPV_V,       0,         default_SLEN,                 VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, SLEN,                    0, SLEN_MIN,   VLEN_MAX,   RV_GROUP(V),     "Override SLEN (vector extension before version 1.0 only)")},
    {  RVPV_V,       0,         default_VLEN,                 VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, VLEN,                    0, SLEN_MIN,   VLEN_MAX,   RV_GROUP(V),     "Override VLEN (vector extension)")},
    {  RVPV_V,       0,         default_EEW_index,            VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, EEW_index,               0, 0,          ELEN_MAX,   RV_GROUP(V),     "Override maximum supported index EEW (vector extension, use ELEN if zero)")},
    {  RVPV_V,       0,         default_SEW_min,              VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, SEW_min,                 0, SEW_MIN,    ELEN_MAX,   RV_GROUP(V),     "Override minimum supported SEW (vector extension)")},
    {  RVPV_V,       0,         default_agnostic_ones,        VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, agnostic_ones,           False,                     RV_GROUP(V),     "Specify that vector agnostic elements are set to 1 (vector extension)")},
    {  RVPV_V,       0,         default_Zvlsseg,              VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zvlsseg,                 False,                     RV_GROUP(V),     "Specify that Zvlsseg is implemented (vector extension)")},
    {  RVPV_V,       0,         default_Zvamo,                VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zvamo,                   False,                     RV_GROUP(V),     "Specify that Zvamo is implemented (vector extension)")},
    {  RVPV_V,       0,         default_Zvediv,               VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zvediv,                  False,                     RV_GROUP(V),     "Specify that Zvediv is implemented (vector extension)")},
    {  RVPV_V,       0,         default_Zvqmac,               VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zvqmac,                  False,                     RV_GROUP(V),     "Specify that Zvqmac is implemented (vector extension)")},
    {  RVPV_V,       0,         default_Zve32x,               VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zve32x,                  False,                     RV_GROUP(V),     "Specify that Zve32x is implemented (vector extension)")},
    {  RVPV_V,       0,         default_Zve32f,               VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zve32f,                  False,                     RV_GROUP(V),     "Specify that Zve32f is implemented (vector extension)")},
    {  RVPV_V,       0,         default_Zve64x,               VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zve64x,                  False,                     RV_GROUP(V),     "Specify that Zve64x is implemented (vector extension)")},
    {  RVPV_V,       0,         default_Zve64f,               VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zve64f,                  False,                     RV_GROUP(V),     "Specify that Zve64f is implemented (vector extension)")},
    {  RVPV_V,       0,         default_Zve64d,               VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zve64d,                  False,                     RV_GROUP(V),     "Specify that Zve64d is implemented (vector extension)")},
    {  RVPV_BK,      0,         default_Zba,                  VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zba,                     False,                     RV_GROUP(B),     "Specify that Zba is implemented (bit manipulation extension)")},
    {  RVPV_BK,      0,         default_Zbb,                  VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zbb,                     False,                     RV_GROUP(B),     "Specify that Zbb is implemented (bit manipulation extension)")},
    {  RVPV_BK,      0,         default_Zbc,                  VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zbc,                     False,                     RV_GROUP(B),     "Specify that Zbc is implemented (bit manipulation extension)")},
    {  RVPV_BK,      0,         default_Zbe,                  VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zbe,                     False,                     RV_GROUP(B),     "Specify that Zbe is implemented (bit manipulation extension; ignored if version 1.0.0)")},
    {  RVPV_BK,      0,         default_Zbf,                  VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zbf,                     False,                     RV_GROUP(B),     "Specify that Zbf is implemented (bit manipulation extension; ignored if version 1.0.0)")},
    {  RVPV_BK,      0,         default_Zbm,                  VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zbm,                     False,                     RV_GROUP(B),     "Specify that Zbm is implemented (bit manipulation extension; ignored if version 1.0.0)")},
    {  RVPV_BK,      0,         default_Zbp,                  VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zbp,                     False,                     RV_GROUP(B),     "Specify that Zbp is implemented (bit manipulation extension; ignored if version 1.0.0)")},
    {  RVPV_BK,      0,         default_Zbr,                  VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zbr,                     False,                     RV_GROUP(B),     "Specify that Zbr is implemented (bit manipulation extension; ignored if version 1.0.0)")},
    {  RVPV_BK,      0,         default_Zbs,                  VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zbs,                     False,                     RV_GROUP(B),     "Specify that Zbs is implemented (bit manipulation extension)")},
    {  RVPV_BK,      0,         default_Zbt,                  VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zbt,                     False,                     RV_GROUP(B),     "Specify that Zbt is implemented (bit manipulation extension; ignored if version 1.0.0)")},
    {  RVPV_K,       0,         default_Zbkb,                 VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zbkb,                    False,                     RV_GROUP(K),     "Specify that Zbkb is implemented (cryptographic extension)")},
    {  RVPV_K,       0,         default_Zbkc,                 VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zbkc,                    False,                     RV_GROUP(K),     "Specify that Zbkc is implemented (cryptographic extension)")},
    {  RVPV_K,       0,         default_Zbkx,                 VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zbkx,                    False,                     RV_GROUP(K),     "Specify that Zbkx is implemented (cryptographic extension)")},
    {  RVPV_K,       0,         default_Zkr,                  VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zkr,                     False,                     RV_GROUP(K),     "Specify that Zkr is implemented (cryptographic extension)")},
    {  RVPV_K,       0,         default_Zknd,                 VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zknd,                    False,                     RV_GROUP(K),     "Specify that Zknd is implemented (cryptographic extension)")},
    {  RVPV_K,       0,         default_Zkne,                 VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zkne,                    False,                     RV_GROUP(K),     "Specify that Zkne is implemented (cryptographic extension)")},
    {  RVPV_K,       0,         default_Zknh,                 VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zknh,                    False,                     RV_GROUP(K),     "Specify that Zknh is implemented (cryptographic extension)")},
    {  RVPV_K,       0,         default_Zksed,                VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zksed,                   False,                     RV_GROUP(K),     "Specify that Zksed is implemented (cryptographic extension)")},
    {  RVPV_K,       0,         default_Zksh,                 VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zksh,                    False,                     RV_GROUP(K),     "Specify that Zksh is implemented (cryptographic extension)")},
    {  RVPV_FP,      0,         default_Zfh,                  VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zfh,                     False,                     RV_GROUP(FP),    "Specify that Zfh is implemented (IEEE half-precision floating point is supported)")},
    {  RVPV_FP,      0,         default_Zfhmin,               VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zfhmin,                  False,                     RV_GROUP(FP),    "Specify that Zfhmin is implemented (restricted IEEE half-precision floating point is supported)")},
    {  RVPV_K,       0,         default_Zkb,                  VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zkb,                     False,                     RV_GROUP(K),     "Specify that Zkb is implemented (cryptographic extension, deprecated alias of Zbkb)")},
    {  RVPV_K,       0,         default_Zkg,                  VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zkg,                     False,                     RV_GROUP(K),     "Specify that Zkg is implemented (cryptographic extension, deprecated alias of Zbkc)")},
    {  RVPV_32P,     0,         default_Zpsfoperand,          VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, Zpsfoperand,             False,                     RV_GROUP(P),     "Specify that Zpsfoperand is implemented (cryptographic extension)")},
    {  RVPV_FP,      0,         default_Zfinx_version,        VMI_ENUM_GROUP_PARAM_SPEC  (riscvParamValues, Zfinx_version,           ZfinxVariants,             RV_GROUP(FP),    "Specify version of Zfinx implemented (use integer register file for floating point instructions)")},
    {  RVPV_C,       0,         default_Zcea_version,         VMI_ENUM_GROUP_PARAM_SPEC  (riscvParamValues, Zcea_version,            ZceaVariants,              RV_GROUP(C),     "Specify version of Zcea implemented (code-size reduction extension)")},
    {  RVPV_C,       0,         default_Zceb_version,         VMI_ENUM_GROUP_PARAM_SPEC  (riscvParamValues, Zceb_version,            ZcebVariants,              RV_GROUP(C),     "Specify version of Zceb implemented (code-size reduction extension)")},
    {  RVPV_C,       0,         default_Zcee_version,         VMI_ENUM_GROUP_PARAM_SPEC  (riscvParamValues, Zcee_version,            ZceeVariants,              RV_GROUP(C),     "Specify version of Zcee implemented (code-size reduction extension)")},

    // CLIC configuration
    {  RVPV_ROOTPRE, 0,         default_CLICLEVELS,           VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, CLICLEVELS,              0, 0,          256,        RV_GROUP(CLIC),  "Specify number of interrupt levels implemented by CLIC, or 0 if CLIC absent")},
    {  RVPV_CLIC,    0,         default_CLICANDBASIC,         VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, CLICANDBASIC,            False,                     RV_GROUP(CLIC),  "Whether original basic mode is also implemented")},
    {  RVPV_CLIC,    0,         default_CLICVERSION,          VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, CLICVERSION,             0, 0,          255,        RV_GROUP(CLIC),  "Specify CLIC version")},
    {  RVPV_CLIC,    0,         default_CLICINTCTLBITS,       VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, CLICINTCTLBITS,          2, 2,          8,          RV_GROUP(CLIC),  "Specify number of bits implemented in clicintctl[i]")},
    {  RVPV_CLIC_NM, 0,         default_CLICCFGMBITS,         VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, CLICCFGMBITS,            0, 0,          0,          RV_GROUP(CLIC),  "Specify number of bits implemented for cliccfg.nmbits (also defines CLICPRIVMODES)")},
    {  RVPV_CLIC,    0,         default_CLICCFGLBITS,         VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, CLICCFGLBITS,            0, 0,          8,          RV_GROUP(CLIC),  "Specify number of bits implemented for cliccfg.nlbits")},
    {  RVPV_CLIC,    0,         default_CLICSELHVEC,          VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, CLICSELHVEC,             False,                     RV_GROUP(CLIC),  "Whether selective hardware vectoring supported")},
    {  RVPV_CLIC,    0,         default_CLICXNXTI,            VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, CLICXNXTI,               False,                     RV_GROUP(CLIC),  "Whether xnxti CSRs implemented")},
    {  RVPV_CLIC,    0,         default_CLICXCSW,             VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, CLICXCSW,                False,                     RV_GROUP(CLIC),  "Whether xscratchcsw/xscratchcswl CSRs implemented")},
    {  RVPV_CLIC,    0,         default_externalCLIC,         VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, externalCLIC,            False,                     RV_GROUP(CLIC),  "Whether CLIC is implemented externally (if False, then use implementation in this model)")},
    {  RVPV_CLIC,    0,         default_tvt_undefined,        VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, tvt_undefined,           False,                     RV_GROUP(CLIC),  "Specify that mtvt, stvt and utvt CSRs are undefined")},
    {  RVPV_CLIC,    0,         default_intthresh_undefined,  VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, intthresh_undefined,     False,                     RV_GROUP(CLIC),  "Specify that mintthreash, sintthresh and uintthresh CSRs are undefined")},
    {  RVPV_CLIC,    0,         default_mclicbase_undefined,  VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, mclicbase_undefined,     False,                     RV_GROUP(CLIC),  "Specify that mclicbase CSR is undefined")},
    {  RVPV_CLIC,    0,         default_posedge_0_63,         VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, posedge_0_63,            0, 0,          0,          RV_GROUP(CLIC),  "Mask of interrupts 0 to 63 that are fixed positive edge triggered")},
    {  RVPV_CLIC,    0,         default_poslevel_0_63,        VMI_UNS64_GROUP_PARAM_SPEC (riscvParamValues, poslevel_0_63,           0, 0,          0,          RV_GROUP(CLIC),  "Mask of interrupts 0 to 63 that are fixed positive level triggered")},
    {  RVPV_CLIC,    0,         default_posedge_other,        VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, posedge_other,           False,                     RV_GROUP(CLIC),  "Whether interrupts 64 and above are fixed positive edge triggered")},
    {  RVPV_CLIC,    0,         default_poslevel_other,       VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, poslevel_other,          False,                     RV_GROUP(CLIC),  "Whether interrupts 64 and above are fixed positive level triggered")},

    // Hypervisor configuration
    {  RVPV_H,       0,         default_GEILEN,               VMI_UNS32_GROUP_PARAM_SPEC (riscvParamValues, GEILEN,                  0, 0,          0,          RV_GROUP(H),     "Specify number of guest external interrupts")},
    {  RVPV_H,       0,         default_xtinst_basic,         VMI_BOOL_GROUP_PARAM_SPEC  (riscvParamValues, xtinst_basic,            False,                     RV_GROUP(H),     "Specify that only pseudo-instructions are reported by htinst/mtinst")},

    // KEEP LAST
    {  RVPV_ALL,     0,         0,                            VMI_END_PARAM}
};

//
// Return any parent of the passed processor
//
inline static riscvP getParent(riscvP riscv) {
    return riscv ? (riscvP)vmirtGetSMPParent((vmiProcessorP)riscv) : 0;
}

//
// Is the processor a member of an SMP?
//
static Bool isSMPMember(riscvP riscv) {

    riscvP parent = getParent(riscv);

    return (parent && !riscvIsCluster(parent));
}

//
// Should this configuration be presented as a public one?
//
inline static Bool selectConfig(riscvConfigCP cfg) {
    return True;
}

//
// Should this parameter be presented as a pre-parameter?
//
static Bool selectPreParameter(riscvP riscv, riscvParameterP param) {

    // ignore all parameters except variant and explicit pre-parameters
    if(!(param->variant & (RVPV_VARIANT|RVPV_PRE))) {
        return False;
    }

    // handle parameters present at root level only
    if((param->variant & RVPV_ROOT) && getParent(riscv)) {
        return False;
    }

    return True;
}

//
// Should this parameter be presented as a public one for the selected variant?
//
static Bool selectParameter(
    riscvP          riscv,
    riscvConfigCP   cfg,
    riscvParameterP param
) {
    if(cfg) {

        // use architecture from configuration (or assume all features are
        // present if this is a cluster)
        riscvArchitecture arch = cfg->arch ? : -1;

        // ignore parameters specific to later privileged versions
        if(param->minPV>cfg->priv_version) {
            return False;
        }

        // cluster-specific parameters are only used by clusters
        if(param->variant & RVPV_CLUSTER) {
            return cfg->members;
        }

        // handle parameters present at root level only
        if((param->variant & RVPV_ROOT) && getParent(riscv)) {
            return False;
        }

        // cluster exposes only variant and root parameters
        if(!(param->variant & (RVPV_VARIANT|RVPV_ROOT)) && cfg->members) {
            return False;
        }

        // include parameters that are only required for multicore variants
        if(param->variant & RVPV_MPCORE) {
            return cfg->numHarts;
        }

        // include parameters that are only required when floating-point is
        // present
        if((param->variant & RVPV_FP) && !(arch&ISA_DF)) {
            return False;
        }

        // include parameters that are only required when compressed
        // instructions are present
        if((param->variant & RVPV_C) && !(arch&ISA_C)) {
            return False;
        }

        // include parameters that are only required when double floating-point
        // is present
        if((param->variant & RVPV_D) && !(arch&ISA_D)) {
            return False;
        }

        // include parameters that are only required when atomic extension is
        // present
        if((param->variant & RVPV_A) && !(arch&ISA_A)) {
            return False;
        }

        // include parameters that are only required when crypto extension is
        // present
        if((param->variant & RVPV_K) && !(arch&ISA_K)) {
            return False;
        }

        // include parameters that are only required when DSP extension is
        // present
        if((param->variant & RVPV_P) && !(arch&ISA_P)) {
            return False;
        }

        // include parameters that are only required when bitmanip or crypto
        // extension is present
        if((param->variant & RVPV_BK) && !(arch&(ISA_B|ISA_K))) {
            return False;
        }

        // include parameters that are only required for 32-bit architecture
        if((param->variant & RVPV_32) && !(arch&ISA_XLEN_32)) {
            return False;
        }

        // include parameters that are only required for 64-bit architecture
        if((param->variant & RVPV_64) && !(arch&ISA_XLEN_64)) {
            return False;
        }

        // include parameters that are only required when Supervisor mode is
        // present
        if((param->variant & RVPV_S) && !(arch&ISA_S)) {
            return False;
        }

        // include parameters that are only required when Supervisor mode is
        // present and floating-point is absent
        if((param->variant & RVPV_SnotFP) && ((arch&ISA_DFS)!=ISA_S)) {
            return False;
        }

        // include parameters that are only required when User mode is
        // present
        if((param->variant & RVPV_U) && !(arch&ISA_U)) {
            return False;
        }

        // include parameters that are only required when Hypervisor mode is
        // present
        if((param->variant & RVPV_H) && !(arch&ISA_H)) {
            return False;
        }

        // include parameters that are only required when User mode interrupts
        // are implemented
        if((param->variant & RVPV_N) && !(arch&ISA_N)) {
            return False;
        }

        // include parameters that are only required when M extension is
        // implemented
        if((param->variant & RVPV_M) && !(arch&ISA_M)) {
            return False;
        }

        // include parameters that are only required when Vector extension is
        // implemented
        if((param->variant & RVPV_V) && !(arch&ISA_V)) {
            return False;
        }

        // include parameters that are only required when CLICCFGMBITS can be
        // non-zero
        if((param->variant & RVPV_NMBITS) && !getCLICCFGMBITSMax(cfg)) {
            return False;
        }

        if(param->variant & RVPV_DBGT) {

            // include parameters that are only required when debug mode or
            // triggers are implemented
            if(!(cfg->debug_mode || cfg->trigger_num)) {
                return False;
            }

        } else {

            // include parameters that are only required when debug mode is
            // implemented
            if((param->variant & RVPV_DEBUG) && !cfg->debug_mode) {
                return False;
            }

            // include parameters that are only required when triggers are
            // implemented
            if((param->variant & RVPV_TRIG) && !cfg->trigger_num) {
                return False;
            }
        }

        // include parameters that are only required when RNMI is implemented
        if((param->variant & RVPV_RNMI) && !cfg->rnmi_version) {
            return False;
        }

        // include parameters that are only required when CLIC is implemented
        if((param->variant & RVPV_CLIC) && !cfg->CLICLEVELS) {
            return False;
        }

        // include parameters that are only required when CLINT is implemented
        if((param->variant & RVPV_CLINT) && !cfg->CLINT_address) {
            return False;
        }

        // include parameters that are only required for Zicbom/Zicbop
        if((param->variant & RVPV_CMOMP) && !(cfg->Zicbom || cfg->Zicbop)) {
            return False;
        }

        // include parameters that are only required for Zicboz
        if((param->variant & RVPV_CMOZ) && !cfg->Zicboz) {
            return False;
        }
    }

    return True;
}

//
// Count the number of visible variants
//
static Uns32 countVariants(riscvConfigCP cfg) {

    Uns32 i = 0;

    while(cfg->name) {
        i++;
        cfg++;
    }

    return i;
}

//
// Count the number of visible pre-parameters
//
static Uns32 countPreParameters(riscvP riscv, riscvParameterP param) {

    Uns32 i = 0;

    while(param->parameter.name) {

        if(selectPreParameter(riscv, param)) {
            i++;
        }

        param++;
    }

    return i;
}

//
// Count the number of visible parameters
//
static Uns32 countParameters(
    riscvP          riscv,
    riscvConfigCP   cfg,
    riscvParameterP param
) {
    Uns32 i = 0;

    while(param->parameter.name) {

        if(selectParameter(riscv, cfg, param)) {
            i++;
        }

        param++;
    }

    return i;
}

//
// Create configuration list applicable to the indicated variant, or a superset
// configuration list of no variant is specified
//
static vmiEnumParameterP createVariantList(riscvP riscv) {

    riscvConfigCP     cfgList = riscvGetConfigList(riscv);
    riscvConfigCP     cfg;
    vmiEnumParameterP result;
    vmiEnumParameterP prm;
    Uns32             i;

    // count the number of entries in the variant list
    Uns32 entries = countVariants(cfgList);

    // allocate the variant list, including NULL terminator
    result = STYPE_CALLOC_N(vmiEnumParameter, entries+1);

    // fill visible entries in the variant list
    for(i=0, prm=result, cfg=cfgList; cfg->name; i++, cfg++) {

        if(selectConfig(cfg)) {

            prm->name  = cfg->name;
            prm->value = i;

            prm++;
        }
    }

    // return resulting list
    return result;
}

//
// Create pre-parameter list
//
static vmiParameterP createPreParameterList(riscvP riscv, riscvConfigCP first) {

    riscvParameterP src = parameters;
    vmiParameterP   dst;
    vmiParameterP   result;
    Uns32           i;

    // count the number of entries in the parameter list
    Uns32 entries = countPreParameters(riscv, src);

    // allocate the pre-parameter list, including NULL terminator
    result = STYPE_CALLOC_N(vmiParameter, entries+1);

    for(i=0, dst=result; src->parameter.name; i++, src++) {

        if(selectPreParameter(riscv, src)) {

            *dst = src->parameter;

            // fill variant list
            if(src->variant & RVPV_VARIANT) {
                dst->u.enumParam.legalValues = riscv->variantList;
            }

            // override default if required
            if(src->defaultCB) {
                src->defaultCB(first, dst);
            }

            dst++;
        }
    }

    // return resulting list
    return result;
}

//
// Create parameter list applicable to the indicated variant
//
static vmiParameterP createParameterList(riscvP riscv, riscvConfigCP cfg) {

    riscvParameterP src = parameters;
    vmiParameterP   dst;
    vmiParameterP   result;
    Uns32           i;

    // create default cluster variants string
    riscv->clusterVariants = riscvNewClusterVariantString(riscv);

    // count the number of entries in the parameter list
    Uns32 entries = countParameters(riscv, cfg, src);

    // allocate the parameter list, including NULL terminator
    result = STYPE_CALLOC_N(vmiParameter, entries+1);

    for(i=0, dst=result; src->parameter.name; i++, src++) {

        if(selectParameter(riscv, cfg, src)) {

            *dst = src->parameter;

            // fill variant list
            if(src->variant & RVPV_VARIANT) {
                dst->u.enumParam.legalValues = riscv->variantList;
            }

            // fill member variants if required
            if(src->variant & RVPV_CLUSTER) {
                dst->u.stringParam.defaultValue = riscv->clusterVariants;
            }

            // override default if required
            if(src->defaultCB) {
                src->defaultCB(cfg, dst);
            }

            dst++;
        }
    }

    // return resulting list
    return result;
}

//
// Refine variant if this is a cluster member
//
static const char *refineVariant(riscvP riscv, const char *variant) {

    if(riscv && riscvIsClusterMember(riscv)) {
        variant = riscvGetMemberVariant(riscv);
    }

    return variant;
}

//
// Function to iterate the pre-parameter specifications
//
VMI_PROC_PARAM_SPECS_FN(riscvGetPreParamSpec) {

    riscvP riscv = (riscvP)processor;

    if(isSMPMember(riscv)) {

        // allow parameterization of clusters and root level objects only
        return 0;

    } else if(!prev) {

        riscvConfigCP cfgList = riscvGetConfigList(riscv);

        // if this is a cluster member, use the member configuration to fill
        // parameters
        if(riscvIsClusterMember(riscv)) {
            cfgList = riscvGetNamedConfig(cfgList, riscvGetMemberVariant(riscv));
        }

        // fill variants and create pre-parameter list
        riscv->variantList = createVariantList(riscv);
        riscv->parameters  = createPreParameterList(riscv, cfgList);

        // return first pre-parameter
        return riscv->parameters;

    } else {

        // return next pre-parameter
        vmiParameterP this = prev+1;
        return this && this->name ? this : 0;
    }
}

//
// Append extensions in the given list to the name, prefixed by the operation
// character
//
static void appendExtensions(char *name, riscvArchitecture arch, char op) {

    if(arch) {

        char *tail = name + strlen(name);
        char  extension;

        // append operation
        *tail++ = op;

        // append modified architectural settings
        for(extension='A'; arch; arch>>=1, extension++) {
            if(arch&1) {
                *tail++ = extension;
            }
        }

        // terminate string
        *tail++ = 0;
    }
}

//
// Apply pre-parameter value if it has been set (if not, leave as per-variant
// default)
//
#define APPLY_PREPARAM_IF_SET(_PROC, _PARAMS, _NAME) { \
    if(_PARAMS->SETBIT(_NAME)) {                    \
        _PROC->configInfo._NAME = params->_NAME;    \
    }                                               \
}

//
// Return arch modified so that it is self-consistent
//
inline static riscvArchitecture fixArch(riscvArchitecture arch) {

    // S extension implies U extension, and N extension requires U extension
    if(arch&ISA_S) {
        arch |= ISA_U;
    } else if(!(arch&ISA_U)) {
        arch &= ~ISA_N;
    }

    return arch;
}

//
// Function to apply pre-parameter values
//
VMI_SET_PARAM_VALUES_FN(riscvGetPreParamValues) {

    riscvP        riscv   = (riscvP)processor;
    riscvConfigCP cfgList = riscvGetConfigList(riscv);

    if(isSMPMember(riscv)) {

        // no action - all parameters for SMP processors are specified at the
        // SMP level, and the hart-specific mhartid parameter specifies the
        // *first* index of an incrementing sequence in this case

    } else {

        // get raw variant
        riscvParamValuesP params  = (riscvParamValuesP)parameterValues;
        riscvConfigCP     match   = cfgList + params->variant;

        // delete pre-parameter definitions
        STYPE_FREE(riscv->parameters);

        // refine variant in cluster if required
        const char *variant = refineVariant(riscv, match->name);
        riscv->configInfo = *riscvGetNamedConfig(cfgList, variant);

        // override architecture versions if required
        APPLY_PREPARAM_IF_SET(riscv, params, user_version);
        APPLY_PREPARAM_IF_SET(riscv, params, priv_version);

        // old and new misa architecture
        riscvArchitecture archExplicit = riscv->configInfo.arch;
        riscvArchitecture archImplicit = riscv->configInfo.archImplicit;
        riscvArchitecture oldArch      = fixArch(archExplicit|archImplicit);
        riscvArchitecture newArch      = oldArch;

        // apply misa_Extensions override if required
        if(SETBIT(params->misa_Extensions)) {
            newArch = params->misa_Extensions | (newArch & (-1 << XLEN_SHIFT));
        }

        // apply sub_Extensions and add_Extensions overrides if required
        newArch &= ~riscvParseExtensions(params->sub_Extensions);
        newArch |=  riscvParseExtensions(params->add_Extensions);

        // apply sub_implicit_Extensions and add_implicit_Extensions overrides
        archImplicit &= ~riscvParseExtensions(params->sub_implicit_Extensions);
        archImplicit |=  riscvParseExtensions(params->add_implicit_Extensions);

        // include implicit features in full list
        newArch |= archImplicit;

        // ensure result is self-consistent
        newArch = fixArch(newArch);

        // update variant to show modified extensions if required
        if(oldArch!=newArch) {

            char tmp[strlen(variant)+32];

            // seed new name
            strcpy(tmp, variant);

            // append removed and added extensions
            appendExtensions(tmp, oldArch&~newArch, '-');
            appendExtensions(tmp, newArch&~oldArch, '+');

            // set variant name
            vmirtSetProcessorVariant(processor, tmp);
        }

        // apply updated architecture
        riscv->configInfo.arch         = newArch;
        riscv->configInfo.archImplicit = archImplicit;

        // H extension requires privileged version 1.12 or later (for mstatush)
        if((newArch&ISA_H) && (riscv->configInfo.priv_version<RVPV_1_12)) {
            riscv->configInfo.priv_version = RVPV_1_12;
        }

        // force CLICLEVELS to valid value
        if(params->CLICLEVELS==1) {
            vmiMessage("W", CPU_PREFIX"_ICL",
                "Illegal CLICLEVELS=1 specified; using CLICLEVELS=2"
            );
            params->CLICLEVELS = 2;
        }

        // apply CLICLEVELS override if required
        APPLY_PREPARAM_IF_SET(riscv, params, CLICLEVELS);

        // apply debug_mode override if required
        APPLY_PREPARAM_IF_SET(riscv, params, debug_mode);

        // apply trigger_num override if required
        APPLY_PREPARAM_IF_SET(riscv, params, trigger_num);

        // apply rnmi_version override if required
        APPLY_PREPARAM_IF_SET(riscv, params, rnmi_version);

        // apply CLINT_address override if required
        APPLY_PREPARAM_IF_SET(riscv, params, CLINT_address);

        // apply Zicbom/Zicbop/Zicboz overrides if required
        APPLY_PREPARAM_IF_SET(riscv, params, Zicbom);
        APPLY_PREPARAM_IF_SET(riscv, params, Zicbop);
        APPLY_PREPARAM_IF_SET(riscv, params, Zicboz);

        // create full parameter list
        riscv->parameters = createParameterList(riscv, &riscv->configInfo);
    }
}

//
// Get the size of the parameter values table
//
VMI_PROC_PARAM_TABLE_SIZE_FN(riscvParamValueSize) {

    return sizeof(riscvParamValues);
}

//
// Function to iterate the parameter specifications
//
VMI_PROC_PARAM_SPECS_FN(riscvGetParamSpec) {

    riscvP        riscv = (riscvP)processor;
    vmiParameterP this  = prev ? prev+1 : riscv->parameters;

    return this && this->name ? this : 0;
}

//
// Free parameter definitions
//
void riscvFreeParameters(riscvP riscv) {

    if(riscv->variantList) {
        STYPE_FREE(riscv->variantList);
    }

    if(riscv->parameters) {
        STYPE_FREE(riscv->parameters);
    }
}

//
// Return Privileged Architecture description
//
const char *riscvGetPrivVersionDesc(riscvP riscv) {
    return privVariants[RISCV_PRIV_VERSION(riscv)].description;
}

//
// Return User Architecture description
//
const char *riscvGetUserVersionDesc(riscvP riscv) {
    return userVariants[RISCV_USER_VERSION(riscv)].description;
}

//
// Return Vector Architecture description
//
const char *riscvGetVectorVersionDesc(riscvP riscv) {
    return vectorVariants[RISCV_VECT_VERSION(riscv)].description;
}

//
// Return Bit Manipulation Architecture description
//
const char *riscvGetBitManipVersionDesc(riscvP riscv) {
    return bitmanipVariants[RISCV_BITMANIP_VERSION(riscv)].description;
}

//
// Return Hypervisor Architecture description
//
const char *riscvGetHypervisorVersionDesc(riscvP riscv) {
    return hypervisorVariants[RISCV_HYP_VERSION(riscv)].description;
}

//
// Return Cryptographic Architecture description
//
const char *riscvGetCryptographicVersionDesc(riscvP riscv) {
    return cryptoVariants[RISCV_CRYPTO_VERSION(riscv)].description;
}

//
// Return DSP Architecture description
//
const char *riscvGetDSPVersionDesc(riscvP riscv) {
    return DSPVariants[RISCV_DSP_VERSION(riscv)].description;
}

//
// Return Debug Architecture description
//
const char *riscvGetDebugVersionDesc(riscvP riscv) {
    return debugVariants[RISCV_DBG_VERSION(riscv)].description;
}

//
// Return RNMI Architecture name
//
const char *riscvGetRNMIVersionName(riscvP riscv) {
    return rnmiVariants[RISCV_RNMI_VERSION(riscv)].name;
}

//
// Return Smepmp Architecture name
//
const char *riscvGetSmepmpVersionName(riscvP riscv) {
    return SmepmpVariants[RISCV_SMEPMP_VERSION(riscv)].name;
}

//
// Return CLIC description
//
const char *riscvGetCLICVersionDesc(riscvP riscv) {
    return CLICVariants[RISCV_CLIC_VERSION(riscv)].description;
}

//
// Return Zfinx version description
//
const char *riscvGetZfinxVersionDesc(riscvP riscv) {
    return ZfinxVariants[Zfinx(riscv)].description;
}

//
// Return Zcea version name
//
const char *riscvGetZceaVersionName(riscvP riscv) {
    return ZceaVariants[Zcea(riscv)].name;
}

//
// Return Zceb version name
//
const char *riscvGetZcebVersionName(riscvP riscv) {
    return ZcebVariants[Zceb(riscv)].name;
}

//
// Return Zcee version name
//
const char *riscvGetZceeVersionName(riscvP riscv) {
    return ZceeVariants[Zcee(riscv)].name;
}

//
// Return 16-bit floating point description
//
const char *riscvGetFP16VersionDesc(riscvP riscv) {
    return fp16Variants[RISCV_FP16_VERSION(riscv)].description;
}

//
// Return mstatus.FS mode name
//
const char *riscvGetFSModeName(riscvP riscv) {
    return FSModes[RISCV_FS_MODE(riscv)].name;
}


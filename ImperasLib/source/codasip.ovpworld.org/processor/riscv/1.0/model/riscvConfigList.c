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

// base model header files
#include "riscvConfig.h"
#include "riscvVariant.h"


//
// Emit common restrictions
//
static void restrictionsCommon(riscvP riscv, vmiDocNodeP node) {

    vmidocAddText(
        node,
        "No Codasip specific CSR initial values are included."
    );
    vmidocAddText(
        node,
        "No Codasip specific extensions are implemented."
    );
}

//
// Emit initial variant restrictions
//
static RV_DOC_FN(restrictionsInitial) {

    vmidocAddText(
        node,
        "This variant is under development. It defines only the RISCV extensions implemented."
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

#define CODASIP_USER_VERSION  RVUV_2_2
#define CODASIP_PRIV_VERSION  RVPV_1_11
#define CODASIP_DSP_VERSION   RVDSPV_0_5_2


//
// Defined configurations
//
static const riscvConfig configList[] = {
    {
        .name             = "L10",
        .arch             = RV32E|ISA_C,
        .archMask         = 0,
        .numHarts         = 0,
        .user_version     = CODASIP_USER_VERSION,
        .priv_version     = CODASIP_USER_VERSION,
        .specificDocs     = specificDocsInitial,
        .restrictionsCB   = restrictionsInitial,
    },
    {
        .name             = "L30",
        .arch             = RV32I|ISA_C,
        .archMask         = 0,
        .numHarts         = 0,
        .user_version     = CODASIP_USER_VERSION,
        .priv_version     = CODASIP_USER_VERSION,
        .specificDocs     = specificDocsInitial,
        .restrictionsCB   = restrictionsInitial,
    },
    {
        .name             = "L30F",
        .arch             = RV32I|ISA_C|ISA_F,
        .archMask         = 0,
        .numHarts         = 0,
        .user_version     = CODASIP_USER_VERSION,
        .priv_version     = CODASIP_USER_VERSION,
        .specificDocs     = specificDocsInitial,
        .restrictionsCB   = restrictionsInitial,
    },
    {
        .name             = "L50",
        .arch             = RV32I|ISA_C,
        .archMask         = 0,
        .numHarts         = 0,
        .user_version     = CODASIP_USER_VERSION,
        .priv_version     = CODASIP_USER_VERSION,
        .specificDocs     = specificDocsInitial,
        .restrictionsCB   = restrictionsInitial,
    },
    {
        .name             = "L50F",
        .arch             = RV32I|ISA_C|ISA_F,
        .archMask         = 0,
        .numHarts         = 0,
        .user_version     = CODASIP_USER_VERSION,
        .priv_version     = CODASIP_USER_VERSION,
        .specificDocs     = specificDocsInitial,
        .restrictionsCB   = restrictionsInitial,
    },
    {
        .name             = "H50X",
        .arch             = RV64I|ISA_C,
        .archMask         = 0,
        .numHarts         = 0,
        .user_version     = CODASIP_USER_VERSION,
        .priv_version     = CODASIP_USER_VERSION,
        .specificDocs     = specificDocsInitial,
        .restrictionsCB   = restrictionsInitial,
    },
    {
        .name             = "H50XF",
        .arch             = RV64I|ISA_C|ISA_F,
        .archMask         = 0,
        .numHarts         = 0,
        .user_version     = CODASIP_USER_VERSION,
        .priv_version     = CODASIP_USER_VERSION,
        .specificDocs     = specificDocsInitial,
        .restrictionsCB   = restrictionsInitial,
    },
    {
        .name             = "A70X",
        .arch             = RV64GC|ISA_S|ISA_U,
        .archMask         = 0,
        .numHarts         = 0,
        .user_version     = CODASIP_USER_VERSION,
        .priv_version     = CODASIP_USER_VERSION,
        .specificDocs     = specificDocsInitial,
        .restrictionsCB   = restrictionsInitial,
    },
    {
        .name             = "A70XP",
        .arch             = RV64GC|ISA_P|ISA_S|ISA_U,
        .archMask         = 0,
        .numHarts         = 0,
        .user_version     = CODASIP_USER_VERSION,
        .priv_version     = CODASIP_USER_VERSION,
        .dsp_version      = CODASIP_DSP_VERSION,
        .specificDocs     = specificDocsInitial,
        .restrictionsCB   = restrictionsInitial,
    },
    {
        .name             = "A70X-MP",
        .arch             = RV64GC|ISA_S|ISA_U,
        .archMask         = 0,
        .numHarts         = 1,
        .user_version     = CODASIP_USER_VERSION,
        .priv_version     = CODASIP_USER_VERSION,
        .specificDocs     = specificDocsInitial,
        .restrictionsCB   = restrictionsInitial,
    },
    {
        .name             = "A70XP-MP",
        .arch             = RV64GC|ISA_P|ISA_S|ISA_U,
        .archMask         = 0,
        .numHarts         = 1,
        .user_version     = CODASIP_USER_VERSION,
        .priv_version     = CODASIP_USER_VERSION,
        .dsp_version      = CODASIP_DSP_VERSION,
        .specificDocs     = specificDocsInitial,
        .restrictionsCB   = restrictionsInitial,
    },
    {
        .name             = "A71X",
        .arch             = RV64GC|ISA_S|ISA_U,
        .archMask         = 0,
        .numHarts         = 0,
        .user_version     = CODASIP_USER_VERSION,
        .priv_version     = CODASIP_USER_VERSION,
        .dsp_version      = CODASIP_DSP_VERSION,
        .specificDocs     = specificDocsInitial,
        .restrictionsCB   = restrictionsInitial,
    },
    {0} // null terminator
};

//
// This returns the supported configuration list
//
riscvConfigCP riscvGetConfigList(riscvP riscv) {
    return configList;
}


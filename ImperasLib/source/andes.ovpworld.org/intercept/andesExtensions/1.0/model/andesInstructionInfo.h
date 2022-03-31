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


////////////////////////////////////////////////////////////////////////////////
// DATA FOR 32-BIT INSTRUCTIONS
////////////////////////////////////////////////////////////////////////////////

//
// Attribute entries for 32-bit instructions like ADDIGP
//
#define ATTR32_ADDIGP(_NAME, _GENERIC, _ARCH, _OPCODE, _PATTERN) [IT32_##_NAME] = { \
    opcode   : _OPCODE,             \
    pattern  : _PATTERN,            \
    format   : FMT_R1_SIMM,         \
    type     : AN_IT_##_GENERIC,    \
    arch     : _ARCH,               \
    r1       : RS_X_11_7,           \
    r2       : RS_GP,               \
    cs1      : CS_LBGP_IMM,         \
}

//
// Attribute entries for 32-bit instructions like BCC
//
#define ATTR32_BBC(_NAME, _GENERIC, _ARCH, _OPCODE, _PATTERN) [IT32_##_NAME] = { \
    opcode   : _OPCODE,             \
    pattern  : _PATTERN,            \
    format   : FMT_R1_UIMM_TGT,     \
    type     : AN_IT_##_GENERIC,    \
    arch     : _ARCH,               \
    r1       : RS_X_19_15,          \
    cs1      : CS_BBC_IMM,          \
    cs2      : CU_BBC_SHAMT,        \
}

//
// Attribute entries for 32-bit instructions like BEQC
//
#define ATTR32_BEQC(_NAME, _GENERIC, _ARCH, _OPCODE, _PATTERN) [IT32_##_NAME] = { \
    opcode   : _OPCODE,             \
    pattern  : _PATTERN,            \
    format   : FMT_R1_UIMM_TGT,     \
    type     : AN_IT_##_GENERIC,    \
    arch     : _ARCH,               \
    r1       : RS_X_19_15,          \
    cs1      : CS_BBC_IMM,          \
    cs2      : CU_BEQC_CIMM,        \
}

//
// Attribute entries for 32-bit instructions like BFOS
//
#define ATTR32_BFOS(_NAME, _GENERIC, _ARCH, _OPCODE, _PATTERN) [IT32_##_NAME] = { \
    opcode   : _OPCODE,             \
    pattern  : _PATTERN,            \
    format   : FMT_R1_R2_UIMM_UIMM, \
    type     : AN_IT_##_GENERIC,    \
    arch     : _ARCH,               \
    r1       : RS_X_11_7,           \
    r2       : RS_X_19_15,          \
    cs1      : CU_BFOS_MSB,         \
    cs2      : CU_BFOS_LSB,         \
}

//
// Attribute entries for 32-bit instructions like LEA.H
//
#define ATTR32_LEA(_NAME, _GENERIC, _ARCH, _OPCODE, _PATTERN) [IT32_##_NAME] = { \
    opcode   : _OPCODE,             \
    pattern  : _PATTERN,            \
    format   : FMT_R1_R2_R3,        \
    type     : AN_IT_##_GENERIC,    \
    arch     : _ARCH,               \
    r1       : RS_X_11_7,           \
    r2       : RS_X_19_15,          \
    r3       : RS_X_24_20,          \
    memBits  : MBS_26_25,           \
    ze32     : ZE32_28,             \
}

//
// Attribute entries for 32-bit instructions like LBGP
//
#define ATTR32_LBGP(_NAME, _GENERIC, _ARCH, _OPCODE, _PATTERN) [IT32_##_NAME] = { \
    opcode   : _OPCODE,             \
    pattern  : _PATTERN,            \
    format   : FMT_R1_OFF,          \
    type     : AN_IT_##_GENERIC,    \
    arch     : _ARCH,               \
    r1       : RS_X_11_7,           \
    r2       : RS_GP,               \
    cs1      : CS_LBGP_IMM,         \
    unsExt   : USX_13,              \
    memBits  : MBS_B,               \
}

//
// Attribute entries for 32-bit instructions like LHGP
//
#define ATTR32_LHGP(_NAME, _GENERIC, _ARCH, _OPCODE, _PATTERN) [IT32_##_NAME] = { \
    opcode   : _OPCODE,             \
    pattern  : _PATTERN,            \
    format   : FMT_R1_OFF,          \
    type     : AN_IT_##_GENERIC,    \
    arch     : _ARCH,               \
    r1       : RS_X_11_7,           \
    r2       : RS_GP,               \
    cs1      : CS_LHGP_IMM,         \
    unsExt   : USX_14,              \
    memBits  : MBS_13_12,           \
}

//
// Attribute entries for 32-bit instructions like LWGP
//
#define ATTR32_LWGP(_NAME, _GENERIC, _ARCH, _OPCODE, _PATTERN) [IT32_##_NAME] = { \
    opcode   : _OPCODE,             \
    pattern  : _PATTERN,            \
    format   : FMT_R1_OFF,          \
    type     : AN_IT_##_GENERIC,    \
    arch     : _ARCH,               \
    r1       : RS_X_11_7,           \
    r2       : RS_GP,               \
    cs1      : CS_LWGP_IMM,         \
    unsExt   : USX_14,              \
    memBits  : MBS_13_12,           \
}

//
// Attribute entries for 32-bit instructions like LDGP
//
#define ATTR32_LDGP(_NAME, _GENERIC, _ARCH, _OPCODE, _PATTERN) [IT32_##_NAME] = { \
    opcode   : _OPCODE,             \
    pattern  : _PATTERN,            \
    format   : FMT_R1_OFF,          \
    type     : AN_IT_##_GENERIC,    \
    arch     : _ARCH,               \
    r1       : RS_X_11_7,           \
    r2       : RS_GP,               \
    cs1      : CS_LDGP_IMM,         \
    unsExt   : USX_14,              \
    memBits  : MBS_13_12,           \
}

//
// Attribute entries for 32-bit instructions like SBGP
//
#define ATTR32_SBGP(_NAME, _GENERIC, _ARCH, _OPCODE, _PATTERN) [IT32_##_NAME] = { \
    opcode   : _OPCODE,             \
    pattern  : _PATTERN,            \
    format   : FMT_R1_OFF,          \
    type     : AN_IT_##_GENERIC,    \
    arch     : _ARCH,               \
    r1       : RS_X_24_20,          \
    r2       : RS_GP,               \
    cs1      : CS_SBGP_IMM,         \
    memBits  : MBS_B,               \
}

//
// Attribute entries for 32-bit instructions like SHGP
//
#define ATTR32_SHGP(_NAME, _GENERIC, _ARCH, _OPCODE, _PATTERN) [IT32_##_NAME] = { \
    opcode   : _OPCODE,             \
    pattern  : _PATTERN,            \
    format   : FMT_R1_OFF,          \
    type     : AN_IT_##_GENERIC,    \
    arch     : _ARCH,               \
    r1       : RS_X_24_20,          \
    r2       : RS_GP,               \
    cs1      : CS_SHGP_IMM,         \
    memBits  : MBS_H,               \
}

//
// Attribute entries for 32-bit instructions like SWGP
//
#define ATTR32_SWGP(_NAME, _GENERIC, _ARCH, _OPCODE, _PATTERN) [IT32_##_NAME] = { \
    opcode   : _OPCODE,             \
    pattern  : _PATTERN,            \
    format   : FMT_R1_OFF,          \
    type     : AN_IT_##_GENERIC,    \
    arch     : _ARCH,               \
    r1       : RS_X_24_20,          \
    r2       : RS_GP,               \
    cs1      : CS_SWGP_IMM,         \
    memBits  : MBS_W,               \
}

//
// Attribute entries for 32-bit instructions like SDGP
//
#define ATTR32_SDGP(_NAME, _GENERIC, _ARCH, _OPCODE, _PATTERN) [IT32_##_NAME] = { \
    opcode   : _OPCODE,             \
    pattern  : _PATTERN,            \
    format   : FMT_R1_OFF,          \
    type     : AN_IT_##_GENERIC,    \
    arch     : _ARCH,               \
    r1       : RS_X_24_20,          \
    r2       : RS_GP,               \
    cs1      : CS_SDGP_IMM,         \
    memBits  : MBS_D,               \
}

//
// Attribute entries for 32-bit instructions like LEA.H
//
#define ATTR32_FFB(_NAME, _GENERIC, _ARCH, _OPCODE, _PATTERN) [IT32_##_NAME] = { \
    opcode   : _OPCODE,             \
    pattern  : _PATTERN,            \
    format   : FMT_R1_R2_R3,        \
    type     : AN_IT_##_GENERIC,    \
    arch     : _ARCH,               \
    r1       : RS_X_11_7,           \
    r2       : RS_X_19_15,          \
    r3       : RS_X_24_20,          \
}

//
// Attribute entries for 32-bit instructions like FLHW
//
#define ATTR32_FLHW(_NAME, _GENERIC, _ARCH, _OPCODE, _PATTERN) [IT32_##_NAME] = { \
    opcode   : _OPCODE,             \
    pattern  : _PATTERN,            \
    format   : FMT_R1_OFF_R2,       \
    type     : AN_IT_##_GENERIC,    \
    arch     : _ARCH,               \
    r1       : RS_F_11_7,           \
    r2       : RS_X_19_15,          \
    cs1      : CS_S_31_20,          \
    memBits  : MBS_H,               \
    cvtF32   : True,                \
}

//
// Attribute entries for 32-bit instructions like FSHW
//
#define ATTR32_FSHW(_NAME, _GENERIC, _ARCH, _OPCODE, _PATTERN) [IT32_##_NAME] = { \
    opcode   : _OPCODE,             \
    pattern  : _PATTERN,            \
    format   : FMT_R1_OFF_R2,       \
    type     : AN_IT_##_GENERIC,    \
    arch     : _ARCH,               \
    r1       : RS_F_24_20,          \
    r2       : RS_X_19_15,          \
    cs1      : CS_S_31_25_11_7,     \
    memBits  : MBS_H,               \
    cvtF32   : True,                \
}

//
// Attribute entries for 32-bit instructions like LAST
//
#define ATTR32_LAST(_NAME, _GENERIC, _OPCODE) [IT32_##_NAME] = { \
    opcode   : _OPCODE,             \
    format   : FMT_NONE,            \
    type     : AN_IT_##_GENERIC     \
}

//
// Attribute entries for 32-bit instructions like VLN.V
//
#define ATTR32_VLNV(_NAME, _GENERIC, _ARCH, _OPCODE, _PATTERN) [IT32_##_NAME] = { \
    opcode   : _OPCODE,             \
    pattern  : _PATTERN,            \
    format   : FMT_R1_MEM2_RM,      \
    type     : AN_IT_##_GENERIC,    \
    arch     : _ARCH,               \
    r1       : RS_V_11_7,           \
    r2       : RS_X_19_15,          \
    mask     : RS_V_M_25,           \
    unsExt   : USX_20,              \
    unsExtQ  : 1,                   \
    elemBits : EBS_21               \
}

//
// Attribute entries for 32-bit instructions like FCVT.S.BF16
//
#define ATTR32_FCVT(_NAME, _ARCH, _OPCODE, _PATTERN) [IT32_##_NAME] = { \
    opcode   : _OPCODE,             \
    pattern  : _PATTERN,            \
    format   : FMT_R1_R2,           \
    type     : AN_IT_##_NAME,       \
    arch     : _ARCH,               \
    r1       : RS_F_11_7,           \
    r2       : RS_F_24_20           \
}

//
// Attribute entries for 32-bit instructions like VFWCVT.S.BF16
//
#define ATTR32_VFCVT(_NAME, _ARCH, _OPCODE, _PATTERN) [IT32_##_NAME] = { \
    opcode   : _OPCODE,             \
    pattern  : _PATTERN,            \
    format   : FMT_R1_R2,           \
    type     : AN_IT_##_NAME,       \
    arch     : _ARCH,               \
    r1       : RS_V_11_7,           \
    r2       : RS_V_24_20           \
}

//
// Attribute entries for 32-bit instructions like VFPMADT.VF
//
#define ATTR32_VFPMADT_VF(_NAME, _ARCH, _OPCODE, _PATTERN) [IT32_##_NAME] = { \
    opcode   : _OPCODE,             \
    pattern  : _PATTERN,            \
    format   : FMT_R1_R2_R3_RM,     \
    type     : AN_IT_##_NAME,       \
    arch     : _ARCH,               \
    r1       : RS_V_11_7,           \
    r2       : RS_F_19_15,          \
    r3       : RS_V_24_20,          \
    mask     : RS_V_M_25,           \
}

//
// Attribute entries for 32-bit base model instructions
//
#define ATTR32_BASE(_NAME, _GENERIC, _ARCH, _OPCODE, _PATTERN) [IT32_##_NAME] = { \
    opcode   : _OPCODE,             \
    pattern  : _PATTERN,            \
    type     : AN_IT_##_GENERIC,    \
    arch     : _ARCH                \
}


////////////////////////////////////////////////////////////////////////////////
// DATA FOR 16-BIT INSTRUCTIONS
////////////////////////////////////////////////////////////////////////////////

//
// Attribute entries for 16-bit instructions like EXEC_IT
//
#define ATTR16_EXEC_IT(_NAME, _GENERIC, _ARCH, _OPCODE, _PATTERN) [IT16_##_NAME] = { \
    opcode   : _OPCODE,             \
    pattern  : _PATTERN,            \
    format   : FMT_UIMM,            \
    type     : AN_IT_##_GENERIC,    \
    arch     : _ARCH,               \
    cs1      : CU_EXEC_IT_IMM,      \
}

//
// Attribute entries for 16-bit instructions like LAST
//
#define ATTR16_LAST(_NAME, _GENERIC, _OPCODE) [IT16_##_NAME] = { \
    opcode   : _OPCODE,             \
    format   : FMT_NONE,            \
    type     : AN_IT_##_GENERIC     \
}

//
// Attribute entries for 16-bit base model instructions
//
#define ATTR16_BASE(_NAME, _GENERIC, _ARCH, _OPCODE, _PATTERN) [IT16_##_NAME] = { \
    opcode   : _OPCODE,             \
    pattern  : _PATTERN,            \
    type     : AN_IT_##_GENERIC,    \
    arch     : _ARCH                \
}


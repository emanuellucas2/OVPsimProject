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

#include <stdio.h>
#include "vmi/vmiCxt.h"
#include "v850Decode.h"
#include "v850Instructions.h"
#include "v850Functions.h"
#include "v850SPR.h"

//
// Generate the disassembler alias lookup table for BCCODE
//
const char *BCCODE[16] = {
    [0]  = "v      ",
    [1]  = "l      ",
    [2]  = "e      ",
    [3]  = "nh     ",
    [4]  = "n      ",
    [5]  = "r      ",
    [6]  = "lt     ",
    [7]  = "le     ",
    [8]  = "nv     ",
    [9]  = "nl     ",
    [10] = "ne     ",
    [11] = "h      ",
    [12] = "p      ",
    [13] = "sa     ",
    [14] = "ge     ",
    [15] = "gt     ",
};

//
// Generate the disassembler alias lookup table for FCCODE
//
const char *FCCODE[16] = {
    [0]  = "v",
    [1]  = "c/l",
    [2]  = "z",
    [3]  = "nh",
    [4]  = "s/n",
    [5]  = "t",
    [6]  = "lt",
    [7]  = "le",
    [8]  = "nv",
    [9]  = "nc/nl",
    [10] = "nz",
    [11] = "h",
    [12] = "ns/p",
    [13] = "sa",
    [14] = "ge",
    [15] = "gt",
};

//
// Generate the disassembler alias lookup table for FPCMPCODE
//
const char *FPCMPCODE[16] = {
    [0]  = "f/t",
    [1]  = "un/or",
    [2]  = "eq/neq",
    [3]  = "ueq/ogl",
    [4]  = "olt/uge",
    [5]  = "ult/oge",
    [6]  = "ole/ugt",
    [7]  = "ule/ogt",
    [8]  = "sf/st",
    [9]  = "ngle/gle",
    [10] = "seq/sne",
    [11] = "ngl/gl",
    [12] = "lt/nlt",
    [13] = "nge/ge",
    [14] = "le/nle",
    [15] = "ngt/gt",
};

//
// Generate the disassembler alias lookup table for GPR
//
const char *GPR[32] = {
    [3]  = "sp",
    [4]  = "gp",
    [30] = "ep",
    [31] = "lp",
};

//
// Generate the disassembler statemachine definitions
//
#define EMITBIT      "\200"
#define EMITBIT_CASE '\200'
#define EMITCCCC      "\201"
#define EMITCCCC_CASE '\201'
#define EMITCOND      "\202"
#define EMITCOND_CASE '\202'
#define EMITFCOND      "\203"
#define EMITFCOND_CASE '\203'
#define EMITFFF      "\204"
#define EMITFFF_CASE '\204'
#define EMITL12      "\205"
#define EMITL12_CASE '\205'
#define EMITOP      "\206"
#define EMITOP_CASE '\206'
#define EMITOP0      "\207"
#define EMITOP0_CASE '\207'
#define EMITR1      "\210"
#define EMITR1_CASE '\210'
#define EMITR2      "\211"
#define EMITR2_CASE '\211'
#define EMITR3      "\212"
#define EMITR3_CASE '\212'
#define EMITR4      "\213"
#define EMITR4_CASE '\213'
#define EMITSD      "\214"
#define EMITSD_CASE '\214'
#define EMITSDR      "\215"
#define EMITSDR_CASE '\215'
#define EMITSI      "\216"
#define EMITSI_CASE '\216'
#define EMITSR1      "\217"
#define EMITSR1_CASE '\217'
#define EMITSR2      "\220"
#define EMITSR2_CASE '\220'
#define EMITSX      "\221"
#define EMITSX_CASE '\221'
#define EMITUD      "\222"
#define EMITUD_CASE '\222'
#define EMITUI      "\223"
#define EMITUI_CASE '\223'
#define EMITUI5      "\224"
#define EMITUI5_CASE '\224'
#define EMITUX      "\225"
#define EMITUX_CASE '\225'
#define EMITSELID      "\226"
#define EMITSELID_CASE '\226'
#define EMITPOS      "\227"
#define EMITPOS_CASE '\227'
#define EMITWID      "\230"
#define EMITWID_CASE '\230'

//
// Generate the instruction formatting table
//
#define FMT_NONE ""
const char *formats[V850_IT_LAST+1] = {
    //
    // Instruction Format F01 Insns
    //
    [V850_IT_ADD_F01]        = EMITOP " " EMITR1 ", " EMITR2,
    [V850_IT_AND_F01]        = EMITOP " " EMITR1 ", " EMITR2,
    [V850_IT_CMP_F01]        = EMITOP " " EMITR1 ", " EMITR2,
    [V850_IT_DIVH_F01]       = EMITOP " " EMITR1 ", " EMITR2,
    [V850_IT_MOV_F01]        = EMITOP " " EMITR1 ", " EMITR2,
    [V850_IT_MULH_F01]       = EMITOP " " EMITR1 ", " EMITR2,
    [V850_IT_NOT_F01]        = EMITOP " " EMITR1 ", " EMITR2,
    [V850_IT_OR_F01]         = EMITOP " " EMITR1 ", " EMITR2,
    [V850_IT_SATADD_F01]     = EMITOP " " EMITR1 ", " EMITR2,
    [V850_IT_SATSUB_F01]     = EMITOP " " EMITR1 ", " EMITR2,
    [V850_IT_SATSUBR_F01]    = EMITOP " " EMITR1 ", " EMITR2,
    [V850_IT_SUB_F01]        = EMITOP " " EMITR1 ", " EMITR2,
    [V850_IT_SUBR_F01]       = EMITOP " " EMITR1 ", " EMITR2,
    [V850_IT_TST_F01]        = EMITOP " " EMITR1 ", " EMITR2,
    [V850_IT_XOR_F01]        = EMITOP " " EMITR1 ", " EMITR2,

    //
    // Instruction Format F01a Insns
    //
    [V850_IT_DBTRAP_F01A]    = EMITOP0,
    [V850_IT_NOP_F01A]       = EMITOP0,
    [V850_IT_RIE_F01A]       = EMITOP0,
    [V850_IT_RMTRAP_F01A]    = EMITOP0,
    [V850_IT_SYNCM_F01A]     = EMITOP0,
    [V850_IT_SYNCP_F01A]     = EMITOP0,
    [V850_IT_SYNCE_F01A]     = EMITOP0,
    [V850_IT_SYNCI_F01A]     = EMITOP0,

    //
    // Instruction Format F01b Insns
    //
    [V850_IT_JMP_F01B]       = EMITOP " [" EMITR1 "]",

    //
    // Instruction Format F01c Insns
    //
    [V850_IT_SXB_F01C]       = EMITOP " " EMITR1,
    [V850_IT_SXH_F01C]       = EMITOP " " EMITR1,
    [V850_IT_ZXB_F01C]       = EMITOP " " EMITR1,
    [V850_IT_ZXH_F01C]       = EMITOP " " EMITR1,

    //
    // Instruction Format F01d Insns
    //
    [V850_IT_SWITCH_F01D]    = EMITOP " " EMITR1,

    //
    // Instruction Format F01e Insns
    //
    [V850_IT_FETRAP_F01E]    = EMITOP " " EMITUI,

    //
    // Instruction Format F02b Insns
    //
    [V850_IT_CALLT_F02B]     = EMITOP " " EMITUI,

    //
    // Instruction Format F02s Insns
    //
    [V850_IT_ADD_F02S]       = EMITOP " " EMITSI ", " EMITR2,
    [V850_IT_CMP_F02S]       = EMITOP " " EMITSI ", " EMITR2,
    [V850_IT_MOV_F02S]       = EMITOP " " EMITSI ", " EMITR2,
    [V850_IT_MULH_F02S]      = EMITOP " " EMITSI ", " EMITR2,
    [V850_IT_SATADD_F02S]    = EMITOP " " EMITSI ", " EMITR2,

    //
    // Instruction Format F02u Insns
    //
    [V850_IT_SAR_F02U]       = EMITOP " " EMITUI ", " EMITR2,
    [V850_IT_SHL_F02U]       = EMITOP " " EMITUI ", " EMITR2,
    [V850_IT_SHR_F02U]       = EMITOP " " EMITUI ", " EMITR2,

    //
    // Instruction Format F03 Insns
    //
    [V850_IT_BCOND_F03]      = EMITOP0 EMITCOND " " EMITSDR,

    //
    // Instruction Format F04db Insns
    //
    [V850_IT_SLD_BU_F04DB]   = EMITOP " " EMITUD "[ep], " EMITR2,

    //
    // Instruction Format F04dh Insns
    //
    [V850_IT_SLD_HU_F04DH]   = EMITOP " " EMITUD "[ep], " EMITR2,

    //
    // Instruction Format F04la Insns
    //
    [V850_IT_SLD_B_F04LA]    = EMITOP " " EMITUD "[ep], " EMITR2,

    //
    // Instruction Format F04lb Insns
    //
    [V850_IT_SLD_H_F04LB]    = EMITOP " " EMITUD "[ep], " EMITR2,

    //
    // Instruction Format F04lc Insns
    //
    [V850_IT_SLD_W_F04LC]    = EMITOP " " EMITUD "[ep], " EMITR2,

    //
    // Instruction Format F04sa Insns
    //
    [V850_IT_SST_B_F04SA]    = EMITOP " " EMITR2 ", " EMITUD "[ep]",

    //
    // Instruction Format F04sb Insns
    //
    [V850_IT_SST_H_F04SB]    = EMITOP " " EMITR2 ", " EMITUD "[ep]",

    //
    // Instruction Format F04sc Insns
    //
    [V850_IT_SST_W_F04SC]    = EMITOP " " EMITR2 ", " EMITUD "[ep]",

    //
    // Instruction Format F05a Insns
    //
    [V850_IT_JARL_F05A]      = EMITOP " " EMITSDR ", " EMITR2,

    //
    // Instruction Format F05b Insns
    //
    [V850_IT_JR_F05B]        = EMITOP " " EMITSDR,

    //
    // Instruction Format F06s Insns
    //
    [V850_IT_ADDI_F06S]      = EMITOP " " EMITSI ", " EMITR1 ", " EMITR2,
    [V850_IT_MOVEA_F06S]     = EMITOP " " EMITSI ", " EMITR1 ", " EMITR2,
    [V850_IT_MOVHI_F06S]     = EMITOP " " EMITSI ", " EMITR1 ", " EMITR2,
    [V850_IT_MULHI_F06S]     = EMITOP " " EMITSI ", " EMITR1 ", " EMITR2,
    [V850_IT_SATSUBI_F06S]   = EMITOP " " EMITSI ", " EMITR1 ", " EMITR2,

    //
    // Instruction Format F06sa Insns
    //
    [V850_IT_JARL_F06SA]     = EMITOP " " EMITSDR ", " EMITR1,

    //
    // Instruction Format F06sb Insns
    //
    [V850_IT_JMP_F06SB]      = EMITOP " " EMITSD "[" EMITR1 "]",

    //
    // Instruction Format F06sc Insns
    //
    [V850_IT_JR_F06SC]       = EMITOP " " EMITSDR,

    //
    // Instruction Format F06u Insns
    //
    [V850_IT_ANDI_F06U]      = EMITOP " " EMITUI ", " EMITR1 ", " EMITR2,
    [V850_IT_ORI_F06U]       = EMITOP " " EMITUI ", " EMITR1 ", " EMITR2,
    [V850_IT_XORI_F06U]      = EMITOP " " EMITUI ", " EMITR1 ", " EMITR2,

    //
    // Instruction Format F06ua Insns
    //
    [V850_IT_MOV_F06UA]      = EMITOP " " EMITUX ", " EMITR1,

    //
    // Instruction Format F06x Insns
    //
    [V850_IT_RIE_F06X]       = EMITOP " " "0, 0",

    //
    // Instruction Format F07 Insns
    //
    [V850_IT_BCOND_F07CC]    = EMITOP0 EMITCOND " " EMITSDR,

    //
    // Instruction Format F07c Insns
    //
    [V850_IT_LD_BU_F07C]     = EMITOP " " EMITSD "[" EMITR1 "], " EMITR2,

    //
    // Instruction Format F07la Insns
    //
    [V850_IT_LD_B_F07LA]     = EMITOP " " EMITSD "[" EMITR1 "], " EMITR2,

    //
    // Instruction Format F07lb Insns
    //
    [V850_IT_LD_H_F07LB]     = EMITOP " " EMITSD "[" EMITR1 "], " EMITR2,
    [V850_IT_LD_HU_F07LB]    = EMITOP " " EMITSD "[" EMITR1 "], " EMITR2,
    [V850_IT_LD_W_F07LB]     = EMITOP " " EMITSD "[" EMITR1 "], " EMITR2,

    //
    // Instruction Format F07sa Insns
    //
    [V850_IT_ST_B_F07SA]     = EMITOP " " EMITR2 ", " EMITSD "[" EMITR1 "]",

    //
    // Instruction Format F07sb Insns
    //
    [V850_IT_ST_H_F07SB]     = EMITOP " " EMITR2 ", " EMITSD "[" EMITR1 "]",
    [V850_IT_ST_W_F07SB]     = EMITOP " " EMITR2 ", " EMITSD "[" EMITR1 "]",

    //
    // Instruction Format F08 Insns
    //
    [V850_IT_CLR1_F08]       = EMITOP " " EMITBIT ", " EMITSD "[" EMITR1 "]",
    [V850_IT_NOT1_F08]       = EMITOP " " EMITBIT ", " EMITSD "[" EMITR1 "]",
    [V850_IT_SET1_F08]       = EMITOP " " EMITBIT ", " EMITSD "[" EMITR1 "]",
    [V850_IT_TST1_F08]       = EMITOP " " EMITBIT ", " EMITSD "[" EMITR1 "]",

    //
    // Instruction Format F09 Insns
    //
    [V850_IT_SASF_F09]       = EMITOP " " EMITCCCC ", " EMITR2,
    [V850_IT_SETF_F09]       = EMITOP " " EMITCCCC ", " EMITR2,

    //
    // Instruction Format F09rr Insns
    //
    [V850_IT_SAR_F09RR]      = EMITOP " " EMITR1  ", " EMITR2,
    [V850_IT_SHL_F09RR]      = EMITOP " " EMITR1  ", " EMITR2,
    [V850_IT_SHR_F09RR]      = EMITOP " " EMITR1  ", " EMITR2,

    //
    // Instruction Format F09rr2 Insns
    //
    [V850_IT_SCH0L_F09RR2]   = EMITOP " " EMITR2  ", " EMITR3,
    [V850_IT_SCH0R_F09RR2]   = EMITOP " " EMITR2  ", " EMITR3,
    [V850_IT_SCH1L_F09RR2]   = EMITOP " " EMITR2  ", " EMITR3,
    [V850_IT_SCH1R_F09RR2]   = EMITOP " " EMITR2  ", " EMITR3,

    //
    // Instruction Format F09rs1 Insns
    //
    [V850_IT_LDSR_F09RS1_0]  = EMITOP " " EMITR1  ", " EMITSR2,
    [V850_IT_LDSR_F09RS1]    = EMITOP " " EMITR1  ", " EMITSR2 ", " EMITSELID,

    //
    // Instruction Format F09rs2 Insns
    //
    [V850_IT_CLR1_F09RS2]    = EMITOP " " EMITR2  ", [" EMITR1 "]",
    [V850_IT_NOT1_F09RS2]    = EMITOP " " EMITR2  ", [" EMITR1 "]",
    [V850_IT_SET1_F09RS2]    = EMITOP " " EMITR2  ", [" EMITR1 "]",
    [V850_IT_TST1_F09RS2]    = EMITOP " " EMITR2  ", [" EMITR1 "]",

    //
    // Instruction Format F09sr Insns
    //
    [V850_IT_STSR_F09SR_0]   = EMITOP " " EMITSR1 ", " EMITR2,
    [V850_IT_STSR_F09SR]     = EMITOP " " EMITSR1 ", " EMITR2 ", " EMITSELID,

    //
    // Instruction Format F10a Insns
    //
    [V850_IT_CTRET_F10A]     = EMITOP0,
    [V850_IT_DBRET_F10A]     = EMITOP0,
    [V850_IT_DI_F10A]        = EMITOP0,
    [V850_IT_EI_F10A]        = EMITOP0,
    [V850_IT_EIRET_F10A]     = EMITOP0,
    [V850_IT_FERET_F10A]     = EMITOP0,
    [V850_IT_HALT_F10A]      = EMITOP0,
    [V850_IT_RETI_F10A]      = EMITOP0,

    //
    // Instruction Format F10b Insns
    //
    [V850_IT_TRAP_F10B]      = EMITOP " " EMITUI,

    //
    // Instruction Format F11 Insns
    //
    [V850_IT_DIV_F11]        = EMITOP " " EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_DIVH_F11]       = EMITOP " " EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_DIVHU_F11]      = EMITOP " " EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_DIVQ_F11]       = EMITOP " " EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_DIVQU_F11]      = EMITOP " " EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_DIVU_F11]       = EMITOP " " EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_MUL_F11]        = EMITOP " " EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_MULU_F11]       = EMITOP " " EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_SAR_F11]        = EMITOP " " EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_SATADD_F11]     = EMITOP " " EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_SATSUB_F11]     = EMITOP " " EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_SHL_F11]        = EMITOP " " EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_SHR_F11]        = EMITOP " " EMITR1 ", " EMITR2 ", " EMITR3,

    //
    // Instruction Format F11a Insns
    //
    [V850_IT_MAC_F11A]       = EMITOP " " EMITR1 ", " EMITR2 ", " EMITR3 ", " EMITR4,
    [V850_IT_MACU_F11A]      = EMITOP " " EMITR1 ", " EMITR2 ", " EMITR3 ", " EMITR4,

    //
    // Instruction Format F11b Insns
    //
    [V850_IT_ADF_F11B]       = EMITOP " " EMITCCCC ", " EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_CMOV_F11B]      = EMITOP " " EMITCCCC ", " EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_SBF_F11B]       = EMITOP " " EMITCCCC ", " EMITR1 ", " EMITR2 ", " EMITR3,

    //
    // Instruction Format F11c Insns
    //
    [V850_IT_CAXI_F11C]      = EMITOP " [" EMITR1 "], " EMITR2 ", " EMITR3,

    //
    // Instruction Format F11d Insns
    //
    [V850_IT_JARL_F11D]      = EMITOP " [" EMITR1 "], " EMITR3,

    //
    // Instruction Format F12a Insns
    //
    [V850_IT_CMOV_F12A]      = EMITOP " " EMITCCCC ", " EMITSI ", " EMITR2 ", " EMITR3,

    //
    // Instruction Format F12b Insns
    //
    [V850_IT_BSH_F12B]       = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_BSW_F12B]       = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_HSH_F12B]       = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_HSW_F12B]       = EMITOP " " EMITR2 ", " EMITR3,

    //
    // Instruction Format F12s Insns
    //
    [V850_IT_MUL_F12S]       = EMITOP " " EMITSI ", " EMITR2 ", " EMITR3,

    //
    // Instruction Format F12u Insns
    //
    [V850_IT_MULU_F12U]      = EMITOP " " EMITUI ", " EMITR2 ", " EMITR3,

    //
    // Instruction Format F13il1 Insns
    //
    [V850_IT_DISPOSE_F13IL1] = EMITOP " " EMITUI5  ", " EMITL12 ", " EMITR1,

    //
    // Instruction Format F13il2 Insns
    //
    [V850_IT_DISPOSE_F13IL2] = EMITOP " " EMITUI5  ", " EMITL12 ", " EMITR1,

    //
    // Instruction Format F13li Insns
    //
    [V850_IT_PREPARE_F13LI]  = EMITOP " " EMITL12 ", " EMITUI5,

    //
    // Instruction Format F13li00 Insns
    //
    [V850_IT_PREPARE_F13LI00] = EMITOP " " EMITL12 ", " EMITUI5,

    //
    // Instruction Format F13li01 Insns
    //
    [V850_IT_PREPARE_F13LI01] = EMITOP " " EMITL12 ", " EMITUI5 ", " EMITSX,

    //
    // Instruction Format F13li10 Insns
    //
    [V850_IT_PREPARE_F13LI10] = EMITOP " " EMITL12 ", " EMITUI5 ", " EMITSX,

    //
    // Instruction Format F13li11 Insns
    //
    [V850_IT_PREPARE_F13LI11] = EMITOP " " EMITL12 ", " EMITUI5 ", " EMITSX,

    //
    // Instruction Format FI Insns
    //
    [V850_IT_ADDF_S_FI]      = EMITOP " " EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_DIVF_S_FI]      = EMITOP " " EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_MAXF_S_FI]      = EMITOP " " EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_MINF_S_FI]      = EMITOP " " EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_MULF_S_FI]      = EMITOP " " EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_SUBF_S_FI]      = EMITOP " " EMITR1 ", " EMITR2 ", " EMITR3,

    //
    // Instruction Format FID Insns
    //
    [V850_IT_ADDF_D_FID]     = EMITOP " "  EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_DIVF_D_FID]     = EMITOP " "  EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_MAXF_D_FID]     = EMITOP " "  EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_MINF_D_FID]     = EMITOP " "  EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_MULF_D_FID]     = EMITOP " "  EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_SUBF_D_FID]     = EMITOP " "  EMITR1 ", " EMITR2 ", " EMITR3,

    //
    // Instruction Format FIDSr2r3 Insns
    //
    [V850_IT_CEILF_DW_FIDSR2R3]  = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CVTF_DS_FIDSR2R3]   = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CVTF_DUW_FIDSR2R3]  = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CVTF_DW_FIDSR2R3]   = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CVTF_LS_FIDSR2R3]   = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CVTF_ULS_FIDSR2R3]  = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_FLOORF_DW_FIDSR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_TRNCF_DW_FIDSR2R3]  = EMITOP " " EMITR2 ", " EMITR3,

    //
    // Instruction Format FIDcond Insns
    //
    [V850_IT_CMPF_D_FIDCOND] = EMITOP " " EMITFCOND ", " EMITR2 ", " EMITR1 ", " EMITFFF,

    //
    // Instruction Format FIDfff Insns
    //
    [V850_IT_CMOVF_D_FIDFFF] = EMITOP " " EMITFFF ", " EMITR1 ", " EMITR2 ", " EMITR3,

    //
    // Instruction Format FIDr2r3 Insns
    //
    [V850_IT_ABSF_D_FIDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CEILF_DL_FIDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CEILF_DUL_FIDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CEILF_DUW_FIDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CVTF_DL_FIDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CVTF_DUL_FIDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CVTF_ULD_FIDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_FLOORF_DL_FIDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_FLOORF_DUL_FIDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_FLOORF_DUW_FIDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_NEGF_D_FIDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_RECIPF_D_FIDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_RSQRTF_D_FIDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_SQRTF_D_FIDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_TRNCF_DL_FIDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_TRNCF_DUL_FIDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_TRNCF_DUW_FIDR2R3] = EMITOP " " EMITR2 ", " EMITR3,

    //
    // Instruction Format FII Insns
    //
    [V850_IT_ABSF_S_FII]     = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CVT_SW_FII]     = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CVT_WS_FII]     = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_NEGF_S_FII]     = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_TRNC_SW_FII]    = EMITOP " " EMITR2 ", " EMITR3,

    //
    // Instruction Format FIS Insns
    //
    [V850_IT_ADDF_S_FIS]     = EMITOP " "  EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_DIVF_S_FIS]     = EMITOP " "  EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_MAXF_S_FIS]     = EMITOP " "  EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_MINF_S_FIS]     = EMITOP " "  EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_MULF_S_FIS]     = EMITOP " "  EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_SUBF_S_FIS]     = EMITOP " "  EMITR1 ", " EMITR2 ", " EMITR3,

    //
    // Instruction Format FISDr2r3 Insns
    //
    [V850_IT_CEILF_SL_FISDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CEILF_SUL_FISDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CVTF_SD_FISDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CVTF_SL_FISDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CVTF_SUL_FISDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CVTF_UWD_FISDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CVTF_WD_FISDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_FLOORF_SL_FISDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_FLOORF_SUL_FISDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_TRNCF_SL_FISDR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_TRNCF_SUL_FISDR2R3] = EMITOP " " EMITR2 ", " EMITR3,

    //
    // Instruction Format FISa Insns
    //
    [V850_IT_MADDF_S_FISA]   = EMITOP " "  EMITR1 ", " EMITR2 ", " EMITR3 ", " EMITR4,
    [V850_IT_MSUBF_S_FISA]   = EMITOP " "  EMITR1 ", " EMITR2 ", " EMITR3 ", " EMITR4,
    [V850_IT_NMADDF_S_FISA]  = EMITOP " "  EMITR1 ", " EMITR2 ", " EMITR3 ", " EMITR4,
    [V850_IT_NMSUBF_S_FISA]  = EMITOP " "  EMITR1 ", " EMITR2 ", " EMITR3 ", " EMITR4,

    //
    // Instruction Format FIScond Insns
    //
    [V850_IT_CMPF_S_FISCOND] = EMITOP " " EMITFCOND ", " EMITR2 ", " EMITR1 ", " EMITFFF,

    //
    // Instruction Format FISfff Insns
    //
    [V850_IT_CMOVF_S_FISFFF] = EMITOP " " EMITFFF ", " EMITR1 ", " EMITR2 ", " EMITR3,

    //
    // Instruction Format FISr2r3 Insns
    //
    [V850_IT_ABSF_S_FISR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CEILF_SUW_FISR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CEILF_SW_FISR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CVTF_LD_FISR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CVTF_SUW_FISR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CVTF_SW_FISR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CVTF_UWS_FISR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CVTF_WS_FISR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_FLOORF_SUW_FISR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_FLOORF_SW_FISR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_NEGF_S_FISR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_RECIPF_S_FISR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_RSQRTF_S_FISR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_SQRTF_S_FISR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_TRNCF_SUW_FISR2R3] = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_TRNCF_SW_FISR2R3] = EMITOP " " EMITR2 ", " EMITR3,

    //
    // Instruction Format FIV Insns
    //
    [V850_IT_TRFF_FIV]       = EMITOP,

    //
    // Instruction Format FIVr2a Insns
    //
    [V850_IT_LDFF_FIVR2A]    = EMITOP " " EMITR2 ", efg",

    //
    // Instruction Format FIVr2b Insns
    //
    [V850_IT_LDFC_FIVR2B]    = EMITOP " " EMITR2 ", ect",

    //
    // Instruction Format FIVr3a Insns
    //
    [V850_IT_STFF_FIVR3A]    = EMITOP "efg, " EMITR3,

    //
    // Instruction Format FIVr3b Insns
    //
    [V850_IT_STFC_FIVR3B]    = EMITOP "ect, " EMITR3,

    //
    // Instruction Format FIfff Insns
    //
    [V850_IT_TRFSR_FIFFF]    = EMITOP " " EMITFFF,

    //
    // RH850 instructions
    //
    [V850_IT_LDL_W_F07D]     = EMITOP " [" EMITR1  "], " EMITR3,
    [V850_IT_STC_W_F07D]     = EMITOP " "  EMITR3  ", [" EMITR1  "]",
    [V850_IT_PUSHSP_F11]     = EMITOP " "  EMITR1  "-"   EMITR3,
    [V850_IT_POPSP_F11]      = EMITOP " "  EMITR1  "-"   EMITR3,
    [V850_IT_ROTL_F07RRR]    = EMITOP " "  EMITR1  ", "  EMITR2  ", "  EMITR3,
    [V850_IT_ROTL_F07IRR]    = EMITOP " "  EMITUI5 ", "  EMITR2  ", "  EMITR3,
    [V850_IT_BINS_F09RPWR_0] = EMITOP " "  EMITR1  ", "  EMITPOS ", "  EMITWID ", " EMITR2,
    [V850_IT_BINS_F09RPWR_1] = EMITOP " "  EMITR1  ", "  EMITPOS ", "  EMITWID ", " EMITR2,
    [V850_IT_BINS_F09RPWR_2] = EMITOP " "  EMITR1  ", "  EMITPOS ", "  EMITWID ", " EMITR2,
    [V850_IT_CLL_F10]        = EMITOP,
    [V850_IT_SNOOZE_F10]     = EMITOP,
    [V850_IT_LOOP_F07RI]     = EMITOP " "  EMITR1  ", "  EMITSDR,
    [V850_IT_LD_DW_F14]      = EMITOP " "  EMITSD  "["   EMITR1  "], " EMITR3,
    [V850_IT_ST_DW_F14]      = EMITOP " "  EMITR3  ", "  EMITSD  "["   EMITR1  "]",
    [V850_IT_LD_BU_F14]      = EMITOP " "  EMITSD  "["   EMITR1  "], " EMITR3,
    [V850_IT_LD_B_F14]       = EMITOP " "  EMITSD  "["   EMITR1  "], " EMITR3,
    [V850_IT_ST_B_F14]       = EMITOP " "  EMITR3  ", "  EMITSD  "["   EMITR1  "]",
    [V850_IT_LD_HU_F14]      = EMITOP " "  EMITSD  "["   EMITR1  "], " EMITR3,
    [V850_IT_LD_H_F14]       = EMITOP " "  EMITSD  "["   EMITR1  "], " EMITR3,
    [V850_IT_ST_H_F14]       = EMITOP " "  EMITR3  ", "  EMITSD  "["   EMITR1  "]",
    [V850_IT_LD_W_F14]       = EMITOP " "  EMITSD  "["   EMITR1  "], " EMITR3,
    [V850_IT_ST_W_F14]       = EMITOP " "  EMITR3  ", "  EMITSD  "["   EMITR1  "]",
    [V850_IT_CACHE_F10]      = EMITOP,
    [V850_IT_CACHE_CHBII]    = EMITOP ", [" EMITR1  "]",
    [V850_IT_CACHE_CIBII]    = EMITOP ", [" EMITR1  "]",
    [V850_IT_CACHE_CFALI]    = EMITOP ", [" EMITR1  "]",
    [V850_IT_CACHE_CISTI]    = EMITOP ", [" EMITR1  "]",
    [V850_IT_CACHE_CILDI]    = EMITOP ", [" EMITR1  "]",
    [V850_IT_PREF_F10]       = EMITOP,
    [V850_IT_PREFI_F10]      = EMITOP ", [" EMITR1  "]",
    [V850_IT_CVTF_HS_FI]     = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_CVTF_SH_FI]     = EMITOP " " EMITR2 ", " EMITR3,
    [V850_IT_FMAF_S_FI]      = EMITOP " " EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_FMSF_S_FI]      = EMITOP " " EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_FNMAF_S_FI]     = EMITOP " " EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_FNMSF_S_FI]     = EMITOP " " EMITR1 ", " EMITR2 ", " EMITR3,
    [V850_IT_SYSCALL_F10C]   = EMITOP " " EMITUI,

    [V850_IT_LAST] = "UNDEFINED"
};

//
// generate builtin disassembler writer functions
//
static void putChar(char **result, char ch) {
    char *tail = *result;
    *tail++ = ch;
    *tail = 0;
    *result = tail;
}

static void putString(char **result, const char *string) {
    char *tail = *result;
    char  ch;
    while((ch=*string++)) {
        *tail++ = ch;
    }
    *tail = 0;
    *result = tail;
}

//
// generate generated disassembler writer functions
//

//
// Function to format the info field #bit#
//
static void EMITBIT_FN(char **result, v850InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%d";
    sprintf(tmp, fmt, info->bit);
    putString(result, tmp);
}
//
// Function to format the info field #cccc#
//
static void EMITCCCC_FN(char **result, v850InstructionInfoP info) {
    char tmp[32];
    const char *fmt = (FCCODE[info->cccc] ? FCCODE[info->cccc] : "%d");
    sprintf(tmp, fmt, info->cccc);
    putString(result, tmp);
}
//
// Function to format the info field #cond#
//
static void EMITCOND_FN(char **result, v850InstructionInfoP info) {
    char tmp[32];
    const char *fmt = (BCCODE[info->cond] ? BCCODE[info->cond] : "%-7s");
    sprintf(tmp, fmt, info->cond);
    putString(result, tmp);
}
//
// Function to format the info field #cond#
//
static void EMITFCOND_FN(char **result, v850InstructionInfoP info) {
    char tmp[32];
    const char *fmt = (FPCMPCODE[info->cond] ? FPCMPCODE[info->cond] : "%-7s");
    sprintf(tmp, fmt, info->cond);
    putString(result, tmp);
}
//
// Function to format the info field #fff#
//
static void EMITFFF_FN(char **result, v850InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%d";
    sprintf(tmp, fmt, info->fff);
    putString(result, tmp);
}
//
// Function to format the info field #list12#
//
static void EMITL12_FN(char **result, v850InstructionInfoP info) {
    char tmp[32];

    Uns32 value;
    Bool  inRange = False;
    Bool  empty   = True;
    Uns8  i;
    // GPR[z]

    putString(result, "{");
    for(i=0; i<=12; i++) {
        value = (info->list12 >> i) & 0x3;

        switch (value) {
        case 0:     // --
            // Do nothing
            inRange = False;
            break;
        case 1:     // -L   Rn
            if (GPR[i+20]) {
                sprintf(tmp, "%s", GPR[i+20]);
            } else {
                sprintf(tmp, "r%02d", i+20);
            }
            putString(result, tmp);
            inRange = False;
            empty   = False;
            break;
        case 2:     // L-   Rn+1
            if (!empty) {
                sprintf(tmp, ", ");
                putString(result, tmp);
            }
            inRange = False;
            break;
        case 3:     // LL   Rn+1, Rn
            if (!inRange) {
                if (GPR[i+20]) {
                    sprintf(tmp, "%s - ", GPR[i+20]);
                } else {
                    sprintf(tmp, "r%02d - ", i+20);
                }
                putString(result, tmp);
                inRange = True;
                empty   = False;
            }
            break;
        }
    }
    putString(result, "}");
}
//
// Function to format the info field #opcode#
//
static void EMITOP_FN(char **result, v850InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%-8s";
    sprintf(tmp, fmt, info->opcode);
    putString(result, tmp);
}
//
// Function to format the info field #opcode#
//
static void EMITOP0_FN(char **result, v850InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%s";
    sprintf(tmp, fmt, info->opcode);
    putString(result, tmp);
}
//
// Function to format the info field #reg1#
//
static void EMITR1_FN(char **result, v850InstructionInfoP info) {
    char tmp[32];
    const char *fmt = (GPR[info->reg1] ? GPR[info->reg1] : "r%d");
    sprintf(tmp, fmt, info->reg1);
    putString(result, tmp);
}
//
// Function to format the info field #reg2#
//
static void EMITR2_FN(char **result, v850InstructionInfoP info) {
    char tmp[32];
    const char *fmt = (GPR[info->reg2] ? GPR[info->reg2] : "r%d");
    sprintf(tmp, fmt, info->reg2);
    putString(result, tmp);
}
//
// Function to format the info field #reg3#
//
static void EMITR3_FN(char **result, v850InstructionInfoP info) {
    char tmp[32];
    const char *fmt = (GPR[info->reg3] ? GPR[info->reg3] : "r%d");
    sprintf(tmp, fmt, info->reg3);
    putString(result, tmp);
}
//
// Function to format the info field #reg4#
//
static void EMITR4_FN(char **result, v850InstructionInfoP info) {
    char tmp[32];
    const char *fmt = (GPR[info->reg4] ? GPR[info->reg4] : "r%d");
    sprintf(tmp, fmt, info->reg4);
    putString(result, tmp);
}
//
// Function to format the info field #sdisp#
//
static void EMITSD_FN(char **result, v850InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%d";
    sprintf(tmp, fmt, info->sdisp);
    putString(result, tmp);
}
//
// Function to format the info field #sdisp# + #thisPC#
//
static void EMITSDR_FN(char **result, v850InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "0x%x";
    sprintf(tmp, fmt, info->targetPC);
    putString(result, tmp);
}

//
// Function to format the info field #simm#
//
static void EMITSI_FN(char **result, v850InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%d";
    sprintf(tmp, fmt, info->simm);
    putString(result, tmp);
}
//
// Function to format the info field #reg1#
//
static void EMITSR1_FN(char **result, v850InstructionInfoP info, v850P v850) {
    char tmp[32];
    v850SystemRegisterP spr = v850GetSystemRegister(v850, info->reg1, info->reg3, False);

    const char *fmt = spr ? spr->name : "sr%d(*undefined*)";
    sprintf(tmp, fmt, info->reg1);
    putString(result, tmp);
}
//
// Function to format the info field #reg2#
//
static void EMITSR2_FN(char **result, v850InstructionInfoP info, v850P v850) {
    char tmp[32];
    v850SystemRegisterP spr = v850GetSystemRegister(v850, info->reg2, info->reg3, False);

    const char *fmt = spr ? spr->name : "sr%d(*undefined*)";
    sprintf(tmp, fmt, info->reg2);
    putString(result, tmp);
}
//
// Function to format the info field #reg2#
//
static void EMITSELID_FN(char **result, v850InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%d";
    sprintf(tmp, fmt, info->reg3);
    putString(result, tmp);
}
//
// Function to format the info field #simm#
//
static void EMITSX_FN(char **result, v850InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "0x%x";
    sprintf(tmp, fmt, info->simm);
    putString(result, tmp);
}
//
// Function to format the info field #udisp#
//
static void EMITUD_FN(char **result, v850InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->udisp);
    putString(result, tmp);
}
//
// Function to format the info field #uimm#
//
static void EMITUI_FN(char **result, v850InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->uimm);
    putString(result, tmp);
}
//
// Function to format the info field #uimm5#
//
static void EMITUI5_FN(char **result, v850InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->uimm5);
    putString(result, tmp);
}
//
// Function to format the info field #uimm#
//
static void EMITUX_FN(char **result, v850InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "0x%x";
    sprintf(tmp, fmt, info->uimm);
    putString(result, tmp);
}

static void EMITPOS_FN(char **result, v850InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%d";
    sprintf(tmp, fmt, info->lsb);
    putString(result, tmp);
}

static void EMITWID_FN(char **result, v850InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    // width = msb - lsb + 1
    Uns32 width = (info->msb - info->lsb + 1);
    sprintf(tmp, fmt, width);
    putString(result, tmp);
}

//
// generate disassembler state machine
//
static void disassembleFormat(
    v850P v850,
    v850InstructionInfoP info,
    char **result,
    const char *format) {

    //
    // Default disassembler output
    //
    char ifmt[64];
    Uns8 ifmtchars = 2 * info->instrsize;
    sprintf(ifmt, "??? instruction(%d bytes)=0x%%0%0dx ", info->instrsize, ifmtchars);
    sprintf(*result, ifmt, info->instruction);

    char ch;
    while((ch=*format++)) {
         switch(ch) {
             case EMITBIT_CASE:
                 EMITBIT_FN(result, info);
                 break;

             case EMITCCCC_CASE:
                 EMITCCCC_FN(result, info);
                 break;

             case EMITCOND_CASE:
                 EMITCOND_FN(result, info);
                 break;

             case EMITFCOND_CASE:
                 EMITFCOND_FN(result, info);
                 break;

             case EMITFFF_CASE:
                 EMITFFF_FN(result, info);
                 break;

             case EMITL12_CASE:
                 EMITL12_FN(result, info);
                 break;

             case EMITOP_CASE:
                 EMITOP_FN(result, info);
                 break;

             case EMITOP0_CASE:
                 EMITOP0_FN(result, info);
                 break;

             case EMITR1_CASE:
                 EMITR1_FN(result, info);
                 break;

             case EMITR2_CASE:
                 EMITR2_FN(result, info);
                 break;

             case EMITR3_CASE:
                 EMITR3_FN(result, info);
                 break;

             case EMITR4_CASE:
                 EMITR4_FN(result, info);
                 break;

             case EMITSD_CASE:
                 EMITSD_FN(result, info);
                 break;

             case EMITSDR_CASE:
                 EMITSDR_FN(result, info);
                 break;

             case EMITSI_CASE:
                 EMITSI_FN(result, info);
                 break;

             case EMITSR1_CASE:
                 EMITSR1_FN(result, info, v850);
                 break;

             case EMITSR2_CASE:
                 EMITSR2_FN(result, info, v850);
                 break;

             case EMITSELID_CASE:
                 EMITSELID_FN(result, info);
                 break;

             case EMITSX_CASE:
                 EMITSX_FN(result, info);
                 break;

             case EMITUD_CASE:
                 EMITUD_FN(result, info);
                 break;

             case EMITUI_CASE:
                 EMITUI_FN(result, info);
                 break;

             case EMITUI5_CASE:
                 EMITUI5_FN(result, info);
                 break;

             case EMITUX_CASE:
                 EMITUX_FN(result, info);
                 break;

             case EMITPOS_CASE:
                 EMITPOS_FN(result, info);
                 break;

             case EMITWID_CASE:
                 EMITWID_FN(result, info);
                 break;

             default:
                 putChar(result, ch);
                 break;
        }
    }
}

//
// v850 disassembler, decoded instruction interface
//
const char *v850DisassembleInfo(v850P v850, v850InstructionInfoP info) {
    static char result[256];
    const char *format;
    char *tail = result;

    //
    // disassemble using the format for the type
    //
    if((format=formats[info->type]) && (info->type != V850_IT_LAST)) {
        disassembleFormat(v850, info, &tail, format);
    } else {
        sprintf(result, "UNDEFINED:0x" FMT_640Nx, info->instruction);
    }
    return result;
}

//
// v850 disassembler
//
VMI_DISASSEMBLE_FN(v850Dis) {
    // static buffer to hold disassembly result
    v850P v850 = (v850P)processor;
    v850InstructionInfo info = {0};
    // get instruction and instruction type
    v850Decode(v850, thisPC, &info);
    // return disassembled instruction
    return v850DisassembleInfo(v850, &info);
}

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

#include "vmi/vmiCxt.h"
#include "vmi/vmiDecode.h"
#include "vmi/vmiMessage.h"
#include "v850Decode.h"
#include "v850Instructions.h"

//
// Generate the instruction opcode table
//
static const char *opcode[V850_IT_LAST+1] = {
    //
    // Instruction Opcode F01 Insns
    //
    [V850_IT_ADD_F01]     = "add",
    [V850_IT_AND_F01]     = "and",
    [V850_IT_CMP_F01]     = "cmp",
    [V850_IT_DIVH_F01]    = "divh",
    [V850_IT_MOV_F01]     = "mov",
    [V850_IT_MULH_F01]    = "mulh",
    [V850_IT_NOT_F01]     = "not",
    [V850_IT_OR_F01]      = "or",
    [V850_IT_SATADD_F01]  = "satadd",
    [V850_IT_SATSUB_F01]  = "satsub",
    [V850_IT_SATSUBR_F01] = "satsubr",
    [V850_IT_SUB_F01]     = "sub",
    [V850_IT_SUBR_F01]    = "subr",
    [V850_IT_TST_F01]     = "tst",
    [V850_IT_XOR_F01]     = "xor",

    //
    // Instruction Opcode F01a Insns
    //
    [V850_IT_DBTRAP_F01A] = "dbtrap",
    [V850_IT_NOP_F01A]    = "nop",
    [V850_IT_RIE_F01A]    = "rie",
    [V850_IT_RMTRAP_F01A] = "rmtrap",
    [V850_IT_SYNCM_F01A]  = "syncm",
    [V850_IT_SYNCP_F01A]  = "syncp",
    [V850_IT_SYNCI_F01A]  = "synci",
    [V850_IT_SYNCE_F01A]  = "synce",

    //
    // Instruction Opcode F01b Insns
    //
    [V850_IT_JMP_F01B] = "jmp",

    //
    // Instruction Opcode F01c Insns
    //
    [V850_IT_SXB_F01C] = "sxb",
    [V850_IT_SXH_F01C] = "sxh",
    [V850_IT_ZXB_F01C] = "zxb",
    [V850_IT_ZXH_F01C] = "zxh",

    //
    // Instruction Opcode F01d Insns
    //
    [V850_IT_SWITCH_F01D] = "switch",

    //
    // Instruction Opcode F01e Insns
    //
    [V850_IT_FETRAP_F01E] = "fetrap",

    //
    // Instruction Opcode F02b Insns
    //
    [V850_IT_CALLT_F02B] = "callt",

    //
    // Instruction Opcode F02s Insns
    //
    [V850_IT_ADD_F02S]    = "add",
    [V850_IT_CMP_F02S]    = "cmp",
    [V850_IT_MOV_F02S]    = "mov",
    [V850_IT_MULH_F02S]   = "mulh",
    [V850_IT_SATADD_F02S] = "satadd",

    //
    // Instruction Opcode F02u Insns
    //
    [V850_IT_SAR_F02U] = "sar",
    [V850_IT_SHL_F02U] = "shl",
    [V850_IT_SHR_F02U] = "shr",

    //
    // Instruction Opcode F03 Insns
    //
    [V850_IT_BCOND_F03] = "b",

    //
    // Instruction Opcode F04db Insns
    //
    [V850_IT_SLD_BU_F04DB] = "sld.bu",

    //
    // Instruction Opcode F04dh Insns
    //
    [V850_IT_SLD_HU_F04DH] = "sld.hu",

    //
    // Instruction Opcode F04la Insns
    //
    [V850_IT_SLD_B_F04LA] = "sld.b",

    //
    // Instruction Opcode F04lb Insns
    //
    [V850_IT_SLD_H_F04LB] = "sld.h",

    //
    // Instruction Opcode F04lc Insns
    //
    [V850_IT_SLD_W_F04LC] = "sld.w",

    //
    // Instruction Opcode F04sa Insns
    //
    [V850_IT_SST_B_F04SA] = "sst.b",

    //
    // Instruction Opcode F04sb Insns
    //
    [V850_IT_SST_H_F04SB] = "sst.h",

    //
    // Instruction Opcode F04sc Insns
    //
    [V850_IT_SST_W_F04SC] = "sst.w",

    //
    // Instruction Opcode F05a Insns
    //
    [V850_IT_JARL_F05A] = "jarl",

    //
    // Instruction Opcode F05b Insns
    //
    [V850_IT_JR_F05B] = "jr",

    //
    // Instruction Opcode F06s Insns
    //
    [V850_IT_ADDI_F06S]    = "addi",
    [V850_IT_MOVEA_F06S]   = "movea",
    [V850_IT_MOVHI_F06S]   = "movhi",
    [V850_IT_MULHI_F06S]   = "mulhi",
    [V850_IT_SATSUBI_F06S] = "satsubi",

    //
    // Instruction Opcode F06sa Insns
    //
    [V850_IT_JARL_F06SA] = "jarl",

    //
    // Instruction Opcode F06sb Insns
    //
    [V850_IT_JMP_F06SB] = "jmp",

    //
    // Instruction Opcode F06sc Insns
    //
    [V850_IT_JR_F06SC] = "jr",

    //
    // Instruction Opcode F06u Insns
    //
    [V850_IT_ANDI_F06U] = "andi",
    [V850_IT_ORI_F06U]  = "ori",
    [V850_IT_XORI_F06U] = "xori",

    //
    // Instruction Opcode F06ua Insns
    //
    [V850_IT_MOV_F06UA] = "mov",

    //
    // Instruction Opcode F06x Insns
    //
    [V850_IT_RIE_F06X] = "rie",

    //
    // Instruction Opcode F07c Insns
    //
    [V850_IT_LD_BU_F07C] = "ld.bu",

    //
    // Instruction Opcode F07la Insns
    //
    [V850_IT_LD_B_F07LA] = "ld.b",

    //
    // Instruction Opcode F07lb Insns
    //
    [V850_IT_LD_H_F07LB]  = "ld.h",
    [V850_IT_LD_HU_F07LB] = "ld.hu",
    [V850_IT_LD_W_F07LB]  = "ld.w",

    //
    // Instruction Opcode F07sa Insns
    //
    [V850_IT_ST_B_F07SA] = "st.b",

    //
    // Instruction Opcode F07sb Insns
    //
    [V850_IT_ST_H_F07SB] = "st.h",
    [V850_IT_ST_W_F07SB] = "st.w",

    //
    // Instruction Opcode F08 Insns
    //
    [V850_IT_CLR1_F08] = "clr1",
    [V850_IT_NOT1_F08] = "not1",
    [V850_IT_SET1_F08] = "set1",
    [V850_IT_TST1_F08] = "tst1",

    //
    // Instruction Opcode F09 Insns
    //
    [V850_IT_SASF_F09] = "sasf",
    [V850_IT_SETF_F09] = "setf",

    //
    // Instruction Opcode F09rr Insns
    //
    [V850_IT_SAR_F09RR] = "sar",
    [V850_IT_SHL_F09RR] = "shl",
    [V850_IT_SHR_F09RR] = "shr",

    //
    // Instruction Opcode F09rr2 Insns
    //
    [V850_IT_SCH0L_F09RR2] = "sch0l",
    [V850_IT_SCH0R_F09RR2] = "sch0r",
    [V850_IT_SCH1L_F09RR2] = "sch1l",
    [V850_IT_SCH1R_F09RR2] = "sch1r",

    //
    // Instruction Opcode F09rs1 Insns
    //
    [V850_IT_LDSR_F09RS1_0] = "ldsr",
    [V850_IT_LDSR_F09RS1]   = "ldsr",

    //
    // Instruction Opcode F09rs2 Insns
    //
    [V850_IT_CLR1_F09RS2] = "clr1",
    [V850_IT_NOT1_F09RS2] = "not1",
    [V850_IT_SET1_F09RS2] = "set1",
    [V850_IT_TST1_F09RS2] = "tst1",

    //
    // Instruction Opcode F09sr Insns
    //
    [V850_IT_STSR_F09SR_0] = "stsr",
    [V850_IT_STSR_F09SR]   = "stsr",

    //
    // Instruction Opcode F10a Insns
    //
    [V850_IT_CTRET_F10A] = "ctret",
    [V850_IT_DBRET_F10A] = "dbret",
    [V850_IT_DI_F10A]    = "di",
    [V850_IT_EI_F10A]    = "ei",
    [V850_IT_EIRET_F10A] = "eiret",
    [V850_IT_FERET_F10A] = "feret",
    [V850_IT_HALT_F10A]  = "halt",
    [V850_IT_RETI_F10A]  = "reti",

    //
    // Instruction Opcode F10b Insns
    //
    [V850_IT_TRAP_F10B] = "trap",

    [V850_IT_SYSCALL_F10C] = "syscall",

    //
    // Instruction Opcode F11 Insns
    //
    [V850_IT_DIV_F11]    = "div",
    [V850_IT_DIVH_F11]   = "divh",
    [V850_IT_DIVHU_F11]  = "divhu",
    [V850_IT_DIVQ_F11]   = "divq",
    [V850_IT_DIVQU_F11]  = "divqu",
    [V850_IT_DIVU_F11]   = "divu",
    [V850_IT_MUL_F11]    = "mul",
    [V850_IT_MULU_F11]   = "mulu",
    [V850_IT_SAR_F11]    = "sar",
    [V850_IT_SATADD_F11] = "satadd",
    [V850_IT_SATSUB_F11] = "satsub",
    [V850_IT_SHL_F11]    = "shl",
    [V850_IT_SHR_F11]    = "shr",

    //
    // Instruction Opcode F11a Insns
    //
    [V850_IT_MAC_F11A]  = "mac",
    [V850_IT_MACU_F11A] = "macu",

    //
    // Instruction Opcode F11b Insns
    //
    [V850_IT_ADF_F11B]  = "adf",
    [V850_IT_CMOV_F11B] = "cmov",
    [V850_IT_SBF_F11B]  = "sbf",

    //
    // Instruction Opcode F11c Insns
    //
    [V850_IT_CAXI_F11C] = "caxi",

    //
    // Instruction Opcode F12a Insns
    //
    [V850_IT_CMOV_F12A] = "cmov",

    //
    // Instruction Opcode F12b Insns
    //
    [V850_IT_BSH_F12B] = "bsh",
    [V850_IT_BSW_F12B] = "bsw",
    [V850_IT_HSH_F12B] = "hsh",
    [V850_IT_HSW_F12B] = "hsw",

    //
    // Instruction Opcode F12s Insns
    //
    [V850_IT_MUL_F12S] = "mul",

    //
    // Instruction Opcode F12u Insns
    //
    [V850_IT_MULU_F12U] = "mulu",

    //
    // Instruction Opcode F13il1 Insns
    //
    [V850_IT_DISPOSE_F13IL1] = "dispose",

    //
    // Instruction Opcode F13il2 Insns
    //
    [V850_IT_DISPOSE_F13IL2] = "dispose",

    //
    // Instruction Opcode F13li Insns
    //
    [V850_IT_PREPARE_F13LI] = "prepare",

    //
    // Instruction Opcode F13li00 Insns
    //
    [V850_IT_PREPARE_F13LI00] = "prepare",

    //
    // Instruction Opcode F13li01 Insns
    //
    [V850_IT_PREPARE_F13LI01] = "prepare",

    //
    // Instruction Opcode F13li10 Insns
    //
    [V850_IT_PREPARE_F13LI10] = "prepare",

    //
    // Instruction Opcode F13li11 Insns
    //
    [V850_IT_PREPARE_F13LI11] = "prepare",

    //
    // Instruction Opcode FI Insns
    //
    [V850_IT_ADDF_S_FI] = "addf.s",
    [V850_IT_DIVF_S_FI] = "divf.s",
    [V850_IT_MAXF_S_FI] = "maxf.s",
    [V850_IT_MINF_S_FI] = "minf.s",
    [V850_IT_MULF_S_FI] = "mulf.s",
    [V850_IT_SUBF_S_FI] = "subf.s",

    //
    // Instruction Opcode FID Insns
    //
    [V850_IT_ADDF_D_FID] = "addf.d",
    [V850_IT_DIVF_D_FID] = "divf.d",
    [V850_IT_MAXF_D_FID] = "maxf.d",
    [V850_IT_MINF_D_FID] = "minf.d",
    [V850_IT_MULF_D_FID] = "mulf.d",
    [V850_IT_SUBF_D_FID] = "subf.d",

    //
    // Instruction Opcode FIDSr2r3 Insns
    //
    [V850_IT_CEILF_DW_FIDSR2R3]  = "ceilf.dw",
    [V850_IT_CVTF_DS_FIDSR2R3]   = "cvtf.ds",
    [V850_IT_CVTF_DUW_FIDSR2R3]  = "cvtf.duw",
    [V850_IT_CVTF_DW_FIDSR2R3]   = "cvtf.dw",
    [V850_IT_CVTF_LS_FIDSR2R3]   = "cvtf.ls",
    [V850_IT_CVTF_ULS_FIDSR2R3]  = "cvtf.uls",
    [V850_IT_FLOORF_DW_FIDSR2R3] = "floorf.dw",
    [V850_IT_TRNCF_DW_FIDSR2R3]  = "trncf.dw",

    //
    // Instruction Opcode FIDcond Insns
    //
    [V850_IT_CMPF_D_FIDCOND] = "cmpf.d",

    //
    // Instruction Opcode FIDfff Insns
    //
    [V850_IT_CMOVF_D_FIDFFF] = "cmovf.d",

    //
    // Instruction Opcode FIDr2r3 Insns
    //
    [V850_IT_ABSF_D_FIDR2R3]     = "absf.d",
    [V850_IT_CEILF_DL_FIDR2R3]   = "ceilf.dl",
    [V850_IT_CEILF_DUL_FIDR2R3]  = "ceilf.dul",
    [V850_IT_CEILF_DUW_FIDR2R3]  = "ceilf.duw",
    [V850_IT_CVTF_DL_FIDR2R3]    = "cvtf.dl",
    [V850_IT_CVTF_DUL_FIDR2R3]   = "cvtf.dul",
    [V850_IT_CVTF_ULD_FIDR2R3]   = "cvtf.uld",
    [V850_IT_FLOORF_DL_FIDR2R3]  = "floorf.dl",
    [V850_IT_FLOORF_DUL_FIDR2R3] = "floorf.dul",
    [V850_IT_FLOORF_DUW_FIDR2R3] = "floorf.duw",
    [V850_IT_NEGF_D_FIDR2R3]     = "negf.d",
    [V850_IT_RECIPF_D_FIDR2R3]   = "recipf.d",
    [V850_IT_RSQRTF_D_FIDR2R3]   = "rsqrtf.d",
    [V850_IT_SQRTF_D_FIDR2R3]    = "sqrtf.d",
    [V850_IT_TRNCF_DL_FIDR2R3]   = "trncf.dl",
    [V850_IT_TRNCF_DUL_FIDR2R3]  = "trncf.dul",
    [V850_IT_TRNCF_DUW_FIDR2R3]  = "trncf.duw",

    //
    // Instruction Opcode FII Insns
    //
    [V850_IT_ABSF_S_FII]  = "absf.s",
    [V850_IT_CVT_SW_FII]  = "cvt.sw",
    [V850_IT_CVT_WS_FII]  = "cvt.ws",
    [V850_IT_NEGF_S_FII]  = "negf.s",
    [V850_IT_TRNC_SW_FII] = "trnc.sw",

    //
    // Instruction Opcode FIS Insns
    //
    [V850_IT_ADDF_S_FIS] = "addf.s",
    [V850_IT_DIVF_S_FIS] = "divf.s",
    [V850_IT_MAXF_S_FIS] = "maxf.s",
    [V850_IT_MINF_S_FIS] = "minf.s",
    [V850_IT_MULF_S_FIS] = "mulf.s",
    [V850_IT_SUBF_S_FIS] = "subf.s",

    //
    // Instruction Opcode FISDr2r3 Insns
    //
    [V850_IT_CEILF_SL_FISDR2R3]   = "ceilf.sl",
    [V850_IT_CEILF_SUL_FISDR2R3]  = "ceilf.sul",
    [V850_IT_CVTF_SD_FISDR2R3]    = "cvtf.sd",
    [V850_IT_CVTF_SL_FISDR2R3]    = "cvtf.sl",
    [V850_IT_CVTF_SUL_FISDR2R3]   = "cvtf.sul",
    [V850_IT_CVTF_UWD_FISDR2R3]   = "cvtf.uwd",
    [V850_IT_CVTF_WD_FISDR2R3]    = "cvtf.wd",
    [V850_IT_FLOORF_SL_FISDR2R3]  = "floorf.sl",
    [V850_IT_FLOORF_SUL_FISDR2R3] = "floorf.sul",
    [V850_IT_TRNCF_SL_FISDR2R3]   = "trncf.sl",
    [V850_IT_TRNCF_SUL_FISDR2R3]  = "trncf.sul",

    //
    // Instruction Opcode FISa Insns
    //
    [V850_IT_MADDF_S_FISA]  = "maddf.s",
    [V850_IT_MSUBF_S_FISA]  = "msubf.s",
    [V850_IT_NMADDF_S_FISA] = "nmaddf.s",
    [V850_IT_NMSUBF_S_FISA] = "nmsubf.s",

    //
    // Instruction Opcode FIScond Insns
    //
    [V850_IT_CMPF_S_FISCOND] = "cmpf.s",

    //
    // Instruction Opcode FISfff Insns
    //
    [V850_IT_CMOVF_S_FISFFF] = "cmovf.s",

    //
    // Instruction Opcode FISr2r3 Insns
    //
    [V850_IT_ABSF_S_FISR2R3]     = "absf.s",
    [V850_IT_CEILF_SUW_FISR2R3]  = "ceilf.suw",
    [V850_IT_CEILF_SW_FISR2R3]   = "ceilf.sw",
    [V850_IT_CVTF_LD_FISR2R3]    = "cvtf.ld",
    [V850_IT_CVTF_SUW_FISR2R3]   = "cvtf.suw",
    [V850_IT_CVTF_SW_FISR2R3]    = "cvtf.sw",
    [V850_IT_CVTF_UWS_FISR2R3]   = "cvtf.uws",
    [V850_IT_CVTF_WS_FISR2R3]    = "cvtf.ws",
    [V850_IT_FLOORF_SUW_FISR2R3] = "floorf.suw",
    [V850_IT_FLOORF_SW_FISR2R3]  = "floorf.sw",
    [V850_IT_NEGF_S_FISR2R3]     = "negf.s",
    [V850_IT_RECIPF_S_FISR2R3]   = "recipf.s",
    [V850_IT_RSQRTF_S_FISR2R3]   = "rsqrtf.s",
    [V850_IT_SQRTF_S_FISR2R3]    = "sqrtf.s",
    [V850_IT_TRNCF_SUW_FISR2R3]  = "trncf.suw",
    [V850_IT_TRNCF_SW_FISR2R3]   = "trncf.sw",

    //
    // Instruction Opcode FIV Insns
    //
    [V850_IT_TRFF_FIV] = "trff",

    //
    // Instruction Opcode FIVr2a Insns
    //
    [V850_IT_LDFF_FIVR2A] = "ldff",

    //
    // Instruction Opcode FIVr2b Insns
    //
    [V850_IT_LDFC_FIVR2B] = "ldfc",

    //
    // Instruction Opcode FIVr3a Insns
    //
    [V850_IT_STFF_FIVR3A] = "stff",

    //
    // Instruction Opcode FIVr3b Insns
    //
    [V850_IT_STFC_FIVR3B] = "stfc",

    //
    // Instruction Opcode FIfff Insns
    //
    [V850_IT_TRFSR_FIFFF] = "trfsr",

    //
    // RH850 Only
    //
    // New
    [V850_IT_LDL_W_F07D]     = "ldl.w",
    [V850_IT_STC_W_F07D]     = "stc.w",
    [V850_IT_BINS_F09RPWR_0] = "bins",
    [V850_IT_BINS_F09RPWR_1] = "bins",
    [V850_IT_BINS_F09RPWR_2] = "bins",
    [V850_IT_CLL_F10]        = "cll",
    [V850_IT_SNOOZE_F10]     = "snooze",
    [V850_IT_ROTL_F07RRR]    = "rotl",
    [V850_IT_ROTL_F07IRR]    = "rotl",
    [V850_IT_LD_DW_F14]      = "ld.dw",
    [V850_IT_ST_DW_F14]      = "st.dw",
    // New Branch instructions
    [V850_IT_BCOND_F07CC]    = "b",
    [V850_IT_JARL_F11D]      = "jarl",
    [V850_IT_LOOP_F07RI]     = "loop",
    // New - but not indicated
    [V850_IT_LD_B_F14]       = "ld.b",
    [V850_IT_LD_BU_F14]      = "ld.bu",
    [V850_IT_LD_H_F14]       = "ld.h",
    [V850_IT_LD_HU_F14]      = "ld.hu",
    [V850_IT_LD_W_F14]       = "ld.w",
    [V850_IT_ST_B_F14]       = "st.b",
    [V850_IT_ST_H_F14]       = "st.h",
    [V850_IT_ST_W_F14]       = "st.w",
    [V850_IT_PUSHSP_F11]     = "pushsp",
    [V850_IT_POPSP_F11]      = "popsp",
    // New cache ops (not reported as new)
    [V850_IT_CACHE_F10]      = "cache",
    [V850_IT_CACHE_CHBII]    = "cache    chbii",
    [V850_IT_CACHE_CIBII]    = "cache    cibii",
    [V850_IT_CACHE_CFALI]    = "cache    cfali",
    [V850_IT_CACHE_CISTI]    = "cache    cisti",
    [V850_IT_CACHE_CILDI]    = "cache    cildi",
    [V850_IT_PREF_F10]       = "pref",
    [V850_IT_PREFI_F10]      = "pref     prefi",
    // FP Ops
    [V850_IT_CVTF_HS_FI]     = "cvtf.hs",
    [V850_IT_CVTF_SH_FI]     = "cvtf.sh",
    [V850_IT_FMAF_S_FI]      = "fmaf.s",
    [V850_IT_FMSF_S_FI]      = "fmsf.s",
    [V850_IT_FNMAF_S_FI]     = "fnmaf.s",
    [V850_IT_FNMSF_S_FI]     = "fnmsf.s",

    [V850_IT_LAST] = "UNDEFINED"
};

#define DECODE_ENTRY(_PRIORITY, _NAME, _FMT) \
    vmidNewEntryFmtBin( \
        table, \
        #_NAME, \
        V850_IT_##_NAME, \
        _FMT, \
        _PRIORITY \
    )

// ISA_E0 Decoder
vmidDecodeTableP v850CreateDecodeTable_ISA_E0_16Bit(vmidDecodeTableP current) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(16, V850_IT_LAST);
    }

    //                            F01   | reg2|opcode| reg1|
    DECODE_ENTRY( 6,          ADD_F01, "|.....|001110|.....|");
    DECODE_ENTRY( 6,          AND_F01, "|.....|001010|.....|");
    DECODE_ENTRY( 6,          CMP_F01, "|.....|001111|.....|");
    DECODE_ENTRY( 6,         DIVH_F01, "|.....|000010|.....|");
    DECODE_ENTRY( 6,          MOV_F01, "|.....|000000|.....|");
    DECODE_ENTRY( 6,         MULH_F01, "|.....|000111|.....|");
    DECODE_ENTRY( 6,          NOT_F01, "|.....|000001|.....|");
    DECODE_ENTRY( 6,           OR_F01, "|.....|001000|.....|");
    DECODE_ENTRY( 6,       SATADD_F01, "|.....|000110|.....|");
    DECODE_ENTRY( 6,       SATSUB_F01, "|.....|000101|.....|");
    DECODE_ENTRY( 6,      SATSUBR_F01, "|.....|000100|.....|");
    DECODE_ENTRY( 6,          SUB_F01, "|.....|001101|.....|");
    DECODE_ENTRY( 6,         SUBR_F01, "|.....|001100|.....|");
    DECODE_ENTRY( 6,          TST_F01, "|.....|001011|.....|");
    DECODE_ENTRY( 6,          XOR_F01, "|.....|001001|.....|");

    //                           F01a   |          opcode|
    DECODE_ENTRY(16,         NOP_F01A, "|0000000000000000|");

    //                           F01b   |supob|opcode| reg1|
    DECODE_ENTRY(11,         JMP_F01B, "|00000|000011|.....|");

    //                           F02s   | reg2|opcode| simm|
    DECODE_ENTRY( 6,         ADD_F02S, "|.....|010010|.....|");
    DECODE_ENTRY( 6,         CMP_F02S, "|.....|010011|.....|");
    DECODE_ENTRY( 6,         MOV_F02S, "|.....|010000|.....|");
    DECODE_ENTRY( 6,        MULH_F02S, "|.....|010111|.....|");
    DECODE_ENTRY( 6,      SATADD_F02S, "|.....|010001|.....|");

    //                           F02u   | reg2|opcode| uimm|
    DECODE_ENTRY( 6,         SAR_F02U, "|.....|010101|.....|");
    DECODE_ENTRY( 6,         SHL_F02U, "|.....|010110|.....|");
    DECODE_ENTRY( 6,         SHR_F02U, "|.....|010100|.....|");

    //                            F03   |sdisp|opco|sdi|cond|
    DECODE_ENTRY( 4,        BCOND_F03, "|.....|1011|...|....|");

    //                          F04la   | reg2|opco|  udisp|
    DECODE_ENTRY( 4,      SLD_B_F04LA, "|.....|0110|.......|");

    //                          F04lb   | reg2|opco|  udisp|
    DECODE_ENTRY( 4,      SLD_H_F04LB, "|.....|1000|.......|");

    //                          F04lc   | reg2|opco| udisp|d|
    DECODE_ENTRY( 5,      SLD_W_F04LC, "|.....|1010|......|0|");

    //                          F04sa   | reg2|opco|  udisp|
    DECODE_ENTRY( 4,      SST_B_F04SA, "|.....|0111|.......|");

    //                          F04sb   | reg2|opco|  udisp|
    DECODE_ENTRY( 4,      SST_H_F04SB, "|.....|1001|.......|");

    //                          F04sc   | reg2|opco| udisp|d|
    DECODE_ENTRY( 5,      SST_W_F04SC, "|.....|1010|......|1|");

    //
    // ISA_E0 Drop through section to next table
    //
    DECODE_ENTRY(16,          INSTR32, ".....11.........");
    DECODE_ENTRY(16,          INSTR32, "00000010111....."); // Explicit match for handling the JARL disp32

    return table;
}

// ISA_E0 Decoder
vmidDecodeTableP v850CreateDecodeTable_ISA_E0_32Bit(vmidDecodeTableP current) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(32, V850_IT_LAST);
    }

    //                           F05a   |          sdisp|b| reg2|opcod| sdisp|
    DECODE_ENTRY( 6,        JARL_F05A, "|...............|0|.....|11110|......|");

    //                           F05b   |          sdisp|b|supop|opcod| sdisp|
    DECODE_ENTRY(11,          JR_F05B, "|...............|0|00000|11110|......|");

    //                           F06s   |            simm| reg2|opcode| reg1|
    DECODE_ENTRY( 6,        ADDI_F06S, "|................|.....|110000|.....|");
    DECODE_ENTRY( 6,       MOVEA_F06S, "|................|.....|110001|.....|");
    DECODE_ENTRY( 6,       MOVHI_F06S, "|................|.....|110010|.....|");
    DECODE_ENTRY( 6,       MULHI_F06S, "|................|.....|110111|.....|");
    DECODE_ENTRY( 6,     SATSUBI_F06S, "|................|.....|110011|.....|");

    //                           F06u   |            uimm| reg2|opcode| reg1|
    DECODE_ENTRY( 6,        ANDI_F06U, "|................|.....|110110|.....|");
    DECODE_ENTRY( 6,         ORI_F06U, "|................|.....|110100|.....|");
    DECODE_ENTRY( 6,        XORI_F06U, "|................|.....|110101|.....|");

    //                          F07la   |           sdisp| reg2|opcode| reg1|
    DECODE_ENTRY( 6,       LD_B_F07LA, "|................|.....|111000|.....|");

    //                          F07lb   |          sdisp|s| reg2|opcode| reg1|
    DECODE_ENTRY( 7,       LD_H_F07LB, "|...............|0|.....|111001|.....|");
    DECODE_ENTRY( 7,       LD_W_F07LB, "|...............|1|.....|111001|.....|");

    //                          F07sa   |           sdisp| reg2|opcode| reg1|
    DECODE_ENTRY( 6,       ST_B_F07SA, "|................|.....|111010|.....|");

    //                          F07sb   |          sdisp|s| reg2|opcode| reg1|
    DECODE_ENTRY( 7,       ST_H_F07SB, "|...............|0|.....|111011|.....|");
    DECODE_ENTRY( 7,       ST_W_F07SB, "|...............|1|.....|111011|.....|");

    //                            F08   |           sdisp|su|bit|opcode| reg1|
    DECODE_ENTRY( 8,         CLR1_F08, "|................|10|...|111110|.....|");
    DECODE_ENTRY( 8,         NOT1_F08, "|................|01|...|111110|.....|");
    DECODE_ENTRY( 8,         SET1_F08, "|................|00|...|111110|.....|");
    DECODE_ENTRY( 8,         TST1_F08, "|................|11|...|111110|.....|");

    //                            F09   | rfu1| subop| rfu0| reg2| opcode|cccc|
    DECODE_ENTRY(23,         SETF_F09, "|00000|000000|00000|.....|1111110|....|");

    //                          F09rr   | rfu1| subop| rfu0| reg2|opcode| reg1|
    DECODE_ENTRY(22,        SAR_F09RR, "|00000|000101|00000|.....|111111|.....|");
    DECODE_ENTRY(22,        SHL_F09RR, "|00000|000110|00000|.....|111111|.....|");
    DECODE_ENTRY(22,        SHR_F09RR, "|00000|000100|00000|.....|111111|.....|");

    //                         F09rs1   |selID| subop| rfu0| reg2|opcode| reg1|
    DECODE_ENTRY(22,    LDSR_F09RS1_0, "|00000|000001|00000|.....|111111|.....|");
    DECODE_ENTRY(17,      LDSR_F09RS1, "|.....|000001|00000|.....|111111|.....|");

    //                          F09sr   |selID| subop| rfu0| reg2|opcode| reg1|
    DECODE_ENTRY(22,     STSR_F09SR_0, "|00000|000010|00000|.....|111111|.....|");
    DECODE_ENTRY(17,       STSR_F09SR, "|.....|000010|00000|.....|111111|.....|");

    //                           F10a   | rfu2|subop1|rfu1|b|sub|rf|opcode| rfu3|
    DECODE_ENTRY(32,          DI_F10A, "|00000|001011|0000|0|000|00|111111|00000|");
    DECODE_ENTRY(32,          EI_F10A, "|00000|001011|0000|0|100|00|111111|00000|");
    DECODE_ENTRY(32,        HALT_F10A, "|00000|001001|0000|0|000|00|111111|00000|");
    DECODE_ENTRY(32,        RETI_F10A, "|00000|001010|0000|0|000|00|111111|00000|");

    //                           F10b   | rfu2|subop1|rfu1|b|sub|rf|opcode| uimm|
    DECODE_ENTRY(27,        TRAP_F10B, "|00000|001000|0000|0|000|00|111111|.....|");

    return table;
}

// ISA_E1 Decoder
vmidDecodeTableP v850CreateDecodeTable_ISA_E1_16Bit(vmidDecodeTableP current) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(16, V850_IT_LAST);
    }

    //                           F01a   |          opcode|
    DECODE_ENTRY(16,      DBTRAP_F01A, "|1111100001000000|");

    //                           F01c   |subop|opcode| reg1|
    DECODE_ENTRY(11,         SXB_F01C, "|00000|000101|.....|");
    DECODE_ENTRY(11,         SXH_F01C, "|00000|000111|.....|");
    DECODE_ENTRY(11,         ZXB_F01C, "|00000|000100|.....|");
    DECODE_ENTRY(11,         ZXH_F01C, "|00000|000110|.....|");

    //                           F01d   |subop|opcode| reg1|
    DECODE_ENTRY(11,      SWITCH_F01D, "|00000|000010|.....|");

    //                           F02b   |subop|opcod|  uimm|
    DECODE_ENTRY(10,       CALLT_F02B, "|00000|01000|......|");

    //                          F04db   | reg2| opcode|udis|
    DECODE_ENTRY( 7,     SLD_BU_F04DB, "|.....|0000110|....|");

    //                          F04dh   | reg2| opcode|udis|
    DECODE_ENTRY( 7,     SLD_HU_F04DH, "|.....|0000111|....|");

    //
    // ISA_E1 Drop through section to next table
    //

    return table;
}

// ISA_E1 Decoder
vmidDecodeTableP v850CreateDecodeTable_ISA_E1_32Bit(vmidDecodeTableP current) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(32, V850_IT_LAST);
    }

    //                           F07c   |          sdisp|s| reg2|opcod|s| reg1|
    DECODE_ENTRY( 6,       LD_BU_F07C, "|...............|1|.....|11110|.|.....|");

    //                          F07lb   |          sdisp|s| reg2|opcode| reg1|
    DECODE_ENTRY( 7,      LD_HU_F07LB, "|...............|1|.....|111111|.....|");

    //                            F09   | rfu1| subop| rfu0| reg2| opcode|cccc|
    DECODE_ENTRY(23,         SASF_F09, "|00000|010000|00000|.....|1111110|....|");

    //                         F09rs2   | rfu1| subop| rfu0| reg2|opcode| reg1|
    DECODE_ENTRY(22,      CLR1_F09RS2, "|00000|000111|00100|.....|111111|.....|");
    DECODE_ENTRY(22,      NOT1_F09RS2, "|00000|000111|00010|.....|111111|.....|");
    DECODE_ENTRY(22,      SET1_F09RS2, "|00000|000111|00000|.....|111111|.....|");
    DECODE_ENTRY(22,      TST1_F09RS2, "|00000|000111|00110|.....|111111|.....|");

    //                           F10a   | rfu2|subop1|rfu1|b|sub|rf|opcode| rfu3|
    DECODE_ENTRY(32,       CTRET_F10A, "|00000|001010|0010|0|000|00|111111|00000|");
    DECODE_ENTRY(32,       DBRET_F10A, "|00000|001010|0011|0|000|00|111111|00000|");

    //                            F11   | reg3|subop1|rfu|s|b| reg2|opcode| reg1|
    DECODE_ENTRY(17,          DIV_F11, "|.....|010110|000|0|0|.....|111111|.....|");
    DECODE_ENTRY(17,         DIVH_F11, "|.....|010100|000|0|0|.....|111111|.....|");
    DECODE_ENTRY(17,        DIVHU_F11, "|.....|010100|000|1|0|.....|111111|.....|");
    DECODE_ENTRY(17,         DIVU_F11, "|.....|010110|000|1|0|.....|111111|.....|");
    DECODE_ENTRY(17,          MUL_F11, "|.....|010001|000|0|0|.....|111111|.....|");
    DECODE_ENTRY(17,         MULU_F11, "|.....|010001|000|1|0|.....|111111|.....|");

    //                           F11b   | reg3|subop1|cccc|b| reg2|opcode| reg1|
    DECODE_ENTRY(13,        CMOV_F11B, "|.....|011001|....|0|.....|111111|.....|");

    //                           F12a   | reg3| subop|cccc|b| reg2|opcode| simm|
    DECODE_ENTRY(13,        CMOV_F12A, "|.....|011000|....|0|.....|111111|.....|");

    //                           F12b   | reg3|     subop|b| reg2|     opcode|
    DECODE_ENTRY(22,         BSH_F12B, "|.....|0110100001|0|.....|11111100000|");
    DECODE_ENTRY(22,         BSW_F12B, "|.....|0110100000|0|.....|11111100000|");
    DECODE_ENTRY(22,         HSW_F12B, "|.....|0110100010|0|.....|11111100000|");

    //                           F12s   | reg3|subop|simm|s|b| reg2|opcode| simm|
    DECODE_ENTRY(13,         MUL_F12S, "|.....|01001|....|0|0|.....|111111|.....|");

    //                           F12u   | reg3|subop|uimm|s|b| reg2|opcode| uimm|
    DECODE_ENTRY(13,        MULU_F12U, "|.....|01001|....|1|0|.....|111111|.....|");

    //                         F13il1   |l|l|l|l|l|l|l|l|l|l|l|subop|  rfu|opcod|uimm5|l|
    DECODE_ENTRY(15,   DISPOSE_F13IL1, "|.|.|.|.|.|.|.|.|.|.|.|00000|00000|11001|.....|.|");

    //                         F13il2   |l|l|l|l|l|l|l|l|l|l|l| reg1|  rfu|opcod|uimm5|l|
    DECODE_ENTRY(10,   DISPOSE_F13IL2, "|.|.|.|.|.|.|.|.|.|.|.|.....|00000|11001|.....|.|");

    //                          F13li   |l|l|l|l|l|l|l|l|l|l|l|subop|  rfu|opcod|uimm5|l|
    DECODE_ENTRY(15,    PREPARE_F13LI, "|.|.|.|.|.|.|.|.|.|.|.|00001|00000|11110|.....|.|");

    //                        F13li00   |l|l|l|l|l|l|l|l|l|l|l|subop|  rfu|opcod|uimm5|l|
    DECODE_ENTRY(15,  PREPARE_F13LI00, "|.|.|.|.|.|.|.|.|.|.|.|00011|00000|11110|.....|.|");

    //
    // ISA_E1 Drop through section to next table
    //
    DECODE_ENTRY(11,          INSTR48, "................00000110001.....");
    DECODE_ENTRY(11,          INSTR48, "...............10000011110......"); // LD_BU et AL

    return table;
}

// ISA_E1 Decoder
vmidDecodeTableP v850CreateDecodeTable_ISA_E1_48Bit(vmidDecodeTableP current) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(64, V850_IT_LAST);
    }

    //                          F06ua   |         padding|                            uimm|subop|opcode| reg1|
    DECODE_ENTRY(11,        MOV_F06UA, "|................|................................|00000|110001|.....|");

    //                        F13li01   |         padding|            simm|l|l|l|l|l|l|l|l|l|l|l|subop|  rfu|opcod|uimm5|l|
    DECODE_ENTRY(15,  PREPARE_F13LI01, "|................|................|.|.|.|.|.|.|.|.|.|.|.|01011|00000|11110|.....|.|");

    //                        F13li10   |         padding|            simm|l|l|l|l|l|l|l|l|l|l|l|subop|  rfu|opcod|uimm5|l|
    DECODE_ENTRY(15,  PREPARE_F13LI10, "|................|................|.|.|.|.|.|.|.|.|.|.|.|10011|00000|11110|.....|.|");

    //
    // ISA_E1 Drop through section to next table
    //
    DECODE_ENTRY(15,          INSTR64, "...........................................110110000011110......");

    return table;
}

// ISA_E1 Decoder
vmidDecodeTableP v850CreateDecodeTable_ISA_E1_64Bit(vmidDecodeTableP current) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(64, V850_IT_LAST);
    }

    //                        F13li11   |                            simm|     list12|subop|  rfu|opcod|uimm5|l|
    DECODE_ENTRY(15,  PREPARE_F13LI11, "|................................|...........|11011|00000|11110|.....|.|");

    return table;
}

// ISA_E2 Decoder
vmidDecodeTableP v850CreateDecodeTable_ISA_E2_16Bit(vmidDecodeTableP current) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(16, V850_IT_LAST);
    }

    //                           F01a   |          opcode|
    DECODE_ENTRY(16,         RIE_F01A, "|0000000001000000|");
    DECODE_ENTRY(16,      RMTRAP_F01A, "|1111000001000000|");
    DECODE_ENTRY(16,       SYNCM_F01A, "|0000000000011110|");
    DECODE_ENTRY(16,       SYNCP_F01A, "|0000000000011111|");

    //                           F01e   |o|uimm|     opcode|
    DECODE_ENTRY(12,      FETRAP_F01E, "|0|....|00001000000|");

    //
    // ISA_E2 Drop through section to next table
    //

    return table;
}

// ISA_E2 Decoder
vmidDecodeTableP v850CreateDecodeTable_ISA_E2_32Bit(vmidDecodeTableP current) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(32, V850_IT_LAST);
    }

    //                           F06x   |            zero|    X| opcode|   X|
    DECODE_ENTRY(23,         RIE_F06X, "|0000000000000000|.....|1111111|....|");

    //                         F09rr2   | reg3|     subop1| reg2|opcode|subop|
    DECODE_ENTRY(22,     SCH0L_F09RR2, "|.....|01101100100|.....|111111|00000|");
    DECODE_ENTRY(22,     SCH0R_F09RR2, "|.....|01101100000|.....|111111|00000|");
    DECODE_ENTRY(22,     SCH1L_F09RR2, "|.....|01101100110|.....|111111|00000|");
    DECODE_ENTRY(22,     SCH1R_F09RR2, "|.....|01101100010|.....|111111|00000|");

    //                           F10a   | rfu2|subop1|rfu1|b|sub|rf|opcode| rfu3|
    DECODE_ENTRY(32,       EIRET_F10A, "|00000|001010|0100|0|000|00|111111|00000|");
    DECODE_ENTRY(32,       FERET_F10A, "|00000|001010|0101|0|000|00|111111|00000|");

    //                            F11   | reg3|subop1|rfu|s|b| reg2|opcode| reg1|
    DECODE_ENTRY(17,         DIVQ_F11, "|.....|010111|111|0|0|.....|111111|.....|");
    DECODE_ENTRY(17,        DIVQU_F11, "|.....|010111|111|1|0|.....|111111|.....|");
    DECODE_ENTRY(17,          SAR_F11, "|.....|000101|000|1|0|.....|111111|.....|");
    DECODE_ENTRY(17,       SATADD_F11, "|.....|011101|110|1|0|.....|111111|.....|");
    DECODE_ENTRY(17,       SATSUB_F11, "|.....|011100|110|1|0|.....|111111|.....|");
    DECODE_ENTRY(17,          SHL_F11, "|.....|000110|000|1|0|.....|111111|.....|");
    DECODE_ENTRY(17,          SHR_F11, "|.....|000100|000|1|0|.....|111111|.....|");

    //                           F11a   |reg3| subop1|reg4|b| reg2|opcode| reg1|
    DECODE_ENTRY(14,         MAC_F11A, "|....|0011110|....|0|.....|111111|.....|");
    DECODE_ENTRY(14,        MACU_F11A, "|....|0011111|....|0|.....|111111|.....|");

    //                           F11b   | reg3|subop1|cccc|b| reg2|opcode| reg1|
    DECODE_ENTRY(13,         ADF_F11B, "|.....|011101|....|0|.....|111111|.....|");
    DECODE_ENTRY(13,         SBF_F11B, "|.....|011100|....|0|.....|111111|.....|");

    //                           F11c   | reg3|subop1|rfu|s|b| reg2|opcode| reg1|
    DECODE_ENTRY(17,        CAXI_F11C, "|.....|000111|011|1|0|.....|111111|.....|");

    //                           F12b   | reg3|     subop|b| reg2|     opcode|
    DECODE_ENTRY(22,         HSH_F12B, "|.....|0110100011|0|.....|11111100000|");

    //
    // ISA_E2 Drop through section to next table
    //
    DECODE_ENTRY(12,          INSTR48, "...............000000010111.....");
    DECODE_ENTRY(12,          INSTR48, "...............000000110111.....");

    return table;
}

// ISA_E2 Decoder
vmidDecodeTableP v850CreateDecodeTable_ISA_E2_48Bit(vmidDecodeTableP current) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(64, V850_IT_LAST);
    }

    //                          F06sa   |         padding|                          sdisp|b|subop|opcode| reg1|
    DECODE_ENTRY(12,       JARL_F06SA, "|................|...............................|0|00000|010111|.....|");

    //                          F06sb   |         padding|                          sdisp|b|subop|opcode| reg1|
    DECODE_ENTRY(12,        JMP_F06SB, "|................|...............................|0|00000|110111|.....|");

    //                          F06sc   |         padding|                          sdisp|b|subop|opcode|subop|
    DECODE_ENTRY(17,         JR_F06SC, "|................|...............................|0|00000|010111|00000|");

    return table;
}

// ISA_E1_FP Decoder
vmidDecodeTableP v850CreateDecodeTable_ISA_E1_FP_32Bit(vmidDecodeTableP current) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(32, V850_IT_LAST);
    }

    //                             FI   | reg3|      subop| reg2|opcode| reg1|
    DECODE_ENTRY(17,        ADDF_S_FI, "|.....|01111101000|.....|111111|.....|");
    DECODE_ENTRY(17,        DIVF_S_FI, "|.....|01111100000|.....|111111|.....|");
    DECODE_ENTRY(17,        MAXF_S_FI, "|.....|01111110100|.....|111111|.....|");
    DECODE_ENTRY(17,        MINF_S_FI, "|.....|01111110000|.....|111111|.....|");
    DECODE_ENTRY(17,        MULF_S_FI, "|.....|01111101100|.....|111111|.....|");
    DECODE_ENTRY(17,        SUBF_S_FI, "|.....|01111100100|.....|111111|.....|");

    //                            FII   | reg3|      subop| reg2|opcode| rfu1|
    DECODE_ENTRY(22,       ABSF_S_FII, "|.....|01111111100|.....|111111|00000|");
    DECODE_ENTRY(22,       CVT_SW_FII, "|.....|01101100000|.....|111111|00000|");
    DECODE_ENTRY(22,       CVT_WS_FII, "|.....|01101110000|.....|111111|00000|");
    DECODE_ENTRY(22,       NEGF_S_FII, "|.....|01111111000|.....|111111|00000|");
    DECODE_ENTRY(22,      TRNC_SW_FII, "|.....|01101101000|.....|111111|00000|");

    //                            FIV   | rfu3|      subop| rfu2|opcode| rfu1|
    DECODE_ENTRY(32,         TRFF_FIV, "|00000|01101111000|00000|111111|00000|");

    //                         FIVr2a   | rfu3|      subop| reg2|opcode| rfu1|
    DECODE_ENTRY(27,      LDFF_FIVR2A, "|00000|01101111010|.....|111111|00000|");

    //                         FIVr2b   | rfu3|      subop| reg2|opcode| rfu1|
    DECODE_ENTRY(27,      LDFC_FIVR2B, "|00000|01101111110|.....|111111|00000|");

    //                         FIVr3a   | reg3|      subop| rfu2|opcode| rfu1|
    DECODE_ENTRY(27,      STFF_FIVR3A, "|.....|01101111000|00000|111111|00000|");

    //                         FIVr3b   | reg3|      subop| rfu2|opcode| rfu1|
    DECODE_ENTRY(27,      STFC_FIVR3B, "|.....|01101111100|00000|111111|00000|");

    return table;
}

// ISA_E2_FP Decoder
vmidDecodeTableP v850CreateDecodeTable_ISA_E2_FP_32Bit(vmidDecodeTableP current) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(32, V850_IT_LAST);
    }

    //                              FID   |reg3|b2|cat|ty|subo|b|reg2|b|opcode|reg1|b|
    DECODE_ENTRY(20,         ADDF_D_FID, "|....|01|000|11|1000|0|....|0|111111|....|0|");
    DECODE_ENTRY(20,         DIVF_D_FID, "|....|01|000|11|1111|0|....|0|111111|....|0|");
    DECODE_ENTRY(20,         MAXF_D_FID, "|....|01|000|11|1100|0|....|0|111111|....|0|");
    DECODE_ENTRY(20,         MINF_D_FID, "|....|01|000|11|1101|0|....|0|111111|....|0|");
    DECODE_ENTRY(20,         MULF_D_FID, "|....|01|000|11|1010|0|....|0|111111|....|0|");
    DECODE_ENTRY(20,         SUBF_D_FID, "|....|01|000|11|1001|0|....|0|111111|....|0|");

    //                         FIDSr2r3   | reg3|b|cat|ty|subo|b|reg2|b|opcode|   b0|
    DECODE_ENTRY(23,  CEILF_DW_FIDSR2R3, "|.....|1|000|10|1000|0|....|0|111111|00010|");
    DECODE_ENTRY(23,   CVTF_DS_FIDSR2R3, "|.....|1|000|10|1001|0|....|0|111111|00011|");
    DECODE_ENTRY(23,  CVTF_DUW_FIDSR2R3, "|.....|1|000|10|1000|0|....|0|111111|10100|");
    DECODE_ENTRY(23,   CVTF_DW_FIDSR2R3, "|.....|1|000|10|1000|0|....|0|111111|00100|");
    DECODE_ENTRY(23,   CVTF_LS_FIDSR2R3, "|.....|1|000|10|0001|0|....|0|111111|00001|");
    DECODE_ENTRY(23,  CVTF_ULS_FIDSR2R3, "|.....|1|000|10|0001|0|....|0|111111|10001|");
    DECODE_ENTRY(23, FLOORF_DW_FIDSR2R3, "|.....|1|000|10|1000|0|....|0|111111|00011|");
    DECODE_ENTRY(23,  TRNCF_DW_FIDSR2R3, "|.....|1|000|10|1000|0|....|0|111111|00001|");

    //                          FIDcond   |b|cond|b|cat|ty|b|fff|b|reg2|b|opcode|reg1|b|
    DECODE_ENTRY(17,     CMPF_D_FIDCOND, "|0|....|1|000|01|1|...|0|....|0|111111|....|0|");

    //                           FIDfff   |reg3|b2|cat|ty|b|fff|b|reg2|b|opcode|reg1|b|
    DECODE_ENTRY(17,     CMOVF_D_FIDFFF, "|....|01|000|00|1|...|0|....|0|111111|....|0|");

    //                          FIDr2r3   |reg3|b2|cat|ty|subo|b|reg2|b|opcode|   b0|
    DECODE_ENTRY(24,     ABSF_D_FIDR2R3, "|....|01|000|10|1100|0|....|0|111111|00000|");
    DECODE_ENTRY(24,   CEILF_DL_FIDR2R3, "|....|01|000|10|1010|0|....|0|111111|00010|");
    DECODE_ENTRY(24,  CEILF_DUL_FIDR2R3, "|....|01|000|10|1010|0|....|0|111111|10010|");
    DECODE_ENTRY(24,  CEILF_DUW_FIDR2R3, "|....|01|000|10|1000|0|....|0|111111|10010|");
    DECODE_ENTRY(24,    CVTF_DL_FIDR2R3, "|....|01|000|10|1010|0|....|0|111111|00100|");
    DECODE_ENTRY(24,   CVTF_DUL_FIDR2R3, "|....|01|000|10|1010|0|....|0|111111|10100|");
    DECODE_ENTRY(24,   CVTF_ULD_FIDR2R3, "|....|01|000|10|1001|0|....|0|111111|10001|");
    DECODE_ENTRY(24,  FLOORF_DL_FIDR2R3, "|....|01|000|10|1010|0|....|0|111111|00011|");
    DECODE_ENTRY(24, FLOORF_DUL_FIDR2R3, "|....|01|000|10|1010|0|....|0|111111|10011|");
    DECODE_ENTRY(24, FLOORF_DUW_FIDR2R3, "|....|01|000|10|1000|0|....|0|111111|10011|");
    DECODE_ENTRY(24,     NEGF_D_FIDR2R3, "|....|01|000|10|1100|0|....|0|111111|00001|");
    DECODE_ENTRY(24,   RECIPF_D_FIDR2R3, "|....|01|000|10|1111|0|....|0|111111|00001|");
    DECODE_ENTRY(24,   RSQRTF_D_FIDR2R3, "|....|01|000|10|1111|0|....|0|111111|00010|");
    DECODE_ENTRY(24,    SQRTF_D_FIDR2R3, "|....|01|000|10|1111|0|....|0|111111|00000|");
    DECODE_ENTRY(24,   TRNCF_DL_FIDR2R3, "|....|01|000|10|1010|0|....|0|111111|00001|");
    DECODE_ENTRY(24,  TRNCF_DUL_FIDR2R3, "|....|01|000|10|1010|0|....|0|111111|10001|");
    DECODE_ENTRY(24,  TRNCF_DUW_FIDR2R3, "|....|01|000|10|1000|0|....|0|111111|10001|");

    //                               FIS   | reg3|b|cat|ty|subo|b| reg2|opcode| reg1|
    DECODE_ENTRY(17,          ADDF_S_FIS, "|.....|1|000|11|0000|0|.....|111111|.....|");
    DECODE_ENTRY(17,          DIVF_S_FIS, "|.....|1|000|11|0111|0|.....|111111|.....|");
    DECODE_ENTRY(17,          MAXF_S_FIS, "|.....|1|000|11|0100|0|.....|111111|.....|");
    DECODE_ENTRY(17,          MINF_S_FIS, "|.....|1|000|11|0101|0|.....|111111|.....|");
    DECODE_ENTRY(17,          MULF_S_FIS, "|.....|1|000|11|0010|0|.....|111111|.....|");
    DECODE_ENTRY(17,          SUBF_S_FIS, "|.....|1|000|11|0001|0|.....|111111|.....|");

    //                          FISDr2r3   |reg3|b2|cat|ty|subo|b| reg2|opcode|   b0|
    DECODE_ENTRY(23,   CEILF_SL_FISDR2R3, "|....|01|000|10|0010|0|.....|111111|00010|");
    DECODE_ENTRY(23,  CEILF_SUL_FISDR2R3, "|....|01|000|10|0010|0|.....|111111|10010|");
    DECODE_ENTRY(23,    CVTF_SD_FISDR2R3, "|....|01|000|10|1001|0|.....|111111|00010|");
    DECODE_ENTRY(23,    CVTF_SL_FISDR2R3, "|....|01|000|10|0010|0|.....|111111|00100|");
    DECODE_ENTRY(23,   CVTF_SUL_FISDR2R3, "|....|01|000|10|0010|0|.....|111111|10100|");
    DECODE_ENTRY(23,   CVTF_UWD_FISDR2R3, "|....|01|000|10|1001|0|.....|111111|10000|");
    DECODE_ENTRY(23,    CVTF_WD_FISDR2R3, "|....|01|000|10|1001|0|.....|111111|00000|");
    DECODE_ENTRY(23,  FLOORF_SL_FISDR2R3, "|....|01|000|10|0010|0|.....|111111|00011|");
    DECODE_ENTRY(23, FLOORF_SUL_FISDR2R3, "|....|01|000|10|0010|0|.....|111111|10011|");
    DECODE_ENTRY(23,   TRNCF_SL_FISDR2R3, "|....|01|000|10|0010|0|.....|111111|00001|");
    DECODE_ENTRY(23,  TRNCF_SUL_FISDR2R3, "|....|01|000|10|0010|0|.....|111111|10001|");

    //                              FISa   | reg3|b|ca|r|ty|reg4|b| reg2|opcode| reg1|
    DECODE_ENTRY(12,        MADDF_S_FISA, "|.....|1|01|.|00|....|0|.....|111111|.....|");
    DECODE_ENTRY(12,        MSUBF_S_FISA, "|.....|1|01|.|01|....|0|.....|111111|.....|");
    DECODE_ENTRY(12,       NMADDF_S_FISA, "|.....|1|01|.|10|....|0|.....|111111|.....|");
    DECODE_ENTRY(12,       NMSUBF_S_FISA, "|.....|1|01|.|11|....|0|.....|111111|.....|");

    //                           FIScond   |b|cond|b|cat|ty|b|fff|b| reg2|opcode| reg1|
    DECODE_ENTRY(15,      CMPF_S_FISCOND, "|0|....|1|000|01|0|...|0|.....|111111|.....|");

    //                           FISfff   | reg3|b|cat|ty|b|fff|b| reg2|opcode| reg1|
    DECODE_ENTRY(14,     CMOVF_S_FISFFF, "|.....|1|000|00|0|...|0|.....|111111|.....|");

    //                        FISr2r3     | reg3|b|cat|ty|subo|b| reg2|opcode|   b0|
    DECODE_ENTRY(22,     ABSF_S_FISR2R3, "|.....|1|000|10|0100|0|.....|111111|00000|");
    DECODE_ENTRY(22,  CEILF_SUW_FISR2R3, "|.....|1|000|10|0000|0|.....|111111|10010|");
    DECODE_ENTRY(22,   CEILF_SW_FISR2R3, "|.....|1|000|10|0000|0|.....|111111|00010|");
    DECODE_ENTRY(22,    CVTF_LD_FISR2R3, "|.....|1|000|10|1001|0|.....|111111|00001|");
    DECODE_ENTRY(22,   CVTF_SUW_FISR2R3, "|.....|1|000|10|0000|0|.....|111111|10100|");
    DECODE_ENTRY(22,    CVTF_SW_FISR2R3, "|.....|1|000|10|0000|0|.....|111111|00100|");
    DECODE_ENTRY(22,   CVTF_UWS_FISR2R3, "|.....|1|000|10|0001|0|.....|111111|10000|");
    DECODE_ENTRY(22,    CVTF_WS_FISR2R3, "|.....|1|000|10|0001|0|.....|111111|00000|");
    DECODE_ENTRY(22, FLOORF_SUW_FISR2R3, "|.....|1|000|10|0000|0|.....|111111|10011|");
    DECODE_ENTRY(22,  FLOORF_SW_FISR2R3, "|.....|1|000|10|0000|0|.....|111111|00011|");
    DECODE_ENTRY(22,     NEGF_S_FISR2R3, "|.....|1|000|10|0100|0|.....|111111|00001|");
    DECODE_ENTRY(22,   RECIPF_S_FISR2R3, "|.....|1|000|10|0111|0|.....|111111|00001|");
    DECODE_ENTRY(22,   RSQRTF_S_FISR2R3, "|.....|1|000|10|0111|0|.....|111111|00010|");
    DECODE_ENTRY(22,    SQRTF_S_FISR2R3, "|.....|1|000|10|0111|0|.....|111111|00000|");
    DECODE_ENTRY(22,  TRNCF_SUW_FISR2R3, "|.....|1|000|10|0000|0|.....|111111|10001|");
    DECODE_ENTRY(22,   TRNCF_SW_FISR2R3, "|.....|1|000|10|0000|0|.....|111111|00001|");

    //                            FIfff   |      opcode|fff|           opcode|
    DECODE_ENTRY(29,        TRFSR_FIFFF, "|000001000000|...|00000011111100000|");

    return table;
}

// ISA_E3 Decoder
vmidDecodeTableP v850CreateDecodeTable_ISA_E3_32Bit(vmidDecodeTableP current) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(32, V850_IT_LAST);
    }

    //                           F11d   | reg3|     subop1|     opcode| reg1|
    DECODE_ENTRY(22,        JARL_F11D, "|.....|00101100000|11000111111|.....|");

    //                          F07CC              sdisp|b|     opcode|D|cccc|
    DECODE_ENTRY(12,      BCOND_F07CC, "|...............|1|00000111111|.|....|");

    //                            F10   |                |                |
    DECODE_ENTRY(32,          CLL_F10, "|1111000101100000|1111111111111111|");
    DECODE_ENTRY(32,       SNOOZE_F10, "|0000000100100000|0000111111100000|");

    //                            F10   |PPPPP|           |   |pp|      |reg1 |
    DECODE_ENTRY(20,        CACHE_F10, "|.....|00101100000|111|..|111111|.....|");
    DECODE_ENTRY(27,      CACHE_CHBII, "|00000|00101100000|111|00|111111|.....|");
    DECODE_ENTRY(27,      CACHE_CIBII, "|00000|00101100000|111|01|111111|.....|");
    DECODE_ENTRY(27,      CACHE_CFALI, "|00000|00101100000|111|10|111111|.....|");
    DECODE_ENTRY(27,      CACHE_CISTI, "|00000|00101100000|111|11|111111|.....|");
    DECODE_ENTRY(27,      CACHE_CILDI, "|00001|00101100000|111|11|111111|.....|");
    DECODE_ENTRY(22,         PREF_F10, "|.....|00101100000|110|11|111111|.....|");
    DECODE_ENTRY(27,        PREFI_F10, "|00000|00101100000|110|11|111111|.....|");

    //                           F10C   |  |vvv|           |           |vvvvv|
    DECODE_ENTRY(24,     SYSCALL_F10C, "|00|...|00101100000|11010111111|.....|");

    //                          F07RI              sdisp|b|     opcode| reg1|
    DECODE_ENTRY(12,       LOOP_F07RI, "|...............|1|00000110111|.....|");

    //                           F07D   | reg3|     subop1|     opcode| reg1|
    DECODE_ENTRY(22,       LDL_W_F07D, "|.....|01101111000|00000111111|.....|");
    DECODE_ENTRY(22,       STC_W_F07D, "|.....|01101111010|00000111111|.....|");

    //                        F09RPWR   |   M|K| subop1|  L| | reg2|opcode| reg1|
    DECODE_ENTRY(14,   BINS_F09RPWR_0, "|....|.|0001001|...|0|.....|111111|.....|");
    DECODE_ENTRY(14,   BINS_F09RPWR_1, "|....|.|0001011|...|0|.....|111111|.....|");
    DECODE_ENTRY(14,   BINS_F09RPWR_2, "|....|.|0001101|...|0|.....|111111|.....|");

    //                            F11   | reg3|                  opcode| reg1|
    DECODE_ENTRY(22,       PUSHSP_F11, "|.....|00101100000|01000|111111|.....|");
    DECODE_ENTRY(22,        POPSP_F11, "|.....|00101100000|01100|111111|.....|");

    //                         F07RRR   | reg3|     subop1| reg2|opcode| reg1|
    DECODE_ENTRY(14,      ROTL_F07RRR, "|.....|00011000110|.....|111111|.....|");

    //                         F07IRR   | reg3|     subop1| reg2|opcode| imm5|
    DECODE_ENTRY(14,      ROTL_F07IRR, "|.....|00011000100|.....|111111|.....|");

    return table;
}

// ISA_E3 Decoder
vmidDecodeTableP v850CreateDecodeTable_ISA_E3_16Bit(vmidDecodeTableP current) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(16, V850_IT_LAST);
    }

    //                           F01a   |          opcode|
    DECODE_ENTRY(16,       SYNCE_F01A, "|0000000000011101|");
    DECODE_ENTRY(16,       SYNCI_F01A, "|0000000000011100");

    return table;
}

// ISA_E3 Decoder
vmidDecodeTableP v850CreateDecodeTable_ISA_E3_FP_32Bit(vmidDecodeTableP current) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(32, V850_IT_LAST);
    }

    //                               FI   | reg3|b|cat|ty|subo|b|reg2 |opcode|   b0|
    DECODE_ENTRY(22,         CVTF_HS_FI, "|.....|1|000|10|0001|0|.....|111111|00010|");
    DECODE_ENTRY(22,         CVTF_SH_FI, "|.....|1|000|10|0001|0|.....|111111|00011|");

    //                             FI   | reg3|      subop| reg2|opcode| reg1|
    DECODE_ENTRY(17,        FMAF_S_FI, "|.....|10011100000|.....|111111|.....|");
    DECODE_ENTRY(17,        FMSF_S_FI, "|.....|10011100010|.....|111111|.....|");
    DECODE_ENTRY(17,       FNMAF_S_FI, "|.....|10011100100|.....|111111|.....|");
    DECODE_ENTRY(17,       FNMSF_S_FI, "|.....|10011100110|.....|111111|.....|");

    return table;
}

// ISA_E3 Decoder
vmidDecodeTableP v850CreateDecodeTable_ISA_E3_48Bit(vmidDecodeTableP current) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(64, V850_IT_LAST);
    }

    //                            F14   |         padding|           sdisp| reg3| sdisp|subop|     opcode| reg1|
    DECODE_ENTRY(16,        LD_DW_F14, "|................|................|.....|......|01001|00000111101|.....|");
    DECODE_ENTRY(16,        ST_DW_F14, "|................|................|.....|......|01111|00000111101|.....|");
    DECODE_ENTRY(15,        LD_BU_F14, "|................|................|.....|.......|0101|00000111101|.....|");
    DECODE_ENTRY(15,         LD_B_F14, "|................|................|.....|.......|0101|00000111100|.....|");
    DECODE_ENTRY(15,         ST_B_F14, "|................|................|.....|.......|1101|00000111100|.....|");
    DECODE_ENTRY(16,        LD_HU_F14, "|................|................|.....|......|00111|00000111101|.....|");
    DECODE_ENTRY(16,         LD_H_F14, "|................|................|.....|......|00111|00000111100|.....|");
    DECODE_ENTRY(16,         ST_H_F14, "|................|................|.....|......|01101|00000111101|.....|");
    DECODE_ENTRY(16,         LD_W_F14, "|................|................|.....|......|01001|00000111100|.....|");
    DECODE_ENTRY(16,         ST_W_F14, "|................|................|.....|......|01111|00000111100|.....|");

    return table;
}

static const octiaInstructionClass classes[V850_IT_LAST] = {
        [V850_IT_ADD_F01]             = OCL_IC_INTEGER,
        [V850_IT_AND_F01]             = OCL_IC_INTEGER,
        [V850_IT_CMP_F01]             = OCL_IC_INTEGER,
        [V850_IT_DIVH_F01]            = OCL_IC_DIVIDE,
        [V850_IT_MOV_F01]             = OCL_IC_INTEGER,
        [V850_IT_MULH_F01]            = OCL_IC_MULTIPLY,
        [V850_IT_NOT_F01]             = OCL_IC_INTEGER,
        [V850_IT_OR_F01]              = OCL_IC_INTEGER,
        [V850_IT_SATADD_F01]          = OCL_IC_INTEGER,
        [V850_IT_SATSUB_F01]          = OCL_IC_INTEGER,
        [V850_IT_SATSUBR_F01]         = OCL_IC_INTEGER,
        [V850_IT_SUB_F01]             = OCL_IC_INTEGER,
        [V850_IT_SUBR_F01]            = OCL_IC_INTEGER,
        [V850_IT_TST_F01]             = OCL_IC_INTEGER,
        [V850_IT_XOR_F01]             = OCL_IC_INTEGER,

        //
        // format F01a Insns
        //
        [V850_IT_DBTRAP_F01A]         = OCL_IC_SYSTEM,
        [V850_IT_NOP_F01A]            = OCL_IC_NOP,
        [V850_IT_RIE_F01A]            = OCL_IC_SYSTEM,
        [V850_IT_RMTRAP_F01A]         = OCL_IC_SYSTEM,
        [V850_IT_SYNCM_F01A]          = OCL_IC_ICACHE,
        [V850_IT_SYNCP_F01A]          = OCL_IC_ICACHE,
        [V850_IT_SYNCI_F01A]          = OCL_IC_ICACHE,
        [V850_IT_SYNCE_F01A]          = OCL_IC_ICACHE,

        //
        // format F01b Insns
        //
        [V850_IT_JMP_F01B]            = OCL_IC_BRANCH,

        //
        // format F01c Insns
        //
        [V850_IT_SXB_F01C]            = OCL_IC_INTEGER,
        [V850_IT_SXH_F01C]            = OCL_IC_INTEGER,
        [V850_IT_ZXB_F01C]            = OCL_IC_INTEGER,
        [V850_IT_ZXH_F01C]            = OCL_IC_INTEGER,

        //
        // format F01d Insns
        //
        [V850_IT_SWITCH_F01D]         = OCL_IC_BRANCH,

        //
        // format F01e Insns
        //
        [V850_IT_FETRAP_F01E]         = OCL_IC_SYSTEM,

        //
        // format F02b Insns
        //
        [V850_IT_CALLT_F02B]          = OCL_IC_BRANCH,

        //
        // format F02s Insns
        //
        [V850_IT_ADD_F02S]            = OCL_IC_INTEGER,
        [V850_IT_CMP_F02S]            = OCL_IC_INTEGER,
        [V850_IT_MOV_F02S]            = OCL_IC_INTEGER,
        [V850_IT_MULH_F02S]           = OCL_IC_MULTIPLY,
        [V850_IT_SATADD_F02S]         = OCL_IC_INTEGER,

        //
        // format F02u Insns
        //
        [V850_IT_SAR_F02U]            = OCL_IC_NOP,
        [V850_IT_SHL_F02U]            = OCL_IC_NOP,
        [V850_IT_SHR_F02U]            = OCL_IC_NOP,

        //
        // format F03 Insns
        //
        [V850_IT_BCOND_F03]           = OCL_IC_BRANCH,

        //
        // format F04db Insns
        //
        [V850_IT_SLD_BU_F04DB]        = OCL_IC_NOP,

        //
        // format F04dh Insns
        //
        [V850_IT_SLD_HU_F04DH]        = OCL_IC_NOP,

        //
        // format F04la Insns
        //
        [V850_IT_SLD_B_F04LA]         = OCL_IC_NOP,

        //
        // format F04lb Insns
        //
        [V850_IT_SLD_H_F04LB]         = OCL_IC_NOP,

        //
        // format F04lc Insns
        //
        [V850_IT_SLD_W_F04LC]         = OCL_IC_NOP,

        //
        // format F04sa Insns
        //
        [V850_IT_SST_B_F04SA]         = OCL_IC_NOP,

        //
        // format F04sb Insns
        //
        [V850_IT_SST_H_F04SB]         = OCL_IC_NOP,

        //
        // format F04sc Insns
        //
        [V850_IT_SST_W_F04SC]         = OCL_IC_NOP,

        //
        // format F05a Insns
        //
        [V850_IT_JARL_F05A]           = OCL_IC_BRANCH,

        //
        // format F05b Insns
        //
        [V850_IT_JR_F05B]             = OCL_IC_BRANCH,

        //
        // format F06s Insns
        //
        [V850_IT_ADDI_F06S]           = OCL_IC_INTEGER,
        [V850_IT_MOVEA_F06S]          = OCL_IC_INTEGER,
        [V850_IT_MOVHI_F06S]          = OCL_IC_INTEGER,
        [V850_IT_MULHI_F06S]          = OCL_IC_INTEGER,
        [V850_IT_SATSUBI_F06S]        = OCL_IC_INTEGER,

        //
        // format F06sa Insns
        //
        [V850_IT_JARL_F06SA]          = OCL_IC_BRANCH,

        //
        // format F06sb Insns
        //
        [V850_IT_JMP_F06SB]           = OCL_IC_BRANCH,

        //
        // format F06sc Insns
        //
        [V850_IT_JR_F06SC]            = OCL_IC_BRANCH,

        //
        // format F06u Insns
        //
        [V850_IT_ANDI_F06U]           = OCL_IC_INTEGER,
        [V850_IT_ORI_F06U]            = OCL_IC_INTEGER,
        [V850_IT_XORI_F06U]           = OCL_IC_INTEGER,

        //
        // format F06ua Insns
        //
        [V850_IT_MOV_F06UA]           = OCL_IC_INTEGER,

        //
        // format F06x Insns
        //
        [V850_IT_RIE_F06X]            = OCL_IC_SYSTEM,

        //
        // format F07cc Insns
        //
        [V850_IT_BCOND_F07CC]         = OCL_IC_BRANCH,

        //
        // format F07cc Insns
        //
        [V850_IT_LOOP_F07RI]          = OCL_IC_BRANCH,

        //
        // format F07c Insns
        //
        [V850_IT_LD_BU_F07C]          = OCL_IC_NOP,

        //
        // format F07la Insns
        //
        [V850_IT_LD_B_F07LA]          = OCL_IC_NOP,

        //
        // format F07lb Insns
        //
        [V850_IT_LD_H_F07LB]          = OCL_IC_NOP,
        [V850_IT_LD_HU_F07LB]         = OCL_IC_NOP,
        [V850_IT_LD_W_F07LB]          = OCL_IC_NOP,

        //
        // format F07sa Insns
        //
        [V850_IT_ST_B_F07SA]          = OCL_IC_NOP,

        //
        // format F07sb Insns
        //
        [V850_IT_ST_H_F07SB]          = OCL_IC_NOP,
        [V850_IT_ST_W_F07SB]          = OCL_IC_NOP,

        //
        // format fo7d
        //
        [V850_IT_LDL_W_F07D]          = OCL_IC_NOP,
        [V850_IT_STC_W_F07D]          = OCL_IC_NOP,

        //
        // format F07rrr
        //
        [V850_IT_ROTL_F07RRR]         = OCL_IC_INTEGER,

        //
        // format F07irr
        //
        [V850_IT_ROTL_F07IRR]         = OCL_IC_INTEGER,

        //
        // format F08 Insns
        //
        [V850_IT_CLR1_F08]            = OCL_IC_INTEGER,
        [V850_IT_NOT1_F08]            = OCL_IC_INTEGER,
        [V850_IT_SET1_F08]            = OCL_IC_INTEGER,
        [V850_IT_TST1_F08]            = OCL_IC_INTEGER,

        //
        // format F09 Insns
        //
        [V850_IT_SASF_F09]            = OCL_IC_INTEGER,
        [V850_IT_SETF_F09]            = OCL_IC_INTEGER,

        //
        // format F09rr Insns
        //
        [V850_IT_SAR_F09RR]           = OCL_IC_INTEGER,
        [V850_IT_SHL_F09RR]           = OCL_IC_INTEGER,
        [V850_IT_SHR_F09RR]           = OCL_IC_INTEGER,

        //
        // format F09rr2 Insns
        //
        [V850_IT_SCH0L_F09RR2]        = OCL_IC_INTEGER,
        [V850_IT_SCH0R_F09RR2]        = OCL_IC_INTEGER,
        [V850_IT_SCH1L_F09RR2]        = OCL_IC_INTEGER,
        [V850_IT_SCH1R_F09RR2]        = OCL_IC_INTEGER,

        //
        // format F09rs1 Insns
        //
        [V850_IT_LDSR_F09RS1_0]       = OCL_IC_SYSREG,
        [V850_IT_LDSR_F09RS1]         = OCL_IC_SYSREG,

        //
        // format F09rs2 Insns
        //
        [V850_IT_CLR1_F09RS2]         = OCL_IC_INTEGER,
        [V850_IT_NOT1_F09RS2]         = OCL_IC_INTEGER,
        [V850_IT_SET1_F09RS2]         = OCL_IC_INTEGER,
        [V850_IT_TST1_F09RS2]         = OCL_IC_INTEGER,

        //
        // format F09sr Insns
        //
        [V850_IT_STSR_F09SR_0]        = OCL_IC_SYSREG,
        [V850_IT_STSR_F09SR]          = OCL_IC_SYSREG,

        //
        // format F09rpwr Insns
        //
        [V850_IT_BINS_F09RPWR_0]      = OCL_IC_INTEGER,
        [V850_IT_BINS_F09RPWR_1]      = OCL_IC_INTEGER,
        [V850_IT_BINS_F09RPWR_2]      = OCL_IC_INTEGER,

        //
        // format F10a Insns
        //
        [V850_IT_CLL_F10]             = OCL_IC_ATOMIC,
        [V850_IT_SNOOZE_F10]          = OCL_IC_NOP,
        [V850_IT_CACHE_F10]           = OCL_IC_ICACHE,
        [V850_IT_CACHE_CHBII]         = OCL_IC_ICACHE,
        [V850_IT_CACHE_CIBII]         = OCL_IC_ICACHE,
        [V850_IT_CACHE_CFALI]         = OCL_IC_ICACHE,
        [V850_IT_CACHE_CISTI]         = OCL_IC_ICACHE,
        [V850_IT_CACHE_CILDI]         = OCL_IC_ICACHE,
        [V850_IT_PREF_F10]            = OCL_IC_ICACHE,
        [V850_IT_PREFI_F10]           = OCL_IC_ICACHE,

        //
        // format F10a Insns
        //
        [V850_IT_CTRET_F10A]          = OCL_IC_SYSTEM,
        [V850_IT_DBRET_F10A]          = OCL_IC_SYSTEM,
        [V850_IT_DI_F10A]             = OCL_IC_SYSTEM,
        [V850_IT_EI_F10A]             = OCL_IC_SYSTEM,
        [V850_IT_EIRET_F10A]          = OCL_IC_SYSTEM,
        [V850_IT_FERET_F10A]          = OCL_IC_SYSTEM,
        [V850_IT_HALT_F10A]           = OCL_IC_SYSTEM,
        [V850_IT_RETI_F10A]           = OCL_IC_SYSTEM,

        //
        // format F10b Insns
        //
        [V850_IT_TRAP_F10B]           = OCL_IC_SYSTEM,
        [V850_IT_SYSCALL_F10C]        = OCL_IC_SYSTEM,

        //
        // format F11 Insns
        //
        [V850_IT_DIV_F11]             = OCL_IC_DIVIDE,
        [V850_IT_DIVH_F11]            = OCL_IC_DIVIDE,
        [V850_IT_DIVHU_F11]           = OCL_IC_DIVIDE,
        [V850_IT_DIVQ_F11]            = OCL_IC_DIVIDE,
        [V850_IT_DIVQU_F11]           = OCL_IC_DIVIDE,
        [V850_IT_DIVU_F11]            = OCL_IC_DIVIDE,
        [V850_IT_MUL_F11]             = OCL_IC_MULTIPLY,
        [V850_IT_MULU_F11]            = OCL_IC_MULTIPLY,
        [V850_IT_SAR_F11]             = OCL_IC_INTEGER,
        [V850_IT_SATADD_F11]          = OCL_IC_INTEGER,
        [V850_IT_SATSUB_F11]          = OCL_IC_INTEGER,
        [V850_IT_SHL_F11]             = OCL_IC_INTEGER,
        [V850_IT_SHR_F11]             = OCL_IC_INTEGER,

        //
        // format F11a Insns
        //
        [V850_IT_MAC_F11A]            = OCL_IC_MULTIPLY,
        [V850_IT_MACU_F11A]           = OCL_IC_MULTIPLY,

        //
        // format F11b Insns
        //
        [V850_IT_ADF_F11B]            = OCL_IC_INTEGER,
        [V850_IT_CMOV_F11B]           = OCL_IC_INTEGER,
        [V850_IT_SBF_F11B]            = OCL_IC_INTEGER,

        //
        // format F11c Insns
        //
        [V850_IT_CAXI_F11C]           = OCL_IC_EXCLUSIVE,

        //
        // format F11d Insns
        //
        [V850_IT_JARL_F11D]           = OCL_IC_BRANCH,

        //
        // format F11 Insns
        //
        [V850_IT_PUSHSP_F11]          = OCL_IC_NOP,
        [V850_IT_POPSP_F11]           = OCL_IC_NOP,

        //
        // format F12a Insns
        //
        [V850_IT_CMOV_F12A]           = OCL_IC_INTEGER,

        //
        // format F12b Insns
        //
        [V850_IT_BSH_F12B]            = OCL_IC_INTEGER,
        [V850_IT_BSW_F12B]            = OCL_IC_INTEGER,
        [V850_IT_HSH_F12B]            = OCL_IC_INTEGER,
        [V850_IT_HSW_F12B]            = OCL_IC_INTEGER,

        //
        // format F12s Insns
        //
        [V850_IT_MUL_F12S]            = OCL_IC_MULTIPLY,

        //
        // format F12u Insns
        //
        [V850_IT_MULU_F12U]           = OCL_IC_MULTIPLY,

        //
        // format F13il1 Insns
        //
        [V850_IT_DISPOSE_F13IL1]      = OCL_IC_NOP,

        //
        // format F13il2 Insns
        //
        [V850_IT_DISPOSE_F13IL2]      = OCL_IC_NOP,

        //
        // format F13li Insns
        //
        [V850_IT_PREPARE_F13LI]       = OCL_IC_NOP,

        //
        // format F13li00 Insns
        //
        [V850_IT_PREPARE_F13LI00]     = OCL_IC_NOP,

        //
        // format F13li01 Insns
        //
        [V850_IT_PREPARE_F13LI01]     = OCL_IC_NOP,

        //
        // format F13li10 Insns
        //
        [V850_IT_PREPARE_F13LI10]     = OCL_IC_NOP,

        //
        // format F13li11 Insns
        //
        [V850_IT_PREPARE_F13LI11]     = OCL_IC_NOP,

        //
        // format FI Insns
        //
        [V850_IT_ADDF_S_FI]           = OCL_IC_FLOAT,
        [V850_IT_DIVF_S_FI]           = OCL_IC_FLOAT,
        [V850_IT_MAXF_S_FI]           = OCL_IC_FLOAT,
        [V850_IT_MINF_S_FI]           = OCL_IC_FLOAT,
        [V850_IT_MULF_S_FI]           = OCL_IC_FLOAT,
        [V850_IT_SUBF_S_FI]           = OCL_IC_FLOAT,

        [V850_IT_FMAF_S_FI]           = OCL_IC_FMA,
        [V850_IT_FMSF_S_FI]           = OCL_IC_FMA,
        [V850_IT_FNMAF_S_FI]          = OCL_IC_FMA,
        [V850_IT_FNMSF_S_FI]          = OCL_IC_FMA,

        //
        // format FID Insns
        //
        [V850_IT_ADDF_D_FID]          = OCL_IC_FLOAT,
        [V850_IT_DIVF_D_FID]          = OCL_IC_FLOAT,
        [V850_IT_MAXF_D_FID]          = OCL_IC_FLOAT,
        [V850_IT_MINF_D_FID]          = OCL_IC_FLOAT,
        [V850_IT_MULF_D_FID]          = OCL_IC_FLOAT,
        [V850_IT_SUBF_D_FID]          = OCL_IC_FLOAT,

        //
        // format FIDSr2r3 Insns
        //
        [V850_IT_CEILF_DW_FIDSR2R3]   = OCL_IC_FLOAT,
        [V850_IT_CVTF_DS_FIDSR2R3]    = OCL_IC_FLOAT,
        [V850_IT_CVTF_DUW_FIDSR2R3]   = OCL_IC_FLOAT,
        [V850_IT_CVTF_DW_FIDSR2R3]    = OCL_IC_FLOAT,
        [V850_IT_CVTF_LS_FIDSR2R3]    = OCL_IC_FLOAT,
        [V850_IT_CVTF_ULS_FIDSR2R3]   = OCL_IC_FLOAT,
        [V850_IT_FLOORF_DW_FIDSR2R3]  = OCL_IC_FLOAT,
        [V850_IT_TRNCF_DW_FIDSR2R3]   = OCL_IC_FLOAT,

        //
        // CVT FI
        //
        [V850_IT_CVTF_HS_FI]          = OCL_IC_FLOAT,
        [V850_IT_CVTF_SH_FI]          = OCL_IC_FLOAT,

        //
        // format FIDcond Insns
        //
        [V850_IT_CMPF_D_FIDCOND]      = OCL_IC_FLOAT,

        //
        // format FIDfff Insns
        //
        [V850_IT_CMOVF_D_FIDFFF]      = OCL_IC_FLOAT,

        //
        // format FIDr2r3 Insns
        //
        [V850_IT_ABSF_D_FIDR2R3]      = OCL_IC_FLOAT,
        [V850_IT_CEILF_DL_FIDR2R3]    = OCL_IC_FLOAT,
        [V850_IT_CEILF_DUL_FIDR2R3]   = OCL_IC_FLOAT,
        [V850_IT_CEILF_DUW_FIDR2R3]   = OCL_IC_FLOAT,
        [V850_IT_CVTF_DL_FIDR2R3]     = OCL_IC_FLOAT,
        [V850_IT_CVTF_DUL_FIDR2R3]    = OCL_IC_FLOAT,
        [V850_IT_CVTF_ULD_FIDR2R3]    = OCL_IC_FLOAT,
        [V850_IT_FLOORF_DL_FIDR2R3]   = OCL_IC_FLOAT,
        [V850_IT_FLOORF_DUL_FIDR2R3]  = OCL_IC_FLOAT,
        [V850_IT_FLOORF_DUW_FIDR2R3]  = OCL_IC_FLOAT,
        [V850_IT_NEGF_D_FIDR2R3]      = OCL_IC_FLOAT,
        [V850_IT_RECIPF_D_FIDR2R3]    = OCL_IC_FLOAT,
        [V850_IT_RSQRTF_D_FIDR2R3]    = OCL_IC_FLOAT,
        [V850_IT_SQRTF_D_FIDR2R3]     = OCL_IC_FLOAT,
        [V850_IT_TRNCF_DL_FIDR2R3]    = OCL_IC_FLOAT,
        [V850_IT_TRNCF_DUL_FIDR2R3]   = OCL_IC_FLOAT,
        [V850_IT_TRNCF_DUW_FIDR2R3]   = OCL_IC_FLOAT,

        //
        // format FII Insns
        //
        [V850_IT_ABSF_S_FII]          = OCL_IC_FLOAT,
        [V850_IT_CVT_SW_FII]          = OCL_IC_FLOAT,
        [V850_IT_CVT_WS_FII]          = OCL_IC_FLOAT,
        [V850_IT_NEGF_S_FII]          = OCL_IC_FLOAT,
        [V850_IT_TRNC_SW_FII]         = OCL_IC_FLOAT,

        //
        // format FIS Insns
        //
        [V850_IT_ADDF_S_FIS]          = OCL_IC_FLOAT,
        [V850_IT_DIVF_S_FIS]          = OCL_IC_FLOAT,
        [V850_IT_MAXF_S_FIS]          = OCL_IC_FLOAT,
        [V850_IT_MINF_S_FIS]          = OCL_IC_FLOAT,
        [V850_IT_MULF_S_FIS]          = OCL_IC_FLOAT,
        [V850_IT_SUBF_S_FIS]          = OCL_IC_FLOAT,

        //
        // format FISDr2r3 Insns
        //
        [V850_IT_CEILF_SL_FISDR2R3]   = OCL_IC_FLOAT,
        [V850_IT_CEILF_SUL_FISDR2R3]  = OCL_IC_FLOAT,
        [V850_IT_CVTF_SD_FISDR2R3]    = OCL_IC_FLOAT,
        [V850_IT_CVTF_SL_FISDR2R3]    = OCL_IC_FLOAT,
        [V850_IT_CVTF_SUL_FISDR2R3]   = OCL_IC_FLOAT,
        [V850_IT_CVTF_UWD_FISDR2R3]   = OCL_IC_FLOAT,
        [V850_IT_CVTF_WD_FISDR2R3]    = OCL_IC_FLOAT,
        [V850_IT_FLOORF_SL_FISDR2R3]  = OCL_IC_FLOAT,
        [V850_IT_FLOORF_SUL_FISDR2R3] = OCL_IC_FLOAT,
        [V850_IT_TRNCF_SL_FISDR2R3]   = OCL_IC_FLOAT,
        [V850_IT_TRNCF_SUL_FISDR2R3]  = OCL_IC_FLOAT,

        //
        // format FISa Insns
        //
        [V850_IT_MADDF_S_FISA]        = OCL_IC_FMA,
        [V850_IT_MSUBF_S_FISA]        = OCL_IC_FMA,
        [V850_IT_NMADDF_S_FISA]       = OCL_IC_FMA,
        [V850_IT_NMSUBF_S_FISA]       = OCL_IC_FMA,

        //
        // format FIScond Insns
        //
        [V850_IT_CMPF_S_FISCOND]      = OCL_IC_FLOAT,

        //
        // format FISfff Insns
        //
        [V850_IT_CMOVF_S_FISFFF]      = OCL_IC_FLOAT,

        //
        // format FISr2r3 Insns
        //
        [V850_IT_ABSF_S_FISR2R3]      = OCL_IC_FLOAT,
        [V850_IT_CEILF_SUW_FISR2R3]   = OCL_IC_FLOAT,
        [V850_IT_CEILF_SW_FISR2R3]    = OCL_IC_FLOAT,
        [V850_IT_CVTF_LD_FISR2R3]     = OCL_IC_FLOAT,
        [V850_IT_CVTF_SUW_FISR2R3]    = OCL_IC_FLOAT,
        [V850_IT_CVTF_SW_FISR2R3]     = OCL_IC_FLOAT,
        [V850_IT_CVTF_UWS_FISR2R3]    = OCL_IC_FLOAT,
        [V850_IT_CVTF_WS_FISR2R3]     = OCL_IC_FLOAT,
        [V850_IT_FLOORF_SUW_FISR2R3]  = OCL_IC_FLOAT,
        [V850_IT_FLOORF_SW_FISR2R3]   = OCL_IC_FLOAT,
        [V850_IT_NEGF_S_FISR2R3]      = OCL_IC_FLOAT,
        [V850_IT_RECIPF_S_FISR2R3]    = OCL_IC_RECIP,
        [V850_IT_RSQRTF_S_FISR2R3]    = OCL_IC_SQRT,
        [V850_IT_SQRTF_S_FISR2R3]     = OCL_IC_SQRT,
        [V850_IT_TRNCF_SUW_FISR2R3]   = OCL_IC_FLOAT,
        [V850_IT_TRNCF_SW_FISR2R3]    = OCL_IC_FLOAT,

        //
        // format FIV Insns
        //
        [V850_IT_TRFF_FIV]            = OCL_IC_FLOAT,

        //
        // format FIVr2a Insns
        //
        [V850_IT_LDFF_FIVR2A]         = OCL_IC_FLOAT,

        //
        // format FIVr2b Insns
        //
        [V850_IT_LDFC_FIVR2B]         = OCL_IC_FLOAT,

        //
        // format FIVr3a Insns
        //
        [V850_IT_STFF_FIVR3A]         = OCL_IC_FLOAT,

        //
        // format FIVr3b Insns
        //
        [V850_IT_STFC_FIVR3B]         = OCL_IC_FLOAT,

        //
        // format FIfff Insns
        //
        [V850_IT_TRFSR_FIFFF]         = OCL_IC_INTEGER,

        //
        // format F14
        //
        [V850_IT_LD_DW_F14]           = OCL_IC_NOP,
        [V850_IT_ST_DW_F14]           = OCL_IC_NOP,
        [V850_IT_LD_B_F14]            = OCL_IC_NOP,
        [V850_IT_LD_BU_F14]           = OCL_IC_NOP,
        [V850_IT_LD_H_F14]            = OCL_IC_NOP,
        [V850_IT_LD_HU_F14]           = OCL_IC_NOP,
        [V850_IT_LD_W_F14]            = OCL_IC_NOP,
        [V850_IT_ST_B_F14]            = OCL_IC_NOP,
        [V850_IT_ST_H_F14]            = OCL_IC_NOP,
        [V850_IT_ST_W_F14]            = OCL_IC_NOP,

        //
        // Drop through catch for instruction widths 16 32 48 64
        //
        [V850_IT_INSTR16]             = OCL_IC_NONE,
        [V850_IT_INSTR32]             = OCL_IC_NONE,
        [V850_IT_INSTR48]             = OCL_IC_NONE,
        [V850_IT_INSTR64]             = OCL_IC_NONE,

};

//
// Initialization of the info structure per instruction
//
void v850GenInstructionInfo (v850InstructionInfoP info) {
    info->opcode  = opcode[info->type];
    info->class   = classes[info->type];

    switch (info->type) {
        case V850_IT_ADD_F01:
        case V850_IT_AND_F01:
        case V850_IT_CMP_F01:
        case V850_IT_DIVH_F01:
        case V850_IT_MOV_F01:
        case V850_IT_MULH_F01:
        case V850_IT_NOT_F01:
        case V850_IT_OR_F01:
        case V850_IT_SATADD_F01:
        case V850_IT_SATSUB_F01:
        case V850_IT_SATSUBR_F01:
        case V850_IT_SUB_F01:
        case V850_IT_SUBR_F01:
        case V850_IT_TST_F01:
        case V850_IT_XOR_F01:
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case V850_IT_CLL_F10:
        case V850_IT_SNOOZE_F10:
            break;

        case V850_IT_CACHE_F10:
        case V850_IT_CACHE_CHBII:
        case V850_IT_CACHE_CIBII:
        case V850_IT_CACHE_CFALI:
        case V850_IT_CACHE_CISTI:
        case V850_IT_CACHE_CILDI:
        case V850_IT_PREF_F10:
        case V850_IT_PREFI_F10:
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            break;

        case V850_IT_DBTRAP_F01A:
        case V850_IT_NOP_F01A:
        case V850_IT_RIE_F01A:
        case V850_IT_RMTRAP_F01A:
        case V850_IT_SYNCM_F01A:
        case V850_IT_SYNCP_F01A:
        case V850_IT_SYNCE_F01A:
        case V850_IT_SYNCI_F01A:
            break;

        case V850_IT_JMP_F01B:
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            break;

        case V850_IT_SXB_F01C:
        case V850_IT_SXH_F01C:
        case V850_IT_ZXB_F01C:
        case V850_IT_ZXH_F01C:
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            break;

        case V850_IT_SWITCH_F01D:
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            break;

        case V850_IT_FETRAP_F01E:
            info->uimm = VECINDEX(info->instruction,14,11,0); // 14:11
            break;

        case V850_IT_CALLT_F02B:
            info->uimm = VECINDEX(info->instruction,5,0,0); // 5:0
            break;

        case V850_IT_ADD_F02S:
        case V850_IT_CMP_F02S:
        case V850_IT_MOV_F02S:
        case V850_IT_MULH_F02S:
        case V850_IT_SATADD_F02S:
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->simm = VECINDEX(info->instruction,4,0,0); // 4:0
            info->simm = SEXTEND(info->simm,4);
            break;

        case V850_IT_SAR_F02U:
        case V850_IT_SHL_F02U:
        case V850_IT_SHR_F02U:
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->uimm = VECINDEX(info->instruction,4,0,0); // 4:0
            break;

        case V850_IT_BCOND_F03:
            info->cond     = VECINDEX(info->instruction,3,0,0); // 3:0
            info->sdisp    = VECINDEX(info->instruction,15,11,3) | VECINDEX(info->instruction,6,4,0); // 15:11 6:4
            info->sdisp    = SHIFTL(info->sdisp,1);
            info->sdisp    = SEXTEND(info->sdisp,8);
            info->targetPC = info->thisPC + info->sdisp;
            break;

        case V850_IT_SLD_BU_F04DB:
            info->reg2    = VECINDEX(info->instruction,15,11,0); // 15:11
            info->udisp   = VECINDEX(info->instruction,3,0,0); // 3:0
            break;

        case V850_IT_SLD_HU_F04DH:
            info->reg2  = VECINDEX(info->instruction,15,11,0); // 15:11
            info->udisp = VECINDEX(info->instruction,3,0,0); // 3:0
            info->udisp = SHIFTL(info->udisp,1);
            break;

        case V850_IT_SLD_B_F04LA:
            info->reg2    = VECINDEX(info->instruction,15,11,0); // 15:11
            info->udisp   = VECINDEX(info->instruction,6,0,0); // 6:0
            break;

        case V850_IT_SLD_H_F04LB:
            info->reg2    = VECINDEX(info->instruction,15,11,0); // 15:11
            info->udisp   = VECINDEX(info->instruction,6,0,0); // 6:0
            info->udisp   = SHIFTL(info->udisp,1);
            break;

        case V850_IT_SLD_W_F04LC:
            info->reg2    = VECINDEX(info->instruction,15,11,0); // 15:11
            info->udisp   = VECINDEX(info->instruction,6,1,0); // 6:1
            info->udisp   = SHIFTL(info->udisp,2);
            break;

        case V850_IT_SST_B_F04SA:
            info->reg2    = VECINDEX(info->instruction,15,11,0); // 15:11
            info->udisp   = VECINDEX(info->instruction,6,0,0); // 6:0
            break;

        case V850_IT_SST_H_F04SB:
            info->reg2    = VECINDEX(info->instruction,15,11,0); // 15:11
            info->udisp   = VECINDEX(info->instruction,6,0,0); // 6:0
            info->udisp   = SHIFTL(info->udisp,1);
            break;

        case V850_IT_SST_W_F04SC:
            info->reg2    = VECINDEX(info->instruction,15,11,0); // 15:11
            info->udisp   = VECINDEX(info->instruction,6,1,0); // 6:1
            info->udisp   = SHIFTL(info->udisp,2);
            break;

        case V850_IT_JARL_F05A:
            info->b16   = VECINDEX(info->instruction,16,16,0); // 16
            info->reg2  = VECINDEX(info->instruction,15,11,0); // 15:11
            info->sdisp = VECINDEX(info->instruction,5,0,15) | VECINDEX(info->instruction,31,17,0); // 5:0 31:17
            info->sdisp = SHIFTL(info->sdisp,1);
            info->sdisp = SEXTEND(info->sdisp,21);
            info->targetPC = info->thisPC + info->sdisp;
            break;

        case V850_IT_JR_F05B:
            info->b16      = VECINDEX(info->instruction,16,16,0); // 16
            info->sdisp    = VECINDEX(info->instruction,5,0,15) | VECINDEX(info->instruction,31,17,0); // 5:0 31:17
            info->sdisp    = SHIFTL(info->sdisp,1);
            info->sdisp    = SEXTEND(info->sdisp,21);
            info->targetPC = info->thisPC + info->sdisp;
            break;

        case V850_IT_ADDI_F06S:
        case V850_IT_MOVEA_F06S:
        case V850_IT_MOVHI_F06S:
        case V850_IT_MULHI_F06S:
        case V850_IT_SATSUBI_F06S:
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->simm = VECINDEX(info->instruction,31,16,0); // 31:16
            info->simm = SEXTEND(info->simm,15);
            break;

        case V850_IT_JARL_F06SA:
            info->b16      = VECINDEX(info->instruction,16,16,0); // 16
            info->reg1     = VECINDEX(info->instruction,4,0,0); // 4:0
            info->sdisp    = VECINDEX(info->instruction,47,17,0); // 47:17
            info->sdisp    = SHIFTL(info->sdisp,1);
            info->sdisp    = SEXTEND(info->sdisp,31);
            info->targetPC = info->thisPC + info->sdisp;
            break;

        case V850_IT_JMP_F06SB:
            info->b16      = VECINDEX(info->instruction,16,16,0); // 16
            info->reg1     = VECINDEX(info->instruction,4,0,0); // 4:0
            info->sdisp    = VECINDEX(info->instruction,47,17,0); // 47:17
            info->sdisp    = SHIFTL(info->sdisp,1);
            info->sdisp    = SEXTEND(info->sdisp,31);
            info->targetPC = info->thisPC + info->sdisp;

            break;

        case V850_IT_JR_F06SC:
            info->b16      = VECINDEX(info->instruction,16,16,0); // 16
            info->sdisp    = VECINDEX(info->instruction,47,17,0); // 47:17
            info->sdisp    = SHIFTL(info->sdisp,1);
            info->sdisp    = SEXTEND(info->sdisp,31);
            info->targetPC = info->thisPC + info->sdisp;
            break;

        case V850_IT_ANDI_F06U:
        case V850_IT_ORI_F06U:
        case V850_IT_XORI_F06U:
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->uimm = VECINDEX(info->instruction,31,16,0); // 31:16
            break;

        case V850_IT_MOV_F06UA:
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->uimm = VECINDEX(info->instruction,47,16,0); // 47:16
            break;

        case V850_IT_RIE_F06X:
            break;

        case V850_IT_BCOND_F07CC:
            info->cond     = VECINDEX(info->instruction,3,0,0); // 3:0
            info->sdisp    = VECINDEX(info->instruction,31,17,1); // 31:17
            info->sdisp    = SEXTEND(info->sdisp,15);
            info->targetPC = info->thisPC + info->sdisp;
            break;

        case V850_IT_LD_BU_F07C:
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->sdisp = VECINDEX(info->instruction,31,17,1) | VECINDEX(info->instruction,5,5,0); // 31:17 5
            info->sdisp = SEXTEND(info->sdisp,15);
            break;

        case V850_IT_LD_B_F07LA:
            info->reg1      = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2      = VECINDEX(info->instruction,15,11,0); // 15:11
            info->sdisp     = VECINDEX(info->instruction,31,16,0); // 31:16
            info->sdisp     = SEXTEND(info->sdisp,15);
            break;

        case V850_IT_LD_H_F07LB:
        case V850_IT_LD_HU_F07LB:
        case V850_IT_LD_W_F07LB:
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->sdisp = VECINDEX(info->instruction,31,17,0); // 31:17
            info->sdisp = SHIFTL(info->sdisp,1);
            info->sdisp = SEXTEND(info->sdisp,15);
            break;

        case V850_IT_ST_B_F07SA:
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->sdisp = VECINDEX(info->instruction,31,16,0); // 31:16
            info->sdisp = SEXTEND(info->sdisp,15);
            break;

        case V850_IT_ST_H_F07SB:
        case V850_IT_ST_W_F07SB:
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->sdisp = VECINDEX(info->instruction,31,17,0); // 31:17
            info->sdisp = SHIFTL(info->sdisp,1);
            info->sdisp = SEXTEND(info->sdisp,15);
            break;

        case V850_IT_CLR1_F08:
        case V850_IT_NOT1_F08:
        case V850_IT_SET1_F08:
        case V850_IT_TST1_F08:
            info->bit = VECINDEX(info->instruction,13,11,0); // 13:11
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->sdisp = VECINDEX(info->instruction,31,16,0); // 31:16
            info->sdisp = SEXTEND(info->sdisp,15);
            break;

        case V850_IT_SASF_F09:
        case V850_IT_SETF_F09:
            info->cccc = VECINDEX(info->instruction,3,0,0); // 3:0
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case V850_IT_SAR_F09RR:
        case V850_IT_SHL_F09RR:
        case V850_IT_SHR_F09RR:
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case V850_IT_SCH0L_F09RR2:
        case V850_IT_SCH0R_F09RR2:
        case V850_IT_SCH1L_F09RR2:
        case V850_IT_SCH1R_F09RR2:
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->reg3 = VECINDEX(info->instruction,31,27,0); // 31:27
            break;

        case V850_IT_LDSR_F09RS1_0:
        case V850_IT_LDSR_F09RS1:
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->reg3 = VECINDEX(info->instruction,31,27,0); // 31:27
            break;

        case V850_IT_CLR1_F09RS2:
        case V850_IT_NOT1_F09RS2:
        case V850_IT_SET1_F09RS2:
        case V850_IT_TST1_F09RS2:
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case V850_IT_STSR_F09SR_0:
        case V850_IT_STSR_F09SR:
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->reg3 = VECINDEX(info->instruction,31,27,0); // 31:27
            break;

        case V850_IT_CTRET_F10A:
        case V850_IT_DBRET_F10A:
        case V850_IT_DI_F10A:
        case V850_IT_EI_F10A:
        case V850_IT_EIRET_F10A:
        case V850_IT_FERET_F10A:
        case V850_IT_HALT_F10A:
        case V850_IT_RETI_F10A:
            info->b16 = VECINDEX(info->instruction,16,16,0); // 16
            break;

        case V850_IT_TRAP_F10B:
            info->b16 = VECINDEX(info->instruction,16,16,0); // 16
            info->uimm = VECINDEX(info->instruction,4,0,0); // 4:0
            break;

        case V850_IT_SYSCALL_F10C:
            info->uimm = VECINDEX(info->instruction,29,27,5) | VECINDEX(info->instruction,4,0,0); // 29:27,4:0
            break;

        case V850_IT_PUSHSP_F11:
        case V850_IT_POPSP_F11:
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg3 = VECINDEX(info->instruction,31,27,0); // 31:27
            break;

        case V850_IT_DIV_F11:
        case V850_IT_DIVH_F11:
        case V850_IT_DIVHU_F11:
        case V850_IT_DIVQ_F11:
        case V850_IT_DIVQU_F11:
        case V850_IT_DIVU_F11:
        case V850_IT_MUL_F11:
        case V850_IT_MULU_F11:
        case V850_IT_SAR_F11:
        case V850_IT_SATADD_F11:
        case V850_IT_SATSUB_F11:
        case V850_IT_SHL_F11:
        case V850_IT_SHR_F11:
            info->b16 = VECINDEX(info->instruction,16,16,0); // 16
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->reg3 = VECINDEX(info->instruction,31,27,0); // 31:27
            break;

        case V850_IT_MAC_F11A:
        case V850_IT_MACU_F11A:
            info->b16 = VECINDEX(info->instruction,16,16,0); // 16
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->reg3 = VECINDEX(info->instruction,31,28,0); // 31:28
            info->reg3 = SHIFTL(info->reg3,1);
            info->reg4 = VECINDEX(info->instruction,20,17,0); // 20:17
            info->reg4 = SHIFTL(info->reg4,1);
            break;

        case V850_IT_ADF_F11B:
        case V850_IT_CMOV_F11B:
        case V850_IT_SBF_F11B:
            info->b16 = VECINDEX(info->instruction,16,16,0); // 16
            info->cccc = VECINDEX(info->instruction,20,17,0); // 20:17
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->reg3 = VECINDEX(info->instruction,31,27,0); // 31:27
            break;

        case V850_IT_CAXI_F11C:
            info->b16 = VECINDEX(info->instruction,16,16,0); // 16
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->reg3 = VECINDEX(info->instruction,31,27,0); // 31:27
            break;

        case V850_IT_JARL_F11D:
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg3 = VECINDEX(info->instruction,31,27,0); // 31:27
            break;

        case V850_IT_CMOV_F12A:
            info->b16 = VECINDEX(info->instruction,16,16,0); // 16
            info->cccc = VECINDEX(info->instruction,20,17,0); // 20:17
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->reg3 = VECINDEX(info->instruction,31,27,0); // 31:27
            info->simm = VECINDEX(info->instruction,4,0,0); // 4:0
            info->simm = SEXTEND(info->simm,4);
            break;

        case V850_IT_BSH_F12B:
        case V850_IT_BSW_F12B:
        case V850_IT_HSH_F12B:
        case V850_IT_HSW_F12B:
            info->b16 = VECINDEX(info->instruction,16,16,0); // 16
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->reg3 = VECINDEX(info->instruction,31,27,0); // 31:27
            break;

        case V850_IT_MUL_F12S:
            info->b16 = VECINDEX(info->instruction,16,16,0); // 16
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->reg3 = VECINDEX(info->instruction,31,27,0); // 31:27
            info->simm = VECINDEX(info->instruction,21,18,5) | VECINDEX(info->instruction,4,0,0); // 21:18 4:0
            info->simm = SEXTEND(info->simm,8);
            break;

        case V850_IT_MULU_F12U:
            info->b16 = VECINDEX(info->instruction,16,16,0); // 16
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->reg3 = VECINDEX(info->instruction,31,27,0); // 31:27
            info->uimm = VECINDEX(info->instruction,21,18,5) | VECINDEX(info->instruction,4,0,0); // 21:18 4:0
            break;

        case V850_IT_DISPOSE_F13IL1:
            info->list12 = VECINDEX(info->instruction,21,21,11) | VECINDEX(info->instruction,0,0,10) | VECINDEX(info->instruction,22,22,9) | VECINDEX(info->instruction,23,23,8) | VECINDEX(info->instruction,28,28,7) | VECINDEX(info->instruction,29,29,6) | VECINDEX(info->instruction,30,30,5) | VECINDEX(info->instruction,31,31,4) | VECINDEX(info->instruction,24,24,3) | VECINDEX(info->instruction,25,25,2) | VECINDEX(info->instruction,26,26,1) | VECINDEX(info->instruction,27,27,0); // 21 0 22 23 28 29 30 31 24 25 26 27
            info->uimm5 = VECINDEX(info->instruction,5,1,0); // 5:1
            break;

        case V850_IT_DISPOSE_F13IL2:
            info->list12 = VECINDEX(info->instruction,21,21,11) | VECINDEX(info->instruction,0,0,10) | VECINDEX(info->instruction,22,22,9) | VECINDEX(info->instruction,23,23,8) | VECINDEX(info->instruction,28,28,7) | VECINDEX(info->instruction,29,29,6) | VECINDEX(info->instruction,30,30,5) | VECINDEX(info->instruction,31,31,4) | VECINDEX(info->instruction,24,24,3) | VECINDEX(info->instruction,25,25,2) | VECINDEX(info->instruction,26,26,1) | VECINDEX(info->instruction,27,27,0); // 21 0 22 23 28 29 30 31 24 25 26 27
            info->reg1 = VECINDEX(info->instruction,20,16,0); // 20:16
            info->uimm5 = VECINDEX(info->instruction,5,1,0); // 5:1
            break;

        case V850_IT_PREPARE_F13LI:
            info->list12 = VECINDEX(info->instruction,21,21,11) | VECINDEX(info->instruction,0,0,10) | VECINDEX(info->instruction,22,22,9) | VECINDEX(info->instruction,23,23,8) | VECINDEX(info->instruction,28,28,7) | VECINDEX(info->instruction,29,29,6) | VECINDEX(info->instruction,30,30,5) | VECINDEX(info->instruction,31,31,4) | VECINDEX(info->instruction,24,24,3) | VECINDEX(info->instruction,25,25,2) | VECINDEX(info->instruction,26,26,1) | VECINDEX(info->instruction,27,27,0); // 21 0 22 23 28 29 30 31 24 25 26 27
            info->uimm5 = VECINDEX(info->instruction,5,1,0); // 5:1
            break;

        case V850_IT_PREPARE_F13LI00:
            info->list12 = VECINDEX(info->instruction,21,21,11) | VECINDEX(info->instruction,0,0,10) | VECINDEX(info->instruction,22,22,9) | VECINDEX(info->instruction,23,23,8) | VECINDEX(info->instruction,28,28,7) | VECINDEX(info->instruction,29,29,6) | VECINDEX(info->instruction,30,30,5) | VECINDEX(info->instruction,31,31,4) | VECINDEX(info->instruction,24,24,3) | VECINDEX(info->instruction,25,25,2) | VECINDEX(info->instruction,26,26,1) | VECINDEX(info->instruction,27,27,0); // 21 0 22 23 28 29 30 31 24 25 26 27
            info->uimm5 = VECINDEX(info->instruction,5,1,0); // 5:1
            break;

        case V850_IT_PREPARE_F13LI01:
            info->list12 = VECINDEX(info->instruction,21,21,11) | VECINDEX(info->instruction,0,0,10) | VECINDEX(info->instruction,22,22,9) | VECINDEX(info->instruction,23,23,8) | VECINDEX(info->instruction,28,28,7) | VECINDEX(info->instruction,29,29,6) | VECINDEX(info->instruction,30,30,5) | VECINDEX(info->instruction,31,31,4) | VECINDEX(info->instruction,24,24,3) | VECINDEX(info->instruction,25,25,2) | VECINDEX(info->instruction,26,26,1) | VECINDEX(info->instruction,27,27,0); // 21 0 22 23 28 29 30 31 24 25 26 27
            info->simm = VECINDEX(info->instruction,47,32,0); // 47:32
            info->simm = SEXTEND(info->simm,15);
            info->uimm5 = VECINDEX(info->instruction,5,1,0); // 5:1
            break;

        case V850_IT_PREPARE_F13LI10:
            info->list12 = VECINDEX(info->instruction,21,21,11) | VECINDEX(info->instruction,0,0,10) | VECINDEX(info->instruction,22,22,9) | VECINDEX(info->instruction,23,23,8) | VECINDEX(info->instruction,28,28,7) | VECINDEX(info->instruction,29,29,6) | VECINDEX(info->instruction,30,30,5) | VECINDEX(info->instruction,31,31,4) | VECINDEX(info->instruction,24,24,3) | VECINDEX(info->instruction,25,25,2) | VECINDEX(info->instruction,26,26,1) | VECINDEX(info->instruction,27,27,0); // 21 0 22 23 28 29 30 31 24 25 26 27
            info->simm = VECINDEX(info->instruction,47,32,0); // 47:32
            info->simm = SHIFTL(info->simm,16);
            info->simm = SEXTEND(info->simm,31);
            info->uimm5 = VECINDEX(info->instruction,5,1,0); // 5:1
            break;

        case V850_IT_PREPARE_F13LI11:
            info->list12 = VECINDEX(info->instruction,0,0,11) | VECINDEX(info->instruction,31,21,0); // 0 31:21
            info->simm = VECINDEX(info->instruction,63,32,0); // 63:32
            info->simm = SEXTEND(info->simm,31);
            info->uimm5 = VECINDEX(info->instruction,5,1,0); // 5:1
            break;

        case V850_IT_ADDF_S_FI:
        case V850_IT_DIVF_S_FI:
        case V850_IT_MAXF_S_FI:
        case V850_IT_MINF_S_FI:
        case V850_IT_MULF_S_FI:
        case V850_IT_SUBF_S_FI:
        case V850_IT_FMAF_S_FI:
        case V850_IT_FMSF_S_FI:
        case V850_IT_FNMAF_S_FI:
        case V850_IT_FNMSF_S_FI:
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->reg3 = VECINDEX(info->instruction,31,27,0); // 31:27
            break;

        case V850_IT_ADDF_D_FID:
        case V850_IT_DIVF_D_FID:
        case V850_IT_MAXF_D_FID:
        case V850_IT_MINF_D_FID:
        case V850_IT_MULF_D_FID:
        case V850_IT_SUBF_D_FID:
            info->b11 = VECINDEX(info->instruction,11,11,0); // 11
            info->b16 = VECINDEX(info->instruction,16,16,0); // 16
            info->b26 = VECINDEX(info->instruction,27,26,0); // 27:26
            info->reg1 = VECINDEX(info->instruction,4,1,0); // 4:1
            info->reg1 = SHIFTL(info->reg1,1);
            info->reg2 = VECINDEX(info->instruction,15,12,0); // 15:12
            info->reg2 = SHIFTL(info->reg2,1);
            info->reg3 = VECINDEX(info->instruction,31,28,0); // 31:28
            info->reg3 = SHIFTL(info->reg3,1);
            break;

        case V850_IT_CEILF_DW_FIDSR2R3:
        case V850_IT_CVTF_DS_FIDSR2R3:
        case V850_IT_CVTF_DUW_FIDSR2R3:
        case V850_IT_CVTF_DW_FIDSR2R3:
        case V850_IT_CVTF_LS_FIDSR2R3:
        case V850_IT_CVTF_ULS_FIDSR2R3:
        case V850_IT_FLOORF_DW_FIDSR2R3:
        case V850_IT_TRNCF_DW_FIDSR2R3:
            info->b11 = VECINDEX(info->instruction,11,11,0); // 11
            info->b16 = VECINDEX(info->instruction,16,16,0); // 16
            info->b26 = VECINDEX(info->instruction,26,26,0); // 26
            info->reg2 = VECINDEX(info->instruction,15,12,0); // 15:12
            info->reg2 = SHIFTL(info->reg2,1);
            info->reg3 = VECINDEX(info->instruction,31,27,0); // 31:27
            break;

        case V850_IT_CVTF_HS_FI:
        case V850_IT_CVTF_SH_FI:
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:12
            info->reg3 = VECINDEX(info->instruction,31,27,0); // 31:27
            break;

        case V850_IT_CMPF_D_FIDCOND:
            info->b11 = VECINDEX(info->instruction,11,11,0); // 11
            info->b16 = VECINDEX(info->instruction,16,16,0); // 16
            info->b20 = VECINDEX(info->instruction,20,20,0); // 20
            info->b26 = VECINDEX(info->instruction,26,26,0); // 26
            info->b31 = VECINDEX(info->instruction,31,31,0); // 31
            info->cond = VECINDEX(info->instruction,30,27,0); // 30:27
            info->fff = VECINDEX(info->instruction,19,17,0); // 19:17
            info->reg1 = VECINDEX(info->instruction,4,1,0); // 4:1
            info->reg1 = SHIFTL(info->reg1,1);
            info->reg2 = VECINDEX(info->instruction,15,12,0); // 15:12
            info->reg2 = SHIFTL(info->reg2,1);
            break;

        case V850_IT_CMOVF_D_FIDFFF:
            info->b11 = VECINDEX(info->instruction,11,11,0); // 11
            info->b16 = VECINDEX(info->instruction,16,16,0); // 16
            info->b20 = VECINDEX(info->instruction,20,20,0); // 20
            info->b26 = VECINDEX(info->instruction,27,26,0); // 27:26
            info->fff = VECINDEX(info->instruction,19,17,0); // 19:17
            info->reg1 = VECINDEX(info->instruction,4,1,0); // 4:1
            info->reg1 = SHIFTL(info->reg1,1);
            info->reg2 = VECINDEX(info->instruction,15,12,0); // 15:12
            info->reg2 = SHIFTL(info->reg2,1);
            info->reg3 = VECINDEX(info->instruction,31,28,0); // 31:28
            info->reg3 = SHIFTL(info->reg3,1);
            break;

        case V850_IT_ABSF_D_FIDR2R3:
        case V850_IT_CEILF_DL_FIDR2R3:
        case V850_IT_CEILF_DUL_FIDR2R3:
        case V850_IT_CEILF_DUW_FIDR2R3:
        case V850_IT_CVTF_DL_FIDR2R3:
        case V850_IT_CVTF_DUL_FIDR2R3:
        case V850_IT_CVTF_ULD_FIDR2R3:
        case V850_IT_FLOORF_DL_FIDR2R3:
        case V850_IT_FLOORF_DUL_FIDR2R3:
        case V850_IT_FLOORF_DUW_FIDR2R3:
        case V850_IT_NEGF_D_FIDR2R3:
        case V850_IT_RECIPF_D_FIDR2R3:
        case V850_IT_RSQRTF_D_FIDR2R3:
        case V850_IT_SQRTF_D_FIDR2R3:
        case V850_IT_TRNCF_DL_FIDR2R3:
        case V850_IT_TRNCF_DUL_FIDR2R3:
        case V850_IT_TRNCF_DUW_FIDR2R3:
            info->b11 = VECINDEX(info->instruction,11,11,0); // 11
            info->b16 = VECINDEX(info->instruction,16,16,0); // 16
            info->b26 = VECINDEX(info->instruction,27,26,0); // 27:26
            info->reg2 = VECINDEX(info->instruction,15,12,0); // 15:12
            info->reg2 = SHIFTL(info->reg2,1);
            info->reg3 = VECINDEX(info->instruction,31,28,0); // 31:28
            info->reg3 = SHIFTL(info->reg3,1);
            break;

        case V850_IT_ABSF_S_FII:
        case V850_IT_CVT_SW_FII:
        case V850_IT_CVT_WS_FII:
        case V850_IT_NEGF_S_FII:
        case V850_IT_TRNC_SW_FII:
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->reg3 = VECINDEX(info->instruction,31,27,0); // 31:27
            break;

        case V850_IT_ADDF_S_FIS:
        case V850_IT_DIVF_S_FIS:
        case V850_IT_MAXF_S_FIS:
        case V850_IT_MINF_S_FIS:
        case V850_IT_MULF_S_FIS:
        case V850_IT_SUBF_S_FIS:
            info->b16 = VECINDEX(info->instruction,16,16,0); // 16
            info->b26 = VECINDEX(info->instruction,26,26,0); // 26
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->reg3 = VECINDEX(info->instruction,31,27,0); // 31:27
            break;

        case V850_IT_CEILF_SL_FISDR2R3:
        case V850_IT_CEILF_SUL_FISDR2R3:
        case V850_IT_CVTF_SD_FISDR2R3:
        case V850_IT_CVTF_SL_FISDR2R3:
        case V850_IT_CVTF_SUL_FISDR2R3:
        case V850_IT_CVTF_UWD_FISDR2R3:
        case V850_IT_CVTF_WD_FISDR2R3:
        case V850_IT_FLOORF_SL_FISDR2R3:
        case V850_IT_FLOORF_SUL_FISDR2R3:
        case V850_IT_TRNCF_SL_FISDR2R3:
        case V850_IT_TRNCF_SUL_FISDR2R3:
            info->b16 = VECINDEX(info->instruction,16,16,0); // 16
            info->b26 = VECINDEX(info->instruction,27,26,0); // 27:26
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->reg3 = VECINDEX(info->instruction,31,28,0); // 31:28
            info->reg3 = SHIFTL(info->reg3,1);
            break;

        case V850_IT_MADDF_S_FISA:
        case V850_IT_MSUBF_S_FISA:
        case V850_IT_NMADDF_S_FISA:
        case V850_IT_NMSUBF_S_FISA:
            info->b16 = VECINDEX(info->instruction,16,16,0); // 16
            info->b26 = VECINDEX(info->instruction,26,26,0); // 26
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->reg3 = VECINDEX(info->instruction,31,27,0); // 31:27
            info->reg4 = VECINDEX(info->instruction,20,17,1) | VECINDEX(info->instruction,23,23,0); // 20:17 23
            break;

        case V850_IT_CMPF_S_FISCOND:
            info->b16 = VECINDEX(info->instruction,16,16,0); // 16
            info->b20 = VECINDEX(info->instruction,20,20,0); // 20
            info->b26 = VECINDEX(info->instruction,26,26,0); // 26
            info->b31 = VECINDEX(info->instruction,31,31,0); // 31
            info->cond = VECINDEX(info->instruction,30,27,0); // 30:27
            info->fff = VECINDEX(info->instruction,19,17,0); // 19:17
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case V850_IT_CMOVF_S_FISFFF:
            info->b16 = VECINDEX(info->instruction,16,16,0); // 16
            info->b20 = VECINDEX(info->instruction,20,20,0); // 20
            info->b26 = VECINDEX(info->instruction,26,26,0); // 26
            info->fff = VECINDEX(info->instruction,19,17,0); // 19:17
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->reg3 = VECINDEX(info->instruction,31,27,0); // 31:27
            break;

        case V850_IT_ABSF_S_FISR2R3:
        case V850_IT_CEILF_SUW_FISR2R3:
        case V850_IT_CEILF_SW_FISR2R3:
        case V850_IT_CVTF_LD_FISR2R3:
        case V850_IT_CVTF_SUW_FISR2R3:
        case V850_IT_CVTF_SW_FISR2R3:
        case V850_IT_CVTF_UWS_FISR2R3:
        case V850_IT_CVTF_WS_FISR2R3:
        case V850_IT_FLOORF_SUW_FISR2R3:
        case V850_IT_FLOORF_SW_FISR2R3:
        case V850_IT_NEGF_S_FISR2R3:
        case V850_IT_RECIPF_S_FISR2R3:
        case V850_IT_RSQRTF_S_FISR2R3:
        case V850_IT_SQRTF_S_FISR2R3:
        case V850_IT_TRNCF_SUW_FISR2R3:
        case V850_IT_TRNCF_SW_FISR2R3:
            info->b16 = VECINDEX(info->instruction,16,16,0); // 16
            info->b26 = VECINDEX(info->instruction,26,26,0); // 26
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->reg3 = VECINDEX(info->instruction,31,27,0); // 31:27
            break;

        case V850_IT_TRFF_FIV:
            break;

        case V850_IT_LDFF_FIVR2A:
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case V850_IT_LDFC_FIVR2B:
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case V850_IT_STFF_FIVR3A:
            info->reg3 = VECINDEX(info->instruction,31,27,0); // 31:27
            break;

        case V850_IT_STFC_FIVR3B:
            info->reg3 = VECINDEX(info->instruction,31,27,0); // 31:27
            break;

        case V850_IT_TRFSR_FIFFF:
            info->fff = VECINDEX(info->instruction,19,17,0); // 19:17
            break;

        //
        // RH850 Only
        //
        case V850_IT_LDL_W_F07D:
        case V850_IT_STC_W_F07D:
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg3 = VECINDEX(info->instruction,31,27,0); // 31:27
            break;

        case V850_IT_ROTL_F07RRR:
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->reg3 = VECINDEX(info->instruction,31,27,0); // 31:27
            break;

        case V850_IT_ROTL_F07IRR:
            info->uimm5 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2  = VECINDEX(info->instruction,15,11,0); // 15:11
            info->reg3  = VECINDEX(info->instruction,31,27,0); // 31:27
            break;

        case V850_IT_BINS_F09RPWR_0: // msb>=16 lsb>=16
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->lsb  = VECINDEX(info->instruction,27,27,3) | VECINDEX(info->instruction,19,17,0); // 27,19.18,17
            info->lsb += 16;
            info->msb  = VECINDEX(info->instruction,31,28,0); // 31,30,29,28
            info->msb += 16;
            break;

        case V850_IT_BINS_F09RPWR_1: // msb>=16 lsb<16
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->lsb  = VECINDEX(info->instruction,27,27,3) | VECINDEX(info->instruction,19,17,0); // 27,19.18,17
            info->msb  = VECINDEX(info->instruction,31,28,0); // 31,30,29,28
            info->msb  += 16;
            break;

        case V850_IT_BINS_F09RPWR_2: // msb<16 lsb<16
            info->reg1 = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg2 = VECINDEX(info->instruction,15,11,0); // 15:11
            info->lsb  = VECINDEX(info->instruction,27,27,3) | VECINDEX(info->instruction,19,17,0); // 27,19.18,17
            info->msb  = VECINDEX(info->instruction,31,28,0); // 31,30,29,28
            break;

        case V850_IT_LD_DW_F14:
        case V850_IT_ST_DW_F14:
        case V850_IT_LD_B_F14:
        case V850_IT_LD_BU_F14:
        case V850_IT_LD_H_F14:
        case V850_IT_LD_HU_F14:
        case V850_IT_LD_W_F14:
        case V850_IT_ST_B_F14:
        case V850_IT_ST_H_F14:
        case V850_IT_ST_W_F14:
            info->reg1  = VECINDEX(info->instruction,4,0,0); // 4:0
            info->reg3  = VECINDEX(info->instruction,31,27,0); // 31:27
            info->sdisp = VECINDEX(info->instruction,47,32,7) | VECINDEX(info->instruction,26,21,1);
            info->sdisp = SEXTEND(info->sdisp,22);
            break;

        case V850_IT_LOOP_F07RI:
            info->reg1     = VECINDEX(info->instruction,4,0,0); // 4:0
            info->sdisp    = VECINDEX(info->instruction,31,17,1);
            info->targetPC = info->thisPC - info->sdisp;
            break;

        case V850_IT_INSTR16:
        case V850_IT_INSTR32:
        case V850_IT_INSTR48:
        case V850_IT_INSTR64:
        case V850_IT_LAST:
            break;
    }

    info->mei.reg = 0;
    switch (info->type) {
    case V850_IT_SLD_B_F04LA:
        info->mei.REG = info->reg2;
        break;

    case V850_IT_SLD_BU_F04DB:
        info->mei.REG = info->reg2;
        info->mei.U   = 1;
        break;

    case V850_IT_SLD_H_F04LB:
        info->mei.REG = info->reg2;
        info->mei.DS  = 1;
        break;

    case V850_IT_SLD_HU_F04DH:
        info->mei.REG = info->reg2;
        info->mei.DS  = 1;
        info->mei.U   = 1;
        break;

    case V850_IT_SLD_W_F04LC:
        info->mei.REG = info->reg2;
        info->mei.DS  = 2;
        break;

    case V850_IT_SST_B_F04SA:
        info->mei.REG = info->reg2;
        info->mei.RW  = 1;
        break;

    case V850_IT_SST_H_F04SB:
        info->mei.REG = info->reg2;
        info->mei.DS  = 1;
        info->mei.RW  = 1;
        break;

    case V850_IT_SST_W_F04SC:
        info->mei.REG = info->reg2;
        info->mei.DS  = 2;
        info->mei.RW  = 1;
        break;

    case V850_IT_LD_B_F07LA:
        info->mei.REG   = info->reg2;
        info->mei.ITYPE = 0x01;
        break;

    case V850_IT_LD_BU_F07C:
        info->mei.REG   = info->reg2;
        info->mei.U     = 1;
        info->mei.ITYPE = 0x01;
        break;

    case V850_IT_LD_H_F07LB:
        info->mei.REG   = info->reg2;
        info->mei.DS    = 1;
        info->mei.ITYPE = 0x01;
        break;

    case V850_IT_LD_HU_F07LB:
        info->mei.REG   = info->reg2;
        info->mei.DS    = 1;
        info->mei.U     = 1;
        info->mei.ITYPE = 0x01;
        break;

    case V850_IT_LD_W_F07LB:
        info->mei.REG   = info->reg2;
        info->mei.DS    = 2;
        info->mei.ITYPE = 0x01;
        break;

    case V850_IT_ST_B_F07SA:
        info->mei.REG   = info->reg2;
        info->mei.RW    = 1;
        info->mei.ITYPE = 0x01;
        break;

    case V850_IT_ST_H_F07SB:
        info->mei.REG   = info->reg2;
        info->mei.DS    = 1;
        info->mei.RW    = 1;
        info->mei.ITYPE = 0x01;
        break;

    case V850_IT_ST_W_F07SB:
        info->mei.REG   = info->reg2;
        info->mei.DS    = 2;
        info->mei.RW    = 1;
        info->mei.ITYPE = 0x01;
        break;

    case V850_IT_LD_B_F14:
        info->mei.REG   = info->reg3;
        info->mei.ITYPE = 0x02;
        break;

    case V850_IT_LD_BU_F14:
        info->mei.REG   = info->reg3;
        info->mei.U     = 1;
        info->mei.ITYPE = 0x02;
        break;

    case V850_IT_LD_H_F14:
        info->mei.REG   = info->reg3;
        info->mei.DS    = 1;
        info->mei.ITYPE = 0x02;
        break;

    case V850_IT_LD_HU_F14:
        info->mei.REG   = info->reg3;
        info->mei.DS    = 1;
        info->mei.U     = 1;
        info->mei.ITYPE = 0x02;
        break;

    case V850_IT_LD_W_F14:
        info->mei.REG   = info->reg3;
        info->mei.DS    = 2;
        info->mei.ITYPE = 0x02;
        break;

    case V850_IT_ST_B_F14:
        info->mei.REG   = info->reg3;
        info->mei.RW    = 1;
        info->mei.ITYPE = 0x02;
        break;

    case V850_IT_ST_H_F14:
        info->mei.REG   = info->reg3;
        info->mei.DS    = 1;
        info->mei.RW    = 1;
        info->mei.ITYPE = 0x02;
        break;

    case V850_IT_ST_W_F14:
        info->mei.REG   = info->reg3;
        info->mei.DS    = 2;
        info->mei.RW    = 1;
        info->mei.ITYPE = 0x02;
        break;

    case V850_IT_LD_DW_F14:
        info->mei.REG   = info->reg3;
        info->mei.DS    = 3;
        info->mei.ITYPE = 0x02;
        break;

    case V850_IT_ST_DW_F14:
        info->mei.REG   = info->reg3;
        info->mei.DS    = 3;
        info->mei.RW    = 1;
        info->mei.ITYPE = 0x02;
        break;

    case V850_IT_LDL_W_F07D:
        info->mei.REG   = info->reg3;
        info->mei.DS    = 2;
        info->mei.ITYPE = 0x02;
        break;

    case V850_IT_STC_W_F07D:
        info->mei.REG   = info->reg3;
        info->mei.DS    = 2;
        info->mei.RW    = 1;
        info->mei.ITYPE = 0x02;
        break;

    case V850_IT_CAXI_F11C:
        info->mei.REG   = info->reg3;
        info->mei.DS    = 2;
        info->mei.U     = 1;
        info->mei.ITYPE = 0x04;
        break;

    case V850_IT_SET1_F08:
    case V850_IT_CLR1_F08:
    case V850_IT_NOT1_F08:
    case V850_IT_TST1_F08:
        info->mei.U     = 1;
        info->mei.ITYPE = 0x05;
        break;

    case V850_IT_PREPARE_F13LI:
    case V850_IT_PREPARE_F13LI00:
    case V850_IT_PREPARE_F13LI01:
    case V850_IT_PREPARE_F13LI10:
    case V850_IT_PREPARE_F13LI11:
        info->mei.DS    = 2;
        info->mei.U     = 1;
        info->mei.RW    = 1;
        info->mei.ITYPE = 0x0C;
        break;

    case V850_IT_DISPOSE_F13IL1:
    case V850_IT_DISPOSE_F13IL2:
        info->mei.DS    = 2;
        info->mei.U     = 1;
        info->mei.ITYPE = 0x0C;
        break;

    case V850_IT_PUSHSP_F11:
        info->mei.DS    = 2;
        info->mei.U     = 1;
        info->mei.RW    = 1;
        info->mei.ITYPE = 0x0D;
        break;

    case V850_IT_POPSP_F11:
        info->mei.DS    = 2;
        info->mei.U     = 1;
        info->mei.ITYPE = 0x0D;
        break;

    case V850_IT_SWITCH_F01D:
        info->mei.DS    = 1;
        info->mei.ITYPE = 0x10;
        break;

    case V850_IT_CALLT_F02B:
        info->mei.DS    = 1;
        info->mei.U     = 1;
        info->mei.ITYPE = 0x11;
        break;

    case V850_IT_SYSCALL_F10C:
        info->mei.DS    = 2;
        info->mei.U     = 1;
        info->mei.ITYPE = 0x12;
        break;

    case V850_IT_CACHE_F10:
    case V850_IT_CACHE_CHBII:
    case V850_IT_CACHE_CIBII:
    case V850_IT_CACHE_CFALI:
    case V850_IT_CACHE_CISTI:
    case V850_IT_CACHE_CILDI:
        info->mei.ITYPE = 0x14;
        break;

    // Interrupt table method
//        info->mei.DS    = 2;
//        info->mei.U     = 1;
//        info->mei.ITYPE = 0x15;
    default:
        break;
    }
    return;
}

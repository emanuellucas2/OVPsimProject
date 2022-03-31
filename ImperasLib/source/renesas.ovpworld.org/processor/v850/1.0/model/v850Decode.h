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

#ifndef V850_DECODE_H
#define V850_DECODE_H

#include "hostapi/impTypes.h"
#include "v850Structure.h"

typedef enum v850InstructionTypeE {
    //
    // format F01 Insns
    //
    V850_IT_ADD_F01,
    V850_IT_AND_F01,
    V850_IT_CMP_F01,
    V850_IT_DIVH_F01,
    V850_IT_MOV_F01,
    V850_IT_MULH_F01,
    V850_IT_NOT_F01,
    V850_IT_OR_F01,
    V850_IT_SATADD_F01,
    V850_IT_SATSUB_F01,
    V850_IT_SATSUBR_F01,
    V850_IT_SUB_F01,
    V850_IT_SUBR_F01,
    V850_IT_TST_F01,
    V850_IT_XOR_F01,

    //
    // format F01a Insns
    //
    V850_IT_DBTRAP_F01A,
    V850_IT_NOP_F01A,
    V850_IT_RIE_F01A,
    V850_IT_RMTRAP_F01A,
    V850_IT_SYNCM_F01A,
    V850_IT_SYNCP_F01A,
    V850_IT_SYNCI_F01A,
    V850_IT_SYNCE_F01A,

    //
    // format F01b Insns
    //
    V850_IT_JMP_F01B,

    //
    // format F01c Insns
    //
    V850_IT_SXB_F01C,
    V850_IT_SXH_F01C,
    V850_IT_ZXB_F01C,
    V850_IT_ZXH_F01C,

    //
    // format F01d Insns
    //
    V850_IT_SWITCH_F01D,

    //
    // format F01e Insns
    //
    V850_IT_FETRAP_F01E,

    //
    // format F02b Insns
    //
    V850_IT_CALLT_F02B,

    //
    // format F02s Insns
    //
    V850_IT_ADD_F02S,
    V850_IT_CMP_F02S,
    V850_IT_MOV_F02S,
    V850_IT_MULH_F02S,
    V850_IT_SATADD_F02S,

    //
    // format F02u Insns
    //
    V850_IT_SAR_F02U,
    V850_IT_SHL_F02U,
    V850_IT_SHR_F02U,

    //
    // format F03 Insns
    //
    V850_IT_BCOND_F03,

    //
    // format F04db Insns
    //
    V850_IT_SLD_BU_F04DB,

    //
    // format F04dh Insns
    //
    V850_IT_SLD_HU_F04DH,

    //
    // format F04la Insns
    //
    V850_IT_SLD_B_F04LA,

    //
    // format F04lb Insns
    //
    V850_IT_SLD_H_F04LB,

    //
    // format F04lc Insns
    //
    V850_IT_SLD_W_F04LC,

    //
    // format F04sa Insns
    //
    V850_IT_SST_B_F04SA,

    //
    // format F04sb Insns
    //
    V850_IT_SST_H_F04SB,

    //
    // format F04sc Insns
    //
    V850_IT_SST_W_F04SC,

    //
    // format F05a Insns
    //
    V850_IT_JARL_F05A,

    //
    // format F05b Insns
    //
    V850_IT_JR_F05B,

    //
    // format F06s Insns
    //
    V850_IT_ADDI_F06S,
    V850_IT_MOVEA_F06S,
    V850_IT_MOVHI_F06S,
    V850_IT_MULHI_F06S,
    V850_IT_SATSUBI_F06S,

    //
    // format F06sa Insns
    //
    V850_IT_JARL_F06SA,

    //
    // format F06sb Insns
    //
    V850_IT_JMP_F06SB,

    //
    // format F06sc Insns
    //
    V850_IT_JR_F06SC,

    //
    // format F06u Insns
    //
    V850_IT_ANDI_F06U,
    V850_IT_ORI_F06U,
    V850_IT_XORI_F06U,

    //
    // format F06ua Insns
    //
    V850_IT_MOV_F06UA,

    //
    // format F06x Insns
    //
    V850_IT_RIE_F06X,

    //
    // format F07cc Insns
    //
    V850_IT_BCOND_F07CC,

    //
    // format F07cc Insns
    //
    V850_IT_LOOP_F07RI,

    //
    // format F07c Insns
    //
    V850_IT_LD_BU_F07C,

    //
    // format F07la Insns
    //
    V850_IT_LD_B_F07LA,

    //
    // format F07lb Insns
    //
    V850_IT_LD_H_F07LB,
    V850_IT_LD_HU_F07LB,
    V850_IT_LD_W_F07LB,

    //
    // format F07sa Insns
    //
    V850_IT_ST_B_F07SA,

    //
    // format F07sb Insns
    //
    V850_IT_ST_H_F07SB,
    V850_IT_ST_W_F07SB,

    //
    // format fo7d
    //
    V850_IT_LDL_W_F07D,
    V850_IT_STC_W_F07D,

    //
    // format F07rrr
    //
    V850_IT_ROTL_F07RRR,

    //
    // format F07irr
    //
    V850_IT_ROTL_F07IRR,

    //
    // format F08 Insns
    //
    V850_IT_CLR1_F08,
    V850_IT_NOT1_F08,
    V850_IT_SET1_F08,
    V850_IT_TST1_F08,

    //
    // format F09 Insns
    //
    V850_IT_SASF_F09,
    V850_IT_SETF_F09,

    //
    // format F09rr Insns
    //
    V850_IT_SAR_F09RR,
    V850_IT_SHL_F09RR,
    V850_IT_SHR_F09RR,

    //
    // format F09rr2 Insns
    //
    V850_IT_SCH0L_F09RR2,
    V850_IT_SCH0R_F09RR2,
    V850_IT_SCH1L_F09RR2,
    V850_IT_SCH1R_F09RR2,

    //
    // format F09rs1 Insns
    //
    V850_IT_LDSR_F09RS1_0,
    V850_IT_LDSR_F09RS1,

    //
    // format F09rs2 Insns
    //
    V850_IT_CLR1_F09RS2,
    V850_IT_NOT1_F09RS2,
    V850_IT_SET1_F09RS2,
    V850_IT_TST1_F09RS2,

    //
    // format F09sr Insns
    //
    V850_IT_STSR_F09SR_0,
    V850_IT_STSR_F09SR,

    //
    // format F09rpwr Insns
    //
    V850_IT_BINS_F09RPWR_0,
    V850_IT_BINS_F09RPWR_1,
    V850_IT_BINS_F09RPWR_2,

    //
    // format F10a Insns
    //
    V850_IT_CLL_F10,
    V850_IT_SNOOZE_F10,
    V850_IT_CACHE_F10,
    V850_IT_CACHE_CHBII,
    V850_IT_CACHE_CIBII,
    V850_IT_CACHE_CFALI,
    V850_IT_CACHE_CISTI,
    V850_IT_CACHE_CILDI,
    V850_IT_PREF_F10,
    V850_IT_PREFI_F10,

    //
    // format F10a Insns
    //
    V850_IT_CTRET_F10A,
    V850_IT_DBRET_F10A,
    V850_IT_DI_F10A,
    V850_IT_EI_F10A,
    V850_IT_EIRET_F10A,
    V850_IT_FERET_F10A,
    V850_IT_HALT_F10A,
    V850_IT_RETI_F10A,

    //
    // format F10b Insns
    //
    V850_IT_TRAP_F10B,
    V850_IT_SYSCALL_F10C,

    //
    // format F11 Insns
    //
    V850_IT_DIV_F11,
    V850_IT_DIVH_F11,
    V850_IT_DIVHU_F11,
    V850_IT_DIVQ_F11,
    V850_IT_DIVQU_F11,
    V850_IT_DIVU_F11,
    V850_IT_MUL_F11,
    V850_IT_MULU_F11,
    V850_IT_SAR_F11,
    V850_IT_SATADD_F11,
    V850_IT_SATSUB_F11,
    V850_IT_SHL_F11,
    V850_IT_SHR_F11,

    //
    // format F11a Insns
    //
    V850_IT_MAC_F11A,
    V850_IT_MACU_F11A,

    //
    // format F11b Insns
    //
    V850_IT_ADF_F11B,
    V850_IT_CMOV_F11B,
    V850_IT_SBF_F11B,

    //
    // format F11c Insns
    //
    V850_IT_CAXI_F11C,

    //
    // format F11d Insns
    //
    V850_IT_JARL_F11D,

    //
    // format F11 Insns
    //
    V850_IT_PUSHSP_F11,
    V850_IT_POPSP_F11,

    //
    // format F12a Insns
    //
    V850_IT_CMOV_F12A,

    //
    // format F12b Insns
    //
    V850_IT_BSH_F12B,
    V850_IT_BSW_F12B,
    V850_IT_HSH_F12B,
    V850_IT_HSW_F12B,

    //
    // format F12s Insns
    //
    V850_IT_MUL_F12S,

    //
    // format F12u Insns
    //
    V850_IT_MULU_F12U,

    //
    // format F13il1 Insns
    //
    V850_IT_DISPOSE_F13IL1,

    //
    // format F13il2 Insns
    //
    V850_IT_DISPOSE_F13IL2,

    //
    // format F13li Insns
    //
    V850_IT_PREPARE_F13LI,

    //
    // format F13li00 Insns
    //
    V850_IT_PREPARE_F13LI00,

    //
    // format F13li01 Insns
    //
    V850_IT_PREPARE_F13LI01,

    //
    // format F13li10 Insns
    //
    V850_IT_PREPARE_F13LI10,

    //
    // format F13li11 Insns
    //
    V850_IT_PREPARE_F13LI11,

    //
    // format FI Insns
    //
    V850_IT_ADDF_S_FI,
    V850_IT_DIVF_S_FI,
    V850_IT_MAXF_S_FI,
    V850_IT_MINF_S_FI,
    V850_IT_MULF_S_FI,
    V850_IT_SUBF_S_FI,

    V850_IT_FMAF_S_FI,
    V850_IT_FMSF_S_FI,
    V850_IT_FNMAF_S_FI,
    V850_IT_FNMSF_S_FI,

    //
    // format FID Insns
    //
    V850_IT_ADDF_D_FID,
    V850_IT_DIVF_D_FID,
    V850_IT_MAXF_D_FID,
    V850_IT_MINF_D_FID,
    V850_IT_MULF_D_FID,
    V850_IT_SUBF_D_FID,

    //
    // format FIDSr2r3 Insns
    //
    V850_IT_CEILF_DW_FIDSR2R3,
    V850_IT_CVTF_DS_FIDSR2R3,
    V850_IT_CVTF_DUW_FIDSR2R3,
    V850_IT_CVTF_DW_FIDSR2R3,
    V850_IT_CVTF_LS_FIDSR2R3,
    V850_IT_CVTF_ULS_FIDSR2R3,
    V850_IT_FLOORF_DW_FIDSR2R3,
    V850_IT_TRNCF_DW_FIDSR2R3,

    //
    // CVT FI
    //
    V850_IT_CVTF_HS_FI,
    V850_IT_CVTF_SH_FI,

    //
    // format FIDcond Insns
    //
    V850_IT_CMPF_D_FIDCOND,

    //
    // format FIDfff Insns
    //
    V850_IT_CMOVF_D_FIDFFF,

    //
    // format FIDr2r3 Insns
    //
    V850_IT_ABSF_D_FIDR2R3,
    V850_IT_CEILF_DL_FIDR2R3,
    V850_IT_CEILF_DUL_FIDR2R3,
    V850_IT_CEILF_DUW_FIDR2R3,
    V850_IT_CVTF_DL_FIDR2R3,
    V850_IT_CVTF_DUL_FIDR2R3,
    V850_IT_CVTF_ULD_FIDR2R3,
    V850_IT_FLOORF_DL_FIDR2R3,
    V850_IT_FLOORF_DUL_FIDR2R3,
    V850_IT_FLOORF_DUW_FIDR2R3,
    V850_IT_NEGF_D_FIDR2R3,
    V850_IT_RECIPF_D_FIDR2R3,
    V850_IT_RSQRTF_D_FIDR2R3,
    V850_IT_SQRTF_D_FIDR2R3,
    V850_IT_TRNCF_DL_FIDR2R3,
    V850_IT_TRNCF_DUL_FIDR2R3,
    V850_IT_TRNCF_DUW_FIDR2R3,

    //
    // format FII Insns
    //
    V850_IT_ABSF_S_FII,
    V850_IT_CVT_SW_FII,
    V850_IT_CVT_WS_FII,
    V850_IT_NEGF_S_FII,
    V850_IT_TRNC_SW_FII,

    //
    // format FIS Insns
    //
    V850_IT_ADDF_S_FIS,
    V850_IT_DIVF_S_FIS,
    V850_IT_MAXF_S_FIS,
    V850_IT_MINF_S_FIS,
    V850_IT_MULF_S_FIS,
    V850_IT_SUBF_S_FIS,

    //
    // format FISDr2r3 Insns
    //
    V850_IT_CEILF_SL_FISDR2R3,
    V850_IT_CEILF_SUL_FISDR2R3,
    V850_IT_CVTF_SD_FISDR2R3,
    V850_IT_CVTF_SL_FISDR2R3,
    V850_IT_CVTF_SUL_FISDR2R3,
    V850_IT_CVTF_UWD_FISDR2R3,
    V850_IT_CVTF_WD_FISDR2R3,
    V850_IT_FLOORF_SL_FISDR2R3,
    V850_IT_FLOORF_SUL_FISDR2R3,
    V850_IT_TRNCF_SL_FISDR2R3,
    V850_IT_TRNCF_SUL_FISDR2R3,

    //
    // format FISa Insns
    //
    V850_IT_MADDF_S_FISA,
    V850_IT_MSUBF_S_FISA,
    V850_IT_NMADDF_S_FISA,
    V850_IT_NMSUBF_S_FISA,

    //
    // format FIScond Insns
    //
    V850_IT_CMPF_S_FISCOND,

    //
    // format FISfff Insns
    //
    V850_IT_CMOVF_S_FISFFF,

    //
    // format FISr2r3 Insns
    //
    V850_IT_ABSF_S_FISR2R3,
    V850_IT_CEILF_SUW_FISR2R3,
    V850_IT_CEILF_SW_FISR2R3,
    V850_IT_CVTF_LD_FISR2R3,
    V850_IT_CVTF_SUW_FISR2R3,
    V850_IT_CVTF_SW_FISR2R3,
    V850_IT_CVTF_UWS_FISR2R3,
    V850_IT_CVTF_WS_FISR2R3,
    V850_IT_FLOORF_SUW_FISR2R3,
    V850_IT_FLOORF_SW_FISR2R3,
    V850_IT_NEGF_S_FISR2R3,
    V850_IT_RECIPF_S_FISR2R3,
    V850_IT_RSQRTF_S_FISR2R3,
    V850_IT_SQRTF_S_FISR2R3,
    V850_IT_TRNCF_SUW_FISR2R3,
    V850_IT_TRNCF_SW_FISR2R3,

    //
    // format FIV Insns
    //
    V850_IT_TRFF_FIV,

    //
    // format FIVr2a Insns
    //
    V850_IT_LDFF_FIVR2A,

    //
    // format FIVr2b Insns
    //
    V850_IT_LDFC_FIVR2B,

    //
    // format FIVr3a Insns
    //
    V850_IT_STFF_FIVR3A,

    //
    // format FIVr3b Insns
    //
    V850_IT_STFC_FIVR3B,

    //
    // format FIfff Insns
    //
    V850_IT_TRFSR_FIFFF,

    //
    // format F14
    //
    V850_IT_LD_DW_F14,
    V850_IT_ST_DW_F14,
    V850_IT_LD_B_F14,
    V850_IT_LD_BU_F14,
    V850_IT_LD_H_F14,
    V850_IT_LD_HU_F14,
    V850_IT_LD_W_F14,
    V850_IT_ST_B_F14,
    V850_IT_ST_H_F14,
    V850_IT_ST_W_F14,

    //
    // Drop through catch for instruction widths 16 32 48 64
    //
    V850_IT_INSTR16,
    V850_IT_INSTR32,
    V850_IT_INSTR48,
    V850_IT_INSTR64,

    //
    // Drop through catch all
    //
    V850_IT_LAST
} v850InstructionType;

#define V850_DISPATCH_FN(_NAME) void _NAME( \
    v850P v850, \
    v850InstructionInfoP info, \
    void *userData \
)

typedef V850_DISPATCH_FN((*v850DispatchFn));
typedef const v850DispatchFn v850DispatchTableC[V850_IT_LAST];
typedef v850DispatchTableC *v850DispatchTableCP;

vmidDecodeTableP v850CreateDecodeTable_ISA_E0_16Bit(vmidDecodeTableP current);
vmidDecodeTableP v850CreateDecodeTable_ISA_E0_32Bit(vmidDecodeTableP current);
vmidDecodeTableP v850CreateDecodeTable_ISA_E1_16Bit(vmidDecodeTableP current);
vmidDecodeTableP v850CreateDecodeTable_ISA_E1_32Bit(vmidDecodeTableP current);
vmidDecodeTableP v850CreateDecodeTable_ISA_E1_48Bit(vmidDecodeTableP current);
vmidDecodeTableP v850CreateDecodeTable_ISA_E1_64Bit(vmidDecodeTableP current);
vmidDecodeTableP v850CreateDecodeTable_ISA_E1_FP_32Bit(vmidDecodeTableP current);

vmidDecodeTableP v850CreateDecodeTable_ISA_E2_16Bit(vmidDecodeTableP current);
vmidDecodeTableP v850CreateDecodeTable_ISA_E2_32Bit(vmidDecodeTableP current);
vmidDecodeTableP v850CreateDecodeTable_ISA_E2_48Bit(vmidDecodeTableP current);
vmidDecodeTableP v850CreateDecodeTable_ISA_E2_FP_32Bit(vmidDecodeTableP current);

vmidDecodeTableP v850CreateDecodeTable_ISA_E3_16Bit(vmidDecodeTableP current);
vmidDecodeTableP v850CreateDecodeTable_ISA_E3_32Bit(vmidDecodeTableP current);
vmidDecodeTableP v850CreateDecodeTable_ISA_E3_FP_32Bit(vmidDecodeTableP current);
vmidDecodeTableP v850CreateDecodeTable_ISA_E3_48Bit(vmidDecodeTableP current);

void v850GenInstructionInfo (v850InstructionInfoP info);

void v850Decode(
    v850P                v850,
    v850Addr             thisPC,
    v850InstructionInfoP info
);

//
// info structure accessed from decoder
//
typedef struct v850InstructionInfoS {
    //
    // Default structure members
    //
    const char           *opcode;
    v850Addr              thisPC;
    v850Addr              nextPC;
    v850Addr              targetPC;
    Uns64                 instruction;
    Uns8                  instrsize;
    v850InstructionType   type;
    v850Architecture      arch;

    octiaInstructionClass class;

    //
    // Instruction format generated structure members
    //
    Uns8  b11;
    Uns8  b16;
    Uns8  b20;
    Uns8  b26;
    Uns8  b31;
    Uns8  bit;
    Uns8  cccc;
    Uns8  cond;
    Uns8  fff;
    Uns16 list12;
    Uns8  reg1;
    Uns8  reg2;
    Uns8  reg3;
    Uns8  reg4;
    Int32 sdisp;
    Int32 simm;
    Uns32 udisp;
    Uns32 uimm;
    Uns8  uimm5;
    Uns8  msb;
    Uns8  lsb;

    //
    // MEI Register for MPU Data exception handling
    //
    TYPE_SPR_MEI mei;
} v850InstructionInfo;

#endif // V850_DECODE_H

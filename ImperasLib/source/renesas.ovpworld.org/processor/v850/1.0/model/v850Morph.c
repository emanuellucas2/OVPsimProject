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

#include "vmi/vmiMessage.h"
#include "vmi/vmiMt.h"
#include "vmi/vmiRt.h"
#include "v850Morph.h"
#include "v850Decode.h"
#include "v850Functions.h"
#include "v850Instructions.h"
#include "v850Structure.h"

//
// Write Morpher Table
//
const static v850MorphAttr dispatchTable[V850_IT_LAST+1] = {
    //
    // Format F01 Insns
    //
    [V850_IT_ADD_F01]     = {arch:ISA_E0, morph:morphADD_F01},
    [V850_IT_AND_F01]     = {arch:ISA_E0, morph:morphAND_F01},
    [V850_IT_CMP_F01]     = {arch:ISA_E0, morph:morphCMP_F01},
    [V850_IT_DIVH_F01]    = {arch:ISA_E0, morph:morphDIVH_F01},
    [V850_IT_MOV_F01]     = {arch:ISA_E0, morph:morphMOV_F01},
    [V850_IT_MULH_F01]    = {arch:ISA_E0, morph:morphMULH_F01},
    [V850_IT_NOT_F01]     = {arch:ISA_E0, morph:morphNOT_F01},
    [V850_IT_OR_F01]      = {arch:ISA_E0, morph:morphOR_F01},
    [V850_IT_SATADD_F01]  = {arch:ISA_E0, morph:morphSATADD_F01},
    [V850_IT_SATSUB_F01]  = {arch:ISA_E0, morph:morphSATSUB_F01},
    [V850_IT_SATSUBR_F01] = {arch:ISA_E0, morph:morphSATSUBR_F01},
    [V850_IT_SUB_F01]     = {arch:ISA_E0, morph:morphSUB_F01},
    [V850_IT_SUBR_F01]    = {arch:ISA_E0, morph:morphSUBR_F01},
    [V850_IT_TST_F01]     = {arch:ISA_E0, morph:morphTST_F01},
    [V850_IT_XOR_F01]     = {arch:ISA_E0, morph:morphXOR_F01},

    //
    // Format F01a Insns
    //
    [V850_IT_DBTRAP_F01A] = {arch:ISA_E1, morph:morphDBTRAP_F01A},
    [V850_IT_NOP_F01A]    = {arch:ISA_E0, morph:morphNOP_F01A},
    [V850_IT_RIE_F01A]    = {arch:ISA_E2, morph:morphRIE_F01A},
    [V850_IT_RMTRAP_F01A] = {arch:ISA_E2, morph:morphRMTRAP_F01A},
    [V850_IT_SYNCM_F01A]  = {arch:ISA_E2, morph:morphSYNCM_F01A},
    [V850_IT_SYNCP_F01A]  = {arch:ISA_E2, morph:morphSYNCP_F01A},

    //
    // Format F01b Insns
    //
    [V850_IT_JMP_F01B] = {arch:ISA_E0, morph:morphJMP_F01B},

    //
    // Format F01c Insns
    //
    [V850_IT_SXB_F01C] = {arch:ISA_E1, morph:morphSXB_F01C},
    [V850_IT_SXH_F01C] = {arch:ISA_E1, morph:morphSXH_F01C},
    [V850_IT_ZXB_F01C] = {arch:ISA_E1, morph:morphZXB_F01C},
    [V850_IT_ZXH_F01C] = {arch:ISA_E1, morph:morphZXH_F01C},

    //
    // Format F01d Insns
    //
    [V850_IT_SWITCH_F01D] = {arch:ISA_E1, morph:morphSWITCH_F01D},

    //
    // Format F01e Insns
    //
    [V850_IT_FETRAP_F01E] = {arch:ISA_E2, morph:morphFETRAP_F01E},

    //
    // Format F02b Insns
    //
    [V850_IT_CALLT_F02B] = {arch:ISA_E1, morph:morphCALLT_F02B},

    //
    // Format F02s Insns
    //
    [V850_IT_ADD_F02S]    = {arch:ISA_E0, morph:morphADD_F02S},
    [V850_IT_CMP_F02S]    = {arch:ISA_E0, morph:morphCMP_F02S},
    [V850_IT_MOV_F02S]    = {arch:ISA_E0, morph:morphMOV_F02S},
    [V850_IT_MULH_F02S]   = {arch:ISA_E0, morph:morphMULH_F02S},
    [V850_IT_SATADD_F02S] = {arch:ISA_E0, morph:morphSATADD_F02S},

    //
    // Format F02u Insns
    //
    [V850_IT_SAR_F02U] = {arch:ISA_E0, morph:morphSAR_F02U},
    [V850_IT_SHL_F02U] = {arch:ISA_E0, morph:morphSHL_F02U},
    [V850_IT_SHR_F02U] = {arch:ISA_E0, morph:morphSHR_F02U},

    //
    // Format F03 Insns
    //
    [V850_IT_BCOND_F03] = {arch:ISA_E0, morph:morphBCOND_F03},

    //
    // Format F04db Insns
    //
    [V850_IT_SLD_BU_F04DB] = {arch:ISA_E1, morph:morphSLD_BU_F04DB},

    //
    // Format F04dh Insns
    //
    [V850_IT_SLD_HU_F04DH] = {arch:ISA_E1, morph:morphSLD_HU_F04DH},

    //
    // Format F04la Insns
    //
    [V850_IT_SLD_B_F04LA] = {arch:ISA_E0, morph:morphSLD_B_F04LA},

    //
    // Format F04lb Insns
    //
    [V850_IT_SLD_H_F04LB] = {arch:ISA_E0, morph:morphSLD_H_F04LB},

    //
    // Format F04lc Insns
    //
    [V850_IT_SLD_W_F04LC] = {arch:ISA_E0, morph:morphSLD_W_F04LC},

    //
    // Format F04sa Insns
    //
    [V850_IT_SST_B_F04SA] = {arch:ISA_E0, morph:morphSST_B_F04SA},

    //
    // Format F04sb Insns
    //
    [V850_IT_SST_H_F04SB] = {arch:ISA_E0, morph:morphSST_H_F04SB},

    //
    // Format F04sc Insns
    //
    [V850_IT_SST_W_F04SC] = {arch:ISA_E0, morph:morphSST_W_F04SC},

    //
    // Format F05a Insns
    //
    [V850_IT_JARL_F05A] = {arch:ISA_E0, morph:morphJARL_F05A},

    //
    // Format F05b Insns
    //
    [V850_IT_JR_F05B] = {arch:ISA_E0, morph:morphJR_F05B},

    //
    // Format F06s Insns
    //
    [V850_IT_ADDI_F06S]    = {arch:ISA_E0, morph:morphADDI_F06S},
    [V850_IT_MOVEA_F06S]   = {arch:ISA_E0, morph:morphMOVEA_F06S},
    [V850_IT_MOVHI_F06S]   = {arch:ISA_E0, morph:morphMOVHI_F06S},
    [V850_IT_MULHI_F06S]   = {arch:ISA_E0, morph:morphMULHI_F06S},
    [V850_IT_SATSUBI_F06S] = {arch:ISA_E0, morph:morphSATSUBI_F06S},

    //
    // Format F06sa Insns
    //
    [V850_IT_JARL_F06SA] = {arch:ISA_E2, morph:morphJARL_F06SA},

    //
    // Format F06sb Insns
    //
    [V850_IT_JMP_F06SB] = {arch:ISA_E2, morph:morphJMP_F06SB},

    //
    // Format F06sc Insns
    //
    [V850_IT_JR_F06SC] = {arch:ISA_E2, morph:morphJR_F06SC},

    //
    // Format F06u Insns
    //
    [V850_IT_ANDI_F06U] = {arch:ISA_E0, morph:morphANDI_F06U},
    [V850_IT_ORI_F06U]  = {arch:ISA_E0, morph:morphORI_F06U},
    [V850_IT_XORI_F06U] = {arch:ISA_E0, morph:morphXORI_F06U},

    //
    // Format F06ua Insns
    //
    [V850_IT_MOV_F06UA] = {arch:ISA_E1, morph:morphMOV_F06UA},

    //
    // Format F06x Insns
    //
    [V850_IT_RIE_F06X] = {arch:ISA_E2, morph:morphRIE_F06X},

    //
    // Format F07c Insns
    //
    [V850_IT_LD_BU_F07C] = {arch:ISA_E1, morph:morphLD_BU_F07C},

    //
    // Format F07la Insns
    //
    [V850_IT_LD_B_F07LA] = {arch:ISA_E0, morph:morphLD_B_F07LA},

    //
    // Format F07lb Insns
    //
    [V850_IT_LD_H_F07LB]  = {arch:ISA_E0, morph:morphLD_H_F07LB},
    [V850_IT_LD_HU_F07LB] = {arch:ISA_E1, morph:morphLD_HU_F07LB},
    [V850_IT_LD_W_F07LB]  = {arch:ISA_E0, morph:morphLD_W_F07LB},

    //
    // Format F07sa Insns
    //
    [V850_IT_ST_B_F07SA] = {arch:ISA_E0, morph:morphST_B_F07SA},

    //
    // Format F07sb Insns
    //
    [V850_IT_ST_H_F07SB] = {arch:ISA_E0, morph:morphST_H_F07SB},
    [V850_IT_ST_W_F07SB] = {arch:ISA_E0, morph:morphST_W_F07SB},

    //
    // Format F08 Insns
    //
    [V850_IT_CLR1_F08] = {arch:ISA_E0, morph:morphCLR1_F08},
    [V850_IT_NOT1_F08] = {arch:ISA_E0, morph:morphNOT1_F08},
    [V850_IT_SET1_F08] = {arch:ISA_E0, morph:morphSET1_F08},
    [V850_IT_TST1_F08] = {arch:ISA_E0, morph:morphTST1_F08},

    //
    // Format F09 Insns
    //
    [V850_IT_SASF_F09] = {arch:ISA_E1, morph:morphSASF_F09},
    [V850_IT_SETF_F09] = {arch:ISA_E0, morph:morphSETF_F09},

    //
    // Format F09rr Insns
    //
    [V850_IT_SAR_F09RR] = {arch:ISA_E0, morph:morphSAR_F09RR},
    [V850_IT_SHL_F09RR] = {arch:ISA_E0, morph:morphSHL_F09RR},
    [V850_IT_SHR_F09RR] = {arch:ISA_E0, morph:morphSHR_F09RR},

    //
    // Format F09rr2 Insns
    //
    [V850_IT_SCH0L_F09RR2] = {arch:ISA_E2, morph:morphSCH0L_F09RR2},
    [V850_IT_SCH0R_F09RR2] = {arch:ISA_E2, morph:morphSCH0R_F09RR2},
    [V850_IT_SCH1L_F09RR2] = {arch:ISA_E2, morph:morphSCH1L_F09RR2},
    [V850_IT_SCH1R_F09RR2] = {arch:ISA_E2, morph:morphSCH1R_F09RR2},

    //
    // Format F09rs1 Insns
    //
    [V850_IT_LDSR_F09RS1_0] = {arch:ISA_E0, morph:morphLDSR_F09RS1},
    [V850_IT_LDSR_F09RS1]   = {arch:ISA_E0, morph:morphLDSR_F09RS1},

    //
    // Format F09rs2 Insns
    //
    [V850_IT_CLR1_F09RS2] = {arch:ISA_E1, morph:morphCLR1_F09RS2},
    [V850_IT_NOT1_F09RS2] = {arch:ISA_E1, morph:morphNOT1_F09RS2},
    [V850_IT_SET1_F09RS2] = {arch:ISA_E1, morph:morphSET1_F09RS2},
    [V850_IT_TST1_F09RS2] = {arch:ISA_E1, morph:morphTST1_F09RS2},

    //
    // Format F09sr Insns
    //
    [V850_IT_STSR_F09SR_0] = {arch:ISA_E0, morph:morphSTSR_F09SR},
    [V850_IT_STSR_F09SR]   = {arch:ISA_E0, morph:morphSTSR_F09SR},

    //
    // Format F10a Insns
    //
    [V850_IT_CTRET_F10A] = {arch:ISA_E1, morph:morphCTRET_F10A},
    [V850_IT_DBRET_F10A] = {arch:ISA_E1, morph:morphDBRET_F10A},
    [V850_IT_DI_F10A]    = {arch:ISA_E0, morph:morphDI_F10A},
    [V850_IT_EI_F10A]    = {arch:ISA_E0, morph:morphEI_F10A},
    [V850_IT_EIRET_F10A] = {arch:ISA_E2, morph:morphEIRET_F10A},
    [V850_IT_FERET_F10A] = {arch:ISA_E2, morph:morphFERET_F10A},
    [V850_IT_HALT_F10A]  = {arch:ISA_E0, morph:morphHALT_F10A},
    [V850_IT_RETI_F10A]  = {arch:ISA_E0, morph:morphRETI_F10A},

    //
    // Format F10b Insns
    //
    [V850_IT_TRAP_F10B] = {arch:ISA_E0, morph:morphTRAP_F10B},

    //
    // Format F11 Insns
    //
    [V850_IT_DIV_F11]    = {arch:ISA_E1, morph:morphDIV_F11},
    [V850_IT_DIVH_F11]   = {arch:ISA_E1, morph:morphDIVH_F11},
    [V850_IT_DIVHU_F11]  = {arch:ISA_E1, morph:morphDIVHU_F11},
    [V850_IT_DIVQ_F11]   = {arch:ISA_E2, morph:morphDIVQ_F11},
    [V850_IT_DIVQU_F11]  = {arch:ISA_E2, morph:morphDIVQU_F11},
    [V850_IT_DIVU_F11]   = {arch:ISA_E1, morph:morphDIVU_F11},
    [V850_IT_MUL_F11]    = {arch:ISA_E1, morph:morphMUL_F11},
    [V850_IT_MULU_F11]   = {arch:ISA_E1, morph:morphMULU_F11},
    [V850_IT_SAR_F11]    = {arch:ISA_E2, morph:morphSAR_F11},
    [V850_IT_SATADD_F11] = {arch:ISA_E2, morph:morphSATADD_F11},
    [V850_IT_SATSUB_F11] = {arch:ISA_E2, morph:morphSATSUB_F11},
    [V850_IT_SHL_F11]    = {arch:ISA_E2, morph:morphSHL_F11},
    [V850_IT_SHR_F11]    = {arch:ISA_E2, morph:morphSHR_F11},

    //
    // Format F11a Insns
    //
    [V850_IT_MAC_F11A]  = {arch:ISA_E2, morph:morphMAC_F11A},
    [V850_IT_MACU_F11A] = {arch:ISA_E2, morph:morphMACU_F11A},

    //
    // Format F11b Insns
    //
    [V850_IT_ADF_F11B]  = {arch:ISA_E2, morph:morphADF_F11B},
    [V850_IT_CMOV_F11B] = {arch:ISA_E1, morph:morphCMOV_F11B},
    [V850_IT_SBF_F11B]  = {arch:ISA_E2, morph:morphSBF_F11B},

    //
    // Format F11c Insns
    //
    [V850_IT_CAXI_F11C] = {arch:ISA_E2, morph:morphCAXI_F11C},

    //
    // Format F12a Insns
    //
    [V850_IT_CMOV_F12A] = {arch:ISA_E1, morph:morphCMOV_F12A},

    //
    // Format F12b Insns
    //
    [V850_IT_BSH_F12B] = {arch:ISA_E1, morph:morphBSH_F12B},
    [V850_IT_BSW_F12B] = {arch:ISA_E1, morph:morphBSW_F12B},
    [V850_IT_HSH_F12B] = {arch:ISA_E2, morph:morphHSH_F12B},
    [V850_IT_HSW_F12B] = {arch:ISA_E1, morph:morphHSW_F12B},

    //
    // Format F12s Insns
    //
    [V850_IT_MUL_F12S] = {arch:ISA_E1, morph:morphMUL_F12S},

    //
    // Format F12u Insns
    //
    [V850_IT_MULU_F12U] = {arch:ISA_E1, morph:morphMULU_F12U},

    //
    // Format F13il1 Insns
    //
    [V850_IT_DISPOSE_F13IL1] = {arch:ISA_E1, morph:morphDISPOSE_F13IL1},

    //
    // Format F13il2 Insns
    //
    [V850_IT_DISPOSE_F13IL2] = {arch:ISA_E1, morph:morphDISPOSE_F13IL2},

    //
    // Format F13li Insns
    //
    [V850_IT_PREPARE_F13LI] = {arch:ISA_E1, morph:morphPREPARE_F13LI},

    //
    // Format F13li00 Insns
    //
    [V850_IT_PREPARE_F13LI00] = {arch:ISA_E1, morph:morphPREPARE_F13LI00},

    //
    // Format F13li01 Insns
    //
    [V850_IT_PREPARE_F13LI01] = {arch:ISA_E1, morph:morphPREPARE_F13LI01},

    //
    // Format F13li10 Insns
    //
    [V850_IT_PREPARE_F13LI10] = {arch:ISA_E1, morph:morphPREPARE_F13LI10},

    //
    // Format F13li11 Insns
    //
    [V850_IT_PREPARE_F13LI11] = {arch:ISA_E1, morph:morphPREPARE_F13LI11},

    //
    // Format FI Insns
    //
    [V850_IT_ADDF_S_FI] = {arch:ISA_E1_FP, morph:morphADDF_S_FI},
    [V850_IT_DIVF_S_FI] = {arch:ISA_E1_FP, morph:morphDIVF_S_FI},
    [V850_IT_MAXF_S_FI] = {arch:ISA_E1_FP, morph:morphMAXF_S_FI},
    [V850_IT_MINF_S_FI] = {arch:ISA_E1_FP, morph:morphMINF_S_FI},
    [V850_IT_MULF_S_FI] = {arch:ISA_E1_FP, morph:morphMULF_S_FI},
    [V850_IT_SUBF_S_FI] = {arch:ISA_E1_FP, morph:morphSUBF_S_FI},

    //
    // Format FID Insns
    //
    [V850_IT_ADDF_D_FID] = {arch:ISA_E2_FP, morph:morphADDF_D_FID},
    [V850_IT_DIVF_D_FID] = {arch:ISA_E2_FP, morph:morphDIVF_D_FID},
    [V850_IT_MAXF_D_FID] = {arch:ISA_E2_FP, morph:morphMAXF_D_FID},
    [V850_IT_MINF_D_FID] = {arch:ISA_E2_FP, morph:morphMINF_D_FID},
    [V850_IT_MULF_D_FID] = {arch:ISA_E2_FP, morph:morphMULF_D_FID},
    [V850_IT_SUBF_D_FID] = {arch:ISA_E2_FP, morph:morphSUBF_D_FID},

    //
    // Format FIDSr2r3 Insns
    //
    [V850_IT_CEILF_DW_FIDSR2R3]  = {arch:ISA_E2_FP, morph:morphCEILF_DW_FIDSR2R3},
    [V850_IT_CVTF_DS_FIDSR2R3]   = {arch:ISA_E2_FP, morph:morphCVTF_DS_FIDSR2R3},
    [V850_IT_CVTF_DUW_FIDSR2R3]  = {arch:ISA_E2_FP, morph:morphCVTF_DUW_FIDSR2R3},
    [V850_IT_CVTF_DW_FIDSR2R3]   = {arch:ISA_E2_FP, morph:morphCVTF_DW_FIDSR2R3},
    [V850_IT_CVTF_LS_FIDSR2R3]   = {arch:ISA_E2_FP, morph:morphCVTF_LS_FIDSR2R3},
    [V850_IT_CVTF_ULS_FIDSR2R3]  = {arch:ISA_E2_FP, morph:morphCVTF_ULS_FIDSR2R3},
    [V850_IT_FLOORF_DW_FIDSR2R3] = {arch:ISA_E2_FP, morph:morphFLOORF_DW_FIDSR2R3},
    [V850_IT_TRNCF_DW_FIDSR2R3]  = {arch:ISA_E2_FP, morph:morphTRNCF_DW_FIDSR2R3},

    //
    // Format FIDcond Insns
    //
    [V850_IT_CMPF_D_FIDCOND] = {arch:ISA_E2_FP, morph:morphCMPF_D_FIDCOND},

    //
    // Format FIDfff Insns
    //
    [V850_IT_CMOVF_D_FIDFFF] = {arch:ISA_E2_FP, morph:morphCMOVF_D_FIDFFF},

    //
    // Format FIDr2r3 Insns
    //
    [V850_IT_ABSF_D_FIDR2R3]     = {arch:ISA_E2_FP, morph:morphABSF_D_FIDR2R3},
    [V850_IT_CEILF_DL_FIDR2R3]   = {arch:ISA_E2_FP, morph:morphCEILF_DL_FIDR2R3},
    [V850_IT_CEILF_DUL_FIDR2R3]  = {arch:ISA_E2_FP, morph:morphCEILF_DUL_FIDR2R3},
    [V850_IT_CEILF_DUW_FIDR2R3]  = {arch:ISA_E2_FP, morph:morphCEILF_DUW_FIDR2R3},
    [V850_IT_CVTF_DL_FIDR2R3]    = {arch:ISA_E2_FP, morph:morphCVTF_DL_FIDR2R3},
    [V850_IT_CVTF_DUL_FIDR2R3]   = {arch:ISA_E2_FP, morph:morphCVTF_DUL_FIDR2R3},
    [V850_IT_CVTF_ULD_FIDR2R3]   = {arch:ISA_E2_FP, morph:morphCVTF_ULD_FIDR2R3},
    [V850_IT_FLOORF_DL_FIDR2R3]  = {arch:ISA_E2_FP, morph:morphFLOORF_DL_FIDR2R3},
    [V850_IT_FLOORF_DUL_FIDR2R3] = {arch:ISA_E2_FP, morph:morphFLOORF_DUL_FIDR2R3},
    [V850_IT_FLOORF_DUW_FIDR2R3] = {arch:ISA_E2_FP, morph:morphFLOORF_DUW_FIDR2R3},
    [V850_IT_NEGF_D_FIDR2R3]     = {arch:ISA_E2_FP, morph:morphNEGF_D_FIDR2R3},
    [V850_IT_RECIPF_D_FIDR2R3]   = {arch:ISA_E2_FP, morph:morphRECIPF_D_FIDR2R3},
    [V850_IT_RSQRTF_D_FIDR2R3]   = {arch:ISA_E2_FP, morph:morphRSQRTF_D_FIDR2R3},
    [V850_IT_SQRTF_D_FIDR2R3]    = {arch:ISA_E2_FP, morph:morphSQRTF_D_FIDR2R3},
    [V850_IT_TRNCF_DL_FIDR2R3]   = {arch:ISA_E2_FP, morph:morphTRNCF_DL_FIDR2R3},
    [V850_IT_TRNCF_DUL_FIDR2R3]  = {arch:ISA_E2_FP, morph:morphTRNCF_DUL_FIDR2R3},
    [V850_IT_TRNCF_DUW_FIDR2R3]  = {arch:ISA_E2_FP, morph:morphTRNCF_DUW_FIDR2R3},

    //
    // Format FII Insns
    //
    [V850_IT_ABSF_S_FII]  = {arch:ISA_E1_FP, morph:morphABSF_S_FII},
    [V850_IT_CVT_SW_FII]  = {arch:ISA_E1_FP, morph:morphCVT_SW_FII},
    [V850_IT_CVT_WS_FII]  = {arch:ISA_E1_FP, morph:morphCVT_WS_FII},
    [V850_IT_NEGF_S_FII]  = {arch:ISA_E1_FP, morph:morphNEGF_S_FII},
    [V850_IT_TRNC_SW_FII] = {arch:ISA_E1_FP, morph:morphTRNC_SW_FII},

    //
    // Format FIS Insns
    //
    [V850_IT_ADDF_S_FIS] = {arch:ISA_E2_FP, morph:morphADDF_S_FIS},
    [V850_IT_DIVF_S_FIS] = {arch:ISA_E2_FP, morph:morphDIVF_S_FIS},
    [V850_IT_MAXF_S_FIS] = {arch:ISA_E2_FP, morph:morphMAXF_S_FIS},
    [V850_IT_MINF_S_FIS] = {arch:ISA_E2_FP, morph:morphMINF_S_FIS},
    [V850_IT_MULF_S_FIS] = {arch:ISA_E2_FP, morph:morphMULF_S_FIS},
    [V850_IT_SUBF_S_FIS] = {arch:ISA_E2_FP, morph:morphSUBF_S_FIS},

    //
    // Format FISDr2r3 Insns
    //
    [V850_IT_CEILF_SL_FISDR2R3]   = {arch:ISA_E2_FP, morph:morphCEILF_SL_FISDR2R3},
    [V850_IT_CEILF_SUL_FISDR2R3]  = {arch:ISA_E2_FP, morph:morphCEILF_SUL_FISDR2R3},
    [V850_IT_CVTF_SD_FISDR2R3]    = {arch:ISA_E2_FP, morph:morphCVTF_SD_FISDR2R3},
    [V850_IT_CVTF_SL_FISDR2R3]    = {arch:ISA_E2_FP, morph:morphCVTF_SL_FISDR2R3},
    [V850_IT_CVTF_SUL_FISDR2R3]   = {arch:ISA_E2_FP, morph:morphCVTF_SUL_FISDR2R3},
    [V850_IT_CVTF_UWD_FISDR2R3]   = {arch:ISA_E2_FP, morph:morphCVTF_UWD_FISDR2R3},
    [V850_IT_CVTF_WD_FISDR2R3]    = {arch:ISA_E2_FP, morph:morphCVTF_WD_FISDR2R3},
    [V850_IT_FLOORF_SL_FISDR2R3]  = {arch:ISA_E2_FP, morph:morphFLOORF_SL_FISDR2R3},
    [V850_IT_FLOORF_SUL_FISDR2R3] = {arch:ISA_E2_FP, morph:morphFLOORF_SUL_FISDR2R3},
    [V850_IT_TRNCF_SL_FISDR2R3]   = {arch:ISA_E2_FP, morph:morphTRNCF_SL_FISDR2R3},
    [V850_IT_TRNCF_SUL_FISDR2R3]  = {arch:ISA_E2_FP, morph:morphTRNCF_SUL_FISDR2R3},

    //
    // Format FISa Insns
    //
    [V850_IT_MADDF_S_FISA]  = {arch:ISA_E2_XCL, morph:morphMADDF_S_FISA},
    [V850_IT_MSUBF_S_FISA]  = {arch:ISA_E2_XCL, morph:morphMSUBF_S_FISA},
    [V850_IT_NMADDF_S_FISA] = {arch:ISA_E2_XCL, morph:morphNMADDF_S_FISA},
    [V850_IT_NMSUBF_S_FISA] = {arch:ISA_E2_XCL, morph:morphNMSUBF_S_FISA},

    //
    // Format FIScond Insns
    //
    [V850_IT_CMPF_S_FISCOND] = {arch:ISA_E2_FP, morph:morphCMPF_S_FISCOND},

    //
    // Format FISfff Insns
    //
    [V850_IT_CMOVF_S_FISFFF] = {arch:ISA_E2_FP, morph:morphCMOVF_S_FISFFF},

    //
    // Format FISr2r3 Insns
    //
    [V850_IT_ABSF_S_FISR2R3]     = {arch:ISA_E2_FP, morph:morphABSF_S_FISR2R3},
    [V850_IT_CEILF_SUW_FISR2R3]  = {arch:ISA_E2_FP, morph:morphCEILF_SUW_FISR2R3},
    [V850_IT_CEILF_SW_FISR2R3]   = {arch:ISA_E2_FP, morph:morphCEILF_SW_FISR2R3},
    [V850_IT_CVTF_LD_FISR2R3]    = {arch:ISA_E2_FP, morph:morphCVTF_LD_FISR2R3},
    [V850_IT_CVTF_SUW_FISR2R3]   = {arch:ISA_E2_FP, morph:morphCVTF_SUW_FISR2R3},
    [V850_IT_CVTF_SW_FISR2R3]    = {arch:ISA_E2_FP, morph:morphCVTF_SW_FISR2R3},
    [V850_IT_CVTF_UWS_FISR2R3]   = {arch:ISA_E2_FP, morph:morphCVTF_UWS_FISR2R3},
    [V850_IT_CVTF_WS_FISR2R3]    = {arch:ISA_E2_FP, morph:morphCVTF_WS_FISR2R3},
    [V850_IT_FLOORF_SUW_FISR2R3] = {arch:ISA_E2_FP, morph:morphFLOORF_SUW_FISR2R3},
    [V850_IT_FLOORF_SW_FISR2R3]  = {arch:ISA_E2_FP, morph:morphFLOORF_SW_FISR2R3},
    [V850_IT_NEGF_S_FISR2R3]     = {arch:ISA_E2_FP, morph:morphNEGF_S_FISR2R3},
    [V850_IT_RECIPF_S_FISR2R3]   = {arch:ISA_E2_FP, morph:morphRECIPF_S_FISR2R3},
    [V850_IT_RSQRTF_S_FISR2R3]   = {arch:ISA_E2_FP, morph:morphRSQRTF_S_FISR2R3},
    [V850_IT_SQRTF_S_FISR2R3]    = {arch:ISA_E2_FP, morph:morphSQRTF_S_FISR2R3},
    [V850_IT_TRNCF_SUW_FISR2R3]  = {arch:ISA_E2_FP, morph:morphTRNCF_SUW_FISR2R3},
    [V850_IT_TRNCF_SW_FISR2R3]   = {arch:ISA_E2_FP, morph:morphTRNCF_SW_FISR2R3},

    //
    // Format FIV Insns
    //
    [V850_IT_TRFF_FIV] = {arch:ISA_E1_FP, morph:morphTRFF_FIV},

    //
    // Format FIVr2a Insns
    //
    [V850_IT_LDFF_FIVR2A] = {arch:ISA_E1_FP, morph:morphLDFF_FIVR2A},

    //
    // Format FIVr2b Insns
    //
    [V850_IT_LDFC_FIVR2B] = {arch:ISA_E1_FP, morph:morphLDFC_FIVR2B},

    //
    // Format FIVr3a Insns
    //
    [V850_IT_STFF_FIVR3A] = {arch:ISA_E1_FP, morph:morphSTFF_FIVR3A},

    //
    // Format FIVr3b Insns
    //
    [V850_IT_STFC_FIVR3B] = {arch:ISA_E1_FP, morph:morphSTFC_FIVR3B},

    //
    // Format FIfff Insns
    //
    [V850_IT_TRFSR_FIFFF] = {arch:ISA_E2_FP, morph:morphTRFSR_FIFFF},

    //
    // RH850 Only
    //
    // New
    [V850_IT_LDL_W_F07D]     = {arch:ISA_E3, morph:morphLDL_W_F07D},
    [V850_IT_STC_W_F07D]     = {arch:ISA_E3, morph:morphSTC_W_F07D},
    [V850_IT_BINS_F09RPWR_0] = {arch:ISA_E3, morph:morphBINS_F09RPWR_0},
    [V850_IT_BINS_F09RPWR_1] = {arch:ISA_E3, morph:morphBINS_F09RPWR_1},
    [V850_IT_BINS_F09RPWR_2] = {arch:ISA_E3, morph:morphBINS_F09RPWR_2},
    [V850_IT_CLL_F10]        = {arch:ISA_E3, morph:morphCLL_F10},
    [V850_IT_SNOOZE_F10]     = {arch:ISA_E3, morph:morphSNOOZE_F10},
    [V850_IT_PUSHSP_F11]     = {arch:ISA_E3, morph:morphPUSHSP_F11},
    [V850_IT_POPSP_F11]      = {arch:ISA_E3, morph:morphPOPSP_F11},
    [V850_IT_ROTL_F07RRR]    = {arch:ISA_E3, morph:morphROTL_F07RRR},
    [V850_IT_ROTL_F07IRR]    = {arch:ISA_E3, morph:morphROTL_F07IRR},
    [V850_IT_LD_DW_F14]      = {arch:ISA_E3, morph:morphLD_DW_F14},
    [V850_IT_ST_DW_F14]      = {arch:ISA_E3, morph:morphST_DW_F14},
    // New Branch instructions
    [V850_IT_BCOND_F07CC]    = {arch:ISA_E3, morph:morphBCOND_F07CC},
    [V850_IT_JARL_F11D]      = {arch:ISA_E3, morph:morphJARL_F11D},
    [V850_IT_LOOP_F07RI]     = {arch:ISA_E3, morph:morphLOOP_F07RI},
    // New - but not indicated
    [V850_IT_LD_B_F14]       = {arch:ISA_E3, morph:morphLD_B_F14},
    [V850_IT_LD_BU_F14]      = {arch:ISA_E3, morph:morphLD_BU_F14},
    [V850_IT_LD_H_F14]       = {arch:ISA_E3, morph:morphLD_H_F14},
    [V850_IT_LD_HU_F14]      = {arch:ISA_E3, morph:morphLD_HU_F14},
    [V850_IT_LD_W_F14]       = {arch:ISA_E3, morph:morphLD_W_F14},
    [V850_IT_ST_B_F14]       = {arch:ISA_E3, morph:morphST_B_F14},
    [V850_IT_ST_H_F14]       = {arch:ISA_E3, morph:morphST_H_F14},
    [V850_IT_ST_W_F14]       = {arch:ISA_E3, morph:morphST_W_F14},
    [V850_IT_CACHE_F10]      = {arch:ISA_E3, morph:morphCACHE_F10},

    [V850_IT_CACHE_CHBII]    = {arch:ISA_E3, morph:morphCACHE_CHBII},
    [V850_IT_CACHE_CIBII]    = {arch:ISA_E3, morph:morphCACHE_CIBII},
    [V850_IT_CACHE_CFALI]    = {arch:ISA_E3, morph:morphCACHE_CFALI},
    [V850_IT_CACHE_CISTI]    = {arch:ISA_E3, morph:morphCACHE_CISTI},
    [V850_IT_CACHE_CILDI]    = {arch:ISA_E3, morph:morphCACHE_CILDI},

    [V850_IT_PREF_F10]       = {arch:ISA_E3, morph:morphPREF_F10},
    [V850_IT_PREFI_F10]      = {arch:ISA_E3, morph:morphPREFI_F10},

    [V850_IT_SYSCALL_F10C]   = {arch:ISA_E3, morph:morphSYSCALL_F10C},
    [V850_IT_SYNCE_F01A]     = {arch:ISA_E3, morph:morphSYNCE_F01A},
    [V850_IT_SYNCI_F01A]     = {arch:ISA_E3, morph:morphSYNCI_F01A},

    [V850_IT_CVTF_HS_FI]     = {arch:ISA_E3_FP, morph:morphCVTF_HS_FI},
    [V850_IT_CVTF_SH_FI]     = {arch:ISA_E3_FP, morph:morphCVTF_SH_FI},

    [V850_IT_FMAF_S_FI]      = {arch:ISA_E3_FP, morph:morphFMAF_S_FI},
    [V850_IT_FMSF_S_FI]      = {arch:ISA_E3_FP, morph:morphFMSF_S_FI},
    [V850_IT_FNMAF_S_FI]     = {arch:ISA_E3_FP, morph:morphFNMAF_S_FI},
    [V850_IT_FNMSF_S_FI]     = {arch:ISA_E3_FP, morph:morphFNMSF_S_FI},


};

//
// Default undecoded/badvariant/unimplemented instruction behavior
//
static void defaultMorphCallback(
    vmiProcessorP processor,
    v850Addr thisPC,
    Uns64 instruction,
    char *message
) {
    vmiPrintf(
        "CPU '%s' 0x%08x:" FMT_640Nx " *** %s instruction: exiting ***\n",
        vmirtProcessorName(processor),
        thisPC,
        instruction,
        message
    );
    vmirtExit(processor);
}


//
// Default morphed code call
//
static V850_MORPH_FN(emitUndefined) {
    vmimtArgProcessor();
    vmimtArgUns32(state->info.thisPC);
    vmimtArgUns64(state->info.instruction);
    vmimtArgNatAddress("undecoded");
    vmimtCall((vmiCallFn)defaultMorphCallback);
    vmimtEndBlock();
}
static V850_MORPH_FN(emitNotVariant) {
    vmimtArgProcessor();
    vmimtArgUns32(state->info.thisPC);
    vmimtArgUns64(state->info.instruction);
    vmimtArgNatAddress("badvariant");
    vmimtCall((vmiCallFn)defaultMorphCallback);
    vmimtEndBlock();
}
static V850_MORPH_FN(emitUnimplemented) {
    vmimtArgProcessor();
    vmimtArgUns32(state->info.thisPC);
    vmimtArgUns64(state->info.instruction);
    vmimtArgNatAddress("unimplemented");
    vmimtCall((vmiCallFn)defaultMorphCallback);
    vmimtEndBlock();
}

static Bool disableMorph(v850MorphStateP state) {
    v850P v850 = state->v850;
    if(!V850_DISASSEMBLE(v850)) {
        return False;
    } else if (state->info.type==V850_IT_LAST) {
        return False;
    } else {
        return True;
    }
}

//
// Call to implemented morph code instruction generator
//
static V850_MORPH_FN(emitImplemented) {
    state->attrs->morph(state);
}

//
// Return a boolean indicating whether the processor supports the required
// architecture
//
static Bool supportedOnVariant(v850P v850, v850MorphStateP state) {

    v850Architecture configVariant   = v850->configInfo.arch;
    v850Architecture requiredVariant = state->attrs->arch;

    //
    // If we have no fpu, remove this from the config variant
    //
    if (v850->params.nofpu) {
        configVariant &= ~(ISA_E1_FP | ISA_E2_FP | ISA_E3_FP);
    }

    if (configVariant & requiredVariant) {
        return True;
    } else {
        return False;
    }
}

//
// Instruction Morpher
//
VMI_MORPH_FN(v850Morph) {
    v850P v850 = (v850P)processor;
    v850MorphState state;

    // get instruction and instruction type
    v850Decode(v850, thisPC, &state.info);

    state.attrs = &dispatchTable[state.info.type];
    state.blockState = blockState;
    state.v850 = v850;

    //VMI_ASSERT((state.info.class != OCL_IC_NONE), "Error no IA Class defined");
    vmimtInstructionClassAdd(state.info.class);

    if(disableMorph(&state)) {
        // no action if in disassembly mode

    } else if(state.info.type==V850_IT_LAST) {
        // take UndefinedInstruction exception
        emitUndefined(&state);
    } else if(!supportedOnVariant(v850, &state)) {
        // instruction not supported on this variant
        emitNotVariant(&state);
    } else if(state.attrs->morph) {
        // translate the instruction
        emitImplemented(&state);
    } else {
        // here if no morph callback specified
        emitUnimplemented(&state);
    }
}

VMI_FETCH_SNAP_FN(v850FetchSnap) {
    return thisPC;
}

VMI_RD_WR_SNAP_FN(v850RdSnap) {
    return bytes;
}

VMI_RD_WR_SNAP_FN(v850WrSnap) {
    return bytes;
}

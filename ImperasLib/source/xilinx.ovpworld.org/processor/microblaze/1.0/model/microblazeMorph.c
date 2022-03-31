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
#include "microblazeMorph.h"
#include "microblazeDecode.h"
#include "microblazeExceptions.h"
#include "microblazeInstructions.h"
#include "microblazeStructure.h"

//
// Write Morpher Table
//
const static microblazeMorphAttr dispatchTable[MICROBLAZE_IT_LAST+1] = {
    //
    // Format TypeA1 Insns
    //
    [MICROBLAZE_IT_ADD_TYPEA1]    = {arch:ISA_V7_00, morph:morphADD_TYPEA1},
    [MICROBLAZE_IT_ADDC_TYPEA1]   = {arch:ISA_V7_00, morph:morphADDC_TYPEA1},
    [MICROBLAZE_IT_ADDK_TYPEA1]   = {arch:ISA_V7_00, morph:morphADDK_TYPEA1},
    [MICROBLAZE_IT_ADDKC_TYPEA1]  = {arch:ISA_V7_00, morph:morphADDKC_TYPEA1},
    [MICROBLAZE_IT_AND_TYPEA1]    = {arch:ISA_V7_00, morph:morphAND_TYPEA1},
    [MICROBLAZE_IT_ANDN_TYPEA1]   = {arch:ISA_V7_00, morph:morphANDN_TYPEA1},
    [MICROBLAZE_IT_FADD_TYPEA1]   = {arch:ISA_V7_00, morph:morphFADD_TYPEA1},
    [MICROBLAZE_IT_FCMPEQ_TYPEA1] = {arch:ISA_V7_00, morph:morphFCMPEQ_TYPEA1},
    [MICROBLAZE_IT_FCMPGE_TYPEA1] = {arch:ISA_V7_00, morph:morphFCMPGE_TYPEA1},
    [MICROBLAZE_IT_FCMPGT_TYPEA1] = {arch:ISA_V7_00, morph:morphFCMPGT_TYPEA1},
    [MICROBLAZE_IT_FCMPLE_TYPEA1] = {arch:ISA_V7_00, morph:morphFCMPLE_TYPEA1},
    [MICROBLAZE_IT_FCMPLT_TYPEA1] = {arch:ISA_V7_00, morph:morphFCMPLT_TYPEA1},
    [MICROBLAZE_IT_FCMPNE_TYPEA1] = {arch:ISA_V7_00, morph:morphFCMPNE_TYPEA1},
    [MICROBLAZE_IT_FCMPUN_TYPEA1] = {arch:ISA_V7_00, morph:morphFCMPUN_TYPEA1},
    [MICROBLAZE_IT_FDIV_TYPEA1]   = {arch:ISA_V7_00, morph:morphFDIV_TYPEA1},
    [MICROBLAZE_IT_FMUL_TYPEA1]   = {arch:ISA_V7_00, morph:morphFMUL_TYPEA1},
    [MICROBLAZE_IT_FRSUB_TYPEA1]  = {arch:ISA_V7_00, morph:morphFRSUB_TYPEA1},
    [MICROBLAZE_IT_LWX_TYPEA1]    = {arch:ISA_V7_00, morph:morphLWX_TYPEA1},
    [MICROBLAZE_IT_MUL_TYPEA1]    = {arch:ISA_V7_00, morph:morphMUL_TYPEA1},
    [MICROBLAZE_IT_MULH_TYPEA1]   = {arch:ISA_V7_00, morph:morphMULH_TYPEA1},
    [MICROBLAZE_IT_MULHSU_TYPEA1] = {arch:ISA_V7_00, morph:morphMULHSU_TYPEA1},
    [MICROBLAZE_IT_MULHU_TYPEA1]  = {arch:ISA_V7_00, morph:morphMULHU_TYPEA1},
    [MICROBLAZE_IT_OR_TYPEA1]     = {arch:ISA_V7_00, morph:morphOR_TYPEA1},
    [MICROBLAZE_IT_PCMPBF_TYPEA1] = {arch:ISA_V7_00, morph:morphPCMPBF_TYPEA1},
    [MICROBLAZE_IT_PCMPEQ_TYPEA1] = {arch:ISA_V7_00, morph:morphPCMPEQ_TYPEA1},
    [MICROBLAZE_IT_PCMPNE_TYPEA1] = {arch:ISA_V7_00, morph:morphPCMPNE_TYPEA1},
    [MICROBLAZE_IT_RSUB_TYPEA1]   = {arch:ISA_V7_00, morph:morphRSUB_TYPEA1},
    [MICROBLAZE_IT_RSUBC_TYPEA1]  = {arch:ISA_V7_00, morph:morphRSUBC_TYPEA1},
    [MICROBLAZE_IT_RSUBK_TYPEA1]  = {arch:ISA_V7_00, morph:morphRSUBK_TYPEA1},
    [MICROBLAZE_IT_RSUBKC_TYPEA1] = {arch:ISA_V7_00, morph:morphRSUBKC_TYPEA1},
    [MICROBLAZE_IT_SWX_TYPEA1]    = {arch:ISA_V7_00, morph:morphSWX_TYPEA1},
    [MICROBLAZE_IT_XOR_TYPEA1]    = {arch:ISA_V7_00, morph:morphXOR_TYPEA1},

    //
    // Format TypeA2 Insns
    //
    [MICROBLAZE_IT_BEQ_TYPEA2]  = {arch:ISA_V7_00, morph:morphBEQ_TYPEA2},
    [MICROBLAZE_IT_BEQD_TYPEA2] = {arch:ISA_V7_00, morph:morphBEQD_TYPEA2},
    [MICROBLAZE_IT_BGE_TYPEA2]  = {arch:ISA_V7_00, morph:morphBGE_TYPEA2},
    [MICROBLAZE_IT_BGED_TYPEA2] = {arch:ISA_V7_00, morph:morphBGED_TYPEA2},
    [MICROBLAZE_IT_BGT_TYPEA2]  = {arch:ISA_V7_00, morph:morphBGT_TYPEA2},
    [MICROBLAZE_IT_BGTD_TYPEA2] = {arch:ISA_V7_00, morph:morphBGTD_TYPEA2},
    [MICROBLAZE_IT_BLE_TYPEA2]  = {arch:ISA_V7_00, morph:morphBLE_TYPEA2},
    [MICROBLAZE_IT_BLED_TYPEA2] = {arch:ISA_V7_00, morph:morphBLED_TYPEA2},
    [MICROBLAZE_IT_BLT_TYPEA2]  = {arch:ISA_V7_00, morph:morphBLT_TYPEA2},
    [MICROBLAZE_IT_BLTD_TYPEA2] = {arch:ISA_V7_00, morph:morphBLTD_TYPEA2},
    [MICROBLAZE_IT_BNE_TYPEA2]  = {arch:ISA_V7_00, morph:morphBNE_TYPEA2},
    [MICROBLAZE_IT_BNED_TYPEA2] = {arch:ISA_V7_00, morph:morphBNED_TYPEA2},

    //
    // Format TypeA3 Insns
    //
    [MICROBLAZE_IT_BR_TYPEA3]   = {arch:ISA_V7_00, morph:morphBR_TYPEA3},
    [MICROBLAZE_IT_BRA_TYPEA3]  = {arch:ISA_V7_00, morph:morphBRA_TYPEA3},
    [MICROBLAZE_IT_BRAD_TYPEA3] = {arch:ISA_V7_00, morph:morphBRAD_TYPEA3},
    [MICROBLAZE_IT_BRD_TYPEA3]  = {arch:ISA_V7_00, morph:morphBRD_TYPEA3},

    //
    // Format TypeA4 Insns
    //
    [MICROBLAZE_IT_BRALD_TYPEA4] = {arch:ISA_V7_00, morph:morphBRALD_TYPEA4},
    [MICROBLAZE_IT_BRLD_TYPEA4]  = {arch:ISA_V7_00, morph:morphBRLD_TYPEA4},

    //
    // Format TypeA5 Insns
    //
    [MICROBLAZE_IT_BRK_TYPEA5] = {arch:ISA_V7_00, morph:morphBRK_TYPEA5},

    //
    // Format TypeA6 Insns
    //
    [MICROBLAZE_IT_BSLL_TYPEA6] = {arch:ISA_V7_00, morph:morphBSLL_TYPEA6},
    [MICROBLAZE_IT_BSRA_TYPEA6] = {arch:ISA_V7_00, morph:morphBSRA_TYPEA6},
    [MICROBLAZE_IT_BSRL_TYPEA6] = {arch:ISA_V7_00, morph:morphBSRL_TYPEA6},

    //
    // Format TypeA7 Insns
    //
    [MICROBLAZE_IT_CMP_TYPEA7] = {arch:ISA_V7_00, morph:morphCMP_TYPEA7},
    [MICROBLAZE_IT_CMPU_TYPEA7] = {arch:ISA_V7_00, morph:morphCMPU_TYPEA7},
    [MICROBLAZE_IT_IDIV_TYPEA7] = {arch:ISA_V7_00, morph:morphIDIV_TYPEA7},
    [MICROBLAZE_IT_IDIVU_TYPEA7] = {arch:ISA_V7_00, morph:morphIDIVU_TYPEA7},

    //
    // Format TypeA8 Insns
    //
    [MICROBLAZE_IT_LBU_TYPEA8]  = {arch:ISA_V7_00, morph:morphLBU_TYPEA8},
    [MICROBLAZE_IT_LBUR_TYPEA8] = {arch:ISA_V7_00, morph:morphLBUR_TYPEA8},
    [MICROBLAZE_IT_LHU_TYPEA8]  = {arch:ISA_V7_00, morph:morphLHU_TYPEA8},
    [MICROBLAZE_IT_LHUR_TYPEA8] = {arch:ISA_V7_00, morph:morphLHUR_TYPEA8},
    [MICROBLAZE_IT_LW_TYPEA8]   = {arch:ISA_V7_00, morph:morphLW_TYPEA8},
    [MICROBLAZE_IT_LWR_TYPEA8]  = {arch:ISA_V7_00, morph:morphLWR_TYPEA8},
    [MICROBLAZE_IT_SB_TYPEA8]   = {arch:ISA_V7_00, morph:morphSB_TYPEA8},
    [MICROBLAZE_IT_SBR_TYPEA8]  = {arch:ISA_V7_00, morph:morphSBR_TYPEA8},
    [MICROBLAZE_IT_SH_TYPEA8]   = {arch:ISA_V7_00, morph:morphSH_TYPEA8},
    [MICROBLAZE_IT_SHR_TYPEA8]  = {arch:ISA_V7_00, morph:morphSHR_TYPEA8},
    [MICROBLAZE_IT_SW_TYPEA8]   = {arch:ISA_V7_00, morph:morphSW_TYPEA8},
    [MICROBLAZE_IT_SWR_TYPEA8]  = {arch:ISA_V7_00, morph:morphSWR_TYPEA8},

    //
    // Format TypeA9 Insns
    //
    [MICROBLAZE_IT_MFS_TYPEA9] = {arch:ISA_V7_00, morph:morphMFS_TYPEA9},

    //
    // Format TypeAa Insns
    //
    [MICROBLAZE_IT_MTS_TYPEAA] = {arch:ISA_V7_00, morph:morphMTS_TYPEAA},

    //
    // Format TypeAb Insns
    //
    [MICROBLAZE_IT_CLZ_TYPEAB]    = {arch:ISA_V7_00, morph:morphCLZ_TYPEAB},
    [MICROBLAZE_IT_FINT_TYPEAB]   = {arch:ISA_V7_00, morph:morphFINT_TYPEAB},
    [MICROBLAZE_IT_FLT_TYPEAB]    = {arch:ISA_V7_00, morph:morphFLT_TYPEAB},
    [MICROBLAZE_IT_FSQRT_TYPEAB]  = {arch:ISA_V7_00, morph:morphFSQRT_TYPEAB},
    [MICROBLAZE_IT_SEXT16_TYPEAB] = {arch:ISA_V7_00, morph:morphSEXT16_TYPEAB},
    [MICROBLAZE_IT_SEXT8_TYPEAB]  = {arch:ISA_V7_00, morph:morphSEXT8_TYPEAB},
    [MICROBLAZE_IT_SRA_TYPEAB]    = {arch:ISA_V7_00, morph:morphSRA_TYPEAB},
    [MICROBLAZE_IT_SRC_TYPEAB]    = {arch:ISA_V7_00, morph:morphSRC_TYPEAB},
    [MICROBLAZE_IT_SRL_TYPEAB]    = {arch:ISA_V7_00, morph:morphSRL_TYPEAB},
    [MICROBLAZE_IT_SWAPB_TYPEAB]  = {arch:ISA_V9_50, morph:morphSWAPB_TYPEAB},
    [MICROBLAZE_IT_SWAPH_TYPEAB]  = {arch:ISA_V9_50, morph:morphSWAPH_TYPEAB},

    //
    // Format TypeAc Insns
    //
    [MICROBLAZE_IT_WDC_TYPEAC]    = {arch:ISA_V7_00, morph:morphWDC_TYPEAC},
    [MICROBLAZE_IT_WDCCLR_TYPEAC] = {arch:ISA_V7_00, morph:morphWDCCLR_TYPEAC},
    [MICROBLAZE_IT_WDCFL_TYPEAC]  = {arch:ISA_V7_00, morph:morphWDCFL_TYPEAC},
    [MICROBLAZE_IT_WIC_TYPEAC]    = {arch:ISA_V7_00, morph:morphWIC_TYPEAC},

    //
    // Format TypeB1 Insns
    //
    [MICROBLAZE_IT_ADDI_TYPEB1]    = {arch:ISA_V7_00, morph:morphADDI_TYPEB1},
    [MICROBLAZE_IT_ADDIC_TYPEB1]   = {arch:ISA_V7_00, morph:morphADDIC_TYPEB1},
    [MICROBLAZE_IT_ADDIK_TYPEB1]   = {arch:ISA_V7_00, morph:morphADDIK_TYPEB1},
    [MICROBLAZE_IT_ADDIKC_TYPEB1]  = {arch:ISA_V7_00, morph:morphADDIKC_TYPEB1},
    [MICROBLAZE_IT_ANDI_TYPEB1]    = {arch:ISA_V7_00, morph:morphANDI_TYPEB1},
    [MICROBLAZE_IT_ANDNI_TYPEB1]   = {arch:ISA_V7_00, morph:morphANDNI_TYPEB1},
    [MICROBLAZE_IT_LBUI_TYPEB1]    = {arch:ISA_V7_00, morph:morphLBUI_TYPEB1},
    [MICROBLAZE_IT_LHUI_TYPEB1]    = {arch:ISA_V7_00, morph:morphLHUI_TYPEB1},
    [MICROBLAZE_IT_LWI_TYPEB1]     = {arch:ISA_V7_00, morph:morphLWI_TYPEB1},
    [MICROBLAZE_IT_MULI_TYPEB1]    = {arch:ISA_V7_00, morph:morphMULI_TYPEB1},
    [MICROBLAZE_IT_ORI_TYPEB1]     = {arch:ISA_V7_00, morph:morphORI_TYPEB1},
    [MICROBLAZE_IT_RSUBI_TYPEB1]   = {arch:ISA_V7_00, morph:morphRSUBI_TYPEB1},
    [MICROBLAZE_IT_RSUBIC_TYPEB1]  = {arch:ISA_V7_00, morph:morphRSUBIC_TYPEB1},
    [MICROBLAZE_IT_RSUBIK_TYPEB1]  = {arch:ISA_V7_00, morph:morphRSUBIK_TYPEB1},
    [MICROBLAZE_IT_RSUBIKC_TYPEB1] = {arch:ISA_V7_00, morph:morphRSUBIKC_TYPEB1},
    [MICROBLAZE_IT_SBI_TYPEB1]     = {arch:ISA_V7_00, morph:morphSBI_TYPEB1},
    [MICROBLAZE_IT_SHI_TYPEB1]     = {arch:ISA_V7_00, morph:morphSHI_TYPEB1},
    [MICROBLAZE_IT_SWI_TYPEB1]     = {arch:ISA_V7_00, morph:morphSWI_TYPEB1},
    [MICROBLAZE_IT_XORI_TYPEB1]    = {arch:ISA_V7_00, morph:morphXORI_TYPEB1},

    //
    // Format TypeB2 Insns
    //
    [MICROBLAZE_IT_BEQI_TYPEB2]  = {arch:ISA_V7_00, morph:morphBEQI_TYPEB2},
    [MICROBLAZE_IT_BEQID_TYPEB2] = {arch:ISA_V7_00, morph:morphBEQID_TYPEB2},
    [MICROBLAZE_IT_BGEI_TYPEB2]  = {arch:ISA_V7_00, morph:morphBGEI_TYPEB2},
    [MICROBLAZE_IT_BGEID_TYPEB2] = {arch:ISA_V7_00, morph:morphBGEID_TYPEB2},
    [MICROBLAZE_IT_BGTI_TYPEB2]  = {arch:ISA_V7_00, morph:morphBGTI_TYPEB2},
    [MICROBLAZE_IT_BGTID_TYPEB2] = {arch:ISA_V7_00, morph:morphBGTID_TYPEB2},
    [MICROBLAZE_IT_BLEI_TYPEB2]  = {arch:ISA_V7_00, morph:morphBLEI_TYPEB2},
    [MICROBLAZE_IT_BLEID_TYPEB2] = {arch:ISA_V7_00, morph:morphBLEID_TYPEB2},
    [MICROBLAZE_IT_BLTI_TYPEB2]  = {arch:ISA_V7_00, morph:morphBLTI_TYPEB2},
    [MICROBLAZE_IT_BLTID_TYPEB2] = {arch:ISA_V7_00, morph:morphBLTID_TYPEB2},
    [MICROBLAZE_IT_BNEI_TYPEB2]  = {arch:ISA_V7_00, morph:morphBNEI_TYPEB2},
    [MICROBLAZE_IT_BNEID_TYPEB2] = {arch:ISA_V7_00, morph:morphBNEID_TYPEB2},

    //
    // Format TypeB3 Insns
    //
    [MICROBLAZE_IT_BRAI_TYPEB3]  = {arch:ISA_V7_00, morph:morphBRAI_TYPEB3},
    [MICROBLAZE_IT_BRAID_TYPEB3] = {arch:ISA_V7_00, morph:morphBRAID_TYPEB3},
    [MICROBLAZE_IT_BRI_TYPEB3]   = {arch:ISA_V7_00, morph:morphBRI_TYPEB3},
    [MICROBLAZE_IT_BRID_TYPEB3]  = {arch:ISA_V7_00, morph:morphBRID_TYPEB3},

    //
    // Format TypeB4 Insns
    //
    [MICROBLAZE_IT_BRALID_TYPEB4] = {arch:ISA_V7_00, morph:morphBRALID_TYPEB4},
    [MICROBLAZE_IT_BRLID_TYPEB4]  = {arch:ISA_V7_00, morph:morphBRLID_TYPEB4},

    //
    // Format TypeB5 Insns
    //
    [MICROBLAZE_IT_BRKI_TYPEB5] = {arch:ISA_V7_00, morph:morphBRKI_TYPEB5},

    //
    // Format TypeB6 Insns
    //
    [MICROBLAZE_IT_BSLLI_TYPEB6] = {arch:ISA_V7_00, morph:morphBSLLI_TYPEB6},
    [MICROBLAZE_IT_BSRAI_TYPEB6] = {arch:ISA_V7_00, morph:morphBSRAI_TYPEB6},
    [MICROBLAZE_IT_BSRLI_TYPEB6] = {arch:ISA_V7_00, morph:morphBSRLI_TYPEB6},

    //
    // Format TypeB8 Insns
    //
    [MICROBLAZE_IT_MBAR_TYPEB8] = {arch:ISA_V7_00, morph:morphMBAR_TYPEB8},

    //
    // Format TypeB9 Insns
    //
    [MICROBLAZE_IT_MSRCLR_TYPEB9] = {arch:ISA_V7_00, morph:morphMSRCLR_TYPEB9},
    [MICROBLAZE_IT_MSRSET_TYPEB9] = {arch:ISA_V7_00, morph:morphMSRSET_TYPEB9},

    //
    // Format TypeBa Insns
    //
    [MICROBLAZE_IT_RTBD_TYPEBA] = {arch:ISA_V7_00, morph:morphRTBD_TYPEBA},
    [MICROBLAZE_IT_RTED_TYPEBA] = {arch:ISA_V7_00, morph:morphRTED_TYPEBA},
    [MICROBLAZE_IT_RTID_TYPEBA] = {arch:ISA_V7_00, morph:morphRTID_TYPEBA},
    [MICROBLAZE_IT_RTSD_TYPEBA] = {arch:ISA_V7_00, morph:morphRTSD_TYPEBA},

    //
    // Format TypeBbe Insns
    //
    [MICROBLAZE_IT_BSEFI_TYPEBBE] = {arch:ISA_V10_00, morph:morphBSEFI_TYPEBBE},

    //
    // Format TypeBbi Insns
    //
    [MICROBLAZE_IT_BSIFI_TYPEBBI] = {arch:ISA_V10_00, morph:morphBSIFI_TYPEBBI},

    //
    // Format TypeC1 Insns
    //
    [MICROBLAZE_IT_AGET_TYPEC1]     = {arch:ISA_V7_00, morph:morphAGET_TYPEC1},
    [MICROBLAZE_IT_CAGET_TYPEC1]    = {arch:ISA_V7_00, morph:morphCAGET_TYPEC1},
    [MICROBLAZE_IT_CGET_TYPEC1]     = {arch:ISA_V7_00, morph:morphCGET_TYPEC1},
    [MICROBLAZE_IT_EAGET_TYPEC1]    = {arch:ISA_V7_00, morph:morphEAGET_TYPEC1},
    [MICROBLAZE_IT_ECAGET_TYPEC1]   = {arch:ISA_V7_00, morph:morphECAGET_TYPEC1},
    [MICROBLAZE_IT_ECGET_TYPEC1]    = {arch:ISA_V7_00, morph:morphECGET_TYPEC1},
    [MICROBLAZE_IT_EGET_TYPEC1]     = {arch:ISA_V7_00, morph:morphEGET_TYPEC1},
    [MICROBLAZE_IT_GET_TYPEC1]      = {arch:ISA_V7_00, morph:morphGET_TYPEC1},
    [MICROBLAZE_IT_NAGET_TYPEC1]    = {arch:ISA_V7_00, morph:morphNAGET_TYPEC1},
    [MICROBLAZE_IT_NCAGET_TYPEC1]   = {arch:ISA_V7_00, morph:morphNCAGET_TYPEC1},
    [MICROBLAZE_IT_NCGET_TYPEC1]    = {arch:ISA_V7_00, morph:morphNCGET_TYPEC1},
    [MICROBLAZE_IT_NEAGET_TYPEC1]   = {arch:ISA_V7_00, morph:morphNEAGET_TYPEC1},
    [MICROBLAZE_IT_NECAGET_TYPEC1]  = {arch:ISA_V7_00, morph:morphNECAGET_TYPEC1},
    [MICROBLAZE_IT_NECGET_TYPEC1]   = {arch:ISA_V7_00, morph:morphNECGET_TYPEC1},
    [MICROBLAZE_IT_NEGET_TYPEC1]    = {arch:ISA_V7_00, morph:morphNEGET_TYPEC1},
    [MICROBLAZE_IT_NGET_TYPEC1]     = {arch:ISA_V7_00, morph:morphNGET_TYPEC1},
    [MICROBLAZE_IT_TAGET_TYPEC1]    = {arch:ISA_V7_00, morph:morphTAGET_TYPEC1},
    [MICROBLAZE_IT_TCAGET_TYPEC1]   = {arch:ISA_V7_00, morph:morphTCAGET_TYPEC1},
    [MICROBLAZE_IT_TCGET_TYPEC1]    = {arch:ISA_V7_00, morph:morphTCGET_TYPEC1},
    [MICROBLAZE_IT_TEAGET_TYPEC1]   = {arch:ISA_V7_00, morph:morphTEAGET_TYPEC1},
    [MICROBLAZE_IT_TECAGET_TYPEC1]  = {arch:ISA_V7_00, morph:morphTECAGET_TYPEC1},
    [MICROBLAZE_IT_TECGET_TYPEC1]   = {arch:ISA_V7_00, morph:morphTECGET_TYPEC1},
    [MICROBLAZE_IT_TEGET_TYPEC1]    = {arch:ISA_V7_00, morph:morphTEGET_TYPEC1},
    [MICROBLAZE_IT_TGET_TYPEC1]     = {arch:ISA_V7_00, morph:morphTGET_TYPEC1},
    [MICROBLAZE_IT_TNAGET_TYPEC1]   = {arch:ISA_V7_00, morph:morphTNAGET_TYPEC1},
    [MICROBLAZE_IT_TNCAGET_TYPEC1]  = {arch:ISA_V7_00, morph:morphTNCAGET_TYPEC1},
    [MICROBLAZE_IT_TNCGET_TYPEC1]   = {arch:ISA_V7_00, morph:morphTNCGET_TYPEC1},
    [MICROBLAZE_IT_TNEAGET_TYPEC1]  = {arch:ISA_V7_00, morph:morphTNEAGET_TYPEC1},
    [MICROBLAZE_IT_TNECAGET_TYPEC1] = {arch:ISA_V7_00, morph:morphTNECAGET_TYPEC1},
    [MICROBLAZE_IT_TNECGET_TYPEC1]  = {arch:ISA_V7_00, morph:morphTNECGET_TYPEC1},
    [MICROBLAZE_IT_TNEGET_TYPEC1]   = {arch:ISA_V7_00, morph:morphTNEGET_TYPEC1},
    [MICROBLAZE_IT_TNGET_TYPEC1]    = {arch:ISA_V7_00, morph:morphTNGET_TYPEC1},

    //
    // Format TypeC2 Insns
    //
    [MICROBLAZE_IT_AGETD_TYPEC2]     = {arch:ISA_V7_00, morph:morphAGETD_TYPEC2},
    [MICROBLAZE_IT_CAGETD_TYPEC2]    = {arch:ISA_V7_00, morph:morphCAGETD_TYPEC2},
    [MICROBLAZE_IT_CGETD_TYPEC2]     = {arch:ISA_V7_00, morph:morphCGETD_TYPEC2},
    [MICROBLAZE_IT_EAGETD_TYPEC2]    = {arch:ISA_V7_00, morph:morphEAGETD_TYPEC2},
    [MICROBLAZE_IT_ECAGETD_TYPEC2]   = {arch:ISA_V7_00, morph:morphECAGETD_TYPEC2},
    [MICROBLAZE_IT_ECGETD_TYPEC2]    = {arch:ISA_V7_00, morph:morphECGETD_TYPEC2},
    [MICROBLAZE_IT_EGETD_TYPEC2]     = {arch:ISA_V7_00, morph:morphEGETD_TYPEC2},
    [MICROBLAZE_IT_GETD_TYPEC2]      = {arch:ISA_V7_00, morph:morphGETD_TYPEC2},
    [MICROBLAZE_IT_NAGETD_TYPEC2]    = {arch:ISA_V7_00, morph:morphNAGETD_TYPEC2},
    [MICROBLAZE_IT_NCAGETD_TYPEC2]   = {arch:ISA_V7_00, morph:morphNCAGETD_TYPEC2},
    [MICROBLAZE_IT_NCGETD_TYPEC2]    = {arch:ISA_V7_00, morph:morphNCGETD_TYPEC2},
    [MICROBLAZE_IT_NEAGETD_TYPEC2]   = {arch:ISA_V7_00, morph:morphNEAGETD_TYPEC2},
    [MICROBLAZE_IT_NECAGETD_TYPEC2]  = {arch:ISA_V7_00, morph:morphNECAGETD_TYPEC2},
    [MICROBLAZE_IT_NECGETD_TYPEC2]   = {arch:ISA_V7_00, morph:morphNECGETD_TYPEC2},
    [MICROBLAZE_IT_NEGETD_TYPEC2]    = {arch:ISA_V7_00, morph:morphNEGETD_TYPEC2},
    [MICROBLAZE_IT_NGETD_TYPEC2]     = {arch:ISA_V7_00, morph:morphNGETD_TYPEC2},
    [MICROBLAZE_IT_TAGETD_TYPEC2]    = {arch:ISA_V7_00, morph:morphTAGETD_TYPEC2},
    [MICROBLAZE_IT_TCAGETD_TYPEC2]   = {arch:ISA_V7_00, morph:morphTCAGETD_TYPEC2},
    [MICROBLAZE_IT_TCGETD_TYPEC2]    = {arch:ISA_V7_00, morph:morphTCGETD_TYPEC2},
    [MICROBLAZE_IT_TEAGETD_TYPEC2]   = {arch:ISA_V7_00, morph:morphTEAGETD_TYPEC2},
    [MICROBLAZE_IT_TECAGETD_TYPEC2]  = {arch:ISA_V7_00, morph:morphTECAGETD_TYPEC2},
    [MICROBLAZE_IT_TECGETD_TYPEC2]   = {arch:ISA_V7_00, morph:morphTECGETD_TYPEC2},
    [MICROBLAZE_IT_TEGETD_TYPEC2]    = {arch:ISA_V7_00, morph:morphTEGETD_TYPEC2},
    [MICROBLAZE_IT_TGETD_TYPEC2]     = {arch:ISA_V7_00, morph:morphTGETD_TYPEC2},
    [MICROBLAZE_IT_TNAGETD_TYPEC2]   = {arch:ISA_V7_00, morph:morphTNAGETD_TYPEC2},
    [MICROBLAZE_IT_TNCAGETD_TYPEC2]  = {arch:ISA_V7_00, morph:morphTNCAGETD_TYPEC2},
    [MICROBLAZE_IT_TNCGETD_TYPEC2]   = {arch:ISA_V7_00, morph:morphTNCGETD_TYPEC2},
    [MICROBLAZE_IT_TNEAGETD_TYPEC2]  = {arch:ISA_V7_00, morph:morphTNEAGETD_TYPEC2},
    [MICROBLAZE_IT_TNECAGETD_TYPEC2] = {arch:ISA_V7_00, morph:morphTNECAGETD_TYPEC2},
    [MICROBLAZE_IT_TNECGETD_TYPEC2]  = {arch:ISA_V7_00, morph:morphTNECGETD_TYPEC2},
    [MICROBLAZE_IT_TNEGETD_TYPEC2]   = {arch:ISA_V7_00, morph:morphTNEGETD_TYPEC2},
    [MICROBLAZE_IT_TNGETD_TYPEC2]    = {arch:ISA_V7_00, morph:morphTNGETD_TYPEC2},

    //
    // Format TypeC3 Insns
    //
    [MICROBLAZE_IT_APUT_TYPEC3]   = {arch:ISA_V7_00, morph:morphAPUT_TYPEC3},
    [MICROBLAZE_IT_CAPUT_TYPEC3]  = {arch:ISA_V7_00, morph:morphCAPUT_TYPEC3},
    [MICROBLAZE_IT_CPUT_TYPEC3]   = {arch:ISA_V7_00, morph:morphCPUT_TYPEC3},
    [MICROBLAZE_IT_NAPUT_TYPEC3]  = {arch:ISA_V7_00, morph:morphNAPUT_TYPEC3},
    [MICROBLAZE_IT_NCAPUT_TYPEC3] = {arch:ISA_V7_00, morph:morphNCAPUT_TYPEC3},
    [MICROBLAZE_IT_NCPUT_TYPEC3]  = {arch:ISA_V7_00, morph:morphNCPUT_TYPEC3},
    [MICROBLAZE_IT_NPUT_TYPEC3]   = {arch:ISA_V7_00, morph:morphNPUT_TYPEC3},
    [MICROBLAZE_IT_PUT_TYPEC3]    = {arch:ISA_V7_00, morph:morphPUT_TYPEC3},

    //
    // Format TypeC3d Insns
    //
    [MICROBLAZE_IT_APUTD_TYPEC3D]   = {arch:ISA_V7_00, morph:morphAPUTD_TYPEC3D},
    [MICROBLAZE_IT_CAPUTD_TYPEC3D]  = {arch:ISA_V7_00, morph:morphCAPUTD_TYPEC3D},
    [MICROBLAZE_IT_CPUTD_TYPEC3D]   = {arch:ISA_V7_00, morph:morphCPUTD_TYPEC3D},
    [MICROBLAZE_IT_NAPUTD_TYPEC3D]  = {arch:ISA_V7_00, morph:morphNAPUTD_TYPEC3D},
    [MICROBLAZE_IT_NCAPUTD_TYPEC3D] = {arch:ISA_V7_00, morph:morphNCAPUTD_TYPEC3D},
    [MICROBLAZE_IT_NCPUTD_TYPEC3D]  = {arch:ISA_V7_00, morph:morphNCPUTD_TYPEC3D},
    [MICROBLAZE_IT_NPUTD_TYPEC3D]   = {arch:ISA_V7_00, morph:morphNPUTD_TYPEC3D},
    [MICROBLAZE_IT_PUTD_TYPEC3D]    = {arch:ISA_V7_00, morph:morphPUTD_TYPEC3D},

    //
    // Format TypeC4 Insns
    //
    [MICROBLAZE_IT_TAPUT_TYPEC4]   = {arch:ISA_V7_00, morph:morphTAPUT_TYPEC4},
    [MICROBLAZE_IT_TCAPUT_TYPEC4]  = {arch:ISA_V7_00, morph:morphTCAPUT_TYPEC4},
    [MICROBLAZE_IT_TCPUT_TYPEC4]   = {arch:ISA_V7_00, morph:morphTCPUT_TYPEC4},
    [MICROBLAZE_IT_TNAPUT_TYPEC4]  = {arch:ISA_V7_00, morph:morphTNAPUT_TYPEC4},
    [MICROBLAZE_IT_TNCAPUT_TYPEC4] = {arch:ISA_V7_00, morph:morphTNCAPUT_TYPEC4},
    [MICROBLAZE_IT_TNCPUT_TYPEC4]  = {arch:ISA_V7_00, morph:morphTNCPUT_TYPEC4},
    [MICROBLAZE_IT_TNPUT_TYPEC4]   = {arch:ISA_V7_00, morph:morphTNPUT_TYPEC4},
    [MICROBLAZE_IT_TPUT_TYPEC4]    = {arch:ISA_V7_00, morph:morphTPUT_TYPEC4},

    //
    // Format TypeC4d Insns
    //
    [MICROBLAZE_IT_TAPUTD_TYPEC4D]   = {arch:ISA_V7_00, morph:morphTAPUTD_TYPEC4D},
    [MICROBLAZE_IT_TCAPUTD_TYPEC4D]  = {arch:ISA_V7_00, morph:morphTCAPUTD_TYPEC4D},
    [MICROBLAZE_IT_TCPUTD_TYPEC4D]   = {arch:ISA_V7_00, morph:morphTCPUTD_TYPEC4D},
    [MICROBLAZE_IT_TNAPUTD_TYPEC4D]  = {arch:ISA_V7_00, morph:morphTNAPUTD_TYPEC4D},
    [MICROBLAZE_IT_TNCAPUTD_TYPEC4D] = {arch:ISA_V7_00, morph:morphTNCAPUTD_TYPEC4D},
    [MICROBLAZE_IT_TNCPUTD_TYPEC4D]  = {arch:ISA_V7_00, morph:morphTNCPUTD_TYPEC4D},
    [MICROBLAZE_IT_TNPUTD_TYPEC4D]   = {arch:ISA_V7_00, morph:morphTNPUTD_TYPEC4D},
    [MICROBLAZE_IT_TPUTD_TYPEC4D]    = {arch:ISA_V7_00, morph:morphTPUTD_TYPEC4D},

    //
    // Format TypeI1 Insns
    //
    [MICROBLAZE_IT_IMM_TYPEI1] = {arch:ISA_V7_00, morph:morphIMM_TYPEI1},

    //
    // Format TypeX Insns
    //
    [MICROBLAZE_IT_NOP_TYPEX] = {arch:ISA_V7_00, morph:morphNOP_TYPEX},

};

//
// Default undecoded/badvariant/unimplemented instruction behavior
//
static void defaultMorphCallback(
    vmiProcessorP processor,
    microblazeAddr thisPC,
    Uns32 instruction,
    char *message
) {
    vmiPrintf(
        "CPU '%s' 0x%08x:0x%08x *** %s instruction: exiting ***\n",
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
static MICROBLAZE_MORPH_FN(emitUndefined) {
    TYPE_SPR_ESR ESR = {0};
    ESR.EC = ILLEGAL_OPCODE_EXCEPTION;
    ESR.bits_ESS_EC_00001.Rx = state->info.rD;
    vmimtArgProcessor();
    vmimtArgUns32(ESR.reg);
    vmimtCall((vmiCallFn)microblazehwExceptionCB);
}
static MICROBLAZE_MORPH_FN(emitNotVariant) {
    vmimtArgProcessor();
    vmimtArgUns32(state->info.thisPC);
    vmimtArgUns32(state->info.instruction);
    vmimtArgNatAddress("badvariant");
    vmimtCall((vmiCallFn)defaultMorphCallback);
}
static MICROBLAZE_MORPH_FN(emitAbsentFeature) {
    vmimtArgProcessor();
    vmimtArgUns32(state->info.thisPC);
    vmimtArgUns32(state->info.instruction);
    vmimtArgNatAddress(state->message);
    vmimtCall((vmiCallFn)defaultMorphCallback);
}
static MICROBLAZE_MORPH_FN(emitUnimplemented) {
    vmimtArgProcessor();
    vmimtArgUns32(state->info.thisPC);
    vmimtArgUns32(state->info.instruction);
    vmimtArgNatAddress("unimplemented");
    vmimtCall((vmiCallFn)defaultMorphCallback);
}

static Bool disableMorph(microblazeMorphStateP state) {
    microblazeP microblaze = state->microblaze;
    if(!MICROBLAZE_DISASSEMBLE(microblaze)) {
        return False;
    } else {
        return True;
    }
}

//
// Call to implemented morph code instruction generator
//
static MICROBLAZE_MORPH_FN(emitImplemented) {
    state->attrs->morph(state);
}

//
// Return a boolean indicating whether the processor supports the required
// architecture
//
static Bool notVariant(microblazeP microblaze, microblazeMorphStateP state) {

    microblazeArchitecture configVariant   = microblaze->configInfo.arch;
    microblazeArchitecture requiredVariant = state->attrs->arch;

    if (configVariant & requiredVariant) {
        return True;
    } else {
        return False;
    }
}

//
// Determine if this C_USE_* feature is enabled in the core
//
typedef enum microblazeFeatureE {
    FR_NONE = 0,                // no special feature requirement
    FR_C_USE_BARREL,            // Requires Barrel Shifter
    FR_C_USE_DIV,               // Requires hardware divider
    FR_C_USE_HW_MUL,            // Requires hardware multiplier
    FR_C_USE_HW_MUL64,          // Requires hardware 64 bit multiplier
    FR_C_USE_FPU,               // Requires FPU
    FR_C_USE_FPU2,              // Requires FPU (extended)
    FR_C_USE_MSR_INSTR,         // Requires MSRSET/MSRCLR
    FR_C_USE_PCMP_INSTR,        // Requires PCMP*/CLZ instructions
    FR_C_USE_REORDER_INSTR,     // Requires L*R, S*R. SWAP*, instructions
    FR_C_USE_FSL_LINKS,         // Requires FSL
    FR_C_USE_EXTENDED_FSL_INSTR // Requires Extended FSL
} microblazeFeature;

static const char *featureAbsentMessage[] = {
    [FR_NONE]                      = "Feature Supported",
    [FR_C_USE_BARREL]              = "Absent Feature USE_BARREL Required",
    [FR_C_USE_DIV]                 = "Absent Feature USE_DIV Required",
    [FR_C_USE_HW_MUL]              = "Absent Feature USE_HW_MUL Required",
    [FR_C_USE_HW_MUL64]            = "Absent Feature USE_HW_MUL64 Required",
    [FR_C_USE_FPU]                 = "Absent Feature USE_FPU Required",
    [FR_C_USE_FPU2]                = "Absent Feature USE_FPU2 Required",
    [FR_C_USE_MSR_INSTR]           = "Absent Feature USE_MSR_INSTR Required",
    [FR_C_USE_PCMP_INSTR]          = "Absent Feature USE_PCMP_INSTR Required",
    [FR_C_USE_REORDER_INSTR]       = "Absent Feature USE_REORDER_INSTR Required",
    [FR_C_USE_FSL_LINKS]           = "Absent Feature USE_FSL_LINKS Required",
    [FR_C_USE_EXTENDED_FSL_INSTR]  = "Absent Feature USE_EXTENDED_FSL_INSTR Required"
};

static const char * lookupFeatureMessage(microblazeFeature Feature) {
    return featureAbsentMessage[Feature];
}

//
// This defines instructions that require particular features to be present
// (omitted instructions have no special feature requirements)
//
#define FEATURE_REQUIRE(_NAME, _FR) [MICROBLAZE_IT_##_NAME] = _FR
const static microblazeFeature featureRequired[MICROBLAZE_IT_LAST+1] = {

    // Barrel shifter functions C_USE_BARREL
    FEATURE_REQUIRE(BSLL_TYPEA6,   FR_C_USE_BARREL),
    FEATURE_REQUIRE(BSLL_TYPEA6,   FR_C_USE_BARREL),
    FEATURE_REQUIRE(BSRA_TYPEA6,   FR_C_USE_BARREL),
    FEATURE_REQUIRE(BSRL_TYPEA6,   FR_C_USE_BARREL),
    FEATURE_REQUIRE(BSLLI_TYPEB6,  FR_C_USE_BARREL),
    FEATURE_REQUIRE(BSRAI_TYPEB6,  FR_C_USE_BARREL),
    FEATURE_REQUIRE(BSRLI_TYPEB6,  FR_C_USE_BARREL),
    FEATURE_REQUIRE(BSEFI_TYPEBBE, FR_C_USE_BARREL),
    FEATURE_REQUIRE(BSIFI_TYPEBBI, FR_C_USE_BARREL),

    // Divider check, C_USE_DIV
    FEATURE_REQUIRE(IDIV_TYPEA7,  FR_C_USE_DIV),
    FEATURE_REQUIRE(IDIVU_TYPEA7, FR_C_USE_DIV),

    // HW Multiply check, C_USE_HW_MUL
    FEATURE_REQUIRE(MUL_TYPEA1,  FR_C_USE_HW_MUL),
    FEATURE_REQUIRE(MULI_TYPEB1, FR_C_USE_HW_MUL),

    // HW Multiply check, C_USE_HW_MUL (64)
    FEATURE_REQUIRE(MULH_TYPEA1,   FR_C_USE_HW_MUL64),
    FEATURE_REQUIRE(MULHSU_TYPEA1, FR_C_USE_HW_MUL64),
    FEATURE_REQUIRE(MULHU_TYPEA1,  FR_C_USE_HW_MUL64),

    // FPU check, C_USE_FPU
    FEATURE_REQUIRE(FADD_TYPEA1,   FR_C_USE_FPU),
    FEATURE_REQUIRE(FRSUB_TYPEA1,  FR_C_USE_FPU),
    FEATURE_REQUIRE(FMUL_TYPEA1,   FR_C_USE_FPU),
    FEATURE_REQUIRE(FDIV_TYPEA1,   FR_C_USE_FPU),
    FEATURE_REQUIRE(FCMPEQ_TYPEA1, FR_C_USE_FPU),
    FEATURE_REQUIRE(FCMPGE_TYPEA1, FR_C_USE_FPU),
    FEATURE_REQUIRE(FCMPGT_TYPEA1, FR_C_USE_FPU),
    FEATURE_REQUIRE(FCMPLE_TYPEA1, FR_C_USE_FPU),
    FEATURE_REQUIRE(FCMPLT_TYPEA1, FR_C_USE_FPU),
    FEATURE_REQUIRE(FCMPNE_TYPEA1, FR_C_USE_FPU),
    FEATURE_REQUIRE(FCMPUN_TYPEA1, FR_C_USE_FPU),

    // FPU check, C_USE_FPU (2)
    FEATURE_REQUIRE(FLT_TYPEAB,   FR_C_USE_FPU2),
    FEATURE_REQUIRE(FINT_TYPEAB,  FR_C_USE_FPU2),
    FEATURE_REQUIRE(FSQRT_TYPEAB, FR_C_USE_FPU2),

    // MSRSET/MSRCLR, C_USE_MSR_INSTR
    FEATURE_REQUIRE(MSRCLR_TYPEB9, FR_C_USE_MSR_INSTR),
    FEATURE_REQUIRE(MSRSET_TYPEB9, FR_C_USE_MSR_INSTR),

    // PCMP/CLZ, C_USE_PCMP_INSTR
    FEATURE_REQUIRE(PCMPBF_TYPEA1, FR_C_USE_PCMP_INSTR),
    FEATURE_REQUIRE(PCMPEQ_TYPEA1, FR_C_USE_PCMP_INSTR),
    FEATURE_REQUIRE(PCMPNE_TYPEA1, FR_C_USE_PCMP_INSTR),
    FEATURE_REQUIRE(CLZ_TYPEAB,    FR_C_USE_PCMP_INSTR),

    // L*R, S*R. SWAP*, C_USE_REORDER
    FEATURE_REQUIRE(LBUR_TYPEA8,  FR_C_USE_REORDER_INSTR),
    FEATURE_REQUIRE(LHUR_TYPEA8,  FR_C_USE_REORDER_INSTR),
    FEATURE_REQUIRE(LWR_TYPEA8,   FR_C_USE_REORDER_INSTR),
    FEATURE_REQUIRE(SBR_TYPEA8,   FR_C_USE_REORDER_INSTR),
    FEATURE_REQUIRE(SHR_TYPEA8,   FR_C_USE_REORDER_INSTR),
    FEATURE_REQUIRE(SWR_TYPEA8,   FR_C_USE_REORDER_INSTR),
    FEATURE_REQUIRE(SWAPB_TYPEAB, FR_C_USE_REORDER_INSTR),
    FEATURE_REQUIRE(SWAPH_TYPEAB, FR_C_USE_REORDER_INSTR),

    // GET/PUT, C_FSL_LINKS
    FEATURE_REQUIRE(CGET_TYPEC1,  FR_C_USE_FSL_LINKS),
    FEATURE_REQUIRE(GET_TYPEC1,   FR_C_USE_FSL_LINKS),
    FEATURE_REQUIRE(NCGET_TYPEC1, FR_C_USE_FSL_LINKS),
    FEATURE_REQUIRE(NGET_TYPEC1,  FR_C_USE_FSL_LINKS),
    FEATURE_REQUIRE(CPUT_TYPEC3,  FR_C_USE_FSL_LINKS),
    FEATURE_REQUIRE(NCPUT_TYPEC3, FR_C_USE_FSL_LINKS),
    FEATURE_REQUIRE(NPUT_TYPEC3,  FR_C_USE_FSL_LINKS),
    FEATURE_REQUIRE(PUT_TYPEC3,   FR_C_USE_FSL_LINKS),

    // C_USE_EXTENDED_FSL_INSTR
    FEATURE_REQUIRE(AGET_TYPEC1,      FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(CAGET_TYPEC1,     FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(EAGET_TYPEC1,     FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(ECAGET_TYPEC1,    FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(ECGET_TYPEC1,     FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(EGET_TYPEC1,      FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(NAGET_TYPEC1,     FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(NCAGET_TYPEC1,    FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(NEAGET_TYPEC1,    FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(NECAGET_TYPEC1,   FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(NECGET_TYPEC1,    FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(NEGET_TYPEC1,     FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TAGET_TYPEC1,     FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TCAGET_TYPEC1,    FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TCGET_TYPEC1,     FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TEAGET_TYPEC1,    FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TECAGET_TYPEC1,   FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TECGET_TYPEC1,    FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TEGET_TYPEC1,     FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TGET_TYPEC1,      FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TNAGET_TYPEC1,    FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TNCAGET_TYPEC1,   FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TNCGET_TYPEC1,    FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TNEAGET_TYPEC1,   FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TNECAGET_TYPEC1,  FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TNECGET_TYPEC1,   FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TNEGET_TYPEC1,    FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TNGET_TYPEC1,     FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(AGETD_TYPEC2,     FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(CAGETD_TYPEC2,    FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(CGETD_TYPEC2,     FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(EAGETD_TYPEC2,    FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(ECAGETD_TYPEC2,   FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(ECGETD_TYPEC2,    FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(EGETD_TYPEC2,     FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(GETD_TYPEC2,      FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(NAGETD_TYPEC2,    FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(NCAGETD_TYPEC2,   FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(NCGETD_TYPEC2,    FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(NEAGETD_TYPEC2,   FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(NECAGETD_TYPEC2,  FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(NECGETD_TYPEC2,   FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(NEGETD_TYPEC2,    FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(NGETD_TYPEC2,     FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TAGETD_TYPEC2,    FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TCAGETD_TYPEC2,   FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TCGETD_TYPEC2,    FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TEAGETD_TYPEC2,   FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TECAGETD_TYPEC2,  FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TECGETD_TYPEC2,   FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TEGETD_TYPEC2,    FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TGETD_TYPEC2,     FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TNAGETD_TYPEC2,   FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TNCAGETD_TYPEC2,  FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TNCGETD_TYPEC2,   FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TNEAGETD_TYPEC2,  FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TNECAGETD_TYPEC2, FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TNECGETD_TYPEC2,  FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TNEGETD_TYPEC2,   FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(TNGETD_TYPEC2,    FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(APUT_TYPEC3,      FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(CAPUT_TYPEC3,     FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(NAPUT_TYPEC3,     FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(NCAPUT_TYPEC3,    FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(APUTD_TYPEC3D,    FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(CAPUTD_TYPEC3D,   FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(NAPUTD_TYPEC3D,   FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(NCAPUTD_TYPEC3D,  FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(CPUTD_TYPEC3D,    FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(NCPUTD_TYPEC3D,   FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(NPUTD_TYPEC3D,    FR_C_USE_EXTENDED_FSL_INSTR),
    FEATURE_REQUIRE(PUTD_TYPEC3D,     FR_C_USE_EXTENDED_FSL_INSTR),

};

//
// A delay slot must not contain
// an IMM, branch or break instruction
//
static Bool illegalDelaySlotInstruction(microblazeP microblaze, microblazeMorphStateP state) {
    Bool status = False;

    // morphNOP_TYPEX

    //
    // If the instruction is 8 bits then this is an imm
    //
    if (state->info.instrsize == 8) {
        status = True;
        vmiMessage("W", "MB_DS_ILL", "Illegal Instruction 0x%08x: 'IMM' In Delay Slot", state->info.thisPC-4);
    } else {
        //
        // Illegal delay slot instructions branch & break
        //
        switch (state->info.type) {
            case MICROBLAZE_IT_BEQ_TYPEA2:
            case MICROBLAZE_IT_BEQD_TYPEA2:
            case MICROBLAZE_IT_BGE_TYPEA2:
            case MICROBLAZE_IT_BGED_TYPEA2:
            case MICROBLAZE_IT_BGT_TYPEA2:
            case MICROBLAZE_IT_BGTD_TYPEA2:
            case MICROBLAZE_IT_BLE_TYPEA2:
            case MICROBLAZE_IT_BLED_TYPEA2:
            case MICROBLAZE_IT_BLT_TYPEA2:
            case MICROBLAZE_IT_BLTD_TYPEA2:
            case MICROBLAZE_IT_BNE_TYPEA2:
            case MICROBLAZE_IT_BNED_TYPEA2:
            case MICROBLAZE_IT_BR_TYPEA3:
            case MICROBLAZE_IT_BRA_TYPEA3:
            case MICROBLAZE_IT_BRAD_TYPEA3:
            case MICROBLAZE_IT_BRD_TYPEA3:
            case MICROBLAZE_IT_BRALD_TYPEA4:
            case MICROBLAZE_IT_BRLD_TYPEA4:
            case MICROBLAZE_IT_BRK_TYPEA5:
            case MICROBLAZE_IT_BEQI_TYPEB2:
            case MICROBLAZE_IT_BEQID_TYPEB2:
            case MICROBLAZE_IT_BGEI_TYPEB2:
            case MICROBLAZE_IT_BGEID_TYPEB2:
            case MICROBLAZE_IT_BGTI_TYPEB2:
            case MICROBLAZE_IT_BGTID_TYPEB2:
            case MICROBLAZE_IT_BLEI_TYPEB2:
            case MICROBLAZE_IT_BLEID_TYPEB2:
            case MICROBLAZE_IT_BLTI_TYPEB2:
            case MICROBLAZE_IT_BLTID_TYPEB2:
            case MICROBLAZE_IT_BNEI_TYPEB2:
            case MICROBLAZE_IT_BNEID_TYPEB2:
            case MICROBLAZE_IT_BRAI_TYPEB3:
            case MICROBLAZE_IT_BRAID_TYPEB3:
            case MICROBLAZE_IT_BRI_TYPEB3:
            case MICROBLAZE_IT_BRID_TYPEB3:
            case MICROBLAZE_IT_BRALID_TYPEB4:
            case MICROBLAZE_IT_BRLID_TYPEB4:
            case MICROBLAZE_IT_BRKI_TYPEB5:
            case MICROBLAZE_IT_RTBD_TYPEBA:
            case MICROBLAZE_IT_RTED_TYPEBA:
            case MICROBLAZE_IT_RTID_TYPEBA:
            case MICROBLAZE_IT_RTSD_TYPEBA:
                status = True;
                vmiMessage("W", "MB_DS_ILL", "Illegal Instruction 0x%08x: '%s' In Delay Slot", state->info.thisPC, state->info.opcode);
                break;

            default:
                status = False;
                break;
        }
    }

    if (status) {
        //
        // Morph a NOP instruction
        //
    }
    return status;
}

static Bool absentFeature(microblazeP microblaze, microblazeMorphStateP state) {

    microblazeFeature fr = featureRequired[state->info.type];
    Bool        isAbsent = False;

    // determine whether required feature is absent
    state->message = lookupFeatureMessage(fr);
    if(fr) {
        switch(fr) {
            case FR_NONE:
                break;
            case FR_C_USE_BARREL:
                isAbsent = !microblaze->SPR_PVR0.BS;
                break;
            case FR_C_USE_DIV:
                isAbsent = !microblaze->SPR_PVR0.DIV;
                break;
            case FR_C_USE_HW_MUL:
                isAbsent = !microblaze->SPR_PVR0.MUL;
                break;
            case FR_C_USE_HW_MUL64:
                isAbsent = !microblaze->SPR_PVR2.MUL64;
                break;
            case FR_C_USE_FPU:
                isAbsent = !microblaze->SPR_PVR0.FPU;
                break;
            case FR_C_USE_FPU2:
                isAbsent = !microblaze->SPR_PVR2.FPU;
                break;
            case FR_C_USE_MSR_INSTR:
                isAbsent = !microblaze->SPR_PVR2.MSR;
                break;
            case FR_C_USE_PCMP_INSTR:
                isAbsent = !microblaze->SPR_PVR2.PCMP;
                break;
            case FR_C_USE_REORDER_INSTR:
                isAbsent = !microblaze->SPR_PVR0.REORD;
                break;
            case FR_C_USE_FSL_LINKS:
                isAbsent = !microblaze->SPR_PVR3.FSL;
                break;
            case FR_C_USE_EXTENDED_FSL_INSTR:
                isAbsent = !microblaze->SPR_PVR2.FSL;
                break;
            default:
                VMI_ABORT("unhandled feature %u\n", fr);
                break;
        }
    }

    return isAbsent;
}

//
// Instruction Morpher
//
VMI_MORPH_FN(microblazeMorph) {
    microblazeP microblaze = (microblazeP)processor;
    microblazeMorphState state;

    // get instruction and instruction type
    microblazeDecode(microblaze, thisPC, &state.info);

    state.attrs = &dispatchTable[state.info.type];
    state.microblaze = microblaze;

    if(disableMorph(&state)) {
        // no action if in disassembly mode

    } else if(state.info.type==MICROBLAZE_IT_LAST) {
        // take UndefinedInstruction exception
        emitUndefined(&state);

    } else if(!notVariant(microblaze, &state)) {
        // instruction not supported on this variant
        emitNotVariant(&state);

    } else if(absentFeature(microblaze, &state)) {
        // instruction not supported on this configuration
        emitAbsentFeature(&state);

    } else if(inDelaySlot && illegalDelaySlotInstruction(microblaze, &state)) {
        // no action - effectively an NOP

    } else if(state.attrs->morph) {
        // translate the instruction
        emitImplemented(&state);

    } else {
        // here if no morph callback specified
        emitUnimplemented(&state);

    }
}

VMI_FETCH_SNAP_FN(microblazeFetchSnap) {
    return thisPC & -4;
}

VMI_RD_WR_SNAP_FN(microblazeRdSnap) {
    return 0;
}

VMI_RD_WR_SNAP_FN(microblazeWrSnap) {
    return 0;
}

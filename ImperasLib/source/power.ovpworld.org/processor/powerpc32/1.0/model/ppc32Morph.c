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
#include "ppc32Morph.h"
#include "ppc32Decode.h"
#include "ppc32Functions.h"
#include "ppc32Instructions.h"
#include "ppc32Structure.h"

//
// Write Morpher Table
//
const static ppc32MorphAttr dispatchTable[PPC32_IT_LAST+1] = {
    //
    // Format A1 Insns
    //
    [PPC32_IT_FMADD_A1] = {arch:FEATURE_I_FP, morph:morphFMADD_A1},
    [PPC32_IT_FMADDRC_A1] = {arch:FEATURE_I_FP, morph:morphFMADDRC_A1},
    [PPC32_IT_FMADDS_A1] = {arch:FEATURE_I_FP, morph:morphFMADDS_A1},
    [PPC32_IT_FMADDSRC_A1] = {arch:FEATURE_I_FP, morph:morphFMADDSRC_A1},
    [PPC32_IT_FMSUB_A1] = {arch:FEATURE_I_FP, morph:morphFMSUB_A1},
    [PPC32_IT_FMSUBRC_A1] = {arch:FEATURE_I_FP, morph:morphFMSUBRC_A1},
    [PPC32_IT_FMSUBS_A1] = {arch:FEATURE_I_FP, morph:morphFMSUBS_A1},
    [PPC32_IT_FMSUBSRC_A1] = {arch:FEATURE_I_FP, morph:morphFMSUBSRC_A1},
    [PPC32_IT_FNMADD_A1] = {arch:FEATURE_I_FP, morph:morphFNMADD_A1},
    [PPC32_IT_FNMADDRC_A1] = {arch:FEATURE_I_FP, morph:morphFNMADDRC_A1},
    [PPC32_IT_FNMADDS_A1] = {arch:FEATURE_I_FP, morph:morphFNMADDS_A1},
    [PPC32_IT_FNMADDSRC_A1] = {arch:FEATURE_I_FP, morph:morphFNMADDSRC_A1},
    [PPC32_IT_FNMSUB_A1] = {arch:FEATURE_I_FP, morph:morphFNMSUB_A1},
    [PPC32_IT_FNMSUBRC_A1] = {arch:FEATURE_I_FP, morph:morphFNMSUBRC_A1},
    [PPC32_IT_FNMSUBS_A1] = {arch:FEATURE_I_FP, morph:morphFNMSUBS_A1},
    [PPC32_IT_FNMSUBSRC_A1] = {arch:FEATURE_I_FP, morph:morphFNMSUBSRC_A1},
    [PPC32_IT_FSEL_A1] = {arch:FEATURE_I_FP, morph:morphFSEL_A1},
    [PPC32_IT_FSELRC_A1] = {arch:FEATURE_I_FP, morph:morphFSELRC_A1},

    //
    // Format A2 Insns
    //
    [PPC32_IT_FADD_A2] = {arch:FEATURE_I_FP, morph:morphFADD_A2},
    [PPC32_IT_FADDRC_A2] = {arch:FEATURE_I_FP, morph:morphFADDRC_A2},
    [PPC32_IT_FADDS_A2] = {arch:FEATURE_I_FP, morph:morphFADDS_A2},
    [PPC32_IT_FADDSRC_A2] = {arch:FEATURE_I_FP, morph:morphFADDSRC_A2},
    [PPC32_IT_FDIV_A2] = {arch:FEATURE_I_FP, morph:morphFDIV_A2},
    [PPC32_IT_FDIVRC_A2] = {arch:FEATURE_I_FP, morph:morphFDIVRC_A2},
    [PPC32_IT_FDIVS_A2] = {arch:FEATURE_I_FP, morph:morphFDIVS_A2},
    [PPC32_IT_FDIVSRC_A2] = {arch:FEATURE_I_FP, morph:morphFDIVSRC_A2},
    [PPC32_IT_FSUB_A2] = {arch:FEATURE_I_FP, morph:morphFSUB_A2},
    [PPC32_IT_FSUBRC_A2] = {arch:FEATURE_I_FP, morph:morphFSUBRC_A2},
    [PPC32_IT_FSUBS_A2] = {arch:FEATURE_I_FP, morph:morphFSUBS_A2},
    [PPC32_IT_FSUBSRC_A2] = {arch:FEATURE_I_FP, morph:morphFSUBSRC_A2},

    //
    // Format A3 Insns
    //
    [PPC32_IT_FMUL_A3] = {arch:FEATURE_I_FP, morph:morphFMUL_A3},
    [PPC32_IT_FMULRC_A3] = {arch:FEATURE_I_FP, morph:morphFMULRC_A3},
    [PPC32_IT_FMULS_A3] = {arch:FEATURE_I_FP, morph:morphFMULS_A3},
    [PPC32_IT_FMULSRC_A3] = {arch:FEATURE_I_FP, morph:morphFMULSRC_A3},

    //
    // Format A4 Insns
    //
    [PPC32_IT_FSQRT_A4] = {arch:FEATURE_I_FP, morph:morphFSQRT_A4},
    [PPC32_IT_FSQRTRC_A4] = {arch:FEATURE_I_FP, morph:morphFSQRTRC_A4},
    [PPC32_IT_FSQRTS_A4] = {arch:FEATURE_I_FP, morph:morphFSQRTS_A4},
    [PPC32_IT_FSQRTSRC_A4] = {arch:FEATURE_I_FP, morph:morphFSQRTSRC_A4},

    //
    // Format A5 Insns
    //
    [PPC32_IT_FRE_A5] = {arch:FEATURE_I_FP, morph:morphFRE_A5},
    [PPC32_IT_FRERC_A5] = {arch:FEATURE_I_FP, morph:morphFRERC_A5},
    [PPC32_IT_FRES_A5] = {arch:FEATURE_I_FP, morph:morphFRES_A5},
    [PPC32_IT_FRESRC_A5] = {arch:FEATURE_I_FP, morph:morphFRESRC_A5},
    [PPC32_IT_FRSQRTE_A5] = {arch:FEATURE_I_FP, morph:morphFRSQRTE_A5},
    [PPC32_IT_FRSQRTERC_A5] = {arch:FEATURE_I_FP, morph:morphFRSQRTERC_A5},
    [PPC32_IT_FRSQRTES_A5] = {arch:FEATURE_I_FP, morph:morphFRSQRTES_A5},
    [PPC32_IT_FRSQRTESRC_A5] = {arch:FEATURE_I_FP, morph:morphFRSQRTESRC_A5},

    //
    // Format A6 Insns
    //
    [PPC32_IT_ISEL_A6] = {arch:FEATURE_I_B, morph:morphISEL_A6},

    //
    // Format B1 Insns
    //
    [PPC32_IT_BC_B1] = {arch:FEATURE_I_B, morph:morphBC_B1},

    //
    // Format BD15 Insns
    //
    [PPC32_IT_E_BC_BD15] = {arch:FEATURE_I_VLE, morph:morphE_BC_BD15},

    //
    // Format BD24 Insns
    //
    [PPC32_IT_E_B_BD24] = {arch:FEATURE_I_VLE, morph:morphE_B_BD24},

    //
    // Format BD81 Insns
    //
    [PPC32_IT_SE_BC_BD81] = {arch:FEATURE_I_VLE, morph:morphSE_BC_BD81},

    //
    // Format BD82 Insns
    //
    [PPC32_IT_SE_B_BD82] = {arch:FEATURE_I_VLE, morph:morphSE_B_BD82},

    //
    // Format C_0 Insns
    //
    [PPC32_IT_SE_ILLEGAL_C_0] = {arch:FEATURE_I_VLE, morph:morphSE_ILLEGAL_C_0},
    [PPC32_IT_SE_ISYNC_C_0] = {arch:FEATURE_I_VLE, morph:morphSE_ISYNC_C_0},
    [PPC32_IT_SE_RFCI_C_0] = {arch:FEATURE_I_VLE, morph:morphSE_RFCI_C_0},
    [PPC32_IT_SE_RFDI_C_0] = {arch:FEATURE_I_VLE, morph:morphSE_RFDI_C_0},
    [PPC32_IT_SE_RFI_C_0] = {arch:FEATURE_I_VLE, morph:morphSE_RFI_C_0},
    [PPC32_IT_SE_RFMCI_C_0] = {arch:FEATURE_I_VLE, morph:morphSE_RFMCI_C_0},
    [PPC32_IT_SE_SC_C_0] = {arch:FEATURE_I_VLE, morph:morphSE_SC_C_0},

    //
    // Format C_1 Insns
    //
    [PPC32_IT_SE_BCTR_C_1] = {arch:FEATURE_I_VLE, morph:morphSE_BCTR_C_1},
    [PPC32_IT_SE_BLR_C_1] = {arch:FEATURE_I_VLE, morph:morphSE_BLR_C_1},

    //
    // Format D1 Insns
    //
    [PPC32_IT_E_LBZ_D1] = {arch:FEATURE_I_VLE, morph:morphE_LBZ_D1},
    [PPC32_IT_E_LHA_D1] = {arch:FEATURE_I_VLE, morph:morphE_LHA_D1},
    [PPC32_IT_E_LHZ_D1] = {arch:FEATURE_I_VLE, morph:morphE_LHZ_D1},
    [PPC32_IT_E_LWZ_D1] = {arch:FEATURE_I_VLE, morph:morphE_LWZ_D1},
    [PPC32_IT_LBZ_D1] = {arch:FEATURE_I_B, morph:morphLBZ_D1},
    [PPC32_IT_LBZU_D1] = {arch:FEATURE_I_B, morph:morphLBZU_D1},
    [PPC32_IT_LHA_D1] = {arch:FEATURE_I_B, morph:morphLHA_D1},
    [PPC32_IT_LHAU_D1] = {arch:FEATURE_I_B, morph:morphLHAU_D1},
    [PPC32_IT_LHZ_D1] = {arch:FEATURE_I_B, morph:morphLHZ_D1},
    [PPC32_IT_LHZU_D1] = {arch:FEATURE_I_B, morph:morphLHZU_D1},
    [PPC32_IT_LMW_D1] = {arch:FEATURE_I_B, morph:morphLMW_D1},
    [PPC32_IT_LWZ_D1] = {arch:FEATURE_I_B, morph:morphLWZ_D1},
    [PPC32_IT_LWZU_D1] = {arch:FEATURE_I_B, morph:morphLWZU_D1},

    //
    // Format D2 Insns
    //
    [PPC32_IT_E_ADD16I_D2] = {arch:FEATURE_I_VLE, morph:morphE_ADD16I_D2},

    //
    // Format D2_0 Insns
    //
    [PPC32_IT_ADDI_D2_0] = {arch:FEATURE_I_B, morph:morphADDI_D2_0},
    [PPC32_IT_ADDIC_D2_0] = {arch:FEATURE_I_B, morph:morphADDIC_D2_0},
    [PPC32_IT_ADDICRC_D2_0] = {arch:FEATURE_I_B, morph:morphADDICRC_D2_0},
    [PPC32_IT_ADDIS_D2_0] = {arch:FEATURE_I_B, morph:morphADDIS_D2_0},
    [PPC32_IT_MULLI_D2_0] = {arch:FEATURE_I_B, morph:morphMULLI_D2_0},
    [PPC32_IT_SUBFIC_D2_0] = {arch:FEATURE_I_B, morph:morphSUBFIC_D2_0},

    //
    // Format D2_1 Insns
    //
    [PPC32_IT_LI_D2_1] = {arch:FEATURE_I_B, morph:morphLI_D2_1},
    [PPC32_IT_LIS_D2_1] = {arch:FEATURE_I_B, morph:morphLIS_D2_1},

    //
    // Format D3 Insns
    //
    [PPC32_IT_E_STB_D3] = {arch:FEATURE_I_VLE, morph:morphE_STB_D3},
    [PPC32_IT_E_STH_D3] = {arch:FEATURE_I_VLE, morph:morphE_STH_D3},
    [PPC32_IT_E_STW_D3] = {arch:FEATURE_I_VLE, morph:morphE_STW_D3},
    [PPC32_IT_STB_D3] = {arch:FEATURE_I_B, morph:morphSTB_D3},
    [PPC32_IT_STBU_D3] = {arch:FEATURE_I_B, morph:morphSTBU_D3},
    [PPC32_IT_STH_D3] = {arch:FEATURE_I_B, morph:morphSTH_D3},
    [PPC32_IT_STHU_D3] = {arch:FEATURE_I_B, morph:morphSTHU_D3},
    [PPC32_IT_STMW_D3] = {arch:FEATURE_I_B, morph:morphSTMW_D3},
    [PPC32_IT_STW_D3] = {arch:FEATURE_I_B, morph:morphSTW_D3},
    [PPC32_IT_STWU_D3] = {arch:FEATURE_I_B, morph:morphSTWU_D3},

    //
    // Format D4 Insns
    //
    [PPC32_IT_ANDIRC_D4] = {arch:FEATURE_I_B, morph:morphANDIRC_D4},
    [PPC32_IT_ANDISRC_D4] = {arch:FEATURE_I_B, morph:morphANDISRC_D4},
    [PPC32_IT_ORI_D4] = {arch:FEATURE_I_B, morph:morphORI_D4},
    [PPC32_IT_ORIS_D4] = {arch:FEATURE_I_B, morph:morphORIS_D4},
    [PPC32_IT_XORI_D4] = {arch:FEATURE_I_B, morph:morphXORI_D4},
    [PPC32_IT_XORIS_D4] = {arch:FEATURE_I_B, morph:morphXORIS_D4},

    //
    // Format D5_0 Insns
    //
    [PPC32_IT_CMPWI_D5_0] = {arch:FEATURE_I_B, morph:morphCMPWI_D5_0},

    //
    // Format D5_1 Insns
    //
    [PPC32_IT_CMPI_D5_1] = {arch:FEATURE_I_B, morph:morphCMPI_D5_1},

    //
    // Format D6_0 Insns
    //
    [PPC32_IT_CMPLWI_D6_0] = {arch:FEATURE_I_B, morph:morphCMPLWI_D6_0},

    //
    // Format D6_1 Insns
    //
    [PPC32_IT_CMPLI_D6_1] = {arch:FEATURE_I_B, morph:morphCMPLI_D6_1},

    //
    // Format D7 Insns
    //
    [PPC32_IT_TWI_D7] = {arch:FEATURE_I_B, morph:morphTWI_D7},

    //
    // Format D8 Insns
    //
    [PPC32_IT_LFD_D8] = {arch:FEATURE_I_FP, morph:morphLFD_D8},
    [PPC32_IT_LFDU_D8] = {arch:FEATURE_I_FP, morph:morphLFDU_D8},
    [PPC32_IT_LFS_D8] = {arch:FEATURE_I_FP, morph:morphLFS_D8},
    [PPC32_IT_LFSU_D8] = {arch:FEATURE_I_FP, morph:morphLFSU_D8},

    //
    // Format D8_0 Insns
    //
    [PPC32_IT_E_LBZU_D8_0] = {arch:FEATURE_I_VLE, morph:morphE_LBZU_D8_0},
    [PPC32_IT_E_LHAU_D8_0] = {arch:FEATURE_I_VLE, morph:morphE_LHAU_D8_0},
    [PPC32_IT_E_LHZU_D8_0] = {arch:FEATURE_I_VLE, morph:morphE_LHZU_D8_0},
    [PPC32_IT_E_LMW_D8_0] = {arch:FEATURE_I_VLE, morph:morphE_LMW_D8_0},
    [PPC32_IT_E_LWZU_D8_0] = {arch:FEATURE_I_VLE, morph:morphE_LWZU_D8_0},

    //
    // Format D8_1 Insns
    //
    [PPC32_IT_E_STBU_D8_1] = {arch:FEATURE_I_VLE, morph:morphE_STBU_D8_1},
    [PPC32_IT_E_STHU_D8_1] = {arch:FEATURE_I_VLE, morph:morphE_STHU_D8_1},
    [PPC32_IT_E_STMW_D8_1] = {arch:FEATURE_I_VLE, morph:morphE_STMW_D8_1},
    [PPC32_IT_E_STWU_D8_1] = {arch:FEATURE_I_VLE, morph:morphE_STWU_D8_1},

    //
    // Format D9 Insns
    //
    [PPC32_IT_STFD_D9] = {arch:FEATURE_I_FP, morph:morphSTFD_D9},
    [PPC32_IT_STFDU_D9] = {arch:FEATURE_I_FP, morph:morphSTFDU_D9},
    [PPC32_IT_STFS_D9] = {arch:FEATURE_I_FP, morph:morphSTFS_D9},
    [PPC32_IT_STFSU_D9] = {arch:FEATURE_I_FP, morph:morphSTFSU_D9},

    //
    // Format DQ1 Insns
    //
    [PPC32_IT_LQ_DQ1] = {arch:FEATURE_I_LMA, morph:morphLQ_DQ1},

    //
    // Format DS1 Insns
    //

    //
    // Format DS2 Insns
    //

    //
    // Format DS3 Insns
    //
    [PPC32_IT_STQ_DS3] = {arch:FEATURE_I_LMA, morph:morphSTQ_DS3},

    //
    // Format DS4 Insns
    //

    //
    // Format DS5 Insns
    //

    //
    // Format EVS Insns
    //
    [PPC32_IT_EVSEL_EVS] = {arch:FEATURE_I_SP, morph:morphEVSEL_EVS},

    //
    // Format EVX1 Insns
    //
    [PPC32_IT_BRINC_EVX1] = {arch:FEATURE_I_SP, morph:morphBRINC_EVX1},
    [PPC32_IT_EVSTDDX_EVX1] = {arch:FEATURE_I_SP, morph:morphEVSTDDX_EVX1},
    [PPC32_IT_EVSTDHX_EVX1] = {arch:FEATURE_I_SP, morph:morphEVSTDHX_EVX1},
    [PPC32_IT_EVSTDWX_EVX1] = {arch:FEATURE_I_SP, morph:morphEVSTDWX_EVX1},
    [PPC32_IT_EVSTWHEX_EVX1] = {arch:FEATURE_I_SP, morph:morphEVSTWHEX_EVX1},
    [PPC32_IT_EVSTWHOX_EVX1] = {arch:FEATURE_I_SP, morph:morphEVSTWHOX_EVX1},
    [PPC32_IT_EVSTWWEX_EVX1] = {arch:FEATURE_I_SP, morph:morphEVSTWWEX_EVX1},
    [PPC32_IT_EVSTWWOX_EVX1] = {arch:FEATURE_I_SP, morph:morphEVSTWWOX_EVX1},

    //
    // Format EVX2 Insns
    //

    //
    // Format EVX2_1 Insns
    //

    //
    // Format EVX2_2 Insns
    //
    [PPC32_IT_EVSTWHE_EVX2_2] = {arch:FEATURE_I_SP, morph:morphEVSTWHE_EVX2_2},
    [PPC32_IT_EVSTWHO_EVX2_2] = {arch:FEATURE_I_SP, morph:morphEVSTWHO_EVX2_2},
    [PPC32_IT_EVSTWWE_EVX2_2] = {arch:FEATURE_I_SP, morph:morphEVSTWWE_EVX2_2},
    [PPC32_IT_EVSTWWO_EVX2_2] = {arch:FEATURE_I_SP, morph:morphEVSTWWO_EVX2_2},

    //
    // Format EVX2_3 Insns
    //
    [PPC32_IT_EVSTDD_EVX2_3] = {arch:FEATURE_I_SP, morph:morphEVSTDD_EVX2_3},
    [PPC32_IT_EVSTDH_EVX2_3] = {arch:FEATURE_I_SP, morph:morphEVSTDH_EVX2_3},
    [PPC32_IT_EVSTDW_EVX2_3] = {arch:FEATURE_I_SP, morph:morphEVSTDW_EVX2_3},

    //
    // Format EVX3 Insns
    //
    [PPC32_IT_EFDCFS_EVX3] = {arch:FEATURE_I_SP, morph:morphEFDCFS_EVX3},
    [PPC32_IT_EFDCFSF_EVX3] = {arch:FEATURE_I_SP, morph:morphEFDCFSF_EVX3},
    [PPC32_IT_EFDCFSI_EVX3] = {arch:FEATURE_I_SP, morph:morphEFDCFSI_EVX3},
    [PPC32_IT_EFDCFSID_EVX3] = {arch:FEATURE_I_SP, morph:morphEFDCFSID_EVX3},
    [PPC32_IT_EFDCFUF_EVX3] = {arch:FEATURE_I_SP, morph:morphEFDCFUF_EVX3},
    [PPC32_IT_EFDCFUI_EVX3] = {arch:FEATURE_I_SP, morph:morphEFDCFUI_EVX3},
    [PPC32_IT_EFDCFUID_EVX3] = {arch:FEATURE_I_SP, morph:morphEFDCFUID_EVX3},
    [PPC32_IT_EFDCTSF_EVX3] = {arch:FEATURE_I_SP, morph:morphEFDCTSF_EVX3},
    [PPC32_IT_EFDCTSI_EVX3] = {arch:FEATURE_I_SP, morph:morphEFDCTSI_EVX3},
    [PPC32_IT_EFDCTSIDZ_EVX3] = {arch:FEATURE_I_SP, morph:morphEFDCTSIDZ_EVX3},
    [PPC32_IT_EFDCTSIZ_EVX3] = {arch:FEATURE_I_SP, morph:morphEFDCTSIZ_EVX3},
    [PPC32_IT_EFDCTUF_EVX3] = {arch:FEATURE_I_SP, morph:morphEFDCTUF_EVX3},
    [PPC32_IT_EFDCTUI_EVX3] = {arch:FEATURE_I_SP, morph:morphEFDCTUI_EVX3},
    [PPC32_IT_EFDCTUIDZ_EVX3] = {arch:FEATURE_I_SP, morph:morphEFDCTUIDZ_EVX3},
    [PPC32_IT_EFDCTUIZ_EVX3] = {arch:FEATURE_I_SP, morph:morphEFDCTUIZ_EVX3},
    [PPC32_IT_EFSCFD_EVX3] = {arch:FEATURE_I_SP, morph:morphEFSCFD_EVX3},
    [PPC32_IT_EFSCFSF_EVX3] = {arch:FEATURE_I_SP, morph:morphEFSCFSF_EVX3},
    [PPC32_IT_EFSCFSI_EVX3] = {arch:FEATURE_I_SP, morph:morphEFSCFSI_EVX3},
    [PPC32_IT_EFSCFUF_EVX3] = {arch:FEATURE_I_SP, morph:morphEFSCFUF_EVX3},
    [PPC32_IT_EFSCFUI_EVX3] = {arch:FEATURE_I_SP, morph:morphEFSCFUI_EVX3},
    [PPC32_IT_EFSCTSF_EVX3] = {arch:FEATURE_I_SP, morph:morphEFSCTSF_EVX3},
    [PPC32_IT_EFSCTSI_EVX3] = {arch:FEATURE_I_SP, morph:morphEFSCTSI_EVX3},
    [PPC32_IT_EFSCTSIZ_EVX3] = {arch:FEATURE_I_SP, morph:morphEFSCTSIZ_EVX3},
    [PPC32_IT_EFSCTUF_EVX3] = {arch:FEATURE_I_SP, morph:morphEFSCTUF_EVX3},
    [PPC32_IT_EFSCTUI_EVX3] = {arch:FEATURE_I_SP, morph:morphEFSCTUI_EVX3},
    [PPC32_IT_EFSCTUIZ_EVX3] = {arch:FEATURE_I_SP, morph:morphEFSCTUIZ_EVX3},
    [PPC32_IT_EVFSCFSF_EVX3] = {arch:FEATURE_I_SP, morph:morphEVFSCFSF_EVX3},
    [PPC32_IT_EVFSCFSI_EVX3] = {arch:FEATURE_I_SP, morph:morphEVFSCFSI_EVX3},
    [PPC32_IT_EVFSCFUF_EVX3] = {arch:FEATURE_I_SP, morph:morphEVFSCFUF_EVX3},
    [PPC32_IT_EVFSCFUI_EVX3] = {arch:FEATURE_I_SP, morph:morphEVFSCFUI_EVX3},
    [PPC32_IT_EVFSCTSF_EVX3] = {arch:FEATURE_I_SP, morph:morphEVFSCTSF_EVX3},
    [PPC32_IT_EVFSCTSI_EVX3] = {arch:FEATURE_I_SP, morph:morphEVFSCTSI_EVX3},
    [PPC32_IT_EVFSCTSIZ_EVX3] = {arch:FEATURE_I_SP, morph:morphEVFSCTSIZ_EVX3},
    [PPC32_IT_EVFSCTUF_EVX3] = {arch:FEATURE_I_SP, morph:morphEVFSCTUF_EVX3},
    [PPC32_IT_EVFSCTUI_EVX3] = {arch:FEATURE_I_SP, morph:morphEVFSCTUI_EVX3},
    [PPC32_IT_EVFSCTUIZ_EVX3] = {arch:FEATURE_I_SP, morph:morphEVFSCTUIZ_EVX3},

    //
    // Format EVX4 Insns
    //
    [PPC32_IT_EFDADD_EVX4] = {arch:FEATURE_I_SP, morph:morphEFDADD_EVX4},
    [PPC32_IT_EFDDIV_EVX4] = {arch:FEATURE_I_SP, morph:morphEFDDIV_EVX4},
    [PPC32_IT_EFDMUL_EVX4] = {arch:FEATURE_I_SP, morph:morphEFDMUL_EVX4},
    [PPC32_IT_EFDSUB_EVX4] = {arch:FEATURE_I_SP, morph:morphEFDSUB_EVX4},
    [PPC32_IT_EFSADD_EVX4] = {arch:FEATURE_I_SP, morph:morphEFSADD_EVX4},
    [PPC32_IT_EFSDIV_EVX4] = {arch:FEATURE_I_SP, morph:morphEFSDIV_EVX4},
    [PPC32_IT_EFSMUL_EVX4] = {arch:FEATURE_I_SP, morph:morphEFSMUL_EVX4},
    [PPC32_IT_EFSSUB_EVX4] = {arch:FEATURE_I_SP, morph:morphEFSSUB_EVX4},
    [PPC32_IT_EVADDW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVADDW_EVX4},
    [PPC32_IT_EVAND_EVX4] = {arch:FEATURE_I_SP, morph:morphEVAND_EVX4},
    [PPC32_IT_EVANDC_EVX4] = {arch:FEATURE_I_SP, morph:morphEVANDC_EVX4},
    [PPC32_IT_EVDIVWS_EVX4] = {arch:FEATURE_I_SP, morph:morphEVDIVWS_EVX4},
    [PPC32_IT_EVDIVWU_EVX4] = {arch:FEATURE_I_SP, morph:morphEVDIVWU_EVX4},
    [PPC32_IT_EVEQV_EVX4] = {arch:FEATURE_I_SP, morph:morphEVEQV_EVX4},
    [PPC32_IT_EVFSADD_EVX4] = {arch:FEATURE_I_SP, morph:morphEVFSADD_EVX4},
    [PPC32_IT_EVFSDIV_EVX4] = {arch:FEATURE_I_SP, morph:morphEVFSDIV_EVX4},
    [PPC32_IT_EVFSMUL_EVX4] = {arch:FEATURE_I_SP, morph:morphEVFSMUL_EVX4},
    [PPC32_IT_EVFSSUB_EVX4] = {arch:FEATURE_I_SP, morph:morphEVFSSUB_EVX4},
    [PPC32_IT_EVLDDX_EVX4] = {arch:FEATURE_I_SP, morph:morphEVLDDX_EVX4},
    [PPC32_IT_EVLDHX_EVX4] = {arch:FEATURE_I_SP, morph:morphEVLDHX_EVX4},
    [PPC32_IT_EVLDWX_EVX4] = {arch:FEATURE_I_SP, morph:morphEVLDWX_EVX4},
    [PPC32_IT_EVLHHESPLATX_EVX4] = {arch:FEATURE_I_SP, morph:morphEVLHHESPLATX_EVX4},
    [PPC32_IT_EVLHHOSSPLATX_EVX4] = {arch:FEATURE_I_SP, morph:morphEVLHHOSSPLATX_EVX4},
    [PPC32_IT_EVLHHOUSPLATX_EVX4] = {arch:FEATURE_I_SP, morph:morphEVLHHOUSPLATX_EVX4},
    [PPC32_IT_EVLWHEX_EVX4] = {arch:FEATURE_I_SP, morph:morphEVLWHEX_EVX4},
    [PPC32_IT_EVLWHOSX_EVX4] = {arch:FEATURE_I_SP, morph:morphEVLWHOSX_EVX4},
    [PPC32_IT_EVLWHOUX_EVX4] = {arch:FEATURE_I_SP, morph:morphEVLWHOUX_EVX4},
    [PPC32_IT_EVLWHSPLATX_EVX4] = {arch:FEATURE_I_SP, morph:morphEVLWHSPLATX_EVX4},
    [PPC32_IT_EVLWWSPLATX_EVX4] = {arch:FEATURE_I_SP, morph:morphEVLWWSPLATX_EVX4},
    [PPC32_IT_EVMERGEHI_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMERGEHI_EVX4},
    [PPC32_IT_EVMERGEHILO_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMERGEHILO_EVX4},
    [PPC32_IT_EVMERGELO_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMERGELO_EVX4},
    [PPC32_IT_EVMERGELOHI_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMERGELOHI_EVX4},
    [PPC32_IT_EVMHEGSMFAA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHEGSMFAA_EVX4},
    [PPC32_IT_EVMHEGSMFAN_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHEGSMFAN_EVX4},
    [PPC32_IT_EVMHEGSMIAA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHEGSMIAA_EVX4},
    [PPC32_IT_EVMHEGSMIAN_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHEGSMIAN_EVX4},
    [PPC32_IT_EVMHEGUMIAA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHEGUMIAA_EVX4},
    [PPC32_IT_EVMHEGUMIAN_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHEGUMIAN_EVX4},
    [PPC32_IT_EVMHESMF_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHESMF_EVX4},
    [PPC32_IT_EVMHESMFA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHESMFA_EVX4},
    [PPC32_IT_EVMHESMFAAW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHESMFAAW_EVX4},
    [PPC32_IT_EVMHESMFANW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHESMFANW_EVX4},
    [PPC32_IT_EVMHESMI_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHESMI_EVX4},
    [PPC32_IT_EVMHESMIA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHESMIA_EVX4},
    [PPC32_IT_EVMHESMIAAW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHESMIAAW_EVX4},
    [PPC32_IT_EVMHESMIANW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHESMIANW_EVX4},
    [PPC32_IT_EVMHESSF_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHESSF_EVX4},
    [PPC32_IT_EVMHESSFA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHESSFA_EVX4},
    [PPC32_IT_EVMHESSFAAW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHESSFAAW_EVX4},
    [PPC32_IT_EVMHESSFANW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHESSFANW_EVX4},
    [PPC32_IT_EVMHESSIAAW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHESSIAAW_EVX4},
    [PPC32_IT_EVMHESSIANW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHESSIANW_EVX4},
    [PPC32_IT_EVMHEUMI_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHEUMI_EVX4},
    [PPC32_IT_EVMHEUMIA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHEUMIA_EVX4},
    [PPC32_IT_EVMHEUMIAAW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHEUMIAAW_EVX4},
    [PPC32_IT_EVMHEUMIANW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHEUMIANW_EVX4},
    [PPC32_IT_EVMHEUSIAAW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHEUSIAAW_EVX4},
    [PPC32_IT_EVMHEUSIANW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHEUSIANW_EVX4},
    [PPC32_IT_EVMHOGSMFAA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOGSMFAA_EVX4},
    [PPC32_IT_EVMHOGSMFAN_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOGSMFAN_EVX4},
    [PPC32_IT_EVMHOGSMIAA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOGSMIAA_EVX4},
    [PPC32_IT_EVMHOGSMIAN_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOGSMIAN_EVX4},
    [PPC32_IT_EVMHOGUMIAA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOGUMIAA_EVX4},
    [PPC32_IT_EVMHOGUMIAN_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOGUMIAN_EVX4},
    [PPC32_IT_EVMHOSMF_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOSMF_EVX4},
    [PPC32_IT_EVMHOSMFA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOSMFA_EVX4},
    [PPC32_IT_EVMHOSMFAAW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOSMFAAW_EVX4},
    [PPC32_IT_EVMHOSMFANW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOSMFANW_EVX4},
    [PPC32_IT_EVMHOSMI_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOSMI_EVX4},
    [PPC32_IT_EVMHOSMIA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOSMIA_EVX4},
    [PPC32_IT_EVMHOSMIAAW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOSMIAAW_EVX4},
    [PPC32_IT_EVMHOSMIANW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOSMIANW_EVX4},
    [PPC32_IT_EVMHOSSF_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOSSF_EVX4},
    [PPC32_IT_EVMHOSSFA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOSSFA_EVX4},
    [PPC32_IT_EVMHOSSFAAW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOSSFAAW_EVX4},
    [PPC32_IT_EVMHOSSFANW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOSSFANW_EVX4},
    [PPC32_IT_EVMHOSSIAAW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOSSIAAW_EVX4},
    [PPC32_IT_EVMHOSSIANW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOSSIANW_EVX4},
    [PPC32_IT_EVMHOUMI_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOUMI_EVX4},
    [PPC32_IT_EVMHOUMIA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOUMIA_EVX4},
    [PPC32_IT_EVMHOUMIAAW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOUMIAAW_EVX4},
    [PPC32_IT_EVMHOUMIANW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOUMIANW_EVX4},
    [PPC32_IT_EVMHOUSIAAW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOUSIAAW_EVX4},
    [PPC32_IT_EVMHOUSIANW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMHOUSIANW_EVX4},
    [PPC32_IT_EVMWHSMF_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWHSMF_EVX4},
    [PPC32_IT_EVMWHSMFA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWHSMFA_EVX4},
    [PPC32_IT_EVMWHSMI_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWHSMI_EVX4},
    [PPC32_IT_EVMWHSMIA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWHSMIA_EVX4},
    [PPC32_IT_EVMWHSSF_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWHSSF_EVX4},
    [PPC32_IT_EVMWHSSFA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWHSSFA_EVX4},
    [PPC32_IT_EVMWHUMI_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWHUMI_EVX4},
    [PPC32_IT_EVMWHUMIA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWHUMIA_EVX4},
    [PPC32_IT_EVMWLSMIAAW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWLSMIAAW_EVX4},
    [PPC32_IT_EVMWLSMIANW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWLSMIANW_EVX4},
    [PPC32_IT_EVMWLSSIAAW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWLSSIAAW_EVX4},
    [PPC32_IT_EVMWLSSIANW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWLSSIANW_EVX4},
    [PPC32_IT_EVMWLUMI_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWLUMI_EVX4},
    [PPC32_IT_EVMWLUMIA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWLUMIA_EVX4},
    [PPC32_IT_EVMWLUMIAAW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWLUMIAAW_EVX4},
    [PPC32_IT_EVMWLUMIANW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWLUMIANW_EVX4},
    [PPC32_IT_EVMWLUSIAAW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWLUSIAAW_EVX4},
    [PPC32_IT_EVMWLUSIANW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWLUSIANW_EVX4},
    [PPC32_IT_EVMWSMF_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWSMF_EVX4},
    [PPC32_IT_EVMWSMFA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWSMFA_EVX4},
    [PPC32_IT_EVMWSMFAA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWSMFAA_EVX4},
    [PPC32_IT_EVMWSMFAN_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWSMFAN_EVX4},
    [PPC32_IT_EVMWSMI_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWSMI_EVX4},
    [PPC32_IT_EVMWSMIA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWSMIA_EVX4},
    [PPC32_IT_EVMWSMIAA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWSMIAA_EVX4},
    [PPC32_IT_EVMWSMIAN_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWSMIAN_EVX4},
    [PPC32_IT_EVMWSSF_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWSSF_EVX4},
    [PPC32_IT_EVMWSSFA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWSSFA_EVX4},
    [PPC32_IT_EVMWSSFAA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWSSFAA_EVX4},
    [PPC32_IT_EVMWSSFAN_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWSSFAN_EVX4},
    [PPC32_IT_EVMWUMI_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWUMI_EVX4},
    [PPC32_IT_EVMWUMIA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWUMIA_EVX4},
    [PPC32_IT_EVMWUMIAA_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWUMIAA_EVX4},
    [PPC32_IT_EVMWUMIAN_EVX4] = {arch:FEATURE_I_SP, morph:morphEVMWUMIAN_EVX4},
    [PPC32_IT_EVNAND_EVX4] = {arch:FEATURE_I_SP, morph:morphEVNAND_EVX4},
    [PPC32_IT_EVNOR_EVX4] = {arch:FEATURE_I_SP, morph:morphEVNOR_EVX4},
    [PPC32_IT_EVOR_EVX4] = {arch:FEATURE_I_SP, morph:morphEVOR_EVX4},
    [PPC32_IT_EVORC_EVX4] = {arch:FEATURE_I_SP, morph:morphEVORC_EVX4},
    [PPC32_IT_EVRLW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVRLW_EVX4},
    [PPC32_IT_EVSLW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVSLW_EVX4},
    [PPC32_IT_EVSRWS_EVX4] = {arch:FEATURE_I_SP, morph:morphEVSRWS_EVX4},
    [PPC32_IT_EVSRWU_EVX4] = {arch:FEATURE_I_SP, morph:morphEVSRWU_EVX4},
    [PPC32_IT_EVSUBFW_EVX4] = {arch:FEATURE_I_SP, morph:morphEVSUBFW_EVX4},
    [PPC32_IT_EVXOR_EVX4] = {arch:FEATURE_I_SP, morph:morphEVXOR_EVX4},

    //
    // Format EVX5 Insns
    //
    [PPC32_IT_EFDABS_EVX5] = {arch:FEATURE_I_SP, morph:morphEFDABS_EVX5},
    [PPC32_IT_EFDNABS_EVX5] = {arch:FEATURE_I_SP, morph:morphEFDNABS_EVX5},
    [PPC32_IT_EFDNEG_EVX5] = {arch:FEATURE_I_SP, morph:morphEFDNEG_EVX5},
    [PPC32_IT_EFSABS_EVX5] = {arch:FEATURE_I_SP, morph:morphEFSABS_EVX5},
    [PPC32_IT_EFSNABS_EVX5] = {arch:FEATURE_I_SP, morph:morphEFSNABS_EVX5},
    [PPC32_IT_EFSNEG_EVX5] = {arch:FEATURE_I_SP, morph:morphEFSNEG_EVX5},
    [PPC32_IT_EVABS_EVX5] = {arch:FEATURE_I_SP, morph:morphEVABS_EVX5},
    [PPC32_IT_EVADDSMIAAW_EVX5] = {arch:FEATURE_I_SP, morph:morphEVADDSMIAAW_EVX5},
    [PPC32_IT_EVADDSSIAAW_EVX5] = {arch:FEATURE_I_SP, morph:morphEVADDSSIAAW_EVX5},
    [PPC32_IT_EVADDUMIAAW_EVX5] = {arch:FEATURE_I_SP, morph:morphEVADDUMIAAW_EVX5},
    [PPC32_IT_EVADDUSIAAW_EVX5] = {arch:FEATURE_I_SP, morph:morphEVADDUSIAAW_EVX5},
    [PPC32_IT_EVCNTLSW_EVX5] = {arch:FEATURE_I_SP, morph:morphEVCNTLSW_EVX5},
    [PPC32_IT_EVCNTLZW_EVX5] = {arch:FEATURE_I_SP, morph:morphEVCNTLZW_EVX5},
    [PPC32_IT_EVEXTSB_EVX5] = {arch:FEATURE_I_SP, morph:morphEVEXTSB_EVX5},
    [PPC32_IT_EVEXTSH_EVX5] = {arch:FEATURE_I_SP, morph:morphEVEXTSH_EVX5},
    [PPC32_IT_EVFSABS_EVX5] = {arch:FEATURE_I_SP, morph:morphEVFSABS_EVX5},
    [PPC32_IT_EVFSNABS_EVX5] = {arch:FEATURE_I_SP, morph:morphEVFSNABS_EVX5},
    [PPC32_IT_EVFSNEG_EVX5] = {arch:FEATURE_I_SP, morph:morphEVFSNEG_EVX5},
    [PPC32_IT_EVMRA_EVX5] = {arch:FEATURE_I_SP, morph:morphEVMRA_EVX5},
    [PPC32_IT_EVNEG_EVX5] = {arch:FEATURE_I_SP, morph:morphEVNEG_EVX5},
    [PPC32_IT_EVRNDW_EVX5] = {arch:FEATURE_I_SP, morph:morphEVRNDW_EVX5},
    [PPC32_IT_EVSUBFSMIAAW_EVX5] = {arch:FEATURE_I_SP, morph:morphEVSUBFSMIAAW_EVX5},
    [PPC32_IT_EVSUBFSSIAAW_EVX5] = {arch:FEATURE_I_SP, morph:morphEVSUBFSSIAAW_EVX5},
    [PPC32_IT_EVSUBFUMIAAW_EVX5] = {arch:FEATURE_I_SP, morph:morphEVSUBFUMIAAW_EVX5},
    [PPC32_IT_EVSUBFUSIAAW_EVX5] = {arch:FEATURE_I_SP, morph:morphEVSUBFUSIAAW_EVX5},

    //
    // Format EVX6_1 Insns
    //
    [PPC32_IT_EVADDIW_EVX6_1] = {arch:FEATURE_I_SP, morph:morphEVADDIW_EVX6_1},

    //
    // Format EVX6_2 Insns
    //
    [PPC32_IT_EVSUBIFW_EVX6_2] = {arch:FEATURE_I_SP, morph:morphEVSUBIFW_EVX6_2},

    //
    // Format EVX7 Insns
    //
    [PPC32_IT_EFDCMPEQ_EVX7] = {arch:FEATURE_I_SP, morph:morphEFDCMPEQ_EVX7},
    [PPC32_IT_EFDCMPGT_EVX7] = {arch:FEATURE_I_SP, morph:morphEFDCMPGT_EVX7},
    [PPC32_IT_EFDCMPLT_EVX7] = {arch:FEATURE_I_SP, morph:morphEFDCMPLT_EVX7},
    [PPC32_IT_EFDTSTEQ_EVX7] = {arch:FEATURE_I_SP, morph:morphEFDTSTEQ_EVX7},
    [PPC32_IT_EFDTSTGT_EVX7] = {arch:FEATURE_I_SP, morph:morphEFDTSTGT_EVX7},
    [PPC32_IT_EFDTSTLT_EVX7] = {arch:FEATURE_I_SP, morph:morphEFDTSTLT_EVX7},
    [PPC32_IT_EFSCMPEQ_EVX7] = {arch:FEATURE_I_SP, morph:morphEFSCMPEQ_EVX7},
    [PPC32_IT_EFSCMPGT_EVX7] = {arch:FEATURE_I_SP, morph:morphEFSCMPGT_EVX7},
    [PPC32_IT_EFSCMPLT_EVX7] = {arch:FEATURE_I_SP, morph:morphEFSCMPLT_EVX7},
    [PPC32_IT_EFSTSTEQ_EVX7] = {arch:FEATURE_I_SP, morph:morphEFSTSTEQ_EVX7},
    [PPC32_IT_EFSTSTGT_EVX7] = {arch:FEATURE_I_SP, morph:morphEFSTSTGT_EVX7},
    [PPC32_IT_EFSTSTLT_EVX7] = {arch:FEATURE_I_SP, morph:morphEFSTSTLT_EVX7},
    [PPC32_IT_EVCMPEQ_EVX7] = {arch:FEATURE_I_SP, morph:morphEVCMPEQ_EVX7},
    [PPC32_IT_EVCMPGTS_EVX7] = {arch:FEATURE_I_SP, morph:morphEVCMPGTS_EVX7},
    [PPC32_IT_EVCMPGTU_EVX7] = {arch:FEATURE_I_SP, morph:morphEVCMPGTU_EVX7},
    [PPC32_IT_EVCMPLTS_EVX7] = {arch:FEATURE_I_SP, morph:morphEVCMPLTS_EVX7},
    [PPC32_IT_EVCMPLTU_EVX7] = {arch:FEATURE_I_SP, morph:morphEVCMPLTU_EVX7},
    [PPC32_IT_EVFSCMPEQ_EVX7] = {arch:FEATURE_I_SP, morph:morphEVFSCMPEQ_EVX7},
    [PPC32_IT_EVFSCMPGT_EVX7] = {arch:FEATURE_I_SP, morph:morphEVFSCMPGT_EVX7},
    [PPC32_IT_EVFSCMPLT_EVX7] = {arch:FEATURE_I_SP, morph:morphEVFSCMPLT_EVX7},
    [PPC32_IT_EVFSTSTEQ_EVX7] = {arch:FEATURE_I_SP, morph:morphEVFSTSTEQ_EVX7},
    [PPC32_IT_EVFSTSTGT_EVX7] = {arch:FEATURE_I_SP, morph:morphEVFSTSTGT_EVX7},
    [PPC32_IT_EVFSTSTLT_EVX7] = {arch:FEATURE_I_SP, morph:morphEVFSTSTLT_EVX7},

    //
    // Format EVX8 Insns
    //
    [PPC32_IT_EVRLWI_EVX8] = {arch:FEATURE_I_SP, morph:morphEVRLWI_EVX8},
    [PPC32_IT_EVSLWI_EVX8] = {arch:FEATURE_I_SP, morph:morphEVSLWI_EVX8},
    [PPC32_IT_EVSRWIS_EVX8] = {arch:FEATURE_I_SP, morph:morphEVSRWIS_EVX8},
    [PPC32_IT_EVSRWIU_EVX8] = {arch:FEATURE_I_SP, morph:morphEVSRWIU_EVX8},

    //
    // Format EVX8_1 Insns
    //
    [PPC32_IT_EVLHHESPLAT_EVX8_1] = {arch:FEATURE_I_SP, morph:morphEVLHHESPLAT_EVX8_1},
    [PPC32_IT_EVLHHOSSPLAT_EVX8_1] = {arch:FEATURE_I_SP, morph:morphEVLHHOSSPLAT_EVX8_1},
    [PPC32_IT_EVLHHOUSPLAT_EVX8_1] = {arch:FEATURE_I_SP, morph:morphEVLHHOUSPLAT_EVX8_1},

    //
    // Format EVX8_2 Insns
    //
    [PPC32_IT_EVLWHE_EVX8_2] = {arch:FEATURE_I_SP, morph:morphEVLWHE_EVX8_2},
    [PPC32_IT_EVLWHOS_EVX8_2] = {arch:FEATURE_I_SP, morph:morphEVLWHOS_EVX8_2},
    [PPC32_IT_EVLWHOU_EVX8_2] = {arch:FEATURE_I_SP, morph:morphEVLWHOU_EVX8_2},
    [PPC32_IT_EVLWHSPLAT_EVX8_2] = {arch:FEATURE_I_SP, morph:morphEVLWHSPLAT_EVX8_2},
    [PPC32_IT_EVLWWSPLAT_EVX8_2] = {arch:FEATURE_I_SP, morph:morphEVLWWSPLAT_EVX8_2},

    //
    // Format EVX8_3 Insns
    //
    [PPC32_IT_EVLDD_EVX8_3] = {arch:FEATURE_I_SP, morph:morphEVLDD_EVX8_3},
    [PPC32_IT_EVLDH_EVX8_3] = {arch:FEATURE_I_SP, morph:morphEVLDH_EVX8_3},
    [PPC32_IT_EVLDW_EVX8_3] = {arch:FEATURE_I_SP, morph:morphEVLDW_EVX8_3},

    //
    // Format EVX9 Insns
    //
    [PPC32_IT_EVSPLATFI_EVX9] = {arch:FEATURE_I_SP, morph:morphEVSPLATFI_EVX9},
    [PPC32_IT_EVSPLATI_EVX9] = {arch:FEATURE_I_SP, morph:morphEVSPLATI_EVX9},

    //
    // Format I1 Insns
    //
    [PPC32_IT_B_I1] = {arch:FEATURE_I_B, morph:morphB_I1},

    //
    // Format I16A1 Insns
    //
    [PPC32_IT_E_ADD2IRC_I16A1] = {arch:FEATURE_I_VLE, morph:morphE_ADD2IRC_I16A1},
    [PPC32_IT_E_ADD2IS_I16A1] = {arch:FEATURE_I_VLE, morph:morphE_ADD2IS_I16A1},
    [PPC32_IT_E_CMP16I_I16A1] = {arch:FEATURE_I_VLE, morph:morphE_CMP16I_I16A1},
    [PPC32_IT_E_CMPH16I_I16A1] = {arch:FEATURE_I_VLE, morph:morphE_CMPH16I_I16A1},
    [PPC32_IT_E_MULL2I_I16A1] = {arch:FEATURE_I_VLE, morph:morphE_MULL2I_I16A1},

    //
    // Format I16A2 Insns
    //
    [PPC32_IT_E_CMPHL16I_I16A2] = {arch:FEATURE_I_VLE, morph:morphE_CMPHL16I_I16A2},
    [PPC32_IT_E_CMPL16I_I16A2] = {arch:FEATURE_I_VLE, morph:morphE_CMPL16I_I16A2},

    //
    // Format I16L Insns
    //
    [PPC32_IT_E_AND2IRC_I16L] = {arch:FEATURE_I_VLE, morph:morphE_AND2IRC_I16L},
    [PPC32_IT_E_AND2ISRC_I16L] = {arch:FEATURE_I_VLE, morph:morphE_AND2ISRC_I16L},
    [PPC32_IT_E_LIS_I16L] = {arch:FEATURE_I_VLE, morph:morphE_LIS_I16L},
    [PPC32_IT_E_OR2I_I16L] = {arch:FEATURE_I_VLE, morph:morphE_OR2I_I16L},
    [PPC32_IT_E_OR2IS_I16L] = {arch:FEATURE_I_VLE, morph:morphE_OR2IS_I16L},

    //
    // Format IM5 Insns
    //
    [PPC32_IT_SE_ANDI_IM5] = {arch:FEATURE_I_VLE, morph:morphSE_ANDI_IM5},
    [PPC32_IT_SE_BMASKI_IM5] = {arch:FEATURE_I_VLE, morph:morphSE_BMASKI_IM5},
    [PPC32_IT_SE_CMPI_IM5] = {arch:FEATURE_I_VLE, morph:morphSE_CMPI_IM5},

    //
    // Format IM7 Insns
    //
    [PPC32_IT_SE_LI_IM7] = {arch:FEATURE_I_VLE, morph:morphSE_LI_IM7},

    //
    // Format LI20 Insns
    //
    [PPC32_IT_E_LI_LI20] = {arch:FEATURE_I_VLE, morph:morphE_LI_LI20},

    //
    // Format M1_0 Insns
    //
    [PPC32_IT_RLWNM_M1_0] = {arch:FEATURE_I_B, morph:morphRLWNM_M1_0},
    [PPC32_IT_RLWNMRC_M1_0] = {arch:FEATURE_I_B, morph:morphRLWNMRC_M1_0},

    //
    // Format M1_1 Insns
    //
    [PPC32_IT_RLWNMRC_0_M1_1] = {arch:FEATURE_I_B, morph:morphRLWNMRC_0_M1_1},
    [PPC32_IT_RLWNM_0_M1_1] = {arch:FEATURE_I_B, morph:morphRLWNM_0_M1_1},

    //
    // Format M2_0 Insns
    //
    [PPC32_IT_E_RLWIMI_M2_0] = {arch:FEATURE_I_VLE, morph:morphE_RLWIMI_M2_0},
    [PPC32_IT_E_RLWINM_M2_0] = {arch:FEATURE_I_VLE, morph:morphE_RLWINM_M2_0},
    [PPC32_IT_RLWIMI_M2_0] = {arch:FEATURE_I_B, morph:morphRLWIMI_M2_0},
    [PPC32_IT_RLWIMIRC_M2_0] = {arch:FEATURE_I_B, morph:morphRLWIMIRC_M2_0},
    [PPC32_IT_RLWINM_M2_0] = {arch:FEATURE_I_B, morph:morphRLWINM_M2_0},
    [PPC32_IT_RLWINMRC_M2_0] = {arch:FEATURE_I_B, morph:morphRLWINMRC_M2_0},

    //
    // Format M2_1 Insns
    //
    [PPC32_IT_RLWINMRC_0_M2_1] = {arch:FEATURE_I_B, morph:morphRLWINMRC_0_M2_1},
    [PPC32_IT_RLWINM_0_M2_1] = {arch:FEATURE_I_B, morph:morphRLWINM_0_M2_1},

    //
    // Format OIM51_0 Insns
    //
    [PPC32_IT_SE_BCLRI_OIM51_0] = {arch:FEATURE_I_VLE, morph:morphSE_BCLRI_OIM51_0},
    [PPC32_IT_SE_BGENI_OIM51_0] = {arch:FEATURE_I_VLE, morph:morphSE_BGENI_OIM51_0},
    [PPC32_IT_SE_BSETI_OIM51_0] = {arch:FEATURE_I_VLE, morph:morphSE_BSETI_OIM51_0},
    [PPC32_IT_SE_BTSTI_OIM51_0] = {arch:FEATURE_I_VLE, morph:morphSE_BTSTI_OIM51_0},
    [PPC32_IT_SE_SLWI_OIM51_0] = {arch:FEATURE_I_VLE, morph:morphSE_SLWI_OIM51_0},
    [PPC32_IT_SE_SRAWI_OIM51_0] = {arch:FEATURE_I_VLE, morph:morphSE_SRAWI_OIM51_0},
    [PPC32_IT_SE_SRWI_OIM51_0] = {arch:FEATURE_I_VLE, morph:morphSE_SRWI_OIM51_0},

    //
    // Format OIM51_1 Insns
    //
    [PPC32_IT_SE_ADDI_OIM51_1] = {arch:FEATURE_I_VLE, morph:morphSE_ADDI_OIM51_1},
    [PPC32_IT_SE_CMPLI_OIM51_1] = {arch:FEATURE_I_VLE, morph:morphSE_CMPLI_OIM51_1},

    //
    // Format OIM52_0 Insns
    //
    [PPC32_IT_SE_SUBI_OIM52_0] = {arch:FEATURE_I_VLE, morph:morphSE_SUBI_OIM52_0},
    [PPC32_IT_SE_SUBIRC_OIM52_0] = {arch:FEATURE_I_VLE, morph:morphSE_SUBIRC_OIM52_0},

    //
    // Format R1 Insns
    //
    [PPC32_IT_SE_EXTSB_R1] = {arch:FEATURE_I_VLE, morph:morphSE_EXTSB_R1},
    [PPC32_IT_SE_EXTSH_R1] = {arch:FEATURE_I_VLE, morph:morphSE_EXTSH_R1},
    [PPC32_IT_SE_EXTZB_R1] = {arch:FEATURE_I_VLE, morph:morphSE_EXTZB_R1},
    [PPC32_IT_SE_EXTZH_R1] = {arch:FEATURE_I_VLE, morph:morphSE_EXTZH_R1},
    [PPC32_IT_SE_MFCTR_R1] = {arch:FEATURE_I_VLE, morph:morphSE_MFCTR_R1},
    [PPC32_IT_SE_MFLR_R1] = {arch:FEATURE_I_VLE, morph:morphSE_MFLR_R1},
    [PPC32_IT_SE_MTCTR_R1] = {arch:FEATURE_I_VLE, morph:morphSE_MTCTR_R1},
    [PPC32_IT_SE_MTLR_R1] = {arch:FEATURE_I_VLE, morph:morphSE_MTLR_R1},
    [PPC32_IT_SE_NEG_R1] = {arch:FEATURE_I_VLE, morph:morphSE_NEG_R1},
    [PPC32_IT_SE_NOT_R1] = {arch:FEATURE_I_VLE, morph:morphSE_NOT_R1},

    //
    // Format RR1 Insns
    //
    [PPC32_IT_SE_ADD_RR1] = {arch:FEATURE_I_VLE, morph:morphSE_ADD_RR1},
    [PPC32_IT_SE_ANDC_RR1] = {arch:FEATURE_I_VLE, morph:morphSE_ANDC_RR1},
    [PPC32_IT_SE_CMP_RR1] = {arch:FEATURE_I_VLE, morph:morphSE_CMP_RR1},
    [PPC32_IT_SE_CMPH_RR1] = {arch:FEATURE_I_VLE, morph:morphSE_CMPH_RR1},
    [PPC32_IT_SE_CMPHL_RR1] = {arch:FEATURE_I_VLE, morph:morphSE_CMPHL_RR1},
    [PPC32_IT_SE_CMPL_RR1] = {arch:FEATURE_I_VLE, morph:morphSE_CMPL_RR1},
    [PPC32_IT_SE_MR_RR1] = {arch:FEATURE_I_VLE, morph:morphSE_MR_RR1},
    [PPC32_IT_SE_MULLW_RR1] = {arch:FEATURE_I_VLE, morph:morphSE_MULLW_RR1},
    [PPC32_IT_SE_OR_RR1] = {arch:FEATURE_I_VLE, morph:morphSE_OR_RR1},
    [PPC32_IT_SE_SLW_RR1] = {arch:FEATURE_I_VLE, morph:morphSE_SLW_RR1},
    [PPC32_IT_SE_SRAW_RR1] = {arch:FEATURE_I_VLE, morph:morphSE_SRAW_RR1},
    [PPC32_IT_SE_SRW_RR1] = {arch:FEATURE_I_VLE, morph:morphSE_SRW_RR1},
    [PPC32_IT_SE_SUB_RR1] = {arch:FEATURE_I_VLE, morph:morphSE_SUB_RR1},
    [PPC32_IT_SE_SUBF_RR1] = {arch:FEATURE_I_VLE, morph:morphSE_SUBF_RR1},

    //
    // Format RR2 Insns
    //
    [PPC32_IT_SE_AND_RR2] = {arch:FEATURE_I_VLE, morph:morphSE_AND_RR2},
    [PPC32_IT_SE_ANDRC_RR2] = {arch:FEATURE_I_VLE, morph:morphSE_ANDRC_RR2},

    //
    // Format RR3 Insns
    //
    [PPC32_IT_SE_MFAR_RR3] = {arch:FEATURE_I_VLE, morph:morphSE_MFAR_RR3},

    //
    // Format RR4 Insns
    //
    [PPC32_IT_SE_MTAR_RR4] = {arch:FEATURE_I_VLE, morph:morphSE_MTAR_RR4},

    //
    // Format SC1 Insns
    //
    [PPC32_IT_SC_SC1] = {arch:FEATURE_I_B, morph:morphSC_SC1},

    //
    // Format SCI8_1 Insns
    //
    [PPC32_IT_E_ADDI_SCI8_1] = {arch:FEATURE_I_VLE, morph:morphE_ADDI_SCI8_1},
    [PPC32_IT_E_ADDIC_SCI8_1] = {arch:FEATURE_I_VLE, morph:morphE_ADDIC_SCI8_1},
    [PPC32_IT_E_ADDICRC_SCI8_1] = {arch:FEATURE_I_VLE, morph:morphE_ADDICRC_SCI8_1},
    [PPC32_IT_E_ADDIRC_SCI8_1] = {arch:FEATURE_I_VLE, morph:morphE_ADDIRC_SCI8_1},
    [PPC32_IT_E_SUBFIC_SCI8_1] = {arch:FEATURE_I_VLE, morph:morphE_SUBFIC_SCI8_1},
    [PPC32_IT_E_SUBFICRC_SCI8_1] = {arch:FEATURE_I_VLE, morph:morphE_SUBFICRC_SCI8_1},

    //
    // Format SCI8_2 Insns
    //
    [PPC32_IT_E_MULLI_SCI8_2] = {arch:FEATURE_I_VLE, morph:morphE_MULLI_SCI8_2},

    //
    // Format SCI8_3 Insns
    //
    [PPC32_IT_E_ANDI_SCI8_3] = {arch:FEATURE_I_VLE, morph:morphE_ANDI_SCI8_3},
    [PPC32_IT_E_ANDIRC_SCI8_3] = {arch:FEATURE_I_VLE, morph:morphE_ANDIRC_SCI8_3},
    [PPC32_IT_E_ORI_SCI8_3] = {arch:FEATURE_I_VLE, morph:morphE_ORI_SCI8_3},
    [PPC32_IT_E_ORIRC_SCI8_3] = {arch:FEATURE_I_VLE, morph:morphE_ORIRC_SCI8_3},
    [PPC32_IT_E_XORI_SCI8_3] = {arch:FEATURE_I_VLE, morph:morphE_XORI_SCI8_3},
    [PPC32_IT_E_XORIRC_SCI8_3] = {arch:FEATURE_I_VLE, morph:morphE_XORIRC_SCI8_3},

    //
    // Format SCI8_5 Insns
    //
    [PPC32_IT_E_CMPI_SCI8_5] = {arch:FEATURE_I_VLE, morph:morphE_CMPI_SCI8_5},

    //
    // Format SCI8_6 Insns
    //
    [PPC32_IT_E_CMPLI_SCI8_6] = {arch:FEATURE_I_VLE, morph:morphE_CMPLI_SCI8_6},

    //
    // Format SD4_0 Insns
    //
    [PPC32_IT_SE_LBZ_SD4_0] = {arch:FEATURE_I_VLE, morph:morphSE_LBZ_SD4_0},
    [PPC32_IT_SE_STB_SD4_0] = {arch:FEATURE_I_VLE, morph:morphSE_STB_SD4_0},

    //
    // Format SD4_1 Insns
    //
    [PPC32_IT_SE_LHZ_SD4_1] = {arch:FEATURE_I_VLE, morph:morphSE_LHZ_SD4_1},
    [PPC32_IT_SE_STH_SD4_1] = {arch:FEATURE_I_VLE, morph:morphSE_STH_SD4_1},

    //
    // Format SD4_2 Insns
    //
    [PPC32_IT_SE_LWZ_SD4_2] = {arch:FEATURE_I_VLE, morph:morphSE_LWZ_SD4_2},
    [PPC32_IT_SE_STW_SD4_2] = {arch:FEATURE_I_VLE, morph:morphSE_STW_SD4_2},

    //
    // Format VA1_0 Insns
    //
    [PPC32_IT_VMHADDSHS_VA1_0] = {arch:FEATURE_I_V, morph:morphVMHADDSHS_VA1_0},
    [PPC32_IT_VMHRADDSHS_VA1_0] = {arch:FEATURE_I_V, morph:morphVMHRADDSHS_VA1_0},
    [PPC32_IT_VMLADDUHM_VA1_0] = {arch:FEATURE_I_V, morph:morphVMLADDUHM_VA1_0},
    [PPC32_IT_VMSUMMBM_VA1_0] = {arch:FEATURE_I_V, morph:morphVMSUMMBM_VA1_0},
    [PPC32_IT_VMSUMSHM_VA1_0] = {arch:FEATURE_I_V, morph:morphVMSUMSHM_VA1_0},
    [PPC32_IT_VMSUMSHS_VA1_0] = {arch:FEATURE_I_V, morph:morphVMSUMSHS_VA1_0},
    [PPC32_IT_VMSUMUBM_VA1_0] = {arch:FEATURE_I_V, morph:morphVMSUMUBM_VA1_0},
    [PPC32_IT_VMSUMUHM_VA1_0] = {arch:FEATURE_I_V, morph:morphVMSUMUHM_VA1_0},
    [PPC32_IT_VMSUMUHS_VA1_0] = {arch:FEATURE_I_V, morph:morphVMSUMUHS_VA1_0},
    [PPC32_IT_VPERM_VA1_0] = {arch:FEATURE_I_V, morph:morphVPERM_VA1_0},
    [PPC32_IT_VSEL_VA1_0] = {arch:FEATURE_I_V, morph:morphVSEL_VA1_0},

    //
    // Format VA1_1 Insns
    //
    [PPC32_IT_VMADDFP_VA1_1] = {arch:FEATURE_I_V, morph:morphVMADDFP_VA1_1},
    [PPC32_IT_VMSUBFP_VA1_1] = {arch:FEATURE_I_V, morph:morphVMSUBFP_VA1_1},

    //
    // Format VA2 Insns
    //
    [PPC32_IT_VSLDOI_VA2] = {arch:FEATURE_I_V, morph:morphVSLDOI_VA2},

    //
    // Format VC1 Insns
    //
    [PPC32_IT_VCMPBFP_VC1] = {arch:FEATURE_I_V, morph:morphVCMPBFP_VC1},
    [PPC32_IT_VCMPBFPRC_VC1] = {arch:FEATURE_I_V, morph:morphVCMPBFPRC_VC1},
    [PPC32_IT_VCMPEQFP_VC1] = {arch:FEATURE_I_V, morph:morphVCMPEQFP_VC1},
    [PPC32_IT_VCMPEQFPRC_VC1] = {arch:FEATURE_I_V, morph:morphVCMPEQFPRC_VC1},
    [PPC32_IT_VCMPEQUB_VC1] = {arch:FEATURE_I_V, morph:morphVCMPEQUB_VC1},
    [PPC32_IT_VCMPEQUBRC_VC1] = {arch:FEATURE_I_V, morph:morphVCMPEQUBRC_VC1},
    [PPC32_IT_VCMPEQUH_VC1] = {arch:FEATURE_I_V, morph:morphVCMPEQUH_VC1},
    [PPC32_IT_VCMPEQUHRC_VC1] = {arch:FEATURE_I_V, morph:morphVCMPEQUHRC_VC1},
    [PPC32_IT_VCMPEQUW_VC1] = {arch:FEATURE_I_V, morph:morphVCMPEQUW_VC1},
    [PPC32_IT_VCMPEQUWRC_VC1] = {arch:FEATURE_I_V, morph:morphVCMPEQUWRC_VC1},
    [PPC32_IT_VCMPGEFP_VC1] = {arch:FEATURE_I_V, morph:morphVCMPGEFP_VC1},
    [PPC32_IT_VCMPGEFPRC_VC1] = {arch:FEATURE_I_V, morph:morphVCMPGEFPRC_VC1},
    [PPC32_IT_VCMPGTFP_VC1] = {arch:FEATURE_I_V, morph:morphVCMPGTFP_VC1},
    [PPC32_IT_VCMPGTFPRC_VC1] = {arch:FEATURE_I_V, morph:morphVCMPGTFPRC_VC1},
    [PPC32_IT_VCMPGTSB_VC1] = {arch:FEATURE_I_V, morph:morphVCMPGTSB_VC1},
    [PPC32_IT_VCMPGTSBRC_VC1] = {arch:FEATURE_I_V, morph:morphVCMPGTSBRC_VC1},
    [PPC32_IT_VCMPGTSH_VC1] = {arch:FEATURE_I_V, morph:morphVCMPGTSH_VC1},
    [PPC32_IT_VCMPGTSHRC_VC1] = {arch:FEATURE_I_V, morph:morphVCMPGTSHRC_VC1},
    [PPC32_IT_VCMPGTSW_VC1] = {arch:FEATURE_I_V, morph:morphVCMPGTSW_VC1},
    [PPC32_IT_VCMPGTSWRC_VC1] = {arch:FEATURE_I_V, morph:morphVCMPGTSWRC_VC1},
    [PPC32_IT_VCMPGTUB_VC1] = {arch:FEATURE_I_V, morph:morphVCMPGTUB_VC1},
    [PPC32_IT_VCMPGTUBRC_VC1] = {arch:FEATURE_I_V, morph:morphVCMPGTUBRC_VC1},
    [PPC32_IT_VCMPGTUH_VC1] = {arch:FEATURE_I_V, morph:morphVCMPGTUH_VC1},
    [PPC32_IT_VCMPGTUHRC_VC1] = {arch:FEATURE_I_V, morph:morphVCMPGTUHRC_VC1},
    [PPC32_IT_VCMPGTUW_VC1] = {arch:FEATURE_I_V, morph:morphVCMPGTUW_VC1},
    [PPC32_IT_VCMPGTUWRC_VC1] = {arch:FEATURE_I_V, morph:morphVCMPGTUWRC_VC1},

    //
    // Format VX1 Insns
    //
    [PPC32_IT_VADDCUW_VX1] = {arch:FEATURE_I_V, morph:morphVADDCUW_VX1},
    [PPC32_IT_VADDFP_VX1] = {arch:FEATURE_I_V, morph:morphVADDFP_VX1},
    [PPC32_IT_VADDSBS_VX1] = {arch:FEATURE_I_V, morph:morphVADDSBS_VX1},
    [PPC32_IT_VADDSHS_VX1] = {arch:FEATURE_I_V, morph:morphVADDSHS_VX1},
    [PPC32_IT_VADDSWS_VX1] = {arch:FEATURE_I_V, morph:morphVADDSWS_VX1},
    [PPC32_IT_VADDUBM_VX1] = {arch:FEATURE_I_V, morph:morphVADDUBM_VX1},
    [PPC32_IT_VADDUBS_VX1] = {arch:FEATURE_I_V, morph:morphVADDUBS_VX1},
    [PPC32_IT_VADDUHM_VX1] = {arch:FEATURE_I_V, morph:morphVADDUHM_VX1},
    [PPC32_IT_VADDUHS_VX1] = {arch:FEATURE_I_V, morph:morphVADDUHS_VX1},
    [PPC32_IT_VADDUWM_VX1] = {arch:FEATURE_I_V, morph:morphVADDUWM_VX1},
    [PPC32_IT_VADDUWS_VX1] = {arch:FEATURE_I_V, morph:morphVADDUWS_VX1},
    [PPC32_IT_VAND_VX1] = {arch:FEATURE_I_V, morph:morphVAND_VX1},
    [PPC32_IT_VANDC_VX1] = {arch:FEATURE_I_V, morph:morphVANDC_VX1},
    [PPC32_IT_VAVGSB_VX1] = {arch:FEATURE_I_V, morph:morphVAVGSB_VX1},
    [PPC32_IT_VAVGSH_VX1] = {arch:FEATURE_I_V, morph:morphVAVGSH_VX1},
    [PPC32_IT_VAVGSW_VX1] = {arch:FEATURE_I_V, morph:morphVAVGSW_VX1},
    [PPC32_IT_VAVGUB_VX1] = {arch:FEATURE_I_V, morph:morphVAVGUB_VX1},
    [PPC32_IT_VAVGUH_VX1] = {arch:FEATURE_I_V, morph:morphVAVGUH_VX1},
    [PPC32_IT_VAVGUW_VX1] = {arch:FEATURE_I_V, morph:morphVAVGUW_VX1},
    [PPC32_IT_VKPPX_VX1] = {arch:FEATURE_I_V, morph:morphVKPPX_VX1},
    [PPC32_IT_VKPSHSS_VX1] = {arch:FEATURE_I_V, morph:morphVKPSHSS_VX1},
    [PPC32_IT_VKPSHUS_VX1] = {arch:FEATURE_I_V, morph:morphVKPSHUS_VX1},
    [PPC32_IT_VKPSWSS_VX1] = {arch:FEATURE_I_V, morph:morphVKPSWSS_VX1},
    [PPC32_IT_VKPSWUS_VX1] = {arch:FEATURE_I_V, morph:morphVKPSWUS_VX1},
    [PPC32_IT_VKPUHUM_VX1] = {arch:FEATURE_I_V, morph:morphVKPUHUM_VX1},
    [PPC32_IT_VKPUHUS_VX1] = {arch:FEATURE_I_V, morph:morphVKPUHUS_VX1},
    [PPC32_IT_VKPUWUM_VX1] = {arch:FEATURE_I_V, morph:morphVKPUWUM_VX1},
    [PPC32_IT_VKPUWUS_VX1] = {arch:FEATURE_I_V, morph:morphVKPUWUS_VX1},
    [PPC32_IT_VMAXFP_VX1] = {arch:FEATURE_I_V, morph:morphVMAXFP_VX1},
    [PPC32_IT_VMAXSB_VX1] = {arch:FEATURE_I_V, morph:morphVMAXSB_VX1},
    [PPC32_IT_VMAXSH_VX1] = {arch:FEATURE_I_V, morph:morphVMAXSH_VX1},
    [PPC32_IT_VMAXSW_VX1] = {arch:FEATURE_I_V, morph:morphVMAXSW_VX1},
    [PPC32_IT_VMAXUB_VX1] = {arch:FEATURE_I_V, morph:morphVMAXUB_VX1},
    [PPC32_IT_VMAXUH_VX1] = {arch:FEATURE_I_V, morph:morphVMAXUH_VX1},
    [PPC32_IT_VMAXUW_VX1] = {arch:FEATURE_I_V, morph:morphVMAXUW_VX1},
    [PPC32_IT_VMINFP_VX1] = {arch:FEATURE_I_V, morph:morphVMINFP_VX1},
    [PPC32_IT_VMINSB_VX1] = {arch:FEATURE_I_V, morph:morphVMINSB_VX1},
    [PPC32_IT_VMINSH_VX1] = {arch:FEATURE_I_V, morph:morphVMINSH_VX1},
    [PPC32_IT_VMINSW_VX1] = {arch:FEATURE_I_V, morph:morphVMINSW_VX1},
    [PPC32_IT_VMINUB_VX1] = {arch:FEATURE_I_V, morph:morphVMINUB_VX1},
    [PPC32_IT_VMINUH_VX1] = {arch:FEATURE_I_V, morph:morphVMINUH_VX1},
    [PPC32_IT_VMINUW_VX1] = {arch:FEATURE_I_V, morph:morphVMINUW_VX1},
    [PPC32_IT_VMRGHB_VX1] = {arch:FEATURE_I_V, morph:morphVMRGHB_VX1},
    [PPC32_IT_VMRGHH_VX1] = {arch:FEATURE_I_V, morph:morphVMRGHH_VX1},
    [PPC32_IT_VMRGHW_VX1] = {arch:FEATURE_I_V, morph:morphVMRGHW_VX1},
    [PPC32_IT_VMRGLB_VX1] = {arch:FEATURE_I_V, morph:morphVMRGLB_VX1},
    [PPC32_IT_VMRGLH_VX1] = {arch:FEATURE_I_V, morph:morphVMRGLH_VX1},
    [PPC32_IT_VMRGLW_VX1] = {arch:FEATURE_I_V, morph:morphVMRGLW_VX1},
    [PPC32_IT_VMULESB_VX1] = {arch:FEATURE_I_V, morph:morphVMULESB_VX1},
    [PPC32_IT_VMULESH_VX1] = {arch:FEATURE_I_V, morph:morphVMULESH_VX1},
    [PPC32_IT_VMULEUB_VX1] = {arch:FEATURE_I_V, morph:morphVMULEUB_VX1},
    [PPC32_IT_VMULEUH_VX1] = {arch:FEATURE_I_V, morph:morphVMULEUH_VX1},
    [PPC32_IT_VMULOSB_VX1] = {arch:FEATURE_I_V, morph:morphVMULOSB_VX1},
    [PPC32_IT_VMULOSH_VX1] = {arch:FEATURE_I_V, morph:morphVMULOSH_VX1},
    [PPC32_IT_VMULOUB_VX1] = {arch:FEATURE_I_V, morph:morphVMULOUB_VX1},
    [PPC32_IT_VMULOUH_VX1] = {arch:FEATURE_I_V, morph:morphVMULOUH_VX1},
    [PPC32_IT_VNOR_VX1] = {arch:FEATURE_I_V, morph:morphVNOR_VX1},
    [PPC32_IT_VOR_VX1] = {arch:FEATURE_I_V, morph:morphVOR_VX1},
    [PPC32_IT_VRLB_VX1] = {arch:FEATURE_I_V, morph:morphVRLB_VX1},
    [PPC32_IT_VRLH_VX1] = {arch:FEATURE_I_V, morph:morphVRLH_VX1},
    [PPC32_IT_VRLW_VX1] = {arch:FEATURE_I_V, morph:morphVRLW_VX1},
    [PPC32_IT_VSL_VX1] = {arch:FEATURE_I_V, morph:morphVSL_VX1},
    [PPC32_IT_VSLB_VX1] = {arch:FEATURE_I_V, morph:morphVSLB_VX1},
    [PPC32_IT_VSLH_VX1] = {arch:FEATURE_I_V, morph:morphVSLH_VX1},
    [PPC32_IT_VSLO_VX1] = {arch:FEATURE_I_V, morph:morphVSLO_VX1},
    [PPC32_IT_VSLW_VX1] = {arch:FEATURE_I_V, morph:morphVSLW_VX1},
    [PPC32_IT_VSR_VX1] = {arch:FEATURE_I_V, morph:morphVSR_VX1},
    [PPC32_IT_VSRAB_VX1] = {arch:FEATURE_I_V, morph:morphVSRAB_VX1},
    [PPC32_IT_VSRAH_VX1] = {arch:FEATURE_I_V, morph:morphVSRAH_VX1},
    [PPC32_IT_VSRAW_VX1] = {arch:FEATURE_I_V, morph:morphVSRAW_VX1},
    [PPC32_IT_VSRB_VX1] = {arch:FEATURE_I_V, morph:morphVSRB_VX1},
    [PPC32_IT_VSRH_VX1] = {arch:FEATURE_I_V, morph:morphVSRH_VX1},
    [PPC32_IT_VSRO_VX1] = {arch:FEATURE_I_V, morph:morphVSRO_VX1},
    [PPC32_IT_VSRW_VX1] = {arch:FEATURE_I_V, morph:morphVSRW_VX1},
    [PPC32_IT_VSUBCUW_VX1] = {arch:FEATURE_I_V, morph:morphVSUBCUW_VX1},
    [PPC32_IT_VSUBFP_VX1] = {arch:FEATURE_I_V, morph:morphVSUBFP_VX1},
    [PPC32_IT_VSUBSBS_VX1] = {arch:FEATURE_I_V, morph:morphVSUBSBS_VX1},
    [PPC32_IT_VSUBSHS_VX1] = {arch:FEATURE_I_V, morph:morphVSUBSHS_VX1},
    [PPC32_IT_VSUBSWS_VX1] = {arch:FEATURE_I_V, morph:morphVSUBSWS_VX1},
    [PPC32_IT_VSUBUBM_VX1] = {arch:FEATURE_I_V, morph:morphVSUBUBM_VX1},
    [PPC32_IT_VSUBUBS_VX1] = {arch:FEATURE_I_V, morph:morphVSUBUBS_VX1},
    [PPC32_IT_VSUBUHM_VX1] = {arch:FEATURE_I_V, morph:morphVSUBUHM_VX1},
    [PPC32_IT_VSUBUHS_VX1] = {arch:FEATURE_I_V, morph:morphVSUBUHS_VX1},
    [PPC32_IT_VSUBUWM_VX1] = {arch:FEATURE_I_V, morph:morphVSUBUWM_VX1},
    [PPC32_IT_VSUBUWS_VX1] = {arch:FEATURE_I_V, morph:morphVSUBUWS_VX1},
    [PPC32_IT_VSUM2SWS_VX1] = {arch:FEATURE_I_V, morph:morphVSUM2SWS_VX1},
    [PPC32_IT_VSUM4SBS_VX1] = {arch:FEATURE_I_V, morph:morphVSUM4SBS_VX1},
    [PPC32_IT_VSUM4SHS_VX1] = {arch:FEATURE_I_V, morph:morphVSUM4SHS_VX1},
    [PPC32_IT_VSUM4UBS_VX1] = {arch:FEATURE_I_V, morph:morphVSUM4UBS_VX1},
    [PPC32_IT_VSUMSWS_VX1] = {arch:FEATURE_I_V, morph:morphVSUMSWS_VX1},
    [PPC32_IT_VXOR_VX1] = {arch:FEATURE_I_V, morph:morphVXOR_VX1},

    //
    // Format VX2 Insns
    //
    [PPC32_IT_VEXPTEFP_VX2] = {arch:FEATURE_I_V, morph:morphVEXPTEFP_VX2},
    [PPC32_IT_VLOGEFP_VX2] = {arch:FEATURE_I_V, morph:morphVLOGEFP_VX2},
    [PPC32_IT_VREFP_VX2] = {arch:FEATURE_I_V, morph:morphVREFP_VX2},
    [PPC32_IT_VRFIM_VX2] = {arch:FEATURE_I_V, morph:morphVRFIM_VX2},
    [PPC32_IT_VRFIN_VX2] = {arch:FEATURE_I_V, morph:morphVRFIN_VX2},
    [PPC32_IT_VRFIP_VX2] = {arch:FEATURE_I_V, morph:morphVRFIP_VX2},
    [PPC32_IT_VRFIZ_VX2] = {arch:FEATURE_I_V, morph:morphVRFIZ_VX2},
    [PPC32_IT_VRSQRTEFP_VX2] = {arch:FEATURE_I_V, morph:morphVRSQRTEFP_VX2},
    [PPC32_IT_VUPKHPX_VX2] = {arch:FEATURE_I_V, morph:morphVUPKHPX_VX2},
    [PPC32_IT_VUPKHSB_VX2] = {arch:FEATURE_I_V, morph:morphVUPKHSB_VX2},
    [PPC32_IT_VUPKHSH_VX2] = {arch:FEATURE_I_V, morph:morphVUPKHSH_VX2},
    [PPC32_IT_VUPKLPX_VX2] = {arch:FEATURE_I_V, morph:morphVUPKLPX_VX2},
    [PPC32_IT_VUPKLSB_VX2] = {arch:FEATURE_I_V, morph:morphVUPKLSB_VX2},
    [PPC32_IT_VUPKLSH_VX2] = {arch:FEATURE_I_V, morph:morphVUPKLSH_VX2},

    //
    // Format VX3 Insns
    //
    [PPC32_IT_VCFSX_VX3] = {arch:FEATURE_I_V, morph:morphVCFSX_VX3},
    [PPC32_IT_VCFUX_VX3] = {arch:FEATURE_I_V, morph:morphVCFUX_VX3},
    [PPC32_IT_VCTSXS_VX3] = {arch:FEATURE_I_V, morph:morphVCTSXS_VX3},
    [PPC32_IT_VCTUXS_VX3] = {arch:FEATURE_I_V, morph:morphVCTUXS_VX3},

    //
    // Format VX4 Insns
    //
    [PPC32_IT_VSPLTB_VX4] = {arch:FEATURE_I_V, morph:morphVSPLTB_VX4},

    //
    // Format VX5 Insns
    //
    [PPC32_IT_VSPLTH_VX5] = {arch:FEATURE_I_V, morph:morphVSPLTH_VX5},

    //
    // Format VX6 Insns
    //
    [PPC32_IT_VSPLTW_VX6] = {arch:FEATURE_I_V, morph:morphVSPLTW_VX6},

    //
    // Format VX7 Insns
    //
    [PPC32_IT_VSPLTISB_VX7] = {arch:FEATURE_I_V, morph:morphVSPLTISB_VX7},
    [PPC32_IT_VSPLTISH_VX7] = {arch:FEATURE_I_V, morph:morphVSPLTISH_VX7},
    [PPC32_IT_VSPLTISW_VX7] = {arch:FEATURE_I_V, morph:morphVSPLTISW_VX7},

    //
    // Format VX8 Insns
    //
    [PPC32_IT_MFVSCR_VX8] = {arch:FEATURE_I_V, morph:morphMFVSCR_VX8},

    //
    // Format VX9 Insns
    //
    [PPC32_IT_MTVSCR_VX9] = {arch:FEATURE_I_V, morph:morphMTVSCR_VX9},

    //
    // Format X1 Insns
    //
    [PPC32_IT_MFAPIDI_X1] = {arch:FEATURE_I_E, morph:morphMFAPIDI_X1},
    [PPC32_IT_MFDCRUX_X1] = {arch:FEATURE_I_E, morph:morphMFDCRUX_X1},
    [PPC32_IT_MFDCRX_X1] = {arch:FEATURE_I_E, morph:morphMFDCRX_X1},

    //
    // Format X10 Insns
    //
    [PPC32_IT_MULCHW_X10] = {arch:FEATURE_I_LMA, morph:morphMULCHW_X10},
    [PPC32_IT_MULCHWRC_X10] = {arch:FEATURE_I_LMA, morph:morphMULCHWRC_X10},
    [PPC32_IT_MULCHWU_X10] = {arch:FEATURE_I_LMA, morph:morphMULCHWU_X10},
    [PPC32_IT_MULCHWURC_X10] = {arch:FEATURE_I_LMA, morph:morphMULCHWURC_X10},
    [PPC32_IT_MULHHW_X10] = {arch:FEATURE_I_LMA, morph:morphMULHHW_X10},
    [PPC32_IT_MULHHWRC_X10] = {arch:FEATURE_I_LMA, morph:morphMULHHWRC_X10},
    [PPC32_IT_MULHHWU_X10] = {arch:FEATURE_I_LMA, morph:morphMULHHWU_X10},
    [PPC32_IT_MULHHWURC_X10] = {arch:FEATURE_I_LMA, morph:morphMULHHWURC_X10},
    [PPC32_IT_MULLHW_X10] = {arch:FEATURE_I_LMA, morph:morphMULLHW_X10},
    [PPC32_IT_MULLHWRC_X10] = {arch:FEATURE_I_LMA, morph:morphMULLHWRC_X10},
    [PPC32_IT_MULLHWU_X10] = {arch:FEATURE_I_LMA, morph:morphMULLHWU_X10},
    [PPC32_IT_MULLHWURC_X10] = {arch:FEATURE_I_LMA, morph:morphMULLHWURC_X10},

    //
    // Format X11 Insns
    //
    [PPC32_IT_STWCXRC_X11] = {arch:FEATURE_I_B, morph:morphSTWCXRC_X11},

    //
    // Format X12 Insns
    //
    [PPC32_IT_CMPB_X12] = {arch:FEATURE_I_B, morph:morphCMPB_X12},
    [PPC32_IT_STBCIX_X12] = {arch:FEATURE_I_S, morph:morphSTBCIX_X12},
    [PPC32_IT_STBEPX_X12] = {arch:FEATURE_I_E_PD, morph:morphSTBEPX_X12},
    [PPC32_IT_STBUX_X12] = {arch:FEATURE_I_B, morph:morphSTBUX_X12},
    [PPC32_IT_STBX_X12] = {arch:FEATURE_I_B, morph:morphSTBX_X12},
    [PPC32_IT_STDCIX_X12] = {arch:FEATURE_I_S, morph:morphSTDCIX_X12},
    [PPC32_IT_STDEPX_X12] = {arch:FEATURE_I_E_PD, morph:morphSTDEPX_X12},
    [PPC32_IT_STHBRX_X12] = {arch:FEATURE_I_B, morph:morphSTHBRX_X12},
    [PPC32_IT_STHCIX_X12] = {arch:FEATURE_I_S, morph:morphSTHCIX_X12},
    [PPC32_IT_STHEPX_X12] = {arch:FEATURE_I_E_PD, morph:morphSTHEPX_X12},
    [PPC32_IT_STHUX_X12] = {arch:FEATURE_I_B, morph:morphSTHUX_X12},
    [PPC32_IT_STHX_X12] = {arch:FEATURE_I_B, morph:morphSTHX_X12},
    [PPC32_IT_STSWX_X12] = {arch:FEATURE_I_MA, morph:morphSTSWX_X12},
    [PPC32_IT_STWBRX_X12] = {arch:FEATURE_I_B, morph:morphSTWBRX_X12},
    [PPC32_IT_STWCIX_X12] = {arch:FEATURE_I_S, morph:morphSTWCIX_X12},
    [PPC32_IT_STWEPX_X12] = {arch:FEATURE_I_E_PD, morph:morphSTWEPX_X12},
    [PPC32_IT_STWUX_X12] = {arch:FEATURE_I_B, morph:morphSTWUX_X12},
    [PPC32_IT_STWX_X12] = {arch:FEATURE_I_B, morph:morphSTWX_X12},

    //
    // Format X13 Insns
    //
    [PPC32_IT_STSWI_X13] = {arch:FEATURE_I_MA, morph:morphSTSWI_X13},

    //
    // Format X14 Insns
    //
    [PPC32_IT_E_RLWI_X14] = {arch:FEATURE_I_VLE, morph:morphE_RLWI_X14},
    [PPC32_IT_E_RLWIRC_X14] = {arch:FEATURE_I_VLE, morph:morphE_RLWIRC_X14},
    [PPC32_IT_E_SLWI_X14] = {arch:FEATURE_I_VLE, morph:morphE_SLWI_X14},
    [PPC32_IT_E_SLWIRC_X14] = {arch:FEATURE_I_VLE, morph:morphE_SLWIRC_X14},
    [PPC32_IT_E_SRWI_X14] = {arch:FEATURE_I_VLE, morph:morphE_SRWI_X14},
    [PPC32_IT_E_SRWIRC_X14] = {arch:FEATURE_I_VLE, morph:morphE_SRWIRC_X14},
    [PPC32_IT_SRAWI_X14] = {arch:FEATURE_I_B, morph:morphSRAWI_X14},
    [PPC32_IT_SRAWIRC_X14] = {arch:FEATURE_I_B, morph:morphSRAWIRC_X14},

    //
    // Format X15 Insns
    //
    [PPC32_IT_CNTLZW_X15] = {arch:FEATURE_I_B, morph:morphCNTLZW_X15},
    [PPC32_IT_CNTLZWRC_X15] = {arch:FEATURE_I_B, morph:morphCNTLZWRC_X15},
    [PPC32_IT_EXTSB_X15] = {arch:FEATURE_I_B, morph:morphEXTSB_X15},
    [PPC32_IT_EXTSBRC_X15] = {arch:FEATURE_I_B, morph:morphEXTSBRC_X15},
    [PPC32_IT_EXTSH_X15] = {arch:FEATURE_I_B, morph:morphEXTSH_X15},
    [PPC32_IT_EXTSHRC_X15] = {arch:FEATURE_I_B, morph:morphEXTSHRC_X15},

    //
    // Format X16 Insns
    //
    [PPC32_IT_CBCDTD_X16] = {arch:FEATURE_I_BCDA, morph:morphCBCDTD_X16},
    [PPC32_IT_CDTBCD_X16] = {arch:FEATURE_I_BCDA, morph:morphCDTBCD_X16},
    [PPC32_IT_MTDCRUX_X16] = {arch:FEATURE_I_E, morph:morphMTDCRUX_X16},
    [PPC32_IT_MTDCRX_X16] = {arch:FEATURE_I_E, morph:morphMTDCRX_X16},
    [PPC32_IT_POPCNTB_X16] = {arch:FEATURE_I_B, morph:morphPOPCNTB_X16},
    [PPC32_IT_PRTYW_X16] = {arch:FEATURE_I_B, morph:morphPRTYW_X16},

    //
    // Format X17 Insns
    //
    [PPC32_IT_MTSR_X17] = {arch:FEATURE_I_S, morph:morphMTSR_X17},

    //
    // Format X18 Insns
    //
    [PPC32_IT_MTSRIN_X18] = {arch:FEATURE_I_S, morph:morphMTSRIN_X18},
    [PPC32_IT_SLBMTE_X18] = {arch:FEATURE_I_S, morph:morphSLBMTE_X18},

    //
    // Format X19_0 Insns
    //
    [PPC32_IT_MTMSR_X19_0] = {arch:FEATURE_I_E, morph:morphMTMSR_X19_0},

    //
    // Format X19_1 Insns
    //
    [PPC32_IT_WRTEE_X19_1] = {arch:FEATURE_I_E, morph:morphWRTEE_X19_1},

    //
    // Format X2 Insns
    //
    [PPC32_IT_DCREAD_X2] = {arch:FEATURE_I_E, morph:morphDCREAD_X2},
    [PPC32_IT_ECIWX_X2] = {arch:FEATURE_I_E_PD, morph:morphECIWX_X2},
    [PPC32_IT_ECOWX_X2] = {arch:FEATURE_I_E_PD, morph:morphECOWX_X2},
    [PPC32_IT_LBEPX_X2] = {arch:FEATURE_I_E_PD, morph:morphLBEPX_X2},
    [PPC32_IT_LBZCIX_X2] = {arch:FEATURE_I_S, morph:morphLBZCIX_X2},
    [PPC32_IT_LBZUX_X2] = {arch:FEATURE_I_B, morph:morphLBZUX_X2},
    [PPC32_IT_LBZX_X2] = {arch:FEATURE_I_B, morph:morphLBZX_X2},
    [PPC32_IT_LDCIX_X2] = {arch:FEATURE_I_S, morph:morphLDCIX_X2},
    [PPC32_IT_LDEPX_X2] = {arch:FEATURE_I_E_PD, morph:morphLDEPX_X2},
    [PPC32_IT_LHAUX_X2] = {arch:FEATURE_I_B, morph:morphLHAUX_X2},
    [PPC32_IT_LHAX_X2] = {arch:FEATURE_I_B, morph:morphLHAX_X2},
    [PPC32_IT_LHBRX_X2] = {arch:FEATURE_I_B, morph:morphLHBRX_X2},
    [PPC32_IT_LHEPX_X2] = {arch:FEATURE_I_E_PD, morph:morphLHEPX_X2},
    [PPC32_IT_LHZCIX_X2] = {arch:FEATURE_I_S, morph:morphLHZCIX_X2},
    [PPC32_IT_LHZUX_X2] = {arch:FEATURE_I_B, morph:morphLHZUX_X2},
    [PPC32_IT_LHZX_X2] = {arch:FEATURE_I_B, morph:morphLHZX_X2},
    [PPC32_IT_LSWX_X2] = {arch:FEATURE_I_MA, morph:morphLSWX_X2},
    [PPC32_IT_LWBRX_X2] = {arch:FEATURE_I_B, morph:morphLWBRX_X2},
    [PPC32_IT_LWEPX_X2] = {arch:FEATURE_I_E_PD, morph:morphLWEPX_X2},
    [PPC32_IT_LWZCIX_X2] = {arch:FEATURE_I_S, morph:morphLWZCIX_X2},
    [PPC32_IT_LWZUX_X2] = {arch:FEATURE_I_B, morph:morphLWZUX_X2},
    [PPC32_IT_LWZX_X2] = {arch:FEATURE_I_B, morph:morphLWZX_X2},

    //
    // Format X20 Insns
    //
    [PPC32_IT_MTMSRD_X20] = {arch:FEATURE_I_S, morph:morphMTMSRD_X20},

    //
    // Format X22_0 Insns
    //
    [PPC32_IT_CMPLW_X22_0] = {arch:FEATURE_I_B, morph:morphCMPLW_X22_0},
    [PPC32_IT_CMPW_X22_0] = {arch:FEATURE_I_B, morph:morphCMPW_X22_0},

    //
    // Format X22_1 Insns
    //
    [PPC32_IT_CMP_X22_1] = {arch:FEATURE_I_B, morph:morphCMP_X22_1},
    [PPC32_IT_CMPL_X22_1] = {arch:FEATURE_I_B, morph:morphCMPL_X22_1},

    //
    // Format X22_2 Insns
    //
    [PPC32_IT_E_CMPH_X22_2] = {arch:FEATURE_I_VLE, morph:morphE_CMPH_X22_2},
    [PPC32_IT_E_CMPHL_X22_2] = {arch:FEATURE_I_VLE, morph:morphE_CMPHL_X22_2},

    //
    // Format X23 Insns
    //
    [PPC32_IT_DCMPO_X23] = {arch:FEATURE_I_DFP, morph:morphDCMPO_X23},
    [PPC32_IT_DCMPU_X23] = {arch:FEATURE_I_DFP, morph:morphDCMPU_X23},
    [PPC32_IT_DTSTEX_X23] = {arch:FEATURE_I_DFP, morph:morphDTSTEX_X23},
    [PPC32_IT_DTSTSF_X23] = {arch:FEATURE_I_DFP, morph:morphDTSTSF_X23},
    [PPC32_IT_FCMPO_X23] = {arch:FEATURE_I_FP, morph:morphFCMPO_X23},
    [PPC32_IT_FCMPU_X23] = {arch:FEATURE_I_FP, morph:morphFCMPU_X23},

    //
    // Format X24 Insns
    //
    [PPC32_IT_MCRFS_X24] = {arch:FEATURE_I_FP, morph:morphMCRFS_X24},

    //
    // Format X25_0 Insns
    //
    [PPC32_IT_MTFSFIZ_X25_0] = {arch:FEATURE_I_FP, morph:morphMTFSFIZ_X25_0},
    [PPC32_IT_MTFSFIZRC_X25_0] = {arch:FEATURE_I_FP, morph:morphMTFSFIZRC_X25_0},

    //
    // Format X25_1 Insns
    //
    [PPC32_IT_MTFSFI_X25_1] = {arch:FEATURE_I_FP, morph:morphMTFSFI_X25_1},
    [PPC32_IT_MTFSFIRC_X25_1] = {arch:FEATURE_I_FP, morph:morphMTFSFIRC_X25_1},

    //
    // Format X26 Insns
    //
    [PPC32_IT_MCRXR_X26] = {arch:FEATURE_I_E, morph:morphMCRXR_X26},

    //
    // Format X27_0 Insns
    //
    [PPC32_IT_DCBT_X27_0] = {arch:FEATURE_I_B, morph:morphDCBT_X27_0},
    [PPC32_IT_DCBTST_X27_0] = {arch:FEATURE_I_B, morph:morphDCBTST_X27_0},

    //
    // Format X27_1 Insns
    //
    [PPC32_IT_DCBTST_1_X27_1] = {arch:FEATURE_I_B, morph:morphDCBTST_1_X27_1},
    [PPC32_IT_DCBT_1_X27_1] = {arch:FEATURE_I_B, morph:morphDCBT_1_X27_1},

    //
    // Format X27_2 Insns
    //
    [PPC32_IT_DCBTEP_X27_2] = {arch:FEATURE_I_E_PD, morph:morphDCBTEP_X27_2},
    [PPC32_IT_DCBTSTEP_X27_2] = {arch:FEATURE_I_E_PD, morph:morphDCBTSTEP_X27_2},

    //
    // Format X28_0 Insns
    //
    [PPC32_IT_DCI_0_X28_0] = {arch:FEATURE_I_E, morph:morphDCI_0_X28_0},
    [PPC32_IT_ICI_0_X28_0] = {arch:FEATURE_I_E, morph:morphICI_0_X28_0},

    //
    // Format X28_1 Insns
    //
    [PPC32_IT_DCI_X28_1] = {arch:FEATURE_I_E, morph:morphDCI_X28_1},
    [PPC32_IT_ICI_X28_1] = {arch:FEATURE_I_E, morph:morphICI_X28_1},

    //
    // Format X29_0 Insns
    //
    [PPC32_IT_DCBLC_0_X29_0] = {arch:FEATURE_I_E_PD, morph:morphDCBLC_0_X29_0},
    [PPC32_IT_DCBTLS_0_X29_0] = {arch:FEATURE_I_E_PD, morph:morphDCBTLS_0_X29_0},
    [PPC32_IT_DCBTSTLS_0_X29_0] = {arch:FEATURE_I_E_PD, morph:morphDCBTSTLS_0_X29_0},
    [PPC32_IT_ICBLC_0_X29_0] = {arch:FEATURE_I_E_PD, morph:morphICBLC_0_X29_0},
    [PPC32_IT_ICBTLS_0_X29_0] = {arch:FEATURE_I_E_PD, morph:morphICBTLS_0_X29_0},
    [PPC32_IT_ICBT_CT0_X29_0] = {arch:FEATURE_I_E, morph:morphICBT_CT0_X29_0},

    //
    // Format X29_1 Insns
    //
    [PPC32_IT_DCBLC_1_X29_1] = {arch:FEATURE_I_E_PD, morph:morphDCBLC_1_X29_1},
    [PPC32_IT_DCBTLS_1_X29_1] = {arch:FEATURE_I_E_PD, morph:morphDCBTLS_1_X29_1},
    [PPC32_IT_DCBTSTLS_1_X29_1] = {arch:FEATURE_I_E_PD, morph:morphDCBTSTLS_1_X29_1},
    [PPC32_IT_ICBLC_1_X29_1] = {arch:FEATURE_I_E_PD, morph:morphICBLC_1_X29_1},
    [PPC32_IT_ICBT_X29_1] = {arch:FEATURE_I_E, morph:morphICBT_X29_1},
    [PPC32_IT_ICBTLS_1_X29_1] = {arch:FEATURE_I_E_PD, morph:morphICBTLS_1_X29_1},

    //
    // Format X3 Insns
    //
    [PPC32_IT_LWARX_X3] = {arch:FEATURE_I_B, morph:morphLWARX_X3},

    //
    // Format X30 Insns
    //
    [PPC32_IT_DCBF_X30] = {arch:FEATURE_I_B, morph:morphDCBF_X30},
    [PPC32_IT_DCBF_L_X30] = {arch:FEATURE_I_S, morph:morphDCBF_L_X30},
    [PPC32_IT_DCBF_LP_X30] = {arch:FEATURE_I_S, morph:morphDCBF_LP_X30},

    //
    // Format X31_0 Insns
    //
    [PPC32_IT_TLBIEL_0_X31_0] = {arch:FEATURE_I_S, morph:morphTLBIEL_0_X31_0},
    [PPC32_IT_TLBIE_0_X31_0] = {arch:FEATURE_I_S, morph:morphTLBIE_0_X31_0},

    //
    // Format X31_1 Insns
    //
    [PPC32_IT_TLBIEL_1_X31_1] = {arch:FEATURE_I_S, morph:morphTLBIEL_1_X31_1},
    [PPC32_IT_TLBIE_1_X31_1] = {arch:FEATURE_I_S, morph:morphTLBIE_1_X31_1},

    //
    // Format X32 Insns
    //
    [PPC32_IT_LWSYNC_X32] = {arch:FEATURE_I_B, morph:morphLWSYNC_X32},
    [PPC32_IT_PTESYNC_X32] = {arch:FEATURE_I_B, morph:morphPTESYNC_X32},
    [PPC32_IT_SYNC_X32] = {arch:FEATURE_I_B, morph:morphSYNC_X32},

    //
    // Format X33 Insns
    //
    [PPC32_IT_TW_X33] = {arch:FEATURE_I_B, morph:morphTW_X33},

    //
    // Format X34 Insns
    //
    [PPC32_IT_LFDEPX_X34] = {arch:FEATURE_I_E_PD, morph:morphLFDEPX_X34},
    [PPC32_IT_LFDUX_X34] = {arch:FEATURE_I_FP, morph:morphLFDUX_X34},
    [PPC32_IT_LFDX_X34] = {arch:FEATURE_I_FP, morph:morphLFDX_X34},
    [PPC32_IT_LFIWAX_X34] = {arch:FEATURE_I_FP, morph:morphLFIWAX_X34},
    [PPC32_IT_LFSUX_X34] = {arch:FEATURE_I_FP, morph:morphLFSUX_X34},
    [PPC32_IT_LFSX_X34] = {arch:FEATURE_I_FP, morph:morphLFSX_X34},
    [PPC32_IT_STFDEPX_X34] = {arch:FEATURE_I_E_PD, morph:morphSTFDEPX_X34},

    //
    // Format X35RC Insns
    //
    [PPC32_IT_DADD_X35RC] = {arch:FEATURE_I_DFP, morph:morphDADD_X35RC},
    [PPC32_IT_DADDRC_X35RC] = {arch:FEATURE_I_DFP, morph:morphDADDRC_X35RC},
    [PPC32_IT_DDIV_X35RC] = {arch:FEATURE_I_DFP, morph:morphDDIV_X35RC},
    [PPC32_IT_DDIVRC_X35RC] = {arch:FEATURE_I_DFP, morph:morphDDIVRC_X35RC},
    [PPC32_IT_DIEX_X35RC] = {arch:FEATURE_I_DFP, morph:morphDIEX_X35RC},
    [PPC32_IT_DIEXRC_X35RC] = {arch:FEATURE_I_DFP, morph:morphDIEXRC_X35RC},
    [PPC32_IT_DMUL_X35RC] = {arch:FEATURE_I_DFP, morph:morphDMUL_X35RC},
    [PPC32_IT_DMULRC_X35RC] = {arch:FEATURE_I_DFP, morph:morphDMULRC_X35RC},
    [PPC32_IT_DSUB_X35RC] = {arch:FEATURE_I_DFP, morph:morphDSUB_X35RC},
    [PPC32_IT_DSUBRC_X35RC] = {arch:FEATURE_I_DFP, morph:morphDSUBRC_X35RC},
    [PPC32_IT_FCPSGN_X35RC] = {arch:FEATURE_I_FP, morph:morphFCPSGN_X35RC},
    [PPC32_IT_FCPSGNRC_X35RC] = {arch:FEATURE_I_FP, morph:morphFCPSGNRC_X35RC},

    //
    // Format X37 Insns
    //
    [PPC32_IT_DCTDP_X37] = {arch:FEATURE_I_DFP, morph:morphDCTDP_X37},
    [PPC32_IT_DCTDPRC_X37] = {arch:FEATURE_I_DFP, morph:morphDCTDPRC_X37},
    [PPC32_IT_DCTFIX_X37] = {arch:FEATURE_I_DFP, morph:morphDCTFIX_X37},
    [PPC32_IT_DCTFIXRC_X37] = {arch:FEATURE_I_DFP, morph:morphDCTFIXRC_X37},
    [PPC32_IT_DRSP_X37] = {arch:FEATURE_I_DFP, morph:morphDRSP_X37},
    [PPC32_IT_DRSPRC_X37] = {arch:FEATURE_I_DFP, morph:morphDRSPRC_X37},
    [PPC32_IT_DXEX_X37] = {arch:FEATURE_I_DFP, morph:morphDXEX_X37},
    [PPC32_IT_DXEXRC_X37] = {arch:FEATURE_I_DFP, morph:morphDXEXRC_X37},
    [PPC32_IT_FABS_X37] = {arch:FEATURE_I_FP, morph:morphFABS_X37},
    [PPC32_IT_FABSRC_X37] = {arch:FEATURE_I_FP, morph:morphFABSRC_X37},
    [PPC32_IT_FCFID_X37] = {arch:FEATURE_I_FP, morph:morphFCFID_X37},
    [PPC32_IT_FCFIDRC_X37] = {arch:FEATURE_I_FP, morph:morphFCFIDRC_X37},
    [PPC32_IT_FCTID_X37] = {arch:FEATURE_I_FP, morph:morphFCTID_X37},
    [PPC32_IT_FCTIDRC_X37] = {arch:FEATURE_I_FP, morph:morphFCTIDRC_X37},
    [PPC32_IT_FCTIDZ_X37] = {arch:FEATURE_I_FP, morph:morphFCTIDZ_X37},
    [PPC32_IT_FCTIDZRC_X37] = {arch:FEATURE_I_FP, morph:morphFCTIDZRC_X37},
    [PPC32_IT_FCTIW_X37] = {arch:FEATURE_I_FP, morph:morphFCTIW_X37},
    [PPC32_IT_FCTIWRC_X37] = {arch:FEATURE_I_FP, morph:morphFCTIWRC_X37},
    [PPC32_IT_FCTIWZ_X37] = {arch:FEATURE_I_FP, morph:morphFCTIWZ_X37},
    [PPC32_IT_FCTIWZRC_X37] = {arch:FEATURE_I_FP, morph:morphFCTIWZRC_X37},
    [PPC32_IT_FMR_X37] = {arch:FEATURE_I_FP, morph:morphFMR_X37},
    [PPC32_IT_FMRRC_X37] = {arch:FEATURE_I_FP, morph:morphFMRRC_X37},
    [PPC32_IT_FNABS_X37] = {arch:FEATURE_I_FP, morph:morphFNABS_X37},
    [PPC32_IT_FNABSRC_X37] = {arch:FEATURE_I_FP, morph:morphFNABSRC_X37},
    [PPC32_IT_FNEG_X37] = {arch:FEATURE_I_FP, morph:morphFNEG_X37},
    [PPC32_IT_FNEGRC_X37] = {arch:FEATURE_I_FP, morph:morphFNEGRC_X37},
    [PPC32_IT_FRIM_X37] = {arch:FEATURE_I_FP, morph:morphFRIM_X37},
    [PPC32_IT_FRIMRC_X37] = {arch:FEATURE_I_FP, morph:morphFRIMRC_X37},
    [PPC32_IT_FRIN_X37] = {arch:FEATURE_I_FP, morph:morphFRIN_X37},
    [PPC32_IT_FRINRC_X37] = {arch:FEATURE_I_FP, morph:morphFRINRC_X37},
    [PPC32_IT_FRIP_X37] = {arch:FEATURE_I_FP, morph:morphFRIP_X37},
    [PPC32_IT_FRIPRC_X37] = {arch:FEATURE_I_FP, morph:morphFRIPRC_X37},
    [PPC32_IT_FRIZ_X37] = {arch:FEATURE_I_FP, morph:morphFRIZ_X37},
    [PPC32_IT_FRIZRC_X37] = {arch:FEATURE_I_FP, morph:morphFRIZRC_X37},
    [PPC32_IT_FRSP_X37] = {arch:FEATURE_I_FP, morph:morphFRSP_X37},
    [PPC32_IT_FRSPRC_X37] = {arch:FEATURE_I_FP, morph:morphFRSPRC_X37},

    //
    // Format X38 Insns
    //
    [PPC32_IT_DCTFIXQ_X38] = {arch:FEATURE_I_DFP, morph:morphDCTFIXQ_X38},
    [PPC32_IT_DCTFIXQRC_X38] = {arch:FEATURE_I_DFP, morph:morphDCTFIXQRC_X38},
    [PPC32_IT_DXEX_X38] = {arch:FEATURE_I_DFP, morph:morphDXEX_X38},
    [PPC32_IT_DXEXRC_X38] = {arch:FEATURE_I_DFP, morph:morphDXEXRC_X38},

    //
    // Format X39 Insns
    //
    [PPC32_IT_MFFS_X39] = {arch:FEATURE_I_FP, morph:morphMFFS_X39},
    [PPC32_IT_MFFSRC_X39] = {arch:FEATURE_I_FP, morph:morphMFFSRC_X39},

    //
    // Format X4 Insns
    //
    [PPC32_IT_LSWI_X4] = {arch:FEATURE_I_MA, morph:morphLSWI_X4},

    //
    // Format X40 Insns
    //
    [PPC32_IT_DCFFIXQ_X40] = {arch:FEATURE_I_DFP, morph:morphDCFFIXQ_X40},
    [PPC32_IT_DCFFIXQRC_X40] = {arch:FEATURE_I_DFP, morph:morphDCFFIXQRC_X40},
    [PPC32_IT_DCTQPQ_X40] = {arch:FEATURE_I_DFP, morph:morphDCTQPQ_X40},
    [PPC32_IT_DCTQPQRC_X40] = {arch:FEATURE_I_DFP, morph:morphDCTQPQRC_X40},

    //
    // Format X41 Insns
    //
    [PPC32_IT_DRDPQ_X41] = {arch:FEATURE_I_DFP, morph:morphDRDPQ_X41},
    [PPC32_IT_DRDPQRC_X41] = {arch:FEATURE_I_DFP, morph:morphDRDPQRC_X41},

    //
    // Format X43 Insns
    //
    [PPC32_IT_DADDQ_X43] = {arch:FEATURE_I_DFP, morph:morphDADDQ_X43},
    [PPC32_IT_DADDQRC_X43] = {arch:FEATURE_I_DFP, morph:morphDADDQRC_X43},
    [PPC32_IT_DDIVQ_X43] = {arch:FEATURE_I_DFP, morph:morphDDIVQ_X43},
    [PPC32_IT_DDIVQRC_X43] = {arch:FEATURE_I_DFP, morph:morphDDIVQRC_X43},
    [PPC32_IT_DIEXQ_X43] = {arch:FEATURE_I_DFP, morph:morphDIEXQ_X43},
    [PPC32_IT_DIEXQRC_X43] = {arch:FEATURE_I_DFP, morph:morphDIEXQRC_X43},
    [PPC32_IT_DMULQ_X43] = {arch:FEATURE_I_DFP, morph:morphDMULQ_X43},
    [PPC32_IT_DMULQRC_X43] = {arch:FEATURE_I_DFP, morph:morphDMULQRC_X43},
    [PPC32_IT_DSUBQ_X43] = {arch:FEATURE_I_DFP, morph:morphDSUBQ_X43},
    [PPC32_IT_DSUBQRC_X43] = {arch:FEATURE_I_DFP, morph:morphDSUBQRC_X43},

    //
    // Format X45 Insns
    //
    [PPC32_IT_DCMPOQ_X45] = {arch:FEATURE_I_DFP, morph:morphDCMPOQ_X45},
    [PPC32_IT_DCMPUQ_X45] = {arch:FEATURE_I_DFP, morph:morphDCMPUQ_X45},
    [PPC32_IT_DTSTEXQ_X45] = {arch:FEATURE_I_DFP, morph:morphDTSTEXQ_X45},
    [PPC32_IT_DTSTSFQ_X45] = {arch:FEATURE_I_DFP, morph:morphDTSTSFQ_X45},

    //
    // Format X46_0 Insns
    //
    [PPC32_IT_DDEDPD_X46_0] = {arch:FEATURE_I_DFP, morph:morphDDEDPD_X46_0},
    [PPC32_IT_DDEDPDRC_X46_0] = {arch:FEATURE_I_DFP, morph:morphDDEDPDRC_X46_0},

    //
    // Format X46_1 Insns
    //
    [PPC32_IT_DENBCD_X46_1] = {arch:FEATURE_I_DFP, morph:morphDENBCD_X46_1},
    [PPC32_IT_DENBCDRC_X46_1] = {arch:FEATURE_I_DFP, morph:morphDENBCDRC_X46_1},

    //
    // Format X47_0 Insns
    //
    [PPC32_IT_DDEDPDQ_X47_0] = {arch:FEATURE_I_DFP, morph:morphDDEDPDQ_X47_0},
    [PPC32_IT_DDEDPDQRC_X47_0] = {arch:FEATURE_I_DFP, morph:morphDDEDPDQRC_X47_0},

    //
    // Format X47_1 Insns
    //
    [PPC32_IT_DENBCDQ_X47_1] = {arch:FEATURE_I_DFP, morph:morphDENBCDQ_X47_1},
    [PPC32_IT_DENBCDQRC_X47_1] = {arch:FEATURE_I_DFP, morph:morphDENBCDQRC_X47_1},

    //
    // Format X48 Insns
    //
    [PPC32_IT_STFDUX_X48] = {arch:FEATURE_I_FP, morph:morphSTFDUX_X48},
    [PPC32_IT_STFDX_X48] = {arch:FEATURE_I_FP, morph:morphSTFDX_X48},
    [PPC32_IT_STFIWX_X48] = {arch:FEATURE_I_FP, morph:morphSTFIWX_X48},
    [PPC32_IT_STFSUX_X48] = {arch:FEATURE_I_FP, morph:morphSTFSUX_X48},
    [PPC32_IT_STFSX_X48] = {arch:FEATURE_I_FP, morph:morphSTFSX_X48},

    //
    // Format X5 Insns
    //
    [PPC32_IT_MFSR_X5] = {arch:FEATURE_I_S, morph:morphMFSR_X5},

    //
    // Format X50 Insns
    //
    [PPC32_IT_MTFSSB0_X50] = {arch:FEATURE_I_FP, morph:morphMTFSSB0_X50},
    [PPC32_IT_MTFSSB0RC_X50] = {arch:FEATURE_I_FP, morph:morphMTFSSB0RC_X50},
    [PPC32_IT_MTFSSB1_X50] = {arch:FEATURE_I_FP, morph:morphMTFSSB1_X50},
    [PPC32_IT_MTFSSB1RC_X50] = {arch:FEATURE_I_FP, morph:morphMTFSSB1RC_X50},

    //
    // Format X51 Insns
    //
    [PPC32_IT_DCBA_X51] = {arch:FEATURE_I_E, morph:morphDCBA_X51},
    [PPC32_IT_DCBFEP_X51] = {arch:FEATURE_I_E_PD, morph:morphDCBFEP_X51},
    [PPC32_IT_DCBI_X51] = {arch:FEATURE_I_E, morph:morphDCBI_X51},
    [PPC32_IT_DCBST_X51] = {arch:FEATURE_I_B, morph:morphDCBST_X51},
    [PPC32_IT_DCBSTEP_X51] = {arch:FEATURE_I_E_PD, morph:morphDCBSTEP_X51},
    [PPC32_IT_DCBZ_X51] = {arch:FEATURE_I_B, morph:morphDCBZ_X51},
    [PPC32_IT_DCBZEP_X51] = {arch:FEATURE_I_E_PD, morph:morphDCBZEP_X51},
    [PPC32_IT_ICBI_X51] = {arch:FEATURE_I_B, morph:morphICBI_X51},
    [PPC32_IT_ICBIEP_X51] = {arch:FEATURE_I_E_PD, morph:morphICBIEP_X51},
    [PPC32_IT_ICREAD_X51] = {arch:FEATURE_I_E, morph:morphICREAD_X51},
    [PPC32_IT_TLBIVAX_X51] = {arch:FEATURE_I_E, morph:morphTLBIVAX_X51},
    [PPC32_IT_TLBSX_X51] = {arch:FEATURE_I_E, morph:morphTLBSX_X51},

    //
    // Format X52 Insns
    //
    [PPC32_IT_MSGCLR_X52] = {arch:FEATURE_I_E_PC, morph:morphMSGCLR_X52},
    [PPC32_IT_MSGSND_X52] = {arch:FEATURE_I_E_PC, morph:morphMSGSND_X52},
    [PPC32_IT_SLBIE_X52] = {arch:FEATURE_I_S, morph:morphSLBIE_X52},

    //
    // Format X53_0 Insns
    //
    [PPC32_IT_EIEIO_X53_0] = {arch:FEATURE_I_S, morph:morphEIEIO_X53_0},

    //
    // Format X53_1 Insns
    //
    [PPC32_IT_TLBIA_X53_1] = {arch:FEATURE_I_S, morph:morphTLBIA_X53_1},
    [PPC32_IT_TLBRE_X53_1] = {arch:FEATURE_I_E, morph:morphTLBRE_X53_1},
    [PPC32_IT_TLBSYNC_X53_1] = {arch:FEATURE_I_B, morph:morphTLBSYNC_X53_1},
    [PPC32_IT_TLBWE_X53_1] = {arch:FEATURE_I_E, morph:morphTLBWE_X53_1},
    [PPC32_IT_WAIT_X53_1] = {arch:FEATURE_I_WT, morph:morphWAIT_X53_1},

    //
    // Format X54 Insns
    //
    [PPC32_IT_WRTEEI_X54] = {arch:FEATURE_I_E, morph:morphWRTEEI_X54},

    //
    // Format X55_0 Insns
    //
    [PPC32_IT_SLBIA_0_X55_0] = {arch:FEATURE_I_S, morph:morphSLBIA_0_X55_0},

    //
    // Format X55_1 Insns
    //
    [PPC32_IT_SLBIA_1_X55_1] = {arch:FEATURE_I_S, morph:morphSLBIA_1_X55_1},

    //
    // Format X58 Insns
    //
    [PPC32_IT_LVEBX_X58] = {arch:FEATURE_I_V, morph:morphLVEBX_X58},
    [PPC32_IT_LVEHX_X58] = {arch:FEATURE_I_V, morph:morphLVEHX_X58},
    [PPC32_IT_LVEWX_X58] = {arch:FEATURE_I_V, morph:morphLVEWX_X58},
    [PPC32_IT_LVSL_X58] = {arch:FEATURE_I_V, morph:morphLVSL_X58},
    [PPC32_IT_LVSR_X58] = {arch:FEATURE_I_V, morph:morphLVSR_X58},
    [PPC32_IT_LVX_X58] = {arch:FEATURE_I_V, morph:morphLVX_X58},
    [PPC32_IT_LVXL_X58] = {arch:FEATURE_I_V, morph:morphLVXL_X58},

    //
    // Format X59 Insns
    //
    [PPC32_IT_STVEBX_X59] = {arch:FEATURE_I_V, morph:morphSTVEBX_X59},
    [PPC32_IT_STVEHX_X59] = {arch:FEATURE_I_V, morph:morphSTVEHX_X59},
    [PPC32_IT_STVEWX_X59] = {arch:FEATURE_I_V, morph:morphSTVEWX_X59},
    [PPC32_IT_STVX_X59] = {arch:FEATURE_I_V, morph:morphSTVX_X59},
    [PPC32_IT_STVXL_X59] = {arch:FEATURE_I_V, morph:morphSTVXL_X59},

    //
    // Format X6 Insns
    //
    [PPC32_IT_MFSRIN_X6] = {arch:FEATURE_I_S, morph:morphMFSRIN_X6},
    [PPC32_IT_SLBMFEE_X6] = {arch:FEATURE_I_S, morph:morphSLBMFEE_X6},
    [PPC32_IT_SLBMFEV_X6] = {arch:FEATURE_I_S, morph:morphSLBMFEV_X6},

    //
    // Format X60 Insns
    //
    [PPC32_IT_MBAR_X60] = {arch:FEATURE_I_E, morph:morphMBAR_X60},

    //
    // Format X8 Insns
    //
    [PPC32_IT_MFMSR_X8] = {arch:FEATURE_I_B, morph:morphMFMSR_X8},

    //
    // Format X9 Insns
    //
    [PPC32_IT_AND_X9] = {arch:FEATURE_I_B, morph:morphAND_X9},
    [PPC32_IT_ANDC_X9] = {arch:FEATURE_I_B, morph:morphANDC_X9},
    [PPC32_IT_ANDCRC_X9] = {arch:FEATURE_I_B, morph:morphANDCRC_X9},
    [PPC32_IT_ANDRC_X9] = {arch:FEATURE_I_B, morph:morphANDRC_X9},
    [PPC32_IT_DLMZB_X9] = {arch:FEATURE_I_LMA, morph:morphDLMZB_X9},
    [PPC32_IT_DLMZBRC_X9] = {arch:FEATURE_I_LMA, morph:morphDLMZBRC_X9},
    [PPC32_IT_EQV_X9] = {arch:FEATURE_I_B, morph:morphEQV_X9},
    [PPC32_IT_EQVRC_X9] = {arch:FEATURE_I_B, morph:morphEQVRC_X9},
    [PPC32_IT_E_RLW_X9] = {arch:FEATURE_I_VLE, morph:morphE_RLW_X9},
    [PPC32_IT_E_RLWRC_X9] = {arch:FEATURE_I_VLE, morph:morphE_RLWRC_X9},
    [PPC32_IT_NAND_X9] = {arch:FEATURE_I_B, morph:morphNAND_X9},
    [PPC32_IT_NANDRC_X9] = {arch:FEATURE_I_B, morph:morphNANDRC_X9},
    [PPC32_IT_NOR_X9] = {arch:FEATURE_I_B, morph:morphNOR_X9},
    [PPC32_IT_NORRC_X9] = {arch:FEATURE_I_B, morph:morphNORRC_X9},
    [PPC32_IT_OR_X9] = {arch:FEATURE_I_B, morph:morphOR_X9},
    [PPC32_IT_ORC_X9] = {arch:FEATURE_I_B, morph:morphORC_X9},
    [PPC32_IT_ORCRC_X9] = {arch:FEATURE_I_B, morph:morphORCRC_X9},
    [PPC32_IT_ORRC_X9] = {arch:FEATURE_I_B, morph:morphORRC_X9},
    [PPC32_IT_SLW_X9] = {arch:FEATURE_I_B, morph:morphSLW_X9},
    [PPC32_IT_SLWRC_X9] = {arch:FEATURE_I_B, morph:morphSLWRC_X9},
    [PPC32_IT_SRAW_X9] = {arch:FEATURE_I_B, morph:morphSRAW_X9},
    [PPC32_IT_SRAWRC_X9] = {arch:FEATURE_I_B, morph:morphSRAWRC_X9},
    [PPC32_IT_SRW_X9] = {arch:FEATURE_I_B, morph:morphSRW_X9},
    [PPC32_IT_SRWRC_X9] = {arch:FEATURE_I_B, morph:morphSRWRC_X9},
    [PPC32_IT_XOR_X9] = {arch:FEATURE_I_B, morph:morphXOR_X9},
    [PPC32_IT_XORRC_X9] = {arch:FEATURE_I_B, morph:morphXORRC_X9},

    //
    // Format XFL Insns
    //
    [PPC32_IT_MTFSF_XFL] = {arch:FEATURE_I_FP, morph:morphMTFSF_XFL},
    [PPC32_IT_MTFSFRC_XFL] = {arch:FEATURE_I_FP, morph:morphMTFSFRC_XFL},

    //
    // Format XFLZ Insns
    //
    [PPC32_IT_MTFSFZ_XFLZ] = {arch:FEATURE_I_FP, morph:morphMTFSFZ_XFLZ},
    [PPC32_IT_MTFSFZRC_XFLZ] = {arch:FEATURE_I_FP, morph:morphMTFSFZRC_XFLZ},

    //
    // Format XFX1 Insns
    //
    [PPC32_IT_MFSPR_XFX1] = {arch:FEATURE_I_B, morph:morphMFSPR_XFX1},
    [PPC32_IT_MFTB_XFX1] = {arch:FEATURE_I_S, morph:morphMFTB_XFX1},

    //
    // Format XFX10 Insns
    //
    [PPC32_IT_MTSPR_XFX10] = {arch:FEATURE_I_B, morph:morphMTSPR_XFX10},

    //
    // Format XFX10D Insns
    //
    [PPC32_IT_MTCTR_XFX10D] = {arch:FEATURE_I_B, morph:morphMTCTR_XFX10D},
    [PPC32_IT_MTLR_XFX10D] = {arch:FEATURE_I_B, morph:morphMTLR_XFX10D},
    [PPC32_IT_MTXER_XFX10D] = {arch:FEATURE_I_B, morph:morphMTXER_XFX10D},

    //
    // Format XFX11 Insns
    //
    [PPC32_IT_MTDCR_XFX11] = {arch:FEATURE_I_E, morph:morphMTDCR_XFX11},

    //
    // Format XFX12 Insns
    //
    [PPC32_IT_MTPMR_XFX12] = {arch:FEATURE_I_E_PD, morph:morphMTPMR_XFX12},

    //
    // Format XFX1D Insns
    //
    [PPC32_IT_MFCTR_XFX1D] = {arch:FEATURE_I_B, morph:morphMFCTR_XFX1D},
    [PPC32_IT_MFLR_XFX1D] = {arch:FEATURE_I_B, morph:morphMFLR_XFX1D},
    [PPC32_IT_MFXER_XFX1D] = {arch:FEATURE_I_B, morph:morphMFXER_XFX1D},

    //
    // Format XFX3 Insns
    //
    [PPC32_IT_MFCR_XFX3] = {arch:FEATURE_I_B, morph:morphMFCR_XFX3},

    //
    // Format XFX4 Insns
    //
    [PPC32_IT_MFOCRF_XFX4] = {arch:FEATURE_I_B, morph:morphMFOCRF_XFX4},

    //
    // Format XFX5 Insns
    //
    [PPC32_IT_MFDCR_XFX5] = {arch:FEATURE_I_E, morph:morphMFDCR_XFX5},

    //
    // Format XFX6 Insns
    //
    [PPC32_IT_MFPMR_XFX6] = {arch:FEATURE_I_E_PD, morph:morphMFPMR_XFX6},

    //
    // Format XFX7 Insns
    //

    //
    // Format XFX8 Insns
    //
    [PPC32_IT_MTCRF_XFX8] = {arch:FEATURE_I_B, morph:morphMTCRF_XFX8},

    //
    // Format XFX8D Insns
    //
    [PPC32_IT_MTCR_XFX8D] = {arch:FEATURE_I_B, morph:morphMTCR_XFX8D},

    //
    // Format XFX9 Insns
    //
    [PPC32_IT_MTOCRF_XFX9] = {arch:FEATURE_I_B, morph:morphMTOCRF_XFX9},

    //
    // Format XL1 Insns
    //
    [PPC32_IT_CRAND_XL1] = {arch:FEATURE_I_B, morph:morphCRAND_XL1},
    [PPC32_IT_CRANDC_XL1] = {arch:FEATURE_I_B, morph:morphCRANDC_XL1},
    [PPC32_IT_CREQV_XL1] = {arch:FEATURE_I_B, morph:morphCREQV_XL1},
    [PPC32_IT_CRNAND_XL1] = {arch:FEATURE_I_B, morph:morphCRNAND_XL1},
    [PPC32_IT_CRNOR_XL1] = {arch:FEATURE_I_B, morph:morphCRNOR_XL1},
    [PPC32_IT_CROR_XL1] = {arch:FEATURE_I_B, morph:morphCROR_XL1},
    [PPC32_IT_CRORC_XL1] = {arch:FEATURE_I_B, morph:morphCRORC_XL1},
    [PPC32_IT_CRXOR_XL1] = {arch:FEATURE_I_B, morph:morphCRXOR_XL1},
    [PPC32_IT_E_CRAND_XL1] = {arch:FEATURE_I_VLE, morph:morphE_CRAND_XL1},
    [PPC32_IT_E_CRANDC_XL1] = {arch:FEATURE_I_VLE, morph:morphE_CRANDC_XL1},
    [PPC32_IT_E_CREQV_XL1] = {arch:FEATURE_I_VLE, morph:morphE_CREQV_XL1},
    [PPC32_IT_E_CRNAND_XL1] = {arch:FEATURE_I_VLE, morph:morphE_CRNAND_XL1},
    [PPC32_IT_E_CRNOR_XL1] = {arch:FEATURE_I_VLE, morph:morphE_CRNOR_XL1},
    [PPC32_IT_E_CROR_XL1] = {arch:FEATURE_I_VLE, morph:morphE_CROR_XL1},
    [PPC32_IT_E_CRORC_XL1] = {arch:FEATURE_I_VLE, morph:morphE_CRORC_XL1},
    [PPC32_IT_E_CRXOR_XL1] = {arch:FEATURE_I_VLE, morph:morphE_CRXOR_XL1},

    //
    // Format XL2 Insns
    //
    [PPC32_IT_BCCTR_XL2] = {arch:FEATURE_I_B, morph:morphBCCTR_XL2},
    [PPC32_IT_BCLR_XL2] = {arch:FEATURE_I_B, morph:morphBCLR_XL2},

    //
    // Format XL3 Insns
    //
    [PPC32_IT_E_MCRF_XL3] = {arch:FEATURE_I_VLE, morph:morphE_MCRF_XL3},
    [PPC32_IT_MCRF_XL3] = {arch:FEATURE_I_B, morph:morphMCRF_XL3},

    //
    // Format XL4 Insns
    //
    [PPC32_IT_DOZE_XL4] = {arch:FEATURE_I_S, morph:morphDOZE_XL4},
    [PPC32_IT_HRFID_XL4] = {arch:FEATURE_I_S, morph:morphHRFID_XL4},
    [PPC32_IT_ISYNC_XL4] = {arch:FEATURE_I_B, morph:morphISYNC_XL4},
    [PPC32_IT_NAP_XL4] = {arch:FEATURE_I_S, morph:morphNAP_XL4},
    [PPC32_IT_RFCI_XL4] = {arch:FEATURE_I_E, morph:morphRFCI_XL4},
    [PPC32_IT_RFI_XL4] = {arch:FEATURE_I_E, morph:morphRFI_XL4},
    [PPC32_IT_RFID_XL4] = {arch:FEATURE_I_S, morph:morphRFID_XL4},
    [PPC32_IT_RFMCI_XL4] = {arch:FEATURE_I_E, morph:morphRFMCI_XL4},
    [PPC32_IT_RVWINKLE_XL4] = {arch:FEATURE_I_S, morph:morphRVWINKLE_XL4},
    [PPC32_IT_SLEEP_XL4] = {arch:FEATURE_I_S, morph:morphSLEEP_XL4},

    //
    // Format XO1 Insns
    //
    [PPC32_IT_ADD_XO1] = {arch:FEATURE_I_B, morph:morphADD_XO1},
    [PPC32_IT_ADDC_XO1] = {arch:FEATURE_I_B, morph:morphADDC_XO1},
    [PPC32_IT_ADDCOE_XO1] = {arch:FEATURE_I_B, morph:morphADDCOE_XO1},
    [PPC32_IT_ADDCOERC_XO1] = {arch:FEATURE_I_B, morph:morphADDCOERC_XO1},
    [PPC32_IT_ADDCRC_XO1] = {arch:FEATURE_I_B, morph:morphADDCRC_XO1},
    [PPC32_IT_ADDE_XO1] = {arch:FEATURE_I_B, morph:morphADDE_XO1},
    [PPC32_IT_ADDEOE_XO1] = {arch:FEATURE_I_B, morph:morphADDEOE_XO1},
    [PPC32_IT_ADDEOERC_XO1] = {arch:FEATURE_I_B, morph:morphADDEOERC_XO1},
    [PPC32_IT_ADDERC_XO1] = {arch:FEATURE_I_B, morph:morphADDERC_XO1},
    [PPC32_IT_ADDOE_XO1] = {arch:FEATURE_I_B, morph:morphADDOE_XO1},
    [PPC32_IT_ADDOERC_XO1] = {arch:FEATURE_I_B, morph:morphADDOERC_XO1},
    [PPC32_IT_ADDRC_XO1] = {arch:FEATURE_I_B, morph:morphADDRC_XO1},
    [PPC32_IT_DIVW_XO1] = {arch:FEATURE_I_B, morph:morphDIVW_XO1},
    [PPC32_IT_DIVWOE_XO1] = {arch:FEATURE_I_B, morph:morphDIVWOE_XO1},
    [PPC32_IT_DIVWOERC_XO1] = {arch:FEATURE_I_B, morph:morphDIVWOERC_XO1},
    [PPC32_IT_DIVWRC_XO1] = {arch:FEATURE_I_B, morph:morphDIVWRC_XO1},
    [PPC32_IT_DIVWU_XO1] = {arch:FEATURE_I_B, morph:morphDIVWU_XO1},
    [PPC32_IT_DIVWUOE_XO1] = {arch:FEATURE_I_B, morph:morphDIVWUOE_XO1},
    [PPC32_IT_DIVWUOERC_XO1] = {arch:FEATURE_I_B, morph:morphDIVWUOERC_XO1},
    [PPC32_IT_DIVWURC_XO1] = {arch:FEATURE_I_B, morph:morphDIVWURC_XO1},
    [PPC32_IT_MACCHW_XO1] = {arch:FEATURE_I_LMA, morph:morphMACCHW_XO1},
    [PPC32_IT_MACCHWOE_XO1] = {arch:FEATURE_I_LMA, morph:morphMACCHWOE_XO1},
    [PPC32_IT_MACCHWOERC_XO1] = {arch:FEATURE_I_LMA, morph:morphMACCHWOERC_XO1},
    [PPC32_IT_MACCHWRC_XO1] = {arch:FEATURE_I_LMA, morph:morphMACCHWRC_XO1},
    [PPC32_IT_MACCHWS_XO1] = {arch:FEATURE_I_LMA, morph:morphMACCHWS_XO1},
    [PPC32_IT_MACCHWSOE_XO1] = {arch:FEATURE_I_LMA, morph:morphMACCHWSOE_XO1},
    [PPC32_IT_MACCHWSOERC_XO1] = {arch:FEATURE_I_LMA, morph:morphMACCHWSOERC_XO1},
    [PPC32_IT_MACCHWSRC_XO1] = {arch:FEATURE_I_LMA, morph:morphMACCHWSRC_XO1},
    [PPC32_IT_MACCHWSU_XO1] = {arch:FEATURE_I_LMA, morph:morphMACCHWSU_XO1},
    [PPC32_IT_MACCHWSUOE_XO1] = {arch:FEATURE_I_LMA, morph:morphMACCHWSUOE_XO1},
    [PPC32_IT_MACCHWSUOERC_XO1] = {arch:FEATURE_I_LMA, morph:morphMACCHWSUOERC_XO1},
    [PPC32_IT_MACCHWSURC_XO1] = {arch:FEATURE_I_LMA, morph:morphMACCHWSURC_XO1},
    [PPC32_IT_MACCHWU_XO1] = {arch:FEATURE_I_LMA, morph:morphMACCHWU_XO1},
    [PPC32_IT_MACCHWUOE_XO1] = {arch:FEATURE_I_LMA, morph:morphMACCHWUOE_XO1},
    [PPC32_IT_MACCHWUOERC_XO1] = {arch:FEATURE_I_LMA, morph:morphMACCHWUOERC_XO1},
    [PPC32_IT_MACCHWURC_XO1] = {arch:FEATURE_I_LMA, morph:morphMACCHWURC_XO1},
    [PPC32_IT_MACHHW_XO1] = {arch:FEATURE_I_LMA, morph:morphMACHHW_XO1},
    [PPC32_IT_MACHHWOE_XO1] = {arch:FEATURE_I_LMA, morph:morphMACHHWOE_XO1},
    [PPC32_IT_MACHHWOERC_XO1] = {arch:FEATURE_I_LMA, morph:morphMACHHWOERC_XO1},
    [PPC32_IT_MACHHWRC_XO1] = {arch:FEATURE_I_LMA, morph:morphMACHHWRC_XO1},
    [PPC32_IT_MACHHWS_XO1] = {arch:FEATURE_I_LMA, morph:morphMACHHWS_XO1},
    [PPC32_IT_MACHHWSOE_XO1] = {arch:FEATURE_I_LMA, morph:morphMACHHWSOE_XO1},
    [PPC32_IT_MACHHWSOERC_XO1] = {arch:FEATURE_I_LMA, morph:morphMACHHWSOERC_XO1},
    [PPC32_IT_MACHHWSRC_XO1] = {arch:FEATURE_I_LMA, morph:morphMACHHWSRC_XO1},
    [PPC32_IT_MACHHWSU_XO1] = {arch:FEATURE_I_LMA, morph:morphMACHHWSU_XO1},
    [PPC32_IT_MACHHWSUOE_XO1] = {arch:FEATURE_I_LMA, morph:morphMACHHWSUOE_XO1},
    [PPC32_IT_MACHHWSUOERC_XO1] = {arch:FEATURE_I_LMA, morph:morphMACHHWSUOERC_XO1},
    [PPC32_IT_MACHHWSURC_XO1] = {arch:FEATURE_I_LMA, morph:morphMACHHWSURC_XO1},
    [PPC32_IT_MACHHWU_XO1] = {arch:FEATURE_I_LMA, morph:morphMACHHWU_XO1},
    [PPC32_IT_MACHHWUOE_XO1] = {arch:FEATURE_I_LMA, morph:morphMACHHWUOE_XO1},
    [PPC32_IT_MACHHWUOERC_XO1] = {arch:FEATURE_I_LMA, morph:morphMACHHWUOERC_XO1},
    [PPC32_IT_MACHHWURC_XO1] = {arch:FEATURE_I_LMA, morph:morphMACHHWURC_XO1},
    [PPC32_IT_MACLHW_XO1] = {arch:FEATURE_I_LMA, morph:morphMACLHW_XO1},
    [PPC32_IT_MACLHWOE_XO1] = {arch:FEATURE_I_LMA, morph:morphMACLHWOE_XO1},
    [PPC32_IT_MACLHWOERC_XO1] = {arch:FEATURE_I_LMA, morph:morphMACLHWOERC_XO1},
    [PPC32_IT_MACLHWRC_XO1] = {arch:FEATURE_I_LMA, morph:morphMACLHWRC_XO1},
    [PPC32_IT_MACLHWS_XO1] = {arch:FEATURE_I_LMA, morph:morphMACLHWS_XO1},
    [PPC32_IT_MACLHWSOE_XO1] = {arch:FEATURE_I_LMA, morph:morphMACLHWSOE_XO1},
    [PPC32_IT_MACLHWSOERC_XO1] = {arch:FEATURE_I_LMA, morph:morphMACLHWSOERC_XO1},
    [PPC32_IT_MACLHWSRC_XO1] = {arch:FEATURE_I_LMA, morph:morphMACLHWSRC_XO1},
    [PPC32_IT_MACLHWSU_XO1] = {arch:FEATURE_I_LMA, morph:morphMACLHWSU_XO1},
    [PPC32_IT_MACLHWSUOE_XO1] = {arch:FEATURE_I_LMA, morph:morphMACLHWSUOE_XO1},
    [PPC32_IT_MACLHWSUOERC_XO1] = {arch:FEATURE_I_LMA, morph:morphMACLHWSUOERC_XO1},
    [PPC32_IT_MACLHWSURC_XO1] = {arch:FEATURE_I_LMA, morph:morphMACLHWSURC_XO1},
    [PPC32_IT_MACLHWU_XO1] = {arch:FEATURE_I_LMA, morph:morphMACLHWU_XO1},
    [PPC32_IT_MACLHWUOE_XO1] = {arch:FEATURE_I_LMA, morph:morphMACLHWUOE_XO1},
    [PPC32_IT_MACLHWUOERC_XO1] = {arch:FEATURE_I_LMA, morph:morphMACLHWUOERC_XO1},
    [PPC32_IT_MACLHWURC_XO1] = {arch:FEATURE_I_LMA, morph:morphMACLHWURC_XO1},
    [PPC32_IT_MULLW_XO1] = {arch:FEATURE_I_B, morph:morphMULLW_XO1},
    [PPC32_IT_MULLWOE_XO1] = {arch:FEATURE_I_B, morph:morphMULLWOE_XO1},
    [PPC32_IT_MULLWOERC_XO1] = {arch:FEATURE_I_B, morph:morphMULLWOERC_XO1},
    [PPC32_IT_MULLWRC_XO1] = {arch:FEATURE_I_B, morph:morphMULLWRC_XO1},
    [PPC32_IT_NMACCHW_XO1] = {arch:FEATURE_I_LMA, morph:morphNMACCHW_XO1},
    [PPC32_IT_NMACCHWOE_XO1] = {arch:FEATURE_I_LMA, morph:morphNMACCHWOE_XO1},
    [PPC32_IT_NMACCHWOERC_XO1] = {arch:FEATURE_I_LMA, morph:morphNMACCHWOERC_XO1},
    [PPC32_IT_NMACCHWRC_XO1] = {arch:FEATURE_I_LMA, morph:morphNMACCHWRC_XO1},
    [PPC32_IT_NMACCHWS_XO1] = {arch:FEATURE_I_LMA, morph:morphNMACCHWS_XO1},
    [PPC32_IT_NMACCHWSOE_XO1] = {arch:FEATURE_I_LMA, morph:morphNMACCHWSOE_XO1},
    [PPC32_IT_NMACCHWSOERC_XO1] = {arch:FEATURE_I_LMA, morph:morphNMACCHWSOERC_XO1},
    [PPC32_IT_NMACCHWSRC_XO1] = {arch:FEATURE_I_LMA, morph:morphNMACCHWSRC_XO1},
    [PPC32_IT_NMACHHW_XO1] = {arch:FEATURE_I_LMA, morph:morphNMACHHW_XO1},
    [PPC32_IT_NMACHHWOE_XO1] = {arch:FEATURE_I_LMA, morph:morphNMACHHWOE_XO1},
    [PPC32_IT_NMACHHWOERC_XO1] = {arch:FEATURE_I_LMA, morph:morphNMACHHWOERC_XO1},
    [PPC32_IT_NMACHHWRC_XO1] = {arch:FEATURE_I_LMA, morph:morphNMACHHWRC_XO1},
    [PPC32_IT_NMACHHWS_XO1] = {arch:FEATURE_I_LMA, morph:morphNMACHHWS_XO1},
    [PPC32_IT_NMACHHWSOE_XO1] = {arch:FEATURE_I_LMA, morph:morphNMACHHWSOE_XO1},
    [PPC32_IT_NMACHHWSOERC_XO1] = {arch:FEATURE_I_LMA, morph:morphNMACHHWSOERC_XO1},
    [PPC32_IT_NMACHHWSRC_XO1] = {arch:FEATURE_I_LMA, morph:morphNMACHHWSRC_XO1},
    [PPC32_IT_NMACLHW_XO1] = {arch:FEATURE_I_LMA, morph:morphNMACLHW_XO1},
    [PPC32_IT_NMACLHWOE_XO1] = {arch:FEATURE_I_LMA, morph:morphNMACLHWOE_XO1},
    [PPC32_IT_NMACLHWOERC_XO1] = {arch:FEATURE_I_LMA, morph:morphNMACLHWOERC_XO1},
    [PPC32_IT_NMACLHWRC_XO1] = {arch:FEATURE_I_LMA, morph:morphNMACLHWRC_XO1},
    [PPC32_IT_NMACLHWS_XO1] = {arch:FEATURE_I_LMA, morph:morphNMACLHWS_XO1},
    [PPC32_IT_NMACLHWSOE_XO1] = {arch:FEATURE_I_LMA, morph:morphNMACLHWSOE_XO1},
    [PPC32_IT_NMACLHWSOERC_XO1] = {arch:FEATURE_I_LMA, morph:morphNMACLHWSOERC_XO1},
    [PPC32_IT_NMACLHWSRC_XO1] = {arch:FEATURE_I_LMA, morph:morphNMACLHWSRC_XO1},
    [PPC32_IT_SUBF_XO1] = {arch:FEATURE_I_B, morph:morphSUBF_XO1},
    [PPC32_IT_SUBFC_XO1] = {arch:FEATURE_I_B, morph:morphSUBFC_XO1},
    [PPC32_IT_SUBFCOE_XO1] = {arch:FEATURE_I_B, morph:morphSUBFCOE_XO1},
    [PPC32_IT_SUBFCOERC_XO1] = {arch:FEATURE_I_B, morph:morphSUBFCOERC_XO1},
    [PPC32_IT_SUBFCRC_XO1] = {arch:FEATURE_I_B, morph:morphSUBFCRC_XO1},
    [PPC32_IT_SUBFE_XO1] = {arch:FEATURE_I_B, morph:morphSUBFE_XO1},
    [PPC32_IT_SUBFEOE_XO1] = {arch:FEATURE_I_B, morph:morphSUBFEOE_XO1},
    [PPC32_IT_SUBFEOERC_XO1] = {arch:FEATURE_I_B, morph:morphSUBFEOERC_XO1},
    [PPC32_IT_SUBFERC_XO1] = {arch:FEATURE_I_B, morph:morphSUBFERC_XO1},
    [PPC32_IT_SUBFOE_XO1] = {arch:FEATURE_I_B, morph:morphSUBFOE_XO1},
    [PPC32_IT_SUBFOERC_XO1] = {arch:FEATURE_I_B, morph:morphSUBFOERC_XO1},
    [PPC32_IT_SUBFRC_XO1] = {arch:FEATURE_I_B, morph:morphSUBFRC_XO1},

    //
    // Format XO2 Insns
    //
    [PPC32_IT_MULHW_XO2] = {arch:FEATURE_I_B, morph:morphMULHW_XO2},
    [PPC32_IT_MULHWRC_XO2] = {arch:FEATURE_I_B, morph:morphMULHWRC_XO2},
    [PPC32_IT_MULHWU_XO2] = {arch:FEATURE_I_B, morph:morphMULHWU_XO2},
    [PPC32_IT_MULHWURC_XO2] = {arch:FEATURE_I_B, morph:morphMULHWURC_XO2},

    //
    // Format XO3 Insns
    //
    [PPC32_IT_ADDG6S_XO3] = {arch:FEATURE_I_BCDA, morph:morphADDG6S_XO3},

    //
    // Format XO4 Insns
    //
    [PPC32_IT_ADDME_XO4] = {arch:FEATURE_I_B, morph:morphADDME_XO4},
    [PPC32_IT_ADDMEOE_XO4] = {arch:FEATURE_I_B, morph:morphADDMEOE_XO4},
    [PPC32_IT_ADDMEOERC_XO4] = {arch:FEATURE_I_B, morph:morphADDMEOERC_XO4},
    [PPC32_IT_ADDMERC_XO4] = {arch:FEATURE_I_B, morph:morphADDMERC_XO4},
    [PPC32_IT_ADDZE_XO4] = {arch:FEATURE_I_B, morph:morphADDZE_XO4},
    [PPC32_IT_ADDZEOE_XO4] = {arch:FEATURE_I_B, morph:morphADDZEOE_XO4},
    [PPC32_IT_ADDZEOERC_XO4] = {arch:FEATURE_I_B, morph:morphADDZEOERC_XO4},
    [PPC32_IT_ADDZERC_XO4] = {arch:FEATURE_I_B, morph:morphADDZERC_XO4},
    [PPC32_IT_NEG_XO4] = {arch:FEATURE_I_B, morph:morphNEG_XO4},
    [PPC32_IT_NEGOE_XO4] = {arch:FEATURE_I_B, morph:morphNEGOE_XO4},
    [PPC32_IT_NEGOERC_XO4] = {arch:FEATURE_I_B, morph:morphNEGOERC_XO4},
    [PPC32_IT_NEGRC_XO4] = {arch:FEATURE_I_B, morph:morphNEGRC_XO4},
    [PPC32_IT_SUBFME_XO4] = {arch:FEATURE_I_B, morph:morphSUBFME_XO4},
    [PPC32_IT_SUBFMEOE_XO4] = {arch:FEATURE_I_B, morph:morphSUBFMEOE_XO4},
    [PPC32_IT_SUBFMEOERC_XO4] = {arch:FEATURE_I_B, morph:morphSUBFMEOERC_XO4},
    [PPC32_IT_SUBFMERC_XO4] = {arch:FEATURE_I_B, morph:morphSUBFMERC_XO4},
    [PPC32_IT_SUBFZE_XO4] = {arch:FEATURE_I_B, morph:morphSUBFZE_XO4},
    [PPC32_IT_SUBFZEOE_XO4] = {arch:FEATURE_I_B, morph:morphSUBFZEOE_XO4},
    [PPC32_IT_SUBFZEOERC_XO4] = {arch:FEATURE_I_B, morph:morphSUBFZEOERC_XO4},
    [PPC32_IT_SUBFZERC_XO4] = {arch:FEATURE_I_B, morph:morphSUBFZERC_XO4},

    //
    // Format Z22_1 Insns
    //
    [PPC32_IT_DTSTDC_Z22_1] = {arch:FEATURE_I_DFP, morph:morphDTSTDC_Z22_1},
    [PPC32_IT_DTSTDG_Z22_1] = {arch:FEATURE_I_DFP, morph:morphDTSTDG_Z22_1},

    //
    // Format Z22_2 Insns
    //
    [PPC32_IT_DTSTDCQ_Z22_2] = {arch:FEATURE_I_DFP, morph:morphDTSTDCQ_Z22_2},
    [PPC32_IT_DTSTDGQ_Z22_2] = {arch:FEATURE_I_DFP, morph:morphDTSTDGQ_Z22_2},

    //
    // Format Z22_3 Insns
    //

    //
    // Format Z22_4 Insns
    //

    //
    // Format Z22_5 Insns
    //
    [PPC32_IT_DSCLI_Z22_5] = {arch:FEATURE_I_DFP, morph:morphDSCLI_Z22_5},
    [PPC32_IT_DSCLIRC_Z22_5] = {arch:FEATURE_I_DFP, morph:morphDSCLIRC_Z22_5},
    [PPC32_IT_DSCRI_Z22_5] = {arch:FEATURE_I_DFP, morph:morphDSCRI_Z22_5},
    [PPC32_IT_DSCRIRC_Z22_5] = {arch:FEATURE_I_DFP, morph:morphDSCRIRC_Z22_5},

    //
    // Format Z22_6 Insns
    //
    [PPC32_IT_DSCLIQ_Z22_6] = {arch:FEATURE_I_DFP, morph:morphDSCLIQ_Z22_6},
    [PPC32_IT_DSCLIQRC_Z22_6] = {arch:FEATURE_I_DFP, morph:morphDSCLIQRC_Z22_6},
    [PPC32_IT_DSCRIQ_Z22_6] = {arch:FEATURE_I_DFP, morph:morphDSCRIQ_Z22_6},
    [PPC32_IT_DSCRIQRC_Z22_6] = {arch:FEATURE_I_DFP, morph:morphDSCRIQRC_Z22_6},

    //
    // Format Z23_1 Insns
    //
    [PPC32_IT_DQUAI_Z23_1] = {arch:FEATURE_I_DFP, morph:morphDQUAI_Z23_1},
    [PPC32_IT_DQUAIRC_Z23_1] = {arch:FEATURE_I_DFP, morph:morphDQUAIRC_Z23_1},

    //
    // Format Z23_2 Insns
    //
    [PPC32_IT_DQUAIQ_Z23_2] = {arch:FEATURE_I_DFP, morph:morphDQUAIQ_Z23_2},
    [PPC32_IT_DQUAIQRC_Z23_2] = {arch:FEATURE_I_DFP, morph:morphDQUAIQRC_Z23_2},

    //
    // Format Z23_3 Insns
    //
    [PPC32_IT_DQUA_Z23_3] = {arch:FEATURE_I_DFP, morph:morphDQUA_Z23_3},
    [PPC32_IT_DQUAQ_Z23_3] = {arch:FEATURE_I_DFP, morph:morphDQUAQ_Z23_3},
    [PPC32_IT_DQUAQRC_Z23_3] = {arch:FEATURE_I_DFP, morph:morphDQUAQRC_Z23_3},
    [PPC32_IT_DQUARC_Z23_3] = {arch:FEATURE_I_DFP, morph:morphDQUARC_Z23_3},
    [PPC32_IT_DRRND_Z23_3] = {arch:FEATURE_I_DFP, morph:morphDRRND_Z23_3},
    [PPC32_IT_DRRNDQ_Z23_3] = {arch:FEATURE_I_DFP, morph:morphDRRNDQ_Z23_3},
    [PPC32_IT_DRRNDQRC_Z23_3] = {arch:FEATURE_I_DFP, morph:morphDRRNDQRC_Z23_3},
    [PPC32_IT_DRRNDRC_Z23_3] = {arch:FEATURE_I_DFP, morph:morphDRRNDRC_Z23_3},

    //
    // Format Z23_5 Insns
    //

    //
    // Format Z23_6 Insns
    //
    [PPC32_IT_DRINTN_Z23_6] = {arch:FEATURE_I_DFP, morph:morphDRINTN_Z23_6},
    [PPC32_IT_DRINTNRC_Z23_6] = {arch:FEATURE_I_DFP, morph:morphDRINTNRC_Z23_6},
    [PPC32_IT_DRINTX_Z23_6] = {arch:FEATURE_I_DFP, morph:morphDRINTX_Z23_6},
    [PPC32_IT_DRINTXRC_Z23_6] = {arch:FEATURE_I_DFP, morph:morphDRINTXRC_Z23_6},

    //
    // Format Z23_7 Insns
    //
    [PPC32_IT_DRINTNQ_Z23_7] = {arch:FEATURE_I_DFP, morph:morphDRINTNQ_Z23_7},
    [PPC32_IT_DRINTNQRC_Z23_7] = {arch:FEATURE_I_DFP, morph:morphDRINTNQRC_Z23_7},
    [PPC32_IT_DRINTXQ_Z23_7] = {arch:FEATURE_I_DFP, morph:morphDRINTXQ_Z23_7},
    [PPC32_IT_DRINTXQRC_Z23_7] = {arch:FEATURE_I_DFP, morph:morphDRINTXQRC_Z23_7},

};

//
// Default undecoded/badvariant/unimplemented instruction behavior
//
static void defaultMorphCallback(
    vmiProcessorP processor,
    ppc32Addr thisPC,
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
static PPC32_MORPH_FN(emitUndefined) {
    vmimtArgProcessor();
    vmimtArgUns32(state->info.thisPC);
    vmimtArgUns64(state->info.instruction);
    vmimtArgNatAddress("undecoded");
    vmimtCall((vmiCallFn)defaultMorphCallback);
    vmimtEndBlock();
}
static PPC32_MORPH_FN(emitNotVariant) {
    vmimtArgProcessor();
    vmimtArgUns32(state->info.thisPC);
    vmimtArgUns64(state->info.instruction);
    vmimtArgNatAddress("badvariant");
    vmimtCall((vmiCallFn)defaultMorphCallback);
    vmimtEndBlock();
}
static PPC32_MORPH_FN(emitUnimplemented) {
    vmimtArgProcessor();
    vmimtArgUns32(state->info.thisPC);
    vmimtArgUns64(state->info.instruction);
    vmimtArgNatAddress("unimplemented");
    vmimtCall((vmiCallFn)defaultMorphCallback);
    vmimtEndBlock();
}

static Bool disableMorph(ppc32MorphStateP state) {
    ppc32P ppc32 = state->ppc32;
    if(!PPC32_DISASSEMBLE(ppc32)) {
        return False;
    } else if (state->info.type==PPC32_IT_LAST) {
        return False;
    } else {
        return True;
    }
}

//
// Call to implemented morph code instruction generator
//
static PPC32_MORPH_FN(emitImplemented) {
    state->attrs->morph(state);
}

//
// Return a boolean indicating whether the processor supports the required
// architecture
//
static Bool supportedOnVariant(ppc32P ppc32, ppc32MorphStateP state) {

    ppc32Architecture configVariant = ppc32->configInfo.arch;
    ppc32Architecture requiredVariant = state->attrs->arch;

    if (configVariant & requiredVariant) {
        return True;
    } else {
        return False;
    }
}

//
// Instruction Morpher
//
VMI_MORPH_FN(ppc32Morph) {
    ppc32P ppc32 = (ppc32P)processor;
    ppc32MorphState state;

    // get instruction and instruction type
    ppc32Decode(ppc32, thisPC, &state.info);

    state.attrs = &dispatchTable[state.info.type];
    state.ppc32 = ppc32;

    if(disableMorph(&state)) {
        // no action if in disassembly mode
    } else if(state.info.type==PPC32_IT_LAST) {
        // take UndefinedInstruction exception
        emitUndefined(&state);
    } else if(!supportedOnVariant(ppc32, &state)) {
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

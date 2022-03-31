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

#ifndef V850_MORPH_H
#define V850_MORPH_H

#include "vmi/vmiTypes.h"
#include "v850Decode.h"

#define V850_MORPH_FN(_NAME) void _NAME(v850MorphStateP state)
typedef V850_MORPH_FN((*v850MorphFn));

//
// Write Default Morpher stub Functions
//
V850_MORPH_FN(morphADD_F01);
V850_MORPH_FN(morphAND_F01);
V850_MORPH_FN(morphCMP_F01);
V850_MORPH_FN(morphDIVH_F01);
V850_MORPH_FN(morphMOV_F01);
V850_MORPH_FN(morphMULH_F01);
V850_MORPH_FN(morphNOT_F01);
V850_MORPH_FN(morphOR_F01);
V850_MORPH_FN(morphSATADD_F01);
V850_MORPH_FN(morphSATSUB_F01);
V850_MORPH_FN(morphSATSUBR_F01);
V850_MORPH_FN(morphSUB_F01);
V850_MORPH_FN(morphSUBR_F01);
V850_MORPH_FN(morphTST_F01);
V850_MORPH_FN(morphXOR_F01);
V850_MORPH_FN(morphDBTRAP_F01A);
V850_MORPH_FN(morphNOP_F01A);
V850_MORPH_FN(morphRIE_F01A);
V850_MORPH_FN(morphRMTRAP_F01A);
V850_MORPH_FN(morphSYNCM_F01A);
V850_MORPH_FN(morphSYNCP_F01A);
V850_MORPH_FN(morphJMP_F01B);
V850_MORPH_FN(morphSXB_F01C);
V850_MORPH_FN(morphSXH_F01C);
V850_MORPH_FN(morphZXB_F01C);
V850_MORPH_FN(morphZXH_F01C);
V850_MORPH_FN(morphSWITCH_F01D);
V850_MORPH_FN(morphFETRAP_F01E);
V850_MORPH_FN(morphCALLT_F02B);
V850_MORPH_FN(morphADD_F02S);
V850_MORPH_FN(morphCMP_F02S);
V850_MORPH_FN(morphMOV_F02S);
V850_MORPH_FN(morphMULH_F02S);
V850_MORPH_FN(morphSATADD_F02S);
V850_MORPH_FN(morphSAR_F02U);
V850_MORPH_FN(morphSHL_F02U);
V850_MORPH_FN(morphSHR_F02U);
V850_MORPH_FN(morphBCOND_F03);
V850_MORPH_FN(morphSLD_BU_F04DB);
V850_MORPH_FN(morphSLD_HU_F04DH);
V850_MORPH_FN(morphSLD_B_F04LA);
V850_MORPH_FN(morphSLD_H_F04LB);
V850_MORPH_FN(morphSLD_W_F04LC);
V850_MORPH_FN(morphSST_B_F04SA);
V850_MORPH_FN(morphSST_H_F04SB);
V850_MORPH_FN(morphSST_W_F04SC);
V850_MORPH_FN(morphJARL_F05A);
V850_MORPH_FN(morphJR_F05B);
V850_MORPH_FN(morphADDI_F06S);
V850_MORPH_FN(morphMOVEA_F06S);
V850_MORPH_FN(morphMOVHI_F06S);
V850_MORPH_FN(morphMULHI_F06S);
V850_MORPH_FN(morphSATSUBI_F06S);
V850_MORPH_FN(morphJARL_F06SA);
V850_MORPH_FN(morphJMP_F06SB);
V850_MORPH_FN(morphJR_F06SC);
V850_MORPH_FN(morphANDI_F06U);
V850_MORPH_FN(morphORI_F06U);
V850_MORPH_FN(morphXORI_F06U);
V850_MORPH_FN(morphMOV_F06UA);
V850_MORPH_FN(morphRIE_F06X);
V850_MORPH_FN(morphBCOND_F07CC);
V850_MORPH_FN(morphLD_BU_F07C);
V850_MORPH_FN(morphLD_B_F07LA);
V850_MORPH_FN(morphLD_H_F07LB);
V850_MORPH_FN(morphLD_HU_F07LB);
V850_MORPH_FN(morphLD_W_F07LB);
V850_MORPH_FN(morphST_B_F07SA);
V850_MORPH_FN(morphST_H_F07SB);
V850_MORPH_FN(morphST_W_F07SB);
V850_MORPH_FN(morphCLR1_F08);
V850_MORPH_FN(morphNOT1_F08);
V850_MORPH_FN(morphSET1_F08);
V850_MORPH_FN(morphTST1_F08);
V850_MORPH_FN(morphSASF_F09);
V850_MORPH_FN(morphSETF_F09);
V850_MORPH_FN(morphSAR_F09RR);
V850_MORPH_FN(morphSHL_F09RR);
V850_MORPH_FN(morphSHR_F09RR);
V850_MORPH_FN(morphSCH0L_F09RR2);
V850_MORPH_FN(morphSCH0R_F09RR2);
V850_MORPH_FN(morphSCH1L_F09RR2);
V850_MORPH_FN(morphSCH1R_F09RR2);
V850_MORPH_FN(morphLDSR_F09RS1_0);
V850_MORPH_FN(morphLDSR_F09RS1);
V850_MORPH_FN(morphCLR1_F09RS2);
V850_MORPH_FN(morphNOT1_F09RS2);
V850_MORPH_FN(morphSET1_F09RS2);
V850_MORPH_FN(morphTST1_F09RS2);
V850_MORPH_FN(morphSTSR_F09SR_0);
V850_MORPH_FN(morphSTSR_F09SR);
V850_MORPH_FN(morphCTRET_F10A);
V850_MORPH_FN(morphDBRET_F10A);
V850_MORPH_FN(morphDI_F10A);
V850_MORPH_FN(morphEI_F10A);
V850_MORPH_FN(morphEIRET_F10A);
V850_MORPH_FN(morphFERET_F10A);
V850_MORPH_FN(morphHALT_F10A);
V850_MORPH_FN(morphRETI_F10A);
V850_MORPH_FN(morphTRAP_F10B);
V850_MORPH_FN(morphDIV_F11);
V850_MORPH_FN(morphDIVH_F11);
V850_MORPH_FN(morphDIVHU_F11);
V850_MORPH_FN(morphDIVQ_F11);
V850_MORPH_FN(morphDIVQU_F11);
V850_MORPH_FN(morphDIVU_F11);
V850_MORPH_FN(morphMUL_F11);
V850_MORPH_FN(morphMULU_F11);
V850_MORPH_FN(morphSAR_F11);
V850_MORPH_FN(morphSATADD_F11);
V850_MORPH_FN(morphSATSUB_F11);
V850_MORPH_FN(morphSHL_F11);
V850_MORPH_FN(morphSHR_F11);
V850_MORPH_FN(morphMAC_F11A);
V850_MORPH_FN(morphMACU_F11A);
V850_MORPH_FN(morphADF_F11B);
V850_MORPH_FN(morphCMOV_F11B);
V850_MORPH_FN(morphSBF_F11B);
V850_MORPH_FN(morphCAXI_F11C);
V850_MORPH_FN(morphJARL_F11D);
V850_MORPH_FN(morphCMOV_F12A);
V850_MORPH_FN(morphBSH_F12B);
V850_MORPH_FN(morphBSW_F12B);
V850_MORPH_FN(morphHSH_F12B);
V850_MORPH_FN(morphHSW_F12B);
V850_MORPH_FN(morphMUL_F12S);
V850_MORPH_FN(morphMULU_F12U);
V850_MORPH_FN(morphDISPOSE_F13IL1);
V850_MORPH_FN(morphDISPOSE_F13IL2);
V850_MORPH_FN(morphPREPARE_F13LI);
V850_MORPH_FN(morphPREPARE_F13LI00);
V850_MORPH_FN(morphPREPARE_F13LI01);
V850_MORPH_FN(morphPREPARE_F13LI10);
V850_MORPH_FN(morphPREPARE_F13LI11);
V850_MORPH_FN(morphADDF_S_FI);
V850_MORPH_FN(morphDIVF_S_FI);
V850_MORPH_FN(morphMAXF_S_FI);
V850_MORPH_FN(morphMINF_S_FI);
V850_MORPH_FN(morphMULF_S_FI);
V850_MORPH_FN(morphSUBF_S_FI);
V850_MORPH_FN(morphADDF_D_FID);
V850_MORPH_FN(morphDIVF_D_FID);
V850_MORPH_FN(morphMAXF_D_FID);
V850_MORPH_FN(morphMINF_D_FID);
V850_MORPH_FN(morphMULF_D_FID);
V850_MORPH_FN(morphSUBF_D_FID);
V850_MORPH_FN(morphCEILF_DW_FIDSR2R3);
V850_MORPH_FN(morphCVTF_DS_FIDSR2R3);
V850_MORPH_FN(morphCVTF_DUW_FIDSR2R3);
V850_MORPH_FN(morphCVTF_DW_FIDSR2R3);
V850_MORPH_FN(morphCVTF_LS_FIDSR2R3);
V850_MORPH_FN(morphCVTF_ULS_FIDSR2R3);
V850_MORPH_FN(morphFLOORF_DW_FIDSR2R3);
V850_MORPH_FN(morphTRNCF_DW_FIDSR2R3);
V850_MORPH_FN(morphCMPF_D_FIDCOND);
V850_MORPH_FN(morphCMOVF_D_FIDFFF);
V850_MORPH_FN(morphABSF_D_FIDR2R3);
V850_MORPH_FN(morphCEILF_DL_FIDR2R3);
V850_MORPH_FN(morphCEILF_DUL_FIDR2R3);
V850_MORPH_FN(morphCEILF_DUW_FIDR2R3);
V850_MORPH_FN(morphCVTF_DL_FIDR2R3);
V850_MORPH_FN(morphCVTF_DUL_FIDR2R3);
V850_MORPH_FN(morphCVTF_ULD_FIDR2R3);
V850_MORPH_FN(morphFLOORF_DL_FIDR2R3);
V850_MORPH_FN(morphFLOORF_DUL_FIDR2R3);
V850_MORPH_FN(morphFLOORF_DUW_FIDR2R3);
V850_MORPH_FN(morphNEGF_D_FIDR2R3);
V850_MORPH_FN(morphRECIPF_D_FIDR2R3);
V850_MORPH_FN(morphRSQRTF_D_FIDR2R3);
V850_MORPH_FN(morphSQRTF_D_FIDR2R3);
V850_MORPH_FN(morphTRNCF_DL_FIDR2R3);
V850_MORPH_FN(morphTRNCF_DUL_FIDR2R3);
V850_MORPH_FN(morphTRNCF_DUW_FIDR2R3);
V850_MORPH_FN(morphABSF_S_FII);
V850_MORPH_FN(morphCVT_SW_FII);
V850_MORPH_FN(morphCVT_WS_FII);
V850_MORPH_FN(morphNEGF_S_FII);
V850_MORPH_FN(morphTRNC_SW_FII);
V850_MORPH_FN(morphADDF_S_FIS);
V850_MORPH_FN(morphDIVF_S_FIS);
V850_MORPH_FN(morphMAXF_S_FIS);
V850_MORPH_FN(morphMINF_S_FIS);
V850_MORPH_FN(morphMULF_S_FIS);
V850_MORPH_FN(morphSUBF_S_FIS);
V850_MORPH_FN(morphCEILF_SL_FISDR2R3);
V850_MORPH_FN(morphCEILF_SUL_FISDR2R3);
V850_MORPH_FN(morphCVTF_SD_FISDR2R3);
V850_MORPH_FN(morphCVTF_SL_FISDR2R3);
V850_MORPH_FN(morphCVTF_SUL_FISDR2R3);
V850_MORPH_FN(morphCVTF_UWD_FISDR2R3);
V850_MORPH_FN(morphCVTF_WD_FISDR2R3);
V850_MORPH_FN(morphFLOORF_SL_FISDR2R3);
V850_MORPH_FN(morphFLOORF_SUL_FISDR2R3);
V850_MORPH_FN(morphTRNCF_SL_FISDR2R3);
V850_MORPH_FN(morphTRNCF_SUL_FISDR2R3);
V850_MORPH_FN(morphMADDF_S_FISA);
V850_MORPH_FN(morphMSUBF_S_FISA);
V850_MORPH_FN(morphNMADDF_S_FISA);
V850_MORPH_FN(morphNMSUBF_S_FISA);
V850_MORPH_FN(morphCMPF_S_FISCOND);
V850_MORPH_FN(morphCMOVF_S_FISFFF);
V850_MORPH_FN(morphABSF_S_FISR2R3);
V850_MORPH_FN(morphCEILF_SUW_FISR2R3);
V850_MORPH_FN(morphCEILF_SW_FISR2R3);
V850_MORPH_FN(morphCVTF_LD_FISR2R3);
V850_MORPH_FN(morphCVTF_SUW_FISR2R3);
V850_MORPH_FN(morphCVTF_SW_FISR2R3);
V850_MORPH_FN(morphCVTF_UWS_FISR2R3);
V850_MORPH_FN(morphCVTF_WS_FISR2R3);
V850_MORPH_FN(morphFLOORF_SUW_FISR2R3);
V850_MORPH_FN(morphFLOORF_SW_FISR2R3);
V850_MORPH_FN(morphNEGF_S_FISR2R3);
V850_MORPH_FN(morphRECIPF_S_FISR2R3);
V850_MORPH_FN(morphRSQRTF_S_FISR2R3);
V850_MORPH_FN(morphSQRTF_S_FISR2R3);
V850_MORPH_FN(morphTRNCF_SUW_FISR2R3);
V850_MORPH_FN(morphTRNCF_SW_FISR2R3);
V850_MORPH_FN(morphTRFF_FIV);
V850_MORPH_FN(morphLDFF_FIVR2A);
V850_MORPH_FN(morphLDFC_FIVR2B);
V850_MORPH_FN(morphSTFF_FIVR3A);
V850_MORPH_FN(morphSTFC_FIVR3B);
V850_MORPH_FN(morphTRFSR_FIFFF);
//
// RH850 Only
//
V850_MORPH_FN(morphLDL_W_F07D);
V850_MORPH_FN(morphSTC_W_F07D);
V850_MORPH_FN(morphBINS_F09RPWR_0);
V850_MORPH_FN(morphBINS_F09RPWR_1);
V850_MORPH_FN(morphBINS_F09RPWR_2);
V850_MORPH_FN(morphCLL_F10);
V850_MORPH_FN(morphSNOOZE_F10);
V850_MORPH_FN(morphROTL_F07RRR);
V850_MORPH_FN(morphPUSHSP_F11);
V850_MORPH_FN(morphPOPSP_F11);
V850_MORPH_FN(morphROTL_F07IRR);
V850_MORPH_FN(morphLD_DW_F14);
V850_MORPH_FN(morphST_DW_F14);
V850_MORPH_FN(morphBCOND_F07CC);
V850_MORPH_FN(morphJARL_F11D);
V850_MORPH_FN(morphLOOP_F07RI);
V850_MORPH_FN(morphLD_B_F14);
V850_MORPH_FN(morphLD_BU_F14);
V850_MORPH_FN(morphLD_H_F14);
V850_MORPH_FN(morphLD_HU_F14);
V850_MORPH_FN(morphLD_W_F14);
V850_MORPH_FN(morphST_B_F14);
V850_MORPH_FN(morphST_H_F14);
V850_MORPH_FN(morphST_W_F14);
V850_MORPH_FN(morphCACHE_F10);
V850_MORPH_FN(morphCACHE_CHBII);
V850_MORPH_FN(morphCACHE_CIBII);
V850_MORPH_FN(morphCACHE_CFALI);
V850_MORPH_FN(morphCACHE_CISTI);
V850_MORPH_FN(morphCACHE_CILDI);
V850_MORPH_FN(morphPREF_F10);
V850_MORPH_FN(morphPREFI_F10);
V850_MORPH_FN(morphCVTF_HS_FI);
V850_MORPH_FN(morphCVTF_SH_FI);
V850_MORPH_FN(morphFMAF_S_FI);
V850_MORPH_FN(morphFMSF_S_FI);
V850_MORPH_FN(morphFNMAF_S_FI);
V850_MORPH_FN(morphFNMSF_S_FI);
V850_MORPH_FN(morphSYSCALL_F10C);
V850_MORPH_FN(morphSYNCE_F01A);
V850_MORPH_FN(morphSYNCI_F01A);

typedef struct v850MorphAttrS {
    v850MorphFn      morph; // callback function to morph the instruction
    v850Architecture arch;
    vmiFlagsCP       flags; // flags Constant pointer
} v850MorphAttr;

typedef struct v850MorphStateS {
    v850InstructionInfo info;       // instruction description - from decoder
    v850MorphAttrCP     attrs;      // instruction attributes
    v850BlockStateP     blockState; // per-block context
    v850P               v850;       // current processor
    v850Addr            nextPC;     // next instruction address in sequence
} v850MorphState;

#endif // V850_MORPH_H
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
#include "ppc32Decode.h"
#include "ppc32Instructions.h"
#include "ppc32Functions.h"

//
// Generate the disassembler alias lookup table for AALK
//
const char *AALK[4] = {
    [0] = "",
    [1] = "l",
    [2] = "a",
    [3] = "la",
};

//
// Generate the disassembler alias lookup table for BITSTR
//
const char *BITSTR[16] = {
    [0] = "dnzf-",
    [1] = "dnzf+",
    [2] = "dzf-",
    [3] = "dzf+",
    [4] = "nzf-",
    [5] = "nzf+",
    [6] = "zf-",
    [7] = "zf+",
    [8] = "dnzt-",
    [9] = "dnzt+",
    [10] = "dzt-",
    [11] = "dzt+",
    [12] = "nzt-",
    [13] = "nzt+",
    [14] = "zt-",
    [15] = "zt+",
};

//
// Generate the disassembler alias lookup table for BITSTR32
//
const char *BITSTR32[4] = {
    [0] = "f",
    [1] = "t",
    [2] = "dnz",
    [3] = "dz",
};

//
// Generate the disassembler alias lookup table for CR
//
const char *CR[32] = {
    [0] = "lt",
    [1] = "gt",
    [2] = "eq",
    [3] = "so",
    [4] = "4*cr1+lt",
    [5] = "4*cr1+gt",
    [6] = "4*cr1+eq",
    [7] = "4*cr1+so",
    [8] = "4*cr2+lt",
    [9] = "4*cr2+gt",
    [10] = "4*cr2+eq",
    [11] = "4*cr2+so",
    [12] = "4*cr3+lt",
    [13] = "4*cr3+gt",
    [14] = "4*cr3+eq",
    [15] = "4*cr3+so",
    [16] = "4*cr4+lt",
    [17] = "4*cr4+gt",
    [18] = "4*cr4+eq",
    [19] = "4*cr4+so",
    [20] = "4*cr5+lt",
    [21] = "4*cr5+gt",
    [22] = "4*cr5+eq",
    [23] = "4*cr5+so",
    [24] = "4*cr6+lt",
    [25] = "4*cr6+gt",
    [26] = "4*cr6+eq",
    [27] = "4*cr6+so",
    [28] = "4*cr7+lt",
    [29] = "4*cr7+gt",
    [30] = "4*cr7+eq",
    [31] = "4*cr7+so",
};

//
// Generate the disassembler alias lookup table for CRVLE
//
const char *CRVLE[16] = {
    [0] = "cr0+lt",
    [1] = "cr0+gt",
    [2] = "cr0+eq",
    [3] = "cr0+so",
    [4] = "cr1+lt",
    [5] = "cr1+gt",
    [6] = "cr1+eq",
    [7] = "cr1+so",
    [8] = "cr2+lt",
    [9] = "cr2+gt",
    [10] = "cr2+eq",
    [11] = "cr2+so",
    [12] = "cr3+lt",
    [13] = "cr3+gt",
    [14] = "cr3+eq",
    [15] = "cr3+so",
};

//
// Generate the disassembler alias lookup table for EH
//
const char *EH[2] = {
    [1] = ",1",
};

//
// Generate the disassembler alias lookup table for RA
//
const char *RA[32] = {
    [0] = "0",
    [1] = "r1",
    [2] = "r2",
    [3] = "r3",
    [4] = "r4",
    [5] = "r5",
    [6] = "r6",
    [7] = "r7",
    [8] = "r8",
    [9] = "r9",
    [10] = "r10",
    [11] = "r11",
    [12] = "r12",
    [13] = "r13",
    [14] = "r14",
    [15] = "r15",
    [16] = "r16",
    [17] = "r17",
    [18] = "r18",
    [19] = "r19",
    [20] = "r20",
    [21] = "r21",
    [22] = "r22",
    [23] = "r23",
    [24] = "r24",
    [25] = "r25",
    [26] = "r26",
    [27] = "r27",
    [28] = "r28",
    [29] = "r29",
    [30] = "r30",
    [31] = "r31",
};

//
// Generate the disassembler alias lookup table for TO
//
const char *TO[32] = {
    [1] = "lgt",
    [2] = "llt",
    [4] = "eq",
    [5] = "lge",
    [6] = "lle",
    [8] = "gt",
    [12] = "ge",
    [16] = "lt",
    [20] = "le",
    [24] = "ne",
};

//
// Generate the disassembler statemachine definitions
//
#define EMITAALK      "\200"
#define EMITAALK_CASE '\200'
#define EMITARX      "\201"
#define EMITARX_CASE '\201'
#define EMITARY      "\202"
#define EMITARY_CASE '\202'
#define EMITBA      "\203"
#define EMITBA_CASE '\203'
#define EMITBB      "\204"
#define EMITBB_CASE '\204'
#define EMITBC      "\205"
#define EMITBC_CASE '\205'
#define EMITBD      "\206"
#define EMITBD_CASE '\206'
#define EMITBD24      "\207"
#define EMITBD24_CASE '\207'
#define EMITBD8      "\210"
#define EMITBD8_CASE '\210'
#define EMITBF      "\211"
#define EMITBF_CASE '\211'
#define EMITBF32      "\212"
#define EMITBF32_CASE '\212'
#define EMITBFA      "\213"
#define EMITBFA_CASE '\213'
#define EMITBFU      "\214"
#define EMITBFU_CASE '\214'
#define EMITBI      "\215"
#define EMITBI_CASE '\215'
#define EMITBI16      "\216"
#define EMITBI16_CASE '\216'
#define EMITBI32      "\217"
#define EMITBI32_CASE '\217'
#define EMITBL      "\220"
#define EMITBL_CASE '\220'
#define EMITBO16      "\221"
#define EMITBO16_CASE '\221'
#define EMITBO32      "\222"
#define EMITBO32_CASE '\222'
#define EMITBO_0      "\223"
#define EMITBO_0_CASE '\223'
#define EMITBO_1      "\224"
#define EMITBO_1_CASE '\224'
#define EMITBT      "\225"
#define EMITBT_CASE '\225'
#define EMITBW      "\226"
#define EMITBW_CASE '\226'
#define EMITCT      "\227"
#define EMITCT_CASE '\227'
#define EMITD      "\230"
#define EMITD_CASE '\230'
#define EMITD8      "\231"
#define EMITD8_CASE '\231'
#define EMITDCM      "\232"
#define EMITDCM_CASE '\232'
#define EMITDCR      "\233"
#define EMITDCR_CASE '\233'
#define EMITDQ      "\234"
#define EMITDQ_CASE '\234'
#define EMITDS      "\235"
#define EMITDS_CASE '\235'
#define EMITDUI      "\236"
#define EMITDUI_CASE '\236'
#define EMITDUIS      "\237"
#define EMITDUIS_CASE '\237'
#define EMITE      "\240"
#define EMITE_CASE '\240'
#define EMITEH      "\241"
#define EMITEH_CASE '\241'
#define EMITFLM      "\242"
#define EMITFLM_CASE '\242'
#define EMITFRA      "\243"
#define EMITFRA_CASE '\243'
#define EMITFRAP      "\244"
#define EMITFRAP_CASE '\244'
#define EMITFRB      "\245"
#define EMITFRB_CASE '\245'
#define EMITFRBP      "\246"
#define EMITFRBP_CASE '\246'
#define EMITFRC      "\247"
#define EMITFRC_CASE '\247'
#define EMITFRS      "\250"
#define EMITFRS_CASE '\250'
#define EMITFRT      "\251"
#define EMITFRT_CASE '\251'
#define EMITFRTP      "\252"
#define EMITFRTP_CASE '\252'
#define EMITFXM      "\253"
#define EMITFXM_CASE '\253'
#define EMITIH      "\254"
#define EMITIH_CASE '\254'
#define EMITLEV      "\255"
#define EMITLEV_CASE '\255'
#define EMITLI      "\256"
#define EMITLI_CASE '\256'
#define EMITLI20      "\257"
#define EMITLI20_CASE '\257'
#define EMITLK      "\260"
#define EMITLK_CASE '\260'
#define EMITMB      "\261"
#define EMITMB_CASE '\261'
#define EMITME      "\262"
#define EMITME_CASE '\262'
#define EMITMO      "\263"
#define EMITMO_CASE '\263'
#define EMITNB      "\264"
#define EMITNB_CASE '\264'
#define EMITOIM5      "\265"
#define EMITOIM5_CASE '\265'
#define EMITOP      "\266"
#define EMITOP_CASE '\266'
#define EMITPMRN      "\267"
#define EMITPMRN_CASE '\267'
#define EMITR      "\270"
#define EMITR_CASE '\270'
#define EMITRA      "\271"
#define EMITRA_CASE '\271'
#define EMITRA_AL      "\272"
#define EMITRA_AL_CASE '\272'
#define EMITRB      "\273"
#define EMITRB_CASE '\273'
#define EMITRMC      "\274"
#define EMITRMC_CASE '\274'
#define EMITRS      "\275"
#define EMITRS_CASE '\275'
#define EMITRSP      "\276"
#define EMITRSP_CASE '\276'
#define EMITRT      "\277"
#define EMITRT_CASE '\277'
#define EMITRTP      "\300"
#define EMITRTP_CASE '\300'
#define EMITRX      "\301"
#define EMITRX_CASE '\301'
#define EMITRY      "\302"
#define EMITRY_CASE '\302'
#define EMITRZ      "\303"
#define EMITRZ_CASE '\303'
#define EMITS      "\304"
#define EMITS_CASE '\304'
#define EMITS8      "\305"
#define EMITS8_CASE '\305'
#define EMITSD4      "\306"
#define EMITSD4_CASE '\306'
#define EMITSH      "\307"
#define EMITSH_CASE '\307'
#define EMITSHB      "\310"
#define EMITSHB_CASE '\310'
#define EMITSI      "\311"
#define EMITSI_CASE '\311'
#define EMITSIM      "\312"
#define EMITSIM_CASE '\312'
#define EMITSP      "\313"
#define EMITSP_CASE '\313'
#define EMITSPR      "\314"
#define EMITSPR_CASE '\314'
#define EMITSR      "\315"
#define EMITSR_CASE '\315'
#define EMITTE      "\316"
#define EMITTE_CASE '\316'
#define EMITTH      "\317"
#define EMITTH_CASE '\317'
#define EMITTO      "\320"
#define EMITTO_CASE '\320'
#define EMITU      "\321"
#define EMITU_CASE '\321'
#define EMITU8      "\322"
#define EMITU8_CASE '\322'
#define EMITUI      "\323"
#define EMITUI_CASE '\323'
#define EMITUI5      "\324"
#define EMITUI5_CASE '\324'
#define EMITUI7      "\325"
#define EMITUI7_CASE '\325'
#define EMITUIM      "\326"
#define EMITUIM_CASE '\326'
#define EMITVRA      "\327"
#define EMITVRA_CASE '\327'
#define EMITVRB      "\330"
#define EMITVRB_CASE '\330'
#define EMITVRC      "\331"
#define EMITVRC_CASE '\331'
#define EMITVRS      "\332"
#define EMITVRS_CASE '\332'
#define EMITVRT      "\333"
#define EMITVRT_CASE '\333'

//
// Generate the instruction formatting table
//
#define FMT_NONE ""
const char *formats[PPC32_IT_LAST+1] = {
    //
    // Instruction Format A1 Insns
    //
    [PPC32_IT_FMADD_A1]      = EMITOP " " EMITFRT "," EMITFRA "," EMITFRC "," EMITFRB,
    [PPC32_IT_FMADDRC_A1]    = EMITOP " " EMITFRT "," EMITFRA "," EMITFRC "," EMITFRB,
    [PPC32_IT_FMADDS_A1]     = EMITOP " " EMITFRT "," EMITFRA "," EMITFRC "," EMITFRB,
    [PPC32_IT_FMADDSRC_A1]   = EMITOP " " EMITFRT "," EMITFRA "," EMITFRC "," EMITFRB,
    [PPC32_IT_FMSUB_A1]      = EMITOP " " EMITFRT "," EMITFRA "," EMITFRC "," EMITFRB,
    [PPC32_IT_FMSUBRC_A1]    = EMITOP " " EMITFRT "," EMITFRA "," EMITFRC "," EMITFRB,
    [PPC32_IT_FMSUBS_A1]     = EMITOP " " EMITFRT "," EMITFRA "," EMITFRC "," EMITFRB,
    [PPC32_IT_FMSUBSRC_A1]   = EMITOP " " EMITFRT "," EMITFRA "," EMITFRC "," EMITFRB,
    [PPC32_IT_FNMADD_A1]     = EMITOP " " EMITFRT "," EMITFRA "," EMITFRC "," EMITFRB,
    [PPC32_IT_FNMADDRC_A1]   = EMITOP " " EMITFRT "," EMITFRA "," EMITFRC "," EMITFRB,
    [PPC32_IT_FNMADDS_A1]    = EMITOP " " EMITFRT "," EMITFRA "," EMITFRC "," EMITFRB,
    [PPC32_IT_FNMADDSRC_A1]  = EMITOP " " EMITFRT "," EMITFRA "," EMITFRC "," EMITFRB,
    [PPC32_IT_FNMSUB_A1]     = EMITOP " " EMITFRT "," EMITFRA "," EMITFRC "," EMITFRB,
    [PPC32_IT_FNMSUBRC_A1]   = EMITOP " " EMITFRT "," EMITFRA "," EMITFRC "," EMITFRB,
    [PPC32_IT_FNMSUBS_A1]    = EMITOP " " EMITFRT "," EMITFRA "," EMITFRC "," EMITFRB,
    [PPC32_IT_FNMSUBSRC_A1]  = EMITOP " " EMITFRT "," EMITFRA "," EMITFRC "," EMITFRB,
    [PPC32_IT_FSEL_A1]       = EMITOP " " EMITFRT "," EMITFRA "," EMITFRC "," EMITFRB,
    [PPC32_IT_FSELRC_A1]     = EMITOP " " EMITFRT "," EMITFRA "," EMITFRC "," EMITFRB,

    //
    // Instruction Format A2 Insns
    //
    [PPC32_IT_FADD_A2]       = EMITOP " " EMITFRT "," EMITFRA "," EMITFRB,
    [PPC32_IT_FADDRC_A2]     = EMITOP " " EMITFRT "," EMITFRA "," EMITFRB,
    [PPC32_IT_FADDS_A2]      = EMITOP " " EMITFRT "," EMITFRA "," EMITFRB,
    [PPC32_IT_FADDSRC_A2]    = EMITOP " " EMITFRT "," EMITFRA "," EMITFRB,
    [PPC32_IT_FDIV_A2]       = EMITOP " " EMITFRT "," EMITFRA "," EMITFRB,
    [PPC32_IT_FDIVRC_A2]     = EMITOP " " EMITFRT "," EMITFRA "," EMITFRB,
    [PPC32_IT_FDIVS_A2]      = EMITOP " " EMITFRT "," EMITFRA "," EMITFRB,
    [PPC32_IT_FDIVSRC_A2]    = EMITOP " " EMITFRT "," EMITFRA "," EMITFRB,
    [PPC32_IT_FSUB_A2]       = EMITOP " " EMITFRT "," EMITFRA "," EMITFRB,
    [PPC32_IT_FSUBRC_A2]     = EMITOP " " EMITFRT "," EMITFRA "," EMITFRB,
    [PPC32_IT_FSUBS_A2]      = EMITOP " " EMITFRT "," EMITFRA "," EMITFRB,
    [PPC32_IT_FSUBSRC_A2]    = EMITOP " " EMITFRT "," EMITFRA "," EMITFRB,

    //
    // Instruction Format A3 Insns
    //
    [PPC32_IT_FMUL_A3]       = EMITOP " " EMITFRT "," EMITFRA "," EMITFRC,
    [PPC32_IT_FMULRC_A3]     = EMITOP " " EMITFRT "," EMITFRA "," EMITFRC,
    [PPC32_IT_FMULS_A3]      = EMITOP " " EMITFRT "," EMITFRA "," EMITFRC,
    [PPC32_IT_FMULSRC_A3]    = EMITOP " " EMITFRT "," EMITFRA "," EMITFRC,

    //
    // Instruction Format A4 Insns
    //
    [PPC32_IT_FSQRT_A4]      = EMITOP " " EMITFRT "," EMITFRB,
    [PPC32_IT_FSQRTRC_A4]    = EMITOP " " EMITFRT "," EMITFRB,
    [PPC32_IT_FSQRTS_A4]     = EMITOP " " EMITFRT "," EMITFRB,
    [PPC32_IT_FSQRTSRC_A4]   = EMITOP " " EMITFRT "," EMITFRB,

    //
    // Instruction Format A5 Insns
    //
    [PPC32_IT_FRE_A5]        = EMITOP " " EMITFRT "," EMITFRB,
    [PPC32_IT_FRERC_A5]      = EMITOP " " EMITFRT "," EMITFRB,
    [PPC32_IT_FRES_A5]       = EMITOP " " EMITFRT "," EMITFRB,
    [PPC32_IT_FRESRC_A5]     = EMITOP " " EMITFRT "," EMITFRB,
    [PPC32_IT_FRSQRTE_A5]    = EMITOP " " EMITFRT "," EMITFRB,
    [PPC32_IT_FRSQRTERC_A5]  = EMITOP " " EMITFRT "," EMITFRB,
    [PPC32_IT_FRSQRTES_A5]   = EMITOP " " EMITFRT "," EMITFRB,
    [PPC32_IT_FRSQRTESRC_A5] = EMITOP " " EMITFRT "," EMITFRB,

    //
    // Instruction Format A6 Insns
    //
    [PPC32_IT_ISEL_A6]       = EMITOP " " EMITRT  "," EMITRA  "," EMITRB  "," EMITBC,

    //
    // Instruction Format B1 Insns
    //
    [PPC32_IT_BC_B1]         = EMITOP EMITAALK " " EMITBO_0 "," EMITBI "," EMITBD,

    //
    // Instruction Format BD15 Insns
    //
    [PPC32_IT_E_BC_BD15]     = EMITOP EMITLK " " EMITBO32 "," EMITBI32 "," EMITBD,

    //
    // Instruction Format BD24 Insns
    //
    [PPC32_IT_E_B_BD24]      = EMITOP EMITLK " " EMITBD24,

    //
    // Instruction Format BD81 Insns
    //
    [PPC32_IT_SE_BC_BD81]    = EMITOP        " " EMITBO16 "," EMITBI16 "," EMITBD8,

    //
    // Instruction Format BD82 Insns
    //
    [PPC32_IT_SE_B_BD82]     = EMITOP EMITLK " " EMITBD8,

    //
    // Instruction Format C_0 Insns
    //
    [PPC32_IT_SE_ILLEGAL_C_0] = EMITOP,
    [PPC32_IT_SE_ISYNC_C_0]  = EMITOP,
    [PPC32_IT_SE_RFCI_C_0]   = EMITOP,
    [PPC32_IT_SE_RFDI_C_0]   = EMITOP,
    [PPC32_IT_SE_RFI_C_0]    = EMITOP,
    [PPC32_IT_SE_RFMCI_C_0]  = EMITOP,
    [PPC32_IT_SE_SC_C_0]     = EMITOP,

    //
    // Instruction Format C_1 Insns
    //
    [PPC32_IT_SE_BCTR_C_1]   = EMITOP EMITLK,
    [PPC32_IT_SE_BLR_C_1]    = EMITOP EMITLK,

    //
    // Instruction Format D1 Insns
    //
    [PPC32_IT_E_LBZ_D1]      = EMITOP " " EMITRT  "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_E_LHA_D1]      = EMITOP " " EMITRT  "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_E_LHZ_D1]      = EMITOP " " EMITRT  "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_E_LWZ_D1]      = EMITOP " " EMITRT  "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_LBZ_D1]        = EMITOP " " EMITRT  "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_LBZU_D1]       = EMITOP " " EMITRT  "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_LHA_D1]        = EMITOP " " EMITRT  "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_LHAU_D1]       = EMITOP " " EMITRT  "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_LHZ_D1]        = EMITOP " " EMITRT  "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_LHZU_D1]       = EMITOP " " EMITRT  "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_LMW_D1]        = EMITOP " " EMITRT  "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_LWZ_D1]        = EMITOP " " EMITRT  "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_LWZU_D1]       = EMITOP " " EMITRT  "," EMITD  "(" EMITRA_AL ")",

    //
    // Instruction Format D2 Insns
    //
    [PPC32_IT_E_ADD16I_D2]   = EMITOP " " EMITRT  "," EMITRA "," EMITSI,

    //
    // Instruction Format D2_0 Insns
    //
    [PPC32_IT_ADDI_D2_0]     = EMITOP " " EMITRT  "," EMITRA "," EMITSI,
    [PPC32_IT_ADDIC_D2_0]    = EMITOP " " EMITRT  "," EMITRA "," EMITSI,
    [PPC32_IT_ADDICRC_D2_0]  = EMITOP " " EMITRT  "," EMITRA "," EMITSI,
    [PPC32_IT_ADDIS_D2_0]    = EMITOP " " EMITRT  "," EMITRA "," EMITSI,
    [PPC32_IT_MULLI_D2_0]    = EMITOP " " EMITRT  "," EMITRA "," EMITSI,
    [PPC32_IT_SUBFIC_D2_0]   = EMITOP " " EMITRT  "," EMITRA "," EMITSI,

    //
    // Instruction Format D2_1 Insns
    //
    [PPC32_IT_LI_D2_1]       = EMITOP " " EMITRT             "," EMITSI,
    [PPC32_IT_LIS_D2_1]      = EMITOP " " EMITRT             "," EMITSI,

    //
    // Instruction Format D3 Insns
    //
    [PPC32_IT_E_STB_D3]      = EMITOP " " EMITRS  "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_E_STH_D3]      = EMITOP " " EMITRS  "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_E_STW_D3]      = EMITOP " " EMITRS  "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_STB_D3]        = EMITOP " " EMITRS  "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_STBU_D3]       = EMITOP " " EMITRS  "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_STH_D3]        = EMITOP " " EMITRS  "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_STHU_D3]       = EMITOP " " EMITRS  "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_STMW_D3]       = EMITOP " " EMITRS  "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_STW_D3]        = EMITOP " " EMITRS  "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_STWU_D3]       = EMITOP " " EMITRS  "," EMITD  "(" EMITRA_AL ")",

    //
    // Instruction Format D4 Insns
    //
    [PPC32_IT_ANDIRC_D4]     = EMITOP " " EMITRA  "," EMITRS "," EMITUI,
    [PPC32_IT_ANDISRC_D4]    = EMITOP " " EMITRA  "," EMITRS "," EMITUI,
    [PPC32_IT_ORI_D4]        = EMITOP " " EMITRA  "," EMITRS "," EMITUI,
    [PPC32_IT_ORIS_D4]       = EMITOP " " EMITRA  "," EMITRS "," EMITUI,
    [PPC32_IT_XORI_D4]       = EMITOP " " EMITRA  "," EMITRS "," EMITUI,
    [PPC32_IT_XORIS_D4]      = EMITOP " " EMITRA  "," EMITRS "," EMITUI,

    //
    // Instruction Format D5_0 Insns
    //
    [PPC32_IT_CMPWI_D5_0]    = EMITOP " " EMITBF  ","   EMITRA "," EMITSI,

    //
    // Instruction Format D5_1 Insns
    //
    [PPC32_IT_CMPI_D5_1]     = EMITOP " " EMITBF  ",1," EMITRA "," EMITSI,

    //
    // Instruction Format D6_0 Insns
    //
    [PPC32_IT_CMPLWI_D6_0]   = EMITOP " " EMITBF  ","   EMITRA "," EMITUI,

    //
    // Instruction Format D6_1 Insns
    //
    [PPC32_IT_CMPLI_D6_1]    = EMITOP " " EMITBF  ",1," EMITRA "," EMITUI,

    //
    // Instruction Format D7 Insns
    //
    [PPC32_IT_TWI_D7]        = EMITOP " " EMITTO  "," EMITRA "," EMITSI,

    //
    // Instruction Format D8 Insns
    //
    [PPC32_IT_LFD_D8]        = EMITOP " " EMITFRT "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_LFDU_D8]       = EMITOP " " EMITFRT "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_LFS_D8]        = EMITOP " " EMITFRT "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_LFSU_D8]       = EMITOP " " EMITFRT "," EMITD  "(" EMITRA_AL ")",

    //
    // Instruction Format D8_0 Insns
    //
    [PPC32_IT_E_LBZU_D8_0]   = EMITOP " " EMITRT "," EMITD8 "(" EMITRA_AL ")",
    [PPC32_IT_E_LHAU_D8_0]   = EMITOP " " EMITRT "," EMITD8 "(" EMITRA_AL ")",
    [PPC32_IT_E_LHZU_D8_0]   = EMITOP " " EMITRT "," EMITD8 "(" EMITRA_AL ")",
    [PPC32_IT_E_LMW_D8_0]    = EMITOP " " EMITRT "," EMITD8 "(" EMITRA_AL ")",
    [PPC32_IT_E_LWZU_D8_0]   = EMITOP " " EMITRT "," EMITD8 "(" EMITRA_AL ")",

    //
    // Instruction Format D8_1 Insns
    //
    [PPC32_IT_E_STBU_D8_1]   = EMITOP " " EMITRS "," EMITD8 "(" EMITRA_AL ")",
    [PPC32_IT_E_STHU_D8_1]   = EMITOP " " EMITRS "," EMITD8 "(" EMITRA_AL ")",
    [PPC32_IT_E_STMW_D8_1]   = EMITOP " " EMITRS "," EMITD8 "(" EMITRA_AL ")",
    [PPC32_IT_E_STWU_D8_1]   = EMITOP " " EMITRS "," EMITD8 "(" EMITRA_AL ")",

    //
    // Instruction Format D9 Insns
    //
    [PPC32_IT_STFD_D9]       = EMITOP " " EMITFRS "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_STFDU_D9]      = EMITOP " " EMITFRS "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_STFS_D9]       = EMITOP " " EMITFRS "," EMITD  "(" EMITRA_AL ")",
    [PPC32_IT_STFSU_D9]      = EMITOP " " EMITFRS "," EMITD  "(" EMITRA_AL ")",

    //
    // Instruction Format DQ1 Insns
    //
    [PPC32_IT_LQ_DQ1]        = EMITOP " " EMITRTP "," EMITDQ  "(" EMITRA_AL ")",

    //
    // Instruction Format DS1 Insns
    //

    //
    // Instruction Format DS2 Insns
    //

    //
    // Instruction Format DS3 Insns
    //
    [PPC32_IT_STQ_DS3]       = EMITOP " " EMITRSP "," EMITDS  "(" EMITRA_AL ")",

    //
    // Instruction Format DS4 Insns
    //

    //
    // Instruction Format DS5 Insns
    //

    //
    // Instruction Format EVS Insns
    //
    [PPC32_IT_EVSEL_EVS]     = EMITOP " " EMITRT "," EMITRA "," EMITRB "," EMITBFA,

    //
    // Instruction Format EVX1 Insns
    //
    [PPC32_IT_BRINC_EVX1]    = EMITOP " " EMITRS "," EMITRA "," EMITRB,
    [PPC32_IT_EVSTDDX_EVX1]  = EMITOP " " EMITRS "," EMITRA "," EMITRB,
    [PPC32_IT_EVSTDHX_EVX1]  = EMITOP " " EMITRS "," EMITRA "," EMITRB,
    [PPC32_IT_EVSTDWX_EVX1]  = EMITOP " " EMITRS "," EMITRA "," EMITRB,
    [PPC32_IT_EVSTWHEX_EVX1] = EMITOP " " EMITRS "," EMITRA "," EMITRB,
    [PPC32_IT_EVSTWHOX_EVX1] = EMITOP " " EMITRS "," EMITRA "," EMITRB,
    [PPC32_IT_EVSTWWEX_EVX1] = EMITOP " " EMITRS "," EMITRA "," EMITRB,
    [PPC32_IT_EVSTWWOX_EVX1] = EMITOP " " EMITRS "," EMITRA "," EMITRB,

    //
    // Instruction Format EVX2 Insns
    //

    //
    // Instruction Format EVX2_1 Insns
    //

    //
    // Instruction Format EVX2_2 Insns
    //
    [PPC32_IT_EVSTWHE_EVX2_2] = EMITOP " " EMITRS "," EMITUI "(" EMITRA ")",
    [PPC32_IT_EVSTWHO_EVX2_2] = EMITOP " " EMITRS "," EMITUI "(" EMITRA ")",
    [PPC32_IT_EVSTWWE_EVX2_2] = EMITOP " " EMITRS "," EMITUI "(" EMITRA ")",
    [PPC32_IT_EVSTWWO_EVX2_2] = EMITOP " " EMITRS "," EMITUI "(" EMITRA ")",

    //
    // Instruction Format EVX2_3 Insns
    //
    [PPC32_IT_EVSTDD_EVX2_3] = EMITOP " " EMITRS "," EMITUI "(" EMITRA ")",
    [PPC32_IT_EVSTDH_EVX2_3] = EMITOP " " EMITRS "," EMITUI "(" EMITRA ")",
    [PPC32_IT_EVSTDW_EVX2_3] = EMITOP " " EMITRS "," EMITUI "(" EMITRA ")",

    //
    // Instruction Format EVX3 Insns
    //
    [PPC32_IT_EFDCFS_EVX3]   = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EFDCFSF_EVX3]  = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EFDCFSI_EVX3]  = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EFDCFSID_EVX3] = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EFDCFUF_EVX3]  = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EFDCFUI_EVX3]  = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EFDCFUID_EVX3] = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EFDCTSF_EVX3]  = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EFDCTSI_EVX3]  = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EFDCTSIDZ_EVX3] = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EFDCTSIZ_EVX3] = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EFDCTUF_EVX3]  = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EFDCTUI_EVX3]  = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EFDCTUIDZ_EVX3] = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EFDCTUIZ_EVX3] = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EFSCFD_EVX3]   = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EFSCFSF_EVX3]  = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EFSCFSI_EVX3]  = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EFSCFUF_EVX3]  = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EFSCFUI_EVX3]  = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EFSCTSF_EVX3]  = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EFSCTSI_EVX3]  = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EFSCTSIZ_EVX3] = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EFSCTUF_EVX3]  = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EFSCTUI_EVX3]  = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EFSCTUIZ_EVX3] = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EVFSCFSF_EVX3] = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EVFSCFSI_EVX3] = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EVFSCFUF_EVX3] = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EVFSCFUI_EVX3] = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EVFSCTSF_EVX3] = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EVFSCTSI_EVX3] = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EVFSCTSIZ_EVX3] = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EVFSCTUF_EVX3] = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EVFSCTUI_EVX3] = EMITOP " " EMITRT "," EMITRB,
    [PPC32_IT_EVFSCTUIZ_EVX3] = EMITOP " " EMITRT "," EMITRB,

    //
    // Instruction Format EVX4 Insns
    //
    [PPC32_IT_EFDADD_EVX4]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EFDDIV_EVX4]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EFDMUL_EVX4]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EFDSUB_EVX4]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EFSADD_EVX4]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EFSDIV_EVX4]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EFSMUL_EVX4]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EFSSUB_EVX4]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVADDW_EVX4]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVAND_EVX4]    = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVANDC_EVX4]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVDIVWS_EVX4]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVDIVWU_EVX4]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVEQV_EVX4]    = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVFSADD_EVX4]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVFSDIV_EVX4]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVFSMUL_EVX4]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVFSSUB_EVX4]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVLDDX_EVX4]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVLDHX_EVX4]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVLDWX_EVX4]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVLHHESPLATX_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVLHHOSSPLATX_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVLHHOUSPLATX_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVLWHEX_EVX4]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVLWHOSX_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVLWHOUX_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVLWHSPLATX_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVLWWSPLATX_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMERGEHI_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMERGEHILO_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMERGELO_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMERGELOHI_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHEGSMFAA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHEGSMFAN_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHEGSMIAA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHEGSMIAN_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHEGUMIAA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHEGUMIAN_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHESMF_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHESMFA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHESMFAAW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHESMFANW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHESMI_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHESMIA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHESMIAAW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHESMIANW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHESSF_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHESSFA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHESSFAAW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHESSFANW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHESSIAAW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHESSIANW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHEUMI_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHEUMIA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHEUMIAAW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHEUMIANW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHEUSIAAW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHEUSIANW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOGSMFAA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOGSMFAN_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOGSMIAA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOGSMIAN_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOGUMIAA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOGUMIAN_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOSMF_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOSMFA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOSMFAAW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOSMFANW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOSMI_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOSMIA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOSMIAAW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOSMIANW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOSSF_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOSSFA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOSSFAAW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOSSFANW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOSSIAAW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOSSIANW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOUMI_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOUMIA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOUMIAAW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOUMIANW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOUSIAAW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMHOUSIANW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWHSMF_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWHSMFA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWHSMI_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWHSMIA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWHSSF_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWHSSFA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWHUMI_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWHUMIA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWLSMIAAW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWLSMIANW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWLSSIAAW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWLSSIANW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWLUMI_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWLUMIA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWLUMIAAW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWLUMIANW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWLUSIAAW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWLUSIANW_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWSMF_EVX4]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWSMFA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWSMFAA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWSMFAN_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWSMI_EVX4]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWSMIA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWSMIAA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWSMIAN_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWSSF_EVX4]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWSSFA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWSSFAA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWSSFAN_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWUMI_EVX4]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWUMIA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWUMIAA_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVMWUMIAN_EVX4] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVNAND_EVX4]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVNOR_EVX4]    = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVOR_EVX4]     = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVORC_EVX4]    = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVRLW_EVX4]    = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVSLW_EVX4]    = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVSRWS_EVX4]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVSRWU_EVX4]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVSUBFW_EVX4]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_EVXOR_EVX4]    = EMITOP " " EMITRT "," EMITRA "," EMITRB,

    //
    // Instruction Format EVX5 Insns
    //
    [PPC32_IT_EFDABS_EVX5]   = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_EFDNABS_EVX5]  = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_EFDNEG_EVX5]   = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_EFSABS_EVX5]   = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_EFSNABS_EVX5]  = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_EFSNEG_EVX5]   = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_EVABS_EVX5]    = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_EVADDSMIAAW_EVX5] = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_EVADDSSIAAW_EVX5] = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_EVADDUMIAAW_EVX5] = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_EVADDUSIAAW_EVX5] = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_EVCNTLSW_EVX5] = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_EVCNTLZW_EVX5] = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_EVEXTSB_EVX5]  = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_EVEXTSH_EVX5]  = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_EVFSABS_EVX5]  = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_EVFSNABS_EVX5] = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_EVFSNEG_EVX5]  = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_EVMRA_EVX5]    = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_EVNEG_EVX5]    = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_EVRNDW_EVX5]   = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_EVSUBFSMIAAW_EVX5] = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_EVSUBFSSIAAW_EVX5] = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_EVSUBFUMIAAW_EVX5] = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_EVSUBFUSIAAW_EVX5] = EMITOP " " EMITRT "," EMITRA,

    //
    // Instruction Format EVX6_1 Insns
    //
    [PPC32_IT_EVADDIW_EVX6_1] = EMITOP " " EMITRT "," EMITRB "," EMITUI,

    //
    // Instruction Format EVX6_2 Insns
    //
    [PPC32_IT_EVSUBIFW_EVX6_2] = EMITOP " " EMITRT "," EMITUI "," EMITRB,

    //
    // Instruction Format EVX7 Insns
    //
    [PPC32_IT_EFDCMPEQ_EVX7] = EMITOP " " EMITBF "," EMITRA "," EMITRB,
    [PPC32_IT_EFDCMPGT_EVX7] = EMITOP " " EMITBF "," EMITRA "," EMITRB,
    [PPC32_IT_EFDCMPLT_EVX7] = EMITOP " " EMITBF "," EMITRA "," EMITRB,
    [PPC32_IT_EFDTSTEQ_EVX7] = EMITOP " " EMITBF "," EMITRA "," EMITRB,
    [PPC32_IT_EFDTSTGT_EVX7] = EMITOP " " EMITBF "," EMITRA "," EMITRB,
    [PPC32_IT_EFDTSTLT_EVX7] = EMITOP " " EMITBF "," EMITRA "," EMITRB,
    [PPC32_IT_EFSCMPEQ_EVX7] = EMITOP " " EMITBF "," EMITRA "," EMITRB,
    [PPC32_IT_EFSCMPGT_EVX7] = EMITOP " " EMITBF "," EMITRA "," EMITRB,
    [PPC32_IT_EFSCMPLT_EVX7] = EMITOP " " EMITBF "," EMITRA "," EMITRB,
    [PPC32_IT_EFSTSTEQ_EVX7] = EMITOP " " EMITBF "," EMITRA "," EMITRB,
    [PPC32_IT_EFSTSTGT_EVX7] = EMITOP " " EMITBF "," EMITRA "," EMITRB,
    [PPC32_IT_EFSTSTLT_EVX7] = EMITOP " " EMITBF "," EMITRA "," EMITRB,
    [PPC32_IT_EVCMPEQ_EVX7]  = EMITOP " " EMITBF "," EMITRA "," EMITRB,
    [PPC32_IT_EVCMPGTS_EVX7] = EMITOP " " EMITBF "," EMITRA "," EMITRB,
    [PPC32_IT_EVCMPGTU_EVX7] = EMITOP " " EMITBF "," EMITRA "," EMITRB,
    [PPC32_IT_EVCMPLTS_EVX7] = EMITOP " " EMITBF "," EMITRA "," EMITRB,
    [PPC32_IT_EVCMPLTU_EVX7] = EMITOP " " EMITBF "," EMITRA "," EMITRB,
    [PPC32_IT_EVFSCMPEQ_EVX7] = EMITOP " " EMITBF "," EMITRA "," EMITRB,
    [PPC32_IT_EVFSCMPGT_EVX7] = EMITOP " " EMITBF "," EMITRA "," EMITRB,
    [PPC32_IT_EVFSCMPLT_EVX7] = EMITOP " " EMITBF "," EMITRA "," EMITRB,
    [PPC32_IT_EVFSTSTEQ_EVX7] = EMITOP " " EMITBF "," EMITRA "," EMITRB,
    [PPC32_IT_EVFSTSTGT_EVX7] = EMITOP " " EMITBF "," EMITRA "," EMITRB,
    [PPC32_IT_EVFSTSTLT_EVX7] = EMITOP " " EMITBF "," EMITRA "," EMITRB,

    //
    // Instruction Format EVX8 Insns
    //
    [PPC32_IT_EVRLWI_EVX8]   = EMITOP " " EMITRT "," EMITRA "," EMITUI,
    [PPC32_IT_EVSLWI_EVX8]   = EMITOP " " EMITRT "," EMITRA "," EMITUI,
    [PPC32_IT_EVSRWIS_EVX8]  = EMITOP " " EMITRT "," EMITRA "," EMITUI,
    [PPC32_IT_EVSRWIU_EVX8]  = EMITOP " " EMITRT "," EMITRA "," EMITUI,

    //
    // Instruction Format EVX8_1 Insns
    //
    [PPC32_IT_EVLHHESPLAT_EVX8_1] = EMITOP " " EMITRT "," EMITUI "(" EMITRA ")",
    [PPC32_IT_EVLHHOSSPLAT_EVX8_1] = EMITOP " " EMITRT "," EMITUI "(" EMITRA ")",
    [PPC32_IT_EVLHHOUSPLAT_EVX8_1] = EMITOP " " EMITRT "," EMITUI "(" EMITRA ")",

    //
    // Instruction Format EVX8_2 Insns
    //
    [PPC32_IT_EVLWHE_EVX8_2] = EMITOP " " EMITRT "," EMITUI "(" EMITRA ")",
    [PPC32_IT_EVLWHOS_EVX8_2] = EMITOP " " EMITRT "," EMITUI "(" EMITRA ")",
    [PPC32_IT_EVLWHOU_EVX8_2] = EMITOP " " EMITRT "," EMITUI "(" EMITRA ")",
    [PPC32_IT_EVLWHSPLAT_EVX8_2] = EMITOP " " EMITRT "," EMITUI "(" EMITRA ")",
    [PPC32_IT_EVLWWSPLAT_EVX8_2] = EMITOP " " EMITRT "," EMITUI "(" EMITRA ")",

    //
    // Instruction Format EVX8_3 Insns
    //
    [PPC32_IT_EVLDD_EVX8_3]  = EMITOP " " EMITRT "," EMITUI "(" EMITRA ")",
    [PPC32_IT_EVLDH_EVX8_3]  = EMITOP " " EMITRT "," EMITUI "(" EMITRA ")",
    [PPC32_IT_EVLDW_EVX8_3]  = EMITOP " " EMITRT "," EMITUI "(" EMITRA ")",

    //
    // Instruction Format EVX9 Insns
    //
    [PPC32_IT_EVSPLATFI_EVX9] = EMITOP " " EMITRT "," EMITSI,
    [PPC32_IT_EVSPLATI_EVX9] = EMITOP " " EMITRT "," EMITSI,

    //
    // Instruction Format I1 Insns
    //
    [PPC32_IT_B_I1]          = EMITOP EMITAALK " " EMITLI,

    //
    // Instruction Format I16A1 Insns
    //
    [PPC32_IT_E_ADD2IRC_I16A1] = EMITOP " " EMITRA "," EMITSI,
    [PPC32_IT_E_ADD2IS_I16A1] = EMITOP " " EMITRA "," EMITSI,
    [PPC32_IT_E_CMP16I_I16A1] = EMITOP " " EMITRA "," EMITSI,
    [PPC32_IT_E_CMPH16I_I16A1] = EMITOP " " EMITRA "," EMITSI,
    [PPC32_IT_E_MULL2I_I16A1] = EMITOP " " EMITRA "," EMITSI,

    //
    // Instruction Format I16A2 Insns
    //
    [PPC32_IT_E_CMPHL16I_I16A2] = EMITOP " " EMITRA "," EMITUI,
    [PPC32_IT_E_CMPL16I_I16A2] = EMITOP " " EMITRA "," EMITUI,

    //
    // Instruction Format I16L Insns
    //
    [PPC32_IT_E_AND2IRC_I16L] = EMITOP " " EMITRT "," EMITUI,
    [PPC32_IT_E_AND2ISRC_I16L] = EMITOP " " EMITRT "," EMITUI,
    [PPC32_IT_E_LIS_I16L]    = EMITOP " " EMITRT "," EMITUI,
    [PPC32_IT_E_OR2I_I16L]   = EMITOP " " EMITRT "," EMITUI,
    [PPC32_IT_E_OR2IS_I16L]  = EMITOP " " EMITRT "," EMITUI,

    //
    // Instruction Format IM5 Insns
    //
    [PPC32_IT_SE_ANDI_IM5]   = EMITOP " " EMITRX "," EMITUI5,
    [PPC32_IT_SE_BMASKI_IM5] = EMITOP " " EMITRX "," EMITUI5,
    [PPC32_IT_SE_CMPI_IM5]   = EMITOP " " EMITRX "," EMITUI5,

    //
    // Instruction Format IM7 Insns
    //
    [PPC32_IT_SE_LI_IM7]     = EMITOP " " EMITRX "," EMITUI7,

    //
    // Instruction Format LI20 Insns
    //
    [PPC32_IT_E_LI_LI20]     = EMITOP " " EMITRT "," EMITLI20,

    //
    // Instruction Format M1_0 Insns
    //
    [PPC32_IT_RLWNM_M1_0]    = EMITOP " " EMITRA "," EMITRS "," EMITRB "," EMITMB "," EMITME,
    [PPC32_IT_RLWNMRC_M1_0]  = EMITOP " " EMITRA "," EMITRS "," EMITRB "," EMITMB "," EMITME,

    //
    // Instruction Format M1_1 Insns
    //
    [PPC32_IT_RLWNMRC_0_M1_1] = EMITOP " " EMITRA "," EMITRS "," EMITRB,
    [PPC32_IT_RLWNM_0_M1_1]  = EMITOP " " EMITRA "," EMITRS "," EMITRB,

    //
    // Instruction Format M2_0 Insns
    //
    [PPC32_IT_E_RLWIMI_M2_0] = EMITOP " " EMITRA "," EMITRS "," EMITSH "," EMITMB "," EMITME,
    [PPC32_IT_E_RLWINM_M2_0] = EMITOP " " EMITRA "," EMITRS "," EMITSH "," EMITMB "," EMITME,
    [PPC32_IT_RLWIMI_M2_0]   = EMITOP " " EMITRA "," EMITRS "," EMITSH "," EMITMB "," EMITME,
    [PPC32_IT_RLWIMIRC_M2_0] = EMITOP " " EMITRA "," EMITRS "," EMITSH "," EMITMB "," EMITME,
    [PPC32_IT_RLWINM_M2_0]   = EMITOP " " EMITRA "," EMITRS "," EMITSH "," EMITMB "," EMITME,
    [PPC32_IT_RLWINMRC_M2_0] = EMITOP " " EMITRA "," EMITRS "," EMITSH "," EMITMB "," EMITME,

    //
    // Instruction Format M2_1 Insns
    //
    [PPC32_IT_RLWINMRC_0_M2_1] = EMITOP " " EMITRA "," EMITRS "," EMITSH,
    [PPC32_IT_RLWINM_0_M2_1] = EMITOP " " EMITRA "," EMITRS "," EMITSH,

    //
    // Instruction Format OIM51_0 Insns
    //
    [PPC32_IT_SE_BCLRI_OIM51_0] = EMITOP " " EMITRX "," EMITOIM5,
    [PPC32_IT_SE_BGENI_OIM51_0] = EMITOP " " EMITRX "," EMITOIM5,
    [PPC32_IT_SE_BSETI_OIM51_0] = EMITOP " " EMITRX "," EMITOIM5,
    [PPC32_IT_SE_BTSTI_OIM51_0] = EMITOP " " EMITRX "," EMITOIM5,
    [PPC32_IT_SE_SLWI_OIM51_0] = EMITOP " " EMITRX "," EMITOIM5,
    [PPC32_IT_SE_SRAWI_OIM51_0] = EMITOP " " EMITRX "," EMITOIM5,
    [PPC32_IT_SE_SRWI_OIM51_0] = EMITOP " " EMITRX "," EMITOIM5,

    //
    // Instruction Format OIM51_1 Insns
    //
    [PPC32_IT_SE_ADDI_OIM51_1] = EMITOP " " EMITRX "," EMITOIM5,
    [PPC32_IT_SE_CMPLI_OIM51_1] = EMITOP " " EMITRX "," EMITOIM5,

    //
    // Instruction Format OIM52_0 Insns
    //
    [PPC32_IT_SE_SUBI_OIM52_0] = EMITOP " " EMITRX "," EMITOIM5,
    [PPC32_IT_SE_SUBIRC_OIM52_0] = EMITOP " " EMITRX "," EMITOIM5,

    //
    // Instruction Format R1 Insns
    //
    [PPC32_IT_SE_EXTSB_R1]   = EMITOP " " EMITRX,
    [PPC32_IT_SE_EXTSH_R1]   = EMITOP " " EMITRX,
    [PPC32_IT_SE_EXTZB_R1]   = EMITOP " " EMITRX,
    [PPC32_IT_SE_EXTZH_R1]   = EMITOP " " EMITRX,
    [PPC32_IT_SE_MFCTR_R1]   = EMITOP " " EMITRX,
    [PPC32_IT_SE_MFLR_R1]    = EMITOP " " EMITRX,
    [PPC32_IT_SE_MTCTR_R1]   = EMITOP " " EMITRX,
    [PPC32_IT_SE_MTLR_R1]    = EMITOP " " EMITRX,
    [PPC32_IT_SE_NEG_R1]     = EMITOP " " EMITRX,
    [PPC32_IT_SE_NOT_R1]     = EMITOP " " EMITRX,

    //
    // Instruction Format RR1 Insns
    //
    [PPC32_IT_SE_ADD_RR1]    = EMITOP " " EMITRX  "," EMITRY,
    [PPC32_IT_SE_ANDC_RR1]   = EMITOP " " EMITRX  "," EMITRY,
    [PPC32_IT_SE_CMP_RR1]    = EMITOP " " EMITRX  "," EMITRY,
    [PPC32_IT_SE_CMPH_RR1]   = EMITOP " " EMITRX  "," EMITRY,
    [PPC32_IT_SE_CMPHL_RR1]  = EMITOP " " EMITRX  "," EMITRY,
    [PPC32_IT_SE_CMPL_RR1]   = EMITOP " " EMITRX  "," EMITRY,
    [PPC32_IT_SE_MR_RR1]     = EMITOP " " EMITRX  "," EMITRY,
    [PPC32_IT_SE_MULLW_RR1]  = EMITOP " " EMITRX  "," EMITRY,
    [PPC32_IT_SE_OR_RR1]     = EMITOP " " EMITRX  "," EMITRY,
    [PPC32_IT_SE_SLW_RR1]    = EMITOP " " EMITRX  "," EMITRY,
    [PPC32_IT_SE_SRAW_RR1]   = EMITOP " " EMITRX  "," EMITRY,
    [PPC32_IT_SE_SRW_RR1]    = EMITOP " " EMITRX  "," EMITRY,
    [PPC32_IT_SE_SUB_RR1]    = EMITOP " " EMITRX  "," EMITRY,
    [PPC32_IT_SE_SUBF_RR1]   = EMITOP " " EMITRX  "," EMITRY,

    //
    // Instruction Format RR2 Insns
    //
    [PPC32_IT_SE_AND_RR2]    = EMITOP " " EMITRX  "," EMITRY,
    [PPC32_IT_SE_ANDRC_RR2]  = EMITOP " " EMITRX  "," EMITRY,

    //
    // Instruction Format RR3 Insns
    //
    [PPC32_IT_SE_MFAR_RR3]   = EMITOP " " EMITRX  "," EMITARY,

    //
    // Instruction Format RR4 Insns
    //
    [PPC32_IT_SE_MTAR_RR4]   = EMITOP " " EMITARX "," EMITRY,

    //
    // Instruction Format SC1 Insns
    //
    [PPC32_IT_SC_SC1]        = EMITOP " " EMITLEV,

    //
    // Instruction Format SCI8_1 Insns
    //
    [PPC32_IT_E_ADDI_SCI8_1] = EMITOP " " EMITRT   "," EMITRA "," EMITU8,
    [PPC32_IT_E_ADDIC_SCI8_1] = EMITOP " " EMITRT   "," EMITRA "," EMITU8,
    [PPC32_IT_E_ADDICRC_SCI8_1] = EMITOP " " EMITRT   "," EMITRA "," EMITU8,
    [PPC32_IT_E_ADDIRC_SCI8_1] = EMITOP " " EMITRT   "," EMITRA "," EMITU8,
    [PPC32_IT_E_SUBFIC_SCI8_1] = EMITOP " " EMITRT   "," EMITRA "," EMITU8,
    [PPC32_IT_E_SUBFICRC_SCI8_1] = EMITOP " " EMITRT   "," EMITRA "," EMITU8,

    //
    // Instruction Format SCI8_2 Insns
    //
    [PPC32_IT_E_MULLI_SCI8_2] = EMITOP " " EMITRT   "," EMITRA "," EMITU8,

    //
    // Instruction Format SCI8_3 Insns
    //
    [PPC32_IT_E_ANDI_SCI8_3] = EMITOP " " EMITRA   "," EMITRS "," EMITU8,
    [PPC32_IT_E_ANDIRC_SCI8_3] = EMITOP " " EMITRA   "," EMITRS "," EMITU8,
    [PPC32_IT_E_ORI_SCI8_3]  = EMITOP " " EMITRA   "," EMITRS "," EMITU8,
    [PPC32_IT_E_ORIRC_SCI8_3] = EMITOP " " EMITRA   "," EMITRS "," EMITU8,
    [PPC32_IT_E_XORI_SCI8_3] = EMITOP " " EMITRA   "," EMITRS "," EMITU8,
    [PPC32_IT_E_XORIRC_SCI8_3] = EMITOP " " EMITRA   "," EMITRS "," EMITU8,

    //
    // Instruction Format SCI8_5 Insns
    //
    [PPC32_IT_E_CMPI_SCI8_5] = EMITOP " " EMITBF32 "," EMITRA "," EMITS8,

    //
    // Instruction Format SCI8_6 Insns
    //
    [PPC32_IT_E_CMPLI_SCI8_6] = EMITOP " " EMITBF32 "," EMITRA "," EMITS8,

    //
    // Instruction Format SD4_0 Insns
    //
    [PPC32_IT_SE_LBZ_SD4_0]  = EMITOP " " EMITRZ  "," EMITSD4 "(" EMITRX ")",
    [PPC32_IT_SE_STB_SD4_0]  = EMITOP " " EMITRZ  "," EMITSD4 "(" EMITRX ")",

    //
    // Instruction Format SD4_1 Insns
    //
    [PPC32_IT_SE_LHZ_SD4_1]  = EMITOP " " EMITRZ  "," EMITSD4 "(" EMITRX ")",
    [PPC32_IT_SE_STH_SD4_1]  = EMITOP " " EMITRZ  "," EMITSD4 "(" EMITRX ")",

    //
    // Instruction Format SD4_2 Insns
    //
    [PPC32_IT_SE_LWZ_SD4_2]  = EMITOP " " EMITRZ  "," EMITSD4 "(" EMITRX ")",
    [PPC32_IT_SE_STW_SD4_2]  = EMITOP " " EMITRZ  "," EMITSD4 "(" EMITRX ")",

    //
    // Instruction Format VA1_0 Insns
    //
    [PPC32_IT_VMHADDSHS_VA1_0] = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB "," EMITVRC,
    [PPC32_IT_VMHRADDSHS_VA1_0] = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB "," EMITVRC,
    [PPC32_IT_VMLADDUHM_VA1_0] = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB "," EMITVRC,
    [PPC32_IT_VMSUMMBM_VA1_0] = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB "," EMITVRC,
    [PPC32_IT_VMSUMSHM_VA1_0] = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB "," EMITVRC,
    [PPC32_IT_VMSUMSHS_VA1_0] = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB "," EMITVRC,
    [PPC32_IT_VMSUMUBM_VA1_0] = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB "," EMITVRC,
    [PPC32_IT_VMSUMUHM_VA1_0] = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB "," EMITVRC,
    [PPC32_IT_VMSUMUHS_VA1_0] = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB "," EMITVRC,
    [PPC32_IT_VPERM_VA1_0]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB "," EMITVRC,
    [PPC32_IT_VSEL_VA1_0]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB "," EMITVRC,

    //
    // Instruction Format VA1_1 Insns
    //
    [PPC32_IT_VMADDFP_VA1_1] = EMITOP " " EMITVRT "," EMITVRA "," EMITVRC "," EMITVRB,
    [PPC32_IT_VMSUBFP_VA1_1] = EMITOP " " EMITVRT "," EMITVRA "," EMITVRC "," EMITVRB,

    //
    // Instruction Format VA2 Insns
    //
    [PPC32_IT_VSLDOI_VA2]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB "," EMITSHB,

    //
    // Instruction Format VC1 Insns
    //
    [PPC32_IT_VCMPBFP_VC1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VCMPBFPRC_VC1] = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VCMPEQFP_VC1]  = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VCMPEQFPRC_VC1] = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VCMPEQUB_VC1]  = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VCMPEQUBRC_VC1] = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VCMPEQUH_VC1]  = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VCMPEQUHRC_VC1] = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VCMPEQUW_VC1]  = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VCMPEQUWRC_VC1] = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VCMPGEFP_VC1]  = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VCMPGEFPRC_VC1] = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VCMPGTFP_VC1]  = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VCMPGTFPRC_VC1] = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VCMPGTSB_VC1]  = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VCMPGTSBRC_VC1] = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VCMPGTSH_VC1]  = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VCMPGTSHRC_VC1] = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VCMPGTSW_VC1]  = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VCMPGTSWRC_VC1] = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VCMPGTUB_VC1]  = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VCMPGTUBRC_VC1] = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VCMPGTUH_VC1]  = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VCMPGTUHRC_VC1] = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VCMPGTUW_VC1]  = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VCMPGTUWRC_VC1] = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,

    //
    // Instruction Format VX1 Insns
    //
    [PPC32_IT_VADDCUW_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VADDFP_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VADDSBS_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VADDSHS_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VADDSWS_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VADDUBM_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VADDUBS_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VADDUHM_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VADDUHS_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VADDUWM_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VADDUWS_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VAND_VX1]      = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VANDC_VX1]     = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VAVGSB_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VAVGSH_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VAVGSW_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VAVGUB_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VAVGUH_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VAVGUW_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VKPPX_VX1]     = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VKPSHSS_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VKPSHUS_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VKPSWSS_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VKPSWUS_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VKPUHUM_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VKPUHUS_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VKPUWUM_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VKPUWUS_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMAXFP_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMAXSB_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMAXSH_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMAXSW_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMAXUB_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMAXUH_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMAXUW_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMINFP_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMINSB_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMINSH_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMINSW_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMINUB_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMINUH_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMINUW_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMRGHB_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMRGHH_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMRGHW_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMRGLB_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMRGLH_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMRGLW_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMULESB_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMULESH_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMULEUB_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMULEUH_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMULOSB_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMULOSH_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMULOUB_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VMULOUH_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VNOR_VX1]      = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VOR_VX1]       = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VRLB_VX1]      = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VRLH_VX1]      = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VRLW_VX1]      = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSL_VX1]       = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSLB_VX1]      = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSLH_VX1]      = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSLO_VX1]      = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSLW_VX1]      = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSR_VX1]       = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSRAB_VX1]     = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSRAH_VX1]     = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSRAW_VX1]     = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSRB_VX1]      = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSRH_VX1]      = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSRO_VX1]      = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSRW_VX1]      = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSUBCUW_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSUBFP_VX1]    = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSUBSBS_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSUBSHS_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSUBSWS_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSUBUBM_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSUBUBS_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSUBUHM_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSUBUHS_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSUBUWM_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSUBUWS_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSUM2SWS_VX1]  = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSUM4SBS_VX1]  = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSUM4SHS_VX1]  = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSUM4UBS_VX1]  = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VSUMSWS_VX1]   = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,
    [PPC32_IT_VXOR_VX1]      = EMITOP " " EMITVRT "," EMITVRA "," EMITVRB,

    //
    // Instruction Format VX2 Insns
    //
    [PPC32_IT_VEXPTEFP_VX2]  = EMITOP " " EMITVRT "," EMITVRB,
    [PPC32_IT_VLOGEFP_VX2]   = EMITOP " " EMITVRT "," EMITVRB,
    [PPC32_IT_VREFP_VX2]     = EMITOP " " EMITVRT "," EMITVRB,
    [PPC32_IT_VRFIM_VX2]     = EMITOP " " EMITVRT "," EMITVRB,
    [PPC32_IT_VRFIN_VX2]     = EMITOP " " EMITVRT "," EMITVRB,
    [PPC32_IT_VRFIP_VX2]     = EMITOP " " EMITVRT "," EMITVRB,
    [PPC32_IT_VRFIZ_VX2]     = EMITOP " " EMITVRT "," EMITVRB,
    [PPC32_IT_VRSQRTEFP_VX2] = EMITOP " " EMITVRT "," EMITVRB,
    [PPC32_IT_VUPKHPX_VX2]   = EMITOP " " EMITVRT "," EMITVRB,
    [PPC32_IT_VUPKHSB_VX2]   = EMITOP " " EMITVRT "," EMITVRB,
    [PPC32_IT_VUPKHSH_VX2]   = EMITOP " " EMITVRT "," EMITVRB,
    [PPC32_IT_VUPKLPX_VX2]   = EMITOP " " EMITVRT "," EMITVRB,
    [PPC32_IT_VUPKLSB_VX2]   = EMITOP " " EMITVRT "," EMITVRB,
    [PPC32_IT_VUPKLSH_VX2]   = EMITOP " " EMITVRT "," EMITVRB,

    //
    // Instruction Format VX3 Insns
    //
    [PPC32_IT_VCFSX_VX3]     = EMITOP " " EMITVRT "," EMITVRB "," EMITUIM,
    [PPC32_IT_VCFUX_VX3]     = EMITOP " " EMITVRT "," EMITVRB "," EMITUIM,
    [PPC32_IT_VCTSXS_VX3]    = EMITOP " " EMITVRT "," EMITVRB "," EMITUIM,
    [PPC32_IT_VCTUXS_VX3]    = EMITOP " " EMITVRT "," EMITVRB "," EMITUIM,

    //
    // Instruction Format VX4 Insns
    //
    [PPC32_IT_VSPLTB_VX4]    = EMITOP " " EMITVRT "," EMITVRB "," EMITUIM,

    //
    // Instruction Format VX5 Insns
    //
    [PPC32_IT_VSPLTH_VX5]    = EMITOP " " EMITVRT "," EMITVRB "," EMITUIM,

    //
    // Instruction Format VX6 Insns
    //
    [PPC32_IT_VSPLTW_VX6]    = EMITOP " " EMITVRT "," EMITVRB "," EMITUIM,

    //
    // Instruction Format VX7 Insns
    //
    [PPC32_IT_VSPLTISB_VX7]  = EMITOP " " EMITVRT "," EMITSIM,
    [PPC32_IT_VSPLTISH_VX7]  = EMITOP " " EMITVRT "," EMITSIM,
    [PPC32_IT_VSPLTISW_VX7]  = EMITOP " " EMITVRT "," EMITSIM,

    //
    // Instruction Format VX8 Insns
    //
    [PPC32_IT_MFVSCR_VX8]    = EMITOP " " EMITVRT,

    //
    // Instruction Format VX9 Insns
    //
    [PPC32_IT_MTVSCR_VX9]    = EMITOP " " EMITVRB,

    //
    // Instruction Format X1 Insns
    //
    [PPC32_IT_MFAPIDI_X1]    = EMITOP " " EMITRT    "," EMITRA,
    [PPC32_IT_MFDCRUX_X1]    = EMITOP " " EMITRT    "," EMITRA,
    [PPC32_IT_MFDCRX_X1]     = EMITOP " " EMITRT    "," EMITRA,

    //
    // Instruction Format X10 Insns
    //
    [PPC32_IT_MULCHW_X10]    = EMITOP " " EMITRT    "," EMITRA    "," EMITRB,
    [PPC32_IT_MULCHWRC_X10]  = EMITOP " " EMITRT    "," EMITRA    "," EMITRB,
    [PPC32_IT_MULCHWU_X10]   = EMITOP " " EMITRT    "," EMITRA    "," EMITRB,
    [PPC32_IT_MULCHWURC_X10] = EMITOP " " EMITRT    "," EMITRA    "," EMITRB,
    [PPC32_IT_MULHHW_X10]    = EMITOP " " EMITRT    "," EMITRA    "," EMITRB,
    [PPC32_IT_MULHHWRC_X10]  = EMITOP " " EMITRT    "," EMITRA    "," EMITRB,
    [PPC32_IT_MULHHWU_X10]   = EMITOP " " EMITRT    "," EMITRA    "," EMITRB,
    [PPC32_IT_MULHHWURC_X10] = EMITOP " " EMITRT    "," EMITRA    "," EMITRB,
    [PPC32_IT_MULLHW_X10]    = EMITOP " " EMITRT    "," EMITRA    "," EMITRB,
    [PPC32_IT_MULLHWRC_X10]  = EMITOP " " EMITRT    "," EMITRA    "," EMITRB,
    [PPC32_IT_MULLHWU_X10]   = EMITOP " " EMITRT    "," EMITRA    "," EMITRB,
    [PPC32_IT_MULLHWURC_X10] = EMITOP " " EMITRT    "," EMITRA    "," EMITRB,

    //
    // Instruction Format X11 Insns
    //
    [PPC32_IT_STWCXRC_X11]   = EMITOP " " EMITRS    "," EMITRA_AL "," EMITRB,

    //
    // Instruction Format X12 Insns
    //
    [PPC32_IT_CMPB_X12]      = EMITOP " " EMITRS    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STBCIX_X12]    = EMITOP " " EMITRS    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STBEPX_X12]    = EMITOP " " EMITRS    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STBUX_X12]     = EMITOP " " EMITRS    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STBX_X12]      = EMITOP " " EMITRS    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STDCIX_X12]    = EMITOP " " EMITRS    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STDEPX_X12]    = EMITOP " " EMITRS    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STHBRX_X12]    = EMITOP " " EMITRS    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STHCIX_X12]    = EMITOP " " EMITRS    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STHEPX_X12]    = EMITOP " " EMITRS    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STHUX_X12]     = EMITOP " " EMITRS    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STHX_X12]      = EMITOP " " EMITRS    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STSWX_X12]     = EMITOP " " EMITRS    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STWBRX_X12]    = EMITOP " " EMITRS    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STWCIX_X12]    = EMITOP " " EMITRS    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STWEPX_X12]    = EMITOP " " EMITRS    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STWUX_X12]     = EMITOP " " EMITRS    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STWX_X12]      = EMITOP " " EMITRS    "," EMITRA_AL "," EMITRB,

    //
    // Instruction Format X13 Insns
    //
    [PPC32_IT_STSWI_X13]     = EMITOP " " EMITRS    "," EMITRA_AL "," EMITNB,

    //
    // Instruction Format X14 Insns
    //
    [PPC32_IT_E_RLWI_X14]    = EMITOP " " EMITRA    "," EMITRS    "," EMITSH,
    [PPC32_IT_E_RLWIRC_X14]  = EMITOP " " EMITRA    "," EMITRS    "," EMITSH,
    [PPC32_IT_E_SLWI_X14]    = EMITOP " " EMITRA    "," EMITRS    "," EMITSH,
    [PPC32_IT_E_SLWIRC_X14]  = EMITOP " " EMITRA    "," EMITRS    "," EMITSH,
    [PPC32_IT_E_SRWI_X14]    = EMITOP " " EMITRA    "," EMITRS    "," EMITSH,
    [PPC32_IT_E_SRWIRC_X14]  = EMITOP " " EMITRA    "," EMITRS    "," EMITSH,
    [PPC32_IT_SRAWI_X14]     = EMITOP " " EMITRA    "," EMITRS    "," EMITSH,
    [PPC32_IT_SRAWIRC_X14]   = EMITOP " " EMITRA    "," EMITRS    "," EMITSH,

    //
    // Instruction Format X15 Insns
    //
    [PPC32_IT_CNTLZW_X15]    = EMITOP " " EMITRA    "," EMITRS,
    [PPC32_IT_CNTLZWRC_X15]  = EMITOP " " EMITRA    "," EMITRS,
    [PPC32_IT_EXTSB_X15]     = EMITOP " " EMITRA    "," EMITRS,
    [PPC32_IT_EXTSBRC_X15]   = EMITOP " " EMITRA    "," EMITRS,
    [PPC32_IT_EXTSH_X15]     = EMITOP " " EMITRA    "," EMITRS,
    [PPC32_IT_EXTSHRC_X15]   = EMITOP " " EMITRA    "," EMITRS,

    //
    // Instruction Format X16 Insns
    //
    [PPC32_IT_CBCDTD_X16]    = EMITOP " " EMITRA    "," EMITRS,
    [PPC32_IT_CDTBCD_X16]    = EMITOP " " EMITRA    "," EMITRS,
    [PPC32_IT_MTDCRUX_X16]   = EMITOP " " EMITRA    "," EMITRS,
    [PPC32_IT_MTDCRX_X16]    = EMITOP " " EMITRA    "," EMITRS,
    [PPC32_IT_POPCNTB_X16]   = EMITOP " " EMITRA    "," EMITRS,
    [PPC32_IT_PRTYW_X16]     = EMITOP " " EMITRA    "," EMITRS,

    //
    // Instruction Format X17 Insns
    //
    [PPC32_IT_MTSR_X17]      = EMITOP " " EMITSR    "," EMITRS,

    //
    // Instruction Format X18 Insns
    //
    [PPC32_IT_MTSRIN_X18]    = EMITOP " " EMITRS    "," EMITRB,
    [PPC32_IT_SLBMTE_X18]    = EMITOP " " EMITRS    "," EMITRB,

    //
    // Instruction Format X19_0 Insns
    //
    [PPC32_IT_MTMSR_X19_0]   = EMITOP " " EMITRS,

    //
    // Instruction Format X19_1 Insns
    //
    [PPC32_IT_WRTEE_X19_1]   = EMITOP " " EMITRS,

    //
    // Instruction Format X2 Insns
    //
    [PPC32_IT_DCREAD_X2]     = EMITOP " " EMITRT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_ECIWX_X2]      = EMITOP " " EMITRT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_ECOWX_X2]      = EMITOP " " EMITRT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LBEPX_X2]      = EMITOP " " EMITRT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LBZCIX_X2]     = EMITOP " " EMITRT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LBZUX_X2]      = EMITOP " " EMITRT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LBZX_X2]       = EMITOP " " EMITRT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LDCIX_X2]      = EMITOP " " EMITRT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LDEPX_X2]      = EMITOP " " EMITRT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LHAUX_X2]      = EMITOP " " EMITRT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LHAX_X2]       = EMITOP " " EMITRT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LHBRX_X2]      = EMITOP " " EMITRT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LHEPX_X2]      = EMITOP " " EMITRT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LHZCIX_X2]     = EMITOP " " EMITRT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LHZUX_X2]      = EMITOP " " EMITRT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LHZX_X2]       = EMITOP " " EMITRT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LSWX_X2]       = EMITOP " " EMITRT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LWBRX_X2]      = EMITOP " " EMITRT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LWEPX_X2]      = EMITOP " " EMITRT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LWZCIX_X2]     = EMITOP " " EMITRT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LWZUX_X2]      = EMITOP " " EMITRT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LWZX_X2]       = EMITOP " " EMITRT    "," EMITRA_AL "," EMITRB,

    //
    // Instruction Format X20 Insns
    //
    [PPC32_IT_MTMSRD_X20]    = EMITOP " " EMITRS,

    //
    // Instruction Format X22_0 Insns
    //
    [PPC32_IT_CMPLW_X22_0]   = EMITOP " " EMITBF    ","   EMITRA  "," EMITRB,
    [PPC32_IT_CMPW_X22_0]    = EMITOP " " EMITBF    ","   EMITRA  "," EMITRB,

    //
    // Instruction Format X22_1 Insns
    //
    [PPC32_IT_CMP_X22_1]     = EMITOP " " EMITBF    ",1," EMITRA  "," EMITRB,
    [PPC32_IT_CMPL_X22_1]    = EMITOP " " EMITBF    ",1," EMITRA  "," EMITRB,

    //
    // Instruction Format X22_2 Insns
    //
    [PPC32_IT_E_CMPH_X22_2]  = EMITOP " " EMITBF    ","   EMITRA  "," EMITRB,
    [PPC32_IT_E_CMPHL_X22_2] = EMITOP " " EMITBF    ","   EMITRA  "," EMITRB,

    //
    // Instruction Format X23 Insns
    //
    [PPC32_IT_DCMPO_X23]     = EMITOP " " EMITBF    "," EMITFRA   "," EMITFRB,
    [PPC32_IT_DCMPU_X23]     = EMITOP " " EMITBF    "," EMITFRA   "," EMITFRB,
    [PPC32_IT_DTSTEX_X23]    = EMITOP " " EMITBF    "," EMITFRA   "," EMITFRB,
    [PPC32_IT_DTSTSF_X23]    = EMITOP " " EMITBF    "," EMITFRA   "," EMITFRB,
    [PPC32_IT_FCMPO_X23]     = EMITOP " " EMITBF    "," EMITFRA   "," EMITFRB,
    [PPC32_IT_FCMPU_X23]     = EMITOP " " EMITBF    "," EMITFRA   "," EMITFRB,

    //
    // Instruction Format X24 Insns
    //
    [PPC32_IT_MCRFS_X24]     = EMITOP " " EMITBF    "," EMITBFA,

    //
    // Instruction Format X25_0 Insns
    //
    [PPC32_IT_MTFSFIZ_X25_0] = EMITOP " " EMITBFU   "," EMITU,
    [PPC32_IT_MTFSFIZRC_X25_0] = EMITOP " " EMITBFU   "," EMITU,

    //
    // Instruction Format X25_1 Insns
    //
    [PPC32_IT_MTFSFI_X25_1]  = EMITOP " " EMITBFU   "," EMITU ",1" ,
    [PPC32_IT_MTFSFIRC_X25_1] = EMITOP " " EMITBFU   "," EMITU ",1" ,

    //
    // Instruction Format X26 Insns
    //
    [PPC32_IT_MCRXR_X26]     = EMITOP " " EMITBF,

    //
    // Instruction Format X27_0 Insns
    //
    [PPC32_IT_DCBT_X27_0]    = EMITOP " " EMITRA_AL "," EMITRB    "," EMITTH,
    [PPC32_IT_DCBTST_X27_0]  = EMITOP " " EMITRA_AL "," EMITRB    "," EMITTH,

    //
    // Instruction Format X27_1 Insns
    //
    [PPC32_IT_DCBTST_1_X27_1] = EMITOP " " EMITRA_AL "," EMITRB,
    [PPC32_IT_DCBT_1_X27_1]  = EMITOP " " EMITRA_AL "," EMITRB,

    //
    // Instruction Format X27_2 Insns
    //
    [PPC32_IT_DCBTEP_X27_2]  = EMITOP " " "r" EMITTH    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_DCBTSTEP_X27_2] = EMITOP " " "r" EMITTH    "," EMITRA_AL "," EMITRB,

    //
    // Instruction Format X28_0 Insns
    //
    [PPC32_IT_DCI_0_X28_0]   = EMITOP,
    [PPC32_IT_ICI_0_X28_0]   = EMITOP,

    //
    // Instruction Format X28_1 Insns
    //
    [PPC32_IT_DCI_X28_1]     = EMITOP " " EMITCT,
    [PPC32_IT_ICI_X28_1]     = EMITOP " " EMITCT,

    //
    // Instruction Format X29_0 Insns
    //
    [PPC32_IT_DCBLC_0_X29_0] = EMITOP " " EMITRA_AL "," EMITRB,
    [PPC32_IT_DCBTLS_0_X29_0] = EMITOP " " EMITRA_AL "," EMITRB,
    [PPC32_IT_DCBTSTLS_0_X29_0] = EMITOP " " EMITRA_AL "," EMITRB,
    [PPC32_IT_ICBLC_0_X29_0] = EMITOP " " EMITRA_AL "," EMITRB,
    [PPC32_IT_ICBTLS_0_X29_0] = EMITOP " " EMITRA_AL "," EMITRB,
    [PPC32_IT_ICBT_CT0_X29_0] = EMITOP " " EMITRA_AL "," EMITRB,

    //
    // Instruction Format X29_1 Insns
    //
    [PPC32_IT_DCBLC_1_X29_1] = EMITOP " " EMITCT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_DCBTLS_1_X29_1] = EMITOP " " EMITCT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_DCBTSTLS_1_X29_1] = EMITOP " " EMITCT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_ICBLC_1_X29_1] = EMITOP " " EMITCT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_ICBT_X29_1]    = EMITOP " " EMITCT    "," EMITRA_AL "," EMITRB,
    [PPC32_IT_ICBTLS_1_X29_1] = EMITOP " " EMITCT    "," EMITRA_AL "," EMITRB,

    //
    // Instruction Format X3 Insns
    //
    [PPC32_IT_LWARX_X3]      = EMITOP " " EMITRT    "," EMITRA_AL "," EMITRB EMITEH,

    //
    // Instruction Format X30 Insns
    //
    [PPC32_IT_DCBF_X30]      = EMITOP " " EMITRA_AL "," EMITRB,
    [PPC32_IT_DCBF_L_X30]    = EMITOP " " EMITRA_AL "," EMITRB,
    [PPC32_IT_DCBF_LP_X30]   = EMITOP " " EMITRA_AL "," EMITRB,

    //
    // Instruction Format X31_0 Insns
    //
    [PPC32_IT_TLBIEL_0_X31_0] = EMITOP " " EMITRB,
    [PPC32_IT_TLBIE_0_X31_0] = EMITOP " " EMITRB,

    //
    // Instruction Format X31_1 Insns
    //
    [PPC32_IT_TLBIEL_1_X31_1] = EMITOP " " EMITRB ",1",
    [PPC32_IT_TLBIE_1_X31_1] = EMITOP " " EMITRB ",1",

    //
    // Instruction Format X32 Insns
    //
    [PPC32_IT_LWSYNC_X32]    = EMITOP,
    [PPC32_IT_PTESYNC_X32]   = EMITOP,
    [PPC32_IT_SYNC_X32]      = EMITOP,

    //
    // Instruction Format X33 Insns
    //
    [PPC32_IT_TW_X33]        = EMITOP " " EMITTO    "," EMITRA    "," EMITRB,

    //
    // Instruction Format X34 Insns
    //
    [PPC32_IT_LFDEPX_X34]    = EMITOP " " EMITFRT   "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LFDUX_X34]     = EMITOP " " EMITFRT   "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LFDX_X34]      = EMITOP " " EMITFRT   "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LFIWAX_X34]    = EMITOP " " EMITFRT   "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LFSUX_X34]     = EMITOP " " EMITFRT   "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LFSX_X34]      = EMITOP " " EMITFRT   "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STFDEPX_X34]   = EMITOP " " EMITFRT   "," EMITRA_AL "," EMITRB,

    //
    // Instruction Format X35RC Insns
    //
    [PPC32_IT_DADD_X35RC]    = EMITOP " " EMITFRT   "," EMITFRA   "," EMITFRB,
    [PPC32_IT_DADDRC_X35RC]  = EMITOP " " EMITFRT   "," EMITFRA   "," EMITFRB,
    [PPC32_IT_DDIV_X35RC]    = EMITOP " " EMITFRT   "," EMITFRA   "," EMITFRB,
    [PPC32_IT_DDIVRC_X35RC]  = EMITOP " " EMITFRT   "," EMITFRA   "," EMITFRB,
    [PPC32_IT_DIEX_X35RC]    = EMITOP " " EMITFRT   "," EMITFRA   "," EMITFRB,
    [PPC32_IT_DIEXRC_X35RC]  = EMITOP " " EMITFRT   "," EMITFRA   "," EMITFRB,
    [PPC32_IT_DMUL_X35RC]    = EMITOP " " EMITFRT   "," EMITFRA   "," EMITFRB,
    [PPC32_IT_DMULRC_X35RC]  = EMITOP " " EMITFRT   "," EMITFRA   "," EMITFRB,
    [PPC32_IT_DSUB_X35RC]    = EMITOP " " EMITFRT   "," EMITFRA   "," EMITFRB,
    [PPC32_IT_DSUBRC_X35RC]  = EMITOP " " EMITFRT   "," EMITFRA   "," EMITFRB,
    [PPC32_IT_FCPSGN_X35RC]  = EMITOP " " EMITFRT   "," EMITFRA   "," EMITFRB,
    [PPC32_IT_FCPSGNRC_X35RC] = EMITOP " " EMITFRT   "," EMITFRA   "," EMITFRB,

    //
    // Instruction Format X37 Insns
    //
    [PPC32_IT_DCTDP_X37]     = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_DCTDPRC_X37]   = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_DCTFIX_X37]    = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_DCTFIXRC_X37]  = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_DRSP_X37]      = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_DRSPRC_X37]    = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_DXEX_X37]      = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_DXEXRC_X37]    = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FABS_X37]      = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FABSRC_X37]    = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FCFID_X37]     = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FCFIDRC_X37]   = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FCTID_X37]     = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FCTIDRC_X37]   = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FCTIDZ_X37]    = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FCTIDZRC_X37]  = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FCTIW_X37]     = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FCTIWRC_X37]   = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FCTIWZ_X37]    = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FCTIWZRC_X37]  = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FMR_X37]       = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FMRRC_X37]     = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FNABS_X37]     = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FNABSRC_X37]   = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FNEG_X37]      = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FNEGRC_X37]    = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FRIM_X37]      = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FRIMRC_X37]    = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FRIN_X37]      = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FRINRC_X37]    = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FRIP_X37]      = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FRIPRC_X37]    = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FRIZ_X37]      = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FRIZRC_X37]    = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FRSP_X37]      = EMITOP " " EMITFRT   "," EMITFRB,
    [PPC32_IT_FRSPRC_X37]    = EMITOP " " EMITFRT   "," EMITFRB,

    //
    // Instruction Format X38 Insns
    //
    [PPC32_IT_DCTFIXQ_X38]   = EMITOP " " EMITFRT   "," EMITFRBP,
    [PPC32_IT_DCTFIXQRC_X38] = EMITOP " " EMITFRT   "," EMITFRBP,
    [PPC32_IT_DXEX_X38]      = EMITOP " " EMITFRT   "," EMITFRBP,
    [PPC32_IT_DXEXRC_X38]    = EMITOP " " EMITFRT   "," EMITFRBP,

    //
    // Instruction Format X39 Insns
    //
    [PPC32_IT_MFFS_X39]      = EMITOP " " EMITFRT,
    [PPC32_IT_MFFSRC_X39]    = EMITOP " " EMITFRT,

    //
    // Instruction Format X4 Insns
    //
    [PPC32_IT_LSWI_X4]       = EMITOP " " EMITRT    "," EMITRA_AL "," EMITNB,

    //
    // Instruction Format X40 Insns
    //
    [PPC32_IT_DCFFIXQ_X40]   = EMITOP " " EMITFRTP  "," EMITFRB,
    [PPC32_IT_DCFFIXQRC_X40] = EMITOP " " EMITFRTP  "," EMITFRB,
    [PPC32_IT_DCTQPQ_X40]    = EMITOP " " EMITFRTP  "," EMITFRB,
    [PPC32_IT_DCTQPQRC_X40]  = EMITOP " " EMITFRTP  "," EMITFRB,

    //
    // Instruction Format X41 Insns
    //
    [PPC32_IT_DRDPQ_X41]     = EMITOP " " EMITFRTP  "," EMITFRBP,
    [PPC32_IT_DRDPQRC_X41]   = EMITOP " " EMITFRTP  "," EMITFRBP,

    //
    // Instruction Format X43 Insns
    //
    [PPC32_IT_DADDQ_X43]     = EMITOP " " EMITFRTP  "," EMITFRAP  "," EMITFRBP,
    [PPC32_IT_DADDQRC_X43]   = EMITOP " " EMITFRTP  "," EMITFRAP  "," EMITFRBP,
    [PPC32_IT_DDIVQ_X43]     = EMITOP " " EMITFRTP  "," EMITFRAP  "," EMITFRBP,
    [PPC32_IT_DDIVQRC_X43]   = EMITOP " " EMITFRTP  "," EMITFRAP  "," EMITFRBP,
    [PPC32_IT_DIEXQ_X43]     = EMITOP " " EMITFRTP  "," EMITFRAP  "," EMITFRBP,
    [PPC32_IT_DIEXQRC_X43]   = EMITOP " " EMITFRTP  "," EMITFRAP  "," EMITFRBP,
    [PPC32_IT_DMULQ_X43]     = EMITOP " " EMITFRTP  "," EMITFRAP  "," EMITFRBP,
    [PPC32_IT_DMULQRC_X43]   = EMITOP " " EMITFRTP  "," EMITFRAP  "," EMITFRBP,
    [PPC32_IT_DSUBQ_X43]     = EMITOP " " EMITFRTP  "," EMITFRAP  "," EMITFRBP,
    [PPC32_IT_DSUBQRC_X43]   = EMITOP " " EMITFRTP  "," EMITFRAP  "," EMITFRBP,

    //
    // Instruction Format X45 Insns
    //
    [PPC32_IT_DCMPOQ_X45]    = EMITOP " " EMITBF    "," EMITFRAP  "," EMITFRBP,
    [PPC32_IT_DCMPUQ_X45]    = EMITOP " " EMITBF    "," EMITFRAP  "," EMITFRBP,
    [PPC32_IT_DTSTEXQ_X45]   = EMITOP " " EMITBF    "," EMITFRAP  "," EMITFRBP,
    [PPC32_IT_DTSTSFQ_X45]   = EMITOP " " EMITBF    "," EMITFRAP  "," EMITFRBP,

    //
    // Instruction Format X46_0 Insns
    //
    [PPC32_IT_DDEDPD_X46_0]  = EMITOP " " EMITSP    "," EMITFRT   "," EMITFRB,
    [PPC32_IT_DDEDPDRC_X46_0] = EMITOP " " EMITSP    "," EMITFRT   "," EMITFRB,

    //
    // Instruction Format X46_1 Insns
    //
    [PPC32_IT_DENBCD_X46_1]  = EMITOP " " EMITS     "," EMITFRT   "," EMITFRB,
    [PPC32_IT_DENBCDRC_X46_1] = EMITOP " " EMITS     "," EMITFRT   "," EMITFRB,

    //
    // Instruction Format X47_0 Insns
    //
    [PPC32_IT_DDEDPDQ_X47_0] = EMITOP " " EMITSP    "," EMITFRTP  "," EMITFRBP,
    [PPC32_IT_DDEDPDQRC_X47_0] = EMITOP " " EMITSP    "," EMITFRTP  "," EMITFRBP,

    //
    // Instruction Format X47_1 Insns
    //
    [PPC32_IT_DENBCDQ_X47_1] = EMITOP " " EMITS     "," EMITFRTP  "," EMITFRBP,
    [PPC32_IT_DENBCDQRC_X47_1] = EMITOP " " EMITS     "," EMITFRTP  "," EMITFRBP,

    //
    // Instruction Format X48 Insns
    //
    [PPC32_IT_STFDUX_X48]    = EMITOP " " EMITFRS   "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STFDX_X48]     = EMITOP " " EMITFRS   "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STFIWX_X48]    = EMITOP " " EMITFRS   "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STFSUX_X48]    = EMITOP " " EMITFRS   "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STFSX_X48]     = EMITOP " " EMITFRS   "," EMITRA_AL "," EMITRB,

    //
    // Instruction Format X5 Insns
    //
    [PPC32_IT_MFSR_X5]       = EMITOP " " EMITRT    "," EMITSR,

    //
    // Instruction Format X50 Insns
    //
    [PPC32_IT_MTFSSB0_X50]   = EMITOP " " EMITBT,
    [PPC32_IT_MTFSSB0RC_X50] = EMITOP " " EMITBT,
    [PPC32_IT_MTFSSB1_X50]   = EMITOP " " EMITBT,
    [PPC32_IT_MTFSSB1RC_X50] = EMITOP " " EMITBT,

    //
    // Instruction Format X51 Insns
    //
    [PPC32_IT_DCBA_X51]      = EMITOP " " EMITRA_AL "," EMITRB,
    [PPC32_IT_DCBFEP_X51]    = EMITOP " " EMITRA_AL "," EMITRB,
    [PPC32_IT_DCBI_X51]      = EMITOP " " EMITRA_AL "," EMITRB,
    [PPC32_IT_DCBST_X51]     = EMITOP " " EMITRA_AL "," EMITRB,
    [PPC32_IT_DCBSTEP_X51]   = EMITOP " " EMITRA_AL "," EMITRB,
    [PPC32_IT_DCBZ_X51]      = EMITOP " " EMITRA_AL "," EMITRB,
    [PPC32_IT_DCBZEP_X51]    = EMITOP " " EMITRA_AL "," EMITRB,
    [PPC32_IT_ICBI_X51]      = EMITOP " " EMITRA_AL "," EMITRB,
    [PPC32_IT_ICBIEP_X51]    = EMITOP " " EMITRA_AL "," EMITRB,
    [PPC32_IT_ICREAD_X51]    = EMITOP " " EMITRA_AL "," EMITRB,
    [PPC32_IT_TLBIVAX_X51]   = EMITOP " " EMITRA_AL "," EMITRB,
    [PPC32_IT_TLBSX_X51]     = EMITOP " " EMITRA_AL "," EMITRB,

    //
    // Instruction Format X52 Insns
    //
    [PPC32_IT_MSGCLR_X52]    = EMITOP " " EMITRB,
    [PPC32_IT_MSGSND_X52]    = EMITOP " " EMITRB,
    [PPC32_IT_SLBIE_X52]     = EMITOP " " EMITRB,

    //
    // Instruction Format X53_0 Insns
    //
    [PPC32_IT_EIEIO_X53_0]   = EMITOP,

    //
    // Instruction Format X53_1 Insns
    //
    [PPC32_IT_TLBIA_X53_1]   = EMITOP,
    [PPC32_IT_TLBRE_X53_1]   = EMITOP,
    [PPC32_IT_TLBSYNC_X53_1] = EMITOP,
    [PPC32_IT_TLBWE_X53_1]   = EMITOP,
    [PPC32_IT_WAIT_X53_1]    = EMITOP,

    //
    // Instruction Format X54 Insns
    //
    [PPC32_IT_WRTEEI_X54]    = EMITOP " " EMITE,

    //
    // Instruction Format X55_0 Insns
    //
    [PPC32_IT_SLBIA_0_X55_0] = EMITOP,

    //
    // Instruction Format X55_1 Insns
    //
    [PPC32_IT_SLBIA_1_X55_1] = EMITOP " " EMITIH,

    //
    // Instruction Format X58 Insns
    //
    [PPC32_IT_LVEBX_X58]     = EMITOP " " EMITVRT   "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LVEHX_X58]     = EMITOP " " EMITVRT   "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LVEWX_X58]     = EMITOP " " EMITVRT   "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LVSL_X58]      = EMITOP " " EMITVRT   "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LVSR_X58]      = EMITOP " " EMITVRT   "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LVX_X58]       = EMITOP " " EMITVRT   "," EMITRA_AL "," EMITRB,
    [PPC32_IT_LVXL_X58]      = EMITOP " " EMITVRT   "," EMITRA_AL "," EMITRB,

    //
    // Instruction Format X59 Insns
    //
    [PPC32_IT_STVEBX_X59]    = EMITOP " " EMITVRS   "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STVEHX_X59]    = EMITOP " " EMITVRS   "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STVEWX_X59]    = EMITOP " " EMITVRS   "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STVX_X59]      = EMITOP " " EMITVRS   "," EMITRA_AL "," EMITRB,
    [PPC32_IT_STVXL_X59]     = EMITOP " " EMITVRS   "," EMITRA_AL "," EMITRB,

    //
    // Instruction Format X6 Insns
    //
    [PPC32_IT_MFSRIN_X6]     = EMITOP " " EMITRT    "," EMITRB,
    [PPC32_IT_SLBMFEE_X6]    = EMITOP " " EMITRT    "," EMITRB,
    [PPC32_IT_SLBMFEV_X6]    = EMITOP " " EMITRT    "," EMITRB,

    //
    // Instruction Format X60 Insns
    //
    [PPC32_IT_MBAR_X60]      = EMITOP " " EMITMO,

    //
    // Instruction Format X8 Insns
    //
    [PPC32_IT_MFMSR_X8]      = EMITOP " " EMITRT,

    //
    // Instruction Format X9 Insns
    //
    [PPC32_IT_AND_X9]        = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,
    [PPC32_IT_ANDC_X9]       = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,
    [PPC32_IT_ANDCRC_X9]     = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,
    [PPC32_IT_ANDRC_X9]      = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,
    [PPC32_IT_DLMZB_X9]      = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,
    [PPC32_IT_DLMZBRC_X9]    = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,
    [PPC32_IT_EQV_X9]        = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,
    [PPC32_IT_EQVRC_X9]      = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,
    [PPC32_IT_E_RLW_X9]      = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,
    [PPC32_IT_E_RLWRC_X9]    = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,
    [PPC32_IT_NAND_X9]       = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,
    [PPC32_IT_NANDRC_X9]     = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,
    [PPC32_IT_NOR_X9]        = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,
    [PPC32_IT_NORRC_X9]      = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,
    [PPC32_IT_OR_X9]         = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,
    [PPC32_IT_ORC_X9]        = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,
    [PPC32_IT_ORCRC_X9]      = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,
    [PPC32_IT_ORRC_X9]       = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,
    [PPC32_IT_SLW_X9]        = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,
    [PPC32_IT_SLWRC_X9]      = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,
    [PPC32_IT_SRAW_X9]       = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,
    [PPC32_IT_SRAWRC_X9]     = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,
    [PPC32_IT_SRW_X9]        = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,
    [PPC32_IT_SRWRC_X9]      = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,
    [PPC32_IT_XOR_X9]        = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,
    [PPC32_IT_XORRC_X9]      = EMITOP " " EMITRA    "," EMITRS    "," EMITRB,

    //
    // Instruction Format XFL Insns
    //
    [PPC32_IT_MTFSF_XFL]     = EMITOP " " EMITFLM "," EMITFRB "," EMITBL "," EMITBW,
    [PPC32_IT_MTFSFRC_XFL]   = EMITOP " " EMITFLM "," EMITFRB "," EMITBL "," EMITBW,

    //
    // Instruction Format XFLZ Insns
    //
    [PPC32_IT_MTFSFZ_XFLZ]   = EMITOP " " EMITFLM "," EMITFRB ,
    [PPC32_IT_MTFSFZRC_XFLZ] = EMITOP " " EMITFLM "," EMITFRB ,

    //
    // Instruction Format XFX1 Insns
    //
    [PPC32_IT_MFSPR_XFX1]    = EMITOP " " EMITRT   "," EMITSPR,
    [PPC32_IT_MFTB_XFX1]     = EMITOP " " EMITRT   "," EMITSPR,

    //
    // Instruction Format XFX10 Insns
    //
    [PPC32_IT_MTSPR_XFX10]   = EMITOP " " EMITSPR  "," EMITRS,

    //
    // Instruction Format XFX10D Insns
    //
    [PPC32_IT_MTCTR_XFX10D]  = EMITOP " " EMITRS,
    [PPC32_IT_MTLR_XFX10D]   = EMITOP " " EMITRS,
    [PPC32_IT_MTXER_XFX10D]  = EMITOP " " EMITRS,

    //
    // Instruction Format XFX11 Insns
    //
    [PPC32_IT_MTDCR_XFX11]   = EMITOP " " EMITDCR  "," EMITRS,

    //
    // Instruction Format XFX12 Insns
    //
    [PPC32_IT_MTPMR_XFX12]   = EMITOP " " EMITPMRN "," EMITRS,

    //
    // Instruction Format XFX1D Insns
    //
    [PPC32_IT_MFCTR_XFX1D]   = EMITOP " " EMITRT,
    [PPC32_IT_MFLR_XFX1D]    = EMITOP " " EMITRT,
    [PPC32_IT_MFXER_XFX1D]   = EMITOP " " EMITRT,

    //
    // Instruction Format XFX3 Insns
    //
    [PPC32_IT_MFCR_XFX3]     = EMITOP " " EMITRT,

    //
    // Instruction Format XFX4 Insns
    //
    [PPC32_IT_MFOCRF_XFX4]   = EMITOP " " EMITRT   "," EMITFXM,

    //
    // Instruction Format XFX5 Insns
    //
    [PPC32_IT_MFDCR_XFX5]    = EMITOP " " EMITRT   "," EMITDCR,

    //
    // Instruction Format XFX6 Insns
    //
    [PPC32_IT_MFPMR_XFX6]    = EMITOP " " EMITRT   "," EMITPMRN,

    //
    // Instruction Format XFX7 Insns
    //

    //
    // Instruction Format XFX8 Insns
    //
    [PPC32_IT_MTCRF_XFX8]    = EMITOP " " EMITFXM  "," EMITRS,

    //
    // Instruction Format XFX8D Insns
    //
    [PPC32_IT_MTCR_XFX8D]    = EMITOP " " EMITRS,

    //
    // Instruction Format XFX9 Insns
    //
    [PPC32_IT_MTOCRF_XFX9]   = EMITOP " " EMITFXM  "," EMITRS,

    //
    // Instruction Format XL1 Insns
    //
    [PPC32_IT_CRAND_XL1]     = EMITOP " " EMITBT   "," EMITBA   "," EMITBB,
    [PPC32_IT_CRANDC_XL1]    = EMITOP " " EMITBT   "," EMITBA   "," EMITBB,
    [PPC32_IT_CREQV_XL1]     = EMITOP " " EMITBT   "," EMITBA   "," EMITBB,
    [PPC32_IT_CRNAND_XL1]    = EMITOP " " EMITBT   "," EMITBA   "," EMITBB,
    [PPC32_IT_CRNOR_XL1]     = EMITOP " " EMITBT   "," EMITBA   "," EMITBB,
    [PPC32_IT_CROR_XL1]      = EMITOP " " EMITBT   "," EMITBA   "," EMITBB,
    [PPC32_IT_CRORC_XL1]     = EMITOP " " EMITBT   "," EMITBA   "," EMITBB,
    [PPC32_IT_CRXOR_XL1]     = EMITOP " " EMITBT   "," EMITBA   "," EMITBB,
    [PPC32_IT_E_CRAND_XL1]   = EMITOP " " EMITBT   "," EMITBA   "," EMITBB,
    [PPC32_IT_E_CRANDC_XL1]  = EMITOP " " EMITBT   "," EMITBA   "," EMITBB,
    [PPC32_IT_E_CREQV_XL1]   = EMITOP " " EMITBT   "," EMITBA   "," EMITBB,
    [PPC32_IT_E_CRNAND_XL1]  = EMITOP " " EMITBT   "," EMITBA   "," EMITBB,
    [PPC32_IT_E_CRNOR_XL1]   = EMITOP " " EMITBT   "," EMITBA   "," EMITBB,
    [PPC32_IT_E_CROR_XL1]    = EMITOP " " EMITBT   "," EMITBA   "," EMITBB,
    [PPC32_IT_E_CRORC_XL1]   = EMITOP " " EMITBT   "," EMITBA   "," EMITBB,
    [PPC32_IT_E_CRXOR_XL1]   = EMITOP " " EMITBT   "," EMITBA   "," EMITBB,

    //
    // Instruction Format XL2 Insns
    //
    [PPC32_IT_BCCTR_XL2]     = EMITOP     EMITLK   " " EMITBO_0 "," EMITBI,
    [PPC32_IT_BCLR_XL2]      = EMITOP     EMITLK   " " EMITBO_0 "," EMITBI,

    //
    // Instruction Format XL3 Insns
    //
    [PPC32_IT_E_MCRF_XL3]    = EMITOP " " EMITBF   "," EMITBFA,
    [PPC32_IT_MCRF_XL3]      = EMITOP " " EMITBF   "," EMITBFA,

    //
    // Instruction Format XL4 Insns
    //
    [PPC32_IT_DOZE_XL4]      = EMITOP,
    [PPC32_IT_HRFID_XL4]     = EMITOP,
    [PPC32_IT_ISYNC_XL4]     = EMITOP,
    [PPC32_IT_NAP_XL4]       = EMITOP,
    [PPC32_IT_RFCI_XL4]      = EMITOP,
    [PPC32_IT_RFI_XL4]       = EMITOP,
    [PPC32_IT_RFID_XL4]      = EMITOP,
    [PPC32_IT_RFMCI_XL4]     = EMITOP,
    [PPC32_IT_RVWINKLE_XL4]  = EMITOP,
    [PPC32_IT_SLEEP_XL4]     = EMITOP,

    //
    // Instruction Format XO1 Insns
    //
    [PPC32_IT_ADD_XO1]       = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_ADDC_XO1]      = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_ADDCOE_XO1]    = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_ADDCOERC_XO1]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_ADDCRC_XO1]    = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_ADDE_XO1]      = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_ADDEOE_XO1]    = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_ADDEOERC_XO1]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_ADDERC_XO1]    = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_ADDOE_XO1]     = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_ADDOERC_XO1]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_ADDRC_XO1]     = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_DIVW_XO1]      = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_DIVWOE_XO1]    = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_DIVWOERC_XO1]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_DIVWRC_XO1]    = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_DIVWU_XO1]     = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_DIVWUOE_XO1]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_DIVWUOERC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_DIVWURC_XO1]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACCHW_XO1]    = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACCHWOE_XO1]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACCHWOERC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACCHWRC_XO1]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACCHWS_XO1]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACCHWSOE_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACCHWSOERC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACCHWSRC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACCHWSU_XO1]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACCHWSUOE_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACCHWSUOERC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACCHWSURC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACCHWU_XO1]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACCHWUOE_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACCHWUOERC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACCHWURC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACHHW_XO1]    = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACHHWOE_XO1]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACHHWOERC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACHHWRC_XO1]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACHHWS_XO1]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACHHWSOE_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACHHWSOERC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACHHWSRC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACHHWSU_XO1]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACHHWSUOE_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACHHWSUOERC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACHHWSURC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACHHWU_XO1]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACHHWUOE_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACHHWUOERC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACHHWURC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACLHW_XO1]    = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACLHWOE_XO1]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACLHWOERC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACLHWRC_XO1]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACLHWS_XO1]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACLHWSOE_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACLHWSOERC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACLHWSRC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACLHWSU_XO1]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACLHWSUOE_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACLHWSUOERC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACLHWSURC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACLHWU_XO1]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACLHWUOE_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACLHWUOERC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MACLHWURC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MULLW_XO1]     = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MULLWOE_XO1]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MULLWOERC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MULLWRC_XO1]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_NMACCHW_XO1]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_NMACCHWOE_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_NMACCHWOERC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_NMACCHWRC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_NMACCHWS_XO1]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_NMACCHWSOE_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_NMACCHWSOERC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_NMACCHWSRC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_NMACHHW_XO1]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_NMACHHWOE_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_NMACHHWOERC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_NMACHHWRC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_NMACHHWS_XO1]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_NMACHHWSOE_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_NMACHHWSOERC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_NMACHHWSRC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_NMACLHW_XO1]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_NMACLHWOE_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_NMACLHWOERC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_NMACLHWRC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_NMACLHWS_XO1]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_NMACLHWSOE_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_NMACLHWSOERC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_NMACLHWSRC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_SUBF_XO1]      = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_SUBFC_XO1]     = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_SUBFCOE_XO1]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_SUBFCOERC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_SUBFCRC_XO1]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_SUBFE_XO1]     = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_SUBFEOE_XO1]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_SUBFEOERC_XO1] = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_SUBFERC_XO1]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_SUBFOE_XO1]    = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_SUBFOERC_XO1]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_SUBFRC_XO1]    = EMITOP " " EMITRT "," EMITRA "," EMITRB,

    //
    // Instruction Format XO2 Insns
    //
    [PPC32_IT_MULHW_XO2]     = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MULHWRC_XO2]   = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MULHWU_XO2]    = EMITOP " " EMITRT "," EMITRA "," EMITRB,
    [PPC32_IT_MULHWURC_XO2]  = EMITOP " " EMITRT "," EMITRA "," EMITRB,

    //
    // Instruction Format XO3 Insns
    //
    [PPC32_IT_ADDG6S_XO3]    = EMITOP " " EMITRT "," EMITRA "," EMITRB,

    //
    // Instruction Format XO4 Insns
    //
    [PPC32_IT_ADDME_XO4]     = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_ADDMEOE_XO4]   = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_ADDMEOERC_XO4] = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_ADDMERC_XO4]   = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_ADDZE_XO4]     = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_ADDZEOE_XO4]   = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_ADDZEOERC_XO4] = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_ADDZERC_XO4]   = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_NEG_XO4]       = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_NEGOE_XO4]     = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_NEGOERC_XO4]   = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_NEGRC_XO4]     = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_SUBFME_XO4]    = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_SUBFMEOE_XO4]  = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_SUBFMEOERC_XO4] = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_SUBFMERC_XO4]  = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_SUBFZE_XO4]    = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_SUBFZEOE_XO4]  = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_SUBFZEOERC_XO4] = EMITOP " " EMITRT "," EMITRA,
    [PPC32_IT_SUBFZERC_XO4]  = EMITOP " " EMITRT "," EMITRA,

    //
    // Instruction Format Z22_1 Insns
    //
    [PPC32_IT_DTSTDC_Z22_1]  = EMITOP " " EMITBF   "," EMITFRA  "," EMITDCM,
    [PPC32_IT_DTSTDG_Z22_1]  = EMITOP " " EMITBF   "," EMITFRA  "," EMITDCM,

    //
    // Instruction Format Z22_2 Insns
    //
    [PPC32_IT_DTSTDCQ_Z22_2] = EMITOP " " EMITBF   "," EMITFRAP "," EMITDCM,
    [PPC32_IT_DTSTDGQ_Z22_2] = EMITOP " " EMITBF   "," EMITFRAP "," EMITDCM,

    //
    // Instruction Format Z22_3 Insns
    //

    //
    // Instruction Format Z22_4 Insns
    //

    //
    // Instruction Format Z22_5 Insns
    //
    [PPC32_IT_DSCLI_Z22_5]   = EMITOP " " EMITFRT  "," EMITFRA  "," EMITSH,
    [PPC32_IT_DSCLIRC_Z22_5] = EMITOP " " EMITFRT  "," EMITFRA  "," EMITSH,
    [PPC32_IT_DSCRI_Z22_5]   = EMITOP " " EMITFRT  "," EMITFRA  "," EMITSH,
    [PPC32_IT_DSCRIRC_Z22_5] = EMITOP " " EMITFRT  "," EMITFRA  "," EMITSH,

    //
    // Instruction Format Z22_6 Insns
    //
    [PPC32_IT_DSCLIQ_Z22_6]  = EMITOP " " EMITFRTP "," EMITFRAP "," EMITSH,
    [PPC32_IT_DSCLIQRC_Z22_6] = EMITOP " " EMITFRTP "," EMITFRAP "," EMITSH,
    [PPC32_IT_DSCRIQ_Z22_6]  = EMITOP " " EMITFRTP "," EMITFRAP "," EMITSH,
    [PPC32_IT_DSCRIQRC_Z22_6] = EMITOP " " EMITFRTP "," EMITFRAP "," EMITSH,

    //
    // Instruction Format Z23_1 Insns
    //
    [PPC32_IT_DQUAI_Z23_1]   = EMITOP " " EMITTE   "," EMITFRT  "," EMITFRB  "," EMITRMC,
    [PPC32_IT_DQUAIRC_Z23_1] = EMITOP " " EMITTE   "," EMITFRT  "," EMITFRB  "," EMITRMC,

    //
    // Instruction Format Z23_2 Insns
    //
    [PPC32_IT_DQUAIQ_Z23_2]  = EMITOP " " EMITTE   "," EMITFRTP "," EMITFRBP "," EMITRMC,
    [PPC32_IT_DQUAIQRC_Z23_2] = EMITOP " " EMITTE   "," EMITFRTP "," EMITFRBP "," EMITRMC,

    //
    // Instruction Format Z23_3 Insns
    //
    [PPC32_IT_DQUA_Z23_3]    = EMITOP " " EMITFRT  "," EMITFRA  "," EMITFRB  "," EMITRMC,
    [PPC32_IT_DQUAQ_Z23_3]   = EMITOP " " EMITFRT  "," EMITFRA  "," EMITFRB  "," EMITRMC,
    [PPC32_IT_DQUAQRC_Z23_3] = EMITOP " " EMITFRT  "," EMITFRA  "," EMITFRB  "," EMITRMC,
    [PPC32_IT_DQUARC_Z23_3]  = EMITOP " " EMITFRT  "," EMITFRA  "," EMITFRB  "," EMITRMC,
    [PPC32_IT_DRRND_Z23_3]   = EMITOP " " EMITFRT  "," EMITFRA  "," EMITFRB  "," EMITRMC,
    [PPC32_IT_DRRNDQ_Z23_3]  = EMITOP " " EMITFRT  "," EMITFRA  "," EMITFRB  "," EMITRMC,
    [PPC32_IT_DRRNDQRC_Z23_3] = EMITOP " " EMITFRT  "," EMITFRA  "," EMITFRB  "," EMITRMC,
    [PPC32_IT_DRRNDRC_Z23_3] = EMITOP " " EMITFRT  "," EMITFRA  "," EMITFRB  "," EMITRMC,

    //
    // Instruction Format Z23_5 Insns
    //

    //
    // Instruction Format Z23_6 Insns
    //
    [PPC32_IT_DRINTN_Z23_6]  = EMITOP " " EMITR    "," EMITFRT  "," EMITFRB  "," EMITRMC,
    [PPC32_IT_DRINTNRC_Z23_6] = EMITOP " " EMITR    "," EMITFRT  "," EMITFRB  "," EMITRMC,
    [PPC32_IT_DRINTX_Z23_6]  = EMITOP " " EMITR    "," EMITFRT  "," EMITFRB  "," EMITRMC,
    [PPC32_IT_DRINTXRC_Z23_6] = EMITOP " " EMITR    "," EMITFRT  "," EMITFRB  "," EMITRMC,

    //
    // Instruction Format Z23_7 Insns
    //
    [PPC32_IT_DRINTNQ_Z23_7] = EMITOP " " EMITR    "," EMITFRTP "," EMITFRBP "," EMITRMC,
    [PPC32_IT_DRINTNQRC_Z23_7] = EMITOP " " EMITR    "," EMITFRTP "," EMITFRBP "," EMITRMC,
    [PPC32_IT_DRINTXQ_Z23_7] = EMITOP " " EMITR    "," EMITFRTP "," EMITFRBP "," EMITRMC,
    [PPC32_IT_DRINTXQRC_Z23_7] = EMITOP " " EMITR    "," EMITFRTP "," EMITFRBP "," EMITRMC,

    [PPC32_IT_LAST] = "UNDEFINED"
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
// Function to format the info field #AA# << 1 | #LK#
//
static void EMITAALK_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = (AALK[info->AA << 1 | info->LK] ? AALK[info->AA << 1 | info->LK] : "%d");
    sprintf(tmp, fmt, info->AA << 1 | info->LK);
    putString(result, tmp);
}
//
// Function to format the info field #ARX#
//
static void EMITARX_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "r%d";
    sprintf(tmp, fmt, info->ARX);
    putString(result, tmp);
}
//
// Function to format the info field #ARY#
//
static void EMITARY_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "r%d";
    sprintf(tmp, fmt, info->ARY);
    putString(result, tmp);
}
//
// Function to format the info field #BA#
//
static void EMITBA_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = (CR[info->BA] ? CR[info->BA] : "%d");
    sprintf(tmp, fmt, info->BA);
    putString(result, tmp);
}
//
// Function to format the info field #BB#
//
static void EMITBB_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = (CR[info->BB] ? CR[info->BB] : "%d");
    sprintf(tmp, fmt, info->BB);
    putString(result, tmp);
}
//
// Function to format the info field #BC#
//
static void EMITBC_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->BC);
    putString(result, tmp);
}
//
// Function to format the info field #AA# ? #BD# : ( #BD# + #thisPC# )
//
static void EMITBD_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "0x%x";
    sprintf(tmp, fmt, info->AA ? info->BD : ( info->BD + info->thisPC ));
    putString(result, tmp);
}
//
// Function to format the info field ( #BD24# + #thisPC# )
//
static void EMITBD24_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "0x%x";
    sprintf(tmp, fmt, ( info->BD24 + info->thisPC ));
    putString(result, tmp);
}
//
// Function to format the info field ( #BD8# + #thisPC# )
//
static void EMITBD8_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "0x%x";
    sprintf(tmp, fmt, ( info->BD8 + info->thisPC ));
    putString(result, tmp);
}
//
// Function to format the info field #BF#
//
static void EMITBF_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "cr%d";
    sprintf(tmp, fmt, info->BF);
    putString(result, tmp);
}
//
// Function to format the info field #BF32#
//
static void EMITBF32_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "cr%d";
    sprintf(tmp, fmt, info->BF32);
    putString(result, tmp);
}
//
// Function to format the info field #BFA#
//
static void EMITBFA_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "cr%d";
    sprintf(tmp, fmt, info->BFA);
    putString(result, tmp);
}
//
// Function to format the info field #BFU#
//
static void EMITBFU_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->BFU);
    putString(result, tmp);
}
//
// Function to format the info field #BI#
//
static void EMITBI_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = (CR[info->BI] ? CR[info->BI] : "%d");
    sprintf(tmp, fmt, info->BI);
    putString(result, tmp);
}
//
// Function to format the info field #BI16#
//
static void EMITBI16_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = (CR[info->BI16] ? CR[info->BI16] : "%d");
    sprintf(tmp, fmt, info->BI16);
    putString(result, tmp);
}
//
// Function to format the info field #BI32#
//
static void EMITBI32_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = (CRVLE[info->BI32] ? CRVLE[info->BI32] : "%d");
    sprintf(tmp, fmt, info->BI32);
    putString(result, tmp);
}
//
// Function to format the info field #BL#
//
static void EMITBL_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->BL);
    putString(result, tmp);
}
//
// Function to format the info field #BO16#
//
static void EMITBO16_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = (BITSTR32[info->BO16] ? BITSTR32[info->BO16] : "");
    sprintf(tmp, fmt, info->BO16);
    putString(result, tmp);
}
//
// Function to format the info field ( #BO32# & 0x3 )
//
static void EMITBO32_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = (BITSTR32[( info->BO32 & 0x3 )] ? BITSTR32[( info->BO32 & 0x3 )] : "");
    sprintf(tmp, fmt, ( info->BO32 & 0x3 ));
    putString(result, tmp);
}
//
// Function to format the info field ( #BO# & 0xf )
//
static void EMITBO_0_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = (BITSTR[( info->BO & 0xf )] ? BITSTR[( info->BO & 0xf )] : "");
    sprintf(tmp, fmt, ( info->BO & 0xf ));
    putString(result, tmp);
}
//
// Function to format the info field ( #BO# >> 4 ) ? '1' : '0'
//
static void EMITBO_1_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%c";
    sprintf(tmp, fmt, ( info->BO >> 4 ) ? '1' : '0');
    putString(result, tmp);
}
//
// Function to format the info field #BT#
//
static void EMITBT_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = (CR[info->BT] ? CR[info->BT] : "%d");
    sprintf(tmp, fmt, info->BT);
    putString(result, tmp);
}
//
// Function to format the info field #BW#
//
static void EMITBW_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->BW);
    putString(result, tmp);
}
//
// Function to format the info field #CT#
//
static void EMITCT_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->CT);
    putString(result, tmp);
}
//
// Function to format the info field #D#
//
static void EMITD_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%d";
    sprintf(tmp, fmt, info->D);
    putString(result, tmp);
}
//
// Function to format the info field #D8#
//
static void EMITD8_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%d";
    sprintf(tmp, fmt, info->D8);
    putString(result, tmp);
}
//
// Function to format the info field #DCM#
//
static void EMITDCM_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->DCM);
    putString(result, tmp);
}
//
// Function to format the info field #DCR#
//
static void EMITDCR_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->DCR);
    putString(result, tmp);
}
//
// Function to format the info field #DQ#
//
static void EMITDQ_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%d";
    sprintf(tmp, fmt, info->DQ);
    putString(result, tmp);
}
//
// Function to format the info field #DS#
//
static void EMITDS_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%d";
    sprintf(tmp, fmt, info->DS);
    putString(result, tmp);
}
//
// Function to format the info field #DUI#
//
static void EMITDUI_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->DUI);
    putString(result, tmp);
}
//
// Function to format the info field #DUIS#
//
static void EMITDUIS_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->DUIS);
    putString(result, tmp);
}
//
// Function to format the info field #E#
//
static void EMITE_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->E);
    putString(result, tmp);
}
//
// Function to format the info field #EH#
//
static void EMITEH_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = (EH[info->EH] ? EH[info->EH] : "");
    sprintf(tmp, fmt, info->EH);
    putString(result, tmp);
}
//
// Function to format the info field #FLM#
//
static void EMITFLM_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->FLM);
    putString(result, tmp);
}
//
// Function to format the info field #FRA#
//
static void EMITFRA_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "f%d";
    sprintf(tmp, fmt, info->FRA);
    putString(result, tmp);
}
//
// Function to format the info field #FRAp#
//
static void EMITFRAP_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "f%d";
    sprintf(tmp, fmt, info->FRAp);
    putString(result, tmp);
}
//
// Function to format the info field #FRB#
//
static void EMITFRB_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "f%d";
    sprintf(tmp, fmt, info->FRB);
    putString(result, tmp);
}
//
// Function to format the info field #FRBp#
//
static void EMITFRBP_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "f%d";
    sprintf(tmp, fmt, info->FRBp);
    putString(result, tmp);
}
//
// Function to format the info field #FRC#
//
static void EMITFRC_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "f%d";
    sprintf(tmp, fmt, info->FRC);
    putString(result, tmp);
}
//
// Function to format the info field #FRS#
//
static void EMITFRS_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "f%d";
    sprintf(tmp, fmt, info->FRS);
    putString(result, tmp);
}
//
// Function to format the info field #FRT#
//
static void EMITFRT_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "f%d";
    sprintf(tmp, fmt, info->FRT);
    putString(result, tmp);
}
//
// Function to format the info field #FRTp#
//
static void EMITFRTP_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "f%d";
    sprintf(tmp, fmt, info->FRTp);
    putString(result, tmp);
}
//
// Function to format the info field #FXM#
//
static void EMITFXM_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->FXM);
    putString(result, tmp);
}
//
// Function to format the info field #IH#
//
static void EMITIH_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->IH);
    putString(result, tmp);
}
//
// Function to format the info field #LEV#
//
static void EMITLEV_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%d";
    sprintf(tmp, fmt, info->LEV);
    putString(result, tmp);
}
//
// Function to format the info field #AA# ? #LI# : ( #LI# + #thisPC# )
//
static void EMITLI_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "0x%x";
    sprintf(tmp, fmt, info->AA ? info->LI : ( info->LI + info->thisPC ));
    putString(result, tmp);
}
//
// Function to format the info field #li20#
//
static void EMITLI20_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%d";
    sprintf(tmp, fmt, info->li20);
    putString(result, tmp);
}
//
// Function to format the info field #LK#
//
static void EMITLK_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = (AALK[info->LK] ? AALK[info->LK] : "%d");
    sprintf(tmp, fmt, info->LK);
    putString(result, tmp);
}
//
// Function to format the info field #MB#
//
static void EMITMB_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->MB);
    putString(result, tmp);
}
//
// Function to format the info field #ME#
//
static void EMITME_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->ME);
    putString(result, tmp);
}
//
// Function to format the info field #MO#
//
static void EMITMO_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->MO);
    putString(result, tmp);
}
//
// Function to format the info field ( #NB# ? #NB# : 32 )
//
static void EMITNB_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%d";
    sprintf(tmp, fmt, ( info->NB ? info->NB : 32 ));
    putString(result, tmp);
}
//
// Function to format the info field #OIM5#
//
static void EMITOIM5_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->OIM5);
    putString(result, tmp);
}
//
// Function to format the info field #opcode#
//
static void EMITOP_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%s";
    sprintf(tmp, fmt, info->opcode);
    putString(result, tmp);
}
//
// Function to format the info field #PMRN#
//
static void EMITPMRN_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->PMRN);
    putString(result, tmp);
}
//
// Function to format the info field #R#
//
static void EMITR_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->R);
    putString(result, tmp);
}
//
// Function to format the info field #RA#
//
static void EMITRA_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "r%d";
    sprintf(tmp, fmt, info->RA);
    putString(result, tmp);
}
//
// Function to format the info field #RA#
//
static void EMITRA_AL_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = (RA[info->RA] ? RA[info->RA] : "");
    sprintf(tmp, fmt, info->RA);
    putString(result, tmp);
}
//
// Function to format the info field #RB#
//
static void EMITRB_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "r%d";
    sprintf(tmp, fmt, info->RB);
    putString(result, tmp);
}
//
// Function to format the info field #RMC#
//
static void EMITRMC_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->RMC);
    putString(result, tmp);
}
//
// Function to format the info field #RS#
//
static void EMITRS_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "r%d";
    sprintf(tmp, fmt, info->RS);
    putString(result, tmp);
}
//
// Function to format the info field #RSp#
//
static void EMITRSP_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "r%d";
    sprintf(tmp, fmt, info->RSp);
    putString(result, tmp);
}
//
// Function to format the info field #RT#
//
static void EMITRT_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "r%d";
    sprintf(tmp, fmt, info->RT);
    putString(result, tmp);
}
//
// Function to format the info field #RTp#
//
static void EMITRTP_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "r%d";
    sprintf(tmp, fmt, info->RTp);
    putString(result, tmp);
}
//
// Function to format the info field #RX#
//
static void EMITRX_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "r%d";
    sprintf(tmp, fmt, info->RX);
    putString(result, tmp);
}
//
// Function to format the info field #RY#
//
static void EMITRY_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "r%d";
    sprintf(tmp, fmt, info->RY);
    putString(result, tmp);
}
//
// Function to format the info field #RZ#
//
static void EMITRZ_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "r%d";
    sprintf(tmp, fmt, info->RZ);
    putString(result, tmp);
}
//
// Function to format the info field #S#
//
static void EMITS_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->S);
    putString(result, tmp);
}
//
// Function to format the info field #F# ? ( ( ( ( #S8# & 0xff ) ^ 0xff ) << ( 8 * #SCL# ) ) ^ 0xffffffff ) : ( ( #S8# & 0xff ) << ( 8 * #SCL# ) )
//
static void EMITS8_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%d";
    sprintf(tmp, fmt, info->F ? ( ( ( ( info->S8 & 0xff ) ^ 0xff ) << ( 8 * info->SCL ) ) ^ 0xffffffff ) : ( ( info->S8 & 0xff ) << ( 8 * info->SCL ) ));
    putString(result, tmp);
}
//
// Function to format the info field #SD4#
//
static void EMITSD4_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->SD4);
    putString(result, tmp);
}
//
// Function to format the info field #SH#
//
static void EMITSH_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->SH);
    putString(result, tmp);
}
//
// Function to format the info field #SHB#
//
static void EMITSHB_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->SHB);
    putString(result, tmp);
}
//
// Function to format the info field #SI#
//
static void EMITSI_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%d";
    sprintf(tmp, fmt, info->SI);
    putString(result, tmp);
}
//
// Function to format the info field #SIM#
//
static void EMITSIM_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%d";
    sprintf(tmp, fmt, info->SIM);
    putString(result, tmp);
}
//
// Function to format the info field #SP#
//
static void EMITSP_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->SP);
    putString(result, tmp);
}
//
// Function to format the info field #SPR#
//
static void EMITSPR_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->SPR);
    putString(result, tmp);
}
//
// Function to format the info field #SR#
//
static void EMITSR_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->SR);
    putString(result, tmp);
}
//
// Function to format the info field #TE#
//
static void EMITTE_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%d";
    sprintf(tmp, fmt, info->TE);
    putString(result, tmp);
}
//
// Function to format the info field #TH#
//
static void EMITTH_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->TH);
    putString(result, tmp);
}
//
// Function to format the info field #TO#
//
static void EMITTO_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = (TO[info->TO] ? TO[info->TO] : "%d");
    sprintf(tmp, fmt, info->TO);
    putString(result, tmp);
}
//
// Function to format the info field #U#
//
static void EMITU_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->U);
    putString(result, tmp);
}
//
// Function to format the info field #F# ? ( ( ( #U8# ^ 0xff ) << ( 8 * #SCL# ) ) ^ 0xffffffff ) : ( #U8# << ( 8 * #SCL# ) )
//
static void EMITU8_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%d";
    sprintf(tmp, fmt, info->F ? ( ( ( info->U8 ^ 0xff ) << ( 8 * info->SCL ) ) ^ 0xffffffff ) : ( info->U8 << ( 8 * info->SCL ) ));
    putString(result, tmp);
}
//
// Function to format the info field #UI#
//
static void EMITUI_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->UI);
    putString(result, tmp);
}
//
// Function to format the info field #UI5#
//
static void EMITUI5_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->UI5);
    putString(result, tmp);
}
//
// Function to format the info field #UI7#
//
static void EMITUI7_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->UI7);
    putString(result, tmp);
}
//
// Function to format the info field #UIM#
//
static void EMITUIM_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "%u";
    sprintf(tmp, fmt, info->UIM);
    putString(result, tmp);
}
//
// Function to format the info field #VRA#
//
static void EMITVRA_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "v%d";
    sprintf(tmp, fmt, info->VRA);
    putString(result, tmp);
}
//
// Function to format the info field #VRB#
//
static void EMITVRB_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "v%d";
    sprintf(tmp, fmt, info->VRB);
    putString(result, tmp);
}
//
// Function to format the info field #VRC#
//
static void EMITVRC_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "v%d";
    sprintf(tmp, fmt, info->VRC);
    putString(result, tmp);
}
//
// Function to format the info field #VRS#
//
static void EMITVRS_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "v%d";
    sprintf(tmp, fmt, info->VRS);
    putString(result, tmp);
}
//
// Function to format the info field #VRT#
//
static void EMITVRT_FN(char **result, ppc32InstructionInfoP info) {
    char tmp[32];
    const char *fmt = "v%d";
    sprintf(tmp, fmt, info->VRT);
    putString(result, tmp);
}

//
// generate disassembler state machine
//
static void disassembleFormat(
    ppc32P ppc32,
    ppc32InstructionInfoP info,
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
             case EMITAALK_CASE:
                 EMITAALK_FN(result, info);
                 break;

             case EMITARX_CASE:
                 EMITARX_FN(result, info);
                 break;

             case EMITARY_CASE:
                 EMITARY_FN(result, info);
                 break;

             case EMITBA_CASE:
                 EMITBA_FN(result, info);
                 break;

             case EMITBB_CASE:
                 EMITBB_FN(result, info);
                 break;

             case EMITBC_CASE:
                 EMITBC_FN(result, info);
                 break;

             case EMITBD_CASE:
                 EMITBD_FN(result, info);
                 break;

             case EMITBD24_CASE:
                 EMITBD24_FN(result, info);
                 break;

             case EMITBD8_CASE:
                 EMITBD8_FN(result, info);
                 break;

             case EMITBF_CASE:
                 EMITBF_FN(result, info);
                 break;

             case EMITBF32_CASE:
                 EMITBF32_FN(result, info);
                 break;

             case EMITBFA_CASE:
                 EMITBFA_FN(result, info);
                 break;

             case EMITBFU_CASE:
                 EMITBFU_FN(result, info);
                 break;

             case EMITBI_CASE:
                 EMITBI_FN(result, info);
                 break;

             case EMITBI16_CASE:
                 EMITBI16_FN(result, info);
                 break;

             case EMITBI32_CASE:
                 EMITBI32_FN(result, info);
                 break;

             case EMITBL_CASE:
                 EMITBL_FN(result, info);
                 break;

             case EMITBO16_CASE:
                 EMITBO16_FN(result, info);
                 break;

             case EMITBO32_CASE:
                 EMITBO32_FN(result, info);
                 break;

             case EMITBO_0_CASE:
                 EMITBO_0_FN(result, info);
                 break;

             case EMITBO_1_CASE:
                 EMITBO_1_FN(result, info);
                 break;

             case EMITBT_CASE:
                 EMITBT_FN(result, info);
                 break;

             case EMITBW_CASE:
                 EMITBW_FN(result, info);
                 break;

             case EMITCT_CASE:
                 EMITCT_FN(result, info);
                 break;

             case EMITD_CASE:
                 EMITD_FN(result, info);
                 break;

             case EMITD8_CASE:
                 EMITD8_FN(result, info);
                 break;

             case EMITDCM_CASE:
                 EMITDCM_FN(result, info);
                 break;

             case EMITDCR_CASE:
                 EMITDCR_FN(result, info);
                 break;

             case EMITDQ_CASE:
                 EMITDQ_FN(result, info);
                 break;

             case EMITDS_CASE:
                 EMITDS_FN(result, info);
                 break;

             case EMITDUI_CASE:
                 EMITDUI_FN(result, info);
                 break;

             case EMITDUIS_CASE:
                 EMITDUIS_FN(result, info);
                 break;

             case EMITE_CASE:
                 EMITE_FN(result, info);
                 break;

             case EMITEH_CASE:
                 EMITEH_FN(result, info);
                 break;

             case EMITFLM_CASE:
                 EMITFLM_FN(result, info);
                 break;

             case EMITFRA_CASE:
                 EMITFRA_FN(result, info);
                 break;

             case EMITFRAP_CASE:
                 EMITFRAP_FN(result, info);
                 break;

             case EMITFRB_CASE:
                 EMITFRB_FN(result, info);
                 break;

             case EMITFRBP_CASE:
                 EMITFRBP_FN(result, info);
                 break;

             case EMITFRC_CASE:
                 EMITFRC_FN(result, info);
                 break;

             case EMITFRS_CASE:
                 EMITFRS_FN(result, info);
                 break;

             case EMITFRT_CASE:
                 EMITFRT_FN(result, info);
                 break;

             case EMITFRTP_CASE:
                 EMITFRTP_FN(result, info);
                 break;

             case EMITFXM_CASE:
                 EMITFXM_FN(result, info);
                 break;

             case EMITIH_CASE:
                 EMITIH_FN(result, info);
                 break;

             case EMITLEV_CASE:
                 EMITLEV_FN(result, info);
                 break;

             case EMITLI_CASE:
                 EMITLI_FN(result, info);
                 break;

             case EMITLI20_CASE:
                 EMITLI20_FN(result, info);
                 break;

             case EMITLK_CASE:
                 EMITLK_FN(result, info);
                 break;

             case EMITMB_CASE:
                 EMITMB_FN(result, info);
                 break;

             case EMITME_CASE:
                 EMITME_FN(result, info);
                 break;

             case EMITMO_CASE:
                 EMITMO_FN(result, info);
                 break;

             case EMITNB_CASE:
                 EMITNB_FN(result, info);
                 break;

             case EMITOIM5_CASE:
                 EMITOIM5_FN(result, info);
                 break;

             case EMITOP_CASE:
                 EMITOP_FN(result, info);
                 break;

             case EMITPMRN_CASE:
                 EMITPMRN_FN(result, info);
                 break;

             case EMITR_CASE:
                 EMITR_FN(result, info);
                 break;

             case EMITRA_CASE:
                 EMITRA_FN(result, info);
                 break;

             case EMITRA_AL_CASE:
                 EMITRA_AL_FN(result, info);
                 break;

             case EMITRB_CASE:
                 EMITRB_FN(result, info);
                 break;

             case EMITRMC_CASE:
                 EMITRMC_FN(result, info);
                 break;

             case EMITRS_CASE:
                 EMITRS_FN(result, info);
                 break;

             case EMITRSP_CASE:
                 EMITRSP_FN(result, info);
                 break;

             case EMITRT_CASE:
                 EMITRT_FN(result, info);
                 break;

             case EMITRTP_CASE:
                 EMITRTP_FN(result, info);
                 break;

             case EMITRX_CASE:
                 EMITRX_FN(result, info);
                 break;

             case EMITRY_CASE:
                 EMITRY_FN(result, info);
                 break;

             case EMITRZ_CASE:
                 EMITRZ_FN(result, info);
                 break;

             case EMITS_CASE:
                 EMITS_FN(result, info);
                 break;

             case EMITS8_CASE:
                 EMITS8_FN(result, info);
                 break;

             case EMITSD4_CASE:
                 EMITSD4_FN(result, info);
                 break;

             case EMITSH_CASE:
                 EMITSH_FN(result, info);
                 break;

             case EMITSHB_CASE:
                 EMITSHB_FN(result, info);
                 break;

             case EMITSI_CASE:
                 EMITSI_FN(result, info);
                 break;

             case EMITSIM_CASE:
                 EMITSIM_FN(result, info);
                 break;

             case EMITSP_CASE:
                 EMITSP_FN(result, info);
                 break;

             case EMITSPR_CASE:
                 EMITSPR_FN(result, info);
                 break;

             case EMITSR_CASE:
                 EMITSR_FN(result, info);
                 break;

             case EMITTE_CASE:
                 EMITTE_FN(result, info);
                 break;

             case EMITTH_CASE:
                 EMITTH_FN(result, info);
                 break;

             case EMITTO_CASE:
                 EMITTO_FN(result, info);
                 break;

             case EMITU_CASE:
                 EMITU_FN(result, info);
                 break;

             case EMITU8_CASE:
                 EMITU8_FN(result, info);
                 break;

             case EMITUI_CASE:
                 EMITUI_FN(result, info);
                 break;

             case EMITUI5_CASE:
                 EMITUI5_FN(result, info);
                 break;

             case EMITUI7_CASE:
                 EMITUI7_FN(result, info);
                 break;

             case EMITUIM_CASE:
                 EMITUIM_FN(result, info);
                 break;

             case EMITVRA_CASE:
                 EMITVRA_FN(result, info);
                 break;

             case EMITVRB_CASE:
                 EMITVRB_FN(result, info);
                 break;

             case EMITVRC_CASE:
                 EMITVRC_FN(result, info);
                 break;

             case EMITVRS_CASE:
                 EMITVRS_FN(result, info);
                 break;

             case EMITVRT_CASE:
                 EMITVRT_FN(result, info);
                 break;

             default:
                 putChar(result, ch);
                 break;
        }
    }
}

//
// ppc32 disassembler, decoded instruction interface
//
const char *ppc32DisassembleInfo(ppc32P ppc32, ppc32InstructionInfoP info) {
    static char result[256];
    const char *format;
    char *tail = result;

    //
    // disassemble using the format for the type
    //
    if((format=formats[info->type])) {
        disassembleFormat(ppc32, info, &tail, format);
    } else {
        sprintf(result, "??? instruction:0x" FMT_640Nx, info->instruction);
    }
    return result;
}

//
// ppc32 disassembler
//
VMI_DISASSEMBLE_FN(ppc32Dis) {
    // static buffer to hold disassembly result
    ppc32P ppc32 = (ppc32P)processor;
    ppc32InstructionInfo info = {0};
    // get instruction and instruction type
    ppc32Decode(ppc32, thisPC, &info);
    // return disassembled instruction
    return ppc32DisassembleInfo(ppc32, &info);
}

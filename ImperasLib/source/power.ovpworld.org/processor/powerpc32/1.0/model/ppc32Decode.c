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
#include "ppc32Decode.h"
#include "ppc32Instructions.h"

//
// Generate the instruction opcode table
//
static const char *opcode[PPC32_IT_LAST+1] = {
    //
    // Instruction Opcode A1 Insns
    //
    [PPC32_IT_FMADD_A1] = "fmadd",
    [PPC32_IT_FMADDRC_A1] = "fmadd.",
    [PPC32_IT_FMADDS_A1] = "fmadds",
    [PPC32_IT_FMADDSRC_A1] = "fmadds.",
    [PPC32_IT_FMSUB_A1] = "fmsub",
    [PPC32_IT_FMSUBRC_A1] = "fmsub.",
    [PPC32_IT_FMSUBS_A1] = "fmsubs",
    [PPC32_IT_FMSUBSRC_A1] = "fmsubs.",
    [PPC32_IT_FNMADD_A1] = "fnmadd",
    [PPC32_IT_FNMADDRC_A1] = "fnmadd.",
    [PPC32_IT_FNMADDS_A1] = "fnmadds",
    [PPC32_IT_FNMADDSRC_A1] = "fnmadds.",
    [PPC32_IT_FNMSUB_A1] = "fnmsub",
    [PPC32_IT_FNMSUBRC_A1] = "fnmsub.",
    [PPC32_IT_FNMSUBS_A1] = "fnmsubs",
    [PPC32_IT_FNMSUBSRC_A1] = "fnmsubs.",
    [PPC32_IT_FSEL_A1] = "fsel",
    [PPC32_IT_FSELRC_A1] = "fsel.",

    //
    // Instruction Opcode A2 Insns
    //
    [PPC32_IT_FADD_A2] = "fadd",
    [PPC32_IT_FADDRC_A2] = "fadd.",
    [PPC32_IT_FADDS_A2] = "fadds",
    [PPC32_IT_FADDSRC_A2] = "fadds.",
    [PPC32_IT_FDIV_A2] = "fdiv",
    [PPC32_IT_FDIVRC_A2] = "fdiv.",
    [PPC32_IT_FDIVS_A2] = "fdivs",
    [PPC32_IT_FDIVSRC_A2] = "fdivs.",
    [PPC32_IT_FSUB_A2] = "fsub",
    [PPC32_IT_FSUBRC_A2] = "fsub.",
    [PPC32_IT_FSUBS_A2] = "fsubs",
    [PPC32_IT_FSUBSRC_A2] = "fsubs.",

    //
    // Instruction Opcode A3 Insns
    //
    [PPC32_IT_FMUL_A3] = "fmul",
    [PPC32_IT_FMULRC_A3] = "fmul.",
    [PPC32_IT_FMULS_A3] = "fmuls",
    [PPC32_IT_FMULSRC_A3] = "fmuls.",

    //
    // Instruction Opcode A4 Insns
    //
    [PPC32_IT_FSQRT_A4] = "fsqrt",
    [PPC32_IT_FSQRTRC_A4] = "fsqrt.",
    [PPC32_IT_FSQRTS_A4] = "fsqrts",
    [PPC32_IT_FSQRTSRC_A4] = "fsqrts.",

    //
    // Instruction Opcode A5 Insns
    //
    [PPC32_IT_FRE_A5] = "fre",
    [PPC32_IT_FRERC_A5] = "fre.",
    [PPC32_IT_FRES_A5] = "fres",
    [PPC32_IT_FRESRC_A5] = "fres.",
    [PPC32_IT_FRSQRTE_A5] = "frsqrte",
    [PPC32_IT_FRSQRTERC_A5] = "frsqrte.",
    [PPC32_IT_FRSQRTES_A5] = "frsqrtes",
    [PPC32_IT_FRSQRTESRC_A5] = "frsqrtes.",

    //
    // Instruction Opcode A6 Insns
    //
    [PPC32_IT_ISEL_A6] = "isel",

    //
    // Instruction Opcode B1 Insns
    //
    [PPC32_IT_BC_B1] = "bc",

    //
    // Instruction Opcode BD15 Insns
    //
    [PPC32_IT_E_BC_BD15] = "e_bc",

    //
    // Instruction Opcode BD24 Insns
    //
    [PPC32_IT_E_B_BD24] = "e_b",

    //
    // Instruction Opcode BD81 Insns
    //
    [PPC32_IT_SE_BC_BD81] = "se_bc",

    //
    // Instruction Opcode BD82 Insns
    //
    [PPC32_IT_SE_B_BD82] = "se_b",

    //
    // Instruction Opcode C_0 Insns
    //
    [PPC32_IT_SE_ILLEGAL_C_0] = "se_illegal",
    [PPC32_IT_SE_ISYNC_C_0] = "se_isync",
    [PPC32_IT_SE_RFCI_C_0] = "se_rfci",
    [PPC32_IT_SE_RFDI_C_0] = "se_rfdi",
    [PPC32_IT_SE_RFI_C_0] = "se_rfi",
    [PPC32_IT_SE_RFMCI_C_0] = "se_rfmci",
    [PPC32_IT_SE_SC_C_0] = "se_sc",

    //
    // Instruction Opcode C_1 Insns
    //
    [PPC32_IT_SE_BCTR_C_1] = "se_bctr",
    [PPC32_IT_SE_BLR_C_1] = "se_blr",

    //
    // Instruction Opcode D1 Insns
    //
    [PPC32_IT_E_LBZ_D1] = "e_lbz",
    [PPC32_IT_E_LHA_D1] = "e_lha",
    [PPC32_IT_E_LHZ_D1] = "e_lhz",
    [PPC32_IT_E_LWZ_D1] = "e_lwz",
    [PPC32_IT_LBZ_D1] = "lbz",
    [PPC32_IT_LBZU_D1] = "lbzu",
    [PPC32_IT_LHA_D1] = "lha",
    [PPC32_IT_LHAU_D1] = "lhau",
    [PPC32_IT_LHZ_D1] = "lhz",
    [PPC32_IT_LHZU_D1] = "lhzu",
    [PPC32_IT_LMW_D1] = "lmw",
    [PPC32_IT_LWZ_D1] = "lwz",
    [PPC32_IT_LWZU_D1] = "lwzu",

    //
    // Instruction Opcode D2 Insns
    //
    [PPC32_IT_E_ADD16I_D2] = "e_add16i",

    //
    // Instruction Opcode D2_0 Insns
    //
    [PPC32_IT_ADDI_D2_0] = "addi",
    [PPC32_IT_ADDIC_D2_0] = "addic",
    [PPC32_IT_ADDICRC_D2_0] = "addic.",
    [PPC32_IT_ADDIS_D2_0] = "addis",
    [PPC32_IT_MULLI_D2_0] = "mulli",
    [PPC32_IT_SUBFIC_D2_0] = "subfic",

    //
    // Instruction Opcode D2_1 Insns
    //
    [PPC32_IT_LI_D2_1] = "li",
    [PPC32_IT_LIS_D2_1] = "lis",

    //
    // Instruction Opcode D3 Insns
    //
    [PPC32_IT_E_STB_D3] = "e_stb",
    [PPC32_IT_E_STH_D3] = "e_sth",
    [PPC32_IT_E_STW_D3] = "e_stw",
    [PPC32_IT_STB_D3] = "stb",
    [PPC32_IT_STBU_D3] = "stbu",
    [PPC32_IT_STH_D3] = "sth",
    [PPC32_IT_STHU_D3] = "sthu",
    [PPC32_IT_STMW_D3] = "stmw",
    [PPC32_IT_STW_D3] = "stw",
    [PPC32_IT_STWU_D3] = "stwu",

    //
    // Instruction Opcode D4 Insns
    //
    [PPC32_IT_ANDIRC_D4] = "andi.",
    [PPC32_IT_ANDISRC_D4] = "andis.",
    [PPC32_IT_ORI_D4] = "ori",
    [PPC32_IT_ORIS_D4] = "oris",
    [PPC32_IT_XORI_D4] = "xori",
    [PPC32_IT_XORIS_D4] = "xoris",

    //
    // Instruction Opcode D5_0 Insns
    //
    [PPC32_IT_CMPWI_D5_0] = "cmpwi",

    //
    // Instruction Opcode D5_1 Insns
    //
    [PPC32_IT_CMPI_D5_1] = "cmpi",

    //
    // Instruction Opcode D6_0 Insns
    //
    [PPC32_IT_CMPLWI_D6_0] = "cmplwi",

    //
    // Instruction Opcode D6_1 Insns
    //
    [PPC32_IT_CMPLI_D6_1] = "cmpli",

    //
    // Instruction Opcode D7 Insns
    //
    [PPC32_IT_TWI_D7] = "twi",

    //
    // Instruction Opcode D8 Insns
    //
    [PPC32_IT_LFD_D8] = "lfd",
    [PPC32_IT_LFDU_D8] = "lfdu",
    [PPC32_IT_LFS_D8] = "lfs",
    [PPC32_IT_LFSU_D8] = "lfsu",

    //
    // Instruction Opcode D8_0 Insns
    //
    [PPC32_IT_E_LBZU_D8_0] = "e_lbzu",
    [PPC32_IT_E_LHAU_D8_0] = "e_lhau",
    [PPC32_IT_E_LHZU_D8_0] = "e_lhzu",
    [PPC32_IT_E_LMW_D8_0] = "e_lmw",
    [PPC32_IT_E_LWZU_D8_0] = "e_lwzu",

    //
    // Instruction Opcode D8_1 Insns
    //
    [PPC32_IT_E_STBU_D8_1] = "e_stbu",
    [PPC32_IT_E_STHU_D8_1] = "e_sthu",
    [PPC32_IT_E_STMW_D8_1] = "e_stmw",
    [PPC32_IT_E_STWU_D8_1] = "e_stwu",

    //
    // Instruction Opcode D9 Insns
    //
    [PPC32_IT_STFD_D9] = "stfd",
    [PPC32_IT_STFDU_D9] = "stfdu",
    [PPC32_IT_STFS_D9] = "stfs",
    [PPC32_IT_STFSU_D9] = "stfsu",

    //
    // Instruction Opcode DQ1 Insns
    //
    [PPC32_IT_LQ_DQ1] = "lq",

    //
    // Instruction Opcode DS1 Insns
    //

    //
    // Instruction Opcode DS2 Insns
    //

    //
    // Instruction Opcode DS3 Insns
    //
    [PPC32_IT_STQ_DS3] = "stq",

    //
    // Instruction Opcode DS4 Insns
    //

    //
    // Instruction Opcode DS5 Insns
    //

    //
    // Instruction Opcode EVS Insns
    //
    [PPC32_IT_EVSEL_EVS] = "evsel",

    //
    // Instruction Opcode EVX1 Insns
    //
    [PPC32_IT_BRINC_EVX1] = "brinc",
    [PPC32_IT_EVSTDDX_EVX1] = "evstddx",
    [PPC32_IT_EVSTDHX_EVX1] = "evstdhx",
    [PPC32_IT_EVSTDWX_EVX1] = "evstdwx",
    [PPC32_IT_EVSTWHEX_EVX1] = "evstwhex",
    [PPC32_IT_EVSTWHOX_EVX1] = "evstwhox",
    [PPC32_IT_EVSTWWEX_EVX1] = "evstwwex",
    [PPC32_IT_EVSTWWOX_EVX1] = "evstwwox",

    //
    // Instruction Opcode EVX2 Insns
    //

    //
    // Instruction Opcode EVX2_1 Insns
    //

    //
    // Instruction Opcode EVX2_2 Insns
    //
    [PPC32_IT_EVSTWHE_EVX2_2] = "evstwhe",
    [PPC32_IT_EVSTWHO_EVX2_2] = "evstwho",
    [PPC32_IT_EVSTWWE_EVX2_2] = "evstwwe",
    [PPC32_IT_EVSTWWO_EVX2_2] = "evstwwo",

    //
    // Instruction Opcode EVX2_3 Insns
    //
    [PPC32_IT_EVSTDD_EVX2_3] = "evstdd",
    [PPC32_IT_EVSTDH_EVX2_3] = "evstdh",
    [PPC32_IT_EVSTDW_EVX2_3] = "evstdw",

    //
    // Instruction Opcode EVX3 Insns
    //
    [PPC32_IT_EFDCFS_EVX3] = "efdcfs",
    [PPC32_IT_EFDCFSF_EVX3] = "efdcfsf",
    [PPC32_IT_EFDCFSI_EVX3] = "efdcfsi",
    [PPC32_IT_EFDCFSID_EVX3] = "efdcfsid",
    [PPC32_IT_EFDCFUF_EVX3] = "efdcfuf",
    [PPC32_IT_EFDCFUI_EVX3] = "efdcfui",
    [PPC32_IT_EFDCFUID_EVX3] = "efdcfuid",
    [PPC32_IT_EFDCTSF_EVX3] = "efdctsf",
    [PPC32_IT_EFDCTSI_EVX3] = "efdctsi",
    [PPC32_IT_EFDCTSIDZ_EVX3] = "efdctsidz",
    [PPC32_IT_EFDCTSIZ_EVX3] = "efdctsiz",
    [PPC32_IT_EFDCTUF_EVX3] = "efdctuf",
    [PPC32_IT_EFDCTUI_EVX3] = "efdctui",
    [PPC32_IT_EFDCTUIDZ_EVX3] = "efdctuidz",
    [PPC32_IT_EFDCTUIZ_EVX3] = "efdctuiz",
    [PPC32_IT_EFSCFD_EVX3] = "efscfd",
    [PPC32_IT_EFSCFSF_EVX3] = "efscfsf",
    [PPC32_IT_EFSCFSI_EVX3] = "efscfsi",
    [PPC32_IT_EFSCFUF_EVX3] = "efscfuf",
    [PPC32_IT_EFSCFUI_EVX3] = "efscfui",
    [PPC32_IT_EFSCTSF_EVX3] = "efsctsf",
    [PPC32_IT_EFSCTSI_EVX3] = "efsctsi",
    [PPC32_IT_EFSCTSIZ_EVX3] = "efsctsiz",
    [PPC32_IT_EFSCTUF_EVX3] = "efsctuf",
    [PPC32_IT_EFSCTUI_EVX3] = "efsctui",
    [PPC32_IT_EFSCTUIZ_EVX3] = "efsctuiz",
    [PPC32_IT_EVFSCFSF_EVX3] = "evfscfsf",
    [PPC32_IT_EVFSCFSI_EVX3] = "evfscfsi",
    [PPC32_IT_EVFSCFUF_EVX3] = "evfscfuf",
    [PPC32_IT_EVFSCFUI_EVX3] = "evfscfui",
    [PPC32_IT_EVFSCTSF_EVX3] = "evfsctsf",
    [PPC32_IT_EVFSCTSI_EVX3] = "evfsctsi",
    [PPC32_IT_EVFSCTSIZ_EVX3] = "evfsctsiz",
    [PPC32_IT_EVFSCTUF_EVX3] = "evfsctuf",
    [PPC32_IT_EVFSCTUI_EVX3] = "evfsctui",
    [PPC32_IT_EVFSCTUIZ_EVX3] = "evfsctuiz",

    //
    // Instruction Opcode EVX4 Insns
    //
    [PPC32_IT_EFDADD_EVX4] = "efdadd",
    [PPC32_IT_EFDDIV_EVX4] = "efddiv",
    [PPC32_IT_EFDMUL_EVX4] = "efdmul",
    [PPC32_IT_EFDSUB_EVX4] = "efdsub",
    [PPC32_IT_EFSADD_EVX4] = "efsadd",
    [PPC32_IT_EFSDIV_EVX4] = "efsdiv",
    [PPC32_IT_EFSMUL_EVX4] = "efsmul",
    [PPC32_IT_EFSSUB_EVX4] = "efssub",
    [PPC32_IT_EVADDW_EVX4] = "evaddw",
    [PPC32_IT_EVAND_EVX4] = "evand",
    [PPC32_IT_EVANDC_EVX4] = "evandc",
    [PPC32_IT_EVDIVWS_EVX4] = "evdivws",
    [PPC32_IT_EVDIVWU_EVX4] = "evdivwu",
    [PPC32_IT_EVEQV_EVX4] = "eveqv",
    [PPC32_IT_EVFSADD_EVX4] = "evfsadd",
    [PPC32_IT_EVFSDIV_EVX4] = "evfsdiv",
    [PPC32_IT_EVFSMUL_EVX4] = "evfsmul",
    [PPC32_IT_EVFSSUB_EVX4] = "evfssub",
    [PPC32_IT_EVLDDX_EVX4] = "evlddx",
    [PPC32_IT_EVLDHX_EVX4] = "evldhx",
    [PPC32_IT_EVLDWX_EVX4] = "evldwx",
    [PPC32_IT_EVLHHESPLATX_EVX4] = "evlhhesplatx",
    [PPC32_IT_EVLHHOSSPLATX_EVX4] = "evlhhossplatx",
    [PPC32_IT_EVLHHOUSPLATX_EVX4] = "evlhhousplatx",
    [PPC32_IT_EVLWHEX_EVX4] = "evlwhex",
    [PPC32_IT_EVLWHOSX_EVX4] = "evlwhosx",
    [PPC32_IT_EVLWHOUX_EVX4] = "evlwhoux",
    [PPC32_IT_EVLWHSPLATX_EVX4] = "evlwhsplatx",
    [PPC32_IT_EVLWWSPLATX_EVX4] = "evlwwsplatx",
    [PPC32_IT_EVMERGEHI_EVX4] = "evmergehi",
    [PPC32_IT_EVMERGEHILO_EVX4] = "evmergehilo",
    [PPC32_IT_EVMERGELO_EVX4] = "evmergelo",
    [PPC32_IT_EVMERGELOHI_EVX4] = "evmergelohi",
    [PPC32_IT_EVMHEGSMFAA_EVX4] = "evmhegsmfaa",
    [PPC32_IT_EVMHEGSMFAN_EVX4] = "evmhegsmfan",
    [PPC32_IT_EVMHEGSMIAA_EVX4] = "evmhegsmiaa",
    [PPC32_IT_EVMHEGSMIAN_EVX4] = "evmhegsmian",
    [PPC32_IT_EVMHEGUMIAA_EVX4] = "evmhegumiaa",
    [PPC32_IT_EVMHEGUMIAN_EVX4] = "evmhegumian",
    [PPC32_IT_EVMHESMF_EVX4] = "evmhesmf",
    [PPC32_IT_EVMHESMFA_EVX4] = "evmhesmfa",
    [PPC32_IT_EVMHESMFAAW_EVX4] = "evmhesmfaaw",
    [PPC32_IT_EVMHESMFANW_EVX4] = "evmhesmfanw",
    [PPC32_IT_EVMHESMI_EVX4] = "evmhesmi",
    [PPC32_IT_EVMHESMIA_EVX4] = "evmhesmia",
    [PPC32_IT_EVMHESMIAAW_EVX4] = "evmhesmiaaw",
    [PPC32_IT_EVMHESMIANW_EVX4] = "evmhesmianw",
    [PPC32_IT_EVMHESSF_EVX4] = "evmhessf",
    [PPC32_IT_EVMHESSFA_EVX4] = "evmhessfa",
    [PPC32_IT_EVMHESSFAAW_EVX4] = "evmhessfaaw",
    [PPC32_IT_EVMHESSFANW_EVX4] = "evmhessfanw",
    [PPC32_IT_EVMHESSIAAW_EVX4] = "evmhessiaaw",
    [PPC32_IT_EVMHESSIANW_EVX4] = "evmhessianw",
    [PPC32_IT_EVMHEUMI_EVX4] = "evmheumi",
    [PPC32_IT_EVMHEUMIA_EVX4] = "evmheumia",
    [PPC32_IT_EVMHEUMIAAW_EVX4] = "evmheumiaaw",
    [PPC32_IT_EVMHEUMIANW_EVX4] = "evmheumianw",
    [PPC32_IT_EVMHEUSIAAW_EVX4] = "evmheusiaaw",
    [PPC32_IT_EVMHEUSIANW_EVX4] = "evmheusianw",
    [PPC32_IT_EVMHOGSMFAA_EVX4] = "evmhogsmfaa",
    [PPC32_IT_EVMHOGSMFAN_EVX4] = "evmhogsmfan",
    [PPC32_IT_EVMHOGSMIAA_EVX4] = "evmhogsmiaa",
    [PPC32_IT_EVMHOGSMIAN_EVX4] = "evmhogsmian",
    [PPC32_IT_EVMHOGUMIAA_EVX4] = "evmhogumiaa",
    [PPC32_IT_EVMHOGUMIAN_EVX4] = "evmhogumian",
    [PPC32_IT_EVMHOSMF_EVX4] = "evmhosmf",
    [PPC32_IT_EVMHOSMFA_EVX4] = "evmhosmfa",
    [PPC32_IT_EVMHOSMFAAW_EVX4] = "evmhosmfaaw",
    [PPC32_IT_EVMHOSMFANW_EVX4] = "evmhosmfanw",
    [PPC32_IT_EVMHOSMI_EVX4] = "evmhosmi",
    [PPC32_IT_EVMHOSMIA_EVX4] = "evmhosmia",
    [PPC32_IT_EVMHOSMIAAW_EVX4] = "evmhosmiaaw",
    [PPC32_IT_EVMHOSMIANW_EVX4] = "evmhosmianw",
    [PPC32_IT_EVMHOSSF_EVX4] = "evmhossf",
    [PPC32_IT_EVMHOSSFA_EVX4] = "evmhossfa",
    [PPC32_IT_EVMHOSSFAAW_EVX4] = "evmhossfaaw",
    [PPC32_IT_EVMHOSSFANW_EVX4] = "evmhossfanw",
    [PPC32_IT_EVMHOSSIAAW_EVX4] = "evmhossiaaw",
    [PPC32_IT_EVMHOSSIANW_EVX4] = "evmhossianw",
    [PPC32_IT_EVMHOUMI_EVX4] = "evmhoumi",
    [PPC32_IT_EVMHOUMIA_EVX4] = "evmhoumia",
    [PPC32_IT_EVMHOUMIAAW_EVX4] = "evmhoumiaaw",
    [PPC32_IT_EVMHOUMIANW_EVX4] = "evmhoumianw",
    [PPC32_IT_EVMHOUSIAAW_EVX4] = "evmhousiaaw",
    [PPC32_IT_EVMHOUSIANW_EVX4] = "evmhousianw",
    [PPC32_IT_EVMWHSMF_EVX4] = "evmwhsmf",
    [PPC32_IT_EVMWHSMFA_EVX4] = "evmwhsmfa",
    [PPC32_IT_EVMWHSMI_EVX4] = "evmwhsmi",
    [PPC32_IT_EVMWHSMIA_EVX4] = "evmwhsmia",
    [PPC32_IT_EVMWHSSF_EVX4] = "evmwhssf",
    [PPC32_IT_EVMWHSSFA_EVX4] = "evmwhssfa",
    [PPC32_IT_EVMWHUMI_EVX4] = "evmwhumi",
    [PPC32_IT_EVMWHUMIA_EVX4] = "evmwhumia",
    [PPC32_IT_EVMWLSMIAAW_EVX4] = "evmwlsmiaaw",
    [PPC32_IT_EVMWLSMIANW_EVX4] = "evmwlsmianw",
    [PPC32_IT_EVMWLSSIAAW_EVX4] = "evmwlssiaaw",
    [PPC32_IT_EVMWLSSIANW_EVX4] = "evmwlssianw",
    [PPC32_IT_EVMWLUMI_EVX4] = "evmwlumi",
    [PPC32_IT_EVMWLUMIA_EVX4] = "evmwlumia",
    [PPC32_IT_EVMWLUMIAAW_EVX4] = "evmwlumiaaw",
    [PPC32_IT_EVMWLUMIANW_EVX4] = "evmwlumianw",
    [PPC32_IT_EVMWLUSIAAW_EVX4] = "evmwlusiaaw",
    [PPC32_IT_EVMWLUSIANW_EVX4] = "evmwlusianw",
    [PPC32_IT_EVMWSMF_EVX4] = "evmwsmf",
    [PPC32_IT_EVMWSMFA_EVX4] = "evmwsmfa",
    [PPC32_IT_EVMWSMFAA_EVX4] = "evmwsmfaa",
    [PPC32_IT_EVMWSMFAN_EVX4] = "evmwsmfan",
    [PPC32_IT_EVMWSMI_EVX4] = "evmwsmi",
    [PPC32_IT_EVMWSMIA_EVX4] = "evmwsmia",
    [PPC32_IT_EVMWSMIAA_EVX4] = "evmwsmiaa",
    [PPC32_IT_EVMWSMIAN_EVX4] = "evmwsmian",
    [PPC32_IT_EVMWSSF_EVX4] = "evmwssf",
    [PPC32_IT_EVMWSSFA_EVX4] = "evmwssfa",
    [PPC32_IT_EVMWSSFAA_EVX4] = "evmwssfaa",
    [PPC32_IT_EVMWSSFAN_EVX4] = "evmwssfan",
    [PPC32_IT_EVMWUMI_EVX4] = "evmwumi",
    [PPC32_IT_EVMWUMIA_EVX4] = "evmwumia",
    [PPC32_IT_EVMWUMIAA_EVX4] = "evmwumiaa",
    [PPC32_IT_EVMWUMIAN_EVX4] = "evmwumian",
    [PPC32_IT_EVNAND_EVX4] = "evnand",
    [PPC32_IT_EVNOR_EVX4] = "evnor",
    [PPC32_IT_EVOR_EVX4] = "evor",
    [PPC32_IT_EVORC_EVX4] = "evorc",
    [PPC32_IT_EVRLW_EVX4] = "evrlw",
    [PPC32_IT_EVSLW_EVX4] = "evslw",
    [PPC32_IT_EVSRWS_EVX4] = "evsrws",
    [PPC32_IT_EVSRWU_EVX4] = "evsrwu",
    [PPC32_IT_EVSUBFW_EVX4] = "evsubfw",
    [PPC32_IT_EVXOR_EVX4] = "evxor",

    //
    // Instruction Opcode EVX5 Insns
    //
    [PPC32_IT_EFDABS_EVX5] = "efdabs",
    [PPC32_IT_EFDNABS_EVX5] = "efdnabs",
    [PPC32_IT_EFDNEG_EVX5] = "efdneg",
    [PPC32_IT_EFSABS_EVX5] = "efsabs",
    [PPC32_IT_EFSNABS_EVX5] = "efsnabs",
    [PPC32_IT_EFSNEG_EVX5] = "efsneg",
    [PPC32_IT_EVABS_EVX5] = "evabs",
    [PPC32_IT_EVADDSMIAAW_EVX5] = "evaddsmiaaw",
    [PPC32_IT_EVADDSSIAAW_EVX5] = "evaddssiaaw",
    [PPC32_IT_EVADDUMIAAW_EVX5] = "evaddumiaaw",
    [PPC32_IT_EVADDUSIAAW_EVX5] = "evaddusiaaw",
    [PPC32_IT_EVCNTLSW_EVX5] = "evcntlsw",
    [PPC32_IT_EVCNTLZW_EVX5] = "evcntlzw",
    [PPC32_IT_EVEXTSB_EVX5] = "evextsb",
    [PPC32_IT_EVEXTSH_EVX5] = "evextsh",
    [PPC32_IT_EVFSABS_EVX5] = "evfsabs",
    [PPC32_IT_EVFSNABS_EVX5] = "evfsnabs",
    [PPC32_IT_EVFSNEG_EVX5] = "evfsneg",
    [PPC32_IT_EVMRA_EVX5] = "evmra",
    [PPC32_IT_EVNEG_EVX5] = "evneg",
    [PPC32_IT_EVRNDW_EVX5] = "evrndw",
    [PPC32_IT_EVSUBFSMIAAW_EVX5] = "evsubfsmiaaw",
    [PPC32_IT_EVSUBFSSIAAW_EVX5] = "evsubfssiaaw",
    [PPC32_IT_EVSUBFUMIAAW_EVX5] = "evsubfumiaaw",
    [PPC32_IT_EVSUBFUSIAAW_EVX5] = "evsubfusiaaw",

    //
    // Instruction Opcode EVX6_1 Insns
    //
    [PPC32_IT_EVADDIW_EVX6_1] = "evaddiw",

    //
    // Instruction Opcode EVX6_2 Insns
    //
    [PPC32_IT_EVSUBIFW_EVX6_2] = "evsubifw",

    //
    // Instruction Opcode EVX7 Insns
    //
    [PPC32_IT_EFDCMPEQ_EVX7] = "efdcmpeq",
    [PPC32_IT_EFDCMPGT_EVX7] = "efdcmpgt",
    [PPC32_IT_EFDCMPLT_EVX7] = "efdcmplt",
    [PPC32_IT_EFDTSTEQ_EVX7] = "efdtsteq",
    [PPC32_IT_EFDTSTGT_EVX7] = "efdtstgt",
    [PPC32_IT_EFDTSTLT_EVX7] = "efdtstlt",
    [PPC32_IT_EFSCMPEQ_EVX7] = "efscmpeq",
    [PPC32_IT_EFSCMPGT_EVX7] = "efscmpgt",
    [PPC32_IT_EFSCMPLT_EVX7] = "efscmplt",
    [PPC32_IT_EFSTSTEQ_EVX7] = "efststeq",
    [PPC32_IT_EFSTSTGT_EVX7] = "efststgt",
    [PPC32_IT_EFSTSTLT_EVX7] = "efststlt",
    [PPC32_IT_EVCMPEQ_EVX7] = "evcmpeq",
    [PPC32_IT_EVCMPGTS_EVX7] = "evcmpgts",
    [PPC32_IT_EVCMPGTU_EVX7] = "evcmpgtu",
    [PPC32_IT_EVCMPLTS_EVX7] = "evcmplts",
    [PPC32_IT_EVCMPLTU_EVX7] = "evcmpltu",
    [PPC32_IT_EVFSCMPEQ_EVX7] = "evfscmpeq",
    [PPC32_IT_EVFSCMPGT_EVX7] = "evfscmpgt",
    [PPC32_IT_EVFSCMPLT_EVX7] = "evfscmplt",
    [PPC32_IT_EVFSTSTEQ_EVX7] = "evfststeq",
    [PPC32_IT_EVFSTSTGT_EVX7] = "evfststgt",
    [PPC32_IT_EVFSTSTLT_EVX7] = "evfststlt",

    //
    // Instruction Opcode EVX8 Insns
    //
    [PPC32_IT_EVRLWI_EVX8] = "evrlwi",
    [PPC32_IT_EVSLWI_EVX8] = "evslwi",
    [PPC32_IT_EVSRWIS_EVX8] = "evsrwis",
    [PPC32_IT_EVSRWIU_EVX8] = "evsrwiu",

    //
    // Instruction Opcode EVX8_1 Insns
    //
    [PPC32_IT_EVLHHESPLAT_EVX8_1] = "evlhhesplat",
    [PPC32_IT_EVLHHOSSPLAT_EVX8_1] = "evlhhossplat",
    [PPC32_IT_EVLHHOUSPLAT_EVX8_1] = "evlhhousplat",

    //
    // Instruction Opcode EVX8_2 Insns
    //
    [PPC32_IT_EVLWHE_EVX8_2] = "evlwhe",
    [PPC32_IT_EVLWHOS_EVX8_2] = "evlwhos",
    [PPC32_IT_EVLWHOU_EVX8_2] = "evlwhou",
    [PPC32_IT_EVLWHSPLAT_EVX8_2] = "evlwhsplat",
    [PPC32_IT_EVLWWSPLAT_EVX8_2] = "evlwwsplat",

    //
    // Instruction Opcode EVX8_3 Insns
    //
    [PPC32_IT_EVLDD_EVX8_3] = "evldd",
    [PPC32_IT_EVLDH_EVX8_3] = "evldh",
    [PPC32_IT_EVLDW_EVX8_3] = "evldw",

    //
    // Instruction Opcode EVX9 Insns
    //
    [PPC32_IT_EVSPLATFI_EVX9] = "evsplatfi",
    [PPC32_IT_EVSPLATI_EVX9] = "evsplati",

    //
    // Instruction Opcode I1 Insns
    //
    [PPC32_IT_B_I1] = "b",

    //
    // Instruction Opcode I16A1 Insns
    //
    [PPC32_IT_E_ADD2IRC_I16A1] = "e_add2i.",
    [PPC32_IT_E_ADD2IS_I16A1] = "e_add2is",
    [PPC32_IT_E_CMP16I_I16A1] = "e_cmp16i",
    [PPC32_IT_E_CMPH16I_I16A1] = "e_cmph16i",
    [PPC32_IT_E_MULL2I_I16A1] = "e_mull2i",

    //
    // Instruction Opcode I16A2 Insns
    //
    [PPC32_IT_E_CMPHL16I_I16A2] = "e_cmphl16i",
    [PPC32_IT_E_CMPL16I_I16A2] = "e_cmpl16i",

    //
    // Instruction Opcode I16L Insns
    //
    [PPC32_IT_E_AND2IRC_I16L] = "e_and2i.",
    [PPC32_IT_E_AND2ISRC_I16L] = "e_and2is.",
    [PPC32_IT_E_LIS_I16L] = "e_lis",
    [PPC32_IT_E_OR2I_I16L] = "e_or2i",
    [PPC32_IT_E_OR2IS_I16L] = "e_or2is",

    //
    // Instruction Opcode IM5 Insns
    //
    [PPC32_IT_SE_ANDI_IM5] = "se_andi",
    [PPC32_IT_SE_BMASKI_IM5] = "se_bmaski",
    [PPC32_IT_SE_CMPI_IM5] = "se_cmpi",

    //
    // Instruction Opcode IM7 Insns
    //
    [PPC32_IT_SE_LI_IM7] = "se_li",

    //
    // Instruction Opcode LI20 Insns
    //
    [PPC32_IT_E_LI_LI20] = "e_li",

    //
    // Instruction Opcode M1_0 Insns
    //
    [PPC32_IT_RLWNM_M1_0] = "rlwnm",
    [PPC32_IT_RLWNMRC_M1_0] = "rlwnm.",

    //
    // Instruction Opcode M1_1 Insns
    //
    [PPC32_IT_RLWNMRC_0_M1_1] = "rotlw.",
    [PPC32_IT_RLWNM_0_M1_1] = "rotlw",

    //
    // Instruction Opcode M2_0 Insns
    //
    [PPC32_IT_E_RLWIMI_M2_0] = "e_rlwimi",
    [PPC32_IT_E_RLWINM_M2_0] = "e_rlwinm",
    [PPC32_IT_RLWIMI_M2_0] = "rlwimi",
    [PPC32_IT_RLWIMIRC_M2_0] = "rlwimi.",
    [PPC32_IT_RLWINM_M2_0] = "rlwinm",
    [PPC32_IT_RLWINMRC_M2_0] = "rlwinm.",

    //
    // Instruction Opcode M2_1 Insns
    //
    [PPC32_IT_RLWINMRC_0_M2_1] = "rotlwi.",
    [PPC32_IT_RLWINM_0_M2_1] = "rotlwi",

    //
    // Instruction Opcode OIM51_0 Insns
    //
    [PPC32_IT_SE_BCLRI_OIM51_0] = "se_bclri",
    [PPC32_IT_SE_BGENI_OIM51_0] = "se_bgeni",
    [PPC32_IT_SE_BSETI_OIM51_0] = "se_bseti",
    [PPC32_IT_SE_BTSTI_OIM51_0] = "se_btsti",
    [PPC32_IT_SE_SLWI_OIM51_0] = "se_slwi",
    [PPC32_IT_SE_SRAWI_OIM51_0] = "se_srawi",
    [PPC32_IT_SE_SRWI_OIM51_0] = "se_srwi",

    //
    // Instruction Opcode OIM51_1 Insns
    //
    [PPC32_IT_SE_ADDI_OIM51_1] = "se_addi",
    [PPC32_IT_SE_CMPLI_OIM51_1] = "se_cmpli",

    //
    // Instruction Opcode OIM52_0 Insns
    //
    [PPC32_IT_SE_SUBI_OIM52_0] = "se_subi",
    [PPC32_IT_SE_SUBIRC_OIM52_0] = "se_subi.",

    //
    // Instruction Opcode R1 Insns
    //
    [PPC32_IT_SE_EXTSB_R1] = "se_extsb",
    [PPC32_IT_SE_EXTSH_R1] = "se_extsh",
    [PPC32_IT_SE_EXTZB_R1] = "se_extzb",
    [PPC32_IT_SE_EXTZH_R1] = "se_extzh",
    [PPC32_IT_SE_MFCTR_R1] = "se_mfctr",
    [PPC32_IT_SE_MFLR_R1] = "se_mflr",
    [PPC32_IT_SE_MTCTR_R1] = "se_mtctr",
    [PPC32_IT_SE_MTLR_R1] = "se_mtlr",
    [PPC32_IT_SE_NEG_R1] = "se_neg",
    [PPC32_IT_SE_NOT_R1] = "se_not",

    //
    // Instruction Opcode RR1 Insns
    //
    [PPC32_IT_SE_ADD_RR1] = "se_add",
    [PPC32_IT_SE_ANDC_RR1] = "se_andc",
    [PPC32_IT_SE_CMP_RR1] = "se_cmp",
    [PPC32_IT_SE_CMPH_RR1] = "se_cmph",
    [PPC32_IT_SE_CMPHL_RR1] = "se_cmphl",
    [PPC32_IT_SE_CMPL_RR1] = "se_cmpl",
    [PPC32_IT_SE_MR_RR1] = "se_mr",
    [PPC32_IT_SE_MULLW_RR1] = "se_mullw",
    [PPC32_IT_SE_OR_RR1] = "se_or",
    [PPC32_IT_SE_SLW_RR1] = "se_slw",
    [PPC32_IT_SE_SRAW_RR1] = "se_sraw",
    [PPC32_IT_SE_SRW_RR1] = "se_srw",
    [PPC32_IT_SE_SUB_RR1] = "se_sub",
    [PPC32_IT_SE_SUBF_RR1] = "se_subf",

    //
    // Instruction Opcode RR2 Insns
    //
    [PPC32_IT_SE_AND_RR2] = "se_and",
    [PPC32_IT_SE_ANDRC_RR2] = "se_and.",

    //
    // Instruction Opcode RR3 Insns
    //
    [PPC32_IT_SE_MFAR_RR3] = "se_mfar",

    //
    // Instruction Opcode RR4 Insns
    //
    [PPC32_IT_SE_MTAR_RR4] = "se_mtar",

    //
    // Instruction Opcode SC1 Insns
    //
    [PPC32_IT_SC_SC1] = "sc",

    //
    // Instruction Opcode SCI8_1 Insns
    //
    [PPC32_IT_E_ADDI_SCI8_1] = "e_addi",
    [PPC32_IT_E_ADDIC_SCI8_1] = "e_addic",
    [PPC32_IT_E_ADDICRC_SCI8_1] = "e_addic.",
    [PPC32_IT_E_ADDIRC_SCI8_1] = "e_addi.",
    [PPC32_IT_E_SUBFIC_SCI8_1] = "e_subfic",
    [PPC32_IT_E_SUBFICRC_SCI8_1] = "e_subfic.",

    //
    // Instruction Opcode SCI8_2 Insns
    //
    [PPC32_IT_E_MULLI_SCI8_2] = "e_mulli",

    //
    // Instruction Opcode SCI8_3 Insns
    //
    [PPC32_IT_E_ANDI_SCI8_3] = "e_andi",
    [PPC32_IT_E_ANDIRC_SCI8_3] = "e_andi.",
    [PPC32_IT_E_ORI_SCI8_3] = "e_ori",
    [PPC32_IT_E_ORIRC_SCI8_3] = "e_ori.",
    [PPC32_IT_E_XORI_SCI8_3] = "e_xori",
    [PPC32_IT_E_XORIRC_SCI8_3] = "e_xori.",

    //
    // Instruction Opcode SCI8_5 Insns
    //
    [PPC32_IT_E_CMPI_SCI8_5] = "e_cmpi",

    //
    // Instruction Opcode SCI8_6 Insns
    //
    [PPC32_IT_E_CMPLI_SCI8_6] = "e_cmpli",

    //
    // Instruction Opcode SD4_0 Insns
    //
    [PPC32_IT_SE_LBZ_SD4_0] = "se_lbz",
    [PPC32_IT_SE_STB_SD4_0] = "se_stb",

    //
    // Instruction Opcode SD4_1 Insns
    //
    [PPC32_IT_SE_LHZ_SD4_1] = "se_lhz",
    [PPC32_IT_SE_STH_SD4_1] = "se_sth",

    //
    // Instruction Opcode SD4_2 Insns
    //
    [PPC32_IT_SE_LWZ_SD4_2] = "se_lwz",
    [PPC32_IT_SE_STW_SD4_2] = "se_stw",

    //
    // Instruction Opcode VA1_0 Insns
    //
    [PPC32_IT_VMHADDSHS_VA1_0] = "vmhaddshs",
    [PPC32_IT_VMHRADDSHS_VA1_0] = "vmhraddshs",
    [PPC32_IT_VMLADDUHM_VA1_0] = "vmladduhm",
    [PPC32_IT_VMSUMMBM_VA1_0] = "vmsummbm",
    [PPC32_IT_VMSUMSHM_VA1_0] = "vmsumshm",
    [PPC32_IT_VMSUMSHS_VA1_0] = "vmsumshs",
    [PPC32_IT_VMSUMUBM_VA1_0] = "vmsumubm",
    [PPC32_IT_VMSUMUHM_VA1_0] = "vmsumuhm",
    [PPC32_IT_VMSUMUHS_VA1_0] = "vmsumuhs",
    [PPC32_IT_VPERM_VA1_0] = "vperm",
    [PPC32_IT_VSEL_VA1_0] = "vsel",

    //
    // Instruction Opcode VA1_1 Insns
    //
    [PPC32_IT_VMADDFP_VA1_1] = "vmaddfp",
    [PPC32_IT_VMSUBFP_VA1_1] = "vnmsubfp",

    //
    // Instruction Opcode VA2 Insns
    //
    [PPC32_IT_VSLDOI_VA2] = "vsldoi",

    //
    // Instruction Opcode VC1 Insns
    //
    [PPC32_IT_VCMPBFP_VC1] = "vcmpbfp",
    [PPC32_IT_VCMPBFPRC_VC1] = "vcmpbfp.",
    [PPC32_IT_VCMPEQFP_VC1] = "vcmpeqfp",
    [PPC32_IT_VCMPEQFPRC_VC1] = "vcmpeqfp.",
    [PPC32_IT_VCMPEQUB_VC1] = "vcmpequb",
    [PPC32_IT_VCMPEQUBRC_VC1] = "vcmpequb.",
    [PPC32_IT_VCMPEQUH_VC1] = "vcmpequh",
    [PPC32_IT_VCMPEQUHRC_VC1] = "vcmpequh.",
    [PPC32_IT_VCMPEQUW_VC1] = "vcmpequw",
    [PPC32_IT_VCMPEQUWRC_VC1] = "vcmpequw.",
    [PPC32_IT_VCMPGEFP_VC1] = "vcmpgefp",
    [PPC32_IT_VCMPGEFPRC_VC1] = "vcmpgefp.",
    [PPC32_IT_VCMPGTFP_VC1] = "vcmpgtfp",
    [PPC32_IT_VCMPGTFPRC_VC1] = "vcmpgtfp.",
    [PPC32_IT_VCMPGTSB_VC1] = "vcmpgtsb",
    [PPC32_IT_VCMPGTSBRC_VC1] = "vcmpgtsb.",
    [PPC32_IT_VCMPGTSH_VC1] = "vcmpgtsh",
    [PPC32_IT_VCMPGTSHRC_VC1] = "vcmpgtsh.",
    [PPC32_IT_VCMPGTSW_VC1] = "vcmpgtsw",
    [PPC32_IT_VCMPGTSWRC_VC1] = "vcmpgtsw.",
    [PPC32_IT_VCMPGTUB_VC1] = "vcmpgtub",
    [PPC32_IT_VCMPGTUBRC_VC1] = "vcmpgtub.",
    [PPC32_IT_VCMPGTUH_VC1] = "vcmpgtuh",
    [PPC32_IT_VCMPGTUHRC_VC1] = "vcmpgtuh.",
    [PPC32_IT_VCMPGTUW_VC1] = "vcmpgtuw",
    [PPC32_IT_VCMPGTUWRC_VC1] = "vcmpgtuw.",

    //
    // Instruction Opcode VX1 Insns
    //
    [PPC32_IT_VADDCUW_VX1] = "vaddcuw",
    [PPC32_IT_VADDFP_VX1] = "vaddfp",
    [PPC32_IT_VADDSBS_VX1] = "vaddsbs",
    [PPC32_IT_VADDSHS_VX1] = "vaddshs",
    [PPC32_IT_VADDSWS_VX1] = "vaddsws",
    [PPC32_IT_VADDUBM_VX1] = "vaddubm",
    [PPC32_IT_VADDUBS_VX1] = "vaddubs",
    [PPC32_IT_VADDUHM_VX1] = "vadduhm",
    [PPC32_IT_VADDUHS_VX1] = "vadduhs",
    [PPC32_IT_VADDUWM_VX1] = "vadduwm",
    [PPC32_IT_VADDUWS_VX1] = "vadduws",
    [PPC32_IT_VAND_VX1] = "vand",
    [PPC32_IT_VANDC_VX1] = "vandc",
    [PPC32_IT_VAVGSB_VX1] = "vavgsb",
    [PPC32_IT_VAVGSH_VX1] = "vavgsh",
    [PPC32_IT_VAVGSW_VX1] = "vavgsw",
    [PPC32_IT_VAVGUB_VX1] = "vavgub",
    [PPC32_IT_VAVGUH_VX1] = "vavguh",
    [PPC32_IT_VAVGUW_VX1] = "vavguw",
    [PPC32_IT_VKPPX_VX1] = "vpkpx",
    [PPC32_IT_VKPSHSS_VX1] = "vpkshss",
    [PPC32_IT_VKPSHUS_VX1] = "vpkshus",
    [PPC32_IT_VKPSWSS_VX1] = "vpkswss",
    [PPC32_IT_VKPSWUS_VX1] = "vpkswus",
    [PPC32_IT_VKPUHUM_VX1] = "vpkuhum",
    [PPC32_IT_VKPUHUS_VX1] = "vpkuhus",
    [PPC32_IT_VKPUWUM_VX1] = "vpkuwum",
    [PPC32_IT_VKPUWUS_VX1] = "vpkuwus",
    [PPC32_IT_VMAXFP_VX1] = "vmaxfp",
    [PPC32_IT_VMAXSB_VX1] = "vmaxsb",
    [PPC32_IT_VMAXSH_VX1] = "vmaxsh",
    [PPC32_IT_VMAXSW_VX1] = "vmaxsw",
    [PPC32_IT_VMAXUB_VX1] = "vmaxub",
    [PPC32_IT_VMAXUH_VX1] = "vmaxuh",
    [PPC32_IT_VMAXUW_VX1] = "vmaxuw",
    [PPC32_IT_VMINFP_VX1] = "vminfp",
    [PPC32_IT_VMINSB_VX1] = "vminsb",
    [PPC32_IT_VMINSH_VX1] = "vminsh",
    [PPC32_IT_VMINSW_VX1] = "vminsw",
    [PPC32_IT_VMINUB_VX1] = "vminub",
    [PPC32_IT_VMINUH_VX1] = "vminuh",
    [PPC32_IT_VMINUW_VX1] = "vminuw",
    [PPC32_IT_VMRGHB_VX1] = "vmrghb",
    [PPC32_IT_VMRGHH_VX1] = "vmrghh",
    [PPC32_IT_VMRGHW_VX1] = "vmrghw",
    [PPC32_IT_VMRGLB_VX1] = "vmrglb",
    [PPC32_IT_VMRGLH_VX1] = "vmrglh",
    [PPC32_IT_VMRGLW_VX1] = "vmrglw",
    [PPC32_IT_VMULESB_VX1] = "vmulesb",
    [PPC32_IT_VMULESH_VX1] = "vmulesh",
    [PPC32_IT_VMULEUB_VX1] = "vmuleub",
    [PPC32_IT_VMULEUH_VX1] = "vmuleuh",
    [PPC32_IT_VMULOSB_VX1] = "vmulosb",
    [PPC32_IT_VMULOSH_VX1] = "vmulosh",
    [PPC32_IT_VMULOUB_VX1] = "vmuloub",
    [PPC32_IT_VMULOUH_VX1] = "vmulouh",
    [PPC32_IT_VNOR_VX1] = "vnor",
    [PPC32_IT_VOR_VX1] = "vor",
    [PPC32_IT_VRLB_VX1] = "vrlb",
    [PPC32_IT_VRLH_VX1] = "vrlh",
    [PPC32_IT_VRLW_VX1] = "vrlw",
    [PPC32_IT_VSL_VX1] = "vsl",
    [PPC32_IT_VSLB_VX1] = "vslb",
    [PPC32_IT_VSLH_VX1] = "vslh",
    [PPC32_IT_VSLO_VX1] = "vslo",
    [PPC32_IT_VSLW_VX1] = "vslw",
    [PPC32_IT_VSR_VX1] = "vsr",
    [PPC32_IT_VSRAB_VX1] = "vsrab",
    [PPC32_IT_VSRAH_VX1] = "vsrah",
    [PPC32_IT_VSRAW_VX1] = "vsraw",
    [PPC32_IT_VSRB_VX1] = "vsrb",
    [PPC32_IT_VSRH_VX1] = "vsrh",
    [PPC32_IT_VSRO_VX1] = "vsro",
    [PPC32_IT_VSRW_VX1] = "vsrw",
    [PPC32_IT_VSUBCUW_VX1] = "vsubcuw",
    [PPC32_IT_VSUBFP_VX1] = "vsubfp",
    [PPC32_IT_VSUBSBS_VX1] = "vsubsbs",
    [PPC32_IT_VSUBSHS_VX1] = "vsubshs",
    [PPC32_IT_VSUBSWS_VX1] = "vsubsws",
    [PPC32_IT_VSUBUBM_VX1] = "vsububm",
    [PPC32_IT_VSUBUBS_VX1] = "vsububs",
    [PPC32_IT_VSUBUHM_VX1] = "vsubuhm",
    [PPC32_IT_VSUBUHS_VX1] = "vsubuhs",
    [PPC32_IT_VSUBUWM_VX1] = "vsubuwm",
    [PPC32_IT_VSUBUWS_VX1] = "vsubuws",
    [PPC32_IT_VSUM2SWS_VX1] = "vsum2sws",
    [PPC32_IT_VSUM4SBS_VX1] = "vsum4sbs",
    [PPC32_IT_VSUM4SHS_VX1] = "vsum4shs",
    [PPC32_IT_VSUM4UBS_VX1] = "vsum4ubs",
    [PPC32_IT_VSUMSWS_VX1] = "vsumsws",
    [PPC32_IT_VXOR_VX1] = "vxor",

    //
    // Instruction Opcode VX2 Insns
    //
    [PPC32_IT_VEXPTEFP_VX2] = "vexptefp",
    [PPC32_IT_VLOGEFP_VX2] = "vlogefp",
    [PPC32_IT_VREFP_VX2] = "vrefp",
    [PPC32_IT_VRFIM_VX2] = "vrfim",
    [PPC32_IT_VRFIN_VX2] = "vrfin",
    [PPC32_IT_VRFIP_VX2] = "vrfip",
    [PPC32_IT_VRFIZ_VX2] = "vrfiz",
    [PPC32_IT_VRSQRTEFP_VX2] = "vrsqrtefp",
    [PPC32_IT_VUPKHPX_VX2] = "vupkhpx",
    [PPC32_IT_VUPKHSB_VX2] = "vupkhsb",
    [PPC32_IT_VUPKHSH_VX2] = "vupkhsh",
    [PPC32_IT_VUPKLPX_VX2] = "vupklpx",
    [PPC32_IT_VUPKLSB_VX2] = "vupklsb",
    [PPC32_IT_VUPKLSH_VX2] = "vupklsh",

    //
    // Instruction Opcode VX3 Insns
    //
    [PPC32_IT_VCFSX_VX3] = "vcfsx",
    [PPC32_IT_VCFUX_VX3] = "vcfux",
    [PPC32_IT_VCTSXS_VX3] = "vctsxs",
    [PPC32_IT_VCTUXS_VX3] = "vctuxs",

    //
    // Instruction Opcode VX4 Insns
    //
    [PPC32_IT_VSPLTB_VX4] = "vspltb",

    //
    // Instruction Opcode VX5 Insns
    //
    [PPC32_IT_VSPLTH_VX5] = "vsplth",

    //
    // Instruction Opcode VX6 Insns
    //
    [PPC32_IT_VSPLTW_VX6] = "vspltw",

    //
    // Instruction Opcode VX7 Insns
    //
    [PPC32_IT_VSPLTISB_VX7] = "vspltisb",
    [PPC32_IT_VSPLTISH_VX7] = "vspltish",
    [PPC32_IT_VSPLTISW_VX7] = "vspltisw",

    //
    // Instruction Opcode VX8 Insns
    //
    [PPC32_IT_MFVSCR_VX8] = "mfvscr",

    //
    // Instruction Opcode VX9 Insns
    //
    [PPC32_IT_MTVSCR_VX9] = "mtvscr",

    //
    // Instruction Opcode X1 Insns
    //
    [PPC32_IT_MFAPIDI_X1] = "mfapidi",
    [PPC32_IT_MFDCRUX_X1] = "mfdcrux",
    [PPC32_IT_MFDCRX_X1] = "mfdcrx",

    //
    // Instruction Opcode X10 Insns
    //
    [PPC32_IT_MULCHW_X10] = "mulchw",
    [PPC32_IT_MULCHWRC_X10] = "mulchw.",
    [PPC32_IT_MULCHWU_X10] = "mulchwu",
    [PPC32_IT_MULCHWURC_X10] = "mulchwu.",
    [PPC32_IT_MULHHW_X10] = "mulhhw",
    [PPC32_IT_MULHHWRC_X10] = "mulhhw.",
    [PPC32_IT_MULHHWU_X10] = "mulhhwu",
    [PPC32_IT_MULHHWURC_X10] = "mulhhwu.",
    [PPC32_IT_MULLHW_X10] = "mullhw",
    [PPC32_IT_MULLHWRC_X10] = "mullhw.",
    [PPC32_IT_MULLHWU_X10] = "mullhwu",
    [PPC32_IT_MULLHWURC_X10] = "mullhwu.",

    //
    // Instruction Opcode X11 Insns
    //
    [PPC32_IT_STWCXRC_X11] = "stwcx.",

    //
    // Instruction Opcode X12 Insns
    //
    [PPC32_IT_CMPB_X12] = "cmpb",
    [PPC32_IT_STBCIX_X12] = "stbcix",
    [PPC32_IT_STBEPX_X12] = "stbepx",
    [PPC32_IT_STBUX_X12] = "stbux",
    [PPC32_IT_STBX_X12] = "stbx",
    [PPC32_IT_STDCIX_X12] = "stdcix",
    [PPC32_IT_STDEPX_X12] = "stdepx",
    [PPC32_IT_STHBRX_X12] = "sthbrx",
    [PPC32_IT_STHCIX_X12] = "sthcix",
    [PPC32_IT_STHEPX_X12] = "sthepx",
    [PPC32_IT_STHUX_X12] = "sthux",
    [PPC32_IT_STHX_X12] = "sthx",
    [PPC32_IT_STSWX_X12] = "stswx",
    [PPC32_IT_STWBRX_X12] = "stwbrx",
    [PPC32_IT_STWCIX_X12] = "stwcix",
    [PPC32_IT_STWEPX_X12] = "stwepx",
    [PPC32_IT_STWUX_X12] = "stwux",
    [PPC32_IT_STWX_X12] = "stwx",

    //
    // Instruction Opcode X13 Insns
    //
    [PPC32_IT_STSWI_X13] = "stswi",

    //
    // Instruction Opcode X14 Insns
    //
    [PPC32_IT_E_RLWI_X14] = "e_rlwi",
    [PPC32_IT_E_RLWIRC_X14] = "e_rlwi.",
    [PPC32_IT_E_SLWI_X14] = "e_slwi",
    [PPC32_IT_E_SLWIRC_X14] = "e_slwi.",
    [PPC32_IT_E_SRWI_X14] = "e_srwi",
    [PPC32_IT_E_SRWIRC_X14] = "e_srwi.",
    [PPC32_IT_SRAWI_X14] = "srawi",
    [PPC32_IT_SRAWIRC_X14] = "srawi.",

    //
    // Instruction Opcode X15 Insns
    //
    [PPC32_IT_CNTLZW_X15] = "cntlzw",
    [PPC32_IT_CNTLZWRC_X15] = "cntlzw.",
    [PPC32_IT_EXTSB_X15] = "extsb",
    [PPC32_IT_EXTSBRC_X15] = "extsb.",
    [PPC32_IT_EXTSH_X15] = "extsh",
    [PPC32_IT_EXTSHRC_X15] = "extsh.",

    //
    // Instruction Opcode X16 Insns
    //
    [PPC32_IT_CBCDTD_X16] = "cbcdtd",
    [PPC32_IT_CDTBCD_X16] = "cdtbcd",
    [PPC32_IT_MTDCRUX_X16] = "mtdcrux",
    [PPC32_IT_MTDCRX_X16] = "mtdcrx",
    [PPC32_IT_POPCNTB_X16] = "popcntb",
    [PPC32_IT_PRTYW_X16] = "prtyw",

    //
    // Instruction Opcode X17 Insns
    //
    [PPC32_IT_MTSR_X17] = "mtsr",

    //
    // Instruction Opcode X18 Insns
    //
    [PPC32_IT_MTSRIN_X18] = "mtsrin",
    [PPC32_IT_SLBMTE_X18] = "slbmte",

    //
    // Instruction Opcode X19_0 Insns
    //
    [PPC32_IT_MTMSR_X19_0] = "mtmsr",

    //
    // Instruction Opcode X19_1 Insns
    //
    [PPC32_IT_WRTEE_X19_1] = "wrtee",

    //
    // Instruction Opcode X2 Insns
    //
    [PPC32_IT_DCREAD_X2] = "dcread",
    [PPC32_IT_ECIWX_X2] = "eciwx",
    [PPC32_IT_ECOWX_X2] = "ecowx",
    [PPC32_IT_LBEPX_X2] = "lbepx",
    [PPC32_IT_LBZCIX_X2] = "lbzcix",
    [PPC32_IT_LBZUX_X2] = "lbzux",
    [PPC32_IT_LBZX_X2] = "lbzx",
    [PPC32_IT_LDCIX_X2] = "ldcix",
    [PPC32_IT_LDEPX_X2] = "ldepx",
    [PPC32_IT_LHAUX_X2] = "lhaux",
    [PPC32_IT_LHAX_X2] = "lhax",
    [PPC32_IT_LHBRX_X2] = "lhbrx",
    [PPC32_IT_LHEPX_X2] = "lhepx",
    [PPC32_IT_LHZCIX_X2] = "lhzcix",
    [PPC32_IT_LHZUX_X2] = "lhzux",
    [PPC32_IT_LHZX_X2] = "lhzx",
    [PPC32_IT_LSWX_X2] = "lswx",
    [PPC32_IT_LWBRX_X2] = "lwbrx",
    [PPC32_IT_LWEPX_X2] = "lwepx",
    [PPC32_IT_LWZCIX_X2] = "lwzcix",
    [PPC32_IT_LWZUX_X2] = "lwzux",
    [PPC32_IT_LWZX_X2] = "lwzx",

    //
    // Instruction Opcode X20 Insns
    //
    [PPC32_IT_MTMSRD_X20] = "mtmsrd",

    //
    // Instruction Opcode X22_0 Insns
    //
    [PPC32_IT_CMPLW_X22_0] = "cmplw",
    [PPC32_IT_CMPW_X22_0] = "cmpw",

    //
    // Instruction Opcode X22_1 Insns
    //
    [PPC32_IT_CMP_X22_1] = "cmp",
    [PPC32_IT_CMPL_X22_1] = "cmpl",

    //
    // Instruction Opcode X22_2 Insns
    //
    [PPC32_IT_E_CMPH_X22_2] = "e_cmph",
    [PPC32_IT_E_CMPHL_X22_2] = "e_cmphl",

    //
    // Instruction Opcode X23 Insns
    //
    [PPC32_IT_DCMPO_X23] = "dcmpo",
    [PPC32_IT_DCMPU_X23] = "dcmpu",
    [PPC32_IT_DTSTEX_X23] = "dtstex",
    [PPC32_IT_DTSTSF_X23] = "dtstsf",
    [PPC32_IT_FCMPO_X23] = "fcmpo",
    [PPC32_IT_FCMPU_X23] = "fcmpu",

    //
    // Instruction Opcode X24 Insns
    //
    [PPC32_IT_MCRFS_X24] = "mcrfs",

    //
    // Instruction Opcode X25_0 Insns
    //
    [PPC32_IT_MTFSFIZ_X25_0] = "mtfsfi",
    [PPC32_IT_MTFSFIZRC_X25_0] = "mtfsfi.",

    //
    // Instruction Opcode X25_1 Insns
    //
    [PPC32_IT_MTFSFI_X25_1] = "mtfsfi",
    [PPC32_IT_MTFSFIRC_X25_1] = "mtfsfi.",

    //
    // Instruction Opcode X26 Insns
    //
    [PPC32_IT_MCRXR_X26] = "mcrxr",

    //
    // Instruction Opcode X27_0 Insns
    //
    [PPC32_IT_DCBT_X27_0] = "dcbt",
    [PPC32_IT_DCBTST_X27_0] = "dcbtst",

    //
    // Instruction Opcode X27_1 Insns
    //
    [PPC32_IT_DCBTST_1_X27_1] = "dcbtst",
    [PPC32_IT_DCBT_1_X27_1] = "dcbt",

    //
    // Instruction Opcode X27_2 Insns
    //
    [PPC32_IT_DCBTEP_X27_2] = "dcbtep",
    [PPC32_IT_DCBTSTEP_X27_2] = "dcbtstep",

    //
    // Instruction Opcode X28_0 Insns
    //
    [PPC32_IT_DCI_0_X28_0] = "dccci",
    [PPC32_IT_ICI_0_X28_0] = "iccci",

    //
    // Instruction Opcode X28_1 Insns
    //
    [PPC32_IT_DCI_X28_1] = "dci",
    [PPC32_IT_ICI_X28_1] = "ici",

    //
    // Instruction Opcode X29_0 Insns
    //
    [PPC32_IT_DCBLC_0_X29_0] = "dcblc",
    [PPC32_IT_DCBTLS_0_X29_0] = "dcbtls",
    [PPC32_IT_DCBTSTLS_0_X29_0] = "dcbtstls",
    [PPC32_IT_ICBLC_0_X29_0] = "icblc",
    [PPC32_IT_ICBTLS_0_X29_0] = "icbtls",
    [PPC32_IT_ICBT_CT0_X29_0] = "icbt",

    //
    // Instruction Opcode X29_1 Insns
    //
    [PPC32_IT_DCBLC_1_X29_1] = "dcblc",
    [PPC32_IT_DCBTLS_1_X29_1] = "dcbtls",
    [PPC32_IT_DCBTSTLS_1_X29_1] = "dcbtstls",
    [PPC32_IT_ICBLC_1_X29_1] = "icblc",
    [PPC32_IT_ICBT_X29_1] = "icbt",
    [PPC32_IT_ICBTLS_1_X29_1] = "icbtls",

    //
    // Instruction Opcode X3 Insns
    //
    [PPC32_IT_LWARX_X3] = "lwarx",

    //
    // Instruction Opcode X30 Insns
    //
    [PPC32_IT_DCBF_X30] = "dcbf",
    [PPC32_IT_DCBF_L_X30] = "dcbfl",
    [PPC32_IT_DCBF_LP_X30] = "dcbflp",

    //
    // Instruction Opcode X31_0 Insns
    //
    [PPC32_IT_TLBIEL_0_X31_0] = "tlbiel",
    [PPC32_IT_TLBIE_0_X31_0] = "tlbie",

    //
    // Instruction Opcode X31_1 Insns
    //
    [PPC32_IT_TLBIEL_1_X31_1] = "tlbiel",
    [PPC32_IT_TLBIE_1_X31_1] = "tlbie",

    //
    // Instruction Opcode X32 Insns
    //
    [PPC32_IT_LWSYNC_X32] = "lwsync",
    [PPC32_IT_PTESYNC_X32] = "ptesync",
    [PPC32_IT_SYNC_X32] = "sync",

    //
    // Instruction Opcode X33 Insns
    //
    [PPC32_IT_TW_X33] = "tw",

    //
    // Instruction Opcode X34 Insns
    //
    [PPC32_IT_LFDEPX_X34] = "lfdepx",
    [PPC32_IT_LFDUX_X34] = "lfdux",
    [PPC32_IT_LFDX_X34] = "lfdx",
    [PPC32_IT_LFIWAX_X34] = "lfiwax",
    [PPC32_IT_LFSUX_X34] = "lfsux",
    [PPC32_IT_LFSX_X34] = "lfsx",
    [PPC32_IT_STFDEPX_X34] = "stfdepx",

    //
    // Instruction Opcode X35RC Insns
    //
    [PPC32_IT_DADD_X35RC] = "dadd",
    [PPC32_IT_DADDRC_X35RC] = "dadd.",
    [PPC32_IT_DDIV_X35RC] = "ddiv",
    [PPC32_IT_DDIVRC_X35RC] = "ddiv.",
    [PPC32_IT_DIEX_X35RC] = "diex",
    [PPC32_IT_DIEXRC_X35RC] = "diex.",
    [PPC32_IT_DMUL_X35RC] = "dmul",
    [PPC32_IT_DMULRC_X35RC] = "dmul.",
    [PPC32_IT_DSUB_X35RC] = "dsub",
    [PPC32_IT_DSUBRC_X35RC] = "dsub.",
    [PPC32_IT_FCPSGN_X35RC] = "fcpsgn",
    [PPC32_IT_FCPSGNRC_X35RC] = "fcpsgn.",

    //
    // Instruction Opcode X37 Insns
    //
    [PPC32_IT_DCTDP_X37] = "dctdp",
    [PPC32_IT_DCTDPRC_X37] = "dctdp.",
    [PPC32_IT_DCTFIX_X37] = "dctfix",
    [PPC32_IT_DCTFIXRC_X37] = "dctfix.",
    [PPC32_IT_DRSP_X37] = "drsp",
    [PPC32_IT_DRSPRC_X37] = "drsp.",
    [PPC32_IT_DXEX_X37] = "dxex",
    [PPC32_IT_DXEXRC_X37] = "dxex.",
    [PPC32_IT_FABS_X37] = "fabs",
    [PPC32_IT_FABSRC_X37] = "fabs.",
    [PPC32_IT_FCFID_X37] = "fcfid",
    [PPC32_IT_FCFIDRC_X37] = "fcfid.",
    [PPC32_IT_FCTID_X37] = "fctid",
    [PPC32_IT_FCTIDRC_X37] = "fctid.",
    [PPC32_IT_FCTIDZ_X37] = "fctidz",
    [PPC32_IT_FCTIDZRC_X37] = "fctidz.",
    [PPC32_IT_FCTIW_X37] = "fctiw",
    [PPC32_IT_FCTIWRC_X37] = "fctiw.",
    [PPC32_IT_FCTIWZ_X37] = "fctiwz",
    [PPC32_IT_FCTIWZRC_X37] = "fctiwz.",
    [PPC32_IT_FMR_X37] = "fmr",
    [PPC32_IT_FMRRC_X37] = "fmr.",
    [PPC32_IT_FNABS_X37] = "fnabs",
    [PPC32_IT_FNABSRC_X37] = "fnabs.",
    [PPC32_IT_FNEG_X37] = "fneg",
    [PPC32_IT_FNEGRC_X37] = "fneg.",
    [PPC32_IT_FRIM_X37] = "frim",
    [PPC32_IT_FRIMRC_X37] = "frim.",
    [PPC32_IT_FRIN_X37] = "frin",
    [PPC32_IT_FRINRC_X37] = "frin.",
    [PPC32_IT_FRIP_X37] = "frip",
    [PPC32_IT_FRIPRC_X37] = "frip.",
    [PPC32_IT_FRIZ_X37] = "friz",
    [PPC32_IT_FRIZRC_X37] = "friz.",
    [PPC32_IT_FRSP_X37] = "frsp",
    [PPC32_IT_FRSPRC_X37] = "frsp.",

    //
    // Instruction Opcode X38 Insns
    //
    [PPC32_IT_DCTFIXQ_X38] = "dctfixq",
    [PPC32_IT_DCTFIXQRC_X38] = "dctfixq.",
    [PPC32_IT_DXEX_X38] = "dxexq",
    [PPC32_IT_DXEXRC_X38] = "dxexq.",

    //
    // Instruction Opcode X39 Insns
    //
    [PPC32_IT_MFFS_X39] = "mffs",
    [PPC32_IT_MFFSRC_X39] = "mffs.",

    //
    // Instruction Opcode X4 Insns
    //
    [PPC32_IT_LSWI_X4] = "lswi",

    //
    // Instruction Opcode X40 Insns
    //
    [PPC32_IT_DCFFIXQ_X40] = "dcffixq",
    [PPC32_IT_DCFFIXQRC_X40] = "dcffixq.",
    [PPC32_IT_DCTQPQ_X40] = "dctqpq",
    [PPC32_IT_DCTQPQRC_X40] = "dctqpq.",

    //
    // Instruction Opcode X41 Insns
    //
    [PPC32_IT_DRDPQ_X41] = "drdpq",
    [PPC32_IT_DRDPQRC_X41] = "drdpq.",

    //
    // Instruction Opcode X43 Insns
    //
    [PPC32_IT_DADDQ_X43] = "daddq",
    [PPC32_IT_DADDQRC_X43] = "daddq.",
    [PPC32_IT_DDIVQ_X43] = "ddivq",
    [PPC32_IT_DDIVQRC_X43] = "ddivq.",
    [PPC32_IT_DIEXQ_X43] = "diexq",
    [PPC32_IT_DIEXQRC_X43] = "diexq.",
    [PPC32_IT_DMULQ_X43] = "dmulq",
    [PPC32_IT_DMULQRC_X43] = "dmulq.",
    [PPC32_IT_DSUBQ_X43] = "dsubq",
    [PPC32_IT_DSUBQRC_X43] = "dsubq.",

    //
    // Instruction Opcode X45 Insns
    //
    [PPC32_IT_DCMPOQ_X45] = "dcmpoq",
    [PPC32_IT_DCMPUQ_X45] = "dcmpuq",
    [PPC32_IT_DTSTEXQ_X45] = "dtstexq",
    [PPC32_IT_DTSTSFQ_X45] = "dtstsfq",

    //
    // Instruction Opcode X46_0 Insns
    //
    [PPC32_IT_DDEDPD_X46_0] = "ddedpd",
    [PPC32_IT_DDEDPDRC_X46_0] = "ddedpd.",

    //
    // Instruction Opcode X46_1 Insns
    //
    [PPC32_IT_DENBCD_X46_1] = "denbcd",
    [PPC32_IT_DENBCDRC_X46_1] = "denbcd.",

    //
    // Instruction Opcode X47_0 Insns
    //
    [PPC32_IT_DDEDPDQ_X47_0] = "ddedpdq",
    [PPC32_IT_DDEDPDQRC_X47_0] = "ddedpdq.",

    //
    // Instruction Opcode X47_1 Insns
    //
    [PPC32_IT_DENBCDQ_X47_1] = "denbcdq",
    [PPC32_IT_DENBCDQRC_X47_1] = "denbcdq.",

    //
    // Instruction Opcode X48 Insns
    //
    [PPC32_IT_STFDUX_X48] = "stfdux",
    [PPC32_IT_STFDX_X48] = "stfdx",
    [PPC32_IT_STFIWX_X48] = "stfiwx",
    [PPC32_IT_STFSUX_X48] = "stfsux",
    [PPC32_IT_STFSX_X48] = "stfsx",

    //
    // Instruction Opcode X5 Insns
    //
    [PPC32_IT_MFSR_X5] = "mfsr",

    //
    // Instruction Opcode X50 Insns
    //
    [PPC32_IT_MTFSSB0_X50] = "mtfsb0",
    [PPC32_IT_MTFSSB0RC_X50] = "mtfsb0.",
    [PPC32_IT_MTFSSB1_X50] = "mtfsb1",
    [PPC32_IT_MTFSSB1RC_X50] = "mtfsb1.",

    //
    // Instruction Opcode X51 Insns
    //
    [PPC32_IT_DCBA_X51] = "dcba",
    [PPC32_IT_DCBFEP_X51] = "dcbfep",
    [PPC32_IT_DCBI_X51] = "dcbi",
    [PPC32_IT_DCBST_X51] = "dcbst",
    [PPC32_IT_DCBSTEP_X51] = "dcbstep",
    [PPC32_IT_DCBZ_X51] = "dcbz",
    [PPC32_IT_DCBZEP_X51] = "dcbzep",
    [PPC32_IT_ICBI_X51] = "icbi",
    [PPC32_IT_ICBIEP_X51] = "icbiep",
    [PPC32_IT_ICREAD_X51] = "icread",
    [PPC32_IT_TLBIVAX_X51] = "tlbivax",
    [PPC32_IT_TLBSX_X51] = "tlbsx",

    //
    // Instruction Opcode X52 Insns
    //
    [PPC32_IT_MSGCLR_X52] = "msgclr",
    [PPC32_IT_MSGSND_X52] = "msgsnd",
    [PPC32_IT_SLBIE_X52] = "slbie",

    //
    // Instruction Opcode X53_0 Insns
    //
    [PPC32_IT_EIEIO_X53_0] = "eieio",

    //
    // Instruction Opcode X53_1 Insns
    //
    [PPC32_IT_TLBIA_X53_1] = "tlbia",
    [PPC32_IT_TLBRE_X53_1] = "tlbre",
    [PPC32_IT_TLBSYNC_X53_1] = "tlbsync",
    [PPC32_IT_TLBWE_X53_1] = "tlbwe",
    [PPC32_IT_WAIT_X53_1] = "wait",

    //
    // Instruction Opcode X54 Insns
    //
    [PPC32_IT_WRTEEI_X54] = "wrteei",

    //
    // Instruction Opcode X55_0 Insns
    //
    [PPC32_IT_SLBIA_0_X55_0] = "slbia",

    //
    // Instruction Opcode X55_1 Insns
    //
    [PPC32_IT_SLBIA_1_X55_1] = "slbia",

    //
    // Instruction Opcode X58 Insns
    //
    [PPC32_IT_LVEBX_X58] = "lvebx",
    [PPC32_IT_LVEHX_X58] = "lvehx",
    [PPC32_IT_LVEWX_X58] = "lvewx",
    [PPC32_IT_LVSL_X58] = "lvsl",
    [PPC32_IT_LVSR_X58] = "lvsr",
    [PPC32_IT_LVX_X58] = "lvx",
    [PPC32_IT_LVXL_X58] = "lvxl",

    //
    // Instruction Opcode X59 Insns
    //
    [PPC32_IT_STVEBX_X59] = "stvebx",
    [PPC32_IT_STVEHX_X59] = "stvehx",
    [PPC32_IT_STVEWX_X59] = "stvewx",
    [PPC32_IT_STVX_X59] = "stvx",
    [PPC32_IT_STVXL_X59] = "stvxl",

    //
    // Instruction Opcode X6 Insns
    //
    [PPC32_IT_MFSRIN_X6] = "mfsrin",
    [PPC32_IT_SLBMFEE_X6] = "slbmfee",
    [PPC32_IT_SLBMFEV_X6] = "slbmfev",

    //
    // Instruction Opcode X60 Insns
    //
    [PPC32_IT_MBAR_X60] = "mbar",

    //
    // Instruction Opcode X8 Insns
    //
    [PPC32_IT_MFMSR_X8] = "mfmsr",

    //
    // Instruction Opcode X9 Insns
    //
    [PPC32_IT_AND_X9] = "and",
    [PPC32_IT_ANDC_X9] = "andc",
    [PPC32_IT_ANDCRC_X9] = "andc.",
    [PPC32_IT_ANDRC_X9] = "and.",
    [PPC32_IT_DLMZB_X9] = "dlmzb",
    [PPC32_IT_DLMZBRC_X9] = "dlmzb.",
    [PPC32_IT_EQV_X9] = "eqv",
    [PPC32_IT_EQVRC_X9] = "eqv.",
    [PPC32_IT_E_RLW_X9] = "e_rlw",
    [PPC32_IT_E_RLWRC_X9] = "e_rlw.",
    [PPC32_IT_NAND_X9] = "nand",
    [PPC32_IT_NANDRC_X9] = "nand.",
    [PPC32_IT_NOR_X9] = "nor",
    [PPC32_IT_NORRC_X9] = "nor.",
    [PPC32_IT_OR_X9] = "or",
    [PPC32_IT_ORC_X9] = "orc",
    [PPC32_IT_ORCRC_X9] = "orc.",
    [PPC32_IT_ORRC_X9] = "or.",
    [PPC32_IT_SLW_X9] = "slw",
    [PPC32_IT_SLWRC_X9] = "slw.",
    [PPC32_IT_SRAW_X9] = "sraw",
    [PPC32_IT_SRAWRC_X9] = "sraw.",
    [PPC32_IT_SRW_X9] = "srw",
    [PPC32_IT_SRWRC_X9] = "srw.",
    [PPC32_IT_XOR_X9] = "xor",
    [PPC32_IT_XORRC_X9] = "xor.",

    //
    // Instruction Opcode XFL Insns
    //
    [PPC32_IT_MTFSF_XFL] = "mtfsf",
    [PPC32_IT_MTFSFRC_XFL] = "mtfsf.",

    //
    // Instruction Opcode XFLZ Insns
    //
    [PPC32_IT_MTFSFZ_XFLZ] = "mtfsf",
    [PPC32_IT_MTFSFZRC_XFLZ] = "mtfsf.",

    //
    // Instruction Opcode XFX1 Insns
    //
    [PPC32_IT_MFSPR_XFX1] = "mfspr",
    [PPC32_IT_MFTB_XFX1] = "mftb",

    //
    // Instruction Opcode XFX10 Insns
    //
    [PPC32_IT_MTSPR_XFX10] = "mtspr",

    //
    // Instruction Opcode XFX10D Insns
    //
    [PPC32_IT_MTCTR_XFX10D] = "mtctr",
    [PPC32_IT_MTLR_XFX10D] = "mtlr",
    [PPC32_IT_MTXER_XFX10D] = "mtxer",

    //
    // Instruction Opcode XFX11 Insns
    //
    [PPC32_IT_MTDCR_XFX11] = "mtdcr",

    //
    // Instruction Opcode XFX12 Insns
    //
    [PPC32_IT_MTPMR_XFX12] = "mtpmr",

    //
    // Instruction Opcode XFX1D Insns
    //
    [PPC32_IT_MFCTR_XFX1D] = "mfctr",
    [PPC32_IT_MFLR_XFX1D] = "mflr",
    [PPC32_IT_MFXER_XFX1D] = "mfxer",

    //
    // Instruction Opcode XFX3 Insns
    //
    [PPC32_IT_MFCR_XFX3] = "mfcr",

    //
    // Instruction Opcode XFX4 Insns
    //
    [PPC32_IT_MFOCRF_XFX4] = "mfocrf",

    //
    // Instruction Opcode XFX5 Insns
    //
    [PPC32_IT_MFDCR_XFX5] = "mfdcr",

    //
    // Instruction Opcode XFX6 Insns
    //
    [PPC32_IT_MFPMR_XFX6] = "mfpmr",

    //
    // Instruction Opcode XFX7 Insns
    //

    //
    // Instruction Opcode XFX8 Insns
    //
    [PPC32_IT_MTCRF_XFX8] = "mtcrf",

    //
    // Instruction Opcode XFX8D Insns
    //
    [PPC32_IT_MTCR_XFX8D] = "mtcr",

    //
    // Instruction Opcode XFX9 Insns
    //
    [PPC32_IT_MTOCRF_XFX9] = "mtocrf",

    //
    // Instruction Opcode XL1 Insns
    //
    [PPC32_IT_CRAND_XL1] = "crand",
    [PPC32_IT_CRANDC_XL1] = "crandc",
    [PPC32_IT_CREQV_XL1] = "creqv",
    [PPC32_IT_CRNAND_XL1] = "crnand",
    [PPC32_IT_CRNOR_XL1] = "crnor",
    [PPC32_IT_CROR_XL1] = "cror",
    [PPC32_IT_CRORC_XL1] = "crorc",
    [PPC32_IT_CRXOR_XL1] = "crxor",
    [PPC32_IT_E_CRAND_XL1] = "e_crand",
    [PPC32_IT_E_CRANDC_XL1] = "e_crandc",
    [PPC32_IT_E_CREQV_XL1] = "e_creqv",
    [PPC32_IT_E_CRNAND_XL1] = "e_crnand",
    [PPC32_IT_E_CRNOR_XL1] = "e_crnor",
    [PPC32_IT_E_CROR_XL1] = "e_cror",
    [PPC32_IT_E_CRORC_XL1] = "e_crorc",
    [PPC32_IT_E_CRXOR_XL1] = "e_crxor",

    //
    // Instruction Opcode XL2 Insns
    //
    [PPC32_IT_BCCTR_XL2] = "bcctr",
    [PPC32_IT_BCLR_XL2] = "bclr",

    //
    // Instruction Opcode XL3 Insns
    //
    [PPC32_IT_E_MCRF_XL3] = "e_mcrf",
    [PPC32_IT_MCRF_XL3] = "mcrf",

    //
    // Instruction Opcode XL4 Insns
    //
    [PPC32_IT_DOZE_XL4] = "doze",
    [PPC32_IT_HRFID_XL4] = "hrfid",
    [PPC32_IT_ISYNC_XL4] = "isync",
    [PPC32_IT_NAP_XL4] = "nap",
    [PPC32_IT_RFCI_XL4] = "rfci",
    [PPC32_IT_RFI_XL4] = "rfi",
    [PPC32_IT_RFID_XL4] = "rfid",
    [PPC32_IT_RFMCI_XL4] = "rfmci",
    [PPC32_IT_RVWINKLE_XL4] = "rvwinkle",
    [PPC32_IT_SLEEP_XL4] = "sleep",

    //
    // Instruction Opcode XO1 Insns
    //
    [PPC32_IT_ADD_XO1] = "add",
    [PPC32_IT_ADDC_XO1] = "addc",
    [PPC32_IT_ADDCOE_XO1] = "addco",
    [PPC32_IT_ADDCOERC_XO1] = "addco.",
    [PPC32_IT_ADDCRC_XO1] = "addc.",
    [PPC32_IT_ADDE_XO1] = "adde",
    [PPC32_IT_ADDEOE_XO1] = "addeo",
    [PPC32_IT_ADDEOERC_XO1] = "addeo.",
    [PPC32_IT_ADDERC_XO1] = "adde.",
    [PPC32_IT_ADDOE_XO1] = "addo",
    [PPC32_IT_ADDOERC_XO1] = "addo.",
    [PPC32_IT_ADDRC_XO1] = "add.",
    [PPC32_IT_DIVW_XO1] = "divw",
    [PPC32_IT_DIVWOE_XO1] = "divwo",
    [PPC32_IT_DIVWOERC_XO1] = "divwo.",
    [PPC32_IT_DIVWRC_XO1] = "divw.",
    [PPC32_IT_DIVWU_XO1] = "divwu",
    [PPC32_IT_DIVWUOE_XO1] = "divwuo",
    [PPC32_IT_DIVWUOERC_XO1] = "divwuo.",
    [PPC32_IT_DIVWURC_XO1] = "divwu.",
    [PPC32_IT_MACCHW_XO1] = "macchw",
    [PPC32_IT_MACCHWOE_XO1] = "macchwo",
    [PPC32_IT_MACCHWOERC_XO1] = "macchwo.",
    [PPC32_IT_MACCHWRC_XO1] = "macchw.",
    [PPC32_IT_MACCHWS_XO1] = "macchws",
    [PPC32_IT_MACCHWSOE_XO1] = "macchwso",
    [PPC32_IT_MACCHWSOERC_XO1] = "macchwso.",
    [PPC32_IT_MACCHWSRC_XO1] = "macchws.",
    [PPC32_IT_MACCHWSU_XO1] = "macchwsu",
    [PPC32_IT_MACCHWSUOE_XO1] = "macchwsuo",
    [PPC32_IT_MACCHWSUOERC_XO1] = "macchwsuo.",
    [PPC32_IT_MACCHWSURC_XO1] = "macchwsu.",
    [PPC32_IT_MACCHWU_XO1] = "macchwu",
    [PPC32_IT_MACCHWUOE_XO1] = "macchwuo",
    [PPC32_IT_MACCHWUOERC_XO1] = "macchwuo.",
    [PPC32_IT_MACCHWURC_XO1] = "macchwu.",
    [PPC32_IT_MACHHW_XO1] = "machhw",
    [PPC32_IT_MACHHWOE_XO1] = "machhwo",
    [PPC32_IT_MACHHWOERC_XO1] = "machhwo.",
    [PPC32_IT_MACHHWRC_XO1] = "machhw.",
    [PPC32_IT_MACHHWS_XO1] = "machhws",
    [PPC32_IT_MACHHWSOE_XO1] = "machhwso",
    [PPC32_IT_MACHHWSOERC_XO1] = "machhwso.",
    [PPC32_IT_MACHHWSRC_XO1] = "machhws.",
    [PPC32_IT_MACHHWSU_XO1] = "machhwsu",
    [PPC32_IT_MACHHWSUOE_XO1] = "machhwsuo",
    [PPC32_IT_MACHHWSUOERC_XO1] = "machhwsuo.",
    [PPC32_IT_MACHHWSURC_XO1] = "machhwsu.",
    [PPC32_IT_MACHHWU_XO1] = "machhwu",
    [PPC32_IT_MACHHWUOE_XO1] = "machhwuo",
    [PPC32_IT_MACHHWUOERC_XO1] = "machhwuo.",
    [PPC32_IT_MACHHWURC_XO1] = "machhwu.",
    [PPC32_IT_MACLHW_XO1] = "maclhw",
    [PPC32_IT_MACLHWOE_XO1] = "maclhwo",
    [PPC32_IT_MACLHWOERC_XO1] = "maclhwo.",
    [PPC32_IT_MACLHWRC_XO1] = "maclhw.",
    [PPC32_IT_MACLHWS_XO1] = "maclhws",
    [PPC32_IT_MACLHWSOE_XO1] = "maclhwso",
    [PPC32_IT_MACLHWSOERC_XO1] = "maclhwso.",
    [PPC32_IT_MACLHWSRC_XO1] = "maclhws.",
    [PPC32_IT_MACLHWSU_XO1] = "maclhwsu",
    [PPC32_IT_MACLHWSUOE_XO1] = "maclhwsuo",
    [PPC32_IT_MACLHWSUOERC_XO1] = "maclhwsuo.",
    [PPC32_IT_MACLHWSURC_XO1] = "maclhwsu.",
    [PPC32_IT_MACLHWU_XO1] = "maclhwu",
    [PPC32_IT_MACLHWUOE_XO1] = "maclhwuo",
    [PPC32_IT_MACLHWUOERC_XO1] = "maclhwuo.",
    [PPC32_IT_MACLHWURC_XO1] = "maclhwu.",
    [PPC32_IT_MULLW_XO1] = "mullw",
    [PPC32_IT_MULLWOE_XO1] = "mullwo",
    [PPC32_IT_MULLWOERC_XO1] = "mullwo.",
    [PPC32_IT_MULLWRC_XO1] = "mullw.",
    [PPC32_IT_NMACCHW_XO1] = "nmacchw",
    [PPC32_IT_NMACCHWOE_XO1] = "nmacchwo",
    [PPC32_IT_NMACCHWOERC_XO1] = "nmacchwo.",
    [PPC32_IT_NMACCHWRC_XO1] = "nmacchw.",
    [PPC32_IT_NMACCHWS_XO1] = "nmacchws",
    [PPC32_IT_NMACCHWSOE_XO1] = "nmacchwso",
    [PPC32_IT_NMACCHWSOERC_XO1] = "nmacchwso.",
    [PPC32_IT_NMACCHWSRC_XO1] = "nmacchws.",
    [PPC32_IT_NMACHHW_XO1] = "nmachhw",
    [PPC32_IT_NMACHHWOE_XO1] = "nmachhwo",
    [PPC32_IT_NMACHHWOERC_XO1] = "nmachhwo.",
    [PPC32_IT_NMACHHWRC_XO1] = "nmachhw.",
    [PPC32_IT_NMACHHWS_XO1] = "nmachhws",
    [PPC32_IT_NMACHHWSOE_XO1] = "nmachhwso",
    [PPC32_IT_NMACHHWSOERC_XO1] = "nmachhwso.",
    [PPC32_IT_NMACHHWSRC_XO1] = "nmachhws.",
    [PPC32_IT_NMACLHW_XO1] = "nmaclhw",
    [PPC32_IT_NMACLHWOE_XO1] = "nmaclhwo",
    [PPC32_IT_NMACLHWOERC_XO1] = "nmaclhwo.",
    [PPC32_IT_NMACLHWRC_XO1] = "nmaclhw.",
    [PPC32_IT_NMACLHWS_XO1] = "nmaclhws",
    [PPC32_IT_NMACLHWSOE_XO1] = "nmaclhwso",
    [PPC32_IT_NMACLHWSOERC_XO1] = "nmaclhwso.",
    [PPC32_IT_NMACLHWSRC_XO1] = "nmaclhws.",
    [PPC32_IT_SUBF_XO1] = "subf",
    [PPC32_IT_SUBFC_XO1] = "subfc",
    [PPC32_IT_SUBFCOE_XO1] = "subfco",
    [PPC32_IT_SUBFCOERC_XO1] = "subfco.",
    [PPC32_IT_SUBFCRC_XO1] = "subfc.",
    [PPC32_IT_SUBFE_XO1] = "subfe",
    [PPC32_IT_SUBFEOE_XO1] = "subfeo",
    [PPC32_IT_SUBFEOERC_XO1] = "subfeo.",
    [PPC32_IT_SUBFERC_XO1] = "subfe.",
    [PPC32_IT_SUBFOE_XO1] = "subfo",
    [PPC32_IT_SUBFOERC_XO1] = "subfo.",
    [PPC32_IT_SUBFRC_XO1] = "subf.",

    //
    // Instruction Opcode XO2 Insns
    //
    [PPC32_IT_MULHW_XO2] = "mulhw",
    [PPC32_IT_MULHWRC_XO2] = "mulhw.",
    [PPC32_IT_MULHWU_XO2] = "mulhwu",
    [PPC32_IT_MULHWURC_XO2] = "mulhwu.",

    //
    // Instruction Opcode XO3 Insns
    //
    [PPC32_IT_ADDG6S_XO3] = "addg6s",

    //
    // Instruction Opcode XO4 Insns
    //
    [PPC32_IT_ADDME_XO4] = "addme",
    [PPC32_IT_ADDMEOE_XO4] = "addmeo",
    [PPC32_IT_ADDMEOERC_XO4] = "addmeo.",
    [PPC32_IT_ADDMERC_XO4] = "addme.",
    [PPC32_IT_ADDZE_XO4] = "addze",
    [PPC32_IT_ADDZEOE_XO4] = "addzeo",
    [PPC32_IT_ADDZEOERC_XO4] = "addzeo.",
    [PPC32_IT_ADDZERC_XO4] = "addze.",
    [PPC32_IT_NEG_XO4] = "neg",
    [PPC32_IT_NEGOE_XO4] = "nego",
    [PPC32_IT_NEGOERC_XO4] = "nego.",
    [PPC32_IT_NEGRC_XO4] = "neg.",
    [PPC32_IT_SUBFME_XO4] = "subfme",
    [PPC32_IT_SUBFMEOE_XO4] = "subfmeo",
    [PPC32_IT_SUBFMEOERC_XO4] = "subfmeo.",
    [PPC32_IT_SUBFMERC_XO4] = "subfme.",
    [PPC32_IT_SUBFZE_XO4] = "subfze",
    [PPC32_IT_SUBFZEOE_XO4] = "subfzeo",
    [PPC32_IT_SUBFZEOERC_XO4] = "subfzeo.",
    [PPC32_IT_SUBFZERC_XO4] = "subfze.",

    //
    // Instruction Opcode Z22_1 Insns
    //
    [PPC32_IT_DTSTDC_Z22_1] = "dtstdc",
    [PPC32_IT_DTSTDG_Z22_1] = "dtstdg",

    //
    // Instruction Opcode Z22_2 Insns
    //
    [PPC32_IT_DTSTDCQ_Z22_2] = "dtstdcq",
    [PPC32_IT_DTSTDGQ_Z22_2] = "dtstdgq",

    //
    // Instruction Opcode Z22_3 Insns
    //

    //
    // Instruction Opcode Z22_4 Insns
    //

    //
    // Instruction Opcode Z22_5 Insns
    //
    [PPC32_IT_DSCLI_Z22_5] = "dscli",
    [PPC32_IT_DSCLIRC_Z22_5] = "dscli.",
    [PPC32_IT_DSCRI_Z22_5] = "dscri",
    [PPC32_IT_DSCRIRC_Z22_5] = "dscri.",

    //
    // Instruction Opcode Z22_6 Insns
    //
    [PPC32_IT_DSCLIQ_Z22_6] = "dscliq",
    [PPC32_IT_DSCLIQRC_Z22_6] = "dscliq.",
    [PPC32_IT_DSCRIQ_Z22_6] = "dscriq",
    [PPC32_IT_DSCRIQRC_Z22_6] = "dscriq.",

    //
    // Instruction Opcode Z23_1 Insns
    //
    [PPC32_IT_DQUAI_Z23_1] = "dquai",
    [PPC32_IT_DQUAIRC_Z23_1] = "dquai.",

    //
    // Instruction Opcode Z23_2 Insns
    //
    [PPC32_IT_DQUAIQ_Z23_2] = "dquaiq",
    [PPC32_IT_DQUAIQRC_Z23_2] = "dquaiq.",

    //
    // Instruction Opcode Z23_3 Insns
    //
    [PPC32_IT_DQUA_Z23_3] = "dqua",
    [PPC32_IT_DQUAQ_Z23_3] = "dquaq",
    [PPC32_IT_DQUAQRC_Z23_3] = "dquaq.",
    [PPC32_IT_DQUARC_Z23_3] = "dqua.",
    [PPC32_IT_DRRND_Z23_3] = "drrnd",
    [PPC32_IT_DRRNDQ_Z23_3] = "drrndq",
    [PPC32_IT_DRRNDQRC_Z23_3] = "drrndq.",
    [PPC32_IT_DRRNDRC_Z23_3] = "drrnd.",

    //
    // Instruction Opcode Z23_5 Insns
    //

    //
    // Instruction Opcode Z23_6 Insns
    //
    [PPC32_IT_DRINTN_Z23_6] = "drintn",
    [PPC32_IT_DRINTNRC_Z23_6] = "drintn.",
    [PPC32_IT_DRINTX_Z23_6] = "drintx",
    [PPC32_IT_DRINTXRC_Z23_6] = "drintx.",

    //
    // Instruction Opcode Z23_7 Insns
    //
    [PPC32_IT_DRINTNQ_Z23_7] = "drintnq",
    [PPC32_IT_DRINTNQRC_Z23_7] = "drintnq.",
    [PPC32_IT_DRINTXQ_Z23_7] = "drintxq",
    [PPC32_IT_DRINTXQRC_Z23_7] = "drintxq.",

    [PPC32_IT_LAST] = "UNDEFINED"
};

#define DECODE_ENTRY(_PRIORITY, _NAME, _FMT) \
    vmidNewEntryFmtBin( \
        table, \
        #_NAME, \
        PPC32_IT_##_NAME, \
        _FMT, \
        _PRIORITY \
    )

// I_B Decoder
vmidDecodeTableP ppc32CreateDecodeTable_I_B_32Bit(vmidDecodeTableP current, Bool vle) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(32, PPC32_IT_LAST);
    }

    //                             A6   |  OPCD|   RT|   RA|   RB|   BC|   XO|X|
    DECODE_ENTRY(11,          ISEL_A6, "|011111|.....|.....|.....|.....|01111|.|");

    if (!vle) {
        //                             B1   |  OPCD|   BO|   BI|            BD|A|L|
        DECODE_ENTRY( 6,            BC_B1, "|010000|.....|.....|..............|.|.|");

        //                             D1   |  OPCD|   RT|   RA|               D|
        DECODE_ENTRY( 6,           LBZ_D1, "|100010|.....|.....|................|");
        DECODE_ENTRY( 6,          LBZU_D1, "|100011|.....|.....|................|");
        DECODE_ENTRY( 6,           LHA_D1, "|101010|.....|.....|................|");
        DECODE_ENTRY( 6,          LHAU_D1, "|101011|.....|.....|................|");
        DECODE_ENTRY( 6,           LHZ_D1, "|101000|.....|.....|................|");
        DECODE_ENTRY( 6,          LHZU_D1, "|101001|.....|.....|................|");
        DECODE_ENTRY( 6,           LMW_D1, "|101110|.....|.....|................|");
        DECODE_ENTRY( 6,           LWZ_D1, "|100000|.....|.....|................|");
        DECODE_ENTRY( 6,          LWZU_D1, "|100001|.....|.....|................|");

        //                           D2_0   |  OPCD|   RT|   RA|              SI|
        DECODE_ENTRY( 6,        ADDI_D2_0, "|001110|.....|.....|................|");
        DECODE_ENTRY( 6,       ADDIC_D2_0, "|001100|.....|.....|................|");
        DECODE_ENTRY( 6,     ADDICRC_D2_0, "|001101|.....|.....|................|");
        DECODE_ENTRY( 6,       ADDIS_D2_0, "|001111|.....|.....|................|");
        DECODE_ENTRY( 6,       MULLI_D2_0, "|000111|.....|.....|................|");
        DECODE_ENTRY( 6,      SUBFIC_D2_0, "|001000|.....|.....|................|");

        //                           D2_1   |  OPCD|   RT|   ZR|              SI|
        DECODE_ENTRY(11,          LI_D2_1, "|001110|.....|00000|................|");
        DECODE_ENTRY(11,         LIS_D2_1, "|001111|.....|00000|................|");

        //                             D3   |  OPCD|   RS|   RA|               D|
        DECODE_ENTRY( 6,           STB_D3, "|100110|.....|.....|................|");
        DECODE_ENTRY( 6,          STBU_D3, "|100111|.....|.....|................|");
        DECODE_ENTRY( 6,           STH_D3, "|101100|.....|.....|................|");
        DECODE_ENTRY( 6,          STHU_D3, "|101101|.....|.....|................|");
        DECODE_ENTRY( 6,          STMW_D3, "|101111|.....|.....|................|");
        DECODE_ENTRY( 6,           STW_D3, "|100100|.....|.....|................|");
        DECODE_ENTRY( 6,          STWU_D3, "|100101|.....|.....|................|");

        //                             D4   |  OPCD|   RS|   RA|              UI|
        DECODE_ENTRY( 6,        ANDIRC_D4, "|011100|.....|.....|................|");
        DECODE_ENTRY( 6,       ANDISRC_D4, "|011101|.....|.....|................|");
        DECODE_ENTRY( 6,           ORI_D4, "|011000|.....|.....|................|");
        DECODE_ENTRY( 6,          ORIS_D4, "|011001|.....|.....|................|");
        DECODE_ENTRY( 6,          XORI_D4, "|011010|.....|.....|................|");
        DECODE_ENTRY( 6,         XORIS_D4, "|011011|.....|.....|................|");

        //                           D5_0   |  OPCD| BF|X|L|   RA|              SI|
        DECODE_ENTRY( 7,       CMPWI_D5_0, "|001011|...|.|0|.....|................|");

        //                           D5_1   |  OPCD| BF|X|L|   RA|              SI|
        DECODE_ENTRY( 7,        CMPI_D5_1, "|001011|...|.|1|.....|................|");

        //                           D6_0   |  OPCD| BF|X|L|   RA|              UI|
        DECODE_ENTRY( 7,      CMPLWI_D6_0, "|001010|...|.|0|.....|................|");

        //                           D6_1   |  OPCD| BF|X|L|   RA|              UI|
        DECODE_ENTRY( 7,       CMPLI_D6_1, "|001010|...|.|1|.....|................|");

        //                             D7   |  OPCD|   TO|   RA|              SI|
        DECODE_ENTRY( 6,           TWI_D7, "|000011|.....|.....|................|");

        //                             I1   |  OPCD|                      LI|A|L|
        DECODE_ENTRY( 6,             B_I1, "|010010|........................|.|.|");

        //                           M1_0   |  OPCD|   RS|   RA|   RB|   MB|   ME|R|
        DECODE_ENTRY( 7,       RLWNM_M1_0, "|010111|.....|.....|.....|.....|.....|0|");
        DECODE_ENTRY( 7,     RLWNMRC_M1_0, "|010111|.....|.....|.....|.....|.....|1|");

        //                           M1_1   |  OPCD|   RS|   RA|   RB|   ZR|   NZ|R|
        DECODE_ENTRY(17,   RLWNMRC_0_M1_1, "|010111|.....|.....|.....|00000|11111|1|");
        DECODE_ENTRY(17,     RLWNM_0_M1_1, "|010111|.....|.....|.....|00000|11111|0|");

        //                           M2_0   |  OPCD|   RS|   RA|   SH|   MB|   ME|R|
        DECODE_ENTRY( 7,      RLWIMI_M2_0, "|010100|.....|.....|.....|.....|.....|0|");
        DECODE_ENTRY( 7,    RLWIMIRC_M2_0, "|010100|.....|.....|.....|.....|.....|1|");
        DECODE_ENTRY( 7,      RLWINM_M2_0, "|010101|.....|.....|.....|.....|.....|0|");
        DECODE_ENTRY( 7,    RLWINMRC_M2_0, "|010101|.....|.....|.....|.....|.....|1|");

        //                           M2_1   |  OPCD|   RS|   RA|   SH|   ZR|   NZ|R|
        DECODE_ENTRY(17,  RLWINMRC_0_M2_1, "|010101|.....|.....|.....|00000|11111|1|");
        DECODE_ENTRY(17,    RLWINM_0_M2_1, "|010101|.....|.....|.....|00000|11111|0|");

        //                            SC1   |  OPCD|             X|    LEV|  X|d|X|
        DECODE_ENTRY( 7,           SC_SC1, "|010001|..............|.......|...|1|.|");
    }

    //                            X11   |  OPCD|   RS|   RA|   RB|        XO|N|
    DECODE_ENTRY(17,      STWCXRC_X11, "|011111|.....|.....|.....|0010010110|1|");

    //                            X12   |  OPCD|   RS|   RA|   RB|        XO|X|
    DECODE_ENTRY(16,         CMPB_X12, "|011111|.....|.....|.....|0111111100|.|");
    DECODE_ENTRY(16,        STBUX_X12, "|011111|.....|.....|.....|0011110111|.|");
    DECODE_ENTRY(16,         STBX_X12, "|011111|.....|.....|.....|0011010111|.|");
    DECODE_ENTRY(16,       STHBRX_X12, "|011111|.....|.....|.....|1110010110|.|");
    DECODE_ENTRY(16,        STHUX_X12, "|011111|.....|.....|.....|0110110111|.|");
    DECODE_ENTRY(16,         STHX_X12, "|011111|.....|.....|.....|0110010111|.|");
    DECODE_ENTRY(16,       STWBRX_X12, "|011111|.....|.....|.....|1010010110|.|");
    DECODE_ENTRY(16,        STWUX_X12, "|011111|.....|.....|.....|0010110111|.|");
    DECODE_ENTRY(16,         STWX_X12, "|011111|.....|.....|.....|0010010111|.|");

    //                            X14   |  OPCD|   RS|   RA|   SH|        XO|R|
    DECODE_ENTRY(17,        SRAWI_X14, "|011111|.....|.....|.....|1100111000|0|");
    DECODE_ENTRY(17,      SRAWIRC_X14, "|011111|.....|.....|.....|1100111000|1|");

    //                            X15   |  OPCD|   RS|   RA|    X|        XO|R|
    DECODE_ENTRY(17,       CNTLZW_X15, "|011111|.....|.....|.....|0000011010|0|");
    DECODE_ENTRY(17,     CNTLZWRC_X15, "|011111|.....|.....|.....|0000011010|1|");
    DECODE_ENTRY(17,        EXTSB_X15, "|011111|.....|.....|.....|1110111010|0|");
    DECODE_ENTRY(17,      EXTSBRC_X15, "|011111|.....|.....|.....|1110111010|1|");
    DECODE_ENTRY(17,        EXTSH_X15, "|011111|.....|.....|.....|1110011010|0|");
    DECODE_ENTRY(17,      EXTSHRC_X15, "|011111|.....|.....|.....|1110011010|1|");

    //                            X16   |  OPCD|   RS|   RA|    X|        XO|X|
    DECODE_ENTRY(16,      POPCNTB_X16, "|011111|.....|.....|.....|0001111010|.|");
    if (!vle)
        DECODE_ENTRY(16,    PRTYW_X16, "|011111|.....|.....|.....|0010011010|.|");

    //                             X2   |  OPCD|   RT|   RA|   RB|        XO|X|
    DECODE_ENTRY(16,         LBZUX_X2, "|011111|.....|.....|.....|0001110111|.|");
    DECODE_ENTRY(16,          LBZX_X2, "|011111|.....|.....|.....|0001010111|.|");
    DECODE_ENTRY(16,         LHAUX_X2, "|011111|.....|.....|.....|0101110111|.|");
    DECODE_ENTRY(16,          LHAX_X2, "|011111|.....|.....|.....|0101010111|.|");
    DECODE_ENTRY(16,         LHBRX_X2, "|011111|.....|.....|.....|1100010110|.|");
    DECODE_ENTRY(16,         LHZUX_X2, "|011111|.....|.....|.....|0100110111|.|");
    DECODE_ENTRY(16,          LHZX_X2, "|011111|.....|.....|.....|0100010111|.|");
    DECODE_ENTRY(16,         LWBRX_X2, "|011111|.....|.....|.....|1000010110|.|");
    DECODE_ENTRY(16,         LWZUX_X2, "|011111|.....|.....|.....|0000110111|.|");
    DECODE_ENTRY(16,          LWZX_X2, "|011111|.....|.....|.....|0000010111|.|");

    //                          X22_0   |  OPCD| BF|X|L|   RA|   RB|        XO|X|
    DECODE_ENTRY(17,      CMPLW_X22_0, "|011111|...|.|0|.....|.....|0000100000|.|");
    DECODE_ENTRY(17,       CMPW_X22_0, "|011111|...|.|0|.....|.....|0000000000|.|");

    //                          X22_1   |  OPCD| BF|X|L|   RA|   RB|        XO|X|
    DECODE_ENTRY(17,        CMP_X22_1, "|011111|...|.|1|.....|.....|0000000000|.|");
    DECODE_ENTRY(17,       CMPL_X22_1, "|011111|...|.|1|.....|.....|0000100000|.|");

    //                          X27_0   |  OPCD|   TH|   RA|   RB|        XO|X|
    DECODE_ENTRY(16,       DCBT_X27_0, "|011111|.....|.....|.....|0100010110|.|");
    DECODE_ENTRY(16,     DCBTST_X27_0, "|011111|.....|.....|.....|0011110110|.|");

    //                          X27_1   |  OPCD|   ZR|   RA|   RB|        XO|X|
    DECODE_ENTRY(21,   DCBTST_1_X27_1, "|011111|00000|.....|.....|0011110110|.|");
    DECODE_ENTRY(21,     DCBT_1_X27_1, "|011111|00000|.....|.....|0100010110|.|");

    //                             X3   |  OPCD|   RT|   RA|   RB|        XO|E|
    DECODE_ENTRY(16,         LWARX_X3, "|011111|.....|.....|.....|0000010100|.|");

    //                            X30   |  OPCD|  X|Ld|   RA|   RB|        XO|X|
    DECODE_ENTRY(18,         DCBF_X30, "|011111|...|00|.....|.....|0001010110|.|");

    if (!vle) {
        //                            X32   |  OPCD|  X|Ld|         X|        XO|X|
        DECODE_ENTRY(18,       LWSYNC_X32, "|011111|...|01|..........|1001010110|.|");
        DECODE_ENTRY(18,      PTESYNC_X32, "|011111|...|10|..........|1001010110|.|");
    }
    DECODE_ENTRY(18,             SYNC_X32, "|011111|...|00|..........|1001010110|.|");

    //                            X33   |  OPCD|   TO|   RA|   RB|        XO|X|
    DECODE_ENTRY(16,           TW_X33, "|011111|.....|.....|.....|0000000100|.|");

    //                            X51   |  OPCD|    X|   RA|   RB|        XO|X|
    DECODE_ENTRY(16,        DCBST_X51, "|011111|.....|.....|.....|0000110110|.|");
    DECODE_ENTRY(16,         DCBZ_X51, "|011111|.....|.....|.....|1111110110|.|");
    DECODE_ENTRY(16,         ICBI_X51, "|011111|.....|.....|.....|1111010110|.|");

    //                          X53_1   |  OPCD|              X|        XO|X|
    DECODE_ENTRY(16,    TLBSYNC_X53_1, "|011111|...............|1000110110|.|");

    //                             X8   |  OPCD|   RT|         X|        XO|X|
    DECODE_ENTRY(16,         MFMSR_X8, "|011111|.....|..........|0001010011|.|");

    //                             X9   |  OPCD|   RS|   RA|   RB|        XO|R|
    DECODE_ENTRY(17,           AND_X9, "|011111|.....|.....|.....|0000011100|0|");
    DECODE_ENTRY(17,          ANDC_X9, "|011111|.....|.....|.....|0000111100|0|");
    DECODE_ENTRY(17,        ANDCRC_X9, "|011111|.....|.....|.....|0000111100|1|");
    DECODE_ENTRY(17,         ANDRC_X9, "|011111|.....|.....|.....|0000011100|1|");
    DECODE_ENTRY(17,           EQV_X9, "|011111|.....|.....|.....|0100011100|0|");
    DECODE_ENTRY(17,         EQVRC_X9, "|011111|.....|.....|.....|0100011100|1|");
    DECODE_ENTRY(17,          NAND_X9, "|011111|.....|.....|.....|0111011100|0|");
    DECODE_ENTRY(17,        NANDRC_X9, "|011111|.....|.....|.....|0111011100|1|");
    DECODE_ENTRY(17,           NOR_X9, "|011111|.....|.....|.....|0001111100|0|");
    DECODE_ENTRY(17,         NORRC_X9, "|011111|.....|.....|.....|0001111100|1|");
    DECODE_ENTRY(17,            OR_X9, "|011111|.....|.....|.....|0110111100|0|");
    DECODE_ENTRY(17,           ORC_X9, "|011111|.....|.....|.....|0110011100|0|");
    DECODE_ENTRY(17,         ORCRC_X9, "|011111|.....|.....|.....|0110011100|1|");
    DECODE_ENTRY(17,          ORRC_X9, "|011111|.....|.....|.....|0110111100|1|");
    DECODE_ENTRY(17,           SLW_X9, "|011111|.....|.....|.....|0000011000|0|");
    DECODE_ENTRY(17,         SLWRC_X9, "|011111|.....|.....|.....|0000011000|1|");
    DECODE_ENTRY(17,          SRAW_X9, "|011111|.....|.....|.....|1100011000|0|");
    DECODE_ENTRY(17,        SRAWRC_X9, "|011111|.....|.....|.....|1100011000|1|");
    DECODE_ENTRY(17,           SRW_X9, "|011111|.....|.....|.....|1000011000|0|");
    DECODE_ENTRY(17,         SRWRC_X9, "|011111|.....|.....|.....|1000011000|1|");
    DECODE_ENTRY(17,           XOR_X9, "|011111|.....|.....|.....|0100111100|0|");
    DECODE_ENTRY(17,         XORRC_X9, "|011111|.....|.....|.....|0100111100|1|");

    //                           XFX1   |  OPCD|   RT|  SPR|  SPR|        XO|X|
    DECODE_ENTRY(16,       MFSPR_XFX1, "|011111|.....|.....|.....|0101010011|.|");

    //                          XFX10   |  OPCD|   RS|  SPR|  SPR|        XO|X|
    DECODE_ENTRY(16,      MTSPR_XFX10, "|011111|.....|.....|.....|0111010011|.|");

    //                         XFX10D   |  OPCD|   RS| SPRD| SPRD|        XO|X|
    DECODE_ENTRY(26,     MTCTR_XFX10D, "|011111|.....|01001|00000|0111010011|.|");
    DECODE_ENTRY(26,      MTLR_XFX10D, "|011111|.....|01000|00000|0111010011|.|");
    DECODE_ENTRY(26,     MTXER_XFX10D, "|011111|.....|00001|00000|0111010011|.|");

    //                          XFX1D   |  OPCD|   RT| SPRD| SPRD|        XO|X|
    DECODE_ENTRY(26,      MFCTR_XFX1D, "|011111|.....|01001|00000|0101010011|.|");
    DECODE_ENTRY(26,       MFLR_XFX1D, "|011111|.....|01000|00000|0101010011|.|");
    DECODE_ENTRY(26,      MFXER_XFX1D, "|011111|.....|00001|00000|0101010011|.|");

    //                           XFX3   |  OPCD|   RT|Z|        X|        XO|X|
    DECODE_ENTRY(17,        MFCR_XFX3, "|011111|.....|0|.........|0000010011|.|");

    //                           XFX4   |  OPCD|   RT|N|     FXM|X|        XO|X|
    DECODE_ENTRY(17,      MFOCRF_XFX4, "|011111|.....|1|........|.|0000010011|.|");

    //                           XFX8   |  OPCD|   RS|Z|     FXM|X|        XO|X|
    DECODE_ENTRY(17,       MTCRF_XFX8, "|011111|.....|0|........|.|0010010000|.|");

    //                          XFX8D   |  OPCD|   RS|Z|    FXMD|X|        XO|X|
    DECODE_ENTRY(25,       MTCR_XFX8D, "|011111|.....|0|11111111|.|0010010000|.|");

    //                           XFX9   |  OPCD|   RS|N|     FXM|X|        XO|X|
    DECODE_ENTRY(17,      MTOCRF_XFX9, "|011111|.....|1|........|.|0010010000|.|");

    if (!vle) {
        //                            XL1   |  OPCD|   BT|   BA|   BB|        XO|X|
        DECODE_ENTRY(16,        CRAND_XL1, "|010011|.....|.....|.....|0100000001|.|");
        DECODE_ENTRY(16,       CRANDC_XL1, "|010011|.....|.....|.....|0010000001|.|");
        DECODE_ENTRY(16,        CREQV_XL1, "|010011|.....|.....|.....|0100100001|.|");
        DECODE_ENTRY(16,       CRNAND_XL1, "|010011|.....|.....|.....|0011100001|.|");
        DECODE_ENTRY(16,        CRNOR_XL1, "|010011|.....|.....|.....|0000100001|.|");
        DECODE_ENTRY(16,         CROR_XL1, "|010011|.....|.....|.....|0111000001|.|");
        DECODE_ENTRY(16,        CRORC_XL1, "|010011|.....|.....|.....|0110100001|.|");
        DECODE_ENTRY(16,        CRXOR_XL1, "|010011|.....|.....|.....|0011000001|.|");

        //                            XL2   |  OPCD|   BO|   BI|  X|BH|        XO|L|
        DECODE_ENTRY(16,        BCCTR_XL2, "|010011|.....|.....|...|..|1000010000|.|");
        DECODE_ENTRY(16,         BCLR_XL2, "|010011|.....|.....|...|..|0000010000|.|");
    }

    //                            XL3   |  OPCD| BF| X|BFA|      X|        XO|X|
    DECODE_ENTRY(16,         MCRF_XL3, "|010011|...|..|...|.......|0000000000|.|");

    if (!vle) {
        //                            XL4   |  OPCD|              X|        XO|X|
        DECODE_ENTRY(16,        ISYNC_XL4, "|010011|...............|0010010110|.|");
    }

    //                            XO1   |  OPCD|   RT|   RA|   RB|O|       XO|R|
    DECODE_ENTRY(17,          ADD_XO1, "|011111|.....|.....|.....|0|100001010|0|");
    DECODE_ENTRY(17,         ADDC_XO1, "|011111|.....|.....|.....|0|000001010|0|");
    DECODE_ENTRY(17,       ADDCOE_XO1, "|011111|.....|.....|.....|1|000001010|0|");
    DECODE_ENTRY(17,     ADDCOERC_XO1, "|011111|.....|.....|.....|1|000001010|1|");
    DECODE_ENTRY(17,       ADDCRC_XO1, "|011111|.....|.....|.....|0|000001010|1|");
    DECODE_ENTRY(17,         ADDE_XO1, "|011111|.....|.....|.....|0|010001010|0|");
    DECODE_ENTRY(17,       ADDEOE_XO1, "|011111|.....|.....|.....|1|010001010|0|");
    DECODE_ENTRY(17,     ADDEOERC_XO1, "|011111|.....|.....|.....|1|010001010|1|");
    DECODE_ENTRY(17,       ADDERC_XO1, "|011111|.....|.....|.....|0|010001010|1|");
    DECODE_ENTRY(17,        ADDOE_XO1, "|011111|.....|.....|.....|1|100001010|0|");
    DECODE_ENTRY(17,      ADDOERC_XO1, "|011111|.....|.....|.....|1|100001010|1|");
    DECODE_ENTRY(17,        ADDRC_XO1, "|011111|.....|.....|.....|0|100001010|1|");
    DECODE_ENTRY(17,         DIVW_XO1, "|011111|.....|.....|.....|0|111101011|0|");
    DECODE_ENTRY(17,       DIVWOE_XO1, "|011111|.....|.....|.....|1|111101011|0|");
    DECODE_ENTRY(17,     DIVWOERC_XO1, "|011111|.....|.....|.....|1|111101011|1|");
    DECODE_ENTRY(17,       DIVWRC_XO1, "|011111|.....|.....|.....|0|111101011|1|");
    DECODE_ENTRY(17,        DIVWU_XO1, "|011111|.....|.....|.....|0|111001011|0|");
    DECODE_ENTRY(17,      DIVWUOE_XO1, "|011111|.....|.....|.....|1|111001011|0|");
    DECODE_ENTRY(17,    DIVWUOERC_XO1, "|011111|.....|.....|.....|1|111001011|1|");
    DECODE_ENTRY(17,      DIVWURC_XO1, "|011111|.....|.....|.....|0|111001011|1|");
    DECODE_ENTRY(17,        MULLW_XO1, "|011111|.....|.....|.....|0|011101011|0|");
    DECODE_ENTRY(17,      MULLWOE_XO1, "|011111|.....|.....|.....|1|011101011|0|");
    DECODE_ENTRY(17,    MULLWOERC_XO1, "|011111|.....|.....|.....|1|011101011|1|");
    DECODE_ENTRY(17,      MULLWRC_XO1, "|011111|.....|.....|.....|0|011101011|1|");
    DECODE_ENTRY(17,         SUBF_XO1, "|011111|.....|.....|.....|0|000101000|0|");
    DECODE_ENTRY(17,        SUBFC_XO1, "|011111|.....|.....|.....|0|000001000|0|");
    DECODE_ENTRY(17,      SUBFCOE_XO1, "|011111|.....|.....|.....|1|000001000|0|");
    DECODE_ENTRY(17,    SUBFCOERC_XO1, "|011111|.....|.....|.....|1|000001000|1|");
    DECODE_ENTRY(17,      SUBFCRC_XO1, "|011111|.....|.....|.....|0|000001000|1|");
    DECODE_ENTRY(17,        SUBFE_XO1, "|011111|.....|.....|.....|0|010001000|0|");
    DECODE_ENTRY(17,      SUBFEOE_XO1, "|011111|.....|.....|.....|1|010001000|0|");
    DECODE_ENTRY(17,    SUBFEOERC_XO1, "|011111|.....|.....|.....|1|010001000|1|");
    DECODE_ENTRY(17,      SUBFERC_XO1, "|011111|.....|.....|.....|0|010001000|1|");
    DECODE_ENTRY(17,       SUBFOE_XO1, "|011111|.....|.....|.....|1|000101000|0|");
    DECODE_ENTRY(17,     SUBFOERC_XO1, "|011111|.....|.....|.....|1|000101000|1|");
    DECODE_ENTRY(17,       SUBFRC_XO1, "|011111|.....|.....|.....|0|000101000|1|");

    //                            XO2   |  OPCD|   RT|   RA|   RB|X|       XO|R|
    DECODE_ENTRY(16,        MULHW_XO2, "|011111|.....|.....|.....|.|001001011|0|");
    DECODE_ENTRY(16,      MULHWRC_XO2, "|011111|.....|.....|.....|.|001001011|1|");
    DECODE_ENTRY(16,       MULHWU_XO2, "|011111|.....|.....|.....|.|000001011|0|");
    DECODE_ENTRY(16,     MULHWURC_XO2, "|011111|.....|.....|.....|.|000001011|1|");

    //                            XO4   |  OPCD|   RT|   RA|    X|O|       XO|R|
    DECODE_ENTRY(17,        ADDME_XO4, "|011111|.....|.....|.....|0|011101010|0|");
    DECODE_ENTRY(17,      ADDMEOE_XO4, "|011111|.....|.....|.....|1|011101010|0|");
    DECODE_ENTRY(17,    ADDMEOERC_XO4, "|011111|.....|.....|.....|1|011101010|1|");
    DECODE_ENTRY(17,      ADDMERC_XO4, "|011111|.....|.....|.....|0|011101010|1|");
    DECODE_ENTRY(17,        ADDZE_XO4, "|011111|.....|.....|.....|0|011001010|0|");
    DECODE_ENTRY(17,      ADDZEOE_XO4, "|011111|.....|.....|.....|1|011001010|0|");
    DECODE_ENTRY(17,    ADDZEOERC_XO4, "|011111|.....|.....|.....|1|011001010|1|");
    DECODE_ENTRY(17,      ADDZERC_XO4, "|011111|.....|.....|.....|0|011001010|1|");
    DECODE_ENTRY(17,          NEG_XO4, "|011111|.....|.....|.....|0|001101000|0|");
    DECODE_ENTRY(17,        NEGOE_XO4, "|011111|.....|.....|.....|1|001101000|0|");
    DECODE_ENTRY(17,      NEGOERC_XO4, "|011111|.....|.....|.....|1|001101000|1|");
    DECODE_ENTRY(17,        NEGRC_XO4, "|011111|.....|.....|.....|0|001101000|1|");
    DECODE_ENTRY(17,       SUBFME_XO4, "|011111|.....|.....|.....|0|011101000|0|");
    DECODE_ENTRY(17,     SUBFMEOE_XO4, "|011111|.....|.....|.....|1|011101000|0|");
    DECODE_ENTRY(17,   SUBFMEOERC_XO4, "|011111|.....|.....|.....|1|011101000|1|");
    DECODE_ENTRY(17,     SUBFMERC_XO4, "|011111|.....|.....|.....|0|011101000|1|");
    DECODE_ENTRY(17,       SUBFZE_XO4, "|011111|.....|.....|.....|0|011001000|0|");
    DECODE_ENTRY(17,     SUBFZEOE_XO4, "|011111|.....|.....|.....|1|011001000|0|");
    DECODE_ENTRY(17,   SUBFZEOERC_XO4, "|011111|.....|.....|.....|1|011001000|1|");
    DECODE_ENTRY(17,     SUBFZERC_XO4, "|011111|.....|.....|.....|0|011001000|1|");

    return table;
}

// I_BCDA Decoder
vmidDecodeTableP ppc32CreateDecodeTable_I_BCDA_32Bit(vmidDecodeTableP current, Bool vle) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(32, PPC32_IT_LAST);
    }

    //                            X16   |  OPCD|   RS|   RA|    X|        XO|X|
    DECODE_ENTRY(16,       CBCDTD_X16, "|011111|.....|.....|.....|0100111010|.|");
    DECODE_ENTRY(16,       CDTBCD_X16, "|011111|.....|.....|.....|0100011010|.|");

    //                            XO3   |  OPCD|   RT|   RA|   RB|X|       XO|X|
    DECODE_ENTRY(15,       ADDG6S_XO3, "|011111|.....|.....|.....|.|001001010|.|");

    return table;
}

// I_S Decoder
vmidDecodeTableP ppc32CreateDecodeTable_I_S_32Bit(vmidDecodeTableP current, Bool vle) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(32, PPC32_IT_LAST);
    }

    //                            X12   |  OPCD|   RS|   RA|   RB|        XO|X|
    DECODE_ENTRY(16,       STBCIX_X12, "|011111|.....|.....|.....|1111010101|.|");
    DECODE_ENTRY(16,       STDCIX_X12, "|011111|.....|.....|.....|1111110101|.|");
    DECODE_ENTRY(16,       STHCIX_X12, "|011111|.....|.....|.....|1110110101|.|");
    DECODE_ENTRY(16,       STWCIX_X12, "|011111|.....|.....|.....|1110010101|.|");

    //                            X17   |  OPCD|   RS|X|  SR|    X|        XO|X|
    DECODE_ENTRY(16,         MTSR_X17, "|011111|.....|.|....|.....|0011010010|.|");

    //                            X18   |  OPCD|   RS|    X|   RB|        XO|X|
    DECODE_ENTRY(16,       MTSRIN_X18, "|011111|.....|.....|.....|0011110010|.|");
    DECODE_ENTRY(16,       SLBMTE_X18, "|011111|.....|.....|.....|0110010010|.|");

    //                             X2   |  OPCD|   RT|   RA|   RB|        XO|X|
    DECODE_ENTRY(16,        LBZCIX_X2, "|011111|.....|.....|.....|1101010101|.|");
    DECODE_ENTRY(16,         LDCIX_X2, "|011111|.....|.....|.....|1101110101|.|");
    DECODE_ENTRY(16,        LHZCIX_X2, "|011111|.....|.....|.....|1100110101|.|");
    DECODE_ENTRY(16,        LWZCIX_X2, "|011111|.....|.....|.....|1100010101|.|");

    //                            X20   |  OPCD|   RS|   X|L|    X|        XO|X|
    DECODE_ENTRY(16,       MTMSRD_X20, "|011111|.....|....|.|.....|0010110010|.|");

    //                            X30   |  OPCD|  X|Ld|   RA|   RB|        XO|X|
    DECODE_ENTRY(18,       DCBF_L_X30, "|011111|...|01|.....|.....|0001010110|.|");
    DECODE_ENTRY(18,      DCBF_LP_X30, "|011111|...|11|.....|.....|0001010110|.|");

    //                          X31_0   |  OPCD|   X|L|    X|   RB|        XO|X|
    DECODE_ENTRY(17,   TLBIEL_0_X31_0, "|011111|....|0|.....|.....|0100010010|.|");
    DECODE_ENTRY(17,    TLBIE_0_X31_0, "|011111|....|0|.....|.....|0100110010|.|");

    //                          X31_1   |  OPCD|   X|L|    X|   RB|        XO|X|
    DECODE_ENTRY(17,   TLBIEL_1_X31_1, "|011111|....|1|.....|.....|0100010010|.|");
    DECODE_ENTRY(17,    TLBIE_1_X31_1, "|011111|....|1|.....|.....|0100110010|.|");

    //                             X5   |  OPCD|   RT|  SR|    X|X|        XO|X|
    DECODE_ENTRY(16,          MFSR_X5, "|011111|.....|.....|.....|1|001010011|.|");

    //                            X52   |  OPCD|         X|   RB|        XO|X|
    DECODE_ENTRY(16,        SLBIE_X52, "|011111|..........|.....|0110110010|.|");

    //                          X53_0   |  OPCD|   ZR|        XO|
    DECODE_ENTRY(21,      EIEIO_X53_0, "|011111|00000|..........1101010110|.");

    //                          X53_1   |  OPCD|              X|        XO|X|
    DECODE_ENTRY(16,      TLBIA_X53_1, "|011111|...............|0101110010|.|");

    //                          X55_0   |  OPCD| X| IH|         X|        XO|X|
    DECODE_ENTRY(19,    SLBIA_0_X55_0, "|011111|..|000|..........|0111110010|.|");

    //                          X55_1   |  OPCD| X| IH|         X|        XO|X|
    DECODE_ENTRY(16,    SLBIA_1_X55_1, "|011111|..|...|..........|0111110010|.|");

    //                             X6   |  OPCD|   RT|    X|   RB|        XO|X|
    DECODE_ENTRY(16,        MFSRIN_X6, "|011111|.....|.....|.....|1010010011|.|");
    DECODE_ENTRY(16,       SLBMFEE_X6, "|011111|.....|.....|.....|1110010011|.|");
    DECODE_ENTRY(16,       SLBMFEV_X6, "|011111|.....|.....|.....|1101010011|.|");

    //                           XFX1   |  OPCD|   RT|  SPR|  SPR|        XO|X|
    DECODE_ENTRY(16,        MFTB_XFX1, "|011111|.....|.....|.....|0101110011|.|");

    //                            XL4   |  OPCD|              X|        XO|X|
    DECODE_ENTRY(16,         DOZE_XL4, "|010011|...............|0110010010|.|");
    DECODE_ENTRY(16,        HRFID_XL4, "|010011|...............|0100010010|.|");
    DECODE_ENTRY(16,          NAP_XL4, "|010011|...............|0110110010|.|");
    DECODE_ENTRY(16,         RFID_XL4, "|010011|...............|0000010010|.|");
    DECODE_ENTRY(16,     RVWINKLE_XL4, "|010011|...............|0111110010|.|");
    DECODE_ENTRY(16,        SLEEP_XL4, "|010011|...............|0111010010|.|");

    return table;
}

// I_E Decoder
vmidDecodeTableP ppc32CreateDecodeTable_I_E_32Bit(vmidDecodeTableP current, Bool vle) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(32, PPC32_IT_LAST);
    }

    //                             X1   |  OPCD|   RT|   RA|    X|        XO|X|
    DECODE_ENTRY(16,       MFAPIDI_X1, "|011111|.....|.....|.....|0100010011|.|");
    DECODE_ENTRY(16,       MFDCRUX_X1, "|011111|.....|.....|.....|0100100011|.|");
    DECODE_ENTRY(16,        MFDCRX_X1, "|011111|.....|.....|.....|0100000011|.|");

    //                            X16   |  OPCD|   RS|   RA|    X|        XO|X|
    DECODE_ENTRY(16,      MTDCRUX_X16, "|011111|.....|.....|.....|0110100011|.|");
    DECODE_ENTRY(16,       MTDCRX_X16, "|011111|.....|.....|.....|0110000011|.|");

    //                          X19_0   |  OPCD|   RS|   X|L|    X|        XO|X|
    DECODE_ENTRY(16,      MTMSR_X19_0, "|011111|.....|....|.|.....|0010010010|.|");

    //                          X19_1   |  OPCD|   RS|         X|        XO|X|
    DECODE_ENTRY(16,      WRTEE_X19_1, "|011111|.....|..........|0010000011|.|");

    //                             X2   |  OPCD|   RT|   RA|   RB|        XO|X|
    DECODE_ENTRY(16,        DCREAD_X2, "|011111|.....|.....|.....|0101000110|.|");

    //                            X26   |  OPCD| BF|           X|        XO|X|
    DECODE_ENTRY(16,        MCRXR_X26, "|011111|...|............|1000000000|.|");

    //                          X28_0   |  OPCD|  CT|         X|        XO|X|
    DECODE_ENTRY(20,      DCI_0_X28_0, "|011111|.0000|..........|0111000110|.|");
    DECODE_ENTRY(20,      ICI_0_X28_0, "|011111|.0000|..........|1111000110|.|");

    //                          X28_1   |  OPCD|  CT|         X|        XO|X|
    DECODE_ENTRY(16,        DCI_X28_1, "|011111|.....|..........|0111000110|.|");
    DECODE_ENTRY(16,        ICI_X28_1, "|011111|.....|..........|1111000110|.|");

    //                          X29_0   |  OPCD|  CT|   RA|   RB|        XO|X|
    DECODE_ENTRY(20,   ICBT_CT0_X29_0, "|011111|.0000|.....|.....|0000010110|.|");

    //                          X29_1   |  OPCD|  CT|   RA|   RB|        XO|X|
    DECODE_ENTRY(16,       ICBT_X29_1, "|011111|.....|.....|.....|0000010110|.|");

    //                            X51   |  OPCD|    X|   RA|   RB|        XO|X|
    DECODE_ENTRY(16,         DCBA_X51, "|011111|.....|.....|.....|1011110110|.|");
    DECODE_ENTRY(16,         DCBI_X51, "|011111|.....|.....|.....|0111010110|.|");
    DECODE_ENTRY(16,       ICREAD_X51, "|011111|.....|.....|.....|1111100110|.|");
    DECODE_ENTRY(16,      TLBIVAX_X51, "|011111|.....|.....|.....|1100010010|.|");
    DECODE_ENTRY(16,        TLBSX_X51, "|011111|.....|.....|.....|1110010010|.|");

    //                          X53_1   |  OPCD|              X|        XO|X|
    DECODE_ENTRY(16,      TLBRE_X53_1, "|011111|...............|1110110010|.|");
    DECODE_ENTRY(16,      TLBWE_X53_1, "|011111|...............|1111010010|.|");

    //                            X54   |  OPCD|         X|E|   X|        XO|X|
    DECODE_ENTRY(16,       WRTEEI_X54, "|011111|..........|.|....|0010100011|.|");

    //                            X60   |  OPCD|   MO|         X|        XO|X|
    DECODE_ENTRY(16,         MBAR_X60, "|011111|.....|..........|1101010110|.|");

    //                          XFX11   |  OPCD|   RS|  DCR|  DCR|        XO|X|
    DECODE_ENTRY(16,      MTDCR_XFX11, "|011111|.....|.....|.....|0111000011|.|");

    //                           XFX5   |  OPCD|   RT|  DCR|  DCR|        XO|X|
    DECODE_ENTRY(16,       MFDCR_XFX5, "|011111|.....|.....|.....|0101000011|.|");

    //                            XL4   |  OPCD|              X|        XO|X|
    DECODE_ENTRY(16,         RFCI_XL4, "|010011|...............|0000110011|.|");
    DECODE_ENTRY(16,          RFI_XL4, "|010011|...............|0000110010|.|");
    DECODE_ENTRY(16,        RFMCI_XL4, "|010011|...............|0000100110|.|");

    return table;
}

// I_E_PC Decoder
vmidDecodeTableP ppc32CreateDecodeTable_I_E_PC_32Bit(vmidDecodeTableP current, Bool vle) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(32, PPC32_IT_LAST);
    }

    //                            X52   |  OPCD|         X|   RB|        XO|X|
    DECODE_ENTRY(16,       MSGCLR_X52, "|011111|..........|.....|0011101110|.|");
    DECODE_ENTRY(16,       MSGSND_X52, "|011111|..........|.....|0011001110|.|");

    return table;
}

// I_E_PD Decoder
vmidDecodeTableP ppc32CreateDecodeTable_I_E_PD_32Bit(vmidDecodeTableP current, Bool vle) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(32, PPC32_IT_LAST);
    }

    //                            X12   |  OPCD|   RS|   RA|   RB|        XO|X|
    DECODE_ENTRY(16,       STBEPX_X12, "|011111|.....|.....|.....|0011011111|.|");
    DECODE_ENTRY(16,       STDEPX_X12, "|011111|.....|.....|.....|0010011101|.|");
    DECODE_ENTRY(16,       STHEPX_X12, "|011111|.....|.....|.....|0110011111|.|");
    DECODE_ENTRY(16,       STWEPX_X12, "|011111|.....|.....|.....|0010011111|.|");

    //                             X2   |  OPCD|   RT|   RA|   RB|        XO|X|
    DECODE_ENTRY(16,         ECIWX_X2, "|011111|.....|.....|.....|0100110110|.|");
    DECODE_ENTRY(16,         ECOWX_X2, "|011111|.....|.....|.....|0110110110|.|");
    DECODE_ENTRY(16,         LBEPX_X2, "|011111|.....|.....|.....|0001011111|.|");
    DECODE_ENTRY(16,         LDEPX_X2, "|011111|.....|.....|.....|0000011101|.|");
    DECODE_ENTRY(16,         LHEPX_X2, "|011111|.....|.....|.....|0100011111|.|");
    DECODE_ENTRY(16,         LWEPX_X2, "|011111|.....|.....|.....|0000011111|.|");

    //                          X27_2   |  OPCD|   TH|   RA|   RB|        XO|X|
    DECODE_ENTRY(16,     DCBTEP_X27_2, "|011111|.....|.....|.....|0100111111|.|");
    DECODE_ENTRY(16,   DCBTSTEP_X27_2, "|011111|.....|.....|.....|0011111111|.|");

    //                          X29_0   |  OPCD|  CT|   RA|   RB|        XO|X|
    DECODE_ENTRY(20,    DCBLC_0_X29_0, "|011111|.0000|.....|.....|0110000110|.|");
    DECODE_ENTRY(20,   DCBTLS_0_X29_0, "|011111|.0000|.....|.....|0010100110|.|");
    DECODE_ENTRY(20, DCBTSTLS_0_X29_0, "|011111|.0000|.....|.....|0010000110|.|");
    DECODE_ENTRY(20,    ICBLC_0_X29_0, "|011111|.0000|.....|.....|0011100110|.|");
    DECODE_ENTRY(20,   ICBTLS_0_X29_0, "|011111|.0000|.....|.....|0111100110|.|");

    //                          X29_1   |  OPCD|  CT|   RA|   RB|        XO|X|
    DECODE_ENTRY(16,    DCBLC_1_X29_1, "|011111|.....|.....|.....|0110000110|.|");
    DECODE_ENTRY(16,   DCBTLS_1_X29_1, "|011111|.....|.....|.....|0010100110|.|");
    DECODE_ENTRY(16, DCBTSTLS_1_X29_1, "|011111|.....|.....|.....|0010000110|.|");
    DECODE_ENTRY(16,    ICBLC_1_X29_1, "|011111|.....|.....|.....|0011100110|.|");
    DECODE_ENTRY(16,   ICBTLS_1_X29_1, "|011111|.....|.....|.....|0111100110|.|");

    //                            X34   |  OPCD|  FRT|   RA|   RB|        XO|X|
    DECODE_ENTRY(16,       LFDEPX_X34, "|011111|.....|.....|.....|1001011111|.|");
    DECODE_ENTRY(16,      STFDEPX_X34, "|011111|.....|.....|.....|1011011111|.|");

    //                            X51   |  OPCD|    X|   RA|   RB|        XO|X|
    DECODE_ENTRY(16,       DCBFEP_X51, "|011111|.....|.....|.....|0001111111|.|");
    DECODE_ENTRY(16,      DCBSTEP_X51, "|011111|.....|.....|.....|0000111111|.|");
    DECODE_ENTRY(16,       DCBZEP_X51, "|011111|.....|.....|.....|1111111111|.|");
    DECODE_ENTRY(16,       ICBIEP_X51, "|011111|.....|.....|.....|1111011111|.|");

    //                          XFX12   |  OPCD|   RS| PMRN| PMRN|        XO|X|
    DECODE_ENTRY(16,      MTPMR_XFX12, "|011111|.....|.....|.....|0111001110|.|");

    //                           XFX6   |  OPCD|   RT| PMRN| PMRN|        XO|X|
    DECODE_ENTRY(16,       MFPMR_XFX6, "|011111|.....|.....|.....|0101001110|.|");

    return table;
}

// I_FP Decoder
vmidDecodeTableP ppc32CreateDecodeTable_I_FP_32Bit(vmidDecodeTableP current, Bool vle) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(32, PPC32_IT_LAST);
    }

    //                             A1   |  OPCD|  FRT|  FRA|  FRB|  FRC|   XO|R|
    DECODE_ENTRY(12,         FMADD_A1, "|111111|.....|.....|.....|.....|11101|0|");
    DECODE_ENTRY(12,       FMADDRC_A1, "|111111|.....|.....|.....|.....|11101|1|");
    DECODE_ENTRY(12,        FMADDS_A1, "|111011|.....|.....|.....|.....|11101|0|");
    DECODE_ENTRY(12,      FMADDSRC_A1, "|111011|.....|.....|.....|.....|11101|1|");
    DECODE_ENTRY(12,         FMSUB_A1, "|111111|.....|.....|.....|.....|11100|0|");
    DECODE_ENTRY(12,       FMSUBRC_A1, "|111111|.....|.....|.....|.....|11100|1|");
    DECODE_ENTRY(12,        FMSUBS_A1, "|111011|.....|.....|.....|.....|11100|0|");
    DECODE_ENTRY(12,      FMSUBSRC_A1, "|111011|.....|.....|.....|.....|11100|1|");
    DECODE_ENTRY(12,        FNMADD_A1, "|111111|.....|.....|.....|.....|11111|0|");
    DECODE_ENTRY(12,      FNMADDRC_A1, "|111111|.....|.....|.....|.....|11111|1|");
    DECODE_ENTRY(12,       FNMADDS_A1, "|111011|.....|.....|.....|.....|11111|0|");
    DECODE_ENTRY(12,     FNMADDSRC_A1, "|111011|.....|.....|.....|.....|11111|1|");
    DECODE_ENTRY(12,        FNMSUB_A1, "|111111|.....|.....|.....|.....|11110|0|");
    DECODE_ENTRY(12,      FNMSUBRC_A1, "|111111|.....|.....|.....|.....|11110|1|");
    DECODE_ENTRY(12,       FNMSUBS_A1, "|111011|.....|.....|.....|.....|11110|0|");
    DECODE_ENTRY(12,     FNMSUBSRC_A1, "|111011|.....|.....|.....|.....|11110|1|");
    DECODE_ENTRY(12,          FSEL_A1, "|111111|.....|.....|.....|.....|10111|0|");
    DECODE_ENTRY(12,        FSELRC_A1, "|111111|.....|.....|.....|.....|10111|1|");

    //                             A2   |  OPCD|  FRT|  FRA|  FRB|    X|   XO|R|
    DECODE_ENTRY(12,          FADD_A2, "|111111|.....|.....|.....|.....|10101|0|");
    DECODE_ENTRY(12,        FADDRC_A2, "|111111|.....|.....|.....|.....|10101|1|");
    DECODE_ENTRY(12,         FADDS_A2, "|111011|.....|.....|.....|.....|10101|0|");
    DECODE_ENTRY(12,       FADDSRC_A2, "|111011|.....|.....|.....|.....|10101|1|");
    DECODE_ENTRY(12,          FDIV_A2, "|111111|.....|.....|.....|.....|10010|0|");
    DECODE_ENTRY(12,        FDIVRC_A2, "|111111|.....|.....|.....|.....|10010|1|");
    DECODE_ENTRY(12,         FDIVS_A2, "|111011|.....|.....|.....|.....|10010|0|");
    DECODE_ENTRY(12,       FDIVSRC_A2, "|111011|.....|.....|.....|.....|10010|1|");
    DECODE_ENTRY(12,          FSUB_A2, "|111111|.....|.....|.....|.....|10100|0|");
    DECODE_ENTRY(12,        FSUBRC_A2, "|111111|.....|.....|.....|.....|10100|1|");
    DECODE_ENTRY(12,         FSUBS_A2, "|111011|.....|.....|.....|.....|10100|0|");
    DECODE_ENTRY(12,       FSUBSRC_A2, "|111011|.....|.....|.....|.....|10100|1|");

    //                             A3   |  OPCD|  FRT|  FRA|    X|  FRC|   XO|R|
    DECODE_ENTRY(12,          FMUL_A3, "|111111|.....|.....|.....|.....|11001|0|");
    DECODE_ENTRY(12,        FMULRC_A3, "|111111|.....|.....|.....|.....|11001|1|");
    DECODE_ENTRY(12,         FMULS_A3, "|111011|.....|.....|.....|.....|11001|0|");
    DECODE_ENTRY(12,       FMULSRC_A3, "|111011|.....|.....|.....|.....|11001|1|");

    //                             A4   |  OPCD|  FRT|    X|  FRB|    X|   XO|R|
    DECODE_ENTRY(12,         FSQRT_A4, "|111111|.....|.....|.....|.....|10110|0|");
    DECODE_ENTRY(12,       FSQRTRC_A4, "|111111|.....|.....|.....|.....|10110|1|");
    DECODE_ENTRY(12,        FSQRTS_A4, "|111011|.....|.....|.....|.....|10110|0|");
    DECODE_ENTRY(12,      FSQRTSRC_A4, "|111011|.....|.....|.....|.....|10110|1|");

    //                             A5   |  OPCD|  FRT|   X|L|  FRB|    X|   XO|R|
    DECODE_ENTRY(13,           FRE_A5, "|111111|.....|....|0|.....|.....|11000|0|");
    DECODE_ENTRY(13,         FRERC_A5, "|111111|.....|....|0|.....|.....|11000|1|");
    DECODE_ENTRY(13,          FRES_A5, "|111011|.....|....|0|.....|.....|11000|0|");
    DECODE_ENTRY(13,        FRESRC_A5, "|111011|.....|....|0|.....|.....|11000|1|");
    DECODE_ENTRY(13,       FRSQRTE_A5, "|111111|.....|....|0|.....|.....|11010|0|");
    DECODE_ENTRY(13,     FRSQRTERC_A5, "|111111|.....|....|0|.....|.....|11010|1|");
    DECODE_ENTRY(13,      FRSQRTES_A5, "|111011|.....|....|0|.....|.....|11010|0|");
    DECODE_ENTRY(13,    FRSQRTESRC_A5, "|111011|.....|....|0|.....|.....|11010|1|");

    //                             D8   |  OPCD|  FRT|   RA|               D|
    DECODE_ENTRY( 6,           LFD_D8, "|110010|.....|.....|................|");
    DECODE_ENTRY( 6,          LFDU_D8, "|110011|.....|.....|................|");
    DECODE_ENTRY( 6,           LFS_D8, "|110000|.....|.....|................|");
    DECODE_ENTRY( 6,          LFSU_D8, "|110001|.....|.....|................|");

    //                             D9   |  OPCD|  FRS|   RA|               D|
    DECODE_ENTRY( 6,          STFD_D9, "|110110|.....|.....|................|");
    DECODE_ENTRY( 6,         STFDU_D9, "|110111|.....|.....|................|");
    DECODE_ENTRY( 6,          STFS_D9, "|110100|.....|.....|................|");
    DECODE_ENTRY( 6,         STFSU_D9, "|110101|.....|.....|................|");

    //                            X23   |  OPCD| BF| X|  FRA|  FRB|        XO|X|
    DECODE_ENTRY(16,        FCMPO_X23, "|111111|...|..|.....|.....|0000100000|.|");
    DECODE_ENTRY(16,        FCMPU_X23, "|111111|...|..|.....|.....|0000000000|.|");

    //                            X24   |  OPCD| BF| X|BFA|      X|        XO|X|
    DECODE_ENTRY(16,        MCRFS_X24, "|111111|...|..|...|.......|0001000000|.|");

    //                          X25_0   |  OPCD|BFU|     X|W|   U|X|        XO|R|
    DECODE_ENTRY(18,    MTFSFIZ_X25_0, "|111111|...|......|0|....|.|0010000110|0|");
    DECODE_ENTRY(18,  MTFSFIZRC_X25_0, "|111111|...|......|0|....|.|0010000110|1|");

    //                          X25_1   |  OPCD|BFU|     X|W|   U|X|        XO|R|
    DECODE_ENTRY(18,     MTFSFI_X25_1, "|111111|...|......|1|....|.|0010000110|0|");
    DECODE_ENTRY(18,   MTFSFIRC_X25_1, "|111111|...|......|1|....|.|0010000110|1|");

    //                            X34   |  OPCD|  FRT|   RA|   RB|        XO|X|
    DECODE_ENTRY(16,        LFDUX_X34, "|011111|.....|.....|.....|1001110111|.|");
    DECODE_ENTRY(16,         LFDX_X34, "|011111|.....|.....|.....|1001010111|.|");
    DECODE_ENTRY(16,       LFIWAX_X34, "|011111|.....|.....|.....|1101010111|.|");
    DECODE_ENTRY(16,        LFSUX_X34, "|011111|.....|.....|.....|1000110111|.|");
    DECODE_ENTRY(16,         LFSX_X34, "|011111|.....|.....|.....|1000010111|.|");

    //                          X35RC   |  OPCD|  FRT|  FRA|  FRB|        XO|R|
    DECODE_ENTRY(17,     FCPSGN_X35RC, "|111111|.....|.....|.....|0000001000|0|");
    DECODE_ENTRY(17,   FCPSGNRC_X35RC, "|111111|.....|.....|.....|0000001000|1|");

    //                            X37   |  OPCD|  FRT|    X|  FRB|        XO|R|
    DECODE_ENTRY(17,         FABS_X37, "|111111|.....|.....|.....|0100001000|0|");
    DECODE_ENTRY(17,       FABSRC_X37, "|111111|.....|.....|.....|0100001000|1|");
    DECODE_ENTRY(17,        FCFID_X37, "|111111|.....|.....|.....|1101001110|0|");
    DECODE_ENTRY(17,      FCFIDRC_X37, "|111111|.....|.....|.....|1101001110|1|");
    DECODE_ENTRY(17,        FCTID_X37, "|111111|.....|.....|.....|1100101110|0|");
    DECODE_ENTRY(17,      FCTIDRC_X37, "|111111|.....|.....|.....|1100101110|1|");
    DECODE_ENTRY(17,       FCTIDZ_X37, "|111111|.....|.....|.....|1100101111|0|");
    DECODE_ENTRY(17,     FCTIDZRC_X37, "|111111|.....|.....|.....|1100101111|1|");
    DECODE_ENTRY(17,        FCTIW_X37, "|111111|.....|.....|.....|0000001110|0|");
    DECODE_ENTRY(17,      FCTIWRC_X37, "|111111|.....|.....|.....|0000001110|1|");
    DECODE_ENTRY(17,       FCTIWZ_X37, "|111111|.....|.....|.....|0000001111|0|");
    DECODE_ENTRY(17,     FCTIWZRC_X37, "|111111|.....|.....|.....|0000001111|1|");
    DECODE_ENTRY(17,          FMR_X37, "|111111|.....|.....|.....|0001001000|0|");
    DECODE_ENTRY(17,        FMRRC_X37, "|111111|.....|.....|.....|0001001000|1|");
    DECODE_ENTRY(17,        FNABS_X37, "|111111|.....|.....|.....|0010001000|0|");
    DECODE_ENTRY(17,      FNABSRC_X37, "|111111|.....|.....|.....|0010001000|1|");
    DECODE_ENTRY(17,         FNEG_X37, "|111111|.....|.....|.....|0000101000|0|");
    DECODE_ENTRY(17,       FNEGRC_X37, "|111111|.....|.....|.....|0000101000|1|");
    DECODE_ENTRY(17,         FRIM_X37, "|111111|.....|.....|.....|0111101000|0|");
    DECODE_ENTRY(17,       FRIMRC_X37, "|111111|.....|.....|.....|0111101000|1|");
    DECODE_ENTRY(17,         FRIN_X37, "|111111|.....|.....|.....|0110001000|0|");
    DECODE_ENTRY(17,       FRINRC_X37, "|111111|.....|.....|.....|0110001000|1|");
    DECODE_ENTRY(17,         FRIP_X37, "|111111|.....|.....|.....|0111001000|0|");
    DECODE_ENTRY(17,       FRIPRC_X37, "|111111|.....|.....|.....|0111001000|1|");
    DECODE_ENTRY(17,         FRIZ_X37, "|111111|.....|.....|.....|0110101000|0|");
    DECODE_ENTRY(17,       FRIZRC_X37, "|111111|.....|.....|.....|0110101000|1|");
    DECODE_ENTRY(17,         FRSP_X37, "|111111|.....|.....|.....|0000001100|0|");
    DECODE_ENTRY(17,       FRSPRC_X37, "|111111|.....|.....|.....|0000001100|1|");

    //                            X39   |  OPCD|  FRT|         X|        XO|R|
    DECODE_ENTRY(17,         MFFS_X39, "|111111|.....|..........|1001000111|0|");
    DECODE_ENTRY(17,       MFFSRC_X39, "|111111|.....|..........|1001000111|1|");

    //                            X48   |  OPCD|  FRS|   RA|   RB|        XO|X|
    DECODE_ENTRY(16,       STFDUX_X48, "|011111|.....|.....|.....|1011110111|.|");
    DECODE_ENTRY(16,        STFDX_X48, "|011111|.....|.....|.....|1011010111|.|");
    DECODE_ENTRY(16,       STFIWX_X48, "|011111|.....|.....|.....|1111010111|.|");
    DECODE_ENTRY(16,       STFSUX_X48, "|011111|.....|.....|.....|1010110111|.|");
    DECODE_ENTRY(16,        STFSX_X48, "|011111|.....|.....|.....|1010010111|.|");

    //                            X50   |  OPCD|   BT|         X|        XO|R|
    DECODE_ENTRY(17,      MTFSSB0_X50, "|111111|.....|..........|0001000110|0|");
    DECODE_ENTRY(17,    MTFSSB0RC_X50, "|111111|.....|..........|0001000110|1|");
    DECODE_ENTRY(17,      MTFSSB1_X50, "|111111|.....|..........|0000100110|0|");
    DECODE_ENTRY(17,    MTFSSB1RC_X50, "|111111|.....|..........|0000100110|1|");

    //                            XFL   |  OPCD|B|     FLM|B|  FRB|        XO|R|
    DECODE_ENTRY(17,        MTFSF_XFL, "|111111|.|........|.|.....|1011000111|0|");
    DECODE_ENTRY(17,      MTFSFRC_XFL, "|111111|.|........|.|.....|1011000111|1|");

    //                           XFLZ   |  OPCD|B|     FLM|B|  FRB|        XO|R|
    DECODE_ENTRY(19,      MTFSFZ_XFLZ, "|111111|0|........|0|.....|1011000111|0|");
    DECODE_ENTRY(19,    MTFSFZRC_XFLZ, "|111111|0|........|0|.....|1011000111|1|");

    return table;
}

// I_DFP Decoder
vmidDecodeTableP ppc32CreateDecodeTable_I_DFP_32Bit(vmidDecodeTableP current, Bool vle) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(32, PPC32_IT_LAST);
    }

    //                            X23   |  OPCD| BF| X|  FRA|  FRB|        XO|X|
    DECODE_ENTRY(16,        DCMPO_X23, "|111011|...|..|.....|.....|0010000010|.|");
    DECODE_ENTRY(16,        DCMPU_X23, "|111011|...|..|.....|.....|1010000010|.|");
    DECODE_ENTRY(16,       DTSTEX_X23, "|111011|...|..|.....|.....|0010100010|.|");
    DECODE_ENTRY(16,       DTSTSF_X23, "|111011|...|..|.....|.....|1010100010|.|");

    //                          X35RC   |  OPCD|  FRT|  FRA|  FRB|        XO|R|
    DECODE_ENTRY(17,       DADD_X35RC, "|111011|.....|.....|.....|0000000010|0|");
    DECODE_ENTRY(17,     DADDRC_X35RC, "|111011|.....|.....|.....|0000000010|1|");
    DECODE_ENTRY(17,       DDIV_X35RC, "|111011|.....|.....|.....|1000100010|0|");
    DECODE_ENTRY(17,     DDIVRC_X35RC, "|111011|.....|.....|.....|1000100010|1|");
    DECODE_ENTRY(17,       DIEX_X35RC, "|111011|.....|.....|.....|1101100010|0|");
    DECODE_ENTRY(17,     DIEXRC_X35RC, "|111011|.....|.....|.....|1101100010|1|");
    DECODE_ENTRY(17,       DMUL_X35RC, "|111011|.....|.....|.....|0000100010|0|");
    DECODE_ENTRY(17,     DMULRC_X35RC, "|111011|.....|.....|.....|0000100010|1|");
    DECODE_ENTRY(17,       DSUB_X35RC, "|111011|.....|.....|.....|1000000010|0|");
    DECODE_ENTRY(17,     DSUBRC_X35RC, "|111011|.....|.....|.....|1000000010|1|");

    //                            X37   |  OPCD|  FRT|    X|  FRB|        XO|R|
    DECODE_ENTRY(17,        DCTDP_X37, "|111011|.....|.....|.....|0100000010|0|");
    DECODE_ENTRY(17,      DCTDPRC_X37, "|111011|.....|.....|.....|0100000010|1|");
    DECODE_ENTRY(17,       DCTFIX_X37, "|111011|.....|.....|.....|0100100010|0|");
    DECODE_ENTRY(17,     DCTFIXRC_X37, "|111011|.....|.....|.....|0100100010|1|");
    DECODE_ENTRY(17,         DRSP_X37, "|111011|.....|.....|.....|1100000010|0|");
    DECODE_ENTRY(17,       DRSPRC_X37, "|111011|.....|.....|.....|1100000010|1|");
    DECODE_ENTRY(17,         DXEX_X37, "|111011|.....|.....|.....|0101100010|0|");
    DECODE_ENTRY(17,       DXEXRC_X37, "|111011|.....|.....|.....|0101100010|1|");

    //                            X38   |  OPCD|  FRT|    X| FRBp|        XO|R|
    DECODE_ENTRY(17,      DCTFIXQ_X38, "|111111|.....|.....|.....|0100100010|0|");
    DECODE_ENTRY(17,    DCTFIXQRC_X38, "|111111|.....|.....|.....|0100100010|1|");
    DECODE_ENTRY(17,         DXEX_X38, "|111111|.....|.....|.....|0101100010|0|");
    DECODE_ENTRY(17,       DXEXRC_X38, "|111111|.....|.....|.....|0101100010|1|");

    //                            X40   |  OPCD| FRTp|    X|  FRB|        XO|R|
    DECODE_ENTRY(17,      DCFFIXQ_X40, "|111111|.....|.....|.....|1100100010|0|");
    DECODE_ENTRY(17,    DCFFIXQRC_X40, "|111111|.....|.....|.....|1100100010|1|");
    DECODE_ENTRY(17,       DCTQPQ_X40, "|111111|.....|.....|.....|0100000010|0|");
    DECODE_ENTRY(17,     DCTQPQRC_X40, "|111111|.....|.....|.....|0100000010|1|");

    //                            X41   |  OPCD| FRTp|    X| FRBp|        XO|R|
    DECODE_ENTRY(17,        DRDPQ_X41, "|111111|.....|.....|.....|1100000010|0|");
    DECODE_ENTRY(17,      DRDPQRC_X41, "|111111|.....|.....|.....|1100000010|1|");

    //                            X43   |  OPCD| FRTp| FRAp| FRBp|        XO|R|
    DECODE_ENTRY(17,        DADDQ_X43, "|111111|.....|.....|.....|0000000010|0|");
    DECODE_ENTRY(17,      DADDQRC_X43, "|111111|.....|.....|.....|0000000010|1|");
    DECODE_ENTRY(17,        DDIVQ_X43, "|111111|.....|.....|.....|1000100010|0|");
    DECODE_ENTRY(17,      DDIVQRC_X43, "|111111|.....|.....|.....|1000100010|1|");
    DECODE_ENTRY(17,        DIEXQ_X43, "|111111|.....|.....|.....|1101100010|0|");
    DECODE_ENTRY(17,      DIEXQRC_X43, "|111111|.....|.....|.....|1101100010|1|");
    DECODE_ENTRY(17,        DMULQ_X43, "|111111|.....|.....|.....|0000100010|0|");
    DECODE_ENTRY(17,      DMULQRC_X43, "|111111|.....|.....|.....|0000100010|1|");
    DECODE_ENTRY(17,        DSUBQ_X43, "|111111|.....|.....|.....|1000000010|0|");
    DECODE_ENTRY(17,      DSUBQRC_X43, "|111111|.....|.....|.....|1000000010|1|");

    //                            X45   |  OPCD| BF| X| FRAp| FRBp|        XO|X|
    DECODE_ENTRY(16,       DCMPOQ_X45, "|111111|...|..|.....|.....|0010000010|.|");
    DECODE_ENTRY(16,       DCMPUQ_X45, "|111111|...|..|.....|.....|1010000010|.|");
    DECODE_ENTRY(16,      DTSTEXQ_X45, "|111111|...|..|.....|.....|0010100010|.|");
    DECODE_ENTRY(16,      DTSTSFQ_X45, "|111111|...|..|.....|.....|1010100010|.|");

    //                          X46_0   |  OPCD|  FRT|SP|  X|  FRB|        XO|R|
    DECODE_ENTRY(17,     DDEDPD_X46_0, "|111011|.....|..|...|.....|0101000010|0|");
    DECODE_ENTRY(17,   DDEDPDRC_X46_0, "|111011|.....|..|...|.....|0101000010|1|");

    //                          X46_1   |  OPCD|  FRT|S|   X|  FRB|        XO|R|
    DECODE_ENTRY(17,     DENBCD_X46_1, "|111011|.....|.|....|.....|1101000010|0|");
    DECODE_ENTRY(17,   DENBCDRC_X46_1, "|111011|.....|.|....|.....|1101000010|1|");

    //                          X47_0   |  OPCD| FRTp|SP|  X| FRBp|        XO|R|
    DECODE_ENTRY(17,    DDEDPDQ_X47_0, "|111111|.....|..|...|.....|0101000010|0|");
    DECODE_ENTRY(17,  DDEDPDQRC_X47_0, "|111111|.....|..|...|.....|0101000010|1|");

    //                          X47_1   |  OPCD| FRTp|S|   X| FRBp|        XO|R|
    DECODE_ENTRY(17,    DENBCDQ_X47_1, "|111111|.....|.|....|.....|1101000010|0|");
    DECODE_ENTRY(17,  DENBCDQRC_X47_1, "|111111|.....|.|....|.....|1101000010|1|");

    //                          Z22_1   |  OPCD| BF| X|  FRA|   DCM|       XO|X|
    DECODE_ENTRY(15,     DTSTDC_Z22_1, "|111011|...|..|.....|......|011000010|.|");
    DECODE_ENTRY(15,     DTSTDG_Z22_1, "|111011|...|..|.....|......|011100010|.|");

    //                          Z22_2   |  OPCD| BF| X| FRAp|   DCM|       XO|X|
    DECODE_ENTRY(15,    DTSTDCQ_Z22_2, "|111111|...|..|.....|......|011000010|.|");
    DECODE_ENTRY(15,    DTSTDGQ_Z22_2, "|111111|...|..|.....|......|011100010|.|");

    //                          Z22_5   |  OPCD|  FRT|  FRA|    SH|       XO|R|
    DECODE_ENTRY(16,      DSCLI_Z22_5, "|111011|.....|.....|......|001000010|0|");
    DECODE_ENTRY(16,    DSCLIRC_Z22_5, "|111011|.....|.....|......|001000010|1|");
    DECODE_ENTRY(16,      DSCRI_Z22_5, "|111011|.....|.....|......|001100010|0|");
    DECODE_ENTRY(16,    DSCRIRC_Z22_5, "|111011|.....|.....|......|001100010|1|");

    //                          Z22_6   |  OPCD| FRTp| FRAp|    SH|       XO|R|
    DECODE_ENTRY(16,     DSCLIQ_Z22_6, "|111111|.....|.....|......|001000010|0|");
    DECODE_ENTRY(16,   DSCLIQRC_Z22_6, "|111111|.....|.....|......|001000010|1|");
    DECODE_ENTRY(16,     DSCRIQ_Z22_6, "|111111|.....|.....|......|001100010|0|");
    DECODE_ENTRY(16,   DSCRIQRC_Z22_6, "|111111|.....|.....|......|001100010|1|");

    //                          Z23_1   |  OPCD|  FRT|   TE|  FRB|RM|      XO|R|
    DECODE_ENTRY(15,      DQUAI_Z23_1, "|111011|.....|.....|.....|..|01000011|0|");
    DECODE_ENTRY(15,    DQUAIRC_Z23_1, "|111011|.....|.....|.....|..|01000011|1|");

    //                          Z23_2   |  OPCD| FRTp|   TE| FRBp|RM|      XO|R|
    DECODE_ENTRY(15,     DQUAIQ_Z23_2, "|111111|.....|.....|.....|..|01000011|0|");
    DECODE_ENTRY(15,   DQUAIQRC_Z23_2, "|111111|.....|.....|.....|..|01000011|1|");

    //                          Z23_3   |  OPCD|  FRT|  FRA|  FRB|RM|      XO|R|
    DECODE_ENTRY(15,       DQUA_Z23_3, "|111011|.....|.....|.....|..|00000011|0|");
    DECODE_ENTRY(15,      DQUAQ_Z23_3, "|111111|.....|.....|.....|..|00000011|0|");
    DECODE_ENTRY(15,    DQUAQRC_Z23_3, "|111111|.....|.....|.....|..|00000011|1|");
    DECODE_ENTRY(15,     DQUARC_Z23_3, "|111011|.....|.....|.....|..|00000011|1|");
    DECODE_ENTRY(15,      DRRND_Z23_3, "|111011|.....|.....|.....|..|00100011|0|");
    DECODE_ENTRY(15,     DRRNDQ_Z23_3, "|111111|.....|.....|.....|..|00100011|0|");
    DECODE_ENTRY(15,   DRRNDQRC_Z23_3, "|111111|.....|.....|.....|..|00100011|1|");
    DECODE_ENTRY(15,    DRRNDRC_Z23_3, "|111011|.....|.....|.....|..|00100011|1|");

    //                          Z23_6   |  OPCD|  FRT|   X|R|  FRB|RM|      XO|R|
    DECODE_ENTRY(15,     DRINTN_Z23_6, "|111011|.....|....|.|.....|..|11100011|0|");
    DECODE_ENTRY(15,   DRINTNRC_Z23_6, "|111011|.....|....|.|.....|..|11100011|1|");
    DECODE_ENTRY(15,     DRINTX_Z23_6, "|111011|.....|....|.|.....|..|01100011|0|");
    DECODE_ENTRY(15,   DRINTXRC_Z23_6, "|111011|.....|....|.|.....|..|01100011|1|");

    //                          Z23_7   |  OPCD| FRTp|   X|R| FRBp|RM|      XO|R|
    DECODE_ENTRY(15,    DRINTNQ_Z23_7, "|111111|.....|....|.|.....|..|11100011|0|");
    DECODE_ENTRY(15,  DRINTNQRC_Z23_7, "|111111|.....|....|.|.....|..|11100011|1|");
    DECODE_ENTRY(15,    DRINTXQ_Z23_7, "|111111|.....|....|.|.....|..|01100011|0|");
    DECODE_ENTRY(15,  DRINTXQRC_Z23_7, "|111111|.....|....|.|.....|..|01100011|1|");

    return table;
}

// I_MA Decoder
vmidDecodeTableP ppc32CreateDecodeTable_I_MA_32Bit(vmidDecodeTableP current, Bool vle) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(32, PPC32_IT_LAST);
    }

    //                            X12   |  OPCD|   RS|   RA|   RB|        XO|X|
    DECODE_ENTRY(16,        STSWX_X12, "|011111|.....|.....|.....|1010010101|.|");

    //                            X13   |  OPCD|   RS|   RA|   NB|        XO|X|
    DECODE_ENTRY(16,        STSWI_X13, "|011111|.....|.....|.....|1011010101|.|");

    //                             X2   |  OPCD|   RT|   RA|   RB|        XO|X|
    DECODE_ENTRY(16,          LSWX_X2, "|011111|.....|.....|.....|1000010101|.|");

    //                             X4   |  OPCD|   RT|   RA|   NB|        XO|X|
    DECODE_ENTRY(16,          LSWI_X4, "|011111|.....|.....|.....|1001010101|.|");

    return table;
}

// I_SP Decoder
vmidDecodeTableP ppc32CreateDecodeTable_I_SP_32Bit(vmidDecodeTableP current, Bool vle) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(32, PPC32_IT_LAST);
    }

    //                            EVS   |  OPCD|   RT|   RA|   RB|      XO|BFA|
    DECODE_ENTRY(14,        EVSEL_EVS, "|000100|.....|.....|.....|01001111|...|");

    //                           EVX1   |  OPCD|   RS|   RA|   RB|         XO|
    DECODE_ENTRY(17,       BRINC_EVX1, "|000100|.....|.....|.....|01000001111|");
    DECODE_ENTRY(17,     EVSTDDX_EVX1, "|000100|.....|.....|.....|01100100000|");
    DECODE_ENTRY(17,     EVSTDHX_EVX1, "|000100|.....|.....|.....|01100100100|");
    DECODE_ENTRY(17,     EVSTDWX_EVX1, "|000100|.....|.....|.....|01100100010|");
    DECODE_ENTRY(17,    EVSTWHEX_EVX1, "|000100|.....|.....|.....|01100110000|");
    DECODE_ENTRY(17,    EVSTWHOX_EVX1, "|000100|.....|.....|.....|01100110100|");
    DECODE_ENTRY(17,    EVSTWWEX_EVX1, "|000100|.....|.....|.....|01100111000|");
    DECODE_ENTRY(17,    EVSTWWOX_EVX1, "|000100|.....|.....|.....|01100111100|");

    //                         EVX2_2   |  OPCD|   RS|   RA|   UI|         XO|
    DECODE_ENTRY(17,   EVSTWHE_EVX2_2, "|000100|.....|.....|.....|01100110001|");
    DECODE_ENTRY(17,   EVSTWHO_EVX2_2, "|000100|.....|.....|.....|01100110101|");
    DECODE_ENTRY(17,   EVSTWWE_EVX2_2, "|000100|.....|.....|.....|01100111001|");
    DECODE_ENTRY(17,   EVSTWWO_EVX2_2, "|000100|.....|.....|.....|01100111101|");

    //                         EVX2_3   |  OPCD|   RS|   RA|   UI|         XO|
    DECODE_ENTRY(17,    EVSTDD_EVX2_3, "|000100|.....|.....|.....|01100100001|");
    DECODE_ENTRY(17,    EVSTDH_EVX2_3, "|000100|.....|.....|.....|01100100101|");
    DECODE_ENTRY(17,    EVSTDW_EVX2_3, "|000100|.....|.....|.....|01100100011|");

    //                           EVX3   |  OPCD|   RT|    X|   RB|         XO|
    DECODE_ENTRY(17,      EFDCFS_EVX3, "|000100|.....|.....|.....|01011101111|");
    DECODE_ENTRY(17,     EFDCFSF_EVX3, "|000100|.....|.....|.....|01011110011|");
    DECODE_ENTRY(17,     EFDCFSI_EVX3, "|000100|.....|.....|.....|01011110001|");
    DECODE_ENTRY(17,    EFDCFSID_EVX3, "|000100|.....|.....|.....|01011100011|");
    DECODE_ENTRY(17,     EFDCFUF_EVX3, "|000100|.....|.....|.....|01011110010|");
    DECODE_ENTRY(17,     EFDCFUI_EVX3, "|000100|.....|.....|.....|01011110000|");
    DECODE_ENTRY(17,    EFDCFUID_EVX3, "|000100|.....|.....|.....|01011100010|");
    DECODE_ENTRY(17,     EFDCTSF_EVX3, "|000100|.....|.....|.....|01011110111|");
    DECODE_ENTRY(17,     EFDCTSI_EVX3, "|000100|.....|.....|.....|01011110101|");
    DECODE_ENTRY(17,   EFDCTSIDZ_EVX3, "|000100|.....|.....|.....|01011101011|");
    DECODE_ENTRY(17,    EFDCTSIZ_EVX3, "|000100|.....|.....|.....|01011111010|");
    DECODE_ENTRY(17,     EFDCTUF_EVX3, "|000100|.....|.....|.....|01011110110|");
    DECODE_ENTRY(17,     EFDCTUI_EVX3, "|000100|.....|.....|.....|01011110100|");
    DECODE_ENTRY(17,   EFDCTUIDZ_EVX3, "|000100|.....|.....|.....|01011101010|");
    DECODE_ENTRY(17,    EFDCTUIZ_EVX3, "|000100|.....|.....|.....|01011111000|");
    DECODE_ENTRY(17,      EFSCFD_EVX3, "|000100|.....|.....|.....|01011001111|");
    DECODE_ENTRY(17,     EFSCFSF_EVX3, "|000100|.....|.....|.....|01011010011|");
    DECODE_ENTRY(17,     EFSCFSI_EVX3, "|000100|.....|.....|.....|01011010001|");
    DECODE_ENTRY(17,     EFSCFUF_EVX3, "|000100|.....|.....|.....|01011010010|");
    DECODE_ENTRY(17,     EFSCFUI_EVX3, "|000100|.....|.....|.....|01011010000|");
    DECODE_ENTRY(17,     EFSCTSF_EVX3, "|000100|.....|.....|.....|01011010111|");
    DECODE_ENTRY(17,     EFSCTSI_EVX3, "|000100|.....|.....|.....|01011010101|");
    DECODE_ENTRY(17,    EFSCTSIZ_EVX3, "|000100|.....|.....|.....|01011011010|");
    DECODE_ENTRY(17,     EFSCTUF_EVX3, "|000100|.....|.....|.....|01011010110|");
    DECODE_ENTRY(17,     EFSCTUI_EVX3, "|000100|.....|.....|.....|01011010100|");
    DECODE_ENTRY(17,    EFSCTUIZ_EVX3, "|000100|.....|.....|.....|01011011000|");
    DECODE_ENTRY(17,    EVFSCFSF_EVX3, "|000100|.....|.....|.....|01010010011|");
    DECODE_ENTRY(17,    EVFSCFSI_EVX3, "|000100|.....|.....|.....|01010010001|");
    DECODE_ENTRY(17,    EVFSCFUF_EVX3, "|000100|.....|.....|.....|01010010010|");
    DECODE_ENTRY(17,    EVFSCFUI_EVX3, "|000100|.....|.....|.....|01010010000|");
    DECODE_ENTRY(17,    EVFSCTSF_EVX3, "|000100|.....|.....|.....|01010010111|");
    DECODE_ENTRY(17,    EVFSCTSI_EVX3, "|000100|.....|.....|.....|01010010101|");
    DECODE_ENTRY(17,   EVFSCTSIZ_EVX3, "|000100|.....|.....|.....|01010011010|");
    DECODE_ENTRY(17,    EVFSCTUF_EVX3, "|000100|.....|.....|.....|01010010110|");
    DECODE_ENTRY(17,    EVFSCTUI_EVX3, "|000100|.....|.....|.....|01010010100|");
    DECODE_ENTRY(17,   EVFSCTUIZ_EVX3, "|000100|.....|.....|.....|01010011000|");

    //                           EVX4   |  OPCD|   RT|   RA|   RB|         XO|
    DECODE_ENTRY(17,      EFDADD_EVX4, "|000100|.....|.....|.....|01011100000|");
    DECODE_ENTRY(17,      EFDDIV_EVX4, "|000100|.....|.....|.....|01011101001|");
    DECODE_ENTRY(17,      EFDMUL_EVX4, "|000100|.....|.....|.....|01011101000|");
    DECODE_ENTRY(17,      EFDSUB_EVX4, "|000100|.....|.....|.....|01011100001|");
    DECODE_ENTRY(17,      EFSADD_EVX4, "|000100|.....|.....|.....|01011000000|");
    DECODE_ENTRY(17,      EFSDIV_EVX4, "|000100|.....|.....|.....|01011001001|");
    DECODE_ENTRY(17,      EFSMUL_EVX4, "|000100|.....|.....|.....|01011001000|");
    DECODE_ENTRY(17,      EFSSUB_EVX4, "|000100|.....|.....|.....|01011000001|");
    DECODE_ENTRY(17,      EVADDW_EVX4, "|000100|.....|.....|.....|01000000000|");
    DECODE_ENTRY(17,       EVAND_EVX4, "|000100|.....|.....|.....|01000010001|");
    DECODE_ENTRY(17,      EVANDC_EVX4, "|000100|.....|.....|.....|01000010010|");
    DECODE_ENTRY(17,     EVDIVWS_EVX4, "|000100|.....|.....|.....|10011000110|");
    DECODE_ENTRY(17,     EVDIVWU_EVX4, "|000100|.....|.....|.....|10011000111|");
    DECODE_ENTRY(17,       EVEQV_EVX4, "|000100|.....|.....|.....|01000011001|");
    DECODE_ENTRY(17,     EVFSADD_EVX4, "|000100|.....|.....|.....|01010000000|");
    DECODE_ENTRY(17,     EVFSDIV_EVX4, "|000100|.....|.....|.....|01010001001|");
    DECODE_ENTRY(17,     EVFSMUL_EVX4, "|000100|.....|.....|.....|01010001000|");
    DECODE_ENTRY(17,     EVFSSUB_EVX4, "|000100|.....|.....|.....|01010000001|");
    DECODE_ENTRY(17,      EVLDDX_EVX4, "|000100|.....|.....|.....|01100000000|");
    DECODE_ENTRY(17,      EVLDHX_EVX4, "|000100|.....|.....|.....|01100000100|");
    DECODE_ENTRY(17,      EVLDWX_EVX4, "|000100|.....|.....|.....|01100000010|");
    DECODE_ENTRY(17, EVLHHESPLATX_EVX4, "|000100|.....|.....|.....|01100001000|");
    DECODE_ENTRY(17, EVLHHOSSPLATX_EVX4, "|000100|.....|.....|.....|01100001110|");
    DECODE_ENTRY(17, EVLHHOUSPLATX_EVX4, "|000100|.....|.....|.....|01100001100|");
    DECODE_ENTRY(17,     EVLWHEX_EVX4, "|000100|.....|.....|.....|01100010000|");
    DECODE_ENTRY(17,    EVLWHOSX_EVX4, "|000100|.....|.....|.....|01100010110|");
    DECODE_ENTRY(17,    EVLWHOUX_EVX4, "|000100|.....|.....|.....|01100010100|");
    DECODE_ENTRY(17, EVLWHSPLATX_EVX4, "|000100|.....|.....|.....|01100011100|");
    DECODE_ENTRY(17, EVLWWSPLATX_EVX4, "|000100|.....|.....|.....|01100011000|");
    DECODE_ENTRY(17,   EVMERGEHI_EVX4, "|000100|.....|.....|.....|01000101100|");
    DECODE_ENTRY(17, EVMERGEHILO_EVX4, "|000100|.....|.....|.....|01000101110|");
    DECODE_ENTRY(17,   EVMERGELO_EVX4, "|000100|.....|.....|.....|01000101101|");
    DECODE_ENTRY(17, EVMERGELOHI_EVX4, "|000100|.....|.....|.....|01000101111|");
    DECODE_ENTRY(17, EVMHEGSMFAA_EVX4, "|000100|.....|.....|.....|10100101011|");
    DECODE_ENTRY(17, EVMHEGSMFAN_EVX4, "|000100|.....|.....|.....|10110101011|");
    DECODE_ENTRY(17, EVMHEGSMIAA_EVX4, "|000100|.....|.....|.....|10100101001|");
    DECODE_ENTRY(17, EVMHEGSMIAN_EVX4, "|000100|.....|.....|.....|10110101001|");
    DECODE_ENTRY(17, EVMHEGUMIAA_EVX4, "|000100|.....|.....|.....|10100101000|");
    DECODE_ENTRY(17, EVMHEGUMIAN_EVX4, "|000100|.....|.....|.....|10110101000|");
    DECODE_ENTRY(17,    EVMHESMF_EVX4, "|000100|.....|.....|.....|10000001011|");
    DECODE_ENTRY(17,   EVMHESMFA_EVX4, "|000100|.....|.....|.....|10000101011|");
    DECODE_ENTRY(17, EVMHESMFAAW_EVX4, "|000100|.....|.....|.....|10100001011|");
    DECODE_ENTRY(17, EVMHESMFANW_EVX4, "|000100|.....|.....|.....|10110001011|");
    DECODE_ENTRY(17,    EVMHESMI_EVX4, "|000100|.....|.....|.....|10000001001|");
    DECODE_ENTRY(17,   EVMHESMIA_EVX4, "|000100|.....|.....|.....|10000101001|");
    DECODE_ENTRY(17, EVMHESMIAAW_EVX4, "|000100|.....|.....|.....|10100001001|");
    DECODE_ENTRY(17, EVMHESMIANW_EVX4, "|000100|.....|.....|.....|10110001001|");
    DECODE_ENTRY(17,    EVMHESSF_EVX4, "|000100|.....|.....|.....|10000000011|");
    DECODE_ENTRY(17,   EVMHESSFA_EVX4, "|000100|.....|.....|.....|10000100011|");
    DECODE_ENTRY(17, EVMHESSFAAW_EVX4, "|000100|.....|.....|.....|10100000011|");
    DECODE_ENTRY(17, EVMHESSFANW_EVX4, "|000100|.....|.....|.....|10110000011|");
    DECODE_ENTRY(17, EVMHESSIAAW_EVX4, "|000100|.....|.....|.....|10100000001|");
    DECODE_ENTRY(17, EVMHESSIANW_EVX4, "|000100|.....|.....|.....|10110000001|");
    DECODE_ENTRY(17,    EVMHEUMI_EVX4, "|000100|.....|.....|.....|10000001000|");
    DECODE_ENTRY(17,   EVMHEUMIA_EVX4, "|000100|.....|.....|.....|10000101000|");
    DECODE_ENTRY(17, EVMHEUMIAAW_EVX4, "|000100|.....|.....|.....|10100001000|");
    DECODE_ENTRY(17, EVMHEUMIANW_EVX4, "|000100|.....|.....|.....|10110001000|");
    DECODE_ENTRY(17, EVMHEUSIAAW_EVX4, "|000100|.....|.....|.....|10100000000|");
    DECODE_ENTRY(17, EVMHEUSIANW_EVX4, "|000100|.....|.....|.....|10110000000|");
    DECODE_ENTRY(17, EVMHOGSMFAA_EVX4, "|000100|.....|.....|.....|10100101111|");
    DECODE_ENTRY(17, EVMHOGSMFAN_EVX4, "|000100|.....|.....|.....|10110101111|");
    DECODE_ENTRY(17, EVMHOGSMIAA_EVX4, "|000100|.....|.....|.....|10100101101|");
    DECODE_ENTRY(17, EVMHOGSMIAN_EVX4, "|000100|.....|.....|.....|10110101101|");
    DECODE_ENTRY(17, EVMHOGUMIAA_EVX4, "|000100|.....|.....|.....|10100101100|");
    DECODE_ENTRY(17, EVMHOGUMIAN_EVX4, "|000100|.....|.....|.....|10110101100|");
    DECODE_ENTRY(17,    EVMHOSMF_EVX4, "|000100|.....|.....|.....|10000001111|");
    DECODE_ENTRY(17,   EVMHOSMFA_EVX4, "|000100|.....|.....|.....|10000101111|");
    DECODE_ENTRY(17, EVMHOSMFAAW_EVX4, "|000100|.....|.....|.....|10100001111|");
    DECODE_ENTRY(17, EVMHOSMFANW_EVX4, "|000100|.....|.....|.....|10110001111|");
    DECODE_ENTRY(17,    EVMHOSMI_EVX4, "|000100|.....|.....|.....|10000001101|");
    DECODE_ENTRY(17,   EVMHOSMIA_EVX4, "|000100|.....|.....|.....|10000101101|");
    DECODE_ENTRY(17, EVMHOSMIAAW_EVX4, "|000100|.....|.....|.....|10100001101|");
    DECODE_ENTRY(17, EVMHOSMIANW_EVX4, "|000100|.....|.....|.....|10110001101|");
    DECODE_ENTRY(17,    EVMHOSSF_EVX4, "|000100|.....|.....|.....|10000000111|");
    DECODE_ENTRY(17,   EVMHOSSFA_EVX4, "|000100|.....|.....|.....|10000100111|");
    DECODE_ENTRY(17, EVMHOSSFAAW_EVX4, "|000100|.....|.....|.....|10100000111|");
    DECODE_ENTRY(17, EVMHOSSFANW_EVX4, "|000100|.....|.....|.....|10110000111|");
    DECODE_ENTRY(17, EVMHOSSIAAW_EVX4, "|000100|.....|.....|.....|10100000101|");
    DECODE_ENTRY(17, EVMHOSSIANW_EVX4, "|000100|.....|.....|.....|10110000101|");
    DECODE_ENTRY(17,    EVMHOUMI_EVX4, "|000100|.....|.....|.....|10000001100|");
    DECODE_ENTRY(17,   EVMHOUMIA_EVX4, "|000100|.....|.....|.....|10000101100|");
    DECODE_ENTRY(17, EVMHOUMIAAW_EVX4, "|000100|.....|.....|.....|10100001100|");
    DECODE_ENTRY(17, EVMHOUMIANW_EVX4, "|000100|.....|.....|.....|10110001100|");
    DECODE_ENTRY(17, EVMHOUSIAAW_EVX4, "|000100|.....|.....|.....|10100000100|");
    DECODE_ENTRY(17, EVMHOUSIANW_EVX4, "|000100|.....|.....|.....|10110000100|");
    DECODE_ENTRY(17,    EVMWHSMF_EVX4, "|000100|.....|.....|.....|10001001111|");
    DECODE_ENTRY(17,   EVMWHSMFA_EVX4, "|000100|.....|.....|.....|10001101111|");
    DECODE_ENTRY(17,    EVMWHSMI_EVX4, "|000100|.....|.....|.....|10001001101|");
    DECODE_ENTRY(17,   EVMWHSMIA_EVX4, "|000100|.....|.....|.....|10001101101|");
    DECODE_ENTRY(17,    EVMWHSSF_EVX4, "|000100|.....|.....|.....|10001000111|");
    DECODE_ENTRY(17,   EVMWHSSFA_EVX4, "|000100|.....|.....|.....|10001100111|");
    DECODE_ENTRY(17,    EVMWHUMI_EVX4, "|000100|.....|.....|.....|10001001100|");
    DECODE_ENTRY(17,   EVMWHUMIA_EVX4, "|000100|.....|.....|.....|10001101100|");
    DECODE_ENTRY(17, EVMWLSMIAAW_EVX4, "|000100|.....|.....|.....|10101001001|");
    DECODE_ENTRY(17, EVMWLSMIANW_EVX4, "|000100|.....|.....|.....|10111001001|");
    DECODE_ENTRY(17, EVMWLSSIAAW_EVX4, "|000100|.....|.....|.....|10101000001|");
    DECODE_ENTRY(17, EVMWLSSIANW_EVX4, "|000100|.....|.....|.....|10111000001|");
    DECODE_ENTRY(17,    EVMWLUMI_EVX4, "|000100|.....|.....|.....|10001001000|");
    DECODE_ENTRY(17,   EVMWLUMIA_EVX4, "|000100|.....|.....|.....|10001101000|");
    DECODE_ENTRY(17, EVMWLUMIAAW_EVX4, "|000100|.....|.....|.....|10101001000|");
    DECODE_ENTRY(17, EVMWLUMIANW_EVX4, "|000100|.....|.....|.....|10111001000|");
    DECODE_ENTRY(17, EVMWLUSIAAW_EVX4, "|000100|.....|.....|.....|10101000000|");
    DECODE_ENTRY(17, EVMWLUSIANW_EVX4, "|000100|.....|.....|.....|10111000000|");
    DECODE_ENTRY(17,     EVMWSMF_EVX4, "|000100|.....|.....|.....|10001011011|");
    DECODE_ENTRY(17,    EVMWSMFA_EVX4, "|000100|.....|.....|.....|10001111011|");
    DECODE_ENTRY(17,   EVMWSMFAA_EVX4, "|000100|.....|.....|.....|10101011011|");
    DECODE_ENTRY(17,   EVMWSMFAN_EVX4, "|000100|.....|.....|.....|10111011011|");
    DECODE_ENTRY(17,     EVMWSMI_EVX4, "|000100|.....|.....|.....|10001011001|");
    DECODE_ENTRY(17,    EVMWSMIA_EVX4, "|000100|.....|.....|.....|10001111001|");
    DECODE_ENTRY(17,   EVMWSMIAA_EVX4, "|000100|.....|.....|.....|10101011001|");
    DECODE_ENTRY(17,   EVMWSMIAN_EVX4, "|000100|.....|.....|.....|10111011001|");
    DECODE_ENTRY(17,     EVMWSSF_EVX4, "|000100|.....|.....|.....|10001010011|");
    DECODE_ENTRY(17,    EVMWSSFA_EVX4, "|000100|.....|.....|.....|10001110011|");
    DECODE_ENTRY(17,   EVMWSSFAA_EVX4, "|000100|.....|.....|.....|10101010011|");
    DECODE_ENTRY(17,   EVMWSSFAN_EVX4, "|000100|.....|.....|.....|10111010011|");
    DECODE_ENTRY(17,     EVMWUMI_EVX4, "|000100|.....|.....|.....|10001011000|");
    DECODE_ENTRY(17,    EVMWUMIA_EVX4, "|000100|.....|.....|.....|10001111000|");
    DECODE_ENTRY(17,   EVMWUMIAA_EVX4, "|000100|.....|.....|.....|10101011000|");
    DECODE_ENTRY(17,   EVMWUMIAN_EVX4, "|000100|.....|.....|.....|10111011000|");
    DECODE_ENTRY(17,      EVNAND_EVX4, "|000100|.....|.....|.....|01000011110|");
    DECODE_ENTRY(17,       EVNOR_EVX4, "|000100|.....|.....|.....|01000011000|");
    DECODE_ENTRY(17,        EVOR_EVX4, "|000100|.....|.....|.....|01000010111|");
    DECODE_ENTRY(17,       EVORC_EVX4, "|000100|.....|.....|.....|01000011011|");
    DECODE_ENTRY(17,       EVRLW_EVX4, "|000100|.....|.....|.....|01000101000|");
    DECODE_ENTRY(17,       EVSLW_EVX4, "|000100|.....|.....|.....|01000100100|");
    DECODE_ENTRY(17,      EVSRWS_EVX4, "|000100|.....|.....|.....|01000100001|");
    DECODE_ENTRY(17,      EVSRWU_EVX4, "|000100|.....|.....|.....|01000100000|");
    DECODE_ENTRY(17,     EVSUBFW_EVX4, "|000100|.....|.....|.....|01000000100|");
    DECODE_ENTRY(17,       EVXOR_EVX4, "|000100|.....|.....|.....|01000010110|");

    //                           EVX5   |  OPCD|   RT|   RA|    X|         XO|
    DECODE_ENTRY(17,      EFDABS_EVX5, "|000100|.....|.....|.....|01011100100|");
    DECODE_ENTRY(17,     EFDNABS_EVX5, "|000100|.....|.....|.....|01011100101|");
    DECODE_ENTRY(17,      EFDNEG_EVX5, "|000100|.....|.....|.....|01011100110|");
    DECODE_ENTRY(17,      EFSABS_EVX5, "|000100|.....|.....|.....|01011000100|");
    DECODE_ENTRY(17,     EFSNABS_EVX5, "|000100|.....|.....|.....|01011000101|");
    DECODE_ENTRY(17,      EFSNEG_EVX5, "|000100|.....|.....|.....|01011000110|");
    DECODE_ENTRY(17,       EVABS_EVX5, "|000100|.....|.....|.....|01000001000|");
    DECODE_ENTRY(17, EVADDSMIAAW_EVX5, "|000100|.....|.....|.....|10011001001|");
    DECODE_ENTRY(17, EVADDSSIAAW_EVX5, "|000100|.....|.....|.....|10011000001|");
    DECODE_ENTRY(17, EVADDUMIAAW_EVX5, "|000100|.....|.....|.....|10011001000|");
    DECODE_ENTRY(17, EVADDUSIAAW_EVX5, "|000100|.....|.....|.....|10011000000|");
    DECODE_ENTRY(17,    EVCNTLSW_EVX5, "|000100|.....|.....|.....|01000001110|");
    DECODE_ENTRY(17,    EVCNTLZW_EVX5, "|000100|.....|.....|.....|01000001101|");
    DECODE_ENTRY(17,     EVEXTSB_EVX5, "|000100|.....|.....|.....|01000001010|");
    DECODE_ENTRY(17,     EVEXTSH_EVX5, "|000100|.....|.....|.....|01000001011|");
    DECODE_ENTRY(17,     EVFSABS_EVX5, "|000100|.....|.....|.....|01010000100|");
    DECODE_ENTRY(17,    EVFSNABS_EVX5, "|000100|.....|.....|.....|01010000101|");
    DECODE_ENTRY(17,     EVFSNEG_EVX5, "|000100|.....|.....|.....|01010000110|");
    DECODE_ENTRY(17,       EVMRA_EVX5, "|000100|.....|.....|.....|10011000100|");
    DECODE_ENTRY(17,       EVNEG_EVX5, "|000100|.....|.....|.....|01000001001|");
    DECODE_ENTRY(17,      EVRNDW_EVX5, "|000100|.....|.....|.....|01000001100|");
    DECODE_ENTRY(17, EVSUBFSMIAAW_EVX5, "|000100|.....|.....|.....|10011001011|");
    DECODE_ENTRY(17, EVSUBFSSIAAW_EVX5, "|000100|.....|.....|.....|10011000011|");
    DECODE_ENTRY(17, EVSUBFUMIAAW_EVX5, "|000100|.....|.....|.....|10011001010|");
    DECODE_ENTRY(17, EVSUBFUSIAAW_EVX5, "|000100|.....|.....|.....|10011000010|");

    //                         EVX6_1   |  OPCD|   RT|   UI|   RB|         XO|
    DECODE_ENTRY(17,   EVADDIW_EVX6_1, "|000100|.....|.....|.....|01000000010|");

    //                         EVX6_2   |  OPCD|   RT|   UI|   RB|         XO|
    DECODE_ENTRY(17,  EVSUBIFW_EVX6_2, "|000100|.....|.....|.....|01000000110|");

    //                           EVX7   |  OPCD| BF| X|   RA|   RB|         XO|
    DECODE_ENTRY(17,    EFDCMPEQ_EVX7, "|000100|...|..|.....|.....|01011101110|");
    DECODE_ENTRY(17,    EFDCMPGT_EVX7, "|000100|...|..|.....|.....|01011101100|");
    DECODE_ENTRY(17,    EFDCMPLT_EVX7, "|000100|...|..|.....|.....|01011101101|");
    DECODE_ENTRY(17,    EFDTSTEQ_EVX7, "|000100|...|..|.....|.....|01011111110|");
    DECODE_ENTRY(17,    EFDTSTGT_EVX7, "|000100|...|..|.....|.....|01011111100|");
    DECODE_ENTRY(17,    EFDTSTLT_EVX7, "|000100|...|..|.....|.....|01011111101|");
    DECODE_ENTRY(17,    EFSCMPEQ_EVX7, "|000100|...|..|.....|.....|01011001110|");
    DECODE_ENTRY(17,    EFSCMPGT_EVX7, "|000100|...|..|.....|.....|01011001100|");
    DECODE_ENTRY(17,    EFSCMPLT_EVX7, "|000100|...|..|.....|.....|01011001101|");
    DECODE_ENTRY(17,    EFSTSTEQ_EVX7, "|000100|...|..|.....|.....|01011011110|");
    DECODE_ENTRY(17,    EFSTSTGT_EVX7, "|000100|...|..|.....|.....|01011011100|");
    DECODE_ENTRY(17,    EFSTSTLT_EVX7, "|000100|...|..|.....|.....|01011011101|");
    DECODE_ENTRY(17,     EVCMPEQ_EVX7, "|000100|...|..|.....|.....|01000110100|");
    DECODE_ENTRY(17,    EVCMPGTS_EVX7, "|000100|...|..|.....|.....|01000110001|");
    DECODE_ENTRY(17,    EVCMPGTU_EVX7, "|000100|...|..|.....|.....|01000110000|");
    DECODE_ENTRY(17,    EVCMPLTS_EVX7, "|000100|...|..|.....|.....|01000110011|");
    DECODE_ENTRY(17,    EVCMPLTU_EVX7, "|000100|...|..|.....|.....|01000110010|");
    DECODE_ENTRY(17,   EVFSCMPEQ_EVX7, "|000100|...|..|.....|.....|01010001110|");
    DECODE_ENTRY(17,   EVFSCMPGT_EVX7, "|000100|...|..|.....|.....|01010001100|");
    DECODE_ENTRY(17,   EVFSCMPLT_EVX7, "|000100|...|..|.....|.....|01010001101|");
    DECODE_ENTRY(17,   EVFSTSTEQ_EVX7, "|000100|...|..|.....|.....|01010011110|");
    DECODE_ENTRY(17,   EVFSTSTGT_EVX7, "|000100|...|..|.....|.....|01010011100|");
    DECODE_ENTRY(17,   EVFSTSTLT_EVX7, "|000100|...|..|.....|.....|01010011101|");

    //                           EVX8   |  OPCD|   RT|   RA|   UI|         XO|
    DECODE_ENTRY(17,      EVRLWI_EVX8, "|000100|.....|.....|.....|01000101010|");
    DECODE_ENTRY(17,      EVSLWI_EVX8, "|000100|.....|.....|.....|01000100110|");
    DECODE_ENTRY(17,     EVSRWIS_EVX8, "|000100|.....|.....|.....|01000100011|");
    DECODE_ENTRY(17,     EVSRWIU_EVX8, "|000100|.....|.....|.....|01000100010|");

    //                         EVX8_1   |  OPCD|   RT|   RA|   UI|         XO|
    DECODE_ENTRY(17, EVLHHESPLAT_EVX8_1, "|000100|.....|.....|.....|01100001001|");
    DECODE_ENTRY(17, EVLHHOSSPLAT_EVX8_1, "|000100|.....|.....|.....|01100001111|");
    DECODE_ENTRY(17, EVLHHOUSPLAT_EVX8_1, "|000100|.....|.....|.....|01100001101|");

    //                         EVX8_2   |  OPCD|   RT|   RA|   UI|         XO|
    DECODE_ENTRY(17,    EVLWHE_EVX8_2, "|000100|.....|.....|.....|01100010001|");
    DECODE_ENTRY(17,   EVLWHOS_EVX8_2, "|000100|.....|.....|.....|01100010111|");
    DECODE_ENTRY(17,   EVLWHOU_EVX8_2, "|000100|.....|.....|.....|01100010101|");
    DECODE_ENTRY(17, EVLWHSPLAT_EVX8_2, "|000100|.....|.....|.....|01100011101|");
    DECODE_ENTRY(17, EVLWWSPLAT_EVX8_2, "|000100|.....|.....|.....|01100011001|");

    //                         EVX8_3   |  OPCD|   RT|   RA|   UI|         XO|
    DECODE_ENTRY(17,     EVLDD_EVX8_3, "|000100|.....|.....|.....|01100000001|");
    DECODE_ENTRY(17,     EVLDH_EVX8_3, "|000100|.....|.....|.....|01100000101|");
    DECODE_ENTRY(17,     EVLDW_EVX8_3, "|000100|.....|.....|.....|01100000011|");

    //                           EVX9   |  OPCD|   RT|   SI|    X|         XO|
    DECODE_ENTRY(17,   EVSPLATFI_EVX9, "|000100|.....|.....|.....|01000101011|");
    DECODE_ENTRY(17,    EVSPLATI_EVX9, "|000100|.....|.....|.....|01000101001|");

    return table;
}

// I_V Decoder
vmidDecodeTableP ppc32CreateDecodeTable_I_V_32Bit(vmidDecodeTableP current, Bool vle) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(32, PPC32_IT_LAST);
    }

    //                          VA1_0   |  OPCD|  VRT|  VRA|  VRB|  VRC|    XO|
    DECODE_ENTRY(12,  VMHADDSHS_VA1_0, "|000100|.....|.....|.....|.....|100000|");
    DECODE_ENTRY(12, VMHRADDSHS_VA1_0, "|000100|.....|.....|.....|.....|100001|");
    DECODE_ENTRY(12,  VMLADDUHM_VA1_0, "|000100|.....|.....|.....|.....|100010|");
    DECODE_ENTRY(12,   VMSUMMBM_VA1_0, "|000100|.....|.....|.....|.....|100101|");
    DECODE_ENTRY(12,   VMSUMSHM_VA1_0, "|000100|.....|.....|.....|.....|101000|");
    DECODE_ENTRY(12,   VMSUMSHS_VA1_0, "|000100|.....|.....|.....|.....|101001|");
    DECODE_ENTRY(12,   VMSUMUBM_VA1_0, "|000100|.....|.....|.....|.....|100100|");
    DECODE_ENTRY(12,   VMSUMUHM_VA1_0, "|000100|.....|.....|.....|.....|100110|");
    DECODE_ENTRY(12,   VMSUMUHS_VA1_0, "|000100|.....|.....|.....|.....|100111|");
    DECODE_ENTRY(12,      VPERM_VA1_0, "|000100|.....|.....|.....|.....|101011|");
    DECODE_ENTRY(12,       VSEL_VA1_0, "|000100|.....|.....|.....|.....|101010|");

    //                          VA1_1   |  OPCD|  VRT|  VRA|  VRB|  VRC|    XO|
    DECODE_ENTRY(12,    VMADDFP_VA1_1, "|000100|.....|.....|.....|.....|101110|");
    DECODE_ENTRY(12,    VMSUBFP_VA1_1, "|000100|.....|.....|.....|.....|101111|");

    //                            VA2   |  OPCD|  VRT|  VRA|  VRB|X| SHB|    XO|
    DECODE_ENTRY(12,       VSLDOI_VA2, "|000100|.....|.....|.....|.|....|101100|");

    //                            VC1   |  OPCD|  VRT|  VRA|  VRB|R|        XO|
    DECODE_ENTRY(17,      VCMPBFP_VC1, "|000100|.....|.....|.....|0|1111000110|");
    DECODE_ENTRY(17,    VCMPBFPRC_VC1, "|000100|.....|.....|.....|1|1111000110|");
    DECODE_ENTRY(17,     VCMPEQFP_VC1, "|000100|.....|.....|.....|0|0011000110|");
    DECODE_ENTRY(17,   VCMPEQFPRC_VC1, "|000100|.....|.....|.....|1|0011000110|");
    DECODE_ENTRY(17,     VCMPEQUB_VC1, "|000100|.....|.....|.....|0|0000000110|");
    DECODE_ENTRY(17,   VCMPEQUBRC_VC1, "|000100|.....|.....|.....|1|0000000110|");
    DECODE_ENTRY(17,     VCMPEQUH_VC1, "|000100|.....|.....|.....|0|0001000110|");
    DECODE_ENTRY(17,   VCMPEQUHRC_VC1, "|000100|.....|.....|.....|1|0001000110|");
    DECODE_ENTRY(17,     VCMPEQUW_VC1, "|000100|.....|.....|.....|0|0010000110|");
    DECODE_ENTRY(17,   VCMPEQUWRC_VC1, "|000100|.....|.....|.....|1|0010000110|");
    DECODE_ENTRY(17,     VCMPGEFP_VC1, "|000100|.....|.....|.....|0|0111000110|");
    DECODE_ENTRY(17,   VCMPGEFPRC_VC1, "|000100|.....|.....|.....|1|0111000110|");
    DECODE_ENTRY(17,     VCMPGTFP_VC1, "|000100|.....|.....|.....|0|1011000110|");
    DECODE_ENTRY(17,   VCMPGTFPRC_VC1, "|000100|.....|.....|.....|1|1011000110|");
    DECODE_ENTRY(17,     VCMPGTSB_VC1, "|000100|.....|.....|.....|0|1100000110|");
    DECODE_ENTRY(17,   VCMPGTSBRC_VC1, "|000100|.....|.....|.....|1|1100000110|");
    DECODE_ENTRY(17,     VCMPGTSH_VC1, "|000100|.....|.....|.....|0|1101000110|");
    DECODE_ENTRY(17,   VCMPGTSHRC_VC1, "|000100|.....|.....|.....|1|1101000110|");
    DECODE_ENTRY(17,     VCMPGTSW_VC1, "|000100|.....|.....|.....|0|1110000110|");
    DECODE_ENTRY(17,   VCMPGTSWRC_VC1, "|000100|.....|.....|.....|1|1110000110|");
    DECODE_ENTRY(17,     VCMPGTUB_VC1, "|000100|.....|.....|.....|0|1000000110|");
    DECODE_ENTRY(17,   VCMPGTUBRC_VC1, "|000100|.....|.....|.....|1|1000000110|");
    DECODE_ENTRY(17,     VCMPGTUH_VC1, "|000100|.....|.....|.....|0|1001000110|");
    DECODE_ENTRY(17,   VCMPGTUHRC_VC1, "|000100|.....|.....|.....|1|1001000110|");
    DECODE_ENTRY(17,     VCMPGTUW_VC1, "|000100|.....|.....|.....|0|1010000110|");
    DECODE_ENTRY(17,   VCMPGTUWRC_VC1, "|000100|.....|.....|.....|1|1010000110|");

    //                            VX1   |  OPCD|  VRT|  VRA|  VRB|         XO|
    DECODE_ENTRY(17,      VADDCUW_VX1, "|000100|.....|.....|.....|00110000000|");
    DECODE_ENTRY(17,       VADDFP_VX1, "|000100|.....|.....|.....|00000001010|");
    DECODE_ENTRY(17,      VADDSBS_VX1, "|000100|.....|.....|.....|01100000000|");
    DECODE_ENTRY(17,      VADDSHS_VX1, "|000100|.....|.....|.....|01101000000|");
    DECODE_ENTRY(17,      VADDSWS_VX1, "|000100|.....|.....|.....|01110000000|");
    DECODE_ENTRY(17,      VADDUBM_VX1, "|000100|.....|.....|.....|00000000000|");
    DECODE_ENTRY(17,      VADDUBS_VX1, "|000100|.....|.....|.....|01000000000|");
    DECODE_ENTRY(17,      VADDUHM_VX1, "|000100|.....|.....|.....|00001000000|");
    DECODE_ENTRY(17,      VADDUHS_VX1, "|000100|.....|.....|.....|01001000000|");
    DECODE_ENTRY(17,      VADDUWM_VX1, "|000100|.....|.....|.....|00010000000|");
    DECODE_ENTRY(17,      VADDUWS_VX1, "|000100|.....|.....|.....|01010000000|");
    DECODE_ENTRY(17,         VAND_VX1, "|000100|.....|.....|.....|10000000100|");
    DECODE_ENTRY(17,        VANDC_VX1, "|000100|.....|.....|.....|10001000100|");
    DECODE_ENTRY(17,       VAVGSB_VX1, "|000100|.....|.....|.....|10100000010|");
    DECODE_ENTRY(17,       VAVGSH_VX1, "|000100|.....|.....|.....|10101000010|");
    DECODE_ENTRY(17,       VAVGSW_VX1, "|000100|.....|.....|.....|10110000010|");
    DECODE_ENTRY(17,       VAVGUB_VX1, "|000100|.....|.....|.....|10000000010|");
    DECODE_ENTRY(17,       VAVGUH_VX1, "|000100|.....|.....|.....|10001000010|");
    DECODE_ENTRY(17,       VAVGUW_VX1, "|000100|.....|.....|.....|10010000010|");
    DECODE_ENTRY(17,        VKPPX_VX1, "|000100|.....|.....|.....|01100001110|");
    DECODE_ENTRY(17,      VKPSHSS_VX1, "|000100|.....|.....|.....|00110001110|");
    DECODE_ENTRY(17,      VKPSHUS_VX1, "|000100|.....|.....|.....|00100001110|");
    DECODE_ENTRY(17,      VKPSWSS_VX1, "|000100|.....|.....|.....|00111001110|");
    DECODE_ENTRY(17,      VKPSWUS_VX1, "|000100|.....|.....|.....|00101001110|");
    DECODE_ENTRY(17,      VKPUHUM_VX1, "|000100|.....|.....|.....|00000001110|");
    DECODE_ENTRY(17,      VKPUHUS_VX1, "|000100|.....|.....|.....|00010001110|");
    DECODE_ENTRY(17,      VKPUWUM_VX1, "|000100|.....|.....|.....|00001001110|");
    DECODE_ENTRY(17,      VKPUWUS_VX1, "|000100|.....|.....|.....|00011001110|");
    DECODE_ENTRY(17,       VMAXFP_VX1, "|000100|.....|.....|.....|10000001010|");
    DECODE_ENTRY(17,       VMAXSB_VX1, "|000100|.....|.....|.....|00100000010|");
    DECODE_ENTRY(17,       VMAXSH_VX1, "|000100|.....|.....|.....|00101000010|");
    DECODE_ENTRY(17,       VMAXSW_VX1, "|000100|.....|.....|.....|00110000010|");
    DECODE_ENTRY(17,       VMAXUB_VX1, "|000100|.....|.....|.....|00000000010|");
    DECODE_ENTRY(17,       VMAXUH_VX1, "|000100|.....|.....|.....|00001000010|");
    DECODE_ENTRY(17,       VMAXUW_VX1, "|000100|.....|.....|.....|00010000010|");
    DECODE_ENTRY(17,       VMINFP_VX1, "|000100|.....|.....|.....|10001001010|");
    DECODE_ENTRY(17,       VMINSB_VX1, "|000100|.....|.....|.....|01100000010|");
    DECODE_ENTRY(17,       VMINSH_VX1, "|000100|.....|.....|.....|01101000010|");
    DECODE_ENTRY(17,       VMINSW_VX1, "|000100|.....|.....|.....|01110000010|");
    DECODE_ENTRY(17,       VMINUB_VX1, "|000100|.....|.....|.....|01000000010|");
    DECODE_ENTRY(17,       VMINUH_VX1, "|000100|.....|.....|.....|01001000010|");
    DECODE_ENTRY(17,       VMINUW_VX1, "|000100|.....|.....|.....|01010000010|");
    DECODE_ENTRY(17,       VMRGHB_VX1, "|000100|.....|.....|.....|00000001100|");
    DECODE_ENTRY(17,       VMRGHH_VX1, "|000100|.....|.....|.....|00001001100|");
    DECODE_ENTRY(17,       VMRGHW_VX1, "|000100|.....|.....|.....|00010001100|");
    DECODE_ENTRY(17,       VMRGLB_VX1, "|000100|.....|.....|.....|00100001100|");
    DECODE_ENTRY(17,       VMRGLH_VX1, "|000100|.....|.....|.....|00101001100|");
    DECODE_ENTRY(17,       VMRGLW_VX1, "|000100|.....|.....|.....|00110001100|");
    DECODE_ENTRY(17,      VMULESB_VX1, "|000100|.....|.....|.....|01100001000|");
    DECODE_ENTRY(17,      VMULESH_VX1, "|000100|.....|.....|.....|01101001000|");
    DECODE_ENTRY(17,      VMULEUB_VX1, "|000100|.....|.....|.....|01000001000|");
    DECODE_ENTRY(17,      VMULEUH_VX1, "|000100|.....|.....|.....|01001001000|");
    DECODE_ENTRY(17,      VMULOSB_VX1, "|000100|.....|.....|.....|00100001000|");
    DECODE_ENTRY(17,      VMULOSH_VX1, "|000100|.....|.....|.....|00101001000|");
    DECODE_ENTRY(17,      VMULOUB_VX1, "|000100|.....|.....|.....|00000001000|");
    DECODE_ENTRY(17,      VMULOUH_VX1, "|000100|.....|.....|.....|00001001000|");
    DECODE_ENTRY(17,         VNOR_VX1, "|000100|.....|.....|.....|10100000100|");
    DECODE_ENTRY(17,          VOR_VX1, "|000100|.....|.....|.....|10010000100|");
    DECODE_ENTRY(17,         VRLB_VX1, "|000100|.....|.....|.....|00000000100|");
    DECODE_ENTRY(17,         VRLH_VX1, "|000100|.....|.....|.....|00001000100|");
    DECODE_ENTRY(17,         VRLW_VX1, "|000100|.....|.....|.....|00010000100|");
    DECODE_ENTRY(17,          VSL_VX1, "|000100|.....|.....|.....|00111000100|");
    DECODE_ENTRY(17,         VSLB_VX1, "|000100|.....|.....|.....|00100000100|");
    DECODE_ENTRY(17,         VSLH_VX1, "|000100|.....|.....|.....|00101000100|");
    DECODE_ENTRY(17,         VSLO_VX1, "|000100|.....|.....|.....|10000001100|");
    DECODE_ENTRY(17,         VSLW_VX1, "|000100|.....|.....|.....|00110000100|");
    DECODE_ENTRY(17,          VSR_VX1, "|000100|.....|.....|.....|01011000100|");
    DECODE_ENTRY(17,        VSRAB_VX1, "|000100|.....|.....|.....|01100000100|");
    DECODE_ENTRY(17,        VSRAH_VX1, "|000100|.....|.....|.....|01101000100|");
    DECODE_ENTRY(17,        VSRAW_VX1, "|000100|.....|.....|.....|01110000100|");
    DECODE_ENTRY(17,         VSRB_VX1, "|000100|.....|.....|.....|01000000100|");
    DECODE_ENTRY(17,         VSRH_VX1, "|000100|.....|.....|.....|01001000100|");
    DECODE_ENTRY(17,         VSRO_VX1, "|000100|.....|.....|.....|10001001100|");
    DECODE_ENTRY(17,         VSRW_VX1, "|000100|.....|.....|.....|01010000100|");
    DECODE_ENTRY(17,      VSUBCUW_VX1, "|000100|.....|.....|.....|10110000000|");
    DECODE_ENTRY(17,       VSUBFP_VX1, "|000100|.....|.....|.....|00001001010|");
    DECODE_ENTRY(17,      VSUBSBS_VX1, "|000100|.....|.....|.....|11100000000|");
    DECODE_ENTRY(17,      VSUBSHS_VX1, "|000100|.....|.....|.....|11101000000|");
    DECODE_ENTRY(17,      VSUBSWS_VX1, "|000100|.....|.....|.....|11110000000|");
    DECODE_ENTRY(17,      VSUBUBM_VX1, "|000100|.....|.....|.....|10000000000|");
    DECODE_ENTRY(17,      VSUBUBS_VX1, "|000100|.....|.....|.....|11000000000|");
    DECODE_ENTRY(17,      VSUBUHM_VX1, "|000100|.....|.....|.....|10001000000|");
    DECODE_ENTRY(17,      VSUBUHS_VX1, "|000100|.....|.....|.....|11001000000|");
    DECODE_ENTRY(17,      VSUBUWM_VX1, "|000100|.....|.....|.....|10010000000|");
    DECODE_ENTRY(17,      VSUBUWS_VX1, "|000100|.....|.....|.....|11010000000|");
    DECODE_ENTRY(17,     VSUM2SWS_VX1, "|000100|.....|.....|.....|11010001000|");
    DECODE_ENTRY(17,     VSUM4SBS_VX1, "|000100|.....|.....|.....|11100001000|");
    DECODE_ENTRY(17,     VSUM4SHS_VX1, "|000100|.....|.....|.....|11001001000|");
    DECODE_ENTRY(17,     VSUM4UBS_VX1, "|000100|.....|.....|.....|11000001000|");
    DECODE_ENTRY(17,      VSUMSWS_VX1, "|000100|.....|.....|.....|11110001000|");
    DECODE_ENTRY(17,         VXOR_VX1, "|000100|.....|.....|.....|10011000100|");

    //                            VX2   |  OPCD|  VRT|    X|  VRB|         XO|
    DECODE_ENTRY(17,     VEXPTEFP_VX2, "|000100|.....|.....|.....|00110001010|");
    DECODE_ENTRY(17,      VLOGEFP_VX2, "|000100|.....|.....|.....|00111001010|");
    DECODE_ENTRY(17,        VREFP_VX2, "|000100|.....|.....|.....|00100001010|");
    DECODE_ENTRY(17,        VRFIM_VX2, "|000100|.....|.....|.....|01011001010|");
    DECODE_ENTRY(17,        VRFIN_VX2, "|000100|.....|.....|.....|01000001010|");
    DECODE_ENTRY(17,        VRFIP_VX2, "|000100|.....|.....|.....|01010001010|");
    DECODE_ENTRY(17,        VRFIZ_VX2, "|000100|.....|.....|.....|01001001010|");
    DECODE_ENTRY(17,    VRSQRTEFP_VX2, "|000100|.....|.....|.....|00101001010|");
    DECODE_ENTRY(17,      VUPKHPX_VX2, "|000100|.....|.....|.....|01101001110|");
    DECODE_ENTRY(17,      VUPKHSB_VX2, "|000100|.....|.....|.....|01000001110|");
    DECODE_ENTRY(17,      VUPKHSH_VX2, "|000100|.....|.....|.....|01001001110|");
    DECODE_ENTRY(17,      VUPKLPX_VX2, "|000100|.....|.....|.....|01111001110|");
    DECODE_ENTRY(17,      VUPKLSB_VX2, "|000100|.....|.....|.....|01010001110|");
    DECODE_ENTRY(17,      VUPKLSH_VX2, "|000100|.....|.....|.....|01011001110|");

    //                            VX3   |  OPCD|  VRT|  UIM|  VRB|         XO|
    DECODE_ENTRY(17,        VCFSX_VX3, "|000100|.....|.....|.....|01101001010|");
    DECODE_ENTRY(17,        VCFUX_VX3, "|000100|.....|.....|.....|01100001010|");
    DECODE_ENTRY(17,       VCTSXS_VX3, "|000100|.....|.....|.....|01111001010|");
    DECODE_ENTRY(17,       VCTUXS_VX3, "|000100|.....|.....|.....|01110001010|");

    //                            VX4   |  OPCD|  VRT|X| UIM|  VRB|         XO|
    DECODE_ENTRY(17,       VSPLTB_VX4, "|000100|.....|.|....|.....|01000001100|");

    //                            VX5   |  OPCD|  VRT| X|UIM|  VRB|         XO|
    DECODE_ENTRY(17,       VSPLTH_VX5, "|000100|.....|..|...|.....|01001001100|");

    //                            VX6   |  OPCD|  VRT|  X|UI|  VRB|         XO|
    DECODE_ENTRY(17,       VSPLTW_VX6, "|000100|.....|...|..|.....|01010001100|");

    //                            VX7   |  OPCD|  VRT|  SIM|    X|         XO|
    DECODE_ENTRY(17,     VSPLTISB_VX7, "|000100|.....|.....|.....|01100001100|");
    DECODE_ENTRY(17,     VSPLTISH_VX7, "|000100|.....|.....|.....|01101001100|");
    DECODE_ENTRY(17,     VSPLTISW_VX7, "|000100|.....|.....|.....|01110001100|");

    //                            VX8   |  OPCD|  VRT|         X|         XO|
    DECODE_ENTRY(17,       MFVSCR_VX8, "|000100|.....|..........|11000000100|");

    //                            VX9   |  OPCD|         X|  VRB|         XO|
    DECODE_ENTRY(17,       MTVSCR_VX9, "|000100|..........|.....|11001000100|");

    //                            X58   |  OPCD|  VRT|   RA|   RB|        XO|X|
    DECODE_ENTRY(16,        LVEBX_X58, "|011111|.....|.....|.....|0000000111|.|");
    DECODE_ENTRY(16,        LVEHX_X58, "|011111|.....|.....|.....|0000100111|.|");
    DECODE_ENTRY(16,        LVEWX_X58, "|011111|.....|.....|.....|0001000111|.|");
    DECODE_ENTRY(16,         LVSL_X58, "|011111|.....|.....|.....|0000000110|.|");
    DECODE_ENTRY(16,         LVSR_X58, "|011111|.....|.....|.....|0000100110|.|");
    DECODE_ENTRY(16,          LVX_X58, "|011111|.....|.....|.....|0001100111|.|");
    DECODE_ENTRY(16,         LVXL_X58, "|011111|.....|.....|.....|0101100111|.|");

    //                            X59   |  OPCD|  VRS|   RA|   RB|        XO|X|
    DECODE_ENTRY(16,       STVEBX_X59, "|011111|.....|.....|.....|0010000111|.|");
    DECODE_ENTRY(16,       STVEHX_X59, "|011111|.....|.....|.....|0010100111|.|");
    DECODE_ENTRY(16,       STVEWX_X59, "|011111|.....|.....|.....|0011000111|.|");
    DECODE_ENTRY(16,         STVX_X59, "|011111|.....|.....|.....|0011100111|.|");
    DECODE_ENTRY(16,        STVXL_X59, "|011111|.....|.....|.....|0111100111|.|");

    return table;
}

// I_LMA Decoder
vmidDecodeTableP ppc32CreateDecodeTable_I_LMA_32Bit(vmidDecodeTableP current, Bool vle) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(32, PPC32_IT_LAST);
    }

    //                            DQ1   |  OPCD|  RTp|   RA|          DQ|   X|
    DECODE_ENTRY( 6,           LQ_DQ1, "|111000|.....|.....|............|....|");

    //                            DS3   |  OPCD|  RSp|   RA|            DS|XO|
    DECODE_ENTRY( 8,          STQ_DS3, "|111110|.....|.....|..............|10|");

    //                            X10   |  OPCD|   RT|   RA|   RB|        XO|R|
    DECODE_ENTRY(17,       MULCHW_X10, "|000100|.....|.....|.....|0010101000|0|");
    DECODE_ENTRY(17,     MULCHWRC_X10, "|000100|.....|.....|.....|0010101000|1|");
    DECODE_ENTRY(17,      MULCHWU_X10, "|000100|.....|.....|.....|0010001000|0|");
    DECODE_ENTRY(17,    MULCHWURC_X10, "|000100|.....|.....|.....|0010001000|1|");
    DECODE_ENTRY(17,       MULHHW_X10, "|000100|.....|.....|.....|0000101000|0|");
    DECODE_ENTRY(17,     MULHHWRC_X10, "|000100|.....|.....|.....|0000101000|1|");
    DECODE_ENTRY(17,      MULHHWU_X10, "|000100|.....|.....|.....|0000001000|0|");
    DECODE_ENTRY(17,    MULHHWURC_X10, "|000100|.....|.....|.....|0000001000|1|");
    DECODE_ENTRY(17,       MULLHW_X10, "|000100|.....|.....|.....|0110101000|0|");
    DECODE_ENTRY(17,     MULLHWRC_X10, "|000100|.....|.....|.....|0110101000|1|");
    DECODE_ENTRY(17,      MULLHWU_X10, "|000100|.....|.....|.....|0110001000|0|");
    DECODE_ENTRY(17,    MULLHWURC_X10, "|000100|.....|.....|.....|0110001000|1|");

    //                             X9   |  OPCD|   RS|   RA|   RB|        XO|R|
    DECODE_ENTRY(17,         DLMZB_X9, "|011111|.....|.....|.....|0001001110|0|");
    DECODE_ENTRY(17,       DLMZBRC_X9, "|011111|.....|.....|.....|0001001110|1|");

    //                            XO1   |  OPCD|   RT|   RA|   RB|O|       XO|R|
    DECODE_ENTRY(17,       MACCHW_XO1, "|000100|.....|.....|.....|0|010101100|0|");
    DECODE_ENTRY(17,     MACCHWOE_XO1, "|000100|.....|.....|.....|1|010101100|0|");
    DECODE_ENTRY(17,   MACCHWOERC_XO1, "|000100|.....|.....|.....|1|010101100|1|");
    DECODE_ENTRY(17,     MACCHWRC_XO1, "|000100|.....|.....|.....|0|010101100|1|");
    DECODE_ENTRY(17,      MACCHWS_XO1, "|000100|.....|.....|.....|0|011101100|0|");
    DECODE_ENTRY(17,    MACCHWSOE_XO1, "|000100|.....|.....|.....|1|011101100|0|");
    DECODE_ENTRY(17,  MACCHWSOERC_XO1, "|000100|.....|.....|.....|1|011101100|1|");
    DECODE_ENTRY(17,    MACCHWSRC_XO1, "|000100|.....|.....|.....|0|011101100|1|");
    DECODE_ENTRY(17,     MACCHWSU_XO1, "|000100|.....|.....|.....|0|011001100|0|");
    DECODE_ENTRY(17,   MACCHWSUOE_XO1, "|000100|.....|.....|.....|1|011001100|0|");
    DECODE_ENTRY(17, MACCHWSUOERC_XO1, "|000100|.....|.....|.....|1|011001100|1|");
    DECODE_ENTRY(17,   MACCHWSURC_XO1, "|000100|.....|.....|.....|0|011001100|1|");
    DECODE_ENTRY(17,      MACCHWU_XO1, "|000100|.....|.....|.....|0|010001100|0|");
    DECODE_ENTRY(17,    MACCHWUOE_XO1, "|000100|.....|.....|.....|1|010001100|0|");
    DECODE_ENTRY(17,  MACCHWUOERC_XO1, "|000100|.....|.....|.....|1|010001100|1|");
    DECODE_ENTRY(17,    MACCHWURC_XO1, "|000100|.....|.....|.....|0|010001100|1|");
    DECODE_ENTRY(17,       MACHHW_XO1, "|000100|.....|.....|.....|0|000101100|0|");
    DECODE_ENTRY(17,     MACHHWOE_XO1, "|000100|.....|.....|.....|1|000101100|0|");
    DECODE_ENTRY(17,   MACHHWOERC_XO1, "|000100|.....|.....|.....|1|000101100|1|");
    DECODE_ENTRY(17,     MACHHWRC_XO1, "|000100|.....|.....|.....|0|000101100|1|");
    DECODE_ENTRY(17,      MACHHWS_XO1, "|000100|.....|.....|.....|0|001101100|0|");
    DECODE_ENTRY(17,    MACHHWSOE_XO1, "|000100|.....|.....|.....|1|001101100|0|");
    DECODE_ENTRY(17,  MACHHWSOERC_XO1, "|000100|.....|.....|.....|1|001101100|1|");
    DECODE_ENTRY(17,    MACHHWSRC_XO1, "|000100|.....|.....|.....|0|001101100|1|");
    DECODE_ENTRY(17,     MACHHWSU_XO1, "|000100|.....|.....|.....|0|001001100|0|");
    DECODE_ENTRY(17,   MACHHWSUOE_XO1, "|000100|.....|.....|.....|1|001001100|0|");
    DECODE_ENTRY(17, MACHHWSUOERC_XO1, "|000100|.....|.....|.....|1|001001100|1|");
    DECODE_ENTRY(17,   MACHHWSURC_XO1, "|000100|.....|.....|.....|0|001001100|1|");
    DECODE_ENTRY(17,      MACHHWU_XO1, "|000100|.....|.....|.....|0|000001100|0|");
    DECODE_ENTRY(17,    MACHHWUOE_XO1, "|000100|.....|.....|.....|1|000001100|0|");
    DECODE_ENTRY(17,  MACHHWUOERC_XO1, "|000100|.....|.....|.....|1|000001100|1|");
    DECODE_ENTRY(17,    MACHHWURC_XO1, "|000100|.....|.....|.....|0|000001100|1|");
    DECODE_ENTRY(17,       MACLHW_XO1, "|000100|.....|.....|.....|0|110101100|0|");
    DECODE_ENTRY(17,     MACLHWOE_XO1, "|000100|.....|.....|.....|1|110101100|0|");
    DECODE_ENTRY(17,   MACLHWOERC_XO1, "|000100|.....|.....|.....|1|110101100|1|");
    DECODE_ENTRY(17,     MACLHWRC_XO1, "|000100|.....|.....|.....|0|110101100|1|");
    DECODE_ENTRY(17,      MACLHWS_XO1, "|000100|.....|.....|.....|0|111101100|0|");
    DECODE_ENTRY(17,    MACLHWSOE_XO1, "|000100|.....|.....|.....|1|111101100|0|");
    DECODE_ENTRY(17,  MACLHWSOERC_XO1, "|000100|.....|.....|.....|1|111101100|1|");
    DECODE_ENTRY(17,    MACLHWSRC_XO1, "|000100|.....|.....|.....|0|111101100|1|");
    DECODE_ENTRY(17,     MACLHWSU_XO1, "|000100|.....|.....|.....|0|111001100|0|");
    DECODE_ENTRY(17,   MACLHWSUOE_XO1, "|000100|.....|.....|.....|1|111001100|0|");
    DECODE_ENTRY(17, MACLHWSUOERC_XO1, "|000100|.....|.....|.....|1|111001100|1|");
    DECODE_ENTRY(17,   MACLHWSURC_XO1, "|000100|.....|.....|.....|0|111001100|1|");
    DECODE_ENTRY(17,      MACLHWU_XO1, "|000100|.....|.....|.....|0|110001100|0|");
    DECODE_ENTRY(17,    MACLHWUOE_XO1, "|000100|.....|.....|.....|1|110001100|0|");
    DECODE_ENTRY(17,  MACLHWUOERC_XO1, "|000100|.....|.....|.....|1|110001100|1|");
    DECODE_ENTRY(17,    MACLHWURC_XO1, "|000100|.....|.....|.....|0|110001100|1|");
    DECODE_ENTRY(17,      NMACCHW_XO1, "|000100|.....|.....|.....|0|010101110|0|");
    DECODE_ENTRY(17,    NMACCHWOE_XO1, "|000100|.....|.....|.....|1|010101110|0|");
    DECODE_ENTRY(17,  NMACCHWOERC_XO1, "|000100|.....|.....|.....|1|010101110|1|");
    DECODE_ENTRY(17,    NMACCHWRC_XO1, "|000100|.....|.....|.....|0|010101110|1|");
    DECODE_ENTRY(17,     NMACCHWS_XO1, "|000100|.....|.....|.....|0|011101110|0|");
    DECODE_ENTRY(17,   NMACCHWSOE_XO1, "|000100|.....|.....|.....|1|011101110|0|");
    DECODE_ENTRY(17, NMACCHWSOERC_XO1, "|000100|.....|.....|.....|1|011101110|1|");
    DECODE_ENTRY(17,   NMACCHWSRC_XO1, "|000100|.....|.....|.....|0|011101110|1|");
    DECODE_ENTRY(17,      NMACHHW_XO1, "|000100|.....|.....|.....|0|000101110|0|");
    DECODE_ENTRY(17,    NMACHHWOE_XO1, "|000100|.....|.....|.....|1|000101110|0|");
    DECODE_ENTRY(17,  NMACHHWOERC_XO1, "|000100|.....|.....|.....|1|000101110|1|");
    DECODE_ENTRY(17,    NMACHHWRC_XO1, "|000100|.....|.....|.....|0|000101110|1|");
    DECODE_ENTRY(17,     NMACHHWS_XO1, "|000100|.....|.....|.....|0|001101110|0|");
    DECODE_ENTRY(17,   NMACHHWSOE_XO1, "|000100|.....|.....|.....|1|001101110|0|");
    DECODE_ENTRY(17, NMACHHWSOERC_XO1, "|000100|.....|.....|.....|1|001101110|1|");
    DECODE_ENTRY(17,   NMACHHWSRC_XO1, "|000100|.....|.....|.....|0|001101110|1|");
    DECODE_ENTRY(17,      NMACLHW_XO1, "|000100|.....|.....|.....|0|110101110|0|");
    DECODE_ENTRY(17,    NMACLHWOE_XO1, "|000100|.....|.....|.....|1|110101110|0|");
    DECODE_ENTRY(17,  NMACLHWOERC_XO1, "|000100|.....|.....|.....|1|110101110|1|");
    DECODE_ENTRY(17,    NMACLHWRC_XO1, "|000100|.....|.....|.....|0|110101110|1|");
    DECODE_ENTRY(17,     NMACLHWS_XO1, "|000100|.....|.....|.....|0|111101110|0|");
    DECODE_ENTRY(17,   NMACLHWSOE_XO1, "|000100|.....|.....|.....|1|111101110|0|");
    DECODE_ENTRY(17, NMACLHWSOERC_XO1, "|000100|.....|.....|.....|1|111101110|1|");
    DECODE_ENTRY(17,   NMACLHWSRC_XO1, "|000100|.....|.....|.....|0|111101110|1|");

    return table;
}

// I_WT Decoder
vmidDecodeTableP ppc32CreateDecodeTable_I_WT_32Bit(vmidDecodeTableP current, Bool vle) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(32, PPC32_IT_LAST);
    }

    //                          X53_1   |  OPCD|              X|        XO|X|
    DECODE_ENTRY(16,       WAIT_X53_1, "|011111|...............|0000111110|.|");

    return table;
}

// I_VLE Decoder
vmidDecodeTableP ppc32CreateDecodeTable_I_VLE_16Bit(vmidDecodeTableP current, Bool vle) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(16, PPC32_IT_LAST);
    }

    //                           BD81   | OPCD|B|BI|     BD8|
    DECODE_ENTRY( 5,       SE_BC_BD81, "|11100|.|..|........|");

    //                           BD82   |  OPCD|X|L|     BD8|
    DECODE_ENTRY( 7,        SE_B_BD82, "|111010|0|.|........|");

    //                            C_0   |            OPCD|
    DECODE_ENTRY(16,   SE_ILLEGAL_C_0, "|0000000000000000|");
    DECODE_ENTRY(16,     SE_ISYNC_C_0, "|0000000000000001|");
    DECODE_ENTRY(16,      SE_RFCI_C_0, "|0000000000001001|");
    DECODE_ENTRY(16,      SE_RFDI_C_0, "|0000000000001010|");
    DECODE_ENTRY(16,       SE_RFI_C_0, "|0000000000001000|");
    DECODE_ENTRY(16,     SE_RFMCI_C_0, "|0000000000001011|");
    DECODE_ENTRY(16,        SE_SC_C_0, "|0000000000000010|");

    //                            C_1   |           OPCD|L|
    DECODE_ENTRY(15,      SE_BCTR_C_1, "|000000000000011|.|");
    DECODE_ENTRY(15,       SE_BLR_C_1, "|000000000000010|.|");

    //                            IM5   |  OPCD|X|  UI5|R|  RX|
    DECODE_ENTRY( 7,      SE_ANDI_IM5, "|001011|1|.....|.|...|");
    DECODE_ENTRY( 7,    SE_BMASKI_IM5, "|001011|0|.....|.|...|");
    DECODE_ENTRY( 7,      SE_CMPI_IM5, "|001010|1|.....|.|...|");

    //                            IM7   | OPCD|    UI7|R|  RX|
    DECODE_ENTRY( 5,        SE_LI_IM7, "|01001|.......|.|...|");

    //                        OIM51_0   |  OPCD|X| OIM5|R|  RX|
    DECODE_ENTRY( 7, SE_BCLRI_OIM51_0, "|011000|0|.....|.|...|");
    DECODE_ENTRY( 7, SE_BGENI_OIM51_0, "|011000|1|.....|.|...|");
    DECODE_ENTRY( 7, SE_BSETI_OIM51_0, "|011001|0|.....|.|...|");
    DECODE_ENTRY( 7, SE_BTSTI_OIM51_0, "|011001|1|.....|.|...|");
    DECODE_ENTRY( 7,  SE_SLWI_OIM51_0, "|011011|0|.....|.|...|");
    DECODE_ENTRY( 7, SE_SRAWI_OIM51_0, "|011010|1|.....|.|...|");
    DECODE_ENTRY( 7,  SE_SRWI_OIM51_0, "|011010|0|.....|.|...|");

    //                        OIM51_1   |  OPCD|X| OIM5|R|  RX|
    DECODE_ENTRY( 7,  SE_ADDI_OIM51_1, "|001000|0|.....|.|...|");
    DECODE_ENTRY( 7, SE_CMPLI_OIM51_1, "|001000|1|.....|.|...|");

    //                        OIM52_0   |  OPCD|R| OIM5|R|  RX|
    DECODE_ENTRY( 7,  SE_SUBI_OIM52_0, "|001001|0|.....|.|...|");
    DECODE_ENTRY( 7, SE_SUBIRC_OIM52_0, "|001001|1|.....|.|...|");

    //                             R1   |  OPCD|    XO|R|  RX|
    DECODE_ENTRY(12,      SE_EXTSB_R1, "|000000|001101|.|...|");
    DECODE_ENTRY(12,      SE_EXTSH_R1, "|000000|001111|.|...|");
    DECODE_ENTRY(12,      SE_EXTZB_R1, "|000000|001100|.|...|");
    DECODE_ENTRY(12,      SE_EXTZH_R1, "|000000|001110|.|...|");
    DECODE_ENTRY(12,      SE_MFCTR_R1, "|000000|001010|.|...|");
    DECODE_ENTRY(12,       SE_MFLR_R1, "|000000|001000|.|...|");
    DECODE_ENTRY(12,      SE_MTCTR_R1, "|000000|001011|.|...|");
    DECODE_ENTRY(12,       SE_MTLR_R1, "|000000|001001|.|...|");
    DECODE_ENTRY(12,        SE_NEG_R1, "|000000|000011|.|...|");
    DECODE_ENTRY(12,        SE_NOT_R1, "|000000|000010|.|...|");

    //                            RR1   |  OPCD|XO|R|  RY|R|  RX|
    DECODE_ENTRY( 8,       SE_ADD_RR1, "|000001|00|.|...|.|...|");
    DECODE_ENTRY( 8,      SE_ANDC_RR1, "|010001|01|.|...|.|...|");
    DECODE_ENTRY( 8,       SE_CMP_RR1, "|000011|00|.|...|.|...|");
    DECODE_ENTRY( 8,      SE_CMPH_RR1, "|000011|10|.|...|.|...|");
    DECODE_ENTRY( 8,     SE_CMPHL_RR1, "|000011|11|.|...|.|...|");
    DECODE_ENTRY( 8,      SE_CMPL_RR1, "|000011|01|.|...|.|...|");
    DECODE_ENTRY( 8,        SE_MR_RR1, "|000000|01|.|...|.|...|");
    DECODE_ENTRY( 8,     SE_MULLW_RR1, "|000001|01|.|...|.|...|");
    DECODE_ENTRY( 8,        SE_OR_RR1, "|010001|00|.|...|.|...|");
    DECODE_ENTRY( 8,       SE_SLW_RR1, "|010000|10|.|...|.|...|");
    DECODE_ENTRY( 8,      SE_SRAW_RR1, "|010000|01|.|...|.|...|");
    DECODE_ENTRY( 8,       SE_SRW_RR1, "|010000|00|.|...|.|...|");
    DECODE_ENTRY( 8,       SE_SUB_RR1, "|000001|10|.|...|.|...|");
    DECODE_ENTRY( 8,      SE_SUBF_RR1, "|000001|11|.|...|.|...|");

    //                            RR2   |  OPCD|X|R|R|  RY|R|  RX|
    DECODE_ENTRY( 8,       SE_AND_RR2, "|010001|1|0|.|...|.|...|");
    DECODE_ENTRY( 8,     SE_ANDRC_RR2, "|010001|1|1|.|...|.|...|");

    //                            RR3   |  OPCD|XO| ARY|R|  RX|
    DECODE_ENTRY( 8,      SE_MFAR_RR3, "|000000|11|....|.|...|");

    //                            RR4   |  OPCD|XO|R|  RY| ARX|
    DECODE_ENTRY( 8,      SE_MTAR_RR4, "|000000|10|.|...|....|");

    //                          SD4_0   |OPCD| SD4|R|  RZ|R|  RX|
    DECODE_ENTRY( 4,     SE_LBZ_SD4_0, "|1000|....|.|...|.|...|");
    DECODE_ENTRY( 4,     SE_STB_SD4_0, "|1001|....|.|...|.|...|");

    //                          SD4_1   |OPCD| SD4|R|  RZ|R|  RX|
    DECODE_ENTRY( 4,     SE_LHZ_SD4_1, "|1010|....|.|...|.|...|");
    DECODE_ENTRY( 4,     SE_STH_SD4_1, "|1011|....|.|...|.|...|");

    //                          SD4_2   |OPCD| SD4|R|  RZ|R|  RX|
    DECODE_ENTRY( 4,     SE_LWZ_SD4_2, "|1100|....|.|...|.|...|");
    DECODE_ENTRY( 4,     SE_STW_SD4_2, "|1101|....|.|...|.|...|");

    //
    // I_VLE Drop through section to next table
    //
    DECODE_ENTRY(16,          INSTR32, "000110..........");
    DECODE_ENTRY(16,          INSTR32, "000111..........");
    DECODE_ENTRY(16,          INSTR32, "001100..........");
    DECODE_ENTRY(16,          INSTR32, "001101..........");
    DECODE_ENTRY(16,          INSTR32, "001110..........");
    DECODE_ENTRY(16,          INSTR32, "010100..........");
    DECODE_ENTRY(16,          INSTR32, "010101..........");
    DECODE_ENTRY(16,          INSTR32, "010110..........");
    DECODE_ENTRY(16,          INSTR32, "010111..........");
    DECODE_ENTRY(16,          INSTR32, "011100..........");
    DECODE_ENTRY(16,          INSTR32, "011101..........");
    DECODE_ENTRY(16,          INSTR32, "0111100.........");
    DECODE_ENTRY(16,          INSTR32, "0111101000......");
    DECODE_ENTRY(16,          INSTR32, "011111..........");

    //
    // SP / V Prefix
    //
    DECODE_ENTRY(16,          INSTR32, "000100..........");

    return table;
}

// I_VLE Decoder
vmidDecodeTableP ppc32CreateDecodeTable_I_VLE_32Bit(vmidDecodeTableP current, Bool vle) {
    vmidDecodeTableP table = current;
    if (!table) {
        table = vmidNewDecodeTable(32, PPC32_IT_LAST);
    }

    //                           BD15   |  OPCD|  XO|BO|BI32|             BD|L|
    DECODE_ENTRY(10,        E_BC_BD15, "|011110|1000|..|....|...............|.|");

    //                           BD24   |  OPCD|Z|                    BD24|L|
    DECODE_ENTRY( 7,         E_B_BD24, "|011110|0|........................|.|");

    //                             D1   |  OPCD|   RT|   RA|               D|
    DECODE_ENTRY( 6,         E_LBZ_D1, "|001100|.....|.....|................|");
    DECODE_ENTRY( 6,         E_LHA_D1, "|001110|.....|.....|................|");
    DECODE_ENTRY( 6,         E_LHZ_D1, "|010110|.....|.....|................|");
    DECODE_ENTRY( 6,         E_LWZ_D1, "|010100|.....|.....|................|");

    //                             D2   |  OPCD|   RT|   RA|              SI|
    DECODE_ENTRY( 6,      E_ADD16I_D2, "|000111|.....|.....|................|");

    //                             D3   |  OPCD|   RS|   RA|               D|
    DECODE_ENTRY( 6,         E_STB_D3, "|001101|.....|.....|................|");
    DECODE_ENTRY( 6,         E_STH_D3, "|010111|.....|.....|................|");
    DECODE_ENTRY( 6,         E_STW_D3, "|010101|.....|.....|................|");

    //                           D8_0   |  OPCD|   RT|   RA|      XO|      D8|
    DECODE_ENTRY(14,      E_LBZU_D8_0, "|000110|.....|.....|00000000|........|");
    DECODE_ENTRY(14,      E_LHAU_D8_0, "|000110|.....|.....|00000011|........|");
    DECODE_ENTRY(14,      E_LHZU_D8_0, "|000110|.....|.....|00000001|........|");
    DECODE_ENTRY(14,       E_LMW_D8_0, "|000110|.....|.....|00001000|........|");
    DECODE_ENTRY(14,      E_LWZU_D8_0, "|000110|.....|.....|00000010|........|");

    //                           D8_1   |  OPCD|   RS|   RA|      XO|      D8|
    DECODE_ENTRY(14,      E_STBU_D8_1, "|000110|.....|.....|00000100|........|");
    DECODE_ENTRY(14,      E_STHU_D8_1, "|000110|.....|.....|00000101|........|");
    DECODE_ENTRY(14,      E_STMW_D8_1, "|000110|.....|.....|00001001|........|");
    DECODE_ENTRY(14,      E_STWU_D8_1, "|000110|.....|.....|00000110|........|");

    //                          I16A1   |  OPCD|   SI|   RA|   XO|         SI|
    DECODE_ENTRY(11,  E_ADD2IRC_I16A1, "|011100|.....|.....|10001|...........|");
    DECODE_ENTRY(11,   E_ADD2IS_I16A1, "|011100|.....|.....|10010|...........|");
    DECODE_ENTRY(11,   E_CMP16I_I16A1, "|011100|.....|.....|10011|...........|");
    DECODE_ENTRY(11,  E_CMPH16I_I16A1, "|011100|.....|.....|10110|...........|");
    DECODE_ENTRY(11,   E_MULL2I_I16A1, "|011100|.....|.....|10100|...........|");

    //                          I16A2   |  OPCD|   UI|   RA|   XO|         UI|
    DECODE_ENTRY(11, E_CMPHL16I_I16A2, "|011100|.....|.....|10111|...........|");
    DECODE_ENTRY(11,  E_CMPL16I_I16A2, "|011100|.....|.....|10101|...........|");

    //                           I16L   |  OPCD|   RT|   UI|   XO|         UI|
    DECODE_ENTRY(11,   E_AND2IRC_I16L, "|011100|.....|.....|11001|...........|");
    DECODE_ENTRY(11,  E_AND2ISRC_I16L, "|011100|.....|.....|11101|...........|");
    DECODE_ENTRY(11,       E_LIS_I16L, "|011100|.....|.....|11100|...........|");
    DECODE_ENTRY(11,      E_OR2I_I16L, "|011100|.....|.....|11000|...........|");
    DECODE_ENTRY(11,     E_OR2IS_I16L, "|011100|.....|.....|11010|...........|");

    //                           LI20   |  OPCD|   RT| li20|X|li20|       li20|
    DECODE_ENTRY( 6,        E_LI_LI20, "|011100|.....|.....|.|....|...........|");

    //                           M2_0   |  OPCD|   RS|   RA|   SH|   MB|   ME|R|
    DECODE_ENTRY( 7,    E_RLWIMI_M2_0, "|011101|.....|.....|.....|.....|.....|0|");
    DECODE_ENTRY( 7,    E_RLWINM_M2_0, "|011101|.....|.....|.....|.....|.....|1|");

    //                         SCI8_1   |  OPCD|   RT|   RA|  XO|R|F|SC|      U8|
    DECODE_ENTRY(11,    E_ADDI_SCI8_1, "|000110|.....|.....|1000|0|.|..|........|");
    DECODE_ENTRY(11,   E_ADDIC_SCI8_1, "|000110|.....|.....|1001|0|.|..|........|");
    DECODE_ENTRY(11, E_ADDICRC_SCI8_1, "|000110|.....|.....|1001|1|.|..|........|");
    DECODE_ENTRY(11,  E_ADDIRC_SCI8_1, "|000110|.....|.....|1000|1|.|..|........|");
    DECODE_ENTRY(11,  E_SUBFIC_SCI8_1, "|000110|.....|.....|1011|0|.|..|........|");
    DECODE_ENTRY(11, E_SUBFICRC_SCI8_1, "|000110|.....|.....|1011|1|.|..|........|");

    //                         SCI8_2   |  OPCD|   RT|   RA|   XO|F|SC|      U8|
    DECODE_ENTRY(11,   E_MULLI_SCI8_2, "|000110|.....|.....|10100|.|..|........|");

    //                         SCI8_3   |  OPCD|   RS|   RA|  XO|R|F|SC|      U8|
    DECODE_ENTRY(11,    E_ANDI_SCI8_3, "|000110|.....|.....|1100|0|.|..|........|");
    DECODE_ENTRY(11,  E_ANDIRC_SCI8_3, "|000110|.....|.....|1100|1|.|..|........|");
    DECODE_ENTRY(11,     E_ORI_SCI8_3, "|000110|.....|.....|1101|0|.|..|........|");
    DECODE_ENTRY(11,   E_ORIRC_SCI8_3, "|000110|.....|.....|1101|1|.|..|........|");
    DECODE_ENTRY(11,    E_XORI_SCI8_3, "|000110|.....|.....|1110|0|.|..|........|");
    DECODE_ENTRY(11,  E_XORIRC_SCI8_3, "|000110|.....|.....|1110|1|.|..|........|");

    //                         SCI8_5   |  OPCD| ZR|BF|   RA|   XO|F|SC|      S8|
    DECODE_ENTRY(14,    E_CMPI_SCI8_5, "|000110|000|..|.....|10101|.|..|........|");

    //                         SCI8_6   |  OPCD| NZ|BF|   RA|   XO|F|SC|      S8|
    DECODE_ENTRY(14,   E_CMPLI_SCI8_6, "|000110|001|..|.....|10101|.|..|........|");

    //                            X14   |  OPCD|   RS|   RA|   SH|        XO|R|
    DECODE_ENTRY(17,       E_RLWI_X14, "|011111|.....|.....|.....|0100111000|0|");
    DECODE_ENTRY(17,     E_RLWIRC_X14, "|011111|.....|.....|.....|0100111000|1|");
    DECODE_ENTRY(17,       E_SLWI_X14, "|011111|.....|.....|.....|0000111000|0|");
    DECODE_ENTRY(17,     E_SLWIRC_X14, "|011111|.....|.....|.....|0000111000|1|");
    DECODE_ENTRY(17,       E_SRWI_X14, "|011111|.....|.....|.....|1000111000|0|");
    DECODE_ENTRY(17,     E_SRWIRC_X14, "|011111|.....|.....|.....|1000111000|1|");

    //                          X22_2   |  OPCD| BF| X|   RA|   RB|        XO|X|
    DECODE_ENTRY(16,     E_CMPH_X22_2, "|011111|...|..|.....|.....|0000001110|.|");
    DECODE_ENTRY(16,    E_CMPHL_X22_2, "|011111|...|..|.....|.....|0000101110|.|");

    //                             X9   |  OPCD|   RS|   RA|   RB|        XO|R|
    DECODE_ENTRY(17,         E_RLW_X9, "|011111|.....|.....|.....|0100011000|0|");
    DECODE_ENTRY(17,       E_RLWRC_X9, "|011111|.....|.....|.....|0100011000|1|");

    //                            XL1   |  OPCD|   BT|   BA|   BB|        XO|X|
    DECODE_ENTRY(16,      E_CRAND_XL1, "|011111|.....|.....|.....|0100000001|.|");
    DECODE_ENTRY(16,     E_CRANDC_XL1, "|011111|.....|.....|.....|0010000001|.|");
    DECODE_ENTRY(16,      E_CREQV_XL1, "|011111|.....|.....|.....|0100100001|.|");
    DECODE_ENTRY(16,     E_CRNAND_XL1, "|011111|.....|.....|.....|0011100001|.|");
    DECODE_ENTRY(16,      E_CRNOR_XL1, "|011111|.....|.....|.....|0000100001|.|");
    DECODE_ENTRY(16,       E_CROR_XL1, "|011111|.....|.....|.....|0111000001|.|");
    DECODE_ENTRY(16,      E_CRORC_XL1, "|011111|.....|.....|.....|0110100001|.|");
    DECODE_ENTRY(16,      E_CRXOR_XL1, "|011111|.....|.....|.....|0011000001|.|");

    //                            XL3   |  OPCD| BF| X|BFA|      X|        XO|X|
    DECODE_ENTRY(16,       E_MCRF_XL3, "|011111|...|..|...|.......|0000010000|.|");

    return table;
}


//
// Initialization of the info structure per instruction
//
void ppc32GenInstructionInfo (ppc32InstructionInfoP info) {
    info->opcode = opcode[info->type];
    switch (info->type) {
        case PPC32_IT_FMADD_A1:
        case PPC32_IT_FMADDRC_A1:
        case PPC32_IT_FMADDS_A1:
        case PPC32_IT_FMADDSRC_A1:
        case PPC32_IT_FMSUB_A1:
        case PPC32_IT_FMSUBRC_A1:
        case PPC32_IT_FMSUBS_A1:
        case PPC32_IT_FMSUBSRC_A1:
        case PPC32_IT_FNMADD_A1:
        case PPC32_IT_FNMADDRC_A1:
        case PPC32_IT_FNMADDS_A1:
        case PPC32_IT_FNMADDSRC_A1:
        case PPC32_IT_FNMSUB_A1:
        case PPC32_IT_FNMSUBRC_A1:
        case PPC32_IT_FNMSUBS_A1:
        case PPC32_IT_FNMSUBSRC_A1:
        case PPC32_IT_FSEL_A1:
        case PPC32_IT_FSELRC_A1:
            info->FRA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->FRB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->FRC = VECINDEX(info->instruction,10,6,0); // 10:6
            info->FRT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_FADD_A2:
        case PPC32_IT_FADDRC_A2:
        case PPC32_IT_FADDS_A2:
        case PPC32_IT_FADDSRC_A2:
        case PPC32_IT_FDIV_A2:
        case PPC32_IT_FDIVRC_A2:
        case PPC32_IT_FDIVS_A2:
        case PPC32_IT_FDIVSRC_A2:
        case PPC32_IT_FSUB_A2:
        case PPC32_IT_FSUBRC_A2:
        case PPC32_IT_FSUBS_A2:
        case PPC32_IT_FSUBSRC_A2:
            info->FRA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->FRB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->FRT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_FMUL_A3:
        case PPC32_IT_FMULRC_A3:
        case PPC32_IT_FMULS_A3:
        case PPC32_IT_FMULSRC_A3:
            info->FRA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->FRC = VECINDEX(info->instruction,10,6,0); // 10:6
            info->FRT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_FSQRT_A4:
        case PPC32_IT_FSQRTRC_A4:
        case PPC32_IT_FSQRTS_A4:
        case PPC32_IT_FSQRTSRC_A4:
            info->FRB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->FRT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_FRE_A5:
        case PPC32_IT_FRERC_A5:
        case PPC32_IT_FRES_A5:
        case PPC32_IT_FRESRC_A5:
        case PPC32_IT_FRSQRTE_A5:
        case PPC32_IT_FRSQRTERC_A5:
        case PPC32_IT_FRSQRTES_A5:
        case PPC32_IT_FRSQRTESRC_A5:
            info->FRB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->FRT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_ISEL_A6:
            info->BC = VECINDEX(info->instruction,10,6,0); // 10:6
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_BC_B1:
            info->AA = VECINDEX(info->instruction,1,1,0); // 1
            info->BD = VECINDEX(info->instruction,15,2,0); // 15:2
            info->BD = SHIFTL(info->BD,2);
            info->BD = SEXTEND(info->BD,15);
            info->BI = VECINDEX(info->instruction,20,16,0); // 20:16
            info->BO = VECINDEX(info->instruction,25,21,0); // 25:21
            info->LK = VECINDEX(info->instruction,0,0,0); // 0
            break;

        case PPC32_IT_E_BC_BD15:
            info->BD = VECINDEX(info->instruction,15,1,0); // 15:1
            info->BD = SHIFTL(info->BD,1);
            info->BD = SEXTEND(info->BD,15);
            info->BI32 = VECINDEX(info->instruction,19,16,0); // 19:16
            info->BO32 = VECINDEX(info->instruction,21,20,0); // 21:20
            info->LK = VECINDEX(info->instruction,0,0,0); // 0
            break;

        case PPC32_IT_E_B_BD24:
            info->BD24 = VECINDEX(info->instruction,24,1,0); // 24:1
            info->BD24 = SHIFTL(info->BD24,1);
            info->BD24 = SEXTEND(info->BD24,24);
            info->LK = VECINDEX(info->instruction,0,0,0); // 0
            break;

        case PPC32_IT_SE_BC_BD81:
            info->BD8 = VECINDEX(info->instruction,7,0,0); // 7:0
            info->BD8 = SHIFTL(info->BD8,1);
            info->BD8 = SEXTEND(info->BD8,8);
            info->BI16 = VECINDEX(info->instruction,9,8,0); // 9:8
            info->BO16 = VECINDEX(info->instruction,10,10,0); // 10
            break;

        case PPC32_IT_SE_B_BD82:
            info->BD8 = VECINDEX(info->instruction,7,0,0); // 7:0
            info->BD8 = SHIFTL(info->BD8,1);
            info->BD8 = SEXTEND(info->BD8,8);
            info->LK = VECINDEX(info->instruction,8,8,0); // 8
            break;

        case PPC32_IT_SE_ILLEGAL_C_0:
        case PPC32_IT_SE_ISYNC_C_0:
        case PPC32_IT_SE_RFCI_C_0:
        case PPC32_IT_SE_RFDI_C_0:
        case PPC32_IT_SE_RFI_C_0:
        case PPC32_IT_SE_RFMCI_C_0:
        case PPC32_IT_SE_SC_C_0:
            break;

        case PPC32_IT_SE_BCTR_C_1:
        case PPC32_IT_SE_BLR_C_1:
            info->LK = VECINDEX(info->instruction,0,0,0); // 0
            break;

        case PPC32_IT_E_LBZ_D1:
        case PPC32_IT_E_LHA_D1:
        case PPC32_IT_E_LHZ_D1:
        case PPC32_IT_E_LWZ_D1:
        case PPC32_IT_LBZ_D1:
        case PPC32_IT_LBZU_D1:
        case PPC32_IT_LHA_D1:
        case PPC32_IT_LHAU_D1:
        case PPC32_IT_LHZ_D1:
        case PPC32_IT_LHZU_D1:
        case PPC32_IT_LMW_D1:
        case PPC32_IT_LWZ_D1:
        case PPC32_IT_LWZU_D1:
            info->D = VECINDEX(info->instruction,15,0,0); // 15:0
            info->D = SEXTEND(info->D,15);
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_E_ADD16I_D2:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            info->SI = VECINDEX(info->instruction,15,0,0); // 15:0
            info->SI = SEXTEND(info->SI,15);
            break;

        case PPC32_IT_ADDI_D2_0:
        case PPC32_IT_ADDIC_D2_0:
        case PPC32_IT_ADDICRC_D2_0:
        case PPC32_IT_ADDIS_D2_0:
        case PPC32_IT_MULLI_D2_0:
        case PPC32_IT_SUBFIC_D2_0:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            info->SI = VECINDEX(info->instruction,15,0,0); // 15:0
            info->SI = SEXTEND(info->SI,15);
            break;

        case PPC32_IT_LI_D2_1:
        case PPC32_IT_LIS_D2_1:
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            info->SI = VECINDEX(info->instruction,15,0,0); // 15:0
            info->SI = SEXTEND(info->SI,15);
            break;

        case PPC32_IT_E_STB_D3:
        case PPC32_IT_E_STH_D3:
        case PPC32_IT_E_STW_D3:
        case PPC32_IT_STB_D3:
        case PPC32_IT_STBU_D3:
        case PPC32_IT_STH_D3:
        case PPC32_IT_STHU_D3:
        case PPC32_IT_STMW_D3:
        case PPC32_IT_STW_D3:
        case PPC32_IT_STWU_D3:
            info->D = VECINDEX(info->instruction,15,0,0); // 15:0
            info->D = SEXTEND(info->D,15);
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_ANDIRC_D4:
        case PPC32_IT_ANDISRC_D4:
        case PPC32_IT_ORI_D4:
        case PPC32_IT_ORIS_D4:
        case PPC32_IT_XORI_D4:
        case PPC32_IT_XORIS_D4:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            info->UI = VECINDEX(info->instruction,15,0,0); // 15:0
            break;

        case PPC32_IT_CMPWI_D5_0:
            info->BF = VECINDEX(info->instruction,25,23,0); // 25:23
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->SI = VECINDEX(info->instruction,15,0,0); // 15:0
            info->SI = SEXTEND(info->SI,15);
            break;

        case PPC32_IT_CMPI_D5_1:
            info->BF = VECINDEX(info->instruction,25,23,0); // 25:23
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->SI = VECINDEX(info->instruction,15,0,0); // 15:0
            info->SI = SEXTEND(info->SI,15);
            break;

        case PPC32_IT_CMPLWI_D6_0:
            info->BF = VECINDEX(info->instruction,25,23,0); // 25:23
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->UI = VECINDEX(info->instruction,15,0,0); // 15:0
            break;

        case PPC32_IT_CMPLI_D6_1:
            info->BF = VECINDEX(info->instruction,25,23,0); // 25:23
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->UI = VECINDEX(info->instruction,15,0,0); // 15:0
            break;

        case PPC32_IT_TWI_D7:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->SI = VECINDEX(info->instruction,15,0,0); // 15:0
            info->SI = SEXTEND(info->SI,15);
            info->TO = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_LFD_D8:
        case PPC32_IT_LFDU_D8:
        case PPC32_IT_LFS_D8:
        case PPC32_IT_LFSU_D8:
            info->D = VECINDEX(info->instruction,15,0,0); // 15:0
            info->D = SEXTEND(info->D,15);
            info->FRT = VECINDEX(info->instruction,25,21,0); // 25:21
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            break;

        case PPC32_IT_E_LBZU_D8_0:
        case PPC32_IT_E_LHAU_D8_0:
        case PPC32_IT_E_LHZU_D8_0:
        case PPC32_IT_E_LMW_D8_0:
        case PPC32_IT_E_LWZU_D8_0:
            info->D8 = VECINDEX(info->instruction,7,0,0); // 7:0
            info->D8 = SEXTEND(info->D8,7);
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_E_STBU_D8_1:
        case PPC32_IT_E_STHU_D8_1:
        case PPC32_IT_E_STMW_D8_1:
        case PPC32_IT_E_STWU_D8_1:
            info->D8 = VECINDEX(info->instruction,7,0,0); // 7:0
            info->D8 = SEXTEND(info->D8,7);
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_STFD_D9:
        case PPC32_IT_STFDU_D9:
        case PPC32_IT_STFS_D9:
        case PPC32_IT_STFSU_D9:
            info->D = VECINDEX(info->instruction,15,0,0); // 15:0
            info->D = SEXTEND(info->D,15);
            info->FRS = VECINDEX(info->instruction,25,21,0); // 25:21
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            break;

        case PPC32_IT_LQ_DQ1:
            info->DQ = VECINDEX(info->instruction,15,4,0); // 15:4
            info->DQ = SHIFTL(info->DQ,4);
            info->DQ = SEXTEND(info->DQ,15);
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RTp = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_STQ_DS3:
            info->DS = VECINDEX(info->instruction,15,2,0); // 15:2
            info->DS = SHIFTL(info->DS,2);
            info->DS = SEXTEND(info->DS,15);
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RSp = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_EVSEL_EVS:
            info->BFA = VECINDEX(info->instruction,2,0,0); // 2:0
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_BRINC_EVX1:
        case PPC32_IT_EVSTDDX_EVX1:
        case PPC32_IT_EVSTDHX_EVX1:
        case PPC32_IT_EVSTDWX_EVX1:
        case PPC32_IT_EVSTWHEX_EVX1:
        case PPC32_IT_EVSTWHOX_EVX1:
        case PPC32_IT_EVSTWWEX_EVX1:
        case PPC32_IT_EVSTWWOX_EVX1:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_EVSTWHE_EVX2_2:
        case PPC32_IT_EVSTWHO_EVX2_2:
        case PPC32_IT_EVSTWWE_EVX2_2:
        case PPC32_IT_EVSTWWO_EVX2_2:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            info->UI = VECINDEX(info->instruction,15,11,0); // 15:11
            info->UI = SHIFTL(info->UI,2);
            break;

        case PPC32_IT_EVSTDD_EVX2_3:
        case PPC32_IT_EVSTDH_EVX2_3:
        case PPC32_IT_EVSTDW_EVX2_3:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            info->UI = VECINDEX(info->instruction,15,11,0); // 15:11
            info->UI = SHIFTL(info->UI,3);
            break;

        case PPC32_IT_EFDCFS_EVX3:
        case PPC32_IT_EFDCFSF_EVX3:
        case PPC32_IT_EFDCFSI_EVX3:
        case PPC32_IT_EFDCFSID_EVX3:
        case PPC32_IT_EFDCFUF_EVX3:
        case PPC32_IT_EFDCFUI_EVX3:
        case PPC32_IT_EFDCFUID_EVX3:
        case PPC32_IT_EFDCTSF_EVX3:
        case PPC32_IT_EFDCTSI_EVX3:
        case PPC32_IT_EFDCTSIDZ_EVX3:
        case PPC32_IT_EFDCTSIZ_EVX3:
        case PPC32_IT_EFDCTUF_EVX3:
        case PPC32_IT_EFDCTUI_EVX3:
        case PPC32_IT_EFDCTUIDZ_EVX3:
        case PPC32_IT_EFDCTUIZ_EVX3:
        case PPC32_IT_EFSCFD_EVX3:
        case PPC32_IT_EFSCFSF_EVX3:
        case PPC32_IT_EFSCFSI_EVX3:
        case PPC32_IT_EFSCFUF_EVX3:
        case PPC32_IT_EFSCFUI_EVX3:
        case PPC32_IT_EFSCTSF_EVX3:
        case PPC32_IT_EFSCTSI_EVX3:
        case PPC32_IT_EFSCTSIZ_EVX3:
        case PPC32_IT_EFSCTUF_EVX3:
        case PPC32_IT_EFSCTUI_EVX3:
        case PPC32_IT_EFSCTUIZ_EVX3:
        case PPC32_IT_EVFSCFSF_EVX3:
        case PPC32_IT_EVFSCFSI_EVX3:
        case PPC32_IT_EVFSCFUF_EVX3:
        case PPC32_IT_EVFSCFUI_EVX3:
        case PPC32_IT_EVFSCTSF_EVX3:
        case PPC32_IT_EVFSCTSI_EVX3:
        case PPC32_IT_EVFSCTSIZ_EVX3:
        case PPC32_IT_EVFSCTUF_EVX3:
        case PPC32_IT_EVFSCTUI_EVX3:
        case PPC32_IT_EVFSCTUIZ_EVX3:
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_EFDADD_EVX4:
        case PPC32_IT_EFDDIV_EVX4:
        case PPC32_IT_EFDMUL_EVX4:
        case PPC32_IT_EFDSUB_EVX4:
        case PPC32_IT_EFSADD_EVX4:
        case PPC32_IT_EFSDIV_EVX4:
        case PPC32_IT_EFSMUL_EVX4:
        case PPC32_IT_EFSSUB_EVX4:
        case PPC32_IT_EVADDW_EVX4:
        case PPC32_IT_EVAND_EVX4:
        case PPC32_IT_EVANDC_EVX4:
        case PPC32_IT_EVDIVWS_EVX4:
        case PPC32_IT_EVDIVWU_EVX4:
        case PPC32_IT_EVEQV_EVX4:
        case PPC32_IT_EVFSADD_EVX4:
        case PPC32_IT_EVFSDIV_EVX4:
        case PPC32_IT_EVFSMUL_EVX4:
        case PPC32_IT_EVFSSUB_EVX4:
        case PPC32_IT_EVLDDX_EVX4:
        case PPC32_IT_EVLDHX_EVX4:
        case PPC32_IT_EVLDWX_EVX4:
        case PPC32_IT_EVLHHESPLATX_EVX4:
        case PPC32_IT_EVLHHOSSPLATX_EVX4:
        case PPC32_IT_EVLHHOUSPLATX_EVX4:
        case PPC32_IT_EVLWHEX_EVX4:
        case PPC32_IT_EVLWHOSX_EVX4:
        case PPC32_IT_EVLWHOUX_EVX4:
        case PPC32_IT_EVLWHSPLATX_EVX4:
        case PPC32_IT_EVLWWSPLATX_EVX4:
        case PPC32_IT_EVMERGEHI_EVX4:
        case PPC32_IT_EVMERGEHILO_EVX4:
        case PPC32_IT_EVMERGELO_EVX4:
        case PPC32_IT_EVMERGELOHI_EVX4:
        case PPC32_IT_EVMHEGSMFAA_EVX4:
        case PPC32_IT_EVMHEGSMFAN_EVX4:
        case PPC32_IT_EVMHEGSMIAA_EVX4:
        case PPC32_IT_EVMHEGSMIAN_EVX4:
        case PPC32_IT_EVMHEGUMIAA_EVX4:
        case PPC32_IT_EVMHEGUMIAN_EVX4:
        case PPC32_IT_EVMHESMF_EVX4:
        case PPC32_IT_EVMHESMFA_EVX4:
        case PPC32_IT_EVMHESMFAAW_EVX4:
        case PPC32_IT_EVMHESMFANW_EVX4:
        case PPC32_IT_EVMHESMI_EVX4:
        case PPC32_IT_EVMHESMIA_EVX4:
        case PPC32_IT_EVMHESMIAAW_EVX4:
        case PPC32_IT_EVMHESMIANW_EVX4:
        case PPC32_IT_EVMHESSF_EVX4:
        case PPC32_IT_EVMHESSFA_EVX4:
        case PPC32_IT_EVMHESSFAAW_EVX4:
        case PPC32_IT_EVMHESSFANW_EVX4:
        case PPC32_IT_EVMHESSIAAW_EVX4:
        case PPC32_IT_EVMHESSIANW_EVX4:
        case PPC32_IT_EVMHEUMI_EVX4:
        case PPC32_IT_EVMHEUMIA_EVX4:
        case PPC32_IT_EVMHEUMIAAW_EVX4:
        case PPC32_IT_EVMHEUMIANW_EVX4:
        case PPC32_IT_EVMHEUSIAAW_EVX4:
        case PPC32_IT_EVMHEUSIANW_EVX4:
        case PPC32_IT_EVMHOGSMFAA_EVX4:
        case PPC32_IT_EVMHOGSMFAN_EVX4:
        case PPC32_IT_EVMHOGSMIAA_EVX4:
        case PPC32_IT_EVMHOGSMIAN_EVX4:
        case PPC32_IT_EVMHOGUMIAA_EVX4:
        case PPC32_IT_EVMHOGUMIAN_EVX4:
        case PPC32_IT_EVMHOSMF_EVX4:
        case PPC32_IT_EVMHOSMFA_EVX4:
        case PPC32_IT_EVMHOSMFAAW_EVX4:
        case PPC32_IT_EVMHOSMFANW_EVX4:
        case PPC32_IT_EVMHOSMI_EVX4:
        case PPC32_IT_EVMHOSMIA_EVX4:
        case PPC32_IT_EVMHOSMIAAW_EVX4:
        case PPC32_IT_EVMHOSMIANW_EVX4:
        case PPC32_IT_EVMHOSSF_EVX4:
        case PPC32_IT_EVMHOSSFA_EVX4:
        case PPC32_IT_EVMHOSSFAAW_EVX4:
        case PPC32_IT_EVMHOSSFANW_EVX4:
        case PPC32_IT_EVMHOSSIAAW_EVX4:
        case PPC32_IT_EVMHOSSIANW_EVX4:
        case PPC32_IT_EVMHOUMI_EVX4:
        case PPC32_IT_EVMHOUMIA_EVX4:
        case PPC32_IT_EVMHOUMIAAW_EVX4:
        case PPC32_IT_EVMHOUMIANW_EVX4:
        case PPC32_IT_EVMHOUSIAAW_EVX4:
        case PPC32_IT_EVMHOUSIANW_EVX4:
        case PPC32_IT_EVMWHSMF_EVX4:
        case PPC32_IT_EVMWHSMFA_EVX4:
        case PPC32_IT_EVMWHSMI_EVX4:
        case PPC32_IT_EVMWHSMIA_EVX4:
        case PPC32_IT_EVMWHSSF_EVX4:
        case PPC32_IT_EVMWHSSFA_EVX4:
        case PPC32_IT_EVMWHUMI_EVX4:
        case PPC32_IT_EVMWHUMIA_EVX4:
        case PPC32_IT_EVMWLSMIAAW_EVX4:
        case PPC32_IT_EVMWLSMIANW_EVX4:
        case PPC32_IT_EVMWLSSIAAW_EVX4:
        case PPC32_IT_EVMWLSSIANW_EVX4:
        case PPC32_IT_EVMWLUMI_EVX4:
        case PPC32_IT_EVMWLUMIA_EVX4:
        case PPC32_IT_EVMWLUMIAAW_EVX4:
        case PPC32_IT_EVMWLUMIANW_EVX4:
        case PPC32_IT_EVMWLUSIAAW_EVX4:
        case PPC32_IT_EVMWLUSIANW_EVX4:
        case PPC32_IT_EVMWSMF_EVX4:
        case PPC32_IT_EVMWSMFA_EVX4:
        case PPC32_IT_EVMWSMFAA_EVX4:
        case PPC32_IT_EVMWSMFAN_EVX4:
        case PPC32_IT_EVMWSMI_EVX4:
        case PPC32_IT_EVMWSMIA_EVX4:
        case PPC32_IT_EVMWSMIAA_EVX4:
        case PPC32_IT_EVMWSMIAN_EVX4:
        case PPC32_IT_EVMWSSF_EVX4:
        case PPC32_IT_EVMWSSFA_EVX4:
        case PPC32_IT_EVMWSSFAA_EVX4:
        case PPC32_IT_EVMWSSFAN_EVX4:
        case PPC32_IT_EVMWUMI_EVX4:
        case PPC32_IT_EVMWUMIA_EVX4:
        case PPC32_IT_EVMWUMIAA_EVX4:
        case PPC32_IT_EVMWUMIAN_EVX4:
        case PPC32_IT_EVNAND_EVX4:
        case PPC32_IT_EVNOR_EVX4:
        case PPC32_IT_EVOR_EVX4:
        case PPC32_IT_EVORC_EVX4:
        case PPC32_IT_EVRLW_EVX4:
        case PPC32_IT_EVSLW_EVX4:
        case PPC32_IT_EVSRWS_EVX4:
        case PPC32_IT_EVSRWU_EVX4:
        case PPC32_IT_EVSUBFW_EVX4:
        case PPC32_IT_EVXOR_EVX4:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_EFDABS_EVX5:
        case PPC32_IT_EFDNABS_EVX5:
        case PPC32_IT_EFDNEG_EVX5:
        case PPC32_IT_EFSABS_EVX5:
        case PPC32_IT_EFSNABS_EVX5:
        case PPC32_IT_EFSNEG_EVX5:
        case PPC32_IT_EVABS_EVX5:
        case PPC32_IT_EVADDSMIAAW_EVX5:
        case PPC32_IT_EVADDSSIAAW_EVX5:
        case PPC32_IT_EVADDUMIAAW_EVX5:
        case PPC32_IT_EVADDUSIAAW_EVX5:
        case PPC32_IT_EVCNTLSW_EVX5:
        case PPC32_IT_EVCNTLZW_EVX5:
        case PPC32_IT_EVEXTSB_EVX5:
        case PPC32_IT_EVEXTSH_EVX5:
        case PPC32_IT_EVFSABS_EVX5:
        case PPC32_IT_EVFSNABS_EVX5:
        case PPC32_IT_EVFSNEG_EVX5:
        case PPC32_IT_EVMRA_EVX5:
        case PPC32_IT_EVNEG_EVX5:
        case PPC32_IT_EVRNDW_EVX5:
        case PPC32_IT_EVSUBFSMIAAW_EVX5:
        case PPC32_IT_EVSUBFSSIAAW_EVX5:
        case PPC32_IT_EVSUBFUMIAAW_EVX5:
        case PPC32_IT_EVSUBFUSIAAW_EVX5:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_EVADDIW_EVX6_1:
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            info->UI = VECINDEX(info->instruction,20,16,0); // 20:16
            break;

        case PPC32_IT_EVSUBIFW_EVX6_2:
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            info->UI = VECINDEX(info->instruction,20,16,0); // 20:16
            break;

        case PPC32_IT_EFDCMPEQ_EVX7:
        case PPC32_IT_EFDCMPGT_EVX7:
        case PPC32_IT_EFDCMPLT_EVX7:
        case PPC32_IT_EFDTSTEQ_EVX7:
        case PPC32_IT_EFDTSTGT_EVX7:
        case PPC32_IT_EFDTSTLT_EVX7:
        case PPC32_IT_EFSCMPEQ_EVX7:
        case PPC32_IT_EFSCMPGT_EVX7:
        case PPC32_IT_EFSCMPLT_EVX7:
        case PPC32_IT_EFSTSTEQ_EVX7:
        case PPC32_IT_EFSTSTGT_EVX7:
        case PPC32_IT_EFSTSTLT_EVX7:
        case PPC32_IT_EVCMPEQ_EVX7:
        case PPC32_IT_EVCMPGTS_EVX7:
        case PPC32_IT_EVCMPGTU_EVX7:
        case PPC32_IT_EVCMPLTS_EVX7:
        case PPC32_IT_EVCMPLTU_EVX7:
        case PPC32_IT_EVFSCMPEQ_EVX7:
        case PPC32_IT_EVFSCMPGT_EVX7:
        case PPC32_IT_EVFSCMPLT_EVX7:
        case PPC32_IT_EVFSTSTEQ_EVX7:
        case PPC32_IT_EVFSTSTGT_EVX7:
        case PPC32_IT_EVFSTSTLT_EVX7:
            info->BF = VECINDEX(info->instruction,25,23,0); // 25:23
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case PPC32_IT_EVRLWI_EVX8:
        case PPC32_IT_EVSLWI_EVX8:
        case PPC32_IT_EVSRWIS_EVX8:
        case PPC32_IT_EVSRWIU_EVX8:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            info->UI = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case PPC32_IT_EVLHHESPLAT_EVX8_1:
        case PPC32_IT_EVLHHOSSPLAT_EVX8_1:
        case PPC32_IT_EVLHHOUSPLAT_EVX8_1:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            info->UI = VECINDEX(info->instruction,15,11,0); // 15:11
            info->UI = SHIFTL(info->UI,1);
            break;

        case PPC32_IT_EVLWHE_EVX8_2:
        case PPC32_IT_EVLWHOS_EVX8_2:
        case PPC32_IT_EVLWHOU_EVX8_2:
        case PPC32_IT_EVLWHSPLAT_EVX8_2:
        case PPC32_IT_EVLWWSPLAT_EVX8_2:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            info->UI = VECINDEX(info->instruction,15,11,0); // 15:11
            info->UI = SHIFTL(info->UI,2);
            break;

        case PPC32_IT_EVLDD_EVX8_3:
        case PPC32_IT_EVLDH_EVX8_3:
        case PPC32_IT_EVLDW_EVX8_3:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            info->UI = VECINDEX(info->instruction,15,11,0); // 15:11
            info->UI = SHIFTL(info->UI,3);
            break;

        case PPC32_IT_EVSPLATFI_EVX9:
        case PPC32_IT_EVSPLATI_EVX9:
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            info->SI = VECINDEX(info->instruction,20,16,0); // 20:16
            info->SI = SEXTEND(info->SI,4);
            break;

        case PPC32_IT_B_I1:
            info->AA = VECINDEX(info->instruction,1,1,0); // 1
            info->LI = VECINDEX(info->instruction,25,2,0); // 25:2
            info->LI = SHIFTL(info->LI,2);
            info->LI = SEXTEND(info->LI,25);
            info->LK = VECINDEX(info->instruction,0,0,0); // 0
            break;

        case PPC32_IT_E_ADD2IRC_I16A1:
        case PPC32_IT_E_ADD2IS_I16A1:
        case PPC32_IT_E_CMP16I_I16A1:
        case PPC32_IT_E_CMPH16I_I16A1:
        case PPC32_IT_E_MULL2I_I16A1:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->SI = VECINDEX(info->instruction,25,21,11) | VECINDEX(info->instruction,10,0,0); // 25:21 10:0
            info->SI = SEXTEND(info->SI,15);
            break;

        case PPC32_IT_E_CMPHL16I_I16A2:
        case PPC32_IT_E_CMPL16I_I16A2:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->UI = VECINDEX(info->instruction,25,21,11) | VECINDEX(info->instruction,10,0,0); // 25:21 10:0
            break;

        case PPC32_IT_E_AND2IRC_I16L:
        case PPC32_IT_E_AND2ISRC_I16L:
        case PPC32_IT_E_LIS_I16L:
        case PPC32_IT_E_OR2I_I16L:
        case PPC32_IT_E_OR2IS_I16L:
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            info->UI = VECINDEX(info->instruction,20,16,11) | VECINDEX(info->instruction,10,0,0); // 20:16 10:0
            break;

        case PPC32_IT_SE_ANDI_IM5:
        case PPC32_IT_SE_BMASKI_IM5:
        case PPC32_IT_SE_CMPI_IM5:
            info->RX = VECINDEX(info->instruction,3,3,4) | VECINDEX(info->instruction,3,0,0); // 3 3:0
            info->UI5 = VECINDEX(info->instruction,8,4,0); // 8:4
            break;

        case PPC32_IT_SE_LI_IM7:
            info->RX = VECINDEX(info->instruction,3,3,4) | VECINDEX(info->instruction,3,0,0); // 3 3:0
            info->UI7 = VECINDEX(info->instruction,10,4,0); // 10:4
            break;

        case PPC32_IT_E_LI_LI20:
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            info->li20 = VECINDEX(info->instruction,14,11,16) | VECINDEX(info->instruction,20,16,11) | VECINDEX(info->instruction,10,0,0); // 14:11 20:16 10:0
            info->li20 = SEXTEND(info->li20,19);
            break;

        case PPC32_IT_RLWNM_M1_0:
        case PPC32_IT_RLWNMRC_M1_0:
            info->MB = VECINDEX(info->instruction,10,6,0); // 10:6
            info->ME = VECINDEX(info->instruction,5,1,0); // 5:1
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_RLWNMRC_0_M1_1:
        case PPC32_IT_RLWNM_0_M1_1:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_E_RLWIMI_M2_0:
        case PPC32_IT_E_RLWINM_M2_0:
        case PPC32_IT_RLWIMI_M2_0:
        case PPC32_IT_RLWIMIRC_M2_0:
        case PPC32_IT_RLWINM_M2_0:
        case PPC32_IT_RLWINMRC_M2_0:
            info->MB = VECINDEX(info->instruction,10,6,0); // 10:6
            info->ME = VECINDEX(info->instruction,5,1,0); // 5:1
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            info->SH = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case PPC32_IT_RLWINMRC_0_M2_1:
        case PPC32_IT_RLWINM_0_M2_1:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            info->SH = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case PPC32_IT_SE_BCLRI_OIM51_0:
        case PPC32_IT_SE_BGENI_OIM51_0:
        case PPC32_IT_SE_BSETI_OIM51_0:
        case PPC32_IT_SE_BTSTI_OIM51_0:
        case PPC32_IT_SE_SLWI_OIM51_0:
        case PPC32_IT_SE_SRAWI_OIM51_0:
        case PPC32_IT_SE_SRWI_OIM51_0:
            info->OIM5 = VECINDEX(info->instruction,8,4,0); // 8:4
            info->RX = VECINDEX(info->instruction,3,3,4) | VECINDEX(info->instruction,3,0,0); // 3 3:0
            break;

        case PPC32_IT_SE_ADDI_OIM51_1:
        case PPC32_IT_SE_CMPLI_OIM51_1:
            info->OIM5 = VECINDEX(info->instruction,8,4,0); // 8:4
            info->OIM5 += 1;
            info->RX = VECINDEX(info->instruction,3,3,4) | VECINDEX(info->instruction,3,0,0); // 3 3:0
            break;

        case PPC32_IT_SE_SUBI_OIM52_0:
        case PPC32_IT_SE_SUBIRC_OIM52_0:
            info->OIM5 = VECINDEX(info->instruction,8,4,0); // 8:4
            info->OIM5 += 1;
            info->RX = VECINDEX(info->instruction,3,3,4) | VECINDEX(info->instruction,3,0,0); // 3 3:0
            break;

        case PPC32_IT_SE_EXTSB_R1:
        case PPC32_IT_SE_EXTSH_R1:
        case PPC32_IT_SE_EXTZB_R1:
        case PPC32_IT_SE_EXTZH_R1:
        case PPC32_IT_SE_MFCTR_R1:
        case PPC32_IT_SE_MFLR_R1:
        case PPC32_IT_SE_MTCTR_R1:
        case PPC32_IT_SE_MTLR_R1:
        case PPC32_IT_SE_NEG_R1:
        case PPC32_IT_SE_NOT_R1:
            info->RX = VECINDEX(info->instruction,3,3,4) | VECINDEX(info->instruction,3,0,0); // 3 3:0
            break;

        case PPC32_IT_SE_ADD_RR1:
        case PPC32_IT_SE_ANDC_RR1:
        case PPC32_IT_SE_CMP_RR1:
        case PPC32_IT_SE_CMPH_RR1:
        case PPC32_IT_SE_CMPHL_RR1:
        case PPC32_IT_SE_CMPL_RR1:
        case PPC32_IT_SE_MR_RR1:
        case PPC32_IT_SE_MULLW_RR1:
        case PPC32_IT_SE_OR_RR1:
        case PPC32_IT_SE_SLW_RR1:
        case PPC32_IT_SE_SRAW_RR1:
        case PPC32_IT_SE_SRW_RR1:
        case PPC32_IT_SE_SUB_RR1:
        case PPC32_IT_SE_SUBF_RR1:
            info->RX = VECINDEX(info->instruction,3,3,4) | VECINDEX(info->instruction,3,0,0); // 3 3:0
            info->RY = VECINDEX(info->instruction,7,7,4) | VECINDEX(info->instruction,7,4,0); // 7 7:4
            break;

        case PPC32_IT_SE_AND_RR2:
        case PPC32_IT_SE_ANDRC_RR2:
            info->RX = VECINDEX(info->instruction,3,3,4) | VECINDEX(info->instruction,3,0,0); // 3 3:0
            info->RY = VECINDEX(info->instruction,7,7,4) | VECINDEX(info->instruction,7,4,0); // 7 7:4
            break;

        case PPC32_IT_SE_MFAR_RR3:
            info->ARY = VECINDEX(info->instruction,7,4,0); // 7:4
            info->ARY += 8;
            info->RX = VECINDEX(info->instruction,3,3,4) | VECINDEX(info->instruction,3,0,0); // 3 3:0
            break;

        case PPC32_IT_SE_MTAR_RR4:
            info->ARX = VECINDEX(info->instruction,3,0,0); // 3:0
            info->ARX += 8;
            info->RY = VECINDEX(info->instruction,7,7,4) | VECINDEX(info->instruction,7,4,0); // 7 7:4
            break;

        case PPC32_IT_SC_SC1:
            info->LEV = VECINDEX(info->instruction,11,5,0); // 11:5
            break;

        case PPC32_IT_E_ADDI_SCI8_1:
        case PPC32_IT_E_ADDIC_SCI8_1:
        case PPC32_IT_E_ADDICRC_SCI8_1:
        case PPC32_IT_E_ADDIRC_SCI8_1:
        case PPC32_IT_E_SUBFIC_SCI8_1:
        case PPC32_IT_E_SUBFICRC_SCI8_1:
            info->F = VECINDEX(info->instruction,10,10,0); // 10
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            info->SCL = VECINDEX(info->instruction,9,8,0); // 9:8
            info->U8 = VECINDEX(info->instruction,7,0,0); // 7:0
            break;

        case PPC32_IT_E_MULLI_SCI8_2:
            info->F = VECINDEX(info->instruction,10,10,0); // 10
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            info->SCL = VECINDEX(info->instruction,9,8,0); // 9:8
            info->U8 = VECINDEX(info->instruction,7,0,0); // 7:0
            break;

        case PPC32_IT_E_ANDI_SCI8_3:
        case PPC32_IT_E_ANDIRC_SCI8_3:
        case PPC32_IT_E_ORI_SCI8_3:
        case PPC32_IT_E_ORIRC_SCI8_3:
        case PPC32_IT_E_XORI_SCI8_3:
        case PPC32_IT_E_XORIRC_SCI8_3:
            info->F = VECINDEX(info->instruction,10,10,0); // 10
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            info->SCL = VECINDEX(info->instruction,9,8,0); // 9:8
            info->U8 = VECINDEX(info->instruction,7,0,0); // 7:0
            break;

        case PPC32_IT_E_CMPI_SCI8_5:
            info->BF32 = VECINDEX(info->instruction,22,21,0); // 22:21
            info->F = VECINDEX(info->instruction,10,10,0); // 10
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->S8 = VECINDEX(info->instruction,7,0,0); // 7:0
            info->S8 = SEXTEND(info->S8,7);
            info->SCL = VECINDEX(info->instruction,9,8,0); // 9:8
            break;

        case PPC32_IT_E_CMPLI_SCI8_6:
            info->BF32 = VECINDEX(info->instruction,22,21,0); // 22:21
            info->F = VECINDEX(info->instruction,10,10,0); // 10
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->S8 = VECINDEX(info->instruction,7,0,0); // 7:0
            info->S8 = SEXTEND(info->S8,7);
            info->SCL = VECINDEX(info->instruction,9,8,0); // 9:8
            break;

        case PPC32_IT_SE_LBZ_SD4_0:
        case PPC32_IT_SE_STB_SD4_0:
            info->RX = VECINDEX(info->instruction,3,3,4) | VECINDEX(info->instruction,3,0,0); // 3 3:0
            info->RZ = VECINDEX(info->instruction,7,7,4) | VECINDEX(info->instruction,7,4,0); // 7 7:4
            info->SD4 = VECINDEX(info->instruction,11,8,0); // 11:8
            break;

        case PPC32_IT_SE_LHZ_SD4_1:
        case PPC32_IT_SE_STH_SD4_1:
            info->RX = VECINDEX(info->instruction,3,3,4) | VECINDEX(info->instruction,3,0,0); // 3 3:0
            info->RZ = VECINDEX(info->instruction,7,7,4) | VECINDEX(info->instruction,7,4,0); // 7 7:4
            info->SD4 = VECINDEX(info->instruction,11,8,0); // 11:8
            info->SD4 = SHIFTL(info->SD4,1);
            break;

        case PPC32_IT_SE_LWZ_SD4_2:
        case PPC32_IT_SE_STW_SD4_2:
            info->RX = VECINDEX(info->instruction,3,3,4) | VECINDEX(info->instruction,3,0,0); // 3 3:0
            info->RZ = VECINDEX(info->instruction,7,7,4) | VECINDEX(info->instruction,7,4,0); // 7 7:4
            info->SD4 = VECINDEX(info->instruction,11,8,0); // 11:8
            info->SD4 = SHIFTL(info->SD4,2);
            break;

        case PPC32_IT_VMHADDSHS_VA1_0:
        case PPC32_IT_VMHRADDSHS_VA1_0:
        case PPC32_IT_VMLADDUHM_VA1_0:
        case PPC32_IT_VMSUMMBM_VA1_0:
        case PPC32_IT_VMSUMSHM_VA1_0:
        case PPC32_IT_VMSUMSHS_VA1_0:
        case PPC32_IT_VMSUMUBM_VA1_0:
        case PPC32_IT_VMSUMUHM_VA1_0:
        case PPC32_IT_VMSUMUHS_VA1_0:
        case PPC32_IT_VPERM_VA1_0:
        case PPC32_IT_VSEL_VA1_0:
            info->VRA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->VRB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->VRC = VECINDEX(info->instruction,10,6,0); // 10:6
            info->VRT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_VMADDFP_VA1_1:
        case PPC32_IT_VMSUBFP_VA1_1:
            info->VRA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->VRB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->VRC = VECINDEX(info->instruction,10,6,0); // 10:6
            info->VRT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_VSLDOI_VA2:
            info->SHB = VECINDEX(info->instruction,9,6,0); // 9:6
            info->VRA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->VRB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->VRT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_VCMPBFP_VC1:
        case PPC32_IT_VCMPBFPRC_VC1:
        case PPC32_IT_VCMPEQFP_VC1:
        case PPC32_IT_VCMPEQFPRC_VC1:
        case PPC32_IT_VCMPEQUB_VC1:
        case PPC32_IT_VCMPEQUBRC_VC1:
        case PPC32_IT_VCMPEQUH_VC1:
        case PPC32_IT_VCMPEQUHRC_VC1:
        case PPC32_IT_VCMPEQUW_VC1:
        case PPC32_IT_VCMPEQUWRC_VC1:
        case PPC32_IT_VCMPGEFP_VC1:
        case PPC32_IT_VCMPGEFPRC_VC1:
        case PPC32_IT_VCMPGTFP_VC1:
        case PPC32_IT_VCMPGTFPRC_VC1:
        case PPC32_IT_VCMPGTSB_VC1:
        case PPC32_IT_VCMPGTSBRC_VC1:
        case PPC32_IT_VCMPGTSH_VC1:
        case PPC32_IT_VCMPGTSHRC_VC1:
        case PPC32_IT_VCMPGTSW_VC1:
        case PPC32_IT_VCMPGTSWRC_VC1:
        case PPC32_IT_VCMPGTUB_VC1:
        case PPC32_IT_VCMPGTUBRC_VC1:
        case PPC32_IT_VCMPGTUH_VC1:
        case PPC32_IT_VCMPGTUHRC_VC1:
        case PPC32_IT_VCMPGTUW_VC1:
        case PPC32_IT_VCMPGTUWRC_VC1:
            info->VRA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->VRB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->VRT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_VADDCUW_VX1:
        case PPC32_IT_VADDFP_VX1:
        case PPC32_IT_VADDSBS_VX1:
        case PPC32_IT_VADDSHS_VX1:
        case PPC32_IT_VADDSWS_VX1:
        case PPC32_IT_VADDUBM_VX1:
        case PPC32_IT_VADDUBS_VX1:
        case PPC32_IT_VADDUHM_VX1:
        case PPC32_IT_VADDUHS_VX1:
        case PPC32_IT_VADDUWM_VX1:
        case PPC32_IT_VADDUWS_VX1:
        case PPC32_IT_VAND_VX1:
        case PPC32_IT_VANDC_VX1:
        case PPC32_IT_VAVGSB_VX1:
        case PPC32_IT_VAVGSH_VX1:
        case PPC32_IT_VAVGSW_VX1:
        case PPC32_IT_VAVGUB_VX1:
        case PPC32_IT_VAVGUH_VX1:
        case PPC32_IT_VAVGUW_VX1:
        case PPC32_IT_VKPPX_VX1:
        case PPC32_IT_VKPSHSS_VX1:
        case PPC32_IT_VKPSHUS_VX1:
        case PPC32_IT_VKPSWSS_VX1:
        case PPC32_IT_VKPSWUS_VX1:
        case PPC32_IT_VKPUHUM_VX1:
        case PPC32_IT_VKPUHUS_VX1:
        case PPC32_IT_VKPUWUM_VX1:
        case PPC32_IT_VKPUWUS_VX1:
        case PPC32_IT_VMAXFP_VX1:
        case PPC32_IT_VMAXSB_VX1:
        case PPC32_IT_VMAXSH_VX1:
        case PPC32_IT_VMAXSW_VX1:
        case PPC32_IT_VMAXUB_VX1:
        case PPC32_IT_VMAXUH_VX1:
        case PPC32_IT_VMAXUW_VX1:
        case PPC32_IT_VMINFP_VX1:
        case PPC32_IT_VMINSB_VX1:
        case PPC32_IT_VMINSH_VX1:
        case PPC32_IT_VMINSW_VX1:
        case PPC32_IT_VMINUB_VX1:
        case PPC32_IT_VMINUH_VX1:
        case PPC32_IT_VMINUW_VX1:
        case PPC32_IT_VMRGHB_VX1:
        case PPC32_IT_VMRGHH_VX1:
        case PPC32_IT_VMRGHW_VX1:
        case PPC32_IT_VMRGLB_VX1:
        case PPC32_IT_VMRGLH_VX1:
        case PPC32_IT_VMRGLW_VX1:
        case PPC32_IT_VMULESB_VX1:
        case PPC32_IT_VMULESH_VX1:
        case PPC32_IT_VMULEUB_VX1:
        case PPC32_IT_VMULEUH_VX1:
        case PPC32_IT_VMULOSB_VX1:
        case PPC32_IT_VMULOSH_VX1:
        case PPC32_IT_VMULOUB_VX1:
        case PPC32_IT_VMULOUH_VX1:
        case PPC32_IT_VNOR_VX1:
        case PPC32_IT_VOR_VX1:
        case PPC32_IT_VRLB_VX1:
        case PPC32_IT_VRLH_VX1:
        case PPC32_IT_VRLW_VX1:
        case PPC32_IT_VSL_VX1:
        case PPC32_IT_VSLB_VX1:
        case PPC32_IT_VSLH_VX1:
        case PPC32_IT_VSLO_VX1:
        case PPC32_IT_VSLW_VX1:
        case PPC32_IT_VSR_VX1:
        case PPC32_IT_VSRAB_VX1:
        case PPC32_IT_VSRAH_VX1:
        case PPC32_IT_VSRAW_VX1:
        case PPC32_IT_VSRB_VX1:
        case PPC32_IT_VSRH_VX1:
        case PPC32_IT_VSRO_VX1:
        case PPC32_IT_VSRW_VX1:
        case PPC32_IT_VSUBCUW_VX1:
        case PPC32_IT_VSUBFP_VX1:
        case PPC32_IT_VSUBSBS_VX1:
        case PPC32_IT_VSUBSHS_VX1:
        case PPC32_IT_VSUBSWS_VX1:
        case PPC32_IT_VSUBUBM_VX1:
        case PPC32_IT_VSUBUBS_VX1:
        case PPC32_IT_VSUBUHM_VX1:
        case PPC32_IT_VSUBUHS_VX1:
        case PPC32_IT_VSUBUWM_VX1:
        case PPC32_IT_VSUBUWS_VX1:
        case PPC32_IT_VSUM2SWS_VX1:
        case PPC32_IT_VSUM4SBS_VX1:
        case PPC32_IT_VSUM4SHS_VX1:
        case PPC32_IT_VSUM4UBS_VX1:
        case PPC32_IT_VSUMSWS_VX1:
        case PPC32_IT_VXOR_VX1:
            info->VRA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->VRB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->VRT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_VEXPTEFP_VX2:
        case PPC32_IT_VLOGEFP_VX2:
        case PPC32_IT_VREFP_VX2:
        case PPC32_IT_VRFIM_VX2:
        case PPC32_IT_VRFIN_VX2:
        case PPC32_IT_VRFIP_VX2:
        case PPC32_IT_VRFIZ_VX2:
        case PPC32_IT_VRSQRTEFP_VX2:
        case PPC32_IT_VUPKHPX_VX2:
        case PPC32_IT_VUPKHSB_VX2:
        case PPC32_IT_VUPKHSH_VX2:
        case PPC32_IT_VUPKLPX_VX2:
        case PPC32_IT_VUPKLSB_VX2:
        case PPC32_IT_VUPKLSH_VX2:
            info->VRB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->VRT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_VCFSX_VX3:
        case PPC32_IT_VCFUX_VX3:
        case PPC32_IT_VCTSXS_VX3:
        case PPC32_IT_VCTUXS_VX3:
            info->UIM = VECINDEX(info->instruction,20,16,0); // 20:16
            info->VRB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->VRT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_VSPLTB_VX4:
            info->UIM = VECINDEX(info->instruction,19,16,0); // 19:16
            info->VRB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->VRT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_VSPLTH_VX5:
            info->UIM = VECINDEX(info->instruction,18,16,0); // 18:16
            info->VRB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->VRT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_VSPLTW_VX6:
            info->UIM = VECINDEX(info->instruction,17,16,0); // 17:16
            info->VRB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->VRT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_VSPLTISB_VX7:
        case PPC32_IT_VSPLTISH_VX7:
        case PPC32_IT_VSPLTISW_VX7:
            info->SIM = VECINDEX(info->instruction,20,16,0); // 20:16
            info->SIM = SEXTEND(info->SIM,4);
            info->VRT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_MFVSCR_VX8:
            info->VRT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_MTVSCR_VX9:
            info->VRB = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case PPC32_IT_MFAPIDI_X1:
        case PPC32_IT_MFDCRUX_X1:
        case PPC32_IT_MFDCRX_X1:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_MULCHW_X10:
        case PPC32_IT_MULCHWRC_X10:
        case PPC32_IT_MULCHWU_X10:
        case PPC32_IT_MULCHWURC_X10:
        case PPC32_IT_MULHHW_X10:
        case PPC32_IT_MULHHWRC_X10:
        case PPC32_IT_MULHHWU_X10:
        case PPC32_IT_MULHHWURC_X10:
        case PPC32_IT_MULLHW_X10:
        case PPC32_IT_MULLHWRC_X10:
        case PPC32_IT_MULLHWU_X10:
        case PPC32_IT_MULLHWURC_X10:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_STWCXRC_X11:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_CMPB_X12:
        case PPC32_IT_STBCIX_X12:
        case PPC32_IT_STBEPX_X12:
        case PPC32_IT_STBUX_X12:
        case PPC32_IT_STBX_X12:
        case PPC32_IT_STDCIX_X12:
        case PPC32_IT_STDEPX_X12:
        case PPC32_IT_STHBRX_X12:
        case PPC32_IT_STHCIX_X12:
        case PPC32_IT_STHEPX_X12:
        case PPC32_IT_STHUX_X12:
        case PPC32_IT_STHX_X12:
        case PPC32_IT_STSWX_X12:
        case PPC32_IT_STWBRX_X12:
        case PPC32_IT_STWCIX_X12:
        case PPC32_IT_STWEPX_X12:
        case PPC32_IT_STWUX_X12:
        case PPC32_IT_STWX_X12:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_STSWI_X13:
            info->NB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_E_RLWI_X14:
        case PPC32_IT_E_RLWIRC_X14:
        case PPC32_IT_E_SLWI_X14:
        case PPC32_IT_E_SLWIRC_X14:
        case PPC32_IT_E_SRWI_X14:
        case PPC32_IT_E_SRWIRC_X14:
        case PPC32_IT_SRAWI_X14:
        case PPC32_IT_SRAWIRC_X14:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            info->SH = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case PPC32_IT_CNTLZW_X15:
        case PPC32_IT_CNTLZWRC_X15:
        case PPC32_IT_EXTSB_X15:
        case PPC32_IT_EXTSBRC_X15:
        case PPC32_IT_EXTSH_X15:
        case PPC32_IT_EXTSHRC_X15:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_CBCDTD_X16:
        case PPC32_IT_CDTBCD_X16:
        case PPC32_IT_MTDCRUX_X16:
        case PPC32_IT_MTDCRX_X16:
        case PPC32_IT_POPCNTB_X16:
        case PPC32_IT_PRTYW_X16:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_MTSR_X17:
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            info->SR = VECINDEX(info->instruction,19,16,0); // 19:16
            break;

        case PPC32_IT_MTSRIN_X18:
        case PPC32_IT_SLBMTE_X18:
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_MTMSR_X19_0:
            info->L = VECINDEX(info->instruction,16,16,0); // 16
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_WRTEE_X19_1:
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_DCREAD_X2:
        case PPC32_IT_ECIWX_X2:
        case PPC32_IT_ECOWX_X2:
        case PPC32_IT_LBEPX_X2:
        case PPC32_IT_LBZCIX_X2:
        case PPC32_IT_LBZUX_X2:
        case PPC32_IT_LBZX_X2:
        case PPC32_IT_LDCIX_X2:
        case PPC32_IT_LDEPX_X2:
        case PPC32_IT_LHAUX_X2:
        case PPC32_IT_LHAX_X2:
        case PPC32_IT_LHBRX_X2:
        case PPC32_IT_LHEPX_X2:
        case PPC32_IT_LHZCIX_X2:
        case PPC32_IT_LHZUX_X2:
        case PPC32_IT_LHZX_X2:
        case PPC32_IT_LSWX_X2:
        case PPC32_IT_LWBRX_X2:
        case PPC32_IT_LWEPX_X2:
        case PPC32_IT_LWZCIX_X2:
        case PPC32_IT_LWZUX_X2:
        case PPC32_IT_LWZX_X2:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_MTMSRD_X20:
            info->L = VECINDEX(info->instruction,16,16,0); // 16
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_CMPLW_X22_0:
        case PPC32_IT_CMPW_X22_0:
            info->BF = VECINDEX(info->instruction,25,23,0); // 25:23
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case PPC32_IT_CMP_X22_1:
        case PPC32_IT_CMPL_X22_1:
            info->BF = VECINDEX(info->instruction,25,23,0); // 25:23
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case PPC32_IT_E_CMPH_X22_2:
        case PPC32_IT_E_CMPHL_X22_2:
            info->BF = VECINDEX(info->instruction,25,23,0); // 25:23
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case PPC32_IT_DCMPO_X23:
        case PPC32_IT_DCMPU_X23:
        case PPC32_IT_DTSTEX_X23:
        case PPC32_IT_DTSTSF_X23:
        case PPC32_IT_FCMPO_X23:
        case PPC32_IT_FCMPU_X23:
            info->BF = VECINDEX(info->instruction,25,23,0); // 25:23
            info->FRA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->FRB = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case PPC32_IT_MCRFS_X24:
            info->BF = VECINDEX(info->instruction,25,23,0); // 25:23
            info->BFA = VECINDEX(info->instruction,20,18,0); // 20:18
            break;

        case PPC32_IT_MTFSFIZ_X25_0:
        case PPC32_IT_MTFSFIZRC_X25_0:
            info->BFU = VECINDEX(info->instruction,25,23,0); // 25:23
            info->U = VECINDEX(info->instruction,15,12,0); // 15:12
            break;

        case PPC32_IT_MTFSFI_X25_1:
        case PPC32_IT_MTFSFIRC_X25_1:
            info->BFU = VECINDEX(info->instruction,25,23,0); // 25:23
            info->U = VECINDEX(info->instruction,15,12,0); // 15:12
            break;

        case PPC32_IT_MCRXR_X26:
            info->BF = VECINDEX(info->instruction,25,23,0); // 25:23
            break;

        case PPC32_IT_DCBT_X27_0:
        case PPC32_IT_DCBTST_X27_0:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->TH = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_DCBTST_1_X27_1:
        case PPC32_IT_DCBT_1_X27_1:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case PPC32_IT_DCBTEP_X27_2:
        case PPC32_IT_DCBTSTEP_X27_2:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->TH = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_DCI_0_X28_0:
        case PPC32_IT_ICI_0_X28_0:
            info->CT = VECINDEX(info->instruction,24,21,0); // 24:21
            break;

        case PPC32_IT_DCI_X28_1:
        case PPC32_IT_ICI_X28_1:
            info->CT = VECINDEX(info->instruction,24,21,0); // 24:21
            break;

        case PPC32_IT_DCBLC_0_X29_0:
        case PPC32_IT_DCBTLS_0_X29_0:
        case PPC32_IT_DCBTSTLS_0_X29_0:
        case PPC32_IT_ICBLC_0_X29_0:
        case PPC32_IT_ICBTLS_0_X29_0:
        case PPC32_IT_ICBT_CT0_X29_0:
            info->CT = VECINDEX(info->instruction,24,21,0); // 24:21
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case PPC32_IT_DCBLC_1_X29_1:
        case PPC32_IT_DCBTLS_1_X29_1:
        case PPC32_IT_DCBTSTLS_1_X29_1:
        case PPC32_IT_ICBLC_1_X29_1:
        case PPC32_IT_ICBT_X29_1:
        case PPC32_IT_ICBTLS_1_X29_1:
            info->CT = VECINDEX(info->instruction,24,21,0); // 24:21
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case PPC32_IT_LWARX_X3:
            info->EH = VECINDEX(info->instruction,0,0,0); // 0
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_DCBF_X30:
        case PPC32_IT_DCBF_L_X30:
        case PPC32_IT_DCBF_LP_X30:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case PPC32_IT_TLBIEL_0_X31_0:
        case PPC32_IT_TLBIE_0_X31_0:
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case PPC32_IT_TLBIEL_1_X31_1:
        case PPC32_IT_TLBIE_1_X31_1:
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case PPC32_IT_LWSYNC_X32:
        case PPC32_IT_PTESYNC_X32:
        case PPC32_IT_SYNC_X32:
            break;

        case PPC32_IT_TW_X33:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->TO = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_LFDEPX_X34:
        case PPC32_IT_LFDUX_X34:
        case PPC32_IT_LFDX_X34:
        case PPC32_IT_LFIWAX_X34:
        case PPC32_IT_LFSUX_X34:
        case PPC32_IT_LFSX_X34:
        case PPC32_IT_STFDEPX_X34:
            info->FRT = VECINDEX(info->instruction,25,21,0); // 25:21
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case PPC32_IT_DADD_X35RC:
        case PPC32_IT_DADDRC_X35RC:
        case PPC32_IT_DDIV_X35RC:
        case PPC32_IT_DDIVRC_X35RC:
        case PPC32_IT_DIEX_X35RC:
        case PPC32_IT_DIEXRC_X35RC:
        case PPC32_IT_DMUL_X35RC:
        case PPC32_IT_DMULRC_X35RC:
        case PPC32_IT_DSUB_X35RC:
        case PPC32_IT_DSUBRC_X35RC:
        case PPC32_IT_FCPSGN_X35RC:
        case PPC32_IT_FCPSGNRC_X35RC:
            info->FRA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->FRB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->FRT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_DCTDP_X37:
        case PPC32_IT_DCTDPRC_X37:
        case PPC32_IT_DCTFIX_X37:
        case PPC32_IT_DCTFIXRC_X37:
        case PPC32_IT_DRSP_X37:
        case PPC32_IT_DRSPRC_X37:
        case PPC32_IT_DXEX_X37:
        case PPC32_IT_DXEXRC_X37:
        case PPC32_IT_FABS_X37:
        case PPC32_IT_FABSRC_X37:
        case PPC32_IT_FCFID_X37:
        case PPC32_IT_FCFIDRC_X37:
        case PPC32_IT_FCTID_X37:
        case PPC32_IT_FCTIDRC_X37:
        case PPC32_IT_FCTIDZ_X37:
        case PPC32_IT_FCTIDZRC_X37:
        case PPC32_IT_FCTIW_X37:
        case PPC32_IT_FCTIWRC_X37:
        case PPC32_IT_FCTIWZ_X37:
        case PPC32_IT_FCTIWZRC_X37:
        case PPC32_IT_FMR_X37:
        case PPC32_IT_FMRRC_X37:
        case PPC32_IT_FNABS_X37:
        case PPC32_IT_FNABSRC_X37:
        case PPC32_IT_FNEG_X37:
        case PPC32_IT_FNEGRC_X37:
        case PPC32_IT_FRIM_X37:
        case PPC32_IT_FRIMRC_X37:
        case PPC32_IT_FRIN_X37:
        case PPC32_IT_FRINRC_X37:
        case PPC32_IT_FRIP_X37:
        case PPC32_IT_FRIPRC_X37:
        case PPC32_IT_FRIZ_X37:
        case PPC32_IT_FRIZRC_X37:
        case PPC32_IT_FRSP_X37:
        case PPC32_IT_FRSPRC_X37:
            info->FRB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->FRT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_DCTFIXQ_X38:
        case PPC32_IT_DCTFIXQRC_X38:
        case PPC32_IT_DXEX_X38:
        case PPC32_IT_DXEXRC_X38:
            info->FRBp = VECINDEX(info->instruction,15,11,0); // 15:11
            info->FRT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_MFFS_X39:
        case PPC32_IT_MFFSRC_X39:
            info->FRT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_LSWI_X4:
            info->NB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_DCFFIXQ_X40:
        case PPC32_IT_DCFFIXQRC_X40:
        case PPC32_IT_DCTQPQ_X40:
        case PPC32_IT_DCTQPQRC_X40:
            info->FRB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->FRTp = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_DRDPQ_X41:
        case PPC32_IT_DRDPQRC_X41:
            info->FRBp = VECINDEX(info->instruction,15,11,0); // 15:11
            info->FRTp = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_DADDQ_X43:
        case PPC32_IT_DADDQRC_X43:
        case PPC32_IT_DDIVQ_X43:
        case PPC32_IT_DDIVQRC_X43:
        case PPC32_IT_DIEXQ_X43:
        case PPC32_IT_DIEXQRC_X43:
        case PPC32_IT_DMULQ_X43:
        case PPC32_IT_DMULQRC_X43:
        case PPC32_IT_DSUBQ_X43:
        case PPC32_IT_DSUBQRC_X43:
            info->FRAp = VECINDEX(info->instruction,20,16,0); // 20:16
            info->FRBp = VECINDEX(info->instruction,15,11,0); // 15:11
            info->FRTp = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_DCMPOQ_X45:
        case PPC32_IT_DCMPUQ_X45:
        case PPC32_IT_DTSTEXQ_X45:
        case PPC32_IT_DTSTSFQ_X45:
            info->BF = VECINDEX(info->instruction,25,23,0); // 25:23
            info->FRAp = VECINDEX(info->instruction,20,16,0); // 20:16
            info->FRBp = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case PPC32_IT_DDEDPD_X46_0:
        case PPC32_IT_DDEDPDRC_X46_0:
            info->FRB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->FRT = VECINDEX(info->instruction,25,21,0); // 25:21
            info->SP = VECINDEX(info->instruction,20,19,0); // 20:19
            break;

        case PPC32_IT_DENBCD_X46_1:
        case PPC32_IT_DENBCDRC_X46_1:
            info->FRB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->FRT = VECINDEX(info->instruction,25,21,0); // 25:21
            info->S = VECINDEX(info->instruction,20,20,0); // 20
            break;

        case PPC32_IT_DDEDPDQ_X47_0:
        case PPC32_IT_DDEDPDQRC_X47_0:
            info->FRBp = VECINDEX(info->instruction,15,11,0); // 15:11
            info->FRTp = VECINDEX(info->instruction,25,21,0); // 25:21
            info->SP = VECINDEX(info->instruction,20,19,0); // 20:19
            break;

        case PPC32_IT_DENBCDQ_X47_1:
        case PPC32_IT_DENBCDQRC_X47_1:
            info->FRBp = VECINDEX(info->instruction,15,11,0); // 15:11
            info->FRTp = VECINDEX(info->instruction,25,21,0); // 25:21
            info->S = VECINDEX(info->instruction,20,20,0); // 20
            break;

        case PPC32_IT_STFDUX_X48:
        case PPC32_IT_STFDX_X48:
        case PPC32_IT_STFIWX_X48:
        case PPC32_IT_STFSUX_X48:
        case PPC32_IT_STFSX_X48:
            info->FRS = VECINDEX(info->instruction,25,21,0); // 25:21
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case PPC32_IT_MFSR_X5:
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            info->SR = VECINDEX(info->instruction,19,16,0); // 19:16
            break;

        case PPC32_IT_MTFSSB0_X50:
        case PPC32_IT_MTFSSB0RC_X50:
        case PPC32_IT_MTFSSB1_X50:
        case PPC32_IT_MTFSSB1RC_X50:
            info->BT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_DCBA_X51:
        case PPC32_IT_DCBFEP_X51:
        case PPC32_IT_DCBI_X51:
        case PPC32_IT_DCBST_X51:
        case PPC32_IT_DCBSTEP_X51:
        case PPC32_IT_DCBZ_X51:
        case PPC32_IT_DCBZEP_X51:
        case PPC32_IT_ICBI_X51:
        case PPC32_IT_ICBIEP_X51:
        case PPC32_IT_ICREAD_X51:
        case PPC32_IT_TLBIVAX_X51:
        case PPC32_IT_TLBSX_X51:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case PPC32_IT_MSGCLR_X52:
        case PPC32_IT_MSGSND_X52:
        case PPC32_IT_SLBIE_X52:
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case PPC32_IT_EIEIO_X53_0:
            break;

        case PPC32_IT_TLBIA_X53_1:
        case PPC32_IT_TLBRE_X53_1:
        case PPC32_IT_TLBSYNC_X53_1:
        case PPC32_IT_TLBWE_X53_1:
        case PPC32_IT_WAIT_X53_1:
            break;

        case PPC32_IT_WRTEEI_X54:
            info->E = VECINDEX(info->instruction,15,15,0); // 15
            break;

        case PPC32_IT_SLBIA_0_X55_0:
            info->IH = VECINDEX(info->instruction,23,21,0); // 23:21
            break;

        case PPC32_IT_SLBIA_1_X55_1:
            info->IH = VECINDEX(info->instruction,23,21,0); // 23:21
            break;

        case PPC32_IT_LVEBX_X58:
        case PPC32_IT_LVEHX_X58:
        case PPC32_IT_LVEWX_X58:
        case PPC32_IT_LVSL_X58:
        case PPC32_IT_LVSR_X58:
        case PPC32_IT_LVX_X58:
        case PPC32_IT_LVXL_X58:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->VRT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_STVEBX_X59:
        case PPC32_IT_STVEHX_X59:
        case PPC32_IT_STVEWX_X59:
        case PPC32_IT_STVX_X59:
        case PPC32_IT_STVXL_X59:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->VRS = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_MFSRIN_X6:
        case PPC32_IT_SLBMFEE_X6:
        case PPC32_IT_SLBMFEV_X6:
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_MBAR_X60:
            info->MO = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_MFMSR_X8:
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_AND_X9:
        case PPC32_IT_ANDC_X9:
        case PPC32_IT_ANDCRC_X9:
        case PPC32_IT_ANDRC_X9:
        case PPC32_IT_DLMZB_X9:
        case PPC32_IT_DLMZBRC_X9:
        case PPC32_IT_EQV_X9:
        case PPC32_IT_EQVRC_X9:
        case PPC32_IT_E_RLW_X9:
        case PPC32_IT_E_RLWRC_X9:
        case PPC32_IT_NAND_X9:
        case PPC32_IT_NANDRC_X9:
        case PPC32_IT_NOR_X9:
        case PPC32_IT_NORRC_X9:
        case PPC32_IT_OR_X9:
        case PPC32_IT_ORC_X9:
        case PPC32_IT_ORCRC_X9:
        case PPC32_IT_ORRC_X9:
        case PPC32_IT_SLW_X9:
        case PPC32_IT_SLWRC_X9:
        case PPC32_IT_SRAW_X9:
        case PPC32_IT_SRAWRC_X9:
        case PPC32_IT_SRW_X9:
        case PPC32_IT_SRWRC_X9:
        case PPC32_IT_XOR_X9:
        case PPC32_IT_XORRC_X9:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_MTFSF_XFL:
        case PPC32_IT_MTFSFRC_XFL:
            info->BL = VECINDEX(info->instruction,25,25,0); // 25
            info->BW = VECINDEX(info->instruction,16,16,0); // 16
            info->FLM = VECINDEX(info->instruction,24,17,0); // 24:17
            info->FRB = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case PPC32_IT_MTFSFZ_XFLZ:
        case PPC32_IT_MTFSFZRC_XFLZ:
            info->BL = VECINDEX(info->instruction,25,25,0); // 25
            info->BW = VECINDEX(info->instruction,16,16,0); // 16
            info->FLM = VECINDEX(info->instruction,24,17,0); // 24:17
            info->FRB = VECINDEX(info->instruction,15,11,0); // 15:11
            break;

        case PPC32_IT_MFSPR_XFX1:
        case PPC32_IT_MFTB_XFX1:
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            info->SPR = VECINDEX(info->instruction,15,11,5) | VECINDEX(info->instruction,20,16,0); // 15:11 20:16
            break;

        case PPC32_IT_MTSPR_XFX10:
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            info->SPR = VECINDEX(info->instruction,15,11,5) | VECINDEX(info->instruction,20,16,0); // 15:11 20:16
            break;

        case PPC32_IT_MTCTR_XFX10D:
        case PPC32_IT_MTLR_XFX10D:
        case PPC32_IT_MTXER_XFX10D:
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_MTDCR_XFX11:
            info->DCR = VECINDEX(info->instruction,15,11,5) | VECINDEX(info->instruction,20,16,0); // 15:11 20:16
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_MTPMR_XFX12:
            info->PMRN = VECINDEX(info->instruction,15,11,5) | VECINDEX(info->instruction,20,16,0); // 15:11 20:16
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_MFCTR_XFX1D:
        case PPC32_IT_MFLR_XFX1D:
        case PPC32_IT_MFXER_XFX1D:
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_MFCR_XFX3:
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_MFOCRF_XFX4:
            info->FXM = VECINDEX(info->instruction,19,12,0); // 19:12
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_MFDCR_XFX5:
            info->DCR = VECINDEX(info->instruction,15,11,5) | VECINDEX(info->instruction,20,16,0); // 15:11 20:16
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_MFPMR_XFX6:
            info->PMRN = VECINDEX(info->instruction,15,11,5) | VECINDEX(info->instruction,20,16,0); // 15:11 20:16
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_MTCRF_XFX8:
            info->FXM = VECINDEX(info->instruction,19,12,0); // 19:12
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_MTCR_XFX8D:
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_MTOCRF_XFX9:
            info->FXM = VECINDEX(info->instruction,19,12,0); // 19:12
            info->RS = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_CRAND_XL1:
        case PPC32_IT_CRANDC_XL1:
        case PPC32_IT_CREQV_XL1:
        case PPC32_IT_CRNAND_XL1:
        case PPC32_IT_CRNOR_XL1:
        case PPC32_IT_CROR_XL1:
        case PPC32_IT_CRORC_XL1:
        case PPC32_IT_CRXOR_XL1:
        case PPC32_IT_E_CRAND_XL1:
        case PPC32_IT_E_CRANDC_XL1:
        case PPC32_IT_E_CREQV_XL1:
        case PPC32_IT_E_CRNAND_XL1:
        case PPC32_IT_E_CRNOR_XL1:
        case PPC32_IT_E_CROR_XL1:
        case PPC32_IT_E_CRORC_XL1:
        case PPC32_IT_E_CRXOR_XL1:
            info->BA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->BB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->BT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_BCCTR_XL2:
        case PPC32_IT_BCLR_XL2:
            info->BH = VECINDEX(info->instruction,12,11,0); // 12:11
            info->BI = VECINDEX(info->instruction,20,16,0); // 20:16
            info->BO = VECINDEX(info->instruction,25,21,0); // 25:21
            info->LK = VECINDEX(info->instruction,0,0,0); // 0
            break;

        case PPC32_IT_E_MCRF_XL3:
        case PPC32_IT_MCRF_XL3:
            info->BF = VECINDEX(info->instruction,25,23,0); // 25:23
            info->BFA = VECINDEX(info->instruction,20,18,0); // 20:18
            break;

        case PPC32_IT_DOZE_XL4:
        case PPC32_IT_HRFID_XL4:
        case PPC32_IT_ISYNC_XL4:
        case PPC32_IT_NAP_XL4:
        case PPC32_IT_RFCI_XL4:
        case PPC32_IT_RFI_XL4:
        case PPC32_IT_RFID_XL4:
        case PPC32_IT_RFMCI_XL4:
        case PPC32_IT_RVWINKLE_XL4:
        case PPC32_IT_SLEEP_XL4:
            break;

        case PPC32_IT_ADD_XO1:
        case PPC32_IT_ADDC_XO1:
        case PPC32_IT_ADDCOE_XO1:
        case PPC32_IT_ADDCOERC_XO1:
        case PPC32_IT_ADDCRC_XO1:
        case PPC32_IT_ADDE_XO1:
        case PPC32_IT_ADDEOE_XO1:
        case PPC32_IT_ADDEOERC_XO1:
        case PPC32_IT_ADDERC_XO1:
        case PPC32_IT_ADDOE_XO1:
        case PPC32_IT_ADDOERC_XO1:
        case PPC32_IT_ADDRC_XO1:
        case PPC32_IT_DIVW_XO1:
        case PPC32_IT_DIVWOE_XO1:
        case PPC32_IT_DIVWOERC_XO1:
        case PPC32_IT_DIVWRC_XO1:
        case PPC32_IT_DIVWU_XO1:
        case PPC32_IT_DIVWUOE_XO1:
        case PPC32_IT_DIVWUOERC_XO1:
        case PPC32_IT_DIVWURC_XO1:
        case PPC32_IT_MACCHW_XO1:
        case PPC32_IT_MACCHWOE_XO1:
        case PPC32_IT_MACCHWOERC_XO1:
        case PPC32_IT_MACCHWRC_XO1:
        case PPC32_IT_MACCHWS_XO1:
        case PPC32_IT_MACCHWSOE_XO1:
        case PPC32_IT_MACCHWSOERC_XO1:
        case PPC32_IT_MACCHWSRC_XO1:
        case PPC32_IT_MACCHWSU_XO1:
        case PPC32_IT_MACCHWSUOE_XO1:
        case PPC32_IT_MACCHWSUOERC_XO1:
        case PPC32_IT_MACCHWSURC_XO1:
        case PPC32_IT_MACCHWU_XO1:
        case PPC32_IT_MACCHWUOE_XO1:
        case PPC32_IT_MACCHWUOERC_XO1:
        case PPC32_IT_MACCHWURC_XO1:
        case PPC32_IT_MACHHW_XO1:
        case PPC32_IT_MACHHWOE_XO1:
        case PPC32_IT_MACHHWOERC_XO1:
        case PPC32_IT_MACHHWRC_XO1:
        case PPC32_IT_MACHHWS_XO1:
        case PPC32_IT_MACHHWSOE_XO1:
        case PPC32_IT_MACHHWSOERC_XO1:
        case PPC32_IT_MACHHWSRC_XO1:
        case PPC32_IT_MACHHWSU_XO1:
        case PPC32_IT_MACHHWSUOE_XO1:
        case PPC32_IT_MACHHWSUOERC_XO1:
        case PPC32_IT_MACHHWSURC_XO1:
        case PPC32_IT_MACHHWU_XO1:
        case PPC32_IT_MACHHWUOE_XO1:
        case PPC32_IT_MACHHWUOERC_XO1:
        case PPC32_IT_MACHHWURC_XO1:
        case PPC32_IT_MACLHW_XO1:
        case PPC32_IT_MACLHWOE_XO1:
        case PPC32_IT_MACLHWOERC_XO1:
        case PPC32_IT_MACLHWRC_XO1:
        case PPC32_IT_MACLHWS_XO1:
        case PPC32_IT_MACLHWSOE_XO1:
        case PPC32_IT_MACLHWSOERC_XO1:
        case PPC32_IT_MACLHWSRC_XO1:
        case PPC32_IT_MACLHWSU_XO1:
        case PPC32_IT_MACLHWSUOE_XO1:
        case PPC32_IT_MACLHWSUOERC_XO1:
        case PPC32_IT_MACLHWSURC_XO1:
        case PPC32_IT_MACLHWU_XO1:
        case PPC32_IT_MACLHWUOE_XO1:
        case PPC32_IT_MACLHWUOERC_XO1:
        case PPC32_IT_MACLHWURC_XO1:
        case PPC32_IT_MULLW_XO1:
        case PPC32_IT_MULLWOE_XO1:
        case PPC32_IT_MULLWOERC_XO1:
        case PPC32_IT_MULLWRC_XO1:
        case PPC32_IT_NMACCHW_XO1:
        case PPC32_IT_NMACCHWOE_XO1:
        case PPC32_IT_NMACCHWOERC_XO1:
        case PPC32_IT_NMACCHWRC_XO1:
        case PPC32_IT_NMACCHWS_XO1:
        case PPC32_IT_NMACCHWSOE_XO1:
        case PPC32_IT_NMACCHWSOERC_XO1:
        case PPC32_IT_NMACCHWSRC_XO1:
        case PPC32_IT_NMACHHW_XO1:
        case PPC32_IT_NMACHHWOE_XO1:
        case PPC32_IT_NMACHHWOERC_XO1:
        case PPC32_IT_NMACHHWRC_XO1:
        case PPC32_IT_NMACHHWS_XO1:
        case PPC32_IT_NMACHHWSOE_XO1:
        case PPC32_IT_NMACHHWSOERC_XO1:
        case PPC32_IT_NMACHHWSRC_XO1:
        case PPC32_IT_NMACLHW_XO1:
        case PPC32_IT_NMACLHWOE_XO1:
        case PPC32_IT_NMACLHWOERC_XO1:
        case PPC32_IT_NMACLHWRC_XO1:
        case PPC32_IT_NMACLHWS_XO1:
        case PPC32_IT_NMACLHWSOE_XO1:
        case PPC32_IT_NMACLHWSOERC_XO1:
        case PPC32_IT_NMACLHWSRC_XO1:
        case PPC32_IT_SUBF_XO1:
        case PPC32_IT_SUBFC_XO1:
        case PPC32_IT_SUBFCOE_XO1:
        case PPC32_IT_SUBFCOERC_XO1:
        case PPC32_IT_SUBFCRC_XO1:
        case PPC32_IT_SUBFE_XO1:
        case PPC32_IT_SUBFEOE_XO1:
        case PPC32_IT_SUBFEOERC_XO1:
        case PPC32_IT_SUBFERC_XO1:
        case PPC32_IT_SUBFOE_XO1:
        case PPC32_IT_SUBFOERC_XO1:
        case PPC32_IT_SUBFRC_XO1:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_MULHW_XO2:
        case PPC32_IT_MULHWRC_XO2:
        case PPC32_IT_MULHWU_XO2:
        case PPC32_IT_MULHWURC_XO2:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_ADDG6S_XO3:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_ADDME_XO4:
        case PPC32_IT_ADDMEOE_XO4:
        case PPC32_IT_ADDMEOERC_XO4:
        case PPC32_IT_ADDMERC_XO4:
        case PPC32_IT_ADDZE_XO4:
        case PPC32_IT_ADDZEOE_XO4:
        case PPC32_IT_ADDZEOERC_XO4:
        case PPC32_IT_ADDZERC_XO4:
        case PPC32_IT_NEG_XO4:
        case PPC32_IT_NEGOE_XO4:
        case PPC32_IT_NEGOERC_XO4:
        case PPC32_IT_NEGRC_XO4:
        case PPC32_IT_SUBFME_XO4:
        case PPC32_IT_SUBFMEOE_XO4:
        case PPC32_IT_SUBFMEOERC_XO4:
        case PPC32_IT_SUBFMERC_XO4:
        case PPC32_IT_SUBFZE_XO4:
        case PPC32_IT_SUBFZEOE_XO4:
        case PPC32_IT_SUBFZEOERC_XO4:
        case PPC32_IT_SUBFZERC_XO4:
            info->RA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->RT = VECINDEX(info->instruction,25,21,0); // 25:21
            break;

        case PPC32_IT_DTSTDC_Z22_1:
        case PPC32_IT_DTSTDG_Z22_1:
            info->BF = VECINDEX(info->instruction,25,23,0); // 25:23
            info->DCM = VECINDEX(info->instruction,15,10,0); // 15:10
            info->FRA = VECINDEX(info->instruction,20,16,0); // 20:16
            break;

        case PPC32_IT_DTSTDCQ_Z22_2:
        case PPC32_IT_DTSTDGQ_Z22_2:
            info->BF = VECINDEX(info->instruction,25,23,0); // 25:23
            info->DCM = VECINDEX(info->instruction,15,10,0); // 15:10
            info->FRAp = VECINDEX(info->instruction,20,16,0); // 20:16
            break;

        case PPC32_IT_DSCLI_Z22_5:
        case PPC32_IT_DSCLIRC_Z22_5:
        case PPC32_IT_DSCRI_Z22_5:
        case PPC32_IT_DSCRIRC_Z22_5:
            info->FRA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->FRT = VECINDEX(info->instruction,25,21,0); // 25:21
            info->SH = VECINDEX(info->instruction,15,10,0); // 15:10
            break;

        case PPC32_IT_DSCLIQ_Z22_6:
        case PPC32_IT_DSCLIQRC_Z22_6:
        case PPC32_IT_DSCRIQ_Z22_6:
        case PPC32_IT_DSCRIQRC_Z22_6:
            info->FRAp = VECINDEX(info->instruction,20,16,0); // 20:16
            info->FRTp = VECINDEX(info->instruction,25,21,0); // 25:21
            info->SH = VECINDEX(info->instruction,15,10,0); // 15:10
            break;

        case PPC32_IT_DQUAI_Z23_1:
        case PPC32_IT_DQUAIRC_Z23_1:
            info->FRB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->FRT = VECINDEX(info->instruction,25,21,0); // 25:21
            info->RMC = VECINDEX(info->instruction,10,9,0); // 10:9
            info->TE = VECINDEX(info->instruction,20,16,0); // 20:16
            info->TE = SEXTEND(info->TE,4);
            break;

        case PPC32_IT_DQUAIQ_Z23_2:
        case PPC32_IT_DQUAIQRC_Z23_2:
            info->FRBp = VECINDEX(info->instruction,15,11,0); // 15:11
            info->FRTp = VECINDEX(info->instruction,25,21,0); // 25:21
            info->RMC = VECINDEX(info->instruction,10,9,0); // 10:9
            info->TE = VECINDEX(info->instruction,20,16,0); // 20:16
            info->TE = SEXTEND(info->TE,4);
            break;

        case PPC32_IT_DQUA_Z23_3:
        case PPC32_IT_DQUAQ_Z23_3:
        case PPC32_IT_DQUAQRC_Z23_3:
        case PPC32_IT_DQUARC_Z23_3:
        case PPC32_IT_DRRND_Z23_3:
        case PPC32_IT_DRRNDQ_Z23_3:
        case PPC32_IT_DRRNDQRC_Z23_3:
        case PPC32_IT_DRRNDRC_Z23_3:
            info->FRA = VECINDEX(info->instruction,20,16,0); // 20:16
            info->FRB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->FRT = VECINDEX(info->instruction,25,21,0); // 25:21
            info->RMC = VECINDEX(info->instruction,10,9,0); // 10:9
            break;

        case PPC32_IT_DRINTN_Z23_6:
        case PPC32_IT_DRINTNRC_Z23_6:
        case PPC32_IT_DRINTX_Z23_6:
        case PPC32_IT_DRINTXRC_Z23_6:
            info->FRB = VECINDEX(info->instruction,15,11,0); // 15:11
            info->FRT = VECINDEX(info->instruction,25,21,0); // 25:21
            info->R = VECINDEX(info->instruction,16,16,0); // 16
            info->RMC = VECINDEX(info->instruction,10,9,0); // 10:9
            break;

        case PPC32_IT_DRINTNQ_Z23_7:
        case PPC32_IT_DRINTNQRC_Z23_7:
        case PPC32_IT_DRINTXQ_Z23_7:
        case PPC32_IT_DRINTXQRC_Z23_7:
            info->FRBp = VECINDEX(info->instruction,15,11,0); // 15:11
            info->FRTp = VECINDEX(info->instruction,25,21,0); // 25:21
            info->R = VECINDEX(info->instruction,16,16,0); // 16
            info->RMC = VECINDEX(info->instruction,10,9,0); // 10:9
            break;

        case PPC32_IT_INSTR16:
        case PPC32_IT_INSTR32:
        case PPC32_IT_LAST:
            break;
    }
    return;
}

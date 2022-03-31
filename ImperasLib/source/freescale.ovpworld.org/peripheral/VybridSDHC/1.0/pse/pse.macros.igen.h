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


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                             Version 20211118.0
//
////////////////////////////////////////////////////////////////////////////////

#ifndef PSE_MACROS_IGEN_H
#define PSE_MACROS_IGEN_H               

// Before including this file in the application, define the indicated macros
// to fix the base address of each slave port.

// Set the macro 'BPORT1' to the base of port 'bport1'
#ifndef BPORT1
#error BPORT1 is undefined. It needs to be set to the port base address
#endif


#define BPORT1_AB_POFFSET               0x0
#define BPORT1_AB_DSADDR_POFFSET        0x0
#define BPORT1_AB_DSADDR                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DSADDR_POFFSET)
#define BPORT1_AB_DSADDR_DSADDR         (0x3fffffff << 2)
#define BPORT1_AB_DSADDR_DSADDR_GET(_v)  ((_v >> 2) & 0x3fffffff)

#define BPORT1_AB_BLKATTR_POFFSET       0x4
#define BPORT1_AB_BLKATTR               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BLKATTR_POFFSET)
#define BPORT1_AB_BLKATTR_BLKCNT        (0xffff << 16)
#define BPORT1_AB_BLKATTR_BLKCNT_GET(_v)  ((_v >> 16) & 0xffff)
#define BPORT1_AB_BLKATTR_BLKSIZE       0x1fff
#define BPORT1_AB_BLKATTR_BLKSIZE_GET(_v)  (_v & 0x1fff)

#define BPORT1_AB_CMDARG_POFFSET        0x8
#define BPORT1_AB_CMDARG                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CMDARG_POFFSET)
#define BPORT1_AB_CMDARG_CMDARG         0xffffffff
#define BPORT1_AB_CMDARG_CMDARG_GET(_v)  (_v & 0xffffffff)

#define BPORT1_AB_XFERTYP_POFFSET       0xc
#define BPORT1_AB_XFERTYP               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_XFERTYP_POFFSET)
#define BPORT1_AB_XFERTYP_AC12EN        (0x1 << 2)
#define BPORT1_AB_XFERTYP_AC12EN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_XFERTYP_BCEN          (0x1 << 1)
#define BPORT1_AB_XFERTYP_BCEN_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_XFERTYP_CCCEN         (0x1 << 19)
#define BPORT1_AB_XFERTYP_CCCEN_GET(_v)  ((_v >> 19) & 0x1)
#define BPORT1_AB_XFERTYP_CICEN         (0x1 << 20)
#define BPORT1_AB_XFERTYP_CICEN_GET(_v)  ((_v >> 20) & 0x1)
#define BPORT1_AB_XFERTYP_CMDINX        (0x3f << 24)
#define BPORT1_AB_XFERTYP_CMDINX_GET(_v)  ((_v >> 24) & 0x3f)
#define BPORT1_AB_XFERTYP_CMDTYP        (0x3 << 22)
#define BPORT1_AB_XFERTYP_CMDTYP_GET(_v)  ((_v >> 22) & 0x3)
#define BPORT1_AB_XFERTYP_DMAEN         0x1
#define BPORT1_AB_XFERTYP_DMAEN_GET(_v)  (_v & 0x1)
#define BPORT1_AB_XFERTYP_DPSEL         (0x1 << 21)
#define BPORT1_AB_XFERTYP_DPSEL_GET(_v)  ((_v >> 21) & 0x1)
#define BPORT1_AB_XFERTYP_DTDSEL        (0x1 << 4)
#define BPORT1_AB_XFERTYP_DTDSEL_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_XFERTYP_MSBSEL        (0x1 << 5)
#define BPORT1_AB_XFERTYP_MSBSEL_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_XFERTYP_RSPTYP        (0x3 << 16)
#define BPORT1_AB_XFERTYP_RSPTYP_GET(_v)  ((_v >> 16) & 0x3)

#define BPORT1_AB_CMDRSP0_POFFSET       0x10
#define BPORT1_AB_CMDRSP0               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CMDRSP0_POFFSET)
#define BPORT1_AB_CMDRSP0_CMDRSP0       0xffffffff
#define BPORT1_AB_CMDRSP0_CMDRSP0_GET(_v)  (_v & 0xffffffff)

#define BPORT1_AB_CMDRSP1_POFFSET       0x14
#define BPORT1_AB_CMDRSP1               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CMDRSP1_POFFSET)
#define BPORT1_AB_CMDRSP1_CMDRSP1       0xffffffff
#define BPORT1_AB_CMDRSP1_CMDRSP1_GET(_v)  (_v & 0xffffffff)

#define BPORT1_AB_CMDRSP2_POFFSET       0x18
#define BPORT1_AB_CMDRSP2               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CMDRSP2_POFFSET)
#define BPORT1_AB_CMDRSP2_CMDRSP2       0xffffffff
#define BPORT1_AB_CMDRSP2_CMDRSP2_GET(_v)  (_v & 0xffffffff)

#define BPORT1_AB_CMDRSP3_POFFSET       0x1c
#define BPORT1_AB_CMDRSP3               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CMDRSP3_POFFSET)
#define BPORT1_AB_CMDRSP3_CMDRSP3       0xffffffff
#define BPORT1_AB_CMDRSP3_CMDRSP3_GET(_v)  (_v & 0xffffffff)

#define BPORT1_AB_DATPORT_POFFSET       0x20
#define BPORT1_AB_DATPORT               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DATPORT_POFFSET)
#define BPORT1_AB_DATPORT_DATCONT       0xffffffff
#define BPORT1_AB_DATPORT_DATCONT_GET(_v)  (_v & 0xffffffff)

#define BPORT1_AB_PRSSTAT_POFFSET       0x24
#define BPORT1_AB_PRSSTAT               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PRSSTAT_POFFSET)
#define BPORT1_AB_PRSSTAT_BREN          (0x1 << 11)
#define BPORT1_AB_PRSSTAT_BREN_GET(_v)  ((_v >> 11) & 0x1)
#define BPORT1_AB_PRSSTAT_BWEN          (0x1 << 10)
#define BPORT1_AB_PRSSTAT_BWEN_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_PRSSTAT_CDIHB         (0x1 << 1)
#define BPORT1_AB_PRSSTAT_CDIHB_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_PRSSTAT_CDPL          (0x1 << 18)
#define BPORT1_AB_PRSSTAT_CDPL_GET(_v)  ((_v >> 18) & 0x1)
#define BPORT1_AB_PRSSTAT_CIHB          0x1
#define BPORT1_AB_PRSSTAT_CIHB_GET(_v)  (_v & 0x1)
#define BPORT1_AB_PRSSTAT_CINS          (0x1 << 16)
#define BPORT1_AB_PRSSTAT_CINS_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_PRSSTAT_CLSL          (0x1 << 23)
#define BPORT1_AB_PRSSTAT_CLSL_GET(_v)  ((_v >> 23) & 0x1)
#define BPORT1_AB_PRSSTAT_DLA           (0x1 << 2)
#define BPORT1_AB_PRSSTAT_DLA_GET(_v)   ((_v >> 2) & 0x1)
#define BPORT1_AB_PRSSTAT_DLSL          (0xff << 24)
#define BPORT1_AB_PRSSTAT_DLSL_GET(_v)  ((_v >> 24) & 0xff)
#define BPORT1_AB_PRSSTAT_HCKOFF        (0x1 << 5)
#define BPORT1_AB_PRSSTAT_HCKOFF_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_PRSSTAT_IPGOFF        (0x1 << 4)
#define BPORT1_AB_PRSSTAT_IPGOFF_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_PRSSTAT_PEROFF        (0x1 << 6)
#define BPORT1_AB_PRSSTAT_PEROFF_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_PRSSTAT_RTA           (0x1 << 9)
#define BPORT1_AB_PRSSTAT_RTA_GET(_v)   ((_v >> 9) & 0x1)
#define BPORT1_AB_PRSSTAT_SDOFF         (0x1 << 7)
#define BPORT1_AB_PRSSTAT_SDOFF_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_PRSSTAT_SDSTB         (0x1 << 3)
#define BPORT1_AB_PRSSTAT_SDSTB_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_PRSSTAT_WPSPL         (0x1 << 19)
#define BPORT1_AB_PRSSTAT_WPSPL_GET(_v)  ((_v >> 19) & 0x1)
#define BPORT1_AB_PRSSTAT_WTA           (0x1 << 8)
#define BPORT1_AB_PRSSTAT_WTA_GET(_v)   ((_v >> 8) & 0x1)

#define BPORT1_AB_PROCTL_POFFSET        0x28
#define BPORT1_AB_PROCTL                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PROCTL_POFFSET)
#define BPORT1_AB_PROCTL_CDSS           (0x1 << 7)
#define BPORT1_AB_PROCTL_CDSS_GET(_v)   ((_v >> 7) & 0x1)
#define BPORT1_AB_PROCTL_CDTL           (0x1 << 6)
#define BPORT1_AB_PROCTL_CDTL_GET(_v)   ((_v >> 6) & 0x1)
#define BPORT1_AB_PROCTL_CREQ           (0x1 << 17)
#define BPORT1_AB_PROCTL_CREQ_GET(_v)   ((_v >> 17) & 0x1)
#define BPORT1_AB_PROCTL_D3CD           (0x1 << 3)
#define BPORT1_AB_PROCTL_D3CD_GET(_v)   ((_v >> 3) & 0x1)
#define BPORT1_AB_PROCTL_DMAS           (0x3 << 8)
#define BPORT1_AB_PROCTL_DMAS_GET(_v)   ((_v >> 8) & 0x3)
#define BPORT1_AB_PROCTL_DTW            (0x3 << 1)
#define BPORT1_AB_PROCTL_DTW_GET(_v)    ((_v >> 1) & 0x3)
#define BPORT1_AB_PROCTL_EMODE          (0x3 << 4)
#define BPORT1_AB_PROCTL_EMODE_GET(_v)  ((_v >> 4) & 0x3)
#define BPORT1_AB_PROCTL_IABG           (0x1 << 19)
#define BPORT1_AB_PROCTL_IABG_GET(_v)   ((_v >> 19) & 0x1)
#define BPORT1_AB_PROCTL_LCTL           0x1
#define BPORT1_AB_PROCTL_LCTL_GET(_v)   (_v & 0x1)
#define BPORT1_AB_PROCTL_RWCTL          (0x1 << 18)
#define BPORT1_AB_PROCTL_RWCTL_GET(_v)  ((_v >> 18) & 0x1)
#define BPORT1_AB_PROCTL_SABGREQ        (0x1 << 16)
#define BPORT1_AB_PROCTL_SABGREQ_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_PROCTL_WECINS         (0x1 << 25)
#define BPORT1_AB_PROCTL_WECINS_GET(_v)  ((_v >> 25) & 0x1)
#define BPORT1_AB_PROCTL_WECINT         (0x1 << 24)
#define BPORT1_AB_PROCTL_WECINT_GET(_v)  ((_v >> 24) & 0x1)
#define BPORT1_AB_PROCTL_WECRM          (0x1 << 26)
#define BPORT1_AB_PROCTL_WECRM_GET(_v)  ((_v >> 26) & 0x1)

#define BPORT1_AB_SYSCTL_POFFSET        0x2c
#define BPORT1_AB_SYSCTL                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SYSCTL_POFFSET)
#define BPORT1_AB_SYSCTL_DTOCV          (0xf << 16)
#define BPORT1_AB_SYSCTL_DTOCV_GET(_v)  ((_v >> 16) & 0xf)
#define BPORT1_AB_SYSCTL_DVS            (0xf << 4)
#define BPORT1_AB_SYSCTL_DVS_GET(_v)    ((_v >> 4) & 0xf)
#define BPORT1_AB_SYSCTL_HCKEN          (0x1 << 1)
#define BPORT1_AB_SYSCTL_HCKEN_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_SYSCTL_INITA          (0x1 << 27)
#define BPORT1_AB_SYSCTL_INITA_GET(_v)  ((_v >> 27) & 0x1)
#define BPORT1_AB_SYSCTL_IPGEN          0x1
#define BPORT1_AB_SYSCTL_IPGEN_GET(_v)  (_v & 0x1)
#define BPORT1_AB_SYSCTL_PEREN          (0x1 << 2)
#define BPORT1_AB_SYSCTL_PEREN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_SYSCTL_RSTA           (0x1 << 24)
#define BPORT1_AB_SYSCTL_RSTA_GET(_v)   ((_v >> 24) & 0x1)
#define BPORT1_AB_SYSCTL_RSTC           (0x1 << 25)
#define BPORT1_AB_SYSCTL_RSTC_GET(_v)   ((_v >> 25) & 0x1)
#define BPORT1_AB_SYSCTL_RSTD           (0x1 << 26)
#define BPORT1_AB_SYSCTL_RSTD_GET(_v)   ((_v >> 26) & 0x1)
#define BPORT1_AB_SYSCTL_SDCLKEN        (0x1 << 3)
#define BPORT1_AB_SYSCTL_SDCLKEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_SYSCTL_SDCLKFS        (0xff << 8)
#define BPORT1_AB_SYSCTL_SDCLKFS_GET(_v)  ((_v >> 8) & 0xff)

#define BPORT1_AB_IRQSTAT_POFFSET       0x30
#define BPORT1_AB_IRQSTAT               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IRQSTAT_POFFSET)
#define BPORT1_AB_IRQSTAT_AC12E         (0x1 << 24)
#define BPORT1_AB_IRQSTAT_AC12E_GET(_v)  ((_v >> 24) & 0x1)
#define BPORT1_AB_IRQSTAT_BGE           (0x1 << 2)
#define BPORT1_AB_IRQSTAT_BGE_GET(_v)   ((_v >> 2) & 0x1)
#define BPORT1_AB_IRQSTAT_BRR           (0x1 << 5)
#define BPORT1_AB_IRQSTAT_BRR_GET(_v)   ((_v >> 5) & 0x1)
#define BPORT1_AB_IRQSTAT_BWR           (0x1 << 4)
#define BPORT1_AB_IRQSTAT_BWR_GET(_v)   ((_v >> 4) & 0x1)
#define BPORT1_AB_IRQSTAT_CC            0x1
#define BPORT1_AB_IRQSTAT_CC_GET(_v)    (_v & 0x1)
#define BPORT1_AB_IRQSTAT_CCE           (0x1 << 17)
#define BPORT1_AB_IRQSTAT_CCE_GET(_v)   ((_v >> 17) & 0x1)
#define BPORT1_AB_IRQSTAT_CEBE          (0x1 << 18)
#define BPORT1_AB_IRQSTAT_CEBE_GET(_v)  ((_v >> 18) & 0x1)
#define BPORT1_AB_IRQSTAT_CIE           (0x1 << 19)
#define BPORT1_AB_IRQSTAT_CIE_GET(_v)   ((_v >> 19) & 0x1)
#define BPORT1_AB_IRQSTAT_CINS          (0x1 << 6)
#define BPORT1_AB_IRQSTAT_CINS_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_IRQSTAT_CINT          (0x1 << 8)
#define BPORT1_AB_IRQSTAT_CINT_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_IRQSTAT_CRM           (0x1 << 7)
#define BPORT1_AB_IRQSTAT_CRM_GET(_v)   ((_v >> 7) & 0x1)
#define BPORT1_AB_IRQSTAT_CTOE          (0x1 << 16)
#define BPORT1_AB_IRQSTAT_CTOE_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_IRQSTAT_DCE           (0x1 << 21)
#define BPORT1_AB_IRQSTAT_DCE_GET(_v)   ((_v >> 21) & 0x1)
#define BPORT1_AB_IRQSTAT_DEBE          (0x1 << 22)
#define BPORT1_AB_IRQSTAT_DEBE_GET(_v)  ((_v >> 22) & 0x1)
#define BPORT1_AB_IRQSTAT_DINT          (0x1 << 3)
#define BPORT1_AB_IRQSTAT_DINT_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_IRQSTAT_DMAE          (0x1 << 28)
#define BPORT1_AB_IRQSTAT_DMAE_GET(_v)  ((_v >> 28) & 0x1)
#define BPORT1_AB_IRQSTAT_DTOE          (0x1 << 20)
#define BPORT1_AB_IRQSTAT_DTOE_GET(_v)  ((_v >> 20) & 0x1)
#define BPORT1_AB_IRQSTAT_TC            (0x1 << 1)
#define BPORT1_AB_IRQSTAT_TC_GET(_v)    ((_v >> 1) & 0x1)

#define BPORT1_AB_IRQSTATEN_POFFSET     0x34
#define BPORT1_AB_IRQSTATEN             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IRQSTATEN_POFFSET)
#define BPORT1_AB_IRQSTATEN_AC12ESEN    (0x1 << 24)
#define BPORT1_AB_IRQSTATEN_AC12ESEN_GET(_v)  ((_v >> 24) & 0x1)
#define BPORT1_AB_IRQSTATEN_BGESEN      (0x1 << 2)
#define BPORT1_AB_IRQSTATEN_BGESEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_IRQSTATEN_BRRSEN      (0x1 << 5)
#define BPORT1_AB_IRQSTATEN_BRRSEN_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_IRQSTATEN_BWRSEN      (0x1 << 4)
#define BPORT1_AB_IRQSTATEN_BWRSEN_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_IRQSTATEN_CCESEN      (0x1 << 17)
#define BPORT1_AB_IRQSTATEN_CCESEN_GET(_v)  ((_v >> 17) & 0x1)
#define BPORT1_AB_IRQSTATEN_CCSEN       0x1
#define BPORT1_AB_IRQSTATEN_CCSEN_GET(_v)  (_v & 0x1)
#define BPORT1_AB_IRQSTATEN_CEBESEN     (0x1 << 18)
#define BPORT1_AB_IRQSTATEN_CEBESEN_GET(_v)  ((_v >> 18) & 0x1)
#define BPORT1_AB_IRQSTATEN_CIESEN      (0x1 << 19)
#define BPORT1_AB_IRQSTATEN_CIESEN_GET(_v)  ((_v >> 19) & 0x1)
#define BPORT1_AB_IRQSTATEN_CINSEN      (0x1 << 6)
#define BPORT1_AB_IRQSTATEN_CINSEN_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_IRQSTATEN_CINTSEN     (0x1 << 8)
#define BPORT1_AB_IRQSTATEN_CINTSEN_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_IRQSTATEN_CRMSEN      (0x1 << 7)
#define BPORT1_AB_IRQSTATEN_CRMSEN_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_IRQSTATEN_CTOESEN     (0x1 << 16)
#define BPORT1_AB_IRQSTATEN_CTOESEN_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_IRQSTATEN_DCESEN      (0x1 << 21)
#define BPORT1_AB_IRQSTATEN_DCESEN_GET(_v)  ((_v >> 21) & 0x1)
#define BPORT1_AB_IRQSTATEN_DEBESEN     (0x1 << 22)
#define BPORT1_AB_IRQSTATEN_DEBESEN_GET(_v)  ((_v >> 22) & 0x1)
#define BPORT1_AB_IRQSTATEN_DINTSEN     (0x1 << 3)
#define BPORT1_AB_IRQSTATEN_DINTSEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_IRQSTATEN_DMAESEN     (0x1 << 28)
#define BPORT1_AB_IRQSTATEN_DMAESEN_GET(_v)  ((_v >> 28) & 0x1)
#define BPORT1_AB_IRQSTATEN_DTOESEN     (0x1 << 20)
#define BPORT1_AB_IRQSTATEN_DTOESEN_GET(_v)  ((_v >> 20) & 0x1)
#define BPORT1_AB_IRQSTATEN_TCSEN       (0x1 << 1)
#define BPORT1_AB_IRQSTATEN_TCSEN_GET(_v)  ((_v >> 1) & 0x1)

#define BPORT1_AB_IRQSIGEN_POFFSET      0x38
#define BPORT1_AB_IRQSIGEN              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IRQSIGEN_POFFSET)
#define BPORT1_AB_IRQSIGEN_AC12EIEN     (0x1 << 24)
#define BPORT1_AB_IRQSIGEN_AC12EIEN_GET(_v)  ((_v >> 24) & 0x1)
#define BPORT1_AB_IRQSIGEN_BGEIEN       (0x1 << 2)
#define BPORT1_AB_IRQSIGEN_BGEIEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_IRQSIGEN_BRRIEN       (0x1 << 5)
#define BPORT1_AB_IRQSIGEN_BRRIEN_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_IRQSIGEN_BWRIEN       (0x1 << 4)
#define BPORT1_AB_IRQSIGEN_BWRIEN_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_IRQSIGEN_CCEIEN       (0x1 << 17)
#define BPORT1_AB_IRQSIGEN_CCEIEN_GET(_v)  ((_v >> 17) & 0x1)
#define BPORT1_AB_IRQSIGEN_CCIEN        0x1
#define BPORT1_AB_IRQSIGEN_CCIEN_GET(_v)  (_v & 0x1)
#define BPORT1_AB_IRQSIGEN_CEBEIEN      (0x1 << 18)
#define BPORT1_AB_IRQSIGEN_CEBEIEN_GET(_v)  ((_v >> 18) & 0x1)
#define BPORT1_AB_IRQSIGEN_CIEIEN       (0x1 << 19)
#define BPORT1_AB_IRQSIGEN_CIEIEN_GET(_v)  ((_v >> 19) & 0x1)
#define BPORT1_AB_IRQSIGEN_CINSIEN      (0x1 << 6)
#define BPORT1_AB_IRQSIGEN_CINSIEN_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_IRQSIGEN_CINTIEN      (0x1 << 8)
#define BPORT1_AB_IRQSIGEN_CINTIEN_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_IRQSIGEN_CRMIEN       (0x1 << 7)
#define BPORT1_AB_IRQSIGEN_CRMIEN_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_IRQSIGEN_CTOEIEN      (0x1 << 16)
#define BPORT1_AB_IRQSIGEN_CTOEIEN_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_IRQSIGEN_DCEIEN       (0x1 << 21)
#define BPORT1_AB_IRQSIGEN_DCEIEN_GET(_v)  ((_v >> 21) & 0x1)
#define BPORT1_AB_IRQSIGEN_DEBEIEN      (0x1 << 22)
#define BPORT1_AB_IRQSIGEN_DEBEIEN_GET(_v)  ((_v >> 22) & 0x1)
#define BPORT1_AB_IRQSIGEN_DINTIEN      (0x1 << 3)
#define BPORT1_AB_IRQSIGEN_DINTIEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_IRQSIGEN_DMAEIEN      (0x1 << 28)
#define BPORT1_AB_IRQSIGEN_DMAEIEN_GET(_v)  ((_v >> 28) & 0x1)
#define BPORT1_AB_IRQSIGEN_DTOEIEN      (0x1 << 20)
#define BPORT1_AB_IRQSIGEN_DTOEIEN_GET(_v)  ((_v >> 20) & 0x1)
#define BPORT1_AB_IRQSIGEN_TCIEN        (0x1 << 1)
#define BPORT1_AB_IRQSIGEN_TCIEN_GET(_v)  ((_v >> 1) & 0x1)

#define BPORT1_AB_AC12ERR_POFFSET       0x3c
#define BPORT1_AB_AC12ERR               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AC12ERR_POFFSET)
#define BPORT1_AB_AC12ERR_AC12CE        (0x1 << 3)
#define BPORT1_AB_AC12ERR_AC12CE_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_AC12ERR_AC12EBE       (0x1 << 2)
#define BPORT1_AB_AC12ERR_AC12EBE_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_AC12ERR_AC12IE        (0x1 << 4)
#define BPORT1_AB_AC12ERR_AC12IE_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_AC12ERR_AC12NE        0x1
#define BPORT1_AB_AC12ERR_AC12NE_GET(_v)  (_v & 0x1)
#define BPORT1_AB_AC12ERR_AC12TOE       (0x1 << 1)
#define BPORT1_AB_AC12ERR_AC12TOE_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_AC12ERR_CNIBAC12E     (0x1 << 7)
#define BPORT1_AB_AC12ERR_CNIBAC12E_GET(_v)  ((_v >> 7) & 0x1)

#define BPORT1_AB_HTCAPBLT_POFFSET      0x40
#define BPORT1_AB_HTCAPBLT              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HTCAPBLT_POFFSET)
#define BPORT1_AB_HTCAPBLT_ADMAS        (0x1 << 20)
#define BPORT1_AB_HTCAPBLT_ADMAS_GET(_v)  ((_v >> 20) & 0x1)
#define BPORT1_AB_HTCAPBLT_DMAS         (0x1 << 22)
#define BPORT1_AB_HTCAPBLT_DMAS_GET(_v)  ((_v >> 22) & 0x1)
#define BPORT1_AB_HTCAPBLT_HSS          (0x1 << 21)
#define BPORT1_AB_HTCAPBLT_HSS_GET(_v)  ((_v >> 21) & 0x1)
#define BPORT1_AB_HTCAPBLT_MBL          (0x7 << 16)
#define BPORT1_AB_HTCAPBLT_MBL_GET(_v)  ((_v >> 16) & 0x7)
#define BPORT1_AB_HTCAPBLT_SRS          (0x1 << 23)
#define BPORT1_AB_HTCAPBLT_SRS_GET(_v)  ((_v >> 23) & 0x1)
#define BPORT1_AB_HTCAPBLT_VS33         (0x1 << 24)
#define BPORT1_AB_HTCAPBLT_VS33_GET(_v)  ((_v >> 24) & 0x1)

#define BPORT1_AB_WML_POFFSET           0x44
#define BPORT1_AB_WML                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WML_POFFSET)
#define BPORT1_AB_WML_RDWML             0xff
#define BPORT1_AB_WML_RDWML_GET(_v)     (_v & 0xff)
#define BPORT1_AB_WML_RDBRSTLEN         (0x1f << 8)
#define BPORT1_AB_WML_RDBRSTLEN_GET(_v)  ((_v >> 8) & 0x1f)
#define BPORT1_AB_WML_WRWML             (0xff << 16)
#define BPORT1_AB_WML_WRWML_GET(_v)     ((_v >> 16) & 0xff)
#define BPORT1_AB_WML_WRBRSTLEN         (0x1f << 24)
#define BPORT1_AB_WML_WRBRSTLEN_GET(_v)  ((_v >> 24) & 0x1f)

#define BPORT1_AB_FEVT_POFFSET          0x50
#define BPORT1_AB_FEVT                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FEVT_POFFSET)
#define BPORT1_AB_FEVT_AC12CE           (0x1 << 2)
#define BPORT1_AB_FEVT_AC12CE_GET(_v)   ((_v >> 2) & 0x1)
#define BPORT1_AB_FEVT_AC12E            (0x1 << 24)
#define BPORT1_AB_FEVT_AC12E_GET(_v)    ((_v >> 24) & 0x1)
#define BPORT1_AB_FEVT_AC12EBE          (0x1 << 3)
#define BPORT1_AB_FEVT_AC12EBE_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_FEVT_AC12IE           (0x1 << 4)
#define BPORT1_AB_FEVT_AC12IE_GET(_v)   ((_v >> 4) & 0x1)
#define BPORT1_AB_FEVT_AC12NE           0x1
#define BPORT1_AB_FEVT_AC12NE_GET(_v)   (_v & 0x1)
#define BPORT1_AB_FEVT_AC12TOE          (0x1 << 1)
#define BPORT1_AB_FEVT_AC12TOE_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_FEVT_CCE              (0x1 << 17)
#define BPORT1_AB_FEVT_CCE_GET(_v)      ((_v >> 17) & 0x1)
#define BPORT1_AB_FEVT_CEBE             (0x1 << 18)
#define BPORT1_AB_FEVT_CEBE_GET(_v)     ((_v >> 18) & 0x1)
#define BPORT1_AB_FEVT_CIE              (0x1 << 19)
#define BPORT1_AB_FEVT_CIE_GET(_v)      ((_v >> 19) & 0x1)
#define BPORT1_AB_FEVT_CINT             (0x1 << 31)
#define BPORT1_AB_FEVT_CINT_GET(_v)     ((_v >> 31) & 0x1)
#define BPORT1_AB_FEVT_CNIBAC12E        (0x1 << 7)
#define BPORT1_AB_FEVT_CNIBAC12E_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_FEVT_CTOE             (0x1 << 16)
#define BPORT1_AB_FEVT_CTOE_GET(_v)     ((_v >> 16) & 0x1)
#define BPORT1_AB_FEVT_DCE              (0x1 << 21)
#define BPORT1_AB_FEVT_DCE_GET(_v)      ((_v >> 21) & 0x1)
#define BPORT1_AB_FEVT_DEBE             (0x1 << 22)
#define BPORT1_AB_FEVT_DEBE_GET(_v)     ((_v >> 22) & 0x1)
#define BPORT1_AB_FEVT_DMAE             (0x1 << 28)
#define BPORT1_AB_FEVT_DMAE_GET(_v)     ((_v >> 28) & 0x1)
#define BPORT1_AB_FEVT_DTOE             (0x1 << 20)
#define BPORT1_AB_FEVT_DTOE_GET(_v)     ((_v >> 20) & 0x1)

#define BPORT1_AB_ADMAES_POFFSET        0x54
#define BPORT1_AB_ADMAES                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ADMAES_POFFSET)
#define BPORT1_AB_ADMAES_ADMADCE        (0x1 << 3)
#define BPORT1_AB_ADMAES_ADMADCE_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_ADMAES_ADMAES         0x3
#define BPORT1_AB_ADMAES_ADMAES_GET(_v)  (_v & 0x3)
#define BPORT1_AB_ADMAES_ADMALME        (0x1 << 2)
#define BPORT1_AB_ADMAES_ADMALME_GET(_v)  ((_v >> 2) & 0x1)

#define BPORT1_AB_ADSADDR_POFFSET       0x58
#define BPORT1_AB_ADSADDR               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ADSADDR_POFFSET)
#define BPORT1_AB_ADSADDR_ADSADDR       (0x3fffffff << 2)
#define BPORT1_AB_ADSADDR_ADSADDR_GET(_v)  ((_v >> 2) & 0x3fffffff)

#define BPORT1_AB_VENDOR_POFFSET        0xc0
#define BPORT1_AB_VENDOR                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_VENDOR_POFFSET)
#define BPORT1_AB_VENDOR_EXBLKNU        (0x1 << 1)
#define BPORT1_AB_VENDOR_EXBLKNU_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_VENDOR_INTSTVAL       (0xff << 16)
#define BPORT1_AB_VENDOR_INTSTVAL_GET(_v)  ((_v >> 16) & 0xff)

#define BPORT1_AB_MMCBOOT_POFFSET       0xc4
#define BPORT1_AB_MMCBOOT               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MMCBOOT_POFFSET)
#define BPORT1_AB_MMCBOOT_AUTOSABGEN    (0x1 << 7)
#define BPORT1_AB_MMCBOOT_AUTOSABGEN_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_MMCBOOT_BOOTACK       (0x1 << 4)
#define BPORT1_AB_MMCBOOT_BOOTACK_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_MMCBOOT_BOOTBLKCNT    (0xffff << 16)
#define BPORT1_AB_MMCBOOT_BOOTBLKCNT_GET(_v)  ((_v >> 16) & 0xffff)
#define BPORT1_AB_MMCBOOT_BOOTEN        (0x1 << 6)
#define BPORT1_AB_MMCBOOT_BOOTEN_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_MMCBOOT_BOOTMODE      (0x1 << 5)
#define BPORT1_AB_MMCBOOT_BOOTMODE_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_MMCBOOT_DTOCVACK      0xf
#define BPORT1_AB_MMCBOOT_DTOCVACK_GET(_v)  (_v & 0xf)

#define BPORT1_AB_HOSTVER_POFFSET       0xfc
#define BPORT1_AB_HOSTVER               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HOSTVER_POFFSET)
#define BPORT1_AB_HOSTVER_SVN           0xff
#define BPORT1_AB_HOSTVER_SVN_GET(_v)   (_v & 0xff)
#define BPORT1_AB_HOSTVER_VVN           (0xff << 8)
#define BPORT1_AB_HOSTVER_VVN_GET(_v)   ((_v >> 8) & 0xff)


#endif

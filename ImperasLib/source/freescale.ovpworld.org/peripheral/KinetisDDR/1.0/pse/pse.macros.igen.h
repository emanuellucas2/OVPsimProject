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
#define BPORT1_AB_CR00_POFFSET          0x0
#define BPORT1_AB_CR00                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR00_POFFSET)
#define BPORT1_AB_CR00_DDRCLS           (0xf << 8)
#define BPORT1_AB_CR00_DDRCLS_GET(_v)   ((_v >> 8) & 0xf)
#define BPORT1_AB_CR00_START            0x1
#define BPORT1_AB_CR00_START_GET(_v)    (_v & 0x1)
#define BPORT1_AB_CR00_VERSION          (0xffff << 16)
#define BPORT1_AB_CR00_VERSION_GET(_v)  ((_v >> 16) & 0xffff)

#define BPORT1_AB_CR01_POFFSET          0x4
#define BPORT1_AB_CR01                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR01_POFFSET)
#define BPORT1_AB_CR01_CSMAX            (0x3 << 16)
#define BPORT1_AB_CR01_CSMAX_GET(_v)    ((_v >> 16) & 0x3)
#define BPORT1_AB_CR01_MAXCOL           (0xf << 8)
#define BPORT1_AB_CR01_MAXCOL_GET(_v)   ((_v >> 8) & 0xf)
#define BPORT1_AB_CR01_MAXROW           0x1f
#define BPORT1_AB_CR01_MAXROW_GET(_v)   (_v & 0x1f)

#define BPORT1_AB_CR02_POFFSET          0x8
#define BPORT1_AB_CR02                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR02_POFFSET)
#define BPORT1_AB_CR02_INITAREF         (0xf << 24)
#define BPORT1_AB_CR02_INITAREF_GET(_v)  ((_v >> 24) & 0xf)
#define BPORT1_AB_CR02_TINIT            0xffffff
#define BPORT1_AB_CR02_TINIT_GET(_v)    (_v & 0xffffff)

#define BPORT1_AB_CR03_POFFSET          0xc
#define BPORT1_AB_CR03                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR03_POFFSET)
#define BPORT1_AB_CR03_LATGATE          (0xf << 8)
#define BPORT1_AB_CR03_LATGATE_GET(_v)  ((_v >> 8) & 0xf)
#define BPORT1_AB_CR03_LATLIN           0xf
#define BPORT1_AB_CR03_LATLIN_GET(_v)   (_v & 0xf)
#define BPORT1_AB_CR03_TCCD             (0x1f << 24)
#define BPORT1_AB_CR03_TCCD_GET(_v)     ((_v >> 24) & 0x1f)
#define BPORT1_AB_CR03_WRLAT            (0xf << 16)
#define BPORT1_AB_CR03_WRLAT_GET(_v)    ((_v >> 16) & 0xf)

#define BPORT1_AB_CR04_POFFSET          0x10
#define BPORT1_AB_CR04                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR04_POFFSET)
#define BPORT1_AB_CR04_TBINT            0x7
#define BPORT1_AB_CR04_TBINT_GET(_v)    (_v & 0x7)
#define BPORT1_AB_CR04_TRASMIN          (0xff << 24)
#define BPORT1_AB_CR04_TRASMIN_GET(_v)  ((_v >> 24) & 0xff)
#define BPORT1_AB_CR04_TRC              (0x3f << 16)
#define BPORT1_AB_CR04_TRC_GET(_v)      ((_v >> 16) & 0x3f)
#define BPORT1_AB_CR04_TRRD             (0x7 << 8)
#define BPORT1_AB_CR04_TRRD_GET(_v)     ((_v >> 8) & 0x7)

#define BPORT1_AB_CR05_POFFSET          0x14
#define BPORT1_AB_CR05                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR05_POFFSET)
#define BPORT1_AB_CR05_TMRD             (0x1f << 24)
#define BPORT1_AB_CR05_TMRD_GET(_v)     ((_v >> 24) & 0x1f)
#define BPORT1_AB_CR05_TRP              (0xf << 8)
#define BPORT1_AB_CR05_TRP_GET(_v)      ((_v >> 8) & 0xf)
#define BPORT1_AB_CR05_TRTP             (0x7 << 16)
#define BPORT1_AB_CR05_TRTP_GET(_v)     ((_v >> 16) & 0x7)
#define BPORT1_AB_CR05_TWTR             0xf
#define BPORT1_AB_CR05_TWTR_GET(_v)     (_v & 0xf)

#define BPORT1_AB_CR06_POFFSET          0x18
#define BPORT1_AB_CR06                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR06_POFFSET)
#define BPORT1_AB_CR06_INTWBR           (0x1 << 24)
#define BPORT1_AB_CR06_INTWBR_GET(_v)   ((_v >> 24) & 0x1)
#define BPORT1_AB_CR06_TMOD             0xff
#define BPORT1_AB_CR06_TMOD_GET(_v)     (_v & 0xff)
#define BPORT1_AB_CR06_TRASMAX          (0xffff << 8)
#define BPORT1_AB_CR06_TRASMAX_GET(_v)  ((_v >> 8) & 0xffff)

#define BPORT1_AB_CR07_POFFSET          0x1c
#define BPORT1_AB_CR07                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR07_POFFSET)
#define BPORT1_AB_CR07_AP               (0x1 << 16)
#define BPORT1_AB_CR07_AP_GET(_v)       ((_v >> 16) & 0x1)
#define BPORT1_AB_CR07_CCAPEN           (0x1 << 24)
#define BPORT1_AB_CR07_CCAPEN_GET(_v)   ((_v >> 24) & 0x1)
#define BPORT1_AB_CR07_CLKPW            0x7
#define BPORT1_AB_CR07_CLKPW_GET(_v)    (_v & 0x7)
#define BPORT1_AB_CR07_TCKESR           (0x1f << 8)
#define BPORT1_AB_CR07_TCKESR_GET(_v)   ((_v >> 8) & 0x1f)

#define BPORT1_AB_CR08_POFFSET          0x20
#define BPORT1_AB_CR08                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR08_POFFSET)
#define BPORT1_AB_CR08_TDAL             (0x1f << 24)
#define BPORT1_AB_CR08_TDAL_GET(_v)     ((_v >> 24) & 0x1f)
#define BPORT1_AB_CR08_TRAS             0x1
#define BPORT1_AB_CR08_TRAS_GET(_v)     (_v & 0x1)
#define BPORT1_AB_CR08_TRASDI           (0xff << 8)
#define BPORT1_AB_CR08_TRASDI_GET(_v)   ((_v >> 8) & 0xff)
#define BPORT1_AB_CR08_TWR              (0x1f << 16)
#define BPORT1_AB_CR08_TWR_GET(_v)      ((_v >> 16) & 0x1f)

#define BPORT1_AB_CR09_POFFSET          0x24
#define BPORT1_AB_CR09                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR09_POFFSET)
#define BPORT1_AB_CR09_BSTLEN           (0x7 << 24)
#define BPORT1_AB_CR09_BSTLEN_GET(_v)   ((_v >> 24) & 0x7)
#define BPORT1_AB_CR09_NOCMD            (0x1 << 16)
#define BPORT1_AB_CR09_NOCMD_GET(_v)    ((_v >> 16) & 0x1)
#define BPORT1_AB_CR09_TDLL             0xffff
#define BPORT1_AB_CR09_TDLL_GET(_v)     (_v & 0xffff)

#define BPORT1_AB_CR10_POFFSET          0x28
#define BPORT1_AB_CR10                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR10_POFFSET)
#define BPORT1_AB_CR10_TCPD             (0xffff << 8)
#define BPORT1_AB_CR10_TCPD_GET(_v)     ((_v >> 8) & 0xffff)
#define BPORT1_AB_CR10_TFAW             0x3f
#define BPORT1_AB_CR10_TFAW_GET(_v)     (_v & 0x3f)
#define BPORT1_AB_CR10_TRPAB            (0xf << 24)
#define BPORT1_AB_CR10_TRPAB_GET(_v)    ((_v >> 24) & 0xf)

#define BPORT1_AB_CR11_POFFSET          0x2c
#define BPORT1_AB_CR11                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR11_POFFSET)
#define BPORT1_AB_CR11_AREF             (0x1 << 8)
#define BPORT1_AB_CR11_AREF_GET(_v)     ((_v >> 8) & 0x1)
#define BPORT1_AB_CR11_AREFMODE         (0x1 << 16)
#define BPORT1_AB_CR11_AREFMODE_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_CR11_REGDIMM          0x1
#define BPORT1_AB_CR11_REGDIMM_GET(_v)  (_v & 0x1)
#define BPORT1_AB_CR11_TREFEN           (0x1 << 24)
#define BPORT1_AB_CR11_TREFEN_GET(_v)   ((_v >> 24) & 0x1)

#define BPORT1_AB_CR12_POFFSET          0x30
#define BPORT1_AB_CR12                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR12_POFFSET)
#define BPORT1_AB_CR12_TREF             (0x3fff << 16)
#define BPORT1_AB_CR12_TREF_GET(_v)     ((_v >> 16) & 0x3fff)
#define BPORT1_AB_CR12_TRFC             0x3ff
#define BPORT1_AB_CR12_TRFC_GET(_v)     (_v & 0x3ff)

#define BPORT1_AB_CR13_POFFSET          0x34
#define BPORT1_AB_CR13                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR13_POFFSET)
#define BPORT1_AB_CR13_PD               (0x1 << 16)
#define BPORT1_AB_CR13_PD_GET(_v)       ((_v >> 16) & 0x1)
#define BPORT1_AB_CR13_TREFINT          0x3fff
#define BPORT1_AB_CR13_TREFINT_GET(_v)  (_v & 0x3fff)

#define BPORT1_AB_CR14_POFFSET          0x38
#define BPORT1_AB_CR14                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR14_POFFSET)
#define BPORT1_AB_CR14_TPDEX            0xffff
#define BPORT1_AB_CR14_TPDEX_GET(_v)    (_v & 0xffff)
#define BPORT1_AB_CR14_TXSR             (0xffff << 16)
#define BPORT1_AB_CR14_TXSR_GET(_v)     ((_v >> 16) & 0xffff)

#define BPORT1_AB_CR15_POFFSET          0x3c
#define BPORT1_AB_CR15                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR15_POFFSET)
#define BPORT1_AB_CR15_PUREF            (0x1 << 24)
#define BPORT1_AB_CR15_PUREF_GET(_v)    ((_v >> 24) & 0x1)
#define BPORT1_AB_CR15_SREF             (0x1 << 16)
#define BPORT1_AB_CR15_SREF_GET(_v)     ((_v >> 16) & 0x1)
#define BPORT1_AB_CR15_TXSNR            0xffff
#define BPORT1_AB_CR15_TXSNR_GET(_v)    (_v & 0xffff)

#define BPORT1_AB_CR16_POFFSET          0x40
#define BPORT1_AB_CR16                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR16_POFFSET)
#define BPORT1_AB_CR16_CLKDLY           (0x7 << 8)
#define BPORT1_AB_CR16_CLKDLY_GET(_v)   ((_v >> 8) & 0x7)
#define BPORT1_AB_CR16_LPCTRL           (0x1f << 16)
#define BPORT1_AB_CR16_LPCTRL_GET(_v)   ((_v >> 16) & 0x1f)
#define BPORT1_AB_CR16_QKREF            0x1
#define BPORT1_AB_CR16_QKREF_GET(_v)    (_v & 0x1)

#define BPORT1_AB_CR17_POFFSET          0x44
#define BPORT1_AB_CR17                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR17_POFFSET)
#define BPORT1_AB_CR17_LPPDCNT          0xffff
#define BPORT1_AB_CR17_LPPDCNT_GET(_v)  (_v & 0xffff)
#define BPORT1_AB_CR17_LPRFCNT          (0xffff << 16)
#define BPORT1_AB_CR17_LPRFCNT_GET(_v)  ((_v >> 16) & 0xffff)

#define BPORT1_AB_CR18_POFFSET          0x48
#define BPORT1_AB_CR18                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR18_POFFSET)
#define BPORT1_AB_CR18_LPAUTO           (0x1f << 16)
#define BPORT1_AB_CR18_LPAUTO_GET(_v)   ((_v >> 16) & 0x1f)
#define BPORT1_AB_CR18_LPEXTCNT         0xffff
#define BPORT1_AB_CR18_LPEXTCNT_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_CR19_POFFSET          0x4c
#define BPORT1_AB_CR19                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR19_POFFSET)
#define BPORT1_AB_CR19_LPINTCNT         0xffff
#define BPORT1_AB_CR19_LPINTCNT_GET(_v)  (_v & 0xffff)
#define BPORT1_AB_CR19_LPRFHOLD         (0xffff << 16)
#define BPORT1_AB_CR19_LPRFHOLD_GET(_v)  ((_v >> 16) & 0xffff)

#define BPORT1_AB_CR20_POFFSET          0x50
#define BPORT1_AB_CR20                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR20_POFFSET)
#define BPORT1_AB_CR20_CKSRE            (0xf << 8)
#define BPORT1_AB_CR20_CKSRE_GET(_v)    ((_v >> 8) & 0xf)
#define BPORT1_AB_CR20_CKSRX            (0xf << 16)
#define BPORT1_AB_CR20_CKSRX_GET(_v)    ((_v >> 16) & 0xf)
#define BPORT1_AB_CR20_LPRE             0x3
#define BPORT1_AB_CR20_LPRE_GET(_v)     (_v & 0x3)
#define BPORT1_AB_CR20_WRMD             (0x1 << 24)
#define BPORT1_AB_CR20_WRMD_GET(_v)     ((_v >> 24) & 0x1)

#define BPORT1_AB_CR21_POFFSET          0x54
#define BPORT1_AB_CR21                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR21_POFFSET)
#define BPORT1_AB_CR21_MR0DAT0          0xffff
#define BPORT1_AB_CR21_MR0DAT0_GET(_v)  (_v & 0xffff)
#define BPORT1_AB_CR21_MR1DAT0          (0xffff << 16)
#define BPORT1_AB_CR21_MR1DAT0_GET(_v)  ((_v >> 16) & 0xffff)

#define BPORT1_AB_CR22_POFFSET          0x58
#define BPORT1_AB_CR22                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR22_POFFSET)
#define BPORT1_AB_CR22_MR2DATA0         0xffff
#define BPORT1_AB_CR22_MR2DATA0_GET(_v)  (_v & 0xffff)
#define BPORT1_AB_CR22_MR3DAT0          (0xffff << 16)
#define BPORT1_AB_CR22_MR3DAT0_GET(_v)  ((_v >> 16) & 0xffff)

#define BPORT1_AB_CR23_POFFSET          0x5c
#define BPORT1_AB_CR23                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR23_POFFSET)
#define BPORT1_AB_CR23_NOT_USED2        0xffff
#define BPORT1_AB_CR23_NOT_USED2_GET(_v)  (_v & 0xffff)
#define BPORT1_AB_CR23_NOT_USED         (0xffff << 16)
#define BPORT1_AB_CR23_NOT_USED_GET(_v)  ((_v >> 16) & 0xffff)

#define BPORT1_AB_CR24_POFFSET          0x60
#define BPORT1_AB_CR24                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR24_POFFSET)

#define BPORT1_AB_CR25_POFFSET          0x64
#define BPORT1_AB_CR25                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR25_POFFSET)
#define BPORT1_AB_CR25_ADDPINS          (0x7 << 8)
#define BPORT1_AB_CR25_ADDPINS_GET(_v)  ((_v >> 8) & 0x7)
#define BPORT1_AB_CR25_APREBIT          (0xf << 24)
#define BPORT1_AB_CR25_APREBIT_GET(_v)  ((_v >> 24) & 0xf)
#define BPORT1_AB_CR25_BNK8             0x1
#define BPORT1_AB_CR25_BNK8_GET(_v)     (_v & 0x1)
#define BPORT1_AB_CR25_COLSIZ           (0x7 << 16)
#define BPORT1_AB_CR25_COLSIZ_GET(_v)   ((_v >> 16) & 0x7)

#define BPORT1_AB_CR26_POFFSET          0x68
#define BPORT1_AB_CR26                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR26_POFFSET)
#define BPORT1_AB_CR26_ADDCOL           (0x1 << 16)
#define BPORT1_AB_CR26_ADDCOL_GET(_v)   ((_v >> 16) & 0x1)
#define BPORT1_AB_CR26_AGECNT           0xff
#define BPORT1_AB_CR26_AGECNT_GET(_v)   (_v & 0xff)
#define BPORT1_AB_CR26_BNKSPT           (0x1 << 24)
#define BPORT1_AB_CR26_BNKSPT_GET(_v)   ((_v >> 24) & 0x1)
#define BPORT1_AB_CR26_CMDAGE           (0xff << 8)
#define BPORT1_AB_CR26_CMDAGE_GET(_v)   ((_v >> 8) & 0xff)

#define BPORT1_AB_CR27_POFFSET          0x6c
#define BPORT1_AB_CR27                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR27_POFFSET)
#define BPORT1_AB_CR27_PLEN             0x1
#define BPORT1_AB_CR27_PLEN_GET(_v)     (_v & 0x1)
#define BPORT1_AB_CR27_PRIEN            (0x1 << 8)
#define BPORT1_AB_CR27_PRIEN_GET(_v)    ((_v >> 8) & 0x1)
#define BPORT1_AB_CR27_RWEN             (0x1 << 16)
#define BPORT1_AB_CR27_RWEN_GET(_v)     ((_v >> 16) & 0x1)
#define BPORT1_AB_CR27_SWPEN            (0x1 << 24)
#define BPORT1_AB_CR27_SWPEN_GET(_v)    ((_v >> 24) & 0x1)

#define BPORT1_AB_CR28_POFFSET          0x70
#define BPORT1_AB_CR28                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR28_POFFSET)
#define BPORT1_AB_CR28_BIGEND           (0x1 << 16)
#define BPORT1_AB_CR28_BIGEND_GET(_v)   ((_v >> 16) & 0x1)
#define BPORT1_AB_CR28_CMDLATR          (0x1 << 24)
#define BPORT1_AB_CR28_CMDLATR_GET(_v)  ((_v >> 24) & 0x1)
#define BPORT1_AB_CR28_CSMAP            0x1
#define BPORT1_AB_CR28_CSMAP_GET(_v)    (_v & 0x1)
#define BPORT1_AB_CR28_REDUC            (0x1 << 8)
#define BPORT1_AB_CR28_REDUC_GET(_v)    ((_v >> 8) & 0x1)

#define BPORT1_AB_CR29_POFFSET          0x74
#define BPORT1_AB_CR29                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR29_POFFSET)
#define BPORT1_AB_CR29_FSTWR            (0x1 << 8)
#define BPORT1_AB_CR29_FSTWR_GET(_v)    ((_v >> 8) & 0x1)
#define BPORT1_AB_CR29_QFULL            (0x3 << 16)
#define BPORT1_AB_CR29_QFULL_GET(_v)    ((_v >> 16) & 0x3)
#define BPORT1_AB_CR29_RESYNC           (0x1 << 24)
#define BPORT1_AB_CR29_RESYNC_GET(_v)   ((_v >> 24) & 0x1)
#define BPORT1_AB_CR29_WRLATR           0x1
#define BPORT1_AB_CR29_WRLATR_GET(_v)   (_v & 0x1)

#define BPORT1_AB_CR30_POFFSET          0x78
#define BPORT1_AB_CR30                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR30_POFFSET)
#define BPORT1_AB_CR30_INTACK           (0xff << 24)
#define BPORT1_AB_CR30_INTACK_GET(_v)   ((_v >> 24) & 0xff)
#define BPORT1_AB_CR30_INTSTAT          (0x1ff << 8)
#define BPORT1_AB_CR30_INTSTAT_GET(_v)  ((_v >> 8) & 0x1ff)
#define BPORT1_AB_CR30_RSYNCRF          0x1
#define BPORT1_AB_CR30_RSYNCRF_GET(_v)  (_v & 0x1)

#define BPORT1_AB_CR31_POFFSET          0x7c
#define BPORT1_AB_CR31                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR31_POFFSET)
#define BPORT1_AB_CR31_INTMASK          0x1ff
#define BPORT1_AB_CR31_INTMASK_GET(_v)  (_v & 0x1ff)

#define BPORT1_AB_CR32_POFFSET          0x80
#define BPORT1_AB_CR32                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR32_POFFSET)
#define BPORT1_AB_CR32_OORAD            0xffffffff
#define BPORT1_AB_CR32_OORAD_GET(_v)    (_v & 0xffffffff)

#define BPORT1_AB_CR33_POFFSET          0x84
#define BPORT1_AB_CR33                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR33_POFFSET)
#define BPORT1_AB_CR33_OORID            (0x3 << 24)
#define BPORT1_AB_CR33_OORID_GET(_v)    ((_v >> 24) & 0x3)
#define BPORT1_AB_CR33_OORLEN           0x3ff
#define BPORT1_AB_CR33_OORLEN_GET(_v)   (_v & 0x3ff)
#define BPORT1_AB_CR33_OORTYP           (0x3f << 16)
#define BPORT1_AB_CR33_OORTYP_GET(_v)   ((_v >> 16) & 0x3f)

#define BPORT1_AB_CR34_POFFSET          0x88
#define BPORT1_AB_CR34                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR34_POFFSET)
#define BPORT1_AB_CR34_ODTRDC           0x1
#define BPORT1_AB_CR34_ODTRDC_GET(_v)   (_v & 0x1)
#define BPORT1_AB_CR34_ODTWRCS          (0x1 << 8)
#define BPORT1_AB_CR34_ODTWRCS_GET(_v)  ((_v >> 8) & 0x1)

#define BPORT1_AB_CR35_POFFSET          0x8c
#define BPORT1_AB_CR35                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR35_POFFSET)
#define BPORT1_AB_CR35_R2WSMCS          0xf
#define BPORT1_AB_CR35_R2WSMCS_GET(_v)  (_v & 0xf)
#define BPORT1_AB_CR35_W2RSMCS          (0xf << 8)
#define BPORT1_AB_CR35_W2RSMCS_GET(_v)  ((_v >> 8) & 0xf)

#define BPORT1_AB_CR36_POFFSET          0x90
#define BPORT1_AB_CR36                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR36_POFFSET)
#define BPORT1_AB_CR36_NOT_USED2        0xffff
#define BPORT1_AB_CR36_NOT_USED2_GET(_v)  (_v & 0xffff)
#define BPORT1_AB_CR36_NOT_USED         (0xffff << 16)
#define BPORT1_AB_CR36_NOT_USED_GET(_v)  ((_v >> 16) & 0xffff)

#define BPORT1_AB_CR37_POFFSET          0x94
#define BPORT1_AB_CR37                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR37_POFFSET)
#define BPORT1_AB_CR37_R2RSAME          0x7
#define BPORT1_AB_CR37_R2RSAME_GET(_v)  (_v & 0x7)
#define BPORT1_AB_CR37_R2WSAME          (0x7 << 8)
#define BPORT1_AB_CR37_R2WSAME_GET(_v)  ((_v >> 8) & 0x7)
#define BPORT1_AB_CR37_W2RSAME          (0x7 << 16)
#define BPORT1_AB_CR37_W2RSAME_GET(_v)  ((_v >> 16) & 0x7)
#define BPORT1_AB_CR37_W2WSAME          (0x7 << 24)
#define BPORT1_AB_CR37_W2WSAME_GET(_v)  ((_v >> 24) & 0x7)

#define BPORT1_AB_CR38_POFFSET          0x98
#define BPORT1_AB_CR38                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR38_POFFSET)
#define BPORT1_AB_CR38_PDNCS            0x1f
#define BPORT1_AB_CR38_PDNCS_GET(_v)    (_v & 0x1f)
#define BPORT1_AB_CR38_PUPCS            (0x1f << 8)
#define BPORT1_AB_CR38_PUPCS_GET(_v)    ((_v >> 8) & 0x1f)
#define BPORT1_AB_CR38_PWRCNT           (0x7ff << 16)
#define BPORT1_AB_CR38_PWRCNT_GET(_v)   ((_v >> 16) & 0x7ff)

#define BPORT1_AB_CR39_POFFSET          0x9c
#define BPORT1_AB_CR39                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR39_POFFSET)
#define BPORT1_AB_CR39_P0RDCNT          0x7ff
#define BPORT1_AB_CR39_P0RDCNT_GET(_v)  (_v & 0x7ff)
#define BPORT1_AB_CR39_RP0              (0x3 << 16)
#define BPORT1_AB_CR39_RP0_GET(_v)      ((_v >> 16) & 0x3)
#define BPORT1_AB_CR39_WP0              (0x3 << 24)
#define BPORT1_AB_CR39_WP0_GET(_v)      ((_v >> 24) & 0x3)

#define BPORT1_AB_CR40_POFFSET          0xa0
#define BPORT1_AB_CR40                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR40_POFFSET)
#define BPORT1_AB_CR40_P0TYP            0x3
#define BPORT1_AB_CR40_P0TYP_GET(_v)    (_v & 0x3)
#define BPORT1_AB_CR40_P1WRCNT          (0x7ff << 8)
#define BPORT1_AB_CR40_P1WRCNT_GET(_v)  ((_v >> 8) & 0x7ff)

#define BPORT1_AB_CR41_POFFSET          0xa4
#define BPORT1_AB_CR41                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR41_POFFSET)
#define BPORT1_AB_CR41_P1RDCNT          0x7ff
#define BPORT1_AB_CR41_P1RDCNT_GET(_v)  (_v & 0x7ff)
#define BPORT1_AB_CR41_RP1              (0x3 << 16)
#define BPORT1_AB_CR41_RP1_GET(_v)      ((_v >> 16) & 0x3)
#define BPORT1_AB_CR41_WP1              (0x3 << 24)
#define BPORT1_AB_CR41_WP1_GET(_v)      ((_v >> 24) & 0x3)

#define BPORT1_AB_CR42_POFFSET          0xa8
#define BPORT1_AB_CR42                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR42_POFFSET)
#define BPORT1_AB_CR42_P1TYP            0x3
#define BPORT1_AB_CR42_P1TYP_GET(_v)    (_v & 0x3)
#define BPORT1_AB_CR42_P2WRCNT          (0x7ff << 8)
#define BPORT1_AB_CR42_P2WRCNT_GET(_v)  ((_v >> 8) & 0x7ff)

#define BPORT1_AB_CR43_POFFSET          0xac
#define BPORT1_AB_CR43                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR43_POFFSET)
#define BPORT1_AB_CR43_P2RDCNT          0x7ff
#define BPORT1_AB_CR43_P2RDCNT_GET(_v)  (_v & 0x7ff)
#define BPORT1_AB_CR43_RP2              (0x3 << 16)
#define BPORT1_AB_CR43_RP2_GET(_v)      ((_v >> 16) & 0x3)
#define BPORT1_AB_CR43_WP2              (0x3 << 24)
#define BPORT1_AB_CR43_WP2_GET(_v)      ((_v >> 24) & 0x3)

#define BPORT1_AB_CR44_POFFSET          0xb0
#define BPORT1_AB_CR44                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR44_POFFSET)
#define BPORT1_AB_CR44_P2TYP            0x3
#define BPORT1_AB_CR44_P2TYP_GET(_v)    (_v & 0x3)
#define BPORT1_AB_CR44_WRRERR           (0xf << 24)
#define BPORT1_AB_CR44_WRRERR_GET(_v)   ((_v >> 24) & 0xf)
#define BPORT1_AB_CR44_WRRLAT           (0x1 << 8)
#define BPORT1_AB_CR44_WRRLAT_GET(_v)   ((_v >> 8) & 0x1)
#define BPORT1_AB_CR44_WRRSHARE         (0x1 << 16)
#define BPORT1_AB_CR44_WRRSHARE_GET(_v)  ((_v >> 16) & 0x1)

#define BPORT1_AB_CR45_POFFSET          0xb4
#define BPORT1_AB_CR45                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR45_POFFSET)
#define BPORT1_AB_CR45_P0PRI0           0xf
#define BPORT1_AB_CR45_P0PRI0_GET(_v)   (_v & 0xf)
#define BPORT1_AB_CR45_P0PRI1           (0xf << 8)
#define BPORT1_AB_CR45_P0PRI1_GET(_v)   ((_v >> 8) & 0xf)
#define BPORT1_AB_CR45_P0PRI2           (0xf << 16)
#define BPORT1_AB_CR45_P0PRI2_GET(_v)   ((_v >> 16) & 0xf)
#define BPORT1_AB_CR45_P0PRI3           (0xf << 24)
#define BPORT1_AB_CR45_P0PRI3_GET(_v)   ((_v >> 24) & 0xf)

#define BPORT1_AB_CR46_POFFSET          0xb8
#define BPORT1_AB_CR46                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR46_POFFSET)
#define BPORT1_AB_CR46_P0ORD            0x3
#define BPORT1_AB_CR46_P0ORD_GET(_v)    (_v & 0x3)
#define BPORT1_AB_CR46_P0PRIRLX         (0x3ff << 8)
#define BPORT1_AB_CR46_P0PRIRLX_GET(_v)  ((_v >> 8) & 0x3ff)
#define BPORT1_AB_CR46_P1PRI0           (0xf << 24)
#define BPORT1_AB_CR46_P1PRI0_GET(_v)   ((_v >> 24) & 0xf)

#define BPORT1_AB_CR47_POFFSET          0xbc
#define BPORT1_AB_CR47                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR47_POFFSET)
#define BPORT1_AB_CR47_P1ORD            (0x3 << 24)
#define BPORT1_AB_CR47_P1ORD_GET(_v)    ((_v >> 24) & 0x3)
#define BPORT1_AB_CR47_P1PRI1           0xf
#define BPORT1_AB_CR47_P1PRI1_GET(_v)   (_v & 0xf)
#define BPORT1_AB_CR47_P1PRI2           (0xf << 8)
#define BPORT1_AB_CR47_P1PRI2_GET(_v)   ((_v >> 8) & 0xf)
#define BPORT1_AB_CR47_P1PRI3           (0xf << 16)
#define BPORT1_AB_CR47_P1PRI3_GET(_v)   ((_v >> 16) & 0xf)

#define BPORT1_AB_CR48_POFFSET          0xc0
#define BPORT1_AB_CR48                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR48_POFFSET)
#define BPORT1_AB_CR48_P1PRIRLX         0x3ff
#define BPORT1_AB_CR48_P1PRIRLX_GET(_v)  (_v & 0x3ff)
#define BPORT1_AB_CR48_P2PRI0           (0xf << 16)
#define BPORT1_AB_CR48_P2PRI0_GET(_v)   ((_v >> 16) & 0xf)
#define BPORT1_AB_CR48_P2PRI1           (0xf << 24)
#define BPORT1_AB_CR48_P2PRI1_GET(_v)   ((_v >> 24) & 0xf)

#define BPORT1_AB_CR49_POFFSET          0xc4
#define BPORT1_AB_CR49                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR49_POFFSET)
#define BPORT1_AB_CR49_P2ORD            (0x3 << 16)
#define BPORT1_AB_CR49_P2ORD_GET(_v)    ((_v >> 16) & 0x3)
#define BPORT1_AB_CR49_P2PRI2           0xf
#define BPORT1_AB_CR49_P2PRI2_GET(_v)   (_v & 0xf)
#define BPORT1_AB_CR49_P2PRI3           (0xf << 8)
#define BPORT1_AB_CR49_P2PRI3_GET(_v)   ((_v >> 8) & 0xf)

#define BPORT1_AB_CR50_POFFSET          0xc8
#define BPORT1_AB_CR50                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR50_POFFSET)
#define BPORT1_AB_CR50_CLKSTATUS        (0x1 << 16)
#define BPORT1_AB_CR50_CLKSTATUS_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_CR50_P2PRIRLX         0x3ff
#define BPORT1_AB_CR50_P2PRIRLX_GET(_v)  (_v & 0x3ff)

#define BPORT1_AB_CR51_POFFSET          0xcc
#define BPORT1_AB_CR51                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR51_POFFSET)
#define BPORT1_AB_CR51_DLLRADLY         (0xff << 16)
#define BPORT1_AB_CR51_DLLRADLY_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_AB_CR51_DLLRSTDLY        0xffff
#define BPORT1_AB_CR51_DLLRSTDLY_GET(_v)  (_v & 0xffff)
#define BPORT1_AB_CR51_PHYWRLAT         (0xf << 24)
#define BPORT1_AB_CR51_PHYWRLAT_GET(_v)  ((_v >> 24) & 0xf)

#define BPORT1_AB_CR52_POFFSET          0xd0
#define BPORT1_AB_CR52                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR52_POFFSET)
#define BPORT1_AB_CR52_PHYRDLAT         (0xf << 8)
#define BPORT1_AB_CR52_PHYRDLAT_GET(_v)  ((_v >> 8) & 0xf)
#define BPORT1_AB_CR52_PYWRLTBS         0xf
#define BPORT1_AB_CR52_PYWRLTBS_GET(_v)  (_v & 0xf)
#define BPORT1_AB_CR52_RDDATAEN         (0xf << 16)
#define BPORT1_AB_CR52_RDDATAEN_GET(_v)  ((_v >> 16) & 0xf)
#define BPORT1_AB_CR52_RDDTENBAS        (0xf << 24)
#define BPORT1_AB_CR52_RDDTENBAS_GET(_v)  ((_v >> 24) & 0xf)

#define BPORT1_AB_CR53_POFFSET          0xd4
#define BPORT1_AB_CR53                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR53_POFFSET)
#define BPORT1_AB_CR53_CLKDISCS         0x1
#define BPORT1_AB_CR53_CLKDISCS_GET(_v)  (_v & 0x1)
#define BPORT1_AB_CR53_CRTLUPDMN        (0xf << 8)
#define BPORT1_AB_CR53_CRTLUPDMN_GET(_v)  ((_v >> 8) & 0xf)
#define BPORT1_AB_CR53_CTRLUPDMX        (0x3fff << 16)
#define BPORT1_AB_CR53_CTRLUPDMX_GET(_v)  ((_v >> 16) & 0x3fff)

#define BPORT1_AB_CR54_POFFSET          0xd8
#define BPORT1_AB_CR54                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR54_POFFSET)
#define BPORT1_AB_CR54_PHYUPDTY0        0x3fff
#define BPORT1_AB_CR54_PHYUPDTY0_GET(_v)  (_v & 0x3fff)
#define BPORT1_AB_CR54_PHYUPDTY1        (0x3fff << 16)
#define BPORT1_AB_CR54_PHYUPDTY1_GET(_v)  ((_v >> 16) & 0x3fff)

#define BPORT1_AB_CR55_POFFSET          0xdc
#define BPORT1_AB_CR55                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR55_POFFSET)
#define BPORT1_AB_CR55_PHYUPDTY2        0x3fff
#define BPORT1_AB_CR55_PHYUPDTY2_GET(_v)  (_v & 0x3fff)
#define BPORT1_AB_CR55_PHYUPDTY3        (0x3fff << 16)
#define BPORT1_AB_CR55_PHYUPDTY3_GET(_v)  ((_v >> 16) & 0x3fff)

#define BPORT1_AB_CR56_POFFSET          0xe0
#define BPORT1_AB_CR56                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR56_POFFSET)
#define BPORT1_AB_CR56_PHYUPDRESP       0x3fff
#define BPORT1_AB_CR56_PHYUPDRESP_GET(_v)  (_v & 0x3fff)
#define BPORT1_AB_CR56_RDLATADJ         (0xf << 16)
#define BPORT1_AB_CR56_RDLATADJ_GET(_v)  ((_v >> 16) & 0xf)
#define BPORT1_AB_CR56_WRLATADJ         (0xf << 24)
#define BPORT1_AB_CR56_WRLATADJ_GET(_v)  ((_v >> 24) & 0xf)

#define BPORT1_AB_CR57_POFFSET          0xe4
#define BPORT1_AB_CR57                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR57_POFFSET)
#define BPORT1_AB_CR57_CLKDISDLY        (0x7 << 8)
#define BPORT1_AB_CR57_CLKDISDLY_GET(_v)  ((_v >> 8) & 0x7)
#define BPORT1_AB_CR57_CLKENDLY         (0xf << 16)
#define BPORT1_AB_CR57_CLKENDLY_GET(_v)  ((_v >> 16) & 0xf)
#define BPORT1_AB_CR57_CMDDLY           0xf
#define BPORT1_AB_CR57_CMDDLY_GET(_v)   (_v & 0xf)
#define BPORT1_AB_CR57_ODTALTEN         (0x1 << 24)
#define BPORT1_AB_CR57_ODTALTEN_GET(_v)  ((_v >> 24) & 0x1)

#define BPORT1_AB_CR58_POFFSET          0xe8
#define BPORT1_AB_CR58                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR58_POFFSET)
#define BPORT1_AB_CR58_NOT_USED2        0xffff
#define BPORT1_AB_CR58_NOT_USED2_GET(_v)  (_v & 0xffff)
#define BPORT1_AB_CR58_NOT_USED         (0xffff << 16)
#define BPORT1_AB_CR58_NOT_USED_GET(_v)  ((_v >> 16) & 0xffff)

#define BPORT1_AB_CR59_POFFSET          0xec
#define BPORT1_AB_CR59                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR59_POFFSET)
#define BPORT1_AB_CR59_NOT_USED2        0xffff
#define BPORT1_AB_CR59_NOT_USED2_GET(_v)  (_v & 0xffff)
#define BPORT1_AB_CR59_NOT_USED         (0xffff << 16)
#define BPORT1_AB_CR59_NOT_USED_GET(_v)  ((_v >> 16) & 0xffff)

#define BPORT1_AB_CR60_POFFSET          0xf0
#define BPORT1_AB_CR60                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR60_POFFSET)
#define BPORT1_AB_CR60_NOT_USED2        0xffff
#define BPORT1_AB_CR60_NOT_USED2_GET(_v)  (_v & 0xffff)
#define BPORT1_AB_CR60_NOT_USED         (0xffff << 16)
#define BPORT1_AB_CR60_NOT_USED_GET(_v)  ((_v >> 16) & 0xffff)

#define BPORT1_AB_CR61_POFFSET          0xf4
#define BPORT1_AB_CR61                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR61_POFFSET)
#define BPORT1_AB_CR61_NOT_USED2        0xffff
#define BPORT1_AB_CR61_NOT_USED2_GET(_v)  (_v & 0xffff)
#define BPORT1_AB_CR61_NOT_USED         (0xffff << 16)
#define BPORT1_AB_CR61_NOT_USED_GET(_v)  ((_v >> 16) & 0xffff)

#define BPORT1_AB_CR62_POFFSET          0xf8
#define BPORT1_AB_CR62                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR62_POFFSET)
#define BPORT1_AB_CR62_NOT_USED2        0xffff
#define BPORT1_AB_CR62_NOT_USED2_GET(_v)  (_v & 0xffff)
#define BPORT1_AB_CR62_NOT_USED         (0xffff << 16)
#define BPORT1_AB_CR62_NOT_USED_GET(_v)  ((_v >> 16) & 0xffff)

#define BPORT1_AB_CR63_POFFSET          0xfc
#define BPORT1_AB_CR63                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR63_POFFSET)
#define BPORT1_AB_CR63_NOT_USED2        0xffff
#define BPORT1_AB_CR63_NOT_USED2_GET(_v)  (_v & 0xffff)
#define BPORT1_AB_CR63_NOT_USED         (0xffff << 16)
#define BPORT1_AB_CR63_NOT_USED_GET(_v)  ((_v >> 16) & 0xffff)

#define BPORT1_AB_RCR_POFFSET           0x180
#define BPORT1_AB_RCR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RCR_POFFSET)
#define BPORT1_AB_RCR_RST               (0x1 << 30)
#define BPORT1_AB_RCR_RST_GET(_v)       ((_v >> 30) & 0x1)


#endif

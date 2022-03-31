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
#define BPORT1_AB_ID_POFFSET            0x0
#define BPORT1_AB_ID                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ID_POFFSET)
#define BPORT1_AB_ID_ID                 0x3f
#define BPORT1_AB_ID_ID_GET(_v)         (_v & 0x3f)
#define BPORT1_AB_ID_NID                (0x3f << 8)
#define BPORT1_AB_ID_NID_GET(_v)        ((_v >> 8) & 0x3f)
#define BPORT1_AB_ID_TAG                (0x1f << 16)
#define BPORT1_AB_ID_TAG_GET(_v)        ((_v >> 16) & 0x1f)
#define BPORT1_AB_ID_REVISION           (0xf << 21)
#define BPORT1_AB_ID_REVISION_GET(_v)   ((_v >> 21) & 0xf)
#define BPORT1_AB_ID_VERSION            (0xf << 25)
#define BPORT1_AB_ID_VERSION_GET(_v)    ((_v >> 25) & 0xf)
#define BPORT1_AB_ID_VERSIONID          (0x7 << 29)
#define BPORT1_AB_ID_VERSIONID_GET(_v)  ((_v >> 29) & 0x7)

#define BPORT1_AB_HWGENERAL_POFFSET     0x4
#define BPORT1_AB_HWGENERAL             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HWGENERAL_POFFSET)
#define BPORT1_AB_HWGENERAL_PHYM        (0x7 << 6)
#define BPORT1_AB_HWGENERAL_PHYM_GET(_v)  ((_v >> 6) & 0x7)
#define BPORT1_AB_HWGENERAL_SM          (0x3 << 9)
#define BPORT1_AB_HWGENERAL_SM_GET(_v)  ((_v >> 9) & 0x3)

#define BPORT1_AB_HWHOST_POFFSET        0x8
#define BPORT1_AB_HWHOST                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HWHOST_POFFSET)
#define BPORT1_AB_HWHOST_HC             0x1
#define BPORT1_AB_HWHOST_HC_GET(_v)     (_v & 0x1)
#define BPORT1_AB_HWHOST_NPORT          (0x7 << 1)
#define BPORT1_AB_HWHOST_NPORT_GET(_v)  ((_v >> 1) & 0x7)
#define BPORT1_AB_HWHOST_TTASY          (0xff << 16)
#define BPORT1_AB_HWHOST_TTASY_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_AB_HWHOST_TTPER          (0xff << 24)
#define BPORT1_AB_HWHOST_TTPER_GET(_v)  ((_v >> 24) & 0xff)

#define BPORT1_AB_HWDEVICE_POFFSET      0xc
#define BPORT1_AB_HWDEVICE              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HWDEVICE_POFFSET)
#define BPORT1_AB_HWDEVICE_DC           0x1
#define BPORT1_AB_HWDEVICE_DC_GET(_v)   (_v & 0x1)
#define BPORT1_AB_HWDEVICE_DEVEP        (0x1f << 1)
#define BPORT1_AB_HWDEVICE_DEVEP_GET(_v)  ((_v >> 1) & 0x1f)

#define BPORT1_AB_HWTXBUF_POFFSET       0x10
#define BPORT1_AB_HWTXBUF               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HWTXBUF_POFFSET)
#define BPORT1_AB_HWTXBUF_TXADD         (0xff << 8)
#define BPORT1_AB_HWTXBUF_TXADD_GET(_v)  ((_v >> 8) & 0xff)
#define BPORT1_AB_HWTXBUF_TXBURST       0xff
#define BPORT1_AB_HWTXBUF_TXBURST_GET(_v)  (_v & 0xff)
#define BPORT1_AB_HWTXBUF_TXCHANADD     (0xff << 16)
#define BPORT1_AB_HWTXBUF_TXCHANADD_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_AB_HWTXBUF_TXLC          (0x1 << 31)
#define BPORT1_AB_HWTXBUF_TXLC_GET(_v)  ((_v >> 31) & 0x1)

#define BPORT1_AB_HWRXBUF_POFFSET       0x14
#define BPORT1_AB_HWRXBUF               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HWRXBUF_POFFSET)
#define BPORT1_AB_HWRXBUF_RXADD         (0xff << 8)
#define BPORT1_AB_HWRXBUF_RXADD_GET(_v)  ((_v >> 8) & 0xff)
#define BPORT1_AB_HWRXBUF_RXBURST       0xff
#define BPORT1_AB_HWRXBUF_RXBURST_GET(_v)  (_v & 0xff)

#define BPORT1_AB_GPTIMER0LD_POFFSET    0x80
#define BPORT1_AB_GPTIMER0LD            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPTIMER0LD_POFFSET)
#define BPORT1_AB_GPTIMER0LD_GPTLD      0xffffff
#define BPORT1_AB_GPTIMER0LD_GPTLD_GET(_v)  (_v & 0xffffff)

#define BPORT1_AB_GPTIMER0CTL_POFFSET   0x84
#define BPORT1_AB_GPTIMER0CTL           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPTIMER0CTL_POFFSET)
#define BPORT1_AB_GPTIMER0CTL_GPTCNT    0xffffff
#define BPORT1_AB_GPTIMER0CTL_GPTCNT_GET(_v)  (_v & 0xffffff)
#define BPORT1_AB_GPTIMER0CTL_MODE      (0x1 << 24)
#define BPORT1_AB_GPTIMER0CTL_MODE_GET(_v)  ((_v >> 24) & 0x1)
#define BPORT1_AB_GPTIMER0CTL_RST       (0x1 << 30)
#define BPORT1_AB_GPTIMER0CTL_RST_GET(_v)  ((_v >> 30) & 0x1)
#define BPORT1_AB_GPTIMER0CTL_RUN       (0x1 << 31)
#define BPORT1_AB_GPTIMER0CTL_RUN_GET(_v)  ((_v >> 31) & 0x1)

#define BPORT1_AB_GPTIMER1LD_POFFSET    0x88
#define BPORT1_AB_GPTIMER1LD            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPTIMER1LD_POFFSET)
#define BPORT1_AB_GPTIMER1LD_GPTLD      0xffffff
#define BPORT1_AB_GPTIMER1LD_GPTLD_GET(_v)  (_v & 0xffffff)

#define BPORT1_AB_GPTIMER1CTL_POFFSET   0x8c
#define BPORT1_AB_GPTIMER1CTL           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPTIMER1CTL_POFFSET)
#define BPORT1_AB_GPTIMER1CTL_GPTCNT    0xffffff
#define BPORT1_AB_GPTIMER1CTL_GPTCNT_GET(_v)  (_v & 0xffffff)
#define BPORT1_AB_GPTIMER1CTL_MODE      (0x1 << 24)
#define BPORT1_AB_GPTIMER1CTL_MODE_GET(_v)  ((_v >> 24) & 0x1)
#define BPORT1_AB_GPTIMER1CTL_RST       (0x1 << 30)
#define BPORT1_AB_GPTIMER1CTL_RST_GET(_v)  ((_v >> 30) & 0x1)
#define BPORT1_AB_GPTIMER1CTL_RUN       (0x1 << 31)
#define BPORT1_AB_GPTIMER1CTL_RUN_GET(_v)  ((_v >> 31) & 0x1)

#define BPORT1_AB_SBUSCFG_POFFSET       0x90
#define BPORT1_AB_SBUSCFG               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SBUSCFG_POFFSET)
#define BPORT1_AB_SBUSCFG_BURSTMODE     0x7
#define BPORT1_AB_SBUSCFG_BURSTMODE_GET(_v)  (_v & 0x7)

#define BPORT1_AB_HCIVERSION_POFFSET    0x100
#define BPORT1_AB_HCIVERSION            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HCIVERSION_POFFSET)
#define BPORT1_AB_HCIVERSION_HCIVERSION  (0xffff << 16)
#define BPORT1_AB_HCIVERSION_HCIVERSION_GET(_v)  ((_v >> 16) & 0xffff)
#define BPORT1_AB_HCIVERSION_CAPLENGTH  0xff
#define BPORT1_AB_HCIVERSION_CAPLENGTH_GET(_v)  (_v & 0xff)

#define BPORT1_AB_HCSPARAMS_POFFSET     0x104
#define BPORT1_AB_HCSPARAMS             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HCSPARAMS_POFFSET)
#define BPORT1_AB_HCSPARAMS_N_CC        (0xf << 12)
#define BPORT1_AB_HCSPARAMS_N_CC_GET(_v)  ((_v >> 12) & 0xf)
#define BPORT1_AB_HCSPARAMS_N_PCC       (0xf << 8)
#define BPORT1_AB_HCSPARAMS_N_PCC_GET(_v)  ((_v >> 8) & 0xf)
#define BPORT1_AB_HCSPARAMS_N_PORTS     0xf
#define BPORT1_AB_HCSPARAMS_N_PORTS_GET(_v)  (_v & 0xf)
#define BPORT1_AB_HCSPARAMS_N_PTT       (0xf << 20)
#define BPORT1_AB_HCSPARAMS_N_PTT_GET(_v)  ((_v >> 20) & 0xf)
#define BPORT1_AB_HCSPARAMS_N_TT        (0xf << 24)
#define BPORT1_AB_HCSPARAMS_N_TT_GET(_v)  ((_v >> 24) & 0xf)
#define BPORT1_AB_HCSPARAMS_PI          (0x1 << 16)
#define BPORT1_AB_HCSPARAMS_PI_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_HCSPARAMS_PPC         (0x1 << 4)
#define BPORT1_AB_HCSPARAMS_PPC_GET(_v)  ((_v >> 4) & 0x1)

#define BPORT1_AB_HCCPARAMS_POFFSET     0x108
#define BPORT1_AB_HCCPARAMS             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HCCPARAMS_POFFSET)
#define BPORT1_AB_HCCPARAMS_ADC         0x1
#define BPORT1_AB_HCCPARAMS_ADC_GET(_v)  (_v & 0x1)
#define BPORT1_AB_HCCPARAMS_ASP         (0x1 << 2)
#define BPORT1_AB_HCCPARAMS_ASP_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_HCCPARAMS_EECP        (0xff << 8)
#define BPORT1_AB_HCCPARAMS_EECP_GET(_v)  ((_v >> 8) & 0xff)
#define BPORT1_AB_HCCPARAMS_IST         (0xf << 4)
#define BPORT1_AB_HCCPARAMS_IST_GET(_v)  ((_v >> 4) & 0xf)
#define BPORT1_AB_HCCPARAMS_PFL         (0x1 << 1)
#define BPORT1_AB_HCCPARAMS_PFL_GET(_v)  ((_v >> 1) & 0x1)

#define BPORT1_AB_DCIVERSION_POFFSET    0x120
#define BPORT1_AB_DCIVERSION            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DCIVERSION_POFFSET)
#define BPORT1_AB_DCIVERSION_DCIVERSION  0xffff
#define BPORT1_AB_DCIVERSION_DCIVERSION_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_DCCPARAMS_POFFSET     0x124
#define BPORT1_AB_DCCPARAMS             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DCCPARAMS_POFFSET)
#define BPORT1_AB_DCCPARAMS_DC          (0x1 << 7)
#define BPORT1_AB_DCCPARAMS_DC_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_DCCPARAMS_DEN         0x1f
#define BPORT1_AB_DCCPARAMS_DEN_GET(_v)  (_v & 0x1f)
#define BPORT1_AB_DCCPARAMS_HC          (0x1 << 8)
#define BPORT1_AB_DCCPARAMS_HC_GET(_v)  ((_v >> 8) & 0x1)

#define BPORT1_AB_USBCMD_POFFSET        0x140
#define BPORT1_AB_USBCMD                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USBCMD_POFFSET)
#define BPORT1_AB_USBCMD_ASE            (0x1 << 5)
#define BPORT1_AB_USBCMD_ASE_GET(_v)    ((_v >> 5) & 0x1)
#define BPORT1_AB_USBCMD_ASP            (0x3 << 8)
#define BPORT1_AB_USBCMD_ASP_GET(_v)    ((_v >> 8) & 0x3)
#define BPORT1_AB_USBCMD_ASPE           (0x1 << 11)
#define BPORT1_AB_USBCMD_ASPE_GET(_v)   ((_v >> 11) & 0x1)
#define BPORT1_AB_USBCMD_ATDTW          (0x1 << 14)
#define BPORT1_AB_USBCMD_ATDTW_GET(_v)  ((_v >> 14) & 0x1)
#define BPORT1_AB_USBCMD_FS             (0x3 << 2)
#define BPORT1_AB_USBCMD_FS_GET(_v)     ((_v >> 2) & 0x3)
#define BPORT1_AB_USBCMD_FS2            (0x1 << 15)
#define BPORT1_AB_USBCMD_FS2_GET(_v)    ((_v >> 15) & 0x1)
#define BPORT1_AB_USBCMD_IAA            (0x1 << 6)
#define BPORT1_AB_USBCMD_IAA_GET(_v)    ((_v >> 6) & 0x1)
#define BPORT1_AB_USBCMD_ITC            (0xff << 16)
#define BPORT1_AB_USBCMD_ITC_GET(_v)    ((_v >> 16) & 0xff)
#define BPORT1_AB_USBCMD_PSE            (0x1 << 4)
#define BPORT1_AB_USBCMD_PSE_GET(_v)    ((_v >> 4) & 0x1)
#define BPORT1_AB_USBCMD_RS             0x1
#define BPORT1_AB_USBCMD_RS_GET(_v)     (_v & 0x1)
#define BPORT1_AB_USBCMD_RST            (0x1 << 1)
#define BPORT1_AB_USBCMD_RST_GET(_v)    ((_v >> 1) & 0x1)
#define BPORT1_AB_USBCMD_SUTW           (0x1 << 13)
#define BPORT1_AB_USBCMD_SUTW_GET(_v)   ((_v >> 13) & 0x1)

#define BPORT1_AB_USBSTS_POFFSET        0x144
#define BPORT1_AB_USBSTS                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USBSTS_POFFSET)
#define BPORT1_AB_USBSTS_AAI            (0x1 << 5)
#define BPORT1_AB_USBSTS_AAI_GET(_v)    ((_v >> 5) & 0x1)
#define BPORT1_AB_USBSTS_AS             (0x1 << 15)
#define BPORT1_AB_USBSTS_AS_GET(_v)     ((_v >> 15) & 0x1)
#define BPORT1_AB_USBSTS_FRI            (0x1 << 3)
#define BPORT1_AB_USBSTS_FRI_GET(_v)    ((_v >> 3) & 0x1)
#define BPORT1_AB_USBSTS_HCH            (0x1 << 12)
#define BPORT1_AB_USBSTS_HCH_GET(_v)    ((_v >> 12) & 0x1)
#define BPORT1_AB_USBSTS_NAKI           (0x1 << 16)
#define BPORT1_AB_USBSTS_NAKI_GET(_v)   ((_v >> 16) & 0x1)
#define BPORT1_AB_USBSTS_PCI            (0x1 << 2)
#define BPORT1_AB_USBSTS_PCI_GET(_v)    ((_v >> 2) & 0x1)
#define BPORT1_AB_USBSTS_PS             (0x1 << 14)
#define BPORT1_AB_USBSTS_PS_GET(_v)     ((_v >> 14) & 0x1)
#define BPORT1_AB_USBSTS_RCL            (0x1 << 13)
#define BPORT1_AB_USBSTS_RCL_GET(_v)    ((_v >> 13) & 0x1)
#define BPORT1_AB_USBSTS_SEI            (0x1 << 4)
#define BPORT1_AB_USBSTS_SEI_GET(_v)    ((_v >> 4) & 0x1)
#define BPORT1_AB_USBSTS_SLI            (0x1 << 8)
#define BPORT1_AB_USBSTS_SLI_GET(_v)    ((_v >> 8) & 0x1)
#define BPORT1_AB_USBSTS_SRI            (0x1 << 7)
#define BPORT1_AB_USBSTS_SRI_GET(_v)    ((_v >> 7) & 0x1)
#define BPORT1_AB_USBSTS_TI0            (0x1 << 24)
#define BPORT1_AB_USBSTS_TI0_GET(_v)    ((_v >> 24) & 0x1)
#define BPORT1_AB_USBSTS_TI1            (0x1 << 25)
#define BPORT1_AB_USBSTS_TI1_GET(_v)    ((_v >> 25) & 0x1)
#define BPORT1_AB_USBSTS_UAI            (0x1 << 18)
#define BPORT1_AB_USBSTS_UAI_GET(_v)    ((_v >> 18) & 0x1)
#define BPORT1_AB_USBSTS_UEI            (0x1 << 1)
#define BPORT1_AB_USBSTS_UEI_GET(_v)    ((_v >> 1) & 0x1)
#define BPORT1_AB_USBSTS_UI             0x1
#define BPORT1_AB_USBSTS_UI_GET(_v)     (_v & 0x1)
#define BPORT1_AB_USBSTS_ULPII          (0x1 << 10)
#define BPORT1_AB_USBSTS_ULPII_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_USBSTS_UPI            (0x1 << 19)
#define BPORT1_AB_USBSTS_UPI_GET(_v)    ((_v >> 19) & 0x1)
#define BPORT1_AB_USBSTS_URI            (0x1 << 6)
#define BPORT1_AB_USBSTS_URI_GET(_v)    ((_v >> 6) & 0x1)

#define BPORT1_AB_USBINTR_POFFSET       0x148
#define BPORT1_AB_USBINTR               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USBINTR_POFFSET)
#define BPORT1_AB_USBINTR_AAE           (0x1 << 5)
#define BPORT1_AB_USBINTR_AAE_GET(_v)   ((_v >> 5) & 0x1)
#define BPORT1_AB_USBINTR_FRE           (0x1 << 3)
#define BPORT1_AB_USBINTR_FRE_GET(_v)   ((_v >> 3) & 0x1)
#define BPORT1_AB_USBINTR_NAKE          (0x1 << 16)
#define BPORT1_AB_USBINTR_NAKE_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_USBINTR_PCE           (0x1 << 2)
#define BPORT1_AB_USBINTR_PCE_GET(_v)   ((_v >> 2) & 0x1)
#define BPORT1_AB_USBINTR_SEE           (0x1 << 4)
#define BPORT1_AB_USBINTR_SEE_GET(_v)   ((_v >> 4) & 0x1)
#define BPORT1_AB_USBINTR_SLE           (0x1 << 8)
#define BPORT1_AB_USBINTR_SLE_GET(_v)   ((_v >> 8) & 0x1)
#define BPORT1_AB_USBINTR_SRE           (0x1 << 7)
#define BPORT1_AB_USBINTR_SRE_GET(_v)   ((_v >> 7) & 0x1)
#define BPORT1_AB_USBINTR_TIE0          (0x1 << 24)
#define BPORT1_AB_USBINTR_TIE0_GET(_v)  ((_v >> 24) & 0x1)
#define BPORT1_AB_USBINTR_TIE1          (0x1 << 25)
#define BPORT1_AB_USBINTR_TIE1_GET(_v)  ((_v >> 25) & 0x1)
#define BPORT1_AB_USBINTR_UAIE          (0x1 << 18)
#define BPORT1_AB_USBINTR_UAIE_GET(_v)  ((_v >> 18) & 0x1)
#define BPORT1_AB_USBINTR_UE            0x1
#define BPORT1_AB_USBINTR_UE_GET(_v)    (_v & 0x1)
#define BPORT1_AB_USBINTR_UEE           (0x1 << 1)
#define BPORT1_AB_USBINTR_UEE_GET(_v)   ((_v >> 1) & 0x1)
#define BPORT1_AB_USBINTR_ULPIE         (0x1 << 10)
#define BPORT1_AB_USBINTR_ULPIE_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_USBINTR_UPIE          (0x1 << 19)
#define BPORT1_AB_USBINTR_UPIE_GET(_v)  ((_v >> 19) & 0x1)
#define BPORT1_AB_USBINTR_URE           (0x1 << 6)
#define BPORT1_AB_USBINTR_URE_GET(_v)   ((_v >> 6) & 0x1)

#define BPORT1_AB_FRINDEX_POFFSET       0x14c
#define BPORT1_AB_FRINDEX               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FRINDEX_POFFSET)
#define BPORT1_AB_FRINDEX_FRINDEX       0x3fff
#define BPORT1_AB_FRINDEX_FRINDEX_GET(_v)  (_v & 0x3fff)

#define BPORT1_AB_DEVICEADDR_POFFSET    0x154
#define BPORT1_AB_DEVICEADDR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DEVICEADDR_POFFSET)
#define BPORT1_AB_DEVICEADDR_USBADR     (0x7f << 25)
#define BPORT1_AB_DEVICEADDR_USBADR_GET(_v)  ((_v >> 25) & 0x7f)
#define BPORT1_AB_DEVICEADDR_USBADRA    (0x1 << 24)
#define BPORT1_AB_DEVICEADDR_USBADRA_GET(_v)  ((_v >> 24) & 0x1)

#define BPORT1_AB_ASYNCLISTADDR_POFFSET  0x158
#define BPORT1_AB_ASYNCLISTADDR         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ASYNCLISTADDR_POFFSET)
#define BPORT1_AB_ASYNCLISTADDR_ASYBASE  (0x7ffffff << 5)
#define BPORT1_AB_ASYNCLISTADDR_ASYBASE_GET(_v)  ((_v >> 5) & 0x7ffffff)

#define BPORT1_AB_TTCTRL_POFFSET        0x15c
#define BPORT1_AB_TTCTRL                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TTCTRL_POFFSET)
#define BPORT1_AB_TTCTRL_TTHA           (0x7f << 24)
#define BPORT1_AB_TTCTRL_TTHA_GET(_v)   ((_v >> 24) & 0x7f)

#define BPORT1_AB_BURSTSIZE_POFFSET     0x160
#define BPORT1_AB_BURSTSIZE             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BURSTSIZE_POFFSET)
#define BPORT1_AB_BURSTSIZE_RXPBURST    0xff
#define BPORT1_AB_BURSTSIZE_RXPBURST_GET(_v)  (_v & 0xff)
#define BPORT1_AB_BURSTSIZE_TXPBURST    (0xff << 8)
#define BPORT1_AB_BURSTSIZE_TXPBURST_GET(_v)  ((_v >> 8) & 0xff)

#define BPORT1_AB_TXFILLTUNING_POFFSET  0x164
#define BPORT1_AB_TXFILLTUNING          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TXFILLTUNING_POFFSET)
#define BPORT1_AB_TXFILLTUNING_TXFIFOTHRES  (0x3f << 16)
#define BPORT1_AB_TXFILLTUNING_TXFIFOTHRES_GET(_v)  ((_v >> 16) & 0x3f)
#define BPORT1_AB_TXFILLTUNING_TXSCHHEALTH  (0x1f << 8)
#define BPORT1_AB_TXFILLTUNING_TXSCHHEALTH_GET(_v)  ((_v >> 8) & 0x1f)
#define BPORT1_AB_TXFILLTUNING_TXSCHOH  0x7f
#define BPORT1_AB_TXFILLTUNING_TXSCHOH_GET(_v)  (_v & 0x7f)

#define BPORT1_AB_ULPI_VIEWPORT_POFFSET  0x170
#define BPORT1_AB_ULPI_VIEWPORT         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ULPI_VIEWPORT_POFFSET)
#define BPORT1_AB_ULPI_VIEWPORT_ULPI_ADDR  (0xff << 16)
#define BPORT1_AB_ULPI_VIEWPORT_ULPI_ADDR_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_AB_ULPI_VIEWPORT_ULPI_DATRD  (0xff << 8)
#define BPORT1_AB_ULPI_VIEWPORT_ULPI_DATRD_GET(_v)  ((_v >> 8) & 0xff)
#define BPORT1_AB_ULPI_VIEWPORT_ULPI_DATWR  0xff
#define BPORT1_AB_ULPI_VIEWPORT_ULPI_DATWR_GET(_v)  (_v & 0xff)
#define BPORT1_AB_ULPI_VIEWPORT_ULPI_PORT  (0x7 << 24)
#define BPORT1_AB_ULPI_VIEWPORT_ULPI_PORT_GET(_v)  ((_v >> 24) & 0x7)
#define BPORT1_AB_ULPI_VIEWPORT_ULPI_RUN  (0x1 << 30)
#define BPORT1_AB_ULPI_VIEWPORT_ULPI_RUN_GET(_v)  ((_v >> 30) & 0x1)
#define BPORT1_AB_ULPI_VIEWPORT_ULPI_RW  (0x1 << 29)
#define BPORT1_AB_ULPI_VIEWPORT_ULPI_RW_GET(_v)  ((_v >> 29) & 0x1)
#define BPORT1_AB_ULPI_VIEWPORT_ULPI_SS  (0x1 << 27)
#define BPORT1_AB_ULPI_VIEWPORT_ULPI_SS_GET(_v)  ((_v >> 27) & 0x1)
#define BPORT1_AB_ULPI_VIEWPORT_ULPI_WU  (0x1 << 31)
#define BPORT1_AB_ULPI_VIEWPORT_ULPI_WU_GET(_v)  ((_v >> 31) & 0x1)

#define BPORT1_AB_ENDPTNAK_POFFSET      0x178
#define BPORT1_AB_ENDPTNAK              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTNAK_POFFSET)
#define BPORT1_AB_ENDPTNAK_EPTNE        (0xf << 16)
#define BPORT1_AB_ENDPTNAK_EPTNE_GET(_v)  ((_v >> 16) & 0xf)
#define BPORT1_AB_ENDPTNAK_EPRNE        0xf
#define BPORT1_AB_ENDPTNAK_EPRNE_GET(_v)  (_v & 0xf)

#define BPORT1_AB_ENDPTNAKEN_POFFSET    0x17c
#define BPORT1_AB_ENDPTNAKEN            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTNAKEN_POFFSET)
#define BPORT1_AB_ENDPTNAKEN_EPTNE      (0xf << 16)
#define BPORT1_AB_ENDPTNAKEN_EPTNE_GET(_v)  ((_v >> 16) & 0xf)
#define BPORT1_AB_ENDPTNAKEN_EPRNE      0xf
#define BPORT1_AB_ENDPTNAKEN_EPRNE_GET(_v)  (_v & 0xf)

#define BPORT1_AB_CONFIGFLAG_POFFSET    0x180
#define BPORT1_AB_CONFIGFLAG            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CONFIGFLAG_POFFSET)

#define BPORT1_AB_PORTSC1_POFFSET       0x184
#define BPORT1_AB_PORTSC1               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PORTSC1_POFFSET)
#define BPORT1_AB_PORTSC1_CCS           0x1
#define BPORT1_AB_PORTSC1_CCS_GET(_v)   (_v & 0x1)
#define BPORT1_AB_PORTSC1_CSC           (0x1 << 1)
#define BPORT1_AB_PORTSC1_CSC_GET(_v)   ((_v >> 1) & 0x1)
#define BPORT1_AB_PORTSC1_FPR           (0x1 << 6)
#define BPORT1_AB_PORTSC1_FPR_GET(_v)   ((_v >> 6) & 0x1)
#define BPORT1_AB_PORTSC1_HSP           (0x1 << 9)
#define BPORT1_AB_PORTSC1_HSP_GET(_v)   ((_v >> 9) & 0x1)
#define BPORT1_AB_PORTSC1_LS            (0x3 << 10)
#define BPORT1_AB_PORTSC1_LS_GET(_v)    ((_v >> 10) & 0x3)
#define BPORT1_AB_PORTSC1_OCA           (0x1 << 4)
#define BPORT1_AB_PORTSC1_OCA_GET(_v)   ((_v >> 4) & 0x1)
#define BPORT1_AB_PORTSC1_OCC           (0x1 << 5)
#define BPORT1_AB_PORTSC1_OCC_GET(_v)   ((_v >> 5) & 0x1)
#define BPORT1_AB_PORTSC1_PE            (0x1 << 2)
#define BPORT1_AB_PORTSC1_PE_GET(_v)    ((_v >> 2) & 0x1)
#define BPORT1_AB_PORTSC1_PEC           (0x1 << 3)
#define BPORT1_AB_PORTSC1_PEC_GET(_v)   ((_v >> 3) & 0x1)
#define BPORT1_AB_PORTSC1_PFSC          (0x1 << 24)
#define BPORT1_AB_PORTSC1_PFSC_GET(_v)  ((_v >> 24) & 0x1)
#define BPORT1_AB_PORTSC1_PHCD          (0x1 << 23)
#define BPORT1_AB_PORTSC1_PHCD_GET(_v)  ((_v >> 23) & 0x1)
#define BPORT1_AB_PORTSC1_PIC           (0x3 << 14)
#define BPORT1_AB_PORTSC1_PIC_GET(_v)   ((_v >> 14) & 0x3)
#define BPORT1_AB_PORTSC1_PO            (0x1 << 13)
#define BPORT1_AB_PORTSC1_PO_GET(_v)    ((_v >> 13) & 0x1)
#define BPORT1_AB_PORTSC1_PP            (0x1 << 12)
#define BPORT1_AB_PORTSC1_PP_GET(_v)    ((_v >> 12) & 0x1)
#define BPORT1_AB_PORTSC1_PR            (0x1 << 8)
#define BPORT1_AB_PORTSC1_PR_GET(_v)    ((_v >> 8) & 0x1)
#define BPORT1_AB_PORTSC1_PSPD          (0x3 << 26)
#define BPORT1_AB_PORTSC1_PSPD_GET(_v)  ((_v >> 26) & 0x3)
#define BPORT1_AB_PORTSC1_PTC           (0xf << 16)
#define BPORT1_AB_PORTSC1_PTC_GET(_v)   ((_v >> 16) & 0xf)
#define BPORT1_AB_PORTSC1_PTS           (0x3 << 30)
#define BPORT1_AB_PORTSC1_PTS_GET(_v)   ((_v >> 30) & 0x3)
#define BPORT1_AB_PORTSC1_SUSP          (0x1 << 7)
#define BPORT1_AB_PORTSC1_SUSP_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_PORTSC1_WKCN          (0x1 << 20)
#define BPORT1_AB_PORTSC1_WKCN_GET(_v)  ((_v >> 20) & 0x1)
#define BPORT1_AB_PORTSC1_WKDS          (0x1 << 21)
#define BPORT1_AB_PORTSC1_WKDS_GET(_v)  ((_v >> 21) & 0x1)
#define BPORT1_AB_PORTSC1_WKOC          (0x1 << 22)
#define BPORT1_AB_PORTSC1_WKOC_GET(_v)  ((_v >> 22) & 0x1)

#define BPORT1_AB_OTGSC_POFFSET         0x1a4
#define BPORT1_AB_OTGSC                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_OTGSC_POFFSET)
#define BPORT1_AB_OTGSC_ASV             (0x1 << 10)
#define BPORT1_AB_OTGSC_ASV_GET(_v)     ((_v >> 10) & 0x1)
#define BPORT1_AB_OTGSC_ASVIE           (0x1 << 26)
#define BPORT1_AB_OTGSC_ASVIE_GET(_v)   ((_v >> 26) & 0x1)
#define BPORT1_AB_OTGSC_ASVIS           (0x1 << 18)
#define BPORT1_AB_OTGSC_ASVIS_GET(_v)   ((_v >> 18) & 0x1)
#define BPORT1_AB_OTGSC_AVV             (0x1 << 9)
#define BPORT1_AB_OTGSC_AVV_GET(_v)     ((_v >> 9) & 0x1)
#define BPORT1_AB_OTGSC_AVVIE           (0x1 << 25)
#define BPORT1_AB_OTGSC_AVVIE_GET(_v)   ((_v >> 25) & 0x1)
#define BPORT1_AB_OTGSC_AVVIS           (0x1 << 17)
#define BPORT1_AB_OTGSC_AVVIS_GET(_v)   ((_v >> 17) & 0x1)
#define BPORT1_AB_OTGSC_BSE             (0x1 << 12)
#define BPORT1_AB_OTGSC_BSE_GET(_v)     ((_v >> 12) & 0x1)
#define BPORT1_AB_OTGSC_BSEIE           (0x1 << 28)
#define BPORT1_AB_OTGSC_BSEIE_GET(_v)   ((_v >> 28) & 0x1)
#define BPORT1_AB_OTGSC_BSEIS           (0x1 << 20)
#define BPORT1_AB_OTGSC_BSEIS_GET(_v)   ((_v >> 20) & 0x1)
#define BPORT1_AB_OTGSC_BSV             (0x1 << 11)
#define BPORT1_AB_OTGSC_BSV_GET(_v)     ((_v >> 11) & 0x1)
#define BPORT1_AB_OTGSC_BSVIE           (0x1 << 27)
#define BPORT1_AB_OTGSC_BSVIE_GET(_v)   ((_v >> 27) & 0x1)
#define BPORT1_AB_OTGSC_BSVIS           (0x1 << 19)
#define BPORT1_AB_OTGSC_BSVIS_GET(_v)   ((_v >> 19) & 0x1)
#define BPORT1_AB_OTGSC_DP              (0x1 << 4)
#define BPORT1_AB_OTGSC_DP_GET(_v)      ((_v >> 4) & 0x1)
#define BPORT1_AB_OTGSC_DPIE            (0x1 << 30)
#define BPORT1_AB_OTGSC_DPIE_GET(_v)    ((_v >> 30) & 0x1)
#define BPORT1_AB_OTGSC_DPIS            (0x1 << 22)
#define BPORT1_AB_OTGSC_DPIS_GET(_v)    ((_v >> 22) & 0x1)
#define BPORT1_AB_OTGSC_DPS             (0x1 << 14)
#define BPORT1_AB_OTGSC_DPS_GET(_v)     ((_v >> 14) & 0x1)
#define BPORT1_AB_OTGSC_ID              (0x1 << 8)
#define BPORT1_AB_OTGSC_ID_GET(_v)      ((_v >> 8) & 0x1)
#define BPORT1_AB_OTGSC_IDIE            (0x1 << 24)
#define BPORT1_AB_OTGSC_IDIE_GET(_v)    ((_v >> 24) & 0x1)
#define BPORT1_AB_OTGSC_IDIS            (0x1 << 16)
#define BPORT1_AB_OTGSC_IDIS_GET(_v)    ((_v >> 16) & 0x1)
#define BPORT1_AB_OTGSC_IDPU            (0x1 << 5)
#define BPORT1_AB_OTGSC_IDPU_GET(_v)    ((_v >> 5) & 0x1)
#define BPORT1_AB_OTGSC_MSE             (0x1 << 29)
#define BPORT1_AB_OTGSC_MSE_GET(_v)     ((_v >> 29) & 0x1)
#define BPORT1_AB_OTGSC_MSS             (0x1 << 21)
#define BPORT1_AB_OTGSC_MSS_GET(_v)     ((_v >> 21) & 0x1)
#define BPORT1_AB_OTGSC_MST             (0x1 << 13)
#define BPORT1_AB_OTGSC_MST_GET(_v)     ((_v >> 13) & 0x1)
#define BPORT1_AB_OTGSC_OT              (0x1 << 3)
#define BPORT1_AB_OTGSC_OT_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_OTGSC_VC              (0x1 << 1)
#define BPORT1_AB_OTGSC_VC_GET(_v)      ((_v >> 1) & 0x1)
#define BPORT1_AB_OTGSC_VD              0x1
#define BPORT1_AB_OTGSC_VD_GET(_v)      (_v & 0x1)
#define BPORT1_AB_OTGSC_HABA            (0x1 << 7)
#define BPORT1_AB_OTGSC_HABA_GET(_v)    ((_v >> 7) & 0x1)
#define BPORT1_AB_OTGSC_HAAR            (0x1 << 2)
#define BPORT1_AB_OTGSC_HAAR_GET(_v)    ((_v >> 2) & 0x1)

#define BPORT1_AB_USBMODE_POFFSET       0x1a8
#define BPORT1_AB_USBMODE               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USBMODE_POFFSET)
#define BPORT1_AB_USBMODE_CM            0x3
#define BPORT1_AB_USBMODE_CM_GET(_v)    (_v & 0x3)
#define BPORT1_AB_USBMODE_ES            (0x1 << 2)
#define BPORT1_AB_USBMODE_ES_GET(_v)    ((_v >> 2) & 0x1)
#define BPORT1_AB_USBMODE_SDIS          (0x1 << 4)
#define BPORT1_AB_USBMODE_SDIS_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_USBMODE_SLOM          (0x1 << 3)
#define BPORT1_AB_USBMODE_SLOM_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_USBMODE_TXHSD         (0x7 << 12)
#define BPORT1_AB_USBMODE_TXHSD_GET(_v)  ((_v >> 12) & 0x7)

#define BPORT1_AB_EPSETUPSR_POFFSET     0x1ac
#define BPORT1_AB_EPSETUPSR             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EPSETUPSR_POFFSET)
#define BPORT1_AB_EPSETUPSR_EPSETUPSTAT  0xf
#define BPORT1_AB_EPSETUPSR_EPSETUPSTAT_GET(_v)  (_v & 0xf)

#define BPORT1_AB_EPPRIME_POFFSET       0x1b0
#define BPORT1_AB_EPPRIME               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EPPRIME_POFFSET)
#define BPORT1_AB_EPPRIME_PERB          0xf
#define BPORT1_AB_EPPRIME_PERB_GET(_v)  (_v & 0xf)
#define BPORT1_AB_EPPRIME_PETB          (0xf << 16)
#define BPORT1_AB_EPPRIME_PETB_GET(_v)  ((_v >> 16) & 0xf)

#define BPORT1_AB_EPFLUSH_POFFSET       0x1b4
#define BPORT1_AB_EPFLUSH               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EPFLUSH_POFFSET)
#define BPORT1_AB_EPFLUSH_FERB          0xf
#define BPORT1_AB_EPFLUSH_FERB_GET(_v)  (_v & 0xf)
#define BPORT1_AB_EPFLUSH_FETB          (0xf << 16)
#define BPORT1_AB_EPFLUSH_FETB_GET(_v)  ((_v >> 16) & 0xf)

#define BPORT1_AB_EPSR_POFFSET          0x1b8
#define BPORT1_AB_EPSR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EPSR_POFFSET)
#define BPORT1_AB_EPSR_ERBR             0xf
#define BPORT1_AB_EPSR_ERBR_GET(_v)     (_v & 0xf)
#define BPORT1_AB_EPSR_ETBR             (0xf << 16)
#define BPORT1_AB_EPSR_ETBR_GET(_v)     ((_v >> 16) & 0xf)

#define BPORT1_AB_EPCOMPLETE_POFFSET    0x1bc
#define BPORT1_AB_EPCOMPLETE            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EPCOMPLETE_POFFSET)
#define BPORT1_AB_EPCOMPLETE_ERCE       0xf
#define BPORT1_AB_EPCOMPLETE_ERCE_GET(_v)  (_v & 0xf)
#define BPORT1_AB_EPCOMPLETE_ETCE       (0xf << 16)
#define BPORT1_AB_EPCOMPLETE_ETCE_GET(_v)  ((_v >> 16) & 0xf)

#define BPORT1_AB_EPCR0_POFFSET         0x1c0
#define BPORT1_AB_EPCR0                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EPCR0_POFFSET)
#define BPORT1_AB_EPCR0_RXE             (0x1 << 7)
#define BPORT1_AB_EPCR0_RXE_GET(_v)     ((_v >> 7) & 0x1)
#define BPORT1_AB_EPCR0_RXS             0x1
#define BPORT1_AB_EPCR0_RXS_GET(_v)     (_v & 0x1)
#define BPORT1_AB_EPCR0_RXT             (0x3 << 2)
#define BPORT1_AB_EPCR0_RXT_GET(_v)     ((_v >> 2) & 0x3)
#define BPORT1_AB_EPCR0_TXE             (0x1 << 23)
#define BPORT1_AB_EPCR0_TXE_GET(_v)     ((_v >> 23) & 0x1)
#define BPORT1_AB_EPCR0_TXS             (0x1 << 16)
#define BPORT1_AB_EPCR0_TXS_GET(_v)     ((_v >> 16) & 0x1)
#define BPORT1_AB_EPCR0_TXT             (0x3 << 18)
#define BPORT1_AB_EPCR0_TXT_GET(_v)     ((_v >> 18) & 0x3)

#define BPORT1_AB_EPCR1_POFFSET         0x1c4
#define BPORT1_AB_EPCR1                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EPCR1_POFFSET)
#define BPORT1_AB_EPCR1_RXD             (0x1 << 1)
#define BPORT1_AB_EPCR1_RXD_GET(_v)     ((_v >> 1) & 0x1)
#define BPORT1_AB_EPCR1_RXE             (0x1 << 7)
#define BPORT1_AB_EPCR1_RXE_GET(_v)     ((_v >> 7) & 0x1)
#define BPORT1_AB_EPCR1_RXI             (0x1 << 5)
#define BPORT1_AB_EPCR1_RXI_GET(_v)     ((_v >> 5) & 0x1)
#define BPORT1_AB_EPCR1_RXR             (0x1 << 6)
#define BPORT1_AB_EPCR1_RXR_GET(_v)     ((_v >> 6) & 0x1)
#define BPORT1_AB_EPCR1_RXS             0x1
#define BPORT1_AB_EPCR1_RXS_GET(_v)     (_v & 0x1)
#define BPORT1_AB_EPCR1_RXT             (0x3 << 2)
#define BPORT1_AB_EPCR1_RXT_GET(_v)     ((_v >> 2) & 0x3)
#define BPORT1_AB_EPCR1_TXD             (0x1 << 17)
#define BPORT1_AB_EPCR1_TXD_GET(_v)     ((_v >> 17) & 0x1)
#define BPORT1_AB_EPCR1_TXE             (0x1 << 23)
#define BPORT1_AB_EPCR1_TXE_GET(_v)     ((_v >> 23) & 0x1)
#define BPORT1_AB_EPCR1_TXI             (0x1 << 21)
#define BPORT1_AB_EPCR1_TXI_GET(_v)     ((_v >> 21) & 0x1)
#define BPORT1_AB_EPCR1_TXR             (0x1 << 22)
#define BPORT1_AB_EPCR1_TXR_GET(_v)     ((_v >> 22) & 0x1)
#define BPORT1_AB_EPCR1_TXS             (0x1 << 16)
#define BPORT1_AB_EPCR1_TXS_GET(_v)     ((_v >> 16) & 0x1)
#define BPORT1_AB_EPCR1_TXT             (0x3 << 18)
#define BPORT1_AB_EPCR1_TXT_GET(_v)     ((_v >> 18) & 0x3)

#define BPORT1_AB_EPCR2_POFFSET         0x1c8
#define BPORT1_AB_EPCR2                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EPCR2_POFFSET)
#define BPORT1_AB_EPCR2_RXD             (0x1 << 1)
#define BPORT1_AB_EPCR2_RXD_GET(_v)     ((_v >> 1) & 0x1)
#define BPORT1_AB_EPCR2_RXE             (0x1 << 7)
#define BPORT1_AB_EPCR2_RXE_GET(_v)     ((_v >> 7) & 0x1)
#define BPORT1_AB_EPCR2_RXI             (0x1 << 5)
#define BPORT1_AB_EPCR2_RXI_GET(_v)     ((_v >> 5) & 0x1)
#define BPORT1_AB_EPCR2_RXR             (0x1 << 6)
#define BPORT1_AB_EPCR2_RXR_GET(_v)     ((_v >> 6) & 0x1)
#define BPORT1_AB_EPCR2_RXS             0x1
#define BPORT1_AB_EPCR2_RXS_GET(_v)     (_v & 0x1)
#define BPORT1_AB_EPCR2_RXT             (0x3 << 2)
#define BPORT1_AB_EPCR2_RXT_GET(_v)     ((_v >> 2) & 0x3)
#define BPORT1_AB_EPCR2_TXD             (0x1 << 17)
#define BPORT1_AB_EPCR2_TXD_GET(_v)     ((_v >> 17) & 0x1)
#define BPORT1_AB_EPCR2_TXE             (0x1 << 23)
#define BPORT1_AB_EPCR2_TXE_GET(_v)     ((_v >> 23) & 0x1)
#define BPORT1_AB_EPCR2_TXI             (0x1 << 21)
#define BPORT1_AB_EPCR2_TXI_GET(_v)     ((_v >> 21) & 0x1)
#define BPORT1_AB_EPCR2_TXR             (0x1 << 22)
#define BPORT1_AB_EPCR2_TXR_GET(_v)     ((_v >> 22) & 0x1)
#define BPORT1_AB_EPCR2_TXS             (0x1 << 16)
#define BPORT1_AB_EPCR2_TXS_GET(_v)     ((_v >> 16) & 0x1)
#define BPORT1_AB_EPCR2_TXT             (0x3 << 18)
#define BPORT1_AB_EPCR2_TXT_GET(_v)     ((_v >> 18) & 0x3)

#define BPORT1_AB_EPCR3_POFFSET         0x1cc
#define BPORT1_AB_EPCR3                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EPCR3_POFFSET)
#define BPORT1_AB_EPCR3_RXD             (0x1 << 1)
#define BPORT1_AB_EPCR3_RXD_GET(_v)     ((_v >> 1) & 0x1)
#define BPORT1_AB_EPCR3_RXE             (0x1 << 7)
#define BPORT1_AB_EPCR3_RXE_GET(_v)     ((_v >> 7) & 0x1)
#define BPORT1_AB_EPCR3_RXI             (0x1 << 5)
#define BPORT1_AB_EPCR3_RXI_GET(_v)     ((_v >> 5) & 0x1)
#define BPORT1_AB_EPCR3_RXR             (0x1 << 6)
#define BPORT1_AB_EPCR3_RXR_GET(_v)     ((_v >> 6) & 0x1)
#define BPORT1_AB_EPCR3_RXS             0x1
#define BPORT1_AB_EPCR3_RXS_GET(_v)     (_v & 0x1)
#define BPORT1_AB_EPCR3_RXT             (0x3 << 2)
#define BPORT1_AB_EPCR3_RXT_GET(_v)     ((_v >> 2) & 0x3)
#define BPORT1_AB_EPCR3_TXD             (0x1 << 17)
#define BPORT1_AB_EPCR3_TXD_GET(_v)     ((_v >> 17) & 0x1)
#define BPORT1_AB_EPCR3_TXE             (0x1 << 23)
#define BPORT1_AB_EPCR3_TXE_GET(_v)     ((_v >> 23) & 0x1)
#define BPORT1_AB_EPCR3_TXI             (0x1 << 21)
#define BPORT1_AB_EPCR3_TXI_GET(_v)     ((_v >> 21) & 0x1)
#define BPORT1_AB_EPCR3_TXR             (0x1 << 22)
#define BPORT1_AB_EPCR3_TXR_GET(_v)     ((_v >> 22) & 0x1)
#define BPORT1_AB_EPCR3_TXS             (0x1 << 16)
#define BPORT1_AB_EPCR3_TXS_GET(_v)     ((_v >> 16) & 0x1)
#define BPORT1_AB_EPCR3_TXT             (0x3 << 18)
#define BPORT1_AB_EPCR3_TXT_GET(_v)     ((_v >> 18) & 0x3)

#define BPORT1_AB_USBGENCTRL_POFFSET    0x200
#define BPORT1_AB_USBGENCTRL            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USBGENCTRL_POFFSET)
#define BPORT1_AB_USBGENCTRL_WU_INT_CLR  (0x1 << 5)
#define BPORT1_AB_USBGENCTRL_WU_INT_CLR_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_USBGENCTRL_WU_ULPI_EN  (0x1 << 1)
#define BPORT1_AB_USBGENCTRL_WU_ULPI_EN_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_USBGENCTRL_WU_IE      0x1
#define BPORT1_AB_USBGENCTRL_WU_IE_GET(_v)  (_v & 0x1)


#endif

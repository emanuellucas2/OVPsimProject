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
#define BPORT1_AB_ID_REVISION           (0xff << 16)
#define BPORT1_AB_ID_REVISION_GET(_v)   ((_v >> 16) & 0xff)

#define BPORT1_AB_HWGENERAL_POFFSET     0x4
#define BPORT1_AB_HWGENERAL             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HWGENERAL_POFFSET)
#define BPORT1_AB_HWGENERAL_PHYM        (0x7 << 6)
#define BPORT1_AB_HWGENERAL_PHYM_GET(_v)  ((_v >> 6) & 0x7)
#define BPORT1_AB_HWGENERAL_PHYW        (0x3 << 4)
#define BPORT1_AB_HWGENERAL_PHYW_GET(_v)  ((_v >> 4) & 0x3)
#define BPORT1_AB_HWGENERAL_SM          (0x3 << 9)
#define BPORT1_AB_HWGENERAL_SM_GET(_v)  ((_v >> 9) & 0x3)

#define BPORT1_AB_HWHOST_POFFSET        0x8
#define BPORT1_AB_HWHOST                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HWHOST_POFFSET)
#define BPORT1_AB_HWHOST_HC             0x1
#define BPORT1_AB_HWHOST_HC_GET(_v)     (_v & 0x1)
#define BPORT1_AB_HWHOST_NPORT          (0x7 << 1)
#define BPORT1_AB_HWHOST_NPORT_GET(_v)  ((_v >> 1) & 0x7)

#define BPORT1_AB_HWDEVICE_POFFSET      0xc
#define BPORT1_AB_HWDEVICE              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HWDEVICE_POFFSET)
#define BPORT1_AB_HWDEVICE_DC           0x1
#define BPORT1_AB_HWDEVICE_DC_GET(_v)   (_v & 0x1)
#define BPORT1_AB_HWDEVICE_DEVEP        (0x1f << 1)
#define BPORT1_AB_HWDEVICE_DEVEP_GET(_v)  ((_v >> 1) & 0x1f)

#define BPORT1_AB_HWTXBUF_POFFSET       0x10
#define BPORT1_AB_HWTXBUF               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HWTXBUF_POFFSET)
#define BPORT1_AB_HWTXBUF_TXBURST       0xff
#define BPORT1_AB_HWTXBUF_TXBURST_GET(_v)  (_v & 0xff)
#define BPORT1_AB_HWTXBUF_TXCHANADD     (0xff << 16)
#define BPORT1_AB_HWTXBUF_TXCHANADD_GET(_v)  ((_v >> 16) & 0xff)

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

#define BPORT1_AB_GPTIMER0CTRL_POFFSET  0x84
#define BPORT1_AB_GPTIMER0CTRL          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPTIMER0CTRL_POFFSET)
#define BPORT1_AB_GPTIMER0CTRL_GPTCNT   0xffffff
#define BPORT1_AB_GPTIMER0CTRL_GPTCNT_GET(_v)  (_v & 0xffffff)
#define BPORT1_AB_GPTIMER0CTRL_GPTMODE  (0x1 << 24)
#define BPORT1_AB_GPTIMER0CTRL_GPTMODE_GET(_v)  ((_v >> 24) & 0x1)
#define BPORT1_AB_GPTIMER0CTRL_GPTRST   (0x1 << 30)
#define BPORT1_AB_GPTIMER0CTRL_GPTRST_GET(_v)  ((_v >> 30) & 0x1)
#define BPORT1_AB_GPTIMER0CTRL_GPTRUN   (0x1 << 31)
#define BPORT1_AB_GPTIMER0CTRL_GPTRUN_GET(_v)  ((_v >> 31) & 0x1)

#define BPORT1_AB_GPTIMER1LD_POFFSET    0x88
#define BPORT1_AB_GPTIMER1LD            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPTIMER1LD_POFFSET)
#define BPORT1_AB_GPTIMER1LD_GPTLD      0xffffff
#define BPORT1_AB_GPTIMER1LD_GPTLD_GET(_v)  (_v & 0xffffff)

#define BPORT1_AB_GPTIMER1CTRL_POFFSET  0x8c
#define BPORT1_AB_GPTIMER1CTRL          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPTIMER1CTRL_POFFSET)
#define BPORT1_AB_GPTIMER1CTRL_GPTCNT   0xffffff
#define BPORT1_AB_GPTIMER1CTRL_GPTCNT_GET(_v)  (_v & 0xffffff)
#define BPORT1_AB_GPTIMER1CTRL_GPTMODE  (0x1 << 24)
#define BPORT1_AB_GPTIMER1CTRL_GPTMODE_GET(_v)  ((_v >> 24) & 0x1)
#define BPORT1_AB_GPTIMER1CTRL_GPTRST   (0x1 << 30)
#define BPORT1_AB_GPTIMER1CTRL_GPTRST_GET(_v)  ((_v >> 30) & 0x1)
#define BPORT1_AB_GPTIMER1CTRL_GPTRUN   (0x1 << 31)
#define BPORT1_AB_GPTIMER1CTRL_GPTRUN_GET(_v)  ((_v >> 31) & 0x1)

#define BPORT1_AB_SBUSCFG_POFFSET       0x90
#define BPORT1_AB_SBUSCFG               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SBUSCFG_POFFSET)
#define BPORT1_AB_SBUSCFG_AHBBRST       0x7
#define BPORT1_AB_SBUSCFG_AHBBRST_GET(_v)  (_v & 0x7)

#define BPORT1_AB_CAPVERSION_POFFSET    0x100
#define BPORT1_AB_CAPVERSION            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CAPVERSION_POFFSET)

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
#define BPORT1_AB_USBCMD_FS1            (0x3 << 2)
#define BPORT1_AB_USBCMD_FS1_GET(_v)    ((_v >> 2) & 0x3)
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
#define BPORT1_AB_USBSTS_UEI            (0x1 << 1)
#define BPORT1_AB_USBSTS_UEI_GET(_v)    ((_v >> 1) & 0x1)
#define BPORT1_AB_USBSTS_UI             0x1
#define BPORT1_AB_USBSTS_UI_GET(_v)     (_v & 0x1)
#define BPORT1_AB_USBSTS_UPI            (0x1 << 19)
#define BPORT1_AB_USBSTS_UPI_GET(_v)    ((_v >> 19) & 0x1)
#define BPORT1_AB_USBSTS_UAI            (0x1 << 18)
#define BPORT1_AB_USBSTS_UAI_GET(_v)    ((_v >> 18) & 0x1)
#define BPORT1_AB_USBSTS_ULPII          (0x1 << 10)
#define BPORT1_AB_USBSTS_ULPII_GET(_v)  ((_v >> 10) & 0x1)
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

#define BPORT1_AB_ASYNCLISTADDR_POFFSET  0x158
#define BPORT1_AB_ASYNCLISTADDR         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ASYNCLISTADDR_POFFSET)

#define BPORT1_AB_BURSTSIZE_POFFSET     0x160
#define BPORT1_AB_BURSTSIZE             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BURSTSIZE_POFFSET)
#define BPORT1_AB_BURSTSIZE_RXPBURST    0xff
#define BPORT1_AB_BURSTSIZE_RXPBURST_GET(_v)  (_v & 0xff)
#define BPORT1_AB_BURSTSIZE_TXPBURST    (0x1ff << 8)
#define BPORT1_AB_BURSTSIZE_TXPBURST_GET(_v)  ((_v >> 8) & 0x1ff)

#define BPORT1_AB_TXFILLTUNING_POFFSET  0x164
#define BPORT1_AB_TXFILLTUNING          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TXFILLTUNING_POFFSET)
#define BPORT1_AB_TXFILLTUNING_TXFIFOTHRES  (0x3f << 16)
#define BPORT1_AB_TXFILLTUNING_TXFIFOTHRES_GET(_v)  ((_v >> 16) & 0x3f)
#define BPORT1_AB_TXFILLTUNING_TXSCHHEALTH  (0x1f << 8)
#define BPORT1_AB_TXFILLTUNING_TXSCHHEALTH_GET(_v)  ((_v >> 8) & 0x1f)
#define BPORT1_AB_TXFILLTUNING_TXSCHOH  0xff
#define BPORT1_AB_TXFILLTUNING_TXSCHOH_GET(_v)  (_v & 0xff)

#define BPORT1_AB_ENDPTNAK_POFFSET      0x178
#define BPORT1_AB_ENDPTNAK              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTNAK_POFFSET)
#define BPORT1_AB_ENDPTNAK_EPRN         0x3f
#define BPORT1_AB_ENDPTNAK_EPRN_GET(_v)  (_v & 0x3f)
#define BPORT1_AB_ENDPTNAK_EPTN         (0x3f << 16)
#define BPORT1_AB_ENDPTNAK_EPTN_GET(_v)  ((_v >> 16) & 0x3f)

#define BPORT1_AB_ENDPTNAKEN_POFFSET    0x17c
#define BPORT1_AB_ENDPTNAKEN            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTNAKEN_POFFSET)
#define BPORT1_AB_ENDPTNAKEN_EPRNE      0x3f
#define BPORT1_AB_ENDPTNAKEN_EPRNE_GET(_v)  (_v & 0x3f)
#define BPORT1_AB_ENDPTNAKEN_EPTNE      (0x3f << 16)
#define BPORT1_AB_ENDPTNAKEN_EPTNE_GET(_v)  ((_v >> 16) & 0x3f)

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
#define BPORT1_AB_PORTSC1_PTS1          (0x1 << 25)
#define BPORT1_AB_PORTSC1_PTS1_GET(_v)  ((_v >> 25) & 0x1)
#define BPORT1_AB_PORTSC1_PTS2          (0x3 << 30)
#define BPORT1_AB_PORTSC1_PTS2_GET(_v)  ((_v >> 30) & 0x3)
#define BPORT1_AB_PORTSC1_PTW           (0x1 << 28)
#define BPORT1_AB_PORTSC1_PTW_GET(_v)   ((_v >> 28) & 0x1)
#define BPORT1_AB_PORTSC1_STS           (0x1 << 29)
#define BPORT1_AB_PORTSC1_STS_GET(_v)   ((_v >> 29) & 0x1)
#define BPORT1_AB_PORTSC1_SUSP          (0x1 << 7)
#define BPORT1_AB_PORTSC1_SUSP_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_PORTSC1_WKCN          (0x1 << 20)
#define BPORT1_AB_PORTSC1_WKCN_GET(_v)  ((_v >> 20) & 0x1)
#define BPORT1_AB_PORTSC1_WKDC          (0x1 << 21)
#define BPORT1_AB_PORTSC1_WKDC_GET(_v)  ((_v >> 21) & 0x1)
#define BPORT1_AB_PORTSC1_WKOC          (0x1 << 22)
#define BPORT1_AB_PORTSC1_WKOC_GET(_v)  ((_v >> 22) & 0x1)

#define BPORT1_AB_OTGSC_POFFSET         0x1a4
#define BPORT1_AB_OTGSC                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_OTGSC_POFFSET)
#define BPORT1_AB_OTGSC_MSS1            (0x1 << 21)
#define BPORT1_AB_OTGSC_MSS1_GET(_v)    ((_v >> 21) & 0x1)
#define BPORT1_AB_OTGSC_MSSE1           (0x1 << 29)
#define BPORT1_AB_OTGSC_MSSE1_GET(_v)   ((_v >> 29) & 0x1)
#define BPORT1_AB_OTGSC_MST1            (0x1 << 13)
#define BPORT1_AB_OTGSC_MST1_GET(_v)    ((_v >> 13) & 0x1)
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
#define BPORT1_AB_OTGSC_OT              (0x1 << 3)
#define BPORT1_AB_OTGSC_OT_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_OTGSC_VD              0x1
#define BPORT1_AB_OTGSC_VD_GET(_v)      (_v & 0x1)

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

#define BPORT1_AB_ENDPTSETUPSTAT_POFFSET  0x1ac
#define BPORT1_AB_ENDPTSETUPSTAT        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTSETUPSTAT_POFFSET)
#define BPORT1_AB_ENDPTSETUPSTAT_ENDPTSETUPSTAT  0xffff
#define BPORT1_AB_ENDPTSETUPSTAT_ENDPTSETUPSTAT_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_ENDPTPRIME_POFFSET    0x1b0
#define BPORT1_AB_ENDPTPRIME            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTPRIME_POFFSET)
#define BPORT1_AB_ENDPTPRIME_PERB       0x3f
#define BPORT1_AB_ENDPTPRIME_PERB_GET(_v)  (_v & 0x3f)
#define BPORT1_AB_ENDPTPRIME_PETB       (0x3f << 16)
#define BPORT1_AB_ENDPTPRIME_PETB_GET(_v)  ((_v >> 16) & 0x3f)

#define BPORT1_AB_ENDPTFLUSH_POFFSET    0x1b4
#define BPORT1_AB_ENDPTFLUSH            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTFLUSH_POFFSET)
#define BPORT1_AB_ENDPTFLUSH_FERB       0x3f
#define BPORT1_AB_ENDPTFLUSH_FERB_GET(_v)  (_v & 0x3f)
#define BPORT1_AB_ENDPTFLUSH_FETB       (0x3f << 16)
#define BPORT1_AB_ENDPTFLUSH_FETB_GET(_v)  ((_v >> 16) & 0x3f)

#define BPORT1_AB_ENDPTSTAT_POFFSET     0x1b8
#define BPORT1_AB_ENDPTSTAT             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTSTAT_POFFSET)
#define BPORT1_AB_ENDPTSTAT_ERBR        0x3f
#define BPORT1_AB_ENDPTSTAT_ERBR_GET(_v)  (_v & 0x3f)
#define BPORT1_AB_ENDPTSTAT_ETBR        (0x3f << 16)
#define BPORT1_AB_ENDPTSTAT_ETBR_GET(_v)  ((_v >> 16) & 0x3f)

#define BPORT1_AB_ENDPTCOMPLETE_POFFSET  0x1bc
#define BPORT1_AB_ENDPTCOMPLETE         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTCOMPLETE_POFFSET)
#define BPORT1_AB_ENDPTCOMPLETE_ERCE    0x3f
#define BPORT1_AB_ENDPTCOMPLETE_ERCE_GET(_v)  (_v & 0x3f)
#define BPORT1_AB_ENDPTCOMPLETE_ETCE    (0x3f << 16)
#define BPORT1_AB_ENDPTCOMPLETE_ETCE_GET(_v)  ((_v >> 16) & 0x3f)

#define BPORT1_AB_ENDPTCTRL0_POFFSET    0x1c0
#define BPORT1_AB_ENDPTCTRL0            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTCTRL0_POFFSET)
#define BPORT1_AB_ENDPTCTRL0_RXE        (0x1 << 7)
#define BPORT1_AB_ENDPTCTRL0_RXE_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_ENDPTCTRL0_RXS        0x1
#define BPORT1_AB_ENDPTCTRL0_RXS_GET(_v)  (_v & 0x1)
#define BPORT1_AB_ENDPTCTRL0_RXT        (0x3 << 2)
#define BPORT1_AB_ENDPTCTRL0_RXT_GET(_v)  ((_v >> 2) & 0x3)
#define BPORT1_AB_ENDPTCTRL0_TXE        (0x1 << 23)
#define BPORT1_AB_ENDPTCTRL0_TXE_GET(_v)  ((_v >> 23) & 0x1)
#define BPORT1_AB_ENDPTCTRL0_TXS        (0x1 << 16)
#define BPORT1_AB_ENDPTCTRL0_TXS_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_ENDPTCTRL0_TXT        (0x3 << 18)
#define BPORT1_AB_ENDPTCTRL0_TXT_GET(_v)  ((_v >> 18) & 0x3)

#define BPORT1_AB_ENDPTCTRL1_POFFSET    0x1c4
#define BPORT1_AB_ENDPTCTRL1            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTCTRL1_POFFSET)
#define BPORT1_AB_ENDPTCTRL1_RXD        (0x1 << 1)
#define BPORT1_AB_ENDPTCTRL1_RXD_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_ENDPTCTRL1_RXE        (0x1 << 7)
#define BPORT1_AB_ENDPTCTRL1_RXE_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_ENDPTCTRL1_RXI        (0x1 << 5)
#define BPORT1_AB_ENDPTCTRL1_RXI_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_ENDPTCTRL1_RXR        (0x1 << 6)
#define BPORT1_AB_ENDPTCTRL1_RXR_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_ENDPTCTRL1_RXS        0x1
#define BPORT1_AB_ENDPTCTRL1_RXS_GET(_v)  (_v & 0x1)
#define BPORT1_AB_ENDPTCTRL1_RXT        (0x3 << 2)
#define BPORT1_AB_ENDPTCTRL1_RXT_GET(_v)  ((_v >> 2) & 0x3)
#define BPORT1_AB_ENDPTCTRL1_TXD        (0x1 << 17)
#define BPORT1_AB_ENDPTCTRL1_TXD_GET(_v)  ((_v >> 17) & 0x1)
#define BPORT1_AB_ENDPTCTRL1_TXE        (0x1 << 23)
#define BPORT1_AB_ENDPTCTRL1_TXE_GET(_v)  ((_v >> 23) & 0x1)
#define BPORT1_AB_ENDPTCTRL1_TXI        (0x1 << 21)
#define BPORT1_AB_ENDPTCTRL1_TXI_GET(_v)  ((_v >> 21) & 0x1)
#define BPORT1_AB_ENDPTCTRL1_TXR        (0x1 << 22)
#define BPORT1_AB_ENDPTCTRL1_TXR_GET(_v)  ((_v >> 22) & 0x1)
#define BPORT1_AB_ENDPTCTRL1_TXS        (0x1 << 16)
#define BPORT1_AB_ENDPTCTRL1_TXS_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_ENDPTCTRL1_TXT        (0x3 << 18)
#define BPORT1_AB_ENDPTCTRL1_TXT_GET(_v)  ((_v >> 18) & 0x3)

#define BPORT1_AB_ENDPTCTRL2_POFFSET    0x1c8
#define BPORT1_AB_ENDPTCTRL2            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTCTRL2_POFFSET)
#define BPORT1_AB_ENDPTCTRL2_RXD        (0x1 << 1)
#define BPORT1_AB_ENDPTCTRL2_RXD_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_ENDPTCTRL2_RXE        (0x1 << 7)
#define BPORT1_AB_ENDPTCTRL2_RXE_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_ENDPTCTRL2_RXI        (0x1 << 5)
#define BPORT1_AB_ENDPTCTRL2_RXI_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_ENDPTCTRL2_RXR        (0x1 << 6)
#define BPORT1_AB_ENDPTCTRL2_RXR_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_ENDPTCTRL2_RXS        0x1
#define BPORT1_AB_ENDPTCTRL2_RXS_GET(_v)  (_v & 0x1)
#define BPORT1_AB_ENDPTCTRL2_RXT        (0x3 << 2)
#define BPORT1_AB_ENDPTCTRL2_RXT_GET(_v)  ((_v >> 2) & 0x3)
#define BPORT1_AB_ENDPTCTRL2_TXD        (0x1 << 17)
#define BPORT1_AB_ENDPTCTRL2_TXD_GET(_v)  ((_v >> 17) & 0x1)
#define BPORT1_AB_ENDPTCTRL2_TXE        (0x1 << 23)
#define BPORT1_AB_ENDPTCTRL2_TXE_GET(_v)  ((_v >> 23) & 0x1)
#define BPORT1_AB_ENDPTCTRL2_TXI        (0x1 << 21)
#define BPORT1_AB_ENDPTCTRL2_TXI_GET(_v)  ((_v >> 21) & 0x1)
#define BPORT1_AB_ENDPTCTRL2_TXR        (0x1 << 22)
#define BPORT1_AB_ENDPTCTRL2_TXR_GET(_v)  ((_v >> 22) & 0x1)
#define BPORT1_AB_ENDPTCTRL2_TXS        (0x1 << 16)
#define BPORT1_AB_ENDPTCTRL2_TXS_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_ENDPTCTRL2_TXT        (0x3 << 18)
#define BPORT1_AB_ENDPTCTRL2_TXT_GET(_v)  ((_v >> 18) & 0x3)

#define BPORT1_AB_ENDPTCTRL3_POFFSET    0x1cc
#define BPORT1_AB_ENDPTCTRL3            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTCTRL3_POFFSET)
#define BPORT1_AB_ENDPTCTRL3_RXD        (0x1 << 1)
#define BPORT1_AB_ENDPTCTRL3_RXD_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_ENDPTCTRL3_RXE        (0x1 << 7)
#define BPORT1_AB_ENDPTCTRL3_RXE_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_ENDPTCTRL3_RXI        (0x1 << 5)
#define BPORT1_AB_ENDPTCTRL3_RXI_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_ENDPTCTRL3_RXR        (0x1 << 6)
#define BPORT1_AB_ENDPTCTRL3_RXR_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_ENDPTCTRL3_RXS        0x1
#define BPORT1_AB_ENDPTCTRL3_RXS_GET(_v)  (_v & 0x1)
#define BPORT1_AB_ENDPTCTRL3_RXT        (0x3 << 2)
#define BPORT1_AB_ENDPTCTRL3_RXT_GET(_v)  ((_v >> 2) & 0x3)
#define BPORT1_AB_ENDPTCTRL3_TXD        (0x1 << 17)
#define BPORT1_AB_ENDPTCTRL3_TXD_GET(_v)  ((_v >> 17) & 0x1)
#define BPORT1_AB_ENDPTCTRL3_TXE        (0x1 << 23)
#define BPORT1_AB_ENDPTCTRL3_TXE_GET(_v)  ((_v >> 23) & 0x1)
#define BPORT1_AB_ENDPTCTRL3_TXI        (0x1 << 21)
#define BPORT1_AB_ENDPTCTRL3_TXI_GET(_v)  ((_v >> 21) & 0x1)
#define BPORT1_AB_ENDPTCTRL3_TXR        (0x1 << 22)
#define BPORT1_AB_ENDPTCTRL3_TXR_GET(_v)  ((_v >> 22) & 0x1)
#define BPORT1_AB_ENDPTCTRL3_TXS        (0x1 << 16)
#define BPORT1_AB_ENDPTCTRL3_TXS_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_ENDPTCTRL3_TXT        (0x3 << 18)
#define BPORT1_AB_ENDPTCTRL3_TXT_GET(_v)  ((_v >> 18) & 0x3)

#define BPORT1_AB_ENDPTCTRL4_POFFSET    0x1d0
#define BPORT1_AB_ENDPTCTRL4            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTCTRL4_POFFSET)
#define BPORT1_AB_ENDPTCTRL4_RXD        (0x1 << 1)
#define BPORT1_AB_ENDPTCTRL4_RXD_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_ENDPTCTRL4_RXE        (0x1 << 7)
#define BPORT1_AB_ENDPTCTRL4_RXE_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_ENDPTCTRL4_RXI        (0x1 << 5)
#define BPORT1_AB_ENDPTCTRL4_RXI_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_ENDPTCTRL4_RXR        (0x1 << 6)
#define BPORT1_AB_ENDPTCTRL4_RXR_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_ENDPTCTRL4_RXS        0x1
#define BPORT1_AB_ENDPTCTRL4_RXS_GET(_v)  (_v & 0x1)
#define BPORT1_AB_ENDPTCTRL4_RXT        (0x3 << 2)
#define BPORT1_AB_ENDPTCTRL4_RXT_GET(_v)  ((_v >> 2) & 0x3)
#define BPORT1_AB_ENDPTCTRL4_TXD        (0x1 << 17)
#define BPORT1_AB_ENDPTCTRL4_TXD_GET(_v)  ((_v >> 17) & 0x1)
#define BPORT1_AB_ENDPTCTRL4_TXE        (0x1 << 23)
#define BPORT1_AB_ENDPTCTRL4_TXE_GET(_v)  ((_v >> 23) & 0x1)
#define BPORT1_AB_ENDPTCTRL4_TXI        (0x1 << 21)
#define BPORT1_AB_ENDPTCTRL4_TXI_GET(_v)  ((_v >> 21) & 0x1)
#define BPORT1_AB_ENDPTCTRL4_TXR        (0x1 << 22)
#define BPORT1_AB_ENDPTCTRL4_TXR_GET(_v)  ((_v >> 22) & 0x1)
#define BPORT1_AB_ENDPTCTRL4_TXS        (0x1 << 16)
#define BPORT1_AB_ENDPTCTRL4_TXS_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_ENDPTCTRL4_TXT        (0x3 << 18)
#define BPORT1_AB_ENDPTCTRL4_TXT_GET(_v)  ((_v >> 18) & 0x3)

#define BPORT1_AB_ENDPTCTRL5_POFFSET    0x1d4
#define BPORT1_AB_ENDPTCTRL5            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENDPTCTRL5_POFFSET)
#define BPORT1_AB_ENDPTCTRL5_RXD        (0x1 << 1)
#define BPORT1_AB_ENDPTCTRL5_RXD_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_ENDPTCTRL5_RXE        (0x1 << 7)
#define BPORT1_AB_ENDPTCTRL5_RXE_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_ENDPTCTRL5_RXI        (0x1 << 5)
#define BPORT1_AB_ENDPTCTRL5_RXI_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_ENDPTCTRL5_RXR        (0x1 << 6)
#define BPORT1_AB_ENDPTCTRL5_RXR_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_ENDPTCTRL5_RXS        0x1
#define BPORT1_AB_ENDPTCTRL5_RXS_GET(_v)  (_v & 0x1)
#define BPORT1_AB_ENDPTCTRL5_RXT        (0x3 << 2)
#define BPORT1_AB_ENDPTCTRL5_RXT_GET(_v)  ((_v >> 2) & 0x3)
#define BPORT1_AB_ENDPTCTRL5_TXD        (0x1 << 17)
#define BPORT1_AB_ENDPTCTRL5_TXD_GET(_v)  ((_v >> 17) & 0x1)
#define BPORT1_AB_ENDPTCTRL5_TXE        (0x1 << 23)
#define BPORT1_AB_ENDPTCTRL5_TXE_GET(_v)  ((_v >> 23) & 0x1)
#define BPORT1_AB_ENDPTCTRL5_TXI        (0x1 << 21)
#define BPORT1_AB_ENDPTCTRL5_TXI_GET(_v)  ((_v >> 21) & 0x1)
#define BPORT1_AB_ENDPTCTRL5_TXR        (0x1 << 22)
#define BPORT1_AB_ENDPTCTRL5_TXR_GET(_v)  ((_v >> 22) & 0x1)
#define BPORT1_AB_ENDPTCTRL5_TXS        (0x1 << 16)
#define BPORT1_AB_ENDPTCTRL5_TXS_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_ENDPTCTRL5_TXT        (0x3 << 18)
#define BPORT1_AB_ENDPTCTRL5_TXT_GET(_v)  ((_v >> 18) & 0x3)

#define BPORT1_AB_CTRL_POFFSET          0x800
#define BPORT1_AB_CTRL                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CTRL_POFFSET)
#define BPORT1_AB_CTRL_WIR              (0x1 << 31)
#define BPORT1_AB_CTRL_WIR_GET(_v)      ((_v >> 31) & 0x1)
#define BPORT1_AB_CTRL_VBUS_CH_INT_MASK  (0x1 << 25)
#define BPORT1_AB_CTRL_VBUS_CH_INT_MASK_GET(_v)  ((_v >> 25) & 0x1)
#define BPORT1_AB_CTRL_VBUS_CH_STAT     (0x1 << 24)
#define BPORT1_AB_CTRL_VBUS_CH_STAT_GET(_v)  ((_v >> 24) & 0x1)
#define BPORT1_AB_CTRL_WKUP_VBUS_EN     (0x1 << 17)
#define BPORT1_AB_CTRL_WKUP_VBUS_EN_GET(_v)  ((_v >> 17) & 0x1)
#define BPORT1_AB_CTRL_WKUP_SW          (0x1 << 15)
#define BPORT1_AB_CTRL_WKUP_SW_GET(_v)  ((_v >> 15) & 0x1)
#define BPORT1_AB_CTRL_WKUP_SW_EN       (0x1 << 14)
#define BPORT1_AB_CTRL_WKUP_SW_EN_GET(_v)  ((_v >> 14) & 0x1)
#define BPORT1_AB_CTRL_ETMI_ON_CLOSK    (0x1 << 13)
#define BPORT1_AB_CTRL_ETMI_ON_CLOSK_GET(_v)  ((_v >> 13) & 0x1)
#define BPORT1_AB_CTRL_SUSPENDM         (0x1 << 12)
#define BPORT1_AB_CTRL_SUSPENDM_GET(_v)  ((_v >> 12) & 0x1)
#define BPORT1_AB_CTRL_RESET            (0x1 << 11)
#define BPORT1_AB_CTRL_RESET_GET(_v)    ((_v >> 11) & 0x1)
#define BPORT1_AB_CTRL_WIE              (0x1 << 10)
#define BPORT1_AB_CTRL_WIE_GET(_v)      ((_v >> 10) & 0x1)
#define BPORT1_AB_CTRL_PM               (0x1 << 9)
#define BPORT1_AB_CTRL_PM_GET(_v)       ((_v >> 9) & 0x1)
#define BPORT1_AB_CTRL_OVER_CUR_POL     (0x1 << 8)
#define BPORT1_AB_CTRL_OVER_CUR_POL_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_CTRL_OVER_CUR_DIS     (0x1 << 7)
#define BPORT1_AB_CTRL_OVER_CUR_DIS_GET(_v)  ((_v >> 7) & 0x1)

#define BPORT1_AB_PHY_POFFSET           0x818
#define BPORT1_AB_PHY                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PHY_POFFSET)
#define BPORT1_AB_PHY_UTMI_CLK_VLD      (0x1 << 31)
#define BPORT1_AB_PHY_UTMI_CLK_VLD_GET(_v)  ((_v >> 31) & 0x1)
#define BPORT1_AB_PHY_CHRGDET           (0x1 << 2)
#define BPORT1_AB_PHY_CHRGDET_GET(_v)   ((_v >> 2) & 0x1)
#define BPORT1_AB_PHY_CHRGDET_INT_EN    (0x1 << 1)
#define BPORT1_AB_PHY_CHRGDET_INT_EN_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_PHY_CHRGDET_INT_FLG   0x1
#define BPORT1_AB_PHY_CHRGDET_INT_FLG_GET(_v)  (_v & 0x1)


#endif

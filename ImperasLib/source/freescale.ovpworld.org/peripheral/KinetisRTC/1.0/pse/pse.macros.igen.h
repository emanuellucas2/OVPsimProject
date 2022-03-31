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
#define BPORT1_AB_TSR_POFFSET           0x0
#define BPORT1_AB_TSR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TSR_POFFSET)
#define BPORT1_AB_TSR_TSR               0xffffffff
#define BPORT1_AB_TSR_TSR_GET(_v)       (_v & 0xffffffff)

#define BPORT1_AB_TPR_POFFSET           0x4
#define BPORT1_AB_TPR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TPR_POFFSET)
#define BPORT1_AB_TPR_TPR               0xffff
#define BPORT1_AB_TPR_TPR_GET(_v)       (_v & 0xffff)

#define BPORT1_AB_TAR_POFFSET           0x8
#define BPORT1_AB_TAR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TAR_POFFSET)
#define BPORT1_AB_TAR_TAR               0xffffffff
#define BPORT1_AB_TAR_TAR_GET(_v)       (_v & 0xffffffff)

#define BPORT1_AB_TCR_POFFSET           0xc
#define BPORT1_AB_TCR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCR_POFFSET)
#define BPORT1_AB_TCR_CIC               (0xff << 24)
#define BPORT1_AB_TCR_CIC_GET(_v)       ((_v >> 24) & 0xff)
#define BPORT1_AB_TCR_CIR               (0xff << 8)
#define BPORT1_AB_TCR_CIR_GET(_v)       ((_v >> 8) & 0xff)
#define BPORT1_AB_TCR_TCR               0xff
#define BPORT1_AB_TCR_TCR_GET(_v)       (_v & 0xff)
#define BPORT1_AB_TCR_TCV               (0xff << 16)
#define BPORT1_AB_TCR_TCV_GET(_v)       ((_v >> 16) & 0xff)

#define BPORT1_AB_CR_POFFSET            0x10
#define BPORT1_AB_CR                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR_POFFSET)
#define BPORT1_AB_CR_CLKO               (0x1 << 9)
#define BPORT1_AB_CR_CLKO_GET(_v)       ((_v >> 9) & 0x1)
#define BPORT1_AB_CR_OSCE               (0x1 << 8)
#define BPORT1_AB_CR_OSCE_GET(_v)       ((_v >> 8) & 0x1)
#define BPORT1_AB_CR_SC16P              (0x1 << 10)
#define BPORT1_AB_CR_SC16P_GET(_v)      ((_v >> 10) & 0x1)
#define BPORT1_AB_CR_SC2P               (0x1 << 13)
#define BPORT1_AB_CR_SC2P_GET(_v)       ((_v >> 13) & 0x1)
#define BPORT1_AB_CR_SC4P               (0x1 << 12)
#define BPORT1_AB_CR_SC4P_GET(_v)       ((_v >> 12) & 0x1)
#define BPORT1_AB_CR_SC8P               (0x1 << 11)
#define BPORT1_AB_CR_SC8P_GET(_v)       ((_v >> 11) & 0x1)
#define BPORT1_AB_CR_SUP                (0x1 << 2)
#define BPORT1_AB_CR_SUP_GET(_v)        ((_v >> 2) & 0x1)
#define BPORT1_AB_CR_SWR                0x1
#define BPORT1_AB_CR_SWR_GET(_v)        (_v & 0x1)
#define BPORT1_AB_CR_UM                 (0x1 << 3)
#define BPORT1_AB_CR_UM_GET(_v)         ((_v >> 3) & 0x1)
#define BPORT1_AB_CR_WPE                (0x1 << 1)
#define BPORT1_AB_CR_WPE_GET(_v)        ((_v >> 1) & 0x1)

#define BPORT1_AB_SR_POFFSET            0x14
#define BPORT1_AB_SR                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SR_POFFSET)
#define BPORT1_AB_SR_MOF                (0x1 << 3)
#define BPORT1_AB_SR_MOF_GET(_v)        ((_v >> 3) & 0x1)
#define BPORT1_AB_SR_TAF                (0x1 << 2)
#define BPORT1_AB_SR_TAF_GET(_v)        ((_v >> 2) & 0x1)
#define BPORT1_AB_SR_TCE                (0x1 << 4)
#define BPORT1_AB_SR_TCE_GET(_v)        ((_v >> 4) & 0x1)
#define BPORT1_AB_SR_TIF                0x1
#define BPORT1_AB_SR_TIF_GET(_v)        (_v & 0x1)
#define BPORT1_AB_SR_TOF                (0x1 << 1)
#define BPORT1_AB_SR_TOF_GET(_v)        ((_v >> 1) & 0x1)

#define BPORT1_AB_LR_POFFSET            0x18
#define BPORT1_AB_LR                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LR_POFFSET)
#define BPORT1_AB_LR_CRL                (0x1 << 4)
#define BPORT1_AB_LR_CRL_GET(_v)        ((_v >> 4) & 0x1)
#define BPORT1_AB_LR_LRL                (0x1 << 6)
#define BPORT1_AB_LR_LRL_GET(_v)        ((_v >> 6) & 0x1)
#define BPORT1_AB_LR_MCHL               (0x1 << 11)
#define BPORT1_AB_LR_MCHL_GET(_v)       ((_v >> 11) & 0x1)
#define BPORT1_AB_LR_MCLL               (0x1 << 10)
#define BPORT1_AB_LR_MCLL_GET(_v)       ((_v >> 10) & 0x1)
#define BPORT1_AB_LR_MEL                (0x1 << 9)
#define BPORT1_AB_LR_MEL_GET(_v)        ((_v >> 9) & 0x1)
#define BPORT1_AB_LR_SRL                (0x1 << 5)
#define BPORT1_AB_LR_SRL_GET(_v)        ((_v >> 5) & 0x1)
#define BPORT1_AB_LR_TCL                (0x1 << 3)
#define BPORT1_AB_LR_TCL_GET(_v)        ((_v >> 3) & 0x1)
#define BPORT1_AB_LR_TDL                (0x1 << 13)
#define BPORT1_AB_LR_TDL_GET(_v)        ((_v >> 13) & 0x1)
#define BPORT1_AB_LR_TEL                (0x1 << 12)
#define BPORT1_AB_LR_TEL_GET(_v)        ((_v >> 12) & 0x1)
#define BPORT1_AB_LR_TIL                (0x1 << 15)
#define BPORT1_AB_LR_TIL_GET(_v)        ((_v >> 15) & 0x1)
#define BPORT1_AB_LR_TTL                (0x1 << 14)
#define BPORT1_AB_LR_TTL_GET(_v)        ((_v >> 14) & 0x1)
#define BPORT1_AB_LR_TTSL               (0x1 << 8)
#define BPORT1_AB_LR_TTSL_GET(_v)       ((_v >> 8) & 0x1)

#define BPORT1_AB_IER_POFFSET           0x1c
#define BPORT1_AB_IER                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IER_POFFSET)
#define BPORT1_AB_IER_MOIE              (0x1 << 3)
#define BPORT1_AB_IER_MOIE_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_IER_TAIE              (0x1 << 2)
#define BPORT1_AB_IER_TAIE_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_IER_TIIE              0x1
#define BPORT1_AB_IER_TIIE_GET(_v)      (_v & 0x1)
#define BPORT1_AB_IER_TOIE              (0x1 << 1)
#define BPORT1_AB_IER_TOIE_GET(_v)      ((_v >> 1) & 0x1)
#define BPORT1_AB_IER_TSIE              (0x1 << 4)
#define BPORT1_AB_IER_TSIE_GET(_v)      ((_v >> 4) & 0x1)

#define BPORT1_AB_TTSR_POFFSET          0x20
#define BPORT1_AB_TTSR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TTSR_POFFSET)
#define BPORT1_AB_TTSR_TTS              0xffffffff
#define BPORT1_AB_TTSR_TTS_GET(_v)      (_v & 0xffffffff)

#define BPORT1_AB_MER_POFFSET           0x24
#define BPORT1_AB_MER                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MER_POFFSET)
#define BPORT1_AB_MER_MCE               (0x1 << 4)
#define BPORT1_AB_MER_MCE_GET(_v)       ((_v >> 4) & 0x1)

#define BPORT1_AB_MCLR_POFFSET          0x28
#define BPORT1_AB_MCLR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MCLR_POFFSET)
#define BPORT1_AB_MCLR_MCL              0xffffffff
#define BPORT1_AB_MCLR_MCL_GET(_v)      (_v & 0xffffffff)

#define BPORT1_AB_MCHR_POFFSET          0x2c
#define BPORT1_AB_MCHR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MCHR_POFFSET)
#define BPORT1_AB_MCHR_MCH              0xffffffff
#define BPORT1_AB_MCHR_MCH_GET(_v)      (_v & 0xffffffff)

#define BPORT1_AB_TER_POFFSET           0x30
#define BPORT1_AB_TER                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TER_POFFSET)
#define BPORT1_AB_TER_CTE               (0x1 << 2)
#define BPORT1_AB_TER_CTE_GET(_v)       ((_v >> 2) & 0x1)
#define BPORT1_AB_TER_DTE               0x1
#define BPORT1_AB_TER_DTE_GET(_v)       (_v & 0x1)
#define BPORT1_AB_TER_FSE               (0x1 << 4)
#define BPORT1_AB_TER_FSE_GET(_v)       ((_v >> 4) & 0x1)
#define BPORT1_AB_TER_TME               (0x1 << 5)
#define BPORT1_AB_TER_TME_GET(_v)       ((_v >> 5) & 0x1)
#define BPORT1_AB_TER_TTE               (0x1 << 3)
#define BPORT1_AB_TER_TTE_GET(_v)       ((_v >> 3) & 0x1)
#define BPORT1_AB_TER_VTE               (0x1 << 1)
#define BPORT1_AB_TER_VTE_GET(_v)       ((_v >> 1) & 0x1)

#define BPORT1_AB_TDR_POFFSET           0x34
#define BPORT1_AB_TDR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TDR_POFFSET)
#define BPORT1_AB_TDR_CTF               (0x1 << 2)
#define BPORT1_AB_TDR_CTF_GET(_v)       ((_v >> 2) & 0x1)
#define BPORT1_AB_TDR_DTF               0x1
#define BPORT1_AB_TDR_DTF_GET(_v)       (_v & 0x1)
#define BPORT1_AB_TDR_FSF               (0x1 << 4)
#define BPORT1_AB_TDR_FSF_GET(_v)       ((_v >> 4) & 0x1)
#define BPORT1_AB_TDR_TMF               (0x1 << 5)
#define BPORT1_AB_TDR_TMF_GET(_v)       ((_v >> 5) & 0x1)
#define BPORT1_AB_TDR_TTF               (0x1 << 3)
#define BPORT1_AB_TDR_TTF_GET(_v)       ((_v >> 3) & 0x1)
#define BPORT1_AB_TDR_VTF               (0x1 << 1)
#define BPORT1_AB_TDR_VTF_GET(_v)       ((_v >> 1) & 0x1)

#define BPORT1_AB_TTR_POFFSET           0x38
#define BPORT1_AB_TTR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TTR_POFFSET)
#define BPORT1_AB_TTR_CDTH              (0x7 << 6)
#define BPORT1_AB_TTR_CDTH_GET(_v)      ((_v >> 6) & 0x7)
#define BPORT1_AB_TTR_CDTL              (0x7 << 9)
#define BPORT1_AB_TTR_CDTL_GET(_v)      ((_v >> 9) & 0x7)
#define BPORT1_AB_TTR_TDTH              (0x7 << 12)
#define BPORT1_AB_TTR_TDTH_GET(_v)      ((_v >> 12) & 0x7)
#define BPORT1_AB_TTR_TDTL              (0x7 << 15)
#define BPORT1_AB_TTR_TDTL_GET(_v)      ((_v >> 15) & 0x7)
#define BPORT1_AB_TTR_VDTH              (0x7 << 3)
#define BPORT1_AB_TTR_VDTH_GET(_v)      ((_v >> 3) & 0x7)
#define BPORT1_AB_TTR_VDTL              0x7
#define BPORT1_AB_TTR_VDTL_GET(_v)      (_v & 0x7)

#define BPORT1_AB_TIR_POFFSET           0x3c
#define BPORT1_AB_TIR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TIR_POFFSET)
#define BPORT1_AB_TIR_CTIE              (0x1 << 2)
#define BPORT1_AB_TIR_CTIE_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_TIR_DTIE              0x1
#define BPORT1_AB_TIR_DTIE_GET(_v)      (_v & 0x1)
#define BPORT1_AB_TIR_FSIE              (0x1 << 4)
#define BPORT1_AB_TIR_FSIE_GET(_v)      ((_v >> 4) & 0x1)
#define BPORT1_AB_TIR_TMIE              (0x1 << 5)
#define BPORT1_AB_TIR_TMIE_GET(_v)      ((_v >> 5) & 0x1)
#define BPORT1_AB_TIR_TTIE              (0x1 << 3)
#define BPORT1_AB_TIR_TTIE_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_TIR_VTIE              (0x1 << 1)
#define BPORT1_AB_TIR_VTIE_GET(_v)      ((_v >> 1) & 0x1)

#define BPORT1_AB_WAR_POFFSET           0x800
#define BPORT1_AB_WAR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WAR_POFFSET)
#define BPORT1_AB_WAR_CRW               (0x1 << 4)
#define BPORT1_AB_WAR_CRW_GET(_v)       ((_v >> 4) & 0x1)
#define BPORT1_AB_WAR_IERW              (0x1 << 7)
#define BPORT1_AB_WAR_IERW_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_WAR_LRW               (0x1 << 6)
#define BPORT1_AB_WAR_LRW_GET(_v)       ((_v >> 6) & 0x1)
#define BPORT1_AB_WAR_MCHW              (0x1 << 11)
#define BPORT1_AB_WAR_MCHW_GET(_v)      ((_v >> 11) & 0x1)
#define BPORT1_AB_WAR_MCLW              (0x1 << 10)
#define BPORT1_AB_WAR_MCLW_GET(_v)      ((_v >> 10) & 0x1)
#define BPORT1_AB_WAR_MERW              (0x1 << 9)
#define BPORT1_AB_WAR_MERW_GET(_v)      ((_v >> 9) & 0x1)
#define BPORT1_AB_WAR_SRW               (0x1 << 5)
#define BPORT1_AB_WAR_SRW_GET(_v)       ((_v >> 5) & 0x1)
#define BPORT1_AB_WAR_TARW              (0x1 << 2)
#define BPORT1_AB_WAR_TARW_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_WAR_TCRW              (0x1 << 3)
#define BPORT1_AB_WAR_TCRW_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_WAR_TDRW              (0x1 << 13)
#define BPORT1_AB_WAR_TDRW_GET(_v)      ((_v >> 13) & 0x1)
#define BPORT1_AB_WAR_TERW              (0x1 << 12)
#define BPORT1_AB_WAR_TERW_GET(_v)      ((_v >> 12) & 0x1)
#define BPORT1_AB_WAR_TIRW              (0x1 << 15)
#define BPORT1_AB_WAR_TIRW_GET(_v)      ((_v >> 15) & 0x1)
#define BPORT1_AB_WAR_TPRW              (0x1 << 1)
#define BPORT1_AB_WAR_TPRW_GET(_v)      ((_v >> 1) & 0x1)
#define BPORT1_AB_WAR_TSRW              0x1
#define BPORT1_AB_WAR_TSRW_GET(_v)      (_v & 0x1)
#define BPORT1_AB_WAR_TTRW              (0x1 << 14)
#define BPORT1_AB_WAR_TTRW_GET(_v)      ((_v >> 14) & 0x1)
#define BPORT1_AB_WAR_TTSW              (0x1 << 8)
#define BPORT1_AB_WAR_TTSW_GET(_v)      ((_v >> 8) & 0x1)

#define BPORT1_AB_RAR_POFFSET           0x804
#define BPORT1_AB_RAR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RAR_POFFSET)
#define BPORT1_AB_RAR_CRR               (0x1 << 4)
#define BPORT1_AB_RAR_CRR_GET(_v)       ((_v >> 4) & 0x1)
#define BPORT1_AB_RAR_IERR              (0x1 << 7)
#define BPORT1_AB_RAR_IERR_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_RAR_LRR               (0x1 << 6)
#define BPORT1_AB_RAR_LRR_GET(_v)       ((_v >> 6) & 0x1)
#define BPORT1_AB_RAR_MCHR              (0x1 << 11)
#define BPORT1_AB_RAR_MCHR_GET(_v)      ((_v >> 11) & 0x1)
#define BPORT1_AB_RAR_MCLR              (0x1 << 10)
#define BPORT1_AB_RAR_MCLR_GET(_v)      ((_v >> 10) & 0x1)
#define BPORT1_AB_RAR_MERR              (0x1 << 9)
#define BPORT1_AB_RAR_MERR_GET(_v)      ((_v >> 9) & 0x1)
#define BPORT1_AB_RAR_SRR               (0x1 << 5)
#define BPORT1_AB_RAR_SRR_GET(_v)       ((_v >> 5) & 0x1)
#define BPORT1_AB_RAR_TARR              (0x1 << 2)
#define BPORT1_AB_RAR_TARR_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_RAR_TCRR              (0x1 << 3)
#define BPORT1_AB_RAR_TCRR_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_RAR_TDRR              (0x1 << 13)
#define BPORT1_AB_RAR_TDRR_GET(_v)      ((_v >> 13) & 0x1)
#define BPORT1_AB_RAR_TERR              (0x1 << 12)
#define BPORT1_AB_RAR_TERR_GET(_v)      ((_v >> 12) & 0x1)
#define BPORT1_AB_RAR_TIRR              (0x1 << 15)
#define BPORT1_AB_RAR_TIRR_GET(_v)      ((_v >> 15) & 0x1)
#define BPORT1_AB_RAR_TPRR              (0x1 << 1)
#define BPORT1_AB_RAR_TPRR_GET(_v)      ((_v >> 1) & 0x1)
#define BPORT1_AB_RAR_TSRR              0x1
#define BPORT1_AB_RAR_TSRR_GET(_v)      (_v & 0x1)
#define BPORT1_AB_RAR_TTRR              (0x1 << 14)
#define BPORT1_AB_RAR_TTRR_GET(_v)      ((_v >> 14) & 0x1)
#define BPORT1_AB_RAR_TTSR              (0x1 << 8)
#define BPORT1_AB_RAR_TTSR_GET(_v)      ((_v >> 8) & 0x1)


#endif

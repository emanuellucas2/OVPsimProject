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
#define BPORT1_AB_TCSR_POFFSET          0x0
#define BPORT1_AB_TCSR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCSR_POFFSET)
#define BPORT1_AB_TCSR_BCE              (0x1 << 28)
#define BPORT1_AB_TCSR_BCE_GET(_v)      ((_v >> 28) & 0x1)
#define BPORT1_AB_TCSR_DBGE             (0x1 << 29)
#define BPORT1_AB_TCSR_DBGE_GET(_v)     ((_v >> 29) & 0x1)
#define BPORT1_AB_TCSR_FEF              (0x1 << 18)
#define BPORT1_AB_TCSR_FEF_GET(_v)      ((_v >> 18) & 0x1)
#define BPORT1_AB_TCSR_FEIE             (0x1 << 10)
#define BPORT1_AB_TCSR_FEIE_GET(_v)     ((_v >> 10) & 0x1)
#define BPORT1_AB_TCSR_FR               (0x1 << 25)
#define BPORT1_AB_TCSR_FR_GET(_v)       ((_v >> 25) & 0x1)
#define BPORT1_AB_TCSR_FRDE             0x1
#define BPORT1_AB_TCSR_FRDE_GET(_v)     (_v & 0x1)
#define BPORT1_AB_TCSR_FRF              (0x1 << 16)
#define BPORT1_AB_TCSR_FRF_GET(_v)      ((_v >> 16) & 0x1)
#define BPORT1_AB_TCSR_FRIE             (0x1 << 8)
#define BPORT1_AB_TCSR_FRIE_GET(_v)     ((_v >> 8) & 0x1)
#define BPORT1_AB_TCSR_FWDE             (0x1 << 1)
#define BPORT1_AB_TCSR_FWDE_GET(_v)     ((_v >> 1) & 0x1)
#define BPORT1_AB_TCSR_FWF              (0x1 << 17)
#define BPORT1_AB_TCSR_FWF_GET(_v)      ((_v >> 17) & 0x1)
#define BPORT1_AB_TCSR_FWIE             (0x1 << 9)
#define BPORT1_AB_TCSR_FWIE_GET(_v)     ((_v >> 9) & 0x1)
#define BPORT1_AB_TCSR_SEF              (0x1 << 19)
#define BPORT1_AB_TCSR_SEF_GET(_v)      ((_v >> 19) & 0x1)
#define BPORT1_AB_TCSR_SEIE             (0x1 << 11)
#define BPORT1_AB_TCSR_SEIE_GET(_v)     ((_v >> 11) & 0x1)
#define BPORT1_AB_TCSR_SR               (0x1 << 24)
#define BPORT1_AB_TCSR_SR_GET(_v)       ((_v >> 24) & 0x1)
#define BPORT1_AB_TCSR_STOPE            (0x1 << 30)
#define BPORT1_AB_TCSR_STOPE_GET(_v)    ((_v >> 30) & 0x1)
#define BPORT1_AB_TCSR_TE               (0x1 << 31)
#define BPORT1_AB_TCSR_TE_GET(_v)       ((_v >> 31) & 0x1)
#define BPORT1_AB_TCSR_WSF              (0x1 << 20)
#define BPORT1_AB_TCSR_WSF_GET(_v)      ((_v >> 20) & 0x1)
#define BPORT1_AB_TCSR_WSIE             (0x1 << 12)
#define BPORT1_AB_TCSR_WSIE_GET(_v)     ((_v >> 12) & 0x1)

#define BPORT1_AB_TCR1_POFFSET          0x4
#define BPORT1_AB_TCR1                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCR1_POFFSET)
#define BPORT1_AB_TCR1_TFW              0x7
#define BPORT1_AB_TCR1_TFW_GET(_v)      (_v & 0x7)

#define BPORT1_AB_TCR2_POFFSET          0x8
#define BPORT1_AB_TCR2                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCR2_POFFSET)
#define BPORT1_AB_TCR2_BCD              (0x1 << 24)
#define BPORT1_AB_TCR2_BCD_GET(_v)      ((_v >> 24) & 0x1)
#define BPORT1_AB_TCR2_BCI              (0x1 << 28)
#define BPORT1_AB_TCR2_BCI_GET(_v)      ((_v >> 28) & 0x1)
#define BPORT1_AB_TCR2_BCP              (0x1 << 25)
#define BPORT1_AB_TCR2_BCP_GET(_v)      ((_v >> 25) & 0x1)
#define BPORT1_AB_TCR2_BCS              (0x1 << 29)
#define BPORT1_AB_TCR2_BCS_GET(_v)      ((_v >> 29) & 0x1)
#define BPORT1_AB_TCR2_DIV              0xff
#define BPORT1_AB_TCR2_DIV_GET(_v)      (_v & 0xff)
#define BPORT1_AB_TCR2_MSEL             (0x3 << 26)
#define BPORT1_AB_TCR2_MSEL_GET(_v)     ((_v >> 26) & 0x3)
#define BPORT1_AB_TCR2_SYNC             (0x3 << 30)
#define BPORT1_AB_TCR2_SYNC_GET(_v)     ((_v >> 30) & 0x3)

#define BPORT1_AB_TCR3_POFFSET          0xc
#define BPORT1_AB_TCR3                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCR3_POFFSET)
#define BPORT1_AB_TCR3_TCE              (0x3 << 16)
#define BPORT1_AB_TCR3_TCE_GET(_v)      ((_v >> 16) & 0x3)
#define BPORT1_AB_TCR3_WDFL             0x1f
#define BPORT1_AB_TCR3_WDFL_GET(_v)     (_v & 0x1f)

#define BPORT1_AB_TCR4_POFFSET          0x10
#define BPORT1_AB_TCR4                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCR4_POFFSET)
#define BPORT1_AB_TCR4_FRSZ             (0x1f << 16)
#define BPORT1_AB_TCR4_FRSZ_GET(_v)     ((_v >> 16) & 0x1f)
#define BPORT1_AB_TCR4_FSD              0x1
#define BPORT1_AB_TCR4_FSD_GET(_v)      (_v & 0x1)
#define BPORT1_AB_TCR4_FSE              (0x1 << 3)
#define BPORT1_AB_TCR4_FSE_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_TCR4_FSP              (0x1 << 1)
#define BPORT1_AB_TCR4_FSP_GET(_v)      ((_v >> 1) & 0x1)
#define BPORT1_AB_TCR4_MF               (0x1 << 4)
#define BPORT1_AB_TCR4_MF_GET(_v)       ((_v >> 4) & 0x1)
#define BPORT1_AB_TCR4_SYWD             (0x1f << 8)
#define BPORT1_AB_TCR4_SYWD_GET(_v)     ((_v >> 8) & 0x1f)

#define BPORT1_AB_TCR5_POFFSET          0x14
#define BPORT1_AB_TCR5                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCR5_POFFSET)
#define BPORT1_AB_TCR5_FBT              (0x1f << 8)
#define BPORT1_AB_TCR5_FBT_GET(_v)      ((_v >> 8) & 0x1f)
#define BPORT1_AB_TCR5_W0W              (0x1f << 16)
#define BPORT1_AB_TCR5_W0W_GET(_v)      ((_v >> 16) & 0x1f)
#define BPORT1_AB_TCR5_WNW              (0x1f << 24)
#define BPORT1_AB_TCR5_WNW_GET(_v)      ((_v >> 24) & 0x1f)

#define BPORT1_AB_TDR0_POFFSET          0x20
#define BPORT1_AB_TDR0                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TDR0_POFFSET)
#define BPORT1_AB_TDR0_TDR              0xffffffff
#define BPORT1_AB_TDR0_TDR_GET(_v)      (_v & 0xffffffff)

#define BPORT1_AB_TDR1_POFFSET          0x24
#define BPORT1_AB_TDR1                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TDR1_POFFSET)
#define BPORT1_AB_TDR1_TDR              0xffffffff
#define BPORT1_AB_TDR1_TDR_GET(_v)      (_v & 0xffffffff)

#define BPORT1_AB_TFR0_POFFSET          0x40
#define BPORT1_AB_TFR0                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TFR0_POFFSET)
#define BPORT1_AB_TFR0_RFP              0xf
#define BPORT1_AB_TFR0_RFP_GET(_v)      (_v & 0xf)
#define BPORT1_AB_TFR0_WFP              (0xf << 16)
#define BPORT1_AB_TFR0_WFP_GET(_v)      ((_v >> 16) & 0xf)

#define BPORT1_AB_TFR1_POFFSET          0x44
#define BPORT1_AB_TFR1                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TFR1_POFFSET)
#define BPORT1_AB_TFR1_RFP              0xf
#define BPORT1_AB_TFR1_RFP_GET(_v)      (_v & 0xf)
#define BPORT1_AB_TFR1_WFP              (0xf << 16)
#define BPORT1_AB_TFR1_WFP_GET(_v)      ((_v >> 16) & 0xf)

#define BPORT1_AB_TMR_POFFSET           0x60
#define BPORT1_AB_TMR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TMR_POFFSET)
#define BPORT1_AB_TMR_TWM               0xffffffff
#define BPORT1_AB_TMR_TWM_GET(_v)       (_v & 0xffffffff)

#define BPORT1_AB_RCSR_POFFSET          0x80
#define BPORT1_AB_RCSR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RCSR_POFFSET)
#define BPORT1_AB_RCSR_BCE              (0x1 << 28)
#define BPORT1_AB_RCSR_BCE_GET(_v)      ((_v >> 28) & 0x1)
#define BPORT1_AB_RCSR_DBGE             (0x1 << 29)
#define BPORT1_AB_RCSR_DBGE_GET(_v)     ((_v >> 29) & 0x1)
#define BPORT1_AB_RCSR_FEF              (0x1 << 18)
#define BPORT1_AB_RCSR_FEF_GET(_v)      ((_v >> 18) & 0x1)
#define BPORT1_AB_RCSR_FEIE             (0x1 << 10)
#define BPORT1_AB_RCSR_FEIE_GET(_v)     ((_v >> 10) & 0x1)
#define BPORT1_AB_RCSR_FR               (0x1 << 25)
#define BPORT1_AB_RCSR_FR_GET(_v)       ((_v >> 25) & 0x1)
#define BPORT1_AB_RCSR_FRDE             0x1
#define BPORT1_AB_RCSR_FRDE_GET(_v)     (_v & 0x1)
#define BPORT1_AB_RCSR_FRF              (0x1 << 16)
#define BPORT1_AB_RCSR_FRF_GET(_v)      ((_v >> 16) & 0x1)
#define BPORT1_AB_RCSR_FRIE             (0x1 << 8)
#define BPORT1_AB_RCSR_FRIE_GET(_v)     ((_v >> 8) & 0x1)
#define BPORT1_AB_RCSR_FWDE             (0x1 << 1)
#define BPORT1_AB_RCSR_FWDE_GET(_v)     ((_v >> 1) & 0x1)
#define BPORT1_AB_RCSR_FWF              (0x1 << 17)
#define BPORT1_AB_RCSR_FWF_GET(_v)      ((_v >> 17) & 0x1)
#define BPORT1_AB_RCSR_FWIE             (0x1 << 9)
#define BPORT1_AB_RCSR_FWIE_GET(_v)     ((_v >> 9) & 0x1)
#define BPORT1_AB_RCSR_RE               (0x1 << 31)
#define BPORT1_AB_RCSR_RE_GET(_v)       ((_v >> 31) & 0x1)
#define BPORT1_AB_RCSR_SEF              (0x1 << 19)
#define BPORT1_AB_RCSR_SEF_GET(_v)      ((_v >> 19) & 0x1)
#define BPORT1_AB_RCSR_SEIE             (0x1 << 11)
#define BPORT1_AB_RCSR_SEIE_GET(_v)     ((_v >> 11) & 0x1)
#define BPORT1_AB_RCSR_SR               (0x1 << 24)
#define BPORT1_AB_RCSR_SR_GET(_v)       ((_v >> 24) & 0x1)
#define BPORT1_AB_RCSR_STOPE            (0x1 << 30)
#define BPORT1_AB_RCSR_STOPE_GET(_v)    ((_v >> 30) & 0x1)
#define BPORT1_AB_RCSR_WSF              (0x1 << 20)
#define BPORT1_AB_RCSR_WSF_GET(_v)      ((_v >> 20) & 0x1)
#define BPORT1_AB_RCSR_WSIE             (0x1 << 12)
#define BPORT1_AB_RCSR_WSIE_GET(_v)     ((_v >> 12) & 0x1)

#define BPORT1_AB_RCR1_POFFSET          0x84
#define BPORT1_AB_RCR1                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RCR1_POFFSET)
#define BPORT1_AB_RCR1_RFW              0x7
#define BPORT1_AB_RCR1_RFW_GET(_v)      (_v & 0x7)

#define BPORT1_AB_RCR2_POFFSET          0x88
#define BPORT1_AB_RCR2                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RCR2_POFFSET)
#define BPORT1_AB_RCR2_BCD              (0x1 << 24)
#define BPORT1_AB_RCR2_BCD_GET(_v)      ((_v >> 24) & 0x1)
#define BPORT1_AB_RCR2_BCI              (0x1 << 28)
#define BPORT1_AB_RCR2_BCI_GET(_v)      ((_v >> 28) & 0x1)
#define BPORT1_AB_RCR2_BCP              (0x1 << 25)
#define BPORT1_AB_RCR2_BCP_GET(_v)      ((_v >> 25) & 0x1)
#define BPORT1_AB_RCR2_BCS              (0x1 << 29)
#define BPORT1_AB_RCR2_BCS_GET(_v)      ((_v >> 29) & 0x1)
#define BPORT1_AB_RCR2_DIV              0xff
#define BPORT1_AB_RCR2_DIV_GET(_v)      (_v & 0xff)
#define BPORT1_AB_RCR2_MSEL             (0x3 << 26)
#define BPORT1_AB_RCR2_MSEL_GET(_v)     ((_v >> 26) & 0x3)
#define BPORT1_AB_RCR2_SYNC             (0x3 << 30)
#define BPORT1_AB_RCR2_SYNC_GET(_v)     ((_v >> 30) & 0x3)

#define BPORT1_AB_RCR3_POFFSET          0x8c
#define BPORT1_AB_RCR3                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RCR3_POFFSET)
#define BPORT1_AB_RCR3_RCE              (0x3 << 16)
#define BPORT1_AB_RCR3_RCE_GET(_v)      ((_v >> 16) & 0x3)
#define BPORT1_AB_RCR3_WDFL             0x1f
#define BPORT1_AB_RCR3_WDFL_GET(_v)     (_v & 0x1f)

#define BPORT1_AB_RCR4_POFFSET          0x90
#define BPORT1_AB_RCR4                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RCR4_POFFSET)
#define BPORT1_AB_RCR4_FRSZ             (0x1f << 16)
#define BPORT1_AB_RCR4_FRSZ_GET(_v)     ((_v >> 16) & 0x1f)
#define BPORT1_AB_RCR4_FSD              0x1
#define BPORT1_AB_RCR4_FSD_GET(_v)      (_v & 0x1)
#define BPORT1_AB_RCR4_FSE              (0x1 << 3)
#define BPORT1_AB_RCR4_FSE_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_RCR4_FSP              (0x1 << 1)
#define BPORT1_AB_RCR4_FSP_GET(_v)      ((_v >> 1) & 0x1)
#define BPORT1_AB_RCR4_MF               (0x1 << 4)
#define BPORT1_AB_RCR4_MF_GET(_v)       ((_v >> 4) & 0x1)
#define BPORT1_AB_RCR4_SYWD             (0x1f << 8)
#define BPORT1_AB_RCR4_SYWD_GET(_v)     ((_v >> 8) & 0x1f)

#define BPORT1_AB_RCR5_POFFSET          0x94
#define BPORT1_AB_RCR5                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RCR5_POFFSET)
#define BPORT1_AB_RCR5_FBT              (0x1f << 8)
#define BPORT1_AB_RCR5_FBT_GET(_v)      ((_v >> 8) & 0x1f)
#define BPORT1_AB_RCR5_W0W              (0x1f << 16)
#define BPORT1_AB_RCR5_W0W_GET(_v)      ((_v >> 16) & 0x1f)
#define BPORT1_AB_RCR5_WNW              (0x1f << 24)
#define BPORT1_AB_RCR5_WNW_GET(_v)      ((_v >> 24) & 0x1f)

#define BPORT1_AB_RDR0_POFFSET          0xa0
#define BPORT1_AB_RDR0                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RDR0_POFFSET)
#define BPORT1_AB_RDR0_RDR              0xffffffff
#define BPORT1_AB_RDR0_RDR_GET(_v)      (_v & 0xffffffff)

#define BPORT1_AB_RDR1_POFFSET          0xa4
#define BPORT1_AB_RDR1                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RDR1_POFFSET)
#define BPORT1_AB_RDR1_RDR              0xffffffff
#define BPORT1_AB_RDR1_RDR_GET(_v)      (_v & 0xffffffff)

#define BPORT1_AB_RFR0_POFFSET          0xc0
#define BPORT1_AB_RFR0                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RFR0_POFFSET)
#define BPORT1_AB_RFR0_RFP              0xf
#define BPORT1_AB_RFR0_RFP_GET(_v)      (_v & 0xf)
#define BPORT1_AB_RFR0_WFP              (0xf << 16)
#define BPORT1_AB_RFR0_WFP_GET(_v)      ((_v >> 16) & 0xf)

#define BPORT1_AB_RFR1_POFFSET          0xc4
#define BPORT1_AB_RFR1                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RFR1_POFFSET)
#define BPORT1_AB_RFR1_RFP              0xf
#define BPORT1_AB_RFR1_RFP_GET(_v)      (_v & 0xf)
#define BPORT1_AB_RFR1_WFP              (0xf << 16)
#define BPORT1_AB_RFR1_WFP_GET(_v)      ((_v >> 16) & 0xf)

#define BPORT1_AB_RMR_POFFSET           0xe0
#define BPORT1_AB_RMR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMR_POFFSET)
#define BPORT1_AB_RMR_RWM               0xffffffff
#define BPORT1_AB_RMR_RWM_GET(_v)       (_v & 0xffffffff)

#define BPORT1_AB_MCR_POFFSET           0x100
#define BPORT1_AB_MCR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MCR_POFFSET)
#define BPORT1_AB_MCR_DUF               (0x1 << 31)
#define BPORT1_AB_MCR_DUF_GET(_v)       ((_v >> 31) & 0x1)
#define BPORT1_AB_MCR_MICS              (0x3 << 24)
#define BPORT1_AB_MCR_MICS_GET(_v)      ((_v >> 24) & 0x3)
#define BPORT1_AB_MCR_MOE               (0x1 << 30)
#define BPORT1_AB_MCR_MOE_GET(_v)       ((_v >> 30) & 0x1)

#define BPORT1_AB_MDR_POFFSET           0x104
#define BPORT1_AB_MDR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MDR_POFFSET)
#define BPORT1_AB_MDR_DIVIDE            0xfff
#define BPORT1_AB_MDR_DIVIDE_GET(_v)    (_v & 0xfff)
#define BPORT1_AB_MDR_FRACT             (0xff << 12)
#define BPORT1_AB_MDR_FRACT_GET(_v)     ((_v >> 12) & 0xff)


#endif

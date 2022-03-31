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
#define BPORT1_AB_BDH_POFFSET           0x0
#define BPORT1_AB_BDH                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BDH_POFFSET)
#define BPORT1_AB_BDH_LBKDIE            (0x1 << 7)
#define BPORT1_AB_BDH_LBKDIE_GET(_v)    ((_v >> 7) & 0x1)
#define BPORT1_AB_BDH_RXEDGIE           (0x1 << 6)
#define BPORT1_AB_BDH_RXEDGIE_GET(_v)   ((_v >> 6) & 0x1)
#define BPORT1_AB_BDH_SBR               0x1f
#define BPORT1_AB_BDH_SBR_GET(_v)       (_v & 0x1f)

#define BPORT1_AB_BDL_POFFSET           0x1
#define BPORT1_AB_BDL                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BDL_POFFSET)
#define BPORT1_AB_BDL_SBR               0xff
#define BPORT1_AB_BDL_SBR_GET(_v)       (_v & 0xff)

#define BPORT1_AB_C1_POFFSET            0x2
#define BPORT1_AB_C1                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C1_POFFSET)
#define BPORT1_AB_C1_ILT                (0x1 << 2)
#define BPORT1_AB_C1_ILT_GET(_v)        ((_v >> 2) & 0x1)
#define BPORT1_AB_C1_LOOPS              (0x1 << 7)
#define BPORT1_AB_C1_LOOPS_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_C1_M                  (0x1 << 4)
#define BPORT1_AB_C1_M_GET(_v)          ((_v >> 4) & 0x1)
#define BPORT1_AB_C1_PE                 (0x1 << 1)
#define BPORT1_AB_C1_PE_GET(_v)         ((_v >> 1) & 0x1)
#define BPORT1_AB_C1_PT                 0x1
#define BPORT1_AB_C1_PT_GET(_v)         (_v & 0x1)
#define BPORT1_AB_C1_RSRC               (0x1 << 5)
#define BPORT1_AB_C1_RSRC_GET(_v)       ((_v >> 5) & 0x1)
#define BPORT1_AB_C1_UARTSWAI           (0x1 << 6)
#define BPORT1_AB_C1_UARTSWAI_GET(_v)   ((_v >> 6) & 0x1)
#define BPORT1_AB_C1_WAKE               (0x1 << 3)
#define BPORT1_AB_C1_WAKE_GET(_v)       ((_v >> 3) & 0x1)

#define BPORT1_AB_C2_POFFSET            0x3
#define BPORT1_AB_C2                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C2_POFFSET)
#define BPORT1_AB_C2_ILIE               (0x1 << 4)
#define BPORT1_AB_C2_ILIE_GET(_v)       ((_v >> 4) & 0x1)
#define BPORT1_AB_C2_RE                 (0x1 << 2)
#define BPORT1_AB_C2_RE_GET(_v)         ((_v >> 2) & 0x1)
#define BPORT1_AB_C2_RIE                (0x1 << 5)
#define BPORT1_AB_C2_RIE_GET(_v)        ((_v >> 5) & 0x1)
#define BPORT1_AB_C2_RWU                (0x1 << 1)
#define BPORT1_AB_C2_RWU_GET(_v)        ((_v >> 1) & 0x1)
#define BPORT1_AB_C2_SBK                0x1
#define BPORT1_AB_C2_SBK_GET(_v)        (_v & 0x1)
#define BPORT1_AB_C2_TCIE               (0x1 << 6)
#define BPORT1_AB_C2_TCIE_GET(_v)       ((_v >> 6) & 0x1)
#define BPORT1_AB_C2_TE                 (0x1 << 3)
#define BPORT1_AB_C2_TE_GET(_v)         ((_v >> 3) & 0x1)
#define BPORT1_AB_C2_TIE                (0x1 << 7)
#define BPORT1_AB_C2_TIE_GET(_v)        ((_v >> 7) & 0x1)

#define BPORT1_AB_S1_POFFSET            0x4
#define BPORT1_AB_S1                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_S1_POFFSET)
#define BPORT1_AB_S1_FE                 (0x1 << 1)
#define BPORT1_AB_S1_FE_GET(_v)         ((_v >> 1) & 0x1)
#define BPORT1_AB_S1_IDLE               (0x1 << 4)
#define BPORT1_AB_S1_IDLE_GET(_v)       ((_v >> 4) & 0x1)
#define BPORT1_AB_S1_NF                 (0x1 << 2)
#define BPORT1_AB_S1_NF_GET(_v)         ((_v >> 2) & 0x1)
#define BPORT1_AB_S1_OR                 (0x1 << 3)
#define BPORT1_AB_S1_OR_GET(_v)         ((_v >> 3) & 0x1)
#define BPORT1_AB_S1_PF                 0x1
#define BPORT1_AB_S1_PF_GET(_v)         (_v & 0x1)
#define BPORT1_AB_S1_RDRF               (0x1 << 5)
#define BPORT1_AB_S1_RDRF_GET(_v)       ((_v >> 5) & 0x1)
#define BPORT1_AB_S1_TC                 (0x1 << 6)
#define BPORT1_AB_S1_TC_GET(_v)         ((_v >> 6) & 0x1)
#define BPORT1_AB_S1_TDRE               (0x1 << 7)
#define BPORT1_AB_S1_TDRE_GET(_v)       ((_v >> 7) & 0x1)

#define BPORT1_AB_S2_POFFSET            0x5
#define BPORT1_AB_S2                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_S2_POFFSET)
#define BPORT1_AB_S2_BRK13              (0x1 << 2)
#define BPORT1_AB_S2_BRK13_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_S2_LBKDE              (0x1 << 1)
#define BPORT1_AB_S2_LBKDE_GET(_v)      ((_v >> 1) & 0x1)
#define BPORT1_AB_S2_LBKDIF             (0x1 << 7)
#define BPORT1_AB_S2_LBKDIF_GET(_v)     ((_v >> 7) & 0x1)
#define BPORT1_AB_S2_MSBF               (0x1 << 5)
#define BPORT1_AB_S2_MSBF_GET(_v)       ((_v >> 5) & 0x1)
#define BPORT1_AB_S2_RAF                0x1
#define BPORT1_AB_S2_RAF_GET(_v)        (_v & 0x1)
#define BPORT1_AB_S2_RWUID              (0x1 << 3)
#define BPORT1_AB_S2_RWUID_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_S2_RXEDGIF            (0x1 << 6)
#define BPORT1_AB_S2_RXEDGIF_GET(_v)    ((_v >> 6) & 0x1)
#define BPORT1_AB_S2_RXINV              (0x1 << 4)
#define BPORT1_AB_S2_RXINV_GET(_v)      ((_v >> 4) & 0x1)

#define BPORT1_AB_C3_POFFSET            0x6
#define BPORT1_AB_C3                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C3_POFFSET)
#define BPORT1_AB_C3_FEIE               (0x1 << 1)
#define BPORT1_AB_C3_FEIE_GET(_v)       ((_v >> 1) & 0x1)
#define BPORT1_AB_C3_NEIE               (0x1 << 2)
#define BPORT1_AB_C3_NEIE_GET(_v)       ((_v >> 2) & 0x1)
#define BPORT1_AB_C3_ORIE               (0x1 << 3)
#define BPORT1_AB_C3_ORIE_GET(_v)       ((_v >> 3) & 0x1)
#define BPORT1_AB_C3_PEIE               0x1
#define BPORT1_AB_C3_PEIE_GET(_v)       (_v & 0x1)
#define BPORT1_AB_C3_R8                 (0x1 << 7)
#define BPORT1_AB_C3_R8_GET(_v)         ((_v >> 7) & 0x1)
#define BPORT1_AB_C3_T8                 (0x1 << 6)
#define BPORT1_AB_C3_T8_GET(_v)         ((_v >> 6) & 0x1)
#define BPORT1_AB_C3_TXDIR              (0x1 << 5)
#define BPORT1_AB_C3_TXDIR_GET(_v)      ((_v >> 5) & 0x1)
#define BPORT1_AB_C3_TXINV              (0x1 << 4)
#define BPORT1_AB_C3_TXINV_GET(_v)      ((_v >> 4) & 0x1)

#define BPORT1_AB_D_POFFSET             0x7
#define BPORT1_AB_D                     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_D_POFFSET)
#define BPORT1_AB_D_RT                  0xff
#define BPORT1_AB_D_RT_GET(_v)          (_v & 0xff)

#define BPORT1_AB_MA1_POFFSET           0x8
#define BPORT1_AB_MA1                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MA1_POFFSET)
#define BPORT1_AB_MA1_MA                0xff
#define BPORT1_AB_MA1_MA_GET(_v)        (_v & 0xff)

#define BPORT1_AB_MA2_POFFSET           0x9
#define BPORT1_AB_MA2                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MA2_POFFSET)
#define BPORT1_AB_MA2_MA                0xff
#define BPORT1_AB_MA2_MA_GET(_v)        (_v & 0xff)

#define BPORT1_AB_C4_POFFSET            0xa
#define BPORT1_AB_C4                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C4_POFFSET)
#define BPORT1_AB_C4_BRFA               0x1f
#define BPORT1_AB_C4_BRFA_GET(_v)       (_v & 0x1f)
#define BPORT1_AB_C4_M10                (0x1 << 5)
#define BPORT1_AB_C4_M10_GET(_v)        ((_v >> 5) & 0x1)
#define BPORT1_AB_C4_MAEN1              (0x1 << 7)
#define BPORT1_AB_C4_MAEN1_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_C4_MAEN2              (0x1 << 6)
#define BPORT1_AB_C4_MAEN2_GET(_v)      ((_v >> 6) & 0x1)

#define BPORT1_AB_C5_POFFSET            0xb
#define BPORT1_AB_C5                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C5_POFFSET)
#define BPORT1_AB_C5_RDMAS              (0x1 << 5)
#define BPORT1_AB_C5_RDMAS_GET(_v)      ((_v >> 5) & 0x1)
#define BPORT1_AB_C5_TDMAS              (0x1 << 7)
#define BPORT1_AB_C5_TDMAS_GET(_v)      ((_v >> 7) & 0x1)

#define BPORT1_AB_ED_POFFSET            0xc
#define BPORT1_AB_ED                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ED_POFFSET)
#define BPORT1_AB_ED_NOISY              (0x1 << 7)
#define BPORT1_AB_ED_NOISY_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_ED_PARITYE            (0x1 << 6)
#define BPORT1_AB_ED_PARITYE_GET(_v)    ((_v >> 6) & 0x1)

#define BPORT1_AB_MODEM_POFFSET         0xd
#define BPORT1_AB_MODEM                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MODEM_POFFSET)
#define BPORT1_AB_MODEM_RXRTSE          (0x1 << 3)
#define BPORT1_AB_MODEM_RXRTSE_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_MODEM_TXCTSE          0x1
#define BPORT1_AB_MODEM_TXCTSE_GET(_v)  (_v & 0x1)
#define BPORT1_AB_MODEM_TXRTSE          (0x1 << 1)
#define BPORT1_AB_MODEM_TXRTSE_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_MODEM_TXRTSPOL        (0x1 << 2)
#define BPORT1_AB_MODEM_TXRTSPOL_GET(_v)  ((_v >> 2) & 0x1)

#define BPORT1_AB_IR_POFFSET            0xe
#define BPORT1_AB_IR                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IR_POFFSET)
#define BPORT1_AB_IR_IREN               (0x1 << 2)
#define BPORT1_AB_IR_IREN_GET(_v)       ((_v >> 2) & 0x1)
#define BPORT1_AB_IR_TNP                0x3
#define BPORT1_AB_IR_TNP_GET(_v)        (_v & 0x3)

#define BPORT1_AB_PFIFO_POFFSET         0x10
#define BPORT1_AB_PFIFO                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PFIFO_POFFSET)
#define BPORT1_AB_PFIFO_RXFE            (0x1 << 3)
#define BPORT1_AB_PFIFO_RXFE_GET(_v)    ((_v >> 3) & 0x1)
#define BPORT1_AB_PFIFO_RXFIFOSIZE      0x7
#define BPORT1_AB_PFIFO_RXFIFOSIZE_GET(_v)  (_v & 0x7)
#define BPORT1_AB_PFIFO_TXFE            (0x1 << 7)
#define BPORT1_AB_PFIFO_TXFE_GET(_v)    ((_v >> 7) & 0x1)
#define BPORT1_AB_PFIFO_TXFIFOSIZE      (0x7 << 4)
#define BPORT1_AB_PFIFO_TXFIFOSIZE_GET(_v)  ((_v >> 4) & 0x7)

#define BPORT1_AB_CFIFO_POFFSET         0x11
#define BPORT1_AB_CFIFO                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CFIFO_POFFSET)
#define BPORT1_AB_CFIFO_RXFLUSH         (0x1 << 6)
#define BPORT1_AB_CFIFO_RXFLUSH_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_CFIFO_RXUFE           0x1
#define BPORT1_AB_CFIFO_RXUFE_GET(_v)   (_v & 0x1)
#define BPORT1_AB_CFIFO_TXFLUSH         (0x1 << 7)
#define BPORT1_AB_CFIFO_TXFLUSH_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_CFIFO_TXOFE           (0x1 << 1)
#define BPORT1_AB_CFIFO_TXOFE_GET(_v)   ((_v >> 1) & 0x1)

#define BPORT1_AB_SFIFO_POFFSET         0x12
#define BPORT1_AB_SFIFO                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SFIFO_POFFSET)
#define BPORT1_AB_SFIFO_RXEMPT          (0x1 << 6)
#define BPORT1_AB_SFIFO_RXEMPT_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_SFIFO_RXUF            0x1
#define BPORT1_AB_SFIFO_RXUF_GET(_v)    (_v & 0x1)
#define BPORT1_AB_SFIFO_TXEMPT          (0x1 << 7)
#define BPORT1_AB_SFIFO_TXEMPT_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_SFIFO_TXOF            (0x1 << 1)
#define BPORT1_AB_SFIFO_TXOF_GET(_v)    ((_v >> 1) & 0x1)

#define BPORT1_AB_TWFIFO_POFFSET        0x13
#define BPORT1_AB_TWFIFO                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TWFIFO_POFFSET)
#define BPORT1_AB_TWFIFO_TXWATER        0xff
#define BPORT1_AB_TWFIFO_TXWATER_GET(_v)  (_v & 0xff)

#define BPORT1_AB_TCFIFO_POFFSET        0x14
#define BPORT1_AB_TCFIFO                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCFIFO_POFFSET)
#define BPORT1_AB_TCFIFO_TXCOUNT        0xff
#define BPORT1_AB_TCFIFO_TXCOUNT_GET(_v)  (_v & 0xff)

#define BPORT1_AB_RWFIFO_POFFSET        0x15
#define BPORT1_AB_RWFIFO                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RWFIFO_POFFSET)
#define BPORT1_AB_RWFIFO_RXWATER        0xff
#define BPORT1_AB_RWFIFO_RXWATER_GET(_v)  (_v & 0xff)

#define BPORT1_AB_RCFIFO_POFFSET        0x16
#define BPORT1_AB_RCFIFO                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RCFIFO_POFFSET)
#define BPORT1_AB_RCFIFO_RXCOUNT        0xff
#define BPORT1_AB_RCFIFO_RXCOUNT_GET(_v)  (_v & 0xff)

#define BPORT1_AB_C7816_POFFSET         0x18
#define BPORT1_AB_C7816                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C7816_POFFSET)
#define BPORT1_AB_C7816_ANACK           (0x1 << 3)
#define BPORT1_AB_C7816_ANACK_GET(_v)   ((_v >> 3) & 0x1)
#define BPORT1_AB_C7816_INIT            (0x1 << 2)
#define BPORT1_AB_C7816_INIT_GET(_v)    ((_v >> 2) & 0x1)
#define BPORT1_AB_C7816_ISO_7816E       0x1
#define BPORT1_AB_C7816_ISO_7816E_GET(_v)  (_v & 0x1)
#define BPORT1_AB_C7816_ONACK           (0x1 << 4)
#define BPORT1_AB_C7816_ONACK_GET(_v)   ((_v >> 4) & 0x1)
#define BPORT1_AB_C7816_TTYPE           (0x1 << 1)
#define BPORT1_AB_C7816_TTYPE_GET(_v)   ((_v >> 1) & 0x1)

#define BPORT1_AB_IE7816_POFFSET        0x19
#define BPORT1_AB_IE7816                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IE7816_POFFSET)
#define BPORT1_AB_IE7816_BWTE           (0x1 << 5)
#define BPORT1_AB_IE7816_BWTE_GET(_v)   ((_v >> 5) & 0x1)
#define BPORT1_AB_IE7816_CWTE           (0x1 << 6)
#define BPORT1_AB_IE7816_CWTE_GET(_v)   ((_v >> 6) & 0x1)
#define BPORT1_AB_IE7816_GTVE           (0x1 << 2)
#define BPORT1_AB_IE7816_GTVE_GET(_v)   ((_v >> 2) & 0x1)
#define BPORT1_AB_IE7816_INITDE         (0x1 << 4)
#define BPORT1_AB_IE7816_INITDE_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_IE7816_RXTE           0x1
#define BPORT1_AB_IE7816_RXTE_GET(_v)   (_v & 0x1)
#define BPORT1_AB_IE7816_TXTE           (0x1 << 1)
#define BPORT1_AB_IE7816_TXTE_GET(_v)   ((_v >> 1) & 0x1)
#define BPORT1_AB_IE7816_WTE            (0x1 << 7)
#define BPORT1_AB_IE7816_WTE_GET(_v)    ((_v >> 7) & 0x1)

#define BPORT1_AB_IS7816_POFFSET        0x1a
#define BPORT1_AB_IS7816                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IS7816_POFFSET)
#define BPORT1_AB_IS7816_BWT            (0x1 << 5)
#define BPORT1_AB_IS7816_BWT_GET(_v)    ((_v >> 5) & 0x1)
#define BPORT1_AB_IS7816_CWT            (0x1 << 6)
#define BPORT1_AB_IS7816_CWT_GET(_v)    ((_v >> 6) & 0x1)
#define BPORT1_AB_IS7816_GTV            (0x1 << 2)
#define BPORT1_AB_IS7816_GTV_GET(_v)    ((_v >> 2) & 0x1)
#define BPORT1_AB_IS7816_INITD          (0x1 << 4)
#define BPORT1_AB_IS7816_INITD_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_IS7816_RXT            0x1
#define BPORT1_AB_IS7816_RXT_GET(_v)    (_v & 0x1)
#define BPORT1_AB_IS7816_TXT            (0x1 << 1)
#define BPORT1_AB_IS7816_TXT_GET(_v)    ((_v >> 1) & 0x1)
#define BPORT1_AB_IS7816_WT             (0x1 << 7)
#define BPORT1_AB_IS7816_WT_GET(_v)     ((_v >> 7) & 0x1)

#define BPORT1_AB_WP7816T0_POFFSET      0x1b
#define BPORT1_AB_WP7816T0              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WP7816T0_POFFSET)
#define BPORT1_AB_WP7816T0_WI           0xff
#define BPORT1_AB_WP7816T0_WI_GET(_v)   (_v & 0xff)

#define BPORT1_AB_WN7816_POFFSET        0x1c
#define BPORT1_AB_WN7816                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WN7816_POFFSET)
#define BPORT1_AB_WN7816_GTN            0xff
#define BPORT1_AB_WN7816_GTN_GET(_v)    (_v & 0xff)

#define BPORT1_AB_WF7816_POFFSET        0x1d
#define BPORT1_AB_WF7816                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WF7816_POFFSET)
#define BPORT1_AB_WF7816_GTFD           0xff
#define BPORT1_AB_WF7816_GTFD_GET(_v)   (_v & 0xff)

#define BPORT1_AB_ET7816_POFFSET        0x1e
#define BPORT1_AB_ET7816                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ET7816_POFFSET)
#define BPORT1_AB_ET7816_RXTHRESHOLD    0xf
#define BPORT1_AB_ET7816_RXTHRESHOLD_GET(_v)  (_v & 0xf)
#define BPORT1_AB_ET7816_TXTHRESHOLD    (0xf << 4)
#define BPORT1_AB_ET7816_TXTHRESHOLD_GET(_v)  ((_v >> 4) & 0xf)

#define BPORT1_AB_TL7816_POFFSET        0x1f
#define BPORT1_AB_TL7816                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TL7816_POFFSET)
#define BPORT1_AB_TL7816_TLEN           0xff
#define BPORT1_AB_TL7816_TLEN_GET(_v)   (_v & 0xff)

#define BPORT1_AB_C6_POFFSET            0x21
#define BPORT1_AB_C6                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C6_POFFSET)
#define BPORT1_AB_C6_CE                 (0x1 << 5)
#define BPORT1_AB_C6_CE_GET(_v)         ((_v >> 5) & 0x1)
#define BPORT1_AB_C6_CP                 (0x1 << 4)
#define BPORT1_AB_C6_CP_GET(_v)         ((_v >> 4) & 0x1)
#define BPORT1_AB_C6_EN709              (0x1 << 7)
#define BPORT1_AB_C6_EN709_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_C6_TX709              (0x1 << 6)
#define BPORT1_AB_C6_TX709_GET(_v)      ((_v >> 6) & 0x1)

#define BPORT1_AB_PCTH_POFFSET          0x22
#define BPORT1_AB_PCTH                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PCTH_POFFSET)
#define BPORT1_AB_PCTH_PCTH             0xff
#define BPORT1_AB_PCTH_PCTH_GET(_v)     (_v & 0xff)

#define BPORT1_AB_PCTL_POFFSET          0x23
#define BPORT1_AB_PCTL                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PCTL_POFFSET)
#define BPORT1_AB_PCTL_PCTL             0xff
#define BPORT1_AB_PCTL_PCTL_GET(_v)     (_v & 0xff)

#define BPORT1_AB_B1T_POFFSET           0x24
#define BPORT1_AB_B1T                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_B1T_POFFSET)
#define BPORT1_AB_B1T_B1T               0xff
#define BPORT1_AB_B1T_B1T_GET(_v)       (_v & 0xff)

#define BPORT1_AB_SDTH_POFFSET          0x25
#define BPORT1_AB_SDTH                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SDTH_POFFSET)
#define BPORT1_AB_SDTH_SDTH             0xff
#define BPORT1_AB_SDTH_SDTH_GET(_v)     (_v & 0xff)

#define BPORT1_AB_SDTL_POFFSET          0x26
#define BPORT1_AB_SDTL                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SDTL_POFFSET)
#define BPORT1_AB_SDTL_SDTL             0xff
#define BPORT1_AB_SDTL_SDTL_GET(_v)     (_v & 0xff)

#define BPORT1_AB_PRE_POFFSET           0x27
#define BPORT1_AB_PRE                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PRE_POFFSET)
#define BPORT1_AB_PRE_PREAMBLE          0xff
#define BPORT1_AB_PRE_PREAMBLE_GET(_v)  (_v & 0xff)

#define BPORT1_AB_TPL_POFFSET           0x28
#define BPORT1_AB_TPL                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TPL_POFFSET)
#define BPORT1_AB_TPL_TPL               0xff
#define BPORT1_AB_TPL_TPL_GET(_v)       (_v & 0xff)

#define BPORT1_AB_IE_POFFSET            0x29
#define BPORT1_AB_IE                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IE_POFFSET)
#define BPORT1_AB_IE_ISDIE              (0x1 << 5)
#define BPORT1_AB_IE_ISDIE_GET(_v)      ((_v >> 5) & 0x1)
#define BPORT1_AB_IE_PCTEIE             (0x1 << 2)
#define BPORT1_AB_IE_PCTEIE_GET(_v)     ((_v >> 2) & 0x1)
#define BPORT1_AB_IE_PRXIE              (0x1 << 4)
#define BPORT1_AB_IE_PRXIE_GET(_v)      ((_v >> 4) & 0x1)
#define BPORT1_AB_IE_PSIE               (0x1 << 1)
#define BPORT1_AB_IE_PSIE_GET(_v)       ((_v >> 1) & 0x1)
#define BPORT1_AB_IE_PTXIE              (0x1 << 3)
#define BPORT1_AB_IE_PTXIE_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_IE_TXFIE              0x1
#define BPORT1_AB_IE_TXFIE_GET(_v)      (_v & 0x1)
#define BPORT1_AB_IE_WBEIE              (0x1 << 6)
#define BPORT1_AB_IE_WBEIE_GET(_v)      ((_v >> 6) & 0x1)

#define BPORT1_AB_WB_POFFSET            0x2a
#define BPORT1_AB_WB                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WB_POFFSET)
#define BPORT1_AB_WB_WBASE              0xff
#define BPORT1_AB_WB_WBASE_GET(_v)      (_v & 0xff)

#define BPORT1_AB_S3_POFFSET            0x2b
#define BPORT1_AB_S3                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_S3_POFFSET)
#define BPORT1_AB_S3_ISD                (0x1 << 5)
#define BPORT1_AB_S3_ISD_GET(_v)        ((_v >> 5) & 0x1)
#define BPORT1_AB_S3_PCTEF              (0x1 << 2)
#define BPORT1_AB_S3_PCTEF_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_S3_PEF                (0x1 << 7)
#define BPORT1_AB_S3_PEF_GET(_v)        ((_v >> 7) & 0x1)
#define BPORT1_AB_S3_PRXF               (0x1 << 4)
#define BPORT1_AB_S3_PRXF_GET(_v)       ((_v >> 4) & 0x1)
#define BPORT1_AB_S3_PSF                (0x1 << 1)
#define BPORT1_AB_S3_PSF_GET(_v)        ((_v >> 1) & 0x1)
#define BPORT1_AB_S3_PTXF               (0x1 << 3)
#define BPORT1_AB_S3_PTXF_GET(_v)       ((_v >> 3) & 0x1)
#define BPORT1_AB_S3_TXFF               0x1
#define BPORT1_AB_S3_TXFF_GET(_v)       (_v & 0x1)
#define BPORT1_AB_S3_WBEF               (0x1 << 6)
#define BPORT1_AB_S3_WBEF_GET(_v)       ((_v >> 6) & 0x1)

#define BPORT1_AB_S4_POFFSET            0x2c
#define BPORT1_AB_S4                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_S4_POFFSET)
#define BPORT1_AB_S4_CDET               (0x3 << 2)
#define BPORT1_AB_S4_CDET_GET(_v)       ((_v >> 2) & 0x3)
#define BPORT1_AB_S4_FE                 0x1
#define BPORT1_AB_S4_FE_GET(_v)         (_v & 0x1)
#define BPORT1_AB_S4_ILCV               (0x1 << 1)
#define BPORT1_AB_S4_ILCV_GET(_v)       ((_v >> 1) & 0x1)
#define BPORT1_AB_S4_INITF              (0x1 << 4)
#define BPORT1_AB_S4_INITF_GET(_v)      ((_v >> 4) & 0x1)

#define BPORT1_AB_RPL_POFFSET           0x2d
#define BPORT1_AB_RPL                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RPL_POFFSET)
#define BPORT1_AB_RPL_RPL               0xff
#define BPORT1_AB_RPL_RPL_GET(_v)       (_v & 0xff)

#define BPORT1_AB_RPREL_POFFSET         0x2e
#define BPORT1_AB_RPREL                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RPREL_POFFSET)
#define BPORT1_AB_RPREL_RPREL           0xff
#define BPORT1_AB_RPREL_RPREL_GET(_v)   (_v & 0xff)

#define BPORT1_AB_CPW_POFFSET           0x2f
#define BPORT1_AB_CPW                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CPW_POFFSET)
#define BPORT1_AB_CPW_CPW               0xff
#define BPORT1_AB_CPW_CPW_GET(_v)       (_v & 0xff)

#define BPORT1_AB_RIDT_POFFSET          0x30
#define BPORT1_AB_RIDT                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RIDT_POFFSET)
#define BPORT1_AB_RIDT_RIDT             0xff
#define BPORT1_AB_RIDT_RIDT_GET(_v)     (_v & 0xff)

#define BPORT1_AB_TIDT_POFFSET          0x31
#define BPORT1_AB_TIDT                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TIDT_POFFSET)
#define BPORT1_AB_TIDT_TIDT             0xff
#define BPORT1_AB_TIDT_TIDT_GET(_v)     (_v & 0xff)


#endif

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
#define BPORT1_AB_DR_POFFSET            0x0
#define BPORT1_AB_DR                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DR_POFFSET)
#define BPORT1_AB_DR_OE                 (0x1 << 11)
#define BPORT1_AB_DR_OE_GET(_v)         ((_v >> 11) & 0x1)
#define BPORT1_AB_DR_BE                 (0x1 << 10)
#define BPORT1_AB_DR_BE_GET(_v)         ((_v >> 10) & 0x1)
#define BPORT1_AB_DR_PE                 (0x1 << 9)
#define BPORT1_AB_DR_PE_GET(_v)         ((_v >> 9) & 0x1)
#define BPORT1_AB_DR_FE                 (0x1 << 8)
#define BPORT1_AB_DR_FE_GET(_v)         ((_v >> 8) & 0x1)
#define BPORT1_AB_DR_DATA               0xff
#define BPORT1_AB_DR_DATA_GET(_v)       (_v & 0xff)

#define BPORT1_AB_RSRECR_POFFSET        0x4
#define BPORT1_AB_RSRECR                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RSRECR_POFFSET)
#define BPORT1_AB_RSRECR_OE             (0x1 << 3)
#define BPORT1_AB_RSRECR_OE_GET(_v)     ((_v >> 3) & 0x1)
#define BPORT1_AB_RSRECR_BE             (0x1 << 2)
#define BPORT1_AB_RSRECR_BE_GET(_v)     ((_v >> 2) & 0x1)
#define BPORT1_AB_RSRECR_PE             (0x1 << 1)
#define BPORT1_AB_RSRECR_PE_GET(_v)     ((_v >> 1) & 0x1)
#define BPORT1_AB_RSRECR_FE             0x1
#define BPORT1_AB_RSRECR_FE_GET(_v)     (_v & 0x1)

#define BPORT1_AB_FR_POFFSET            0x18
#define BPORT1_AB_FR                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FR_POFFSET)
#define BPORT1_AB_FR_TXFE               (0x1 << 7)
#define BPORT1_AB_FR_TXFE_GET(_v)       ((_v >> 7) & 0x1)
#define BPORT1_AB_FR_RXFF               (0x1 << 6)
#define BPORT1_AB_FR_RXFF_GET(_v)       ((_v >> 6) & 0x1)
#define BPORT1_AB_FR_TXFF               (0x1 << 5)
#define BPORT1_AB_FR_TXFF_GET(_v)       ((_v >> 5) & 0x1)
#define BPORT1_AB_FR_RXFE               (0x1 << 4)
#define BPORT1_AB_FR_RXFE_GET(_v)       ((_v >> 4) & 0x1)
#define BPORT1_AB_FR_BUSY               (0x1 << 3)
#define BPORT1_AB_FR_BUSY_GET(_v)       ((_v >> 3) & 0x1)

#define BPORT1_AB_FBRD_POFFSET          0x24
#define BPORT1_AB_FBRD                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FBRD_POFFSET)
#define BPORT1_AB_FBRD_DIVFRAC          0x3f
#define BPORT1_AB_FBRD_DIVFRAC_GET(_v)  (_v & 0x3f)

#define BPORT1_AB_IBRD_POFFSET          0x28
#define BPORT1_AB_IBRD                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IBRD_POFFSET)
#define BPORT1_AB_IBRD_DIVINT           0xffff
#define BPORT1_AB_IBRD_DIVINT_GET(_v)   (_v & 0xffff)

#define BPORT1_AB_LCRH_POFFSET          0x2c
#define BPORT1_AB_LCRH                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LCRH_POFFSET)
#define BPORT1_AB_LCRH_SPS              (0x1 << 7)
#define BPORT1_AB_LCRH_SPS_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_LCRH_WLEN             (0x3 << 5)
#define BPORT1_AB_LCRH_WLEN_GET(_v)     ((_v >> 5) & 0x3)
#define BPORT1_AB_LCRH_FEN              (0x1 << 4)
#define BPORT1_AB_LCRH_FEN_GET(_v)      ((_v >> 4) & 0x1)
#define BPORT1_AB_LCRH_STP2             (0x1 << 3)
#define BPORT1_AB_LCRH_STP2_GET(_v)     ((_v >> 3) & 0x1)
#define BPORT1_AB_LCRH_EPS              (0x1 << 2)
#define BPORT1_AB_LCRH_EPS_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_LCRH_PEN              (0x1 << 1)
#define BPORT1_AB_LCRH_PEN_GET(_v)      ((_v >> 1) & 0x1)
#define BPORT1_AB_LCRH_BRK              0x1
#define BPORT1_AB_LCRH_BRK_GET(_v)      (_v & 0x1)

#define BPORT1_AB_CTL_POFFSET           0x30
#define BPORT1_AB_CTL                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CTL_POFFSET)
#define BPORT1_AB_CTL_RXE               (0x1 << 9)
#define BPORT1_AB_CTL_RXE_GET(_v)       ((_v >> 9) & 0x1)
#define BPORT1_AB_CTL_TXE               (0x1 << 8)
#define BPORT1_AB_CTL_TXE_GET(_v)       ((_v >> 8) & 0x1)
#define BPORT1_AB_CTL_LBE               (0x1 << 7)
#define BPORT1_AB_CTL_LBE_GET(_v)       ((_v >> 7) & 0x1)
#define BPORT1_AB_CTL_UARTEN            0x1
#define BPORT1_AB_CTL_UARTEN_GET(_v)    (_v & 0x1)

#define BPORT1_AB_IFLS_POFFSET          0x34
#define BPORT1_AB_IFLS                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IFLS_POFFSET)
#define BPORT1_AB_IFLS_RXIFLSEL         (0x7 << 3)
#define BPORT1_AB_IFLS_RXIFLSEL_GET(_v)  ((_v >> 3) & 0x7)
#define BPORT1_AB_IFLS_TXIFLSEL         0x7
#define BPORT1_AB_IFLS_TXIFLSEL_GET(_v)  (_v & 0x7)

#define BPORT1_AB_IM_POFFSET            0x38
#define BPORT1_AB_IM                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IM_POFFSET)
#define BPORT1_AB_IM_OEIM               (0x1 << 6)
#define BPORT1_AB_IM_OEIM_GET(_v)       ((_v >> 6) & 0x1)
#define BPORT1_AB_IM_BEIM               (0x1 << 5)
#define BPORT1_AB_IM_BEIM_GET(_v)       ((_v >> 5) & 0x1)
#define BPORT1_AB_IM_PEIM               (0x1 << 4)
#define BPORT1_AB_IM_PEIM_GET(_v)       ((_v >> 4) & 0x1)
#define BPORT1_AB_IM_FEIM               (0x1 << 3)
#define BPORT1_AB_IM_FEIM_GET(_v)       ((_v >> 3) & 0x1)
#define BPORT1_AB_IM_RTIM               (0x1 << 2)
#define BPORT1_AB_IM_RTIM_GET(_v)       ((_v >> 2) & 0x1)
#define BPORT1_AB_IM_TXIM               (0x1 << 1)
#define BPORT1_AB_IM_TXIM_GET(_v)       ((_v >> 1) & 0x1)
#define BPORT1_AB_IM_RXIM               0x1
#define BPORT1_AB_IM_RXIM_GET(_v)       (_v & 0x1)

#define BPORT1_AB_RIS_POFFSET           0x3c
#define BPORT1_AB_RIS                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RIS_POFFSET)
#define BPORT1_AB_RIS_OERIS             (0x1 << 6)
#define BPORT1_AB_RIS_OERIS_GET(_v)     ((_v >> 6) & 0x1)
#define BPORT1_AB_RIS_BERIS             (0x1 << 5)
#define BPORT1_AB_RIS_BERIS_GET(_v)     ((_v >> 5) & 0x1)
#define BPORT1_AB_RIS_PERIS             (0x1 << 4)
#define BPORT1_AB_RIS_PERIS_GET(_v)     ((_v >> 4) & 0x1)
#define BPORT1_AB_RIS_FERIS             (0x1 << 3)
#define BPORT1_AB_RIS_FERIS_GET(_v)     ((_v >> 3) & 0x1)
#define BPORT1_AB_RIS_RTRIS             (0x1 << 2)
#define BPORT1_AB_RIS_RTRIS_GET(_v)     ((_v >> 2) & 0x1)
#define BPORT1_AB_RIS_TXRIS             (0x1 << 1)
#define BPORT1_AB_RIS_TXRIS_GET(_v)     ((_v >> 1) & 0x1)
#define BPORT1_AB_RIS_RXRIS             0x1
#define BPORT1_AB_RIS_RXRIS_GET(_v)     (_v & 0x1)

#define BPORT1_AB_MIS_POFFSET           0x40
#define BPORT1_AB_MIS                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIS_POFFSET)
#define BPORT1_AB_MIS_OEMIS             (0x1 << 6)
#define BPORT1_AB_MIS_OEMIS_GET(_v)     ((_v >> 6) & 0x1)
#define BPORT1_AB_MIS_BEMIS             (0x1 << 5)
#define BPORT1_AB_MIS_BEMIS_GET(_v)     ((_v >> 5) & 0x1)
#define BPORT1_AB_MIS_PEMIS             (0x1 << 4)
#define BPORT1_AB_MIS_PEMIS_GET(_v)     ((_v >> 4) & 0x1)
#define BPORT1_AB_MIS_FEMIS             (0x1 << 3)
#define BPORT1_AB_MIS_FEMIS_GET(_v)     ((_v >> 3) & 0x1)
#define BPORT1_AB_MIS_RTMIS             (0x1 << 2)
#define BPORT1_AB_MIS_RTMIS_GET(_v)     ((_v >> 2) & 0x1)
#define BPORT1_AB_MIS_TXMIS             (0x1 << 1)
#define BPORT1_AB_MIS_TXMIS_GET(_v)     ((_v >> 1) & 0x1)
#define BPORT1_AB_MIS_RXMIS             0x1
#define BPORT1_AB_MIS_RXMIS_GET(_v)     (_v & 0x1)

#define BPORT1_AB_ICR_POFFSET           0x44
#define BPORT1_AB_ICR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ICR_POFFSET)
#define BPORT1_AB_ICR_OEIC              (0x1 << 6)
#define BPORT1_AB_ICR_OEIC_GET(_v)      ((_v >> 6) & 0x1)
#define BPORT1_AB_ICR_BEIC              (0x1 << 5)
#define BPORT1_AB_ICR_BEIC_GET(_v)      ((_v >> 5) & 0x1)
#define BPORT1_AB_ICR_PEIC              (0x1 << 4)
#define BPORT1_AB_ICR_PEIC_GET(_v)      ((_v >> 4) & 0x1)
#define BPORT1_AB_ICR_FEIC              (0x1 << 3)
#define BPORT1_AB_ICR_FEIC_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_ICR_RTIC              (0x1 << 2)
#define BPORT1_AB_ICR_RTIC_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_ICR_TXIC              (0x1 << 1)
#define BPORT1_AB_ICR_TXIC_GET(_v)      ((_v >> 1) & 0x1)
#define BPORT1_AB_ICR_RXIC              0x1
#define BPORT1_AB_ICR_RXIC_GET(_v)      (_v & 0x1)

#define BPORT1_AB_PID0_POFFSET          0xfd0
#define BPORT1_AB_PID0                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PID0_POFFSET)

#define BPORT1_AB_PID1_POFFSET          0xfd4
#define BPORT1_AB_PID1                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PID1_POFFSET)

#define BPORT1_AB_PID2_POFFSET          0xfd8
#define BPORT1_AB_PID2                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PID2_POFFSET)

#define BPORT1_AB_PID3_POFFSET          0xfdc
#define BPORT1_AB_PID3                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PID3_POFFSET)

#define BPORT1_AB_PID4_POFFSET          0xfe0
#define BPORT1_AB_PID4                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PID4_POFFSET)

#define BPORT1_AB_PID5_POFFSET          0xfe4
#define BPORT1_AB_PID5                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PID5_POFFSET)

#define BPORT1_AB_PID6_POFFSET          0xfe8
#define BPORT1_AB_PID6                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PID6_POFFSET)

#define BPORT1_AB_PID7_POFFSET          0xfec
#define BPORT1_AB_PID7                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PID7_POFFSET)

#define BPORT1_AB_CID0_POFFSET          0xff0
#define BPORT1_AB_CID0                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CID0_POFFSET)

#define BPORT1_AB_CID1_POFFSET          0xff4
#define BPORT1_AB_CID1                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CID1_POFFSET)

#define BPORT1_AB_CID2_POFFSET          0xff8
#define BPORT1_AB_CID2                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CID2_POFFSET)

#define BPORT1_AB_CID3_POFFSET          0xffc
#define BPORT1_AB_CID3                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CID3_POFFSET)


#endif

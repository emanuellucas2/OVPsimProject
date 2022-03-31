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
#define BPORT1_AB_UART_URXD_POFFSET     0x0
#define BPORT1_AB_UART_URXD             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UART_URXD_POFFSET)
#define BPORT1_AB_UART_URXD_CHARRDY     (0x1 << 15)
#define BPORT1_AB_UART_URXD_CHARRDY_GET(_v)  ((_v >> 15) & 0x1)
#define BPORT1_AB_UART_URXD_ERR         (0x1 << 14)
#define BPORT1_AB_UART_URXD_ERR_GET(_v)  ((_v >> 14) & 0x1)
#define BPORT1_AB_UART_URXD_OVRRUN      (0x1 << 13)
#define BPORT1_AB_UART_URXD_OVRRUN_GET(_v)  ((_v >> 13) & 0x1)
#define BPORT1_AB_UART_URXD_FRMERR      (0x1 << 12)
#define BPORT1_AB_UART_URXD_FRMERR_GET(_v)  ((_v >> 12) & 0x1)
#define BPORT1_AB_UART_URXD_BRK         (0x1 << 11)
#define BPORT1_AB_UART_URXD_BRK_GET(_v)  ((_v >> 11) & 0x1)
#define BPORT1_AB_UART_URXD_PRERR       (0x1 << 10)
#define BPORT1_AB_UART_URXD_PRERR_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_UART_URXD_DATA        0xff
#define BPORT1_AB_UART_URXD_DATA_GET(_v)  (_v & 0xff)

#define BPORT1_AB_UART_UTXD_POFFSET     0x40
#define BPORT1_AB_UART_UTXD             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UART_UTXD_POFFSET)
#define BPORT1_AB_UART_UTXD_DATA        0xff
#define BPORT1_AB_UART_UTXD_DATA_GET(_v)  (_v & 0xff)

#define BPORT1_AB_UART_UCR1_POFFSET     0x80
#define BPORT1_AB_UART_UCR1             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UART_UCR1_POFFSET)
#define BPORT1_AB_UART_UCR1_ADEN        (0x1 << 15)
#define BPORT1_AB_UART_UCR1_ADEN_GET(_v)  ((_v >> 15) & 0x1)
#define BPORT1_AB_UART_UCR1_ADBR        (0x1 << 14)
#define BPORT1_AB_UART_UCR1_ADBR_GET(_v)  ((_v >> 14) & 0x1)
#define BPORT1_AB_UART_UCR1_TRDYEN      (0x1 << 13)
#define BPORT1_AB_UART_UCR1_TRDYEN_GET(_v)  ((_v >> 13) & 0x1)
#define BPORT1_AB_UART_UCR1_IDEN        (0x1 << 12)
#define BPORT1_AB_UART_UCR1_IDEN_GET(_v)  ((_v >> 12) & 0x1)
#define BPORT1_AB_UART_UCR1_ICD         (0x3 << 10)
#define BPORT1_AB_UART_UCR1_ICD_GET(_v)  ((_v >> 10) & 0x3)
#define BPORT1_AB_UART_UCR1_RRDYEN      (0x1 << 9)
#define BPORT1_AB_UART_UCR1_RRDYEN_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_UART_UCR1_RXDMAEN     (0x1 << 8)
#define BPORT1_AB_UART_UCR1_RXDMAEN_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_UART_UCR1_IREN        (0x1 << 7)
#define BPORT1_AB_UART_UCR1_IREN_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_UART_UCR1_TXMPTYEN    (0x1 << 6)
#define BPORT1_AB_UART_UCR1_TXMPTYEN_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_UART_UCR1_RTSDEN      (0x1 << 5)
#define BPORT1_AB_UART_UCR1_RTSDEN_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_UART_UCR1_SNDBRK      (0x1 << 4)
#define BPORT1_AB_UART_UCR1_SNDBRK_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_UART_UCR1_TXDMAEN     (0x1 << 3)
#define BPORT1_AB_UART_UCR1_TXDMAEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_UART_UCR1_ATDMAEN     (0x1 << 2)
#define BPORT1_AB_UART_UCR1_ATDMAEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_UART_UCR1_DOZE        (0x1 << 1)
#define BPORT1_AB_UART_UCR1_DOZE_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_UART_UCR1_UARTEN      0x1
#define BPORT1_AB_UART_UCR1_UARTEN_GET(_v)  (_v & 0x1)

#define BPORT1_AB_UART_UCR2_POFFSET     0x84
#define BPORT1_AB_UART_UCR2             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UART_UCR2_POFFSET)
#define BPORT1_AB_UART_UCR2_ESCI        (0x1 << 15)
#define BPORT1_AB_UART_UCR2_ESCI_GET(_v)  ((_v >> 15) & 0x1)
#define BPORT1_AB_UART_UCR2_IRTS        (0x1 << 14)
#define BPORT1_AB_UART_UCR2_IRTS_GET(_v)  ((_v >> 14) & 0x1)
#define BPORT1_AB_UART_UCR2_CTSC        (0x1 << 13)
#define BPORT1_AB_UART_UCR2_CTSC_GET(_v)  ((_v >> 13) & 0x1)
#define BPORT1_AB_UART_UCR2_CTS         (0x1 << 12)
#define BPORT1_AB_UART_UCR2_CTS_GET(_v)  ((_v >> 12) & 0x1)
#define BPORT1_AB_UART_UCR2_ESCEN       (0x1 << 11)
#define BPORT1_AB_UART_UCR2_ESCEN_GET(_v)  ((_v >> 11) & 0x1)
#define BPORT1_AB_UART_UCR2_RTEC        (0x3 << 9)
#define BPORT1_AB_UART_UCR2_RTEC_GET(_v)  ((_v >> 9) & 0x3)
#define BPORT1_AB_UART_UCR2_PREN        (0x1 << 8)
#define BPORT1_AB_UART_UCR2_PREN_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_UART_UCR2_PROE        (0x1 << 7)
#define BPORT1_AB_UART_UCR2_PROE_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_UART_UCR2_STPB        (0x1 << 6)
#define BPORT1_AB_UART_UCR2_STPB_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_UART_UCR2_WS          (0x1 << 5)
#define BPORT1_AB_UART_UCR2_WS_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_UART_UCR2_RTSEN       (0x1 << 4)
#define BPORT1_AB_UART_UCR2_RTSEN_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_UART_UCR2_ATEN        (0x1 << 3)
#define BPORT1_AB_UART_UCR2_ATEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_UART_UCR2_TXEN        (0x1 << 2)
#define BPORT1_AB_UART_UCR2_TXEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_UART_UCR2_RXEN        (0x1 << 1)
#define BPORT1_AB_UART_UCR2_RXEN_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_UART_UCR2_SRST        0x1
#define BPORT1_AB_UART_UCR2_SRST_GET(_v)  (_v & 0x1)

#define BPORT1_AB_UART_UCR3_POFFSET     0x88
#define BPORT1_AB_UART_UCR3             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UART_UCR3_POFFSET)
#define BPORT1_AB_UART_UCR3_DPEC        (0x3 << 14)
#define BPORT1_AB_UART_UCR3_DPEC_GET(_v)  ((_v >> 14) & 0x3)
#define BPORT1_AB_UART_UCR3_DTREN       (0x1 << 13)
#define BPORT1_AB_UART_UCR3_DTREN_GET(_v)  ((_v >> 13) & 0x1)
#define BPORT1_AB_UART_UCR3_PARERREN    (0x1 << 12)
#define BPORT1_AB_UART_UCR3_PARERREN_GET(_v)  ((_v >> 12) & 0x1)
#define BPORT1_AB_UART_UCR3_FRAERREN    (0x1 << 11)
#define BPORT1_AB_UART_UCR3_FRAERREN_GET(_v)  ((_v >> 11) & 0x1)
#define BPORT1_AB_UART_UCR3_DSR         (0x1 << 10)
#define BPORT1_AB_UART_UCR3_DSR_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_UART_UCR3_DCD         (0x1 << 9)
#define BPORT1_AB_UART_UCR3_DCD_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_UART_UCR3_RI          (0x1 << 8)
#define BPORT1_AB_UART_UCR3_RI_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_UART_UCR3_ADNIMP      (0x1 << 7)
#define BPORT1_AB_UART_UCR3_ADNIMP_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_UART_UCR3_RXDSEN      (0x1 << 6)
#define BPORT1_AB_UART_UCR3_RXDSEN_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_UART_UCR3_AIRINTEN    (0x1 << 5)
#define BPORT1_AB_UART_UCR3_AIRINTEN_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_UART_UCR3_AWAKEN      (0x1 << 4)
#define BPORT1_AB_UART_UCR3_AWAKEN_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_UART_UCR3_DTRDEN      (0x1 << 3)
#define BPORT1_AB_UART_UCR3_DTRDEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_UART_UCR3_RXDMUXSEL   (0x1 << 2)
#define BPORT1_AB_UART_UCR3_RXDMUXSEL_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_UART_UCR3_INVT        (0x1 << 1)
#define BPORT1_AB_UART_UCR3_INVT_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_UART_UCR3_ACIEN       0x1
#define BPORT1_AB_UART_UCR3_ACIEN_GET(_v)  (_v & 0x1)

#define BPORT1_AB_UART_UCR4_POFFSET     0x8c
#define BPORT1_AB_UART_UCR4             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UART_UCR4_POFFSET)
#define BPORT1_AB_UART_UCR4_CTSTL       (0x3f << 10)
#define BPORT1_AB_UART_UCR4_CTSTL_GET(_v)  ((_v >> 10) & 0x3f)
#define BPORT1_AB_UART_UCR4_INVR        (0x1 << 9)
#define BPORT1_AB_UART_UCR4_INVR_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_UART_UCR4_ENIRI       (0x1 << 8)
#define BPORT1_AB_UART_UCR4_ENIRI_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_UART_UCR4_WKEN        (0x1 << 7)
#define BPORT1_AB_UART_UCR4_WKEN_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_UART_UCR4_IDDMAEN     (0x1 << 6)
#define BPORT1_AB_UART_UCR4_IDDMAEN_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_UART_UCR4_IRSC        (0x1 << 5)
#define BPORT1_AB_UART_UCR4_IRSC_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_UART_UCR4_LPBYP       (0x1 << 4)
#define BPORT1_AB_UART_UCR4_LPBYP_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_UART_UCR4_TCEN        (0x1 << 3)
#define BPORT1_AB_UART_UCR4_TCEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_UART_UCR4_BKEN        (0x1 << 2)
#define BPORT1_AB_UART_UCR4_BKEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_UART_UCR4_OREN        (0x1 << 1)
#define BPORT1_AB_UART_UCR4_OREN_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_UART_UCR4_DREN        0x1
#define BPORT1_AB_UART_UCR4_DREN_GET(_v)  (_v & 0x1)

#define BPORT1_AB_UART_UFCR_POFFSET     0x90
#define BPORT1_AB_UART_UFCR             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UART_UFCR_POFFSET)
#define BPORT1_AB_UART_UFCR_TXTL        (0x3f << 10)
#define BPORT1_AB_UART_UFCR_TXTL_GET(_v)  ((_v >> 10) & 0x3f)
#define BPORT1_AB_UART_UFCR_RFDIV       (0x7 << 7)
#define BPORT1_AB_UART_UFCR_RFDIV_GET(_v)  ((_v >> 7) & 0x7)
#define BPORT1_AB_UART_UFCR_DCEDTE      (0x1 << 6)
#define BPORT1_AB_UART_UFCR_DCEDTE_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_UART_UFCR_RXTL        0x3f
#define BPORT1_AB_UART_UFCR_RXTL_GET(_v)  (_v & 0x3f)

#define BPORT1_AB_UART_USR1_POFFSET     0x94
#define BPORT1_AB_UART_USR1             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UART_USR1_POFFSET)
#define BPORT1_AB_UART_USR1_PARITYERR   (0x1 << 15)
#define BPORT1_AB_UART_USR1_PARITYERR_GET(_v)  ((_v >> 15) & 0x1)
#define BPORT1_AB_UART_USR1_RTSS        (0x1 << 14)
#define BPORT1_AB_UART_USR1_RTSS_GET(_v)  ((_v >> 14) & 0x1)
#define BPORT1_AB_UART_USR1_TRDY        (0x1 << 13)
#define BPORT1_AB_UART_USR1_TRDY_GET(_v)  ((_v >> 13) & 0x1)
#define BPORT1_AB_UART_USR1_RTSD        (0x1 << 12)
#define BPORT1_AB_UART_USR1_RTSD_GET(_v)  ((_v >> 12) & 0x1)
#define BPORT1_AB_UART_USR1_ESCF        (0x1 << 11)
#define BPORT1_AB_UART_USR1_ESCF_GET(_v)  ((_v >> 11) & 0x1)
#define BPORT1_AB_UART_USR1_FRAMERR     (0x1 << 10)
#define BPORT1_AB_UART_USR1_FRAMERR_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_UART_USR1_RRDY        (0x1 << 9)
#define BPORT1_AB_UART_USR1_RRDY_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_UART_USR1_AGTIM       (0x1 << 8)
#define BPORT1_AB_UART_USR1_AGTIM_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_UART_USR1_DTRD        (0x1 << 7)
#define BPORT1_AB_UART_USR1_DTRD_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_UART_USR1_RXDS        (0x1 << 6)
#define BPORT1_AB_UART_USR1_RXDS_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_UART_USR1_AIRINT      (0x1 << 5)
#define BPORT1_AB_UART_USR1_AIRINT_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_UART_USR1_AWAKE       (0x1 << 4)
#define BPORT1_AB_UART_USR1_AWAKE_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_UART_USR1_SAD         (0x1 << 3)
#define BPORT1_AB_UART_USR1_SAD_GET(_v)  ((_v >> 3) & 0x1)

#define BPORT1_AB_UART_USR2_POFFSET     0x98
#define BPORT1_AB_UART_USR2             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UART_USR2_POFFSET)
#define BPORT1_AB_UART_USR2_ADET        (0x1 << 15)
#define BPORT1_AB_UART_USR2_ADET_GET(_v)  ((_v >> 15) & 0x1)
#define BPORT1_AB_UART_USR2_TXFE        (0x1 << 14)
#define BPORT1_AB_UART_USR2_TXFE_GET(_v)  ((_v >> 14) & 0x1)
#define BPORT1_AB_UART_USR2_DTRF        (0x1 << 13)
#define BPORT1_AB_UART_USR2_DTRF_GET(_v)  ((_v >> 13) & 0x1)
#define BPORT1_AB_UART_USR2_IDLE        (0x1 << 12)
#define BPORT1_AB_UART_USR2_IDLE_GET(_v)  ((_v >> 12) & 0x1)
#define BPORT1_AB_UART_USR2_ACST        (0x1 << 11)
#define BPORT1_AB_UART_USR2_ACST_GET(_v)  ((_v >> 11) & 0x1)
#define BPORT1_AB_UART_USR2_RIDELT      (0x1 << 10)
#define BPORT1_AB_UART_USR2_RIDELT_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_UART_USR2_RIIN        (0x1 << 9)
#define BPORT1_AB_UART_USR2_RIIN_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_UART_USR2_IRINT       (0x1 << 8)
#define BPORT1_AB_UART_USR2_IRINT_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_UART_USR2_WAKE        (0x1 << 7)
#define BPORT1_AB_UART_USR2_WAKE_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_UART_USR2_DCDDELT     (0x1 << 6)
#define BPORT1_AB_UART_USR2_DCDDELT_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_UART_USR2_DCDIN       (0x1 << 5)
#define BPORT1_AB_UART_USR2_DCDIN_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_UART_USR2_RTSF        (0x1 << 4)
#define BPORT1_AB_UART_USR2_RTSF_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_UART_USR2_TXDC        (0x1 << 3)
#define BPORT1_AB_UART_USR2_TXDC_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_UART_USR2_BRCD        (0x1 << 2)
#define BPORT1_AB_UART_USR2_BRCD_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_UART_USR2_ORE         (0x1 << 1)
#define BPORT1_AB_UART_USR2_ORE_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_UART_USR2_RDR         0x1
#define BPORT1_AB_UART_USR2_RDR_GET(_v)  (_v & 0x1)

#define BPORT1_AB_UART_UESC_POFFSET     0x9c
#define BPORT1_AB_UART_UESC             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UART_UESC_POFFSET)
#define BPORT1_AB_UART_UESC_ESC_CHAR    0xff
#define BPORT1_AB_UART_UESC_ESC_CHAR_GET(_v)  (_v & 0xff)

#define BPORT1_AB_UART_UTIM_POFFSET     0xa0
#define BPORT1_AB_UART_UTIM             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UART_UTIM_POFFSET)
#define BPORT1_AB_UART_UTIM_TIM         0xfff
#define BPORT1_AB_UART_UTIM_TIM_GET(_v)  (_v & 0xfff)

#define BPORT1_AB_UART_UBIR_POFFSET     0xa4
#define BPORT1_AB_UART_UBIR             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UART_UBIR_POFFSET)
#define BPORT1_AB_UART_UBIR_INC         0xffff
#define BPORT1_AB_UART_UBIR_INC_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_UART_UBMR_POFFSET     0xa8
#define BPORT1_AB_UART_UBMR             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UART_UBMR_POFFSET)
#define BPORT1_AB_UART_UBMR_MOD         0xffff
#define BPORT1_AB_UART_UBMR_MOD_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_UART_UBRC_POFFSET     0xac
#define BPORT1_AB_UART_UBRC             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UART_UBRC_POFFSET)
#define BPORT1_AB_UART_UBRC_BCNT        0xffff
#define BPORT1_AB_UART_UBRC_BCNT_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_UART_ONEMS_POFFSET    0xb0
#define BPORT1_AB_UART_ONEMS            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UART_ONEMS_POFFSET)
#define BPORT1_AB_UART_ONEMS_ONEMS      0xffffff
#define BPORT1_AB_UART_ONEMS_ONEMS_GET(_v)  (_v & 0xffffff)

#define BPORT1_AB_UART_UTS_POFFSET      0xb4
#define BPORT1_AB_UART_UTS              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UART_UTS_POFFSET)
#define BPORT1_AB_UART_UTS_FRCPERR      (0x1 << 13)
#define BPORT1_AB_UART_UTS_FRCPERR_GET(_v)  ((_v >> 13) & 0x1)
#define BPORT1_AB_UART_UTS_LOOP         (0x1 << 12)
#define BPORT1_AB_UART_UTS_LOOP_GET(_v)  ((_v >> 12) & 0x1)
#define BPORT1_AB_UART_UTS_DBGEN        (0x1 << 11)
#define BPORT1_AB_UART_UTS_DBGEN_GET(_v)  ((_v >> 11) & 0x1)
#define BPORT1_AB_UART_UTS_LOOPIR       (0x1 << 10)
#define BPORT1_AB_UART_UTS_LOOPIR_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_UART_UTS_RXDBG        (0x1 << 9)
#define BPORT1_AB_UART_UTS_RXDBG_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_UART_UTS_TXEMPTY      (0x1 << 6)
#define BPORT1_AB_UART_UTS_TXEMPTY_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_UART_UTS_RXEMPTY      (0x1 << 5)
#define BPORT1_AB_UART_UTS_RXEMPTY_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_UART_UTS_TXFULL       (0x1 << 4)
#define BPORT1_AB_UART_UTS_TXFULL_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_UART_UTS_RXFULL       (0x1 << 3)
#define BPORT1_AB_UART_UTS_RXFULL_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_UART_UTS_SOFTRST      0x1
#define BPORT1_AB_UART_UTS_SOFTRST_GET(_v)  (_v & 0x1)

#define BPORT1_AB_UART_UMCR_POFFSET     0xb8
#define BPORT1_AB_UART_UMCR             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UART_UMCR_POFFSET)
#define BPORT1_AB_UART_UMCR_SLADDR      (0xff << 8)
#define BPORT1_AB_UART_UMCR_SLADDR_GET(_v)  ((_v >> 8) & 0xff)
#define BPORT1_AB_UART_UMCR_SADEN       (0x1 << 3)
#define BPORT1_AB_UART_UMCR_SADEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_UART_UMCR_TXB8        (0x1 << 2)
#define BPORT1_AB_UART_UMCR_TXB8_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_UART_UMCR_SLAM        (0x1 << 1)
#define BPORT1_AB_UART_UMCR_SLAM_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_UART_UMCR_MDEN        0x1
#define BPORT1_AB_UART_UMCR_MDEN_GET(_v)  (_v & 0x1)

#define BPORT1_AB_BUFFER_POFFSET        0x0
#define BPORT1_AB_BUFFER                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BUFFER_POFFSET)
#define BPORT1_AB_BUFFER_BYTES          0x4000


#endif

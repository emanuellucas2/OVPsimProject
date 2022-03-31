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
#define BPORT1_AB_MCR_POFFSET           0x0
#define BPORT1_AB_MCR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MCR_POFFSET)
#define BPORT1_AB_MCR_MAXMB             0x7f
#define BPORT1_AB_MCR_MAXMB_GET(_v)     (_v & 0x7f)
#define BPORT1_AB_MCR_IDAM              (0x3 << 8)
#define BPORT1_AB_MCR_IDAM_GET(_v)      ((_v >> 8) & 0x3)
#define BPORT1_AB_MCR_AEN               (0x1 << 12)
#define BPORT1_AB_MCR_AEN_GET(_v)       ((_v >> 12) & 0x1)
#define BPORT1_AB_MCR_LPRIOEN           (0x1 << 13)
#define BPORT1_AB_MCR_LPRIOEN_GET(_v)   ((_v >> 13) & 0x1)
#define BPORT1_AB_MCR_IRMQ              (0x1 << 16)
#define BPORT1_AB_MCR_IRMQ_GET(_v)      ((_v >> 16) & 0x1)
#define BPORT1_AB_MCR_SRXDIS            (0x1 << 17)
#define BPORT1_AB_MCR_SRXDIS_GET(_v)    ((_v >> 17) & 0x1)
#define BPORT1_AB_MCR_DOZE              (0x1 << 18)
#define BPORT1_AB_MCR_DOZE_GET(_v)      ((_v >> 18) & 0x1)
#define BPORT1_AB_MCR_LPMACK            (0x1 << 20)
#define BPORT1_AB_MCR_LPMACK_GET(_v)    ((_v >> 20) & 0x1)
#define BPORT1_AB_MCR_WRNEN             (0x1 << 21)
#define BPORT1_AB_MCR_WRNEN_GET(_v)     ((_v >> 21) & 0x1)
#define BPORT1_AB_MCR_SLFWAK            (0x1 << 22)
#define BPORT1_AB_MCR_SLFWAK_GET(_v)    ((_v >> 22) & 0x1)
#define BPORT1_AB_MCR_SUPV              (0x1 << 23)
#define BPORT1_AB_MCR_SUPV_GET(_v)      ((_v >> 23) & 0x1)
#define BPORT1_AB_MCR_FRZACK            (0x1 << 24)
#define BPORT1_AB_MCR_FRZACK_GET(_v)    ((_v >> 24) & 0x1)
#define BPORT1_AB_MCR_SOFTRST           (0x1 << 25)
#define BPORT1_AB_MCR_SOFTRST_GET(_v)   ((_v >> 25) & 0x1)
#define BPORT1_AB_MCR_WAKMSK            (0x1 << 26)
#define BPORT1_AB_MCR_WAKMSK_GET(_v)    ((_v >> 26) & 0x1)
#define BPORT1_AB_MCR_NOTRDY            (0x1 << 27)
#define BPORT1_AB_MCR_NOTRDY_GET(_v)    ((_v >> 27) & 0x1)
#define BPORT1_AB_MCR_HALT              (0x1 << 28)
#define BPORT1_AB_MCR_HALT_GET(_v)      ((_v >> 28) & 0x1)
#define BPORT1_AB_MCR_RFEN              (0x1 << 29)
#define BPORT1_AB_MCR_RFEN_GET(_v)      ((_v >> 29) & 0x1)
#define BPORT1_AB_MCR_FRZ               (0x1 << 30)
#define BPORT1_AB_MCR_FRZ_GET(_v)       ((_v >> 30) & 0x1)
#define BPORT1_AB_MCR_MDIS              (0x1 << 31)
#define BPORT1_AB_MCR_MDIS_GET(_v)      ((_v >> 31) & 0x1)

#define BPORT1_AB_CTRL1_POFFSET         0x4
#define BPORT1_AB_CTRL1                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CTRL1_POFFSET)
#define BPORT1_AB_CTRL1_PROPSEG         0x7
#define BPORT1_AB_CTRL1_PROPSEG_GET(_v)  (_v & 0x7)
#define BPORT1_AB_CTRL1_LOM             (0x1 << 3)
#define BPORT1_AB_CTRL1_LOM_GET(_v)     ((_v >> 3) & 0x1)
#define BPORT1_AB_CTRL1_LBUF            (0x1 << 4)
#define BPORT1_AB_CTRL1_LBUF_GET(_v)    ((_v >> 4) & 0x1)
#define BPORT1_AB_CTRL1_TSYN            (0x1 << 5)
#define BPORT1_AB_CTRL1_TSYN_GET(_v)    ((_v >> 5) & 0x1)
#define BPORT1_AB_CTRL1_BOFFREC         (0x1 << 6)
#define BPORT1_AB_CTRL1_BOFFREC_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_CTRL1_SMP             (0x1 << 7)
#define BPORT1_AB_CTRL1_SMP_GET(_v)     ((_v >> 7) & 0x1)
#define BPORT1_AB_CTRL1_RWRNMSK         (0x1 << 10)
#define BPORT1_AB_CTRL1_RWRNMSK_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_CTRL1_TWRNMSK         (0x1 << 11)
#define BPORT1_AB_CTRL1_TWRNMSK_GET(_v)  ((_v >> 11) & 0x1)
#define BPORT1_AB_CTRL1_LPB             (0x1 << 12)
#define BPORT1_AB_CTRL1_LPB_GET(_v)     ((_v >> 12) & 0x1)
#define BPORT1_AB_CTRL1_CLKSRC          (0x1 << 13)
#define BPORT1_AB_CTRL1_CLKSRC_GET(_v)  ((_v >> 13) & 0x1)
#define BPORT1_AB_CTRL1_ERRMSK          (0x1 << 14)
#define BPORT1_AB_CTRL1_ERRMSK_GET(_v)  ((_v >> 14) & 0x1)
#define BPORT1_AB_CTRL1_BOFFMSK         (0x1 << 15)
#define BPORT1_AB_CTRL1_BOFFMSK_GET(_v)  ((_v >> 15) & 0x1)
#define BPORT1_AB_CTRL1_PSEG2           (0x7 << 16)
#define BPORT1_AB_CTRL1_PSEG2_GET(_v)   ((_v >> 16) & 0x7)
#define BPORT1_AB_CTRL1_PSEG1           (0x7 << 19)
#define BPORT1_AB_CTRL1_PSEG1_GET(_v)   ((_v >> 19) & 0x7)
#define BPORT1_AB_CTRL1_RJW             (0x3 << 22)
#define BPORT1_AB_CTRL1_RJW_GET(_v)     ((_v >> 22) & 0x3)
#define BPORT1_AB_CTRL1_PRESDIV         (0xff << 24)
#define BPORT1_AB_CTRL1_PRESDIV_GET(_v)  ((_v >> 24) & 0xff)

#define BPORT1_AB_TIMER_POFFSET         0x8
#define BPORT1_AB_TIMER                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TIMER_POFFSET)
#define BPORT1_AB_TIMER_TIMER           0xffff
#define BPORT1_AB_TIMER_TIMER_GET(_v)   (_v & 0xffff)

#define BPORT1_AB_RXMGMASK_POFFSET      0x10
#define BPORT1_AB_RXMGMASK              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXMGMASK_POFFSET)
#define BPORT1_AB_RXMGMASK_MG           0xffffffff
#define BPORT1_AB_RXMGMASK_MG_GET(_v)   (_v & 0xffffffff)

#define BPORT1_AB_RX14MASK_POFFSET      0x14
#define BPORT1_AB_RX14MASK              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RX14MASK_POFFSET)
#define BPORT1_AB_RX14MASK_RX14M        0xffffffff
#define BPORT1_AB_RX14MASK_RX14M_GET(_v)  (_v & 0xffffffff)

#define BPORT1_AB_RX15MASK_POFFSET      0x18
#define BPORT1_AB_RX15MASK              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RX15MASK_POFFSET)
#define BPORT1_AB_RX15MASK_RX15M        0xffffffff
#define BPORT1_AB_RX15MASK_RX15M_GET(_v)  (_v & 0xffffffff)

#define BPORT1_AB_ECR_POFFSET           0x1c
#define BPORT1_AB_ECR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ECR_POFFSET)
#define BPORT1_AB_ECR_TXERRCNT          0xff
#define BPORT1_AB_ECR_TXERRCNT_GET(_v)  (_v & 0xff)
#define BPORT1_AB_ECR_RXERRCNT          (0xff << 8)
#define BPORT1_AB_ECR_RXERRCNT_GET(_v)  ((_v >> 8) & 0xff)

#define BPORT1_AB_ESR1_POFFSET          0x20
#define BPORT1_AB_ESR1                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ESR1_POFFSET)
#define BPORT1_AB_ESR1_WAKINT           0x1
#define BPORT1_AB_ESR1_WAKINT_GET(_v)   (_v & 0x1)
#define BPORT1_AB_ESR1_ERRINT           (0x1 << 1)
#define BPORT1_AB_ESR1_ERRINT_GET(_v)   ((_v >> 1) & 0x1)
#define BPORT1_AB_ESR1_BOFFINT          (0x1 << 2)
#define BPORT1_AB_ESR1_BOFFINT_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_ESR1_RX               (0x1 << 3)
#define BPORT1_AB_ESR1_RX_GET(_v)       ((_v >> 3) & 0x1)
#define BPORT1_AB_ESR1_FLTCONF          (0x3 << 4)
#define BPORT1_AB_ESR1_FLTCONF_GET(_v)  ((_v >> 4) & 0x3)
#define BPORT1_AB_ESR1_TX               (0x1 << 6)
#define BPORT1_AB_ESR1_TX_GET(_v)       ((_v >> 6) & 0x1)
#define BPORT1_AB_ESR1_IDLE             (0x1 << 7)
#define BPORT1_AB_ESR1_IDLE_GET(_v)     ((_v >> 7) & 0x1)
#define BPORT1_AB_ESR1_RXWRN            (0x1 << 8)
#define BPORT1_AB_ESR1_RXWRN_GET(_v)    ((_v >> 8) & 0x1)
#define BPORT1_AB_ESR1_TXWRN            (0x1 << 9)
#define BPORT1_AB_ESR1_TXWRN_GET(_v)    ((_v >> 9) & 0x1)
#define BPORT1_AB_ESR1_STFERR           (0x1 << 10)
#define BPORT1_AB_ESR1_STFERR_GET(_v)   ((_v >> 10) & 0x1)
#define BPORT1_AB_ESR1_FRMERR           (0x1 << 11)
#define BPORT1_AB_ESR1_FRMERR_GET(_v)   ((_v >> 11) & 0x1)
#define BPORT1_AB_ESR1_CRCERR           (0x1 << 12)
#define BPORT1_AB_ESR1_CRCERR_GET(_v)   ((_v >> 12) & 0x1)
#define BPORT1_AB_ESR1_ACKERR           (0x1 << 13)
#define BPORT1_AB_ESR1_ACKERR_GET(_v)   ((_v >> 13) & 0x1)
#define BPORT1_AB_ESR1_BIT0ERR          (0x1 << 14)
#define BPORT1_AB_ESR1_BIT0ERR_GET(_v)  ((_v >> 14) & 0x1)
#define BPORT1_AB_ESR1_BIT1ERR          (0x1 << 15)
#define BPORT1_AB_ESR1_BIT1ERR_GET(_v)  ((_v >> 15) & 0x1)
#define BPORT1_AB_ESR1_RWRNINT          (0x1 << 16)
#define BPORT1_AB_ESR1_RWRNINT_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_ESR1_TWRNINT          (0x1 << 17)
#define BPORT1_AB_ESR1_TWRNINT_GET(_v)  ((_v >> 17) & 0x1)
#define BPORT1_AB_ESR1_SYNCH            (0x1 << 18)
#define BPORT1_AB_ESR1_SYNCH_GET(_v)    ((_v >> 18) & 0x1)

#define BPORT1_AB_IMASK2_POFFSET        0x24
#define BPORT1_AB_IMASK2                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IMASK2_POFFSET)
#define BPORT1_AB_IMASK2_BUFHM          0xffffffff
#define BPORT1_AB_IMASK2_BUFHM_GET(_v)  (_v & 0xffffffff)

#define BPORT1_AB_IMASK1_POFFSET        0x28
#define BPORT1_AB_IMASK1                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IMASK1_POFFSET)
#define BPORT1_AB_IMASK1_BUFLM          0xffffffff
#define BPORT1_AB_IMASK1_BUFLM_GET(_v)  (_v & 0xffffffff)

#define BPORT1_AB_IFLAG2_POFFSET        0x2c
#define BPORT1_AB_IFLAG2                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IFLAG2_POFFSET)
#define BPORT1_AB_IFLAG2_BUFHI          0xffffffff
#define BPORT1_AB_IFLAG2_BUFHI_GET(_v)  (_v & 0xffffffff)

#define BPORT1_AB_IFLAG1_POFFSET        0x30
#define BPORT1_AB_IFLAG1                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IFLAG1_POFFSET)
#define BPORT1_AB_IFLAG1_BUF4TO0I       0x1f
#define BPORT1_AB_IFLAG1_BUF4TO0I_GET(_v)  (_v & 0x1f)
#define BPORT1_AB_IFLAG1_BUF5I          (0x1 << 5)
#define BPORT1_AB_IFLAG1_BUF5I_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_IFLAG1_BUF6I          (0x1 << 6)
#define BPORT1_AB_IFLAG1_BUF6I_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_IFLAG1_BUF7I          (0x1 << 7)
#define BPORT1_AB_IFLAG1_BUF7I_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_IFLAG1_BUF31TO8I      (0xffffff << 8)
#define BPORT1_AB_IFLAG1_BUF31TO8I_GET(_v)  ((_v >> 8) & 0xffffff)

#define BPORT1_AB_CTRL2_POFFSET         0x34
#define BPORT1_AB_CTRL2                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CTRL2_POFFSET)
#define BPORT1_AB_CTRL2_EACEN           (0x1 << 16)
#define BPORT1_AB_CTRL2_EACEN_GET(_v)   ((_v >> 16) & 0x1)
#define BPORT1_AB_CTRL2_RRS             (0x1 << 17)
#define BPORT1_AB_CTRL2_RRS_GET(_v)     ((_v >> 17) & 0x1)
#define BPORT1_AB_CTRL2_MRP             (0x1 << 18)
#define BPORT1_AB_CTRL2_MRP_GET(_v)     ((_v >> 18) & 0x1)
#define BPORT1_AB_CTRL2_TASD            (0x1f << 19)
#define BPORT1_AB_CTRL2_TASD_GET(_v)    ((_v >> 19) & 0x1f)
#define BPORT1_AB_CTRL2_RFFN            (0xf << 24)
#define BPORT1_AB_CTRL2_RFFN_GET(_v)    ((_v >> 24) & 0xf)
#define BPORT1_AB_CTRL2_WRMFRZ          (0x1 << 28)
#define BPORT1_AB_CTRL2_WRMFRZ_GET(_v)  ((_v >> 28) & 0x1)

#define BPORT1_AB_ESR2_POFFSET          0x38
#define BPORT1_AB_ESR2                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ESR2_POFFSET)
#define BPORT1_AB_ESR2_IMB              (0x1 << 13)
#define BPORT1_AB_ESR2_IMB_GET(_v)      ((_v >> 13) & 0x1)
#define BPORT1_AB_ESR2_VPS              (0x1 << 14)
#define BPORT1_AB_ESR2_VPS_GET(_v)      ((_v >> 14) & 0x1)
#define BPORT1_AB_ESR2_LPTM             (0x7f << 16)
#define BPORT1_AB_ESR2_LPTM_GET(_v)     ((_v >> 16) & 0x7f)

#define BPORT1_AB_CRCR_POFFSET          0x44
#define BPORT1_AB_CRCR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CRCR_POFFSET)
#define BPORT1_AB_CRCR_TXCRC            0x7fff
#define BPORT1_AB_CRCR_TXCRC_GET(_v)    (_v & 0x7fff)
#define BPORT1_AB_CRCR_MBCRC            (0x7f << 16)
#define BPORT1_AB_CRCR_MBCRC_GET(_v)    ((_v >> 16) & 0x7f)

#define BPORT1_AB_RXFGMASK_POFFSET      0x48
#define BPORT1_AB_RXFGMASK              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXFGMASK_POFFSET)
#define BPORT1_AB_RXFGMASK_FGM          0xffffffff
#define BPORT1_AB_RXFGMASK_FGM_GET(_v)  (_v & 0xffffffff)

#define BPORT1_AB_RXFIR_POFFSET         0x4c
#define BPORT1_AB_RXFIR                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXFIR_POFFSET)
#define BPORT1_AB_RXFIR_IDHIT           0x1ff
#define BPORT1_AB_RXFIR_IDHIT_GET(_v)   (_v & 0x1ff)

#define BPORT1_AB_RXIMR0_POFFSET        0x880
#define BPORT1_AB_RXIMR0                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXIMR0_POFFSET)
#define BPORT1_AB_RXIMR0_MI             0xffffffff
#define BPORT1_AB_RXIMR0_MI_GET(_v)     (_v & 0xffffffff)

#define BPORT1_AB_RXIMR1_POFFSET        0x884
#define BPORT1_AB_RXIMR1                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXIMR1_POFFSET)
#define BPORT1_AB_RXIMR1_MI             0xffffffff
#define BPORT1_AB_RXIMR1_MI_GET(_v)     (_v & 0xffffffff)

#define BPORT1_AB_RXIMR2_POFFSET        0x888
#define BPORT1_AB_RXIMR2                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXIMR2_POFFSET)
#define BPORT1_AB_RXIMR2_MI             0xffffffff
#define BPORT1_AB_RXIMR2_MI_GET(_v)     (_v & 0xffffffff)

#define BPORT1_AB_RXIMR3_POFFSET        0x88c
#define BPORT1_AB_RXIMR3                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXIMR3_POFFSET)
#define BPORT1_AB_RXIMR3_MI             0xffffffff
#define BPORT1_AB_RXIMR3_MI_GET(_v)     (_v & 0xffffffff)

#define BPORT1_AB_RXIMR4_POFFSET        0x890
#define BPORT1_AB_RXIMR4                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXIMR4_POFFSET)
#define BPORT1_AB_RXIMR4_MI             0xffffffff
#define BPORT1_AB_RXIMR4_MI_GET(_v)     (_v & 0xffffffff)

#define BPORT1_AB_RXIMR5_POFFSET        0x894
#define BPORT1_AB_RXIMR5                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXIMR5_POFFSET)
#define BPORT1_AB_RXIMR5_MI             0xffffffff
#define BPORT1_AB_RXIMR5_MI_GET(_v)     (_v & 0xffffffff)

#define BPORT1_AB_RXIMR6_POFFSET        0x898
#define BPORT1_AB_RXIMR6                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXIMR6_POFFSET)
#define BPORT1_AB_RXIMR6_MI             0xffffffff
#define BPORT1_AB_RXIMR6_MI_GET(_v)     (_v & 0xffffffff)

#define BPORT1_AB_RXIMR7_POFFSET        0x89c
#define BPORT1_AB_RXIMR7                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXIMR7_POFFSET)
#define BPORT1_AB_RXIMR7_MI             0xffffffff
#define BPORT1_AB_RXIMR7_MI_GET(_v)     (_v & 0xffffffff)

#define BPORT1_AB_RXIMR8_POFFSET        0x8a0
#define BPORT1_AB_RXIMR8                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXIMR8_POFFSET)
#define BPORT1_AB_RXIMR8_MI             0xffffffff
#define BPORT1_AB_RXIMR8_MI_GET(_v)     (_v & 0xffffffff)

#define BPORT1_AB_RXIMR9_POFFSET        0x8a4
#define BPORT1_AB_RXIMR9                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXIMR9_POFFSET)
#define BPORT1_AB_RXIMR9_MI             0xffffffff
#define BPORT1_AB_RXIMR9_MI_GET(_v)     (_v & 0xffffffff)

#define BPORT1_AB_RXIMR10_POFFSET       0x8a8
#define BPORT1_AB_RXIMR10               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXIMR10_POFFSET)
#define BPORT1_AB_RXIMR10_MI            0xffffffff
#define BPORT1_AB_RXIMR10_MI_GET(_v)    (_v & 0xffffffff)

#define BPORT1_AB_RXIMR11_POFFSET       0x8ac
#define BPORT1_AB_RXIMR11               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXIMR11_POFFSET)
#define BPORT1_AB_RXIMR11_MI            0xffffffff
#define BPORT1_AB_RXIMR11_MI_GET(_v)    (_v & 0xffffffff)

#define BPORT1_AB_RXIMR12_POFFSET       0x8b0
#define BPORT1_AB_RXIMR12               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXIMR12_POFFSET)
#define BPORT1_AB_RXIMR12_MI            0xffffffff
#define BPORT1_AB_RXIMR12_MI_GET(_v)    (_v & 0xffffffff)

#define BPORT1_AB_RXIMR13_POFFSET       0x8b4
#define BPORT1_AB_RXIMR13               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXIMR13_POFFSET)
#define BPORT1_AB_RXIMR13_MI            0xffffffff
#define BPORT1_AB_RXIMR13_MI_GET(_v)    (_v & 0xffffffff)

#define BPORT1_AB_RXIMR14_POFFSET       0x8b8
#define BPORT1_AB_RXIMR14               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXIMR14_POFFSET)
#define BPORT1_AB_RXIMR14_MI            0xffffffff
#define BPORT1_AB_RXIMR14_MI_GET(_v)    (_v & 0xffffffff)

#define BPORT1_AB_RXIMR15_POFFSET       0x8bc
#define BPORT1_AB_RXIMR15               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXIMR15_POFFSET)
#define BPORT1_AB_RXIMR15_MI            0xffffffff
#define BPORT1_AB_RXIMR15_MI_GET(_v)    (_v & 0xffffffff)


#endif

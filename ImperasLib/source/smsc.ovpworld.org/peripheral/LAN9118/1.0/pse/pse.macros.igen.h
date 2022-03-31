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
#define BPORT1_AB_RX_DATA_FIFO_POFFSET  0x0
#define BPORT1_AB_RX_DATA_FIFO          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RX_DATA_FIFO_POFFSET)

#define BPORT1_AB_RX_DATA_FIFO_1_POFFSET  0x4
#define BPORT1_AB_RX_DATA_FIFO_1        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RX_DATA_FIFO_1_POFFSET)

#define BPORT1_AB_RX_DATA_FIFO_2_POFFSET  0x8
#define BPORT1_AB_RX_DATA_FIFO_2        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RX_DATA_FIFO_2_POFFSET)

#define BPORT1_AB_RX_DATA_FIFO_3_POFFSET  0xc
#define BPORT1_AB_RX_DATA_FIFO_3        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RX_DATA_FIFO_3_POFFSET)

#define BPORT1_AB_RX_DATA_FIFO_4_POFFSET  0x10
#define BPORT1_AB_RX_DATA_FIFO_4        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RX_DATA_FIFO_4_POFFSET)

#define BPORT1_AB_RX_DATA_FIFO_5_POFFSET  0x14
#define BPORT1_AB_RX_DATA_FIFO_5        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RX_DATA_FIFO_5_POFFSET)

#define BPORT1_AB_RX_DATA_FIFO_6_POFFSET  0x18
#define BPORT1_AB_RX_DATA_FIFO_6        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RX_DATA_FIFO_6_POFFSET)

#define BPORT1_AB_RX_DATA_FIFO_7_POFFSET  0x1c
#define BPORT1_AB_RX_DATA_FIFO_7        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RX_DATA_FIFO_7_POFFSET)

#define BPORT1_AB_TX_DATA_FIFO_POFFSET  0x20
#define BPORT1_AB_TX_DATA_FIFO          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TX_DATA_FIFO_POFFSET)

#define BPORT1_AB_TX_DATA_FIFO_1_POFFSET  0x24
#define BPORT1_AB_TX_DATA_FIFO_1        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TX_DATA_FIFO_1_POFFSET)

#define BPORT1_AB_TX_DATA_FIFO_2_POFFSET  0x28
#define BPORT1_AB_TX_DATA_FIFO_2        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TX_DATA_FIFO_2_POFFSET)

#define BPORT1_AB_TX_DATA_FIFO_3_POFFSET  0x2c
#define BPORT1_AB_TX_DATA_FIFO_3        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TX_DATA_FIFO_3_POFFSET)

#define BPORT1_AB_TX_DATA_FIFO_4_POFFSET  0x30
#define BPORT1_AB_TX_DATA_FIFO_4        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TX_DATA_FIFO_4_POFFSET)

#define BPORT1_AB_TX_DATA_FIFO_5_POFFSET  0x34
#define BPORT1_AB_TX_DATA_FIFO_5        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TX_DATA_FIFO_5_POFFSET)

#define BPORT1_AB_TX_DATA_FIFO_6_POFFSET  0x38
#define BPORT1_AB_TX_DATA_FIFO_6        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TX_DATA_FIFO_6_POFFSET)

#define BPORT1_AB_TX_DATA_FIFO_7_POFFSET  0x3c
#define BPORT1_AB_TX_DATA_FIFO_7        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TX_DATA_FIFO_7_POFFSET)

#define BPORT1_AB_RX_STATUS_FIFO_POFFSET  0x40
#define BPORT1_AB_RX_STATUS_FIFO        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RX_STATUS_FIFO_POFFSET)

#define BPORT1_AB_RX_STATUS_FIFO_PEEK_POFFSET  0x44
#define BPORT1_AB_RX_STATUS_FIFO_PEEK   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RX_STATUS_FIFO_PEEK_POFFSET)

#define BPORT1_AB_TX_STATUS_FIFO_POFFSET  0x48
#define BPORT1_AB_TX_STATUS_FIFO        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TX_STATUS_FIFO_POFFSET)

#define BPORT1_AB_TX_STATUS_FIFO_PEEK_POFFSET  0x4c
#define BPORT1_AB_TX_STATUS_FIFO_PEEK   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TX_STATUS_FIFO_PEEK_POFFSET)

#define BPORT1_AB_ID_REV_POFFSET        0x50
#define BPORT1_AB_ID_REV                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ID_REV_POFFSET)
#define BPORT1_AB_ID_REV_ID             (0xffff << 16)
#define BPORT1_AB_ID_REV_ID_GET(_v)     ((_v >> 16) & 0xffff)
#define BPORT1_AB_ID_REV_REV            0xffff
#define BPORT1_AB_ID_REV_REV_GET(_v)    (_v & 0xffff)

#define BPORT1_AB_IRQ_CFG_POFFSET       0x54
#define BPORT1_AB_IRQ_CFG               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IRQ_CFG_POFFSET)
#define BPORT1_AB_IRQ_CFG_INT_DEAS      (0xff << 24)
#define BPORT1_AB_IRQ_CFG_INT_DEAS_GET(_v)  ((_v >> 24) & 0xff)
#define BPORT1_AB_IRQ_CFG_INT_DEAS_CLR  (0x1 << 14)
#define BPORT1_AB_IRQ_CFG_INT_DEAS_CLR_GET(_v)  ((_v >> 14) & 0x1)
#define BPORT1_AB_IRQ_CFG_INT_DEAS_STS  (0x1 << 13)
#define BPORT1_AB_IRQ_CFG_INT_DEAS_STS_GET(_v)  ((_v >> 13) & 0x1)
#define BPORT1_AB_IRQ_CFG_IRQ_INT       (0x1 << 12)
#define BPORT1_AB_IRQ_CFG_IRQ_INT_GET(_v)  ((_v >> 12) & 0x1)
#define BPORT1_AB_IRQ_CFG_IRQ_EN        (0x1 << 8)
#define BPORT1_AB_IRQ_CFG_IRQ_EN_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_IRQ_CFG_IRQ_POL       (0x1 << 4)
#define BPORT1_AB_IRQ_CFG_IRQ_POL_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_IRQ_CFG_IRQ_TYPE      0x1
#define BPORT1_AB_IRQ_CFG_IRQ_TYPE_GET(_v)  (_v & 0x1)

#define BPORT1_AB_INT_STS_POFFSET       0x58
#define BPORT1_AB_INT_STS               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INT_STS_POFFSET)
#define BPORT1_AB_INT_STS_SW_INT        (0x1 << 31)
#define BPORT1_AB_INT_STS_SW_INT_GET(_v)  ((_v >> 31) & 0x1)
#define BPORT1_AB_INT_STS_TXSTOP_INT    (0x1 << 25)
#define BPORT1_AB_INT_STS_TXSTOP_INT_GET(_v)  ((_v >> 25) & 0x1)
#define BPORT1_AB_INT_STS_RXSTOP_INT    (0x1 << 24)
#define BPORT1_AB_INT_STS_RXSTOP_INT_GET(_v)  ((_v >> 24) & 0x1)
#define BPORT1_AB_INT_STS_RXDFH_INT     (0x1 << 23)
#define BPORT1_AB_INT_STS_RXDFH_INT_GET(_v)  ((_v >> 23) & 0x1)
#define BPORT1_AB_INT_STS_TX_IOC        (0x1 << 21)
#define BPORT1_AB_INT_STS_TX_IOC_GET(_v)  ((_v >> 21) & 0x1)
#define BPORT1_AB_INT_STS_RXD_INT       (0x1 << 20)
#define BPORT1_AB_INT_STS_RXD_INT_GET(_v)  ((_v >> 20) & 0x1)
#define BPORT1_AB_INT_STS_GPT_INT       (0x1 << 19)
#define BPORT1_AB_INT_STS_GPT_INT_GET(_v)  ((_v >> 19) & 0x1)
#define BPORT1_AB_INT_STS_PHY_INT       (0x1 << 18)
#define BPORT1_AB_INT_STS_PHY_INT_GET(_v)  ((_v >> 18) & 0x1)
#define BPORT1_AB_INT_STS_PME_INT       (0x1 << 17)
#define BPORT1_AB_INT_STS_PME_INT_GET(_v)  ((_v >> 17) & 0x1)
#define BPORT1_AB_INT_STS_TXSO          (0x1 << 16)
#define BPORT1_AB_INT_STS_TXSO_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_INT_STS_RWT           (0x1 << 15)
#define BPORT1_AB_INT_STS_RWT_GET(_v)   ((_v >> 15) & 0x1)
#define BPORT1_AB_INT_STS_RXE           (0x1 << 14)
#define BPORT1_AB_INT_STS_RXE_GET(_v)   ((_v >> 14) & 0x1)
#define BPORT1_AB_INT_STS_TXE           (0x1 << 13)
#define BPORT1_AB_INT_STS_TXE_GET(_v)   ((_v >> 13) & 0x1)
#define BPORT1_AB_INT_STS_TDFO          (0x1 << 10)
#define BPORT1_AB_INT_STS_TDFO_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_INT_STS_TDFA          (0x1 << 9)
#define BPORT1_AB_INT_STS_TDFA_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_INT_STS_TSFF          (0x1 << 8)
#define BPORT1_AB_INT_STS_TSFF_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_INT_STS_TSFL          (0x1 << 7)
#define BPORT1_AB_INT_STS_TSFL_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_INT_STS_RXDF_INT      (0x1 << 6)
#define BPORT1_AB_INT_STS_RXDF_INT_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_INT_STS_RSFF          (0x1 << 4)
#define BPORT1_AB_INT_STS_RSFF_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_INT_STS_RSFL          (0x1 << 3)
#define BPORT1_AB_INT_STS_RSFL_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_INT_STS_GPIOX_INT     0x7
#define BPORT1_AB_INT_STS_GPIOX_INT_GET(_v)  (_v & 0x7)

#define BPORT1_AB_INT_EN_POFFSET        0x5c
#define BPORT1_AB_INT_EN                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INT_EN_POFFSET)
#define BPORT1_AB_INT_EN_SW_INT_EN      (0x1 << 31)
#define BPORT1_AB_INT_EN_SW_INT_EN_GET(_v)  ((_v >> 31) & 0x1)
#define BPORT1_AB_INT_EN_TXSTOP_INT_EN  (0x1 << 25)
#define BPORT1_AB_INT_EN_TXSTOP_INT_EN_GET(_v)  ((_v >> 25) & 0x1)
#define BPORT1_AB_INT_EN_RXSTOP_INT_EN  (0x1 << 24)
#define BPORT1_AB_INT_EN_RXSTOP_INT_EN_GET(_v)  ((_v >> 24) & 0x1)
#define BPORT1_AB_INT_EN_RXDFH_INT_EN   (0x1 << 23)
#define BPORT1_AB_INT_EN_RXDFH_INT_EN_GET(_v)  ((_v >> 23) & 0x1)
#define BPORT1_AB_INT_EN_TIOC_INT_EN    (0x1 << 21)
#define BPORT1_AB_INT_EN_TIOC_INT_EN_GET(_v)  ((_v >> 21) & 0x1)
#define BPORT1_AB_INT_EN_RXD_INT        (0x1 << 20)
#define BPORT1_AB_INT_EN_RXD_INT_GET(_v)  ((_v >> 20) & 0x1)
#define BPORT1_AB_INT_EN_GPT_INT_EN     (0x1 << 19)
#define BPORT1_AB_INT_EN_GPT_INT_EN_GET(_v)  ((_v >> 19) & 0x1)
#define BPORT1_AB_INT_EN_PHY_INT_EN     (0x1 << 18)
#define BPORT1_AB_INT_EN_PHY_INT_EN_GET(_v)  ((_v >> 18) & 0x1)
#define BPORT1_AB_INT_EN_PME_INT_EN     (0x1 << 17)
#define BPORT1_AB_INT_EN_PME_INT_EN_GET(_v)  ((_v >> 17) & 0x1)
#define BPORT1_AB_INT_EN_TXSO_EN        (0x1 << 16)
#define BPORT1_AB_INT_EN_TXSO_EN_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_INT_EN_RWT_INT_EN     (0x1 << 15)
#define BPORT1_AB_INT_EN_RWT_INT_EN_GET(_v)  ((_v >> 15) & 0x1)
#define BPORT1_AB_INT_EN_RXE_INT_EN     (0x1 << 14)
#define BPORT1_AB_INT_EN_RXE_INT_EN_GET(_v)  ((_v >> 14) & 0x1)
#define BPORT1_AB_INT_EN_TXE_INT_EN     (0x1 << 13)
#define BPORT1_AB_INT_EN_TXE_INT_EN_GET(_v)  ((_v >> 13) & 0x1)
#define BPORT1_AB_INT_EN_TDFO_INT_EN    (0x1 << 10)
#define BPORT1_AB_INT_EN_TDFO_INT_EN_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_INT_EN_TDFA_INT_EN    (0x1 << 9)
#define BPORT1_AB_INT_EN_TDFA_INT_EN_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_INT_EN_TSFF_INT_EN    (0x1 << 8)
#define BPORT1_AB_INT_EN_TSFF_INT_EN_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_INT_EN_TSFL_INT_EN    (0x1 << 7)
#define BPORT1_AB_INT_EN_TSFL_INT_EN_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_INT_EN_RXDF_INT_EN    (0x1 << 6)
#define BPORT1_AB_INT_EN_RXDF_INT_EN_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_INT_EN_RSFF_INT_EN    (0x1 << 4)
#define BPORT1_AB_INT_EN_RSFF_INT_EN_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_INT_EN_RSFL_INT_EN    (0x1 << 3)
#define BPORT1_AB_INT_EN_RSFL_INT_EN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_INT_EN_GPIOX_INT_EN   0x7
#define BPORT1_AB_INT_EN_GPIOX_INT_EN_GET(_v)  (_v & 0x7)

#define BPORT1_AB_BYTE_TEST_POFFSET     0x64
#define BPORT1_AB_BYTE_TEST             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BYTE_TEST_POFFSET)

#define BPORT1_AB_FIFO_INT_POFFSET      0x68
#define BPORT1_AB_FIFO_INT              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FIFO_INT_POFFSET)
#define BPORT1_AB_FIFO_INT_TXDATAAVAILL  (0xff << 24)
#define BPORT1_AB_FIFO_INT_TXDATAAVAILL_GET(_v)  ((_v >> 24) & 0xff)
#define BPORT1_AB_FIFO_INT_TXSTATUSL    (0xff << 16)
#define BPORT1_AB_FIFO_INT_TXSTATUSL_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_AB_FIFO_INT_RXSTATUSL    0xff
#define BPORT1_AB_FIFO_INT_RXSTATUSL_GET(_v)  (_v & 0xff)

#define BPORT1_AB_RX_CFG_POFFSET        0x6c
#define BPORT1_AB_RX_CFG                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RX_CFG_POFFSET)
#define BPORT1_AB_RX_CFG_RXENDALIGN     (0x3 << 30)
#define BPORT1_AB_RX_CFG_RXENDALIGN_GET(_v)  ((_v >> 30) & 0x3)
#define BPORT1_AB_RX_CFG_RX_DMA_CNT     (0xfff << 16)
#define BPORT1_AB_RX_CFG_RX_DMA_CNT_GET(_v)  ((_v >> 16) & 0xfff)
#define BPORT1_AB_RX_CFG_RX_DUMP        (0x1 << 15)
#define BPORT1_AB_RX_CFG_RX_DUMP_GET(_v)  ((_v >> 15) & 0x1)
#define BPORT1_AB_RX_CFG_RXDOFF         (0x1f << 8)
#define BPORT1_AB_RX_CFG_RXDOFF_GET(_v)  ((_v >> 8) & 0x1f)

#define BPORT1_AB_TX_CFG_POFFSET        0x70
#define BPORT1_AB_TX_CFG                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TX_CFG_POFFSET)
#define BPORT1_AB_TX_CFG_TXS_DUMP       (0x1 << 15)
#define BPORT1_AB_TX_CFG_TXS_DUMP_GET(_v)  ((_v >> 15) & 0x1)
#define BPORT1_AB_TX_CFG_TXD_DUMP       (0x1 << 14)
#define BPORT1_AB_TX_CFG_TXD_DUMP_GET(_v)  ((_v >> 14) & 0x1)
#define BPORT1_AB_TX_CFG_TXSAO          (0x1 << 2)
#define BPORT1_AB_TX_CFG_TXSAO_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_TX_CFG_TX_ON          (0x1 << 1)
#define BPORT1_AB_TX_CFG_TX_ON_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_TX_CFG_STOP_TX        0x1
#define BPORT1_AB_TX_CFG_STOP_TX_GET(_v)  (_v & 0x1)

#define BPORT1_AB_HW_CFG_POFFSET        0x74
#define BPORT1_AB_HW_CFG                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HW_CFG_POFFSET)
#define BPORT1_AB_HW_CFG_MBO            (0x1 << 20)
#define BPORT1_AB_HW_CFG_MBO_GET(_v)    ((_v >> 20) & 0x1)
#define BPORT1_AB_HW_CFG_TX_FIF_SZ      (0xf << 16)
#define BPORT1_AB_HW_CFG_TX_FIF_SZ_GET(_v)  ((_v >> 16) & 0xf)
#define BPORT1_AB_HW_CFG_MODE1632       (0x1 << 2)
#define BPORT1_AB_HW_CFG_MODE1632_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_HW_CFG_SRST_TO        (0x1 << 1)
#define BPORT1_AB_HW_CFG_SRST_TO_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_HW_CFG_SRST           0x1
#define BPORT1_AB_HW_CFG_SRST_GET(_v)   (_v & 0x1)

#define BPORT1_AB_RX_DP_CTRL_POFFSET    0x78
#define BPORT1_AB_RX_DP_CTRL            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RX_DP_CTRL_POFFSET)
#define BPORT1_AB_RX_DP_CTRL_RX_FFWD    (0x1 << 31)
#define BPORT1_AB_RX_DP_CTRL_RX_FFWD_GET(_v)  ((_v >> 31) & 0x1)

#define BPORT1_AB_RX_FIFO_INF_POFFSET   0x7c
#define BPORT1_AB_RX_FIFO_INF           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RX_FIFO_INF_POFFSET)
#define BPORT1_AB_RX_FIFO_INF_RXSUSED   (0xff << 16)
#define BPORT1_AB_RX_FIFO_INF_RXSUSED_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_AB_RX_FIFO_INF_RXDUSED   0xffff
#define BPORT1_AB_RX_FIFO_INF_RXDUSED_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_TX_FIFO_INF_POFFSET   0x80
#define BPORT1_AB_TX_FIFO_INF           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TX_FIFO_INF_POFFSET)
#define BPORT1_AB_TX_FIFO_INF_TXSUSED   (0xff << 16)
#define BPORT1_AB_TX_FIFO_INF_TXSUSED_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_AB_TX_FIFO_INF_TXDFREE   0xffff
#define BPORT1_AB_TX_FIFO_INF_TXDFREE_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_PMT_CTRL_POFFSET      0x84
#define BPORT1_AB_PMT_CTRL              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PMT_CTRL_POFFSET)
#define BPORT1_AB_PMT_CTRL_PM_MODE      (0x3 << 12)
#define BPORT1_AB_PMT_CTRL_PM_MODE_GET(_v)  ((_v >> 12) & 0x3)
#define BPORT1_AB_PMT_CTRL_PHY_RST      (0x1 << 10)
#define BPORT1_AB_PMT_CTRL_PHY_RST_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_PMT_CTRL_WOL_EN       (0x1 << 9)
#define BPORT1_AB_PMT_CTRL_WOL_EN_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_PMT_CTRL_ED_EN        (0x1 << 8)
#define BPORT1_AB_PMT_CTRL_ED_EN_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_PMT_CTRL_PME_TYPE     (0x1 << 6)
#define BPORT1_AB_PMT_CTRL_PME_TYPE_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_PMT_CTRL_WUPS         (0x3 << 4)
#define BPORT1_AB_PMT_CTRL_WUPS_GET(_v)  ((_v >> 4) & 0x3)
#define BPORT1_AB_PMT_CTRL_PME_IND      (0x1 << 3)
#define BPORT1_AB_PMT_CTRL_PME_IND_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_PMT_CTRL_PME_POL      (0x1 << 2)
#define BPORT1_AB_PMT_CTRL_PME_POL_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_PMT_CTRL_PME_EN       (0x1 << 1)
#define BPORT1_AB_PMT_CTRL_PME_EN_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_PMT_CTRL_READY        0x1
#define BPORT1_AB_PMT_CTRL_READY_GET(_v)  (_v & 0x1)

#define BPORT1_AB_GPIO_CFG_POFFSET      0x88
#define BPORT1_AB_GPIO_CFG              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPIO_CFG_POFFSET)
#define BPORT1_AB_GPIO_CFG_LEDX_EN      (0x7 << 28)
#define BPORT1_AB_GPIO_CFG_LEDX_EN_GET(_v)  ((_v >> 28) & 0x7)
#define BPORT1_AB_GPIO_CFG_GPIO_INT_POL  (0x7 << 24)
#define BPORT1_AB_GPIO_CFG_GPIO_INT_POL_GET(_v)  ((_v >> 24) & 0x7)
#define BPORT1_AB_GPIO_CFG_EEPR_EN      (0x7 << 20)
#define BPORT1_AB_GPIO_CFG_EEPR_EN_GET(_v)  ((_v >> 20) & 0x7)
#define BPORT1_AB_GPIO_CFG_GPIOBUFN     (0x7 << 16)
#define BPORT1_AB_GPIO_CFG_GPIOBUFN_GET(_v)  ((_v >> 16) & 0x7)
#define BPORT1_AB_GPIO_CFG_GPDIRN       (0x7 << 8)
#define BPORT1_AB_GPIO_CFG_GPDIRN_GET(_v)  ((_v >> 8) & 0x7)
#define BPORT1_AB_GPIO_CFG_GPODN        (0x3 << 3)
#define BPORT1_AB_GPIO_CFG_GPODN_GET(_v)  ((_v >> 3) & 0x3)
#define BPORT1_AB_GPIO_CFG_GPIODN       0x7
#define BPORT1_AB_GPIO_CFG_GPIODN_GET(_v)  (_v & 0x7)

#define BPORT1_AB_GPT_CFG_POFFSET       0x8c
#define BPORT1_AB_GPT_CFG               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPT_CFG_POFFSET)
#define BPORT1_AB_GPT_CFG_TIMER_EN      (0x1 << 29)
#define BPORT1_AB_GPT_CFG_TIMER_EN_GET(_v)  ((_v >> 29) & 0x1)
#define BPORT1_AB_GPT_CFG_GPT_LOAD      0xffff
#define BPORT1_AB_GPT_CFG_GPT_LOAD_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_GPT_CNT_POFFSET       0x90
#define BPORT1_AB_GPT_CNT               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPT_CNT_POFFSET)
#define BPORT1_AB_GPT_CNT_GPT_CNT       0xffff
#define BPORT1_AB_GPT_CNT_GPT_CNT_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_WORD_SWAP_POFFSET     0x98
#define BPORT1_AB_WORD_SWAP             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WORD_SWAP_POFFSET)

#define BPORT1_AB_FREE_RUN_POFFSET      0x9c
#define BPORT1_AB_FREE_RUN              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FREE_RUN_POFFSET)
#define BPORT1_AB_FREE_RUN_FR_CNT       0xffffffff
#define BPORT1_AB_FREE_RUN_FR_CNT_GET(_v)  (_v & 0xffffffff)

#define BPORT1_AB_RX_DROP_POFFSET       0xa0
#define BPORT1_AB_RX_DROP               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RX_DROP_POFFSET)
#define BPORT1_AB_RX_DROP_RX_DFC        0xffffffff
#define BPORT1_AB_RX_DROP_RX_DFC_GET(_v)  (_v & 0xffffffff)

#define BPORT1_AB_MAC_CSR_CMD_POFFSET   0xa4
#define BPORT1_AB_MAC_CSR_CMD           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MAC_CSR_CMD_POFFSET)
#define BPORT1_AB_MAC_CSR_CMD_CSRBUSY   (0x1 << 31)
#define BPORT1_AB_MAC_CSR_CMD_CSRBUSY_GET(_v)  ((_v >> 31) & 0x1)
#define BPORT1_AB_MAC_CSR_CMD_RNW       (0x1 << 30)
#define BPORT1_AB_MAC_CSR_CMD_RNW_GET(_v)  ((_v >> 30) & 0x1)
#define BPORT1_AB_MAC_CSR_CMD_CSRADDRESS  0xff
#define BPORT1_AB_MAC_CSR_CMD_CSRADDRESS_GET(_v)  (_v & 0xff)

#define BPORT1_AB_MAC_CSR_DATA_POFFSET  0xa8
#define BPORT1_AB_MAC_CSR_DATA          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MAC_CSR_DATA_POFFSET)
#define BPORT1_AB_MAC_CSR_DATA_MACCSRDATA  0xffffffff
#define BPORT1_AB_MAC_CSR_DATA_MACCSRDATA_GET(_v)  (_v & 0xffffffff)

#define BPORT1_AB_AFC_CFG_POFFSET       0xac
#define BPORT1_AB_AFC_CFG               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AFC_CFG_POFFSET)
#define BPORT1_AB_AFC_CFG_AFC_HI        (0xff << 16)
#define BPORT1_AB_AFC_CFG_AFC_HI_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_AB_AFC_CFG_AFC_LO        (0xff << 8)
#define BPORT1_AB_AFC_CFG_AFC_LO_GET(_v)  ((_v >> 8) & 0xff)
#define BPORT1_AB_AFC_CFG_BACK_DUR      (0xf << 4)
#define BPORT1_AB_AFC_CFG_BACK_DUR_GET(_v)  ((_v >> 4) & 0xf)
#define BPORT1_AB_AFC_CFG_FCMULT        (0x1 << 3)
#define BPORT1_AB_AFC_CFG_FCMULT_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_AFC_CFG_FCBRD         (0x1 << 2)
#define BPORT1_AB_AFC_CFG_FCBRD_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_AFC_CFG_FCADD         (0x1 << 1)
#define BPORT1_AB_AFC_CFG_FCADD_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_AFC_CFG_FCANY         0x1
#define BPORT1_AB_AFC_CFG_FCANY_GET(_v)  (_v & 0x1)

#define BPORT1_AB_E2P_CMD_POFFSET       0xb0
#define BPORT1_AB_E2P_CMD               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_E2P_CMD_POFFSET)
#define BPORT1_AB_E2P_CMD_EPCBUSY       (0x1 << 31)
#define BPORT1_AB_E2P_CMD_EPCBUSY_GET(_v)  ((_v >> 31) & 0x1)
#define BPORT1_AB_E2P_CMD_EPCCOMMAND    (0x7 << 28)
#define BPORT1_AB_E2P_CMD_EPCCOMMAND_GET(_v)  ((_v >> 28) & 0x7)
#define BPORT1_AB_E2P_CMD_EPCTIMEOUT    (0x1 << 9)
#define BPORT1_AB_E2P_CMD_EPCTIMEOUT_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_E2P_CMD_MACADDRLOADED  (0x1 << 8)
#define BPORT1_AB_E2P_CMD_MACADDRLOADED_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_E2P_CMD_EPCADDR       0xff
#define BPORT1_AB_E2P_CMD_EPCADDR_GET(_v)  (_v & 0xff)

#define BPORT1_AB_E2P_DATA_POFFSET      0xb4
#define BPORT1_AB_E2P_DATA              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_E2P_DATA_POFFSET)
#define BPORT1_AB_E2P_DATA_EEPROMDATA   0xff
#define BPORT1_AB_E2P_DATA_EEPROMDATA_GET(_v)  (_v & 0xff)


#endif

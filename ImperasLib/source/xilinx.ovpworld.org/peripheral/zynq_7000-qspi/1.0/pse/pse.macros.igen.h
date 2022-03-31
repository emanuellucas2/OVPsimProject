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

// Set the macro 'BPAXI' to the base of port 'bpAXI'
#ifndef BPAXI
#error BPAXI is undefined. It needs to be set to the port base address
#endif
// Set the macro 'BPAPB' to the base of port 'bpAPB'
#ifndef BPAPB
#error BPAPB is undefined. It needs to be set to the port base address
#endif


#define BPAXI_ABM_POFFSET               0x0
#define BPAXI_ABM_FLASH_POFFSET         0x0
#define BPAXI_ABM_FLASH                 (BPAXI + BPAXI_ABM_POFFSET + BPAXI_ABM_FLASH_POFFSET)
#define BPAXI_ABM_FLASH_BYTES           0x2000000


#define BPAPB_AB_POFFSET                0x0
#define BPAPB_AB_CONFIG_REG_POFFSET     0x0
#define BPAPB_AB_CONFIG_REG             (BPAPB + BPAPB_AB_POFFSET + BPAPB_AB_CONFIG_REG_POFFSET)
#define BPAPB_AB_CONFIG_REG_LEG_FLSH    (0x1 << 31)
#define BPAPB_AB_CONFIG_REG_LEG_FLSH_GET(_v)  ((_v >> 31) & 0x1)
#define BPAPB_AB_CONFIG_REG_ENDIAN      (0x1 << 26)
#define BPAPB_AB_CONFIG_REG_ENDIAN_GET(_v)  ((_v >> 26) & 0x1)
#define BPAPB_AB_CONFIG_REG_HOLDB_DR    (0x1 << 19)
#define BPAPB_AB_CONFIG_REG_HOLDB_DR_GET(_v)  ((_v >> 19) & 0x1)
#define BPAPB_AB_CONFIG_REG_MAN_START_COM  (0x1 << 16)
#define BPAPB_AB_CONFIG_REG_MAN_START_COM_GET(_v)  ((_v >> 16) & 0x1)
#define BPAPB_AB_CONFIG_REG_MANUAL_CS   (0x1 << 15)
#define BPAPB_AB_CONFIG_REG_MANUAL_CS_GET(_v)  ((_v >> 15) & 0x1)
#define BPAPB_AB_CONFIG_REG_PCS         (0x1 << 10)
#define BPAPB_AB_CONFIG_REG_PCS_GET(_v)  ((_v >> 10) & 0x1)
#define BPAPB_AB_CONFIG_REG_REF_CLK     (0x1 << 8)
#define BPAPB_AB_CONFIG_REG_REF_CLK_GET(_v)  ((_v >> 8) & 0x1)
#define BPAPB_AB_CONFIG_REG_FIFO_WIDTH  (0x3 << 6)
#define BPAPB_AB_CONFIG_REG_FIFO_WIDTH_GET(_v)  ((_v >> 6) & 0x3)
#define BPAPB_AB_CONFIG_REG_BAUD_RATE_DIC  (0x7 << 3)
#define BPAPB_AB_CONFIG_REG_BAUD_RATE_DIC_GET(_v)  ((_v >> 3) & 0x7)
#define BPAPB_AB_CONFIG_REG_CLK_PH      (0x1 << 2)
#define BPAPB_AB_CONFIG_REG_CLK_PH_GET(_v)  ((_v >> 2) & 0x1)
#define BPAPB_AB_CONFIG_REG_CLK_POL     (0x1 << 1)
#define BPAPB_AB_CONFIG_REG_CLK_POL_GET(_v)  ((_v >> 1) & 0x1)
#define BPAPB_AB_CONFIG_REG_MODE_SEL    0x1
#define BPAPB_AB_CONFIG_REG_MODE_SEL_GET(_v)  (_v & 0x1)

#define BPAPB_AB_INTR_STATUS_REG_POFFSET  0x4
#define BPAPB_AB_INTR_STATUS_REG        (BPAPB + BPAPB_AB_POFFSET + BPAPB_AB_INTR_STATUS_REG_POFFSET)
#define BPAPB_AB_INTR_STATUS_REG_TXUF   (0x1 << 6)
#define BPAPB_AB_INTR_STATUS_REG_TXUF_GET(_v)  ((_v >> 6) & 0x1)
#define BPAPB_AB_INTR_STATUS_REG_RXFULL  (0x1 << 5)
#define BPAPB_AB_INTR_STATUS_REG_RXFULL_GET(_v)  ((_v >> 5) & 0x1)
#define BPAPB_AB_INTR_STATUS_REG_RXNEMPTY  (0x1 << 4)
#define BPAPB_AB_INTR_STATUS_REG_RXNEMPTY_GET(_v)  ((_v >> 4) & 0x1)
#define BPAPB_AB_INTR_STATUS_REG_TXFULL  (0x1 << 3)
#define BPAPB_AB_INTR_STATUS_REG_TXFULL_GET(_v)  ((_v >> 3) & 0x1)
#define BPAPB_AB_INTR_STATUS_REG_TXOW   (0x1 << 2)
#define BPAPB_AB_INTR_STATUS_REG_TXOW_GET(_v)  ((_v >> 2) & 0x1)
#define BPAPB_AB_INTR_STATUS_REG_RXOVR  0x1
#define BPAPB_AB_INTR_STATUS_REG_RXOVR_GET(_v)  (_v & 0x1)

#define BPAPB_AB_INTRPT_EN_REG_POFFSET  0x8
#define BPAPB_AB_INTRPT_EN_REG          (BPAPB + BPAPB_AB_POFFSET + BPAPB_AB_INTRPT_EN_REG_POFFSET)
#define BPAPB_AB_INTRPT_EN_REG_TXUF     (0x1 << 6)
#define BPAPB_AB_INTRPT_EN_REG_TXUF_GET(_v)  ((_v >> 6) & 0x1)
#define BPAPB_AB_INTRPT_EN_REG_RXFULL   (0x1 << 5)
#define BPAPB_AB_INTRPT_EN_REG_RXFULL_GET(_v)  ((_v >> 5) & 0x1)
#define BPAPB_AB_INTRPT_EN_REG_RXNEMPTY  (0x1 << 4)
#define BPAPB_AB_INTRPT_EN_REG_RXNEMPTY_GET(_v)  ((_v >> 4) & 0x1)
#define BPAPB_AB_INTRPT_EN_REG_TXFULL   (0x1 << 3)
#define BPAPB_AB_INTRPT_EN_REG_TXFULL_GET(_v)  ((_v >> 3) & 0x1)
#define BPAPB_AB_INTRPT_EN_REG_TXOW     (0x1 << 2)
#define BPAPB_AB_INTRPT_EN_REG_TXOW_GET(_v)  ((_v >> 2) & 0x1)
#define BPAPB_AB_INTRPT_EN_REG_RXOVR    0x1
#define BPAPB_AB_INTRPT_EN_REG_RXOVR_GET(_v)  (_v & 0x1)

#define BPAPB_AB_INTRPT_DIS_REG_POFFSET  0xc
#define BPAPB_AB_INTRPT_DIS_REG         (BPAPB + BPAPB_AB_POFFSET + BPAPB_AB_INTRPT_DIS_REG_POFFSET)
#define BPAPB_AB_INTRPT_DIS_REG_TXUF    (0x1 << 6)
#define BPAPB_AB_INTRPT_DIS_REG_TXUF_GET(_v)  ((_v >> 6) & 0x1)
#define BPAPB_AB_INTRPT_DIS_REG_RXFULL  (0x1 << 5)
#define BPAPB_AB_INTRPT_DIS_REG_RXFULL_GET(_v)  ((_v >> 5) & 0x1)
#define BPAPB_AB_INTRPT_DIS_REG_RXNEMPTY  (0x1 << 4)
#define BPAPB_AB_INTRPT_DIS_REG_RXNEMPTY_GET(_v)  ((_v >> 4) & 0x1)
#define BPAPB_AB_INTRPT_DIS_REG_TXFULL  (0x1 << 3)
#define BPAPB_AB_INTRPT_DIS_REG_TXFULL_GET(_v)  ((_v >> 3) & 0x1)
#define BPAPB_AB_INTRPT_DIS_REG_TXOW    (0x1 << 2)
#define BPAPB_AB_INTRPT_DIS_REG_TXOW_GET(_v)  ((_v >> 2) & 0x1)
#define BPAPB_AB_INTRPT_DIS_REG_RXOVR   0x1
#define BPAPB_AB_INTRPT_DIS_REG_RXOVR_GET(_v)  (_v & 0x1)

#define BPAPB_AB_INTRPT_MASK_REG_POFFSET  0x10
#define BPAPB_AB_INTRPT_MASK_REG        (BPAPB + BPAPB_AB_POFFSET + BPAPB_AB_INTRPT_MASK_REG_POFFSET)
#define BPAPB_AB_INTRPT_MASK_REG_TXUF   (0x1 << 6)
#define BPAPB_AB_INTRPT_MASK_REG_TXUF_GET(_v)  ((_v >> 6) & 0x1)
#define BPAPB_AB_INTRPT_MASK_REG_RXFULL  (0x1 << 5)
#define BPAPB_AB_INTRPT_MASK_REG_RXFULL_GET(_v)  ((_v >> 5) & 0x1)
#define BPAPB_AB_INTRPT_MASK_REG_RXNEMPTY  (0x1 << 4)
#define BPAPB_AB_INTRPT_MASK_REG_RXNEMPTY_GET(_v)  ((_v >> 4) & 0x1)
#define BPAPB_AB_INTRPT_MASK_REG_TXFULL  (0x1 << 3)
#define BPAPB_AB_INTRPT_MASK_REG_TXFULL_GET(_v)  ((_v >> 3) & 0x1)
#define BPAPB_AB_INTRPT_MASK_REG_TXOW   (0x1 << 2)
#define BPAPB_AB_INTRPT_MASK_REG_TXOW_GET(_v)  ((_v >> 2) & 0x1)
#define BPAPB_AB_INTRPT_MASK_REG_RXOVR  0x1
#define BPAPB_AB_INTRPT_MASK_REG_RXOVR_GET(_v)  (_v & 0x1)

#define BPAPB_AB_EN_REG_POFFSET         0x14
#define BPAPB_AB_EN_REG                 (BPAPB + BPAPB_AB_POFFSET + BPAPB_AB_EN_REG_POFFSET)
#define BPAPB_AB_EN_REG_ENABLE          0x1
#define BPAPB_AB_EN_REG_ENABLE_GET(_v)  (_v & 0x1)

#define BPAPB_AB_DELAY_REG_POFFSET      0x18
#define BPAPB_AB_DELAY_REG              (BPAPB + BPAPB_AB_POFFSET + BPAPB_AB_DELAY_REG_POFFSET)
#define BPAPB_AB_DELAY_REG_NSS          (0xff << 24)
#define BPAPB_AB_DELAY_REG_NSS_GET(_v)  ((_v >> 24) & 0xff)
#define BPAPB_AB_DELAY_REG_BTWN         (0xff << 16)
#define BPAPB_AB_DELAY_REG_BTWN_GET(_v)  ((_v >> 16) & 0xff)
#define BPAPB_AB_DELAY_REG_AFTER        (0xff << 8)
#define BPAPB_AB_DELAY_REG_AFTER_GET(_v)  ((_v >> 8) & 0xff)
#define BPAPB_AB_DELAY_REG_INIT         0xff
#define BPAPB_AB_DELAY_REG_INIT_GET(_v)  (_v & 0xff)

#define BPAPB_AB_TXD0_POFFSET           0x1c
#define BPAPB_AB_TXD0                   (BPAPB + BPAPB_AB_POFFSET + BPAPB_AB_TXD0_POFFSET)

#define BPAPB_AB_RX_DATA_REG_POFFSET    0x20
#define BPAPB_AB_RX_DATA_REG            (BPAPB + BPAPB_AB_POFFSET + BPAPB_AB_RX_DATA_REG_POFFSET)

#define BPAPB_AB_SLAVE_IDLE_COUNT_REG_POFFSET  0x24
#define BPAPB_AB_SLAVE_IDLE_COUNT_REG   (BPAPB + BPAPB_AB_POFFSET + BPAPB_AB_SLAVE_IDLE_COUNT_REG_POFFSET)
#define BPAPB_AB_SLAVE_IDLE_COUNT_REG_MASK  0xff
#define BPAPB_AB_SLAVE_IDLE_COUNT_REG_MASK_GET(_v)  (_v & 0xff)

#define BPAPB_AB_TX_THRES_REG_POFFSET   0x28
#define BPAPB_AB_TX_THRES_REG           (BPAPB + BPAPB_AB_POFFSET + BPAPB_AB_TX_THRES_REG_POFFSET)

#define BPAPB_AB_RX_THRES_REG_POFFSET   0x2c
#define BPAPB_AB_RX_THRES_REG           (BPAPB + BPAPB_AB_POFFSET + BPAPB_AB_RX_THRES_REG_POFFSET)

#define BPAPB_AB_GPIO_POFFSET           0x30
#define BPAPB_AB_GPIO                   (BPAPB + BPAPB_AB_POFFSET + BPAPB_AB_GPIO_POFFSET)
#define BPAPB_AB_GPIO_WP                0x1
#define BPAPB_AB_GPIO_WP_GET(_v)        (_v & 0x1)

#define BPAPB_AB_LPBK_DLY_ADJ_POFFSET   0x38
#define BPAPB_AB_LPBK_DLY_ADJ           (BPAPB + BPAPB_AB_POFFSET + BPAPB_AB_LPBK_DLY_ADJ_POFFSET)

#define BPAPB_AB_TXD1_POFFSET           0x80
#define BPAPB_AB_TXD1                   (BPAPB + BPAPB_AB_POFFSET + BPAPB_AB_TXD1_POFFSET)

#define BPAPB_AB_TXD2_POFFSET           0x84
#define BPAPB_AB_TXD2                   (BPAPB + BPAPB_AB_POFFSET + BPAPB_AB_TXD2_POFFSET)

#define BPAPB_AB_TXD3_POFFSET           0x88
#define BPAPB_AB_TXD3                   (BPAPB + BPAPB_AB_POFFSET + BPAPB_AB_TXD3_POFFSET)

#define BPAPB_AB_LQSPI_CFG_POFFSET      0xa0
#define BPAPB_AB_LQSPI_CFG              (BPAPB + BPAPB_AB_POFFSET + BPAPB_AB_LQSPI_CFG_POFFSET)
#define BPAPB_AB_LQSPI_CFG_LQ_MODE      (0x1 << 31)
#define BPAPB_AB_LQSPI_CFG_LQ_MODE_GET(_v)  ((_v >> 31) & 0x1)
#define BPAPB_AB_LQSPI_CFG_TWO_MEM      (0x1 << 30)
#define BPAPB_AB_LQSPI_CFG_TWO_MEM_GET(_v)  ((_v >> 30) & 0x1)
#define BPAPB_AB_LQSPI_CFG_SEP_BUS      (0x1 << 29)
#define BPAPB_AB_LQSPI_CFG_SEP_BUS_GET(_v)  ((_v >> 29) & 0x1)
#define BPAPB_AB_LQSPI_CFG_U_PAGE       (0x1 << 28)
#define BPAPB_AB_LQSPI_CFG_U_PAGE_GET(_v)  ((_v >> 28) & 0x1)
#define BPAPB_AB_LQSPI_CFG_MODE_EN      (0x1 << 25)
#define BPAPB_AB_LQSPI_CFG_MODE_EN_GET(_v)  ((_v >> 25) & 0x1)
#define BPAPB_AB_LQSPI_CFG_MODE_ON      (0x1 << 24)
#define BPAPB_AB_LQSPI_CFG_MODE_ON_GET(_v)  ((_v >> 24) & 0x1)
#define BPAPB_AB_LQSPI_CFG_MODE_BITS    (0xff << 16)
#define BPAPB_AB_LQSPI_CFG_MODE_BITS_GET(_v)  ((_v >> 16) & 0xff)
#define BPAPB_AB_LQSPI_CFG_DUMMY        (0x7 << 8)
#define BPAPB_AB_LQSPI_CFG_DUMMY_GET(_v)  ((_v >> 8) & 0x7)
#define BPAPB_AB_LQSPI_CFG_INST         0xff
#define BPAPB_AB_LQSPI_CFG_INST_GET(_v)  (_v & 0xff)

#define BPAPB_AB_LQSPI_STS_POFFSET      0xa4
#define BPAPB_AB_LQSPI_STS              (BPAPB + BPAPB_AB_POFFSET + BPAPB_AB_LQSPI_STS_POFFSET)
#define BPAPB_AB_LQSPI_STS_D_FSM_ERR    (0x1 << 2)
#define BPAPB_AB_LQSPI_STS_D_FSM_ERR_GET(_v)  ((_v >> 2) & 0x1)
#define BPAPB_AB_LQSPI_STS_WR_RECVD     (0x1 << 1)
#define BPAPB_AB_LQSPI_STS_WR_RECVD_GET(_v)  ((_v >> 1) & 0x1)

#define BPAPB_AB_MOD_ID_POFFSET         0xfc
#define BPAPB_AB_MOD_ID                 (BPAPB + BPAPB_AB_POFFSET + BPAPB_AB_MOD_ID_POFFSET)

#define BPAPB_AB_BUFFER_POFFSET         0x0
#define BPAPB_AB_BUFFER                 (BPAPB + BPAPB_AB_POFFSET + BPAPB_AB_BUFFER_POFFSET)
#define BPAPB_AB_BUFFER_BYTES           0x1000


#endif

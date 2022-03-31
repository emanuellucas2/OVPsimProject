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
#define BPORT1_AB_CONTROL_POFFSET       0x0
#define BPORT1_AB_CONTROL               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CONTROL_POFFSET)
#define BPORT1_AB_CONTROL_STPBRK        (0x1 << 8)
#define BPORT1_AB_CONTROL_STPBRK_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_CONTROL_STTBRK        (0x1 << 7)
#define BPORT1_AB_CONTROL_STTBRK_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_CONTROL_RSTT0         (0x1 << 6)
#define BPORT1_AB_CONTROL_RSTT0_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_CONTROL_TXDIS         (0x1 << 5)
#define BPORT1_AB_CONTROL_TXDIS_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_CONTROL_TXEN          (0x1 << 4)
#define BPORT1_AB_CONTROL_TXEN_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_CONTROL_RXDIS         (0x1 << 3)
#define BPORT1_AB_CONTROL_RXDIS_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_CONTROL_RXEN          (0x1 << 2)
#define BPORT1_AB_CONTROL_RXEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_CONTROL_TXRES         (0x1 << 1)
#define BPORT1_AB_CONTROL_TXRES_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_CONTROL_RXRES         0x1
#define BPORT1_AB_CONTROL_RXRES_GET(_v)  (_v & 0x1)

#define BPORT1_AB_MODE_POFFSET          0x4
#define BPORT1_AB_MODE                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MODE_POFFSET)
#define BPORT1_AB_MODE_CHMODE           (0x3 << 8)
#define BPORT1_AB_MODE_CHMODE_GET(_v)   ((_v >> 8) & 0x3)
#define BPORT1_AB_MODE_NBSTOP           (0x3 << 6)
#define BPORT1_AB_MODE_NBSTOP_GET(_v)   ((_v >> 6) & 0x3)
#define BPORT1_AB_MODE_PAR              (0x7 << 3)
#define BPORT1_AB_MODE_PAR_GET(_v)      ((_v >> 3) & 0x7)
#define BPORT1_AB_MODE_CHRL             (0x3 << 1)
#define BPORT1_AB_MODE_CHRL_GET(_v)     ((_v >> 1) & 0x3)
#define BPORT1_AB_MODE_CLKS             0x1
#define BPORT1_AB_MODE_CLKS_GET(_v)     (_v & 0x1)

#define BPORT1_AB_INTRPT_EN_POFFSET     0x8
#define BPORT1_AB_INTRPT_EN             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INTRPT_EN_POFFSET)
#define BPORT1_AB_INTRPT_EN_TOVR        (0x1 << 12)
#define BPORT1_AB_INTRPT_EN_TOVR_GET(_v)  ((_v >> 12) & 0x1)
#define BPORT1_AB_INTRPT_EN_TNFUL       (0x1 << 11)
#define BPORT1_AB_INTRPT_EN_TNFUL_GET(_v)  ((_v >> 11) & 0x1)
#define BPORT1_AB_INTRPT_EN_TTRIG       (0x1 << 10)
#define BPORT1_AB_INTRPT_EN_TTRIG_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_INTRPT_EN_DMSI        (0x1 << 9)
#define BPORT1_AB_INTRPT_EN_DMSI_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_INTRPT_EN_TIMEOUT     (0x1 << 8)
#define BPORT1_AB_INTRPT_EN_TIMEOUT_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_INTRPT_EN_PARE        (0x1 << 7)
#define BPORT1_AB_INTRPT_EN_PARE_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_INTRPT_EN_FRAME       (0x1 << 6)
#define BPORT1_AB_INTRPT_EN_FRAME_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_INTRPT_EN_ROVR        (0x1 << 5)
#define BPORT1_AB_INTRPT_EN_ROVR_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_INTRPT_EN_TFUL        (0x1 << 4)
#define BPORT1_AB_INTRPT_EN_TFUL_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_INTRPT_EN_TEMPTY      (0x1 << 3)
#define BPORT1_AB_INTRPT_EN_TEMPTY_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_INTRPT_EN_RFUL        (0x1 << 2)
#define BPORT1_AB_INTRPT_EN_RFUL_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_INTRPT_EN_REMPTY      (0x1 << 1)
#define BPORT1_AB_INTRPT_EN_REMPTY_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_INTRPT_EN_RTRIG       0x1
#define BPORT1_AB_INTRPT_EN_RTRIG_GET(_v)  (_v & 0x1)

#define BPORT1_AB_INTRPT_DIS_POFFSET    0xc
#define BPORT1_AB_INTRPT_DIS            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INTRPT_DIS_POFFSET)
#define BPORT1_AB_INTRPT_DIS_TOVR       (0x1 << 12)
#define BPORT1_AB_INTRPT_DIS_TOVR_GET(_v)  ((_v >> 12) & 0x1)
#define BPORT1_AB_INTRPT_DIS_TNFUL      (0x1 << 11)
#define BPORT1_AB_INTRPT_DIS_TNFUL_GET(_v)  ((_v >> 11) & 0x1)
#define BPORT1_AB_INTRPT_DIS_TTRIG      (0x1 << 10)
#define BPORT1_AB_INTRPT_DIS_TTRIG_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_INTRPT_DIS_DMSI       (0x1 << 9)
#define BPORT1_AB_INTRPT_DIS_DMSI_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_INTRPT_DIS_TIMEOUT    (0x1 << 8)
#define BPORT1_AB_INTRPT_DIS_TIMEOUT_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_INTRPT_DIS_PARE       (0x1 << 7)
#define BPORT1_AB_INTRPT_DIS_PARE_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_INTRPT_DIS_FRAME      (0x1 << 6)
#define BPORT1_AB_INTRPT_DIS_FRAME_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_INTRPT_DIS_ROVR       (0x1 << 5)
#define BPORT1_AB_INTRPT_DIS_ROVR_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_INTRPT_DIS_TFUL       (0x1 << 4)
#define BPORT1_AB_INTRPT_DIS_TFUL_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_INTRPT_DIS_TEMPTY     (0x1 << 3)
#define BPORT1_AB_INTRPT_DIS_TEMPTY_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_INTRPT_DIS_RFUL       (0x1 << 2)
#define BPORT1_AB_INTRPT_DIS_RFUL_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_INTRPT_DIS_REMPTY     (0x1 << 1)
#define BPORT1_AB_INTRPT_DIS_REMPTY_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_INTRPT_DIS_RTRIG      0x1
#define BPORT1_AB_INTRPT_DIS_RTRIG_GET(_v)  (_v & 0x1)

#define BPORT1_AB_INTRPT_MASK_POFFSET   0x10
#define BPORT1_AB_INTRPT_MASK           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INTRPT_MASK_POFFSET)
#define BPORT1_AB_INTRPT_MASK_TOVR      (0x1 << 12)
#define BPORT1_AB_INTRPT_MASK_TOVR_GET(_v)  ((_v >> 12) & 0x1)
#define BPORT1_AB_INTRPT_MASK_TNFUL     (0x1 << 11)
#define BPORT1_AB_INTRPT_MASK_TNFUL_GET(_v)  ((_v >> 11) & 0x1)
#define BPORT1_AB_INTRPT_MASK_TTRIG     (0x1 << 10)
#define BPORT1_AB_INTRPT_MASK_TTRIG_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_INTRPT_MASK_DMSI      (0x1 << 9)
#define BPORT1_AB_INTRPT_MASK_DMSI_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_INTRPT_MASK_TIMEOUT   (0x1 << 8)
#define BPORT1_AB_INTRPT_MASK_TIMEOUT_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_INTRPT_MASK_PARE      (0x1 << 7)
#define BPORT1_AB_INTRPT_MASK_PARE_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_INTRPT_MASK_FRAME     (0x1 << 6)
#define BPORT1_AB_INTRPT_MASK_FRAME_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_INTRPT_MASK_ROVR      (0x1 << 5)
#define BPORT1_AB_INTRPT_MASK_ROVR_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_INTRPT_MASK_TFUL      (0x1 << 4)
#define BPORT1_AB_INTRPT_MASK_TFUL_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_INTRPT_MASK_TEMPTY    (0x1 << 3)
#define BPORT1_AB_INTRPT_MASK_TEMPTY_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_INTRPT_MASK_RFUL      (0x1 << 2)
#define BPORT1_AB_INTRPT_MASK_RFUL_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_INTRPT_MASK_REMPTY    (0x1 << 1)
#define BPORT1_AB_INTRPT_MASK_REMPTY_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_INTRPT_MASK_RTRIG     0x1
#define BPORT1_AB_INTRPT_MASK_RTRIG_GET(_v)  (_v & 0x1)

#define BPORT1_AB_CHNL_INT_STS_POFFSET  0x14
#define BPORT1_AB_CHNL_INT_STS          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CHNL_INT_STS_POFFSET)
#define BPORT1_AB_CHNL_INT_STS_TOVR     (0x1 << 12)
#define BPORT1_AB_CHNL_INT_STS_TOVR_GET(_v)  ((_v >> 12) & 0x1)
#define BPORT1_AB_CHNL_INT_STS_TNFUL    (0x1 << 11)
#define BPORT1_AB_CHNL_INT_STS_TNFUL_GET(_v)  ((_v >> 11) & 0x1)
#define BPORT1_AB_CHNL_INT_STS_TTRIG    (0x1 << 10)
#define BPORT1_AB_CHNL_INT_STS_TTRIG_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_CHNL_INT_STS_DMSI     (0x1 << 9)
#define BPORT1_AB_CHNL_INT_STS_DMSI_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_CHNL_INT_STS_TIMEOUT  (0x1 << 8)
#define BPORT1_AB_CHNL_INT_STS_TIMEOUT_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_CHNL_INT_STS_PARE     (0x1 << 7)
#define BPORT1_AB_CHNL_INT_STS_PARE_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_CHNL_INT_STS_FRAME    (0x1 << 6)
#define BPORT1_AB_CHNL_INT_STS_FRAME_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_CHNL_INT_STS_ROVR     (0x1 << 5)
#define BPORT1_AB_CHNL_INT_STS_ROVR_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_CHNL_INT_STS_TFUL     (0x1 << 4)
#define BPORT1_AB_CHNL_INT_STS_TFUL_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_CHNL_INT_STS_TEMPTY   (0x1 << 3)
#define BPORT1_AB_CHNL_INT_STS_TEMPTY_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_CHNL_INT_STS_RFUL     (0x1 << 2)
#define BPORT1_AB_CHNL_INT_STS_RFUL_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_CHNL_INT_STS_REMPTY   (0x1 << 1)
#define BPORT1_AB_CHNL_INT_STS_REMPTY_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_CHNL_INT_STS_RTRIG    0x1
#define BPORT1_AB_CHNL_INT_STS_RTRIG_GET(_v)  (_v & 0x1)

#define BPORT1_AB_BAUD_RATE_GEN_POFFSET  0x18
#define BPORT1_AB_BAUD_RATE_GEN         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BAUD_RATE_GEN_POFFSET)
#define BPORT1_AB_BAUD_RATE_GEN_CD      0xffff
#define BPORT1_AB_BAUD_RATE_GEN_CD_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_RCVR_TIMEOUT_POFFSET  0x1c
#define BPORT1_AB_RCVR_TIMEOUT          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RCVR_TIMEOUT_POFFSET)
#define BPORT1_AB_RCVR_TIMEOUT_RTO      0xff
#define BPORT1_AB_RCVR_TIMEOUT_RTO_GET(_v)  (_v & 0xff)

#define BPORT1_AB_RCVR_FIFO_TRIGGER_LEVEL_POFFSET  0x20
#define BPORT1_AB_RCVR_FIFO_TRIGGER_LEVEL  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RCVR_FIFO_TRIGGER_LEVEL_POFFSET)
#define BPORT1_AB_RCVR_FIFO_TRIGGER_LEVEL_RTRIG  0x3f
#define BPORT1_AB_RCVR_FIFO_TRIGGER_LEVEL_RTRIG_GET(_v)  (_v & 0x3f)

#define BPORT1_AB_MODEM_CTRL_POFFSET    0x24
#define BPORT1_AB_MODEM_CTRL            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MODEM_CTRL_POFFSET)
#define BPORT1_AB_MODEM_CTRL_FCM        (0x1 << 5)
#define BPORT1_AB_MODEM_CTRL_FCM_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_MODEM_CTRL_RTS        (0x1 << 1)
#define BPORT1_AB_MODEM_CTRL_RTS_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_MODEM_CTRL_DTR        0x1
#define BPORT1_AB_MODEM_CTRL_DTR_GET(_v)  (_v & 0x1)

#define BPORT1_AB_MODEM_STS_POFFSET     0x28
#define BPORT1_AB_MODEM_STS             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MODEM_STS_POFFSET)
#define BPORT1_AB_MODEM_STS_FCMS        (0x1 << 8)
#define BPORT1_AB_MODEM_STS_FCMS_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_MODEM_STS_DCD         (0x1 << 7)
#define BPORT1_AB_MODEM_STS_DCD_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_MODEM_STS_RI          (0x1 << 6)
#define BPORT1_AB_MODEM_STS_RI_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_MODEM_STS_DSR         (0x1 << 5)
#define BPORT1_AB_MODEM_STS_DSR_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_MODEM_STS_CTS         (0x1 << 4)
#define BPORT1_AB_MODEM_STS_CTS_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_MODEM_STS_DDCD        (0x1 << 3)
#define BPORT1_AB_MODEM_STS_DDCD_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_MODEM_STS_TERI        (0x1 << 2)
#define BPORT1_AB_MODEM_STS_TERI_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_MODEM_STS_DDSR        (0x1 << 1)
#define BPORT1_AB_MODEM_STS_DDSR_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_MODEM_STS_DCTS        0x1
#define BPORT1_AB_MODEM_STS_DCTS_GET(_v)  (_v & 0x1)

#define BPORT1_AB_CHANNEL_STS_POFFSET   0x2c
#define BPORT1_AB_CHANNEL_STS           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CHANNEL_STS_POFFSET)
#define BPORT1_AB_CHANNEL_STS_TNFUL     (0x1 << 14)
#define BPORT1_AB_CHANNEL_STS_TNFUL_GET(_v)  ((_v >> 14) & 0x1)
#define BPORT1_AB_CHANNEL_STS_TTRIG     (0x1 << 13)
#define BPORT1_AB_CHANNEL_STS_TTRIG_GET(_v)  ((_v >> 13) & 0x1)
#define BPORT1_AB_CHANNEL_STS_FDELT     (0x1 << 12)
#define BPORT1_AB_CHANNEL_STS_FDELT_GET(_v)  ((_v >> 12) & 0x1)
#define BPORT1_AB_CHANNEL_STS_TACTIVE   (0x1 << 11)
#define BPORT1_AB_CHANNEL_STS_TACTIVE_GET(_v)  ((_v >> 11) & 0x1)
#define BPORT1_AB_CHANNEL_STS_RACTIVE   (0x1 << 10)
#define BPORT1_AB_CHANNEL_STS_RACTIVE_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_CHANNEL_STS_TFUL      (0x1 << 4)
#define BPORT1_AB_CHANNEL_STS_TFUL_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_CHANNEL_STS_TEMPTY    (0x1 << 3)
#define BPORT1_AB_CHANNEL_STS_TEMPTY_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_CHANNEL_STS_RFUL      (0x1 << 2)
#define BPORT1_AB_CHANNEL_STS_RFUL_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_CHANNEL_STS_REMPTY    (0x1 << 1)
#define BPORT1_AB_CHANNEL_STS_REMPTY_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_CHANNEL_STS_RTRIG     0x1
#define BPORT1_AB_CHANNEL_STS_RTRIG_GET(_v)  (_v & 0x1)

#define BPORT1_AB_TX_RX_FIFO_POFFSET    0x30
#define BPORT1_AB_TX_RX_FIFO            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TX_RX_FIFO_POFFSET)
#define BPORT1_AB_TX_RX_FIFO_FIF0       0xff
#define BPORT1_AB_TX_RX_FIFO_FIF0_GET(_v)  (_v & 0xff)

#define BPORT1_AB_BAUD_RATE_DIVIDER_POFFSET  0x34
#define BPORT1_AB_BAUD_RATE_DIVIDER     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BAUD_RATE_DIVIDER_POFFSET)
#define BPORT1_AB_BAUD_RATE_DIVIDER_BDIV  0xff
#define BPORT1_AB_BAUD_RATE_DIVIDER_BDIV_GET(_v)  (_v & 0xff)

#define BPORT1_AB_FLOW_DELAY_POFFSET    0x38
#define BPORT1_AB_FLOW_DELAY            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FLOW_DELAY_POFFSET)
#define BPORT1_AB_FLOW_DELAY_FDEL       0x3f
#define BPORT1_AB_FLOW_DELAY_FDEL_GET(_v)  (_v & 0x3f)

#define BPORT1_AB_TX_FIFO_TRIGGER_LEVEL_POFFSET  0x44
#define BPORT1_AB_TX_FIFO_TRIGGER_LEVEL  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TX_FIFO_TRIGGER_LEVEL_POFFSET)
#define BPORT1_AB_TX_FIFO_TRIGGER_LEVEL_TTRIG  0x3f
#define BPORT1_AB_TX_FIFO_TRIGGER_LEVEL_TTRIG_GET(_v)  (_v & 0x3f)

#define BPORT1_AB_BUFFER_POFFSET        0x0
#define BPORT1_AB_BUFFER                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BUFFER_POFFSET)
#define BPORT1_AB_BUFFER_BYTES          0x1000


#endif

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
#define BPORT1_AB_EIR_POFFSET           0x4
#define BPORT1_AB_EIR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EIR_POFFSET)
#define BPORT1_AB_EIR_BABR              (0x1 << 30)
#define BPORT1_AB_EIR_BABR_GET(_v)      ((_v >> 30) & 0x1)
#define BPORT1_AB_EIR_BABT              (0x1 << 29)
#define BPORT1_AB_EIR_BABT_GET(_v)      ((_v >> 29) & 0x1)
#define BPORT1_AB_EIR_EBERR             (0x1 << 22)
#define BPORT1_AB_EIR_EBERR_GET(_v)     ((_v >> 22) & 0x1)
#define BPORT1_AB_EIR_GRA               (0x1 << 28)
#define BPORT1_AB_EIR_GRA_GET(_v)       ((_v >> 28) & 0x1)
#define BPORT1_AB_EIR_LC                (0x1 << 21)
#define BPORT1_AB_EIR_LC_GET(_v)        ((_v >> 21) & 0x1)
#define BPORT1_AB_EIR_MII               (0x1 << 23)
#define BPORT1_AB_EIR_MII_GET(_v)       ((_v >> 23) & 0x1)
#define BPORT1_AB_EIR_PLR               (0x1 << 18)
#define BPORT1_AB_EIR_PLR_GET(_v)       ((_v >> 18) & 0x1)
#define BPORT1_AB_EIR_RL                (0x1 << 20)
#define BPORT1_AB_EIR_RL_GET(_v)        ((_v >> 20) & 0x1)
#define BPORT1_AB_EIR_RXB               (0x1 << 24)
#define BPORT1_AB_EIR_RXB_GET(_v)       ((_v >> 24) & 0x1)
#define BPORT1_AB_EIR_RXF               (0x1 << 25)
#define BPORT1_AB_EIR_RXF_GET(_v)       ((_v >> 25) & 0x1)
#define BPORT1_AB_EIR_TS_AVAIL          (0x1 << 16)
#define BPORT1_AB_EIR_TS_AVAIL_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_EIR_TS_TIMER          (0x1 << 15)
#define BPORT1_AB_EIR_TS_TIMER_GET(_v)  ((_v >> 15) & 0x1)
#define BPORT1_AB_EIR_TXB               (0x1 << 26)
#define BPORT1_AB_EIR_TXB_GET(_v)       ((_v >> 26) & 0x1)
#define BPORT1_AB_EIR_TXF               (0x1 << 27)
#define BPORT1_AB_EIR_TXF_GET(_v)       ((_v >> 27) & 0x1)
#define BPORT1_AB_EIR_UN                (0x1 << 19)
#define BPORT1_AB_EIR_UN_GET(_v)        ((_v >> 19) & 0x1)
#define BPORT1_AB_EIR_WAKEUP            (0x1 << 17)
#define BPORT1_AB_EIR_WAKEUP_GET(_v)    ((_v >> 17) & 0x1)

#define BPORT1_AB_EIMR_POFFSET          0x8
#define BPORT1_AB_EIMR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EIMR_POFFSET)
#define BPORT1_AB_EIMR_BABR             (0x1 << 30)
#define BPORT1_AB_EIMR_BABR_GET(_v)     ((_v >> 30) & 0x1)
#define BPORT1_AB_EIMR_BABT             (0x1 << 29)
#define BPORT1_AB_EIMR_BABT_GET(_v)     ((_v >> 29) & 0x1)
#define BPORT1_AB_EIMR_EBERR            (0x1 << 22)
#define BPORT1_AB_EIMR_EBERR_GET(_v)    ((_v >> 22) & 0x1)
#define BPORT1_AB_EIMR_GRA              (0x1 << 28)
#define BPORT1_AB_EIMR_GRA_GET(_v)      ((_v >> 28) & 0x1)
#define BPORT1_AB_EIMR_LC               (0x1 << 21)
#define BPORT1_AB_EIMR_LC_GET(_v)       ((_v >> 21) & 0x1)
#define BPORT1_AB_EIMR_MII              (0x1 << 23)
#define BPORT1_AB_EIMR_MII_GET(_v)      ((_v >> 23) & 0x1)
#define BPORT1_AB_EIMR_PLR              (0x1 << 18)
#define BPORT1_AB_EIMR_PLR_GET(_v)      ((_v >> 18) & 0x1)
#define BPORT1_AB_EIMR_RL               (0x1 << 20)
#define BPORT1_AB_EIMR_RL_GET(_v)       ((_v >> 20) & 0x1)
#define BPORT1_AB_EIMR_RXB              (0x1 << 24)
#define BPORT1_AB_EIMR_RXB_GET(_v)      ((_v >> 24) & 0x1)
#define BPORT1_AB_EIMR_RXF              (0x1 << 25)
#define BPORT1_AB_EIMR_RXF_GET(_v)      ((_v >> 25) & 0x1)
#define BPORT1_AB_EIMR_TS_AVAIL         (0x1 << 16)
#define BPORT1_AB_EIMR_TS_AVAIL_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_EIMR_TS_TIMER         (0x1 << 15)
#define BPORT1_AB_EIMR_TS_TIMER_GET(_v)  ((_v >> 15) & 0x1)
#define BPORT1_AB_EIMR_TXB              (0x1 << 26)
#define BPORT1_AB_EIMR_TXB_GET(_v)      ((_v >> 26) & 0x1)
#define BPORT1_AB_EIMR_TXF              (0x1 << 27)
#define BPORT1_AB_EIMR_TXF_GET(_v)      ((_v >> 27) & 0x1)
#define BPORT1_AB_EIMR_UN               (0x1 << 19)
#define BPORT1_AB_EIMR_UN_GET(_v)       ((_v >> 19) & 0x1)
#define BPORT1_AB_EIMR_WAKEUP           (0x1 << 17)
#define BPORT1_AB_EIMR_WAKEUP_GET(_v)   ((_v >> 17) & 0x1)

#define BPORT1_AB_RDAR_POFFSET          0x10
#define BPORT1_AB_RDAR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RDAR_POFFSET)
#define BPORT1_AB_RDAR_RDAR             (0x1 << 24)
#define BPORT1_AB_RDAR_RDAR_GET(_v)     ((_v >> 24) & 0x1)

#define BPORT1_AB_TDAR_POFFSET          0x14
#define BPORT1_AB_TDAR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TDAR_POFFSET)
#define BPORT1_AB_TDAR_TDAR             (0x1 << 24)
#define BPORT1_AB_TDAR_TDAR_GET(_v)     ((_v >> 24) & 0x1)

#define BPORT1_AB_ECR_POFFSET           0x24
#define BPORT1_AB_ECR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ECR_POFFSET)
#define BPORT1_AB_ECR_DBGEN             (0x1 << 6)
#define BPORT1_AB_ECR_DBGEN_GET(_v)     ((_v >> 6) & 0x1)
#define BPORT1_AB_ECR_DBSWP             (0x1 << 8)
#define BPORT1_AB_ECR_DBSWP_GET(_v)     ((_v >> 8) & 0x1)
#define BPORT1_AB_ECR_EN1588            (0x1 << 4)
#define BPORT1_AB_ECR_EN1588_GET(_v)    ((_v >> 4) & 0x1)
#define BPORT1_AB_ECR_ETHEREN           (0x1 << 1)
#define BPORT1_AB_ECR_ETHEREN_GET(_v)   ((_v >> 1) & 0x1)
#define BPORT1_AB_ECR_MAGICEN           (0x1 << 2)
#define BPORT1_AB_ECR_MAGICEN_GET(_v)   ((_v >> 2) & 0x1)
#define BPORT1_AB_ECR_RESET             0x1
#define BPORT1_AB_ECR_RESET_GET(_v)     (_v & 0x1)
#define BPORT1_AB_ECR_SLEEP             (0x1 << 3)
#define BPORT1_AB_ECR_SLEEP_GET(_v)     ((_v >> 3) & 0x1)
#define BPORT1_AB_ECR_STOPEN            (0x1 << 7)
#define BPORT1_AB_ECR_STOPEN_GET(_v)    ((_v >> 7) & 0x1)

#define BPORT1_AB_MMFR_POFFSET          0x40
#define BPORT1_AB_MMFR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MMFR_POFFSET)
#define BPORT1_AB_MMFR_DATA             0xffff
#define BPORT1_AB_MMFR_DATA_GET(_v)     (_v & 0xffff)
#define BPORT1_AB_MMFR_OP               (0x3 << 28)
#define BPORT1_AB_MMFR_OP_GET(_v)       ((_v >> 28) & 0x3)
#define BPORT1_AB_MMFR_PA               (0x1f << 23)
#define BPORT1_AB_MMFR_PA_GET(_v)       ((_v >> 23) & 0x1f)
#define BPORT1_AB_MMFR_RA               (0x1f << 18)
#define BPORT1_AB_MMFR_RA_GET(_v)       ((_v >> 18) & 0x1f)
#define BPORT1_AB_MMFR_ST               (0x3 << 30)
#define BPORT1_AB_MMFR_ST_GET(_v)       ((_v >> 30) & 0x3)
#define BPORT1_AB_MMFR_TA               (0x3 << 16)
#define BPORT1_AB_MMFR_TA_GET(_v)       ((_v >> 16) & 0x3)

#define BPORT1_AB_MSCR_POFFSET          0x44
#define BPORT1_AB_MSCR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MSCR_POFFSET)
#define BPORT1_AB_MSCR_DIS_PRE          (0x1 << 7)
#define BPORT1_AB_MSCR_DIS_PRE_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_MSCR_HOLDTIME         (0x7 << 8)
#define BPORT1_AB_MSCR_HOLDTIME_GET(_v)  ((_v >> 8) & 0x7)
#define BPORT1_AB_MSCR_MII_SPEED        (0x3f << 1)
#define BPORT1_AB_MSCR_MII_SPEED_GET(_v)  ((_v >> 1) & 0x3f)

#define BPORT1_AB_MIBC_POFFSET          0x64
#define BPORT1_AB_MIBC                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIBC_POFFSET)
#define BPORT1_AB_MIBC_MIB_CLEAR        (0x1 << 29)
#define BPORT1_AB_MIBC_MIB_CLEAR_GET(_v)  ((_v >> 29) & 0x1)
#define BPORT1_AB_MIBC_MIB_DIS          (0x1 << 31)
#define BPORT1_AB_MIBC_MIB_DIS_GET(_v)  ((_v >> 31) & 0x1)
#define BPORT1_AB_MIBC_MIB_IDLE         (0x1 << 30)
#define BPORT1_AB_MIBC_MIB_IDLE_GET(_v)  ((_v >> 30) & 0x1)

#define BPORT1_AB_RCR_POFFSET           0x84
#define BPORT1_AB_RCR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RCR_POFFSET)
#define BPORT1_AB_RCR_BC_REJ            (0x1 << 4)
#define BPORT1_AB_RCR_BC_REJ_GET(_v)    ((_v >> 4) & 0x1)
#define BPORT1_AB_RCR_CFEN              (0x1 << 15)
#define BPORT1_AB_RCR_CFEN_GET(_v)      ((_v >> 15) & 0x1)
#define BPORT1_AB_RCR_CRCFWD            (0x1 << 14)
#define BPORT1_AB_RCR_CRCFWD_GET(_v)    ((_v >> 14) & 0x1)
#define BPORT1_AB_RCR_DRT               (0x1 << 1)
#define BPORT1_AB_RCR_DRT_GET(_v)       ((_v >> 1) & 0x1)
#define BPORT1_AB_RCR_FCE               (0x1 << 5)
#define BPORT1_AB_RCR_FCE_GET(_v)       ((_v >> 5) & 0x1)
#define BPORT1_AB_RCR_GRS               (0x1 << 31)
#define BPORT1_AB_RCR_GRS_GET(_v)       ((_v >> 31) & 0x1)
#define BPORT1_AB_RCR_LOOP              0x1
#define BPORT1_AB_RCR_LOOP_GET(_v)      (_v & 0x1)
#define BPORT1_AB_RCR_MAX_FL            (0x3fff << 16)
#define BPORT1_AB_RCR_MAX_FL_GET(_v)    ((_v >> 16) & 0x3fff)
#define BPORT1_AB_RCR_MII_MODE          (0x1 << 2)
#define BPORT1_AB_RCR_MII_MODE_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_RCR_NLC               (0x1 << 30)
#define BPORT1_AB_RCR_NLC_GET(_v)       ((_v >> 30) & 0x1)
#define BPORT1_AB_RCR_PADEN             (0x1 << 12)
#define BPORT1_AB_RCR_PADEN_GET(_v)     ((_v >> 12) & 0x1)
#define BPORT1_AB_RCR_PAUFWD            (0x1 << 13)
#define BPORT1_AB_RCR_PAUFWD_GET(_v)    ((_v >> 13) & 0x1)
#define BPORT1_AB_RCR_PROM              (0x1 << 3)
#define BPORT1_AB_RCR_PROM_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_RCR_RMII_10T          (0x1 << 9)
#define BPORT1_AB_RCR_RMII_10T_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_RCR_RMII_MODE         (0x1 << 8)
#define BPORT1_AB_RCR_RMII_MODE_GET(_v)  ((_v >> 8) & 0x1)

#define BPORT1_AB_TCR_POFFSET           0xc4
#define BPORT1_AB_TCR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCR_POFFSET)
#define BPORT1_AB_TCR_ADDINS            (0x1 << 8)
#define BPORT1_AB_TCR_ADDINS_GET(_v)    ((_v >> 8) & 0x1)
#define BPORT1_AB_TCR_ADDSEL            (0x7 << 5)
#define BPORT1_AB_TCR_ADDSEL_GET(_v)    ((_v >> 5) & 0x7)
#define BPORT1_AB_TCR_CRCFWD            (0x1 << 9)
#define BPORT1_AB_TCR_CRCFWD_GET(_v)    ((_v >> 9) & 0x1)
#define BPORT1_AB_TCR_FDEN              (0x1 << 2)
#define BPORT1_AB_TCR_FDEN_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_TCR_GTS               0x1
#define BPORT1_AB_TCR_GTS_GET(_v)       (_v & 0x1)
#define BPORT1_AB_TCR_RFC_PAUSE         (0x1 << 4)
#define BPORT1_AB_TCR_RFC_PAUSE_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_TCR_TFC_PAUSE         (0x1 << 3)
#define BPORT1_AB_TCR_TFC_PAUSE_GET(_v)  ((_v >> 3) & 0x1)

#define BPORT1_AB_PALR_POFFSET          0xe4
#define BPORT1_AB_PALR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PALR_POFFSET)
#define BPORT1_AB_PALR_PADDR1           0xffffffff
#define BPORT1_AB_PALR_PADDR1_GET(_v)   (_v & 0xffffffff)

#define BPORT1_AB_PAUR_POFFSET          0xe8
#define BPORT1_AB_PAUR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PAUR_POFFSET)
#define BPORT1_AB_PAUR_PADDR2           (0xffff << 16)
#define BPORT1_AB_PAUR_PADDR2_GET(_v)   ((_v >> 16) & 0xffff)
#define BPORT1_AB_PAUR_TYPE             0xffff
#define BPORT1_AB_PAUR_TYPE_GET(_v)     (_v & 0xffff)

#define BPORT1_AB_OPD_POFFSET           0xec
#define BPORT1_AB_OPD                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_OPD_POFFSET)
#define BPORT1_AB_OPD_OPCODE            (0xffff << 16)
#define BPORT1_AB_OPD_OPCODE_GET(_v)    ((_v >> 16) & 0xffff)
#define BPORT1_AB_OPD_PAUSE_DUR         0xffff
#define BPORT1_AB_OPD_PAUSE_DUR_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_IAUR_POFFSET          0x118
#define BPORT1_AB_IAUR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IAUR_POFFSET)
#define BPORT1_AB_IAUR_IADDR1           0xffffffff
#define BPORT1_AB_IAUR_IADDR1_GET(_v)   (_v & 0xffffffff)

#define BPORT1_AB_IALR_POFFSET          0x11c
#define BPORT1_AB_IALR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IALR_POFFSET)
#define BPORT1_AB_IALR_IADDR2           0xffffffff
#define BPORT1_AB_IALR_IADDR2_GET(_v)   (_v & 0xffffffff)

#define BPORT1_AB_GAUR_POFFSET          0x120
#define BPORT1_AB_GAUR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GAUR_POFFSET)
#define BPORT1_AB_GAUR_GADDR1           0xffffffff
#define BPORT1_AB_GAUR_GADDR1_GET(_v)   (_v & 0xffffffff)

#define BPORT1_AB_GALR_POFFSET          0x124
#define BPORT1_AB_GALR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GALR_POFFSET)
#define BPORT1_AB_GALR_GADDR2           0xffffffff
#define BPORT1_AB_GALR_GADDR2_GET(_v)   (_v & 0xffffffff)

#define BPORT1_AB_TFWR_POFFSET          0x144
#define BPORT1_AB_TFWR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TFWR_POFFSET)
#define BPORT1_AB_TFWR_STRFWD           (0x1 << 8)
#define BPORT1_AB_TFWR_STRFWD_GET(_v)   ((_v >> 8) & 0x1)
#define BPORT1_AB_TFWR_TFWR             0x3f
#define BPORT1_AB_TFWR_TFWR_GET(_v)     (_v & 0x3f)

#define BPORT1_AB_RDSR_POFFSET          0x180
#define BPORT1_AB_RDSR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RDSR_POFFSET)
#define BPORT1_AB_RDSR_R_DES_START      (0x1fffffff << 3)
#define BPORT1_AB_RDSR_R_DES_START_GET(_v)  ((_v >> 3) & 0x1fffffff)

#define BPORT1_AB_TDSR_POFFSET          0x184
#define BPORT1_AB_TDSR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TDSR_POFFSET)
#define BPORT1_AB_TDSR_X_DES_START      (0x1fffffff << 3)
#define BPORT1_AB_TDSR_X_DES_START_GET(_v)  ((_v >> 3) & 0x1fffffff)

#define BPORT1_AB_MRBR_POFFSET          0x188
#define BPORT1_AB_MRBR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MRBR_POFFSET)
#define BPORT1_AB_MRBR_R_BUF_SIZE       (0x3ff << 4)
#define BPORT1_AB_MRBR_R_BUF_SIZE_GET(_v)  ((_v >> 4) & 0x3ff)

#define BPORT1_AB_RSFL_POFFSET          0x190
#define BPORT1_AB_RSFL                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RSFL_POFFSET)
#define BPORT1_AB_RSFL_RX_SECTION_FULL  0xff
#define BPORT1_AB_RSFL_RX_SECTION_FULL_GET(_v)  (_v & 0xff)

#define BPORT1_AB_RSEM_POFFSET          0x194
#define BPORT1_AB_RSEM                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RSEM_POFFSET)
#define BPORT1_AB_RSEM_RX_SECTION_EMPTY  0xff
#define BPORT1_AB_RSEM_RX_SECTION_EMPTY_GET(_v)  (_v & 0xff)

#define BPORT1_AB_RAEM_POFFSET          0x198
#define BPORT1_AB_RAEM                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RAEM_POFFSET)
#define BPORT1_AB_RAEM_RX_ALMOST_EMPTY  0xff
#define BPORT1_AB_RAEM_RX_ALMOST_EMPTY_GET(_v)  (_v & 0xff)

#define BPORT1_AB_RAFL_POFFSET          0x19c
#define BPORT1_AB_RAFL                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RAFL_POFFSET)
#define BPORT1_AB_RAFL_RX_ALMOST_FULL   0xff
#define BPORT1_AB_RAFL_RX_ALMOST_FULL_GET(_v)  (_v & 0xff)

#define BPORT1_AB_TSEM_POFFSET          0x1a0
#define BPORT1_AB_TSEM                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TSEM_POFFSET)
#define BPORT1_AB_TSEM_TX_SECTION_EMPTY  0xff
#define BPORT1_AB_TSEM_TX_SECTION_EMPTY_GET(_v)  (_v & 0xff)

#define BPORT1_AB_TAEM_POFFSET          0x1a4
#define BPORT1_AB_TAEM                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TAEM_POFFSET)
#define BPORT1_AB_TAEM_TX_ALMOST_EMPTY  0xff
#define BPORT1_AB_TAEM_TX_ALMOST_EMPTY_GET(_v)  (_v & 0xff)

#define BPORT1_AB_TAFL_POFFSET          0x1a8
#define BPORT1_AB_TAFL                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TAFL_POFFSET)
#define BPORT1_AB_TAFL_TX_ALMOST_FULL   0xff
#define BPORT1_AB_TAFL_TX_ALMOST_FULL_GET(_v)  (_v & 0xff)

#define BPORT1_AB_TIPG_POFFSET          0x1ac
#define BPORT1_AB_TIPG                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TIPG_POFFSET)
#define BPORT1_AB_TIPG_IPG              0x1f
#define BPORT1_AB_TIPG_IPG_GET(_v)      (_v & 0x1f)

#define BPORT1_AB_FTRL_POFFSET          0x1b0
#define BPORT1_AB_FTRL                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FTRL_POFFSET)
#define BPORT1_AB_FTRL_TRUNC_FL         0x3fff
#define BPORT1_AB_FTRL_TRUNC_FL_GET(_v)  (_v & 0x3fff)

#define BPORT1_AB_TACC_POFFSET          0x1c0
#define BPORT1_AB_TACC                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TACC_POFFSET)
#define BPORT1_AB_TACC_IPCHK            (0x1 << 3)
#define BPORT1_AB_TACC_IPCHK_GET(_v)    ((_v >> 3) & 0x1)
#define BPORT1_AB_TACC_PROCHK           (0x1 << 4)
#define BPORT1_AB_TACC_PROCHK_GET(_v)   ((_v >> 4) & 0x1)
#define BPORT1_AB_TACC_SHIFT16          0x1
#define BPORT1_AB_TACC_SHIFT16_GET(_v)  (_v & 0x1)

#define BPORT1_AB_RACC_POFFSET          0x1c4
#define BPORT1_AB_RACC                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RACC_POFFSET)
#define BPORT1_AB_RACC_IPDIS            (0x1 << 1)
#define BPORT1_AB_RACC_IPDIS_GET(_v)    ((_v >> 1) & 0x1)
#define BPORT1_AB_RACC_LINEDIS          (0x1 << 6)
#define BPORT1_AB_RACC_LINEDIS_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_RACC_PADREM           0x1
#define BPORT1_AB_RACC_PADREM_GET(_v)   (_v & 0x1)
#define BPORT1_AB_RACC_PRODIS           (0x1 << 2)
#define BPORT1_AB_RACC_PRODIS_GET(_v)   ((_v >> 2) & 0x1)
#define BPORT1_AB_RACC_SHIFT16          (0x1 << 7)
#define BPORT1_AB_RACC_SHIFT16_GET(_v)  ((_v >> 7) & 0x1)

#define BPORT1_AB_RMON_T_DROP_POFFSET   0x200
#define BPORT1_AB_RMON_T_DROP           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_T_DROP_POFFSET)

#define BPORT1_AB_RMON_T_PACKETS_POFFSET  0x204
#define BPORT1_AB_RMON_T_PACKETS        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_T_PACKETS_POFFSET)

#define BPORT1_AB_RMON_T_BC_PKT_POFFSET  0x208
#define BPORT1_AB_RMON_T_BC_PKT         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_T_BC_PKT_POFFSET)

#define BPORT1_AB_RMON_T_MC_PKT_POFFSET  0x20c
#define BPORT1_AB_RMON_T_MC_PKT         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_T_MC_PKT_POFFSET)

#define BPORT1_AB_RMON_T_CRC_ALIGN_POFFSET  0x210
#define BPORT1_AB_RMON_T_CRC_ALIGN      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_T_CRC_ALIGN_POFFSET)

#define BPORT1_AB_RMON_T_UNDERSIZE_POFFSET  0x214
#define BPORT1_AB_RMON_T_UNDERSIZE      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_T_UNDERSIZE_POFFSET)

#define BPORT1_AB_RMON_T_OVERSIZE_POFFSET  0x218
#define BPORT1_AB_RMON_T_OVERSIZE       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_T_OVERSIZE_POFFSET)

#define BPORT1_AB_RMON_T_FRAG_POFFSET   0x21c
#define BPORT1_AB_RMON_T_FRAG           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_T_FRAG_POFFSET)

#define BPORT1_AB_RMON_T_JAB_POFFSET    0x220
#define BPORT1_AB_RMON_T_JAB            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_T_JAB_POFFSET)

#define BPORT1_AB_RMON_T_COL_POFFSET    0x224
#define BPORT1_AB_RMON_T_COL            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_T_COL_POFFSET)

#define BPORT1_AB_RMON_T_P64_POFFSET    0x228
#define BPORT1_AB_RMON_T_P64            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_T_P64_POFFSET)

#define BPORT1_AB_RMON_T_P65TO127_POFFSET  0x22c
#define BPORT1_AB_RMON_T_P65TO127       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_T_P65TO127_POFFSET)

#define BPORT1_AB_RMON_T_P128TO255_POFFSET  0x230
#define BPORT1_AB_RMON_T_P128TO255      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_T_P128TO255_POFFSET)

#define BPORT1_AB_RMON_T_P256TO511_POFFSET  0x234
#define BPORT1_AB_RMON_T_P256TO511      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_T_P256TO511_POFFSET)

#define BPORT1_AB_RMON_T_P512TO1023_POFFSET  0x238
#define BPORT1_AB_RMON_T_P512TO1023     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_T_P512TO1023_POFFSET)

#define BPORT1_AB_RMON_T_P1024TO2047_POFFSET  0x23c
#define BPORT1_AB_RMON_T_P1024TO2047    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_T_P1024TO2047_POFFSET)

#define BPORT1_AB_RMON_T_P_GTE2048_POFFSET  0x240
#define BPORT1_AB_RMON_T_P_GTE2048      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_T_P_GTE2048_POFFSET)

#define BPORT1_AB_RMON_T_OCTETS_POFFSET  0x244
#define BPORT1_AB_RMON_T_OCTETS         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_T_OCTETS_POFFSET)

#define BPORT1_AB_IEEE_T_DROP_POFFSET   0x248
#define BPORT1_AB_IEEE_T_DROP           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IEEE_T_DROP_POFFSET)

#define BPORT1_AB_IEEE_T_FRAME_OK_POFFSET  0x24c
#define BPORT1_AB_IEEE_T_FRAME_OK       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IEEE_T_FRAME_OK_POFFSET)

#define BPORT1_AB_IEEE_T_1COL_POFFSET   0x250
#define BPORT1_AB_IEEE_T_1COL           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IEEE_T_1COL_POFFSET)

#define BPORT1_AB_IEEE_T_MCOL_POFFSET   0x254
#define BPORT1_AB_IEEE_T_MCOL           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IEEE_T_MCOL_POFFSET)

#define BPORT1_AB_IEEE_T_DEF_POFFSET    0x258
#define BPORT1_AB_IEEE_T_DEF            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IEEE_T_DEF_POFFSET)

#define BPORT1_AB_IEEE_T_LCOL_POFFSET   0x25c
#define BPORT1_AB_IEEE_T_LCOL           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IEEE_T_LCOL_POFFSET)

#define BPORT1_AB_IEEE_T_EXCOL_POFFSET  0x260
#define BPORT1_AB_IEEE_T_EXCOL          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IEEE_T_EXCOL_POFFSET)

#define BPORT1_AB_IEEE_T_MACERR_POFFSET  0x264
#define BPORT1_AB_IEEE_T_MACERR         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IEEE_T_MACERR_POFFSET)

#define BPORT1_AB_IEEE_T_CSERR_POFFSET  0x268
#define BPORT1_AB_IEEE_T_CSERR          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IEEE_T_CSERR_POFFSET)

#define BPORT1_AB_IEEE_T_SQE_POFFSET    0x26c
#define BPORT1_AB_IEEE_T_SQE            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IEEE_T_SQE_POFFSET)

#define BPORT1_AB_IEEE_T_FDXFC_POFFSET  0x270
#define BPORT1_AB_IEEE_T_FDXFC          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IEEE_T_FDXFC_POFFSET)

#define BPORT1_AB_IEEE_T_OCTETS_OK_POFFSET  0x274
#define BPORT1_AB_IEEE_T_OCTETS_OK      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IEEE_T_OCTETS_OK_POFFSET)

#define BPORT1_AB_RMON_R_PACKETS_POFFSET  0x284
#define BPORT1_AB_RMON_R_PACKETS        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_R_PACKETS_POFFSET)

#define BPORT1_AB_RMON_R_BC_PKT_POFFSET  0x288
#define BPORT1_AB_RMON_R_BC_PKT         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_R_BC_PKT_POFFSET)

#define BPORT1_AB_RMON_R_MC_PKT_POFFSET  0x28c
#define BPORT1_AB_RMON_R_MC_PKT         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_R_MC_PKT_POFFSET)

#define BPORT1_AB_RMON_R_CRC_ALIGN_POFFSET  0x290
#define BPORT1_AB_RMON_R_CRC_ALIGN      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_R_CRC_ALIGN_POFFSET)

#define BPORT1_AB_RMON_R_UNDERSIZE_POFFSET  0x294
#define BPORT1_AB_RMON_R_UNDERSIZE      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_R_UNDERSIZE_POFFSET)

#define BPORT1_AB_RMON_R_OVERSIZE_POFFSET  0x298
#define BPORT1_AB_RMON_R_OVERSIZE       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_R_OVERSIZE_POFFSET)

#define BPORT1_AB_RMON_R_FRAG_POFFSET   0x29c
#define BPORT1_AB_RMON_R_FRAG           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_R_FRAG_POFFSET)

#define BPORT1_AB_RMON_R_JAB_POFFSET    0x2a0
#define BPORT1_AB_RMON_R_JAB            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_R_JAB_POFFSET)

#define BPORT1_AB_RMON_R_RESVD_0_POFFSET  0x2a4
#define BPORT1_AB_RMON_R_RESVD_0        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_R_RESVD_0_POFFSET)

#define BPORT1_AB_RMON_R_P64_POFFSET    0x2a8
#define BPORT1_AB_RMON_R_P64            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_R_P64_POFFSET)

#define BPORT1_AB_RMON_R_P65TO127_POFFSET  0x2ac
#define BPORT1_AB_RMON_R_P65TO127       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_R_P65TO127_POFFSET)

#define BPORT1_AB_RMON_R_P128TO255_POFFSET  0x2b0
#define BPORT1_AB_RMON_R_P128TO255      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_R_P128TO255_POFFSET)

#define BPORT1_AB_RMON_R_P256TO511_POFFSET  0x2b4
#define BPORT1_AB_RMON_R_P256TO511      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_R_P256TO511_POFFSET)

#define BPORT1_AB_RMON_R_P512TO1023_POFFSET  0x2b8
#define BPORT1_AB_RMON_R_P512TO1023     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_R_P512TO1023_POFFSET)

#define BPORT1_AB_RMON_R_P1024TO2047_POFFSET  0x2bc
#define BPORT1_AB_RMON_R_P1024TO2047    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_R_P1024TO2047_POFFSET)

#define BPORT1_AB_RMON_R_P_GTE2048_POFFSET  0x2c0
#define BPORT1_AB_RMON_R_P_GTE2048      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_R_P_GTE2048_POFFSET)

#define BPORT1_AB_RMON_R_OCTETS_POFFSET  0x2c4
#define BPORT1_AB_RMON_R_OCTETS         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_R_OCTETS_POFFSET)

#define BPORT1_AB_RMON_R_DROP_POFFSET   0x2c8
#define BPORT1_AB_RMON_R_DROP           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_R_DROP_POFFSET)

#define BPORT1_AB_RMON_R_FRAME_OK_POFFSET  0x2cc
#define BPORT1_AB_RMON_R_FRAME_OK       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RMON_R_FRAME_OK_POFFSET)

#define BPORT1_AB_IEEE_R_CRC_POFFSET    0x2d0
#define BPORT1_AB_IEEE_R_CRC            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IEEE_R_CRC_POFFSET)

#define BPORT1_AB_IEEE_R_ALIGN_POFFSET  0x2d4
#define BPORT1_AB_IEEE_R_ALIGN          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IEEE_R_ALIGN_POFFSET)

#define BPORT1_AB_IEEE_R_MACERR_POFFSET  0x2d8
#define BPORT1_AB_IEEE_R_MACERR         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IEEE_R_MACERR_POFFSET)

#define BPORT1_AB_IEEE_R_FDXFC_POFFSET  0x2dc
#define BPORT1_AB_IEEE_R_FDXFC          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IEEE_R_FDXFC_POFFSET)

#define BPORT1_AB_IEEE_R_OCTETS_OK_POFFSET  0x2e0
#define BPORT1_AB_IEEE_R_OCTETS_OK      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IEEE_R_OCTETS_OK_POFFSET)

#define BPORT1_AB_ATCR_POFFSET          0x400
#define BPORT1_AB_ATCR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ATCR_POFFSET)
#define BPORT1_AB_ATCR_CAPTURE          (0x1 << 11)
#define BPORT1_AB_ATCR_CAPTURE_GET(_v)  ((_v >> 11) & 0x1)
#define BPORT1_AB_ATCR_EN               0x1
#define BPORT1_AB_ATCR_EN_GET(_v)       (_v & 0x1)
#define BPORT1_AB_ATCR_OFFEN            (0x1 << 2)
#define BPORT1_AB_ATCR_OFFEN_GET(_v)    ((_v >> 2) & 0x1)
#define BPORT1_AB_ATCR_OFFRST           (0x1 << 3)
#define BPORT1_AB_ATCR_OFFRST_GET(_v)   ((_v >> 3) & 0x1)
#define BPORT1_AB_ATCR_PEREN            (0x1 << 4)
#define BPORT1_AB_ATCR_PEREN_GET(_v)    ((_v >> 4) & 0x1)
#define BPORT1_AB_ATCR_PINPER           (0x1 << 7)
#define BPORT1_AB_ATCR_PINPER_GET(_v)   ((_v >> 7) & 0x1)
#define BPORT1_AB_ATCR_RESTART          (0x1 << 9)
#define BPORT1_AB_ATCR_RESTART_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_ATCR_SLAVE            (0x1 << 13)
#define BPORT1_AB_ATCR_SLAVE_GET(_v)    ((_v >> 13) & 0x1)

#define BPORT1_AB_ATVR_POFFSET          0x404
#define BPORT1_AB_ATVR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ATVR_POFFSET)
#define BPORT1_AB_ATVR_ATIME            0xffffffff
#define BPORT1_AB_ATVR_ATIME_GET(_v)    (_v & 0xffffffff)

#define BPORT1_AB_ATOFF_POFFSET         0x408
#define BPORT1_AB_ATOFF                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ATOFF_POFFSET)
#define BPORT1_AB_ATOFF_OFFSET          0xffffffff
#define BPORT1_AB_ATOFF_OFFSET_GET(_v)  (_v & 0xffffffff)

#define BPORT1_AB_ATPER_POFFSET         0x40c
#define BPORT1_AB_ATPER                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ATPER_POFFSET)
#define BPORT1_AB_ATPER_PERIOD          0xffffffff
#define BPORT1_AB_ATPER_PERIOD_GET(_v)  (_v & 0xffffffff)

#define BPORT1_AB_ATCOR_POFFSET         0x410
#define BPORT1_AB_ATCOR                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ATCOR_POFFSET)
#define BPORT1_AB_ATCOR_COR             0x7fffffff
#define BPORT1_AB_ATCOR_COR_GET(_v)     (_v & 0x7fffffff)

#define BPORT1_AB_ATINC_POFFSET         0x414
#define BPORT1_AB_ATINC                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ATINC_POFFSET)
#define BPORT1_AB_ATINC_INC             0x7f
#define BPORT1_AB_ATINC_INC_GET(_v)     (_v & 0x7f)
#define BPORT1_AB_ATINC_INC_CORR        (0x7f << 8)
#define BPORT1_AB_ATINC_INC_CORR_GET(_v)  ((_v >> 8) & 0x7f)

#define BPORT1_AB_ATSTMP_POFFSET        0x418
#define BPORT1_AB_ATSTMP                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ATSTMP_POFFSET)
#define BPORT1_AB_ATSTMP_TIMESTAMP      0xffffffff
#define BPORT1_AB_ATSTMP_TIMESTAMP_GET(_v)  (_v & 0xffffffff)

#define BPORT1_AB_TGSR_POFFSET          0x604
#define BPORT1_AB_TGSR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TGSR_POFFSET)
#define BPORT1_AB_TGSR_TF0              0x1
#define BPORT1_AB_TGSR_TF0_GET(_v)      (_v & 0x1)
#define BPORT1_AB_TGSR_TF1              (0x1 << 1)
#define BPORT1_AB_TGSR_TF1_GET(_v)      ((_v >> 1) & 0x1)
#define BPORT1_AB_TGSR_TF2              (0x1 << 2)
#define BPORT1_AB_TGSR_TF2_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_TGSR_TF3              (0x1 << 3)
#define BPORT1_AB_TGSR_TF3_GET(_v)      ((_v >> 3) & 0x1)

#define BPORT1_AB_TCSR0_POFFSET         0x608
#define BPORT1_AB_TCSR0                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCSR0_POFFSET)
#define BPORT1_AB_TCSR0_TDRE            0x1
#define BPORT1_AB_TCSR0_TDRE_GET(_v)    (_v & 0x1)
#define BPORT1_AB_TCSR0_TF              (0x1 << 7)
#define BPORT1_AB_TCSR0_TF_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_TCSR0_TIE             (0x1 << 6)
#define BPORT1_AB_TCSR0_TIE_GET(_v)     ((_v >> 6) & 0x1)
#define BPORT1_AB_TCSR0_TMODE           (0xf << 2)
#define BPORT1_AB_TCSR0_TMODE_GET(_v)   ((_v >> 2) & 0xf)

#define BPORT1_AB_TCCR0_POFFSET         0x60c
#define BPORT1_AB_TCCR0                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCCR0_POFFSET)
#define BPORT1_AB_TCCR0_TCC             0xffffffff
#define BPORT1_AB_TCCR0_TCC_GET(_v)     (_v & 0xffffffff)

#define BPORT1_AB_TCSR1_POFFSET         0x610
#define BPORT1_AB_TCSR1                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCSR1_POFFSET)
#define BPORT1_AB_TCSR1_TDRE            0x1
#define BPORT1_AB_TCSR1_TDRE_GET(_v)    (_v & 0x1)
#define BPORT1_AB_TCSR1_TF              (0x1 << 7)
#define BPORT1_AB_TCSR1_TF_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_TCSR1_TIE             (0x1 << 6)
#define BPORT1_AB_TCSR1_TIE_GET(_v)     ((_v >> 6) & 0x1)
#define BPORT1_AB_TCSR1_TMODE           (0xf << 2)
#define BPORT1_AB_TCSR1_TMODE_GET(_v)   ((_v >> 2) & 0xf)

#define BPORT1_AB_TCCR1_POFFSET         0x614
#define BPORT1_AB_TCCR1                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCCR1_POFFSET)
#define BPORT1_AB_TCCR1_TCC             0xffffffff
#define BPORT1_AB_TCCR1_TCC_GET(_v)     (_v & 0xffffffff)

#define BPORT1_AB_TCSR2_POFFSET         0x618
#define BPORT1_AB_TCSR2                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCSR2_POFFSET)
#define BPORT1_AB_TCSR2_TDRE            0x1
#define BPORT1_AB_TCSR2_TDRE_GET(_v)    (_v & 0x1)
#define BPORT1_AB_TCSR2_TF              (0x1 << 7)
#define BPORT1_AB_TCSR2_TF_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_TCSR2_TIE             (0x1 << 6)
#define BPORT1_AB_TCSR2_TIE_GET(_v)     ((_v >> 6) & 0x1)
#define BPORT1_AB_TCSR2_TMODE           (0xf << 2)
#define BPORT1_AB_TCSR2_TMODE_GET(_v)   ((_v >> 2) & 0xf)

#define BPORT1_AB_TCCR2_POFFSET         0x61c
#define BPORT1_AB_TCCR2                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCCR2_POFFSET)
#define BPORT1_AB_TCCR2_TCC             0xffffffff
#define BPORT1_AB_TCCR2_TCC_GET(_v)     (_v & 0xffffffff)

#define BPORT1_AB_TCSR3_POFFSET         0x620
#define BPORT1_AB_TCSR3                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCSR3_POFFSET)
#define BPORT1_AB_TCSR3_TDRE            0x1
#define BPORT1_AB_TCSR3_TDRE_GET(_v)    (_v & 0x1)
#define BPORT1_AB_TCSR3_TF              (0x1 << 7)
#define BPORT1_AB_TCSR3_TF_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_TCSR3_TIE             (0x1 << 6)
#define BPORT1_AB_TCSR3_TIE_GET(_v)     ((_v >> 6) & 0x1)
#define BPORT1_AB_TCSR3_TMODE           (0xf << 2)
#define BPORT1_AB_TCSR3_TMODE_GET(_v)   ((_v >> 2) & 0xf)

#define BPORT1_AB_TCCR3_POFFSET         0x624
#define BPORT1_AB_TCCR3                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCCR3_POFFSET)
#define BPORT1_AB_TCCR3_TCC             0xffffffff
#define BPORT1_AB_TCCR3_TCC_GET(_v)     (_v & 0xffffffff)


#endif

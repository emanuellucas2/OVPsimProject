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
#define BPORT1_AB_POWER_POFFSET         0x0
#define BPORT1_AB_POWER                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_POWER_POFFSET)

#define BPORT1_AB_CLOCK_POFFSET         0x4
#define BPORT1_AB_CLOCK                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CLOCK_POFFSET)

#define BPORT1_AB_CMDARG_POFFSET        0x8
#define BPORT1_AB_CMDARG                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CMDARG_POFFSET)

#define BPORT1_AB_CMD_POFFSET           0xc
#define BPORT1_AB_CMD                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CMD_POFFSET)
#define BPORT1_AB_CMD_C_INDEX           0x3f
#define BPORT1_AB_CMD_C_INDEX_GET(_v)   (_v & 0x3f)
#define BPORT1_AB_CMD_C_RESPONSE        (0x1 << 6)
#define BPORT1_AB_CMD_C_RESPONSE_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_CMD_C_LONGRESP        (0x1 << 7)
#define BPORT1_AB_CMD_C_LONGRESP_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_CMD_C_INTERRUPT       (0x1 << 8)
#define BPORT1_AB_CMD_C_INTERRUPT_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_CMD_C_PENDING         (0x1 << 9)
#define BPORT1_AB_CMD_C_PENDING_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_CMD_C_ENABLE          (0x1 << 10)
#define BPORT1_AB_CMD_C_ENABLE_GET(_v)  ((_v >> 10) & 0x1)

#define BPORT1_AB_RESPCMD_POFFSET       0x10
#define BPORT1_AB_RESPCMD               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RESPCMD_POFFSET)

#define BPORT1_AB_RESPONSE0_POFFSET     0x14
#define BPORT1_AB_RESPONSE0             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RESPONSE0_POFFSET)

#define BPORT1_AB_RESPONSE1_POFFSET     0x18
#define BPORT1_AB_RESPONSE1             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RESPONSE1_POFFSET)

#define BPORT1_AB_RESPONSE2_POFFSET     0x1c
#define BPORT1_AB_RESPONSE2             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RESPONSE2_POFFSET)

#define BPORT1_AB_RESPONSE3_POFFSET     0x20
#define BPORT1_AB_RESPONSE3             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RESPONSE3_POFFSET)

#define BPORT1_AB_DATATIMER_POFFSET     0x24
#define BPORT1_AB_DATATIMER             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DATATIMER_POFFSET)

#define BPORT1_AB_DATALENGTH_POFFSET    0x28
#define BPORT1_AB_DATALENGTH            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DATALENGTH_POFFSET)

#define BPORT1_AB_DATACTRL_POFFSET      0x2c
#define BPORT1_AB_DATACTRL              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DATACTRL_POFFSET)
#define BPORT1_AB_DATACTRL_D_ENABLE     0x1
#define BPORT1_AB_DATACTRL_D_ENABLE_GET(_v)  (_v & 0x1)
#define BPORT1_AB_DATACTRL_D_DIRECTION  (0x1 << 1)
#define BPORT1_AB_DATACTRL_D_DIRECTION_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_DATACTRL_D_MODE       (0x1 << 2)
#define BPORT1_AB_DATACTRL_D_MODE_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_DATACTRL_D_DMAENABLE  (0x1 << 3)
#define BPORT1_AB_DATACTRL_D_DMAENABLE_GET(_v)  ((_v >> 3) & 0x1)

#define BPORT1_AB_DATACNT_POFFSET       0x30
#define BPORT1_AB_DATACNT               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DATACNT_POFFSET)

#define BPORT1_AB_STATUS_POFFSET        0x34
#define BPORT1_AB_STATUS                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_STATUS_POFFSET)
#define BPORT1_AB_STATUS_S_CMDCRCFAIL   0x1
#define BPORT1_AB_STATUS_S_CMDCRCFAIL_GET(_v)  (_v & 0x1)
#define BPORT1_AB_STATUS_S_DATACRCFAIL  (0x1 << 1)
#define BPORT1_AB_STATUS_S_DATACRCFAIL_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_STATUS_S_CMDTIMEOUT   (0x1 << 2)
#define BPORT1_AB_STATUS_S_CMDTIMEOUT_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_STATUS_S_DATATIMEOUT  (0x1 << 3)
#define BPORT1_AB_STATUS_S_DATATIMEOUT_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_STATUS_S_TXUNDERRUN   (0x1 << 4)
#define BPORT1_AB_STATUS_S_TXUNDERRUN_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_STATUS_S_RXOVERRUN    (0x1 << 5)
#define BPORT1_AB_STATUS_S_RXOVERRUN_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_STATUS_S_CMDRESPEND   (0x1 << 6)
#define BPORT1_AB_STATUS_S_CMDRESPEND_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_STATUS_S_CMDSENT      (0x1 << 7)
#define BPORT1_AB_STATUS_S_CMDSENT_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_STATUS_S_DATAEND      (0x1 << 8)
#define BPORT1_AB_STATUS_S_DATAEND_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_STATUS_S_DATABLOCKEND  (0x1 << 10)
#define BPORT1_AB_STATUS_S_DATABLOCKEND_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_STATUS_S_CMDACTIVE    (0x1 << 11)
#define BPORT1_AB_STATUS_S_CMDACTIVE_GET(_v)  ((_v >> 11) & 0x1)
#define BPORT1_AB_STATUS_S_TXACTIVE     (0x1 << 12)
#define BPORT1_AB_STATUS_S_TXACTIVE_GET(_v)  ((_v >> 12) & 0x1)
#define BPORT1_AB_STATUS_S_RXACTIVE     (0x1 << 13)
#define BPORT1_AB_STATUS_S_RXACTIVE_GET(_v)  ((_v >> 13) & 0x1)
#define BPORT1_AB_STATUS_S_TXFIFOHALFEMPTY  (0x1 << 14)
#define BPORT1_AB_STATUS_S_TXFIFOHALFEMPTY_GET(_v)  ((_v >> 14) & 0x1)
#define BPORT1_AB_STATUS_S_RXFIFOHALFFULL  (0x1 << 15)
#define BPORT1_AB_STATUS_S_RXFIFOHALFFULL_GET(_v)  ((_v >> 15) & 0x1)
#define BPORT1_AB_STATUS_S_TXFIFOFULL   (0x1 << 16)
#define BPORT1_AB_STATUS_S_TXFIFOFULL_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_STATUS_S_RXFIFOFULL   (0x1 << 17)
#define BPORT1_AB_STATUS_S_RXFIFOFULL_GET(_v)  ((_v >> 17) & 0x1)
#define BPORT1_AB_STATUS_S_TXFIFOEMPTY  (0x1 << 18)
#define BPORT1_AB_STATUS_S_TXFIFOEMPTY_GET(_v)  ((_v >> 18) & 0x1)
#define BPORT1_AB_STATUS_S_RXFIFOEMPTY  (0x1 << 19)
#define BPORT1_AB_STATUS_S_RXFIFOEMPTY_GET(_v)  ((_v >> 19) & 0x1)
#define BPORT1_AB_STATUS_S_TXDATAAVLBL  (0x1 << 20)
#define BPORT1_AB_STATUS_S_TXDATAAVLBL_GET(_v)  ((_v >> 20) & 0x1)
#define BPORT1_AB_STATUS_S_RXDATAAVLBL  (0x1 << 21)
#define BPORT1_AB_STATUS_S_RXDATAAVLBL_GET(_v)  ((_v >> 21) & 0x1)

#define BPORT1_AB_CLEAR_POFFSET         0x38
#define BPORT1_AB_CLEAR                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CLEAR_POFFSET)

#define BPORT1_AB_MASK0_POFFSET         0x3c
#define BPORT1_AB_MASK0                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MASK0_POFFSET)

#define BPORT1_AB_MASK1_POFFSET         0x40
#define BPORT1_AB_MASK1                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MASK1_POFFSET)

#define BPORT1_AB_FIFOCNT_POFFSET       0x48
#define BPORT1_AB_FIFOCNT               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FIFOCNT_POFFSET)

#define BPORT1_AB_PERIPHID0_POFFSET     0xfe0
#define BPORT1_AB_PERIPHID0             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PERIPHID0_POFFSET)

#define BPORT1_AB_PERIPHID1_POFFSET     0xfe4
#define BPORT1_AB_PERIPHID1             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PERIPHID1_POFFSET)

#define BPORT1_AB_PERIPHID2_POFFSET     0xfe8
#define BPORT1_AB_PERIPHID2             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PERIPHID2_POFFSET)

#define BPORT1_AB_PERIPHID3_POFFSET     0xfec
#define BPORT1_AB_PERIPHID3             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PERIPHID3_POFFSET)

#define BPORT1_AB_PCELLID0_POFFSET      0xff0
#define BPORT1_AB_PCELLID0              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PCELLID0_POFFSET)

#define BPORT1_AB_PCELLID1_POFFSET      0xff4
#define BPORT1_AB_PCELLID1              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PCELLID1_POFFSET)

#define BPORT1_AB_PCELLID2_POFFSET      0xff8
#define BPORT1_AB_PCELLID2              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PCELLID2_POFFSET)

#define BPORT1_AB_PCELLID3_POFFSET      0xffc
#define BPORT1_AB_PCELLID3              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PCELLID3_POFFSET)

#define BPORT1_AB_RESERVED1_POFFSET     0x4c
#define BPORT1_AB_RESERVED1             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RESERVED1_POFFSET)
#define BPORT1_AB_RESERVED1_BYTES       0x34

#define BPORT1_AB_RESERVED2_POFFSET     0xc0
#define BPORT1_AB_RESERVED2             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RESERVED2_POFFSET)
#define BPORT1_AB_RESERVED2_BYTES       0xf20

#define BPORT1_AB_FIFO_POFFSET          0x80
#define BPORT1_AB_FIFO                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FIFO_POFFSET)
#define BPORT1_AB_FIFO_BYTES            0x40


#endif

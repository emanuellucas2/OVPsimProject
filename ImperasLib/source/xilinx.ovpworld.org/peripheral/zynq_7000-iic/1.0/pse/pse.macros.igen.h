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

// Set the macro 'I2C_SLAVE' to the base of port 'I2C_Slave'
#ifndef I2C_SLAVE
#error I2C_SLAVE is undefined. It needs to be set to the port base address
#endif
// Set the macro 'BPORT1' to the base of port 'bport1'
#ifndef BPORT1
#error BPORT1 is undefined. It needs to be set to the port base address
#endif


#define I2C_SLAVE_DR_POFFSET            0x0
#define I2C_SLAVE_DR_BUFF_POFFSET       0x0
#define I2C_SLAVE_DR_BUFF               (I2C_SLAVE + I2C_SLAVE_DR_POFFSET + I2C_SLAVE_DR_BUFF_POFFSET)
#define I2C_SLAVE_DR_BUFF_BYTES         0x4


#define BPORT1_AB_POFFSET               0x0
#define BPORT1_AB_CONTROL_POFFSET       0x0
#define BPORT1_AB_CONTROL               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CONTROL_POFFSET)
#define BPORT1_AB_CONTROL_DIV_A         (0x3 << 14)
#define BPORT1_AB_CONTROL_DIV_A_GET(_v)  ((_v >> 14) & 0x3)
#define BPORT1_AB_CONTROL_DIV_B         (0x3f << 8)
#define BPORT1_AB_CONTROL_DIV_B_GET(_v)  ((_v >> 8) & 0x3f)
#define BPORT1_AB_CONTROL_CLR_FIFO      (0x1 << 6)
#define BPORT1_AB_CONTROL_CLR_FIFO_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_CONTROL_SLVMON        (0x1 << 5)
#define BPORT1_AB_CONTROL_SLVMON_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_CONTROL_HOLD          (0x1 << 4)
#define BPORT1_AB_CONTROL_HOLD_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_CONTROL_ACKEN         (0x1 << 3)
#define BPORT1_AB_CONTROL_ACKEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_CONTROL_NEA           (0x1 << 2)
#define BPORT1_AB_CONTROL_NEA_GET(_v)   ((_v >> 2) & 0x1)
#define BPORT1_AB_CONTROL_MS            (0x1 << 1)
#define BPORT1_AB_CONTROL_MS_GET(_v)    ((_v >> 1) & 0x1)
#define BPORT1_AB_CONTROL_RW            0x1
#define BPORT1_AB_CONTROL_RW_GET(_v)    (_v & 0x1)

#define BPORT1_AB_I2CADDRESS_POFFSET    0x8
#define BPORT1_AB_I2CADDRESS            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_I2CADDRESS_POFFSET)
#define BPORT1_AB_I2CADDRESS_ADD        0x1ff
#define BPORT1_AB_I2CADDRESS_ADD_GET(_v)  (_v & 0x1ff)

#define BPORT1_AB_I2CDATA_POFFSET       0xc
#define BPORT1_AB_I2CDATA               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_I2CDATA_POFFSET)
#define BPORT1_AB_I2CDATA_DATA          0xff
#define BPORT1_AB_I2CDATA_DATA_GET(_v)  (_v & 0xff)

#define BPORT1_AB_TRANSFERSIZE_POFFSET  0x14
#define BPORT1_AB_TRANSFERSIZE          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TRANSFERSIZE_POFFSET)
#define BPORT1_AB_TRANSFERSIZE_XFERSZ   0xff
#define BPORT1_AB_TRANSFERSIZE_XFERSZ_GET(_v)  (_v & 0xff)

#define BPORT1_AB_SLAVEMONPAUSE_POFFSET  0x18
#define BPORT1_AB_SLAVEMONPAUSE         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SLAVEMONPAUSE_POFFSET)
#define BPORT1_AB_SLAVEMONPAUSE_PAUSE   0xff
#define BPORT1_AB_SLAVEMONPAUSE_PAUSE_GET(_v)  (_v & 0xff)

#define BPORT1_AB_TIMEOUT_POFFSET       0x1c
#define BPORT1_AB_TIMEOUT               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TIMEOUT_POFFSET)
#define BPORT1_AB_TIMEOUT_TO            0xff
#define BPORT1_AB_TIMEOUT_TO_GET(_v)    (_v & 0xff)

#define BPORT1_AB_INTERRUPTMASK_POFFSET  0x20
#define BPORT1_AB_INTERRUPTMASK         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INTERRUPTMASK_POFFSET)
#define BPORT1_AB_INTERRUPTMASK_ARB_LOST  (0x1 << 9)
#define BPORT1_AB_INTERRUPTMASK_ARB_LOST_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_INTERRUPTMASK_RX_UNF  (0x1 << 7)
#define BPORT1_AB_INTERRUPTMASK_RX_UNF_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_INTERRUPTMASK_TX_OVF  (0x1 << 6)
#define BPORT1_AB_INTERRUPTMASK_TX_OVF_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_INTERRUPTMASK_RX_OVF  (0x1 << 5)
#define BPORT1_AB_INTERRUPTMASK_RX_OVF_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_INTERRUPTMASK_SLV_RDY  (0x1 << 4)
#define BPORT1_AB_INTERRUPTMASK_SLV_RDY_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_INTERRUPTMASK_TO      (0x1 << 3)
#define BPORT1_AB_INTERRUPTMASK_TO_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_INTERRUPTMASK_NACK    (0x1 << 2)
#define BPORT1_AB_INTERRUPTMASK_NACK_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_INTERRUPTMASK_DATA    (0x1 << 1)
#define BPORT1_AB_INTERRUPTMASK_DATA_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_INTERRUPTMASK_COMP    0x1
#define BPORT1_AB_INTERRUPTMASK_COMP_GET(_v)  (_v & 0x1)

#define BPORT1_AB_INTERRUPTENABLE_POFFSET  0x24
#define BPORT1_AB_INTERRUPTENABLE       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INTERRUPTENABLE_POFFSET)
#define BPORT1_AB_INTERRUPTENABLE_ARB_LOST  (0x1 << 9)
#define BPORT1_AB_INTERRUPTENABLE_ARB_LOST_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_INTERRUPTENABLE_RX_UNF  (0x1 << 7)
#define BPORT1_AB_INTERRUPTENABLE_RX_UNF_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_INTERRUPTENABLE_TX_OVF  (0x1 << 6)
#define BPORT1_AB_INTERRUPTENABLE_TX_OVF_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_INTERRUPTENABLE_RX_OVF  (0x1 << 5)
#define BPORT1_AB_INTERRUPTENABLE_RX_OVF_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_INTERRUPTENABLE_SLV_RDY  (0x1 << 4)
#define BPORT1_AB_INTERRUPTENABLE_SLV_RDY_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_INTERRUPTENABLE_TO    (0x1 << 3)
#define BPORT1_AB_INTERRUPTENABLE_TO_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_INTERRUPTENABLE_NACK  (0x1 << 2)
#define BPORT1_AB_INTERRUPTENABLE_NACK_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_INTERRUPTENABLE_DATA  (0x1 << 1)
#define BPORT1_AB_INTERRUPTENABLE_DATA_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_INTERRUPTENABLE_COMP  0x1
#define BPORT1_AB_INTERRUPTENABLE_COMP_GET(_v)  (_v & 0x1)

#define BPORT1_AB_INTERRUPTDISABLE_POFFSET  0x28
#define BPORT1_AB_INTERRUPTDISABLE      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INTERRUPTDISABLE_POFFSET)
#define BPORT1_AB_INTERRUPTDISABLE_ARB_LOST  (0x1 << 9)
#define BPORT1_AB_INTERRUPTDISABLE_ARB_LOST_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_INTERRUPTDISABLE_RX_UNF  (0x1 << 7)
#define BPORT1_AB_INTERRUPTDISABLE_RX_UNF_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_INTERRUPTDISABLE_TX_OVF  (0x1 << 6)
#define BPORT1_AB_INTERRUPTDISABLE_TX_OVF_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_INTERRUPTDISABLE_RX_OVF  (0x1 << 5)
#define BPORT1_AB_INTERRUPTDISABLE_RX_OVF_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_INTERRUPTDISABLE_SLV_RDY  (0x1 << 4)
#define BPORT1_AB_INTERRUPTDISABLE_SLV_RDY_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_INTERRUPTDISABLE_TO   (0x1 << 3)
#define BPORT1_AB_INTERRUPTDISABLE_TO_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_INTERRUPTDISABLE_NACK  (0x1 << 2)
#define BPORT1_AB_INTERRUPTDISABLE_NACK_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_INTERRUPTDISABLE_DATA  (0x1 << 1)
#define BPORT1_AB_INTERRUPTDISABLE_DATA_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_INTERRUPTDISABLE_COMP  0x1
#define BPORT1_AB_INTERRUPTDISABLE_COMP_GET(_v)  (_v & 0x1)

#define BPORT1_AB_BUFFER1_POFFSET       0x2c
#define BPORT1_AB_BUFFER1               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BUFFER1_POFFSET)
#define BPORT1_AB_BUFFER1_BYTES         0xfd4

#define BPORT1_AB_STATUS_POFFSET        0x4
#define BPORT1_AB_STATUS                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_STATUS_POFFSET)
#define BPORT1_AB_STATUS_BYTES          0x10

#define BPORT1_AB_INTERRUPTSTATUS_POFFSET  0x10
#define BPORT1_AB_INTERRUPTSTATUS       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INTERRUPTSTATUS_POFFSET)
#define BPORT1_AB_INTERRUPTSTATUS_BYTES  0x10


#endif

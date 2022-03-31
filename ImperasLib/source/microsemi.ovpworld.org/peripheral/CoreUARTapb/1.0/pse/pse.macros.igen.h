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

// Set the macro 'PORT0' to the base of port 'port0'
#ifndef PORT0
#error PORT0 is undefined. It needs to be set to the port base address
#endif


#define PORT0_REG_POFFSET               0x0
#define PORT0_REG_TXDATA_POFFSET        0x0
#define PORT0_REG_TXDATA                (PORT0 + PORT0_REG_POFFSET + PORT0_REG_TXDATA_POFFSET)

#define PORT0_REG_RXDATA_POFFSET        0x4
#define PORT0_REG_RXDATA                (PORT0 + PORT0_REG_POFFSET + PORT0_REG_RXDATA_POFFSET)

#define PORT0_REG_CTRL1_POFFSET         0x8
#define PORT0_REG_CTRL1                 (PORT0 + PORT0_REG_POFFSET + PORT0_REG_CTRL1_POFFSET)
#define PORT0_REG_CTRL1_BAUD_VALUE      0xff
#define PORT0_REG_CTRL1_BAUD_VALUE_GET(_v)  (_v & 0xff)

#define PORT0_REG_CTRL2_POFFSET         0xc
#define PORT0_REG_CTRL2                 (PORT0 + PORT0_REG_POFFSET + PORT0_REG_CTRL2_POFFSET)
#define PORT0_REG_CTRL2_BIT8            0x1
#define PORT0_REG_CTRL2_BIT8_GET(_v)    (_v & 0x1)
#define PORT0_REG_CTRL2_PARITY_EN       (0x1 << 1)
#define PORT0_REG_CTRL2_PARITY_EN_GET(_v)  ((_v >> 1) & 0x1)
#define PORT0_REG_CTRL2_ODD_N_EVEN      (0x1 << 2)
#define PORT0_REG_CTRL2_ODD_N_EVEN_GET(_v)  ((_v >> 2) & 0x1)
#define PORT0_REG_CTRL2_BAUD_VALUE      (0x1f << 3)
#define PORT0_REG_CTRL2_BAUD_VALUE_GET(_v)  ((_v >> 3) & 0x1f)

#define PORT0_REG_STATUS_POFFSET        0x10
#define PORT0_REG_STATUS                (PORT0 + PORT0_REG_POFFSET + PORT0_REG_STATUS_POFFSET)
#define PORT0_REG_STATUS_TXRDY          0x1
#define PORT0_REG_STATUS_TXRDY_GET(_v)  (_v & 0x1)
#define PORT0_REG_STATUS_RXRDY          (0x1 << 1)
#define PORT0_REG_STATUS_RXRDY_GET(_v)  ((_v >> 1) & 0x1)
#define PORT0_REG_STATUS_PARITY_ERR     (0x1 << 2)
#define PORT0_REG_STATUS_PARITY_ERR_GET(_v)  ((_v >> 2) & 0x1)
#define PORT0_REG_STATUS_OVERFLOW       (0x1 << 3)
#define PORT0_REG_STATUS_OVERFLOW_GET(_v)  ((_v >> 3) & 0x1)
#define PORT0_REG_STATUS_FRAMING_ERR    (0x1 << 4)
#define PORT0_REG_STATUS_FRAMING_ERR_GET(_v)  ((_v >> 4) & 0x1)

#define PORT0_REG_CTRL3_POFFSET         0x14
#define PORT0_REG_CTRL3                 (PORT0 + PORT0_REG_POFFSET + PORT0_REG_CTRL3_POFFSET)
#define PORT0_REG_CTRL3_BAUD_VALUE_FRACTION  0x7
#define PORT0_REG_CTRL3_BAUD_VALUE_FRACTION_GET(_v)  (_v & 0x7)


#endif

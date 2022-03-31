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

// Set the macro 'SP1' to the base of port 'sp1'
#ifndef SP1
#error SP1 is undefined. It needs to be set to the port base address
#endif


#define SP1_REG0_POFFSET                0x0
#define SP1_REG0_RXDATA_POFFSET         0x0
#define SP1_REG0_RXDATA                 (SP1 + SP1_REG0_POFFSET + SP1_REG0_RXDATA_POFFSET)

#define SP1_REG0_TXDATA_POFFSET         0x4
#define SP1_REG0_TXDATA                 (SP1 + SP1_REG0_POFFSET + SP1_REG0_TXDATA_POFFSET)

#define SP1_REG0_STATUS_POFFSET         0x8
#define SP1_REG0_STATUS                 (SP1 + SP1_REG0_POFFSET + SP1_REG0_STATUS_POFFSET)
#define SP1_REG0_STATUS_PE              0x1
#define SP1_REG0_STATUS_PE_GET(_v)      (_v & 0x1)
#define SP1_REG0_STATUS_FE              (0x1 << 1)
#define SP1_REG0_STATUS_FE_GET(_v)      ((_v >> 1) & 0x1)
#define SP1_REG0_STATUS_BRK             (0x1 << 2)
#define SP1_REG0_STATUS_BRK_GET(_v)     ((_v >> 2) & 0x1)
#define SP1_REG0_STATUS_ROE             (0x1 << 3)
#define SP1_REG0_STATUS_ROE_GET(_v)     ((_v >> 3) & 0x1)
#define SP1_REG0_STATUS_TOE             (0x1 << 4)
#define SP1_REG0_STATUS_TOE_GET(_v)     ((_v >> 4) & 0x1)
#define SP1_REG0_STATUS_TMT             (0x1 << 5)
#define SP1_REG0_STATUS_TMT_GET(_v)     ((_v >> 5) & 0x1)
#define SP1_REG0_STATUS_TRDY            (0x1 << 6)
#define SP1_REG0_STATUS_TRDY_GET(_v)    ((_v >> 6) & 0x1)
#define SP1_REG0_STATUS_RRDY            (0x1 << 7)
#define SP1_REG0_STATUS_RRDY_GET(_v)    ((_v >> 7) & 0x1)
#define SP1_REG0_STATUS_E               (0x3 << 8)
#define SP1_REG0_STATUS_E_GET(_v)       ((_v >> 8) & 0x3)
#define SP1_REG0_STATUS_DCTS            (0x1 << 10)
#define SP1_REG0_STATUS_DCTS_GET(_v)    ((_v >> 10) & 0x1)
#define SP1_REG0_STATUS_CTS             (0x1 << 11)
#define SP1_REG0_STATUS_CTS_GET(_v)     ((_v >> 11) & 0x1)
#define SP1_REG0_STATUS_EOP             (0x1 << 12)
#define SP1_REG0_STATUS_EOP_GET(_v)     ((_v >> 12) & 0x1)

#define SP1_REG0_CONTROL_POFFSET        0xc
#define SP1_REG0_CONTROL                (SP1 + SP1_REG0_POFFSET + SP1_REG0_CONTROL_POFFSET)
#define SP1_REG0_CONTROL_IPE            0x1
#define SP1_REG0_CONTROL_IPE_GET(_v)    (_v & 0x1)
#define SP1_REG0_CONTROL_IFE            (0x1 << 1)
#define SP1_REG0_CONTROL_IFE_GET(_v)    ((_v >> 1) & 0x1)
#define SP1_REG0_CONTROL_IBRK           (0x1 << 2)
#define SP1_REG0_CONTROL_IBRK_GET(_v)   ((_v >> 2) & 0x1)
#define SP1_REG0_CONTROL_IROE           (0x1 << 3)
#define SP1_REG0_CONTROL_IROE_GET(_v)   ((_v >> 3) & 0x1)
#define SP1_REG0_CONTROL_ITOE           (0x1 << 4)
#define SP1_REG0_CONTROL_ITOE_GET(_v)   ((_v >> 4) & 0x1)
#define SP1_REG0_CONTROL_ITMT           (0x1 << 5)
#define SP1_REG0_CONTROL_ITMT_GET(_v)   ((_v >> 5) & 0x1)
#define SP1_REG0_CONTROL_ITRDY          (0x1 << 6)
#define SP1_REG0_CONTROL_ITRDY_GET(_v)  ((_v >> 6) & 0x1)
#define SP1_REG0_CONTROL_IRRDY          (0x1 << 7)
#define SP1_REG0_CONTROL_IRRDY_GET(_v)  ((_v >> 7) & 0x1)
#define SP1_REG0_CONTROL_IE             (0x1 << 8)
#define SP1_REG0_CONTROL_IE_GET(_v)     ((_v >> 8) & 0x1)
#define SP1_REG0_CONTROL_TRBK           (0x1 << 9)
#define SP1_REG0_CONTROL_TRBK_GET(_v)   ((_v >> 9) & 0x1)
#define SP1_REG0_CONTROL_IDCTS          (0x1 << 10)
#define SP1_REG0_CONTROL_IDCTS_GET(_v)  ((_v >> 10) & 0x1)
#define SP1_REG0_CONTROL_RTS            (0x1 << 11)
#define SP1_REG0_CONTROL_RTS_GET(_v)    ((_v >> 11) & 0x1)
#define SP1_REG0_CONTROL_IEOP           (0x1 << 12)
#define SP1_REG0_CONTROL_IEOP_GET(_v)   ((_v >> 12) & 0x1)

#define SP1_REG0_DIVISOR_POFFSET        0x10
#define SP1_REG0_DIVISOR                (SP1 + SP1_REG0_POFFSET + SP1_REG0_DIVISOR_POFFSET)

#define SP1_REG0_EOP_POFFSET            0x14
#define SP1_REG0_EOP                    (SP1 + SP1_REG0_POFFSET + SP1_REG0_EOP_POFFSET)


#endif

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

// Set the macro 'CSIBP0' to the base of port 'CSIBP0'
#ifndef CSIBP0
#error CSIBP0 is undefined. It needs to be set to the port base address
#endif


#define CSIBP0_REG0_POFFSET             0x0
#define CSIBP0_REG0_CTL0_POFFSET        0x0
#define CSIBP0_REG0_CTL0                (CSIBP0 + CSIBP0_REG0_POFFSET + CSIBP0_REG0_CTL0_POFFSET)
#define CSIBP0_REG0_CTL0_SCE            0x1
#define CSIBP0_REG0_CTL0_SCE_GET(_v)    (_v & 0x1)
#define CSIBP0_REG0_CTL0_TMS            (0x1 << 1)
#define CSIBP0_REG0_CTL0_TMS_GET(_v)    ((_v >> 1) & 0x1)
#define CSIBP0_REG0_CTL0_SSE            (0x1 << 2)
#define CSIBP0_REG0_CTL0_SSE_GET(_v)    ((_v >> 2) & 0x1)
#define CSIBP0_REG0_CTL0_DIR            (0x1 << 4)
#define CSIBP0_REG0_CTL0_DIR_GET(_v)    ((_v >> 4) & 0x1)
#define CSIBP0_REG0_CTL0_RXE            (0x1 << 5)
#define CSIBP0_REG0_CTL0_RXE_GET(_v)    ((_v >> 5) & 0x1)
#define CSIBP0_REG0_CTL0_TXE            (0x1 << 6)
#define CSIBP0_REG0_CTL0_TXE_GET(_v)    ((_v >> 6) & 0x1)
#define CSIBP0_REG0_CTL0_PWR            (0x1 << 7)
#define CSIBP0_REG0_CTL0_PWR_GET(_v)    ((_v >> 7) & 0x1)

#define CSIBP0_REG0_CTL1_POFFSET        0x1
#define CSIBP0_REG0_CTL1                (CSIBP0 + CSIBP0_REG0_POFFSET + CSIBP0_REG0_CTL1_POFFSET)
#define CSIBP0_REG0_CTL1_CKS            0xf
#define CSIBP0_REG0_CTL1_CKS_GET(_v)    (_v & 0xf)

#define CSIBP0_REG0_CTL2_POFFSET        0x2
#define CSIBP0_REG0_CTL2                (CSIBP0 + CSIBP0_REG0_POFFSET + CSIBP0_REG0_CTL2_POFFSET)
#define CSIBP0_REG0_CTL2_CL             0xf
#define CSIBP0_REG0_CTL2_CL_GET(_v)     (_v & 0xf)

#define CSIBP0_REG0_STR_POFFSET         0x3
#define CSIBP0_REG0_STR                 (CSIBP0 + CSIBP0_REG0_POFFSET + CSIBP0_REG0_STR_POFFSET)
#define CSIBP0_REG0_STR_OVE             0x1
#define CSIBP0_REG0_STR_OVE_GET(_v)     (_v & 0x1)
#define CSIBP0_REG0_STR_TSF             (0x1 << 7)
#define CSIBP0_REG0_STR_TSF_GET(_v)     ((_v >> 7) & 0x1)

#define CSIBP0_REG1_POFFSET             0x4
#define CSIBP0_REG1_RX_POFFSET          0x0
#define CSIBP0_REG1_RX                  (CSIBP0 + CSIBP0_REG1_POFFSET + CSIBP0_REG1_RX_POFFSET)
#define CSIBP0_REG1_RX_RXL              0xff
#define CSIBP0_REG1_RX_RXL_GET(_v)      (_v & 0xff)
#define CSIBP0_REG1_RX_RXH              (0xff << 8)
#define CSIBP0_REG1_RX_RXH_GET(_v)      ((_v >> 8) & 0xff)

#define CSIBP0_REG1_TX_POFFSET          0x2
#define CSIBP0_REG1_TX                  (CSIBP0 + CSIBP0_REG1_POFFSET + CSIBP0_REG1_TX_POFFSET)
#define CSIBP0_REG1_TX_TXL              0xff
#define CSIBP0_REG1_TX_TXL_GET(_v)      (_v & 0xff)
#define CSIBP0_REG1_TX_TXH              (0xff << 8)
#define CSIBP0_REG1_TX_TXH_GET(_v)      ((_v >> 8) & 0xff)


#endif

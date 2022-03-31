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

// Set the macro 'BCUP0' to the base of port 'BCUP0'
#ifndef BCUP0
#error BCUP0 is undefined. It needs to be set to the port base address
#endif


#define BCUP0_REG0_POFFSET              0x0
#define BCUP0_REG0_CSC0_POFFSET         0x0
#define BCUP0_REG0_CSC0                 (BCUP0 + BCUP0_REG0_POFFSET + BCUP0_REG0_CSC0_POFFSET)
#define BCUP0_REG0_CSC0_CS0             0xf
#define BCUP0_REG0_CSC0_CS0_GET(_v)     (_v & 0xf)
#define BCUP0_REG0_CSC0_CS1             (0xf << 4)
#define BCUP0_REG0_CSC0_CS1_GET(_v)     ((_v >> 4) & 0xf)
#define BCUP0_REG0_CSC0_CS2             (0xf << 8)
#define BCUP0_REG0_CSC0_CS2_GET(_v)     ((_v >> 8) & 0xf)
#define BCUP0_REG0_CSC0_CS3             (0xf << 12)
#define BCUP0_REG0_CSC0_CS3_GET(_v)     ((_v >> 12) & 0xf)

#define BCUP0_REG0_CSC1_POFFSET         0x2
#define BCUP0_REG0_CSC1                 (BCUP0 + BCUP0_REG0_POFFSET + BCUP0_REG0_CSC1_POFFSET)
#define BCUP0_REG0_CSC1_CS7             0xf
#define BCUP0_REG0_CSC1_CS7_GET(_v)     (_v & 0xf)
#define BCUP0_REG0_CSC1_CS6             (0xf << 4)
#define BCUP0_REG0_CSC1_CS6_GET(_v)     ((_v >> 4) & 0xf)
#define BCUP0_REG0_CSC1_CS5             (0xf << 8)
#define BCUP0_REG0_CSC1_CS5_GET(_v)     ((_v >> 8) & 0xf)
#define BCUP0_REG0_CSC1_CS4             (0xf << 12)
#define BCUP0_REG0_CSC1_CS4_GET(_v)     ((_v >> 12) & 0xf)

#define BCUP0_REG0_BPC_POFFSET          0x4
#define BCUP0_REG0_BPC                  (BCUP0 + BCUP0_REG0_POFFSET + BCUP0_REG0_BPC_POFFSET)

#define BCUP0_REG0_BSC_POFFSET          0x6
#define BCUP0_REG0_BSC                  (BCUP0 + BCUP0_REG0_POFFSET + BCUP0_REG0_BSC_POFFSET)
#define BCUP0_REG0_BSC_BS0              0x3
#define BCUP0_REG0_BSC_BS0_GET(_v)      (_v & 0x3)
#define BCUP0_REG0_BSC_BS1              (0x3 << 2)
#define BCUP0_REG0_BSC_BS1_GET(_v)      ((_v >> 2) & 0x3)
#define BCUP0_REG0_BSC_BS2              (0x3 << 4)
#define BCUP0_REG0_BSC_BS2_GET(_v)      ((_v >> 4) & 0x3)
#define BCUP0_REG0_BSC_BS3              (0x3 << 6)
#define BCUP0_REG0_BSC_BS3_GET(_v)      ((_v >> 6) & 0x3)
#define BCUP0_REG0_BSC_BS4              (0x3 << 8)
#define BCUP0_REG0_BSC_BS4_GET(_v)      ((_v >> 8) & 0x3)
#define BCUP0_REG0_BSC_BS5              (0x3 << 10)
#define BCUP0_REG0_BSC_BS5_GET(_v)      ((_v >> 10) & 0x3)
#define BCUP0_REG0_BSC_BS6              (0x3 << 12)
#define BCUP0_REG0_BSC_BS6_GET(_v)      ((_v >> 12) & 0x3)
#define BCUP0_REG0_BSC_BS7              (0x3 << 14)
#define BCUP0_REG0_BSC_BS7_GET(_v)      ((_v >> 14) & 0x3)

#define BCUP0_REG0_BEC_POFFSET          0x8
#define BCUP0_REG0_BEC                  (BCUP0 + BCUP0_REG0_POFFSET + BCUP0_REG0_BEC_POFFSET)
#define BCUP0_REG0_BEC_BE00             0x1
#define BCUP0_REG0_BEC_BE00_GET(_v)     (_v & 0x1)
#define BCUP0_REG0_BEC_BE10             (0x1 << 2)
#define BCUP0_REG0_BEC_BE10_GET(_v)     ((_v >> 2) & 0x1)
#define BCUP0_REG0_BEC_BE20             (0x1 << 4)
#define BCUP0_REG0_BEC_BE20_GET(_v)     ((_v >> 4) & 0x1)
#define BCUP0_REG0_BEC_BE30             (0x1 << 6)
#define BCUP0_REG0_BEC_BE30_GET(_v)     ((_v >> 6) & 0x1)
#define BCUP0_REG0_BEC_BE40             (0x1 << 8)
#define BCUP0_REG0_BEC_BE40_GET(_v)     ((_v >> 8) & 0x1)
#define BCUP0_REG0_BEC_BE50             (0x1 << 10)
#define BCUP0_REG0_BEC_BE50_GET(_v)     ((_v >> 10) & 0x1)
#define BCUP0_REG0_BEC_BE60             (0x1 << 12)
#define BCUP0_REG0_BEC_BE60_GET(_v)     ((_v >> 12) & 0x1)
#define BCUP0_REG0_BEC_BE70             (0x1 << 14)
#define BCUP0_REG0_BEC_BE70_GET(_v)     ((_v >> 14) & 0x1)

#define BCUP0_REG1_POFFSET              0xf
#define BCUP0_REG1_VSWC_POFFSET         0x0
#define BCUP0_REG1_VSWC                 (BCUP0 + BCUP0_REG1_POFFSET + BCUP0_REG1_VSWC_POFFSET)


#endif

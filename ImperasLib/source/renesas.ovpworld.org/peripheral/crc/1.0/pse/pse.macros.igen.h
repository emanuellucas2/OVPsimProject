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

// Set the macro 'CRCP0' to the base of port 'CRCP0'
#ifndef CRCP0
#error CRCP0 is undefined. It needs to be set to the port base address
#endif


#define CRCP0_REG0_POFFSET              0x0
#define CRCP0_REG0_CCRCIN0_POFFSET      0x0
#define CRCP0_REG0_CCRCIN0              (CRCP0 + CRCP0_REG0_POFFSET + CRCP0_REG0_CCRCIN0_POFFSET)

#define CRCP0_REG0_CCRCD0_POFFSET       0x4
#define CRCP0_REG0_CCRCD0               (CRCP0 + CRCP0_REG0_POFFSET + CRCP0_REG0_CCRCD0_POFFSET)

#define CRCP0_REG0_CCRCIN1_POFFSET      0x8
#define CRCP0_REG0_CCRCIN1              (CRCP0 + CRCP0_REG0_POFFSET + CRCP0_REG0_CCRCIN1_POFFSET)

#define CRCP0_REG0_CCRCD1_POFFSET       0xc
#define CRCP0_REG0_CCRCD1               (CRCP0 + CRCP0_REG0_POFFSET + CRCP0_REG0_CCRCD1_POFFSET)

#define CRCP0_REG0_CCRCIN2_POFFSET      0x10
#define CRCP0_REG0_CCRCIN2              (CRCP0 + CRCP0_REG0_POFFSET + CRCP0_REG0_CCRCIN2_POFFSET)

#define CRCP0_REG0_CCRCD2_POFFSET       0x14
#define CRCP0_REG0_CCRCD2               (CRCP0 + CRCP0_REG0_POFFSET + CRCP0_REG0_CCRCD2_POFFSET)

#define CRCP0_REG0_CCRCIN3_POFFSET      0x18
#define CRCP0_REG0_CCRCIN3              (CRCP0 + CRCP0_REG0_POFFSET + CRCP0_REG0_CCRCIN3_POFFSET)

#define CRCP0_REG0_CCRCD3_POFFSET       0x1c
#define CRCP0_REG0_CCRCD3               (CRCP0 + CRCP0_REG0_POFFSET + CRCP0_REG0_CCRCD3_POFFSET)

#define CRCP0_REG0_CCRCIN4_POFFSET      0x20
#define CRCP0_REG0_CCRCIN4              (CRCP0 + CRCP0_REG0_POFFSET + CRCP0_REG0_CCRCIN4_POFFSET)

#define CRCP0_REG0_CCRCD4_POFFSET       0x24
#define CRCP0_REG0_CCRCD4               (CRCP0 + CRCP0_REG0_POFFSET + CRCP0_REG0_CCRCD4_POFFSET)

#define CRCP0_REG0_DCRCIN_POFFSET       0x30
#define CRCP0_REG0_DCRCIN               (CRCP0 + CRCP0_REG0_POFFSET + CRCP0_REG0_DCRCIN_POFFSET)

#define CRCP0_REG0_DCRCD_POFFSET        0x34
#define CRCP0_REG0_DCRCD                (CRCP0 + CRCP0_REG0_POFFSET + CRCP0_REG0_DCRCD_POFFSET)

#define CRCP0_REG0_CRCC_POFFSET         0x40
#define CRCP0_REG0_CRCC                 (CRCP0 + CRCP0_REG0_POFFSET + CRCP0_REG0_CRCC_POFFSET)
#define CRCP0_REG0_CRCC_POL             0x1
#define CRCP0_REG0_CRCC_POL_GET(_v)     (_v & 0x1)
#define CRCP0_REG0_CRCC_ISZ             (0x3 << 1)
#define CRCP0_REG0_CRCC_ISZ_GET(_v)     ((_v >> 1) & 0x3)
#define CRCP0_REG0_CRCC_CRCEN0          (0x1 << 8)
#define CRCP0_REG0_CRCC_CRCEN0_GET(_v)  ((_v >> 8) & 0x1)
#define CRCP0_REG0_CRCC_CRCEN1          (0x1 << 9)
#define CRCP0_REG0_CRCC_CRCEN1_GET(_v)  ((_v >> 9) & 0x1)
#define CRCP0_REG0_CRCC_CRCEN2          (0x1 << 10)
#define CRCP0_REG0_CRCC_CRCEN2_GET(_v)  ((_v >> 10) & 0x1)
#define CRCP0_REG0_CRCC_CRCEN3          (0x1 << 11)
#define CRCP0_REG0_CRCC_CRCEN3_GET(_v)  ((_v >> 11) & 0x1)
#define CRCP0_REG0_CRCC_CRCEN4          (0x1 << 12)
#define CRCP0_REG0_CRCC_CRCEN4_GET(_v)  ((_v >> 12) & 0x1)


#endif

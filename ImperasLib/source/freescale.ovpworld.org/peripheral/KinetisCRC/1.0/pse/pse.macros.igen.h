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
#define BPORT1_AB_CRC_POFFSET           0x0
#define BPORT1_AB_CRC                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CRC_POFFSET)
#define BPORT1_AB_CRC_LL                0xff
#define BPORT1_AB_CRC_LL_GET(_v)        (_v & 0xff)
#define BPORT1_AB_CRC_LU                (0xff << 8)
#define BPORT1_AB_CRC_LU_GET(_v)        ((_v >> 8) & 0xff)
#define BPORT1_AB_CRC_HL                (0xff << 16)
#define BPORT1_AB_CRC_HL_GET(_v)        ((_v >> 16) & 0xff)
#define BPORT1_AB_CRC_HU                (0xff << 24)
#define BPORT1_AB_CRC_HU_GET(_v)        ((_v >> 24) & 0xff)

#define BPORT1_AB_GPOLY_POFFSET         0x4
#define BPORT1_AB_GPOLY                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPOLY_POFFSET)
#define BPORT1_AB_GPOLY_LOW             0xffff
#define BPORT1_AB_GPOLY_LOW_GET(_v)     (_v & 0xffff)
#define BPORT1_AB_GPOLY_HIGH            (0xffff << 16)
#define BPORT1_AB_GPOLY_HIGH_GET(_v)    ((_v >> 16) & 0xffff)

#define BPORT1_AB_CTRL_POFFSET          0x8
#define BPORT1_AB_CTRL                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CTRL_POFFSET)
#define BPORT1_AB_CTRL_TCRC             (0x1 << 24)
#define BPORT1_AB_CTRL_TCRC_GET(_v)     ((_v >> 24) & 0x1)
#define BPORT1_AB_CTRL_WAS              (0x1 << 25)
#define BPORT1_AB_CTRL_WAS_GET(_v)      ((_v >> 25) & 0x1)
#define BPORT1_AB_CTRL_FXOR             (0x1 << 26)
#define BPORT1_AB_CTRL_FXOR_GET(_v)     ((_v >> 26) & 0x1)
#define BPORT1_AB_CTRL_TOTR             (0x3 << 28)
#define BPORT1_AB_CTRL_TOTR_GET(_v)     ((_v >> 28) & 0x3)
#define BPORT1_AB_CTRL_TOT              (0x3 << 30)
#define BPORT1_AB_CTRL_TOT_GET(_v)      ((_v >> 30) & 0x3)


#endif

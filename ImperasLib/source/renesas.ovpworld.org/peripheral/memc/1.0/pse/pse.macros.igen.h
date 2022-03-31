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

// Set the macro 'MEMCP0' to the base of port 'MEMCP0'
#ifndef MEMCP0
#error MEMCP0 is undefined. It needs to be set to the port base address
#endif


#define MEMCP0_REG0_POFFSET             0x0
#define MEMCP0_REG0_BCT0_POFFSET        0x0
#define MEMCP0_REG0_BCT0                (MEMCP0 + MEMCP0_REG0_POFFSET + MEMCP0_REG0_BCT0_POFFSET)
#define MEMCP0_REG0_BCT0_ME0            (0x1 << 3)
#define MEMCP0_REG0_BCT0_ME0_GET(_v)    ((_v >> 3) & 0x1)
#define MEMCP0_REG0_BCT0_ME1            (0x1 << 7)
#define MEMCP0_REG0_BCT0_ME1_GET(_v)    ((_v >> 7) & 0x1)
#define MEMCP0_REG0_BCT0_ME2            (0x1 << 11)
#define MEMCP0_REG0_BCT0_ME2_GET(_v)    ((_v >> 11) & 0x1)
#define MEMCP0_REG0_BCT0_ME3            (0x1 << 15)
#define MEMCP0_REG0_BCT0_ME3_GET(_v)    ((_v >> 15) & 0x1)

#define MEMCP0_REG0_BCT1_POFFSET        0x2
#define MEMCP0_REG0_BCT1                (MEMCP0 + MEMCP0_REG0_POFFSET + MEMCP0_REG0_BCT1_POFFSET)
#define MEMCP0_REG0_BCT1_ME4            (0x1 << 3)
#define MEMCP0_REG0_BCT1_ME4_GET(_v)    ((_v >> 3) & 0x1)
#define MEMCP0_REG0_BCT1_ME5            (0x1 << 7)
#define MEMCP0_REG0_BCT1_ME5_GET(_v)    ((_v >> 7) & 0x1)
#define MEMCP0_REG0_BCT1_ME6            (0x1 << 11)
#define MEMCP0_REG0_BCT1_ME6_GET(_v)    ((_v >> 11) & 0x1)
#define MEMCP0_REG0_BCT1_ME7            (0x1 << 15)
#define MEMCP0_REG0_BCT1_ME7_GET(_v)    ((_v >> 15) & 0x1)

#define MEMCP0_REG0_DWC0_POFFSET        0x4
#define MEMCP0_REG0_DWC0                (MEMCP0 + MEMCP0_REG0_POFFSET + MEMCP0_REG0_DWC0_POFFSET)
#define MEMCP0_REG0_DWC0_DW0            0x7
#define MEMCP0_REG0_DWC0_DW0_GET(_v)    (_v & 0x7)
#define MEMCP0_REG0_DWC0_DW1            (0x7 << 4)
#define MEMCP0_REG0_DWC0_DW1_GET(_v)    ((_v >> 4) & 0x7)
#define MEMCP0_REG0_DWC0_DW2            (0x7 << 8)
#define MEMCP0_REG0_DWC0_DW2_GET(_v)    ((_v >> 8) & 0x7)
#define MEMCP0_REG0_DWC0_DW3            (0x7 << 12)
#define MEMCP0_REG0_DWC0_DW3_GET(_v)    ((_v >> 12) & 0x7)

#define MEMCP0_REG0_DWC1_POFFSET        0x6
#define MEMCP0_REG0_DWC1                (MEMCP0 + MEMCP0_REG0_POFFSET + MEMCP0_REG0_DWC1_POFFSET)
#define MEMCP0_REG0_DWC1_DW4            0x7
#define MEMCP0_REG0_DWC1_DW4_GET(_v)    (_v & 0x7)
#define MEMCP0_REG0_DWC1_DW5            (0x7 << 4)
#define MEMCP0_REG0_DWC1_DW5_GET(_v)    ((_v >> 4) & 0x7)
#define MEMCP0_REG0_DWC1_DW6            (0x7 << 8)
#define MEMCP0_REG0_DWC1_DW6_GET(_v)    ((_v >> 8) & 0x7)
#define MEMCP0_REG0_DWC1_DW7            (0x7 << 12)
#define MEMCP0_REG0_DWC1_DW7_GET(_v)    ((_v >> 12) & 0x7)

#define MEMCP0_REG0_AWC_POFFSET         0x8
#define MEMCP0_REG0_AWC                 (MEMCP0 + MEMCP0_REG0_POFFSET + MEMCP0_REG0_AWC_POFFSET)
#define MEMCP0_REG0_AWC_ASW0            0x1
#define MEMCP0_REG0_AWC_ASW0_GET(_v)    (_v & 0x1)
#define MEMCP0_REG0_AWC_AHW0            (0x1 << 1)
#define MEMCP0_REG0_AWC_AHW0_GET(_v)    ((_v >> 1) & 0x1)
#define MEMCP0_REG0_AWC_ASW1            (0x1 << 2)
#define MEMCP0_REG0_AWC_ASW1_GET(_v)    ((_v >> 2) & 0x1)
#define MEMCP0_REG0_AWC_AHW1            (0x1 << 3)
#define MEMCP0_REG0_AWC_AHW1_GET(_v)    ((_v >> 3) & 0x1)
#define MEMCP0_REG0_AWC_ASW2            (0x1 << 4)
#define MEMCP0_REG0_AWC_ASW2_GET(_v)    ((_v >> 4) & 0x1)
#define MEMCP0_REG0_AWC_AHW2            (0x1 << 5)
#define MEMCP0_REG0_AWC_AHW2_GET(_v)    ((_v >> 5) & 0x1)
#define MEMCP0_REG0_AWC_ASW3            (0x1 << 6)
#define MEMCP0_REG0_AWC_ASW3_GET(_v)    ((_v >> 6) & 0x1)
#define MEMCP0_REG0_AWC_AHW3            (0x1 << 7)
#define MEMCP0_REG0_AWC_AHW3_GET(_v)    ((_v >> 7) & 0x1)
#define MEMCP0_REG0_AWC_ASW4            (0x1 << 8)
#define MEMCP0_REG0_AWC_ASW4_GET(_v)    ((_v >> 8) & 0x1)
#define MEMCP0_REG0_AWC_AHW4            (0x1 << 9)
#define MEMCP0_REG0_AWC_AHW4_GET(_v)    ((_v >> 9) & 0x1)
#define MEMCP0_REG0_AWC_ASW5            (0x1 << 10)
#define MEMCP0_REG0_AWC_ASW5_GET(_v)    ((_v >> 10) & 0x1)
#define MEMCP0_REG0_AWC_AHW5            (0x1 << 11)
#define MEMCP0_REG0_AWC_AHW5_GET(_v)    ((_v >> 11) & 0x1)
#define MEMCP0_REG0_AWC_ASW6            (0x1 << 12)
#define MEMCP0_REG0_AWC_ASW6_GET(_v)    ((_v >> 12) & 0x1)
#define MEMCP0_REG0_AWC_AHW6            (0x1 << 13)
#define MEMCP0_REG0_AWC_AHW6_GET(_v)    ((_v >> 13) & 0x1)
#define MEMCP0_REG0_AWC_ASW7            (0x1 << 14)
#define MEMCP0_REG0_AWC_ASW7_GET(_v)    ((_v >> 14) & 0x1)
#define MEMCP0_REG0_AWC_AHW7            (0x1 << 15)
#define MEMCP0_REG0_AWC_AHW7_GET(_v)    ((_v >> 15) & 0x1)

#define MEMCP0_REG0_BCC_POFFSET         0xa
#define MEMCP0_REG0_BCC                 (MEMCP0 + MEMCP0_REG0_POFFSET + MEMCP0_REG0_BCC_POFFSET)
#define MEMCP0_REG0_BCC_BC01            (0x1 << 1)
#define MEMCP0_REG0_BCC_BC01_GET(_v)    ((_v >> 1) & 0x1)
#define MEMCP0_REG0_BCC_BC11            (0x1 << 3)
#define MEMCP0_REG0_BCC_BC11_GET(_v)    ((_v >> 3) & 0x1)
#define MEMCP0_REG0_BCC_BC21            (0x1 << 5)
#define MEMCP0_REG0_BCC_BC21_GET(_v)    ((_v >> 5) & 0x1)
#define MEMCP0_REG0_BCC_BC31            (0x1 << 7)
#define MEMCP0_REG0_BCC_BC31_GET(_v)    ((_v >> 7) & 0x1)
#define MEMCP0_REG0_BCC_BC41            (0x1 << 9)
#define MEMCP0_REG0_BCC_BC41_GET(_v)    ((_v >> 9) & 0x1)
#define MEMCP0_REG0_BCC_BC51            (0x1 << 11)
#define MEMCP0_REG0_BCC_BC51_GET(_v)    ((_v >> 11) & 0x1)
#define MEMCP0_REG0_BCC_BC61            (0x1 << 13)
#define MEMCP0_REG0_BCC_BC61_GET(_v)    ((_v >> 13) & 0x1)
#define MEMCP0_REG0_BCC_BC71            (0x1 << 15)
#define MEMCP0_REG0_BCC_BC71_GET(_v)    ((_v >> 15) & 0x1)

#define MEMCP0_REG1_POFFSET             0xf
#define MEMCP0_REG1_DVC_POFFSET         0x0
#define MEMCP0_REG1_DVC                 (MEMCP0 + MEMCP0_REG1_POFFSET + MEMCP0_REG1_DVC_POFFSET)


#endif

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

// Set the macro 'BP1' to the base of port 'bp1'
#ifndef BP1
#error BP1 is undefined. It needs to be set to the port base address
#endif


#define BP1_REG_POFFSET                 0x0
#define BP1_REG_PS_CR_POFFSET           0x0
#define BP1_REG_PS_CR                   (BP1 + BP1_REG_POFFSET + BP1_REG_PS_CR_POFFSET)
#define BP1_REG_PS_CR_CPU               0x1
#define BP1_REG_PS_CR_CPU_GET(_v)       (_v & 0x1)

#define BP1_REG_PS_PCER_POFFSET         0x4
#define BP1_REG_PS_PCER                 (BP1 + BP1_REG_POFFSET + BP1_REG_PS_PCER_POFFSET)
#define BP1_REG_PS_PCER_PIO             (0x1 << 8)
#define BP1_REG_PS_PCER_PIO_GET(_v)     ((_v >> 8) & 0x1)
#define BP1_REG_PS_PCER_TC2             (0x1 << 6)
#define BP1_REG_PS_PCER_TC2_GET(_v)     ((_v >> 6) & 0x1)
#define BP1_REG_PS_PCER_TC1             (0x1 << 5)
#define BP1_REG_PS_PCER_TC1_GET(_v)     ((_v >> 5) & 0x1)
#define BP1_REG_PS_PCER_TC0             (0x1 << 4)
#define BP1_REG_PS_PCER_TC0_GET(_v)     ((_v >> 4) & 0x1)
#define BP1_REG_PS_PCER_US1             (0x1 << 3)
#define BP1_REG_PS_PCER_US1_GET(_v)     ((_v >> 3) & 0x1)
#define BP1_REG_PS_PCER_US0             (0x1 << 2)
#define BP1_REG_PS_PCER_US0_GET(_v)     ((_v >> 2) & 0x1)

#define BP1_REG_PS_PCDR_POFFSET         0x8
#define BP1_REG_PS_PCDR                 (BP1 + BP1_REG_POFFSET + BP1_REG_PS_PCDR_POFFSET)
#define BP1_REG_PS_PCDR_PIO             (0x1 << 8)
#define BP1_REG_PS_PCDR_PIO_GET(_v)     ((_v >> 8) & 0x1)
#define BP1_REG_PS_PCDR_TC2             (0x1 << 6)
#define BP1_REG_PS_PCDR_TC2_GET(_v)     ((_v >> 6) & 0x1)
#define BP1_REG_PS_PCDR_TC1             (0x1 << 5)
#define BP1_REG_PS_PCDR_TC1_GET(_v)     ((_v >> 5) & 0x1)
#define BP1_REG_PS_PCDR_TC0             (0x1 << 4)
#define BP1_REG_PS_PCDR_TC0_GET(_v)     ((_v >> 4) & 0x1)
#define BP1_REG_PS_PCDR_US1             (0x1 << 3)
#define BP1_REG_PS_PCDR_US1_GET(_v)     ((_v >> 3) & 0x1)
#define BP1_REG_PS_PCDR_US0             (0x1 << 2)
#define BP1_REG_PS_PCDR_US0_GET(_v)     ((_v >> 2) & 0x1)

#define BP1_REG_PS_PCSR_POFFSET         0xc
#define BP1_REG_PS_PCSR                 (BP1 + BP1_REG_POFFSET + BP1_REG_PS_PCSR_POFFSET)
#define BP1_REG_PS_PCSR_PIO             (0x1 << 8)
#define BP1_REG_PS_PCSR_PIO_GET(_v)     ((_v >> 8) & 0x1)
#define BP1_REG_PS_PCSR_TC2             (0x1 << 6)
#define BP1_REG_PS_PCSR_TC2_GET(_v)     ((_v >> 6) & 0x1)
#define BP1_REG_PS_PCSR_TC1             (0x1 << 5)
#define BP1_REG_PS_PCSR_TC1_GET(_v)     ((_v >> 5) & 0x1)
#define BP1_REG_PS_PCSR_TC0             (0x1 << 4)
#define BP1_REG_PS_PCSR_TC0_GET(_v)     ((_v >> 4) & 0x1)
#define BP1_REG_PS_PCSR_US1             (0x1 << 3)
#define BP1_REG_PS_PCSR_US1_GET(_v)     ((_v >> 3) & 0x1)
#define BP1_REG_PS_PCSR_US0             (0x1 << 2)
#define BP1_REG_PS_PCSR_US0_GET(_v)     ((_v >> 2) & 0x1)


#endif

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

// Set the macro 'SP' to the base of port 'sp'
#ifndef SP
#error SP is undefined. It needs to be set to the port base address
#endif


#define SP_AB_POFFSET                   0x0
#define SP_AB_TCSR0_POFFSET             0x0
#define SP_AB_TCSR0                     (SP + SP_AB_POFFSET + SP_AB_TCSR0_POFFSET)
#define SP_AB_TCSR0_MDT0                0x1
#define SP_AB_TCSR0_MDT0_GET(_v)        (_v & 0x1)
#define SP_AB_TCSR0_UDT0                (0x1 << 1)
#define SP_AB_TCSR0_UDT0_GET(_v)        ((_v >> 1) & 0x1)
#define SP_AB_TCSR0_GENT0               (0x1 << 2)
#define SP_AB_TCSR0_GENT0_GET(_v)       ((_v >> 2) & 0x1)
#define SP_AB_TCSR0_CAPT0               (0x1 << 3)
#define SP_AB_TCSR0_CAPT0_GET(_v)       ((_v >> 3) & 0x1)
#define SP_AB_TCSR0_ARHT0               (0x1 << 4)
#define SP_AB_TCSR0_ARHT0_GET(_v)       ((_v >> 4) & 0x1)
#define SP_AB_TCSR0_LOAD0               (0x1 << 5)
#define SP_AB_TCSR0_LOAD0_GET(_v)       ((_v >> 5) & 0x1)
#define SP_AB_TCSR0_ENIT0               (0x1 << 6)
#define SP_AB_TCSR0_ENIT0_GET(_v)       ((_v >> 6) & 0x1)
#define SP_AB_TCSR0_ENT0                (0x1 << 7)
#define SP_AB_TCSR0_ENT0_GET(_v)        ((_v >> 7) & 0x1)
#define SP_AB_TCSR0_T0INT               (0x1 << 8)
#define SP_AB_TCSR0_T0INT_GET(_v)       ((_v >> 8) & 0x1)
#define SP_AB_TCSR0_PWMA0               (0x1 << 9)
#define SP_AB_TCSR0_PWMA0_GET(_v)       ((_v >> 9) & 0x1)
#define SP_AB_TCSR0_ENALL0              (0x1 << 10)
#define SP_AB_TCSR0_ENALL0_GET(_v)      ((_v >> 10) & 0x1)
#define SP_AB_TCSR0_CASC0               (0x1 << 11)
#define SP_AB_TCSR0_CASC0_GET(_v)       ((_v >> 11) & 0x1)

#define SP_AB_TLR0_POFFSET              0x4
#define SP_AB_TLR0                      (SP + SP_AB_POFFSET + SP_AB_TLR0_POFFSET)

#define SP_AB_TCR0_POFFSET              0x8
#define SP_AB_TCR0                      (SP + SP_AB_POFFSET + SP_AB_TCR0_POFFSET)

#define SP_AB_TCSR1_POFFSET             0x10
#define SP_AB_TCSR1                     (SP + SP_AB_POFFSET + SP_AB_TCSR1_POFFSET)
#define SP_AB_TCSR1_MDT1                0x1
#define SP_AB_TCSR1_MDT1_GET(_v)        (_v & 0x1)
#define SP_AB_TCSR1_UDT1                (0x1 << 1)
#define SP_AB_TCSR1_UDT1_GET(_v)        ((_v >> 1) & 0x1)
#define SP_AB_TCSR1_GENT1               (0x1 << 2)
#define SP_AB_TCSR1_GENT1_GET(_v)       ((_v >> 2) & 0x1)
#define SP_AB_TCSR1_CAPT1               (0x1 << 3)
#define SP_AB_TCSR1_CAPT1_GET(_v)       ((_v >> 3) & 0x1)
#define SP_AB_TCSR1_ARHT1               (0x1 << 4)
#define SP_AB_TCSR1_ARHT1_GET(_v)       ((_v >> 4) & 0x1)
#define SP_AB_TCSR1_LOAD1               (0x1 << 5)
#define SP_AB_TCSR1_LOAD1_GET(_v)       ((_v >> 5) & 0x1)
#define SP_AB_TCSR1_ENIT1               (0x1 << 6)
#define SP_AB_TCSR1_ENIT1_GET(_v)       ((_v >> 6) & 0x1)
#define SP_AB_TCSR1_ENT1                (0x1 << 7)
#define SP_AB_TCSR1_ENT1_GET(_v)        ((_v >> 7) & 0x1)
#define SP_AB_TCSR1_T1INT               (0x1 << 8)
#define SP_AB_TCSR1_T1INT_GET(_v)       ((_v >> 8) & 0x1)
#define SP_AB_TCSR1_PWMA1               (0x1 << 9)
#define SP_AB_TCSR1_PWMA1_GET(_v)       ((_v >> 9) & 0x1)
#define SP_AB_TCSR1_ENALL1              (0x1 << 10)
#define SP_AB_TCSR1_ENALL1_GET(_v)      ((_v >> 10) & 0x1)

#define SP_AB_TLR1_POFFSET              0x14
#define SP_AB_TLR1                      (SP + SP_AB_POFFSET + SP_AB_TLR1_POFFSET)

#define SP_AB_TCR1_POFFSET              0x18
#define SP_AB_TCR1                      (SP + SP_AB_POFFSET + SP_AB_TCR1_POFFSET)

#define SP_AB_RESERVED0_POFFSET         0xc
#define SP_AB_RESERVED0                 (SP + SP_AB_POFFSET + SP_AB_RESERVED0_POFFSET)
#define SP_AB_RESERVED0_BYTES           0x4

#define SP_AB_RESERVED1_POFFSET         0x1c
#define SP_AB_RESERVED1                 (SP + SP_AB_POFFSET + SP_AB_RESERVED1_POFFSET)
#define SP_AB_RESERVED1_BYTES           0x4


#endif

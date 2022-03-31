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
#define BPORT1_AB_LOAD0_POFFSET         0x0
#define BPORT1_AB_LOAD0                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LOAD0_POFFSET)

#define BPORT1_AB_LIMIT0_POFFSET        0x4
#define BPORT1_AB_LIMIT0                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LIMIT0_POFFSET)

#define BPORT1_AB_CONTROL0_POFFSET      0x8
#define BPORT1_AB_CONTROL0              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CONTROL0_POFFSET)
#define BPORT1_AB_CONTROL0_ONESHOT      0x1
#define BPORT1_AB_CONTROL0_ONESHOT_GET(_v)  (_v & 0x1)
#define BPORT1_AB_CONTROL0_M32BIT       (0x1 << 1)
#define BPORT1_AB_CONTROL0_M32BIT_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_CONTROL0_DIV          (0x3 << 2)
#define BPORT1_AB_CONTROL0_DIV_GET(_v)  ((_v >> 2) & 0x3)
#define BPORT1_AB_CONTROL0_IE           (0x1 << 5)
#define BPORT1_AB_CONTROL0_IE_GET(_v)   ((_v >> 5) & 0x1)
#define BPORT1_AB_CONTROL0_PERIODIC     (0x1 << 6)
#define BPORT1_AB_CONTROL0_PERIODIC_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_CONTROL0_ENABLE       (0x1 << 7)
#define BPORT1_AB_CONTROL0_ENABLE_GET(_v)  ((_v >> 7) & 0x1)

#define BPORT1_AB_INTCLR0_POFFSET       0xc
#define BPORT1_AB_INTCLR0               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INTCLR0_POFFSET)

#define BPORT1_AB_INTLEVEL0_POFFSET     0x10
#define BPORT1_AB_INTLEVEL0             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INTLEVEL0_POFFSET)

#define BPORT1_AB_MIS0_POFFSET          0x14
#define BPORT1_AB_MIS0                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIS0_POFFSET)

#define BPORT1_AB_BGLOAD0_POFFSET       0x18
#define BPORT1_AB_BGLOAD0               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BGLOAD0_POFFSET)

#define BPORT1_AB_LOAD1_POFFSET         0x100
#define BPORT1_AB_LOAD1                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LOAD1_POFFSET)

#define BPORT1_AB_LIMIT1_POFFSET        0x104
#define BPORT1_AB_LIMIT1                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LIMIT1_POFFSET)

#define BPORT1_AB_CONTROL1_POFFSET      0x108
#define BPORT1_AB_CONTROL1              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CONTROL1_POFFSET)
#define BPORT1_AB_CONTROL1_ONESHOT      0x1
#define BPORT1_AB_CONTROL1_ONESHOT_GET(_v)  (_v & 0x1)
#define BPORT1_AB_CONTROL1_M32BIT       (0x1 << 1)
#define BPORT1_AB_CONTROL1_M32BIT_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_CONTROL1_DIV          (0x3 << 2)
#define BPORT1_AB_CONTROL1_DIV_GET(_v)  ((_v >> 2) & 0x3)
#define BPORT1_AB_CONTROL1_IE           (0x1 << 5)
#define BPORT1_AB_CONTROL1_IE_GET(_v)   ((_v >> 5) & 0x1)
#define BPORT1_AB_CONTROL1_PERIODIC     (0x1 << 6)
#define BPORT1_AB_CONTROL1_PERIODIC_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_CONTROL1_ENABLE       (0x1 << 7)
#define BPORT1_AB_CONTROL1_ENABLE_GET(_v)  ((_v >> 7) & 0x1)

#define BPORT1_AB_INTCLR1_POFFSET       0x10c
#define BPORT1_AB_INTCLR1               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INTCLR1_POFFSET)

#define BPORT1_AB_INTLEVEL1_POFFSET     0x110
#define BPORT1_AB_INTLEVEL1             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INTLEVEL1_POFFSET)

#define BPORT1_AB_MIS1_POFFSET          0x114
#define BPORT1_AB_MIS1                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIS1_POFFSET)

#define BPORT1_AB_BGLOAD1_POFFSET       0x118
#define BPORT1_AB_BGLOAD1               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BGLOAD1_POFFSET)

#define BPORT1_AB_LOAD2_POFFSET         0x200
#define BPORT1_AB_LOAD2                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LOAD2_POFFSET)

#define BPORT1_AB_LIMIT2_POFFSET        0x204
#define BPORT1_AB_LIMIT2                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LIMIT2_POFFSET)

#define BPORT1_AB_CONTROL2_POFFSET      0x208
#define BPORT1_AB_CONTROL2              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CONTROL2_POFFSET)
#define BPORT1_AB_CONTROL2_ONESHOT      0x1
#define BPORT1_AB_CONTROL2_ONESHOT_GET(_v)  (_v & 0x1)
#define BPORT1_AB_CONTROL2_M32BIT       (0x1 << 1)
#define BPORT1_AB_CONTROL2_M32BIT_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_CONTROL2_DIV          (0x3 << 2)
#define BPORT1_AB_CONTROL2_DIV_GET(_v)  ((_v >> 2) & 0x3)
#define BPORT1_AB_CONTROL2_IE           (0x1 << 5)
#define BPORT1_AB_CONTROL2_IE_GET(_v)   ((_v >> 5) & 0x1)
#define BPORT1_AB_CONTROL2_PERIODIC     (0x1 << 6)
#define BPORT1_AB_CONTROL2_PERIODIC_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_CONTROL2_ENABLE       (0x1 << 7)
#define BPORT1_AB_CONTROL2_ENABLE_GET(_v)  ((_v >> 7) & 0x1)

#define BPORT1_AB_INTCLR2_POFFSET       0x20c
#define BPORT1_AB_INTCLR2               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INTCLR2_POFFSET)

#define BPORT1_AB_INTLEVEL2_POFFSET     0x210
#define BPORT1_AB_INTLEVEL2             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INTLEVEL2_POFFSET)

#define BPORT1_AB_MIS2_POFFSET          0x214
#define BPORT1_AB_MIS2                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIS2_POFFSET)

#define BPORT1_AB_BGLOAD2_POFFSET       0x218
#define BPORT1_AB_BGLOAD2               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BGLOAD2_POFFSET)


#endif

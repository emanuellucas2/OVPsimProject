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
#define BPORT1_AB_T0LOAD_POFFSET        0x0
#define BPORT1_AB_T0LOAD                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_T0LOAD_POFFSET)

#define BPORT1_AB_T0VALUE_POFFSET       0x4
#define BPORT1_AB_T0VALUE               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_T0VALUE_POFFSET)

#define BPORT1_AB_T0CONTROL_POFFSET     0x8
#define BPORT1_AB_T0CONTROL             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_T0CONTROL_POFFSET)
#define BPORT1_AB_T0CONTROL_ONESHOT     0x1
#define BPORT1_AB_T0CONTROL_ONESHOT_GET(_v)  (_v & 0x1)
#define BPORT1_AB_T0CONTROL_M32BIT      (0x1 << 1)
#define BPORT1_AB_T0CONTROL_M32BIT_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_T0CONTROL_DIV         (0x3 << 2)
#define BPORT1_AB_T0CONTROL_DIV_GET(_v)  ((_v >> 2) & 0x3)
#define BPORT1_AB_T0CONTROL_IE          (0x1 << 5)
#define BPORT1_AB_T0CONTROL_IE_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_T0CONTROL_PERIODIC    (0x1 << 6)
#define BPORT1_AB_T0CONTROL_PERIODIC_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_T0CONTROL_ENABLE      (0x1 << 7)
#define BPORT1_AB_T0CONTROL_ENABLE_GET(_v)  ((_v >> 7) & 0x1)

#define BPORT1_AB_T0INTCLR_POFFSET      0xc
#define BPORT1_AB_T0INTCLR              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_T0INTCLR_POFFSET)

#define BPORT1_AB_T0RIS_POFFSET         0x10
#define BPORT1_AB_T0RIS                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_T0RIS_POFFSET)

#define BPORT1_AB_T0MIS_POFFSET         0x14
#define BPORT1_AB_T0MIS                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_T0MIS_POFFSET)

#define BPORT1_AB_T0BGLOAD_POFFSET      0x18
#define BPORT1_AB_T0BGLOAD              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_T0BGLOAD_POFFSET)

#define BPORT1_AB_T1LOAD_POFFSET        0x20
#define BPORT1_AB_T1LOAD                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_T1LOAD_POFFSET)

#define BPORT1_AB_T1VALUE_POFFSET       0x24
#define BPORT1_AB_T1VALUE               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_T1VALUE_POFFSET)

#define BPORT1_AB_T1CONTROL_POFFSET     0x28
#define BPORT1_AB_T1CONTROL             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_T1CONTROL_POFFSET)
#define BPORT1_AB_T1CONTROL_ONESHOT     0x1
#define BPORT1_AB_T1CONTROL_ONESHOT_GET(_v)  (_v & 0x1)
#define BPORT1_AB_T1CONTROL_M32BIT      (0x1 << 1)
#define BPORT1_AB_T1CONTROL_M32BIT_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_T1CONTROL_DIV         (0x3 << 2)
#define BPORT1_AB_T1CONTROL_DIV_GET(_v)  ((_v >> 2) & 0x3)
#define BPORT1_AB_T1CONTROL_IE          (0x1 << 5)
#define BPORT1_AB_T1CONTROL_IE_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_T1CONTROL_PERIODIC    (0x1 << 6)
#define BPORT1_AB_T1CONTROL_PERIODIC_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_T1CONTROL_ENABLE      (0x1 << 7)
#define BPORT1_AB_T1CONTROL_ENABLE_GET(_v)  ((_v >> 7) & 0x1)

#define BPORT1_AB_T1INTCLR_POFFSET      0x2c
#define BPORT1_AB_T1INTCLR              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_T1INTCLR_POFFSET)

#define BPORT1_AB_T1RIS_POFFSET         0x30
#define BPORT1_AB_T1RIS                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_T1RIS_POFFSET)

#define BPORT1_AB_T1MIS_POFFSET         0x34
#define BPORT1_AB_T1MIS                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_T1MIS_POFFSET)

#define BPORT1_AB_T1BGLOAD_POFFSET      0x38
#define BPORT1_AB_T1BGLOAD              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_T1BGLOAD_POFFSET)

#define BPORT1_AB_ITCR_POFFSET          0xf00
#define BPORT1_AB_ITCR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ITCR_POFFSET)

#define BPORT1_AB_ITOP_POFFSET          0xf04
#define BPORT1_AB_ITOP                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ITOP_POFFSET)

#define BPORT1_AB_PERIPHID0_POFFSET     0xfe0
#define BPORT1_AB_PERIPHID0             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PERIPHID0_POFFSET)

#define BPORT1_AB_PERIPHID1_POFFSET     0xfe4
#define BPORT1_AB_PERIPHID1             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PERIPHID1_POFFSET)

#define BPORT1_AB_PERIPHID2_POFFSET     0xfe8
#define BPORT1_AB_PERIPHID2             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PERIPHID2_POFFSET)

#define BPORT1_AB_PERIPHID3_POFFSET     0xfec
#define BPORT1_AB_PERIPHID3             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PERIPHID3_POFFSET)

#define BPORT1_AB_PCELLID0_POFFSET      0xff0
#define BPORT1_AB_PCELLID0              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PCELLID0_POFFSET)

#define BPORT1_AB_PCELLID1_POFFSET      0xff4
#define BPORT1_AB_PCELLID1              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PCELLID1_POFFSET)

#define BPORT1_AB_PCELLID2_POFFSET      0xff8
#define BPORT1_AB_PCELLID2              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PCELLID2_POFFSET)

#define BPORT1_AB_PCELLID3_POFFSET      0xffc
#define BPORT1_AB_PCELLID3              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PCELLID3_POFFSET)


#endif

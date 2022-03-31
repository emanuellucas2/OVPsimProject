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
#define BPORT1_AB_TIMING0_POFFSET       0x0
#define BPORT1_AB_TIMING0               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TIMING0_POFFSET)

#define BPORT1_AB_TIMING1_POFFSET       0x4
#define BPORT1_AB_TIMING1               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TIMING1_POFFSET)

#define BPORT1_AB_TIMING2_POFFSET       0x8
#define BPORT1_AB_TIMING2               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TIMING2_POFFSET)

#define BPORT1_AB_TIMING3_POFFSET       0xc
#define BPORT1_AB_TIMING3               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TIMING3_POFFSET)

#define BPORT1_AB_UPBASE_POFFSET        0x10
#define BPORT1_AB_UPBASE                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UPBASE_POFFSET)

#define BPORT1_AB_LPBASE_POFFSET        0x14
#define BPORT1_AB_LPBASE                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LPBASE_POFFSET)

#define BPORT1_AB_IMSC_POFFSET          0x18
#define BPORT1_AB_IMSC                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IMSC_POFFSET)

#define BPORT1_AB_CONTROL_POFFSET       0x1c
#define BPORT1_AB_CONTROL               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CONTROL_POFFSET)
#define BPORT1_AB_CONTROL_EN            0x1
#define BPORT1_AB_CONTROL_EN_GET(_v)    (_v & 0x1)
#define BPORT1_AB_CONTROL_BGR           (0x1 << 8)
#define BPORT1_AB_CONTROL_BGR_GET(_v)   ((_v >> 8) & 0x1)
#define BPORT1_AB_CONTROL_BEBO          (0x1 << 9)
#define BPORT1_AB_CONTROL_BEBO_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_CONTROL_BEPO          (0x1 << 10)
#define BPORT1_AB_CONTROL_BEPO_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_CONTROL_PWR           (0x1 << 11)
#define BPORT1_AB_CONTROL_PWR_GET(_v)   ((_v >> 11) & 0x1)

#define BPORT1_AB_INT_STATUS_POFFSET    0x20
#define BPORT1_AB_INT_STATUS            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INT_STATUS_POFFSET)

#define BPORT1_AB_INT_MIS_POFFSET       0x24
#define BPORT1_AB_INT_MIS               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INT_MIS_POFFSET)

#define BPORT1_AB_INT_CLR_POFFSET       0x28
#define BPORT1_AB_INT_CLR               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INT_CLR_POFFSET)

#define BPORT1_AB_UPBASE2_POFFSET       0x2c
#define BPORT1_AB_UPBASE2               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UPBASE2_POFFSET)

#define BPORT1_AB_LPBASE2_POFFSET       0x30
#define BPORT1_AB_LPBASE2               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LPBASE2_POFFSET)

#define BPORT1_AB_ID_POFFSET            0xfe0
#define BPORT1_AB_ID(_MMR_INDEX)        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ID_POFFSET + ((_MMR_INDEX) * 0x4))


#endif

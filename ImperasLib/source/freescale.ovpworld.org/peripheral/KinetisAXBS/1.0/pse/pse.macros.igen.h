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
#define BPORT1_AB_PRS_POFFSET           0x0
#define BPORT1_AB_PRS(_AB_INDEX)        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PRS_POFFSET + ((_AB_INDEX) * 0x100))

#define BPORT1_AB_CRS_POFFSET           0x10
#define BPORT1_AB_CRS(_AB_INDEX)        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CRS_POFFSET + ((_AB_INDEX) * 0x100))

#define BPORT1_AC_POFFSET               0x800
#define BPORT1_AC_MGPCR0_POFFSET        0x0
#define BPORT1_AC_MGPCR0                (BPORT1 + BPORT1_AC_POFFSET + BPORT1_AC_MGPCR0_POFFSET)
#define BPORT1_AC_MGPCR0_AULB           0x7
#define BPORT1_AC_MGPCR0_AULB_GET(_v)   (_v & 0x7)

#define BPORT1_AC_MGPCR1_POFFSET        0x100
#define BPORT1_AC_MGPCR1                (BPORT1 + BPORT1_AC_POFFSET + BPORT1_AC_MGPCR1_POFFSET)
#define BPORT1_AC_MGPCR1_AULB           0x7
#define BPORT1_AC_MGPCR1_AULB_GET(_v)   (_v & 0x7)

#define BPORT1_AC_MGPCR2_POFFSET        0x200
#define BPORT1_AC_MGPCR2                (BPORT1 + BPORT1_AC_POFFSET + BPORT1_AC_MGPCR2_POFFSET)
#define BPORT1_AC_MGPCR2_AULB           0x7
#define BPORT1_AC_MGPCR2_AULB_GET(_v)   (_v & 0x7)

#define BPORT1_AC_MGPCR3_POFFSET        0x300
#define BPORT1_AC_MGPCR3                (BPORT1 + BPORT1_AC_POFFSET + BPORT1_AC_MGPCR3_POFFSET)
#define BPORT1_AC_MGPCR3_AULB           0x7
#define BPORT1_AC_MGPCR3_AULB_GET(_v)   (_v & 0x7)

#define BPORT1_AC_MGPCR6_POFFSET        0x600
#define BPORT1_AC_MGPCR6                (BPORT1 + BPORT1_AC_POFFSET + BPORT1_AC_MGPCR6_POFFSET)
#define BPORT1_AC_MGPCR6_AULB           0x7
#define BPORT1_AC_MGPCR6_AULB_GET(_v)   (_v & 0x7)

#define BPORT1_AC_MGPCR7_POFFSET        0x700
#define BPORT1_AC_MGPCR7                (BPORT1 + BPORT1_AC_POFFSET + BPORT1_AC_MGPCR7_POFFSET)
#define BPORT1_AC_MGPCR7_AULB           0x7
#define BPORT1_AC_MGPCR7_AULB_GET(_v)   (_v & 0x7)


#endif

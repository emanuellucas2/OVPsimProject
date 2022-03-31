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
#define BPORT1_AB_DR_POFFSET            0x0
#define BPORT1_AB_DR                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DR_POFFSET)

#define BPORT1_AB_MR_POFFSET            0x4
#define BPORT1_AB_MR                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MR_POFFSET)

#define BPORT1_AB_LR_POFFSET            0x8
#define BPORT1_AB_LR                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LR_POFFSET)

#define BPORT1_AB_CR_POFFSET            0xc
#define BPORT1_AB_CR                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR_POFFSET)

#define BPORT1_AB_IM_POFFSET            0x10
#define BPORT1_AB_IM                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IM_POFFSET)

#define BPORT1_AB_IS_POFFSET            0x14
#define BPORT1_AB_IS                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IS_POFFSET)

#define BPORT1_AB_MIS_POFFSET           0x18
#define BPORT1_AB_MIS                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MIS_POFFSET)

#define BPORT1_AB_ICR_POFFSET           0x1c
#define BPORT1_AB_ICR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ICR_POFFSET)

#define BPORT1_AB_ID_POFFSET            0xfe0
#define BPORT1_AB_ID(_MMR_INDEX)        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ID_POFFSET + ((_MMR_INDEX) * 0x4))


#endif

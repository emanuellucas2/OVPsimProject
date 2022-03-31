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
#define BPORT1_AB_ISR_POFFSET           0x0
#define BPORT1_AB_ISR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ISR_POFFSET)

#define BPORT1_AB_IPR_POFFSET           0x4
#define BPORT1_AB_IPR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IPR_POFFSET)

#define BPORT1_AB_IER_POFFSET           0x8
#define BPORT1_AB_IER                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IER_POFFSET)

#define BPORT1_AB_IAR_POFFSET           0xc
#define BPORT1_AB_IAR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IAR_POFFSET)

#define BPORT1_AB_SIE_POFFSET           0x10
#define BPORT1_AB_SIE                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SIE_POFFSET)

#define BPORT1_AB_CIE_POFFSET           0x14
#define BPORT1_AB_CIE                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CIE_POFFSET)

#define BPORT1_AB_IVR_POFFSET           0x18
#define BPORT1_AB_IVR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IVR_POFFSET)

#define BPORT1_AB_MER_POFFSET           0x1c
#define BPORT1_AB_MER                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MER_POFFSET)
#define BPORT1_AB_MER_ME                0x1
#define BPORT1_AB_MER_ME_GET(_v)        (_v & 0x1)
#define BPORT1_AB_MER_HIE               (0x1 << 1)
#define BPORT1_AB_MER_HIE_GET(_v)       ((_v >> 1) & 0x1)

#define BPORT1_AB_IMR_POFFSET           0x20
#define BPORT1_AB_IMR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IMR_POFFSET)

#define BPORT1_AB_ILR_POFFSET           0x24
#define BPORT1_AB_ILR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ILR_POFFSET)

#define BPORT1_AB_IVAR_POFFSET          0x100
#define BPORT1_AB_IVAR(_MMR_INDEX)      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IVAR_POFFSET + ((_MMR_INDEX) * 0x4))

#define BPORT1_AB_BUFFER_POFFSET        0x0
#define BPORT1_AB_BUFFER                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BUFFER_POFFSET)
#define BPORT1_AB_BUFFER_BYTES          0x200


#endif

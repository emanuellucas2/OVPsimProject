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
#define BPORT1_AB_GPC_CNTR_POFFSET      0x0
#define BPORT1_AB_GPC_CNTR              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPC_CNTR_POFFSET)
#define BPORT1_AB_GPC_CNTR_GPCIRQM      (0x1 << 21)
#define BPORT1_AB_GPC_CNTR_GPCIRQM_GET(_v)  ((_v >> 21) & 0x1)
#define BPORT1_AB_GPC_CNTR_VPU_PUP      (0x1 << 1)
#define BPORT1_AB_GPC_CNTR_VPU_PUP_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_GPC_CNTR_VPU_PDN      0x1
#define BPORT1_AB_GPC_CNTR_VPU_PDN_GET(_v)  (_v & 0x1)

#define BPORT1_AB_GPC_PGR_POFFSET       0x4
#define BPORT1_AB_GPC_PGR               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPC_PGR_POFFSET)
#define BPORT1_AB_GPC_PGR_DRCIC         (0x3 << 29)
#define BPORT1_AB_GPC_PGR_DRCIC_GET(_v)  ((_v >> 29) & 0x3)

#define BPORT1_AB_GPC_IMR1_POFFSET      0x8
#define BPORT1_AB_GPC_IMR1              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPC_IMR1_POFFSET)

#define BPORT1_AB_GPC_IMR2_POFFSET      0xc
#define BPORT1_AB_GPC_IMR2              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPC_IMR2_POFFSET)

#define BPORT1_AB_GPC_IMR3_POFFSET      0x10
#define BPORT1_AB_GPC_IMR3              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPC_IMR3_POFFSET)

#define BPORT1_AB_GPC_IMR4_POFFSET      0x14
#define BPORT1_AB_GPC_IMR4              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPC_IMR4_POFFSET)

#define BPORT1_AB_GPC_ISR1_POFFSET      0x18
#define BPORT1_AB_GPC_ISR1              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPC_ISR1_POFFSET)

#define BPORT1_AB_GPC_ISR2_POFFSET      0x1c
#define BPORT1_AB_GPC_ISR2              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPC_ISR2_POFFSET)

#define BPORT1_AB_GPC_ISR3_POFFSET      0x20
#define BPORT1_AB_GPC_ISR3              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPC_ISR3_POFFSET)

#define BPORT1_AB_GPC_ISR4_POFFSET      0x24
#define BPORT1_AB_GPC_ISR4              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPC_ISR4_POFFSET)

#define BPORT1_AB_BUFFER_POFFSET        0x0
#define BPORT1_AB_BUFFER                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BUFFER_POFFSET)
#define BPORT1_AB_BUFFER_BYTES          0x260


#endif

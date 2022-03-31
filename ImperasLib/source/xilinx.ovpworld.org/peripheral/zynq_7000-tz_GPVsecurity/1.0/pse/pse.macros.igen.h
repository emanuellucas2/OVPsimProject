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
#define BPORT1_AB_SECURITY_GP0_AXI_POFFSET  0x1c
#define BPORT1_AB_SECURITY_GP0_AXI      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SECURITY_GP0_AXI_POFFSET)

#define BPORT1_AB_SECURITY_GP1_AXI_POFFSET  0x20
#define BPORT1_AB_SECURITY_GP1_AXI      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SECURITY_GP1_AXI_POFFSET)

#define BPORT1_AB_SECURITY_APB_POFFSET  0x28
#define BPORT1_AB_SECURITY_APB          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SECURITY_APB_POFFSET)
#define BPORT1_AB_SECURITY_APB_DDRC     (0x1 << 5)
#define BPORT1_AB_SECURITY_APB_DDRC_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_SECURITY_APB_TTC1     (0x1 << 4)
#define BPORT1_AB_SECURITY_APB_TTC1_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_SECURITY_APB_AFI3     (0x1 << 3)
#define BPORT1_AB_SECURITY_APB_AFI3_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_SECURITY_APB_AFI2     (0x1 << 2)
#define BPORT1_AB_SECURITY_APB_AFI2_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_SECURITY_APB_AFI1     (0x1 << 1)
#define BPORT1_AB_SECURITY_APB_AFI1_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_SECURITY_APB_AFI0     0x1
#define BPORT1_AB_SECURITY_APB_AFI0_GET(_v)  (_v & 0x1)

#define BPORT1_AB_BUFFER_POFFSET        0x0
#define BPORT1_AB_BUFFER                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BUFFER_POFFSET)
#define BPORT1_AB_BUFFER_BYTES          0x40


#endif

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
#define BPORT1_AB_PMPROT_POFFSET        0x0
#define BPORT1_AB_PMPROT                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PMPROT_POFFSET)
#define BPORT1_AB_PMPROT_ALLS           (0x1 << 3)
#define BPORT1_AB_PMPROT_ALLS_GET(_v)   ((_v >> 3) & 0x1)
#define BPORT1_AB_PMPROT_AVLLS          (0x1 << 1)
#define BPORT1_AB_PMPROT_AVLLS_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_PMPROT_AVLP           (0x1 << 5)
#define BPORT1_AB_PMPROT_AVLP_GET(_v)   ((_v >> 5) & 0x1)

#define BPORT1_AB_PMCTRL_POFFSET        0x1
#define BPORT1_AB_PMCTRL                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PMCTRL_POFFSET)
#define BPORT1_AB_PMCTRL_LPWUI          (0x1 << 7)
#define BPORT1_AB_PMCTRL_LPWUI_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_PMCTRL_RUNM           (0x3 << 5)
#define BPORT1_AB_PMCTRL_RUNM_GET(_v)   ((_v >> 5) & 0x3)
#define BPORT1_AB_PMCTRL_STOPA          (0x1 << 3)
#define BPORT1_AB_PMCTRL_STOPA_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_PMCTRL_STOPM          0x7
#define BPORT1_AB_PMCTRL_STOPM_GET(_v)  (_v & 0x7)

#define BPORT1_AB_VLLSCTRL_POFFSET      0x2
#define BPORT1_AB_VLLSCTRL              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_VLLSCTRL_POFFSET)
#define BPORT1_AB_VLLSCTRL_VLLSM        0x7
#define BPORT1_AB_VLLSCTRL_VLLSM_GET(_v)  (_v & 0x7)

#define BPORT1_AB_PMSTAT_POFFSET        0x3
#define BPORT1_AB_PMSTAT                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PMSTAT_POFFSET)
#define BPORT1_AB_PMSTAT_PMSTAT         0x7f
#define BPORT1_AB_PMSTAT_PMSTAT_GET(_v)  (_v & 0x7f)


#endif

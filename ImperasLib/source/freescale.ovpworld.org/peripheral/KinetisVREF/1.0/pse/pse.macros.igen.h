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
#define BPORT1_AB_TRM_POFFSET           0x0
#define BPORT1_AB_TRM                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TRM_POFFSET)
#define BPORT1_AB_TRM_TRIM              0x3f
#define BPORT1_AB_TRM_TRIM_GET(_v)      (_v & 0x3f)

#define BPORT1_AB_SC_POFFSET            0x1
#define BPORT1_AB_SC                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SC_POFFSET)
#define BPORT1_AB_SC_MODE_LV            0x3
#define BPORT1_AB_SC_MODE_LV_GET(_v)    (_v & 0x3)
#define BPORT1_AB_SC_REGEN              (0x1 << 6)
#define BPORT1_AB_SC_REGEN_GET(_v)      ((_v >> 6) & 0x1)
#define BPORT1_AB_SC_VREFEN             (0x1 << 7)
#define BPORT1_AB_SC_VREFEN_GET(_v)     ((_v >> 7) & 0x1)
#define BPORT1_AB_SC_VREFST             (0x1 << 2)
#define BPORT1_AB_SC_VREFST_GET(_v)     ((_v >> 2) & 0x1)


#endif

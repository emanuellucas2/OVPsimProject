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
#define BPORT1_AB_STATUS_POFFSET        0x0
#define BPORT1_AB_STATUS                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_STATUS_POFFSET)

#define BPORT1_AB_LEVEL_POFFSET         0x4
#define BPORT1_AB_LEVEL                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LEVEL_POFFSET)

#define BPORT1_AB_ENABLE_POFFSET        0x8
#define BPORT1_AB_ENABLE                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENABLE_POFFSET)

#define BPORT1_AB_CLR_POFFSET           0xc
#define BPORT1_AB_CLR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CLR_POFFSET)

#define BPORT1_AB_SOFTSET_POFFSET       0x10
#define BPORT1_AB_SOFTSET               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SOFTSET_POFFSET)

#define BPORT1_AB_SOFTCLR_POFFSET       0x14
#define BPORT1_AB_SOFTCLR               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SOFTCLR_POFFSET)

#define BPORT1_AB_FRQSTAT_POFFSET       0x20
#define BPORT1_AB_FRQSTAT               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FRQSTAT_POFFSET)

#define BPORT1_AB_RAWSTAT_POFFSET       0x24
#define BPORT1_AB_RAWSTAT               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RAWSTAT_POFFSET)

#define BPORT1_AB_FIQEN_POFFSET         0x28
#define BPORT1_AB_FIQEN                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FIQEN_POFFSET)

#define BPORT1_AB_FIQENCLR_POFFSET      0x2c
#define BPORT1_AB_FIQENCLR              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FIQENCLR_POFFSET)


#endif

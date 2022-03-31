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


#define BPORT1_REG_POFFSET              0x0
#define BPORT1_REG_MSEL_POFFSET         0x0
#define BPORT1_REG_MSEL                 (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_MSEL_POFFSET)

#define BPORT1_CODE_POFFSET             0x4
#define BPORT1_CODE_RESET_POFFSET       0x0
#define BPORT1_CODE_RESET               (BPORT1 + BPORT1_CODE_POFFSET + BPORT1_CODE_RESET_POFFSET)
#define BPORT1_CODE_RESET_BYTES         0x20

#define BPORT1_TABLE_POFFSET            0x100
#define BPORT1_TABLE_JUMPADDR_POFFSET   0x0
#define BPORT1_TABLE_JUMPADDR           (BPORT1 + BPORT1_TABLE_POFFSET + BPORT1_TABLE_JUMPADDR_POFFSET)
#define BPORT1_TABLE_JUMPADDR_BYTES     0x80


#endif

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

// Set the macro 'IDPORT' to the base of port 'idport'
#ifndef IDPORT
#error IDPORT is undefined. It needs to be set to the port base address
#endif


#define IDPORT_AB_POFFSET               0x0
#define IDPORT_AB_ID_POFFSET            0x0
#define IDPORT_AB_ID                    (IDPORT + IDPORT_AB_POFFSET + IDPORT_AB_ID_POFFSET)
#define IDPORT_AB_ID_BYTES              0x4


#endif

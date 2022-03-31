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

// Set the macro 'BRGP0' to the base of port 'BRGP0'
#ifndef BRGP0
#error BRGP0 is undefined. It needs to be set to the port base address
#endif


#define BRGP0_REG0_POFFSET              0x0
#define BRGP0_REG0_PRSM_POFFSET         0x0
#define BRGP0_REG0_PRSM                 (BRGP0 + BRGP0_REG0_POFFSET + BRGP0_REG0_PRSM_POFFSET)
#define BRGP0_REG0_PRSM_BGCS            0x3
#define BRGP0_REG0_PRSM_BGCS_GET(_v)    (_v & 0x3)
#define BRGP0_REG0_PRSM_TODIS           (0x1 << 2)
#define BRGP0_REG0_PRSM_TODIS_GET(_v)   ((_v >> 2) & 0x1)
#define BRGP0_REG0_PRSM_BGCE            (0x1 << 4)
#define BRGP0_REG0_PRSM_BGCE_GET(_v)    ((_v >> 4) & 0x1)

#define BRGP0_REG0_PRSCM_POFFSET        0x1
#define BRGP0_REG0_PRSCM                (BRGP0 + BRGP0_REG0_POFFSET + BRGP0_REG0_PRSCM_POFFSET)


#endif

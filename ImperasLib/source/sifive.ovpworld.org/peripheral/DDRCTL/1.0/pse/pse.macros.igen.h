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

// Set the macro 'CONTROL' to the base of port 'CONTROL'
#ifndef CONTROL
#error CONTROL is undefined. It needs to be set to the port base address
#endif
// Set the macro 'BLOCKER' to the base of port 'BLOCKER'
#ifndef BLOCKER
#error BLOCKER is undefined. It needs to be set to the port base address
#endif


#define CONTROL_REGS_POFFSET            0x0
#define CONTROL_REGS_REG33_POFFSET      0x84
#define CONTROL_REGS_REG33              (CONTROL + CONTROL_REGS_POFFSET + CONTROL_REGS_REG33_POFFSET)

#define CONTROL_REGS_CTRLREGS_POFFSET   0x0
#define CONTROL_REGS_CTRLREGS           (CONTROL + CONTROL_REGS_POFFSET + CONTROL_REGS_CTRLREGS_POFFSET)
#define CONTROL_REGS_CTRLREGS_BYTES     0x4000


#define BLOCKER_REGS_POFFSET            0x0
#define BLOCKER_REGS_BLKREGS_POFFSET    0x0
#define BLOCKER_REGS_BLKREGS            (BLOCKER + BLOCKER_REGS_POFFSET + BLOCKER_REGS_BLKREGS_POFFSET)
#define BLOCKER_REGS_BLKREGS_BYTES      0x8


#endif

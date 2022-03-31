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
#define BPORT1_REG_COUNT_POFFSET        0x0
#define BPORT1_REG_COUNT                (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_COUNT_POFFSET)

#define BPORT1_REG_INIT_TIME_POFFSET    0x4
#define BPORT1_REG_INIT_TIME            (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_INIT_TIME_POFFSET)
#define BPORT1_REG_INIT_TIME_INIT       (0xffffff << 8)
#define BPORT1_REG_INIT_TIME_INIT_GET(_v)  ((_v >> 8) & 0xffffff)
#define BPORT1_REG_INIT_TIME_CTRL       0xff
#define BPORT1_REG_INIT_TIME_CTRL_GET(_v)  (_v & 0xff)

#define BPORT1_REG_CAPTURE_TIME_POFFSET  0x8
#define BPORT1_REG_CAPTURE_TIME         (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_CAPTURE_TIME_POFFSET)

#define BPORT1_REG_BUFFER0_POFFSET      0x0
#define BPORT1_REG_BUFFER0              (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_BUFFER0_POFFSET)
#define BPORT1_REG_BUFFER0_BYTES        0x1000


#endif

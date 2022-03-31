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

// Set the macro 'SP1' to the base of port 'sp1'
#ifndef SP1
#error SP1 is undefined. It needs to be set to the port base address
#endif


#define SP1_REG0_POFFSET                0x0
#define SP1_REG0_STATUS_POFFSET         0x0
#define SP1_REG0_STATUS                 (SP1 + SP1_REG0_POFFSET + SP1_REG0_STATUS_POFFSET)
#define SP1_REG0_STATUS_TO              0x1
#define SP1_REG0_STATUS_TO_GET(_v)      (_v & 0x1)
#define SP1_REG0_STATUS_RUN             (0x1 << 1)
#define SP1_REG0_STATUS_RUN_GET(_v)     ((_v >> 1) & 0x1)

#define SP1_REG0_CONTROL_POFFSET        0x4
#define SP1_REG0_CONTROL                (SP1 + SP1_REG0_POFFSET + SP1_REG0_CONTROL_POFFSET)
#define SP1_REG0_CONTROL_ITO            0x1
#define SP1_REG0_CONTROL_ITO_GET(_v)    (_v & 0x1)
#define SP1_REG0_CONTROL_CONT           (0x1 << 1)
#define SP1_REG0_CONTROL_CONT_GET(_v)   ((_v >> 1) & 0x1)
#define SP1_REG0_CONTROL_START          (0x1 << 2)
#define SP1_REG0_CONTROL_START_GET(_v)  ((_v >> 2) & 0x1)
#define SP1_REG0_CONTROL_STOP           (0x1 << 3)
#define SP1_REG0_CONTROL_STOP_GET(_v)   ((_v >> 3) & 0x1)

#define SP1_REG0_PERIODL_POFFSET        0x8
#define SP1_REG0_PERIODL                (SP1 + SP1_REG0_POFFSET + SP1_REG0_PERIODL_POFFSET)

#define SP1_REG0_PERIODH_POFFSET        0xc
#define SP1_REG0_PERIODH                (SP1 + SP1_REG0_POFFSET + SP1_REG0_PERIODH_POFFSET)

#define SP1_REG0_SNAPL_POFFSET          0x10
#define SP1_REG0_SNAPL                  (SP1 + SP1_REG0_POFFSET + SP1_REG0_SNAPL_POFFSET)

#define SP1_REG0_SNAPH_POFFSET          0x14
#define SP1_REG0_SNAPH                  (SP1 + SP1_REG0_POFFSET + SP1_REG0_SNAPH_POFFSET)


#endif

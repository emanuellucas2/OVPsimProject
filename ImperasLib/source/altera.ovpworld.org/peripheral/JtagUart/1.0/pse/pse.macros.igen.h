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
#define SP1_REG0_DATA_POFFSET           0x0
#define SP1_REG0_DATA                   (SP1 + SP1_REG0_POFFSET + SP1_REG0_DATA_POFFSET)
#define SP1_REG0_DATA_DATA              0xff
#define SP1_REG0_DATA_DATA_GET(_v)      (_v & 0xff)
#define SP1_REG0_DATA_RVALID            (0x1 << 15)
#define SP1_REG0_DATA_RVALID_GET(_v)    ((_v >> 15) & 0x1)
#define SP1_REG0_DATA_RAVAIL            (0xffff << 16)
#define SP1_REG0_DATA_RAVAIL_GET(_v)    ((_v >> 16) & 0xffff)

#define SP1_REG0_CONTROL_POFFSET        0x4
#define SP1_REG0_CONTROL                (SP1 + SP1_REG0_POFFSET + SP1_REG0_CONTROL_POFFSET)
#define SP1_REG0_CONTROL_RE             0x1
#define SP1_REG0_CONTROL_RE_GET(_v)     (_v & 0x1)
#define SP1_REG0_CONTROL_WE             (0x1 << 1)
#define SP1_REG0_CONTROL_WE_GET(_v)     ((_v >> 1) & 0x1)
#define SP1_REG0_CONTROL_RI             (0x1 << 8)
#define SP1_REG0_CONTROL_RI_GET(_v)     ((_v >> 8) & 0x1)
#define SP1_REG0_CONTROL_WI             (0x1 << 9)
#define SP1_REG0_CONTROL_WI_GET(_v)     ((_v >> 9) & 0x1)
#define SP1_REG0_CONTROL_AC             (0x1 << 10)
#define SP1_REG0_CONTROL_AC_GET(_v)     ((_v >> 10) & 0x1)
#define SP1_REG0_CONTROL_WSPACE         (0xffff << 16)
#define SP1_REG0_CONTROL_WSPACE_GET(_v)  ((_v >> 16) & 0xffff)


#endif

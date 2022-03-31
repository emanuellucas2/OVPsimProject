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

// Set the macro 'DMACSP' to the base of port 'DMACSP'
#ifndef DMACSP
#error DMACSP is undefined. It needs to be set to the port base address
#endif


#define DMACSP_AB8_POFFSET              0x0
#define DMACSP_AB8_INTTCSTATUS_POFFSET  0x4
#define DMACSP_AB8_INTTCSTATUS          (DMACSP + DMACSP_AB8_POFFSET + DMACSP_AB8_INTTCSTATUS_POFFSET)

#define DMACSP_AB8_RAWTCSTATUS_POFFSET  0x14
#define DMACSP_AB8_RAWTCSTATUS          (DMACSP + DMACSP_AB8_POFFSET + DMACSP_AB8_RAWTCSTATUS_POFFSET)

#define DMACSP_AB8_CONFIG_POFFSET       0x30
#define DMACSP_AB8_CONFIG               (DMACSP + DMACSP_AB8_POFFSET + DMACSP_AB8_CONFIG_POFFSET)
#define DMACSP_AB8_CONFIG_BURSTSIZE     0x3
#define DMACSP_AB8_CONFIG_BURSTSIZE_GET(_v)  (_v & 0x3)

#define DMACSP_AB32CH0_POFFSET          0x100
#define DMACSP_AB32CH0_SRCADDR_POFFSET  0x0
#define DMACSP_AB32CH0_SRCADDR          (DMACSP + DMACSP_AB32CH0_POFFSET + DMACSP_AB32CH0_SRCADDR_POFFSET)

#define DMACSP_AB32CH0_DSTADDR_POFFSET  0x4
#define DMACSP_AB32CH0_DSTADDR          (DMACSP + DMACSP_AB32CH0_POFFSET + DMACSP_AB32CH0_DSTADDR_POFFSET)

#define DMACSP_AB32CH0_CONTROL_POFFSET  0xc
#define DMACSP_AB32CH0_CONTROL          (DMACSP + DMACSP_AB32CH0_POFFSET + DMACSP_AB32CH0_CONTROL_POFFSET)
#define DMACSP_AB32CH0_CONTROL_TRANSFERSIZE  0xfff
#define DMACSP_AB32CH0_CONTROL_TRANSFERSIZE_GET(_v)  (_v & 0xfff)

#define DMACSP_AB32CH0_CONFIG_POFFSET   0x10
#define DMACSP_AB32CH0_CONFIG           (DMACSP + DMACSP_AB32CH0_POFFSET + DMACSP_AB32CH0_CONFIG_POFFSET)
#define DMACSP_AB32CH0_CONFIG_ENABLE    0x1
#define DMACSP_AB32CH0_CONFIG_ENABLE_GET(_v)  (_v & 0x1)
#define DMACSP_AB32CH0_CONFIG_INTEN     (0x1 << 15)
#define DMACSP_AB32CH0_CONFIG_INTEN_GET(_v)  ((_v >> 15) & 0x1)
#define DMACSP_AB32CH0_CONFIG_HALT      (0x1 << 18)
#define DMACSP_AB32CH0_CONFIG_HALT_GET(_v)  ((_v >> 18) & 0x1)

#define DMACSP_AB32CH1_POFFSET          0x120
#define DMACSP_AB32CH1_SRCADDR_POFFSET  0x0
#define DMACSP_AB32CH1_SRCADDR          (DMACSP + DMACSP_AB32CH1_POFFSET + DMACSP_AB32CH1_SRCADDR_POFFSET)

#define DMACSP_AB32CH1_DSTADDR_POFFSET  0x4
#define DMACSP_AB32CH1_DSTADDR          (DMACSP + DMACSP_AB32CH1_POFFSET + DMACSP_AB32CH1_DSTADDR_POFFSET)

#define DMACSP_AB32CH1_CONTROL_POFFSET  0xc
#define DMACSP_AB32CH1_CONTROL          (DMACSP + DMACSP_AB32CH1_POFFSET + DMACSP_AB32CH1_CONTROL_POFFSET)
#define DMACSP_AB32CH1_CONTROL_TRANSFERSIZE  0xfff
#define DMACSP_AB32CH1_CONTROL_TRANSFERSIZE_GET(_v)  (_v & 0xfff)

#define DMACSP_AB32CH1_CONFIG_POFFSET   0x10
#define DMACSP_AB32CH1_CONFIG           (DMACSP + DMACSP_AB32CH1_POFFSET + DMACSP_AB32CH1_CONFIG_POFFSET)
#define DMACSP_AB32CH1_CONFIG_ENABLE    0x1
#define DMACSP_AB32CH1_CONFIG_ENABLE_GET(_v)  (_v & 0x1)
#define DMACSP_AB32CH1_CONFIG_INTEN     (0x1 << 15)
#define DMACSP_AB32CH1_CONFIG_INTEN_GET(_v)  ((_v >> 15) & 0x1)
#define DMACSP_AB32CH1_CONFIG_HALT      (0x1 << 18)
#define DMACSP_AB32CH1_CONFIG_HALT_GET(_v)  ((_v >> 18) & 0x1)


#endif

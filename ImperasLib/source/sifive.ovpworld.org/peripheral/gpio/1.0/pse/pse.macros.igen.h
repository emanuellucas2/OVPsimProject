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
#define BPORT1_REG_VALUE_POFFSET        0x0
#define BPORT1_REG_VALUE                (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_VALUE_POFFSET)

#define BPORT1_REG_INPUT_EN_POFFSET     0x4
#define BPORT1_REG_INPUT_EN             (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_INPUT_EN_POFFSET)

#define BPORT1_REG_OUTPUT_EN_POFFSET    0x8
#define BPORT1_REG_OUTPUT_EN            (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_OUTPUT_EN_POFFSET)

#define BPORT1_REG_PORT_POFFSET         0xc
#define BPORT1_REG_PORT                 (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_PORT_POFFSET)

#define BPORT1_REG_PUE_POFFSET          0x10
#define BPORT1_REG_PUE                  (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_PUE_POFFSET)

#define BPORT1_REG_DS_POFFSET           0x14
#define BPORT1_REG_DS                   (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_DS_POFFSET)

#define BPORT1_REG_RISE_IE_POFFSET      0x18
#define BPORT1_REG_RISE_IE              (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_RISE_IE_POFFSET)

#define BPORT1_REG_RISE_IP_POFFSET      0x1c
#define BPORT1_REG_RISE_IP              (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_RISE_IP_POFFSET)

#define BPORT1_REG_FALL_IE_POFFSET      0x20
#define BPORT1_REG_FALL_IE              (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_FALL_IE_POFFSET)

#define BPORT1_REG_FALL_IP_POFFSET      0x24
#define BPORT1_REG_FALL_IP              (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_FALL_IP_POFFSET)

#define BPORT1_REG_HIGH_IE_POFFSET      0x28
#define BPORT1_REG_HIGH_IE              (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_HIGH_IE_POFFSET)

#define BPORT1_REG_HIGH_IP_POFFSET      0x2c
#define BPORT1_REG_HIGH_IP              (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_HIGH_IP_POFFSET)

#define BPORT1_REG_LOW_IE_POFFSET       0x30
#define BPORT1_REG_LOW_IE               (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_LOW_IE_POFFSET)

#define BPORT1_REG_LOW_IP_POFFSET       0x34
#define BPORT1_REG_LOW_IP               (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_LOW_IP_POFFSET)

#define BPORT1_REG_IOF_EN_POFFSET       0x38
#define BPORT1_REG_IOF_EN               (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_IOF_EN_POFFSET)

#define BPORT1_REG_IOF_SEL_POFFSET      0x3c
#define BPORT1_REG_IOF_SEL              (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_IOF_SEL_POFFSET)

#define BPORT1_REG_OUT_XOR_POFFSET      0x40
#define BPORT1_REG_OUT_XOR              (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_OUT_XOR_POFFSET)


#endif

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
#define BPORT1_AB_CCM_ANALOG_PLL_ARM_POFFSET  0x0
#define BPORT1_AB_CCM_ANALOG_PLL_ARM    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_ARM_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_ARM_SET_POFFSET  0x4
#define BPORT1_AB_CCM_ANALOG_PLL_ARM_SET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_ARM_SET_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_ARM_CLR_POFFSET  0x8
#define BPORT1_AB_CCM_ANALOG_PLL_ARM_CLR  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_ARM_CLR_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_ARM_TOG_POFFSET  0xc
#define BPORT1_AB_CCM_ANALOG_PLL_ARM_TOG  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_ARM_TOG_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_USB1_POFFSET  0x10
#define BPORT1_AB_CCM_ANALOG_PLL_USB1   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_USB1_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_USB1_SET_POFFSET  0x14
#define BPORT1_AB_CCM_ANALOG_PLL_USB1_SET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_USB1_SET_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_USB1_CLR_POFFSET  0x18
#define BPORT1_AB_CCM_ANALOG_PLL_USB1_CLR  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_USB1_CLR_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_USB1_TOG_POFFSET  0x1c
#define BPORT1_AB_CCM_ANALOG_PLL_USB1_TOG  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_USB1_TOG_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_USB2_POFFSET  0x20
#define BPORT1_AB_CCM_ANALOG_PLL_USB2   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_USB2_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_USB2_SET_POFFSET  0x24
#define BPORT1_AB_CCM_ANALOG_PLL_USB2_SET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_USB2_SET_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_USB2_CLR_POFFSET  0x28
#define BPORT1_AB_CCM_ANALOG_PLL_USB2_CLR  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_USB2_CLR_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_USB2_TOG_POFFSET  0x2c
#define BPORT1_AB_CCM_ANALOG_PLL_USB2_TOG  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_USB2_TOG_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_SYS_POFFSET  0x30
#define BPORT1_AB_CCM_ANALOG_PLL_SYS    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_SYS_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_SYS_SET_POFFSET  0x34
#define BPORT1_AB_CCM_ANALOG_PLL_SYS_SET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_SYS_SET_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_SYS_CLR_POFFSET  0x38
#define BPORT1_AB_CCM_ANALOG_PLL_SYS_CLR  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_SYS_CLR_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_SYS_TOG_POFFSET  0x3c
#define BPORT1_AB_CCM_ANALOG_PLL_SYS_TOG  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_SYS_TOG_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_SYS_SS_POFFSET  0x40
#define BPORT1_AB_CCM_ANALOG_PLL_SYS_SS  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_SYS_SS_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_SYS_SYS_NUM_POFFSET  0x50
#define BPORT1_AB_CCM_ANALOG_PLL_SYS_SYS_NUM  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_SYS_SYS_NUM_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_SYS_SYS_DENOM_POFFSET  0x60
#define BPORT1_AB_CCM_ANALOG_PLL_SYS_SYS_DENOM  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_SYS_SYS_DENOM_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_POFFSET  0x70
#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_AUDIO_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_SET_POFFSET  0x74
#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_SET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_AUDIO_SET_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_CLR_POFFSET  0x78
#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_CLR  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_AUDIO_CLR_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_TOG_POFFSET  0x7c
#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_TOG  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_AUDIO_TOG_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_NUM_POFFSET  0x80
#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_NUM  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_AUDIO_NUM_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_NUM_SET_POFFSET  0x84
#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_NUM_SET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_AUDIO_NUM_SET_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_NUM_CLR_POFFSET  0x88
#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_NUM_CLR  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_AUDIO_NUM_CLR_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_NUM_TOG_POFFSET  0x8c
#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_NUM_TOG  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_AUDIO_NUM_TOG_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_DENOM_POFFSET  0x90
#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_DENOM  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_AUDIO_DENOM_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_DENOM_SET_POFFSET  0x94
#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_DENOM_SET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_AUDIO_DENOM_SET_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_DENOM_CLR_POFFSET  0x98
#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_DENOM_CLR  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_AUDIO_DENOM_CLR_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_DENOM_TOG_POFFSET  0x9c
#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_DENOM_TOG  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_AUDIO_DENOM_TOG_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_POFFSET  0xa0
#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_VIDEO_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_SET_POFFSET  0xa4
#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_SET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_VIDEO_SET_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_CLR_POFFSET  0xa8
#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_CLR  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_VIDEO_CLR_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_TOG_POFFSET  0xac
#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_TOG  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_VIDEO_TOG_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_NUM_POFFSET  0xb0
#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_NUM  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_VIDEO_NUM_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_NUM_SET_POFFSET  0xb4
#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_NUM_SET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_VIDEO_NUM_SET_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_NUM_CLR_POFFSET  0xb8
#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_NUM_CLR  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_VIDEO_NUM_CLR_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_NUM_TOG_POFFSET  0xbc
#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_NUM_TOG  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_VIDEO_NUM_TOG_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_DENOM_POFFSET  0xc0
#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_DENOM  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_VIDEO_DENOM_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_DENOM_SET_POFFSET  0xc4
#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_DENOM_SET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_VIDEO_DENOM_SET_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_DENOM_CLR_POFFSET  0xc8
#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_DENOM_CLR  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_VIDEO_DENOM_CLR_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_DENOM_TOG_POFFSET  0xcc
#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_DENOM_TOG  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_VIDEO_DENOM_TOG_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_MLB_POFFSET  0xd0
#define BPORT1_AB_CCM_ANALOG_PLL_MLB    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_MLB_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_MLB_SET_POFFSET  0xd4
#define BPORT1_AB_CCM_ANALOG_PLL_MLB_SET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_MLB_SET_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_MLB_CLR_POFFSET  0xd8
#define BPORT1_AB_CCM_ANALOG_PLL_MLB_CLR  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_MLB_CLR_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_MLB_TOG_POFFSET  0xdc
#define BPORT1_AB_CCM_ANALOG_PLL_MLB_TOG  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_MLB_TOG_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_ENET_POFFSET  0xe0
#define BPORT1_AB_CCM_ANALOG_PLL_ENET   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_ENET_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_ENET_SET_POFFSET  0xe4
#define BPORT1_AB_CCM_ANALOG_PLL_ENET_SET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_ENET_SET_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_ENET_CLR_POFFSET  0xe8
#define BPORT1_AB_CCM_ANALOG_PLL_ENET_CLR  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_ENET_CLR_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PLL_ENET_TOG_POFFSET  0xec
#define BPORT1_AB_CCM_ANALOG_PLL_ENET_TOG  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PLL_ENET_TOG_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PFD_480_POFFSET  0xf0
#define BPORT1_AB_CCM_ANALOG_PFD_480    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PFD_480_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PFD_480_SET_POFFSET  0xf4
#define BPORT1_AB_CCM_ANALOG_PFD_480_SET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PFD_480_SET_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PFD_480_CLR_POFFSET  0xf8
#define BPORT1_AB_CCM_ANALOG_PFD_480_CLR  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PFD_480_CLR_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PFD_480_TOG_POFFSET  0xfc
#define BPORT1_AB_CCM_ANALOG_PFD_480_TOG  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PFD_480_TOG_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PFD_528_POFFSET  0x100
#define BPORT1_AB_CCM_ANALOG_PFD_528    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PFD_528_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PFD_528_SET_POFFSET  0x104
#define BPORT1_AB_CCM_ANALOG_PFD_528_SET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PFD_528_SET_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PFD_528_CLR_POFFSET  0x108
#define BPORT1_AB_CCM_ANALOG_PFD_528_CLR  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PFD_528_CLR_POFFSET)

#define BPORT1_AB_CCM_ANALOG_PFD_528_TOG_POFFSET  0x10c
#define BPORT1_AB_CCM_ANALOG_PFD_528_TOG  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_ANALOG_PFD_528_TOG_POFFSET)

#define BPORT1_AB_PMU_REG_1P1_POFFSET   0x110
#define BPORT1_AB_PMU_REG_1P1           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PMU_REG_1P1_POFFSET)

#define BPORT1_AB_PMU_REG_1P1_SET_POFFSET  0x114
#define BPORT1_AB_PMU_REG_1P1_SET       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PMU_REG_1P1_SET_POFFSET)

#define BPORT1_AB_PMU_REG_1P1_CLR_POFFSET  0x118
#define BPORT1_AB_PMU_REG_1P1_CLR       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PMU_REG_1P1_CLR_POFFSET)

#define BPORT1_AB_PMU_REG_1P1_TOG_POFFSET  0x11c
#define BPORT1_AB_PMU_REG_1P1_TOG       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PMU_REG_1P1_TOG_POFFSET)

#define BPORT1_AB_PMU_REG_3P0_POFFSET   0x120
#define BPORT1_AB_PMU_REG_3P0           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PMU_REG_3P0_POFFSET)

#define BPORT1_AB_PMU_REG_3P0_SET_POFFSET  0x124
#define BPORT1_AB_PMU_REG_3P0_SET       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PMU_REG_3P0_SET_POFFSET)

#define BPORT1_AB_PMU_REG_3P0_CLR_POFFSET  0x128
#define BPORT1_AB_PMU_REG_3P0_CLR       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PMU_REG_3P0_CLR_POFFSET)

#define BPORT1_AB_PMU_REG_3P0_TOG_POFFSET  0x12c
#define BPORT1_AB_PMU_REG_3P0_TOG       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PMU_REG_3P0_TOG_POFFSET)

#define BPORT1_AB_PMU_REG_2P5_POFFSET   0x130
#define BPORT1_AB_PMU_REG_2P5           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PMU_REG_2P5_POFFSET)

#define BPORT1_AB_PMU_REG_2P5_SET_POFFSET  0x134
#define BPORT1_AB_PMU_REG_2P5_SET       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PMU_REG_2P5_SET_POFFSET)

#define BPORT1_AB_PMU_REG_2P5_CLR_POFFSET  0x138
#define BPORT1_AB_PMU_REG_2P5_CLR       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PMU_REG_2P5_CLR_POFFSET)

#define BPORT1_AB_PMU_REG_2P5_TOG_POFFSET  0x13c
#define BPORT1_AB_PMU_REG_2P5_TOG       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PMU_REG_2P5_TOG_POFFSET)

#define BPORT1_AB_PMU_REG_CORE_POFFSET  0x140
#define BPORT1_AB_PMU_REG_CORE          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PMU_REG_CORE_POFFSET)

#define BPORT1_AB_PMU_REG_CORE_SET_POFFSET  0x144
#define BPORT1_AB_PMU_REG_CORE_SET      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PMU_REG_CORE_SET_POFFSET)

#define BPORT1_AB_PMU_REG_CORE_CLR_POFFSET  0x148
#define BPORT1_AB_PMU_REG_CORE_CLR      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PMU_REG_CORE_CLR_POFFSET)

#define BPORT1_AB_PMU_REG_CORE_TOG_POFFSET  0x14c
#define BPORT1_AB_PMU_REG_CORE_TOG      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PMU_REG_CORE_TOG_POFFSET)

#define BPORT1_AB_MISC0_POFFSET         0x150
#define BPORT1_AB_MISC0                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MISC0_POFFSET)

#define BPORT1_AB_MISC0_SET_POFFSET     0x154
#define BPORT1_AB_MISC0_SET             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MISC0_SET_POFFSET)

#define BPORT1_AB_MISC0_CLR_POFFSET     0x158
#define BPORT1_AB_MISC0_CLR             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MISC0_CLR_POFFSET)

#define BPORT1_AB_MISC0_TOG_POFFSET     0x15c
#define BPORT1_AB_MISC0_TOG             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MISC0_TOG_POFFSET)

#define BPORT1_AB_MISC1_POFFSET         0x160
#define BPORT1_AB_MISC1                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MISC1_POFFSET)

#define BPORT1_AB_MISC1_SET_POFFSET     0x164
#define BPORT1_AB_MISC1_SET             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MISC1_SET_POFFSET)

#define BPORT1_AB_MISC1_CLR_POFFSET     0x168
#define BPORT1_AB_MISC1_CLR             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MISC1_CLR_POFFSET)

#define BPORT1_AB_MISC1_TOG_POFFSET     0x16c
#define BPORT1_AB_MISC1_TOG             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MISC1_TOG_POFFSET)

#define BPORT1_AB_MISC2_POFFSET         0x170
#define BPORT1_AB_MISC2                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MISC2_POFFSET)

#define BPORT1_AB_MISC2_SET_POFFSET     0x174
#define BPORT1_AB_MISC2_SET             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MISC2_SET_POFFSET)

#define BPORT1_AB_MISC2_CLR_POFFSET     0x178
#define BPORT1_AB_MISC2_CLR             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MISC2_CLR_POFFSET)

#define BPORT1_AB_MISC2_TOG_POFFSET     0x17c
#define BPORT1_AB_MISC2_TOG             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MISC2_TOG_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB1_VBUS_DETECT_POFFSET  0x1a0
#define BPORT1_AB_USB_ANALOG_USB1_VBUS_DETECT  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB1_VBUS_DETECT_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB1_VBUS_DETECT_SET_POFFSET  0x1a4
#define BPORT1_AB_USB_ANALOG_USB1_VBUS_DETECT_SET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB1_VBUS_DETECT_SET_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB1_VBUS_DETECT_CLR_POFFSET  0x1a8
#define BPORT1_AB_USB_ANALOG_USB1_VBUS_DETECT_CLR  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB1_VBUS_DETECT_CLR_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB1_VBUS_DETECT_TOG_POFFSET  0x1ac
#define BPORT1_AB_USB_ANALOG_USB1_VBUS_DETECT_TOG  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB1_VBUS_DETECT_TOG_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB1_CHRG_DETECT_POFFSET  0x1b0
#define BPORT1_AB_USB_ANALOG_USB1_CHRG_DETECT  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB1_CHRG_DETECT_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB1_CHRG_DETECT_SET_POFFSET  0x1b4
#define BPORT1_AB_USB_ANALOG_USB1_CHRG_DETECT_SET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB1_CHRG_DETECT_SET_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB1_CHRG_DETECT_CLR_POFFSET  0x1b8
#define BPORT1_AB_USB_ANALOG_USB1_CHRG_DETECT_CLR  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB1_CHRG_DETECT_CLR_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB1_CHRG_DETECT_TOG_POFFSET  0x1bc
#define BPORT1_AB_USB_ANALOG_USB1_CHRG_DETECT_TOG  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB1_CHRG_DETECT_TOG_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB1_VBUS_DETECT_STAT_POFFSET  0x1c0
#define BPORT1_AB_USB_ANALOG_USB1_VBUS_DETECT_STAT  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB1_VBUS_DETECT_STAT_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB1_CHRG_DETECT_STAT_POFFSET  0x1d0
#define BPORT1_AB_USB_ANALOG_USB1_CHRG_DETECT_STAT  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB1_CHRG_DETECT_STAT_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB1_MISC_POFFSET  0x1f0
#define BPORT1_AB_USB_ANALOG_USB1_MISC  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB1_MISC_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB1_MISC_SET_POFFSET  0x1f4
#define BPORT1_AB_USB_ANALOG_USB1_MISC_SET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB1_MISC_SET_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB1_MISC_CLR_POFFSET  0x1f8
#define BPORT1_AB_USB_ANALOG_USB1_MISC_CLR  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB1_MISC_CLR_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB1_MISC_TOG_POFFSET  0x1fc
#define BPORT1_AB_USB_ANALOG_USB1_MISC_TOG  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB1_MISC_TOG_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB2_VBUS_DETECT_POFFSET  0x200
#define BPORT1_AB_USB_ANALOG_USB2_VBUS_DETECT  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB2_VBUS_DETECT_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB2_VBUS_DETECT_SET_POFFSET  0x204
#define BPORT1_AB_USB_ANALOG_USB2_VBUS_DETECT_SET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB2_VBUS_DETECT_SET_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB2_VBUS_DETECT_CLR_POFFSET  0x208
#define BPORT1_AB_USB_ANALOG_USB2_VBUS_DETECT_CLR  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB2_VBUS_DETECT_CLR_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB2_VBUS_DETECT_TOG_POFFSET  0x20c
#define BPORT1_AB_USB_ANALOG_USB2_VBUS_DETECT_TOG  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB2_VBUS_DETECT_TOG_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB2_CHRG_DETECT_POFFSET  0x210
#define BPORT1_AB_USB_ANALOG_USB2_CHRG_DETECT  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB2_CHRG_DETECT_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB2_CHRG_DETECT_SET_POFFSET  0x214
#define BPORT1_AB_USB_ANALOG_USB2_CHRG_DETECT_SET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB2_CHRG_DETECT_SET_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB2_CHRG_DETECT_CLR_POFFSET  0x218
#define BPORT1_AB_USB_ANALOG_USB2_CHRG_DETECT_CLR  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB2_CHRG_DETECT_CLR_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB2_CHRG_DETECT_TOG_POFFSET  0x21c
#define BPORT1_AB_USB_ANALOG_USB2_CHRG_DETECT_TOG  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB2_CHRG_DETECT_TOG_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB2_VBUS_DETECT_STAT_POFFSET  0x220
#define BPORT1_AB_USB_ANALOG_USB2_VBUS_DETECT_STAT  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB2_VBUS_DETECT_STAT_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB2_CHRG_DETECT_STAT_POFFSET  0x230
#define BPORT1_AB_USB_ANALOG_USB2_CHRG_DETECT_STAT  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB2_CHRG_DETECT_STAT_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB2_MISC_POFFSET  0x250
#define BPORT1_AB_USB_ANALOG_USB2_MISC  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB2_MISC_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB2_MISC_SET_POFFSET  0x254
#define BPORT1_AB_USB_ANALOG_USB2_MISC_SET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB2_MISC_SET_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB2_MISC_CLR_POFFSET  0x258
#define BPORT1_AB_USB_ANALOG_USB2_MISC_CLR  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB2_MISC_CLR_POFFSET)

#define BPORT1_AB_USB_ANALOG_USB2_MISC_TOG_POFFSET  0x25c
#define BPORT1_AB_USB_ANALOG_USB2_MISC_TOG  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_USB2_MISC_TOG_POFFSET)

#define BPORT1_AB_USB_ANALOG_DIGPROG_POFFSET  0x260
#define BPORT1_AB_USB_ANALOG_DIGPROG    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_DIGPROG_POFFSET)

#define BPORT1_AB_USB_ANALOG_DIGPROG_SET_POFFSET  0x264
#define BPORT1_AB_USB_ANALOG_DIGPROG_SET  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_DIGPROG_SET_POFFSET)

#define BPORT1_AB_USB_ANALOG_DIGPROG_CLR_POFFSET  0x268
#define BPORT1_AB_USB_ANALOG_DIGPROG_CLR  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_DIGPROG_CLR_POFFSET)

#define BPORT1_AB_USB_ANALOG_DIGPROG_TOG_POFFSET  0x26c
#define BPORT1_AB_USB_ANALOG_DIGPROG_TOG  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_USB_ANALOG_DIGPROG_TOG_POFFSET)

#define BPORT1_AB_BUFFER_POFFSET        0x0
#define BPORT1_AB_BUFFER                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BUFFER_POFFSET)
#define BPORT1_AB_BUFFER_BYTES          0x1000


#endif

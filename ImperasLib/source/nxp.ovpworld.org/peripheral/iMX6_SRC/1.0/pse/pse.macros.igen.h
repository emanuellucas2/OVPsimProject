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
#define BPORT1_AB_SRC_SCR_POFFSET       0x0
#define BPORT1_AB_SRC_SCR               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SRC_SCR_POFFSET)
#define BPORT1_AB_SRC_SCR_DBG_RST_MSK   (0x1 << 25)
#define BPORT1_AB_SRC_SCR_DBG_RST_MSK_GET(_v)  ((_v >> 25) & 0x1)
#define BPORT1_AB_SRC_SCR_CORE1EN       (0x1 << 22)
#define BPORT1_AB_SRC_SCR_CORE1EN_GET(_v)  ((_v >> 22) & 0x1)
#define BPORT1_AB_SRC_SCR_CORES_DBG_RST  (0x1 << 21)
#define BPORT1_AB_SRC_SCR_CORES_DBG_RST_GET(_v)  ((_v >> 21) & 0x1)
#define BPORT1_AB_SRC_SCR_CORE1_DBG_RST  (0x1 << 18)
#define BPORT1_AB_SRC_SCR_CORE1_DBG_RST_GET(_v)  ((_v >> 18) & 0x1)
#define BPORT1_AB_SRC_SCR_CORE0_DBG_RST  (0x1 << 17)
#define BPORT1_AB_SRC_SCR_CORE0_DBG_RST_GET(_v)  ((_v >> 17) & 0x1)
#define BPORT1_AB_SRC_SCR_CORE1_RST     (0x1 << 14)
#define BPORT1_AB_SRC_SCR_CORE1_RST_GET(_v)  ((_v >> 14) & 0x1)
#define BPORT1_AB_SRC_SCR_CORE0_RST     (0x1 << 13)
#define BPORT1_AB_SRC_SCR_CORE0_RST_GET(_v)  ((_v >> 13) & 0x1)
#define BPORT1_AB_SRC_SCR_EIM_RST       (0x1 << 11)
#define BPORT1_AB_SRC_SCR_EIM_RST_GET(_v)  ((_v >> 11) & 0x1)
#define BPORT1_AB_SRC_SCR_MSK_WDG_RST   (0xf << 7)
#define BPORT1_AB_SRC_SCR_MSK_WDG_RST_GET(_v)  ((_v >> 7) & 0xf)
#define BPORT1_AB_SRC_SCR_WRM_RST_BYPASS  (0x3 << 5)
#define BPORT1_AB_SRC_SCR_WRM_RST_BYPASS_GET(_v)  ((_v >> 5) & 0x3)
#define BPORT1_AB_SRC_SCR_SW_OPVG_RST   (0x1 << 4)
#define BPORT1_AB_SRC_SCR_SW_OPVG_RST_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_SRC_SCR_SW_IPU1_RST   (0x1 << 3)
#define BPORT1_AB_SRC_SCR_SW_IPU1_RST_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_SRC_SCR_SW_VPU_RST    (0x1 << 2)
#define BPORT1_AB_SRC_SCR_SW_VPU_RST_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_SRC_SCR_SW_GPU_RST    (0x1 << 1)
#define BPORT1_AB_SRC_SCR_SW_GPU_RST_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_SRC_SCR_WARM_RST_EN   0x1
#define BPORT1_AB_SRC_SCR_WARM_RST_EN_GET(_v)  (_v & 0x1)

#define BPORT1_AB_SRC_SBMR1_POFFSET     0x4
#define BPORT1_AB_SRC_SBMR1             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SRC_SBMR1_POFFSET)
#define BPORT1_AB_SRC_SBMR1_BOOT_CFG4   (0xff << 24)
#define BPORT1_AB_SRC_SBMR1_BOOT_CFG4_GET(_v)  ((_v >> 24) & 0xff)
#define BPORT1_AB_SRC_SBMR1_BOOT_CFG3   (0xff << 16)
#define BPORT1_AB_SRC_SBMR1_BOOT_CFG3_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_AB_SRC_SBMR1_BOOT_CFG2   (0xff << 8)
#define BPORT1_AB_SRC_SBMR1_BOOT_CFG2_GET(_v)  ((_v >> 8) & 0xff)
#define BPORT1_AB_SRC_SBMR1_BOOT_CFG1   0xff
#define BPORT1_AB_SRC_SBMR1_BOOT_CFG1_GET(_v)  (_v & 0xff)

#define BPORT1_AB_SRC_SRSR_POFFSET      0x8
#define BPORT1_AB_SRC_SRSR              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SRC_SRSR_POFFSET)
#define BPORT1_AB_SRC_SRSR_WARM_BOOT    (0x1 << 16)
#define BPORT1_AB_SRC_SRSR_WARM_BOOT_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_SRC_SRSR_JTAG_SW_RST  (0x1 << 6)
#define BPORT1_AB_SRC_SRSR_JTAG_SW_RST_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_SRC_SRSR_JTAG_RST     (0x1 << 5)
#define BPORT1_AB_SRC_SRSR_JTAG_RST_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_SRC_SRSR_WDOG_RST     (0x1 << 4)
#define BPORT1_AB_SRC_SRSR_WDOG_RST_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_SRC_SRSR_IPP_USER_RST  (0x1 << 3)
#define BPORT1_AB_SRC_SRSR_IPP_USER_RST_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_SRC_SRSR_CSU_RST      (0x1 << 2)
#define BPORT1_AB_SRC_SRSR_CSU_RST_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_SRC_SRSR_IPP_RST      0x1
#define BPORT1_AB_SRC_SRSR_IPP_RST_GET(_v)  (_v & 0x1)

#define BPORT1_AB_SRC_SISR_POFFSET      0xc
#define BPORT1_AB_SRC_SISR              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SRC_SISR_POFFSET)
#define BPORT1_AB_SRC_SISR_CORE1_WDOG   (0x1 << 6)
#define BPORT1_AB_SRC_SISR_CORE1_WDOG_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_SRC_SISR_CORE0_WDOG   (0x1 << 5)
#define BPORT1_AB_SRC_SISR_CORE0_WDOG_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_SRC_SISR_OP_VG_PASS   (0x1 << 3)
#define BPORT1_AB_SRC_SISR_OP_VG_PASS_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_SRC_SISR_IPU1_PASS    (0x1 << 2)
#define BPORT1_AB_SRC_SISR_IPU1_PASS_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_SRC_SISR_VPU_PASS     (0x1 << 1)
#define BPORT1_AB_SRC_SISR_VPU_PASS_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_SRC_SISR_GPU_PASS     0x1
#define BPORT1_AB_SRC_SISR_GPU_PASS_GET(_v)  (_v & 0x1)

#define BPORT1_AB_SRC_SIMR_POFFSET      0x10
#define BPORT1_AB_SRC_SIMR              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SRC_SIMR_POFFSET)
#define BPORT1_AB_SRC_SIMR_OP_VG_PASS   (0x1 << 3)
#define BPORT1_AB_SRC_SIMR_OP_VG_PASS_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_SRC_SIMR_IPU1_PASS    (0x1 << 2)
#define BPORT1_AB_SRC_SIMR_IPU1_PASS_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_SRC_SIMR_VPU_PASS     (0x1 << 1)
#define BPORT1_AB_SRC_SIMR_VPU_PASS_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_SRC_SIMR_GPU_PASS     0x1
#define BPORT1_AB_SRC_SIMR_GPU_PASS_GET(_v)  (_v & 0x1)

#define BPORT1_AB_SRC_SBMR2_POFFSET     0x14
#define BPORT1_AB_SRC_SBMR2             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SRC_SBMR2_POFFSET)
#define BPORT1_AB_SRC_SBMR2_BMOD        (0x3 << 24)
#define BPORT1_AB_SRC_SBMR2_BMOD_GET(_v)  ((_v >> 24) & 0x3)
#define BPORT1_AB_SRC_SBMR2_BT_FUSE_SEL  (0x1 << 4)
#define BPORT1_AB_SRC_SBMR2_BT_FUSE_SEL_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_SRC_SBMR2_DIR_BT_DIS  (0x1 << 3)
#define BPORT1_AB_SRC_SBMR2_DIR_BT_DIS_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_SRC_SBMR2_SEC_CONFIG  0x3
#define BPORT1_AB_SRC_SBMR2_SEC_CONFIG_GET(_v)  (_v & 0x3)

#define BPORT1_AB_SRC_GPR1_POFFSET      0x18
#define BPORT1_AB_SRC_GPR1              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SRC_GPR1_POFFSET)

#define BPORT1_AB_SRC_GPR2_POFFSET      0x1c
#define BPORT1_AB_SRC_GPR2              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SRC_GPR2_POFFSET)

#define BPORT1_AB_SRC_GPR3_POFFSET      0x20
#define BPORT1_AB_SRC_GPR3              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SRC_GPR3_POFFSET)

#define BPORT1_AB_SRC_GPR4_POFFSET      0x24
#define BPORT1_AB_SRC_GPR4              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SRC_GPR4_POFFSET)

#define BPORT1_AB_SRC_GPR5_POFFSET      0x28
#define BPORT1_AB_SRC_GPR5              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SRC_GPR5_POFFSET)

#define BPORT1_AB_SRC_GPR6_POFFSET      0x2c
#define BPORT1_AB_SRC_GPR6              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SRC_GPR6_POFFSET)

#define BPORT1_AB_SRC_GPR7_POFFSET      0x30
#define BPORT1_AB_SRC_GPR7              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SRC_GPR7_POFFSET)

#define BPORT1_AB_SRC_GPR8_POFFSET      0x34
#define BPORT1_AB_SRC_GPR8              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SRC_GPR8_POFFSET)

#define BPORT1_AB_SRC_GPR9_POFFSET      0x38
#define BPORT1_AB_SRC_GPR9              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SRC_GPR9_POFFSET)

#define BPORT1_AB_SRC_GPR10_POFFSET     0x3c
#define BPORT1_AB_SRC_GPR10             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SRC_GPR10_POFFSET)

#define BPORT1_AB_BUFFER_POFFSET        0x0
#define BPORT1_AB_BUFFER                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BUFFER_POFFSET)
#define BPORT1_AB_BUFFER_BYTES          0x4000


#endif

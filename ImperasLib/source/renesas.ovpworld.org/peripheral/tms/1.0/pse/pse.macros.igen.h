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

// Set the macro 'TMSP0' to the base of port 'TMSP0'
#ifndef TMSP0
#error TMSP0 is undefined. It needs to be set to the port base address
#endif


#define TMSP0_REG0_POFFSET              0x0
#define TMSP0_REG0_CTL0_POFFSET         0x0
#define TMSP0_REG0_CTL0                 (TMSP0 + TMSP0_REG0_POFFSET + TMSP0_REG0_CTL0_POFFSET)
#define TMSP0_REG0_CTL0_CKS             0x7
#define TMSP0_REG0_CTL0_CKS_GET(_v)     (_v & 0x7)
#define TMSP0_REG0_CTL0_CE              (0x1 << 7)
#define TMSP0_REG0_CTL0_CE_GET(_v)      ((_v >> 7) & 0x1)

#define TMSP0_REG0_CTL1_POFFSET         0x1
#define TMSP0_REG0_CTL1                 (TMSP0 + TMSP0_REG0_POFFSET + TMSP0_REG0_CTL1_POFFSET)
#define TMSP0_REG0_CTL1_MD              0xf
#define TMSP0_REG0_CTL1_MD_GET(_v)      (_v & 0xf)
#define TMSP0_REG0_CTL1_EEE             (0x1 << 5)
#define TMSP0_REG0_CTL1_EEE_GET(_v)     ((_v >> 5) & 0x1)
#define TMSP0_REG0_CTL1_EST             (0x1 << 6)
#define TMSP0_REG0_CTL1_EST_GET(_v)     ((_v >> 6) & 0x1)

#define TMSP0_REG1_POFFSET              0x2
#define TMSP0_REG1_IOC0_POFFSET         0x0
#define TMSP0_REG1_IOC0                 (TMSP0 + TMSP0_REG1_POFFSET + TMSP0_REG1_IOC0_POFFSET)
#define TMSP0_REG1_IOC0_OE0             0x1
#define TMSP0_REG1_IOC0_OE0_GET(_v)     (_v & 0x1)
#define TMSP0_REG1_IOC0_OL0             (0x1 << 1)
#define TMSP0_REG1_IOC0_OL0_GET(_v)     ((_v >> 1) & 0x1)
#define TMSP0_REG1_IOC0_OE1             (0x1 << 2)
#define TMSP0_REG1_IOC0_OE1_GET(_v)     ((_v >> 2) & 0x1)
#define TMSP0_REG1_IOC0_OL1             (0x1 << 3)
#define TMSP0_REG1_IOC0_OL1_GET(_v)     ((_v >> 3) & 0x1)
#define TMSP0_REG1_IOC0_OE2             (0x1 << 4)
#define TMSP0_REG1_IOC0_OE2_GET(_v)     ((_v >> 4) & 0x1)
#define TMSP0_REG1_IOC0_OL2             (0x1 << 5)
#define TMSP0_REG1_IOC0_OL2_GET(_v)     ((_v >> 5) & 0x1)
#define TMSP0_REG1_IOC0_OE3             (0x1 << 6)
#define TMSP0_REG1_IOC0_OE3_GET(_v)     ((_v >> 6) & 0x1)
#define TMSP0_REG1_IOC0_OL3             (0x1 << 7)
#define TMSP0_REG1_IOC0_OL3_GET(_v)     ((_v >> 7) & 0x1)
#define TMSP0_REG1_IOC0_OE4             (0x1 << 8)
#define TMSP0_REG1_IOC0_OE4_GET(_v)     ((_v >> 8) & 0x1)
#define TMSP0_REG1_IOC0_OL4             (0x1 << 9)
#define TMSP0_REG1_IOC0_OL4_GET(_v)     ((_v >> 9) & 0x1)
#define TMSP0_REG1_IOC0_OE5             (0x1 << 10)
#define TMSP0_REG1_IOC0_OE5_GET(_v)     ((_v >> 10) & 0x1)
#define TMSP0_REG1_IOC0_OL5             (0x1 << 11)
#define TMSP0_REG1_IOC0_OL5_GET(_v)     ((_v >> 11) & 0x1)
#define TMSP0_REG1_IOC0_OE6             (0x1 << 12)
#define TMSP0_REG1_IOC0_OE6_GET(_v)     ((_v >> 12) & 0x1)
#define TMSP0_REG1_IOC0_OL6             (0x1 << 13)
#define TMSP0_REG1_IOC0_OL6_GET(_v)     ((_v >> 13) & 0x1)
#define TMSP0_REG1_IOC0_OE7             (0x1 << 14)
#define TMSP0_REG1_IOC0_OE7_GET(_v)     ((_v >> 14) & 0x1)
#define TMSP0_REG1_IOC0_OL7             (0x1 << 15)
#define TMSP0_REG1_IOC0_OL7_GET(_v)     ((_v >> 15) & 0x1)

#define TMSP0_REG2_POFFSET              0x4
#define TMSP0_REG2_IOC2_POFFSET         0x0
#define TMSP0_REG2_IOC2                 (TMSP0 + TMSP0_REG2_POFFSET + TMSP0_REG2_IOC2_POFFSET)
#define TMSP0_REG2_IOC2_ETS             0x3
#define TMSP0_REG2_IOC2_ETS_GET(_v)     (_v & 0x3)
#define TMSP0_REG2_IOC2_EES             (0x3 << 2)
#define TMSP0_REG2_IOC2_EES_GET(_v)     ((_v >> 2) & 0x3)

#define TMSP0_REG2_IOC4_POFFSET         0x1
#define TMSP0_REG2_IOC4                 (TMSP0 + TMSP0_REG2_POFFSET + TMSP0_REG2_IOC4_POFFSET)
#define TMSP0_REG2_IOC4_EOC             0x1
#define TMSP0_REG2_IOC4_EOC_GET(_v)     (_v & 0x1)
#define TMSP0_REG2_IOC4_WOC             (0x1 << 2)
#define TMSP0_REG2_IOC4_WOC_GET(_v)     ((_v >> 2) & 0x1)
#define TMSP0_REG2_IOC4_BA              (0x7 << 4)
#define TMSP0_REG2_IOC4_BA_GET(_v)      ((_v >> 4) & 0x7)

#define TMSP0_REG2_OPT0_POFFSET         0x2
#define TMSP0_REG2_OPT0                 (TMSP0 + TMSP0_REG2_POFFSET + TMSP0_REG2_OPT0_POFFSET)
#define TMSP0_REG2_OPT0_OVF             0x1
#define TMSP0_REG2_OPT0_OVF_GET(_v)     (_v & 0x1)
#define TMSP0_REG2_OPT0_CUF             (0x1 << 1)
#define TMSP0_REG2_OPT0_CUF_GET(_v)     ((_v >> 1) & 0x1)
#define TMSP0_REG2_OPT0_CMS             (0x1 << 2)
#define TMSP0_REG2_OPT0_CMS_GET(_v)     ((_v >> 2) & 0x1)
#define TMSP0_REG2_OPT0_DSE             (0x1 << 3)
#define TMSP0_REG2_OPT0_DSE_GET(_v)     ((_v >> 3) & 0x1)

#define TMSP0_REG2_OPT4_POFFSET         0x4
#define TMSP0_REG2_OPT4                 (TMSP0 + TMSP0_REG2_POFFSET + TMSP0_REG2_OPT4_POFFSET)
#define TMSP0_REG2_OPT4_IPC             0x7
#define TMSP0_REG2_OPT4_IPC_GET(_v)     (_v & 0x7)
#define TMSP0_REG2_OPT4_PSC             (0x1 << 3)
#define TMSP0_REG2_OPT4_PSC_GET(_v)     ((_v >> 3) & 0x1)
#define TMSP0_REG2_OPT4_SOC             (0x1 << 7)
#define TMSP0_REG2_OPT4_SOC_GET(_v)     ((_v >> 7) & 0x1)

#define TMSP0_REG2_OPT5_POFFSET         0x5
#define TMSP0_REG2_OPT5                 (TMSP0 + TMSP0_REG2_POFFSET + TMSP0_REG2_OPT5_POFFSET)
#define TMSP0_REG2_OPT5_OPF             0x7
#define TMSP0_REG2_OPT5_OPF_GET(_v)     (_v & 0x7)
#define TMSP0_REG2_OPT5_TSF             (0x1 << 3)
#define TMSP0_REG2_OPT5_TSF_GET(_v)     ((_v >> 3) & 0x1)
#define TMSP0_REG2_OPT5_PTS             (0x1 << 4)
#define TMSP0_REG2_OPT5_PTS_GET(_v)     ((_v >> 4) & 0x1)
#define TMSP0_REG2_OPT5_PSS             (0x1 << 5)
#define TMSP0_REG2_OPT5_PSS_GET(_v)     ((_v >> 5) & 0x1)
#define TMSP0_REG2_OPT5_POT             (0x1 << 6)
#define TMSP0_REG2_OPT5_POT_GET(_v)     ((_v >> 6) & 0x1)
#define TMSP0_REG2_OPT5_ADC             (0x1 << 7)
#define TMSP0_REG2_OPT5_ADC_GET(_v)     ((_v >> 7) & 0x1)

#define TMSP0_REG2_OPT7_POFFSET         0x3
#define TMSP0_REG2_OPT7                 (TMSP0 + TMSP0_REG2_POFFSET + TMSP0_REG2_OPT7_POFFSET)
#define TMSP0_REG2_OPT7_TOS             0x1
#define TMSP0_REG2_OPT7_TOS_GET(_v)     (_v & 0x1)
#define TMSP0_REG2_OPT7_PTC             (0x3 << 1)
#define TMSP0_REG2_OPT7_PTC_GET(_v)     ((_v >> 1) & 0x3)
#define TMSP0_REG2_OPT7_TDC             (0x1 << 3)
#define TMSP0_REG2_OPT7_TDC_GET(_v)     ((_v >> 3) & 0x1)
#define TMSP0_REG2_OPT7_PPC             (0x1 << 4)
#define TMSP0_REG2_OPT7_PPC_GET(_v)     ((_v >> 4) & 0x1)
#define TMSP0_REG2_OPT7_IDC             (0x1 << 5)
#define TMSP0_REG2_OPT7_IDC_GET(_v)     ((_v >> 5) & 0x1)

#define TMSP0_REG3_POFFSET              0xa
#define TMSP0_REG3_OPT1_POFFSET         0x0
#define TMSP0_REG3_OPT1                 (TMSP0 + TMSP0_REG3_POFFSET + TMSP0_REG3_OPT1_POFFSET)
#define TMSP0_REG3_OPT1_ID              0x1f
#define TMSP0_REG3_OPT1_ID_GET(_v)      (_v & 0x1f)
#define TMSP0_REG3_OPT1_RDE             (0x1 << 5)
#define TMSP0_REG3_OPT1_RDE_GET(_v)     ((_v >> 5) & 0x1)
#define TMSP0_REG3_OPT1_IOE             (0x1 << 6)
#define TMSP0_REG3_OPT1_IOE_GET(_v)     ((_v >> 6) & 0x1)
#define TMSP0_REG3_OPT1_ICE             (0x1 << 7)
#define TMSP0_REG3_OPT1_ICE_GET(_v)     ((_v >> 7) & 0x1)
#define TMSP0_REG3_OPT1_RBE             (0x1 << 8)
#define TMSP0_REG3_OPT1_RBE_GET(_v)     ((_v >> 8) & 0x1)
#define TMSP0_REG3_OPT1_RTE             (0x1 << 9)
#define TMSP0_REG3_OPT1_RTE_GET(_v)     ((_v >> 9) & 0x1)

#define TMSP0_REG3_OPT2_POFFSET         0x16
#define TMSP0_REG3_OPT2                 (TMSP0 + TMSP0_REG3_POFFSET + TMSP0_REG3_OPT2_POFFSET)
#define TMSP0_REG3_OPT2_AT00            0x1
#define TMSP0_REG3_OPT2_AT00_GET(_v)    (_v & 0x1)
#define TMSP0_REG3_OPT2_AT01            (0x1 << 1)
#define TMSP0_REG3_OPT2_AT01_GET(_v)    ((_v >> 1) & 0x1)
#define TMSP0_REG3_OPT2_AT02            (0x1 << 2)
#define TMSP0_REG3_OPT2_AT02_GET(_v)    ((_v >> 2) & 0x1)
#define TMSP0_REG3_OPT2_AT03            (0x1 << 3)
#define TMSP0_REG3_OPT2_AT03_GET(_v)    ((_v >> 3) & 0x1)
#define TMSP0_REG3_OPT2_AT04            (0x1 << 4)
#define TMSP0_REG3_OPT2_AT04_GET(_v)    ((_v >> 4) & 0x1)
#define TMSP0_REG3_OPT2_AT05            (0x1 << 5)
#define TMSP0_REG3_OPT2_AT05_GET(_v)    ((_v >> 5) & 0x1)
#define TMSP0_REG3_OPT2_AT06            (0x1 << 6)
#define TMSP0_REG3_OPT2_AT06_GET(_v)    ((_v >> 6) & 0x1)
#define TMSP0_REG3_OPT2_AT07            (0x1 << 7)
#define TMSP0_REG3_OPT2_AT07_GET(_v)    ((_v >> 7) & 0x1)
#define TMSP0_REG3_OPT2_ACC0            (0x1 << 8)
#define TMSP0_REG3_OPT2_ACC0_GET(_v)    ((_v >> 8) & 0x1)
#define TMSP0_REG3_OPT2_ACC1            (0x1 << 9)
#define TMSP0_REG3_OPT2_ACC1_GET(_v)    ((_v >> 9) & 0x1)

#define TMSP0_REG3_OPT3_POFFSET         0x18
#define TMSP0_REG3_OPT3                 (TMSP0 + TMSP0_REG3_POFFSET + TMSP0_REG3_OPT3_POFFSET)
#define TMSP0_REG3_OPT3_AT00            0x1
#define TMSP0_REG3_OPT3_AT00_GET(_v)    (_v & 0x1)
#define TMSP0_REG3_OPT3_AT01            (0x1 << 1)
#define TMSP0_REG3_OPT3_AT01_GET(_v)    ((_v >> 1) & 0x1)
#define TMSP0_REG3_OPT3_AT02            (0x1 << 2)
#define TMSP0_REG3_OPT3_AT02_GET(_v)    ((_v >> 2) & 0x1)
#define TMSP0_REG3_OPT3_AT03            (0x1 << 3)
#define TMSP0_REG3_OPT3_AT03_GET(_v)    ((_v >> 3) & 0x1)
#define TMSP0_REG3_OPT3_AT04            (0x1 << 4)
#define TMSP0_REG3_OPT3_AT04_GET(_v)    ((_v >> 4) & 0x1)
#define TMSP0_REG3_OPT3_AT05            (0x1 << 5)
#define TMSP0_REG3_OPT3_AT05_GET(_v)    ((_v >> 5) & 0x1)
#define TMSP0_REG3_OPT3_AT06            (0x1 << 6)
#define TMSP0_REG3_OPT3_AT06_GET(_v)    ((_v >> 6) & 0x1)
#define TMSP0_REG3_OPT3_AT07            (0x1 << 7)
#define TMSP0_REG3_OPT3_AT07_GET(_v)    ((_v >> 7) & 0x1)
#define TMSP0_REG3_OPT3_ACC2            (0x1 << 8)
#define TMSP0_REG3_OPT3_ACC2_GET(_v)    ((_v >> 8) & 0x1)
#define TMSP0_REG3_OPT3_ACC3            (0x1 << 9)
#define TMSP0_REG3_OPT3_ACC3_GET(_v)    ((_v >> 9) & 0x1)

#define TMSP0_REG3_OPT6_POFFSET         0x1a
#define TMSP0_REG3_OPT6                 (TMSP0 + TMSP0_REG3_POFFSET + TMSP0_REG3_OPT6_POFFSET)
#define TMSP0_REG3_OPT6_RSF             0x1
#define TMSP0_REG3_OPT6_RSF_GET(_v)     (_v & 0x1)
#define TMSP0_REG3_OPT6_SUF             (0x1 << 1)
#define TMSP0_REG3_OPT6_SUF_GET(_v)     ((_v >> 1) & 0x1)
#define TMSP0_REG3_OPT6_TBF             (0x1 << 2)
#define TMSP0_REG3_OPT6_TBF_GET(_v)     ((_v >> 2) & 0x1)
#define TMSP0_REG3_OPT6_PEF             (0x1 << 3)
#define TMSP0_REG3_OPT6_PEF_GET(_v)     ((_v >> 3) & 0x1)
#define TMSP0_REG3_OPT6_PRF             (0x1 << 4)
#define TMSP0_REG3_OPT6_PRF_GET(_v)     ((_v >> 4) & 0x1)
#define TMSP0_REG3_OPT6_NDF             (0x1 << 5)
#define TMSP0_REG3_OPT6_NDF_GET(_v)     ((_v >> 5) & 0x1)
#define TMSP0_REG3_OPT6_TDF             (0x1 << 6)
#define TMSP0_REG3_OPT6_TDF_GET(_v)     ((_v >> 6) & 0x1)
#define TMSP0_REG3_OPT6_PTF             (0x1 << 7)
#define TMSP0_REG3_OPT6_PTF_GET(_v)     ((_v >> 7) & 0x1)
#define TMSP0_REG3_OPT6_PPF             (0x1 << 8)
#define TMSP0_REG3_OPT6_PPF_GET(_v)     ((_v >> 8) & 0x1)

#define TMSP0_REG3_DTC0_POFFSET         0x4
#define TMSP0_REG3_DTC0                 (TMSP0 + TMSP0_REG3_POFFSET + TMSP0_REG3_DTC0_POFFSET)
#define TMSP0_REG3_DTC0_DTV             (0x1ff << 1)
#define TMSP0_REG3_DTC0_DTV_GET(_v)     ((_v >> 1) & 0x1ff)

#define TMSP0_REG3_DTC1_POFFSET         0x2
#define TMSP0_REG3_DTC1                 (TMSP0 + TMSP0_REG3_POFFSET + TMSP0_REG3_DTC1_POFFSET)
#define TMSP0_REG3_DTC1_DTV             (0x1ff << 1)
#define TMSP0_REG3_DTC1_DTV_GET(_v)     ((_v >> 1) & 0x1ff)

#define TMSP0_REG3_PAT0_POFFSET         0xc
#define TMSP0_REG3_PAT0                 (TMSP0 + TMSP0_REG3_POFFSET + TMSP0_REG3_PAT0_POFFSET)
#define TMSP0_REG3_PAT0_SP0             0xf
#define TMSP0_REG3_PAT0_SP0_GET(_v)     (_v & 0xf)
#define TMSP0_REG3_PAT0_SP1             (0xf << 4)
#define TMSP0_REG3_PAT0_SP1_GET(_v)     ((_v >> 4) & 0xf)
#define TMSP0_REG3_PAT0_SP2             (0xf << 8)
#define TMSP0_REG3_PAT0_SP2_GET(_v)     ((_v >> 8) & 0xf)
#define TMSP0_REG3_PAT0_SP3             (0xf << 12)
#define TMSP0_REG3_PAT0_SP3_GET(_v)     ((_v >> 12) & 0xf)

#define TMSP0_REG3_PAT1_POFFSET         0xa
#define TMSP0_REG3_PAT1                 (TMSP0 + TMSP0_REG3_POFFSET + TMSP0_REG3_PAT1_POFFSET)
#define TMSP0_REG3_PAT1_SP4             0xf
#define TMSP0_REG3_PAT1_SP4_GET(_v)     (_v & 0xf)
#define TMSP0_REG3_PAT1_SP5             (0xf << 4)
#define TMSP0_REG3_PAT1_SP5_GET(_v)     ((_v >> 4) & 0xf)
#define TMSP0_REG3_PAT1_SP6             (0xf << 8)
#define TMSP0_REG3_PAT1_SP6_GET(_v)     ((_v >> 8) & 0xf)
#define TMSP0_REG3_PAT1_SP7             (0xf << 12)
#define TMSP0_REG3_PAT1_SP7_GET(_v)     ((_v >> 12) & 0xf)

#define TMSP0_REG3_CCR0_POFFSET         0xe
#define TMSP0_REG3_CCR0                 (TMSP0 + TMSP0_REG3_POFFSET + TMSP0_REG3_CCR0_POFFSET)

#define TMSP0_REG3_CCR1_POFFSET         0x14
#define TMSP0_REG3_CCR1                 (TMSP0 + TMSP0_REG3_POFFSET + TMSP0_REG3_CCR1_POFFSET)

#define TMSP0_REG3_CCR2_POFFSET         0x12
#define TMSP0_REG3_CCR2                 (TMSP0 + TMSP0_REG3_POFFSET + TMSP0_REG3_CCR2_POFFSET)

#define TMSP0_REG3_CCR3_POFFSET         0x10
#define TMSP0_REG3_CCR3                 (TMSP0 + TMSP0_REG3_POFFSET + TMSP0_REG3_CCR3_POFFSET)

#define TMSP0_REG3_CCR4_POFFSET         0x8
#define TMSP0_REG3_CCR4                 (TMSP0 + TMSP0_REG3_POFFSET + TMSP0_REG3_CCR4_POFFSET)

#define TMSP0_REG3_CCR5_POFFSET         0x6
#define TMSP0_REG3_CCR5                 (TMSP0 + TMSP0_REG3_POFFSET + TMSP0_REG3_CCR5_POFFSET)

#define TMSP0_REG3_CNT_POFFSET          0x1c
#define TMSP0_REG3_CNT                  (TMSP0 + TMSP0_REG3_POFFSET + TMSP0_REG3_CNT_POFFSET)
#define TMSP0_REG3_CNT_MODE             0x1
#define TMSP0_REG3_CNT_MODE_GET(_v)     (_v & 0x1)
#define TMSP0_REG3_CNT_VAL              (0x7fff << 1)
#define TMSP0_REG3_CNT_VAL_GET(_v)      ((_v >> 1) & 0x7fff)

#define TMSP0_REG3_SBC_POFFSET          0x1e
#define TMSP0_REG3_SBC                  (TMSP0 + TMSP0_REG3_POFFSET + TMSP0_REG3_SBC_POFFSET)
#define TMSP0_REG3_SBC_MODE             0x1
#define TMSP0_REG3_SBC_MODE_GET(_v)     (_v & 0x1)
#define TMSP0_REG3_SBC_SVAL             (0x7fff << 1)
#define TMSP0_REG3_SBC_SVAL_GET(_v)     ((_v >> 1) & 0x7fff)


#endif

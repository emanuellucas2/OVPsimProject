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

// Set the macro 'TMTP0' to the base of port 'TMTP0'
#ifndef TMTP0
#error TMTP0 is undefined. It needs to be set to the port base address
#endif
// Set the macro 'TMTP1' to the base of port 'TMTP1'
#ifndef TMTP1
#error TMTP1 is undefined. It needs to be set to the port base address
#endif


#define TMTP0_REG0_POFFSET              0x0
#define TMTP0_REG0_CTL0_POFFSET         0x0
#define TMTP0_REG0_CTL0                 (TMTP0 + TMTP0_REG0_POFFSET + TMTP0_REG0_CTL0_POFFSET)
#define TMTP0_REG0_CTL0_CKS             0x7
#define TMTP0_REG0_CTL0_CKS_GET(_v)     (_v & 0x7)
#define TMTP0_REG0_CTL0_CE              (0x1 << 7)
#define TMTP0_REG0_CTL0_CE_GET(_v)      ((_v >> 7) & 0x1)

#define TMTP0_REG0_CTL1_POFFSET         0x1
#define TMTP0_REG0_CTL1                 (TMTP0 + TMTP0_REG0_POFFSET + TMTP0_REG0_CTL1_POFFSET)
#define TMTP0_REG0_CTL1_MD              0xf
#define TMTP0_REG0_CTL1_MD_GET(_v)      (_v & 0xf)
#define TMTP0_REG0_CTL1_EEE             (0x1 << 5)
#define TMTP0_REG0_CTL1_EEE_GET(_v)     ((_v >> 5) & 0x1)
#define TMTP0_REG0_CTL1_EST             (0x1 << 6)
#define TMTP0_REG0_CTL1_EST_GET(_v)     ((_v >> 6) & 0x1)

#define TMTP0_REG0_CTL2_POFFSET         0x2
#define TMTP0_REG0_CTL2                 (TMTP0 + TMTP0_REG0_POFFSET + TMTP0_REG0_CTL2_POFFSET)
#define TMTP0_REG0_CTL2_UDS             0x3
#define TMTP0_REG0_CTL2_UDS_GET(_v)     (_v & 0x3)
#define TMTP0_REG0_CTL2_ECM             (0x3 << 2)
#define TMTP0_REG0_CTL2_ECM_GET(_v)     ((_v >> 2) & 0x3)
#define TMTP0_REG0_CTL2_LDE             (0x1 << 4)
#define TMTP0_REG0_CTL2_LDE_GET(_v)     ((_v >> 4) & 0x1)
#define TMTP0_REG0_CTL2_ECC             (0x1 << 7)
#define TMTP0_REG0_CTL2_ECC_GET(_v)     ((_v >> 7) & 0x1)

#define TMTP0_REG0_IOC0_POFFSET         0x3
#define TMTP0_REG0_IOC0                 (TMTP0 + TMTP0_REG0_POFFSET + TMTP0_REG0_IOC0_POFFSET)
#define TMTP0_REG0_IOC0_OE0             0x1
#define TMTP0_REG0_IOC0_OE0_GET(_v)     (_v & 0x1)
#define TMTP0_REG0_IOC0_OL0             (0x1 << 1)
#define TMTP0_REG0_IOC0_OL0_GET(_v)     ((_v >> 1) & 0x1)
#define TMTP0_REG0_IOC0_OE1             (0x1 << 2)
#define TMTP0_REG0_IOC0_OE1_GET(_v)     ((_v >> 2) & 0x1)
#define TMTP0_REG0_IOC0_OL1             (0x1 << 3)
#define TMTP0_REG0_IOC0_OL1_GET(_v)     ((_v >> 3) & 0x1)

#define TMTP0_REG0_IOC1_POFFSET         0x4
#define TMTP0_REG0_IOC1                 (TMTP0 + TMTP0_REG0_POFFSET + TMTP0_REG0_IOC1_POFFSET)
#define TMTP0_REG0_IOC1_IS              0xf
#define TMTP0_REG0_IOC1_IS_GET(_v)      (_v & 0xf)

#define TMTP0_REG0_IOC2_POFFSET         0x5
#define TMTP0_REG0_IOC2                 (TMTP0 + TMTP0_REG0_POFFSET + TMTP0_REG0_IOC2_POFFSET)
#define TMTP0_REG0_IOC2_ETS             0x3
#define TMTP0_REG0_IOC2_ETS_GET(_v)     (_v & 0x3)
#define TMTP0_REG0_IOC2_EES             (0x3 << 2)
#define TMTP0_REG0_IOC2_EES_GET(_v)     ((_v >> 2) & 0x3)

#define TMTP0_REG0_IOC3_POFFSET         0x6
#define TMTP0_REG0_IOC3                 (TMTP0 + TMTP0_REG0_POFFSET + TMTP0_REG0_IOC3_POFFSET)
#define TMTP0_REG0_IOC3_EIS             0x3
#define TMTP0_REG0_IOC3_EIS_GET(_v)     (_v & 0x3)
#define TMTP0_REG0_IOC3_ECS             (0x3 << 2)
#define TMTP0_REG0_IOC3_ECS_GET(_v)     ((_v >> 2) & 0x3)
#define TMTP0_REG0_IOC3_ACL             (0x1 << 4)
#define TMTP0_REG0_IOC3_ACL_GET(_v)     ((_v >> 4) & 0x1)
#define TMTP0_REG0_IOC3_BCL             (0x1 << 5)
#define TMTP0_REG0_IOC3_BCL_GET(_v)     ((_v >> 5) & 0x1)
#define TMTP0_REG0_IOC3_ZCL             (0x1 << 6)
#define TMTP0_REG0_IOC3_ZCL_GET(_v)     ((_v >> 6) & 0x1)
#define TMTP0_REG0_IOC3_SCE             (0x1 << 7)
#define TMTP0_REG0_IOC3_SCE_GET(_v)     ((_v >> 7) & 0x1)

#define TMTP0_REG0_OPT0_POFFSET         0x7
#define TMTP0_REG0_OPT0                 (TMTP0 + TMTP0_REG0_POFFSET + TMTP0_REG0_OPT0_POFFSET)
#define TMTP0_REG0_OPT0_OVF             0x1
#define TMTP0_REG0_OPT0_OVF_GET(_v)     (_v & 0x1)
#define TMTP0_REG0_OPT0_CCS             (0x3 << 4)
#define TMTP0_REG0_OPT0_CCS_GET(_v)     ((_v >> 4) & 0x3)

#define TMTP0_REG0_OPT1_POFFSET         0x8
#define TMTP0_REG0_OPT1                 (TMTP0 + TMTP0_REG0_POFFSET + TMTP0_REG0_OPT1_POFFSET)
#define TMTP0_REG0_OPT1_ESF             0x1
#define TMTP0_REG0_OPT1_ESF_GET(_v)     (_v & 0x1)
#define TMTP0_REG0_OPT1_EOF             (0x1 << 1)
#define TMTP0_REG0_OPT1_EOF_GET(_v)     ((_v >> 1) & 0x1)
#define TMTP0_REG0_OPT1_EUF             (0x1 << 2)
#define TMTP0_REG0_OPT1_EUF_GET(_v)     ((_v >> 2) & 0x1)

#define TMTP0_REG0_OPT2_POFFSET         0x9
#define TMTP0_REG0_OPT2                 (TMTP0 + TMTP0_REG0_POFFSET + TMTP0_REG0_OPT2_POFFSET)
#define TMTP0_REG0_OPT2_RSF             0x1
#define TMTP0_REG0_OPT2_RSF_GET(_v)     (_v & 0x1)

#define TMTP0_REG1_POFFSET              0xa
#define TMTP0_REG1_CCR0_POFFSET         0x0
#define TMTP0_REG1_CCR0                 (TMTP0 + TMTP0_REG1_POFFSET + TMTP0_REG1_CCR0_POFFSET)

#define TMTP0_REG1_CCR1_POFFSET         0x2
#define TMTP0_REG1_CCR1                 (TMTP0 + TMTP0_REG1_POFFSET + TMTP0_REG1_CCR1_POFFSET)

#define TMTP0_REG1_CNT_POFFSET          0x4
#define TMTP0_REG1_CNT                  (TMTP0 + TMTP0_REG1_POFFSET + TMTP0_REG1_CNT_POFFSET)


#define TMTP1_REG0_POFFSET              0x0
#define TMTP1_REG0_TCW_POFFSET          0x0
#define TMTP1_REG0_TCW                  (TMTP1 + TMTP1_REG0_POFFSET + TMTP1_REG0_TCW_POFFSET)


#endif

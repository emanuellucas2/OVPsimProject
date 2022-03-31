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

// Set the macro 'CSIEP0' to the base of port 'CSIEP0'
#ifndef CSIEP0
#error CSIEP0 is undefined. It needs to be set to the port base address
#endif


#define CSIEP0_REG0_POFFSET             0x0
#define CSIEP0_REG0_CTL0_POFFSET        0x0
#define CSIEP0_REG0_CTL0                (CSIEP0 + CSIEP0_REG0_POFFSET + CSIEP0_REG0_CTL0_POFFSET)
#define CSIEP0_REG0_CTL0_CSM            0x1
#define CSIEP0_REG0_CTL0_CSM_GET(_v)    (_v & 0x1)
#define CSIEP0_REG0_CTL0_WE             (0x1 << 1)
#define CSIEP0_REG0_CTL0_WE_GET(_v)     ((_v >> 1) & 0x1)
#define CSIEP0_REG0_CTL0_SIT            (0x1 << 2)
#define CSIEP0_REG0_CTL0_SIT_GET(_v)    ((_v >> 2) & 0x1)
#define CSIEP0_REG0_CTL0_DIR            (0x1 << 3)
#define CSIEP0_REG0_CTL0_DIR_GET(_v)    ((_v >> 3) & 0x1)
#define CSIEP0_REG0_CTL0_TMS            (0x1 << 4)
#define CSIEP0_REG0_CTL0_TMS_GET(_v)    ((_v >> 4) & 0x1)
#define CSIEP0_REG0_CTL0_RXE            (0x1 << 5)
#define CSIEP0_REG0_CTL0_RXE_GET(_v)    ((_v >> 5) & 0x1)
#define CSIEP0_REG0_CTL0_TXE            (0x1 << 6)
#define CSIEP0_REG0_CTL0_TXE_GET(_v)    ((_v >> 6) & 0x1)
#define CSIEP0_REG0_CTL0_PWR            (0x1 << 7)
#define CSIEP0_REG0_CTL0_PWR_GET(_v)    ((_v >> 7) & 0x1)

#define CSIEP0_REG0_CTL1_POFFSET        0x1
#define CSIEP0_REG0_CTL1                (CSIEP0 + CSIEP0_REG0_POFFSET + CSIEP0_REG0_CTL1_POFFSET)
#define CSIEP0_REG0_CTL1_CKS            0x7
#define CSIEP0_REG0_CTL1_CKS_GET(_v)    (_v & 0x7)
#define CSIEP0_REG0_CTL1_DAP            (0x1 << 3)
#define CSIEP0_REG0_CTL1_DAP_GET(_v)    ((_v >> 3) & 0x1)
#define CSIEP0_REG0_CTL1_CKP            (0x1 << 4)
#define CSIEP0_REG0_CTL1_CKP_GET(_v)    ((_v >> 4) & 0x1)
#define CSIEP0_REG0_CTL1_MDL            (0x7 << 5)
#define CSIEP0_REG0_CTL1_MDL_GET(_v)    ((_v >> 5) & 0x7)

#define CSIEP0_REG1_POFFSET             0x2
#define CSIEP0_REG1_RX_POFFSET          0x0
#define CSIEP0_REG1_RX                  (CSIEP0 + CSIEP0_REG1_POFFSET + CSIEP0_REG1_RX_POFFSET)

#define CSIEP0_REG1_CS_POFFSET          0x2
#define CSIEP0_REG1_CS                  (CSIEP0 + CSIEP0_REG1_POFFSET + CSIEP0_REG1_CS_POFFSET)
#define CSIEP0_REG1_CS_CS               0xf
#define CSIEP0_REG1_CS_CS_GET(_v)       (_v & 0xf)

#define CSIEP0_REG1_TX_POFFSET          0x4
#define CSIEP0_REG1_TX                  (CSIEP0 + CSIEP0_REG1_POFFSET + CSIEP0_REG1_TX_POFFSET)

#define CSIEP0_REG2_POFFSET             0x8
#define CSIEP0_REG2_STR_POFFSET         0x0
#define CSIEP0_REG2_STR                 (CSIEP0 + CSIEP0_REG2_POFFSET + CSIEP0_REG2_STR_POFFSET)
#define CSIEP0_REG2_STR_SFP             0xf
#define CSIEP0_REG2_STR_SFP_GET(_v)     (_v & 0xf)
#define CSIEP0_REG2_STR_TSF             (0x1 << 4)
#define CSIEP0_REG2_STR_TSF_GET(_v)     ((_v >> 4) & 0x1)
#define CSIEP0_REG2_STR_EMF             (0x1 << 5)
#define CSIEP0_REG2_STR_EMF_GET(_v)     ((_v >> 5) & 0x1)
#define CSIEP0_REG2_STR_FLF             (0x1 << 6)
#define CSIEP0_REG2_STR_FLF_GET(_v)     ((_v >> 6) & 0x1)
#define CSIEP0_REG2_STR_PCT             (0x1 << 7)
#define CSIEP0_REG2_STR_PCT_GET(_v)     ((_v >> 7) & 0x1)

#define CSIEP0_REG2_CTL2_POFFSET        0x1
#define CSIEP0_REG2_CTL2                (CSIEP0 + CSIEP0_REG2_POFFSET + CSIEP0_REG2_CTL2_POFFSET)
#define CSIEP0_REG2_CTL2_DL             0xf
#define CSIEP0_REG2_CTL2_DL_GET(_v)     (_v & 0xf)
#define CSIEP0_REG2_CTL2_CSL            (0xf << 4)
#define CSIEP0_REG2_CTL2_CSL_GET(_v)    ((_v >> 4) & 0xf)

#define CSIEP0_REG2_CTL3_POFFSET        0x4
#define CSIEP0_REG2_CTL3                (CSIEP0 + CSIEP0_REG2_POFFSET + CSIEP0_REG2_CTL3_POFFSET)
#define CSIEP0_REG2_CTL3_SFN            0xf
#define CSIEP0_REG2_CTL3_SFN_GET(_v)    (_v & 0xf)

#define CSIEP0_REG2_CTL4_POFFSET        0x5
#define CSIEP0_REG2_CTL4                (CSIEP0 + CSIEP0_REG2_POFFSET + CSIEP0_REG2_CTL4_POFFSET)
#define CSIEP0_REG2_CTL4_MD             0x1
#define CSIEP0_REG2_CTL4_MD_GET(_v)     (_v & 0x1)
#define CSIEP0_REG2_CTL4_OPE            (0x1 << 1)
#define CSIEP0_REG2_CTL4_OPE_GET(_v)    ((_v >> 1) & 0x1)
#define CSIEP0_REG2_CTL4_DPA            (0x1 << 2)
#define CSIEP0_REG2_CTL4_DPA_GET(_v)    ((_v >> 2) & 0x1)
#define CSIEP0_REG2_CTL4_CPA            (0x1 << 3)
#define CSIEP0_REG2_CTL4_CPA_GET(_v)    ((_v >> 3) & 0x1)
#define CSIEP0_REG2_CTL4_CSL            (0xf << 4)
#define CSIEP0_REG2_CTL4_CSL_GET(_v)    ((_v >> 4) & 0xf)

#define CSIEP0_REG3_POFFSET             0x10
#define CSIEP0_REG3_OPT_POFFSET         0x0
#define CSIEP0_REG3_OPT(_MMR_INDEX)     (CSIEP0 + CSIEP0_REG3_POFFSET + CSIEP0_REG3_OPT_POFFSET + ((_MMR_INDEX) * 0x2))


#endif

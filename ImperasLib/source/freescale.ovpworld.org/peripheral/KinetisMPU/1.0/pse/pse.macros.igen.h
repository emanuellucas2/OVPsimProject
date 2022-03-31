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
#define BPORT1_AB_CESR_POFFSET          0x0
#define BPORT1_AB_CESR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CESR_POFFSET)
#define BPORT1_AB_CESR_VLD              0x1
#define BPORT1_AB_CESR_VLD_GET(_v)      (_v & 0x1)
#define BPORT1_AB_CESR_NRGD             (0xf << 8)
#define BPORT1_AB_CESR_NRGD_GET(_v)     ((_v >> 8) & 0xf)
#define BPORT1_AB_CESR_NSP              (0xf << 12)
#define BPORT1_AB_CESR_NSP_GET(_v)      ((_v >> 12) & 0xf)
#define BPORT1_AB_CESR_HRL              (0xf << 16)
#define BPORT1_AB_CESR_HRL_GET(_v)      ((_v >> 16) & 0xf)
#define BPORT1_AB_CESR_SPERR            (0xff << 24)
#define BPORT1_AB_CESR_SPERR_GET(_v)    ((_v >> 24) & 0xff)

#define BPORT1_AB_EAR0_POFFSET          0x10
#define BPORT1_AB_EAR0                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EAR0_POFFSET)
#define BPORT1_AB_EAR0_EADDR            0xffffffff
#define BPORT1_AB_EAR0_EADDR_GET(_v)    (_v & 0xffffffff)

#define BPORT1_AB_EDR0_POFFSET          0x14
#define BPORT1_AB_EDR0                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EDR0_POFFSET)
#define BPORT1_AB_EDR0_ERW              0x1
#define BPORT1_AB_EDR0_ERW_GET(_v)      (_v & 0x1)
#define BPORT1_AB_EDR0_EATTR            (0x7 << 1)
#define BPORT1_AB_EDR0_EATTR_GET(_v)    ((_v >> 1) & 0x7)
#define BPORT1_AB_EDR0_EMN              (0xf << 4)
#define BPORT1_AB_EDR0_EMN_GET(_v)      ((_v >> 4) & 0xf)
#define BPORT1_AB_EDR0_EPID             (0xff << 8)
#define BPORT1_AB_EDR0_EPID_GET(_v)     ((_v >> 8) & 0xff)
#define BPORT1_AB_EDR0_EACD             (0xffff << 16)
#define BPORT1_AB_EDR0_EACD_GET(_v)     ((_v >> 16) & 0xffff)

#define BPORT1_AB_EAR1_POFFSET          0x18
#define BPORT1_AB_EAR1                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EAR1_POFFSET)
#define BPORT1_AB_EAR1_EADDR            0xffffffff
#define BPORT1_AB_EAR1_EADDR_GET(_v)    (_v & 0xffffffff)

#define BPORT1_AB_EDR1_POFFSET          0x1c
#define BPORT1_AB_EDR1                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EDR1_POFFSET)
#define BPORT1_AB_EDR1_ERW              0x1
#define BPORT1_AB_EDR1_ERW_GET(_v)      (_v & 0x1)
#define BPORT1_AB_EDR1_EATTR            (0x7 << 1)
#define BPORT1_AB_EDR1_EATTR_GET(_v)    ((_v >> 1) & 0x7)
#define BPORT1_AB_EDR1_EMN              (0xf << 4)
#define BPORT1_AB_EDR1_EMN_GET(_v)      ((_v >> 4) & 0xf)
#define BPORT1_AB_EDR1_EPID             (0xff << 8)
#define BPORT1_AB_EDR1_EPID_GET(_v)     ((_v >> 8) & 0xff)
#define BPORT1_AB_EDR1_EACD             (0xffff << 16)
#define BPORT1_AB_EDR1_EACD_GET(_v)     ((_v >> 16) & 0xffff)

#define BPORT1_AB_EAR2_POFFSET          0x20
#define BPORT1_AB_EAR2                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EAR2_POFFSET)
#define BPORT1_AB_EAR2_EADDR            0xffffffff
#define BPORT1_AB_EAR2_EADDR_GET(_v)    (_v & 0xffffffff)

#define BPORT1_AB_EDR2_POFFSET          0x24
#define BPORT1_AB_EDR2                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EDR2_POFFSET)
#define BPORT1_AB_EDR2_ERW              0x1
#define BPORT1_AB_EDR2_ERW_GET(_v)      (_v & 0x1)
#define BPORT1_AB_EDR2_EATTR            (0x7 << 1)
#define BPORT1_AB_EDR2_EATTR_GET(_v)    ((_v >> 1) & 0x7)
#define BPORT1_AB_EDR2_EMN              (0xf << 4)
#define BPORT1_AB_EDR2_EMN_GET(_v)      ((_v >> 4) & 0xf)
#define BPORT1_AB_EDR2_EPID             (0xff << 8)
#define BPORT1_AB_EDR2_EPID_GET(_v)     ((_v >> 8) & 0xff)
#define BPORT1_AB_EDR2_EACD             (0xffff << 16)
#define BPORT1_AB_EDR2_EACD_GET(_v)     ((_v >> 16) & 0xffff)

#define BPORT1_AB_EAR3_POFFSET          0x28
#define BPORT1_AB_EAR3                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EAR3_POFFSET)
#define BPORT1_AB_EAR3_EADDR            0xffffffff
#define BPORT1_AB_EAR3_EADDR_GET(_v)    (_v & 0xffffffff)

#define BPORT1_AB_EDR3_POFFSET          0x2c
#define BPORT1_AB_EDR3                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EDR3_POFFSET)
#define BPORT1_AB_EDR3_ERW              0x1
#define BPORT1_AB_EDR3_ERW_GET(_v)      (_v & 0x1)
#define BPORT1_AB_EDR3_EATTR            (0x7 << 1)
#define BPORT1_AB_EDR3_EATTR_GET(_v)    ((_v >> 1) & 0x7)
#define BPORT1_AB_EDR3_EMN              (0xf << 4)
#define BPORT1_AB_EDR3_EMN_GET(_v)      ((_v >> 4) & 0xf)
#define BPORT1_AB_EDR3_EPID             (0xff << 8)
#define BPORT1_AB_EDR3_EPID_GET(_v)     ((_v >> 8) & 0xff)
#define BPORT1_AB_EDR3_EACD             (0xffff << 16)
#define BPORT1_AB_EDR3_EACD_GET(_v)     ((_v >> 16) & 0xffff)

#define BPORT1_AB_EAR4_POFFSET          0x30
#define BPORT1_AB_EAR4                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EAR4_POFFSET)
#define BPORT1_AB_EAR4_EADDR            0xffffffff
#define BPORT1_AB_EAR4_EADDR_GET(_v)    (_v & 0xffffffff)

#define BPORT1_AB_EDR4_POFFSET          0x34
#define BPORT1_AB_EDR4                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EDR4_POFFSET)
#define BPORT1_AB_EDR4_ERW              0x1
#define BPORT1_AB_EDR4_ERW_GET(_v)      (_v & 0x1)
#define BPORT1_AB_EDR4_EATTR            (0x7 << 1)
#define BPORT1_AB_EDR4_EATTR_GET(_v)    ((_v >> 1) & 0x7)
#define BPORT1_AB_EDR4_EMN              (0xf << 4)
#define BPORT1_AB_EDR4_EMN_GET(_v)      ((_v >> 4) & 0xf)
#define BPORT1_AB_EDR4_EPID             (0xff << 8)
#define BPORT1_AB_EDR4_EPID_GET(_v)     ((_v >> 8) & 0xff)
#define BPORT1_AB_EDR4_EACD             (0xffff << 16)
#define BPORT1_AB_EDR4_EACD_GET(_v)     ((_v >> 16) & 0xffff)

#define BPORT1_RGD_POFFSET              0x400
#define BPORT1_RGD_WORD0_POFFSET        0x0
#define BPORT1_RGD_WORD0(_AB_INDEX)     (BPORT1 + BPORT1_RGD_POFFSET + BPORT1_RGD_WORD0_POFFSET + ((_AB_INDEX) * 0x10))

#define BPORT1_RGD_WORD1_POFFSET        0x4
#define BPORT1_RGD_WORD1(_AB_INDEX)     (BPORT1 + BPORT1_RGD_POFFSET + BPORT1_RGD_WORD1_POFFSET + ((_AB_INDEX) * 0x10))

#define BPORT1_RGD_WORD2_POFFSET        0x8
#define BPORT1_RGD_WORD2(_AB_INDEX)     (BPORT1 + BPORT1_RGD_POFFSET + BPORT1_RGD_WORD2_POFFSET + ((_AB_INDEX) * 0x10))

#define BPORT1_RGD_WORD3_POFFSET        0xc
#define BPORT1_RGD_WORD3(_AB_INDEX)     (BPORT1 + BPORT1_RGD_POFFSET + BPORT1_RGD_WORD3_POFFSET + ((_AB_INDEX) * 0x10))

#define BPORT1_AAC_POFFSET              0x800
#define BPORT1_AAC_RGDAAC_POFFSET       0x0
#define BPORT1_AAC_RGDAAC(_MMR_INDEX)   (BPORT1 + BPORT1_AAC_POFFSET + BPORT1_AAC_RGDAAC_POFFSET + ((_MMR_INDEX) * 0x4))


#endif

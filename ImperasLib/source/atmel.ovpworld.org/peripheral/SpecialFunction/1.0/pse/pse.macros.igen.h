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

// Set the macro 'BP1' to the base of port 'bp1'
#ifndef BP1
#error BP1 is undefined. It needs to be set to the port base address
#endif


#define BP1_REG_POFFSET                 0x0
#define BP1_REG_SF_CIDR_POFFSET         0x0
#define BP1_REG_SF_CIDR                 (BP1 + BP1_REG_POFFSET + BP1_REG_SF_CIDR_POFFSET)
#define BP1_REG_SF_CIDR_EXT             (0x1 << 31)
#define BP1_REG_SF_CIDR_EXT_GET(_v)     ((_v >> 31) & 0x1)
#define BP1_REG_SF_CIDR_ARCH            (0xff << 20)
#define BP1_REG_SF_CIDR_ARCH_GET(_v)    ((_v >> 20) & 0xff)
#define BP1_REG_SF_CIDR_VDSIZ           (0xf << 16)
#define BP1_REG_SF_CIDR_VDSIZ_GET(_v)   ((_v >> 16) & 0xf)
#define BP1_REG_SF_CIDR_NVDSIZ          (0xf << 12)
#define BP1_REG_SF_CIDR_NVDSIZ_GET(_v)  ((_v >> 12) & 0xf)
#define BP1_REG_SF_CIDR_NVPSIZ          (0xf << 8)
#define BP1_REG_SF_CIDR_NVPSIZ_GET(_v)  ((_v >> 8) & 0xf)
#define BP1_REG_SF_CIDR_VERSION         0x1f
#define BP1_REG_SF_CIDR_VERSION_GET(_v)  (_v & 0x1f)

#define BP1_REG_SF_EXID_POFFSET         0x4
#define BP1_REG_SF_EXID                 (BP1 + BP1_REG_POFFSET + BP1_REG_SF_EXID_POFFSET)
#define BP1_REG_SF_EXID_RESET           0xff
#define BP1_REG_SF_EXID_RESET_GET(_v)   (_v & 0xff)

#define BP1_REG_SF_RSR_POFFSET          0x8
#define BP1_REG_SF_RSR                  (BP1 + BP1_REG_POFFSET + BP1_REG_SF_RSR_POFFSET)

#define BP1_REG_SF_PMR_POFFSET          0x18
#define BP1_REG_SF_PMR                  (BP1 + BP1_REG_POFFSET + BP1_REG_SF_PMR_POFFSET)
#define BP1_REG_SF_PMR_PMRKEY           (0xffff << 16)
#define BP1_REG_SF_PMR_PMRKEY_GET(_v)   ((_v >> 16) & 0xffff)
#define BP1_REG_SF_PMR_AIC              (0x1 << 5)
#define BP1_REG_SF_PMR_AIC_GET(_v)      ((_v >> 5) & 0x1)


#endif

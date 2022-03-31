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
#define BP1_REG_WD_OMR_POFFSET          0x0
#define BP1_REG_WD_OMR                  (BP1 + BP1_REG_POFFSET + BP1_REG_WD_OMR_POFFSET)
#define BP1_REG_WD_OMR_OKEY             (0xfff << 4)
#define BP1_REG_WD_OMR_OKEY_GET(_v)     ((_v >> 4) & 0xfff)
#define BP1_REG_WD_OMR_EXTEN            (0x1 << 3)
#define BP1_REG_WD_OMR_EXTEN_GET(_v)    ((_v >> 3) & 0x1)
#define BP1_REG_WD_OMR_IRQEN            (0x1 << 2)
#define BP1_REG_WD_OMR_IRQEN_GET(_v)    ((_v >> 2) & 0x1)
#define BP1_REG_WD_OMR_RSTEN            (0x1 << 1)
#define BP1_REG_WD_OMR_RSTEN_GET(_v)    ((_v >> 1) & 0x1)
#define BP1_REG_WD_OMR_WDEN             0x1
#define BP1_REG_WD_OMR_WDEN_GET(_v)     (_v & 0x1)

#define BP1_REG_WD_CMR_POFFSET          0x4
#define BP1_REG_WD_CMR                  (BP1 + BP1_REG_POFFSET + BP1_REG_WD_CMR_POFFSET)
#define BP1_REG_WD_CMR_CKEY             (0x1ff << 7)
#define BP1_REG_WD_CMR_CKEY_GET(_v)     ((_v >> 7) & 0x1ff)
#define BP1_REG_WD_CMR_HPCV             (0xf << 2)
#define BP1_REG_WD_CMR_HPCV_GET(_v)     ((_v >> 2) & 0xf)
#define BP1_REG_WD_CMR_WDCLKS           0x3
#define BP1_REG_WD_CMR_WDCLKS_GET(_v)   (_v & 0x3)

#define BP1_REG_WD_CR_POFFSET           0x8
#define BP1_REG_WD_CR                   (BP1 + BP1_REG_POFFSET + BP1_REG_WD_CR_POFFSET)
#define BP1_REG_WD_CR_RSTKEY            0xffff
#define BP1_REG_WD_CR_RSTKEY_GET(_v)    (_v & 0xffff)

#define BP1_REG_WD_SR_POFFSET           0xc
#define BP1_REG_WD_SR                   (BP1 + BP1_REG_POFFSET + BP1_REG_WD_SR_POFFSET)
#define BP1_REG_WD_SR_WDOVF             0x1
#define BP1_REG_WD_SR_WDOVF_GET(_v)     (_v & 0x1)


#endif

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
#define BPORT1_AB_CR_POFFSET            0x0
#define BPORT1_AB_CR                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR_POFFSET)
#define BPORT1_AB_CR_CLRI               (0x1 << 3)
#define BPORT1_AB_CR_CLRI_GET(_v)       ((_v >> 3) & 0x1)
#define BPORT1_AB_CR_GO                 0x1
#define BPORT1_AB_CR_GO_GET(_v)         (_v & 0x1)
#define BPORT1_AB_CR_HA                 (0x1 << 1)
#define BPORT1_AB_CR_HA_GET(_v)         ((_v >> 1) & 0x1)
#define BPORT1_AB_CR_INTM               (0x1 << 2)
#define BPORT1_AB_CR_INTM_GET(_v)       ((_v >> 2) & 0x1)
#define BPORT1_AB_CR_SLP                (0x1 << 4)
#define BPORT1_AB_CR_SLP_GET(_v)        ((_v >> 4) & 0x1)

#define BPORT1_AB_SR_POFFSET            0x4
#define BPORT1_AB_SR                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SR_POFFSET)
#define BPORT1_AB_SR_ERRI               (0x1 << 3)
#define BPORT1_AB_SR_ERRI_GET(_v)       ((_v >> 3) & 0x1)
#define BPORT1_AB_SR_LRS                (0x1 << 1)
#define BPORT1_AB_SR_LRS_GET(_v)        ((_v >> 1) & 0x1)
#define BPORT1_AB_SR_OREG_LVL           (0xff << 8)
#define BPORT1_AB_SR_OREG_LVL_GET(_v)   ((_v >> 8) & 0xff)
#define BPORT1_AB_SR_OREG_SIZE          (0xff << 16)
#define BPORT1_AB_SR_OREG_SIZE_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_AB_SR_ORU                (0x1 << 2)
#define BPORT1_AB_SR_ORU_GET(_v)        ((_v >> 2) & 0x1)
#define BPORT1_AB_SR_SECV               0x1
#define BPORT1_AB_SR_SECV_GET(_v)       (_v & 0x1)
#define BPORT1_AB_SR_SLP                (0x1 << 4)
#define BPORT1_AB_SR_SLP_GET(_v)        ((_v >> 4) & 0x1)

#define BPORT1_AB_ER_POFFSET            0x8
#define BPORT1_AB_ER                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ER_POFFSET)
#define BPORT1_AB_ER_EXT_ENT            0xffffffff
#define BPORT1_AB_ER_EXT_ENT_GET(_v)    (_v & 0xffffffff)

#define BPORT1_AB_OR_POFFSET            0xc
#define BPORT1_AB_OR                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_OR_POFFSET)
#define BPORT1_AB_OR_RANDOUT            0xffffffff
#define BPORT1_AB_OR_RANDOUT_GET(_v)    (_v & 0xffffffff)


#endif

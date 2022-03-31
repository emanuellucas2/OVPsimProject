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
#define BPORT1_AB_SRS0_POFFSET          0x0
#define BPORT1_AB_SRS0                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SRS0_POFFSET)
#define BPORT1_AB_SRS0_LOC              (0x1 << 2)
#define BPORT1_AB_SRS0_LOC_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_SRS0_LVD              (0x1 << 1)
#define BPORT1_AB_SRS0_LVD_GET(_v)      ((_v >> 1) & 0x1)
#define BPORT1_AB_SRS0_PIN              (0x1 << 6)
#define BPORT1_AB_SRS0_PIN_GET(_v)      ((_v >> 6) & 0x1)
#define BPORT1_AB_SRS0_POR              (0x1 << 7)
#define BPORT1_AB_SRS0_POR_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_SRS0_WAKEUP           0x1
#define BPORT1_AB_SRS0_WAKEUP_GET(_v)   (_v & 0x1)
#define BPORT1_AB_SRS0_WDOG             (0x1 << 5)
#define BPORT1_AB_SRS0_WDOG_GET(_v)     ((_v >> 5) & 0x1)

#define BPORT1_AB_SRS1_POFFSET          0x1
#define BPORT1_AB_SRS1                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SRS1_POFFSET)
#define BPORT1_AB_SRS1_EZPT             (0x1 << 4)
#define BPORT1_AB_SRS1_EZPT_GET(_v)     ((_v >> 4) & 0x1)
#define BPORT1_AB_SRS1_JTAG             0x1
#define BPORT1_AB_SRS1_JTAG_GET(_v)     (_v & 0x1)
#define BPORT1_AB_SRS1_LOCKUP           (0x1 << 1)
#define BPORT1_AB_SRS1_LOCKUP_GET(_v)   ((_v >> 1) & 0x1)
#define BPORT1_AB_SRS1_MDM_AP           (0x1 << 3)
#define BPORT1_AB_SRS1_MDM_AP_GET(_v)   ((_v >> 3) & 0x1)
#define BPORT1_AB_SRS1_SACKERR          (0x1 << 5)
#define BPORT1_AB_SRS1_SACKERR_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_SRS1_SW               (0x1 << 2)
#define BPORT1_AB_SRS1_SW_GET(_v)       ((_v >> 2) & 0x1)
#define BPORT1_AB_SRS1_TAMPER           (0x1 << 7)
#define BPORT1_AB_SRS1_TAMPER_GET(_v)   ((_v >> 7) & 0x1)

#define BPORT1_AB_RPFC_POFFSET          0x4
#define BPORT1_AB_RPFC                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RPFC_POFFSET)
#define BPORT1_AB_RPFC_RSTFLTSRW        0x3
#define BPORT1_AB_RPFC_RSTFLTSRW_GET(_v)  (_v & 0x3)
#define BPORT1_AB_RPFC_RSTFLTSS         (0x1 << 2)
#define BPORT1_AB_RPFC_RSTFLTSS_GET(_v)  ((_v >> 2) & 0x1)

#define BPORT1_AB_RPFW_POFFSET          0x5
#define BPORT1_AB_RPFW                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RPFW_POFFSET)
#define BPORT1_AB_RPFW_RSTFLTSEL        0x1f
#define BPORT1_AB_RPFW_RSTFLTSEL_GET(_v)  (_v & 0x1f)

#define BPORT1_AB_MR_POFFSET            0x7
#define BPORT1_AB_MR                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MR_POFFSET)
#define BPORT1_AB_MR_EZP_MS             (0x1 << 1)
#define BPORT1_AB_MR_EZP_MS_GET(_v)     ((_v >> 1) & 0x1)


#endif

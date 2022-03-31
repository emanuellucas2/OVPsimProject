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
#define BPORT1_AB_WDOGLOAD_POFFSET      0x0
#define BPORT1_AB_WDOGLOAD              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WDOGLOAD_POFFSET)

#define BPORT1_AB_WDOGVALUE_POFFSET     0x4
#define BPORT1_AB_WDOGVALUE             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WDOGVALUE_POFFSET)

#define BPORT1_AB_WDOGCONTROL_POFFSET   0x8
#define BPORT1_AB_WDOGCONTROL           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WDOGCONTROL_POFFSET)

#define BPORT1_AB_WDOGINTCLR_POFFSET    0xc
#define BPORT1_AB_WDOGINTCLR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WDOGINTCLR_POFFSET)

#define BPORT1_AB_WDOGRIS_POFFSET       0x10
#define BPORT1_AB_WDOGRIS               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WDOGRIS_POFFSET)

#define BPORT1_AB_WDOGMIS_POFFSET       0x14
#define BPORT1_AB_WDOGMIS               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WDOGMIS_POFFSET)

#define BPORT1_AB_WDOGLOCK_POFFSET      0xc00
#define BPORT1_AB_WDOGLOCK              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WDOGLOCK_POFFSET)

#define BPORT1_AB_WDOGITCR_POFFSET      0xf00
#define BPORT1_AB_WDOGITCR              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WDOGITCR_POFFSET)

#define BPORT1_AB_WDOGITOP_POFFSET      0xf04
#define BPORT1_AB_WDOGITOP              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WDOGITOP_POFFSET)

#define BPORT1_AB_PERIPHID0_POFFSET     0xfe0
#define BPORT1_AB_PERIPHID0             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PERIPHID0_POFFSET)

#define BPORT1_AB_PERIPHID1_POFFSET     0xfe4
#define BPORT1_AB_PERIPHID1             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PERIPHID1_POFFSET)

#define BPORT1_AB_PERIPHID2_POFFSET     0xfe8
#define BPORT1_AB_PERIPHID2             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PERIPHID2_POFFSET)

#define BPORT1_AB_PERIPHID3_POFFSET     0xfec
#define BPORT1_AB_PERIPHID3             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PERIPHID3_POFFSET)

#define BPORT1_AB_PCELLID0_POFFSET      0xff0
#define BPORT1_AB_PCELLID0              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PCELLID0_POFFSET)

#define BPORT1_AB_PCELLID1_POFFSET      0xff4
#define BPORT1_AB_PCELLID1              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PCELLID1_POFFSET)

#define BPORT1_AB_PCELLID2_POFFSET      0xff8
#define BPORT1_AB_PCELLID2              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PCELLID2_POFFSET)

#define BPORT1_AB_PCELLID3_POFFSET      0xffc
#define BPORT1_AB_PCELLID3              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PCELLID3_POFFSET)


#endif

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
#define BPORT1_AB_ID_POFFSET            0x0
#define BPORT1_AB_ID                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ID_POFFSET)

#define BPORT1_AB_SW_POFFSET            0x4
#define BPORT1_AB_SW                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SW_POFFSET)

#define BPORT1_AB_LED_POFFSET           0x8
#define BPORT1_AB_LED                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LED_POFFSET)

#define BPORT1_AB_CNT100HZ_POFFSET      0x24
#define BPORT1_AB_CNT100HZ              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CNT100HZ_POFFSET)

#define BPORT1_AB_FLAGSSET_POFFSET      0x30
#define BPORT1_AB_FLAGSSET              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FLAGSSET_POFFSET)

#define BPORT1_AB_FLAGSCLR_POFFSET      0x34
#define BPORT1_AB_FLAGSCLR              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FLAGSCLR_POFFSET)

#define BPORT1_AB_NVFLAGSSET_POFFSET    0x38
#define BPORT1_AB_NVFLAGSSET            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_NVFLAGSSET_POFFSET)

#define BPORT1_AB_NVFLAGSCLR_POFFSET    0x3c
#define BPORT1_AB_NVFLAGSCLR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_NVFLAGSCLR_POFFSET)

#define BPORT1_AB_MCI_POFFSET           0x48
#define BPORT1_AB_MCI                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MCI_POFFSET)

#define BPORT1_AB_FLASH_POFFSET         0x4c
#define BPORT1_AB_FLASH                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FLASH_POFFSET)

#define BPORT1_AB_CFGSW_POFFSET         0x58
#define BPORT1_AB_CFGSW                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CFGSW_POFFSET)

#define BPORT1_AB_CNT24MHZ_POFFSET      0x5c
#define BPORT1_AB_CNT24MHZ              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CNT24MHZ_POFFSET)

#define BPORT1_AB_MISC_POFFSET          0x60
#define BPORT1_AB_MISC                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MISC_POFFSET)

#define BPORT1_AB_DMA_POFFSET           0x64
#define BPORT1_AB_DMA                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DMA_POFFSET)

#define BPORT1_AB_PROCID0_POFFSET       0x84
#define BPORT1_AB_PROCID0               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PROCID0_POFFSET)

#define BPORT1_AB_PROCID1_POFFSET       0x88
#define BPORT1_AB_PROCID1               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PROCID1_POFFSET)

#define BPORT1_AB_CFGDATA_POFFSET       0xa0
#define BPORT1_AB_CFGDATA               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CFGDATA_POFFSET)

#define BPORT1_AB_CFGCTRL_POFFSET       0xa4
#define BPORT1_AB_CFGCTRL               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CFGCTRL_POFFSET)

#define BPORT1_AB_CFGSTAT_POFFSET       0xa8
#define BPORT1_AB_CFGSTAT               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CFGSTAT_POFFSET)


#endif

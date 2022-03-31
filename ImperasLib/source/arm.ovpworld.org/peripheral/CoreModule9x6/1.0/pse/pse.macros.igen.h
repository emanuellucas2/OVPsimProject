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

#define BPORT1_AB_PROC_POFFSET          0x4
#define BPORT1_AB_PROC                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PROC_POFFSET)

#define BPORT1_AB_OSC_POFFSET           0x8
#define BPORT1_AB_OSC                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_OSC_POFFSET)

#define BPORT1_AB_CTRL_POFFSET          0xc
#define BPORT1_AB_CTRL                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CTRL_POFFSET)

#define BPORT1_AB_STAT_POFFSET          0x10
#define BPORT1_AB_STAT                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_STAT_POFFSET)

#define BPORT1_AB_LOCK_POFFSET          0x14
#define BPORT1_AB_LOCK                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LOCK_POFFSET)

#define BPORT1_AB_LMBUSCNT_POFFSET      0x18
#define BPORT1_AB_LMBUSCNT              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LMBUSCNT_POFFSET)

#define BPORT1_AB_AUXOSC_POFFSET        0x1c
#define BPORT1_AB_AUXOSC                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AUXOSC_POFFSET)

#define BPORT1_AB_SDRAM_POFFSET         0x20
#define BPORT1_AB_SDRAM                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SDRAM_POFFSET)

#define BPORT1_AB_INIT_POFFSET          0x24
#define BPORT1_AB_INIT                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INIT_POFFSET)

#define BPORT1_AB_REFCT_POFFSET         0x28
#define BPORT1_AB_REFCT                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REFCT_POFFSET)

#define BPORT1_AB_FLAGS_POFFSET         0x30
#define BPORT1_AB_FLAGS                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FLAGS_POFFSET)

#define BPORT1_AB_FLAGSC_POFFSET        0x34
#define BPORT1_AB_FLAGSC                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FLAGSC_POFFSET)

#define BPORT1_AB_NVFLAGS_POFFSET       0x38
#define BPORT1_AB_NVFLAGS               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_NVFLAGS_POFFSET)

#define BPORT1_AB_NVFLAGSS_POFFSET      0x3c
#define BPORT1_AB_NVFLAGSS              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_NVFLAGSS_POFFSET)

#define BPORT1_AB_IRQSTAT_POFFSET       0x40
#define BPORT1_AB_IRQSTAT               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IRQSTAT_POFFSET)

#define BPORT1_AB_IRQRSTAT_POFFSET      0x44
#define BPORT1_AB_IRQRSTAT              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IRQRSTAT_POFFSET)

#define BPORT1_AB_IRQENSET_POFFSET      0x48
#define BPORT1_AB_IRQENSET              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IRQENSET_POFFSET)

#define BPORT1_AB_IRQENCLR_POFFSET      0x4c
#define BPORT1_AB_IRQENCLR              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IRQENCLR_POFFSET)

#define BPORT1_AB_SOFTINTSET_POFFSET    0x50
#define BPORT1_AB_SOFTINTSET            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SOFTINTSET_POFFSET)

#define BPORT1_AB_SOFTINTCLR_POFFSET    0x54
#define BPORT1_AB_SOFTINTCLR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SOFTINTCLR_POFFSET)

#define BPORT1_AB_FIQSTAT_POFFSET       0x60
#define BPORT1_AB_FIQSTAT               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FIQSTAT_POFFSET)

#define BPORT1_AB_FIQRSTAT_POFFSET      0x64
#define BPORT1_AB_FIQRSTAT              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FIQRSTAT_POFFSET)

#define BPORT1_AB_FIQENSET_POFFSET      0x68
#define BPORT1_AB_FIQENSET              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FIQENSET_POFFSET)

#define BPORT1_AB_FIQENCLR_POFFSET      0x6c
#define BPORT1_AB_FIQENCLR              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FIQENCLR_POFFSET)

#define BPORT1_AB_VOLT0_POFFSET         0x80
#define BPORT1_AB_VOLT0                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_VOLT0_POFFSET)

#define BPORT1_AB_VOLT1_POFFSET         0x84
#define BPORT1_AB_VOLT1                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_VOLT1_POFFSET)

#define BPORT1_AB_VOLT2_POFFSET         0x88
#define BPORT1_AB_VOLT2                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_VOLT2_POFFSET)

#define BPORT1_AB_VOLT3_POFFSET         0x8c
#define BPORT1_AB_VOLT3                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_VOLT3_POFFSET)


#endif

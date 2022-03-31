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
#define BPORT1_AB_CONFIG_POFFSET        0x0
#define BPORT1_AB_CONFIG                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CONFIG_POFFSET)

#define BPORT1_AB_INTR_STATUS_POFFSET   0x4
#define BPORT1_AB_INTR_STATUS           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INTR_STATUS_POFFSET)

#define BPORT1_AB_INTRPT_EN_POFFSET     0x8
#define BPORT1_AB_INTRPT_EN             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INTRPT_EN_POFFSET)

#define BPORT1_AB_INTRPT_DIS_POFFSET    0xc
#define BPORT1_AB_INTRPT_DIS            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INTRPT_DIS_POFFSET)

#define BPORT1_AB_INTRPT_MASK_POFFSET   0x10
#define BPORT1_AB_INTRPT_MASK           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INTRPT_MASK_POFFSET)

#define BPORT1_AB_EN_POFFSET            0x14
#define BPORT1_AB_EN                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EN_POFFSET)

#define BPORT1_AB_DELAY_POFFSET         0x18
#define BPORT1_AB_DELAY                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DELAY_POFFSET)

#define BPORT1_AB_TX_DATA_POFFSET       0x1c
#define BPORT1_AB_TX_DATA               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TX_DATA_POFFSET)

#define BPORT1_AB_RX_DATA_POFFSET       0x20
#define BPORT1_AB_RX_DATA               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RX_DATA_POFFSET)

#define BPORT1_AB_SLAVE_IDLE_COUNT_POFFSET  0x24
#define BPORT1_AB_SLAVE_IDLE_COUNT      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SLAVE_IDLE_COUNT_POFFSET)

#define BPORT1_AB_TX_THRES_POFFSET      0x28
#define BPORT1_AB_TX_THRES              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TX_THRES_POFFSET)

#define BPORT1_AB_RX_THRES_POFFSET      0x2c
#define BPORT1_AB_RX_THRES              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RX_THRES_POFFSET)

#define BPORT1_AB_MOD_ID_POFFSET        0xfc
#define BPORT1_AB_MOD_ID                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MOD_ID_POFFSET)

#define BPORT1_AB_BUFFER_POFFSET        0x0
#define BPORT1_AB_BUFFER                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BUFFER_POFFSET)
#define BPORT1_AB_BUFFER_BYTES          0x1000


#endif

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

#define BPORT1_AB_STAT_POFFSET          0x4
#define BPORT1_AB_STAT                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_STAT_POFFSET)
#define BPORT1_AB_STAT_TXEMPTY          (0x1 << 6)
#define BPORT1_AB_STAT_TXEMPTY_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_STAT_TXBUSY           (0x1 << 5)
#define BPORT1_AB_STAT_TXBUSY_GET(_v)   ((_v >> 5) & 0x1)
#define BPORT1_AB_STAT_RXFULL           (0x1 << 4)
#define BPORT1_AB_STAT_RXFULL_GET(_v)   ((_v >> 4) & 0x1)
#define BPORT1_AB_STAT_RXBUSY           (0x1 << 3)
#define BPORT1_AB_STAT_RXBUSY_GET(_v)   ((_v >> 3) & 0x1)
#define BPORT1_AB_STAT_RXPARITY         (0x1 << 2)
#define BPORT1_AB_STAT_RXPARITY_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_STAT_KMIC             (0x1 << 1)
#define BPORT1_AB_STAT_KMIC_GET(_v)     ((_v >> 1) & 0x1)
#define BPORT1_AB_STAT_KMID             0x1
#define BPORT1_AB_STAT_KMID_GET(_v)     (_v & 0x1)

#define BPORT1_AB_DATA_POFFSET          0x8
#define BPORT1_AB_DATA                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DATA_POFFSET)

#define BPORT1_AB_CLK_POFFSET           0xc
#define BPORT1_AB_CLK                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CLK_POFFSET)

#define BPORT1_AB_IIR_POFFSET           0x10
#define BPORT1_AB_IIR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IIR_POFFSET)

#define BPORT1_AB_ID_POFFSET            0xfe0
#define BPORT1_AB_ID(_MMR_INDEX)        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ID_POFFSET + ((_MMR_INDEX) * 0x4))


#endif

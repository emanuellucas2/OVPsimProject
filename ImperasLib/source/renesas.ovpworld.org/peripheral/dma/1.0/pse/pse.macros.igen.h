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

// Set the macro 'DMAP0' to the base of port 'DMAP0'
#ifndef DMAP0
#error DMAP0 is undefined. It needs to be set to the port base address
#endif
// Set the macro 'DMAP1' to the base of port 'DMAP1'
#ifndef DMAP1
#error DMAP1 is undefined. It needs to be set to the port base address
#endif


#define DMAP0_ABC_POFFSET               0x0
#define DMAP0_ABC_DMAWC0_POFFSET        0x0
#define DMAP0_ABC_DMAWC0                (DMAP0 + DMAP0_ABC_POFFSET + DMAP0_ABC_DMAWC0_POFFSET)

#define DMAP0_ABC_DMAWC1_POFFSET        0x2
#define DMAP0_ABC_DMAWC1                (DMAP0 + DMAP0_ABC_POFFSET + DMAP0_ABC_DMAWC1_POFFSET)


#define DMAP1_ABW_POFFSET               0x0
#define DMAP1_ABW_MAR_POFFSET           0x0
#define DMAP1_ABW_MAR(_MMR_INDEX)       (DMAP1 + DMAP1_ABW_POFFSET + DMAP1_ABW_MAR_POFFSET + ((_MMR_INDEX) * 0x2))

#define DMAP1_ABB_POFFSET               0x24
#define DMAP1_ABB_SAR_POFFSET           0x0
#define DMAP1_ABB_SAR(_MMR_INDEX)       (DMAP1 + DMAP1_ABB_POFFSET + DMAP1_ABB_SAR_POFFSET + ((_MMR_INDEX) * 0x1))

#define DMAP1_ABB_DTFR_POFFSET          0x5c
#define DMAP1_ABB_DTFR(_MMR_INDEX)      (DMAP1 + DMAP1_ABB_POFFSET + DMAP1_ABB_DTFR_POFFSET + ((_MMR_INDEX) * 0x1))

#define DMAP1_ABB_DTCR_POFFSET          0x1c
#define DMAP1_ABB_DTCR(_MMR_INDEX)      (DMAP1 + DMAP1_ABB_POFFSET + DMAP1_ABB_DTCR_POFFSET + ((_MMR_INDEX) * 0x1))

#define DMAP1_ABB_DMASL_POFFSET         0x3e
#define DMAP1_ABB_DMASL                 (DMAP1 + DMAP1_ABB_POFFSET + DMAP1_ABB_DMASL_POFFSET)
#define DMAP1_ABB_DMASL_DMAS7           (0x1 << 7)
#define DMAP1_ABB_DMASL_DMAS7_GET(_v)   ((_v >> 7) & 0x1)
#define DMAP1_ABB_DMASL_DMAS6           (0x1 << 6)
#define DMAP1_ABB_DMASL_DMAS6_GET(_v)   ((_v >> 6) & 0x1)
#define DMAP1_ABB_DMASL_DMAS5           (0x1 << 5)
#define DMAP1_ABB_DMASL_DMAS5_GET(_v)   ((_v >> 5) & 0x1)
#define DMAP1_ABB_DMASL_DMAS4           (0x1 << 4)
#define DMAP1_ABB_DMASL_DMAS4_GET(_v)   ((_v >> 4) & 0x1)
#define DMAP1_ABB_DMASL_DMAS3           (0x1 << 3)
#define DMAP1_ABB_DMASL_DMAS3_GET(_v)   ((_v >> 3) & 0x1)
#define DMAP1_ABB_DMASL_DMAS2           (0x1 << 2)
#define DMAP1_ABB_DMASL_DMAS2_GET(_v)   ((_v >> 2) & 0x1)
#define DMAP1_ABB_DMASL_DMAS1           (0x1 << 1)
#define DMAP1_ABB_DMASL_DMAS1_GET(_v)   ((_v >> 1) & 0x1)
#define DMAP1_ABB_DMASL_DMAS0           0x1
#define DMAP1_ABB_DMASL_DMAS0_GET(_v)   (_v & 0x1)

#define DMAP1_ABB_DMAMCL_POFFSET        0x3c
#define DMAP1_ABB_DMAMCL                (DMAP1 + DMAP1_ABB_POFFSET + DMAP1_ABB_DMAMCL_POFFSET)
#define DMAP1_ABB_DMAMCL_DE7            (0x1 << 7)
#define DMAP1_ABB_DMAMCL_DE7_GET(_v)    ((_v >> 7) & 0x1)
#define DMAP1_ABB_DMAMCL_DE6            (0x1 << 6)
#define DMAP1_ABB_DMAMCL_DE6_GET(_v)    ((_v >> 6) & 0x1)
#define DMAP1_ABB_DMAMCL_DE5            (0x1 << 5)
#define DMAP1_ABB_DMAMCL_DE5_GET(_v)    ((_v >> 5) & 0x1)
#define DMAP1_ABB_DMAMCL_DE4            (0x1 << 4)
#define DMAP1_ABB_DMAMCL_DE4_GET(_v)    ((_v >> 4) & 0x1)
#define DMAP1_ABB_DMAMCL_DE3            (0x1 << 3)
#define DMAP1_ABB_DMAMCL_DE3_GET(_v)    ((_v >> 3) & 0x1)
#define DMAP1_ABB_DMAMCL_DE2            (0x1 << 2)
#define DMAP1_ABB_DMAMCL_DE2_GET(_v)    ((_v >> 2) & 0x1)
#define DMAP1_ABB_DMAMCL_DE1            (0x1 << 1)
#define DMAP1_ABB_DMAMCL_DE1_GET(_v)    ((_v >> 1) & 0x1)
#define DMAP1_ABB_DMAMCL_DE0            0x1
#define DMAP1_ABB_DMAMCL_DE0_GET(_v)    (_v & 0x1)

#define DMAP1_ABB_DMADSCL_POFFSET       0x40
#define DMAP1_ABB_DMADSCL               (DMAP1 + DMAP1_ABB_POFFSET + DMAP1_ABB_DMADSCL_POFFSET)
#define DMAP1_ABB_DMADSCL_DMADCS7       (0x1 << 7)
#define DMAP1_ABB_DMADSCL_DMADCS7_GET(_v)  ((_v >> 7) & 0x1)
#define DMAP1_ABB_DMADSCL_DMADCS6       (0x1 << 6)
#define DMAP1_ABB_DMADSCL_DMADCS6_GET(_v)  ((_v >> 6) & 0x1)
#define DMAP1_ABB_DMADSCL_DMADCS5       (0x1 << 5)
#define DMAP1_ABB_DMADSCL_DMADCS5_GET(_v)  ((_v >> 5) & 0x1)
#define DMAP1_ABB_DMADSCL_DMADCS4       (0x1 << 4)
#define DMAP1_ABB_DMADSCL_DMADCS4_GET(_v)  ((_v >> 4) & 0x1)


#endif

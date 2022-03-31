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
#define BPORT1_AB_WDOG_WCR_POFFSET      0x0
#define BPORT1_AB_WDOG_WCR              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WDOG_WCR_POFFSET)
#define BPORT1_AB_WDOG_WCR_WT           (0xff << 8)
#define BPORT1_AB_WDOG_WCR_WT_GET(_v)   ((_v >> 8) & 0xff)
#define BPORT1_AB_WDOG_WCR_WDW          (0x1 << 7)
#define BPORT1_AB_WDOG_WCR_WDW_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_WDOG_WCR_SRE          (0x1 << 6)
#define BPORT1_AB_WDOG_WCR_SRE_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_WDOG_WCR_WDA          (0x1 << 5)
#define BPORT1_AB_WDOG_WCR_WDA_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_WDOG_WCR_SRS          (0x1 << 4)
#define BPORT1_AB_WDOG_WCR_SRS_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_WDOG_WCR_WDT          (0x1 << 3)
#define BPORT1_AB_WDOG_WCR_WDT_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_WDOG_WCR_WDE          (0x1 << 2)
#define BPORT1_AB_WDOG_WCR_WDE_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_WDOG_WCR_WDBG         (0x1 << 1)
#define BPORT1_AB_WDOG_WCR_WDBG_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_WDOG_WCR_WDZST        0x1
#define BPORT1_AB_WDOG_WCR_WDZST_GET(_v)  (_v & 0x1)

#define BPORT1_AB_WDOG_WSR_POFFSET      0x2
#define BPORT1_AB_WDOG_WSR              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WDOG_WSR_POFFSET)

#define BPORT1_AB_WDOG_WRSR_POFFSET     0x4
#define BPORT1_AB_WDOG_WRSR             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WDOG_WRSR_POFFSET)
#define BPORT1_AB_WDOG_WRSR_POR         (0x1 << 4)
#define BPORT1_AB_WDOG_WRSR_POR_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_WDOG_WRSR_TOUT        (0x1 << 1)
#define BPORT1_AB_WDOG_WRSR_TOUT_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_WDOG_WRSR_SFTW        0x1
#define BPORT1_AB_WDOG_WRSR_SFTW_GET(_v)  (_v & 0x1)

#define BPORT1_AB_WDOG_WICR_POFFSET     0x6
#define BPORT1_AB_WDOG_WICR             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WDOG_WICR_POFFSET)
#define BPORT1_AB_WDOG_WICR_WIE         (0x1 << 15)
#define BPORT1_AB_WDOG_WICR_WIE_GET(_v)  ((_v >> 15) & 0x1)
#define BPORT1_AB_WDOG_WICR_WTIS        (0x1 << 14)
#define BPORT1_AB_WDOG_WICR_WTIS_GET(_v)  ((_v >> 14) & 0x1)
#define BPORT1_AB_WDOG_WICR_WICT        0xff
#define BPORT1_AB_WDOG_WICR_WICT_GET(_v)  (_v & 0xff)

#define BPORT1_AB_WDOG_WMCR_POFFSET     0x8
#define BPORT1_AB_WDOG_WMCR             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WDOG_WMCR_POFFSET)
#define BPORT1_AB_WDOG_WMCR_PDE         0x1
#define BPORT1_AB_WDOG_WMCR_PDE_GET(_v)  (_v & 0x1)

#define BPORT1_AB_BUFFER_POFFSET        0x0
#define BPORT1_AB_BUFFER                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BUFFER_POFFSET)
#define BPORT1_AB_BUFFER_BYTES          0x4000


#endif

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
#define BPORT1_AB_TXDATA_POFFSET        0x0
#define BPORT1_AB_TXDATA                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TXDATA_POFFSET)
#define BPORT1_AB_TXDATA_DATA           0xff
#define BPORT1_AB_TXDATA_DATA_GET(_v)   (_v & 0xff)
#define BPORT1_AB_TXDATA_FULL           (0x1 << 31)
#define BPORT1_AB_TXDATA_FULL_GET(_v)   ((_v >> 31) & 0x1)

#define BPORT1_AB_RXDATA_POFFSET        0x4
#define BPORT1_AB_RXDATA                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXDATA_POFFSET)
#define BPORT1_AB_RXDATA_DATA           0xff
#define BPORT1_AB_RXDATA_DATA_GET(_v)   (_v & 0xff)
#define BPORT1_AB_RXDATA_EMPTY          (0x1 << 31)
#define BPORT1_AB_RXDATA_EMPTY_GET(_v)  ((_v >> 31) & 0x1)

#define BPORT1_AB_TXCTRL_POFFSET        0x8
#define BPORT1_AB_TXCTRL                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TXCTRL_POFFSET)
#define BPORT1_AB_TXCTRL_TXEN           0x1
#define BPORT1_AB_TXCTRL_TXEN_GET(_v)   (_v & 0x1)
#define BPORT1_AB_TXCTRL_NSTOP          (0x1 << 1)
#define BPORT1_AB_TXCTRL_NSTOP_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_TXCTRL_TXCNT          (0x7 << 16)
#define BPORT1_AB_TXCTRL_TXCNT_GET(_v)  ((_v >> 16) & 0x7)

#define BPORT1_AB_RXCTRL_POFFSET        0xc
#define BPORT1_AB_RXCTRL                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXCTRL_POFFSET)
#define BPORT1_AB_RXCTRL_RXEN           0x1
#define BPORT1_AB_RXCTRL_RXEN_GET(_v)   (_v & 0x1)
#define BPORT1_AB_RXCTRL_RXCNT          (0x7 << 16)
#define BPORT1_AB_RXCTRL_RXCNT_GET(_v)  ((_v >> 16) & 0x7)

#define BPORT1_AB_IE_POFFSET            0x10
#define BPORT1_AB_IE                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IE_POFFSET)
#define BPORT1_AB_IE_TXWM               0x1
#define BPORT1_AB_IE_TXWM_GET(_v)       (_v & 0x1)
#define BPORT1_AB_IE_RXWM               (0x1 << 1)
#define BPORT1_AB_IE_RXWM_GET(_v)       ((_v >> 1) & 0x1)

#define BPORT1_AB_IP_POFFSET            0x14
#define BPORT1_AB_IP                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IP_POFFSET)
#define BPORT1_AB_IP_TXWM               0x1
#define BPORT1_AB_IP_TXWM_GET(_v)       (_v & 0x1)
#define BPORT1_AB_IP_RXWM               (0x1 << 1)
#define BPORT1_AB_IP_RXWM_GET(_v)       ((_v >> 1) & 0x1)

#define BPORT1_AB_DIV_POFFSET           0x18
#define BPORT1_AB_DIV                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DIV_POFFSET)
#define BPORT1_AB_DIV_DIV               0xfffff
#define BPORT1_AB_DIV_DIV_GET(_v)       (_v & 0xfffff)


#endif

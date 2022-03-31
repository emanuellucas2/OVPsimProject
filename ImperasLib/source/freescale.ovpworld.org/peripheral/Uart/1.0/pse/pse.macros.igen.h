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
#define BPORT1_AB_BDH_POFFSET           0x0
#define BPORT1_AB_BDH                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BDH_POFFSET)
#define BPORT1_AB_BDH_SBR               0x1f
#define BPORT1_AB_BDH_SBR_GET(_v)       (_v & 0x1f)

#define BPORT1_AB_BDL_POFFSET           0x1
#define BPORT1_AB_BDL                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BDL_POFFSET)

#define BPORT1_AB_C1_POFFSET            0x2
#define BPORT1_AB_C1                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C1_POFFSET)

#define BPORT1_AB_C2_POFFSET            0x3
#define BPORT1_AB_C2                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C2_POFFSET)
#define BPORT1_AB_C2_TIE                (0x1 << 7)
#define BPORT1_AB_C2_TIE_GET(_v)        ((_v >> 7) & 0x1)
#define BPORT1_AB_C2_TCIE               (0x1 << 6)
#define BPORT1_AB_C2_TCIE_GET(_v)       ((_v >> 6) & 0x1)
#define BPORT1_AB_C2_RIE                (0x1 << 5)
#define BPORT1_AB_C2_RIE_GET(_v)        ((_v >> 5) & 0x1)
#define BPORT1_AB_C2_ILIE               (0x1 << 4)
#define BPORT1_AB_C2_ILIE_GET(_v)       ((_v >> 4) & 0x1)
#define BPORT1_AB_C2_TE                 (0x1 << 3)
#define BPORT1_AB_C2_TE_GET(_v)         ((_v >> 3) & 0x1)
#define BPORT1_AB_C2_RE                 (0x1 << 2)
#define BPORT1_AB_C2_RE_GET(_v)         ((_v >> 2) & 0x1)

#define BPORT1_AB_S1_POFFSET            0x4
#define BPORT1_AB_S1                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_S1_POFFSET)
#define BPORT1_AB_S1_TDRE               (0x1 << 7)
#define BPORT1_AB_S1_TDRE_GET(_v)       ((_v >> 7) & 0x1)
#define BPORT1_AB_S1_TC                 (0x1 << 6)
#define BPORT1_AB_S1_TC_GET(_v)         ((_v >> 6) & 0x1)
#define BPORT1_AB_S1_RDRF               (0x1 << 5)
#define BPORT1_AB_S1_RDRF_GET(_v)       ((_v >> 5) & 0x1)
#define BPORT1_AB_S1_IDLE               (0x1 << 4)
#define BPORT1_AB_S1_IDLE_GET(_v)       ((_v >> 4) & 0x1)

#define BPORT1_AB_S2_POFFSET            0x5
#define BPORT1_AB_S2                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_S2_POFFSET)

#define BPORT1_AB_C3_POFFSET            0x6
#define BPORT1_AB_C3                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C3_POFFSET)

#define BPORT1_AB_D_POFFSET             0x7
#define BPORT1_AB_D                     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_D_POFFSET)

#define BPORT1_AB_MA1_POFFSET           0x8
#define BPORT1_AB_MA1                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MA1_POFFSET)

#define BPORT1_AB_MA2_POFFSET           0x9
#define BPORT1_AB_MA2                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MA2_POFFSET)

#define BPORT1_AB_C4_POFFSET            0xa
#define BPORT1_AB_C4                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C4_POFFSET)
#define BPORT1_AB_C4_BRFA               0x1f
#define BPORT1_AB_C4_BRFA_GET(_v)       (_v & 0x1f)

#define BPORT1_AB_C5_POFFSET            0xb
#define BPORT1_AB_C5                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C5_POFFSET)

#define BPORT1_AB_ED_POFFSET            0xc
#define BPORT1_AB_ED                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ED_POFFSET)

#define BPORT1_AB_MODEM_POFFSET         0xd
#define BPORT1_AB_MODEM                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MODEM_POFFSET)

#define BPORT1_AB_INFRARED_POFFSET      0xe
#define BPORT1_AB_INFRARED              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INFRARED_POFFSET)

#define BPORT1_AB_PFIFO_POFFSET         0x10
#define BPORT1_AB_PFIFO                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PFIFO_POFFSET)
#define BPORT1_AB_PFIFO_TXFE            (0x1 << 7)
#define BPORT1_AB_PFIFO_TXFE_GET(_v)    ((_v >> 7) & 0x1)
#define BPORT1_AB_PFIFO_TXFIFOSIZE      (0x7 << 4)
#define BPORT1_AB_PFIFO_TXFIFOSIZE_GET(_v)  ((_v >> 4) & 0x7)
#define BPORT1_AB_PFIFO_RXFE            (0x1 << 3)
#define BPORT1_AB_PFIFO_RXFE_GET(_v)    ((_v >> 3) & 0x1)
#define BPORT1_AB_PFIFO_RXFIFOSIZE      0x7
#define BPORT1_AB_PFIFO_RXFIFOSIZE_GET(_v)  (_v & 0x7)

#define BPORT1_AB_CFIFO_POFFSET         0x11
#define BPORT1_AB_CFIFO                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CFIFO_POFFSET)
#define BPORT1_AB_CFIFO_TXFLUSH         (0x1 << 7)
#define BPORT1_AB_CFIFO_TXFLUSH_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_CFIFO_RXFLUSH         (0x1 << 6)
#define BPORT1_AB_CFIFO_RXFLUSH_GET(_v)  ((_v >> 6) & 0x1)

#define BPORT1_AB_SFIFO_POFFSET         0x12
#define BPORT1_AB_SFIFO                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SFIFO_POFFSET)

#define BPORT1_AB_TWFIFO_POFFSET        0x13
#define BPORT1_AB_TWFIFO                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TWFIFO_POFFSET)

#define BPORT1_AB_TCFIFO_POFFSET        0x14
#define BPORT1_AB_TCFIFO                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCFIFO_POFFSET)

#define BPORT1_AB_RWFIFO_POFFSET        0x15
#define BPORT1_AB_RWFIFO                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RWFIFO_POFFSET)

#define BPORT1_AB_RCFIFO_POFFSET        0x16
#define BPORT1_AB_RCFIFO                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RCFIFO_POFFSET)


#endif

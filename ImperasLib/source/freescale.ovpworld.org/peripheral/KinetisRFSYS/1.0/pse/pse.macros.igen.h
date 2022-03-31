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
#define BPORT1_AB_REGA_POFFSET          0x0
#define BPORT1_AB_REGA                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REGA_POFFSET)
#define BPORT1_AB_REGA_HH               (0xff << 24)
#define BPORT1_AB_REGA_HH_GET(_v)       ((_v >> 24) & 0xff)
#define BPORT1_AB_REGA_HL               (0xff << 16)
#define BPORT1_AB_REGA_HL_GET(_v)       ((_v >> 16) & 0xff)
#define BPORT1_AB_REGA_LH               (0xff << 8)
#define BPORT1_AB_REGA_LH_GET(_v)       ((_v >> 8) & 0xff)
#define BPORT1_AB_REGA_LL               0xff
#define BPORT1_AB_REGA_LL_GET(_v)       (_v & 0xff)

#define BPORT1_AB_REGB_POFFSET          0x4
#define BPORT1_AB_REGB                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REGB_POFFSET)
#define BPORT1_AB_REGB_HH               (0xff << 24)
#define BPORT1_AB_REGB_HH_GET(_v)       ((_v >> 24) & 0xff)
#define BPORT1_AB_REGB_HL               (0xff << 16)
#define BPORT1_AB_REGB_HL_GET(_v)       ((_v >> 16) & 0xff)
#define BPORT1_AB_REGB_LH               (0xff << 8)
#define BPORT1_AB_REGB_LH_GET(_v)       ((_v >> 8) & 0xff)
#define BPORT1_AB_REGB_LL               0xff
#define BPORT1_AB_REGB_LL_GET(_v)       (_v & 0xff)

#define BPORT1_AB_REGC_POFFSET          0x8
#define BPORT1_AB_REGC                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REGC_POFFSET)
#define BPORT1_AB_REGC_HH               (0xff << 24)
#define BPORT1_AB_REGC_HH_GET(_v)       ((_v >> 24) & 0xff)
#define BPORT1_AB_REGC_HL               (0xff << 16)
#define BPORT1_AB_REGC_HL_GET(_v)       ((_v >> 16) & 0xff)
#define BPORT1_AB_REGC_LH               (0xff << 8)
#define BPORT1_AB_REGC_LH_GET(_v)       ((_v >> 8) & 0xff)
#define BPORT1_AB_REGC_LL               0xff
#define BPORT1_AB_REGC_LL_GET(_v)       (_v & 0xff)

#define BPORT1_AB_REGD_POFFSET          0xc
#define BPORT1_AB_REGD                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REGD_POFFSET)
#define BPORT1_AB_REGD_HH               (0xff << 24)
#define BPORT1_AB_REGD_HH_GET(_v)       ((_v >> 24) & 0xff)
#define BPORT1_AB_REGD_HL               (0xff << 16)
#define BPORT1_AB_REGD_HL_GET(_v)       ((_v >> 16) & 0xff)
#define BPORT1_AB_REGD_LH               (0xff << 8)
#define BPORT1_AB_REGD_LH_GET(_v)       ((_v >> 8) & 0xff)
#define BPORT1_AB_REGD_LL               0xff
#define BPORT1_AB_REGD_LL_GET(_v)       (_v & 0xff)

#define BPORT1_AB_REGE_POFFSET          0x10
#define BPORT1_AB_REGE                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REGE_POFFSET)
#define BPORT1_AB_REGE_HH               (0xff << 24)
#define BPORT1_AB_REGE_HH_GET(_v)       ((_v >> 24) & 0xff)
#define BPORT1_AB_REGE_HL               (0xff << 16)
#define BPORT1_AB_REGE_HL_GET(_v)       ((_v >> 16) & 0xff)
#define BPORT1_AB_REGE_LH               (0xff << 8)
#define BPORT1_AB_REGE_LH_GET(_v)       ((_v >> 8) & 0xff)
#define BPORT1_AB_REGE_LL               0xff
#define BPORT1_AB_REGE_LL_GET(_v)       (_v & 0xff)

#define BPORT1_AB_REGF_POFFSET          0x14
#define BPORT1_AB_REGF                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REGF_POFFSET)
#define BPORT1_AB_REGF_HH               (0xff << 24)
#define BPORT1_AB_REGF_HH_GET(_v)       ((_v >> 24) & 0xff)
#define BPORT1_AB_REGF_HL               (0xff << 16)
#define BPORT1_AB_REGF_HL_GET(_v)       ((_v >> 16) & 0xff)
#define BPORT1_AB_REGF_LH               (0xff << 8)
#define BPORT1_AB_REGF_LH_GET(_v)       ((_v >> 8) & 0xff)
#define BPORT1_AB_REGF_LL               0xff
#define BPORT1_AB_REGF_LL_GET(_v)       (_v & 0xff)

#define BPORT1_AB_REGG_POFFSET          0x18
#define BPORT1_AB_REGG                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REGG_POFFSET)
#define BPORT1_AB_REGG_HH               (0xff << 24)
#define BPORT1_AB_REGG_HH_GET(_v)       ((_v >> 24) & 0xff)
#define BPORT1_AB_REGG_HL               (0xff << 16)
#define BPORT1_AB_REGG_HL_GET(_v)       ((_v >> 16) & 0xff)
#define BPORT1_AB_REGG_LH               (0xff << 8)
#define BPORT1_AB_REGG_LH_GET(_v)       ((_v >> 8) & 0xff)
#define BPORT1_AB_REGG_LL               0xff
#define BPORT1_AB_REGG_LL_GET(_v)       (_v & 0xff)

#define BPORT1_AB_REGH_POFFSET          0x1c
#define BPORT1_AB_REGH                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REGH_POFFSET)
#define BPORT1_AB_REGH_HH               (0xff << 24)
#define BPORT1_AB_REGH_HH_GET(_v)       ((_v >> 24) & 0xff)
#define BPORT1_AB_REGH_HL               (0xff << 16)
#define BPORT1_AB_REGH_HL_GET(_v)       ((_v >> 16) & 0xff)
#define BPORT1_AB_REGH_LH               (0xff << 8)
#define BPORT1_AB_REGH_LH_GET(_v)       ((_v >> 8) & 0xff)
#define BPORT1_AB_REGH_LL               0xff
#define BPORT1_AB_REGH_LL_GET(_v)       (_v & 0xff)


#endif

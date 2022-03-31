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
#define BPORT1_AB_CONTROL_POFFSET       0x0
#define BPORT1_AB_CONTROL               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CONTROL_POFFSET)
#define BPORT1_AB_CONTROL_IACK          0x1
#define BPORT1_AB_CONTROL_IACK_GET(_v)  (_v & 0x1)
#define BPORT1_AB_CONTROL_IE            (0x1 << 16)
#define BPORT1_AB_CONTROL_IE_GET(_v)    ((_v >> 16) & 0x1)
#define BPORT1_AB_CONTROL_IF            (0x1 << 8)
#define BPORT1_AB_CONTROL_IF_GET(_v)    ((_v >> 8) & 0x1)
#define BPORT1_AB_CONTROL_SR            (0x1 << 25)
#define BPORT1_AB_CONTROL_SR_GET(_v)    ((_v >> 25) & 0x1)
#define BPORT1_AB_CONTROL_START         (0x1 << 24)
#define BPORT1_AB_CONTROL_START_GET(_v)  ((_v >> 24) & 0x1)

#define BPORT1_AB_CLOCK_POFFSET         0x4
#define BPORT1_AB_CLOCK                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CLOCK_POFFSET)
#define BPORT1_AB_CLOCK_CLOCK_SPEED     (0x3ff << 2)
#define BPORT1_AB_CLOCK_CLOCK_SPEED_GET(_v)  ((_v >> 2) & 0x3ff)
#define BPORT1_AB_CLOCK_CLOCK_UNIT      0x1
#define BPORT1_AB_CLOCK_CLOCK_UNIT_GET(_v)  (_v & 0x1)

#define BPORT1_AB_STATUS_POFFSET        0x8
#define BPORT1_AB_STATUS                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_STATUS_POFFSET)
#define BPORT1_AB_STATUS_ACTIVE         (0x1 << 22)
#define BPORT1_AB_STATUS_ACTIVE_GET(_v)  ((_v >> 22) & 0x1)
#define BPORT1_AB_STATUS_ERR            (0x1 << 20)
#define BPORT1_AB_STATUS_ERR_GET(_v)    ((_v >> 20) & 0x1)
#define BPORT1_AB_STATUS_SEQ_RES        (0x3 << 16)
#define BPORT1_AB_STATUS_SEQ_RES_GET(_v)  ((_v >> 16) & 0x3)
#define BPORT1_AB_STATUS_SEQ_STAT       (0x3 << 18)
#define BPORT1_AB_STATUS_SEQ_STAT_GET(_v)  ((_v >> 18) & 0x3)
#define BPORT1_AB_STATUS_TO             (0x1 << 21)
#define BPORT1_AB_STATUS_TO_GET(_v)     ((_v >> 21) & 0x1)

#define BPORT1_AB_TIMER0_POFFSET        0x10
#define BPORT1_AB_TIMER0                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TIMER0_POFFSET)
#define BPORT1_AB_TIMER0_TSEQ_INIT      (0x3ff << 16)
#define BPORT1_AB_TIMER0_TSEQ_INIT_GET(_v)  ((_v >> 16) & 0x3ff)
#define BPORT1_AB_TIMER0_TUNITCON       0xfff
#define BPORT1_AB_TIMER0_TUNITCON_GET(_v)  (_v & 0xfff)

#define BPORT1_AB_TIMER1_POFFSET        0x14
#define BPORT1_AB_TIMER1                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TIMER1_POFFSET)
#define BPORT1_AB_TIMER1_TDCD_DBNC      (0x3ff << 16)
#define BPORT1_AB_TIMER1_TDCD_DBNC_GET(_v)  ((_v >> 16) & 0x3ff)
#define BPORT1_AB_TIMER1_TVDPSRC_ON     0x3ff
#define BPORT1_AB_TIMER1_TVDPSRC_ON_GET(_v)  (_v & 0x3ff)

#define BPORT1_AB_TIMER2_POFFSET        0x18
#define BPORT1_AB_TIMER2                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TIMER2_POFFSET)
#define BPORT1_AB_TIMER2_CHECK_DM       0xf
#define BPORT1_AB_TIMER2_CHECK_DM_GET(_v)  (_v & 0xf)
#define BPORT1_AB_TIMER2_TVDPSRC_CON    (0x3ff << 16)
#define BPORT1_AB_TIMER2_TVDPSRC_CON_GET(_v)  ((_v >> 16) & 0x3ff)


#endif

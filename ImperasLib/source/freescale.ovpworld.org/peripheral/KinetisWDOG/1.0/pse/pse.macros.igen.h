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
#define BPORT1_AB_STCTRLH_POFFSET       0x0
#define BPORT1_AB_STCTRLH               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_STCTRLH_POFFSET)
#define BPORT1_AB_STCTRLH_ALLOWUPDATE   (0x1 << 4)
#define BPORT1_AB_STCTRLH_ALLOWUPDATE_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_STCTRLH_BYTESEL       (0x3 << 12)
#define BPORT1_AB_STCTRLH_BYTESEL_GET(_v)  ((_v >> 12) & 0x3)
#define BPORT1_AB_STCTRLH_CLKSRC        (0x1 << 1)
#define BPORT1_AB_STCTRLH_CLKSRC_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_STCTRLH_DBGEN         (0x1 << 5)
#define BPORT1_AB_STCTRLH_DBGEN_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_STCTRLH_DISTESTWDOG   (0x1 << 14)
#define BPORT1_AB_STCTRLH_DISTESTWDOG_GET(_v)  ((_v >> 14) & 0x1)
#define BPORT1_AB_STCTRLH_IRQRSTEN      (0x1 << 2)
#define BPORT1_AB_STCTRLH_IRQRSTEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_STCTRLH_STNDBYEN      (0x1 << 8)
#define BPORT1_AB_STCTRLH_STNDBYEN_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_STCTRLH_STOPEN        (0x1 << 6)
#define BPORT1_AB_STCTRLH_STOPEN_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_STCTRLH_TESTSEL       (0x1 << 11)
#define BPORT1_AB_STCTRLH_TESTSEL_GET(_v)  ((_v >> 11) & 0x1)
#define BPORT1_AB_STCTRLH_TESTWDOG      (0x1 << 10)
#define BPORT1_AB_STCTRLH_TESTWDOG_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_STCTRLH_WAITEN        (0x1 << 7)
#define BPORT1_AB_STCTRLH_WAITEN_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_STCTRLH_WDOGEN        0x1
#define BPORT1_AB_STCTRLH_WDOGEN_GET(_v)  (_v & 0x1)
#define BPORT1_AB_STCTRLH_WINEN         (0x1 << 3)
#define BPORT1_AB_STCTRLH_WINEN_GET(_v)  ((_v >> 3) & 0x1)

#define BPORT1_AB_STCTRLL_POFFSET       0x2
#define BPORT1_AB_STCTRLL               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_STCTRLL_POFFSET)
#define BPORT1_AB_STCTRLL_INTFLG        (0x1 << 15)
#define BPORT1_AB_STCTRLL_INTFLG_GET(_v)  ((_v >> 15) & 0x1)

#define BPORT1_AB_TOVALH_POFFSET        0x4
#define BPORT1_AB_TOVALH                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TOVALH_POFFSET)
#define BPORT1_AB_TOVALH_TOVALHIGH      0xffff
#define BPORT1_AB_TOVALH_TOVALHIGH_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_TOVALL_POFFSET        0x6
#define BPORT1_AB_TOVALL                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TOVALL_POFFSET)
#define BPORT1_AB_TOVALL_TOVALLOW       0xffff
#define BPORT1_AB_TOVALL_TOVALLOW_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_WINH_POFFSET          0x8
#define BPORT1_AB_WINH                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WINH_POFFSET)
#define BPORT1_AB_WINH_WINHIGH          0xffff
#define BPORT1_AB_WINH_WINHIGH_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_WINL_POFFSET          0xa
#define BPORT1_AB_WINL                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WINL_POFFSET)
#define BPORT1_AB_WINL_WINLOW           0xffff
#define BPORT1_AB_WINL_WINLOW_GET(_v)   (_v & 0xffff)

#define BPORT1_AB_REFRESH_POFFSET       0xc
#define BPORT1_AB_REFRESH               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REFRESH_POFFSET)
#define BPORT1_AB_REFRESH_WDOGREFRESH   0xffff
#define BPORT1_AB_REFRESH_WDOGREFRESH_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_UNLOCK_POFFSET        0xe
#define BPORT1_AB_UNLOCK                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UNLOCK_POFFSET)
#define BPORT1_AB_UNLOCK_WDOGUNLOCK     0xffff
#define BPORT1_AB_UNLOCK_WDOGUNLOCK_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_TMROUTH_POFFSET       0x10
#define BPORT1_AB_TMROUTH               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TMROUTH_POFFSET)
#define BPORT1_AB_TMROUTH_TIMEROUTHIGH  0xffff
#define BPORT1_AB_TMROUTH_TIMEROUTHIGH_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_TMROUTL_POFFSET       0x12
#define BPORT1_AB_TMROUTL               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TMROUTL_POFFSET)
#define BPORT1_AB_TMROUTL_TIMEROUTLOW   0xffff
#define BPORT1_AB_TMROUTL_TIMEROUTLOW_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_RSTCNT_POFFSET        0x14
#define BPORT1_AB_RSTCNT                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RSTCNT_POFFSET)
#define BPORT1_AB_RSTCNT_RSTCNT         0xffff
#define BPORT1_AB_RSTCNT_RSTCNT_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_PRESC_POFFSET         0x16
#define BPORT1_AB_PRESC                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PRESC_POFFSET)
#define BPORT1_AB_PRESC_PRESCVAL        (0x7 << 8)
#define BPORT1_AB_PRESC_PRESCVAL_GET(_v)  ((_v >> 8) & 0x7)


#endif

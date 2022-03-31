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
#define BPORT1_AB_C1_POFFSET            0x0
#define BPORT1_AB_C1                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C1_POFFSET)
#define BPORT1_AB_C1_CLKS               (0x3 << 6)
#define BPORT1_AB_C1_CLKS_GET(_v)       ((_v >> 6) & 0x3)
#define BPORT1_AB_C1_FRDIV              (0x7 << 3)
#define BPORT1_AB_C1_FRDIV_GET(_v)      ((_v >> 3) & 0x7)
#define BPORT1_AB_C1_IRCLKEN            (0x1 << 1)
#define BPORT1_AB_C1_IRCLKEN_GET(_v)    ((_v >> 1) & 0x1)
#define BPORT1_AB_C1_IREFS              (0x1 << 2)
#define BPORT1_AB_C1_IREFS_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_C1_IREFSTEN           0x1
#define BPORT1_AB_C1_IREFSTEN_GET(_v)   (_v & 0x1)

#define BPORT1_AB_C2_POFFSET            0x1
#define BPORT1_AB_C2                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C2_POFFSET)
#define BPORT1_AB_C2_EREFS0             (0x1 << 2)
#define BPORT1_AB_C2_EREFS0_GET(_v)     ((_v >> 2) & 0x1)
#define BPORT1_AB_C2_HGO0               (0x1 << 3)
#define BPORT1_AB_C2_HGO0_GET(_v)       ((_v >> 3) & 0x1)
#define BPORT1_AB_C2_IRCS               0x1
#define BPORT1_AB_C2_IRCS_GET(_v)       (_v & 0x1)
#define BPORT1_AB_C2_LOCRE0             (0x1 << 7)
#define BPORT1_AB_C2_LOCRE0_GET(_v)     ((_v >> 7) & 0x1)
#define BPORT1_AB_C2_LP                 (0x1 << 1)
#define BPORT1_AB_C2_LP_GET(_v)         ((_v >> 1) & 0x1)
#define BPORT1_AB_C2_RANGE0             (0x3 << 4)
#define BPORT1_AB_C2_RANGE0_GET(_v)     ((_v >> 4) & 0x3)

#define BPORT1_AB_C3_POFFSET            0x2
#define BPORT1_AB_C3                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C3_POFFSET)
#define BPORT1_AB_C3_SCTRIM             0xff
#define BPORT1_AB_C3_SCTRIM_GET(_v)     (_v & 0xff)

#define BPORT1_AB_C4_POFFSET            0x3
#define BPORT1_AB_C4                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C4_POFFSET)
#define BPORT1_AB_C4_DMX32              (0x1 << 7)
#define BPORT1_AB_C4_DMX32_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_C4_DRST_DRS           (0x3 << 5)
#define BPORT1_AB_C4_DRST_DRS_GET(_v)   ((_v >> 5) & 0x3)
#define BPORT1_AB_C4_FCTRIM             (0xf << 1)
#define BPORT1_AB_C4_FCTRIM_GET(_v)     ((_v >> 1) & 0xf)
#define BPORT1_AB_C4_SCFTRIM            0x1
#define BPORT1_AB_C4_SCFTRIM_GET(_v)    (_v & 0x1)

#define BPORT1_AB_C5_POFFSET            0x4
#define BPORT1_AB_C5                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C5_POFFSET)
#define BPORT1_AB_C5_PLLCLKEN0          (0x1 << 6)
#define BPORT1_AB_C5_PLLCLKEN0_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_C5_PLLREFSEL0         (0x1 << 7)
#define BPORT1_AB_C5_PLLREFSEL0_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_C5_PLLSTEN0           (0x1 << 5)
#define BPORT1_AB_C5_PLLSTEN0_GET(_v)   ((_v >> 5) & 0x1)
#define BPORT1_AB_C5_PRDIV0             0x7
#define BPORT1_AB_C5_PRDIV0_GET(_v)     (_v & 0x7)

#define BPORT1_AB_C6_POFFSET            0x5
#define BPORT1_AB_C6                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C6_POFFSET)
#define BPORT1_AB_C6_CME0               (0x1 << 5)
#define BPORT1_AB_C6_CME0_GET(_v)       ((_v >> 5) & 0x1)
#define BPORT1_AB_C6_LOLIE0             (0x1 << 7)
#define BPORT1_AB_C6_LOLIE0_GET(_v)     ((_v >> 7) & 0x1)
#define BPORT1_AB_C6_PLLS               (0x1 << 6)
#define BPORT1_AB_C6_PLLS_GET(_v)       ((_v >> 6) & 0x1)
#define BPORT1_AB_C6_VDIV0              0x1f
#define BPORT1_AB_C6_VDIV0_GET(_v)      (_v & 0x1f)

#define BPORT1_AB_S_POFFSET             0x6
#define BPORT1_AB_S                     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_S_POFFSET)
#define BPORT1_AB_S_CLKST               (0x3 << 2)
#define BPORT1_AB_S_CLKST_GET(_v)       ((_v >> 2) & 0x3)
#define BPORT1_AB_S_IRCST               0x1
#define BPORT1_AB_S_IRCST_GET(_v)       (_v & 0x1)
#define BPORT1_AB_S_IREFST              (0x1 << 4)
#define BPORT1_AB_S_IREFST_GET(_v)      ((_v >> 4) & 0x1)
#define BPORT1_AB_S_LOCK0               (0x1 << 6)
#define BPORT1_AB_S_LOCK0_GET(_v)       ((_v >> 6) & 0x1)
#define BPORT1_AB_S_LOLS0               (0x1 << 7)
#define BPORT1_AB_S_LOLS0_GET(_v)       ((_v >> 7) & 0x1)
#define BPORT1_AB_S_OSCINIT0            (0x1 << 1)
#define BPORT1_AB_S_OSCINIT0_GET(_v)    ((_v >> 1) & 0x1)
#define BPORT1_AB_S_PLLST               (0x1 << 5)
#define BPORT1_AB_S_PLLST_GET(_v)       ((_v >> 5) & 0x1)

#define BPORT1_AB_SC_POFFSET            0x8
#define BPORT1_AB_SC                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SC_POFFSET)
#define BPORT1_AB_SC_ATME               (0x1 << 7)
#define BPORT1_AB_SC_ATME_GET(_v)       ((_v >> 7) & 0x1)
#define BPORT1_AB_SC_ATMF               (0x1 << 5)
#define BPORT1_AB_SC_ATMF_GET(_v)       ((_v >> 5) & 0x1)
#define BPORT1_AB_SC_ATMS               (0x1 << 6)
#define BPORT1_AB_SC_ATMS_GET(_v)       ((_v >> 6) & 0x1)
#define BPORT1_AB_SC_FCIRDIV            (0x7 << 1)
#define BPORT1_AB_SC_FCIRDIV_GET(_v)    ((_v >> 1) & 0x7)
#define BPORT1_AB_SC_FLTPRSRV           (0x1 << 4)
#define BPORT1_AB_SC_FLTPRSRV_GET(_v)   ((_v >> 4) & 0x1)
#define BPORT1_AB_SC_LOCS0              0x1
#define BPORT1_AB_SC_LOCS0_GET(_v)      (_v & 0x1)

#define BPORT1_AB_ATCVH_POFFSET         0xa
#define BPORT1_AB_ATCVH                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ATCVH_POFFSET)
#define BPORT1_AB_ATCVH_ATCVH           0xff
#define BPORT1_AB_ATCVH_ATCVH_GET(_v)   (_v & 0xff)

#define BPORT1_AB_ATCVL_POFFSET         0xb
#define BPORT1_AB_ATCVL                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ATCVL_POFFSET)
#define BPORT1_AB_ATCVL_ATCVL           0xff
#define BPORT1_AB_ATCVL_ATCVL_GET(_v)   (_v & 0xff)

#define BPORT1_AB_C7_POFFSET            0xc
#define BPORT1_AB_C7                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C7_POFFSET)
#define BPORT1_AB_C7_OSCSEL             0x1
#define BPORT1_AB_C7_OSCSEL_GET(_v)     (_v & 0x1)

#define BPORT1_AB_C8_POFFSET            0xd
#define BPORT1_AB_C8                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C8_POFFSET)
#define BPORT1_AB_C8_CME1               (0x1 << 5)
#define BPORT1_AB_C8_CME1_GET(_v)       ((_v >> 5) & 0x1)
#define BPORT1_AB_C8_LOCRE1             (0x1 << 7)
#define BPORT1_AB_C8_LOCRE1_GET(_v)     ((_v >> 7) & 0x1)
#define BPORT1_AB_C8_LOCS1              0x1
#define BPORT1_AB_C8_LOCS1_GET(_v)      (_v & 0x1)

#define BPORT1_AB_C10_POFFSET           0xf
#define BPORT1_AB_C10                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C10_POFFSET)
#define BPORT1_AB_C10_EREFS1            (0x1 << 2)
#define BPORT1_AB_C10_EREFS1_GET(_v)    ((_v >> 2) & 0x1)
#define BPORT1_AB_C10_HGO1              (0x1 << 3)
#define BPORT1_AB_C10_HGO1_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_C10_LOCRE2            (0x1 << 7)
#define BPORT1_AB_C10_LOCRE2_GET(_v)    ((_v >> 7) & 0x1)
#define BPORT1_AB_C10_RANGE1            (0x3 << 4)
#define BPORT1_AB_C10_RANGE1_GET(_v)    ((_v >> 4) & 0x3)

#define BPORT1_AB_C11_POFFSET           0x10
#define BPORT1_AB_C11                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C11_POFFSET)
#define BPORT1_AB_C11_PLLCLKEN1         (0x1 << 6)
#define BPORT1_AB_C11_PLLCLKEN1_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_C11_PLLCS             (0x1 << 4)
#define BPORT1_AB_C11_PLLCS_GET(_v)     ((_v >> 4) & 0x1)
#define BPORT1_AB_C11_PLLREFSEL1        (0x1 << 7)
#define BPORT1_AB_C11_PLLREFSEL1_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_C11_PLLSTEN1          (0x1 << 5)
#define BPORT1_AB_C11_PLLSTEN1_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_C11_PRDIV1            0x7
#define BPORT1_AB_C11_PRDIV1_GET(_v)    (_v & 0x7)

#define BPORT1_AB_C12_POFFSET           0x11
#define BPORT1_AB_C12                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C12_POFFSET)
#define BPORT1_AB_C12_CME2              (0x1 << 5)
#define BPORT1_AB_C12_CME2_GET(_v)      ((_v >> 5) & 0x1)
#define BPORT1_AB_C12_LOLIE1            (0x1 << 7)
#define BPORT1_AB_C12_LOLIE1_GET(_v)    ((_v >> 7) & 0x1)
#define BPORT1_AB_C12_VDIV1             0x1f
#define BPORT1_AB_C12_VDIV1_GET(_v)     (_v & 0x1f)

#define BPORT1_AB_S2_POFFSET            0x12
#define BPORT1_AB_S2                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_S2_POFFSET)
#define BPORT1_AB_S2_LOCK2              (0x1 << 6)
#define BPORT1_AB_S2_LOCK2_GET(_v)      ((_v >> 6) & 0x1)
#define BPORT1_AB_S2_LOCS2              0x1
#define BPORT1_AB_S2_LOCS2_GET(_v)      (_v & 0x1)
#define BPORT1_AB_S2_LOLS2              (0x1 << 7)
#define BPORT1_AB_S2_LOLS2_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_S2_OSCINIT2           (0x1 << 1)
#define BPORT1_AB_S2_OSCINIT2_GET(_v)   ((_v >> 1) & 0x1)
#define BPORT1_AB_S2_PLLCST             (0x1 << 4)
#define BPORT1_AB_S2_PLLCST_GET(_v)     ((_v >> 4) & 0x1)


#endif

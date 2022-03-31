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
#define BPORT1_AB_CSAR0_POFFSET         0x0
#define BPORT1_AB_CSAR0                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CSAR0_POFFSET)
#define BPORT1_AB_CSAR0_BA              (0xffff << 16)
#define BPORT1_AB_CSAR0_BA_GET(_v)      ((_v >> 16) & 0xffff)

#define BPORT1_AB_CSMR0_POFFSET         0x4
#define BPORT1_AB_CSMR0                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CSMR0_POFFSET)
#define BPORT1_AB_CSMR0_BAM             (0xffff << 16)
#define BPORT1_AB_CSMR0_BAM_GET(_v)     ((_v >> 16) & 0xffff)
#define BPORT1_AB_CSMR0_V               0x1
#define BPORT1_AB_CSMR0_V_GET(_v)       (_v & 0x1)
#define BPORT1_AB_CSMR0_WP              (0x1 << 8)
#define BPORT1_AB_CSMR0_WP_GET(_v)      ((_v >> 8) & 0x1)

#define BPORT1_AB_CSCR0_POFFSET         0x8
#define BPORT1_AB_CSCR0                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CSCR0_POFFSET)
#define BPORT1_AB_CSCR0_AA              (0x1 << 8)
#define BPORT1_AB_CSCR0_AA_GET(_v)      ((_v >> 8) & 0x1)
#define BPORT1_AB_CSCR0_ASET            (0x3 << 20)
#define BPORT1_AB_CSCR0_ASET_GET(_v)    ((_v >> 20) & 0x3)
#define BPORT1_AB_CSCR0_BEM             (0x1 << 5)
#define BPORT1_AB_CSCR0_BEM_GET(_v)     ((_v >> 5) & 0x1)
#define BPORT1_AB_CSCR0_BLS             (0x1 << 9)
#define BPORT1_AB_CSCR0_BLS_GET(_v)     ((_v >> 9) & 0x1)
#define BPORT1_AB_CSCR0_BSTR            (0x1 << 4)
#define BPORT1_AB_CSCR0_BSTR_GET(_v)    ((_v >> 4) & 0x1)
#define BPORT1_AB_CSCR0_BSTW            (0x1 << 3)
#define BPORT1_AB_CSCR0_BSTW_GET(_v)    ((_v >> 3) & 0x1)
#define BPORT1_AB_CSCR0_EXTS            (0x1 << 22)
#define BPORT1_AB_CSCR0_EXTS_GET(_v)    ((_v >> 22) & 0x1)
#define BPORT1_AB_CSCR0_PS              (0x3 << 6)
#define BPORT1_AB_CSCR0_PS_GET(_v)      ((_v >> 6) & 0x3)
#define BPORT1_AB_CSCR0_RDAH            (0x3 << 18)
#define BPORT1_AB_CSCR0_RDAH_GET(_v)    ((_v >> 18) & 0x3)
#define BPORT1_AB_CSCR0_SWS             (0x3f << 26)
#define BPORT1_AB_CSCR0_SWS_GET(_v)     ((_v >> 26) & 0x3f)
#define BPORT1_AB_CSCR0_SWSEN           (0x1 << 23)
#define BPORT1_AB_CSCR0_SWSEN_GET(_v)   ((_v >> 23) & 0x1)
#define BPORT1_AB_CSCR0_WRAH            (0x3 << 16)
#define BPORT1_AB_CSCR0_WRAH_GET(_v)    ((_v >> 16) & 0x3)
#define BPORT1_AB_CSCR0_WS              (0x3f << 10)
#define BPORT1_AB_CSCR0_WS_GET(_v)      ((_v >> 10) & 0x3f)

#define BPORT1_AB_CSAR1_POFFSET         0xc
#define BPORT1_AB_CSAR1                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CSAR1_POFFSET)
#define BPORT1_AB_CSAR1_BA              (0xffff << 16)
#define BPORT1_AB_CSAR1_BA_GET(_v)      ((_v >> 16) & 0xffff)

#define BPORT1_AB_CSMR1_POFFSET         0x10
#define BPORT1_AB_CSMR1                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CSMR1_POFFSET)
#define BPORT1_AB_CSMR1_BAM             (0xffff << 16)
#define BPORT1_AB_CSMR1_BAM_GET(_v)     ((_v >> 16) & 0xffff)
#define BPORT1_AB_CSMR1_V               0x1
#define BPORT1_AB_CSMR1_V_GET(_v)       (_v & 0x1)
#define BPORT1_AB_CSMR1_WP              (0x1 << 8)
#define BPORT1_AB_CSMR1_WP_GET(_v)      ((_v >> 8) & 0x1)

#define BPORT1_AB_CSCR1_POFFSET         0x14
#define BPORT1_AB_CSCR1                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CSCR1_POFFSET)
#define BPORT1_AB_CSCR1_AA              (0x1 << 8)
#define BPORT1_AB_CSCR1_AA_GET(_v)      ((_v >> 8) & 0x1)
#define BPORT1_AB_CSCR1_ASET            (0x3 << 20)
#define BPORT1_AB_CSCR1_ASET_GET(_v)    ((_v >> 20) & 0x3)
#define BPORT1_AB_CSCR1_BEM             (0x1 << 5)
#define BPORT1_AB_CSCR1_BEM_GET(_v)     ((_v >> 5) & 0x1)
#define BPORT1_AB_CSCR1_BLS             (0x1 << 9)
#define BPORT1_AB_CSCR1_BLS_GET(_v)     ((_v >> 9) & 0x1)
#define BPORT1_AB_CSCR1_BSTR            (0x1 << 4)
#define BPORT1_AB_CSCR1_BSTR_GET(_v)    ((_v >> 4) & 0x1)
#define BPORT1_AB_CSCR1_BSTW            (0x1 << 3)
#define BPORT1_AB_CSCR1_BSTW_GET(_v)    ((_v >> 3) & 0x1)
#define BPORT1_AB_CSCR1_EXTS            (0x1 << 22)
#define BPORT1_AB_CSCR1_EXTS_GET(_v)    ((_v >> 22) & 0x1)
#define BPORT1_AB_CSCR1_PS              (0x3 << 6)
#define BPORT1_AB_CSCR1_PS_GET(_v)      ((_v >> 6) & 0x3)
#define BPORT1_AB_CSCR1_RDAH            (0x3 << 18)
#define BPORT1_AB_CSCR1_RDAH_GET(_v)    ((_v >> 18) & 0x3)
#define BPORT1_AB_CSCR1_SWS             (0x3f << 26)
#define BPORT1_AB_CSCR1_SWS_GET(_v)     ((_v >> 26) & 0x3f)
#define BPORT1_AB_CSCR1_SWSEN           (0x1 << 23)
#define BPORT1_AB_CSCR1_SWSEN_GET(_v)   ((_v >> 23) & 0x1)
#define BPORT1_AB_CSCR1_WRAH            (0x3 << 16)
#define BPORT1_AB_CSCR1_WRAH_GET(_v)    ((_v >> 16) & 0x3)
#define BPORT1_AB_CSCR1_WS              (0x3f << 10)
#define BPORT1_AB_CSCR1_WS_GET(_v)      ((_v >> 10) & 0x3f)

#define BPORT1_AB_CSAR2_POFFSET         0x18
#define BPORT1_AB_CSAR2                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CSAR2_POFFSET)
#define BPORT1_AB_CSAR2_BA              (0xffff << 16)
#define BPORT1_AB_CSAR2_BA_GET(_v)      ((_v >> 16) & 0xffff)

#define BPORT1_AB_CSMR2_POFFSET         0x1c
#define BPORT1_AB_CSMR2                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CSMR2_POFFSET)
#define BPORT1_AB_CSMR2_BAM             (0xffff << 16)
#define BPORT1_AB_CSMR2_BAM_GET(_v)     ((_v >> 16) & 0xffff)
#define BPORT1_AB_CSMR2_V               0x1
#define BPORT1_AB_CSMR2_V_GET(_v)       (_v & 0x1)
#define BPORT1_AB_CSMR2_WP              (0x1 << 8)
#define BPORT1_AB_CSMR2_WP_GET(_v)      ((_v >> 8) & 0x1)

#define BPORT1_AB_CSCR2_POFFSET         0x20
#define BPORT1_AB_CSCR2                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CSCR2_POFFSET)
#define BPORT1_AB_CSCR2_AA              (0x1 << 8)
#define BPORT1_AB_CSCR2_AA_GET(_v)      ((_v >> 8) & 0x1)
#define BPORT1_AB_CSCR2_ASET            (0x3 << 20)
#define BPORT1_AB_CSCR2_ASET_GET(_v)    ((_v >> 20) & 0x3)
#define BPORT1_AB_CSCR2_BEM             (0x1 << 5)
#define BPORT1_AB_CSCR2_BEM_GET(_v)     ((_v >> 5) & 0x1)
#define BPORT1_AB_CSCR2_BLS             (0x1 << 9)
#define BPORT1_AB_CSCR2_BLS_GET(_v)     ((_v >> 9) & 0x1)
#define BPORT1_AB_CSCR2_BSTR            (0x1 << 4)
#define BPORT1_AB_CSCR2_BSTR_GET(_v)    ((_v >> 4) & 0x1)
#define BPORT1_AB_CSCR2_BSTW            (0x1 << 3)
#define BPORT1_AB_CSCR2_BSTW_GET(_v)    ((_v >> 3) & 0x1)
#define BPORT1_AB_CSCR2_EXTS            (0x1 << 22)
#define BPORT1_AB_CSCR2_EXTS_GET(_v)    ((_v >> 22) & 0x1)
#define BPORT1_AB_CSCR2_PS              (0x3 << 6)
#define BPORT1_AB_CSCR2_PS_GET(_v)      ((_v >> 6) & 0x3)
#define BPORT1_AB_CSCR2_RDAH            (0x3 << 18)
#define BPORT1_AB_CSCR2_RDAH_GET(_v)    ((_v >> 18) & 0x3)
#define BPORT1_AB_CSCR2_SWS             (0x3f << 26)
#define BPORT1_AB_CSCR2_SWS_GET(_v)     ((_v >> 26) & 0x3f)
#define BPORT1_AB_CSCR2_SWSEN           (0x1 << 23)
#define BPORT1_AB_CSCR2_SWSEN_GET(_v)   ((_v >> 23) & 0x1)
#define BPORT1_AB_CSCR2_WRAH            (0x3 << 16)
#define BPORT1_AB_CSCR2_WRAH_GET(_v)    ((_v >> 16) & 0x3)
#define BPORT1_AB_CSCR2_WS              (0x3f << 10)
#define BPORT1_AB_CSCR2_WS_GET(_v)      ((_v >> 10) & 0x3f)

#define BPORT1_AB_CSAR3_POFFSET         0x24
#define BPORT1_AB_CSAR3                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CSAR3_POFFSET)
#define BPORT1_AB_CSAR3_BA              (0xffff << 16)
#define BPORT1_AB_CSAR3_BA_GET(_v)      ((_v >> 16) & 0xffff)

#define BPORT1_AB_CSMR3_POFFSET         0x28
#define BPORT1_AB_CSMR3                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CSMR3_POFFSET)
#define BPORT1_AB_CSMR3_BAM             (0xffff << 16)
#define BPORT1_AB_CSMR3_BAM_GET(_v)     ((_v >> 16) & 0xffff)
#define BPORT1_AB_CSMR3_V               0x1
#define BPORT1_AB_CSMR3_V_GET(_v)       (_v & 0x1)
#define BPORT1_AB_CSMR3_WP              (0x1 << 8)
#define BPORT1_AB_CSMR3_WP_GET(_v)      ((_v >> 8) & 0x1)

#define BPORT1_AB_CSCR3_POFFSET         0x2c
#define BPORT1_AB_CSCR3                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CSCR3_POFFSET)
#define BPORT1_AB_CSCR3_AA              (0x1 << 8)
#define BPORT1_AB_CSCR3_AA_GET(_v)      ((_v >> 8) & 0x1)
#define BPORT1_AB_CSCR3_ASET            (0x3 << 20)
#define BPORT1_AB_CSCR3_ASET_GET(_v)    ((_v >> 20) & 0x3)
#define BPORT1_AB_CSCR3_BEM             (0x1 << 5)
#define BPORT1_AB_CSCR3_BEM_GET(_v)     ((_v >> 5) & 0x1)
#define BPORT1_AB_CSCR3_BLS             (0x1 << 9)
#define BPORT1_AB_CSCR3_BLS_GET(_v)     ((_v >> 9) & 0x1)
#define BPORT1_AB_CSCR3_BSTR            (0x1 << 4)
#define BPORT1_AB_CSCR3_BSTR_GET(_v)    ((_v >> 4) & 0x1)
#define BPORT1_AB_CSCR3_BSTW            (0x1 << 3)
#define BPORT1_AB_CSCR3_BSTW_GET(_v)    ((_v >> 3) & 0x1)
#define BPORT1_AB_CSCR3_EXTS            (0x1 << 22)
#define BPORT1_AB_CSCR3_EXTS_GET(_v)    ((_v >> 22) & 0x1)
#define BPORT1_AB_CSCR3_PS              (0x3 << 6)
#define BPORT1_AB_CSCR3_PS_GET(_v)      ((_v >> 6) & 0x3)
#define BPORT1_AB_CSCR3_RDAH            (0x3 << 18)
#define BPORT1_AB_CSCR3_RDAH_GET(_v)    ((_v >> 18) & 0x3)
#define BPORT1_AB_CSCR3_SWS             (0x3f << 26)
#define BPORT1_AB_CSCR3_SWS_GET(_v)     ((_v >> 26) & 0x3f)
#define BPORT1_AB_CSCR3_SWSEN           (0x1 << 23)
#define BPORT1_AB_CSCR3_SWSEN_GET(_v)   ((_v >> 23) & 0x1)
#define BPORT1_AB_CSCR3_WRAH            (0x3 << 16)
#define BPORT1_AB_CSCR3_WRAH_GET(_v)    ((_v >> 16) & 0x3)
#define BPORT1_AB_CSCR3_WS              (0x3f << 10)
#define BPORT1_AB_CSCR3_WS_GET(_v)      ((_v >> 10) & 0x3f)

#define BPORT1_AB_CSAR4_POFFSET         0x30
#define BPORT1_AB_CSAR4                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CSAR4_POFFSET)
#define BPORT1_AB_CSAR4_BA              (0xffff << 16)
#define BPORT1_AB_CSAR4_BA_GET(_v)      ((_v >> 16) & 0xffff)

#define BPORT1_AB_CSMR4_POFFSET         0x34
#define BPORT1_AB_CSMR4                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CSMR4_POFFSET)
#define BPORT1_AB_CSMR4_BAM             (0xffff << 16)
#define BPORT1_AB_CSMR4_BAM_GET(_v)     ((_v >> 16) & 0xffff)
#define BPORT1_AB_CSMR4_V               0x1
#define BPORT1_AB_CSMR4_V_GET(_v)       (_v & 0x1)
#define BPORT1_AB_CSMR4_WP              (0x1 << 8)
#define BPORT1_AB_CSMR4_WP_GET(_v)      ((_v >> 8) & 0x1)

#define BPORT1_AB_CSCR4_POFFSET         0x38
#define BPORT1_AB_CSCR4                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CSCR4_POFFSET)
#define BPORT1_AB_CSCR4_AA              (0x1 << 8)
#define BPORT1_AB_CSCR4_AA_GET(_v)      ((_v >> 8) & 0x1)
#define BPORT1_AB_CSCR4_ASET            (0x3 << 20)
#define BPORT1_AB_CSCR4_ASET_GET(_v)    ((_v >> 20) & 0x3)
#define BPORT1_AB_CSCR4_BEM             (0x1 << 5)
#define BPORT1_AB_CSCR4_BEM_GET(_v)     ((_v >> 5) & 0x1)
#define BPORT1_AB_CSCR4_BLS             (0x1 << 9)
#define BPORT1_AB_CSCR4_BLS_GET(_v)     ((_v >> 9) & 0x1)
#define BPORT1_AB_CSCR4_BSTR            (0x1 << 4)
#define BPORT1_AB_CSCR4_BSTR_GET(_v)    ((_v >> 4) & 0x1)
#define BPORT1_AB_CSCR4_BSTW            (0x1 << 3)
#define BPORT1_AB_CSCR4_BSTW_GET(_v)    ((_v >> 3) & 0x1)
#define BPORT1_AB_CSCR4_EXTS            (0x1 << 22)
#define BPORT1_AB_CSCR4_EXTS_GET(_v)    ((_v >> 22) & 0x1)
#define BPORT1_AB_CSCR4_PS              (0x3 << 6)
#define BPORT1_AB_CSCR4_PS_GET(_v)      ((_v >> 6) & 0x3)
#define BPORT1_AB_CSCR4_RDAH            (0x3 << 18)
#define BPORT1_AB_CSCR4_RDAH_GET(_v)    ((_v >> 18) & 0x3)
#define BPORT1_AB_CSCR4_SWS             (0x3f << 26)
#define BPORT1_AB_CSCR4_SWS_GET(_v)     ((_v >> 26) & 0x3f)
#define BPORT1_AB_CSCR4_SWSEN           (0x1 << 23)
#define BPORT1_AB_CSCR4_SWSEN_GET(_v)   ((_v >> 23) & 0x1)
#define BPORT1_AB_CSCR4_WRAH            (0x3 << 16)
#define BPORT1_AB_CSCR4_WRAH_GET(_v)    ((_v >> 16) & 0x3)
#define BPORT1_AB_CSCR4_WS              (0x3f << 10)
#define BPORT1_AB_CSCR4_WS_GET(_v)      ((_v >> 10) & 0x3f)

#define BPORT1_AB_CSAR5_POFFSET         0x3c
#define BPORT1_AB_CSAR5                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CSAR5_POFFSET)
#define BPORT1_AB_CSAR5_BA              (0xffff << 16)
#define BPORT1_AB_CSAR5_BA_GET(_v)      ((_v >> 16) & 0xffff)

#define BPORT1_AB_CSMR5_POFFSET         0x40
#define BPORT1_AB_CSMR5                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CSMR5_POFFSET)
#define BPORT1_AB_CSMR5_BAM             (0xffff << 16)
#define BPORT1_AB_CSMR5_BAM_GET(_v)     ((_v >> 16) & 0xffff)
#define BPORT1_AB_CSMR5_V               0x1
#define BPORT1_AB_CSMR5_V_GET(_v)       (_v & 0x1)
#define BPORT1_AB_CSMR5_WP              (0x1 << 8)
#define BPORT1_AB_CSMR5_WP_GET(_v)      ((_v >> 8) & 0x1)

#define BPORT1_AB_CSCR5_POFFSET         0x44
#define BPORT1_AB_CSCR5                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CSCR5_POFFSET)
#define BPORT1_AB_CSCR5_AA              (0x1 << 8)
#define BPORT1_AB_CSCR5_AA_GET(_v)      ((_v >> 8) & 0x1)
#define BPORT1_AB_CSCR5_ASET            (0x3 << 20)
#define BPORT1_AB_CSCR5_ASET_GET(_v)    ((_v >> 20) & 0x3)
#define BPORT1_AB_CSCR5_BEM             (0x1 << 5)
#define BPORT1_AB_CSCR5_BEM_GET(_v)     ((_v >> 5) & 0x1)
#define BPORT1_AB_CSCR5_BLS             (0x1 << 9)
#define BPORT1_AB_CSCR5_BLS_GET(_v)     ((_v >> 9) & 0x1)
#define BPORT1_AB_CSCR5_BSTR            (0x1 << 4)
#define BPORT1_AB_CSCR5_BSTR_GET(_v)    ((_v >> 4) & 0x1)
#define BPORT1_AB_CSCR5_BSTW            (0x1 << 3)
#define BPORT1_AB_CSCR5_BSTW_GET(_v)    ((_v >> 3) & 0x1)
#define BPORT1_AB_CSCR5_EXTS            (0x1 << 22)
#define BPORT1_AB_CSCR5_EXTS_GET(_v)    ((_v >> 22) & 0x1)
#define BPORT1_AB_CSCR5_PS              (0x3 << 6)
#define BPORT1_AB_CSCR5_PS_GET(_v)      ((_v >> 6) & 0x3)
#define BPORT1_AB_CSCR5_RDAH            (0x3 << 18)
#define BPORT1_AB_CSCR5_RDAH_GET(_v)    ((_v >> 18) & 0x3)
#define BPORT1_AB_CSCR5_SWS             (0x3f << 26)
#define BPORT1_AB_CSCR5_SWS_GET(_v)     ((_v >> 26) & 0x3f)
#define BPORT1_AB_CSCR5_SWSEN           (0x1 << 23)
#define BPORT1_AB_CSCR5_SWSEN_GET(_v)   ((_v >> 23) & 0x1)
#define BPORT1_AB_CSCR5_WRAH            (0x3 << 16)
#define BPORT1_AB_CSCR5_WRAH_GET(_v)    ((_v >> 16) & 0x3)
#define BPORT1_AB_CSCR5_WS              (0x3f << 10)
#define BPORT1_AB_CSCR5_WS_GET(_v)      ((_v >> 10) & 0x3f)

#define BPORT1_AB_CSPMCR_POFFSET        0x60
#define BPORT1_AB_CSPMCR                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CSPMCR_POFFSET)
#define BPORT1_AB_CSPMCR_GROUP1         (0xf << 28)
#define BPORT1_AB_CSPMCR_GROUP1_GET(_v)  ((_v >> 28) & 0xf)
#define BPORT1_AB_CSPMCR_GROUP2         (0xf << 24)
#define BPORT1_AB_CSPMCR_GROUP2_GET(_v)  ((_v >> 24) & 0xf)
#define BPORT1_AB_CSPMCR_GROUP3         (0xf << 20)
#define BPORT1_AB_CSPMCR_GROUP3_GET(_v)  ((_v >> 20) & 0xf)
#define BPORT1_AB_CSPMCR_GROUP4         (0xf << 16)
#define BPORT1_AB_CSPMCR_GROUP4_GET(_v)  ((_v >> 16) & 0xf)
#define BPORT1_AB_CSPMCR_GROUP5         (0xf << 12)
#define BPORT1_AB_CSPMCR_GROUP5_GET(_v)  ((_v >> 12) & 0xf)


#endif

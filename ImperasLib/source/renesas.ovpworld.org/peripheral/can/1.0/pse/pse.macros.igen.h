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

// Set the macro 'BUSPORTGR' to the base of port 'busPortGR'
#ifndef BUSPORTGR
#error BUSPORTGR is undefined. It needs to be set to the port base address
#endif


#define BUSPORTGR_GR1_POFFSET           0x0
#define BUSPORTGR_GR1_GMCTRL_POFFSET    0x0
#define BUSPORTGR_GR1_GMCTRL            (BUSPORTGR + BUSPORTGR_GR1_POFFSET + BUSPORTGR_GR1_GMCTRL_POFFSET)

#define BUSPORTGR_GR1_GMCS_POFFSET      0x2
#define BUSPORTGR_GR1_GMCS              (BUSPORTGR + BUSPORTGR_GR1_POFFSET + BUSPORTGR_GR1_GMCS_POFFSET)

#define BUSPORTGR_GR1_GMABT_POFFSET     0x6
#define BUSPORTGR_GR1_GMABT             (BUSPORTGR + BUSPORTGR_GR1_POFFSET + BUSPORTGR_GR1_GMABT_POFFSET)

#define BUSPORTGR_GR1_GMABTD_POFFSET    0x8
#define BUSPORTGR_GR1_GMABTD            (BUSPORTGR + BUSPORTGR_GR1_POFFSET + BUSPORTGR_GR1_GMABTD_POFFSET)

#define BUSPORTGR_GR1_MASK1L_POFFSET    0x40
#define BUSPORTGR_GR1_MASK1L            (BUSPORTGR + BUSPORTGR_GR1_POFFSET + BUSPORTGR_GR1_MASK1L_POFFSET)

#define BUSPORTGR_GR1_MASK1H_POFFSET    0x42
#define BUSPORTGR_GR1_MASK1H            (BUSPORTGR + BUSPORTGR_GR1_POFFSET + BUSPORTGR_GR1_MASK1H_POFFSET)

#define BUSPORTGR_GR1_MASK2L_POFFSET    0x44
#define BUSPORTGR_GR1_MASK2L            (BUSPORTGR + BUSPORTGR_GR1_POFFSET + BUSPORTGR_GR1_MASK2L_POFFSET)

#define BUSPORTGR_GR1_MASK2H_POFFSET    0x46
#define BUSPORTGR_GR1_MASK2H            (BUSPORTGR + BUSPORTGR_GR1_POFFSET + BUSPORTGR_GR1_MASK2H_POFFSET)

#define BUSPORTGR_GR1_MASK3L_POFFSET    0x48
#define BUSPORTGR_GR1_MASK3L            (BUSPORTGR + BUSPORTGR_GR1_POFFSET + BUSPORTGR_GR1_MASK3L_POFFSET)

#define BUSPORTGR_GR1_MASK3H_POFFSET    0x4a
#define BUSPORTGR_GR1_MASK3H            (BUSPORTGR + BUSPORTGR_GR1_POFFSET + BUSPORTGR_GR1_MASK3H_POFFSET)

#define BUSPORTGR_GR1_MASK4L_POFFSET    0x4c
#define BUSPORTGR_GR1_MASK4L            (BUSPORTGR + BUSPORTGR_GR1_POFFSET + BUSPORTGR_GR1_MASK4L_POFFSET)

#define BUSPORTGR_GR1_MASK4H_POFFSET    0x4e
#define BUSPORTGR_GR1_MASK4H            (BUSPORTGR + BUSPORTGR_GR1_POFFSET + BUSPORTGR_GR1_MASK4H_POFFSET)

#define BUSPORTGR_GR1_CTRL_POFFSET      0x50
#define BUSPORTGR_GR1_CTRL              (BUSPORTGR + BUSPORTGR_GR1_POFFSET + BUSPORTGR_GR1_CTRL_POFFSET)

#define BUSPORTGR_GR2_POFFSET           0x52
#define BUSPORTGR_GR2_LEC_POFFSET       0x0
#define BUSPORTGR_GR2_LEC               (BUSPORTGR + BUSPORTGR_GR2_POFFSET + BUSPORTGR_GR2_LEC_POFFSET)

#define BUSPORTGR_GR2_INFO_POFFSET      0x1
#define BUSPORTGR_GR2_INFO              (BUSPORTGR + BUSPORTGR_GR2_POFFSET + BUSPORTGR_GR2_INFO_POFFSET)

#define BUSPORTGR_GR3_POFFSET           0x54
#define BUSPORTGR_GR3_ERC_POFFSET       0x0
#define BUSPORTGR_GR3_ERC               (BUSPORTGR + BUSPORTGR_GR3_POFFSET + BUSPORTGR_GR3_ERC_POFFSET)

#define BUSPORTGR_GR3_IE_POFFSET        0x2
#define BUSPORTGR_GR3_IE                (BUSPORTGR + BUSPORTGR_GR3_POFFSET + BUSPORTGR_GR3_IE_POFFSET)

#define BUSPORTGR_GR3_INTS_POFFSET      0x4
#define BUSPORTGR_GR3_INTS              (BUSPORTGR + BUSPORTGR_GR3_POFFSET + BUSPORTGR_GR3_INTS_POFFSET)

#define BUSPORTGR_GR3_BRP_POFFSET       0x6
#define BUSPORTGR_GR3_BRP               (BUSPORTGR + BUSPORTGR_GR3_POFFSET + BUSPORTGR_GR3_BRP_POFFSET)

#define BUSPORTGR_GR3_BTR_POFFSET       0x8
#define BUSPORTGR_GR3_BTR               (BUSPORTGR + BUSPORTGR_GR3_POFFSET + BUSPORTGR_GR3_BTR_POFFSET)

#define BUSPORTGR_GR3_LIPT_POFFSET      0xa
#define BUSPORTGR_GR3_LIPT              (BUSPORTGR + BUSPORTGR_GR3_POFFSET + BUSPORTGR_GR3_LIPT_POFFSET)

#define BUSPORTGR_GR3_RGPT_POFFSET      0xc
#define BUSPORTGR_GR3_RGPT              (BUSPORTGR + BUSPORTGR_GR3_POFFSET + BUSPORTGR_GR3_RGPT_POFFSET)

#define BUSPORTGR_GR3_LOPT_POFFSET      0xe
#define BUSPORTGR_GR3_LOPT              (BUSPORTGR + BUSPORTGR_GR3_POFFSET + BUSPORTGR_GR3_LOPT_POFFSET)

#define BUSPORTGR_GR3_TGPT_POFFSET      0x10
#define BUSPORTGR_GR3_TGPT              (BUSPORTGR + BUSPORTGR_GR3_POFFSET + BUSPORTGR_GR3_TGPT_POFFSET)

#define BUSPORTGR_GR3_TS_POFFSET        0x12
#define BUSPORTGR_GR3_TS                (BUSPORTGR + BUSPORTGR_GR3_POFFSET + BUSPORTGR_GR3_TS_POFFSET)


#endif

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
#define BPORT1_AB_SC1A_POFFSET          0x0
#define BPORT1_AB_SC1A                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SC1A_POFFSET)
#define BPORT1_AB_SC1A_ADCH             0x1f
#define BPORT1_AB_SC1A_ADCH_GET(_v)     (_v & 0x1f)
#define BPORT1_AB_SC1A_AIEN             (0x1 << 6)
#define BPORT1_AB_SC1A_AIEN_GET(_v)     ((_v >> 6) & 0x1)
#define BPORT1_AB_SC1A_COCO             (0x1 << 7)
#define BPORT1_AB_SC1A_COCO_GET(_v)     ((_v >> 7) & 0x1)
#define BPORT1_AB_SC1A_DIFF             (0x1 << 5)
#define BPORT1_AB_SC1A_DIFF_GET(_v)     ((_v >> 5) & 0x1)

#define BPORT1_AB_SC1B_POFFSET          0x4
#define BPORT1_AB_SC1B                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SC1B_POFFSET)
#define BPORT1_AB_SC1B_ADCH             0x1f
#define BPORT1_AB_SC1B_ADCH_GET(_v)     (_v & 0x1f)
#define BPORT1_AB_SC1B_AIEN             (0x1 << 6)
#define BPORT1_AB_SC1B_AIEN_GET(_v)     ((_v >> 6) & 0x1)
#define BPORT1_AB_SC1B_COCO             (0x1 << 7)
#define BPORT1_AB_SC1B_COCO_GET(_v)     ((_v >> 7) & 0x1)
#define BPORT1_AB_SC1B_DIFF             (0x1 << 5)
#define BPORT1_AB_SC1B_DIFF_GET(_v)     ((_v >> 5) & 0x1)

#define BPORT1_AB_CFG1_POFFSET          0x8
#define BPORT1_AB_CFG1                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CFG1_POFFSET)
#define BPORT1_AB_CFG1_ADICLK           0x3
#define BPORT1_AB_CFG1_ADICLK_GET(_v)   (_v & 0x3)
#define BPORT1_AB_CFG1_ADIV             (0x3 << 5)
#define BPORT1_AB_CFG1_ADIV_GET(_v)     ((_v >> 5) & 0x3)
#define BPORT1_AB_CFG1_ADLPC            (0x1 << 7)
#define BPORT1_AB_CFG1_ADLPC_GET(_v)    ((_v >> 7) & 0x1)
#define BPORT1_AB_CFG1_ADLSMP           (0x1 << 4)
#define BPORT1_AB_CFG1_ADLSMP_GET(_v)   ((_v >> 4) & 0x1)
#define BPORT1_AB_CFG1_MODE             (0x3 << 2)
#define BPORT1_AB_CFG1_MODE_GET(_v)     ((_v >> 2) & 0x3)

#define BPORT1_AB_CFG2_POFFSET          0xc
#define BPORT1_AB_CFG2                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CFG2_POFFSET)
#define BPORT1_AB_CFG2_ADACKEN          (0x1 << 3)
#define BPORT1_AB_CFG2_ADACKEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_CFG2_ADHSC            (0x1 << 2)
#define BPORT1_AB_CFG2_ADHSC_GET(_v)    ((_v >> 2) & 0x1)
#define BPORT1_AB_CFG2_ADLSTS           0x3
#define BPORT1_AB_CFG2_ADLSTS_GET(_v)   (_v & 0x3)
#define BPORT1_AB_CFG2_MUXSEL           (0x1 << 4)
#define BPORT1_AB_CFG2_MUXSEL_GET(_v)   ((_v >> 4) & 0x1)

#define BPORT1_AB_RA_POFFSET            0x10
#define BPORT1_AB_RA                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RA_POFFSET)
#define BPORT1_AB_RA_D                  0xffff
#define BPORT1_AB_RA_D_GET(_v)          (_v & 0xffff)

#define BPORT1_AB_RB_POFFSET            0x14
#define BPORT1_AB_RB                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RB_POFFSET)
#define BPORT1_AB_RB_D                  0xffff
#define BPORT1_AB_RB_D_GET(_v)          (_v & 0xffff)

#define BPORT1_AB_CV1_POFFSET           0x18
#define BPORT1_AB_CV1                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CV1_POFFSET)
#define BPORT1_AB_CV1_CV                0xffff
#define BPORT1_AB_CV1_CV_GET(_v)        (_v & 0xffff)

#define BPORT1_AB_CV2_POFFSET           0x1c
#define BPORT1_AB_CV2                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CV2_POFFSET)
#define BPORT1_AB_CV2_CV                0xffff
#define BPORT1_AB_CV2_CV_GET(_v)        (_v & 0xffff)

#define BPORT1_AB_SC2_POFFSET           0x20
#define BPORT1_AB_SC2                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SC2_POFFSET)
#define BPORT1_AB_SC2_ACFE              (0x1 << 5)
#define BPORT1_AB_SC2_ACFE_GET(_v)      ((_v >> 5) & 0x1)
#define BPORT1_AB_SC2_ACFGT             (0x1 << 4)
#define BPORT1_AB_SC2_ACFGT_GET(_v)     ((_v >> 4) & 0x1)
#define BPORT1_AB_SC2_ACREN             (0x1 << 3)
#define BPORT1_AB_SC2_ACREN_GET(_v)     ((_v >> 3) & 0x1)
#define BPORT1_AB_SC2_ADACT             (0x1 << 7)
#define BPORT1_AB_SC2_ADACT_GET(_v)     ((_v >> 7) & 0x1)
#define BPORT1_AB_SC2_ADTRG             (0x1 << 6)
#define BPORT1_AB_SC2_ADTRG_GET(_v)     ((_v >> 6) & 0x1)
#define BPORT1_AB_SC2_DMAEN             (0x1 << 2)
#define BPORT1_AB_SC2_DMAEN_GET(_v)     ((_v >> 2) & 0x1)
#define BPORT1_AB_SC2_REFSEL            0x3
#define BPORT1_AB_SC2_REFSEL_GET(_v)    (_v & 0x3)

#define BPORT1_AB_SC3_POFFSET           0x24
#define BPORT1_AB_SC3                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SC3_POFFSET)
#define BPORT1_AB_SC3_ADCO              (0x1 << 3)
#define BPORT1_AB_SC3_ADCO_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_SC3_AVGE              (0x1 << 2)
#define BPORT1_AB_SC3_AVGE_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_SC3_AVGS              0x3
#define BPORT1_AB_SC3_AVGS_GET(_v)      (_v & 0x3)
#define BPORT1_AB_SC3_CAL               (0x1 << 7)
#define BPORT1_AB_SC3_CAL_GET(_v)       ((_v >> 7) & 0x1)
#define BPORT1_AB_SC3_CALF              (0x1 << 6)
#define BPORT1_AB_SC3_CALF_GET(_v)      ((_v >> 6) & 0x1)

#define BPORT1_AB_OFS_POFFSET           0x28
#define BPORT1_AB_OFS                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_OFS_POFFSET)
#define BPORT1_AB_OFS_OFS               0xffff
#define BPORT1_AB_OFS_OFS_GET(_v)       (_v & 0xffff)

#define BPORT1_AB_PG_POFFSET            0x2c
#define BPORT1_AB_PG                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PG_POFFSET)
#define BPORT1_AB_PG_PG                 0xffff
#define BPORT1_AB_PG_PG_GET(_v)         (_v & 0xffff)

#define BPORT1_AB_MG_POFFSET            0x30
#define BPORT1_AB_MG                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MG_POFFSET)
#define BPORT1_AB_MG_MG                 0xffff
#define BPORT1_AB_MG_MG_GET(_v)         (_v & 0xffff)

#define BPORT1_AB_CLPD_POFFSET          0x34
#define BPORT1_AB_CLPD                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CLPD_POFFSET)
#define BPORT1_AB_CLPD_CLPD             0x3f
#define BPORT1_AB_CLPD_CLPD_GET(_v)     (_v & 0x3f)

#define BPORT1_AB_CLPS_POFFSET          0x38
#define BPORT1_AB_CLPS                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CLPS_POFFSET)
#define BPORT1_AB_CLPS_CLPS             0x3f
#define BPORT1_AB_CLPS_CLPS_GET(_v)     (_v & 0x3f)

#define BPORT1_AB_CLP4_POFFSET          0x3c
#define BPORT1_AB_CLP4                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CLP4_POFFSET)
#define BPORT1_AB_CLP4_CLP4             0x3ff
#define BPORT1_AB_CLP4_CLP4_GET(_v)     (_v & 0x3ff)

#define BPORT1_AB_CLP3_POFFSET          0x40
#define BPORT1_AB_CLP3                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CLP3_POFFSET)
#define BPORT1_AB_CLP3_CLP3             0x1ff
#define BPORT1_AB_CLP3_CLP3_GET(_v)     (_v & 0x1ff)

#define BPORT1_AB_CLP2_POFFSET          0x44
#define BPORT1_AB_CLP2                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CLP2_POFFSET)
#define BPORT1_AB_CLP2_CLP2             0xff
#define BPORT1_AB_CLP2_CLP2_GET(_v)     (_v & 0xff)

#define BPORT1_AB_CLP1_POFFSET          0x48
#define BPORT1_AB_CLP1                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CLP1_POFFSET)
#define BPORT1_AB_CLP1_CLP1             0x7f
#define BPORT1_AB_CLP1_CLP1_GET(_v)     (_v & 0x7f)

#define BPORT1_AB_CLP0_POFFSET          0x4c
#define BPORT1_AB_CLP0                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CLP0_POFFSET)
#define BPORT1_AB_CLP0_CLP0             0x3f
#define BPORT1_AB_CLP0_CLP0_GET(_v)     (_v & 0x3f)

#define BPORT1_AB_PGA_POFFSET           0x50
#define BPORT1_AB_PGA                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PGA_POFFSET)
#define BPORT1_AB_PGA_PGACHPB           (0x1 << 21)
#define BPORT1_AB_PGA_PGACHPB_GET(_v)   ((_v >> 21) & 0x1)
#define BPORT1_AB_PGA_PGAEN             (0x1 << 23)
#define BPORT1_AB_PGA_PGAEN_GET(_v)     ((_v >> 23) & 0x1)
#define BPORT1_AB_PGA_PGAG              (0xf << 16)
#define BPORT1_AB_PGA_PGAG_GET(_v)      ((_v >> 16) & 0xf)
#define BPORT1_AB_PGA_PGALPB            (0x1 << 20)
#define BPORT1_AB_PGA_PGALPB_GET(_v)    ((_v >> 20) & 0x1)
#define BPORT1_AB_PGA_PGAOFSM           (0x1 << 14)
#define BPORT1_AB_PGA_PGAOFSM_GET(_v)   ((_v >> 14) & 0x1)

#define BPORT1_AB_CLMD_POFFSET          0x54
#define BPORT1_AB_CLMD                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CLMD_POFFSET)
#define BPORT1_AB_CLMD_CLMD             0x3f
#define BPORT1_AB_CLMD_CLMD_GET(_v)     (_v & 0x3f)

#define BPORT1_AB_CLMS_POFFSET          0x58
#define BPORT1_AB_CLMS                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CLMS_POFFSET)
#define BPORT1_AB_CLMS_CLMS             0x3f
#define BPORT1_AB_CLMS_CLMS_GET(_v)     (_v & 0x3f)

#define BPORT1_AB_CLM4_POFFSET          0x5c
#define BPORT1_AB_CLM4                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CLM4_POFFSET)
#define BPORT1_AB_CLM4_CLM4             0x3ff
#define BPORT1_AB_CLM4_CLM4_GET(_v)     (_v & 0x3ff)

#define BPORT1_AB_CLM3_POFFSET          0x60
#define BPORT1_AB_CLM3                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CLM3_POFFSET)
#define BPORT1_AB_CLM3_CLM3             0x1ff
#define BPORT1_AB_CLM3_CLM3_GET(_v)     (_v & 0x1ff)

#define BPORT1_AB_CLM2_POFFSET          0x64
#define BPORT1_AB_CLM2                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CLM2_POFFSET)
#define BPORT1_AB_CLM2_CLM2             0xff
#define BPORT1_AB_CLM2_CLM2_GET(_v)     (_v & 0xff)

#define BPORT1_AB_CLM1_POFFSET          0x68
#define BPORT1_AB_CLM1                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CLM1_POFFSET)
#define BPORT1_AB_CLM1_CLM1             0x7f
#define BPORT1_AB_CLM1_CLM1_GET(_v)     (_v & 0x7f)

#define BPORT1_AB_CLM0_POFFSET          0x6c
#define BPORT1_AB_CLM0                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CLM0_POFFSET)
#define BPORT1_AB_CLM0_CLM0             0x3f
#define BPORT1_AB_CLM0_CLM0_GET(_v)     (_v & 0x3f)


#endif

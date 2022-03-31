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
#define BPORT1_AB_A1_POFFSET            0x0
#define BPORT1_AB_A1                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_A1_POFFSET)
#define BPORT1_AB_A1_AD                 (0x7f << 1)
#define BPORT1_AB_A1_AD_GET(_v)         ((_v >> 1) & 0x7f)

#define BPORT1_AB_F_POFFSET             0x1
#define BPORT1_AB_F                     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_F_POFFSET)
#define BPORT1_AB_F_ICR                 0x3f
#define BPORT1_AB_F_ICR_GET(_v)         (_v & 0x3f)
#define BPORT1_AB_F_MULT                (0x3 << 6)
#define BPORT1_AB_F_MULT_GET(_v)        ((_v >> 6) & 0x3)

#define BPORT1_AB_C1_POFFSET            0x2
#define BPORT1_AB_C1                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C1_POFFSET)
#define BPORT1_AB_C1_DMAEN              0x1
#define BPORT1_AB_C1_DMAEN_GET(_v)      (_v & 0x1)
#define BPORT1_AB_C1_IICEN              (0x1 << 7)
#define BPORT1_AB_C1_IICEN_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_C1_IICIE              (0x1 << 6)
#define BPORT1_AB_C1_IICIE_GET(_v)      ((_v >> 6) & 0x1)
#define BPORT1_AB_C1_MST                (0x1 << 5)
#define BPORT1_AB_C1_MST_GET(_v)        ((_v >> 5) & 0x1)
#define BPORT1_AB_C1_RSTA               (0x1 << 2)
#define BPORT1_AB_C1_RSTA_GET(_v)       ((_v >> 2) & 0x1)
#define BPORT1_AB_C1_TX                 (0x1 << 4)
#define BPORT1_AB_C1_TX_GET(_v)         ((_v >> 4) & 0x1)
#define BPORT1_AB_C1_TXAK               (0x1 << 3)
#define BPORT1_AB_C1_TXAK_GET(_v)       ((_v >> 3) & 0x1)
#define BPORT1_AB_C1_WUEN               (0x1 << 1)
#define BPORT1_AB_C1_WUEN_GET(_v)       ((_v >> 1) & 0x1)

#define BPORT1_AB_S_POFFSET             0x3
#define BPORT1_AB_S                     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_S_POFFSET)
#define BPORT1_AB_S_ARBL                (0x1 << 4)
#define BPORT1_AB_S_ARBL_GET(_v)        ((_v >> 4) & 0x1)
#define BPORT1_AB_S_BUSY                (0x1 << 5)
#define BPORT1_AB_S_BUSY_GET(_v)        ((_v >> 5) & 0x1)
#define BPORT1_AB_S_IAAS                (0x1 << 6)
#define BPORT1_AB_S_IAAS_GET(_v)        ((_v >> 6) & 0x1)
#define BPORT1_AB_S_IICIF               (0x1 << 1)
#define BPORT1_AB_S_IICIF_GET(_v)       ((_v >> 1) & 0x1)
#define BPORT1_AB_S_RAM                 (0x1 << 3)
#define BPORT1_AB_S_RAM_GET(_v)         ((_v >> 3) & 0x1)
#define BPORT1_AB_S_RXAK                0x1
#define BPORT1_AB_S_RXAK_GET(_v)        (_v & 0x1)
#define BPORT1_AB_S_SRW                 (0x1 << 2)
#define BPORT1_AB_S_SRW_GET(_v)         ((_v >> 2) & 0x1)
#define BPORT1_AB_S_TCF                 (0x1 << 7)
#define BPORT1_AB_S_TCF_GET(_v)         ((_v >> 7) & 0x1)

#define BPORT1_AB_D_POFFSET             0x4
#define BPORT1_AB_D                     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_D_POFFSET)
#define BPORT1_AB_D_DATA                0xff
#define BPORT1_AB_D_DATA_GET(_v)        (_v & 0xff)

#define BPORT1_AB_C2_POFFSET            0x5
#define BPORT1_AB_C2                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C2_POFFSET)
#define BPORT1_AB_C2_AD                 0x7
#define BPORT1_AB_C2_AD_GET(_v)         (_v & 0x7)
#define BPORT1_AB_C2_ADEXT              (0x1 << 6)
#define BPORT1_AB_C2_ADEXT_GET(_v)      ((_v >> 6) & 0x1)
#define BPORT1_AB_C2_GCAEN              (0x1 << 7)
#define BPORT1_AB_C2_GCAEN_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_C2_HDRS               (0x1 << 5)
#define BPORT1_AB_C2_HDRS_GET(_v)       ((_v >> 5) & 0x1)
#define BPORT1_AB_C2_RMEN               (0x1 << 3)
#define BPORT1_AB_C2_RMEN_GET(_v)       ((_v >> 3) & 0x1)
#define BPORT1_AB_C2_SBRC               (0x1 << 4)
#define BPORT1_AB_C2_SBRC_GET(_v)       ((_v >> 4) & 0x1)

#define BPORT1_AB_FLT_POFFSET           0x6
#define BPORT1_AB_FLT                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FLT_POFFSET)
#define BPORT1_AB_FLT_FLT               0x1f
#define BPORT1_AB_FLT_FLT_GET(_v)       (_v & 0x1f)

#define BPORT1_AB_RA_POFFSET            0x7
#define BPORT1_AB_RA                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RA_POFFSET)
#define BPORT1_AB_RA_RAD                (0x7f << 1)
#define BPORT1_AB_RA_RAD_GET(_v)        ((_v >> 1) & 0x7f)

#define BPORT1_AB_SMB_POFFSET           0x8
#define BPORT1_AB_SMB                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SMB_POFFSET)
#define BPORT1_AB_SMB_ALERTEN           (0x1 << 6)
#define BPORT1_AB_SMB_ALERTEN_GET(_v)   ((_v >> 6) & 0x1)
#define BPORT1_AB_SMB_FACK              (0x1 << 7)
#define BPORT1_AB_SMB_FACK_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_SMB_SHTF1             (0x1 << 2)
#define BPORT1_AB_SMB_SHTF1_GET(_v)     ((_v >> 2) & 0x1)
#define BPORT1_AB_SMB_SHTF2             (0x1 << 1)
#define BPORT1_AB_SMB_SHTF2_GET(_v)     ((_v >> 1) & 0x1)
#define BPORT1_AB_SMB_SHTF2IE           0x1
#define BPORT1_AB_SMB_SHTF2IE_GET(_v)   (_v & 0x1)
#define BPORT1_AB_SMB_SIICAEN           (0x1 << 5)
#define BPORT1_AB_SMB_SIICAEN_GET(_v)   ((_v >> 5) & 0x1)
#define BPORT1_AB_SMB_SLTF              (0x1 << 3)
#define BPORT1_AB_SMB_SLTF_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_SMB_TCKSEL            (0x1 << 4)
#define BPORT1_AB_SMB_TCKSEL_GET(_v)    ((_v >> 4) & 0x1)

#define BPORT1_AB_A2_POFFSET            0x9
#define BPORT1_AB_A2                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_A2_POFFSET)
#define BPORT1_AB_A2_SAD                (0x7f << 1)
#define BPORT1_AB_A2_SAD_GET(_v)        ((_v >> 1) & 0x7f)

#define BPORT1_AB_SLTH_POFFSET          0xa
#define BPORT1_AB_SLTH                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SLTH_POFFSET)
#define BPORT1_AB_SLTH_SSLT             0xff
#define BPORT1_AB_SLTH_SSLT_GET(_v)     (_v & 0xff)

#define BPORT1_AB_SLTL_POFFSET          0xb
#define BPORT1_AB_SLTL                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SLTL_POFFSET)
#define BPORT1_AB_SLTL_SSLT             0xff
#define BPORT1_AB_SLTL_SSLT_GET(_v)     (_v & 0xff)


#endif

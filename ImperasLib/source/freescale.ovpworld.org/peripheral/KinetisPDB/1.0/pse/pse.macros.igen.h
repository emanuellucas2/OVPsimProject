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
#define BPORT1_AB_SC_POFFSET            0x0
#define BPORT1_AB_SC                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SC_POFFSET)
#define BPORT1_AB_SC_CONT               (0x1 << 1)
#define BPORT1_AB_SC_CONT_GET(_v)       ((_v >> 1) & 0x1)
#define BPORT1_AB_SC_DMAEN              (0x1 << 15)
#define BPORT1_AB_SC_DMAEN_GET(_v)      ((_v >> 15) & 0x1)
#define BPORT1_AB_SC_LDMOD              (0x3 << 18)
#define BPORT1_AB_SC_LDMOD_GET(_v)      ((_v >> 18) & 0x3)
#define BPORT1_AB_SC_LDOK               0x1
#define BPORT1_AB_SC_LDOK_GET(_v)       (_v & 0x1)
#define BPORT1_AB_SC_MULT               (0x3 << 2)
#define BPORT1_AB_SC_MULT_GET(_v)       ((_v >> 2) & 0x3)
#define BPORT1_AB_SC_PDBEIE             (0x1 << 17)
#define BPORT1_AB_SC_PDBEIE_GET(_v)     ((_v >> 17) & 0x1)
#define BPORT1_AB_SC_PDBEN              (0x1 << 7)
#define BPORT1_AB_SC_PDBEN_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_SC_PDBIE              (0x1 << 5)
#define BPORT1_AB_SC_PDBIE_GET(_v)      ((_v >> 5) & 0x1)
#define BPORT1_AB_SC_PDBIF              (0x1 << 6)
#define BPORT1_AB_SC_PDBIF_GET(_v)      ((_v >> 6) & 0x1)
#define BPORT1_AB_SC_PRESCALER          (0x7 << 12)
#define BPORT1_AB_SC_PRESCALER_GET(_v)  ((_v >> 12) & 0x7)
#define BPORT1_AB_SC_SWTRIG             (0x1 << 16)
#define BPORT1_AB_SC_SWTRIG_GET(_v)     ((_v >> 16) & 0x1)
#define BPORT1_AB_SC_TRGSEL             (0xf << 8)
#define BPORT1_AB_SC_TRGSEL_GET(_v)     ((_v >> 8) & 0xf)

#define BPORT1_AB_MOD_POFFSET           0x4
#define BPORT1_AB_MOD                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MOD_POFFSET)
#define BPORT1_AB_MOD_MOD               0xffff
#define BPORT1_AB_MOD_MOD_GET(_v)       (_v & 0xffff)

#define BPORT1_AB_CNT_POFFSET           0x8
#define BPORT1_AB_CNT                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CNT_POFFSET)
#define BPORT1_AB_CNT_CNT               0xffff
#define BPORT1_AB_CNT_CNT_GET(_v)       (_v & 0xffff)

#define BPORT1_AB_IDLY_POFFSET          0xc
#define BPORT1_AB_IDLY                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IDLY_POFFSET)
#define BPORT1_AB_IDLY_IDLY             0xffff
#define BPORT1_AB_IDLY_IDLY_GET(_v)     (_v & 0xffff)

#define BPORT1_AB_CH0C1_POFFSET         0x10
#define BPORT1_AB_CH0C1                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CH0C1_POFFSET)
#define BPORT1_AB_CH0C1_BB              (0xff << 16)
#define BPORT1_AB_CH0C1_BB_GET(_v)      ((_v >> 16) & 0xff)
#define BPORT1_AB_CH0C1_EN              0xff
#define BPORT1_AB_CH0C1_EN_GET(_v)      (_v & 0xff)
#define BPORT1_AB_CH0C1_TOS             (0xff << 8)
#define BPORT1_AB_CH0C1_TOS_GET(_v)     ((_v >> 8) & 0xff)

#define BPORT1_AB_CH0S_POFFSET          0x14
#define BPORT1_AB_CH0S                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CH0S_POFFSET)
#define BPORT1_AB_CH0S_CF               (0xff << 16)
#define BPORT1_AB_CH0S_CF_GET(_v)       ((_v >> 16) & 0xff)
#define BPORT1_AB_CH0S_ERR              0xff
#define BPORT1_AB_CH0S_ERR_GET(_v)      (_v & 0xff)

#define BPORT1_AB_CH0DLY0_POFFSET       0x18
#define BPORT1_AB_CH0DLY0               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CH0DLY0_POFFSET)
#define BPORT1_AB_CH0DLY0_DLY           0xffff
#define BPORT1_AB_CH0DLY0_DLY_GET(_v)   (_v & 0xffff)

#define BPORT1_AB_CH0DLY1_POFFSET       0x1c
#define BPORT1_AB_CH0DLY1               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CH0DLY1_POFFSET)
#define BPORT1_AB_CH0DLY1_DLY           0xffff
#define BPORT1_AB_CH0DLY1_DLY_GET(_v)   (_v & 0xffff)

#define BPORT1_AB_CH1C1_POFFSET         0x38
#define BPORT1_AB_CH1C1                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CH1C1_POFFSET)
#define BPORT1_AB_CH1C1_BB              (0xff << 16)
#define BPORT1_AB_CH1C1_BB_GET(_v)      ((_v >> 16) & 0xff)
#define BPORT1_AB_CH1C1_EN              0xff
#define BPORT1_AB_CH1C1_EN_GET(_v)      (_v & 0xff)
#define BPORT1_AB_CH1C1_TOS             (0xff << 8)
#define BPORT1_AB_CH1C1_TOS_GET(_v)     ((_v >> 8) & 0xff)

#define BPORT1_AB_CH1S_POFFSET          0x3c
#define BPORT1_AB_CH1S                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CH1S_POFFSET)
#define BPORT1_AB_CH1S_CF               (0xff << 16)
#define BPORT1_AB_CH1S_CF_GET(_v)       ((_v >> 16) & 0xff)
#define BPORT1_AB_CH1S_ERR              0xff
#define BPORT1_AB_CH1S_ERR_GET(_v)      (_v & 0xff)

#define BPORT1_AB_CH1DLY0_POFFSET       0x40
#define BPORT1_AB_CH1DLY0               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CH1DLY0_POFFSET)
#define BPORT1_AB_CH1DLY0_DLY           0xffff
#define BPORT1_AB_CH1DLY0_DLY_GET(_v)   (_v & 0xffff)

#define BPORT1_AB_CH1DLY1_POFFSET       0x44
#define BPORT1_AB_CH1DLY1               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CH1DLY1_POFFSET)
#define BPORT1_AB_CH1DLY1_DLY           0xffff
#define BPORT1_AB_CH1DLY1_DLY_GET(_v)   (_v & 0xffff)

#define BPORT1_AB_CH2C1_POFFSET         0x60
#define BPORT1_AB_CH2C1                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CH2C1_POFFSET)
#define BPORT1_AB_CH2C1_BB              (0xff << 16)
#define BPORT1_AB_CH2C1_BB_GET(_v)      ((_v >> 16) & 0xff)
#define BPORT1_AB_CH2C1_EN              0xff
#define BPORT1_AB_CH2C1_EN_GET(_v)      (_v & 0xff)
#define BPORT1_AB_CH2C1_TOS             (0xff << 8)
#define BPORT1_AB_CH2C1_TOS_GET(_v)     ((_v >> 8) & 0xff)

#define BPORT1_AB_CH2S_POFFSET          0x64
#define BPORT1_AB_CH2S                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CH2S_POFFSET)
#define BPORT1_AB_CH2S_CF               (0xff << 16)
#define BPORT1_AB_CH2S_CF_GET(_v)       ((_v >> 16) & 0xff)
#define BPORT1_AB_CH2S_ERR              0xff
#define BPORT1_AB_CH2S_ERR_GET(_v)      (_v & 0xff)

#define BPORT1_AB_CH2DLY0_POFFSET       0x68
#define BPORT1_AB_CH2DLY0               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CH2DLY0_POFFSET)
#define BPORT1_AB_CH2DLY0_DLY           0xffff
#define BPORT1_AB_CH2DLY0_DLY_GET(_v)   (_v & 0xffff)

#define BPORT1_AB_CH2DLY1_POFFSET       0x6c
#define BPORT1_AB_CH2DLY1               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CH2DLY1_POFFSET)
#define BPORT1_AB_CH2DLY1_DLY           0xffff
#define BPORT1_AB_CH2DLY1_DLY_GET(_v)   (_v & 0xffff)

#define BPORT1_AB_CH3C1_POFFSET         0x88
#define BPORT1_AB_CH3C1                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CH3C1_POFFSET)
#define BPORT1_AB_CH3C1_BB              (0xff << 16)
#define BPORT1_AB_CH3C1_BB_GET(_v)      ((_v >> 16) & 0xff)
#define BPORT1_AB_CH3C1_EN              0xff
#define BPORT1_AB_CH3C1_EN_GET(_v)      (_v & 0xff)
#define BPORT1_AB_CH3C1_TOS             (0xff << 8)
#define BPORT1_AB_CH3C1_TOS_GET(_v)     ((_v >> 8) & 0xff)

#define BPORT1_AB_CH3S_POFFSET          0x8c
#define BPORT1_AB_CH3S                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CH3S_POFFSET)
#define BPORT1_AB_CH3S_CF               (0xff << 16)
#define BPORT1_AB_CH3S_CF_GET(_v)       ((_v >> 16) & 0xff)
#define BPORT1_AB_CH3S_ERR              0xff
#define BPORT1_AB_CH3S_ERR_GET(_v)      (_v & 0xff)

#define BPORT1_AB_CH3DLY0_POFFSET       0x90
#define BPORT1_AB_CH3DLY0               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CH3DLY0_POFFSET)
#define BPORT1_AB_CH3DLY0_DLY           0xffff
#define BPORT1_AB_CH3DLY0_DLY_GET(_v)   (_v & 0xffff)

#define BPORT1_AB_CH3DLY1_POFFSET       0x94
#define BPORT1_AB_CH3DLY1               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CH3DLY1_POFFSET)
#define BPORT1_AB_CH3DLY1_DLY           0xffff
#define BPORT1_AB_CH3DLY1_DLY_GET(_v)   (_v & 0xffff)

#define BPORT1_AB_DACINTC0_POFFSET      0x150
#define BPORT1_AB_DACINTC0              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DACINTC0_POFFSET)
#define BPORT1_AB_DACINTC0_EXT          (0x1 << 1)
#define BPORT1_AB_DACINTC0_EXT_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_DACINTC0_TOE          0x1
#define BPORT1_AB_DACINTC0_TOE_GET(_v)  (_v & 0x1)

#define BPORT1_AB_DACINT0_POFFSET       0x154
#define BPORT1_AB_DACINT0               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DACINT0_POFFSET)
#define BPORT1_AB_DACINT0_INT           0xffff
#define BPORT1_AB_DACINT0_INT_GET(_v)   (_v & 0xffff)

#define BPORT1_AB_DACINTC1_POFFSET      0x158
#define BPORT1_AB_DACINTC1              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DACINTC1_POFFSET)
#define BPORT1_AB_DACINTC1_EXT          (0x1 << 1)
#define BPORT1_AB_DACINTC1_EXT_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_DACINTC1_TOE          0x1
#define BPORT1_AB_DACINTC1_TOE_GET(_v)  (_v & 0x1)

#define BPORT1_AB_DACINT1_POFFSET       0x15c
#define BPORT1_AB_DACINT1               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DACINT1_POFFSET)
#define BPORT1_AB_DACINT1_INT           0xffff
#define BPORT1_AB_DACINT1_INT_GET(_v)   (_v & 0xffff)

#define BPORT1_AB_POEN_POFFSET          0x190
#define BPORT1_AB_POEN                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_POEN_POFFSET)
#define BPORT1_AB_POEN_POEN             0xff
#define BPORT1_AB_POEN_POEN_GET(_v)     (_v & 0xff)

#define BPORT1_AB_PO0DLY_POFFSET        0x194
#define BPORT1_AB_PO0DLY                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PO0DLY_POFFSET)
#define BPORT1_AB_PO0DLY_DLY1           (0xffff << 16)
#define BPORT1_AB_PO0DLY_DLY1_GET(_v)   ((_v >> 16) & 0xffff)
#define BPORT1_AB_PO0DLY_DLY2           0xffff
#define BPORT1_AB_PO0DLY_DLY2_GET(_v)   (_v & 0xffff)

#define BPORT1_AB_PO1DLY_POFFSET        0x198
#define BPORT1_AB_PO1DLY                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PO1DLY_POFFSET)
#define BPORT1_AB_PO1DLY_DLY1           (0xffff << 16)
#define BPORT1_AB_PO1DLY_DLY1_GET(_v)   ((_v >> 16) & 0xffff)
#define BPORT1_AB_PO1DLY_DLY2           0xffff
#define BPORT1_AB_PO1DLY_DLY2_GET(_v)   (_v & 0xffff)

#define BPORT1_AB_PO2DLY_POFFSET        0x19c
#define BPORT1_AB_PO2DLY                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PO2DLY_POFFSET)
#define BPORT1_AB_PO2DLY_DLY1           (0xffff << 16)
#define BPORT1_AB_PO2DLY_DLY1_GET(_v)   ((_v >> 16) & 0xffff)
#define BPORT1_AB_PO2DLY_DLY2           0xffff
#define BPORT1_AB_PO2DLY_DLY2_GET(_v)   (_v & 0xffff)

#define BPORT1_AB_PO3DLY_POFFSET        0x1a0
#define BPORT1_AB_PO3DLY                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PO3DLY_POFFSET)
#define BPORT1_AB_PO3DLY_DLY1           (0xffff << 16)
#define BPORT1_AB_PO3DLY_DLY1_GET(_v)   ((_v >> 16) & 0xffff)
#define BPORT1_AB_PO3DLY_DLY2           0xffff
#define BPORT1_AB_PO3DLY_DLY2_GET(_v)   (_v & 0xffff)


#endif

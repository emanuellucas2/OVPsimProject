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
#define BPORT1_AB_LCDCR_POFFSET         0x0
#define BPORT1_AB_LCDCR                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LCDCR_POFFSET)
#define BPORT1_AB_LCDCR_BIAS            (0x1 << 25)
#define BPORT1_AB_LCDCR_BIAS_GET(_v)    ((_v >> 25) & 0x1)
#define BPORT1_AB_LCDCR_BSTAO           (0x1 << 19)
#define BPORT1_AB_LCDCR_BSTAO_GET(_v)   ((_v >> 19) & 0x1)
#define BPORT1_AB_LCDCR_BSTEN           (0x1 << 21)
#define BPORT1_AB_LCDCR_BSTEN_GET(_v)   ((_v >> 21) & 0x1)
#define BPORT1_AB_LCDCR_BSTSEL          (0x1 << 20)
#define BPORT1_AB_LCDCR_BSTSEL_GET(_v)  ((_v >> 20) & 0x1)
#define BPORT1_AB_LCDCR_DUTY            (0x7 << 26)
#define BPORT1_AB_LCDCR_DUTY_GET(_v)    ((_v >> 26) & 0x7)
#define BPORT1_AB_LCDCR_EOF             (0x1 << 16)
#define BPORT1_AB_LCDCR_EOF_GET(_v)     ((_v >> 16) & 0x1)
#define BPORT1_AB_LCDCR_LCDBPA          (0x3 << 4)
#define BPORT1_AB_LCDCR_LCDBPA_GET(_v)  ((_v >> 4) & 0x3)
#define BPORT1_AB_LCDCR_LCDBPS          0x7
#define BPORT1_AB_LCDCR_LCDBPS_GET(_v)  (_v & 0x7)
#define BPORT1_AB_LCDCR_LCDEN           (0x1 << 31)
#define BPORT1_AB_LCDCR_LCDEN_GET(_v)   ((_v >> 31) & 0x1)
#define BPORT1_AB_LCDCR_LCDINT          (0x1 << 17)
#define BPORT1_AB_LCDCR_LCDINT_GET(_v)  ((_v >> 17) & 0x1)
#define BPORT1_AB_LCDCR_LCDOCS          (0x1 << 18)
#define BPORT1_AB_LCDCR_LCDOCS_GET(_v)  ((_v >> 18) & 0x1)
#define BPORT1_AB_LCDCR_LCDRCS          (0x1 << 29)
#define BPORT1_AB_LCDCR_LCDRCS_GET(_v)  ((_v >> 29) & 0x1)
#define BPORT1_AB_LCDCR_LCDRST          (0x1 << 30)
#define BPORT1_AB_LCDCR_LCDRST_GET(_v)  ((_v >> 30) & 0x1)
#define BPORT1_AB_LCDCR_NOF             (0xff << 8)
#define BPORT1_AB_LCDCR_NOF_GET(_v)     ((_v >> 8) & 0xff)
#define BPORT1_AB_LCDCR_PWR             (0x3 << 22)
#define BPORT1_AB_LCDCR_PWR_GET(_v)     ((_v >> 22) & 0x3)
#define BPORT1_AB_LCDCR_VLCDS           (0x1 << 24)
#define BPORT1_AB_LCDCR_VLCDS_GET(_v)   ((_v >> 24) & 0x1)

#define BPORT1_AB_LCDPCR_POFFSET        0x4
#define BPORT1_AB_LCDPCR                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LCDPCR_POFFSET)
#define BPORT1_AB_LCDPCR_LCLK           (0xf << 24)
#define BPORT1_AB_LCDPCR_LCLK_GET(_v)   ((_v >> 24) & 0xf)

#define BPORT1_AB_LCDCCR_POFFSET        0x8
#define BPORT1_AB_LCDCCR                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LCDCCR_POFFSET)
#define BPORT1_AB_LCDCCR_CCEN           (0x1 << 31)
#define BPORT1_AB_LCDCCR_CCEN_GET(_v)   ((_v >> 31) & 0x1)
#define BPORT1_AB_LCDCCR_LCC            (0x7ff << 16)
#define BPORT1_AB_LCDCCR_LCC_GET(_v)    ((_v >> 16) & 0x7ff)

#define BPORT1_AB_ENFPR0_POFFSET        0x10
#define BPORT1_AB_ENFPR0                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENFPR0_POFFSET)
#define BPORT1_AB_ENFPR0_ENFP           0xffffffff
#define BPORT1_AB_ENFPR0_ENFP_GET(_v)   (_v & 0xffffffff)

#define BPORT1_AB_ENFPR1_POFFSET        0x14
#define BPORT1_AB_ENFPR1                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ENFPR1_POFFSET)
#define BPORT1_AB_ENFPR1_ENFP           0xffffffff
#define BPORT1_AB_ENFPR1_ENFP_GET(_v)   (_v & 0xffffffff)

#define BPORT1_AB_LCDRAM0_POFFSET       0x20
#define BPORT1_AB_LCDRAM0               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LCDRAM0_POFFSET)
#define BPORT1_AB_LCDRAM0_FP0_BP        (0xff << 24)
#define BPORT1_AB_LCDRAM0_FP0_BP_GET(_v)  ((_v >> 24) & 0xff)
#define BPORT1_AB_LCDRAM0_FP1_BP        (0xff << 16)
#define BPORT1_AB_LCDRAM0_FP1_BP_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_AB_LCDRAM0_FP2_BP        (0xff << 8)
#define BPORT1_AB_LCDRAM0_FP2_BP_GET(_v)  ((_v >> 8) & 0xff)
#define BPORT1_AB_LCDRAM0_FP3_BP        0xff
#define BPORT1_AB_LCDRAM0_FP3_BP_GET(_v)  (_v & 0xff)

#define BPORT1_AB_LCDRAM1_POFFSET       0x24
#define BPORT1_AB_LCDRAM1               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LCDRAM1_POFFSET)
#define BPORT1_AB_LCDRAM1_FP4_BP        (0xff << 24)
#define BPORT1_AB_LCDRAM1_FP4_BP_GET(_v)  ((_v >> 24) & 0xff)
#define BPORT1_AB_LCDRAM1_FP5_BP        (0xff << 16)
#define BPORT1_AB_LCDRAM1_FP5_BP_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_AB_LCDRAM1_FP6_BP        (0xff << 8)
#define BPORT1_AB_LCDRAM1_FP6_BP_GET(_v)  ((_v >> 8) & 0xff)
#define BPORT1_AB_LCDRAM1_FP7_BP        0xff
#define BPORT1_AB_LCDRAM1_FP7_BP_GET(_v)  (_v & 0xff)

#define BPORT1_AB_LCDRAM2_POFFSET       0x28
#define BPORT1_AB_LCDRAM2               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LCDRAM2_POFFSET)
#define BPORT1_AB_LCDRAM2_FP10_BP       (0xff << 8)
#define BPORT1_AB_LCDRAM2_FP10_BP_GET(_v)  ((_v >> 8) & 0xff)
#define BPORT1_AB_LCDRAM2_FP11_BP       0xff
#define BPORT1_AB_LCDRAM2_FP11_BP_GET(_v)  (_v & 0xff)
#define BPORT1_AB_LCDRAM2_FP8_BP        (0xff << 24)
#define BPORT1_AB_LCDRAM2_FP8_BP_GET(_v)  ((_v >> 24) & 0xff)
#define BPORT1_AB_LCDRAM2_FP9_BP        (0xff << 16)
#define BPORT1_AB_LCDRAM2_FP9_BP_GET(_v)  ((_v >> 16) & 0xff)

#define BPORT1_AB_LCDRAM3_POFFSET       0x2c
#define BPORT1_AB_LCDRAM3               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LCDRAM3_POFFSET)
#define BPORT1_AB_LCDRAM3_FP12_BP       (0xff << 24)
#define BPORT1_AB_LCDRAM3_FP12_BP_GET(_v)  ((_v >> 24) & 0xff)
#define BPORT1_AB_LCDRAM3_FP13_BP       (0xff << 16)
#define BPORT1_AB_LCDRAM3_FP13_BP_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_AB_LCDRAM3_FP14_BP       (0xff << 8)
#define BPORT1_AB_LCDRAM3_FP14_BP_GET(_v)  ((_v >> 8) & 0xff)
#define BPORT1_AB_LCDRAM3_FP15_BP       0xff
#define BPORT1_AB_LCDRAM3_FP15_BP_GET(_v)  (_v & 0xff)

#define BPORT1_AB_LCDRAM4_POFFSET       0x30
#define BPORT1_AB_LCDRAM4               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LCDRAM4_POFFSET)
#define BPORT1_AB_LCDRAM4_FP16_BP       (0xff << 24)
#define BPORT1_AB_LCDRAM4_FP16_BP_GET(_v)  ((_v >> 24) & 0xff)
#define BPORT1_AB_LCDRAM4_FP17_BP       (0xff << 16)
#define BPORT1_AB_LCDRAM4_FP17_BP_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_AB_LCDRAM4_FP18_BP       (0xff << 8)
#define BPORT1_AB_LCDRAM4_FP18_BP_GET(_v)  ((_v >> 8) & 0xff)
#define BPORT1_AB_LCDRAM4_FP19_BP       0xff
#define BPORT1_AB_LCDRAM4_FP19_BP_GET(_v)  (_v & 0xff)

#define BPORT1_AB_LCDRAM5_POFFSET       0x34
#define BPORT1_AB_LCDRAM5               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LCDRAM5_POFFSET)
#define BPORT1_AB_LCDRAM5_FP20_BP       (0xff << 24)
#define BPORT1_AB_LCDRAM5_FP20_BP_GET(_v)  ((_v >> 24) & 0xff)
#define BPORT1_AB_LCDRAM5_FP21_BP       (0xff << 16)
#define BPORT1_AB_LCDRAM5_FP21_BP_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_AB_LCDRAM5_FP22_BP       (0xff << 8)
#define BPORT1_AB_LCDRAM5_FP22_BP_GET(_v)  ((_v >> 8) & 0xff)
#define BPORT1_AB_LCDRAM5_FP23_BP       0xff
#define BPORT1_AB_LCDRAM5_FP23_BP_GET(_v)  (_v & 0xff)

#define BPORT1_AB_LCDRAM6_POFFSET       0x38
#define BPORT1_AB_LCDRAM6               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LCDRAM6_POFFSET)
#define BPORT1_AB_LCDRAM6_FP24_BP       (0xff << 24)
#define BPORT1_AB_LCDRAM6_FP24_BP_GET(_v)  ((_v >> 24) & 0xff)
#define BPORT1_AB_LCDRAM6_FP25_BP       (0xff << 16)
#define BPORT1_AB_LCDRAM6_FP25_BP_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_AB_LCDRAM6_FP26_BP       (0xff << 8)
#define BPORT1_AB_LCDRAM6_FP26_BP_GET(_v)  ((_v >> 8) & 0xff)
#define BPORT1_AB_LCDRAM6_FP27_BP       0xff
#define BPORT1_AB_LCDRAM6_FP27_BP_GET(_v)  (_v & 0xff)

#define BPORT1_AB_LCDRAM7_POFFSET       0x3c
#define BPORT1_AB_LCDRAM7               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LCDRAM7_POFFSET)
#define BPORT1_AB_LCDRAM7_FP28_BP       (0xff << 24)
#define BPORT1_AB_LCDRAM7_FP28_BP_GET(_v)  ((_v >> 24) & 0xff)
#define BPORT1_AB_LCDRAM7_FP29_BP       (0xff << 16)
#define BPORT1_AB_LCDRAM7_FP29_BP_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_AB_LCDRAM7_FP30_BP       (0xff << 8)
#define BPORT1_AB_LCDRAM7_FP30_BP_GET(_v)  ((_v >> 8) & 0xff)
#define BPORT1_AB_LCDRAM7_FP31_BP       0xff
#define BPORT1_AB_LCDRAM7_FP31_BP_GET(_v)  (_v & 0xff)

#define BPORT1_AB_LCDRAM8_POFFSET       0x40
#define BPORT1_AB_LCDRAM8               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LCDRAM8_POFFSET)
#define BPORT1_AB_LCDRAM8_FP32_BP       (0xff << 24)
#define BPORT1_AB_LCDRAM8_FP32_BP_GET(_v)  ((_v >> 24) & 0xff)
#define BPORT1_AB_LCDRAM8_FP33_BP       (0xff << 16)
#define BPORT1_AB_LCDRAM8_FP33_BP_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_AB_LCDRAM8_FP34_BP       (0xff << 8)
#define BPORT1_AB_LCDRAM8_FP34_BP_GET(_v)  ((_v >> 8) & 0xff)
#define BPORT1_AB_LCDRAM8_FP35_BP       0xff
#define BPORT1_AB_LCDRAM8_FP35_BP_GET(_v)  (_v & 0xff)

#define BPORT1_AB_LCDRAM9_POFFSET       0x44
#define BPORT1_AB_LCDRAM9               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LCDRAM9_POFFSET)
#define BPORT1_AB_LCDRAM9_FP36_BP       (0xff << 24)
#define BPORT1_AB_LCDRAM9_FP36_BP_GET(_v)  ((_v >> 24) & 0xff)
#define BPORT1_AB_LCDRAM9_FP37_BP       (0xff << 16)
#define BPORT1_AB_LCDRAM9_FP37_BP_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_AB_LCDRAM9_FP38_BP       (0xff << 8)
#define BPORT1_AB_LCDRAM9_FP38_BP_GET(_v)  ((_v >> 8) & 0xff)
#define BPORT1_AB_LCDRAM9_FP39_BP       0xff
#define BPORT1_AB_LCDRAM9_FP39_BP_GET(_v)  (_v & 0xff)

#define BPORT1_AB_LCDRAM10_POFFSET      0x48
#define BPORT1_AB_LCDRAM10              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LCDRAM10_POFFSET)
#define BPORT1_AB_LCDRAM10_FP40_BP      (0xff << 24)
#define BPORT1_AB_LCDRAM10_FP40_BP_GET(_v)  ((_v >> 24) & 0xff)
#define BPORT1_AB_LCDRAM10_FP41_BP      (0xff << 16)
#define BPORT1_AB_LCDRAM10_FP41_BP_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_AB_LCDRAM10_FP42_BP      (0xff << 8)
#define BPORT1_AB_LCDRAM10_FP42_BP_GET(_v)  ((_v >> 8) & 0xff)
#define BPORT1_AB_LCDRAM10_FP43_BP      0xff
#define BPORT1_AB_LCDRAM10_FP43_BP_GET(_v)  (_v & 0xff)

#define BPORT1_AB_LCDRAM11_POFFSET      0x4c
#define BPORT1_AB_LCDRAM11              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LCDRAM11_POFFSET)
#define BPORT1_AB_LCDRAM11_FP44_BP      (0xff << 24)
#define BPORT1_AB_LCDRAM11_FP44_BP_GET(_v)  ((_v >> 24) & 0xff)
#define BPORT1_AB_LCDRAM11_FP45_BP      (0xff << 16)
#define BPORT1_AB_LCDRAM11_FP45_BP_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_AB_LCDRAM11_FP46_BP      (0xff << 8)
#define BPORT1_AB_LCDRAM11_FP46_BP_GET(_v)  ((_v >> 8) & 0xff)
#define BPORT1_AB_LCDRAM11_FP47_BP      0xff
#define BPORT1_AB_LCDRAM11_FP47_BP_GET(_v)  (_v & 0xff)

#define BPORT1_AB_LCDRAM12_POFFSET      0x50
#define BPORT1_AB_LCDRAM12              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LCDRAM12_POFFSET)
#define BPORT1_AB_LCDRAM12_FP48_BP      (0xff << 24)
#define BPORT1_AB_LCDRAM12_FP48_BP_GET(_v)  ((_v >> 24) & 0xff)
#define BPORT1_AB_LCDRAM12_FP49_BP      (0xff << 16)
#define BPORT1_AB_LCDRAM12_FP49_BP_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_AB_LCDRAM12_FP50_BP      (0xff << 8)
#define BPORT1_AB_LCDRAM12_FP50_BP_GET(_v)  ((_v >> 8) & 0xff)
#define BPORT1_AB_LCDRAM12_FP51_BP      0xff
#define BPORT1_AB_LCDRAM12_FP51_BP_GET(_v)  (_v & 0xff)

#define BPORT1_AB_LCDRAM13_POFFSET      0x54
#define BPORT1_AB_LCDRAM13              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LCDRAM13_POFFSET)
#define BPORT1_AB_LCDRAM13_FP52_BP      (0xff << 24)
#define BPORT1_AB_LCDRAM13_FP52_BP_GET(_v)  ((_v >> 24) & 0xff)
#define BPORT1_AB_LCDRAM13_FP53_BP      (0xff << 16)
#define BPORT1_AB_LCDRAM13_FP53_BP_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_AB_LCDRAM13_FP54_BP      (0xff << 8)
#define BPORT1_AB_LCDRAM13_FP54_BP_GET(_v)  ((_v >> 8) & 0xff)
#define BPORT1_AB_LCDRAM13_FP55_BP      0xff
#define BPORT1_AB_LCDRAM13_FP55_BP_GET(_v)  (_v & 0xff)

#define BPORT1_AB_LCDRAM14_POFFSET      0x58
#define BPORT1_AB_LCDRAM14              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LCDRAM14_POFFSET)
#define BPORT1_AB_LCDRAM14_FP56_BP      (0xff << 24)
#define BPORT1_AB_LCDRAM14_FP56_BP_GET(_v)  ((_v >> 24) & 0xff)
#define BPORT1_AB_LCDRAM14_FP57_BP      (0xff << 16)
#define BPORT1_AB_LCDRAM14_FP57_BP_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_AB_LCDRAM14_FP58_BP      (0xff << 8)
#define BPORT1_AB_LCDRAM14_FP58_BP_GET(_v)  ((_v >> 8) & 0xff)
#define BPORT1_AB_LCDRAM14_FP59_BP      0xff
#define BPORT1_AB_LCDRAM14_FP59_BP_GET(_v)  (_v & 0xff)

#define BPORT1_AB_LCDRAM15_POFFSET      0x5c
#define BPORT1_AB_LCDRAM15              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LCDRAM15_POFFSET)
#define BPORT1_AB_LCDRAM15_FP60_BP      (0xff << 24)
#define BPORT1_AB_LCDRAM15_FP60_BP_GET(_v)  ((_v >> 24) & 0xff)
#define BPORT1_AB_LCDRAM15_FP61_BP      (0xff << 16)
#define BPORT1_AB_LCDRAM15_FP61_BP_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_AB_LCDRAM15_FP62_BP      (0xff << 8)
#define BPORT1_AB_LCDRAM15_FP62_BP_GET(_v)  ((_v >> 8) & 0xff)
#define BPORT1_AB_LCDRAM15_FP63_BP      0xff
#define BPORT1_AB_LCDRAM15_FP63_BP_GET(_v)  (_v & 0xff)


#endif

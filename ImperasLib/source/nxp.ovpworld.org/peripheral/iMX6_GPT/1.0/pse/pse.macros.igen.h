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
#define BPORT1_AB_GPT_CR_POFFSET        0x0
#define BPORT1_AB_GPT_CR                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPT_CR_POFFSET)
#define BPORT1_AB_GPT_CR_FO3            (0x1 << 31)
#define BPORT1_AB_GPT_CR_FO3_GET(_v)    ((_v >> 31) & 0x1)
#define BPORT1_AB_GPT_CR_FO2            (0x1 << 30)
#define BPORT1_AB_GPT_CR_FO2_GET(_v)    ((_v >> 30) & 0x1)
#define BPORT1_AB_GPT_CR_FO1            (0x1 << 29)
#define BPORT1_AB_GPT_CR_FO1_GET(_v)    ((_v >> 29) & 0x1)
#define BPORT1_AB_GPT_CR_OM3            (0x7 << 26)
#define BPORT1_AB_GPT_CR_OM3_GET(_v)    ((_v >> 26) & 0x7)
#define BPORT1_AB_GPT_CR_OM2            (0x7 << 23)
#define BPORT1_AB_GPT_CR_OM2_GET(_v)    ((_v >> 23) & 0x7)
#define BPORT1_AB_GPT_CR_OM1            (0x7 << 20)
#define BPORT1_AB_GPT_CR_OM1_GET(_v)    ((_v >> 20) & 0x7)
#define BPORT1_AB_GPT_CR_IM2            (0x3 << 18)
#define BPORT1_AB_GPT_CR_IM2_GET(_v)    ((_v >> 18) & 0x3)
#define BPORT1_AB_GPT_CR_IM1            (0x3 << 16)
#define BPORT1_AB_GPT_CR_IM1_GET(_v)    ((_v >> 16) & 0x3)
#define BPORT1_AB_GPT_CR_SWR            (0x1 << 15)
#define BPORT1_AB_GPT_CR_SWR_GET(_v)    ((_v >> 15) & 0x1)
#define BPORT1_AB_GPT_CR_EN_24M         (0x1 << 10)
#define BPORT1_AB_GPT_CR_EN_24M_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_GPT_CR_FRR            (0x1 << 9)
#define BPORT1_AB_GPT_CR_FRR_GET(_v)    ((_v >> 9) & 0x1)
#define BPORT1_AB_GPT_CR_CLKSRC         (0x7 << 6)
#define BPORT1_AB_GPT_CR_CLKSRC_GET(_v)  ((_v >> 6) & 0x7)
#define BPORT1_AB_GPT_CR_STOPEN         (0x1 << 5)
#define BPORT1_AB_GPT_CR_STOPEN_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_GPT_CR_DOZEEN         (0x1 << 4)
#define BPORT1_AB_GPT_CR_DOZEEN_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_GPT_CR_QAITEN         (0x1 << 3)
#define BPORT1_AB_GPT_CR_QAITEN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_GPT_CR_DBGEN          (0x1 << 2)
#define BPORT1_AB_GPT_CR_DBGEN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_GPT_CR_ENMOD          (0x1 << 1)
#define BPORT1_AB_GPT_CR_ENMOD_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_GPT_CR_EN             0x1
#define BPORT1_AB_GPT_CR_EN_GET(_v)     (_v & 0x1)

#define BPORT1_AB_GPT_PR_POFFSET        0x4
#define BPORT1_AB_GPT_PR                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPT_PR_POFFSET)
#define BPORT1_AB_GPT_PR_PRESCALER24M   (0xf << 12)
#define BPORT1_AB_GPT_PR_PRESCALER24M_GET(_v)  ((_v >> 12) & 0xf)
#define BPORT1_AB_GPT_PR_PRESCALER      0xfff
#define BPORT1_AB_GPT_PR_PRESCALER_GET(_v)  (_v & 0xfff)

#define BPORT1_AB_GPT_SR_POFFSET        0x8
#define BPORT1_AB_GPT_SR                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPT_SR_POFFSET)
#define BPORT1_AB_GPT_SR_ROV            (0x1 << 5)
#define BPORT1_AB_GPT_SR_ROV_GET(_v)    ((_v >> 5) & 0x1)
#define BPORT1_AB_GPT_SR_IF2            (0x1 << 4)
#define BPORT1_AB_GPT_SR_IF2_GET(_v)    ((_v >> 4) & 0x1)
#define BPORT1_AB_GPT_SR_IF1            (0x1 << 3)
#define BPORT1_AB_GPT_SR_IF1_GET(_v)    ((_v >> 3) & 0x1)
#define BPORT1_AB_GPT_SR_OF3            (0x1 << 2)
#define BPORT1_AB_GPT_SR_OF3_GET(_v)    ((_v >> 2) & 0x1)
#define BPORT1_AB_GPT_SR_OF2            (0x1 << 1)
#define BPORT1_AB_GPT_SR_OF2_GET(_v)    ((_v >> 1) & 0x1)
#define BPORT1_AB_GPT_SR_OF1            0x1
#define BPORT1_AB_GPT_SR_OF1_GET(_v)    (_v & 0x1)

#define BPORT1_AB_GPT_IR_POFFSET        0xc
#define BPORT1_AB_GPT_IR                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPT_IR_POFFSET)
#define BPORT1_AB_GPT_IR_ROVIE          (0x1 << 5)
#define BPORT1_AB_GPT_IR_ROVIE_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_GPT_IR_IF2IE          (0x1 << 4)
#define BPORT1_AB_GPT_IR_IF2IE_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_GPT_IR_IF1IE          (0x1 << 3)
#define BPORT1_AB_GPT_IR_IF1IE_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_GPT_IR_OF3IE          (0x1 << 2)
#define BPORT1_AB_GPT_IR_OF3IE_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_GPT_IR_OF2IE          (0x1 << 1)
#define BPORT1_AB_GPT_IR_OF2IE_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_GPT_IR_OF1IE          0x1
#define BPORT1_AB_GPT_IR_OF1IE_GET(_v)  (_v & 0x1)

#define BPORT1_AB_GPT_OCR1_POFFSET      0x10
#define BPORT1_AB_GPT_OCR1              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPT_OCR1_POFFSET)

#define BPORT1_AB_GPT_OCR2_POFFSET      0x14
#define BPORT1_AB_GPT_OCR2              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPT_OCR2_POFFSET)

#define BPORT1_AB_GPT_OCR3_POFFSET      0x18
#define BPORT1_AB_GPT_OCR3              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPT_OCR3_POFFSET)

#define BPORT1_AB_GPT_ICR1_POFFSET      0x1c
#define BPORT1_AB_GPT_ICR1              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPT_ICR1_POFFSET)

#define BPORT1_AB_GPT_ICR2_POFFSET      0x20
#define BPORT1_AB_GPT_ICR2              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPT_ICR2_POFFSET)

#define BPORT1_AB_GPT_CNT_POFFSET       0x24
#define BPORT1_AB_GPT_CNT               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_GPT_CNT_POFFSET)

#define BPORT1_AB_BUFFER_POFFSET        0x0
#define BPORT1_AB_BUFFER                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BUFFER_POFFSET)
#define BPORT1_AB_BUFFER_BYTES          0x1000


#endif

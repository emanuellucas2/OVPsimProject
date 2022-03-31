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
#define BPORT1_AB_CR_POFFSET            0x0
#define BPORT1_AB_CR                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CR_POFFSET)
#define BPORT1_AB_CR_CLM                (0x1 << 6)
#define BPORT1_AB_CR_CLM_GET(_v)        ((_v >> 6) & 0x1)
#define BPORT1_AB_CR_CX                 (0x1 << 17)
#define BPORT1_AB_CR_CX_GET(_v)         ((_v >> 17) & 0x1)
#define BPORT1_AB_CR_ECX                (0x1 << 16)
#define BPORT1_AB_CR_ECX_GET(_v)        ((_v >> 16) & 0x1)
#define BPORT1_AB_CR_EDBG               (0x1 << 1)
#define BPORT1_AB_CR_EDBG_GET(_v)       ((_v >> 1) & 0x1)
#define BPORT1_AB_CR_EMLM               (0x1 << 7)
#define BPORT1_AB_CR_EMLM_GET(_v)       ((_v >> 7) & 0x1)
#define BPORT1_AB_CR_ERCA               (0x1 << 2)
#define BPORT1_AB_CR_ERCA_GET(_v)       ((_v >> 2) & 0x1)
#define BPORT1_AB_CR_ERGA               (0x1 << 3)
#define BPORT1_AB_CR_ERGA_GET(_v)       ((_v >> 3) & 0x1)
#define BPORT1_AB_CR_GRP0PRI            (0x3 << 8)
#define BPORT1_AB_CR_GRP0PRI_GET(_v)    ((_v >> 8) & 0x3)
#define BPORT1_AB_CR_GRP1PRI            (0x3 << 10)
#define BPORT1_AB_CR_GRP1PRI_GET(_v)    ((_v >> 10) & 0x3)
#define BPORT1_AB_CR_HALT               (0x1 << 5)
#define BPORT1_AB_CR_HALT_GET(_v)       ((_v >> 5) & 0x1)
#define BPORT1_AB_CR_HOE                (0x1 << 4)
#define BPORT1_AB_CR_HOE_GET(_v)        ((_v >> 4) & 0x1)

#define BPORT1_AB_ES_POFFSET            0x4
#define BPORT1_AB_ES                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ES_POFFSET)
#define BPORT1_AB_ES_CPE                (0x1 << 14)
#define BPORT1_AB_ES_CPE_GET(_v)        ((_v >> 14) & 0x1)
#define BPORT1_AB_ES_DAE                (0x1 << 5)
#define BPORT1_AB_ES_DAE_GET(_v)        ((_v >> 5) & 0x1)
#define BPORT1_AB_ES_DBE                0x1
#define BPORT1_AB_ES_DBE_GET(_v)        (_v & 0x1)
#define BPORT1_AB_ES_DOE                (0x1 << 4)
#define BPORT1_AB_ES_DOE_GET(_v)        ((_v >> 4) & 0x1)
#define BPORT1_AB_ES_ECX                (0x1 << 16)
#define BPORT1_AB_ES_ECX_GET(_v)        ((_v >> 16) & 0x1)
#define BPORT1_AB_ES_ERRCHN             (0x1f << 8)
#define BPORT1_AB_ES_ERRCHN_GET(_v)     ((_v >> 8) & 0x1f)
#define BPORT1_AB_ES_GPE                (0x1 << 15)
#define BPORT1_AB_ES_GPE_GET(_v)        ((_v >> 15) & 0x1)
#define BPORT1_AB_ES_NCE                (0x1 << 3)
#define BPORT1_AB_ES_NCE_GET(_v)        ((_v >> 3) & 0x1)
#define BPORT1_AB_ES_SAE                (0x1 << 7)
#define BPORT1_AB_ES_SAE_GET(_v)        ((_v >> 7) & 0x1)
#define BPORT1_AB_ES_SBE                (0x1 << 1)
#define BPORT1_AB_ES_SBE_GET(_v)        ((_v >> 1) & 0x1)
#define BPORT1_AB_ES_SGE                (0x1 << 2)
#define BPORT1_AB_ES_SGE_GET(_v)        ((_v >> 2) & 0x1)
#define BPORT1_AB_ES_SOE                (0x1 << 6)
#define BPORT1_AB_ES_SOE_GET(_v)        ((_v >> 6) & 0x1)
#define BPORT1_AB_ES_VLD                (0x1 << 31)
#define BPORT1_AB_ES_VLD_GET(_v)        ((_v >> 31) & 0x1)

#define BPORT1_AB_ERQ_POFFSET           0xc
#define BPORT1_AB_ERQ                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ERQ_POFFSET)
#define BPORT1_AB_ERQ_ERQ0              0x1
#define BPORT1_AB_ERQ_ERQ0_GET(_v)      (_v & 0x1)
#define BPORT1_AB_ERQ_ERQ1              (0x1 << 1)
#define BPORT1_AB_ERQ_ERQ1_GET(_v)      ((_v >> 1) & 0x1)
#define BPORT1_AB_ERQ_ERQ10             (0x1 << 10)
#define BPORT1_AB_ERQ_ERQ10_GET(_v)     ((_v >> 10) & 0x1)
#define BPORT1_AB_ERQ_ERQ11             (0x1 << 11)
#define BPORT1_AB_ERQ_ERQ11_GET(_v)     ((_v >> 11) & 0x1)
#define BPORT1_AB_ERQ_ERQ12             (0x1 << 12)
#define BPORT1_AB_ERQ_ERQ12_GET(_v)     ((_v >> 12) & 0x1)
#define BPORT1_AB_ERQ_ERQ13             (0x1 << 13)
#define BPORT1_AB_ERQ_ERQ13_GET(_v)     ((_v >> 13) & 0x1)
#define BPORT1_AB_ERQ_ERQ14             (0x1 << 14)
#define BPORT1_AB_ERQ_ERQ14_GET(_v)     ((_v >> 14) & 0x1)
#define BPORT1_AB_ERQ_ERQ15             (0x1 << 15)
#define BPORT1_AB_ERQ_ERQ15_GET(_v)     ((_v >> 15) & 0x1)
#define BPORT1_AB_ERQ_ERQ16             (0x1 << 16)
#define BPORT1_AB_ERQ_ERQ16_GET(_v)     ((_v >> 16) & 0x1)
#define BPORT1_AB_ERQ_ERQ17             (0x1 << 17)
#define BPORT1_AB_ERQ_ERQ17_GET(_v)     ((_v >> 17) & 0x1)
#define BPORT1_AB_ERQ_ERQ18             (0x1 << 18)
#define BPORT1_AB_ERQ_ERQ18_GET(_v)     ((_v >> 18) & 0x1)
#define BPORT1_AB_ERQ_ERQ19             (0x1 << 19)
#define BPORT1_AB_ERQ_ERQ19_GET(_v)     ((_v >> 19) & 0x1)
#define BPORT1_AB_ERQ_ERQ2              (0x1 << 2)
#define BPORT1_AB_ERQ_ERQ2_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_ERQ_ERQ20             (0x1 << 20)
#define BPORT1_AB_ERQ_ERQ20_GET(_v)     ((_v >> 20) & 0x1)
#define BPORT1_AB_ERQ_ERQ21             (0x1 << 21)
#define BPORT1_AB_ERQ_ERQ21_GET(_v)     ((_v >> 21) & 0x1)
#define BPORT1_AB_ERQ_ERQ22             (0x1 << 22)
#define BPORT1_AB_ERQ_ERQ22_GET(_v)     ((_v >> 22) & 0x1)
#define BPORT1_AB_ERQ_ERQ23             (0x1 << 23)
#define BPORT1_AB_ERQ_ERQ23_GET(_v)     ((_v >> 23) & 0x1)
#define BPORT1_AB_ERQ_ERQ24             (0x1 << 24)
#define BPORT1_AB_ERQ_ERQ24_GET(_v)     ((_v >> 24) & 0x1)
#define BPORT1_AB_ERQ_ERQ25             (0x1 << 25)
#define BPORT1_AB_ERQ_ERQ25_GET(_v)     ((_v >> 25) & 0x1)
#define BPORT1_AB_ERQ_ERQ26             (0x1 << 26)
#define BPORT1_AB_ERQ_ERQ26_GET(_v)     ((_v >> 26) & 0x1)
#define BPORT1_AB_ERQ_ERQ27             (0x1 << 27)
#define BPORT1_AB_ERQ_ERQ27_GET(_v)     ((_v >> 27) & 0x1)
#define BPORT1_AB_ERQ_ERQ28             (0x1 << 28)
#define BPORT1_AB_ERQ_ERQ28_GET(_v)     ((_v >> 28) & 0x1)
#define BPORT1_AB_ERQ_ERQ29             (0x1 << 29)
#define BPORT1_AB_ERQ_ERQ29_GET(_v)     ((_v >> 29) & 0x1)
#define BPORT1_AB_ERQ_ERQ3              (0x1 << 3)
#define BPORT1_AB_ERQ_ERQ3_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_ERQ_ERQ30             (0x1 << 30)
#define BPORT1_AB_ERQ_ERQ30_GET(_v)     ((_v >> 30) & 0x1)
#define BPORT1_AB_ERQ_ERQ31             (0x1 << 31)
#define BPORT1_AB_ERQ_ERQ31_GET(_v)     ((_v >> 31) & 0x1)
#define BPORT1_AB_ERQ_ERQ4              (0x1 << 4)
#define BPORT1_AB_ERQ_ERQ4_GET(_v)      ((_v >> 4) & 0x1)
#define BPORT1_AB_ERQ_ERQ5              (0x1 << 5)
#define BPORT1_AB_ERQ_ERQ5_GET(_v)      ((_v >> 5) & 0x1)
#define BPORT1_AB_ERQ_ERQ6              (0x1 << 6)
#define BPORT1_AB_ERQ_ERQ6_GET(_v)      ((_v >> 6) & 0x1)
#define BPORT1_AB_ERQ_ERQ7              (0x1 << 7)
#define BPORT1_AB_ERQ_ERQ7_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_ERQ_ERQ8              (0x1 << 8)
#define BPORT1_AB_ERQ_ERQ8_GET(_v)      ((_v >> 8) & 0x1)
#define BPORT1_AB_ERQ_ERQ9              (0x1 << 9)
#define BPORT1_AB_ERQ_ERQ9_GET(_v)      ((_v >> 9) & 0x1)

#define BPORT1_AB_EEI_POFFSET           0x14
#define BPORT1_AB_EEI                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EEI_POFFSET)
#define BPORT1_AB_EEI_EEI0              0x1
#define BPORT1_AB_EEI_EEI0_GET(_v)      (_v & 0x1)
#define BPORT1_AB_EEI_EEI1              (0x1 << 1)
#define BPORT1_AB_EEI_EEI1_GET(_v)      ((_v >> 1) & 0x1)
#define BPORT1_AB_EEI_EEI10             (0x1 << 10)
#define BPORT1_AB_EEI_EEI10_GET(_v)     ((_v >> 10) & 0x1)
#define BPORT1_AB_EEI_EEI11             (0x1 << 11)
#define BPORT1_AB_EEI_EEI11_GET(_v)     ((_v >> 11) & 0x1)
#define BPORT1_AB_EEI_EEI12             (0x1 << 12)
#define BPORT1_AB_EEI_EEI12_GET(_v)     ((_v >> 12) & 0x1)
#define BPORT1_AB_EEI_EEI13             (0x1 << 13)
#define BPORT1_AB_EEI_EEI13_GET(_v)     ((_v >> 13) & 0x1)
#define BPORT1_AB_EEI_EEI14             (0x1 << 14)
#define BPORT1_AB_EEI_EEI14_GET(_v)     ((_v >> 14) & 0x1)
#define BPORT1_AB_EEI_EEI15             (0x1 << 15)
#define BPORT1_AB_EEI_EEI15_GET(_v)     ((_v >> 15) & 0x1)
#define BPORT1_AB_EEI_EEI16             (0x1 << 16)
#define BPORT1_AB_EEI_EEI16_GET(_v)     ((_v >> 16) & 0x1)
#define BPORT1_AB_EEI_EEI17             (0x1 << 17)
#define BPORT1_AB_EEI_EEI17_GET(_v)     ((_v >> 17) & 0x1)
#define BPORT1_AB_EEI_EEI18             (0x1 << 18)
#define BPORT1_AB_EEI_EEI18_GET(_v)     ((_v >> 18) & 0x1)
#define BPORT1_AB_EEI_EEI19             (0x1 << 19)
#define BPORT1_AB_EEI_EEI19_GET(_v)     ((_v >> 19) & 0x1)
#define BPORT1_AB_EEI_EEI2              (0x1 << 2)
#define BPORT1_AB_EEI_EEI2_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_EEI_EEI20             (0x1 << 20)
#define BPORT1_AB_EEI_EEI20_GET(_v)     ((_v >> 20) & 0x1)
#define BPORT1_AB_EEI_EEI21             (0x1 << 21)
#define BPORT1_AB_EEI_EEI21_GET(_v)     ((_v >> 21) & 0x1)
#define BPORT1_AB_EEI_EEI22             (0x1 << 22)
#define BPORT1_AB_EEI_EEI22_GET(_v)     ((_v >> 22) & 0x1)
#define BPORT1_AB_EEI_EEI23             (0x1 << 23)
#define BPORT1_AB_EEI_EEI23_GET(_v)     ((_v >> 23) & 0x1)
#define BPORT1_AB_EEI_EEI24             (0x1 << 24)
#define BPORT1_AB_EEI_EEI24_GET(_v)     ((_v >> 24) & 0x1)
#define BPORT1_AB_EEI_EEI25             (0x1 << 25)
#define BPORT1_AB_EEI_EEI25_GET(_v)     ((_v >> 25) & 0x1)
#define BPORT1_AB_EEI_EEI26             (0x1 << 26)
#define BPORT1_AB_EEI_EEI26_GET(_v)     ((_v >> 26) & 0x1)
#define BPORT1_AB_EEI_EEI27             (0x1 << 27)
#define BPORT1_AB_EEI_EEI27_GET(_v)     ((_v >> 27) & 0x1)
#define BPORT1_AB_EEI_EEI28             (0x1 << 28)
#define BPORT1_AB_EEI_EEI28_GET(_v)     ((_v >> 28) & 0x1)
#define BPORT1_AB_EEI_EEI29             (0x1 << 29)
#define BPORT1_AB_EEI_EEI29_GET(_v)     ((_v >> 29) & 0x1)
#define BPORT1_AB_EEI_EEI3              (0x1 << 3)
#define BPORT1_AB_EEI_EEI3_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_EEI_EEI30             (0x1 << 30)
#define BPORT1_AB_EEI_EEI30_GET(_v)     ((_v >> 30) & 0x1)
#define BPORT1_AB_EEI_EEI31             (0x1 << 31)
#define BPORT1_AB_EEI_EEI31_GET(_v)     ((_v >> 31) & 0x1)
#define BPORT1_AB_EEI_EEI4              (0x1 << 4)
#define BPORT1_AB_EEI_EEI4_GET(_v)      ((_v >> 4) & 0x1)
#define BPORT1_AB_EEI_EEI5              (0x1 << 5)
#define BPORT1_AB_EEI_EEI5_GET(_v)      ((_v >> 5) & 0x1)
#define BPORT1_AB_EEI_EEI6              (0x1 << 6)
#define BPORT1_AB_EEI_EEI6_GET(_v)      ((_v >> 6) & 0x1)
#define BPORT1_AB_EEI_EEI7              (0x1 << 7)
#define BPORT1_AB_EEI_EEI7_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_EEI_EEI8              (0x1 << 8)
#define BPORT1_AB_EEI_EEI8_GET(_v)      ((_v >> 8) & 0x1)
#define BPORT1_AB_EEI_EEI9              (0x1 << 9)
#define BPORT1_AB_EEI_EEI9_GET(_v)      ((_v >> 9) & 0x1)

#define BPORT1_AB_CS_EEI_ERC_POFFSET    0x18
#define BPORT1_AB_CS_EEI_ERC            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CS_EEI_ERC_POFFSET)

#define BPORT1_AB_DNE_SRT_ERR_INT_POFFSET  0x1c
#define BPORT1_AB_DNE_SRT_ERR_INT       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DNE_SRT_ERR_INT_POFFSET)

#define BPORT1_AB_INT_POFFSET           0x24
#define BPORT1_AB_INT                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INT_POFFSET)
#define BPORT1_AB_INT_INT0              0x1
#define BPORT1_AB_INT_INT0_GET(_v)      (_v & 0x1)
#define BPORT1_AB_INT_INT1              (0x1 << 1)
#define BPORT1_AB_INT_INT1_GET(_v)      ((_v >> 1) & 0x1)
#define BPORT1_AB_INT_INT10             (0x1 << 10)
#define BPORT1_AB_INT_INT10_GET(_v)     ((_v >> 10) & 0x1)
#define BPORT1_AB_INT_INT11             (0x1 << 11)
#define BPORT1_AB_INT_INT11_GET(_v)     ((_v >> 11) & 0x1)
#define BPORT1_AB_INT_INT12             (0x1 << 12)
#define BPORT1_AB_INT_INT12_GET(_v)     ((_v >> 12) & 0x1)
#define BPORT1_AB_INT_INT13             (0x1 << 13)
#define BPORT1_AB_INT_INT13_GET(_v)     ((_v >> 13) & 0x1)
#define BPORT1_AB_INT_INT14             (0x1 << 14)
#define BPORT1_AB_INT_INT14_GET(_v)     ((_v >> 14) & 0x1)
#define BPORT1_AB_INT_INT15             (0x1 << 15)
#define BPORT1_AB_INT_INT15_GET(_v)     ((_v >> 15) & 0x1)
#define BPORT1_AB_INT_INT16             (0x1 << 16)
#define BPORT1_AB_INT_INT16_GET(_v)     ((_v >> 16) & 0x1)
#define BPORT1_AB_INT_INT17             (0x1 << 17)
#define BPORT1_AB_INT_INT17_GET(_v)     ((_v >> 17) & 0x1)
#define BPORT1_AB_INT_INT18             (0x1 << 18)
#define BPORT1_AB_INT_INT18_GET(_v)     ((_v >> 18) & 0x1)
#define BPORT1_AB_INT_INT19             (0x1 << 19)
#define BPORT1_AB_INT_INT19_GET(_v)     ((_v >> 19) & 0x1)
#define BPORT1_AB_INT_INT2              (0x1 << 2)
#define BPORT1_AB_INT_INT2_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_INT_INT20             (0x1 << 20)
#define BPORT1_AB_INT_INT20_GET(_v)     ((_v >> 20) & 0x1)
#define BPORT1_AB_INT_INT21             (0x1 << 21)
#define BPORT1_AB_INT_INT21_GET(_v)     ((_v >> 21) & 0x1)
#define BPORT1_AB_INT_INT22             (0x1 << 22)
#define BPORT1_AB_INT_INT22_GET(_v)     ((_v >> 22) & 0x1)
#define BPORT1_AB_INT_INT23             (0x1 << 23)
#define BPORT1_AB_INT_INT23_GET(_v)     ((_v >> 23) & 0x1)
#define BPORT1_AB_INT_INT24             (0x1 << 24)
#define BPORT1_AB_INT_INT24_GET(_v)     ((_v >> 24) & 0x1)
#define BPORT1_AB_INT_INT25             (0x1 << 25)
#define BPORT1_AB_INT_INT25_GET(_v)     ((_v >> 25) & 0x1)
#define BPORT1_AB_INT_INT26             (0x1 << 26)
#define BPORT1_AB_INT_INT26_GET(_v)     ((_v >> 26) & 0x1)
#define BPORT1_AB_INT_INT27             (0x1 << 27)
#define BPORT1_AB_INT_INT27_GET(_v)     ((_v >> 27) & 0x1)
#define BPORT1_AB_INT_INT28             (0x1 << 28)
#define BPORT1_AB_INT_INT28_GET(_v)     ((_v >> 28) & 0x1)
#define BPORT1_AB_INT_INT29             (0x1 << 29)
#define BPORT1_AB_INT_INT29_GET(_v)     ((_v >> 29) & 0x1)
#define BPORT1_AB_INT_INT3              (0x1 << 3)
#define BPORT1_AB_INT_INT3_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_INT_INT30             (0x1 << 30)
#define BPORT1_AB_INT_INT30_GET(_v)     ((_v >> 30) & 0x1)
#define BPORT1_AB_INT_INT31             (0x1 << 31)
#define BPORT1_AB_INT_INT31_GET(_v)     ((_v >> 31) & 0x1)
#define BPORT1_AB_INT_INT4              (0x1 << 4)
#define BPORT1_AB_INT_INT4_GET(_v)      ((_v >> 4) & 0x1)
#define BPORT1_AB_INT_INT5              (0x1 << 5)
#define BPORT1_AB_INT_INT5_GET(_v)      ((_v >> 5) & 0x1)
#define BPORT1_AB_INT_INT6              (0x1 << 6)
#define BPORT1_AB_INT_INT6_GET(_v)      ((_v >> 6) & 0x1)
#define BPORT1_AB_INT_INT7              (0x1 << 7)
#define BPORT1_AB_INT_INT7_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_INT_INT8              (0x1 << 8)
#define BPORT1_AB_INT_INT8_GET(_v)      ((_v >> 8) & 0x1)
#define BPORT1_AB_INT_INT9              (0x1 << 9)
#define BPORT1_AB_INT_INT9_GET(_v)      ((_v >> 9) & 0x1)

#define BPORT1_AB_ERR_POFFSET           0x2c
#define BPORT1_AB_ERR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ERR_POFFSET)
#define BPORT1_AB_ERR_ERR0              0x1
#define BPORT1_AB_ERR_ERR0_GET(_v)      (_v & 0x1)
#define BPORT1_AB_ERR_ERR1              (0x1 << 1)
#define BPORT1_AB_ERR_ERR1_GET(_v)      ((_v >> 1) & 0x1)
#define BPORT1_AB_ERR_ERR10             (0x1 << 10)
#define BPORT1_AB_ERR_ERR10_GET(_v)     ((_v >> 10) & 0x1)
#define BPORT1_AB_ERR_ERR11             (0x1 << 11)
#define BPORT1_AB_ERR_ERR11_GET(_v)     ((_v >> 11) & 0x1)
#define BPORT1_AB_ERR_ERR12             (0x1 << 12)
#define BPORT1_AB_ERR_ERR12_GET(_v)     ((_v >> 12) & 0x1)
#define BPORT1_AB_ERR_ERR13             (0x1 << 13)
#define BPORT1_AB_ERR_ERR13_GET(_v)     ((_v >> 13) & 0x1)
#define BPORT1_AB_ERR_ERR14             (0x1 << 14)
#define BPORT1_AB_ERR_ERR14_GET(_v)     ((_v >> 14) & 0x1)
#define BPORT1_AB_ERR_ERR15             (0x1 << 15)
#define BPORT1_AB_ERR_ERR15_GET(_v)     ((_v >> 15) & 0x1)
#define BPORT1_AB_ERR_ERR16             (0x1 << 16)
#define BPORT1_AB_ERR_ERR16_GET(_v)     ((_v >> 16) & 0x1)
#define BPORT1_AB_ERR_ERR17             (0x1 << 17)
#define BPORT1_AB_ERR_ERR17_GET(_v)     ((_v >> 17) & 0x1)
#define BPORT1_AB_ERR_ERR18             (0x1 << 18)
#define BPORT1_AB_ERR_ERR18_GET(_v)     ((_v >> 18) & 0x1)
#define BPORT1_AB_ERR_ERR19             (0x1 << 19)
#define BPORT1_AB_ERR_ERR19_GET(_v)     ((_v >> 19) & 0x1)
#define BPORT1_AB_ERR_ERR2              (0x1 << 2)
#define BPORT1_AB_ERR_ERR2_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_ERR_ERR20             (0x1 << 20)
#define BPORT1_AB_ERR_ERR20_GET(_v)     ((_v >> 20) & 0x1)
#define BPORT1_AB_ERR_ERR21             (0x1 << 21)
#define BPORT1_AB_ERR_ERR21_GET(_v)     ((_v >> 21) & 0x1)
#define BPORT1_AB_ERR_ERR22             (0x1 << 22)
#define BPORT1_AB_ERR_ERR22_GET(_v)     ((_v >> 22) & 0x1)
#define BPORT1_AB_ERR_ERR23             (0x1 << 23)
#define BPORT1_AB_ERR_ERR23_GET(_v)     ((_v >> 23) & 0x1)
#define BPORT1_AB_ERR_ERR24             (0x1 << 24)
#define BPORT1_AB_ERR_ERR24_GET(_v)     ((_v >> 24) & 0x1)
#define BPORT1_AB_ERR_ERR25             (0x1 << 25)
#define BPORT1_AB_ERR_ERR25_GET(_v)     ((_v >> 25) & 0x1)
#define BPORT1_AB_ERR_ERR26             (0x1 << 26)
#define BPORT1_AB_ERR_ERR26_GET(_v)     ((_v >> 26) & 0x1)
#define BPORT1_AB_ERR_ERR27             (0x1 << 27)
#define BPORT1_AB_ERR_ERR27_GET(_v)     ((_v >> 27) & 0x1)
#define BPORT1_AB_ERR_ERR28             (0x1 << 28)
#define BPORT1_AB_ERR_ERR28_GET(_v)     ((_v >> 28) & 0x1)
#define BPORT1_AB_ERR_ERR29             (0x1 << 29)
#define BPORT1_AB_ERR_ERR29_GET(_v)     ((_v >> 29) & 0x1)
#define BPORT1_AB_ERR_ERR3              (0x1 << 3)
#define BPORT1_AB_ERR_ERR3_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_ERR_ERR30             (0x1 << 30)
#define BPORT1_AB_ERR_ERR30_GET(_v)     ((_v >> 30) & 0x1)
#define BPORT1_AB_ERR_ERR31             (0x1 << 31)
#define BPORT1_AB_ERR_ERR31_GET(_v)     ((_v >> 31) & 0x1)
#define BPORT1_AB_ERR_ERR4              (0x1 << 4)
#define BPORT1_AB_ERR_ERR4_GET(_v)      ((_v >> 4) & 0x1)
#define BPORT1_AB_ERR_ERR5              (0x1 << 5)
#define BPORT1_AB_ERR_ERR5_GET(_v)      ((_v >> 5) & 0x1)
#define BPORT1_AB_ERR_ERR6              (0x1 << 6)
#define BPORT1_AB_ERR_ERR6_GET(_v)      ((_v >> 6) & 0x1)
#define BPORT1_AB_ERR_ERR7              (0x1 << 7)
#define BPORT1_AB_ERR_ERR7_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_ERR_ERR8              (0x1 << 8)
#define BPORT1_AB_ERR_ERR8_GET(_v)      ((_v >> 8) & 0x1)
#define BPORT1_AB_ERR_ERR9              (0x1 << 9)
#define BPORT1_AB_ERR_ERR9_GET(_v)      ((_v >> 9) & 0x1)

#define BPORT1_AB_HRS_POFFSET           0x34
#define BPORT1_AB_HRS                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HRS_POFFSET)
#define BPORT1_AB_HRS_HRS0              0x1
#define BPORT1_AB_HRS_HRS0_GET(_v)      (_v & 0x1)
#define BPORT1_AB_HRS_HRS1              (0x1 << 1)
#define BPORT1_AB_HRS_HRS1_GET(_v)      ((_v >> 1) & 0x1)
#define BPORT1_AB_HRS_HRS10             (0x1 << 10)
#define BPORT1_AB_HRS_HRS10_GET(_v)     ((_v >> 10) & 0x1)
#define BPORT1_AB_HRS_HRS11             (0x1 << 11)
#define BPORT1_AB_HRS_HRS11_GET(_v)     ((_v >> 11) & 0x1)
#define BPORT1_AB_HRS_HRS12             (0x1 << 12)
#define BPORT1_AB_HRS_HRS12_GET(_v)     ((_v >> 12) & 0x1)
#define BPORT1_AB_HRS_HRS13             (0x1 << 13)
#define BPORT1_AB_HRS_HRS13_GET(_v)     ((_v >> 13) & 0x1)
#define BPORT1_AB_HRS_HRS14             (0x1 << 14)
#define BPORT1_AB_HRS_HRS14_GET(_v)     ((_v >> 14) & 0x1)
#define BPORT1_AB_HRS_HRS15             (0x1 << 15)
#define BPORT1_AB_HRS_HRS15_GET(_v)     ((_v >> 15) & 0x1)
#define BPORT1_AB_HRS_HRS16             (0x1 << 16)
#define BPORT1_AB_HRS_HRS16_GET(_v)     ((_v >> 16) & 0x1)
#define BPORT1_AB_HRS_HRS17             (0x1 << 17)
#define BPORT1_AB_HRS_HRS17_GET(_v)     ((_v >> 17) & 0x1)
#define BPORT1_AB_HRS_HRS18             (0x1 << 18)
#define BPORT1_AB_HRS_HRS18_GET(_v)     ((_v >> 18) & 0x1)
#define BPORT1_AB_HRS_HRS19             (0x1 << 19)
#define BPORT1_AB_HRS_HRS19_GET(_v)     ((_v >> 19) & 0x1)
#define BPORT1_AB_HRS_HRS2              (0x1 << 2)
#define BPORT1_AB_HRS_HRS2_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_HRS_HRS20             (0x1 << 20)
#define BPORT1_AB_HRS_HRS20_GET(_v)     ((_v >> 20) & 0x1)
#define BPORT1_AB_HRS_HRS21             (0x1 << 21)
#define BPORT1_AB_HRS_HRS21_GET(_v)     ((_v >> 21) & 0x1)
#define BPORT1_AB_HRS_HRS22             (0x1 << 22)
#define BPORT1_AB_HRS_HRS22_GET(_v)     ((_v >> 22) & 0x1)
#define BPORT1_AB_HRS_HRS23             (0x1 << 23)
#define BPORT1_AB_HRS_HRS23_GET(_v)     ((_v >> 23) & 0x1)
#define BPORT1_AB_HRS_HRS24             (0x1 << 24)
#define BPORT1_AB_HRS_HRS24_GET(_v)     ((_v >> 24) & 0x1)
#define BPORT1_AB_HRS_HRS25             (0x1 << 25)
#define BPORT1_AB_HRS_HRS25_GET(_v)     ((_v >> 25) & 0x1)
#define BPORT1_AB_HRS_HRS26             (0x1 << 26)
#define BPORT1_AB_HRS_HRS26_GET(_v)     ((_v >> 26) & 0x1)
#define BPORT1_AB_HRS_HRS27             (0x1 << 27)
#define BPORT1_AB_HRS_HRS27_GET(_v)     ((_v >> 27) & 0x1)
#define BPORT1_AB_HRS_HRS28             (0x1 << 28)
#define BPORT1_AB_HRS_HRS28_GET(_v)     ((_v >> 28) & 0x1)
#define BPORT1_AB_HRS_HRS29             (0x1 << 29)
#define BPORT1_AB_HRS_HRS29_GET(_v)     ((_v >> 29) & 0x1)
#define BPORT1_AB_HRS_HRS3              (0x1 << 3)
#define BPORT1_AB_HRS_HRS3_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_HRS_HRS30             (0x1 << 30)
#define BPORT1_AB_HRS_HRS30_GET(_v)     ((_v >> 30) & 0x1)
#define BPORT1_AB_HRS_HRS31             (0x1 << 31)
#define BPORT1_AB_HRS_HRS31_GET(_v)     ((_v >> 31) & 0x1)
#define BPORT1_AB_HRS_HRS4              (0x1 << 4)
#define BPORT1_AB_HRS_HRS4_GET(_v)      ((_v >> 4) & 0x1)
#define BPORT1_AB_HRS_HRS5              (0x1 << 5)
#define BPORT1_AB_HRS_HRS5_GET(_v)      ((_v >> 5) & 0x1)
#define BPORT1_AB_HRS_HRS6              (0x1 << 6)
#define BPORT1_AB_HRS_HRS6_GET(_v)      ((_v >> 6) & 0x1)
#define BPORT1_AB_HRS_HRS7              (0x1 << 7)
#define BPORT1_AB_HRS_HRS7_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_HRS_HRS8              (0x1 << 8)
#define BPORT1_AB_HRS_HRS8_GET(_v)      ((_v >> 8) & 0x1)
#define BPORT1_AB_HRS_HRS9              (0x1 << 9)
#define BPORT1_AB_HRS_HRS9_GET(_v)      ((_v >> 9) & 0x1)

#define BPORT1_AB_EARS_POFFSET          0x44
#define BPORT1_AB_EARS                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EARS_POFFSET)
#define BPORT1_AB_EARS_EDREQ_0          0x1
#define BPORT1_AB_EARS_EDREQ_0_GET(_v)  (_v & 0x1)
#define BPORT1_AB_EARS_EDREQ_1          (0x1 << 1)
#define BPORT1_AB_EARS_EDREQ_1_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_EARS_EDREQ_10         (0x1 << 10)
#define BPORT1_AB_EARS_EDREQ_10_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_EARS_EDREQ_11         (0x1 << 11)
#define BPORT1_AB_EARS_EDREQ_11_GET(_v)  ((_v >> 11) & 0x1)
#define BPORT1_AB_EARS_EDREQ_12         (0x1 << 12)
#define BPORT1_AB_EARS_EDREQ_12_GET(_v)  ((_v >> 12) & 0x1)
#define BPORT1_AB_EARS_EDREQ_13         (0x1 << 13)
#define BPORT1_AB_EARS_EDREQ_13_GET(_v)  ((_v >> 13) & 0x1)
#define BPORT1_AB_EARS_EDREQ_14         (0x1 << 14)
#define BPORT1_AB_EARS_EDREQ_14_GET(_v)  ((_v >> 14) & 0x1)
#define BPORT1_AB_EARS_EDREQ_15         (0x1 << 15)
#define BPORT1_AB_EARS_EDREQ_15_GET(_v)  ((_v >> 15) & 0x1)
#define BPORT1_AB_EARS_EDREQ_16         (0x1 << 16)
#define BPORT1_AB_EARS_EDREQ_16_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_EARS_EDREQ_17         (0x1 << 17)
#define BPORT1_AB_EARS_EDREQ_17_GET(_v)  ((_v >> 17) & 0x1)
#define BPORT1_AB_EARS_EDREQ_18         (0x1 << 18)
#define BPORT1_AB_EARS_EDREQ_18_GET(_v)  ((_v >> 18) & 0x1)
#define BPORT1_AB_EARS_EDREQ_19         (0x1 << 19)
#define BPORT1_AB_EARS_EDREQ_19_GET(_v)  ((_v >> 19) & 0x1)
#define BPORT1_AB_EARS_EDREQ_2          (0x1 << 2)
#define BPORT1_AB_EARS_EDREQ_2_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_EARS_EDREQ_20         (0x1 << 20)
#define BPORT1_AB_EARS_EDREQ_20_GET(_v)  ((_v >> 20) & 0x1)
#define BPORT1_AB_EARS_EDREQ_21         (0x1 << 21)
#define BPORT1_AB_EARS_EDREQ_21_GET(_v)  ((_v >> 21) & 0x1)
#define BPORT1_AB_EARS_EDREQ_22         (0x1 << 22)
#define BPORT1_AB_EARS_EDREQ_22_GET(_v)  ((_v >> 22) & 0x1)
#define BPORT1_AB_EARS_EDREQ_23         (0x1 << 23)
#define BPORT1_AB_EARS_EDREQ_23_GET(_v)  ((_v >> 23) & 0x1)
#define BPORT1_AB_EARS_EDREQ_24         (0x1 << 24)
#define BPORT1_AB_EARS_EDREQ_24_GET(_v)  ((_v >> 24) & 0x1)
#define BPORT1_AB_EARS_EDREQ_25         (0x1 << 25)
#define BPORT1_AB_EARS_EDREQ_25_GET(_v)  ((_v >> 25) & 0x1)
#define BPORT1_AB_EARS_EDREQ_26         (0x1 << 26)
#define BPORT1_AB_EARS_EDREQ_26_GET(_v)  ((_v >> 26) & 0x1)
#define BPORT1_AB_EARS_EDREQ_27         (0x1 << 27)
#define BPORT1_AB_EARS_EDREQ_27_GET(_v)  ((_v >> 27) & 0x1)
#define BPORT1_AB_EARS_EDREQ_28         (0x1 << 28)
#define BPORT1_AB_EARS_EDREQ_28_GET(_v)  ((_v >> 28) & 0x1)
#define BPORT1_AB_EARS_EDREQ_29         (0x1 << 29)
#define BPORT1_AB_EARS_EDREQ_29_GET(_v)  ((_v >> 29) & 0x1)
#define BPORT1_AB_EARS_EDREQ_3          (0x1 << 3)
#define BPORT1_AB_EARS_EDREQ_3_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_EARS_EDREQ_30         (0x1 << 30)
#define BPORT1_AB_EARS_EDREQ_30_GET(_v)  ((_v >> 30) & 0x1)
#define BPORT1_AB_EARS_EDREQ_31         (0x1 << 31)
#define BPORT1_AB_EARS_EDREQ_31_GET(_v)  ((_v >> 31) & 0x1)
#define BPORT1_AB_EARS_EDREQ_4          (0x1 << 4)
#define BPORT1_AB_EARS_EDREQ_4_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_EARS_EDREQ_5          (0x1 << 5)
#define BPORT1_AB_EARS_EDREQ_5_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_EARS_EDREQ_6          (0x1 << 6)
#define BPORT1_AB_EARS_EDREQ_6_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_EARS_EDREQ_7          (0x1 << 7)
#define BPORT1_AB_EARS_EDREQ_7_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_EARS_EDREQ_8          (0x1 << 8)
#define BPORT1_AB_EARS_EDREQ_8_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_EARS_EDREQ_9          (0x1 << 9)
#define BPORT1_AB_EARS_EDREQ_9_GET(_v)  ((_v >> 9) & 0x1)

#define BPORT1_AB_DCHPRI3_0_POFFSET     0x100
#define BPORT1_AB_DCHPRI3_0             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DCHPRI3_0_POFFSET)

#define BPORT1_AB_DCHPRI7_4_POFFSET     0x104
#define BPORT1_AB_DCHPRI7_4             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DCHPRI7_4_POFFSET)

#define BPORT1_AB_DCHPRI11_8_POFFSET    0x108
#define BPORT1_AB_DCHPRI11_8            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DCHPRI11_8_POFFSET)

#define BPORT1_AB_DCHPRI15_12_POFFSET   0x10c
#define BPORT1_AB_DCHPRI15_12           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DCHPRI15_12_POFFSET)

#define BPORT1_AB_DCHPRI19_16_POFFSET   0x110
#define BPORT1_AB_DCHPRI19_16           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DCHPRI19_16_POFFSET)

#define BPORT1_AB_DCHPRI23_20_POFFSET   0x114
#define BPORT1_AB_DCHPRI23_20           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DCHPRI23_20_POFFSET)

#define BPORT1_AB_DCHPRI27_24_POFFSET   0x118
#define BPORT1_AB_DCHPRI27_24           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DCHPRI27_24_POFFSET)

#define BPORT1_AB_DCHPRI31_28_POFFSET   0x11c
#define BPORT1_AB_DCHPRI31_28           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DCHPRI31_28_POFFSET)

#define BPORT1_AB_TCD0_SADDR_POFFSET    0x1000
#define BPORT1_AB_TCD0_SADDR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD0_SADDR_POFFSET)

#define BPORT1_AB_TCD0_SOFF_ATTR_POFFSET  0x1004
#define BPORT1_AB_TCD0_SOFF_ATTR        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD0_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD0_NBYTES_POFFSET   0x1008
#define BPORT1_AB_TCD0_NBYTES           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD0_NBYTES_POFFSET)

#define BPORT1_AB_TCD0_SLAST_POFFSET    0x100c
#define BPORT1_AB_TCD0_SLAST            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD0_SLAST_POFFSET)

#define BPORT1_AB_TCD0_DADDR_POFFSET    0x1010
#define BPORT1_AB_TCD0_DADDR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD0_DADDR_POFFSET)

#define BPORT1_AB_TCD0_DOFF_CITER_POFFSET  0x1014
#define BPORT1_AB_TCD0_DOFF_CITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD0_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD0_DLASTSGA_POFFSET  0x1018
#define BPORT1_AB_TCD0_DLASTSGA         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD0_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD0_CSR_BITER_POFFSET  0x101c
#define BPORT1_AB_TCD0_CSR_BITER        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD0_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD1_SADDR_POFFSET    0x1020
#define BPORT1_AB_TCD1_SADDR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD1_SADDR_POFFSET)

#define BPORT1_AB_TCD1_SOFF_ATTR_POFFSET  0x1024
#define BPORT1_AB_TCD1_SOFF_ATTR        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD1_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD1_NBYTES_POFFSET   0x1028
#define BPORT1_AB_TCD1_NBYTES           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD1_NBYTES_POFFSET)

#define BPORT1_AB_TCD1_SLAST_POFFSET    0x102c
#define BPORT1_AB_TCD1_SLAST            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD1_SLAST_POFFSET)

#define BPORT1_AB_TCD1_DADDR_POFFSET    0x1030
#define BPORT1_AB_TCD1_DADDR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD1_DADDR_POFFSET)

#define BPORT1_AB_TCD1_DOFF_CITER_POFFSET  0x1034
#define BPORT1_AB_TCD1_DOFF_CITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD1_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD1_DLASTSGA_POFFSET  0x1038
#define BPORT1_AB_TCD1_DLASTSGA         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD1_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD1_CSR_BITER_POFFSET  0x103c
#define BPORT1_AB_TCD1_CSR_BITER        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD1_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD2_SADDR_POFFSET    0x1040
#define BPORT1_AB_TCD2_SADDR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD2_SADDR_POFFSET)

#define BPORT1_AB_TCD2_SOFF_ATTR_POFFSET  0x1044
#define BPORT1_AB_TCD2_SOFF_ATTR        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD2_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD2_NBYTES_POFFSET   0x1048
#define BPORT1_AB_TCD2_NBYTES           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD2_NBYTES_POFFSET)

#define BPORT1_AB_TCD2_SLAST_POFFSET    0x104c
#define BPORT1_AB_TCD2_SLAST            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD2_SLAST_POFFSET)

#define BPORT1_AB_TCD2_DADDR_POFFSET    0x1050
#define BPORT1_AB_TCD2_DADDR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD2_DADDR_POFFSET)

#define BPORT1_AB_TCD2_DOFF_CITER_POFFSET  0x1054
#define BPORT1_AB_TCD2_DOFF_CITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD2_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD2_DLASTSGA_POFFSET  0x1058
#define BPORT1_AB_TCD2_DLASTSGA         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD2_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD2_CSR_BITER_POFFSET  0x105c
#define BPORT1_AB_TCD2_CSR_BITER        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD2_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD3_SADDR_POFFSET    0x1060
#define BPORT1_AB_TCD3_SADDR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD3_SADDR_POFFSET)

#define BPORT1_AB_TCD3_SOFF_ATTR_POFFSET  0x1064
#define BPORT1_AB_TCD3_SOFF_ATTR        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD3_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD3_NBYTES_POFFSET   0x1068
#define BPORT1_AB_TCD3_NBYTES           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD3_NBYTES_POFFSET)

#define BPORT1_AB_TCD3_SLAST_POFFSET    0x106c
#define BPORT1_AB_TCD3_SLAST            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD3_SLAST_POFFSET)

#define BPORT1_AB_TCD3_DADDR_POFFSET    0x1070
#define BPORT1_AB_TCD3_DADDR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD3_DADDR_POFFSET)

#define BPORT1_AB_TCD3_DOFF_CITER_POFFSET  0x1074
#define BPORT1_AB_TCD3_DOFF_CITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD3_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD3_DLASTSGA_POFFSET  0x1078
#define BPORT1_AB_TCD3_DLASTSGA         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD3_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD3_CSR_BITER_POFFSET  0x107c
#define BPORT1_AB_TCD3_CSR_BITER        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD3_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD4_SADDR_POFFSET    0x1080
#define BPORT1_AB_TCD4_SADDR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD4_SADDR_POFFSET)

#define BPORT1_AB_TCD4_SOFF_ATTR_POFFSET  0x1084
#define BPORT1_AB_TCD4_SOFF_ATTR        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD4_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD4_NBYTES_POFFSET   0x1088
#define BPORT1_AB_TCD4_NBYTES           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD4_NBYTES_POFFSET)

#define BPORT1_AB_TCD4_SLAST_POFFSET    0x108c
#define BPORT1_AB_TCD4_SLAST            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD4_SLAST_POFFSET)

#define BPORT1_AB_TCD4_DADDR_POFFSET    0x1090
#define BPORT1_AB_TCD4_DADDR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD4_DADDR_POFFSET)

#define BPORT1_AB_TCD4_DOFF_CITER_POFFSET  0x1094
#define BPORT1_AB_TCD4_DOFF_CITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD4_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD4_DLASTSGA_POFFSET  0x1098
#define BPORT1_AB_TCD4_DLASTSGA         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD4_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD4_CSR_BITER_POFFSET  0x109c
#define BPORT1_AB_TCD4_CSR_BITER        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD4_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD5_SADDR_POFFSET    0x10a0
#define BPORT1_AB_TCD5_SADDR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD5_SADDR_POFFSET)

#define BPORT1_AB_TCD5_SOFF_ATTR_POFFSET  0x10a4
#define BPORT1_AB_TCD5_SOFF_ATTR        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD5_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD5_NBYTES_POFFSET   0x10a8
#define BPORT1_AB_TCD5_NBYTES           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD5_NBYTES_POFFSET)

#define BPORT1_AB_TCD5_SLAST_POFFSET    0x10ac
#define BPORT1_AB_TCD5_SLAST            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD5_SLAST_POFFSET)

#define BPORT1_AB_TCD5_DADDR_POFFSET    0x10b0
#define BPORT1_AB_TCD5_DADDR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD5_DADDR_POFFSET)

#define BPORT1_AB_TCD5_DOFF_CITER_POFFSET  0x10b4
#define BPORT1_AB_TCD5_DOFF_CITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD5_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD5_DLASTSGA_POFFSET  0x10b8
#define BPORT1_AB_TCD5_DLASTSGA         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD5_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD5_CSR_BITER_POFFSET  0x10bc
#define BPORT1_AB_TCD5_CSR_BITER        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD5_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD6_SADDR_POFFSET    0x10c0
#define BPORT1_AB_TCD6_SADDR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD6_SADDR_POFFSET)

#define BPORT1_AB_TCD6_SOFF_ATTR_POFFSET  0x10c4
#define BPORT1_AB_TCD6_SOFF_ATTR        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD6_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD6_NBYTES_POFFSET   0x10c8
#define BPORT1_AB_TCD6_NBYTES           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD6_NBYTES_POFFSET)

#define BPORT1_AB_TCD6_SLAST_POFFSET    0x10cc
#define BPORT1_AB_TCD6_SLAST            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD6_SLAST_POFFSET)

#define BPORT1_AB_TCD6_DADDR_POFFSET    0x10d0
#define BPORT1_AB_TCD6_DADDR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD6_DADDR_POFFSET)

#define BPORT1_AB_TCD6_DOFF_CITER_POFFSET  0x10d4
#define BPORT1_AB_TCD6_DOFF_CITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD6_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD6_DLASTSGA_POFFSET  0x10d8
#define BPORT1_AB_TCD6_DLASTSGA         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD6_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD6_CSR_BITER_POFFSET  0x10dc
#define BPORT1_AB_TCD6_CSR_BITER        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD6_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD7_SADDR_POFFSET    0x10e0
#define BPORT1_AB_TCD7_SADDR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD7_SADDR_POFFSET)

#define BPORT1_AB_TCD7_SOFF_ATTR_POFFSET  0x10e4
#define BPORT1_AB_TCD7_SOFF_ATTR        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD7_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD7_NBYTES_POFFSET   0x10e8
#define BPORT1_AB_TCD7_NBYTES           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD7_NBYTES_POFFSET)

#define BPORT1_AB_TCD7_SLAST_POFFSET    0x10ec
#define BPORT1_AB_TCD7_SLAST            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD7_SLAST_POFFSET)

#define BPORT1_AB_TCD7_DADDR_POFFSET    0x10f0
#define BPORT1_AB_TCD7_DADDR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD7_DADDR_POFFSET)

#define BPORT1_AB_TCD7_DOFF_CITER_POFFSET  0x10f4
#define BPORT1_AB_TCD7_DOFF_CITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD7_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD7_DLASTSGA_POFFSET  0x10f8
#define BPORT1_AB_TCD7_DLASTSGA         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD7_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD7_CSR_BITER_POFFSET  0x10fc
#define BPORT1_AB_TCD7_CSR_BITER        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD7_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD8_SADDR_POFFSET    0x1100
#define BPORT1_AB_TCD8_SADDR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD8_SADDR_POFFSET)

#define BPORT1_AB_TCD8_SOFF_ATTR_POFFSET  0x1104
#define BPORT1_AB_TCD8_SOFF_ATTR        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD8_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD8_NBYTES_POFFSET   0x1108
#define BPORT1_AB_TCD8_NBYTES           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD8_NBYTES_POFFSET)

#define BPORT1_AB_TCD8_SLAST_POFFSET    0x110c
#define BPORT1_AB_TCD8_SLAST            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD8_SLAST_POFFSET)

#define BPORT1_AB_TCD8_DADDR_POFFSET    0x1110
#define BPORT1_AB_TCD8_DADDR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD8_DADDR_POFFSET)

#define BPORT1_AB_TCD8_DOFF_CITER_POFFSET  0x1114
#define BPORT1_AB_TCD8_DOFF_CITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD8_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD8_DLASTSGA_POFFSET  0x1118
#define BPORT1_AB_TCD8_DLASTSGA         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD8_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD8_CSR_BITER_POFFSET  0x111c
#define BPORT1_AB_TCD8_CSR_BITER        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD8_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD9_SADDR_POFFSET    0x1120
#define BPORT1_AB_TCD9_SADDR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD9_SADDR_POFFSET)

#define BPORT1_AB_TCD9_SOFF_ATTR_POFFSET  0x1124
#define BPORT1_AB_TCD9_SOFF_ATTR        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD9_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD9_NBYTES_POFFSET   0x1128
#define BPORT1_AB_TCD9_NBYTES           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD9_NBYTES_POFFSET)

#define BPORT1_AB_TCD9_SLAST_POFFSET    0x112c
#define BPORT1_AB_TCD9_SLAST            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD9_SLAST_POFFSET)

#define BPORT1_AB_TCD9_DADDR_POFFSET    0x1130
#define BPORT1_AB_TCD9_DADDR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD9_DADDR_POFFSET)

#define BPORT1_AB_TCD9_DOFF_CITER_POFFSET  0x1134
#define BPORT1_AB_TCD9_DOFF_CITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD9_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD9_DLASTSGA_POFFSET  0x1138
#define BPORT1_AB_TCD9_DLASTSGA         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD9_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD9_CSR_BITER_POFFSET  0x113c
#define BPORT1_AB_TCD9_CSR_BITER        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD9_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD10_SADDR_POFFSET   0x1140
#define BPORT1_AB_TCD10_SADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD10_SADDR_POFFSET)

#define BPORT1_AB_TCD10_SOFF_ATTR_POFFSET  0x1144
#define BPORT1_AB_TCD10_SOFF_ATTR       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD10_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD10_NBYTES_POFFSET  0x1148
#define BPORT1_AB_TCD10_NBYTES          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD10_NBYTES_POFFSET)

#define BPORT1_AB_TCD10_SLAST_POFFSET   0x114c
#define BPORT1_AB_TCD10_SLAST           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD10_SLAST_POFFSET)

#define BPORT1_AB_TCD10_DADDR_POFFSET   0x1150
#define BPORT1_AB_TCD10_DADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD10_DADDR_POFFSET)

#define BPORT1_AB_TCD10_DOFF_CITER_POFFSET  0x1154
#define BPORT1_AB_TCD10_DOFF_CITER      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD10_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD10_DLASTSGA_POFFSET  0x1158
#define BPORT1_AB_TCD10_DLASTSGA        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD10_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD10_CSR_BITER_POFFSET  0x115c
#define BPORT1_AB_TCD10_CSR_BITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD10_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD11_SADDR_POFFSET   0x1160
#define BPORT1_AB_TCD11_SADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD11_SADDR_POFFSET)

#define BPORT1_AB_TCD11_SOFF_ATTR_POFFSET  0x1164
#define BPORT1_AB_TCD11_SOFF_ATTR       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD11_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD11_NBYTES_POFFSET  0x1168
#define BPORT1_AB_TCD11_NBYTES          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD11_NBYTES_POFFSET)

#define BPORT1_AB_TCD11_SLAST_POFFSET   0x116c
#define BPORT1_AB_TCD11_SLAST           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD11_SLAST_POFFSET)

#define BPORT1_AB_TCD11_DADDR_POFFSET   0x1170
#define BPORT1_AB_TCD11_DADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD11_DADDR_POFFSET)

#define BPORT1_AB_TCD11_DOFF_CITER_POFFSET  0x1174
#define BPORT1_AB_TCD11_DOFF_CITER      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD11_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD11_DLASTSGA_POFFSET  0x1178
#define BPORT1_AB_TCD11_DLASTSGA        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD11_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD11_CSR_BITER_POFFSET  0x117c
#define BPORT1_AB_TCD11_CSR_BITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD11_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD12_SADDR_POFFSET   0x1180
#define BPORT1_AB_TCD12_SADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD12_SADDR_POFFSET)

#define BPORT1_AB_TCD12_SOFF_ATTR_POFFSET  0x1184
#define BPORT1_AB_TCD12_SOFF_ATTR       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD12_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD12_NBYTES_POFFSET  0x1188
#define BPORT1_AB_TCD12_NBYTES          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD12_NBYTES_POFFSET)

#define BPORT1_AB_TCD12_SLAST_POFFSET   0x118c
#define BPORT1_AB_TCD12_SLAST           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD12_SLAST_POFFSET)

#define BPORT1_AB_TCD12_DADDR_POFFSET   0x1190
#define BPORT1_AB_TCD12_DADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD12_DADDR_POFFSET)

#define BPORT1_AB_TCD12_DOFF_CITER_POFFSET  0x1194
#define BPORT1_AB_TCD12_DOFF_CITER      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD12_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD12_DLASTSGA_POFFSET  0x1198
#define BPORT1_AB_TCD12_DLASTSGA        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD12_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD12_CSR_BITER_POFFSET  0x119c
#define BPORT1_AB_TCD12_CSR_BITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD12_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD13_SADDR_POFFSET   0x11a0
#define BPORT1_AB_TCD13_SADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD13_SADDR_POFFSET)

#define BPORT1_AB_TCD13_SOFF_ATTR_POFFSET  0x11a4
#define BPORT1_AB_TCD13_SOFF_ATTR       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD13_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD13_NBYTES_POFFSET  0x11a8
#define BPORT1_AB_TCD13_NBYTES          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD13_NBYTES_POFFSET)

#define BPORT1_AB_TCD13_SLAST_POFFSET   0x11ac
#define BPORT1_AB_TCD13_SLAST           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD13_SLAST_POFFSET)

#define BPORT1_AB_TCD13_DADDR_POFFSET   0x11b0
#define BPORT1_AB_TCD13_DADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD13_DADDR_POFFSET)

#define BPORT1_AB_TCD13_DOFF_CITER_POFFSET  0x11b4
#define BPORT1_AB_TCD13_DOFF_CITER      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD13_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD13_DLASTSGA_POFFSET  0x11b8
#define BPORT1_AB_TCD13_DLASTSGA        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD13_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD13_CSR_BITER_POFFSET  0x11bc
#define BPORT1_AB_TCD13_CSR_BITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD13_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD14_SADDR_POFFSET   0x11c0
#define BPORT1_AB_TCD14_SADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD14_SADDR_POFFSET)

#define BPORT1_AB_TCD14_SOFF_ATTR_POFFSET  0x11c4
#define BPORT1_AB_TCD14_SOFF_ATTR       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD14_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD14_NBYTES_POFFSET  0x11c8
#define BPORT1_AB_TCD14_NBYTES          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD14_NBYTES_POFFSET)

#define BPORT1_AB_TCD14_SLAST_POFFSET   0x11cc
#define BPORT1_AB_TCD14_SLAST           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD14_SLAST_POFFSET)

#define BPORT1_AB_TCD14_DADDR_POFFSET   0x11d0
#define BPORT1_AB_TCD14_DADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD14_DADDR_POFFSET)

#define BPORT1_AB_TCD14_DOFF_CITER_POFFSET  0x11d4
#define BPORT1_AB_TCD14_DOFF_CITER      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD14_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD14_DLASTSGA_POFFSET  0x11d8
#define BPORT1_AB_TCD14_DLASTSGA        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD14_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD14_CSR_BITER_POFFSET  0x11dc
#define BPORT1_AB_TCD14_CSR_BITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD14_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD15_SADDR_POFFSET   0x11e0
#define BPORT1_AB_TCD15_SADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD15_SADDR_POFFSET)

#define BPORT1_AB_TCD15_SOFF_ATTR_POFFSET  0x11e4
#define BPORT1_AB_TCD15_SOFF_ATTR       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD15_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD15_NBYTES_POFFSET  0x11e8
#define BPORT1_AB_TCD15_NBYTES          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD15_NBYTES_POFFSET)

#define BPORT1_AB_TCD15_SLAST_POFFSET   0x11ec
#define BPORT1_AB_TCD15_SLAST           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD15_SLAST_POFFSET)

#define BPORT1_AB_TCD15_DADDR_POFFSET   0x11f0
#define BPORT1_AB_TCD15_DADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD15_DADDR_POFFSET)

#define BPORT1_AB_TCD15_DOFF_CITER_POFFSET  0x11f4
#define BPORT1_AB_TCD15_DOFF_CITER      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD15_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD15_DLASTSGA_POFFSET  0x11f8
#define BPORT1_AB_TCD15_DLASTSGA        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD15_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD15_CSR_BITER_POFFSET  0x11fc
#define BPORT1_AB_TCD15_CSR_BITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD15_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD16_SADDR_POFFSET   0x1200
#define BPORT1_AB_TCD16_SADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD16_SADDR_POFFSET)

#define BPORT1_AB_TCD16_SOFF_ATTR_POFFSET  0x1204
#define BPORT1_AB_TCD16_SOFF_ATTR       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD16_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD16_NBYTES_POFFSET  0x1208
#define BPORT1_AB_TCD16_NBYTES          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD16_NBYTES_POFFSET)

#define BPORT1_AB_TCD16_SLAST_POFFSET   0x120c
#define BPORT1_AB_TCD16_SLAST           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD16_SLAST_POFFSET)

#define BPORT1_AB_TCD16_DADDR_POFFSET   0x1210
#define BPORT1_AB_TCD16_DADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD16_DADDR_POFFSET)

#define BPORT1_AB_TCD16_DOFF_CITER_POFFSET  0x1214
#define BPORT1_AB_TCD16_DOFF_CITER      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD16_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD16_DLASTSGA_POFFSET  0x1218
#define BPORT1_AB_TCD16_DLASTSGA        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD16_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD16_CSR_BITER_POFFSET  0x121c
#define BPORT1_AB_TCD16_CSR_BITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD16_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD17_SADDR_POFFSET   0x1220
#define BPORT1_AB_TCD17_SADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD17_SADDR_POFFSET)

#define BPORT1_AB_TCD17_SOFF_ATTR_POFFSET  0x1224
#define BPORT1_AB_TCD17_SOFF_ATTR       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD17_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD17_NBYTES_POFFSET  0x1228
#define BPORT1_AB_TCD17_NBYTES          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD17_NBYTES_POFFSET)

#define BPORT1_AB_TCD17_SLAST_POFFSET   0x122c
#define BPORT1_AB_TCD17_SLAST           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD17_SLAST_POFFSET)

#define BPORT1_AB_TCD17_DADDR_POFFSET   0x1230
#define BPORT1_AB_TCD17_DADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD17_DADDR_POFFSET)

#define BPORT1_AB_TCD17_DOFF_CITER_POFFSET  0x1234
#define BPORT1_AB_TCD17_DOFF_CITER      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD17_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD17_DLASTSGA_POFFSET  0x1238
#define BPORT1_AB_TCD17_DLASTSGA        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD17_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD17_CSR_BITER_POFFSET  0x123c
#define BPORT1_AB_TCD17_CSR_BITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD17_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD18_SADDR_POFFSET   0x1240
#define BPORT1_AB_TCD18_SADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD18_SADDR_POFFSET)

#define BPORT1_AB_TCD18_SOFF_ATTR_POFFSET  0x1244
#define BPORT1_AB_TCD18_SOFF_ATTR       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD18_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD18_NBYTES_POFFSET  0x1248
#define BPORT1_AB_TCD18_NBYTES          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD18_NBYTES_POFFSET)

#define BPORT1_AB_TCD18_SLAST_POFFSET   0x124c
#define BPORT1_AB_TCD18_SLAST           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD18_SLAST_POFFSET)

#define BPORT1_AB_TCD18_DADDR_POFFSET   0x1250
#define BPORT1_AB_TCD18_DADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD18_DADDR_POFFSET)

#define BPORT1_AB_TCD18_DOFF_CITER_POFFSET  0x1254
#define BPORT1_AB_TCD18_DOFF_CITER      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD18_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD18_DLASTSGA_POFFSET  0x1258
#define BPORT1_AB_TCD18_DLASTSGA        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD18_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD18_CSR_BITER_POFFSET  0x125c
#define BPORT1_AB_TCD18_CSR_BITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD18_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD19_SADDR_POFFSET   0x1260
#define BPORT1_AB_TCD19_SADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD19_SADDR_POFFSET)

#define BPORT1_AB_TCD19_SOFF_ATTR_POFFSET  0x1264
#define BPORT1_AB_TCD19_SOFF_ATTR       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD19_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD19_NBYTES_POFFSET  0x1268
#define BPORT1_AB_TCD19_NBYTES          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD19_NBYTES_POFFSET)

#define BPORT1_AB_TCD19_SLAST_POFFSET   0x126c
#define BPORT1_AB_TCD19_SLAST           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD19_SLAST_POFFSET)

#define BPORT1_AB_TCD19_DADDR_POFFSET   0x1270
#define BPORT1_AB_TCD19_DADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD19_DADDR_POFFSET)

#define BPORT1_AB_TCD19_DOFF_CITER_POFFSET  0x1274
#define BPORT1_AB_TCD19_DOFF_CITER      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD19_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD19_DLASTSGA_POFFSET  0x1278
#define BPORT1_AB_TCD19_DLASTSGA        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD19_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD19_CSR_BITER_POFFSET  0x127c
#define BPORT1_AB_TCD19_CSR_BITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD19_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD20_SADDR_POFFSET   0x1280
#define BPORT1_AB_TCD20_SADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD20_SADDR_POFFSET)

#define BPORT1_AB_TCD20_SOFF_ATTR_POFFSET  0x1284
#define BPORT1_AB_TCD20_SOFF_ATTR       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD20_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD20_NBYTES_POFFSET  0x1288
#define BPORT1_AB_TCD20_NBYTES          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD20_NBYTES_POFFSET)

#define BPORT1_AB_TCD20_SLAST_POFFSET   0x128c
#define BPORT1_AB_TCD20_SLAST           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD20_SLAST_POFFSET)

#define BPORT1_AB_TCD20_DADDR_POFFSET   0x1290
#define BPORT1_AB_TCD20_DADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD20_DADDR_POFFSET)

#define BPORT1_AB_TCD20_DOFF_CITER_POFFSET  0x1294
#define BPORT1_AB_TCD20_DOFF_CITER      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD20_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD20_DLASTSGA_POFFSET  0x1298
#define BPORT1_AB_TCD20_DLASTSGA        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD20_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD20_CSR_BITER_POFFSET  0x129c
#define BPORT1_AB_TCD20_CSR_BITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD20_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD21_SADDR_POFFSET   0x12a0
#define BPORT1_AB_TCD21_SADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD21_SADDR_POFFSET)

#define BPORT1_AB_TCD21_SOFF_ATTR_POFFSET  0x12a4
#define BPORT1_AB_TCD21_SOFF_ATTR       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD21_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD21_NBYTES_POFFSET  0x12a8
#define BPORT1_AB_TCD21_NBYTES          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD21_NBYTES_POFFSET)

#define BPORT1_AB_TCD21_SLAST_POFFSET   0x12ac
#define BPORT1_AB_TCD21_SLAST           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD21_SLAST_POFFSET)

#define BPORT1_AB_TCD21_DADDR_POFFSET   0x12b0
#define BPORT1_AB_TCD21_DADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD21_DADDR_POFFSET)

#define BPORT1_AB_TCD21_DOFF_CITER_POFFSET  0x12b4
#define BPORT1_AB_TCD21_DOFF_CITER      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD21_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD21_DLASTSGA_POFFSET  0x12b8
#define BPORT1_AB_TCD21_DLASTSGA        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD21_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD21_CSR_BITER_POFFSET  0x12bc
#define BPORT1_AB_TCD21_CSR_BITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD21_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD22_SADDR_POFFSET   0x12c0
#define BPORT1_AB_TCD22_SADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD22_SADDR_POFFSET)

#define BPORT1_AB_TCD22_SOFF_ATTR_POFFSET  0x12c4
#define BPORT1_AB_TCD22_SOFF_ATTR       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD22_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD22_NBYTES_POFFSET  0x12c8
#define BPORT1_AB_TCD22_NBYTES          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD22_NBYTES_POFFSET)

#define BPORT1_AB_TCD22_SLAST_POFFSET   0x12cc
#define BPORT1_AB_TCD22_SLAST           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD22_SLAST_POFFSET)

#define BPORT1_AB_TCD22_DADDR_POFFSET   0x12d0
#define BPORT1_AB_TCD22_DADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD22_DADDR_POFFSET)

#define BPORT1_AB_TCD22_DOFF_CITER_POFFSET  0x12d4
#define BPORT1_AB_TCD22_DOFF_CITER      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD22_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD22_DLASTSGA_POFFSET  0x12d8
#define BPORT1_AB_TCD22_DLASTSGA        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD22_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD22_CSR_BITER_POFFSET  0x12dc
#define BPORT1_AB_TCD22_CSR_BITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD22_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD23_SADDR_POFFSET   0x12e0
#define BPORT1_AB_TCD23_SADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD23_SADDR_POFFSET)

#define BPORT1_AB_TCD23_SOFF_ATTR_POFFSET  0x12e4
#define BPORT1_AB_TCD23_SOFF_ATTR       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD23_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD23_NBYTES_POFFSET  0x12e8
#define BPORT1_AB_TCD23_NBYTES          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD23_NBYTES_POFFSET)

#define BPORT1_AB_TCD23_SLAST_POFFSET   0x12ec
#define BPORT1_AB_TCD23_SLAST           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD23_SLAST_POFFSET)

#define BPORT1_AB_TCD23_DADDR_POFFSET   0x12f0
#define BPORT1_AB_TCD23_DADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD23_DADDR_POFFSET)

#define BPORT1_AB_TCD23_DOFF_CITER_POFFSET  0x12f4
#define BPORT1_AB_TCD23_DOFF_CITER      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD23_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD23_DLASTSGA_POFFSET  0x12f8
#define BPORT1_AB_TCD23_DLASTSGA        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD23_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD23_CSR_BITER_POFFSET  0x12fc
#define BPORT1_AB_TCD23_CSR_BITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD23_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD24_SADDR_POFFSET   0x1300
#define BPORT1_AB_TCD24_SADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD24_SADDR_POFFSET)

#define BPORT1_AB_TCD24_SOFF_ATTR_POFFSET  0x1304
#define BPORT1_AB_TCD24_SOFF_ATTR       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD24_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD24_NBYTES_POFFSET  0x1308
#define BPORT1_AB_TCD24_NBYTES          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD24_NBYTES_POFFSET)

#define BPORT1_AB_TCD24_SLAST_POFFSET   0x130c
#define BPORT1_AB_TCD24_SLAST           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD24_SLAST_POFFSET)

#define BPORT1_AB_TCD24_DADDR_POFFSET   0x1310
#define BPORT1_AB_TCD24_DADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD24_DADDR_POFFSET)

#define BPORT1_AB_TCD24_DOFF_CITER_POFFSET  0x1314
#define BPORT1_AB_TCD24_DOFF_CITER      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD24_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD24_DLASTSGA_POFFSET  0x1318
#define BPORT1_AB_TCD24_DLASTSGA        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD24_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD24_CSR_BITER_POFFSET  0x131c
#define BPORT1_AB_TCD24_CSR_BITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD24_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD25_SADDR_POFFSET   0x1320
#define BPORT1_AB_TCD25_SADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD25_SADDR_POFFSET)

#define BPORT1_AB_TCD25_SOFF_ATTR_POFFSET  0x1324
#define BPORT1_AB_TCD25_SOFF_ATTR       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD25_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD25_NBYTES_POFFSET  0x1328
#define BPORT1_AB_TCD25_NBYTES          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD25_NBYTES_POFFSET)

#define BPORT1_AB_TCD25_SLAST_POFFSET   0x132c
#define BPORT1_AB_TCD25_SLAST           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD25_SLAST_POFFSET)

#define BPORT1_AB_TCD25_DADDR_POFFSET   0x1330
#define BPORT1_AB_TCD25_DADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD25_DADDR_POFFSET)

#define BPORT1_AB_TCD25_DOFF_CITER_POFFSET  0x1334
#define BPORT1_AB_TCD25_DOFF_CITER      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD25_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD25_DLASTSGA_POFFSET  0x1338
#define BPORT1_AB_TCD25_DLASTSGA        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD25_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD25_CSR_BITER_POFFSET  0x133c
#define BPORT1_AB_TCD25_CSR_BITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD25_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD26_SADDR_POFFSET   0x1340
#define BPORT1_AB_TCD26_SADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD26_SADDR_POFFSET)

#define BPORT1_AB_TCD26_SOFF_ATTR_POFFSET  0x1344
#define BPORT1_AB_TCD26_SOFF_ATTR       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD26_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD26_NBYTES_POFFSET  0x1348
#define BPORT1_AB_TCD26_NBYTES          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD26_NBYTES_POFFSET)

#define BPORT1_AB_TCD26_SLAST_POFFSET   0x134c
#define BPORT1_AB_TCD26_SLAST           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD26_SLAST_POFFSET)

#define BPORT1_AB_TCD26_DADDR_POFFSET   0x1350
#define BPORT1_AB_TCD26_DADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD26_DADDR_POFFSET)

#define BPORT1_AB_TCD26_DOFF_CITER_POFFSET  0x1354
#define BPORT1_AB_TCD26_DOFF_CITER      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD26_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD26_DLASTSGA_POFFSET  0x1358
#define BPORT1_AB_TCD26_DLASTSGA        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD26_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD26_CSR_BITER_POFFSET  0x135c
#define BPORT1_AB_TCD26_CSR_BITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD26_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD27_SADDR_POFFSET   0x1360
#define BPORT1_AB_TCD27_SADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD27_SADDR_POFFSET)

#define BPORT1_AB_TCD27_SOFF_ATTR_POFFSET  0x1364
#define BPORT1_AB_TCD27_SOFF_ATTR       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD27_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD27_NBYTES_POFFSET  0x1368
#define BPORT1_AB_TCD27_NBYTES          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD27_NBYTES_POFFSET)

#define BPORT1_AB_TCD27_SLAST_POFFSET   0x136c
#define BPORT1_AB_TCD27_SLAST           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD27_SLAST_POFFSET)

#define BPORT1_AB_TCD27_DADDR_POFFSET   0x1370
#define BPORT1_AB_TCD27_DADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD27_DADDR_POFFSET)

#define BPORT1_AB_TCD27_DOFF_CITER_POFFSET  0x1374
#define BPORT1_AB_TCD27_DOFF_CITER      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD27_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD27_DLASTSGA_POFFSET  0x1378
#define BPORT1_AB_TCD27_DLASTSGA        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD27_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD27_CSR_BITER_POFFSET  0x137c
#define BPORT1_AB_TCD27_CSR_BITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD27_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD28_SADDR_POFFSET   0x1380
#define BPORT1_AB_TCD28_SADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD28_SADDR_POFFSET)

#define BPORT1_AB_TCD28_SOFF_ATTR_POFFSET  0x1384
#define BPORT1_AB_TCD28_SOFF_ATTR       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD28_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD28_NBYTES_POFFSET  0x1388
#define BPORT1_AB_TCD28_NBYTES          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD28_NBYTES_POFFSET)

#define BPORT1_AB_TCD28_SLAST_POFFSET   0x138c
#define BPORT1_AB_TCD28_SLAST           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD28_SLAST_POFFSET)

#define BPORT1_AB_TCD28_DADDR_POFFSET   0x1390
#define BPORT1_AB_TCD28_DADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD28_DADDR_POFFSET)

#define BPORT1_AB_TCD28_DOFF_CITER_POFFSET  0x1394
#define BPORT1_AB_TCD28_DOFF_CITER      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD28_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD28_DLASTSGA_POFFSET  0x1398
#define BPORT1_AB_TCD28_DLASTSGA        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD28_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD28_CSR_BITER_POFFSET  0x139c
#define BPORT1_AB_TCD28_CSR_BITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD28_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD29_SADDR_POFFSET   0x13a0
#define BPORT1_AB_TCD29_SADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD29_SADDR_POFFSET)

#define BPORT1_AB_TCD29_SOFF_ATTR_POFFSET  0x13a4
#define BPORT1_AB_TCD29_SOFF_ATTR       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD29_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD29_NBYTES_POFFSET  0x13a8
#define BPORT1_AB_TCD29_NBYTES          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD29_NBYTES_POFFSET)

#define BPORT1_AB_TCD29_SLAST_POFFSET   0x13ac
#define BPORT1_AB_TCD29_SLAST           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD29_SLAST_POFFSET)

#define BPORT1_AB_TCD29_DADDR_POFFSET   0x13b0
#define BPORT1_AB_TCD29_DADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD29_DADDR_POFFSET)

#define BPORT1_AB_TCD29_DOFF_CITER_POFFSET  0x13b4
#define BPORT1_AB_TCD29_DOFF_CITER      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD29_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD29_DLASTSGA_POFFSET  0x13b8
#define BPORT1_AB_TCD29_DLASTSGA        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD29_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD29_CSR_BITER_POFFSET  0x13bc
#define BPORT1_AB_TCD29_CSR_BITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD29_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD30_SADDR_POFFSET   0x13c0
#define BPORT1_AB_TCD30_SADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD30_SADDR_POFFSET)

#define BPORT1_AB_TCD30_SOFF_ATTR_POFFSET  0x13c4
#define BPORT1_AB_TCD30_SOFF_ATTR       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD30_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD30_NBYTES_POFFSET  0x13c8
#define BPORT1_AB_TCD30_NBYTES          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD30_NBYTES_POFFSET)

#define BPORT1_AB_TCD30_SLAST_POFFSET   0x13cc
#define BPORT1_AB_TCD30_SLAST           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD30_SLAST_POFFSET)

#define BPORT1_AB_TCD30_DADDR_POFFSET   0x13d0
#define BPORT1_AB_TCD30_DADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD30_DADDR_POFFSET)

#define BPORT1_AB_TCD30_DOFF_CITER_POFFSET  0x13d4
#define BPORT1_AB_TCD30_DOFF_CITER      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD30_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD30_DLASTSGA_POFFSET  0x13d8
#define BPORT1_AB_TCD30_DLASTSGA        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD30_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD30_CSR_BITER_POFFSET  0x13dc
#define BPORT1_AB_TCD30_CSR_BITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD30_CSR_BITER_POFFSET)

#define BPORT1_AB_TCD31_SADDR_POFFSET   0x13e0
#define BPORT1_AB_TCD31_SADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD31_SADDR_POFFSET)

#define BPORT1_AB_TCD31_SOFF_ATTR_POFFSET  0x13e4
#define BPORT1_AB_TCD31_SOFF_ATTR       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD31_SOFF_ATTR_POFFSET)

#define BPORT1_AB_TCD31_NBYTES_POFFSET  0x13e8
#define BPORT1_AB_TCD31_NBYTES          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD31_NBYTES_POFFSET)

#define BPORT1_AB_TCD31_SLAST_POFFSET   0x13ec
#define BPORT1_AB_TCD31_SLAST           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD31_SLAST_POFFSET)

#define BPORT1_AB_TCD31_DADDR_POFFSET   0x13f0
#define BPORT1_AB_TCD31_DADDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD31_DADDR_POFFSET)

#define BPORT1_AB_TCD31_DOFF_CITER_POFFSET  0x13f4
#define BPORT1_AB_TCD31_DOFF_CITER      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD31_DOFF_CITER_POFFSET)

#define BPORT1_AB_TCD31_DLASTSGA_POFFSET  0x13f8
#define BPORT1_AB_TCD31_DLASTSGA        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD31_DLASTSGA_POFFSET)

#define BPORT1_AB_TCD31_CSR_BITER_POFFSET  0x13fc
#define BPORT1_AB_TCD31_CSR_BITER       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCD31_CSR_BITER_POFFSET)


#endif

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
#define BPORT1_AB_ERQ_ERQ2              (0x1 << 2)
#define BPORT1_AB_ERQ_ERQ2_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_ERQ_ERQ3              (0x1 << 3)
#define BPORT1_AB_ERQ_ERQ3_GET(_v)      ((_v >> 3) & 0x1)
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
#define BPORT1_AB_ERQ_ERQ30             (0x1 << 30)
#define BPORT1_AB_ERQ_ERQ30_GET(_v)     ((_v >> 30) & 0x1)
#define BPORT1_AB_ERQ_ERQ31             (0x1 << 31)
#define BPORT1_AB_ERQ_ERQ31_GET(_v)     ((_v >> 31) & 0x1)

#define BPORT1_AB_EEI_POFFSET           0x14
#define BPORT1_AB_EEI                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EEI_POFFSET)
#define BPORT1_AB_EEI_EEI00             0x1
#define BPORT1_AB_EEI_EEI00_GET(_v)     (_v & 0x1)
#define BPORT1_AB_EEI_EEI01             (0x1 << 1)
#define BPORT1_AB_EEI_EEI01_GET(_v)     ((_v >> 1) & 0x1)
#define BPORT1_AB_EEI_EEI02             (0x1 << 2)
#define BPORT1_AB_EEI_EEI02_GET(_v)     ((_v >> 2) & 0x1)
#define BPORT1_AB_EEI_EEI03             (0x1 << 3)
#define BPORT1_AB_EEI_EEI03_GET(_v)     ((_v >> 3) & 0x1)
#define BPORT1_AB_EEI_EEI04             (0x1 << 4)
#define BPORT1_AB_EEI_EEI04_GET(_v)     ((_v >> 4) & 0x1)
#define BPORT1_AB_EEI_EEI05             (0x1 << 5)
#define BPORT1_AB_EEI_EEI05_GET(_v)     ((_v >> 5) & 0x1)
#define BPORT1_AB_EEI_EEI06             (0x1 << 6)
#define BPORT1_AB_EEI_EEI06_GET(_v)     ((_v >> 6) & 0x1)
#define BPORT1_AB_EEI_EEI07             (0x1 << 7)
#define BPORT1_AB_EEI_EEI07_GET(_v)     ((_v >> 7) & 0x1)
#define BPORT1_AB_EEI_EEI08             (0x1 << 8)
#define BPORT1_AB_EEI_EEI08_GET(_v)     ((_v >> 8) & 0x1)
#define BPORT1_AB_EEI_EEI09             (0x1 << 9)
#define BPORT1_AB_EEI_EEI09_GET(_v)     ((_v >> 9) & 0x1)
#define BPORT1_AB_EEI_EEI010            (0x1 << 10)
#define BPORT1_AB_EEI_EEI010_GET(_v)    ((_v >> 10) & 0x1)
#define BPORT1_AB_EEI_EEI011            (0x1 << 11)
#define BPORT1_AB_EEI_EEI011_GET(_v)    ((_v >> 11) & 0x1)
#define BPORT1_AB_EEI_EEI012            (0x1 << 12)
#define BPORT1_AB_EEI_EEI012_GET(_v)    ((_v >> 12) & 0x1)
#define BPORT1_AB_EEI_EEI013            (0x1 << 13)
#define BPORT1_AB_EEI_EEI013_GET(_v)    ((_v >> 13) & 0x1)
#define BPORT1_AB_EEI_EEI014            (0x1 << 14)
#define BPORT1_AB_EEI_EEI014_GET(_v)    ((_v >> 14) & 0x1)
#define BPORT1_AB_EEI_EEI015            (0x1 << 15)
#define BPORT1_AB_EEI_EEI015_GET(_v)    ((_v >> 15) & 0x1)
#define BPORT1_AB_EEI_EEI016            (0x1 << 16)
#define BPORT1_AB_EEI_EEI016_GET(_v)    ((_v >> 16) & 0x1)
#define BPORT1_AB_EEI_EEI017            (0x1 << 17)
#define BPORT1_AB_EEI_EEI017_GET(_v)    ((_v >> 17) & 0x1)
#define BPORT1_AB_EEI_EEI018            (0x1 << 18)
#define BPORT1_AB_EEI_EEI018_GET(_v)    ((_v >> 18) & 0x1)
#define BPORT1_AB_EEI_EEI019            (0x1 << 19)
#define BPORT1_AB_EEI_EEI019_GET(_v)    ((_v >> 19) & 0x1)
#define BPORT1_AB_EEI_EEI020            (0x1 << 20)
#define BPORT1_AB_EEI_EEI020_GET(_v)    ((_v >> 20) & 0x1)
#define BPORT1_AB_EEI_EEI021            (0x1 << 21)
#define BPORT1_AB_EEI_EEI021_GET(_v)    ((_v >> 21) & 0x1)
#define BPORT1_AB_EEI_EEI022            (0x1 << 22)
#define BPORT1_AB_EEI_EEI022_GET(_v)    ((_v >> 22) & 0x1)
#define BPORT1_AB_EEI_EEI023            (0x1 << 23)
#define BPORT1_AB_EEI_EEI023_GET(_v)    ((_v >> 23) & 0x1)
#define BPORT1_AB_EEI_EEI024            (0x1 << 24)
#define BPORT1_AB_EEI_EEI024_GET(_v)    ((_v >> 24) & 0x1)
#define BPORT1_AB_EEI_EEI025            (0x1 << 25)
#define BPORT1_AB_EEI_EEI025_GET(_v)    ((_v >> 25) & 0x1)
#define BPORT1_AB_EEI_EEI026            (0x1 << 26)
#define BPORT1_AB_EEI_EEI026_GET(_v)    ((_v >> 26) & 0x1)
#define BPORT1_AB_EEI_EEI027            (0x1 << 27)
#define BPORT1_AB_EEI_EEI027_GET(_v)    ((_v >> 27) & 0x1)
#define BPORT1_AB_EEI_EEI028            (0x1 << 28)
#define BPORT1_AB_EEI_EEI028_GET(_v)    ((_v >> 28) & 0x1)
#define BPORT1_AB_EEI_EEI029            (0x1 << 29)
#define BPORT1_AB_EEI_EEI029_GET(_v)    ((_v >> 29) & 0x1)
#define BPORT1_AB_EEI_EEI030            (0x1 << 30)
#define BPORT1_AB_EEI_EEI030_GET(_v)    ((_v >> 30) & 0x1)
#define BPORT1_AB_EEI_EEI031            (0x1 << 31)
#define BPORT1_AB_EEI_EEI031_GET(_v)    ((_v >> 31) & 0x1)

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
#define BPORT1_AB_INT_INT2              (0x1 << 2)
#define BPORT1_AB_INT_INT2_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_INT_INT3              (0x1 << 3)
#define BPORT1_AB_INT_INT3_GET(_v)      ((_v >> 3) & 0x1)
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
#define BPORT1_AB_INT_INT30             (0x1 << 30)
#define BPORT1_AB_INT_INT30_GET(_v)     ((_v >> 30) & 0x1)
#define BPORT1_AB_INT_INT31             (0x1 << 31)
#define BPORT1_AB_INT_INT31_GET(_v)     ((_v >> 31) & 0x1)

#define BPORT1_AB_ERR_POFFSET           0x2c
#define BPORT1_AB_ERR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ERR_POFFSET)
#define BPORT1_AB_ERR_ERR0              0x1
#define BPORT1_AB_ERR_ERR0_GET(_v)      (_v & 0x1)
#define BPORT1_AB_ERR_ERR1              (0x1 << 1)
#define BPORT1_AB_ERR_ERR1_GET(_v)      ((_v >> 1) & 0x1)
#define BPORT1_AB_ERR_ERR2              (0x1 << 2)
#define BPORT1_AB_ERR_ERR2_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_ERR_ERR3              (0x1 << 3)
#define BPORT1_AB_ERR_ERR3_GET(_v)      ((_v >> 3) & 0x1)
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
#define BPORT1_AB_ERR_ERR30             (0x1 << 30)
#define BPORT1_AB_ERR_ERR30_GET(_v)     ((_v >> 30) & 0x1)
#define BPORT1_AB_ERR_ERR31             (0x1 << 31)
#define BPORT1_AB_ERR_ERR31_GET(_v)     ((_v >> 31) & 0x1)

#define BPORT1_AB_HRS_POFFSET           0x34
#define BPORT1_AB_HRS                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_HRS_POFFSET)
#define BPORT1_AB_HRS_HRS0              0x1
#define BPORT1_AB_HRS_HRS0_GET(_v)      (_v & 0x1)
#define BPORT1_AB_HRS_HRS1              (0x1 << 1)
#define BPORT1_AB_HRS_HRS1_GET(_v)      ((_v >> 1) & 0x1)
#define BPORT1_AB_HRS_HRS2              (0x1 << 2)
#define BPORT1_AB_HRS_HRS2_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_HRS_HRS3              (0x1 << 3)
#define BPORT1_AB_HRS_HRS3_GET(_v)      ((_v >> 3) & 0x1)
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
#define BPORT1_AB_HRS_HRS30             (0x1 << 30)
#define BPORT1_AB_HRS_HRS30_GET(_v)     ((_v >> 30) & 0x1)
#define BPORT1_AB_HRS_HRS31             (0x1 << 31)
#define BPORT1_AB_HRS_HRS31_GET(_v)     ((_v >> 31) & 0x1)

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

#define BPORT1_TCD_POFFSET              0x1000
#define BPORT1_TCD_SADDR_POFFSET        0x0
#define BPORT1_TCD_SADDR(_AB_INDEX)     (BPORT1 + BPORT1_TCD_POFFSET + BPORT1_TCD_SADDR_POFFSET + ((_AB_INDEX) * 0x20))

#define BPORT1_TCD_SOFF_ATTR_POFFSET    0x4
#define BPORT1_TCD_SOFF_ATTR(_AB_INDEX)  (BPORT1 + BPORT1_TCD_POFFSET + BPORT1_TCD_SOFF_ATTR_POFFSET + ((_AB_INDEX) * 0x20))

#define BPORT1_TCD_NBYTES_POFFSET       0x8
#define BPORT1_TCD_NBYTES(_AB_INDEX)    (BPORT1 + BPORT1_TCD_POFFSET + BPORT1_TCD_NBYTES_POFFSET + ((_AB_INDEX) * 0x20))

#define BPORT1_TCD_SLAST_POFFSET        0xc
#define BPORT1_TCD_SLAST(_AB_INDEX)     (BPORT1 + BPORT1_TCD_POFFSET + BPORT1_TCD_SLAST_POFFSET + ((_AB_INDEX) * 0x20))

#define BPORT1_TCD_DADDR_POFFSET        0x10
#define BPORT1_TCD_DADDR(_AB_INDEX)     (BPORT1 + BPORT1_TCD_POFFSET + BPORT1_TCD_DADDR_POFFSET + ((_AB_INDEX) * 0x20))

#define BPORT1_TCD_DOFF_CITER_POFFSET   0x14
#define BPORT1_TCD_DOFF_CITER(_AB_INDEX)  (BPORT1 + BPORT1_TCD_POFFSET + BPORT1_TCD_DOFF_CITER_POFFSET + ((_AB_INDEX) * 0x20))

#define BPORT1_TCD_DLASTSGA_POFFSET     0x18
#define BPORT1_TCD_DLASTSGA(_AB_INDEX)  (BPORT1 + BPORT1_TCD_POFFSET + BPORT1_TCD_DLASTSGA_POFFSET + ((_AB_INDEX) * 0x20))

#define BPORT1_TCD_CSR_BITER_POFFSET    0x1c
#define BPORT1_TCD_CSR_BITER(_AB_INDEX)  (BPORT1 + BPORT1_TCD_POFFSET + BPORT1_TCD_CSR_BITER_POFFSET + ((_AB_INDEX) * 0x20))


#endif

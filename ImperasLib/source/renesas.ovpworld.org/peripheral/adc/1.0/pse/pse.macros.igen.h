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

// Set the macro 'ADCP0' to the base of port 'ADCP0'
#ifndef ADCP0
#error ADCP0 is undefined. It needs to be set to the port base address
#endif
// Set the macro 'ADCP1' to the base of port 'ADCP1'
#ifndef ADCP1
#error ADCP1 is undefined. It needs to be set to the port base address
#endif


#define ADCP0_REG0_POFFSET              0x0
#define ADCP0_REG0_ADM0_POFFSET         0x0
#define ADCP0_REG0_ADM0                 (ADCP0 + ADCP0_REG0_POFFSET + ADCP0_REG0_ADM0_POFFSET)
#define ADCP0_REG0_ADM0_MS              (0x1 << 4)
#define ADCP0_REG0_ADM0_MS_GET(_v)      ((_v >> 4) & 0x1)
#define ADCP0_REG0_ADM0_BS              (0x1 << 5)
#define ADCP0_REG0_ADM0_BS_GET(_v)      ((_v >> 5) & 0x1)
#define ADCP0_REG0_ADM0_ADCS            (0x1 << 6)
#define ADCP0_REG0_ADM0_ADCS_GET(_v)    ((_v >> 6) & 0x1)
#define ADCP0_REG0_ADM0_ADCE            (0x1 << 7)
#define ADCP0_REG0_ADM0_ADCE_GET(_v)    ((_v >> 7) & 0x1)

#define ADCP0_REG0_ADM1_POFFSET         0x1
#define ADCP0_REG0_ADM1                 (ADCP0 + ADCP0_REG0_POFFSET + ADCP0_REG0_ADM1_POFFSET)
#define ADCP0_REG0_ADM1_FR              0x3
#define ADCP0_REG0_ADM1_FR_GET(_v)      (_v & 0x3)
#define ADCP0_REG0_ADM1_TRG             (0x3 << 4)
#define ADCP0_REG0_ADM1_TRG_GET(_v)     ((_v >> 4) & 0x3)
#define ADCP0_REG0_ADM1_EGA             (0x3 << 6)
#define ADCP0_REG0_ADM1_EGA_GET(_v)     ((_v >> 6) & 0x3)

#define ADCP0_REG0_ADM2_POFFSET         0x2
#define ADCP0_REG0_ADM2                 (ADCP0 + ADCP0_REG0_POFFSET + ADCP0_REG0_ADM2_POFFSET)
#define ADCP0_REG0_ADM2_ANI             0xf
#define ADCP0_REG0_ADM2_ANI_GET(_v)     (_v & 0xf)

#define ADCP0_REG1_POFFSET              0x10
#define ADCP0_REG1_ADCR0_POFFSET        0x0
#define ADCP0_REG1_ADCR0                (ADCP0 + ADCP0_REG1_POFFSET + ADCP0_REG1_ADCR0_POFFSET)
#define ADCP0_REG1_ADCR0_AD             (0x3ff << 6)
#define ADCP0_REG1_ADCR0_AD_GET(_v)     ((_v >> 6) & 0x3ff)

#define ADCP0_REG1_ADCR1_POFFSET        0x2
#define ADCP0_REG1_ADCR1                (ADCP0 + ADCP0_REG1_POFFSET + ADCP0_REG1_ADCR1_POFFSET)
#define ADCP0_REG1_ADCR1_AD             (0x3ff << 6)
#define ADCP0_REG1_ADCR1_AD_GET(_v)     ((_v >> 6) & 0x3ff)

#define ADCP0_REG1_ADCR2_POFFSET        0x4
#define ADCP0_REG1_ADCR2                (ADCP0 + ADCP0_REG1_POFFSET + ADCP0_REG1_ADCR2_POFFSET)
#define ADCP0_REG1_ADCR2_AD             (0x3ff << 6)
#define ADCP0_REG1_ADCR2_AD_GET(_v)     ((_v >> 6) & 0x3ff)

#define ADCP0_REG1_ADCR3_POFFSET        0x6
#define ADCP0_REG1_ADCR3                (ADCP0 + ADCP0_REG1_POFFSET + ADCP0_REG1_ADCR3_POFFSET)
#define ADCP0_REG1_ADCR3_AD             (0x3ff << 6)
#define ADCP0_REG1_ADCR3_AD_GET(_v)     ((_v >> 6) & 0x3ff)

#define ADCP0_REG1_ADCR4_POFFSET        0x8
#define ADCP0_REG1_ADCR4                (ADCP0 + ADCP0_REG1_POFFSET + ADCP0_REG1_ADCR4_POFFSET)
#define ADCP0_REG1_ADCR4_AD             (0x3ff << 6)
#define ADCP0_REG1_ADCR4_AD_GET(_v)     ((_v >> 6) & 0x3ff)

#define ADCP0_REG1_ADCR5_POFFSET        0xa
#define ADCP0_REG1_ADCR5                (ADCP0 + ADCP0_REG1_POFFSET + ADCP0_REG1_ADCR5_POFFSET)
#define ADCP0_REG1_ADCR5_AD             (0x3ff << 6)
#define ADCP0_REG1_ADCR5_AD_GET(_v)     ((_v >> 6) & 0x3ff)

#define ADCP0_REG1_ADCR6_POFFSET        0xc
#define ADCP0_REG1_ADCR6                (ADCP0 + ADCP0_REG1_POFFSET + ADCP0_REG1_ADCR6_POFFSET)
#define ADCP0_REG1_ADCR6_AD             (0x3ff << 6)
#define ADCP0_REG1_ADCR6_AD_GET(_v)     ((_v >> 6) & 0x3ff)

#define ADCP0_REG1_ADCR7_POFFSET        0xe
#define ADCP0_REG1_ADCR7                (ADCP0 + ADCP0_REG1_POFFSET + ADCP0_REG1_ADCR7_POFFSET)
#define ADCP0_REG1_ADCR7_AD             (0x3ff << 6)
#define ADCP0_REG1_ADCR7_AD_GET(_v)     ((_v >> 6) & 0x3ff)

#define ADCP0_REG1_ADCR8_POFFSET        0x10
#define ADCP0_REG1_ADCR8                (ADCP0 + ADCP0_REG1_POFFSET + ADCP0_REG1_ADCR8_POFFSET)
#define ADCP0_REG1_ADCR8_AD             (0x3ff << 6)
#define ADCP0_REG1_ADCR8_AD_GET(_v)     ((_v >> 6) & 0x3ff)

#define ADCP0_REG1_ADCR9_POFFSET        0x12
#define ADCP0_REG1_ADCR9                (ADCP0 + ADCP0_REG1_POFFSET + ADCP0_REG1_ADCR9_POFFSET)
#define ADCP0_REG1_ADCR9_AD             (0x3ff << 6)
#define ADCP0_REG1_ADCR9_AD_GET(_v)     ((_v >> 6) & 0x3ff)

#define ADCP0_REG2_POFFSET              0x2e
#define ADCP0_REG2_ADDMA_POFFSET        0x0
#define ADCP0_REG2_ADDMA                (ADCP0 + ADCP0_REG2_POFFSET + ADCP0_REG2_ADDMA_POFFSET)
#define ADCP0_REG2_ADDMA_ODF            0x1
#define ADCP0_REG2_ADDMA_ODF_GET(_v)    (_v & 0x1)
#define ADCP0_REG2_ADDMA_ADDMA          (0x3ff << 6)
#define ADCP0_REG2_ADDMA_ADDMA_GET(_v)  ((_v >> 6) & 0x3ff)


#define ADCP1_REG0_POFFSET              0x0
#define ADCP1_REG0_ADTRSEL_POFFSET      0x0
#define ADCP1_REG0_ADTRSEL              (ADCP1 + ADCP1_REG0_POFFSET + ADCP1_REG0_ADTRSEL_POFFSET)
#define ADCP1_REG0_ADTRSEL_TSEL         0xf
#define ADCP1_REG0_ADTRSEL_TSEL_GET(_v)  (_v & 0xf)


#endif

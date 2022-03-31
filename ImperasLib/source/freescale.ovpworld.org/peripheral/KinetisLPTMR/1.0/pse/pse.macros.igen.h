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
#define BPORT1_AB_CSR_POFFSET           0x0
#define BPORT1_AB_CSR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CSR_POFFSET)
#define BPORT1_AB_CSR_TCF               (0x1 << 7)
#define BPORT1_AB_CSR_TCF_GET(_v)       ((_v >> 7) & 0x1)
#define BPORT1_AB_CSR_TEN               0x1
#define BPORT1_AB_CSR_TEN_GET(_v)       (_v & 0x1)
#define BPORT1_AB_CSR_TFC               (0x1 << 2)
#define BPORT1_AB_CSR_TFC_GET(_v)       ((_v >> 2) & 0x1)
#define BPORT1_AB_CSR_TIE               (0x1 << 6)
#define BPORT1_AB_CSR_TIE_GET(_v)       ((_v >> 6) & 0x1)
#define BPORT1_AB_CSR_TMS               (0x1 << 1)
#define BPORT1_AB_CSR_TMS_GET(_v)       ((_v >> 1) & 0x1)
#define BPORT1_AB_CSR_TPP               (0x1 << 3)
#define BPORT1_AB_CSR_TPP_GET(_v)       ((_v >> 3) & 0x1)
#define BPORT1_AB_CSR_TPS               (0x3 << 4)
#define BPORT1_AB_CSR_TPS_GET(_v)       ((_v >> 4) & 0x3)

#define BPORT1_AB_PSR_POFFSET           0x4
#define BPORT1_AB_PSR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PSR_POFFSET)
#define BPORT1_AB_PSR_PBYP              (0x1 << 2)
#define BPORT1_AB_PSR_PBYP_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_PSR_PCS               0x3
#define BPORT1_AB_PSR_PCS_GET(_v)       (_v & 0x3)
#define BPORT1_AB_PSR_PRESCALE          (0xf << 3)
#define BPORT1_AB_PSR_PRESCALE_GET(_v)  ((_v >> 3) & 0xf)

#define BPORT1_AB_CMR_POFFSET           0x8
#define BPORT1_AB_CMR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CMR_POFFSET)
#define BPORT1_AB_CMR_COMPARE           0xffff
#define BPORT1_AB_CMR_COMPARE_GET(_v)   (_v & 0xffff)

#define BPORT1_AB_CNR_POFFSET           0xc
#define BPORT1_AB_CNR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CNR_POFFSET)
#define BPORT1_AB_CNR_COUNTER           0xffff
#define BPORT1_AB_CNR_COUNTER_GET(_v)   (_v & 0xffff)


#endif

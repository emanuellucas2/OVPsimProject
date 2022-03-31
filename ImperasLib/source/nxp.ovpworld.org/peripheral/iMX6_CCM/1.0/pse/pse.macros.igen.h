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
#define BPORT1_AB_CCM_CCR_POFFSET       0x0
#define BPORT1_AB_CCM_CCR               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CCR_POFFSET)

#define BPORT1_AB_CCM_CCDR_POFFSET      0x4
#define BPORT1_AB_CCM_CCDR              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CCDR_POFFSET)

#define BPORT1_AB_CCM_CSR_POFFSET       0x8
#define BPORT1_AB_CCM_CSR               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CSR_POFFSET)

#define BPORT1_AB_CCM_CCSR_POFFSET      0xc
#define BPORT1_AB_CCM_CCSR              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CCSR_POFFSET)

#define BPORT1_AB_CCM_CACRR_POFFSET     0x10
#define BPORT1_AB_CCM_CACRR             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CACRR_POFFSET)

#define BPORT1_AB_CCM_CBCDR_POFFSET     0x14
#define BPORT1_AB_CCM_CBCDR             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CBCDR_POFFSET)

#define BPORT1_AB_CCM_CBCMR_POFFSET     0x18
#define BPORT1_AB_CCM_CBCMR             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CBCMR_POFFSET)

#define BPORT1_AB_CCM_CSCMR1_POFFSET    0x1c
#define BPORT1_AB_CCM_CSCMR1            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CSCMR1_POFFSET)

#define BPORT1_AB_CCM_CSCMR2_POFFSET    0x20
#define BPORT1_AB_CCM_CSCMR2            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CSCMR2_POFFSET)

#define BPORT1_AB_CCM_CSCDR1_POFFSET    0x24
#define BPORT1_AB_CCM_CSCDR1            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CSCDR1_POFFSET)

#define BPORT1_AB_CCM_CS1CDR_POFFSET    0x28
#define BPORT1_AB_CCM_CS1CDR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CS1CDR_POFFSET)

#define BPORT1_AB_CCM_CS2CDR_POFFSET    0x2c
#define BPORT1_AB_CCM_CS2CDR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CS2CDR_POFFSET)

#define BPORT1_AB_CCM_CDCDR_POFFSET     0x30
#define BPORT1_AB_CCM_CDCDR             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CDCDR_POFFSET)

#define BPORT1_AB_CCM_CHSCCDR_POFFSET   0x34
#define BPORT1_AB_CCM_CHSCCDR           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CHSCCDR_POFFSET)

#define BPORT1_AB_CCM_CSCDR2_POFFSET    0x38
#define BPORT1_AB_CCM_CSCDR2            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CSCDR2_POFFSET)

#define BPORT1_AB_CCM_CSCDR3_POFFSET    0x3c
#define BPORT1_AB_CCM_CSCDR3            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CSCDR3_POFFSET)

#define BPORT1_AB_CCM_CDHIPR_POFFSET    0x48
#define BPORT1_AB_CCM_CDHIPR            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CDHIPR_POFFSET)

#define BPORT1_AB_CCM_CLPCR_POFFSET     0x54
#define BPORT1_AB_CCM_CLPCR             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CLPCR_POFFSET)

#define BPORT1_AB_CCM_CISR_POFFSET      0x58
#define BPORT1_AB_CCM_CISR              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CISR_POFFSET)

#define BPORT1_AB_CCM_CIMR_POFFSET      0x5c
#define BPORT1_AB_CCM_CIMR              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CIMR_POFFSET)

#define BPORT1_AB_CCM_CCOSR_POFFSET     0x60
#define BPORT1_AB_CCM_CCOSR             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CCOSR_POFFSET)

#define BPORT1_AB_CCM_CGPR_POFFSET      0x64
#define BPORT1_AB_CCM_CGPR              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CGPR_POFFSET)

#define BPORT1_AB_CCM_CCGR0_POFFSET     0x68
#define BPORT1_AB_CCM_CCGR0             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CCGR0_POFFSET)

#define BPORT1_AB_CCM_CCGR1_POFFSET     0x6c
#define BPORT1_AB_CCM_CCGR1             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CCGR1_POFFSET)

#define BPORT1_AB_CCM_CCGR2_POFFSET     0x70
#define BPORT1_AB_CCM_CCGR2             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CCGR2_POFFSET)

#define BPORT1_AB_CCM_CCGR3_POFFSET     0x74
#define BPORT1_AB_CCM_CCGR3             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CCGR3_POFFSET)

#define BPORT1_AB_CCM_CCGR4_POFFSET     0x78
#define BPORT1_AB_CCM_CCGR4             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CCGR4_POFFSET)

#define BPORT1_AB_CCM_CCGR5_POFFSET     0x7c
#define BPORT1_AB_CCM_CCGR5             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CCGR5_POFFSET)

#define BPORT1_AB_CCM_CCGR6_POFFSET     0x80
#define BPORT1_AB_CCM_CCGR6             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CCGR6_POFFSET)

#define BPORT1_AB_CCM_CMEOR_POFFSET     0x88
#define BPORT1_AB_CCM_CMEOR             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CCM_CMEOR_POFFSET)

#define BPORT1_AB_BUFFER_POFFSET        0x0
#define BPORT1_AB_BUFFER                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BUFFER_POFFSET)
#define BPORT1_AB_BUFFER_BYTES          0x1000


#endif

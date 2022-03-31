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
#define BPORT1_AB_SRR_POFFSET           0x0
#define BPORT1_AB_SRR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SRR_POFFSET)

#define BPORT1_AB_MSR_POFFSET           0x4
#define BPORT1_AB_MSR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MSR_POFFSET)

#define BPORT1_AB_BRPR_POFFSET          0x8
#define BPORT1_AB_BRPR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BRPR_POFFSET)

#define BPORT1_AB_BTR_POFFSET           0xc
#define BPORT1_AB_BTR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BTR_POFFSET)

#define BPORT1_AB_ECR_POFFSET           0x10
#define BPORT1_AB_ECR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ECR_POFFSET)

#define BPORT1_AB_ESR_POFFSET           0x14
#define BPORT1_AB_ESR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ESR_POFFSET)

#define BPORT1_AB_SR_POFFSET            0x18
#define BPORT1_AB_SR                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SR_POFFSET)

#define BPORT1_AB_ISR_POFFSET           0x1c
#define BPORT1_AB_ISR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ISR_POFFSET)

#define BPORT1_AB_IER_POFFSET           0x20
#define BPORT1_AB_IER                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IER_POFFSET)

#define BPORT1_AB_ICR_POFFSET           0x24
#define BPORT1_AB_ICR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ICR_POFFSET)

#define BPORT1_AB_TCR_POFFSET           0x28
#define BPORT1_AB_TCR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCR_POFFSET)

#define BPORT1_AB_WIR_POFFSET           0x2c
#define BPORT1_AB_WIR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_WIR_POFFSET)

#define BPORT1_AB_TXFIFO_ID_POFFSET     0x30
#define BPORT1_AB_TXFIFO_ID             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TXFIFO_ID_POFFSET)

#define BPORT1_AB_TXFIFO_DLC_POFFSET    0x34
#define BPORT1_AB_TXFIFO_DLC            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TXFIFO_DLC_POFFSET)

#define BPORT1_AB_TXFIFO_DATA1_POFFSET  0x38
#define BPORT1_AB_TXFIFO_DATA1          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TXFIFO_DATA1_POFFSET)

#define BPORT1_AB_TXFIFO_DATA2_POFFSET  0x3c
#define BPORT1_AB_TXFIFO_DATA2          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TXFIFO_DATA2_POFFSET)

#define BPORT1_AB_TXHPB_ID_POFFSET      0x40
#define BPORT1_AB_TXHPB_ID              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TXHPB_ID_POFFSET)

#define BPORT1_AB_TXHPB_DLC_POFFSET     0x44
#define BPORT1_AB_TXHPB_DLC             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TXHPB_DLC_POFFSET)

#define BPORT1_AB_TXHPB_DATA1_POFFSET   0x48
#define BPORT1_AB_TXHPB_DATA1           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TXHPB_DATA1_POFFSET)

#define BPORT1_AB_TXHPB_DATA2_POFFSET   0x4c
#define BPORT1_AB_TXHPB_DATA2           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TXHPB_DATA2_POFFSET)

#define BPORT1_AB_RXFIFO_ID_POFFSET     0x50
#define BPORT1_AB_RXFIFO_ID             (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXFIFO_ID_POFFSET)

#define BPORT1_AB_RXFIFO_DLC_POFFSET    0x54
#define BPORT1_AB_RXFIFO_DLC            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXFIFO_DLC_POFFSET)

#define BPORT1_AB_RXFIFO_DATA1_POFFSET  0x58
#define BPORT1_AB_RXFIFO_DATA1          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXFIFO_DATA1_POFFSET)

#define BPORT1_AB_RXFIFO_DATA2_POFFSET  0x5c
#define BPORT1_AB_RXFIFO_DATA2          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXFIFO_DATA2_POFFSET)

#define BPORT1_AB_AFR_POFFSET           0x60
#define BPORT1_AB_AFR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AFR_POFFSET)

#define BPORT1_AB_AFMR1_POFFSET         0x64
#define BPORT1_AB_AFMR1                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AFMR1_POFFSET)

#define BPORT1_AB_AFIR1_POFFSET         0x68
#define BPORT1_AB_AFIR1                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AFIR1_POFFSET)

#define BPORT1_AB_AFMR2_POFFSET         0x6c
#define BPORT1_AB_AFMR2                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AFMR2_POFFSET)

#define BPORT1_AB_AFIR2_POFFSET         0x70
#define BPORT1_AB_AFIR2                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AFIR2_POFFSET)

#define BPORT1_AB_AFMR3_POFFSET         0x74
#define BPORT1_AB_AFMR3                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AFMR3_POFFSET)

#define BPORT1_AB_AFIR3_POFFSET         0x78
#define BPORT1_AB_AFIR3                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AFIR3_POFFSET)

#define BPORT1_AB_AFMR4_POFFSET         0x7c
#define BPORT1_AB_AFMR4                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AFMR4_POFFSET)

#define BPORT1_AB_AFIR4_POFFSET         0x80
#define BPORT1_AB_AFIR4                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_AFIR4_POFFSET)

#define BPORT1_AB_BUFFER_POFFSET        0x0
#define BPORT1_AB_BUFFER                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BUFFER_POFFSET)
#define BPORT1_AB_BUFFER_BYTES          0x1000


#endif

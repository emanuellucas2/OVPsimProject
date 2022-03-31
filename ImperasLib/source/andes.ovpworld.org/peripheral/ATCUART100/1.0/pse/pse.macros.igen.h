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
#define BPORT1_AB_IDREV_POFFSET         0x0
#define BPORT1_AB_IDREV                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IDREV_POFFSET)
#define BPORT1_AB_IDREV_ID              (0xffff << 16)
#define BPORT1_AB_IDREV_ID_GET(_v)      ((_v >> 16) & 0xffff)
#define BPORT1_AB_IDREV_MAJOR           (0xfff << 4)
#define BPORT1_AB_IDREV_MAJOR_GET(_v)   ((_v >> 4) & 0xfff)
#define BPORT1_AB_IDREV_MINOR           0xf
#define BPORT1_AB_IDREV_MINOR_GET(_v)   (_v & 0xf)

#define BPORT1_AB_CFG_POFFSET           0x10
#define BPORT1_AB_CFG                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CFG_POFFSET)
#define BPORT1_AB_CFG_FIFO_DEPTH        0x3
#define BPORT1_AB_CFG_FIFO_DEPTH_GET(_v)  (_v & 0x3)

#define BPORT1_AB_OSCR_POFFSET          0x14
#define BPORT1_AB_OSCR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_OSCR_POFFSET)
#define BPORT1_AB_OSCR_OSC              0x1f
#define BPORT1_AB_OSCR_OSC_GET(_v)      (_v & 0x1f)

#define BPORT1_AB_RBR_DLL_POFFSET       0x20
#define BPORT1_AB_RBR_DLL               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RBR_DLL_POFFSET)

#define BPORT1_AB_THR_DLL_POFFSET       0x20
#define BPORT1_AB_THR_DLL               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_THR_DLL_POFFSET)

#define BPORT1_AB_IER_DLM_POFFSET       0x24
#define BPORT1_AB_IER_DLM               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IER_DLM_POFFSET)
#define BPORT1_AB_IER_DLM_ERBI          0x1
#define BPORT1_AB_IER_DLM_ERBI_GET(_v)  (_v & 0x1)
#define BPORT1_AB_IER_DLM_ETHEI         (0x1 << 1)
#define BPORT1_AB_IER_DLM_ETHEI_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_IER_DLM_ELSI          (0x1 << 2)
#define BPORT1_AB_IER_DLM_ELSI_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_IER_DLM_EMSI          (0x1 << 3)
#define BPORT1_AB_IER_DLM_EMSI_GET(_v)  ((_v >> 3) & 0x1)

#define BPORT1_AB_IIR_POFFSET           0x28
#define BPORT1_AB_IIR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_IIR_POFFSET)
#define BPORT1_AB_IIR_FIFOED            (0x3 << 6)
#define BPORT1_AB_IIR_FIFOED_GET(_v)    ((_v >> 6) & 0x3)
#define BPORT1_AB_IIR_INTRID            0xf
#define BPORT1_AB_IIR_INTRID_GET(_v)    (_v & 0xf)

#define BPORT1_AB_FCR_POFFSET           0x28
#define BPORT1_AB_FCR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FCR_POFFSET)
#define BPORT1_AB_FCR_RFIFOT            (0x3 << 6)
#define BPORT1_AB_FCR_RFIFOT_GET(_v)    ((_v >> 6) & 0x3)
#define BPORT1_AB_FCR_TFIFOT            (0x3 << 4)
#define BPORT1_AB_FCR_TFIFOT_GET(_v)    ((_v >> 4) & 0x3)
#define BPORT1_AB_FCR_DMAE              (0x1 << 3)
#define BPORT1_AB_FCR_DMAE_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_FCR_TFIFORST          (0x1 << 2)
#define BPORT1_AB_FCR_TFIFORST_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_FCR_RFIFORST          (0x1 << 1)
#define BPORT1_AB_FCR_RFIFORST_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_FCR_FIFOE             0x1
#define BPORT1_AB_FCR_FIFOE_GET(_v)     (_v & 0x1)

#define BPORT1_AB_LCR_POFFSET           0x2c
#define BPORT1_AB_LCR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LCR_POFFSET)
#define BPORT1_AB_LCR_DLAB              (0x1 << 7)
#define BPORT1_AB_LCR_DLAB_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_LCR_BC                (0x1 << 6)
#define BPORT1_AB_LCR_BC_GET(_v)        ((_v >> 6) & 0x1)
#define BPORT1_AB_LCR_SPS               (0x1 << 5)
#define BPORT1_AB_LCR_SPS_GET(_v)       ((_v >> 5) & 0x1)
#define BPORT1_AB_LCR_EPS               (0x1 << 4)
#define BPORT1_AB_LCR_EPS_GET(_v)       ((_v >> 4) & 0x1)
#define BPORT1_AB_LCR_PEN               (0x1 << 3)
#define BPORT1_AB_LCR_PEN_GET(_v)       ((_v >> 3) & 0x1)
#define BPORT1_AB_LCR_STB               (0x1 << 2)
#define BPORT1_AB_LCR_STB_GET(_v)       ((_v >> 2) & 0x1)
#define BPORT1_AB_LCR_WLS               0x3
#define BPORT1_AB_LCR_WLS_GET(_v)       (_v & 0x3)

#define BPORT1_AB_MCR_POFFSET           0x30
#define BPORT1_AB_MCR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MCR_POFFSET)

#define BPORT1_AB_LSR_POFFSET           0x34
#define BPORT1_AB_LSR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LSR_POFFSET)
#define BPORT1_AB_LSR_RDR               0x1
#define BPORT1_AB_LSR_RDR_GET(_v)       (_v & 0x1)
#define BPORT1_AB_LSR_OE                (0x1 << 1)
#define BPORT1_AB_LSR_OE_GET(_v)        ((_v >> 1) & 0x1)
#define BPORT1_AB_LSR_PE                (0x1 << 2)
#define BPORT1_AB_LSR_PE_GET(_v)        ((_v >> 2) & 0x1)
#define BPORT1_AB_LSR_FE                (0x1 << 3)
#define BPORT1_AB_LSR_FE_GET(_v)        ((_v >> 3) & 0x1)
#define BPORT1_AB_LSR_LBREAK            (0x1 << 4)
#define BPORT1_AB_LSR_LBREAK_GET(_v)    ((_v >> 4) & 0x1)
#define BPORT1_AB_LSR_THRE              (0x1 << 5)
#define BPORT1_AB_LSR_THRE_GET(_v)      ((_v >> 5) & 0x1)
#define BPORT1_AB_LSR_TEMT              (0x1 << 6)
#define BPORT1_AB_LSR_TEMT_GET(_v)      ((_v >> 6) & 0x1)
#define BPORT1_AB_LSR_ERRF              (0x1 << 7)
#define BPORT1_AB_LSR_ERRF_GET(_v)      ((_v >> 7) & 0x1)

#define BPORT1_AB_MSR_POFFSET           0x38
#define BPORT1_AB_MSR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MSR_POFFSET)

#define BPORT1_AB_SCR_POFFSET           0x3c
#define BPORT1_AB_SCR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SCR_POFFSET)


#endif

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
#define BPORT1_AB_MCR_POFFSET           0x0
#define BPORT1_AB_MCR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MCR_POFFSET)
#define BPORT1_AB_MCR_CLR_RXF           (0x1 << 10)
#define BPORT1_AB_MCR_CLR_RXF_GET(_v)   ((_v >> 10) & 0x1)
#define BPORT1_AB_MCR_CLR_TXF           (0x1 << 11)
#define BPORT1_AB_MCR_CLR_TXF_GET(_v)   ((_v >> 11) & 0x1)
#define BPORT1_AB_MCR_CONT_SCKE         (0x1 << 30)
#define BPORT1_AB_MCR_CONT_SCKE_GET(_v)  ((_v >> 30) & 0x1)
#define BPORT1_AB_MCR_DCONF             (0x3 << 28)
#define BPORT1_AB_MCR_DCONF_GET(_v)     ((_v >> 28) & 0x3)
#define BPORT1_AB_MCR_DIS_RXF           (0x1 << 12)
#define BPORT1_AB_MCR_DIS_RXF_GET(_v)   ((_v >> 12) & 0x1)
#define BPORT1_AB_MCR_DIS_TXF           (0x1 << 13)
#define BPORT1_AB_MCR_DIS_TXF_GET(_v)   ((_v >> 13) & 0x1)
#define BPORT1_AB_MCR_DOZE              (0x1 << 15)
#define BPORT1_AB_MCR_DOZE_GET(_v)      ((_v >> 15) & 0x1)
#define BPORT1_AB_MCR_FRZ               (0x1 << 27)
#define BPORT1_AB_MCR_FRZ_GET(_v)       ((_v >> 27) & 0x1)
#define BPORT1_AB_MCR_HALT              0x1
#define BPORT1_AB_MCR_HALT_GET(_v)      (_v & 0x1)
#define BPORT1_AB_MCR_MDIS              (0x1 << 14)
#define BPORT1_AB_MCR_MDIS_GET(_v)      ((_v >> 14) & 0x1)
#define BPORT1_AB_MCR_MSTR              (0x1 << 31)
#define BPORT1_AB_MCR_MSTR_GET(_v)      ((_v >> 31) & 0x1)
#define BPORT1_AB_MCR_MTFE              (0x1 << 26)
#define BPORT1_AB_MCR_MTFE_GET(_v)      ((_v >> 26) & 0x1)
#define BPORT1_AB_MCR_PCSIS             (0x3f << 16)
#define BPORT1_AB_MCR_PCSIS_GET(_v)     ((_v >> 16) & 0x3f)
#define BPORT1_AB_MCR_PCSSE             (0x1 << 25)
#define BPORT1_AB_MCR_PCSSE_GET(_v)     ((_v >> 25) & 0x1)
#define BPORT1_AB_MCR_ROOE              (0x1 << 24)
#define BPORT1_AB_MCR_ROOE_GET(_v)      ((_v >> 24) & 0x1)
#define BPORT1_AB_MCR_SMPL_PT           (0x3 << 8)
#define BPORT1_AB_MCR_SMPL_PT_GET(_v)   ((_v >> 8) & 0x3)

#define BPORT1_AB_TCR_POFFSET           0x8
#define BPORT1_AB_TCR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TCR_POFFSET)
#define BPORT1_AB_TCR_SPI_TCNT          (0xffff << 16)
#define BPORT1_AB_TCR_SPI_TCNT_GET(_v)  ((_v >> 16) & 0xffff)

#define BPORT1_AB_CTAR0_POFFSET         0xc
#define BPORT1_AB_CTAR0                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CTAR0_POFFSET)
#define BPORT1_AB_CTAR0_ASC             (0xf << 8)
#define BPORT1_AB_CTAR0_ASC_GET(_v)     ((_v >> 8) & 0xf)
#define BPORT1_AB_CTAR0_BR              0xf
#define BPORT1_AB_CTAR0_BR_GET(_v)      (_v & 0xf)
#define BPORT1_AB_CTAR0_CPHA            (0x1 << 25)
#define BPORT1_AB_CTAR0_CPHA_GET(_v)    ((_v >> 25) & 0x1)
#define BPORT1_AB_CTAR0_CPOL            (0x1 << 26)
#define BPORT1_AB_CTAR0_CPOL_GET(_v)    ((_v >> 26) & 0x1)
#define BPORT1_AB_CTAR0_CSSCK           (0xf << 12)
#define BPORT1_AB_CTAR0_CSSCK_GET(_v)   ((_v >> 12) & 0xf)
#define BPORT1_AB_CTAR0_DBR             (0x1 << 31)
#define BPORT1_AB_CTAR0_DBR_GET(_v)     ((_v >> 31) & 0x1)
#define BPORT1_AB_CTAR0_DT              (0xf << 4)
#define BPORT1_AB_CTAR0_DT_GET(_v)      ((_v >> 4) & 0xf)
#define BPORT1_AB_CTAR0_FMSZ            (0xf << 27)
#define BPORT1_AB_CTAR0_FMSZ_GET(_v)    ((_v >> 27) & 0xf)
#define BPORT1_AB_CTAR0_LSBFE           (0x1 << 24)
#define BPORT1_AB_CTAR0_LSBFE_GET(_v)   ((_v >> 24) & 0x1)
#define BPORT1_AB_CTAR0_PASC            (0x3 << 20)
#define BPORT1_AB_CTAR0_PASC_GET(_v)    ((_v >> 20) & 0x3)
#define BPORT1_AB_CTAR0_PBR             (0x3 << 16)
#define BPORT1_AB_CTAR0_PBR_GET(_v)     ((_v >> 16) & 0x3)
#define BPORT1_AB_CTAR0_PCSSCK          (0x3 << 22)
#define BPORT1_AB_CTAR0_PCSSCK_GET(_v)  ((_v >> 22) & 0x3)
#define BPORT1_AB_CTAR0_PDT             (0x3 << 18)
#define BPORT1_AB_CTAR0_PDT_GET(_v)     ((_v >> 18) & 0x3)

#define BPORT1_AB_CTAR1_POFFSET         0x10
#define BPORT1_AB_CTAR1                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CTAR1_POFFSET)
#define BPORT1_AB_CTAR1_ASC             (0xf << 8)
#define BPORT1_AB_CTAR1_ASC_GET(_v)     ((_v >> 8) & 0xf)
#define BPORT1_AB_CTAR1_BR              0xf
#define BPORT1_AB_CTAR1_BR_GET(_v)      (_v & 0xf)
#define BPORT1_AB_CTAR1_CPHA            (0x1 << 25)
#define BPORT1_AB_CTAR1_CPHA_GET(_v)    ((_v >> 25) & 0x1)
#define BPORT1_AB_CTAR1_CPOL            (0x1 << 26)
#define BPORT1_AB_CTAR1_CPOL_GET(_v)    ((_v >> 26) & 0x1)
#define BPORT1_AB_CTAR1_CSSCK           (0xf << 12)
#define BPORT1_AB_CTAR1_CSSCK_GET(_v)   ((_v >> 12) & 0xf)
#define BPORT1_AB_CTAR1_DBR             (0x1 << 31)
#define BPORT1_AB_CTAR1_DBR_GET(_v)     ((_v >> 31) & 0x1)
#define BPORT1_AB_CTAR1_DT              (0xf << 4)
#define BPORT1_AB_CTAR1_DT_GET(_v)      ((_v >> 4) & 0xf)
#define BPORT1_AB_CTAR1_FMSZ            (0xf << 27)
#define BPORT1_AB_CTAR1_FMSZ_GET(_v)    ((_v >> 27) & 0xf)
#define BPORT1_AB_CTAR1_LSBFE           (0x1 << 24)
#define BPORT1_AB_CTAR1_LSBFE_GET(_v)   ((_v >> 24) & 0x1)
#define BPORT1_AB_CTAR1_PASC            (0x3 << 20)
#define BPORT1_AB_CTAR1_PASC_GET(_v)    ((_v >> 20) & 0x3)
#define BPORT1_AB_CTAR1_PBR             (0x3 << 16)
#define BPORT1_AB_CTAR1_PBR_GET(_v)     ((_v >> 16) & 0x3)
#define BPORT1_AB_CTAR1_PCSSCK          (0x3 << 22)
#define BPORT1_AB_CTAR1_PCSSCK_GET(_v)  ((_v >> 22) & 0x3)
#define BPORT1_AB_CTAR1_PDT             (0x3 << 18)
#define BPORT1_AB_CTAR1_PDT_GET(_v)     ((_v >> 18) & 0x3)

#define BPORT1_AB_SR_POFFSET            0x2c
#define BPORT1_AB_SR                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SR_POFFSET)
#define BPORT1_AB_SR_EOQF               (0x1 << 28)
#define BPORT1_AB_SR_EOQF_GET(_v)       ((_v >> 28) & 0x1)
#define BPORT1_AB_SR_POPNXTPTR          0xf
#define BPORT1_AB_SR_POPNXTPTR_GET(_v)  (_v & 0xf)
#define BPORT1_AB_SR_RFDF               (0x1 << 17)
#define BPORT1_AB_SR_RFDF_GET(_v)       ((_v >> 17) & 0x1)
#define BPORT1_AB_SR_RFOF               (0x1 << 19)
#define BPORT1_AB_SR_RFOF_GET(_v)       ((_v >> 19) & 0x1)
#define BPORT1_AB_SR_RXCTR              (0xf << 4)
#define BPORT1_AB_SR_RXCTR_GET(_v)      ((_v >> 4) & 0xf)
#define BPORT1_AB_SR_TCF                (0x1 << 31)
#define BPORT1_AB_SR_TCF_GET(_v)        ((_v >> 31) & 0x1)
#define BPORT1_AB_SR_TFFF               (0x1 << 25)
#define BPORT1_AB_SR_TFFF_GET(_v)       ((_v >> 25) & 0x1)
#define BPORT1_AB_SR_TFUF               (0x1 << 27)
#define BPORT1_AB_SR_TFUF_GET(_v)       ((_v >> 27) & 0x1)
#define BPORT1_AB_SR_TXCTR              (0xf << 12)
#define BPORT1_AB_SR_TXCTR_GET(_v)      ((_v >> 12) & 0xf)
#define BPORT1_AB_SR_TXNXTPTR           (0xf << 8)
#define BPORT1_AB_SR_TXNXTPTR_GET(_v)   ((_v >> 8) & 0xf)
#define BPORT1_AB_SR_TXRXS              (0x1 << 30)
#define BPORT1_AB_SR_TXRXS_GET(_v)      ((_v >> 30) & 0x1)

#define BPORT1_AB_RSER_POFFSET          0x30
#define BPORT1_AB_RSER                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RSER_POFFSET)
#define BPORT1_AB_RSER_EOQF_RE          (0x1 << 28)
#define BPORT1_AB_RSER_EOQF_RE_GET(_v)  ((_v >> 28) & 0x1)
#define BPORT1_AB_RSER_RFDF_DIRS        (0x1 << 16)
#define BPORT1_AB_RSER_RFDF_DIRS_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_RSER_RFDF_RE          (0x1 << 17)
#define BPORT1_AB_RSER_RFDF_RE_GET(_v)  ((_v >> 17) & 0x1)
#define BPORT1_AB_RSER_RFOF_RE          (0x1 << 19)
#define BPORT1_AB_RSER_RFOF_RE_GET(_v)  ((_v >> 19) & 0x1)
#define BPORT1_AB_RSER_TCF_RE           (0x1 << 31)
#define BPORT1_AB_RSER_TCF_RE_GET(_v)   ((_v >> 31) & 0x1)
#define BPORT1_AB_RSER_TFFF_DIRS        (0x1 << 24)
#define BPORT1_AB_RSER_TFFF_DIRS_GET(_v)  ((_v >> 24) & 0x1)
#define BPORT1_AB_RSER_TFFF_RE          (0x1 << 25)
#define BPORT1_AB_RSER_TFFF_RE_GET(_v)  ((_v >> 25) & 0x1)
#define BPORT1_AB_RSER_TFUF_RE          (0x1 << 27)
#define BPORT1_AB_RSER_TFUF_RE_GET(_v)  ((_v >> 27) & 0x1)

#define BPORT1_AB_PUSHR_POFFSET         0x34
#define BPORT1_AB_PUSHR                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PUSHR_POFFSET)
#define BPORT1_AB_PUSHR_CONT            (0x1 << 31)
#define BPORT1_AB_PUSHR_CONT_GET(_v)    ((_v >> 31) & 0x1)
#define BPORT1_AB_PUSHR_CTAS            (0x7 << 28)
#define BPORT1_AB_PUSHR_CTAS_GET(_v)    ((_v >> 28) & 0x7)
#define BPORT1_AB_PUSHR_CTCNT           (0x1 << 26)
#define BPORT1_AB_PUSHR_CTCNT_GET(_v)   ((_v >> 26) & 0x1)
#define BPORT1_AB_PUSHR_EOQ             (0x1 << 27)
#define BPORT1_AB_PUSHR_EOQ_GET(_v)     ((_v >> 27) & 0x1)
#define BPORT1_AB_PUSHR_PCS             (0x3f << 16)
#define BPORT1_AB_PUSHR_PCS_GET(_v)     ((_v >> 16) & 0x3f)
#define BPORT1_AB_PUSHR_TXDATA          0xffff
#define BPORT1_AB_PUSHR_TXDATA_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_POPR_POFFSET          0x38
#define BPORT1_AB_POPR                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_POPR_POFFSET)
#define BPORT1_AB_POPR_RXDATA           0xffffffff
#define BPORT1_AB_POPR_RXDATA_GET(_v)   (_v & 0xffffffff)

#define BPORT1_AB_TXFR0_POFFSET         0x3c
#define BPORT1_AB_TXFR0                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TXFR0_POFFSET)
#define BPORT1_AB_TXFR0_TXCMD_TXDATA    (0xffff << 16)
#define BPORT1_AB_TXFR0_TXCMD_TXDATA_GET(_v)  ((_v >> 16) & 0xffff)
#define BPORT1_AB_TXFR0_TXDATA          0xffff
#define BPORT1_AB_TXFR0_TXDATA_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_TXFR1_POFFSET         0x40
#define BPORT1_AB_TXFR1                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TXFR1_POFFSET)
#define BPORT1_AB_TXFR1_TXCMD_TXDATA    (0xffff << 16)
#define BPORT1_AB_TXFR1_TXCMD_TXDATA_GET(_v)  ((_v >> 16) & 0xffff)
#define BPORT1_AB_TXFR1_TXDATA          0xffff
#define BPORT1_AB_TXFR1_TXDATA_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_TXFR2_POFFSET         0x44
#define BPORT1_AB_TXFR2                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TXFR2_POFFSET)
#define BPORT1_AB_TXFR2_TXCMD_TXDATA    (0xffff << 16)
#define BPORT1_AB_TXFR2_TXCMD_TXDATA_GET(_v)  ((_v >> 16) & 0xffff)
#define BPORT1_AB_TXFR2_TXDATA          0xffff
#define BPORT1_AB_TXFR2_TXDATA_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_TXFR3_POFFSET         0x48
#define BPORT1_AB_TXFR3                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_TXFR3_POFFSET)
#define BPORT1_AB_TXFR3_TXCMD_TXDATA    (0xffff << 16)
#define BPORT1_AB_TXFR3_TXCMD_TXDATA_GET(_v)  ((_v >> 16) & 0xffff)
#define BPORT1_AB_TXFR3_TXDATA          0xffff
#define BPORT1_AB_TXFR3_TXDATA_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_RXFR0_POFFSET         0x7c
#define BPORT1_AB_RXFR0                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXFR0_POFFSET)
#define BPORT1_AB_RXFR0_RXDATA          0xffffffff
#define BPORT1_AB_RXFR0_RXDATA_GET(_v)  (_v & 0xffffffff)

#define BPORT1_AB_RXFR1_POFFSET         0x80
#define BPORT1_AB_RXFR1                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXFR1_POFFSET)
#define BPORT1_AB_RXFR1_RXDATA          0xffffffff
#define BPORT1_AB_RXFR1_RXDATA_GET(_v)  (_v & 0xffffffff)

#define BPORT1_AB_RXFR2_POFFSET         0x84
#define BPORT1_AB_RXFR2                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXFR2_POFFSET)
#define BPORT1_AB_RXFR2_RXDATA          0xffffffff
#define BPORT1_AB_RXFR2_RXDATA_GET(_v)  (_v & 0xffffffff)

#define BPORT1_AB_RXFR3_POFFSET         0x88
#define BPORT1_AB_RXFR3                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RXFR3_POFFSET)
#define BPORT1_AB_RXFR3_RXDATA          0xffffffff
#define BPORT1_AB_RXFR3_RXDATA_GET(_v)  (_v & 0xffffffff)


#endif

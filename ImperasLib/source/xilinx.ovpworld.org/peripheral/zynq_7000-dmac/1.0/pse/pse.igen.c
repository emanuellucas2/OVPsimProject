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


#include "pse.igen.h"
/////////////////////////////// Port Declarations //////////////////////////////

bportS_abS_dataT bportS_abS_data;

bportNS_abNS_dataT bportNS_abNS_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "zynq_7000-dmac", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bportNS_abNS_CCR0_maskWrite) {
    bportNS_abNS_data.CCR0.value = (bportNS_abNS_data.CCR0.value & BPORTNS_ABNS_CCR0_WRNMASK) | (data & BPORTNS_ABNS_CCR0_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CCR1_maskWrite) {
    bportNS_abNS_data.CCR1.value = (bportNS_abNS_data.CCR1.value & BPORTNS_ABNS_CCR1_WRNMASK) | (data & BPORTNS_ABNS_CCR1_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CCR2_maskWrite) {
    bportNS_abNS_data.CCR2.value = (bportNS_abNS_data.CCR2.value & BPORTNS_ABNS_CCR2_WRNMASK) | (data & BPORTNS_ABNS_CCR2_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CCR3_maskWrite) {
    bportNS_abNS_data.CCR3.value = (bportNS_abNS_data.CCR3.value & BPORTNS_ABNS_CCR3_WRNMASK) | (data & BPORTNS_ABNS_CCR3_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CCR4_maskWrite) {
    bportNS_abNS_data.CCR4.value = (bportNS_abNS_data.CCR4.value & BPORTNS_ABNS_CCR4_WRNMASK) | (data & BPORTNS_ABNS_CCR4_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CCR5_maskWrite) {
    bportNS_abNS_data.CCR5.value = (bportNS_abNS_data.CCR5.value & BPORTNS_ABNS_CCR5_WRNMASK) | (data & BPORTNS_ABNS_CCR5_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CCR6_maskWrite) {
    bportNS_abNS_data.CCR6.value = (bportNS_abNS_data.CCR6.value & BPORTNS_ABNS_CCR6_WRNMASK) | (data & BPORTNS_ABNS_CCR6_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CCR7_maskWrite) {
    bportNS_abNS_data.CCR7.value = (bportNS_abNS_data.CCR7.value & BPORTNS_ABNS_CCR7_WRNMASK) | (data & BPORTNS_ABNS_CCR7_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CPC0_maskWrite) {
    bportNS_abNS_data.CPC0.value = (bportNS_abNS_data.CPC0.value & BPORTNS_ABNS_CPC0_WRNMASK) | (data & BPORTNS_ABNS_CPC0_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CPC1_maskWrite) {
    bportNS_abNS_data.CPC1.value = (bportNS_abNS_data.CPC1.value & BPORTNS_ABNS_CPC1_WRNMASK) | (data & BPORTNS_ABNS_CPC1_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CPC2_maskWrite) {
    bportNS_abNS_data.CPC2.value = (bportNS_abNS_data.CPC2.value & BPORTNS_ABNS_CPC2_WRNMASK) | (data & BPORTNS_ABNS_CPC2_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CPC3_maskWrite) {
    bportNS_abNS_data.CPC3.value = (bportNS_abNS_data.CPC3.value & BPORTNS_ABNS_CPC3_WRNMASK) | (data & BPORTNS_ABNS_CPC3_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CPC4_maskWrite) {
    bportNS_abNS_data.CPC4.value = (bportNS_abNS_data.CPC4.value & BPORTNS_ABNS_CPC4_WRNMASK) | (data & BPORTNS_ABNS_CPC4_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CPC5_maskWrite) {
    bportNS_abNS_data.CPC5.value = (bportNS_abNS_data.CPC5.value & BPORTNS_ABNS_CPC5_WRNMASK) | (data & BPORTNS_ABNS_CPC5_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CPC6_maskWrite) {
    bportNS_abNS_data.CPC6.value = (bportNS_abNS_data.CPC6.value & BPORTNS_ABNS_CPC6_WRNMASK) | (data & BPORTNS_ABNS_CPC6_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CPC7_maskWrite) {
    bportNS_abNS_data.CPC7.value = (bportNS_abNS_data.CPC7.value & BPORTNS_ABNS_CPC7_WRNMASK) | (data & BPORTNS_ABNS_CPC7_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CR0_maskWrite) {
    bportNS_abNS_data.CR0.value = (bportNS_abNS_data.CR0.value & BPORTNS_ABNS_CR0_WRNMASK) | (data & BPORTNS_ABNS_CR0_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CR1_maskWrite) {
    bportNS_abNS_data.CR1.value = (bportNS_abNS_data.CR1.value & BPORTNS_ABNS_CR1_WRNMASK) | (data & BPORTNS_ABNS_CR1_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CR2_maskWrite) {
    bportNS_abNS_data.CR2.value = (bportNS_abNS_data.CR2.value & BPORTNS_ABNS_CR2_WRNMASK) | (data & BPORTNS_ABNS_CR2_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CR3_maskWrite) {
    bportNS_abNS_data.CR3.value = (bportNS_abNS_data.CR3.value & BPORTNS_ABNS_CR3_WRNMASK) | (data & BPORTNS_ABNS_CR3_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CR4_maskWrite) {
    bportNS_abNS_data.CR4.value = (bportNS_abNS_data.CR4.value & BPORTNS_ABNS_CR4_WRNMASK) | (data & BPORTNS_ABNS_CR4_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CRD_maskWrite) {
    bportNS_abNS_data.CRD.value = (bportNS_abNS_data.CRD.value & BPORTNS_ABNS_CRD_WRNMASK) | (data & BPORTNS_ABNS_CRD_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CSR0_maskWrite) {
    bportNS_abNS_data.CSR0.value = (bportNS_abNS_data.CSR0.value & BPORTNS_ABNS_CSR0_WRNMASK) | (data & BPORTNS_ABNS_CSR0_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CSR1_maskWrite) {
    bportNS_abNS_data.CSR1.value = (bportNS_abNS_data.CSR1.value & BPORTNS_ABNS_CSR1_WRNMASK) | (data & BPORTNS_ABNS_CSR1_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CSR2_maskWrite) {
    bportNS_abNS_data.CSR2.value = (bportNS_abNS_data.CSR2.value & BPORTNS_ABNS_CSR2_WRNMASK) | (data & BPORTNS_ABNS_CSR2_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CSR3_maskWrite) {
    bportNS_abNS_data.CSR3.value = (bportNS_abNS_data.CSR3.value & BPORTNS_ABNS_CSR3_WRNMASK) | (data & BPORTNS_ABNS_CSR3_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CSR4_maskWrite) {
    bportNS_abNS_data.CSR4.value = (bportNS_abNS_data.CSR4.value & BPORTNS_ABNS_CSR4_WRNMASK) | (data & BPORTNS_ABNS_CSR4_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CSR5_maskWrite) {
    bportNS_abNS_data.CSR5.value = (bportNS_abNS_data.CSR5.value & BPORTNS_ABNS_CSR5_WRNMASK) | (data & BPORTNS_ABNS_CSR5_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CSR6_maskWrite) {
    bportNS_abNS_data.CSR6.value = (bportNS_abNS_data.CSR6.value & BPORTNS_ABNS_CSR6_WRNMASK) | (data & BPORTNS_ABNS_CSR6_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_CSR7_maskWrite) {
    bportNS_abNS_data.CSR7.value = (bportNS_abNS_data.CSR7.value & BPORTNS_ABNS_CSR7_WRNMASK) | (data & BPORTNS_ABNS_CSR7_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_DAR0_maskWrite) {
    bportNS_abNS_data.DAR0.value = (bportNS_abNS_data.DAR0.value & BPORTNS_ABNS_DAR0_WRNMASK) | (data & BPORTNS_ABNS_DAR0_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_DAR1_maskWrite) {
    bportNS_abNS_data.DAR1.value = (bportNS_abNS_data.DAR1.value & BPORTNS_ABNS_DAR1_WRNMASK) | (data & BPORTNS_ABNS_DAR1_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_DAR2_maskWrite) {
    bportNS_abNS_data.DAR2.value = (bportNS_abNS_data.DAR2.value & BPORTNS_ABNS_DAR2_WRNMASK) | (data & BPORTNS_ABNS_DAR2_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_DAR3_maskWrite) {
    bportNS_abNS_data.DAR3.value = (bportNS_abNS_data.DAR3.value & BPORTNS_ABNS_DAR3_WRNMASK) | (data & BPORTNS_ABNS_DAR3_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_DAR4_maskWrite) {
    bportNS_abNS_data.DAR4.value = (bportNS_abNS_data.DAR4.value & BPORTNS_ABNS_DAR4_WRNMASK) | (data & BPORTNS_ABNS_DAR4_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_DAR5_maskWrite) {
    bportNS_abNS_data.DAR5.value = (bportNS_abNS_data.DAR5.value & BPORTNS_ABNS_DAR5_WRNMASK) | (data & BPORTNS_ABNS_DAR5_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_DAR6_maskWrite) {
    bportNS_abNS_data.DAR6.value = (bportNS_abNS_data.DAR6.value & BPORTNS_ABNS_DAR6_WRNMASK) | (data & BPORTNS_ABNS_DAR6_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_DAR7_maskWrite) {
    bportNS_abNS_data.DAR7.value = (bportNS_abNS_data.DAR7.value & BPORTNS_ABNS_DAR7_WRNMASK) | (data & BPORTNS_ABNS_DAR7_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_DBGCMD_maskWrite) {
    bportNS_abNS_data.DBGCMD.value = (bportNS_abNS_data.DBGCMD.value & BPORTNS_ABNS_DBGCMD_WRNMASK) | (data & BPORTNS_ABNS_DBGCMD_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_DBGINST0_maskWrite) {
    bportNS_abNS_data.DBGINST0.value = (bportNS_abNS_data.DBGINST0.value & BPORTNS_ABNS_DBGINST0_WRNMASK) | (data & BPORTNS_ABNS_DBGINST0_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_DBGINST1_maskWrite) {
    bportNS_abNS_data.DBGINST1.value = (bportNS_abNS_data.DBGINST1.value & BPORTNS_ABNS_DBGINST1_WRNMASK) | (data & BPORTNS_ABNS_DBGINST1_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_DBGSTATUS_maskWrite) {
    bportNS_abNS_data.DBGSTATUS.value = (bportNS_abNS_data.DBGSTATUS.value & BPORTNS_ABNS_DBGSTATUS_WRNMASK) | (data & BPORTNS_ABNS_DBGSTATUS_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_DPC_maskWrite) {
    bportNS_abNS_data.DPC.value = (bportNS_abNS_data.DPC.value & BPORTNS_ABNS_DPC_WRNMASK) | (data & BPORTNS_ABNS_DPC_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_DSR_maskWrite) {
    bportNS_abNS_data.DSR.value = (bportNS_abNS_data.DSR.value & BPORTNS_ABNS_DSR_WRNMASK) | (data & BPORTNS_ABNS_DSR_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_FSRC_maskWrite) {
    bportNS_abNS_data.FSRC.value = (bportNS_abNS_data.FSRC.value & BPORTNS_ABNS_FSRC_WRNMASK) | (data & BPORTNS_ABNS_FSRC_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_FSRD_maskWrite) {
    bportNS_abNS_data.FSRD.value = (bportNS_abNS_data.FSRD.value & BPORTNS_ABNS_FSRD_WRNMASK) | (data & BPORTNS_ABNS_FSRD_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_FTR0_maskWrite) {
    bportNS_abNS_data.FTR0.value = (bportNS_abNS_data.FTR0.value & BPORTNS_ABNS_FTR0_WRNMASK) | (data & BPORTNS_ABNS_FTR0_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_FTR1_maskWrite) {
    bportNS_abNS_data.FTR1.value = (bportNS_abNS_data.FTR1.value & BPORTNS_ABNS_FTR1_WRNMASK) | (data & BPORTNS_ABNS_FTR1_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_FTR2_maskWrite) {
    bportNS_abNS_data.FTR2.value = (bportNS_abNS_data.FTR2.value & BPORTNS_ABNS_FTR2_WRNMASK) | (data & BPORTNS_ABNS_FTR2_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_FTR3_maskWrite) {
    bportNS_abNS_data.FTR3.value = (bportNS_abNS_data.FTR3.value & BPORTNS_ABNS_FTR3_WRNMASK) | (data & BPORTNS_ABNS_FTR3_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_FTR4_maskWrite) {
    bportNS_abNS_data.FTR4.value = (bportNS_abNS_data.FTR4.value & BPORTNS_ABNS_FTR4_WRNMASK) | (data & BPORTNS_ABNS_FTR4_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_FTR5_maskWrite) {
    bportNS_abNS_data.FTR5.value = (bportNS_abNS_data.FTR5.value & BPORTNS_ABNS_FTR5_WRNMASK) | (data & BPORTNS_ABNS_FTR5_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_FTR6_maskWrite) {
    bportNS_abNS_data.FTR6.value = (bportNS_abNS_data.FTR6.value & BPORTNS_ABNS_FTR6_WRNMASK) | (data & BPORTNS_ABNS_FTR6_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_FTR7_maskWrite) {
    bportNS_abNS_data.FTR7.value = (bportNS_abNS_data.FTR7.value & BPORTNS_ABNS_FTR7_WRNMASK) | (data & BPORTNS_ABNS_FTR7_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_FTRD_maskWrite) {
    bportNS_abNS_data.FTRD.value = (bportNS_abNS_data.FTRD.value & BPORTNS_ABNS_FTRD_WRNMASK) | (data & BPORTNS_ABNS_FTRD_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_INTCLR_maskWrite) {
    bportNS_abNS_data.INTCLR.value = (bportNS_abNS_data.INTCLR.value & BPORTNS_ABNS_INTCLR_WRNMASK) | (data & BPORTNS_ABNS_INTCLR_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_INTEN_maskWrite) {
    bportNS_abNS_data.INTEN.value = (bportNS_abNS_data.INTEN.value & BPORTNS_ABNS_INTEN_WRNMASK) | (data & BPORTNS_ABNS_INTEN_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_INTMIS_maskWrite) {
    bportNS_abNS_data.INTMIS.value = (bportNS_abNS_data.INTMIS.value & BPORTNS_ABNS_INTMIS_WRNMASK) | (data & BPORTNS_ABNS_INTMIS_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_INT_EVENT_RIS_maskWrite) {
    bportNS_abNS_data.INT_EVENT_RIS.value = (bportNS_abNS_data.INT_EVENT_RIS.value & BPORTNS_ABNS_INT_EVENT_RIS_WRNMASK) | (data & BPORTNS_ABNS_INT_EVENT_RIS_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_LC0_0_maskWrite) {
    bportNS_abNS_data.LC0_0.value = (bportNS_abNS_data.LC0_0.value & BPORTNS_ABNS_LC0_0_WRNMASK) | (data & BPORTNS_ABNS_LC0_0_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_LC0_1_maskWrite) {
    bportNS_abNS_data.LC0_1.value = (bportNS_abNS_data.LC0_1.value & BPORTNS_ABNS_LC0_1_WRNMASK) | (data & BPORTNS_ABNS_LC0_1_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_LC0_2_maskWrite) {
    bportNS_abNS_data.LC0_2.value = (bportNS_abNS_data.LC0_2.value & BPORTNS_ABNS_LC0_2_WRNMASK) | (data & BPORTNS_ABNS_LC0_2_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_LC0_3_maskWrite) {
    bportNS_abNS_data.LC0_3.value = (bportNS_abNS_data.LC0_3.value & BPORTNS_ABNS_LC0_3_WRNMASK) | (data & BPORTNS_ABNS_LC0_3_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_LC0_4_maskWrite) {
    bportNS_abNS_data.LC0_4.value = (bportNS_abNS_data.LC0_4.value & BPORTNS_ABNS_LC0_4_WRNMASK) | (data & BPORTNS_ABNS_LC0_4_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_LC0_5_maskWrite) {
    bportNS_abNS_data.LC0_5.value = (bportNS_abNS_data.LC0_5.value & BPORTNS_ABNS_LC0_5_WRNMASK) | (data & BPORTNS_ABNS_LC0_5_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_LC0_6_maskWrite) {
    bportNS_abNS_data.LC0_6.value = (bportNS_abNS_data.LC0_6.value & BPORTNS_ABNS_LC0_6_WRNMASK) | (data & BPORTNS_ABNS_LC0_6_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_LC0_7_maskWrite) {
    bportNS_abNS_data.LC0_7.value = (bportNS_abNS_data.LC0_7.value & BPORTNS_ABNS_LC0_7_WRNMASK) | (data & BPORTNS_ABNS_LC0_7_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_LC1_0_maskWrite) {
    bportNS_abNS_data.LC1_0.value = (bportNS_abNS_data.LC1_0.value & BPORTNS_ABNS_LC1_0_WRNMASK) | (data & BPORTNS_ABNS_LC1_0_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_LC1_1_maskWrite) {
    bportNS_abNS_data.LC1_1.value = (bportNS_abNS_data.LC1_1.value & BPORTNS_ABNS_LC1_1_WRNMASK) | (data & BPORTNS_ABNS_LC1_1_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_LC1_2_maskWrite) {
    bportNS_abNS_data.LC1_2.value = (bportNS_abNS_data.LC1_2.value & BPORTNS_ABNS_LC1_2_WRNMASK) | (data & BPORTNS_ABNS_LC1_2_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_LC1_3_maskWrite) {
    bportNS_abNS_data.LC1_3.value = (bportNS_abNS_data.LC1_3.value & BPORTNS_ABNS_LC1_3_WRNMASK) | (data & BPORTNS_ABNS_LC1_3_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_LC1_4_maskWrite) {
    bportNS_abNS_data.LC1_4.value = (bportNS_abNS_data.LC1_4.value & BPORTNS_ABNS_LC1_4_WRNMASK) | (data & BPORTNS_ABNS_LC1_4_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_LC1_5_maskWrite) {
    bportNS_abNS_data.LC1_5.value = (bportNS_abNS_data.LC1_5.value & BPORTNS_ABNS_LC1_5_WRNMASK) | (data & BPORTNS_ABNS_LC1_5_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_LC1_6_maskWrite) {
    bportNS_abNS_data.LC1_6.value = (bportNS_abNS_data.LC1_6.value & BPORTNS_ABNS_LC1_6_WRNMASK) | (data & BPORTNS_ABNS_LC1_6_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_LC1_7_maskWrite) {
    bportNS_abNS_data.LC1_7.value = (bportNS_abNS_data.LC1_7.value & BPORTNS_ABNS_LC1_7_WRNMASK) | (data & BPORTNS_ABNS_LC1_7_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_SAR0_maskWrite) {
    bportNS_abNS_data.SAR0.value = (bportNS_abNS_data.SAR0.value & BPORTNS_ABNS_SAR0_WRNMASK) | (data & BPORTNS_ABNS_SAR0_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_SAR1_maskWrite) {
    bportNS_abNS_data.SAR1.value = (bportNS_abNS_data.SAR1.value & BPORTNS_ABNS_SAR1_WRNMASK) | (data & BPORTNS_ABNS_SAR1_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_SAR2_maskWrite) {
    bportNS_abNS_data.SAR2.value = (bportNS_abNS_data.SAR2.value & BPORTNS_ABNS_SAR2_WRNMASK) | (data & BPORTNS_ABNS_SAR2_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_SAR3_maskWrite) {
    bportNS_abNS_data.SAR3.value = (bportNS_abNS_data.SAR3.value & BPORTNS_ABNS_SAR3_WRNMASK) | (data & BPORTNS_ABNS_SAR3_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_SAR4_maskWrite) {
    bportNS_abNS_data.SAR4.value = (bportNS_abNS_data.SAR4.value & BPORTNS_ABNS_SAR4_WRNMASK) | (data & BPORTNS_ABNS_SAR4_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_SAR5_maskWrite) {
    bportNS_abNS_data.SAR5.value = (bportNS_abNS_data.SAR5.value & BPORTNS_ABNS_SAR5_WRNMASK) | (data & BPORTNS_ABNS_SAR5_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_SAR6_maskWrite) {
    bportNS_abNS_data.SAR6.value = (bportNS_abNS_data.SAR6.value & BPORTNS_ABNS_SAR6_WRNMASK) | (data & BPORTNS_ABNS_SAR6_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_SAR7_maskWrite) {
    bportNS_abNS_data.SAR7.value = (bportNS_abNS_data.SAR7.value & BPORTNS_ABNS_SAR7_WRNMASK) | (data & BPORTNS_ABNS_SAR7_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_WD_maskWrite) {
    bportNS_abNS_data.WD.value = (bportNS_abNS_data.WD.value & BPORTNS_ABNS_WD_WRNMASK) | (data & BPORTNS_ABNS_WD_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_pcell_id_0_maskWrite) {
    bportNS_abNS_data.pcell_id_0.value = (bportNS_abNS_data.pcell_id_0.value & BPORTNS_ABNS_PCELL_ID_0_WRNMASK) | (data & BPORTNS_ABNS_PCELL_ID_0_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_pcell_id_1_maskWrite) {
    bportNS_abNS_data.pcell_id_1.value = (bportNS_abNS_data.pcell_id_1.value & BPORTNS_ABNS_PCELL_ID_1_WRNMASK) | (data & BPORTNS_ABNS_PCELL_ID_1_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_pcell_id_2_maskWrite) {
    bportNS_abNS_data.pcell_id_2.value = (bportNS_abNS_data.pcell_id_2.value & BPORTNS_ABNS_PCELL_ID_2_WRNMASK) | (data & BPORTNS_ABNS_PCELL_ID_2_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_pcell_id_3_maskWrite) {
    bportNS_abNS_data.pcell_id_3.value = (bportNS_abNS_data.pcell_id_3.value & BPORTNS_ABNS_PCELL_ID_3_WRNMASK) | (data & BPORTNS_ABNS_PCELL_ID_3_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_periph_id_0_maskWrite) {
    bportNS_abNS_data.periph_id_0.value = (bportNS_abNS_data.periph_id_0.value & BPORTNS_ABNS_PERIPH_ID_0_WRNMASK) | (data & BPORTNS_ABNS_PERIPH_ID_0_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_periph_id_1_maskWrite) {
    bportNS_abNS_data.periph_id_1.value = (bportNS_abNS_data.periph_id_1.value & BPORTNS_ABNS_PERIPH_ID_1_WRNMASK) | (data & BPORTNS_ABNS_PERIPH_ID_1_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_periph_id_2_maskWrite) {
    bportNS_abNS_data.periph_id_2.value = (bportNS_abNS_data.periph_id_2.value & BPORTNS_ABNS_PERIPH_ID_2_WRNMASK) | (data & BPORTNS_ABNS_PERIPH_ID_2_WRMASK);
}

static PPM_WRITE_CB(bportNS_abNS_periph_id_3_maskWrite) {
    bportNS_abNS_data.periph_id_3.value = (bportNS_abNS_data.periph_id_3.value & BPORTNS_ABNS_PERIPH_ID_3_WRNMASK) | (data & BPORTNS_ABNS_PERIPH_ID_3_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CCR0_maskWrite) {
    bportS_abS_data.CCR0.value = (bportS_abS_data.CCR0.value & BPORTS_ABS_CCR0_WRNMASK) | (data & BPORTS_ABS_CCR0_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CCR1_maskWrite) {
    bportS_abS_data.CCR1.value = (bportS_abS_data.CCR1.value & BPORTS_ABS_CCR1_WRNMASK) | (data & BPORTS_ABS_CCR1_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CCR2_maskWrite) {
    bportS_abS_data.CCR2.value = (bportS_abS_data.CCR2.value & BPORTS_ABS_CCR2_WRNMASK) | (data & BPORTS_ABS_CCR2_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CCR3_maskWrite) {
    bportS_abS_data.CCR3.value = (bportS_abS_data.CCR3.value & BPORTS_ABS_CCR3_WRNMASK) | (data & BPORTS_ABS_CCR3_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CCR4_maskWrite) {
    bportS_abS_data.CCR4.value = (bportS_abS_data.CCR4.value & BPORTS_ABS_CCR4_WRNMASK) | (data & BPORTS_ABS_CCR4_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CCR5_maskWrite) {
    bportS_abS_data.CCR5.value = (bportS_abS_data.CCR5.value & BPORTS_ABS_CCR5_WRNMASK) | (data & BPORTS_ABS_CCR5_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CCR6_maskWrite) {
    bportS_abS_data.CCR6.value = (bportS_abS_data.CCR6.value & BPORTS_ABS_CCR6_WRNMASK) | (data & BPORTS_ABS_CCR6_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CCR7_maskWrite) {
    bportS_abS_data.CCR7.value = (bportS_abS_data.CCR7.value & BPORTS_ABS_CCR7_WRNMASK) | (data & BPORTS_ABS_CCR7_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CPC0_maskWrite) {
    bportS_abS_data.CPC0.value = (bportS_abS_data.CPC0.value & BPORTS_ABS_CPC0_WRNMASK) | (data & BPORTS_ABS_CPC0_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CPC1_maskWrite) {
    bportS_abS_data.CPC1.value = (bportS_abS_data.CPC1.value & BPORTS_ABS_CPC1_WRNMASK) | (data & BPORTS_ABS_CPC1_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CPC2_maskWrite) {
    bportS_abS_data.CPC2.value = (bportS_abS_data.CPC2.value & BPORTS_ABS_CPC2_WRNMASK) | (data & BPORTS_ABS_CPC2_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CPC3_maskWrite) {
    bportS_abS_data.CPC3.value = (bportS_abS_data.CPC3.value & BPORTS_ABS_CPC3_WRNMASK) | (data & BPORTS_ABS_CPC3_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CPC4_maskWrite) {
    bportS_abS_data.CPC4.value = (bportS_abS_data.CPC4.value & BPORTS_ABS_CPC4_WRNMASK) | (data & BPORTS_ABS_CPC4_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CPC5_maskWrite) {
    bportS_abS_data.CPC5.value = (bportS_abS_data.CPC5.value & BPORTS_ABS_CPC5_WRNMASK) | (data & BPORTS_ABS_CPC5_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CPC6_maskWrite) {
    bportS_abS_data.CPC6.value = (bportS_abS_data.CPC6.value & BPORTS_ABS_CPC6_WRNMASK) | (data & BPORTS_ABS_CPC6_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CPC7_maskWrite) {
    bportS_abS_data.CPC7.value = (bportS_abS_data.CPC7.value & BPORTS_ABS_CPC7_WRNMASK) | (data & BPORTS_ABS_CPC7_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CR0_maskWrite) {
    bportS_abS_data.CR0.value = (bportS_abS_data.CR0.value & BPORTS_ABS_CR0_WRNMASK) | (data & BPORTS_ABS_CR0_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CR1_maskWrite) {
    bportS_abS_data.CR1.value = (bportS_abS_data.CR1.value & BPORTS_ABS_CR1_WRNMASK) | (data & BPORTS_ABS_CR1_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CR2_maskWrite) {
    bportS_abS_data.CR2.value = (bportS_abS_data.CR2.value & BPORTS_ABS_CR2_WRNMASK) | (data & BPORTS_ABS_CR2_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CR3_maskWrite) {
    bportS_abS_data.CR3.value = (bportS_abS_data.CR3.value & BPORTS_ABS_CR3_WRNMASK) | (data & BPORTS_ABS_CR3_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CR4_maskWrite) {
    bportS_abS_data.CR4.value = (bportS_abS_data.CR4.value & BPORTS_ABS_CR4_WRNMASK) | (data & BPORTS_ABS_CR4_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CRD_maskWrite) {
    bportS_abS_data.CRD.value = (bportS_abS_data.CRD.value & BPORTS_ABS_CRD_WRNMASK) | (data & BPORTS_ABS_CRD_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CSR0_maskWrite) {
    bportS_abS_data.CSR0.value = (bportS_abS_data.CSR0.value & BPORTS_ABS_CSR0_WRNMASK) | (data & BPORTS_ABS_CSR0_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CSR1_maskWrite) {
    bportS_abS_data.CSR1.value = (bportS_abS_data.CSR1.value & BPORTS_ABS_CSR1_WRNMASK) | (data & BPORTS_ABS_CSR1_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CSR2_maskWrite) {
    bportS_abS_data.CSR2.value = (bportS_abS_data.CSR2.value & BPORTS_ABS_CSR2_WRNMASK) | (data & BPORTS_ABS_CSR2_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CSR3_maskWrite) {
    bportS_abS_data.CSR3.value = (bportS_abS_data.CSR3.value & BPORTS_ABS_CSR3_WRNMASK) | (data & BPORTS_ABS_CSR3_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CSR4_maskWrite) {
    bportS_abS_data.CSR4.value = (bportS_abS_data.CSR4.value & BPORTS_ABS_CSR4_WRNMASK) | (data & BPORTS_ABS_CSR4_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CSR5_maskWrite) {
    bportS_abS_data.CSR5.value = (bportS_abS_data.CSR5.value & BPORTS_ABS_CSR5_WRNMASK) | (data & BPORTS_ABS_CSR5_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CSR6_maskWrite) {
    bportS_abS_data.CSR6.value = (bportS_abS_data.CSR6.value & BPORTS_ABS_CSR6_WRNMASK) | (data & BPORTS_ABS_CSR6_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_CSR7_maskWrite) {
    bportS_abS_data.CSR7.value = (bportS_abS_data.CSR7.value & BPORTS_ABS_CSR7_WRNMASK) | (data & BPORTS_ABS_CSR7_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_DAR0_maskWrite) {
    bportS_abS_data.DAR0.value = (bportS_abS_data.DAR0.value & BPORTS_ABS_DAR0_WRNMASK) | (data & BPORTS_ABS_DAR0_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_DAR1_maskWrite) {
    bportS_abS_data.DAR1.value = (bportS_abS_data.DAR1.value & BPORTS_ABS_DAR1_WRNMASK) | (data & BPORTS_ABS_DAR1_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_DAR2_maskWrite) {
    bportS_abS_data.DAR2.value = (bportS_abS_data.DAR2.value & BPORTS_ABS_DAR2_WRNMASK) | (data & BPORTS_ABS_DAR2_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_DAR3_maskWrite) {
    bportS_abS_data.DAR3.value = (bportS_abS_data.DAR3.value & BPORTS_ABS_DAR3_WRNMASK) | (data & BPORTS_ABS_DAR3_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_DAR4_maskWrite) {
    bportS_abS_data.DAR4.value = (bportS_abS_data.DAR4.value & BPORTS_ABS_DAR4_WRNMASK) | (data & BPORTS_ABS_DAR4_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_DAR5_maskWrite) {
    bportS_abS_data.DAR5.value = (bportS_abS_data.DAR5.value & BPORTS_ABS_DAR5_WRNMASK) | (data & BPORTS_ABS_DAR5_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_DAR6_maskWrite) {
    bportS_abS_data.DAR6.value = (bportS_abS_data.DAR6.value & BPORTS_ABS_DAR6_WRNMASK) | (data & BPORTS_ABS_DAR6_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_DAR7_maskWrite) {
    bportS_abS_data.DAR7.value = (bportS_abS_data.DAR7.value & BPORTS_ABS_DAR7_WRNMASK) | (data & BPORTS_ABS_DAR7_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_DBGCMD_maskWrite) {
    bportS_abS_data.DBGCMD.value = (bportS_abS_data.DBGCMD.value & BPORTS_ABS_DBGCMD_WRNMASK) | (data & BPORTS_ABS_DBGCMD_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_DBGINST0_maskWrite) {
    bportS_abS_data.DBGINST0.value = (bportS_abS_data.DBGINST0.value & BPORTS_ABS_DBGINST0_WRNMASK) | (data & BPORTS_ABS_DBGINST0_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_DBGINST1_maskWrite) {
    bportS_abS_data.DBGINST1.value = (bportS_abS_data.DBGINST1.value & BPORTS_ABS_DBGINST1_WRNMASK) | (data & BPORTS_ABS_DBGINST1_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_DBGSTATUS_maskWrite) {
    bportS_abS_data.DBGSTATUS.value = (bportS_abS_data.DBGSTATUS.value & BPORTS_ABS_DBGSTATUS_WRNMASK) | (data & BPORTS_ABS_DBGSTATUS_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_DPC_maskWrite) {
    bportS_abS_data.DPC.value = (bportS_abS_data.DPC.value & BPORTS_ABS_DPC_WRNMASK) | (data & BPORTS_ABS_DPC_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_DSR_maskWrite) {
    bportS_abS_data.DSR.value = (bportS_abS_data.DSR.value & BPORTS_ABS_DSR_WRNMASK) | (data & BPORTS_ABS_DSR_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_FSRC_maskWrite) {
    bportS_abS_data.FSRC.value = (bportS_abS_data.FSRC.value & BPORTS_ABS_FSRC_WRNMASK) | (data & BPORTS_ABS_FSRC_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_FSRD_maskWrite) {
    bportS_abS_data.FSRD.value = (bportS_abS_data.FSRD.value & BPORTS_ABS_FSRD_WRNMASK) | (data & BPORTS_ABS_FSRD_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_FTR0_maskWrite) {
    bportS_abS_data.FTR0.value = (bportS_abS_data.FTR0.value & BPORTS_ABS_FTR0_WRNMASK) | (data & BPORTS_ABS_FTR0_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_FTR1_maskWrite) {
    bportS_abS_data.FTR1.value = (bportS_abS_data.FTR1.value & BPORTS_ABS_FTR1_WRNMASK) | (data & BPORTS_ABS_FTR1_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_FTR2_maskWrite) {
    bportS_abS_data.FTR2.value = (bportS_abS_data.FTR2.value & BPORTS_ABS_FTR2_WRNMASK) | (data & BPORTS_ABS_FTR2_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_FTR3_maskWrite) {
    bportS_abS_data.FTR3.value = (bportS_abS_data.FTR3.value & BPORTS_ABS_FTR3_WRNMASK) | (data & BPORTS_ABS_FTR3_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_FTR4_maskWrite) {
    bportS_abS_data.FTR4.value = (bportS_abS_data.FTR4.value & BPORTS_ABS_FTR4_WRNMASK) | (data & BPORTS_ABS_FTR4_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_FTR5_maskWrite) {
    bportS_abS_data.FTR5.value = (bportS_abS_data.FTR5.value & BPORTS_ABS_FTR5_WRNMASK) | (data & BPORTS_ABS_FTR5_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_FTR6_maskWrite) {
    bportS_abS_data.FTR6.value = (bportS_abS_data.FTR6.value & BPORTS_ABS_FTR6_WRNMASK) | (data & BPORTS_ABS_FTR6_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_FTR7_maskWrite) {
    bportS_abS_data.FTR7.value = (bportS_abS_data.FTR7.value & BPORTS_ABS_FTR7_WRNMASK) | (data & BPORTS_ABS_FTR7_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_FTRD_maskWrite) {
    bportS_abS_data.FTRD.value = (bportS_abS_data.FTRD.value & BPORTS_ABS_FTRD_WRNMASK) | (data & BPORTS_ABS_FTRD_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_INTCLR_maskWrite) {
    bportS_abS_data.INTCLR.value = (bportS_abS_data.INTCLR.value & BPORTS_ABS_INTCLR_WRNMASK) | (data & BPORTS_ABS_INTCLR_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_INTEN_maskWrite) {
    bportS_abS_data.INTEN.value = (bportS_abS_data.INTEN.value & BPORTS_ABS_INTEN_WRNMASK) | (data & BPORTS_ABS_INTEN_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_INTMIS_maskWrite) {
    bportS_abS_data.INTMIS.value = (bportS_abS_data.INTMIS.value & BPORTS_ABS_INTMIS_WRNMASK) | (data & BPORTS_ABS_INTMIS_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_INT_EVENT_RIS_maskWrite) {
    bportS_abS_data.INT_EVENT_RIS.value = (bportS_abS_data.INT_EVENT_RIS.value & BPORTS_ABS_INT_EVENT_RIS_WRNMASK) | (data & BPORTS_ABS_INT_EVENT_RIS_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_LC0_0_maskWrite) {
    bportS_abS_data.LC0_0.value = (bportS_abS_data.LC0_0.value & BPORTS_ABS_LC0_0_WRNMASK) | (data & BPORTS_ABS_LC0_0_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_LC0_1_maskWrite) {
    bportS_abS_data.LC0_1.value = (bportS_abS_data.LC0_1.value & BPORTS_ABS_LC0_1_WRNMASK) | (data & BPORTS_ABS_LC0_1_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_LC0_2_maskWrite) {
    bportS_abS_data.LC0_2.value = (bportS_abS_data.LC0_2.value & BPORTS_ABS_LC0_2_WRNMASK) | (data & BPORTS_ABS_LC0_2_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_LC0_3_maskWrite) {
    bportS_abS_data.LC0_3.value = (bportS_abS_data.LC0_3.value & BPORTS_ABS_LC0_3_WRNMASK) | (data & BPORTS_ABS_LC0_3_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_LC0_4_maskWrite) {
    bportS_abS_data.LC0_4.value = (bportS_abS_data.LC0_4.value & BPORTS_ABS_LC0_4_WRNMASK) | (data & BPORTS_ABS_LC0_4_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_LC0_5_maskWrite) {
    bportS_abS_data.LC0_5.value = (bportS_abS_data.LC0_5.value & BPORTS_ABS_LC0_5_WRNMASK) | (data & BPORTS_ABS_LC0_5_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_LC0_6_maskWrite) {
    bportS_abS_data.LC0_6.value = (bportS_abS_data.LC0_6.value & BPORTS_ABS_LC0_6_WRNMASK) | (data & BPORTS_ABS_LC0_6_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_LC0_7_maskWrite) {
    bportS_abS_data.LC0_7.value = (bportS_abS_data.LC0_7.value & BPORTS_ABS_LC0_7_WRNMASK) | (data & BPORTS_ABS_LC0_7_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_LC1_0_maskWrite) {
    bportS_abS_data.LC1_0.value = (bportS_abS_data.LC1_0.value & BPORTS_ABS_LC1_0_WRNMASK) | (data & BPORTS_ABS_LC1_0_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_LC1_1_maskWrite) {
    bportS_abS_data.LC1_1.value = (bportS_abS_data.LC1_1.value & BPORTS_ABS_LC1_1_WRNMASK) | (data & BPORTS_ABS_LC1_1_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_LC1_2_maskWrite) {
    bportS_abS_data.LC1_2.value = (bportS_abS_data.LC1_2.value & BPORTS_ABS_LC1_2_WRNMASK) | (data & BPORTS_ABS_LC1_2_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_LC1_3_maskWrite) {
    bportS_abS_data.LC1_3.value = (bportS_abS_data.LC1_3.value & BPORTS_ABS_LC1_3_WRNMASK) | (data & BPORTS_ABS_LC1_3_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_LC1_4_maskWrite) {
    bportS_abS_data.LC1_4.value = (bportS_abS_data.LC1_4.value & BPORTS_ABS_LC1_4_WRNMASK) | (data & BPORTS_ABS_LC1_4_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_LC1_5_maskWrite) {
    bportS_abS_data.LC1_5.value = (bportS_abS_data.LC1_5.value & BPORTS_ABS_LC1_5_WRNMASK) | (data & BPORTS_ABS_LC1_5_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_LC1_6_maskWrite) {
    bportS_abS_data.LC1_6.value = (bportS_abS_data.LC1_6.value & BPORTS_ABS_LC1_6_WRNMASK) | (data & BPORTS_ABS_LC1_6_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_LC1_7_maskWrite) {
    bportS_abS_data.LC1_7.value = (bportS_abS_data.LC1_7.value & BPORTS_ABS_LC1_7_WRNMASK) | (data & BPORTS_ABS_LC1_7_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_SAR0_maskWrite) {
    bportS_abS_data.SAR0.value = (bportS_abS_data.SAR0.value & BPORTS_ABS_SAR0_WRNMASK) | (data & BPORTS_ABS_SAR0_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_SAR1_maskWrite) {
    bportS_abS_data.SAR1.value = (bportS_abS_data.SAR1.value & BPORTS_ABS_SAR1_WRNMASK) | (data & BPORTS_ABS_SAR1_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_SAR2_maskWrite) {
    bportS_abS_data.SAR2.value = (bportS_abS_data.SAR2.value & BPORTS_ABS_SAR2_WRNMASK) | (data & BPORTS_ABS_SAR2_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_SAR3_maskWrite) {
    bportS_abS_data.SAR3.value = (bportS_abS_data.SAR3.value & BPORTS_ABS_SAR3_WRNMASK) | (data & BPORTS_ABS_SAR3_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_SAR4_maskWrite) {
    bportS_abS_data.SAR4.value = (bportS_abS_data.SAR4.value & BPORTS_ABS_SAR4_WRNMASK) | (data & BPORTS_ABS_SAR4_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_SAR5_maskWrite) {
    bportS_abS_data.SAR5.value = (bportS_abS_data.SAR5.value & BPORTS_ABS_SAR5_WRNMASK) | (data & BPORTS_ABS_SAR5_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_SAR6_maskWrite) {
    bportS_abS_data.SAR6.value = (bportS_abS_data.SAR6.value & BPORTS_ABS_SAR6_WRNMASK) | (data & BPORTS_ABS_SAR6_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_SAR7_maskWrite) {
    bportS_abS_data.SAR7.value = (bportS_abS_data.SAR7.value & BPORTS_ABS_SAR7_WRNMASK) | (data & BPORTS_ABS_SAR7_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_WD_maskWrite) {
    bportS_abS_data.WD.value = (bportS_abS_data.WD.value & BPORTS_ABS_WD_WRNMASK) | (data & BPORTS_ABS_WD_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_pcell_id_0_maskWrite) {
    bportS_abS_data.pcell_id_0.value = (bportS_abS_data.pcell_id_0.value & BPORTS_ABS_PCELL_ID_0_WRNMASK) | (data & BPORTS_ABS_PCELL_ID_0_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_pcell_id_1_maskWrite) {
    bportS_abS_data.pcell_id_1.value = (bportS_abS_data.pcell_id_1.value & BPORTS_ABS_PCELL_ID_1_WRNMASK) | (data & BPORTS_ABS_PCELL_ID_1_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_pcell_id_2_maskWrite) {
    bportS_abS_data.pcell_id_2.value = (bportS_abS_data.pcell_id_2.value & BPORTS_ABS_PCELL_ID_2_WRNMASK) | (data & BPORTS_ABS_PCELL_ID_2_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_pcell_id_3_maskWrite) {
    bportS_abS_data.pcell_id_3.value = (bportS_abS_data.pcell_id_3.value & BPORTS_ABS_PCELL_ID_3_WRNMASK) | (data & BPORTS_ABS_PCELL_ID_3_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_periph_id_0_maskWrite) {
    bportS_abS_data.periph_id_0.value = (bportS_abS_data.periph_id_0.value & BPORTS_ABS_PERIPH_ID_0_WRNMASK) | (data & BPORTS_ABS_PERIPH_ID_0_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_periph_id_1_maskWrite) {
    bportS_abS_data.periph_id_1.value = (bportS_abS_data.periph_id_1.value & BPORTS_ABS_PERIPH_ID_1_WRNMASK) | (data & BPORTS_ABS_PERIPH_ID_1_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_periph_id_2_maskWrite) {
    bportS_abS_data.periph_id_2.value = (bportS_abS_data.periph_id_2.value & BPORTS_ABS_PERIPH_ID_2_WRNMASK) | (data & BPORTS_ABS_PERIPH_ID_2_WRMASK);
}

static PPM_WRITE_CB(bportS_abS_periph_id_3_maskWrite) {
    bportS_abS_data.periph_id_3.value = (bportS_abS_data.periph_id_3.value & BPORTS_ABS_PERIPH_ID_3_WRNMASK) | (data & BPORTS_ABS_PERIPH_ID_3_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bportS = ppmCreateSlaveBusPort("bportS", 4096);
    if (!handles.bportS) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bportS'");
    }

    ppmInstallReadCallback(regNoDefinitionReadS, (void*)0 , handles.bportS + 0x0, 0x1000);
    ppmInstallWriteCallback(regNoDefinitionWriteS, (void*)0 , handles.bportS + 0x0, 0x1000);
    handles.bportNS = ppmCreateSlaveBusPort("bportNS", 4096);
    if (!handles.bportNS) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bportNS'");
    }

    ppmInstallReadCallback(regNoDefinitionReadNS, (void*)0 , handles.bportNS + 0x0, 0x1000);
    ppmInstallWriteCallback(regNoDefinitionWriteNS, (void*)0 , handles.bportNS + 0x0, 0x1000);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "abS_DSR",
            "DMA Manager Status",
            handles.bportS,
            0x0,
            4,
            read_32,
            bportS_abS_DSR_maskWrite,
            view32,
            &(bportS_abS_data.DSR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_DPC",
            "DMA Program Counter",
            handles.bportS,
            0x4,
            4,
            read_32,
            bportS_abS_DPC_maskWrite,
            view32,
            &(bportS_abS_data.DPC.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_INTEN",
            "DMASEV Instruction Response Control",
            handles.bportS,
            0x20,
            4,
            read_32,
            bportS_abS_INTEN_maskWrite,
            view32,
            &(bportS_abS_data.INTEN.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_INT_EVENT_RIS",
            "Event Interrupt Raw Status",
            handles.bportS,
            0x24,
            4,
            read_32,
            bportS_abS_INT_EVENT_RIS_maskWrite,
            view32,
            &(bportS_abS_data.INT_EVENT_RIS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_INTMIS",
            "Interrupt Status",
            handles.bportS,
            0x28,
            4,
            read_32,
            bportS_abS_INTMIS_maskWrite,
            view32,
            &(bportS_abS_data.INTMIS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_INTCLR",
            "Interrupt Clear",
            handles.bportS,
            0x2c,
            4,
            read_32,
            bportS_abS_INTCLR_maskWrite,
            view32,
            &(bportS_abS_data.INTCLR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_FSRD",
            "Fault Status DMA Manager",
            handles.bportS,
            0x30,
            4,
            read_32,
            bportS_abS_FSRD_maskWrite,
            view32,
            &(bportS_abS_data.FSRD.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_FSRC",
            "Fault Status DMA Channel",
            handles.bportS,
            0x34,
            4,
            read_32,
            bportS_abS_FSRC_maskWrite,
            view32,
            &(bportS_abS_data.FSRC.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_FTRD",
            "Fault Type DMA Manager",
            handles.bportS,
            0x38,
            4,
            read_32,
            bportS_abS_FTRD_maskWrite,
            view32,
            &(bportS_abS_data.FTRD.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_FTR0",
            "Default Type DMA Channel 0",
            handles.bportS,
            0x40,
            4,
            read_32,
            bportS_abS_FTR0_maskWrite,
            view32,
            &(bportS_abS_data.FTR0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_FTR1",
            "Default Type DMA Channel 1",
            handles.bportS,
            0x44,
            4,
            read_32,
            bportS_abS_FTR1_maskWrite,
            view32,
            &(bportS_abS_data.FTR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_FTR2",
            "Default Type DMA Channel 2",
            handles.bportS,
            0x48,
            4,
            read_32,
            bportS_abS_FTR2_maskWrite,
            view32,
            &(bportS_abS_data.FTR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_FTR3",
            "Default Type DMA Channel 3",
            handles.bportS,
            0x4c,
            4,
            read_32,
            bportS_abS_FTR3_maskWrite,
            view32,
            &(bportS_abS_data.FTR3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_FTR4",
            "Default Type DMA Channel 4",
            handles.bportS,
            0x50,
            4,
            read_32,
            bportS_abS_FTR4_maskWrite,
            view32,
            &(bportS_abS_data.FTR4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_FTR5",
            "Default Type DMA Channel 5",
            handles.bportS,
            0x54,
            4,
            read_32,
            bportS_abS_FTR5_maskWrite,
            view32,
            &(bportS_abS_data.FTR5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_FTR6",
            "Default Type DMA Channel 6",
            handles.bportS,
            0x58,
            4,
            read_32,
            bportS_abS_FTR6_maskWrite,
            view32,
            &(bportS_abS_data.FTR6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_FTR7",
            "Default Type DMA Channel 7",
            handles.bportS,
            0x5c,
            4,
            read_32,
            bportS_abS_FTR7_maskWrite,
            view32,
            &(bportS_abS_data.FTR7.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CSR0",
            "Channel Status DMA Channel 0",
            handles.bportS,
            0x100,
            4,
            read_32,
            bportS_abS_CSR0_maskWrite,
            view32,
            &(bportS_abS_data.CSR0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CPC0",
            "Channel PC for DMA Channel 0",
            handles.bportS,
            0x104,
            4,
            read_32,
            bportS_abS_CPC0_maskWrite,
            view32,
            &(bportS_abS_data.CPC0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CSR1",
            "Channel Status DMA Channel 1",
            handles.bportS,
            0x108,
            4,
            read_32,
            bportS_abS_CSR1_maskWrite,
            view32,
            &(bportS_abS_data.CSR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CPC1",
            "Channel PC for DMA Channel 1",
            handles.bportS,
            0x10c,
            4,
            read_32,
            bportS_abS_CPC1_maskWrite,
            view32,
            &(bportS_abS_data.CPC1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CSR2",
            "Channel Status DMA Channel 2",
            handles.bportS,
            0x110,
            4,
            read_32,
            bportS_abS_CSR2_maskWrite,
            view32,
            &(bportS_abS_data.CSR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CPC2",
            "Channel PC for DMA Channel 2",
            handles.bportS,
            0x114,
            4,
            read_32,
            bportS_abS_CPC2_maskWrite,
            view32,
            &(bportS_abS_data.CPC2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CSR3",
            "Channel Status DMA Channel 3",
            handles.bportS,
            0x118,
            4,
            read_32,
            bportS_abS_CSR3_maskWrite,
            view32,
            &(bportS_abS_data.CSR3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CPC3",
            "Channel PC for DMA Channel 3",
            handles.bportS,
            0x11c,
            4,
            read_32,
            bportS_abS_CPC3_maskWrite,
            view32,
            &(bportS_abS_data.CPC3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CSR4",
            "Channel Status DMA Channel 4",
            handles.bportS,
            0x120,
            4,
            read_32,
            bportS_abS_CSR4_maskWrite,
            view32,
            &(bportS_abS_data.CSR4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CPC4",
            "Channel PC for DMA Channel 4",
            handles.bportS,
            0x124,
            4,
            read_32,
            bportS_abS_CPC4_maskWrite,
            view32,
            &(bportS_abS_data.CPC4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CSR5",
            "Channel Status DMA Channel 5",
            handles.bportS,
            0x128,
            4,
            read_32,
            bportS_abS_CSR5_maskWrite,
            view32,
            &(bportS_abS_data.CSR5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CPC5",
            "Channel PC for DMA Channel 5",
            handles.bportS,
            0x12c,
            4,
            read_32,
            bportS_abS_CPC5_maskWrite,
            view32,
            &(bportS_abS_data.CPC5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CSR6",
            "Channel Status DMA Channel 6",
            handles.bportS,
            0x130,
            4,
            read_32,
            bportS_abS_CSR6_maskWrite,
            view32,
            &(bportS_abS_data.CSR6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CPC6",
            "Channel PC for DMA Channel 6",
            handles.bportS,
            0x134,
            4,
            read_32,
            bportS_abS_CPC6_maskWrite,
            view32,
            &(bportS_abS_data.CPC6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CSR7",
            "Channel Status DMA Channel 7",
            handles.bportS,
            0x138,
            4,
            read_32,
            bportS_abS_CSR7_maskWrite,
            view32,
            &(bportS_abS_data.CSR7.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CPC7",
            "Channel PC for DMA Channel 7",
            handles.bportS,
            0x13c,
            4,
            read_32,
            bportS_abS_CPC7_maskWrite,
            view32,
            &(bportS_abS_data.CPC7.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_SAR0",
            "Source Address DMA Channel 0",
            handles.bportS,
            0x400,
            4,
            read_32,
            bportS_abS_SAR0_maskWrite,
            view32,
            &(bportS_abS_data.SAR0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_DAR0",
            "Destination Addr DMA Channel 0",
            handles.bportS,
            0x404,
            4,
            read_32,
            bportS_abS_DAR0_maskWrite,
            view32,
            &(bportS_abS_data.DAR0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CCR0",
            "Channel Control DMA Channel 0 (dmac0_ns: 0x00000000 dmac0_s: 0x00800200)",
            handles.bportS,
            0x408,
            4,
            read_32,
            bportS_abS_CCR0_maskWrite,
            view32,
            &(bportS_abS_data.CCR0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_LC0_0",
            "Loop Counter 0 DMA Channel 0",
            handles.bportS,
            0x40c,
            4,
            read_32,
            bportS_abS_LC0_0_maskWrite,
            view32,
            &(bportS_abS_data.LC0_0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_LC1_0",
            "Loop Counter 1 DMA Channel 0",
            handles.bportS,
            0x410,
            4,
            read_32,
            bportS_abS_LC1_0_maskWrite,
            view32,
            &(bportS_abS_data.LC1_0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_SAR1",
            "Source address DMA Channel 1",
            handles.bportS,
            0x420,
            4,
            read_32,
            bportS_abS_SAR1_maskWrite,
            view32,
            &(bportS_abS_data.SAR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_DAR1",
            "Destination Addr DMA Channel 1",
            handles.bportS,
            0x424,
            4,
            read_32,
            bportS_abS_DAR1_maskWrite,
            view32,
            &(bportS_abS_data.DAR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CCR1",
            "Channel Control DMA Channel 1 (dmac0_ns: 0x00000000 dmac0_s: 0x00800200 )",
            handles.bportS,
            0x428,
            4,
            read_32,
            bportS_abS_CCR1_maskWrite,
            view32,
            &(bportS_abS_data.CCR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_LC0_1",
            "Loop Counter 0 DMA Channel 1",
            handles.bportS,
            0x42c,
            4,
            read_32,
            bportS_abS_LC0_1_maskWrite,
            view32,
            &(bportS_abS_data.LC0_1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_LC1_1",
            "Loop Counter 1 DMA Channel 1",
            handles.bportS,
            0x430,
            4,
            read_32,
            bportS_abS_LC1_1_maskWrite,
            view32,
            &(bportS_abS_data.LC1_1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_SAR2",
            "Source Address DMA Channel 2",
            handles.bportS,
            0x440,
            4,
            read_32,
            bportS_abS_SAR2_maskWrite,
            view32,
            &(bportS_abS_data.SAR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_DAR2",
            "Destination Addr DMA Channel 2",
            handles.bportS,
            0x444,
            4,
            read_32,
            bportS_abS_DAR2_maskWrite,
            view32,
            &(bportS_abS_data.DAR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CCR2",
            "Channel Control DMA Channel 2 (dmac0_ns: 0x00000000 dmac0_s: 0x00800200 )",
            handles.bportS,
            0x448,
            4,
            read_32,
            bportS_abS_CCR2_maskWrite,
            view32,
            &(bportS_abS_data.CCR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_LC0_2",
            "Loop Counter 0 DMA Channel 2",
            handles.bportS,
            0x44c,
            4,
            read_32,
            bportS_abS_LC0_2_maskWrite,
            view32,
            &(bportS_abS_data.LC0_2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_LC1_2",
            "Loop Counter 1 DMA Channel 2",
            handles.bportS,
            0x450,
            4,
            read_32,
            bportS_abS_LC1_2_maskWrite,
            view32,
            &(bportS_abS_data.LC1_2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_SAR3",
            "Source Address DMA Channel 3",
            handles.bportS,
            0x460,
            4,
            read_32,
            bportS_abS_SAR3_maskWrite,
            view32,
            &(bportS_abS_data.SAR3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_DAR3",
            "Destination Addr DMA Channel 3",
            handles.bportS,
            0x464,
            4,
            read_32,
            bportS_abS_DAR3_maskWrite,
            view32,
            &(bportS_abS_data.DAR3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CCR3",
            "Channel Control DMA Channel 3 (dmac0_ns: 0x00000000 dmac0_s: 0x00800200)",
            handles.bportS,
            0x468,
            4,
            read_32,
            bportS_abS_CCR3_maskWrite,
            view32,
            &(bportS_abS_data.CCR3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_LC0_3",
            "Loop Counter 0 DMA Channel 3",
            handles.bportS,
            0x46c,
            4,
            read_32,
            bportS_abS_LC0_3_maskWrite,
            view32,
            &(bportS_abS_data.LC0_3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_LC1_3",
            "Loop Counter 1 DMA Channel 3",
            handles.bportS,
            0x470,
            4,
            read_32,
            bportS_abS_LC1_3_maskWrite,
            view32,
            &(bportS_abS_data.LC1_3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_SAR4",
            "Source Address DMA Channel 4",
            handles.bportS,
            0x480,
            4,
            read_32,
            bportS_abS_SAR4_maskWrite,
            view32,
            &(bportS_abS_data.SAR4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_DAR4",
            "Destination Addr DMA Channel 4",
            handles.bportS,
            0x484,
            4,
            read_32,
            bportS_abS_DAR4_maskWrite,
            view32,
            &(bportS_abS_data.DAR4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CCR4",
            "Channel Control DMA Channel 4 (dmac0_ns: 0x00000000 dmac0_s: 0x00800200 )",
            handles.bportS,
            0x488,
            4,
            read_32,
            bportS_abS_CCR4_maskWrite,
            view32,
            &(bportS_abS_data.CCR4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_LC0_4",
            "Loop Counter 0 DMA Channel 4",
            handles.bportS,
            0x48c,
            4,
            read_32,
            bportS_abS_LC0_4_maskWrite,
            view32,
            &(bportS_abS_data.LC0_4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_LC1_4",
            "Loop Counter 1 DMA Channel 4",
            handles.bportS,
            0x490,
            4,
            read_32,
            bportS_abS_LC1_4_maskWrite,
            view32,
            &(bportS_abS_data.LC1_4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_SAR5",
            "Source Address DMA Channel 5",
            handles.bportS,
            0x4a0,
            4,
            read_32,
            bportS_abS_SAR5_maskWrite,
            view32,
            &(bportS_abS_data.SAR5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_DAR5",
            "Destination Addr DMA Channel 5",
            handles.bportS,
            0x4a4,
            4,
            read_32,
            bportS_abS_DAR5_maskWrite,
            view32,
            &(bportS_abS_data.DAR5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CCR5",
            "Channel Control DMA Channel 5 (dmac0_ns: 0x00000000 dmac0_s: 0x00800200 )",
            handles.bportS,
            0x4a8,
            4,
            read_32,
            bportS_abS_CCR5_maskWrite,
            view32,
            &(bportS_abS_data.CCR5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_LC0_5",
            "Loop Counter 0 DMA Channel 5",
            handles.bportS,
            0x4ac,
            4,
            read_32,
            bportS_abS_LC0_5_maskWrite,
            view32,
            &(bportS_abS_data.LC0_5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_LC1_5",
            "Loop Counter 1 DMA Channel 5",
            handles.bportS,
            0x4b0,
            4,
            read_32,
            bportS_abS_LC1_5_maskWrite,
            view32,
            &(bportS_abS_data.LC1_5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_SAR6",
            "Source Address DMA Channel 6",
            handles.bportS,
            0x4c0,
            4,
            read_32,
            bportS_abS_SAR6_maskWrite,
            view32,
            &(bportS_abS_data.SAR6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_DAR6",
            "Destination Addr DMA Channel 6",
            handles.bportS,
            0x4c4,
            4,
            read_32,
            bportS_abS_DAR6_maskWrite,
            view32,
            &(bportS_abS_data.DAR6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CCR6",
            "Channel Control DMA Channel 6 (dmac0_ns: 0x00000000 dmac0_s: 0x00800200 )",
            handles.bportS,
            0x4c8,
            4,
            read_32,
            bportS_abS_CCR6_maskWrite,
            view32,
            &(bportS_abS_data.CCR6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_LC0_6",
            "Loop Counter 0 DMA Channel 6",
            handles.bportS,
            0x4cc,
            4,
            read_32,
            bportS_abS_LC0_6_maskWrite,
            view32,
            &(bportS_abS_data.LC0_6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_LC1_6",
            "Loop Counter 1 DMA Channel 6",
            handles.bportS,
            0x4d0,
            4,
            read_32,
            bportS_abS_LC1_6_maskWrite,
            view32,
            &(bportS_abS_data.LC1_6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_SAR7",
            "Source Address DMA Channel 7",
            handles.bportS,
            0x4e0,
            4,
            read_32,
            bportS_abS_SAR7_maskWrite,
            view32,
            &(bportS_abS_data.SAR7.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_DAR7",
            "Destination Addr DMA Channel 7",
            handles.bportS,
            0x4e4,
            4,
            read_32,
            bportS_abS_DAR7_maskWrite,
            view32,
            &(bportS_abS_data.DAR7.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CCR7",
            "Channel Control DMA Channel 7 (dmac0_ns: 0x00000000 dmac0_s: 0x00800200 )",
            handles.bportS,
            0x4e8,
            4,
            read_32,
            bportS_abS_CCR7_maskWrite,
            view32,
            &(bportS_abS_data.CCR7.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_LC0_7",
            "Loop Counter 0 DMA Channel 7",
            handles.bportS,
            0x4ec,
            4,
            read_32,
            bportS_abS_LC0_7_maskWrite,
            view32,
            &(bportS_abS_data.LC0_7.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_LC1_7",
            "Loop Counter 1 DMA Channel 7",
            handles.bportS,
            0x4f0,
            4,
            read_32,
            bportS_abS_LC1_7_maskWrite,
            view32,
            &(bportS_abS_data.LC1_7.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_DBGSTATUS",
            "DMA Manager Execution Status",
            handles.bportS,
            0xd00,
            4,
            read_32,
            bportS_abS_DBGSTATUS_maskWrite,
            view32,
            &(bportS_abS_data.DBGSTATUS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_DBGCMD",
            "DMA Manager Instr. command ",
            handles.bportS,
            0xd04,
            4,
            read_32,
            bportS_abS_DBGCMD_maskWrite,
            view32,
            &(bportS_abS_data.DBGCMD.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_DBGINST0",
            "DMA Manager Instruction Part A",
            handles.bportS,
            0xd08,
            4,
            read_32,
            bportS_abS_DBGINST0_maskWrite,
            view32,
            &(bportS_abS_data.DBGINST0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_DBGINST1",
            "DMA Manager Instruction Part B",
            handles.bportS,
            0xd0c,
            4,
            read_32,
            bportS_abS_DBGINST1_maskWrite,
            view32,
            &(bportS_abS_data.DBGINST1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CR0",
            "Config. 0: Events, Peripheral Interfaces, PC, Mode (dmac0_ns: 0x00000000 dmac0_s: 0x001E3071 )",
            handles.bportS,
            0xe00,
            4,
            read_32,
            bportS_abS_CR0_maskWrite,
            view32,
            &(bportS_abS_data.CR0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CR1",
            "Config. 1: Instruction Cache (dmac0_ns: 0x00000000 dmac0_s: 0x00000074 )",
            handles.bportS,
            0xe04,
            4,
            read_32,
            bportS_abS_CR1_maskWrite,
            view32,
            &(bportS_abS_data.CR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CR2",
            "Config. 2: DMA Mgr Boot Addr",
            handles.bportS,
            0xe08,
            4,
            read_32,
            bportS_abS_CR2_maskWrite,
            view32,
            &(bportS_abS_data.CR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CR3",
            "Config. 3: Security state of IRQs",
            handles.bportS,
            0xe0c,
            4,
            read_32,
            bportS_abS_CR3_maskWrite,
            view32,
            &(bportS_abS_data.CR3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CR4",
            "Config 4, Security of Periph Interfaces",
            handles.bportS,
            0xe10,
            4,
            read_32,
            bportS_abS_CR4_maskWrite,
            view32,
            &(bportS_abS_data.CR4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_CRD",
            "DMA configuration (dmac0_ns: 0x00000000 dmac0_s: 0x07FF7F73 )",
            handles.bportS,
            0xe14,
            4,
            read_32,
            bportS_abS_CRD_maskWrite,
            view32,
            &(bportS_abS_data.CRD.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_WD",
            "Watchdog Timer",
            handles.bportS,
            0xe80,
            4,
            read_32,
            bportS_abS_WD_maskWrite,
            view32,
            &(bportS_abS_data.WD.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_periph_id_0",
            "Peripheral Identification register 0 (dmac0_ns: 0x00000000 dmac0_s: 0x00000030 )",
            handles.bportS,
            0xfe0,
            4,
            read_32,
            bportS_abS_periph_id_0_maskWrite,
            view32,
            &(bportS_abS_data.periph_id_0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_periph_id_1",
            "Peripheral Identification register 1 (dmac0_ns: 0x00000000 dmac0_s: 0x00000013 )",
            handles.bportS,
            0xfe4,
            4,
            read_32,
            bportS_abS_periph_id_1_maskWrite,
            view32,
            &(bportS_abS_data.periph_id_1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_periph_id_2",
            "Peripheral Identification register 2 (dmac0_ns: 0x00000000 dmac0_s: 0x00000024 )",
            handles.bportS,
            0xfe8,
            4,
            read_32,
            bportS_abS_periph_id_2_maskWrite,
            view32,
            &(bportS_abS_data.periph_id_2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_periph_id_3",
            "Peripheral Identification register 3",
            handles.bportS,
            0xfec,
            4,
            read_32,
            bportS_abS_periph_id_3_maskWrite,
            view32,
            &(bportS_abS_data.periph_id_3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_pcell_id_0",
            "Component Identification register 0 (dmac0_ns: 0x00000000 dmac0_s: 0x0000000D)",
            handles.bportS,
            0xff0,
            4,
            read_32,
            bportS_abS_pcell_id_0_maskWrite,
            view32,
            &(bportS_abS_data.pcell_id_0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_pcell_id_1",
            "Component Identification register 1 (dmac0_ns: 0x00000000 dmac0_s: 0x000000F0)",
            handles.bportS,
            0xff4,
            4,
            read_32,
            bportS_abS_pcell_id_1_maskWrite,
            view32,
            &(bportS_abS_data.pcell_id_1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_pcell_id_2",
            "Component Identification register 2 (dmac0_ns: 0x00000000 dmac0_s: 0x00000005)",
            handles.bportS,
            0xff8,
            4,
            read_32,
            bportS_abS_pcell_id_2_maskWrite,
            view32,
            &(bportS_abS_data.pcell_id_2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abS_pcell_id_3",
            "Component Identification register 3 (dmac0_ns: 0x00000000 dmac0_s: 0x000000B1)",
            handles.bportS,
            0xffc,
            4,
            read_32,
            bportS_abS_pcell_id_3_maskWrite,
            view32,
            &(bportS_abS_data.pcell_id_3.value),
            True
        );
    }

    {
        ppmCreateRegister(
            "abNS_DSR",
            "DMA Manager Status",
            handles.bportNS,
            0x0,
            4,
            read_32,
            bportNS_abNS_DSR_maskWrite,
            view32,
            &(bportNS_abNS_data.DSR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_DPC",
            "DMA Program Counter",
            handles.bportNS,
            0x4,
            4,
            read_32,
            bportNS_abNS_DPC_maskWrite,
            view32,
            &(bportNS_abNS_data.DPC.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_INTEN",
            "DMASEV Instruction Response Control",
            handles.bportNS,
            0x20,
            4,
            read_32,
            bportNS_abNS_INTEN_maskWrite,
            view32,
            &(bportNS_abNS_data.INTEN.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_INT_EVENT_RIS",
            "Event Interrupt Raw Status",
            handles.bportNS,
            0x24,
            4,
            read_32,
            bportNS_abNS_INT_EVENT_RIS_maskWrite,
            view32,
            &(bportNS_abNS_data.INT_EVENT_RIS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_INTMIS",
            "Interrupt Status",
            handles.bportNS,
            0x28,
            4,
            read_32,
            bportNS_abNS_INTMIS_maskWrite,
            view32,
            &(bportNS_abNS_data.INTMIS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_INTCLR",
            "Interrupt Clear",
            handles.bportNS,
            0x2c,
            4,
            read_32,
            bportNS_abNS_INTCLR_maskWrite,
            view32,
            &(bportNS_abNS_data.INTCLR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_FSRD",
            "Fault Status DMA Manager",
            handles.bportNS,
            0x30,
            4,
            read_32,
            bportNS_abNS_FSRD_maskWrite,
            view32,
            &(bportNS_abNS_data.FSRD.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_FSRC",
            "Fault Status DMA Channel",
            handles.bportNS,
            0x34,
            4,
            read_32,
            bportNS_abNS_FSRC_maskWrite,
            view32,
            &(bportNS_abNS_data.FSRC.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_FTRD",
            "Fault Type DMA Manager",
            handles.bportNS,
            0x38,
            4,
            read_32,
            bportNS_abNS_FTRD_maskWrite,
            view32,
            &(bportNS_abNS_data.FTRD.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_FTR0",
            "Default Type DMA Channel 0",
            handles.bportNS,
            0x40,
            4,
            read_32,
            bportNS_abNS_FTR0_maskWrite,
            view32,
            &(bportNS_abNS_data.FTR0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_FTR1",
            "Default Type DMA Channel 1",
            handles.bportNS,
            0x44,
            4,
            read_32,
            bportNS_abNS_FTR1_maskWrite,
            view32,
            &(bportNS_abNS_data.FTR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_FTR2",
            "Default Type DMA Channel 2",
            handles.bportNS,
            0x48,
            4,
            read_32,
            bportNS_abNS_FTR2_maskWrite,
            view32,
            &(bportNS_abNS_data.FTR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_FTR3",
            "Default Type DMA Channel 3",
            handles.bportNS,
            0x4c,
            4,
            read_32,
            bportNS_abNS_FTR3_maskWrite,
            view32,
            &(bportNS_abNS_data.FTR3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_FTR4",
            "Default Type DMA Channel 4",
            handles.bportNS,
            0x50,
            4,
            read_32,
            bportNS_abNS_FTR4_maskWrite,
            view32,
            &(bportNS_abNS_data.FTR4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_FTR5",
            "Default Type DMA Channel 5",
            handles.bportNS,
            0x54,
            4,
            read_32,
            bportNS_abNS_FTR5_maskWrite,
            view32,
            &(bportNS_abNS_data.FTR5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_FTR6",
            "Default Type DMA Channel 6",
            handles.bportNS,
            0x58,
            4,
            read_32,
            bportNS_abNS_FTR6_maskWrite,
            view32,
            &(bportNS_abNS_data.FTR6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_FTR7",
            "Default Type DMA Channel 7",
            handles.bportNS,
            0x5c,
            4,
            read_32,
            bportNS_abNS_FTR7_maskWrite,
            view32,
            &(bportNS_abNS_data.FTR7.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CSR0",
            "Channel Status DMA Channel 0",
            handles.bportNS,
            0x100,
            4,
            read_32,
            bportNS_abNS_CSR0_maskWrite,
            view32,
            &(bportNS_abNS_data.CSR0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CPC0",
            "Channel PC for DMA Channel 0",
            handles.bportNS,
            0x104,
            4,
            read_32,
            bportNS_abNS_CPC0_maskWrite,
            view32,
            &(bportNS_abNS_data.CPC0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CSR1",
            "Channel Status DMA Channel 1",
            handles.bportNS,
            0x108,
            4,
            read_32,
            bportNS_abNS_CSR1_maskWrite,
            view32,
            &(bportNS_abNS_data.CSR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CPC1",
            "Channel PC for DMA Channel 1",
            handles.bportNS,
            0x10c,
            4,
            read_32,
            bportNS_abNS_CPC1_maskWrite,
            view32,
            &(bportNS_abNS_data.CPC1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CSR2",
            "Channel Status DMA Channel 2",
            handles.bportNS,
            0x110,
            4,
            read_32,
            bportNS_abNS_CSR2_maskWrite,
            view32,
            &(bportNS_abNS_data.CSR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CPC2",
            "Channel PC for DMA Channel 2",
            handles.bportNS,
            0x114,
            4,
            read_32,
            bportNS_abNS_CPC2_maskWrite,
            view32,
            &(bportNS_abNS_data.CPC2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CSR3",
            "Channel Status DMA Channel 3",
            handles.bportNS,
            0x118,
            4,
            read_32,
            bportNS_abNS_CSR3_maskWrite,
            view32,
            &(bportNS_abNS_data.CSR3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CPC3",
            "Channel PC for DMA Channel 3",
            handles.bportNS,
            0x11c,
            4,
            read_32,
            bportNS_abNS_CPC3_maskWrite,
            view32,
            &(bportNS_abNS_data.CPC3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CSR4",
            "Channel Status DMA Channel 4",
            handles.bportNS,
            0x120,
            4,
            read_32,
            bportNS_abNS_CSR4_maskWrite,
            view32,
            &(bportNS_abNS_data.CSR4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CPC4",
            "Channel PC for DMA Channel 4",
            handles.bportNS,
            0x124,
            4,
            read_32,
            bportNS_abNS_CPC4_maskWrite,
            view32,
            &(bportNS_abNS_data.CPC4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CSR5",
            "Channel Status DMA Channel 5",
            handles.bportNS,
            0x128,
            4,
            read_32,
            bportNS_abNS_CSR5_maskWrite,
            view32,
            &(bportNS_abNS_data.CSR5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CPC5",
            "Channel PC for DMA Channel 5",
            handles.bportNS,
            0x12c,
            4,
            read_32,
            bportNS_abNS_CPC5_maskWrite,
            view32,
            &(bportNS_abNS_data.CPC5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CSR6",
            "Channel Status DMA Channel 6",
            handles.bportNS,
            0x130,
            4,
            read_32,
            bportNS_abNS_CSR6_maskWrite,
            view32,
            &(bportNS_abNS_data.CSR6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CPC6",
            "Channel PC for DMA Channel 6",
            handles.bportNS,
            0x134,
            4,
            read_32,
            bportNS_abNS_CPC6_maskWrite,
            view32,
            &(bportNS_abNS_data.CPC6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CSR7",
            "Channel Status DMA Channel 7",
            handles.bportNS,
            0x138,
            4,
            read_32,
            bportNS_abNS_CSR7_maskWrite,
            view32,
            &(bportNS_abNS_data.CSR7.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CPC7",
            "Channel PC for DMA Channel 7",
            handles.bportNS,
            0x13c,
            4,
            read_32,
            bportNS_abNS_CPC7_maskWrite,
            view32,
            &(bportNS_abNS_data.CPC7.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_SAR0",
            "Source Address DMA Channel 0",
            handles.bportNS,
            0x400,
            4,
            read_32,
            bportNS_abNS_SAR0_maskWrite,
            view32,
            &(bportNS_abNS_data.SAR0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_DAR0",
            "Destination Addr DMA Channel 0",
            handles.bportNS,
            0x404,
            4,
            read_32,
            bportNS_abNS_DAR0_maskWrite,
            view32,
            &(bportNS_abNS_data.DAR0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CCR0",
            "Channel Control DMA Channel 0 (dmac0_ns: 0x00000000 dmac0_s: 0x00800200)",
            handles.bportNS,
            0x408,
            4,
            read_32,
            bportNS_abNS_CCR0_maskWrite,
            view32,
            &(bportNS_abNS_data.CCR0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_LC0_0",
            "Loop Counter 0 DMA Channel 0",
            handles.bportNS,
            0x40c,
            4,
            read_32,
            bportNS_abNS_LC0_0_maskWrite,
            view32,
            &(bportNS_abNS_data.LC0_0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_LC1_0",
            "Loop Counter 1 DMA Channel 0",
            handles.bportNS,
            0x410,
            4,
            read_32,
            bportNS_abNS_LC1_0_maskWrite,
            view32,
            &(bportNS_abNS_data.LC1_0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_SAR1",
            "Source address DMA Channel 1",
            handles.bportNS,
            0x420,
            4,
            read_32,
            bportNS_abNS_SAR1_maskWrite,
            view32,
            &(bportNS_abNS_data.SAR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_DAR1",
            "Destination Addr DMA Channel 1",
            handles.bportNS,
            0x424,
            4,
            read_32,
            bportNS_abNS_DAR1_maskWrite,
            view32,
            &(bportNS_abNS_data.DAR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CCR1",
            "Channel Control DMA Channel 1 (dmac0_ns: 0x00000000 dmac0_s: 0x00800200 )",
            handles.bportNS,
            0x428,
            4,
            read_32,
            bportNS_abNS_CCR1_maskWrite,
            view32,
            &(bportNS_abNS_data.CCR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_LC0_1",
            "Loop Counter 0 DMA Channel 1",
            handles.bportNS,
            0x42c,
            4,
            read_32,
            bportNS_abNS_LC0_1_maskWrite,
            view32,
            &(bportNS_abNS_data.LC0_1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_LC1_1",
            "Loop Counter 1 DMA Channel 1",
            handles.bportNS,
            0x430,
            4,
            read_32,
            bportNS_abNS_LC1_1_maskWrite,
            view32,
            &(bportNS_abNS_data.LC1_1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_SAR2",
            "Source Address DMA Channel 2",
            handles.bportNS,
            0x440,
            4,
            read_32,
            bportNS_abNS_SAR2_maskWrite,
            view32,
            &(bportNS_abNS_data.SAR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_DAR2",
            "Destination Addr DMA Channel 2",
            handles.bportNS,
            0x444,
            4,
            read_32,
            bportNS_abNS_DAR2_maskWrite,
            view32,
            &(bportNS_abNS_data.DAR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CCR2",
            "Channel Control DMA Channel 2 (dmac0_ns: 0x00000000 dmac0_s: 0x00800200 )",
            handles.bportNS,
            0x448,
            4,
            read_32,
            bportNS_abNS_CCR2_maskWrite,
            view32,
            &(bportNS_abNS_data.CCR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_LC0_2",
            "Loop Counter 0 DMA Channel 2",
            handles.bportNS,
            0x44c,
            4,
            read_32,
            bportNS_abNS_LC0_2_maskWrite,
            view32,
            &(bportNS_abNS_data.LC0_2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_LC1_2",
            "Loop Counter 1 DMA Channel 2",
            handles.bportNS,
            0x450,
            4,
            read_32,
            bportNS_abNS_LC1_2_maskWrite,
            view32,
            &(bportNS_abNS_data.LC1_2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_SAR3",
            "Source Address DMA Channel 3",
            handles.bportNS,
            0x460,
            4,
            read_32,
            bportNS_abNS_SAR3_maskWrite,
            view32,
            &(bportNS_abNS_data.SAR3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_DAR3",
            "Destination Addr DMA Channel 3",
            handles.bportNS,
            0x464,
            4,
            read_32,
            bportNS_abNS_DAR3_maskWrite,
            view32,
            &(bportNS_abNS_data.DAR3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CCR3",
            "Channel Control DMA Channel 3 (dmac0_ns: 0x00000000 dmac0_s: 0x00800200)",
            handles.bportNS,
            0x468,
            4,
            read_32,
            bportNS_abNS_CCR3_maskWrite,
            view32,
            &(bportNS_abNS_data.CCR3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_LC0_3",
            "Loop Counter 0 DMA Channel 3",
            handles.bportNS,
            0x46c,
            4,
            read_32,
            bportNS_abNS_LC0_3_maskWrite,
            view32,
            &(bportNS_abNS_data.LC0_3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_LC1_3",
            "Loop Counter 1 DMA Channel 3",
            handles.bportNS,
            0x470,
            4,
            read_32,
            bportNS_abNS_LC1_3_maskWrite,
            view32,
            &(bportNS_abNS_data.LC1_3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_SAR4",
            "Source Address DMA Channel 4",
            handles.bportNS,
            0x480,
            4,
            read_32,
            bportNS_abNS_SAR4_maskWrite,
            view32,
            &(bportNS_abNS_data.SAR4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_DAR4",
            "Destination Addr DMA Channel 4",
            handles.bportNS,
            0x484,
            4,
            read_32,
            bportNS_abNS_DAR4_maskWrite,
            view32,
            &(bportNS_abNS_data.DAR4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CCR4",
            "Channel Control DMA Channel 4 (dmac0_ns: 0x00000000 dmac0_s: 0x00800200 )",
            handles.bportNS,
            0x488,
            4,
            read_32,
            bportNS_abNS_CCR4_maskWrite,
            view32,
            &(bportNS_abNS_data.CCR4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_LC0_4",
            "Loop Counter 0 DMA Channel 4",
            handles.bportNS,
            0x48c,
            4,
            read_32,
            bportNS_abNS_LC0_4_maskWrite,
            view32,
            &(bportNS_abNS_data.LC0_4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_LC1_4",
            "Loop Counter 1 DMA Channel 4",
            handles.bportNS,
            0x490,
            4,
            read_32,
            bportNS_abNS_LC1_4_maskWrite,
            view32,
            &(bportNS_abNS_data.LC1_4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_SAR5",
            "Source Address DMA Channel 5",
            handles.bportNS,
            0x4a0,
            4,
            read_32,
            bportNS_abNS_SAR5_maskWrite,
            view32,
            &(bportNS_abNS_data.SAR5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_DAR5",
            "Destination Addr DMA Channel 5",
            handles.bportNS,
            0x4a4,
            4,
            read_32,
            bportNS_abNS_DAR5_maskWrite,
            view32,
            &(bportNS_abNS_data.DAR5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CCR5",
            "Channel Control DMA Channel 5 (dmac0_ns: 0x00000000 dmac0_s: 0x00800200 )",
            handles.bportNS,
            0x4a8,
            4,
            read_32,
            bportNS_abNS_CCR5_maskWrite,
            view32,
            &(bportNS_abNS_data.CCR5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_LC0_5",
            "Loop Counter 0 DMA Channel 5",
            handles.bportNS,
            0x4ac,
            4,
            read_32,
            bportNS_abNS_LC0_5_maskWrite,
            view32,
            &(bportNS_abNS_data.LC0_5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_LC1_5",
            "Loop Counter 1 DMA Channel 5",
            handles.bportNS,
            0x4b0,
            4,
            read_32,
            bportNS_abNS_LC1_5_maskWrite,
            view32,
            &(bportNS_abNS_data.LC1_5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_SAR6",
            "Source Address DMA Channel 6",
            handles.bportNS,
            0x4c0,
            4,
            read_32,
            bportNS_abNS_SAR6_maskWrite,
            view32,
            &(bportNS_abNS_data.SAR6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_DAR6",
            "Destination Addr DMA Channel 6",
            handles.bportNS,
            0x4c4,
            4,
            read_32,
            bportNS_abNS_DAR6_maskWrite,
            view32,
            &(bportNS_abNS_data.DAR6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CCR6",
            "Channel Control DMA Channel 6 (dmac0_ns: 0x00000000 dmac0_s: 0x00800200 )",
            handles.bportNS,
            0x4c8,
            4,
            read_32,
            bportNS_abNS_CCR6_maskWrite,
            view32,
            &(bportNS_abNS_data.CCR6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_LC0_6",
            "Loop Counter 0 DMA Channel 6",
            handles.bportNS,
            0x4cc,
            4,
            read_32,
            bportNS_abNS_LC0_6_maskWrite,
            view32,
            &(bportNS_abNS_data.LC0_6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_LC1_6",
            "Loop Counter 1 DMA Channel 6",
            handles.bportNS,
            0x4d0,
            4,
            read_32,
            bportNS_abNS_LC1_6_maskWrite,
            view32,
            &(bportNS_abNS_data.LC1_6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_SAR7",
            "Source Address DMA Channel 7",
            handles.bportNS,
            0x4e0,
            4,
            read_32,
            bportNS_abNS_SAR7_maskWrite,
            view32,
            &(bportNS_abNS_data.SAR7.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_DAR7",
            "Destination Addr DMA Channel 7",
            handles.bportNS,
            0x4e4,
            4,
            read_32,
            bportNS_abNS_DAR7_maskWrite,
            view32,
            &(bportNS_abNS_data.DAR7.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CCR7",
            "Channel Control DMA Channel 7 (dmac0_ns: 0x00000000 dmac0_s: 0x00800200 )",
            handles.bportNS,
            0x4e8,
            4,
            read_32,
            bportNS_abNS_CCR7_maskWrite,
            view32,
            &(bportNS_abNS_data.CCR7.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_LC0_7",
            "Loop Counter 0 DMA Channel 7",
            handles.bportNS,
            0x4ec,
            4,
            read_32,
            bportNS_abNS_LC0_7_maskWrite,
            view32,
            &(bportNS_abNS_data.LC0_7.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_LC1_7",
            "Loop Counter 1 DMA Channel 7",
            handles.bportNS,
            0x4f0,
            4,
            read_32,
            bportNS_abNS_LC1_7_maskWrite,
            view32,
            &(bportNS_abNS_data.LC1_7.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_DBGSTATUS",
            "DMA Manager Execution Status",
            handles.bportNS,
            0xd00,
            4,
            read_32,
            bportNS_abNS_DBGSTATUS_maskWrite,
            view32,
            &(bportNS_abNS_data.DBGSTATUS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_DBGCMD",
            "DMA Manager Instr. command ",
            handles.bportNS,
            0xd04,
            4,
            read_32,
            bportNS_abNS_DBGCMD_maskWrite,
            view32,
            &(bportNS_abNS_data.DBGCMD.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_DBGINST0",
            "DMA Manager Instruction Part A",
            handles.bportNS,
            0xd08,
            4,
            read_32,
            bportNS_abNS_DBGINST0_maskWrite,
            view32,
            &(bportNS_abNS_data.DBGINST0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_DBGINST1",
            "DMA Manager Instruction Part B",
            handles.bportNS,
            0xd0c,
            4,
            read_32,
            bportNS_abNS_DBGINST1_maskWrite,
            view32,
            &(bportNS_abNS_data.DBGINST1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CR0",
            "Config. 0: Events, Peripheral Interfaces, PC, Mode (dmac0_ns: 0x00000000 dmac0_s: 0x001E3071 )",
            handles.bportNS,
            0xe00,
            4,
            read_32,
            bportNS_abNS_CR0_maskWrite,
            view32,
            &(bportNS_abNS_data.CR0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CR1",
            "Config. 1: Instruction Cache (dmac0_ns: 0x00000000 dmac0_s: 0x00000074 )",
            handles.bportNS,
            0xe04,
            4,
            read_32,
            bportNS_abNS_CR1_maskWrite,
            view32,
            &(bportNS_abNS_data.CR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CR2",
            "Config. 2: DMA Mgr Boot Addr",
            handles.bportNS,
            0xe08,
            4,
            read_32,
            bportNS_abNS_CR2_maskWrite,
            view32,
            &(bportNS_abNS_data.CR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CR3",
            "Config. 3: Security state of IRQs",
            handles.bportNS,
            0xe0c,
            4,
            read_32,
            bportNS_abNS_CR3_maskWrite,
            view32,
            &(bportNS_abNS_data.CR3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CR4",
            "Config 4, Security of Periph Interfaces",
            handles.bportNS,
            0xe10,
            4,
            read_32,
            bportNS_abNS_CR4_maskWrite,
            view32,
            &(bportNS_abNS_data.CR4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_CRD",
            "DMA configuration (dmac0_ns: 0x00000000 dmac0_s: 0x07FF7F73 )",
            handles.bportNS,
            0xe14,
            4,
            read_32,
            bportNS_abNS_CRD_maskWrite,
            view32,
            &(bportNS_abNS_data.CRD.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_WD",
            "Watchdog Timer",
            handles.bportNS,
            0xe80,
            4,
            read_32,
            bportNS_abNS_WD_maskWrite,
            view32,
            &(bportNS_abNS_data.WD.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_periph_id_0",
            "Peripheral Identification register 0 (dmac0_ns: 0x00000000 dmac0_s: 0x00000030 )",
            handles.bportNS,
            0xfe0,
            4,
            read_32,
            bportNS_abNS_periph_id_0_maskWrite,
            view32,
            &(bportNS_abNS_data.periph_id_0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_periph_id_1",
            "Peripheral Identification register 1 (dmac0_ns: 0x00000000 dmac0_s: 0x00000013 )",
            handles.bportNS,
            0xfe4,
            4,
            read_32,
            bportNS_abNS_periph_id_1_maskWrite,
            view32,
            &(bportNS_abNS_data.periph_id_1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_periph_id_2",
            "Peripheral Identification register 2 (dmac0_ns: 0x00000000 dmac0_s: 0x00000024 )",
            handles.bportNS,
            0xfe8,
            4,
            read_32,
            bportNS_abNS_periph_id_2_maskWrite,
            view32,
            &(bportNS_abNS_data.periph_id_2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_periph_id_3",
            "Peripheral Identification register 3",
            handles.bportNS,
            0xfec,
            4,
            read_32,
            bportNS_abNS_periph_id_3_maskWrite,
            view32,
            &(bportNS_abNS_data.periph_id_3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_pcell_id_0",
            "Component Identification register 0 (dmac0_ns: 0x00000000 dmac0_s: 0x0000000D)",
            handles.bportNS,
            0xff0,
            4,
            read_32,
            bportNS_abNS_pcell_id_0_maskWrite,
            view32,
            &(bportNS_abNS_data.pcell_id_0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_pcell_id_1",
            "Component Identification register 1 (dmac0_ns: 0x00000000 dmac0_s: 0x000000F0)",
            handles.bportNS,
            0xff4,
            4,
            read_32,
            bportNS_abNS_pcell_id_1_maskWrite,
            view32,
            &(bportNS_abNS_data.pcell_id_1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_pcell_id_2",
            "Component Identification register 2 (dmac0_ns: 0x00000000 dmac0_s: 0x00000005)",
            handles.bportNS,
            0xff8,
            4,
            read_32,
            bportNS_abNS_pcell_id_2_maskWrite,
            view32,
            &(bportNS_abNS_data.pcell_id_2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abNS_pcell_id_3",
            "Component Identification register 3 (dmac0_ns: 0x00000000 dmac0_s: 0x000000B1)",
            handles.bportNS,
            0xffc,
            4,
            read_32,
            bportNS_abNS_pcell_id_3_maskWrite,
            view32,
            &(bportNS_abNS_data.pcell_id_3.value),
            True
        );
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bportNS_abNS_data.pcell_id_3.value = (Uns32)(bportNS_abNS_data.pcell_id_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.pcell_id_2.value = (Uns32)(bportNS_abNS_data.pcell_id_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.pcell_id_1.value = (Uns32)(bportNS_abNS_data.pcell_id_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.pcell_id_0.value = (Uns32)(bportNS_abNS_data.pcell_id_0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.periph_id_3.value = (Uns32)(bportNS_abNS_data.periph_id_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.periph_id_2.value = (Uns32)(bportNS_abNS_data.periph_id_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.periph_id_1.value = (Uns32)(bportNS_abNS_data.periph_id_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.periph_id_0.value = (Uns32)(bportNS_abNS_data.periph_id_0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.WD.value = (Uns32)(bportNS_abNS_data.WD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CRD.value = (Uns32)(bportNS_abNS_data.CRD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CR4.value = (Uns32)(bportNS_abNS_data.CR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CR3.value = (Uns32)(bportNS_abNS_data.CR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CR2.value = (Uns32)(bportNS_abNS_data.CR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CR1.value = (Uns32)(bportNS_abNS_data.CR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CR0.value = (Uns32)(bportNS_abNS_data.CR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.DBGINST1.value = (Uns32)(bportNS_abNS_data.DBGINST1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.DBGINST0.value = (Uns32)(bportNS_abNS_data.DBGINST0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.DBGCMD.value = (Uns32)(bportNS_abNS_data.DBGCMD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.DBGSTATUS.value = (Uns32)(bportNS_abNS_data.DBGSTATUS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.LC1_7.value = (Uns32)(bportNS_abNS_data.LC1_7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.LC0_7.value = (Uns32)(bportNS_abNS_data.LC0_7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CCR7.value = (Uns32)(bportNS_abNS_data.CCR7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.DAR7.value = (Uns32)(bportNS_abNS_data.DAR7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.SAR7.value = (Uns32)(bportNS_abNS_data.SAR7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.LC1_6.value = (Uns32)(bportNS_abNS_data.LC1_6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.LC0_6.value = (Uns32)(bportNS_abNS_data.LC0_6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CCR6.value = (Uns32)(bportNS_abNS_data.CCR6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.DAR6.value = (Uns32)(bportNS_abNS_data.DAR6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.SAR6.value = (Uns32)(bportNS_abNS_data.SAR6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.LC1_5.value = (Uns32)(bportNS_abNS_data.LC1_5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.LC0_5.value = (Uns32)(bportNS_abNS_data.LC0_5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CCR5.value = (Uns32)(bportNS_abNS_data.CCR5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.DAR5.value = (Uns32)(bportNS_abNS_data.DAR5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.SAR5.value = (Uns32)(bportNS_abNS_data.SAR5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.LC1_4.value = (Uns32)(bportNS_abNS_data.LC1_4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.LC0_4.value = (Uns32)(bportNS_abNS_data.LC0_4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CCR4.value = (Uns32)(bportNS_abNS_data.CCR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.DAR4.value = (Uns32)(bportNS_abNS_data.DAR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.SAR4.value = (Uns32)(bportNS_abNS_data.SAR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.LC1_3.value = (Uns32)(bportNS_abNS_data.LC1_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.LC0_3.value = (Uns32)(bportNS_abNS_data.LC0_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CCR3.value = (Uns32)(bportNS_abNS_data.CCR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.DAR3.value = (Uns32)(bportNS_abNS_data.DAR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.SAR3.value = (Uns32)(bportNS_abNS_data.SAR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.LC1_2.value = (Uns32)(bportNS_abNS_data.LC1_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.LC0_2.value = (Uns32)(bportNS_abNS_data.LC0_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CCR2.value = (Uns32)(bportNS_abNS_data.CCR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.DAR2.value = (Uns32)(bportNS_abNS_data.DAR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.SAR2.value = (Uns32)(bportNS_abNS_data.SAR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.LC1_1.value = (Uns32)(bportNS_abNS_data.LC1_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.LC0_1.value = (Uns32)(bportNS_abNS_data.LC0_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CCR1.value = (Uns32)(bportNS_abNS_data.CCR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.DAR1.value = (Uns32)(bportNS_abNS_data.DAR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.SAR1.value = (Uns32)(bportNS_abNS_data.SAR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.LC1_0.value = (Uns32)(bportNS_abNS_data.LC1_0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.LC0_0.value = (Uns32)(bportNS_abNS_data.LC0_0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CCR0.value = (Uns32)(bportNS_abNS_data.CCR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.DAR0.value = (Uns32)(bportNS_abNS_data.DAR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.SAR0.value = (Uns32)(bportNS_abNS_data.SAR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CPC7.value = (Uns32)(bportNS_abNS_data.CPC7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CSR7.value = (Uns32)(bportNS_abNS_data.CSR7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CPC6.value = (Uns32)(bportNS_abNS_data.CPC6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CSR6.value = (Uns32)(bportNS_abNS_data.CSR6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CPC5.value = (Uns32)(bportNS_abNS_data.CPC5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CSR5.value = (Uns32)(bportNS_abNS_data.CSR5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CPC4.value = (Uns32)(bportNS_abNS_data.CPC4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CSR4.value = (Uns32)(bportNS_abNS_data.CSR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CPC3.value = (Uns32)(bportNS_abNS_data.CPC3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CSR3.value = (Uns32)(bportNS_abNS_data.CSR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CPC2.value = (Uns32)(bportNS_abNS_data.CPC2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CSR2.value = (Uns32)(bportNS_abNS_data.CSR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CPC1.value = (Uns32)(bportNS_abNS_data.CPC1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CSR1.value = (Uns32)(bportNS_abNS_data.CSR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CPC0.value = (Uns32)(bportNS_abNS_data.CPC0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.CSR0.value = (Uns32)(bportNS_abNS_data.CSR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.FTR7.value = (Uns32)(bportNS_abNS_data.FTR7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.FTR6.value = (Uns32)(bportNS_abNS_data.FTR6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.FTR5.value = (Uns32)(bportNS_abNS_data.FTR5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.FTR4.value = (Uns32)(bportNS_abNS_data.FTR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.FTR3.value = (Uns32)(bportNS_abNS_data.FTR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.FTR2.value = (Uns32)(bportNS_abNS_data.FTR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.FTR1.value = (Uns32)(bportNS_abNS_data.FTR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.FTR0.value = (Uns32)(bportNS_abNS_data.FTR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.FTRD.value = (Uns32)(bportNS_abNS_data.FTRD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.FSRC.value = (Uns32)(bportNS_abNS_data.FSRC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.FSRD.value = (Uns32)(bportNS_abNS_data.FSRD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.INTCLR.value = (Uns32)(bportNS_abNS_data.INTCLR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.INTMIS.value = (Uns32)(bportNS_abNS_data.INTMIS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.INT_EVENT_RIS.value = (Uns32)(bportNS_abNS_data.INT_EVENT_RIS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.INTEN.value = (Uns32)(bportNS_abNS_data.INTEN.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.DPC.value = (Uns32)(bportNS_abNS_data.DPC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportNS_abNS_data.DSR.value = (Uns32)(bportNS_abNS_data.DSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.pcell_id_3.value = (Uns32)(bportS_abS_data.pcell_id_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x000000B1));
        bportS_abS_data.pcell_id_2.value = (Uns32)(bportS_abS_data.pcell_id_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000005));
        bportS_abS_data.pcell_id_1.value = (Uns32)(bportS_abS_data.pcell_id_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x000000F0));
        bportS_abS_data.pcell_id_0.value = (Uns32)(bportS_abS_data.pcell_id_0.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000000D));
        bportS_abS_data.periph_id_3.value = (Uns32)(bportS_abS_data.periph_id_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.periph_id_2.value = (Uns32)(bportS_abS_data.periph_id_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000024));
        bportS_abS_data.periph_id_1.value = (Uns32)(bportS_abS_data.periph_id_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000013));
        bportS_abS_data.periph_id_0.value = (Uns32)(bportS_abS_data.periph_id_0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000030));
        bportS_abS_data.WD.value = (Uns32)(bportS_abS_data.WD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CRD.value = (Uns32)(bportS_abS_data.CRD.value & ~(0xffffffff)) | ((0xffffffff) & (0x07FF7F73));
        bportS_abS_data.CR4.value = (Uns32)(bportS_abS_data.CR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CR3.value = (Uns32)(bportS_abS_data.CR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CR2.value = (Uns32)(bportS_abS_data.CR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CR1.value = (Uns32)(bportS_abS_data.CR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000074));
        bportS_abS_data.CR0.value = (Uns32)(bportS_abS_data.CR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x001E3071));
        bportS_abS_data.DBGINST1.value = (Uns32)(bportS_abS_data.DBGINST1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.DBGINST0.value = (Uns32)(bportS_abS_data.DBGINST0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.DBGCMD.value = (Uns32)(bportS_abS_data.DBGCMD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.DBGSTATUS.value = (Uns32)(bportS_abS_data.DBGSTATUS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.LC1_7.value = (Uns32)(bportS_abS_data.LC1_7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.LC0_7.value = (Uns32)(bportS_abS_data.LC0_7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CCR7.value = (Uns32)(bportS_abS_data.CCR7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00800200));
        bportS_abS_data.DAR7.value = (Uns32)(bportS_abS_data.DAR7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.SAR7.value = (Uns32)(bportS_abS_data.SAR7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.LC1_6.value = (Uns32)(bportS_abS_data.LC1_6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.LC0_6.value = (Uns32)(bportS_abS_data.LC0_6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CCR6.value = (Uns32)(bportS_abS_data.CCR6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00800200));
        bportS_abS_data.DAR6.value = (Uns32)(bportS_abS_data.DAR6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.SAR6.value = (Uns32)(bportS_abS_data.SAR6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.LC1_5.value = (Uns32)(bportS_abS_data.LC1_5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.LC0_5.value = (Uns32)(bportS_abS_data.LC0_5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CCR5.value = (Uns32)(bportS_abS_data.CCR5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00800200));
        bportS_abS_data.DAR5.value = (Uns32)(bportS_abS_data.DAR5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.SAR5.value = (Uns32)(bportS_abS_data.SAR5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.LC1_4.value = (Uns32)(bportS_abS_data.LC1_4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.LC0_4.value = (Uns32)(bportS_abS_data.LC0_4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CCR4.value = (Uns32)(bportS_abS_data.CCR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00800200));
        bportS_abS_data.DAR4.value = (Uns32)(bportS_abS_data.DAR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.SAR4.value = (Uns32)(bportS_abS_data.SAR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.LC1_3.value = (Uns32)(bportS_abS_data.LC1_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.LC0_3.value = (Uns32)(bportS_abS_data.LC0_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CCR3.value = (Uns32)(bportS_abS_data.CCR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00800200));
        bportS_abS_data.DAR3.value = (Uns32)(bportS_abS_data.DAR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.SAR3.value = (Uns32)(bportS_abS_data.SAR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.LC1_2.value = (Uns32)(bportS_abS_data.LC1_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.LC0_2.value = (Uns32)(bportS_abS_data.LC0_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CCR2.value = (Uns32)(bportS_abS_data.CCR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00800200));
        bportS_abS_data.DAR2.value = (Uns32)(bportS_abS_data.DAR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.SAR2.value = (Uns32)(bportS_abS_data.SAR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.LC1_1.value = (Uns32)(bportS_abS_data.LC1_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.LC0_1.value = (Uns32)(bportS_abS_data.LC0_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CCR1.value = (Uns32)(bportS_abS_data.CCR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00800200));
        bportS_abS_data.DAR1.value = (Uns32)(bportS_abS_data.DAR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.SAR1.value = (Uns32)(bportS_abS_data.SAR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.LC1_0.value = (Uns32)(bportS_abS_data.LC1_0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.LC0_0.value = (Uns32)(bportS_abS_data.LC0_0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CCR0.value = (Uns32)(bportS_abS_data.CCR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00800200));
        bportS_abS_data.DAR0.value = (Uns32)(bportS_abS_data.DAR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.SAR0.value = (Uns32)(bportS_abS_data.SAR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CPC7.value = (Uns32)(bportS_abS_data.CPC7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CSR7.value = (Uns32)(bportS_abS_data.CSR7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CPC6.value = (Uns32)(bportS_abS_data.CPC6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CSR6.value = (Uns32)(bportS_abS_data.CSR6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CPC5.value = (Uns32)(bportS_abS_data.CPC5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CSR5.value = (Uns32)(bportS_abS_data.CSR5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CPC4.value = (Uns32)(bportS_abS_data.CPC4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CSR4.value = (Uns32)(bportS_abS_data.CSR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CPC3.value = (Uns32)(bportS_abS_data.CPC3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CSR3.value = (Uns32)(bportS_abS_data.CSR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CPC2.value = (Uns32)(bportS_abS_data.CPC2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CSR2.value = (Uns32)(bportS_abS_data.CSR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CPC1.value = (Uns32)(bportS_abS_data.CPC1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CSR1.value = (Uns32)(bportS_abS_data.CSR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CPC0.value = (Uns32)(bportS_abS_data.CPC0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.CSR0.value = (Uns32)(bportS_abS_data.CSR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.FTR7.value = (Uns32)(bportS_abS_data.FTR7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.FTR6.value = (Uns32)(bportS_abS_data.FTR6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.FTR5.value = (Uns32)(bportS_abS_data.FTR5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.FTR4.value = (Uns32)(bportS_abS_data.FTR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.FTR3.value = (Uns32)(bportS_abS_data.FTR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.FTR2.value = (Uns32)(bportS_abS_data.FTR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.FTR1.value = (Uns32)(bportS_abS_data.FTR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.FTR0.value = (Uns32)(bportS_abS_data.FTR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.FTRD.value = (Uns32)(bportS_abS_data.FTRD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.FSRC.value = (Uns32)(bportS_abS_data.FSRC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.FSRD.value = (Uns32)(bportS_abS_data.FSRD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.INTCLR.value = (Uns32)(bportS_abS_data.INTCLR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.INTMIS.value = (Uns32)(bportS_abS_data.INTMIS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.INT_EVENT_RIS.value = (Uns32)(bportS_abS_data.INT_EVENT_RIS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.INTEN.value = (Uns32)(bportS_abS_data.INTEN.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.DPC.value = (Uns32)(bportS_abS_data.DPC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bportS_abS_data.DSR.value = (Uns32)(bportS_abS_data.DSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Zynq 7000 Platform DMA Controller (DMAC)");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model implements the full set of registers. There is no behavior included.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    reset_resetNet(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    destructor();
    return 0;
}


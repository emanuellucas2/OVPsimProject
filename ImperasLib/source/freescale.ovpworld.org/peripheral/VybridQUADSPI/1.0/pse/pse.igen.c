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

bport1_ab_dataT bport1_ab_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "VybridQUADSPI", "Example");
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

static PPM_WRITE_CB(bport1_ab_BFGENCR_maskWrite) {
    bport1_ab_data.BFGENCR.value = (bport1_ab_data.BFGENCR.value & BPORT1_AB_BFGENCR_WRNMASK) | (data & BPORT1_AB_BFGENCR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_BUF0CR_maskWrite) {
    bport1_ab_data.BUF0CR.value = (bport1_ab_data.BUF0CR.value & BPORT1_AB_BUF0CR_WRNMASK) | (data & BPORT1_AB_BUF0CR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_BUF0IND_maskWrite) {
    bport1_ab_data.BUF0IND.value = (bport1_ab_data.BUF0IND.value & BPORT1_AB_BUF0IND_WRNMASK) | (data & BPORT1_AB_BUF0IND_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_BUF1CR_maskWrite) {
    bport1_ab_data.BUF1CR.value = (bport1_ab_data.BUF1CR.value & BPORT1_AB_BUF1CR_WRNMASK) | (data & BPORT1_AB_BUF1CR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_BUF1IND_maskWrite) {
    bport1_ab_data.BUF1IND.value = (bport1_ab_data.BUF1IND.value & BPORT1_AB_BUF1IND_WRNMASK) | (data & BPORT1_AB_BUF1IND_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_BUF2CR_maskWrite) {
    bport1_ab_data.BUF2CR.value = (bport1_ab_data.BUF2CR.value & BPORT1_AB_BUF2CR_WRNMASK) | (data & BPORT1_AB_BUF2CR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_BUF2IND_maskWrite) {
    bport1_ab_data.BUF2IND.value = (bport1_ab_data.BUF2IND.value & BPORT1_AB_BUF2IND_WRNMASK) | (data & BPORT1_AB_BUF2IND_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_BUF3CR_maskWrite) {
    bport1_ab_data.BUF3CR.value = (bport1_ab_data.BUF3CR.value & BPORT1_AB_BUF3CR_WRNMASK) | (data & BPORT1_AB_BUF3CR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FLSHCR_maskWrite) {
    bport1_ab_data.FLSHCR.value = (bport1_ab_data.FLSHCR.value & BPORT1_AB_FLSHCR_WRNMASK) | (data & BPORT1_AB_FLSHCR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FR_maskWrite) {
    bport1_ab_data.FR.value = (bport1_ab_data.FR.value & BPORT1_AB_FR_WRNMASK) | (data & BPORT1_AB_FR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_IPCR_maskWrite) {
    bport1_ab_data.IPCR.value = (bport1_ab_data.IPCR.value & BPORT1_AB_IPCR_WRNMASK) | (data & BPORT1_AB_IPCR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT0_maskWrite) {
    bport1_ab_data.LUT0.value = (bport1_ab_data.LUT0.value & BPORT1_AB_LUT0_WRNMASK) | (data & BPORT1_AB_LUT0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT10_maskWrite) {
    bport1_ab_data.LUT10.value = (bport1_ab_data.LUT10.value & BPORT1_AB_LUT10_WRNMASK) | (data & BPORT1_AB_LUT10_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT11_maskWrite) {
    bport1_ab_data.LUT11.value = (bport1_ab_data.LUT11.value & BPORT1_AB_LUT11_WRNMASK) | (data & BPORT1_AB_LUT11_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT12_maskWrite) {
    bport1_ab_data.LUT12.value = (bport1_ab_data.LUT12.value & BPORT1_AB_LUT12_WRNMASK) | (data & BPORT1_AB_LUT12_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT13_maskWrite) {
    bport1_ab_data.LUT13.value = (bport1_ab_data.LUT13.value & BPORT1_AB_LUT13_WRNMASK) | (data & BPORT1_AB_LUT13_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT14_maskWrite) {
    bport1_ab_data.LUT14.value = (bport1_ab_data.LUT14.value & BPORT1_AB_LUT14_WRNMASK) | (data & BPORT1_AB_LUT14_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT15_maskWrite) {
    bport1_ab_data.LUT15.value = (bport1_ab_data.LUT15.value & BPORT1_AB_LUT15_WRNMASK) | (data & BPORT1_AB_LUT15_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT16_maskWrite) {
    bport1_ab_data.LUT16.value = (bport1_ab_data.LUT16.value & BPORT1_AB_LUT16_WRNMASK) | (data & BPORT1_AB_LUT16_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT17_maskWrite) {
    bport1_ab_data.LUT17.value = (bport1_ab_data.LUT17.value & BPORT1_AB_LUT17_WRNMASK) | (data & BPORT1_AB_LUT17_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT18_maskWrite) {
    bport1_ab_data.LUT18.value = (bport1_ab_data.LUT18.value & BPORT1_AB_LUT18_WRNMASK) | (data & BPORT1_AB_LUT18_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT19_maskWrite) {
    bport1_ab_data.LUT19.value = (bport1_ab_data.LUT19.value & BPORT1_AB_LUT19_WRNMASK) | (data & BPORT1_AB_LUT19_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT1_maskWrite) {
    bport1_ab_data.LUT1.value = (bport1_ab_data.LUT1.value & BPORT1_AB_LUT1_WRNMASK) | (data & BPORT1_AB_LUT1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT20_maskWrite) {
    bport1_ab_data.LUT20.value = (bport1_ab_data.LUT20.value & BPORT1_AB_LUT20_WRNMASK) | (data & BPORT1_AB_LUT20_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT21_maskWrite) {
    bport1_ab_data.LUT21.value = (bport1_ab_data.LUT21.value & BPORT1_AB_LUT21_WRNMASK) | (data & BPORT1_AB_LUT21_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT22_maskWrite) {
    bport1_ab_data.LUT22.value = (bport1_ab_data.LUT22.value & BPORT1_AB_LUT22_WRNMASK) | (data & BPORT1_AB_LUT22_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT23_maskWrite) {
    bport1_ab_data.LUT23.value = (bport1_ab_data.LUT23.value & BPORT1_AB_LUT23_WRNMASK) | (data & BPORT1_AB_LUT23_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT24_maskWrite) {
    bport1_ab_data.LUT24.value = (bport1_ab_data.LUT24.value & BPORT1_AB_LUT24_WRNMASK) | (data & BPORT1_AB_LUT24_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT25_maskWrite) {
    bport1_ab_data.LUT25.value = (bport1_ab_data.LUT25.value & BPORT1_AB_LUT25_WRNMASK) | (data & BPORT1_AB_LUT25_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT26_maskWrite) {
    bport1_ab_data.LUT26.value = (bport1_ab_data.LUT26.value & BPORT1_AB_LUT26_WRNMASK) | (data & BPORT1_AB_LUT26_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT27_maskWrite) {
    bport1_ab_data.LUT27.value = (bport1_ab_data.LUT27.value & BPORT1_AB_LUT27_WRNMASK) | (data & BPORT1_AB_LUT27_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT28_maskWrite) {
    bport1_ab_data.LUT28.value = (bport1_ab_data.LUT28.value & BPORT1_AB_LUT28_WRNMASK) | (data & BPORT1_AB_LUT28_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT29_maskWrite) {
    bport1_ab_data.LUT29.value = (bport1_ab_data.LUT29.value & BPORT1_AB_LUT29_WRNMASK) | (data & BPORT1_AB_LUT29_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT2_maskWrite) {
    bport1_ab_data.LUT2.value = (bport1_ab_data.LUT2.value & BPORT1_AB_LUT2_WRNMASK) | (data & BPORT1_AB_LUT2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT30_maskWrite) {
    bport1_ab_data.LUT30.value = (bport1_ab_data.LUT30.value & BPORT1_AB_LUT30_WRNMASK) | (data & BPORT1_AB_LUT30_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT31_maskWrite) {
    bport1_ab_data.LUT31.value = (bport1_ab_data.LUT31.value & BPORT1_AB_LUT31_WRNMASK) | (data & BPORT1_AB_LUT31_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT32_maskWrite) {
    bport1_ab_data.LUT32.value = (bport1_ab_data.LUT32.value & BPORT1_AB_LUT32_WRNMASK) | (data & BPORT1_AB_LUT32_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT33_maskWrite) {
    bport1_ab_data.LUT33.value = (bport1_ab_data.LUT33.value & BPORT1_AB_LUT33_WRNMASK) | (data & BPORT1_AB_LUT33_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT34_maskWrite) {
    bport1_ab_data.LUT34.value = (bport1_ab_data.LUT34.value & BPORT1_AB_LUT34_WRNMASK) | (data & BPORT1_AB_LUT34_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT35_maskWrite) {
    bport1_ab_data.LUT35.value = (bport1_ab_data.LUT35.value & BPORT1_AB_LUT35_WRNMASK) | (data & BPORT1_AB_LUT35_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT36_maskWrite) {
    bport1_ab_data.LUT36.value = (bport1_ab_data.LUT36.value & BPORT1_AB_LUT36_WRNMASK) | (data & BPORT1_AB_LUT36_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT37_maskWrite) {
    bport1_ab_data.LUT37.value = (bport1_ab_data.LUT37.value & BPORT1_AB_LUT37_WRNMASK) | (data & BPORT1_AB_LUT37_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT38_maskWrite) {
    bport1_ab_data.LUT38.value = (bport1_ab_data.LUT38.value & BPORT1_AB_LUT38_WRNMASK) | (data & BPORT1_AB_LUT38_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT39_maskWrite) {
    bport1_ab_data.LUT39.value = (bport1_ab_data.LUT39.value & BPORT1_AB_LUT39_WRNMASK) | (data & BPORT1_AB_LUT39_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT3_maskWrite) {
    bport1_ab_data.LUT3.value = (bport1_ab_data.LUT3.value & BPORT1_AB_LUT3_WRNMASK) | (data & BPORT1_AB_LUT3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT40_maskWrite) {
    bport1_ab_data.LUT40.value = (bport1_ab_data.LUT40.value & BPORT1_AB_LUT40_WRNMASK) | (data & BPORT1_AB_LUT40_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT41_maskWrite) {
    bport1_ab_data.LUT41.value = (bport1_ab_data.LUT41.value & BPORT1_AB_LUT41_WRNMASK) | (data & BPORT1_AB_LUT41_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT42_maskWrite) {
    bport1_ab_data.LUT42.value = (bport1_ab_data.LUT42.value & BPORT1_AB_LUT42_WRNMASK) | (data & BPORT1_AB_LUT42_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT43_maskWrite) {
    bport1_ab_data.LUT43.value = (bport1_ab_data.LUT43.value & BPORT1_AB_LUT43_WRNMASK) | (data & BPORT1_AB_LUT43_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT44_maskWrite) {
    bport1_ab_data.LUT44.value = (bport1_ab_data.LUT44.value & BPORT1_AB_LUT44_WRNMASK) | (data & BPORT1_AB_LUT44_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT45_maskWrite) {
    bport1_ab_data.LUT45.value = (bport1_ab_data.LUT45.value & BPORT1_AB_LUT45_WRNMASK) | (data & BPORT1_AB_LUT45_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT46_maskWrite) {
    bport1_ab_data.LUT46.value = (bport1_ab_data.LUT46.value & BPORT1_AB_LUT46_WRNMASK) | (data & BPORT1_AB_LUT46_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT47_maskWrite) {
    bport1_ab_data.LUT47.value = (bport1_ab_data.LUT47.value & BPORT1_AB_LUT47_WRNMASK) | (data & BPORT1_AB_LUT47_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT48_maskWrite) {
    bport1_ab_data.LUT48.value = (bport1_ab_data.LUT48.value & BPORT1_AB_LUT48_WRNMASK) | (data & BPORT1_AB_LUT48_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT49_maskWrite) {
    bport1_ab_data.LUT49.value = (bport1_ab_data.LUT49.value & BPORT1_AB_LUT49_WRNMASK) | (data & BPORT1_AB_LUT49_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT4_maskWrite) {
    bport1_ab_data.LUT4.value = (bport1_ab_data.LUT4.value & BPORT1_AB_LUT4_WRNMASK) | (data & BPORT1_AB_LUT4_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT50_maskWrite) {
    bport1_ab_data.LUT50.value = (bport1_ab_data.LUT50.value & BPORT1_AB_LUT50_WRNMASK) | (data & BPORT1_AB_LUT50_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT51_maskWrite) {
    bport1_ab_data.LUT51.value = (bport1_ab_data.LUT51.value & BPORT1_AB_LUT51_WRNMASK) | (data & BPORT1_AB_LUT51_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT52_maskWrite) {
    bport1_ab_data.LUT52.value = (bport1_ab_data.LUT52.value & BPORT1_AB_LUT52_WRNMASK) | (data & BPORT1_AB_LUT52_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT53_maskWrite) {
    bport1_ab_data.LUT53.value = (bport1_ab_data.LUT53.value & BPORT1_AB_LUT53_WRNMASK) | (data & BPORT1_AB_LUT53_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT54_maskWrite) {
    bport1_ab_data.LUT54.value = (bport1_ab_data.LUT54.value & BPORT1_AB_LUT54_WRNMASK) | (data & BPORT1_AB_LUT54_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT55_maskWrite) {
    bport1_ab_data.LUT55.value = (bport1_ab_data.LUT55.value & BPORT1_AB_LUT55_WRNMASK) | (data & BPORT1_AB_LUT55_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT56_maskWrite) {
    bport1_ab_data.LUT56.value = (bport1_ab_data.LUT56.value & BPORT1_AB_LUT56_WRNMASK) | (data & BPORT1_AB_LUT56_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT57_maskWrite) {
    bport1_ab_data.LUT57.value = (bport1_ab_data.LUT57.value & BPORT1_AB_LUT57_WRNMASK) | (data & BPORT1_AB_LUT57_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT58_maskWrite) {
    bport1_ab_data.LUT58.value = (bport1_ab_data.LUT58.value & BPORT1_AB_LUT58_WRNMASK) | (data & BPORT1_AB_LUT58_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT59_maskWrite) {
    bport1_ab_data.LUT59.value = (bport1_ab_data.LUT59.value & BPORT1_AB_LUT59_WRNMASK) | (data & BPORT1_AB_LUT59_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT5_maskWrite) {
    bport1_ab_data.LUT5.value = (bport1_ab_data.LUT5.value & BPORT1_AB_LUT5_WRNMASK) | (data & BPORT1_AB_LUT5_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT60_maskWrite) {
    bport1_ab_data.LUT60.value = (bport1_ab_data.LUT60.value & BPORT1_AB_LUT60_WRNMASK) | (data & BPORT1_AB_LUT60_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT61_maskWrite) {
    bport1_ab_data.LUT61.value = (bport1_ab_data.LUT61.value & BPORT1_AB_LUT61_WRNMASK) | (data & BPORT1_AB_LUT61_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT62_maskWrite) {
    bport1_ab_data.LUT62.value = (bport1_ab_data.LUT62.value & BPORT1_AB_LUT62_WRNMASK) | (data & BPORT1_AB_LUT62_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT63_maskWrite) {
    bport1_ab_data.LUT63.value = (bport1_ab_data.LUT63.value & BPORT1_AB_LUT63_WRNMASK) | (data & BPORT1_AB_LUT63_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT6_maskWrite) {
    bport1_ab_data.LUT6.value = (bport1_ab_data.LUT6.value & BPORT1_AB_LUT6_WRNMASK) | (data & BPORT1_AB_LUT6_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT7_maskWrite) {
    bport1_ab_data.LUT7.value = (bport1_ab_data.LUT7.value & BPORT1_AB_LUT7_WRNMASK) | (data & BPORT1_AB_LUT7_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT8_maskWrite) {
    bport1_ab_data.LUT8.value = (bport1_ab_data.LUT8.value & BPORT1_AB_LUT8_WRNMASK) | (data & BPORT1_AB_LUT8_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LUT9_maskWrite) {
    bport1_ab_data.LUT9.value = (bport1_ab_data.LUT9.value & BPORT1_AB_LUT9_WRNMASK) | (data & BPORT1_AB_LUT9_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MCR_maskWrite) {
    bport1_ab_data.MCR.value = (bport1_ab_data.MCR.value & BPORT1_AB_MCR_WRNMASK) | (data & BPORT1_AB_MCR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBCT_maskWrite) {
    bport1_ab_data.RBCT.value = (bport1_ab_data.RBCT.value & BPORT1_AB_RBCT_WRNMASK) | (data & BPORT1_AB_RBCT_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR0_maskWrite) {
    bport1_ab_data.RBDR0.value = (bport1_ab_data.RBDR0.value & BPORT1_AB_RBDR0_WRNMASK) | (data & BPORT1_AB_RBDR0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR10_maskWrite) {
    bport1_ab_data.RBDR10.value = (bport1_ab_data.RBDR10.value & BPORT1_AB_RBDR10_WRNMASK) | (data & BPORT1_AB_RBDR10_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR11_maskWrite) {
    bport1_ab_data.RBDR11.value = (bport1_ab_data.RBDR11.value & BPORT1_AB_RBDR11_WRNMASK) | (data & BPORT1_AB_RBDR11_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR12_maskWrite) {
    bport1_ab_data.RBDR12.value = (bport1_ab_data.RBDR12.value & BPORT1_AB_RBDR12_WRNMASK) | (data & BPORT1_AB_RBDR12_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR13_maskWrite) {
    bport1_ab_data.RBDR13.value = (bport1_ab_data.RBDR13.value & BPORT1_AB_RBDR13_WRNMASK) | (data & BPORT1_AB_RBDR13_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR14_maskWrite) {
    bport1_ab_data.RBDR14.value = (bport1_ab_data.RBDR14.value & BPORT1_AB_RBDR14_WRNMASK) | (data & BPORT1_AB_RBDR14_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR15_maskWrite) {
    bport1_ab_data.RBDR15.value = (bport1_ab_data.RBDR15.value & BPORT1_AB_RBDR15_WRNMASK) | (data & BPORT1_AB_RBDR15_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR16_maskWrite) {
    bport1_ab_data.RBDR16.value = (bport1_ab_data.RBDR16.value & BPORT1_AB_RBDR16_WRNMASK) | (data & BPORT1_AB_RBDR16_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR17_maskWrite) {
    bport1_ab_data.RBDR17.value = (bport1_ab_data.RBDR17.value & BPORT1_AB_RBDR17_WRNMASK) | (data & BPORT1_AB_RBDR17_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR18_maskWrite) {
    bport1_ab_data.RBDR18.value = (bport1_ab_data.RBDR18.value & BPORT1_AB_RBDR18_WRNMASK) | (data & BPORT1_AB_RBDR18_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR19_maskWrite) {
    bport1_ab_data.RBDR19.value = (bport1_ab_data.RBDR19.value & BPORT1_AB_RBDR19_WRNMASK) | (data & BPORT1_AB_RBDR19_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR1_maskWrite) {
    bport1_ab_data.RBDR1.value = (bport1_ab_data.RBDR1.value & BPORT1_AB_RBDR1_WRNMASK) | (data & BPORT1_AB_RBDR1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR20_maskWrite) {
    bport1_ab_data.RBDR20.value = (bport1_ab_data.RBDR20.value & BPORT1_AB_RBDR20_WRNMASK) | (data & BPORT1_AB_RBDR20_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR21_maskWrite) {
    bport1_ab_data.RBDR21.value = (bport1_ab_data.RBDR21.value & BPORT1_AB_RBDR21_WRNMASK) | (data & BPORT1_AB_RBDR21_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR22_maskWrite) {
    bport1_ab_data.RBDR22.value = (bport1_ab_data.RBDR22.value & BPORT1_AB_RBDR22_WRNMASK) | (data & BPORT1_AB_RBDR22_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR23_maskWrite) {
    bport1_ab_data.RBDR23.value = (bport1_ab_data.RBDR23.value & BPORT1_AB_RBDR23_WRNMASK) | (data & BPORT1_AB_RBDR23_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR24_maskWrite) {
    bport1_ab_data.RBDR24.value = (bport1_ab_data.RBDR24.value & BPORT1_AB_RBDR24_WRNMASK) | (data & BPORT1_AB_RBDR24_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR25_maskWrite) {
    bport1_ab_data.RBDR25.value = (bport1_ab_data.RBDR25.value & BPORT1_AB_RBDR25_WRNMASK) | (data & BPORT1_AB_RBDR25_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR26_maskWrite) {
    bport1_ab_data.RBDR26.value = (bport1_ab_data.RBDR26.value & BPORT1_AB_RBDR26_WRNMASK) | (data & BPORT1_AB_RBDR26_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR27_maskWrite) {
    bport1_ab_data.RBDR27.value = (bport1_ab_data.RBDR27.value & BPORT1_AB_RBDR27_WRNMASK) | (data & BPORT1_AB_RBDR27_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR28_maskWrite) {
    bport1_ab_data.RBDR28.value = (bport1_ab_data.RBDR28.value & BPORT1_AB_RBDR28_WRNMASK) | (data & BPORT1_AB_RBDR28_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR29_maskWrite) {
    bport1_ab_data.RBDR29.value = (bport1_ab_data.RBDR29.value & BPORT1_AB_RBDR29_WRNMASK) | (data & BPORT1_AB_RBDR29_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR2_maskWrite) {
    bport1_ab_data.RBDR2.value = (bport1_ab_data.RBDR2.value & BPORT1_AB_RBDR2_WRNMASK) | (data & BPORT1_AB_RBDR2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR30_maskWrite) {
    bport1_ab_data.RBDR30.value = (bport1_ab_data.RBDR30.value & BPORT1_AB_RBDR30_WRNMASK) | (data & BPORT1_AB_RBDR30_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR31_maskWrite) {
    bport1_ab_data.RBDR31.value = (bport1_ab_data.RBDR31.value & BPORT1_AB_RBDR31_WRNMASK) | (data & BPORT1_AB_RBDR31_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR32_maskWrite) {
    bport1_ab_data.RBDR32.value = (bport1_ab_data.RBDR32.value & BPORT1_AB_RBDR32_WRNMASK) | (data & BPORT1_AB_RBDR32_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR33_maskWrite) {
    bport1_ab_data.RBDR33.value = (bport1_ab_data.RBDR33.value & BPORT1_AB_RBDR33_WRNMASK) | (data & BPORT1_AB_RBDR33_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR34_maskWrite) {
    bport1_ab_data.RBDR34.value = (bport1_ab_data.RBDR34.value & BPORT1_AB_RBDR34_WRNMASK) | (data & BPORT1_AB_RBDR34_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR35_maskWrite) {
    bport1_ab_data.RBDR35.value = (bport1_ab_data.RBDR35.value & BPORT1_AB_RBDR35_WRNMASK) | (data & BPORT1_AB_RBDR35_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR36_maskWrite) {
    bport1_ab_data.RBDR36.value = (bport1_ab_data.RBDR36.value & BPORT1_AB_RBDR36_WRNMASK) | (data & BPORT1_AB_RBDR36_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR37_maskWrite) {
    bport1_ab_data.RBDR37.value = (bport1_ab_data.RBDR37.value & BPORT1_AB_RBDR37_WRNMASK) | (data & BPORT1_AB_RBDR37_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR38_maskWrite) {
    bport1_ab_data.RBDR38.value = (bport1_ab_data.RBDR38.value & BPORT1_AB_RBDR38_WRNMASK) | (data & BPORT1_AB_RBDR38_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR39_maskWrite) {
    bport1_ab_data.RBDR39.value = (bport1_ab_data.RBDR39.value & BPORT1_AB_RBDR39_WRNMASK) | (data & BPORT1_AB_RBDR39_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR3_maskWrite) {
    bport1_ab_data.RBDR3.value = (bport1_ab_data.RBDR3.value & BPORT1_AB_RBDR3_WRNMASK) | (data & BPORT1_AB_RBDR3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR40_maskWrite) {
    bport1_ab_data.RBDR40.value = (bport1_ab_data.RBDR40.value & BPORT1_AB_RBDR40_WRNMASK) | (data & BPORT1_AB_RBDR40_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR41_maskWrite) {
    bport1_ab_data.RBDR41.value = (bport1_ab_data.RBDR41.value & BPORT1_AB_RBDR41_WRNMASK) | (data & BPORT1_AB_RBDR41_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR42_maskWrite) {
    bport1_ab_data.RBDR42.value = (bport1_ab_data.RBDR42.value & BPORT1_AB_RBDR42_WRNMASK) | (data & BPORT1_AB_RBDR42_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR43_maskWrite) {
    bport1_ab_data.RBDR43.value = (bport1_ab_data.RBDR43.value & BPORT1_AB_RBDR43_WRNMASK) | (data & BPORT1_AB_RBDR43_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR44_maskWrite) {
    bport1_ab_data.RBDR44.value = (bport1_ab_data.RBDR44.value & BPORT1_AB_RBDR44_WRNMASK) | (data & BPORT1_AB_RBDR44_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR45_maskWrite) {
    bport1_ab_data.RBDR45.value = (bport1_ab_data.RBDR45.value & BPORT1_AB_RBDR45_WRNMASK) | (data & BPORT1_AB_RBDR45_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR46_maskWrite) {
    bport1_ab_data.RBDR46.value = (bport1_ab_data.RBDR46.value & BPORT1_AB_RBDR46_WRNMASK) | (data & BPORT1_AB_RBDR46_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR47_maskWrite) {
    bport1_ab_data.RBDR47.value = (bport1_ab_data.RBDR47.value & BPORT1_AB_RBDR47_WRNMASK) | (data & BPORT1_AB_RBDR47_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR48_maskWrite) {
    bport1_ab_data.RBDR48.value = (bport1_ab_data.RBDR48.value & BPORT1_AB_RBDR48_WRNMASK) | (data & BPORT1_AB_RBDR48_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR49_maskWrite) {
    bport1_ab_data.RBDR49.value = (bport1_ab_data.RBDR49.value & BPORT1_AB_RBDR49_WRNMASK) | (data & BPORT1_AB_RBDR49_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR4_maskWrite) {
    bport1_ab_data.RBDR4.value = (bport1_ab_data.RBDR4.value & BPORT1_AB_RBDR4_WRNMASK) | (data & BPORT1_AB_RBDR4_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR50_maskWrite) {
    bport1_ab_data.RBDR50.value = (bport1_ab_data.RBDR50.value & BPORT1_AB_RBDR50_WRNMASK) | (data & BPORT1_AB_RBDR50_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR51_maskWrite) {
    bport1_ab_data.RBDR51.value = (bport1_ab_data.RBDR51.value & BPORT1_AB_RBDR51_WRNMASK) | (data & BPORT1_AB_RBDR51_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR52_maskWrite) {
    bport1_ab_data.RBDR52.value = (bport1_ab_data.RBDR52.value & BPORT1_AB_RBDR52_WRNMASK) | (data & BPORT1_AB_RBDR52_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR53_maskWrite) {
    bport1_ab_data.RBDR53.value = (bport1_ab_data.RBDR53.value & BPORT1_AB_RBDR53_WRNMASK) | (data & BPORT1_AB_RBDR53_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR54_maskWrite) {
    bport1_ab_data.RBDR54.value = (bport1_ab_data.RBDR54.value & BPORT1_AB_RBDR54_WRNMASK) | (data & BPORT1_AB_RBDR54_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR55_maskWrite) {
    bport1_ab_data.RBDR55.value = (bport1_ab_data.RBDR55.value & BPORT1_AB_RBDR55_WRNMASK) | (data & BPORT1_AB_RBDR55_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR56_maskWrite) {
    bport1_ab_data.RBDR56.value = (bport1_ab_data.RBDR56.value & BPORT1_AB_RBDR56_WRNMASK) | (data & BPORT1_AB_RBDR56_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR57_maskWrite) {
    bport1_ab_data.RBDR57.value = (bport1_ab_data.RBDR57.value & BPORT1_AB_RBDR57_WRNMASK) | (data & BPORT1_AB_RBDR57_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR58_maskWrite) {
    bport1_ab_data.RBDR58.value = (bport1_ab_data.RBDR58.value & BPORT1_AB_RBDR58_WRNMASK) | (data & BPORT1_AB_RBDR58_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR59_maskWrite) {
    bport1_ab_data.RBDR59.value = (bport1_ab_data.RBDR59.value & BPORT1_AB_RBDR59_WRNMASK) | (data & BPORT1_AB_RBDR59_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR5_maskWrite) {
    bport1_ab_data.RBDR5.value = (bport1_ab_data.RBDR5.value & BPORT1_AB_RBDR5_WRNMASK) | (data & BPORT1_AB_RBDR5_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR60_maskWrite) {
    bport1_ab_data.RBDR60.value = (bport1_ab_data.RBDR60.value & BPORT1_AB_RBDR60_WRNMASK) | (data & BPORT1_AB_RBDR60_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR61_maskWrite) {
    bport1_ab_data.RBDR61.value = (bport1_ab_data.RBDR61.value & BPORT1_AB_RBDR61_WRNMASK) | (data & BPORT1_AB_RBDR61_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR62_maskWrite) {
    bport1_ab_data.RBDR62.value = (bport1_ab_data.RBDR62.value & BPORT1_AB_RBDR62_WRNMASK) | (data & BPORT1_AB_RBDR62_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR63_maskWrite) {
    bport1_ab_data.RBDR63.value = (bport1_ab_data.RBDR63.value & BPORT1_AB_RBDR63_WRNMASK) | (data & BPORT1_AB_RBDR63_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR6_maskWrite) {
    bport1_ab_data.RBDR6.value = (bport1_ab_data.RBDR6.value & BPORT1_AB_RBDR6_WRNMASK) | (data & BPORT1_AB_RBDR6_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR7_maskWrite) {
    bport1_ab_data.RBDR7.value = (bport1_ab_data.RBDR7.value & BPORT1_AB_RBDR7_WRNMASK) | (data & BPORT1_AB_RBDR7_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR8_maskWrite) {
    bport1_ab_data.RBDR8.value = (bport1_ab_data.RBDR8.value & BPORT1_AB_RBDR8_WRNMASK) | (data & BPORT1_AB_RBDR8_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RBDR9_maskWrite) {
    bport1_ab_data.RBDR9.value = (bport1_ab_data.RBDR9.value & BPORT1_AB_RBDR9_WRNMASK) | (data & BPORT1_AB_RBDR9_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RSER_maskWrite) {
    bport1_ab_data.RSER.value = (bport1_ab_data.RSER.value & BPORT1_AB_RSER_WRNMASK) | (data & BPORT1_AB_RSER_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SFA1AD_maskWrite) {
    bport1_ab_data.SFA1AD.value = (bport1_ab_data.SFA1AD.value & BPORT1_AB_SFA1AD_WRNMASK) | (data & BPORT1_AB_SFA1AD_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SFA2AD_maskWrite) {
    bport1_ab_data.SFA2AD.value = (bport1_ab_data.SFA2AD.value & BPORT1_AB_SFA2AD_WRNMASK) | (data & BPORT1_AB_SFA2AD_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SFAR_maskWrite) {
    bport1_ab_data.SFAR.value = (bport1_ab_data.SFAR.value & BPORT1_AB_SFAR_WRNMASK) | (data & BPORT1_AB_SFAR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SFB1AD_maskWrite) {
    bport1_ab_data.SFB1AD.value = (bport1_ab_data.SFB1AD.value & BPORT1_AB_SFB1AD_WRNMASK) | (data & BPORT1_AB_SFB1AD_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SFB2AD_maskWrite) {
    bport1_ab_data.SFB2AD.value = (bport1_ab_data.SFB2AD.value & BPORT1_AB_SFB2AD_WRNMASK) | (data & BPORT1_AB_SFB2AD_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SMPR_maskWrite) {
    bport1_ab_data.SMPR.value = (bport1_ab_data.SMPR.value & BPORT1_AB_SMPR_WRNMASK) | (data & BPORT1_AB_SMPR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SPTRCLR_maskWrite) {
    bport1_ab_data.SPTRCLR.value = (bport1_ab_data.SPTRCLR.value & BPORT1_AB_SPTRCLR_WRNMASK) | (data & BPORT1_AB_SPTRCLR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TBDR_maskWrite) {
    bport1_ab_data.TBDR.value = (bport1_ab_data.TBDR.value & BPORT1_AB_TBDR_WRNMASK) | (data & BPORT1_AB_TBDR_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abMCR_reg = ppmCreateRegister(
            "ab_MCR",
            "Module Configuration Register, offset: 0x0",
            handles.bport1,
            0x0,
            4,
            read_32,
            bport1_ab_MCR_maskWrite,
            view32,
            &(bport1_ab_data.MCR.value),
            True
        );

        ppmCreateRegisterField(abMCR_reg, "CLR_RXF", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "CLR_TXF", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "DDR_EN", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "DQS_EN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "END_CFG", 0, 2, 2, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "MDIS", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "SCLKCFG", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "SWRSTHD", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "SWRSTSD", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abIPCR_reg = ppmCreateRegister(
            "ab_IPCR",
            "IP Configuration Register, offset: 0x8",
            handles.bport1,
            0x8,
            4,
            read_32,
            bport1_ab_IPCR_maskWrite,
            view32,
            &(bport1_ab_data.IPCR.value),
            True
        );

        ppmCreateRegisterField(abIPCR_reg, "IDATSZ", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(abIPCR_reg, "PAR_EN", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abIPCR_reg, "SEQID", 0, 24, 4, 1, 1);
    }
    {
        registerHandle abFLSHCR_reg = ppmCreateRegister(
            "ab_FLSHCR",
            "Flash Configuration Register, offset: 0xC",
            handles.bport1,
            0xc,
            4,
            read_32,
            bport1_ab_FLSHCR_maskWrite,
            view32,
            &(bport1_ab_data.FLSHCR.value),
            True
        );

        ppmCreateRegisterField(abFLSHCR_reg, "TCSH", 0, 8, 4, 1, 1);
        ppmCreateRegisterField(abFLSHCR_reg, "TCSS", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abBUF0CR_reg = ppmCreateRegister(
            "ab_BUF0CR",
            "Buffer0 Configuration Register, offset: 0x10",
            handles.bport1,
            0x10,
            4,
            read_32,
            bport1_ab_BUF0CR_maskWrite,
            view32,
            &(bport1_ab_data.BUF0CR.value),
            True
        );

        ppmCreateRegisterField(abBUF0CR_reg, "ADATSZ", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abBUF0CR_reg, "HP_EN", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abBUF0CR_reg, "MSTRID", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abBUF1CR_reg = ppmCreateRegister(
            "ab_BUF1CR",
            "Buffer1 Configuration Register, offset: 0x14",
            handles.bport1,
            0x14,
            4,
            read_32,
            bport1_ab_BUF1CR_maskWrite,
            view32,
            &(bport1_ab_data.BUF1CR.value),
            True
        );

        ppmCreateRegisterField(abBUF1CR_reg, "ADATSZ", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abBUF1CR_reg, "MSTRID", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abBUF2CR_reg = ppmCreateRegister(
            "ab_BUF2CR",
            "Buffer2 Configuration Register, offset: 0x18",
            handles.bport1,
            0x18,
            4,
            read_32,
            bport1_ab_BUF2CR_maskWrite,
            view32,
            &(bport1_ab_data.BUF2CR.value),
            True
        );

        ppmCreateRegisterField(abBUF2CR_reg, "ADATSZ", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abBUF2CR_reg, "MSTRID", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abBUF3CR_reg = ppmCreateRegister(
            "ab_BUF3CR",
            "Buffer3 Configuration Register, offset: 0x1C",
            handles.bport1,
            0x1c,
            4,
            read_32,
            bport1_ab_BUF3CR_maskWrite,
            view32,
            &(bport1_ab_data.BUF3CR.value),
            True
        );

        ppmCreateRegisterField(abBUF3CR_reg, "ADATSZ", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abBUF3CR_reg, "ALLMST", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abBUF3CR_reg, "MSTRID", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abBFGENCR_reg = ppmCreateRegister(
            "ab_BFGENCR",
            "Buffer Generic Configuration Register, offset: 0x20",
            handles.bport1,
            0x20,
            4,
            read_32,
            bport1_ab_BFGENCR_maskWrite,
            view32,
            &(bport1_ab_data.BFGENCR.value),
            True
        );

        ppmCreateRegisterField(abBFGENCR_reg, "PAR_EN", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abBFGENCR_reg, "SEQID", 0, 12, 4, 1, 1);
    }
    {
        registerHandle abBUF0IND_reg = ppmCreateRegister(
            "ab_BUF0IND",
            "Buffer0 Top Index Register, offset: 0x30",
            handles.bport1,
            0x30,
            4,
            read_32,
            bport1_ab_BUF0IND_maskWrite,
            view32,
            &(bport1_ab_data.BUF0IND.value),
            True
        );

        ppmCreateRegisterField(abBUF0IND_reg, "TPINDX0", 0, 3, 29, 1, 1);
    }
    {
        registerHandle abBUF1IND_reg = ppmCreateRegister(
            "ab_BUF1IND",
            "Buffer1 Top Index Register, offset: 0x34",
            handles.bport1,
            0x34,
            4,
            read_32,
            bport1_ab_BUF1IND_maskWrite,
            view32,
            &(bport1_ab_data.BUF1IND.value),
            True
        );

        ppmCreateRegisterField(abBUF1IND_reg, "TPINDX1", 0, 3, 29, 1, 1);
    }
    {
        registerHandle abBUF2IND_reg = ppmCreateRegister(
            "ab_BUF2IND",
            "Buffer2 Top Index Register, offset: 0x38",
            handles.bport1,
            0x38,
            4,
            read_32,
            bport1_ab_BUF2IND_maskWrite,
            view32,
            &(bport1_ab_data.BUF2IND.value),
            True
        );

        ppmCreateRegisterField(abBUF2IND_reg, "TPINDX2", 0, 3, 29, 1, 1);
    }
    {
        registerHandle abSFAR_reg = ppmCreateRegister(
            "ab_SFAR",
            "Serial Flash Address Register, offset: 0x100",
            handles.bport1,
            0x100,
            4,
            read_32,
            bport1_ab_SFAR_maskWrite,
            view32,
            &(bport1_ab_data.SFAR.value),
            True
        );

        ppmCreateRegisterField(abSFAR_reg, "SFADR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abSMPR_reg = ppmCreateRegister(
            "ab_SMPR",
            "Sampling Register, offset: 0x108",
            handles.bport1,
            0x108,
            4,
            read_32,
            bport1_ab_SMPR_maskWrite,
            view32,
            &(bport1_ab_data.SMPR.value),
            True
        );

        ppmCreateRegisterField(abSMPR_reg, "DDRSMP", 0, 16, 3, 1, 1);
        ppmCreateRegisterField(abSMPR_reg, "FSDLY", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abSMPR_reg, "FSPHS", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abSMPR_reg, "HSDLY", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abSMPR_reg, "HSENA", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abSMPR_reg, "HSPHS", 0, 1, 1, 1, 1);
    }
    {
        registerHandle abRBSR_reg = ppmCreateRegister(
            "ab_RBSR",
            "RX Buffer Status Register, offset: 0x10C",
            handles.bport1,
            0x10c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.RBSR.value),
            True
        );

        ppmCreateRegisterField(abRBSR_reg, "RDBFL", 0, 8, 6, 1, 0);
        ppmCreateRegisterField(abRBSR_reg, "RDCTR", 0, 16, 16, 1, 0);
    }
    {
        registerHandle abRBCT_reg = ppmCreateRegister(
            "ab_RBCT",
            "RX Buffer Control Register, offset: 0x110",
            handles.bport1,
            0x110,
            4,
            read_32,
            bport1_ab_RBCT_maskWrite,
            view32,
            &(bport1_ab_data.RBCT.value),
            True
        );

        ppmCreateRegisterField(abRBCT_reg, "RXBRD", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abRBCT_reg, "WMRK", 0, 0, 5, 1, 1);
    }
    {
        registerHandle abTBSR_reg = ppmCreateRegister(
            "ab_TBSR",
            "TX Buffer Status Register, offset: 0x150",
            handles.bport1,
            0x150,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.TBSR.value),
            True
        );

        ppmCreateRegisterField(abTBSR_reg, "TRBFL", 0, 8, 5, 1, 0);
        ppmCreateRegisterField(abTBSR_reg, "TRCTR", 0, 16, 16, 1, 0);
    }
    {
        registerHandle abTBDR_reg = ppmCreateRegister(
            "ab_TBDR",
            "TX Buffer Data Register, offset: 0x154",
            handles.bport1,
            0x154,
            4,
            read_32,
            bport1_ab_TBDR_maskWrite,
            view32,
            &(bport1_ab_data.TBDR.value),
            True
        );

        ppmCreateRegisterField(abTBDR_reg, "TXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abSR_reg = ppmCreateRegister(
            "ab_SR",
            "Status Register, offset: 0x15C",
            handles.bport1,
            0x15c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.SR.value),
            True
        );

        ppmCreateRegisterField(abSR_reg, "AHB0FUL", 0, 11, 1, 1, 0);
        ppmCreateRegisterField(abSR_reg, "AHB0NE", 0, 7, 1, 1, 0);
        ppmCreateRegisterField(abSR_reg, "AHB1FUL", 0, 12, 1, 1, 0);
        ppmCreateRegisterField(abSR_reg, "AHB1NE", 0, 8, 1, 1, 0);
        ppmCreateRegisterField(abSR_reg, "AHB2FUL", 0, 13, 1, 1, 0);
        ppmCreateRegisterField(abSR_reg, "AHB2NE", 0, 9, 1, 1, 0);
        ppmCreateRegisterField(abSR_reg, "AHB3FUL", 0, 14, 1, 1, 0);
        ppmCreateRegisterField(abSR_reg, "AHB3NE", 0, 10, 1, 1, 0);
        ppmCreateRegisterField(abSR_reg, "AHB_ACC", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(abSR_reg, "AHBGNT", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(abSR_reg, "AHBTRN", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(abSR_reg, "BUSY", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(abSR_reg, "DLPSMP", 0, 29, 3, 1, 0);
        ppmCreateRegisterField(abSR_reg, "IP_ACC", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(abSR_reg, "RXDMA", 0, 23, 1, 1, 0);
        ppmCreateRegisterField(abSR_reg, "RXFULL", 0, 19, 1, 1, 0);
        ppmCreateRegisterField(abSR_reg, "RXWE", 0, 16, 1, 1, 0);
        ppmCreateRegisterField(abSR_reg, "TXFULL", 0, 27, 1, 1, 0);
        ppmCreateRegisterField(abSR_reg, "TXNE", 0, 24, 1, 1, 0);
    }
    {
        registerHandle abFR_reg = ppmCreateRegister(
            "ab_FR",
            "Flag Register, offset: 0x160",
            handles.bport1,
            0x160,
            4,
            read_32,
            bport1_ab_FR_maskWrite,
            view32,
            &(bport1_ab_data.FR.value),
            True
        );

        ppmCreateRegisterField(abFR_reg, "ABOF", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abFR_reg, "ABSEF", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abFR_reg, "DLPFF", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abFR_reg, "ILLINE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abFR_reg, "IPAEF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abFR_reg, "IPGEF", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abFR_reg, "IPIEF", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abFR_reg, "IUEF", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abFR_reg, "RBDF", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abFR_reg, "RBOF", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abFR_reg, "TBFF", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(abFR_reg, "TBUF", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abFR_reg, "TFF", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abRSER_reg = ppmCreateRegister(
            "ab_RSER",
            "Interrupt and DMA Request Select and Enable Register, offset: 0x164",
            handles.bport1,
            0x164,
            4,
            read_32,
            bport1_ab_RSER_maskWrite,
            view32,
            &(bport1_ab_data.RSER.value),
            True
        );

        ppmCreateRegisterField(abRSER_reg, "ABOIE", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abRSER_reg, "ABSEIE", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abRSER_reg, "DLPFIE", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abRSER_reg, "ILLINIE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abRSER_reg, "IPAEIE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abRSER_reg, "IPGEIE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abRSER_reg, "IPIEIE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abRSER_reg, "IUEIE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abRSER_reg, "RBDDE", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abRSER_reg, "RBDIE", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abRSER_reg, "RBOIE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abRSER_reg, "TBFIE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(abRSER_reg, "TBUIE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abRSER_reg, "TFIE", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abSPNDST_reg = ppmCreateRegister(
            "ab_SPNDST",
            "Sequence Suspend Status Register, offset: 0x168",
            handles.bport1,
            0x168,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.SPNDST.value),
            True
        );

        ppmCreateRegisterField(abSPNDST_reg, "DATLFT", 0, 9, 7, 1, 0);
        ppmCreateRegisterField(abSPNDST_reg, "SPDBUF", 0, 6, 2, 1, 0);
        ppmCreateRegisterField(abSPNDST_reg, "SUSPND", 0, 0, 1, 1, 0);
    }
    {
        registerHandle abSPTRCLR_reg = ppmCreateRegister(
            "ab_SPTRCLR",
            "Sequence Pointer Clear Register, offset: 0x16C",
            handles.bport1,
            0x16c,
            4,
            read_32,
            bport1_ab_SPTRCLR_maskWrite,
            view32,
            &(bport1_ab_data.SPTRCLR.value),
            True
        );

        ppmCreateRegisterField(abSPTRCLR_reg, "BFPTRC", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abSPTRCLR_reg, "IPPTRC", 0, 8, 1, 1, 1);
    }
    {
        registerHandle abSFA1AD_reg = ppmCreateRegister(
            "ab_SFA1AD",
            "Serial Flash A1 Top Address, offset: 0x180",
            handles.bport1,
            0x180,
            4,
            read_32,
            bport1_ab_SFA1AD_maskWrite,
            view32,
            &(bport1_ab_data.SFA1AD.value),
            True
        );

        ppmCreateRegisterField(abSFA1AD_reg, "TPADA1", 0, 10, 22, 1, 1);
    }
    {
        registerHandle abSFA2AD_reg = ppmCreateRegister(
            "ab_SFA2AD",
            "Serial Flash A2 Top Address, offset: 0x184",
            handles.bport1,
            0x184,
            4,
            read_32,
            bport1_ab_SFA2AD_maskWrite,
            view32,
            &(bport1_ab_data.SFA2AD.value),
            True
        );

        ppmCreateRegisterField(abSFA2AD_reg, "TPADA2", 0, 10, 22, 1, 1);
    }
    {
        registerHandle abSFB1AD_reg = ppmCreateRegister(
            "ab_SFB1AD",
            "Serial Flash B1Top Address, offset: 0x188",
            handles.bport1,
            0x188,
            4,
            read_32,
            bport1_ab_SFB1AD_maskWrite,
            view32,
            &(bport1_ab_data.SFB1AD.value),
            True
        );

        ppmCreateRegisterField(abSFB1AD_reg, "TPADB1", 0, 10, 22, 1, 1);
    }
    {
        registerHandle abSFB2AD_reg = ppmCreateRegister(
            "ab_SFB2AD",
            "Serial Flash B2Top Address, offset: 0x18C",
            handles.bport1,
            0x18c,
            4,
            read_32,
            bport1_ab_SFB2AD_maskWrite,
            view32,
            &(bport1_ab_data.SFB2AD.value),
            True
        );

        ppmCreateRegisterField(abSFB2AD_reg, "TPADB2", 0, 10, 22, 1, 1);
    }
    {
        registerHandle abLUTKEY_reg = ppmCreateRegister(
            "ab_LUTKEY",
            "LUT Key Register, offset: 0x300",
            handles.bport1,
            0x300,
            4,
            readLutKey,
            writeLutKey,
            view32,
            &(bport1_ab_data.LUTKEY.value),
            True
        );

        ppmCreateRegisterField(abLUTKEY_reg, "KEY", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abLCKCR_reg = ppmCreateRegister(
            "ab_LCKCR",
            "LUT Lock Configuration Register, offset: 0x304",
            handles.bport1,
            0x304,
            4,
            readLutLck,
            writeLutLck,
            view32,
            &(bport1_ab_data.LCKCR.value),
            True
        );

        ppmCreateRegisterField(abLCKCR_reg, "LOCK", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abLCKCR_reg, "UNLOCK", 0, 1, 1, 1, 1);
    }
    {
        registerHandle abRBDR0_reg = ppmCreateRegister(
            "ab_RBDR0",
            "RX Buffer DataRegister 0 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x200,
            4,
            read_32,
            bport1_ab_RBDR0_maskWrite,
            view32,
            &(bport1_ab_data.RBDR0.value),
            True
        );

        ppmCreateRegisterField(abRBDR0_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR1_reg = ppmCreateRegister(
            "ab_RBDR1",
            "RX Buffer DataRegister 1 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x204,
            4,
            read_32,
            bport1_ab_RBDR1_maskWrite,
            view32,
            &(bport1_ab_data.RBDR1.value),
            True
        );

        ppmCreateRegisterField(abRBDR1_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR2_reg = ppmCreateRegister(
            "ab_RBDR2",
            "RX Buffer DataRegister 2 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x208,
            4,
            read_32,
            bport1_ab_RBDR2_maskWrite,
            view32,
            &(bport1_ab_data.RBDR2.value),
            True
        );

        ppmCreateRegisterField(abRBDR2_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR3_reg = ppmCreateRegister(
            "ab_RBDR3",
            "RX Buffer DataRegister 3 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x20c,
            4,
            read_32,
            bport1_ab_RBDR3_maskWrite,
            view32,
            &(bport1_ab_data.RBDR3.value),
            True
        );

        ppmCreateRegisterField(abRBDR3_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR4_reg = ppmCreateRegister(
            "ab_RBDR4",
            "RX Buffer DataRegister 4 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x210,
            4,
            read_32,
            bport1_ab_RBDR4_maskWrite,
            view32,
            &(bport1_ab_data.RBDR4.value),
            True
        );

        ppmCreateRegisterField(abRBDR4_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR5_reg = ppmCreateRegister(
            "ab_RBDR5",
            "RX Buffer DataRegister 5 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x214,
            4,
            read_32,
            bport1_ab_RBDR5_maskWrite,
            view32,
            &(bport1_ab_data.RBDR5.value),
            True
        );

        ppmCreateRegisterField(abRBDR5_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR6_reg = ppmCreateRegister(
            "ab_RBDR6",
            "RX Buffer DataRegister 6 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x218,
            4,
            read_32,
            bport1_ab_RBDR6_maskWrite,
            view32,
            &(bport1_ab_data.RBDR6.value),
            True
        );

        ppmCreateRegisterField(abRBDR6_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR7_reg = ppmCreateRegister(
            "ab_RBDR7",
            "RX Buffer DataRegister 7 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x21c,
            4,
            read_32,
            bport1_ab_RBDR7_maskWrite,
            view32,
            &(bport1_ab_data.RBDR7.value),
            True
        );

        ppmCreateRegisterField(abRBDR7_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR8_reg = ppmCreateRegister(
            "ab_RBDR8",
            "RX Buffer DataRegister 8 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x220,
            4,
            read_32,
            bport1_ab_RBDR8_maskWrite,
            view32,
            &(bport1_ab_data.RBDR8.value),
            True
        );

        ppmCreateRegisterField(abRBDR8_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR9_reg = ppmCreateRegister(
            "ab_RBDR9",
            "RX Buffer DataRegister 9 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x224,
            4,
            read_32,
            bport1_ab_RBDR9_maskWrite,
            view32,
            &(bport1_ab_data.RBDR9.value),
            True
        );

        ppmCreateRegisterField(abRBDR9_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR10_reg = ppmCreateRegister(
            "ab_RBDR10",
            "RX Buffer DataRegister 10 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x228,
            4,
            read_32,
            bport1_ab_RBDR10_maskWrite,
            view32,
            &(bport1_ab_data.RBDR10.value),
            True
        );

        ppmCreateRegisterField(abRBDR10_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR11_reg = ppmCreateRegister(
            "ab_RBDR11",
            "RX Buffer DataRegister 11 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x22c,
            4,
            read_32,
            bport1_ab_RBDR11_maskWrite,
            view32,
            &(bport1_ab_data.RBDR11.value),
            True
        );

        ppmCreateRegisterField(abRBDR11_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR12_reg = ppmCreateRegister(
            "ab_RBDR12",
            "RX Buffer DataRegister 12 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x230,
            4,
            read_32,
            bport1_ab_RBDR12_maskWrite,
            view32,
            &(bport1_ab_data.RBDR12.value),
            True
        );

        ppmCreateRegisterField(abRBDR12_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR13_reg = ppmCreateRegister(
            "ab_RBDR13",
            "RX Buffer DataRegister 13 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x234,
            4,
            read_32,
            bport1_ab_RBDR13_maskWrite,
            view32,
            &(bport1_ab_data.RBDR13.value),
            True
        );

        ppmCreateRegisterField(abRBDR13_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR14_reg = ppmCreateRegister(
            "ab_RBDR14",
            "RX Buffer DataRegister 14 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x238,
            4,
            read_32,
            bport1_ab_RBDR14_maskWrite,
            view32,
            &(bport1_ab_data.RBDR14.value),
            True
        );

        ppmCreateRegisterField(abRBDR14_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR15_reg = ppmCreateRegister(
            "ab_RBDR15",
            "RX Buffer DataRegister 15 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x23c,
            4,
            read_32,
            bport1_ab_RBDR15_maskWrite,
            view32,
            &(bport1_ab_data.RBDR15.value),
            True
        );

        ppmCreateRegisterField(abRBDR15_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR16_reg = ppmCreateRegister(
            "ab_RBDR16",
            "RX Buffer DataRegister 16 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x240,
            4,
            read_32,
            bport1_ab_RBDR16_maskWrite,
            view32,
            &(bport1_ab_data.RBDR16.value),
            True
        );

        ppmCreateRegisterField(abRBDR16_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR17_reg = ppmCreateRegister(
            "ab_RBDR17",
            "RX Buffer DataRegister 17 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x244,
            4,
            read_32,
            bport1_ab_RBDR17_maskWrite,
            view32,
            &(bport1_ab_data.RBDR17.value),
            True
        );

        ppmCreateRegisterField(abRBDR17_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR18_reg = ppmCreateRegister(
            "ab_RBDR18",
            "RX Buffer DataRegister 18 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x248,
            4,
            read_32,
            bport1_ab_RBDR18_maskWrite,
            view32,
            &(bport1_ab_data.RBDR18.value),
            True
        );

        ppmCreateRegisterField(abRBDR18_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR19_reg = ppmCreateRegister(
            "ab_RBDR19",
            "RX Buffer DataRegister 19 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x24c,
            4,
            read_32,
            bport1_ab_RBDR19_maskWrite,
            view32,
            &(bport1_ab_data.RBDR19.value),
            True
        );

        ppmCreateRegisterField(abRBDR19_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR20_reg = ppmCreateRegister(
            "ab_RBDR20",
            "RX Buffer DataRegister 20 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x250,
            4,
            read_32,
            bport1_ab_RBDR20_maskWrite,
            view32,
            &(bport1_ab_data.RBDR20.value),
            True
        );

        ppmCreateRegisterField(abRBDR20_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR21_reg = ppmCreateRegister(
            "ab_RBDR21",
            "RX Buffer DataRegister 21 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x254,
            4,
            read_32,
            bport1_ab_RBDR21_maskWrite,
            view32,
            &(bport1_ab_data.RBDR21.value),
            True
        );

        ppmCreateRegisterField(abRBDR21_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR22_reg = ppmCreateRegister(
            "ab_RBDR22",
            "RX Buffer DataRegister 22 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x258,
            4,
            read_32,
            bport1_ab_RBDR22_maskWrite,
            view32,
            &(bport1_ab_data.RBDR22.value),
            True
        );

        ppmCreateRegisterField(abRBDR22_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR23_reg = ppmCreateRegister(
            "ab_RBDR23",
            "RX Buffer DataRegister 23 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x25c,
            4,
            read_32,
            bport1_ab_RBDR23_maskWrite,
            view32,
            &(bport1_ab_data.RBDR23.value),
            True
        );

        ppmCreateRegisterField(abRBDR23_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR24_reg = ppmCreateRegister(
            "ab_RBDR24",
            "RX Buffer DataRegister 24 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x260,
            4,
            read_32,
            bport1_ab_RBDR24_maskWrite,
            view32,
            &(bport1_ab_data.RBDR24.value),
            True
        );

        ppmCreateRegisterField(abRBDR24_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR25_reg = ppmCreateRegister(
            "ab_RBDR25",
            "RX Buffer DataRegister 25 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x264,
            4,
            read_32,
            bport1_ab_RBDR25_maskWrite,
            view32,
            &(bport1_ab_data.RBDR25.value),
            True
        );

        ppmCreateRegisterField(abRBDR25_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR26_reg = ppmCreateRegister(
            "ab_RBDR26",
            "RX Buffer DataRegister 26 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x268,
            4,
            read_32,
            bport1_ab_RBDR26_maskWrite,
            view32,
            &(bport1_ab_data.RBDR26.value),
            True
        );

        ppmCreateRegisterField(abRBDR26_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR27_reg = ppmCreateRegister(
            "ab_RBDR27",
            "RX Buffer DataRegister 27 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x26c,
            4,
            read_32,
            bport1_ab_RBDR27_maskWrite,
            view32,
            &(bport1_ab_data.RBDR27.value),
            True
        );

        ppmCreateRegisterField(abRBDR27_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR28_reg = ppmCreateRegister(
            "ab_RBDR28",
            "RX Buffer DataRegister 28 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x270,
            4,
            read_32,
            bport1_ab_RBDR28_maskWrite,
            view32,
            &(bport1_ab_data.RBDR28.value),
            True
        );

        ppmCreateRegisterField(abRBDR28_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR29_reg = ppmCreateRegister(
            "ab_RBDR29",
            "RX Buffer DataRegister 29 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x274,
            4,
            read_32,
            bport1_ab_RBDR29_maskWrite,
            view32,
            &(bport1_ab_data.RBDR29.value),
            True
        );

        ppmCreateRegisterField(abRBDR29_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abRBDR30_reg = ppmCreateRegister(
            "ab_RBDR30",
            "RX Buffer DataRegister 30 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x278,
            4,
            read_32,
            bport1_ab_RBDR30_maskWrite,
            view32,
            &(bport1_ab_data.RBDR30.value),
            True
        );

        ppmCreateRegisterField(abRBDR30_reg, "RXDATA", 0, 0, 32, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_RBDR31",
            "RX Buffer DataRegister 31 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x27c,
            4,
            read_32,
            bport1_ab_RBDR31_maskWrite,
            view32,
            &(bport1_ab_data.RBDR31.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR32",
            "RX Buffer DataRegister 32 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x280,
            4,
            read_32,
            bport1_ab_RBDR32_maskWrite,
            view32,
            &(bport1_ab_data.RBDR32.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR33",
            "RX Buffer DataRegister 33 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x284,
            4,
            read_32,
            bport1_ab_RBDR33_maskWrite,
            view32,
            &(bport1_ab_data.RBDR33.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR34",
            "RX Buffer DataRegister 34 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x288,
            4,
            read_32,
            bport1_ab_RBDR34_maskWrite,
            view32,
            &(bport1_ab_data.RBDR34.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR35",
            "RX Buffer DataRegister 35 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x28c,
            4,
            read_32,
            bport1_ab_RBDR35_maskWrite,
            view32,
            &(bport1_ab_data.RBDR35.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR36",
            "RX Buffer DataRegister 36 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x290,
            4,
            read_32,
            bport1_ab_RBDR36_maskWrite,
            view32,
            &(bport1_ab_data.RBDR36.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR37",
            "RX Buffer DataRegister 37 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x294,
            4,
            read_32,
            bport1_ab_RBDR37_maskWrite,
            view32,
            &(bport1_ab_data.RBDR37.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR38",
            "RX Buffer DataRegister 38 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x298,
            4,
            read_32,
            bport1_ab_RBDR38_maskWrite,
            view32,
            &(bport1_ab_data.RBDR38.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR39",
            "RX Buffer DataRegister 39 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x29c,
            4,
            read_32,
            bport1_ab_RBDR39_maskWrite,
            view32,
            &(bport1_ab_data.RBDR39.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR40",
            "RX Buffer DataRegister 40 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x2a0,
            4,
            read_32,
            bport1_ab_RBDR40_maskWrite,
            view32,
            &(bport1_ab_data.RBDR40.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR41",
            "RX Buffer DataRegister 41 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x2a4,
            4,
            read_32,
            bport1_ab_RBDR41_maskWrite,
            view32,
            &(bport1_ab_data.RBDR41.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR42",
            "RX Buffer DataRegister 42 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x2a8,
            4,
            read_32,
            bport1_ab_RBDR42_maskWrite,
            view32,
            &(bport1_ab_data.RBDR42.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR43",
            "RX Buffer DataRegister 43 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x2ac,
            4,
            read_32,
            bport1_ab_RBDR43_maskWrite,
            view32,
            &(bport1_ab_data.RBDR43.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR44",
            "RX Buffer DataRegister 44 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x2b0,
            4,
            read_32,
            bport1_ab_RBDR44_maskWrite,
            view32,
            &(bport1_ab_data.RBDR44.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR45",
            "RX Buffer DataRegister 45 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x2b4,
            4,
            read_32,
            bport1_ab_RBDR45_maskWrite,
            view32,
            &(bport1_ab_data.RBDR45.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR46",
            "RX Buffer DataRegister 46 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x2b8,
            4,
            read_32,
            bport1_ab_RBDR46_maskWrite,
            view32,
            &(bport1_ab_data.RBDR46.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR47",
            "RX Buffer DataRegister 47 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x2bc,
            4,
            read_32,
            bport1_ab_RBDR47_maskWrite,
            view32,
            &(bport1_ab_data.RBDR47.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR48",
            "RX Buffer DataRegister 48 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x2c0,
            4,
            read_32,
            bport1_ab_RBDR48_maskWrite,
            view32,
            &(bport1_ab_data.RBDR48.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR49",
            "RX Buffer DataRegister 49 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x2c4,
            4,
            read_32,
            bport1_ab_RBDR49_maskWrite,
            view32,
            &(bport1_ab_data.RBDR49.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR50",
            "RX Buffer DataRegister 50 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x2c8,
            4,
            read_32,
            bport1_ab_RBDR50_maskWrite,
            view32,
            &(bport1_ab_data.RBDR50.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR51",
            "RX Buffer DataRegister 51 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x2cc,
            4,
            read_32,
            bport1_ab_RBDR51_maskWrite,
            view32,
            &(bport1_ab_data.RBDR51.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR52",
            "RX Buffer DataRegister 52 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x2d0,
            4,
            read_32,
            bport1_ab_RBDR52_maskWrite,
            view32,
            &(bport1_ab_data.RBDR52.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR53",
            "RX Buffer DataRegister 53 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x2d4,
            4,
            read_32,
            bport1_ab_RBDR53_maskWrite,
            view32,
            &(bport1_ab_data.RBDR53.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR54",
            "RX Buffer DataRegister 54 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x2d8,
            4,
            read_32,
            bport1_ab_RBDR54_maskWrite,
            view32,
            &(bport1_ab_data.RBDR54.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR55",
            "RX Buffer DataRegister 55 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x2dc,
            4,
            read_32,
            bport1_ab_RBDR55_maskWrite,
            view32,
            &(bport1_ab_data.RBDR55.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR56",
            "RX Buffer DataRegister 56 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x2e0,
            4,
            read_32,
            bport1_ab_RBDR56_maskWrite,
            view32,
            &(bport1_ab_data.RBDR56.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR57",
            "RX Buffer DataRegister 57 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x2e4,
            4,
            read_32,
            bport1_ab_RBDR57_maskWrite,
            view32,
            &(bport1_ab_data.RBDR57.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR58",
            "RX Buffer DataRegister 58 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x2e8,
            4,
            read_32,
            bport1_ab_RBDR58_maskWrite,
            view32,
            &(bport1_ab_data.RBDR58.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR59",
            "RX Buffer DataRegister 59 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x2ec,
            4,
            read_32,
            bport1_ab_RBDR59_maskWrite,
            view32,
            &(bport1_ab_data.RBDR59.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR60",
            "RX Buffer DataRegister 60 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x2f0,
            4,
            read_32,
            bport1_ab_RBDR60_maskWrite,
            view32,
            &(bport1_ab_data.RBDR60.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR61",
            "RX Buffer DataRegister 61 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x2f4,
            4,
            read_32,
            bport1_ab_RBDR61_maskWrite,
            view32,
            &(bport1_ab_data.RBDR61.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR62",
            "RX Buffer DataRegister 62 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x2f8,
            4,
            read_32,
            bport1_ab_RBDR62_maskWrite,
            view32,
            &(bport1_ab_data.RBDR62.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RBDR63",
            "RX Buffer DataRegister 63 offset base 0x200: array step: 0x4",
            handles.bport1,
            0x2fc,
            4,
            read_32,
            bport1_ab_RBDR63_maskWrite,
            view32,
            &(bport1_ab_data.RBDR63.value),
            True
        );
    }
    {
        registerHandle abLUT0_reg = ppmCreateRegister(
            "ab_LUT0",
            "Look-up Table register 0, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x310,
            4,
            read_32,
            bport1_ab_LUT0_maskWrite,
            view32,
            &(bport1_ab_data.LUT0.value),
            True
        );

        ppmCreateRegisterField(abLUT0_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT0_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT0_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT0_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT0_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT0_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT1_reg = ppmCreateRegister(
            "ab_LUT1",
            "Look-up Table register 1, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x314,
            4,
            read_32,
            bport1_ab_LUT1_maskWrite,
            view32,
            &(bport1_ab_data.LUT1.value),
            True
        );

        ppmCreateRegisterField(abLUT1_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT1_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT1_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT1_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT1_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT1_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT2_reg = ppmCreateRegister(
            "ab_LUT2",
            "Look-up Table register 2, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x318,
            4,
            read_32,
            bport1_ab_LUT2_maskWrite,
            view32,
            &(bport1_ab_data.LUT2.value),
            True
        );

        ppmCreateRegisterField(abLUT2_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT2_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT2_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT2_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT2_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT2_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT3_reg = ppmCreateRegister(
            "ab_LUT3",
            "Look-up Table register 3, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x31c,
            4,
            read_32,
            bport1_ab_LUT3_maskWrite,
            view32,
            &(bport1_ab_data.LUT3.value),
            True
        );

        ppmCreateRegisterField(abLUT3_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT3_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT3_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT3_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT3_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT3_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT4_reg = ppmCreateRegister(
            "ab_LUT4",
            "Look-up Table register 4, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x320,
            4,
            read_32,
            bport1_ab_LUT4_maskWrite,
            view32,
            &(bport1_ab_data.LUT4.value),
            True
        );

        ppmCreateRegisterField(abLUT4_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT4_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT4_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT4_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT4_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT4_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT5_reg = ppmCreateRegister(
            "ab_LUT5",
            "Look-up Table register 5, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x324,
            4,
            read_32,
            bport1_ab_LUT5_maskWrite,
            view32,
            &(bport1_ab_data.LUT5.value),
            True
        );

        ppmCreateRegisterField(abLUT5_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT5_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT5_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT5_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT5_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT5_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT6_reg = ppmCreateRegister(
            "ab_LUT6",
            "Look-up Table register 6, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x328,
            4,
            read_32,
            bport1_ab_LUT6_maskWrite,
            view32,
            &(bport1_ab_data.LUT6.value),
            True
        );

        ppmCreateRegisterField(abLUT6_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT6_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT6_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT6_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT6_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT6_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT7_reg = ppmCreateRegister(
            "ab_LUT7",
            "Look-up Table register 7, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x32c,
            4,
            read_32,
            bport1_ab_LUT7_maskWrite,
            view32,
            &(bport1_ab_data.LUT7.value),
            True
        );

        ppmCreateRegisterField(abLUT7_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT7_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT7_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT7_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT7_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT7_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT8_reg = ppmCreateRegister(
            "ab_LUT8",
            "Look-up Table register 8, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x330,
            4,
            read_32,
            bport1_ab_LUT8_maskWrite,
            view32,
            &(bport1_ab_data.LUT8.value),
            True
        );

        ppmCreateRegisterField(abLUT8_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT8_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT8_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT8_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT8_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT8_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT9_reg = ppmCreateRegister(
            "ab_LUT9",
            "Look-up Table register 9, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x334,
            4,
            read_32,
            bport1_ab_LUT9_maskWrite,
            view32,
            &(bport1_ab_data.LUT9.value),
            True
        );

        ppmCreateRegisterField(abLUT9_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT9_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT9_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT9_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT9_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT9_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT10_reg = ppmCreateRegister(
            "ab_LUT10",
            "Look-up Table register 10, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x338,
            4,
            read_32,
            bport1_ab_LUT10_maskWrite,
            view32,
            &(bport1_ab_data.LUT10.value),
            True
        );

        ppmCreateRegisterField(abLUT10_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT10_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT10_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT10_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT10_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT10_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT11_reg = ppmCreateRegister(
            "ab_LUT11",
            "Look-up Table register 11, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x33c,
            4,
            read_32,
            bport1_ab_LUT11_maskWrite,
            view32,
            &(bport1_ab_data.LUT11.value),
            True
        );

        ppmCreateRegisterField(abLUT11_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT11_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT11_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT11_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT11_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT11_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT12_reg = ppmCreateRegister(
            "ab_LUT12",
            "Look-up Table register 12, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x340,
            4,
            read_32,
            bport1_ab_LUT12_maskWrite,
            view32,
            &(bport1_ab_data.LUT12.value),
            True
        );

        ppmCreateRegisterField(abLUT12_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT12_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT12_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT12_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT12_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT12_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT13_reg = ppmCreateRegister(
            "ab_LUT13",
            "Look-up Table register 13, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x344,
            4,
            read_32,
            bport1_ab_LUT13_maskWrite,
            view32,
            &(bport1_ab_data.LUT13.value),
            True
        );

        ppmCreateRegisterField(abLUT13_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT13_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT13_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT13_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT13_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT13_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT14_reg = ppmCreateRegister(
            "ab_LUT14",
            "Look-up Table register 14, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x348,
            4,
            read_32,
            bport1_ab_LUT14_maskWrite,
            view32,
            &(bport1_ab_data.LUT14.value),
            True
        );

        ppmCreateRegisterField(abLUT14_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT14_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT14_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT14_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT14_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT14_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT15_reg = ppmCreateRegister(
            "ab_LUT15",
            "Look-up Table register 15, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x34c,
            4,
            read_32,
            bport1_ab_LUT15_maskWrite,
            view32,
            &(bport1_ab_data.LUT15.value),
            True
        );

        ppmCreateRegisterField(abLUT15_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT15_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT15_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT15_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT15_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT15_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT16_reg = ppmCreateRegister(
            "ab_LUT16",
            "Look-up Table register 16, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x350,
            4,
            read_32,
            bport1_ab_LUT16_maskWrite,
            view32,
            &(bport1_ab_data.LUT16.value),
            True
        );

        ppmCreateRegisterField(abLUT16_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT16_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT16_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT16_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT16_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT16_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT17_reg = ppmCreateRegister(
            "ab_LUT17",
            "Look-up Table register 17, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x354,
            4,
            read_32,
            bport1_ab_LUT17_maskWrite,
            view32,
            &(bport1_ab_data.LUT17.value),
            True
        );

        ppmCreateRegisterField(abLUT17_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT17_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT17_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT17_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT17_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT17_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT18_reg = ppmCreateRegister(
            "ab_LUT18",
            "Look-up Table register 18, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x358,
            4,
            read_32,
            bport1_ab_LUT18_maskWrite,
            view32,
            &(bport1_ab_data.LUT18.value),
            True
        );

        ppmCreateRegisterField(abLUT18_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT18_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT18_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT18_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT18_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT18_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT19_reg = ppmCreateRegister(
            "ab_LUT19",
            "Look-up Table register 19, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x35c,
            4,
            read_32,
            bport1_ab_LUT19_maskWrite,
            view32,
            &(bport1_ab_data.LUT19.value),
            True
        );

        ppmCreateRegisterField(abLUT19_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT19_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT19_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT19_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT19_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT19_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT20_reg = ppmCreateRegister(
            "ab_LUT20",
            "Look-up Table register 20, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x360,
            4,
            read_32,
            bport1_ab_LUT20_maskWrite,
            view32,
            &(bport1_ab_data.LUT20.value),
            True
        );

        ppmCreateRegisterField(abLUT20_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT20_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT20_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT20_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT20_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT20_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT21_reg = ppmCreateRegister(
            "ab_LUT21",
            "Look-up Table register 21, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x364,
            4,
            read_32,
            bport1_ab_LUT21_maskWrite,
            view32,
            &(bport1_ab_data.LUT21.value),
            True
        );

        ppmCreateRegisterField(abLUT21_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT21_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT21_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT21_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT21_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT21_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT22_reg = ppmCreateRegister(
            "ab_LUT22",
            "Look-up Table register 22, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x368,
            4,
            read_32,
            bport1_ab_LUT22_maskWrite,
            view32,
            &(bport1_ab_data.LUT22.value),
            True
        );

        ppmCreateRegisterField(abLUT22_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT22_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT22_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT22_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT22_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT22_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT23_reg = ppmCreateRegister(
            "ab_LUT23",
            "Look-up Table register 23, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x36c,
            4,
            read_32,
            bport1_ab_LUT23_maskWrite,
            view32,
            &(bport1_ab_data.LUT23.value),
            True
        );

        ppmCreateRegisterField(abLUT23_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT23_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT23_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT23_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT23_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT23_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT24_reg = ppmCreateRegister(
            "ab_LUT24",
            "Look-up Table register 24, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x370,
            4,
            read_32,
            bport1_ab_LUT24_maskWrite,
            view32,
            &(bport1_ab_data.LUT24.value),
            True
        );

        ppmCreateRegisterField(abLUT24_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT24_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT24_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT24_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT24_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT24_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT25_reg = ppmCreateRegister(
            "ab_LUT25",
            "Look-up Table register 25, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x374,
            4,
            read_32,
            bport1_ab_LUT25_maskWrite,
            view32,
            &(bport1_ab_data.LUT25.value),
            True
        );

        ppmCreateRegisterField(abLUT25_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT25_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT25_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT25_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT25_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT25_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT26_reg = ppmCreateRegister(
            "ab_LUT26",
            "Look-up Table register 26, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x378,
            4,
            read_32,
            bport1_ab_LUT26_maskWrite,
            view32,
            &(bport1_ab_data.LUT26.value),
            True
        );

        ppmCreateRegisterField(abLUT26_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT26_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT26_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT26_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT26_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT26_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT27_reg = ppmCreateRegister(
            "ab_LUT27",
            "Look-up Table register 27, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x37c,
            4,
            read_32,
            bport1_ab_LUT27_maskWrite,
            view32,
            &(bport1_ab_data.LUT27.value),
            True
        );

        ppmCreateRegisterField(abLUT27_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT27_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT27_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT27_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT27_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT27_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT28_reg = ppmCreateRegister(
            "ab_LUT28",
            "Look-up Table register 28, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x380,
            4,
            read_32,
            bport1_ab_LUT28_maskWrite,
            view32,
            &(bport1_ab_data.LUT28.value),
            True
        );

        ppmCreateRegisterField(abLUT28_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT28_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT28_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT28_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT28_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT28_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT29_reg = ppmCreateRegister(
            "ab_LUT29",
            "Look-up Table register 29, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x384,
            4,
            read_32,
            bport1_ab_LUT29_maskWrite,
            view32,
            &(bport1_ab_data.LUT29.value),
            True
        );

        ppmCreateRegisterField(abLUT29_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT29_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT29_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT29_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT29_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT29_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT30_reg = ppmCreateRegister(
            "ab_LUT30",
            "Look-up Table register 30, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x388,
            4,
            read_32,
            bport1_ab_LUT30_maskWrite,
            view32,
            &(bport1_ab_data.LUT30.value),
            True
        );

        ppmCreateRegisterField(abLUT30_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT30_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT30_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT30_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT30_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT30_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT31_reg = ppmCreateRegister(
            "ab_LUT31",
            "Look-up Table register 31, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x38c,
            4,
            read_32,
            bport1_ab_LUT31_maskWrite,
            view32,
            &(bport1_ab_data.LUT31.value),
            True
        );

        ppmCreateRegisterField(abLUT31_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT31_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT31_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT31_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT31_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT31_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT32_reg = ppmCreateRegister(
            "ab_LUT32",
            "Look-up Table register 32, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x390,
            4,
            read_32,
            bport1_ab_LUT32_maskWrite,
            view32,
            &(bport1_ab_data.LUT32.value),
            True
        );

        ppmCreateRegisterField(abLUT32_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT32_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT32_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT32_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT32_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT32_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT33_reg = ppmCreateRegister(
            "ab_LUT33",
            "Look-up Table register 33, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x394,
            4,
            read_32,
            bport1_ab_LUT33_maskWrite,
            view32,
            &(bport1_ab_data.LUT33.value),
            True
        );

        ppmCreateRegisterField(abLUT33_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT33_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT33_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT33_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT33_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT33_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT34_reg = ppmCreateRegister(
            "ab_LUT34",
            "Look-up Table register 34, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x398,
            4,
            read_32,
            bport1_ab_LUT34_maskWrite,
            view32,
            &(bport1_ab_data.LUT34.value),
            True
        );

        ppmCreateRegisterField(abLUT34_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT34_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT34_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT34_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT34_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT34_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT35_reg = ppmCreateRegister(
            "ab_LUT35",
            "Look-up Table register 35, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x39c,
            4,
            read_32,
            bport1_ab_LUT35_maskWrite,
            view32,
            &(bport1_ab_data.LUT35.value),
            True
        );

        ppmCreateRegisterField(abLUT35_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT35_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT35_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT35_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT35_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT35_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT36_reg = ppmCreateRegister(
            "ab_LUT36",
            "Look-up Table register 36, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x3a0,
            4,
            read_32,
            bport1_ab_LUT36_maskWrite,
            view32,
            &(bport1_ab_data.LUT36.value),
            True
        );

        ppmCreateRegisterField(abLUT36_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT36_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT36_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT36_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT36_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT36_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT37_reg = ppmCreateRegister(
            "ab_LUT37",
            "Look-up Table register 37, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x3a4,
            4,
            read_32,
            bport1_ab_LUT37_maskWrite,
            view32,
            &(bport1_ab_data.LUT37.value),
            True
        );

        ppmCreateRegisterField(abLUT37_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT37_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT37_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT37_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT37_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT37_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT38_reg = ppmCreateRegister(
            "ab_LUT38",
            "Look-up Table register 38, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x3a8,
            4,
            read_32,
            bport1_ab_LUT38_maskWrite,
            view32,
            &(bport1_ab_data.LUT38.value),
            True
        );

        ppmCreateRegisterField(abLUT38_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT38_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT38_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT38_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT38_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT38_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT39_reg = ppmCreateRegister(
            "ab_LUT39",
            "Look-up Table register 39, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x3ac,
            4,
            read_32,
            bport1_ab_LUT39_maskWrite,
            view32,
            &(bport1_ab_data.LUT39.value),
            True
        );

        ppmCreateRegisterField(abLUT39_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT39_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT39_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT39_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT39_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT39_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT40_reg = ppmCreateRegister(
            "ab_LUT40",
            "Look-up Table register 40, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x3b0,
            4,
            read_32,
            bport1_ab_LUT40_maskWrite,
            view32,
            &(bport1_ab_data.LUT40.value),
            True
        );

        ppmCreateRegisterField(abLUT40_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT40_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT40_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT40_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT40_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT40_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT41_reg = ppmCreateRegister(
            "ab_LUT41",
            "Look-up Table register 41, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x3b4,
            4,
            read_32,
            bport1_ab_LUT41_maskWrite,
            view32,
            &(bport1_ab_data.LUT41.value),
            True
        );

        ppmCreateRegisterField(abLUT41_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT41_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT41_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT41_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT41_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT41_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT42_reg = ppmCreateRegister(
            "ab_LUT42",
            "Look-up Table register 42, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x3b8,
            4,
            read_32,
            bport1_ab_LUT42_maskWrite,
            view32,
            &(bport1_ab_data.LUT42.value),
            True
        );

        ppmCreateRegisterField(abLUT42_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT42_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT42_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT42_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT42_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT42_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT43_reg = ppmCreateRegister(
            "ab_LUT43",
            "Look-up Table register 43, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x3bc,
            4,
            read_32,
            bport1_ab_LUT43_maskWrite,
            view32,
            &(bport1_ab_data.LUT43.value),
            True
        );

        ppmCreateRegisterField(abLUT43_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT43_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT43_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT43_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT43_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT43_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT44_reg = ppmCreateRegister(
            "ab_LUT44",
            "Look-up Table register 44, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x3c0,
            4,
            read_32,
            bport1_ab_LUT44_maskWrite,
            view32,
            &(bport1_ab_data.LUT44.value),
            True
        );

        ppmCreateRegisterField(abLUT44_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT44_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT44_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT44_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT44_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT44_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT45_reg = ppmCreateRegister(
            "ab_LUT45",
            "Look-up Table register 45, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x3c4,
            4,
            read_32,
            bport1_ab_LUT45_maskWrite,
            view32,
            &(bport1_ab_data.LUT45.value),
            True
        );

        ppmCreateRegisterField(abLUT45_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT45_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT45_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT45_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT45_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT45_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT46_reg = ppmCreateRegister(
            "ab_LUT46",
            "Look-up Table register 46, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x3c8,
            4,
            read_32,
            bport1_ab_LUT46_maskWrite,
            view32,
            &(bport1_ab_data.LUT46.value),
            True
        );

        ppmCreateRegisterField(abLUT46_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT46_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT46_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT46_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT46_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT46_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT47_reg = ppmCreateRegister(
            "ab_LUT47",
            "Look-up Table register 47, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x3cc,
            4,
            read_32,
            bport1_ab_LUT47_maskWrite,
            view32,
            &(bport1_ab_data.LUT47.value),
            True
        );

        ppmCreateRegisterField(abLUT47_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT47_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT47_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT47_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT47_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT47_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT48_reg = ppmCreateRegister(
            "ab_LUT48",
            "Look-up Table register 48, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x3d0,
            4,
            read_32,
            bport1_ab_LUT48_maskWrite,
            view32,
            &(bport1_ab_data.LUT48.value),
            True
        );

        ppmCreateRegisterField(abLUT48_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT48_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT48_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT48_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT48_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT48_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT49_reg = ppmCreateRegister(
            "ab_LUT49",
            "Look-up Table register 49, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x3d4,
            4,
            read_32,
            bport1_ab_LUT49_maskWrite,
            view32,
            &(bport1_ab_data.LUT49.value),
            True
        );

        ppmCreateRegisterField(abLUT49_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT49_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT49_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT49_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT49_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT49_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT50_reg = ppmCreateRegister(
            "ab_LUT50",
            "Look-up Table register 50, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x3d8,
            4,
            read_32,
            bport1_ab_LUT50_maskWrite,
            view32,
            &(bport1_ab_data.LUT50.value),
            True
        );

        ppmCreateRegisterField(abLUT50_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT50_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT50_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT50_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT50_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT50_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT51_reg = ppmCreateRegister(
            "ab_LUT51",
            "Look-up Table register 51, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x3dc,
            4,
            read_32,
            bport1_ab_LUT51_maskWrite,
            view32,
            &(bport1_ab_data.LUT51.value),
            True
        );

        ppmCreateRegisterField(abLUT51_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT51_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT51_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT51_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT51_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT51_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT52_reg = ppmCreateRegister(
            "ab_LUT52",
            "Look-up Table register 52, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x3e0,
            4,
            read_32,
            bport1_ab_LUT52_maskWrite,
            view32,
            &(bport1_ab_data.LUT52.value),
            True
        );

        ppmCreateRegisterField(abLUT52_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT52_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT52_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT52_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT52_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT52_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT53_reg = ppmCreateRegister(
            "ab_LUT53",
            "Look-up Table register 53, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x3e4,
            4,
            read_32,
            bport1_ab_LUT53_maskWrite,
            view32,
            &(bport1_ab_data.LUT53.value),
            True
        );

        ppmCreateRegisterField(abLUT53_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT53_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT53_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT53_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT53_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT53_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT54_reg = ppmCreateRegister(
            "ab_LUT54",
            "Look-up Table register 54, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x3e8,
            4,
            read_32,
            bport1_ab_LUT54_maskWrite,
            view32,
            &(bport1_ab_data.LUT54.value),
            True
        );

        ppmCreateRegisterField(abLUT54_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT54_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT54_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT54_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT54_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT54_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT55_reg = ppmCreateRegister(
            "ab_LUT55",
            "Look-up Table register 55, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x3ec,
            4,
            read_32,
            bport1_ab_LUT55_maskWrite,
            view32,
            &(bport1_ab_data.LUT55.value),
            True
        );

        ppmCreateRegisterField(abLUT55_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT55_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT55_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT55_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT55_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT55_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT56_reg = ppmCreateRegister(
            "ab_LUT56",
            "Look-up Table register 56, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x3f0,
            4,
            read_32,
            bport1_ab_LUT56_maskWrite,
            view32,
            &(bport1_ab_data.LUT56.value),
            True
        );

        ppmCreateRegisterField(abLUT56_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT56_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT56_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT56_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT56_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT56_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT57_reg = ppmCreateRegister(
            "ab_LUT57",
            "Look-up Table register 57, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x3f4,
            4,
            read_32,
            bport1_ab_LUT57_maskWrite,
            view32,
            &(bport1_ab_data.LUT57.value),
            True
        );

        ppmCreateRegisterField(abLUT57_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT57_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT57_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT57_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT57_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT57_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT58_reg = ppmCreateRegister(
            "ab_LUT58",
            "Look-up Table register 58, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x3f8,
            4,
            read_32,
            bport1_ab_LUT58_maskWrite,
            view32,
            &(bport1_ab_data.LUT58.value),
            True
        );

        ppmCreateRegisterField(abLUT58_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT58_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT58_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT58_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT58_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT58_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT59_reg = ppmCreateRegister(
            "ab_LUT59",
            "Look-up Table register 59, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x3fc,
            4,
            read_32,
            bport1_ab_LUT59_maskWrite,
            view32,
            &(bport1_ab_data.LUT59.value),
            True
        );

        ppmCreateRegisterField(abLUT59_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT59_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT59_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT59_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT59_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT59_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT60_reg = ppmCreateRegister(
            "ab_LUT60",
            "Look-up Table register 60, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x400,
            4,
            read_32,
            bport1_ab_LUT60_maskWrite,
            view32,
            &(bport1_ab_data.LUT60.value),
            True
        );

        ppmCreateRegisterField(abLUT60_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT60_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT60_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT60_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT60_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT60_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT61_reg = ppmCreateRegister(
            "ab_LUT61",
            "Look-up Table register 61, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x404,
            4,
            read_32,
            bport1_ab_LUT61_maskWrite,
            view32,
            &(bport1_ab_data.LUT61.value),
            True
        );

        ppmCreateRegisterField(abLUT61_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT61_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT61_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT61_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT61_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT61_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT62_reg = ppmCreateRegister(
            "ab_LUT62",
            "Look-up Table register 62, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x408,
            4,
            read_32,
            bport1_ab_LUT62_maskWrite,
            view32,
            &(bport1_ab_data.LUT62.value),
            True
        );

        ppmCreateRegisterField(abLUT62_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT62_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT62_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT62_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT62_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT62_reg, "INSTR1", 0, 26, 6, 1, 1);
    }
    {
        registerHandle abLUT63_reg = ppmCreateRegister(
            "ab_LUT63",
            "Look-up Table register 63, array offset base 0x310:  , array step: 0x4",
            handles.bport1,
            0x40c,
            4,
            read_32,
            bport1_ab_LUT63_maskWrite,
            view32,
            &(bport1_ab_data.LUT63.value),
            True
        );

        ppmCreateRegisterField(abLUT63_reg, "OPRND0", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abLUT63_reg, "PAD0", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abLUT63_reg, "INSTR0", 0, 10, 6, 1, 1);
        ppmCreateRegisterField(abLUT63_reg, "OPRND1", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abLUT63_reg, "PAD1", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abLUT63_reg, "INSTR1", 0, 26, 6, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.LUT63.value = (Uns32)(bport1_ab_data.LUT63.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT62.value = (Uns32)(bport1_ab_data.LUT62.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT61.value = (Uns32)(bport1_ab_data.LUT61.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT60.value = (Uns32)(bport1_ab_data.LUT60.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT59.value = (Uns32)(bport1_ab_data.LUT59.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT58.value = (Uns32)(bport1_ab_data.LUT58.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT57.value = (Uns32)(bport1_ab_data.LUT57.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT56.value = (Uns32)(bport1_ab_data.LUT56.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT55.value = (Uns32)(bport1_ab_data.LUT55.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT54.value = (Uns32)(bport1_ab_data.LUT54.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT53.value = (Uns32)(bport1_ab_data.LUT53.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT52.value = (Uns32)(bport1_ab_data.LUT52.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT51.value = (Uns32)(bport1_ab_data.LUT51.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT50.value = (Uns32)(bport1_ab_data.LUT50.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT49.value = (Uns32)(bport1_ab_data.LUT49.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT48.value = (Uns32)(bport1_ab_data.LUT48.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT47.value = (Uns32)(bport1_ab_data.LUT47.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT46.value = (Uns32)(bport1_ab_data.LUT46.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT45.value = (Uns32)(bport1_ab_data.LUT45.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT44.value = (Uns32)(bport1_ab_data.LUT44.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT43.value = (Uns32)(bport1_ab_data.LUT43.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT42.value = (Uns32)(bport1_ab_data.LUT42.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT41.value = (Uns32)(bport1_ab_data.LUT41.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT40.value = (Uns32)(bport1_ab_data.LUT40.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT39.value = (Uns32)(bport1_ab_data.LUT39.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT38.value = (Uns32)(bport1_ab_data.LUT38.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT37.value = (Uns32)(bport1_ab_data.LUT37.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT36.value = (Uns32)(bport1_ab_data.LUT36.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT35.value = (Uns32)(bport1_ab_data.LUT35.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT34.value = (Uns32)(bport1_ab_data.LUT34.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT33.value = (Uns32)(bport1_ab_data.LUT33.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT32.value = (Uns32)(bport1_ab_data.LUT32.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT31.value = (Uns32)(bport1_ab_data.LUT31.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT30.value = (Uns32)(bport1_ab_data.LUT30.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT29.value = (Uns32)(bport1_ab_data.LUT29.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT28.value = (Uns32)(bport1_ab_data.LUT28.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT27.value = (Uns32)(bport1_ab_data.LUT27.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT26.value = (Uns32)(bport1_ab_data.LUT26.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT25.value = (Uns32)(bport1_ab_data.LUT25.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT24.value = (Uns32)(bport1_ab_data.LUT24.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT23.value = (Uns32)(bport1_ab_data.LUT23.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT22.value = (Uns32)(bport1_ab_data.LUT22.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT21.value = (Uns32)(bport1_ab_data.LUT21.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT20.value = (Uns32)(bport1_ab_data.LUT20.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT19.value = (Uns32)(bport1_ab_data.LUT19.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT18.value = (Uns32)(bport1_ab_data.LUT18.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT17.value = (Uns32)(bport1_ab_data.LUT17.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT16.value = (Uns32)(bport1_ab_data.LUT16.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT15.value = (Uns32)(bport1_ab_data.LUT15.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT14.value = (Uns32)(bport1_ab_data.LUT14.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT13.value = (Uns32)(bport1_ab_data.LUT13.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT12.value = (Uns32)(bport1_ab_data.LUT12.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT11.value = (Uns32)(bport1_ab_data.LUT11.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT10.value = (Uns32)(bport1_ab_data.LUT10.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT9.value = (Uns32)(bport1_ab_data.LUT9.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT8.value = (Uns32)(bport1_ab_data.LUT8.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT7.value = (Uns32)(bport1_ab_data.LUT7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT6.value = (Uns32)(bport1_ab_data.LUT6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT5.value = (Uns32)(bport1_ab_data.LUT5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT4.value = (Uns32)(bport1_ab_data.LUT4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT3.value = (Uns32)(bport1_ab_data.LUT3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT2.value = (Uns32)(bport1_ab_data.LUT2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT1.value = (Uns32)(bport1_ab_data.LUT1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LUT0.value = (Uns32)(bport1_ab_data.LUT0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR63.value = (Uns32)(bport1_ab_data.RBDR63.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR62.value = (Uns32)(bport1_ab_data.RBDR62.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR61.value = (Uns32)(bport1_ab_data.RBDR61.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR60.value = (Uns32)(bport1_ab_data.RBDR60.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR59.value = (Uns32)(bport1_ab_data.RBDR59.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR58.value = (Uns32)(bport1_ab_data.RBDR58.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR57.value = (Uns32)(bport1_ab_data.RBDR57.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR56.value = (Uns32)(bport1_ab_data.RBDR56.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR55.value = (Uns32)(bport1_ab_data.RBDR55.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR54.value = (Uns32)(bport1_ab_data.RBDR54.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR53.value = (Uns32)(bport1_ab_data.RBDR53.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR52.value = (Uns32)(bport1_ab_data.RBDR52.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR51.value = (Uns32)(bport1_ab_data.RBDR51.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR50.value = (Uns32)(bport1_ab_data.RBDR50.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR49.value = (Uns32)(bport1_ab_data.RBDR49.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR48.value = (Uns32)(bport1_ab_data.RBDR48.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR47.value = (Uns32)(bport1_ab_data.RBDR47.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR46.value = (Uns32)(bport1_ab_data.RBDR46.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR45.value = (Uns32)(bport1_ab_data.RBDR45.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR44.value = (Uns32)(bport1_ab_data.RBDR44.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR43.value = (Uns32)(bport1_ab_data.RBDR43.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR42.value = (Uns32)(bport1_ab_data.RBDR42.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR41.value = (Uns32)(bport1_ab_data.RBDR41.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR40.value = (Uns32)(bport1_ab_data.RBDR40.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR39.value = (Uns32)(bport1_ab_data.RBDR39.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR38.value = (Uns32)(bport1_ab_data.RBDR38.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR37.value = (Uns32)(bport1_ab_data.RBDR37.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR36.value = (Uns32)(bport1_ab_data.RBDR36.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR35.value = (Uns32)(bport1_ab_data.RBDR35.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR34.value = (Uns32)(bport1_ab_data.RBDR34.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR33.value = (Uns32)(bport1_ab_data.RBDR33.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR32.value = (Uns32)(bport1_ab_data.RBDR32.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR31.value = (Uns32)(bport1_ab_data.RBDR31.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR30.value = (Uns32)(bport1_ab_data.RBDR30.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR29.value = (Uns32)(bport1_ab_data.RBDR29.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR28.value = (Uns32)(bport1_ab_data.RBDR28.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR27.value = (Uns32)(bport1_ab_data.RBDR27.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR26.value = (Uns32)(bport1_ab_data.RBDR26.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR25.value = (Uns32)(bport1_ab_data.RBDR25.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR24.value = (Uns32)(bport1_ab_data.RBDR24.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR23.value = (Uns32)(bport1_ab_data.RBDR23.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR22.value = (Uns32)(bport1_ab_data.RBDR22.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR21.value = (Uns32)(bport1_ab_data.RBDR21.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR20.value = (Uns32)(bport1_ab_data.RBDR20.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR19.value = (Uns32)(bport1_ab_data.RBDR19.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR18.value = (Uns32)(bport1_ab_data.RBDR18.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR17.value = (Uns32)(bport1_ab_data.RBDR17.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR16.value = (Uns32)(bport1_ab_data.RBDR16.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR15.value = (Uns32)(bport1_ab_data.RBDR15.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR14.value = (Uns32)(bport1_ab_data.RBDR14.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR13.value = (Uns32)(bport1_ab_data.RBDR13.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR12.value = (Uns32)(bport1_ab_data.RBDR12.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR11.value = (Uns32)(bport1_ab_data.RBDR11.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR10.value = (Uns32)(bport1_ab_data.RBDR10.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR9.value = (Uns32)(bport1_ab_data.RBDR9.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR8.value = (Uns32)(bport1_ab_data.RBDR8.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR7.value = (Uns32)(bport1_ab_data.RBDR7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR6.value = (Uns32)(bport1_ab_data.RBDR6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR5.value = (Uns32)(bport1_ab_data.RBDR5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR4.value = (Uns32)(bport1_ab_data.RBDR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR3.value = (Uns32)(bport1_ab_data.RBDR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR2.value = (Uns32)(bport1_ab_data.RBDR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR1.value = (Uns32)(bport1_ab_data.RBDR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBDR0.value = (Uns32)(bport1_ab_data.RBDR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LCKCR.value = (Uns32)(bport1_ab_data.LCKCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000002));
        bport1_ab_data.LUTKEY.value = (Uns32)(bport1_ab_data.LUTKEY.value & ~(0xffffffff)) | ((0xffffffff) & (0x5af05af0));
        bport1_ab_data.SFB2AD.value = (Uns32)(bport1_ab_data.SFB2AD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SFB1AD.value = (Uns32)(bport1_ab_data.SFB1AD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SFA2AD.value = (Uns32)(bport1_ab_data.SFA2AD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SFA1AD.value = (Uns32)(bport1_ab_data.SFA1AD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SPTRCLR.value = (Uns32)(bport1_ab_data.SPTRCLR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SPNDST.value = (Uns32)(bport1_ab_data.SPNDST.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RSER.value = (Uns32)(bport1_ab_data.RSER.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.FR.value = (Uns32)(bport1_ab_data.FR.value & ~(0xffffffff)) | ((0xffffffff) & (0x08000000));
        bport1_ab_data.SR.value = (Uns32)(bport1_ab_data.SR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00003800));
        bport1_ab_data.TBDR.value = (Uns32)(bport1_ab_data.TBDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TBSR.value = (Uns32)(bport1_ab_data.TBSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBCT.value = (Uns32)(bport1_ab_data.RBCT.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RBSR.value = (Uns32)(bport1_ab_data.RBSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SMPR.value = (Uns32)(bport1_ab_data.SMPR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SFAR.value = (Uns32)(bport1_ab_data.SFAR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.BUF2IND.value = (Uns32)(bport1_ab_data.BUF2IND.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.BUF1IND.value = (Uns32)(bport1_ab_data.BUF1IND.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.BUF0IND.value = (Uns32)(bport1_ab_data.BUF0IND.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.BFGENCR.value = (Uns32)(bport1_ab_data.BFGENCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.BUF3CR.value = (Uns32)(bport1_ab_data.BUF3CR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.BUF2CR.value = (Uns32)(bport1_ab_data.BUF2CR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.BUF1CR.value = (Uns32)(bport1_ab_data.BUF1CR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.BUF0CR.value = (Uns32)(bport1_ab_data.BUF0CR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.FLSHCR.value = (Uns32)(bport1_ab_data.FLSHCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000303));
        bport1_ab_data.IPCR.value = (Uns32)(bport1_ab_data.IPCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MCR.value = (Uns32)(bport1_ab_data.MCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x000f4000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the QUADSPI peripheral used on the Freescale Vybrid platform");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "Provides the base behaviour for the OVP Freescale Vybrid platforms");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "Development based on document number: VYBRIDRM Rev. 5, 07/2013");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_32_node, "Open Source Apache 2.0");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    reset_Reset(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}


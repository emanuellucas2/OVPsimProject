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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisFMC", "Example");
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

static PPM_WRITE_CB(bport1_ab_DATAW0S0LM_maskWrite) {
    bport1_ab_data.DATAW0S0LM.value = (bport1_ab_data.DATAW0S0LM.value & BPORT1_AB_DATAW0S0LM_WRNMASK) | (data & BPORT1_AB_DATAW0S0LM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S0ML_maskWrite) {
    bport1_ab_data.DATAW0S0ML.value = (bport1_ab_data.DATAW0S0ML.value & BPORT1_AB_DATAW0S0ML_WRNMASK) | (data & BPORT1_AB_DATAW0S0ML_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S0MU_maskWrite) {
    bport1_ab_data.DATAW0S0MU.value = (bport1_ab_data.DATAW0S0MU.value & BPORT1_AB_DATAW0S0MU_WRNMASK) | (data & BPORT1_AB_DATAW0S0MU_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S0UM_maskWrite) {
    bport1_ab_data.DATAW0S0UM.value = (bport1_ab_data.DATAW0S0UM.value & BPORT1_AB_DATAW0S0UM_WRNMASK) | (data & BPORT1_AB_DATAW0S0UM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S1LM_maskWrite) {
    bport1_ab_data.DATAW0S1LM.value = (bport1_ab_data.DATAW0S1LM.value & BPORT1_AB_DATAW0S1LM_WRNMASK) | (data & BPORT1_AB_DATAW0S1LM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S1ML_maskWrite) {
    bport1_ab_data.DATAW0S1ML.value = (bport1_ab_data.DATAW0S1ML.value & BPORT1_AB_DATAW0S1ML_WRNMASK) | (data & BPORT1_AB_DATAW0S1ML_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S1MU_maskWrite) {
    bport1_ab_data.DATAW0S1MU.value = (bport1_ab_data.DATAW0S1MU.value & BPORT1_AB_DATAW0S1MU_WRNMASK) | (data & BPORT1_AB_DATAW0S1MU_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S1UM_maskWrite) {
    bport1_ab_data.DATAW0S1UM.value = (bport1_ab_data.DATAW0S1UM.value & BPORT1_AB_DATAW0S1UM_WRNMASK) | (data & BPORT1_AB_DATAW0S1UM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S2LM_maskWrite) {
    bport1_ab_data.DATAW0S2LM.value = (bport1_ab_data.DATAW0S2LM.value & BPORT1_AB_DATAW0S2LM_WRNMASK) | (data & BPORT1_AB_DATAW0S2LM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S2ML_maskWrite) {
    bport1_ab_data.DATAW0S2ML.value = (bport1_ab_data.DATAW0S2ML.value & BPORT1_AB_DATAW0S2ML_WRNMASK) | (data & BPORT1_AB_DATAW0S2ML_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S2MU_maskWrite) {
    bport1_ab_data.DATAW0S2MU.value = (bport1_ab_data.DATAW0S2MU.value & BPORT1_AB_DATAW0S2MU_WRNMASK) | (data & BPORT1_AB_DATAW0S2MU_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S2UM_maskWrite) {
    bport1_ab_data.DATAW0S2UM.value = (bport1_ab_data.DATAW0S2UM.value & BPORT1_AB_DATAW0S2UM_WRNMASK) | (data & BPORT1_AB_DATAW0S2UM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S3LM_maskWrite) {
    bport1_ab_data.DATAW0S3LM.value = (bport1_ab_data.DATAW0S3LM.value & BPORT1_AB_DATAW0S3LM_WRNMASK) | (data & BPORT1_AB_DATAW0S3LM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S3ML_maskWrite) {
    bport1_ab_data.DATAW0S3ML.value = (bport1_ab_data.DATAW0S3ML.value & BPORT1_AB_DATAW0S3ML_WRNMASK) | (data & BPORT1_AB_DATAW0S3ML_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S3MU_maskWrite) {
    bport1_ab_data.DATAW0S3MU.value = (bport1_ab_data.DATAW0S3MU.value & BPORT1_AB_DATAW0S3MU_WRNMASK) | (data & BPORT1_AB_DATAW0S3MU_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW0S3UM_maskWrite) {
    bport1_ab_data.DATAW0S3UM.value = (bport1_ab_data.DATAW0S3UM.value & BPORT1_AB_DATAW0S3UM_WRNMASK) | (data & BPORT1_AB_DATAW0S3UM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S0LM_maskWrite) {
    bport1_ab_data.DATAW1S0LM.value = (bport1_ab_data.DATAW1S0LM.value & BPORT1_AB_DATAW1S0LM_WRNMASK) | (data & BPORT1_AB_DATAW1S0LM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S0ML_maskWrite) {
    bport1_ab_data.DATAW1S0ML.value = (bport1_ab_data.DATAW1S0ML.value & BPORT1_AB_DATAW1S0ML_WRNMASK) | (data & BPORT1_AB_DATAW1S0ML_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S0MU_maskWrite) {
    bport1_ab_data.DATAW1S0MU.value = (bport1_ab_data.DATAW1S0MU.value & BPORT1_AB_DATAW1S0MU_WRNMASK) | (data & BPORT1_AB_DATAW1S0MU_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S0UM_maskWrite) {
    bport1_ab_data.DATAW1S0UM.value = (bport1_ab_data.DATAW1S0UM.value & BPORT1_AB_DATAW1S0UM_WRNMASK) | (data & BPORT1_AB_DATAW1S0UM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S1LM_maskWrite) {
    bport1_ab_data.DATAW1S1LM.value = (bport1_ab_data.DATAW1S1LM.value & BPORT1_AB_DATAW1S1LM_WRNMASK) | (data & BPORT1_AB_DATAW1S1LM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S1ML_maskWrite) {
    bport1_ab_data.DATAW1S1ML.value = (bport1_ab_data.DATAW1S1ML.value & BPORT1_AB_DATAW1S1ML_WRNMASK) | (data & BPORT1_AB_DATAW1S1ML_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S1MU_maskWrite) {
    bport1_ab_data.DATAW1S1MU.value = (bport1_ab_data.DATAW1S1MU.value & BPORT1_AB_DATAW1S1MU_WRNMASK) | (data & BPORT1_AB_DATAW1S1MU_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S1UM_maskWrite) {
    bport1_ab_data.DATAW1S1UM.value = (bport1_ab_data.DATAW1S1UM.value & BPORT1_AB_DATAW1S1UM_WRNMASK) | (data & BPORT1_AB_DATAW1S1UM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S2LM_maskWrite) {
    bport1_ab_data.DATAW1S2LM.value = (bport1_ab_data.DATAW1S2LM.value & BPORT1_AB_DATAW1S2LM_WRNMASK) | (data & BPORT1_AB_DATAW1S2LM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S2ML_maskWrite) {
    bport1_ab_data.DATAW1S2ML.value = (bport1_ab_data.DATAW1S2ML.value & BPORT1_AB_DATAW1S2ML_WRNMASK) | (data & BPORT1_AB_DATAW1S2ML_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S2MU_maskWrite) {
    bport1_ab_data.DATAW1S2MU.value = (bport1_ab_data.DATAW1S2MU.value & BPORT1_AB_DATAW1S2MU_WRNMASK) | (data & BPORT1_AB_DATAW1S2MU_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S2UM_maskWrite) {
    bport1_ab_data.DATAW1S2UM.value = (bport1_ab_data.DATAW1S2UM.value & BPORT1_AB_DATAW1S2UM_WRNMASK) | (data & BPORT1_AB_DATAW1S2UM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S3LM_maskWrite) {
    bport1_ab_data.DATAW1S3LM.value = (bport1_ab_data.DATAW1S3LM.value & BPORT1_AB_DATAW1S3LM_WRNMASK) | (data & BPORT1_AB_DATAW1S3LM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S3ML_maskWrite) {
    bport1_ab_data.DATAW1S3ML.value = (bport1_ab_data.DATAW1S3ML.value & BPORT1_AB_DATAW1S3ML_WRNMASK) | (data & BPORT1_AB_DATAW1S3ML_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S3MU_maskWrite) {
    bport1_ab_data.DATAW1S3MU.value = (bport1_ab_data.DATAW1S3MU.value & BPORT1_AB_DATAW1S3MU_WRNMASK) | (data & BPORT1_AB_DATAW1S3MU_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW1S3UM_maskWrite) {
    bport1_ab_data.DATAW1S3UM.value = (bport1_ab_data.DATAW1S3UM.value & BPORT1_AB_DATAW1S3UM_WRNMASK) | (data & BPORT1_AB_DATAW1S3UM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S0LM_maskWrite) {
    bport1_ab_data.DATAW2S0LM.value = (bport1_ab_data.DATAW2S0LM.value & BPORT1_AB_DATAW2S0LM_WRNMASK) | (data & BPORT1_AB_DATAW2S0LM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S0ML_maskWrite) {
    bport1_ab_data.DATAW2S0ML.value = (bport1_ab_data.DATAW2S0ML.value & BPORT1_AB_DATAW2S0ML_WRNMASK) | (data & BPORT1_AB_DATAW2S0ML_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S0MU_maskWrite) {
    bport1_ab_data.DATAW2S0MU.value = (bport1_ab_data.DATAW2S0MU.value & BPORT1_AB_DATAW2S0MU_WRNMASK) | (data & BPORT1_AB_DATAW2S0MU_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S0UM_maskWrite) {
    bport1_ab_data.DATAW2S0UM.value = (bport1_ab_data.DATAW2S0UM.value & BPORT1_AB_DATAW2S0UM_WRNMASK) | (data & BPORT1_AB_DATAW2S0UM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S1LM_maskWrite) {
    bport1_ab_data.DATAW2S1LM.value = (bport1_ab_data.DATAW2S1LM.value & BPORT1_AB_DATAW2S1LM_WRNMASK) | (data & BPORT1_AB_DATAW2S1LM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S1ML_maskWrite) {
    bport1_ab_data.DATAW2S1ML.value = (bport1_ab_data.DATAW2S1ML.value & BPORT1_AB_DATAW2S1ML_WRNMASK) | (data & BPORT1_AB_DATAW2S1ML_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S1MU_maskWrite) {
    bport1_ab_data.DATAW2S1MU.value = (bport1_ab_data.DATAW2S1MU.value & BPORT1_AB_DATAW2S1MU_WRNMASK) | (data & BPORT1_AB_DATAW2S1MU_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S1UM_maskWrite) {
    bport1_ab_data.DATAW2S1UM.value = (bport1_ab_data.DATAW2S1UM.value & BPORT1_AB_DATAW2S1UM_WRNMASK) | (data & BPORT1_AB_DATAW2S1UM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S2LM_maskWrite) {
    bport1_ab_data.DATAW2S2LM.value = (bport1_ab_data.DATAW2S2LM.value & BPORT1_AB_DATAW2S2LM_WRNMASK) | (data & BPORT1_AB_DATAW2S2LM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S2ML_maskWrite) {
    bport1_ab_data.DATAW2S2ML.value = (bport1_ab_data.DATAW2S2ML.value & BPORT1_AB_DATAW2S2ML_WRNMASK) | (data & BPORT1_AB_DATAW2S2ML_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S2MU_maskWrite) {
    bport1_ab_data.DATAW2S2MU.value = (bport1_ab_data.DATAW2S2MU.value & BPORT1_AB_DATAW2S2MU_WRNMASK) | (data & BPORT1_AB_DATAW2S2MU_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S2UM_maskWrite) {
    bport1_ab_data.DATAW2S2UM.value = (bport1_ab_data.DATAW2S2UM.value & BPORT1_AB_DATAW2S2UM_WRNMASK) | (data & BPORT1_AB_DATAW2S2UM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S3LM_maskWrite) {
    bport1_ab_data.DATAW2S3LM.value = (bport1_ab_data.DATAW2S3LM.value & BPORT1_AB_DATAW2S3LM_WRNMASK) | (data & BPORT1_AB_DATAW2S3LM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S3ML_maskWrite) {
    bport1_ab_data.DATAW2S3ML.value = (bport1_ab_data.DATAW2S3ML.value & BPORT1_AB_DATAW2S3ML_WRNMASK) | (data & BPORT1_AB_DATAW2S3ML_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S3MU_maskWrite) {
    bport1_ab_data.DATAW2S3MU.value = (bport1_ab_data.DATAW2S3MU.value & BPORT1_AB_DATAW2S3MU_WRNMASK) | (data & BPORT1_AB_DATAW2S3MU_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW2S3UM_maskWrite) {
    bport1_ab_data.DATAW2S3UM.value = (bport1_ab_data.DATAW2S3UM.value & BPORT1_AB_DATAW2S3UM_WRNMASK) | (data & BPORT1_AB_DATAW2S3UM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S0LM_maskWrite) {
    bport1_ab_data.DATAW3S0LM.value = (bport1_ab_data.DATAW3S0LM.value & BPORT1_AB_DATAW3S0LM_WRNMASK) | (data & BPORT1_AB_DATAW3S0LM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S0ML_maskWrite) {
    bport1_ab_data.DATAW3S0ML.value = (bport1_ab_data.DATAW3S0ML.value & BPORT1_AB_DATAW3S0ML_WRNMASK) | (data & BPORT1_AB_DATAW3S0ML_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S0MU_maskWrite) {
    bport1_ab_data.DATAW3S0MU.value = (bport1_ab_data.DATAW3S0MU.value & BPORT1_AB_DATAW3S0MU_WRNMASK) | (data & BPORT1_AB_DATAW3S0MU_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S0UM_maskWrite) {
    bport1_ab_data.DATAW3S0UM.value = (bport1_ab_data.DATAW3S0UM.value & BPORT1_AB_DATAW3S0UM_WRNMASK) | (data & BPORT1_AB_DATAW3S0UM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S1LM_maskWrite) {
    bport1_ab_data.DATAW3S1LM.value = (bport1_ab_data.DATAW3S1LM.value & BPORT1_AB_DATAW3S1LM_WRNMASK) | (data & BPORT1_AB_DATAW3S1LM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S1ML_maskWrite) {
    bport1_ab_data.DATAW3S1ML.value = (bport1_ab_data.DATAW3S1ML.value & BPORT1_AB_DATAW3S1ML_WRNMASK) | (data & BPORT1_AB_DATAW3S1ML_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S1MU_maskWrite) {
    bport1_ab_data.DATAW3S1MU.value = (bport1_ab_data.DATAW3S1MU.value & BPORT1_AB_DATAW3S1MU_WRNMASK) | (data & BPORT1_AB_DATAW3S1MU_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S1UM_maskWrite) {
    bport1_ab_data.DATAW3S1UM.value = (bport1_ab_data.DATAW3S1UM.value & BPORT1_AB_DATAW3S1UM_WRNMASK) | (data & BPORT1_AB_DATAW3S1UM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S2LM_maskWrite) {
    bport1_ab_data.DATAW3S2LM.value = (bport1_ab_data.DATAW3S2LM.value & BPORT1_AB_DATAW3S2LM_WRNMASK) | (data & BPORT1_AB_DATAW3S2LM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S2ML_maskWrite) {
    bport1_ab_data.DATAW3S2ML.value = (bport1_ab_data.DATAW3S2ML.value & BPORT1_AB_DATAW3S2ML_WRNMASK) | (data & BPORT1_AB_DATAW3S2ML_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S2MU_maskWrite) {
    bport1_ab_data.DATAW3S2MU.value = (bport1_ab_data.DATAW3S2MU.value & BPORT1_AB_DATAW3S2MU_WRNMASK) | (data & BPORT1_AB_DATAW3S2MU_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S2UM_maskWrite) {
    bport1_ab_data.DATAW3S2UM.value = (bport1_ab_data.DATAW3S2UM.value & BPORT1_AB_DATAW3S2UM_WRNMASK) | (data & BPORT1_AB_DATAW3S2UM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S3LM_maskWrite) {
    bport1_ab_data.DATAW3S3LM.value = (bport1_ab_data.DATAW3S3LM.value & BPORT1_AB_DATAW3S3LM_WRNMASK) | (data & BPORT1_AB_DATAW3S3LM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S3ML_maskWrite) {
    bport1_ab_data.DATAW3S3ML.value = (bport1_ab_data.DATAW3S3ML.value & BPORT1_AB_DATAW3S3ML_WRNMASK) | (data & BPORT1_AB_DATAW3S3ML_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S3MU_maskWrite) {
    bport1_ab_data.DATAW3S3MU.value = (bport1_ab_data.DATAW3S3MU.value & BPORT1_AB_DATAW3S3MU_WRNMASK) | (data & BPORT1_AB_DATAW3S3MU_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATAW3S3UM_maskWrite) {
    bport1_ab_data.DATAW3S3UM.value = (bport1_ab_data.DATAW3S3UM.value & BPORT1_AB_DATAW3S3UM_WRNMASK) | (data & BPORT1_AB_DATAW3S3UM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PFAPR_maskWrite) {
    bport1_ab_data.PFAPR.value = (bport1_ab_data.PFAPR.value & BPORT1_AB_PFAPR_WRNMASK) | (data & BPORT1_AB_PFAPR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PFB01CR_maskWrite) {
    bport1_ab_data.PFB01CR.value = (bport1_ab_data.PFB01CR.value & BPORT1_AB_PFB01CR_WRNMASK) | (data & BPORT1_AB_PFB01CR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PFB23CR_maskWrite) {
    bport1_ab_data.PFB23CR.value = (bport1_ab_data.PFB23CR.value & BPORT1_AB_PFB23CR_WRNMASK) | (data & BPORT1_AB_PFB23CR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW0S0_maskWrite) {
    bport1_ab_data.TAGVDW0S0.value = (bport1_ab_data.TAGVDW0S0.value & BPORT1_AB_TAGVDW0S0_WRNMASK) | (data & BPORT1_AB_TAGVDW0S0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW0S1_maskWrite) {
    bport1_ab_data.TAGVDW0S1.value = (bport1_ab_data.TAGVDW0S1.value & BPORT1_AB_TAGVDW0S1_WRNMASK) | (data & BPORT1_AB_TAGVDW0S1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW0S2_maskWrite) {
    bport1_ab_data.TAGVDW0S2.value = (bport1_ab_data.TAGVDW0S2.value & BPORT1_AB_TAGVDW0S2_WRNMASK) | (data & BPORT1_AB_TAGVDW0S2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW0S3_maskWrite) {
    bport1_ab_data.TAGVDW0S3.value = (bport1_ab_data.TAGVDW0S3.value & BPORT1_AB_TAGVDW0S3_WRNMASK) | (data & BPORT1_AB_TAGVDW0S3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW1S0_maskWrite) {
    bport1_ab_data.TAGVDW1S0.value = (bport1_ab_data.TAGVDW1S0.value & BPORT1_AB_TAGVDW1S0_WRNMASK) | (data & BPORT1_AB_TAGVDW1S0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW1S1_maskWrite) {
    bport1_ab_data.TAGVDW1S1.value = (bport1_ab_data.TAGVDW1S1.value & BPORT1_AB_TAGVDW1S1_WRNMASK) | (data & BPORT1_AB_TAGVDW1S1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW1S2_maskWrite) {
    bport1_ab_data.TAGVDW1S2.value = (bport1_ab_data.TAGVDW1S2.value & BPORT1_AB_TAGVDW1S2_WRNMASK) | (data & BPORT1_AB_TAGVDW1S2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW1S3_maskWrite) {
    bport1_ab_data.TAGVDW1S3.value = (bport1_ab_data.TAGVDW1S3.value & BPORT1_AB_TAGVDW1S3_WRNMASK) | (data & BPORT1_AB_TAGVDW1S3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW2S0_maskWrite) {
    bport1_ab_data.TAGVDW2S0.value = (bport1_ab_data.TAGVDW2S0.value & BPORT1_AB_TAGVDW2S0_WRNMASK) | (data & BPORT1_AB_TAGVDW2S0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW2S1_maskWrite) {
    bport1_ab_data.TAGVDW2S1.value = (bport1_ab_data.TAGVDW2S1.value & BPORT1_AB_TAGVDW2S1_WRNMASK) | (data & BPORT1_AB_TAGVDW2S1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW2S2_maskWrite) {
    bport1_ab_data.TAGVDW2S2.value = (bport1_ab_data.TAGVDW2S2.value & BPORT1_AB_TAGVDW2S2_WRNMASK) | (data & BPORT1_AB_TAGVDW2S2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW2S3_maskWrite) {
    bport1_ab_data.TAGVDW2S3.value = (bport1_ab_data.TAGVDW2S3.value & BPORT1_AB_TAGVDW2S3_WRNMASK) | (data & BPORT1_AB_TAGVDW2S3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW3S0_maskWrite) {
    bport1_ab_data.TAGVDW3S0.value = (bport1_ab_data.TAGVDW3S0.value & BPORT1_AB_TAGVDW3S0_WRNMASK) | (data & BPORT1_AB_TAGVDW3S0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW3S1_maskWrite) {
    bport1_ab_data.TAGVDW3S1.value = (bport1_ab_data.TAGVDW3S1.value & BPORT1_AB_TAGVDW3S1_WRNMASK) | (data & BPORT1_AB_TAGVDW3S1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW3S2_maskWrite) {
    bport1_ab_data.TAGVDW3S2.value = (bport1_ab_data.TAGVDW3S2.value & BPORT1_AB_TAGVDW3S2_WRNMASK) | (data & BPORT1_AB_TAGVDW3S2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TAGVDW3S3_maskWrite) {
    bport1_ab_data.TAGVDW3S3.value = (bport1_ab_data.TAGVDW3S3.value & BPORT1_AB_TAGVDW3S3_WRNMASK) | (data & BPORT1_AB_TAGVDW3S3_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abPFAPR_reg = ppmCreateRegister(
            "ab_PFAPR",
            "Flash Access Protection Register, offset: 0x0 ",
            handles.bport1,
            0x0,
            4,
            read_32,
            bport1_ab_PFAPR_maskWrite,
            view32,
            &(bport1_ab_data.PFAPR.value),
            True
        );

        ppmCreateRegisterField(abPFAPR_reg, "M0AP", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(abPFAPR_reg, "M0PFD", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abPFAPR_reg, "M1AP", 0, 2, 2, 1, 1);
        ppmCreateRegisterField(abPFAPR_reg, "M1PFD", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abPFAPR_reg, "M2AP", 0, 4, 2, 1, 1);
        ppmCreateRegisterField(abPFAPR_reg, "M2PFD", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abPFAPR_reg, "M3AP", 0, 6, 2, 1, 1);
        ppmCreateRegisterField(abPFAPR_reg, "M3PFD", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abPFAPR_reg, "M4AP", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abPFAPR_reg, "M4PFD", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abPFAPR_reg, "M5AP", 0, 10, 2, 1, 1);
        ppmCreateRegisterField(abPFAPR_reg, "M5PFD", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abPFAPR_reg, "M6AP", 0, 12, 2, 1, 1);
        ppmCreateRegisterField(abPFAPR_reg, "M6PFD", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abPFAPR_reg, "M7AP", 0, 14, 2, 1, 1);
        ppmCreateRegisterField(abPFAPR_reg, "M7PFD", 0, 23, 1, 1, 1);
    }
    {
        registerHandle abPFB01CR_reg = ppmCreateRegister(
            "ab_PFB01CR",
            "Flash Bank 0-1 Control Register, offset: 0x4 ",
            handles.bport1,
            0x4,
            4,
            read_32,
            bport1_ab_PFB01CR_maskWrite,
            view32,
            &(bport1_ab_data.PFB01CR.value),
            True
        );

        ppmCreateRegisterField(abPFB01CR_reg, "B01DCE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPFB01CR_reg, "B01DPE", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPFB01CR_reg, "B01ICE", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abPFB01CR_reg, "B01IPE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPFB01CR_reg, "B01MW", 0, 17, 2, 1, 1);
        ppmCreateRegisterField(abPFB01CR_reg, "B01RWSC", 0, 28, 4, 1, 1);
        ppmCreateRegisterField(abPFB01CR_reg, "B01SEBE", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPFB01CR_reg, "CINV_WAY", 0, 20, 4, 1, 1);
        ppmCreateRegisterField(abPFB01CR_reg, "CLCK_WAY", 0, 24, 4, 1, 1);
        ppmCreateRegisterField(abPFB01CR_reg, "CRC", 0, 5, 3, 1, 1);
        ppmCreateRegisterField(abPFB01CR_reg, "S_B_INV", 0, 19, 1, 1, 1);
    }
    {
        registerHandle abPFB23CR_reg = ppmCreateRegister(
            "ab_PFB23CR",
            "Flash Bank 2-3 Control Register, offset: 0x8 ",
            handles.bport1,
            0x8,
            4,
            read_32,
            bport1_ab_PFB23CR_maskWrite,
            view32,
            &(bport1_ab_data.PFB23CR.value),
            True
        );

        ppmCreateRegisterField(abPFB23CR_reg, "B23DCE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPFB23CR_reg, "B23DPE", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPFB23CR_reg, "B23ICE", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abPFB23CR_reg, "B23IPE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPFB23CR_reg, "B23MW", 0, 17, 2, 1, 1);
        ppmCreateRegisterField(abPFB23CR_reg, "B23RWSC", 0, 28, 4, 1, 1);
        ppmCreateRegisterField(abPFB23CR_reg, "B23SEBE", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abTAGVDW0S0_reg = ppmCreateRegister(
            "ab_TAGVDW0S0",
            "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
            handles.bport1,
            0x100,
            4,
            read_32,
            bport1_ab_TAGVDW0S0_maskWrite,
            view32,
            &(bport1_ab_data.TAGVDW0S0.value),
            True
        );

        ppmCreateRegisterField(abTAGVDW0S0_reg, "tag", 0, 6, 14, 1, 1);
        ppmCreateRegisterField(abTAGVDW0S0_reg, "valid", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abTAGVDW0S1_reg = ppmCreateRegister(
            "ab_TAGVDW0S1",
            "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
            handles.bport1,
            0x104,
            4,
            read_32,
            bport1_ab_TAGVDW0S1_maskWrite,
            view32,
            &(bport1_ab_data.TAGVDW0S1.value),
            True
        );

        ppmCreateRegisterField(abTAGVDW0S1_reg, "tag", 0, 6, 14, 1, 1);
        ppmCreateRegisterField(abTAGVDW0S1_reg, "valid", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abTAGVDW0S2_reg = ppmCreateRegister(
            "ab_TAGVDW0S2",
            "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
            handles.bport1,
            0x108,
            4,
            read_32,
            bport1_ab_TAGVDW0S2_maskWrite,
            view32,
            &(bport1_ab_data.TAGVDW0S2.value),
            True
        );

        ppmCreateRegisterField(abTAGVDW0S2_reg, "tag", 0, 6, 14, 1, 1);
        ppmCreateRegisterField(abTAGVDW0S2_reg, "valid", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abTAGVDW0S3_reg = ppmCreateRegister(
            "ab_TAGVDW0S3",
            "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
            handles.bport1,
            0x10c,
            4,
            read_32,
            bport1_ab_TAGVDW0S3_maskWrite,
            view32,
            &(bport1_ab_data.TAGVDW0S3.value),
            True
        );

        ppmCreateRegisterField(abTAGVDW0S3_reg, "tag", 0, 6, 14, 1, 1);
        ppmCreateRegisterField(abTAGVDW0S3_reg, "valid", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abTAGVDW1S0_reg = ppmCreateRegister(
            "ab_TAGVDW1S0",
            "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
            handles.bport1,
            0x110,
            4,
            read_32,
            bport1_ab_TAGVDW1S0_maskWrite,
            view32,
            &(bport1_ab_data.TAGVDW1S0.value),
            True
        );

        ppmCreateRegisterField(abTAGVDW1S0_reg, "tag", 0, 6, 14, 1, 1);
        ppmCreateRegisterField(abTAGVDW1S0_reg, "valid", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abTAGVDW1S1_reg = ppmCreateRegister(
            "ab_TAGVDW1S1",
            "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
            handles.bport1,
            0x114,
            4,
            read_32,
            bport1_ab_TAGVDW1S1_maskWrite,
            view32,
            &(bport1_ab_data.TAGVDW1S1.value),
            True
        );

        ppmCreateRegisterField(abTAGVDW1S1_reg, "tag", 0, 6, 14, 1, 1);
        ppmCreateRegisterField(abTAGVDW1S1_reg, "valid", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abTAGVDW1S2_reg = ppmCreateRegister(
            "ab_TAGVDW1S2",
            "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
            handles.bport1,
            0x118,
            4,
            read_32,
            bport1_ab_TAGVDW1S2_maskWrite,
            view32,
            &(bport1_ab_data.TAGVDW1S2.value),
            True
        );

        ppmCreateRegisterField(abTAGVDW1S2_reg, "tag", 0, 6, 14, 1, 1);
        ppmCreateRegisterField(abTAGVDW1S2_reg, "valid", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abTAGVDW1S3_reg = ppmCreateRegister(
            "ab_TAGVDW1S3",
            "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
            handles.bport1,
            0x11c,
            4,
            read_32,
            bport1_ab_TAGVDW1S3_maskWrite,
            view32,
            &(bport1_ab_data.TAGVDW1S3.value),
            True
        );

        ppmCreateRegisterField(abTAGVDW1S3_reg, "tag", 0, 6, 14, 1, 1);
        ppmCreateRegisterField(abTAGVDW1S3_reg, "valid", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abTAGVDW2S0_reg = ppmCreateRegister(
            "ab_TAGVDW2S0",
            "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
            handles.bport1,
            0x120,
            4,
            read_32,
            bport1_ab_TAGVDW2S0_maskWrite,
            view32,
            &(bport1_ab_data.TAGVDW2S0.value),
            True
        );

        ppmCreateRegisterField(abTAGVDW2S0_reg, "tag", 0, 6, 14, 1, 1);
        ppmCreateRegisterField(abTAGVDW2S0_reg, "valid", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abTAGVDW2S1_reg = ppmCreateRegister(
            "ab_TAGVDW2S1",
            "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
            handles.bport1,
            0x124,
            4,
            read_32,
            bport1_ab_TAGVDW2S1_maskWrite,
            view32,
            &(bport1_ab_data.TAGVDW2S1.value),
            True
        );

        ppmCreateRegisterField(abTAGVDW2S1_reg, "tag", 0, 6, 14, 1, 1);
        ppmCreateRegisterField(abTAGVDW2S1_reg, "valid", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abTAGVDW2S2_reg = ppmCreateRegister(
            "ab_TAGVDW2S2",
            "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
            handles.bport1,
            0x128,
            4,
            read_32,
            bport1_ab_TAGVDW2S2_maskWrite,
            view32,
            &(bport1_ab_data.TAGVDW2S2.value),
            True
        );

        ppmCreateRegisterField(abTAGVDW2S2_reg, "tag", 0, 6, 14, 1, 1);
        ppmCreateRegisterField(abTAGVDW2S2_reg, "valid", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abTAGVDW2S3_reg = ppmCreateRegister(
            "ab_TAGVDW2S3",
            "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
            handles.bport1,
            0x12c,
            4,
            read_32,
            bport1_ab_TAGVDW2S3_maskWrite,
            view32,
            &(bport1_ab_data.TAGVDW2S3.value),
            True
        );

        ppmCreateRegisterField(abTAGVDW2S3_reg, "tag", 0, 6, 14, 1, 1);
        ppmCreateRegisterField(abTAGVDW2S3_reg, "valid", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abTAGVDW3S0_reg = ppmCreateRegister(
            "ab_TAGVDW3S0",
            "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
            handles.bport1,
            0x130,
            4,
            read_32,
            bport1_ab_TAGVDW3S0_maskWrite,
            view32,
            &(bport1_ab_data.TAGVDW3S0.value),
            True
        );

        ppmCreateRegisterField(abTAGVDW3S0_reg, "tag", 0, 6, 14, 1, 1);
        ppmCreateRegisterField(abTAGVDW3S0_reg, "valid", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abTAGVDW3S1_reg = ppmCreateRegister(
            "ab_TAGVDW3S1",
            "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
            handles.bport1,
            0x134,
            4,
            read_32,
            bport1_ab_TAGVDW3S1_maskWrite,
            view32,
            &(bport1_ab_data.TAGVDW3S1.value),
            True
        );

        ppmCreateRegisterField(abTAGVDW3S1_reg, "tag", 0, 6, 14, 1, 1);
        ppmCreateRegisterField(abTAGVDW3S1_reg, "valid", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abTAGVDW3S2_reg = ppmCreateRegister(
            "ab_TAGVDW3S2",
            "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
            handles.bport1,
            0x138,
            4,
            read_32,
            bport1_ab_TAGVDW3S2_maskWrite,
            view32,
            &(bport1_ab_data.TAGVDW3S2.value),
            True
        );

        ppmCreateRegisterField(abTAGVDW3S2_reg, "tag", 0, 6, 14, 1, 1);
        ppmCreateRegisterField(abTAGVDW3S2_reg, "valid", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abTAGVDW3S3_reg = ppmCreateRegister(
            "ab_TAGVDW3S3",
            "Cache Tag Storage, array offset: 0x100, array step: index*0x10, index2*0x4 ",
            handles.bport1,
            0x13c,
            4,
            read_32,
            bport1_ab_TAGVDW3S3_maskWrite,
            view32,
            &(bport1_ab_data.TAGVDW3S3.value),
            True
        );

        ppmCreateRegisterField(abTAGVDW3S3_reg, "tag", 0, 6, 14, 1, 1);
        ppmCreateRegisterField(abTAGVDW3S3_reg, "valid", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abDATAW0S0UM_reg = ppmCreateRegister(
            "ab_DATAW0S0UM",
            "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x200,
            4,
            read_32,
            bport1_ab_DATAW0S0UM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW0S0UM.value),
            True
        );

        ppmCreateRegisterField(abDATAW0S0UM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW0S0MU_reg = ppmCreateRegister(
            "ab_DATAW0S0MU",
            "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x204,
            4,
            read_32,
            bport1_ab_DATAW0S0MU_maskWrite,
            view32,
            &(bport1_ab_data.DATAW0S0MU.value),
            True
        );

        ppmCreateRegisterField(abDATAW0S0MU_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW0S0ML_reg = ppmCreateRegister(
            "ab_DATAW0S0ML",
            "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x208,
            4,
            read_32,
            bport1_ab_DATAW0S0ML_maskWrite,
            view32,
            &(bport1_ab_data.DATAW0S0ML.value),
            True
        );

        ppmCreateRegisterField(abDATAW0S0ML_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW0S0LM_reg = ppmCreateRegister(
            "ab_DATAW0S0LM",
            "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x20c,
            4,
            read_32,
            bport1_ab_DATAW0S0LM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW0S0LM.value),
            True
        );

        ppmCreateRegisterField(abDATAW0S0LM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW0S1UM_reg = ppmCreateRegister(
            "ab_DATAW0S1UM",
            "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x210,
            4,
            read_32,
            bport1_ab_DATAW0S1UM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW0S1UM.value),
            True
        );

        ppmCreateRegisterField(abDATAW0S1UM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW0S1MU_reg = ppmCreateRegister(
            "ab_DATAW0S1MU",
            "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x214,
            4,
            read_32,
            bport1_ab_DATAW0S1MU_maskWrite,
            view32,
            &(bport1_ab_data.DATAW0S1MU.value),
            True
        );

        ppmCreateRegisterField(abDATAW0S1MU_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW0S1ML_reg = ppmCreateRegister(
            "ab_DATAW0S1ML",
            "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x218,
            4,
            read_32,
            bport1_ab_DATAW0S1ML_maskWrite,
            view32,
            &(bport1_ab_data.DATAW0S1ML.value),
            True
        );

        ppmCreateRegisterField(abDATAW0S1ML_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW0S1LM_reg = ppmCreateRegister(
            "ab_DATAW0S1LM",
            "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x21c,
            4,
            read_32,
            bport1_ab_DATAW0S1LM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW0S1LM.value),
            True
        );

        ppmCreateRegisterField(abDATAW0S1LM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW0S2UM_reg = ppmCreateRegister(
            "ab_DATAW0S2UM",
            "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x220,
            4,
            read_32,
            bport1_ab_DATAW0S2UM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW0S2UM.value),
            True
        );

        ppmCreateRegisterField(abDATAW0S2UM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW0S2MU_reg = ppmCreateRegister(
            "ab_DATAW0S2MU",
            "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x224,
            4,
            read_32,
            bport1_ab_DATAW0S2MU_maskWrite,
            view32,
            &(bport1_ab_data.DATAW0S2MU.value),
            True
        );

        ppmCreateRegisterField(abDATAW0S2MU_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW0S2ML_reg = ppmCreateRegister(
            "ab_DATAW0S2ML",
            "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x228,
            4,
            read_32,
            bport1_ab_DATAW0S2ML_maskWrite,
            view32,
            &(bport1_ab_data.DATAW0S2ML.value),
            True
        );

        ppmCreateRegisterField(abDATAW0S2ML_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW0S2LM_reg = ppmCreateRegister(
            "ab_DATAW0S2LM",
            "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x22c,
            4,
            read_32,
            bport1_ab_DATAW0S2LM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW0S2LM.value),
            True
        );

        ppmCreateRegisterField(abDATAW0S2LM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW0S3UM_reg = ppmCreateRegister(
            "ab_DATAW0S3UM",
            "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x230,
            4,
            read_32,
            bport1_ab_DATAW0S3UM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW0S3UM.value),
            True
        );

        ppmCreateRegisterField(abDATAW0S3UM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW0S3MU_reg = ppmCreateRegister(
            "ab_DATAW0S3MU",
            "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x234,
            4,
            read_32,
            bport1_ab_DATAW0S3MU_maskWrite,
            view32,
            &(bport1_ab_data.DATAW0S3MU.value),
            True
        );

        ppmCreateRegisterField(abDATAW0S3MU_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW0S3ML_reg = ppmCreateRegister(
            "ab_DATAW0S3ML",
            "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x238,
            4,
            read_32,
            bport1_ab_DATAW0S3ML_maskWrite,
            view32,
            &(bport1_ab_data.DATAW0S3ML.value),
            True
        );

        ppmCreateRegisterField(abDATAW0S3ML_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW0S3LM_reg = ppmCreateRegister(
            "ab_DATAW0S3LM",
            "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x23c,
            4,
            read_32,
            bport1_ab_DATAW0S3LM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW0S3LM.value),
            True
        );

        ppmCreateRegisterField(abDATAW0S3LM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW1S0UM_reg = ppmCreateRegister(
            "ab_DATAW1S0UM",
            "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x240,
            4,
            read_32,
            bport1_ab_DATAW1S0UM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW1S0UM.value),
            True
        );

        ppmCreateRegisterField(abDATAW1S0UM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW1S0MU_reg = ppmCreateRegister(
            "ab_DATAW1S0MU",
            "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x244,
            4,
            read_32,
            bport1_ab_DATAW1S0MU_maskWrite,
            view32,
            &(bport1_ab_data.DATAW1S0MU.value),
            True
        );

        ppmCreateRegisterField(abDATAW1S0MU_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW1S0ML_reg = ppmCreateRegister(
            "ab_DATAW1S0ML",
            "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x248,
            4,
            read_32,
            bport1_ab_DATAW1S0ML_maskWrite,
            view32,
            &(bport1_ab_data.DATAW1S0ML.value),
            True
        );

        ppmCreateRegisterField(abDATAW1S0ML_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW1S0LM_reg = ppmCreateRegister(
            "ab_DATAW1S0LM",
            "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x24c,
            4,
            read_32,
            bport1_ab_DATAW1S0LM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW1S0LM.value),
            True
        );

        ppmCreateRegisterField(abDATAW1S0LM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW1S1UM_reg = ppmCreateRegister(
            "ab_DATAW1S1UM",
            "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x250,
            4,
            read_32,
            bport1_ab_DATAW1S1UM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW1S1UM.value),
            True
        );

        ppmCreateRegisterField(abDATAW1S1UM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW1S1MU_reg = ppmCreateRegister(
            "ab_DATAW1S1MU",
            "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x254,
            4,
            read_32,
            bport1_ab_DATAW1S1MU_maskWrite,
            view32,
            &(bport1_ab_data.DATAW1S1MU.value),
            True
        );

        ppmCreateRegisterField(abDATAW1S1MU_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW1S1ML_reg = ppmCreateRegister(
            "ab_DATAW1S1ML",
            "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x258,
            4,
            read_32,
            bport1_ab_DATAW1S1ML_maskWrite,
            view32,
            &(bport1_ab_data.DATAW1S1ML.value),
            True
        );

        ppmCreateRegisterField(abDATAW1S1ML_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW1S1LM_reg = ppmCreateRegister(
            "ab_DATAW1S1LM",
            "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x25c,
            4,
            read_32,
            bport1_ab_DATAW1S1LM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW1S1LM.value),
            True
        );

        ppmCreateRegisterField(abDATAW1S1LM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW1S2UM_reg = ppmCreateRegister(
            "ab_DATAW1S2UM",
            "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x260,
            4,
            read_32,
            bport1_ab_DATAW1S2UM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW1S2UM.value),
            True
        );

        ppmCreateRegisterField(abDATAW1S2UM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW1S2MU_reg = ppmCreateRegister(
            "ab_DATAW1S2MU",
            "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x264,
            4,
            read_32,
            bport1_ab_DATAW1S2MU_maskWrite,
            view32,
            &(bport1_ab_data.DATAW1S2MU.value),
            True
        );

        ppmCreateRegisterField(abDATAW1S2MU_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW1S2ML_reg = ppmCreateRegister(
            "ab_DATAW1S2ML",
            "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x268,
            4,
            read_32,
            bport1_ab_DATAW1S2ML_maskWrite,
            view32,
            &(bport1_ab_data.DATAW1S2ML.value),
            True
        );

        ppmCreateRegisterField(abDATAW1S2ML_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW1S2LM_reg = ppmCreateRegister(
            "ab_DATAW1S2LM",
            "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x26c,
            4,
            read_32,
            bport1_ab_DATAW1S2LM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW1S2LM.value),
            True
        );

        ppmCreateRegisterField(abDATAW1S2LM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW1S3UM_reg = ppmCreateRegister(
            "ab_DATAW1S3UM",
            "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x270,
            4,
            read_32,
            bport1_ab_DATAW1S3UM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW1S3UM.value),
            True
        );

        ppmCreateRegisterField(abDATAW1S3UM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW1S3MU_reg = ppmCreateRegister(
            "ab_DATAW1S3MU",
            "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x274,
            4,
            read_32,
            bport1_ab_DATAW1S3MU_maskWrite,
            view32,
            &(bport1_ab_data.DATAW1S3MU.value),
            True
        );

        ppmCreateRegisterField(abDATAW1S3MU_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW1S3ML_reg = ppmCreateRegister(
            "ab_DATAW1S3ML",
            "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x278,
            4,
            read_32,
            bport1_ab_DATAW1S3ML_maskWrite,
            view32,
            &(bport1_ab_data.DATAW1S3ML.value),
            True
        );

        ppmCreateRegisterField(abDATAW1S3ML_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW1S3LM_reg = ppmCreateRegister(
            "ab_DATAW1S3LM",
            "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x27c,
            4,
            read_32,
            bport1_ab_DATAW1S3LM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW1S3LM.value),
            True
        );

        ppmCreateRegisterField(abDATAW1S3LM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW2S0UM_reg = ppmCreateRegister(
            "ab_DATAW2S0UM",
            "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x280,
            4,
            read_32,
            bport1_ab_DATAW2S0UM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW2S0UM.value),
            True
        );

        ppmCreateRegisterField(abDATAW2S0UM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW2S0MU_reg = ppmCreateRegister(
            "ab_DATAW2S0MU",
            "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x284,
            4,
            read_32,
            bport1_ab_DATAW2S0MU_maskWrite,
            view32,
            &(bport1_ab_data.DATAW2S0MU.value),
            True
        );

        ppmCreateRegisterField(abDATAW2S0MU_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW2S0ML_reg = ppmCreateRegister(
            "ab_DATAW2S0ML",
            "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x288,
            4,
            read_32,
            bport1_ab_DATAW2S0ML_maskWrite,
            view32,
            &(bport1_ab_data.DATAW2S0ML.value),
            True
        );

        ppmCreateRegisterField(abDATAW2S0ML_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW2S0LM_reg = ppmCreateRegister(
            "ab_DATAW2S0LM",
            "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x28c,
            4,
            read_32,
            bport1_ab_DATAW2S0LM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW2S0LM.value),
            True
        );

        ppmCreateRegisterField(abDATAW2S0LM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW2S1UM_reg = ppmCreateRegister(
            "ab_DATAW2S1UM",
            "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x290,
            4,
            read_32,
            bport1_ab_DATAW2S1UM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW2S1UM.value),
            True
        );

        ppmCreateRegisterField(abDATAW2S1UM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW2S1MU_reg = ppmCreateRegister(
            "ab_DATAW2S1MU",
            "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x294,
            4,
            read_32,
            bport1_ab_DATAW2S1MU_maskWrite,
            view32,
            &(bport1_ab_data.DATAW2S1MU.value),
            True
        );

        ppmCreateRegisterField(abDATAW2S1MU_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW2S1ML_reg = ppmCreateRegister(
            "ab_DATAW2S1ML",
            "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x298,
            4,
            read_32,
            bport1_ab_DATAW2S1ML_maskWrite,
            view32,
            &(bport1_ab_data.DATAW2S1ML.value),
            True
        );

        ppmCreateRegisterField(abDATAW2S1ML_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW2S1LM_reg = ppmCreateRegister(
            "ab_DATAW2S1LM",
            "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x29c,
            4,
            read_32,
            bport1_ab_DATAW2S1LM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW2S1LM.value),
            True
        );

        ppmCreateRegisterField(abDATAW2S1LM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW2S2UM_reg = ppmCreateRegister(
            "ab_DATAW2S2UM",
            "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x2a0,
            4,
            read_32,
            bport1_ab_DATAW2S2UM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW2S2UM.value),
            True
        );

        ppmCreateRegisterField(abDATAW2S2UM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW2S2MU_reg = ppmCreateRegister(
            "ab_DATAW2S2MU",
            "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x2a4,
            4,
            read_32,
            bport1_ab_DATAW2S2MU_maskWrite,
            view32,
            &(bport1_ab_data.DATAW2S2MU.value),
            True
        );

        ppmCreateRegisterField(abDATAW2S2MU_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW2S2ML_reg = ppmCreateRegister(
            "ab_DATAW2S2ML",
            "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x2a8,
            4,
            read_32,
            bport1_ab_DATAW2S2ML_maskWrite,
            view32,
            &(bport1_ab_data.DATAW2S2ML.value),
            True
        );

        ppmCreateRegisterField(abDATAW2S2ML_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW2S2LM_reg = ppmCreateRegister(
            "ab_DATAW2S2LM",
            "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x2ac,
            4,
            read_32,
            bport1_ab_DATAW2S2LM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW2S2LM.value),
            True
        );

        ppmCreateRegisterField(abDATAW2S2LM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW2S3UM_reg = ppmCreateRegister(
            "ab_DATAW2S3UM",
            "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x2b0,
            4,
            read_32,
            bport1_ab_DATAW2S3UM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW2S3UM.value),
            True
        );

        ppmCreateRegisterField(abDATAW2S3UM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW2S3MU_reg = ppmCreateRegister(
            "ab_DATAW2S3MU",
            "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x2b4,
            4,
            read_32,
            bport1_ab_DATAW2S3MU_maskWrite,
            view32,
            &(bport1_ab_data.DATAW2S3MU.value),
            True
        );

        ppmCreateRegisterField(abDATAW2S3MU_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW2S3ML_reg = ppmCreateRegister(
            "ab_DATAW2S3ML",
            "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x2b8,
            4,
            read_32,
            bport1_ab_DATAW2S3ML_maskWrite,
            view32,
            &(bport1_ab_data.DATAW2S3ML.value),
            True
        );

        ppmCreateRegisterField(abDATAW2S3ML_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW2S3LM_reg = ppmCreateRegister(
            "ab_DATAW2S3LM",
            "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x2bc,
            4,
            read_32,
            bport1_ab_DATAW2S3LM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW2S3LM.value),
            True
        );

        ppmCreateRegisterField(abDATAW2S3LM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW3S0UM_reg = ppmCreateRegister(
            "ab_DATAW3S0UM",
            "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x2c0,
            4,
            read_32,
            bport1_ab_DATAW3S0UM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW3S0UM.value),
            True
        );

        ppmCreateRegisterField(abDATAW3S0UM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW3S0MU_reg = ppmCreateRegister(
            "ab_DATAW3S0MU",
            "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x2c4,
            4,
            read_32,
            bport1_ab_DATAW3S0MU_maskWrite,
            view32,
            &(bport1_ab_data.DATAW3S0MU.value),
            True
        );

        ppmCreateRegisterField(abDATAW3S0MU_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW3S0ML_reg = ppmCreateRegister(
            "ab_DATAW3S0ML",
            "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x2c8,
            4,
            read_32,
            bport1_ab_DATAW3S0ML_maskWrite,
            view32,
            &(bport1_ab_data.DATAW3S0ML.value),
            True
        );

        ppmCreateRegisterField(abDATAW3S0ML_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW3S0LM_reg = ppmCreateRegister(
            "ab_DATAW3S0LM",
            "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x2cc,
            4,
            read_32,
            bport1_ab_DATAW3S0LM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW3S0LM.value),
            True
        );

        ppmCreateRegisterField(abDATAW3S0LM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW3S1UM_reg = ppmCreateRegister(
            "ab_DATAW3S1UM",
            "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x2d0,
            4,
            read_32,
            bport1_ab_DATAW3S1UM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW3S1UM.value),
            True
        );

        ppmCreateRegisterField(abDATAW3S1UM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW3S1MU_reg = ppmCreateRegister(
            "ab_DATAW3S1MU",
            "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x2d4,
            4,
            read_32,
            bport1_ab_DATAW3S1MU_maskWrite,
            view32,
            &(bport1_ab_data.DATAW3S1MU.value),
            True
        );

        ppmCreateRegisterField(abDATAW3S1MU_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW3S1ML_reg = ppmCreateRegister(
            "ab_DATAW3S1ML",
            "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x2d8,
            4,
            read_32,
            bport1_ab_DATAW3S1ML_maskWrite,
            view32,
            &(bport1_ab_data.DATAW3S1ML.value),
            True
        );

        ppmCreateRegisterField(abDATAW3S1ML_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW3S1LM_reg = ppmCreateRegister(
            "ab_DATAW3S1LM",
            "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x2dc,
            4,
            read_32,
            bport1_ab_DATAW3S1LM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW3S1LM.value),
            True
        );

        ppmCreateRegisterField(abDATAW3S1LM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW3S2UM_reg = ppmCreateRegister(
            "ab_DATAW3S2UM",
            "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x2e0,
            4,
            read_32,
            bport1_ab_DATAW3S2UM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW3S2UM.value),
            True
        );

        ppmCreateRegisterField(abDATAW3S2UM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW3S2MU_reg = ppmCreateRegister(
            "ab_DATAW3S2MU",
            "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x2e4,
            4,
            read_32,
            bport1_ab_DATAW3S2MU_maskWrite,
            view32,
            &(bport1_ab_data.DATAW3S2MU.value),
            True
        );

        ppmCreateRegisterField(abDATAW3S2MU_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW3S2ML_reg = ppmCreateRegister(
            "ab_DATAW3S2ML",
            "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x2e8,
            4,
            read_32,
            bport1_ab_DATAW3S2ML_maskWrite,
            view32,
            &(bport1_ab_data.DATAW3S2ML.value),
            True
        );

        ppmCreateRegisterField(abDATAW3S2ML_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW3S2LM_reg = ppmCreateRegister(
            "ab_DATAW3S2LM",
            "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x2ec,
            4,
            read_32,
            bport1_ab_DATAW3S2LM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW3S2LM.value),
            True
        );

        ppmCreateRegisterField(abDATAW3S2LM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW3S3UM_reg = ppmCreateRegister(
            "ab_DATAW3S3UM",
            "Cache Data Storage (uppermost word), array offset: 0x200, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x2f0,
            4,
            read_32,
            bport1_ab_DATAW3S3UM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW3S3UM.value),
            True
        );

        ppmCreateRegisterField(abDATAW3S3UM_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW3S3MU_reg = ppmCreateRegister(
            "ab_DATAW3S3MU",
            "Cache Data Storage (mid-upper word), array offset: 0x204, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x2f4,
            4,
            read_32,
            bport1_ab_DATAW3S3MU_maskWrite,
            view32,
            &(bport1_ab_data.DATAW3S3MU.value),
            True
        );

        ppmCreateRegisterField(abDATAW3S3MU_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW3S3ML_reg = ppmCreateRegister(
            "ab_DATAW3S3ML",
            "Cache Data Storage (mid-lower word), array offset: 0x208, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x2f8,
            4,
            read_32,
            bport1_ab_DATAW3S3ML_maskWrite,
            view32,
            &(bport1_ab_data.DATAW3S3ML.value),
            True
        );

        ppmCreateRegisterField(abDATAW3S3ML_reg, "data", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDATAW3S3LM_reg = ppmCreateRegister(
            "ab_DATAW3S3LM",
            "Cache Data Storage (lowermost word), array offset: 0x20C, array step: index*0x40, index2*0x10 ",
            handles.bport1,
            0x2fc,
            4,
            read_32,
            bport1_ab_DATAW3S3LM_maskWrite,
            view32,
            &(bport1_ab_data.DATAW3S3LM.value),
            True
        );

        ppmCreateRegisterField(abDATAW3S3LM_reg, "data", 0, 0, 32, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.DATAW3S3LM.value = (Uns32)(bport1_ab_data.DATAW3S3LM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW3S3ML.value = (Uns32)(bport1_ab_data.DATAW3S3ML.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW3S3MU.value = (Uns32)(bport1_ab_data.DATAW3S3MU.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW3S3UM.value = (Uns32)(bport1_ab_data.DATAW3S3UM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW3S2LM.value = (Uns32)(bport1_ab_data.DATAW3S2LM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW3S2ML.value = (Uns32)(bport1_ab_data.DATAW3S2ML.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW3S2MU.value = (Uns32)(bport1_ab_data.DATAW3S2MU.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW3S2UM.value = (Uns32)(bport1_ab_data.DATAW3S2UM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW3S1LM.value = (Uns32)(bport1_ab_data.DATAW3S1LM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW3S1ML.value = (Uns32)(bport1_ab_data.DATAW3S1ML.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW3S1MU.value = (Uns32)(bport1_ab_data.DATAW3S1MU.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW3S1UM.value = (Uns32)(bport1_ab_data.DATAW3S1UM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW3S0LM.value = (Uns32)(bport1_ab_data.DATAW3S0LM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW3S0ML.value = (Uns32)(bport1_ab_data.DATAW3S0ML.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW3S0MU.value = (Uns32)(bport1_ab_data.DATAW3S0MU.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW3S0UM.value = (Uns32)(bport1_ab_data.DATAW3S0UM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW2S3LM.value = (Uns32)(bport1_ab_data.DATAW2S3LM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW2S3ML.value = (Uns32)(bport1_ab_data.DATAW2S3ML.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW2S3MU.value = (Uns32)(bport1_ab_data.DATAW2S3MU.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW2S3UM.value = (Uns32)(bport1_ab_data.DATAW2S3UM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW2S2LM.value = (Uns32)(bport1_ab_data.DATAW2S2LM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW2S2ML.value = (Uns32)(bport1_ab_data.DATAW2S2ML.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW2S2MU.value = (Uns32)(bport1_ab_data.DATAW2S2MU.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW2S2UM.value = (Uns32)(bport1_ab_data.DATAW2S2UM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW2S1LM.value = (Uns32)(bport1_ab_data.DATAW2S1LM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW2S1ML.value = (Uns32)(bport1_ab_data.DATAW2S1ML.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW2S1MU.value = (Uns32)(bport1_ab_data.DATAW2S1MU.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW2S1UM.value = (Uns32)(bport1_ab_data.DATAW2S1UM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW2S0LM.value = (Uns32)(bport1_ab_data.DATAW2S0LM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW2S0ML.value = (Uns32)(bport1_ab_data.DATAW2S0ML.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW2S0MU.value = (Uns32)(bport1_ab_data.DATAW2S0MU.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW2S0UM.value = (Uns32)(bport1_ab_data.DATAW2S0UM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW1S3LM.value = (Uns32)(bport1_ab_data.DATAW1S3LM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW1S3ML.value = (Uns32)(bport1_ab_data.DATAW1S3ML.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW1S3MU.value = (Uns32)(bport1_ab_data.DATAW1S3MU.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW1S3UM.value = (Uns32)(bport1_ab_data.DATAW1S3UM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW1S2LM.value = (Uns32)(bport1_ab_data.DATAW1S2LM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW1S2ML.value = (Uns32)(bport1_ab_data.DATAW1S2ML.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW1S2MU.value = (Uns32)(bport1_ab_data.DATAW1S2MU.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW1S2UM.value = (Uns32)(bport1_ab_data.DATAW1S2UM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW1S1LM.value = (Uns32)(bport1_ab_data.DATAW1S1LM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW1S1ML.value = (Uns32)(bport1_ab_data.DATAW1S1ML.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW1S1MU.value = (Uns32)(bport1_ab_data.DATAW1S1MU.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW1S1UM.value = (Uns32)(bport1_ab_data.DATAW1S1UM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW1S0LM.value = (Uns32)(bport1_ab_data.DATAW1S0LM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW1S0ML.value = (Uns32)(bport1_ab_data.DATAW1S0ML.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW1S0MU.value = (Uns32)(bport1_ab_data.DATAW1S0MU.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW1S0UM.value = (Uns32)(bport1_ab_data.DATAW1S0UM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW0S3LM.value = (Uns32)(bport1_ab_data.DATAW0S3LM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW0S3ML.value = (Uns32)(bport1_ab_data.DATAW0S3ML.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW0S3MU.value = (Uns32)(bport1_ab_data.DATAW0S3MU.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW0S3UM.value = (Uns32)(bport1_ab_data.DATAW0S3UM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW0S2LM.value = (Uns32)(bport1_ab_data.DATAW0S2LM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW0S2ML.value = (Uns32)(bport1_ab_data.DATAW0S2ML.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW0S2MU.value = (Uns32)(bport1_ab_data.DATAW0S2MU.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW0S2UM.value = (Uns32)(bport1_ab_data.DATAW0S2UM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW0S1LM.value = (Uns32)(bport1_ab_data.DATAW0S1LM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW0S1ML.value = (Uns32)(bport1_ab_data.DATAW0S1ML.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW0S1MU.value = (Uns32)(bport1_ab_data.DATAW0S1MU.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW0S1UM.value = (Uns32)(bport1_ab_data.DATAW0S1UM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW0S0LM.value = (Uns32)(bport1_ab_data.DATAW0S0LM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW0S0ML.value = (Uns32)(bport1_ab_data.DATAW0S0ML.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW0S0MU.value = (Uns32)(bport1_ab_data.DATAW0S0MU.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATAW0S0UM.value = (Uns32)(bport1_ab_data.DATAW0S0UM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TAGVDW3S3.value = (Uns32)(bport1_ab_data.TAGVDW3S3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TAGVDW3S2.value = (Uns32)(bport1_ab_data.TAGVDW3S2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TAGVDW3S1.value = (Uns32)(bport1_ab_data.TAGVDW3S1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TAGVDW3S0.value = (Uns32)(bport1_ab_data.TAGVDW3S0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TAGVDW2S3.value = (Uns32)(bport1_ab_data.TAGVDW2S3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TAGVDW2S2.value = (Uns32)(bport1_ab_data.TAGVDW2S2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TAGVDW2S1.value = (Uns32)(bport1_ab_data.TAGVDW2S1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TAGVDW2S0.value = (Uns32)(bport1_ab_data.TAGVDW2S0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TAGVDW1S3.value = (Uns32)(bport1_ab_data.TAGVDW1S3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TAGVDW1S2.value = (Uns32)(bport1_ab_data.TAGVDW1S2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TAGVDW1S1.value = (Uns32)(bport1_ab_data.TAGVDW1S1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TAGVDW1S0.value = (Uns32)(bport1_ab_data.TAGVDW1S0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TAGVDW0S3.value = (Uns32)(bport1_ab_data.TAGVDW0S3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TAGVDW0S2.value = (Uns32)(bport1_ab_data.TAGVDW0S2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TAGVDW0S1.value = (Uns32)(bport1_ab_data.TAGVDW0S1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TAGVDW0S0.value = (Uns32)(bport1_ab_data.TAGVDW0S0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PFB23CR.value = (Uns32)(bport1_ab_data.PFB23CR.value & ~(0xffffffff)) | ((0xffffffff) & (0x3004001f));
        bport1_ab_data.PFB01CR.value = (Uns32)(bport1_ab_data.PFB01CR.value & ~(0xffffffff)) | ((0xffffffff) & (0x3004001f));
        bport1_ab_data.PFAPR.value = (Uns32)(bport1_ab_data.PFAPR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00f8003f));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the FMC peripheral used on the Freescale Kinetis platform");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "Provides the base behaviour for the OVP Freescale Kinetis platforms");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "www.freescale.com/Kinetis");
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


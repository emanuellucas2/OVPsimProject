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

bp1_REG_dataT bp1_REG_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "SpecialFunction", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bp1 = ppmCreateSlaveBusPort("bp1", 16384);
    if (!handles.bp1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bp1'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle REGSF_CIDR_reg = ppmCreateRegister(
            "REG_SF_CIDR",
            0,
            handles.bp1,
            0x0,
            4,
            read_32,
            0,
            view32,
            &(bp1_REG_data.SF_CIDR.value),
            True
        );

        ppmCreateRegisterField(REGSF_CIDR_reg, "EXT", 0, 31, 1, 1, 0);
        ppmCreateRegisterField(REGSF_CIDR_reg, "ARCH", 0, 20, 8, 1, 0);
        ppmCreateRegisterField(REGSF_CIDR_reg, "VDSIZ", 0, 16, 4, 1, 0);
        ppmCreateRegisterField(REGSF_CIDR_reg, "NVDSIZ", 0, 12, 4, 1, 0);
        ppmCreateRegisterField(REGSF_CIDR_reg, "NVPSIZ", 0, 8, 4, 1, 0);
        ppmCreateRegisterField(REGSF_CIDR_reg, "VERSION", 0, 0, 5, 1, 0);
    }
    {
        registerHandle REGSF_EXID_reg = ppmCreateRegister(
            "REG_SF_EXID",
            0,
            handles.bp1,
            0x4,
            4,
            read_32,
            0,
            view32,
            &(bp1_REG_data.SF_EXID.value),
            True
        );

        ppmCreateRegisterField(REGSF_EXID_reg, "RESET", 0, 0, 8, 1, 0);
    }
    {
        ppmCreateRegister(
            "REG_SF_RSR",
            0,
            handles.bp1,
            0x8,
            4,
            read_32,
            0,
            view32,
            &(bp1_REG_data.SF_RSR.value),
            True
        );
    }
    {
        registerHandle REGSF_PMR_reg = ppmCreateRegister(
            "REG_SF_PMR",
            0,
            handles.bp1,
            0x18,
            4,
            read_32,
            SF_PMR_wcb,
            view32,
            &(bp1_REG_data.SF_PMR.value),
            True
        );

        ppmCreateRegisterField(REGSF_PMR_reg, "PMRKEY", 0, 16, 16, 1, 1);
        ppmCreateRegisterField(REGSF_PMR_reg, "AIC", 0, 5, 1, 1, 1);
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bp1_REG_data.SF_PMR.value = (Uns32)(bp1_REG_data.SF_PMR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bp1_REG_data.SF_RSR.value = (Uns32)(bp1_REG_data.SF_RSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bp1_REG_data.SF_EXID.value = (Uns32)(bp1_REG_data.SF_EXID.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bp1_REG_data.SF_CIDR.value = (Uns32)(bp1_REG_data.SF_CIDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x14000040));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "This model contains an accurate Register set interface.\nThe functionality has only been implemented to sufficiently boot uClinux\nThe AT91FR40162SB provides registers that implement the following special functions.\n Chip Identification\n RESET Status\n Protect Mode\nfor more information visit http://www.atmel.com/products/at91");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model is sufficient to boot Linux");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Rev. 1354D ARM08/02");
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
    periphConstructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}


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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "PowerSaving", "Example");
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
        registerHandle REGPS_CR_reg = ppmCreateRegister(
            "REG_PS_CR",
            0,
            handles.bp1,
            0x0,
            4,
            0,
            PS_CR_wcb,
            view32,
            &(bp1_REG_data.PS_CR.value),
            True
        );

        ppmCreateRegisterField(REGPS_CR_reg, "CPU", 0, 0, 1, 0, 1);
    }
    {
        registerHandle REGPS_PCER_reg = ppmCreateRegister(
            "REG_PS_PCER",
            0,
            handles.bp1,
            0x4,
            4,
            0,
            PS_PCER_wcb,
            view32,
            &(bp1_REG_data.PS_PCER.value),
            True
        );

        ppmCreateRegisterField(REGPS_PCER_reg, "PIO", 0, 8, 1, 0, 1);
        ppmCreateRegisterField(REGPS_PCER_reg, "TC2", 0, 6, 1, 0, 1);
        ppmCreateRegisterField(REGPS_PCER_reg, "TC1", 0, 5, 1, 0, 1);
        ppmCreateRegisterField(REGPS_PCER_reg, "TC0", 0, 4, 1, 0, 1);
        ppmCreateRegisterField(REGPS_PCER_reg, "US1", 0, 3, 1, 0, 1);
        ppmCreateRegisterField(REGPS_PCER_reg, "US0", 0, 2, 1, 0, 1);
    }
    {
        registerHandle REGPS_PCDR_reg = ppmCreateRegister(
            "REG_PS_PCDR",
            0,
            handles.bp1,
            0x8,
            4,
            0,
            PS_PCDR_wcb,
            view32,
            &(bp1_REG_data.PS_PCDR.value),
            True
        );

        ppmCreateRegisterField(REGPS_PCDR_reg, "PIO", 0, 8, 1, 0, 1);
        ppmCreateRegisterField(REGPS_PCDR_reg, "TC2", 0, 6, 1, 0, 1);
        ppmCreateRegisterField(REGPS_PCDR_reg, "TC1", 0, 5, 1, 0, 1);
        ppmCreateRegisterField(REGPS_PCDR_reg, "TC0", 0, 4, 1, 0, 1);
        ppmCreateRegisterField(REGPS_PCDR_reg, "US1", 0, 3, 1, 0, 1);
        ppmCreateRegisterField(REGPS_PCDR_reg, "US0", 0, 2, 1, 0, 1);
    }
    {
        registerHandle REGPS_PCSR_reg = ppmCreateRegister(
            "REG_PS_PCSR",
            0,
            handles.bp1,
            0xc,
            4,
            read_32,
            0,
            view32,
            &(bp1_REG_data.PS_PCSR.value),
            True
        );

        ppmCreateRegisterField(REGPS_PCSR_reg, "PIO", 0, 8, 1, 1, 0);
        ppmCreateRegisterField(REGPS_PCSR_reg, "TC2", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(REGPS_PCSR_reg, "TC1", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(REGPS_PCSR_reg, "TC0", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(REGPS_PCSR_reg, "US1", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(REGPS_PCSR_reg, "US0", 0, 2, 1, 1, 0);
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bp1_REG_data.PS_PCSR.value = (Uns32)(bp1_REG_data.PS_PCSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x17c));
        bp1_REG_data.PS_PCDR.value = (Uns32)(bp1_REG_data.PS_PCDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.PS_PCER.value = (Uns32)(bp1_REG_data.PS_PCER.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.PS_CR.value = (Uns32)(bp1_REG_data.PS_CR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "This model contains an accurate Register set interface.\nThe functionality has only been implemented to sufficiently boot uClinux\nfor more information visit http://www.atmel.com/products/at91");
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


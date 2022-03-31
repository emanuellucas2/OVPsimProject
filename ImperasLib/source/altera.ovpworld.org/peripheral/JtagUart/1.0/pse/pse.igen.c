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

sp1_reg0_dataT sp1_reg0_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "JtagUart", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.sp1 = ppmCreateSlaveBusPort("sp1", 8);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle reg0data_reg = ppmCreateRegister(
            "reg0_data",
            0,
            handles.sp1,
            0x0,
            4,
            read_data,
            write_data,
            view32,
            &(sp1_reg0_data.data.value),
            True
        );

        ppmCreateRegisterField(reg0data_reg, "DATA", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(reg0data_reg, "RVALID", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(reg0data_reg, "RAVAIL", 0, 16, 16, 1, 1);
    }
    {
        registerHandle reg0control_reg = ppmCreateRegister(
            "reg0_control",
            0,
            handles.sp1,
            0x4,
            4,
            read_control,
            write_control,
            view32,
            &(sp1_reg0_data.control.value),
            True
        );

        ppmCreateRegisterField(reg0control_reg, "RE", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(reg0control_reg, "WE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(reg0control_reg, "RI", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(reg0control_reg, "WI", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(reg0control_reg, "AC", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(reg0control_reg, "WSPACE", 0, 16, 16, 1, 1);
    }

}

PPM_NET_CB(reset_IRESET) {
    if(value != 0 ) {
        sp1_reg0_data.control.value = (Uns32)(sp1_reg0_data.control.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        sp1_reg0_data.data.value = (Uns32)(sp1_reg0_data.data.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Altera Avalon JTAG UART");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "No Support for pin level transitions");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Embedded Peripherals IP User Guide, UG-01085-11.0 11.0 June 2011");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    reset_IRESET(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}


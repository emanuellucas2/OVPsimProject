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

busPort_A_dataT busPort_A_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "Alpha2x16Display", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

static PPM_WRITE_CB(write_8) { *(Uns8*)user = data; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.busPort = ppmCreateSlaveBusPort("busPort", 4);
    if (!handles.busPort) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'busPort'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle Acontrol_reg = ppmCreateRegister(
            "A_control",
            0,
            handles.busPort,
            0x0,
            1,
            read_8,
            controlWrite,
            view8,
            &(busPort_A_data.control.value),
            True
        );

        ppmCreateRegisterField(Acontrol_reg, "invert", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(Acontrol_reg, "set", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(Acontrol_reg, "clear", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(Acontrol_reg, "enable", 0, 0, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "A_address",
            0,
            handles.busPort,
            0x1,
            1,
            read_8,
            write_8,
            view8,
            &(busPort_A_data.address.value),
            True
        );
    }
    {
        registerHandle Astatus_reg = ppmCreateRegister(
            "A_status",
            0,
            handles.busPort,
            0x2,
            1,
            read_8,
            statusWriteError,
            view8,
            &(busPort_A_data.status.value),
            True
        );

        ppmCreateRegisterField(Astatus_reg, "enable", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(Astatus_reg, "busy", 0, 0, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "A_data",
            0,
            handles.busPort,
            0x3,
            1,
            dataRead,
            dataWrite,
            view8,
            &(busPort_A_data.data.value),
            True
        );
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        busPort_A_data.status.value = (Uns8)(busPort_A_data.status.value & ~(0xff)) | ((0xff) & (0));
        busPort_A_data.address.value = (Uns8)(busPort_A_data.address.value & ~(0xff)) | ((0xff) & (0));
        busPort_A_data.control.value = (Uns8)(busPort_A_data.control.value & ~(0xff)) | ((0xff) & (0));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "This is a simple test peripheral creating a 2x16 alphanumeric display.");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This is not representing a real device and provides simple operations as an example.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "This is not based upon a real device");
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
    userStart();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}


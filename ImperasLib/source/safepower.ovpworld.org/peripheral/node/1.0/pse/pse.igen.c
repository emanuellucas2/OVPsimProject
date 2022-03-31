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

hostif_reg_dataT hostif_reg_data;

hostif_msgtx_dataT hostif_msgtx_data;

hostif_msgrx_dataT hostif_msgrx_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "node", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

static PPM_WRITE_CB(write_32) { *(Uns32*)user = data; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.hostif = ppmCreateSlaveBusPort("hostif", 1024);
    if (!handles.hostif) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'hostif'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "reg_control",
            "Control register",
            handles.hostif,
            0x0,
            4,
            read_32,
            writeControl,
            view32,
            &(hostif_reg_data.control.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg_status",
            "Transfer status register",
            handles.hostif,
            0x4,
            4,
            read_32,
            write_32,
            view32,
            &(hostif_reg_data.status.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "msgtx_id",
            0,
            handles.hostif,
            0x100,
            4,
            read_32,
            write_32,
            view32,
            &(hostif_msgtx_data.id.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "msgtx_from",
            0,
            handles.hostif,
            0x104,
            4,
            read_32,
            write_32,
            view32,
            &(hostif_msgtx_data.from.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "msgtx_nid",
            0,
            handles.hostif,
            0x108,
            4,
            read_32,
            write_32,
            view32,
            &(hostif_msgtx_data.nid.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "msgtx_msgLen",
            0,
            handles.hostif,
            0x10c,
            4,
            read_32,
            write_32,
            view32,
            &(hostif_msgtx_data.msgLen.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "msgrx_id",
            0,
            handles.hostif,
            0x200,
            4,
            read_32,
            write_32,
            view32,
            &(hostif_msgrx_data.id.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "msgrx_from",
            0,
            handles.hostif,
            0x204,
            4,
            read_32,
            write_32,
            view32,
            &(hostif_msgrx_data.from.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "msgrx_nid",
            0,
            handles.hostif,
            0x208,
            4,
            read_32,
            write_32,
            view32,
            &(hostif_msgrx_data.nid.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "msgrx_msgLen",
            0,
            handles.hostif,
            0x20c,
            4,
            read_32,
            write_32,
            view32,
            &(hostif_msgrx_data.msgLen.value),
            True
        );
    }

}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Example Network on Chip (NoC) node peripheral for SafePower Project");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model implements a data and control interface to allow a processor to receive or transmit data across a packetnet interface. This is used to illustrate the use as part of a NoC.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "No Reference, created as an example");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
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


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

hostif_outbox_dataT hostif_outbox_data;

hostif_inbox_dataT hostif_inbox_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "NostrumNode", "Example");
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
    handles.hostif = ppmCreateSlaveBusPort("hostif", 131072);
    if (!handles.hostif) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'hostif'");
    }

    ppmInstallWriteCallback(writeSyncFlag, (void*)0 , handles.hostif + 0xc, 0x4);
    ppmInstallReadCallback(readMsgLength, (void*)0 , handles.hostif + 0x20, 0x20);
    ppmInstallReadCallback(readMsgStatus, (void*)0 , handles.hostif + 0x40, 0x20);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "reg_status",
            0,
            handles.hostif,
            0x0,
            4,
            readStatus,
            0,
            view32,
            &(hostif_reg_data.status.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg_command",
            0,
            handles.hostif,
            0x0,
            4,
            0,
            writeCommand,
            view32,
            &(hostif_reg_data.command.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg_intclr",
            0,
            handles.hostif,
            0x4,
            4,
            0,
            writeIntClr,
            view32,
            &(hostif_reg_data.intclr.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg_intStatus",
            0,
            handles.hostif,
            0x8,
            4,
            readIntStatus,
            0,
            view32,
            &(hostif_reg_data.intStatus.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg_nodeid",
            0,
            handles.hostif,
            0x10,
            4,
            readNodeId,
            0,
            view32,
            &(hostif_reg_data.nodeid.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg_heartbeat",
            0,
            handles.hostif,
            0x10,
            4,
            0,
            writeHeartbeat,
            view32,
            &(hostif_reg_data.heartbeat.value),
            True
        );
    }

}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "The Nostrum Network on Chip (NoC) node peripheral for SafePower Project");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model implements the Nostrum NoC node processor interface. It does not model any timing in the transfer of messages between nodes.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Generated using the VHDL file generic_interface_to_noc_static.vhd provided as part of example December release.");
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


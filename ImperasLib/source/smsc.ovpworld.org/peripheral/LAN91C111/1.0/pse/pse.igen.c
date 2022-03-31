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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "LAN91C111", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

//////////////////////////////// View callbacks ////////////////////////////////

static PPM_VIEW_CB(view_bport1_ab_BANK_SEL) {
    *(Uns16*)data = bport1_ab_data.BANK_SEL.value;
}

static PPM_VIEW_CB(view_bport1_ab_REG_0) {
    *(Uns16*)data = bport1_ab_data.REG_0.value;
}

static PPM_VIEW_CB(view_bport1_ab_REG_2) {
    *(Uns16*)data = bport1_ab_data.REG_2.value;
}

static PPM_VIEW_CB(view_bport1_ab_REG_4) {
    *(Uns16*)data = bport1_ab_data.REG_4.value;
}

static PPM_VIEW_CB(view_bport1_ab_REG_6) {
    *(Uns16*)data = bport1_ab_data.REG_6.value;
}

static PPM_VIEW_CB(view_bport1_ab_REG_8) {
    *(Uns16*)data = bport1_ab_data.REG_8.value;
}

static PPM_VIEW_CB(view_bport1_ab_REG_10) {
    *(Uns16*)data = bport1_ab_data.REG_10.value;
}

static PPM_VIEW_CB(view_bport1_ab_REG_12) {
    *(Uns16*)data = bport1_ab_data.REG_12.value;
}
//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "ab_BANK_SEL",
            0,
            handles.bport1,
            0xe,
            2,
            readReg16,
            writeReg16,
            view_bport1_ab_BANK_SEL,
            (void*)0xE,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_REG_0",
            0,
            handles.bport1,
            0x0,
            2,
            readReg16,
            writeReg16,
            view_bport1_ab_REG_0,
            (void*)0,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_REG_2",
            0,
            handles.bport1,
            0x2,
            2,
            readReg16,
            writeReg16,
            view_bport1_ab_REG_2,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_REG_4",
            0,
            handles.bport1,
            0x4,
            2,
            readReg16,
            writeReg16,
            view_bport1_ab_REG_4,
            (void*)4,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_REG_6",
            0,
            handles.bport1,
            0x6,
            2,
            readReg16,
            writeReg16,
            view_bport1_ab_REG_6,
            (void*)6,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_REG_8",
            0,
            handles.bport1,
            0x8,
            2,
            readReg16,
            writeReg16,
            view_bport1_ab_REG_8,
            (void*)8,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_REG_10",
            0,
            handles.bport1,
            0xa,
            2,
            readReg16,
            writeReg16,
            view_bport1_ab_REG_10,
            (void*)10,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_REG_12",
            0,
            handles.bport1,
            0xc,
            2,
            readReg16,
            writeReg16,
            view_bport1_ab_REG_12,
            (void*)12,
            True
        );
    }

}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "SMSC LAN91C111");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Not all registers and device features are implemented.  Only 16-bit bus interface currently supported.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "SMSC LAN91C111 10/100 Non-PCI Ethernet Single Chip MAC + PHY Datasheet Revision 1.91 (06-01-09)");
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


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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "IntICP", "Example");
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
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "ab_status",
            "IRQ_STATUS",
            handles.bport1,
            0x0,
            4,
            readIRQ,
            0,
            view32,
            &(bport1_ab_data.status.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_level",
            "IRQ_RAWSTAT",
            handles.bport1,
            0x4,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.level.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_enable",
            "IRQ_ENABLE_SET",
            handles.bport1,
            0x8,
            4,
            read_32,
            writeSET,
            view32,
            &(bport1_ab_data.enable.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_clr",
            "IRQ_ENABLE_CLR",
            handles.bport1,
            0xc,
            4,
            0,
            writeCLR,
            view32,
            &(bport1_ab_data.clr.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_softset",
            "INT_SOFTSET",
            handles.bport1,
            0x10,
            4,
            readLEV,
            writeSST,
            view32,
            &(bport1_ab_data.softset.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_softclr",
            "INT_SOFTCLR",
            handles.bport1,
            0x14,
            4,
            0,
            writeSCL,
            view32,
            &(bport1_ab_data.softclr.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_frqstat",
            "FRQ_STATUS",
            handles.bport1,
            0x20,
            4,
            readFIQ,
            0,
            view32,
            &(bport1_ab_data.frqstat.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_rawstat",
            "FRQ_RAWSTAT",
            handles.bport1,
            0x24,
            4,
            readLevel,
            0,
            view32,
            &(bport1_ab_data.rawstat.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_fiqen",
            "FIQ_ENABLESET",
            handles.bport1,
            0x28,
            4,
            0,
            writeFIQS,
            view32,
            &(bport1_ab_data.fiqen.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_fiqenclr",
            "FRQ_ENABLECLR",
            handles.bport1,
            0x2c,
            4,
            0,
            writeFIQC,
            view32,
            &(bport1_ab_data.fiqenclr.value),
            True
        );
    }

}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "ARM Integrator Board interrupt controller");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "none");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "Integrator User Guide Compact Platform Baseboard HBI-0086 (DUI 0159B)");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_32_node, "Open Source Apache 2.0");
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
    return 0;
}


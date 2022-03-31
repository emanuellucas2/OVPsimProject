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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "zynq_7000-qos301", "Example");
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
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

    ppmInstallReadCallback(regNoDefinitionRead, (void*)0 , handles.bport1 + 0x0, 0x1000);
    ppmInstallWriteCallback(regNoDefinitionWrite, (void*)0 , handles.bport1 + 0x0, 0x1000);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "ab_qos_cntl",
            "The QoS control register contains the enable bits for all the regulators.",
            handles.bport1,
            0x10c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.qos_cntl.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_max_ot",
            "Maximum number of outstanding transactions",
            handles.bport1,
            0x110,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.max_ot.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_max_comb_ot",
            "Maximum number of combined outstanding transactions",
            handles.bport1,
            0x114,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.max_comb_ot.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_aw_p",
            "AW channel peak rate",
            handles.bport1,
            0x118,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.aw_p.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_aw_b",
            "AW channel burstiness allowance",
            handles.bport1,
            0x11c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.aw_b.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_aw_r",
            "AW channel average rate",
            handles.bport1,
            0x120,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.aw_r.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ar_p",
            "AR channel peak rate",
            handles.bport1,
            0x124,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ar_p.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ar_b",
            "AR channel burstiness allowance",
            handles.bport1,
            0x128,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ar_b.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ar_r",
            "AR channel average rate",
            handles.bport1,
            0x12c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ar_r.value),
            True
        );
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.ar_r.value = (Uns32)(bport1_ab_data.ar_r.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ar_b.value = (Uns32)(bport1_ab_data.ar_b.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ar_p.value = (Uns32)(bport1_ab_data.ar_p.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.aw_r.value = (Uns32)(bport1_ab_data.aw_r.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.aw_b.value = (Uns32)(bport1_ab_data.aw_b.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.aw_p.value = (Uns32)(bport1_ab_data.aw_p.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.max_comb_ot.value = (Uns32)(bport1_ab_data.max_comb_ot.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.max_ot.value = (Uns32)(bport1_ab_data.max_ot.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.qos_cntl.value = (Uns32)(bport1_ab_data.qos_cntl.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Zynq 7000 Platform Interconnect QoS (qos301)");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model implements the full set of registers. There is no behavior included.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)");
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
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    destructor();
    return 0;
}


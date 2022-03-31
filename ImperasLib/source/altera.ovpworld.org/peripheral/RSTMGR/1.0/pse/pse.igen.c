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

bport1_REGS_dataT bport1_REGS_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "RSTMGR", "Example");
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

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "REGS_stat",
            0,
            handles.bport1,
            0x0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_REGS_data.stat.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REGS_ctrl",
            0,
            handles.bport1,
            0x4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_REGS_data.ctrl.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REGS_counts",
            0,
            handles.bport1,
            0x8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_REGS_data.counts.value),
            True
        );
    }
    {
        registerHandle REGSmpumodrst_reg = ppmCreateRegister(
            "REGS_mpumodrst",
            0,
            handles.bport1,
            0x10,
            4,
            read_32,
            Writempumodrst,
            view32,
            &(bport1_REGS_data.mpumodrst.value),
            True
        );

        ppmCreateRegisterField(REGSmpumodrst_reg, "cpu0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(REGSmpumodrst_reg, "cpu1", 0, 1, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "REGS_permodrst",
            0,
            handles.bport1,
            0x14,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_REGS_data.permodrst.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REGS_per2modrst",
            0,
            handles.bport1,
            0x18,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_REGS_data.per2modrst.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REGS_brgmodrst",
            0,
            handles.bport1,
            0x1c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_REGS_data.brgmodrst.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REGS_miscmodrst",
            0,
            handles.bport1,
            0x20,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_REGS_data.miscmodrst.value),
            True
        );
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_REGS_data.miscmodrst.value = (Uns32)(bport1_REGS_data.miscmodrst.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REGS_data.brgmodrst.value = (Uns32)(bport1_REGS_data.brgmodrst.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000007));
        bport1_REGS_data.per2modrst.value = (Uns32)(bport1_REGS_data.per2modrst.value & ~(0xffffffff)) | ((0xffffffff) & (0x000000ff));
        bport1_REGS_data.permodrst.value = (Uns32)(bport1_REGS_data.permodrst.value & ~(0xffffffff)) | ((0xffffffff) & (0x3fffffff));
        bport1_REGS_data.mpumodrst.value = (Uns32)(bport1_REGS_data.mpumodrst.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000002));
        bport1_REGS_data.counts.value = (Uns32)(bport1_REGS_data.counts.value & ~(0xffffffff)) | ((0xffffffff) & (0x00080080));
        bport1_REGS_data.ctrl.value = (Uns32)(bport1_REGS_data.ctrl.value & ~(0xffffffff)) | ((0xffffffff) & (0x00100000));
        bport1_REGS_data.stat.value = (Uns32)(bport1_REGS_data.stat.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Altera Cyclone V Reset Manager");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "Only register mpumodrst cpu0 and cpu1 reset functionality is implemented");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_22_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Cyclone V Device Handbook Volume 3: Hard Processor System Technical Reference Manual cv_5v4 2013.12.30");
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


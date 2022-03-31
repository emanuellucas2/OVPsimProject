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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "zynq_7000-ocm", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_OCM_CONTROL_maskWrite) {
    bport1_ab_data.OCM_CONTROL.value = (bport1_ab_data.OCM_CONTROL.value & BPORT1_AB_OCM_CONTROL_WRNMASK) | (data & BPORT1_AB_OCM_CONTROL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_OCM_IRQ_STS_maskWrite) {
    bport1_ab_data.OCM_IRQ_STS.value = (bport1_ab_data.OCM_IRQ_STS.value & BPORT1_AB_OCM_IRQ_STS_WRNMASK) | (data & BPORT1_AB_OCM_IRQ_STS_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_OCM_PARITY_CTRL_maskWrite) {
    bport1_ab_data.OCM_PARITY_CTRL.value = (bport1_ab_data.OCM_PARITY_CTRL.value & BPORT1_AB_OCM_PARITY_CTRL_WRNMASK) | (data & BPORT1_AB_OCM_PARITY_CTRL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_OCM_PARITY_ERRADDRESS_maskWrite) {
    bport1_ab_data.OCM_PARITY_ERRADDRESS.value = (bport1_ab_data.OCM_PARITY_ERRADDRESS.value & BPORT1_AB_OCM_PARITY_ERRADDRESS_WRNMASK) | (data & BPORT1_AB_OCM_PARITY_ERRADDRESS_WRMASK);
}

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
        registerHandle abOCM_PARITY_CTRL_reg = ppmCreateRegister(
            "ab_OCM_PARITY_CTRL",
            "Control fields for RAM parity operation",
            handles.bport1,
            0x0,
            4,
            read_32,
            bport1_ab_OCM_PARITY_CTRL_maskWrite,
            view32,
            &(bport1_ab_data.OCM_PARITY_CTRL.value),
            True
        );

        ppmCreateRegisterField(abOCM_PARITY_CTRL_reg, "OP", 0, 5, 15, 1, 1);
        ppmCreateRegisterField(abOCM_PARITY_CTRL_reg, "LF", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abOCM_PARITY_CTRL_reg, "MP", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abOCM_PARITY_CTRL_reg, "SP", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abOCM_PARITY_CTRL_reg, "RR", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abOCM_PARITY_CTRL_reg, "PCD", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abOCM_PARITY_ERRADDRESS_reg = ppmCreateRegister(
            "ab_OCM_PARITY_ERRADDRESS",
            "Stores the first parity error access address. This register is sticky and will retain its value unless explicitly cleared (written with 1's) with an APB write access. The physical RAM address is logged.",
            handles.bport1,
            0x4,
            4,
            read_32,
            bport1_ab_OCM_PARITY_ERRADDRESS_maskWrite,
            view32,
            &(bport1_ab_data.OCM_PARITY_ERRADDRESS.value),
            True
        );

        ppmCreateRegisterField(abOCM_PARITY_ERRADDRESS_reg, "PEA", 0, 0, 14, 1, 1);
    }
    {
        registerHandle abOCM_IRQ_STS_reg = ppmCreateRegister(
            "ab_OCM_IRQ_STS",
            "Status of OCM Interrupt",
            handles.bport1,
            0x8,
            4,
            read_32,
            bport1_ab_OCM_IRQ_STS_maskWrite,
            view32,
            &(bport1_ab_data.OCM_IRQ_STS.value),
            True
        );

        ppmCreateRegisterField(abOCM_IRQ_STS_reg, "LF", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abOCM_IRQ_STS_reg, "MP", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abOCM_IRQ_STS_reg, "SP", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abOCM_CONTROL_reg = ppmCreateRegister(
            "ab_OCM_CONTROL",
            "Control fields for OCM",
            handles.bport1,
            0xc,
            4,
            read_32,
            bport1_ab_OCM_CONTROL_maskWrite,
            view32,
            &(bport1_ab_data.OCM_CONTROL.value),
            True
        );

        ppmCreateRegisterField(abOCM_CONTROL_reg, "ArbShare", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abOCM_CONTROL_reg, "ScuWrPri", 0, 0, 1, 1, 1);
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.OCM_CONTROL.value = (Uns32)(bport1_ab_data.OCM_CONTROL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.OCM_IRQ_STS.value = (Uns32)(bport1_ab_data.OCM_IRQ_STS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.OCM_PARITY_ERRADDRESS.value = (Uns32)(bport1_ab_data.OCM_PARITY_ERRADDRESS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.OCM_PARITY_CTRL.value = (Uns32)(bport1_ab_data.OCM_PARITY_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Zynq 7000 Platform On Chip Memory Controller Registers (OCM)");
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


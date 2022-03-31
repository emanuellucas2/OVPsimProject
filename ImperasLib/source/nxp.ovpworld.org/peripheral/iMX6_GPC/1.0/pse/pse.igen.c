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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "iMX6_GPC", "Example");
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

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_GPC_PGR_maskWrite) {
    bport1_ab_data.GPC_PGR.value = (bport1_ab_data.GPC_PGR.value & BPORT1_AB_GPC_PGR_WRNMASK) | (data & BPORT1_AB_GPC_PGR_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 608);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

    ppmInstallReadCallback(regNoDefinitionRead, (void*)0 , handles.bport1 + 0x0, 0x260);
    ppmInstallWriteCallback(regNoDefinitionWrite, (void*)0 , handles.bport1 + 0x0, 0x260);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abGPC_CNTR_reg = ppmCreateRegister(
            "ab_GPC_CNTR",
            "Description\nGPC Interface control register\nGPC interrupt/event masking\nGPU/VPU Power Up request\nGPU/VPU Power Down request\n",
            handles.bport1,
            0x0,
            4,
            read_32,
            WriteGPC_CNTR,
            view32,
            &(bport1_ab_data.GPC_CNTR.value),
            True
        );

        ppmCreateRegisterField(abGPC_CNTR_reg, "GPCIRQM", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abGPC_CNTR_reg, "VPU_PUP", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abGPC_CNTR_reg, "VPU_PDN", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abGPC_PGR_reg = ppmCreateRegister(
            "ab_GPC_PGR",
            "Description\nGPC Power Gating Register\n\n",
            handles.bport1,
            0x4,
            4,
            read_32,
            bport1_ab_GPC_PGR_maskWrite,
            view32,
            &(bport1_ab_data.GPC_PGR.value),
            True
        );

        ppmCreateRegisterField(abGPC_PGR_reg, "DRCIC", 0, 29, 2, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_GPC_IMR1",
            "IRQ masking register 1",
            handles.bport1,
            0x8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.GPC_IMR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GPC_IMR2",
            "IRQ masking register 2",
            handles.bport1,
            0xc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.GPC_IMR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GPC_IMR3",
            "IRQ masking register 3",
            handles.bport1,
            0x10,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.GPC_IMR3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GPC_IMR4",
            "IRQ masking register 4",
            handles.bport1,
            0x14,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.GPC_IMR4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GPC_ISR1",
            "IRQ status resister 1",
            handles.bport1,
            0x18,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.GPC_ISR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GPC_ISR2",
            "IRQ status resister 2",
            handles.bport1,
            0x1c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.GPC_ISR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GPC_ISR3",
            "IRQ status resister 3",
            handles.bport1,
            0x20,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.GPC_ISR3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GPC_ISR4",
            "IRQ status resister 4",
            handles.bport1,
            0x24,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.GPC_ISR4.value),
            True
        );
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.GPC_ISR4.value = (Uns32)(bport1_ab_data.GPC_ISR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPC_ISR3.value = (Uns32)(bport1_ab_data.GPC_ISR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPC_ISR2.value = (Uns32)(bport1_ab_data.GPC_ISR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPC_ISR1.value = (Uns32)(bport1_ab_data.GPC_ISR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPC_IMR4.value = (Uns32)(bport1_ab_data.GPC_IMR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPC_IMR3.value = (Uns32)(bport1_ab_data.GPC_IMR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPC_IMR2.value = (Uns32)(bport1_ab_data.GPC_IMR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPC_IMR1.value = (Uns32)(bport1_ab_data.GPC_IMR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPC_PGR.value = (Uns32)(bport1_ab_data.GPC_PGR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPC_CNTR.value = (Uns32)(bport1_ab_data.GPC_CNTR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00100000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "NXP i.MX6 GPC General Power Controller");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This is a register only model");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "i.MX 6Solo/6DualLite Applications Processor Reference Manual (IMX6SDLRM_Ref_Manual.pdf");
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


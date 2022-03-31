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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "zynq_7000-spi", "Example");
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
            "ab_Config",
            "SPI configuration register",
            handles.bport1,
            0x0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Config.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Intr_status",
            "SPI interrupt status register",
            handles.bport1,
            0x4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Intr_status.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Intrpt_en",
            "Interrupt Enable register",
            handles.bport1,
            0x8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Intrpt_en.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Intrpt_dis",
            "Interrupt disable register",
            handles.bport1,
            0xc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Intrpt_dis.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Intrpt_mask",
            "Interrupt mask register",
            handles.bport1,
            0x10,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.Intrpt_mask.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_En",
            "SPI_Enable Register",
            handles.bport1,
            0x14,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.En.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Delay",
            "Delay Register",
            handles.bport1,
            0x18,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Delay.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Tx_data",
            "Transmit Data Register.",
            handles.bport1,
            0x1c,
            4,
            0,
            wrData,
            view32,
            &(bport1_ab_data.Tx_data.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Rx_data",
            "Receive Data Register",
            handles.bport1,
            0x20,
            4,
            rdData,
            0,
            view32,
            &(bport1_ab_data.Rx_data.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Slave_Idle_count",
            "Slave Idle Count Register",
            handles.bport1,
            0x24,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Slave_Idle_count.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TX_thres",
            "TX_FIFO Threshold Register",
            handles.bport1,
            0x28,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.TX_thres.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RX_thres",
            "RX FIFO Threshold Register",
            handles.bport1,
            0x2c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.RX_thres.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Mod_id",
            "Module ID register",
            handles.bport1,
            0xfc,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.Mod_id.value),
            True
        );
    }

}

/////////////////////////////// Bus Master Ports ///////////////////////////////

static void installMasterPorts(void) {
    handles.SPI = ppmOpenAddressSpace("SPI");
}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.Mod_id.value = (Uns32)(bport1_ab_data.Mod_id.value & ~(0xffffffff)) | ((0xffffffff) & (0x00090106));
        bport1_ab_data.RX_thres.value = (Uns32)(bport1_ab_data.RX_thres.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bport1_ab_data.TX_thres.value = (Uns32)(bport1_ab_data.TX_thres.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bport1_ab_data.Slave_Idle_count.value = (Uns32)(bport1_ab_data.Slave_Idle_count.value & ~(0xffffffff)) | ((0xffffffff) & (0x000000FF));
        bport1_ab_data.Rx_data.value = (Uns32)(bport1_ab_data.Rx_data.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Tx_data.value = (Uns32)(bport1_ab_data.Tx_data.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Delay.value = (Uns32)(bport1_ab_data.Delay.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.En.value = (Uns32)(bport1_ab_data.En.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Intrpt_mask.value = (Uns32)(bport1_ab_data.Intrpt_mask.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Intrpt_dis.value = (Uns32)(bport1_ab_data.Intrpt_dis.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Intrpt_en.value = (Uns32)(bport1_ab_data.Intrpt_en.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Intr_status.value = (Uns32)(bport1_ab_data.Intr_status.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000004));
        bport1_ab_data.Config.value = (Uns32)(bport1_ab_data.Config.value & ~(0xffffffff)) | ((0xffffffff) & (0x00020000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Zynq 7000 SPI Registers");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model implements the full set of registers but no behavior.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installMasterPorts();
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


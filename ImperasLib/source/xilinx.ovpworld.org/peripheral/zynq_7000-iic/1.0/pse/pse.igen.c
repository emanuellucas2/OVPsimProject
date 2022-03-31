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

I2C_Slave_dr_dataT I2C_Slave_dr_data;

bport1_ab_dataT bport1_ab_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "zynq_7000-iic", "Example");
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

static PPM_WRITE_CB(bport1_ab_SlaveMonPause_maskWrite) {
    bport1_ab_data.SlaveMonPause.value = (bport1_ab_data.SlaveMonPause.value & BPORT1_AB_SLAVEMONPAUSE_WRNMASK) | (data & BPORT1_AB_SLAVEMONPAUSE_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TimeOut_maskWrite) {
    bport1_ab_data.TimeOut.value = (bport1_ab_data.TimeOut.value & BPORT1_AB_TIMEOUT_WRNMASK) | (data & BPORT1_AB_TIMEOUT_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.I2C_Slave = ppmCreateSlaveBusPort("I2C_Slave", 4);

    ppmInstallReadCallback(i2cSlaveRead, (void*)0 , handles.I2C_Slave + 0x0, 0x4);
    ppmInstallWriteCallback(i2cSlaveWrite, (void*)0 , handles.I2C_Slave + 0x0, 0x4);
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

    ppmInstallReadCallback(regNoDefinitionRead, (void*)0 , handles.bport1 + 0x2c, 0xfd4);
    ppmInstallWriteCallback(regNoDefinitionWrite, (void*)0 , handles.bport1 + 0x2c, 0xfd4);
    ppmInstallWriteCallback(wrStatus, (void*)0 , handles.bport1 + 0x4, 0x10);
    ppmInstallWriteCallback(intClear, (void*)0 , handles.bport1 + 0x10, 0x10);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {


    {
        registerHandle abControl_reg = ppmCreateRegister(
            "ab_Control",
            "Control register",
            handles.bport1,
            0x0,
            4,
            read_32,
            wrControl,
            view32,
            &(bport1_ab_data.Control.value),
            True
        );

        ppmCreateRegisterField(abControl_reg, "DIV_A", 0, 14, 2, 1, 1);
        ppmCreateRegisterField(abControl_reg, "DIV_B", 0, 8, 6, 1, 1);
        ppmCreateRegisterField(abControl_reg, "CLR_FIFO", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abControl_reg, "SLVMON", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abControl_reg, "HOLD", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abControl_reg, "ACKEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abControl_reg, "NEA", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abControl_reg, "MS", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abControl_reg, "RW", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abI2CAddress_reg = ppmCreateRegister(
            "ab_I2CAddress",
            "I2C Address register",
            handles.bport1,
            0x8,
            4,
            read_32,
            wrAddress,
            view32,
            &(bport1_ab_data.I2CAddress.value),
            True
        );

        ppmCreateRegisterField(abI2CAddress_reg, "ADD", 0, 0, 9, 1, 1);
    }
    {
        registerHandle abI2CData_reg = ppmCreateRegister(
            "ab_I2CData",
            "I2C Data register",
            handles.bport1,
            0xc,
            4,
            rdData,
            wrData,
            view32,
            &(bport1_ab_data.I2CData.value),
            True
        );

        ppmCreateRegisterField(abI2CData_reg, "DATA", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abTransferSize_reg = ppmCreateRegister(
            "ab_TransferSize",
            "Transfer Size register",
            handles.bport1,
            0x14,
            4,
            rdXSz,
            wrXSz,
            view32,
            &(bport1_ab_data.TransferSize.value),
            True
        );

        ppmCreateRegisterField(abTransferSize_reg, "XFERSZ", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abSlaveMonPause_reg = ppmCreateRegister(
            "ab_SlaveMonPause",
            "Slave Monitor Pause register",
            handles.bport1,
            0x18,
            4,
            read_32,
            bport1_ab_SlaveMonPause_maskWrite,
            view32,
            &(bport1_ab_data.SlaveMonPause.value),
            True
        );

        ppmCreateRegisterField(abSlaveMonPause_reg, "PAUSE", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abTimeOut_reg = ppmCreateRegister(
            "ab_TimeOut",
            "Time Out register",
            handles.bport1,
            0x1c,
            4,
            read_32,
            bport1_ab_TimeOut_maskWrite,
            view32,
            &(bport1_ab_data.TimeOut.value),
            True
        );

        ppmCreateRegisterField(abTimeOut_reg, "TO", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abInterruptMask_reg = ppmCreateRegister(
            "ab_InterruptMask",
            "Interrupt Mask register",
            handles.bport1,
            0x20,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.InterruptMask.value),
            True
        );

        ppmCreateRegisterField(abInterruptMask_reg, "ARB_LOST", 0, 9, 1, 1, 0);
        ppmCreateRegisterField(abInterruptMask_reg, "RX_UNF", 0, 7, 1, 1, 0);
        ppmCreateRegisterField(abInterruptMask_reg, "TX_OVF", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(abInterruptMask_reg, "RX_OVF", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(abInterruptMask_reg, "SLV_RDY", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(abInterruptMask_reg, "TO", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(abInterruptMask_reg, "NACK", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(abInterruptMask_reg, "DATA", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(abInterruptMask_reg, "COMP", 0, 0, 1, 1, 0);
    }
    {
        registerHandle abInterruptEnable_reg = ppmCreateRegister(
            "ab_InterruptEnable",
            "Interrupt Enable register",
            handles.bport1,
            0x24,
            4,
            rdZero,
            intEnable,
            view32,
            &(bport1_ab_data.InterruptEnable.value),
            True
        );

        ppmCreateRegisterField(abInterruptEnable_reg, "ARB_LOST", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abInterruptEnable_reg, "RX_UNF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abInterruptEnable_reg, "TX_OVF", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abInterruptEnable_reg, "RX_OVF", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abInterruptEnable_reg, "SLV_RDY", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abInterruptEnable_reg, "TO", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abInterruptEnable_reg, "NACK", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abInterruptEnable_reg, "DATA", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abInterruptEnable_reg, "COMP", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abInterruptDisable_reg = ppmCreateRegister(
            "ab_InterruptDisable",
            "Interrupt Disable register",
            handles.bport1,
            0x28,
            4,
            rdZero,
            intDisable,
            view32,
            &(bport1_ab_data.InterruptDisable.value),
            True
        );

        ppmCreateRegisterField(abInterruptDisable_reg, "ARB_LOST", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abInterruptDisable_reg, "RX_UNF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abInterruptDisable_reg, "TX_OVF", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abInterruptDisable_reg, "RX_OVF", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abInterruptDisable_reg, "SLV_RDY", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abInterruptDisable_reg, "TO", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abInterruptDisable_reg, "NACK", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abInterruptDisable_reg, "DATA", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abInterruptDisable_reg, "COMP", 0, 0, 1, 1, 1);
    }

}

/////////////////////////////// Bus Master Ports ///////////////////////////////

static void installMasterPorts(void) {
    handles.I2C_Master = ppmOpenAddressSpace("I2C_Master");
}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.InterruptDisable.value = (Uns32)(bport1_ab_data.InterruptDisable.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.InterruptEnable.value = (Uns32)(bport1_ab_data.InterruptEnable.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.InterruptMask.value = (Uns32)(bport1_ab_data.InterruptMask.value & ~(0xffffffff)) | ((0xffffffff) & (0x000002ff));
        bport1_ab_data.TimeOut.value = (Uns32)(bport1_ab_data.TimeOut.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000001f));
        bport1_ab_data.SlaveMonPause.value = (Uns32)(bport1_ab_data.SlaveMonPause.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TransferSize.value = (Uns32)(bport1_ab_data.TransferSize.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.I2CData.value = (Uns32)(bport1_ab_data.I2CData.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.I2CAddress.value = (Uns32)(bport1_ab_data.I2CAddress.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Control.value = (Uns32)(bport1_ab_data.Control.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Zynq 7000 I2C Registers. This model also includes the behaviour for PCA9548 I2C Bus Switch");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model implements the full set of registers and behaviour to read and write the I2C address space.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf).");
        ppmDocAddText(doc_32_node, "Evaluation Board ZC706 (ug954-zc706-eval-board-xc7z045-ap-soc.pdf)");
        ppmDocAddText(doc_32_node, "Evaluation Board ZC702 (ug850-zc702-eval-board.pdf)");
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


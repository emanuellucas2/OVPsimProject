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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "zynq_7000-sdio", "Example");
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

static PPM_WRITE_CB(bport1_ab_ADMA_error_status_maskWrite) {
    bport1_ab_data.ADMA_error_status.value = (bport1_ab_data.ADMA_error_status.value & BPORT1_AB_ADMA_ERROR_STATUS_WRNMASK) | (data & BPORT1_AB_ADMA_ERROR_STATUS_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_Interrupt_signal_enable_maskWrite) {
    bport1_ab_data.Interrupt_signal_enable.value = (bport1_ab_data.Interrupt_signal_enable.value & BPORT1_AB_INTERRUPT_SIGNAL_ENABLE_WRNMASK) | (data & BPORT1_AB_INTERRUPT_SIGNAL_ENABLE_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_Interrupt_status_enable_maskWrite) {
    bport1_ab_data.Interrupt_status_enable.value = (bport1_ab_data.Interrupt_status_enable.value & BPORT1_AB_INTERRUPT_STATUS_ENABLE_WRNMASK) | (data & BPORT1_AB_INTERRUPT_STATUS_ENABLE_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_Interrupt_status_maskWrite) {
    bport1_ab_data.Interrupt_status.value = (bport1_ab_data.Interrupt_status.value & BPORT1_AB_INTERRUPT_STATUS_WRNMASK) | (data & BPORT1_AB_INTERRUPT_STATUS_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SPI_interrupt_support_maskWrite) {
    bport1_ab_data.SPI_interrupt_support.value = (bport1_ab_data.SPI_interrupt_support.value & BPORT1_AB_SPI_INTERRUPT_SUPPORT_WRNMASK) | (data & BPORT1_AB_SPI_INTERRUPT_SUPPORT_WRMASK);
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
        ppmCreateRegister(
            "ab_SDMA_system_address_register",
            "System DMA Address Register",
            handles.bport1,
            0x0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.SDMA_system_address_register.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Block_Size_Block_Count",
            "Block size register / Block count register",
            handles.bport1,
            0x4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Block_Size_Block_Count.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Argument",
            "Argument register",
            handles.bport1,
            0x8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Argument.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Transfer_Mode_Command",
            "Transfer mode register / Command register",
            handles.bport1,
            0xc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Transfer_Mode_Command.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Response0",
            "Response register",
            handles.bport1,
            0x10,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.Response0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Response1",
            "Response register",
            handles.bport1,
            0x14,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.Response1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Response2",
            "Response register",
            handles.bport1,
            0x18,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.Response2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Response3",
            "Response register",
            handles.bport1,
            0x1c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.Response3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Buffer_Data_Port",
            "Buffer data port register",
            handles.bport1,
            0x20,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Buffer_Data_Port.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Present_State",
            "Present State register",
            handles.bport1,
            0x24,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.Present_State.value),
            True
        );
    }
    {
        registerHandle abHost_Power_Block_Gap_Wakeup_control_reg = ppmCreateRegister(
            "ab_Host_Power_Block_Gap_Wakeup_control",
            "(Host_control_Power_control_Block_Gap_Control_Wakeup_control) Host control register / Power control register / Block gap control register / Wake-up control register",
            handles.bport1,
            0x28,
            4,
            read_32,
            wrPwrCtrl,
            view32,
            &(bport1_ab_data.Host_Power_Block_Gap_Wakeup_control.value),
            True
        );

        ppmCreateRegisterField(abHost_Power_Block_Gap_Wakeup_control_reg, "LED", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abClock_Timeout_control_Software_reset_reg = ppmCreateRegister(
            "ab_Clock_Timeout_control_Software_reset",
            "(Clock_Control_Timeout_control_Software_reset) Clock Control register / Timeout control register / Software reset register",
            handles.bport1,
            0x2c,
            4,
            read_32,
            wrClkCtrl,
            view32,
            &(bport1_ab_data.Clock_Timeout_control_Software_reset.value),
            True
        );

        ppmCreateRegisterField(abClock_Timeout_control_Software_reset_reg, "SWRST_DAT", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abClock_Timeout_control_Software_reset_reg, "SWRST_CMD", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abClock_Timeout_control_Software_reset_reg, "SWRST_ALL", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abClock_Timeout_control_Software_reset_reg, "ICLKST", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abClock_Timeout_control_Software_reset_reg, "ICLKEN", 0, 0, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_Interrupt_status",
            "(Normal_interrupt_status_Error_interrupt_status) Normal interrupt status register / Error interrupt status register",
            handles.bport1,
            0x30,
            4,
            read_32,
            bport1_ab_Interrupt_status_maskWrite,
            view32,
            &(bport1_ab_data.Interrupt_status.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Interrupt_status_enable",
            "(Normal_interrupt_status_enable_Error_interrupt_status_enable) Normal interrupt status enable register / Error interrupt status enable register",
            handles.bport1,
            0x34,
            4,
            read_32,
            bport1_ab_Interrupt_status_enable_maskWrite,
            view32,
            &(bport1_ab_data.Interrupt_status_enable.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Interrupt_signal_enable",
            "(Normal_interrupt_signal_enable_Error_interrupt_signal_enable) Normal interrupt signal enable   register / Error interrupt signal enable register",
            handles.bport1,
            0x38,
            4,
            read_32,
            bport1_ab_Interrupt_signal_enable_maskWrite,
            view32,
            &(bport1_ab_data.Interrupt_signal_enable.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Auto_CMD12_error_status",
            "Auto CMD12 error status register",
            handles.bport1,
            0x3c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.Auto_CMD12_error_status.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Capabilities",
            "Capabilities register",
            handles.bport1,
            0x40,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.Capabilities.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Maximum_current_capabilities",
            "Maximum current capabilities register",
            handles.bport1,
            0x48,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.Maximum_current_capabilities.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Force_event",
            "(Force_event_for_AutoCmd12_Error_Status_Force_event_register_for_error_interrupt_status) Force event register for Auto CMD12 error status register / Force event register for error interrupt status",
            handles.bport1,
            0x50,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Force_event.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ADMA_error_status",
            "ADMA error status register",
            handles.bport1,
            0x54,
            4,
            read_32,
            bport1_ab_ADMA_error_status_maskWrite,
            view32,
            &(bport1_ab_data.ADMA_error_status.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ADMA_system_address",
            "ADMA system address register",
            handles.bport1,
            0x58,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ADMA_system_address.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Boot_Timeout_control",
            "Boot Timeout control register",
            handles.bport1,
            0x60,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Boot_Timeout_control.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Debug_Selection",
            "Debug Selection Register",
            handles.bport1,
            0x64,
            4,
            0,
            wrDebugSel,
            view32,
            &(bport1_ab_data.Debug_Selection.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_SPI_interrupt_support",
            "SPI interrupt support register",
            handles.bport1,
            0xf0,
            4,
            read_32,
            bport1_ab_SPI_interrupt_support_maskWrite,
            view32,
            &(bport1_ab_data.SPI_interrupt_support.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Slot_status_Host_version",
            "(Slot_interrupt_status_Host_controller_version) Slot interrupt status register and Host controller version register",
            handles.bport1,
            0xfc,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.Slot_status_Host_version.value),
            True
        );
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.Slot_status_Host_version.value = (Uns32)(bport1_ab_data.Slot_status_Host_version.value & ~(0xffffffff)) | ((0xffffffff) & (0x89010000));
        bport1_ab_data.SPI_interrupt_support.value = (Uns32)(bport1_ab_data.SPI_interrupt_support.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Debug_Selection.value = (Uns32)(bport1_ab_data.Debug_Selection.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Boot_Timeout_control.value = (Uns32)(bport1_ab_data.Boot_Timeout_control.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ADMA_system_address.value = (Uns32)(bport1_ab_data.ADMA_system_address.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ADMA_error_status.value = (Uns32)(bport1_ab_data.ADMA_error_status.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Force_event.value = (Uns32)(bport1_ab_data.Force_event.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Maximum_current_capabilities.value = (Uns32)(bport1_ab_data.Maximum_current_capabilities.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bport1_ab_data.Capabilities.value = (Uns32)(bport1_ab_data.Capabilities.value & ~(0xffffffff)) | ((0xffffffff) & (0x69EC0080));
        bport1_ab_data.Auto_CMD12_error_status.value = (Uns32)(bport1_ab_data.Auto_CMD12_error_status.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Interrupt_signal_enable.value = (Uns32)(bport1_ab_data.Interrupt_signal_enable.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Interrupt_status_enable.value = (Uns32)(bport1_ab_data.Interrupt_status_enable.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Interrupt_status.value = (Uns32)(bport1_ab_data.Interrupt_status.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Clock_Timeout_control_Software_reset.value = (Uns32)(bport1_ab_data.Clock_Timeout_control_Software_reset.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Host_Power_Block_Gap_Wakeup_control.value = (Uns32)(bport1_ab_data.Host_Power_Block_Gap_Wakeup_control.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Present_State.value = (Uns32)(bport1_ab_data.Present_State.value & ~(0xffffffff)) | ((0xffffffff) & (0x01F20000));
        bport1_ab_data.Buffer_Data_Port.value = (Uns32)(bport1_ab_data.Buffer_Data_Port.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Response3.value = (Uns32)(bport1_ab_data.Response3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Response2.value = (Uns32)(bport1_ab_data.Response2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Response1.value = (Uns32)(bport1_ab_data.Response1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Response0.value = (Uns32)(bport1_ab_data.Response0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Transfer_Mode_Command.value = (Uns32)(bport1_ab_data.Transfer_Mode_Command.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Argument.value = (Uns32)(bport1_ab_data.Argument.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Block_Size_Block_Count.value = (Uns32)(bport1_ab_data.Block_Size_Block_Count.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SDMA_system_address_register.value = (Uns32)(bport1_ab_data.SDMA_system_address_register.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Zynq 7000 SD/SDIO Registers");
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


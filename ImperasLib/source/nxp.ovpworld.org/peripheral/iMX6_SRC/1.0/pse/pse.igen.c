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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "iMX6_SRC", "Example");
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
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 16384);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

    ppmInstallReadCallback(regNoDefinitionRead, (void*)0 , handles.bport1 + 0x0, 0x4000);
    ppmInstallWriteCallback(regNoDefinitionWrite, (void*)0 , handles.bport1 + 0x0, 0x4000);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abSRC_SCR_reg = ppmCreateRegister(
            "ab_SRC_SCR",
            "SRC Control Register (SRC_SCR)",
            handles.bport1,
            0x0,
            4,
            ReadSRC_SCR,
            WriteSRC_SCR,
            view32,
            &(bport1_ab_data.SRC_SCR.value),
            True
        );

        ppmCreateRegisterField(abSRC_SCR_reg, "DBG_RST_MSK", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abSRC_SCR_reg, "CORE1EN", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abSRC_SCR_reg, "CORES_DBG_RST", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abSRC_SCR_reg, "CORE1_DBG_RST", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abSRC_SCR_reg, "CORE0_DBG_RST", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abSRC_SCR_reg, "CORE1_RST", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abSRC_SCR_reg, "CORE0_RST", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abSRC_SCR_reg, "EIM_RST", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abSRC_SCR_reg, "MSK_WDG_RST", 0, 7, 4, 1, 1);
        ppmCreateRegisterField(abSRC_SCR_reg, "WRM_RST_BYPASS", 0, 5, 2, 1, 1);
        ppmCreateRegisterField(abSRC_SCR_reg, "SW_OPVG_RST", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abSRC_SCR_reg, "SW_IPU1_RST", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abSRC_SCR_reg, "SW_VPU_RST", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abSRC_SCR_reg, "SW_GPU_RST", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abSRC_SCR_reg, "WARM_RST_EN", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abSRC_SBMR1_reg = ppmCreateRegister(
            "ab_SRC_SBMR1",
            "SRC Boot Mode Register 1 (SRC_SBMR1)",
            handles.bport1,
            0x4,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.SRC_SBMR1.value),
            True
        );

        ppmCreateRegisterField(abSRC_SBMR1_reg, "BOOT_CFG4", 0, 24, 8, 1, 0);
        ppmCreateRegisterField(abSRC_SBMR1_reg, "BOOT_CFG3", 0, 16, 8, 1, 0);
        ppmCreateRegisterField(abSRC_SBMR1_reg, "BOOT_CFG2", 0, 8, 8, 1, 0);
        ppmCreateRegisterField(abSRC_SBMR1_reg, "BOOT_CFG1", 0, 0, 8, 1, 0);
    }
    {
        registerHandle abSRC_SRSR_reg = ppmCreateRegister(
            "ab_SRC_SRSR",
            "SRC Reset Status Register (SRC_SRSR)",
            handles.bport1,
            0x8,
            4,
            ReadSRC_SRSR,
            WriteSRC_SRSR,
            view32,
            &(bport1_ab_data.SRC_SRSR.value),
            True
        );

        ppmCreateRegisterField(abSRC_SRSR_reg, "WARM_BOOT", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abSRC_SRSR_reg, "JTAG_SW_RST", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abSRC_SRSR_reg, "JTAG_RST", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abSRC_SRSR_reg, "WDOG_RST", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abSRC_SRSR_reg, "IPP_USER_RST", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abSRC_SRSR_reg, "CSU_RST", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abSRC_SRSR_reg, "IPP_RST", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abSRC_SISR_reg = ppmCreateRegister(
            "ab_SRC_SISR",
            "SRC Interrupt Status Register (SRC_SISR)",
            handles.bport1,
            0xc,
            4,
            ReadSRC_SISR,
            0,
            view32,
            &(bport1_ab_data.SRC_SISR.value),
            True
        );

        ppmCreateRegisterField(abSRC_SISR_reg, "CORE1_WDOG", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(abSRC_SISR_reg, "CORE0_WDOG", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(abSRC_SISR_reg, "OP_VG_PASS", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(abSRC_SISR_reg, "IPU1_PASS", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(abSRC_SISR_reg, "VPU_PASS", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(abSRC_SISR_reg, "GPU_PASS", 0, 0, 1, 1, 0);
    }
    {
        registerHandle abSRC_SIMR_reg = ppmCreateRegister(
            "ab_SRC_SIMR",
            "SRC Interrupt Mask Register (SRC_SIMR)",
            handles.bport1,
            0x10,
            4,
            ReadSRC_SIMR,
            WriteSRC_SIMR,
            view32,
            &(bport1_ab_data.SRC_SIMR.value),
            True
        );

        ppmCreateRegisterField(abSRC_SIMR_reg, "OP_VG_PASS", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abSRC_SIMR_reg, "IPU1_PASS", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abSRC_SIMR_reg, "VPU_PASS", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abSRC_SIMR_reg, "GPU_PASS", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abSRC_SBMR2_reg = ppmCreateRegister(
            "ab_SRC_SBMR2",
            "SRC Boot Mode Register 2 (SRC_SBMR2)",
            handles.bport1,
            0x14,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.SRC_SBMR2.value),
            True
        );

        ppmCreateRegisterField(abSRC_SBMR2_reg, "BMOD", 0, 24, 2, 1, 0);
        ppmCreateRegisterField(abSRC_SBMR2_reg, "BT_FUSE_SEL", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(abSRC_SBMR2_reg, "DIR_BT_DIS", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(abSRC_SBMR2_reg, "SEC_CONFIG", 0, 0, 2, 1, 0);
    }
    {
        ppmCreateRegister(
            "ab_SRC_GPR1",
            "SRC General Purpose Register 1 (SRC_GPR1)",
            handles.bport1,
            0x18,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.SRC_GPR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_SRC_GPR2",
            "SRC General Purpose Register 2 (SRC_GPR2)",
            handles.bport1,
            0x1c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.SRC_GPR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_SRC_GPR3",
            "SRC General Purpose Register 3 (SRC_GPR3)",
            handles.bport1,
            0x20,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.SRC_GPR3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_SRC_GPR4",
            "SRC General Purpose Register 4 (SRC_GPR4)",
            handles.bport1,
            0x24,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.SRC_GPR4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_SRC_GPR5",
            "SRC General Purpose Register 5 (SRC_GPR5)",
            handles.bport1,
            0x28,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.SRC_GPR5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_SRC_GPR6",
            "SRC General Purpose Register 6 (SRC_GPR6)",
            handles.bport1,
            0x2c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.SRC_GPR6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_SRC_GPR7",
            "SRC General Purpose Register 7 (SRC_GPR7)",
            handles.bport1,
            0x30,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.SRC_GPR7.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_SRC_GPR8",
            "SRC General Purpose Register 8 (SRC_GPR8)",
            handles.bport1,
            0x34,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.SRC_GPR8.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_SRC_GPR9",
            "SRC General Purpose Register 9 (SRC_GPR9)",
            handles.bport1,
            0x38,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.SRC_GPR9.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_SRC_GPR10",
            "SRC General Purpose Register 10 (SRC_GPR10)",
            handles.bport1,
            0x3c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.SRC_GPR10.value),
            True
        );
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.SRC_GPR10.value = (Uns32)(bport1_ab_data.SRC_GPR10.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SRC_GPR9.value = (Uns32)(bport1_ab_data.SRC_GPR9.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SRC_GPR8.value = (Uns32)(bport1_ab_data.SRC_GPR8.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SRC_GPR7.value = (Uns32)(bport1_ab_data.SRC_GPR7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SRC_GPR6.value = (Uns32)(bport1_ab_data.SRC_GPR6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SRC_GPR5.value = (Uns32)(bport1_ab_data.SRC_GPR5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SRC_GPR4.value = (Uns32)(bport1_ab_data.SRC_GPR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SRC_GPR3.value = (Uns32)(bport1_ab_data.SRC_GPR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SRC_GPR2.value = (Uns32)(bport1_ab_data.SRC_GPR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SRC_GPR1.value = (Uns32)(bport1_ab_data.SRC_GPR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SRC_SBMR2.value = (Uns32)(bport1_ab_data.SRC_SBMR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SRC_SIMR.value = (Uns32)(bport1_ab_data.SRC_SIMR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000001F));
        bport1_ab_data.SRC_SISR.value = (Uns32)(bport1_ab_data.SRC_SISR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SRC_SRSR.value = (Uns32)(bport1_ab_data.SRC_SRSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bport1_ab_data.SRC_SBMR1.value = (Uns32)(bport1_ab_data.SRC_SBMR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SRC_SCR.value = (Uns32)(bport1_ab_data.SRC_SCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000521));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "NXP i.MX6 System Reset Control (SRC)");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Implements the power on reset and core1 enable requirements.");
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


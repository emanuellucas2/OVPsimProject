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

bport1_ab2_dataT bport1_ab2_data[4];

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisPIT", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abMCR_reg = ppmCreateNByteRegister(
            "ab_MCR",
            0,
            handles.bport1,
            0x0,
            4,
            0,
            writeMCR,
            0,
            &(bport1_ab_data.MCR.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abMCR_reg, "FRZ", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abMCR_reg, "MDIS", 0, 1, 1, 1, 1);
    }
    {
        registerHandle ab2LDVAL_reg = ppmCreateNByteRegister(
            "ab2_0_LDVAL",
            "Timer Load Value Register",
            handles.bport1,
            0x100,
            4,
            0,
            0,
            0,
            &(bport1_ab2_data[0].LDVAL.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(ab2LDVAL_reg, "TSV", 0, 0, 32, 1, 1);
    }
    {
        registerHandle ab2CVAL_reg = ppmCreateNByteRegister(
            "ab2_0_CVAL",
            "Current Timer Value Register",
            handles.bport1,
            0x104,
            4,
            readCVAL,
            0,
            viewCVAL,
            &(bport1_ab2_data[0].CVAL.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(ab2CVAL_reg, "TVL", 0, 0, 32, 1, 1);
    }
    {
        registerHandle ab2TCTRL_reg = ppmCreateNByteRegister(
            "ab2_0_TCTRL",
            "Timer Control Register",
            handles.bport1,
            0x108,
            4,
            0,
            writeTCTRL,
            0,
            &(bport1_ab2_data[0].TCTRL.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(ab2TCTRL_reg, "TEN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(ab2TCTRL_reg, "TIE", 0, 1, 1, 1, 1);
    }
    {
        registerHandle ab2TFLG_reg = ppmCreateNByteRegister(
            "ab2_0_TFLG",
            "Timer Flag Register",
            handles.bport1,
            0x10c,
            4,
            0,
            writeTFLG,
            0,
            &(bport1_ab2_data[0].TFLG.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(ab2TFLG_reg, "TIF", 0, 0, 1, 1, 1);
    }
    {
        registerHandle ab2LDVAL_reg = ppmCreateNByteRegister(
            "ab2_1_LDVAL",
            "Timer Load Value Register",
            handles.bport1,
            0x110,
            4,
            0,
            0,
            0,
            &(bport1_ab2_data[1].LDVAL.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(ab2LDVAL_reg, "TSV", 0, 0, 32, 1, 1);
    }
    {
        registerHandle ab2CVAL_reg = ppmCreateNByteRegister(
            "ab2_1_CVAL",
            "Current Timer Value Register",
            handles.bport1,
            0x114,
            4,
            readCVAL,
            0,
            viewCVAL,
            &(bport1_ab2_data[1].CVAL.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(ab2CVAL_reg, "TVL", 0, 0, 32, 1, 1);
    }
    {
        registerHandle ab2TCTRL_reg = ppmCreateNByteRegister(
            "ab2_1_TCTRL",
            "Timer Control Register",
            handles.bport1,
            0x118,
            4,
            0,
            writeTCTRL,
            0,
            &(bport1_ab2_data[1].TCTRL.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(ab2TCTRL_reg, "TEN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(ab2TCTRL_reg, "TIE", 0, 1, 1, 1, 1);
    }
    {
        registerHandle ab2TFLG_reg = ppmCreateNByteRegister(
            "ab2_1_TFLG",
            "Timer Flag Register",
            handles.bport1,
            0x11c,
            4,
            0,
            writeTFLG,
            0,
            &(bport1_ab2_data[1].TFLG.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(ab2TFLG_reg, "TIF", 0, 0, 1, 1, 1);
    }
    {
        registerHandle ab2LDVAL_reg = ppmCreateNByteRegister(
            "ab2_2_LDVAL",
            "Timer Load Value Register",
            handles.bport1,
            0x120,
            4,
            0,
            0,
            0,
            &(bport1_ab2_data[2].LDVAL.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(ab2LDVAL_reg, "TSV", 0, 0, 32, 1, 1);
    }
    {
        registerHandle ab2CVAL_reg = ppmCreateNByteRegister(
            "ab2_2_CVAL",
            "Current Timer Value Register",
            handles.bport1,
            0x124,
            4,
            readCVAL,
            0,
            viewCVAL,
            &(bport1_ab2_data[2].CVAL.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(ab2CVAL_reg, "TVL", 0, 0, 32, 1, 1);
    }
    {
        registerHandle ab2TCTRL_reg = ppmCreateNByteRegister(
            "ab2_2_TCTRL",
            "Timer Control Register",
            handles.bport1,
            0x128,
            4,
            0,
            writeTCTRL,
            0,
            &(bport1_ab2_data[2].TCTRL.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(ab2TCTRL_reg, "TEN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(ab2TCTRL_reg, "TIE", 0, 1, 1, 1, 1);
    }
    {
        registerHandle ab2TFLG_reg = ppmCreateNByteRegister(
            "ab2_2_TFLG",
            "Timer Flag Register",
            handles.bport1,
            0x12c,
            4,
            0,
            writeTFLG,
            0,
            &(bport1_ab2_data[2].TFLG.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(ab2TFLG_reg, "TIF", 0, 0, 1, 1, 1);
    }
    {
        registerHandle ab2LDVAL_reg = ppmCreateNByteRegister(
            "ab2_3_LDVAL",
            "Timer Load Value Register",
            handles.bport1,
            0x130,
            4,
            0,
            0,
            0,
            &(bport1_ab2_data[3].LDVAL.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(ab2LDVAL_reg, "TSV", 0, 0, 32, 1, 1);
    }
    {
        registerHandle ab2CVAL_reg = ppmCreateNByteRegister(
            "ab2_3_CVAL",
            "Current Timer Value Register",
            handles.bport1,
            0x134,
            4,
            readCVAL,
            0,
            viewCVAL,
            &(bport1_ab2_data[3].CVAL.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(ab2CVAL_reg, "TVL", 0, 0, 32, 1, 1);
    }
    {
        registerHandle ab2TCTRL_reg = ppmCreateNByteRegister(
            "ab2_3_TCTRL",
            "Timer Control Register",
            handles.bport1,
            0x138,
            4,
            0,
            writeTCTRL,
            0,
            &(bport1_ab2_data[3].TCTRL.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(ab2TCTRL_reg, "TEN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(ab2TCTRL_reg, "TIE", 0, 1, 1, 1, 1);
    }
    {
        registerHandle ab2TFLG_reg = ppmCreateNByteRegister(
            "ab2_3_TFLG",
            "Timer Flag Register",
            handles.bport1,
            0x13c,
            4,
            0,
            writeTFLG,
            0,
            &(bport1_ab2_data[3].TFLG.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(ab2TFLG_reg, "TIF", 0, 0, 1, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab2_data[0].TFLG.value = (Uns32)(bport1_ab2_data[0].TFLG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab2_data[1].TFLG.value = (Uns32)(bport1_ab2_data[1].TFLG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab2_data[2].TFLG.value = (Uns32)(bport1_ab2_data[2].TFLG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab2_data[3].TFLG.value = (Uns32)(bport1_ab2_data[3].TFLG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab2_data[0].TCTRL.value = (Uns32)(bport1_ab2_data[0].TCTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab2_data[1].TCTRL.value = (Uns32)(bport1_ab2_data[1].TCTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab2_data[2].TCTRL.value = (Uns32)(bport1_ab2_data[2].TCTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab2_data[3].TCTRL.value = (Uns32)(bport1_ab2_data[3].TCTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab2_data[0].CVAL.value = (Uns32)(bport1_ab2_data[0].CVAL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab2_data[1].CVAL.value = (Uns32)(bport1_ab2_data[1].CVAL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab2_data[2].CVAL.value = (Uns32)(bport1_ab2_data[2].CVAL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab2_data[3].CVAL.value = (Uns32)(bport1_ab2_data[3].CVAL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab2_data[0].LDVAL.value = (Uns32)(bport1_ab2_data[0].LDVAL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab2_data[1].LDVAL.value = (Uns32)(bport1_ab2_data[1].LDVAL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab2_data[2].LDVAL.value = (Uns32)(bport1_ab2_data[2].LDVAL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab2_data[3].LDVAL.value = (Uns32)(bport1_ab2_data[3].LDVAL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MCR.value = (Uns32)(bport1_ab_data.MCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000002));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the PIT peripheral used on the Freescale Kinetis platform");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "Provides the base behaviour for the OVP Freescale Kinetis platforms");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "www.freescale.com/Kinetis");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_32_node, "Open Source Apache 2.0");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    reset_Reset(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}


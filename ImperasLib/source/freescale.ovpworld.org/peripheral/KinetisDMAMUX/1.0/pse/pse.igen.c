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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisDMAMUX", "Example");
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
        registerHandle abCHCFG_reg = ppmCreateNByteRegister(
            "ab_CHCFG0",
            0,
            handles.bport1,
            0x0,
            1,
            0,
            dmamuxWrite,
            0,
            &(bport1_ab_data.CHCFG[0].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abCHCFG_reg, "ENBL", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "SOURCE", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "TRIG", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abCHCFG_reg = ppmCreateNByteRegister(
            "ab_CHCFG1",
            0,
            handles.bport1,
            0x1,
            1,
            0,
            dmamuxWrite,
            0,
            &(bport1_ab_data.CHCFG[1].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abCHCFG_reg, "ENBL", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "SOURCE", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "TRIG", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abCHCFG_reg = ppmCreateNByteRegister(
            "ab_CHCFG2",
            0,
            handles.bport1,
            0x2,
            1,
            0,
            dmamuxWrite,
            0,
            &(bport1_ab_data.CHCFG[2].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abCHCFG_reg, "ENBL", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "SOURCE", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "TRIG", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abCHCFG_reg = ppmCreateNByteRegister(
            "ab_CHCFG3",
            0,
            handles.bport1,
            0x3,
            1,
            0,
            dmamuxWrite,
            0,
            &(bport1_ab_data.CHCFG[3].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abCHCFG_reg, "ENBL", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "SOURCE", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "TRIG", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abCHCFG_reg = ppmCreateNByteRegister(
            "ab_CHCFG4",
            0,
            handles.bport1,
            0x4,
            1,
            0,
            dmamuxWrite,
            0,
            &(bport1_ab_data.CHCFG[4].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abCHCFG_reg, "ENBL", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "SOURCE", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "TRIG", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abCHCFG_reg = ppmCreateNByteRegister(
            "ab_CHCFG5",
            0,
            handles.bport1,
            0x5,
            1,
            0,
            dmamuxWrite,
            0,
            &(bport1_ab_data.CHCFG[5].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abCHCFG_reg, "ENBL", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "SOURCE", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "TRIG", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abCHCFG_reg = ppmCreateNByteRegister(
            "ab_CHCFG6",
            0,
            handles.bport1,
            0x6,
            1,
            0,
            dmamuxWrite,
            0,
            &(bport1_ab_data.CHCFG[6].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abCHCFG_reg, "ENBL", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "SOURCE", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "TRIG", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abCHCFG_reg = ppmCreateNByteRegister(
            "ab_CHCFG7",
            0,
            handles.bport1,
            0x7,
            1,
            0,
            dmamuxWrite,
            0,
            &(bport1_ab_data.CHCFG[7].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abCHCFG_reg, "ENBL", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "SOURCE", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "TRIG", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abCHCFG_reg = ppmCreateNByteRegister(
            "ab_CHCFG8",
            0,
            handles.bport1,
            0x8,
            1,
            0,
            dmamuxWrite,
            0,
            &(bport1_ab_data.CHCFG[8].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abCHCFG_reg, "ENBL", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "SOURCE", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "TRIG", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abCHCFG_reg = ppmCreateNByteRegister(
            "ab_CHCFG9",
            0,
            handles.bport1,
            0x9,
            1,
            0,
            dmamuxWrite,
            0,
            &(bport1_ab_data.CHCFG[9].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abCHCFG_reg, "ENBL", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "SOURCE", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "TRIG", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abCHCFG_reg = ppmCreateNByteRegister(
            "ab_CHCFG10",
            0,
            handles.bport1,
            0xa,
            1,
            0,
            dmamuxWrite,
            0,
            &(bport1_ab_data.CHCFG[10].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abCHCFG_reg, "ENBL", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "SOURCE", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "TRIG", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abCHCFG_reg = ppmCreateNByteRegister(
            "ab_CHCFG11",
            0,
            handles.bport1,
            0xb,
            1,
            0,
            dmamuxWrite,
            0,
            &(bport1_ab_data.CHCFG[11].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abCHCFG_reg, "ENBL", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "SOURCE", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "TRIG", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abCHCFG_reg = ppmCreateNByteRegister(
            "ab_CHCFG12",
            0,
            handles.bport1,
            0xc,
            1,
            0,
            dmamuxWrite,
            0,
            &(bport1_ab_data.CHCFG[12].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abCHCFG_reg, "ENBL", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "SOURCE", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "TRIG", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abCHCFG_reg = ppmCreateNByteRegister(
            "ab_CHCFG13",
            0,
            handles.bport1,
            0xd,
            1,
            0,
            dmamuxWrite,
            0,
            &(bport1_ab_data.CHCFG[13].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abCHCFG_reg, "ENBL", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "SOURCE", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "TRIG", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abCHCFG_reg = ppmCreateNByteRegister(
            "ab_CHCFG14",
            0,
            handles.bport1,
            0xe,
            1,
            0,
            dmamuxWrite,
            0,
            &(bport1_ab_data.CHCFG[14].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abCHCFG_reg, "ENBL", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "SOURCE", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "TRIG", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abCHCFG_reg = ppmCreateNByteRegister(
            "ab_CHCFG15",
            0,
            handles.bport1,
            0xf,
            1,
            0,
            dmamuxWrite,
            0,
            &(bport1_ab_data.CHCFG[15].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abCHCFG_reg, "ENBL", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "SOURCE", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(abCHCFG_reg, "TRIG", 0, 6, 1, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.CHCFG[0].value = (Uns8)(bport1_ab_data.CHCFG[0].value & ~(0xff)) | ((0xff) & (0));
        bport1_ab_data.CHCFG[1].value = (Uns8)(bport1_ab_data.CHCFG[1].value & ~(0xff)) | ((0xff) & (0));
        bport1_ab_data.CHCFG[2].value = (Uns8)(bport1_ab_data.CHCFG[2].value & ~(0xff)) | ((0xff) & (0));
        bport1_ab_data.CHCFG[3].value = (Uns8)(bport1_ab_data.CHCFG[3].value & ~(0xff)) | ((0xff) & (0));
        bport1_ab_data.CHCFG[4].value = (Uns8)(bport1_ab_data.CHCFG[4].value & ~(0xff)) | ((0xff) & (0));
        bport1_ab_data.CHCFG[5].value = (Uns8)(bport1_ab_data.CHCFG[5].value & ~(0xff)) | ((0xff) & (0));
        bport1_ab_data.CHCFG[6].value = (Uns8)(bport1_ab_data.CHCFG[6].value & ~(0xff)) | ((0xff) & (0));
        bport1_ab_data.CHCFG[7].value = (Uns8)(bport1_ab_data.CHCFG[7].value & ~(0xff)) | ((0xff) & (0));
        bport1_ab_data.CHCFG[8].value = (Uns8)(bport1_ab_data.CHCFG[8].value & ~(0xff)) | ((0xff) & (0));
        bport1_ab_data.CHCFG[9].value = (Uns8)(bport1_ab_data.CHCFG[9].value & ~(0xff)) | ((0xff) & (0));
        bport1_ab_data.CHCFG[10].value = (Uns8)(bport1_ab_data.CHCFG[10].value & ~(0xff)) | ((0xff) & (0));
        bport1_ab_data.CHCFG[11].value = (Uns8)(bport1_ab_data.CHCFG[11].value & ~(0xff)) | ((0xff) & (0));
        bport1_ab_data.CHCFG[12].value = (Uns8)(bport1_ab_data.CHCFG[12].value & ~(0xff)) | ((0xff) & (0));
        bport1_ab_data.CHCFG[13].value = (Uns8)(bport1_ab_data.CHCFG[13].value & ~(0xff)) | ((0xff) & (0));
        bport1_ab_data.CHCFG[14].value = (Uns8)(bport1_ab_data.CHCFG[14].value & ~(0xff)) | ((0xff) & (0));
        bport1_ab_data.CHCFG[15].value = (Uns8)(bport1_ab_data.CHCFG[15].value & ~(0xff)) | ((0xff) & (0));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the DMAMUX peripheral used on the Freescale Kinetis platform");
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


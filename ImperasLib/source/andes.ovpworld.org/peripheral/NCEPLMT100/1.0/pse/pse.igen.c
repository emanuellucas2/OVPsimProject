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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "NCEPLMT100", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 256);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

    ppmInstallNByteCallbacks(defaultMemRead, defaultMemWrite, 0, handles.bport1, 0x0, 0x100, True, True, False, BHM_ENDIAN_LITTLE);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abmtime_reg = ppmCreateNByteRegister(
            "ab_mtime",
            "Constant frequency real-time counter",
            handles.bport1,
            0x0,
            8,
            rdMTIME,
            wrMTIME,
            viewMTIME,
            &(bport1_ab_data.mtime.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtime_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp0",
            "Compare Register MTIMECMP",
            handles.bport1,
            0x8,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[0].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp1",
            "Compare Register MTIMECMP",
            handles.bport1,
            0x10,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[1].value),
            (void*)1,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp2",
            "Compare Register MTIMECMP",
            handles.bport1,
            0x18,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[2].value),
            (void*)2,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp3",
            "Compare Register MTIMECMP",
            handles.bport1,
            0x20,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[3].value),
            (void*)3,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp4",
            "Compare Register MTIMECMP",
            handles.bport1,
            0x28,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[4].value),
            (void*)4,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp5",
            "Compare Register MTIMECMP",
            handles.bport1,
            0x30,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[5].value),
            (void*)5,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp6",
            "Compare Register MTIMECMP",
            handles.bport1,
            0x38,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[6].value),
            (void*)6,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp7",
            "Compare Register MTIMECMP",
            handles.bport1,
            0x40,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[7].value),
            (void*)7,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp8",
            "Compare Register MTIMECMP",
            handles.bport1,
            0x48,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[8].value),
            (void*)8,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp9",
            "Compare Register MTIMECMP",
            handles.bport1,
            0x50,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[9].value),
            (void*)9,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp10",
            "Compare Register MTIMECMP",
            handles.bport1,
            0x58,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[10].value),
            (void*)10,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp11",
            "Compare Register MTIMECMP",
            handles.bport1,
            0x60,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[11].value),
            (void*)11,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp12",
            "Compare Register MTIMECMP",
            handles.bport1,
            0x68,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[12].value),
            (void*)12,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp13",
            "Compare Register MTIMECMP",
            handles.bport1,
            0x70,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[13].value),
            (void*)13,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp14",
            "Compare Register MTIMECMP",
            handles.bport1,
            0x78,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[14].value),
            (void*)14,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp15",
            "Compare Register MTIMECMP",
            handles.bport1,
            0x80,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[15].value),
            (void*)15,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp16",
            "Compare Register MTIMECMP",
            handles.bport1,
            0x88,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[16].value),
            (void*)16,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp17",
            "Compare Register MTIMECMP",
            handles.bport1,
            0x90,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[17].value),
            (void*)17,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp18",
            "Compare Register MTIMECMP",
            handles.bport1,
            0x98,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[18].value),
            (void*)18,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp19",
            "Compare Register MTIMECMP",
            handles.bport1,
            0xa0,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[19].value),
            (void*)19,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp20",
            "Compare Register MTIMECMP",
            handles.bport1,
            0xa8,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[20].value),
            (void*)20,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp21",
            "Compare Register MTIMECMP",
            handles.bport1,
            0xb0,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[21].value),
            (void*)21,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp22",
            "Compare Register MTIMECMP",
            handles.bport1,
            0xb8,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[22].value),
            (void*)22,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp23",
            "Compare Register MTIMECMP",
            handles.bport1,
            0xc0,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[23].value),
            (void*)23,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp24",
            "Compare Register MTIMECMP",
            handles.bport1,
            0xc8,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[24].value),
            (void*)24,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp25",
            "Compare Register MTIMECMP",
            handles.bport1,
            0xd0,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[25].value),
            (void*)25,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp26",
            "Compare Register MTIMECMP",
            handles.bport1,
            0xd8,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[26].value),
            (void*)26,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp27",
            "Compare Register MTIMECMP",
            handles.bport1,
            0xe0,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[27].value),
            (void*)27,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp28",
            "Compare Register MTIMECMP",
            handles.bport1,
            0xe8,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[28].value),
            (void*)28,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp29",
            "Compare Register MTIMECMP",
            handles.bport1,
            0xf0,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[29].value),
            (void*)29,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }
    {
        registerHandle abmtimecmp_reg = ppmCreateNByteRegister(
            "ab_mtimecmp30",
            "Compare Register MTIMECMP",
            handles.bport1,
            0xf8,
            8,
            rdMTIMECMP,
            wrMTIMECMP,
            0,
            &(bport1_ab_data.mtimecmp[30].value),
            (void*)30,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abmtimecmp_reg, "d", 0, 0, 64, 1, 1);
    }

}

PPM_NET_CB(reset_reset) {
    if(value != 0 ) {
        bport1_ab_data.mtimecmp[0].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[1].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[2].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[3].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[4].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[5].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[6].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[7].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[8].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[9].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[10].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[11].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[12].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[13].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[14].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[15].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[16].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[17].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[18].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[19].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[20].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[21].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[22].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[23].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[24].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[25].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[26].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[27].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[28].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[29].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtimecmp[30].bits.d = 0xFFFFFFFFFFFFFFFFLL;
        bport1_ab_data.mtime.bits.d = 0x0LL;
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "NCEPLMT100 Platform-Level Machine Timer");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "A max of 31 timers, rather then the hardware max of 32 is supported by the model. This has not been changed in order to preserve backward compatability of the model's port size, but may be changed locally if needed.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "AndeStar_V5_Timer_UM167_v1.1.pdf 2018-03-07");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    reset_reset(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}


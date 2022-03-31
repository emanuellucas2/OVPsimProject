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

LOGICP0_reg0_dataT LOGICP0_reg0_data;

LOGICP1_reg0_dataT LOGICP1_reg0_data;

LOGICP2_reg0_dataT LOGICP2_reg0_data;

LOGICP3_reg0_dataT LOGICP3_reg0_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "UPD70F3441Logic", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.LOGICP0 = ppmCreateSlaveBusPort("LOGICP0", 4);

    handles.LOGICP1 = ppmCreateSlaveBusPort("LOGICP1", 118);

    handles.LOGICP2 = ppmCreateSlaveBusPort("LOGICP2", 12);

    handles.LOGICP3 = ppmCreateSlaveBusPort("LOGICP3", 1);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle reg0INTSEL_reg = ppmCreateRegister(
            "reg0_INTSEL",
            0,
            handles.LOGICP0,
            0x0,
            1,
            read_8,
            writeSEL,
            view8,
            &(LOGICP0_reg0_data.INTSEL.value),
            True
        );

        ppmCreateRegisterField(reg0INTSEL_reg, "BRGSSR", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(reg0INTSEL_reg, "INTSEL4", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(reg0INTSEL_reg, "ISR", 0, 7, 1, 1, 1);
    }
    {
        registerHandle reg0INTERRF_reg = ppmCreateRegister(
            "reg0_INTERRF",
            0,
            handles.LOGICP0,
            0x2,
            1,
            read_8,
            writeERR,
            view8,
            &(LOGICP0_reg0_data.INTERRF.value),
            True
        );

        ppmCreateRegisterField(reg0INTERRF_reg, "INTERR0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(reg0INTERRF_reg, "INTERR1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(reg0INTERRF_reg, "INTERR2", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(reg0INTERRF_reg, "INTERR7", 0, 7, 1, 1, 1);
    }

    {
        ppmCreateRegister(
            "reg0_LOGICP0",
            0,
            handles.LOGICP1,
            0x0,
            1,
            read_8,
            0,
            view8,
            &(LOGICP1_reg0_data.LOGICP0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_P1",
            0,
            handles.LOGICP1,
            0x2,
            1,
            read_8,
            writeP,
            view8,
            &(LOGICP1_reg0_data.P1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PM1",
            0,
            handles.LOGICP1,
            0x22,
            1,
            read_8,
            writePM,
            view8,
            &(LOGICP1_reg0_data.PM1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PMC1",
            0,
            handles.LOGICP1,
            0x42,
            1,
            read_8,
            writePMC,
            view8,
            &(LOGICP1_reg0_data.PMC1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_P2",
            0,
            handles.LOGICP1,
            0x4,
            1,
            read_8,
            writeP,
            view8,
            &(LOGICP1_reg0_data.P2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PM2",
            0,
            handles.LOGICP1,
            0x24,
            1,
            read_8,
            writePM,
            view8,
            &(LOGICP1_reg0_data.PM2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PMC2",
            0,
            handles.LOGICP1,
            0x44,
            1,
            read_8,
            writePMC,
            view8,
            &(LOGICP1_reg0_data.PMC2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_P3",
            0,
            handles.LOGICP1,
            0x6,
            1,
            read_8,
            writeP,
            view8,
            &(LOGICP1_reg0_data.P3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PM3",
            0,
            handles.LOGICP1,
            0x26,
            1,
            read_8,
            writePM,
            view8,
            &(LOGICP1_reg0_data.PM3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PMC3",
            0,
            handles.LOGICP1,
            0x46,
            1,
            read_8,
            writePMC,
            view8,
            &(LOGICP1_reg0_data.PMC3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_P4",
            0,
            handles.LOGICP1,
            0x8,
            1,
            read_8,
            writeP,
            view8,
            &(LOGICP1_reg0_data.P4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PM4",
            0,
            handles.LOGICP1,
            0x28,
            1,
            read_8,
            writePM,
            view8,
            &(LOGICP1_reg0_data.PM4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PMC4",
            0,
            handles.LOGICP1,
            0x48,
            1,
            read_8,
            writePMC,
            view8,
            &(LOGICP1_reg0_data.PMC4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_P5",
            0,
            handles.LOGICP1,
            0xa,
            1,
            read_8,
            writeP,
            view8,
            &(LOGICP1_reg0_data.P5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PM5",
            0,
            handles.LOGICP1,
            0x2a,
            1,
            read_8,
            writePM,
            view8,
            &(LOGICP1_reg0_data.PM5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PMC5",
            0,
            handles.LOGICP1,
            0x4a,
            1,
            read_8,
            writePMC,
            view8,
            &(LOGICP1_reg0_data.PMC5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_P6",
            0,
            handles.LOGICP1,
            0xc,
            1,
            read_8,
            writeP,
            view8,
            &(LOGICP1_reg0_data.P6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PM6",
            0,
            handles.LOGICP1,
            0x2c,
            1,
            read_8,
            writePM,
            view8,
            &(LOGICP1_reg0_data.PM6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PMC6",
            0,
            handles.LOGICP1,
            0x4c,
            1,
            read_8,
            writePMC,
            view8,
            &(LOGICP1_reg0_data.PMC6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_P7",
            0,
            handles.LOGICP1,
            0xe,
            1,
            read_8,
            writeP,
            view8,
            &(LOGICP1_reg0_data.P7.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PM7",
            0,
            handles.LOGICP1,
            0x2e,
            1,
            read_8,
            writePM,
            view8,
            &(LOGICP1_reg0_data.PM7.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PMC7",
            0,
            handles.LOGICP1,
            0x4e,
            1,
            read_8,
            writePMC,
            view8,
            &(LOGICP1_reg0_data.PMC7.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_P8",
            0,
            handles.LOGICP1,
            0x10,
            1,
            read_8,
            writeP,
            view8,
            &(LOGICP1_reg0_data.P8.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PM8",
            0,
            handles.LOGICP1,
            0x30,
            1,
            read_8,
            writePM,
            view8,
            &(LOGICP1_reg0_data.PM8.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PMC8",
            0,
            handles.LOGICP1,
            0x50,
            1,
            read_8,
            writePMC,
            view8,
            &(LOGICP1_reg0_data.PMC8.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_P9",
            0,
            handles.LOGICP1,
            0x12,
            1,
            read_8,
            writeP,
            view8,
            &(LOGICP1_reg0_data.P9.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PM9",
            0,
            handles.LOGICP1,
            0x32,
            1,
            read_8,
            writePM,
            view8,
            &(LOGICP1_reg0_data.PM9.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PMC9",
            0,
            handles.LOGICP1,
            0x52,
            1,
            read_8,
            writePMC,
            view8,
            &(LOGICP1_reg0_data.PMC9.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_P10",
            0,
            handles.LOGICP1,
            0x14,
            1,
            read_8,
            writeP,
            view8,
            &(LOGICP1_reg0_data.P10.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PM10",
            0,
            handles.LOGICP1,
            0x34,
            1,
            read_8,
            writePM,
            view8,
            &(LOGICP1_reg0_data.PM10.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PMC10",
            0,
            handles.LOGICP1,
            0x54,
            1,
            read_8,
            writePMC,
            view8,
            &(LOGICP1_reg0_data.PMC10.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_P11",
            0,
            handles.LOGICP1,
            0x16,
            1,
            read_8,
            writeP,
            view8,
            &(LOGICP1_reg0_data.P11.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PM11",
            0,
            handles.LOGICP1,
            0x36,
            1,
            read_8,
            writePM,
            view8,
            &(LOGICP1_reg0_data.PM11.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PMC11",
            0,
            handles.LOGICP1,
            0x56,
            1,
            read_8,
            writePMC,
            view8,
            &(LOGICP1_reg0_data.PMC11.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PFC1",
            0,
            handles.LOGICP1,
            0x62,
            1,
            read_8,
            writePFC,
            view8,
            &(LOGICP1_reg0_data.PFC1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PFC2",
            0,
            handles.LOGICP1,
            0x64,
            1,
            read_8,
            writePFC,
            view8,
            &(LOGICP1_reg0_data.PFC2.value),
            True
        );
    }
    {
        registerHandle reg0PFC4_reg = ppmCreateRegister(
            "reg0_PFC4",
            0,
            handles.LOGICP1,
            0x68,
            1,
            read_8,
            writePFC,
            view8,
            &(LOGICP1_reg0_data.PFC4.value),
            True
        );

        ppmCreateRegisterField(reg0PFC4_reg, "PFC40", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(reg0PFC4_reg, "PFC41", 0, 1, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "reg0_PFC7",
            0,
            handles.LOGICP1,
            0x6e,
            1,
            read_8,
            writePFC,
            view8,
            &(LOGICP1_reg0_data.PFC7.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PFC8",
            0,
            handles.LOGICP1,
            0x70,
            1,
            read_8,
            writePFC,
            view8,
            &(LOGICP1_reg0_data.PFC8.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PFC9",
            0,
            handles.LOGICP1,
            0x72,
            1,
            read_8,
            writePFC,
            view8,
            &(LOGICP1_reg0_data.PFC9.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PFC10",
            0,
            handles.LOGICP1,
            0x74,
            1,
            read_8,
            writePFC,
            view8,
            &(LOGICP1_reg0_data.PFC10.value),
            True
        );
    }

    {
        ppmCreateRegister(
            "reg0_PESC5",
            0,
            handles.LOGICP2,
            0x0,
            1,
            read_8,
            writePESC5,
            view8,
            &(LOGICP2_reg0_data.PESC5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_ESOST5",
            0,
            handles.LOGICP2,
            0x2,
            1,
            read_8,
            writeESOST5,
            view8,
            &(LOGICP2_reg0_data.ESOST5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PESC6",
            0,
            handles.LOGICP2,
            0x4,
            1,
            read_8,
            writePESC6,
            view8,
            &(LOGICP2_reg0_data.PESC6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_ESOST6",
            0,
            handles.LOGICP2,
            0x6,
            1,
            read_8,
            writeESOST6,
            view8,
            &(LOGICP2_reg0_data.ESOST6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PESMK5",
            0,
            handles.LOGICP2,
            0x8,
            1,
            read_8,
            writePESMK5,
            view8,
            &(LOGICP2_reg0_data.PESMK5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_PESMK6",
            0,
            handles.LOGICP2,
            0xa,
            1,
            read_8,
            writePESMK6,
            view8,
            &(LOGICP2_reg0_data.PESMK6.value),
            True
        );
    }

    {
        ppmCreateRegister(
            "reg0_PRCMD",
            0,
            handles.LOGICP3,
            0x0,
            1,
            0,
            writePRCMD,
            view8,
            &(LOGICP3_reg0_data.PRCMD.value),
            True
        );
    }

}

PPM_NET_CB(reset_IRESET) {
    if(value != 0 ) {
        LOGICP2_reg0_data.PESMK6.value = (Uns8)(LOGICP2_reg0_data.PESMK6.value & ~(0xff)) | ((0xff) & (0x00));
        LOGICP2_reg0_data.PESMK5.value = (Uns8)(LOGICP2_reg0_data.PESMK5.value & ~(0xff)) | ((0xff) & (0x00));
        LOGICP2_reg0_data.ESOST6.value = (Uns8)(LOGICP2_reg0_data.ESOST6.value & ~(0xff)) | ((0xff) & (0x00));
        LOGICP2_reg0_data.PESC6.value = (Uns8)(LOGICP2_reg0_data.PESC6.value & ~(0xff)) | ((0xff) & (0x00));
        LOGICP2_reg0_data.ESOST5.value = (Uns8)(LOGICP2_reg0_data.ESOST5.value & ~(0xff)) | ((0xff) & (0x00));
        LOGICP2_reg0_data.PESC5.value = (Uns8)(LOGICP2_reg0_data.PESC5.value & ~(0xff)) | ((0xff) & (0x00));
        LOGICP0_reg0_data.INTERRF.value = (Uns8)(LOGICP0_reg0_data.INTERRF.value & ~(0xff)) | ((0xff) & (0x00));
        LOGICP0_reg0_data.INTSEL.value = (Uns8)(LOGICP0_reg0_data.INTSEL.value & ~(0xff)) | ((0xff) & (0x00));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Renesas V850PHO3 / UPD70F3441 Glue Logic");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "No known limitations");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    reset_IRESET(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}


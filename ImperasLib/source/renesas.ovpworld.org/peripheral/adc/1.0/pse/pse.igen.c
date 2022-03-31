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

ADCP0_reg0_dataT ADCP0_reg0_data;

ADCP0_reg1_dataT ADCP0_reg1_data;

ADCP0_reg2_dataT ADCP0_reg2_data;

ADCP1_reg0_dataT ADCP1_reg0_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "adc", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

static PPM_VIEW_CB(view16) {  *(Uns16*)data = *(Uns16*)user; }

//////////////////////////////// View callbacks ////////////////////////////////

static PPM_VIEW_CB(view_ADCP0_reg1_ADCR0) {
    *(Uns16*)data = ADCP0_reg1_data.ADCR0.value;
}

static PPM_VIEW_CB(view_ADCP0_reg1_ADCR1) {
    *(Uns16*)data = ADCP0_reg1_data.ADCR1.value;
}

static PPM_VIEW_CB(view_ADCP0_reg1_ADCR2) {
    *(Uns16*)data = ADCP0_reg1_data.ADCR2.value;
}

static PPM_VIEW_CB(view_ADCP0_reg1_ADCR3) {
    *(Uns16*)data = ADCP0_reg1_data.ADCR3.value;
}

static PPM_VIEW_CB(view_ADCP0_reg1_ADCR4) {
    *(Uns16*)data = ADCP0_reg1_data.ADCR4.value;
}

static PPM_VIEW_CB(view_ADCP0_reg1_ADCR5) {
    *(Uns16*)data = ADCP0_reg1_data.ADCR5.value;
}

static PPM_VIEW_CB(view_ADCP0_reg1_ADCR6) {
    *(Uns16*)data = ADCP0_reg1_data.ADCR6.value;
}

static PPM_VIEW_CB(view_ADCP0_reg1_ADCR7) {
    *(Uns16*)data = ADCP0_reg1_data.ADCR7.value;
}

static PPM_VIEW_CB(view_ADCP0_reg1_ADCR8) {
    *(Uns16*)data = ADCP0_reg1_data.ADCR8.value;
}

static PPM_VIEW_CB(view_ADCP0_reg1_ADCR9) {
    *(Uns16*)data = ADCP0_reg1_data.ADCR9.value;
}
//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.ADCP0 = ppmCreateSlaveBusPort("ADCP0", 48);

    handles.ADCP1 = ppmCreateSlaveBusPort("ADCP1", 1);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle reg0ADM0_reg = ppmCreateRegister(
            "reg0_ADM0",
            0,
            handles.ADCP0,
            0x0,
            1,
            read_8,
            writeADM0,
            view8,
            &(ADCP0_reg0_data.ADM0.value),
            True
        );

        ppmCreateRegisterField(reg0ADM0_reg, "MS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(reg0ADM0_reg, "BS", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(reg0ADM0_reg, "ADCS", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg0ADM0_reg, "ADCE", 0, 7, 1, 1, 1);
    }
    {
        registerHandle reg0ADM1_reg = ppmCreateRegister(
            "reg0_ADM1",
            0,
            handles.ADCP0,
            0x1,
            1,
            read_8,
            writeADM1,
            view8,
            &(ADCP0_reg0_data.ADM1.value),
            True
        );

        ppmCreateRegisterField(reg0ADM1_reg, "FR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(reg0ADM1_reg, "TRG", 0, 4, 2, 1, 1);
        ppmCreateRegisterField(reg0ADM1_reg, "EGA", 0, 6, 2, 1, 1);
    }
    {
        registerHandle reg0ADM2_reg = ppmCreateRegister(
            "reg0_ADM2",
            0,
            handles.ADCP0,
            0x2,
            1,
            read_8,
            writeADM2,
            view8,
            &(ADCP0_reg0_data.ADM2.value),
            True
        );

        ppmCreateRegisterField(reg0ADM2_reg, "ANI", 0, 0, 4, 1, 1);
    }
    {
        registerHandle reg1ADCR0_reg = ppmCreateRegister(
            "reg1_ADCR0",
            0,
            handles.ADCP0,
            0x10,
            2,
            readADCR,
            0,
            view_ADCP0_reg1_ADCR0,
            (void*)0,
            True
        );

        ppmCreateRegisterField(reg1ADCR0_reg, "AD", 0, 6, 10, 1, 0);
    }
    {
        registerHandle reg1ADCR1_reg = ppmCreateRegister(
            "reg1_ADCR1",
            0,
            handles.ADCP0,
            0x12,
            2,
            readADCR,
            0,
            view_ADCP0_reg1_ADCR1,
            (void*)1,
            True
        );

        ppmCreateRegisterField(reg1ADCR1_reg, "AD", 0, 6, 10, 1, 0);
    }
    {
        registerHandle reg1ADCR2_reg = ppmCreateRegister(
            "reg1_ADCR2",
            0,
            handles.ADCP0,
            0x14,
            2,
            readADCR,
            0,
            view_ADCP0_reg1_ADCR2,
            (void*)2,
            True
        );

        ppmCreateRegisterField(reg1ADCR2_reg, "AD", 0, 6, 10, 1, 0);
    }
    {
        registerHandle reg1ADCR3_reg = ppmCreateRegister(
            "reg1_ADCR3",
            0,
            handles.ADCP0,
            0x16,
            2,
            readADCR,
            0,
            view_ADCP0_reg1_ADCR3,
            (void*)3,
            True
        );

        ppmCreateRegisterField(reg1ADCR3_reg, "AD", 0, 6, 10, 1, 0);
    }
    {
        registerHandle reg1ADCR4_reg = ppmCreateRegister(
            "reg1_ADCR4",
            0,
            handles.ADCP0,
            0x18,
            2,
            readADCR,
            0,
            view_ADCP0_reg1_ADCR4,
            (void*)4,
            True
        );

        ppmCreateRegisterField(reg1ADCR4_reg, "AD", 0, 6, 10, 1, 0);
    }
    {
        registerHandle reg1ADCR5_reg = ppmCreateRegister(
            "reg1_ADCR5",
            0,
            handles.ADCP0,
            0x1a,
            2,
            readADCR,
            0,
            view_ADCP0_reg1_ADCR5,
            (void*)5,
            True
        );

        ppmCreateRegisterField(reg1ADCR5_reg, "AD", 0, 6, 10, 1, 0);
    }
    {
        registerHandle reg1ADCR6_reg = ppmCreateRegister(
            "reg1_ADCR6",
            0,
            handles.ADCP0,
            0x1c,
            2,
            readADCR,
            0,
            view_ADCP0_reg1_ADCR6,
            (void*)6,
            True
        );

        ppmCreateRegisterField(reg1ADCR6_reg, "AD", 0, 6, 10, 1, 0);
    }
    {
        registerHandle reg1ADCR7_reg = ppmCreateRegister(
            "reg1_ADCR7",
            0,
            handles.ADCP0,
            0x1e,
            2,
            readADCR,
            0,
            view_ADCP0_reg1_ADCR7,
            (void*)7,
            True
        );

        ppmCreateRegisterField(reg1ADCR7_reg, "AD", 0, 6, 10, 1, 0);
    }
    {
        registerHandle reg1ADCR8_reg = ppmCreateRegister(
            "reg1_ADCR8",
            0,
            handles.ADCP0,
            0x20,
            2,
            readADCR,
            0,
            view_ADCP0_reg1_ADCR8,
            (void*)8,
            True
        );

        ppmCreateRegisterField(reg1ADCR8_reg, "AD", 0, 6, 10, 1, 0);
    }
    {
        registerHandle reg1ADCR9_reg = ppmCreateRegister(
            "reg1_ADCR9",
            0,
            handles.ADCP0,
            0x22,
            2,
            readADCR,
            0,
            view_ADCP0_reg1_ADCR9,
            (void*)9,
            True
        );

        ppmCreateRegisterField(reg1ADCR9_reg, "AD", 0, 6, 10, 1, 0);
    }
    {
        registerHandle reg2ADDMA_reg = ppmCreateRegister(
            "reg2_ADDMA",
            0,
            handles.ADCP0,
            0x2e,
            2,
            readADDMA,
            0,
            view16,
            &(ADCP0_reg2_data.ADDMA.value),
            True
        );

        ppmCreateRegisterField(reg2ADDMA_reg, "ODF", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(reg2ADDMA_reg, "ADDMA", 0, 6, 10, 1, 0);
    }

    {
        registerHandle reg0ADTRSEL_reg = ppmCreateRegister(
            "reg0_ADTRSEL",
            0,
            handles.ADCP1,
            0x0,
            1,
            read_8,
            writeADTRSEL,
            view8,
            &(ADCP1_reg0_data.ADTRSEL.value),
            True
        );

        ppmCreateRegisterField(reg0ADTRSEL_reg, "TSEL", 0, 0, 4, 1, 1);
    }

}

PPM_NET_CB(reset_IRESET) {
    if(value != 0 ) {
        ADCP1_reg0_data.ADTRSEL.value = (Uns8)(ADCP1_reg0_data.ADTRSEL.value & ~(0xff)) | ((0xff) & (0x00));
        ADCP0_reg2_data.ADDMA.value = (Uns16)(ADCP0_reg2_data.ADDMA.value & ~(0xffff)) | ((0xffff) & (0x00));
        ADCP0_reg1_data.ADCR9.value = (Uns16)(ADCP0_reg1_data.ADCR9.value & ~(0xffff)) | ((0xffff) & (0x00));
        ADCP0_reg1_data.ADCR8.value = (Uns16)(ADCP0_reg1_data.ADCR8.value & ~(0xffff)) | ((0xffff) & (0x00));
        ADCP0_reg1_data.ADCR7.value = (Uns16)(ADCP0_reg1_data.ADCR7.value & ~(0xffff)) | ((0xffff) & (0x00));
        ADCP0_reg1_data.ADCR6.value = (Uns16)(ADCP0_reg1_data.ADCR6.value & ~(0xffff)) | ((0xffff) & (0x00));
        ADCP0_reg1_data.ADCR5.value = (Uns16)(ADCP0_reg1_data.ADCR5.value & ~(0xffff)) | ((0xffff) & (0x00));
        ADCP0_reg1_data.ADCR4.value = (Uns16)(ADCP0_reg1_data.ADCR4.value & ~(0xffff)) | ((0xffff) & (0x00));
        ADCP0_reg1_data.ADCR3.value = (Uns16)(ADCP0_reg1_data.ADCR3.value & ~(0xffff)) | ((0xffff) & (0x00));
        ADCP0_reg1_data.ADCR2.value = (Uns16)(ADCP0_reg1_data.ADCR2.value & ~(0xffff)) | ((0xffff) & (0x00));
        ADCP0_reg1_data.ADCR1.value = (Uns16)(ADCP0_reg1_data.ADCR1.value & ~(0xffff)) | ((0xffff) & (0x00));
        ADCP0_reg1_data.ADCR0.value = (Uns16)(ADCP0_reg1_data.ADCR0.value & ~(0xffff)) | ((0xffff) & (0x00));
        ADCP0_reg0_data.ADM2.value = (Uns8)(ADCP0_reg0_data.ADM2.value & ~(0xff)) | ((0xff) & (0x00));
        ADCP0_reg0_data.ADM1.value = (Uns8)(ADCP0_reg0_data.ADM1.value & ~(0xff)) | ((0xff) & (0x00));
        ADCP0_reg0_data.ADM0.value = (Uns8)(ADCP0_reg0_data.ADM0.value & ~(0xff)) | ((0xff) & (0x00));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Renesas ADC A/D Converter");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Model supports Modes Select, Scan, 1xBuffer, 4xBuffer - no support for external trigger");
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
    destructor();
    return 0;
}


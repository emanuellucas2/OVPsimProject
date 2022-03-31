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

TAAP0_reg0_dataT TAAP0_reg0_data;

TAAP0_reg1_dataT TAAP0_reg1_data;

TAAP0_reg2_dataT TAAP0_reg2_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "taa", "Example");
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

static PPM_READ_CB(read_16) {  return *(Uns16*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.TAAP0 = ppmCreateSlaveBusPort("TAAP0", 16);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle reg0CTL0_reg = ppmCreateRegister(
            "reg0_CTL0",
            0,
            handles.TAAP0,
            0x0,
            1,
            read_8,
            writeCTL0,
            view8,
            &(TAAP0_reg0_data.CTL0.value),
            True
        );

        ppmCreateRegisterField(reg0CTL0_reg, "CKS", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(reg0CTL0_reg, "CE", 0, 7, 1, 1, 1);
    }
    {
        registerHandle reg0CTL1_reg = ppmCreateRegister(
            "reg0_CTL1",
            0,
            handles.TAAP0,
            0x1,
            1,
            read_8,
            writeCTL1,
            view8,
            &(TAAP0_reg0_data.CTL1.value),
            True
        );

        ppmCreateRegisterField(reg0CTL1_reg, "MD", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(reg0CTL1_reg, "EEE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(reg0CTL1_reg, "EST", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg0CTL1_reg, "SYE", 0, 7, 1, 1, 1);
    }
    {
        registerHandle reg0IOC0_reg = ppmCreateRegister(
            "reg0_IOC0",
            0,
            handles.TAAP0,
            0x2,
            1,
            read_8,
            writeIOC0,
            view8,
            &(TAAP0_reg0_data.IOC0.value),
            True
        );

        ppmCreateRegisterField(reg0IOC0_reg, "OE0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(reg0IOC0_reg, "OL0", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(reg0IOC0_reg, "OE1", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(reg0IOC0_reg, "OL1", 0, 3, 1, 1, 1);
    }
    {
        registerHandle reg0IOC1_reg = ppmCreateRegister(
            "reg0_IOC1",
            0,
            handles.TAAP0,
            0x3,
            1,
            read_8,
            writeIOC1,
            view8,
            &(TAAP0_reg0_data.IOC1.value),
            True
        );

        ppmCreateRegisterField(reg0IOC1_reg, "IS", 0, 0, 4, 1, 1);
    }
    {
        registerHandle reg0IOC2_reg = ppmCreateRegister(
            "reg0_IOC2",
            0,
            handles.TAAP0,
            0x4,
            1,
            read_8,
            writeIOC2,
            view8,
            &(TAAP0_reg0_data.IOC2.value),
            True
        );

        ppmCreateRegisterField(reg0IOC2_reg, "ETS", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(reg0IOC2_reg, "EES", 0, 2, 2, 1, 1);
    }
    {
        registerHandle reg0OPT0_reg = ppmCreateRegister(
            "reg0_OPT0",
            0,
            handles.TAAP0,
            0x5,
            1,
            read_8,
            writeOPT0,
            view8,
            &(TAAP0_reg0_data.OPT0.value),
            True
        );

        ppmCreateRegisterField(reg0OPT0_reg, "OVF", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(reg0OPT0_reg, "CCS", 0, 4, 2, 1, 1);
    }
    {
        ppmCreateRegister(
            "reg1_CCR0",
            0,
            handles.TAAP0,
            0x6,
            2,
            read_16,
            writeCCR0,
            view16,
            &(TAAP0_reg1_data.CCR0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg1_CCR1",
            0,
            handles.TAAP0,
            0x8,
            2,
            read_16,
            writeCCR1,
            view16,
            &(TAAP0_reg1_data.CCR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg1_CNT",
            0,
            handles.TAAP0,
            0xa,
            2,
            readCNT,
            0,
            view16,
            &(TAAP0_reg1_data.CNT.value),
            True
        );
    }
    {
        registerHandle reg2IOC4_reg = ppmCreateRegister(
            "reg2_IOC4",
            0,
            handles.TAAP0,
            0xc,
            1,
            read_8,
            writeIOC4,
            view8,
            &(TAAP0_reg2_data.IOC4.value),
            True
        );

        ppmCreateRegisterField(reg2IOC4_reg, "OR0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(reg2IOC4_reg, "OS0", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(reg2IOC4_reg, "OR1", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(reg2IOC4_reg, "OS1", 0, 3, 1, 1, 1);
    }
    {
        registerHandle reg2SVC_reg = ppmCreateRegister(
            "reg2_SVC",
            0,
            handles.TAAP0,
            0xe,
            1,
            read_8,
            writeSVC,
            view8,
            &(TAAP0_reg2_data.SVC.value),
            True
        );

        ppmCreateRegisterField(reg2SVC_reg, "CSR0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(reg2SVC_reg, "CSD0", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(reg2SVC_reg, "CSE0", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(reg2SVC_reg, "ENC0", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(reg2SVC_reg, "CSR1", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(reg2SVC_reg, "CSD1", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(reg2SVC_reg, "CSE1", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg2SVC_reg, "ENC1", 0, 7, 1, 1, 1);
    }

}

PPM_NET_CB(reset_IRESET) {
    if(value != 0 ) {
        TAAP0_reg2_data.SVC.value = (Uns8)(TAAP0_reg2_data.SVC.value & ~(0xff)) | ((0xff) & (0x00));
        TAAP0_reg2_data.IOC4.value = (Uns8)(TAAP0_reg2_data.IOC4.value & ~(0xff)) | ((0xff) & (0x00));
        TAAP0_reg1_data.CNT.value = (Uns16)(TAAP0_reg1_data.CNT.value & ~(0xffff)) | ((0xffff) & (0x0000));
        TAAP0_reg1_data.CCR1.value = (Uns16)(TAAP0_reg1_data.CCR1.value & ~(0xffff)) | ((0xffff) & (0x0000));
        TAAP0_reg1_data.CCR0.value = (Uns16)(TAAP0_reg1_data.CCR0.value & ~(0xffff)) | ((0xffff) & (0x0000));
        TAAP0_reg0_data.OPT0.value = (Uns8)(TAAP0_reg0_data.OPT0.value & ~(0xff)) | ((0xff) & (0x00));
        TAAP0_reg0_data.IOC2.value = (Uns8)(TAAP0_reg0_data.IOC2.value & ~(0xff)) | ((0xff) & (0x00));
        TAAP0_reg0_data.IOC1.value = (Uns8)(TAAP0_reg0_data.IOC1.value & ~(0xff)) | ((0xff) & (0x00));
        TAAP0_reg0_data.IOC0.value = (Uns8)(TAAP0_reg0_data.IOC0.value & ~(0xff)) | ((0xff) & (0x00));
        TAAP0_reg0_data.CTL1.value = (Uns8)(TAAP0_reg0_data.CTL1.value & ~(0xff)) | ((0xff) & (0x00));
        TAAP0_reg0_data.CTL0.value = (Uns8)(TAAP0_reg0_data.CTL0.value & ~(0xff)) | ((0xff) & (0x00));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Renesas TAA Timer/Event Counter AA");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Status of Modes\n- Interval Timer Mode                  - Supported\n- External Event Count Mode            - Unsupported\n- External Trigger Pulse Output Mode   - Unsupported\n- One-Shot Pulse Mode                  - Unsupported\n- PWM Mode                             - Unsupported\n- Free-Running Mode                    - Supported\n- Pulse Width Measurement Mode         - Unsupported\n");
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


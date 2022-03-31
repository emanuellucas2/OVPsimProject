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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "iMX6_GPT", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

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
        registerHandle abGPT_CR_reg = ppmCreateRegister(
            "ab_GPT_CR",
            "Description\nGPT Control Register\nForce Output Compare Channel 3\nForce Output Compare Channel 2\nForce Output Compare Channel 1\nOutput Compare Channel 3 operating mode\nOutput Compare Channel 2 operating mode\nOutput Compare Channel 1 operating mode\nInput Capture Channel 2 operating mode\nInput Capture Channel 1 operating mode\nSoftware reset.\nEnable 24 MHz clock input from crystal\nFree-Run or Restart mode.\nClock Source select\nGPT Stop Mode enable\nGPT Doze Mode Enable\nGPT Wait Mode enable.\nGPT debug mode enable\nGPT Enable mode\nGPT Enable\n",
            handles.bport1,
            0x0,
            4,
            read_32,
            WriteGPT_CR,
            view32,
            &(bport1_ab_data.GPT_CR.value),
            True
        );

        ppmCreateRegisterField(abGPT_CR_reg, "FO3", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abGPT_CR_reg, "FO2", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abGPT_CR_reg, "FO1", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abGPT_CR_reg, "OM3", 0, 26, 3, 1, 1);
        ppmCreateRegisterField(abGPT_CR_reg, "OM2", 0, 23, 3, 1, 1);
        ppmCreateRegisterField(abGPT_CR_reg, "OM1", 0, 20, 3, 1, 1);
        ppmCreateRegisterField(abGPT_CR_reg, "IM2", 0, 18, 2, 1, 1);
        ppmCreateRegisterField(abGPT_CR_reg, "IM1", 0, 16, 2, 1, 1);
        ppmCreateRegisterField(abGPT_CR_reg, "SWR", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abGPT_CR_reg, "EN_24M", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abGPT_CR_reg, "FRR", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abGPT_CR_reg, "CLKSRC", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(abGPT_CR_reg, "STOPEN", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abGPT_CR_reg, "DOZEEN", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abGPT_CR_reg, "QAITEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abGPT_CR_reg, "DBGEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abGPT_CR_reg, "ENMOD", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abGPT_CR_reg, "EN", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abGPT_PR_reg = ppmCreateRegister(
            "ab_GPT_PR",
            "Description\nGPT Prescaler Register\n24M crystal clock Prescaler bits\nCLKSRC Prescaler bits\n",
            handles.bport1,
            0x4,
            4,
            read_32,
            WriteGPT_PR,
            view32,
            &(bport1_ab_data.GPT_PR.value),
            True
        );

        ppmCreateRegisterField(abGPT_PR_reg, "PRESCALER24M", 0, 12, 4, 1, 1);
        ppmCreateRegisterField(abGPT_PR_reg, "PRESCALER", 0, 0, 12, 1, 1);
    }
    {
        registerHandle abGPT_SR_reg = ppmCreateRegister(
            "ab_GPT_SR",
            "Description\nGPT Status Register\nRollover Flag.\nIF2 Input capture 2 Flag\nIF1 Input capture 1 Flag\nOF3 Output Compare 3 Flag\nOF2 Output Compare 2 Flag\nOF1 Output Compare 1 Flag\n",
            handles.bport1,
            0x8,
            4,
            read_32,
            WriteGPT_SR,
            view32,
            &(bport1_ab_data.GPT_SR.value),
            True
        );

        ppmCreateRegisterField(abGPT_SR_reg, "ROV", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abGPT_SR_reg, "IF2", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abGPT_SR_reg, "IF1", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abGPT_SR_reg, "OF3", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abGPT_SR_reg, "OF2", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abGPT_SR_reg, "OF1", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abGPT_IR_reg = ppmCreateRegister(
            "ab_GPT_IR",
            "Description\nGPT Interrupt Register\nRollover Interrupt Enable\nInput capture 2 Interrupt Enable\nInput capture 1 Interrupt Enable\nOutput Compare 3 Interrupt Enable\nOutput Compare 2 Interrupt Enable\nOutput Compare 1 Interrupt Enable\n",
            handles.bport1,
            0xc,
            4,
            read_32,
            WriteGPT_IR,
            view32,
            &(bport1_ab_data.GPT_IR.value),
            True
        );

        ppmCreateRegisterField(abGPT_IR_reg, "ROVIE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abGPT_IR_reg, "IF2IE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abGPT_IR_reg, "IF1IE", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abGPT_IR_reg, "OF3IE", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abGPT_IR_reg, "OF2IE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abGPT_IR_reg, "OF1IE", 0, 0, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_GPT_OCR1",
            "GPT Output Compare Register 1",
            handles.bport1,
            0x10,
            4,
            read_32,
            WriteGPT_OCR1,
            view32,
            &(bport1_ab_data.GPT_OCR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GPT_OCR2",
            "GPT Output Compare Register 2",
            handles.bport1,
            0x14,
            4,
            read_32,
            WriteGPT_OCR2,
            view32,
            &(bport1_ab_data.GPT_OCR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GPT_OCR3",
            "GPT Output Compare Register 3",
            handles.bport1,
            0x18,
            4,
            read_32,
            WriteGPT_OCR3,
            view32,
            &(bport1_ab_data.GPT_OCR3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GPT_ICR1",
            "GPT Input Capture Register 1",
            handles.bport1,
            0x1c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.GPT_ICR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GPT_ICR2",
            "GPT Input Capture Register 2",
            handles.bport1,
            0x20,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.GPT_ICR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GPT_CNT",
            "GPT Counter Register",
            handles.bport1,
            0x24,
            4,
            ReadGPT_CNT,
            0,
            view32,
            &(bport1_ab_data.GPT_CNT.value),
            True
        );
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.GPT_CNT.value = (Uns32)(bport1_ab_data.GPT_CNT.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPT_ICR2.value = (Uns32)(bport1_ab_data.GPT_ICR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPT_ICR1.value = (Uns32)(bport1_ab_data.GPT_ICR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPT_OCR3.value = (Uns32)(bport1_ab_data.GPT_OCR3.value & ~(0xffffffff)) | ((0xffffffff) & (0xffffffff));
        bport1_ab_data.GPT_OCR2.value = (Uns32)(bport1_ab_data.GPT_OCR2.value & ~(0xffffffff)) | ((0xffffffff) & (0xffffffff));
        bport1_ab_data.GPT_OCR1.value = (Uns32)(bport1_ab_data.GPT_OCR1.value & ~(0xffffffff)) | ((0xffffffff) & (0xffffffff));
        bport1_ab_data.GPT_IR.value = (Uns32)(bport1_ab_data.GPT_IR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPT_SR.value = (Uns32)(bport1_ab_data.GPT_SR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPT_PR.value = (Uns32)(bport1_ab_data.GPT_PR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPT_CR.value = (Uns32)(bport1_ab_data.GPT_CR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "NXP i.MX6 GPT General Purpose Timer");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Resolution of this timer is limited to the simulation time slice (aka quantum) size");
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


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

bp1_REG_dataT bp1_REG_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "WatchdogTimer", "Example");
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
    handles.bp1 = ppmCreateSlaveBusPort("bp1", 16384);
    if (!handles.bp1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bp1'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle REGWD_OMR_reg = ppmCreateRegister(
            "REG_WD_OMR",
            0,
            handles.bp1,
            0x0,
            4,
            read_32,
            WD_OMR_wcb,
            view32,
            &(bp1_REG_data.WD_OMR.value),
            True
        );

        ppmCreateRegisterField(REGWD_OMR_reg, "OKEY", 0, 4, 12, 1, 1);
        ppmCreateRegisterField(REGWD_OMR_reg, "EXTEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(REGWD_OMR_reg, "IRQEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(REGWD_OMR_reg, "RSTEN", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(REGWD_OMR_reg, "WDEN", 0, 0, 1, 1, 1);
    }
    {
        registerHandle REGWD_CMR_reg = ppmCreateRegister(
            "REG_WD_CMR",
            0,
            handles.bp1,
            0x4,
            4,
            read_32,
            WD_CMR_wcb,
            view32,
            &(bp1_REG_data.WD_CMR.value),
            True
        );

        ppmCreateRegisterField(REGWD_CMR_reg, "CKEY", 0, 7, 9, 1, 1);
        ppmCreateRegisterField(REGWD_CMR_reg, "HPCV", 0, 2, 4, 1, 1);
        ppmCreateRegisterField(REGWD_CMR_reg, "WDCLKS", 0, 0, 2, 1, 1);
    }
    {
        registerHandle REGWD_CR_reg = ppmCreateRegister(
            "REG_WD_CR",
            0,
            handles.bp1,
            0x8,
            4,
            0,
            WD_CR_wcb,
            view32,
            &(bp1_REG_data.WD_CR.value),
            True
        );

        ppmCreateRegisterField(REGWD_CR_reg, "RSTKEY", 0, 0, 16, 0, 1);
    }
    {
        registerHandle REGWD_SR_reg = ppmCreateRegister(
            "REG_WD_SR",
            0,
            handles.bp1,
            0xc,
            4,
            read_32,
            0,
            view32,
            &(bp1_REG_data.WD_SR.value),
            True
        );

        ppmCreateRegisterField(REGWD_SR_reg, "WDOVF", 0, 0, 1, 1, 0);
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bp1_REG_data.WD_SR.value = (Uns32)(bp1_REG_data.WD_SR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.WD_CR.value = (Uns32)(bp1_REG_data.WD_CR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.WD_CMR.value = (Uns32)(bp1_REG_data.WD_CMR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.WD_OMR.value = (Uns32)(bp1_REG_data.WD_OMR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "WD: Watchdog\nThe Watchdog is built around a 16-bit counter and is used to prevent system lock-up if the software\nbecomes trapped in a deadlock. It can generate an internal reset or interrupt, or assert an\nactive level on the dedicated pin NWDOVF. All programming registers are password-protected to prevent unintentional programming.\nfor more information visit http://www.atmel.com/products/at91");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model is sufficient to boot Linux");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Rev. 1354D ARM08/02");
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
    periphConstructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}


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

bport1_timer1_dataT bport1_timer1_data;

bport1_timers_dataT bport1_timers_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "dw-apb-timer", "Example");
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

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "timer1_loadcount",
            0,
            handles.bport1,
            0x0,
            4,
            read_32,
            Writeloadcount,
            view32,
            &(bport1_timer1_data.loadcount.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "timer1_currentval",
            0,
            handles.bport1,
            0x4,
            4,
            Readcurrentval,
            0,
            view32,
            &(bport1_timer1_data.currentval.value),
            True
        );
    }
    {
        registerHandle timer1controlreg_reg = ppmCreateRegister(
            "timer1_controlreg",
            0,
            handles.bport1,
            0x8,
            4,
            read_32,
            Writecontrolreg,
            view32,
            &(bport1_timer1_data.controlreg.value),
            True
        );

        ppmCreateRegisterField(timer1controlreg_reg, "enable", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(timer1controlreg_reg, "mode", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(timer1controlreg_reg, "interrupt_mask", 0, 2, 1, 1, 1);
    }
    {
        registerHandle timer1eoi_reg = ppmCreateRegister(
            "timer1_eoi",
            0,
            handles.bport1,
            0xc,
            4,
            Readeoi,
            0,
            view32,
            &(bport1_timer1_data.eoi.value),
            True
        );

        ppmCreateRegisterField(timer1eoi_reg, "eoi", 0, 0, 1, 1, 0);
    }
    {
        registerHandle timer1intstat_reg = ppmCreateRegister(
            "timer1_intstat",
            0,
            handles.bport1,
            0x10,
            4,
            Readintstat,
            0,
            view32,
            &(bport1_timer1_data.intstat.value),
            True
        );

        ppmCreateRegisterField(timer1intstat_reg, "intstat", 0, 0, 1, 1, 0);
    }
    {
        registerHandle timersintstat_reg = ppmCreateRegister(
            "timers_intstat",
            0,
            handles.bport1,
            0xa0,
            4,
            Readintstat,
            0,
            view32,
            &(bport1_timers_data.intstat.value),
            True
        );

        ppmCreateRegisterField(timersintstat_reg, "intstat", 0, 0, 1, 1, 0);
    }
    {
        registerHandle timerseoi_reg = ppmCreateRegister(
            "timers_eoi",
            0,
            handles.bport1,
            0xa4,
            4,
            Readeoi,
            0,
            view32,
            &(bport1_timers_data.eoi.value),
            True
        );

        ppmCreateRegisterField(timerseoi_reg, "eoi", 0, 0, 1, 1, 0);
    }
    {
        registerHandle timersrawintstat_reg = ppmCreateRegister(
            "timers_rawintstat",
            0,
            handles.bport1,
            0xa8,
            4,
            Readrawintstat,
            0,
            view32,
            &(bport1_timers_data.rawintstat.value),
            True
        );

        ppmCreateRegisterField(timersrawintstat_reg, "intstat", 0, 0, 1, 1, 0);
    }
    {
        ppmCreateRegister(
            "timers_compversion",
            0,
            handles.bport1,
            0xac,
            4,
            read_32,
            0,
            view32,
            &(bport1_timers_data.compversion.value),
            True
        );
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_timers_data.compversion.value = (Uns32)(bport1_timers_data.compversion.value & ~(0xffffffff)) | ((0xffffffff) & (0x3230352a));
        bport1_timer1_data.intstat.value = (Uns32)(bport1_timer1_data.intstat.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_timer1_data.eoi.value = (Uns32)(bport1_timer1_data.eoi.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_timer1_data.controlreg.value = (Uns32)(bport1_timer1_data.controlreg.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_timer1_data.currentval.value = (Uns32)(bport1_timer1_data.currentval.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_timer1_data.loadcount.value = (Uns32)(bport1_timer1_data.loadcount.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of dw-apb-timer for CycloneV platform.");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "Only functionality required for Altera Cyclone-V is implemented: single timer, 32 bits, little endian only");
        ppmDocAddText(doc_12_node, "Resolution of this timer is limited to the simulation time slice (aka quantum) size");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "Cyclone V Device Handbook Volume 3: Hard Processor System Technical Reference Manual cv_5v4 2013.12.30");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_32_node, "Open Source Apache 2.0");
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


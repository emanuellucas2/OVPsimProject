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

sp_ab_dataT sp_ab_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "axi-timer", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

//////////////////////////////// View callbacks ////////////////////////////////

static PPM_VIEW_CB(view_sp_ab_TCSR0) {
    *(Uns32*)data = sp_ab_data.TCSR0.value;
}

static PPM_VIEW_CB(view_sp_ab_TLR0) {
    *(Uns32*)data = sp_ab_data.TLR0.value;
}

static PPM_VIEW_CB(view_sp_ab_TCR0) {
    *(Uns32*)data = sp_ab_data.TCR0.value;
}

static PPM_VIEW_CB(view_sp_ab_TCSR1) {
    *(Uns32*)data = sp_ab_data.TCSR1.value;
}

static PPM_VIEW_CB(view_sp_ab_TLR1) {
    *(Uns32*)data = sp_ab_data.TLR1.value;
}

static PPM_VIEW_CB(view_sp_ab_TCR1) {
    *(Uns32*)data = sp_ab_data.TCR1.value;
}
//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.sp = ppmCreateSlaveBusPort("sp", 32);
    if (!handles.sp) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'sp'");
    }

    ppmInstallReadCallback(regNoDefinitionRead, (void*)0 , handles.sp + 0xc, 0x4);
    ppmInstallWriteCallback(regNoDefinitionWrite, (void*)0 , handles.sp + 0xc, 0x4);
    ppmInstallReadCallback(regNoDefinitionRead, (void*)0 , handles.sp + 0x1c, 0x4);
    ppmInstallWriteCallback(regNoDefinitionWrite, (void*)0 , handles.sp + 0x1c, 0x4);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abTCSR0_reg = ppmCreateRegister(
            "ab_TCSR0",
            0,
            handles.sp,
            0x0,
            4,
            ReadTCSR0,
            WriteTCSR0,
            view_sp_ab_TCSR0,
            (void*)0x00,
            True
        );

        ppmCreateRegisterField(abTCSR0_reg, "MDT0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abTCSR0_reg, "UDT0", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abTCSR0_reg, "GENT0", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abTCSR0_reg, "CAPT0", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abTCSR0_reg, "ARHT0", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abTCSR0_reg, "LOAD0", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abTCSR0_reg, "ENIT0", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abTCSR0_reg, "ENT0", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abTCSR0_reg, "T0INT", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abTCSR0_reg, "PWMA0", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abTCSR0_reg, "ENALL0", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abTCSR0_reg, "CASC0", 0, 11, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_TLR0",
            0,
            handles.sp,
            0x4,
            4,
            ReadTLR0,
            WriteTLR0,
            view_sp_ab_TLR0,
            (void*)0x04,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCR0",
            0,
            handles.sp,
            0x8,
            4,
            ReadTCR0,
            0,
            view_sp_ab_TCR0,
            (void*)0x08,
            True
        );
    }
    {
        registerHandle abTCSR1_reg = ppmCreateRegister(
            "ab_TCSR1",
            0,
            handles.sp,
            0x10,
            4,
            ReadTCSR1,
            WriteTCSR1,
            view_sp_ab_TCSR1,
            (void*)0x10,
            True
        );

        ppmCreateRegisterField(abTCSR1_reg, "MDT1", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abTCSR1_reg, "UDT1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abTCSR1_reg, "GENT1", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abTCSR1_reg, "CAPT1", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abTCSR1_reg, "ARHT1", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abTCSR1_reg, "LOAD1", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abTCSR1_reg, "ENIT1", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abTCSR1_reg, "ENT1", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abTCSR1_reg, "T1INT", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abTCSR1_reg, "PWMA1", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abTCSR1_reg, "ENALL1", 0, 10, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_TLR1",
            0,
            handles.sp,
            0x14,
            4,
            ReadTLR1,
            WriteTLR1,
            view_sp_ab_TLR1,
            (void*)0x14,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCR1",
            0,
            handles.sp,
            0x18,
            4,
            ReadTCR1,
            0,
            view_sp_ab_TCR1,
            (void*)0x18,
            True
        );
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        sp_ab_data.TCR1.value = (Uns32)(sp_ab_data.TCR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        sp_ab_data.TLR1.value = (Uns32)(sp_ab_data.TLR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        sp_ab_data.TCSR1.value = (Uns32)(sp_ab_data.TCSR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        sp_ab_data.TCR0.value = (Uns32)(sp_ab_data.TCR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        sp_ab_data.TLR0.value = (Uns32)(sp_ab_data.TLR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        sp_ab_data.TCSR0.value = (Uns32)(sp_ab_data.TCSR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Xilinx AXI Timer");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Resolution of this timer is limited to the simulation time slice (aka quantum) size");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "pg079-axi-timer, Vivado Design Suite, October t, 2016");
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


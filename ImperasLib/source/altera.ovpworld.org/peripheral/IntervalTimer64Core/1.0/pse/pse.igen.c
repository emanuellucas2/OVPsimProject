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

sp1_reg0_dataT sp1_reg0_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "IntervalTimer64Core", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view16) {  *(Uns16*)data = *(Uns16*)user; }

//////////////////////////////// View callbacks ////////////////////////////////

static PPM_VIEW_CB(view_sp1_reg0_period_0) {
    *(Uns16*)data = sp1_reg0_data.period_0.value;
}

static PPM_VIEW_CB(view_sp1_reg0_period_1) {
    *(Uns16*)data = sp1_reg0_data.period_1.value;
}

static PPM_VIEW_CB(view_sp1_reg0_period_2) {
    *(Uns16*)data = sp1_reg0_data.period_2.value;
}

static PPM_VIEW_CB(view_sp1_reg0_period_3) {
    *(Uns16*)data = sp1_reg0_data.period_3.value;
}

static PPM_VIEW_CB(view_sp1_reg0_snap_0) {
    *(Uns16*)data = sp1_reg0_data.snap_0.value;
}

static PPM_VIEW_CB(view_sp1_reg0_snap_1) {
    *(Uns16*)data = sp1_reg0_data.snap_1.value;
}

static PPM_VIEW_CB(view_sp1_reg0_snap_2) {
    *(Uns16*)data = sp1_reg0_data.snap_2.value;
}

static PPM_VIEW_CB(view_sp1_reg0_snap_3) {
    *(Uns16*)data = sp1_reg0_data.snap_3.value;
}
//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.sp1 = ppmCreateSlaveBusPort("sp1", 40);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle reg0status_reg = ppmCreateRegister(
            "reg0_status",
            0,
            handles.sp1,
            0x0,
            2,
            read_status,
            write_status,
            view16,
            &(sp1_reg0_data.status.value),
            True
        );

        ppmCreateRegisterField(reg0status_reg, "TO", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(reg0status_reg, "RUN", 0, 1, 1, 1, 1);
    }
    {
        registerHandle reg0control_reg = ppmCreateRegister(
            "reg0_control",
            0,
            handles.sp1,
            0x4,
            2,
            read_control,
            write_control,
            view16,
            &(sp1_reg0_data.control.value),
            True
        );

        ppmCreateRegisterField(reg0control_reg, "ITO", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(reg0control_reg, "CONT", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(reg0control_reg, "START", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(reg0control_reg, "STOP", 0, 3, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "reg0_period_0",
            0,
            handles.sp1,
            0x8,
            2,
            read_period,
            write_period,
            view_sp1_reg0_period_0,
            (void*)0,
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_period_1",
            0,
            handles.sp1,
            0xc,
            2,
            read_period,
            write_period,
            view_sp1_reg0_period_1,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_period_2",
            0,
            handles.sp1,
            0x10,
            2,
            read_period,
            write_period,
            view_sp1_reg0_period_2,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_period_3",
            0,
            handles.sp1,
            0x14,
            2,
            read_period,
            write_period,
            view_sp1_reg0_period_3,
            (void*)3,
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_snap_0",
            0,
            handles.sp1,
            0x18,
            2,
            read_snap,
            write_snap,
            view_sp1_reg0_snap_0,
            (void*)0,
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_snap_1",
            0,
            handles.sp1,
            0x1c,
            2,
            read_snap,
            write_snap,
            view_sp1_reg0_snap_1,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_snap_2",
            0,
            handles.sp1,
            0x20,
            2,
            read_snap,
            write_snap,
            view_sp1_reg0_snap_2,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_snap_3",
            0,
            handles.sp1,
            0x24,
            2,
            read_snap,
            write_snap,
            view_sp1_reg0_snap_3,
            (void*)3,
            True
        );
    }

}

PPM_NET_CB(reset_IRESET) {
    if(value != 0 ) {
        sp1_reg0_data.snap_3.value = (Uns16)(sp1_reg0_data.snap_3.value & ~(0xffff)) | ((0xffff) & (0x0000));
        sp1_reg0_data.snap_2.value = (Uns16)(sp1_reg0_data.snap_2.value & ~(0xffff)) | ((0xffff) & (0x0000));
        sp1_reg0_data.snap_1.value = (Uns16)(sp1_reg0_data.snap_1.value & ~(0xffff)) | ((0xffff) & (0x0000));
        sp1_reg0_data.snap_0.value = (Uns16)(sp1_reg0_data.snap_0.value & ~(0xffff)) | ((0xffff) & (0x0000));
        sp1_reg0_data.period_3.value = (Uns16)(sp1_reg0_data.period_3.value & ~(0xffff)) | ((0xffff) & (0x0000));
        sp1_reg0_data.period_2.value = (Uns16)(sp1_reg0_data.period_2.value & ~(0xffff)) | ((0xffff) & (0x0000));
        sp1_reg0_data.period_1.value = (Uns16)(sp1_reg0_data.period_1.value & ~(0xffff)) | ((0xffff) & (0x0000));
        sp1_reg0_data.period_0.value = (Uns16)(sp1_reg0_data.period_0.value & ~(0xffff)) | ((0xffff) & (0x0000));
        sp1_reg0_data.control.value = (Uns16)(sp1_reg0_data.control.value & ~(0xffff)) | ((0xffff) & (0x0000));
        sp1_reg0_data.status.value = (Uns16)(sp1_reg0_data.status.value & ~(0xffff)) | ((0xffff) & (0x0000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Altera Avalon Interval Timer32 Core");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "No Support for pin level transitions");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Altera Interval Timer Core");
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


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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "PerformanceCounterCore", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

//////////////////////////////// View callbacks ////////////////////////////////

static PPM_VIEW_CB(view_sp1_reg0_t0lo) {
    *(Uns32*)data = sp1_reg0_data.t0lo.value;
}

static PPM_VIEW_CB(view_sp1_reg0_t0hi) {
    *(Uns32*)data = sp1_reg0_data.t0hi.value;
}

static PPM_VIEW_CB(view_sp1_reg0_t0ev) {
    *(Uns32*)data = sp1_reg0_data.t0ev.value;
}

static PPM_VIEW_CB(view_sp1_reg0_t1lo) {
    *(Uns32*)data = sp1_reg0_data.t1lo.value;
}

static PPM_VIEW_CB(view_sp1_reg0_t1hi) {
    *(Uns32*)data = sp1_reg0_data.t1hi.value;
}

static PPM_VIEW_CB(view_sp1_reg0_t1ev) {
    *(Uns32*)data = sp1_reg0_data.t1ev.value;
}

static PPM_VIEW_CB(view_sp1_reg0_t2lo) {
    *(Uns32*)data = sp1_reg0_data.t2lo.value;
}

static PPM_VIEW_CB(view_sp1_reg0_t2hi) {
    *(Uns32*)data = sp1_reg0_data.t2hi.value;
}

static PPM_VIEW_CB(view_sp1_reg0_t2ev) {
    *(Uns32*)data = sp1_reg0_data.t2ev.value;
}

static PPM_VIEW_CB(view_sp1_reg0_t3lo) {
    *(Uns32*)data = sp1_reg0_data.t3lo.value;
}

static PPM_VIEW_CB(view_sp1_reg0_t3hi) {
    *(Uns32*)data = sp1_reg0_data.t3hi.value;
}

static PPM_VIEW_CB(view_sp1_reg0_t3ev) {
    *(Uns32*)data = sp1_reg0_data.t3ev.value;
}

static PPM_VIEW_CB(view_sp1_reg0_t4lo) {
    *(Uns32*)data = sp1_reg0_data.t4lo.value;
}

static PPM_VIEW_CB(view_sp1_reg0_t4hi) {
    *(Uns32*)data = sp1_reg0_data.t4hi.value;
}

static PPM_VIEW_CB(view_sp1_reg0_t4ev) {
    *(Uns32*)data = sp1_reg0_data.t4ev.value;
}

static PPM_VIEW_CB(view_sp1_reg0_t5lo) {
    *(Uns32*)data = sp1_reg0_data.t5lo.value;
}

static PPM_VIEW_CB(view_sp1_reg0_t5hi) {
    *(Uns32*)data = sp1_reg0_data.t5hi.value;
}

static PPM_VIEW_CB(view_sp1_reg0_t5ev) {
    *(Uns32*)data = sp1_reg0_data.t5ev.value;
}
//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.sp1 = ppmCreateSlaveBusPort("sp1", 128);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "reg0_t0lo",
            0,
            handles.sp1,
            0x0,
            4,
            read_lo,
            write_lo,
            view_sp1_reg0_t0lo,
            (void*)0,
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_t0hi",
            0,
            handles.sp1,
            0x4,
            4,
            read_hi,
            write_hi,
            view_sp1_reg0_t0hi,
            (void*)0,
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_t0ev",
            0,
            handles.sp1,
            0x8,
            4,
            read_ev,
            write_ev,
            view_sp1_reg0_t0ev,
            (void*)0,
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_t1lo",
            0,
            handles.sp1,
            0xc,
            4,
            read_lo,
            write_lo,
            view_sp1_reg0_t1lo,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_t1hi",
            0,
            handles.sp1,
            0x10,
            4,
            read_hi,
            write_hi,
            view_sp1_reg0_t1hi,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_t1ev",
            0,
            handles.sp1,
            0x14,
            4,
            read_ev,
            write_ev,
            view_sp1_reg0_t1ev,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_t2lo",
            0,
            handles.sp1,
            0x18,
            4,
            read_lo,
            write_lo,
            view_sp1_reg0_t2lo,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_t2hi",
            0,
            handles.sp1,
            0x1c,
            4,
            read_hi,
            write_hi,
            view_sp1_reg0_t2hi,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_t2ev",
            0,
            handles.sp1,
            0x20,
            4,
            read_ev,
            write_ev,
            view_sp1_reg0_t2ev,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_t3lo",
            0,
            handles.sp1,
            0x24,
            4,
            read_lo,
            write_lo,
            view_sp1_reg0_t3lo,
            (void*)3,
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_t3hi",
            0,
            handles.sp1,
            0x28,
            4,
            read_hi,
            write_hi,
            view_sp1_reg0_t3hi,
            (void*)3,
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_t3ev",
            0,
            handles.sp1,
            0x2c,
            4,
            read_ev,
            write_ev,
            view_sp1_reg0_t3ev,
            (void*)3,
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_t4lo",
            0,
            handles.sp1,
            0x30,
            4,
            read_lo,
            write_lo,
            view_sp1_reg0_t4lo,
            (void*)4,
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_t4hi",
            0,
            handles.sp1,
            0x34,
            4,
            read_hi,
            write_hi,
            view_sp1_reg0_t4hi,
            (void*)4,
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_t4ev",
            0,
            handles.sp1,
            0x38,
            4,
            read_ev,
            write_ev,
            view_sp1_reg0_t4ev,
            (void*)4,
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_t5lo",
            0,
            handles.sp1,
            0x3c,
            4,
            read_lo,
            write_lo,
            view_sp1_reg0_t5lo,
            (void*)5,
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_t5hi",
            0,
            handles.sp1,
            0x40,
            4,
            read_hi,
            write_hi,
            view_sp1_reg0_t5hi,
            (void*)5,
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_t5ev",
            0,
            handles.sp1,
            0x44,
            4,
            read_ev,
            write_ev,
            view_sp1_reg0_t5ev,
            (void*)5,
            True
        );
    }

}

PPM_NET_CB(reset_IRESET) {
    if(value != 0 ) {
        sp1_reg0_data.t5ev.value = (Uns32)(sp1_reg0_data.t5ev.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        sp1_reg0_data.t5hi.value = (Uns32)(sp1_reg0_data.t5hi.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        sp1_reg0_data.t5lo.value = (Uns32)(sp1_reg0_data.t5lo.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        sp1_reg0_data.t4ev.value = (Uns32)(sp1_reg0_data.t4ev.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        sp1_reg0_data.t4hi.value = (Uns32)(sp1_reg0_data.t4hi.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        sp1_reg0_data.t4lo.value = (Uns32)(sp1_reg0_data.t4lo.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        sp1_reg0_data.t3ev.value = (Uns32)(sp1_reg0_data.t3ev.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        sp1_reg0_data.t3hi.value = (Uns32)(sp1_reg0_data.t3hi.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        sp1_reg0_data.t3lo.value = (Uns32)(sp1_reg0_data.t3lo.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        sp1_reg0_data.t2ev.value = (Uns32)(sp1_reg0_data.t2ev.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        sp1_reg0_data.t2hi.value = (Uns32)(sp1_reg0_data.t2hi.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        sp1_reg0_data.t2lo.value = (Uns32)(sp1_reg0_data.t2lo.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        sp1_reg0_data.t1ev.value = (Uns32)(sp1_reg0_data.t1ev.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        sp1_reg0_data.t1hi.value = (Uns32)(sp1_reg0_data.t1hi.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        sp1_reg0_data.t1lo.value = (Uns32)(sp1_reg0_data.t1lo.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        sp1_reg0_data.t0ev.value = (Uns32)(sp1_reg0_data.t0ev.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        sp1_reg0_data.t0hi.value = (Uns32)(sp1_reg0_data.t0hi.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        sp1_reg0_data.t0lo.value = (Uns32)(sp1_reg0_data.t0lo.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Altera Avalon Performance Counter Core");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "No Support for pin level transitions");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Embedded Peripherals IP User Guide, UG-01085-11.0 11.0 June 2011");
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


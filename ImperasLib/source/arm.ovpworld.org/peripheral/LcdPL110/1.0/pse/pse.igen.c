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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "LcdPL110", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

//////////////////////////////// View callbacks ////////////////////////////////

static PPM_VIEW_CB(view_bport1_ab_timing0) {
    *(Uns32*)data = bport1_ab_data.timing0.value;
}

static PPM_VIEW_CB(view_bport1_ab_timing1) {
    *(Uns32*)data = bport1_ab_data.timing1.value;
}

static PPM_VIEW_CB(view_bport1_ab_timing2) {
    *(Uns32*)data = bport1_ab_data.timing2.value;
}

static PPM_VIEW_CB(view_bport1_ab_timing3) {
    *(Uns32*)data = bport1_ab_data.timing3.value;
}
//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {


    {
        ppmCreateRegister(
            "ab_timing0",
            "LCD Timing 0",
            handles.bport1,
            0x0,
            4,
            readTiming,
            writeTiming,
            view_bport1_ab_timing0,
            (void*)0,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_timing1",
            "LCD Timing 1",
            handles.bport1,
            0x4,
            4,
            readTiming,
            writeTiming,
            view_bport1_ab_timing1,
            (void*)1,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_timing2",
            "LCD Timing 2",
            handles.bport1,
            0x8,
            4,
            readTiming,
            writeTiming,
            view_bport1_ab_timing2,
            (void*)2,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_timing3",
            "LCD Timing 3",
            handles.bport1,
            0xc,
            4,
            readTiming,
            writeTiming,
            view_bport1_ab_timing3,
            (void*)3,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_upbase",
            "LCD UP Base",
            handles.bport1,
            0x10,
            4,
            read_32,
            writeUP,
            view32,
            &(bport1_ab_data.upbase.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_lpbase",
            "LCD LP Base",
            handles.bport1,
            0x14,
            4,
            read_32,
            writeLP,
            view32,
            &(bport1_ab_data.lpbase.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_imsc",
            "LCD IMSC",
            handles.bport1,
            0x18,
            4,
            readIMSC,
            writeIMSC,
            view32,
            &(bport1_ab_data.imsc.value),
            True
        );
    }
    {
        registerHandle abcontrol_reg = ppmCreateRegister(
            "ab_control",
            "LCD Control",
            handles.bport1,
            0x1c,
            4,
            readControl,
            writeControl,
            view32,
            &(bport1_ab_data.control.value),
            True
        );

        ppmCreateRegisterField(abcontrol_reg, "EN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abcontrol_reg, "BGR", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abcontrol_reg, "BEBO", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abcontrol_reg, "BEPO", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abcontrol_reg, "PWR", 0, 11, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_int_status",
            "LCD RIS",
            handles.bport1,
            0x20,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.int_status.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_int_mis",
            "LCD MIS",
            handles.bport1,
            0x24,
            4,
            readMIS,
            0,
            view32,
            &(bport1_ab_data.int_mis.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_int_clr",
            "LCD ICR",
            handles.bport1,
            0x28,
            4,
            0,
            writeICR,
            view32,
            &(bport1_ab_data.int_clr.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_upbase2",
            "LCD UP current",
            handles.bport1,
            0x2c,
            4,
            readUP,
            0,
            view32,
            &(bport1_ab_data.upbase2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_lpbase2",
            "LCD LP current",
            handles.bport1,
            0x30,
            4,
            readLP,
            0,
            view32,
            &(bport1_ab_data.lpbase2.value),
            True
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_id0",
            0,
            handles.bport1,
            0xfe0,
            4,
            readID,
            0,
            0,
            &(bport1_ab_data.id[0].value),
            (void*)0,
            True,
            1,
            0,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_id1",
            0,
            handles.bport1,
            0xfe4,
            4,
            readID,
            0,
            0,
            &(bport1_ab_data.id[1].value),
            (void*)1,
            True,
            1,
            0,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_id2",
            0,
            handles.bport1,
            0xfe8,
            4,
            readID,
            0,
            0,
            &(bport1_ab_data.id[2].value),
            (void*)2,
            True,
            1,
            0,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_id3",
            0,
            handles.bport1,
            0xfec,
            4,
            readID,
            0,
            0,
            &(bport1_ab_data.id[3].value),
            (void*)3,
            True,
            1,
            0,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_id4",
            0,
            handles.bport1,
            0xff0,
            4,
            readID,
            0,
            0,
            &(bport1_ab_data.id[4].value),
            (void*)4,
            True,
            1,
            0,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_id5",
            0,
            handles.bport1,
            0xff4,
            4,
            readID,
            0,
            0,
            &(bport1_ab_data.id[5].value),
            (void*)5,
            True,
            1,
            0,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_id6",
            0,
            handles.bport1,
            0xff8,
            4,
            readID,
            0,
            0,
            &(bport1_ab_data.id[6].value),
            (void*)6,
            True,
            1,
            0,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_id7",
            0,
            handles.bport1,
            0xffc,
            4,
            readID,
            0,
            0,
            &(bport1_ab_data.id[7].value),
            (void*)7,
            True,
            1,
            0,
            BHM_ENDIAN_LITTLE
        );
    }

}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "ARM PL110 LCD Controller");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "The VGA display refresh is not optimised resulting in the VGA peripheral causing a limit on the maximum performance of a platform it contains to be around 300 MIPS (actual dependent upon refresh rate of LCD).");
        ppmDocAddText(doc_12_node, "The LCD peripheral utilises memory watchpoints to optimise display refresh. This requires the use of ICM memory for the frame buffers, which currently may stop its use in SystemC TLM2 platforms.");
        ppmDocAddText(doc_12_node, "Interrupts are not supported");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "ARM PrimeCell Color LCD Controller (PL111) Technical Reference Manual (ARM DDI 0293)");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_32_node, "Open Source Apache 2.0");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}


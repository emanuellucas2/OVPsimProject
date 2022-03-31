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

bport1_REG_dataT bport1_REG_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "gpio", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

static PPM_WRITE_CB(write_32) { *(Uns32*)user = data; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

    ppmInstallNByteCallbacks(defaultMemRead, defaultMemWrite, 0, handles.bport1, 0x0, 0x1000, True, True, False, BHM_ENDIAN_LITTLE);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "REG_VALUE",
            "Pin Value",
            handles.bport1,
            0x0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_REG_data.VALUE.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_INPUT_EN",
            "Enable Input bits",
            handles.bport1,
            0x4,
            4,
            read_32,
            wrInputEn,
            view32,
            &(bport1_REG_data.INPUT_EN.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_OUTPUT_EN",
            "Enable Output bits",
            handles.bport1,
            0x8,
            4,
            read_32,
            wrOutputEn,
            view32,
            &(bport1_REG_data.OUTPUT_EN.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_PORT",
            "Output Port Value",
            handles.bport1,
            0xc,
            4,
            read_32,
            wrPort,
            view32,
            &(bport1_REG_data.PORT.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_PUE",
            "Internal pull-up enabled",
            handles.bport1,
            0x10,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_REG_data.PUE.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_DS",
            "Pin Drive Strength",
            handles.bport1,
            0x14,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_REG_data.DS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_RISE_IE",
            "Rising edge interupt enable",
            handles.bport1,
            0x18,
            4,
            read_32,
            wrRIE,
            view32,
            &(bport1_REG_data.RISE_IE.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_RISE_IP",
            "Rising interrupt pending",
            handles.bport1,
            0x1c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_REG_data.RISE_IP.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_FALL_IE",
            "Falling edge interupt enable",
            handles.bport1,
            0x20,
            4,
            read_32,
            wrFIE,
            view32,
            &(bport1_REG_data.FALL_IE.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_FALL_IP",
            "Falling interrupt pending",
            handles.bport1,
            0x24,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_REG_data.FALL_IP.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_HIGH_IE",
            "High level edge interupt enable",
            handles.bport1,
            0x28,
            4,
            read_32,
            wrHIE,
            view32,
            &(bport1_REG_data.HIGH_IE.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_HIGH_IP",
            "High level interrupt pending",
            handles.bport1,
            0x2c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_REG_data.HIGH_IP.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_LOW_IE",
            "Low level interupt enable",
            handles.bport1,
            0x30,
            4,
            read_32,
            wrLIE,
            view32,
            &(bport1_REG_data.LOW_IE.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_LOW_IP",
            "Low level interrupt pending",
            handles.bport1,
            0x34,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_REG_data.LOW_IP.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_IOF_EN",
            "H/W I/O Function enable",
            handles.bport1,
            0x38,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_REG_data.IOF_EN.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_IOF_SEL",
            "H/W I/O Function Select",
            handles.bport1,
            0x3c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_REG_data.IOF_SEL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_OUT_XOR",
            "Output XOR (invert)",
            handles.bport1,
            0x40,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_REG_data.OUT_XOR.value),
            True
        );
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_REG_data.OUT_XOR.value = (Uns32)(bport1_REG_data.OUT_XOR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.IOF_SEL.value = (Uns32)(bport1_REG_data.IOF_SEL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.IOF_EN.value = (Uns32)(bport1_REG_data.IOF_EN.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.LOW_IP.value = (Uns32)(bport1_REG_data.LOW_IP.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.LOW_IE.value = (Uns32)(bport1_REG_data.LOW_IE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.HIGH_IP.value = (Uns32)(bport1_REG_data.HIGH_IP.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.HIGH_IE.value = (Uns32)(bport1_REG_data.HIGH_IE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.FALL_IP.value = (Uns32)(bport1_REG_data.FALL_IP.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.FALL_IE.value = (Uns32)(bport1_REG_data.FALL_IE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.RISE_IP.value = (Uns32)(bport1_REG_data.RISE_IP.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.RISE_IE.value = (Uns32)(bport1_REG_data.RISE_IE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.DS.value = (Uns32)(bport1_REG_data.DS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.PUE.value = (Uns32)(bport1_REG_data.PUE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.PORT.value = (Uns32)(bport1_REG_data.PORT.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.OUTPUT_EN.value = (Uns32)(bport1_REG_data.OUTPUT_EN.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.INPUT_EN.value = (Uns32)(bport1_REG_data.INPUT_EN.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.VALUE.value = (Uns32)(bport1_REG_data.VALUE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "SiFive coreip-s51-arty GPIO Registers (gpio)");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model implements only the registers for generation of input or output data values.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "SiFive Freedom E SDK coreip-s51-arty Board Support Package details.");
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


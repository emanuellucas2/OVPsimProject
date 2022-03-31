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

DMACSP_ab8_dataT DMACSP_ab8_data;

DMACSP_ab32ch0_dataT DMACSP_ab32ch0_data;

DMACSP_ab32ch1_dataT DMACSP_ab32ch1_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "SimpleDma", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

static PPM_WRITE_CB(write_32) { *(Uns32*)user = data; }

//////////////////////////////// View callbacks ////////////////////////////////

static PPM_VIEW_CB(view_DMACSP_ab32ch0_config) {
    *(Uns32*)data = DMACSP_ab32ch0_data.config.value;
}

static PPM_VIEW_CB(view_DMACSP_ab32ch1_config) {
    *(Uns32*)data = DMACSP_ab32ch1_data.config.value;
}
//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.DMACSP = ppmCreateSlaveBusPort("DMACSP", 320);
    if (!handles.DMACSP) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'DMACSP'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "ab8_intTCstatus",
            "internal TC status",
            handles.DMACSP,
            0x4,
            1,
            read_8,
            TCclearWr,
            view8,
            &(DMACSP_ab8_data.intTCstatus.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab8_rawTCstatus",
            "raw TC status",
            handles.DMACSP,
            0x14,
            1,
            read_8,
            0,
            view8,
            &(DMACSP_ab8_data.rawTCstatus.value),
            True
        );
    }
    {
        registerHandle ab8config_reg = ppmCreateRegister(
            "ab8_config",
            "configuration",
            handles.DMACSP,
            0x30,
            1,
            read_8,
            configWr,
            view8,
            &(DMACSP_ab8_data.config.value),
            True
        );

        ppmCreateRegisterField(ab8config_reg, "burstSize", 0, 0, 2, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab32ch0_srcAddr",
            "channel 0 source address",
            handles.DMACSP,
            0x100,
            4,
            read_32,
            write_32,
            view32,
            &(DMACSP_ab32ch0_data.srcAddr.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab32ch0_dstAddr",
            "channel 0 dest address",
            handles.DMACSP,
            0x104,
            4,
            read_32,
            write_32,
            view32,
            &(DMACSP_ab32ch0_data.dstAddr.value),
            True
        );
    }
    {
        registerHandle ab32ch0control_reg = ppmCreateRegister(
            "ab32ch0_control",
            "channel 0 control",
            handles.DMACSP,
            0x10c,
            4,
            read_32,
            write_32,
            view32,
            &(DMACSP_ab32ch0_data.control.value),
            True
        );

        ppmCreateRegisterField(ab32ch0control_reg, "transferSize", 0, 0, 12, 1, 1);
    }
    {
        registerHandle ab32ch0config_reg = ppmCreateRegister(
            "ab32ch0_config",
            "channel 0 configuration",
            handles.DMACSP,
            0x110,
            4,
            read_32,
            configChWr,
            view_DMACSP_ab32ch0_config,
            (void*)0,
            True
        );

        ppmCreateRegisterField(ab32ch0config_reg, "enable", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(ab32ch0config_reg, "inten", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(ab32ch0config_reg, "halt", 0, 18, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab32ch1_srcAddr",
            "channel 1 source address",
            handles.DMACSP,
            0x120,
            4,
            read_32,
            write_32,
            view32,
            &(DMACSP_ab32ch1_data.srcAddr.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab32ch1_dstAddr",
            "channel 1 dest address",
            handles.DMACSP,
            0x124,
            4,
            read_32,
            write_32,
            view32,
            &(DMACSP_ab32ch1_data.dstAddr.value),
            True
        );
    }
    {
        registerHandle ab32ch1control_reg = ppmCreateRegister(
            "ab32ch1_control",
            "channel 1 control",
            handles.DMACSP,
            0x12c,
            4,
            read_32,
            write_32,
            view32,
            &(DMACSP_ab32ch1_data.control.value),
            True
        );

        ppmCreateRegisterField(ab32ch1control_reg, "transferSize", 0, 0, 12, 1, 1);
    }
    {
        registerHandle ab32ch1config_reg = ppmCreateRegister(
            "ab32ch1_config",
            "channel 1 configuration",
            handles.DMACSP,
            0x130,
            4,
            read_32,
            configChWr,
            view_DMACSP_ab32ch1_config,
            (void*)1,
            True
        );

        ppmCreateRegisterField(ab32ch1config_reg, "enable", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(ab32ch1config_reg, "inten", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(ab32ch1config_reg, "halt", 0, 18, 1, 1, 1);
    }

}

/////////////////////////////// Bus Master Ports ///////////////////////////////

static void installMasterPorts(void) {
    handles.MREAD = ppmOpenAddressSpace("MREAD");
    handles.MWRITE = ppmOpenAddressSpace("MWRITE");
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Basic DMA Controller.");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model is a basic DMA engine example implementation, it does not conform to an actual device.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "This is not based upon a real device");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installMasterPorts();
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


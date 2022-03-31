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

config_ab_dataT config_ab_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "GD5446", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

static PPM_WRITE_CB(write_8) { *(Uns8*)user = data; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.config = ppmCreateSlaveBusPort("config", 48);
    if (!handles.config) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'config'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "ab_cr_index",
            0,
            handles.config,
            0x4,
            1,
            read_8,
            write_8,
            view8,
            &(config_ab_data.cr_index.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_cr",
            0,
            handles.config,
            0x5,
            1,
            read_8,
            write_8,
            view8,
            &(config_ab_data.cr.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_gr_index",
            0,
            handles.config,
            0x1e,
            1,
            read_8,
            write_8,
            view8,
            &(config_ab_data.gr_index.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ar_index",
            0,
            handles.config,
            0x10,
            1,
            read_8,
            write_8,
            view8,
            &(config_ab_data.ar_index.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ar",
            0,
            handles.config,
            0x11,
            1,
            read_8,
            0,
            view8,
            &(config_ab_data.ar.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_msrWrite",
            0,
            handles.config,
            0x12,
            1,
            0,
            write_8,
            view8,
            &(config_ab_data.msrWrite.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_st00",
            0,
            handles.config,
            0x12,
            1,
            read_8,
            0,
            view8,
            &(config_ab_data.st00.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_gr",
            0,
            handles.config,
            0x1f,
            1,
            read_8,
            write_8,
            view8,
            &(config_ab_data.gr.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_sr_index",
            0,
            handles.config,
            0x14,
            1,
            read_8,
            write_8,
            view8,
            &(config_ab_data.sr_index.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_sr",
            0,
            handles.config,
            0x15,
            1,
            read_8,
            write_8,
            view8,
            &(config_ab_data.sr.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_fcrWrite",
            0,
            handles.config,
            0xa,
            1,
            0,
            write_8,
            view8,
            &(config_ab_data.fcrWrite.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_st01",
            0,
            handles.config,
            0xa,
            1,
            read_8,
            0,
            view8,
            &(config_ab_data.st01.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_dac_read_index",
            0,
            handles.config,
            0x17,
            1,
            read_8,
            write_8,
            view8,
            &(config_ab_data.dac_read_index.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_dac_write_index",
            0,
            handles.config,
            0x18,
            1,
            read_8,
            write_8,
            view8,
            &(config_ab_data.dac_write_index.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_dac_cache",
            0,
            handles.config,
            0x19,
            1,
            read_8,
            write_8,
            view8,
            &(config_ab_data.dac_cache.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_fcrRead",
            0,
            handles.config,
            0x1a,
            1,
            read_8,
            0,
            view8,
            &(config_ab_data.fcrRead.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_msrRead",
            0,
            handles.config,
            0x1c,
            1,
            read_8,
            0,
            view8,
            &(config_ab_data.msrRead.value),
            True
        );
    }



}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Cirrus CL GD5446 VGA controller.");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model has sufficient functionality to allow a Linux Kernel to Boot on the MIPS:MALTA platform. \n                       The VGA peripheral utilises memory mapping. \n                       This requires the use of ICM memory for the frame buffers, which currently may stop its use in SystemC TLM2 platforms.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "CL-GD5446 Preliminary Databook, Version 2.0, November 1996");
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
    destructor();
    return 0;
}


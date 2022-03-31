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

port0_msip_dataT port0_msip_data;

port0_mtime_dataT port0_mtime_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "CLINT", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.port0 = ppmCreateSlaveBusPort("port0", 49152);

    ppmInstallNByteCallbacks(defaultMemRead, defaultMemWrite, 0, handles.port0, 0x0, 0xc000, True, True, False, BHM_ENDIAN_LITTLE);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateNByteRegister(
            "msip_msip0",
            "Hart 0 Machine-Mode Software Interrupt",
            handles.port0,
            0x0,
            4,
            msipRead,
            msipWrite,
            msipView,
            &(port0_msip_data.msip0.value),
            (void*)0,
            False,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "mtime_mtimecmp0",
            "Hart 0 Machine-Mode Timer Compare",
            handles.port0,
            0x4000,
            8,
            mtimecmpRead,
            mtimecmpWrite,
            mtimecmpView,
            &(port0_mtime_data.mtimecmp0.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "mtime_mtime",
            "Machine-Mode mtime",
            handles.port0,
            0xbff8,
            8,
            mtimeRead,
            mtimeWrite,
            mtimeView,
            &(port0_mtime_data.mtime.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }

}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "SiFive-compatabile Risc-V Core Local Interruptor (CLINT).");
        ppmDocAddText(doc_12_node, "Use the num_harts parameter to specify the number of harts suported (default 1).");
        ppmDocAddText(doc_12_node, "For each supported hart there will be an MTimerInterruptN and MSWInterruptN net port, plus msipN and mtimecmpN registers implemented, where N is a value from 0..num_harts-1.");
        ppmDocAddText(doc_12_node, "There is also a single mtime register.");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "Various SiFive Core Complex manuals, e.g. SiFive U54 Core Complex Manual (https://sifive.cdn.prismic.io/sifive/a07d1a9a-2cb8-4cf5-bb75-5351888ea2e1_u54_core_complex_manual_21G2.pdf)");
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


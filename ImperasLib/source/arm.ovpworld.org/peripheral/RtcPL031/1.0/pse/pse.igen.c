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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "RtcPL031", "Example");
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

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "ab_dr",
            "Data read",
            handles.bport1,
            0x0,
            4,
            readDR,
            0,
            view32,
            &(bport1_ab_data.dr.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_mr",
            "Match",
            handles.bport1,
            0x4,
            4,
            read_32,
            writeMR,
            view32,
            &(bport1_ab_data.mr.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_lr",
            "Data load",
            handles.bport1,
            0x8,
            4,
            read_32,
            writeLR,
            view32,
            &(bport1_ab_data.lr.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_cr",
            "Control",
            handles.bport1,
            0xc,
            4,
            readCR,
            writeCR,
            view32,
            &(bport1_ab_data.cr.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_im",
            "Interrupt mask",
            handles.bport1,
            0x10,
            4,
            read_32,
            writeIM,
            view32,
            &(bport1_ab_data.im.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_is",
            "Raw interrupt",
            handles.bport1,
            0x14,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.is.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_mis",
            "Masked interrupt",
            handles.bport1,
            0x18,
            4,
            readMIS,
            0,
            view32,
            &(bport1_ab_data.mis.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_icr",
            "Interrupt clear",
            handles.bport1,
            0x1c,
            4,
            0,
            writeICR,
            view32,
            &(bport1_ab_data.icr.value),
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
        ppmDocAddText(doc2_node, "ARM PL031 Real Time Clock (RTC)");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "none");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "ARM PrimeCell Real Time Clock (PL031) Technical Reference Manual (ARM DDI 0224)");
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


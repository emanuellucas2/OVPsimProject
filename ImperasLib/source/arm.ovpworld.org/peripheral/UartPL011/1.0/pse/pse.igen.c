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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "UartPL011", "Example");
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

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "ab_dr",
            "UARTDR",
            handles.bport1,
            0x0,
            4,
            readDR,
            writeDR,
            view32,
            &(bport1_ab_data.dr.value),
            True
        );
    }
    {
        registerHandle abecr_reg = ppmCreateRegister(
            "ab_ecr",
            "UARTECR",
            handles.bport1,
            0x4,
            4,
            readECR,
            writeECR,
            view32,
            &(bport1_ab_data.ecr.value),
            True
        );

        ppmCreateRegisterField(abecr_reg, "OE", 0, 3, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_ilpr",
            "UARTILPR",
            handles.bport1,
            0x20,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ilpr.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ibrd",
            "UARTIBRD",
            handles.bport1,
            0x24,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ibrd.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_vbrd",
            "UARTFBRD",
            handles.bport1,
            0x28,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.vbrd.value),
            True
        );
    }
    {
        registerHandle ablcr_reg = ppmCreateRegister(
            "ab_lcr",
            "UARTLCR_H",
            handles.bport1,
            0x2c,
            4,
            read_32,
            writeLCR,
            view32,
            &(bport1_ab_data.lcr.value),
            True
        );

        ppmCreateRegisterField(ablcr_reg, "FEN", 0, 4, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_cr",
            "UARTCR",
            handles.bport1,
            0x30,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.cr.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ifl",
            "UARTIFS",
            handles.bport1,
            0x34,
            4,
            read_32,
            writeIFL,
            view32,
            &(bport1_ab_data.ifl.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_int_enabled",
            "UARTIMSC",
            handles.bport1,
            0x38,
            4,
            read_32,
            writeIMSC,
            view32,
            &(bport1_ab_data.int_enabled.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_mis",
            "UARTMIS",
            handles.bport1,
            0x40,
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
            "UARTDICR",
            handles.bport1,
            0x44,
            4,
            0,
            writeICR,
            view32,
            &(bport1_ab_data.icr.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_dmacr",
            "UARTDMACR",
            handles.bport1,
            0x48,
            4,
            read_32,
            writeDMA,
            view32,
            &(bport1_ab_data.dmacr.value),
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
        ppmDocAddText(doc2_node, "ARM PL011 UART");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "This is not a complete model of the PL011. There is no modeling of physical aspects of the UART, such as baud rates etc.");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "ARM PrimeCell UART (PL011) Technical Reference Manual (ARM DDI 0183)");
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
    closeDown();
    return 0;
}


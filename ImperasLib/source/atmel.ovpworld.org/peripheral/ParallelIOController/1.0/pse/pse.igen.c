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

bp1_REG_dataT bp1_REG_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "ParallelIOController", "Example");
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
    handles.bp1 = ppmCreateSlaveBusPort("bp1", 16384);
    if (!handles.bp1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bp1'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "REG_PIO_PER",
            0,
            handles.bp1,
            0x0,
            4,
            0,
            PIO_PER_wcb,
            view32,
            &(bp1_REG_data.PIO_PER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_PIO_PDR",
            0,
            handles.bp1,
            0x4,
            4,
            0,
            PIO_PDR_wcb,
            view32,
            &(bp1_REG_data.PIO_PDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_PIO_PSR",
            0,
            handles.bp1,
            0x8,
            4,
            read_32,
            0,
            view32,
            &(bp1_REG_data.PIO_PSR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_PIO_OER",
            0,
            handles.bp1,
            0x10,
            4,
            0,
            PIO_OER_wcb,
            view32,
            &(bp1_REG_data.PIO_OER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_PIO_ODR",
            0,
            handles.bp1,
            0x14,
            4,
            0,
            PIO_ODR_wcb,
            view32,
            &(bp1_REG_data.PIO_ODR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_PIO_OSR",
            0,
            handles.bp1,
            0x18,
            4,
            read_32,
            0,
            view32,
            &(bp1_REG_data.PIO_OSR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_PIO_IFER",
            0,
            handles.bp1,
            0x20,
            4,
            0,
            PIO_IFER_wcb,
            view32,
            &(bp1_REG_data.PIO_IFER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_PIO_IFDR",
            0,
            handles.bp1,
            0x24,
            4,
            0,
            PIO_IFDR_wcb,
            view32,
            &(bp1_REG_data.PIO_IFDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_PIO_IFSR",
            0,
            handles.bp1,
            0x28,
            4,
            read_32,
            0,
            view32,
            &(bp1_REG_data.PIO_IFSR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_PIO_SODR",
            0,
            handles.bp1,
            0x30,
            4,
            0,
            PIO_SODR_wcb,
            view32,
            &(bp1_REG_data.PIO_SODR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_PIO_CODR",
            0,
            handles.bp1,
            0x34,
            4,
            0,
            PIO_CODR_wcb,
            view32,
            &(bp1_REG_data.PIO_CODR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_PIO_ODSR",
            0,
            handles.bp1,
            0x38,
            4,
            read_32,
            0,
            view32,
            &(bp1_REG_data.PIO_ODSR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_PIO_PDSR",
            0,
            handles.bp1,
            0x3c,
            4,
            read_32,
            0,
            view32,
            &(bp1_REG_data.PIO_PDSR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_PIO_IER",
            0,
            handles.bp1,
            0x40,
            4,
            0,
            PIO_IER_wcb,
            view32,
            &(bp1_REG_data.PIO_IER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_PIO_IDR",
            0,
            handles.bp1,
            0x44,
            4,
            0,
            PIO_IDR_wcb,
            view32,
            &(bp1_REG_data.PIO_IDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_PIO_IMR",
            0,
            handles.bp1,
            0x48,
            4,
            read_32,
            0,
            view32,
            &(bp1_REG_data.PIO_IMR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_PIO_ISR",
            0,
            handles.bp1,
            0x4c,
            4,
            read_32,
            0,
            view32,
            &(bp1_REG_data.PIO_ISR.value),
            True
        );
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bp1_REG_data.PIO_ISR.value = (Uns32)(bp1_REG_data.PIO_ISR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.PIO_IMR.value = (Uns32)(bp1_REG_data.PIO_IMR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.PIO_IDR.value = (Uns32)(bp1_REG_data.PIO_IDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.PIO_IER.value = (Uns32)(bp1_REG_data.PIO_IER.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.PIO_PDSR.value = (Uns32)(bp1_REG_data.PIO_PDSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.PIO_ODSR.value = (Uns32)(bp1_REG_data.PIO_ODSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.PIO_CODR.value = (Uns32)(bp1_REG_data.PIO_CODR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.PIO_SODR.value = (Uns32)(bp1_REG_data.PIO_SODR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.PIO_IFSR.value = (Uns32)(bp1_REG_data.PIO_IFSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.PIO_IFDR.value = (Uns32)(bp1_REG_data.PIO_IFDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.PIO_IFER.value = (Uns32)(bp1_REG_data.PIO_IFER.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.PIO_OSR.value = (Uns32)(bp1_REG_data.PIO_OSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.PIO_ODR.value = (Uns32)(bp1_REG_data.PIO_ODR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.PIO_OER.value = (Uns32)(bp1_REG_data.PIO_OER.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.PIO_PSR.value = (Uns32)(bp1_REG_data.PIO_PSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x01ffffff));
        bp1_REG_data.PIO_PDR.value = (Uns32)(bp1_REG_data.PIO_PDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.PIO_PER.value = (Uns32)(bp1_REG_data.PIO_PER.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "PIO: Parallel I/O Controller\nThis model contains an accurate Register set interface.\nThe functionality has only been implemented to sufficiently boot uClinux\nThe Parallel I/O Controller has 32 programmable I/O lines. Six pins are dedicated as general-purpose\nI/O pins. Other I/O lines are multiplexed with an external signal of a peripheral to optimize\nthe use of available package pins. The PIO controller enables generation of an interrupt on input\nchange and insertion of a simple input glitch filter on any of the PIO pins.\nfor more information visit http://www.atmel.com/products/at91");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model is sufficient to boot Linux");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Rev. 1354D ARM08/02");
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
    periphConstructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}


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

DMAP0_abc_dataT DMAP0_abc_data;

DMAP1_abw_dataT DMAP1_abw_data;

DMAP1_abb_dataT DMAP1_abb_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "dma", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_VIEW_CB(view16) {  *(Uns16*)data = *(Uns16*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.DMAP0 = ppmCreateSlaveBusPort("DMAP0", 16);

    handles.DMAP1 = ppmCreateSlaveBusPort("DMAP1", 256);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "abc_DMAWC0",
            "DMA Controller Wait Control Register 0",
            handles.DMAP0,
            0x0,
            2,
            readDMAWC0,
            writeDMAWC0,
            view16,
            &(DMAP0_abc_data.DMAWC0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "abc_DMAWC1",
            "DMA Controller Wait Control Register 1",
            handles.DMAP0,
            0x2,
            2,
            readDMAWC1,
            writeDMAWC1,
            view16,
            &(DMAP0_abc_data.DMAWC1.value),
            True
        );
    }

    {
        ppmCreateNByteRegister(
            "abw_MAR0",
            "DMA Controller Transfer Memory Start Address Register",
            handles.DMAP1,
            0x0,
            2,
            readMAR,
            writeMAR,
            0,
            &(DMAP1_abw_data.MAR[0].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "abw_MAR1",
            "DMA Controller Transfer Memory Start Address Register",
            handles.DMAP1,
            0x2,
            2,
            readMAR,
            writeMAR,
            0,
            &(DMAP1_abw_data.MAR[1].value),
            (void*)1,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "abw_MAR2",
            "DMA Controller Transfer Memory Start Address Register",
            handles.DMAP1,
            0x4,
            2,
            readMAR,
            writeMAR,
            0,
            &(DMAP1_abw_data.MAR[2].value),
            (void*)2,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "abw_MAR3",
            "DMA Controller Transfer Memory Start Address Register",
            handles.DMAP1,
            0x6,
            2,
            readMAR,
            writeMAR,
            0,
            &(DMAP1_abw_data.MAR[3].value),
            (void*)3,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "abw_MAR4",
            "DMA Controller Transfer Memory Start Address Register",
            handles.DMAP1,
            0x8,
            2,
            readMAR,
            writeMAR,
            0,
            &(DMAP1_abw_data.MAR[4].value),
            (void*)4,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "abw_MAR5",
            "DMA Controller Transfer Memory Start Address Register",
            handles.DMAP1,
            0xa,
            2,
            readMAR,
            writeMAR,
            0,
            &(DMAP1_abw_data.MAR[5].value),
            (void*)5,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "abw_MAR6",
            "DMA Controller Transfer Memory Start Address Register",
            handles.DMAP1,
            0xc,
            2,
            readMAR,
            writeMAR,
            0,
            &(DMAP1_abw_data.MAR[6].value),
            (void*)6,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "abw_MAR7",
            "DMA Controller Transfer Memory Start Address Register",
            handles.DMAP1,
            0xe,
            2,
            readMAR,
            writeMAR,
            0,
            &(DMAP1_abw_data.MAR[7].value),
            (void*)7,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "abw_MAR8",
            "DMA Controller Transfer Memory Start Address Register",
            handles.DMAP1,
            0x10,
            2,
            readMAR,
            writeMAR,
            0,
            &(DMAP1_abw_data.MAR[8].value),
            (void*)8,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "abw_MAR9",
            "DMA Controller Transfer Memory Start Address Register",
            handles.DMAP1,
            0x12,
            2,
            readMAR,
            writeMAR,
            0,
            &(DMAP1_abw_data.MAR[9].value),
            (void*)9,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        registerHandle abbSAR_reg = ppmCreateNByteRegister(
            "abb_SAR2",
            "DMA Controller Transfer SFR Start Adrress Register",
            handles.DMAP1,
            0x24,
            1,
            readSAR,
            writeSAR,
            0,
            &(DMAP1_abb_data.SAR[0].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abbSAR_reg, "SAR", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abbSAR_reg = ppmCreateNByteRegister(
            "abb_SAR3",
            "DMA Controller Transfer SFR Start Adrress Register",
            handles.DMAP1,
            0x25,
            1,
            readSAR,
            writeSAR,
            0,
            &(DMAP1_abb_data.SAR[1].value),
            (void*)1,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abbSAR_reg, "SAR", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abbDTFR_reg = ppmCreateNByteRegister(
            "abb_DTFR4",
            "DMA Controller Trigger Factor register",
            handles.DMAP1,
            0x80,
            1,
            readDTFR,
            writeDTFR,
            0,
            &(DMAP1_abb_data.DTFR[0].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abbDTFR_reg, "IFCn", 0, 0, 3, 1, 1);
    }
    {
        registerHandle abbDTFR_reg = ppmCreateNByteRegister(
            "abb_DTFR5",
            "DMA Controller Trigger Factor register",
            handles.DMAP1,
            0x81,
            1,
            readDTFR,
            writeDTFR,
            0,
            &(DMAP1_abb_data.DTFR[1].value),
            (void*)1,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abbDTFR_reg, "IFCn", 0, 0, 3, 1, 1);
    }
    {
        registerHandle abbDTFR_reg = ppmCreateNByteRegister(
            "abb_DTFR6",
            "DMA Controller Trigger Factor register",
            handles.DMAP1,
            0x82,
            1,
            readDTFR,
            writeDTFR,
            0,
            &(DMAP1_abb_data.DTFR[2].value),
            (void*)2,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abbDTFR_reg, "IFCn", 0, 0, 3, 1, 1);
    }
    {
        registerHandle abbDTFR_reg = ppmCreateNByteRegister(
            "abb_DTFR7",
            "DMA Controller Trigger Factor register",
            handles.DMAP1,
            0x83,
            1,
            readDTFR,
            writeDTFR,
            0,
            &(DMAP1_abb_data.DTFR[3].value),
            (void*)3,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abbDTFR_reg, "IFCn", 0, 0, 3, 1, 1);
    }
    {
        ppmCreateNByteRegister(
            "abb_DTCR0",
            "DMA Controller Transfer Count register",
            handles.DMAP1,
            0x40,
            1,
            readDTCR,
            writeDTCR,
            0,
            &(DMAP1_abb_data.DTCR[0].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "abb_DTCR1",
            "DMA Controller Transfer Count register",
            handles.DMAP1,
            0x41,
            1,
            readDTCR,
            writeDTCR,
            0,
            &(DMAP1_abb_data.DTCR[1].value),
            (void*)1,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "abb_DTCR2",
            "DMA Controller Transfer Count register",
            handles.DMAP1,
            0x42,
            1,
            readDTCR,
            writeDTCR,
            0,
            &(DMAP1_abb_data.DTCR[2].value),
            (void*)2,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "abb_DTCR3",
            "DMA Controller Transfer Count register",
            handles.DMAP1,
            0x43,
            1,
            readDTCR,
            writeDTCR,
            0,
            &(DMAP1_abb_data.DTCR[3].value),
            (void*)3,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "abb_DTCR4",
            "DMA Controller Transfer Count register",
            handles.DMAP1,
            0x44,
            1,
            readDTCR,
            writeDTCR,
            0,
            &(DMAP1_abb_data.DTCR[4].value),
            (void*)4,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "abb_DTCR5",
            "DMA Controller Transfer Count register",
            handles.DMAP1,
            0x45,
            1,
            readDTCR,
            writeDTCR,
            0,
            &(DMAP1_abb_data.DTCR[5].value),
            (void*)5,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "abb_DTCR6",
            "DMA Controller Transfer Count register",
            handles.DMAP1,
            0x46,
            1,
            readDTCR,
            writeDTCR,
            0,
            &(DMAP1_abb_data.DTCR[6].value),
            (void*)6,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "abb_DTCR7",
            "DMA Controller Transfer Count register",
            handles.DMAP1,
            0x47,
            1,
            readDTCR,
            writeDTCR,
            0,
            &(DMAP1_abb_data.DTCR[7].value),
            (void*)7,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "abb_DTCR8",
            "DMA Controller Transfer Count register",
            handles.DMAP1,
            0x48,
            1,
            readDTCR,
            writeDTCR,
            0,
            &(DMAP1_abb_data.DTCR[8].value),
            (void*)8,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "abb_DTCR9",
            "DMA Controller Transfer Count register",
            handles.DMAP1,
            0x49,
            1,
            readDTCR,
            writeDTCR,
            0,
            &(DMAP1_abb_data.DTCR[9].value),
            (void*)9,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        registerHandle abbDMASL_reg = ppmCreateRegister(
            "abb_DMASL",
            "DMA Controller Status Register",
            handles.DMAP1,
            0x62,
            1,
            readDMASL,
            writeDMASL,
            view8,
            &(DMAP1_abb_data.DMASL.value),
            True
        );

        ppmCreateRegisterField(abbDMASL_reg, "DMAS7", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abbDMASL_reg, "DMAS6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abbDMASL_reg, "DMAS5", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abbDMASL_reg, "DMAS4", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abbDMASL_reg, "DMAS3", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abbDMASL_reg, "DMAS2", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abbDMASL_reg, "DMAS1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abbDMASL_reg, "DMAS0", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abbDMAMCL_reg = ppmCreateRegister(
            "abb_DMAMCL",
            "DMA Controller Mode Control Register",
            handles.DMAP1,
            0x60,
            1,
            readDMAMCL,
            writeDMAMCL,
            view8,
            &(DMAP1_abb_data.DMAMCL.value),
            True
        );

        ppmCreateRegisterField(abbDMAMCL_reg, "DE7", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abbDMAMCL_reg, "DE6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abbDMAMCL_reg, "DE5", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abbDMAMCL_reg, "DE4", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abbDMAMCL_reg, "DE3", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abbDMAMCL_reg, "DE2", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abbDMAMCL_reg, "DE1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abbDMAMCL_reg, "DE0", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abbDMADSCL_reg = ppmCreateRegister(
            "abb_DMADSCL",
            "DMA Controller Data Size Control Register",
            handles.DMAP1,
            0x64,
            1,
            readDMADSCL,
            writeDMADSCL,
            view8,
            &(DMAP1_abb_data.DMADSCL.value),
            True
        );

        ppmCreateRegisterField(abbDMADSCL_reg, "DMADCS7", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abbDMADSCL_reg, "DMADCS6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abbDMADSCL_reg, "DMADCS5", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abbDMADSCL_reg, "DMADCS4", 0, 4, 1, 1, 1);
    }

}

/////////////////////////////// Bus Master Ports ///////////////////////////////

static void installMasterPorts(void) {
    handles.DMAPM = ppmOpenAddressSpace("DMAPM");
}

PPM_NET_CB(reset_reset) {
    if(value != 0 ) {
        DMAP1_abb_data.DMADSCL.value = (Uns8)(DMAP1_abb_data.DMADSCL.value & ~(0xff)) | ((0xff) & (0x00));
        DMAP1_abb_data.DMAMCL.value = (Uns8)(DMAP1_abb_data.DMAMCL.value & ~(0xff)) | ((0xff) & (0x00));
        DMAP1_abb_data.DMASL.value = (Uns8)(DMAP1_abb_data.DMASL.value & ~(0xff)) | ((0xff) & (0x00));
        DMAP1_abb_data.DTCR[0].value = (Uns8)(DMAP1_abb_data.DTCR[0].value & ~(0xff)) | ((0xff) & (0x00));
        DMAP1_abb_data.DTCR[1].value = (Uns8)(DMAP1_abb_data.DTCR[1].value & ~(0xff)) | ((0xff) & (0x00));
        DMAP1_abb_data.DTCR[2].value = (Uns8)(DMAP1_abb_data.DTCR[2].value & ~(0xff)) | ((0xff) & (0x00));
        DMAP1_abb_data.DTCR[3].value = (Uns8)(DMAP1_abb_data.DTCR[3].value & ~(0xff)) | ((0xff) & (0x00));
        DMAP1_abb_data.DTCR[4].value = (Uns8)(DMAP1_abb_data.DTCR[4].value & ~(0xff)) | ((0xff) & (0x00));
        DMAP1_abb_data.DTCR[5].value = (Uns8)(DMAP1_abb_data.DTCR[5].value & ~(0xff)) | ((0xff) & (0x00));
        DMAP1_abb_data.DTCR[6].value = (Uns8)(DMAP1_abb_data.DTCR[6].value & ~(0xff)) | ((0xff) & (0x00));
        DMAP1_abb_data.DTCR[7].value = (Uns8)(DMAP1_abb_data.DTCR[7].value & ~(0xff)) | ((0xff) & (0x00));
        DMAP1_abb_data.DTCR[8].value = (Uns8)(DMAP1_abb_data.DTCR[8].value & ~(0xff)) | ((0xff) & (0x00));
        DMAP1_abb_data.DTCR[9].value = (Uns8)(DMAP1_abb_data.DTCR[9].value & ~(0xff)) | ((0xff) & (0x00));
        DMAP1_abb_data.DTFR[0].value = (Uns8)(DMAP1_abb_data.DTFR[0].value & ~(0xff)) | ((0xff) & (0x00));
        DMAP1_abb_data.DTFR[1].value = (Uns8)(DMAP1_abb_data.DTFR[1].value & ~(0xff)) | ((0xff) & (0x00));
        DMAP1_abb_data.DTFR[2].value = (Uns8)(DMAP1_abb_data.DTFR[2].value & ~(0xff)) | ((0xff) & (0x00));
        DMAP1_abb_data.DTFR[3].value = (Uns8)(DMAP1_abb_data.DTFR[3].value & ~(0xff)) | ((0xff) & (0x00));
        DMAP1_abb_data.SAR[0].value = (Uns8)(DMAP1_abb_data.SAR[0].value & ~(0xff)) | ((0xff) & (0x00));
        DMAP1_abb_data.SAR[1].value = (Uns8)(DMAP1_abb_data.SAR[1].value & ~(0xff)) | ((0xff) & (0x00));
        DMAP1_abw_data.MAR[0].value = (Uns16)(DMAP1_abw_data.MAR[0].value & ~(0xffff)) | ((0xffff) & (0x00));
        DMAP1_abw_data.MAR[1].value = (Uns16)(DMAP1_abw_data.MAR[1].value & ~(0xffff)) | ((0xffff) & (0x00));
        DMAP1_abw_data.MAR[2].value = (Uns16)(DMAP1_abw_data.MAR[2].value & ~(0xffff)) | ((0xffff) & (0x00));
        DMAP1_abw_data.MAR[3].value = (Uns16)(DMAP1_abw_data.MAR[3].value & ~(0xffff)) | ((0xffff) & (0x00));
        DMAP1_abw_data.MAR[4].value = (Uns16)(DMAP1_abw_data.MAR[4].value & ~(0xffff)) | ((0xffff) & (0x00));
        DMAP1_abw_data.MAR[5].value = (Uns16)(DMAP1_abw_data.MAR[5].value & ~(0xffff)) | ((0xffff) & (0x00));
        DMAP1_abw_data.MAR[6].value = (Uns16)(DMAP1_abw_data.MAR[6].value & ~(0xffff)) | ((0xffff) & (0x00));
        DMAP1_abw_data.MAR[7].value = (Uns16)(DMAP1_abw_data.MAR[7].value & ~(0xffff)) | ((0xffff) & (0x00));
        DMAP1_abw_data.MAR[8].value = (Uns16)(DMAP1_abw_data.MAR[8].value & ~(0xffff)) | ((0xffff) & (0x00));
        DMAP1_abw_data.MAR[9].value = (Uns16)(DMAP1_abw_data.MAR[9].value & ~(0xffff)) | ((0xffff) & (0x00));
        DMAP0_abc_data.DMAWC1.value = (Uns16)(DMAP0_abc_data.DMAWC1.value & ~(0xffff)) | ((0xffff) & (0x07));
        DMAP0_abc_data.DMAWC0.value = (Uns16)(DMAP0_abc_data.DMAWC0.value & ~(0xffff)) | ((0xffff) & (0x37));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Renesas DMA Controller");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Initial implementation to support CAN DMA message transfer only");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installMasterPorts();
    reset_reset(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}


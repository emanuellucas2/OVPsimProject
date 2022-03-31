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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "VybridI2C", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_IBAD_maskWrite) {
    bport1_ab_data.IBAD.value = (bport1_ab_data.IBAD.value & BPORT1_AB_IBAD_WRNMASK) | (data & BPORT1_AB_IBAD_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_IBCR_maskWrite) {
    bport1_ab_data.IBCR.value = (bport1_ab_data.IBCR.value & BPORT1_AB_IBCR_WRNMASK) | (data & BPORT1_AB_IBCR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_IBDBG_maskWrite) {
    bport1_ab_data.IBDBG.value = (bport1_ab_data.IBDBG.value & BPORT1_AB_IBDBG_WRNMASK) | (data & BPORT1_AB_IBDBG_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_IBDR_maskWrite) {
    bport1_ab_data.IBDR.value = (bport1_ab_data.IBDR.value & BPORT1_AB_IBDR_WRNMASK) | (data & BPORT1_AB_IBDR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_IBFD_maskWrite) {
    bport1_ab_data.IBFD.value = (bport1_ab_data.IBFD.value & BPORT1_AB_IBFD_WRNMASK) | (data & BPORT1_AB_IBFD_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_IBIC_maskWrite) {
    bport1_ab_data.IBIC.value = (bport1_ab_data.IBIC.value & BPORT1_AB_IBIC_WRNMASK) | (data & BPORT1_AB_IBIC_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abIBAD_reg = ppmCreateRegister(
            "ab_IBAD",
            "I2C Bus Address Register, offset: 0x0",
            handles.bport1,
            0x0,
            1,
            read_8,
            bport1_ab_IBAD_maskWrite,
            view8,
            &(bport1_ab_data.IBAD.value),
            True
        );

        ppmCreateRegisterField(abIBAD_reg, "ADR", 0, 1, 7, 1, 1);
    }
    {
        registerHandle abIBFD_reg = ppmCreateRegister(
            "ab_IBFD",
            "I2C Bus Frequency Divider Register, offset: 0x1",
            handles.bport1,
            0x1,
            1,
            read_8,
            bport1_ab_IBFD_maskWrite,
            view8,
            &(bport1_ab_data.IBFD.value),
            True
        );

        ppmCreateRegisterField(abIBFD_reg, "IBC", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abIBCR_reg = ppmCreateRegister(
            "ab_IBCR",
            "I2C Bus Control Register, offset: 0x2",
            handles.bport1,
            0x2,
            1,
            read_8,
            bport1_ab_IBCR_maskWrite,
            view8,
            &(bport1_ab_data.IBCR.value),
            True
        );

        ppmCreateRegisterField(abIBCR_reg, "DMAEN", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abIBCR_reg, "IBIE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abIBCR_reg, "MDIS", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abIBCR_reg, "MSSL", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abIBCR_reg, "NOACK", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abIBCR_reg, "RSTA", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abIBCR_reg, "TXRX", 0, 4, 1, 1, 1);
    }
    {
        registerHandle abIBSR_reg = ppmCreateRegister(
            "ab_IBSR",
            "I2C Bus Status Register, offset: 0x3",
            handles.bport1,
            0x3,
            1,
            read_8,
            BSRWrite1C,
            view8,
            &(bport1_ab_data.IBSR.value),
            True
        );

        ppmCreateRegisterField(abIBSR_reg, "IAAS", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abIBSR_reg, "IBAL", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abIBSR_reg, "IBB", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abIBSR_reg, "IBIF", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abIBSR_reg, "RXAK", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abIBSR_reg, "SRW", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abIBSR_reg, "TCF", 0, 7, 1, 1, 1);
    }
    {
        registerHandle abIBDR_reg = ppmCreateRegister(
            "ab_IBDR",
            "I2C Bus Data I/O Register, offset: 0x4",
            handles.bport1,
            0x4,
            1,
            read_8,
            bport1_ab_IBDR_maskWrite,
            view8,
            &(bport1_ab_data.IBDR.value),
            True
        );

        ppmCreateRegisterField(abIBDR_reg, "DATA", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abIBIC_reg = ppmCreateRegister(
            "ab_IBIC",
            "I2C Bus Interrupt Config Register, offset: 0x5",
            handles.bport1,
            0x5,
            1,
            read_8,
            bport1_ab_IBIC_maskWrite,
            view8,
            &(bport1_ab_data.IBIC.value),
            True
        );

        ppmCreateRegisterField(abIBIC_reg, "BIIE", 0, 7, 1, 1, 1);
    }
    {
        registerHandle abIBDBG_reg = ppmCreateRegister(
            "ab_IBDBG",
            "I2C Bus Debug Register, offset: 0x6",
            handles.bport1,
            0x6,
            1,
            read_8,
            bport1_ab_IBDBG_maskWrite,
            view8,
            &(bport1_ab_data.IBDBG.value),
            True
        );

        ppmCreateRegisterField(abIBDBG_reg, "IPG_DEBUG_EN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abIBDBG_reg, "IPG_DEBUG_HALTED", 0, 1, 1, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.IBDBG.value = (Uns8)(bport1_ab_data.IBDBG.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.IBIC.value = (Uns8)(bport1_ab_data.IBIC.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.IBDR.value = (Uns8)(bport1_ab_data.IBDR.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.IBSR.value = (Uns8)(bport1_ab_data.IBSR.value & ~(0xff)) | ((0xff) & (0x80));
        bport1_ab_data.IBCR.value = (Uns8)(bport1_ab_data.IBCR.value & ~(0xff)) | ((0xff) & (0x80));
        bport1_ab_data.IBFD.value = (Uns8)(bport1_ab_data.IBFD.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.IBAD.value = (Uns8)(bport1_ab_data.IBAD.value & ~(0xff)) | ((0xff) & (0x00));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the I2C peripheral used on the Freescale Vybrid platform");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "Provides the base behaviour for the OVP Freescale Vybrid platforms");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "Development based on document number: VYBRIDRM Rev. 5, 07/2013");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_32_node, "Open Source Apache 2.0");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    reset_Reset(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}


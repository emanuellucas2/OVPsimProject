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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisNFC", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_CAR_maskWrite) {
    bport1_ab_data.CAR.value = (bport1_ab_data.CAR.value & BPORT1_AB_CAR_WRNMASK) | (data & BPORT1_AB_CAR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CFG_maskWrite) {
    bport1_ab_data.CFG.value = (bport1_ab_data.CFG.value & BPORT1_AB_CFG_WRNMASK) | (data & BPORT1_AB_CFG_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CMD1_maskWrite) {
    bport1_ab_data.CMD1.value = (bport1_ab_data.CMD1.value & BPORT1_AB_CMD1_WRNMASK) | (data & BPORT1_AB_CMD1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CMD2_maskWrite) {
    bport1_ab_data.CMD2.value = (bport1_ab_data.CMD2.value & BPORT1_AB_CMD2_WRNMASK) | (data & BPORT1_AB_CMD2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DMA1_maskWrite) {
    bport1_ab_data.DMA1.value = (bport1_ab_data.DMA1.value & BPORT1_AB_DMA1_WRNMASK) | (data & BPORT1_AB_DMA1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DMA2_maskWrite) {
    bport1_ab_data.DMA2.value = (bport1_ab_data.DMA2.value & BPORT1_AB_DMA2_WRNMASK) | (data & BPORT1_AB_DMA2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DMACFG_maskWrite) {
    bport1_ab_data.DMACFG.value = (bport1_ab_data.DMACFG.value & BPORT1_AB_DMACFG_WRNMASK) | (data & BPORT1_AB_DMACFG_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ISR_maskWrite) {
    bport1_ab_data.ISR.value = (bport1_ab_data.ISR.value & BPORT1_AB_ISR_WRNMASK) | (data & BPORT1_AB_ISR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RAI_maskWrite) {
    bport1_ab_data.RAI.value = (bport1_ab_data.RAI.value & BPORT1_AB_RAI_WRNMASK) | (data & BPORT1_AB_RAI_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RAR_maskWrite) {
    bport1_ab_data.RAR.value = (bport1_ab_data.RAR.value & BPORT1_AB_RAR_WRNMASK) | (data & BPORT1_AB_RAR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RPT_maskWrite) {
    bport1_ab_data.RPT.value = (bport1_ab_data.RPT.value & BPORT1_AB_RPT_WRNMASK) | (data & BPORT1_AB_RPT_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SECSZ_maskWrite) {
    bport1_ab_data.SECSZ.value = (bport1_ab_data.SECSZ.value & BPORT1_AB_SECSZ_WRNMASK) | (data & BPORT1_AB_SECSZ_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SWAP_maskWrite) {
    bport1_ab_data.SWAP.value = (bport1_ab_data.SWAP.value & BPORT1_AB_SWAP_WRNMASK) | (data & BPORT1_AB_SWAP_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 16384);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abCMD1_reg = ppmCreateRegister(
            "ab_CMD1",
            "Flash command 1, offset: 0x3F00 ",
            handles.bport1,
            0x3f00,
            4,
            read_32,
            bport1_ab_CMD1_maskWrite,
            view32,
            &(bport1_ab_data.CMD1.value),
            True
        );

        ppmCreateRegisterField(abCMD1_reg, "BYTE2", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abCMD1_reg, "BYTE3", 0, 16, 8, 1, 1);
    }
    {
        registerHandle abCMD2_reg = ppmCreateRegister(
            "ab_CMD2",
            "Flash command 2, offset: 0x3F04 ",
            handles.bport1,
            0x3f04,
            4,
            read_32,
            bport1_ab_CMD2_maskWrite,
            view32,
            &(bport1_ab_data.CMD2.value),
            True
        );

        ppmCreateRegisterField(abCMD2_reg, "BUFNO", 0, 1, 2, 1, 1);
        ppmCreateRegisterField(abCMD2_reg, "BUSY_START", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abCMD2_reg, "BYTE1", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abCMD2_reg, "CODE", 0, 8, 16, 1, 1);
    }
    {
        registerHandle abCAR_reg = ppmCreateRegister(
            "ab_CAR",
            "Column address, offset: 0x3F08 ",
            handles.bport1,
            0x3f08,
            4,
            read_32,
            bport1_ab_CAR_maskWrite,
            view32,
            &(bport1_ab_data.CAR.value),
            True
        );

        ppmCreateRegisterField(abCAR_reg, "BYTE1", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abCAR_reg, "BYTE2", 0, 8, 8, 1, 1);
    }
    {
        registerHandle abRAR_reg = ppmCreateRegister(
            "ab_RAR",
            "Row address, offset: 0x3F0C ",
            handles.bport1,
            0x3f0c,
            4,
            read_32,
            bport1_ab_RAR_maskWrite,
            view32,
            &(bport1_ab_data.RAR.value),
            True
        );

        ppmCreateRegisterField(abRAR_reg, "BYTE1", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abRAR_reg, "BYTE2", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abRAR_reg, "BYTE3", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abRAR_reg, "CS0", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abRAR_reg, "CS1", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abRAR_reg, "RB0", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abRAR_reg, "RB1", 0, 25, 1, 1, 1);
    }
    {
        registerHandle abRPT_reg = ppmCreateRegister(
            "ab_RPT",
            "Flash command repeat, offset: 0x3F10 ",
            handles.bport1,
            0x3f10,
            4,
            read_32,
            bport1_ab_RPT_maskWrite,
            view32,
            &(bport1_ab_data.RPT.value),
            True
        );

        ppmCreateRegisterField(abRPT_reg, "COUNT", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abRAI_reg = ppmCreateRegister(
            "ab_RAI",
            "Row address increment, offset: 0x3F14 ",
            handles.bport1,
            0x3f14,
            4,
            read_32,
            bport1_ab_RAI_maskWrite,
            view32,
            &(bport1_ab_data.RAI.value),
            True
        );

        ppmCreateRegisterField(abRAI_reg, "INC1", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abRAI_reg, "INC2", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abRAI_reg, "INC3", 0, 16, 8, 1, 1);
    }
    {
        registerHandle abSR1_reg = ppmCreateRegister(
            "ab_SR1",
            "Flash status 1, offset: 0x3F18 ",
            handles.bport1,
            0x3f18,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.SR1.value),
            True
        );

        ppmCreateRegisterField(abSR1_reg, "ID1", 0, 24, 8, 1, 0);
        ppmCreateRegisterField(abSR1_reg, "ID2", 0, 16, 8, 1, 0);
        ppmCreateRegisterField(abSR1_reg, "ID3", 0, 8, 8, 1, 0);
        ppmCreateRegisterField(abSR1_reg, "ID4", 0, 0, 8, 1, 0);
    }
    {
        registerHandle abSR2_reg = ppmCreateRegister(
            "ab_SR2",
            "Flash status 2, offset: 0x3F1C ",
            handles.bport1,
            0x3f1c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.SR2.value),
            True
        );

        ppmCreateRegisterField(abSR2_reg, "ID5", 0, 24, 8, 1, 0);
        ppmCreateRegisterField(abSR2_reg, "STATUS1", 0, 0, 8, 1, 0);
    }
    {
        registerHandle abDMA1_reg = ppmCreateRegister(
            "ab_DMA1",
            "DMA channel 1 address, offset: 0x3F20 ",
            handles.bport1,
            0x3f20,
            4,
            read_32,
            bport1_ab_DMA1_maskWrite,
            view32,
            &(bport1_ab_data.DMA1.value),
            True
        );

        ppmCreateRegisterField(abDMA1_reg, "ADDRESS", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDMACFG_reg = ppmCreateRegister(
            "ab_DMACFG",
            "DMA configuration, offset: 0x3F24 ",
            handles.bport1,
            0x3f24,
            4,
            read_32,
            bport1_ab_DMACFG_maskWrite,
            view32,
            &(bport1_ab_data.DMACFG.value),
            True
        );

        ppmCreateRegisterField(abDMACFG_reg, "ACT1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abDMACFG_reg, "ACT2", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abDMACFG_reg, "COUNT1", 0, 20, 12, 1, 1);
        ppmCreateRegisterField(abDMACFG_reg, "COUNT2", 0, 13, 7, 1, 1);
        ppmCreateRegisterField(abDMACFG_reg, "OFFSET2", 0, 9, 4, 1, 1);
    }
    {
        registerHandle abSWAP_reg = ppmCreateRegister(
            "ab_SWAP",
            "Cach swap, offset: 0x3F28 ",
            handles.bport1,
            0x3f28,
            4,
            read_32,
            bport1_ab_SWAP_maskWrite,
            view32,
            &(bport1_ab_data.SWAP.value),
            True
        );

        ppmCreateRegisterField(abSWAP_reg, "ADDR1", 0, 17, 11, 1, 1);
        ppmCreateRegisterField(abSWAP_reg, "ADDR2", 0, 1, 11, 1, 1);
    }
    {
        registerHandle abSECSZ_reg = ppmCreateRegister(
            "ab_SECSZ",
            "Sector size, offset: 0x3F2C ",
            handles.bport1,
            0x3f2c,
            4,
            read_32,
            bport1_ab_SECSZ_maskWrite,
            view32,
            &(bport1_ab_data.SECSZ.value),
            True
        );

        ppmCreateRegisterField(abSECSZ_reg, "SIZE", 0, 0, 13, 1, 1);
    }
    {
        registerHandle abCFG_reg = ppmCreateRegister(
            "ab_CFG",
            "Flash configuration, offset: 0x3F30 ",
            handles.bport1,
            0x3f30,
            4,
            read_32,
            bport1_ab_CFG_maskWrite,
            view32,
            &(bport1_ab_data.CFG.value),
            True
        );

        ppmCreateRegisterField(abCFG_reg, "AIAD", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abCFG_reg, "AIBN", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abCFG_reg, "BITWIDTH", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCFG_reg, "BTMD", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abCFG_reg, "DMAREQ", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abCFG_reg, "ECCAD", 0, 22, 9, 1, 1);
        ppmCreateRegisterField(abCFG_reg, "ECCMODE", 0, 17, 3, 1, 1);
        ppmCreateRegisterField(abCFG_reg, "ECCSRAM", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abCFG_reg, "FAST", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abCFG_reg, "IDCNT", 0, 13, 3, 1, 1);
        ppmCreateRegisterField(abCFG_reg, "PAGECNT", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(abCFG_reg, "STOPWERR", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abCFG_reg, "TIMEOUT", 0, 8, 5, 1, 1);
    }
    {
        registerHandle abDMA2_reg = ppmCreateRegister(
            "ab_DMA2",
            "DMA channel 2 address, offset: 0x3F34 ",
            handles.bport1,
            0x3f34,
            4,
            read_32,
            bport1_ab_DMA2_maskWrite,
            view32,
            &(bport1_ab_data.DMA2.value),
            True
        );

        ppmCreateRegisterField(abDMA2_reg, "ADDRESS", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abISR_reg = ppmCreateRegister(
            "ab_ISR",
            "Interrupt status, offset: 0x3F38 ",
            handles.bport1,
            0x3f38,
            4,
            read_32,
            bport1_ab_ISR_maskWrite,
            view32,
            &(bport1_ab_data.ISR.value),
            True
        );

        ppmCreateRegisterField(abISR_reg, "CMDBUSY", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abISR_reg, "DMABN", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(abISR_reg, "DMABUSY", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abISR_reg, "DONE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abISR_reg, "DONECLR", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abISR_reg, "DONEEN", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abISR_reg, "ECCBN", 0, 2, 2, 1, 1);
        ppmCreateRegisterField(abISR_reg, "ECCBUSY", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abISR_reg, "IDLE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abISR_reg, "IDLECLR", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abISR_reg, "IDLEEN", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abISR_reg, "RESBN", 0, 4, 2, 1, 1);
        ppmCreateRegisterField(abISR_reg, "RESBUSY", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abISR_reg, "WERR", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abISR_reg, "WERRCLR", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abISR_reg, "WERREN", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abISR_reg, "WERRNS", 0, 27, 1, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.ISR.value = (Uns32)(bport1_ab_data.ISR.value & ~(0xffffffff)) | ((0xffffffff) & (0x60000000));
        bport1_ab_data.DMA2.value = (Uns32)(bport1_ab_data.DMA2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CFG.value = (Uns32)(bport1_ab_data.CFG.value & ~(0xffffffff)) | ((0xffffffff) & (0x000ea631));
        bport1_ab_data.SECSZ.value = (Uns32)(bport1_ab_data.SECSZ.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000420));
        bport1_ab_data.SWAP.value = (Uns32)(bport1_ab_data.SWAP.value & ~(0xffffffff)) | ((0xffffffff) & (0x0ffe0ffe));
        bport1_ab_data.DMACFG.value = (Uns32)(bport1_ab_data.DMACFG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DMA1.value = (Uns32)(bport1_ab_data.DMA1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SR2.value = (Uns32)(bport1_ab_data.SR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SR1.value = (Uns32)(bport1_ab_data.SR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RAI.value = (Uns32)(bport1_ab_data.RAI.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RPT.value = (Uns32)(bport1_ab_data.RPT.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.RAR.value = (Uns32)(bport1_ab_data.RAR.value & ~(0xffffffff)) | ((0xffffffff) & (0x11000000));
        bport1_ab_data.CAR.value = (Uns32)(bport1_ab_data.CAR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CMD2.value = (Uns32)(bport1_ab_data.CMD2.value & ~(0xffffffff)) | ((0xffffffff) & (0x007ee000));
        bport1_ab_data.CMD1.value = (Uns32)(bport1_ab_data.CMD1.value & ~(0xffffffff)) | ((0xffffffff) & (0x30ff0000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the NFC peripheral used on the Freescale Kinetis platform");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "Provides the base behaviour for the OVP Freescale Kinetis platforms");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "www.freescale.com/Kinetis");
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


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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "zynq_7000-devcfg", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

    ppmInstallReadCallback(regNoDefinitionRead, (void*)0 , handles.bport1 + 0x0, 0x1000);
    ppmInstallWriteCallback(regNoDefinitionWrite, (void*)0 , handles.bport1 + 0x0, 0x1000);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abCTRL_reg = ppmCreateRegister(
            "ab_CTRL",
            "Control Register",
            handles.bport1,
            0x0,
            4,
            ReadCTRL,
            WriteCTRL,
            view32,
            &(bport1_ab_data.CTRL.value),
            True
        );

        ppmCreateRegisterField(abCTRL_reg, "FORCE_RST", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "PCFG_PROG_B", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "PCFG_POR_CNT_4K", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "PCAP_PR", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "PCAP_MODE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "PCAP_RATE_EN", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "MULTIBOOT_EN", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "JTAG_CHAIN_DIS", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "PCFG_AES_FUSE", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "PCFG_AES_EN", 0, 9, 3, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "SEU_EN", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "SEC_EN", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "SPNIDEN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "SPIDEN", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "NIDEN", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "DBGEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "DAP_EN", 0, 0, 3, 1, 1);
    }
    {
        registerHandle abLOCK_reg = ppmCreateRegister(
            "ab_LOCK",
            "LOCK",
            handles.bport1,
            0x4,
            4,
            ReadLOCK,
            WriteLOCK,
            view32,
            &(bport1_ab_data.LOCK.value),
            True
        );

        ppmCreateRegisterField(abLOCK_reg, "AES_FUSE_LOCK", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abLOCK_reg, "AES_EN_LOCK", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abLOCK_reg, "SEU_LOCK", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abLOCK_reg, "SEC_LOCK", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abLOCK_reg, "DBG_LOCK", 0, 0, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_CFG",
            "Configuration Register",
            handles.bport1,
            0x8,
            4,
            ReadCFG,
            WriteCFG,
            view32,
            &(bport1_ab_data.CFG.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_INT_STS",
            "Interrupt Status Register",
            handles.bport1,
            0xc,
            4,
            ReadINT_STS,
            WriteINT_STS,
            view32,
            &(bport1_ab_data.INT_STS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_INT_MASK",
            "Interrupt Mask Register",
            handles.bport1,
            0x10,
            4,
            ReadINT_MASK,
            WriteINT_MASK,
            view32,
            &(bport1_ab_data.INT_MASK.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_STATUS",
            "Status Register",
            handles.bport1,
            0x14,
            4,
            ReadSTATUS,
            WriteSTATUS,
            view32,
            &(bport1_ab_data.STATUS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DMA_SRC_ADDR",
            "DMA Source address Register",
            handles.bport1,
            0x18,
            4,
            ReadDMA_SRC_ADDR,
            WriteDMA_SRC_ADDR,
            view32,
            &(bport1_ab_data.DMA_SRC_ADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DMA_DST_ADDR",
            "DMA Destination address Register",
            handles.bport1,
            0x1c,
            4,
            ReadDMA_DST_ADDR,
            WriteDMA_DST_ADDR,
            view32,
            &(bport1_ab_data.DMA_DST_ADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DMA_SRC_LEN",
            "DMA Source transfer Length Register",
            handles.bport1,
            0x20,
            4,
            ReadDMA_SRC_LEN,
            WriteDMA_SRC_LEN,
            view32,
            &(bport1_ab_data.DMA_SRC_LEN.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DMA_DEST_LEN",
            "DMA Destination transfer Length Register",
            handles.bport1,
            0x24,
            4,
            ReadDMA_DEST_LEN,
            WriteDMA_DEST_LEN,
            view32,
            &(bport1_ab_data.DMA_DEST_LEN.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ROM_SHADOW",
            "ROM_SHADOW",
            handles.bport1,
            0x28,
            4,
            ReadROM_SHADOW,
            WriteROM_SHADOW,
            view32,
            &(bport1_ab_data.ROM_SHADOW.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MULTIBOOT_ADDR",
            "MULTI Boot Addr Pointer Register",
            handles.bport1,
            0x2c,
            4,
            ReadMULTIBOOT_ADDR,
            WriteMULTIBOOT_ADDR,
            view32,
            &(bport1_ab_data.MULTIBOOT_ADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_UNLOCK",
            "Unlock Register. The boot ROM will unlock the DEVCI by writing 0x757BDF0D to this register.",
            handles.bport1,
            0x34,
            4,
            ReadUNLOCK,
            WriteUNLOCK,
            view32,
            &(bport1_ab_data.UNLOCK.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MCTRL",
            "Miscellaneous control Register PS_VERSION=1 (v2.0 Silicon)",
            handles.bport1,
            0x80,
            4,
            ReadMCTRL,
            WriteMCTRL,
            view32,
            &(bport1_ab_data.MCTRL.value),
            True
        );
    }
    {
        registerHandle abXADCIF_CFG_reg = ppmCreateRegister(
            "ab_XADCIF_CFG",
            "XADC Interface Configuration Register",
            handles.bport1,
            0x100,
            4,
            ReadXADCIF_CFG,
            WriteXADCIF_CFG,
            view32,
            &(bport1_ab_data.XADCIF_CFG.value),
            True
        );

        ppmCreateRegisterField(abXADCIF_CFG_reg, "ENABLE", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abXADCIF_CFG_reg, "CFIFOTH", 0, 20, 4, 1, 1);
        ppmCreateRegisterField(abXADCIF_CFG_reg, "DFIFOTH", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abXADCIF_CFG_reg, "WEDGE", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abXADCIF_CFG_reg, "REDGE", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abXADCIF_CFG_reg, "TCKARTE", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abXADCIF_CFG_reg, "IGAP", 0, 0, 5, 1, 1);
    }
    {
        registerHandle abXADCIF_INT_STS_reg = ppmCreateRegister(
            "ab_XADCIF_INT_STS",
            "XADC Interface Interrupt Status Register",
            handles.bport1,
            0x104,
            4,
            ReadXADCIF_INT_STS,
            WriteXADCIF_INT_STS,
            view32,
            &(bport1_ab_data.XADCIF_INT_STS.value),
            True
        );

        ppmCreateRegisterField(abXADCIF_INT_STS_reg, "CFIFO_LTH", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abXADCIF_INT_STS_reg, "DFIFO_GTH", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abXADCIF_INT_STS_reg, "OT", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abXADCIF_INT_STS_reg, "ALM", 0, 0, 7, 1, 1);
    }
    {
        registerHandle abXADCIF_INT_MASK_reg = ppmCreateRegister(
            "ab_XADCIF_INT_MASK",
            "XADC Interface Interrupt Mask Register",
            handles.bport1,
            0x108,
            4,
            ReadXADCIF_INT_MASK,
            WriteXADCIF_INT_MASK,
            view32,
            &(bport1_ab_data.XADCIF_INT_MASK.value),
            True
        );

        ppmCreateRegisterField(abXADCIF_INT_MASK_reg, "CFIFO_LTH", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abXADCIF_INT_MASK_reg, "DFIFO_GTH", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abXADCIF_INT_MASK_reg, "OT", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abXADCIF_INT_MASK_reg, "ALM", 0, 0, 7, 1, 1);
    }
    {
        registerHandle abXADCIF_MSTS_reg = ppmCreateRegister(
            "ab_XADCIF_MSTS",
            "XADC Interface miscellaneous Status Register",
            handles.bport1,
            0x10c,
            4,
            ReadXADCIF_MSTS,
            0,
            view32,
            &(bport1_ab_data.XADCIF_MSTS.value),
            True
        );

        ppmCreateRegisterField(abXADCIF_MSTS_reg, "CFIFO_LVL", 0, 16, 4, 1, 0);
        ppmCreateRegisterField(abXADCIF_MSTS_reg, "DFIFO_LVL", 0, 12, 4, 1, 0);
        ppmCreateRegisterField(abXADCIF_MSTS_reg, "CFIFOF", 0, 11, 1, 1, 0);
        ppmCreateRegisterField(abXADCIF_MSTS_reg, "CFIFOE", 0, 10, 1, 1, 0);
        ppmCreateRegisterField(abXADCIF_MSTS_reg, "DFIFOF", 0, 9, 1, 1, 0);
        ppmCreateRegisterField(abXADCIF_MSTS_reg, "DFIFOE", 0, 8, 1, 1, 0);
        ppmCreateRegisterField(abXADCIF_MSTS_reg, "OT", 0, 7, 1, 1, 0);
        ppmCreateRegisterField(abXADCIF_MSTS_reg, "ALM", 0, 0, 6, 1, 0);
    }
    {
        registerHandle abXADCIF_CMDFIFO_reg = ppmCreateRegister(
            "ab_XADCIF_CMDFIFO",
            "XADC Interface Command FIFO Register",
            handles.bport1,
            0x110,
            4,
            0,
            WriteXADCIF_CMDFIFO,
            view32,
            &(bport1_ab_data.XADCIF_CMDFIFO.value),
            True
        );

        ppmCreateRegisterField(abXADCIF_CMDFIFO_reg, "CMD", 0, 26, 4, 0, 1);
        ppmCreateRegisterField(abXADCIF_CMDFIFO_reg, "ADDR", 0, 16, 10, 0, 1);
        ppmCreateRegisterField(abXADCIF_CMDFIFO_reg, "DATA", 0, 0, 16, 0, 1);
    }
    {
        registerHandle abXADCIF_RDFIFO_reg = ppmCreateRegister(
            "ab_XADCIF_RDFIFO",
            "XADC Interface Data FIFO Register",
            handles.bport1,
            0x114,
            4,
            ReadXADCIF_RDFIFO,
            0,
            view32,
            &(bport1_ab_data.XADCIF_RDFIFO.value),
            True
        );

        ppmCreateRegisterField(abXADCIF_RDFIFO_reg, "DATA", 0, 0, 16, 1, 0);
    }
    {
        registerHandle abXADCIF_MCTL_reg = ppmCreateRegister(
            "ab_XADCIF_MCTL",
            "XADC Interface Miscellaneous Control Register",
            handles.bport1,
            0x118,
            4,
            ReadXADCIF_MCTL,
            WriteXADCIF_MCTL,
            view32,
            &(bport1_ab_data.XADCIF_MCTL.value),
            True
        );

        ppmCreateRegisterField(abXADCIF_MCTL_reg, "RESET", 0, 4, 1, 1, 1);
    }

}

/////////////////////////////// Bus Master Ports ///////////////////////////////

static void installMasterPorts(void) {
    handles.xadc = ppmOpenAddressSpace("xadc");
}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.XADCIF_MCTL.value = (Uns32)(bport1_ab_data.XADCIF_MCTL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000010));
        bport1_ab_data.XADCIF_RDFIFO.value = (Uns32)(bport1_ab_data.XADCIF_RDFIFO.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.XADCIF_CMDFIFO.value = (Uns32)(bport1_ab_data.XADCIF_CMDFIFO.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.XADCIF_MSTS.value = (Uns32)(bport1_ab_data.XADCIF_MSTS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000500));
        bport1_ab_data.XADCIF_INT_MASK.value = (Uns32)(bport1_ab_data.XADCIF_INT_MASK.value & ~(0xffffffff)) | ((0xffffffff) & (0x3FFFFFFF));
        bport1_ab_data.XADCIF_INT_STS.value = (Uns32)(bport1_ab_data.XADCIF_INT_STS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000200));
        bport1_ab_data.XADCIF_CFG.value = (Uns32)(bport1_ab_data.XADCIF_CFG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001114));
        bport1_ab_data.MCTRL.value = (Uns32)(bport1_ab_data.MCTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x10200000));
        bport1_ab_data.UNLOCK.value = (Uns32)(bport1_ab_data.UNLOCK.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MULTIBOOT_ADDR.value = (Uns32)(bport1_ab_data.MULTIBOOT_ADDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ROM_SHADOW.value = (Uns32)(bport1_ab_data.ROM_SHADOW.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DMA_DEST_LEN.value = (Uns32)(bport1_ab_data.DMA_DEST_LEN.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DMA_SRC_LEN.value = (Uns32)(bport1_ab_data.DMA_SRC_LEN.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DMA_DST_ADDR.value = (Uns32)(bport1_ab_data.DMA_DST_ADDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DMA_SRC_ADDR.value = (Uns32)(bport1_ab_data.DMA_SRC_ADDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.STATUS.value = (Uns32)(bport1_ab_data.STATUS.value & ~(0xffffffff)) | ((0xffffffff) & (0x40000820));
        bport1_ab_data.INT_MASK.value = (Uns32)(bport1_ab_data.INT_MASK.value & ~(0xffffffff)) | ((0xffffffff) & (0xffffffff));
        bport1_ab_data.INT_STS.value = (Uns32)(bport1_ab_data.INT_STS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CFG.value = (Uns32)(bport1_ab_data.CFG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000508));
        bport1_ab_data.LOCK.value = (Uns32)(bport1_ab_data.LOCK.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CTRL.value = (Uns32)(bport1_ab_data.CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x0c006000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Zynq 7000 Platform Device Configuration Registers (devcfg)");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This is mainly a register only interface model.\n           It provides behavior to access the power rails using the XADC interface. The power rail data is provided by values stored in memory which can be updated externally.\n           It provides the ability to lock and un-lock registers.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installMasterPorts();
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


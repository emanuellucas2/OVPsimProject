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

bport1_REG_dataT bport1_REG_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "PRCI", "Example");
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

static PPM_WRITE_CB(bport1_REG_coreclksel_maskWrite) {
    bport1_REG_data.coreclksel.value = (bport1_REG_data.coreclksel.value & BPORT1_REG_CORECLKSEL_WRNMASK) | (data & BPORT1_REG_CORECLKSEL_WRMASK);
}

static PPM_WRITE_CB(bport1_REG_corepllcfg0_maskWrite) {
    bport1_REG_data.corepllcfg0.value = (bport1_REG_data.corepllcfg0.value & BPORT1_REG_COREPLLCFG0_WRNMASK) | (data & BPORT1_REG_COREPLLCFG0_WRMASK);
}

static PPM_WRITE_CB(bport1_REG_ddrpllcfg0_maskWrite) {
    bport1_REG_data.ddrpllcfg0.value = (bport1_REG_data.ddrpllcfg0.value & BPORT1_REG_DDRPLLCFG0_WRNMASK) | (data & BPORT1_REG_DDRPLLCFG0_WRMASK);
}

static PPM_WRITE_CB(bport1_REG_ddrpllcfg1_maskWrite) {
    bport1_REG_data.ddrpllcfg1.value = (bport1_REG_data.ddrpllcfg1.value & BPORT1_REG_DDRPLLCFG1_WRNMASK) | (data & BPORT1_REG_DDRPLLCFG1_WRMASK);
}

static PPM_WRITE_CB(bport1_REG_devicesresetreg_maskWrite) {
    bport1_REG_data.devicesresetreg.value = (bport1_REG_data.devicesresetreg.value & BPORT1_REG_DEVICESRESETREG_WRNMASK) | (data & BPORT1_REG_DEVICESRESETREG_WRMASK);
}

static PPM_WRITE_CB(bport1_REG_gemgxlpllcfg0_maskWrite) {
    bport1_REG_data.gemgxlpllcfg0.value = (bport1_REG_data.gemgxlpllcfg0.value & BPORT1_REG_GEMGXLPLLCFG0_WRNMASK) | (data & BPORT1_REG_GEMGXLPLLCFG0_WRMASK);
}

static PPM_WRITE_CB(bport1_REG_gemgxlpllcfg1_maskWrite) {
    bport1_REG_data.gemgxlpllcfg1.value = (bport1_REG_data.gemgxlpllcfg1.value & BPORT1_REG_GEMGXLPLLCFG1_WRNMASK) | (data & BPORT1_REG_GEMGXLPLLCFG1_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

    ppmInstallReadCallback(reservedRD, (void*)0 , handles.bport1 + 0x0, 0x1000);
    ppmInstallWriteCallback(reservedWR, (void*)0 , handles.bport1 + 0x0, 0x1000);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle REGhfxosccfg_reg = ppmCreateRegister(
            "REG_hfxosccfg",
            0,
            handles.bport1,
            0x0,
            4,
            read_32,
            hfxosccfgWrite,
            view32,
            &(bport1_REG_data.hfxosccfg.value),
            True
        );

        ppmCreateRegisterField(REGhfxosccfg_reg, "XOSC_RDY", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(REGhfxosccfg_reg, "XOSCCFG_EN", 0, 31, 1, 1, 1);
    }
    {
        registerHandle REGcorepllcfg0_reg = ppmCreateRegister(
            "REG_corepllcfg0",
            0,
            handles.bport1,
            0x4,
            4,
            read_32,
            bport1_REG_corepllcfg0_maskWrite,
            view32,
            &(bport1_REG_data.corepllcfg0.value),
            True
        );

        ppmCreateRegisterField(REGcorepllcfg0_reg, "DIVR", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(REGcorepllcfg0_reg, "DIVF", 0, 6, 9, 1, 1);
        ppmCreateRegisterField(REGcorepllcfg0_reg, "DIVQ", 0, 15, 3, 1, 1);
        ppmCreateRegisterField(REGcorepllcfg0_reg, "RANGE", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(REGcorepllcfg0_reg, "BYPASS", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(REGcorepllcfg0_reg, "FSE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(REGcorepllcfg0_reg, "LOCK", 0, 31, 1, 1, 1);
    }
    {
        registerHandle REGddrpllcfg0_reg = ppmCreateRegister(
            "REG_ddrpllcfg0",
            0,
            handles.bport1,
            0xc,
            4,
            read_32,
            bport1_REG_ddrpllcfg0_maskWrite,
            view32,
            &(bport1_REG_data.ddrpllcfg0.value),
            True
        );

        ppmCreateRegisterField(REGddrpllcfg0_reg, "DIVR", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(REGddrpllcfg0_reg, "DIVF", 0, 6, 9, 1, 1);
        ppmCreateRegisterField(REGddrpllcfg0_reg, "DIVQ", 0, 15, 3, 1, 1);
        ppmCreateRegisterField(REGddrpllcfg0_reg, "RANGE", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(REGddrpllcfg0_reg, "BYPASS", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(REGddrpllcfg0_reg, "FSE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(REGddrpllcfg0_reg, "LOCK", 0, 31, 1, 1, 1);
    }
    {
        registerHandle REGddrpllcfg1_reg = ppmCreateRegister(
            "REG_ddrpllcfg1",
            0,
            handles.bport1,
            0x10,
            4,
            read_32,
            bport1_REG_ddrpllcfg1_maskWrite,
            view32,
            &(bport1_REG_data.ddrpllcfg1.value),
            True
        );

        ppmCreateRegisterField(REGddrpllcfg1_reg, "CKE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle REGgemgxlpllcfg0_reg = ppmCreateRegister(
            "REG_gemgxlpllcfg0",
            0,
            handles.bport1,
            0x1c,
            4,
            read_32,
            bport1_REG_gemgxlpllcfg0_maskWrite,
            view32,
            &(bport1_REG_data.gemgxlpllcfg0.value),
            True
        );

        ppmCreateRegisterField(REGgemgxlpllcfg0_reg, "DIVR", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(REGgemgxlpllcfg0_reg, "DIVF", 0, 6, 9, 1, 1);
        ppmCreateRegisterField(REGgemgxlpllcfg0_reg, "DIVQ", 0, 15, 3, 1, 1);
        ppmCreateRegisterField(REGgemgxlpllcfg0_reg, "RANGE", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(REGgemgxlpllcfg0_reg, "BYPASS", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(REGgemgxlpllcfg0_reg, "FSE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(REGgemgxlpllcfg0_reg, "LOCK", 0, 31, 1, 1, 1);
    }
    {
        registerHandle REGgemgxlpllcfg1_reg = ppmCreateRegister(
            "REG_gemgxlpllcfg1",
            0,
            handles.bport1,
            0x20,
            4,
            read_32,
            bport1_REG_gemgxlpllcfg1_maskWrite,
            view32,
            &(bport1_REG_data.gemgxlpllcfg1.value),
            True
        );

        ppmCreateRegisterField(REGgemgxlpllcfg1_reg, "CKE", 0, 24, 1, 1, 1);
    }
    {
        registerHandle REGcoreclksel_reg = ppmCreateRegister(
            "REG_coreclksel",
            0,
            handles.bport1,
            0x24,
            4,
            read_32,
            bport1_REG_coreclksel_maskWrite,
            view32,
            &(bport1_REG_data.coreclksel.value),
            True
        );

        ppmCreateRegisterField(REGcoreclksel_reg, "CORECLKSEL", 0, 0, 1, 1, 1);
    }
    {
        registerHandle REGdevicesresetreg_reg = ppmCreateRegister(
            "REG_devicesresetreg",
            0,
            handles.bport1,
            0x28,
            4,
            read_32,
            bport1_REG_devicesresetreg_maskWrite,
            view32,
            &(bport1_REG_data.devicesresetreg.value),
            True
        );

        ppmCreateRegisterField(REGdevicesresetreg_reg, "DDR_CTRL_RST_N", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(REGdevicesresetreg_reg, "DDR_AXI_RST_N", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(REGdevicesresetreg_reg, "DDR_AHB_RST_N", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(REGdevicesresetreg_reg, "DDR_PHY_RST_N", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(REGdevicesresetreg_reg, "GEMGXL_RST_N", 0, 5, 1, 1, 1);
    }

}

PPM_NET_CB(reset_reset) {
    if(value != 0 ) {
        bport1_REG_data.devicesresetreg.value = (Uns32)(bport1_REG_data.devicesresetreg.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000002f));
        bport1_REG_data.coreclksel.value = (Uns32)(bport1_REG_data.coreclksel.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.gemgxlpllcfg1.value = (Uns32)(bport1_REG_data.gemgxlpllcfg1.value & ~(0xffffffff)) | ((0xffffffff) & (0x80000000));
        bport1_REG_data.gemgxlpllcfg0.value = (Uns32)(bport1_REG_data.gemgxlpllcfg0.value & ~(0xffffffff)) | ((0xffffffff) & (0x82128ec0));
        bport1_REG_data.ddrpllcfg1.value = (Uns32)(bport1_REG_data.ddrpllcfg1.value & ~(0xffffffff)) | ((0xffffffff) & (0x80000000));
        bport1_REG_data.ddrpllcfg0.value = (Uns32)(bport1_REG_data.ddrpllcfg0.value & ~(0xffffffff)) | ((0xffffffff) & (0x82110dc0));
        bport1_REG_data.corepllcfg0.value = (Uns32)(bport1_REG_data.corepllcfg0.value & ~(0xffffffff)) | ((0xffffffff) & (0x82110ec0));
        bport1_REG_data.hfxosccfg.value = (Uns32)(bport1_REG_data.hfxosccfg.value & ~(0xffffffff)) | ((0xffffffff) & (0xc0000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Power Reset Clocking Interrupt (PRCI) block for SiFive FU540 chip");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "None");
        ppmDocAddText(doc_12_node, "Register only model. Reset values based on typical post-ZSBL configuration (1GHz coreclk, 500MHz tlclk).");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_22_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "SiFive Freedom U540-C000 Manual FU540-C000-v1.0.pdf (https://www.sifive.com/documentation/chips/freedom-u540-c000-manual)");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
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


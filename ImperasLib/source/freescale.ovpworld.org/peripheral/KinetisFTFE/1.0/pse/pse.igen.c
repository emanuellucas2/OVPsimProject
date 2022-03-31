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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisFTFE", "Example");
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

static PPM_WRITE_CB(bport1_ab_FCCOB0_maskWrite) {
    bport1_ab_data.FCCOB0.value = (bport1_ab_data.FCCOB0.value & BPORT1_AB_FCCOB0_WRNMASK) | (data & BPORT1_AB_FCCOB0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FCCOB1_maskWrite) {
    bport1_ab_data.FCCOB1.value = (bport1_ab_data.FCCOB1.value & BPORT1_AB_FCCOB1_WRNMASK) | (data & BPORT1_AB_FCCOB1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FCCOB2_maskWrite) {
    bport1_ab_data.FCCOB2.value = (bport1_ab_data.FCCOB2.value & BPORT1_AB_FCCOB2_WRNMASK) | (data & BPORT1_AB_FCCOB2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FCCOB3_maskWrite) {
    bport1_ab_data.FCCOB3.value = (bport1_ab_data.FCCOB3.value & BPORT1_AB_FCCOB3_WRNMASK) | (data & BPORT1_AB_FCCOB3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FCCOB4_maskWrite) {
    bport1_ab_data.FCCOB4.value = (bport1_ab_data.FCCOB4.value & BPORT1_AB_FCCOB4_WRNMASK) | (data & BPORT1_AB_FCCOB4_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FCCOB5_maskWrite) {
    bport1_ab_data.FCCOB5.value = (bport1_ab_data.FCCOB5.value & BPORT1_AB_FCCOB5_WRNMASK) | (data & BPORT1_AB_FCCOB5_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FCCOB6_maskWrite) {
    bport1_ab_data.FCCOB6.value = (bport1_ab_data.FCCOB6.value & BPORT1_AB_FCCOB6_WRNMASK) | (data & BPORT1_AB_FCCOB6_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FCCOB7_maskWrite) {
    bport1_ab_data.FCCOB7.value = (bport1_ab_data.FCCOB7.value & BPORT1_AB_FCCOB7_WRNMASK) | (data & BPORT1_AB_FCCOB7_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FCCOB8_maskWrite) {
    bport1_ab_data.FCCOB8.value = (bport1_ab_data.FCCOB8.value & BPORT1_AB_FCCOB8_WRNMASK) | (data & BPORT1_AB_FCCOB8_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FCCOB9_maskWrite) {
    bport1_ab_data.FCCOB9.value = (bport1_ab_data.FCCOB9.value & BPORT1_AB_FCCOB9_WRNMASK) | (data & BPORT1_AB_FCCOB9_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FCCOBA_maskWrite) {
    bport1_ab_data.FCCOBA.value = (bport1_ab_data.FCCOBA.value & BPORT1_AB_FCCOBA_WRNMASK) | (data & BPORT1_AB_FCCOBA_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FCCOBB_maskWrite) {
    bport1_ab_data.FCCOBB.value = (bport1_ab_data.FCCOBB.value & BPORT1_AB_FCCOBB_WRNMASK) | (data & BPORT1_AB_FCCOBB_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FCNFG_maskWrite) {
    bport1_ab_data.FCNFG.value = (bport1_ab_data.FCNFG.value & BPORT1_AB_FCNFG_WRNMASK) | (data & BPORT1_AB_FCNFG_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FDPROT_maskWrite) {
    bport1_ab_data.FDPROT.value = (bport1_ab_data.FDPROT.value & BPORT1_AB_FDPROT_WRNMASK) | (data & BPORT1_AB_FDPROT_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FEPROT_maskWrite) {
    bport1_ab_data.FEPROT.value = (bport1_ab_data.FEPROT.value & BPORT1_AB_FEPROT_WRNMASK) | (data & BPORT1_AB_FEPROT_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FPROT0_maskWrite) {
    bport1_ab_data.FPROT0.value = (bport1_ab_data.FPROT0.value & BPORT1_AB_FPROT0_WRNMASK) | (data & BPORT1_AB_FPROT0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FPROT1_maskWrite) {
    bport1_ab_data.FPROT1.value = (bport1_ab_data.FPROT1.value & BPORT1_AB_FPROT1_WRNMASK) | (data & BPORT1_AB_FPROT1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FPROT2_maskWrite) {
    bport1_ab_data.FPROT2.value = (bport1_ab_data.FPROT2.value & BPORT1_AB_FPROT2_WRNMASK) | (data & BPORT1_AB_FPROT2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FPROT3_maskWrite) {
    bport1_ab_data.FPROT3.value = (bport1_ab_data.FPROT3.value & BPORT1_AB_FPROT3_WRNMASK) | (data & BPORT1_AB_FPROT3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FSTAT_maskWrite) {
    bport1_ab_data.FSTAT.value = (bport1_ab_data.FSTAT.value & BPORT1_AB_FSTAT_WRNMASK) | (data & BPORT1_AB_FSTAT_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abFSTAT_reg = ppmCreateRegister(
            "ab_FSTAT",
            "Flash Status Register, offset: 0x0 ",
            handles.bport1,
            0x0,
            1,
            read_8,
            bport1_ab_FSTAT_maskWrite,
            view8,
            &(bport1_ab_data.FSTAT.value),
            True
        );

        ppmCreateRegisterField(abFSTAT_reg, "ACCERR", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abFSTAT_reg, "CCIF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abFSTAT_reg, "FPVIOL", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abFSTAT_reg, "MGSTAT0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abFSTAT_reg, "RDCOLERR", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abFCNFG_reg = ppmCreateRegister(
            "ab_FCNFG",
            "Flash Configuration Register, offset: 0x1 ",
            handles.bport1,
            0x1,
            1,
            read_8,
            bport1_ab_FCNFG_maskWrite,
            view8,
            &(bport1_ab_data.FCNFG.value),
            True
        );

        ppmCreateRegisterField(abFCNFG_reg, "CCIE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abFCNFG_reg, "EEERDY", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abFCNFG_reg, "ERSAREQ", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abFCNFG_reg, "ERSSUSP", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abFCNFG_reg, "PFLSH", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abFCNFG_reg, "RAMRDY", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abFCNFG_reg, "RDCOLLIE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abFCNFG_reg, "SWAP", 0, 3, 1, 1, 1);
    }
    {
        registerHandle abFSEC_reg = ppmCreateRegister(
            "ab_FSEC",
            "Flash Security Register, offset: 0x2 ",
            handles.bport1,
            0x2,
            1,
            read_8,
            0,
            view8,
            &(bport1_ab_data.FSEC.value),
            True
        );

        ppmCreateRegisterField(abFSEC_reg, "FSLACC", 0, 2, 2, 1, 0);
        ppmCreateRegisterField(abFSEC_reg, "KEYEN", 0, 6, 2, 1, 0);
        ppmCreateRegisterField(abFSEC_reg, "MEEN", 0, 4, 2, 1, 0);
        ppmCreateRegisterField(abFSEC_reg, "SEC", 0, 0, 2, 1, 0);
    }
    {
        registerHandle abFOPT_reg = ppmCreateRegister(
            "ab_FOPT",
            "Flash Option Register, offset: 0x3 ",
            handles.bport1,
            0x3,
            1,
            read_8,
            0,
            view8,
            &(bport1_ab_data.FOPT.value),
            True
        );

        ppmCreateRegisterField(abFOPT_reg, "OPT", 0, 0, 8, 1, 0);
    }
    {
        registerHandle abFCCOB3_reg = ppmCreateRegister(
            "ab_FCCOB3",
            "Flash Common Command Object Registers, offset: 0x4 ",
            handles.bport1,
            0x4,
            1,
            read_8,
            bport1_ab_FCCOB3_maskWrite,
            view8,
            &(bport1_ab_data.FCCOB3.value),
            True
        );

        ppmCreateRegisterField(abFCCOB3_reg, "CCOBn", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abFCCOB2_reg = ppmCreateRegister(
            "ab_FCCOB2",
            "Flash Common Command Object Registers, offset: 0x5 ",
            handles.bport1,
            0x5,
            1,
            read_8,
            bport1_ab_FCCOB2_maskWrite,
            view8,
            &(bport1_ab_data.FCCOB2.value),
            True
        );

        ppmCreateRegisterField(abFCCOB2_reg, "CCOBn", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abFCCOB1_reg = ppmCreateRegister(
            "ab_FCCOB1",
            "Flash Common Command Object Registers, offset: 0x6 ",
            handles.bport1,
            0x6,
            1,
            read_8,
            bport1_ab_FCCOB1_maskWrite,
            view8,
            &(bport1_ab_data.FCCOB1.value),
            True
        );

        ppmCreateRegisterField(abFCCOB1_reg, "CCOBn", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abFCCOB0_reg = ppmCreateRegister(
            "ab_FCCOB0",
            "Flash Common Command Object Registers, offset: 0x7 ",
            handles.bport1,
            0x7,
            1,
            read_8,
            bport1_ab_FCCOB0_maskWrite,
            view8,
            &(bport1_ab_data.FCCOB0.value),
            True
        );

        ppmCreateRegisterField(abFCCOB0_reg, "CCOBn", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abFCCOB7_reg = ppmCreateRegister(
            "ab_FCCOB7",
            "Flash Common Command Object Registers, offset: 0x8 ",
            handles.bport1,
            0x8,
            1,
            read_8,
            bport1_ab_FCCOB7_maskWrite,
            view8,
            &(bport1_ab_data.FCCOB7.value),
            True
        );

        ppmCreateRegisterField(abFCCOB7_reg, "CCOBn", 0, 0, 8, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_FCCOB6",
            "Flash Common Command Object Registers, offset: 0x9 ",
            handles.bport1,
            0x9,
            1,
            read_8,
            bport1_ab_FCCOB6_maskWrite,
            view8,
            &(bport1_ab_data.FCCOB6.value),
            True
        );
    }
    {
        registerHandle abFCCOB5_reg = ppmCreateRegister(
            "ab_FCCOB5",
            "Flash Common Command Object Registers, offset: 0xA ",
            handles.bport1,
            0xa,
            1,
            read_8,
            bport1_ab_FCCOB5_maskWrite,
            view8,
            &(bport1_ab_data.FCCOB5.value),
            True
        );

        ppmCreateRegisterField(abFCCOB5_reg, "CCOBn", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abFCCOB4_reg = ppmCreateRegister(
            "ab_FCCOB4",
            "Flash Common Command Object Registers, offset: 0xB ",
            handles.bport1,
            0xb,
            1,
            read_8,
            bport1_ab_FCCOB4_maskWrite,
            view8,
            &(bport1_ab_data.FCCOB4.value),
            True
        );

        ppmCreateRegisterField(abFCCOB4_reg, "CCOBn", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abFCCOBB_reg = ppmCreateRegister(
            "ab_FCCOBB",
            "Flash Common Command Object Registers, offset: 0xC ",
            handles.bport1,
            0xc,
            1,
            read_8,
            bport1_ab_FCCOBB_maskWrite,
            view8,
            &(bport1_ab_data.FCCOBB.value),
            True
        );

        ppmCreateRegisterField(abFCCOBB_reg, "CCOBn", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abFCCOBA_reg = ppmCreateRegister(
            "ab_FCCOBA",
            "Flash Common Command Object Registers, offset: 0xD ",
            handles.bport1,
            0xd,
            1,
            read_8,
            bport1_ab_FCCOBA_maskWrite,
            view8,
            &(bport1_ab_data.FCCOBA.value),
            True
        );

        ppmCreateRegisterField(abFCCOBA_reg, "CCOBn", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abFCCOB9_reg = ppmCreateRegister(
            "ab_FCCOB9",
            "Flash Common Command Object Registers, offset: 0xE ",
            handles.bport1,
            0xe,
            1,
            read_8,
            bport1_ab_FCCOB9_maskWrite,
            view8,
            &(bport1_ab_data.FCCOB9.value),
            True
        );

        ppmCreateRegisterField(abFCCOB9_reg, "CCOBn", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abFCCOB8_reg = ppmCreateRegister(
            "ab_FCCOB8",
            "Flash Common Command Object Registers, offset: 0xF ",
            handles.bport1,
            0xf,
            1,
            read_8,
            bport1_ab_FCCOB8_maskWrite,
            view8,
            &(bport1_ab_data.FCCOB8.value),
            True
        );

        ppmCreateRegisterField(abFCCOB8_reg, "CCOBn", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abFPROT3_reg = ppmCreateRegister(
            "ab_FPROT3",
            "Program Flash Protection Registers, offset: 0x10 ",
            handles.bport1,
            0x10,
            1,
            read_8,
            bport1_ab_FPROT3_maskWrite,
            view8,
            &(bport1_ab_data.FPROT3.value),
            True
        );

        ppmCreateRegisterField(abFPROT3_reg, "PROT", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abFPROT2_reg = ppmCreateRegister(
            "ab_FPROT2",
            "Program Flash Protection Registers, offset: 0x11 ",
            handles.bport1,
            0x11,
            1,
            read_8,
            bport1_ab_FPROT2_maskWrite,
            view8,
            &(bport1_ab_data.FPROT2.value),
            True
        );

        ppmCreateRegisterField(abFPROT2_reg, "PROT", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abFPROT1_reg = ppmCreateRegister(
            "ab_FPROT1",
            "Program Flash Protection Registers, offset: 0x12 ",
            handles.bport1,
            0x12,
            1,
            read_8,
            bport1_ab_FPROT1_maskWrite,
            view8,
            &(bport1_ab_data.FPROT1.value),
            True
        );

        ppmCreateRegisterField(abFPROT1_reg, "PROT", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abFPROT0_reg = ppmCreateRegister(
            "ab_FPROT0",
            "Program Flash Protection Registers, offset: 0x13 ",
            handles.bport1,
            0x13,
            1,
            read_8,
            bport1_ab_FPROT0_maskWrite,
            view8,
            &(bport1_ab_data.FPROT0.value),
            True
        );

        ppmCreateRegisterField(abFPROT0_reg, "PROT", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abFEPROT_reg = ppmCreateRegister(
            "ab_FEPROT",
            "EEPROM Protection Register, offset: 0x16 ",
            handles.bport1,
            0x16,
            1,
            read_8,
            bport1_ab_FEPROT_maskWrite,
            view8,
            &(bport1_ab_data.FEPROT.value),
            True
        );

        ppmCreateRegisterField(abFEPROT_reg, "EPROT", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abFDPROT_reg = ppmCreateRegister(
            "ab_FDPROT",
            "Data Flash Protection Register, offset: 0x17 ",
            handles.bport1,
            0x17,
            1,
            read_8,
            bport1_ab_FDPROT_maskWrite,
            view8,
            &(bport1_ab_data.FDPROT.value),
            True
        );

        ppmCreateRegisterField(abFDPROT_reg, "DPROT", 0, 0, 8, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.FCCOB8.value = (Uns8)(bport1_ab_data.FCCOB8.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.FCCOB9.value = (Uns8)(bport1_ab_data.FCCOB9.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.FCCOBA.value = (Uns8)(bport1_ab_data.FCCOBA.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.FCCOBB.value = (Uns8)(bport1_ab_data.FCCOBB.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.FCCOB4.value = (Uns8)(bport1_ab_data.FCCOB4.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.FCCOB5.value = (Uns8)(bport1_ab_data.FCCOB5.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.FCCOB6.value = (Uns8)(bport1_ab_data.FCCOB6.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.FCCOB7.value = (Uns8)(bport1_ab_data.FCCOB7.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.FCCOB0.value = (Uns8)(bport1_ab_data.FCCOB0.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.FCCOB1.value = (Uns8)(bport1_ab_data.FCCOB1.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.FCCOB2.value = (Uns8)(bport1_ab_data.FCCOB2.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.FCCOB3.value = (Uns8)(bport1_ab_data.FCCOB3.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.FCNFG.value = (Uns8)(bport1_ab_data.FCNFG.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.FSTAT.value = (Uns8)(bport1_ab_data.FSTAT.value & ~(0xff)) | ((0xff) & (0x00));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the FTFE peripheral used on the Freescale Kinetis platform");
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


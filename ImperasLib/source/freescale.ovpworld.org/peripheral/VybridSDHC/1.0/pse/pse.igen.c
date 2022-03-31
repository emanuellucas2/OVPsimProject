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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "VybridSDHC", "Example");
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

static PPM_WRITE_CB(bport1_ab_ADSADDR_maskWrite) {
    bport1_ab_data.ADSADDR.value = (bport1_ab_data.ADSADDR.value & BPORT1_AB_ADSADDR_WRNMASK) | (data & BPORT1_AB_ADSADDR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_BLKATTR_maskWrite) {
    bport1_ab_data.BLKATTR.value = (bport1_ab_data.BLKATTR.value & BPORT1_AB_BLKATTR_WRNMASK) | (data & BPORT1_AB_BLKATTR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CMDARG_maskWrite) {
    bport1_ab_data.CMDARG.value = (bport1_ab_data.CMDARG.value & BPORT1_AB_CMDARG_WRNMASK) | (data & BPORT1_AB_CMDARG_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DATPORT_maskWrite) {
    bport1_ab_data.DATPORT.value = (bport1_ab_data.DATPORT.value & BPORT1_AB_DATPORT_WRNMASK) | (data & BPORT1_AB_DATPORT_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DSADDR_maskWrite) {
    bport1_ab_data.DSADDR.value = (bport1_ab_data.DSADDR.value & BPORT1_AB_DSADDR_WRNMASK) | (data & BPORT1_AB_DSADDR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FEVT_maskWrite) {
    bport1_ab_data.FEVT.value = (bport1_ab_data.FEVT.value & BPORT1_AB_FEVT_WRNMASK) | (data & BPORT1_AB_FEVT_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_IRQSIGEN_maskWrite) {
    bport1_ab_data.IRQSIGEN.value = (bport1_ab_data.IRQSIGEN.value & BPORT1_AB_IRQSIGEN_WRNMASK) | (data & BPORT1_AB_IRQSIGEN_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_IRQSTATEN_maskWrite) {
    bport1_ab_data.IRQSTATEN.value = (bport1_ab_data.IRQSTATEN.value & BPORT1_AB_IRQSTATEN_WRNMASK) | (data & BPORT1_AB_IRQSTATEN_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_IRQSTAT_maskWrite) {
    bport1_ab_data.IRQSTAT.value = (bport1_ab_data.IRQSTAT.value & BPORT1_AB_IRQSTAT_WRNMASK) | (data & BPORT1_AB_IRQSTAT_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MMCBOOT_maskWrite) {
    bport1_ab_data.MMCBOOT.value = (bport1_ab_data.MMCBOOT.value & BPORT1_AB_MMCBOOT_WRNMASK) | (data & BPORT1_AB_MMCBOOT_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PROCTL_maskWrite) {
    bport1_ab_data.PROCTL.value = (bport1_ab_data.PROCTL.value & BPORT1_AB_PROCTL_WRNMASK) | (data & BPORT1_AB_PROCTL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SYSCTL_maskWrite) {
    bport1_ab_data.SYSCTL.value = (bport1_ab_data.SYSCTL.value & BPORT1_AB_SYSCTL_WRNMASK) | (data & BPORT1_AB_SYSCTL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_VENDOR_maskWrite) {
    bport1_ab_data.VENDOR.value = (bport1_ab_data.VENDOR.value & BPORT1_AB_VENDOR_WRNMASK) | (data & BPORT1_AB_VENDOR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_WML_maskWrite) {
    bport1_ab_data.WML.value = (bport1_ab_data.WML.value & BPORT1_AB_WML_WRNMASK) | (data & BPORT1_AB_WML_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_XFERTYP_maskWrite) {
    bport1_ab_data.XFERTYP.value = (bport1_ab_data.XFERTYP.value & BPORT1_AB_XFERTYP_WRNMASK) | (data & BPORT1_AB_XFERTYP_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abDSADDR_reg = ppmCreateRegister(
            "ab_DSADDR",
            "DMA System Address Register, offset: 0x0 ",
            handles.bport1,
            0x0,
            4,
            read_32,
            bport1_ab_DSADDR_maskWrite,
            view32,
            &(bport1_ab_data.DSADDR.value),
            True
        );

        ppmCreateRegisterField(abDSADDR_reg, "DSADDR", 0, 2, 30, 1, 1);
    }
    {
        registerHandle abBLKATTR_reg = ppmCreateRegister(
            "ab_BLKATTR",
            "Block Attributes Register, offset: 0x4 ",
            handles.bport1,
            0x4,
            4,
            read_32,
            bport1_ab_BLKATTR_maskWrite,
            view32,
            &(bport1_ab_data.BLKATTR.value),
            True
        );

        ppmCreateRegisterField(abBLKATTR_reg, "BLKCNT", 0, 16, 16, 1, 1);
        ppmCreateRegisterField(abBLKATTR_reg, "BLKSIZE", 0, 0, 13, 1, 1);
    }
    {
        registerHandle abCMDARG_reg = ppmCreateRegister(
            "ab_CMDARG",
            "Command Argument Register, offset: 0x8 ",
            handles.bport1,
            0x8,
            4,
            read_32,
            bport1_ab_CMDARG_maskWrite,
            view32,
            &(bport1_ab_data.CMDARG.value),
            True
        );

        ppmCreateRegisterField(abCMDARG_reg, "CMDARG", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abXFERTYP_reg = ppmCreateRegister(
            "ab_XFERTYP",
            "Transfer Type Register, offset: 0xC ",
            handles.bport1,
            0xc,
            4,
            read_32,
            bport1_ab_XFERTYP_maskWrite,
            view32,
            &(bport1_ab_data.XFERTYP.value),
            True
        );

        ppmCreateRegisterField(abXFERTYP_reg, "AC12EN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abXFERTYP_reg, "BCEN", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abXFERTYP_reg, "CCCEN", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abXFERTYP_reg, "CICEN", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abXFERTYP_reg, "CMDINX", 0, 24, 6, 1, 1);
        ppmCreateRegisterField(abXFERTYP_reg, "CMDTYP", 0, 22, 2, 1, 1);
        ppmCreateRegisterField(abXFERTYP_reg, "DMAEN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abXFERTYP_reg, "DPSEL", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abXFERTYP_reg, "DTDSEL", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abXFERTYP_reg, "MSBSEL", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abXFERTYP_reg, "RSPTYP", 0, 16, 2, 1, 1);
    }
    {
        registerHandle abCMDRSP0_reg = ppmCreateRegister(
            "ab_CMDRSP0",
            "Command Response 0, offset: 0x10, array step: 0x4 ",
            handles.bport1,
            0x10,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.CMDRSP0.value),
            True
        );

        ppmCreateRegisterField(abCMDRSP0_reg, "CMDRSP0", 0, 0, 32, 1, 0);
    }
    {
        registerHandle abCMDRSP1_reg = ppmCreateRegister(
            "ab_CMDRSP1",
            "Command Response 1, offset: 0x10, array step: 0x4 ",
            handles.bport1,
            0x14,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.CMDRSP1.value),
            True
        );

        ppmCreateRegisterField(abCMDRSP1_reg, "CMDRSP1", 0, 0, 32, 1, 0);
    }
    {
        registerHandle abCMDRSP2_reg = ppmCreateRegister(
            "ab_CMDRSP2",
            "Command Response 2, offset: 0x10, array step: 0x4 ",
            handles.bport1,
            0x18,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.CMDRSP2.value),
            True
        );

        ppmCreateRegisterField(abCMDRSP2_reg, "CMDRSP2", 0, 0, 32, 1, 0);
    }
    {
        registerHandle abCMDRSP3_reg = ppmCreateRegister(
            "ab_CMDRSP3",
            "Command Response 3, offset: 0x10, array step: 0x4 ",
            handles.bport1,
            0x1c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.CMDRSP3.value),
            True
        );

        ppmCreateRegisterField(abCMDRSP3_reg, "CMDRSP3", 0, 0, 32, 1, 0);
    }
    {
        registerHandle abDATPORT_reg = ppmCreateRegister(
            "ab_DATPORT",
            "Buffer Data Port Register, offset: 0x20 ",
            handles.bport1,
            0x20,
            4,
            read_32,
            bport1_ab_DATPORT_maskWrite,
            view32,
            &(bport1_ab_data.DATPORT.value),
            True
        );

        ppmCreateRegisterField(abDATPORT_reg, "DATCONT", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abPRSSTAT_reg = ppmCreateRegister(
            "ab_PRSSTAT",
            "Present State Register, offset: 0x24 ",
            handles.bport1,
            0x24,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.PRSSTAT.value),
            True
        );

        ppmCreateRegisterField(abPRSSTAT_reg, "BREN", 0, 11, 1, 1, 0);
        ppmCreateRegisterField(abPRSSTAT_reg, "BWEN", 0, 10, 1, 1, 0);
        ppmCreateRegisterField(abPRSSTAT_reg, "CDIHB", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(abPRSSTAT_reg, "CDPL", 0, 18, 1, 1, 0);
        ppmCreateRegisterField(abPRSSTAT_reg, "CIHB", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(abPRSSTAT_reg, "CINS", 0, 16, 1, 1, 0);
        ppmCreateRegisterField(abPRSSTAT_reg, "CLSL", 0, 23, 1, 1, 0);
        ppmCreateRegisterField(abPRSSTAT_reg, "DLA", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(abPRSSTAT_reg, "DLSL", 0, 24, 8, 1, 0);
        ppmCreateRegisterField(abPRSSTAT_reg, "HCKOFF", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(abPRSSTAT_reg, "IPGOFF", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(abPRSSTAT_reg, "PEROFF", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(abPRSSTAT_reg, "RTA", 0, 9, 1, 1, 0);
        ppmCreateRegisterField(abPRSSTAT_reg, "SDOFF", 0, 7, 1, 1, 0);
        ppmCreateRegisterField(abPRSSTAT_reg, "SDSTB", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(abPRSSTAT_reg, "WPSPL", 0, 19, 1, 1, 0);
        ppmCreateRegisterField(abPRSSTAT_reg, "WTA", 0, 8, 1, 1, 0);
    }
    {
        registerHandle abPROCTL_reg = ppmCreateRegister(
            "ab_PROCTL",
            "Protocol Control Register, offset: 0x28 ",
            handles.bport1,
            0x28,
            4,
            read_32,
            bport1_ab_PROCTL_maskWrite,
            view32,
            &(bport1_ab_data.PROCTL.value),
            True
        );

        ppmCreateRegisterField(abPROCTL_reg, "CDSS", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abPROCTL_reg, "CDTL", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPROCTL_reg, "CREQ", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abPROCTL_reg, "D3CD", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abPROCTL_reg, "DMAS", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abPROCTL_reg, "DTW", 0, 1, 2, 1, 1);
        ppmCreateRegisterField(abPROCTL_reg, "EMODE", 0, 4, 2, 1, 1);
        ppmCreateRegisterField(abPROCTL_reg, "IABG", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abPROCTL_reg, "LCTL", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPROCTL_reg, "RWCTL", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abPROCTL_reg, "SABGREQ", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abPROCTL_reg, "WECINS", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abPROCTL_reg, "WECINT", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPROCTL_reg, "WECRM", 0, 26, 1, 1, 1);
    }
    {
        registerHandle abSYSCTL_reg = ppmCreateRegister(
            "ab_SYSCTL",
            "System Control Register, offset: 0x2C ",
            handles.bport1,
            0x2c,
            4,
            read_32,
            bport1_ab_SYSCTL_maskWrite,
            view32,
            &(bport1_ab_data.SYSCTL.value),
            True
        );

        ppmCreateRegisterField(abSYSCTL_reg, "DTOCV", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abSYSCTL_reg, "DVS", 0, 4, 4, 1, 1);
        ppmCreateRegisterField(abSYSCTL_reg, "HCKEN", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abSYSCTL_reg, "INITA", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(abSYSCTL_reg, "IPGEN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abSYSCTL_reg, "PEREN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abSYSCTL_reg, "RSTA", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abSYSCTL_reg, "RSTC", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abSYSCTL_reg, "RSTD", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abSYSCTL_reg, "SDCLKEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abSYSCTL_reg, "SDCLKFS", 0, 8, 8, 1, 1);
    }
    {
        registerHandle abIRQSTAT_reg = ppmCreateRegister(
            "ab_IRQSTAT",
            "Interrupt Status Register, offset: 0x30 ",
            handles.bport1,
            0x30,
            4,
            read_32,
            bport1_ab_IRQSTAT_maskWrite,
            view32,
            &(bport1_ab_data.IRQSTAT.value),
            True
        );

        ppmCreateRegisterField(abIRQSTAT_reg, "AC12E", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTAT_reg, "BGE", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTAT_reg, "BRR", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTAT_reg, "BWR", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTAT_reg, "CC", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTAT_reg, "CCE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTAT_reg, "CEBE", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTAT_reg, "CIE", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTAT_reg, "CINS", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTAT_reg, "CINT", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTAT_reg, "CRM", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTAT_reg, "CTOE", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTAT_reg, "DCE", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTAT_reg, "DEBE", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTAT_reg, "DINT", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTAT_reg, "DMAE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTAT_reg, "DTOE", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTAT_reg, "TC", 0, 1, 1, 1, 1);
    }
    {
        registerHandle abIRQSTATEN_reg = ppmCreateRegister(
            "ab_IRQSTATEN",
            "Interrupt Status Enable Register, offset: 0x34 ",
            handles.bport1,
            0x34,
            4,
            read_32,
            bport1_ab_IRQSTATEN_maskWrite,
            view32,
            &(bport1_ab_data.IRQSTATEN.value),
            True
        );

        ppmCreateRegisterField(abIRQSTATEN_reg, "AC12ESEN", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTATEN_reg, "BGESEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTATEN_reg, "BRRSEN", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTATEN_reg, "BWRSEN", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTATEN_reg, "CCESEN", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTATEN_reg, "CCSEN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTATEN_reg, "CEBESEN", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTATEN_reg, "CIESEN", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTATEN_reg, "CINSEN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTATEN_reg, "CINTSEN", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTATEN_reg, "CRMSEN", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTATEN_reg, "CTOESEN", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTATEN_reg, "DCESEN", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTATEN_reg, "DEBESEN", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTATEN_reg, "DINTSEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTATEN_reg, "DMAESEN", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTATEN_reg, "DTOESEN", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abIRQSTATEN_reg, "TCSEN", 0, 1, 1, 1, 1);
    }
    {
        registerHandle abIRQSIGEN_reg = ppmCreateRegister(
            "ab_IRQSIGEN",
            "Interrupt Signal Enable Register, offset: 0x38 ",
            handles.bport1,
            0x38,
            4,
            read_32,
            bport1_ab_IRQSIGEN_maskWrite,
            view32,
            &(bport1_ab_data.IRQSIGEN.value),
            True
        );

        ppmCreateRegisterField(abIRQSIGEN_reg, "AC12EIEN", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abIRQSIGEN_reg, "BGEIEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abIRQSIGEN_reg, "BRRIEN", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abIRQSIGEN_reg, "BWRIEN", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abIRQSIGEN_reg, "CCEIEN", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abIRQSIGEN_reg, "CCIEN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abIRQSIGEN_reg, "CEBEIEN", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abIRQSIGEN_reg, "CIEIEN", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abIRQSIGEN_reg, "CINSIEN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abIRQSIGEN_reg, "CINTIEN", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abIRQSIGEN_reg, "CRMIEN", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abIRQSIGEN_reg, "CTOEIEN", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abIRQSIGEN_reg, "DCEIEN", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abIRQSIGEN_reg, "DEBEIEN", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abIRQSIGEN_reg, "DINTIEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abIRQSIGEN_reg, "DMAEIEN", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abIRQSIGEN_reg, "DTOEIEN", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abIRQSIGEN_reg, "TCIEN", 0, 1, 1, 1, 1);
    }
    {
        registerHandle abAC12ERR_reg = ppmCreateRegister(
            "ab_AC12ERR",
            "Auto CMD12 Error Status Register, offset: 0x3C ",
            handles.bport1,
            0x3c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.AC12ERR.value),
            True
        );

        ppmCreateRegisterField(abAC12ERR_reg, "AC12CE", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(abAC12ERR_reg, "AC12EBE", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(abAC12ERR_reg, "AC12IE", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(abAC12ERR_reg, "AC12NE", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(abAC12ERR_reg, "AC12TOE", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(abAC12ERR_reg, "CNIBAC12E", 0, 7, 1, 1, 0);
    }
    {
        registerHandle abHTCAPBLT_reg = ppmCreateRegister(
            "ab_HTCAPBLT",
            "Host Controller Capabilities, offset: 0x40 ",
            handles.bport1,
            0x40,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.HTCAPBLT.value),
            True
        );

        ppmCreateRegisterField(abHTCAPBLT_reg, "ADMAS", 0, 20, 1, 1, 0);
        ppmCreateRegisterField(abHTCAPBLT_reg, "DMAS", 0, 22, 1, 1, 0);
        ppmCreateRegisterField(abHTCAPBLT_reg, "HSS", 0, 21, 1, 1, 0);
        ppmCreateRegisterField(abHTCAPBLT_reg, "MBL", 0, 16, 3, 1, 0);
        ppmCreateRegisterField(abHTCAPBLT_reg, "SRS", 0, 23, 1, 1, 0);
        ppmCreateRegisterField(abHTCAPBLT_reg, "VS33", 0, 24, 1, 1, 0);
    }
    {
        registerHandle abWML_reg = ppmCreateRegister(
            "ab_WML",
            "Watermark Level Register, offset: 0x44 ",
            handles.bport1,
            0x44,
            4,
            read_32,
            bport1_ab_WML_maskWrite,
            view32,
            &(bport1_ab_data.WML.value),
            True
        );

        ppmCreateRegisterField(abWML_reg, "RDWML", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abWML_reg, "RDBRSTLEN", 0, 8, 5, 1, 1);
        ppmCreateRegisterField(abWML_reg, "WRWML", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abWML_reg, "WRBRSTLEN", 0, 24, 5, 1, 1);
    }
    {
        registerHandle abFEVT_reg = ppmCreateRegister(
            "ab_FEVT",
            "Force Event Register, offset: 0x50 ",
            handles.bport1,
            0x50,
            4,
            0,
            bport1_ab_FEVT_maskWrite,
            view32,
            &(bport1_ab_data.FEVT.value),
            True
        );

        ppmCreateRegisterField(abFEVT_reg, "AC12CE", 0, 2, 1, 0, 1);
        ppmCreateRegisterField(abFEVT_reg, "AC12E", 0, 24, 1, 0, 1);
        ppmCreateRegisterField(abFEVT_reg, "AC12EBE", 0, 3, 1, 0, 1);
        ppmCreateRegisterField(abFEVT_reg, "AC12IE", 0, 4, 1, 0, 1);
        ppmCreateRegisterField(abFEVT_reg, "AC12NE", 0, 0, 1, 0, 1);
        ppmCreateRegisterField(abFEVT_reg, "AC12TOE", 0, 1, 1, 0, 1);
        ppmCreateRegisterField(abFEVT_reg, "CCE", 0, 17, 1, 0, 1);
        ppmCreateRegisterField(abFEVT_reg, "CEBE", 0, 18, 1, 0, 1);
        ppmCreateRegisterField(abFEVT_reg, "CIE", 0, 19, 1, 0, 1);
        ppmCreateRegisterField(abFEVT_reg, "CINT", 0, 31, 1, 0, 1);
        ppmCreateRegisterField(abFEVT_reg, "CNIBAC12E", 0, 7, 1, 0, 1);
        ppmCreateRegisterField(abFEVT_reg, "CTOE", 0, 16, 1, 0, 1);
        ppmCreateRegisterField(abFEVT_reg, "DCE", 0, 21, 1, 0, 1);
        ppmCreateRegisterField(abFEVT_reg, "DEBE", 0, 22, 1, 0, 1);
        ppmCreateRegisterField(abFEVT_reg, "DMAE", 0, 28, 1, 0, 1);
        ppmCreateRegisterField(abFEVT_reg, "DTOE", 0, 20, 1, 0, 1);
    }
    {
        registerHandle abADMAES_reg = ppmCreateRegister(
            "ab_ADMAES",
            "ADMA Error Status Register, offset: 0x54 ",
            handles.bport1,
            0x54,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.ADMAES.value),
            True
        );

        ppmCreateRegisterField(abADMAES_reg, "ADMADCE", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(abADMAES_reg, "ADMAES", 0, 0, 2, 1, 0);
        ppmCreateRegisterField(abADMAES_reg, "ADMALME", 0, 2, 1, 1, 0);
    }
    {
        registerHandle abADSADDR_reg = ppmCreateRegister(
            "ab_ADSADDR",
            "ADMA System Address Register, offset: 0x58 ",
            handles.bport1,
            0x58,
            4,
            read_32,
            bport1_ab_ADSADDR_maskWrite,
            view32,
            &(bport1_ab_data.ADSADDR.value),
            True
        );

        ppmCreateRegisterField(abADSADDR_reg, "ADSADDR", 0, 2, 30, 1, 1);
    }
    {
        registerHandle abVENDOR_reg = ppmCreateRegister(
            "ab_VENDOR",
            "Vendor Specific Register, offset: 0xC0 ",
            handles.bport1,
            0xc0,
            4,
            read_32,
            bport1_ab_VENDOR_maskWrite,
            view32,
            &(bport1_ab_data.VENDOR.value),
            True
        );

        ppmCreateRegisterField(abVENDOR_reg, "EXBLKNU", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abVENDOR_reg, "INTSTVAL", 0, 16, 8, 1, 1);
    }
    {
        registerHandle abMMCBOOT_reg = ppmCreateRegister(
            "ab_MMCBOOT",
            "MMC Boot Register, offset: 0xC4 ",
            handles.bport1,
            0xc4,
            4,
            read_32,
            bport1_ab_MMCBOOT_maskWrite,
            view32,
            &(bport1_ab_data.MMCBOOT.value),
            True
        );

        ppmCreateRegisterField(abMMCBOOT_reg, "AUTOSABGEN", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abMMCBOOT_reg, "BOOTACK", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abMMCBOOT_reg, "BOOTBLKCNT", 0, 16, 16, 1, 1);
        ppmCreateRegisterField(abMMCBOOT_reg, "BOOTEN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abMMCBOOT_reg, "BOOTMODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abMMCBOOT_reg, "DTOCVACK", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abHOSTVER_reg = ppmCreateRegister(
            "ab_HOSTVER",
            "Host Controller Version, offset: 0xFC ",
            handles.bport1,
            0xfc,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.HOSTVER.value),
            True
        );

        ppmCreateRegisterField(abHOSTVER_reg, "SVN", 0, 0, 8, 1, 0);
        ppmCreateRegisterField(abHOSTVER_reg, "VVN", 0, 8, 8, 1, 0);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.HOSTVER.value = (Uns32)(bport1_ab_data.HOSTVER.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001201));
        bport1_ab_data.MMCBOOT.value = (Uns32)(bport1_ab_data.MMCBOOT.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.VENDOR.value = (Uns32)(bport1_ab_data.VENDOR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bport1_ab_data.ADSADDR.value = (Uns32)(bport1_ab_data.ADSADDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ADMAES.value = (Uns32)(bport1_ab_data.ADMAES.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.FEVT.value = (Uns32)(bport1_ab_data.FEVT.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.WML.value = (Uns32)(bport1_ab_data.WML.value & ~(0xffffffff)) | ((0xffffffff) & (0x08100810));
        bport1_ab_data.HTCAPBLT.value = (Uns32)(bport1_ab_data.HTCAPBLT.value & ~(0xffffffff)) | ((0xffffffff) & (0x07f30000));
        bport1_ab_data.AC12ERR.value = (Uns32)(bport1_ab_data.AC12ERR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IRQSIGEN.value = (Uns32)(bport1_ab_data.IRQSIGEN.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IRQSTATEN.value = (Uns32)(bport1_ab_data.IRQSTATEN.value & ~(0xffffffff)) | ((0xffffffff) & (0x117f013f));
        bport1_ab_data.IRQSTAT.value = (Uns32)(bport1_ab_data.IRQSTAT.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SYSCTL.value = (Uns32)(bport1_ab_data.SYSCTL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00008008));
        bport1_ab_data.PROCTL.value = (Uns32)(bport1_ab_data.PROCTL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000020));
        bport1_ab_data.PRSSTAT.value = (Uns32)(bport1_ab_data.PRSSTAT.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DATPORT.value = (Uns32)(bport1_ab_data.DATPORT.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CMDRSP3.value = (Uns32)(bport1_ab_data.CMDRSP3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CMDRSP2.value = (Uns32)(bport1_ab_data.CMDRSP2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CMDRSP1.value = (Uns32)(bport1_ab_data.CMDRSP1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CMDRSP0.value = (Uns32)(bport1_ab_data.CMDRSP0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.XFERTYP.value = (Uns32)(bport1_ab_data.XFERTYP.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CMDARG.value = (Uns32)(bport1_ab_data.CMDARG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.BLKATTR.value = (Uns32)(bport1_ab_data.BLKATTR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DSADDR.value = (Uns32)(bport1_ab_data.DSADDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the SDHC peripheral used on the Freescale Vybrid platform");
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


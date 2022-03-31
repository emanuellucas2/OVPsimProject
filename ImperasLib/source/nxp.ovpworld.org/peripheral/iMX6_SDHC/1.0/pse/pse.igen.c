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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "iMX6_SDHC", "Example");
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

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_uSDHC_ADMA_SYS_ADDR_maskWrite) {
    bport1_ab_data.uSDHC_ADMA_SYS_ADDR.value = (bport1_ab_data.uSDHC_ADMA_SYS_ADDR.value & BPORT1_AB_USDHC_ADMA_SYS_ADDR_WRNMASK) | (data & BPORT1_AB_USDHC_ADMA_SYS_ADDR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_uSDHC_BLK_ATT_maskWrite) {
    bport1_ab_data.uSDHC_BLK_ATT.value = (bport1_ab_data.uSDHC_BLK_ATT.value & BPORT1_AB_USDHC_BLK_ATT_WRNMASK) | (data & BPORT1_AB_USDHC_BLK_ATT_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_uSDHC_CLK_TUNE_CTRL_STATUS_maskWrite) {
    bport1_ab_data.uSDHC_CLK_TUNE_CTRL_STATUS.value = (bport1_ab_data.uSDHC_CLK_TUNE_CTRL_STATUS.value & BPORT1_AB_USDHC_CLK_TUNE_CTRL_STATUS_WRNMASK) | (data & BPORT1_AB_USDHC_CLK_TUNE_CTRL_STATUS_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_uSDHC_DLL_CTRL_maskWrite) {
    bport1_ab_data.uSDHC_DLL_CTRL.value = (bport1_ab_data.uSDHC_DLL_CTRL.value & BPORT1_AB_USDHC_DLL_CTRL_WRNMASK) | (data & BPORT1_AB_USDHC_DLL_CTRL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_uSDHC_DS_ADDR_maskWrite) {
    bport1_ab_data.uSDHC_DS_ADDR.value = (bport1_ab_data.uSDHC_DS_ADDR.value & BPORT1_AB_USDHC_DS_ADDR_WRNMASK) | (data & BPORT1_AB_USDHC_DS_ADDR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_uSDHC_MIX_CTRL_maskWrite) {
    bport1_ab_data.uSDHC_MIX_CTRL.value = (bport1_ab_data.uSDHC_MIX_CTRL.value & BPORT1_AB_USDHC_MIX_CTRL_WRNMASK) | (data & BPORT1_AB_USDHC_MIX_CTRL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_uSDHC_MMC_BOOT_maskWrite) {
    bport1_ab_data.uSDHC_MMC_BOOT.value = (bport1_ab_data.uSDHC_MMC_BOOT.value & BPORT1_AB_USDHC_MMC_BOOT_WRNMASK) | (data & BPORT1_AB_USDHC_MMC_BOOT_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_uSDHC_VEND_SPEC2_maskWrite) {
    bport1_ab_data.uSDHC_VEND_SPEC2.value = (bport1_ab_data.uSDHC_VEND_SPEC2.value & BPORT1_AB_USDHC_VEND_SPEC2_WRNMASK) | (data & BPORT1_AB_USDHC_VEND_SPEC2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_uSDHC_VEND_SPEC_maskWrite) {
    bport1_ab_data.uSDHC_VEND_SPEC.value = (bport1_ab_data.uSDHC_VEND_SPEC.value & BPORT1_AB_USDHC_VEND_SPEC_WRNMASK) | (data & BPORT1_AB_USDHC_VEND_SPEC_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 16384);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

    ppmInstallReadCallback(regNoDefinitionRead, (void*)0 , handles.bport1 + 0x4c, 0x4);
    ppmInstallWriteCallback(regNoDefinitionWrite, (void*)0 , handles.bport1 + 0x4c, 0x4);
    ppmInstallReadCallback(regNoDefinitionRead, (void*)0 , handles.bport1 + 0x5c, 0x4);
    ppmInstallWriteCallback(regNoDefinitionWrite, (void*)0 , handles.bport1 + 0x5c, 0x4);
    ppmInstallReadCallback(regNoDefinitionRead, (void*)0 , handles.bport1 + 0x6c, 0x54);
    ppmInstallWriteCallback(regNoDefinitionWrite, (void*)0 , handles.bport1 + 0x6c, 0x54);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abuSDHC_DS_ADDR_reg = ppmCreateRegister(
            "ab_uSDHC_DS_ADDR",
            "Description\nDMA System Address\nBlocks Count For Current Transfer\nTransfer Block Size\n",
            handles.bport1,
            0x0,
            4,
            read_32,
            bport1_ab_uSDHC_DS_ADDR_maskWrite,
            view32,
            &(bport1_ab_data.uSDHC_DS_ADDR.value),
            True
        );

        ppmCreateRegisterField(abuSDHC_DS_ADDR_reg, "BLKCNT", 0, 16, 16, 1, 1);
        ppmCreateRegisterField(abuSDHC_DS_ADDR_reg, "BLKSIZE", 0, 0, 13, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_uSDHC_BLK_ATT",
            "Block Attributes",
            handles.bport1,
            0x4,
            4,
            read_32,
            bport1_ab_uSDHC_BLK_ATT_maskWrite,
            view32,
            &(bport1_ab_data.uSDHC_BLK_ATT.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_uSDHC_CMD_ARG",
            "Command Argument",
            handles.bport1,
            0x8,
            4,
            read_32,
            WriteuSDHC_CMD_ARG,
            view32,
            &(bport1_ab_data.uSDHC_CMD_ARG.value),
            True
        );
    }
    {
        registerHandle abuSDHC_CMD_XFR_TYP_reg = ppmCreateRegister(
            "ab_uSDHC_CMD_XFR_TYP",
            "Description\nCommand Transfer Type\nCommand Index\nCommand Type\nData Present Select\nCommand Index Check Enable\nCommand CRC Check Enable\nResponse Type Select\n",
            handles.bport1,
            0xc,
            4,
            read_32,
            WriteuSDHC_CMD_XFR_TYP,
            view32,
            &(bport1_ab_data.uSDHC_CMD_XFR_TYP.value),
            True
        );

        ppmCreateRegisterField(abuSDHC_CMD_XFR_TYP_reg, "CMDINX", 0, 24, 6, 1, 1);
        ppmCreateRegisterField(abuSDHC_CMD_XFR_TYP_reg, "CMDTYP", 0, 22, 2, 1, 1);
        ppmCreateRegisterField(abuSDHC_CMD_XFR_TYP_reg, "DPSEL", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_CMD_XFR_TYP_reg, "CICEN", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_CMD_XFR_TYP_reg, "CCCEN", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_CMD_XFR_TYP_reg, "RSPTYP", 0, 16, 2, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_uSDHC_CMD_RSP0",
            "Command Response0",
            handles.bport1,
            0x10,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.uSDHC_CMD_RSP0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_uSDHC_CMD_RSP1",
            "Command Response1",
            handles.bport1,
            0x14,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.uSDHC_CMD_RSP1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_uSDHC_CMD_RSP2",
            "Command Response2",
            handles.bport1,
            0x18,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.uSDHC_CMD_RSP2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_uSDHC_CMD_RSP3",
            "Command Response3",
            handles.bport1,
            0x1c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.uSDHC_CMD_RSP3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_uSDHC_DATA_BUFF_ACC_PORT",
            "Data Buffer Access Port",
            handles.bport1,
            0x20,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.uSDHC_DATA_BUFF_ACC_PORT.value),
            True
        );
    }
    {
        registerHandle abuSDHC_PRES_STATE_reg = ppmCreateRegister(
            "ab_uSDHC_PRES_STATE",
            "Description\nPresent State\nData Line Signal Level\nCMD Line Signal Level\nWrite Protect Switch Pin Level\nCard Detect Pin Level\nCard Inserted\nRe-Tuning Request (only for SD3.0 SDR104 mode)\nBuffer Read Enable\nBuffer Write Enable\nRead Transfer Active\nWrite Transfer Active\nSD Clock Gated Off Internally\nIPG_PERCLK Gated Off Internally\nHCLK Gated Off Internally\nIPG_CLK Gated Off Internally\nSD Clock Stable\nData Line Active\nCommand Inhibit (DATA)\nCommand Inhibit (CMD)\n",
            handles.bport1,
            0x24,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.uSDHC_PRES_STATE.value),
            True
        );

        ppmCreateRegisterField(abuSDHC_PRES_STATE_reg, "DLSL", 0, 24, 8, 1, 0);
        ppmCreateRegisterField(abuSDHC_PRES_STATE_reg, "CLSL", 0, 23, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_PRES_STATE_reg, "WPSPL", 0, 19, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_PRES_STATE_reg, "CDPL", 0, 18, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_PRES_STATE_reg, "CINST", 0, 16, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_PRES_STATE_reg, "RTR", 0, 12, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_PRES_STATE_reg, "BREN", 0, 11, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_PRES_STATE_reg, "BWEN", 0, 10, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_PRES_STATE_reg, "RTA", 0, 9, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_PRES_STATE_reg, "WTA", 0, 8, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_PRES_STATE_reg, "SDOFF", 0, 7, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_PRES_STATE_reg, "PEROFF", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_PRES_STATE_reg, "HCKOFF", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_PRES_STATE_reg, "IPGOFF", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_PRES_STATE_reg, "SDSTB", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_PRES_STATE_reg, "DLA", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_PRES_STATE_reg, "CDIHB", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_PRES_STATE_reg, "CIHB", 0, 0, 1, 1, 0);
    }
    {
        registerHandle abuSDHC_PROT_CTRL_reg = ppmCreateRegister(
            "ab_uSDHC_PROT_CTRL",
            "Description\nProtocol Control\nCurrent block read is non-exact block read. It is only used for SDIO.\nBURST length enable for INCR, INCR4 / INCR8 / INCR16, INCR4-WRAP / INCR8-WRAP / INCR16-WRAP\nWakeup Event Enable On SD Card Removal\nWakeup Event Enable On SD Card Insertion\nWakeup Event Enable On Card Interrupt\nRead done no 8 clock\nInterrupt At Block Gap\nRead Wait Control\nContinue Request\nStop At Block Gap Request\nDMA Select\nCard Detect Signal Selection\nCard Detect Test Level\nEndian Mode\nDATA3 as Card Detection Pin\nData Transfer Width\nLED Control\n",
            handles.bport1,
            0x28,
            4,
            read_32,
            WriteuSDHC_PROT_CTRL,
            view32,
            &(bport1_ab_data.uSDHC_PROT_CTRL.value),
            True
        );

        ppmCreateRegisterField(abuSDHC_PROT_CTRL_reg, "NON_EXACT_BLK_RD", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_PROT_CTRL_reg, "BURST_LEN_EN", 0, 27, 3, 1, 1);
        ppmCreateRegisterField(abuSDHC_PROT_CTRL_reg, "WECRM", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_PROT_CTRL_reg, "WECINS", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_PROT_CTRL_reg, "WECINT", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_PROT_CTRL_reg, "RD_DONE_NO_8CLK", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_PROT_CTRL_reg, "IABG", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_PROT_CTRL_reg, "RWCTL", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_PROT_CTRL_reg, "CREQ", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_PROT_CTRL_reg, "SABGREQ", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_PROT_CTRL_reg, "DMASEL", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abuSDHC_PROT_CTRL_reg, "CDSS", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_PROT_CTRL_reg, "CDTL", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_PROT_CTRL_reg, "EMODE", 0, 4, 2, 1, 1);
        ppmCreateRegisterField(abuSDHC_PROT_CTRL_reg, "D3CD", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_PROT_CTRL_reg, "DTW", 0, 1, 2, 1, 1);
        ppmCreateRegisterField(abuSDHC_PROT_CTRL_reg, "LCTL", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abuSDHC_SYS_CTRL_reg = ppmCreateRegister(
            "ab_uSDHC_SYS_CTRL",
            "Description\nSystem Control\nInitialization Active\nSoftware Reset For DATA Line\nSoftware Reset For CMD Line\nSoftware Reset For ALL\nhardware reset of the card\nData Timeout Counter Value\nSDCLK Frequency Select\nDivisor\n",
            handles.bport1,
            0x2c,
            4,
            ReaduSDHC_SYS_CTRL,
            WriteuSDHC_SYS_CTRL,
            view32,
            &(bport1_ab_data.uSDHC_SYS_CTRL.value),
            True
        );

        ppmCreateRegisterField(abuSDHC_SYS_CTRL_reg, "INITA", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_SYS_CTRL_reg, "RSTD", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_SYS_CTRL_reg, "RSTC", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_SYS_CTRL_reg, "RSTA", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_SYS_CTRL_reg, "IPP_RST_N", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_SYS_CTRL_reg, "DTOCV", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abuSDHC_SYS_CTRL_reg, "SDCLKFS", 0, 8, 7, 1, 1);
        ppmCreateRegisterField(abuSDHC_SYS_CTRL_reg, "DVS", 0, 4, 3, 1, 1);
    }
    {
        registerHandle abuSDHC_INT_STATUS_reg = ppmCreateRegister(
            "ab_uSDHC_INT_STATUS",
            "Description\nInterrupt Status\nDMA Error\nTuning Error: (only for SD3.0 SDR104 mode)\nAuto CMD12 Error\nData End Bit Error\nData CRC Error\nData Timeout Error\nCommand Index Error\nCommand End Bit Error\nCommand CRC Error\nCommand Timeout Error\nTuning Pass:(only for SD3.0 SDR104 mode)\nRe-Tuning Event: (only for SD3.0 SDR104 mode)\nCard Interrupt\nCard Removal\nCard Insertion\nBuffer Read Ready\nBuffer Write Ready\nDMA Interrupt\nBlock Gap Event\nTransfer Complete\nCommand Complete\n",
            handles.bport1,
            0x30,
            4,
            0,
            WriteuSDHC_INT_STATUS,
            view32,
            &(bport1_ab_data.uSDHC_INT_STATUS.value),
            True
        );

        ppmCreateRegisterField(abuSDHC_INT_STATUS_reg, "DMAE", 0, 28, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_reg, "TNE", 0, 26, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_reg, "AC12E", 0, 24, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_reg, "DEBE", 0, 22, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_reg, "DCE", 0, 21, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_reg, "DTOE", 0, 20, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_reg, "CIE", 0, 19, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_reg, "CEBE", 0, 18, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_reg, "CCE", 0, 17, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_reg, "CTOE", 0, 16, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_reg, "TP", 0, 14, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_reg, "RTE", 0, 12, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_reg, "CINT", 0, 8, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_reg, "CRM", 0, 7, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_reg, "CINS", 0, 6, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_reg, "BRR", 0, 5, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_reg, "BWR", 0, 4, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_reg, "DINT", 0, 3, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_reg, "BGE", 0, 2, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_reg, "TC", 0, 1, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_reg, "CC", 0, 0, 1, 0, 1);
    }
    {
        registerHandle abuSDHC_INT_STATUS_EN_reg = ppmCreateRegister(
            "ab_uSDHC_INT_STATUS_EN",
            "Description\nInterrupt Status Enable\nDMA Error\nTuning Error: (only for SD3.0 SDR104 mode)\nAuto CMD12 Error\nData End Bit Error\nData CRC Error\nData Timeout Error\nCommand Index Error\nCommand End Bit Error\nCommand CRC Error\nCommand Timeout Error\nTuning Pass:(only for SD3.0 SDR104 mode)\nRe-Tuning Event: (only for SD3.0 SDR104 mode)\nCard Interrupt\nCard Removal\nCard Insertion\nBuffer Read Ready\nBuffer Write Ready\nDMA Interrupt\nBlock Gap Event\nTransfer Complete\nCommand Complete\n",
            handles.bport1,
            0x34,
            4,
            read_32,
            WriteuSDHC_INT_STATUS_EN,
            view32,
            &(bport1_ab_data.uSDHC_INT_STATUS_EN.value),
            True
        );

        ppmCreateRegisterField(abuSDHC_INT_STATUS_EN_reg, "DMAESEN", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_EN_reg, "TNESEN", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_EN_reg, "AC12ESEN", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_EN_reg, "DEBESEN", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_EN_reg, "DCESEN", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_EN_reg, "DTOESEN", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_EN_reg, "CIESEN", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_EN_reg, "CEBESEN", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_EN_reg, "CCESEN", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_EN_reg, "CTOESEN", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_EN_reg, "TPSEN", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_EN_reg, "RTESEN", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_EN_reg, "CINTSEN", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_EN_reg, "CRMSEN", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_EN_reg, "CINSSEN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_EN_reg, "BRRSEN", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_EN_reg, "BWRSEN", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_EN_reg, "DINTSEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_EN_reg, "BGESEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_EN_reg, "TCSEN", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_STATUS_EN_reg, "CCSEN", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abuSDHC_INT_SIGNAL_EN_reg = ppmCreateRegister(
            "ab_uSDHC_INT_SIGNAL_EN",
            "Description\nInterrupt Signal Enable\nDMA Error\nTuning Error: (only for SD3.0 SDR104 mode)\nAuto CMD12 Error\nData End Bit Error\nData CRC Error\nData Timeout Error\nCommand Index Error\nCommand End Bit Error\nCommand CRC Error\nCommand Timeout Error\nTuning Pass:(only for SD3.0 SDR104 mode)\nRe-Tuning Event: (only for SD3.0 SDR104 mode)\nCard Interrupt\nCard Removal\nCard Insertion\nBuffer Read Ready\nBuffer Write Ready\nDMA Interrupt\nBlock Gap Event\nTransfer Complete\nCommand Complete\n",
            handles.bport1,
            0x38,
            4,
            read_32,
            WriteuSDHC_INT_SIGNAL_EN,
            view32,
            &(bport1_ab_data.uSDHC_INT_SIGNAL_EN.value),
            True
        );

        ppmCreateRegisterField(abuSDHC_INT_SIGNAL_EN_reg, "DMAEIEN", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_SIGNAL_EN_reg, "TNEIEN", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_SIGNAL_EN_reg, "AC12EIEN", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_SIGNAL_EN_reg, "DEBEIEN", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_SIGNAL_EN_reg, "DCEIEN", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_SIGNAL_EN_reg, "DTOEIEN", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_SIGNAL_EN_reg, "CIEIEN", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_SIGNAL_EN_reg, "CEBEIEN", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_SIGNAL_EN_reg, "CCEIEN", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_SIGNAL_EN_reg, "CTOEIEN", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_SIGNAL_EN_reg, "TPIEN", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_SIGNAL_EN_reg, "RTEIEN", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_SIGNAL_EN_reg, "CINTIEN", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_SIGNAL_EN_reg, "CRMIEN", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_SIGNAL_EN_reg, "CINSIEN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_SIGNAL_EN_reg, "BRRIEN", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_SIGNAL_EN_reg, "BWRIEN", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_SIGNAL_EN_reg, "DINTIEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_SIGNAL_EN_reg, "BGEIEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_SIGNAL_EN_reg, "TCIEN", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_INT_SIGNAL_EN_reg, "CCIEN", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abuSDHC_AUTOCMD12_ERR_STATUS_reg = ppmCreateRegister(
            "ab_uSDHC_AUTOCMD12_ERR_STATUS",
            "Description\nAuto CMD12 Error Status\nCommand Not Issued By Auto CMD12 Error\nAuto CMD12/23 Index Error\nAuto CMD12/23 CRC Error\nAuto CMD12/23 End Bit Error\nAuto CMD12/23 Timeout Error\nAuto CMD12 Not Executed\n",
            handles.bport1,
            0x3c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.uSDHC_AUTOCMD12_ERR_STATUS.value),
            True
        );

        ppmCreateRegisterField(abuSDHC_AUTOCMD12_ERR_STATUS_reg, "CNIBAC12E", 0, 7, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_AUTOCMD12_ERR_STATUS_reg, "AC12IE", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_AUTOCMD12_ERR_STATUS_reg, "AC12CE", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_AUTOCMD12_ERR_STATUS_reg, "AC12EBE", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_AUTOCMD12_ERR_STATUS_reg, "AC12TOE", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_AUTOCMD12_ERR_STATUS_reg, "AC12NE", 0, 0, 1, 1, 0);
    }
    {
        registerHandle abuSDHC_HOST_CTRL_CAP_reg = ppmCreateRegister(
            "ab_uSDHC_HOST_CTRL_CAP",
            "Description\nHost Controller Capabilities\nVoltage Support 1.8 V\nVoltage Support 3.0 V\nVoltage Support 3.3V\nSuspend / Resume Support\nDMA Support\nHigh Speed Support\nADMA Support (Advanced DMA Support)\nMax Block Length\n",
            handles.bport1,
            0x40,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.uSDHC_HOST_CTRL_CAP.value),
            True
        );

        ppmCreateRegisterField(abuSDHC_HOST_CTRL_CAP_reg, "VS18", 0, 26, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_HOST_CTRL_CAP_reg, "VS30", 0, 25, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_HOST_CTRL_CAP_reg, "VS33", 0, 24, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_HOST_CTRL_CAP_reg, "SRS", 0, 23, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_HOST_CTRL_CAP_reg, "DMAS", 0, 22, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_HOST_CTRL_CAP_reg, "HSS", 0, 21, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_HOST_CTRL_CAP_reg, "ADMAS", 0, 20, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_HOST_CTRL_CAP_reg, "MBL", 0, 16, 3, 1, 0);
    }
    {
        registerHandle abuSDHC_WTMK_LVL_reg = ppmCreateRegister(
            "ab_uSDHC_WTMK_LVL",
            "Description\nWatermark Level\nWrite Burst Length 1\nWrite Watermark Level\nRead Burst Length 2\nRead Watermark Level\n",
            handles.bport1,
            0x44,
            4,
            read_32,
            WriteuSDHC_WTMK_LVL,
            view32,
            &(bport1_ab_data.uSDHC_WTMK_LVL.value),
            True
        );

        ppmCreateRegisterField(abuSDHC_WTMK_LVL_reg, "WR_BRST_LEN", 0, 24, 5, 1, 1);
        ppmCreateRegisterField(abuSDHC_WTMK_LVL_reg, "WR_WML", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abuSDHC_WTMK_LVL_reg, "RD_BRST_LEN", 0, 8, 5, 1, 1);
        ppmCreateRegisterField(abuSDHC_WTMK_LVL_reg, "RD_WML", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abuSDHC_MIX_CTRL_reg = ppmCreateRegister(
            "ab_uSDHC_MIX_CTRL",
            "Description\nMixer Control\nFeedback Clock Source Selection (Only used for SD3.0, SDR104 mode)\nAuto Tuning Enable (Only used for SD3.0, SDR104 mode)\nTuned clock or Fixed clock is used to sample data / cmd (Only used for SD3.0, SDR104 mode)\nExecute Tuning: (Only used for SD3.0, SDR104 mode)\nAuto CMD23 Enable\nIn DDR 4-bit mode nibble position indictation\nMulti / Single Block Select\nData Transfer Direction Select\nDual Data Rate mode selection\nAuto CMD12 Enable\nBlock Count Enable\nDMA Enable\n",
            handles.bport1,
            0x48,
            4,
            read_32,
            bport1_ab_uSDHC_MIX_CTRL_maskWrite,
            view32,
            &(bport1_ab_data.uSDHC_MIX_CTRL.value),
            True
        );

        ppmCreateRegisterField(abuSDHC_MIX_CTRL_reg, "FBCLK_SEL", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_MIX_CTRL_reg, "AUTO_TUNE_EN", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_MIX_CTRL_reg, "SMP_CLK_SEL", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_MIX_CTRL_reg, "EXE_TUNE", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_MIX_CTRL_reg, "AC23EN", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_MIX_CTRL_reg, "NIBBLE_POS", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_MIX_CTRL_reg, "MSBSEL", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_MIX_CTRL_reg, "DTDSEL", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_MIX_CTRL_reg, "DDR_EN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_MIX_CTRL_reg, "AC12EN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_MIX_CTRL_reg, "BCEN", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_MIX_CTRL_reg, "DMAEN", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abuSDHC_FORCE_EVENT_reg = ppmCreateRegister(
            "ab_uSDHC_FORCE_EVENT",
            "Description\nForce Event\nForce Event Card Interrupt\nForce Event DMA Error\nForce Tuning Error\nForce Event Auto Command 12 Error\nForce Event Data End Bit Error\nForce Event Data CRC Error\nForce Event Data Time Out Error\nForce Event Command Index Error\nForce Event Command End Bit Error\nForce Event Command CRC Error\nForce Event Command Time Out Error\nForce Event Command Not Executed By Auto Command 12 Error\nForce Event Auto Command 12 Index Error\nForce Event Auto Command 12 End Bit Error\nForce Event Auto Command 12 CRC Error\nForce Event Auto Command 12 Time Out Error\nForce Event Auto Command 12 Not Executed\n",
            handles.bport1,
            0x50,
            4,
            0,
            WriteuSDHC_FORCE_EVENT,
            view32,
            &(bport1_ab_data.uSDHC_FORCE_EVENT.value),
            True
        );

        ppmCreateRegisterField(abuSDHC_FORCE_EVENT_reg, "FEVTCINT", 0, 31, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_FORCE_EVENT_reg, "FEVTDMAE", 0, 28, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_FORCE_EVENT_reg, "FEVTTNE", 0, 26, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_FORCE_EVENT_reg, "FEVTAC12E", 0, 24, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_FORCE_EVENT_reg, "FEVTDEBE", 0, 22, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_FORCE_EVENT_reg, "FEVTDCE", 0, 21, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_FORCE_EVENT_reg, "FEVTDTOE", 0, 20, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_FORCE_EVENT_reg, "FEVTCIE", 0, 19, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_FORCE_EVENT_reg, "FEVTCEBE", 0, 18, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_FORCE_EVENT_reg, "FEVTCCE", 0, 17, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_FORCE_EVENT_reg, "FEVTCTOE", 0, 16, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_FORCE_EVENT_reg, "FEVTCNIBAC12E", 0, 7, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_FORCE_EVENT_reg, "FEVTAC12IE", 0, 4, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_FORCE_EVENT_reg, "FEVTAC12EBE", 0, 3, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_FORCE_EVENT_reg, "FEVTAC12CE", 0, 2, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_FORCE_EVENT_reg, "FEVTAC12TOE", 0, 1, 1, 0, 1);
        ppmCreateRegisterField(abuSDHC_FORCE_EVENT_reg, "FEVTAC12NE", 0, 0, 1, 0, 1);
    }
    {
        registerHandle abuSDHC_ADMA_ERR_STATUS_reg = ppmCreateRegister(
            "ab_uSDHC_ADMA_ERR_STATUS",
            "Description\nADMA Error Status Register\nADMA Descritor Error\nADMA Length Mismatch Error\nADMA Error State (when ADMA Error is occurred)\n",
            handles.bport1,
            0x54,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.uSDHC_ADMA_ERR_STATUS.value),
            True
        );

        ppmCreateRegisterField(abuSDHC_ADMA_ERR_STATUS_reg, "ADMADCE", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_ADMA_ERR_STATUS_reg, "ADMALME", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_ADMA_ERR_STATUS_reg, "ADMAES", 0, 0, 2, 1, 0);
    }
    {
        ppmCreateRegister(
            "ab_uSDHC_ADMA_SYS_ADDR",
            "ADMA System Address",
            handles.bport1,
            0x58,
            4,
            read_32,
            bport1_ab_uSDHC_ADMA_SYS_ADDR_maskWrite,
            view32,
            &(bport1_ab_data.uSDHC_ADMA_SYS_ADDR.value),
            True
        );
    }
    {
        registerHandle abuSDHC_DLL_CTRL_reg = ppmCreateRegister(
            "ab_uSDHC_DLL_CTRL",
            "Description\nDLL (Delay Line) Control\nDLL control loop update interval\nSlave delay line update interval\nRefer to DLL_CTRL_SLV_DLY_TARGET0\nWhen SLV_OVERRIDE = 1 This field is used to select 1 of 128 physical taps manually. A value of 0 selects tap 1, and a value of 0x7f selects tap 128.\nEnable manual override for slave delay chain using SLV_OVERRIDE_VAL\nPrevent the DLL from updating\nThe delay target for the uSDHC loopback read clock\nForce the slave delay line to update to the DLL calibrated value immediately\nForce a reset on DLL\nEnable the DLL and delay chain\n",
            handles.bport1,
            0x60,
            4,
            read_32,
            bport1_ab_uSDHC_DLL_CTRL_maskWrite,
            view32,
            &(bport1_ab_data.uSDHC_DLL_CTRL.value),
            True
        );

        ppmCreateRegisterField(abuSDHC_DLL_CTRL_reg, "DLL_CTRL_REF_UPDATE_INT", 0, 28, 4, 1, 1);
        ppmCreateRegisterField(abuSDHC_DLL_CTRL_reg, "DLL_CTRL_SLV_UPDATE_INT", 0, 20, 8, 1, 1);
        ppmCreateRegisterField(abuSDHC_DLL_CTRL_reg, "DLL_CTRL_SLV_DLY_TARGET1", 0, 16, 3, 1, 1);
        ppmCreateRegisterField(abuSDHC_DLL_CTRL_reg, "DLL_CTRL_SLV_OVERRIDE_VAL", 0, 9, 6, 1, 1);
        ppmCreateRegisterField(abuSDHC_DLL_CTRL_reg, "DLL_CTRL_SLV_OVERRIDE", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_DLL_CTRL_reg, "DLL_CTRL_GATE_UPDATE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_DLL_CTRL_reg, "DLL_CTRL_SLV_DLY_TARGET0", 0, 3, 4, 1, 1);
        ppmCreateRegisterField(abuSDHC_DLL_CTRL_reg, "DLL_CTRL_SLV_FORCE_UPD", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_DLL_CTRL_reg, "DLL_CTRL_RESET", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_DLL_CTRL_reg, "DLL_CTRL_ENABLE", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abuSDHC_DLL_STATUS_reg = ppmCreateRegister(
            "ab_uSDHC_DLL_STATUS",
            "Description\nDLL Status\nReference delay line select taps\nSlave delay line select status\nReference DLL lock status\nSlave delay-line lock status\n",
            handles.bport1,
            0x64,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.uSDHC_DLL_STATUS.value),
            True
        );

        ppmCreateRegisterField(abuSDHC_DLL_STATUS_reg, "DLL_STS_REF_SEL", 0, 9, 7, 1, 0);
        ppmCreateRegisterField(abuSDHC_DLL_STATUS_reg, "DLL_STS_SLV_SEL", 0, 2, 7, 1, 0);
        ppmCreateRegisterField(abuSDHC_DLL_STATUS_reg, "DLL_STS_REF_LOCK", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(abuSDHC_DLL_STATUS_reg, "DLL_STS_SLV_LOCK", 0, 0, 1, 1, 0);
    }
    {
        registerHandle abuSDHC_CLK_TUNE_CTRL_STATUS_reg = ppmCreateRegister(
            "ab_uSDHC_CLK_TUNE_CTRL_STATUS",
            "Description\nCLK Tuning Control and Status\nPRE error\nNumber of delay cells added on the feedback clock between the feedback clock and CLK_PRE\nNumber of delay cells added on the feedback clock between CLK_PRE and CLK_OUT\nNumber of delay cells added on the feedback clock between CLK_OUT and CLK_POST\nNXT error\nNumber of delay cells on the feedback clock between the feedback clock and CLK_PRE\nNumber of delay cells on the feedback clock between CLK_PRE and CLK_OUT\nNumber of delay cells on the feedback clock between CLK_OUT and CLK_POST\n",
            handles.bport1,
            0x68,
            4,
            read_32,
            bport1_ab_uSDHC_CLK_TUNE_CTRL_STATUS_maskWrite,
            view32,
            &(bport1_ab_data.uSDHC_CLK_TUNE_CTRL_STATUS.value),
            True
        );

        ppmCreateRegisterField(abuSDHC_CLK_TUNE_CTRL_STATUS_reg, "PRE_ERR", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_CLK_TUNE_CTRL_STATUS_reg, "TAP_SEL_PRE", 0, 24, 7, 1, 1);
        ppmCreateRegisterField(abuSDHC_CLK_TUNE_CTRL_STATUS_reg, "TAP_SEL_OUT", 0, 20, 4, 1, 1);
        ppmCreateRegisterField(abuSDHC_CLK_TUNE_CTRL_STATUS_reg, "TAP_SEL_POST", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abuSDHC_CLK_TUNE_CTRL_STATUS_reg, "NXT_ERR", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_CLK_TUNE_CTRL_STATUS_reg, "DLY_CELL_SET_PRE", 0, 8, 7, 1, 1);
        ppmCreateRegisterField(abuSDHC_CLK_TUNE_CTRL_STATUS_reg, "DLY_CELL_SET_OUT", 0, 4, 3, 1, 1);
        ppmCreateRegisterField(abuSDHC_CLK_TUNE_CTRL_STATUS_reg, "DLY_CELL_SET_POST", 0, 0, 3, 1, 1);
    }
    {
        registerHandle abuSDHC_VEND_SPEC_reg = ppmCreateRegister(
            "ab_uSDHC_VEND_SPEC",
            "Description\nVendor Specific Register\nByte access Enable\nInternal State Value\nCRC Check Disable\nCard Clock Software Enable\nIPG_PERCLK Software Enable\nAHB Clock Software Enable\nIPG_CLK Software Enable\nForce CLK output active\nOnly for debug. Force CLK output active when sending Abort command\nOnly for debug. Polarity of the WP pin\nOnly for debug.Polarity of the CD_B pin\nOnly for debug.Polarity of DATA3 pin when it is used as card detection\nCheck busy enable after auto CMD12 for write data packet\nConflict check enable\nVoltage Selection\nExternal DMA Request Enable\n",
            handles.bport1,
            0xc0,
            4,
            read_32,
            bport1_ab_uSDHC_VEND_SPEC_maskWrite,
            view32,
            &(bport1_ab_data.uSDHC_VEND_SPEC.value),
            True
        );

        ppmCreateRegisterField(abuSDHC_VEND_SPEC_reg, "CMD_BYTE_EN", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_VEND_SPEC_reg, "INT_ST_VAL", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abuSDHC_VEND_SPEC_reg, "CRC_CHK_DIS", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_VEND_SPEC_reg, "CARD_CLK_SOFT_EN", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_VEND_SPEC_reg, "IPG_PERCLK_SOFT_EN", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_VEND_SPEC_reg, "HCLK_SOFT_EN", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_VEND_SPEC_reg, "IPG_CLK_SOFT_EN", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_VEND_SPEC_reg, "FRC_SDCLK_ON", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_VEND_SPEC_reg, "CLKONJ_IN_ABORT", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_VEND_SPEC_reg, "WP_POL", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_VEND_SPEC_reg, "CD_POL", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_VEND_SPEC_reg, "DAT3_CD_POL", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_VEND_SPEC_reg, "AC12_WR_CHKBUSY_EN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_VEND_SPEC_reg, "CONFLICT_CHK_EN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_VEND_SPEC_reg, "VSELECT", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_VEND_SPEC_reg, "EXT_DMA_EN", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abuSDHC_MMC_BOOT_reg = ppmCreateRegister(
            "ab_uSDHC_MMC_BOOT",
            "Description\nMMC Boot Register\nStop At Block Gap value of automatic mode\nDisable Time Out\nEnable auto stop at block gap function\nBoot mode enable\nBoot mode select\nBoot ACK mode select\nBoot ACK time out counter value\n",
            handles.bport1,
            0xc4,
            4,
            read_32,
            bport1_ab_uSDHC_MMC_BOOT_maskWrite,
            view32,
            &(bport1_ab_data.uSDHC_MMC_BOOT.value),
            True
        );

        ppmCreateRegisterField(abuSDHC_MMC_BOOT_reg, "BOOT_BLK_CNT", 0, 16, 16, 1, 1);
        ppmCreateRegisterField(abuSDHC_MMC_BOOT_reg, "DISABLE_TIME_OUT", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_MMC_BOOT_reg, "AUTO_SABG_EN", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_MMC_BOOT_reg, "BOOT_EN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_MMC_BOOT_reg, "BOOT_MODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_MMC_BOOT_reg, "BOOT_ACK", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_MMC_BOOT_reg, "DTOCV_ACK", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abuSDHC_VEND_SPEC2_reg = ppmCreateRegister(
            "ab_uSDHC_VEND_SPEC2",
            "Description\nVendor Specific 2 Register\nDisable the feature to clear the Card interrupt status bit when Card Interrupt status enable bit is cleared\nEnable the auto tuning circuit to check the CMD line\nEnable the auto tuning circuit to check the DATA0 only. It is used with the TUNING_8bit_EN together.\nEnable the auto tuning circuit to check the DATA[7:0]. It is used with the TUNING_1bit_EN together.\nCard Interrupt Detection Test\nInterrupt window after abort command is sent.\nCMD_OE / DATA_OE logic generation test.\nTimeout counter test.\n",
            handles.bport1,
            0xc8,
            4,
            read_32,
            bport1_ab_uSDHC_VEND_SPEC2_maskWrite,
            view32,
            &(bport1_ab_data.uSDHC_VEND_SPEC2.value),
            True
        );

        ppmCreateRegisterField(abuSDHC_VEND_SPEC2_reg, "CARD_INT_AUTO_CLR_DIS", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_VEND_SPEC2_reg, "TUNING_CMD_EN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_VEND_SPEC2_reg, "TUNING_1bit_EN", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_VEND_SPEC2_reg, "TUNING_8bit_EN", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_VEND_SPEC2_reg, "CARD_INT_D3_TEST", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_VEND_SPEC2_reg, "SDR104_NSD_DIS", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_VEND_SPEC2_reg, "SDR104_OE_DIS", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abuSDHC_VEND_SPEC2_reg, "SDR104_TIMING_DIS", 0, 0, 1, 1, 1);
    }

}

/////////////////////////////// Bus Master Ports ///////////////////////////////

static void installMasterPorts(void) {
    handles.mport = ppmOpenAddressSpace("mport");
    if (!handles.mport) {
        bhmMessage("E", "PPM_MPNC", "Could not connect port 'mport'");
    }
}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.uSDHC_VEND_SPEC2.value = (Uns32)(bport1_ab_data.uSDHC_VEND_SPEC2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000006));
        bport1_ab_data.uSDHC_MMC_BOOT.value = (Uns32)(bport1_ab_data.uSDHC_MMC_BOOT.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.uSDHC_VEND_SPEC.value = (Uns32)(bport1_ab_data.uSDHC_VEND_SPEC.value & ~(0xffffffff)) | ((0xffffffff) & (0x20007809));
        bport1_ab_data.uSDHC_CLK_TUNE_CTRL_STATUS.value = (Uns32)(bport1_ab_data.uSDHC_CLK_TUNE_CTRL_STATUS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.uSDHC_DLL_STATUS.value = (Uns32)(bport1_ab_data.uSDHC_DLL_STATUS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.uSDHC_DLL_CTRL.value = (Uns32)(bport1_ab_data.uSDHC_DLL_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000200));
        bport1_ab_data.uSDHC_ADMA_SYS_ADDR.value = (Uns32)(bport1_ab_data.uSDHC_ADMA_SYS_ADDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.uSDHC_ADMA_ERR_STATUS.value = (Uns32)(bport1_ab_data.uSDHC_ADMA_ERR_STATUS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.uSDHC_FORCE_EVENT.value = (Uns32)(bport1_ab_data.uSDHC_FORCE_EVENT.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.uSDHC_MIX_CTRL.value = (Uns32)(bport1_ab_data.uSDHC_MIX_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x80000000));
        bport1_ab_data.uSDHC_WTMK_LVL.value = (Uns32)(bport1_ab_data.uSDHC_WTMK_LVL.value & ~(0xffffffff)) | ((0xffffffff) & (0x08100810));
        bport1_ab_data.uSDHC_HOST_CTRL_CAP.value = (Uns32)(bport1_ab_data.uSDHC_HOST_CTRL_CAP.value & ~(0xffffffff)) | ((0xffffffff) & (0x07F30000));
        bport1_ab_data.uSDHC_AUTOCMD12_ERR_STATUS.value = (Uns32)(bport1_ab_data.uSDHC_AUTOCMD12_ERR_STATUS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.uSDHC_INT_SIGNAL_EN.value = (Uns32)(bport1_ab_data.uSDHC_INT_SIGNAL_EN.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.uSDHC_INT_STATUS_EN.value = (Uns32)(bport1_ab_data.uSDHC_INT_STATUS_EN.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.uSDHC_INT_STATUS.value = (Uns32)(bport1_ab_data.uSDHC_INT_STATUS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.uSDHC_SYS_CTRL.value = (Uns32)(bport1_ab_data.uSDHC_SYS_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x0080800F));
        bport1_ab_data.uSDHC_PROT_CTRL.value = (Uns32)(bport1_ab_data.uSDHC_PROT_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x08800020));
        bport1_ab_data.uSDHC_PRES_STATE.value = (Uns32)(bport1_ab_data.uSDHC_PRES_STATE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.uSDHC_DATA_BUFF_ACC_PORT.value = (Uns32)(bport1_ab_data.uSDHC_DATA_BUFF_ACC_PORT.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.uSDHC_CMD_RSP3.value = (Uns32)(bport1_ab_data.uSDHC_CMD_RSP3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.uSDHC_CMD_RSP2.value = (Uns32)(bport1_ab_data.uSDHC_CMD_RSP2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.uSDHC_CMD_RSP1.value = (Uns32)(bport1_ab_data.uSDHC_CMD_RSP1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.uSDHC_CMD_RSP0.value = (Uns32)(bport1_ab_data.uSDHC_CMD_RSP0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.uSDHC_CMD_XFR_TYP.value = (Uns32)(bport1_ab_data.uSDHC_CMD_XFR_TYP.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.uSDHC_CMD_ARG.value = (Uns32)(bport1_ab_data.uSDHC_CMD_ARG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.uSDHC_BLK_ATT.value = (Uns32)(bport1_ab_data.uSDHC_BLK_ATT.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.uSDHC_DS_ADDR.value = (Uns32)(bport1_ab_data.uSDHC_DS_ADDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "NXP i.MX6 SDHC Ultra Secured Digital Host Controller");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Not Complete. Register interface only.");
        ppmDocAddText(doc_22_node, "Support only for memory card features.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "i.MX 6Solo/6DualLite Applications Processor Reference Manual (IMX6SDLRM_Ref_Manual.pdf");
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


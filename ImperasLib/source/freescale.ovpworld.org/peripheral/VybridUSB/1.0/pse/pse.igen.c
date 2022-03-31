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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "VybridUSB", "Example");
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

static PPM_WRITE_CB(bport1_ab_BURSTSIZE_maskWrite) {
    bport1_ab_data.BURSTSIZE.value = (bport1_ab_data.BURSTSIZE.value & BPORT1_AB_BURSTSIZE_WRNMASK) | (data & BPORT1_AB_BURSTSIZE_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CTRL_maskWrite) {
    bport1_ab_data.CTRL.value = (bport1_ab_data.CTRL.value & BPORT1_AB_CTRL_WRNMASK) | (data & BPORT1_AB_CTRL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPTCOMPLETE_maskWrite) {
    bport1_ab_data.ENDPTCOMPLETE.value = (bport1_ab_data.ENDPTCOMPLETE.value & BPORT1_AB_ENDPTCOMPLETE_WRNMASK) | (data & BPORT1_AB_ENDPTCOMPLETE_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPTCTRL0_maskWrite) {
    bport1_ab_data.ENDPTCTRL0.value = (bport1_ab_data.ENDPTCTRL0.value & BPORT1_AB_ENDPTCTRL0_WRNMASK) | (data & BPORT1_AB_ENDPTCTRL0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPTCTRL1_maskWrite) {
    bport1_ab_data.ENDPTCTRL1.value = (bport1_ab_data.ENDPTCTRL1.value & BPORT1_AB_ENDPTCTRL1_WRNMASK) | (data & BPORT1_AB_ENDPTCTRL1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPTCTRL2_maskWrite) {
    bport1_ab_data.ENDPTCTRL2.value = (bport1_ab_data.ENDPTCTRL2.value & BPORT1_AB_ENDPTCTRL2_WRNMASK) | (data & BPORT1_AB_ENDPTCTRL2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPTCTRL3_maskWrite) {
    bport1_ab_data.ENDPTCTRL3.value = (bport1_ab_data.ENDPTCTRL3.value & BPORT1_AB_ENDPTCTRL3_WRNMASK) | (data & BPORT1_AB_ENDPTCTRL3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPTCTRL4_maskWrite) {
    bport1_ab_data.ENDPTCTRL4.value = (bport1_ab_data.ENDPTCTRL4.value & BPORT1_AB_ENDPTCTRL4_WRNMASK) | (data & BPORT1_AB_ENDPTCTRL4_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPTCTRL5_maskWrite) {
    bport1_ab_data.ENDPTCTRL5.value = (bport1_ab_data.ENDPTCTRL5.value & BPORT1_AB_ENDPTCTRL5_WRNMASK) | (data & BPORT1_AB_ENDPTCTRL5_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPTFLUSH_maskWrite) {
    bport1_ab_data.ENDPTFLUSH.value = (bport1_ab_data.ENDPTFLUSH.value & BPORT1_AB_ENDPTFLUSH_WRNMASK) | (data & BPORT1_AB_ENDPTFLUSH_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPTNAKEN_maskWrite) {
    bport1_ab_data.ENDPTNAKEN.value = (bport1_ab_data.ENDPTNAKEN.value & BPORT1_AB_ENDPTNAKEN_WRNMASK) | (data & BPORT1_AB_ENDPTNAKEN_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPTNAK_maskWrite) {
    bport1_ab_data.ENDPTNAK.value = (bport1_ab_data.ENDPTNAK.value & BPORT1_AB_ENDPTNAK_WRNMASK) | (data & BPORT1_AB_ENDPTNAK_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPTPRIME_maskWrite) {
    bport1_ab_data.ENDPTPRIME.value = (bport1_ab_data.ENDPTPRIME.value & BPORT1_AB_ENDPTPRIME_WRNMASK) | (data & BPORT1_AB_ENDPTPRIME_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPTSETUPSTAT_maskWrite) {
    bport1_ab_data.ENDPTSETUPSTAT.value = (bport1_ab_data.ENDPTSETUPSTAT.value & BPORT1_AB_ENDPTSETUPSTAT_WRNMASK) | (data & BPORT1_AB_ENDPTSETUPSTAT_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FRINDEX_maskWrite) {
    bport1_ab_data.FRINDEX.value = (bport1_ab_data.FRINDEX.value & BPORT1_AB_FRINDEX_WRNMASK) | (data & BPORT1_AB_FRINDEX_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_GPTIMER0CTRL_maskWrite) {
    bport1_ab_data.GPTIMER0CTRL.value = (bport1_ab_data.GPTIMER0CTRL.value & BPORT1_AB_GPTIMER0CTRL_WRNMASK) | (data & BPORT1_AB_GPTIMER0CTRL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_GPTIMER0LD_maskWrite) {
    bport1_ab_data.GPTIMER0LD.value = (bport1_ab_data.GPTIMER0LD.value & BPORT1_AB_GPTIMER0LD_WRNMASK) | (data & BPORT1_AB_GPTIMER0LD_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_GPTIMER1CTRL_maskWrite) {
    bport1_ab_data.GPTIMER1CTRL.value = (bport1_ab_data.GPTIMER1CTRL.value & BPORT1_AB_GPTIMER1CTRL_WRNMASK) | (data & BPORT1_AB_GPTIMER1CTRL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_GPTIMER1LD_maskWrite) {
    bport1_ab_data.GPTIMER1LD.value = (bport1_ab_data.GPTIMER1LD.value & BPORT1_AB_GPTIMER1LD_WRNMASK) | (data & BPORT1_AB_GPTIMER1LD_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_OTGSC_maskWrite) {
    bport1_ab_data.OTGSC.value = (bport1_ab_data.OTGSC.value & BPORT1_AB_OTGSC_WRNMASK) | (data & BPORT1_AB_OTGSC_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PORTSC1_maskWrite) {
    bport1_ab_data.PORTSC1.value = (bport1_ab_data.PORTSC1.value & BPORT1_AB_PORTSC1_WRNMASK) | (data & BPORT1_AB_PORTSC1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SBUSCFG_maskWrite) {
    bport1_ab_data.SBUSCFG.value = (bport1_ab_data.SBUSCFG.value & BPORT1_AB_SBUSCFG_WRNMASK) | (data & BPORT1_AB_SBUSCFG_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TXFILLTUNING_maskWrite) {
    bport1_ab_data.TXFILLTUNING.value = (bport1_ab_data.TXFILLTUNING.value & BPORT1_AB_TXFILLTUNING_WRNMASK) | (data & BPORT1_AB_TXFILLTUNING_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_USBCMD_maskWrite) {
    bport1_ab_data.USBCMD.value = (bport1_ab_data.USBCMD.value & BPORT1_AB_USBCMD_WRNMASK) | (data & BPORT1_AB_USBCMD_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_USBINTR_maskWrite) {
    bport1_ab_data.USBINTR.value = (bport1_ab_data.USBINTR.value & BPORT1_AB_USBINTR_WRNMASK) | (data & BPORT1_AB_USBINTR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_USBMODE_maskWrite) {
    bport1_ab_data.USBMODE.value = (bport1_ab_data.USBMODE.value & BPORT1_AB_USBMODE_WRNMASK) | (data & BPORT1_AB_USBMODE_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_USBSTS_maskWrite) {
    bport1_ab_data.USBSTS.value = (bport1_ab_data.USBSTS.value & BPORT1_AB_USBSTS_WRNMASK) | (data & BPORT1_AB_USBSTS_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abID_reg = ppmCreateRegister(
            "ab_ID",
            "Identification register, offset: 0x0",
            handles.bport1,
            0x0,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.ID.value),
            True
        );

        ppmCreateRegisterField(abID_reg, "ID", 0, 0, 6, 1, 0);
        ppmCreateRegisterField(abID_reg, "NID", 0, 8, 6, 1, 0);
        ppmCreateRegisterField(abID_reg, "REVISION", 0, 16, 8, 1, 0);
    }
    {
        registerHandle abHWGENERAL_reg = ppmCreateRegister(
            "ab_HWGENERAL",
            "Hardware General, offset: 0x4",
            handles.bport1,
            0x4,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.HWGENERAL.value),
            True
        );

        ppmCreateRegisterField(abHWGENERAL_reg, "PHYM", 0, 6, 3, 1, 0);
        ppmCreateRegisterField(abHWGENERAL_reg, "PHYW", 0, 4, 2, 1, 0);
        ppmCreateRegisterField(abHWGENERAL_reg, "SM", 0, 9, 2, 1, 0);
    }
    {
        registerHandle abHWHOST_reg = ppmCreateRegister(
            "ab_HWHOST",
            "Host Hardware Parameters, offset: 0x8",
            handles.bport1,
            0x8,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.HWHOST.value),
            True
        );

        ppmCreateRegisterField(abHWHOST_reg, "HC", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(abHWHOST_reg, "NPORT", 0, 1, 3, 1, 0);
    }
    {
        registerHandle abHWDEVICE_reg = ppmCreateRegister(
            "ab_HWDEVICE",
            "Device Hardware Parameters, offset: 0xC",
            handles.bport1,
            0xc,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.HWDEVICE.value),
            True
        );

        ppmCreateRegisterField(abHWDEVICE_reg, "DC", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(abHWDEVICE_reg, "DEVEP", 0, 1, 5, 1, 0);
    }
    {
        registerHandle abHWTXBUF_reg = ppmCreateRegister(
            "ab_HWTXBUF",
            "TX Buffer Hardware Parameters, offset: 0x10",
            handles.bport1,
            0x10,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.HWTXBUF.value),
            True
        );

        ppmCreateRegisterField(abHWTXBUF_reg, "TXBURST", 0, 0, 8, 1, 0);
        ppmCreateRegisterField(abHWTXBUF_reg, "TXCHANADD", 0, 16, 8, 1, 0);
    }
    {
        registerHandle abHWRXBUF_reg = ppmCreateRegister(
            "ab_HWRXBUF",
            "RX Buffer Hardware Parameters, offset: 0x14",
            handles.bport1,
            0x14,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.HWRXBUF.value),
            True
        );

        ppmCreateRegisterField(abHWRXBUF_reg, "RXADD", 0, 8, 8, 1, 0);
        ppmCreateRegisterField(abHWRXBUF_reg, "RXBURST", 0, 0, 8, 1, 0);
    }
    {
        registerHandle abGPTIMER0LD_reg = ppmCreateRegister(
            "ab_GPTIMER0LD",
            "General Purpose Timer #0 Load, offset: 0x80",
            handles.bport1,
            0x80,
            4,
            read_32,
            bport1_ab_GPTIMER0LD_maskWrite,
            view32,
            &(bport1_ab_data.GPTIMER0LD.value),
            True
        );

        ppmCreateRegisterField(abGPTIMER0LD_reg, "GPTLD", 0, 0, 24, 1, 1);
    }
    {
        registerHandle abGPTIMER0CTRL_reg = ppmCreateRegister(
            "ab_GPTIMER0CTRL",
            "General Purpose Timer #0 Controller, offset: 0x84",
            handles.bport1,
            0x84,
            4,
            read_32,
            bport1_ab_GPTIMER0CTRL_maskWrite,
            view32,
            &(bport1_ab_data.GPTIMER0CTRL.value),
            True
        );

        ppmCreateRegisterField(abGPTIMER0CTRL_reg, "GPTCNT", 0, 0, 24, 1, 1);
        ppmCreateRegisterField(abGPTIMER0CTRL_reg, "GPTMODE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abGPTIMER0CTRL_reg, "GPTRST", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abGPTIMER0CTRL_reg, "GPTRUN", 0, 31, 1, 1, 1);
    }
    {
        registerHandle abGPTIMER1LD_reg = ppmCreateRegister(
            "ab_GPTIMER1LD",
            "General Purpose Timer #1 Load, offset: 0x88",
            handles.bport1,
            0x88,
            4,
            read_32,
            bport1_ab_GPTIMER1LD_maskWrite,
            view32,
            &(bport1_ab_data.GPTIMER1LD.value),
            True
        );

        ppmCreateRegisterField(abGPTIMER1LD_reg, "GPTLD", 0, 0, 24, 1, 1);
    }
    {
        registerHandle abGPTIMER1CTRL_reg = ppmCreateRegister(
            "ab_GPTIMER1CTRL",
            "General Purpose Timer #1 Controller, offset: 0x8C",
            handles.bport1,
            0x8c,
            4,
            read_32,
            bport1_ab_GPTIMER1CTRL_maskWrite,
            view32,
            &(bport1_ab_data.GPTIMER1CTRL.value),
            True
        );

        ppmCreateRegisterField(abGPTIMER1CTRL_reg, "GPTCNT", 0, 0, 24, 1, 1);
        ppmCreateRegisterField(abGPTIMER1CTRL_reg, "GPTMODE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abGPTIMER1CTRL_reg, "GPTRST", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abGPTIMER1CTRL_reg, "GPTRUN", 0, 31, 1, 1, 1);
    }
    {
        registerHandle abSBUSCFG_reg = ppmCreateRegister(
            "ab_SBUSCFG",
            "System Bus Config, offset: 0x90",
            handles.bport1,
            0x90,
            4,
            read_32,
            bport1_ab_SBUSCFG_maskWrite,
            view32,
            &(bport1_ab_data.SBUSCFG.value),
            True
        );

        ppmCreateRegisterField(abSBUSCFG_reg, "AHBBRST", 0, 0, 3, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_CAPVERSION",
            "Capability Register Length, offset: 0x100",
            handles.bport1,
            0x100,
            4,
            readCapVersion,
            0,
            view32,
            &(bport1_ab_data.CAPVERSION.value),
            True
        );
    }
    {
        registerHandle abHCSPARAMS_reg = ppmCreateRegister(
            "ab_HCSPARAMS",
            "Host Controller Structural Parameters, offset: 0x104",
            handles.bport1,
            0x104,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.HCSPARAMS.value),
            True
        );

        ppmCreateRegisterField(abHCSPARAMS_reg, "N_CC", 0, 12, 4, 1, 0);
        ppmCreateRegisterField(abHCSPARAMS_reg, "N_PCC", 0, 8, 4, 1, 0);
        ppmCreateRegisterField(abHCSPARAMS_reg, "N_PORTS", 0, 0, 4, 1, 0);
        ppmCreateRegisterField(abHCSPARAMS_reg, "N_PTT", 0, 20, 4, 1, 0);
        ppmCreateRegisterField(abHCSPARAMS_reg, "N_TT", 0, 24, 4, 1, 0);
        ppmCreateRegisterField(abHCSPARAMS_reg, "PI", 0, 16, 1, 1, 0);
        ppmCreateRegisterField(abHCSPARAMS_reg, "PPC", 0, 4, 1, 1, 0);
    }
    {
        registerHandle abHCCPARAMS_reg = ppmCreateRegister(
            "ab_HCCPARAMS",
            "Host Controller Capability Parameters, offset: 0x108",
            handles.bport1,
            0x108,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.HCCPARAMS.value),
            True
        );

        ppmCreateRegisterField(abHCCPARAMS_reg, "ADC", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(abHCCPARAMS_reg, "ASP", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(abHCCPARAMS_reg, "EECP", 0, 8, 8, 1, 0);
        ppmCreateRegisterField(abHCCPARAMS_reg, "IST", 0, 4, 4, 1, 0);
        ppmCreateRegisterField(abHCCPARAMS_reg, "PFL", 0, 1, 1, 1, 0);
    }
    {
        ppmCreateRegister(
            "ab_DCIVERSION",
            "Device Controller Interface Version, offset: 0x120",
            handles.bport1,
            0x120,
            4,
            readDCIVersion,
            0,
            view32,
            &(bport1_ab_data.DCIVERSION.value),
            True
        );
    }
    {
        registerHandle abDCCPARAMS_reg = ppmCreateRegister(
            "ab_DCCPARAMS",
            "Device Controller Capability Parameters, offset: 0x124",
            handles.bport1,
            0x124,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.DCCPARAMS.value),
            True
        );

        ppmCreateRegisterField(abDCCPARAMS_reg, "DC", 0, 7, 1, 1, 0);
        ppmCreateRegisterField(abDCCPARAMS_reg, "DEN", 0, 0, 5, 1, 0);
        ppmCreateRegisterField(abDCCPARAMS_reg, "HC", 0, 8, 1, 1, 0);
    }
    {
        registerHandle abUSBCMD_reg = ppmCreateRegister(
            "ab_USBCMD",
            "USB Command Register, offset: 0x140",
            handles.bport1,
            0x140,
            4,
            read_32,
            bport1_ab_USBCMD_maskWrite,
            view32,
            &(bport1_ab_data.USBCMD.value),
            True
        );

        ppmCreateRegisterField(abUSBCMD_reg, "ASE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abUSBCMD_reg, "ASP", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abUSBCMD_reg, "ASPE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abUSBCMD_reg, "ATDTW", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abUSBCMD_reg, "FS1", 0, 2, 2, 1, 1);
        ppmCreateRegisterField(abUSBCMD_reg, "FS2", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abUSBCMD_reg, "IAA", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abUSBCMD_reg, "ITC", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abUSBCMD_reg, "PSE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abUSBCMD_reg, "RS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abUSBCMD_reg, "RST", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abUSBCMD_reg, "SUTW", 0, 13, 1, 1, 1);
    }
    {
        registerHandle abUSBSTS_reg = ppmCreateRegister(
            "ab_USBSTS",
            "USB Status Register, offset: 0x144",
            handles.bport1,
            0x144,
            4,
            read_32,
            bport1_ab_USBSTS_maskWrite,
            view32,
            &(bport1_ab_data.USBSTS.value),
            True
        );

        ppmCreateRegisterField(abUSBSTS_reg, "AAI", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abUSBSTS_reg, "AS", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abUSBSTS_reg, "FRI", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abUSBSTS_reg, "HCH", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abUSBSTS_reg, "NAKI", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abUSBSTS_reg, "PCI", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abUSBSTS_reg, "PS", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abUSBSTS_reg, "RCL", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abUSBSTS_reg, "SEI", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abUSBSTS_reg, "SLI", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abUSBSTS_reg, "SRI", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abUSBSTS_reg, "TI0", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abUSBSTS_reg, "TI1", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abUSBSTS_reg, "UEI", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abUSBSTS_reg, "UI", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abUSBSTS_reg, "UPI", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abUSBSTS_reg, "UAI", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abUSBSTS_reg, "ULPII", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abUSBSTS_reg, "URI", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abUSBINTR_reg = ppmCreateRegister(
            "ab_USBINTR",
            "Interrupt Enable Register, offset: 0x148",
            handles.bport1,
            0x148,
            4,
            read_32,
            bport1_ab_USBINTR_maskWrite,
            view32,
            &(bport1_ab_data.USBINTR.value),
            True
        );

        ppmCreateRegisterField(abUSBINTR_reg, "AAE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abUSBINTR_reg, "FRE", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abUSBINTR_reg, "NAKE", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abUSBINTR_reg, "PCE", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abUSBINTR_reg, "SEE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abUSBINTR_reg, "SLE", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abUSBINTR_reg, "SRE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abUSBINTR_reg, "TIE0", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abUSBINTR_reg, "TIE1", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abUSBINTR_reg, "UAIE", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abUSBINTR_reg, "UE", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abUSBINTR_reg, "UEE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abUSBINTR_reg, "ULPIE", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abUSBINTR_reg, "UPIE", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abUSBINTR_reg, "URE", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abFRINDEX_reg = ppmCreateRegister(
            "ab_FRINDEX",
            "USB Frame Index, offset: 0x14C",
            handles.bport1,
            0x14c,
            4,
            read_32,
            bport1_ab_FRINDEX_maskWrite,
            view32,
            &(bport1_ab_data.FRINDEX.value),
            True
        );

        ppmCreateRegisterField(abFRINDEX_reg, "FRINDEX", 0, 0, 14, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_DEVICEADDR",
            "Device_FrameList Base Address, offset: 0x154",
            handles.bport1,
            0x154,
            4,
            readShare154h,
            writeShare154h,
            view32,
            &(bport1_ab_data.DEVICEADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ASYNCLISTADDR",
            "Next Asynch._Enpoint List Address, offset: 0x158",
            handles.bport1,
            0x158,
            4,
            readShare158h,
            writeShare154h,
            view32,
            &(bport1_ab_data.ASYNCLISTADDR.value),
            True
        );
    }
    {
        registerHandle abBURSTSIZE_reg = ppmCreateRegister(
            "ab_BURSTSIZE",
            "Programmable Burst Size, offset: 0x160",
            handles.bport1,
            0x160,
            4,
            read_32,
            bport1_ab_BURSTSIZE_maskWrite,
            view32,
            &(bport1_ab_data.BURSTSIZE.value),
            True
        );

        ppmCreateRegisterField(abBURSTSIZE_reg, "RXPBURST", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abBURSTSIZE_reg, "TXPBURST", 0, 8, 9, 1, 1);
    }
    {
        registerHandle abTXFILLTUNING_reg = ppmCreateRegister(
            "ab_TXFILLTUNING",
            "TX FIFO Fill Tuning, offset: 0x164",
            handles.bport1,
            0x164,
            4,
            read_32,
            bport1_ab_TXFILLTUNING_maskWrite,
            view32,
            &(bport1_ab_data.TXFILLTUNING.value),
            True
        );

        ppmCreateRegisterField(abTXFILLTUNING_reg, "TXFIFOTHRES", 0, 16, 6, 1, 1);
        ppmCreateRegisterField(abTXFILLTUNING_reg, "TXSCHHEALTH", 0, 8, 5, 1, 1);
        ppmCreateRegisterField(abTXFILLTUNING_reg, "TXSCHOH", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abENDPTNAK_reg = ppmCreateRegister(
            "ab_ENDPTNAK",
            "Endpoint NAK, offset: 0x178",
            handles.bport1,
            0x178,
            4,
            read_32,
            bport1_ab_ENDPTNAK_maskWrite,
            view32,
            &(bport1_ab_data.ENDPTNAK.value),
            True
        );

        ppmCreateRegisterField(abENDPTNAK_reg, "EPRN", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(abENDPTNAK_reg, "EPTN", 0, 16, 6, 1, 1);
    }
    {
        registerHandle abENDPTNAKEN_reg = ppmCreateRegister(
            "ab_ENDPTNAKEN",
            "Endpoint NAK Enable, offset: 0x17C",
            handles.bport1,
            0x17c,
            4,
            read_32,
            bport1_ab_ENDPTNAKEN_maskWrite,
            view32,
            &(bport1_ab_data.ENDPTNAKEN.value),
            True
        );

        ppmCreateRegisterField(abENDPTNAKEN_reg, "EPRNE", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(abENDPTNAKEN_reg, "EPTNE", 0, 16, 6, 1, 1);
    }
    {
        registerHandle abPORTSC1_reg = ppmCreateRegister(
            "ab_PORTSC1",
            "Port Status & Control, offset: 0x184",
            handles.bport1,
            0x184,
            4,
            read_32,
            bport1_ab_PORTSC1_maskWrite,
            view32,
            &(bport1_ab_data.PORTSC1.value),
            True
        );

        ppmCreateRegisterField(abPORTSC1_reg, "CCS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "CSC", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "FPR", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "HSP", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "LS", 0, 10, 2, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "OCA", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "OCC", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "PE", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "PEC", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "PFSC", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "PHCD", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "PIC", 0, 14, 2, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "PO", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "PP", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "PR", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "PSPD", 0, 26, 2, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "PTC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "PTS1", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "PTS2", 0, 30, 2, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "PTW", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "STS", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "SUSP", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "WKCN", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "WKDC", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "WKOC", 0, 22, 1, 1, 1);
    }
    {
        registerHandle abOTGSC_reg = ppmCreateRegister(
            "ab_OTGSC",
            "On-The-Go Status & control, offset: 0x1A4",
            handles.bport1,
            0x1a4,
            4,
            read_32,
            bport1_ab_OTGSC_maskWrite,
            view32,
            &(bport1_ab_data.OTGSC.value),
            True
        );

        ppmCreateRegisterField(abOTGSC_reg, "MSS1", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "MSSE1", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "MST1", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "ASV", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "ASVIE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "ASVIS", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "AVV", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "AVVIE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "AVVIS", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "BSE", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "BSEIE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "BSEIS", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "BSV", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "BSVIE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "BSVIS", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "DPIE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "DPIS", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "DPS", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "ID", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "IDIE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "IDIS", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "IDPU", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "OT", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "VD", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abUSBMODE_reg = ppmCreateRegister(
            "ab_USBMODE",
            "USB Device Mode, offset: 0x1A8",
            handles.bport1,
            0x1a8,
            4,
            read_32,
            bport1_ab_USBMODE_maskWrite,
            view32,
            &(bport1_ab_data.USBMODE.value),
            True
        );

        ppmCreateRegisterField(abUSBMODE_reg, "CM", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(abUSBMODE_reg, "ES", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abUSBMODE_reg, "SDIS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abUSBMODE_reg, "SLOM", 0, 3, 1, 1, 1);
    }
    {
        registerHandle abENDPTSETUPSTAT_reg = ppmCreateRegister(
            "ab_ENDPTSETUPSTAT",
            "Endpoint Setup Status, offset: 0x1AC",
            handles.bport1,
            0x1ac,
            4,
            read_32,
            bport1_ab_ENDPTSETUPSTAT_maskWrite,
            view32,
            &(bport1_ab_data.ENDPTSETUPSTAT.value),
            True
        );

        ppmCreateRegisterField(abENDPTSETUPSTAT_reg, "ENDPTSETUPSTAT", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abENDPTPRIME_reg = ppmCreateRegister(
            "ab_ENDPTPRIME",
            "Endpoint Initialization, offset: 0x1B0",
            handles.bport1,
            0x1b0,
            4,
            read_32,
            bport1_ab_ENDPTPRIME_maskWrite,
            view32,
            &(bport1_ab_data.ENDPTPRIME.value),
            True
        );

        ppmCreateRegisterField(abENDPTPRIME_reg, "PERB", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(abENDPTPRIME_reg, "PETB", 0, 16, 6, 1, 1);
    }
    {
        registerHandle abENDPTFLUSH_reg = ppmCreateRegister(
            "ab_ENDPTFLUSH",
            "Endpoint De-Initialize, offset: 0x1B4",
            handles.bport1,
            0x1b4,
            4,
            read_32,
            bport1_ab_ENDPTFLUSH_maskWrite,
            view32,
            &(bport1_ab_data.ENDPTFLUSH.value),
            True
        );

        ppmCreateRegisterField(abENDPTFLUSH_reg, "FERB", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(abENDPTFLUSH_reg, "FETB", 0, 16, 6, 1, 1);
    }
    {
        registerHandle abENDPTSTAT_reg = ppmCreateRegister(
            "ab_ENDPTSTAT",
            "Endpoint Status, offset: 0x1B8",
            handles.bport1,
            0x1b8,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.ENDPTSTAT.value),
            True
        );

        ppmCreateRegisterField(abENDPTSTAT_reg, "ERBR", 0, 0, 6, 1, 0);
        ppmCreateRegisterField(abENDPTSTAT_reg, "ETBR", 0, 16, 6, 1, 0);
    }
    {
        registerHandle abENDPTCOMPLETE_reg = ppmCreateRegister(
            "ab_ENDPTCOMPLETE",
            "Endpoint Complete, offset: 0x1BC",
            handles.bport1,
            0x1bc,
            4,
            read_32,
            bport1_ab_ENDPTCOMPLETE_maskWrite,
            view32,
            &(bport1_ab_data.ENDPTCOMPLETE.value),
            True
        );

        ppmCreateRegisterField(abENDPTCOMPLETE_reg, "ERCE", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(abENDPTCOMPLETE_reg, "ETCE", 0, 16, 6, 1, 1);
    }
    {
        registerHandle abENDPTCTRL0_reg = ppmCreateRegister(
            "ab_ENDPTCTRL0",
            "Endpoint Control0, offset: 0x1C0",
            handles.bport1,
            0x1c0,
            4,
            read_32,
            bport1_ab_ENDPTCTRL0_maskWrite,
            view32,
            &(bport1_ab_data.ENDPTCTRL0.value),
            True
        );

        ppmCreateRegisterField(abENDPTCTRL0_reg, "RXE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL0_reg, "RXS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL0_reg, "RXT", 0, 2, 2, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL0_reg, "TXE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL0_reg, "TXS", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL0_reg, "TXT", 0, 18, 2, 1, 1);
    }
    {
        registerHandle abENDPTCTRL1_reg = ppmCreateRegister(
            "ab_ENDPTCTRL1",
            "Endpoint Control1, offset: 0x1C4",
            handles.bport1,
            0x1c4,
            4,
            read_32,
            bport1_ab_ENDPTCTRL1_maskWrite,
            view32,
            &(bport1_ab_data.ENDPTCTRL1.value),
            True
        );

        ppmCreateRegisterField(abENDPTCTRL1_reg, "RXD", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL1_reg, "RXE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL1_reg, "RXI", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL1_reg, "RXR", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL1_reg, "RXS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL1_reg, "RXT", 0, 2, 2, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL1_reg, "TXD", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL1_reg, "TXE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL1_reg, "TXI", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL1_reg, "TXR", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL1_reg, "TXS", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL1_reg, "TXT", 0, 18, 2, 1, 1);
    }
    {
        registerHandle abENDPTCTRL2_reg = ppmCreateRegister(
            "ab_ENDPTCTRL2",
            "Endpoint Control2, offset: 0x1C8",
            handles.bport1,
            0x1c8,
            4,
            read_32,
            bport1_ab_ENDPTCTRL2_maskWrite,
            view32,
            &(bport1_ab_data.ENDPTCTRL2.value),
            True
        );

        ppmCreateRegisterField(abENDPTCTRL2_reg, "RXD", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL2_reg, "RXE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL2_reg, "RXI", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL2_reg, "RXR", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL2_reg, "RXS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL2_reg, "RXT", 0, 2, 2, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL2_reg, "TXD", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL2_reg, "TXE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL2_reg, "TXI", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL2_reg, "TXR", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL2_reg, "TXS", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL2_reg, "TXT", 0, 18, 2, 1, 1);
    }
    {
        registerHandle abENDPTCTRL3_reg = ppmCreateRegister(
            "ab_ENDPTCTRL3",
            "Endpoint Control3, offset: 0x1Cc",
            handles.bport1,
            0x1cc,
            4,
            read_32,
            bport1_ab_ENDPTCTRL3_maskWrite,
            view32,
            &(bport1_ab_data.ENDPTCTRL3.value),
            True
        );

        ppmCreateRegisterField(abENDPTCTRL3_reg, "RXD", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL3_reg, "RXE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL3_reg, "RXI", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL3_reg, "RXR", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL3_reg, "RXS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL3_reg, "RXT", 0, 2, 2, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL3_reg, "TXD", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL3_reg, "TXE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL3_reg, "TXI", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL3_reg, "TXR", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL3_reg, "TXS", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL3_reg, "TXT", 0, 18, 2, 1, 1);
    }
    {
        registerHandle abENDPTCTRL4_reg = ppmCreateRegister(
            "ab_ENDPTCTRL4",
            "Endpoint Control4, offset: 0x1d0",
            handles.bport1,
            0x1d0,
            4,
            read_32,
            bport1_ab_ENDPTCTRL4_maskWrite,
            view32,
            &(bport1_ab_data.ENDPTCTRL4.value),
            True
        );

        ppmCreateRegisterField(abENDPTCTRL4_reg, "RXD", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL4_reg, "RXE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL4_reg, "RXI", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL4_reg, "RXR", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL4_reg, "RXS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL4_reg, "RXT", 0, 2, 2, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL4_reg, "TXD", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL4_reg, "TXE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL4_reg, "TXI", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL4_reg, "TXR", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL4_reg, "TXS", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL4_reg, "TXT", 0, 18, 2, 1, 1);
    }
    {
        registerHandle abENDPTCTRL5_reg = ppmCreateRegister(
            "ab_ENDPTCTRL5",
            "Endpoint Control5, offset: 0x1d4",
            handles.bport1,
            0x1d4,
            4,
            read_32,
            bport1_ab_ENDPTCTRL5_maskWrite,
            view32,
            &(bport1_ab_data.ENDPTCTRL5.value),
            True
        );

        ppmCreateRegisterField(abENDPTCTRL5_reg, "RXD", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL5_reg, "RXE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL5_reg, "RXI", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL5_reg, "RXR", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL5_reg, "RXS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL5_reg, "RXT", 0, 2, 2, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL5_reg, "TXD", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL5_reg, "TXE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL5_reg, "TXI", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL5_reg, "TXR", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL5_reg, "TXS", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abENDPTCTRL5_reg, "TXT", 0, 18, 2, 1, 1);
    }
    {
        registerHandle abCTRL_reg = ppmCreateRegister(
            "ab_CTRL",
            "Non-Core Register: USB Control Register",
            handles.bport1,
            0x800,
            4,
            read_32,
            bport1_ab_CTRL_maskWrite,
            view32,
            &(bport1_ab_data.CTRL.value),
            True
        );

        ppmCreateRegisterField(abCTRL_reg, "WIR", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "VBUS_CH_INT_MASK", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "VBUS_CH_STAT", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "WKUP_VBUS_EN", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "WKUP_SW", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "WKUP_SW_EN", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "ETMI_ON_CLOSK", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "SUSPENDM", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "RESET", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "WIE", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "PM", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "OVER_CUR_POL", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abCTRL_reg, "OVER_CUR_DIS", 0, 7, 1, 1, 1);
    }
    {
        registerHandle abPHY_reg = ppmCreateRegister(
            "ab_PHY",
            "Non-Core Register: USB PHY Control Register",
            handles.bport1,
            0x818,
            4,
            read_32,
            PHYWrite1c,
            view32,
            &(bport1_ab_data.PHY.value),
            True
        );

        ppmCreateRegisterField(abPHY_reg, "UTMI_CLK_VLD", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abPHY_reg, "CHRGDET", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPHY_reg, "CHRGDET_INT_EN", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPHY_reg, "CHRGDET_INT_FLG", 0, 0, 1, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.PHY.value = (Uns32)(bport1_ab_data.PHY.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CTRL.value = (Uns32)(bport1_ab_data.CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00003000));
        bport1_ab_data.ENDPTCTRL5.value = (Uns32)(bport1_ab_data.ENDPTCTRL5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ENDPTCTRL4.value = (Uns32)(bport1_ab_data.ENDPTCTRL4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ENDPTCTRL3.value = (Uns32)(bport1_ab_data.ENDPTCTRL3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ENDPTCTRL2.value = (Uns32)(bport1_ab_data.ENDPTCTRL2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ENDPTCTRL1.value = (Uns32)(bport1_ab_data.ENDPTCTRL1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ENDPTCTRL0.value = (Uns32)(bport1_ab_data.ENDPTCTRL0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00800080));
        bport1_ab_data.ENDPTCOMPLETE.value = (Uns32)(bport1_ab_data.ENDPTCOMPLETE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ENDPTSTAT.value = (Uns32)(bport1_ab_data.ENDPTSTAT.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ENDPTFLUSH.value = (Uns32)(bport1_ab_data.ENDPTFLUSH.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ENDPTPRIME.value = (Uns32)(bport1_ab_data.ENDPTPRIME.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ENDPTSETUPSTAT.value = (Uns32)(bport1_ab_data.ENDPTSETUPSTAT.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.USBMODE.value = (Uns32)(bport1_ab_data.USBMODE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00005002));
        bport1_ab_data.OTGSC.value = (Uns32)(bport1_ab_data.OTGSC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000220));
        bport1_ab_data.PORTSC1.value = (Uns32)(bport1_ab_data.PORTSC1.value & ~(0xffffffff)) | ((0xffffffff) & (0x10000000));
        bport1_ab_data.ENDPTNAKEN.value = (Uns32)(bport1_ab_data.ENDPTNAKEN.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ENDPTNAK.value = (Uns32)(bport1_ab_data.ENDPTNAK.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TXFILLTUNING.value = (Uns32)(bport1_ab_data.TXFILLTUNING.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000808));
        bport1_ab_data.BURSTSIZE.value = (Uns32)(bport1_ab_data.BURSTSIZE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001010));
        bport1_ab_data.ASYNCLISTADDR.value = (Uns32)(bport1_ab_data.ASYNCLISTADDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DEVICEADDR.value = (Uns32)(bport1_ab_data.DEVICEADDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.FRINDEX.value = (Uns32)(bport1_ab_data.FRINDEX.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.USBINTR.value = (Uns32)(bport1_ab_data.USBINTR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.USBSTS.value = (Uns32)(bport1_ab_data.USBSTS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.USBCMD.value = (Uns32)(bport1_ab_data.USBCMD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00080000));
        bport1_ab_data.DCCPARAMS.value = (Uns32)(bport1_ab_data.DCCPARAMS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000186));
        bport1_ab_data.DCIVERSION.value = (Uns32)(bport1_ab_data.DCIVERSION.value & ~(0xffffffff)) | ((0xffffffff) & (0x0001));
        bport1_ab_data.HCCPARAMS.value = (Uns32)(bport1_ab_data.HCCPARAMS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000006));
        bport1_ab_data.HCSPARAMS.value = (Uns32)(bport1_ab_data.HCSPARAMS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00010011));
        bport1_ab_data.CAPVERSION.value = (Uns32)(bport1_ab_data.CAPVERSION.value & ~(0xffffffff)) | ((0xffffffff) & (0x40));
        bport1_ab_data.SBUSCFG.value = (Uns32)(bport1_ab_data.SBUSCFG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bport1_ab_data.GPTIMER1CTRL.value = (Uns32)(bport1_ab_data.GPTIMER1CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPTIMER1LD.value = (Uns32)(bport1_ab_data.GPTIMER1LD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPTIMER0CTRL.value = (Uns32)(bport1_ab_data.GPTIMER0CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPTIMER0LD.value = (Uns32)(bport1_ab_data.GPTIMER0LD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.HWRXBUF.value = (Uns32)(bport1_ab_data.HWRXBUF.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000904));
        bport1_ab_data.HWTXBUF.value = (Uns32)(bport1_ab_data.HWTXBUF.value & ~(0xffffffff)) | ((0xffffffff) & (0x80080b04));
        bport1_ab_data.HWDEVICE.value = (Uns32)(bport1_ab_data.HWDEVICE.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000000d));
        bport1_ab_data.HWHOST.value = (Uns32)(bport1_ab_data.HWHOST.value & ~(0xffffffff)) | ((0xffffffff) & (0x10020001));
        bport1_ab_data.HWGENERAL.value = (Uns32)(bport1_ab_data.HWGENERAL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000015));
        bport1_ab_data.ID.value = (Uns32)(bport1_ab_data.ID.value & ~(0xffffffff)) | ((0xffffffff) & (0xe481fa05));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the USB peripheral used on the Freescale Vybrid platform");
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


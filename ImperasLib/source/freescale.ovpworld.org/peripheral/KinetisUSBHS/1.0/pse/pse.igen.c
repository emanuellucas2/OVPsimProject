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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisUSBHS", "Example");
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

static PPM_WRITE_CB(bport1_ab_ASYNCLISTADDR_maskWrite) {
    bport1_ab_data.ASYNCLISTADDR.value = (bport1_ab_data.ASYNCLISTADDR.value & BPORT1_AB_ASYNCLISTADDR_WRNMASK) | (data & BPORT1_AB_ASYNCLISTADDR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_BURSTSIZE_maskWrite) {
    bport1_ab_data.BURSTSIZE.value = (bport1_ab_data.BURSTSIZE.value & BPORT1_AB_BURSTSIZE_WRNMASK) | (data & BPORT1_AB_BURSTSIZE_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DEVICEADDR_maskWrite) {
    bport1_ab_data.DEVICEADDR.value = (bport1_ab_data.DEVICEADDR.value & BPORT1_AB_DEVICEADDR_WRNMASK) | (data & BPORT1_AB_DEVICEADDR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPTNAKEN_maskWrite) {
    bport1_ab_data.ENDPTNAKEN.value = (bport1_ab_data.ENDPTNAKEN.value & BPORT1_AB_ENDPTNAKEN_WRNMASK) | (data & BPORT1_AB_ENDPTNAKEN_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPTNAK_maskWrite) {
    bport1_ab_data.ENDPTNAK.value = (bport1_ab_data.ENDPTNAK.value & BPORT1_AB_ENDPTNAK_WRNMASK) | (data & BPORT1_AB_ENDPTNAK_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_EPCOMPLETE_maskWrite) {
    bport1_ab_data.EPCOMPLETE.value = (bport1_ab_data.EPCOMPLETE.value & BPORT1_AB_EPCOMPLETE_WRNMASK) | (data & BPORT1_AB_EPCOMPLETE_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_EPCR0_maskWrite) {
    bport1_ab_data.EPCR0.value = (bport1_ab_data.EPCR0.value & BPORT1_AB_EPCR0_WRNMASK) | (data & BPORT1_AB_EPCR0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_EPCR1_maskWrite) {
    bport1_ab_data.EPCR1.value = (bport1_ab_data.EPCR1.value & BPORT1_AB_EPCR1_WRNMASK) | (data & BPORT1_AB_EPCR1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_EPCR2_maskWrite) {
    bport1_ab_data.EPCR2.value = (bport1_ab_data.EPCR2.value & BPORT1_AB_EPCR2_WRNMASK) | (data & BPORT1_AB_EPCR2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_EPCR3_maskWrite) {
    bport1_ab_data.EPCR3.value = (bport1_ab_data.EPCR3.value & BPORT1_AB_EPCR3_WRNMASK) | (data & BPORT1_AB_EPCR3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_EPFLUSH_maskWrite) {
    bport1_ab_data.EPFLUSH.value = (bport1_ab_data.EPFLUSH.value & BPORT1_AB_EPFLUSH_WRNMASK) | (data & BPORT1_AB_EPFLUSH_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_EPPRIME_maskWrite) {
    bport1_ab_data.EPPRIME.value = (bport1_ab_data.EPPRIME.value & BPORT1_AB_EPPRIME_WRNMASK) | (data & BPORT1_AB_EPPRIME_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_EPSETUPSR_maskWrite) {
    bport1_ab_data.EPSETUPSR.value = (bport1_ab_data.EPSETUPSR.value & BPORT1_AB_EPSETUPSR_WRNMASK) | (data & BPORT1_AB_EPSETUPSR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FRINDEX_maskWrite) {
    bport1_ab_data.FRINDEX.value = (bport1_ab_data.FRINDEX.value & BPORT1_AB_FRINDEX_WRNMASK) | (data & BPORT1_AB_FRINDEX_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_GPTIMER0CTL_maskWrite) {
    bport1_ab_data.GPTIMER0CTL.value = (bport1_ab_data.GPTIMER0CTL.value & BPORT1_AB_GPTIMER0CTL_WRNMASK) | (data & BPORT1_AB_GPTIMER0CTL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_GPTIMER0LD_maskWrite) {
    bport1_ab_data.GPTIMER0LD.value = (bport1_ab_data.GPTIMER0LD.value & BPORT1_AB_GPTIMER0LD_WRNMASK) | (data & BPORT1_AB_GPTIMER0LD_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_GPTIMER1CTL_maskWrite) {
    bport1_ab_data.GPTIMER1CTL.value = (bport1_ab_data.GPTIMER1CTL.value & BPORT1_AB_GPTIMER1CTL_WRNMASK) | (data & BPORT1_AB_GPTIMER1CTL_WRMASK);
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

static PPM_WRITE_CB(bport1_ab_ULPI_VIEWPORT_maskWrite) {
    bport1_ab_data.ULPI_VIEWPORT.value = (bport1_ab_data.ULPI_VIEWPORT.value & BPORT1_AB_ULPI_VIEWPORT_WRNMASK) | (data & BPORT1_AB_ULPI_VIEWPORT_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_USBCMD_maskWrite) {
    bport1_ab_data.USBCMD.value = (bport1_ab_data.USBCMD.value & BPORT1_AB_USBCMD_WRNMASK) | (data & BPORT1_AB_USBCMD_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_USBGENCTRL_maskWrite) {
    bport1_ab_data.USBGENCTRL.value = (bport1_ab_data.USBGENCTRL.value & BPORT1_AB_USBGENCTRL_WRNMASK) | (data & BPORT1_AB_USBGENCTRL_WRMASK);
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
            "Identification Register, offset: 0x0 ",
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
        ppmCreateRegisterField(abID_reg, "TAG", 0, 16, 5, 1, 0);
        ppmCreateRegisterField(abID_reg, "REVISION", 0, 21, 4, 1, 0);
        ppmCreateRegisterField(abID_reg, "VERSION", 0, 25, 4, 1, 0);
        ppmCreateRegisterField(abID_reg, "VERSIONID", 0, 29, 3, 1, 0);
    }
    {
        registerHandle abHWGENERAL_reg = ppmCreateRegister(
            "ab_HWGENERAL",
            "General Hardware Parameters Register, offset: 0x4 ",
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
        ppmCreateRegisterField(abHWGENERAL_reg, "SM", 0, 9, 2, 1, 0);
    }
    {
        registerHandle abHWHOST_reg = ppmCreateRegister(
            "ab_HWHOST",
            "Host Hardware Parameters Register, offset: 0x8 ",
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
        ppmCreateRegisterField(abHWHOST_reg, "TTASY", 0, 16, 8, 1, 0);
        ppmCreateRegisterField(abHWHOST_reg, "TTPER", 0, 24, 8, 1, 0);
    }
    {
        registerHandle abHWDEVICE_reg = ppmCreateRegister(
            "ab_HWDEVICE",
            "Device Hardware Parameters Register, offset: 0xC ",
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
            "Transmit Buffer Hardware Parameters Register, offset: 0x10 ",
            handles.bport1,
            0x10,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.HWTXBUF.value),
            True
        );

        ppmCreateRegisterField(abHWTXBUF_reg, "TXADD", 0, 8, 8, 1, 0);
        ppmCreateRegisterField(abHWTXBUF_reg, "TXBURST", 0, 0, 8, 1, 0);
        ppmCreateRegisterField(abHWTXBUF_reg, "TXCHANADD", 0, 16, 8, 1, 0);
        ppmCreateRegisterField(abHWTXBUF_reg, "TXLC", 0, 31, 1, 1, 0);
    }
    {
        registerHandle abHWRXBUF_reg = ppmCreateRegister(
            "ab_HWRXBUF",
            "Receive Buffer Hardware Parameters Register, offset: 0x14 ",
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
            "General Purpose Timer n Load Register, offset: 0x80 ",
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
        registerHandle abGPTIMER0CTL_reg = ppmCreateRegister(
            "ab_GPTIMER0CTL",
            "General Purpose Timer n Control Register, offset: 0x84 ",
            handles.bport1,
            0x84,
            4,
            read_32,
            bport1_ab_GPTIMER0CTL_maskWrite,
            view32,
            &(bport1_ab_data.GPTIMER0CTL.value),
            True
        );

        ppmCreateRegisterField(abGPTIMER0CTL_reg, "GPTCNT", 0, 0, 24, 1, 1);
        ppmCreateRegisterField(abGPTIMER0CTL_reg, "MODE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abGPTIMER0CTL_reg, "RST", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abGPTIMER0CTL_reg, "RUN", 0, 31, 1, 1, 1);
    }
    {
        registerHandle abGPTIMER1LD_reg = ppmCreateRegister(
            "ab_GPTIMER1LD",
            "General Purpose Timer n Load Register, offset: 0x88 ",
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
        registerHandle abGPTIMER1CTL_reg = ppmCreateRegister(
            "ab_GPTIMER1CTL",
            "General Purpose Timer n Control Register, offset: 0x8C ",
            handles.bport1,
            0x8c,
            4,
            read_32,
            bport1_ab_GPTIMER1CTL_maskWrite,
            view32,
            &(bport1_ab_data.GPTIMER1CTL.value),
            True
        );

        ppmCreateRegisterField(abGPTIMER1CTL_reg, "GPTCNT", 0, 0, 24, 1, 1);
        ppmCreateRegisterField(abGPTIMER1CTL_reg, "MODE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abGPTIMER1CTL_reg, "RST", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abGPTIMER1CTL_reg, "RUN", 0, 31, 1, 1, 1);
    }
    {
        registerHandle abSBUSCFG_reg = ppmCreateRegister(
            "ab_SBUSCFG",
            "System Bus Interface Configuration Register, offset: 0x90 ",
            handles.bport1,
            0x90,
            4,
            read_32,
            bport1_ab_SBUSCFG_maskWrite,
            view32,
            &(bport1_ab_data.SBUSCFG.value),
            True
        );

        ppmCreateRegisterField(abSBUSCFG_reg, "BURSTMODE", 0, 0, 3, 1, 1);
    }
    {
        registerHandle abHCIVERSION_reg = ppmCreateRegister(
            "ab_HCIVERSION",
            "Host Controller Interface Version Register, offset: 0x100 ",
            handles.bport1,
            0x100,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.HCIVERSION.value),
            True
        );

        ppmCreateRegisterField(abHCIVERSION_reg, "HCIVERSION", 0, 16, 16, 1, 0);
        ppmCreateRegisterField(abHCIVERSION_reg, "CAPLENGTH", 0, 0, 8, 1, 0);
    }
    {
        registerHandle abHCSPARAMS_reg = ppmCreateRegister(
            "ab_HCSPARAMS",
            "Host Controller Structural Parameters Register, offset: 0x104 ",
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
            "Host Controller Capability Parameters Register, offset: 0x108 ",
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
        registerHandle abDCIVERSION_reg = ppmCreateRegister(
            "ab_DCIVERSION",
            "Device Controller Interface Version, offset: 0x122, 16bit ",
            handles.bport1,
            0x120,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.DCIVERSION.value),
            True
        );

        ppmCreateRegisterField(abDCIVERSION_reg, "DCIVERSION", 0, 0, 16, 1, 0);
    }
    {
        registerHandle abDCCPARAMS_reg = ppmCreateRegister(
            "ab_DCCPARAMS",
            "Device Controller Capability Parameters, offset: 0x124 ",
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
            "USB Command Register, offset: 0x140 ",
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
        ppmCreateRegisterField(abUSBCMD_reg, "FS", 0, 2, 2, 1, 1);
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
            "USB Status Register, offset: 0x144 ",
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
        ppmCreateRegisterField(abUSBSTS_reg, "UAI", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abUSBSTS_reg, "UEI", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abUSBSTS_reg, "UI", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abUSBSTS_reg, "ULPII", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abUSBSTS_reg, "UPI", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abUSBSTS_reg, "URI", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abUSBINTR_reg = ppmCreateRegister(
            "ab_USBINTR",
            "USB Interrupt Enable Register, offset: 0x148 ",
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
            "Frame Index Register, offset: 0x14C ",
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
        registerHandle abDEVICEADDR_reg = ppmCreateRegister(
            "ab_DEVICEADDR",
            "Device Address Register, offset: 0x154 ",
            handles.bport1,
            0x154,
            4,
            read_32,
            bport1_ab_DEVICEADDR_maskWrite,
            view32,
            &(bport1_ab_data.DEVICEADDR.value),
            True
        );

        ppmCreateRegisterField(abDEVICEADDR_reg, "USBADR", 0, 25, 7, 1, 1);
        ppmCreateRegisterField(abDEVICEADDR_reg, "USBADRA", 0, 24, 1, 1, 1);
    }
    {
        registerHandle abASYNCLISTADDR_reg = ppmCreateRegister(
            "ab_ASYNCLISTADDR",
            "Current Asynchronous List Address Register, offset: 0x158 ",
            handles.bport1,
            0x158,
            4,
            read_32,
            bport1_ab_ASYNCLISTADDR_maskWrite,
            view32,
            &(bport1_ab_data.ASYNCLISTADDR.value),
            True
        );

        ppmCreateRegisterField(abASYNCLISTADDR_reg, "ASYBASE", 0, 5, 27, 1, 1);
    }
    {
        registerHandle abTTCTRL_reg = ppmCreateRegister(
            "ab_TTCTRL",
            "Host TT Asynchronous Buffer Control, offset: 0x15C ",
            handles.bport1,
            0x15c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.TTCTRL.value),
            True
        );

        ppmCreateRegisterField(abTTCTRL_reg, "TTHA", 0, 24, 7, 1, 1);
    }
    {
        registerHandle abBURSTSIZE_reg = ppmCreateRegister(
            "ab_BURSTSIZE",
            "Master Interface Data Burst Size Register, offset: 0x160 ",
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
        ppmCreateRegisterField(abBURSTSIZE_reg, "TXPBURST", 0, 8, 8, 1, 1);
    }
    {
        registerHandle abTXFILLTUNING_reg = ppmCreateRegister(
            "ab_TXFILLTUNING",
            "Transmit FIFO Tuning Control Register, offset: 0x164 ",
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
        ppmCreateRegisterField(abTXFILLTUNING_reg, "TXSCHOH", 0, 0, 7, 1, 1);
    }
    {
        registerHandle abULPI_VIEWPORT_reg = ppmCreateRegister(
            "ab_ULPI_VIEWPORT",
            "ULPI Register Access, offset: 0x170 ",
            handles.bport1,
            0x170,
            4,
            read_32,
            bport1_ab_ULPI_VIEWPORT_maskWrite,
            view32,
            &(bport1_ab_data.ULPI_VIEWPORT.value),
            True
        );

        ppmCreateRegisterField(abULPI_VIEWPORT_reg, "ULPI_ADDR", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abULPI_VIEWPORT_reg, "ULPI_DATRD", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abULPI_VIEWPORT_reg, "ULPI_DATWR", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abULPI_VIEWPORT_reg, "ULPI_PORT", 0, 24, 3, 1, 1);
        ppmCreateRegisterField(abULPI_VIEWPORT_reg, "ULPI_RUN", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abULPI_VIEWPORT_reg, "ULPI_RW", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abULPI_VIEWPORT_reg, "ULPI_SS", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(abULPI_VIEWPORT_reg, "ULPI_WU", 0, 31, 1, 1, 1);
    }
    {
        registerHandle abENDPTNAK_reg = ppmCreateRegister(
            "ab_ENDPTNAK",
            "ULPI Register Access, offset: 0x170 ",
            handles.bport1,
            0x178,
            4,
            read_32,
            bport1_ab_ENDPTNAK_maskWrite,
            view32,
            &(bport1_ab_data.ENDPTNAK.value),
            True
        );

        ppmCreateRegisterField(abENDPTNAK_reg, "EPTNE", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abENDPTNAK_reg, "EPRNE", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abENDPTNAKEN_reg = ppmCreateRegister(
            "ab_ENDPTNAKEN",
            "ULPI Register Access, offset: 0x170 ",
            handles.bport1,
            0x17c,
            4,
            read_32,
            bport1_ab_ENDPTNAKEN_maskWrite,
            view32,
            &(bport1_ab_data.ENDPTNAKEN.value),
            True
        );

        ppmCreateRegisterField(abENDPTNAKEN_reg, "EPTNE", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abENDPTNAKEN_reg, "EPRNE", 0, 0, 4, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_CONFIGFLAG",
            "Configure Flag Register, offset: 0x180 ",
            handles.bport1,
            0x180,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CONFIGFLAG.value),
            True
        );
    }
    {
        registerHandle abPORTSC1_reg = ppmCreateRegister(
            "ab_PORTSC1",
            "Port Status and Control Registers, offset: 0x184 ",
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
        ppmCreateRegisterField(abPORTSC1_reg, "PTS", 0, 30, 2, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "SUSP", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "WKCN", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "WKDS", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abPORTSC1_reg, "WKOC", 0, 22, 1, 1, 1);
    }
    {
        registerHandle abOTGSC_reg = ppmCreateRegister(
            "ab_OTGSC",
            "On-the-Go Status and Control Register, offset: 0x1A4 ",
            handles.bport1,
            0x1a4,
            4,
            read_32,
            bport1_ab_OTGSC_maskWrite,
            view32,
            &(bport1_ab_data.OTGSC.value),
            True
        );

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
        ppmCreateRegisterField(abOTGSC_reg, "DP", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "DPIE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "DPIS", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "DPS", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "ID", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "IDIE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "IDIS", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "IDPU", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "MSE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "MSS", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "MST", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "OT", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "VC", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "VD", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "HABA", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abOTGSC_reg, "HAAR", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abUSBMODE_reg = ppmCreateRegister(
            "ab_USBMODE",
            "USB Mode Register, offset: 0x1A8 ",
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
        ppmCreateRegisterField(abUSBMODE_reg, "TXHSD", 0, 12, 3, 1, 1);
    }
    {
        registerHandle abEPSETUPSR_reg = ppmCreateRegister(
            "ab_EPSETUPSR",
            "Endpoint Setup Status Register, offset: 0x1AC ",
            handles.bport1,
            0x1ac,
            4,
            read_32,
            bport1_ab_EPSETUPSR_maskWrite,
            view32,
            &(bport1_ab_data.EPSETUPSR.value),
            True
        );

        ppmCreateRegisterField(abEPSETUPSR_reg, "EPSETUPSTAT", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abEPPRIME_reg = ppmCreateRegister(
            "ab_EPPRIME",
            "Endpoint Initialization Register, offset: 0x1B0 ",
            handles.bport1,
            0x1b0,
            4,
            read_32,
            bport1_ab_EPPRIME_maskWrite,
            view32,
            &(bport1_ab_data.EPPRIME.value),
            True
        );

        ppmCreateRegisterField(abEPPRIME_reg, "PERB", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(abEPPRIME_reg, "PETB", 0, 16, 4, 1, 1);
    }
    {
        registerHandle abEPFLUSH_reg = ppmCreateRegister(
            "ab_EPFLUSH",
            "Endpoint Flush Register, offset: 0x1B4 ",
            handles.bport1,
            0x1b4,
            4,
            read_32,
            bport1_ab_EPFLUSH_maskWrite,
            view32,
            &(bport1_ab_data.EPFLUSH.value),
            True
        );

        ppmCreateRegisterField(abEPFLUSH_reg, "FERB", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(abEPFLUSH_reg, "FETB", 0, 16, 4, 1, 1);
    }
    {
        registerHandle abEPSR_reg = ppmCreateRegister(
            "ab_EPSR",
            "Endpoint Status Register, offset: 0x1B8 ",
            handles.bport1,
            0x1b8,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.EPSR.value),
            True
        );

        ppmCreateRegisterField(abEPSR_reg, "ERBR", 0, 0, 4, 1, 0);
        ppmCreateRegisterField(abEPSR_reg, "ETBR", 0, 16, 4, 1, 0);
    }
    {
        registerHandle abEPCOMPLETE_reg = ppmCreateRegister(
            "ab_EPCOMPLETE",
            "Endpoint Complete Register, offset: 0x1BC ",
            handles.bport1,
            0x1bc,
            4,
            read_32,
            bport1_ab_EPCOMPLETE_maskWrite,
            view32,
            &(bport1_ab_data.EPCOMPLETE.value),
            True
        );

        ppmCreateRegisterField(abEPCOMPLETE_reg, "ERCE", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(abEPCOMPLETE_reg, "ETCE", 0, 16, 4, 1, 1);
    }
    {
        registerHandle abEPCR0_reg = ppmCreateRegister(
            "ab_EPCR0",
            "Endpoint Control Register 0, offset: 0x1C0 ",
            handles.bport1,
            0x1c0,
            4,
            read_32,
            bport1_ab_EPCR0_maskWrite,
            view32,
            &(bport1_ab_data.EPCR0.value),
            True
        );

        ppmCreateRegisterField(abEPCR0_reg, "RXE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abEPCR0_reg, "RXS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abEPCR0_reg, "RXT", 0, 2, 2, 1, 1);
        ppmCreateRegisterField(abEPCR0_reg, "TXE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abEPCR0_reg, "TXS", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abEPCR0_reg, "TXT", 0, 18, 2, 1, 1);
    }
    {
        registerHandle abEPCR1_reg = ppmCreateRegister(
            "ab_EPCR1",
            "Endpoint Control Register n, array offset: 0x1C4, array step: 0x4 ",
            handles.bport1,
            0x1c4,
            4,
            read_32,
            bport1_ab_EPCR1_maskWrite,
            view32,
            &(bport1_ab_data.EPCR1.value),
            True
        );

        ppmCreateRegisterField(abEPCR1_reg, "RXD", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abEPCR1_reg, "RXE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abEPCR1_reg, "RXI", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abEPCR1_reg, "RXR", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abEPCR1_reg, "RXS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abEPCR1_reg, "RXT", 0, 2, 2, 1, 1);
        ppmCreateRegisterField(abEPCR1_reg, "TXD", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abEPCR1_reg, "TXE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abEPCR1_reg, "TXI", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abEPCR1_reg, "TXR", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abEPCR1_reg, "TXS", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abEPCR1_reg, "TXT", 0, 18, 2, 1, 1);
    }
    {
        registerHandle abEPCR2_reg = ppmCreateRegister(
            "ab_EPCR2",
            "Endpoint Control Register n, array offset: 0x1C4, array step: 0x4 ",
            handles.bport1,
            0x1c8,
            4,
            read_32,
            bport1_ab_EPCR2_maskWrite,
            view32,
            &(bport1_ab_data.EPCR2.value),
            True
        );

        ppmCreateRegisterField(abEPCR2_reg, "RXD", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abEPCR2_reg, "RXE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abEPCR2_reg, "RXI", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abEPCR2_reg, "RXR", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abEPCR2_reg, "RXS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abEPCR2_reg, "RXT", 0, 2, 2, 1, 1);
        ppmCreateRegisterField(abEPCR2_reg, "TXD", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abEPCR2_reg, "TXE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abEPCR2_reg, "TXI", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abEPCR2_reg, "TXR", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abEPCR2_reg, "TXS", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abEPCR2_reg, "TXT", 0, 18, 2, 1, 1);
    }
    {
        registerHandle abEPCR3_reg = ppmCreateRegister(
            "ab_EPCR3",
            "Endpoint Control Register n, array offset: 0x1C4, array step: 0x4 ",
            handles.bport1,
            0x1cc,
            4,
            read_32,
            bport1_ab_EPCR3_maskWrite,
            view32,
            &(bport1_ab_data.EPCR3.value),
            True
        );

        ppmCreateRegisterField(abEPCR3_reg, "RXD", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abEPCR3_reg, "RXE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abEPCR3_reg, "RXI", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abEPCR3_reg, "RXR", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abEPCR3_reg, "RXS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abEPCR3_reg, "RXT", 0, 2, 2, 1, 1);
        ppmCreateRegisterField(abEPCR3_reg, "TXD", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abEPCR3_reg, "TXE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abEPCR3_reg, "TXI", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abEPCR3_reg, "TXR", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abEPCR3_reg, "TXS", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abEPCR3_reg, "TXT", 0, 18, 2, 1, 1);
    }
    {
        registerHandle abUSBGENCTRL_reg = ppmCreateRegister(
            "ab_USBGENCTRL",
            "General Control Regiser, offset: 0x20 ",
            handles.bport1,
            0x200,
            4,
            read_32,
            bport1_ab_USBGENCTRL_maskWrite,
            view32,
            &(bport1_ab_data.USBGENCTRL.value),
            True
        );

        ppmCreateRegisterField(abUSBGENCTRL_reg, "WU_INT_CLR", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abUSBGENCTRL_reg, "WU_ULPI_EN", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abUSBGENCTRL_reg, "WU_IE", 0, 0, 1, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.USBGENCTRL.value = (Uns32)(bport1_ab_data.USBGENCTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.EPCR3.value = (Uns32)(bport1_ab_data.EPCR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.EPCR2.value = (Uns32)(bport1_ab_data.EPCR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.EPCR1.value = (Uns32)(bport1_ab_data.EPCR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.EPCR0.value = (Uns32)(bport1_ab_data.EPCR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00800080));
        bport1_ab_data.EPCOMPLETE.value = (Uns32)(bport1_ab_data.EPCOMPLETE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.EPSR.value = (Uns32)(bport1_ab_data.EPSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.EPFLUSH.value = (Uns32)(bport1_ab_data.EPFLUSH.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.EPPRIME.value = (Uns32)(bport1_ab_data.EPPRIME.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.EPSETUPSR.value = (Uns32)(bport1_ab_data.EPSETUPSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.USBMODE.value = (Uns32)(bport1_ab_data.USBMODE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00005000));
        bport1_ab_data.OTGSC.value = (Uns32)(bport1_ab_data.OTGSC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001020));
        bport1_ab_data.PORTSC1.value = (Uns32)(bport1_ab_data.PORTSC1.value & ~(0xffffffff)) | ((0xffffffff) & (0x80000000));
        bport1_ab_data.CONFIGFLAG.value = (Uns32)(bport1_ab_data.CONFIGFLAG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bport1_ab_data.ENDPTNAKEN.value = (Uns32)(bport1_ab_data.ENDPTNAKEN.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ENDPTNAK.value = (Uns32)(bport1_ab_data.ENDPTNAK.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ULPI_VIEWPORT.value = (Uns32)(bport1_ab_data.ULPI_VIEWPORT.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TXFILLTUNING.value = (Uns32)(bport1_ab_data.TXFILLTUNING.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.BURSTSIZE.value = (Uns32)(bport1_ab_data.BURSTSIZE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00008080));
        bport1_ab_data.TTCTRL.value = (Uns32)(bport1_ab_data.TTCTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ASYNCLISTADDR.value = (Uns32)(bport1_ab_data.ASYNCLISTADDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DEVICEADDR.value = (Uns32)(bport1_ab_data.DEVICEADDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.FRINDEX.value = (Uns32)(bport1_ab_data.FRINDEX.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.USBINTR.value = (Uns32)(bport1_ab_data.USBINTR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.USBSTS.value = (Uns32)(bport1_ab_data.USBSTS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.USBCMD.value = (Uns32)(bport1_ab_data.USBCMD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00080000));
        bport1_ab_data.DCCPARAMS.value = (Uns32)(bport1_ab_data.DCCPARAMS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000184));
        bport1_ab_data.DCIVERSION.value = (Uns32)(bport1_ab_data.DCIVERSION.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bport1_ab_data.HCCPARAMS.value = (Uns32)(bport1_ab_data.HCCPARAMS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000006));
        bport1_ab_data.HCSPARAMS.value = (Uns32)(bport1_ab_data.HCSPARAMS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00010011));
        bport1_ab_data.HCIVERSION.value = (Uns32)(bport1_ab_data.HCIVERSION.value & ~(0xffffffff)) | ((0xffffffff) & (0x01000040));
        bport1_ab_data.SBUSCFG.value = (Uns32)(bport1_ab_data.SBUSCFG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPTIMER1CTL.value = (Uns32)(bport1_ab_data.GPTIMER1CTL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPTIMER1LD.value = (Uns32)(bport1_ab_data.GPTIMER1LD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPTIMER0CTL.value = (Uns32)(bport1_ab_data.GPTIMER0CTL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPTIMER0LD.value = (Uns32)(bport1_ab_data.GPTIMER0LD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.HWRXBUF.value = (Uns32)(bport1_ab_data.HWRXBUF.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000808));
        bport1_ab_data.HWTXBUF.value = (Uns32)(bport1_ab_data.HWTXBUF.value & ~(0xffffffff)) | ((0xffffffff) & (0x80070908));
        bport1_ab_data.HWDEVICE.value = (Uns32)(bport1_ab_data.HWDEVICE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000009));
        bport1_ab_data.HWHOST.value = (Uns32)(bport1_ab_data.HWHOST.value & ~(0xffffffff)) | ((0xffffffff) & (0x10020001));
        bport1_ab_data.HWGENERAL.value = (Uns32)(bport1_ab_data.HWGENERAL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000085));
        bport1_ab_data.ID.value = (Uns32)(bport1_ab_data.ID.value & ~(0xffffffff)) | ((0xffffffff) & (0xe461fa05));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the USBHS peripheral used on the Freescale Kinetis platform");
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


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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "zynq_7000-usb", "Example");
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
        ppmCreateRegister(
            "ab_ID",
            "IP version and revision, read-only",
            handles.bport1,
            0x0,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.ID.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_HWGENERAL",
            "Misc IP config constants, read-only",
            handles.bport1,
            0x4,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.HWGENERAL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_HWHOST",
            "Host Mode IP config constants, read-only",
            handles.bport1,
            0x8,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.HWHOST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_HWDEVICE",
            "Device Mode IP config constants, read-only",
            handles.bport1,
            0xc,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.HWDEVICE.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_HWTXBUF",
            "TxBuffer IP config constants, read-only",
            handles.bport1,
            0x10,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.HWTXBUF.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_HWRXBUF",
            "IP constants, RX buffer constants, read-only",
            handles.bport1,
            0x14,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.HWRXBUF.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GPTIMER0LD",
            "GP Timer 0 Load Value",
            handles.bport1,
            0x80,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.GPTIMER0LD.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GPTIMER0CTRL",
            "GP Timer 1 Control",
            handles.bport1,
            0x84,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.GPTIMER0CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GPTIMER1LD",
            "GP Timer 1 Load Value",
            handles.bport1,
            0x88,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.GPTIMER1LD.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GPTIMER1CTRL",
            "GP Timer 1 Control",
            handles.bport1,
            0x8c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.GPTIMER1CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_SBUSCFG",
            "DMA Master AHB Burst Mode ",
            handles.bport1,
            0x90,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.SBUSCFG.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CAPLENGTH_HCIVERSION",
            "EHCI Addr Space and HCI constants, read-only",
            handles.bport1,
            0x100,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.CAPLENGTH_HCIVERSION.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_HCSPARAMS",
            "TT counts and EHCI HCS constants, read-only",
            handles.bport1,
            0x104,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.HCSPARAMS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_HCCPARAMS",
            "EHCI Host configuration constants",
            handles.bport1,
            0x108,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.HCCPARAMS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DCIVERSION",
            "Device Mode CI version constant",
            handles.bport1,
            0x120,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.DCIVERSION.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DCCPARAMS",
            "EHCI, device and endpoint capabilities",
            handles.bport1,
            0x124,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.DCCPARAMS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_USBCMD",
            "USB Commands (EHCI extended)",
            handles.bport1,
            0x140,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.USBCMD.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_USBSTS",
            "Interrupt/Raw Status (EHCI extended) (Host/Device)",
            handles.bport1,
            0x144,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.USBSTS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_USBINTR",
            "Interrrupts and Enables",
            handles.bport1,
            0x148,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.USBINTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_FRINDEX",
            "Frame List Index",
            handles.bport1,
            0x14c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.FRINDEX.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_PERIODICLISTBASE_DEVICEADDR",
            "Host/Device Address dual-use",
            handles.bport1,
            0x154,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.PERIODICLISTBASE_DEVICEADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ASYNCLISTADDR_ENDPOINTLISTADDR",
            "Host/Device dual-use",
            handles.bport1,
            0x158,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ASYNCLISTADDR_ENDPOINTLISTADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TTCTRL",
            "TT Control",
            handles.bport1,
            0x15c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.TTCTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_BURSTSIZE",
            "Burst Size",
            handles.bport1,
            0x160,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.BURSTSIZE.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TXFILLTUNING",
            "TxFIFO Fill Tuning",
            handles.bport1,
            0x164,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.TXFILLTUNING.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TXTTFILLTUNING",
            "TT TX latency FIFO",
            handles.bport1,
            0x168,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.TXTTFILLTUNING.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_IC_USB",
            "Low and Fast Speed Control constants",
            handles.bport1,
            0x16c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.IC_USB.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ULPI_VIEWPORT",
            "ULPI Viewport",
            handles.bport1,
            0x170,
            4,
            read_32,
            wrVP,
            view32,
            &(bport1_ab_data.ULPI_VIEWPORT.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ENDPTNAK",
            "Endpoint NAK (Device mode)",
            handles.bport1,
            0x178,
            4,
            0,
            write_32,
            view32,
            &(bport1_ab_data.ENDPTNAK.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ENDPTNAKEN",
            "Endpoint NAK (Device mode)",
            handles.bport1,
            0x17c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ENDPTNAKEN.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CONFIGFLAG",
            "reserved",
            handles.bport1,
            0x180,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.CONFIGFLAG.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_PORTSC1",
            "Port Status & Control",
            handles.bport1,
            0x184,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.PORTSC1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_OTGSC",
            "OTG Status and Control",
            handles.bport1,
            0x1a4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.OTGSC.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_USBMODE",
            "USB Mode Selection",
            handles.bport1,
            0x1a8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.USBMODE.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ENDPTSETUPSTAT",
            "Endpoint Status Setup (Device mode)",
            handles.bport1,
            0x1ac,
            4,
            0,
            write_32,
            view32,
            &(bport1_ab_data.ENDPTSETUPSTAT.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ENDPTPRIME",
            "Endpoint Primer (Device mode)",
            handles.bport1,
            0x1b0,
            4,
            0,
            write_32,
            view32,
            &(bport1_ab_data.ENDPTPRIME.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ENDPTFLUSH",
            "Endpoint Flush (Device mode)",
            handles.bport1,
            0x1b4,
            4,
            0,
            write_32,
            view32,
            &(bport1_ab_data.ENDPTFLUSH.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ENDPTSTAT",
            "Endpoint Buffer Ready Status (Device mode), RO",
            handles.bport1,
            0x1b8,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.ENDPTSTAT.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ENDPTCOMPLETE",
            "Endpoint Tx Complete (Device mode)",
            handles.bport1,
            0x1bc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ENDPTCOMPLETE.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ENDPTCTRL0",
            "Endpoint 0 (Device mode)",
            handles.bport1,
            0x1c0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ENDPTCTRL0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ENDPTCTRL1",
            "Endpoints 1 to 11 (Device mode)",
            handles.bport1,
            0x1c4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ENDPTCTRL1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ENDPTCTRL2",
            "Endpoints 1 to 11 (Device mode)",
            handles.bport1,
            0x1c8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ENDPTCTRL2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ENDPTCTRL3",
            "Endpoints 1 to 11 (Device mode)",
            handles.bport1,
            0x1cc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ENDPTCTRL3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ENDPTCTRL4",
            "Endpoints 1 to 11 (Device mode)",
            handles.bport1,
            0x1d0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ENDPTCTRL4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ENDPTCTRL5",
            "Endpoints 1 to 11 (Device mode)",
            handles.bport1,
            0x1d4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ENDPTCTRL5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ENDPTCTRL6",
            "Endpoints 1 to 11 (Device mode)",
            handles.bport1,
            0x1d8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ENDPTCTRL6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ENDPTCTRL7",
            "Endpoints 1 to 11 (Device mode)",
            handles.bport1,
            0x1dc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ENDPTCTRL7.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ENDPTCTRL8",
            "Endpoints 1 to 11 (Device mode)",
            handles.bport1,
            0x1e0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ENDPTCTRL8.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ENDPTCTRL9",
            "Endpoints 1 to 11 (Device mode)",
            handles.bport1,
            0x1e4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ENDPTCTRL9.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ENDPTCTRL10",
            "Endpoints 1 to 11 (Device mode)",
            handles.bport1,
            0x1e8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ENDPTCTRL10.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ENDPTCTRL11",
            "Endpoints 1 to 11 (Device mode)",
            handles.bport1,
            0x1ec,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ENDPTCTRL11.value),
            True
        );
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.ENDPTCTRL11.value = (Uns32)(bport1_ab_data.ENDPTCTRL11.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ENDPTCTRL10.value = (Uns32)(bport1_ab_data.ENDPTCTRL10.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ENDPTCTRL9.value = (Uns32)(bport1_ab_data.ENDPTCTRL9.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ENDPTCTRL8.value = (Uns32)(bport1_ab_data.ENDPTCTRL8.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ENDPTCTRL7.value = (Uns32)(bport1_ab_data.ENDPTCTRL7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ENDPTCTRL6.value = (Uns32)(bport1_ab_data.ENDPTCTRL6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
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
        bport1_ab_data.USBMODE.value = (Uns32)(bport1_ab_data.USBMODE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.OTGSC.value = (Uns32)(bport1_ab_data.OTGSC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001020));
        bport1_ab_data.PORTSC1.value = (Uns32)(bport1_ab_data.PORTSC1.value & ~(0xffffffff)) | ((0xffffffff) & (0x8C000004));
        bport1_ab_data.CONFIGFLAG.value = (Uns32)(bport1_ab_data.CONFIGFLAG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bport1_ab_data.ENDPTNAKEN.value = (Uns32)(bport1_ab_data.ENDPTNAKEN.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ENDPTNAK.value = (Uns32)(bport1_ab_data.ENDPTNAK.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ULPI_VIEWPORT.value = (Uns32)(bport1_ab_data.ULPI_VIEWPORT.value & ~(0xffffffff)) | ((0xffffffff) & (0x08000000));
        bport1_ab_data.IC_USB.value = (Uns32)(bport1_ab_data.IC_USB.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TXTTFILLTUNING.value = (Uns32)(bport1_ab_data.TXTTFILLTUNING.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TXFILLTUNING.value = (Uns32)(bport1_ab_data.TXFILLTUNING.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.BURSTSIZE.value = (Uns32)(bport1_ab_data.BURSTSIZE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001010));
        bport1_ab_data.TTCTRL.value = (Uns32)(bport1_ab_data.TTCTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ASYNCLISTADDR_ENDPOINTLISTADDR.value = (Uns32)(bport1_ab_data.ASYNCLISTADDR_ENDPOINTLISTADDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PERIODICLISTBASE_DEVICEADDR.value = (Uns32)(bport1_ab_data.PERIODICLISTBASE_DEVICEADDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.FRINDEX.value = (Uns32)(bport1_ab_data.FRINDEX.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.USBINTR.value = (Uns32)(bport1_ab_data.USBINTR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.USBSTS.value = (Uns32)(bport1_ab_data.USBSTS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.USBCMD.value = (Uns32)(bport1_ab_data.USBCMD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00080000));
        bport1_ab_data.DCCPARAMS.value = (Uns32)(bport1_ab_data.DCCPARAMS.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000018C));
        bport1_ab_data.DCIVERSION.value = (Uns32)(bport1_ab_data.DCIVERSION.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bport1_ab_data.HCCPARAMS.value = (Uns32)(bport1_ab_data.HCCPARAMS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000006));
        bport1_ab_data.HCSPARAMS.value = (Uns32)(bport1_ab_data.HCSPARAMS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00010011));
        bport1_ab_data.CAPLENGTH_HCIVERSION.value = (Uns32)(bport1_ab_data.CAPLENGTH_HCIVERSION.value & ~(0xffffffff)) | ((0xffffffff) & (0x01000040));
        bport1_ab_data.SBUSCFG.value = (Uns32)(bport1_ab_data.SBUSCFG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000003));
        bport1_ab_data.GPTIMER1CTRL.value = (Uns32)(bport1_ab_data.GPTIMER1CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPTIMER1LD.value = (Uns32)(bport1_ab_data.GPTIMER1LD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPTIMER0CTRL.value = (Uns32)(bport1_ab_data.GPTIMER0CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPTIMER0LD.value = (Uns32)(bport1_ab_data.GPTIMER0LD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.HWRXBUF.value = (Uns32)(bport1_ab_data.HWRXBUF.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000A10));
        bport1_ab_data.HWTXBUF.value = (Uns32)(bport1_ab_data.HWTXBUF.value & ~(0xffffffff)) | ((0xffffffff) & (0x80060A10));
        bport1_ab_data.HWDEVICE.value = (Uns32)(bport1_ab_data.HWDEVICE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000019));
        bport1_ab_data.HWHOST.value = (Uns32)(bport1_ab_data.HWHOST.value & ~(0xffffffff)) | ((0xffffffff) & (0x10020001));
        bport1_ab_data.HWGENERAL.value = (Uns32)(bport1_ab_data.HWGENERAL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000083));
        bport1_ab_data.ID.value = (Uns32)(bport1_ab_data.ID.value & ~(0xffffffff)) | ((0xffffffff) & (0xE441FA05));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Zynq 7000 USB Registers");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model implements the full set of registers but no behavior.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
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


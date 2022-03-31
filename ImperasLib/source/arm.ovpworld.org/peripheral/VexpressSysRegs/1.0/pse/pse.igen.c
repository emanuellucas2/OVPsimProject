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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "VexpressSysRegs", "Example");
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

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "ab_ID",
            "System Identifier",
            handles.bport1,
            0x0,
            4,
            readId,
            write_32,
            view32,
            &(bport1_ab_data.ID.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_SW",
            "Soft user switches",
            handles.bport1,
            0x4,
            4,
            readSw,
            write_32,
            view32,
            &(bport1_ab_data.SW.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_LED",
            "User LEDs",
            handles.bport1,
            0x8,
            4,
            read_32,
            writeLed,
            view32,
            &(bport1_ab_data.LED.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CNT100HZ",
            "100Hz counter",
            handles.bport1,
            0x24,
            4,
            read100Hz,
            0,
            view32,
            &(bport1_ab_data.CNT100HZ.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_FLAGSSET",
            "Flag Set Register",
            handles.bport1,
            0x30,
            4,
            readFlags,
            writeFlags,
            view32,
            &(bport1_ab_data.FLAGSSET.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_FLAGSCLR",
            "Flag Clear Register",
            handles.bport1,
            0x34,
            4,
            0,
            write_32,
            view32,
            &(bport1_ab_data.FLAGSCLR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_NVFLAGSSET",
            "NV Flag Set Registers",
            handles.bport1,
            0x38,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.NVFLAGSSET.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_NVFLAGSCLR",
            "NV Flag Clear Registers",
            handles.bport1,
            0x3c,
            4,
            0,
            write_32,
            view32,
            &(bport1_ab_data.NVFLAGSCLR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MCI",
            "MCI status and control register",
            handles.bport1,
            0x48,
            4,
            readMci,
            0,
            view32,
            &(bport1_ab_data.MCI.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_FLASH",
            "Flash write protection",
            handles.bport1,
            0x4c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.FLASH.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CFGSW",
            "Soft configuration switches",
            handles.bport1,
            0x58,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CFGSW.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CNT24MHZ",
            "32-bit counter clocked at 24MHz",
            handles.bport1,
            0x5c,
            4,
            read24MHz,
            0,
            view32,
            &(bport1_ab_data.CNT24MHZ.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MISC",
            "Miscellaneous control flags",
            handles.bport1,
            0x60,
            4,
            readMisc,
            write_32,
            view32,
            &(bport1_ab_data.MISC.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DMA",
            "DMA Channel Selection Register",
            handles.bport1,
            0x64,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DMA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_PROCID0",
            0,
            handles.bport1,
            0x84,
            4,
            readProcId0,
            write_32,
            view32,
            &(bport1_ab_data.PROCID0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_PROCID1",
            0,
            handles.bport1,
            0x88,
            4,
            readProcId1,
            write_32,
            view32,
            &(bport1_ab_data.PROCID1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CFGDATA",
            "System Configuration register",
            handles.bport1,
            0xa0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CFGDATA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CFGCTRL",
            "Configuration Control Register",
            handles.bport1,
            0xa4,
            4,
            readCfgCtrl,
            write_32,
            view32,
            &(bport1_ab_data.CFGCTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CFGSTAT",
            "Configuration Status Register",
            handles.bport1,
            0xa8,
            4,
            readCfgStat,
            write_32,
            view32,
            &(bport1_ab_data.CFGSTAT.value),
            True
        );
    }

}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "ARM Versatile Express System Registers");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "Only select registers are modeled. See user.c for details.");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "ARM Motherboard Express ATX V2M-P1 Technical Reference Manual(ARM DUI 0447G), Section 4.3 Register Summary");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_32_node, "Open Source Apache 2.0");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}


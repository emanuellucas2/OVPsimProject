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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "CoreModule9x6", "Example");
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
            "ab_id",
            "Identification",
            handles.bport1,
            0x0,
            4,
            readID,
            0,
            view32,
            &(bport1_ab_data.id.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_proc",
            "Proc",
            handles.bport1,
            0x4,
            4,
            readProc,
            0,
            view32,
            &(bport1_ab_data.proc.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_osc",
            "Oscillator",
            handles.bport1,
            0x8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.osc.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ctrl",
            "Control",
            handles.bport1,
            0xc,
            4,
            read_32,
            writeCtrl,
            view32,
            &(bport1_ab_data.ctrl.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_stat",
            "Status",
            handles.bport1,
            0x10,
            4,
            readStat,
            0,
            view32,
            &(bport1_ab_data.stat.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_lock",
            "Lock",
            handles.bport1,
            0x14,
            4,
            readLock,
            0,
            view32,
            &(bport1_ab_data.lock.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_lmbuscnt",
            "Hi Freq timer",
            handles.bport1,
            0x18,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.lmbuscnt.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_auxosc",
            "Aux Osc",
            handles.bport1,
            0x1c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.auxosc.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_sdram",
            "SDRAM",
            handles.bport1,
            0x20,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.sdram.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_init",
            "Init",
            handles.bport1,
            0x24,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.init.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_refct",
            "SDRAM",
            handles.bport1,
            0x28,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.refct.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_flags",
            "Flags",
            handles.bport1,
            0x30,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.flags.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_flagsc",
            "Flagsc",
            handles.bport1,
            0x34,
            4,
            0,
            write_32,
            view32,
            &(bport1_ab_data.flagsc.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_nvflags",
            "NV Flags",
            handles.bport1,
            0x38,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.nvflags.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_nvflagss",
            "NV FlagsS",
            handles.bport1,
            0x3c,
            4,
            0,
            write_32,
            view32,
            &(bport1_ab_data.nvflagss.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_irqstat",
            "IRQ Status",
            handles.bport1,
            0x40,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.irqstat.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_irqrstat",
            "IRQ RSTATUS",
            handles.bport1,
            0x44,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.irqrstat.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_irqenset",
            "IRQ EN SET",
            handles.bport1,
            0x48,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.irqenset.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_irqenclr",
            "IRQ EN Clear",
            handles.bport1,
            0x4c,
            4,
            0,
            write_32,
            view32,
            &(bport1_ab_data.irqenclr.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_softintset",
            "Soft Interrupt Set",
            handles.bport1,
            0x50,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.softintset.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_softintclr",
            "Soft Interrupt Clear",
            handles.bport1,
            0x54,
            4,
            0,
            write_32,
            view32,
            &(bport1_ab_data.softintclr.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_fiqstat",
            "FIQ Status",
            handles.bport1,
            0x60,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.fiqstat.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_fiqrstat",
            "FIQ RStatus",
            handles.bport1,
            0x64,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.fiqrstat.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_fiqenset",
            "FIQ EN Set",
            handles.bport1,
            0x68,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.fiqenset.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_fiqenclr",
            "FIQ EN Clear",
            handles.bport1,
            0x6c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.fiqenclr.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_volt0",
            "Voltage CTL0",
            handles.bport1,
            0x80,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.volt0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_volt1",
            "Voltage CTL1",
            handles.bport1,
            0x84,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.volt1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_volt2",
            "Voltage CTL2",
            handles.bport1,
            0x88,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.volt2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_volt3",
            "Voltage CTL3",
            handles.bport1,
            0x8c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.volt3.value),
            True
        );
    }

}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "ARM Integrator Board 9x6 Core Module Registers ");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "none");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "ARM Integrator CM926EJ-S, CM946E-S, CM966E-S, CM1026EJ-S, and CM1136JF-S User Guide (DUI 0138)");
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


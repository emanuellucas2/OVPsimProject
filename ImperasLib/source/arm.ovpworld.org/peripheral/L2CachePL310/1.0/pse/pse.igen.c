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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "L2CachePL310", "Example");
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
            "ab_reg0_cache_id",
            "                 ",
            handles.bport1,
            0x0,
            4,
            readId,
            0,
            view32,
            &(bport1_ab_data.reg0_cache_id.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg0_cache_type",
            "                 ",
            handles.bport1,
            0x4,
            4,
            readType,
            0,
            view32,
            &(bport1_ab_data.reg0_cache_type.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg1_control",
            "                 ",
            handles.bport1,
            0x100,
            4,
            readCtrl,
            writeCtrl,
            view32,
            &(bport1_ab_data.reg1_control.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg1_aux_control",
            "                 ",
            handles.bport1,
            0x104,
            4,
            readAux,
            writeAux,
            view32,
            &(bport1_ab_data.reg1_aux_control.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg1_tag_ram_control",
            "                 ",
            handles.bport1,
            0x108,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg1_tag_ram_control.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg1_data_ram_control",
            "                 ",
            handles.bport1,
            0x10c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg1_data_ram_control.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg2_ev_counter_ctrl",
            "                 ",
            handles.bport1,
            0x200,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg2_ev_counter_ctrl.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg2_ev_counter1_cfg",
            "                 ",
            handles.bport1,
            0x204,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg2_ev_counter1_cfg.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg2_ev_counter0_cfg",
            "                 ",
            handles.bport1,
            0x208,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg2_ev_counter0_cfg.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg2_ev_counter1",
            "                 ",
            handles.bport1,
            0x20c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg2_ev_counter1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg2_ev_counter0",
            "                 ",
            handles.bport1,
            0x210,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg2_ev_counter0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg2_int_maske",
            "                 ",
            handles.bport1,
            0x214,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg2_int_maske.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg2_int_mask_statuse",
            "                 ",
            handles.bport1,
            0x218,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.reg2_int_mask_statuse.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg2_int_raw_statuse",
            "                 ",
            handles.bport1,
            0x21c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.reg2_int_raw_statuse.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg2_int_cleare",
            "                 ",
            handles.bport1,
            0x220,
            4,
            0,
            write_32,
            view32,
            &(bport1_ab_data.reg2_int_cleare.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg7_cache_sync",
            "                 ",
            handles.bport1,
            0x730,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg7_cache_sync.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg7_inv_pa",
            "                 ",
            handles.bport1,
            0x770,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg7_inv_pa.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg7_inv_way",
            "                 ",
            handles.bport1,
            0x77c,
            4,
            readInvWay,
            write_32,
            view32,
            &(bport1_ab_data.reg7_inv_way.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg7_clean_pa",
            "                 ",
            handles.bport1,
            0x7b0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg7_clean_pa.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg7_clean_index",
            "                 ",
            handles.bport1,
            0x7b8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg7_clean_index.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg7_clean_way",
            "                 ",
            handles.bport1,
            0x7bc,
            4,
            readCleanWay,
            write_32,
            view32,
            &(bport1_ab_data.reg7_clean_way.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg7_clean_inv_pa",
            "                 ",
            handles.bport1,
            0x7f0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg7_clean_inv_pa.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg7_clean_inv_index",
            "                 ",
            handles.bport1,
            0x7f8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg7_clean_inv_index.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg7_clean_inv_way",
            "                 ",
            handles.bport1,
            0x7fc,
            4,
            readCleanInvWay,
            write_32,
            view32,
            &(bport1_ab_data.reg7_clean_inv_way.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg9_d_lockdown0",
            "                 ",
            handles.bport1,
            0x900,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg9_d_lockdown0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg9_i_lockdown0",
            "                 ",
            handles.bport1,
            0x904,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg9_i_lockdown0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg9_d_lockdown1f",
            "                 ",
            handles.bport1,
            0x908,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg9_d_lockdown1f.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg9_i_lockdown1f",
            "                 ",
            handles.bport1,
            0x90c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg9_i_lockdown1f.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg9_d_lockdown2f",
            "                 ",
            handles.bport1,
            0x910,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg9_d_lockdown2f.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg9_i_lockdown2f",
            "                 ",
            handles.bport1,
            0x914,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg9_i_lockdown2f.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg9_d_lockdown3f",
            "                 ",
            handles.bport1,
            0x918,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg9_d_lockdown3f.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg9_i_lockdown3f",
            "                 ",
            handles.bport1,
            0x91c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg9_i_lockdown3f.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg9_d_lockdown4f",
            "                 ",
            handles.bport1,
            0x920,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg9_d_lockdown4f.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg9_i_lockdown4f",
            "                 ",
            handles.bport1,
            0x924,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg9_i_lockdown4f.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg9_d_lockdown5f",
            "                 ",
            handles.bport1,
            0x928,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg9_d_lockdown5f.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg9_i_lockdown5f",
            "                 ",
            handles.bport1,
            0x92c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg9_i_lockdown5f.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg9_d_lockdown6f",
            "                 ",
            handles.bport1,
            0x930,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg9_d_lockdown6f.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg9_i_lockdown6f",
            "                 ",
            handles.bport1,
            0x934,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg9_i_lockdown6f.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg9_d_lockdown7f",
            "                 ",
            handles.bport1,
            0x938,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg9_d_lockdown7f.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg9_i_lockdown7f",
            "                 ",
            handles.bport1,
            0x93c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg9_i_lockdown7f.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg9_lock_line_eng",
            "                 ",
            handles.bport1,
            0x950,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg9_lock_line_eng.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg9_unlock_wayg",
            "                 ",
            handles.bport1,
            0x954,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg9_unlock_wayg.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg12_addr_filt_start",
            "                 ",
            handles.bport1,
            0xc00,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg12_addr_filt_start.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg12_addr_filt_end",
            "                 ",
            handles.bport1,
            0xc04,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg12_addr_filt_end.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg15_debug_ctrl",
            "                 ",
            handles.bport1,
            0xf40,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg15_debug_ctrl.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg15_prefetch_ctrl",
            "                 ",
            handles.bport1,
            0xf60,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg15_prefetch_ctrl.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_reg15_power_ctrl",
            "                 ",
            handles.bport1,
            0xf80,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.reg15_power_ctrl.value),
            True
        );
    }

}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "ARM PL310 L2 Cache Control Registers");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Programmers View, register model only. Does NOT model functionality, just provides registers to allow code to run.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "ARM PrimeCell Level 2 Cache Controller (PL310) Technical Reference Manual (ARM DDI 0246)");
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


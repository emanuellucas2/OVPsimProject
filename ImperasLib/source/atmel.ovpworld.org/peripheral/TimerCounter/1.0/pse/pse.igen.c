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

bp1_REG_dataT bp1_REG_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "TimerCounter", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bp1 = ppmCreateSlaveBusPort("bp1", 16384);
    if (!handles.bp1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bp1'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle REGTC_CCR0_reg = ppmCreateRegister(
            "REG_TC_CCR0",
            0,
            handles.bp1,
            0x0,
            4,
            0,
            TC_CCR_wcb0,
            view32,
            &(bp1_REG_data.TC_CCR0.value),
            True
        );

        ppmCreateRegisterField(REGTC_CCR0_reg, "SWTRG", 0, 2, 1, 0, 1);
        ppmCreateRegisterField(REGTC_CCR0_reg, "CLKDIS", 0, 1, 1, 0, 1);
        ppmCreateRegisterField(REGTC_CCR0_reg, "CLKEN", 0, 0, 1, 0, 1);
    }
    {
        registerHandle REGTC_CMR0_reg = ppmCreateRegister(
            "REG_TC_CMR0",
            0,
            handles.bp1,
            0x4,
            4,
            read_32,
            TC_CMR_wcb0,
            view32,
            &(bp1_REG_data.TC_CMR0.value),
            True
        );

        ppmCreateRegisterField(REGTC_CMR0_reg, "LDRB", 0, 18, 2, 1, 1);
        ppmCreateRegisterField(REGTC_CMR0_reg, "LDRA", 0, 16, 2, 1, 1);
        ppmCreateRegisterField(REGTC_CMR0_reg, "WAVE", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(REGTC_CMR0_reg, "CPCTRG", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(REGTC_CMR0_reg, "ABETRG", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(REGTC_CMR0_reg, "ETRGEDG", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(REGTC_CMR0_reg, "LDBDIS", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(REGTC_CMR0_reg, "LDBSTOP", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(REGTC_CMR0_reg, "BURST", 0, 4, 2, 1, 1);
        ppmCreateRegisterField(REGTC_CMR0_reg, "CLKI", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(REGTC_CMR0_reg, "TCCLKS", 0, 0, 3, 1, 1);
    }
    {
        registerHandle REGTC_CVR0_reg = ppmCreateRegister(
            "REG_TC_CVR0",
            0,
            handles.bp1,
            0x10,
            4,
            read_32,
            TC_CVR_wcb0,
            view32,
            &(bp1_REG_data.TC_CVR0.value),
            True
        );

        ppmCreateRegisterField(REGTC_CVR0_reg, "CV", 0, 0, 16, 1, 1);
    }
    {
        registerHandle REGTC_RA0_reg = ppmCreateRegister(
            "REG_TC_RA0",
            0,
            handles.bp1,
            0x14,
            4,
            read_32,
            TC_RA_wcb0,
            view32,
            &(bp1_REG_data.TC_RA0.value),
            True
        );

        ppmCreateRegisterField(REGTC_RA0_reg, "RA", 0, 0, 16, 1, 1);
    }
    {
        registerHandle REGTC_RB0_reg = ppmCreateRegister(
            "REG_TC_RB0",
            0,
            handles.bp1,
            0x18,
            4,
            read_32,
            TC_RB_wcb0,
            view32,
            &(bp1_REG_data.TC_RB0.value),
            True
        );

        ppmCreateRegisterField(REGTC_RB0_reg, "RB", 0, 0, 16, 1, 1);
    }
    {
        registerHandle REGTC_RC0_reg = ppmCreateRegister(
            "REG_TC_RC0",
            0,
            handles.bp1,
            0x1c,
            4,
            read_32,
            TC_RC_wcb0,
            view32,
            &(bp1_REG_data.TC_RC0.value),
            True
        );

        ppmCreateRegisterField(REGTC_RC0_reg, "RC", 0, 0, 16, 1, 1);
    }
    {
        registerHandle REGTC_SR0_reg = ppmCreateRegister(
            "REG_TC_SR0",
            0,
            handles.bp1,
            0x20,
            4,
            read_32,
            0,
            view32,
            &(bp1_REG_data.TC_SR0.value),
            True
        );

        ppmCreateRegisterField(REGTC_SR0_reg, "MTIOB", 0, 18, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR0_reg, "MTIOA", 0, 17, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR0_reg, "CLKSTA", 0, 16, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR0_reg, "ETRGS", 0, 7, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR0_reg, "LDRBS", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR0_reg, "LDRAS", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR0_reg, "CPCS", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR0_reg, "CPBS", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR0_reg, "CPAS", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR0_reg, "LOVRS", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR0_reg, "COVFS", 0, 0, 1, 1, 0);
    }
    {
        registerHandle REGTC_IER0_reg = ppmCreateRegister(
            "REG_TC_IER0",
            0,
            handles.bp1,
            0x24,
            4,
            0,
            TC_IER_wcb0,
            view32,
            &(bp1_REG_data.TC_IER0.value),
            True
        );

        ppmCreateRegisterField(REGTC_IER0_reg, "ETRGS", 0, 7, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IER0_reg, "LDRBS", 0, 6, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IER0_reg, "LDRAS", 0, 5, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IER0_reg, "CPCS", 0, 4, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IER0_reg, "CPBS", 0, 3, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IER0_reg, "CPAS", 0, 2, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IER0_reg, "LOVRS", 0, 1, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IER0_reg, "COVFS", 0, 0, 1, 0, 1);
    }
    {
        registerHandle REGTC_IDR0_reg = ppmCreateRegister(
            "REG_TC_IDR0",
            0,
            handles.bp1,
            0x28,
            4,
            0,
            TC_IDR_wcb0,
            view32,
            &(bp1_REG_data.TC_IDR0.value),
            True
        );

        ppmCreateRegisterField(REGTC_IDR0_reg, "ETRGS", 0, 7, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IDR0_reg, "LDRBS", 0, 6, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IDR0_reg, "LDRAS", 0, 5, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IDR0_reg, "CPCS", 0, 4, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IDR0_reg, "CPBS", 0, 3, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IDR0_reg, "CPAS", 0, 2, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IDR0_reg, "LOVRS", 0, 1, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IDR0_reg, "COVFS", 0, 0, 1, 0, 1);
    }
    {
        registerHandle REGTC_IMR0_reg = ppmCreateRegister(
            "REG_TC_IMR0",
            0,
            handles.bp1,
            0x2c,
            4,
            read_32,
            0,
            view32,
            &(bp1_REG_data.TC_IMR0.value),
            True
        );

        ppmCreateRegisterField(REGTC_IMR0_reg, "ETRGS", 0, 7, 1, 1, 0);
        ppmCreateRegisterField(REGTC_IMR0_reg, "LDRBS", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(REGTC_IMR0_reg, "LDRAS", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(REGTC_IMR0_reg, "CPCS", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(REGTC_IMR0_reg, "CPBS", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(REGTC_IMR0_reg, "CPAS", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(REGTC_IMR0_reg, "LOVRS", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(REGTC_IMR0_reg, "COVFS", 0, 0, 1, 1, 0);
    }
    {
        registerHandle REGTC_CCR1_reg = ppmCreateRegister(
            "REG_TC_CCR1",
            0,
            handles.bp1,
            0x40,
            4,
            0,
            TC_CCR_wcb1,
            view32,
            &(bp1_REG_data.TC_CCR1.value),
            True
        );

        ppmCreateRegisterField(REGTC_CCR1_reg, "SWTRG", 0, 2, 1, 0, 1);
        ppmCreateRegisterField(REGTC_CCR1_reg, "CLKDIS", 0, 1, 1, 0, 1);
        ppmCreateRegisterField(REGTC_CCR1_reg, "CLKEN", 0, 0, 1, 0, 1);
    }
    {
        registerHandle REGTC_CMR1_reg = ppmCreateRegister(
            "REG_TC_CMR1",
            0,
            handles.bp1,
            0x44,
            4,
            read_32,
            TC_CMR_wcb1,
            view32,
            &(bp1_REG_data.TC_CMR1.value),
            True
        );

        ppmCreateRegisterField(REGTC_CMR1_reg, "LDRB", 0, 18, 2, 1, 1);
        ppmCreateRegisterField(REGTC_CMR1_reg, "LDRA", 0, 16, 2, 1, 1);
        ppmCreateRegisterField(REGTC_CMR1_reg, "WAVE", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(REGTC_CMR1_reg, "CPCTRG", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(REGTC_CMR1_reg, "ABETRG", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(REGTC_CMR1_reg, "ETRGEDG", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(REGTC_CMR1_reg, "LDBDIS", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(REGTC_CMR1_reg, "LDBSTOP", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(REGTC_CMR1_reg, "BURST", 0, 4, 2, 1, 1);
        ppmCreateRegisterField(REGTC_CMR1_reg, "CLKI", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(REGTC_CMR1_reg, "TCCLKS", 0, 0, 3, 1, 1);
    }
    {
        registerHandle REGTC_CVR1_reg = ppmCreateRegister(
            "REG_TC_CVR1",
            0,
            handles.bp1,
            0x50,
            4,
            read_32,
            TC_CVR_wcb1,
            view32,
            &(bp1_REG_data.TC_CVR1.value),
            True
        );

        ppmCreateRegisterField(REGTC_CVR1_reg, "CV", 0, 0, 16, 1, 1);
    }
    {
        registerHandle REGTC_RA1_reg = ppmCreateRegister(
            "REG_TC_RA1",
            0,
            handles.bp1,
            0x54,
            4,
            read_32,
            TC_RA_wcb1,
            view32,
            &(bp1_REG_data.TC_RA1.value),
            True
        );

        ppmCreateRegisterField(REGTC_RA1_reg, "RA", 0, 0, 16, 1, 1);
    }
    {
        registerHandle REGTC_RB1_reg = ppmCreateRegister(
            "REG_TC_RB1",
            0,
            handles.bp1,
            0x58,
            4,
            read_32,
            TC_RB_wcb1,
            view32,
            &(bp1_REG_data.TC_RB1.value),
            True
        );

        ppmCreateRegisterField(REGTC_RB1_reg, "RB", 0, 0, 16, 1, 1);
    }
    {
        registerHandle REGTC_RC1_reg = ppmCreateRegister(
            "REG_TC_RC1",
            0,
            handles.bp1,
            0x5c,
            4,
            read_32,
            TC_RC_wcb1,
            view32,
            &(bp1_REG_data.TC_RC1.value),
            True
        );

        ppmCreateRegisterField(REGTC_RC1_reg, "RC", 0, 0, 16, 1, 1);
    }
    {
        registerHandle REGTC_SR1_reg = ppmCreateRegister(
            "REG_TC_SR1",
            0,
            handles.bp1,
            0x60,
            4,
            read_32,
            0,
            view32,
            &(bp1_REG_data.TC_SR1.value),
            True
        );

        ppmCreateRegisterField(REGTC_SR1_reg, "MTIOB", 0, 18, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR1_reg, "MTIOA", 0, 17, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR1_reg, "CLKSTA", 0, 16, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR1_reg, "ETRGS", 0, 7, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR1_reg, "LDRBS", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR1_reg, "LDRAS", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR1_reg, "CPCS", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR1_reg, "CPBS", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR1_reg, "CPAS", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR1_reg, "LOVRS", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR1_reg, "COVFS", 0, 0, 1, 1, 0);
    }
    {
        registerHandle REGTC_IER1_reg = ppmCreateRegister(
            "REG_TC_IER1",
            0,
            handles.bp1,
            0x64,
            4,
            0,
            TC_IER_wcb1,
            view32,
            &(bp1_REG_data.TC_IER1.value),
            True
        );

        ppmCreateRegisterField(REGTC_IER1_reg, "ETRGS", 0, 7, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IER1_reg, "LDRBS", 0, 6, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IER1_reg, "LDRAS", 0, 5, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IER1_reg, "CPCS", 0, 4, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IER1_reg, "CPBS", 0, 3, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IER1_reg, "CPAS", 0, 2, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IER1_reg, "LOVRS", 0, 1, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IER1_reg, "COVFS", 0, 0, 1, 0, 1);
    }
    {
        registerHandle REGTC_IDR1_reg = ppmCreateRegister(
            "REG_TC_IDR1",
            0,
            handles.bp1,
            0x68,
            4,
            0,
            TC_IDR_wcb1,
            view32,
            &(bp1_REG_data.TC_IDR1.value),
            True
        );

        ppmCreateRegisterField(REGTC_IDR1_reg, "ETRGS", 0, 7, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IDR1_reg, "LDRBS", 0, 6, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IDR1_reg, "LDRAS", 0, 5, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IDR1_reg, "CPCS", 0, 4, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IDR1_reg, "CPBS", 0, 3, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IDR1_reg, "CPAS", 0, 2, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IDR1_reg, "LOVRS", 0, 1, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IDR1_reg, "COVFS", 0, 0, 1, 0, 1);
    }
    {
        registerHandle REGTC_IMR1_reg = ppmCreateRegister(
            "REG_TC_IMR1",
            0,
            handles.bp1,
            0x6c,
            4,
            read_32,
            0,
            view32,
            &(bp1_REG_data.TC_IMR1.value),
            True
        );

        ppmCreateRegisterField(REGTC_IMR1_reg, "ETRGS", 0, 7, 1, 1, 0);
        ppmCreateRegisterField(REGTC_IMR1_reg, "LDRBS", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(REGTC_IMR1_reg, "LDRAS", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(REGTC_IMR1_reg, "CPCS", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(REGTC_IMR1_reg, "CPBS", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(REGTC_IMR1_reg, "CPAS", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(REGTC_IMR1_reg, "LOVRS", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(REGTC_IMR1_reg, "COVFS", 0, 0, 1, 1, 0);
    }
    {
        registerHandle REGTC_CCR2_reg = ppmCreateRegister(
            "REG_TC_CCR2",
            0,
            handles.bp1,
            0x80,
            4,
            0,
            TC_CCR_wcb2,
            view32,
            &(bp1_REG_data.TC_CCR2.value),
            True
        );

        ppmCreateRegisterField(REGTC_CCR2_reg, "SWTRG", 0, 2, 1, 0, 1);
        ppmCreateRegisterField(REGTC_CCR2_reg, "CLKDIS", 0, 1, 1, 0, 1);
        ppmCreateRegisterField(REGTC_CCR2_reg, "CLKEN", 0, 0, 1, 0, 1);
    }
    {
        registerHandle REGTC_CMR2_reg = ppmCreateRegister(
            "REG_TC_CMR2",
            0,
            handles.bp1,
            0x84,
            4,
            read_32,
            TC_CMR_wcb2,
            view32,
            &(bp1_REG_data.TC_CMR2.value),
            True
        );

        ppmCreateRegisterField(REGTC_CMR2_reg, "LDRB", 0, 18, 2, 1, 1);
        ppmCreateRegisterField(REGTC_CMR2_reg, "LDRA", 0, 16, 2, 1, 1);
        ppmCreateRegisterField(REGTC_CMR2_reg, "WAVE", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(REGTC_CMR2_reg, "CPCTRG", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(REGTC_CMR2_reg, "ABETRG", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(REGTC_CMR2_reg, "ETRGEDG", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(REGTC_CMR2_reg, "LDBDIS", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(REGTC_CMR2_reg, "LDBSTOP", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(REGTC_CMR2_reg, "BURST", 0, 4, 2, 1, 1);
        ppmCreateRegisterField(REGTC_CMR2_reg, "CLKI", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(REGTC_CMR2_reg, "TCCLKS", 0, 0, 3, 1, 1);
    }
    {
        registerHandle REGTC_CVR2_reg = ppmCreateRegister(
            "REG_TC_CVR2",
            0,
            handles.bp1,
            0x90,
            4,
            read_32,
            TC_CVR_wcb2,
            view32,
            &(bp1_REG_data.TC_CVR2.value),
            True
        );

        ppmCreateRegisterField(REGTC_CVR2_reg, "CV", 0, 0, 16, 1, 1);
    }
    {
        registerHandle REGTC_RA2_reg = ppmCreateRegister(
            "REG_TC_RA2",
            0,
            handles.bp1,
            0x94,
            4,
            read_32,
            TC_RA_wcb2,
            view32,
            &(bp1_REG_data.TC_RA2.value),
            True
        );

        ppmCreateRegisterField(REGTC_RA2_reg, "RA", 0, 0, 16, 1, 1);
    }
    {
        registerHandle REGTC_RB2_reg = ppmCreateRegister(
            "REG_TC_RB2",
            0,
            handles.bp1,
            0x98,
            4,
            read_32,
            TC_RB_wcb2,
            view32,
            &(bp1_REG_data.TC_RB2.value),
            True
        );

        ppmCreateRegisterField(REGTC_RB2_reg, "RB", 0, 0, 16, 1, 1);
    }
    {
        registerHandle REGTC_RC2_reg = ppmCreateRegister(
            "REG_TC_RC2",
            0,
            handles.bp1,
            0x9c,
            4,
            read_32,
            TC_RC_wcb2,
            view32,
            &(bp1_REG_data.TC_RC2.value),
            True
        );

        ppmCreateRegisterField(REGTC_RC2_reg, "RC", 0, 0, 16, 1, 1);
    }
    {
        registerHandle REGTC_SR2_reg = ppmCreateRegister(
            "REG_TC_SR2",
            0,
            handles.bp1,
            0xa0,
            4,
            read_32,
            0,
            view32,
            &(bp1_REG_data.TC_SR2.value),
            True
        );

        ppmCreateRegisterField(REGTC_SR2_reg, "MTIOB", 0, 18, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR2_reg, "MTIOA", 0, 17, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR2_reg, "CLKSTA", 0, 16, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR2_reg, "ETRGS", 0, 7, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR2_reg, "LDRBS", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR2_reg, "LDRAS", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR2_reg, "CPCS", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR2_reg, "CPBS", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR2_reg, "CPAS", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR2_reg, "LOVRS", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(REGTC_SR2_reg, "COVFS", 0, 0, 1, 1, 0);
    }
    {
        registerHandle REGTC_IER2_reg = ppmCreateRegister(
            "REG_TC_IER2",
            0,
            handles.bp1,
            0xa4,
            4,
            0,
            TC_IER_wcb2,
            view32,
            &(bp1_REG_data.TC_IER2.value),
            True
        );

        ppmCreateRegisterField(REGTC_IER2_reg, "ETRGS", 0, 7, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IER2_reg, "LDRBS", 0, 6, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IER2_reg, "LDRAS", 0, 5, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IER2_reg, "CPCS", 0, 4, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IER2_reg, "CPBS", 0, 3, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IER2_reg, "CPAS", 0, 2, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IER2_reg, "LOVRS", 0, 1, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IER2_reg, "COVFS", 0, 0, 1, 0, 1);
    }
    {
        registerHandle REGTC_IDR2_reg = ppmCreateRegister(
            "REG_TC_IDR2",
            0,
            handles.bp1,
            0xa8,
            4,
            0,
            TC_IDR_wcb2,
            view32,
            &(bp1_REG_data.TC_IDR2.value),
            True
        );

        ppmCreateRegisterField(REGTC_IDR2_reg, "ETRGS", 0, 7, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IDR2_reg, "LDRBS", 0, 6, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IDR2_reg, "LDRAS", 0, 5, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IDR2_reg, "CPCS", 0, 4, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IDR2_reg, "CPBS", 0, 3, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IDR2_reg, "CPAS", 0, 2, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IDR2_reg, "LOVRS", 0, 1, 1, 0, 1);
        ppmCreateRegisterField(REGTC_IDR2_reg, "COVFS", 0, 0, 1, 0, 1);
    }
    {
        registerHandle REGTC_IMR2_reg = ppmCreateRegister(
            "REG_TC_IMR2",
            0,
            handles.bp1,
            0xac,
            4,
            read_32,
            0,
            view32,
            &(bp1_REG_data.TC_IMR2.value),
            True
        );

        ppmCreateRegisterField(REGTC_IMR2_reg, "ETRGS", 0, 7, 1, 1, 0);
        ppmCreateRegisterField(REGTC_IMR2_reg, "LDRBS", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(REGTC_IMR2_reg, "LDRAS", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(REGTC_IMR2_reg, "CPCS", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(REGTC_IMR2_reg, "CPBS", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(REGTC_IMR2_reg, "CPAS", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(REGTC_IMR2_reg, "LOVRS", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(REGTC_IMR2_reg, "COVFS", 0, 0, 1, 1, 0);
    }
    {
        registerHandle REGTC_BCR_reg = ppmCreateRegister(
            "REG_TC_BCR",
            0,
            handles.bp1,
            0xc0,
            4,
            0,
            TC_BCR_wcb,
            view32,
            &(bp1_REG_data.TC_BCR.value),
            True
        );

        ppmCreateRegisterField(REGTC_BCR_reg, "SYNC", 0, 0, 1, 0, 1);
    }
    {
        registerHandle REGTC_BMR_reg = ppmCreateRegister(
            "REG_TC_BMR",
            0,
            handles.bp1,
            0xc4,
            4,
            0,
            TC_BMR_wcb,
            view32,
            &(bp1_REG_data.TC_BMR.value),
            True
        );

        ppmCreateRegisterField(REGTC_BMR_reg, "TC2X2CS", 0, 4, 2, 0, 1);
        ppmCreateRegisterField(REGTC_BMR_reg, "TC1X1CS", 0, 2, 2, 0, 1);
        ppmCreateRegisterField(REGTC_BMR_reg, "TC0X0CS", 0, 0, 2, 0, 1);
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bp1_REG_data.TC_BMR.value = (Uns32)(bp1_REG_data.TC_BMR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_BCR.value = (Uns32)(bp1_REG_data.TC_BCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_IMR2.value = (Uns32)(bp1_REG_data.TC_IMR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_IDR2.value = (Uns32)(bp1_REG_data.TC_IDR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_IER2.value = (Uns32)(bp1_REG_data.TC_IER2.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_SR2.value = (Uns32)(bp1_REG_data.TC_SR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_RC2.value = (Uns32)(bp1_REG_data.TC_RC2.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_RB2.value = (Uns32)(bp1_REG_data.TC_RB2.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_RA2.value = (Uns32)(bp1_REG_data.TC_RA2.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_CVR2.value = (Uns32)(bp1_REG_data.TC_CVR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_CMR2.value = (Uns32)(bp1_REG_data.TC_CMR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_CCR2.value = (Uns32)(bp1_REG_data.TC_CCR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_IMR1.value = (Uns32)(bp1_REG_data.TC_IMR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_IDR1.value = (Uns32)(bp1_REG_data.TC_IDR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_IER1.value = (Uns32)(bp1_REG_data.TC_IER1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_SR1.value = (Uns32)(bp1_REG_data.TC_SR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_RC1.value = (Uns32)(bp1_REG_data.TC_RC1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_RB1.value = (Uns32)(bp1_REG_data.TC_RB1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_RA1.value = (Uns32)(bp1_REG_data.TC_RA1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_CVR1.value = (Uns32)(bp1_REG_data.TC_CVR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_CMR1.value = (Uns32)(bp1_REG_data.TC_CMR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_CCR1.value = (Uns32)(bp1_REG_data.TC_CCR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_IMR0.value = (Uns32)(bp1_REG_data.TC_IMR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_IDR0.value = (Uns32)(bp1_REG_data.TC_IDR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_IER0.value = (Uns32)(bp1_REG_data.TC_IER0.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_SR0.value = (Uns32)(bp1_REG_data.TC_SR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_RC0.value = (Uns32)(bp1_REG_data.TC_RC0.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_RB0.value = (Uns32)(bp1_REG_data.TC_RB0.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_RA0.value = (Uns32)(bp1_REG_data.TC_RA0.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_CVR0.value = (Uns32)(bp1_REG_data.TC_CVR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_CMR0.value = (Uns32)(bp1_REG_data.TC_CMR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.TC_CCR0.value = (Uns32)(bp1_REG_data.TC_CCR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "TC: Timer Counter\nThis model contains an accurate Register set interface.\nThe functionality has only been implemented to sufficiently boot uClinux\nThe Timer Counter block includes three identical 16-bit timer\ncounter channels. Each channel can be independently programmed to perform a wide range of\nfunctions including frequency measurement, event counting, interval measurement, pulse generation,\ndelay timing and pulse width modulation.\nThe Timer Counter can be used in Capture or Waveform mode, and all three counter channels\ncan be started simultaneously and chained together.\nfor more information visit http://www.atmel.com/products/at91");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model is sufficient to boot Linux");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Rev. 1354D ARM08/02");
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
    return 0;
}


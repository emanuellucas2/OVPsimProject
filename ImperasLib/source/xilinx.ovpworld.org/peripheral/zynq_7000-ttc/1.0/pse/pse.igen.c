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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "zynq_7000-ttc", "Example");
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
        registerHandle abClock_Control_1_reg = ppmCreateRegister(
            "ab_Clock_Control_1",
            "Clock Control register",
            handles.bport1,
            0x0,
            4,
            read_32,
            wrClkCtrl1,
            view32,
            &(bport1_ab_data.Clock_Control_1.value),
            True
        );

        ppmCreateRegisterField(abClock_Control_1_reg, "E", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abClock_Control_1_reg, "SRC", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abClock_Control_1_reg, "PS_V", 0, 1, 4, 1, 1);
        ppmCreateRegisterField(abClock_Control_1_reg, "PS_EN", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abClock_Control_2_reg = ppmCreateRegister(
            "ab_Clock_Control_2",
            "Clock Control register",
            handles.bport1,
            0x4,
            4,
            read_32,
            wrClkCtrl2,
            view32,
            &(bport1_ab_data.Clock_Control_2.value),
            True
        );

        ppmCreateRegisterField(abClock_Control_2_reg, "E", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abClock_Control_2_reg, "SRC", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abClock_Control_2_reg, "PS_V", 0, 1, 4, 1, 1);
        ppmCreateRegisterField(abClock_Control_2_reg, "PS_EN", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abClock_Control_3_reg = ppmCreateRegister(
            "ab_Clock_Control_3",
            "Clock Control register",
            handles.bport1,
            0x8,
            4,
            read_32,
            wrClkCtrl3,
            view32,
            &(bport1_ab_data.Clock_Control_3.value),
            True
        );

        ppmCreateRegisterField(abClock_Control_3_reg, "E", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abClock_Control_3_reg, "SRC", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abClock_Control_3_reg, "PS_V", 0, 1, 4, 1, 1);
        ppmCreateRegisterField(abClock_Control_3_reg, "PS_EN", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abCounter_Control_1_reg = ppmCreateRegister(
            "ab_Counter_Control_1",
            "Operational mode and reset",
            handles.bport1,
            0xc,
            4,
            read_32,
            wrCntrCtrl1,
            view32,
            &(bport1_ab_data.Counter_Control_1.value),
            True
        );

        ppmCreateRegisterField(abCounter_Control_1_reg, "WAVPOL", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abCounter_Control_1_reg, "WAVEN", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abCounter_Control_1_reg, "RST", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abCounter_Control_1_reg, "MATCH", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abCounter_Control_1_reg, "DEC", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abCounter_Control_1_reg, "INT", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abCounter_Control_1_reg, "DIS", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abCounter_Control_2_reg = ppmCreateRegister(
            "ab_Counter_Control_2",
            "Operational mode and reset",
            handles.bport1,
            0x10,
            4,
            read_32,
            wrCntrCtrl2,
            view32,
            &(bport1_ab_data.Counter_Control_2.value),
            True
        );

        ppmCreateRegisterField(abCounter_Control_2_reg, "WAVPOL", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abCounter_Control_2_reg, "WAVEN", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abCounter_Control_2_reg, "RST", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abCounter_Control_2_reg, "MATCH", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abCounter_Control_2_reg, "DEC", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abCounter_Control_2_reg, "INT", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abCounter_Control_2_reg, "DIS", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abCounter_Control_3_reg = ppmCreateRegister(
            "ab_Counter_Control_3",
            "Operational mode and reset",
            handles.bport1,
            0x14,
            4,
            read_32,
            wrCntrCtrl3,
            view32,
            &(bport1_ab_data.Counter_Control_3.value),
            True
        );

        ppmCreateRegisterField(abCounter_Control_3_reg, "WAVPOL", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abCounter_Control_3_reg, "WAVEN", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abCounter_Control_3_reg, "RST", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abCounter_Control_3_reg, "MATCH", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abCounter_Control_3_reg, "DEC", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abCounter_Control_3_reg, "INT", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abCounter_Control_3_reg, "DIS", 0, 0, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_Counter_Value_1",
            "Current counter value",
            handles.bport1,
            0x18,
            4,
            rdCurrent1,
            0,
            view32,
            &(bport1_ab_data.Counter_Value_1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Counter_Value_2",
            "Current counter value",
            handles.bport1,
            0x1c,
            4,
            rdCurrent2,
            0,
            view32,
            &(bport1_ab_data.Counter_Value_2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Counter_Value_3",
            "Current counter value",
            handles.bport1,
            0x20,
            4,
            rdCurrent3,
            0,
            view32,
            &(bport1_ab_data.Counter_Value_3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Interval_Counter_1",
            "Interval value",
            handles.bport1,
            0x24,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Interval_Counter_1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Interval_Counter_2",
            "Interval value",
            handles.bport1,
            0x28,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Interval_Counter_2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Interval_Counter_3",
            "Interval value",
            handles.bport1,
            0x2c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Interval_Counter_3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Match_1_Counter_1",
            "Match value",
            handles.bport1,
            0x30,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Match_1_Counter_1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Match_1_Counter_2",
            "Match value",
            handles.bport1,
            0x34,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Match_1_Counter_2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Match_1_Counter_3",
            "Match value",
            handles.bport1,
            0x38,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Match_1_Counter_3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Match_2_Counter_1",
            "Match value",
            handles.bport1,
            0x3c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Match_2_Counter_1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Match_2_Counter_2",
            "Match value",
            handles.bport1,
            0x40,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Match_2_Counter_2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Match_2_Counter_3",
            "Match value",
            handles.bport1,
            0x44,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Match_2_Counter_3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Match_3_Counter_1",
            "Match value",
            handles.bport1,
            0x48,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Match_3_Counter_1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Match_3_Counter_2",
            "Match value",
            handles.bport1,
            0x4c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Match_3_Counter_2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Match_3_Counter_3",
            "Match value",
            handles.bport1,
            0x50,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Match_3_Counter_3.value),
            True
        );
    }
    {
        registerHandle abInterrupt_Register_1_reg = ppmCreateRegister(
            "ab_Interrupt_Register_1",
            "Counter 1 Interval, Match, Overflow and Event interrupts",
            handles.bport1,
            0x54,
            4,
            rdInt1,
            wrInt,
            view32,
            &(bport1_ab_data.Interrupt_Register_1.value),
            True
        );

        ppmCreateRegisterField(abInterrupt_Register_1_reg, "EV", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abInterrupt_Register_1_reg, "OV", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abInterrupt_Register_1_reg, "M3", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abInterrupt_Register_1_reg, "M2", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abInterrupt_Register_1_reg, "M1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abInterrupt_Register_1_reg, "IV", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abInterrupt_Register_2_reg = ppmCreateRegister(
            "ab_Interrupt_Register_2",
            "Counter 2 Interval, Match, Overflow and Event interrupts",
            handles.bport1,
            0x58,
            4,
            rdInt2,
            wrInt,
            view32,
            &(bport1_ab_data.Interrupt_Register_2.value),
            True
        );

        ppmCreateRegisterField(abInterrupt_Register_2_reg, "EV", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abInterrupt_Register_2_reg, "OV", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abInterrupt_Register_2_reg, "M3", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abInterrupt_Register_2_reg, "M2", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abInterrupt_Register_2_reg, "M1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abInterrupt_Register_2_reg, "IV", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abInterrupt_Register_3_reg = ppmCreateRegister(
            "ab_Interrupt_Register_3",
            "Counter 3 Interval, Match, Overflow and Event interrupts",
            handles.bport1,
            0x5c,
            4,
            rdInt3,
            wrInt,
            view32,
            &(bport1_ab_data.Interrupt_Register_3.value),
            True
        );

        ppmCreateRegisterField(abInterrupt_Register_3_reg, "EV", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abInterrupt_Register_3_reg, "OV", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abInterrupt_Register_3_reg, "M3", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abInterrupt_Register_3_reg, "M2", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abInterrupt_Register_3_reg, "M1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abInterrupt_Register_3_reg, "IV", 0, 0, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_Interrupt_Enable_1",
            "ANDed with corresponding Interrupt Register",
            handles.bport1,
            0x60,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Interrupt_Enable_1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Interrupt_Enable_2",
            "ANDed with corresponding Interrupt Register",
            handles.bport1,
            0x64,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Interrupt_Enable_2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Interrupt_Enable_3",
            "ANDed with corresponding Interrupt Register",
            handles.bport1,
            0x68,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Interrupt_Enable_3.value),
            True
        );
    }
    {
        registerHandle abEvent_Control_Timer_1_reg = ppmCreateRegister(
            "ab_Event_Control_Timer_1",
            "Enable, pulse and overflow",
            handles.bport1,
            0x6c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Event_Control_Timer_1.value),
            True
        );

        ppmCreateRegisterField(abEvent_Control_Timer_1_reg, "OV", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abEvent_Control_Timer_1_reg, "LO", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abEvent_Control_Timer_1_reg, "EN", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abEvent_Control_Timer_2_reg = ppmCreateRegister(
            "ab_Event_Control_Timer_2",
            "Enable, pulse and overflow",
            handles.bport1,
            0x70,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Event_Control_Timer_2.value),
            True
        );

        ppmCreateRegisterField(abEvent_Control_Timer_2_reg, "OV", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abEvent_Control_Timer_2_reg, "LO", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abEvent_Control_Timer_2_reg, "EN", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abEvent_Control_Timer_3_reg = ppmCreateRegister(
            "ab_Event_Control_Timer_3",
            "Enable, pulse and overflow",
            handles.bport1,
            0x74,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Event_Control_Timer_3.value),
            True
        );

        ppmCreateRegisterField(abEvent_Control_Timer_3_reg, "OV", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abEvent_Control_Timer_3_reg, "LO", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abEvent_Control_Timer_3_reg, "EN", 0, 0, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_Event_Register_1",
            "pclk cycle count for event",
            handles.bport1,
            0x78,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.Event_Register_1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Event_Register_2",
            "pclk cycle count for event",
            handles.bport1,
            0x7c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.Event_Register_2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_Event_Register_3",
            "pclk cycle count for event",
            handles.bport1,
            0x80,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.Event_Register_3.value),
            True
        );
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.Event_Register_3.value = (Uns32)(bport1_ab_data.Event_Register_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Event_Register_2.value = (Uns32)(bport1_ab_data.Event_Register_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Event_Register_1.value = (Uns32)(bport1_ab_data.Event_Register_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Event_Control_Timer_3.value = (Uns32)(bport1_ab_data.Event_Control_Timer_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Event_Control_Timer_2.value = (Uns32)(bport1_ab_data.Event_Control_Timer_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Event_Control_Timer_1.value = (Uns32)(bport1_ab_data.Event_Control_Timer_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Interrupt_Enable_3.value = (Uns32)(bport1_ab_data.Interrupt_Enable_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Interrupt_Enable_2.value = (Uns32)(bport1_ab_data.Interrupt_Enable_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Interrupt_Enable_1.value = (Uns32)(bport1_ab_data.Interrupt_Enable_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Interrupt_Register_3.value = (Uns32)(bport1_ab_data.Interrupt_Register_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Interrupt_Register_2.value = (Uns32)(bport1_ab_data.Interrupt_Register_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Interrupt_Register_1.value = (Uns32)(bport1_ab_data.Interrupt_Register_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Match_3_Counter_3.value = (Uns32)(bport1_ab_data.Match_3_Counter_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Match_3_Counter_2.value = (Uns32)(bport1_ab_data.Match_3_Counter_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Match_3_Counter_1.value = (Uns32)(bport1_ab_data.Match_3_Counter_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Match_2_Counter_3.value = (Uns32)(bport1_ab_data.Match_2_Counter_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Match_2_Counter_2.value = (Uns32)(bport1_ab_data.Match_2_Counter_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Match_2_Counter_1.value = (Uns32)(bport1_ab_data.Match_2_Counter_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Match_1_Counter_3.value = (Uns32)(bport1_ab_data.Match_1_Counter_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Match_1_Counter_2.value = (Uns32)(bport1_ab_data.Match_1_Counter_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Match_1_Counter_1.value = (Uns32)(bport1_ab_data.Match_1_Counter_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Interval_Counter_3.value = (Uns32)(bport1_ab_data.Interval_Counter_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Interval_Counter_2.value = (Uns32)(bport1_ab_data.Interval_Counter_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Interval_Counter_1.value = (Uns32)(bport1_ab_data.Interval_Counter_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Counter_Value_3.value = (Uns32)(bport1_ab_data.Counter_Value_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Counter_Value_2.value = (Uns32)(bport1_ab_data.Counter_Value_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Counter_Value_1.value = (Uns32)(bport1_ab_data.Counter_Value_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Counter_Control_3.value = (Uns32)(bport1_ab_data.Counter_Control_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000021));
        bport1_ab_data.Counter_Control_2.value = (Uns32)(bport1_ab_data.Counter_Control_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000021));
        bport1_ab_data.Counter_Control_1.value = (Uns32)(bport1_ab_data.Counter_Control_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000021));
        bport1_ab_data.Clock_Control_3.value = (Uns32)(bport1_ab_data.Clock_Control_3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Clock_Control_2.value = (Uns32)(bport1_ab_data.Clock_Control_2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Clock_Control_1.value = (Uns32)(bport1_ab_data.Clock_Control_1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Zynq 7000 Triple Timer Counter Registers");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model implements the full set of registers and basic behavior. It is not yet completed.");
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


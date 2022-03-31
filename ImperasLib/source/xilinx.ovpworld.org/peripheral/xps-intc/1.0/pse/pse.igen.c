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

plb_REG_dataT plb_REG_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "xps-intc", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.plb = ppmCreateSlaveBusPort("plb", 32);
    if (!handles.plb) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'plb'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle REGISR_reg = ppmCreateRegister(
            "REG_ISR",
            0,
            handles.plb,
            0x0,
            4,
            ReadISR,
            WriteISR,
            view32,
            &(plb_REG_data.ISR.value),
            True
        );

        ppmCreateRegisterField(REGISR_reg, "INT0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT2", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT3", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT4", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT5", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT7", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT8", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT9", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT10", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT11", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT12", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT13", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT14", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT15", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT16", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT17", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT18", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT19", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT20", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT21", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT22", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT23", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT24", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT25", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT26", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT27", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT28", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT29", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT30", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(REGISR_reg, "INT31", 0, 31, 1, 1, 1);
    }
    {
        registerHandle REGIPR_reg = ppmCreateRegister(
            "REG_IPR",
            0,
            handles.plb,
            0x4,
            4,
            ReadIPR,
            0,
            view32,
            &(plb_REG_data.IPR.value),
            True
        );

        ppmCreateRegisterField(REGIPR_reg, "INT0", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT1", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT2", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT3", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT4", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT5", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT6", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT7", 0, 7, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT8", 0, 8, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT9", 0, 9, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT10", 0, 10, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT11", 0, 11, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT12", 0, 12, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT13", 0, 13, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT14", 0, 14, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT15", 0, 15, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT16", 0, 16, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT17", 0, 17, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT18", 0, 18, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT19", 0, 19, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT20", 0, 20, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT21", 0, 21, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT22", 0, 22, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT23", 0, 23, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT24", 0, 24, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT25", 0, 25, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT26", 0, 26, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT27", 0, 27, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT28", 0, 28, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT29", 0, 29, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT30", 0, 30, 1, 1, 0);
        ppmCreateRegisterField(REGIPR_reg, "INT31", 0, 31, 1, 1, 0);
    }
    {
        registerHandle REGIER_reg = ppmCreateRegister(
            "REG_IER",
            0,
            handles.plb,
            0x8,
            4,
            ReadIER,
            WriteIER,
            view32,
            &(plb_REG_data.IER.value),
            True
        );

        ppmCreateRegisterField(REGIER_reg, "INT0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT2", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT3", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT4", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT5", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT7", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT8", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT9", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT10", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT11", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT12", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT13", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT14", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT15", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT16", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT17", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT18", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT19", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT20", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT21", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT22", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT23", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT24", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT25", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT26", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT27", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT28", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT29", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT30", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(REGIER_reg, "INT31", 0, 31, 1, 1, 1);
    }
    {
        registerHandle REGIAR_reg = ppmCreateRegister(
            "REG_IAR",
            0,
            handles.plb,
            0xc,
            4,
            0,
            WriteIAR,
            view32,
            &(plb_REG_data.IAR.value),
            True
        );

        ppmCreateRegisterField(REGIAR_reg, "INT0", 0, 0, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT1", 0, 1, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT2", 0, 2, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT3", 0, 3, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT4", 0, 4, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT5", 0, 5, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT6", 0, 6, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT7", 0, 7, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT8", 0, 8, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT9", 0, 9, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT10", 0, 10, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT11", 0, 11, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT12", 0, 12, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT13", 0, 13, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT14", 0, 14, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT15", 0, 15, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT16", 0, 16, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT17", 0, 17, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT18", 0, 18, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT19", 0, 19, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT20", 0, 20, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT21", 0, 21, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT22", 0, 22, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT23", 0, 23, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT24", 0, 24, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT25", 0, 25, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT26", 0, 26, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT27", 0, 27, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT28", 0, 28, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT29", 0, 29, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT30", 0, 30, 1, 0, 1);
        ppmCreateRegisterField(REGIAR_reg, "INT31", 0, 31, 1, 0, 1);
    }
    {
        registerHandle REGSIE_reg = ppmCreateRegister(
            "REG_SIE",
            0,
            handles.plb,
            0x10,
            4,
            0,
            WriteSIE,
            view32,
            &(plb_REG_data.SIE.value),
            True
        );

        ppmCreateRegisterField(REGSIE_reg, "INT0", 0, 0, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT1", 0, 1, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT2", 0, 2, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT3", 0, 3, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT4", 0, 4, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT5", 0, 5, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT6", 0, 6, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT7", 0, 7, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT8", 0, 8, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT9", 0, 9, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT10", 0, 10, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT11", 0, 11, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT12", 0, 12, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT13", 0, 13, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT14", 0, 14, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT15", 0, 15, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT16", 0, 16, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT17", 0, 17, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT18", 0, 18, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT19", 0, 19, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT20", 0, 20, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT21", 0, 21, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT22", 0, 22, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT23", 0, 23, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT24", 0, 24, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT25", 0, 25, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT26", 0, 26, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT27", 0, 27, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT28", 0, 28, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT29", 0, 29, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT30", 0, 30, 1, 0, 1);
        ppmCreateRegisterField(REGSIE_reg, "INT31", 0, 31, 1, 0, 1);
    }
    {
        registerHandle REGCIE_reg = ppmCreateRegister(
            "REG_CIE",
            0,
            handles.plb,
            0x14,
            4,
            0,
            WriteCIE,
            view32,
            &(plb_REG_data.CIE.value),
            True
        );

        ppmCreateRegisterField(REGCIE_reg, "INT0", 0, 0, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT1", 0, 1, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT2", 0, 2, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT3", 0, 3, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT4", 0, 4, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT5", 0, 5, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT6", 0, 6, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT7", 0, 7, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT8", 0, 8, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT9", 0, 9, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT10", 0, 10, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT11", 0, 11, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT12", 0, 12, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT13", 0, 13, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT14", 0, 14, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT15", 0, 15, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT16", 0, 16, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT17", 0, 17, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT18", 0, 18, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT19", 0, 19, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT20", 0, 20, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT21", 0, 21, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT22", 0, 22, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT23", 0, 23, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT24", 0, 24, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT25", 0, 25, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT26", 0, 26, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT27", 0, 27, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT28", 0, 28, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT29", 0, 29, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT30", 0, 30, 1, 0, 1);
        ppmCreateRegisterField(REGCIE_reg, "INT31", 0, 31, 1, 0, 1);
    }
    {
        ppmCreateRegister(
            "REG_IVR",
            0,
            handles.plb,
            0x18,
            4,
            ReadIVR,
            0,
            view32,
            &(plb_REG_data.IVR.value),
            True
        );
    }
    {
        registerHandle REGMER_reg = ppmCreateRegister(
            "REG_MER",
            0,
            handles.plb,
            0x1c,
            4,
            ReadMER,
            WriteMER,
            view32,
            &(plb_REG_data.MER.value),
            True
        );

        ppmCreateRegisterField(REGMER_reg, "ME", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(REGMER_reg, "HIE", 0, 1, 1, 1, 1);
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        plb_REG_data.MER.value = (Uns32)(plb_REG_data.MER.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        plb_REG_data.IVR.value = (Uns32)(plb_REG_data.IVR.value & ~(0xffffffff)) | ((0xffffffff) & (0xFFFFFFFF));
        plb_REG_data.CIE.value = (Uns32)(plb_REG_data.CIE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        plb_REG_data.SIE.value = (Uns32)(plb_REG_data.SIE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        plb_REG_data.IAR.value = (Uns32)(plb_REG_data.IAR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        plb_REG_data.IER.value = (Uns32)(plb_REG_data.IER.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        plb_REG_data.IPR.value = (Uns32)(plb_REG_data.IPR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        plb_REG_data.ISR.value = (Uns32)(plb_REG_data.ISR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Microblaze LogiCORE IP XPS Interrupt Controller");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model implements all of the required behavior sufficient to boot Linux");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "DS572 April 19, 2010 v2.01a");
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


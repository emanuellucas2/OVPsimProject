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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisFTM", "Example");
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

static PPM_WRITE_CB(bport1_ab_C0SC_maskWrite) {
    bport1_ab_data.C0SC.value = (bport1_ab_data.C0SC.value & BPORT1_AB_C0SC_WRNMASK) | (data & BPORT1_AB_C0SC_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C0V_maskWrite) {
    bport1_ab_data.C0V.value = (bport1_ab_data.C0V.value & BPORT1_AB_C0V_WRNMASK) | (data & BPORT1_AB_C0V_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C1SC_maskWrite) {
    bport1_ab_data.C1SC.value = (bport1_ab_data.C1SC.value & BPORT1_AB_C1SC_WRNMASK) | (data & BPORT1_AB_C1SC_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C1V_maskWrite) {
    bport1_ab_data.C1V.value = (bport1_ab_data.C1V.value & BPORT1_AB_C1V_WRNMASK) | (data & BPORT1_AB_C1V_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C2SC_maskWrite) {
    bport1_ab_data.C2SC.value = (bport1_ab_data.C2SC.value & BPORT1_AB_C2SC_WRNMASK) | (data & BPORT1_AB_C2SC_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C2V_maskWrite) {
    bport1_ab_data.C2V.value = (bport1_ab_data.C2V.value & BPORT1_AB_C2V_WRNMASK) | (data & BPORT1_AB_C2V_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C3SC_maskWrite) {
    bport1_ab_data.C3SC.value = (bport1_ab_data.C3SC.value & BPORT1_AB_C3SC_WRNMASK) | (data & BPORT1_AB_C3SC_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C3V_maskWrite) {
    bport1_ab_data.C3V.value = (bport1_ab_data.C3V.value & BPORT1_AB_C3V_WRNMASK) | (data & BPORT1_AB_C3V_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C4SC_maskWrite) {
    bport1_ab_data.C4SC.value = (bport1_ab_data.C4SC.value & BPORT1_AB_C4SC_WRNMASK) | (data & BPORT1_AB_C4SC_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C4V_maskWrite) {
    bport1_ab_data.C4V.value = (bport1_ab_data.C4V.value & BPORT1_AB_C4V_WRNMASK) | (data & BPORT1_AB_C4V_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C5SC_maskWrite) {
    bport1_ab_data.C5SC.value = (bport1_ab_data.C5SC.value & BPORT1_AB_C5SC_WRNMASK) | (data & BPORT1_AB_C5SC_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C5V_maskWrite) {
    bport1_ab_data.C5V.value = (bport1_ab_data.C5V.value & BPORT1_AB_C5V_WRNMASK) | (data & BPORT1_AB_C5V_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C6SC_maskWrite) {
    bport1_ab_data.C6SC.value = (bport1_ab_data.C6SC.value & BPORT1_AB_C6SC_WRNMASK) | (data & BPORT1_AB_C6SC_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C6V_maskWrite) {
    bport1_ab_data.C6V.value = (bport1_ab_data.C6V.value & BPORT1_AB_C6V_WRNMASK) | (data & BPORT1_AB_C6V_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C7SC_maskWrite) {
    bport1_ab_data.C7SC.value = (bport1_ab_data.C7SC.value & BPORT1_AB_C7SC_WRNMASK) | (data & BPORT1_AB_C7SC_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C7V_maskWrite) {
    bport1_ab_data.C7V.value = (bport1_ab_data.C7V.value & BPORT1_AB_C7V_WRNMASK) | (data & BPORT1_AB_C7V_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CNTIN_maskWrite) {
    bport1_ab_data.CNTIN.value = (bport1_ab_data.CNTIN.value & BPORT1_AB_CNTIN_WRNMASK) | (data & BPORT1_AB_CNTIN_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CNT_maskWrite) {
    bport1_ab_data.CNT.value = (bport1_ab_data.CNT.value & BPORT1_AB_CNT_WRNMASK) | (data & BPORT1_AB_CNT_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_COMBINE_maskWrite) {
    bport1_ab_data.COMBINE.value = (bport1_ab_data.COMBINE.value & BPORT1_AB_COMBINE_WRNMASK) | (data & BPORT1_AB_COMBINE_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CONF_maskWrite) {
    bport1_ab_data.CONF.value = (bport1_ab_data.CONF.value & BPORT1_AB_CONF_WRNMASK) | (data & BPORT1_AB_CONF_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DEADTIME_maskWrite) {
    bport1_ab_data.DEADTIME.value = (bport1_ab_data.DEADTIME.value & BPORT1_AB_DEADTIME_WRNMASK) | (data & BPORT1_AB_DEADTIME_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_EXTTRIG_maskWrite) {
    bport1_ab_data.EXTTRIG.value = (bport1_ab_data.EXTTRIG.value & BPORT1_AB_EXTTRIG_WRNMASK) | (data & BPORT1_AB_EXTTRIG_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FILTER_maskWrite) {
    bport1_ab_data.FILTER.value = (bport1_ab_data.FILTER.value & BPORT1_AB_FILTER_WRNMASK) | (data & BPORT1_AB_FILTER_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FLTCTRL_maskWrite) {
    bport1_ab_data.FLTCTRL.value = (bport1_ab_data.FLTCTRL.value & BPORT1_AB_FLTCTRL_WRNMASK) | (data & BPORT1_AB_FLTCTRL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FLTPOL_maskWrite) {
    bport1_ab_data.FLTPOL.value = (bport1_ab_data.FLTPOL.value & BPORT1_AB_FLTPOL_WRNMASK) | (data & BPORT1_AB_FLTPOL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FMS_maskWrite) {
    bport1_ab_data.FMS.value = (bport1_ab_data.FMS.value & BPORT1_AB_FMS_WRNMASK) | (data & BPORT1_AB_FMS_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_INVCTRL_maskWrite) {
    bport1_ab_data.INVCTRL.value = (bport1_ab_data.INVCTRL.value & BPORT1_AB_INVCTRL_WRNMASK) | (data & BPORT1_AB_INVCTRL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MODE_maskWrite) {
    bport1_ab_data.MODE.value = (bport1_ab_data.MODE.value & BPORT1_AB_MODE_WRNMASK) | (data & BPORT1_AB_MODE_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MOD_maskWrite) {
    bport1_ab_data.MOD.value = (bport1_ab_data.MOD.value & BPORT1_AB_MOD_WRNMASK) | (data & BPORT1_AB_MOD_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_OUTINIT_maskWrite) {
    bport1_ab_data.OUTINIT.value = (bport1_ab_data.OUTINIT.value & BPORT1_AB_OUTINIT_WRNMASK) | (data & BPORT1_AB_OUTINIT_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_OUTMASK_maskWrite) {
    bport1_ab_data.OUTMASK.value = (bport1_ab_data.OUTMASK.value & BPORT1_AB_OUTMASK_WRNMASK) | (data & BPORT1_AB_OUTMASK_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_POL_maskWrite) {
    bport1_ab_data.POL.value = (bport1_ab_data.POL.value & BPORT1_AB_POL_WRNMASK) | (data & BPORT1_AB_POL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PWMLOAD_maskWrite) {
    bport1_ab_data.PWMLOAD.value = (bport1_ab_data.PWMLOAD.value & BPORT1_AB_PWMLOAD_WRNMASK) | (data & BPORT1_AB_PWMLOAD_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_QDCTRL_maskWrite) {
    bport1_ab_data.QDCTRL.value = (bport1_ab_data.QDCTRL.value & BPORT1_AB_QDCTRL_WRNMASK) | (data & BPORT1_AB_QDCTRL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SWOCTRL_maskWrite) {
    bport1_ab_data.SWOCTRL.value = (bport1_ab_data.SWOCTRL.value & BPORT1_AB_SWOCTRL_WRNMASK) | (data & BPORT1_AB_SWOCTRL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SYNCONF_maskWrite) {
    bport1_ab_data.SYNCONF.value = (bport1_ab_data.SYNCONF.value & BPORT1_AB_SYNCONF_WRNMASK) | (data & BPORT1_AB_SYNCONF_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SYNC_maskWrite) {
    bport1_ab_data.SYNC.value = (bport1_ab_data.SYNC.value & BPORT1_AB_SYNC_WRNMASK) | (data & BPORT1_AB_SYNC_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abSC_reg = ppmCreateRegister(
            "ab_SC",
            "Status and Control, offset: 0x0 ",
            handles.bport1,
            0x0,
            4,
            readSC,
            writeSC,
            view32,
            &(bport1_ab_data.SC.value),
            True
        );

        ppmCreateRegisterField(abSC_reg, "CLKS", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(abSC_reg, "CPWMS", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abSC_reg, "PS", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abSC_reg, "TOF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abSC_reg, "TOIE", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abCNT_reg = ppmCreateRegister(
            "ab_CNT",
            "Counter, offset: 0x4 ",
            handles.bport1,
            0x4,
            4,
            read_32,
            bport1_ab_CNT_maskWrite,
            view32,
            &(bport1_ab_data.CNT.value),
            True
        );

        ppmCreateRegisterField(abCNT_reg, "COUNT", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abMOD_reg = ppmCreateRegister(
            "ab_MOD",
            "Modulo, offset: 0x8 ",
            handles.bport1,
            0x8,
            4,
            read_32,
            bport1_ab_MOD_maskWrite,
            view32,
            &(bport1_ab_data.MOD.value),
            True
        );

        ppmCreateRegisterField(abMOD_reg, "MOD", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abC0SC_reg = ppmCreateRegister(
            "ab_C0SC",
            "Channel (n) Status and Control, array offset: 0xC, array step: 0x8 ",
            handles.bport1,
            0xc,
            4,
            read_32,
            bport1_ab_C0SC_maskWrite,
            view32,
            &(bport1_ab_data.C0SC.value),
            True
        );

        ppmCreateRegisterField(abC0SC_reg, "CHF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abC0SC_reg, "CHIE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abC0SC_reg, "DMA", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abC0SC_reg, "ELSA", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abC0SC_reg, "ELSB", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abC0SC_reg, "MSA", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abC0SC_reg, "MSB", 0, 5, 1, 1, 1);
    }
    {
        registerHandle abC0V_reg = ppmCreateRegister(
            "ab_C0V",
            "Channel (n) Value, array offset: 0x10, array step: 0x8 ",
            handles.bport1,
            0x10,
            4,
            read_32,
            bport1_ab_C0V_maskWrite,
            view32,
            &(bport1_ab_data.C0V.value),
            True
        );

        ppmCreateRegisterField(abC0V_reg, "VAL", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abC1SC_reg = ppmCreateRegister(
            "ab_C1SC",
            "Channel (n) Status and Control, array offset: 0xC, array step: 0x8 ",
            handles.bport1,
            0x14,
            4,
            read_32,
            bport1_ab_C1SC_maskWrite,
            view32,
            &(bport1_ab_data.C1SC.value),
            True
        );

        ppmCreateRegisterField(abC1SC_reg, "CHF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abC1SC_reg, "CHIE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abC1SC_reg, "DMA", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abC1SC_reg, "ELSA", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abC1SC_reg, "ELSB", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abC1SC_reg, "MSA", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abC1SC_reg, "MSB", 0, 5, 1, 1, 1);
    }
    {
        registerHandle abC1V_reg = ppmCreateRegister(
            "ab_C1V",
            "Channel (n) Value, array offset: 0x10, array step: 0x8 ",
            handles.bport1,
            0x18,
            4,
            read_32,
            bport1_ab_C1V_maskWrite,
            view32,
            &(bport1_ab_data.C1V.value),
            True
        );

        ppmCreateRegisterField(abC1V_reg, "VAL", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abC2SC_reg = ppmCreateRegister(
            "ab_C2SC",
            "Channel (n) Status and Control, array offset: 0xC, array step: 0x8 ",
            handles.bport1,
            0x1c,
            4,
            read_32,
            bport1_ab_C2SC_maskWrite,
            view32,
            &(bport1_ab_data.C2SC.value),
            True
        );

        ppmCreateRegisterField(abC2SC_reg, "CHF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abC2SC_reg, "CHIE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abC2SC_reg, "DMA", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abC2SC_reg, "ELSA", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abC2SC_reg, "ELSB", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abC2SC_reg, "MSA", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abC2SC_reg, "MSB", 0, 5, 1, 1, 1);
    }
    {
        registerHandle abC2V_reg = ppmCreateRegister(
            "ab_C2V",
            "Channel (n) Value, array offset: 0x10, array step: 0x8 ",
            handles.bport1,
            0x20,
            4,
            read_32,
            bport1_ab_C2V_maskWrite,
            view32,
            &(bport1_ab_data.C2V.value),
            True
        );

        ppmCreateRegisterField(abC2V_reg, "VAL", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abC3SC_reg = ppmCreateRegister(
            "ab_C3SC",
            "Channel (n) Status and Control, array offset: 0xC, array step: 0x8 ",
            handles.bport1,
            0x24,
            4,
            read_32,
            bport1_ab_C3SC_maskWrite,
            view32,
            &(bport1_ab_data.C3SC.value),
            True
        );

        ppmCreateRegisterField(abC3SC_reg, "CHF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abC3SC_reg, "CHIE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abC3SC_reg, "DMA", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abC3SC_reg, "ELSA", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abC3SC_reg, "ELSB", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abC3SC_reg, "MSA", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abC3SC_reg, "MSB", 0, 5, 1, 1, 1);
    }
    {
        registerHandle abC3V_reg = ppmCreateRegister(
            "ab_C3V",
            "Channel (n) Value, array offset: 0x10, array step: 0x8 ",
            handles.bport1,
            0x28,
            4,
            read_32,
            bport1_ab_C3V_maskWrite,
            view32,
            &(bport1_ab_data.C3V.value),
            True
        );

        ppmCreateRegisterField(abC3V_reg, "VAL", 0, 0, 16, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_C4SC",
            "Channel (n) Status and Control, array offset: 0xC, array step: 0x8 ",
            handles.bport1,
            0x2c,
            4,
            read_32,
            bport1_ab_C4SC_maskWrite,
            view32,
            &(bport1_ab_data.C4SC.value),
            True
        );
    }
    {
        registerHandle abC4V_reg = ppmCreateRegister(
            "ab_C4V",
            "Channel (n) Value, array offset: 0x10, array step: 0x8 ",
            handles.bport1,
            0x30,
            4,
            read_32,
            bport1_ab_C4V_maskWrite,
            view32,
            &(bport1_ab_data.C4V.value),
            True
        );

        ppmCreateRegisterField(abC4V_reg, "VAL", 0, 0, 16, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_C5SC",
            "Channel (n) Status and Control, array offset: 0xC, array step: 0x8 ",
            handles.bport1,
            0x34,
            4,
            read_32,
            bport1_ab_C5SC_maskWrite,
            view32,
            &(bport1_ab_data.C5SC.value),
            True
        );
    }
    {
        registerHandle abC5V_reg = ppmCreateRegister(
            "ab_C5V",
            "Channel (n) Value, array offset: 0x10, array step: 0x8 ",
            handles.bport1,
            0x38,
            4,
            read_32,
            bport1_ab_C5V_maskWrite,
            view32,
            &(bport1_ab_data.C5V.value),
            True
        );

        ppmCreateRegisterField(abC5V_reg, "VAL", 0, 0, 16, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_C6SC",
            "Channel (n) Status and Control, array offset: 0xC, array step: 0x8 ",
            handles.bport1,
            0x3c,
            4,
            read_32,
            bport1_ab_C6SC_maskWrite,
            view32,
            &(bport1_ab_data.C6SC.value),
            True
        );
    }
    {
        registerHandle abC6V_reg = ppmCreateRegister(
            "ab_C6V",
            "Channel (n) Value, array offset: 0x10, array step: 0x8 ",
            handles.bport1,
            0x40,
            4,
            read_32,
            bport1_ab_C6V_maskWrite,
            view32,
            &(bport1_ab_data.C6V.value),
            True
        );

        ppmCreateRegisterField(abC6V_reg, "VAL", 0, 0, 16, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_C7SC",
            "Channel (n) Status and Control, array offset: 0xC, array step: 0x8 ",
            handles.bport1,
            0x44,
            4,
            read_32,
            bport1_ab_C7SC_maskWrite,
            view32,
            &(bport1_ab_data.C7SC.value),
            True
        );
    }
    {
        registerHandle abC7V_reg = ppmCreateRegister(
            "ab_C7V",
            "Channel (n) Value, array offset: 0x10, array step: 0x8 ",
            handles.bport1,
            0x48,
            4,
            read_32,
            bport1_ab_C7V_maskWrite,
            view32,
            &(bport1_ab_data.C7V.value),
            True
        );

        ppmCreateRegisterField(abC7V_reg, "VAL", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abCNTIN_reg = ppmCreateRegister(
            "ab_CNTIN",
            "Counter Initial Value, offset: 0x4C ",
            handles.bport1,
            0x4c,
            4,
            read_32,
            bport1_ab_CNTIN_maskWrite,
            view32,
            &(bport1_ab_data.CNTIN.value),
            True
        );

        ppmCreateRegisterField(abCNTIN_reg, "INIT", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abSTATUS_reg = ppmCreateRegister(
            "ab_STATUS",
            "Capture and Compare Status, offset: 0x50 ",
            handles.bport1,
            0x50,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.STATUS.value),
            True
        );

        ppmCreateRegisterField(abSTATUS_reg, "CH0F", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abSTATUS_reg, "CH1F", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abSTATUS_reg, "CH2F", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abSTATUS_reg, "CH3F", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abSTATUS_reg, "CH4F", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abSTATUS_reg, "CH5F", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abSTATUS_reg, "CH6F", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abSTATUS_reg, "CH7F", 0, 7, 1, 1, 1);
    }
    {
        registerHandle abMODE_reg = ppmCreateRegister(
            "ab_MODE",
            "Features Mode Selection, offset: 0x54 ",
            handles.bport1,
            0x54,
            4,
            read_32,
            bport1_ab_MODE_maskWrite,
            view32,
            &(bport1_ab_data.MODE.value),
            True
        );

        ppmCreateRegisterField(abMODE_reg, "CAPTEST", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abMODE_reg, "FAULTIE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abMODE_reg, "FAULTM", 0, 5, 2, 1, 1);
        ppmCreateRegisterField(abMODE_reg, "FTMEN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abMODE_reg, "INIT", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abMODE_reg, "PWMSYNC", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abMODE_reg, "WPDIS", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abSYNC_reg = ppmCreateRegister(
            "ab_SYNC",
            "Synchronization, offset: 0x58 ",
            handles.bport1,
            0x58,
            4,
            read_32,
            bport1_ab_SYNC_maskWrite,
            view32,
            &(bport1_ab_data.SYNC.value),
            True
        );

        ppmCreateRegisterField(abSYNC_reg, "CNTMAX", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abSYNC_reg, "CNTMIN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abSYNC_reg, "REINIT", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abSYNC_reg, "SWSYNC", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abSYNC_reg, "SYNCHOM", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abSYNC_reg, "TRIG0", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abSYNC_reg, "TRIG1", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abSYNC_reg, "TRIG2", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abOUTINIT_reg = ppmCreateRegister(
            "ab_OUTINIT",
            "Initial State for Channels Output, offset: 0x5C ",
            handles.bport1,
            0x5c,
            4,
            read_32,
            bport1_ab_OUTINIT_maskWrite,
            view32,
            &(bport1_ab_data.OUTINIT.value),
            True
        );

        ppmCreateRegisterField(abOUTINIT_reg, "CH0OI", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abOUTINIT_reg, "CH1OI", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abOUTINIT_reg, "CH2OI", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abOUTINIT_reg, "CH3OI", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abOUTINIT_reg, "CH4OI", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abOUTINIT_reg, "CH5OI", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abOUTINIT_reg, "CH6OI", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abOUTINIT_reg, "CH7OI", 0, 7, 1, 1, 1);
    }
    {
        registerHandle abOUTMASK_reg = ppmCreateRegister(
            "ab_OUTMASK",
            "Output Mask, offset: 0x60 ",
            handles.bport1,
            0x60,
            4,
            read_32,
            bport1_ab_OUTMASK_maskWrite,
            view32,
            &(bport1_ab_data.OUTMASK.value),
            True
        );

        ppmCreateRegisterField(abOUTMASK_reg, "CH0OM", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abOUTMASK_reg, "CH1OM", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abOUTMASK_reg, "CH2OM", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abOUTMASK_reg, "CH3OM", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abOUTMASK_reg, "CH4OM", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abOUTMASK_reg, "CH5OM", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abOUTMASK_reg, "CH6OM", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abOUTMASK_reg, "CH7OM", 0, 7, 1, 1, 1);
    }
    {
        registerHandle abCOMBINE_reg = ppmCreateRegister(
            "ab_COMBINE",
            "Function for Linked Channels, offset: 0x64 ",
            handles.bport1,
            0x64,
            4,
            read_32,
            bport1_ab_COMBINE_maskWrite,
            view32,
            &(bport1_ab_data.COMBINE.value),
            True
        );

        ppmCreateRegisterField(abCOMBINE_reg, "COMBINE0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "COMBINE1", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "COMBINE2", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "COMBINE3", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "COMP0", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "COMP1", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "COMP2", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "COMP3", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "DECAP0", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "DECAP1", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "DECAP2", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "DECAP3", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "DECAPEN0", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "DECAPEN1", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "DECAPEN2", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "DECAPEN3", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "DTEN0", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "DTEN1", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "DTEN2", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "DTEN3", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "FAULTEN0", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "FAULTEN1", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "FAULTEN2", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "FAULTEN3", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "SYNCEN0", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "SYNCEN1", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "SYNCEN2", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abCOMBINE_reg, "SYNCEN3", 0, 29, 1, 1, 1);
    }
    {
        registerHandle abDEADTIME_reg = ppmCreateRegister(
            "ab_DEADTIME",
            "Deadtime Insertion Control, offset: 0x68 ",
            handles.bport1,
            0x68,
            4,
            read_32,
            bport1_ab_DEADTIME_maskWrite,
            view32,
            &(bport1_ab_data.DEADTIME.value),
            True
        );

        ppmCreateRegisterField(abDEADTIME_reg, "DTPS", 0, 6, 2, 1, 1);
        ppmCreateRegisterField(abDEADTIME_reg, "DTVAL", 0, 0, 6, 1, 1);
    }
    {
        registerHandle abEXTTRIG_reg = ppmCreateRegister(
            "ab_EXTTRIG",
            "FTM External Trigger, offset: 0x6C ",
            handles.bport1,
            0x6c,
            4,
            read_32,
            bport1_ab_EXTTRIG_maskWrite,
            view32,
            &(bport1_ab_data.EXTTRIG.value),
            True
        );

        ppmCreateRegisterField(abEXTTRIG_reg, "CH0TRIG", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abEXTTRIG_reg, "CH1TRIG", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abEXTTRIG_reg, "CH2TRIG", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abEXTTRIG_reg, "CH3TRIG", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abEXTTRIG_reg, "CH4TRIG", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abEXTTRIG_reg, "CH5TRIG", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abEXTTRIG_reg, "INITTRIGEN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abEXTTRIG_reg, "TRIGF", 0, 7, 1, 1, 1);
    }
    {
        registerHandle abPOL_reg = ppmCreateRegister(
            "ab_POL",
            "Channels Polarity, offset: 0x70 ",
            handles.bport1,
            0x70,
            4,
            read_32,
            bport1_ab_POL_maskWrite,
            view32,
            &(bport1_ab_data.POL.value),
            True
        );

        ppmCreateRegisterField(abPOL_reg, "POL0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPOL_reg, "POL1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPOL_reg, "POL2", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPOL_reg, "POL3", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abPOL_reg, "POL4", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPOL_reg, "POL5", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPOL_reg, "POL6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPOL_reg, "POL7", 0, 7, 1, 1, 1);
    }
    {
        registerHandle abFMS_reg = ppmCreateRegister(
            "ab_FMS",
            "Fault Mode Status, offset: 0x74 ",
            handles.bport1,
            0x74,
            4,
            read_32,
            bport1_ab_FMS_maskWrite,
            view32,
            &(bport1_ab_data.FMS.value),
            True
        );

        ppmCreateRegisterField(abFMS_reg, "FAULTF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abFMS_reg, "FAULTF0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abFMS_reg, "FAULTF1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abFMS_reg, "FAULTF2", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abFMS_reg, "FAULTF3", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abFMS_reg, "FAULTIN", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abFMS_reg, "WPEN", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abFILTER_reg = ppmCreateRegister(
            "ab_FILTER",
            "Input Capture Filter Control, offset: 0x78 ",
            handles.bport1,
            0x78,
            4,
            read_32,
            bport1_ab_FILTER_maskWrite,
            view32,
            &(bport1_ab_data.FILTER.value),
            True
        );

        ppmCreateRegisterField(abFILTER_reg, "CH0FVAL", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(abFILTER_reg, "CH1FVAL", 0, 4, 4, 1, 1);
        ppmCreateRegisterField(abFILTER_reg, "CH2FVAL", 0, 8, 4, 1, 1);
        ppmCreateRegisterField(abFILTER_reg, "CH3FVAL", 0, 12, 4, 1, 1);
    }
    {
        registerHandle abFLTCTRL_reg = ppmCreateRegister(
            "ab_FLTCTRL",
            "Fault Control, offset: 0x7C ",
            handles.bport1,
            0x7c,
            4,
            read_32,
            bport1_ab_FLTCTRL_maskWrite,
            view32,
            &(bport1_ab_data.FLTCTRL.value),
            True
        );

        ppmCreateRegisterField(abFLTCTRL_reg, "FAULT0EN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abFLTCTRL_reg, "FAULT1EN", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abFLTCTRL_reg, "FAULT2EN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abFLTCTRL_reg, "FAULT3EN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abFLTCTRL_reg, "FFLTR0EN", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abFLTCTRL_reg, "FFLTR1EN", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abFLTCTRL_reg, "FFLTR2EN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abFLTCTRL_reg, "FFLTR3EN", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abFLTCTRL_reg, "FFVAL", 0, 8, 4, 1, 1);
    }
    {
        registerHandle abQDCTRL_reg = ppmCreateRegister(
            "ab_QDCTRL",
            "Quadrature Decoder Control and Status, offset: 0x80 ",
            handles.bport1,
            0x80,
            4,
            read_32,
            bport1_ab_QDCTRL_maskWrite,
            view32,
            &(bport1_ab_data.QDCTRL.value),
            True
        );

        ppmCreateRegisterField(abQDCTRL_reg, "PHAFLTREN", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abQDCTRL_reg, "PHAPOL", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abQDCTRL_reg, "PHBFLTREN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abQDCTRL_reg, "PHBPOL", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abQDCTRL_reg, "QUADEN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abQDCTRL_reg, "QUADIR", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abQDCTRL_reg, "QUADMODE", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abQDCTRL_reg, "TOFDIR", 0, 1, 1, 1, 1);
    }
    {
        registerHandle abCONF_reg = ppmCreateRegister(
            "ab_CONF",
            "Configuration, offset: 0x84 ",
            handles.bport1,
            0x84,
            4,
            read_32,
            bport1_ab_CONF_maskWrite,
            view32,
            &(bport1_ab_data.CONF.value),
            True
        );

        ppmCreateRegisterField(abCONF_reg, "BDMMODE", 0, 6, 2, 1, 1);
        ppmCreateRegisterField(abCONF_reg, "GTBEEN", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abCONF_reg, "GTBEOUT", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abCONF_reg, "NUMTOF", 0, 0, 5, 1, 1);
    }
    {
        registerHandle abFLTPOL_reg = ppmCreateRegister(
            "ab_FLTPOL",
            "FTM Fault Input Polarity, offset: 0x88 ",
            handles.bport1,
            0x88,
            4,
            read_32,
            bport1_ab_FLTPOL_maskWrite,
            view32,
            &(bport1_ab_data.FLTPOL.value),
            True
        );

        ppmCreateRegisterField(abFLTPOL_reg, "FLT0POL", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abFLTPOL_reg, "FLT1POL", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abFLTPOL_reg, "FLT2POL", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abFLTPOL_reg, "FLT3POL", 0, 3, 1, 1, 1);
    }
    {
        registerHandle abSYNCONF_reg = ppmCreateRegister(
            "ab_SYNCONF",
            "Synchronization Configuration, offset: 0x8C ",
            handles.bport1,
            0x8c,
            4,
            read_32,
            bport1_ab_SYNCONF_maskWrite,
            view32,
            &(bport1_ab_data.SYNCONF.value),
            True
        );

        ppmCreateRegisterField(abSYNCONF_reg, "CNTINC", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abSYNCONF_reg, "HWINVC", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abSYNCONF_reg, "HWOM", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abSYNCONF_reg, "HWRSTCNT", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abSYNCONF_reg, "HWSOC", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abSYNCONF_reg, "HWTRIGMODE", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abSYNCONF_reg, "HWWRBUF", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abSYNCONF_reg, "INVC", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abSYNCONF_reg, "SWINVC", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abSYNCONF_reg, "SWOC", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abSYNCONF_reg, "SWOM", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abSYNCONF_reg, "SWRSTCNT", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abSYNCONF_reg, "SWSOC", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abSYNCONF_reg, "SWWRBUF", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abSYNCONF_reg, "SYNCMODE", 0, 7, 1, 1, 1);
    }
    {
        registerHandle abINVCTRL_reg = ppmCreateRegister(
            "ab_INVCTRL",
            "FTM Inverting Control, offset: 0x90 ",
            handles.bport1,
            0x90,
            4,
            read_32,
            bport1_ab_INVCTRL_maskWrite,
            view32,
            &(bport1_ab_data.INVCTRL.value),
            True
        );

        ppmCreateRegisterField(abINVCTRL_reg, "INV0EN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abINVCTRL_reg, "INV1EN", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abINVCTRL_reg, "INV2EN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abINVCTRL_reg, "INV3EN", 0, 3, 1, 1, 1);
    }
    {
        registerHandle abSWOCTRL_reg = ppmCreateRegister(
            "ab_SWOCTRL",
            "FTM Software Output Control, offset: 0x94 ",
            handles.bport1,
            0x94,
            4,
            read_32,
            bport1_ab_SWOCTRL_maskWrite,
            view32,
            &(bport1_ab_data.SWOCTRL.value),
            True
        );

        ppmCreateRegisterField(abSWOCTRL_reg, "CH0OC", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abSWOCTRL_reg, "CH0OCV", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abSWOCTRL_reg, "CH1OC", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abSWOCTRL_reg, "CH1OCV", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abSWOCTRL_reg, "CH2OC", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abSWOCTRL_reg, "CH2OCV", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abSWOCTRL_reg, "CH3OC", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abSWOCTRL_reg, "CH3OCV", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abSWOCTRL_reg, "CH4OC", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abSWOCTRL_reg, "CH4OCV", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abSWOCTRL_reg, "CH5OC", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abSWOCTRL_reg, "CH5OCV", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abSWOCTRL_reg, "CH6OC", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abSWOCTRL_reg, "CH6OCV", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abSWOCTRL_reg, "CH7OC", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abSWOCTRL_reg, "CH7OCV", 0, 15, 1, 1, 1);
    }
    {
        registerHandle abPWMLOAD_reg = ppmCreateRegister(
            "ab_PWMLOAD",
            "FTM PWM Load, offset: 0x98 ",
            handles.bport1,
            0x98,
            4,
            read_32,
            bport1_ab_PWMLOAD_maskWrite,
            view32,
            &(bport1_ab_data.PWMLOAD.value),
            True
        );

        ppmCreateRegisterField(abPWMLOAD_reg, "CH0SEL", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPWMLOAD_reg, "CH1SEL", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPWMLOAD_reg, "CH2SEL", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPWMLOAD_reg, "CH3SEL", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abPWMLOAD_reg, "CH4SEL", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPWMLOAD_reg, "CH5SEL", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPWMLOAD_reg, "CH6SEL", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPWMLOAD_reg, "CH7SEL", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abPWMLOAD_reg, "LDOK", 0, 9, 1, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.PWMLOAD.value = (Uns32)(bport1_ab_data.PWMLOAD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SWOCTRL.value = (Uns32)(bport1_ab_data.SWOCTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.INVCTRL.value = (Uns32)(bport1_ab_data.INVCTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SYNCONF.value = (Uns32)(bport1_ab_data.SYNCONF.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.FLTPOL.value = (Uns32)(bport1_ab_data.FLTPOL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CONF.value = (Uns32)(bport1_ab_data.CONF.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.QDCTRL.value = (Uns32)(bport1_ab_data.QDCTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.FLTCTRL.value = (Uns32)(bport1_ab_data.FLTCTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.FILTER.value = (Uns32)(bport1_ab_data.FILTER.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.FMS.value = (Uns32)(bport1_ab_data.FMS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.POL.value = (Uns32)(bport1_ab_data.POL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.EXTTRIG.value = (Uns32)(bport1_ab_data.EXTTRIG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DEADTIME.value = (Uns32)(bport1_ab_data.DEADTIME.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.COMBINE.value = (Uns32)(bport1_ab_data.COMBINE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.OUTMASK.value = (Uns32)(bport1_ab_data.OUTMASK.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.OUTINIT.value = (Uns32)(bport1_ab_data.OUTINIT.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SYNC.value = (Uns32)(bport1_ab_data.SYNC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MODE.value = (Uns32)(bport1_ab_data.MODE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000004));
        bport1_ab_data.STATUS.value = (Uns32)(bport1_ab_data.STATUS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CNTIN.value = (Uns32)(bport1_ab_data.CNTIN.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.C7V.value = (Uns32)(bport1_ab_data.C7V.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.C7SC.value = (Uns32)(bport1_ab_data.C7SC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.C6V.value = (Uns32)(bport1_ab_data.C6V.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.C6SC.value = (Uns32)(bport1_ab_data.C6SC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.C5V.value = (Uns32)(bport1_ab_data.C5V.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.C5SC.value = (Uns32)(bport1_ab_data.C5SC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.C4V.value = (Uns32)(bport1_ab_data.C4V.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.C4SC.value = (Uns32)(bport1_ab_data.C4SC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.C3V.value = (Uns32)(bport1_ab_data.C3V.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.C3SC.value = (Uns32)(bport1_ab_data.C3SC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.C2V.value = (Uns32)(bport1_ab_data.C2V.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.C2SC.value = (Uns32)(bport1_ab_data.C2SC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.C1V.value = (Uns32)(bport1_ab_data.C1V.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.C1SC.value = (Uns32)(bport1_ab_data.C1SC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.C0V.value = (Uns32)(bport1_ab_data.C0V.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.C0SC.value = (Uns32)(bport1_ab_data.C0SC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MOD.value = (Uns32)(bport1_ab_data.MOD.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CNT.value = (Uns32)(bport1_ab_data.CNT.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SC.value = (Uns32)(bport1_ab_data.SC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the FTM peripheral used on the Freescale Kinetis platform");
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


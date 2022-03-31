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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisDAC", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_C0_maskWrite) {
    bport1_ab_data.C0.value = (bport1_ab_data.C0.value & BPORT1_AB_C0_WRNMASK) | (data & BPORT1_AB_C0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C1_maskWrite) {
    bport1_ab_data.C1.value = (bport1_ab_data.C1.value & BPORT1_AB_C1_WRNMASK) | (data & BPORT1_AB_C1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_C2_maskWrite) {
    bport1_ab_data.C2.value = (bport1_ab_data.C2.value & BPORT1_AB_C2_WRNMASK) | (data & BPORT1_AB_C2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT0H_maskWrite) {
    bport1_ab_data.DAT0H.value = (bport1_ab_data.DAT0H.value & BPORT1_AB_DAT0H_WRNMASK) | (data & BPORT1_AB_DAT0H_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT0L_maskWrite) {
    bport1_ab_data.DAT0L.value = (bport1_ab_data.DAT0L.value & BPORT1_AB_DAT0L_WRNMASK) | (data & BPORT1_AB_DAT0L_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT10H_maskWrite) {
    bport1_ab_data.DAT10H.value = (bport1_ab_data.DAT10H.value & BPORT1_AB_DAT10H_WRNMASK) | (data & BPORT1_AB_DAT10H_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT10L_maskWrite) {
    bport1_ab_data.DAT10L.value = (bport1_ab_data.DAT10L.value & BPORT1_AB_DAT10L_WRNMASK) | (data & BPORT1_AB_DAT10L_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT11H_maskWrite) {
    bport1_ab_data.DAT11H.value = (bport1_ab_data.DAT11H.value & BPORT1_AB_DAT11H_WRNMASK) | (data & BPORT1_AB_DAT11H_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT11L_maskWrite) {
    bport1_ab_data.DAT11L.value = (bport1_ab_data.DAT11L.value & BPORT1_AB_DAT11L_WRNMASK) | (data & BPORT1_AB_DAT11L_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT12H_maskWrite) {
    bport1_ab_data.DAT12H.value = (bport1_ab_data.DAT12H.value & BPORT1_AB_DAT12H_WRNMASK) | (data & BPORT1_AB_DAT12H_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT12L_maskWrite) {
    bport1_ab_data.DAT12L.value = (bport1_ab_data.DAT12L.value & BPORT1_AB_DAT12L_WRNMASK) | (data & BPORT1_AB_DAT12L_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT13H_maskWrite) {
    bport1_ab_data.DAT13H.value = (bport1_ab_data.DAT13H.value & BPORT1_AB_DAT13H_WRNMASK) | (data & BPORT1_AB_DAT13H_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT13L_maskWrite) {
    bport1_ab_data.DAT13L.value = (bport1_ab_data.DAT13L.value & BPORT1_AB_DAT13L_WRNMASK) | (data & BPORT1_AB_DAT13L_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT14H_maskWrite) {
    bport1_ab_data.DAT14H.value = (bport1_ab_data.DAT14H.value & BPORT1_AB_DAT14H_WRNMASK) | (data & BPORT1_AB_DAT14H_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT14L_maskWrite) {
    bport1_ab_data.DAT14L.value = (bport1_ab_data.DAT14L.value & BPORT1_AB_DAT14L_WRNMASK) | (data & BPORT1_AB_DAT14L_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT15H_maskWrite) {
    bport1_ab_data.DAT15H.value = (bport1_ab_data.DAT15H.value & BPORT1_AB_DAT15H_WRNMASK) | (data & BPORT1_AB_DAT15H_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT15L_maskWrite) {
    bport1_ab_data.DAT15L.value = (bport1_ab_data.DAT15L.value & BPORT1_AB_DAT15L_WRNMASK) | (data & BPORT1_AB_DAT15L_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT1H_maskWrite) {
    bport1_ab_data.DAT1H.value = (bport1_ab_data.DAT1H.value & BPORT1_AB_DAT1H_WRNMASK) | (data & BPORT1_AB_DAT1H_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT1L_maskWrite) {
    bport1_ab_data.DAT1L.value = (bport1_ab_data.DAT1L.value & BPORT1_AB_DAT1L_WRNMASK) | (data & BPORT1_AB_DAT1L_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT2H_maskWrite) {
    bport1_ab_data.DAT2H.value = (bport1_ab_data.DAT2H.value & BPORT1_AB_DAT2H_WRNMASK) | (data & BPORT1_AB_DAT2H_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT2L_maskWrite) {
    bport1_ab_data.DAT2L.value = (bport1_ab_data.DAT2L.value & BPORT1_AB_DAT2L_WRNMASK) | (data & BPORT1_AB_DAT2L_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT3H_maskWrite) {
    bport1_ab_data.DAT3H.value = (bport1_ab_data.DAT3H.value & BPORT1_AB_DAT3H_WRNMASK) | (data & BPORT1_AB_DAT3H_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT3L_maskWrite) {
    bport1_ab_data.DAT3L.value = (bport1_ab_data.DAT3L.value & BPORT1_AB_DAT3L_WRNMASK) | (data & BPORT1_AB_DAT3L_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT4H_maskWrite) {
    bport1_ab_data.DAT4H.value = (bport1_ab_data.DAT4H.value & BPORT1_AB_DAT4H_WRNMASK) | (data & BPORT1_AB_DAT4H_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT4L_maskWrite) {
    bport1_ab_data.DAT4L.value = (bport1_ab_data.DAT4L.value & BPORT1_AB_DAT4L_WRNMASK) | (data & BPORT1_AB_DAT4L_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT5H_maskWrite) {
    bport1_ab_data.DAT5H.value = (bport1_ab_data.DAT5H.value & BPORT1_AB_DAT5H_WRNMASK) | (data & BPORT1_AB_DAT5H_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT5L_maskWrite) {
    bport1_ab_data.DAT5L.value = (bport1_ab_data.DAT5L.value & BPORT1_AB_DAT5L_WRNMASK) | (data & BPORT1_AB_DAT5L_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT6H_maskWrite) {
    bport1_ab_data.DAT6H.value = (bport1_ab_data.DAT6H.value & BPORT1_AB_DAT6H_WRNMASK) | (data & BPORT1_AB_DAT6H_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT6L_maskWrite) {
    bport1_ab_data.DAT6L.value = (bport1_ab_data.DAT6L.value & BPORT1_AB_DAT6L_WRNMASK) | (data & BPORT1_AB_DAT6L_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT7H_maskWrite) {
    bport1_ab_data.DAT7H.value = (bport1_ab_data.DAT7H.value & BPORT1_AB_DAT7H_WRNMASK) | (data & BPORT1_AB_DAT7H_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT7L_maskWrite) {
    bport1_ab_data.DAT7L.value = (bport1_ab_data.DAT7L.value & BPORT1_AB_DAT7L_WRNMASK) | (data & BPORT1_AB_DAT7L_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT8H_maskWrite) {
    bport1_ab_data.DAT8H.value = (bport1_ab_data.DAT8H.value & BPORT1_AB_DAT8H_WRNMASK) | (data & BPORT1_AB_DAT8H_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT8L_maskWrite) {
    bport1_ab_data.DAT8L.value = (bport1_ab_data.DAT8L.value & BPORT1_AB_DAT8L_WRNMASK) | (data & BPORT1_AB_DAT8L_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT9H_maskWrite) {
    bport1_ab_data.DAT9H.value = (bport1_ab_data.DAT9H.value & BPORT1_AB_DAT9H_WRNMASK) | (data & BPORT1_AB_DAT9H_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DAT9L_maskWrite) {
    bport1_ab_data.DAT9L.value = (bport1_ab_data.DAT9L.value & BPORT1_AB_DAT9L_WRNMASK) | (data & BPORT1_AB_DAT9L_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SR_maskWrite) {
    bport1_ab_data.SR.value = (bport1_ab_data.SR.value & BPORT1_AB_SR_WRNMASK) | (data & BPORT1_AB_SR_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abDAT0L_reg = ppmCreateRegister(
            "ab_DAT0L",
            "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
            handles.bport1,
            0x0,
            1,
            read_8,
            bport1_ab_DAT0L_maskWrite,
            view8,
            &(bport1_ab_data.DAT0L.value),
            True
        );

        ppmCreateRegisterField(abDAT0L_reg, "DATA", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abDAT0H_reg = ppmCreateRegister(
            "ab_DAT0H",
            "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
            handles.bport1,
            0x1,
            1,
            read_8,
            bport1_ab_DAT0H_maskWrite,
            view8,
            &(bport1_ab_data.DAT0H.value),
            True
        );

        ppmCreateRegisterField(abDAT0H_reg, "DATA", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abDAT1L_reg = ppmCreateRegister(
            "ab_DAT1L",
            "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
            handles.bport1,
            0x2,
            1,
            read_8,
            bport1_ab_DAT1L_maskWrite,
            view8,
            &(bport1_ab_data.DAT1L.value),
            True
        );

        ppmCreateRegisterField(abDAT1L_reg, "DATA", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abDAT1H_reg = ppmCreateRegister(
            "ab_DAT1H",
            "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
            handles.bport1,
            0x3,
            1,
            read_8,
            bport1_ab_DAT1H_maskWrite,
            view8,
            &(bport1_ab_data.DAT1H.value),
            True
        );

        ppmCreateRegisterField(abDAT1H_reg, "DATA", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abDAT2L_reg = ppmCreateRegister(
            "ab_DAT2L",
            "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
            handles.bport1,
            0x4,
            1,
            read_8,
            bport1_ab_DAT2L_maskWrite,
            view8,
            &(bport1_ab_data.DAT2L.value),
            True
        );

        ppmCreateRegisterField(abDAT2L_reg, "DATA", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abDAT2H_reg = ppmCreateRegister(
            "ab_DAT2H",
            "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
            handles.bport1,
            0x5,
            1,
            read_8,
            bport1_ab_DAT2H_maskWrite,
            view8,
            &(bport1_ab_data.DAT2H.value),
            True
        );

        ppmCreateRegisterField(abDAT2H_reg, "DATA", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abDAT3L_reg = ppmCreateRegister(
            "ab_DAT3L",
            "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
            handles.bport1,
            0x6,
            1,
            read_8,
            bport1_ab_DAT3L_maskWrite,
            view8,
            &(bport1_ab_data.DAT3L.value),
            True
        );

        ppmCreateRegisterField(abDAT3L_reg, "DATA", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abDAT3H_reg = ppmCreateRegister(
            "ab_DAT3H",
            "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
            handles.bport1,
            0x7,
            1,
            read_8,
            bport1_ab_DAT3H_maskWrite,
            view8,
            &(bport1_ab_data.DAT3H.value),
            True
        );

        ppmCreateRegisterField(abDAT3H_reg, "DATA", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abDAT4L_reg = ppmCreateRegister(
            "ab_DAT4L",
            "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
            handles.bport1,
            0x8,
            1,
            read_8,
            bport1_ab_DAT4L_maskWrite,
            view8,
            &(bport1_ab_data.DAT4L.value),
            True
        );

        ppmCreateRegisterField(abDAT4L_reg, "DATA", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abDAT4H_reg = ppmCreateRegister(
            "ab_DAT4H",
            "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
            handles.bport1,
            0x9,
            1,
            read_8,
            bport1_ab_DAT4H_maskWrite,
            view8,
            &(bport1_ab_data.DAT4H.value),
            True
        );

        ppmCreateRegisterField(abDAT4H_reg, "DATA", 0, 0, 4, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_DAT5L",
            "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
            handles.bport1,
            0xa,
            1,
            read_8,
            bport1_ab_DAT5L_maskWrite,
            view8,
            &(bport1_ab_data.DAT5L.value),
            True
        );
    }
    {
        registerHandle abDAT5H_reg = ppmCreateRegister(
            "ab_DAT5H",
            "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
            handles.bport1,
            0xb,
            1,
            read_8,
            bport1_ab_DAT5H_maskWrite,
            view8,
            &(bport1_ab_data.DAT5H.value),
            True
        );

        ppmCreateRegisterField(abDAT5H_reg, "DATA", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abDAT6L_reg = ppmCreateRegister(
            "ab_DAT6L",
            "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
            handles.bport1,
            0xc,
            1,
            read_8,
            bport1_ab_DAT6L_maskWrite,
            view8,
            &(bport1_ab_data.DAT6L.value),
            True
        );

        ppmCreateRegisterField(abDAT6L_reg, "DATA", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abDAT6H_reg = ppmCreateRegister(
            "ab_DAT6H",
            "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
            handles.bport1,
            0xd,
            1,
            read_8,
            bport1_ab_DAT6H_maskWrite,
            view8,
            &(bport1_ab_data.DAT6H.value),
            True
        );

        ppmCreateRegisterField(abDAT6H_reg, "DATA", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abDAT7L_reg = ppmCreateRegister(
            "ab_DAT7L",
            "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
            handles.bport1,
            0xe,
            1,
            read_8,
            bport1_ab_DAT7L_maskWrite,
            view8,
            &(bport1_ab_data.DAT7L.value),
            True
        );

        ppmCreateRegisterField(abDAT7L_reg, "DATA", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abDAT7H_reg = ppmCreateRegister(
            "ab_DAT7H",
            "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
            handles.bport1,
            0xf,
            1,
            read_8,
            bport1_ab_DAT7H_maskWrite,
            view8,
            &(bport1_ab_data.DAT7H.value),
            True
        );

        ppmCreateRegisterField(abDAT7H_reg, "DATA", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abDAT8L_reg = ppmCreateRegister(
            "ab_DAT8L",
            "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
            handles.bport1,
            0x10,
            1,
            read_8,
            bport1_ab_DAT8L_maskWrite,
            view8,
            &(bport1_ab_data.DAT8L.value),
            True
        );

        ppmCreateRegisterField(abDAT8L_reg, "DATA", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abDAT8H_reg = ppmCreateRegister(
            "ab_DAT8H",
            "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
            handles.bport1,
            0x11,
            1,
            read_8,
            bport1_ab_DAT8H_maskWrite,
            view8,
            &(bport1_ab_data.DAT8H.value),
            True
        );

        ppmCreateRegisterField(abDAT8H_reg, "DATA", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abDAT9L_reg = ppmCreateRegister(
            "ab_DAT9L",
            "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
            handles.bport1,
            0x12,
            1,
            read_8,
            bport1_ab_DAT9L_maskWrite,
            view8,
            &(bport1_ab_data.DAT9L.value),
            True
        );

        ppmCreateRegisterField(abDAT9L_reg, "DATA", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abDAT9H_reg = ppmCreateRegister(
            "ab_DAT9H",
            "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
            handles.bport1,
            0x13,
            1,
            read_8,
            bport1_ab_DAT9H_maskWrite,
            view8,
            &(bport1_ab_data.DAT9H.value),
            True
        );

        ppmCreateRegisterField(abDAT9H_reg, "DATA", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abDAT10L_reg = ppmCreateRegister(
            "ab_DAT10L",
            "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
            handles.bport1,
            0x14,
            1,
            read_8,
            bport1_ab_DAT10L_maskWrite,
            view8,
            &(bport1_ab_data.DAT10L.value),
            True
        );

        ppmCreateRegisterField(abDAT10L_reg, "DATA", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abDAT10H_reg = ppmCreateRegister(
            "ab_DAT10H",
            "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
            handles.bport1,
            0x15,
            1,
            read_8,
            bport1_ab_DAT10H_maskWrite,
            view8,
            &(bport1_ab_data.DAT10H.value),
            True
        );

        ppmCreateRegisterField(abDAT10H_reg, "DATA", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abDAT11L_reg = ppmCreateRegister(
            "ab_DAT11L",
            "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
            handles.bport1,
            0x16,
            1,
            read_8,
            bport1_ab_DAT11L_maskWrite,
            view8,
            &(bport1_ab_data.DAT11L.value),
            True
        );

        ppmCreateRegisterField(abDAT11L_reg, "DATA", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abDAT11H_reg = ppmCreateRegister(
            "ab_DAT11H",
            "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
            handles.bport1,
            0x17,
            1,
            read_8,
            bport1_ab_DAT11H_maskWrite,
            view8,
            &(bport1_ab_data.DAT11H.value),
            True
        );

        ppmCreateRegisterField(abDAT11H_reg, "DATA", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abDAT12L_reg = ppmCreateRegister(
            "ab_DAT12L",
            "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
            handles.bport1,
            0x18,
            1,
            read_8,
            bport1_ab_DAT12L_maskWrite,
            view8,
            &(bport1_ab_data.DAT12L.value),
            True
        );

        ppmCreateRegisterField(abDAT12L_reg, "DATA", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abDAT12H_reg = ppmCreateRegister(
            "ab_DAT12H",
            "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
            handles.bport1,
            0x19,
            1,
            read_8,
            bport1_ab_DAT12H_maskWrite,
            view8,
            &(bport1_ab_data.DAT12H.value),
            True
        );

        ppmCreateRegisterField(abDAT12H_reg, "DATA", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abDAT13L_reg = ppmCreateRegister(
            "ab_DAT13L",
            "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
            handles.bport1,
            0x1a,
            1,
            read_8,
            bport1_ab_DAT13L_maskWrite,
            view8,
            &(bport1_ab_data.DAT13L.value),
            True
        );

        ppmCreateRegisterField(abDAT13L_reg, "DATA", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abDAT13H_reg = ppmCreateRegister(
            "ab_DAT13H",
            "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
            handles.bport1,
            0x1b,
            1,
            read_8,
            bport1_ab_DAT13H_maskWrite,
            view8,
            &(bport1_ab_data.DAT13H.value),
            True
        );

        ppmCreateRegisterField(abDAT13H_reg, "DATA", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abDAT14L_reg = ppmCreateRegister(
            "ab_DAT14L",
            "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
            handles.bport1,
            0x1c,
            1,
            read_8,
            bport1_ab_DAT14L_maskWrite,
            view8,
            &(bport1_ab_data.DAT14L.value),
            True
        );

        ppmCreateRegisterField(abDAT14L_reg, "DATA", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abDAT14H_reg = ppmCreateRegister(
            "ab_DAT14H",
            "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
            handles.bport1,
            0x1d,
            1,
            read_8,
            bport1_ab_DAT14H_maskWrite,
            view8,
            &(bport1_ab_data.DAT14H.value),
            True
        );

        ppmCreateRegisterField(abDAT14H_reg, "DATA", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abDAT15L_reg = ppmCreateRegister(
            "ab_DAT15L",
            "DAC Data Low Register, array offset: 0x0, array step: 0x2 ",
            handles.bport1,
            0x1e,
            1,
            read_8,
            bport1_ab_DAT15L_maskWrite,
            view8,
            &(bport1_ab_data.DAT15L.value),
            True
        );

        ppmCreateRegisterField(abDAT15L_reg, "DATA", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abDAT15H_reg = ppmCreateRegister(
            "ab_DAT15H",
            "DAC Data High Register, array offset: 0x1, array step: 0x2 ",
            handles.bport1,
            0x1f,
            1,
            read_8,
            bport1_ab_DAT15H_maskWrite,
            view8,
            &(bport1_ab_data.DAT15H.value),
            True
        );

        ppmCreateRegisterField(abDAT15H_reg, "DATA", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abSR_reg = ppmCreateRegister(
            "ab_SR",
            "DAC Status Register, offset: 0x20 ",
            handles.bport1,
            0x20,
            1,
            read_8,
            bport1_ab_SR_maskWrite,
            view8,
            &(bport1_ab_data.SR.value),
            True
        );

        ppmCreateRegisterField(abSR_reg, "DACBFRPBF", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abSR_reg, "DACBFRPTF", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abSR_reg, "DACBFWMF", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abC0_reg = ppmCreateRegister(
            "ab_C0",
            "DAC Control Register, offset: 0x21 ",
            handles.bport1,
            0x21,
            1,
            read_8,
            bport1_ab_C0_maskWrite,
            view8,
            &(bport1_ab_data.C0.value),
            True
        );

        ppmCreateRegisterField(abC0_reg, "DACBBIEN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abC0_reg, "DACBTIEN", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abC0_reg, "DACBWIEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abC0_reg, "LPEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abC0_reg, "DACSWTRG", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abC0_reg, "DACTRGSEL", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abC0_reg, "DACRFS", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abC0_reg, "DACEN", 0, 7, 1, 1, 1);
    }
    {
        registerHandle abC1_reg = ppmCreateRegister(
            "ab_C1",
            "DAC Control Register 1, offset: 0x22 ",
            handles.bport1,
            0x22,
            1,
            read_8,
            bport1_ab_C1_maskWrite,
            view8,
            &(bport1_ab_data.C1.value),
            True
        );

        ppmCreateRegisterField(abC1_reg, "DACBFEN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abC1_reg, "DACBFMD", 0, 1, 2, 1, 1);
        ppmCreateRegisterField(abC1_reg, "DACBFWM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(abC1_reg, "DMAEN", 0, 7, 1, 1, 1);
    }
    {
        registerHandle abC2_reg = ppmCreateRegister(
            "ab_C2",
            "DAC Control Register 2, offset: 0x23 ",
            handles.bport1,
            0x23,
            1,
            read_8,
            bport1_ab_C2_maskWrite,
            view8,
            &(bport1_ab_data.C2.value),
            True
        );

        ppmCreateRegisterField(abC2_reg, "DACBFUP", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(abC2_reg, "DACBFRP", 0, 4, 4, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.C2.value = (Uns8)(bport1_ab_data.C2.value & ~(0xff)) | ((0xff) & (0x0f));
        bport1_ab_data.C1.value = (Uns8)(bport1_ab_data.C1.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.C0.value = (Uns8)(bport1_ab_data.C0.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.SR.value = (Uns8)(bport1_ab_data.SR.value & ~(0xff)) | ((0xff) & (0x02));
        bport1_ab_data.DAT15H.value = (Uns8)(bport1_ab_data.DAT15H.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT15L.value = (Uns8)(bport1_ab_data.DAT15L.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT14H.value = (Uns8)(bport1_ab_data.DAT14H.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT14L.value = (Uns8)(bport1_ab_data.DAT14L.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT13H.value = (Uns8)(bport1_ab_data.DAT13H.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT13L.value = (Uns8)(bport1_ab_data.DAT13L.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT12H.value = (Uns8)(bport1_ab_data.DAT12H.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT12L.value = (Uns8)(bport1_ab_data.DAT12L.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT11H.value = (Uns8)(bport1_ab_data.DAT11H.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT11L.value = (Uns8)(bport1_ab_data.DAT11L.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT10H.value = (Uns8)(bport1_ab_data.DAT10H.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT10L.value = (Uns8)(bport1_ab_data.DAT10L.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT9H.value = (Uns8)(bport1_ab_data.DAT9H.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT9L.value = (Uns8)(bport1_ab_data.DAT9L.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT8H.value = (Uns8)(bport1_ab_data.DAT8H.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT8L.value = (Uns8)(bport1_ab_data.DAT8L.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT7H.value = (Uns8)(bport1_ab_data.DAT7H.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT7L.value = (Uns8)(bport1_ab_data.DAT7L.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT6H.value = (Uns8)(bport1_ab_data.DAT6H.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT6L.value = (Uns8)(bport1_ab_data.DAT6L.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT5H.value = (Uns8)(bport1_ab_data.DAT5H.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT5L.value = (Uns8)(bport1_ab_data.DAT5L.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT4H.value = (Uns8)(bport1_ab_data.DAT4H.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT4L.value = (Uns8)(bport1_ab_data.DAT4L.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT3H.value = (Uns8)(bport1_ab_data.DAT3H.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT3L.value = (Uns8)(bport1_ab_data.DAT3L.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT2H.value = (Uns8)(bport1_ab_data.DAT2H.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT2L.value = (Uns8)(bport1_ab_data.DAT2L.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT1H.value = (Uns8)(bport1_ab_data.DAT1H.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT1L.value = (Uns8)(bport1_ab_data.DAT1L.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT0H.value = (Uns8)(bport1_ab_data.DAT0H.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.DAT0L.value = (Uns8)(bport1_ab_data.DAT0L.value & ~(0xff)) | ((0xff) & (0x00));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the DAC peripheral used on the Freescale Kinetis platform");
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


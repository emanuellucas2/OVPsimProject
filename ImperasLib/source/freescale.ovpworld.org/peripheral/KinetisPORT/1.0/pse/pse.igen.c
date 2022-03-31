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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisPORT", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_DFCR_maskWrite) {
    bport1_ab_data.DFCR.value = (bport1_ab_data.DFCR.value & BPORT1_AB_DFCR_WRNMASK) | (data & BPORT1_AB_DFCR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DFER_maskWrite) {
    bport1_ab_data.DFER.value = (bport1_ab_data.DFER.value & BPORT1_AB_DFER_WRNMASK) | (data & BPORT1_AB_DFER_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_DFWR_maskWrite) {
    bport1_ab_data.DFWR.value = (bport1_ab_data.DFWR.value & BPORT1_AB_DFWR_WRNMASK) | (data & BPORT1_AB_DFWR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_GPCHR_maskWrite) {
    bport1_ab_data.GPCHR.value = (bport1_ab_data.GPCHR.value & BPORT1_AB_GPCHR_WRNMASK) | (data & BPORT1_AB_GPCHR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_GPCLR_maskWrite) {
    bport1_ab_data.GPCLR.value = (bport1_ab_data.GPCLR.value & BPORT1_AB_GPCLR_WRNMASK) | (data & BPORT1_AB_GPCLR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ISFR_maskWrite) {
    bport1_ab_data.ISFR.value = (bport1_ab_data.ISFR.value & BPORT1_AB_ISFR_WRNMASK) | (data & BPORT1_AB_ISFR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR0_maskWrite) {
    bport1_ab_data.PCR0.value = (bport1_ab_data.PCR0.value & BPORT1_AB_PCR0_WRNMASK) | (data & BPORT1_AB_PCR0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR10_maskWrite) {
    bport1_ab_data.PCR10.value = (bport1_ab_data.PCR10.value & BPORT1_AB_PCR10_WRNMASK) | (data & BPORT1_AB_PCR10_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR11_maskWrite) {
    bport1_ab_data.PCR11.value = (bport1_ab_data.PCR11.value & BPORT1_AB_PCR11_WRNMASK) | (data & BPORT1_AB_PCR11_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR12_maskWrite) {
    bport1_ab_data.PCR12.value = (bport1_ab_data.PCR12.value & BPORT1_AB_PCR12_WRNMASK) | (data & BPORT1_AB_PCR12_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR13_maskWrite) {
    bport1_ab_data.PCR13.value = (bport1_ab_data.PCR13.value & BPORT1_AB_PCR13_WRNMASK) | (data & BPORT1_AB_PCR13_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR14_maskWrite) {
    bport1_ab_data.PCR14.value = (bport1_ab_data.PCR14.value & BPORT1_AB_PCR14_WRNMASK) | (data & BPORT1_AB_PCR14_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR15_maskWrite) {
    bport1_ab_data.PCR15.value = (bport1_ab_data.PCR15.value & BPORT1_AB_PCR15_WRNMASK) | (data & BPORT1_AB_PCR15_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR16_maskWrite) {
    bport1_ab_data.PCR16.value = (bport1_ab_data.PCR16.value & BPORT1_AB_PCR16_WRNMASK) | (data & BPORT1_AB_PCR16_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR17_maskWrite) {
    bport1_ab_data.PCR17.value = (bport1_ab_data.PCR17.value & BPORT1_AB_PCR17_WRNMASK) | (data & BPORT1_AB_PCR17_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR18_maskWrite) {
    bport1_ab_data.PCR18.value = (bport1_ab_data.PCR18.value & BPORT1_AB_PCR18_WRNMASK) | (data & BPORT1_AB_PCR18_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR19_maskWrite) {
    bport1_ab_data.PCR19.value = (bport1_ab_data.PCR19.value & BPORT1_AB_PCR19_WRNMASK) | (data & BPORT1_AB_PCR19_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR1_maskWrite) {
    bport1_ab_data.PCR1.value = (bport1_ab_data.PCR1.value & BPORT1_AB_PCR1_WRNMASK) | (data & BPORT1_AB_PCR1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR20_maskWrite) {
    bport1_ab_data.PCR20.value = (bport1_ab_data.PCR20.value & BPORT1_AB_PCR20_WRNMASK) | (data & BPORT1_AB_PCR20_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR21_maskWrite) {
    bport1_ab_data.PCR21.value = (bport1_ab_data.PCR21.value & BPORT1_AB_PCR21_WRNMASK) | (data & BPORT1_AB_PCR21_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR22_maskWrite) {
    bport1_ab_data.PCR22.value = (bport1_ab_data.PCR22.value & BPORT1_AB_PCR22_WRNMASK) | (data & BPORT1_AB_PCR22_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR23_maskWrite) {
    bport1_ab_data.PCR23.value = (bport1_ab_data.PCR23.value & BPORT1_AB_PCR23_WRNMASK) | (data & BPORT1_AB_PCR23_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR24_maskWrite) {
    bport1_ab_data.PCR24.value = (bport1_ab_data.PCR24.value & BPORT1_AB_PCR24_WRNMASK) | (data & BPORT1_AB_PCR24_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR25_maskWrite) {
    bport1_ab_data.PCR25.value = (bport1_ab_data.PCR25.value & BPORT1_AB_PCR25_WRNMASK) | (data & BPORT1_AB_PCR25_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR26_maskWrite) {
    bport1_ab_data.PCR26.value = (bport1_ab_data.PCR26.value & BPORT1_AB_PCR26_WRNMASK) | (data & BPORT1_AB_PCR26_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR27_maskWrite) {
    bport1_ab_data.PCR27.value = (bport1_ab_data.PCR27.value & BPORT1_AB_PCR27_WRNMASK) | (data & BPORT1_AB_PCR27_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR28_maskWrite) {
    bport1_ab_data.PCR28.value = (bport1_ab_data.PCR28.value & BPORT1_AB_PCR28_WRNMASK) | (data & BPORT1_AB_PCR28_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR29_maskWrite) {
    bport1_ab_data.PCR29.value = (bport1_ab_data.PCR29.value & BPORT1_AB_PCR29_WRNMASK) | (data & BPORT1_AB_PCR29_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR2_maskWrite) {
    bport1_ab_data.PCR2.value = (bport1_ab_data.PCR2.value & BPORT1_AB_PCR2_WRNMASK) | (data & BPORT1_AB_PCR2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR30_maskWrite) {
    bport1_ab_data.PCR30.value = (bport1_ab_data.PCR30.value & BPORT1_AB_PCR30_WRNMASK) | (data & BPORT1_AB_PCR30_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR31_maskWrite) {
    bport1_ab_data.PCR31.value = (bport1_ab_data.PCR31.value & BPORT1_AB_PCR31_WRNMASK) | (data & BPORT1_AB_PCR31_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR3_maskWrite) {
    bport1_ab_data.PCR3.value = (bport1_ab_data.PCR3.value & BPORT1_AB_PCR3_WRNMASK) | (data & BPORT1_AB_PCR3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR4_maskWrite) {
    bport1_ab_data.PCR4.value = (bport1_ab_data.PCR4.value & BPORT1_AB_PCR4_WRNMASK) | (data & BPORT1_AB_PCR4_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR5_maskWrite) {
    bport1_ab_data.PCR5.value = (bport1_ab_data.PCR5.value & BPORT1_AB_PCR5_WRNMASK) | (data & BPORT1_AB_PCR5_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR6_maskWrite) {
    bport1_ab_data.PCR6.value = (bport1_ab_data.PCR6.value & BPORT1_AB_PCR6_WRNMASK) | (data & BPORT1_AB_PCR6_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR7_maskWrite) {
    bport1_ab_data.PCR7.value = (bport1_ab_data.PCR7.value & BPORT1_AB_PCR7_WRNMASK) | (data & BPORT1_AB_PCR7_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR8_maskWrite) {
    bport1_ab_data.PCR8.value = (bport1_ab_data.PCR8.value & BPORT1_AB_PCR8_WRNMASK) | (data & BPORT1_AB_PCR8_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_PCR9_maskWrite) {
    bport1_ab_data.PCR9.value = (bport1_ab_data.PCR9.value & BPORT1_AB_PCR9_WRNMASK) | (data & BPORT1_AB_PCR9_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abPCR0_reg = ppmCreateRegister(
            "ab_PCR0",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x0,
            4,
            read_32,
            bport1_ab_PCR0_maskWrite,
            view32,
            &(bport1_ab_data.PCR0.value),
            True
        );

        ppmCreateRegisterField(abPCR0_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR0_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR0_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR0_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR0_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR0_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR0_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR0_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR0_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR0_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR1_reg = ppmCreateRegister(
            "ab_PCR1",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x4,
            4,
            read_32,
            bport1_ab_PCR1_maskWrite,
            view32,
            &(bport1_ab_data.PCR1.value),
            True
        );

        ppmCreateRegisterField(abPCR1_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR1_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR1_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR1_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR1_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR1_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR1_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR1_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR1_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR1_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR2_reg = ppmCreateRegister(
            "ab_PCR2",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x8,
            4,
            read_32,
            bport1_ab_PCR2_maskWrite,
            view32,
            &(bport1_ab_data.PCR2.value),
            True
        );

        ppmCreateRegisterField(abPCR2_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR2_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR2_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR2_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR2_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR2_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR2_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR2_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR2_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR2_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR3_reg = ppmCreateRegister(
            "ab_PCR3",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0xc,
            4,
            read_32,
            bport1_ab_PCR3_maskWrite,
            view32,
            &(bport1_ab_data.PCR3.value),
            True
        );

        ppmCreateRegisterField(abPCR3_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR3_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR3_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR3_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR3_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR3_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR3_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR3_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR3_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR3_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR4_reg = ppmCreateRegister(
            "ab_PCR4",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x10,
            4,
            read_32,
            bport1_ab_PCR4_maskWrite,
            view32,
            &(bport1_ab_data.PCR4.value),
            True
        );

        ppmCreateRegisterField(abPCR4_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR4_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR4_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR4_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR4_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR4_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR4_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR4_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR4_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR4_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR5_reg = ppmCreateRegister(
            "ab_PCR5",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x14,
            4,
            read_32,
            bport1_ab_PCR5_maskWrite,
            view32,
            &(bport1_ab_data.PCR5.value),
            True
        );

        ppmCreateRegisterField(abPCR5_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR5_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR5_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR5_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR5_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR5_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR5_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR5_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR5_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR5_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR6_reg = ppmCreateRegister(
            "ab_PCR6",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x18,
            4,
            read_32,
            bport1_ab_PCR6_maskWrite,
            view32,
            &(bport1_ab_data.PCR6.value),
            True
        );

        ppmCreateRegisterField(abPCR6_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR6_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR6_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR6_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR6_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR6_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR6_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR6_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR6_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR6_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR7_reg = ppmCreateRegister(
            "ab_PCR7",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x1c,
            4,
            read_32,
            bport1_ab_PCR7_maskWrite,
            view32,
            &(bport1_ab_data.PCR7.value),
            True
        );

        ppmCreateRegisterField(abPCR7_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR7_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR7_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR7_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR7_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR7_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR7_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR7_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR7_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR7_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR8_reg = ppmCreateRegister(
            "ab_PCR8",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x20,
            4,
            read_32,
            bport1_ab_PCR8_maskWrite,
            view32,
            &(bport1_ab_data.PCR8.value),
            True
        );

        ppmCreateRegisterField(abPCR8_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR8_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR8_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR8_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR8_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR8_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR8_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR8_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR8_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR8_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR9_reg = ppmCreateRegister(
            "ab_PCR9",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x24,
            4,
            read_32,
            bport1_ab_PCR9_maskWrite,
            view32,
            &(bport1_ab_data.PCR9.value),
            True
        );

        ppmCreateRegisterField(abPCR9_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR9_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR9_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR9_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR9_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR9_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR9_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR9_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR9_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR9_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR10_reg = ppmCreateRegister(
            "ab_PCR10",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x28,
            4,
            read_32,
            bport1_ab_PCR10_maskWrite,
            view32,
            &(bport1_ab_data.PCR10.value),
            True
        );

        ppmCreateRegisterField(abPCR10_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR10_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR10_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR10_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR10_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR10_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR10_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR10_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR10_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR10_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR11_reg = ppmCreateRegister(
            "ab_PCR11",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x2c,
            4,
            read_32,
            bport1_ab_PCR11_maskWrite,
            view32,
            &(bport1_ab_data.PCR11.value),
            True
        );

        ppmCreateRegisterField(abPCR11_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR11_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR11_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR11_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR11_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR11_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR11_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR11_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR11_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR11_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR12_reg = ppmCreateRegister(
            "ab_PCR12",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x30,
            4,
            read_32,
            bport1_ab_PCR12_maskWrite,
            view32,
            &(bport1_ab_data.PCR12.value),
            True
        );

        ppmCreateRegisterField(abPCR12_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR12_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR12_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR12_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR12_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR12_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR12_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR12_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR12_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR12_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR13_reg = ppmCreateRegister(
            "ab_PCR13",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x34,
            4,
            read_32,
            bport1_ab_PCR13_maskWrite,
            view32,
            &(bport1_ab_data.PCR13.value),
            True
        );

        ppmCreateRegisterField(abPCR13_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR13_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR13_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR13_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR13_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR13_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR13_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR13_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR13_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR13_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR14_reg = ppmCreateRegister(
            "ab_PCR14",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x38,
            4,
            read_32,
            bport1_ab_PCR14_maskWrite,
            view32,
            &(bport1_ab_data.PCR14.value),
            True
        );

        ppmCreateRegisterField(abPCR14_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR14_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR14_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR14_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR14_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR14_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR14_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR14_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR14_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR14_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR15_reg = ppmCreateRegister(
            "ab_PCR15",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x3c,
            4,
            read_32,
            bport1_ab_PCR15_maskWrite,
            view32,
            &(bport1_ab_data.PCR15.value),
            True
        );

        ppmCreateRegisterField(abPCR15_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR15_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR15_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR15_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR15_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR15_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR15_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR15_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR15_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR15_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR16_reg = ppmCreateRegister(
            "ab_PCR16",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x40,
            4,
            read_32,
            bport1_ab_PCR16_maskWrite,
            view32,
            &(bport1_ab_data.PCR16.value),
            True
        );

        ppmCreateRegisterField(abPCR16_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR16_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR16_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR16_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR16_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR16_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR16_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR16_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR16_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR16_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR17_reg = ppmCreateRegister(
            "ab_PCR17",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x44,
            4,
            read_32,
            bport1_ab_PCR17_maskWrite,
            view32,
            &(bport1_ab_data.PCR17.value),
            True
        );

        ppmCreateRegisterField(abPCR17_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR17_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR17_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR17_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR17_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR17_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR17_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR17_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR17_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR17_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR18_reg = ppmCreateRegister(
            "ab_PCR18",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x48,
            4,
            read_32,
            bport1_ab_PCR18_maskWrite,
            view32,
            &(bport1_ab_data.PCR18.value),
            True
        );

        ppmCreateRegisterField(abPCR18_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR18_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR18_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR18_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR18_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR18_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR18_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR18_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR18_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR18_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR19_reg = ppmCreateRegister(
            "ab_PCR19",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x4c,
            4,
            read_32,
            bport1_ab_PCR19_maskWrite,
            view32,
            &(bport1_ab_data.PCR19.value),
            True
        );

        ppmCreateRegisterField(abPCR19_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR19_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR19_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR19_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR19_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR19_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR19_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR19_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR19_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR19_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR20_reg = ppmCreateRegister(
            "ab_PCR20",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x50,
            4,
            read_32,
            bport1_ab_PCR20_maskWrite,
            view32,
            &(bport1_ab_data.PCR20.value),
            True
        );

        ppmCreateRegisterField(abPCR20_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR20_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR20_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR20_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR20_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR20_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR20_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR20_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR20_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR20_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR21_reg = ppmCreateRegister(
            "ab_PCR21",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x54,
            4,
            read_32,
            bport1_ab_PCR21_maskWrite,
            view32,
            &(bport1_ab_data.PCR21.value),
            True
        );

        ppmCreateRegisterField(abPCR21_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR21_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR21_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR21_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR21_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR21_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR21_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR21_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR21_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR21_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR22_reg = ppmCreateRegister(
            "ab_PCR22",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x58,
            4,
            read_32,
            bport1_ab_PCR22_maskWrite,
            view32,
            &(bport1_ab_data.PCR22.value),
            True
        );

        ppmCreateRegisterField(abPCR22_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR22_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR22_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR22_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR22_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR22_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR22_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR22_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR22_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR22_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR23_reg = ppmCreateRegister(
            "ab_PCR23",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x5c,
            4,
            read_32,
            bport1_ab_PCR23_maskWrite,
            view32,
            &(bport1_ab_data.PCR23.value),
            True
        );

        ppmCreateRegisterField(abPCR23_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR23_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR23_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR23_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR23_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR23_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR23_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR23_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR23_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR23_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR24_reg = ppmCreateRegister(
            "ab_PCR24",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x60,
            4,
            read_32,
            bport1_ab_PCR24_maskWrite,
            view32,
            &(bport1_ab_data.PCR24.value),
            True
        );

        ppmCreateRegisterField(abPCR24_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR24_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR24_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR24_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR24_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR24_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR24_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR24_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR24_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR24_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR25_reg = ppmCreateRegister(
            "ab_PCR25",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x64,
            4,
            read_32,
            bport1_ab_PCR25_maskWrite,
            view32,
            &(bport1_ab_data.PCR25.value),
            True
        );

        ppmCreateRegisterField(abPCR25_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR25_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR25_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR25_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR25_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR25_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR25_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR25_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR25_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR25_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR26_reg = ppmCreateRegister(
            "ab_PCR26",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x68,
            4,
            read_32,
            bport1_ab_PCR26_maskWrite,
            view32,
            &(bport1_ab_data.PCR26.value),
            True
        );

        ppmCreateRegisterField(abPCR26_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR26_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR26_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR26_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR26_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR26_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR26_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR26_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR26_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR26_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR27_reg = ppmCreateRegister(
            "ab_PCR27",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x6c,
            4,
            read_32,
            bport1_ab_PCR27_maskWrite,
            view32,
            &(bport1_ab_data.PCR27.value),
            True
        );

        ppmCreateRegisterField(abPCR27_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR27_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR27_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR27_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR27_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR27_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR27_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR27_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR27_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR27_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR28_reg = ppmCreateRegister(
            "ab_PCR28",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x70,
            4,
            read_32,
            bport1_ab_PCR28_maskWrite,
            view32,
            &(bport1_ab_data.PCR28.value),
            True
        );

        ppmCreateRegisterField(abPCR28_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR28_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR28_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR28_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR28_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR28_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR28_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR28_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR28_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR28_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR29_reg = ppmCreateRegister(
            "ab_PCR29",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x74,
            4,
            read_32,
            bport1_ab_PCR29_maskWrite,
            view32,
            &(bport1_ab_data.PCR29.value),
            True
        );

        ppmCreateRegisterField(abPCR29_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR29_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR29_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR29_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR29_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR29_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR29_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR29_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR29_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR29_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR30_reg = ppmCreateRegister(
            "ab_PCR30",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x78,
            4,
            read_32,
            bport1_ab_PCR30_maskWrite,
            view32,
            &(bport1_ab_data.PCR30.value),
            True
        );

        ppmCreateRegisterField(abPCR30_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR30_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR30_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR30_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR30_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR30_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR30_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR30_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR30_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR30_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abPCR31_reg = ppmCreateRegister(
            "ab_PCR31",
            "Pin Control Register n, array offset: 0x0, array step: 0x4 ",
            handles.bport1,
            0x7c,
            4,
            read_32,
            bport1_ab_PCR31_maskWrite,
            view32,
            &(bport1_ab_data.PCR31.value),
            True
        );

        ppmCreateRegisterField(abPCR31_reg, "DSE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPCR31_reg, "IRQC", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abPCR31_reg, "ISF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abPCR31_reg, "LK", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abPCR31_reg, "MUX", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPCR31_reg, "ODE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abPCR31_reg, "PE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPCR31_reg, "PFE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abPCR31_reg, "PS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abPCR31_reg, "SRE", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abGPCLR_reg = ppmCreateRegister(
            "ab_GPCLR",
            "Global Pin Control Low Register, offset: 0x80 ",
            handles.bport1,
            0x80,
            4,
            0,
            bport1_ab_GPCLR_maskWrite,
            view32,
            &(bport1_ab_data.GPCLR.value),
            True
        );

        ppmCreateRegisterField(abGPCLR_reg, "GPWD", 0, 0, 16, 0, 1);
        ppmCreateRegisterField(abGPCLR_reg, "GPWE", 0, 16, 16, 0, 1);
    }
    {
        registerHandle abGPCHR_reg = ppmCreateRegister(
            "ab_GPCHR",
            "Global Pin Control High Register, offset: 0x84 ",
            handles.bport1,
            0x84,
            4,
            0,
            bport1_ab_GPCHR_maskWrite,
            view32,
            &(bport1_ab_data.GPCHR.value),
            True
        );

        ppmCreateRegisterField(abGPCHR_reg, "GPWD", 0, 0, 16, 0, 1);
        ppmCreateRegisterField(abGPCHR_reg, "GPWE", 0, 16, 16, 0, 1);
    }
    {
        registerHandle abISFR_reg = ppmCreateRegister(
            "ab_ISFR",
            "Interrupt Status Flag Register, offset: 0xA0 ",
            handles.bport1,
            0xa0,
            4,
            read_32,
            bport1_ab_ISFR_maskWrite,
            view32,
            &(bport1_ab_data.ISFR.value),
            True
        );

        ppmCreateRegisterField(abISFR_reg, "ISF", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDFER_reg = ppmCreateRegister(
            "ab_DFER",
            "Digital Filter Enable Register, offset: 0xC0 ",
            handles.bport1,
            0xc0,
            4,
            read_32,
            bport1_ab_DFER_maskWrite,
            view32,
            &(bport1_ab_data.DFER.value),
            True
        );

        ppmCreateRegisterField(abDFER_reg, "DFE", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abDFCR_reg = ppmCreateRegister(
            "ab_DFCR",
            "Digital Filter Clock Register, offset: 0xC4 ",
            handles.bport1,
            0xc4,
            4,
            read_32,
            bport1_ab_DFCR_maskWrite,
            view32,
            &(bport1_ab_data.DFCR.value),
            True
        );

        ppmCreateRegisterField(abDFCR_reg, "CS", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abDFWR_reg = ppmCreateRegister(
            "ab_DFWR",
            "Digital Filter Width Register, offset: 0xC8 ",
            handles.bport1,
            0xc8,
            4,
            read_32,
            bport1_ab_DFWR_maskWrite,
            view32,
            &(bport1_ab_data.DFWR.value),
            True
        );

        ppmCreateRegisterField(abDFWR_reg, "FILT", 0, 0, 5, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.DFWR.value = (Uns32)(bport1_ab_data.DFWR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DFCR.value = (Uns32)(bport1_ab_data.DFCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DFER.value = (Uns32)(bport1_ab_data.DFER.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ISFR.value = (Uns32)(bport1_ab_data.ISFR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPCHR.value = (Uns32)(bport1_ab_data.GPCHR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPCLR.value = (Uns32)(bport1_ab_data.GPCLR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR31.value = (Uns32)(bport1_ab_data.PCR31.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR30.value = (Uns32)(bport1_ab_data.PCR30.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR29.value = (Uns32)(bport1_ab_data.PCR29.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR28.value = (Uns32)(bport1_ab_data.PCR28.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR27.value = (Uns32)(bport1_ab_data.PCR27.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR26.value = (Uns32)(bport1_ab_data.PCR26.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR25.value = (Uns32)(bport1_ab_data.PCR25.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR24.value = (Uns32)(bport1_ab_data.PCR24.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR23.value = (Uns32)(bport1_ab_data.PCR23.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR22.value = (Uns32)(bport1_ab_data.PCR22.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR21.value = (Uns32)(bport1_ab_data.PCR21.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR20.value = (Uns32)(bport1_ab_data.PCR20.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR19.value = (Uns32)(bport1_ab_data.PCR19.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR18.value = (Uns32)(bport1_ab_data.PCR18.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR17.value = (Uns32)(bport1_ab_data.PCR17.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR16.value = (Uns32)(bport1_ab_data.PCR16.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR15.value = (Uns32)(bport1_ab_data.PCR15.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR14.value = (Uns32)(bport1_ab_data.PCR14.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR13.value = (Uns32)(bport1_ab_data.PCR13.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR12.value = (Uns32)(bport1_ab_data.PCR12.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR11.value = (Uns32)(bport1_ab_data.PCR11.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR10.value = (Uns32)(bport1_ab_data.PCR10.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR9.value = (Uns32)(bport1_ab_data.PCR9.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR8.value = (Uns32)(bport1_ab_data.PCR8.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR7.value = (Uns32)(bport1_ab_data.PCR7.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR6.value = (Uns32)(bport1_ab_data.PCR6.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR5.value = (Uns32)(bport1_ab_data.PCR5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR4.value = (Uns32)(bport1_ab_data.PCR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR3.value = (Uns32)(bport1_ab_data.PCR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR2.value = (Uns32)(bport1_ab_data.PCR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR1.value = (Uns32)(bport1_ab_data.PCR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCR0.value = (Uns32)(bport1_ab_data.PCR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the PORT peripheral used on the Freescale Kinetis platform");
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


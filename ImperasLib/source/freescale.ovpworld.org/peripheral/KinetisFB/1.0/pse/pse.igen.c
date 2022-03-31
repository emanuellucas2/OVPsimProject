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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisFB", "Example");
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

static PPM_WRITE_CB(bport1_ab_CSAR0_maskWrite) {
    bport1_ab_data.CSAR0.value = (bport1_ab_data.CSAR0.value & BPORT1_AB_CSAR0_WRNMASK) | (data & BPORT1_AB_CSAR0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CSAR1_maskWrite) {
    bport1_ab_data.CSAR1.value = (bport1_ab_data.CSAR1.value & BPORT1_AB_CSAR1_WRNMASK) | (data & BPORT1_AB_CSAR1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CSAR2_maskWrite) {
    bport1_ab_data.CSAR2.value = (bport1_ab_data.CSAR2.value & BPORT1_AB_CSAR2_WRNMASK) | (data & BPORT1_AB_CSAR2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CSAR3_maskWrite) {
    bport1_ab_data.CSAR3.value = (bport1_ab_data.CSAR3.value & BPORT1_AB_CSAR3_WRNMASK) | (data & BPORT1_AB_CSAR3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CSAR4_maskWrite) {
    bport1_ab_data.CSAR4.value = (bport1_ab_data.CSAR4.value & BPORT1_AB_CSAR4_WRNMASK) | (data & BPORT1_AB_CSAR4_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CSAR5_maskWrite) {
    bport1_ab_data.CSAR5.value = (bport1_ab_data.CSAR5.value & BPORT1_AB_CSAR5_WRNMASK) | (data & BPORT1_AB_CSAR5_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CSCR0_maskWrite) {
    bport1_ab_data.CSCR0.value = (bport1_ab_data.CSCR0.value & BPORT1_AB_CSCR0_WRNMASK) | (data & BPORT1_AB_CSCR0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CSCR1_maskWrite) {
    bport1_ab_data.CSCR1.value = (bport1_ab_data.CSCR1.value & BPORT1_AB_CSCR1_WRNMASK) | (data & BPORT1_AB_CSCR1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CSCR2_maskWrite) {
    bport1_ab_data.CSCR2.value = (bport1_ab_data.CSCR2.value & BPORT1_AB_CSCR2_WRNMASK) | (data & BPORT1_AB_CSCR2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CSCR3_maskWrite) {
    bport1_ab_data.CSCR3.value = (bport1_ab_data.CSCR3.value & BPORT1_AB_CSCR3_WRNMASK) | (data & BPORT1_AB_CSCR3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CSCR4_maskWrite) {
    bport1_ab_data.CSCR4.value = (bport1_ab_data.CSCR4.value & BPORT1_AB_CSCR4_WRNMASK) | (data & BPORT1_AB_CSCR4_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CSCR5_maskWrite) {
    bport1_ab_data.CSCR5.value = (bport1_ab_data.CSCR5.value & BPORT1_AB_CSCR5_WRNMASK) | (data & BPORT1_AB_CSCR5_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CSMR0_maskWrite) {
    bport1_ab_data.CSMR0.value = (bport1_ab_data.CSMR0.value & BPORT1_AB_CSMR0_WRNMASK) | (data & BPORT1_AB_CSMR0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CSMR1_maskWrite) {
    bport1_ab_data.CSMR1.value = (bport1_ab_data.CSMR1.value & BPORT1_AB_CSMR1_WRNMASK) | (data & BPORT1_AB_CSMR1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CSMR2_maskWrite) {
    bport1_ab_data.CSMR2.value = (bport1_ab_data.CSMR2.value & BPORT1_AB_CSMR2_WRNMASK) | (data & BPORT1_AB_CSMR2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CSMR3_maskWrite) {
    bport1_ab_data.CSMR3.value = (bport1_ab_data.CSMR3.value & BPORT1_AB_CSMR3_WRNMASK) | (data & BPORT1_AB_CSMR3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CSMR4_maskWrite) {
    bport1_ab_data.CSMR4.value = (bport1_ab_data.CSMR4.value & BPORT1_AB_CSMR4_WRNMASK) | (data & BPORT1_AB_CSMR4_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CSMR5_maskWrite) {
    bport1_ab_data.CSMR5.value = (bport1_ab_data.CSMR5.value & BPORT1_AB_CSMR5_WRNMASK) | (data & BPORT1_AB_CSMR5_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CSPMCR_maskWrite) {
    bport1_ab_data.CSPMCR.value = (bport1_ab_data.CSPMCR.value & BPORT1_AB_CSPMCR_WRNMASK) | (data & BPORT1_AB_CSPMCR_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abCSAR0_reg = ppmCreateRegister(
            "ab_CSAR0",
            "Chip select address register, array offset: 0x0, array step: 0xC ",
            handles.bport1,
            0x0,
            4,
            read_32,
            bport1_ab_CSAR0_maskWrite,
            view32,
            &(bport1_ab_data.CSAR0.value),
            True
        );

        ppmCreateRegisterField(abCSAR0_reg, "BA", 0, 16, 16, 1, 1);
    }
    {
        registerHandle abCSMR0_reg = ppmCreateRegister(
            "ab_CSMR0",
            "Chip select mask register, array offset: 0x4, array step: 0xC ",
            handles.bport1,
            0x4,
            4,
            read_32,
            bport1_ab_CSMR0_maskWrite,
            view32,
            &(bport1_ab_data.CSMR0.value),
            True
        );

        ppmCreateRegisterField(abCSMR0_reg, "BAM", 0, 16, 16, 1, 1);
        ppmCreateRegisterField(abCSMR0_reg, "V", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abCSMR0_reg, "WP", 0, 8, 1, 1, 1);
    }
    {
        registerHandle abCSCR0_reg = ppmCreateRegister(
            "ab_CSCR0",
            "Chip select control register, array offset: 0x8, array step: 0xC ",
            handles.bport1,
            0x8,
            4,
            read_32,
            bport1_ab_CSCR0_maskWrite,
            view32,
            &(bport1_ab_data.CSCR0.value),
            True
        );

        ppmCreateRegisterField(abCSCR0_reg, "AA", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abCSCR0_reg, "ASET", 0, 20, 2, 1, 1);
        ppmCreateRegisterField(abCSCR0_reg, "BEM", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abCSCR0_reg, "BLS", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abCSCR0_reg, "BSTR", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abCSCR0_reg, "BSTW", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abCSCR0_reg, "EXTS", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abCSCR0_reg, "PS", 0, 6, 2, 1, 1);
        ppmCreateRegisterField(abCSCR0_reg, "RDAH", 0, 18, 2, 1, 1);
        ppmCreateRegisterField(abCSCR0_reg, "SWS", 0, 26, 6, 1, 1);
        ppmCreateRegisterField(abCSCR0_reg, "SWSEN", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abCSCR0_reg, "WRAH", 0, 16, 2, 1, 1);
        ppmCreateRegisterField(abCSCR0_reg, "WS", 0, 10, 6, 1, 1);
    }
    {
        registerHandle abCSAR1_reg = ppmCreateRegister(
            "ab_CSAR1",
            "Chip select address register, array offset: 0x0, array step: 0xC ",
            handles.bport1,
            0xc,
            4,
            read_32,
            bport1_ab_CSAR1_maskWrite,
            view32,
            &(bport1_ab_data.CSAR1.value),
            True
        );

        ppmCreateRegisterField(abCSAR1_reg, "BA", 0, 16, 16, 1, 1);
    }
    {
        registerHandle abCSMR1_reg = ppmCreateRegister(
            "ab_CSMR1",
            "Chip select mask register, array offset: 0x4, array step: 0xC ",
            handles.bport1,
            0x10,
            4,
            read_32,
            bport1_ab_CSMR1_maskWrite,
            view32,
            &(bport1_ab_data.CSMR1.value),
            True
        );

        ppmCreateRegisterField(abCSMR1_reg, "BAM", 0, 16, 16, 1, 1);
        ppmCreateRegisterField(abCSMR1_reg, "V", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abCSMR1_reg, "WP", 0, 8, 1, 1, 1);
    }
    {
        registerHandle abCSCR1_reg = ppmCreateRegister(
            "ab_CSCR1",
            "Chip select control register, array offset: 0x8, array step: 0xC ",
            handles.bport1,
            0x14,
            4,
            read_32,
            bport1_ab_CSCR1_maskWrite,
            view32,
            &(bport1_ab_data.CSCR1.value),
            True
        );

        ppmCreateRegisterField(abCSCR1_reg, "AA", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abCSCR1_reg, "ASET", 0, 20, 2, 1, 1);
        ppmCreateRegisterField(abCSCR1_reg, "BEM", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abCSCR1_reg, "BLS", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abCSCR1_reg, "BSTR", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abCSCR1_reg, "BSTW", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abCSCR1_reg, "EXTS", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abCSCR1_reg, "PS", 0, 6, 2, 1, 1);
        ppmCreateRegisterField(abCSCR1_reg, "RDAH", 0, 18, 2, 1, 1);
        ppmCreateRegisterField(abCSCR1_reg, "SWS", 0, 26, 6, 1, 1);
        ppmCreateRegisterField(abCSCR1_reg, "SWSEN", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abCSCR1_reg, "WRAH", 0, 16, 2, 1, 1);
        ppmCreateRegisterField(abCSCR1_reg, "WS", 0, 10, 6, 1, 1);
    }
    {
        registerHandle abCSAR2_reg = ppmCreateRegister(
            "ab_CSAR2",
            "Chip select address register, array offset: 0x0, array step: 0xC ",
            handles.bport1,
            0x18,
            4,
            read_32,
            bport1_ab_CSAR2_maskWrite,
            view32,
            &(bport1_ab_data.CSAR2.value),
            True
        );

        ppmCreateRegisterField(abCSAR2_reg, "BA", 0, 16, 16, 1, 1);
    }
    {
        registerHandle abCSMR2_reg = ppmCreateRegister(
            "ab_CSMR2",
            "Chip select mask register, array offset: 0x4, array step: 0xC ",
            handles.bport1,
            0x1c,
            4,
            read_32,
            bport1_ab_CSMR2_maskWrite,
            view32,
            &(bport1_ab_data.CSMR2.value),
            True
        );

        ppmCreateRegisterField(abCSMR2_reg, "BAM", 0, 16, 16, 1, 1);
        ppmCreateRegisterField(abCSMR2_reg, "V", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abCSMR2_reg, "WP", 0, 8, 1, 1, 1);
    }
    {
        registerHandle abCSCR2_reg = ppmCreateRegister(
            "ab_CSCR2",
            "Chip select control register, array offset: 0x8, array step: 0xC ",
            handles.bport1,
            0x20,
            4,
            read_32,
            bport1_ab_CSCR2_maskWrite,
            view32,
            &(bport1_ab_data.CSCR2.value),
            True
        );

        ppmCreateRegisterField(abCSCR2_reg, "AA", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abCSCR2_reg, "ASET", 0, 20, 2, 1, 1);
        ppmCreateRegisterField(abCSCR2_reg, "BEM", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abCSCR2_reg, "BLS", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abCSCR2_reg, "BSTR", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abCSCR2_reg, "BSTW", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abCSCR2_reg, "EXTS", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abCSCR2_reg, "PS", 0, 6, 2, 1, 1);
        ppmCreateRegisterField(abCSCR2_reg, "RDAH", 0, 18, 2, 1, 1);
        ppmCreateRegisterField(abCSCR2_reg, "SWS", 0, 26, 6, 1, 1);
        ppmCreateRegisterField(abCSCR2_reg, "SWSEN", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abCSCR2_reg, "WRAH", 0, 16, 2, 1, 1);
        ppmCreateRegisterField(abCSCR2_reg, "WS", 0, 10, 6, 1, 1);
    }
    {
        registerHandle abCSAR3_reg = ppmCreateRegister(
            "ab_CSAR3",
            "Chip select address register, array offset: 0x0, array step: 0xC ",
            handles.bport1,
            0x24,
            4,
            read_32,
            bport1_ab_CSAR3_maskWrite,
            view32,
            &(bport1_ab_data.CSAR3.value),
            True
        );

        ppmCreateRegisterField(abCSAR3_reg, "BA", 0, 16, 16, 1, 1);
    }
    {
        registerHandle abCSMR3_reg = ppmCreateRegister(
            "ab_CSMR3",
            "Chip select mask register, array offset: 0x4, array step: 0xC ",
            handles.bport1,
            0x28,
            4,
            read_32,
            bport1_ab_CSMR3_maskWrite,
            view32,
            &(bport1_ab_data.CSMR3.value),
            True
        );

        ppmCreateRegisterField(abCSMR3_reg, "BAM", 0, 16, 16, 1, 1);
        ppmCreateRegisterField(abCSMR3_reg, "V", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abCSMR3_reg, "WP", 0, 8, 1, 1, 1);
    }
    {
        registerHandle abCSCR3_reg = ppmCreateRegister(
            "ab_CSCR3",
            "Chip select control register, array offset: 0x8, array step: 0xC ",
            handles.bport1,
            0x2c,
            4,
            read_32,
            bport1_ab_CSCR3_maskWrite,
            view32,
            &(bport1_ab_data.CSCR3.value),
            True
        );

        ppmCreateRegisterField(abCSCR3_reg, "AA", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abCSCR3_reg, "ASET", 0, 20, 2, 1, 1);
        ppmCreateRegisterField(abCSCR3_reg, "BEM", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abCSCR3_reg, "BLS", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abCSCR3_reg, "BSTR", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abCSCR3_reg, "BSTW", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abCSCR3_reg, "EXTS", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abCSCR3_reg, "PS", 0, 6, 2, 1, 1);
        ppmCreateRegisterField(abCSCR3_reg, "RDAH", 0, 18, 2, 1, 1);
        ppmCreateRegisterField(abCSCR3_reg, "SWS", 0, 26, 6, 1, 1);
        ppmCreateRegisterField(abCSCR3_reg, "SWSEN", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abCSCR3_reg, "WRAH", 0, 16, 2, 1, 1);
        ppmCreateRegisterField(abCSCR3_reg, "WS", 0, 10, 6, 1, 1);
    }
    {
        registerHandle abCSAR4_reg = ppmCreateRegister(
            "ab_CSAR4",
            "Chip select address register, array offset: 0x0, array step: 0xC ",
            handles.bport1,
            0x30,
            4,
            read_32,
            bport1_ab_CSAR4_maskWrite,
            view32,
            &(bport1_ab_data.CSAR4.value),
            True
        );

        ppmCreateRegisterField(abCSAR4_reg, "BA", 0, 16, 16, 1, 1);
    }
    {
        registerHandle abCSMR4_reg = ppmCreateRegister(
            "ab_CSMR4",
            "Chip select mask register, array offset: 0x4, array step: 0xC ",
            handles.bport1,
            0x34,
            4,
            read_32,
            bport1_ab_CSMR4_maskWrite,
            view32,
            &(bport1_ab_data.CSMR4.value),
            True
        );

        ppmCreateRegisterField(abCSMR4_reg, "BAM", 0, 16, 16, 1, 1);
        ppmCreateRegisterField(abCSMR4_reg, "V", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abCSMR4_reg, "WP", 0, 8, 1, 1, 1);
    }
    {
        registerHandle abCSCR4_reg = ppmCreateRegister(
            "ab_CSCR4",
            "Chip select control register, array offset: 0x8, array step: 0xC ",
            handles.bport1,
            0x38,
            4,
            read_32,
            bport1_ab_CSCR4_maskWrite,
            view32,
            &(bport1_ab_data.CSCR4.value),
            True
        );

        ppmCreateRegisterField(abCSCR4_reg, "AA", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abCSCR4_reg, "ASET", 0, 20, 2, 1, 1);
        ppmCreateRegisterField(abCSCR4_reg, "BEM", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abCSCR4_reg, "BLS", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abCSCR4_reg, "BSTR", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abCSCR4_reg, "BSTW", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abCSCR4_reg, "EXTS", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abCSCR4_reg, "PS", 0, 6, 2, 1, 1);
        ppmCreateRegisterField(abCSCR4_reg, "RDAH", 0, 18, 2, 1, 1);
        ppmCreateRegisterField(abCSCR4_reg, "SWS", 0, 26, 6, 1, 1);
        ppmCreateRegisterField(abCSCR4_reg, "SWSEN", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abCSCR4_reg, "WRAH", 0, 16, 2, 1, 1);
        ppmCreateRegisterField(abCSCR4_reg, "WS", 0, 10, 6, 1, 1);
    }
    {
        registerHandle abCSAR5_reg = ppmCreateRegister(
            "ab_CSAR5",
            "Chip select address register, array offset: 0x0, array step: 0xC ",
            handles.bport1,
            0x3c,
            4,
            read_32,
            bport1_ab_CSAR5_maskWrite,
            view32,
            &(bport1_ab_data.CSAR5.value),
            True
        );

        ppmCreateRegisterField(abCSAR5_reg, "BA", 0, 16, 16, 1, 1);
    }
    {
        registerHandle abCSMR5_reg = ppmCreateRegister(
            "ab_CSMR5",
            "Chip select mask register, array offset: 0x4, array step: 0xC ",
            handles.bport1,
            0x40,
            4,
            read_32,
            bport1_ab_CSMR5_maskWrite,
            view32,
            &(bport1_ab_data.CSMR5.value),
            True
        );

        ppmCreateRegisterField(abCSMR5_reg, "BAM", 0, 16, 16, 1, 1);
        ppmCreateRegisterField(abCSMR5_reg, "V", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abCSMR5_reg, "WP", 0, 8, 1, 1, 1);
    }
    {
        registerHandle abCSCR5_reg = ppmCreateRegister(
            "ab_CSCR5",
            "Chip select control register, array offset: 0x8, array step: 0xC ",
            handles.bport1,
            0x44,
            4,
            read_32,
            bport1_ab_CSCR5_maskWrite,
            view32,
            &(bport1_ab_data.CSCR5.value),
            True
        );

        ppmCreateRegisterField(abCSCR5_reg, "AA", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abCSCR5_reg, "ASET", 0, 20, 2, 1, 1);
        ppmCreateRegisterField(abCSCR5_reg, "BEM", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abCSCR5_reg, "BLS", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abCSCR5_reg, "BSTR", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abCSCR5_reg, "BSTW", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abCSCR5_reg, "EXTS", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abCSCR5_reg, "PS", 0, 6, 2, 1, 1);
        ppmCreateRegisterField(abCSCR5_reg, "RDAH", 0, 18, 2, 1, 1);
        ppmCreateRegisterField(abCSCR5_reg, "SWS", 0, 26, 6, 1, 1);
        ppmCreateRegisterField(abCSCR5_reg, "SWSEN", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abCSCR5_reg, "WRAH", 0, 16, 2, 1, 1);
        ppmCreateRegisterField(abCSCR5_reg, "WS", 0, 10, 6, 1, 1);
    }
    {
        registerHandle abCSPMCR_reg = ppmCreateRegister(
            "ab_CSPMCR",
            "Chip select port multiplexing control register, offset: 0x60 ",
            handles.bport1,
            0x60,
            4,
            read_32,
            bport1_ab_CSPMCR_maskWrite,
            view32,
            &(bport1_ab_data.CSPMCR.value),
            True
        );

        ppmCreateRegisterField(abCSPMCR_reg, "GROUP1", 0, 28, 4, 1, 1);
        ppmCreateRegisterField(abCSPMCR_reg, "GROUP2", 0, 24, 4, 1, 1);
        ppmCreateRegisterField(abCSPMCR_reg, "GROUP3", 0, 20, 4, 1, 1);
        ppmCreateRegisterField(abCSPMCR_reg, "GROUP4", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abCSPMCR_reg, "GROUP5", 0, 12, 4, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.CSPMCR.value = (Uns32)(bport1_ab_data.CSPMCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CSCR5.value = (Uns32)(bport1_ab_data.CSCR5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CSMR5.value = (Uns32)(bport1_ab_data.CSMR5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CSAR5.value = (Uns32)(bport1_ab_data.CSAR5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CSCR4.value = (Uns32)(bport1_ab_data.CSCR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CSMR4.value = (Uns32)(bport1_ab_data.CSMR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CSAR4.value = (Uns32)(bport1_ab_data.CSAR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CSCR3.value = (Uns32)(bport1_ab_data.CSCR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CSMR3.value = (Uns32)(bport1_ab_data.CSMR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CSAR3.value = (Uns32)(bport1_ab_data.CSAR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CSCR2.value = (Uns32)(bport1_ab_data.CSCR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CSMR2.value = (Uns32)(bport1_ab_data.CSMR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CSAR2.value = (Uns32)(bport1_ab_data.CSAR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CSCR1.value = (Uns32)(bport1_ab_data.CSCR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CSMR1.value = (Uns32)(bport1_ab_data.CSMR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CSAR1.value = (Uns32)(bport1_ab_data.CSAR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CSCR0.value = (Uns32)(bport1_ab_data.CSCR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CSMR0.value = (Uns32)(bport1_ab_data.CSMR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CSAR0.value = (Uns32)(bport1_ab_data.CSAR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the FB peripheral used on the Freescale Kinetis platform");
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


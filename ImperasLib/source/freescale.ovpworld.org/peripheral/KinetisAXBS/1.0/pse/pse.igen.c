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

bport1_ab_dataT bport1_ab_data[8];

bport1_ac_dataT bport1_ac_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisAXBS", "Example");
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

static PPM_NBYTE_WRITE_CB(bport1_ab_CRS_maskWrite) {
    if(bytes != 4 || (offset & (4-1))!=0) {
        bhmMessage("E", "PPM_WNB", "Only aligned 4 byte access permitted");
        return;
    }
    Uns32 block = (offset-0x0)/0x100;
    bport1_ab_data[block].CRS.value = (bport1_ab_data[block].CRS.value & BPORT1_AB_CRS_WRNMASK) | (*(Uns32*)data & BPORT1_AB_CRS_WRMASK);
}

static PPM_NBYTE_WRITE_CB(bport1_ab_PRS_maskWrite) {
    if(bytes != 4 || (offset & (4-1))!=0) {
        bhmMessage("E", "PPM_WNB", "Only aligned 4 byte access permitted");
        return;
    }
    Uns32 block = (offset-0x0)/0x100;
    bport1_ab_data[block].PRS.value = (bport1_ab_data[block].PRS.value & BPORT1_AB_PRS_WRNMASK) | (*(Uns32*)data & BPORT1_AB_PRS_WRMASK);
}

static PPM_WRITE_CB(bport1_ac_MGPCR0_maskWrite) {
    bport1_ac_data.MGPCR0.value = (bport1_ac_data.MGPCR0.value & BPORT1_AC_MGPCR0_WRNMASK) | (data & BPORT1_AC_MGPCR0_WRMASK);
}

static PPM_WRITE_CB(bport1_ac_MGPCR1_maskWrite) {
    bport1_ac_data.MGPCR1.value = (bport1_ac_data.MGPCR1.value & BPORT1_AC_MGPCR1_WRNMASK) | (data & BPORT1_AC_MGPCR1_WRMASK);
}

static PPM_WRITE_CB(bport1_ac_MGPCR2_maskWrite) {
    bport1_ac_data.MGPCR2.value = (bport1_ac_data.MGPCR2.value & BPORT1_AC_MGPCR2_WRNMASK) | (data & BPORT1_AC_MGPCR2_WRMASK);
}

static PPM_WRITE_CB(bport1_ac_MGPCR3_maskWrite) {
    bport1_ac_data.MGPCR3.value = (bport1_ac_data.MGPCR3.value & BPORT1_AC_MGPCR3_WRNMASK) | (data & BPORT1_AC_MGPCR3_WRMASK);
}

static PPM_WRITE_CB(bport1_ac_MGPCR6_maskWrite) {
    bport1_ac_data.MGPCR6.value = (bport1_ac_data.MGPCR6.value & BPORT1_AC_MGPCR6_WRNMASK) | (data & BPORT1_AC_MGPCR6_WRMASK);
}

static PPM_WRITE_CB(bport1_ac_MGPCR7_maskWrite) {
    bport1_ac_data.MGPCR7.value = (bport1_ac_data.MGPCR7.value & BPORT1_AC_MGPCR7_WRNMASK) | (data & BPORT1_AC_MGPCR7_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abPRS_reg = ppmCreateNByteRegister(
            "ab0_PRS",
            0,
            handles.bport1,
            0x0,
            4,
            0,
            bport1_ab_PRS_maskWrite,
            0,
            &(bport1_ab_data[0].PRS.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abPRS_reg, "M0", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M1", 0, 4, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M2", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M3", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M4", 0, 16, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M5", 0, 20, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M6", 0, 24, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M7", 0, 28, 3, 1, 1);
    }
    {
        registerHandle abCRS_reg = ppmCreateNByteRegister(
            "ab0_CRS",
            0,
            handles.bport1,
            0x10,
            4,
            0,
            bport1_ab_CRS_maskWrite,
            0,
            &(bport1_ab_data[0].CRS.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abCRS_reg, "ARB", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "HLP", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "PARK", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "PCTL", 0, 4, 2, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "RO", 0, 31, 1, 1, 1);
    }
    {
        registerHandle abPRS_reg = ppmCreateNByteRegister(
            "ab1_PRS",
            0,
            handles.bport1,
            0x100,
            4,
            0,
            bport1_ab_PRS_maskWrite,
            0,
            &(bport1_ab_data[1].PRS.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abPRS_reg, "M0", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M1", 0, 4, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M2", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M3", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M4", 0, 16, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M5", 0, 20, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M6", 0, 24, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M7", 0, 28, 3, 1, 1);
    }
    {
        registerHandle abCRS_reg = ppmCreateNByteRegister(
            "ab1_CRS",
            0,
            handles.bport1,
            0x110,
            4,
            0,
            bport1_ab_CRS_maskWrite,
            0,
            &(bport1_ab_data[1].CRS.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abCRS_reg, "ARB", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "HLP", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "PARK", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "PCTL", 0, 4, 2, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "RO", 0, 31, 1, 1, 1);
    }
    {
        registerHandle abPRS_reg = ppmCreateNByteRegister(
            "ab2_PRS",
            0,
            handles.bport1,
            0x200,
            4,
            0,
            bport1_ab_PRS_maskWrite,
            0,
            &(bport1_ab_data[2].PRS.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abPRS_reg, "M0", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M1", 0, 4, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M2", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M3", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M4", 0, 16, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M5", 0, 20, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M6", 0, 24, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M7", 0, 28, 3, 1, 1);
    }
    {
        registerHandle abCRS_reg = ppmCreateNByteRegister(
            "ab2_CRS",
            0,
            handles.bport1,
            0x210,
            4,
            0,
            bport1_ab_CRS_maskWrite,
            0,
            &(bport1_ab_data[2].CRS.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abCRS_reg, "ARB", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "HLP", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "PARK", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "PCTL", 0, 4, 2, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "RO", 0, 31, 1, 1, 1);
    }
    {
        registerHandle abPRS_reg = ppmCreateNByteRegister(
            "ab3_PRS",
            0,
            handles.bport1,
            0x300,
            4,
            0,
            bport1_ab_PRS_maskWrite,
            0,
            &(bport1_ab_data[3].PRS.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abPRS_reg, "M0", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M1", 0, 4, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M2", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M3", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M4", 0, 16, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M5", 0, 20, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M6", 0, 24, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M7", 0, 28, 3, 1, 1);
    }
    {
        registerHandle abCRS_reg = ppmCreateNByteRegister(
            "ab3_CRS",
            0,
            handles.bport1,
            0x310,
            4,
            0,
            bport1_ab_CRS_maskWrite,
            0,
            &(bport1_ab_data[3].CRS.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abCRS_reg, "ARB", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "HLP", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "PARK", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "PCTL", 0, 4, 2, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "RO", 0, 31, 1, 1, 1);
    }
    {
        registerHandle abPRS_reg = ppmCreateNByteRegister(
            "ab4_PRS",
            0,
            handles.bport1,
            0x400,
            4,
            0,
            bport1_ab_PRS_maskWrite,
            0,
            &(bport1_ab_data[4].PRS.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abPRS_reg, "M0", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M1", 0, 4, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M2", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M3", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M4", 0, 16, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M5", 0, 20, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M6", 0, 24, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M7", 0, 28, 3, 1, 1);
    }
    {
        registerHandle abCRS_reg = ppmCreateNByteRegister(
            "ab4_CRS",
            0,
            handles.bport1,
            0x410,
            4,
            0,
            bport1_ab_CRS_maskWrite,
            0,
            &(bport1_ab_data[4].CRS.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abCRS_reg, "ARB", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "HLP", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "PARK", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "PCTL", 0, 4, 2, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "RO", 0, 31, 1, 1, 1);
    }
    {
        registerHandle abPRS_reg = ppmCreateNByteRegister(
            "ab5_PRS",
            0,
            handles.bport1,
            0x500,
            4,
            0,
            bport1_ab_PRS_maskWrite,
            0,
            &(bport1_ab_data[5].PRS.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abPRS_reg, "M0", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M1", 0, 4, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M2", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M3", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M4", 0, 16, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M5", 0, 20, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M6", 0, 24, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M7", 0, 28, 3, 1, 1);
    }
    {
        registerHandle abCRS_reg = ppmCreateNByteRegister(
            "ab5_CRS",
            0,
            handles.bport1,
            0x510,
            4,
            0,
            bport1_ab_CRS_maskWrite,
            0,
            &(bport1_ab_data[5].CRS.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abCRS_reg, "ARB", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "HLP", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "PARK", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "PCTL", 0, 4, 2, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "RO", 0, 31, 1, 1, 1);
    }
    {
        registerHandle abPRS_reg = ppmCreateNByteRegister(
            "ab6_PRS",
            0,
            handles.bport1,
            0x600,
            4,
            0,
            bport1_ab_PRS_maskWrite,
            0,
            &(bport1_ab_data[6].PRS.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abPRS_reg, "M0", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M1", 0, 4, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M2", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M3", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M4", 0, 16, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M5", 0, 20, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M6", 0, 24, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M7", 0, 28, 3, 1, 1);
    }
    {
        registerHandle abCRS_reg = ppmCreateNByteRegister(
            "ab6_CRS",
            0,
            handles.bport1,
            0x610,
            4,
            0,
            bport1_ab_CRS_maskWrite,
            0,
            &(bport1_ab_data[6].CRS.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abCRS_reg, "ARB", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "HLP", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "PARK", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "PCTL", 0, 4, 2, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "RO", 0, 31, 1, 1, 1);
    }
    {
        registerHandle abPRS_reg = ppmCreateNByteRegister(
            "ab7_PRS",
            0,
            handles.bport1,
            0x700,
            4,
            0,
            bport1_ab_PRS_maskWrite,
            0,
            &(bport1_ab_data[7].PRS.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abPRS_reg, "M0", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M1", 0, 4, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M2", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M3", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M4", 0, 16, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M5", 0, 20, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M6", 0, 24, 3, 1, 1);
        ppmCreateRegisterField(abPRS_reg, "M7", 0, 28, 3, 1, 1);
    }
    {
        registerHandle abCRS_reg = ppmCreateNByteRegister(
            "ab7_CRS",
            0,
            handles.bport1,
            0x710,
            4,
            0,
            bport1_ab_CRS_maskWrite,
            0,
            &(bport1_ab_data[7].CRS.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abCRS_reg, "ARB", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "HLP", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "PARK", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "PCTL", 0, 4, 2, 1, 1);
        ppmCreateRegisterField(abCRS_reg, "RO", 0, 31, 1, 1, 1);
    }
    {
        registerHandle acMGPCR0_reg = ppmCreateRegister(
            "ac_MGPCR0",
            "Master General Purpose Control Register, offset: 0x800 ",
            handles.bport1,
            0x800,
            4,
            read_32,
            bport1_ac_MGPCR0_maskWrite,
            view32,
            &(bport1_ac_data.MGPCR0.value),
            True
        );

        ppmCreateRegisterField(acMGPCR0_reg, "AULB", 0, 0, 3, 1, 1);
    }
    {
        registerHandle acMGPCR1_reg = ppmCreateRegister(
            "ac_MGPCR1",
            "Master General Purpose Control Register, offset: 0x900 ",
            handles.bport1,
            0x900,
            4,
            read_32,
            bport1_ac_MGPCR1_maskWrite,
            view32,
            &(bport1_ac_data.MGPCR1.value),
            True
        );

        ppmCreateRegisterField(acMGPCR1_reg, "AULB", 0, 0, 3, 1, 1);
    }
    {
        registerHandle acMGPCR2_reg = ppmCreateRegister(
            "ac_MGPCR2",
            "Master General Purpose Control Register, offset: 0xA00 ",
            handles.bport1,
            0xa00,
            4,
            read_32,
            bport1_ac_MGPCR2_maskWrite,
            view32,
            &(bport1_ac_data.MGPCR2.value),
            True
        );

        ppmCreateRegisterField(acMGPCR2_reg, "AULB", 0, 0, 3, 1, 1);
    }
    {
        registerHandle acMGPCR3_reg = ppmCreateRegister(
            "ac_MGPCR3",
            "Master General Purpose Control Register, offset: 0xB00 ",
            handles.bport1,
            0xb00,
            4,
            read_32,
            bport1_ac_MGPCR3_maskWrite,
            view32,
            &(bport1_ac_data.MGPCR3.value),
            True
        );

        ppmCreateRegisterField(acMGPCR3_reg, "AULB", 0, 0, 3, 1, 1);
    }
    {
        registerHandle acMGPCR6_reg = ppmCreateRegister(
            "ac_MGPCR6",
            "Master General Purpose Control Register, offset: 0xE00 ",
            handles.bport1,
            0xe00,
            4,
            read_32,
            bport1_ac_MGPCR6_maskWrite,
            view32,
            &(bport1_ac_data.MGPCR6.value),
            True
        );

        ppmCreateRegisterField(acMGPCR6_reg, "AULB", 0, 0, 3, 1, 1);
    }
    {
        registerHandle acMGPCR7_reg = ppmCreateRegister(
            "ac_MGPCR7",
            "Master General Purpose Control Register, offset: 0xF00 ",
            handles.bport1,
            0xf00,
            4,
            read_32,
            bport1_ac_MGPCR7_maskWrite,
            view32,
            &(bport1_ac_data.MGPCR7.value),
            True
        );

        ppmCreateRegisterField(acMGPCR7_reg, "AULB", 0, 0, 3, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ac_data.MGPCR7.value = (Uns32)(bport1_ac_data.MGPCR7.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ac_data.MGPCR6.value = (Uns32)(bport1_ac_data.MGPCR6.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ac_data.MGPCR3.value = (Uns32)(bport1_ac_data.MGPCR3.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ac_data.MGPCR2.value = (Uns32)(bport1_ac_data.MGPCR2.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ac_data.MGPCR1.value = (Uns32)(bport1_ac_data.MGPCR1.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ac_data.MGPCR0.value = (Uns32)(bport1_ac_data.MGPCR0.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data[0].CRS.value = (Uns32)(bport1_ab_data[0].CRS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000337));
        bport1_ab_data[1].CRS.value = (Uns32)(bport1_ab_data[1].CRS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000337));
        bport1_ab_data[2].CRS.value = (Uns32)(bport1_ab_data[2].CRS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000337));
        bport1_ab_data[3].CRS.value = (Uns32)(bport1_ab_data[3].CRS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000337));
        bport1_ab_data[4].CRS.value = (Uns32)(bport1_ab_data[4].CRS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000337));
        bport1_ab_data[5].CRS.value = (Uns32)(bport1_ab_data[5].CRS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000337));
        bport1_ab_data[6].CRS.value = (Uns32)(bport1_ab_data[6].CRS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000337));
        bport1_ab_data[7].CRS.value = (Uns32)(bport1_ab_data[7].CRS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000337));
        bport1_ab_data[0].PRS.value = (Uns32)(bport1_ab_data[0].PRS.value & ~(0xffffffff)) | ((0xffffffff) & (0x76543210));
        bport1_ab_data[1].PRS.value = (Uns32)(bport1_ab_data[1].PRS.value & ~(0xffffffff)) | ((0xffffffff) & (0x76543210));
        bport1_ab_data[2].PRS.value = (Uns32)(bport1_ab_data[2].PRS.value & ~(0xffffffff)) | ((0xffffffff) & (0x76543210));
        bport1_ab_data[3].PRS.value = (Uns32)(bport1_ab_data[3].PRS.value & ~(0xffffffff)) | ((0xffffffff) & (0x76543210));
        bport1_ab_data[4].PRS.value = (Uns32)(bport1_ab_data[4].PRS.value & ~(0xffffffff)) | ((0xffffffff) & (0x76543210));
        bport1_ab_data[5].PRS.value = (Uns32)(bport1_ab_data[5].PRS.value & ~(0xffffffff)) | ((0xffffffff) & (0x76543210));
        bport1_ab_data[6].PRS.value = (Uns32)(bport1_ab_data[6].PRS.value & ~(0xffffffff)) | ((0xffffffff) & (0x76543210));
        bport1_ab_data[7].PRS.value = (Uns32)(bport1_ab_data[7].PRS.value & ~(0xffffffff)) | ((0xffffffff) & (0x76543210));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the AXBS peripheral used on the Freescale Kinetis platform");
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


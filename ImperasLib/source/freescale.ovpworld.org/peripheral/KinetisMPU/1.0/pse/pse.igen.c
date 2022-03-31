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

bport1_RGD_dataT bport1_RGD_data[16];

bport1_AAC_dataT bport1_AAC_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisMPU", "Example");
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

static PPM_NBYTE_WRITE_CB(bport1_RGD_WORD0_maskWrite) {
    if(bytes != 4 || (offset & (4-1))!=0) {
        bhmMessage("E", "PPM_WNB", "Only aligned 4 byte access permitted");
        return;
    }
    Uns32 block = (offset-0x400)/0x10;
    bport1_RGD_data[block].WORD0.value = (bport1_RGD_data[block].WORD0.value & BPORT1_RGD_WORD0_WRNMASK) | (*(Uns32*)data & BPORT1_RGD_WORD0_WRMASK);
}

static PPM_NBYTE_WRITE_CB(bport1_RGD_WORD1_maskWrite) {
    if(bytes != 4 || (offset & (4-1))!=0) {
        bhmMessage("E", "PPM_WNB", "Only aligned 4 byte access permitted");
        return;
    }
    Uns32 block = (offset-0x400)/0x10;
    bport1_RGD_data[block].WORD1.value = (bport1_RGD_data[block].WORD1.value & BPORT1_RGD_WORD1_WRNMASK) | (*(Uns32*)data & BPORT1_RGD_WORD1_WRMASK);
}

static PPM_NBYTE_WRITE_CB(bport1_RGD_WORD3_maskWrite) {
    if(bytes != 4 || (offset & (4-1))!=0) {
        bhmMessage("E", "PPM_WNB", "Only aligned 4 byte access permitted");
        return;
    }
    Uns32 block = (offset-0x400)/0x10;
    bport1_RGD_data[block].WORD3.value = (bport1_RGD_data[block].WORD3.value & BPORT1_RGD_WORD3_WRNMASK) | (*(Uns32*)data & BPORT1_RGD_WORD3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CESR_maskWrite) {
    bport1_ab_data.CESR.value = (bport1_ab_data.CESR.value & BPORT1_AB_CESR_WRNMASK) | (data & BPORT1_AB_CESR_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abCESR_reg = ppmCreateRegister(
            "ab_CESR",
            0,
            handles.bport1,
            0x0,
            4,
            read_32,
            bport1_ab_CESR_maskWrite,
            view32,
            &(bport1_ab_data.CESR.value),
            True
        );

        ppmCreateRegisterField(abCESR_reg, "VLD", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abCESR_reg, "NRGD", 0, 8, 4, 1, 1);
        ppmCreateRegisterField(abCESR_reg, "NSP", 0, 12, 4, 1, 1);
        ppmCreateRegisterField(abCESR_reg, "HRL", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abCESR_reg, "SPERR", 0, 24, 8, 1, 1);
    }
    {
        registerHandle abEAR0_reg = ppmCreateRegister(
            "ab_EAR0",
            "Error Address Register, Slave Port n, array offset: 0x10, array step: 0x8 ",
            handles.bport1,
            0x10,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.EAR0.value),
            True
        );

        ppmCreateRegisterField(abEAR0_reg, "EADDR", 0, 0, 32, 1, 0);
    }
    {
        registerHandle abEDR0_reg = ppmCreateRegister(
            "ab_EDR0",
            "Error Detail  Register, Slave Port n, array offset: 0x14, array step: 0x8 ",
            handles.bport1,
            0x14,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.EDR0.value),
            True
        );

        ppmCreateRegisterField(abEDR0_reg, "ERW", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(abEDR0_reg, "EATTR", 0, 1, 3, 1, 0);
        ppmCreateRegisterField(abEDR0_reg, "EMN", 0, 4, 4, 1, 0);
        ppmCreateRegisterField(abEDR0_reg, "EPID", 0, 8, 8, 1, 0);
        ppmCreateRegisterField(abEDR0_reg, "EACD", 0, 16, 16, 1, 0);
    }
    {
        registerHandle abEAR1_reg = ppmCreateRegister(
            "ab_EAR1",
            "Error Address Register, Slave Port n, array offset: 0x10, array step: 0x8 ",
            handles.bport1,
            0x18,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.EAR1.value),
            True
        );

        ppmCreateRegisterField(abEAR1_reg, "EADDR", 0, 0, 32, 1, 0);
    }
    {
        registerHandle abEDR1_reg = ppmCreateRegister(
            "ab_EDR1",
            "Error Detail  Register, Slave Port n, array offset: 0x14, array step: 0x8 ",
            handles.bport1,
            0x1c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.EDR1.value),
            True
        );

        ppmCreateRegisterField(abEDR1_reg, "ERW", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(abEDR1_reg, "EATTR", 0, 1, 3, 1, 0);
        ppmCreateRegisterField(abEDR1_reg, "EMN", 0, 4, 4, 1, 0);
        ppmCreateRegisterField(abEDR1_reg, "EPID", 0, 8, 8, 1, 0);
        ppmCreateRegisterField(abEDR1_reg, "EACD", 0, 16, 16, 1, 0);
    }
    {
        registerHandle abEAR2_reg = ppmCreateRegister(
            "ab_EAR2",
            "Error Address Register, Slave Port n, array offset: 0x10, array step: 0x8 ",
            handles.bport1,
            0x20,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.EAR2.value),
            True
        );

        ppmCreateRegisterField(abEAR2_reg, "EADDR", 0, 0, 32, 1, 0);
    }
    {
        registerHandle abEDR2_reg = ppmCreateRegister(
            "ab_EDR2",
            "Error Detail  Register, Slave Port n, array offset: 0x14, array step: 0x8 ",
            handles.bport1,
            0x24,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.EDR2.value),
            True
        );

        ppmCreateRegisterField(abEDR2_reg, "ERW", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(abEDR2_reg, "EATTR", 0, 1, 3, 1, 0);
        ppmCreateRegisterField(abEDR2_reg, "EMN", 0, 4, 4, 1, 0);
        ppmCreateRegisterField(abEDR2_reg, "EPID", 0, 8, 8, 1, 0);
        ppmCreateRegisterField(abEDR2_reg, "EACD", 0, 16, 16, 1, 0);
    }
    {
        registerHandle abEAR3_reg = ppmCreateRegister(
            "ab_EAR3",
            "Error Address Register, Slave Port n, array offset: 0x10, array step: 0x8 ",
            handles.bport1,
            0x28,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.EAR3.value),
            True
        );

        ppmCreateRegisterField(abEAR3_reg, "EADDR", 0, 0, 32, 1, 0);
    }
    {
        registerHandle abEDR3_reg = ppmCreateRegister(
            "ab_EDR3",
            "Error Detail  Register, Slave Port n, array offset: 0x14, array step: 0x8 ",
            handles.bport1,
            0x2c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.EDR3.value),
            True
        );

        ppmCreateRegisterField(abEDR3_reg, "ERW", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(abEDR3_reg, "EATTR", 0, 1, 3, 1, 0);
        ppmCreateRegisterField(abEDR3_reg, "EMN", 0, 4, 4, 1, 0);
        ppmCreateRegisterField(abEDR3_reg, "EPID", 0, 8, 8, 1, 0);
        ppmCreateRegisterField(abEDR3_reg, "EACD", 0, 16, 16, 1, 0);
    }
    {
        registerHandle abEAR4_reg = ppmCreateRegister(
            "ab_EAR4",
            "Error Address Register, Slave Port n, array offset: 0x10, array step: 0x8 ",
            handles.bport1,
            0x30,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.EAR4.value),
            True
        );

        ppmCreateRegisterField(abEAR4_reg, "EADDR", 0, 0, 32, 1, 0);
    }
    {
        registerHandle abEDR4_reg = ppmCreateRegister(
            "ab_EDR4",
            "Error Detail  Register, Slave Port n, array offset: 0x14, array step: 0x8 ",
            handles.bport1,
            0x34,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.EDR4.value),
            True
        );

        ppmCreateRegisterField(abEDR4_reg, "ERW", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(abEDR4_reg, "EATTR", 0, 1, 3, 1, 0);
        ppmCreateRegisterField(abEDR4_reg, "EMN", 0, 4, 4, 1, 0);
        ppmCreateRegisterField(abEDR4_reg, "EPID", 0, 8, 8, 1, 0);
        ppmCreateRegisterField(abEDR4_reg, "EACD", 0, 16, 16, 1, 0);
    }
    {
        registerHandle RGDWORD0_reg = ppmCreateNByteRegister(
            "RGD0_WORD0",
            "Region Descriptor",
            handles.bport1,
            0x400,
            4,
            0,
            bport1_RGD_WORD0_maskWrite,
            0,
            &(bport1_RGD_data[0].WORD0.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD0_reg, "SRTADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD1_reg = ppmCreateNByteRegister(
            "RGD0_WORD1",
            "Region Descriptor",
            handles.bport1,
            0x404,
            4,
            0,
            bport1_RGD_WORD1_maskWrite,
            0,
            &(bport1_RGD_data[0].WORD1.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD1_reg, "ENDADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD2_reg = ppmCreateNByteRegister(
            "RGD0_WORD2",
            "Region Descriptor",
            handles.bport1,
            0x408,
            4,
            0,
            0,
            0,
            &(bport1_RGD_data[0].WORD2.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD2_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle RGDWORD3_reg = ppmCreateNByteRegister(
            "RGD0_WORD3",
            "Region Descriptor",
            handles.bport1,
            0x40c,
            4,
            0,
            bport1_RGD_WORD3_maskWrite,
            0,
            &(bport1_RGD_data[0].WORD3.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD3_reg, "PID", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "PIDMASK", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "VLD", 0, 0, 1, 1, 1);
    }
    {
        registerHandle RGDWORD0_reg = ppmCreateNByteRegister(
            "RGD1_WORD0",
            "Region Descriptor",
            handles.bport1,
            0x410,
            4,
            0,
            bport1_RGD_WORD0_maskWrite,
            0,
            &(bport1_RGD_data[1].WORD0.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD0_reg, "SRTADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD1_reg = ppmCreateNByteRegister(
            "RGD1_WORD1",
            "Region Descriptor",
            handles.bport1,
            0x414,
            4,
            0,
            bport1_RGD_WORD1_maskWrite,
            0,
            &(bport1_RGD_data[1].WORD1.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD1_reg, "ENDADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD2_reg = ppmCreateNByteRegister(
            "RGD1_WORD2",
            "Region Descriptor",
            handles.bport1,
            0x418,
            4,
            0,
            0,
            0,
            &(bport1_RGD_data[1].WORD2.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD2_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle RGDWORD3_reg = ppmCreateNByteRegister(
            "RGD1_WORD3",
            "Region Descriptor",
            handles.bport1,
            0x41c,
            4,
            0,
            bport1_RGD_WORD3_maskWrite,
            0,
            &(bport1_RGD_data[1].WORD3.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD3_reg, "PID", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "PIDMASK", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "VLD", 0, 0, 1, 1, 1);
    }
    {
        registerHandle RGDWORD0_reg = ppmCreateNByteRegister(
            "RGD2_WORD0",
            "Region Descriptor",
            handles.bport1,
            0x420,
            4,
            0,
            bport1_RGD_WORD0_maskWrite,
            0,
            &(bport1_RGD_data[2].WORD0.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD0_reg, "SRTADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD1_reg = ppmCreateNByteRegister(
            "RGD2_WORD1",
            "Region Descriptor",
            handles.bport1,
            0x424,
            4,
            0,
            bport1_RGD_WORD1_maskWrite,
            0,
            &(bport1_RGD_data[2].WORD1.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD1_reg, "ENDADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD2_reg = ppmCreateNByteRegister(
            "RGD2_WORD2",
            "Region Descriptor",
            handles.bport1,
            0x428,
            4,
            0,
            0,
            0,
            &(bport1_RGD_data[2].WORD2.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD2_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle RGDWORD3_reg = ppmCreateNByteRegister(
            "RGD2_WORD3",
            "Region Descriptor",
            handles.bport1,
            0x42c,
            4,
            0,
            bport1_RGD_WORD3_maskWrite,
            0,
            &(bport1_RGD_data[2].WORD3.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD3_reg, "PID", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "PIDMASK", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "VLD", 0, 0, 1, 1, 1);
    }
    {
        registerHandle RGDWORD0_reg = ppmCreateNByteRegister(
            "RGD3_WORD0",
            "Region Descriptor",
            handles.bport1,
            0x430,
            4,
            0,
            bport1_RGD_WORD0_maskWrite,
            0,
            &(bport1_RGD_data[3].WORD0.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD0_reg, "SRTADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD1_reg = ppmCreateNByteRegister(
            "RGD3_WORD1",
            "Region Descriptor",
            handles.bport1,
            0x434,
            4,
            0,
            bport1_RGD_WORD1_maskWrite,
            0,
            &(bport1_RGD_data[3].WORD1.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD1_reg, "ENDADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD2_reg = ppmCreateNByteRegister(
            "RGD3_WORD2",
            "Region Descriptor",
            handles.bport1,
            0x438,
            4,
            0,
            0,
            0,
            &(bport1_RGD_data[3].WORD2.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD2_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle RGDWORD3_reg = ppmCreateNByteRegister(
            "RGD3_WORD3",
            "Region Descriptor",
            handles.bport1,
            0x43c,
            4,
            0,
            bport1_RGD_WORD3_maskWrite,
            0,
            &(bport1_RGD_data[3].WORD3.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD3_reg, "PID", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "PIDMASK", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "VLD", 0, 0, 1, 1, 1);
    }
    {
        registerHandle RGDWORD0_reg = ppmCreateNByteRegister(
            "RGD4_WORD0",
            "Region Descriptor",
            handles.bport1,
            0x440,
            4,
            0,
            bport1_RGD_WORD0_maskWrite,
            0,
            &(bport1_RGD_data[4].WORD0.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD0_reg, "SRTADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD1_reg = ppmCreateNByteRegister(
            "RGD4_WORD1",
            "Region Descriptor",
            handles.bport1,
            0x444,
            4,
            0,
            bport1_RGD_WORD1_maskWrite,
            0,
            &(bport1_RGD_data[4].WORD1.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD1_reg, "ENDADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD2_reg = ppmCreateNByteRegister(
            "RGD4_WORD2",
            "Region Descriptor",
            handles.bport1,
            0x448,
            4,
            0,
            0,
            0,
            &(bport1_RGD_data[4].WORD2.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD2_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle RGDWORD3_reg = ppmCreateNByteRegister(
            "RGD4_WORD3",
            "Region Descriptor",
            handles.bport1,
            0x44c,
            4,
            0,
            bport1_RGD_WORD3_maskWrite,
            0,
            &(bport1_RGD_data[4].WORD3.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD3_reg, "PID", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "PIDMASK", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "VLD", 0, 0, 1, 1, 1);
    }
    {
        registerHandle RGDWORD0_reg = ppmCreateNByteRegister(
            "RGD5_WORD0",
            "Region Descriptor",
            handles.bport1,
            0x450,
            4,
            0,
            bport1_RGD_WORD0_maskWrite,
            0,
            &(bport1_RGD_data[5].WORD0.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD0_reg, "SRTADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD1_reg = ppmCreateNByteRegister(
            "RGD5_WORD1",
            "Region Descriptor",
            handles.bport1,
            0x454,
            4,
            0,
            bport1_RGD_WORD1_maskWrite,
            0,
            &(bport1_RGD_data[5].WORD1.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD1_reg, "ENDADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD2_reg = ppmCreateNByteRegister(
            "RGD5_WORD2",
            "Region Descriptor",
            handles.bport1,
            0x458,
            4,
            0,
            0,
            0,
            &(bport1_RGD_data[5].WORD2.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD2_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle RGDWORD3_reg = ppmCreateNByteRegister(
            "RGD5_WORD3",
            "Region Descriptor",
            handles.bport1,
            0x45c,
            4,
            0,
            bport1_RGD_WORD3_maskWrite,
            0,
            &(bport1_RGD_data[5].WORD3.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD3_reg, "PID", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "PIDMASK", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "VLD", 0, 0, 1, 1, 1);
    }
    {
        registerHandle RGDWORD0_reg = ppmCreateNByteRegister(
            "RGD6_WORD0",
            "Region Descriptor",
            handles.bport1,
            0x460,
            4,
            0,
            bport1_RGD_WORD0_maskWrite,
            0,
            &(bport1_RGD_data[6].WORD0.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD0_reg, "SRTADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD1_reg = ppmCreateNByteRegister(
            "RGD6_WORD1",
            "Region Descriptor",
            handles.bport1,
            0x464,
            4,
            0,
            bport1_RGD_WORD1_maskWrite,
            0,
            &(bport1_RGD_data[6].WORD1.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD1_reg, "ENDADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD2_reg = ppmCreateNByteRegister(
            "RGD6_WORD2",
            "Region Descriptor",
            handles.bport1,
            0x468,
            4,
            0,
            0,
            0,
            &(bport1_RGD_data[6].WORD2.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD2_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle RGDWORD3_reg = ppmCreateNByteRegister(
            "RGD6_WORD3",
            "Region Descriptor",
            handles.bport1,
            0x46c,
            4,
            0,
            bport1_RGD_WORD3_maskWrite,
            0,
            &(bport1_RGD_data[6].WORD3.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD3_reg, "PID", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "PIDMASK", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "VLD", 0, 0, 1, 1, 1);
    }
    {
        registerHandle RGDWORD0_reg = ppmCreateNByteRegister(
            "RGD7_WORD0",
            "Region Descriptor",
            handles.bport1,
            0x470,
            4,
            0,
            bport1_RGD_WORD0_maskWrite,
            0,
            &(bport1_RGD_data[7].WORD0.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD0_reg, "SRTADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD1_reg = ppmCreateNByteRegister(
            "RGD7_WORD1",
            "Region Descriptor",
            handles.bport1,
            0x474,
            4,
            0,
            bport1_RGD_WORD1_maskWrite,
            0,
            &(bport1_RGD_data[7].WORD1.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD1_reg, "ENDADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD2_reg = ppmCreateNByteRegister(
            "RGD7_WORD2",
            "Region Descriptor",
            handles.bport1,
            0x478,
            4,
            0,
            0,
            0,
            &(bport1_RGD_data[7].WORD2.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD2_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle RGDWORD3_reg = ppmCreateNByteRegister(
            "RGD7_WORD3",
            "Region Descriptor",
            handles.bport1,
            0x47c,
            4,
            0,
            bport1_RGD_WORD3_maskWrite,
            0,
            &(bport1_RGD_data[7].WORD3.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD3_reg, "PID", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "PIDMASK", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "VLD", 0, 0, 1, 1, 1);
    }
    {
        registerHandle RGDWORD0_reg = ppmCreateNByteRegister(
            "RGD8_WORD0",
            "Region Descriptor",
            handles.bport1,
            0x480,
            4,
            0,
            bport1_RGD_WORD0_maskWrite,
            0,
            &(bport1_RGD_data[8].WORD0.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD0_reg, "SRTADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD1_reg = ppmCreateNByteRegister(
            "RGD8_WORD1",
            "Region Descriptor",
            handles.bport1,
            0x484,
            4,
            0,
            bport1_RGD_WORD1_maskWrite,
            0,
            &(bport1_RGD_data[8].WORD1.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD1_reg, "ENDADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD2_reg = ppmCreateNByteRegister(
            "RGD8_WORD2",
            "Region Descriptor",
            handles.bport1,
            0x488,
            4,
            0,
            0,
            0,
            &(bport1_RGD_data[8].WORD2.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD2_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle RGDWORD3_reg = ppmCreateNByteRegister(
            "RGD8_WORD3",
            "Region Descriptor",
            handles.bport1,
            0x48c,
            4,
            0,
            bport1_RGD_WORD3_maskWrite,
            0,
            &(bport1_RGD_data[8].WORD3.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD3_reg, "PID", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "PIDMASK", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "VLD", 0, 0, 1, 1, 1);
    }
    {
        registerHandle RGDWORD0_reg = ppmCreateNByteRegister(
            "RGD9_WORD0",
            "Region Descriptor",
            handles.bport1,
            0x490,
            4,
            0,
            bport1_RGD_WORD0_maskWrite,
            0,
            &(bport1_RGD_data[9].WORD0.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD0_reg, "SRTADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD1_reg = ppmCreateNByteRegister(
            "RGD9_WORD1",
            "Region Descriptor",
            handles.bport1,
            0x494,
            4,
            0,
            bport1_RGD_WORD1_maskWrite,
            0,
            &(bport1_RGD_data[9].WORD1.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD1_reg, "ENDADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD2_reg = ppmCreateNByteRegister(
            "RGD9_WORD2",
            "Region Descriptor",
            handles.bport1,
            0x498,
            4,
            0,
            0,
            0,
            &(bport1_RGD_data[9].WORD2.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD2_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle RGDWORD3_reg = ppmCreateNByteRegister(
            "RGD9_WORD3",
            "Region Descriptor",
            handles.bport1,
            0x49c,
            4,
            0,
            bport1_RGD_WORD3_maskWrite,
            0,
            &(bport1_RGD_data[9].WORD3.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD3_reg, "PID", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "PIDMASK", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "VLD", 0, 0, 1, 1, 1);
    }
    {
        registerHandle RGDWORD0_reg = ppmCreateNByteRegister(
            "RGD10_WORD0",
            "Region Descriptor",
            handles.bport1,
            0x4a0,
            4,
            0,
            bport1_RGD_WORD0_maskWrite,
            0,
            &(bport1_RGD_data[10].WORD0.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD0_reg, "SRTADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD1_reg = ppmCreateNByteRegister(
            "RGD10_WORD1",
            "Region Descriptor",
            handles.bport1,
            0x4a4,
            4,
            0,
            bport1_RGD_WORD1_maskWrite,
            0,
            &(bport1_RGD_data[10].WORD1.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD1_reg, "ENDADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD2_reg = ppmCreateNByteRegister(
            "RGD10_WORD2",
            "Region Descriptor",
            handles.bport1,
            0x4a8,
            4,
            0,
            0,
            0,
            &(bport1_RGD_data[10].WORD2.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD2_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle RGDWORD3_reg = ppmCreateNByteRegister(
            "RGD10_WORD3",
            "Region Descriptor",
            handles.bport1,
            0x4ac,
            4,
            0,
            bport1_RGD_WORD3_maskWrite,
            0,
            &(bport1_RGD_data[10].WORD3.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD3_reg, "PID", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "PIDMASK", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "VLD", 0, 0, 1, 1, 1);
    }
    {
        registerHandle RGDWORD0_reg = ppmCreateNByteRegister(
            "RGD11_WORD0",
            "Region Descriptor",
            handles.bport1,
            0x4b0,
            4,
            0,
            bport1_RGD_WORD0_maskWrite,
            0,
            &(bport1_RGD_data[11].WORD0.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD0_reg, "SRTADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD1_reg = ppmCreateNByteRegister(
            "RGD11_WORD1",
            "Region Descriptor",
            handles.bport1,
            0x4b4,
            4,
            0,
            bport1_RGD_WORD1_maskWrite,
            0,
            &(bport1_RGD_data[11].WORD1.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD1_reg, "ENDADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD2_reg = ppmCreateNByteRegister(
            "RGD11_WORD2",
            "Region Descriptor",
            handles.bport1,
            0x4b8,
            4,
            0,
            0,
            0,
            &(bport1_RGD_data[11].WORD2.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD2_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle RGDWORD3_reg = ppmCreateNByteRegister(
            "RGD11_WORD3",
            "Region Descriptor",
            handles.bport1,
            0x4bc,
            4,
            0,
            bport1_RGD_WORD3_maskWrite,
            0,
            &(bport1_RGD_data[11].WORD3.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD3_reg, "PID", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "PIDMASK", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "VLD", 0, 0, 1, 1, 1);
    }
    {
        registerHandle RGDWORD0_reg = ppmCreateNByteRegister(
            "RGD12_WORD0",
            "Region Descriptor",
            handles.bport1,
            0x4c0,
            4,
            0,
            bport1_RGD_WORD0_maskWrite,
            0,
            &(bport1_RGD_data[12].WORD0.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD0_reg, "SRTADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD1_reg = ppmCreateNByteRegister(
            "RGD12_WORD1",
            "Region Descriptor",
            handles.bport1,
            0x4c4,
            4,
            0,
            bport1_RGD_WORD1_maskWrite,
            0,
            &(bport1_RGD_data[12].WORD1.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD1_reg, "ENDADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD2_reg = ppmCreateNByteRegister(
            "RGD12_WORD2",
            "Region Descriptor",
            handles.bport1,
            0x4c8,
            4,
            0,
            0,
            0,
            &(bport1_RGD_data[12].WORD2.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD2_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle RGDWORD3_reg = ppmCreateNByteRegister(
            "RGD12_WORD3",
            "Region Descriptor",
            handles.bport1,
            0x4cc,
            4,
            0,
            bport1_RGD_WORD3_maskWrite,
            0,
            &(bport1_RGD_data[12].WORD3.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD3_reg, "PID", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "PIDMASK", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "VLD", 0, 0, 1, 1, 1);
    }
    {
        registerHandle RGDWORD0_reg = ppmCreateNByteRegister(
            "RGD13_WORD0",
            "Region Descriptor",
            handles.bport1,
            0x4d0,
            4,
            0,
            bport1_RGD_WORD0_maskWrite,
            0,
            &(bport1_RGD_data[13].WORD0.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD0_reg, "SRTADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD1_reg = ppmCreateNByteRegister(
            "RGD13_WORD1",
            "Region Descriptor",
            handles.bport1,
            0x4d4,
            4,
            0,
            bport1_RGD_WORD1_maskWrite,
            0,
            &(bport1_RGD_data[13].WORD1.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD1_reg, "ENDADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD2_reg = ppmCreateNByteRegister(
            "RGD13_WORD2",
            "Region Descriptor",
            handles.bport1,
            0x4d8,
            4,
            0,
            0,
            0,
            &(bport1_RGD_data[13].WORD2.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD2_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle RGDWORD3_reg = ppmCreateNByteRegister(
            "RGD13_WORD3",
            "Region Descriptor",
            handles.bport1,
            0x4dc,
            4,
            0,
            bport1_RGD_WORD3_maskWrite,
            0,
            &(bport1_RGD_data[13].WORD3.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD3_reg, "PID", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "PIDMASK", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "VLD", 0, 0, 1, 1, 1);
    }
    {
        registerHandle RGDWORD0_reg = ppmCreateNByteRegister(
            "RGD14_WORD0",
            "Region Descriptor",
            handles.bport1,
            0x4e0,
            4,
            0,
            bport1_RGD_WORD0_maskWrite,
            0,
            &(bport1_RGD_data[14].WORD0.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD0_reg, "SRTADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD1_reg = ppmCreateNByteRegister(
            "RGD14_WORD1",
            "Region Descriptor",
            handles.bport1,
            0x4e4,
            4,
            0,
            bport1_RGD_WORD1_maskWrite,
            0,
            &(bport1_RGD_data[14].WORD1.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD1_reg, "ENDADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD2_reg = ppmCreateNByteRegister(
            "RGD14_WORD2",
            "Region Descriptor",
            handles.bport1,
            0x4e8,
            4,
            0,
            0,
            0,
            &(bport1_RGD_data[14].WORD2.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD2_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle RGDWORD3_reg = ppmCreateNByteRegister(
            "RGD14_WORD3",
            "Region Descriptor",
            handles.bport1,
            0x4ec,
            4,
            0,
            bport1_RGD_WORD3_maskWrite,
            0,
            &(bport1_RGD_data[14].WORD3.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD3_reg, "PID", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "PIDMASK", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "VLD", 0, 0, 1, 1, 1);
    }
    {
        registerHandle RGDWORD0_reg = ppmCreateNByteRegister(
            "RGD15_WORD0",
            "Region Descriptor",
            handles.bport1,
            0x4f0,
            4,
            0,
            bport1_RGD_WORD0_maskWrite,
            0,
            &(bport1_RGD_data[15].WORD0.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD0_reg, "SRTADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD1_reg = ppmCreateNByteRegister(
            "RGD15_WORD1",
            "Region Descriptor",
            handles.bport1,
            0x4f4,
            4,
            0,
            bport1_RGD_WORD1_maskWrite,
            0,
            &(bport1_RGD_data[15].WORD1.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD1_reg, "ENDADDR", 0, 5, 27, 1, 1);
    }
    {
        registerHandle RGDWORD2_reg = ppmCreateNByteRegister(
            "RGD15_WORD2",
            "Region Descriptor",
            handles.bport1,
            0x4f8,
            4,
            0,
            0,
            0,
            &(bport1_RGD_data[15].WORD2.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD2_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(RGDWORD2_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle RGDWORD3_reg = ppmCreateNByteRegister(
            "RGD15_WORD3",
            "Region Descriptor",
            handles.bport1,
            0x4fc,
            4,
            0,
            bport1_RGD_WORD3_maskWrite,
            0,
            &(bport1_RGD_data[15].WORD3.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(RGDWORD3_reg, "PID", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "PIDMASK", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(RGDWORD3_reg, "VLD", 0, 0, 1, 1, 1);
    }
    {
        registerHandle AACRGDAAC_reg = ppmCreateNByteRegister(
            "AAC_RGDAAC0",
            "Region Descriptor Alternate Access Control",
            handles.bport1,
            0xbc0,
            4,
            0,
            0,
            0,
            &(bport1_AAC_data.RGDAAC[0].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(AACRGDAAC_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle AACRGDAAC_reg = ppmCreateNByteRegister(
            "AAC_RGDAAC1",
            "Region Descriptor Alternate Access Control",
            handles.bport1,
            0xbc4,
            4,
            0,
            0,
            0,
            &(bport1_AAC_data.RGDAAC[1].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(AACRGDAAC_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle AACRGDAAC_reg = ppmCreateNByteRegister(
            "AAC_RGDAAC2",
            "Region Descriptor Alternate Access Control",
            handles.bport1,
            0xbc8,
            4,
            0,
            0,
            0,
            &(bport1_AAC_data.RGDAAC[2].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(AACRGDAAC_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle AACRGDAAC_reg = ppmCreateNByteRegister(
            "AAC_RGDAAC3",
            "Region Descriptor Alternate Access Control",
            handles.bport1,
            0xbcc,
            4,
            0,
            0,
            0,
            &(bport1_AAC_data.RGDAAC[3].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(AACRGDAAC_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle AACRGDAAC_reg = ppmCreateNByteRegister(
            "AAC_RGDAAC4",
            "Region Descriptor Alternate Access Control",
            handles.bport1,
            0xbd0,
            4,
            0,
            0,
            0,
            &(bport1_AAC_data.RGDAAC[4].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(AACRGDAAC_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle AACRGDAAC_reg = ppmCreateNByteRegister(
            "AAC_RGDAAC5",
            "Region Descriptor Alternate Access Control",
            handles.bport1,
            0xbd4,
            4,
            0,
            0,
            0,
            &(bport1_AAC_data.RGDAAC[5].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(AACRGDAAC_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle AACRGDAAC_reg = ppmCreateNByteRegister(
            "AAC_RGDAAC6",
            "Region Descriptor Alternate Access Control",
            handles.bport1,
            0xbd8,
            4,
            0,
            0,
            0,
            &(bport1_AAC_data.RGDAAC[6].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(AACRGDAAC_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle AACRGDAAC_reg = ppmCreateNByteRegister(
            "AAC_RGDAAC7",
            "Region Descriptor Alternate Access Control",
            handles.bport1,
            0xbdc,
            4,
            0,
            0,
            0,
            &(bport1_AAC_data.RGDAAC[7].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(AACRGDAAC_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle AACRGDAAC_reg = ppmCreateNByteRegister(
            "AAC_RGDAAC8",
            "Region Descriptor Alternate Access Control",
            handles.bport1,
            0xbe0,
            4,
            0,
            0,
            0,
            &(bport1_AAC_data.RGDAAC[8].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(AACRGDAAC_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle AACRGDAAC_reg = ppmCreateNByteRegister(
            "AAC_RGDAAC9",
            "Region Descriptor Alternate Access Control",
            handles.bport1,
            0xbe4,
            4,
            0,
            0,
            0,
            &(bport1_AAC_data.RGDAAC[9].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(AACRGDAAC_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle AACRGDAAC_reg = ppmCreateNByteRegister(
            "AAC_RGDAAC10",
            "Region Descriptor Alternate Access Control",
            handles.bport1,
            0xbe8,
            4,
            0,
            0,
            0,
            &(bport1_AAC_data.RGDAAC[10].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(AACRGDAAC_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle AACRGDAAC_reg = ppmCreateNByteRegister(
            "AAC_RGDAAC11",
            "Region Descriptor Alternate Access Control",
            handles.bport1,
            0xbec,
            4,
            0,
            0,
            0,
            &(bport1_AAC_data.RGDAAC[11].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(AACRGDAAC_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle AACRGDAAC_reg = ppmCreateNByteRegister(
            "AAC_RGDAAC12",
            "Region Descriptor Alternate Access Control",
            handles.bport1,
            0xbf0,
            4,
            0,
            0,
            0,
            &(bport1_AAC_data.RGDAAC[12].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(AACRGDAAC_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle AACRGDAAC_reg = ppmCreateNByteRegister(
            "AAC_RGDAAC13",
            "Region Descriptor Alternate Access Control",
            handles.bport1,
            0xbf4,
            4,
            0,
            0,
            0,
            &(bport1_AAC_data.RGDAAC[13].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(AACRGDAAC_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle AACRGDAAC_reg = ppmCreateNByteRegister(
            "AAC_RGDAAC14",
            "Region Descriptor Alternate Access Control",
            handles.bport1,
            0xbf8,
            4,
            0,
            0,
            0,
            &(bport1_AAC_data.RGDAAC[14].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(AACRGDAAC_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7RE", 0, 31, 1, 1, 1);
    }
    {
        registerHandle AACRGDAAC_reg = ppmCreateNByteRegister(
            "AAC_RGDAAC15",
            "Region Descriptor Alternate Access Control",
            handles.bport1,
            0xbfc,
            4,
            0,
            0,
            0,
            &(bport1_AAC_data.RGDAAC[15].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(AACRGDAAC_reg, "M0UM", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0SM", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M0PE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1UM", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1SM", 0, 9, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M1PE", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2UM", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2SM", 0, 15, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M2PE", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3UM", 0, 18, 3, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3SM", 0, 21, 2, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M3PE", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4WE", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M4RE", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5WE", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M5RE", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6WE", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M6RE", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7WE", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(AACRGDAAC_reg, "M7RE", 0, 31, 1, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_RGD_data[0].WORD3.value = (Uns32)(bport1_RGD_data[0].WORD3.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[1].WORD3.value = (Uns32)(bport1_RGD_data[1].WORD3.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[2].WORD3.value = (Uns32)(bport1_RGD_data[2].WORD3.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[3].WORD3.value = (Uns32)(bport1_RGD_data[3].WORD3.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[4].WORD3.value = (Uns32)(bport1_RGD_data[4].WORD3.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[5].WORD3.value = (Uns32)(bport1_RGD_data[5].WORD3.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[6].WORD3.value = (Uns32)(bport1_RGD_data[6].WORD3.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[7].WORD3.value = (Uns32)(bport1_RGD_data[7].WORD3.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[8].WORD3.value = (Uns32)(bport1_RGD_data[8].WORD3.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[9].WORD3.value = (Uns32)(bport1_RGD_data[9].WORD3.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[10].WORD3.value = (Uns32)(bport1_RGD_data[10].WORD3.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[11].WORD3.value = (Uns32)(bport1_RGD_data[11].WORD3.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[12].WORD3.value = (Uns32)(bport1_RGD_data[12].WORD3.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[13].WORD3.value = (Uns32)(bport1_RGD_data[13].WORD3.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[14].WORD3.value = (Uns32)(bport1_RGD_data[14].WORD3.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[15].WORD3.value = (Uns32)(bport1_RGD_data[15].WORD3.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[0].WORD2.value = (Uns32)(bport1_RGD_data[0].WORD2.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[1].WORD2.value = (Uns32)(bport1_RGD_data[1].WORD2.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[2].WORD2.value = (Uns32)(bport1_RGD_data[2].WORD2.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[3].WORD2.value = (Uns32)(bport1_RGD_data[3].WORD2.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[4].WORD2.value = (Uns32)(bport1_RGD_data[4].WORD2.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[5].WORD2.value = (Uns32)(bport1_RGD_data[5].WORD2.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[6].WORD2.value = (Uns32)(bport1_RGD_data[6].WORD2.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[7].WORD2.value = (Uns32)(bport1_RGD_data[7].WORD2.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[8].WORD2.value = (Uns32)(bport1_RGD_data[8].WORD2.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[9].WORD2.value = (Uns32)(bport1_RGD_data[9].WORD2.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[10].WORD2.value = (Uns32)(bport1_RGD_data[10].WORD2.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[11].WORD2.value = (Uns32)(bport1_RGD_data[11].WORD2.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[12].WORD2.value = (Uns32)(bport1_RGD_data[12].WORD2.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[13].WORD2.value = (Uns32)(bport1_RGD_data[13].WORD2.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[14].WORD2.value = (Uns32)(bport1_RGD_data[14].WORD2.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[15].WORD2.value = (Uns32)(bport1_RGD_data[15].WORD2.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[0].WORD1.value = (Uns32)(bport1_RGD_data[0].WORD1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000001f));
        bport1_RGD_data[1].WORD1.value = (Uns32)(bport1_RGD_data[1].WORD1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000001f));
        bport1_RGD_data[2].WORD1.value = (Uns32)(bport1_RGD_data[2].WORD1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000001f));
        bport1_RGD_data[3].WORD1.value = (Uns32)(bport1_RGD_data[3].WORD1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000001f));
        bport1_RGD_data[4].WORD1.value = (Uns32)(bport1_RGD_data[4].WORD1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000001f));
        bport1_RGD_data[5].WORD1.value = (Uns32)(bport1_RGD_data[5].WORD1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000001f));
        bport1_RGD_data[6].WORD1.value = (Uns32)(bport1_RGD_data[6].WORD1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000001f));
        bport1_RGD_data[7].WORD1.value = (Uns32)(bport1_RGD_data[7].WORD1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000001f));
        bport1_RGD_data[8].WORD1.value = (Uns32)(bport1_RGD_data[8].WORD1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000001f));
        bport1_RGD_data[9].WORD1.value = (Uns32)(bport1_RGD_data[9].WORD1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000001f));
        bport1_RGD_data[10].WORD1.value = (Uns32)(bport1_RGD_data[10].WORD1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000001f));
        bport1_RGD_data[11].WORD1.value = (Uns32)(bport1_RGD_data[11].WORD1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000001f));
        bport1_RGD_data[12].WORD1.value = (Uns32)(bport1_RGD_data[12].WORD1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000001f));
        bport1_RGD_data[13].WORD1.value = (Uns32)(bport1_RGD_data[13].WORD1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000001f));
        bport1_RGD_data[14].WORD1.value = (Uns32)(bport1_RGD_data[14].WORD1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000001f));
        bport1_RGD_data[15].WORD1.value = (Uns32)(bport1_RGD_data[15].WORD1.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000001f));
        bport1_RGD_data[0].WORD0.value = (Uns32)(bport1_RGD_data[0].WORD0.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[1].WORD0.value = (Uns32)(bport1_RGD_data[1].WORD0.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[2].WORD0.value = (Uns32)(bport1_RGD_data[2].WORD0.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[3].WORD0.value = (Uns32)(bport1_RGD_data[3].WORD0.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[4].WORD0.value = (Uns32)(bport1_RGD_data[4].WORD0.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[5].WORD0.value = (Uns32)(bport1_RGD_data[5].WORD0.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[6].WORD0.value = (Uns32)(bport1_RGD_data[6].WORD0.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[7].WORD0.value = (Uns32)(bport1_RGD_data[7].WORD0.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[8].WORD0.value = (Uns32)(bport1_RGD_data[8].WORD0.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[9].WORD0.value = (Uns32)(bport1_RGD_data[9].WORD0.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[10].WORD0.value = (Uns32)(bport1_RGD_data[10].WORD0.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[11].WORD0.value = (Uns32)(bport1_RGD_data[11].WORD0.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[12].WORD0.value = (Uns32)(bport1_RGD_data[12].WORD0.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[13].WORD0.value = (Uns32)(bport1_RGD_data[13].WORD0.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[14].WORD0.value = (Uns32)(bport1_RGD_data[14].WORD0.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_RGD_data[15].WORD0.value = (Uns32)(bport1_RGD_data[15].WORD0.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CESR.value = (Uns32)(bport1_ab_data.CESR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00818201));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the MPU peripheral used on the Freescale Kinetis platform");
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


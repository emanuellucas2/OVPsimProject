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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "axi-intc", "Example");
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
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 512);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

    ppmInstallReadCallback(regNoDefinitionRead, (void*)0 , handles.bport1 + 0x0, 0x200);
    ppmInstallWriteCallback(regNoDefinitionWrite, (void*)0 , handles.bport1 + 0x0, 0x200);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "ab_ISR",
            "Interrupt Status Register (ISR)",
            handles.bport1,
            0x0,
            4,
            read_32,
            WriteISR,
            view32,
            &(bport1_ab_data.ISR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_IPR",
            "Interrupt Pending Register (IPR)",
            handles.bport1,
            0x4,
            4,
            ReadIPR,
            WriteIPR,
            view32,
            &(bport1_ab_data.IPR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_IER",
            "Interrupt Enable Register (IER)",
            handles.bport1,
            0x8,
            4,
            read_32,
            WriteIER,
            view32,
            &(bport1_ab_data.IER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_IAR",
            "Interrupt Acknowledge Register (IAR)",
            handles.bport1,
            0xc,
            4,
            read_32,
            WriteIAR,
            view32,
            &(bport1_ab_data.IAR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_SIE",
            "Set Interrupt Enables (SIE)",
            handles.bport1,
            0x10,
            4,
            read_32,
            WriteSIE,
            view32,
            &(bport1_ab_data.SIE.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CIE",
            "Clear Interrupt Enables (CIE)",
            handles.bport1,
            0x14,
            4,
            read_32,
            WriteCIE,
            view32,
            &(bport1_ab_data.CIE.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_IVR",
            "Interrupt Vector Register (IVR)",
            handles.bport1,
            0x18,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.IVR.value),
            True
        );
    }
    {
        registerHandle abMER_reg = ppmCreateRegister(
            "ab_MER",
            "Description\nMaster Enable Register (MER)\n\n\n",
            handles.bport1,
            0x1c,
            4,
            read_32,
            WriteMER,
            view32,
            &(bport1_ab_data.MER.value),
            True
        );

        ppmCreateRegisterField(abMER_reg, "ME", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abMER_reg, "HIE", 0, 1, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_IMR",
            "Interrupt Mode Register (IMR)",
            handles.bport1,
            0x20,
            4,
            read_32,
            WriteIMR,
            view32,
            &(bport1_ab_data.IMR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_ILR",
            "Interrupt Level Register (ILR)",
            handles.bport1,
            0x24,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.ILR.value),
            True
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR0",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x100,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[0].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR1",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x104,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[1].value),
            (void*)1,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR2",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x108,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[2].value),
            (void*)2,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR3",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x10c,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[3].value),
            (void*)3,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR4",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x110,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[4].value),
            (void*)4,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR5",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x114,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[5].value),
            (void*)5,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR6",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x118,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[6].value),
            (void*)6,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR7",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x11c,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[7].value),
            (void*)7,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR8",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x120,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[8].value),
            (void*)8,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR9",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x124,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[9].value),
            (void*)9,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR10",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x128,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[10].value),
            (void*)10,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR11",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x12c,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[11].value),
            (void*)11,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR12",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x130,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[12].value),
            (void*)12,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR13",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x134,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[13].value),
            (void*)13,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR14",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x138,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[14].value),
            (void*)14,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR15",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x13c,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[15].value),
            (void*)15,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR16",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x140,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[16].value),
            (void*)16,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR17",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x144,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[17].value),
            (void*)17,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR18",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x148,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[18].value),
            (void*)18,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR19",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x14c,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[19].value),
            (void*)19,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR20",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x150,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[20].value),
            (void*)20,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR21",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x154,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[21].value),
            (void*)21,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR22",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x158,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[22].value),
            (void*)22,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR23",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x15c,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[23].value),
            (void*)23,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR24",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x160,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[24].value),
            (void*)24,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR25",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x164,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[25].value),
            (void*)25,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR26",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x168,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[26].value),
            (void*)26,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR27",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x16c,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[27].value),
            (void*)27,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR28",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x170,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[28].value),
            (void*)28,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR29",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x174,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[29].value),
            (void*)29,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR30",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x178,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[30].value),
            (void*)30,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_IVAR31",
            "IVAR Interrupt Vector Address Register (IVAR)",
            handles.bport1,
            0x17c,
            4,
            ReadIVAR,
            WriteIVAR,
            0,
            &(bport1_ab_data.IVAR[31].value),
            (void*)31,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.IVAR[0].value = (Uns32)(bport1_ab_data.IVAR[0].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[1].value = (Uns32)(bport1_ab_data.IVAR[1].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[2].value = (Uns32)(bport1_ab_data.IVAR[2].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[3].value = (Uns32)(bport1_ab_data.IVAR[3].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[4].value = (Uns32)(bport1_ab_data.IVAR[4].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[5].value = (Uns32)(bport1_ab_data.IVAR[5].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[6].value = (Uns32)(bport1_ab_data.IVAR[6].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[7].value = (Uns32)(bport1_ab_data.IVAR[7].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[8].value = (Uns32)(bport1_ab_data.IVAR[8].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[9].value = (Uns32)(bport1_ab_data.IVAR[9].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[10].value = (Uns32)(bport1_ab_data.IVAR[10].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[11].value = (Uns32)(bport1_ab_data.IVAR[11].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[12].value = (Uns32)(bport1_ab_data.IVAR[12].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[13].value = (Uns32)(bport1_ab_data.IVAR[13].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[14].value = (Uns32)(bport1_ab_data.IVAR[14].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[15].value = (Uns32)(bport1_ab_data.IVAR[15].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[16].value = (Uns32)(bport1_ab_data.IVAR[16].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[17].value = (Uns32)(bport1_ab_data.IVAR[17].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[18].value = (Uns32)(bport1_ab_data.IVAR[18].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[19].value = (Uns32)(bport1_ab_data.IVAR[19].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[20].value = (Uns32)(bport1_ab_data.IVAR[20].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[21].value = (Uns32)(bport1_ab_data.IVAR[21].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[22].value = (Uns32)(bport1_ab_data.IVAR[22].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[23].value = (Uns32)(bport1_ab_data.IVAR[23].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[24].value = (Uns32)(bport1_ab_data.IVAR[24].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[25].value = (Uns32)(bport1_ab_data.IVAR[25].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[26].value = (Uns32)(bport1_ab_data.IVAR[26].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[27].value = (Uns32)(bport1_ab_data.IVAR[27].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[28].value = (Uns32)(bport1_ab_data.IVAR[28].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[29].value = (Uns32)(bport1_ab_data.IVAR[29].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[30].value = (Uns32)(bport1_ab_data.IVAR[30].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVAR[31].value = (Uns32)(bport1_ab_data.IVAR[31].value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ILR.value = (Uns32)(bport1_ab_data.ILR.value & ~(0xffffffff)) | ((0xffffffff) & (0xffffffff));
        bport1_ab_data.IMR.value = (Uns32)(bport1_ab_data.IMR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MER.value = (Uns32)(bport1_ab_data.MER.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IVR.value = (Uns32)(bport1_ab_data.IVR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CIE.value = (Uns32)(bport1_ab_data.CIE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SIE.value = (Uns32)(bport1_ab_data.SIE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IAR.value = (Uns32)(bport1_ab_data.IAR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IER.value = (Uns32)(bport1_ab_data.IER.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IPR.value = (Uns32)(bport1_ab_data.IPR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ISR.value = (Uns32)(bport1_ab_data.ISR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Microblaze LogiCORE IP AXI Interrupt Controller");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Implements the basic interrupt processing behavior");
        ppmDocAddText(doc_22_node, "Does not implement interrupt cascade");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "PG099 October 4, 2017 v4.1");
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


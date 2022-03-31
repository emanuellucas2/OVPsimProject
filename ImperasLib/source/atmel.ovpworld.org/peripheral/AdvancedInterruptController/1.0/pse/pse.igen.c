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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "AdvancedInterruptController", "Example");
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
    handles.bp1 = ppmCreateSlaveBusPort("bp1", 4096);
    if (!handles.bp1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bp1'");
    }

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR0",
            0,
            handles.bp1,
            0x0,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[0].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR1",
            0,
            handles.bp1,
            0x4,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[1].value),
            (void*)1,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR2",
            0,
            handles.bp1,
            0x8,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[2].value),
            (void*)2,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR3",
            0,
            handles.bp1,
            0xc,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[3].value),
            (void*)3,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR4",
            0,
            handles.bp1,
            0x10,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[4].value),
            (void*)4,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR5",
            0,
            handles.bp1,
            0x14,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[5].value),
            (void*)5,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR6",
            0,
            handles.bp1,
            0x18,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[6].value),
            (void*)6,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR7",
            0,
            handles.bp1,
            0x1c,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[7].value),
            (void*)7,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR8",
            0,
            handles.bp1,
            0x20,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[8].value),
            (void*)8,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR9",
            0,
            handles.bp1,
            0x24,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[9].value),
            (void*)9,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR10",
            0,
            handles.bp1,
            0x28,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[10].value),
            (void*)10,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR11",
            0,
            handles.bp1,
            0x2c,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[11].value),
            (void*)11,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR12",
            0,
            handles.bp1,
            0x30,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[12].value),
            (void*)12,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR13",
            0,
            handles.bp1,
            0x34,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[13].value),
            (void*)13,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR14",
            0,
            handles.bp1,
            0x38,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[14].value),
            (void*)14,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR15",
            0,
            handles.bp1,
            0x3c,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[15].value),
            (void*)15,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR16",
            0,
            handles.bp1,
            0x40,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[16].value),
            (void*)16,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR17",
            0,
            handles.bp1,
            0x44,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[17].value),
            (void*)17,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR18",
            0,
            handles.bp1,
            0x48,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[18].value),
            (void*)18,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR19",
            0,
            handles.bp1,
            0x4c,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[19].value),
            (void*)19,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR20",
            0,
            handles.bp1,
            0x50,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[20].value),
            (void*)20,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR21",
            0,
            handles.bp1,
            0x54,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[21].value),
            (void*)21,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR22",
            0,
            handles.bp1,
            0x58,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[22].value),
            (void*)22,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR23",
            0,
            handles.bp1,
            0x5c,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[23].value),
            (void*)23,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR24",
            0,
            handles.bp1,
            0x60,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[24].value),
            (void*)24,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR25",
            0,
            handles.bp1,
            0x64,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[25].value),
            (void*)25,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR26",
            0,
            handles.bp1,
            0x68,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[26].value),
            (void*)26,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR27",
            0,
            handles.bp1,
            0x6c,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[27].value),
            (void*)27,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR28",
            0,
            handles.bp1,
            0x70,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[28].value),
            (void*)28,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR29",
            0,
            handles.bp1,
            0x74,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[29].value),
            (void*)29,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR30",
            0,
            handles.bp1,
            0x78,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[30].value),
            (void*)30,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SMR_reg = ppmCreateNByteRegister(
            "REG_AIC_SMR31",
            0,
            handles.bp1,
            0x7c,
            4,
            0,
            AIC_SMR_wcb,
            0,
            &(bp1_REG_data.AIC_SMR[31].value),
            (void*)31,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SMR_reg, "PRIOR", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGAIC_SMR_reg, "SRCTYPE", 0, 5, 2, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR0",
            0,
            handles.bp1,
            0x80,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[0].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR1",
            0,
            handles.bp1,
            0x84,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[1].value),
            (void*)1,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR2",
            0,
            handles.bp1,
            0x88,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[2].value),
            (void*)2,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR3",
            0,
            handles.bp1,
            0x8c,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[3].value),
            (void*)3,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR4",
            0,
            handles.bp1,
            0x90,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[4].value),
            (void*)4,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR5",
            0,
            handles.bp1,
            0x94,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[5].value),
            (void*)5,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR6",
            0,
            handles.bp1,
            0x98,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[6].value),
            (void*)6,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR7",
            0,
            handles.bp1,
            0x9c,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[7].value),
            (void*)7,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR8",
            0,
            handles.bp1,
            0xa0,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[8].value),
            (void*)8,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR9",
            0,
            handles.bp1,
            0xa4,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[9].value),
            (void*)9,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR10",
            0,
            handles.bp1,
            0xa8,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[10].value),
            (void*)10,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR11",
            0,
            handles.bp1,
            0xac,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[11].value),
            (void*)11,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR12",
            0,
            handles.bp1,
            0xb0,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[12].value),
            (void*)12,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR13",
            0,
            handles.bp1,
            0xb4,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[13].value),
            (void*)13,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR14",
            0,
            handles.bp1,
            0xb8,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[14].value),
            (void*)14,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR15",
            0,
            handles.bp1,
            0xbc,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[15].value),
            (void*)15,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR16",
            0,
            handles.bp1,
            0xc0,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[16].value),
            (void*)16,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR17",
            0,
            handles.bp1,
            0xc4,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[17].value),
            (void*)17,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR18",
            0,
            handles.bp1,
            0xc8,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[18].value),
            (void*)18,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR19",
            0,
            handles.bp1,
            0xcc,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[19].value),
            (void*)19,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR20",
            0,
            handles.bp1,
            0xd0,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[20].value),
            (void*)20,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR21",
            0,
            handles.bp1,
            0xd4,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[21].value),
            (void*)21,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR22",
            0,
            handles.bp1,
            0xd8,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[22].value),
            (void*)22,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR23",
            0,
            handles.bp1,
            0xdc,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[23].value),
            (void*)23,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR24",
            0,
            handles.bp1,
            0xe0,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[24].value),
            (void*)24,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR25",
            0,
            handles.bp1,
            0xe4,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[25].value),
            (void*)25,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR26",
            0,
            handles.bp1,
            0xe8,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[26].value),
            (void*)26,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR27",
            0,
            handles.bp1,
            0xec,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[27].value),
            (void*)27,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR28",
            0,
            handles.bp1,
            0xf0,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[28].value),
            (void*)28,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR29",
            0,
            handles.bp1,
            0xf4,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[29].value),
            (void*)29,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR30",
            0,
            handles.bp1,
            0xf8,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[30].value),
            (void*)30,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle REGAIC_SVR_reg = ppmCreateNByteRegister(
            "REG_AIC_SVR31",
            0,
            handles.bp1,
            0xfc,
            4,
            0,
            AIC_SVR_wcb,
            0,
            &(bp1_REG_data.AIC_SVR[31].value),
            (void*)31,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(REGAIC_SVR_reg, "VECTOR", 0, 0, 32, 1, 1);
    }
    {
        ppmCreateRegister(
            "REG_AIC_IVR",
            0,
            handles.bp1,
            0x100,
            4,
            AIC_IVR_rcb,
            0,
            view32,
            &(bp1_REG_data.AIC_IVR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_AIC_FVR",
            0,
            handles.bp1,
            0x104,
            4,
            read_32,
            0,
            view32,
            &(bp1_REG_data.AIC_FVR.value),
            True
        );
    }
    {
        registerHandle REGAIC_ISR_reg = ppmCreateRegister(
            "REG_AIC_ISR",
            0,
            handles.bp1,
            0x108,
            4,
            read_32,
            0,
            view32,
            &(bp1_REG_data.AIC_ISR.value),
            True
        );

        ppmCreateRegisterField(REGAIC_ISR_reg, "IRQID", 0, 0, 5, 1, 0);
    }
    {
        registerHandle REGAIC_IPR_reg = ppmCreateRegister(
            "REG_AIC_IPR",
            0,
            handles.bp1,
            0x10c,
            4,
            read_32,
            0,
            view32,
            &(bp1_REG_data.AIC_IPR.value),
            True
        );

        ppmCreateRegisterField(REGAIC_IPR_reg, "IRQ2", 0, 18, 1, 1, 0);
        ppmCreateRegisterField(REGAIC_IPR_reg, "IRQ1", 0, 17, 1, 1, 0);
        ppmCreateRegisterField(REGAIC_IPR_reg, "IRQ0", 0, 16, 1, 1, 0);
        ppmCreateRegisterField(REGAIC_IPR_reg, "PIOIRQ", 0, 8, 1, 1, 0);
        ppmCreateRegisterField(REGAIC_IPR_reg, "WDIRQ", 0, 7, 1, 1, 0);
        ppmCreateRegisterField(REGAIC_IPR_reg, "TC2IRQ", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(REGAIC_IPR_reg, "TC1IRQ", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(REGAIC_IPR_reg, "TC0IRQ", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(REGAIC_IPR_reg, "US1IRQ", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(REGAIC_IPR_reg, "US0IRQ", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(REGAIC_IPR_reg, "SWIRQ", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(REGAIC_IPR_reg, "FIQ", 0, 0, 1, 1, 0);
    }
    {
        registerHandle REGAIC_IMR_reg = ppmCreateRegister(
            "REG_AIC_IMR",
            0,
            handles.bp1,
            0x110,
            4,
            read_32,
            0,
            view32,
            &(bp1_REG_data.AIC_IMR.value),
            True
        );

        ppmCreateRegisterField(REGAIC_IMR_reg, "IRQ2", 0, 18, 1, 1, 0);
        ppmCreateRegisterField(REGAIC_IMR_reg, "IRQ1", 0, 17, 1, 1, 0);
        ppmCreateRegisterField(REGAIC_IMR_reg, "IRQ0", 0, 16, 1, 1, 0);
        ppmCreateRegisterField(REGAIC_IMR_reg, "PIOIRQ", 0, 8, 1, 1, 0);
        ppmCreateRegisterField(REGAIC_IMR_reg, "WDIRQ", 0, 7, 1, 1, 0);
        ppmCreateRegisterField(REGAIC_IMR_reg, "TC2IRQ", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(REGAIC_IMR_reg, "TC1IRQ", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(REGAIC_IMR_reg, "TC0IRQ", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(REGAIC_IMR_reg, "US1IRQ", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(REGAIC_IMR_reg, "US0IRQ", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(REGAIC_IMR_reg, "SWIRQ", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(REGAIC_IMR_reg, "FIQ", 0, 0, 1, 1, 0);
    }
    {
        registerHandle REGAIC_CISR_reg = ppmCreateRegister(
            "REG_AIC_CISR",
            0,
            handles.bp1,
            0x114,
            4,
            read_32,
            0,
            view32,
            &(bp1_REG_data.AIC_CISR.value),
            True
        );

        ppmCreateRegisterField(REGAIC_CISR_reg, "NIRQ", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(REGAIC_CISR_reg, "NFIQ", 0, 0, 1, 1, 0);
    }
    {
        registerHandle REGAIC_IECR_reg = ppmCreateRegister(
            "REG_AIC_IECR",
            0,
            handles.bp1,
            0x120,
            4,
            0,
            AIC_IECR_wcb,
            view32,
            &(bp1_REG_data.AIC_IECR.value),
            True
        );

        ppmCreateRegisterField(REGAIC_IECR_reg, "IRQ2", 0, 18, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_IECR_reg, "IRQ1", 0, 17, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_IECR_reg, "IRQ0", 0, 16, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_IECR_reg, "PIOIRQ", 0, 8, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_IECR_reg, "WDIRQ", 0, 7, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_IECR_reg, "TC2IRQ", 0, 6, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_IECR_reg, "TC1IRQ", 0, 5, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_IECR_reg, "TC0IRQ", 0, 4, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_IECR_reg, "US1IRQ", 0, 3, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_IECR_reg, "US0IRQ", 0, 2, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_IECR_reg, "SWIRQ", 0, 1, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_IECR_reg, "FIQ", 0, 0, 1, 0, 1);
    }
    {
        registerHandle REGAIC_IDCR_reg = ppmCreateRegister(
            "REG_AIC_IDCR",
            0,
            handles.bp1,
            0x124,
            4,
            0,
            AIC_IDCR_wcb,
            view32,
            &(bp1_REG_data.AIC_IDCR.value),
            True
        );

        ppmCreateRegisterField(REGAIC_IDCR_reg, "IRQ2", 0, 18, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_IDCR_reg, "IRQ1", 0, 17, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_IDCR_reg, "IRQ0", 0, 16, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_IDCR_reg, "PIOIRQ", 0, 8, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_IDCR_reg, "WDIRQ", 0, 7, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_IDCR_reg, "TC2IRQ", 0, 6, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_IDCR_reg, "TC1IRQ", 0, 5, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_IDCR_reg, "TC0IRQ", 0, 4, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_IDCR_reg, "US1IRQ", 0, 3, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_IDCR_reg, "US0IRQ", 0, 2, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_IDCR_reg, "SWIRQ", 0, 1, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_IDCR_reg, "FIQ", 0, 0, 1, 0, 1);
    }
    {
        registerHandle REGAIC_ICCR_reg = ppmCreateRegister(
            "REG_AIC_ICCR",
            0,
            handles.bp1,
            0x128,
            4,
            0,
            AIC_ICCR_wcb,
            view32,
            &(bp1_REG_data.AIC_ICCR.value),
            True
        );

        ppmCreateRegisterField(REGAIC_ICCR_reg, "IRQ2", 0, 18, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_ICCR_reg, "IRQ1", 0, 17, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_ICCR_reg, "IRQ0", 0, 16, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_ICCR_reg, "PIOIRQ", 0, 8, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_ICCR_reg, "WDIRQ", 0, 7, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_ICCR_reg, "TC2IRQ", 0, 6, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_ICCR_reg, "TC1IRQ", 0, 5, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_ICCR_reg, "TC0IRQ", 0, 4, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_ICCR_reg, "US1IRQ", 0, 3, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_ICCR_reg, "US0IRQ", 0, 2, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_ICCR_reg, "SWIRQ", 0, 1, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_ICCR_reg, "FIQ", 0, 0, 1, 0, 1);
    }
    {
        registerHandle REGAIC_ISCR_reg = ppmCreateRegister(
            "REG_AIC_ISCR",
            0,
            handles.bp1,
            0x12c,
            4,
            0,
            AIC_ISCR_wcb,
            view32,
            &(bp1_REG_data.AIC_ISCR.value),
            True
        );

        ppmCreateRegisterField(REGAIC_ISCR_reg, "IRQ2", 0, 18, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_ISCR_reg, "IRQ1", 0, 17, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_ISCR_reg, "IRQ0", 0, 16, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_ISCR_reg, "PIOIRQ", 0, 8, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_ISCR_reg, "WDIRQ", 0, 7, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_ISCR_reg, "TC2IRQ", 0, 6, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_ISCR_reg, "TC1IRQ", 0, 5, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_ISCR_reg, "TC0IRQ", 0, 4, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_ISCR_reg, "US1IRQ", 0, 3, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_ISCR_reg, "US0IRQ", 0, 2, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_ISCR_reg, "SWIRQ", 0, 1, 1, 0, 1);
        ppmCreateRegisterField(REGAIC_ISCR_reg, "FIQ", 0, 0, 1, 0, 1);
    }
    {
        ppmCreateRegister(
            "REG_AIC_EOICR",
            0,
            handles.bp1,
            0x130,
            4,
            0,
            AIC_EOICR_wcb,
            view32,
            &(bp1_REG_data.AIC_EOICR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_AIC_SPU",
            0,
            handles.bp1,
            0x134,
            4,
            read_32,
            AIC_SPU_wcb,
            view32,
            &(bp1_REG_data.AIC_SPU.value),
            True
        );
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bp1_REG_data.AIC_SPU.value = (Uns32)(bp1_REG_data.AIC_SPU.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.AIC_EOICR.value = (Uns32)(bp1_REG_data.AIC_EOICR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.AIC_ISCR.value = (Uns32)(bp1_REG_data.AIC_ISCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.AIC_ICCR.value = (Uns32)(bp1_REG_data.AIC_ICCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.AIC_IDCR.value = (Uns32)(bp1_REG_data.AIC_IDCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.AIC_IECR.value = (Uns32)(bp1_REG_data.AIC_IECR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.AIC_CISR.value = (Uns32)(bp1_REG_data.AIC_CISR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.AIC_IMR.value = (Uns32)(bp1_REG_data.AIC_IMR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.AIC_IPR.value = (Uns32)(bp1_REG_data.AIC_IPR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.AIC_ISR.value = (Uns32)(bp1_REG_data.AIC_ISR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.AIC_FVR.value = (Uns32)(bp1_REG_data.AIC_FVR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bp1_REG_data.AIC_IVR.value = (Uns32)(bp1_REG_data.AIC_IVR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "AIC: Advanced Interrupt Controller\nThis model contains an accurate Register set interface.\nThe functionality has only been implemented to sufficiently boot uClinux\nThe Advanced Interrupt Controller has an 8-level priority, individually maskable, vectored interrupt\ncontroller, and drives the NIRQ and NFIQ pins of the ARM7TDMI from:\n The external fast interrupt line (FIQ)\n The three external interrupt request lines (IRQ0 - IRQ2)\n The interrupt signals from the on-chip peripherals\nThe AIC is extensively programmable offering maximum flexibility, and its vectoring features\nreduce the real-time overhead in handling interrupts.\nThe AIC also features a spurious vector detection feature, which reduces spurious interrupt handling\nto a minimum, and a protect mode that facilitates the debug capabilities.\n");
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


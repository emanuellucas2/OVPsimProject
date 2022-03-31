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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "VybridDMA", "Example");
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

static PPM_WRITE_CB(bport1_ab_EARS_maskWrite) {
    bport1_ab_data.EARS.value = (bport1_ab_data.EARS.value & BPORT1_AB_EARS_WRNMASK) | (data & BPORT1_AB_EARS_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 8192);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abCR_reg = ppmCreateRegister(
            "ab_CR",
            "Control Register, offset: 0x0 ",
            handles.bport1,
            0x0,
            4,
            regReadCR,
            regWriteCR,
            view32,
            &(bport1_ab_data.CR.value),
            True
        );

        ppmCreateRegisterField(abCR_reg, "CLM", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abCR_reg, "CX", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abCR_reg, "ECX", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abCR_reg, "EDBG", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abCR_reg, "EMLM", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCR_reg, "ERCA", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abCR_reg, "ERGA", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abCR_reg, "GRP0PRI", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(abCR_reg, "GRP1PRI", 0, 10, 2, 1, 1);
        ppmCreateRegisterField(abCR_reg, "HALT", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abCR_reg, "HOE", 0, 4, 1, 1, 1);
    }
    {
        registerHandle abES_reg = ppmCreateRegister(
            "ab_ES",
            "Error Status Register, offset: 0x4 ",
            handles.bport1,
            0x4,
            4,
            regReadES,
            0,
            view32,
            &(bport1_ab_data.ES.value),
            True
        );

        ppmCreateRegisterField(abES_reg, "CPE", 0, 14, 1, 1, 0);
        ppmCreateRegisterField(abES_reg, "DAE", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(abES_reg, "DBE", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(abES_reg, "DOE", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(abES_reg, "ECX", 0, 16, 1, 1, 0);
        ppmCreateRegisterField(abES_reg, "ERRCHN", 0, 8, 5, 1, 0);
        ppmCreateRegisterField(abES_reg, "GPE", 0, 15, 1, 1, 0);
        ppmCreateRegisterField(abES_reg, "NCE", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(abES_reg, "SAE", 0, 7, 1, 1, 0);
        ppmCreateRegisterField(abES_reg, "SBE", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(abES_reg, "SGE", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(abES_reg, "SOE", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(abES_reg, "VLD", 0, 31, 1, 1, 0);
    }
    {
        registerHandle abERQ_reg = ppmCreateRegister(
            "ab_ERQ",
            "Enable Request Register, offset: 0xC ",
            handles.bport1,
            0xc,
            4,
            regRead32,
            regWrite32,
            view32,
            &(bport1_ab_data.ERQ.value),
            True
        );

        ppmCreateRegisterField(abERQ_reg, "ERQ0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ10", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ11", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ12", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ13", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ14", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ15", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ16", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ17", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ18", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ19", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ2", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ20", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ21", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ22", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ23", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ24", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ25", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ26", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ27", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ28", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ29", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ3", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ30", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ31", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ4", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ5", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ7", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ8", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abERQ_reg, "ERQ9", 0, 9, 1, 1, 1);
    }
    {
        registerHandle abEEI_reg = ppmCreateRegister(
            "ab_EEI",
            0,
            handles.bport1,
            0x14,
            4,
            regRead32,
            regWrite32,
            view32,
            &(bport1_ab_data.EEI.value),
            True
        );

        ppmCreateRegisterField(abEEI_reg, "EEI0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI10", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI11", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI12", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI13", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI14", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI15", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI16", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI17", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI18", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI19", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI2", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI20", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI21", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI22", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI23", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI24", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI25", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI26", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI27", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI28", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI29", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI3", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI30", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI31", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI4", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI5", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI7", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI8", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abEEI_reg, "EEI9", 0, 9, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_CS_EEI_ERC",
            "Clear/Set EEI, ERC",
            handles.bport1,
            0x18,
            4,
            regReadZero,
            regSetGroup,
            view32,
            &(bport1_ab_data.CS_EEI_ERC.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DNE_SRT_ERR_INT",
            "Clear/Set DNE, START, ERR, INT registers",
            handles.bport1,
            0x1c,
            4,
            regReadZero,
            regSetGroup,
            view32,
            &(bport1_ab_data.DNE_SRT_ERR_INT.value),
            True
        );
    }
    {
        registerHandle abINT_reg = ppmCreateRegister(
            "ab_INT",
            0,
            handles.bport1,
            0x24,
            4,
            regRead32,
            regWrite1c,
            view32,
            &(bport1_ab_data.INT.value),
            True
        );

        ppmCreateRegisterField(abINT_reg, "INT0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT10", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT11", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT12", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT13", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT14", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT15", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT16", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT17", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT18", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT19", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT2", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT20", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT21", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT22", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT23", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT24", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT25", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT26", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT27", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT28", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT29", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT3", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT30", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT31", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT4", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT5", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT7", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT8", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abINT_reg, "INT9", 0, 9, 1, 1, 1);
    }
    {
        registerHandle abERR_reg = ppmCreateRegister(
            "ab_ERR",
            "Error Register, offset: 0x2C ",
            handles.bport1,
            0x2c,
            4,
            regRead32,
            regWrite1c,
            view32,
            &(bport1_ab_data.ERR.value),
            True
        );

        ppmCreateRegisterField(abERR_reg, "ERR0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR10", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR11", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR12", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR13", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR14", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR15", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR16", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR17", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR18", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR19", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR2", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR20", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR21", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR22", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR23", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR24", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR25", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR26", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR27", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR28", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR29", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR3", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR30", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR31", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR4", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR5", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR7", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR8", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abERR_reg, "ERR9", 0, 9, 1, 1, 1);
    }
    {
        registerHandle abHRS_reg = ppmCreateRegister(
            "ab_HRS",
            0,
            handles.bport1,
            0x34,
            4,
            regRead32,
            regWrite32,
            view32,
            &(bport1_ab_data.HRS.value),
            True
        );

        ppmCreateRegisterField(abHRS_reg, "HRS0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS10", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS11", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS12", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS13", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS14", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS15", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS16", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS17", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS18", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS19", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS2", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS20", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS21", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS22", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS23", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS24", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS25", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS26", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS27", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS28", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS29", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS3", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS30", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS31", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS4", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS5", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS7", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS8", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abHRS_reg, "HRS9", 0, 9, 1, 1, 1);
    }
    {
        registerHandle abEARS_reg = ppmCreateRegister(
            "ab_EARS",
            "Enable Asyncronous Request",
            handles.bport1,
            0x44,
            4,
            read_32,
            bport1_ab_EARS_maskWrite,
            view32,
            &(bport1_ab_data.EARS.value),
            True
        );

        ppmCreateRegisterField(abEARS_reg, "EDREQ_0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_10", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_11", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_12", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_13", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_14", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_15", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_16", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_17", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_18", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_19", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_2", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_20", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_21", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_22", 0, 22, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_23", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_24", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_25", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_26", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_27", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_28", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_29", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_3", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_30", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_31", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_4", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_5", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_6", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_7", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_8", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abEARS_reg, "EDREQ_9", 0, 9, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_DCHPRI3_0",
            "Channel n Priority Registers 3 to 0",
            handles.bport1,
            0x100,
            4,
            regReadCHPRI,
            regWriteCHPRI,
            view32,
            &(bport1_ab_data.DCHPRI3_0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DCHPRI7_4",
            0,
            handles.bport1,
            0x104,
            4,
            regReadCHPRI,
            regWriteCHPRI,
            view32,
            &(bport1_ab_data.DCHPRI7_4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DCHPRI11_8",
            0,
            handles.bport1,
            0x108,
            4,
            regReadCHPRI,
            regWriteCHPRI,
            view32,
            &(bport1_ab_data.DCHPRI11_8.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DCHPRI15_12",
            0,
            handles.bport1,
            0x10c,
            4,
            regReadCHPRI,
            regWriteCHPRI,
            view32,
            &(bport1_ab_data.DCHPRI15_12.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DCHPRI19_16",
            0,
            handles.bport1,
            0x110,
            4,
            regReadCHPRI,
            regWriteCHPRI,
            view32,
            &(bport1_ab_data.DCHPRI19_16.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DCHPRI23_20",
            0,
            handles.bport1,
            0x114,
            4,
            regReadCHPRI,
            regWriteCHPRI,
            view32,
            &(bport1_ab_data.DCHPRI23_20.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DCHPRI27_24",
            0,
            handles.bport1,
            0x118,
            4,
            regReadCHPRI,
            regWriteCHPRI,
            view32,
            &(bport1_ab_data.DCHPRI27_24.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DCHPRI31_28",
            0,
            handles.bport1,
            0x11c,
            4,
            regReadCHPRI,
            regWriteCHPRI,
            view32,
            &(bport1_ab_data.DCHPRI31_28.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD0_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x1000,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD0_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD0_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x1004,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD0_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD0_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x1008,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD0_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD0_SLAST",
            0,
            handles.bport1,
            0x100c,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD0_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD0_DADDR",
            0,
            handles.bport1,
            0x1010,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD0_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD0_DOFF_CITER",
            0,
            handles.bport1,
            0x1014,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD0_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD0_DLASTSGA",
            0,
            handles.bport1,
            0x1018,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD0_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD0_CSR_BITER",
            0,
            handles.bport1,
            0x101c,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD0_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD1_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x1020,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD1_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD1_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x1024,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD1_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD1_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x1028,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD1_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD1_SLAST",
            0,
            handles.bport1,
            0x102c,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD1_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD1_DADDR",
            0,
            handles.bport1,
            0x1030,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD1_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD1_DOFF_CITER",
            0,
            handles.bport1,
            0x1034,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD1_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD1_DLASTSGA",
            0,
            handles.bport1,
            0x1038,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD1_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD1_CSR_BITER",
            0,
            handles.bport1,
            0x103c,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD1_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD2_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x1040,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD2_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD2_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x1044,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD2_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD2_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x1048,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD2_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD2_SLAST",
            0,
            handles.bport1,
            0x104c,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD2_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD2_DADDR",
            0,
            handles.bport1,
            0x1050,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD2_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD2_DOFF_CITER",
            0,
            handles.bport1,
            0x1054,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD2_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD2_DLASTSGA",
            0,
            handles.bport1,
            0x1058,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD2_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD2_CSR_BITER",
            0,
            handles.bport1,
            0x105c,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD2_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD3_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x1060,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD3_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD3_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x1064,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD3_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD3_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x1068,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD3_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD3_SLAST",
            0,
            handles.bport1,
            0x106c,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD3_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD3_DADDR",
            0,
            handles.bport1,
            0x1070,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD3_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD3_DOFF_CITER",
            0,
            handles.bport1,
            0x1074,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD3_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD3_DLASTSGA",
            0,
            handles.bport1,
            0x1078,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD3_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD3_CSR_BITER",
            0,
            handles.bport1,
            0x107c,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD3_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD4_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x1080,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD4_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD4_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x1084,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD4_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD4_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x1088,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD4_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD4_SLAST",
            0,
            handles.bport1,
            0x108c,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD4_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD4_DADDR",
            0,
            handles.bport1,
            0x1090,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD4_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD4_DOFF_CITER",
            0,
            handles.bport1,
            0x1094,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD4_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD4_DLASTSGA",
            0,
            handles.bport1,
            0x1098,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD4_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD4_CSR_BITER",
            0,
            handles.bport1,
            0x109c,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD4_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD5_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x10a0,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD5_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD5_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x10a4,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD5_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD5_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x10a8,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD5_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD5_SLAST",
            0,
            handles.bport1,
            0x10ac,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD5_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD5_DADDR",
            0,
            handles.bport1,
            0x10b0,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD5_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD5_DOFF_CITER",
            0,
            handles.bport1,
            0x10b4,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD5_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD5_DLASTSGA",
            0,
            handles.bport1,
            0x10b8,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD5_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD5_CSR_BITER",
            0,
            handles.bport1,
            0x10bc,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD5_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD6_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x10c0,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD6_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD6_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x10c4,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD6_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD6_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x10c8,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD6_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD6_SLAST",
            0,
            handles.bport1,
            0x10cc,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD6_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD6_DADDR",
            0,
            handles.bport1,
            0x10d0,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD6_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD6_DOFF_CITER",
            0,
            handles.bport1,
            0x10d4,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD6_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD6_DLASTSGA",
            0,
            handles.bport1,
            0x10d8,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD6_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD6_CSR_BITER",
            0,
            handles.bport1,
            0x10dc,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD6_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD7_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x10e0,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD7_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD7_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x10e4,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD7_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD7_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x10e8,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD7_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD7_SLAST",
            0,
            handles.bport1,
            0x10ec,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD7_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD7_DADDR",
            0,
            handles.bport1,
            0x10f0,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD7_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD7_DOFF_CITER",
            0,
            handles.bport1,
            0x10f4,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD7_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD7_DLASTSGA",
            0,
            handles.bport1,
            0x10f8,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD7_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD7_CSR_BITER",
            0,
            handles.bport1,
            0x10fc,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD7_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD8_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x1100,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD8_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD8_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x1104,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD8_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD8_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x1108,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD8_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD8_SLAST",
            0,
            handles.bport1,
            0x110c,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD8_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD8_DADDR",
            0,
            handles.bport1,
            0x1110,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD8_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD8_DOFF_CITER",
            0,
            handles.bport1,
            0x1114,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD8_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD8_DLASTSGA",
            0,
            handles.bport1,
            0x1118,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD8_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD8_CSR_BITER",
            0,
            handles.bport1,
            0x111c,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD8_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD9_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x1120,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD9_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD9_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x1124,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD9_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD9_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x1128,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD9_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD9_SLAST",
            0,
            handles.bport1,
            0x112c,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD9_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD9_DADDR",
            0,
            handles.bport1,
            0x1130,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD9_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD9_DOFF_CITER",
            0,
            handles.bport1,
            0x1134,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD9_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD9_DLASTSGA",
            0,
            handles.bport1,
            0x1138,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD9_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD9_CSR_BITER",
            0,
            handles.bport1,
            0x113c,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD9_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD10_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x1140,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD10_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD10_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x1144,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD10_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD10_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x1148,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD10_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD10_SLAST",
            0,
            handles.bport1,
            0x114c,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD10_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD10_DADDR",
            0,
            handles.bport1,
            0x1150,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD10_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD10_DOFF_CITER",
            0,
            handles.bport1,
            0x1154,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD10_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD10_DLASTSGA",
            0,
            handles.bport1,
            0x1158,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD10_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD10_CSR_BITER",
            0,
            handles.bport1,
            0x115c,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD10_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD11_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x1160,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD11_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD11_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x1164,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD11_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD11_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x1168,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD11_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD11_SLAST",
            0,
            handles.bport1,
            0x116c,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD11_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD11_DADDR",
            0,
            handles.bport1,
            0x1170,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD11_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD11_DOFF_CITER",
            0,
            handles.bport1,
            0x1174,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD11_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD11_DLASTSGA",
            0,
            handles.bport1,
            0x1178,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD11_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD11_CSR_BITER",
            0,
            handles.bport1,
            0x117c,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD11_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD12_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x1180,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD12_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD12_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x1184,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD12_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD12_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x1188,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD12_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD12_SLAST",
            0,
            handles.bport1,
            0x118c,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD12_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD12_DADDR",
            0,
            handles.bport1,
            0x1190,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD12_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD12_DOFF_CITER",
            0,
            handles.bport1,
            0x1194,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD12_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD12_DLASTSGA",
            0,
            handles.bport1,
            0x1198,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD12_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD12_CSR_BITER",
            0,
            handles.bport1,
            0x119c,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD12_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD13_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x11a0,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD13_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD13_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x11a4,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD13_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD13_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x11a8,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD13_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD13_SLAST",
            0,
            handles.bport1,
            0x11ac,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD13_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD13_DADDR",
            0,
            handles.bport1,
            0x11b0,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD13_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD13_DOFF_CITER",
            0,
            handles.bport1,
            0x11b4,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD13_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD13_DLASTSGA",
            0,
            handles.bport1,
            0x11b8,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD13_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD13_CSR_BITER",
            0,
            handles.bport1,
            0x11bc,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD13_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD14_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x11c0,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD14_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD14_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x11c4,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD14_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD14_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x11c8,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD14_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD14_SLAST",
            0,
            handles.bport1,
            0x11cc,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD14_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD14_DADDR",
            0,
            handles.bport1,
            0x11d0,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD14_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD14_DOFF_CITER",
            0,
            handles.bport1,
            0x11d4,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD14_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD14_DLASTSGA",
            0,
            handles.bport1,
            0x11d8,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD14_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD14_CSR_BITER",
            0,
            handles.bport1,
            0x11dc,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD14_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD15_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x11e0,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD15_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD15_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x11e4,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD15_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD15_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x11e8,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD15_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD15_SLAST",
            0,
            handles.bport1,
            0x11ec,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD15_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD15_DADDR",
            0,
            handles.bport1,
            0x11f0,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD15_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD15_DOFF_CITER",
            0,
            handles.bport1,
            0x11f4,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD15_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD15_DLASTSGA",
            0,
            handles.bport1,
            0x11f8,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD15_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD15_CSR_BITER",
            0,
            handles.bport1,
            0x11fc,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD15_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD16_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x1200,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD16_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD16_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x1204,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD16_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD16_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x1208,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD16_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD16_SLAST",
            0,
            handles.bport1,
            0x120c,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD16_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD16_DADDR",
            0,
            handles.bport1,
            0x1210,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD16_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD16_DOFF_CITER",
            0,
            handles.bport1,
            0x1214,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD16_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD16_DLASTSGA",
            0,
            handles.bport1,
            0x1218,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD16_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD16_CSR_BITER",
            0,
            handles.bport1,
            0x121c,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD16_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD17_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x1220,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD17_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD17_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x1224,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD17_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD17_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x1228,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD17_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD17_SLAST",
            0,
            handles.bport1,
            0x122c,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD17_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD17_DADDR",
            0,
            handles.bport1,
            0x1230,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD17_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD17_DOFF_CITER",
            0,
            handles.bport1,
            0x1234,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD17_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD17_DLASTSGA",
            0,
            handles.bport1,
            0x1238,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD17_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD17_CSR_BITER",
            0,
            handles.bport1,
            0x123c,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD17_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD18_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x1240,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD18_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD18_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x1244,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD18_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD18_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x1248,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD18_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD18_SLAST",
            0,
            handles.bport1,
            0x124c,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD18_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD18_DADDR",
            0,
            handles.bport1,
            0x1250,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD18_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD18_DOFF_CITER",
            0,
            handles.bport1,
            0x1254,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD18_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD18_DLASTSGA",
            0,
            handles.bport1,
            0x1258,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD18_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD18_CSR_BITER",
            0,
            handles.bport1,
            0x125c,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD18_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD19_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x1260,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD19_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD19_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x1264,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD19_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD19_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x1268,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD19_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD19_SLAST",
            0,
            handles.bport1,
            0x126c,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD19_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD19_DADDR",
            0,
            handles.bport1,
            0x1270,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD19_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD19_DOFF_CITER",
            0,
            handles.bport1,
            0x1274,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD19_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD19_DLASTSGA",
            0,
            handles.bport1,
            0x1278,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD19_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD19_CSR_BITER",
            0,
            handles.bport1,
            0x127c,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD19_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD20_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x1280,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD20_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD20_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x1284,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD20_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD20_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x1288,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD20_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD20_SLAST",
            0,
            handles.bport1,
            0x128c,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD20_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD20_DADDR",
            0,
            handles.bport1,
            0x1290,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD20_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD20_DOFF_CITER",
            0,
            handles.bport1,
            0x1294,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD20_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD20_DLASTSGA",
            0,
            handles.bport1,
            0x1298,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD20_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD20_CSR_BITER",
            0,
            handles.bport1,
            0x129c,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD20_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD21_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x12a0,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD21_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD21_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x12a4,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD21_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD21_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x12a8,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD21_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD21_SLAST",
            0,
            handles.bport1,
            0x12ac,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD21_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD21_DADDR",
            0,
            handles.bport1,
            0x12b0,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD21_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD21_DOFF_CITER",
            0,
            handles.bport1,
            0x12b4,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD21_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD21_DLASTSGA",
            0,
            handles.bport1,
            0x12b8,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD21_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD21_CSR_BITER",
            0,
            handles.bport1,
            0x12bc,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD21_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD22_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x12c0,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD22_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD22_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x12c4,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD22_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD22_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x12c8,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD22_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD22_SLAST",
            0,
            handles.bport1,
            0x12cc,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD22_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD22_DADDR",
            0,
            handles.bport1,
            0x12d0,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD22_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD22_DOFF_CITER",
            0,
            handles.bport1,
            0x12d4,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD22_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD22_DLASTSGA",
            0,
            handles.bport1,
            0x12d8,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD22_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD22_CSR_BITER",
            0,
            handles.bport1,
            0x12dc,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD22_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD23_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x12e0,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD23_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD23_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x12e4,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD23_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD23_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x12e8,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD23_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD23_SLAST",
            0,
            handles.bport1,
            0x12ec,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD23_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD23_DADDR",
            0,
            handles.bport1,
            0x12f0,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD23_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD23_DOFF_CITER",
            0,
            handles.bport1,
            0x12f4,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD23_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD23_DLASTSGA",
            0,
            handles.bport1,
            0x12f8,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD23_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD23_CSR_BITER",
            0,
            handles.bport1,
            0x12fc,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD23_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD24_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x1300,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD24_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD24_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x1304,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD24_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD24_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x1308,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD24_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD24_SLAST",
            0,
            handles.bport1,
            0x130c,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD24_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD24_DADDR",
            0,
            handles.bport1,
            0x1310,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD24_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD24_DOFF_CITER",
            0,
            handles.bport1,
            0x1314,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD24_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD24_DLASTSGA",
            0,
            handles.bport1,
            0x1318,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD24_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD24_CSR_BITER",
            0,
            handles.bport1,
            0x131c,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD24_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD25_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x1320,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD25_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD25_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x1324,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD25_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD25_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x1328,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD25_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD25_SLAST",
            0,
            handles.bport1,
            0x132c,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD25_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD25_DADDR",
            0,
            handles.bport1,
            0x1330,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD25_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD25_DOFF_CITER",
            0,
            handles.bport1,
            0x1334,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD25_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD25_DLASTSGA",
            0,
            handles.bport1,
            0x1338,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD25_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD25_CSR_BITER",
            0,
            handles.bport1,
            0x133c,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD25_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD26_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x1340,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD26_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD26_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x1344,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD26_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD26_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x1348,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD26_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD26_SLAST",
            0,
            handles.bport1,
            0x134c,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD26_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD26_DADDR",
            0,
            handles.bport1,
            0x1350,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD26_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD26_DOFF_CITER",
            0,
            handles.bport1,
            0x1354,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD26_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD26_DLASTSGA",
            0,
            handles.bport1,
            0x1358,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD26_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD26_CSR_BITER",
            0,
            handles.bport1,
            0x135c,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD26_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD27_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x1360,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD27_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD27_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x1364,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD27_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD27_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x1368,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD27_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD27_SLAST",
            0,
            handles.bport1,
            0x136c,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD27_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD27_DADDR",
            0,
            handles.bport1,
            0x1370,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD27_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD27_DOFF_CITER",
            0,
            handles.bport1,
            0x1374,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD27_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD27_DLASTSGA",
            0,
            handles.bport1,
            0x1378,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD27_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD27_CSR_BITER",
            0,
            handles.bport1,
            0x137c,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD27_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD28_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x1380,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD28_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD28_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x1384,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD28_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD28_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x1388,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD28_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD28_SLAST",
            0,
            handles.bport1,
            0x138c,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD28_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD28_DADDR",
            0,
            handles.bport1,
            0x1390,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD28_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD28_DOFF_CITER",
            0,
            handles.bport1,
            0x1394,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD28_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD28_DLASTSGA",
            0,
            handles.bport1,
            0x1398,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD28_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD28_CSR_BITER",
            0,
            handles.bport1,
            0x139c,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD28_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD29_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x13a0,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD29_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD29_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x13a4,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD29_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD29_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x13a8,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD29_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD29_SLAST",
            0,
            handles.bport1,
            0x13ac,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD29_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD29_DADDR",
            0,
            handles.bport1,
            0x13b0,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD29_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD29_DOFF_CITER",
            0,
            handles.bport1,
            0x13b4,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD29_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD29_DLASTSGA",
            0,
            handles.bport1,
            0x13b8,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD29_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD29_CSR_BITER",
            0,
            handles.bport1,
            0x13bc,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD29_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD30_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x13c0,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD30_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD30_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x13c4,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD30_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD30_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x13c8,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD30_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD30_SLAST",
            0,
            handles.bport1,
            0x13cc,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD30_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD30_DADDR",
            0,
            handles.bport1,
            0x13d0,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD30_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD30_DOFF_CITER",
            0,
            handles.bport1,
            0x13d4,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD30_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD30_DLASTSGA",
            0,
            handles.bport1,
            0x13d8,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD30_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD30_CSR_BITER",
            0,
            handles.bport1,
            0x13dc,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD30_CSR_BITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD31_SADDR",
            "TCD Source Address",
            handles.bport1,
            0x13e0,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD31_SADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD31_SOFF_ATTR",
            "TCD Signed Source Address Offset",
            handles.bport1,
            0x13e4,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD31_SOFF_ATTR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD31_NBYTES",
            "TCD Signed Minor Loop Offset, Minor Loop Disabled",
            handles.bport1,
            0x13e8,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD31_NBYTES.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD31_SLAST",
            0,
            handles.bport1,
            0x13ec,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD31_SLAST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD31_DADDR",
            0,
            handles.bport1,
            0x13f0,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD31_DADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD31_DOFF_CITER",
            0,
            handles.bport1,
            0x13f4,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD31_DOFF_CITER.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD31_DLASTSGA",
            0,
            handles.bport1,
            0x13f8,
            4,
            regReadTCD,
            regWriteTCD,
            view32,
            &(bport1_ab_data.TCD31_DLASTSGA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TCD31_CSR_BITER",
            0,
            handles.bport1,
            0x13fc,
            4,
            regReadTCD16,
            regWriteTCD16,
            view32,
            &(bport1_ab_data.TCD31_CSR_BITER.value),
            True
        );
    }

}

/////////////////////////////// Bus Master Ports ///////////////////////////////

static void installMasterPorts(void) {
    handles.MREAD = ppmOpenAddressSpace("MREAD");
    handles.MWRITE = ppmOpenAddressSpace("MWRITE");
}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.EARS.value = (Uns32)(bport1_ab_data.EARS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.HRS.value = (Uns32)(bport1_ab_data.HRS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ERR.value = (Uns32)(bport1_ab_data.ERR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.INT.value = (Uns32)(bport1_ab_data.INT.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.EEI.value = (Uns32)(bport1_ab_data.EEI.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ERQ.value = (Uns32)(bport1_ab_data.ERQ.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.ES.value = (Uns32)(bport1_ab_data.ES.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CR.value = (Uns32)(bport1_ab_data.CR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000400));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Freescale Vybrid Direct Memory Access Controller");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "Only models control register read/write - control register CX and ECX bits are modeled as RAZ/WI");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_22_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Freescale Vybrid Peripheral User Guide");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installMasterPorts();
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


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

TMSP0_reg0_dataT TMSP0_reg0_data;

TMSP0_reg1_dataT TMSP0_reg1_data;

TMSP0_reg2_dataT TMSP0_reg2_data;

TMSP0_reg3_dataT TMSP0_reg3_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "tms", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

static PPM_VIEW_CB(view16) {  *(Uns16*)data = *(Uns16*)user; }

static PPM_READ_CB(read_16) {  return *(Uns16*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.TMSP0 = ppmCreateSlaveBusPort("TMSP0", 42);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle reg0CTL0_reg = ppmCreateRegister(
            "reg0_CTL0",
            0,
            handles.TMSP0,
            0x0,
            1,
            read_8,
            writeCTL0,
            view8,
            &(TMSP0_reg0_data.CTL0.value),
            True
        );

        ppmCreateRegisterField(reg0CTL0_reg, "CKS", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(reg0CTL0_reg, "CE", 0, 7, 1, 1, 1);
    }
    {
        registerHandle reg0CTL1_reg = ppmCreateRegister(
            "reg0_CTL1",
            0,
            handles.TMSP0,
            0x1,
            1,
            read_8,
            writeCTL1,
            view8,
            &(TMSP0_reg0_data.CTL1.value),
            True
        );

        ppmCreateRegisterField(reg0CTL1_reg, "MD", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(reg0CTL1_reg, "EEE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(reg0CTL1_reg, "EST", 0, 6, 1, 1, 1);
    }
    {
        registerHandle reg1IOC0_reg = ppmCreateRegister(
            "reg1_IOC0",
            0,
            handles.TMSP0,
            0x2,
            2,
            readIOC0,
            writeIOC0,
            view16,
            &(TMSP0_reg1_data.IOC0.value),
            True
        );

        ppmCreateRegisterField(reg1IOC0_reg, "OE0", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(reg1IOC0_reg, "OL0", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(reg1IOC0_reg, "OE1", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(reg1IOC0_reg, "OL1", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(reg1IOC0_reg, "OE2", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(reg1IOC0_reg, "OL2", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(reg1IOC0_reg, "OE3", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IOC0_reg, "OL3", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IOC0_reg, "OE4", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(reg1IOC0_reg, "OL4", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(reg1IOC0_reg, "OE5", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(reg1IOC0_reg, "OL5", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(reg1IOC0_reg, "OE6", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(reg1IOC0_reg, "OL6", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(reg1IOC0_reg, "OE7", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(reg1IOC0_reg, "OL7", 0, 15, 1, 1, 1);
    }
    {
        registerHandle reg2IOC2_reg = ppmCreateRegister(
            "reg2_IOC2",
            0,
            handles.TMSP0,
            0x4,
            1,
            read_8,
            writeIOC2,
            view8,
            &(TMSP0_reg2_data.IOC2.value),
            True
        );

        ppmCreateRegisterField(reg2IOC2_reg, "ETS", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(reg2IOC2_reg, "EES", 0, 2, 2, 1, 1);
    }
    {
        registerHandle reg2IOC4_reg = ppmCreateRegister(
            "reg2_IOC4",
            0,
            handles.TMSP0,
            0x5,
            1,
            read_8,
            writeIOC4,
            view8,
            &(TMSP0_reg2_data.IOC4.value),
            True
        );

        ppmCreateRegisterField(reg2IOC4_reg, "EOC", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(reg2IOC4_reg, "WOC", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(reg2IOC4_reg, "BA", 0, 4, 3, 1, 1);
    }
    {
        registerHandle reg2OPT0_reg = ppmCreateRegister(
            "reg2_OPT0",
            0,
            handles.TMSP0,
            0x6,
            1,
            read_8,
            writeOPT0,
            view8,
            &(TMSP0_reg2_data.OPT0.value),
            True
        );

        ppmCreateRegisterField(reg2OPT0_reg, "OVF", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(reg2OPT0_reg, "CUF", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(reg2OPT0_reg, "CMS", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(reg2OPT0_reg, "DSE", 0, 3, 1, 1, 1);
    }
    {
        registerHandle reg2OPT4_reg = ppmCreateRegister(
            "reg2_OPT4",
            0,
            handles.TMSP0,
            0x8,
            1,
            read_8,
            writeOPT4,
            view8,
            &(TMSP0_reg2_data.OPT4.value),
            True
        );

        ppmCreateRegisterField(reg2OPT4_reg, "IPC", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(reg2OPT4_reg, "PSC", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(reg2OPT4_reg, "SOC", 0, 7, 1, 1, 1);
    }
    {
        registerHandle reg2OPT5_reg = ppmCreateRegister(
            "reg2_OPT5",
            0,
            handles.TMSP0,
            0x9,
            1,
            read_8,
            writeOPT5,
            view8,
            &(TMSP0_reg2_data.OPT5.value),
            True
        );

        ppmCreateRegisterField(reg2OPT5_reg, "OPF", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(reg2OPT5_reg, "TSF", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(reg2OPT5_reg, "PTS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(reg2OPT5_reg, "PSS", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(reg2OPT5_reg, "POT", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg2OPT5_reg, "ADC", 0, 7, 1, 1, 1);
    }
    {
        registerHandle reg2OPT7_reg = ppmCreateRegister(
            "reg2_OPT7",
            0,
            handles.TMSP0,
            0x7,
            1,
            read_8,
            writeOPT7,
            view8,
            &(TMSP0_reg2_data.OPT7.value),
            True
        );

        ppmCreateRegisterField(reg2OPT7_reg, "TOS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(reg2OPT7_reg, "PTC", 0, 1, 2, 1, 1);
        ppmCreateRegisterField(reg2OPT7_reg, "TDC", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(reg2OPT7_reg, "PPC", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(reg2OPT7_reg, "IDC", 0, 5, 1, 1, 1);
    }
    {
        registerHandle reg3OPT1_reg = ppmCreateRegister(
            "reg3_OPT1",
            0,
            handles.TMSP0,
            0xa,
            2,
            readOPT1,
            writeOPT1,
            view16,
            &(TMSP0_reg3_data.OPT1.value),
            True
        );

        ppmCreateRegisterField(reg3OPT1_reg, "ID", 0, 0, 5, 1, 1);
        ppmCreateRegisterField(reg3OPT1_reg, "RDE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT1_reg, "IOE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT1_reg, "ICE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT1_reg, "RBE", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT1_reg, "RTE", 0, 9, 1, 1, 1);
    }
    {
        registerHandle reg3OPT2_reg = ppmCreateRegister(
            "reg3_OPT2",
            0,
            handles.TMSP0,
            0x20,
            2,
            readOPT2,
            writeOPT2,
            view16,
            &(TMSP0_reg3_data.OPT2.value),
            True
        );

        ppmCreateRegisterField(reg3OPT2_reg, "AT00", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT2_reg, "AT01", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT2_reg, "AT02", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT2_reg, "AT03", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT2_reg, "AT04", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT2_reg, "AT05", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT2_reg, "AT06", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT2_reg, "AT07", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT2_reg, "ACC0", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT2_reg, "ACC1", 0, 9, 1, 1, 1);
    }
    {
        registerHandle reg3OPT3_reg = ppmCreateRegister(
            "reg3_OPT3",
            0,
            handles.TMSP0,
            0x22,
            2,
            readOPT3,
            writeOPT3,
            view16,
            &(TMSP0_reg3_data.OPT3.value),
            True
        );

        ppmCreateRegisterField(reg3OPT3_reg, "AT00", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT3_reg, "AT01", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT3_reg, "AT02", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT3_reg, "AT03", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT3_reg, "AT04", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT3_reg, "AT05", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT3_reg, "AT06", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT3_reg, "AT07", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT3_reg, "ACC2", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT3_reg, "ACC3", 0, 9, 1, 1, 1);
    }
    {
        registerHandle reg3OPT6_reg = ppmCreateRegister(
            "reg3_OPT6",
            0,
            handles.TMSP0,
            0x24,
            2,
            readOPT6,
            writeOPT6,
            view16,
            &(TMSP0_reg3_data.OPT6.value),
            True
        );

        ppmCreateRegisterField(reg3OPT6_reg, "RSF", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT6_reg, "SUF", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT6_reg, "TBF", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT6_reg, "PEF", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT6_reg, "PRF", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT6_reg, "NDF", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT6_reg, "TDF", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT6_reg, "PTF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg3OPT6_reg, "PPF", 0, 8, 1, 1, 1);
    }
    {
        registerHandle reg3DTC0_reg = ppmCreateRegister(
            "reg3_DTC0",
            0,
            handles.TMSP0,
            0xe,
            2,
            read_16,
            writeDTC0,
            view16,
            &(TMSP0_reg3_data.DTC0.value),
            True
        );

        ppmCreateRegisterField(reg3DTC0_reg, "DTV", 0, 1, 9, 1, 1);
    }
    {
        registerHandle reg3DTC1_reg = ppmCreateRegister(
            "reg3_DTC1",
            0,
            handles.TMSP0,
            0xc,
            2,
            read_16,
            writeDTC1,
            view16,
            &(TMSP0_reg3_data.DTC1.value),
            True
        );

        ppmCreateRegisterField(reg3DTC1_reg, "DTV", 0, 1, 9, 1, 1);
    }
    {
        registerHandle reg3PAT0_reg = ppmCreateRegister(
            "reg3_PAT0",
            0,
            handles.TMSP0,
            0x16,
            2,
            read_16,
            writePAT0,
            view16,
            &(TMSP0_reg3_data.PAT0.value),
            True
        );

        ppmCreateRegisterField(reg3PAT0_reg, "SP0", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(reg3PAT0_reg, "SP1", 0, 4, 4, 1, 1);
        ppmCreateRegisterField(reg3PAT0_reg, "SP2", 0, 8, 4, 1, 1);
        ppmCreateRegisterField(reg3PAT0_reg, "SP3", 0, 12, 4, 1, 1);
    }
    {
        registerHandle reg3PAT1_reg = ppmCreateRegister(
            "reg3_PAT1",
            0,
            handles.TMSP0,
            0x14,
            2,
            read_16,
            writePAT1,
            view16,
            &(TMSP0_reg3_data.PAT1.value),
            True
        );

        ppmCreateRegisterField(reg3PAT1_reg, "SP4", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(reg3PAT1_reg, "SP5", 0, 4, 4, 1, 1);
        ppmCreateRegisterField(reg3PAT1_reg, "SP6", 0, 8, 4, 1, 1);
        ppmCreateRegisterField(reg3PAT1_reg, "SP7", 0, 12, 4, 1, 1);
    }
    {
        ppmCreateRegister(
            "reg3_CCR0",
            0,
            handles.TMSP0,
            0x18,
            2,
            read_16,
            writeCCR0,
            view16,
            &(TMSP0_reg3_data.CCR0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg3_CCR1",
            0,
            handles.TMSP0,
            0x1e,
            2,
            read_16,
            writeCCR1,
            view16,
            &(TMSP0_reg3_data.CCR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg3_CCR2",
            0,
            handles.TMSP0,
            0x1c,
            2,
            read_16,
            writeCCR2,
            view16,
            &(TMSP0_reg3_data.CCR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg3_CCR3",
            0,
            handles.TMSP0,
            0x1a,
            2,
            read_16,
            writeCCR3,
            view16,
            &(TMSP0_reg3_data.CCR3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg3_CCR4",
            0,
            handles.TMSP0,
            0x12,
            2,
            read_16,
            writeCCR4,
            view16,
            &(TMSP0_reg3_data.CCR4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg3_CCR5",
            0,
            handles.TMSP0,
            0x10,
            2,
            read_16,
            writeCCR5,
            view16,
            &(TMSP0_reg3_data.CCR5.value),
            True
        );
    }
    {
        registerHandle reg3CNT_reg = ppmCreateRegister(
            "reg3_CNT",
            0,
            handles.TMSP0,
            0x26,
            2,
            readCNT,
            0,
            view16,
            &(TMSP0_reg3_data.CNT.value),
            True
        );

        ppmCreateRegisterField(reg3CNT_reg, "MODE", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(reg3CNT_reg, "VAL", 0, 1, 15, 1, 0);
    }
    {
        registerHandle reg3SBC_reg = ppmCreateRegister(
            "reg3_SBC",
            0,
            handles.TMSP0,
            0x28,
            2,
            readSBC,
            0,
            view16,
            &(TMSP0_reg3_data.SBC.value),
            True
        );

        ppmCreateRegisterField(reg3SBC_reg, "MODE", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(reg3SBC_reg, "SVAL", 0, 1, 15, 1, 0);
    }

}

PPM_NET_CB(reset_IRESET) {
    if(value != 0 ) {
        TMSP0_reg3_data.SBC.value = (Uns16)(TMSP0_reg3_data.SBC.value & ~(0xffff)) | ((0xffff) & (0x0000));
        TMSP0_reg3_data.CNT.value = (Uns16)(TMSP0_reg3_data.CNT.value & ~(0xffff)) | ((0xffff) & (0x0000));
        TMSP0_reg3_data.CCR5.value = (Uns16)(TMSP0_reg3_data.CCR5.value & ~(0xffff)) | ((0xffff) & (0x0000));
        TMSP0_reg3_data.CCR4.value = (Uns16)(TMSP0_reg3_data.CCR4.value & ~(0xffff)) | ((0xffff) & (0x0000));
        TMSP0_reg3_data.CCR3.value = (Uns16)(TMSP0_reg3_data.CCR3.value & ~(0xffff)) | ((0xffff) & (0x0000));
        TMSP0_reg3_data.CCR2.value = (Uns16)(TMSP0_reg3_data.CCR2.value & ~(0xffff)) | ((0xffff) & (0x0000));
        TMSP0_reg3_data.CCR1.value = (Uns16)(TMSP0_reg3_data.CCR1.value & ~(0xffff)) | ((0xffff) & (0x0000));
        TMSP0_reg3_data.CCR0.value = (Uns16)(TMSP0_reg3_data.CCR0.value & ~(0xffff)) | ((0xffff) & (0x0000));
        TMSP0_reg3_data.PAT1.value = (Uns16)(TMSP0_reg3_data.PAT1.value & ~(0xffff)) | ((0xffff) & (0x0000));
        TMSP0_reg3_data.PAT0.value = (Uns16)(TMSP0_reg3_data.PAT0.value & ~(0xffff)) | ((0xffff) & (0x0000));
        TMSP0_reg3_data.DTC1.value = (Uns16)(TMSP0_reg3_data.DTC1.value & ~(0xffff)) | ((0xffff) & (0x0000));
        TMSP0_reg3_data.DTC0.value = (Uns16)(TMSP0_reg3_data.DTC0.value & ~(0xffff)) | ((0xffff) & (0x0000));
        TMSP0_reg3_data.OPT6.value = (Uns16)(TMSP0_reg3_data.OPT6.value & ~(0xffff)) | ((0xffff) & (0x0000));
        TMSP0_reg3_data.OPT3.value = (Uns16)(TMSP0_reg3_data.OPT3.value & ~(0xffff)) | ((0xffff) & (0x0000));
        TMSP0_reg3_data.OPT2.value = (Uns16)(TMSP0_reg3_data.OPT2.value & ~(0xffff)) | ((0xffff) & (0x0000));
        TMSP0_reg2_data.OPT7.value = (Uns8)(TMSP0_reg2_data.OPT7.value & ~(0xff)) | ((0xff) & (0x00));
        TMSP0_reg2_data.OPT5.value = (Uns8)(TMSP0_reg2_data.OPT5.value & ~(0xff)) | ((0xff) & (0x00));
        TMSP0_reg2_data.OPT4.value = (Uns8)(TMSP0_reg2_data.OPT4.value & ~(0xff)) | ((0xff) & (0x00));
        TMSP0_reg2_data.OPT0.value = (Uns8)(TMSP0_reg2_data.OPT0.value & ~(0xff)) | ((0xff) & (0x00));
        TMSP0_reg2_data.IOC4.value = (Uns8)(TMSP0_reg2_data.IOC4.value & ~(0xff)) | ((0xff) & (0x00));
        TMSP0_reg2_data.IOC2.value = (Uns8)(TMSP0_reg2_data.IOC2.value & ~(0xff)) | ((0xff) & (0x00));
        TMSP0_reg1_data.IOC0.value = (Uns16)(TMSP0_reg1_data.IOC0.value & ~(0xffff)) | ((0xffff) & (0x0000));
        TMSP0_reg0_data.CTL1.value = (Uns8)(TMSP0_reg0_data.CTL1.value & ~(0xff)) | ((0xff) & (0x00));
        TMSP0_reg0_data.CTL0.value = (Uns8)(TMSP0_reg0_data.CTL0.value & ~(0xff)) | ((0xff) & (0x00));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Renesas TMS Timer/Event Counter S");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Status of Modes\n- Interval Timer Mode                  - Supported\n- External Event Count Mode            - Untested\n- External Trigger Pulse Output Mode   - Unsupported\n- One-Shot Pulse Mode                  - Unsupported\n- PWM Mode                             - Unsupported\n- Free-Running Mode                    - Supported\n- Triangular-Wave PWM Mode             - Unsupported\n- High Accuracy T-PWM Mode             - Unsupported\n- PWM Mode with Dead Time              - Unsupported\n- 120Deg Excitation Mode               - Unsupported\n- Special 120Deg Excitation Mode       - Unsupported\n- Special Pattern Output Mode          - Unsupported\n");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    reset_IRESET(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}


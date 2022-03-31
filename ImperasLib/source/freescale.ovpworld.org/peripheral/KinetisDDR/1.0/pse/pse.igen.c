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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisDDR", "Example");
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
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abCR00_reg = ppmCreateRegister(
            "ab_CR00",
            "DDR Control Register 0, offset: 0x0 ",
            handles.bport1,
            0x0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR00.value),
            True
        );

        ppmCreateRegisterField(abCR00_reg, "DDRCLS", 0, 8, 4, 1, 1);
        ppmCreateRegisterField(abCR00_reg, "START", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abCR00_reg, "VERSION", 0, 16, 16, 1, 1);
    }
    {
        registerHandle abCR01_reg = ppmCreateRegister(
            "ab_CR01",
            "DDR Control Register 1, offset: 0x4 ",
            handles.bport1,
            0x4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR01.value),
            True
        );

        ppmCreateRegisterField(abCR01_reg, "CSMAX", 0, 16, 2, 1, 1);
        ppmCreateRegisterField(abCR01_reg, "MAXCOL", 0, 8, 4, 1, 1);
        ppmCreateRegisterField(abCR01_reg, "MAXROW", 0, 0, 5, 1, 1);
    }
    {
        registerHandle abCR02_reg = ppmCreateRegister(
            "ab_CR02",
            "DDR Control Register 2, offset: 0x8 ",
            handles.bport1,
            0x8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR02.value),
            True
        );

        ppmCreateRegisterField(abCR02_reg, "INITAREF", 0, 24, 4, 1, 1);
        ppmCreateRegisterField(abCR02_reg, "TINIT", 0, 0, 24, 1, 1);
    }
    {
        registerHandle abCR03_reg = ppmCreateRegister(
            "ab_CR03",
            "DDR Control Register 3, offset: 0xC ",
            handles.bport1,
            0xc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR03.value),
            True
        );

        ppmCreateRegisterField(abCR03_reg, "LATGATE", 0, 8, 4, 1, 1);
        ppmCreateRegisterField(abCR03_reg, "LATLIN", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(abCR03_reg, "TCCD", 0, 24, 5, 1, 1);
        ppmCreateRegisterField(abCR03_reg, "WRLAT", 0, 16, 4, 1, 1);
    }
    {
        registerHandle abCR04_reg = ppmCreateRegister(
            "ab_CR04",
            "DDR Control Register 4, offset: 0x10 ",
            handles.bport1,
            0x10,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR04.value),
            True
        );

        ppmCreateRegisterField(abCR04_reg, "TBINT", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abCR04_reg, "TRASMIN", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abCR04_reg, "TRC", 0, 16, 6, 1, 1);
        ppmCreateRegisterField(abCR04_reg, "TRRD", 0, 8, 3, 1, 1);
    }
    {
        registerHandle abCR05_reg = ppmCreateRegister(
            "ab_CR05",
            "DDR Control Register 5, offset: 0x14 ",
            handles.bport1,
            0x14,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR05.value),
            True
        );

        ppmCreateRegisterField(abCR05_reg, "TMRD", 0, 24, 5, 1, 1);
        ppmCreateRegisterField(abCR05_reg, "TRP", 0, 8, 4, 1, 1);
        ppmCreateRegisterField(abCR05_reg, "TRTP", 0, 16, 3, 1, 1);
        ppmCreateRegisterField(abCR05_reg, "TWTR", 0, 0, 4, 1, 1);
    }
    {
        registerHandle abCR06_reg = ppmCreateRegister(
            "ab_CR06",
            "DDR Control Register 6, offset: 0x18 ",
            handles.bport1,
            0x18,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR06.value),
            True
        );

        ppmCreateRegisterField(abCR06_reg, "INTWBR", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abCR06_reg, "TMOD", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abCR06_reg, "TRASMAX", 0, 8, 16, 1, 1);
    }
    {
        registerHandle abCR07_reg = ppmCreateRegister(
            "ab_CR07",
            "DDR Control Register 7, offset: 0x1C ",
            handles.bport1,
            0x1c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR07.value),
            True
        );

        ppmCreateRegisterField(abCR07_reg, "AP", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abCR07_reg, "CCAPEN", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abCR07_reg, "CLKPW", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abCR07_reg, "TCKESR", 0, 8, 5, 1, 1);
    }
    {
        registerHandle abCR08_reg = ppmCreateRegister(
            "ab_CR08",
            "DDR Control Register 8, offset: 0x20 ",
            handles.bport1,
            0x20,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR08.value),
            True
        );

        ppmCreateRegisterField(abCR08_reg, "TDAL", 0, 24, 5, 1, 1);
        ppmCreateRegisterField(abCR08_reg, "TRAS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abCR08_reg, "TRASDI", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abCR08_reg, "TWR", 0, 16, 5, 1, 1);
    }
    {
        registerHandle abCR09_reg = ppmCreateRegister(
            "ab_CR09",
            "DDR Control Register 9, offset: 0x24 ",
            handles.bport1,
            0x24,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR09.value),
            True
        );

        ppmCreateRegisterField(abCR09_reg, "BSTLEN", 0, 24, 3, 1, 1);
        ppmCreateRegisterField(abCR09_reg, "NOCMD", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abCR09_reg, "TDLL", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abCR10_reg = ppmCreateRegister(
            "ab_CR10",
            "DDR Control Register 10, offset: 0x28 ",
            handles.bport1,
            0x28,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR10.value),
            True
        );

        ppmCreateRegisterField(abCR10_reg, "TCPD", 0, 8, 16, 1, 1);
        ppmCreateRegisterField(abCR10_reg, "TFAW", 0, 0, 6, 1, 1);
        ppmCreateRegisterField(abCR10_reg, "TRPAB", 0, 24, 4, 1, 1);
    }
    {
        registerHandle abCR11_reg = ppmCreateRegister(
            "ab_CR11",
            "DDR Control Register 11, offset: 0x2C ",
            handles.bport1,
            0x2c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR11.value),
            True
        );

        ppmCreateRegisterField(abCR11_reg, "AREF", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abCR11_reg, "AREFMODE", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abCR11_reg, "REGDIMM", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abCR11_reg, "TREFEN", 0, 24, 1, 1, 1);
    }
    {
        registerHandle abCR12_reg = ppmCreateRegister(
            "ab_CR12",
            "DDR Control Register 12, offset: 0x30 ",
            handles.bport1,
            0x30,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR12.value),
            True
        );

        ppmCreateRegisterField(abCR12_reg, "TREF", 0, 16, 14, 1, 1);
        ppmCreateRegisterField(abCR12_reg, "TRFC", 0, 0, 10, 1, 1);
    }
    {
        registerHandle abCR13_reg = ppmCreateRegister(
            "ab_CR13",
            "DDR Control Register 13, offset: 0x34 ",
            handles.bport1,
            0x34,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR13.value),
            True
        );

        ppmCreateRegisterField(abCR13_reg, "PD", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abCR13_reg, "TREFINT", 0, 0, 14, 1, 1);
    }
    {
        registerHandle abCR14_reg = ppmCreateRegister(
            "ab_CR14",
            "DDR Control Register 14, offset: 0x38 ",
            handles.bport1,
            0x38,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR14.value),
            True
        );

        ppmCreateRegisterField(abCR14_reg, "TPDEX", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(abCR14_reg, "TXSR", 0, 16, 16, 1, 1);
    }
    {
        registerHandle abCR15_reg = ppmCreateRegister(
            "ab_CR15",
            "DDR Control Register 15, offset: 0x3C ",
            handles.bport1,
            0x3c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR15.value),
            True
        );

        ppmCreateRegisterField(abCR15_reg, "PUREF", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abCR15_reg, "SREF", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abCR15_reg, "TXSNR", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abCR16_reg = ppmCreateRegister(
            "ab_CR16",
            "DDR Control Register 16, offset: 0x40 ",
            handles.bport1,
            0x40,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR16.value),
            True
        );

        ppmCreateRegisterField(abCR16_reg, "CLKDLY", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abCR16_reg, "LPCTRL", 0, 16, 5, 1, 1);
        ppmCreateRegisterField(abCR16_reg, "QKREF", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abCR17_reg = ppmCreateRegister(
            "ab_CR17",
            "DDR Control Register 17, offset: 0x44 ",
            handles.bport1,
            0x44,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR17.value),
            True
        );

        ppmCreateRegisterField(abCR17_reg, "LPPDCNT", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(abCR17_reg, "LPRFCNT", 0, 16, 16, 1, 1);
    }
    {
        registerHandle abCR18_reg = ppmCreateRegister(
            "ab_CR18",
            "DDR Control Register 18, offset: 0x48 ",
            handles.bport1,
            0x48,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR18.value),
            True
        );

        ppmCreateRegisterField(abCR18_reg, "LPAUTO", 0, 16, 5, 1, 1);
        ppmCreateRegisterField(abCR18_reg, "LPEXTCNT", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abCR19_reg = ppmCreateRegister(
            "ab_CR19",
            "DDR Control Register 19, offset: 0x4C ",
            handles.bport1,
            0x4c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR19.value),
            True
        );

        ppmCreateRegisterField(abCR19_reg, "LPINTCNT", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(abCR19_reg, "LPRFHOLD", 0, 16, 16, 1, 1);
    }
    {
        registerHandle abCR20_reg = ppmCreateRegister(
            "ab_CR20",
            "DDR Control Register 20, offset: 0x50 ",
            handles.bport1,
            0x50,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR20.value),
            True
        );

        ppmCreateRegisterField(abCR20_reg, "CKSRE", 0, 8, 4, 1, 1);
        ppmCreateRegisterField(abCR20_reg, "CKSRX", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abCR20_reg, "LPRE", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(abCR20_reg, "WRMD", 0, 24, 1, 1, 1);
    }
    {
        registerHandle abCR21_reg = ppmCreateRegister(
            "ab_CR21",
            "DDR Control Register 21, offset: 0x54 ",
            handles.bport1,
            0x54,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR21.value),
            True
        );

        ppmCreateRegisterField(abCR21_reg, "MR0DAT0", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(abCR21_reg, "MR1DAT0", 0, 16, 16, 1, 1);
    }
    {
        registerHandle abCR22_reg = ppmCreateRegister(
            "ab_CR22",
            "DDR Control Register 22, offset: 0x58 ",
            handles.bport1,
            0x58,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR22.value),
            True
        );

        ppmCreateRegisterField(abCR22_reg, "MR2DATA0", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(abCR22_reg, "MR3DAT0", 0, 16, 16, 1, 1);
    }
    {
        registerHandle abCR23_reg = ppmCreateRegister(
            "ab_CR23",
            "DDR Control Register 23, offset: 0x5C ",
            handles.bport1,
            0x5c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR23.value),
            True
        );

        ppmCreateRegisterField(abCR23_reg, "NOT_USED2", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(abCR23_reg, "NOT_USED", 0, 16, 16, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_CR24",
            "DDR Control Register 24, offset: 0x60 ",
            handles.bport1,
            0x60,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR24.value),
            True
        );
    }
    {
        registerHandle abCR25_reg = ppmCreateRegister(
            "ab_CR25",
            "DDR Control Register 25, offset: 0x64 ",
            handles.bport1,
            0x64,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR25.value),
            True
        );

        ppmCreateRegisterField(abCR25_reg, "ADDPINS", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abCR25_reg, "APREBIT", 0, 24, 4, 1, 1);
        ppmCreateRegisterField(abCR25_reg, "BNK8", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abCR25_reg, "COLSIZ", 0, 16, 3, 1, 1);
    }
    {
        registerHandle abCR26_reg = ppmCreateRegister(
            "ab_CR26",
            "DDR Control Register 26, offset: 0x68 ",
            handles.bport1,
            0x68,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR26.value),
            True
        );

        ppmCreateRegisterField(abCR26_reg, "ADDCOL", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abCR26_reg, "AGECNT", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abCR26_reg, "BNKSPT", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abCR26_reg, "CMDAGE", 0, 8, 8, 1, 1);
    }
    {
        registerHandle abCR27_reg = ppmCreateRegister(
            "ab_CR27",
            "DDR Control Register 27, offset: 0x6C ",
            handles.bport1,
            0x6c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR27.value),
            True
        );

        ppmCreateRegisterField(abCR27_reg, "PLEN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abCR27_reg, "PRIEN", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abCR27_reg, "RWEN", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abCR27_reg, "SWPEN", 0, 24, 1, 1, 1);
    }
    {
        registerHandle abCR28_reg = ppmCreateRegister(
            "ab_CR28",
            "DDR Control Register 28, offset: 0x70 ",
            handles.bport1,
            0x70,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR28.value),
            True
        );

        ppmCreateRegisterField(abCR28_reg, "BIGEND", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abCR28_reg, "CMDLATR", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abCR28_reg, "CSMAP", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abCR28_reg, "REDUC", 0, 8, 1, 1, 1);
    }
    {
        registerHandle abCR29_reg = ppmCreateRegister(
            "ab_CR29",
            "DDR Control Register 29, offset: 0x74 ",
            handles.bport1,
            0x74,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR29.value),
            True
        );

        ppmCreateRegisterField(abCR29_reg, "FSTWR", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abCR29_reg, "QFULL", 0, 16, 2, 1, 1);
        ppmCreateRegisterField(abCR29_reg, "RESYNC", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abCR29_reg, "WRLATR", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abCR30_reg = ppmCreateRegister(
            "ab_CR30",
            "DDR Control Register 30, offset: 0x78 ",
            handles.bport1,
            0x78,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR30.value),
            True
        );

        ppmCreateRegisterField(abCR30_reg, "INTACK", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abCR30_reg, "INTSTAT", 0, 8, 9, 1, 1);
        ppmCreateRegisterField(abCR30_reg, "RSYNCRF", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abCR31_reg = ppmCreateRegister(
            "ab_CR31",
            "DDR Control Register 31, offset: 0x7C ",
            handles.bport1,
            0x7c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR31.value),
            True
        );

        ppmCreateRegisterField(abCR31_reg, "INTMASK", 0, 0, 9, 1, 1);
    }
    {
        registerHandle abCR32_reg = ppmCreateRegister(
            "ab_CR32",
            "DDR Control Register 32, offset: 0x80 ",
            handles.bport1,
            0x80,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR32.value),
            True
        );

        ppmCreateRegisterField(abCR32_reg, "OORAD", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abCR33_reg = ppmCreateRegister(
            "ab_CR33",
            "DDR Control Register 33, offset: 0x84 ",
            handles.bport1,
            0x84,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR33.value),
            True
        );

        ppmCreateRegisterField(abCR33_reg, "OORID", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abCR33_reg, "OORLEN", 0, 0, 10, 1, 1);
        ppmCreateRegisterField(abCR33_reg, "OORTYP", 0, 16, 6, 1, 1);
    }
    {
        registerHandle abCR34_reg = ppmCreateRegister(
            "ab_CR34",
            "DDR Control Register 34, offset: 0x88 ",
            handles.bport1,
            0x88,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR34.value),
            True
        );

        ppmCreateRegisterField(abCR34_reg, "ODTRDC", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abCR34_reg, "ODTWRCS", 0, 8, 1, 1, 1);
    }
    {
        registerHandle abCR35_reg = ppmCreateRegister(
            "ab_CR35",
            "DDR Control Register 35, offset: 0x8C ",
            handles.bport1,
            0x8c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR35.value),
            True
        );

        ppmCreateRegisterField(abCR35_reg, "R2WSMCS", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(abCR35_reg, "W2RSMCS", 0, 8, 4, 1, 1);
    }
    {
        registerHandle abCR36_reg = ppmCreateRegister(
            "ab_CR36",
            "DDR Control Register 36, offset: 0x90 ",
            handles.bport1,
            0x90,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR36.value),
            True
        );

        ppmCreateRegisterField(abCR36_reg, "NOT_USED2", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(abCR36_reg, "NOT_USED", 0, 16, 16, 1, 1);
    }
    {
        registerHandle abCR37_reg = ppmCreateRegister(
            "ab_CR37",
            "DDR Control Register 37, offset: 0x94 ",
            handles.bport1,
            0x94,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR37.value),
            True
        );

        ppmCreateRegisterField(abCR37_reg, "R2RSAME", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(abCR37_reg, "R2WSAME", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abCR37_reg, "W2RSAME", 0, 16, 3, 1, 1);
        ppmCreateRegisterField(abCR37_reg, "W2WSAME", 0, 24, 3, 1, 1);
    }
    {
        registerHandle abCR38_reg = ppmCreateRegister(
            "ab_CR38",
            "DDR Control Register 38, offset: 0x98 ",
            handles.bport1,
            0x98,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR38.value),
            True
        );

        ppmCreateRegisterField(abCR38_reg, "PDNCS", 0, 0, 5, 1, 1);
        ppmCreateRegisterField(abCR38_reg, "PUPCS", 0, 8, 5, 1, 1);
        ppmCreateRegisterField(abCR38_reg, "PWRCNT", 0, 16, 11, 1, 1);
    }
    {
        registerHandle abCR39_reg = ppmCreateRegister(
            "ab_CR39",
            "DDR Control Register 39, offset: 0x9C ",
            handles.bport1,
            0x9c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR39.value),
            True
        );

        ppmCreateRegisterField(abCR39_reg, "P0RDCNT", 0, 0, 11, 1, 1);
        ppmCreateRegisterField(abCR39_reg, "RP0", 0, 16, 2, 1, 1);
        ppmCreateRegisterField(abCR39_reg, "WP0", 0, 24, 2, 1, 1);
    }
    {
        registerHandle abCR40_reg = ppmCreateRegister(
            "ab_CR40",
            "DDR Control Register 40, offset: 0xA0 ",
            handles.bport1,
            0xa0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR40.value),
            True
        );

        ppmCreateRegisterField(abCR40_reg, "P0TYP", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(abCR40_reg, "P1WRCNT", 0, 8, 11, 1, 1);
    }
    {
        registerHandle abCR41_reg = ppmCreateRegister(
            "ab_CR41",
            "DDR Control Register 41, offset: 0xA4 ",
            handles.bport1,
            0xa4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR41.value),
            True
        );

        ppmCreateRegisterField(abCR41_reg, "P1RDCNT", 0, 0, 11, 1, 1);
        ppmCreateRegisterField(abCR41_reg, "RP1", 0, 16, 2, 1, 1);
        ppmCreateRegisterField(abCR41_reg, "WP1", 0, 24, 2, 1, 1);
    }
    {
        registerHandle abCR42_reg = ppmCreateRegister(
            "ab_CR42",
            "DDR Control Register 42, offset: 0xA8 ",
            handles.bport1,
            0xa8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR42.value),
            True
        );

        ppmCreateRegisterField(abCR42_reg, "P1TYP", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(abCR42_reg, "P2WRCNT", 0, 8, 11, 1, 1);
    }
    {
        registerHandle abCR43_reg = ppmCreateRegister(
            "ab_CR43",
            "DDR Control Register 43, offset: 0xAC ",
            handles.bport1,
            0xac,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR43.value),
            True
        );

        ppmCreateRegisterField(abCR43_reg, "P2RDCNT", 0, 0, 11, 1, 1);
        ppmCreateRegisterField(abCR43_reg, "RP2", 0, 16, 2, 1, 1);
        ppmCreateRegisterField(abCR43_reg, "WP2", 0, 24, 2, 1, 1);
    }
    {
        registerHandle abCR44_reg = ppmCreateRegister(
            "ab_CR44",
            "DDR Control Register 44, offset: 0xB0 ",
            handles.bport1,
            0xb0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR44.value),
            True
        );

        ppmCreateRegisterField(abCR44_reg, "P2TYP", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(abCR44_reg, "WRRERR", 0, 24, 4, 1, 1);
        ppmCreateRegisterField(abCR44_reg, "WRRLAT", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abCR44_reg, "WRRSHARE", 0, 16, 1, 1, 1);
    }
    {
        registerHandle abCR45_reg = ppmCreateRegister(
            "ab_CR45",
            "DDR Control Register 45, offset: 0xB4 ",
            handles.bport1,
            0xb4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR45.value),
            True
        );

        ppmCreateRegisterField(abCR45_reg, "P0PRI0", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(abCR45_reg, "P0PRI1", 0, 8, 4, 1, 1);
        ppmCreateRegisterField(abCR45_reg, "P0PRI2", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abCR45_reg, "P0PRI3", 0, 24, 4, 1, 1);
    }
    {
        registerHandle abCR46_reg = ppmCreateRegister(
            "ab_CR46",
            "DDR Control Register 46, offset: 0xB8 ",
            handles.bport1,
            0xb8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR46.value),
            True
        );

        ppmCreateRegisterField(abCR46_reg, "P0ORD", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(abCR46_reg, "P0PRIRLX", 0, 8, 10, 1, 1);
        ppmCreateRegisterField(abCR46_reg, "P1PRI0", 0, 24, 4, 1, 1);
    }
    {
        registerHandle abCR47_reg = ppmCreateRegister(
            "ab_CR47",
            "DDR Control Register 47, offset: 0xBC ",
            handles.bport1,
            0xbc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR47.value),
            True
        );

        ppmCreateRegisterField(abCR47_reg, "P1ORD", 0, 24, 2, 1, 1);
        ppmCreateRegisterField(abCR47_reg, "P1PRI1", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(abCR47_reg, "P1PRI2", 0, 8, 4, 1, 1);
        ppmCreateRegisterField(abCR47_reg, "P1PRI3", 0, 16, 4, 1, 1);
    }
    {
        registerHandle abCR48_reg = ppmCreateRegister(
            "ab_CR48",
            "DDR Control Register 48, offset: 0xC0 ",
            handles.bport1,
            0xc0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR48.value),
            True
        );

        ppmCreateRegisterField(abCR48_reg, "P1PRIRLX", 0, 0, 10, 1, 1);
        ppmCreateRegisterField(abCR48_reg, "P2PRI0", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abCR48_reg, "P2PRI1", 0, 24, 4, 1, 1);
    }
    {
        registerHandle abCR49_reg = ppmCreateRegister(
            "ab_CR49",
            "DDR Control Register 49, offset: 0xC4 ",
            handles.bport1,
            0xc4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR49.value),
            True
        );

        ppmCreateRegisterField(abCR49_reg, "P2ORD", 0, 16, 2, 1, 1);
        ppmCreateRegisterField(abCR49_reg, "P2PRI2", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(abCR49_reg, "P2PRI3", 0, 8, 4, 1, 1);
    }
    {
        registerHandle abCR50_reg = ppmCreateRegister(
            "ab_CR50",
            "DDR Control Register 50, offset: 0xC8 ",
            handles.bport1,
            0xc8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR50.value),
            True
        );

        ppmCreateRegisterField(abCR50_reg, "CLKSTATUS", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abCR50_reg, "P2PRIRLX", 0, 0, 10, 1, 1);
    }
    {
        registerHandle abCR51_reg = ppmCreateRegister(
            "ab_CR51",
            "DDR Control Register 51, offset: 0xCC ",
            handles.bport1,
            0xcc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR51.value),
            True
        );

        ppmCreateRegisterField(abCR51_reg, "DLLRADLY", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abCR51_reg, "DLLRSTDLY", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(abCR51_reg, "PHYWRLAT", 0, 24, 4, 1, 1);
    }
    {
        registerHandle abCR52_reg = ppmCreateRegister(
            "ab_CR52",
            "DDR Control Register 52, offset: 0xD0 ",
            handles.bport1,
            0xd0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR52.value),
            True
        );

        ppmCreateRegisterField(abCR52_reg, "PHYRDLAT", 0, 8, 4, 1, 1);
        ppmCreateRegisterField(abCR52_reg, "PYWRLTBS", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(abCR52_reg, "RDDATAEN", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abCR52_reg, "RDDTENBAS", 0, 24, 4, 1, 1);
    }
    {
        registerHandle abCR53_reg = ppmCreateRegister(
            "ab_CR53",
            "DDR Control Register 53, offset: 0xD4 ",
            handles.bport1,
            0xd4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR53.value),
            True
        );

        ppmCreateRegisterField(abCR53_reg, "CLKDISCS", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abCR53_reg, "CRTLUPDMN", 0, 8, 4, 1, 1);
        ppmCreateRegisterField(abCR53_reg, "CTRLUPDMX", 0, 16, 14, 1, 1);
    }
    {
        registerHandle abCR54_reg = ppmCreateRegister(
            "ab_CR54",
            "DDR Control Register 54, offset: 0xD8 ",
            handles.bport1,
            0xd8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR54.value),
            True
        );

        ppmCreateRegisterField(abCR54_reg, "PHYUPDTY0", 0, 0, 14, 1, 1);
        ppmCreateRegisterField(abCR54_reg, "PHYUPDTY1", 0, 16, 14, 1, 1);
    }
    {
        registerHandle abCR55_reg = ppmCreateRegister(
            "ab_CR55",
            "DDR Control Register 55, offset: 0xDC ",
            handles.bport1,
            0xdc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR55.value),
            True
        );

        ppmCreateRegisterField(abCR55_reg, "PHYUPDTY2", 0, 0, 14, 1, 1);
        ppmCreateRegisterField(abCR55_reg, "PHYUPDTY3", 0, 16, 14, 1, 1);
    }
    {
        registerHandle abCR56_reg = ppmCreateRegister(
            "ab_CR56",
            "DDR Control Register 56, offset: 0xE0 ",
            handles.bport1,
            0xe0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR56.value),
            True
        );

        ppmCreateRegisterField(abCR56_reg, "PHYUPDRESP", 0, 0, 14, 1, 1);
        ppmCreateRegisterField(abCR56_reg, "RDLATADJ", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abCR56_reg, "WRLATADJ", 0, 24, 4, 1, 1);
    }
    {
        registerHandle abCR57_reg = ppmCreateRegister(
            "ab_CR57",
            "DDR Control Register 57, offset: 0xE4 ",
            handles.bport1,
            0xe4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR57.value),
            True
        );

        ppmCreateRegisterField(abCR57_reg, "CLKDISDLY", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abCR57_reg, "CLKENDLY", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abCR57_reg, "CMDDLY", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(abCR57_reg, "ODTALTEN", 0, 24, 1, 1, 1);
    }
    {
        registerHandle abCR58_reg = ppmCreateRegister(
            "ab_CR58",
            "DDR Control Register 58, offset: 0xE8 ",
            handles.bport1,
            0xe8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR58.value),
            True
        );

        ppmCreateRegisterField(abCR58_reg, "NOT_USED2", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(abCR58_reg, "NOT_USED", 0, 16, 16, 1, 1);
    }
    {
        registerHandle abCR59_reg = ppmCreateRegister(
            "ab_CR59",
            "DDR Control Register 59, offset: 0xEC ",
            handles.bport1,
            0xec,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR59.value),
            True
        );

        ppmCreateRegisterField(abCR59_reg, "NOT_USED2", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(abCR59_reg, "NOT_USED", 0, 16, 16, 1, 1);
    }
    {
        registerHandle abCR60_reg = ppmCreateRegister(
            "ab_CR60",
            "DDR Control Register 60, offset: 0xF0 ",
            handles.bport1,
            0xf0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR60.value),
            True
        );

        ppmCreateRegisterField(abCR60_reg, "NOT_USED2", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(abCR60_reg, "NOT_USED", 0, 16, 16, 1, 1);
    }
    {
        registerHandle abCR61_reg = ppmCreateRegister(
            "ab_CR61",
            "DDR Control Register 61, offset: 0xF4 ",
            handles.bport1,
            0xf4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR61.value),
            True
        );

        ppmCreateRegisterField(abCR61_reg, "NOT_USED2", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(abCR61_reg, "NOT_USED", 0, 16, 16, 1, 1);
    }
    {
        registerHandle abCR62_reg = ppmCreateRegister(
            "ab_CR62",
            "DDR Control Register 62, offset: 0xF8 ",
            handles.bport1,
            0xf8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR62.value),
            True
        );

        ppmCreateRegisterField(abCR62_reg, "NOT_USED2", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(abCR62_reg, "NOT_USED", 0, 16, 16, 1, 1);
    }
    {
        registerHandle abCR63_reg = ppmCreateRegister(
            "ab_CR63",
            "DDR Control Register 63, offset: 0xFC ",
            handles.bport1,
            0xfc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CR63.value),
            True
        );

        ppmCreateRegisterField(abCR63_reg, "NOT_USED2", 0, 0, 16, 1, 1);
        ppmCreateRegisterField(abCR63_reg, "NOT_USED", 0, 16, 16, 1, 1);
    }
    {
        registerHandle abRCR_reg = ppmCreateRegister(
            "ab_RCR",
            "RCR Control Register, offset: 0x180 ",
            handles.bport1,
            0x180,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.RCR.value),
            True
        );

        ppmCreateRegisterField(abRCR_reg, "RST", 0, 30, 1, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.RCR.value = (Uns32)(bport1_ab_data.RCR.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR63.value = (Uns32)(bport1_ab_data.CR63.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR62.value = (Uns32)(bport1_ab_data.CR62.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR61.value = (Uns32)(bport1_ab_data.CR61.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR60.value = (Uns32)(bport1_ab_data.CR60.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR59.value = (Uns32)(bport1_ab_data.CR59.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR58.value = (Uns32)(bport1_ab_data.CR58.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR57.value = (Uns32)(bport1_ab_data.CR57.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR56.value = (Uns32)(bport1_ab_data.CR56.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR55.value = (Uns32)(bport1_ab_data.CR55.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR54.value = (Uns32)(bport1_ab_data.CR54.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR53.value = (Uns32)(bport1_ab_data.CR53.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR52.value = (Uns32)(bport1_ab_data.CR52.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR51.value = (Uns32)(bport1_ab_data.CR51.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR50.value = (Uns32)(bport1_ab_data.CR50.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR49.value = (Uns32)(bport1_ab_data.CR49.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR48.value = (Uns32)(bport1_ab_data.CR48.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR47.value = (Uns32)(bport1_ab_data.CR47.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR46.value = (Uns32)(bport1_ab_data.CR46.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR45.value = (Uns32)(bport1_ab_data.CR45.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR44.value = (Uns32)(bport1_ab_data.CR44.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR43.value = (Uns32)(bport1_ab_data.CR43.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR42.value = (Uns32)(bport1_ab_data.CR42.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR41.value = (Uns32)(bport1_ab_data.CR41.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR40.value = (Uns32)(bport1_ab_data.CR40.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR39.value = (Uns32)(bport1_ab_data.CR39.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR38.value = (Uns32)(bport1_ab_data.CR38.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR37.value = (Uns32)(bport1_ab_data.CR37.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR36.value = (Uns32)(bport1_ab_data.CR36.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR35.value = (Uns32)(bport1_ab_data.CR35.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR34.value = (Uns32)(bport1_ab_data.CR34.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR33.value = (Uns32)(bport1_ab_data.CR33.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR32.value = (Uns32)(bport1_ab_data.CR32.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR31.value = (Uns32)(bport1_ab_data.CR31.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR30.value = (Uns32)(bport1_ab_data.CR30.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR29.value = (Uns32)(bport1_ab_data.CR29.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR28.value = (Uns32)(bport1_ab_data.CR28.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR27.value = (Uns32)(bport1_ab_data.CR27.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR26.value = (Uns32)(bport1_ab_data.CR26.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR25.value = (Uns32)(bport1_ab_data.CR25.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR24.value = (Uns32)(bport1_ab_data.CR24.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR23.value = (Uns32)(bport1_ab_data.CR23.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR22.value = (Uns32)(bport1_ab_data.CR22.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR21.value = (Uns32)(bport1_ab_data.CR21.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR20.value = (Uns32)(bport1_ab_data.CR20.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR19.value = (Uns32)(bport1_ab_data.CR19.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR18.value = (Uns32)(bport1_ab_data.CR18.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR17.value = (Uns32)(bport1_ab_data.CR17.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR16.value = (Uns32)(bport1_ab_data.CR16.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR15.value = (Uns32)(bport1_ab_data.CR15.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR14.value = (Uns32)(bport1_ab_data.CR14.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR13.value = (Uns32)(bport1_ab_data.CR13.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR12.value = (Uns32)(bport1_ab_data.CR12.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR11.value = (Uns32)(bport1_ab_data.CR11.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR10.value = (Uns32)(bport1_ab_data.CR10.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR09.value = (Uns32)(bport1_ab_data.CR09.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR08.value = (Uns32)(bport1_ab_data.CR08.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR07.value = (Uns32)(bport1_ab_data.CR07.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR06.value = (Uns32)(bport1_ab_data.CR06.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR05.value = (Uns32)(bport1_ab_data.CR05.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR04.value = (Uns32)(bport1_ab_data.CR04.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR03.value = (Uns32)(bport1_ab_data.CR03.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR02.value = (Uns32)(bport1_ab_data.CR02.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR01.value = (Uns32)(bport1_ab_data.CR01.value & ~(0xffffffff)) | ((0xffffffff) & (0));
        bport1_ab_data.CR00.value = (Uns32)(bport1_ab_data.CR00.value & ~(0xffffffff)) | ((0xffffffff) & (0));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the DDR peripheral used on the Freescale Kinetis platform");
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


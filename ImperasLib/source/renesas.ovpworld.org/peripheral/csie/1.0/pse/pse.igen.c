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

CSIEP0_reg0_dataT CSIEP0_reg0_data;

CSIEP0_reg1_dataT CSIEP0_reg1_data;

CSIEP0_reg2_dataT CSIEP0_reg2_data;

CSIEP0_reg3_dataT CSIEP0_reg3_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "csie", "Example");
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
    handles.CSIEP0 = ppmCreateSlaveBusPort("CSIEP0", 32);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle reg0CTL0_reg = ppmCreateRegister(
            "reg0_CTL0",
            0,
            handles.CSIEP0,
            0x0,
            1,
            read_8,
            writeCTL0,
            view8,
            &(CSIEP0_reg0_data.CTL0.value),
            True
        );

        ppmCreateRegisterField(reg0CTL0_reg, "CSM", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(reg0CTL0_reg, "WE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(reg0CTL0_reg, "SIT", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(reg0CTL0_reg, "DIR", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(reg0CTL0_reg, "TMS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(reg0CTL0_reg, "RXE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(reg0CTL0_reg, "TXE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg0CTL0_reg, "PWR", 0, 7, 1, 1, 1);
    }
    {
        registerHandle reg0CTL1_reg = ppmCreateRegister(
            "reg0_CTL1",
            0,
            handles.CSIEP0,
            0x1,
            1,
            read_8,
            writeCTL1,
            view8,
            &(CSIEP0_reg0_data.CTL1.value),
            True
        );

        ppmCreateRegisterField(reg0CTL1_reg, "CKS", 0, 0, 3, 1, 1);
        ppmCreateRegisterField(reg0CTL1_reg, "DAP", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(reg0CTL1_reg, "CKP", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(reg0CTL1_reg, "MDL", 0, 5, 3, 1, 1);
    }
    {
        ppmCreateRegister(
            "reg1_RX",
            0,
            handles.CSIEP0,
            0x2,
            2,
            readRX,
            0,
            view16,
            &(CSIEP0_reg1_data.RX.value),
            True
        );
    }
    {
        registerHandle reg1CS_reg = ppmCreateRegister(
            "reg1_CS",
            0,
            handles.CSIEP0,
            0x4,
            2,
            read_16,
            writeCS,
            view16,
            &(CSIEP0_reg1_data.CS.value),
            True
        );

        ppmCreateRegisterField(reg1CS_reg, "CS", 0, 0, 4, 1, 1);
    }
    {
        ppmCreateRegister(
            "reg1_TX",
            0,
            handles.CSIEP0,
            0x6,
            2,
            readTX,
            writeTX,
            view16,
            &(CSIEP0_reg1_data.TX.value),
            True
        );
    }
    {
        registerHandle reg2STR_reg = ppmCreateRegister(
            "reg2_STR",
            0,
            handles.CSIEP0,
            0x8,
            1,
            read_8,
            writeSTR,
            view8,
            &(CSIEP0_reg2_data.STR.value),
            True
        );

        ppmCreateRegisterField(reg2STR_reg, "SFP", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(reg2STR_reg, "TSF", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(reg2STR_reg, "EMF", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(reg2STR_reg, "FLF", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg2STR_reg, "PCT", 0, 7, 1, 1, 1);
    }
    {
        registerHandle reg2CTL2_reg = ppmCreateRegister(
            "reg2_CTL2",
            0,
            handles.CSIEP0,
            0x9,
            1,
            read_8,
            writeCTL2,
            view8,
            &(CSIEP0_reg2_data.CTL2.value),
            True
        );

        ppmCreateRegisterField(reg2CTL2_reg, "DL", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(reg2CTL2_reg, "CSL", 0, 4, 4, 1, 1);
    }
    {
        registerHandle reg2CTL3_reg = ppmCreateRegister(
            "reg2_CTL3",
            0,
            handles.CSIEP0,
            0xc,
            1,
            read_8,
            writeCTL3,
            view8,
            &(CSIEP0_reg2_data.CTL3.value),
            True
        );

        ppmCreateRegisterField(reg2CTL3_reg, "SFN", 0, 0, 4, 1, 1);
    }
    {
        registerHandle reg2CTL4_reg = ppmCreateRegister(
            "reg2_CTL4",
            0,
            handles.CSIEP0,
            0xd,
            1,
            read_8,
            writeCTL4,
            view8,
            &(CSIEP0_reg2_data.CTL4.value),
            True
        );

        ppmCreateRegisterField(reg2CTL4_reg, "MD", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(reg2CTL4_reg, "OPE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(reg2CTL4_reg, "DPA", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(reg2CTL4_reg, "CPA", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(reg2CTL4_reg, "CSL", 0, 4, 4, 1, 1);
    }
    {
        ppmCreateNByteRegister(
            "reg3_OPT0",
            0,
            handles.CSIEP0,
            0x10,
            2,
            0,
            writeOPT,
            0,
            &(CSIEP0_reg3_data.OPT[0].value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "reg3_OPT1",
            0,
            handles.CSIEP0,
            0x12,
            2,
            0,
            writeOPT,
            0,
            &(CSIEP0_reg3_data.OPT[1].value),
            (void*)1,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "reg3_OPT2",
            0,
            handles.CSIEP0,
            0x14,
            2,
            0,
            writeOPT,
            0,
            &(CSIEP0_reg3_data.OPT[2].value),
            (void*)2,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "reg3_OPT3",
            0,
            handles.CSIEP0,
            0x16,
            2,
            0,
            writeOPT,
            0,
            &(CSIEP0_reg3_data.OPT[3].value),
            (void*)3,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "reg3_OPT4",
            0,
            handles.CSIEP0,
            0x18,
            2,
            0,
            writeOPT,
            0,
            &(CSIEP0_reg3_data.OPT[4].value),
            (void*)4,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "reg3_OPT5",
            0,
            handles.CSIEP0,
            0x1a,
            2,
            0,
            writeOPT,
            0,
            &(CSIEP0_reg3_data.OPT[5].value),
            (void*)5,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "reg3_OPT6",
            0,
            handles.CSIEP0,
            0x1c,
            2,
            0,
            writeOPT,
            0,
            &(CSIEP0_reg3_data.OPT[6].value),
            (void*)6,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "reg3_OPT7",
            0,
            handles.CSIEP0,
            0x1e,
            2,
            0,
            writeOPT,
            0,
            &(CSIEP0_reg3_data.OPT[7].value),
            (void*)7,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }

}

PPM_NET_CB(reset_IRESET) {
    if(value != 0 ) {
        CSIEP0_reg3_data.OPT[0].value = (Uns16)(CSIEP0_reg3_data.OPT[0].value & ~(0xffff)) | ((0xffff) & (0x0002));
        CSIEP0_reg3_data.OPT[1].value = (Uns16)(CSIEP0_reg3_data.OPT[1].value & ~(0xffff)) | ((0xffff) & (0x0002));
        CSIEP0_reg3_data.OPT[2].value = (Uns16)(CSIEP0_reg3_data.OPT[2].value & ~(0xffff)) | ((0xffff) & (0x0002));
        CSIEP0_reg3_data.OPT[3].value = (Uns16)(CSIEP0_reg3_data.OPT[3].value & ~(0xffff)) | ((0xffff) & (0x0002));
        CSIEP0_reg3_data.OPT[4].value = (Uns16)(CSIEP0_reg3_data.OPT[4].value & ~(0xffff)) | ((0xffff) & (0x0002));
        CSIEP0_reg3_data.OPT[5].value = (Uns16)(CSIEP0_reg3_data.OPT[5].value & ~(0xffff)) | ((0xffff) & (0x0002));
        CSIEP0_reg3_data.OPT[6].value = (Uns16)(CSIEP0_reg3_data.OPT[6].value & ~(0xffff)) | ((0xffff) & (0x0002));
        CSIEP0_reg3_data.OPT[7].value = (Uns16)(CSIEP0_reg3_data.OPT[7].value & ~(0xffff)) | ((0xffff) & (0x0002));
        CSIEP0_reg2_data.CTL4.value = (Uns8)(CSIEP0_reg2_data.CTL4.value & ~(0xff)) | ((0xff) & (0x00));
        CSIEP0_reg2_data.CTL3.value = (Uns8)(CSIEP0_reg2_data.CTL3.value & ~(0xff)) | ((0xff) & (0x00));
        CSIEP0_reg2_data.CTL2.value = (Uns8)(CSIEP0_reg2_data.CTL2.value & ~(0xff)) | ((0xff) & (0x00));
        CSIEP0_reg2_data.STR.value = (Uns8)(CSIEP0_reg2_data.STR.value & ~(0xff)) | ((0xff) & (0x20));
        CSIEP0_reg1_data.TX.value = (Uns16)(CSIEP0_reg1_data.TX.value & ~(0xffff)) | ((0xffff) & (0x0000));
        CSIEP0_reg1_data.CS.value = (Uns16)(CSIEP0_reg1_data.CS.value & ~(0xffff)) | ((0xffff) & (0xffff));
        CSIEP0_reg1_data.RX.value = (Uns16)(CSIEP0_reg1_data.RX.value & ~(0xffff)) | ((0xffff) & (0x0000));
        CSIEP0_reg0_data.CTL1.value = (Uns8)(CSIEP0_reg0_data.CTL1.value & ~(0xff)) | ((0xff) & (0x07));
        CSIEP0_reg0_data.CTL0.value = (Uns8)(CSIEP0_reg0_data.CTL0.value & ~(0xff)) | ((0xff) & (0x00));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Renesas CSIE Enhanced Queued Clocked Serial Interface");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Register View Model Only");
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


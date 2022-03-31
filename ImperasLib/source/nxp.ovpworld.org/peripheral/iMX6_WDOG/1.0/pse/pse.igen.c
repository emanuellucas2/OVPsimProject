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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "iMX6_WDOG", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view16) {  *(Uns16*)data = *(Uns16*)user; }

static PPM_READ_CB(read_16) {  return *(Uns16*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 16384);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

    ppmInstallReadCallback(regNoDefinitionWrite, (void*)0 , handles.bport1 + 0x0, 0x4000);
    ppmInstallWriteCallback(regNoDefinitionRead, (void*)0 , handles.bport1 + 0x0, 0x4000);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abWDOG_WCR_reg = ppmCreateRegister(
            "ab_WDOG_WCR",
            "Description\nWatchdog Control Register\nWatchdog Time-out Field (0.5 to 128 seconds)\nWatchdog Disable for Wait\nSoftware reset extension, an option way to generate software reset\nWDOG_B assertion. Controls the software assertion of the WDOG_B signal\nSoftware Reset Signal. Controls the software assertion of the WDOG-generated reset signal WDOG_RESET_B_DEB\nWDOG_B Time-out assertion. Determines if the WDOG_B gets asserted upon a Watchdog Time-out Event\nWatchdog Enable. Enables or disables the WDOG block\nWatchdog DEBUG Enable. Determines the operation of the WDOG during DEBUG mode\nWatchdog Low Power. Determines the operation of the WDOG during low-power modes\n",
            handles.bport1,
            0x0,
            2,
            read_16,
            WriteWDOG_WCR,
            view16,
            &(bport1_ab_data.WDOG_WCR.value),
            True
        );

        ppmCreateRegisterField(abWDOG_WCR_reg, "WT", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abWDOG_WCR_reg, "WDW", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abWDOG_WCR_reg, "SRE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abWDOG_WCR_reg, "WDA", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abWDOG_WCR_reg, "SRS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abWDOG_WCR_reg, "WDT", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abWDOG_WCR_reg, "WDE", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abWDOG_WCR_reg, "WDBG", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abWDOG_WCR_reg, "WDZST", 0, 0, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_WDOG_WSR",
            "Watchdog Service Register",
            handles.bport1,
            0x2,
            2,
            read_16,
            WriteWDOG_WSR,
            view16,
            &(bport1_ab_data.WDOG_WSR.value),
            True
        );
    }
    {
        registerHandle abWDOG_WRSR_reg = ppmCreateRegister(
            "ab_WDOG_WRSR",
            "Description\nWatchdog Reset Status Register\nPower On Reset. Indicates whether the reset is the result of a power on reset\nTimeout. Indicates whether the reset is the result of a WDOG timeout\nSoftware Reset. Indicates whether the reset is the result of a WDOG software reset by asserting SRS bit\n",
            handles.bport1,
            0x4,
            2,
            read_16,
            0,
            view16,
            &(bport1_ab_data.WDOG_WRSR.value),
            True
        );

        ppmCreateRegisterField(abWDOG_WRSR_reg, "POR", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(abWDOG_WRSR_reg, "TOUT", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(abWDOG_WRSR_reg, "SFTW", 0, 0, 1, 1, 0);
    }
    {
        registerHandle abWDOG_WICR_reg = ppmCreateRegister(
            "ab_WDOG_WICR",
            "Description\nWatchdog Interrupt Control Register\nWatchdog Timer Interrupt enable bit\nWatchdog TImer Interrupt Status bit will reflect the timer interrupt status\nWatchdog Interrupt Count Time-out (WICT) field determines, how long before the counter time-out must the interrupt occur\n",
            handles.bport1,
            0x6,
            2,
            read_16,
            WriteWDOG_WICR,
            view16,
            &(bport1_ab_data.WDOG_WICR.value),
            True
        );

        ppmCreateRegisterField(abWDOG_WICR_reg, "WIE", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abWDOG_WICR_reg, "WTIS", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abWDOG_WICR_reg, "WICT", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abWDOG_WMCR_reg = ppmCreateRegister(
            "ab_WDOG_WMCR",
            "Description\nWatchdog Miscellaneous Control Register\nPower Down Enable bit\n",
            handles.bport1,
            0x8,
            2,
            read_16,
            WriteWDOG_WMCR,
            view16,
            &(bport1_ab_data.WDOG_WMCR.value),
            True
        );

        ppmCreateRegisterField(abWDOG_WMCR_reg, "PDE", 0, 0, 1, 1, 1);
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.WDOG_WMCR.value = (Uns16)(bport1_ab_data.WDOG_WMCR.value & ~(0xffff)) | ((0xffff) & (0x0001));
        bport1_ab_data.WDOG_WICR.value = (Uns16)(bport1_ab_data.WDOG_WICR.value & ~(0xffff)) | ((0xffff) & (0x0004));
        bport1_ab_data.WDOG_WRSR.value = (Uns16)(bport1_ab_data.WDOG_WRSR.value & ~(0xffff)) | ((0xffff) & (0x0000));
        bport1_ab_data.WDOG_WSR.value = (Uns16)(bport1_ab_data.WDOG_WSR.value & ~(0xffff)) | ((0xffff) & (0x0000));
        bport1_ab_data.WDOG_WCR.value = (Uns16)(bport1_ab_data.WDOG_WCR.value & ~(0xffff)) | ((0xffff) & (0x0030));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "iMX6 WDOG");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This is an incomplete model of the WDOG.");
        ppmDocAddText(doc_22_node, "It has basic functionality to support the iMX6 platform.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "i.MX 6Solo/6DualLite Applications Processor Reference Manual (IMX6SDLRM_Ref_Manual.pdf");
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


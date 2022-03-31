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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "TzpcBP147", "Example");
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
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "ab_TZPCR0SIZE",
            0,
            handles.bport1,
            0x0,
            4,
            read_32,
            WriteTZPCR0SIZE,
            view32,
            &(bport1_ab_data.TZPCR0SIZE.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZPCDECPROT0Stat",
            0,
            handles.bport1,
            0x800,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.TZPCDECPROT0Stat.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZPCDECPROT0Set",
            0,
            handles.bport1,
            0x804,
            4,
            0,
            WriteTZPCDECPROT0Set,
            view32,
            &(bport1_ab_data.TZPCDECPROT0Set.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZPCDECPROT0Clr",
            0,
            handles.bport1,
            0x808,
            4,
            0,
            WriteTZPCDECPROT0Clr,
            view32,
            &(bport1_ab_data.TZPCDECPROT0Clr.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZPCDECPROT1Stat",
            0,
            handles.bport1,
            0x80c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.TZPCDECPROT1Stat.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZPCDECPROT1Set",
            0,
            handles.bport1,
            0x810,
            4,
            0,
            WriteTZPCDECPROT1Set,
            view32,
            &(bport1_ab_data.TZPCDECPROT1Set.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZPCDECPROT1Clr",
            0,
            handles.bport1,
            0x814,
            4,
            0,
            WriteTZPCDECPROT1Clr,
            view32,
            &(bport1_ab_data.TZPCDECPROT1Clr.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZPCDECPROT2Stat",
            0,
            handles.bport1,
            0x818,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.TZPCDECPROT2Stat.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZPCDECPROT2Set",
            0,
            handles.bport1,
            0x81c,
            4,
            0,
            WriteTZPCDECPROT2Set,
            view32,
            &(bport1_ab_data.TZPCDECPROT2Set.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZPCDECPROT2Clr",
            0,
            handles.bport1,
            0x820,
            4,
            0,
            WriteTZPCDECPROT2Clr,
            view32,
            &(bport1_ab_data.TZPCDECPROT2Clr.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZPCPERIPHID0",
            0,
            handles.bport1,
            0xfe0,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.TZPCPERIPHID0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZPCPERIPHID1",
            0,
            handles.bport1,
            0xfe4,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.TZPCPERIPHID1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZPCPERIPHID2",
            0,
            handles.bport1,
            0xfe8,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.TZPCPERIPHID2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZPCPERIPHID3",
            0,
            handles.bport1,
            0xfec,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.TZPCPERIPHID3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZPCPCELLID0",
            0,
            handles.bport1,
            0xff0,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.TZPCPCELLID0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZPCPCELLID1",
            0,
            handles.bport1,
            0xff4,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.TZPCPCELLID1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZPCPCELLID2",
            0,
            handles.bport1,
            0xff8,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.TZPCPCELLID2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZPCPCELLID3",
            0,
            handles.bport1,
            0xffc,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.TZPCPCELLID3.value),
            True
        );
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.TZPCPCELLID3.value = (Uns32)(bport1_ab_data.TZPCPCELLID3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000081));
        bport1_ab_data.TZPCPCELLID2.value = (Uns32)(bport1_ab_data.TZPCPCELLID2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000005));
        bport1_ab_data.TZPCPCELLID1.value = (Uns32)(bport1_ab_data.TZPCPCELLID1.value & ~(0xffffffff)) | ((0xffffffff) & (0x000000F0));
        bport1_ab_data.TZPCPCELLID0.value = (Uns32)(bport1_ab_data.TZPCPCELLID0.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000000D));
        bport1_ab_data.TZPCPERIPHID3.value = (Uns32)(bport1_ab_data.TZPCPERIPHID3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TZPCPERIPHID2.value = (Uns32)(bport1_ab_data.TZPCPERIPHID2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000004));
        bport1_ab_data.TZPCPERIPHID1.value = (Uns32)(bport1_ab_data.TZPCPERIPHID1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000018));
        bport1_ab_data.TZPCPERIPHID0.value = (Uns32)(bport1_ab_data.TZPCPERIPHID0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000070));
        bport1_ab_data.TZPCDECPROT2Stat.value = (Uns32)(bport1_ab_data.TZPCDECPROT2Stat.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.TZPCDECPROT1Stat.value = (Uns32)(bport1_ab_data.TZPCDECPROT1Stat.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.TZPCDECPROT0Stat.value = (Uns32)(bport1_ab_data.TZPCDECPROT0Stat.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.TZPCR0SIZE.value = (Uns32)(bport1_ab_data.TZPCR0SIZE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000200));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "ARM BP147 TrustZone Protection Controller.");
        ppmDocAddText(doc2_node, "There are 24 output net ports (TZPCDECPROT0_0 thru TZPCDECPROT2_7) corresponding to the 24 enables defined as 3 banks of 8 enables.");
        ppmDocAddText(doc2_node, "Each net port may be used to drive a net connected to a peripheral such as the DynamicBridge which can enable/disable a BusBridge mapping under control of an input net.");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "none");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_22_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "ARM PrimeCell Infrastructure AMBA3 TrustZone Protection Controller (BP147) Technical Overview (ARM DTO 0015)");
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


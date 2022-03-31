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

mport1_MEM_dataT mport1_MEM_data;

bport1_REG_dataT bport1_REG_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "spi", "Example");
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
    handles.mport1 = ppmCreateSlaveBusPort("mport1", 536870912);
    if (!handles.mport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'mport1'");
    }

    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

    ppmInstallNByteCallbacks(defaultMemRead, defaultMemWrite, 0, handles.bport1, 0x0, 0x1000, True, True, False, BHM_ENDIAN_LITTLE);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {


    {
        registerHandle REGsckdiv_reg = ppmCreateRegister(
            "REG_sckdiv",
            "Description\nSerial clock divisor\nDivisor for serial clock\n",
            handles.bport1,
            0x0,
            4,
            read_32,
            wrSckdiv,
            view32,
            &(bport1_REG_data.sckdiv.value),
            True
        );

        ppmCreateRegisterField(REGsckdiv_reg, "scale", 0, 0, 12, 1, 1);
    }
    {
        registerHandle REGsckmode_reg = ppmCreateRegister(
            "REG_sckmode",
            "Description\nSerial clock mode\nSerial clock phase\nSerial clock polarity\n",
            handles.bport1,
            0x4,
            4,
            read_32,
            wrSckmode,
            view32,
            &(bport1_REG_data.sckmode.value),
            True
        );

        ppmCreateRegisterField(REGsckmode_reg, "pha", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(REGsckmode_reg, "pol", 0, 1, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "REG_csid",
            "Chip select ID",
            handles.bport1,
            0x10,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_REG_data.csid.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_csdef",
            "Chip select default",
            handles.bport1,
            0x14,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_REG_data.csdef.value),
            True
        );
    }
    {
        registerHandle REGcsmode_reg = ppmCreateRegister(
            "REG_csmode",
            "Description\nChip select mode\n\n",
            handles.bport1,
            0x18,
            4,
            read_32,
            wrCsmode,
            view32,
            &(bport1_REG_data.csmode.value),
            True
        );

        ppmCreateRegisterField(REGcsmode_reg, "mode", 0, 0, 2, 1, 1);
    }
    {
        registerHandle REGdelay0_reg = ppmCreateRegister(
            "REG_delay0",
            "Description\nDelay control 0\nCS to SCK Delay\nSCK to CS Delay\n",
            handles.bport1,
            0x28,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_REG_data.delay0.value),
            True
        );

        ppmCreateRegisterField(REGdelay0_reg, "cssck", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(REGdelay0_reg, "sckcs", 0, 16, 8, 1, 1);
    }
    {
        registerHandle REGdelay1_reg = ppmCreateRegister(
            "REG_delay1",
            "Description\nDelay control 1\nMinimum CS inactive time\nMaximum interframe delay\n",
            handles.bport1,
            0x2c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_REG_data.delay1.value),
            True
        );

        ppmCreateRegisterField(REGdelay1_reg, "intercs", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(REGdelay1_reg, "interxfr", 0, 16, 8, 1, 1);
    }
    {
        registerHandle REGfmt_reg = ppmCreateRegister(
            "REG_fmt",
            "Description\nFrame format\nSPI Protocol\nSPI endinanness\nSPI I/O Direction\nNumber of bits per frame\n",
            handles.bport1,
            0x40,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_REG_data.fmt.value),
            True
        );

        ppmCreateRegisterField(REGfmt_reg, "proto", 0, 0, 2, 1, 1);
        ppmCreateRegisterField(REGfmt_reg, "endian", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(REGfmt_reg, "dir", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(REGfmt_reg, "len", 0, 16, 4, 1, 1);
    }
    {
        registerHandle REGtxdata_reg = ppmCreateRegister(
            "REG_txdata",
            "Description\nTx FIFO data\nTransmit data\nFIFO full flag\n",
            handles.bport1,
            0x48,
            4,
            rdTx,
            wrTx,
            view32,
            &(bport1_REG_data.txdata.value),
            True
        );

        ppmCreateRegisterField(REGtxdata_reg, "data", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(REGtxdata_reg, "full", 0, 31, 1, 1, 1);
    }
    {
        registerHandle REGrxdata_reg = ppmCreateRegister(
            "REG_rxdata",
            "Description\nRx FIFO data\nReceived data\nFIFO empty flag\n",
            handles.bport1,
            0x4c,
            4,
            rdRx,
            0,
            view32,
            &(bport1_REG_data.rxdata.value),
            True
        );

        ppmCreateRegisterField(REGrxdata_reg, "data", 0, 0, 8, 1, 0);
        ppmCreateRegisterField(REGrxdata_reg, "empty", 0, 31, 1, 1, 0);
    }
    {
        registerHandle REGtxmark_reg = ppmCreateRegister(
            "REG_txmark",
            "Description\nTx FIFO watermark\nTransmit watermark\n",
            handles.bport1,
            0x50,
            4,
            read_32,
            wrTxMark,
            view32,
            &(bport1_REG_data.txmark.value),
            True
        );

        ppmCreateRegisterField(REGtxmark_reg, "txmark", 0, 0, 3, 1, 1);
    }
    {
        registerHandle REGrxmark_reg = ppmCreateRegister(
            "REG_rxmark",
            "Description\nRx FIFO watermark\nreceive watermark\n",
            handles.bport1,
            0x54,
            4,
            read_32,
            wrRxMark,
            view32,
            &(bport1_REG_data.rxmark.value),
            True
        );

        ppmCreateRegisterField(REGrxmark_reg, "rxmark", 0, 0, 3, 1, 1);
    }
    {
        registerHandle REGfctrl_reg = ppmCreateRegister(
            "REG_fctrl",
            "Description\nSPI flash interface control\nSPI Flash Mode Select\n",
            handles.bport1,
            0x60,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_REG_data.fctrl.value),
            True
        );

        ppmCreateRegisterField(REGfctrl_reg, "en", 0, 0, 1, 1, 1);
    }
    {
        registerHandle REGffmt_reg = ppmCreateRegister(
            "REG_ffmt",
            "Description\nSPI flash instruction format\nEnable sending of command\nNumber of address bytes(0 to 4)\nNumber of dummy cycles\nProtocol for transmitting command\nProtocol for transmitting address and padding\nProtocol for receiving data bytes\nValue of command byte\nFirst 8 bits to transmit during dummy cycles\n",
            handles.bport1,
            0x64,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_REG_data.ffmt.value),
            True
        );

        ppmCreateRegisterField(REGffmt_reg, "cmd_en", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(REGffmt_reg, "addr_len", 0, 1, 3, 1, 1);
        ppmCreateRegisterField(REGffmt_reg, "pad_cnt", 0, 4, 4, 1, 1);
        ppmCreateRegisterField(REGffmt_reg, "cmd_proto", 0, 8, 2, 1, 1);
        ppmCreateRegisterField(REGffmt_reg, "addr_proto", 0, 10, 2, 1, 1);
        ppmCreateRegisterField(REGffmt_reg, "data_proto", 0, 12, 2, 1, 1);
        ppmCreateRegisterField(REGffmt_reg, "cmd_code", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(REGffmt_reg, "pad_code", 0, 24, 8, 1, 1);
    }
    {
        registerHandle REGie_reg = ppmCreateRegister(
            "REG_ie",
            "Description\nSPI interrupt enable\nTransmit watermark enable\nReceive watermark enable\n",
            handles.bport1,
            0x70,
            4,
            read_32,
            0,
            view32,
            &(bport1_REG_data.ie.value),
            True
        );

        ppmCreateRegisterField(REGie_reg, "txwm", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(REGie_reg, "rxwm", 0, 1, 1, 1, 0);
    }
    {
        registerHandle REGip_reg = ppmCreateRegister(
            "REG_ip",
            "Description\nSPI interrupt pending\nTransmit watermark pending\nReceive watermark pending\n",
            handles.bport1,
            0x74,
            4,
            read_32,
            0,
            view32,
            &(bport1_REG_data.ip.value),
            True
        );

        ppmCreateRegisterField(REGip_reg, "txwm", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(REGip_reg, "rxwm", 0, 1, 1, 1, 0);
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_REG_data.ip.value = (Uns32)(bport1_REG_data.ip.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.ie.value = (Uns32)(bport1_REG_data.ie.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.ffmt.value = (Uns32)(bport1_REG_data.ffmt.value & ~(0xffffffff)) | ((0xffffffff) & (0x00030007));
        bport1_REG_data.fctrl.value = (Uns32)(bport1_REG_data.fctrl.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bport1_REG_data.rxmark.value = (Uns32)(bport1_REG_data.rxmark.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bport1_REG_data.txmark.value = (Uns32)(bport1_REG_data.txmark.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bport1_REG_data.rxdata.value = (Uns32)(bport1_REG_data.rxdata.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.txdata.value = (Uns32)(bport1_REG_data.txdata.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.fmt.value = (Uns32)(bport1_REG_data.fmt.value & ~(0xffffffff)) | ((0xffffffff) & (0x00080008));
        bport1_REG_data.delay1.value = (Uns32)(bport1_REG_data.delay1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.delay0.value = (Uns32)(bport1_REG_data.delay0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.csmode.value = (Uns32)(bport1_REG_data.csmode.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.csdef.value = (Uns32)(bport1_REG_data.csdef.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bport1_REG_data.csid.value = (Uns32)(bport1_REG_data.csid.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.sckmode.value = (Uns32)(bport1_REG_data.sckmode.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.sckdiv.value = (Uns32)(bport1_REG_data.sckdiv.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000003));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "SiFive coreip-s51-arty SPI Registers and Memory (spi)");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model implements only the registers and memory. It contains no SPI behaviour.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "SiFive Freedom E SDK coreip-s51-arty Board Support Package details.");
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


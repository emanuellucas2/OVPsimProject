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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "VirtioNetMMIO", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 512);

    ppmInstallNByteCallbacks(readCfg, writeCfg, 0, handles.bport1, 0x100, 0x100, 1, 1, 1, BHM_ENDIAN_LITTLE);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateNByteRegister(
            "ab_MagicValue",
            "Magic value ('virt' string)",
            handles.bport1,
            0x0,
            4,
            rdMagic,
            0,
            0,
            &(bport1_ab_data.MagicValue.value),
            (void*)0,
            True,
            1,
            0,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_Version",
            "Device Version number",
            handles.bport1,
            0x4,
            4,
            0,
            0,
            0,
            &(bport1_ab_data.Version.value),
            (void*)0,
            True,
            1,
            0,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_DeviceID",
            "Block Subsystem Device ID",
            handles.bport1,
            0x8,
            4,
            0,
            0,
            0,
            &(bport1_ab_data.DeviceID.value),
            (void*)0,
            True,
            1,
            0,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_VendorID",
            "Subsystem Vendor ID ('OVP' string)",
            handles.bport1,
            0xc,
            4,
            0,
            0,
            0,
            &(bport1_ab_data.VendorID.value),
            (void*)0,
            True,
            1,
            0,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_HostFeatures",
            "Host features flags",
            handles.bport1,
            0x10,
            4,
            rdHostF,
            0,
            0,
            &(bport1_ab_data.HostFeatures.value),
            (void*)0,
            True,
            1,
            0,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_HostFSel",
            "Host features select",
            handles.bport1,
            0x14,
            4,
            0,
            wrSel,
            0,
            &(bport1_ab_data.HostFSel.value),
            (void*)0,
            True,
            0,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_GuestFeatures",
            "Guest features flags",
            handles.bport1,
            0x20,
            4,
            0,
            wrGuestF,
            0,
            &(bport1_ab_data.GuestFeatures.value),
            (void*)0,
            True,
            0,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_GuestFSel",
            "Guest features select",
            handles.bport1,
            0x24,
            4,
            0,
            wrSel,
            0,
            &(bport1_ab_data.GuestFSel.value),
            (void*)0,
            True,
            0,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_GuestPageSz",
            "Guest page size",
            handles.bport1,
            0x28,
            4,
            0,
            wrGPgSz,
            0,
            &(bport1_ab_data.GuestPageSz.value),
            (void*)0,
            True,
            0,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_QueueSel",
            "Virtual queue index",
            handles.bport1,
            0x30,
            4,
            0,
            wrSel,
            0,
            &(bport1_ab_data.QueueSel.value),
            (void*)0,
            True,
            0,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_QueueNumMax",
            "Maximum virtual queue size",
            handles.bport1,
            0x34,
            4,
            0,
            0,
            0,
            &(bport1_ab_data.QueueNumMax.value),
            (void*)0,
            True,
            1,
            0,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_QueueNum",
            "Virtual queue size",
            handles.bport1,
            0x38,
            4,
            0,
            wrQNum,
            0,
            &(bport1_ab_data.QueueNum.value),
            (void*)0,
            True,
            0,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_QueueAlign",
            "Virtual queue align",
            handles.bport1,
            0x3c,
            4,
            0,
            wrQAlign,
            0,
            &(bport1_ab_data.QueueAlign.value),
            (void*)0,
            True,
            0,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_QueuePFN",
            "Virtual queue PFN",
            handles.bport1,
            0x40,
            4,
            rdQPFN,
            wrQPFN,
            0,
            &(bport1_ab_data.QueuePFN.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        ppmCreateNByteRegister(
            "ab_QueueNotify",
            "Virtual queue notify",
            handles.bport1,
            0x50,
            4,
            0,
            wrQNotify,
            0,
            &(bport1_ab_data.QueueNotify.value),
            (void*)0,
            True,
            0,
            1,
            BHM_ENDIAN_LITTLE
        );
    }
    {
        registerHandle abIntStatus_reg = ppmCreateNByteRegister(
            "ab_IntStatus",
            "Interrupt status",
            handles.bport1,
            0x60,
            4,
            rdIntStat,
            0,
            0,
            &(bport1_ab_data.IntStatus.value),
            (void*)0,
            True,
            1,
            0,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abIntStatus_reg, "UsedRingUpdate", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(abIntStatus_reg, "ConfigChange", 0, 1, 1, 1, 0);
    }
    {
        registerHandle abIntAck_reg = ppmCreateNByteRegister(
            "ab_IntAck",
            "Interrupt acknowlege",
            handles.bport1,
            0x64,
            4,
            0,
            wrIntAck,
            0,
            &(bport1_ab_data.IntAck.value),
            (void*)0,
            True,
            0,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abIntAck_reg, "UsedRingUpdate", 0, 0, 1, 0, 1);
        ppmCreateRegisterField(abIntAck_reg, "ConfigChange", 0, 1, 1, 0, 1);
    }
    {
        registerHandle abStatus_reg = ppmCreateNByteRegister(
            "ab_Status",
            "Device status",
            handles.bport1,
            0x70,
            4,
            rdStatus,
            wrStatus,
            0,
            &(bport1_ab_data.Status.value),
            (void*)0,
            True,
            1,
            1,
            BHM_ENDIAN_LITTLE
        );

        ppmCreateRegisterField(abStatus_reg, "Ack", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abStatus_reg, "Driver", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abStatus_reg, "DriverOk", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abStatus_reg, "Failed", 0, 7, 1, 1, 1);
    }

}

/////////////////////////////// Bus Master Ports ///////////////////////////////

static void installMasterPorts(void) {
    handles.dma = ppmOpenAddressSpace("dma");
    if (!handles.dma) {
        bhmMessage("E", "PPM_MPNC", "Could not connect port 'dma'");
    }
}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.Status.value = (Uns32)(bport1_ab_data.Status.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.IntAck.value = (Uns32)(bport1_ab_data.IntAck.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.IntStatus.value = (Uns32)(bport1_ab_data.IntStatus.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.QueueNotify.value = (Uns32)(bport1_ab_data.QueueNotify.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.QueuePFN.value = (Uns32)(bport1_ab_data.QueuePFN.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.QueueAlign.value = (Uns32)(bport1_ab_data.QueueAlign.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.QueueNum.value = (Uns32)(bport1_ab_data.QueueNum.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.QueueNumMax.value = (Uns32)(bport1_ab_data.QueueNumMax.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000100));
        bport1_ab_data.QueueSel.value = (Uns32)(bport1_ab_data.QueueSel.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.GuestPageSz.value = (Uns32)(bport1_ab_data.GuestPageSz.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.GuestFSel.value = (Uns32)(bport1_ab_data.GuestFSel.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.GuestFeatures.value = (Uns32)(bport1_ab_data.GuestFeatures.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.HostFSel.value = (Uns32)(bport1_ab_data.HostFSel.value & ~(0xffffffff)) | ((0xffffffff) & (0x0));
        bport1_ab_data.HostFeatures.value = (Uns32)(bport1_ab_data.HostFeatures.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000020));
        bport1_ab_data.VendorID.value = (Uns32)(bport1_ab_data.VendorID.value & ~(0xffffffff)) | ((0xffffffff) & (0x0050564F));
        bport1_ab_data.DeviceID.value = (Uns32)(bport1_ab_data.DeviceID.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bport1_ab_data.Version.value = (Uns32)(bport1_ab_data.Version.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bport1_ab_data.MagicValue.value = (Uns32)(bport1_ab_data.MagicValue.value & ~(0xffffffff)) | ((0xffffffff) & (0x74726976));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "\n VIRTIO version 1 mmio block device\n This model implements a VIRTIO  MMIO net device as described in:\n      http://docs.oasis-open.org/virtio/virtio/v1.0/virtio-v1.0.pdf.\n");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "\nOnly supports the Legacy (Device Version 1) interface.\nOnly little endian guests are supported.\n");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_22_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "\nhttp://docs.oasis-open.org/virtio/virtio/v1.0/virtio-v1.0.pdf\n");
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


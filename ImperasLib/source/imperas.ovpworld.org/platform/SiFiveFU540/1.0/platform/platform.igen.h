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

#define UNUSED   __attribute__((unused))

// instantiate module components
static OP_CONSTRUCT_FN(instantiateComponents) {

    optDocNodeP doc1_node = opModuleDocSectionAdd(mi, "Licensing");
    opDocTextAdd(doc1_node, "Open Source Apache 2.0");
    optDocNodeP doc_11_node = opModuleDocSectionAdd(mi, "Description");
    opDocTextAdd(doc_11_node, "\n    SiFive FU540-C000 SoC module.\n    On start up or reset, the reset code at 0x1004 will jump to a jump table entry indexed by the MSEL register at address 0x1000 (default initial MSEL value is 0xf which will cause a jump to address 0x10000). Use the msel peripheral's MSEL parameter to change the initial value of this register. \n    To run a bare metal application use the --program command line option to specify an elf file to be loaded. It must be linked to use addresses corresponding to the implemented memory regions. The --program option will override the initial pc with the ELF file's start address. \n    To facilitate booting Linux an OVP SmartLoader psuedo-peripheral has been included that provides the functionality of the ZSBL/FSBL. The SmartLoader's dtb parameter should be used to specify the device tree blob file to load, and the bbl elf file should be loaded using the --objfilenoentry command line option. \n    ");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_21_node, "SiFive Freedom U540-C000 Manual FU540-C000-v1.0.pdf (https://www.sifive.com/documentation/chips/freedom-u540-c000-manual)");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_31_node, "\n    Caches and the Cache Controller are not modeled.\n    The Instruction Tightly Integrated Memory (ITIM) is implemented simply as RAM. Deallocation by writing to the byte immediately following the memory is a NOP.\n    The L2 Loosely Integrated Memory (L2-LIM) is implemented simply as RAM. It is always available, since the Cache Controller is not modeled.\n    The L2 Scratchpad memory is not modeled.\n    The Platform DMA Engine (PDMA) is not modeled.\n    The Pulse Width Modulator (PWM) is not modeled.\n    The Inter-Integrated Circuit (I2C) Master Interface is not modeled.\n    The Serial Peripheral Interface (SPI) is not modeled. Instead a Virtio Block MMIO device has been added at reserved address 0x1f000000, using interrupt 54.\n    The General Purpose Input/Output Controller (GPIO) is not modeled.\n    The One-Time Programmable Memory Interface (OTP) is not modeled.\n    DDR controller is not modeled. DDR memory is modeled as RAM.\n    The Debug Interface is not modeled.");


    // Module Instance SiFiveFU540

    const char *SiFiveFU540_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "module",
        "FU540",
        "1.0",
        OP_MODULE,
        OP_VLNV_PRINT
    );

    opParamBoolOverride(mi, "SiFiveFU540/uart0/console", 1);
    opParamBoolOverride(mi, "SiFiveFU540/uart0/finishOnDisconnect", 1);
    opParamStringOverride(mi, "SiFiveFU540/uart0/outfile", "uart0.log");
    opModuleNew(
        mi,       // parent module
        SiFiveFU540_path,       // modelfile
        "SiFiveFU540",   // name
        0,
        0
    );

}

optModuleAttr modelAttrs = {
    .versionString        = OP_VERSION,
    .type                 = OP_MODULE,
    .name                 = MODULE_NAME,
    .objectSize           = sizeof(optModuleObject),
    .releaseStatus        = OP_OVP,
    .purpose              = OP_PP_FIX,
    .visibility           = OP_VISIBLE,
    .vlnv          = {
        .vendor  = "imperas.ovpworld.org",
        .library = "platform",
        .name    = "SiFiveFU540",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

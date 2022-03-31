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
    opDocTextAdd(doc_11_node, "This platform instances an ARM VersatileExpress with a Xilinx Microblaze based sub-system");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "Peripherals are modeled to the extent required to boot and run Operating Systems such as Linux.");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "ARM Development Boards VersatileExpress");


    // Bus busX1

    optBusP busX1_b = opBusNew(mi, "busX1", 32, 0, 0);


    // Processor xilinx1

    const char *xilinx1_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        0,
        "microblaze",
        "1.0",
        OP_PROCESSOR,
        OP_VLNV_PRINT
    );

    opProcessorNew(
        mi,
        xilinx1_path,
        "xilinx1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busX1_b, "INSTRUCTION"),
                OP_BUS_CONNECT(busX1_b, "DATA")
            )
        ),
        0
    );


    // Module Instance versatileexpress

    const char *versatileexpress_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        "module",
        "ArmVersatileExpress-CA15",
        "1.0",
        OP_MODULE,
        OP_VLNV_PRINT
    );

    opModuleNew(
        mi,       // parent module
        versatileexpress_path,       // modelfile
        "versatileexpress",   // name
        0,
        0
    );

    // Memory ramX1

    opMemoryNew(
        mi,
        "ramX1",
        OP_PRIV_RWX,
        (0x2fffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busX1_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x2fffffffULL)
            )
        ),
        0
    );

    // PSE uartX

    const char *uartX_path = opVLNVString(
        0, // use the default VLNV path
        "national.ovpworld.org",
        0,
        "16550",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uartX_path,
        "uartX",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busX1_b, "bport1", .slave=1, .addrLo=0x40000000ULL, .addrHi=0x40000007ULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_STRING_SET("outfile", "uartX.log")
        )
    );

}

optModuleAttr modelAttrs = {
    .versionString        = OP_VERSION,
    .type                 = OP_MODULE,
    .name                 = MODULE_NAME,
    .objectSize           = sizeof(optModuleObject),
    .releaseStatus        = OP_IMPERAS,
    .purpose              = OP_PP_MODULE,
    .visibility           = OP_VISIBLE,
    .vlnv          = {
        .vendor  = "imperas.ovpworld.org",
        .library = "module",
        .name    = "Hetero_ArmVersatileExpress_XilinxMicroBlaze",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

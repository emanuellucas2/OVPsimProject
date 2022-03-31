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

    optDocNodeP doc1_node = opModuleDocSectionAdd(mi, "Description");
    opDocTextAdd(doc1_node, "Platform for an Or1k Processor to execute uCLinux.");
    optDocNodeP doc_11_node = opModuleDocSectionAdd(mi, "Licensing");
    opDocTextAdd(doc_11_node, "Open Source Apache 2.0");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "Provides sufficient functionality to execute uCLinux operating system and OR1K elf files");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "none");


    // Bus bus1

    optBusP bus1_b = opBusNew(mi, "bus1", 32, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP int1_n = opNetNew(mi, "int1", 0, 0);

    // Processor cpu1

    const char *cpu1_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "or1k",
        0,
        OP_PROCESSOR,
        OP_VLNV_PRINT
    );

    opProcessorNew(
        mi,
        cpu1_path,
        "cpu1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "INSTRUCTION"),
                OP_BUS_CONNECT(bus1_b, "DATA")
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(int1_n, "intr2")
            )
        ),
        0
    );


    // Memory mem1

    opMemoryNew(
        mi,
        "mem1",
        OP_PRIV_RWX,
        (0x8fffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x8fffffffULL)
            )
        ),
        0
    );

    // Memory mem2

    opMemoryNew(
        mi,
        "mem2",
        OP_PRIV_RWX,
        (0xffffffffULL) - (0x90000008ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "sp1", .slave=1, .addrLo=0x90000008ULL, .addrHi=0xffffffffULL)
            )
        ),
        0
    );

    // PSE uart1

    const char *uart1_path = opVLNVString(
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
        uart1_path,
        "uart1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "bport1", .slave=1, .addrLo=0x90000000ULL, .addrHi=0x90000007ULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(int1_n, "intOut")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
        )
    );

}

optModuleAttr modelAttrs = {
    .versionString        = OP_VERSION,
    .type                 = OP_MODULE,
    .name                 = MODULE_NAME,
    .objectSize           = sizeof(optModuleObject),
    .releaseStatus        = OP_OVP,
    .purpose              = OP_PP_BAREMETAL,
    .visibility           = OP_VISIBLE,
    .vlnv          = {
        .vendor  = "imperas.ovpworld.org",
        .library = "platform",
        .name    = "Or1kUclinux",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

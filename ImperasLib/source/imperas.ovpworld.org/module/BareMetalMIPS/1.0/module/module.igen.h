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
    opDocTextAdd(doc1_node, "Bare Metal hardware defintion with an MIPS32 Processor.");
    optDocNodeP doc_11_node = opModuleDocSectionAdd(mi, "Licensing");
    opDocTextAdd(doc_11_node, "Open Source Apache 2.0");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "BareMetal platform for execution of MIPS MIPS32 binary elf files.");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "None");
    // Variables indicating when parameters are set
    Bool addressbits_isSet        = 0;

    // Variables holding parameter values
    UNUSED Uns32        addressbits              = opObjectParamUns32Value(mi, "addressbits", &addressbits_isSet);


    // Bus bus

    optBusP bus_b = opBusNew(mi, "bus", addressbits, 0, 0);


    // Bus pBusMapped

    optBusP pBusMapped_b = opBusNew(mi, "pBusMapped", 32, "pBusP", 0);


    // Processor cpu

    const char *cpu_path = opVLNVString(
        0, // use the default VLNV path
        "mips.ovpworld.org",
        "processor",
        "mips32_r1r5",
        0,
        OP_PROCESSOR,
        OP_VLNV_PRINT
    );

    opProcessorNew(
        mi,
        cpu_path,
        "cpu",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus_b, "INSTRUCTION"),
                OP_BUS_CONNECT(bus_b, "DATA")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("defaultsemihost", 1)
        )
    );


    // Memory memory1

    opMemoryNew(
        mi,
        "memory1",
        OP_PRIV_RWX,
        (0x400fffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x400fffffULL)
            )
        ),
        0
    );

    // Memory memory2

    opMemoryNew(
        mi,
        "memory2",
        OP_PRIV_RWX,
        (0xffffffffULL) - (0x40110000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus_b, "sp1", .slave=1, .addrLo=0x40110000ULL, .addrHi=0xffffffffULL)
            )
        ),
        0
    );

    // Bridge pBusBridge

    opBridgeNew(
        mi,
        "pBusBridge",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBusMapped_b, "mp1", .addrLo=0x0ULL, .addrHi=0xffffULL),
                OP_BUS_CONNECT(bus_b, "sp1", .slave=1, .addrLo=0x40100000ULL, .addrHi=0x4010ffffULL)
            )
        ),
        0
    );

}

static optParamSpec paramSpecs[] = {
    {
        .name        = "addressbits",
        .type        = OP_PARAM_UNS32,
        .description = "Allows the address bits for the main bus to be modified (default 32)",
        .spec.uns32Spec.min          = 32,
        .spec.uns32Spec.max          = 64,
        .spec.uns32Spec.defaultValue = 32,
    },
    { 0 }
};

static OP_PARAM_SPEC_FN(moduleParamIterator) {
    prev = prev ? prev + 1 : paramSpecs; 
    return prev->name ? prev : 0;
}

static optBusPortInfo busPortSpecs[] = {
    {
        .name        = "pBusP",
        .description = 0,
    },
    { 0 }
};

static OP_BUS_PORT_FN(moduleBusPortIterator) {
    prev = prev ? prev + 1 : busPortSpecs; 
    return prev->name ? prev : 0;
}


optModuleAttr modelAttrs = {
    .versionString        = OP_VERSION,
    .type                 = OP_MODULE,
    .name                 = MODULE_NAME,
    .objectSize           = sizeof(optModuleObject),
    .releaseStatus        = OP_OVP,
    .purpose              = OP_PP_MODULE,
    .visibility           = OP_VISIBLE,
    .vlnv          = {
        .vendor  = "imperas.ovpworld.org",
        .library = "module",
        .name    = "BareMetalMIPS",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
    .paramSpecsCB         = moduleParamIterator,
    .busPortSpecsCB       = moduleBusPortIterator,
};

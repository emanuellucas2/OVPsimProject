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
    opDocTextAdd(doc_11_node, "SiFive coreip-s51-rtl module.");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_21_node, "SiFive Freedom E SDK coreip-s51-rtl Board Support Package details.");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_31_node, "The IO peripherals are provided as register only models.");


    // Bus bus

    optBusP bus_b = opBusNew(mi, "bus", 40, 0, 0);


    // Module Instance S51CC

    const char *S51CC_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "module",
        "S51CC",
        "1.0",
        OP_MODULE,
        OP_VLNV_PRINT
    );

    opModuleNew(
        mi,       // parent module
        S51CC_path,       // modelfile
        "S51CC",   // name
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus_b, "systemPort")
            )
        ),
        0
    );

    // Memory mem

    opMemoryNew(
        mi,
        "mem",
        OP_PRIV_RWX,
        (0x23ffffffULL) - (0x20000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus_b, "sp1", .slave=1, .addrLo=0x20000000ULL, .addrHi=0x23ffffffULL)
            )
        ),
        0
    );

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
        .vendor  = "sifive.ovpworld.org",
        .library = "module",
        .name    = "coreip-s51-rtl",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

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
    opDocTextAdd(doc_11_node, "This module implements a NoC ni used to implement an example TTEL NoC in the Xilinx Zynq Programmable Logic (PL).\nThis PL configuration instances one Xilinx MicroBlaze processor with a local memory and a TTEL NoC interface peripheral.");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "This is baremetal only.");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "No Reference");
    // Variables indicating when parameters are set
    Bool cluster_isSet            = 0;
    Bool tile_isSet               = 0;
    Bool node_isSet               = 0;

    // Variables holding parameter values
    UNUSED Uns32        cluster                  = opObjectParamUns32Value(mi, "cluster", &cluster_isSet);
    UNUSED Uns32        tile                     = opObjectParamUns32Value(mi, "tile", &tile_isSet);
    UNUSED Uns32        node                     = opObjectParamUns32Value(mi, "node", &node_isSet);


    // Bus pBus

    optBusP pBus_b = opBusNew(mi, "pBus", 32, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP CoreInterrupt_n = opNetNew(mi, "CoreInterrupt", 0, 0);
    optNetP pIntToCore_n = opNetNew(mi, "pIntToCore", 0, 0);

    optPacketnetP networkNode_pkn = opPacketnetNew(mi, "networkNode", "networkNodePort", 0);

    // Processor cpu

    const char *cpu_path = opVLNVString(
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
        cpu_path,
        "cpu",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "INSTRUCTION"),
                OP_BUS_CONNECT(pBus_b, "DATA")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("defaultsemihost", 1)
        )
    );


    // Memory ramS

    opMemoryNew(
        mi,
        "ramS",
        OP_PRIV_RWX,
        (0x3ffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x3ffffffULL)
            )
        ),
        0
    );

    // PSE ni

    const char *ni_path = opVLNVString(
        0, // use the default VLNV path
        "safepower.ovpworld.org",
        0,
        "TTELNode",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ni_path,
        "ni",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "hostif", .slave=1, .addrLo=0x80000000ULL, .addrHi=0x80ffffffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(CoreInterrupt_n, "CoreInterrupt"),
                OP_NET_CONNECT(pIntToCore_n, "pIntToCore")
            ),
            OP_PACKETNET_CONNECTIONS(
                OP_PACKETNET_CONNECT(networkNode_pkn, "network")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("cluster", cluster)
            ,OP_PARAM_UNS32_SET("tile", tile)
            ,OP_PARAM_UNS32_SET("node", node)
        )
    );

}

static optParamSpec paramSpecs[] = {
    {
        .name        = "cluster",
        .type        = OP_PARAM_UNS32,
        .description = 0,
    },
    {
        .name        = "tile",
        .type        = OP_PARAM_UNS32,
        .description = 0,
    },
    {
        .name        = "node",
        .type        = OP_PARAM_UNS32,
        .description = 0,
    },
    { 0 }
};

static OP_PARAM_SPEC_FN(moduleParamIterator) {
    prev = prev ? prev + 1 : paramSpecs; 
    return prev->name ? prev : 0;
}

static optPacketnetPortInfo packetnetPortSpecs[] = {
    {
        .name        = "networkNodePort",
        .mustConnect = 1,
        .description = 0,
    },
    { 0 }
};

static OP_PACKETNET_PORT_FN(modulePacketnetPortIterator) {
    prev = prev ? prev + 1 : packetnetPortSpecs; 
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
        .vendor  = "safepower.ovpworld.org",
        .library = "module",
        .name    = "Zynq_PL_TTELNoC_node",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
    .paramSpecsCB         = moduleParamIterator,
    .packetnetPortSpecsCB = modulePacketnetPortIterator,
};

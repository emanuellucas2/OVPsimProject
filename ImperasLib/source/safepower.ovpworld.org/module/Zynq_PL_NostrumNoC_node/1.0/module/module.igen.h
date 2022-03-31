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
    opDocTextAdd(doc_11_node, "This module implements a NoC node used to implement an example NoC in the Xilinx Zynq Programmable Logic (PL).\nThis PL configuration instances one Xilinx MicroBlaze processor with a local memory and a NoC interface peripheral.");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "This is baremetal only.");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "No Reference");
    // Variables indicating when parameters are set
    Bool nocid_isSet              = 0;
    Bool generateSync_isSet       = 0;
    Bool sendChannelSize_isSet    = 0;
    Bool mboxSize_isSet           = 0;

    // Variables holding parameter values
    UNUSED Uns32        nocid                    = opObjectParamUns32Value(mi, "nocid", &nocid_isSet);
    UNUSED Bool         generateSync             = opObjectParamBoolValue(mi, "generateSync", &generateSync_isSet);
    UNUSED Uns32        sendChannelSize          = opObjectParamUns32Value(mi, "sendChannelSize", &sendChannelSize_isSet);
    UNUSED Uns32        mboxSize                 = opObjectParamUns32Value(mi, "mboxSize", &mboxSize_isSet);


    // Bus pBus

    optBusP pBus_b = opBusNew(mi, "pBus", 32, 0, 0);


    // Bus gpiodprBus

    optBusP gpiodprBus_b = opBusNew(mi, "gpiodprBus", 32, "gpiodprPort", 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP gpio_out_n = opNetNew(mi, "gpio_out", "gpio_outP", 0);
    optNetP gpio2_out_n = opNetNew(mi, "gpio2_out", "gpio2_outP", 0);
    optNetP gpio_in_n = opNetNew(mi, "gpio_in", "gpio_inP", 0);
    optNetP gpio2_in_n = opNetNew(mi, "gpio2_in", "gpio2_inP", 0);
    optNetP syncIn_n = opNetNew(mi, "syncIn", "syncInPort", 0);
    optNetP syncOut_n = opNetNew(mi, "syncOut", "syncOutPort", 0);

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

    // Bridge gpiodprBridge

    opBridgeNew(
        mi,
        "gpiodprBridge",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(gpiodprBus_b, "mp1", .addrLo=0x41000000ULL, .addrHi=0x410001ffULL),
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x41000000ULL, .addrHi=0x410001ffULL)
            )
        ),
        0
    );

    // PSE gpio

    const char *gpio_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        0,
        "axi-gpio",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        gpio_path,
        "gpio",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x40000000ULL, .addrHi=0x400001ffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(gpio_out_n, "gpio_out"),
                OP_NET_CONNECT(gpio2_out_n, "gpio2_out"),
                OP_NET_CONNECT(gpio_in_n, "gpio_in"),
                OP_NET_CONNECT(gpio2_in_n, "gpio2_in")
            )
        ),
        0
    );

    // PSE node

    const char *node_path = opVLNVString(
        0, // use the default VLNV path
        "safepower.ovpworld.org",
        0,
        "NostrumNode",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        node_path,
        "node",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "hostif", .slave=1, .addrLo=0x70020000ULL, .addrHi=0x7003ffffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(syncIn_n, "syncIn"),
                OP_NET_CONNECT(syncOut_n, "syncOut")
            ),
            OP_PACKETNET_CONNECTIONS(
                OP_PACKETNET_CONNECT(networkNode_pkn, "network")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("id", nocid)
            ,OP_PARAM_BOOL_SET("generateSync", generateSync)
            ,OP_PARAM_UNS32_SET("sendChannelSize", sendChannelSize)
            ,OP_PARAM_UNS32_SET("mboxSize", mboxSize)
        )
    );

}

static optParamSpec paramSpecs[] = {
    {
        .name        = "nocid",
        .type        = OP_PARAM_UNS32,
        .description = 0,
    },
    {
        .name        = "generateSync",
        .type        = OP_PARAM_BOOL,
        .description = 0,
    },
    {
        .name        = "sendChannelSize",
        .type        = OP_PARAM_UNS32,
        .description = 0,
    },
    {
        .name        = "mboxSize",
        .type        = OP_PARAM_UNS32,
        .description = 0,
    },
    { 0 }
};

static OP_PARAM_SPEC_FN(moduleParamIterator) {
    prev = prev ? prev + 1 : paramSpecs; 
    return prev->name ? prev : 0;
}

static optBusPortInfo busPortSpecs[] = {
    {
        .name        = "gpiodprPort",
        .description = 0,
    },
    { 0 }
};

static OP_BUS_PORT_FN(moduleBusPortIterator) {
    prev = prev ? prev + 1 : busPortSpecs; 
    return prev->name ? prev : 0;
}

static optNetPortInfo netPortSpecs[] = {
    {
        .name        = "syncInPort",
        .description = 0,
    },
    {
        .name        = "syncOutPort",
        .description = 0,
    },
    {
        .name        = "gpio_outP",
        .description = 0,
    },
    {
        .name        = "gpio2_outP",
        .description = 0,
    },
    {
        .name        = "gpio_inP",
        .description = 0,
    },
    {
        .name        = "gpio2_inP",
        .description = 0,
    },
    { 0 }
};

static OP_NET_PORT_FN(moduleNetPortIterator) {
    prev = prev ? prev + 1 : netPortSpecs; 
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
        .name    = "Zynq_PL_NostrumNoC_node",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
    .paramSpecsCB         = moduleParamIterator,
    .busPortSpecsCB       = moduleBusPortIterator,
    .netPortSpecsCB       = moduleNetPortIterator,
    .packetnetPortSpecsCB = modulePacketnetPortIterator,
};

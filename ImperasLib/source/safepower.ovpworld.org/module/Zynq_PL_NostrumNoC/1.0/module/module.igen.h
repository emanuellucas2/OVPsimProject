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
    opDocTextAdd(doc_11_node, "This module implements a configuration for Xilinx Zynq Programmable Logic (PL).\nThis PL configuration instances four Xilinx MicroBlaze processor based NoC sub-systems (Zync_PL_NoC_node), each with a MicroBlaze processor, local memory and NoC interface Peripheral.\nAlso included is a NoC interface peripheral that is accessible from the Zynq_PS ARM processors.");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "This is baremetal only.");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "No Reference");


    // Bus extPortBus

    optBusP extPortBus_b = opBusNew(mi, "extPortBus", 32, "extPort", 0);


    // Bus mBus

    optBusP mBus_b = opBusNew(mi, "mBus", 32, 0, 0);


    // Bus gpiodprBus

    optBusP gpiodprBus_b = opBusNew(mi, "gpiodprBus", 32, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    opNetNew(mi, "gpio_bank2_out", "gpio_bank2_outP", 0);
    opNetNew(mi, "gpio_bank2_oen_out", "gpio_bank2_oen_outP", 0);
    opNetNew(mi, "gpio_bank2_in", "gpio_bank2_inP", 0);
    opNetNew(mi, "gpio_bank3_out", "gpio_bank3_outP", 0);
    opNetNew(mi, "gpio_bank3_oen_out", "gpio_bank3_oen_outP", 0);
    opNetNew(mi, "gpio_bank3_in", "gpio_bank3_inP", 0);
    opNetNew(mi, "irqf2p0", "irqf2p0_outP", 0);
    opNetNew(mi, "irqf2p1", "irqf2p1_outP", 0);
    opNetNew(mi, "irqf2p2", "irqf2p2_outP", 0);
    opNetNew(mi, "irqf2p3", "irqf2p3_outP", 0);
    opNetNew(mi, "irqf2p4", "irqf2p4_outP", 0);
    opNetNew(mi, "irqf2p5", "irqf2p5_outP", 0);
    opNetNew(mi, "irqf2p6", "irqf2p6_outP", 0);
    opNetNew(mi, "irqf2p7", "irqf2p7_outP", 0);
    opNetNew(mi, "irqf2p8", "irqf2p8_outP", 0);
    opNetNew(mi, "irqf2p9", "irqf2p9_outP", 0);
    opNetNew(mi, "irqf2p10", "irqf2p10_outP", 0);
    opNetNew(mi, "irqf2p11", "irqf2p11_outP", 0);
    opNetNew(mi, "irqf2p12", "irqf2p12_outP", 0);
    opNetNew(mi, "irqf2p13", "irqf2p13_outP", 0);
    opNetNew(mi, "irqf2p14", "irqf2p14_outP", 0);
    opNetNew(mi, "irqf2p15", "irqf2p15_outP", 0);
    opNetNew(mi, "irqf2p16", "irqf2p16_outP", 0);
    opNetNew(mi, "irqf2p17", "irqf2p17_outP", 0);
    opNetNew(mi, "irqf2p18", "irqf2p18_outP", 0);
    opNetNew(mi, "irqf2p19", "irqf2p19_outP", 0);
    opNetNew(mi, "irqp2f0", "irqp2f0_inP", 0);
    opNetNew(mi, "irqp2f1", "irqp2f1_inP", 0);
    opNetNew(mi, "irqp2f2", "irqp2f2_inP", 0);
    opNetNew(mi, "irqp2f3", "irqp2f3_inP", 0);
    opNetNew(mi, "irqp2f4", "irqp2f4_inP", 0);
    opNetNew(mi, "irqp2f5", "irqp2f5_inP", 0);
    opNetNew(mi, "irqp2f6", "irqp2f6_inP", 0);
    opNetNew(mi, "irqp2f7", "irqp2f7_inP", 0);
    opNetNew(mi, "irqp2f8", "irqp2f8_inP", 0);
    opNetNew(mi, "irqp2f9", "irqp2f9_inP", 0);
    opNetNew(mi, "irqp2f10", "irqp2f10_inP", 0);
    opNetNew(mi, "irqp2f11", "irqp2f11_inP", 0);
    opNetNew(mi, "irqp2f12", "irqp2f12_inP", 0);
    opNetNew(mi, "irqp2f13", "irqp2f13_inP", 0);
    opNetNew(mi, "irqp2f14", "irqp2f14_inP", 0);
    opNetNew(mi, "irqp2f15", "irqp2f15_inP", 0);
    opNetNew(mi, "irqp2f16", "irqp2f16_inP", 0);
    opNetNew(mi, "irqp2f17", "irqp2f17_inP", 0);
    opNetNew(mi, "irqp2f18", "irqp2f18_inP", 0);
    opNetNew(mi, "irqp2f19", "irqp2f19_inP", 0);
    opNetNew(mi, "irqp2f20", "irqp2f20_inP", 0);
    opNetNew(mi, "irqp2f21", "irqp2f21_inP", 0);
    opNetNew(mi, "irqp2f22", "irqp2f22_inP", 0);
    opNetNew(mi, "irqp2f23", "irqp2f23_inP", 0);
    opNetNew(mi, "irqp2f24", "irqp2f24_inP", 0);
    opNetNew(mi, "irqp2f25", "irqp2f25_inP", 0);
    opNetNew(mi, "irqp2f26", "irqp2f26_inP", 0);
    opNetNew(mi, "irqp2f27", "irqp2f27_inP", 0);
    opNetNew(mi, "irqp2f28", "irqp2f28_inP", 0);
    optNetP sync_n = opNetNew(mi, "sync", 0, 0);
    optNetP pio_0_0_gpio_out_n = opNetNew(mi, "pio_0_0_gpio_out", 0, 0);
    optNetP pio_0_0_gpio2_in_n = opNetNew(mi, "pio_0_0_gpio2_in", 0, 0);
    optNetP pio_dpr_gpio_out_n = opNetNew(mi, "pio_dpr_gpio_out", 0, 0);
    optNetP pio_0_1_gpio_out_n = opNetNew(mi, "pio_0_1_gpio_out", 0, 0);
    optNetP pio_0_1_gpio2_in_n = opNetNew(mi, "pio_0_1_gpio2_in", 0, 0);
    optNetP pio_1_0_gpio_out_n = opNetNew(mi, "pio_1_0_gpio_out", 0, 0);
    optNetP pio_1_0_gpio2_in_n = opNetNew(mi, "pio_1_0_gpio2_in", 0, 0);
    optNetP pio_1_1_gpio_out_n = opNetNew(mi, "pio_1_1_gpio_out", 0, 0);
    optNetP pio_1_1_gpio2_in_n = opNetNew(mi, "pio_1_1_gpio2_in", 0, 0);

    optPacketnetP network_pkn = opPacketnetNew(mi, "network", 0, 0);

    // Module Instance NoC_0_1

    const char *NoC_0_1_path = opVLNVString(
        0, // use the default VLNV path
        "safepower.ovpworld.org",
        "module",
        "Zynq_PL_NostrumNoC_node",
        "1.0",
        OP_MODULE,
        OP_VLNV_PRINT
    );

    opModuleNew(
        mi,       // parent module
        NoC_0_1_path,       // modelfile
        "NoC_0_1",   // name
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(gpiodprBus_b, "gpiodprPort")
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(sync_n, "syncInPort"),
                OP_NET_CONNECT(pio_0_1_gpio_out_n, "gpio_outP"),
                OP_NET_CONNECT(pio_0_1_gpio2_in_n, "gpio2_inP")
            ),
            OP_PACKETNET_CONNECTIONS(
                OP_PACKETNET_CONNECT(network_pkn, "networkNodePort")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("nocid", 1)
            ,OP_PARAM_UNS32_SET("sendChannelSize", 3)
            ,OP_PARAM_UNS32_SET("mboxSize", 16)
        )
    );

    // Module Instance NoC_1_0

    const char *NoC_1_0_path = opVLNVString(
        0, // use the default VLNV path
        "safepower.ovpworld.org",
        "module",
        "Zynq_PL_NostrumNoC_node",
        "1.0",
        OP_MODULE,
        OP_VLNV_PRINT
    );

    opModuleNew(
        mi,       // parent module
        NoC_1_0_path,       // modelfile
        "NoC_1_0",   // name
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(gpiodprBus_b, "gpiodprPort")
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(sync_n, "syncInPort"),
                OP_NET_CONNECT(pio_1_0_gpio_out_n, "gpio_outP"),
                OP_NET_CONNECT(pio_1_0_gpio2_in_n, "gpio2_inP")
            ),
            OP_PACKETNET_CONNECTIONS(
                OP_PACKETNET_CONNECT(network_pkn, "networkNodePort")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("nocid", 2)
            ,OP_PARAM_UNS32_SET("sendChannelSize", 2)
            ,OP_PARAM_UNS32_SET("mboxSize", 16)
        )
    );

    // Module Instance NoC_1_1

    const char *NoC_1_1_path = opVLNVString(
        0, // use the default VLNV path
        "safepower.ovpworld.org",
        "module",
        "Zynq_PL_NostrumNoC_node",
        "1.0",
        OP_MODULE,
        OP_VLNV_PRINT
    );

    opModuleNew(
        mi,       // parent module
        NoC_1_1_path,       // modelfile
        "NoC_1_1",   // name
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(gpiodprBus_b, "gpiodprPort")
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(sync_n, "syncInPort"),
                OP_NET_CONNECT(pio_1_1_gpio_out_n, "gpio_outP"),
                OP_NET_CONNECT(pio_1_1_gpio2_in_n, "gpio2_inP")
            ),
            OP_PACKETNET_CONNECTIONS(
                OP_PACKETNET_CONNECT(network_pkn, "networkNodePort")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("nocid", 3)
            ,OP_PARAM_UNS32_SET("sendChannelSize", 2)
            ,OP_PARAM_UNS32_SET("mboxSize", 16)
        )
    );

    // Bridge smem_extPort

    opBridgeNew(
        mi,
        "smem_extPort",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(mBus_b, "mp1", .addrLo=0x40000000ULL, .addrHi=0x400fffffULL),
                OP_BUS_CONNECT(extPortBus_b, "sp1", .slave=1, .addrLo=0x40000000ULL, .addrHi=0x400fffffULL)
            )
        ),
        0
    );

    // Bridge smem2_extPort

    opBridgeNew(
        mi,
        "smem2_extPort",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(gpiodprBus_b, "mp1", .addrLo=0x41000000ULL, .addrHi=0x41000fffULL),
                OP_BUS_CONNECT(extPortBus_b, "sp1", .slave=1, .addrLo=0x41000000ULL, .addrHi=0x41000fffULL)
            )
        ),
        0
    );

    // Bridge nocif_extPort

    opBridgeNew(
        mi,
        "nocif_extPort",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(mBus_b, "mp1", .addrLo=0x70020000ULL, .addrHi=0x7003ffffULL),
                OP_BUS_CONNECT(extPortBus_b, "sp1", .slave=1, .addrLo=0x70020000ULL, .addrHi=0x7003ffffULL)
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
                OP_BUS_CONNECT(mBus_b, "sp1", .slave=1, .addrLo=0x40000000ULL, .addrHi=0x400001ffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(pio_0_0_gpio_out_n, "gpio_out"),
                OP_NET_CONNECT(pio_0_0_gpio2_in_n, "gpio2_in")
            )
        ),
        0
    );

    // PSE NoC_0_0

    const char *NoC_0_0_path = opVLNVString(
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
        NoC_0_0_path,
        "NoC_0_0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(mBus_b, "hostif", .slave=1, .addrLo=0x70020000ULL, .addrHi=0x7003ffffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(sync_n, "syncOut")
            ),
            OP_PACKETNET_CONNECTIONS(
                OP_PACKETNET_CONNECT(network_pkn, "network")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("id", 0)
            ,OP_PARAM_BOOL_SET("generateSync", 1)
            ,OP_PARAM_UNS32_SET("sendChannelSize", 3)
            ,OP_PARAM_UNS32_SET("mboxSize", 16)
        )
    );

    // PSE gpio_dpr

    const char *gpio_dpr_path = opVLNVString(
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
        gpio_dpr_path,
        "gpio_dpr",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(gpiodprBus_b, "sp1", .slave=1, .addrLo=0x41000000ULL, .addrHi=0x410001ffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(pio_dpr_gpio_out_n, "gpio_out"),
                OP_NET_CONNECT(pio_0_0_gpio2_in_n, "gpio2_in")
            )
        ),
        0
    );

}

static optBusPortInfo busPortSpecs[] = {
    {
        .name        = "extPort",
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
        .name        = "gpio_bank2_outP",
        .description = 0,
    },
    {
        .name        = "gpio_bank2_oen_outP",
        .description = 0,
    },
    {
        .name        = "gpio_bank2_inP",
        .description = 0,
    },
    {
        .name        = "gpio_bank3_outP",
        .description = 0,
    },
    {
        .name        = "gpio_bank3_oen_outP",
        .description = 0,
    },
    {
        .name        = "gpio_bank3_inP",
        .description = 0,
    },
    {
        .name        = "irqf2p0_outP",
        .description = 0,
    },
    {
        .name        = "irqf2p1_outP",
        .description = 0,
    },
    {
        .name        = "irqf2p2_outP",
        .description = 0,
    },
    {
        .name        = "irqf2p3_outP",
        .description = 0,
    },
    {
        .name        = "irqf2p4_outP",
        .description = 0,
    },
    {
        .name        = "irqf2p5_outP",
        .description = 0,
    },
    {
        .name        = "irqf2p6_outP",
        .description = 0,
    },
    {
        .name        = "irqf2p7_outP",
        .description = 0,
    },
    {
        .name        = "irqf2p8_outP",
        .description = 0,
    },
    {
        .name        = "irqf2p9_outP",
        .description = 0,
    },
    {
        .name        = "irqf2p10_outP",
        .description = 0,
    },
    {
        .name        = "irqf2p11_outP",
        .description = 0,
    },
    {
        .name        = "irqf2p12_outP",
        .description = 0,
    },
    {
        .name        = "irqf2p13_outP",
        .description = 0,
    },
    {
        .name        = "irqf2p14_outP",
        .description = 0,
    },
    {
        .name        = "irqf2p15_outP",
        .description = 0,
    },
    {
        .name        = "irqf2p16_outP",
        .description = 0,
    },
    {
        .name        = "irqf2p17_outP",
        .description = 0,
    },
    {
        .name        = "irqf2p18_outP",
        .description = 0,
    },
    {
        .name        = "irqf2p19_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f0_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f1_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f2_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f3_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f4_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f5_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f6_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f7_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f8_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f9_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f10_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f11_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f12_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f13_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f14_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f15_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f16_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f17_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f18_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f19_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f20_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f21_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f22_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f23_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f24_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f25_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f26_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f27_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f28_inP",
        .description = 0,
    },
    { 0 }
};

static OP_NET_PORT_FN(moduleNetPortIterator) {
    prev = prev ? prev + 1 : netPortSpecs; 
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
        .name    = "Zynq_PL_NostrumNoC",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
    .busPortSpecsCB       = moduleBusPortIterator,
    .netPortSpecsCB       = moduleNetPortIterator,
};

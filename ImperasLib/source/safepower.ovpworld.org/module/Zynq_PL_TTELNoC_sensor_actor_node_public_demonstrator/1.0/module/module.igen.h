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
    opDocTextAdd(doc_11_node, "This module implements a Sensor/Actor Node for the SafePower Public Demonstrator in the Xilinx Zynq Programmable Logic (PL).\nThis PL configuration instances one Xilinx MicroBlaze processor with a local memory and a TTEL NoC interface peripheral.");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "Provides a baremetal implementation.");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "SafePower Public Demonstrator");
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

    optNetP timer_intc_n = opNetNew(mi, "timer_intc", 0, 0);
    optNetP period_intc_n = opNetNew(mi, "period_intc", 0, 0);
    optNetP core_intc_n = opNetNew(mi, "core_intc", 0, 0);
    optNetP intc_mb_n = opNetNew(mi, "intc_mb", 0, 0);

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
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(intc_mb_n, "Interrupt")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("defaultsemihost", 1)
            ,OP_PARAM_UNS32_SET("C_ENDIANNESS", 1)
            ,OP_PARAM_UNS32_SET("C_USE_INTERRUPT", 1)
            ,OP_PARAM_UNS32_SET("C_INTERCONNECT", 2)
            ,OP_PARAM_UNS32_SET("C_USE_FPU", 1)
            ,OP_PARAM_UNS32_SET("C_USE_HW_MUL", 2)
            ,OP_PARAM_BOOL_SET("C_USE_DIV", 1)
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

    // Memory iic_bu

    opMemoryNew(
        mi,
        "iic_bu",
        OP_PRIV_RWX,
        (0x4081ffffULL) - (0x40810000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x40810000ULL, .addrHi=0x4081ffffULL)
            )
        ),
        0
    );

    // Memory iic_imu

    opMemoryNew(
        mi,
        "iic_imu",
        OP_PRIV_RWX,
        (0x4080ffffULL) - (0x40800000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x40800000ULL, .addrHi=0x4080ffffULL)
            )
        ),
        0
    );

    // Memory iic_motor

    opMemoryNew(
        mi,
        "iic_motor",
        OP_PRIV_RWX,
        (0x4082ffffULL) - (0x40820000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x40820000ULL, .addrHi=0x4082ffffULL)
            )
        ),
        0
    );

    // Memory debug_gpio_led_gimbal

    opMemoryNew(
        mi,
        "debug_gpio_led_gimbal",
        OP_PRIV_RWX,
        (0x4003ffffULL) - (0x40000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x40000000ULL, .addrHi=0x4003ffffULL)
            )
        ),
        0
    );

    // Memory spi_bg

    opMemoryNew(
        mi,
        "spi_bg",
        OP_PRIV_RWX,
        (0x44a1ffffULL) - (0x44a10000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x44a10000ULL, .addrHi=0x44a1ffffULL)
            )
        ),
        0
    );

    // Memory ppm

    opMemoryNew(
        mi,
        "ppm",
        OP_PRIV_RWX,
        (0x44a0ffffULL) - (0x44a00000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x44a00000ULL, .addrHi=0x44a0ffffULL)
            )
        ),
        0
    );

    // Memory xadc

    opMemoryNew(
        mi,
        "xadc",
        OP_PRIV_RWX,
        (0x44a2ffffULL) - (0x44a20000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x44a20000ULL, .addrHi=0x44a2ffffULL)
            )
        ),
        0
    );

    // Memory clock_control

    opMemoryNew(
        mi,
        "clock_control",
        OP_PRIV_RWX,
        (0x44a3ffffULL) - (0x44a30000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x44a30000ULL, .addrHi=0x44a3ffffULL)
            )
        ),
        0
    );

    // Memory ttel_clock

    opMemoryNew(
        mi,
        "ttel_clock",
        OP_PRIV_RWX,
        (0x44a4ffffULL) - (0x44a40000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x44a40000ULL, .addrHi=0x44a4ffffULL)
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
                OP_NET_CONNECT(period_intc_n, "PeriodInterrupt"),
                OP_NET_CONNECT(core_intc_n, "CoreInterrupt")
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

    // PSE intc

    const char *intc_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        0,
        "axi-intc",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        intc_path,
        "intc",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x41200000ULL, .addrHi=0x412001ffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(timer_intc_n, "intr3"),
                OP_NET_CONNECT(core_intc_n, "intr2"),
                OP_NET_CONNECT(period_intc_n, "intr0"),
                OP_NET_CONNECT(intc_mb_n, "irq")
            )
        ),
        0
    );

    // PSE timer

    const char *timer_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        0,
        "axi-timer",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        timer_path,
        "timer",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp", .slave=1, .addrLo=0x41c00000ULL, .addrHi=0x41c0001fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(timer_intc_n, "Interrupt")
            )
        ),
        OP_PARAMS(
             OP_PARAM_STRING_SET("endian", "little")
            ,OP_PARAM_DOUBLE_SET("frequency", 100.000000)
        )
    );

    // PSE uart

    const char *uart_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        0,
        "xps-uartlite",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart_path,
        "uart",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "plb", .slave=1, .addrLo=0x40600000ULL, .addrHi=0x4060000fULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_STRING_SET("endian", "little")
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
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
        .name    = "Zynq_PL_TTELNoC_sensor_actor_node_public_demonstrator",
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

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
    opDocTextAdd(doc_11_node, "This platform models the Altera Cyclone V SOC FPGA chip Hard Processor System.");
    opDocTextAdd(doc_11_node, "The processor is an ARM Cortex-A9MPx2.");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "Peripherals are modeled only to the extent required to boot and run Operating Systems such as Linux.");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "Cyclone V Handbook Volume 3: Hard Processor System Technical Reference Manual cv_5v4 2013.12.30.");


    // Bus smbus

    optBusP smbus_b = opBusNew(mi, "smbus", 32, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP ir199_n = opNetNew(mi, "ir199", 0, 0);
    optNetP ir200_n = opNetNew(mi, "ir200", 0, 0);
    optNetP ir201_n = opNetNew(mi, "ir201", 0, 0);
    optNetP ir202_n = opNetNew(mi, "ir202", 0, 0);
    optNetP ir194_n = opNetNew(mi, "ir194", 0, 0);
    optNetP ir195_n = opNetNew(mi, "ir195", 0, 0);
    optNetP cpu0Reset_n = opNetNew(mi, "cpu0Reset", 0, 0);
    optNetP cpu1Reset_n = opNetNew(mi, "cpu1Reset", 0, 0);

    // Processor cpu

    const char *cpu_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "arm",
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
                OP_BUS_CONNECT(smbus_b, "INSTRUCTION"),
                OP_BUS_CONNECT(smbus_b, "DATA")
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir199_n, "SPI199"),
                OP_NET_CONNECT(ir200_n, "SPI200"),
                OP_NET_CONNECT(ir201_n, "SPI201"),
                OP_NET_CONNECT(ir202_n, "SPI202"),
                OP_NET_CONNECT(ir194_n, "SPI194"),
                OP_NET_CONNECT(ir195_n, "SPI195"),
                OP_NET_CONNECT(cpu0Reset_n, "reset_CPU0"),
                OP_NET_CONNECT(cpu1Reset_n, "reset_CPU1")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_DOUBLE_SET("mips", 100.0)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_ENUM_SET("variant", "Cortex-A9MPx2")
            ,OP_PARAM_ENUM_SET("compatibility", "ISA")
            ,OP_PARAM_BOOL_SET("UAL", 1)
            ,OP_PARAM_BOOL_SET("showHiddenRegs", 0)
            ,OP_PARAM_UNS32_SET("override_CBAR", 0xfffec000)
            ,OP_PARAM_UNS32_SET("override_GICD_TYPER_ITLines", 6)
        )
    );


    // Memory sram1

    opMemoryNew(
        mi,
        "sram1",
        OP_PRIV_RWX,
        (0x3fffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x3fffffffULL)
            )
        ),
        0
    );

    // PSE L2

    const char *L2_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "L2CachePL310",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        L2_path,
        "L2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0xfffef000ULL, .addrHi=0xfffeffffULL)
            )
        ),
        0
    );

    // PSE timer0

    const char *timer0_path = opVLNVString(
        0, // use the default VLNV path
        "altera.ovpworld.org",
        0,
        "dw-apb-timer",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        timer0_path,
        "timer0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0xffc08000ULL, .addrHi=0xffc08fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir199_n, "irq")
            )
        ),
        0
    );

    // PSE timer1

    const char *timer1_path = opVLNVString(
        0, // use the default VLNV path
        "altera.ovpworld.org",
        0,
        "dw-apb-timer",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        timer1_path,
        "timer1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0xffc09000ULL, .addrHi=0xffc09fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir200_n, "irq")
            )
        ),
        0
    );

    // PSE timer2

    const char *timer2_path = opVLNVString(
        0, // use the default VLNV path
        "altera.ovpworld.org",
        0,
        "dw-apb-timer",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        timer2_path,
        "timer2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0xffd00000ULL, .addrHi=0xffd00fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir201_n, "irq")
            )
        ),
        0
    );

    // PSE timer3

    const char *timer3_path = opVLNVString(
        0, // use the default VLNV path
        "altera.ovpworld.org",
        0,
        "dw-apb-timer",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        timer3_path,
        "timer3",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0xffd01000ULL, .addrHi=0xffd01fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir202_n, "irq")
            )
        ),
        0
    );

    // PSE uart0

    const char *uart0_path = opVLNVString(
        0, // use the default VLNV path
        "altera.ovpworld.org",
        0,
        "dw-apb-uart",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart0_path,
        "uart0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0xffc02000ULL, .addrHi=0xffc02fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir194_n, "intOut")
            )
        ),
        OP_PARAMS(
             OP_PARAM_STRING_SET("outfile", "uart0.log")
            ,OP_PARAM_BOOL_SET("console", 1)
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
        )
    );

    // PSE uart1

    const char *uart1_path = opVLNVString(
        0, // use the default VLNV path
        "altera.ovpworld.org",
        0,
        "dw-apb-uart",
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
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0xffc03000ULL, .addrHi=0xffc03fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir195_n, "intOut")
            )
        ),
        OP_PARAMS(
             OP_PARAM_STRING_SET("outfile", "uart1.log")
            ,OP_PARAM_BOOL_SET("console", 1)
        )
    );

    // PSE RSTMGR0

    const char *RSTMGR0_path = opVLNVString(
        0, // use the default VLNV path
        "altera.ovpworld.org",
        0,
        "RSTMGR",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        RSTMGR0_path,
        "RSTMGR0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0xffd05000ULL, .addrHi=0xffd05fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(cpu0Reset_n, "cpu0Reset"),
                OP_NET_CONNECT(cpu1Reset_n, "cpu1Reset")
            )
        ),
        0
    );

    // PSE SYSMGR0

    const char *SYSMGR0_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        SYSMGR0_path,
        "SYSMGR0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xffd08000)
        )
    );

    // PSE CLKMGR0

    const char *CLKMGR0_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        CLKMGR0_path,
        "CLKMGR0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xffd04000)
        )
    );

    // PSE pdma0

    const char *pdma0_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        pdma0_path,
        "pdma0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xffe01000)
        )
    );

    // PSE gmac0

    const char *gmac0_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        gmac0_path,
        "gmac0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xff700000)
        )
    );

    // PSE emac0_dma

    const char *emac0_dma_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        emac0_dma_path,
        "emac0_dma",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xff701000)
        )
    );

    // PSE gmac1

    const char *gmac1_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        gmac1_path,
        "gmac1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xff702000)
        )
    );

    // PSE emac1_dma

    const char *emac1_dma_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        emac1_dma_path,
        "emac1_dma",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xff703000)
        )
    );

    // PSE smartLoader

    const char *smartLoader_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "SmartLoaderArmLinux",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        smartLoader_path,
        "smartLoader",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_b, "mport", .addrLo=0x0ULL, .addrHi=0xffffffffULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("boardid", 0xffffffff)
            ,OP_PARAM_STRING_SET("kernel", "zImage")
            ,OP_PARAM_STRING_SET("initrd", "fs.img")
            ,OP_PARAM_STRING_SET("command", "mem=1024M console=ttyS0")
            ,OP_PARAM_UNS32_SET("physicalbase", 0x00000000)
            ,OP_PARAM_UNS32_SET("memsize", 0x40000000)
            ,OP_PARAM_BOOL_SET("disable", 0)
        )
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
        .vendor  = "altera.ovpworld.org",
        .library = "module",
        .name    = "AlteraCycloneV_HPS",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

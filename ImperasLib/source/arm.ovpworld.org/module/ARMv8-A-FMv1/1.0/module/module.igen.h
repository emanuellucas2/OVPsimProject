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
    opDocTextAdd(doc_11_node, "\nThis platform implements the ARM v8-A Foundation Model v1 memory map described in ARM DUI 0677C.\n\nThe default processor is an ARM Cortex-A57MPx4.\n\nThe processor mips rate is modeled as 500MIPS by default. \n\nThe timerScaleFactor and processor MIPS rate default to values to model a 100MHz timer and CNTFREQ is automatically set accordingly. \nThis matches the clock frequency in the default Linux device tree. These should be adjusted if that is changed.\n");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "\nThis platform provides the peripherals required to boot and run Operating Systems such as Linux.\nSome of the peripherals are register-only, non-functional models. See the individual peripheral model documentation for details.\n");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "ARM DUI 0677C");


    // Bus pBus

    optBusP pBus_b = opBusNew(mi, "pBus", 40, 0, 0);


    // Bus pBusMapped

    optBusP pBusMapped_b = opBusNew(mi, "pBusMapped", 32, "pBusP", 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP ir5_n = opNetNew(mi, "ir5", 0, 0);
    optNetP ir6_n = opNetNew(mi, "ir6", 0, 0);
    optNetP ir7_n = opNetNew(mi, "ir7", 0, 0);
    optNetP ir8_n = opNetNew(mi, "ir8", 0, 0);
    optNetP ir15_n = opNetNew(mi, "ir15", 0, 0);
    optNetP ir42_n = opNetNew(mi, "ir42", 0, 0);
    optNetP directReadN_n = opNetNew(mi, "directReadN", "directReadP", 0);
    optNetP directWriteN_n = opNetNew(mi, "directWriteN", "directWriteP", 0);

    optPacketnetP phyEthernet_pkn = opPacketnetNew(mi, "phyEthernet", "phyEthernetPort", 0);

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
                OP_BUS_CONNECT(pBus_b, "INSTRUCTION"),
                OP_BUS_CONNECT(pBus_b, "DATA")
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir5_n, "SPI37"),
                OP_NET_CONNECT(ir6_n, "SPI38"),
                OP_NET_CONNECT(ir7_n, "SPI39"),
                OP_NET_CONNECT(ir8_n, "SPI40"),
                OP_NET_CONNECT(ir15_n, "SPI47"),
                OP_NET_CONNECT(ir42_n, "SPI74")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_DOUBLE_SET("mips", 500)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_ENUM_SET("variant", "Cortex-A57MPx4")
            ,OP_PARAM_ENUM_SET("compatibility", "ISA")
            ,OP_PARAM_BOOL_SET("UAL", 1)
            ,OP_PARAM_UNS32_SET("override_CBAR", 0x2c000000)
            ,OP_PARAM_UNS32_SET("override_GICD_TYPER_ITLines", 4)
            ,OP_PARAM_UNS32_SET("override_timerScaleFactor", 5)
        )
    );


    // Memory RAM0

    opMemoryNew(
        mi,
        "RAM0",
        OP_PRIV_RWX,
        (0x3ffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x3ffffffULL)
            )
        ),
        0
    );

    // Memory RAM1

    opMemoryNew(
        mi,
        "RAM1",
        OP_PRIV_RWX,
        (0x403ffffULL) - (0x4000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x4000000ULL, .addrHi=0x403ffffULL)
            )
        ),
        0
    );

    // Memory RAM2

    opMemoryNew(
        mi,
        "RAM2",
        OP_PRIV_RWX,
        (0x7ffffffULL) - (0x6000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x6000000ULL, .addrHi=0x7ffffffULL)
            )
        ),
        0
    );

    // Memory DRAM0

    opMemoryNew(
        mi,
        "DRAM0",
        OP_PRIV_RWX,
        (0xffffffffULL) - (0x80000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x80000000ULL, .addrHi=0xffffffffULL)
            )
        ),
        0
    );

    // Memory DRAM1

    opMemoryNew(
        mi,
        "DRAM1",
        OP_PRIV_RWX,
        (0x9ffffffffULL) - (0x880000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x880000000ULL, .addrHi=0x9ffffffffULL)
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
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x5000000ULL, .addrHi=0x500ffffULL)
            )
        ),
        0
    );

    // PSE eth0

    const char *eth0_path = opVLNVString(
        0, // use the default VLNV path
        "smsc.ovpworld.org",
        0,
        "LAN91C111",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        eth0_path,
        "eth0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1a000000ULL, .addrHi=0x1a000fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir15_n, "irq")
            ),
            OP_PACKETNET_CONNECTIONS(
                OP_PACKETNET_CONNECT(phyEthernet_pkn, "phy")
            )
        ),
        0
    );

    // PSE sysRegs

    const char *sysRegs_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "VexpressSysRegs",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        sysRegs_path,
        "sysRegs",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1c010000ULL, .addrHi=0x1c010fffULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("SYS_PROCID0", 0x14000237)
        )
    );

    // PSE uart0

    const char *uart0_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "UartPL011",
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1c090000ULL, .addrHi=0x1c090fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir5_n, "irq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_STRING_SET("variant", "ARM")
            ,OP_PARAM_STRING_SET("outfile", "uart0.log")
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
            ,OP_PARAM_UNS32_SET("xchars", 120)
            ,OP_PARAM_UNS32_SET("ychars", 40)
        )
    );

    // PSE uart1

    const char *uart1_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "UartPL011",
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1c0a0000ULL, .addrHi=0x1c0a0fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir6_n, "irq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_STRING_SET("variant", "ARM")
            ,OP_PARAM_STRING_SET("outfile", "uart1.log")
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
        )
    );

    // PSE uart2

    const char *uart2_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "UartPL011",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart2_path,
        "uart2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1c0b0000ULL, .addrHi=0x1c0b0fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir7_n, "irq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_STRING_SET("variant", "ARM")
        )
    );

    // PSE uart3

    const char *uart3_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "UartPL011",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart3_path,
        "uart3",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1c0c0000ULL, .addrHi=0x1c0c0fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir8_n, "irq"),
                OP_NET_CONNECT(directReadN_n, "DirectRead"),
                OP_NET_CONNECT(directWriteN_n, "DirectWrite")
            )
        ),
        OP_PARAMS(
             OP_PARAM_STRING_SET("variant", "ARM")
        )
    );

    // PSE vbd0

    const char *vbd0_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "VirtioBlkMMIO",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        vbd0_path,
        "vbd0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "dma", .addrLo=0x0ULL, .addrHi=0xffffffffffULL),
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1c130000ULL, .addrHi=0x1c1301ffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir42_n, "Interrupt")
            )
        ),
        0
    );

    // PSE smartLoader

    const char *smartLoader_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "SmartLoaderArm64Linux",
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
                OP_BUS_CONNECT(pBus_b, "mport", .addrLo=0x0ULL, .addrHi=0xffffffffULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS64_SET("physicalbase", 0x80000000ULL)
            ,OP_PARAM_STRING_SET("command", "console=ttyAMA0 earlyprintk=pl011,0x1c090000 nokaslr")
        )
    );

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

static optNetPortInfo netPortSpecs[] = {
    {
        .name        = "directReadP",
        .description = 0,
    },
    {
        .name        = "directWriteP",
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
        .name        = "phyEthernetPort",
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
        .vendor  = "arm.ovpworld.org",
        .library = "module",
        .name    = "ARMv8-A-FMv1",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
    .busPortSpecsCB       = moduleBusPortIterator,
    .netPortSpecsCB       = moduleNetPortIterator,
    .packetnetPortSpecsCB = modulePacketnetPortIterator,
};

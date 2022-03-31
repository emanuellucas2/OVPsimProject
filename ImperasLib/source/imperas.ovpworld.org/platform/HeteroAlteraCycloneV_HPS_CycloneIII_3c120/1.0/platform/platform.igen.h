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
    opDocTextAdd(doc_11_node, "This platform merges the Altera Cyclone V (ARM) and Cyclone III (Nios_II) processor systems");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "Peripherals are modeled only to the extent required to boot and run Operating Systems such as Linux.");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "Altera Cyclone III 3c120 Reference Guide and Cyclone V Handbook Volume 3: Hard Processor System Technical Reference Manual cv_5v4 2013.12.30");


    // Bus smbus_HPS

    optBusP smbus_HPS_b = opBusNew(mi, "smbus_HPS", 32, 0, 0);


    // Bus smbus_3c120

    optBusP smbus_3c120_b = opBusNew(mi, "smbus_3c120", 32, 0, 0);


    // Bus iobus_3c120

    optBusP iobus_3c120_b = opBusNew(mi, "iobus_3c120", 32, 0, 0);


    // Bus dbus_3c120

    optBusP dbus_3c120_b = opBusNew(mi, "dbus_3c120", 32, 0, 0);


    // Bus ibus_3c120

    optBusP ibus_3c120_b = opBusNew(mi, "ibus_3c120", 32, 0, 0);


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
    optNetP irq10_n = opNetNew(mi, "irq10", 0, 0);
    optNetP irq1_n = opNetNew(mi, "irq1", 0, 0);
    optNetP irq11_n = opNetNew(mi, "irq11", 0, 0);

    // Processor cpu_A9MPx2

    const char *cpu_A9MPx2_path = opVLNVString(
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
        cpu_A9MPx2_path,
        "cpu_A9MPx2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_HPS_b, "INSTRUCTION"),
                OP_BUS_CONNECT(smbus_HPS_b, "DATA")
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


    // Processor cpu_Nios_II

    const char *cpu_Nios_II_path = opVLNVString(
        0, // use the default VLNV path
        "altera.ovpworld.org",
        0,
        "nios_ii",
        "1.0",
        OP_PROCESSOR,
        OP_VLNV_PRINT
    );

    opProcessorNew(
        mi,
        cpu_Nios_II_path,
        "cpu_Nios_II",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(ibus_3c120_b, "INSTRUCTION", .addrLo=0x0ULL, .addrHi=0xffffffffULL),
                OP_BUS_CONNECT(dbus_3c120_b, "DATA", .addrLo=0x0ULL, .addrHi=0xffffffffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(irq10_n, "d_irq10"),
                OP_NET_CONNECT(irq1_n, "d_irq1"),
                OP_NET_CONNECT(irq11_n, "d_irq11")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_UNS32_SET("cpuid", 1)
            ,OP_PARAM_DOUBLE_SET("mips", 125.0)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_ENUM_SET("variant", "Nios_II_F")
            ,OP_PARAM_UNS32_SET("BREAK_VECTOR", 0xc7fff820)
            ,OP_PARAM_UNS32_SET("EXCEPTION_VECTOR", 0xd0000020)
            ,OP_PARAM_UNS32_SET("RESET_VECTOR", 0xc2800000)
            ,OP_PARAM_UNS32_SET("FAST_TLB_MISS_EXCEPTION_VECTOR", 0xc7fff400)
            ,OP_PARAM_BOOL_SET("HW_DIVIDE", 1)
            ,OP_PARAM_BOOL_SET("HW_MULTIPLY", 1)
            ,OP_PARAM_BOOL_SET("HW_MULX", 0)
            ,OP_PARAM_BOOL_SET("INCLUDE_MMU", 1)
            ,OP_PARAM_STRING_SET("MMU_TLB_SET_ASSOCIATIVITY", "16")
            ,OP_PARAM_STRING_SET("MMU_TLB_ENTRIES", "128")
            ,OP_PARAM_UNS32_SET("MMU_PID_BITS", 8)
            ,OP_PARAM_UNS32_SET("DATA_ADDR_WIDTH", 29)
            ,OP_PARAM_UNS32_SET("INST_ADDR_WIDTH", 29)
            ,OP_PARAM_BOOL_SET("TEST_HALT_EXIT", 1)
            ,OP_PARAM_BOOL_SET("EXCEPTION_EXTRA_INFORMATION", 1)
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
                OP_BUS_CONNECT(smbus_HPS_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x3fffffffULL)
            )
        ),
        0
    );

    // Memory pb_cpu_to_ddr2_bot

    opMemoryNew(
        mi,
        "pb_cpu_to_ddr2_bot",
        OP_PRIV_RWX,
        (0x17ffffffULL) - (0x10000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_3c120_b, "sp1", .slave=1, .addrLo=0x10000000ULL, .addrHi=0x17ffffffULL)
            )
        ),
        0
    );

    // Memory tlb_miss_ram_1k

    opMemoryNew(
        mi,
        "tlb_miss_ram_1k",
        OP_PRIV_RWX,
        (0x7fff7ffULL) - (0x7fff400ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_3c120_b, "sp1", .slave=1, .addrLo=0x7fff400ULL, .addrHi=0x7fff7ffULL)
            )
        ),
        0
    );

    // Memory flash_mem_64m

    opMemoryNew(
        mi,
        "flash_mem_64m",
        OP_PRIV_RWX,
        (0x3ffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_3c120_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x3ffffffULL)
            )
        ),
        0
    );

    // Bridge pb_ibus_to_smbus_3c120

    opBridgeNew(
        mi,
        "pb_ibus_to_smbus_3c120",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_3c120_b, "mp1", .addrLo=0x0ULL, .addrHi=0xffffffffULL),
                OP_BUS_CONNECT(ibus_3c120_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0xffffffffULL)
            )
        ),
        0
    );

    // Bridge pb_dbus_to_smbus_3c120_1

    opBridgeNew(
        mi,
        "pb_dbus_to_smbus_3c120_1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_3c120_b, "mp1", .addrLo=0x0ULL, .addrHi=0x7ffffffULL),
                OP_BUS_CONNECT(dbus_3c120_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x7ffffffULL)
            )
        ),
        0
    );

    // Bridge pb_dbus_to_smbus_3c120_2

    opBridgeNew(
        mi,
        "pb_dbus_to_smbus_3c120_2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_3c120_b, "mp1", .addrLo=0x8800000ULL, .addrHi=0xffffffffULL),
                OP_BUS_CONNECT(dbus_3c120_b, "sp1", .slave=1, .addrLo=0x8800000ULL, .addrHi=0xffffffffULL)
            )
        ),
        0
    );

    // Bridge pb_cpu_to_io

    opBridgeNew(
        mi,
        "pb_cpu_to_io",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(iobus_3c120_b, "mp1", .addrLo=0x0ULL, .addrHi=0x7fffffULL),
                OP_BUS_CONNECT(dbus_3c120_b, "sp1", .slave=1, .addrLo=0x8000000ULL, .addrHi=0x87fffffULL)
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
                OP_BUS_CONNECT(smbus_HPS_b, "bport1", .slave=1, .addrLo=0xfffef000ULL, .addrHi=0xfffeffffULL)
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
                OP_BUS_CONNECT(smbus_HPS_b, "bport1", .slave=1, .addrLo=0xffc08000ULL, .addrHi=0xffc08fffULL)
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
                OP_BUS_CONNECT(smbus_HPS_b, "bport1", .slave=1, .addrLo=0xffc09000ULL, .addrHi=0xffc09fffULL)
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
                OP_BUS_CONNECT(smbus_HPS_b, "bport1", .slave=1, .addrLo=0xffd00000ULL, .addrHi=0xffd00fffULL)
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
                OP_BUS_CONNECT(smbus_HPS_b, "bport1", .slave=1, .addrLo=0xffd01000ULL, .addrHi=0xffd01fffULL)
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
                OP_BUS_CONNECT(smbus_HPS_b, "bport1", .slave=1, .addrLo=0xffc02000ULL, .addrHi=0xffc02fffULL)
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
                OP_BUS_CONNECT(smbus_HPS_b, "bport1", .slave=1, .addrLo=0xffc03000ULL, .addrHi=0xffc03fffULL)
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
                OP_BUS_CONNECT(smbus_HPS_b, "bport1", .slave=1, .addrLo=0xffd05000ULL, .addrHi=0xffd05fffULL)
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
                OP_BUS_CONNECT(smbus_HPS_b, "bport1", .slave=1, .dynamic=1)
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
                OP_BUS_CONNECT(smbus_HPS_b, "bport1", .slave=1, .dynamic=1)
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
                OP_BUS_CONNECT(smbus_HPS_b, "bport1", .slave=1, .dynamic=1)
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
                OP_BUS_CONNECT(smbus_HPS_b, "bport1", .slave=1, .dynamic=1)
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
                OP_BUS_CONNECT(smbus_HPS_b, "bport1", .slave=1, .dynamic=1)
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
                OP_BUS_CONNECT(smbus_HPS_b, "bport1", .slave=1, .dynamic=1)
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
                OP_BUS_CONNECT(smbus_HPS_b, "bport1", .slave=1, .dynamic=1)
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
                OP_BUS_CONNECT(smbus_HPS_b, "mport", .addrLo=0x0ULL, .addrHi=0xffffffffULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("boardid", 0xffffffff)
            ,OP_PARAM_STRING_SET("kernel", "zImage")
            ,OP_PARAM_STRING_SET("initrd", "fs.img")
            ,OP_PARAM_STRING_SET("command", "mem=1024M console=ttyS0")
            ,OP_PARAM_UNS32_SET("physicalbase", 0x0)
            ,OP_PARAM_UNS32_SET("memsize", 0x40000000)
            ,OP_PARAM_BOOL_SET("disable", 0)
        )
    );

    // PSE uart_s1

    const char *uart_s1_path = opVLNVString(
        0, // use the default VLNV path
        "altera.ovpworld.org",
        0,
        "Uart",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart_s1_path,
        "uart_s1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(iobus_3c120_b, "sp1", .slave=1, .addrLo=0x4c80ULL, .addrHi=0x4c9fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(irq10_n, "irq")
            )
        ),
        0
    );

    // PSE sysid

    const char *sysid_path = opVLNVString(
        0, // use the default VLNV path
        "altera.ovpworld.org",
        0,
        "SystemIDCore",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        sysid_path,
        "sysid",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(iobus_3c120_b, "sp1", .slave=1, .addrLo=0x4d40ULL, .addrHi=0x4d47ULL)
            )
        ),
        0
    );

    // PSE jtag_uart

    const char *jtag_uart_path = opVLNVString(
        0, // use the default VLNV path
        "altera.ovpworld.org",
        0,
        "JtagUart",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        jtag_uart_path,
        "jtag_uart",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(iobus_3c120_b, "sp1", .slave=1, .addrLo=0x4d50ULL, .addrHi=0x4d57ULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(irq1_n, "irq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("writeIRQThreshold", 8)
            ,OP_PARAM_UNS32_SET("readIRQThreshold", 8)
            ,OP_PARAM_UNS32_SET("writeBufferDepth", 64)
            ,OP_PARAM_UNS32_SET("readBufferDepth", 64)
            ,OP_PARAM_BOOL_SET("console", 1)
            ,OP_PARAM_STRING_SET("outfile", "jtag_uart.log")
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
        )
    );

    // PSE timer_1ms

    const char *timer_1ms_path = opVLNVString(
        0, // use the default VLNV path
        "altera.ovpworld.org",
        0,
        "IntervalTimer32Core",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        timer_1ms_path,
        "timer_1ms",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(iobus_3c120_b, "sp1", .slave=1, .addrLo=0x400000ULL, .addrHi=0x400017ULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(irq11_n, "irq")
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
    .releaseStatus        = OP_IMPERAS,
    .purpose              = OP_PP_FIX,
    .visibility           = OP_VISIBLE,
    .vlnv          = {
        .vendor  = "imperas.ovpworld.org",
        .library = "platform",
        .name    = "HeteroAlteraCycloneV_HPS_CycloneIII_3c120",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

static void cmdParserAddUserArgs(optCmdParserP parser) {
    opCmdParserAdd(parser, "ZIMAGE"  , 0 , 0, 0                   , OP_FT_STRINGVAL     , &options.ZIMAGE, "Linux zImage file to load using smartLoader", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "ZIMAGEADDR", 0 , 0, 0                   , OP_FT_UNS64VAL      , &options.ZIMAGEADDR, "Physical address to load zImage file (default 0x04000000)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "INITRD"  , 0 , 0, 0                   , OP_FT_STRINGVAL     , &options.INITRD, "Linux initrd file to load using smartLoader", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "INITRDADDR", 0 , 0, 0                   , OP_FT_UNS64VAL      , &options.INITRDADDR, "Physical address to load initrd file (default 0x06000000)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "LINUXSYM", 0 , 0, 0                   , OP_FT_STRINGVAL     , &options.LINUXSYM, "Linux ELF file with symbolic debug info (CpuManger only)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "BOARDID" , 0 , 0, 0                   , OP_FT_INT32VAL      , &options.BOARDID, "Value to pass to Linux as the boardid (default (0xffffffff)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "LINUXMEM", 0 , 0, 0                   , OP_FT_UNS64VAL      , &options.LINUXMEM, "Amount of memory allocated to Linux (required in AMP mode)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "LINUXCMD", 0 , 0, 0                   , OP_FT_STRINGVAL     , &options.LINUXCMD, "Linux command line (default: 'mem=1024M console=ttyS0', with mem value adjusted if LINUXMEM or MEMSIZE specified)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "APP0"    , 0 , 0, 0                   , OP_FT_STRINGVAL     , &options.APP0, "ELF file to load on CPU0 instead of Linux (Precludes use of Linux options)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "APP1"    , 0 , 0, 0                   , OP_FT_STRINGVAL     , &options.APP1, "ELF file to load on CPU1 for AMP", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "BOOT"    , 0 , 0, 0                   , OP_FT_STRINGVAL     , &options.BOOT, "ELF file with boot code (both processors will start at its entry)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "IMAGE0"  , 0 , 0, 0                   , OP_FT_STRINGVAL     , &options.IMAGE0, "Image file to load on cpu0", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "IMAGE0ADDR", 0 , 0, 0                   , OP_FT_UNS64VAL      , &options.IMAGE0ADDR, "load address for image on cpu0 (IMAGE0 must be specified)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "IMAGE0SYM", 0 , 0, 0                   , OP_FT_STRINGVAL     , &options.IMAGE0SYM, "Elf file with symbolic debug info for image on cpu0 (IMAGE0 must be specified, CpuManger only)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "IMAGE1"  , 0 , 0, 0                   , OP_FT_STRINGVAL     , &options.IMAGE1, "Image file to load on cpu1", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "IMAGE1ADDR", 0 , 0, 0                   , OP_FT_UNS64VAL      , &options.IMAGE1ADDR, "Load address for image on cpu1 (IMAGE1 must be specified)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "IMAGE1SYM", 0 , 0, 0                   , OP_FT_STRINGVAL     , &options.IMAGE1SYM, "Elf file with symbolic debug info for image on cpu1 (IMAGE1 must be specified, CpuManger only)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "UART0PORT", 0 , 0, 0                   , OP_FT_STRINGVAL     , &options.UART0PORT, "Uart0 port: 'auto' for automatic console, 0 for simulator-chosen port, or number for specific port", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "UART1PORT", 0 , 0, 0                   , OP_FT_STRINGVAL     , &options.UART1PORT, "Uart1 port: 'auto' for automatic console, 0 for simulator-chosen port, or number for specific port", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "NIOSBOOT", 0 , 0, 0                   , OP_FT_STRINGVAL     , &options.NIOSBOOT, "vmlinux to load onto ", OP_AC_ALL, 0, 0);
}

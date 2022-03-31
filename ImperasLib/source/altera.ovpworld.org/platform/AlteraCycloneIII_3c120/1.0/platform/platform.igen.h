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
    opDocTextAdd(doc_11_node, "This platform models the Altera Cyclone III 3c120.\n\nThe processor is an Altera Nios_II procesor, Nios_II_F.");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "Peripherals are modeled only to the extent required to boot and run Operating Systems such as Linux.");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "Altera Cyclone III 3c120 Reference Guide");


    // Bus smbus

    optBusP smbus_b = opBusNew(mi, "smbus", 32, 0, 0);


    // Bus iobus

    optBusP iobus_b = opBusNew(mi, "iobus", 32, 0, 0);


    // Bus dbus

    optBusP dbus_b = opBusNew(mi, "dbus", 32, 0, 0);


    // Bus ibus

    optBusP ibus_b = opBusNew(mi, "ibus", 32, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP irq10_n = opNetNew(mi, "irq10", 0, 0);
    optNetP irq1_n = opNetNew(mi, "irq1", 0, 0);
    optNetP irq11_n = opNetNew(mi, "irq11", 0, 0);

    // Processor cpu

    const char *cpu_path = opVLNVString(
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
        cpu_path,
        "cpu",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(ibus_b, "INSTRUCTION", .addrLo=0x0ULL, .addrHi=0xffffffffULL),
                OP_BUS_CONNECT(dbus_b, "DATA", .addrLo=0x0ULL, .addrHi=0xffffffffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(irq10_n, "d_irq10"),
                OP_NET_CONNECT(irq1_n, "d_irq1"),
                OP_NET_CONNECT(irq11_n, "d_irq11")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
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


    // Memory pb_cpu_to_ddr2_bot

    opMemoryNew(
        mi,
        "pb_cpu_to_ddr2_bot",
        OP_PRIV_RWX,
        (0x17ffffffULL) - (0x10000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_b, "sp1", .slave=1, .addrLo=0x10000000ULL, .addrHi=0x17ffffffULL)
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
                OP_BUS_CONNECT(smbus_b, "sp1", .slave=1, .addrLo=0x7fff400ULL, .addrHi=0x7fff7ffULL)
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
                OP_BUS_CONNECT(smbus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x3ffffffULL)
            )
        ),
        0
    );

    // Bridge pb_ibus_to_smbus

    opBridgeNew(
        mi,
        "pb_ibus_to_smbus",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_b, "mp1", .addrLo=0x0ULL, .addrHi=0xffffffffULL),
                OP_BUS_CONNECT(ibus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0xffffffffULL)
            )
        ),
        0
    );

    // Bridge pb_dbus_to_smbus_1

    opBridgeNew(
        mi,
        "pb_dbus_to_smbus_1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_b, "mp1", .addrLo=0x0ULL, .addrHi=0x7ffffffULL),
                OP_BUS_CONNECT(dbus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x7ffffffULL)
            )
        ),
        0
    );

    // Bridge pb_dbus_to_smbus_2

    opBridgeNew(
        mi,
        "pb_dbus_to_smbus_2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_b, "mp1", .addrLo=0x8800000ULL, .addrHi=0xffffffffULL),
                OP_BUS_CONNECT(dbus_b, "sp1", .slave=1, .addrLo=0x8800000ULL, .addrHi=0xffffffffULL)
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
                OP_BUS_CONNECT(iobus_b, "mp1", .addrLo=0x0ULL, .addrHi=0x7fffffULL),
                OP_BUS_CONNECT(dbus_b, "sp1", .slave=1, .addrLo=0x8000000ULL, .addrHi=0x87fffffULL)
            )
        ),
        0
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
                OP_BUS_CONNECT(iobus_b, "sp1", .slave=1, .addrLo=0x4c80ULL, .addrHi=0x4c9fULL)
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
                OP_BUS_CONNECT(iobus_b, "sp1", .slave=1, .addrLo=0x4d40ULL, .addrHi=0x4d47ULL)
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
                OP_BUS_CONNECT(iobus_b, "sp1", .slave=1, .addrLo=0x4d50ULL, .addrHi=0x4d57ULL)
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
                OP_BUS_CONNECT(iobus_b, "sp1", .slave=1, .addrLo=0x400000ULL, .addrHi=0x400017ULL)
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
    .releaseStatus        = OP_OVP,
    .purpose              = OP_PP_BAREMETAL,
    .visibility           = OP_VISIBLE,
    .vlnv          = {
        .vendor  = "altera.ovpworld.org",
        .library = "platform",
        .name    = "AlteraCycloneIII_3c120",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

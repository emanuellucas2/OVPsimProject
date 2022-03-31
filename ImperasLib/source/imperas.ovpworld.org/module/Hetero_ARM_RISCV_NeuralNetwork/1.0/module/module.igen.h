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
    opDocTextAdd(doc1_node, "Platform for FreeRTOS bring");
    optDocNodeP doc_11_node = opModuleDocSectionAdd(mi, "Licensing");
    opDocTextAdd(doc_11_node, "Open Source Apache 2.0");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "Created to demostrate specific Nerual network applications");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "Alexnet and Minst Neural Networks");


    // Bus arm_bus

    optBusP arm_bus_b = opBusNew(mi, "arm_bus", 44, 0, 0);


    // Bus rv64_bus

    optBusP rv64_bus_b = opBusNew(mi, "rv64_bus", 38, 0, 0);


    // Bus shared_bus

    optBusP shared_bus_b = opBusNew(mi, "shared_bus", 38, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP MTimerInterrupt0_n = opNetNew(mi, "MTimerInterrupt0", 0, 0);
    optNetP MSWInterrupt0_n = opNetNew(mi, "MSWInterrupt0", 0, 0);
    optNetP MTimerInterrupt1_n = opNetNew(mi, "MTimerInterrupt1", 0, 0);
    optNetP MSWInterrupt1_n = opNetNew(mi, "MSWInterrupt1", 0, 0);
    optNetP MTimerInterrupt2_n = opNetNew(mi, "MTimerInterrupt2", 0, 0);
    optNetP MSWInterrupt2_n = opNetNew(mi, "MSWInterrupt2", 0, 0);
    optNetP MTimerInterrupt3_n = opNetNew(mi, "MTimerInterrupt3", 0, 0);
    optNetP MSWInterrupt3_n = opNetNew(mi, "MSWInterrupt3", 0, 0);
    optNetP MTimerInterrupt4_n = opNetNew(mi, "MTimerInterrupt4", 0, 0);
    optNetP MSWInterrupt4_n = opNetNew(mi, "MSWInterrupt4", 0, 0);
    optNetP MTimerInterrupt5_n = opNetNew(mi, "MTimerInterrupt5", 0, 0);
    optNetP MSWInterrupt5_n = opNetNew(mi, "MSWInterrupt5", 0, 0);
    optNetP MTimerInterrupt6_n = opNetNew(mi, "MTimerInterrupt6", 0, 0);
    optNetP MSWInterrupt6_n = opNetNew(mi, "MSWInterrupt6", 0, 0);
    optNetP MTimerInterrupt7_n = opNetNew(mi, "MTimerInterrupt7", 0, 0);
    optNetP MSWInterrupt7_n = opNetNew(mi, "MSWInterrupt7", 0, 0);
    optNetP MTimerInterrupt8_n = opNetNew(mi, "MTimerInterrupt8", 0, 0);
    optNetP MSWInterrupt8_n = opNetNew(mi, "MSWInterrupt8", 0, 0);
    optNetP MTimerInterrupt9_n = opNetNew(mi, "MTimerInterrupt9", 0, 0);
    optNetP MSWInterrupt9_n = opNetNew(mi, "MSWInterrupt9", 0, 0);
    optNetP MTimerInterrupt10_n = opNetNew(mi, "MTimerInterrupt10", 0, 0);
    optNetP MSWInterrupt10_n = opNetNew(mi, "MSWInterrupt10", 0, 0);
    optNetP MTimerInterrupt11_n = opNetNew(mi, "MTimerInterrupt11", 0, 0);
    optNetP MSWInterrupt11_n = opNetNew(mi, "MSWInterrupt11", 0, 0);
    optNetP MTimerInterrupt12_n = opNetNew(mi, "MTimerInterrupt12", 0, 0);
    optNetP MSWInterrupt12_n = opNetNew(mi, "MSWInterrupt12", 0, 0);
    optNetP MTimerInterrupt13_n = opNetNew(mi, "MTimerInterrupt13", 0, 0);
    optNetP MSWInterrupt13_n = opNetNew(mi, "MSWInterrupt13", 0, 0);
    optNetP MTimerInterrupt14_n = opNetNew(mi, "MTimerInterrupt14", 0, 0);
    optNetP MSWInterrupt14_n = opNetNew(mi, "MSWInterrupt14", 0, 0);
    optNetP MTimerInterrupt15_n = opNetNew(mi, "MTimerInterrupt15", 0, 0);
    optNetP MSWInterrupt15_n = opNetNew(mi, "MSWInterrupt15", 0, 0);
    optNetP MTimerInterrupt16_n = opNetNew(mi, "MTimerInterrupt16", 0, 0);
    optNetP MSWInterrupt16_n = opNetNew(mi, "MSWInterrupt16", 0, 0);

    // Processor arm_cpu

    const char *arm_cpu_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "arm",
        0,
        OP_PROCESSOR,
        OP_VLNV_PRINT
    );

    opProcessorNew(
        mi,
        arm_cpu_path,
        "arm_cpu",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(arm_bus_b, "INSTRUCTION"),
                OP_BUS_CONNECT(arm_bus_b, "DATA")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_BOOL_SET("enableimperasintercepts", 1)
            ,OP_PARAM_DOUBLE_SET("mips", 50)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_ENUM_SET("variant", "Cortex-A57MPx1")
            ,OP_PARAM_ENUM_SET("compatibility", "ISA")
            ,OP_PARAM_BOOL_SET("showHiddenRegs", 0)
        )
    );


    // Processor rv64_cpu

    const char *rv64_cpu_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "processor",
        "riscv",
        "1.0",
        OP_PROCESSOR,
        OP_VLNV_PRINT
    );

    opProcessorNew(
        mi,
        rv64_cpu_path,
        "rv64_cpu",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(rv64_bus_b, "INSTRUCTION"),
                OP_BUS_CONNECT(rv64_bus_b, "DATA")
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(MTimerInterrupt0_n, "hart0_MTimerInterrupt"),
                OP_NET_CONNECT(MSWInterrupt0_n, "hart0_MSWInterrupt"),
                OP_NET_CONNECT(MTimerInterrupt1_n, "hart1_MTimerInterrupt"),
                OP_NET_CONNECT(MSWInterrupt1_n, "hart1_MSWInterrupt"),
                OP_NET_CONNECT(MTimerInterrupt2_n, "hart2_MTimerInterrupt"),
                OP_NET_CONNECT(MSWInterrupt2_n, "hart2_MSWInterrupt"),
                OP_NET_CONNECT(MTimerInterrupt3_n, "hart3_MTimerInterrupt"),
                OP_NET_CONNECT(MSWInterrupt3_n, "hart3_MSWInterrupt"),
                OP_NET_CONNECT(MTimerInterrupt4_n, "hart4_MTimerInterrupt"),
                OP_NET_CONNECT(MSWInterrupt4_n, "hart4_MSWInterrupt"),
                OP_NET_CONNECT(MTimerInterrupt5_n, "hart5_MTimerInterrupt"),
                OP_NET_CONNECT(MSWInterrupt5_n, "hart5_MSWInterrupt"),
                OP_NET_CONNECT(MTimerInterrupt6_n, "hart6_MTimerInterrupt"),
                OP_NET_CONNECT(MSWInterrupt6_n, "hart6_MSWInterrupt"),
                OP_NET_CONNECT(MTimerInterrupt7_n, "hart7_MTimerInterrupt"),
                OP_NET_CONNECT(MSWInterrupt7_n, "hart7_MSWInterrupt"),
                OP_NET_CONNECT(MTimerInterrupt8_n, "hart8_MTimerInterrupt"),
                OP_NET_CONNECT(MSWInterrupt8_n, "hart8_MSWInterrupt"),
                OP_NET_CONNECT(MTimerInterrupt9_n, "hart9_MTimerInterrupt"),
                OP_NET_CONNECT(MSWInterrupt9_n, "hart9_MSWInterrupt"),
                OP_NET_CONNECT(MTimerInterrupt10_n, "hart10_MTimerInterrupt"),
                OP_NET_CONNECT(MSWInterrupt10_n, "hart10_MSWInterrupt"),
                OP_NET_CONNECT(MTimerInterrupt11_n, "hart11_MTimerInterrupt"),
                OP_NET_CONNECT(MSWInterrupt11_n, "hart11_MSWInterrupt"),
                OP_NET_CONNECT(MTimerInterrupt12_n, "hart12_MTimerInterrupt"),
                OP_NET_CONNECT(MSWInterrupt12_n, "hart12_MSWInterrupt"),
                OP_NET_CONNECT(MTimerInterrupt13_n, "hart13_MTimerInterrupt"),
                OP_NET_CONNECT(MSWInterrupt13_n, "hart13_MSWInterrupt"),
                OP_NET_CONNECT(MTimerInterrupt14_n, "hart14_MTimerInterrupt"),
                OP_NET_CONNECT(MSWInterrupt14_n, "hart14_MSWInterrupt"),
                OP_NET_CONNECT(MTimerInterrupt15_n, "hart15_MTimerInterrupt"),
                OP_NET_CONNECT(MSWInterrupt15_n, "hart15_MSWInterrupt"),
                OP_NET_CONNECT(MTimerInterrupt16_n, "hart16_MTimerInterrupt"),
                OP_NET_CONNECT(MSWInterrupt16_n, "hart16_MSWInterrupt")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_UNS32_SET("cpuid", 1)
            ,OP_PARAM_DOUBLE_SET("mips", 200)
            ,OP_PARAM_ENUM_SET("variant", "U54")
            ,OP_PARAM_UNS32_SET("local_int_num", 48)
            ,OP_PARAM_UNS32_SET("numHarts", 17)
            ,OP_PARAM_BOOL_SET("wfi_is_nop", 0)
            ,OP_PARAM_UNS32_SET("mstatus_FS", 1)
        )
    );


    // Memory arm_ram

    opMemoryNew(
        mi,
        "arm_ram",
        OP_PRIV_RWX,
        (0xfffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(arm_bus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0xfffffffULL)
            )
        ),
        0
    );

    // Memory rv64_ram

    opMemoryNew(
        mi,
        "rv64_ram",
        OP_PRIV_RWX,
        (0xfffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(rv64_bus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0xfffffffULL)
            )
        ),
        0
    );

    // Memory shared_ram

    opMemoryNew(
        mi,
        "shared_ram",
        OP_PRIV_RWX,
        (0x2fffffffULL) - (0x20000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(shared_bus_b, "sp1", .slave=1, .addrLo=0x20000000ULL, .addrHi=0x2fffffffULL)
            )
        ),
        0
    );

    // Memory cpuload

    opMemoryNew(
        mi,
        "cpuload",
        OP_PRIV_RWX,
        (0x300300ffULL) - (0x30030000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(shared_bus_b, "sp1", .slave=1, .addrLo=0x30030000ULL, .addrHi=0x300300ffULL)
            )
        ),
        0
    );

    // Bridge arm_bridge

    opBridgeNew(
        mi,
        "arm_bridge",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(shared_bus_b, "mp", .addrLo=0x20000000ULL, .addrHi=0x3fffffffULL),
                OP_BUS_CONNECT(arm_bus_b, "sp", .slave=1, .addrLo=0x20000000ULL, .addrHi=0x3fffffffULL)
            )
        ),
        0
    );

    // Bridge rv64_bridge

    opBridgeNew(
        mi,
        "rv64_bridge",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(shared_bus_b, "mp", .addrLo=0x20000000ULL, .addrHi=0x3fffffffULL),
                OP_BUS_CONNECT(rv64_bus_b, "sp", .slave=1, .addrLo=0x20000000ULL, .addrHi=0x3fffffffULL)
            )
        ),
        0
    );

    // PSE fb

    const char *fb_path = opVLNVString(
        0, // use the default VLNV path
        "imperas.ovpworld.org",
        "peripheral",
        "frameBuffer",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        fb_path,
        "fb",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(arm_bus_b, "sp", .slave=1, .addrLo=0x10000000ULL, .addrHi=0x10000fffULL),
                OP_BUS_CONNECT(arm_bus_b, "mp", .slave=1, .dynamic=1)
            )
        ),
        0
    );

    // PSE uart0

    const char *uart0_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "UART",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart0_path,
        "uart0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(shared_bus_b, "bport1", .slave=1, .addrLo=0x30010000ULL, .addrHi=0x3001001bULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("ychars", 30)
            ,OP_PARAM_BOOL_SET("console", 1)
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
        )
    );

    // PSE uart1

    const char *uart1_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "UART",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart1_path,
        "uart1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(shared_bus_b, "bport1", .slave=1, .addrLo=0x30011000ULL, .addrHi=0x3001101bULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("ychars", 7)
        )
    );

    // PSE uart2

    const char *uart2_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "UART",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart2_path,
        "uart2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(shared_bus_b, "bport1", .slave=1, .addrLo=0x30012000ULL, .addrHi=0x3001201bULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("ychars", 7)
        )
    );

    // PSE uart3

    const char *uart3_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "UART",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart3_path,
        "uart3",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(shared_bus_b, "bport1", .slave=1, .addrLo=0x30013000ULL, .addrHi=0x3001301bULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("ychars", 7)
        )
    );

    // PSE uart4

    const char *uart4_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "UART",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart4_path,
        "uart4",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(shared_bus_b, "bport1", .slave=1, .addrLo=0x30014000ULL, .addrHi=0x3001401bULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("ychars", 7)
        )
    );

    // PSE uart5

    const char *uart5_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "UART",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart5_path,
        "uart5",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(shared_bus_b, "bport1", .slave=1, .addrLo=0x30015000ULL, .addrHi=0x3001501bULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("ychars", 7)
        )
    );

    // PSE uart6

    const char *uart6_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "UART",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart6_path,
        "uart6",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(shared_bus_b, "bport1", .slave=1, .addrLo=0x30016000ULL, .addrHi=0x3001601bULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("ychars", 7)
        )
    );

    // PSE uart7

    const char *uart7_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "UART",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart7_path,
        "uart7",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(shared_bus_b, "bport1", .slave=1, .addrLo=0x30017000ULL, .addrHi=0x3001701bULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("ychars", 7)
        )
    );

    // PSE uart8

    const char *uart8_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "UART",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart8_path,
        "uart8",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(shared_bus_b, "bport1", .slave=1, .addrLo=0x30018000ULL, .addrHi=0x3001801bULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("ychars", 7)
        )
    );

    // PSE uart9

    const char *uart9_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "UART",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart9_path,
        "uart9",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(shared_bus_b, "bport1", .slave=1, .addrLo=0x30019000ULL, .addrHi=0x3001901bULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("ychars", 7)
        )
    );

    // PSE uart10

    const char *uart10_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "UART",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart10_path,
        "uart10",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(shared_bus_b, "bport1", .slave=1, .addrLo=0x3001a000ULL, .addrHi=0x3001a01bULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("ychars", 30)
            ,OP_PARAM_BOOL_SET("console", 1)
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
        )
    );

    // PSE uart11

    const char *uart11_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "UART",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart11_path,
        "uart11",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(shared_bus_b, "bport1", .slave=1, .addrLo=0x3001b000ULL, .addrHi=0x3001b01bULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("ychars", 7)
        )
    );

    // PSE uart12

    const char *uart12_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "UART",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart12_path,
        "uart12",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(shared_bus_b, "bport1", .slave=1, .addrLo=0x3001c000ULL, .addrHi=0x3001c01bULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("ychars", 7)
        )
    );

    // PSE uart13

    const char *uart13_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "UART",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart13_path,
        "uart13",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(shared_bus_b, "bport1", .slave=1, .addrLo=0x3001d000ULL, .addrHi=0x3001d01bULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("ychars", 7)
        )
    );

    // PSE uart14

    const char *uart14_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "UART",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart14_path,
        "uart14",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(shared_bus_b, "bport1", .slave=1, .addrLo=0x3001e000ULL, .addrHi=0x3001e01bULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("ychars", 7)
        )
    );

    // PSE uart15

    const char *uart15_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "UART",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart15_path,
        "uart15",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(shared_bus_b, "bport1", .slave=1, .addrLo=0x3001f000ULL, .addrHi=0x3001f01bULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("ychars", 7)
        )
    );

    // PSE uart16

    const char *uart16_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "UART",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart16_path,
        "uart16",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(shared_bus_b, "bport1", .slave=1, .addrLo=0x30020000ULL, .addrHi=0x3002001bULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("ychars", 7)
        )
    );

    // PSE uart17

    const char *uart17_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "UART",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart17_path,
        "uart17",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(shared_bus_b, "bport1", .slave=1, .addrLo=0x30021000ULL, .addrHi=0x3002101bULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("ychars", 20)
            ,OP_PARAM_BOOL_SET("console", 1)
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
        )
    );

    // PSE usecCount

    const char *usecCount_path = opVLNVString(
        0, // use the default VLNV path
        "imperas.ovpworld.org",
        "peripheral",
        "usecCounter",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        usecCount_path,
        "usecCount",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(shared_bus_b, "bport1", .slave=1, .addrLo=0x30040000ULL, .addrHi=0x30040003ULL)
            )
        ),
        0
    );

    // PSE clint

    const char *clint_path = opVLNVString(
        0, // use the default VLNV path
        "riscv.ovpworld.org",
        "peripheral",
        "CLINT",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        clint_path,
        "clint",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(shared_bus_b, "port0", .slave=1, .addrLo=0x30100000ULL, .addrHi=0x3010bfffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(MTimerInterrupt0_n, "MTimerInterrupt0"),
                OP_NET_CONNECT(MSWInterrupt0_n, "MSWInterrupt0"),
                OP_NET_CONNECT(MTimerInterrupt1_n, "MTimerInterrupt1"),
                OP_NET_CONNECT(MSWInterrupt1_n, "MSWInterrupt1"),
                OP_NET_CONNECT(MTimerInterrupt2_n, "MTimerInterrupt2"),
                OP_NET_CONNECT(MSWInterrupt2_n, "MSWInterrupt2"),
                OP_NET_CONNECT(MTimerInterrupt3_n, "MTimerInterrupt3"),
                OP_NET_CONNECT(MSWInterrupt3_n, "MSWInterrupt3"),
                OP_NET_CONNECT(MTimerInterrupt4_n, "MTimerInterrupt4"),
                OP_NET_CONNECT(MSWInterrupt4_n, "MSWInterrupt4"),
                OP_NET_CONNECT(MTimerInterrupt5_n, "MTimerInterrupt5"),
                OP_NET_CONNECT(MSWInterrupt5_n, "MSWInterrupt5"),
                OP_NET_CONNECT(MTimerInterrupt6_n, "MTimerInterrupt6"),
                OP_NET_CONNECT(MSWInterrupt6_n, "MSWInterrupt6"),
                OP_NET_CONNECT(MTimerInterrupt7_n, "MTimerInterrupt7"),
                OP_NET_CONNECT(MSWInterrupt7_n, "MSWInterrupt7"),
                OP_NET_CONNECT(MTimerInterrupt8_n, "MTimerInterrupt8"),
                OP_NET_CONNECT(MSWInterrupt8_n, "MSWInterrupt8"),
                OP_NET_CONNECT(MTimerInterrupt9_n, "MTimerInterrupt9"),
                OP_NET_CONNECT(MSWInterrupt9_n, "MSWInterrupt9"),
                OP_NET_CONNECT(MTimerInterrupt10_n, "MTimerInterrupt10"),
                OP_NET_CONNECT(MSWInterrupt10_n, "MSWInterrupt10"),
                OP_NET_CONNECT(MTimerInterrupt11_n, "MTimerInterrupt11"),
                OP_NET_CONNECT(MSWInterrupt11_n, "MSWInterrupt11"),
                OP_NET_CONNECT(MTimerInterrupt12_n, "MTimerInterrupt12"),
                OP_NET_CONNECT(MSWInterrupt12_n, "MSWInterrupt12"),
                OP_NET_CONNECT(MTimerInterrupt13_n, "MTimerInterrupt13"),
                OP_NET_CONNECT(MSWInterrupt13_n, "MSWInterrupt13"),
                OP_NET_CONNECT(MTimerInterrupt14_n, "MTimerInterrupt14"),
                OP_NET_CONNECT(MSWInterrupt14_n, "MSWInterrupt14"),
                OP_NET_CONNECT(MTimerInterrupt15_n, "MTimerInterrupt15"),
                OP_NET_CONNECT(MSWInterrupt15_n, "MSWInterrupt15"),
                OP_NET_CONNECT(MTimerInterrupt16_n, "MTimerInterrupt16"),
                OP_NET_CONNECT(MSWInterrupt16_n, "MSWInterrupt16")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("num_harts", 17)
            ,OP_PARAM_DOUBLE_SET("clockMHz", 1.0)
        )
    );

}

optModuleAttr modelAttrs = {
    .versionString        = OP_VERSION,
    .type                 = OP_MODULE,
    .name                 = MODULE_NAME,
    .objectSize           = sizeof(optModuleObject),
    .releaseStatus        = OP_IMPERAS,
    .purpose              = OP_PP_MODULE,
    .visibility           = OP_VISIBLE,
    .vlnv          = {
        .vendor  = "imperas.ovpworld.org",
        .library = "module",
        .name    = "Hetero_ARM_RISCV_NeuralNetwork",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

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
    opDocTextAdd(doc1_node, "Xilinx ML505 Reference Platform");
    optDocNodeP doc_11_node = opModuleDocSectionAdd(mi, "Licensing");
    opDocTextAdd(doc_11_node, "Open Source Apache 2.0");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "This platform provides a subset of the full platform functionality. It is provided to boot the Linux operating system.\n           Other software may be used but the operation cannot be guaranteed.");
    opDocTextAdd(doc_21_node, "Platform capable of booting linux");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "UG347 (v3.1.2) May 16, 2011");


    // Bus bus1

    optBusP bus1_b = opBusNew(mi, "bus1", 32, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP Interrupt_net_n = opNetNew(mi, "Interrupt_net", 0, 0);
    optNetP Interrupt_3_n = opNetNew(mi, "Interrupt_3", 0, 0);
    optNetP Interrupt_8_n = opNetNew(mi, "Interrupt_8", 0, 0);

    // Processor microblaze_0

    const char *microblaze_0_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "processor",
        "microblaze",
        "1.0",
        OP_PROCESSOR,
        OP_VLNV_PRINT
    );

    opProcessorNew(
        mi,
        microblaze_0_path,
        "microblaze_0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "INSTRUCTION"),
                OP_BUS_CONNECT(bus1_b, "DATA")
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(Interrupt_net_n, "Interrupt")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_DOUBLE_SET("mips", 125)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_BIG)
            ,OP_PARAM_UNS32_SET("C_USE_MMU", 3)
            ,OP_PARAM_UNS32_SET("C_MMU_ITLB_SIZE", 2)
            ,OP_PARAM_UNS32_SET("C_MMU_DTLB_SIZE", 4)
            ,OP_PARAM_UNS32_SET("C_MMU_TLB_ACCESS", 3)
            ,OP_PARAM_UNS32_SET("C_MMU_ZONES", 16)
            ,OP_PARAM_BOOL_SET("C_USE_EXTENDED_FSL_INSTR", 1)
            ,OP_PARAM_BOOL_SET("C_FSL_EXCEPTION", 1)
            ,OP_PARAM_UNS32_SET("C_USE_HW_MUL", 2)
            ,OP_PARAM_UNS32_SET("C_PVR", 2)
            ,OP_PARAM_BOOL_SET("C_OPCODE_0x0_ILLEGAL", 1)
            ,OP_PARAM_BOOL_SET("C_FPU_EXCEPTION", 1)
            ,OP_PARAM_BOOL_SET("C_UNALIGNED_EXCEPTIONS", 1)
            ,OP_PARAM_BOOL_SET("C_ILL_OPCODE_EXCEPTION", 1)
            ,OP_PARAM_BOOL_SET("C_DIV_ZERO_EXCEPTION", 1)
            ,OP_PARAM_UNS32_SET("C_INTERCONNECT", 1)
            ,OP_PARAM_BOOL_SET("C_USE_BARREL", 1)
            ,OP_PARAM_BOOL_SET("C_USE_DIV", 1)
            ,OP_PARAM_UNS32_SET("C_FSL_LINKS", 4)
            ,OP_PARAM_BOOL_SET("C_DEBUG_ENABLED", 1)
            ,OP_PARAM_BOOL_SET("C_I_LMB", 1)
            ,OP_PARAM_BOOL_SET("C_D_LMB", 1)
            ,OP_PARAM_UNS32_SET("C_USE_FPU", 2)
            ,OP_PARAM_BOOL_SET("C_USE_MSR_INSTR", 1)
            ,OP_PARAM_BOOL_SET("C_USE_PCMP_INSTR", 1)
            ,OP_PARAM_UNS32_SET("C_FAMILY", 12)
        )
    );


    // Memory BOOTMEM

    opMemoryNew(
        mi,
        "BOOTMEM",
        OP_PRIV_RWX,
        (0x1ffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x1ffffffULL)
            )
        ),
        0
    );

    // Memory DDR2_SDRAM

    opMemoryNew(
        mi,
        "DDR2_SDRAM",
        OP_PRIV_RWX,
        (0x9fffffffULL) - (0x90000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "sp1", .slave=1, .addrLo=0x90000000ULL, .addrHi=0x9fffffffULL)
            )
        ),
        0
    );

    // Memory UNKNOWN_PERIPH

    opMemoryNew(
        mi,
        "UNKNOWN_PERIPH",
        OP_PRIV_RWX,
        (0x8fffffffULL) - (0x8ffff000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "sp1", .slave=1, .addrLo=0x8ffff000ULL, .addrHi=0x8fffffffULL)
            )
        ),
        0
    );

    // PSE LEDs_8Bit

    const char *LEDs_8Bit_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        0,
        "xps-gpio",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        LEDs_8Bit_path,
        "LEDs_8Bit",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "plb", .slave=1, .addrLo=0x81400000ULL, .addrHi=0x8140ffffULL)
            )
        ),
        0
    );

    // PSE IIC_EEPROM

    const char *IIC_EEPROM_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        0,
        "xps-iic",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        IIC_EEPROM_path,
        "IIC_EEPROM",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "plb", .slave=1, .addrLo=0x81600000ULL, .addrHi=0x8160ffffULL)
            )
        ),
        0
    );

    // PSE xps_intc_0

    const char *xps_intc_0_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        0,
        "xps-intc",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        xps_intc_0_path,
        "xps_intc_0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "plb", .slave=1, .addrLo=0x81800000ULL, .addrHi=0x8180001fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(Interrupt_net_n, "Irq"),
                OP_NET_CONNECT(Interrupt_3_n, "Intr3"),
                OP_NET_CONNECT(Interrupt_8_n, "Intr8")
            )
        ),
        0
    );

    // PSE Hard_Ethernet_MAC

    const char *Hard_Ethernet_MAC_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        0,
        "xps-ll-temac",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        Hard_Ethernet_MAC_path,
        "Hard_Ethernet_MAC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "plb", .slave=1, .addrLo=0x81c00000ULL, .addrHi=0x81c0003fULL)
            )
        ),
        0
    );

    // PSE SysACE_CompactFlash

    const char *SysACE_CompactFlash_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        0,
        "xps-sysace",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        SysACE_CompactFlash_path,
        "SysACE_CompactFlash",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "plb", .slave=1, .addrLo=0x83600000ULL, .addrHi=0x8360ffffULL)
            )
        ),
        0
    );

    // PSE xps_timer_1

    const char *xps_timer_1_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        0,
        "xps-timer",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        xps_timer_1_path,
        "xps_timer_1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "plb", .slave=1, .addrLo=0x83c00000ULL, .addrHi=0x83c0001fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(Interrupt_3_n, "Interrupt")
            )
        ),
        0
    );

    // PSE RS232_Uart_1

    const char *RS232_Uart_1_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        0,
        "xps-uartlite",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        RS232_Uart_1_path,
        "RS232_Uart_1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "plb", .slave=1, .addrLo=0x84000000ULL, .addrHi=0x8400000fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(Interrupt_8_n, "Interrupt")
            )
        ),
        OP_PARAMS(
             OP_PARAM_STRING_SET("outfile", "RS232_Uart_1.log")
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
        )
    );

    // PSE debug_module

    const char *debug_module_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        0,
        "mdm",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        debug_module_path,
        "debug_module",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "plb", .slave=1, .addrLo=0x84400000ULL, .addrHi=0x8440ffffULL)
            )
        ),
        0
    );

    // PSE mpmc

    const char *mpmc_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        0,
        "mpmc",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        mpmc_path,
        "mpmc",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "plb", .slave=1, .addrLo=0x84600180ULL, .addrHi=0x846001ffULL)
            )
        ),
        0
    );

    // PSE mb_plb

    const char *mb_plb_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        0,
        "xps-mch-emc",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        mb_plb_path,
        "mb_plb",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "plb", .slave=1, .addrLo=0xa0000000ULL, .addrHi=0xa1ffffffULL)
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
        .vendor  = "xilinx.ovpworld.org",
        .library = "platform",
        .name    = "XilinxML505",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

static void cmdParserAddUserArgs(optCmdParserP parser) {
    opCmdParserAdd(parser, "kernel"  , 0 , 0, "user platform config", OP_FT_STRINGVAL     , &options.kernel, "The Linux Kernel image e.g. vmlinux", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "uartconsole", 0 , 0, "user platform config", OP_FT_BOOLVAL       , &options.uartconsole, "Open a console terminal on the UART", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "uartport", 0 , 0, "user platform config", OP_FT_UNS64VAL      , &options.uartport, "Set the port number to open on the UART and wait for connection", OP_AC_ALL, 0, 0);
}

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
    opDocTextAdd(doc_11_node, "This platform models the ARM INTEGRATOR CP development board.\nIt provides the peripherals required to boot and run Operating Systems such as Linux or Nucleus.\nThe main processor is an ARM, by default this is an ARM926EJ-S (Linux) but can be overriden; for example ARM920T (Nucleus).");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "No known limitations for executing Linux and Nucleus operating systems.");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "ARM Development Boards Integrator CP BaseBoard and Integrator Core Modules ARM9x6");


    // Bus bus1

    optBusP bus1_b = opBusNew(mi, "bus1", 32, 0, 0);


    // Bus membus

    optBusP membus_b = opBusNew(mi, "membus", 32, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP irq_n = opNetNew(mi, "irq", 0, 0);
    optNetP fiq_n = opNetNew(mi, "fiq", 0, 0);
    optNetP ir1_n = opNetNew(mi, "ir1", 0, 0);
    optNetP ir2_n = opNetNew(mi, "ir2", 0, 0);
    optNetP ir3_n = opNetNew(mi, "ir3", 0, 0);
    optNetP ir4_n = opNetNew(mi, "ir4", 0, 0);
    optNetP ir5_n = opNetNew(mi, "ir5", 0, 0);
    optNetP ir6_n = opNetNew(mi, "ir6", 0, 0);
    optNetP ir7_n = opNetNew(mi, "ir7", 0, 0);
    optNetP ir8_n = opNetNew(mi, "ir8", 0, 0);
    optNetP ir23_n = opNetNew(mi, "ir23", 0, 0);
    optNetP ir24_n = opNetNew(mi, "ir24", 0, 0);

    // Processor arm1

    const char *arm1_path = opVLNVString(
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
        arm1_path,
        "arm1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "INSTRUCTION"),
                OP_BUS_CONNECT(bus1_b, "DATA")
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(irq_n, "irq"),
                OP_NET_CONNECT(fiq_n, "fiq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_BOOL_SET("enableimperasintercepts", 1)
            ,OP_PARAM_DOUBLE_SET("mips", 200.0)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_ENUM_SET("variant", "ARM926EJ-S")
            ,OP_PARAM_ENUM_SET("compatibility", "ISA")
            ,OP_PARAM_BOOL_SET("showHiddenRegs", 0)
        )
    );


    // Memory ram1

    opMemoryNew(
        mi,
        "ram1",
        OP_PRIV_RWX,
        (0x7ffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(membus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x7ffffffULL)
            )
        ),
        0
    );

    // Memory ambaDummy

    opMemoryNew(
        mi,
        "ambaDummy",
        OP_PRIV_RWX,
        (0x1d000fffULL) - (0x1d000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "sp1", .slave=1, .addrLo=0x1d000000ULL, .addrHi=0x1d000fffULL)
            )
        ),
        0
    );

    // Bridge ram1Bridge

    opBridgeNew(
        mi,
        "ram1Bridge",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(membus_b, "mp", .addrLo=0x0ULL, .addrHi=0x7ffffffULL),
                OP_BUS_CONNECT(bus1_b, "sp", .slave=1, .addrLo=0x0ULL, .addrHi=0x7ffffffULL)
            )
        ),
        0
    );

    // Bridge ram2Bridge

    opBridgeNew(
        mi,
        "ram2Bridge",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(membus_b, "mp", .addrLo=0x0ULL, .addrHi=0x7ffffffULL),
                OP_BUS_CONNECT(bus1_b, "sp1", .slave=1, .addrLo=0x80000000ULL, .addrHi=0x87ffffffULL)
            )
        ),
        0
    );

    // PSE cm

    const char *cm_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "CoreModule9x6",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        cm_path,
        "cm",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "bport1", .slave=1, .addrLo=0x10000000ULL, .addrHi=0x10000fffULL)
            )
        ),
        0
    );

    // PSE pic1

    const char *pic1_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "IntICP",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        pic1_path,
        "pic1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "bport1", .slave=1, .addrLo=0x14000000ULL, .addrHi=0x14000fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(irq_n, "irq"),
                OP_NET_CONNECT(fiq_n, "fiq"),
                OP_NET_CONNECT(ir1_n, "ir1"),
                OP_NET_CONNECT(ir2_n, "ir2"),
                OP_NET_CONNECT(ir3_n, "ir3"),
                OP_NET_CONNECT(ir4_n, "ir4"),
                OP_NET_CONNECT(ir5_n, "ir5"),
                OP_NET_CONNECT(ir6_n, "ir6"),
                OP_NET_CONNECT(ir7_n, "ir7"),
                OP_NET_CONNECT(ir8_n, "ir8"),
                OP_NET_CONNECT(ir23_n, "ir23"),
                OP_NET_CONNECT(ir24_n, "ir24")
            )
        ),
        0
    );

    // PSE pic2

    const char *pic2_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "IntICP",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        pic2_path,
        "pic2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "bport1", .slave=1, .addrLo=0xca000000ULL, .addrHi=0xca000fffULL)
            )
        ),
        0
    );

    // PSE ethlan

    const char *ethlan_path = opVLNVString(
        0, // use the default VLNV path
        "smsc.ovpworld.org",
        0,
        "LAN9118",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ethlan_path,
        "ethlan",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "bport1", .slave=1, .addrLo=0xc8000000ULL, .addrHi=0xc8000fffULL)
            )
        ),
        0
    );

    // PSE pit

    const char *pit_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "IcpCounterTimer",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        pit_path,
        "pit",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "bport1", .slave=1, .addrLo=0x13000000ULL, .addrHi=0x13000fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir5_n, "irq0"),
                OP_NET_CONNECT(ir6_n, "irq1"),
                OP_NET_CONNECT(ir7_n, "irq2")
            )
        ),
        0
    );

    // PSE icp

    const char *icp_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "IcpControl",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        icp_path,
        "icp",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "bport1", .slave=1, .addrLo=0xcb000000ULL, .addrHi=0xcb00000fULL)
            )
        ),
        0
    );

    // PSE ld1

    const char *ld1_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "DebugLedAndDipSwitch",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ld1_path,
        "ld1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "bport1", .slave=1, .addrLo=0x1a000000ULL, .addrHi=0x1a000fffULL)
            )
        ),
        0
    );

    // PSE kb1

    const char *kb1_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "KbPL050",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        kb1_path,
        "kb1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "bport1", .slave=1, .addrLo=0x18000000ULL, .addrHi=0x18000fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir3_n, "irq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("isMouse", 0)
            ,OP_PARAM_BOOL_SET("grabDisable", 0)
        )
    );

    // PSE ms1

    const char *ms1_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "KbPL050",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ms1_path,
        "ms1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "bport1", .slave=1, .addrLo=0x19000000ULL, .addrHi=0x19000fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir4_n, "irq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("isMouse", 1)
            ,OP_PARAM_BOOL_SET("grabDisable", 1)
        )
    );

    // PSE rtc

    const char *rtc_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "RtcPL031",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        rtc_path,
        "rtc",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "bport1", .slave=1, .addrLo=0x15000000ULL, .addrHi=0x15000fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir8_n, "irq")
            )
        ),
        0
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
                OP_BUS_CONNECT(bus1_b, "bport1", .slave=1, .addrLo=0x16000000ULL, .addrHi=0x16000fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir1_n, "irq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_ENUM_SET("variant", "ARM")
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
                OP_BUS_CONNECT(bus1_b, "bport1", .slave=1, .addrLo=0x17000000ULL, .addrHi=0x17000fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir2_n, "irq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_ENUM_SET("variant", "ARM")
            ,OP_PARAM_STRING_SET("outfile", "uart2.log")
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
        )
    );

    // PSE mmci

    const char *mmci_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "MmciPL181",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        mmci_path,
        "mmci",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "bport1", .slave=1, .addrLo=0x1c000000ULL, .addrHi=0x1c000fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir23_n, "irq0"),
                OP_NET_CONNECT(ir24_n, "irq1")
            )
        ),
        0
    );

    // PSE lcd

    const char *lcd_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "LcdPL110",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        lcd_path,
        "lcd",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "bport1", .slave=1, .addrLo=0xc0000000ULL, .addrHi=0xc0000fffULL),
                OP_BUS_CONNECT(membus_b, "memory", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("busOffset", 0x80000000)
            ,OP_PARAM_UNS32_SET("scanDelay", 50000)
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
                OP_BUS_CONNECT(bus1_b, "mport", .addrLo=0x0ULL, .addrHi=0xffffffffULL)
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
        .vendor  = "arm.ovpworld.org",
        .library = "platform",
        .name    = "ArmIntegratorCP",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

static void cmdParserAddUserArgs(optCmdParserP parser) {
    opCmdParserAdd(parser, "kernel"  , 0 , 0, "user platform config Linux", OP_FT_STRINGVAL     , &options.kernel, "The Linux Kernel image e.g. zImage", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "ramdisk" , 0 , 0, "user platform config Linux", OP_FT_STRINGVAL     , &options.ramdisk, "Boot Linux Kernel from the specified ramdisk image e.g. fs.img", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "uartport", 0 , 0, "user platform config", OP_FT_UNS64VAL      , &options.uartport, "set the port number to open on the UART (uart1)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "uartconsole", 0 , 0, "user platform config", OP_FT_BOOLVAL       , &options.uartconsole, "open a console terminal on the UART (uart1)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "semihost", 0 , 0, "user platform config", OP_FT_STRINGVAL     , &options.semihost, "Specify a semihost library (full path)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "nographics", 0 , 0, "user platform config", OP_FT_BOOLVAL       , &options.nographics, "Disable the LCD graphics window.", OP_AC_ALL, 0, 0);
}

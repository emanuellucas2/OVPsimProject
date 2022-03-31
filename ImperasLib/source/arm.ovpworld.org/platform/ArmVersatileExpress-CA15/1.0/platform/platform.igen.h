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
    opDocTextAdd(doc_11_node, "\nThis platform models the ARM Versatile Express development board with a CoreTile Express A15x2 (V2P-CA15) Daughterboard.\nSee the ARM documents DUI0447G_v2m_p1_trm.pdf and DUI0604E_v2p_ca15_tc1_trm.pdf for details of the hardware being modeled. \nNote this platform implements the motherboard's 'Cortex-A Series' memory map.\n\nThe default processor is an ARM Cortex-A15MPx2, which may be changed.\n");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "\nThis platform provides the peripherals required to boot and run Operating Systems such as Linux or Android.\nSome of the peripherals are register-only, non-functional models. See the individual peripheral model documentation for details.\n\nCoreSight software debug and trace ports are not modeled.\n\nRemap option not modeled.\n\nThe CLCD does not work in Linux\n");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "ARM Development Boards Versatile Express BaseBoard and ARM CoreTile Express A15x2");


    // Bus pBus

    optBusP pBus_b = opBusNew(mi, "pBus", 40, 0, 0);


    // Bus nor0bus

    optBusP nor0bus_b = opBusNew(mi, "nor0bus", 32, 0, 0);


    // Bus ddr2bus

    optBusP ddr2bus_b = opBusNew(mi, "ddr2bus", 32, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP ir2_n = opNetNew(mi, "ir2", 0, 0);
    optNetP ir3_n = opNetNew(mi, "ir3", 0, 0);
    optNetP ir4_n = opNetNew(mi, "ir4", 0, 0);
    optNetP ir5_n = opNetNew(mi, "ir5", 0, 0);
    optNetP ir6_n = opNetNew(mi, "ir6", 0, 0);
    optNetP ir7_n = opNetNew(mi, "ir7", 0, 0);
    optNetP ir8_n = opNetNew(mi, "ir8", 0, 0);
    optNetP ir9_n = opNetNew(mi, "ir9", 0, 0);
    optNetP ir10_n = opNetNew(mi, "ir10", 0, 0);
    optNetP ir12_n = opNetNew(mi, "ir12", 0, 0);
    optNetP ir13_n = opNetNew(mi, "ir13", 0, 0);
    optNetP ir14_n = opNetNew(mi, "ir14", 0, 0);
    optNetP ir15_n = opNetNew(mi, "ir15", 0, 0);
    optNetP ir16_n = opNetNew(mi, "ir16", 0, 0);
    optNetP wprot_n = opNetNew(mi, "wprot", 0, 0);
    optNetP cardin_n = opNetNew(mi, "cardin", 0, 0);

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
                OP_NET_CONNECT(ir2_n, "SPI34"),
                OP_NET_CONNECT(ir3_n, "SPI35"),
                OP_NET_CONNECT(ir4_n, "SPI36"),
                OP_NET_CONNECT(ir5_n, "SPI37"),
                OP_NET_CONNECT(ir6_n, "SPI38"),
                OP_NET_CONNECT(ir7_n, "SPI39"),
                OP_NET_CONNECT(ir8_n, "SPI40"),
                OP_NET_CONNECT(ir9_n, "SPI41"),
                OP_NET_CONNECT(ir10_n, "SPI42"),
                OP_NET_CONNECT(ir12_n, "SPI44"),
                OP_NET_CONNECT(ir13_n, "SPI45"),
                OP_NET_CONNECT(ir14_n, "SPI46"),
                OP_NET_CONNECT(ir15_n, "SPI47"),
                OP_NET_CONNECT(ir16_n, "SPI48")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_DOUBLE_SET("mips", 1000)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_ENUM_SET("variant", "Cortex-A15MPx2")
            ,OP_PARAM_ENUM_SET("compatibility", "ISA")
            ,OP_PARAM_BOOL_SET("UAL", 1)
            ,OP_PARAM_UNS32_SET("override_CBAR", 0x2c000000)
            ,OP_PARAM_UNS32_SET("override_GICD_TYPER_ITLines", 4)
        )
    );


    // Memory nor0

    opMemoryNew(
        mi,
        "nor0",
        OP_PRIV_RWX,
        (0x3ffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(nor0bus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x3ffffffULL)
            )
        ),
        0
    );

    // Memory nor1

    opMemoryNew(
        mi,
        "nor1",
        OP_PRIV_RWX,
        (0xfffffffULL) - (0xc000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0xc000000ULL, .addrHi=0xfffffffULL)
            )
        ),
        0
    );

    // Memory sram1

    opMemoryNew(
        mi,
        "sram1",
        OP_PRIV_RWX,
        (0x17ffffffULL) - (0x14000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x14000000ULL, .addrHi=0x17ffffffULL)
            )
        ),
        0
    );

    // Memory vram1

    opMemoryNew(
        mi,
        "vram1",
        OP_PRIV_RWX,
        (0x19ffffffULL) - (0x18000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x18000000ULL, .addrHi=0x19ffffffULL)
            )
        ),
        0
    );

    // Memory ddr2ram

    opMemoryNew(
        mi,
        "ddr2ram",
        OP_PRIV_RWX,
        (0x7fffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(ddr2bus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x7fffffffULL)
            )
        ),
        0
    );

    // Bridge nor0Bridge

    opBridgeNew(
        mi,
        "nor0Bridge",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(nor0bus_b, "mp", .addrLo=0x0ULL, .addrHi=0x3ffffffULL),
                OP_BUS_CONNECT(pBus_b, "sp", .slave=1, .addrLo=0x0ULL, .addrHi=0x3ffffffULL)
            )
        ),
        0
    );

    // Bridge nor0Remap

    opBridgeNew(
        mi,
        "nor0Remap",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(nor0bus_b, "mp", .addrLo=0x0ULL, .addrHi=0x3ffffffULL),
                OP_BUS_CONNECT(pBus_b, "sp", .slave=1, .addrLo=0x8000000ULL, .addrHi=0xbffffffULL)
            )
        ),
        0
    );

    // Bridge ddr2Bridge

    opBridgeNew(
        mi,
        "ddr2Bridge",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(ddr2bus_b, "mp", .addrLo=0x0ULL, .addrHi=0x7fffffffULL),
                OP_BUS_CONNECT(pBus_b, "sp", .slave=1, .addrLo=0x80000000ULL, .addrHi=0xffffffffULL)
            )
        ),
        0
    );

    // Bridge ddr2Remap1

    opBridgeNew(
        mi,
        "ddr2Remap1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(ddr2bus_b, "mp", .addrLo=0x0ULL, .addrHi=0x7fffffffULL),
                OP_BUS_CONNECT(pBus_b, "sp", .slave=1, .addrLo=0x800000000ULL, .addrHi=0x87fffffffULL)
            )
        ),
        0
    );

    // Bridge ddr2Remap2

    opBridgeNew(
        mi,
        "ddr2Remap2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(ddr2bus_b, "mp", .addrLo=0x0ULL, .addrHi=0x7fffffffULL),
                OP_BUS_CONNECT(pBus_b, "sp", .slave=1, .addrLo=0x880000000ULL, .addrHi=0x8ffffffffULL)
            )
        ),
        0
    );

    // Bridge ddr2Remap3

    opBridgeNew(
        mi,
        "ddr2Remap3",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(ddr2bus_b, "mp", .addrLo=0x0ULL, .addrHi=0x7fffffffULL),
                OP_BUS_CONNECT(pBus_b, "sp", .slave=1, .addrLo=0x8000000000ULL, .addrHi=0x807fffffffULL)
            )
        ),
        0
    );

    // Bridge ddr2Remap4

    opBridgeNew(
        mi,
        "ddr2Remap4",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(ddr2bus_b, "mp", .addrLo=0x0ULL, .addrHi=0x7fffffffULL),
                OP_BUS_CONNECT(pBus_b, "sp", .slave=1, .addrLo=0x8080000000ULL, .addrHi=0x80ffffffffULL)
            )
        ),
        0
    );

    // PSE eth0

    const char *eth0_path = opVLNVString(
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
        eth0_path,
        "eth0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1a000000ULL, .addrHi=0x1a000fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir15_n, "irq")
            )
        ),
        0
    );

    // PSE usb0

    const char *usb0_path = opVLNVString(
        0, // use the default VLNV path
        "philips.ovpworld.org",
        0,
        "ISP1761",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        usb0_path,
        "usb0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1b000000ULL, .addrHi=0x1b00ffffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir16_n, "hc_irq")
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
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(wprot_n, "wprot"),
                OP_NET_CONNECT(cardin_n, "cardin")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("SYS_PROCID0", 0x14000237)
        )
    );

    // PSE sysCtrl

    const char *sysCtrl_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "SysCtrlSP810",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        sysCtrl_path,
        "sysCtrl",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1c020000ULL, .addrHi=0x1c020fffULL)
            )
        ),
        0
    );

    // PSE aac1

    const char *aac1_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "AaciPL041",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        aac1_path,
        "aac1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1c040000ULL, .addrHi=0x1c040fffULL)
            )
        ),
        0
    );

    // PSE mmc1

    const char *mmc1_path = opVLNVString(
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
        mmc1_path,
        "mmc1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1c050000ULL, .addrHi=0x1c050fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir9_n, "irq0"),
                OP_NET_CONNECT(ir10_n, "irq1"),
                OP_NET_CONNECT(wprot_n, "wprot"),
                OP_NET_CONNECT(cardin_n, "cardin")
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1c060000ULL, .addrHi=0x1c060fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir12_n, "irq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("isKeyboard", 1)
            ,OP_PARAM_BOOL_SET("grabDisable", 1)
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1c070000ULL, .addrHi=0x1c070fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir13_n, "irq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("isMouse", 1)
            ,OP_PARAM_BOOL_SET("grabDisable", 1)
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
             OP_PARAM_ENUM_SET("variant", "ARM")
            ,OP_PARAM_STRING_SET("outfile", "uart0.log")
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
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
             OP_PARAM_ENUM_SET("variant", "ARM")
            ,OP_PARAM_STRING_SET("outfile", "uart1.log")
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
             OP_PARAM_ENUM_SET("variant", "ARM")
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
                OP_NET_CONNECT(ir8_n, "irq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_ENUM_SET("variant", "ARM")
        )
    );

    // PSE wdt1

    const char *wdt1_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "WdtSP805",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        wdt1_path,
        "wdt1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1c0f0000ULL, .addrHi=0x1c0f0fffULL)
            )
        ),
        0
    );

    // PSE timer01

    const char *timer01_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "TimerSP804",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        timer01_path,
        "timer01",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1c110000ULL, .addrHi=0x1c110fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir2_n, "irq")
            )
        ),
        0
    );

    // PSE timer23

    const char *timer23_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "TimerSP804",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        timer23_path,
        "timer23",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1c120000ULL, .addrHi=0x1c120fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir3_n, "irq")
            )
        ),
        0
    );

    // PSE dvi1

    const char *dvi1_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "SerBusDviRegs",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        dvi1_path,
        "dvi1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1c160000ULL, .addrHi=0x1c160fffULL)
            )
        ),
        0
    );

    // PSE rtc1

    const char *rtc1_path = opVLNVString(
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
        rtc1_path,
        "rtc1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1c170000ULL, .addrHi=0x1c170fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir4_n, "irq")
            )
        ),
        0
    );

    // PSE cf1

    const char *cf1_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "CompactFlashRegs",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        cf1_path,
        "cf1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1001a000ULL, .addrHi=0x1001afffULL)
            )
        ),
        0
    );

    // PSE uart4

    const char *uart4_path = opVLNVString(
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
        uart4_path,
        "uart4",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1c1b0000ULL, .addrHi=0x1c1b0fffULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_ENUM_SET("variant", "ARM")
        )
    );

    // PSE clcd

    const char *clcd_path = opVLNVString(
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
        clcd_path,
        "clcd",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1c1f0000ULL, .addrHi=0x1c1f0fffULL),
                OP_BUS_CONNECT(pBus_b, "memory", .slave=1, .dynamic=1)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir14_n, "irq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_ENUM_SET("resolution", "xga")
            ,OP_PARAM_BOOL_SET("noGraphics", 1)
        )
    );

    // PSE wdt2

    const char *wdt2_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "WdtSP805",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        wdt2_path,
        "wdt2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x2b060000ULL, .addrHi=0x2b060fffULL)
            )
        ),
        0
    );

    // PSE dmc1

    const char *dmc1_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "DMemCtrlPL341",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        dmc1_path,
        "dmc1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x2b0a0000ULL, .addrHi=0x2b0a0fffULL)
            )
        ),
        0
    );

    // PSE dma0

    const char *dma0_path = opVLNVString(
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
        dma0_path,
        "dma0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x7ffb0000)
        )
    );

    // PSE smc1

    const char *smc1_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "SMemCtrlPL354",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        smc1_path,
        "smc1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x7ffd0000ULL, .addrHi=0x7ffd0fffULL)
            )
        ),
        0
    );

    // PSE smartLoader

    const char *smartLoader_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "SmartLoaderArmLinux",
        "1.0",
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
             OP_PARAM_STRING_SET("command", "mem=2G@0x80000000 raid=noautodetect console=ttyAMA0,38400n8 devtmpfs.mount=0")
            ,OP_PARAM_UNS32_SET("physicalbase", 0x80000000)
            ,OP_PARAM_UNS32_SET("memsize", 0x80000000)
            ,OP_PARAM_UNS32_SET("boardid", 0x8e0)
        )
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
        .name    = "ArmVersatileExpress-CA15",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

static void cmdParserAddUserArgs(optCmdParserP parser) {
    opCmdParserAdd(parser, "zimage"  , 0 , 0, "userPlatformConfig", OP_FT_STRINGVAL     , &options.zimage, "Linux zImage file to load using smartLoader", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "zimageaddr", 0 , 0, "userPlatformConfig", OP_FT_UNS64VAL      , &options.zimageaddr, "Physical address to load zImage file (default:physicalbase + 0x00010000)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "initrd"  , 0 , 0, "userPlatformConfig", OP_FT_STRINGVAL     , &options.initrd, "Linux initrd file to load using smartLoader", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "initrdaddr", 0 , 0, "userPlatformConfig", OP_FT_UNS64VAL      , &options.initrdaddr, "Physical address to load initrd file (default:physicalbase + 0x00d00000)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "linuxsym", 0 , 0, "userPlatformConfig", OP_FT_STRINGVAL     , &options.linuxsym, "Linux ELF file with symbolic debug info (CpuManger only)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "linuxcmd", 0 , 0, "userPlatformConfig", OP_FT_STRINGVAL     , &options.linuxcmd, "Linux command line (default: 'mem=2G@0x80000000 raid=noautodetect console=ttyAMA0,38400n8 devtmpfs.mount=0", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "boardid" , 0 , 0, "userPlatformConfig", OP_FT_INT32VAL      , &options.boardid, "Value to pass to Linux as the boardid (default (0x8e0)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "linuxmem", 0 , 0, "userPlatformConfig", OP_FT_UNS64VAL      , &options.linuxmem, "Amount of memory allocated to Linux (required in AMP mode)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "boot"    , 0 , 0, "userPlatformConfig", OP_FT_STRINGVAL     , &options.boot, "Boot code object file (If specified, smartLoader will jump to this rather than zImage)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "image0"  , 0 , 0, "userPlatformConfig", OP_FT_STRINGVAL     , &options.image0, "Image file to load on cpu0", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "image0addr", 0 , 0, "userPlatformConfig", OP_FT_UNS64VAL      , &options.image0addr, "load address for image on cpu0 (IMAGE0 must be specified)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "image0sym", 0 , 0, "userPlatformConfig", OP_FT_STRINGVAL     , &options.image0sym, "Elf file with symbolic debug info for image on cpu0 (IMAGE0 must be specified, CpuManger only)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "image1"  , 0 , 0, "userPlatformConfig", OP_FT_STRINGVAL     , &options.image1, "Image file to load on cpu1 to n", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "image1addr", 0 , 0, "userPlatformConfig", OP_FT_UNS64VAL      , &options.image1addr, "Load address for image on cpu1 to n (IMAGE1 must be specified)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "image1sym", 0 , 0, "userPlatformConfig", OP_FT_STRINGVAL     , &options.image1sym, "Elf file with symbolic debug info for image on cpu1 to n (IMAGE1 must be specified, CpuManger only)", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "uart0port", 0 , 0, "userPlatformConfig", OP_FT_STRINGVAL     , &options.uart0port, "Uart0 port: 'auto' for automatic console, 0 for simulator chosen port #, or number of specific port", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "uart1port", 0 , 0, "userPlatformConfig", OP_FT_STRINGVAL     , &options.uart1port, "Uart1 port: 'auto' for automatic console, 0 for simulator chosen port #, or number of specific port", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "nographics", 0 , 0, "userPlatformConfig", OP_FT_BOOLVAL       , &options.nographics, "Inhibit opening of the lcd graphics window", OP_AC_ALL, 0, 0);
}

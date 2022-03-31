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
    opDocTextAdd(doc_11_node, "\nThis platform models the ARM Versatile Express development board with a CoreTile Express A9x4 (V2P-CA9) Daughterboard.\nSee the ARM documents DUI0447G_v2m_p1_trm.pdf and DUI0448G_v2p_ca9_trm.pdf for details of the hardware being modeled. \nNote this platform implements the motherboard's 'Legacy' memory map.\n\nThe default processor is an ARM Cortex-A9MPx4, which may be changed.");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "\nThis platform provides the peripherals required to boot and run Operating Systems such as Linux or Android.\nSome of the peripherals are register-only, non-functional models. See the individual peripheral model documentation for details.\n\nThe TrustZone Protection Controller (TZPC) is modeled, the TrustZone Address Space Controller (TZASPC) is not modeled.\n\nCoreSight software debug and trace ports are not modeled.\n");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "ARM Development Boards Versatile Express BaseBoard and ARM CoreTile Express A9x4");


    // Bus tzBus

    optBusP tzBus_b = opBusNew(mi, "tzBus", 41, 0, 0);


    // Bus pBus

    optBusP pBus_b = opBusNew(mi, "pBus", 32, 0, 0);


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
    optNetP ir44_n = opNetNew(mi, "ir44", 0, 0);
    optNetP ir48_n = opNetNew(mi, "ir48", 0, 0);
    optNetP cardin_n = opNetNew(mi, "cardin", 0, 0);
    optNetP wprot_n = opNetNew(mi, "wprot", 0, 0);
    optNetP tzpcdecprot1_4_n = opNetNew(mi, "tzpcdecprot1_4", 0, 0);
    optNetP tzpcdecprot0_0_n = opNetNew(mi, "tzpcdecprot0_0", 0, 0);
    optNetP tzpcdecprot0_1_n = opNetNew(mi, "tzpcdecprot0_1", 0, 0);
    optNetP tzpcdecprot0_2_n = opNetNew(mi, "tzpcdecprot0_2", 0, 0);
    optNetP tzpcdecprot0_4_n = opNetNew(mi, "tzpcdecprot0_4", 0, 0);
    optNetP tzpcdecprot0_5_n = opNetNew(mi, "tzpcdecprot0_5", 0, 0);
    optNetP tzpcdecprot0_9_n = opNetNew(mi, "tzpcdecprot0_9", 0, 0);
    optNetP tzpcdecprot0_10_n = opNetNew(mi, "tzpcdecprot0_10", 0, 0);

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
                OP_BUS_CONNECT(tzBus_b, "INSTRUCTION"),
                OP_BUS_CONNECT(tzBus_b, "DATA")
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
                OP_NET_CONNECT(ir16_n, "SPI48"),
                OP_NET_CONNECT(ir44_n, "SPI76"),
                OP_NET_CONNECT(ir48_n, "SPI80")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_DOUBLE_SET("mips", 448.0)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_ENUM_SET("variant", "Cortex-A9MPx4")
            ,OP_PARAM_ENUM_SET("compatibility", "ISA")
            ,OP_PARAM_BOOL_SET("UAL", 1)
            ,OP_PARAM_BOOL_SET("showHiddenRegs", 0)
            ,OP_PARAM_UNS32_SET("override_CBAR", 0x1e000000)
        )
    );


    // Memory sram1

    opMemoryNew(
        mi,
        "sram1",
        OP_PRIV_RWX,
        (0x4bffffffULL) - (0x48000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x48000000ULL, .addrHi=0x4bffffffULL)
            )
        ),
        0
    );

    // Memory vram1

    opMemoryNew(
        mi,
        "vram1",
        OP_PRIV_RWX,
        (0x4c7fffffULL) - (0x4c000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x4c000000ULL, .addrHi=0x4c7fffffULL)
            )
        ),
        0
    );

    // Memory ddr2ram

    opMemoryNew(
        mi,
        "ddr2ram",
        OP_PRIV_RWX,
        (0x3fffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(ddr2bus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x3fffffffULL)
            )
        ),
        0
    );

    // Bridge secure

    opBridgeNew(
        mi,
        "secure",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x0ULL, .addrHi=0xffffffffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x0ULL, .addrHi=0xffffffffULL)
            )
        ),
        0
    );

    // Bridge sysRegsNS

    opBridgeNew(
        mi,
        "sysRegsNS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x10000000ULL, .addrHi=0x10000fffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x10010000000ULL, .addrHi=0x10010000fffULL)
            )
        ),
        0
    );

    // Bridge sysCtrlNS

    opBridgeNew(
        mi,
        "sysCtrlNS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x10001000ULL, .addrHi=0x10001fffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x10010001000ULL, .addrHi=0x10010001fffULL)
            )
        ),
        0
    );

    // Bridge aac1NS

    opBridgeNew(
        mi,
        "aac1NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x10004000ULL, .addrHi=0x10004fffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x10010004000ULL, .addrHi=0x10010004fffULL)
            )
        ),
        0
    );

    // Bridge mmc1NS

    opBridgeNew(
        mi,
        "mmc1NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x10005000ULL, .addrHi=0x10005fffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x10010005000ULL, .addrHi=0x10010005fffULL)
            )
        ),
        0
    );

    // Bridge kb1NS

    opBridgeNew(
        mi,
        "kb1NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x10006000ULL, .addrHi=0x10006fffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x10010006000ULL, .addrHi=0x10010006fffULL)
            )
        ),
        0
    );

    // Bridge ms1NS

    opBridgeNew(
        mi,
        "ms1NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x10007000ULL, .addrHi=0x10007fffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x10010007000ULL, .addrHi=0x10010007fffULL)
            )
        ),
        0
    );

    // Bridge uart0NS

    opBridgeNew(
        mi,
        "uart0NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x10009000ULL, .addrHi=0x10009fffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x10010009000ULL, .addrHi=0x10010009fffULL)
            )
        ),
        0
    );

    // Bridge uart1NS

    opBridgeNew(
        mi,
        "uart1NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x1000a000ULL, .addrHi=0x1000afffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x1001000a000ULL, .addrHi=0x1001000afffULL)
            )
        ),
        0
    );

    // Bridge uart2NS

    opBridgeNew(
        mi,
        "uart2NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x1000b000ULL, .addrHi=0x1000bfffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x1001000b000ULL, .addrHi=0x1001000bfffULL)
            )
        ),
        0
    );

    // Bridge uart3NS

    opBridgeNew(
        mi,
        "uart3NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x1000c000ULL, .addrHi=0x1000cfffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x1001000c000ULL, .addrHi=0x1001000cfffULL)
            )
        ),
        0
    );

    // Bridge wdt1NS

    opBridgeNew(
        mi,
        "wdt1NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x1000f000ULL, .addrHi=0x1000ffffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x1001000f000ULL, .addrHi=0x1001000ffffULL)
            )
        ),
        0
    );

    // Bridge timer01NS

    opBridgeNew(
        mi,
        "timer01NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x10011000ULL, .addrHi=0x10011fffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x10010011000ULL, .addrHi=0x10010011fffULL)
            )
        ),
        0
    );

    // Bridge timer02NS

    opBridgeNew(
        mi,
        "timer02NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x10012000ULL, .addrHi=0x10012fffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x10010012000ULL, .addrHi=0x10010012fffULL)
            )
        ),
        0
    );

    // Bridge dvi1NS

    opBridgeNew(
        mi,
        "dvi1NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x10016000ULL, .addrHi=0x10016fffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x10010016000ULL, .addrHi=0x10010016fffULL)
            )
        ),
        0
    );

    // Bridge rtc1NS

    opBridgeNew(
        mi,
        "rtc1NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x10017000ULL, .addrHi=0x10017fffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x10010017000ULL, .addrHi=0x10010017fffULL)
            )
        ),
        0
    );

    // Bridge cf1NS

    opBridgeNew(
        mi,
        "cf1NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x1001a000ULL, .addrHi=0x1001afffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x1001001a000ULL, .addrHi=0x1001001afffULL)
            )
        ),
        0
    );

    // Bridge lcd2NS

    opBridgeNew(
        mi,
        "lcd2NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x1001f000ULL, .addrHi=0x1001ffffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x1001001f000ULL, .addrHi=0x1001001ffffULL)
            )
        ),
        0
    );

    // Bridge l2regsNS

    opBridgeNew(
        mi,
        "l2regsNS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x1e00a000ULL, .addrHi=0x1e00afffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x1001e00a000ULL, .addrHi=0x1001e00afffULL)
            )
        ),
        0
    );

    // Bridge nor0NS

    opBridgeNew(
        mi,
        "nor0NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x40000000ULL, .addrHi=0x43ffffffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x10040000000ULL, .addrHi=0x10043ffffffULL)
            )
        ),
        0
    );

    // Bridge nor1NS

    opBridgeNew(
        mi,
        "nor1NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x44000000ULL, .addrHi=0x47ffffffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x10044000000ULL, .addrHi=0x10047ffffffULL)
            )
        ),
        0
    );

    // Bridge sram1NS

    opBridgeNew(
        mi,
        "sram1NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x48000000ULL, .addrHi=0x4bffffffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x10048000000ULL, .addrHi=0x1004bffffffULL)
            )
        ),
        0
    );

    // Bridge vram1NS

    opBridgeNew(
        mi,
        "vram1NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x4c000000ULL, .addrHi=0x4c7fffffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x1004c000000ULL, .addrHi=0x1004c7fffffULL)
            )
        ),
        0
    );

    // Bridge eth0NS

    opBridgeNew(
        mi,
        "eth0NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x4e000000ULL, .addrHi=0x4e000fffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x1004e000000ULL, .addrHi=0x1004e000fffULL)
            )
        ),
        0
    );

    // Bridge usb0NS

    opBridgeNew(
        mi,
        "usb0NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x4f000000ULL, .addrHi=0x4f00ffffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x1004f000000ULL, .addrHi=0x1004f00ffffULL)
            )
        ),
        0
    );

    // Bridge ddr2RamBridge

    opBridgeNew(
        mi,
        "ddr2RamBridge",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(ddr2bus_b, "mp", .addrLo=0x0ULL, .addrHi=0x3fffffffULL),
                OP_BUS_CONNECT(pBus_b, "sp", .slave=1, .addrLo=0x60000000ULL, .addrHi=0x9fffffffULL)
            )
        ),
        0
    );

    // Bridge ddr2ramNS

    opBridgeNew(
        mi,
        "ddr2ramNS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x60000000ULL, .addrHi=0x9fffffffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x10060000000ULL, .addrHi=0x1009fffffffULL)
            )
        ),
        0
    );

    // Bridge ddr2RemapBridge

    opBridgeNew(
        mi,
        "ddr2RemapBridge",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(ddr2bus_b, "mp", .addrLo=0x20000000ULL, .addrHi=0x23ffffffULL),
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x3ffffffULL)
            )
        ),
        0
    );

    // Bridge ddr2RemapBridgeNS

    opBridgeNew(
        mi,
        "ddr2RemapBridgeNS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp", .addrLo=0x0ULL, .addrHi=0x3ffffffULL),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .addrLo=0x10000000000ULL, .addrHi=0x10003ffffffULL)
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x10000000ULL, .addrHi=0x10000fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(cardin_n, "cardin"),
                OP_NET_CONNECT(wprot_n, "wprot")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("SYS_PROCID0", 0x0c000191)
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x10001000ULL, .addrHi=0x10001fffULL)
            )
        ),
        0
    );

    // PSE sbpci0

    const char *sbpci0_path = opVLNVString(
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
        sbpci0_path,
        "sbpci0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x10002000)
        )
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x10004000ULL, .addrHi=0x10004fffULL)
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x10005000ULL, .addrHi=0x10005fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir9_n, "irq0"),
                OP_NET_CONNECT(ir10_n, "irq1"),
                OP_NET_CONNECT(cardin_n, "cardin"),
                OP_NET_CONNECT(wprot_n, "wprot")
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x10006000ULL, .addrHi=0x10006fffULL)
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x10007000ULL, .addrHi=0x10007fffULL)
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x10009000ULL, .addrHi=0x10009fffULL)
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1000a000ULL, .addrHi=0x1000afffULL)
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1000b000ULL, .addrHi=0x1000bfffULL)
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1000c000ULL, .addrHi=0x1000cfffULL)
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1000f000ULL, .addrHi=0x1000ffffULL)
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x10011000ULL, .addrHi=0x10011fffULL)
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x10012000ULL, .addrHi=0x10012fffULL)
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x10016000ULL, .addrHi=0x10016fffULL)
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x10017000ULL, .addrHi=0x10017fffULL)
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1001f000ULL, .addrHi=0x1001ffffULL),
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

    // PSE lcd1

    const char *lcd1_path = opVLNVString(
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
        lcd1_path,
        "lcd1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x10020000ULL, .addrHi=0x10020fffULL),
                OP_BUS_CONNECT(pBus_b, "memory", .slave=1, .dynamic=1)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir44_n, "irq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_ENUM_SET("resolution", "xga")
        )
    );

    // PSE lcd1NS

    const char *lcd1NS_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "DynamicBridge",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        lcd1NS_path,
        "lcd1NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp"),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .dynamic=1)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(tzpcdecprot1_4_n, "enable")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS64_SET("mpLoAddress", 0x10020000ULL)
            ,OP_PARAM_UNS64_SET("spLoAddress", 0x10010020000ULL)
            ,OP_PARAM_UNS64_SET("portSize", 0x1000ULL)
        )
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x100e0000ULL, .addrHi=0x100e0fffULL)
            )
        ),
        0
    );

    // PSE dmc1NS

    const char *dmc1NS_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "DynamicBridge",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        dmc1NS_path,
        "dmc1NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp"),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .dynamic=1)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(tzpcdecprot0_0_n, "enable")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS64_SET("mpLoAddress", 0x100e0000ULL)
            ,OP_PARAM_UNS64_SET("spLoAddress", 0x100100e0000ULL)
            ,OP_PARAM_UNS64_SET("portSize", 0x1000ULL)
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x100e1000ULL, .addrHi=0x100e1fffULL)
            )
        ),
        0
    );

    // PSE smc1NS

    const char *smc1NS_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "DynamicBridge",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        smc1NS_path,
        "smc1NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp"),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .dynamic=1)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(tzpcdecprot0_1_n, "enable")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS64_SET("mpLoAddress", 0x100e1000ULL)
            ,OP_PARAM_UNS64_SET("spLoAddress", 0x100100e1000ULL)
            ,OP_PARAM_UNS64_SET("portSize", 0x1000ULL)
        )
    );

    // PSE scc1

    const char *scc1_path = opVLNVString(
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
        scc1_path,
        "scc1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x100e2000)
        )
    );

    // PSE scc1NS

    const char *scc1NS_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "DynamicBridge",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        scc1NS_path,
        "scc1NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp"),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .dynamic=1)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(tzpcdecprot0_2_n, "enable")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS64_SET("mpLoAddress", 0x100e2000ULL)
            ,OP_PARAM_UNS64_SET("spLoAddress", 0x100100e2000ULL)
            ,OP_PARAM_UNS64_SET("portSize", 0x1000ULL)
        )
    );

    // PSE timer45

    const char *timer45_path = opVLNVString(
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
        timer45_path,
        "timer45",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x100e4000ULL, .addrHi=0x100e4fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir48_n, "irq")
            )
        ),
        0
    );

    // PSE timer45NS

    const char *timer45NS_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "DynamicBridge",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        timer45NS_path,
        "timer45NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp"),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .dynamic=1)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(tzpcdecprot0_4_n, "enable")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS64_SET("mpLoAddress", 0x100e4000ULL)
            ,OP_PARAM_UNS64_SET("spLoAddress", 0x100100e4000ULL)
            ,OP_PARAM_UNS64_SET("portSize", 0x1000ULL)
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x100e5000ULL, .addrHi=0x100e5fffULL)
            )
        ),
        0
    );

    // PSE wdt2NS

    const char *wdt2NS_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "DynamicBridge",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        wdt2NS_path,
        "wdt2NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp"),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .dynamic=1)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(tzpcdecprot0_5_n, "enable")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS64_SET("mpLoAddress", 0x100e5000ULL)
            ,OP_PARAM_UNS64_SET("spLoAddress", 0x100100e5000ULL)
            ,OP_PARAM_UNS64_SET("portSize", 0x1000ULL)
        )
    );

    // PSE tzpc

    const char *tzpc_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "TzpcBP147",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        tzpc_path,
        "tzpc",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x100e6000ULL, .addrHi=0x100e6fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(tzpcdecprot0_0_n, "TZPCDECPROT0_0"),
                OP_NET_CONNECT(tzpcdecprot0_1_n, "TZPCDECPROT0_1"),
                OP_NET_CONNECT(tzpcdecprot0_2_n, "TZPCDECPROT0_2"),
                OP_NET_CONNECT(tzpcdecprot0_4_n, "TZPCDECPROT0_4"),
                OP_NET_CONNECT(tzpcdecprot0_5_n, "TZPCDECPROT0_5"),
                OP_NET_CONNECT(tzpcdecprot0_9_n, "TZPCDECPROT0_9"),
                OP_NET_CONNECT(tzpcdecprot0_10_n, "TZPCDECPROT0_10"),
                OP_NET_CONNECT(tzpcdecprot1_4_n, "TZPCDECPROT1_4")
            )
        ),
        0
    );

    // PSE gpio0

    const char *gpio0_path = opVLNVString(
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
        gpio0_path,
        "gpio0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x100e8000)
        )
    );

    // PSE faxi1

    const char *faxi1_path = opVLNVString(
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
        faxi1_path,
        "faxi1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x100e9000)
        )
    );

    // PSE faxi1NS

    const char *faxi1NS_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "DynamicBridge",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        faxi1NS_path,
        "faxi1NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp"),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .dynamic=1)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(tzpcdecprot0_9_n, "enable")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS64_SET("mpLoAddress", 0x100e9000ULL)
            ,OP_PARAM_UNS64_SET("spLoAddress", 0x100100e9000ULL)
            ,OP_PARAM_UNS64_SET("portSize", 0x1000ULL)
        )
    );

    // PSE saxi1

    const char *saxi1_path = opVLNVString(
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
        saxi1_path,
        "saxi1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x100ea000)
        )
    );

    // PSE saxi1NS

    const char *saxi1NS_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "DynamicBridge",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        saxi1NS_path,
        "saxi1NS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mp"),
                OP_BUS_CONNECT(tzBus_b, "sp", .slave=1, .dynamic=1)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(tzpcdecprot0_10_n, "enable")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS64_SET("mpLoAddress", 0x100ea000ULL)
            ,OP_PARAM_UNS64_SET("spLoAddress", 0x100100ea000ULL)
            ,OP_PARAM_UNS64_SET("portSize", 0x1000ULL)
        )
    );

    // PSE l2regs

    const char *l2regs_path = opVLNVString(
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
        l2regs_path,
        "l2regs",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x1e00a000ULL, .addrHi=0x1e00afffULL)
            )
        ),
        0
    );

    // PSE nor0

    const char *nor0_path = opVLNVString(
        0, // use the default VLNV path
        "intel.ovpworld.org",
        0,
        "NorFlash48F4400",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        nor0_path,
        "nor0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "flash", .slave=1, .addrLo=0x40000000ULL, .addrHi=0x43ffffffULL)
            )
        ),
        0
    );

    // PSE nor1

    const char *nor1_path = opVLNVString(
        0, // use the default VLNV path
        "intel.ovpworld.org",
        0,
        "NorFlash48F4400",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        nor1_path,
        "nor1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "flash", .slave=1, .addrLo=0x44000000ULL, .addrHi=0x47ffffffULL)
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4e000000ULL, .addrHi=0x4e000fffULL)
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4f000000ULL, .addrHi=0x4f00ffffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir16_n, "hc_irq")
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
             OP_PARAM_STRING_SET("command", "mem=1024M raid=noautodetect console=ttyAMA0,38400n8 vmalloc=256MB devtmpfs.mount=0")
            ,OP_PARAM_UNS32_SET("physicalbase", 0x60000000)
            ,OP_PARAM_UNS32_SET("memsize", 0x40000000)
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
    .purpose              = OP_PP_MODULE,
    .visibility           = OP_VISIBLE,
    .vlnv          = {
        .vendor  = "arm.ovpworld.org",
        .library = "module",
        .name    = "ArmVersatileExpress-CA9",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

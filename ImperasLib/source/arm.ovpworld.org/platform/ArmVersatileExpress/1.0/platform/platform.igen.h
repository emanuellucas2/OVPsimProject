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
    opDocTextAdd(doc_11_node, "This platform models the ARM Versatile Express development board with the Legacy memory map.\nIt provides the peripherals required to boot and run Operating Systems such as Linux or Android.\nThe main processor is an ARM Cortex-A9UP.\nThis platform is deprecated in favor of the ArmVersatileExpress-CA9 platform which models additional behavior, including TrustZone.");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "No known limitations for executing Linux operating system.");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "ARM Development Boards Versatile Express BaseBoard and ARM CoreTile Express");


    // Bus smbus

    optBusP smbus_b = opBusNew(mi, "smbus", 32, 0, 0);


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
    optNetP ir15_n = opNetNew(mi, "ir15", 0, 0);
    optNetP ir16_n = opNetNew(mi, "ir16", 0, 0);
    optNetP ir44_n = opNetNew(mi, "ir44", 0, 0);
    optNetP ir48_n = opNetNew(mi, "ir48", 0, 0);
    optNetP cardin_n = opNetNew(mi, "cardin", 0, 0);
    optNetP wprot_n = opNetNew(mi, "wprot", 0, 0);

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
            ,OP_PARAM_ENUM_SET("variant", "Cortex-A9MPx1")
            ,OP_PARAM_ENUM_SET("compatibility", "ISA")
            ,OP_PARAM_BOOL_SET("UAL", 1)
            ,OP_PARAM_BOOL_SET("showHiddenRegs", 0)
            ,OP_PARAM_UNS32_SET("override_CBAR", 0x1e000000)
        )
    );


    // Memory lcd2

    opMemoryNew(
        mi,
        "lcd2",
        OP_PRIV_RWX,
        (0x1001ffffULL) - (0x1001f000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_b, "sp1", .slave=1, .addrLo=0x1001f000ULL, .addrHi=0x1001ffffULL)
            )
        ),
        0
    );

    // Memory nor0

    opMemoryNew(
        mi,
        "nor0",
        OP_PRIV_RWX,
        (0x43ffffffULL) - (0x40000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_b, "sp1", .slave=1, .addrLo=0x40000000ULL, .addrHi=0x43ffffffULL)
            )
        ),
        0
    );

    // Memory nor1

    opMemoryNew(
        mi,
        "nor1",
        OP_PRIV_RWX,
        (0x47ffffffULL) - (0x44000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_b, "sp1", .slave=1, .addrLo=0x44000000ULL, .addrHi=0x47ffffffULL)
            )
        ),
        0
    );

    // Memory sram1

    opMemoryNew(
        mi,
        "sram1",
        OP_PRIV_RWX,
        (0x4bffffffULL) - (0x48000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(smbus_b, "sp1", .slave=1, .addrLo=0x48000000ULL, .addrHi=0x4bffffffULL)
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
                OP_BUS_CONNECT(smbus_b, "sp1", .slave=1, .addrLo=0x4c000000ULL, .addrHi=0x4c7fffffULL)
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

    // Bridge ddr2RamBridge

    opBridgeNew(
        mi,
        "ddr2RamBridge",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(ddr2bus_b, "mp", .addrLo=0x0ULL, .addrHi=0x3fffffffULL),
                OP_BUS_CONNECT(smbus_b, "sp", .slave=1, .addrLo=0x60000000ULL, .addrHi=0x9fffffffULL)
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
                OP_BUS_CONNECT(smbus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x3ffffffULL)
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
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0x10000000ULL, .addrHi=0x10000fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(cardin_n, "cardin"),
                OP_NET_CONNECT(wprot_n, "wprot")
            )
        ),
        0
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
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0x10001000ULL, .addrHi=0x10001fffULL)
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
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0x10004000ULL, .addrHi=0x10004fffULL)
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
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0x10005000ULL, .addrHi=0x10005fffULL)
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
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0x10006000ULL, .addrHi=0x10006fffULL)
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
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0x10007000ULL, .addrHi=0x10007fffULL)
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
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0x10009000ULL, .addrHi=0x10009fffULL)
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
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0x1000a000ULL, .addrHi=0x1000afffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir6_n, "irq")
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
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0x1000b000ULL, .addrHi=0x1000bfffULL)
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
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0x1000c000ULL, .addrHi=0x1000cfffULL)
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
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0x1000f000ULL, .addrHi=0x1000ffffULL)
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
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0x10011000ULL, .addrHi=0x10011fffULL)
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
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0x10012000ULL, .addrHi=0x10012fffULL)
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
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0x10016000ULL, .addrHi=0x10016fffULL)
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
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0x10017000ULL, .addrHi=0x10017fffULL)
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
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0x1001a000ULL, .addrHi=0x1001afffULL)
            )
        ),
        0
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
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0x10020000ULL, .addrHi=0x10020fffULL),
                OP_BUS_CONNECT(smbus_b, "memory", .slave=1, .dynamic=1)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir44_n, "irq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_ENUM_SET("resolution", "xga")
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
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0x100e0000ULL, .addrHi=0x100e0fffULL)
            )
        ),
        0
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
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0x100e1000ULL, .addrHi=0x100e1fffULL)
            )
        ),
        0
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
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0x100e4000ULL, .addrHi=0x100e4fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ir48_n, "irq")
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
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x100e8000)
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
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0x1e00a000ULL, .addrHi=0x1e00afffULL)
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
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0x4e000000ULL, .addrHi=0x4e000fffULL)
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
                OP_BUS_CONNECT(smbus_b, "bport1", .slave=1, .addrLo=0x4f000000ULL, .addrHi=0x4f00ffffULL)
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
                OP_BUS_CONNECT(smbus_b, "mport", .addrLo=0x0ULL, .addrHi=0xffffffffULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_STRING_SET("command", "mem=1024M raid=noautodetect console=ttyAMA0,38400n8 vmalloc=256MB devtmpfs.mount=0")
            ,OP_PARAM_UNS32_SET("physicalbase", 0x60000000)
            ,OP_PARAM_UNS32_SET("memsize", 0x10000000)
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
        .name    = "ArmVersatileExpress",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

static void cmdParserAddUserArgs(optCmdParserP parser) {
    opCmdParserAdd(parser, "kernel"  , 0 , 0, "user platform config Linux", OP_FT_STRINGVAL     , &options.kernel, "set the kernel to load", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "ramdisk" , 0 , 0, "user platform config Linux", OP_FT_STRINGVAL     , &options.ramdisk, "Specify the ramdisk image e.g. initrd.gz or fs.img for boot", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "command" , 0 , 0, "user platform config Linux", OP_FT_STRINGVAL     , &options.command, "Add additional Linux Kernel command line options", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "sdcard"  , 0 , 0, "user platform config Linux", OP_FT_STRINGVAL     , &options.sdcard, "The name of an image file to load by SD Card", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "bootcode", 0 , 0, "user platform config Linux", OP_FT_STRINGVAL     , &options.bootcode, "Boot code to load and execute", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "uartport", 0 , 0, "user platform config Linux", OP_FT_UNS64VAL      , &options.uartport, "set the port number to open on the UART", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "uartconsole", 0 , 0, "user platform config Linux", OP_FT_BOOLVAL       , &options.uartconsole, "open a console terminal on the UART", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "nographics", 0 , 0, "user platform config", OP_FT_BOOLVAL       , &options.nographics, "Disable the LCD graphics window.", OP_AC_ALL, 0, 0);
}

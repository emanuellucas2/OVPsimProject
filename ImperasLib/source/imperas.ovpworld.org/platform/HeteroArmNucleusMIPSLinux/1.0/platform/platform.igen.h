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
    opDocTextAdd(doc_11_node, "This heterogeneous platform combines MIPS Malta and ARM Integrator platforms.");
    opDocTextAdd(doc_11_node, "MIPS Malta executes a Linux Kernel Operating System.");
    opDocTextAdd(doc_11_node, "ARM Integrator executes the Nucleus Operating System.");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "Peripherals are modeled only to the extent required to boot and run Operating Systems.");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "OVP Heterogeneous platforms. MIPS Malta and ARM IntgratorCP reference guides.");


    // Bus busmipsMain

    optBusP busmipsMain_b = opBusNew(mi, "busmipsMain", 32, 0, 0);


    // Bus PCIconfigBusmipsMain

    optBusP PCIconfigBusmipsMain_b = opBusNew(mi, "PCIconfigBusmipsMain", 16, 0, 0);


    // Bus PCIackBusmipsMain

    optBusP PCIackBusmipsMain_b = opBusNew(mi, "PCIackBusmipsMain", 1, 0, 0);


    // Bus cascadeBusmipsMain

    optBusP cascadeBusmipsMain_b = opBusNew(mi, "cascadeBusmipsMain", 3, 0, 0);


    // Bus flashBus

    optBusP flashBus_b = opBusNew(mi, "flashBus", 32, 0, 0);


    // Bus busarmSub1

    optBusP busarmSub1_b = opBusNew(mi, "busarmSub1", 32, 0, 0);


    // Bus busShared

    optBusP busShared_b = opBusNew(mi, "busShared", 32, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP i8259Int_n = opNetNew(mi, "i8259Int", 0, 0);
    optNetP armSub1irq_n = opNetNew(mi, "armSub1irq", 0, 0);
    optNetP armSub1fiq_n = opNetNew(mi, "armSub1fiq", 0, 0);
    optNetP intCtl_ir14_n = opNetNew(mi, "intCtl_ir14", 0, 0);
    optNetP intCtl_ir15_n = opNetNew(mi, "intCtl_ir15", 0, 0);
    optNetP intCtl_ir10_n = opNetNew(mi, "intCtl_ir10", 0, 0);
    optNetP intCtl_ir1_n = opNetNew(mi, "intCtl_ir1", 0, 0);
    optNetP intCtl_ir3_n = opNetNew(mi, "intCtl_ir3", 0, 0);
    optNetP intCtl_ir4_n = opNetNew(mi, "intCtl_ir4", 0, 0);
    optNetP i8259Cascade_n = opNetNew(mi, "i8259Cascade", 0, 0);
    optNetP intCtl_ir8_n = opNetNew(mi, "intCtl_ir8", 0, 0);
    optNetP intCtl_ir12_n = opNetNew(mi, "intCtl_ir12", 0, 0);
    optNetP armSub1ir1_n = opNetNew(mi, "armSub1ir1", 0, 0);
    optNetP armSub1ir2_n = opNetNew(mi, "armSub1ir2", 0, 0);
    optNetP armSub1ir3_n = opNetNew(mi, "armSub1ir3", 0, 0);
    optNetP armSub1ir4_n = opNetNew(mi, "armSub1ir4", 0, 0);
    optNetP armSub1ir5_n = opNetNew(mi, "armSub1ir5", 0, 0);
    optNetP armSub1ir6_n = opNetNew(mi, "armSub1ir6", 0, 0);
    optNetP armSub1ir7_n = opNetNew(mi, "armSub1ir7", 0, 0);
    optNetP armSub1ir8_n = opNetNew(mi, "armSub1ir8", 0, 0);
    optNetP armSub1ir23_n = opNetNew(mi, "armSub1ir23", 0, 0);
    optNetP armSub1ir24_n = opNetNew(mi, "armSub1ir24", 0, 0);

    // Processor mipsle1

    const char *mipsle1_path = opVLNVString(
        0, // use the default VLNV path
        "mips.ovpworld.org",
        0,
        "mips32_r1r5",
        0,
        OP_PROCESSOR,
        OP_VLNV_PRINT
    );

    optProcessorP mipsle1_c = opProcessorNew(
        mi,
        mipsle1_path,
        "mipsle1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busmipsMain_b, "INSTRUCTION"),
                OP_BUS_CONNECT(busmipsMain_b, "DATA")
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(i8259Int_n, "hwint0")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_DOUBLE_SET("mips", 100)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_ENUM_SET("variant", "34Kf")
            ,OP_PARAM_BOOL_SET("vectoredinterrupt", 0)
            ,OP_PARAM_UNS32_SET("config1MMUSizeM1", 63)
        )
    );


    // Processor armSub1arm1

    const char *armSub1arm1_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "arm",
        0,
        OP_PROCESSOR,
        OP_VLNV_PRINT
    );

    optProcessorP armSub1arm1_c = opProcessorNew(
        mi,
        armSub1arm1_path,
        "armSub1arm1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busarmSub1_b, "INSTRUCTION"),
                OP_BUS_CONNECT(busarmSub1_b, "DATA")
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(armSub1irq_n, "irq"),
                OP_NET_CONNECT(armSub1fiq_n, "fiq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_UNS32_SET("cpuid", 1)
            ,OP_PARAM_DOUBLE_SET("mips", 200.0)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_ENUM_SET("variant", "ARM920T")
            ,OP_PARAM_ENUM_SET("compatibility", "ISA")
            ,OP_PARAM_BOOL_SET("showHiddenRegs", 0)
        )
    );


    // Memory Core_Board_SDRAM

    opMemoryNew(
        mi,
        "Core_Board_SDRAM",
        OP_PRIV_RWX,
        (0x7ffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busmipsMain_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x7ffffffULL)
            )
        ),
        0
    );

    // Memory Monitor_Flash

    opMemoryNew(
        mi,
        "Monitor_Flash",
        OP_PRIV_RWX,
        (0x1e3fffffULL) - (0x1e000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(flashBus_b, "sp1", .slave=1, .addrLo=0x1e000000ULL, .addrHi=0x1e3fffffULL)
            )
        ),
        0
    );

    // Memory armSub1ram1

    opMemoryNew(
        mi,
        "armSub1ram1",
        OP_PRIV_RWX,
        (0x87ffffffULL) - (0x80000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busarmSub1_b, "sp1", .slave=1, .addrLo=0x80000000ULL, .addrHi=0x87ffffffULL)
            )
        ),
        0
    );

    // Memory armSub1ambaDummy

    opMemoryNew(
        mi,
        "armSub1ambaDummy",
        OP_PRIV_RWX,
        (0x1d000fffULL) - (0x1d000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busarmSub1_b, "sp1", .slave=1, .addrLo=0x1d000000ULL, .addrHi=0x1d000fffULL)
            )
        ),
        0
    );

    // Memory sharedRAM

    opMemoryNew(
        mi,
        "sharedRAM",
        OP_PRIV_RWX,
        (0xffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busShared_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0xffffULL)
            )
        ),
        0
    );

    // Bridge map

    opBridgeNew(
        mi,
        "map",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(flashBus_b, "mp1", .addrLo=0x1e000000ULL, .addrHi=0x1e3fffffULL),
                OP_BUS_CONNECT(busmipsMain_b, "sp1", .slave=1, .addrLo=0x1e000000ULL, .addrHi=0x1e3fffffULL)
            )
        ),
        0
    );

    // Bridge remap1

    opBridgeNew(
        mi,
        "remap1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(flashBus_b, "mp1", .addrLo=0x1e000000ULL, .addrHi=0x1e00000fULL),
                OP_BUS_CONNECT(busmipsMain_b, "sp1", .slave=1, .addrLo=0x1fc00000ULL, .addrHi=0x1fc0000fULL)
            )
        ),
        0
    );

    // Bridge remap2

    opBridgeNew(
        mi,
        "remap2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(flashBus_b, "mp1", .addrLo=0x1e000014ULL, .addrHi=0x1e3fffffULL),
                OP_BUS_CONNECT(busmipsMain_b, "sp1", .slave=1, .addrLo=0x1fc00014ULL, .addrHi=0x1fffffffULL)
            )
        ),
        0
    );

    // Bridge armSub1ram1Bridge

    opBridgeNew(
        mi,
        "armSub1ram1Bridge",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busarmSub1_b, "mp", .addrLo=0x80000000ULL, .addrHi=0x87ffffffULL),
                OP_BUS_CONNECT(busarmSub1_b, "sp", .slave=1, .addrLo=0x0ULL, .addrHi=0x7ffffffULL)
            )
        ),
        0
    );

    // Bridge busBridgeM1

    opBridgeNew(
        mi,
        "busBridgeM1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busShared_b, "mp1", .addrLo=0x0ULL, .addrHi=0xffffULL),
                OP_BUS_CONNECT(busmipsMain_b, "sp1", .slave=1, .addrLo=0x8000000ULL, .addrHi=0x800ffffULL)
            )
        ),
        0
    );

    // Bridge busBridgeA1

    opBridgeNew(
        mi,
        "busBridgeA1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busShared_b, "mp1", .addrLo=0x0ULL, .addrHi=0xffffULL),
                OP_BUS_CONNECT(busarmSub1_b, "sp1", .slave=1, .addrLo=0xa000000ULL, .addrHi=0xa00ffffULL)
            )
        ),
        0
    );

    // PSE Core_Board_SDRAM_promInit

    const char *Core_Board_SDRAM_promInit_path = opVLNVString(
        0, // use the default VLNV path
        "mips.ovpworld.org",
        "peripheral",
        "SmartLoaderLinux",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        Core_Board_SDRAM_promInit_path,
        "Core_Board_SDRAM_promInit",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busmipsMain_b, "mport", .addrLo=0x0ULL, .addrHi=0x7fffffffULL),
                OP_BUS_CONNECT(busmipsMain_b, "idport", .slave=1, .addrLo=0x1fc00010ULL, .addrHi=0x1fc00013ULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_STRING_SET("kernel", "mips.vmlinux")
            ,OP_PARAM_UNS32_SET("boardid", 0x00000420)
            ,OP_PARAM_STRING_SET("initrd", "mips.initrd.gz")
            ,OP_PARAM_STRING_SET("command", "console=tty0")
        )
    );

    // PSE sysControl

    const char *sysControl_path = opVLNVString(
        0, // use the default VLNV path
        "marvell.ovpworld.org",
        "peripheral",
        "GT6412x",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        sysControl_path,
        "sysControl",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(PCIconfigBusmipsMain_b, "PCIconfigM"),
                OP_BUS_CONNECT(PCIackBusmipsMain_b, "PCIackM"),
                OP_BUS_CONNECT(busmipsMain_b, "busPort", .slave=1, .dynamic=1),
                OP_BUS_CONNECT(PCIconfigBusmipsMain_b, "PCIconfig", .slave=1, .dynamic=1)
            )
        ),
        0
    );

    // PSE PIIX4

    const char *PIIX4_path = opVLNVString(
        0, // use the default VLNV path
        "intel.ovpworld.org",
        "peripheral",
        "82371EB",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        PIIX4_path,
        "PIIX4",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(PCIconfigBusmipsMain_b, "PCIconfig", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCIslot", 10)
        )
    );

    // PSE PIIX4-IDE

    const char *PIIX4_IDE_path = opVLNVString(
        0, // use the default VLNV path
        "intel.ovpworld.org",
        "peripheral",
        "PciIDE",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        PIIX4_IDE_path,
        "PIIX4-IDE",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busmipsMain_b, "dmaPort"),
                OP_BUS_CONNECT(PCIconfigBusmipsMain_b, "PCIconfig", .slave=1, .dynamic=1),
                OP_BUS_CONNECT(busmipsMain_b, "busPort", .slave=1, .dynamic=1)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(intCtl_ir14_n, "intOut0"),
                OP_NET_CONNECT(intCtl_ir15_n, "intOut1")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCIslot", 10)
            ,OP_PARAM_UNS32_SET("PCIfunction", 1)
            ,OP_PARAM_STRING_SET("Drive0Name", "mipsel_hda")
            ,OP_PARAM_STRING_SET("Drive1Name", "mipsel_hdb")
            ,OP_PARAM_STRING_SET("Drive2Name", "mipsel_cd")
        )
    );

    // PSE PCI_USB

    const char *PCI_USB_path = opVLNVString(
        0, // use the default VLNV path
        "intel.ovpworld.org",
        "peripheral",
        "PciUSB",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        PCI_USB_path,
        "PCI_USB",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(PCIconfigBusmipsMain_b, "PCIconfig", .slave=1, .dynamic=1),
                OP_BUS_CONNECT(busmipsMain_b, "busPort", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCIslot", 10)
            ,OP_PARAM_UNS32_SET("PCIfunction", 2)
        )
    );

    // PSE PCI_PM

    const char *PCI_PM_path = opVLNVString(
        0, // use the default VLNV path
        "intel.ovpworld.org",
        "peripheral",
        "PciPM",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        PCI_PM_path,
        "PCI_PM",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(PCIconfigBusmipsMain_b, "PCIconfig", .slave=1, .dynamic=1),
                OP_BUS_CONNECT(busmipsMain_b, "busPort", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCIslot", 10)
            ,OP_PARAM_UNS32_SET("PCIfunction", 3)
        )
    );

    // PSE PCI_NET

    const char *PCI_NET_path = opVLNVString(
        0, // use the default VLNV path
        "amd.ovpworld.org",
        "peripheral",
        "79C970",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        PCI_NET_path,
        "PCI_NET",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busmipsMain_b, "dmaPort"),
                OP_BUS_CONNECT(PCIconfigBusmipsMain_b, "PCIconfig", .slave=1, .dynamic=1),
                OP_BUS_CONNECT(busmipsMain_b, "busPort", .slave=1, .dynamic=1)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(intCtl_ir10_n, "intOut0")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCIslot", 11)
            ,OP_PARAM_UNS32_SET("PCIfunction", 0)
        )
    );

    // PSE intCtrlMaster

    const char *intCtrlMaster_path = opVLNVString(
        0, // use the default VLNV path
        "intel.ovpworld.org",
        "peripheral",
        "8259A",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        intCtrlMaster_path,
        "intCtrlMaster",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(cascadeBusmipsMain_b, "cascade"),
                OP_BUS_CONNECT(busmipsMain_b, "io", .slave=1, .addrLo=0x18000020ULL, .addrHi=0x18000021ULL),
                OP_BUS_CONNECT(busmipsMain_b, "elcr", .slave=1, .addrLo=0x180004d0ULL, .addrHi=0x180004d0ULL),
                OP_BUS_CONNECT(PCIackBusmipsMain_b, "PCIackS", .slave=1, .addrLo=0x0ULL, .addrHi=0x0ULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(i8259Int_n, "intp"),
                OP_NET_CONNECT(intCtl_ir1_n, "ir1"),
                OP_NET_CONNECT(intCtl_ir3_n, "ir3"),
                OP_NET_CONNECT(intCtl_ir4_n, "ir4"),
                OP_NET_CONNECT(i8259Cascade_n, "ir2")
            )
        ),
        OP_PARAMS(
             OP_PARAM_ENUM_SET("spen", "master")
        )
    );

    // PSE intCtrlSlave

    const char *intCtrlSlave_path = opVLNVString(
        0, // use the default VLNV path
        "intel.ovpworld.org",
        "peripheral",
        "8259A",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        intCtrlSlave_path,
        "intCtrlSlave",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busmipsMain_b, "io", .slave=1, .addrLo=0x180000a0ULL, .addrHi=0x180000a1ULL),
                OP_BUS_CONNECT(busmipsMain_b, "elcr", .slave=1, .addrLo=0x180004d1ULL, .addrHi=0x180004d1ULL),
                OP_BUS_CONNECT(cascadeBusmipsMain_b, "PCIackS", .slave=1, .addrLo=0x2ULL, .addrHi=0x2ULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(intCtl_ir8_n, "ir0"),
                OP_NET_CONNECT(intCtl_ir10_n, "ir2"),
                OP_NET_CONNECT(intCtl_ir12_n, "ir4"),
                OP_NET_CONNECT(intCtl_ir14_n, "ir6"),
                OP_NET_CONNECT(intCtl_ir15_n, "ir7"),
                OP_NET_CONNECT(i8259Cascade_n, "intp")
            )
        ),
        OP_PARAMS(
             OP_PARAM_ENUM_SET("spen", "slave")
        )
    );

    // PSE vga

    const char *vga_path = opVLNVString(
        0, // use the default VLNV path
        "cirrus.ovpworld.org",
        "peripheral",
        "GD5446",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        vga_path,
        "vga",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(PCIconfigBusmipsMain_b, "PCIconfig", .slave=1, .dynamic=1),
                OP_BUS_CONNECT(busmipsMain_b, "config", .slave=1, .addrLo=0x180003b0ULL, .addrHi=0x180003dfULL),
                OP_BUS_CONNECT(busmipsMain_b, "memory", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("scanDelay", 50000)
            ,OP_PARAM_UNS32_SET("PCIslot", 18)
            ,OP_PARAM_STRING_SET("title", "Imperas MIPS32 Malta")
        )
    );

    // PSE Ps2Control

    const char *Ps2Control_path = opVLNVString(
        0, // use the default VLNV path
        "intel.ovpworld.org",
        "peripheral",
        "Ps2Control",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        Ps2Control_path,
        "Ps2Control",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busmipsMain_b, "config", .slave=1, .addrLo=0x18000060ULL, .addrHi=0x18000067ULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(intCtl_ir1_n, "kbdInterrupt"),
                OP_NET_CONNECT(intCtl_ir12_n, "mouseInterrupt")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("pollPeriod", 5000)
            ,OP_PARAM_BOOL_SET("grabDisable", 1)
        )
    );

    // PSE mpit

    const char *mpit_path = opVLNVString(
        0, // use the default VLNV path
        "intel.ovpworld.org",
        "peripheral",
        "8253",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        mpit_path,
        "mpit",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busmipsMain_b, "bport1", .slave=1, .addrLo=0x18000040ULL, .addrHi=0x18000043ULL)
            )
        ),
        0
    );

    // PSE mrtc

    const char *mrtc_path = opVLNVString(
        0, // use the default VLNV path
        "motorola.ovpworld.org",
        "peripheral",
        "MC146818",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        mrtc_path,
        "mrtc",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busmipsMain_b, "busPort", .slave=1, .addrLo=0x18000070ULL, .addrHi=0x18000071ULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(intCtl_ir8_n, "timerInt")
            )
        ),
        0
    );

    // PSE uartTTY0

    const char *uartTTY0_path = opVLNVString(
        0, // use the default VLNV path
        "national.ovpworld.org",
        "peripheral",
        "16550",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uartTTY0_path,
        "uartTTY0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busmipsMain_b, "bport1", .slave=1, .addrLo=0x180003f8ULL, .addrHi=0x180003ffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(intCtl_ir4_n, "intOut")
            )
        ),
        0
    );

    // PSE uartTTY1

    const char *uartTTY1_path = opVLNVString(
        0, // use the default VLNV path
        "national.ovpworld.org",
        "peripheral",
        "16550",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uartTTY1_path,
        "uartTTY1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busmipsMain_b, "bport1", .slave=1, .addrLo=0x180002f8ULL, .addrHi=0x180002ffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(intCtl_ir3_n, "intOut")
            )
        ),
        0
    );

    // PSE uartCBUS

    const char *uartCBUS_path = opVLNVString(
        0, // use the default VLNV path
        "mips.ovpworld.org",
        "peripheral",
        "16450C",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uartCBUS_path,
        "uartCBUS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busmipsMain_b, "bport1", .slave=1, .addrLo=0x1f000900ULL, .addrHi=0x1f00093fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(intCtl_ir3_n, "intOut")
            )
        ),
        0
    );

    // PSE fd0

    const char *fd0_path = opVLNVString(
        0, // use the default VLNV path
        "intel.ovpworld.org",
        "peripheral",
        "82077AA",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        fd0_path,
        "fd0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busmipsMain_b, "bport1", .slave=1, .addrLo=0x180003f0ULL, .addrHi=0x180003f7ULL)
            )
        ),
        0
    );

    // PSE maltaFpga

    const char *maltaFpga_path = opVLNVString(
        0, // use the default VLNV path
        "mips.ovpworld.org",
        "peripheral",
        "MaltaFPGA",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        maltaFpga_path,
        "maltaFpga",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busmipsMain_b, "busPort1", .slave=1, .addrLo=0x1f000000ULL, .addrHi=0x1f0008ffULL),
                OP_BUS_CONNECT(busmipsMain_b, "busPort2", .slave=1, .addrLo=0x1f000a00ULL, .addrHi=0x1f000fffULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("stoponsoftreset", 1)
        )
    );

    // PSE armSub1cm

    const char *armSub1cm_path = opVLNVString(
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
        armSub1cm_path,
        "armSub1cm",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busarmSub1_b, "bport1", .slave=1, .addrLo=0x10000000ULL, .addrHi=0x10000fffULL)
            )
        ),
        0
    );

    // PSE armSub1pic1

    const char *armSub1pic1_path = opVLNVString(
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
        armSub1pic1_path,
        "armSub1pic1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busarmSub1_b, "bport1", .slave=1, .addrLo=0x14000000ULL, .addrHi=0x14000fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(armSub1irq_n, "irq"),
                OP_NET_CONNECT(armSub1fiq_n, "fiq"),
                OP_NET_CONNECT(armSub1ir1_n, "ir1"),
                OP_NET_CONNECT(armSub1ir2_n, "ir2"),
                OP_NET_CONNECT(armSub1ir3_n, "ir3"),
                OP_NET_CONNECT(armSub1ir4_n, "ir4"),
                OP_NET_CONNECT(armSub1ir5_n, "ir5"),
                OP_NET_CONNECT(armSub1ir6_n, "ir6"),
                OP_NET_CONNECT(armSub1ir7_n, "ir7"),
                OP_NET_CONNECT(armSub1ir8_n, "ir8"),
                OP_NET_CONNECT(armSub1ir23_n, "ir23"),
                OP_NET_CONNECT(armSub1ir24_n, "ir24")
            )
        ),
        0
    );

    // PSE armSub1pic2

    const char *armSub1pic2_path = opVLNVString(
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
        armSub1pic2_path,
        "armSub1pic2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busarmSub1_b, "bport1", .slave=1, .addrLo=0xca000000ULL, .addrHi=0xca000fffULL)
            )
        ),
        0
    );

    // PSE armSub1pit

    const char *armSub1pit_path = opVLNVString(
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
        armSub1pit_path,
        "armSub1pit",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busarmSub1_b, "bport1", .slave=1, .addrLo=0x13000000ULL, .addrHi=0x13000fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(armSub1ir5_n, "irq0"),
                OP_NET_CONNECT(armSub1ir6_n, "irq1"),
                OP_NET_CONNECT(armSub1ir7_n, "irq2")
            )
        ),
        0
    );

    // PSE armSub1icp

    const char *armSub1icp_path = opVLNVString(
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
        armSub1icp_path,
        "armSub1icp",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busarmSub1_b, "bport1", .slave=1, .addrLo=0xcb000000ULL, .addrHi=0xcb00000fULL)
            )
        ),
        0
    );

    // PSE armSub1ld1

    const char *armSub1ld1_path = opVLNVString(
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
        armSub1ld1_path,
        "armSub1ld1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busarmSub1_b, "bport1", .slave=1, .addrLo=0x1a000000ULL, .addrHi=0x1a000fffULL)
            )
        ),
        0
    );

    // PSE armSub1kb1

    const char *armSub1kb1_path = opVLNVString(
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
        armSub1kb1_path,
        "armSub1kb1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busarmSub1_b, "bport1", .slave=1, .addrLo=0x18000000ULL, .addrHi=0x18000fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(armSub1ir3_n, "irq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("isMouse", 0)
            ,OP_PARAM_BOOL_SET("grabDisable", 0)
        )
    );

    // PSE armSub1ms1

    const char *armSub1ms1_path = opVLNVString(
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
        armSub1ms1_path,
        "armSub1ms1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busarmSub1_b, "bport1", .slave=1, .addrLo=0x19000000ULL, .addrHi=0x19000fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(armSub1ir4_n, "irq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("isMouse", 1)
            ,OP_PARAM_BOOL_SET("grabDisable", 1)
        )
    );

    // PSE armSub1rtc

    const char *armSub1rtc_path = opVLNVString(
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
        armSub1rtc_path,
        "armSub1rtc",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busarmSub1_b, "bport1", .slave=1, .addrLo=0x15000000ULL, .addrHi=0x15000fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(armSub1ir8_n, "irq")
            )
        ),
        0
    );

    // PSE armSub1uart1

    const char *armSub1uart1_path = opVLNVString(
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
        armSub1uart1_path,
        "armSub1uart1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busarmSub1_b, "bport1", .slave=1, .addrLo=0x16000000ULL, .addrHi=0x16000fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(armSub1ir1_n, "irq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_ENUM_SET("variant", "ARM")
            ,OP_PARAM_STRING_SET("outfile", "uart1.log")
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
        )
    );

    // PSE armSub1uart2

    const char *armSub1uart2_path = opVLNVString(
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
        armSub1uart2_path,
        "armSub1uart2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busarmSub1_b, "bport1", .slave=1, .addrLo=0x17000000ULL, .addrHi=0x17000fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(armSub1ir2_n, "irq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_ENUM_SET("variant", "ARM")
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
        )
    );

    // PSE armSub1mmci

    const char *armSub1mmci_path = opVLNVString(
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
        armSub1mmci_path,
        "armSub1mmci",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busarmSub1_b, "bport1", .slave=1, .addrLo=0x1c000000ULL, .addrHi=0x1c000fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(armSub1ir23_n, "irq0"),
                OP_NET_CONNECT(armSub1ir24_n, "irq1")
            )
        ),
        0
    );

    // PSE armSub1lcd

    const char *armSub1lcd_path = opVLNVString(
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
        armSub1lcd_path,
        "armSub1lcd",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busarmSub1_b, "bport1", .slave=1, .addrLo=0xc0000000ULL, .addrHi=0xc0000fffULL),
                OP_BUS_CONNECT(busarmSub1_b, "memory", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("noGraphics", 1)
        )
    );

    // PSE armSub1smartLoader

    const char *armSub1smartLoader_path = opVLNVString(
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
        armSub1smartLoader_path,
        "armSub1smartLoader",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busarmSub1_b, "mport", .addrLo=0x0ULL, .addrHi=0xffffffffULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("disable", 1)
        )
    );
////////////////////////////////////////////////////////////////////////////////
//                               Program loading
////////////////////////////////////////////////////////////////////////////////

    opProcessorApplicationLoad(mipsle1_c, "mips.vmlinux", OP_LDR_DEFAULT|OP_LDR_FAIL_IS_ERROR, 0);
    opProcessorApplicationLoad(armSub1arm1_c, "arm.plus_demo.out", OP_LDR_DEFAULT|OP_LDR_FAIL_IS_ERROR, 0);

}

optModuleAttr modelAttrs = {
    .versionString        = OP_VERSION,
    .type                 = OP_MODULE,
    .name                 = MODULE_NAME,
    .objectSize           = sizeof(optModuleObject),
    .releaseStatus        = OP_OVP,
    .purpose              = OP_PP_FIX,
    .visibility           = OP_VISIBLE,
    .vlnv          = {
        .vendor  = "imperas.ovpworld.org",
        .library = "platform",
        .name    = "HeteroArmNucleusMIPSLinux",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

static void cmdParserAddUserArgs(optCmdParserP parser) {
    opCmdParserAdd(parser, "uartconsole", 0 , 0, "user platform config", OP_FT_BOOLVAL       , &options.uartconsole, "open a console terminal on the ARM IntegratorCP UART", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "uartport", 0 , 0, "user platform config", OP_FT_UNS32VAL      , &options.uartport, "set the base port number to open on the ARM IntegratorCP UART", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "nographics", 0 , 0, "user platform config", OP_FT_BOOLVAL       , &options.nographics, "disable the MIPS Malta graphics window", OP_AC_ALL, 0, 0);
}

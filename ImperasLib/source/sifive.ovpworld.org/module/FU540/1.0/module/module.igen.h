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
    opDocTextAdd(doc_11_node, "SiFive FU540-C000 SoC module.");
    opDocTextAdd(doc_11_node, "On start up or reset, the reset code at 0x1004 will jump to a jump table entry indexed by the MSEL register at address 0x1000 (default initial MSEL value is 0xf which will cause a jump to address 0x10000). Use the msel peripheral's MSEL parameter to change the initial value of this register.");
    opDocTextAdd(doc_11_node, "To run a bare metal application use the --program command line option to specify an elf file to be loaded. It must be linked to use addresses corresponding to the implemented memory regions. The --program option will override the initial pc with the ELF file's start address.");
    opDocTextAdd(doc_11_node, "To facilitate booting Linux an OVP SmartLoader psuedo-peripheral has been included that provides the functionality of the ZSBL/FSBL. The SmartLoader's dtb parameter should be used to specify the device tree blob file to load, and the bbl elf file should be loaded using the --objfilenoentry command line option.");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_21_node, "SiFive Freedom U540-C000 Manual FU540-C000-v1.0.pdf (https://www.sifive.com/documentation/chips/freedom-u540-c000-manual)");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_31_node, "Caches and the Cache Controller are not modeled.");
    opDocTextAdd(doc_31_node, "The Instruction Tightly Integrated Memory (ITIM) is implemented simply as RAM. Deallocation by writing to the byte immediately following the memory is a NOP.");
    opDocTextAdd(doc_31_node, "The L2 Loosely Integrated Memory (L2-LIM) is implemented simply as RAM. It is always available, since the Cache Controller is not modeled.");
    opDocTextAdd(doc_31_node, "The L2 Scratchpad memory is not modeled.");
    opDocTextAdd(doc_31_node, "The Platform DMA Engine (PDMA) is not modeled.");
    opDocTextAdd(doc_31_node, "The Pulse Width Modulator (PWM) is not modeled.");
    opDocTextAdd(doc_31_node, "The Inter-Integrated Circuit (I2C) Master Interface is not modeled.");
    opDocTextAdd(doc_31_node, "The Serial Peripheral Interfaces (SPI) are not modeled. Instead a Virtio Block MMIO device has been added at reserved address 0x1f000000, using interrupt 54.");
    opDocTextAdd(doc_31_node, "The General Purpose Input/Output Controller (GPIO) is modeled with register stubs only.");
    opDocTextAdd(doc_31_node, "The One-Time Programmable Memory Interface (OTP) is not modeled.");
    opDocTextAdd(doc_31_node, "DDR controller is modeled with register stubs only. DDR memory is modeled as RAM.");
    opDocTextAdd(doc_31_node, "The Debug Interface is not modeled.");


    // Bus bus0

    optBusP bus0_b = opBusNew(mi, "bus0", 38, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP irqT0_n = opNetNew(mi, "irqT0", 0, 0);
    optNetP irqT1_n = opNetNew(mi, "irqT1", 0, 0);
    optNetP irqT2_n = opNetNew(mi, "irqT2", 0, 0);
    optNetP irqT3_n = opNetNew(mi, "irqT3", 0, 0);
    optNetP irqT4_n = opNetNew(mi, "irqT4", 0, 0);
    optNetP irqT5_n = opNetNew(mi, "irqT5", 0, 0);
    optNetP irqT6_n = opNetNew(mi, "irqT6", 0, 0);
    optNetP irqT7_n = opNetNew(mi, "irqT7", 0, 0);
    optNetP irqT8_n = opNetNew(mi, "irqT8", 0, 0);
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
    optNetP gi1_n = opNetNew(mi, "gi1", "gi1", 0);
    optNetP gi2_n = opNetNew(mi, "gi2", "gi2", 0);
    optNetP gi3_n = opNetNew(mi, "gi3", "gi3", 0);
    optNetP gi4_n = opNetNew(mi, "gi4", "gi4", 0);
    optNetP gi5_n = opNetNew(mi, "gi5", "gi5", 0);
    optNetP gi6_n = opNetNew(mi, "gi6", "gi6", 0);
    optNetP gi7_n = opNetNew(mi, "gi7", "gi7", 0);
    optNetP gi8_n = opNetNew(mi, "gi8", "gi8", 0);
    optNetP gi9_n = opNetNew(mi, "gi9", "gi9", 0);
    optNetP gi10_n = opNetNew(mi, "gi10", "gi10", 0);
    optNetP gi11_n = opNetNew(mi, "gi11", "gi11", 0);
    optNetP gi12_n = opNetNew(mi, "gi12", "gi12", 0);
    optNetP gi13_n = opNetNew(mi, "gi13", "gi13", 0);
    optNetP gi14_n = opNetNew(mi, "gi14", "gi14", 0);
    optNetP gi15_n = opNetNew(mi, "gi15", "gi15", 0);
    optNetP gi16_n = opNetNew(mi, "gi16", "gi16", 0);
    optNetP gi17_n = opNetNew(mi, "gi17", "gi17", 0);
    optNetP gi18_n = opNetNew(mi, "gi18", "gi18", 0);
    optNetP gi19_n = opNetNew(mi, "gi19", "gi19", 0);
    optNetP gi20_n = opNetNew(mi, "gi20", "gi20", 0);
    optNetP gi21_n = opNetNew(mi, "gi21", "gi21", 0);
    optNetP gi22_n = opNetNew(mi, "gi22", "gi22", 0);
    optNetP gi23_n = opNetNew(mi, "gi23", "gi23", 0);
    optNetP gi24_n = opNetNew(mi, "gi24", "gi24", 0);
    optNetP gi25_n = opNetNew(mi, "gi25", "gi25", 0);
    optNetP gi26_n = opNetNew(mi, "gi26", "gi26", 0);
    optNetP gi27_n = opNetNew(mi, "gi27", "gi27", 0);
    optNetP gi28_n = opNetNew(mi, "gi28", "gi28", 0);
    optNetP gi29_n = opNetNew(mi, "gi29", "gi29", 0);
    optNetP gi30_n = opNetNew(mi, "gi30", "gi30", 0);
    optNetP gi31_n = opNetNew(mi, "gi31", "gi31", 0);
    optNetP gi32_n = opNetNew(mi, "gi32", "gi32", 0);
    optNetP gi33_n = opNetNew(mi, "gi33", "gi33", 0);
    optNetP gi34_n = opNetNew(mi, "gi34", "gi34", 0);
    optNetP gi35_n = opNetNew(mi, "gi35", "gi35", 0);
    optNetP gi36_n = opNetNew(mi, "gi36", "gi36", 0);
    optNetP gi37_n = opNetNew(mi, "gi37", "gi37", 0);
    optNetP gi38_n = opNetNew(mi, "gi38", "gi38", 0);
    optNetP gi39_n = opNetNew(mi, "gi39", "gi39", 0);
    optNetP gi40_n = opNetNew(mi, "gi40", "gi40", 0);
    optNetP gi41_n = opNetNew(mi, "gi41", "gi41", 0);
    optNetP gi42_n = opNetNew(mi, "gi42", "gi42", 0);
    optNetP gi43_n = opNetNew(mi, "gi43", "gi43", 0);
    optNetP gi44_n = opNetNew(mi, "gi44", "gi44", 0);
    optNetP gi45_n = opNetNew(mi, "gi45", "gi45", 0);
    optNetP gi46_n = opNetNew(mi, "gi46", "gi46", 0);
    optNetP gi47_n = opNetNew(mi, "gi47", "gi47", 0);
    optNetP gi48_n = opNetNew(mi, "gi48", "gi48", 0);
    optNetP gi49_n = opNetNew(mi, "gi49", "gi49", 0);
    optNetP gi50_n = opNetNew(mi, "gi50", "gi50", 0);
    optNetP gi51_n = opNetNew(mi, "gi51", "gi51", 0);
    optNetP gi52_n = opNetNew(mi, "gi52", "gi52", 0);
    optNetP gi53_n = opNetNew(mi, "gi53", "gi53", 0);

    // Processor E51

    const char *E51_path = opVLNVString(
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
        E51_path,
        "E51",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "INSTRUCTION"),
                OP_BUS_CONNECT(bus0_b, "DATA")
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(MTimerInterrupt0_n, "hart0_MTimerInterrupt"),
                OP_NET_CONNECT(MSWInterrupt0_n, "hart0_MSWInterrupt"),
                OP_NET_CONNECT(irqT0_n, "hart0_MExternalInterrupt")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_DOUBLE_SET("mips", 1000)
            ,OP_PARAM_UNS64_SET("mhartid", 0x0ULL)
            ,OP_PARAM_UNS32_SET("local_int_num", 48)
            ,OP_PARAM_UNS64_SET("reset_address", 0x1004ULL)
            ,OP_PARAM_ENUM_SET("variant", "E51")
        )
    );


    // Processor U54

    const char *U54_path = opVLNVString(
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
        U54_path,
        "U54",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "INSTRUCTION"),
                OP_BUS_CONNECT(bus0_b, "DATA")
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(MTimerInterrupt1_n, "hart1_MTimerInterrupt"),
                OP_NET_CONNECT(MSWInterrupt1_n, "hart1_MSWInterrupt"),
                OP_NET_CONNECT(irqT1_n, "hart1_MExternalInterrupt"),
                OP_NET_CONNECT(irqT2_n, "hart1_SExternalInterrupt"),
                OP_NET_CONNECT(MTimerInterrupt2_n, "hart2_MTimerInterrupt"),
                OP_NET_CONNECT(MSWInterrupt2_n, "hart2_MSWInterrupt"),
                OP_NET_CONNECT(irqT3_n, "hart2_MExternalInterrupt"),
                OP_NET_CONNECT(irqT4_n, "hart2_SExternalInterrupt"),
                OP_NET_CONNECT(MTimerInterrupt3_n, "hart3_MTimerInterrupt"),
                OP_NET_CONNECT(MSWInterrupt3_n, "hart3_MSWInterrupt"),
                OP_NET_CONNECT(irqT5_n, "hart3_MExternalInterrupt"),
                OP_NET_CONNECT(irqT6_n, "hart3_SExternalInterrupt"),
                OP_NET_CONNECT(MTimerInterrupt4_n, "hart4_MTimerInterrupt"),
                OP_NET_CONNECT(MSWInterrupt4_n, "hart4_MSWInterrupt"),
                OP_NET_CONNECT(irqT7_n, "hart4_MExternalInterrupt"),
                OP_NET_CONNECT(irqT8_n, "hart4_SExternalInterrupt")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_UNS32_SET("cpuid", 1)
            ,OP_PARAM_DOUBLE_SET("mips", 1000)
            ,OP_PARAM_UNS64_SET("mhartid", 0x1ULL)
            ,OP_PARAM_UNS32_SET("local_int_num", 48)
            ,OP_PARAM_UNS64_SET("reset_address", 0x1004ULL)
            ,OP_PARAM_UNS32_SET("numHarts", 4)
            ,OP_PARAM_ENUM_SET("variant", "U54")
        )
    );


    // Memory maskROM

    opMemoryNew(
        mi,
        "maskROM",
        OP_PRIV_RWX,
        (0x17fffULL) - (0x10000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x10000ULL, .addrHi=0x17fffULL)
            )
        ),
        0
    );

    // Memory ddr1

    opMemoryNew(
        mi,
        "ddr1",
        OP_PRIV_RWX,
        (0xbfffffffULL) - (0x80000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x80000000ULL, .addrHi=0xbfffffffULL)
            )
        ),
        0
    );

    // Memory safe0addr

    opMemoryNew(
        mi,
        "safe0addr",
        OP_PRIV_RWX,
        (0xffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0xffULL)
            )
        ),
        0
    );

    // Memory hart0DTIM

    opMemoryNew(
        mi,
        "hart0DTIM",
        OP_PRIV_RWX,
        (0x1001fffULL) - (0x1000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x1000000ULL, .addrHi=0x1001fffULL)
            )
        ),
        0
    );

    // Memory hart0ITIM

    opMemoryNew(
        mi,
        "hart0ITIM",
        OP_PRIV_RWX,
        (0x1802000ULL) - (0x1800000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x1800000ULL, .addrHi=0x1802000ULL)
            )
        ),
        0
    );

    // Memory hart1ITIM

    opMemoryNew(
        mi,
        "hart1ITIM",
        OP_PRIV_RWX,
        (0x180f000ULL) - (0x1808000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x1808000ULL, .addrHi=0x180f000ULL)
            )
        ),
        0
    );

    // Memory hart2ITIM

    opMemoryNew(
        mi,
        "hart2ITIM",
        OP_PRIV_RWX,
        (0x1817000ULL) - (0x1810000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x1810000ULL, .addrHi=0x1817000ULL)
            )
        ),
        0
    );

    // Memory hart3ITIM

    opMemoryNew(
        mi,
        "hart3ITIM",
        OP_PRIV_RWX,
        (0x181f000ULL) - (0x1818000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x1818000ULL, .addrHi=0x181f000ULL)
            )
        ),
        0
    );

    // Memory hart4ITIM

    opMemoryNew(
        mi,
        "hart4ITIM",
        OP_PRIV_RWX,
        (0x1827000ULL) - (0x1820000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x1820000ULL, .addrHi=0x1827000ULL)
            )
        ),
        0
    );

    // Memory l2LIM

    opMemoryNew(
        mi,
        "l2LIM",
        OP_PRIV_RWX,
        (0x9ffffffULL) - (0x8000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x8000000ULL, .addrHi=0x9ffffffULL)
            )
        ),
        0
    );

    // PSE msel

    const char *msel_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "MSEL",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        msel_path,
        "msel",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .addrLo=0x1000ULL, .addrHi=0x1fffULL)
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
                OP_BUS_CONNECT(bus0_b, "port0", .slave=1, .addrLo=0x2000000ULL, .addrHi=0x200bfffULL)
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
                OP_NET_CONNECT(MSWInterrupt4_n, "MSWInterrupt4")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("num_harts", 5)
            ,OP_PARAM_DOUBLE_SET("clockMHz", 1.0)
        )
    );

    // PSE plic

    const char *plic_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "PLIC",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        plic_path,
        "plic",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "port0", .slave=1, .addrLo=0xc000000ULL, .addrHi=0xc3fffffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(irqT0_n, "irqT0"),
                OP_NET_CONNECT(irqT1_n, "irqT1"),
                OP_NET_CONNECT(irqT2_n, "irqT2"),
                OP_NET_CONNECT(irqT3_n, "irqT3"),
                OP_NET_CONNECT(irqT4_n, "irqT4"),
                OP_NET_CONNECT(irqT5_n, "irqT5"),
                OP_NET_CONNECT(irqT6_n, "irqT6"),
                OP_NET_CONNECT(irqT7_n, "irqT7"),
                OP_NET_CONNECT(irqT8_n, "irqT8"),
                OP_NET_CONNECT(gi1_n, "irqS1"),
                OP_NET_CONNECT(gi2_n, "irqS2"),
                OP_NET_CONNECT(gi3_n, "irqS3"),
                OP_NET_CONNECT(gi4_n, "irqS4"),
                OP_NET_CONNECT(gi5_n, "irqS5"),
                OP_NET_CONNECT(gi6_n, "irqS6"),
                OP_NET_CONNECT(gi7_n, "irqS7"),
                OP_NET_CONNECT(gi8_n, "irqS8"),
                OP_NET_CONNECT(gi9_n, "irqS9"),
                OP_NET_CONNECT(gi10_n, "irqS10"),
                OP_NET_CONNECT(gi11_n, "irqS11"),
                OP_NET_CONNECT(gi12_n, "irqS12"),
                OP_NET_CONNECT(gi13_n, "irqS13"),
                OP_NET_CONNECT(gi14_n, "irqS14"),
                OP_NET_CONNECT(gi15_n, "irqS15"),
                OP_NET_CONNECT(gi16_n, "irqS16"),
                OP_NET_CONNECT(gi17_n, "irqS17"),
                OP_NET_CONNECT(gi18_n, "irqS18"),
                OP_NET_CONNECT(gi19_n, "irqS19"),
                OP_NET_CONNECT(gi20_n, "irqS20"),
                OP_NET_CONNECT(gi21_n, "irqS21"),
                OP_NET_CONNECT(gi22_n, "irqS22"),
                OP_NET_CONNECT(gi23_n, "irqS23"),
                OP_NET_CONNECT(gi24_n, "irqS24"),
                OP_NET_CONNECT(gi25_n, "irqS25"),
                OP_NET_CONNECT(gi26_n, "irqS26"),
                OP_NET_CONNECT(gi27_n, "irqS27"),
                OP_NET_CONNECT(gi28_n, "irqS28"),
                OP_NET_CONNECT(gi29_n, "irqS29"),
                OP_NET_CONNECT(gi30_n, "irqS30"),
                OP_NET_CONNECT(gi31_n, "irqS31"),
                OP_NET_CONNECT(gi32_n, "irqS32"),
                OP_NET_CONNECT(gi33_n, "irqS33"),
                OP_NET_CONNECT(gi34_n, "irqS34"),
                OP_NET_CONNECT(gi35_n, "irqS35"),
                OP_NET_CONNECT(gi36_n, "irqS36"),
                OP_NET_CONNECT(gi37_n, "irqS37"),
                OP_NET_CONNECT(gi38_n, "irqS38"),
                OP_NET_CONNECT(gi39_n, "irqS39"),
                OP_NET_CONNECT(gi40_n, "irqS40"),
                OP_NET_CONNECT(gi41_n, "irqS41"),
                OP_NET_CONNECT(gi42_n, "irqS42"),
                OP_NET_CONNECT(gi43_n, "irqS43"),
                OP_NET_CONNECT(gi44_n, "irqS44"),
                OP_NET_CONNECT(gi45_n, "irqS45"),
                OP_NET_CONNECT(gi46_n, "irqS46"),
                OP_NET_CONNECT(gi47_n, "irqS47"),
                OP_NET_CONNECT(gi48_n, "irqS48"),
                OP_NET_CONNECT(gi49_n, "irqS49"),
                OP_NET_CONNECT(gi50_n, "irqS50"),
                OP_NET_CONNECT(gi51_n, "irqS51"),
                OP_NET_CONNECT(gi52_n, "irqS52"),
                OP_NET_CONNECT(gi53_n, "irqS53")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("num_targets", 9)
            ,OP_PARAM_UNS32_SET("num_sources", 53)
        )
    );

    // PSE prci

    const char *prci_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "PRCI",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        prci_path,
        "prci",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .addrLo=0x10000000ULL, .addrHi=0x10000fffULL)
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
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .addrLo=0x10010000ULL, .addrHi=0x1001001bULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(gi4_n, "intOut")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("refClkFreq", 500000000)
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
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .addrLo=0x10011000ULL, .addrHi=0x1001101bULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(gi5_n, "intOut")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("refClkFreq", 500000000)
        )
    );

    // PSE gpio

    const char *gpio_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "gpio",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        gpio_path,
        "gpio",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .addrLo=0x10060000ULL, .addrHi=0x10060fffULL)
            )
        ),
        0
    );

    // PSE emac

    const char *emac_path = opVLNVString(
        0, // use the default VLNV path
        "cadence.ovpworld.org",
        "peripheral",
        "gem",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        emac_path,
        "emac",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport2"),
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .addrLo=0x10090000ULL, .addrHi=0x10090fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(gi53_n, "irq")
            )
        ),
        0
    );

    // PSE emgmt

    const char *emgmt_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        "peripheral",
        "trap",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        emgmt_path,
        "emgmt",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x100a0000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
        )
    );

    // PSE ddrctl

    const char *ddrctl_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "DDRCTL",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ddrctl_path,
        "ddrctl",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "CONTROL", .slave=1, .addrLo=0x100b0000ULL, .addrHi=0x100b3fffULL),
                OP_BUS_CONNECT(bus0_b, "BLOCKER", .slave=1, .addrLo=0x100b8000ULL, .addrHi=0x100b8007ULL)
            )
        ),
        0
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
                OP_BUS_CONNECT(bus0_b, "dma"),
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .addrLo=0x1f000000ULL, .addrHi=0x1f0001ffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(gi6_n, "Interrupt")
            )
        ),
        0
    );

    // PSE smartLoader

    const char *smartLoader_path = opVLNVString(
        0, // use the default VLNV path
        "riscv.ovpworld.org",
        0,
        "SmartLoaderRV64Linux",
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
                OP_BUS_CONNECT(bus0_b, "mport")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS64_SET("membase", 0x80000000ULL)
            ,OP_PARAM_UNS64_SET("memsize", 0x40000000ULL)
        )
    );

}

static optNetPortInfo netPortSpecs[] = {
    {
        .name        = "gi1",
        .description = 0,
    },
    {
        .name        = "gi2",
        .description = 0,
    },
    {
        .name        = "gi3",
        .description = 0,
    },
    {
        .name        = "gi4",
        .description = 0,
    },
    {
        .name        = "gi5",
        .description = 0,
    },
    {
        .name        = "gi6",
        .description = 0,
    },
    {
        .name        = "gi7",
        .description = 0,
    },
    {
        .name        = "gi8",
        .description = 0,
    },
    {
        .name        = "gi9",
        .description = 0,
    },
    {
        .name        = "gi10",
        .description = 0,
    },
    {
        .name        = "gi11",
        .description = 0,
    },
    {
        .name        = "gi12",
        .description = 0,
    },
    {
        .name        = "gi13",
        .description = 0,
    },
    {
        .name        = "gi14",
        .description = 0,
    },
    {
        .name        = "gi15",
        .description = 0,
    },
    {
        .name        = "gi16",
        .description = 0,
    },
    {
        .name        = "gi17",
        .description = 0,
    },
    {
        .name        = "gi18",
        .description = 0,
    },
    {
        .name        = "gi19",
        .description = 0,
    },
    {
        .name        = "gi20",
        .description = 0,
    },
    {
        .name        = "gi21",
        .description = 0,
    },
    {
        .name        = "gi22",
        .description = 0,
    },
    {
        .name        = "gi23",
        .description = 0,
    },
    {
        .name        = "gi24",
        .description = 0,
    },
    {
        .name        = "gi25",
        .description = 0,
    },
    {
        .name        = "gi26",
        .description = 0,
    },
    {
        .name        = "gi27",
        .description = 0,
    },
    {
        .name        = "gi28",
        .description = 0,
    },
    {
        .name        = "gi29",
        .description = 0,
    },
    {
        .name        = "gi30",
        .description = 0,
    },
    {
        .name        = "gi31",
        .description = 0,
    },
    {
        .name        = "gi32",
        .description = 0,
    },
    {
        .name        = "gi33",
        .description = 0,
    },
    {
        .name        = "gi34",
        .description = 0,
    },
    {
        .name        = "gi35",
        .description = 0,
    },
    {
        .name        = "gi36",
        .description = 0,
    },
    {
        .name        = "gi37",
        .description = 0,
    },
    {
        .name        = "gi38",
        .description = 0,
    },
    {
        .name        = "gi39",
        .description = 0,
    },
    {
        .name        = "gi40",
        .description = 0,
    },
    {
        .name        = "gi41",
        .description = 0,
    },
    {
        .name        = "gi42",
        .description = 0,
    },
    {
        .name        = "gi43",
        .description = 0,
    },
    {
        .name        = "gi44",
        .description = 0,
    },
    {
        .name        = "gi45",
        .description = 0,
    },
    {
        .name        = "gi46",
        .description = 0,
    },
    {
        .name        = "gi47",
        .description = 0,
    },
    {
        .name        = "gi48",
        .description = 0,
    },
    {
        .name        = "gi49",
        .description = 0,
    },
    {
        .name        = "gi50",
        .description = 0,
    },
    {
        .name        = "gi51",
        .description = 0,
    },
    {
        .name        = "gi52",
        .description = 0,
    },
    {
        .name        = "gi53",
        .description = 0,
    },
    { 0 }
};

static OP_NET_PORT_FN(moduleNetPortIterator) {
    prev = prev ? prev + 1 : netPortSpecs; 
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
        .vendor  = "sifive.ovpworld.org",
        .library = "module",
        .name    = "FU540",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
    .netPortSpecsCB       = moduleNetPortIterator,
};

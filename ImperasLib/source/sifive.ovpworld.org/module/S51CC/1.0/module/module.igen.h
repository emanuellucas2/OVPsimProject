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
    opDocTextAdd(doc_11_node, "SiFive S51 (aka E51) Core Complex module.");
    opDocTextAdd(doc_11_node, "To run a bare metal application use the --program command line option to specify an elf file to be loaded. It must be linked to use addresses corresponding to the implemented memory regions. The --program option will override the initial pc with the ELF file's start address.");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_21_node, "SiFive S51 Core Complex Manual v19.02 (Downloaded from: https://www.sifive.com/documentation)");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_31_node, "Caches are not modeled.");
    opDocTextAdd(doc_31_node, "The Instruction Tightly Integrated Memory (ITIM) is implemented simply as RAM. Deallocation by writing to the byte immediately following the memory is a NOP.");
    opDocTextAdd(doc_31_node, "The Safe Zero Address area at address 0x0 is implemented as normal RAM, so is not guaranteed to always read as 0.");


    // Bus bus0

    optBusP bus0_b = opBusNew(mi, "bus0", 40, "systemPort", 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP LocalInterrupt0_n = opNetNew(mi, "LocalInterrupt0", "li0", 0);
    optNetP LocalInterrupt1_n = opNetNew(mi, "LocalInterrupt1", "li1", 0);
    optNetP LocalInterrupt2_n = opNetNew(mi, "LocalInterrupt2", "li2", 0);
    optNetP LocalInterrupt3_n = opNetNew(mi, "LocalInterrupt3", "li3", 0);
    optNetP LocalInterrupt4_n = opNetNew(mi, "LocalInterrupt4", "li4", 0);
    optNetP LocalInterrupt5_n = opNetNew(mi, "LocalInterrupt5", "li5", 0);
    optNetP LocalInterrupt6_n = opNetNew(mi, "LocalInterrupt6", "li6", 0);
    optNetP LocalInterrupt7_n = opNetNew(mi, "LocalInterrupt7", "li7", 0);
    optNetP LocalInterrupt8_n = opNetNew(mi, "LocalInterrupt8", "li8", 0);
    optNetP LocalInterrupt9_n = opNetNew(mi, "LocalInterrupt9", "li9", 0);
    optNetP LocalInterrupt10_n = opNetNew(mi, "LocalInterrupt10", "li10", 0);
    optNetP LocalInterrupt11_n = opNetNew(mi, "LocalInterrupt11", "li11", 0);
    optNetP LocalInterrupt12_n = opNetNew(mi, "LocalInterrupt12", "li12", 0);
    optNetP LocalInterrupt13_n = opNetNew(mi, "LocalInterrupt13", "li13", 0);
    optNetP LocalInterrupt14_n = opNetNew(mi, "LocalInterrupt14", "li14", 0);
    optNetP LocalInterrupt15_n = opNetNew(mi, "LocalInterrupt15", "li15", 0);
    optNetP resetNet_n = opNetNew(mi, "resetNet", "resetPort", 0);
    optNetP MTimerInterrupt0_n = opNetNew(mi, "MTimerInterrupt0", 0, 0);
    optNetP MSWInterrupt0_n = opNetNew(mi, "MSWInterrupt0", 0, 0);
    optNetP MExternalInterrupt0_n = opNetNew(mi, "MExternalInterrupt0", 0, 0);
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
    optNetP gi54_n = opNetNew(mi, "gi54", "gi54", 0);
    optNetP gi55_n = opNetNew(mi, "gi55", "gi55", 0);
    optNetP gi56_n = opNetNew(mi, "gi56", "gi56", 0);
    optNetP gi57_n = opNetNew(mi, "gi57", "gi57", 0);
    optNetP gi58_n = opNetNew(mi, "gi58", "gi58", 0);
    optNetP gi59_n = opNetNew(mi, "gi59", "gi59", 0);
    optNetP gi60_n = opNetNew(mi, "gi60", "gi60", 0);
    optNetP gi61_n = opNetNew(mi, "gi61", "gi61", 0);
    optNetP gi62_n = opNetNew(mi, "gi62", "gi62", 0);
    optNetP gi63_n = opNetNew(mi, "gi63", "gi63", 0);
    optNetP gi64_n = opNetNew(mi, "gi64", "gi64", 0);
    optNetP gi65_n = opNetNew(mi, "gi65", "gi65", 0);
    optNetP gi66_n = opNetNew(mi, "gi66", "gi66", 0);
    optNetP gi67_n = opNetNew(mi, "gi67", "gi67", 0);
    optNetP gi68_n = opNetNew(mi, "gi68", "gi68", 0);
    optNetP gi69_n = opNetNew(mi, "gi69", "gi69", 0);
    optNetP gi70_n = opNetNew(mi, "gi70", "gi70", 0);
    optNetP gi71_n = opNetNew(mi, "gi71", "gi71", 0);
    optNetP gi72_n = opNetNew(mi, "gi72", "gi72", 0);
    optNetP gi73_n = opNetNew(mi, "gi73", "gi73", 0);
    optNetP gi74_n = opNetNew(mi, "gi74", "gi74", 0);
    optNetP gi75_n = opNetNew(mi, "gi75", "gi75", 0);
    optNetP gi76_n = opNetNew(mi, "gi76", "gi76", 0);
    optNetP gi77_n = opNetNew(mi, "gi77", "gi77", 0);
    optNetP gi78_n = opNetNew(mi, "gi78", "gi78", 0);
    optNetP gi79_n = opNetNew(mi, "gi79", "gi79", 0);
    optNetP gi80_n = opNetNew(mi, "gi80", "gi80", 0);
    optNetP gi81_n = opNetNew(mi, "gi81", "gi81", 0);
    optNetP gi82_n = opNetNew(mi, "gi82", "gi82", 0);
    optNetP gi83_n = opNetNew(mi, "gi83", "gi83", 0);
    optNetP gi84_n = opNetNew(mi, "gi84", "gi84", 0);
    optNetP gi85_n = opNetNew(mi, "gi85", "gi85", 0);
    optNetP gi86_n = opNetNew(mi, "gi86", "gi86", 0);
    optNetP gi87_n = opNetNew(mi, "gi87", "gi87", 0);
    optNetP gi88_n = opNetNew(mi, "gi88", "gi88", 0);
    optNetP gi89_n = opNetNew(mi, "gi89", "gi89", 0);
    optNetP gi90_n = opNetNew(mi, "gi90", "gi90", 0);
    optNetP gi91_n = opNetNew(mi, "gi91", "gi91", 0);
    optNetP gi92_n = opNetNew(mi, "gi92", "gi92", 0);
    optNetP gi93_n = opNetNew(mi, "gi93", "gi93", 0);
    optNetP gi94_n = opNetNew(mi, "gi94", "gi94", 0);
    optNetP gi95_n = opNetNew(mi, "gi95", "gi95", 0);
    optNetP gi96_n = opNetNew(mi, "gi96", "gi96", 0);
    optNetP gi97_n = opNetNew(mi, "gi97", "gi97", 0);
    optNetP gi98_n = opNetNew(mi, "gi98", "gi98", 0);
    optNetP gi99_n = opNetNew(mi, "gi99", "gi99", 0);
    optNetP gi100_n = opNetNew(mi, "gi100", "gi100", 0);
    optNetP gi101_n = opNetNew(mi, "gi101", "gi101", 0);
    optNetP gi102_n = opNetNew(mi, "gi102", "gi102", 0);
    optNetP gi103_n = opNetNew(mi, "gi103", "gi103", 0);
    optNetP gi104_n = opNetNew(mi, "gi104", "gi104", 0);
    optNetP gi105_n = opNetNew(mi, "gi105", "gi105", 0);
    optNetP gi106_n = opNetNew(mi, "gi106", "gi106", 0);
    optNetP gi107_n = opNetNew(mi, "gi107", "gi107", 0);
    optNetP gi108_n = opNetNew(mi, "gi108", "gi108", 0);
    optNetP gi109_n = opNetNew(mi, "gi109", "gi109", 0);
    optNetP gi110_n = opNetNew(mi, "gi110", "gi110", 0);
    optNetP gi111_n = opNetNew(mi, "gi111", "gi111", 0);
    optNetP gi112_n = opNetNew(mi, "gi112", "gi112", 0);
    optNetP gi113_n = opNetNew(mi, "gi113", "gi113", 0);
    optNetP gi114_n = opNetNew(mi, "gi114", "gi114", 0);
    optNetP gi115_n = opNetNew(mi, "gi115", "gi115", 0);
    optNetP gi116_n = opNetNew(mi, "gi116", "gi116", 0);
    optNetP gi117_n = opNetNew(mi, "gi117", "gi117", 0);
    optNetP gi118_n = opNetNew(mi, "gi118", "gi118", 0);
    optNetP gi119_n = opNetNew(mi, "gi119", "gi119", 0);
    optNetP gi120_n = opNetNew(mi, "gi120", "gi120", 0);
    optNetP gi121_n = opNetNew(mi, "gi121", "gi121", 0);
    optNetP gi122_n = opNetNew(mi, "gi122", "gi122", 0);
    optNetP gi123_n = opNetNew(mi, "gi123", "gi123", 0);
    optNetP gi124_n = opNetNew(mi, "gi124", "gi124", 0);
    optNetP gi125_n = opNetNew(mi, "gi125", "gi125", 0);
    optNetP gi126_n = opNetNew(mi, "gi126", "gi126", 0);
    optNetP gi127_n = opNetNew(mi, "gi127", "gi127", 0);

    // Processor S51

    const char *S51_path = opVLNVString(
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
        S51_path,
        "S51",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "INSTRUCTION"),
                OP_BUS_CONNECT(bus0_b, "DATA")
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(MTimerInterrupt0_n, "hart0_MTimerInterrupt"),
                OP_NET_CONNECT(MSWInterrupt0_n, "hart0_MSWInterrupt"),
                OP_NET_CONNECT(MExternalInterrupt0_n, "hart0_MExternalInterrupt"),
                OP_NET_CONNECT(LocalInterrupt0_n, "hart0_LocalInterrupt0"),
                OP_NET_CONNECT(LocalInterrupt1_n, "hart0_LocalInterrupt1"),
                OP_NET_CONNECT(LocalInterrupt2_n, "hart0_LocalInterrupt2"),
                OP_NET_CONNECT(LocalInterrupt3_n, "hart0_LocalInterrupt3"),
                OP_NET_CONNECT(LocalInterrupt4_n, "hart0_LocalInterrupt4"),
                OP_NET_CONNECT(LocalInterrupt5_n, "hart0_LocalInterrupt5"),
                OP_NET_CONNECT(LocalInterrupt6_n, "hart0_LocalInterrupt6"),
                OP_NET_CONNECT(LocalInterrupt7_n, "hart0_LocalInterrupt7"),
                OP_NET_CONNECT(LocalInterrupt8_n, "hart0_LocalInterrupt8"),
                OP_NET_CONNECT(LocalInterrupt9_n, "hart0_LocalInterrupt9"),
                OP_NET_CONNECT(LocalInterrupt10_n, "hart0_LocalInterrupt10"),
                OP_NET_CONNECT(LocalInterrupt11_n, "hart0_LocalInterrupt11"),
                OP_NET_CONNECT(LocalInterrupt12_n, "hart0_LocalInterrupt12"),
                OP_NET_CONNECT(LocalInterrupt13_n, "hart0_LocalInterrupt13"),
                OP_NET_CONNECT(LocalInterrupt14_n, "hart0_LocalInterrupt14"),
                OP_NET_CONNECT(LocalInterrupt15_n, "hart0_LocalInterrupt15"),
                OP_NET_CONNECT(resetNet_n, "hart0_reset")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_DOUBLE_SET("mips", 1000)
            ,OP_PARAM_ENUM_SET("variant", "S51")
            ,OP_PARAM_UNS32_SET("local_int_num", 16)
        )
    );


    // Memory safe0addr

    opMemoryNew(
        mi,
        "safe0addr",
        OP_PRIV_RWX,
        (0x7ULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x7ULL)
            )
        ),
        0
    );

    // Memory debugRAM

    opMemoryNew(
        mi,
        "debugRAM",
        OP_PRIV_RWX,
        (0x3ffULL) - (0x300ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x300ULL, .addrHi=0x3ffULL)
            )
        ),
        0
    );

    // Memory debugROM

    opMemoryNew(
        mi,
        "debugROM",
        OP_PRIV_RX,
        (0xfffULL) - (0x800ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x800ULL, .addrHi=0xfffULL)
            )
        ),
        0
    );

    // Memory hart0ITIM

    opMemoryNew(
        mi,
        "hart0ITIM",
        OP_PRIV_RWX,
        (0x8002000ULL) - (0x8000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x8000000ULL, .addrHi=0x8002000ULL)
            )
        ),
        0
    );

    // Memory hart0DTIM

    opMemoryNew(
        mi,
        "hart0DTIM",
        OP_PRIV_RWX,
        (0x8000ffffULL) - (0x80000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x80000000ULL, .addrHi=0x8000ffffULL)
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
                OP_NET_CONNECT(MSWInterrupt0_n, "MSWInterrupt0")
            )
        ),
        0
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
                OP_NET_CONNECT(MExternalInterrupt0_n, "irqT0"),
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
                OP_NET_CONNECT(gi53_n, "irqS53"),
                OP_NET_CONNECT(gi54_n, "irqS54"),
                OP_NET_CONNECT(gi55_n, "irqS55"),
                OP_NET_CONNECT(gi56_n, "irqS56"),
                OP_NET_CONNECT(gi57_n, "irqS57"),
                OP_NET_CONNECT(gi58_n, "irqS58"),
                OP_NET_CONNECT(gi59_n, "irqS59"),
                OP_NET_CONNECT(gi60_n, "irqS60"),
                OP_NET_CONNECT(gi61_n, "irqS61"),
                OP_NET_CONNECT(gi62_n, "irqS62"),
                OP_NET_CONNECT(gi63_n, "irqS63"),
                OP_NET_CONNECT(gi64_n, "irqS64"),
                OP_NET_CONNECT(gi65_n, "irqS65"),
                OP_NET_CONNECT(gi66_n, "irqS66"),
                OP_NET_CONNECT(gi67_n, "irqS67"),
                OP_NET_CONNECT(gi68_n, "irqS68"),
                OP_NET_CONNECT(gi69_n, "irqS69"),
                OP_NET_CONNECT(gi70_n, "irqS70"),
                OP_NET_CONNECT(gi71_n, "irqS71"),
                OP_NET_CONNECT(gi72_n, "irqS72"),
                OP_NET_CONNECT(gi73_n, "irqS73"),
                OP_NET_CONNECT(gi74_n, "irqS74"),
                OP_NET_CONNECT(gi75_n, "irqS75"),
                OP_NET_CONNECT(gi76_n, "irqS76"),
                OP_NET_CONNECT(gi77_n, "irqS77"),
                OP_NET_CONNECT(gi78_n, "irqS78"),
                OP_NET_CONNECT(gi79_n, "irqS79"),
                OP_NET_CONNECT(gi80_n, "irqS80"),
                OP_NET_CONNECT(gi81_n, "irqS81"),
                OP_NET_CONNECT(gi82_n, "irqS82"),
                OP_NET_CONNECT(gi83_n, "irqS83"),
                OP_NET_CONNECT(gi84_n, "irqS84"),
                OP_NET_CONNECT(gi85_n, "irqS85"),
                OP_NET_CONNECT(gi86_n, "irqS86"),
                OP_NET_CONNECT(gi87_n, "irqS87"),
                OP_NET_CONNECT(gi88_n, "irqS88"),
                OP_NET_CONNECT(gi89_n, "irqS89"),
                OP_NET_CONNECT(gi90_n, "irqS90"),
                OP_NET_CONNECT(gi91_n, "irqS91"),
                OP_NET_CONNECT(gi92_n, "irqS92"),
                OP_NET_CONNECT(gi93_n, "irqS93"),
                OP_NET_CONNECT(gi94_n, "irqS94"),
                OP_NET_CONNECT(gi95_n, "irqS95"),
                OP_NET_CONNECT(gi96_n, "irqS96"),
                OP_NET_CONNECT(gi97_n, "irqS97"),
                OP_NET_CONNECT(gi98_n, "irqS98"),
                OP_NET_CONNECT(gi99_n, "irqS99"),
                OP_NET_CONNECT(gi100_n, "irqS100"),
                OP_NET_CONNECT(gi101_n, "irqS101"),
                OP_NET_CONNECT(gi102_n, "irqS102"),
                OP_NET_CONNECT(gi103_n, "irqS103"),
                OP_NET_CONNECT(gi104_n, "irqS104"),
                OP_NET_CONNECT(gi105_n, "irqS105"),
                OP_NET_CONNECT(gi106_n, "irqS106"),
                OP_NET_CONNECT(gi107_n, "irqS107"),
                OP_NET_CONNECT(gi108_n, "irqS108"),
                OP_NET_CONNECT(gi109_n, "irqS109"),
                OP_NET_CONNECT(gi110_n, "irqS110"),
                OP_NET_CONNECT(gi111_n, "irqS111"),
                OP_NET_CONNECT(gi112_n, "irqS112"),
                OP_NET_CONNECT(gi113_n, "irqS113"),
                OP_NET_CONNECT(gi114_n, "irqS114"),
                OP_NET_CONNECT(gi115_n, "irqS115"),
                OP_NET_CONNECT(gi116_n, "irqS116"),
                OP_NET_CONNECT(gi117_n, "irqS117"),
                OP_NET_CONNECT(gi118_n, "irqS118"),
                OP_NET_CONNECT(gi119_n, "irqS119"),
                OP_NET_CONNECT(gi120_n, "irqS120"),
                OP_NET_CONNECT(gi121_n, "irqS121"),
                OP_NET_CONNECT(gi122_n, "irqS122"),
                OP_NET_CONNECT(gi123_n, "irqS123"),
                OP_NET_CONNECT(gi124_n, "irqS124"),
                OP_NET_CONNECT(gi125_n, "irqS125"),
                OP_NET_CONNECT(gi126_n, "irqS126"),
                OP_NET_CONNECT(gi127_n, "irqS127")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("num_targets", 1)
            ,OP_PARAM_UNS32_SET("num_sources", 127)
        )
    );

}

static optBusPortInfo busPortSpecs[] = {
    {
        .name        = "systemPort",
        .description = 0,
    },
    { 0 }
};

static OP_BUS_PORT_FN(moduleBusPortIterator) {
    prev = prev ? prev + 1 : busPortSpecs; 
    return prev->name ? prev : 0;
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
    {
        .name        = "gi54",
        .description = 0,
    },
    {
        .name        = "gi55",
        .description = 0,
    },
    {
        .name        = "gi56",
        .description = 0,
    },
    {
        .name        = "gi57",
        .description = 0,
    },
    {
        .name        = "gi58",
        .description = 0,
    },
    {
        .name        = "gi59",
        .description = 0,
    },
    {
        .name        = "gi60",
        .description = 0,
    },
    {
        .name        = "gi61",
        .description = 0,
    },
    {
        .name        = "gi62",
        .description = 0,
    },
    {
        .name        = "gi63",
        .description = 0,
    },
    {
        .name        = "gi64",
        .description = 0,
    },
    {
        .name        = "gi65",
        .description = 0,
    },
    {
        .name        = "gi66",
        .description = 0,
    },
    {
        .name        = "gi67",
        .description = 0,
    },
    {
        .name        = "gi68",
        .description = 0,
    },
    {
        .name        = "gi69",
        .description = 0,
    },
    {
        .name        = "gi70",
        .description = 0,
    },
    {
        .name        = "gi71",
        .description = 0,
    },
    {
        .name        = "gi72",
        .description = 0,
    },
    {
        .name        = "gi73",
        .description = 0,
    },
    {
        .name        = "gi74",
        .description = 0,
    },
    {
        .name        = "gi75",
        .description = 0,
    },
    {
        .name        = "gi76",
        .description = 0,
    },
    {
        .name        = "gi77",
        .description = 0,
    },
    {
        .name        = "gi78",
        .description = 0,
    },
    {
        .name        = "gi79",
        .description = 0,
    },
    {
        .name        = "gi80",
        .description = 0,
    },
    {
        .name        = "gi81",
        .description = 0,
    },
    {
        .name        = "gi82",
        .description = 0,
    },
    {
        .name        = "gi83",
        .description = 0,
    },
    {
        .name        = "gi84",
        .description = 0,
    },
    {
        .name        = "gi85",
        .description = 0,
    },
    {
        .name        = "gi86",
        .description = 0,
    },
    {
        .name        = "gi87",
        .description = 0,
    },
    {
        .name        = "gi88",
        .description = 0,
    },
    {
        .name        = "gi89",
        .description = 0,
    },
    {
        .name        = "gi90",
        .description = 0,
    },
    {
        .name        = "gi91",
        .description = 0,
    },
    {
        .name        = "gi92",
        .description = 0,
    },
    {
        .name        = "gi93",
        .description = 0,
    },
    {
        .name        = "gi94",
        .description = 0,
    },
    {
        .name        = "gi95",
        .description = 0,
    },
    {
        .name        = "gi96",
        .description = 0,
    },
    {
        .name        = "gi97",
        .description = 0,
    },
    {
        .name        = "gi98",
        .description = 0,
    },
    {
        .name        = "gi99",
        .description = 0,
    },
    {
        .name        = "gi100",
        .description = 0,
    },
    {
        .name        = "gi101",
        .description = 0,
    },
    {
        .name        = "gi102",
        .description = 0,
    },
    {
        .name        = "gi103",
        .description = 0,
    },
    {
        .name        = "gi104",
        .description = 0,
    },
    {
        .name        = "gi105",
        .description = 0,
    },
    {
        .name        = "gi106",
        .description = 0,
    },
    {
        .name        = "gi107",
        .description = 0,
    },
    {
        .name        = "gi108",
        .description = 0,
    },
    {
        .name        = "gi109",
        .description = 0,
    },
    {
        .name        = "gi110",
        .description = 0,
    },
    {
        .name        = "gi111",
        .description = 0,
    },
    {
        .name        = "gi112",
        .description = 0,
    },
    {
        .name        = "gi113",
        .description = 0,
    },
    {
        .name        = "gi114",
        .description = 0,
    },
    {
        .name        = "gi115",
        .description = 0,
    },
    {
        .name        = "gi116",
        .description = 0,
    },
    {
        .name        = "gi117",
        .description = 0,
    },
    {
        .name        = "gi118",
        .description = 0,
    },
    {
        .name        = "gi119",
        .description = 0,
    },
    {
        .name        = "gi120",
        .description = 0,
    },
    {
        .name        = "gi121",
        .description = 0,
    },
    {
        .name        = "gi122",
        .description = 0,
    },
    {
        .name        = "gi123",
        .description = 0,
    },
    {
        .name        = "gi124",
        .description = 0,
    },
    {
        .name        = "gi125",
        .description = 0,
    },
    {
        .name        = "gi126",
        .description = 0,
    },
    {
        .name        = "gi127",
        .description = 0,
    },
    {
        .name        = "li0",
        .description = 0,
    },
    {
        .name        = "li1",
        .description = 0,
    },
    {
        .name        = "li2",
        .description = 0,
    },
    {
        .name        = "li3",
        .description = 0,
    },
    {
        .name        = "li4",
        .description = 0,
    },
    {
        .name        = "li5",
        .description = 0,
    },
    {
        .name        = "li6",
        .description = 0,
    },
    {
        .name        = "li7",
        .description = 0,
    },
    {
        .name        = "li8",
        .description = 0,
    },
    {
        .name        = "li9",
        .description = 0,
    },
    {
        .name        = "li10",
        .description = 0,
    },
    {
        .name        = "li11",
        .description = 0,
    },
    {
        .name        = "li12",
        .description = 0,
    },
    {
        .name        = "li13",
        .description = 0,
    },
    {
        .name        = "li14",
        .description = 0,
    },
    {
        .name        = "li15",
        .description = 0,
    },
    {
        .name        = "resetPort",
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
        .name    = "S51CC",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
    .busPortSpecsCB       = moduleBusPortIterator,
    .netPortSpecsCB       = moduleNetPortIterator,
};

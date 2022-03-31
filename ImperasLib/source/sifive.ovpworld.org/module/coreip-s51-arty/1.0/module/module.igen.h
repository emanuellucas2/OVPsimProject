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
    opDocTextAdd(doc_11_node, "SiFive coreip-s51-arty module.");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_21_node, "SiFive Freedom E SDK coreip-s51-arty Board Support Package details.");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_31_node, "None");


    // Bus systemBus

    optBusP systemBus_b = opBusNew(mi, "systemBus", 40, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP gi1_n = opNetNew(mi, "gi1", 0, 0);
    optNetP gi2_n = opNetNew(mi, "gi2", 0, 0);
    optNetP gi3_n = opNetNew(mi, "gi3", 0, 0);
    optNetP gi4_n = opNetNew(mi, "gi4", 0, 0);
    optNetP gi5_n = opNetNew(mi, "gi5", 0, 0);
    optNetP gi6_n = opNetNew(mi, "gi6", 0, 0);
    optNetP gi7_n = opNetNew(mi, "gi7", 0, 0);
    optNetP gi8_n = opNetNew(mi, "gi8", 0, 0);
    optNetP gi9_n = opNetNew(mi, "gi9", 0, 0);
    optNetP gi10_n = opNetNew(mi, "gi10", 0, 0);
    optNetP gi11_n = opNetNew(mi, "gi11", 0, 0);
    optNetP gi12_n = opNetNew(mi, "gi12", 0, 0);
    optNetP gi13_n = opNetNew(mi, "gi13", 0, 0);
    optNetP gi14_n = opNetNew(mi, "gi14", 0, 0);
    optNetP gi15_n = opNetNew(mi, "gi15", 0, 0);
    optNetP gi16_n = opNetNew(mi, "gi16", 0, 0);
    optNetP gi17_n = opNetNew(mi, "gi17", 0, 0);
    optNetP gi18_n = opNetNew(mi, "gi18", 0, 0);
    optNetP gi19_n = opNetNew(mi, "gi19", 0, 0);
    optNetP gi20_n = opNetNew(mi, "gi20", 0, 0);
    optNetP gi21_n = opNetNew(mi, "gi21", 0, 0);
    optNetP gi22_n = opNetNew(mi, "gi22", 0, 0);
    optNetP gi23_n = opNetNew(mi, "gi23", 0, 0);
    optNetP gi24_n = opNetNew(mi, "gi24", 0, 0);
    optNetP gi25_n = opNetNew(mi, "gi25", 0, 0);
    optNetP gi26_n = opNetNew(mi, "gi26", 0, 0);
    optNetP gi27_n = opNetNew(mi, "gi27", 0, 0);
    optNetP gi28_n = opNetNew(mi, "gi28", 0, 0);
    optNetP gi29_n = opNetNew(mi, "gi29", 0, 0);
    optNetP gi30_n = opNetNew(mi, "gi30", 0, 0);
    optNetP gi31_n = opNetNew(mi, "gi31", 0, 0);
    optNetP gi32_n = opNetNew(mi, "gi32", 0, 0);
    optNetP gi33_n = opNetNew(mi, "gi33", 0, 0);
    optNetP gi34_n = opNetNew(mi, "gi34", 0, 0);
    optNetP gi35_n = opNetNew(mi, "gi35", 0, 0);
    optNetP gi36_n = opNetNew(mi, "gi36", 0, 0);
    optNetP gi37_n = opNetNew(mi, "gi37", 0, 0);
    optNetP gi38_n = opNetNew(mi, "gi38", 0, 0);
    optNetP gi39_n = opNetNew(mi, "gi39", 0, 0);
    optNetP gi40_n = opNetNew(mi, "gi40", 0, 0);
    optNetP gi41_n = opNetNew(mi, "gi41", 0, 0);
    optNetP gi42_n = opNetNew(mi, "gi42", 0, 0);
    optNetP gi43_n = opNetNew(mi, "gi43", 0, 0);
    optNetP gi44_n = opNetNew(mi, "gi44", 0, 0);
    optNetP gi45_n = opNetNew(mi, "gi45", 0, 0);
    optNetP gi46_n = opNetNew(mi, "gi46", 0, 0);
    optNetP gi47_n = opNetNew(mi, "gi47", 0, 0);
    optNetP gi48_n = opNetNew(mi, "gi48", 0, 0);
    optNetP gi49_n = opNetNew(mi, "gi49", 0, 0);
    optNetP gi50_n = opNetNew(mi, "gi50", 0, 0);
    optNetP gi51_n = opNetNew(mi, "gi51", 0, 0);
    optNetP gi52_n = opNetNew(mi, "gi52", 0, 0);
    optNetP gi53_n = opNetNew(mi, "gi53", 0, 0);
    optNetP gi54_n = opNetNew(mi, "gi54", 0, 0);
    optNetP gi55_n = opNetNew(mi, "gi55", 0, 0);
    optNetP gi56_n = opNetNew(mi, "gi56", 0, 0);
    optNetP gi57_n = opNetNew(mi, "gi57", 0, 0);
    optNetP gi58_n = opNetNew(mi, "gi58", 0, 0);
    optNetP gi59_n = opNetNew(mi, "gi59", 0, 0);
    optNetP gi60_n = opNetNew(mi, "gi60", 0, 0);
    optNetP gi61_n = opNetNew(mi, "gi61", 0, 0);
    optNetP gi62_n = opNetNew(mi, "gi62", 0, 0);
    optNetP gi63_n = opNetNew(mi, "gi63", 0, 0);
    optNetP gi64_n = opNetNew(mi, "gi64", 0, 0);
    optNetP gi65_n = opNetNew(mi, "gi65", 0, 0);
    optNetP gi66_n = opNetNew(mi, "gi66", 0, 0);
    optNetP gi67_n = opNetNew(mi, "gi67", 0, 0);
    optNetP gi68_n = opNetNew(mi, "gi68", 0, 0);
    optNetP gi69_n = opNetNew(mi, "gi69", 0, 0);
    optNetP gi70_n = opNetNew(mi, "gi70", 0, 0);
    optNetP gi71_n = opNetNew(mi, "gi71", 0, 0);
    optNetP gi72_n = opNetNew(mi, "gi72", 0, 0);
    optNetP gi73_n = opNetNew(mi, "gi73", 0, 0);
    optNetP gi74_n = opNetNew(mi, "gi74", 0, 0);
    optNetP gi75_n = opNetNew(mi, "gi75", 0, 0);
    optNetP gi76_n = opNetNew(mi, "gi76", 0, 0);
    optNetP gi77_n = opNetNew(mi, "gi77", 0, 0);
    optNetP gi78_n = opNetNew(mi, "gi78", 0, 0);
    optNetP gi79_n = opNetNew(mi, "gi79", 0, 0);
    optNetP gi80_n = opNetNew(mi, "gi80", 0, 0);
    optNetP gi81_n = opNetNew(mi, "gi81", 0, 0);
    optNetP gi82_n = opNetNew(mi, "gi82", 0, 0);
    optNetP gi83_n = opNetNew(mi, "gi83", 0, 0);
    optNetP gi84_n = opNetNew(mi, "gi84", 0, 0);
    optNetP gi85_n = opNetNew(mi, "gi85", 0, 0);
    optNetP gi86_n = opNetNew(mi, "gi86", 0, 0);
    optNetP gi87_n = opNetNew(mi, "gi87", 0, 0);
    optNetP gi88_n = opNetNew(mi, "gi88", 0, 0);
    optNetP gi89_n = opNetNew(mi, "gi89", 0, 0);
    optNetP gi90_n = opNetNew(mi, "gi90", 0, 0);
    optNetP gi91_n = opNetNew(mi, "gi91", 0, 0);
    optNetP gi92_n = opNetNew(mi, "gi92", 0, 0);
    optNetP gi93_n = opNetNew(mi, "gi93", 0, 0);
    optNetP gi94_n = opNetNew(mi, "gi94", 0, 0);
    optNetP gi95_n = opNetNew(mi, "gi95", 0, 0);
    optNetP gi96_n = opNetNew(mi, "gi96", 0, 0);
    optNetP gi97_n = opNetNew(mi, "gi97", 0, 0);
    optNetP gi98_n = opNetNew(mi, "gi98", 0, 0);
    optNetP gi99_n = opNetNew(mi, "gi99", 0, 0);
    optNetP gi100_n = opNetNew(mi, "gi100", 0, 0);
    optNetP gi101_n = opNetNew(mi, "gi101", 0, 0);
    optNetP gi102_n = opNetNew(mi, "gi102", 0, 0);
    optNetP gi103_n = opNetNew(mi, "gi103", 0, 0);
    optNetP gi104_n = opNetNew(mi, "gi104", 0, 0);
    optNetP gi105_n = opNetNew(mi, "gi105", 0, 0);
    optNetP gi106_n = opNetNew(mi, "gi106", 0, 0);
    optNetP gi107_n = opNetNew(mi, "gi107", 0, 0);
    optNetP gi108_n = opNetNew(mi, "gi108", 0, 0);
    optNetP gi109_n = opNetNew(mi, "gi109", 0, 0);
    optNetP gi110_n = opNetNew(mi, "gi110", 0, 0);
    optNetP gi111_n = opNetNew(mi, "gi111", 0, 0);
    optNetP gi112_n = opNetNew(mi, "gi112", 0, 0);
    optNetP gi113_n = opNetNew(mi, "gi113", 0, 0);
    optNetP gi114_n = opNetNew(mi, "gi114", 0, 0);
    optNetP gi115_n = opNetNew(mi, "gi115", 0, 0);
    optNetP gi116_n = opNetNew(mi, "gi116", 0, 0);
    optNetP gi117_n = opNetNew(mi, "gi117", 0, 0);
    optNetP gi118_n = opNetNew(mi, "gi118", 0, 0);
    optNetP gi119_n = opNetNew(mi, "gi119", 0, 0);
    optNetP gi120_n = opNetNew(mi, "gi120", 0, 0);
    optNetP gi121_n = opNetNew(mi, "gi121", 0, 0);
    optNetP gi122_n = opNetNew(mi, "gi122", 0, 0);
    optNetP gi123_n = opNetNew(mi, "gi123", 0, 0);
    optNetP gi124_n = opNetNew(mi, "gi124", 0, 0);
    optNetP gi125_n = opNetNew(mi, "gi125", 0, 0);
    optNetP gi126_n = opNetNew(mi, "gi126", 0, 0);
    optNetP li0_n = opNetNew(mi, "li0", 0, 0);
    optNetP li1_n = opNetNew(mi, "li1", 0, 0);
    optNetP li2_n = opNetNew(mi, "li2", 0, 0);
    optNetP li3_n = opNetNew(mi, "li3", 0, 0);
    optNetP li4_n = opNetNew(mi, "li4", 0, 0);
    optNetP li5_n = opNetNew(mi, "li5", 0, 0);
    optNetP li6_n = opNetNew(mi, "li6", 0, 0);
    optNetP li7_n = opNetNew(mi, "li7", 0, 0);
    optNetP li8_n = opNetNew(mi, "li8", 0, 0);
    optNetP li9_n = opNetNew(mi, "li9", 0, 0);
    optNetP li10_n = opNetNew(mi, "li10", 0, 0);
    optNetP li11_n = opNetNew(mi, "li11", 0, 0);
    optNetP li12_n = opNetNew(mi, "li12", 0, 0);
    optNetP li13_n = opNetNew(mi, "li13", 0, 0);
    optNetP li14_n = opNetNew(mi, "li14", 0, 0);
    optNetP li15_n = opNetNew(mi, "li15", 0, 0);
    optNetP gpioout0_n = opNetNew(mi, "gpioout0", 0, 0);
    optNetP gpioout1_n = opNetNew(mi, "gpioout1", 0, 0);
    optNetP gpioout2_n = opNetNew(mi, "gpioout2", 0, 0);

    // Module Instance S51CC

    const char *S51CC_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "module",
        "S51CC",
        "1.0",
        OP_MODULE,
        OP_VLNV_PRINT
    );

    opParamDoubleOverride(mi, "S51CC/S51/mips", 65);
    opParamBoolOverride(mi, "S51CC/S51/time_undefined", "True");
    opParamDoubleOverride(mi, "S51CC/clint/clockMHz", 0.032768);
    opModuleNew(
        mi,       // parent module
        S51CC_path,       // modelfile
        "S51CC",   // name
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(systemBus_b, "systemPort")
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(gi1_n, "gi1"),
                OP_NET_CONNECT(gi2_n, "gi2"),
                OP_NET_CONNECT(gi3_n, "gi3"),
                OP_NET_CONNECT(gi4_n, "gi4"),
                OP_NET_CONNECT(gi5_n, "gi5"),
                OP_NET_CONNECT(gi6_n, "gi6"),
                OP_NET_CONNECT(gi7_n, "gi7"),
                OP_NET_CONNECT(gi8_n, "gi8"),
                OP_NET_CONNECT(gi9_n, "gi9"),
                OP_NET_CONNECT(gi10_n, "gi10"),
                OP_NET_CONNECT(gi11_n, "gi11"),
                OP_NET_CONNECT(gi12_n, "gi12"),
                OP_NET_CONNECT(gi13_n, "gi13"),
                OP_NET_CONNECT(gi14_n, "gi14"),
                OP_NET_CONNECT(gi15_n, "gi15"),
                OP_NET_CONNECT(gi16_n, "gi16"),
                OP_NET_CONNECT(gi17_n, "gi17"),
                OP_NET_CONNECT(gi18_n, "gi18"),
                OP_NET_CONNECT(gi19_n, "gi19"),
                OP_NET_CONNECT(gi20_n, "gi20"),
                OP_NET_CONNECT(gi21_n, "gi21"),
                OP_NET_CONNECT(gi22_n, "gi22"),
                OP_NET_CONNECT(gi23_n, "gi23"),
                OP_NET_CONNECT(gi24_n, "gi24"),
                OP_NET_CONNECT(gi25_n, "gi25"),
                OP_NET_CONNECT(gi26_n, "gi26"),
                OP_NET_CONNECT(gi27_n, "gi27"),
                OP_NET_CONNECT(gi28_n, "gi28"),
                OP_NET_CONNECT(gi29_n, "gi29"),
                OP_NET_CONNECT(gi30_n, "gi30"),
                OP_NET_CONNECT(gi31_n, "gi31"),
                OP_NET_CONNECT(gi32_n, "gi32"),
                OP_NET_CONNECT(gi33_n, "gi33"),
                OP_NET_CONNECT(gi34_n, "gi34"),
                OP_NET_CONNECT(gi35_n, "gi35"),
                OP_NET_CONNECT(gi36_n, "gi36"),
                OP_NET_CONNECT(gi37_n, "gi37"),
                OP_NET_CONNECT(gi38_n, "gi38"),
                OP_NET_CONNECT(gi39_n, "gi39"),
                OP_NET_CONNECT(gi40_n, "gi40"),
                OP_NET_CONNECT(gi41_n, "gi41"),
                OP_NET_CONNECT(gi42_n, "gi42"),
                OP_NET_CONNECT(gi43_n, "gi43"),
                OP_NET_CONNECT(gi44_n, "gi44"),
                OP_NET_CONNECT(gi45_n, "gi45"),
                OP_NET_CONNECT(gi46_n, "gi46"),
                OP_NET_CONNECT(gi47_n, "gi47"),
                OP_NET_CONNECT(gi48_n, "gi48"),
                OP_NET_CONNECT(gi49_n, "gi49"),
                OP_NET_CONNECT(gi50_n, "gi50"),
                OP_NET_CONNECT(gi51_n, "gi51"),
                OP_NET_CONNECT(gi52_n, "gi52"),
                OP_NET_CONNECT(gi53_n, "gi53"),
                OP_NET_CONNECT(gi54_n, "gi54"),
                OP_NET_CONNECT(gi55_n, "gi55"),
                OP_NET_CONNECT(gi56_n, "gi56"),
                OP_NET_CONNECT(gi57_n, "gi57"),
                OP_NET_CONNECT(gi58_n, "gi58"),
                OP_NET_CONNECT(gi59_n, "gi59"),
                OP_NET_CONNECT(gi60_n, "gi60"),
                OP_NET_CONNECT(gi61_n, "gi61"),
                OP_NET_CONNECT(gi62_n, "gi62"),
                OP_NET_CONNECT(gi63_n, "gi63"),
                OP_NET_CONNECT(gi64_n, "gi64"),
                OP_NET_CONNECT(gi65_n, "gi65"),
                OP_NET_CONNECT(gi66_n, "gi66"),
                OP_NET_CONNECT(gi67_n, "gi67"),
                OP_NET_CONNECT(gi68_n, "gi68"),
                OP_NET_CONNECT(gi69_n, "gi69"),
                OP_NET_CONNECT(gi70_n, "gi70"),
                OP_NET_CONNECT(gi71_n, "gi71"),
                OP_NET_CONNECT(gi72_n, "gi72"),
                OP_NET_CONNECT(gi73_n, "gi73"),
                OP_NET_CONNECT(gi74_n, "gi74"),
                OP_NET_CONNECT(gi75_n, "gi75"),
                OP_NET_CONNECT(gi76_n, "gi76"),
                OP_NET_CONNECT(gi77_n, "gi77"),
                OP_NET_CONNECT(gi78_n, "gi78"),
                OP_NET_CONNECT(gi79_n, "gi79"),
                OP_NET_CONNECT(gi80_n, "gi80"),
                OP_NET_CONNECT(gi81_n, "gi81"),
                OP_NET_CONNECT(gi82_n, "gi82"),
                OP_NET_CONNECT(gi83_n, "gi83"),
                OP_NET_CONNECT(gi84_n, "gi84"),
                OP_NET_CONNECT(gi85_n, "gi85"),
                OP_NET_CONNECT(gi86_n, "gi86"),
                OP_NET_CONNECT(gi87_n, "gi87"),
                OP_NET_CONNECT(gi88_n, "gi88"),
                OP_NET_CONNECT(gi89_n, "gi89"),
                OP_NET_CONNECT(gi90_n, "gi90"),
                OP_NET_CONNECT(gi91_n, "gi91"),
                OP_NET_CONNECT(gi92_n, "gi92"),
                OP_NET_CONNECT(gi93_n, "gi93"),
                OP_NET_CONNECT(gi94_n, "gi94"),
                OP_NET_CONNECT(gi95_n, "gi95"),
                OP_NET_CONNECT(gi96_n, "gi96"),
                OP_NET_CONNECT(gi97_n, "gi97"),
                OP_NET_CONNECT(gi98_n, "gi98"),
                OP_NET_CONNECT(gi99_n, "gi99"),
                OP_NET_CONNECT(gi100_n, "gi100"),
                OP_NET_CONNECT(gi101_n, "gi101"),
                OP_NET_CONNECT(gi102_n, "gi102"),
                OP_NET_CONNECT(gi103_n, "gi103"),
                OP_NET_CONNECT(gi104_n, "gi104"),
                OP_NET_CONNECT(gi105_n, "gi105"),
                OP_NET_CONNECT(gi106_n, "gi106"),
                OP_NET_CONNECT(gi107_n, "gi107"),
                OP_NET_CONNECT(gi108_n, "gi108"),
                OP_NET_CONNECT(gi109_n, "gi109"),
                OP_NET_CONNECT(gi110_n, "gi110"),
                OP_NET_CONNECT(gi111_n, "gi111"),
                OP_NET_CONNECT(gi112_n, "gi112"),
                OP_NET_CONNECT(gi113_n, "gi113"),
                OP_NET_CONNECT(gi114_n, "gi114"),
                OP_NET_CONNECT(gi115_n, "gi115"),
                OP_NET_CONNECT(gi116_n, "gi116"),
                OP_NET_CONNECT(gi117_n, "gi117"),
                OP_NET_CONNECT(gi118_n, "gi118"),
                OP_NET_CONNECT(gi119_n, "gi119"),
                OP_NET_CONNECT(gi120_n, "gi120"),
                OP_NET_CONNECT(gi121_n, "gi121"),
                OP_NET_CONNECT(gi122_n, "gi122"),
                OP_NET_CONNECT(gi123_n, "gi123"),
                OP_NET_CONNECT(gi124_n, "gi124"),
                OP_NET_CONNECT(gi125_n, "gi125"),
                OP_NET_CONNECT(gi126_n, "gi126"),
                OP_NET_CONNECT(li0_n, "li0"),
                OP_NET_CONNECT(li1_n, "li1"),
                OP_NET_CONNECT(li2_n, "li2"),
                OP_NET_CONNECT(li3_n, "li3"),
                OP_NET_CONNECT(li4_n, "li4"),
                OP_NET_CONNECT(li5_n, "li5"),
                OP_NET_CONNECT(li6_n, "li6"),
                OP_NET_CONNECT(li7_n, "li7"),
                OP_NET_CONNECT(li8_n, "li8"),
                OP_NET_CONNECT(li9_n, "li9"),
                OP_NET_CONNECT(li10_n, "li10"),
                OP_NET_CONNECT(li11_n, "li11"),
                OP_NET_CONNECT(li12_n, "li12"),
                OP_NET_CONNECT(li13_n, "li13"),
                OP_NET_CONNECT(li14_n, "li14"),
                OP_NET_CONNECT(li15_n, "li15")
            )
        ),
        0
    );

    // PSE tstatus

    const char *tstatus_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "teststatus",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        tstatus_path,
        "tstatus",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(systemBus_b, "bport1", .slave=1, .addrLo=0x4000ULL, .addrHi=0x4fffULL)
            )
        ),
        0
    );

    // PSE uart

    const char *uart_path = opVLNVString(
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
        uart_path,
        "uart",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(systemBus_b, "bport1", .slave=1, .addrLo=0x0020000000ULL, .addrHi=0x002000001bULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(gi1_n, "intOut")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("finishOnDisconnect", True)
            ,OP_PARAM_BOOL_SET("console", True)
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
                OP_BUS_CONNECT(systemBus_b, "bport1", .slave=1, .addrLo=0x0020002000ULL, .addrHi=0x0020002FFFULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(gi7_n, "intOut0"),
                OP_NET_CONNECT(gi8_n, "intOut1"),
                OP_NET_CONNECT(gi9_n, "intOut2"),
                OP_NET_CONNECT(gi10_n, "intOut3"),
                OP_NET_CONNECT(gi11_n, "intOut4"),
                OP_NET_CONNECT(gi12_n, "intOut5"),
                OP_NET_CONNECT(gi13_n, "intOut6"),
                OP_NET_CONNECT(gi14_n, "intOut7"),
                OP_NET_CONNECT(gi15_n, "intOut8"),
                OP_NET_CONNECT(gi16_n, "intOut9"),
                OP_NET_CONNECT(gi17_n, "intOut10"),
                OP_NET_CONNECT(gi18_n, "intOut11"),
                OP_NET_CONNECT(gi19_n, "intOut12"),
                OP_NET_CONNECT(gi20_n, "intOut13"),
                OP_NET_CONNECT(gi21_n, "intOut14"),
                OP_NET_CONNECT(gi22_n, "intOut15"),
                OP_NET_CONNECT(gpioout0_n, "gpios0"),
                OP_NET_CONNECT(gpioout1_n, "gpios1"),
                OP_NET_CONNECT(gpioout2_n, "gpios2"),
                OP_NET_CONNECT(li4_n, "gpios4"),
                OP_NET_CONNECT(li5_n, "gpios5"),
                OP_NET_CONNECT(li6_n, "gpios6"),
                OP_NET_CONNECT(li7_n, "gpios7")
            )
        ),
        0
    );

    // PSE io

    const char *io_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "artyIO",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        io_path,
        "io",
        OP_CONNECTIONS(
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(li0_n, "SW0"),
                OP_NET_CONNECT(li1_n, "SW1"),
                OP_NET_CONNECT(li2_n, "SW2"),
                OP_NET_CONNECT(li3_n, "SW3"),
                OP_NET_CONNECT(li4_n, "BTN0"),
                OP_NET_CONNECT(li5_n, "BTN1"),
                OP_NET_CONNECT(li6_n, "BTN2"),
                OP_NET_CONNECT(li7_n, "BTN3"),
                OP_NET_CONNECT(gpioout0_n, "LD0red"),
                OP_NET_CONNECT(gpioout1_n, "LD0green"),
                OP_NET_CONNECT(gpioout2_n, "LD0blue")
            )
        ),
        0
    );

    // PSE spi

    const char *spi_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "spi",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        spi_path,
        "spi",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(systemBus_b, "bport1", .slave=1, .addrLo=0x20004000ULL, .addrHi=0x20004fffULL),
                OP_BUS_CONNECT(systemBus_b, "mport1", .slave=1, .addrLo=0x0040000000ULL, .addrHi=0x005fffffffULL)
            )
        ),
        0
    );

    // PSE pwm

    const char *pwm_path = opVLNVString(
        0, // use the default VLNV path
        "sifive.ovpworld.org",
        "peripheral",
        "pwm",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        pwm_path,
        "pwm",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(systemBus_b, "bport1", .slave=1, .addrLo=0x20005000ULL, .addrHi=0x20005fffULL)
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
    .purpose              = OP_PP_MODULE,
    .visibility           = OP_VISIBLE,
    .vlnv          = {
        .vendor  = "sifive.ovpworld.org",
        .library = "module",
        .name    = "coreip-s51-arty",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

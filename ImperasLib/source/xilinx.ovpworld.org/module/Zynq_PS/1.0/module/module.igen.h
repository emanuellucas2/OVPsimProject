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
    opDocTextAdd(doc_11_node, "This module implements the Zynq 7000 Processing Sub-System (PS).\n          The PS integrates two ARM Cortex-A9 MPCore application processors, memories and peripherals.");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "This module provides the peripheral behavior required to boot a Linux Kernel or XtratuM hypervisor.");
    opDocTextAdd(doc_21_node, "Some of the peripherals are register-only, non-functional models. See the individual peripheral model documentation for details.");
    opDocTextAdd(doc_21_node, "Snoop Control Unit is not implemented, Trust Zone memory protection is not implemented");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "ZC702 Board user Guide UG850 (v1.5) September 4,2015 (ug850-zc702-eval-bd.pdf) and\n               ZC706 Evaluation Board for the Zynq-7000 XC7Z045 All Programmable SoC (v1.6) March 29, 2016 (ug954-zc706-eval-bd-xc7z04-ap-soc.pdf) and\n               Zynq-7000 AP SoC Technical Reference Manual UG585 (v1.10) February 23, 2015 (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)");
    // Variables indicating when parameters are set
    Bool armmips_isSet            = 0;
    Bool psclock_isSet            = 0;

    // Variables holding parameter values
    UNUSED Uns32        armmips                  = opObjectParamUns32Value(mi, "armmips", &armmips_isSet);
    UNUSED const char * flashtype                = opObjectParamStringValue(mi, "flashtype");
    UNUSED Uns32        psclock                  = opObjectParamUns32Value(mi, "psclock", &psclock_isSet);
    UNUSED const char * board                    = opObjectParamStringValue(mi, "board");


    // Bus pBus

    optBusP pBus_b = opBusNew(mi, "pBus", 32, 0, 0);


    // Bus ddrBus

    optBusP ddrBus_b = opBusNew(mi, "ddrBus", 32, 0, 0);


    // Bus ddrSBus

    optBusP ddrSBus_b = opBusNew(mi, "ddrSBus", 32, 0, 0);


    // Bus extPortBus

    optBusP extPortBus_b = opBusNew(mi, "extPortBus", 32, "extPort", 0);


    // Bus apbBus

    optBusP apbBus_b = opBusNew(mi, "apbBus", 32, 0, 0);


    // Bus ocmBus

    optBusP ocmBus_b = opBusNew(mi, "ocmBus", 32, 0, 0);


    // Bus i2cBus

    optBusP i2cBus_b = opBusNew(mi, "i2cBus", 16, "extPortI2C", 0);


    // Bus xadcBus

    optBusP xadcBus_b = opBusNew(mi, "xadcBus", 16, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP l2cache_spi34_n = opNetNew(mi, "l2cache_spi34", 0, 0);
    optNetP ocm_spi35_n = opNetNew(mi, "ocm_spi35", 0, 0);
    optNetP pmu0_spi37_n = opNetNew(mi, "pmu0_spi37", 0, 0);
    optNetP pmu1_spi38_n = opNetNew(mi, "pmu1_spi38", 0, 0);
    optNetP xadc_spi39_n = opNetNew(mi, "xadc_spi39", 0, 0);
    optNetP devc_spi40_n = opNetNew(mi, "devc_spi40", 0, 0);
    optNetP swdt_spi41_n = opNetNew(mi, "swdt_spi41", 0, 0);
    optNetP ttc0_spi42_n = opNetNew(mi, "ttc0_spi42", 0, 0);
    optNetP ttc0_spi43_n = opNetNew(mi, "ttc0_spi43", 0, 0);
    optNetP ttc0_spi44_n = opNetNew(mi, "ttc0_spi44", 0, 0);
    optNetP dmaca_spi45_n = opNetNew(mi, "dmaca_spi45", "irqp2f28_outP", 0);
    optNetP dmac0_spi46_n = opNetNew(mi, "dmac0_spi46", "irqp2f20_outP", 0);
    optNetP dmac1_spi47_n = opNetNew(mi, "dmac1_spi47", "irqp2f21_outP", 0);
    optNetP dmac2_spi48_n = opNetNew(mi, "dmac2_spi48", "irqp2f22_outP", 0);
    optNetP dmac3_spi49_n = opNetNew(mi, "dmac3_spi49", "irqp2f23_outP", 0);
    optNetP smc_spi50_n = opNetNew(mi, "smc_spi50", "irqp2f19_outP", 0);
    optNetP qspi_spi51_n = opNetNew(mi, "qspi_spi51", "irqp2f18_outP", 0);
    optNetP gpio_spi52_n = opNetNew(mi, "gpio_spi52", "irqp2f16_outP", 0);
    optNetP usb0_spi53_n = opNetNew(mi, "usb0_spi53", "irqp2f15_outP", 0);
    optNetP eth0_spi54_n = opNetNew(mi, "eth0_spi54", "irqp2f14_outP", 0);
    optNetP eth0wu_spi55_n = opNetNew(mi, "eth0wu_spi55", "irqp2f13_outP", 0);
    optNetP sdio0_spi56_n = opNetNew(mi, "sdio0_spi56", "irqp2f12_outP", 0);
    optNetP i2c0_spi57_n = opNetNew(mi, "i2c0_spi57", "irqp2f11_outP", 0);
    optNetP spi0_spi58_n = opNetNew(mi, "spi0_spi58", "irqp2f10_outP", 0);
    optNetP uart0_spi59_n = opNetNew(mi, "uart0_spi59", "irqp2f9_outP", 0);
    optNetP can0_spi60_n = opNetNew(mi, "can0_spi60", "irqp2f8_outP", 0);
    optNetP ttc1_spi69_n = opNetNew(mi, "ttc1_spi69", 0, 0);
    optNetP ttc1_spi70_n = opNetNew(mi, "ttc1_spi70", 0, 0);
    optNetP ttc1_spi71_n = opNetNew(mi, "ttc1_spi71", 0, 0);
    optNetP dmac4_spi72_n = opNetNew(mi, "dmac4_spi72", "irqp2f24_outP", 0);
    optNetP dmac5_spi73_n = opNetNew(mi, "dmac5_spi73", "irqp2f25_outP", 0);
    optNetP dmac6_spi74_n = opNetNew(mi, "dmac6_spi74", "irqp2f26_outP", 0);
    optNetP dmac7_spi75_n = opNetNew(mi, "dmac7_spi75", "irqp2f27_outP", 0);
    optNetP usb1_spi76_n = opNetNew(mi, "usb1_spi76", "irqp2f7_outP", 0);
    optNetP eth1_spi77_n = opNetNew(mi, "eth1_spi77", "irqp2f6_outP", 0);
    optNetP eth1wu_spi78_n = opNetNew(mi, "eth1wu_spi78", "irqp2f5_outP", 0);
    optNetP sdio1_spi79_n = opNetNew(mi, "sdio1_spi79", "irqp2f4_outP", 0);
    optNetP i2c1_spi80_n = opNetNew(mi, "i2c1_spi80", "irqp2f3_outP", 0);
    optNetP spi1_spi81_n = opNetNew(mi, "spi1_spi81", "irqp2f2_outP", 0);
    optNetP uart1_spi82_n = opNetNew(mi, "uart1_spi82", "irqp2f1_outP", 0);
    optNetP can1_spi83_n = opNetNew(mi, "can1_spi83", "irqp2f0_outP", 0);
    optNetP spup_spi92_n = opNetNew(mi, "spup_spi92", 0, 0);
    optNetP reset_A9_CPU0_n = opNetNew(mi, "reset_A9_CPU0", 0, 0);
    optNetP reset_A9_CPU1_n = opNetNew(mi, "reset_A9_CPU1", 0, 0);
    optNetP irqf2p0_n = opNetNew(mi, "irqf2p0", "irqf2p0_inP", 0);
    optNetP irqf2p1_n = opNetNew(mi, "irqf2p1", "irqf2p1_inP", 0);
    optNetP irqf2p2_n = opNetNew(mi, "irqf2p2", "irqf2p2_inP", 0);
    optNetP irqf2p3_n = opNetNew(mi, "irqf2p3", "irqf2p3_inP", 0);
    optNetP irqf2p4_n = opNetNew(mi, "irqf2p4", "irqf2p4_inP", 0);
    optNetP irqf2p5_n = opNetNew(mi, "irqf2p5", "irqf2p5_inP", 0);
    optNetP irqf2p6_n = opNetNew(mi, "irqf2p6", "irqf2p6_inP", 0);
    optNetP irqf2p7_n = opNetNew(mi, "irqf2p7", "irqf2p7_inP", 0);
    optNetP irqf2p8_n = opNetNew(mi, "irqf2p8", "irqf2p8_inP", 0);
    optNetP irqf2p9_n = opNetNew(mi, "irqf2p9", "irqf2p9_inP", 0);
    optNetP irqf2p10_n = opNetNew(mi, "irqf2p10", "irqf2p10_inP", 0);
    optNetP irqf2p11_n = opNetNew(mi, "irqf2p11", "irqf2p11_inP", 0);
    optNetP irqf2p12_n = opNetNew(mi, "irqf2p12", "irqf2p12_inP", 0);
    optNetP irqf2p13_n = opNetNew(mi, "irqf2p13", "irqf2p13_inP", 0);
    optNetP irqf2p14_n = opNetNew(mi, "irqf2p14", "irqf2p14_inP", 0);
    optNetP irqf2p15_n = opNetNew(mi, "irqf2p15", "irqf2p15_inP", 0);
    optNetP irqf2p16_n = opNetNew(mi, "irqf2p16", "irqf2p16_inP", 0);
    optNetP irqf2p17_n = opNetNew(mi, "irqf2p17", "irqf2p17_inP", 0);
    optNetP irqf2p18_n = opNetNew(mi, "irqf2p18", "irqf2p18_inP", 0);
    optNetP irqf2p19_n = opNetNew(mi, "irqf2p19", "irqf2p19_inP", 0);
    opNetNew(mi, "irqp2f17", "irqp2f17_outP", 0);
    optNetP xadcmux_n = opNetNew(mi, "xadcmux", "extPortXADCMux", 0);
    optNetP gpio_bank0_out_n = opNetNew(mi, "gpio_bank0_out", "gpio_bank0_outP", 0);
    optNetP gpio_bank0_in_n = opNetNew(mi, "gpio_bank0_in", "gpio_bank0_inP", 0);
    optNetP gpio_bank1_out_n = opNetNew(mi, "gpio_bank1_out", "gpio_bank1_outP", 0);
    optNetP gpio_bank1_in_n = opNetNew(mi, "gpio_bank1_in", "gpio_bank1_inP", 0);
    optNetP gpio_bank2_out_n = opNetNew(mi, "gpio_bank2_out", "gpio_bank2_outP", 0);
    optNetP gpio_bank2_oen_out_n = opNetNew(mi, "gpio_bank2_oen_out", "gpio_bank2_oen_outP", 0);
    optNetP gpio_bank2_in_n = opNetNew(mi, "gpio_bank2_in", "gpio_bank2_inP", 0);
    optNetP gpio_bank3_out_n = opNetNew(mi, "gpio_bank3_out", "gpio_bank3_outP", 0);
    optNetP gpio_bank3_oen_out_n = opNetNew(mi, "gpio_bank3_oen_out", "gpio_bank3_oen_outP", 0);
    optNetP gpio_bank3_in_n = opNetNew(mi, "gpio_bank3_in", "gpio_bank3_inP", 0);
    optNetP ARM0Deration_n = opNetNew(mi, "ARM0Deration", 0, 0);
    optNetP ARM1Deration_n = opNetNew(mi, "ARM1Deration", 0, 0);

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
                OP_NET_CONNECT(l2cache_spi34_n, "SPI34"),
                OP_NET_CONNECT(ocm_spi35_n, "SPI35"),
                OP_NET_CONNECT(pmu0_spi37_n, "SPI37"),
                OP_NET_CONNECT(pmu1_spi38_n, "SPI38"),
                OP_NET_CONNECT(xadc_spi39_n, "SPI39"),
                OP_NET_CONNECT(devc_spi40_n, "SPI40"),
                OP_NET_CONNECT(swdt_spi41_n, "SPI41"),
                OP_NET_CONNECT(ttc0_spi42_n, "SPI42"),
                OP_NET_CONNECT(ttc0_spi43_n, "SPI43"),
                OP_NET_CONNECT(ttc0_spi44_n, "SPI44"),
                OP_NET_CONNECT(dmaca_spi45_n, "SPI45"),
                OP_NET_CONNECT(dmac0_spi46_n, "SPI46"),
                OP_NET_CONNECT(dmac1_spi47_n, "SPI47"),
                OP_NET_CONNECT(dmac2_spi48_n, "SPI48"),
                OP_NET_CONNECT(dmac3_spi49_n, "SPI49"),
                OP_NET_CONNECT(smc_spi50_n, "SPI50"),
                OP_NET_CONNECT(qspi_spi51_n, "SPI51"),
                OP_NET_CONNECT(gpio_spi52_n, "SPI52"),
                OP_NET_CONNECT(usb0_spi53_n, "SPI53"),
                OP_NET_CONNECT(eth0_spi54_n, "SPI54"),
                OP_NET_CONNECT(eth0wu_spi55_n, "SPI55"),
                OP_NET_CONNECT(sdio0_spi56_n, "SPI56"),
                OP_NET_CONNECT(i2c0_spi57_n, "SPI57"),
                OP_NET_CONNECT(spi0_spi58_n, "SPI58"),
                OP_NET_CONNECT(uart0_spi59_n, "SPI59"),
                OP_NET_CONNECT(can0_spi60_n, "SPI60"),
                OP_NET_CONNECT(ttc1_spi69_n, "SPI69"),
                OP_NET_CONNECT(ttc1_spi70_n, "SPI70"),
                OP_NET_CONNECT(ttc1_spi71_n, "SPI71"),
                OP_NET_CONNECT(dmac4_spi72_n, "SPI72"),
                OP_NET_CONNECT(dmac5_spi73_n, "SPI73"),
                OP_NET_CONNECT(dmac6_spi74_n, "SPI74"),
                OP_NET_CONNECT(dmac7_spi75_n, "SPI75"),
                OP_NET_CONNECT(usb1_spi76_n, "SPI76"),
                OP_NET_CONNECT(eth1_spi77_n, "SPI77"),
                OP_NET_CONNECT(eth1wu_spi78_n, "SPI78"),
                OP_NET_CONNECT(sdio1_spi79_n, "SPI79"),
                OP_NET_CONNECT(i2c1_spi80_n, "SPI80"),
                OP_NET_CONNECT(spi1_spi81_n, "SPI81"),
                OP_NET_CONNECT(uart1_spi82_n, "SPI82"),
                OP_NET_CONNECT(can1_spi83_n, "SPI83"),
                OP_NET_CONNECT(spup_spi92_n, "SPI92"),
                OP_NET_CONNECT(irqf2p0_n, "SPI61"),
                OP_NET_CONNECT(irqf2p1_n, "SPI62"),
                OP_NET_CONNECT(irqf2p2_n, "SPI63"),
                OP_NET_CONNECT(irqf2p3_n, "SPI64"),
                OP_NET_CONNECT(irqf2p4_n, "SPI65"),
                OP_NET_CONNECT(irqf2p5_n, "SPI66"),
                OP_NET_CONNECT(irqf2p6_n, "SPI67"),
                OP_NET_CONNECT(irqf2p7_n, "SPI68"),
                OP_NET_CONNECT(irqf2p8_n, "SPI84"),
                OP_NET_CONNECT(irqf2p9_n, "SPI85"),
                OP_NET_CONNECT(irqf2p10_n, "SPI86"),
                OP_NET_CONNECT(irqf2p11_n, "SPI87"),
                OP_NET_CONNECT(irqf2p12_n, "SPI88"),
                OP_NET_CONNECT(irqf2p13_n, "SPI89"),
                OP_NET_CONNECT(irqf2p14_n, "SPI90"),
                OP_NET_CONNECT(irqf2p15_n, "SPI91"),
                OP_NET_CONNECT(irqf2p16_n, "irq_CPU0"),
                OP_NET_CONNECT(irqf2p17_n, "fiq_CPU0"),
                OP_NET_CONNECT(irqf2p18_n, "irq_CPU1"),
                OP_NET_CONNECT(irqf2p19_n, "fiq_CPU1"),
                OP_NET_CONNECT(reset_A9_CPU0_n, "reset_CPU0"),
                OP_NET_CONNECT(reset_A9_CPU1_n, "reset_CPU1")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_DOUBLE_SET("mips", armmips)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_ENUM_SET("variant", "Cortex-A9MPx2")
            ,OP_PARAM_ENUM_SET("compatibility", "ISA")
            ,OP_PARAM_BOOL_SET("UAL", 1)
            ,OP_PARAM_UNS32_SET("override_CBAR", 0xf8f00000)
            ,OP_PARAM_UNS32_SET("override_MIDR", 0x413fc090)
        )
    );


    // Memory DDR0

    opMemoryNew(
        mi,
        "DDR0",
        OP_PRIV_RWX,
        (0x3ffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(ddrBus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x3ffffULL)
            )
        ),
        0
    );

    // Memory DDR1

    opMemoryNew(
        mi,
        "DDR1",
        OP_PRIV_RWX,
        (0x7ffffULL) - (0x40000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(ddrBus_b, "sp1", .slave=1, .addrLo=0x40000ULL, .addrHi=0x7ffffULL)
            )
        ),
        0
    );

    // Memory DDR2

    opMemoryNew(
        mi,
        "DDR2",
        OP_PRIV_RWX,
        (0xfffffULL) - (0x80000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(ddrBus_b, "sp1", .slave=1, .addrLo=0x80000ULL, .addrHi=0xfffffULL)
            )
        ),
        0
    );

    // Memory DDR3

    opMemoryNew(
        mi,
        "DDR3",
        OP_PRIV_RWX,
        (0x3fffffffULL) - (0x100000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(ddrSBus_b, "sp1", .slave=1, .addrLo=0x100000ULL, .addrHi=0x3fffffffULL)
            )
        ),
        0
    );

    // Memory ocm

    opMemoryNew(
        mi,
        "ocm",
        OP_PRIV_RWX,
        (0x3ffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(ocmBus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x3ffffULL)
            )
        ),
        0
    );

    // Memory xadcMem

    opMemoryNew(
        mi,
        "xadcMem",
        OP_PRIV_RWX,
        (0x3ffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(xadcBus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x3ffULL)
            )
        ),
        0
    );

    // Bridge brPtoDDR

    opBridgeNew(
        mi,
        "brPtoDDR",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(ddrBus_b, "mp1", .addrLo=0x0ULL, .addrHi=0xfffffULL),
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0xfffffULL)
            )
        ),
        0
    );

    // Bridge brPtoDDRS

    opBridgeNew(
        mi,
        "brPtoDDRS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(ddrSBus_b, "mp1", .addrLo=0x100000ULL, .addrHi=0x3fffffffULL),
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x100000ULL, .addrHi=0x3fffffffULL)
            )
        ),
        0
    );

    // Bridge extPorttoDDRS

    opBridgeNew(
        mi,
        "extPorttoDDRS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(ddrSBus_b, "mp1", .addrLo=0x100000ULL, .addrHi=0x3fffffffULL),
                OP_BUS_CONNECT(extPortBus_b, "sp1", .slave=1, .addrLo=0x100000ULL, .addrHi=0x3fffffffULL)
            )
        ),
        0
    );

    // Bridge extPorttoAPB

    opBridgeNew(
        mi,
        "extPorttoAPB",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(apbBus_b, "mp1", .addrLo=0xe0000000ULL, .addrHi=0xe0101fffULL),
                OP_BUS_CONNECT(extPortBus_b, "sp1", .slave=1, .addrLo=0xe0000000ULL, .addrHi=0xe0101fffULL)
            )
        ),
        0
    );

    // Bridge pBustoAPB

    opBridgeNew(
        mi,
        "pBustoAPB",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(apbBus_b, "mp1", .addrLo=0xe0000000ULL, .addrHi=0xe0101fffULL),
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0xe0000000ULL, .addrHi=0xe0101fffULL)
            )
        ),
        0
    );

    // Bridge pBustoExtPort

    opBridgeNew(
        mi,
        "pBustoExtPort",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(extPortBus_b, "mp1", .addrLo=0x40000000ULL, .addrHi=0xbfffffffULL),
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x40000000ULL, .addrHi=0xbfffffffULL)
            )
        ),
        0
    );

    // PSE uart0

    const char *uart0_path = opVLNVString(
        0, // use the default VLNV path
        "cadence.ovpworld.org",
        0,
        "uart",
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
                OP_BUS_CONNECT(apbBus_b, "bport1", .slave=1, .addrLo=0xe0000000ULL, .addrHi=0xe0000fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(uart0_spi59_n, "irq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_STRING_SET("outfile", "uart0.log")
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
            ,OP_PARAM_BOOL_SET("console", 1)
            ,OP_PARAM_UNS32_SET("xchars", 130)
            ,OP_PARAM_UNS32_SET("ychars", 30)
        )
    );

    // PSE uart1

    const char *uart1_path = opVLNVString(
        0, // use the default VLNV path
        "cadence.ovpworld.org",
        0,
        "uart",
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
                OP_BUS_CONNECT(apbBus_b, "bport1", .slave=1, .addrLo=0xe0001000ULL, .addrHi=0xe0001fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(uart1_spi82_n, "irq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_STRING_SET("outfile", "uart1.log")
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
            ,OP_PARAM_BOOL_SET("console", 1)
            ,OP_PARAM_UNS32_SET("xchars", 130)
            ,OP_PARAM_UNS32_SET("ychars", 30)
        )
    );

    // PSE usb0

    const char *usb0_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "peripheral",
        "zynq_7000-usb",
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
                OP_BUS_CONNECT(apbBus_b, "bport1", .slave=1, .addrLo=0xe0002000ULL, .addrHi=0xe0002fffULL)
            )
        ),
        0
    );

    // PSE usb1

    const char *usb1_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "peripheral",
        "zynq_7000-usb",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        usb1_path,
        "usb1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(apbBus_b, "bport1", .slave=1, .addrLo=0xe0003000ULL, .addrHi=0xe0003fffULL)
            )
        ),
        0
    );

    // PSE i2c0

    const char *i2c0_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "peripheral",
        "zynq_7000-iic",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        i2c0_path,
        "i2c0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(i2cBus_b, "I2C_Master"),
                OP_BUS_CONNECT(apbBus_b, "bport1", .slave=1, .addrLo=0xe0004000ULL, .addrHi=0xe0004fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(i2c0_spi57_n, "intOut")
            )
        ),
        0
    );

    // PSE i2c1

    const char *i2c1_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "peripheral",
        "zynq_7000-iic",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        i2c1_path,
        "i2c1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(apbBus_b, "bport1", .slave=1, .addrLo=0xe0005000ULL, .addrHi=0xe0005fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(i2c1_spi80_n, "intOut")
            )
        ),
        0
    );

    // PSE spi0

    const char *spi0_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "peripheral",
        "zynq_7000-spi",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        spi0_path,
        "spi0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(apbBus_b, "bport1", .slave=1, .addrLo=0xe0006000ULL, .addrHi=0xe0006fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(spi0_spi58_n, "intOut")
            )
        ),
        0
    );

    // PSE spi1

    const char *spi1_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "peripheral",
        "zynq_7000-spi",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        spi1_path,
        "spi1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(apbBus_b, "bport1", .slave=1, .addrLo=0xe0007000ULL, .addrHi=0xe0007fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(spi1_spi81_n, "intOut")
            )
        ),
        0
    );

    // PSE can0

    const char *can0_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "peripheral",
        "zynq_7000-can",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        can0_path,
        "can0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(apbBus_b, "bport1", .slave=1, .addrLo=0xe0008000ULL, .addrHi=0xe0008fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(can0_spi60_n, "intOut")
            )
        ),
        0
    );

    // PSE can1

    const char *can1_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "peripheral",
        "zynq_7000-can",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        can1_path,
        "can1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(apbBus_b, "bport1", .slave=1, .addrLo=0xe0009000ULL, .addrHi=0xe0009fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(can1_spi83_n, "intOut")
            )
        ),
        0
    );

    // PSE GPIO

    const char *GPIO_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "peripheral",
        "zynq_7000-gpio",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        GPIO_path,
        "GPIO",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(apbBus_b, "bport1", .slave=1, .addrLo=0xe000a000ULL, .addrHi=0xe000afffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(gpio_spi52_n, "intOut"),
                OP_NET_CONNECT(gpio_bank0_out_n, "gpio_bank0_out"),
                OP_NET_CONNECT(gpio_bank0_in_n, "gpio_bank0_in"),
                OP_NET_CONNECT(gpio_bank1_out_n, "gpio_bank1_out"),
                OP_NET_CONNECT(gpio_bank1_in_n, "gpio_bank1_in"),
                OP_NET_CONNECT(gpio_bank2_out_n, "gpio_bank2_out"),
                OP_NET_CONNECT(gpio_bank2_oen_out_n, "gpio_bank2_oen_out"),
                OP_NET_CONNECT(gpio_bank2_in_n, "gpio_bank2_in"),
                OP_NET_CONNECT(gpio_bank3_out_n, "gpio_bank3_out"),
                OP_NET_CONNECT(gpio_bank3_oen_out_n, "gpio_bank3_oen_out"),
                OP_NET_CONNECT(gpio_bank3_in_n, "gpio_bank3_in")
            )
        ),
        0
    );

    // PSE eth0

    const char *eth0_path = opVLNVString(
        0, // use the default VLNV path
        "cadence.ovpworld.org",
        "peripheral",
        "gem",
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
                OP_BUS_CONNECT(pBus_b, "bport2"),
                OP_BUS_CONNECT(apbBus_b, "bport1", .slave=1, .addrLo=0xe000b000ULL, .addrHi=0xe000bfffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(eth0_spi54_n, "irq")
            )
        ),
        0
    );

    // PSE eth1

    const char *eth1_path = opVLNVString(
        0, // use the default VLNV path
        "cadence.ovpworld.org",
        "peripheral",
        "gem",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        eth1_path,
        "eth1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport2"),
                OP_BUS_CONNECT(apbBus_b, "bport1", .slave=1, .addrLo=0xe000c000ULL, .addrHi=0xe000cfffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(eth1_spi77_n, "irq")
            )
        ),
        0
    );

    // PSE qspi

    const char *qspi_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "peripheral",
        "zynq_7000-qspi",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        qspi_path,
        "qspi",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(apbBus_b, "bpAPB", .slave=1, .addrLo=0xe000d000ULL, .addrHi=0xe000dfffULL),
                OP_BUS_CONNECT(apbBus_b, "bpAXI", .slave=1, .addrLo=0xfc000000ULL, .addrHi=0xfdffffffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(qspi_spi51_n, "interrupt")
            )
        ),
        OP_PARAMS(
             OP_PARAM_STRING_SET("flash", flashtype)
        )
    );

    // PSE dummySMC

    const char *dummySMC_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        "peripheral",
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        dummySMC_path,
        "dummySMC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(apbBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xe000e000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
        )
    );

    // PSE dummyUnknown1

    const char *dummyUnknown1_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        "peripheral",
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        dummyUnknown1_path,
        "dummyUnknown1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(apbBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xe000f000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
        )
    );

    // PSE sdio0

    const char *sdio0_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "peripheral",
        "zynq_7000-sdio",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        sdio0_path,
        "sdio0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(apbBus_b, "bport1", .slave=1, .addrLo=0xe0100000ULL, .addrHi=0xe0100fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(sdio0_spi56_n, "intOut")
            )
        ),
        0
    );

    // PSE sdio1

    const char *sdio1_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "peripheral",
        "zynq_7000-sdio",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        sdio1_path,
        "sdio1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(apbBus_b, "bport1", .slave=1, .addrLo=0xe0101000ULL, .addrHi=0xe0101fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(sdio1_spi79_n, "intOut")
            )
        ),
        0
    );

    // PSE trustzone_security

    const char *trustzone_security_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "peripheral",
        "zynq_7000-tz_security",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        trustzone_security_path,
        "trustzone_security",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0xe0200000ULL, .addrHi=0xe020001fULL)
            )
        ),
        0
    );

    // PSE slcr

    const char *slcr_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        0,
        "zynq_7000-slcr",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        slcr_path,
        "slcr",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(ocmBus_b, "mpOCM"),
                OP_BUS_CONNECT(ddrBus_b, "mpDDR"),
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0xf8000000ULL, .addrHi=0xf8000bffULL),
                OP_BUS_CONNECT(pBus_b, "spOCMDDR", .slave=1, .dynamic=1)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(reset_A9_CPU0_n, "A9_RST0"),
                OP_NET_CONNECT(reset_A9_CPU1_n, "A9_RST1"),
                OP_NET_CONNECT(ARM0Deration_n, "ARM0Deration"),
                OP_NET_CONNECT(ARM1Deration_n, "ARM1Deration")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("deviceid", 0x11)
            ,OP_PARAM_UNS32_SET("psclock", psclock)
            ,OP_PARAM_UNS32_SET("armmips", armmips)
        )
    );

    // PSE ttc0

    const char *ttc0_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "peripheral",
        "zynq_7000-ttc",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ttc0_path,
        "ttc0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0xf8001000ULL, .addrHi=0xf8001fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ttc0_spi42_n, "int1"),
                OP_NET_CONNECT(ttc0_spi43_n, "int2"),
                OP_NET_CONNECT(ttc0_spi44_n, "int3")
            )
        ),
        0
    );

    // PSE ttc1

    const char *ttc1_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "peripheral",
        "zynq_7000-ttc",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ttc1_path,
        "ttc1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0xf8002000ULL, .addrHi=0xf8002fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ttc1_spi69_n, "int1"),
                OP_NET_CONNECT(ttc1_spi70_n, "int2"),
                OP_NET_CONNECT(ttc1_spi71_n, "int3")
            )
        ),
        0
    );

    // PSE DMAC

    const char *DMAC_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "peripheral",
        "zynq_7000-dmac",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        DMAC_path,
        "DMAC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bportS", .slave=1, .addrLo=0xf8003000ULL, .addrHi=0xf8003fffULL),
                OP_BUS_CONNECT(pBus_b, "bportNS", .slave=1, .addrLo=0xf8004000ULL, .addrHi=0xf8004fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(dmaca_spi45_n, "inta")
            )
        ),
        0
    );

    // PSE swdt

    const char *swdt_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "peripheral",
        "zynq_7000-swdt",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        swdt_path,
        "swdt",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0xf8005000ULL, .addrHi=0xf8005fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(swdt_spi41_n, "wdo")
            )
        ),
        0
    );

    // PSE DDRC

    const char *DDRC_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "peripheral",
        "zynq_7000-ddrc",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        DDRC_path,
        "DDRC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0xf8006000ULL, .addrHi=0xf8006fffULL)
            )
        ),
        0
    );

    // PSE devcfg

    const char *devcfg_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        0,
        "zynq_7000-devcfg",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        devcfg_path,
        "devcfg",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(xadcBus_b, "xadc"),
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0xf8007000ULL, .addrHi=0xf8007fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(xadcmux_n, "xadcmux")
            )
        ),
        OP_PARAMS(
             OP_PARAM_STRING_SET("board", board)
        )
    );

    // PSE dummyAXI_HP0

    const char *dummyAXI_HP0_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        "peripheral",
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        dummyAXI_HP0_path,
        "dummyAXI_HP0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xf8008000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
        )
    );

    // PSE dummyAXI_HP1

    const char *dummyAXI_HP1_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        "peripheral",
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        dummyAXI_HP1_path,
        "dummyAXI_HP1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xf8009000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
        )
    );

    // PSE dummyAXI_HP2

    const char *dummyAXI_HP2_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        "peripheral",
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        dummyAXI_HP2_path,
        "dummyAXI_HP2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xf800a000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
        )
    );

    // PSE dummyAXI_HP3

    const char *dummyAXI_HP3_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        "peripheral",
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        dummyAXI_HP3_path,
        "dummyAXI_HP3",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xf800b000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
        )
    );

    // PSE OCM

    const char *OCM_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "peripheral",
        "zynq_7000-ocm",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        OCM_path,
        "OCM",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0xf800c000ULL, .addrHi=0xf800cfffULL)
            )
        ),
        0
    );

    // PSE dummyeFuse

    const char *dummyeFuse_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        "peripheral",
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        dummyeFuse_path,
        "dummyeFuse",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xf800d000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
        )
    );

    // PSE dummyUnknown2

    const char *dummyUnknown2_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        "peripheral",
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        dummyUnknown2_path,
        "dummyUnknown2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xf800e000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
        )
    );

    // PSE trustzone_GPVsecurity

    const char *trustzone_GPVsecurity_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "peripheral",
        "zynq_7000-tz_GPVsecurity",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        trustzone_GPVsecurity_path,
        "trustzone_GPVsecurity",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0xf8900000ULL, .addrHi=0xf890003fULL)
            )
        ),
        0
    );

    // PSE GPV_qos301_cpu

    const char *GPV_qos301_cpu_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "peripheral",
        "zynq_7000-qos301",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        GPV_qos301_cpu_path,
        "GPV_qos301_cpu",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0xf8946000ULL, .addrHi=0xf8946fffULL)
            )
        ),
        0
    );

    // PSE GPV_qos301_dmac

    const char *GPV_qos301_dmac_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "peripheral",
        "zynq_7000-qos301",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        GPV_qos301_dmac_path,
        "GPV_qos301_dmac",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0xf8947000ULL, .addrHi=0xf8947fffULL)
            )
        ),
        0
    );

    // PSE GPV_qos301_iou

    const char *GPV_qos301_iou_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "peripheral",
        "zynq_7000-qos301",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        GPV_qos301_iou_path,
        "GPV_qos301_iou",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0xf8948000ULL, .addrHi=0xf8948fffULL)
            )
        ),
        0
    );

    // PSE l2cache

    const char *l2cache_path = opVLNVString(
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
        l2cache_path,
        "l2cache",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0xf8f02000ULL, .addrHi=0xf8f02fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(l2cache_spi34_n, "irq")
            )
        ),
        0
    );

}

static optParamSpec paramSpecs[] = {
    {
        .name        = "armmips",
        .type        = OP_PARAM_UNS32,
        .description = 0,
    },
    {
        .name        = "flashtype",
        .type        = OP_PARAM_STRING,
        .description = 0,
        .spec.stringSpec.defaultValue = "micron",
    },
    {
        .name        = "psclock",
        .type        = OP_PARAM_UNS32,
        .description = 0,
    },
    {
        .name        = "board",
        .type        = OP_PARAM_STRING,
        .description = 0,
    },
    { 0 }
};

static OP_PARAM_SPEC_FN(moduleParamIterator) {
    prev = prev ? prev + 1 : paramSpecs; 
    return prev->name ? prev : 0;
}

static optBusPortInfo busPortSpecs[] = {
    {
        .name        = "extPort",
        .description = 0,
    },
    {
        .name        = "extPortI2C",
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
        .name        = "irqf2p0_inP",
        .description = 0,
    },
    {
        .name        = "irqf2p1_inP",
        .description = 0,
    },
    {
        .name        = "irqf2p2_inP",
        .description = 0,
    },
    {
        .name        = "irqf2p3_inP",
        .description = 0,
    },
    {
        .name        = "irqf2p4_inP",
        .description = 0,
    },
    {
        .name        = "irqf2p5_inP",
        .description = 0,
    },
    {
        .name        = "irqf2p6_inP",
        .description = 0,
    },
    {
        .name        = "irqf2p7_inP",
        .description = 0,
    },
    {
        .name        = "irqf2p8_inP",
        .description = 0,
    },
    {
        .name        = "irqf2p9_inP",
        .description = 0,
    },
    {
        .name        = "irqf2p10_inP",
        .description = 0,
    },
    {
        .name        = "irqf2p11_inP",
        .description = 0,
    },
    {
        .name        = "irqf2p12_inP",
        .description = 0,
    },
    {
        .name        = "irqf2p13_inP",
        .description = 0,
    },
    {
        .name        = "irqf2p14_inP",
        .description = 0,
    },
    {
        .name        = "irqf2p15_inP",
        .description = 0,
    },
    {
        .name        = "irqf2p16_inP",
        .description = 0,
    },
    {
        .name        = "irqf2p17_inP",
        .description = 0,
    },
    {
        .name        = "irqf2p18_inP",
        .description = 0,
    },
    {
        .name        = "irqf2p19_inP",
        .description = 0,
    },
    {
        .name        = "irqp2f0_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f1_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f2_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f3_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f4_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f5_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f6_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f7_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f8_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f9_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f10_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f11_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f12_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f13_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f14_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f15_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f16_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f17_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f18_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f19_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f20_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f21_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f22_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f23_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f24_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f25_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f26_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f27_outP",
        .description = 0,
    },
    {
        .name        = "irqp2f28_outP",
        .description = 0,
    },
    {
        .name        = "extPortXADCMux",
        .description = 0,
    },
    {
        .name        = "gpio_bank0_outP",
        .description = 0,
    },
    {
        .name        = "gpio_bank0_inP",
        .description = 0,
    },
    {
        .name        = "gpio_bank1_outP",
        .description = 0,
    },
    {
        .name        = "gpio_bank1_inP",
        .description = 0,
    },
    {
        .name        = "gpio_bank2_outP",
        .description = 0,
    },
    {
        .name        = "gpio_bank2_oen_outP",
        .description = 0,
    },
    {
        .name        = "gpio_bank2_inP",
        .description = 0,
    },
    {
        .name        = "gpio_bank3_outP",
        .description = 0,
    },
    {
        .name        = "gpio_bank3_oen_outP",
        .description = 0,
    },
    {
        .name        = "gpio_bank3_inP",
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
        .vendor  = "xilinx.ovpworld.org",
        .library = "module",
        .name    = "Zynq_PS",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
    .diagSetCB            = moduleDiagSet,
    .paramSpecsCB         = moduleParamIterator,
    .busPortSpecsCB       = moduleBusPortIterator,
    .netPortSpecsCB       = moduleNetPortIterator,
};

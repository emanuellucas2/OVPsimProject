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
    opDocTextAdd(doc_11_node, "\nFreescale Vybrid VFxx platform\n");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "\nOnly enough functionality modeled to boot MQX. Most peripherals modeled as dummy register ports.\n");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "Development based on document number: VYBRIDRM Rev. 5, 07/2013");


    // Bus pBus

    optBusP pBus_b = opBusNew(mi, "pBus", 32, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP SPI93_n = opNetNew(mi, "SPI93", 0, 0);
    optNetP SPI94_n = opNetNew(mi, "SPI94", 0, 0);
    optNetP SPI95_n = opNetNew(mi, "SPI95", 0, 0);
    optNetP SPI96_n = opNetNew(mi, "SPI96", 0, 0);
    optNetP SPI97_n = opNetNew(mi, "SPI97", 0, 0);
    optNetP SPI98_n = opNetNew(mi, "SPI98", 0, 0);
    optNetP dma_eDMARequest0_n = opNetNew(mi, "dma_eDMARequest0", 0, 0);
    optNetP int16_n = opNetNew(mi, "int16", 0, 0);
    optNetP int0_n = opNetNew(mi, "int0", 0, 0);
    optNetP int1_n = opNetNew(mi, "int1", 0, 0);
    optNetP int2_n = opNetNew(mi, "int2", 0, 0);
    optNetP int3_n = opNetNew(mi, "int3", 0, 0);
    optNetP int4_n = opNetNew(mi, "int4", 0, 0);
    optNetP int5_n = opNetNew(mi, "int5", 0, 0);
    optNetP int6_n = opNetNew(mi, "int6", 0, 0);
    optNetP int7_n = opNetNew(mi, "int7", 0, 0);
    optNetP int8_n = opNetNew(mi, "int8", 0, 0);
    optNetP int9_n = opNetNew(mi, "int9", 0, 0);
    optNetP int10_n = opNetNew(mi, "int10", 0, 0);
    optNetP int11_n = opNetNew(mi, "int11", 0, 0);
    optNetP int12_n = opNetNew(mi, "int12", 0, 0);
    optNetP int13_n = opNetNew(mi, "int13", 0, 0);
    optNetP int14_n = opNetNew(mi, "int14", 0, 0);
    optNetP int15_n = opNetNew(mi, "int15", 0, 0);
    optNetP uart0_tx_n = opNetNew(mi, "uart0_tx", "p_uart0_tx", 0);
    optNetP uart0_rx_n = opNetNew(mi, "uart0_rx", "p_uart0_rx", 0);
    optNetP uart2_tx_n = opNetNew(mi, "uart2_tx", "p_uart2_tx", 0);
    optNetP uart2_rx_n = opNetNew(mi, "uart2_rx", "p_uart2_rx", 0);
    optNetP uart3_tx_n = opNetNew(mi, "uart3_tx", "p_uart3_tx", 0);
    optNetP uart3_rx_n = opNetNew(mi, "uart3_rx", "p_uart3_rx", 0);
    optNetP ftm0_phaseA_n = opNetNew(mi, "ftm0_phaseA", 0, 0);
    optNetP ftm0_phaseB_n = opNetNew(mi, "ftm0_phaseB", 0, 0);
    optNetP int62_n = opNetNew(mi, "int62", 0, 0);
    optNetP ftm1_phaseA_n = opNetNew(mi, "ftm1_phaseA", 0, 0);
    optNetP ftm1_phaseB_n = opNetNew(mi, "ftm1_phaseB", 0, 0);
    optNetP int63_n = opNetNew(mi, "int63", 0, 0);
    optNetP dma_eDMARequest1_n = opNetNew(mi, "dma_eDMARequest1", 0, 0);
    optNetP uart4_tx_n = opNetNew(mi, "uart4_tx", "p_uart4_tx", 0);
    optNetP uart4_rx_n = opNetNew(mi, "uart4_rx", "p_uart4_rx", 0);
    optNetP uart5_tx_n = opNetNew(mi, "uart5_tx", "p_uart5_tx", 0);
    optNetP uart5_rx_n = opNetNew(mi, "uart5_rx", "p_uart5_rx", 0);
    optNetP ftm2_phaseA_n = opNetNew(mi, "ftm2_phaseA", 0, 0);
    optNetP ftm2_phaseB_n = opNetNew(mi, "ftm2_phaseB", 0, 0);
    optNetP int64_n = opNetNew(mi, "int64", 0, 0);
    optNetP ftm3_phaseA_n = opNetNew(mi, "ftm3_phaseA", 0, 0);
    optNetP ftm3_phaseB_n = opNetNew(mi, "ftm3_phaseB", 0, 0);
    optNetP int101_n = opNetNew(mi, "int101", 0, 0);
    opNetNew(mi, "uart1_tx", "p_uart1_tx", 0);
    opNetNew(mi, "uart1_rx", "p_uart1_rx", 0);
    opNetNew(mi, "gpio0_out", "p_gpio0_out", 0);
    opNetNew(mi, "gpio0_in", "p_gpio0_in", 0);
    opNetNew(mi, "gpio0_mask", "p_gpio0_mask", 0);
    opNetNew(mi, "gpio1_out", "p_gpio1_out", 0);
    opNetNew(mi, "gpio1_in", "p_gpio1_in", 0);
    opNetNew(mi, "gpio1_mask", "p_gpio1_mask", 0);
    opNetNew(mi, "gpio2_out", "p_gpio2_out", 0);
    opNetNew(mi, "gpio2_in", "p_gpio2_in", 0);
    opNetNew(mi, "gpio2_mask", "p_gpio2_mask", 0);
    opNetNew(mi, "gpio3_out", "p_gpio3_out", 0);
    opNetNew(mi, "gpio3_in", "p_gpio3_in", 0);
    opNetNew(mi, "gpio3_mask", "p_gpio3_mask", 0);
    opNetNew(mi, "gpio4_out", "p_gpio4_out", 0);
    opNetNew(mi, "gpio4_in", "p_gpio4_in", 0);
    opNetNew(mi, "gpio4_mask", "p_gpio4_mask", 0);

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
                OP_NET_CONNECT(SPI93_n, "SPI93"),
                OP_NET_CONNECT(SPI94_n, "SPI94"),
                OP_NET_CONNECT(SPI95_n, "SPI95"),
                OP_NET_CONNECT(SPI96_n, "SPI96"),
                OP_NET_CONNECT(SPI97_n, "SPI97"),
                OP_NET_CONNECT(SPI98_n, "SPI98")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_DOUBLE_SET("mips", 396)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_STRING_SET("variant", "Cortex-A5MPx1")
            ,OP_PARAM_BOOL_SET("UAL", 1)
            ,OP_PARAM_UNS32_SET("override_CBAR", 0x40002000)
            ,OP_PARAM_UNS32_SET("override_GICD_TYPER_ITLines", 4)
            ,OP_PARAM_UNS32_SET("override_timerScaleFactor", 3)
        )
    );


    // Memory bootrom

    opMemoryNew(
        mi,
        "bootrom",
        OP_PRIV_RX,
        (0x17fffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x17fffULL)
            )
        ),
        0
    );

    // Memory sysram

    opMemoryNew(
        mi,
        "sysram",
        OP_PRIV_RWX,
        (0x3f0fffffULL) - (0x3f000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x3f000000ULL, .addrHi=0x3f0fffffULL)
            )
        ),
        0
    );

    // PSE mcsm

    const char *mcsm_path = opVLNVString(
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
        mcsm_path,
        "mcsm",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x40001000)
        )
    );

    // PSE dma0

    const char *dma0_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        0,
        "VybridDMA",
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
                OP_BUS_CONNECT(pBus_b, "MREAD", .addrLo=0x0ULL, .addrHi=0xffffffffULL),
                OP_BUS_CONNECT(pBus_b, "MWRITE", .addrLo=0x0ULL, .addrHi=0xffffffffULL),
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40018000ULL, .addrHi=0x40019fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(dma_eDMARequest0_n, "eDMARequest"),
                OP_NET_CONNECT(int16_n, "errorInterrupt"),
                OP_NET_CONNECT(int0_n, "dmaInterrupt_ch0"),
                OP_NET_CONNECT(int1_n, "dmaInterrupt_ch1"),
                OP_NET_CONNECT(int2_n, "dmaInterrupt_ch2"),
                OP_NET_CONNECT(int3_n, "dmaInterrupt_ch3"),
                OP_NET_CONNECT(int4_n, "dmaInterrupt_ch4"),
                OP_NET_CONNECT(int5_n, "dmaInterrupt_ch5"),
                OP_NET_CONNECT(int6_n, "dmaInterrupt_ch6"),
                OP_NET_CONNECT(int7_n, "dmaInterrupt_ch7"),
                OP_NET_CONNECT(int8_n, "dmaInterrupt_ch8"),
                OP_NET_CONNECT(int9_n, "dmaInterrupt_ch9"),
                OP_NET_CONNECT(int10_n, "dmaInterrupt_ch10"),
                OP_NET_CONNECT(int11_n, "dmaInterrupt_ch11"),
                OP_NET_CONNECT(int12_n, "dmaInterrupt_ch12"),
                OP_NET_CONNECT(int13_n, "dmaInterrupt_ch13"),
                OP_NET_CONNECT(int14_n, "dmaInterrupt_ch14"),
                OP_NET_CONNECT(int15_n, "dmaInterrupt_ch15")
            )
        ),
        0
    );

    // PSE dmamux0

    const char *dmamux0_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisDMAMUX",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        dmamux0_path,
        "dmamux0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40024000ULL, .addrHi=0x40024fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(dma_eDMARequest0_n, "eDMARequest")
            )
        ),
        0
    );

    // PSE dmamux1

    const char *dmamux1_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisDMAMUX",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        dmamux1_path,
        "dmamux1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40025000ULL, .addrHi=0x40025fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(dma_eDMARequest0_n, "eDMARequest")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("startDMAChannel", 16)
        )
    );

    // PSE uart0

    const char *uart0_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridUART",
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40027000ULL, .addrHi=0x40027fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(SPI93_n, "Interrupt"),
                OP_NET_CONNECT(uart0_tx_n, "DirectWrite"),
                OP_NET_CONNECT(uart0_rx_n, "DirectRead")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("fifoSize", 16)
            ,OP_PARAM_UNS32_SET("moduleClkFreq", 66000000)
        )
    );

    // PSE uart1

    const char *uart1_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridUART",
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40028000ULL, .addrHi=0x40028fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(SPI94_n, "Interrupt")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("fifoSize", 16)
            ,OP_PARAM_UNS32_SET("moduleClkFreq", 66000000)
        )
    );

    // PSE uart2

    const char *uart2_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridUART",
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40029000ULL, .addrHi=0x40029fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(SPI95_n, "Interrupt"),
                OP_NET_CONNECT(uart2_tx_n, "DirectWrite"),
                OP_NET_CONNECT(uart2_rx_n, "DirectRead")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("fifoSize", 8)
            ,OP_PARAM_UNS32_SET("moduleClkFreq", 66000000)
        )
    );

    // PSE uart3

    const char *uart3_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridUART",
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4002a000ULL, .addrHi=0x4002afffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(SPI96_n, "Interrupt"),
                OP_NET_CONNECT(uart3_tx_n, "DirectWrite"),
                OP_NET_CONNECT(uart3_rx_n, "DirectRead")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("fifoSize", 8)
            ,OP_PARAM_UNS32_SET("moduleClkFreq", 66000000)
        )
    );

    // PSE spi0

    const char *spi0_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridSPI",
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4002c000ULL, .addrHi=0x4002cfffULL)
            )
        ),
        0
    );

    // PSE spi1

    const char *spi1_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridSPI",
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4002d000ULL, .addrHi=0x4002dfffULL)
            )
        ),
        0
    );

    // PSE usbc0

    const char *usbc0_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridUSB",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        usbc0_path,
        "usbc0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40034000ULL, .addrHi=0x40034fffULL)
            )
        ),
        0
    );

    // PSE ftm0

    const char *ftm0_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        0,
        "KinetisFTM",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ftm0_path,
        "ftm0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40038000ULL, .addrHi=0x40038fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ftm0_phaseA_n, "PhaseA"),
                OP_NET_CONNECT(ftm0_phaseB_n, "PhaseB"),
                OP_NET_CONNECT(int62_n, "Interrupt")
            )
        ),
        0
    );

    // PSE ftm1

    const char *ftm1_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        0,
        "KinetisFTM",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ftm1_path,
        "ftm1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40039000ULL, .addrHi=0x40039fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ftm1_phaseA_n, "PhaseA"),
                OP_NET_CONNECT(ftm1_phaseB_n, "PhaseB"),
                OP_NET_CONNECT(int63_n, "Interrupt")
            )
        ),
        0
    );

    // PSE adc0

    const char *adc0_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridADC",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        adc0_path,
        "adc0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4003b000ULL, .addrHi=0x4003bfffULL)
            )
        ),
        0
    );

    // PSE quadspi0

    const char *quadspi0_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridQUADSPI",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        quadspi0_path,
        "quadspi0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40044000ULL, .addrHi=0x40044fffULL)
            )
        ),
        0
    );

    // PSE iomuxc

    const char *iomuxc_path = opVLNVString(
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
        iomuxc_path,
        "iomuxc",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x40048000)
        )
    );

    // PSE anadig

    const char *anadig_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        0,
        "VybridANADIG",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        anadig_path,
        "anadig",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40050000ULL, .addrHi=0x40050fffULL)
            )
        ),
        0
    );

    // PSE i2c0

    const char *i2c0_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridI2C",
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40066000ULL, .addrHi=0x40066fffULL)
            )
        ),
        0
    );

    // PSE i2c1

    const char *i2c1_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridI2C",
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40067000ULL, .addrHi=0x40067fffULL)
            )
        ),
        0
    );

    // PSE ccm

    const char *ccm_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        0,
        "VybridCCM",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ccm_path,
        "ccm",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4006b000ULL, .addrHi=0x4006bfffULL)
            )
        ),
        0
    );

    // PSE dma1

    const char *dma1_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridDMA",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        dma1_path,
        "dma1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "MREAD", .addrLo=0x0ULL, .addrHi=0xffffffffULL),
                OP_BUS_CONNECT(pBus_b, "MWRITE", .addrLo=0x0ULL, .addrHi=0xffffffffULL),
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40098000ULL, .addrHi=0x40099fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(dma_eDMARequest1_n, "eDMARequest"),
                OP_NET_CONNECT(int16_n, "errorInterrupt"),
                OP_NET_CONNECT(int0_n, "dmaInterrupt_ch0"),
                OP_NET_CONNECT(int1_n, "dmaInterrupt_ch1"),
                OP_NET_CONNECT(int2_n, "dmaInterrupt_ch2"),
                OP_NET_CONNECT(int3_n, "dmaInterrupt_ch3"),
                OP_NET_CONNECT(int4_n, "dmaInterrupt_ch4"),
                OP_NET_CONNECT(int5_n, "dmaInterrupt_ch5"),
                OP_NET_CONNECT(int6_n, "dmaInterrupt_ch6"),
                OP_NET_CONNECT(int7_n, "dmaInterrupt_ch7"),
                OP_NET_CONNECT(int8_n, "dmaInterrupt_ch8"),
                OP_NET_CONNECT(int9_n, "dmaInterrupt_ch9"),
                OP_NET_CONNECT(int10_n, "dmaInterrupt_ch10"),
                OP_NET_CONNECT(int11_n, "dmaInterrupt_ch11"),
                OP_NET_CONNECT(int12_n, "dmaInterrupt_ch12"),
                OP_NET_CONNECT(int13_n, "dmaInterrupt_ch13"),
                OP_NET_CONNECT(int14_n, "dmaInterrupt_ch14"),
                OP_NET_CONNECT(int15_n, "dmaInterrupt_ch15")
            )
        ),
        0
    );

    // PSE dmamux2

    const char *dmamux2_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisDMAMUX",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        dmamux2_path,
        "dmamux2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400a1000ULL, .addrHi=0x400a1fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(dma_eDMARequest1_n, "eDMARequest")
            )
        ),
        0
    );

    // PSE dmamux3

    const char *dmamux3_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisDMAMUX",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        dmamux3_path,
        "dmamux3",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400a2000ULL, .addrHi=0x400a2fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(dma_eDMARequest1_n, "eDMARequest")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("startDMAChannel", 16)
        )
    );

    // PSE uart4

    const char *uart4_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridUART",
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400a9000ULL, .addrHi=0x400a9fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(SPI95_n, "Interrupt"),
                OP_NET_CONNECT(uart4_tx_n, "DirectWrite"),
                OP_NET_CONNECT(uart4_rx_n, "DirectRead")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("fifoSize", 8)
            ,OP_PARAM_UNS32_SET("moduleClkFreq", 66000000)
        )
    );

    // PSE uart5

    const char *uart5_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridUART",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart5_path,
        "uart5",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400aa000ULL, .addrHi=0x400aafffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(SPI96_n, "Interrupt"),
                OP_NET_CONNECT(uart5_tx_n, "DirectWrite"),
                OP_NET_CONNECT(uart5_rx_n, "DirectRead")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("fifoSize", 8)
            ,OP_PARAM_UNS32_SET("moduleClkFreq", 66000000)
        )
    );

    // PSE spi3

    const char *spi3_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridSPI",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        spi3_path,
        "spi3",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400ac000ULL, .addrHi=0x400acfffULL)
            )
        ),
        0
    );

    // PSE spi4

    const char *spi4_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridSPI",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        spi4_path,
        "spi4",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400ad000ULL, .addrHi=0x400adfffULL)
            )
        ),
        0
    );

    // PSE ddrmc

    const char *ddrmc_path = opVLNVString(
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
        ddrmc_path,
        "ddrmc",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x400ae000)
        )
    );

    // PSE sdhc0

    const char *sdhc0_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridSDHC",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        sdhc0_path,
        "sdhc0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400b1000ULL, .addrHi=0x400b1fffULL)
            )
        ),
        0
    );

    // PSE sdhc1

    const char *sdhc1_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridSDHC",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        sdhc1_path,
        "sdhc1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400b2000ULL, .addrHi=0x400b2fffULL)
            )
        ),
        0
    );

    // PSE usbc1

    const char *usbc1_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridUSB",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        usbc1_path,
        "usbc1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400b4000ULL, .addrHi=0x400b4fffULL)
            )
        ),
        0
    );

    // PSE ftm2

    const char *ftm2_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        0,
        "KinetisFTM",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ftm2_path,
        "ftm2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400b8000ULL, .addrHi=0x400b8fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ftm2_phaseA_n, "PhaseA"),
                OP_NET_CONNECT(ftm2_phaseB_n, "PhaseB"),
                OP_NET_CONNECT(int64_n, "Interrupt")
            )
        ),
        0
    );

    // PSE ftm3

    const char *ftm3_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        0,
        "KinetisFTM",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ftm3_path,
        "ftm3",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400b9000ULL, .addrHi=0x400b9fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ftm3_phaseA_n, "PhaseA"),
                OP_NET_CONNECT(ftm3_phaseB_n, "PhaseB"),
                OP_NET_CONNECT(int101_n, "Interrupt")
            )
        ),
        0
    );

    // PSE adc1

    const char *adc1_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridADC",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        adc1_path,
        "adc1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400bb000ULL, .addrHi=0x400bbfffULL)
            )
        ),
        0
    );

    // PSE lcd0

    const char *lcd0_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridLCD",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        lcd0_path,
        "lcd0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400be000ULL, .addrHi=0x400befffULL)
            )
        ),
        0
    );

    // PSE quadspi1

    const char *quadspi1_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridQUADSPI",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        quadspi1_path,
        "quadspi1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400c4000ULL, .addrHi=0x400c4fffULL)
            )
        ),
        0
    );

    // PSE i2c2

    const char *i2c2_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridI2C",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        i2c2_path,
        "i2c2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400e6000ULL, .addrHi=0x400e6fffULL)
            )
        ),
        0
    );

    // PSE i2c3

    const char *i2c3_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridI2C",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        i2c3_path,
        "i2c3",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400e7000ULL, .addrHi=0x400e7fffULL)
            )
        ),
        0
    );

    // PSE gpio0

    const char *gpio0_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridGPIO",
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
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400ff000ULL, .addrHi=0x400ff03fULL)
            )
        ),
        0
    );

    // PSE gpio1

    const char *gpio1_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridGPIO",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        gpio1_path,
        "gpio1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400ff040ULL, .addrHi=0x400ff07fULL)
            )
        ),
        0
    );

    // PSE gpio2

    const char *gpio2_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridGPIO",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        gpio2_path,
        "gpio2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400ff080ULL, .addrHi=0x400ff0bfULL)
            )
        ),
        0
    );

    // PSE gpio3

    const char *gpio3_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridGPIO",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        gpio3_path,
        "gpio3",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400ff0c0ULL, .addrHi=0x400ff0ffULL)
            )
        ),
        0
    );

    // PSE gpio4

    const char *gpio4_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "VybridGPIO",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        gpio4_path,
        "gpio4",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400ff100ULL, .addrHi=0x400ff13fULL)
            )
        ),
        0
    );

}

static optNetPortInfo netPortSpecs[] = {
    {
        .name        = "p_uart0_tx",
        .description = 0,
    },
    {
        .name        = "p_uart0_rx",
        .description = 0,
    },
    {
        .name        = "p_uart1_tx",
        .description = 0,
    },
    {
        .name        = "p_uart1_rx",
        .description = 0,
    },
    {
        .name        = "p_uart2_tx",
        .description = 0,
    },
    {
        .name        = "p_uart2_rx",
        .description = 0,
    },
    {
        .name        = "p_uart3_tx",
        .description = 0,
    },
    {
        .name        = "p_uart3_rx",
        .description = 0,
    },
    {
        .name        = "p_uart4_tx",
        .description = 0,
    },
    {
        .name        = "p_uart4_rx",
        .description = 0,
    },
    {
        .name        = "p_uart5_tx",
        .description = 0,
    },
    {
        .name        = "p_uart5_rx",
        .description = 0,
    },
    {
        .name        = "p_gpio0_out",
        .description = 0,
    },
    {
        .name        = "p_gpio0_in",
        .description = 0,
    },
    {
        .name        = "p_gpio0_mask",
        .description = 0,
    },
    {
        .name        = "p_gpio1_out",
        .description = 0,
    },
    {
        .name        = "p_gpio1_in",
        .description = 0,
    },
    {
        .name        = "p_gpio1_mask",
        .description = 0,
    },
    {
        .name        = "p_gpio2_out",
        .description = 0,
    },
    {
        .name        = "p_gpio2_in",
        .description = 0,
    },
    {
        .name        = "p_gpio2_mask",
        .description = 0,
    },
    {
        .name        = "p_gpio3_out",
        .description = 0,
    },
    {
        .name        = "p_gpio3_in",
        .description = 0,
    },
    {
        .name        = "p_gpio3_mask",
        .description = 0,
    },
    {
        .name        = "p_gpio4_out",
        .description = 0,
    },
    {
        .name        = "p_gpio4_in",
        .description = 0,
    },
    {
        .name        = "p_gpio4_mask",
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
    .purpose              = OP_PP_BAREMETAL,
    .visibility           = OP_VISIBLE,
    .vlnv          = {
        .vendor  = "freescale.ovpworld.org",
        .library = "platform",
        .name    = "FreescaleVybridVFxx",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
    .netPortSpecsCB       = moduleNetPortIterator,
};

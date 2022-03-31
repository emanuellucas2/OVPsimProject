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
    opDocTextAdd(doc_11_node, "Andes AE350 module (skeleton)");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_21_node, "Andes BSP v5.0 ae350 BSP Definition");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_31_node, "This is a skeleton platform that contains only those peripherals required to boot FreeRTOS demo.");
    opDocTextAdd(doc_31_node, "The following peripherals are register only models that do not provide any behavior:");
    opDocTextAdd(doc_31_node, "  - BMC");
    opDocTextAdd(doc_31_node, "  - AHBDEC");
    opDocTextAdd(doc_31_node, "  - MAC");
    opDocTextAdd(doc_31_node, "  - LCDC");
    opDocTextAdd(doc_31_node, "  - SMC");
    opDocTextAdd(doc_31_node, "  - PLIC_SW");
    opDocTextAdd(doc_31_node, "  - PLDM");
    opDocTextAdd(doc_31_node, "  - APBBRG");
    opDocTextAdd(doc_31_node, "  - SMU");
    opDocTextAdd(doc_31_node, "  - PIT");
    opDocTextAdd(doc_31_node, "  - WDT");
    opDocTextAdd(doc_31_node, "  - RTC");
    opDocTextAdd(doc_31_node, "  - GPIO");
    opDocTextAdd(doc_31_node, "  - I2C");
    opDocTextAdd(doc_31_node, "  - SPI1");
    opDocTextAdd(doc_31_node, "  - DMAC");
    opDocTextAdd(doc_31_node, "  - AC97");
    opDocTextAdd(doc_31_node, "  - SDC");
    opDocTextAdd(doc_31_node, "  - SPI2");
    opDocTextAdd(doc_31_node, "The UART does not support dma mode, so if using the Andes AMSI BSP you should set RTE_UART*_DMA_*X_EN=0 in RTE_Device.h");
    // Variables indicating when parameters are set
    Bool buswidth_isSet           = 0;

    // Variables holding parameter values
    UNUSED Uns32        buswidth                 = opObjectParamUns32Value(mi, "buswidth", &buswidth_isSet);


    // Bus bus0

    optBusP bus0_b = opBusNew(mi, "bus0", buswidth, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP MExternalInterrupt_n = opNetNew(mi, "MExternalInterrupt", 0, 0);
    optNetP MExternalInterruptID_n = opNetNew(mi, "MExternalInterruptID", 0, 0);
    optNetP MExternalInterruptACK_n = opNetNew(mi, "MExternalInterruptACK", 0, 0);
    optNetP mtip_n = opNetNew(mi, "mtip", 0, 0);
    optNetP uart1Irq_n = opNetNew(mi, "uart1Irq", 0, 0);
    optNetP uart2Irq_n = opNetNew(mi, "uart2Irq", 0, 0);

    // Processor cpu0

    const char *cpu0_path = opVLNVString(
        0, // use the default VLNV path
        "andes.ovpworld.org",
        "processor",
        "riscv",
        "1.0",
        OP_PROCESSOR,
        OP_VLNV_PRINT
    );

    opProcessorNew(
        mi,
        cpu0_path,
        "cpu0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "INSTRUCTION"),
                OP_BUS_CONNECT(bus0_b, "DATA")
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(MExternalInterrupt_n, "MExternalInterrupt"),
                OP_NET_CONNECT(MExternalInterruptID_n, "MExternalInterruptID"),
                OP_NET_CONNECT(MExternalInterruptACK_n, "MExternalInterruptACK"),
                OP_NET_CONNECT(mtip_n, "MTimerInterrupt")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_DOUBLE_SET("mips", 60)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_ENUM_SET("variant", "NX25")
        )
    );


    // Memory eilm

    opMemoryNew(
        mi,
        "eilm",
        OP_PRIV_RWX,
        (0x1fffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x1fffffULL)
            )
        ),
        0
    );

    // Memory edlm

    opMemoryNew(
        mi,
        "edlm",
        OP_PRIV_RWX,
        (0x2fffffULL) - (0x200000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x200000ULL, .addrHi=0x2fffffULL)
            )
        ),
        0
    );

    // Memory spimem

    opMemoryNew(
        mi,
        "spimem",
        OP_PRIV_RWX,
        (0x801fffffULL) - (0x80000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x80000000ULL, .addrHi=0x801fffffULL)
            )
        ),
        0
    );

    // Memory stack

    opMemoryNew(
        mi,
        "stack",
        OP_PRIV_RWX,
        (0x7ffffffULL) - (0x7ff0000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x7ff0000ULL, .addrHi=0x7ffffffULL)
            )
        ),
        0
    );

    // PSE BMC

    const char *BMC_path = opVLNVString(
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
        BMC_path,
        "BMC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xC0000000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
            ,OP_PARAM_BOOL_SET("cbEnable", 1)
        )
    );

    // PSE AHBDEC

    const char *AHBDEC_path = opVLNVString(
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
        AHBDEC_path,
        "AHBDEC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xE0000000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
            ,OP_PARAM_BOOL_SET("cbEnable", 1)
        )
    );

    // PSE MAC

    const char *MAC_path = opVLNVString(
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
        MAC_path,
        "MAC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xE0100000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
            ,OP_PARAM_BOOL_SET("cbEnable", 1)
        )
    );

    // PSE LCDC

    const char *LCDC_path = opVLNVString(
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
        LCDC_path,
        "LCDC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xE0200000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
            ,OP_PARAM_BOOL_SET("cbEnable", 1)
        )
    );

    // PSE SMC

    const char *SMC_path = opVLNVString(
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
        SMC_path,
        "SMC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xE0400000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
            ,OP_PARAM_BOOL_SET("cbEnable", 1)
        )
    );

    // PSE PLIC

    const char *PLIC_path = opVLNVString(
        0, // use the default VLNV path
        "andes.ovpworld.org",
        "peripheral",
        "NCEPLIC100",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        PLIC_path,
        "PLIC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "port0", .slave=1, .addrLo=0xe4000000ULL, .addrHi=0xe43fffffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(MExternalInterrupt_n, "irqT0"),
                OP_NET_CONNECT(MExternalInterruptID_n, "t0_eiid"),
                OP_NET_CONNECT(MExternalInterruptACK_n, "t0_eiack"),
                OP_NET_CONNECT(uart1Irq_n, "irqS8"),
                OP_NET_CONNECT(uart2Irq_n, "irqS9")
            )
        ),
        0
    );

    // PSE PLMT

    const char *PLMT_path = opVLNVString(
        0, // use the default VLNV path
        "andes.ovpworld.org",
        "peripheral",
        "NCEPLMT100",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        PLMT_path,
        "PLMT",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .addrLo=0xe6000000ULL, .addrHi=0xe60000ffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(mtip_n, "intOut_0")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("numharts", 1)
            ,OP_PARAM_DOUBLE_SET("clockMHz", 60)
        )
    );

    // PSE PLIC_SW

    const char *PLIC_SW_path = opVLNVString(
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
        PLIC_SW_path,
        "PLIC_SW",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xE6400000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
            ,OP_PARAM_BOOL_SET("cbEnable", 1)
        )
    );

    // PSE PLDM

    const char *PLDM_path = opVLNVString(
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
        PLDM_path,
        "PLDM",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xE6800000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
            ,OP_PARAM_BOOL_SET("cbEnable", 1)
        )
    );

    // PSE APBBRG

    const char *APBBRG_path = opVLNVString(
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
        APBBRG_path,
        "APBBRG",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xF0000000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
            ,OP_PARAM_BOOL_SET("cbEnable", 1)
        )
    );

    // PSE SMU

    const char *SMU_path = opVLNVString(
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
        SMU_path,
        "SMU",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xF0100000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
            ,OP_PARAM_BOOL_SET("cbEnable", 1)
        )
    );

    // PSE UART1

    const char *UART1_path = opVLNVString(
        0, // use the default VLNV path
        "andes.ovpworld.org",
        "peripheral",
        "ATCUART100",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        UART1_path,
        "UART1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .addrLo=0xf0200000ULL, .addrHi=0xf020003fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(uart1Irq_n, "intOut")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("console", 1)
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
        )
    );

    // PSE UART2

    const char *UART2_path = opVLNVString(
        0, // use the default VLNV path
        "andes.ovpworld.org",
        "peripheral",
        "ATCUART100",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        UART2_path,
        "UART2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .addrLo=0xf0300000ULL, .addrHi=0xf030003fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(uart2Irq_n, "intOut")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("console", 1)
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
        )
    );

    // PSE PIT

    const char *PIT_path = opVLNVString(
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
        PIT_path,
        "PIT",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xF0400000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
            ,OP_PARAM_BOOL_SET("cbEnable", 1)
        )
    );

    // PSE WDT

    const char *WDT_path = opVLNVString(
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
        WDT_path,
        "WDT",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xF0500000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
            ,OP_PARAM_BOOL_SET("cbEnable", 1)
        )
    );

    // PSE RTC

    const char *RTC_path = opVLNVString(
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
        RTC_path,
        "RTC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xF0600000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
            ,OP_PARAM_BOOL_SET("cbEnable", 1)
        )
    );

    // PSE GPIO

    const char *GPIO_path = opVLNVString(
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
        GPIO_path,
        "GPIO",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xF0700000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
            ,OP_PARAM_BOOL_SET("cbEnable", 1)
        )
    );

    // PSE I2C

    const char *I2C_path = opVLNVString(
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
        I2C_path,
        "I2C",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xF0A00000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
            ,OP_PARAM_BOOL_SET("cbEnable", 1)
        )
    );

    // PSE SPI1

    const char *SPI1_path = opVLNVString(
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
        SPI1_path,
        "SPI1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xF0B00000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
            ,OP_PARAM_BOOL_SET("cbEnable", 1)
        )
    );

    // PSE DMAC

    const char *DMAC_path = opVLNVString(
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
        DMAC_path,
        "DMAC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xF0C00000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
            ,OP_PARAM_BOOL_SET("cbEnable", 1)
        )
    );

    // PSE AC97

    const char *AC97_path = opVLNVString(
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
        AC97_path,
        "AC97",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xF0D00000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
            ,OP_PARAM_BOOL_SET("cbEnable", 1)
        )
    );

    // PSE SDC

    const char *SDC_path = opVLNVString(
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
        SDC_path,
        "SDC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xF0E00000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
            ,OP_PARAM_BOOL_SET("cbEnable", 1)
        )
    );

    // PSE SPI2

    const char *SPI2_path = opVLNVString(
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
        SPI2_path,
        "SPI2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0xF0F00000)
            ,OP_PARAM_UNS32_SET("portSize", 0x1000)
            ,OP_PARAM_BOOL_SET("cbEnable", 1)
        )
    );

}

static optParamSpec paramSpecs[] = {
    {
        .name        = "buswidth",
        .type        = OP_PARAM_UNS32,
        .description = 0,
        .spec.uns32Spec.defaultValue = 37,
    },
    { 0 }
};

static OP_PARAM_SPEC_FN(moduleParamIterator) {
    prev = prev ? prev + 1 : paramSpecs; 
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
        .vendor  = "andes.ovpworld.org",
        .library = "module",
        .name    = "AE350",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
    .paramSpecsCB         = moduleParamIterator,
};

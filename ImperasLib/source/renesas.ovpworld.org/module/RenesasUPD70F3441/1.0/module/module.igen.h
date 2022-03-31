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
    opDocTextAdd(doc_11_node, "The Renesas uPD70F3441 - V850/PHO3 platform");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "Limitiations of peripheral functionality is documented within the peripheral component.\nUnimplemented Components:\n    System Controller\n    Standby Controller\n    Bus Control Unit\n    Memory Controller\n    CAN Controller\n    FlexRay\n    I/O Ports\n    CPU-CRC\n    DATA-CRC\n    On-chip Debug Unit\n    NBD\nPartially Implemented Components (not complete - only certain modes or features modeled or tested)\n    DMA\n");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010");


    // Bus vfb

    optBusP vfb_b = opBusNew(mi, "vfb", 28, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP INTRESET_n = opNetNew(mi, "INTRESET", 0, 0);
    optNetP INTNMI_n = opNetNew(mi, "INTNMI", 0, 0);
    optNetP INTINTP_n = opNetNew(mi, "INTINTP", 0, 0);
    optNetP INTMIRETI_n = opNetNew(mi, "INTMIRETI", 0, 0);
    optNetP INTINTACK_n = opNetNew(mi, "INTINTACK", 0, 0);
    optNetP INTNMI0_n = opNetNew(mi, "INTNMI0", 0, 0);
    optNetP INTINT0_n = opNetNew(mi, "INTINT0", 0, 0);
    optNetP INTINT1_n = opNetNew(mi, "INTINT1", 0, 0);
    optNetP INTUC0R_n = opNetNew(mi, "INTUC0R", 0, 0);
    optNetP INTINT6_n = opNetNew(mi, "INTINT6", 0, 0);
    optNetP INTUC1R_n = opNetNew(mi, "INTUC1R", 0, 0);
    optNetP INTINT7_n = opNetNew(mi, "INTINT7", 0, 0);
    optNetP INTBRG0_n = opNetNew(mi, "INTBRG0", 0, 0);
    optNetP INTBRG1_n = opNetNew(mi, "INTBRG1", 0, 0);
    optNetP INTINT75_n = opNetNew(mi, "INTINT75", 0, 0);
    optNetP INTCB0T_n = opNetNew(mi, "INTCB0T", 0, 0);
    optNetP INTUC2T_n = opNetNew(mi, "INTUC2T", 0, 0);
    optNetP INTINT99_n = opNetNew(mi, "INTINT99", 0, 0);
    optNetP INTCB0R_n = opNetNew(mi, "INTCB0R", 0, 0);
    optNetP INTUC2R_n = opNetNew(mi, "INTUC2R", 0, 0);
    optNetP INTINT100_n = opNetNew(mi, "INTINT100", 0, 0);
    optNetP INTCB0RE_n = opNetNew(mi, "INTCB0RE", 0, 0);
    optNetP INTUC2RE_n = opNetNew(mi, "INTUC2RE", 0, 0);
    optNetP INTINT101_n = opNetNew(mi, "INTINT101", 0, 0);
    optNetP INTINT116_n = opNetNew(mi, "INTINT116", 0, 0);
    optNetP INTTS0OV_n = opNetNew(mi, "INTTS0OV", 0, 0);
    optNetP INTTS0CC0_n = opNetNew(mi, "INTTS0CC0", 0, 0);
    optNetP INTTS0CC1_n = opNetNew(mi, "INTTS0CC1", 0, 0);
    optNetP INTTS0CC2_n = opNetNew(mi, "INTTS0CC2", 0, 0);
    optNetP INTTS0CC3_n = opNetNew(mi, "INTTS0CC3", 0, 0);
    optNetP INTTS0CC4_n = opNetNew(mi, "INTTS0CC4", 0, 0);
    optNetP INTTS0CC5_n = opNetNew(mi, "INTTS0CC5", 0, 0);
    optNetP INTTS0CD0_n = opNetNew(mi, "INTTS0CD0", 0, 0);
    optNetP INTTS0OD_n = opNetNew(mi, "INTTS0OD", 0, 0);
    optNetP INTTS0ER_n = opNetNew(mi, "INTTS0ER", 0, 0);
    optNetP INTTS0WN_n = opNetNew(mi, "INTTS0WN", 0, 0);
    optNetP INTTS1OV_n = opNetNew(mi, "INTTS1OV", 0, 0);
    optNetP INTTS1CC0_n = opNetNew(mi, "INTTS1CC0", 0, 0);
    optNetP INTTS1CC1_n = opNetNew(mi, "INTTS1CC1", 0, 0);
    optNetP INTTS1CC2_n = opNetNew(mi, "INTTS1CC2", 0, 0);
    optNetP INTTS1CC3_n = opNetNew(mi, "INTTS1CC3", 0, 0);
    optNetP INTTS1CC4_n = opNetNew(mi, "INTTS1CC4", 0, 0);
    optNetP INTTS1CC5_n = opNetNew(mi, "INTTS1CC5", 0, 0);
    optNetP INTTS1CD0_n = opNetNew(mi, "INTTS1CD0", 0, 0);
    optNetP INTTS1OD_n = opNetNew(mi, "INTTS1OD", 0, 0);
    optNetP INTTS1ER_n = opNetNew(mi, "INTTS1ER", 0, 0);
    optNetP INTTS1WN_n = opNetNew(mi, "INTTS1WN", 0, 0);
    optNetP INTTT0OV_n = opNetNew(mi, "INTTT0OV", 0, 0);
    optNetP INTTT0CC0_n = opNetNew(mi, "INTTT0CC0", 0, 0);
    optNetP INTTT0CC1_n = opNetNew(mi, "INTTT0CC1", 0, 0);
    optNetP INTTT0EC_n = opNetNew(mi, "INTTT0EC", 0, 0);
    optNetP INTTT1OV_n = opNetNew(mi, "INTTT1OV", 0, 0);
    optNetP INTTT1CC0_n = opNetNew(mi, "INTTT1CC0", 0, 0);
    optNetP INTTT1CC1_n = opNetNew(mi, "INTTT1CC1", 0, 0);
    optNetP INTTT1EC_n = opNetNew(mi, "INTTT1EC", 0, 0);
    optNetP INTTAA0OV_n = opNetNew(mi, "INTTAA0OV", 0, 0);
    optNetP INTTAA0CC0_n = opNetNew(mi, "INTTAA0CC0", 0, 0);
    optNetP INTTAA0CC1_n = opNetNew(mi, "INTTAA0CC1", 0, 0);
    optNetP INTTAA1OV_n = opNetNew(mi, "INTTAA1OV", 0, 0);
    optNetP INTTAA1CC0_n = opNetNew(mi, "INTTAA1CC0", 0, 0);
    optNetP INTTAA1CC1_n = opNetNew(mi, "INTTAA1CC1", 0, 0);
    optNetP INTTAA2OV_n = opNetNew(mi, "INTTAA2OV", 0, 0);
    optNetP INTTAA2CC0_n = opNetNew(mi, "INTTAA2CC0", 0, 0);
    optNetP INTTAA2CC1_n = opNetNew(mi, "INTTAA2CC1", 0, 0);
    optNetP INTTAA3OV_n = opNetNew(mi, "INTTAA3OV", 0, 0);
    optNetP INTTAA3CC0_n = opNetNew(mi, "INTTAA3CC0", 0, 0);
    optNetP INTTAA3CC1_n = opNetNew(mi, "INTTAA3CC1", 0, 0);
    optNetP INTTAA4OV_n = opNetNew(mi, "INTTAA4OV", 0, 0);
    optNetP INTTAA4CC0_n = opNetNew(mi, "INTTAA4CC0", 0, 0);
    optNetP INTTAA4CC1_n = opNetNew(mi, "INTTAA4CC1", 0, 0);
    optNetP INTTAA5OV_n = opNetNew(mi, "INTTAA5OV", 0, 0);
    optNetP INTTAA5CC0_n = opNetNew(mi, "INTTAA5CC0", 0, 0);
    optNetP INTTAA5CC1_n = opNetNew(mi, "INTTAA5CC1", 0, 0);
    optNetP INTTAA6OV_n = opNetNew(mi, "INTTAA6OV", 0, 0);
    optNetP INTTAA6CC0_n = opNetNew(mi, "INTTAA6CC0", 0, 0);
    optNetP INTTAA6CC1_n = opNetNew(mi, "INTTAA6CC1", 0, 0);
    optNetP INTTAA7OV_n = opNetNew(mi, "INTTAA7OV", 0, 0);
    optNetP INTTAA7CC0_n = opNetNew(mi, "INTTAA7CC0", 0, 0);
    optNetP INTTAA7CC1_n = opNetNew(mi, "INTTAA7CC1", 0, 0);
    optNetP INTTAA8OV_n = opNetNew(mi, "INTTAA8OV", 0, 0);
    optNetP INTTAA8CC0_n = opNetNew(mi, "INTTAA8CC0", 0, 0);
    optNetP INTTAA8CC1_n = opNetNew(mi, "INTTAA8CC1", 0, 0);
    optNetP INTTAA9OV_n = opNetNew(mi, "INTTAA9OV", 0, 0);
    optNetP INTTAA9CC0_n = opNetNew(mi, "INTTAA9CC0", 0, 0);
    optNetP INTTAA9CC1_n = opNetNew(mi, "INTTAA9CC1", 0, 0);
    optNetP INTBRG2_n = opNetNew(mi, "INTBRG2", 0, 0);
    optNetP INTC0ERR_n = opNetNew(mi, "INTC0ERR", 0, 0);
    optNetP INTC0WUPIC_n = opNetNew(mi, "INTC0WUPIC", 0, 0);
    optNetP INTC0REC_n = opNetNew(mi, "INTC0REC", 0, 0);
    optNetP INTC0TRX_n = opNetNew(mi, "INTC0TRX", 0, 0);
    optNetP INTC1ERR_n = opNetNew(mi, "INTC1ERR", 0, 0);
    optNetP INTC1WUPIC_n = opNetNew(mi, "INTC1WUPIC", 0, 0);
    optNetP INTC1REC_n = opNetNew(mi, "INTC1REC", 0, 0);
    optNetP INTC1TRX_n = opNetNew(mi, "INTC1TRX", 0, 0);
    optNetP INTCB1T_n = opNetNew(mi, "INTCB1T", 0, 0);
    optNetP INTCB1R_n = opNetNew(mi, "INTCB1R", 0, 0);
    optNetP INTCB1RE_n = opNetNew(mi, "INTCB1RE", 0, 0);
    optNetP INTUC0RE_n = opNetNew(mi, "INTUC0RE", 0, 0);
    optNetP INTUC0T_n = opNetNew(mi, "INTUC0T", 0, 0);
    optNetP INTUC1RE_n = opNetNew(mi, "INTUC1RE", 0, 0);
    optNetP INTUC1T_n = opNetNew(mi, "INTUC1T", 0, 0);
    optNetP INTAD0_n = opNetNew(mi, "INTAD0", 0, 0);
    optNetP INTAD1_n = opNetNew(mi, "INTAD1", 0, 0);
    optNetP DMA0EN_n = opNetNew(mi, "DMA0EN", 0, 0);
    optNetP DMA1EN_n = opNetNew(mi, "DMA1EN", 0, 0);
    optNetP ADDMARQ0_n = opNetNew(mi, "ADDMARQ0", 0, 0);
    optNetP ADDMARQ1_n = opNetNew(mi, "ADDMARQ1", 0, 0);
    optNetP TS0ADTRG0_n = opNetNew(mi, "TS0ADTRG0", 0, 0);
    optNetP TS0ADTRG1_n = opNetNew(mi, "TS0ADTRG1", 0, 0);
    optNetP TS1ADTRG0_n = opNetNew(mi, "TS1ADTRG0", 0, 0);
    optNetP TS1ADTRG1_n = opNetNew(mi, "TS1ADTRG1", 0, 0);

    optPacketnetP vcan0_pkn = opPacketnetNew(mi, "vcan0", 0, 0);

    opPacketnetNew(mi, "vcan1", 0, 0);

    // Processor CPU

    const char *CPU_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "processor",
        "v850",
        0,
        OP_PROCESSOR,
        OP_VLNV_PRINT
    );

    opProcessorNew(
        mi,
        CPU_path,
        "CPU",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "INSTRUCTION"),
                OP_BUS_CONNECT(vfb_b, "DATA")
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTRESET_n, "reset"),
                OP_NET_CONNECT(INTNMI_n, "nmi0"),
                OP_NET_CONNECT(INTINTP_n, "intp"),
                OP_NET_CONNECT(INTMIRETI_n, "mireti"),
                OP_NET_CONNECT(INTINTACK_n, "intack")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("enableimperasintercepts", 1)
            ,OP_PARAM_DOUBLE_SET("mips", 128)
            ,OP_PARAM_ENUM_SET("variant", "V850ES")
        )
    );


    // Memory CodeFlash

    opMemoryNew(
        mi,
        "CodeFlash",
        OP_PRIV_RWX,
        (0xf7fffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0xf7fffULL)
            )
        ),
        0
    );

    // Memory DataFlash

    opMemoryNew(
        mi,
        "DataFlash",
        OP_PRIV_RWX,
        (0x3e07fffULL) - (0x3e00000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "sp1", .slave=1, .addrLo=0x3e00000ULL, .addrHi=0x3e07fffULL)
            )
        ),
        0
    );

    // Memory iRam

    opMemoryNew(
        mi,
        "iRam",
        OP_PRIV_RWX,
        (0x3ffefffULL) - (0x3ff0000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "sp1", .slave=1, .addrLo=0x3ff0000ULL, .addrHi=0x3ffefffULL)
            )
        ),
        0
    );

    // Bridge bridge_vfb_0x03FF0000_0x0FFF0000

    opBridgeNew(
        mi,
        "bridge_vfb_0x03FF0000_0x0FFF0000",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "mp", .addrLo=0x3ff0000ULL, .addrHi=0x3ffefffULL),
                OP_BUS_CONNECT(vfb_b, "sp", .slave=1, .addrLo=0xfff0000ULL, .addrHi=0xfffefffULL)
            )
        ),
        0
    );

    // Bridge bridge_vfb_0x0FFFF58A_0x0FFFFB48

    opBridgeNew(
        mi,
        "bridge_vfb_0x0FFFF58A_0x0FFFFB48",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "mp", .addrLo=0xffff58aULL, .addrHi=0xffff593ULL),
                OP_BUS_CONNECT(vfb_b, "sp", .slave=1, .addrLo=0xffffb48ULL, .addrHi=0xffffb51ULL)
            )
        ),
        0
    );

    // Bridge bridge_vfb_0x0FFFF598_0x0FFFFB56

    opBridgeNew(
        mi,
        "bridge_vfb_0x0FFFF598_0x0FFFFB56",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "mp", .addrLo=0xffff598ULL, .addrHi=0xffff59fULL),
                OP_BUS_CONNECT(vfb_b, "sp", .slave=1, .addrLo=0xffffb56ULL, .addrHi=0xffffb5dULL)
            )
        ),
        0
    );

    // Bridge bridge_vfb_0x0FFFF5CA_0x0FFFFBC8

    opBridgeNew(
        mi,
        "bridge_vfb_0x0FFFF5CA_0x0FFFFBC8",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "mp", .addrLo=0xffff5caULL, .addrHi=0xffff5d3ULL),
                OP_BUS_CONNECT(vfb_b, "sp", .slave=1, .addrLo=0xffffbc8ULL, .addrHi=0xffffbd1ULL)
            )
        ),
        0
    );

    // Bridge bridge_vfb_0x0FFFF5D8_0x0FFFFBD6

    opBridgeNew(
        mi,
        "bridge_vfb_0x0FFFF5D8_0x0FFFFBD6",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "mp", .addrLo=0xffff5d8ULL, .addrHi=0xffff5dfULL),
                OP_BUS_CONNECT(vfb_b, "sp", .slave=1, .addrLo=0xffffbd6ULL, .addrHi=0xffffbddULL)
            )
        ),
        0
    );

    // PSE LOGIC

    const char *LOGIC_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "UPD70F3441Logic",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        LOGIC_path,
        "LOGIC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "LOGICP0", .slave=1, .addrLo=0xffff6d0ULL, .addrHi=0xffff6d3ULL),
                OP_BUS_CONNECT(vfb_b, "LOGICP1", .slave=1, .addrLo=0xffff400ULL, .addrHi=0xffff475ULL),
                OP_BUS_CONNECT(vfb_b, "LOGICP2", .slave=1, .addrLo=0xffff888ULL, .addrHi=0xffff893ULL),
                OP_BUS_CONNECT(vfb_b, "LOGICP3", .slave=1, .addrLo=0xffff1fcULL, .addrHi=0xffff1fcULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTNMI0_n, "NMIOUT"),
                OP_NET_CONNECT(INTINT0_n, "INT0"),
                OP_NET_CONNECT(INTINT1_n, "INT1"),
                OP_NET_CONNECT(INTUC0R_n, "INTUC0R"),
                OP_NET_CONNECT(INTINT6_n, "INT6"),
                OP_NET_CONNECT(INTUC1R_n, "INTUC1R"),
                OP_NET_CONNECT(INTINT7_n, "INT7"),
                OP_NET_CONNECT(INTBRG0_n, "INTBRG0"),
                OP_NET_CONNECT(INTBRG1_n, "INTBRG1"),
                OP_NET_CONNECT(INTINT75_n, "INT75"),
                OP_NET_CONNECT(INTCB0T_n, "INTCB0T"),
                OP_NET_CONNECT(INTUC2T_n, "INTUC2T"),
                OP_NET_CONNECT(INTINT99_n, "INT99"),
                OP_NET_CONNECT(INTCB0R_n, "INTCB0R"),
                OP_NET_CONNECT(INTUC2R_n, "INTUC2R"),
                OP_NET_CONNECT(INTINT100_n, "INT100"),
                OP_NET_CONNECT(INTCB0RE_n, "INTCB0RE"),
                OP_NET_CONNECT(INTUC2RE_n, "INTUC2RE"),
                OP_NET_CONNECT(INTINT101_n, "INT101"),
                OP_NET_CONNECT(INTINT116_n, "INT116")
            )
        ),
        0
    );

    // PSE INTC

    const char *INTC_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "intc",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        INTC_path,
        "INTC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "INTCP0", .slave=1, .addrLo=0xffff100ULL, .addrHi=0xffff1fbULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTRESET_n, "RESET"),
                OP_NET_CONNECT(INTNMI_n, "NMI0"),
                OP_NET_CONNECT(INTINTP_n, "INTP"),
                OP_NET_CONNECT(INTMIRETI_n, "MIRETI"),
                OP_NET_CONNECT(INTINTACK_n, "INTACK"),
                OP_NET_CONNECT(INTNMI0_n, "NMI_00"),
                OP_NET_CONNECT(INTINT0_n, "INT_00"),
                OP_NET_CONNECT(INTINT1_n, "INT_01"),
                OP_NET_CONNECT(INTINT6_n, "INT_06"),
                OP_NET_CONNECT(INTINT7_n, "INT_07"),
                OP_NET_CONNECT(INTTS0OV_n, "INT_15"),
                OP_NET_CONNECT(INTTS0CC0_n, "INT_16"),
                OP_NET_CONNECT(INTTS0CC1_n, "INT_17"),
                OP_NET_CONNECT(INTTS0CC2_n, "INT_18"),
                OP_NET_CONNECT(INTTS0CC3_n, "INT_19"),
                OP_NET_CONNECT(INTTS0CC4_n, "INT_20"),
                OP_NET_CONNECT(INTTS0CC5_n, "INT_21"),
                OP_NET_CONNECT(INTTS0CD0_n, "INT_22"),
                OP_NET_CONNECT(INTTS0OD_n, "INT_23"),
                OP_NET_CONNECT(INTTS0ER_n, "INT_24"),
                OP_NET_CONNECT(INTTS0WN_n, "INT_25"),
                OP_NET_CONNECT(INTTS1OV_n, "INT_26"),
                OP_NET_CONNECT(INTTS1CC0_n, "INT_27"),
                OP_NET_CONNECT(INTTS1CC1_n, "INT_28"),
                OP_NET_CONNECT(INTTS1CC2_n, "INT_29"),
                OP_NET_CONNECT(INTTS1CC3_n, "INT_30"),
                OP_NET_CONNECT(INTTS1CC4_n, "INT_31"),
                OP_NET_CONNECT(INTTS1CC5_n, "INT_32"),
                OP_NET_CONNECT(INTTS1CD0_n, "INT_33"),
                OP_NET_CONNECT(INTTS1OD_n, "INT_34"),
                OP_NET_CONNECT(INTTS1ER_n, "INT_35"),
                OP_NET_CONNECT(INTTS1WN_n, "INT_36"),
                OP_NET_CONNECT(INTTT0OV_n, "INT_37"),
                OP_NET_CONNECT(INTTT0CC0_n, "INT_38"),
                OP_NET_CONNECT(INTTT0CC1_n, "INT_39"),
                OP_NET_CONNECT(INTTT0EC_n, "INT_40"),
                OP_NET_CONNECT(INTTT1OV_n, "INT_41"),
                OP_NET_CONNECT(INTTT1CC0_n, "INT_42"),
                OP_NET_CONNECT(INTTT1CC1_n, "INT_43"),
                OP_NET_CONNECT(INTTT1EC_n, "INT_44"),
                OP_NET_CONNECT(INTTAA0OV_n, "INT_45"),
                OP_NET_CONNECT(INTTAA0CC0_n, "INT_46"),
                OP_NET_CONNECT(INTTAA0CC1_n, "INT_47"),
                OP_NET_CONNECT(INTTAA1OV_n, "INT_48"),
                OP_NET_CONNECT(INTTAA1CC0_n, "INT_49"),
                OP_NET_CONNECT(INTTAA1CC1_n, "INT_50"),
                OP_NET_CONNECT(INTTAA2OV_n, "INT_51"),
                OP_NET_CONNECT(INTTAA2CC0_n, "INT_52"),
                OP_NET_CONNECT(INTTAA2CC1_n, "INT_53"),
                OP_NET_CONNECT(INTTAA3OV_n, "INT_54"),
                OP_NET_CONNECT(INTTAA3CC0_n, "INT_55"),
                OP_NET_CONNECT(INTTAA3CC1_n, "INT_56"),
                OP_NET_CONNECT(INTTAA4OV_n, "INT_57"),
                OP_NET_CONNECT(INTTAA4CC0_n, "INT_58"),
                OP_NET_CONNECT(INTTAA4CC1_n, "INT_59"),
                OP_NET_CONNECT(INTTAA5OV_n, "INT_60"),
                OP_NET_CONNECT(INTTAA5CC0_n, "INT_61"),
                OP_NET_CONNECT(INTTAA5CC1_n, "INT_62"),
                OP_NET_CONNECT(INTTAA6OV_n, "INT_63"),
                OP_NET_CONNECT(INTTAA6CC0_n, "INT_64"),
                OP_NET_CONNECT(INTTAA6CC1_n, "INT_65"),
                OP_NET_CONNECT(INTTAA7OV_n, "INT_66"),
                OP_NET_CONNECT(INTTAA7CC0_n, "INT_67"),
                OP_NET_CONNECT(INTTAA7CC1_n, "INT_68"),
                OP_NET_CONNECT(INTTAA8OV_n, "INT_69"),
                OP_NET_CONNECT(INTTAA8CC0_n, "INT_70"),
                OP_NET_CONNECT(INTTAA8CC1_n, "INT_71"),
                OP_NET_CONNECT(INTTAA9OV_n, "INT_72"),
                OP_NET_CONNECT(INTTAA9CC0_n, "INT_73"),
                OP_NET_CONNECT(INTTAA9CC1_n, "INT_74"),
                OP_NET_CONNECT(INTINT75_n, "INT_75"),
                OP_NET_CONNECT(INTBRG2_n, "INT_76"),
                OP_NET_CONNECT(INTC0ERR_n, "INT_83"),
                OP_NET_CONNECT(INTC0WUPIC_n, "INT_84"),
                OP_NET_CONNECT(INTC0REC_n, "INT_85"),
                OP_NET_CONNECT(INTC0TRX_n, "INT_86"),
                OP_NET_CONNECT(INTC1ERR_n, "INT_87"),
                OP_NET_CONNECT(INTC1WUPIC_n, "INT_88"),
                OP_NET_CONNECT(INTC1REC_n, "INT_89"),
                OP_NET_CONNECT(INTC1TRX_n, "INT_90"),
                OP_NET_CONNECT(INTINT99_n, "INT_99"),
                OP_NET_CONNECT(INTINT100_n, "INT_100"),
                OP_NET_CONNECT(INTINT101_n, "INT_101"),
                OP_NET_CONNECT(INTCB1T_n, "INT_102"),
                OP_NET_CONNECT(INTCB1R_n, "INT_103"),
                OP_NET_CONNECT(INTCB1RE_n, "INT_104"),
                OP_NET_CONNECT(INTUC0RE_n, "INT_109"),
                OP_NET_CONNECT(INTUC0T_n, "INT_110"),
                OP_NET_CONNECT(INTUC1RE_n, "INT_111"),
                OP_NET_CONNECT(INTUC1T_n, "INT_112"),
                OP_NET_CONNECT(INTAD0_n, "INT_113"),
                OP_NET_CONNECT(INTAD1_n, "INT_114"),
                OP_NET_CONNECT(INTINT116_n, "INT_116")
            )
        ),
        0
    );

    // PSE CRC

    const char *CRC_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "crc",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        CRC_path,
        "CRC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "CRCP0", .slave=1, .addrLo=0xfe00000ULL, .addrHi=0xfe0007fULL)
            )
        ),
        0
    );

    // PSE CLKGEN

    const char *CLKGEN_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "clkgen",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        CLKGEN_path,
        "CLKGEN",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "CLKGENP0", .slave=1, .addrLo=0xffff860ULL, .addrHi=0xffff860ULL),
                OP_BUS_CONNECT(vfb_b, "CLKGENP1", .slave=1, .addrLo=0xffffca0ULL, .addrHi=0xffffca0ULL)
            )
        ),
        0
    );

    // PSE BCU

    const char *BCU_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "bcu",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        BCU_path,
        "BCU",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "BCUP0", .slave=1, .addrLo=0xffff060ULL, .addrHi=0xffff06fULL)
            )
        ),
        0
    );

    // PSE MEMC

    const char *MEMC_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "memc",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        MEMC_path,
        "MEMC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "MEMCP0", .slave=1, .addrLo=0xffff480ULL, .addrHi=0xffff48fULL)
            )
        ),
        0
    );

    // PSE DMA

    const char *DMA_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "dma",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        DMA_path,
        "DMA",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "DMAPM"),
                OP_BUS_CONNECT(vfb_b, "DMAP0", .slave=1, .addrLo=0xffffe00ULL, .addrHi=0xffffe0fULL),
                OP_BUS_CONNECT(vfb_b, "DMAP1", .slave=1, .addrLo=0xffff300ULL, .addrHi=0xffff3ffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTAD0_n, "INTDMA0"),
                OP_NET_CONNECT(INTAD1_n, "INTDMA1"),
                OP_NET_CONNECT(DMA0EN_n, "DMA0EN"),
                OP_NET_CONNECT(DMA1EN_n, "DMA1EN"),
                OP_NET_CONNECT(ADDMARQ0_n, "ADDMARQ0"),
                OP_NET_CONNECT(ADDMARQ1_n, "ADDMARQ1"),
                OP_NET_CONNECT(INTUC0R_n, "INTUC0R"),
                OP_NET_CONNECT(INTUC1R_n, "INTUC1R"),
                OP_NET_CONNECT(INTUC2R_n, "INTUC2R")
            )
        ),
        0
    );

    // PSE UARTC0

    const char *UARTC0_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "uartc",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        UARTC0_path,
        "UARTC0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "UARTP0", .slave=1, .addrLo=0xffffa00ULL, .addrHi=0xffffa0fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTUC0T_n, "INTUCT"),
                OP_NET_CONNECT(INTUC0R_n, "INTUCR"),
                OP_NET_CONNECT(INTUC0RE_n, "INTUCRE")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK0", 33554432)
            ,OP_PARAM_UNS32_SET("PCLK1", 16777216)
            ,OP_PARAM_UNS32_SET("PCLK2", 8388608)
            ,OP_PARAM_UNS32_SET("PCLK3", 4194304)
            ,OP_PARAM_UNS32_SET("PCLK4", 2097152)
            ,OP_PARAM_UNS32_SET("PCLK5", 1048576)
            ,OP_PARAM_UNS32_SET("PCLK7", 262144)
            ,OP_PARAM_UNS32_SET("PCLK9", 65536)
            ,OP_PARAM_BOOL_SET("console", 1)
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
        )
    );

    // PSE UARTC1

    const char *UARTC1_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "uartc",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        UARTC1_path,
        "UARTC1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "UARTP0", .slave=1, .addrLo=0xffffa20ULL, .addrHi=0xffffa2fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTUC1T_n, "INTUCT"),
                OP_NET_CONNECT(INTUC1R_n, "INTUCR"),
                OP_NET_CONNECT(INTUC1RE_n, "INTUCRE")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK0", 33554432)
            ,OP_PARAM_UNS32_SET("PCLK1", 16777216)
            ,OP_PARAM_UNS32_SET("PCLK2", 8388608)
            ,OP_PARAM_UNS32_SET("PCLK3", 4194304)
            ,OP_PARAM_UNS32_SET("PCLK4", 2097152)
            ,OP_PARAM_UNS32_SET("PCLK5", 1048576)
            ,OP_PARAM_UNS32_SET("PCLK7", 262144)
            ,OP_PARAM_UNS32_SET("PCLK9", 65536)
            ,OP_PARAM_BOOL_SET("console", 1)
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
        )
    );

    // PSE UARTC2

    const char *UARTC2_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "uartc",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        UARTC2_path,
        "UARTC2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "UARTP0", .slave=1, .addrLo=0xffffa40ULL, .addrHi=0xffffa4fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTUC2T_n, "INTUCT"),
                OP_NET_CONNECT(INTUC2R_n, "INTUCR"),
                OP_NET_CONNECT(INTUC2RE_n, "INTUCRE")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK0", 33554432)
            ,OP_PARAM_UNS32_SET("PCLK1", 16777216)
            ,OP_PARAM_UNS32_SET("PCLK2", 8388608)
            ,OP_PARAM_UNS32_SET("PCLK3", 4194304)
            ,OP_PARAM_UNS32_SET("PCLK4", 2097152)
            ,OP_PARAM_UNS32_SET("PCLK5", 1048576)
            ,OP_PARAM_UNS32_SET("PCLK7", 262144)
            ,OP_PARAM_UNS32_SET("PCLK9", 65536)
            ,OP_PARAM_BOOL_SET("console", 1)
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
        )
    );

    // PSE CSIB0

    const char *CSIB0_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "csib",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        CSIB0_path,
        "CSIB0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "CSIBP0", .slave=1, .addrLo=0xffffd00ULL, .addrHi=0xffffd07ULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTCB0T_n, "INTCBT"),
                OP_NET_CONNECT(INTCB0R_n, "INTCBR"),
                OP_NET_CONNECT(INTCB0RE_n, "INTCBRE")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK1", 16777216)
            ,OP_PARAM_UNS32_SET("PCLK2", 8388608)
            ,OP_PARAM_UNS32_SET("PCLK3", 4194304)
            ,OP_PARAM_UNS32_SET("PCLK4", 2097152)
            ,OP_PARAM_UNS32_SET("PCLK5", 1048576)
            ,OP_PARAM_UNS32_SET("PCLK6", 524288)
        )
    );

    // PSE CSIB1

    const char *CSIB1_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "csib",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        CSIB1_path,
        "CSIB1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "CSIBP0", .slave=1, .addrLo=0xffffd20ULL, .addrHi=0xffffd27ULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTCB1T_n, "INTCBT"),
                OP_NET_CONNECT(INTCB1R_n, "INTCBR"),
                OP_NET_CONNECT(INTCB1RE_n, "INTCBRE")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK1", 16777216)
            ,OP_PARAM_UNS32_SET("PCLK2", 8388608)
            ,OP_PARAM_UNS32_SET("PCLK3", 4194304)
            ,OP_PARAM_UNS32_SET("PCLK4", 2097152)
            ,OP_PARAM_UNS32_SET("PCLK5", 1048576)
            ,OP_PARAM_UNS32_SET("PCLK6", 524288)
        )
    );

    // PSE CSIE0

    const char *CSIE0_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "csie",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        CSIE0_path,
        "CSIE0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "CSIEP0", .slave=1, .addrLo=0xffffd40ULL, .addrHi=0xffffd5fULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK0", 33554432)
        )
    );

    // PSE CSIE1

    const char *CSIE1_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "csie",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        CSIE1_path,
        "CSIE1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "CSIEP0", .slave=1, .addrLo=0xffffd80ULL, .addrHi=0xffffd9fULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK0", 33554432)
        )
    );

    // PSE CAN0

    const char *CAN0_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "can",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        CAN0_path,
        "CAN0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "busPortGR", .slave=1, .addrLo=0x8400000ULL, .addrHi=0x84000ffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTC0ERR_n, "INTERR"),
                OP_NET_CONNECT(INTC0REC_n, "INTREC"),
                OP_NET_CONNECT(INTC0TRX_n, "INTTRX"),
                OP_NET_CONNECT(INTC0WUPIC_n, "INTWUP")
            ),
            OP_PACKETNET_CONNECTIONS(
                OP_PACKETNET_CONNECT(vcan0_pkn, "CAN")
            )
        ),
        0
    );

    // PSE CAN1

    const char *CAN1_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "can",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        CAN1_path,
        "CAN1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "busPortGR", .slave=1, .addrLo=0x8400600ULL, .addrHi=0x84006ffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTC0ERR_n, "INTERR"),
                OP_NET_CONNECT(INTC0REC_n, "INTREC"),
                OP_NET_CONNECT(INTC0TRX_n, "INTTRX"),
                OP_NET_CONNECT(INTC0WUPIC_n, "INTWUP")
            ),
            OP_PACKETNET_CONNECTIONS(
                OP_PACKETNET_CONNECT(vcan0_pkn, "CAN")
            )
        ),
        0
    );

    // PSE ADC0

    const char *ADC0_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "adc",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ADC0_path,
        "ADC0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "ADCP0", .slave=1, .addrLo=0xffff200ULL, .addrHi=0xffff22fULL),
                OP_BUS_CONNECT(vfb_b, "ADCP1", .slave=1, .addrLo=0xffff270ULL, .addrHi=0xffff270ULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(TS0ADTRG0_n, "TS0ADT0"),
                OP_NET_CONNECT(TS0ADTRG1_n, "TS0ADT1"),
                OP_NET_CONNECT(TS1ADTRG0_n, "TS1ADT0"),
                OP_NET_CONNECT(TS1ADTRG1_n, "TS1ADT1"),
                OP_NET_CONNECT(INTTS0OD_n, "INTTS0OD"),
                OP_NET_CONNECT(INTTS0CD0_n, "INTTS0CD"),
                OP_NET_CONNECT(INTTS1OD_n, "INTTS1OD"),
                OP_NET_CONNECT(INTTS1CD0_n, "INTTS1CD"),
                OP_NET_CONNECT(INTAD0_n, "INTAD"),
                OP_NET_CONNECT(ADDMARQ0_n, "ADDMARQ"),
                OP_NET_CONNECT(DMA0EN_n, "INTADEN")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK1", 16777216)
            ,OP_PARAM_DOUBLE_SET("sample", 100)
        )
    );

    // PSE ADC1

    const char *ADC1_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "adc",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ADC1_path,
        "ADC1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "ADCP0", .slave=1, .addrLo=0xffff240ULL, .addrHi=0xffff26fULL),
                OP_BUS_CONNECT(vfb_b, "ADCP1", .slave=1, .addrLo=0xffff272ULL, .addrHi=0xffff272ULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(TS0ADTRG0_n, "TS0ADT0"),
                OP_NET_CONNECT(TS0ADTRG1_n, "TS0ADT1"),
                OP_NET_CONNECT(TS1ADTRG0_n, "TS1ADT0"),
                OP_NET_CONNECT(TS1ADTRG1_n, "TS1ADT1"),
                OP_NET_CONNECT(INTTS0OD_n, "INTTS0OD"),
                OP_NET_CONNECT(INTTS0CD0_n, "INTTS0CD"),
                OP_NET_CONNECT(INTTS1OD_n, "INTTS1OD"),
                OP_NET_CONNECT(INTTS1CD0_n, "INTTS1CD"),
                OP_NET_CONNECT(INTAD1_n, "INTAD"),
                OP_NET_CONNECT(ADDMARQ1_n, "ADDMARQ"),
                OP_NET_CONNECT(DMA1EN_n, "INTADEN")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK1", 16777216)
            ,OP_PARAM_DOUBLE_SET("sample", 100)
        )
    );

    // PSE TAA0

    const char *TAA0_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "taa",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        TAA0_path,
        "TAA0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "TAAP0", .slave=1, .addrLo=0xffff600ULL, .addrHi=0xffff60fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTTAA0OV_n, "INTTAAOV"),
                OP_NET_CONNECT(INTTAA0CC0_n, "INTTAACC0"),
                OP_NET_CONNECT(INTTAA0CC1_n, "INTTAACC1")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK0", 33554432)
            ,OP_PARAM_UNS32_SET("PCLK1", 16777216)
            ,OP_PARAM_UNS32_SET("PCLK2", 8388608)
            ,OP_PARAM_UNS32_SET("PCLK3", 4194304)
            ,OP_PARAM_UNS32_SET("PCLK4", 2097152)
            ,OP_PARAM_UNS32_SET("PCLK5", 1048576)
            ,OP_PARAM_UNS32_SET("PCLK7", 262144)
            ,OP_PARAM_UNS32_SET("PCLK9", 65536)
        )
    );

    // PSE TAA1

    const char *TAA1_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "taa",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        TAA1_path,
        "TAA1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "TAAP0", .slave=1, .addrLo=0xffff610ULL, .addrHi=0xffff61fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTTAA1OV_n, "INTTAAOV"),
                OP_NET_CONNECT(INTTAA1CC0_n, "INTTAACC0"),
                OP_NET_CONNECT(INTTAA1CC1_n, "INTTAACC1")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK0", 33554432)
            ,OP_PARAM_UNS32_SET("PCLK1", 16777216)
            ,OP_PARAM_UNS32_SET("PCLK2", 8388608)
            ,OP_PARAM_UNS32_SET("PCLK3", 4194304)
            ,OP_PARAM_UNS32_SET("PCLK4", 2097152)
            ,OP_PARAM_UNS32_SET("PCLK5", 1048576)
            ,OP_PARAM_UNS32_SET("PCLK7", 262144)
            ,OP_PARAM_UNS32_SET("PCLK9", 65536)
        )
    );

    // PSE TAA2

    const char *TAA2_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "taa",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        TAA2_path,
        "TAA2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "TAAP0", .slave=1, .addrLo=0xffff620ULL, .addrHi=0xffff62fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTTAA2OV_n, "INTTAAOV"),
                OP_NET_CONNECT(INTTAA2CC0_n, "INTTAACC0"),
                OP_NET_CONNECT(INTTAA2CC1_n, "INTTAACC1")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK0", 33554432)
            ,OP_PARAM_UNS32_SET("PCLK1", 16777216)
            ,OP_PARAM_UNS32_SET("PCLK2", 8388608)
            ,OP_PARAM_UNS32_SET("PCLK3", 4194304)
            ,OP_PARAM_UNS32_SET("PCLK4", 2097152)
            ,OP_PARAM_UNS32_SET("PCLK5", 1048576)
            ,OP_PARAM_UNS32_SET("PCLK7", 262144)
            ,OP_PARAM_UNS32_SET("PCLK9", 65536)
        )
    );

    // PSE TAA3

    const char *TAA3_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "taa",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        TAA3_path,
        "TAA3",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "TAAP0", .slave=1, .addrLo=0xffff630ULL, .addrHi=0xffff63fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTTAA3OV_n, "INTTAAOV"),
                OP_NET_CONNECT(INTTAA3CC0_n, "INTTAACC0"),
                OP_NET_CONNECT(INTTAA3CC1_n, "INTTAACC1")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK0", 33554432)
            ,OP_PARAM_UNS32_SET("PCLK1", 16777216)
            ,OP_PARAM_UNS32_SET("PCLK2", 8388608)
            ,OP_PARAM_UNS32_SET("PCLK3", 4194304)
            ,OP_PARAM_UNS32_SET("PCLK4", 2097152)
            ,OP_PARAM_UNS32_SET("PCLK5", 1048576)
            ,OP_PARAM_UNS32_SET("PCLK7", 262144)
            ,OP_PARAM_UNS32_SET("PCLK9", 65536)
        )
    );

    // PSE TAA4

    const char *TAA4_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "taa",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        TAA4_path,
        "TAA4",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "TAAP0", .slave=1, .addrLo=0xffff640ULL, .addrHi=0xffff64fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTTAA4OV_n, "INTTAAOV"),
                OP_NET_CONNECT(INTTAA4CC0_n, "INTTAACC0"),
                OP_NET_CONNECT(INTTAA4CC1_n, "INTTAACC1")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK0", 33554432)
            ,OP_PARAM_UNS32_SET("PCLK1", 16777216)
            ,OP_PARAM_UNS32_SET("PCLK2", 8388608)
            ,OP_PARAM_UNS32_SET("PCLK3", 4194304)
            ,OP_PARAM_UNS32_SET("PCLK4", 2097152)
            ,OP_PARAM_UNS32_SET("PCLK5", 1048576)
            ,OP_PARAM_UNS32_SET("PCLK7", 262144)
            ,OP_PARAM_UNS32_SET("PCLK9", 65536)
        )
    );

    // PSE TAA5

    const char *TAA5_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "taa",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        TAA5_path,
        "TAA5",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "TAAP0", .slave=1, .addrLo=0xffff650ULL, .addrHi=0xffff65fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTTAA5OV_n, "INTTAAOV"),
                OP_NET_CONNECT(INTTAA5CC0_n, "INTTAACC0"),
                OP_NET_CONNECT(INTTAA5CC1_n, "INTTAACC1")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK0", 33554432)
            ,OP_PARAM_UNS32_SET("PCLK1", 16777216)
            ,OP_PARAM_UNS32_SET("PCLK2", 8388608)
            ,OP_PARAM_UNS32_SET("PCLK3", 4194304)
            ,OP_PARAM_UNS32_SET("PCLK4", 2097152)
            ,OP_PARAM_UNS32_SET("PCLK5", 1048576)
            ,OP_PARAM_UNS32_SET("PCLK7", 262144)
            ,OP_PARAM_UNS32_SET("PCLK9", 65536)
        )
    );

    // PSE TAA6

    const char *TAA6_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "taa",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        TAA6_path,
        "TAA6",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "TAAP0", .slave=1, .addrLo=0xffff660ULL, .addrHi=0xffff66fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTTAA6OV_n, "INTTAAOV"),
                OP_NET_CONNECT(INTTAA6CC0_n, "INTTAACC0"),
                OP_NET_CONNECT(INTTAA6CC1_n, "INTTAACC1")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK0", 33554432)
            ,OP_PARAM_UNS32_SET("PCLK1", 16777216)
            ,OP_PARAM_UNS32_SET("PCLK2", 8388608)
            ,OP_PARAM_UNS32_SET("PCLK3", 4194304)
            ,OP_PARAM_UNS32_SET("PCLK4", 2097152)
            ,OP_PARAM_UNS32_SET("PCLK5", 1048576)
            ,OP_PARAM_UNS32_SET("PCLK7", 262144)
            ,OP_PARAM_UNS32_SET("PCLK9", 65536)
        )
    );

    // PSE TAA7

    const char *TAA7_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "taa",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        TAA7_path,
        "TAA7",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "TAAP0", .slave=1, .addrLo=0xffff670ULL, .addrHi=0xffff67fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTTAA7OV_n, "INTTAAOV"),
                OP_NET_CONNECT(INTTAA7CC0_n, "INTTAACC0"),
                OP_NET_CONNECT(INTTAA7CC1_n, "INTTAACC1")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK0", 33554432)
            ,OP_PARAM_UNS32_SET("PCLK1", 16777216)
            ,OP_PARAM_UNS32_SET("PCLK2", 8388608)
            ,OP_PARAM_UNS32_SET("PCLK3", 4194304)
            ,OP_PARAM_UNS32_SET("PCLK4", 2097152)
            ,OP_PARAM_UNS32_SET("PCLK5", 1048576)
            ,OP_PARAM_UNS32_SET("PCLK7", 262144)
            ,OP_PARAM_UNS32_SET("PCLK9", 65536)
        )
    );

    // PSE TAA8

    const char *TAA8_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "taa",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        TAA8_path,
        "TAA8",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "TAAP0", .slave=1, .addrLo=0xffff680ULL, .addrHi=0xffff68fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTTAA8OV_n, "INTTAAOV"),
                OP_NET_CONNECT(INTTAA8CC0_n, "INTTAACC0"),
                OP_NET_CONNECT(INTTAA8CC1_n, "INTTAACC1")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK0", 33554432)
            ,OP_PARAM_UNS32_SET("PCLK1", 16777216)
            ,OP_PARAM_UNS32_SET("PCLK2", 8388608)
            ,OP_PARAM_UNS32_SET("PCLK3", 4194304)
            ,OP_PARAM_UNS32_SET("PCLK4", 2097152)
            ,OP_PARAM_UNS32_SET("PCLK5", 1048576)
            ,OP_PARAM_UNS32_SET("PCLK7", 262144)
            ,OP_PARAM_UNS32_SET("PCLK9", 65536)
        )
    );

    // PSE TAA9

    const char *TAA9_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "taa",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        TAA9_path,
        "TAA9",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "TAAP0", .slave=1, .addrLo=0xffff6b0ULL, .addrHi=0xffff6bfULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTTAA9OV_n, "INTTAAOV"),
                OP_NET_CONNECT(INTTAA9CC0_n, "INTTAACC0"),
                OP_NET_CONNECT(INTTAA9CC1_n, "INTTAACC1")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK0", 33554432)
            ,OP_PARAM_UNS32_SET("PCLK1", 16777216)
            ,OP_PARAM_UNS32_SET("PCLK2", 8388608)
            ,OP_PARAM_UNS32_SET("PCLK3", 4194304)
            ,OP_PARAM_UNS32_SET("PCLK4", 2097152)
            ,OP_PARAM_UNS32_SET("PCLK5", 1048576)
            ,OP_PARAM_UNS32_SET("PCLK7", 262144)
            ,OP_PARAM_UNS32_SET("PCLK9", 65536)
        )
    );

    // PSE TMS0

    const char *TMS0_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "tms",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        TMS0_path,
        "TMS0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "TMSP0", .slave=1, .addrLo=0xffff580ULL, .addrHi=0xffff5a9ULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTTS0OV_n, "INTTSOV"),
                OP_NET_CONNECT(INTTS0CC0_n, "INTTSCC0"),
                OP_NET_CONNECT(INTTS0CC1_n, "INTTSCC1"),
                OP_NET_CONNECT(INTTS0CC2_n, "INTTSCC2"),
                OP_NET_CONNECT(INTTS0CC3_n, "INTTSCC3"),
                OP_NET_CONNECT(INTTS0CC4_n, "INTTSCC4"),
                OP_NET_CONNECT(INTTS0CC5_n, "INTTSCC5"),
                OP_NET_CONNECT(INTTS0CD0_n, "INTTSCD0"),
                OP_NET_CONNECT(INTTS0OD_n, "INTTSOD"),
                OP_NET_CONNECT(INTTS0ER_n, "INTTSER"),
                OP_NET_CONNECT(INTTS0WN_n, "INTTSWN"),
                OP_NET_CONNECT(TS0ADTRG0_n, "TSADTRG0"),
                OP_NET_CONNECT(TS0ADTRG1_n, "TSADTRG1")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK0", 33554432)
            ,OP_PARAM_UNS32_SET("PCLK1", 16777216)
            ,OP_PARAM_UNS32_SET("PCLK2", 8388608)
            ,OP_PARAM_UNS32_SET("PCLK3", 4194304)
            ,OP_PARAM_UNS32_SET("PCLK4", 2097152)
            ,OP_PARAM_UNS32_SET("PCLK5", 1048576)
            ,OP_PARAM_UNS32_SET("PCLK7", 262144)
            ,OP_PARAM_UNS32_SET("PCLK9", 65536)
        )
    );

    // PSE TMS1

    const char *TMS1_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "tms",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        TMS1_path,
        "TMS1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "TMSP0", .slave=1, .addrLo=0xffff5c0ULL, .addrHi=0xffff5e9ULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTTS1OV_n, "INTTSOV"),
                OP_NET_CONNECT(INTTS1CC0_n, "INTTSCC0"),
                OP_NET_CONNECT(INTTS1CC1_n, "INTTSCC1"),
                OP_NET_CONNECT(INTTS1CC2_n, "INTTSCC2"),
                OP_NET_CONNECT(INTTS1CC3_n, "INTTSCC3"),
                OP_NET_CONNECT(INTTS1CC4_n, "INTTSCC4"),
                OP_NET_CONNECT(INTTS1CC5_n, "INTTSCC5"),
                OP_NET_CONNECT(INTTS1CD0_n, "INTTSCD0"),
                OP_NET_CONNECT(INTTS1OD_n, "INTTSOD"),
                OP_NET_CONNECT(INTTS1ER_n, "INTTSER"),
                OP_NET_CONNECT(INTTS1WN_n, "INTTSWN"),
                OP_NET_CONNECT(TS1ADTRG0_n, "TSADTRG0"),
                OP_NET_CONNECT(TS1ADTRG1_n, "TSADTRG1")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK0", 33554432)
            ,OP_PARAM_UNS32_SET("PCLK1", 16777216)
            ,OP_PARAM_UNS32_SET("PCLK2", 8388608)
            ,OP_PARAM_UNS32_SET("PCLK3", 4194304)
            ,OP_PARAM_UNS32_SET("PCLK4", 2097152)
            ,OP_PARAM_UNS32_SET("PCLK5", 1048576)
            ,OP_PARAM_UNS32_SET("PCLK7", 262144)
            ,OP_PARAM_UNS32_SET("PCLK9", 65536)
        )
    );

    // PSE TMT0

    const char *TMT0_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "tmt",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        TMT0_path,
        "TMT0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "TMTP0", .slave=1, .addrLo=0xffff690ULL, .addrHi=0xffff69fULL),
                OP_BUS_CONNECT(vfb_b, "TMTP1", .slave=1, .addrLo=0xffff990ULL, .addrHi=0xffff991ULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTTT0OV_n, "INTTTOV"),
                OP_NET_CONNECT(INTTT0CC0_n, "INTTTCC0"),
                OP_NET_CONNECT(INTTT0CC1_n, "INTTTCC1"),
                OP_NET_CONNECT(INTTT0EC_n, "INTTTEC")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK0", 33554432)
            ,OP_PARAM_UNS32_SET("PCLK1", 16777216)
            ,OP_PARAM_UNS32_SET("PCLK2", 8388608)
            ,OP_PARAM_UNS32_SET("PCLK3", 4194304)
            ,OP_PARAM_UNS32_SET("PCLK4", 2097152)
            ,OP_PARAM_UNS32_SET("PCLK5", 1048576)
            ,OP_PARAM_UNS32_SET("PCLK7", 262144)
            ,OP_PARAM_UNS32_SET("PCLK9", 65536)
        )
    );

    // PSE TMT1

    const char *TMT1_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "tmt",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        TMT1_path,
        "TMT1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "TMTP0", .slave=1, .addrLo=0xffff6a0ULL, .addrHi=0xffff6afULL),
                OP_BUS_CONNECT(vfb_b, "TMTP1", .slave=1, .addrLo=0xffff9a0ULL, .addrHi=0xffff9a1ULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTTT1OV_n, "INTTTOV"),
                OP_NET_CONNECT(INTTT1CC0_n, "INTTTCC0"),
                OP_NET_CONNECT(INTTT1CC1_n, "INTTTCC1"),
                OP_NET_CONNECT(INTTT1EC_n, "INTTTEC")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK0", 33554432)
            ,OP_PARAM_UNS32_SET("PCLK1", 16777216)
            ,OP_PARAM_UNS32_SET("PCLK2", 8388608)
            ,OP_PARAM_UNS32_SET("PCLK3", 4194304)
            ,OP_PARAM_UNS32_SET("PCLK4", 2097152)
            ,OP_PARAM_UNS32_SET("PCLK5", 1048576)
            ,OP_PARAM_UNS32_SET("PCLK7", 262144)
            ,OP_PARAM_UNS32_SET("PCLK9", 65536)
        )
    );

    // PSE RNG0

    const char *RNG0_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "rng",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        RNG0_path,
        "RNG0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "RNGP0", .slave=1, .addrLo=0xffff700ULL, .addrHi=0xffff701ULL)
            )
        ),
        0
    );

    // PSE BRG0

    const char *BRG0_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "brg",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        BRG0_path,
        "BRG0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "BRGP0", .slave=1, .addrLo=0xffffdc0ULL, .addrHi=0xffffdc1ULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTBRG0_n, "INTBRG")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK", 16777216)
        )
    );

    // PSE BRG1

    const char *BRG1_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "brg",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        BRG1_path,
        "BRG1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "BRGP0", .slave=1, .addrLo=0xffffdd0ULL, .addrHi=0xffffdd1ULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTBRG1_n, "INTBRG")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK", 16777216)
        )
    );

    // PSE BRG2

    const char *BRG2_path = opVLNVString(
        0, // use the default VLNV path
        "renesas.ovpworld.org",
        "peripheral",
        "brg",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        BRG2_path,
        "BRG2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(vfb_b, "BRGP0", .slave=1, .addrLo=0xffffde0ULL, .addrHi=0xffffde1ULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(INTBRG2_n, "INTBRG")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCLK", 33554432)
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
        .vendor  = "renesas.ovpworld.org",
        .library = "module",
        .name    = "RenesasUPD70F3441",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

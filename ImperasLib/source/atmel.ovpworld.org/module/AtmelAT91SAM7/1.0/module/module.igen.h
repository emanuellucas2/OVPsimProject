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

    optDocNodeP doc1_node = opModuleDocSectionAdd(mi, "Description");
    opDocTextAdd(doc1_node, " Simple platform of Atmel AT91 ARM7TDMI based system\n");
    optDocNodeP doc_11_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_11_node, "This platform is sufficient to boot Linux");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_21_node, "Rev. 1354D ARM08/02");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Licensing");
    opDocTextAdd(doc_31_node, "Open Source Apache 2.0");


    // Bus mainbus

    optBusP mainbus_b = opBusNew(mi, "mainbus", 32, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP NFIQ_n = opNetNew(mi, "NFIQ", 0, 0);
    optNetP NIRQ_n = opNetNew(mi, "NIRQ", 0, 0);
    optNetP US0IRQ_n = opNetNew(mi, "US0IRQ", 0, 0);
    optNetP US1IRQ_n = opNetNew(mi, "US1IRQ", 0, 0);
    optNetP TC0IRQ_n = opNetNew(mi, "TC0IRQ", 0, 0);
    optNetP TC1IRQ_n = opNetNew(mi, "TC1IRQ", 0, 0);
    optNetP TC2IRQ_n = opNetNew(mi, "TC2IRQ", 0, 0);
    optNetP WDIRQ_n = opNetNew(mi, "WDIRQ", 0, 0);
    optNetP PIOIRQ_n = opNetNew(mi, "PIOIRQ", 0, 0);

    // Processor ARM7TDMICore

    const char *ARM7TDMICore_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "arm",
        0,
        OP_PROCESSOR,
        OP_VLNV_PRINT
    );

    optProcessorP ARM7TDMICore_c = opProcessorNew(
        mi,
        ARM7TDMICore_path,
        "ARM7TDMICore",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(mainbus_b, "INSTRUCTION"),
                OP_BUS_CONNECT(mainbus_b, "DATA")
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(NFIQ_n, "fiq"),
                OP_NET_CONNECT(NIRQ_n, "irq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_ENUM_SET("variant", "ARM7TDMI")
        )
    );

    const char *loader_0_expath = opVLNVString(
        0, // use the default VLNV path
        "atmel.ovpworld.org",
        "intercept",
        "loader",
        0,
        OP_EXTENSION,
        OP_VLNV_PRINT
    );

    opProcessorExtensionNew(
        ARM7TDMICore_c,
        loader_0_expath,
        "loader_0_ex",
        0
    );

    // Memory extDev

    opMemoryNew(
        mi,
        "extDev",
        OP_PRIV_RWX,
        (0xffbfffffULL) - (0x400000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(mainbus_b, "sp1", .slave=1, .addrLo=0x400000ULL, .addrHi=0xffbfffffULL)
            )
        ),
        0
    );

    // Memory ram0

    opMemoryNew(
        mi,
        "ram0",
        OP_PRIV_RWX,
        (0xfffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(mainbus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0xfffffULL)
            )
        ),
        0
    );

    // PSE AIC

    const char *AIC_path = opVLNVString(
        0, // use the default VLNV path
        "atmel.ovpworld.org",
        0,
        "AdvancedInterruptController",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        AIC_path,
        "AIC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(mainbus_b, "bp1", .slave=1, .addrLo=0xfffff000ULL, .addrHi=0xffffffffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(US0IRQ_n, "US0IRQ"),
                OP_NET_CONNECT(US1IRQ_n, "US1IRQ"),
                OP_NET_CONNECT(TC0IRQ_n, "TC0IRQ"),
                OP_NET_CONNECT(TC1IRQ_n, "TC1IRQ"),
                OP_NET_CONNECT(TC2IRQ_n, "TC2IRQ"),
                OP_NET_CONNECT(WDIRQ_n, "WDIRQ"),
                OP_NET_CONNECT(PIOIRQ_n, "PIOIRQ"),
                OP_NET_CONNECT(NFIQ_n, "NFIQ"),
                OP_NET_CONNECT(NIRQ_n, "NIRQ")
            )
        ),
        0
    );

    // PSE WD

    const char *WD_path = opVLNVString(
        0, // use the default VLNV path
        "atmel.ovpworld.org",
        0,
        "WatchdogTimer",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        WD_path,
        "WD",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(mainbus_b, "bp1", .slave=1, .addrLo=0xffff8000ULL, .addrHi=0xffffbfffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(WDIRQ_n, "IRQ")
            )
        ),
        0
    );

    // PSE PS

    const char *PS_path = opVLNVString(
        0, // use the default VLNV path
        "atmel.ovpworld.org",
        0,
        "PowerSaving",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        PS_path,
        "PS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(mainbus_b, "bp1", .slave=1, .addrLo=0xffff4000ULL, .addrHi=0xffff7fffULL)
            )
        ),
        0
    );

    // PSE PIO

    const char *PIO_path = opVLNVString(
        0, // use the default VLNV path
        "atmel.ovpworld.org",
        0,
        "ParallelIOController",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        PIO_path,
        "PIO",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(mainbus_b, "bp1", .slave=1, .addrLo=0xffff0000ULL, .addrHi=0xffff3fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(PIOIRQ_n, "IRQ")
            )
        ),
        0
    );

    // PSE TC

    const char *TC_path = opVLNVString(
        0, // use the default VLNV path
        "atmel.ovpworld.org",
        0,
        "TimerCounter",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        TC_path,
        "TC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(mainbus_b, "bp1", .slave=1, .addrLo=0xfffe0000ULL, .addrHi=0xfffe3fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(TC0IRQ_n, "IRQ0"),
                OP_NET_CONNECT(TC1IRQ_n, "IRQ1"),
                OP_NET_CONNECT(TC2IRQ_n, "IRQ2")
            )
        ),
        0
    );

    // PSE USART0

    const char *USART0_path = opVLNVString(
        0, // use the default VLNV path
        "atmel.ovpworld.org",
        0,
        "UsartInterface",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        USART0_path,
        "USART0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(mainbus_b, "asb"),
                OP_BUS_CONNECT(mainbus_b, "apb", .slave=1, .addrLo=0xfffd0000ULL, .addrHi=0xfffd3fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(US0IRQ_n, "IRQ")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
        )
    );

    // PSE USART1

    const char *USART1_path = opVLNVString(
        0, // use the default VLNV path
        "atmel.ovpworld.org",
        0,
        "UsartInterface",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        USART1_path,
        "USART1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(mainbus_b, "asb"),
                OP_BUS_CONNECT(mainbus_b, "apb", .slave=1, .addrLo=0xfffcc000ULL, .addrHi=0xfffcffffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(US1IRQ_n, "IRQ")
            )
        ),
        0
    );

    // PSE SF

    const char *SF_path = opVLNVString(
        0, // use the default VLNV path
        "atmel.ovpworld.org",
        0,
        "SpecialFunction",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        SF_path,
        "SF",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(mainbus_b, "bp1", .slave=1, .addrLo=0xfff00000ULL, .addrHi=0xfff03fffULL)
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
        .vendor  = "atmel.ovpworld.org",
        .library = "module",
        .name    = "AtmelAT91SAM7",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

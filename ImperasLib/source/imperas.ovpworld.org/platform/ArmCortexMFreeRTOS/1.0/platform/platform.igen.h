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
    opDocTextAdd(doc1_node, "Platform for FreeRTOS bring");
    optDocNodeP doc_11_node = opModuleDocSectionAdd(mi, "Licensing");
    opDocTextAdd(doc_11_node, "Open Source Apache 2.0");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "BareMetal platform for bring up of FreeRTOS on ARM Cortex-M3 processor");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "www.freertos.org");


    // Bus bus1

    optBusP bus1_b = opBusNew(mi, "bus1", 32, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP uart_irq_n = opNetNew(mi, "uart_irq", 0, 0);

    // Processor cpu1

    const char *cpu1_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "armm",
        0,
        OP_PROCESSOR,
        OP_VLNV_PRINT
    );

    optProcessorP cpu1_c = opProcessorNew(
        mi,
        cpu1_path,
        "cpu1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "INSTRUCTION"),
                OP_BUS_CONNECT(bus1_b, "DATA")
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(uart_irq_n, "int")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_DOUBLE_SET("mips", 12)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_ENUM_SET("variant", "Cortex-M3")
            ,OP_PARAM_BOOL_SET("UAL", 1)
        )
    );

    const char *armNewlib_0_expath = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "armNewlib",
        0,
        OP_EXTENSION,
        OP_VLNV_PRINT
    );

    opProcessorExtensionNew(
        cpu1_c,
        armNewlib_0_expath,
        "armNewlib_0_ex",
        0
    );

    // Memory memory1

    opMemoryNew(
        mi,
        "memory1",
        OP_PRIV_RWX,
        (0x3fffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x3fffffffULL)
            )
        ),
        0
    );

    // Memory memory2

    opMemoryNew(
        mi,
        "memory2",
        OP_PRIV_RWX,
        (0xffffffffULL) - (0x41000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "sp1", .slave=1, .addrLo=0x41000000ULL, .addrHi=0xffffffffULL)
            )
        ),
        0
    );

    // PSE LEDRegister

    const char *LEDRegister_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "ledRegister",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        LEDRegister_path,
        "LEDRegister",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "busPort", .slave=1, .addrLo=0x40004000ULL, .addrHi=0x40004007ULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("availableLEDS", 8)
        )
    );

    // PSE UART0

    const char *UART0_path = opVLNVString(
        0, // use the default VLNV path
        "ti.ovpworld.org",
        0,
        "UartInterface",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        UART0_path,
        "UART0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "bport1", .slave=1, .addrLo=0x4000c000ULL, .addrHi=0x4000cfffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(uart_irq_n, "irq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("console", 1)
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
            ,OP_PARAM_BOOL_SET("loopback", 1)
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
        .vendor  = "imperas.ovpworld.org",
        .library = "platform",
        .name    = "ArmCortexMFreeRTOS",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

static void cmdParserAddUserArgs(optCmdParserP parser) {
    opCmdParserAdd(parser, "rtos"    , 0 , 0, "user platform config", OP_FT_STRINGVAL     , &options.rtos, "the FreeRTOS image", OP_AC_ALL, 0, 1);
}

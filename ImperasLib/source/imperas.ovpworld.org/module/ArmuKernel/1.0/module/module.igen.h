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
    opDocTextAdd(doc_11_node, "\n    Bare Metal Platform for an ARM Cortex-A9MPx4 to execute the SMP UKernel.\n    This platform  executes the ARM MPCore Boot and Synchronization Example Code");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "BareMetal platform for execution of ARM binary uKernel file");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "http://www.arm.com/products/processors/cortex-a/arm-mpcore-sample-code.php");
    // Variables indicating when parameters are set

    // Variables holding parameter values
    UNUSED const char * uart1logname             = opObjectParamStringValue(mi, "uart1logname");


    // Bus bus1

    optBusP bus1_b = opBusNew(mi, "bus1", 32, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP irq_n = opNetNew(mi, "irq", 0, 0);

    // Processor cpu1

    const char *cpu1_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "arm",
        "1.0",
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
                OP_NET_CONNECT(irq_n, "SPI36")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_DOUBLE_SET("mips", 100.0)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_ENUM_SET("variant", "Cortex-A9MPx4")
            ,OP_PARAM_BOOL_SET("UAL", 1)
            ,OP_PARAM_UNS32_SET("override_CBAR", 0x1f000000)
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
        (0xfffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0xfffffffULL)
            )
        ),
        0
    );

    // Memory deviceDummy1

    opMemoryNew(
        mi,
        "deviceDummy1",
        OP_PRIV_RWX,
        (0x10008fffULL) - (0x10000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "sp1", .slave=1, .addrLo=0x10000000ULL, .addrHi=0x10008fffULL)
            )
        ),
        0
    );

    // Memory deviceDummy2

    opMemoryNew(
        mi,
        "deviceDummy2",
        OP_PRIV_RWX,
        (0xffffffffULL) - (0x1000a000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "sp1", .slave=1, .addrLo=0x1000a000ULL, .addrHi=0xffffffffULL)
            )
        ),
        0
    );

    // PSE uart1

    const char *uart1_path = opVLNVString(
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
        uart1_path,
        "uart1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "bport1", .slave=1, .addrLo=0x10009000ULL, .addrHi=0x10009fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(irq_n, "irq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_ENUM_SET("variant", "ARM")
            ,OP_PARAM_STRING_SET("outfile", uart1logname)
            ,OP_PARAM_BOOL_SET("console", 1)
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
        )
    );
////////////////////////////////////////////////////////////////////////////////
//                               Program loading
////////////////////////////////////////////////////////////////////////////////

    opProcessorApplicationLoad(cpu1_c, "cli.axf", OP_LDR_DEFAULT|OP_LDR_SET_START|OP_LDR_FAIL_IS_ERROR, 0);

}

static optParamSpec paramSpecs[] = {
    {
        .name        = "uart1logname",
        .type        = OP_PARAM_STRING,
        .description = 0,
        .spec.stringSpec.defaultValue = "uart1.log",
    },
    OP_HTTP_VIS_PORT_FORMALS,
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
        .vendor  = "imperas.ovpworld.org",
        .library = "module",
        .name    = "ArmuKernel",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
    .paramSpecsCB         = moduleParamIterator,
};

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
    opDocTextAdd(doc1_node, "Platform for Micrium uc/OS-II bring up and simple LED access");
    optDocNodeP doc_11_node = opModuleDocSectionAdd(mi, "Licensing");
    opDocTextAdd(doc_11_node, "Open Source Apache 2.0");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "BareMetal platform for bring up of uc/OS-II on ARM Cortex-M3 processor");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "www.micrium.com/page/products/rtos/os-ii");


    // Bus bus1

    optBusP bus1_b = opBusNew(mi, "bus1", 32, 0, 0);


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
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_DOUBLE_SET("mips", 100.0)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_ENUM_SET("variant", "Cortex-M3")
            ,OP_PARAM_ENUM_SET("compatibility", "gdb")
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

    // Memory memory2

    opMemoryNew(
        mi,
        "memory2",
        OP_PRIV_RWX,
        (0xffffffffULL) - (0x20000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "sp1", .slave=1, .addrLo=0x20000000ULL, .addrHi=0xffffffffULL)
            )
        ),
        0
    );

    // PSE led

    const char *led_path = opVLNVString(
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
        led_path,
        "led",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "busPort", .slave=1, .addrLo=0x10000000ULL, .addrHi=0x10000007ULL)
            )
        ),
        0
    );
////////////////////////////////////////////////////////////////////////////////
//                               Program loading
////////////////////////////////////////////////////////////////////////////////

    opProcessorApplicationLoad(cpu1_c, "ucosiiDemoApplication.ARM_CORTEX_M3.elf", OP_LDR_DEFAULT|OP_LDR_FAIL_IS_ERROR, 0);

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
        .name    = "ArmCortexMuCOS-II",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

static void cmdParserAddUserArgs(optCmdParserP parser) {
    opCmdParserAdd(parser, "kernel"  , 0 , 0, "user platform config", OP_FT_STRINGVAL     , &options.kernel, "the uc/OS-II image", OP_AC_ALL, 0, 1);
}

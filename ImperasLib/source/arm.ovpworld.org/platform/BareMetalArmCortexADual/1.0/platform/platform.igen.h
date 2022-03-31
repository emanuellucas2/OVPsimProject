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
    opDocTextAdd(doc1_node, "Bare Metal Platform for an ARM Cortex-A series Processor (default Cortex-A9UP).\n    The bare metal platform instantiates two ARM Cortex-A series processor instances. \n    The processor operates using little endian data ordering.\n    It creates contiguous memory from 0x00000000 to 0xFFFFFFFF.\n    The platform can be passed any application compiled to an ARM elf format. The\n    same application executes on each processor. There is no sharing of data.\n    It may also be passed a new variant to be used (default Cortex-A9UP)\n    ./platform.OS.exe application.CROSS.elf [model variant]");
    optDocNodeP doc_11_node = opModuleDocSectionAdd(mi, "Licensing");
    opDocTextAdd(doc_11_node, "Open Source Apache 2.0");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "BareMetal platform for execution of ARM binary files compiled with Linaro 32-bit CrossCompiler toolchain for Cortex-A.");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "None");


    // Bus bus0

    optBusP bus0_b = opBusNew(mi, "bus0", 32, 0, 0);


    // Bus bus1

    optBusP bus1_b = opBusNew(mi, "bus1", 32, 0, 0);


    // Processor cpu0

    const char *cpu0_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "arm",
        0,
        OP_PROCESSOR,
        OP_VLNV_PRINT
    );

    optProcessorP cpu0_c = opProcessorNew(
        mi,
        cpu0_path,
        "cpu0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "INSTRUCTION"),
                OP_BUS_CONNECT(bus0_b, "DATA")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("enableimperasintercepts", 1)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_ENUM_SET("variant", "Cortex-A9UP")
            ,OP_PARAM_ENUM_SET("compatibility", "nopSVC")
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
        cpu0_c,
        armNewlib_0_expath,
        "armNewlib_0_ex",
        0
    );

    // Processor cpu1

    const char *cpu1_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "arm",
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
             OP_PARAM_BOOL_SET("enableimperasintercepts", 1)
            ,OP_PARAM_UNS32_SET("cpuid", 1)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_ENUM_SET("variant", "Cortex-A9UP")
            ,OP_PARAM_ENUM_SET("compatibility", "nopSVC")
            ,OP_PARAM_BOOL_SET("UAL", 1)
        )
    );

    const char *armNewlib_1_expath = opVLNVString(
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
        armNewlib_1_expath,
        "armNewlib_1_ex",
        0
    );

    // Memory memory0

    opMemoryNew(
        mi,
        "memory0",
        OP_PRIV_RWX,
        (0xffffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0xffffffffULL)
            )
        ),
        0
    );

    // Memory memory1

    opMemoryNew(
        mi,
        "memory1",
        OP_PRIV_RWX,
        (0xffffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0xffffffffULL)
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
    .purpose              = OP_PP_BAREMETAL,
    .visibility           = OP_VISIBLE,
    .vlnv          = {
        .vendor  = "arm.ovpworld.org",
        .library = "platform",
        .name    = "BareMetalArmCortexADual",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

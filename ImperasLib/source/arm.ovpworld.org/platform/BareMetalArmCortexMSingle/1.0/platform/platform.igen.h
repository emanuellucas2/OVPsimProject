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
    opDocTextAdd(doc1_node, "Bare Metal Platform for an ARM Cortex-M series Processor (default Cortex-M3).\n    The bare metal platform instantiates a single ARM Cortex-M series processor instance. \n    The processor operates using little endian data ordering.\n    It creates contiguous memory from 0x00000000 to 0xFFFFFFFF.\n    The platform can be passed any application compiled to an ARM elf format.\n    It may also be passed a new variant to be used (default Cortex-M3)\n    ./platform.OS.exe --program application.CROSS.elf [ --variant <model variant>]");
    optDocNodeP doc_11_node = opModuleDocSectionAdd(mi, "Licensing");
    opDocTextAdd(doc_11_node, "Open Source Apache 2.0");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "BareMetal platform for execution of ARM binary files compiled with Linaro 32-bit CrossCompiler toolchain for Cortex-M.");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "None");


    // Bus bus

    optBusP bus_b = opBusNew(mi, "bus", 32, 0, 0);


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
                OP_BUS_CONNECT(bus_b, "INSTRUCTION"),
                OP_BUS_CONNECT(bus_b, "DATA")
            )
        ),
        OP_PARAMS(
             OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_ENUM_SET("variant", "Cortex-M3")
            ,OP_PARAM_ENUM_SET("compatibility", "nopBKPT")
            ,OP_PARAM_BOOL_SET("resetAtTime0", 0)
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

    // Memory memory

    opMemoryNew(
        mi,
        "memory",
        OP_PRIV_RWX,
        (0xffffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0xffffffffULL)
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
        .name    = "BareMetalArmCortexMSingle",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

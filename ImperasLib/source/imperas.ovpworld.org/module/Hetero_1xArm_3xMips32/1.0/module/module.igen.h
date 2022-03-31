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
    opDocTextAdd(doc1_node, "This is a hardware definition that instantiates 1 ARM processor and 3 MIPS processors.\n           Each processor has private independent memory areas from 0x00000000 to 0x01ffffff and from 0x0fff0000 to 0x0fffffff.\n           There is a shared area of memory that appears from 0x02000000 to 0x02ffffff in each processor memory map. ");
    optDocNodeP doc_11_node = opModuleDocSectionAdd(mi, "Licensing");
    opDocTextAdd(doc_11_node, "Open Source Apache 2.0");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "BareMetal platform for execution of specific example applications for MIPS32 and ARM Cortex-A.");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "None, BareMetal platform definition");


    // Bus busS

    optBusP busS_b = opBusNew(mi, "busS", 32, 0, 0);


    // Bus bus0

    optBusP bus0_b = opBusNew(mi, "bus0", 32, 0, 0);


    // Bus bus1

    optBusP bus1_b = opBusNew(mi, "bus1", 32, 0, 0);


    // Bus bus2

    optBusP bus2_b = opBusNew(mi, "bus2", 32, 0, 0);


    // Bus bus3

    optBusP bus3_b = opBusNew(mi, "bus3", 32, 0, 0);


    // Processor CPU0_ARM

    const char *CPU0_ARM_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "arm",
        0,
        OP_PROCESSOR,
        OP_VLNV_PRINT
    );

    opProcessorNew(
        mi,
        CPU0_ARM_path,
        "CPU0_ARM",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "INSTRUCTION"),
                OP_BUS_CONNECT(bus0_b, "DATA")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("defaultsemihost", 1)
            ,OP_PARAM_BOOL_SET("enableimperasintercepts", 1)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_ENUM_SET("variant", "Cortex-A9UP")
            ,OP_PARAM_ENUM_SET("compatibility", "nopSVC")
        )
    );


    // Processor CPU1_MIPS

    const char *CPU1_MIPS_path = opVLNVString(
        0, // use the default VLNV path
        "mips.ovpworld.org",
        0,
        "mips32_r1r5",
        0,
        OP_PROCESSOR,
        OP_VLNV_PRINT
    );

    opProcessorNew(
        mi,
        CPU1_MIPS_path,
        "CPU1_MIPS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "INSTRUCTION"),
                OP_BUS_CONNECT(bus1_b, "DATA")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("defaultsemihost", 1)
            ,OP_PARAM_BOOL_SET("enableimperasintercepts", 1)
            ,OP_PARAM_UNS32_SET("cpuid", 1)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_ENUM_SET("variant", "24KEc")
        )
    );


    // Processor CPU2_MIPS

    const char *CPU2_MIPS_path = opVLNVString(
        0, // use the default VLNV path
        "mips.ovpworld.org",
        0,
        "mips32_r1r5",
        0,
        OP_PROCESSOR,
        OP_VLNV_PRINT
    );

    opProcessorNew(
        mi,
        CPU2_MIPS_path,
        "CPU2_MIPS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus2_b, "INSTRUCTION"),
                OP_BUS_CONNECT(bus2_b, "DATA")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("defaultsemihost", 1)
            ,OP_PARAM_BOOL_SET("enableimperasintercepts", 1)
            ,OP_PARAM_UNS32_SET("cpuid", 2)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_ENUM_SET("variant", "24KEc")
        )
    );


    // Processor CPU3_MIPS

    const char *CPU3_MIPS_path = opVLNVString(
        0, // use the default VLNV path
        "mips.ovpworld.org",
        0,
        "mips32_r1r5",
        0,
        OP_PROCESSOR,
        OP_VLNV_PRINT
    );

    opProcessorNew(
        mi,
        CPU3_MIPS_path,
        "CPU3_MIPS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus3_b, "INSTRUCTION"),
                OP_BUS_CONNECT(bus3_b, "DATA")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("defaultsemihost", 1)
            ,OP_PARAM_BOOL_SET("enableimperasintercepts", 1)
            ,OP_PARAM_UNS32_SET("cpuid", 3)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_ENUM_SET("variant", "24KEc")
        )
    );


    // Memory sharedMem

    opMemoryNew(
        mi,
        "sharedMem",
        OP_PRIV_RWX,
        (0x2ffffffULL) - (0x2000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busS_b, "sp1", .slave=1, .addrLo=0x2000000ULL, .addrHi=0x2ffffffULL)
            )
        ),
        0
    );

    // Memory mem0

    opMemoryNew(
        mi,
        "mem0",
        OP_PRIV_RWX,
        (0x1ffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x1ffffffULL)
            )
        ),
        0
    );

    // Memory mem0h

    opMemoryNew(
        mi,
        "mem0h",
        OP_PRIV_RWX,
        (0xfffffffULL) - (0xfff0000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0xfff0000ULL, .addrHi=0xfffffffULL)
            )
        ),
        0
    );

    // Memory mem1

    opMemoryNew(
        mi,
        "mem1",
        OP_PRIV_RWX,
        (0x1ffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x1ffffffULL)
            )
        ),
        0
    );

    // Memory mem1h

    opMemoryNew(
        mi,
        "mem1h",
        OP_PRIV_RWX,
        (0xfffffffULL) - (0xfff0000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "sp1", .slave=1, .addrLo=0xfff0000ULL, .addrHi=0xfffffffULL)
            )
        ),
        0
    );

    // Memory mem2

    opMemoryNew(
        mi,
        "mem2",
        OP_PRIV_RWX,
        (0x1ffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus2_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x1ffffffULL)
            )
        ),
        0
    );

    // Memory mem2h

    opMemoryNew(
        mi,
        "mem2h",
        OP_PRIV_RWX,
        (0xfffffffULL) - (0xfff0000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus2_b, "sp1", .slave=1, .addrLo=0xfff0000ULL, .addrHi=0xfffffffULL)
            )
        ),
        0
    );

    // Memory mem3

    opMemoryNew(
        mi,
        "mem3",
        OP_PRIV_RWX,
        (0x1ffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus3_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0x1ffffffULL)
            )
        ),
        0
    );

    // Memory mem3h

    opMemoryNew(
        mi,
        "mem3h",
        OP_PRIV_RWX,
        (0xfffffffULL) - (0xfff0000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus3_b, "sp1", .slave=1, .addrLo=0xfff0000ULL, .addrHi=0xfffffffULL)
            )
        ),
        0
    );

    // Bridge br0

    opBridgeNew(
        mi,
        "br0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busS_b, "mp1", .addrLo=0x2000000ULL, .addrHi=0x2ffffffULL),
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x2000000ULL, .addrHi=0x2ffffffULL)
            )
        ),
        0
    );

    // Bridge br1

    opBridgeNew(
        mi,
        "br1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busS_b, "mp1", .addrLo=0x2000000ULL, .addrHi=0x2ffffffULL),
                OP_BUS_CONNECT(bus1_b, "sp1", .slave=1, .addrLo=0x2000000ULL, .addrHi=0x2ffffffULL)
            )
        ),
        0
    );

    // Bridge br2

    opBridgeNew(
        mi,
        "br2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busS_b, "mp1", .addrLo=0x2000000ULL, .addrHi=0x2ffffffULL),
                OP_BUS_CONNECT(bus2_b, "sp1", .slave=1, .addrLo=0x2000000ULL, .addrHi=0x2ffffffULL)
            )
        ),
        0
    );

    // Bridge br3

    opBridgeNew(
        mi,
        "br3",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busS_b, "mp1", .addrLo=0x2000000ULL, .addrHi=0x2ffffffULL),
                OP_BUS_CONNECT(bus3_b, "sp1", .slave=1, .addrLo=0x2000000ULL, .addrHi=0x2ffffffULL)
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
    .releaseStatus        = OP_IMPERAS,
    .purpose              = OP_PP_MODULE,
    .visibility           = OP_VISIBLE,
    .vlnv          = {
        .vendor  = "imperas.ovpworld.org",
        .library = "module",
        .name    = "Hetero_1xArm_3xMips32",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

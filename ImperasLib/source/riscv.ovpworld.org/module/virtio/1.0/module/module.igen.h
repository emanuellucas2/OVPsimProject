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
    opDocTextAdd(doc_11_node, "Virtio System Platform to boot BusyBear-Linux Kernel");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_21_node, "Virtio System Platform");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_31_node, "Sufficient functionality to boot BusyBear-Linux Kernel using the Virtio platform");


    // Bus bus0

    optBusP bus0_b = opBusNew(mi, "bus0", 48, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP irqT0_n = opNetNew(mi, "irqT0", 0, 0);
    optNetP irqT1_n = opNetNew(mi, "irqT1", 0, 0);
    optNetP irqS1_n = opNetNew(mi, "irqS1", 0, 0);
    optNetP irqS2_n = opNetNew(mi, "irqS2", 0, 0);
    optNetP irqS10_n = opNetNew(mi, "irqS10", 0, 0);
    optNetP MTimerInterrupt0_n = opNetNew(mi, "MTimerInterrupt0", 0, 0);
    optNetP MSWInterrupt0_n = opNetNew(mi, "MSWInterrupt0", 0, 0);

    // Processor hart0

    const char *hart0_path = opVLNVString(
        0, // use the default VLNV path
        "riscv.ovpworld.org",
        "processor",
        "riscv",
        "1.0",
        OP_PROCESSOR,
        OP_VLNV_PRINT
    );

    opProcessorNew(
        mi,
        hart0_path,
        "hart0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "INSTRUCTION"),
                OP_BUS_CONNECT(bus0_b, "DATA")
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(irqT0_n, "MExternalInterrupt"),
                OP_NET_CONNECT(irqT1_n, "SExternalInterrupt"),
                OP_NET_CONNECT(MTimerInterrupt0_n, "MTimerInterrupt"),
                OP_NET_CONNECT(MSWInterrupt0_n, "MSWInterrupt")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_DOUBLE_SET("mips", 50)
            ,OP_PARAM_ENUM_SET("variant", "RVB64I")
            ,OP_PARAM_STRING_SET("add_Extensions", "MAFDCSU")
            ,OP_PARAM_UNS64_SET("reset_address", 0x1000ULL)
            ,OP_PARAM_BOOL_SET("time_undefined", True)
        )
    );


    // Memory bootram

    opMemoryNew(
        mi,
        "bootram",
        OP_PRIV_RWX,
        (0x3fffULL) - (0x1000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x1000ULL, .addrHi=0x3fffULL)
            )
        ),
        0
    );

    // Memory main

    opMemoryNew(
        mi,
        "main",
        OP_PRIV_RWX,
        (0x87ffffffULL) - (0x80000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "sp1", .slave=1, .addrLo=0x80000000ULL, .addrHi=0x87ffffffULL)
            )
        ),
        0
    );

    // PSE VBD0

    const char *VBD0_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "VirtioBlkMMIO",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        VBD0_path,
        "VBD0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "dma", .addrLo=0x0ULL, .addrHi=0xffffffffULL),
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .addrLo=0x10001000ULL, .addrHi=0x100011ffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(irqS1_n, "Interrupt")
            )
        ),
        0
    );

    // PSE VND0

    const char *VND0_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "VirtioNetMMIO",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        VND0_path,
        "VND0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "dma", .addrLo=0x0ULL, .addrHi=0xffffffffULL),
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .addrLo=0x10002000ULL, .addrHi=0x100021ffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(irqS2_n, "Interrupt")
            )
        ),
        0
    );

    // PSE virtio_mmio3

    const char *virtio_mmio3_path = opVLNVString(
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
        virtio_mmio3_path,
        "virtio_mmio3",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x10003000)
            ,OP_PARAM_UNS32_SET("portSize", 4096)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE virtio_mmio4

    const char *virtio_mmio4_path = opVLNVString(
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
        virtio_mmio4_path,
        "virtio_mmio4",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x10004000)
            ,OP_PARAM_UNS32_SET("portSize", 4096)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE virtio_mmio5

    const char *virtio_mmio5_path = opVLNVString(
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
        virtio_mmio5_path,
        "virtio_mmio5",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x10005000)
            ,OP_PARAM_UNS32_SET("portSize", 4096)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE virtio_mmio6

    const char *virtio_mmio6_path = opVLNVString(
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
        virtio_mmio6_path,
        "virtio_mmio6",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x10006000)
            ,OP_PARAM_UNS32_SET("portSize", 4096)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE virtio_mmio7

    const char *virtio_mmio7_path = opVLNVString(
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
        virtio_mmio7_path,
        "virtio_mmio7",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x10007000)
            ,OP_PARAM_UNS32_SET("portSize", 4096)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE virtio_mmio8

    const char *virtio_mmio8_path = opVLNVString(
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
        virtio_mmio8_path,
        "virtio_mmio8",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x10008000)
            ,OP_PARAM_UNS32_SET("portSize", 4096)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE clint

    const char *clint_path = opVLNVString(
        0, // use the default VLNV path
        "riscv.ovpworld.org",
        "peripheral",
        "CLINT",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        clint_path,
        "clint",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "port0", .slave=1, .addrLo=0x2000000ULL, .addrHi=0x200bfffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(MTimerInterrupt0_n, "MTimerInterrupt0"),
                OP_NET_CONNECT(MSWInterrupt0_n, "MSWInterrupt0")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("num_harts", 1)
            ,OP_PARAM_DOUBLE_SET("clockMHz", 25.0)
        )
    );

    // PSE plic

    const char *plic_path = opVLNVString(
        0, // use the default VLNV path
        "riscv.ovpworld.org",
        "peripheral",
        "PLIC",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        plic_path,
        "plic",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "port0", .slave=1, .addrLo=0xc000000ULL, .addrHi=0xfffffffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(irqT0_n, "irqT0"),
                OP_NET_CONNECT(irqT1_n, "irqT1"),
                OP_NET_CONNECT(irqS1_n, "irqS1"),
                OP_NET_CONNECT(irqS2_n, "irqS2"),
                OP_NET_CONNECT(irqS10_n, "irqS10")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("num_sources", 10)
            ,OP_PARAM_UNS32_SET("num_targets", 2)
        )
    );

    // PSE uartTTY0

    const char *uartTTY0_path = opVLNVString(
        0, // use the default VLNV path
        "national.ovpworld.org",
        "peripheral",
        "16550",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uartTTY0_path,
        "uartTTY0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "bport1", .slave=1, .addrLo=0x10000000ULL, .addrHi=0x10000007ULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(irqS10_n, "intOut")
            )
        ),
        0
    );

    // PSE smartLoader

    const char *smartLoader_path = opVLNVString(
        0, // use the default VLNV path
        "riscv.ovpworld.org",
        0,
        "SmartLoaderRV64Linux",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        smartLoader_path,
        "smartLoader",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus0_b, "mport", .addrLo=0x0ULL, .addrHi=0xffffffffULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS64_SET("bootaddr", 0x80000000ULL)
            ,OP_PARAM_UNS64_SET("slbootaddr", 0x1000ULL)
            ,OP_PARAM_UNS64_SET("membase", 0x80000000ULL)
            ,OP_PARAM_UNS64_SET("memsize", 0x8000000ULL)
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
        .vendor  = "riscv.ovpworld.org",
        .library = "module",
        .name    = "virtio",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

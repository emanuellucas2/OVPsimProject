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
    opDocTextAdd(doc_11_node, "This is a platform representing a MIPS Malta development board.\n    It provides the peripherals required to boot and run a Linux Operating System.\n    A single MIPS32 architecture processor is instantiated in this platform.\n    This instance could be duplicated to instantiate further processors to easily create an SMP platform.\n    Attributes are provided for configuration of the generic ISA model for a specific processor.\n    The processor model is configured to operate as a MIPS32 4KEc.\n\n    The main SDRAM and Flash memory is modeled using RAM models. Both are initialised in places by the\n    'SmartLoaderLinux'. The SmartLoaderLinux allows ease of use of changing kernel command lines,\n    loading an initial ram disk and creating the boot flash(s). The operation of the SmartloaderLinux is configured\n    using a number of attributes.  \n       The kernel attribute of the SmartLoaderLinux and the imagefile of the processor must be consistent.\n\n    NOTE: a non Mips Malta peripheral 'AlphaDisplay16x2' has been defined in this platform definition\n          to be used for demo purposes. It should be removed if there is a memory error in the address space 0x18000100-0x18000103\n\n    If this platform is not part of your installation, then it is available for download from www.OVPworld.org/ip-vendor-mips.");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "Verification has only been carried out using Little Endian memory ordering.");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "MIPS Malta User's Manual MD00048-2B-MALTA-USM-1.07.pdf\n           MIPS Malta-R Development Platform User's Manual MD00627-2B-MALTA_R-USM-01.01.pdf    \n           CoreFPGA User's Manual MD00116-2B-COREFPGA-USM-01.00.pdf\n           Linux for the MIPS Malta Development Platform User's Guide MD00646-2B-LINUXMALTA-USM-01.03.pdf");
    // Variables indicating when parameters are set
    Bool addressbits_isSet        = 0;

    // Variables holding parameter values
    UNUSED Uns32        addressbits              = opObjectParamUns32Value(mi, "addressbits", &addressbits_isSet);
    UNUSED const char * processorinterrupt       = opObjectParamStringValue(mi, "processorinterrupt");


    // Bus bus1

    optBusP bus1_b = opBusNew(mi, "bus1", addressbits, 0, 0);


    // Bus busPCI

    optBusP busPCI_b = opBusNew(mi, "busPCI", 32, 0, 0);


    // Bus busPCIReMap

    optBusP busPCIReMap_b = opBusNew(mi, "busPCIReMap", 32, 0, 0);


    // Bus PCIconfigBus

    optBusP PCIconfigBus_b = opBusNew(mi, "PCIconfigBus", 16, 0, 0);


    // Bus PCIackBus

    optBusP PCIackBus_b = opBusNew(mi, "PCIackBus", 0, 0, 0);


    // Bus cascadeBus

    optBusP cascadeBus_b = opBusNew(mi, "cascadeBus", 3, 0, 0);


    // Bus flashBus

    optBusP flashBus_b = opBusNew(mi, "flashBus", 32, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP intCtl_ir1_n = opNetNew(mi, "intCtl_ir1", 0, 0);
    optNetP intCtl_ir3_n = opNetNew(mi, "intCtl_ir3", 0, 0);
    optNetP intCtl_ir4_n = opNetNew(mi, "intCtl_ir4", 0, 0);
    optNetP intCtl_ir8_n = opNetNew(mi, "intCtl_ir8", 0, 0);
    optNetP intCtl_ir10_n = opNetNew(mi, "intCtl_ir10", 0, 0);
    optNetP intCtl_ir12_n = opNetNew(mi, "intCtl_ir12", 0, 0);
    optNetP intCtl_ir14_n = opNetNew(mi, "intCtl_ir14", 0, 0);
    optNetP intCtl_ir15_n = opNetNew(mi, "intCtl_ir15", 0, 0);
    optNetP i8259Int_n = opNetNew(mi, "i8259Int", 0, 0);
    optNetP i8259Cascade_n = opNetNew(mi, "i8259Cascade", 0, 0);

    // Processor mipsle1

    const char *mipsle1_path = opVLNVString(
        0, // use the default VLNV path
        "mips.ovpworld.org",
        "processor",
        "mips32_r1r5",
        0,
        OP_PROCESSOR,
        OP_VLNV_PRINT
    );

    opProcessorNew(
        mi,
        mipsle1_path,
        "mipsle1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "INSTRUCTION"),
                OP_BUS_CONNECT(bus1_b, "DATA")
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(i8259Int_n, processorinterrupt)
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_DOUBLE_SET("mips", 100.0)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_ENUM_SET("variant", "34Kc")
            ,OP_PARAM_BOOL_SET("vectoredinterrupt", 0)
            ,OP_PARAM_UNS32_SET("config1MMUSizeM1", 63)
        )
    );


    // Memory Core_Board_SDRAM

    opMemoryNew(
        mi,
        "Core_Board_SDRAM",
        OP_PRIV_RWX,
        (0xfffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0xfffffffULL)
            )
        ),
        0
    );

    // Memory Core_Board_SDRAM2

    opMemoryNew(
        mi,
        "Core_Board_SDRAM2",
        OP_PRIV_RWX,
        (0x5fffffffULL) - (0x20000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "sp1", .slave=1, .addrLo=0x20000000ULL, .addrHi=0x5fffffffULL)
            )
        ),
        0
    );

    // Memory Monitor_Flash

    opMemoryNew(
        mi,
        "Monitor_Flash",
        OP_PRIV_RWX,
        (0x1e3fffffULL) - (0x1e000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(flashBus_b, "sp1", .slave=1, .addrLo=0x1e000000ULL, .addrHi=0x1e3fffffULL)
            )
        ),
        0
    );

    // Memory vgaMemRegion

    opMemoryNew(
        mi,
        "vgaMemRegion",
        OP_PRIV_RX,
        (0x100bffffULL) - (0x100a0000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busPCI_b, "sp1", .slave=1, .addrLo=0x100a0000ULL, .addrHi=0x100bffffULL)
            )
        ),
        0
    );

    // Bridge pciBr

    opBridgeNew(
        mi,
        "pciBr",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busPCI_b, "mp1", .addrLo=0x10000000ULL, .addrHi=0x1bffffffULL),
                OP_BUS_CONNECT(bus1_b, "sp1", .slave=1, .addrLo=0x10000000ULL, .addrHi=0x1bffffffULL)
            )
        ),
        0
    );

    // Bridge pciMBr

    opBridgeNew(
        mi,
        "pciMBr",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "mp1", .addrLo=0x0ULL, .addrHi=0xfffffffULL),
                OP_BUS_CONNECT(busPCI_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0xfffffffULL)
            )
        ),
        0
    );

    // Bridge map

    opBridgeNew(
        mi,
        "map",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(flashBus_b, "mp1", .addrLo=0x1e000000ULL, .addrHi=0x1e3fffffULL),
                OP_BUS_CONNECT(bus1_b, "sp1", .slave=1, .addrLo=0x1e000000ULL, .addrHi=0x1e3fffffULL)
            )
        ),
        0
    );

    // Bridge remap1

    opBridgeNew(
        mi,
        "remap1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(flashBus_b, "mp1", .addrLo=0x1e000000ULL, .addrHi=0x1e00000fULL),
                OP_BUS_CONNECT(bus1_b, "sp1", .slave=1, .addrLo=0x1fc00000ULL, .addrHi=0x1fc0000fULL)
            )
        ),
        0
    );

    // Bridge remap2

    opBridgeNew(
        mi,
        "remap2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(flashBus_b, "mp1", .addrLo=0x1e000014ULL, .addrHi=0x1e3fffffULL),
                OP_BUS_CONNECT(bus1_b, "sp1", .slave=1, .addrLo=0x1fc00014ULL, .addrHi=0x1fffffffULL)
            )
        ),
        0
    );

    // Bridge high2low

    opBridgeNew(
        mi,
        "high2low",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "mp1", .addrLo=0x0ULL, .addrHi=0x7fffffffULL),
                OP_BUS_CONNECT(bus1_b, "sp1", .slave=1, .addrLo=0x80000000ULL, .addrHi=0xffffffffULL)
            )
        ),
        0
    );

    // PSE Core_Board_SDRAM_promInit

    const char *Core_Board_SDRAM_promInit_path = opVLNVString(
        0, // use the default VLNV path
        "mips.ovpworld.org",
        "peripheral",
        "SmartLoaderLinux",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        Core_Board_SDRAM_promInit_path,
        "Core_Board_SDRAM_promInit",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "mport", .addrLo=0x0ULL, .addrHi=0xffffffffULL),
                OP_BUS_CONNECT(bus1_b, "idport", .slave=1, .addrLo=0x1fc00010ULL, .addrHi=0x1fc00013ULL)
            )
        ),
        0
    );

    // PSE sysControl

    const char *sysControl_path = opVLNVString(
        0, // use the default VLNV path
        "marvell.ovpworld.org",
        "peripheral",
        "GT6412x",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        sysControl_path,
        "sysControl",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(PCIconfigBus_b, "PCIconfigM"),
                OP_BUS_CONNECT(PCIackBus_b, "PCIackM"),
                OP_BUS_CONNECT(busPCI_b, "busPort", .slave=1, .dynamic=1),
                OP_BUS_CONNECT(PCIconfigBus_b, "PCIconfig", .slave=1, .dynamic=1)
            )
        ),
        0
    );

    // PSE PIIX4

    const char *PIIX4_path = opVLNVString(
        0, // use the default VLNV path
        "intel.ovpworld.org",
        "peripheral",
        "82371EB",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        PIIX4_path,
        "PIIX4",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(PCIconfigBus_b, "PCIconfig", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCIslot", 10)
        )
    );

    // PSE PIIX4-IDE

    const char *PIIX4_IDE_path = opVLNVString(
        0, // use the default VLNV path
        "intel.ovpworld.org",
        "peripheral",
        "PciIDE",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        PIIX4_IDE_path,
        "PIIX4-IDE",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busPCI_b, "dmaPort"),
                OP_BUS_CONNECT(PCIconfigBus_b, "PCIconfig", .slave=1, .dynamic=1),
                OP_BUS_CONNECT(busPCI_b, "busPort", .slave=1, .dynamic=1)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(intCtl_ir14_n, "intOut0"),
                OP_NET_CONNECT(intCtl_ir15_n, "intOut1")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCIslot", 10)
            ,OP_PARAM_UNS32_SET("PCIfunction", 1)
        )
    );

    // PSE PCI_PM

    const char *PCI_PM_path = opVLNVString(
        0, // use the default VLNV path
        "intel.ovpworld.org",
        "peripheral",
        "PciPM",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        PCI_PM_path,
        "PCI_PM",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(PCIconfigBus_b, "PCIconfig", .slave=1, .dynamic=1),
                OP_BUS_CONNECT(busPCI_b, "busPort", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCIslot", 10)
            ,OP_PARAM_UNS32_SET("PCIfunction", 3)
        )
    );

    // PSE PCI_NET

    const char *PCI_NET_path = opVLNVString(
        0, // use the default VLNV path
        "amd.ovpworld.org",
        "peripheral",
        "79C970",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        PCI_NET_path,
        "PCI_NET",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busPCI_b, "dmaPort"),
                OP_BUS_CONNECT(PCIconfigBus_b, "PCIconfig", .slave=1, .dynamic=1),
                OP_BUS_CONNECT(busPCI_b, "busPort", .slave=1, .dynamic=1)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(intCtl_ir10_n, "intOut0")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("PCIslot", 11)
            ,OP_PARAM_UNS32_SET("PCIfunction", 0)
        )
    );

    // PSE intCtrlMaster

    const char *intCtrlMaster_path = opVLNVString(
        0, // use the default VLNV path
        "intel.ovpworld.org",
        "peripheral",
        "8259A",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        intCtrlMaster_path,
        "intCtrlMaster",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(cascadeBus_b, "cascade"),
                OP_BUS_CONNECT(busPCIReMap_b, "io", .slave=1, .addrLo=0x18000020ULL, .addrHi=0x18000021ULL),
                OP_BUS_CONNECT(busPCIReMap_b, "elcr", .slave=1, .addrLo=0x180004d0ULL, .addrHi=0x180004d0ULL),
                OP_BUS_CONNECT(PCIackBus_b, "PCIackS", .slave=1, .addrLo=0x0ULL, .addrHi=0x0ULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(i8259Int_n, "intp"),
                OP_NET_CONNECT(intCtl_ir1_n, "ir1"),
                OP_NET_CONNECT(i8259Cascade_n, "ir2"),
                OP_NET_CONNECT(intCtl_ir3_n, "ir3"),
                OP_NET_CONNECT(intCtl_ir4_n, "ir4")
            )
        ),
        OP_PARAMS(
             OP_PARAM_ENUM_SET("spen", "master")
        )
    );

    // PSE pciBrD_intCtrlMaster_io

    const char *pciBrD_intCtrlMaster_io_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "DynamicBridge",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        pciBrD_intCtrlMaster_io_path,
        "pciBrD_intCtrlMaster_io",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busPCIReMap_b, "mp"),
                OP_BUS_CONNECT(busPCI_b, "sp", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS64_SET("spLoAddress", 0x18000020ULL)
            ,OP_PARAM_UNS64_SET("mpLoAddress", 0x18000020ULL)
            ,OP_PARAM_UNS64_SET("portSize", 0x2ULL)
            ,OP_PARAM_BOOL_SET("enableBridge", 1)
        )
    );

    // PSE pciBrD_intCtrlMaster_elcr

    const char *pciBrD_intCtrlMaster_elcr_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "DynamicBridge",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        pciBrD_intCtrlMaster_elcr_path,
        "pciBrD_intCtrlMaster_elcr",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busPCIReMap_b, "mp"),
                OP_BUS_CONNECT(busPCI_b, "sp", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS64_SET("spLoAddress", 0x180004d0ULL)
            ,OP_PARAM_UNS64_SET("mpLoAddress", 0x180004d0ULL)
            ,OP_PARAM_UNS64_SET("portSize", 0x1ULL)
            ,OP_PARAM_BOOL_SET("enableBridge", 1)
        )
    );

    // PSE intCtrlSlave

    const char *intCtrlSlave_path = opVLNVString(
        0, // use the default VLNV path
        "intel.ovpworld.org",
        "peripheral",
        "8259A",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        intCtrlSlave_path,
        "intCtrlSlave",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busPCIReMap_b, "io", .slave=1, .addrLo=0x180000a0ULL, .addrHi=0x180000a1ULL),
                OP_BUS_CONNECT(busPCIReMap_b, "elcr", .slave=1, .addrLo=0x180004d1ULL, .addrHi=0x180004d1ULL),
                OP_BUS_CONNECT(cascadeBus_b, "PCIackS", .slave=1, .addrLo=0x2ULL, .addrHi=0x2ULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(intCtl_ir8_n, "ir0"),
                OP_NET_CONNECT(intCtl_ir10_n, "ir2"),
                OP_NET_CONNECT(intCtl_ir12_n, "ir4"),
                OP_NET_CONNECT(intCtl_ir14_n, "ir6"),
                OP_NET_CONNECT(intCtl_ir15_n, "ir7"),
                OP_NET_CONNECT(i8259Cascade_n, "intp")
            )
        ),
        OP_PARAMS(
             OP_PARAM_ENUM_SET("spen", "slave")
        )
    );

    // PSE pciBrD_intCtrlSlave_io

    const char *pciBrD_intCtrlSlave_io_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "DynamicBridge",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        pciBrD_intCtrlSlave_io_path,
        "pciBrD_intCtrlSlave_io",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busPCIReMap_b, "mp"),
                OP_BUS_CONNECT(busPCI_b, "sp", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS64_SET("spLoAddress", 0x180000a0ULL)
            ,OP_PARAM_UNS64_SET("mpLoAddress", 0x180000a0ULL)
            ,OP_PARAM_UNS64_SET("portSize", 0x2ULL)
            ,OP_PARAM_BOOL_SET("enableBridge", 1)
        )
    );

    // PSE pciBrD_intCtrlSlave_elcr

    const char *pciBrD_intCtrlSlave_elcr_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "DynamicBridge",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        pciBrD_intCtrlSlave_elcr_path,
        "pciBrD_intCtrlSlave_elcr",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busPCIReMap_b, "mp"),
                OP_BUS_CONNECT(busPCI_b, "sp", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS64_SET("spLoAddress", 0x180004d1ULL)
            ,OP_PARAM_UNS64_SET("mpLoAddress", 0x180004d1ULL)
            ,OP_PARAM_UNS64_SET("portSize", 0x1ULL)
            ,OP_PARAM_BOOL_SET("enableBridge", 1)
        )
    );

    // PSE _SUPERIO_REG_

    const char *_SUPERIO_REG__path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "SerInt",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        _SUPERIO_REG__path,
        "_SUPERIO_REG_",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busPCIReMap_b, "bport1", .slave=1, .addrLo=0x180000b0ULL, .addrHi=0x180000b3ULL)
            )
        ),
        0
    );

    // PSE pciBrD__SUPERIO_REG__bport1

    const char *pciBrD__SUPERIO_REG__bport1_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "DynamicBridge",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        pciBrD__SUPERIO_REG__bport1_path,
        "pciBrD__SUPERIO_REG__bport1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busPCIReMap_b, "mp"),
                OP_BUS_CONNECT(busPCI_b, "sp", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS64_SET("spLoAddress", 0x180000b0ULL)
            ,OP_PARAM_UNS64_SET("mpLoAddress", 0x180000b0ULL)
            ,OP_PARAM_UNS64_SET("portSize", 0x4ULL)
            ,OP_PARAM_BOOL_SET("enableBridge", 1)
        )
    );

    // PSE vga

    const char *vga_path = opVLNVString(
        0, // use the default VLNV path
        "cirrus.ovpworld.org",
        "peripheral",
        "GD5446",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        vga_path,
        "vga",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(PCIconfigBus_b, "PCIconfig", .slave=1, .dynamic=1),
                OP_BUS_CONNECT(busPCIReMap_b, "config", .slave=1, .addrLo=0x180003b0ULL, .addrHi=0x180003dfULL),
                OP_BUS_CONNECT(busPCI_b, "memory", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("scanDelay", 50000)
            ,OP_PARAM_UNS32_SET("PCIslot", 18)
            ,OP_PARAM_STRING_SET("title", "Imperas MIPS32 Malta")
        )
    );

    // PSE pciBrD_vga_config

    const char *pciBrD_vga_config_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "DynamicBridge",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        pciBrD_vga_config_path,
        "pciBrD_vga_config",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busPCIReMap_b, "mp"),
                OP_BUS_CONNECT(busPCI_b, "sp", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS64_SET("spLoAddress", 0x180003b0ULL)
            ,OP_PARAM_UNS64_SET("mpLoAddress", 0x180003b0ULL)
            ,OP_PARAM_UNS64_SET("portSize", 0x30ULL)
            ,OP_PARAM_BOOL_SET("enableBridge", 1)
        )
    );

    // PSE ps2if

    const char *ps2if_path = opVLNVString(
        0, // use the default VLNV path
        "intel.ovpworld.org",
        "peripheral",
        "Ps2Control",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ps2if_path,
        "ps2if",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busPCIReMap_b, "config", .slave=1, .addrLo=0x18000060ULL, .addrHi=0x18000067ULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(intCtl_ir1_n, "kbdInterrupt"),
                OP_NET_CONNECT(intCtl_ir12_n, "mouseInterrupt")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("pollPeriod", 50000)
            ,OP_PARAM_BOOL_SET("grabDisable", 1)
        )
    );

    // PSE pciBrD_ps2if_config

    const char *pciBrD_ps2if_config_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "DynamicBridge",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        pciBrD_ps2if_config_path,
        "pciBrD_ps2if_config",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busPCIReMap_b, "mp"),
                OP_BUS_CONNECT(busPCI_b, "sp", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS64_SET("spLoAddress", 0x18000060ULL)
            ,OP_PARAM_UNS64_SET("mpLoAddress", 0x18000060ULL)
            ,OP_PARAM_UNS64_SET("portSize", 0x8ULL)
            ,OP_PARAM_BOOL_SET("enableBridge", 1)
        )
    );

    // PSE pit

    const char *pit_path = opVLNVString(
        0, // use the default VLNV path
        "intel.ovpworld.org",
        "peripheral",
        "8253",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        pit_path,
        "pit",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busPCIReMap_b, "bport1", .slave=1, .addrLo=0x18000040ULL, .addrHi=0x18000043ULL)
            )
        ),
        0
    );

    // PSE pciBrD_pit_bport1

    const char *pciBrD_pit_bport1_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "DynamicBridge",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        pciBrD_pit_bport1_path,
        "pciBrD_pit_bport1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busPCIReMap_b, "mp"),
                OP_BUS_CONNECT(busPCI_b, "sp", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS64_SET("spLoAddress", 0x18000040ULL)
            ,OP_PARAM_UNS64_SET("mpLoAddress", 0x18000040ULL)
            ,OP_PARAM_UNS64_SET("portSize", 0x4ULL)
            ,OP_PARAM_BOOL_SET("enableBridge", 1)
        )
    );

    // PSE rtc

    const char *rtc_path = opVLNVString(
        0, // use the default VLNV path
        "motorola.ovpworld.org",
        "peripheral",
        "MC146818",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        rtc_path,
        "rtc",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busPCIReMap_b, "busPort", .slave=1, .addrLo=0x18000070ULL, .addrHi=0x18000071ULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(intCtl_ir8_n, "timerInt")
            )
        ),
        0
    );

    // PSE pciBrD_rtc_busPort

    const char *pciBrD_rtc_busPort_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "DynamicBridge",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        pciBrD_rtc_busPort_path,
        "pciBrD_rtc_busPort",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busPCIReMap_b, "mp"),
                OP_BUS_CONNECT(busPCI_b, "sp", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS64_SET("spLoAddress", 0x18000070ULL)
            ,OP_PARAM_UNS64_SET("mpLoAddress", 0x18000070ULL)
            ,OP_PARAM_UNS64_SET("portSize", 0x2ULL)
            ,OP_PARAM_BOOL_SET("enableBridge", 1)
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
                OP_BUS_CONNECT(busPCIReMap_b, "bport1", .slave=1, .addrLo=0x180003f8ULL, .addrHi=0x180003ffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(intCtl_ir4_n, "intOut")
            )
        ),
        OP_PARAMS(
             OP_PARAM_STRING_SET("outfile", "uartTTY0.log")
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
        )
    );

    // PSE pciBrD_uartTTY0_bport1

    const char *pciBrD_uartTTY0_bport1_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "DynamicBridge",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        pciBrD_uartTTY0_bport1_path,
        "pciBrD_uartTTY0_bport1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busPCIReMap_b, "mp"),
                OP_BUS_CONNECT(busPCI_b, "sp", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS64_SET("spLoAddress", 0x180003f8ULL)
            ,OP_PARAM_UNS64_SET("mpLoAddress", 0x180003f8ULL)
            ,OP_PARAM_UNS64_SET("portSize", 0x8ULL)
            ,OP_PARAM_BOOL_SET("enableBridge", 1)
        )
    );

    // PSE uartTTY1

    const char *uartTTY1_path = opVLNVString(
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
        uartTTY1_path,
        "uartTTY1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busPCIReMap_b, "bport1", .slave=1, .addrLo=0x180002f8ULL, .addrHi=0x180002ffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(intCtl_ir3_n, "intOut")
            )
        ),
        OP_PARAMS(
             OP_PARAM_STRING_SET("outfile", "uartTTY1.log")
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
        )
    );

    // PSE pciBrD_uartTTY1_bport1

    const char *pciBrD_uartTTY1_bport1_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "DynamicBridge",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        pciBrD_uartTTY1_bport1_path,
        "pciBrD_uartTTY1_bport1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busPCIReMap_b, "mp"),
                OP_BUS_CONNECT(busPCI_b, "sp", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS64_SET("spLoAddress", 0x180002f8ULL)
            ,OP_PARAM_UNS64_SET("mpLoAddress", 0x180002f8ULL)
            ,OP_PARAM_UNS64_SET("portSize", 0x8ULL)
            ,OP_PARAM_BOOL_SET("enableBridge", 1)
        )
    );

    // PSE fd0

    const char *fd0_path = opVLNVString(
        0, // use the default VLNV path
        "intel.ovpworld.org",
        "peripheral",
        "82077AA",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        fd0_path,
        "fd0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busPCIReMap_b, "bport1", .slave=1, .addrLo=0x180003f0ULL, .addrHi=0x180003f7ULL)
            )
        ),
        0
    );

    // PSE pciBrD_fd0_bport1

    const char *pciBrD_fd0_bport1_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "DynamicBridge",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        pciBrD_fd0_bport1_path,
        "pciBrD_fd0_bport1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busPCIReMap_b, "mp"),
                OP_BUS_CONNECT(busPCI_b, "sp", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS64_SET("spLoAddress", 0x180003f0ULL)
            ,OP_PARAM_UNS64_SET("mpLoAddress", 0x180003f0ULL)
            ,OP_PARAM_UNS64_SET("portSize", 0x8ULL)
            ,OP_PARAM_BOOL_SET("enableBridge", 1)
        )
    );

    // PSE uartCBUS

    const char *uartCBUS_path = opVLNVString(
        0, // use the default VLNV path
        "mips.ovpworld.org",
        "peripheral",
        "16450C",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uartCBUS_path,
        "uartCBUS",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "bport1", .slave=1, .addrLo=0x1f000900ULL, .addrHi=0x1f00093fULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_STRING_SET("outfile", "uartCBUS.log")
        )
    );

    // PSE maltaFpga

    const char *maltaFpga_path = opVLNVString(
        0, // use the default VLNV path
        "mips.ovpworld.org",
        "peripheral",
        "MaltaFPGA",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        maltaFpga_path,
        "maltaFpga",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1_b, "busPort1", .slave=1, .addrLo=0x1f000000ULL, .addrHi=0x1f0008ffULL),
                OP_BUS_CONNECT(bus1_b, "busPort2", .slave=1, .addrLo=0x1f000a00ULL, .addrHi=0x1f000fffULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("stoponsoftreset", 1)
        )
    );

    // PSE alphaDisplay

    const char *alphaDisplay_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "Alpha2x16Display",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        alphaDisplay_path,
        "alphaDisplay",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busPCIReMap_b, "busPort", .slave=1, .addrLo=0x18000100ULL, .addrHi=0x18000103ULL)
            )
        ),
        0
    );

    // PSE pciBrD_alphaDisplay_busPort

    const char *pciBrD_alphaDisplay_busPort_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "DynamicBridge",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        pciBrD_alphaDisplay_busPort_path,
        "pciBrD_alphaDisplay_busPort",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(busPCIReMap_b, "mp"),
                OP_BUS_CONNECT(busPCI_b, "sp", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS64_SET("spLoAddress", 0x18000100ULL)
            ,OP_PARAM_UNS64_SET("mpLoAddress", 0x18000100ULL)
            ,OP_PARAM_UNS64_SET("portSize", 0x4ULL)
            ,OP_PARAM_BOOL_SET("enableBridge", 1)
        )
    );

}

static optParamSpec paramSpecs[] = {
    {
        .name        = "addressbits",
        .type        = OP_PARAM_UNS32,
        .description = "Formal parameter addressbits allows the address bits for the main bus to be modified (default 32)",
        .spec.uns32Spec.min          = 32,
        .spec.uns32Spec.max          = 64,
        .spec.uns32Spec.defaultValue = 32,
    },
    {
        .name        = "processorinterrupt",
        .type        = OP_PARAM_STRING,
        .description = "Formal parameter processorinterrupt allows the interrupt pin used on the processor to be modified to select direct interrupts or GIC interrupts (default hwint0)",
        .spec.stringSpec.defaultValue = "hwint0",
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
        .vendor  = "mips.ovpworld.org",
        .library = "module",
        .name    = "MipsMalta",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
    .paramSpecsCB         = moduleParamIterator,
};

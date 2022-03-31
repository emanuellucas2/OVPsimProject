/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */

#include "op/op.h"

#define MODULE_NAME "simpleCpuMemoryUart"

static OP_CONSTRUCT_FN(moduleConstructor) {

    // Bus mainBus

    optBusP mainBus_b = opBusNew(mi, "mainBus", 32, 0, 0);

    // nets
    
    optNetP directWrite_n = opNetNew(mi, "directWrite", 0, 0);
    optNetP directRead_n = opNetNew(mi, "directRead", 0, 0);

    // Processor cpu1

    const char *cpu1_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        "processor",
        "or1k",
        "1.0",
        OP_PROCESSOR,
        OP_VLNV_FATAL
    );

    optProcessorP cpu1_c = opProcessorNew(
        mi,
        cpu1_path,
        "cpu1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(mainBus_b, "INSTRUCTION"),
                OP_BUS_CONNECT(mainBus_b, "DATA")
            )
        ),
        OP_PARAMS(
             OP_PARAM_STRING_SET("variant", "generic")
        )
    );

    // processor semihost library
    
    const char *or1kNewlib_0_expath = opVLNVString(
        0, // use the default VLNV path
        0,
        0,
        "or1kNewlib",
        0,
        OP_EXTENSION,
        OP_VLNV_FATAL
    );

    opProcessorExtensionNew(
        cpu1_c,
        or1kNewlib_0_expath,
        "or1kNewlib_0",
        0
    );

    // Memory ram1

    opMemoryNew(
        mi,
        "ram1",
        OP_PRIV_RWX,
        (0x0fffffff) - (0x0),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(mainBus_b, "sp1", .slave=1, .addrLo=0x0, .addrHi=0x0fffffff)
            )
        ),
        0
    );

    // Memory ram2

    opMemoryNew(
        mi,
        "ram2",
        OP_PRIV_RWX,
        (0xffffffff) - (0x20000000),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(mainBus_b, "sp1", .slave=1, .addrLo=0x20000000, .addrHi=0xffffffff)
            )
        ),
        0
    );

    // peripheral periph0

    const char *periph0_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisUART",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_FATAL
    );

    opPeripheralNew(
        mi,
        periph0_path,
        "periph0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(mainBus_b, "bport1", .slave=1, .addrLo=0x100003f8, .addrHi=0x100013f7)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(directWrite_n, "DirectWrite"),
                OP_NET_CONNECT(directRead_n, "DirectRead")
            )
        ),
        OP_PARAMS(
             OP_PARAM_STRING_SET("outfile", "uartTTY0.log")
        )
    );
}

optModuleAttr modelAttrs = {
    .versionString        = OP_VERSION,
    .type                 = OP_MODULE,
    .name                 = MODULE_NAME,
    .releaseStatus        = OP_UNSET,
    .purpose              = OP_PP_BAREMETAL,
    .visibility           = OP_VISIBLE,
    .constructCB          = moduleConstructor,
};

/*

For information, this is what the iGen input script would look like.

ihwnew -name simpleCpuMemoryUart

ihwaddbus -instancename mainBus -addresswidth 32

ihwaddnet -instancename directWrite
ihwaddnet -instancename directRead

ihwaddprocessor -instancename cpu1 -vendor ovpworld.org -library processor -type or1k -version 1.0 -semihostname or1kNewlib -variant generic
ihwconnect -bus mainBus -instancename cpu1 -busmasterport INSTRUCTION
ihwconnect -bus mainBus -instancename cpu1 -busmasterport DATA

ihwaddmemory -instancename ram1 -type ram
ihwconnect -bus mainBus -instancename ram1 -busslaveport sp1 -loaddress 0x0 -hiaddress 0x0fffffff

ihwaddmemory -instancename ram2 -type ram
ihwconnect -bus mainBus -instancename ram2 -busslaveport sp1 -loaddress 0x20000000 -hiaddress 0xffffffff

ihwaddperipheral -instancename periph0 -vendor freescale.ovpworld.org -library peripheral -version 1.0 -type KinetisUART
ihwsetparameter    -handle periph0 -name         outfile     -value uartTTY0.log
ihwconnect -instancename periph0 -busslaveport bport1      -bus mainBus         -loaddress 0x100003f8 -hiaddress 0x100013f7
ihwconnect -instancename periph0 -netport      DirectWrite -net directWrite 
ihwconnect -instancename periph0 -netport      DirectRead  -net directRead 
*/

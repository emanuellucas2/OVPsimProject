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
    opDocTextAdd(doc_11_node, "Example platform with riscv processor with custom FIFO extensions communicating with a peripheral using FIFOs.\nThe processor's output FIFO port is connected to the input FIFO port of the peripheral and vice versa.");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "None.");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "No Reference, created as an example");


    // Bus mainBus

    optBusP mainBus_b = opBusNew(mi, "mainBus", 32, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    FIFOS
////////////////////////////////////////////////////////////////////////////////
    optFIFOP fifo01_fifo = opFIFONew(mi, "fifo01", 16, 0, 0);

    optFIFOP fifo10_fifo = opFIFONew(mi, "fifo10", 16, 0, 0);


    // Processor proc

    const char *proc_path = opVLNVString(
        0, // use the default VLNV path
        "vendor.com",
        "processor",
        "riscv",
        0,
        OP_PROCESSOR,
        OP_VLNV_PRINT
    );

    opProcessorNew(
        mi,
        proc_path,
        "proc",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(mainBus_b, "INSTRUCTION"),
                OP_BUS_CONNECT(mainBus_b, "DATA")
            ),
            OP_FIFO_CONNECTIONS(
                OP_FIFO_CONNECT(fifo01_fifo, "fifoPortOut"),
                OP_FIFO_CONNECT(fifo10_fifo, "fifoPortIn")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("defaultsemihost", 1)
            ,OP_PARAM_ENUM_SET("variant", "RV32X")
        )
    );


    // Memory ram

    opMemoryNew(
        mi,
        "ram",
        OP_PRIV_RWX,
        (0xffffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(mainBus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0xffffffffULL)
            )
        ),
        0
    );

    // PSE periph

    const char *periph_path = opVLNVString(
        0, // use the default VLNV path
        "vendor.com",
        0,
        "fifo",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        periph_path,
        "periph",
        OP_CONNECTIONS(
            OP_FIFO_CONNECTIONS(
                OP_FIFO_CONNECT(fifo01_fifo, "fifoPortIn"),
                OP_FIFO_CONNECT(fifo10_fifo, "fifoPortOut")
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
        .vendor  = "vendor.com",
        .library = "module",
        .name    = "dualFifo",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

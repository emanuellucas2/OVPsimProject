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
    opDocTextAdd(doc_11_node, "This module implements a system containing two sub-systems  \n1) ARM FMv1 Cortex-A53MPx5 running Linux, and  2) Cortex-M3 running FreeRTOS.  The two sub-systems are connected by a shared memory.");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "None");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "ARM DUI 0677C and www.freertos.org");


    // Bus sharedBus

    optBusP sharedBus_b = opBusNew(mi, "sharedBus", 32, 0, 0);


    // Module Instance ARMv8-A-FMv1

    const char *ARMv8_A_FMv1_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        "module",
        "ARMv8-A-FMv1",
        "1.0",
        OP_MODULE,
        OP_VLNV_PRINT
    );

    opModuleNew(
        mi,       // parent module
        ARMv8_A_FMv1_path,       // modelfile
        "ARMv8-A-FMv1",   // name
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(sharedBus_b, "pBusP")
            )
        ),
        0
    );

    // Module Instance ArmCortexMFreeRTOS

    const char *ArmCortexMFreeRTOS_path = opVLNVString(
        0, // use the default VLNV path
        "imperas.ovpworld.org",
        "module",
        "ArmCortexMFreeRTOS",
        "1.0",
        OP_MODULE,
        OP_VLNV_PRINT
    );

    opModuleNew(
        mi,       // parent module
        ArmCortexMFreeRTOS_path,       // modelfile
        "ArmCortexMFreeRTOS",   // name
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(sharedBus_b, "pBusP")
            )
        ),
        0
    );

    // Memory sharedMemory

    opMemoryNew(
        mi,
        "sharedMemory",
        OP_PRIV_RWX,
        (0xfffbULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(sharedBus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0xfffbULL)
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
    .purpose              = OP_PP_MODULE,
    .visibility           = OP_VISIBLE,
    .vlnv          = {
        .vendor  = "imperas.ovpworld.org",
        .library = "module",
        .name    = "Hetero_ARMv8-A-FMv1_Cortex-M3",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

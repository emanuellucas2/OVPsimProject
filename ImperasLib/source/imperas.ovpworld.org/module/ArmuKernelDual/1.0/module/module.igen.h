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
    opDocTextAdd(doc_11_node, "\n        This platform instantiates two modules for an ARM Cortex-A9MPx4 to execute the SMP UKernel\n        (ARM MPCore Boot and Synchronization Example Code)");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "BareMetal platform for execution of ARM binary uKernel file");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "http://www.arm.com/products/processors/cortex-a/arm-mpcore-sample-code.php");


    // Module Instance sys0

    const char *sys0_path = opVLNVString(
        0, // use the default VLNV path
        "imperas.ovpworld.org",
        "module",
        "ArmuKernel",
        "1.0",
        OP_MODULE,
        OP_VLNV_PRINT
    );

    opModuleNew(
        mi,       // parent module
        sys0_path,       // modelfile
        "sys0",   // name
        0,
        OP_PARAMS(
             OP_PARAM_STRING_SET("uart1logname", "uart0_1.log")
        )
    );

    // Module Instance sys1

    const char *sys1_path = opVLNVString(
        0, // use the default VLNV path
        "imperas.ovpworld.org",
        "module",
        "ArmuKernel",
        "1.0",
        OP_MODULE,
        OP_VLNV_PRINT
    );

    opModuleNew(
        mi,       // parent module
        sys1_path,       // modelfile
        "sys1",   // name
        0,
        OP_PARAMS(
             OP_PARAM_STRING_SET("uart1logname", "uart1_1.log")
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
        .vendor  = "imperas.ovpworld.org",
        .library = "module",
        .name    = "ArmuKernelDual",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

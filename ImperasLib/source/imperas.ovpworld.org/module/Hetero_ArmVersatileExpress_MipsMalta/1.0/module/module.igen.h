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
    opDocTextAdd(doc_11_node, "This platform instances an ARM VersatileExpress with a MIPS Malta");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "Peripherals are modeled to the extent required to boot and run Operating Systems such as Linux.");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "ARM Development Boards Versatile Express BaseBoard and ARM CoreTile Express A15x2 \n\t MIPS Malta User's Manual MD00048-2B-MALTA-USM-1.07.pdf\n\t MIPS Malta-R Development Platform User's Manual MD00627-2B-MALTA_R-USM-01.01.pdf    \n\t CoreFPGA User's Manual MD00116-2B-COREFPGA-USM-01.00.pdf\n\t Linux for the MIPS Malta Development Platform User's Guide MD00646-2B-LINUXMALTA-USM-01.03.pdf");


    // Module Instance versatileexpress

    const char *versatileexpress_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        "module",
        "ArmVersatileExpress-CA15",
        "1.0",
        OP_MODULE,
        OP_VLNV_PRINT
    );

    opModuleNew(
        mi,       // parent module
        versatileexpress_path,       // modelfile
        "versatileexpress",   // name
        0,
        0
    );

    // Module Instance malta

    const char *malta_path = opVLNVString(
        0, // use the default VLNV path
        "mips.ovpworld.org",
        "module",
        "MipsMalta",
        "1.0",
        OP_MODULE,
        OP_VLNV_PRINT
    );

    opModuleNew(
        mi,       // parent module
        malta_path,       // modelfile
        "malta",   // name
        0,
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
        .name    = "Hetero_ArmVersatileExpress_MipsMalta",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

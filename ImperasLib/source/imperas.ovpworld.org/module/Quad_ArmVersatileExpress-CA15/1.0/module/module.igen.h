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
    opDocTextAdd(doc_11_node, "\nThis defines the hardware that includes four instantiations of the ARM Versatile Express development board with a CoreTile Express A15x2 (V2P-CA15) Daughterboard.\nSee the ARM documents DUI0447G_v2m_p1_trm.pdf and DUI0604E_v2p_ca15_tc1_trm.pdf for details of the hardware being modeled. \nNote this platform implements the motherboard's 'Cortex-A Series' memory map.\n\nThe default processor is an ARM Cortex-A15MPx2, which may be changed.\n");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "\nThis platform provides the peripherals required to boot and run Operating Systems such as Linux or Android.\nSome of the peripherals are register-only, non-functional models. See the individual peripheral model documentation for details.\n\nCoreSight software debug and trace ports are not modeled.\n\nRemap option not modeled.\n\nThe CLCD does not work in Linux\n");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "ARM Development Boards Versatile Express BaseBoard and ARM CoreTile Express A15x2");


    // Module Instance sys0

    const char *sys0_path = opVLNVString(
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
        sys0_path,       // modelfile
        "sys0",   // name
        0,
        0
    );

    // Module Instance sys1

    const char *sys1_path = opVLNVString(
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
        sys1_path,       // modelfile
        "sys1",   // name
        0,
        0
    );

    // Module Instance sys2

    const char *sys2_path = opVLNVString(
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
        sys2_path,       // modelfile
        "sys2",   // name
        0,
        0
    );

    // Module Instance sys3

    const char *sys3_path = opVLNVString(
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
        sys3_path,       // modelfile
        "sys3",   // name
        0,
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
        .name    = "Quad_ArmVersatileExpress-CA15",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

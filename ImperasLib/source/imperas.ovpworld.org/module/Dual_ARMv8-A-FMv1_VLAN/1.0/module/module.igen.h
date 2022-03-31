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
    opDocTextAdd(doc_11_node, "This module implements a platform containing dual ARMv8-A-FMv1 modules connected using a Virtual LAN.");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "none known");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "none");


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////


    optPacketnetP phyEthernet_pkn = opPacketnetNew(mi, "phyEthernet", 0, 0);

    // Module Instance Sys1

    const char *Sys1_path = opVLNVString(
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
        Sys1_path,       // modelfile
        "Sys1",   // name
        OP_CONNECTIONS(
            OP_PACKETNET_CONNECTIONS(
                OP_PACKETNET_CONNECT(phyEthernet_pkn, "phyEthernetPort")
            )
        ),
        0
    );

    // Module Instance Sys2

    const char *Sys2_path = opVLNVString(
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
        Sys2_path,       // modelfile
        "Sys2",   // name
        OP_CONNECTIONS(
            OP_PACKETNET_CONNECTIONS(
                OP_PACKETNET_CONNECT(phyEthernet_pkn, "phyEthernetPort")
            )
        ),
        0
    );

    // PSE lanBridge

    const char *lanBridge_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        "peripheral",
        "vEthernet_Bridge",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        lanBridge_path,
        "lanBridge",
        OP_CONNECTIONS(
            OP_PACKETNET_CONNECTIONS(
                OP_PACKETNET_CONNECT(phyEthernet_pkn, "phyBridge")
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
        .name    = "Dual_ARMv8-A-FMv1_VLAN",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

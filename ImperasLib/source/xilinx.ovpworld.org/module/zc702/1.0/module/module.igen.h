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
    opDocTextAdd(doc_11_node, "This module implements the Zynq zc702 Evaluation Board.\n          This module provides the board level definition and the instantiation of a Zynq and memory.");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "Currently this module is not used. It instances the Zynq module only.");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "ZC702 Board user Guide UG850 (v1.5) September 4,2015 (ug850-zc702-eval-bd.pdf) and \nZynq-7000 AP SoC Technical Reference Manual UG585 (v1.10) February 23, 2015 (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)");
    // Variables indicating when parameters are set

    // Variables holding parameter values
    UNUSED const char * configfile               = opObjectParamStringValue(mi, "configfile");


    // Bus i2cBus

    optBusP i2cBus_b = opBusNew(mi, "i2cBus", 16, 0, 0);


    // Module Instance Zynq

    const char *Zynq_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "module",
        "Zynq",
        "1.0",
        OP_MODULE,
        OP_VLNV_PRINT
    );

    opModuleNew(
        mi,       // parent module
        Zynq_path,       // modelfile
        "Zynq",   // name
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(i2cBus_b, "extPortI2C")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("psclock", 33)
            ,OP_PARAM_UNS32_SET("armmips", 500)
            ,OP_PARAM_STRING_SET("board", "zc702")
        )
    );

    // PSE pmbus1

    const char *pmbus1_path = opVLNVString(
        0, // use the default VLNV path
        "ti.ovpworld.org",
        0,
        "ucd9248",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        pmbus1_path,
        "pmbus1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(i2cBus_b, "iic", .slave=1, .addrLo=0x734ULL, .addrHi=0x734ULL)
            )
        ),
        0
    );

    // PSE pmbus2

    const char *pmbus2_path = opVLNVString(
        0, // use the default VLNV path
        "ti.ovpworld.org",
        0,
        "ucd9248",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        pmbus2_path,
        "pmbus2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(i2cBus_b, "iic", .slave=1, .addrLo=0x735ULL, .addrHi=0x735ULL)
            )
        ),
        0
    );

    // PSE pmbus3

    const char *pmbus3_path = opVLNVString(
        0, // use the default VLNV path
        "ti.ovpworld.org",
        0,
        "ucd9248",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        pmbus3_path,
        "pmbus3",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(i2cBus_b, "iic", .slave=1, .addrLo=0x736ULL, .addrHi=0x736ULL)
            )
        ),
        0
    );

}

static optParamSpec paramSpecs[] = {
    {
        .name        = "configfile",
        .type        = OP_PARAM_STRING,
        .description = "Formal parameter configfile provides the configuration file for LED and Switch usage",
    },
    OP_HTTP_VIS_PORT_FORMALS,
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
        .vendor  = "xilinx.ovpworld.org",
        .library = "module",
        .name    = "zc702",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
    .diagSetCB            = moduleDiagSet,
    .paramSpecsCB         = moduleParamIterator,
};

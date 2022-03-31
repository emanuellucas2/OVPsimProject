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
    opDocTextAdd(doc_11_node, "This module implements the Zynq 7000");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "This module provides the instantiation of a Processing Sub-system (Zynq_PS) module and a Programmable Logic (Zynq_PL) module.");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "Zynq-7000 AP SoC Technical Reference Manual UG585 (v1.10) February 23, 2015 (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)");
    // Variables indicating when parameters are set
    Bool psclock_isSet            = 0;
    Bool armmips_isSet            = 0;

    // Variables holding parameter values
    UNUSED Uns32        psclock                  = opObjectParamUns32Value(mi, "psclock", &psclock_isSet);
    UNUSED Uns32        armmips                  = opObjectParamUns32Value(mi, "armmips", &armmips_isSet);
    UNUSED const char * board                    = opObjectParamStringValue(mi, "board");
    UNUSED const char * flashtype                = opObjectParamStringValue(mi, "flashtype");
    UNUSED const char * plmoduletype             = opObjectParamStringValue(mi, "plmoduletype");
    UNUSED const char * plmodulevendor           = opObjectParamStringValue(mi, "plmodulevendor");


    // Bus i2cBus

    optBusP i2cBus_b = opBusNew(mi, "i2cBus", 16, "extPortI2C", 0);


    // Bus icBus

    optBusP icBus_b = opBusNew(mi, "icBus", 32, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP xadcmux_n = opNetNew(mi, "xadcmux", "extPortXADCMux", 0);
    optNetP gpio_bank0_in_n = opNetNew(mi, "gpio_bank0_in", "gpio_bank0_inP", 0);
    optNetP gpio_bank0_out_n = opNetNew(mi, "gpio_bank0_out", "gpio_bank0_outP", 0);
    optNetP gpio_bank1_in_n = opNetNew(mi, "gpio_bank1_in", "gpio_bank1_inP", 0);
    optNetP gpio_bank1_out_n = opNetNew(mi, "gpio_bank1_out", "gpio_bank1_outP", 0);
    optNetP gpio_bank2_in_n = opNetNew(mi, "gpio_bank2_in", 0, 0);
    optNetP gpio_bank2_out_n = opNetNew(mi, "gpio_bank2_out", 0, 0);
    optNetP gpio_bank2_oen_out_n = opNetNew(mi, "gpio_bank2_oen_out", 0, 0);
    optNetP gpio_bank3_in_n = opNetNew(mi, "gpio_bank3_in", 0, 0);
    optNetP gpio_bank3_out_n = opNetNew(mi, "gpio_bank3_out", 0, 0);
    optNetP gpio_bank3_oen_out_n = opNetNew(mi, "gpio_bank3_oen_out", 0, 0);
    optNetP irqf2p0_n = opNetNew(mi, "irqf2p0", 0, 0);
    optNetP irqf2p1_n = opNetNew(mi, "irqf2p1", 0, 0);
    optNetP irqf2p2_n = opNetNew(mi, "irqf2p2", 0, 0);
    optNetP irqf2p3_n = opNetNew(mi, "irqf2p3", 0, 0);
    optNetP irqf2p4_n = opNetNew(mi, "irqf2p4", 0, 0);
    optNetP irqf2p5_n = opNetNew(mi, "irqf2p5", 0, 0);
    optNetP irqf2p6_n = opNetNew(mi, "irqf2p6", 0, 0);
    optNetP irqf2p7_n = opNetNew(mi, "irqf2p7", 0, 0);
    optNetP irqf2p8_n = opNetNew(mi, "irqf2p8", 0, 0);
    optNetP irqf2p9_n = opNetNew(mi, "irqf2p9", 0, 0);
    optNetP irqf2p10_n = opNetNew(mi, "irqf2p10", 0, 0);
    optNetP irqf2p11_n = opNetNew(mi, "irqf2p11", 0, 0);
    optNetP irqf2p12_n = opNetNew(mi, "irqf2p12", 0, 0);
    optNetP irqf2p13_n = opNetNew(mi, "irqf2p13", 0, 0);
    optNetP irqf2p14_n = opNetNew(mi, "irqf2p14", 0, 0);
    optNetP irqf2p15_n = opNetNew(mi, "irqf2p15", 0, 0);
    optNetP irqf2p16_n = opNetNew(mi, "irqf2p16", 0, 0);
    optNetP irqf2p17_n = opNetNew(mi, "irqf2p17", 0, 0);
    optNetP irqf2p18_n = opNetNew(mi, "irqf2p18", 0, 0);
    optNetP irqf2p19_n = opNetNew(mi, "irqf2p19", 0, 0);
    optNetP irqp2f0_n = opNetNew(mi, "irqp2f0", 0, 0);
    optNetP irqp2f1_n = opNetNew(mi, "irqp2f1", 0, 0);
    optNetP irqp2f2_n = opNetNew(mi, "irqp2f2", 0, 0);
    optNetP irqp2f3_n = opNetNew(mi, "irqp2f3", 0, 0);
    optNetP irqp2f4_n = opNetNew(mi, "irqp2f4", 0, 0);
    optNetP irqp2f5_n = opNetNew(mi, "irqp2f5", 0, 0);
    optNetP irqp2f6_n = opNetNew(mi, "irqp2f6", 0, 0);
    optNetP irqp2f7_n = opNetNew(mi, "irqp2f7", 0, 0);
    optNetP irqp2f8_n = opNetNew(mi, "irqp2f8", 0, 0);
    optNetP irqp2f9_n = opNetNew(mi, "irqp2f9", 0, 0);
    optNetP irqp2f10_n = opNetNew(mi, "irqp2f10", 0, 0);
    optNetP irqp2f11_n = opNetNew(mi, "irqp2f11", 0, 0);
    optNetP irqp2f12_n = opNetNew(mi, "irqp2f12", 0, 0);
    optNetP irqp2f13_n = opNetNew(mi, "irqp2f13", 0, 0);
    optNetP irqp2f14_n = opNetNew(mi, "irqp2f14", 0, 0);
    optNetP irqp2f15_n = opNetNew(mi, "irqp2f15", 0, 0);
    optNetP irqp2f16_n = opNetNew(mi, "irqp2f16", 0, 0);
    optNetP irqp2f17_n = opNetNew(mi, "irqp2f17", 0, 0);
    optNetP irqp2f18_n = opNetNew(mi, "irqp2f18", 0, 0);
    optNetP irqp2f19_n = opNetNew(mi, "irqp2f19", 0, 0);
    optNetP irqp2f20_n = opNetNew(mi, "irqp2f20", 0, 0);
    optNetP irqp2f21_n = opNetNew(mi, "irqp2f21", 0, 0);
    optNetP irqp2f22_n = opNetNew(mi, "irqp2f22", 0, 0);
    optNetP irqp2f23_n = opNetNew(mi, "irqp2f23", 0, 0);
    optNetP irqp2f24_n = opNetNew(mi, "irqp2f24", 0, 0);
    optNetP irqp2f25_n = opNetNew(mi, "irqp2f25", 0, 0);
    optNetP irqp2f26_n = opNetNew(mi, "irqp2f26", 0, 0);
    optNetP irqp2f27_n = opNetNew(mi, "irqp2f27", 0, 0);
    optNetP irqp2f28_n = opNetNew(mi, "irqp2f28", 0, 0);

    // Module Instance Zynq_PS

    const char *Zynq_PS_path = opVLNVString(
        0, // use the default VLNV path
        "xilinx.ovpworld.org",
        "module",
        "Zynq_PS",
        "1.0",
        OP_MODULE,
        OP_VLNV_PRINT
    );

    opModuleNew(
        mi,       // parent module
        Zynq_PS_path,       // modelfile
        "Zynq_PS",   // name
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(i2cBus_b, "extPortI2C"),
                OP_BUS_CONNECT(icBus_b, "extPort")
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(xadcmux_n, "extPortXADCMux"),
                OP_NET_CONNECT(gpio_bank0_out_n, "gpio_bank0_outP"),
                OP_NET_CONNECT(gpio_bank0_in_n, "gpio_bank0_inP"),
                OP_NET_CONNECT(gpio_bank1_out_n, "gpio_bank1_outP"),
                OP_NET_CONNECT(gpio_bank1_in_n, "gpio_bank1_inP"),
                OP_NET_CONNECT(gpio_bank2_out_n, "gpio_bank2_outP"),
                OP_NET_CONNECT(gpio_bank2_oen_out_n, "gpio_bank2_oen_outP"),
                OP_NET_CONNECT(gpio_bank2_in_n, "gpio_bank2_inP"),
                OP_NET_CONNECT(gpio_bank3_out_n, "gpio_bank3_outP"),
                OP_NET_CONNECT(gpio_bank3_oen_out_n, "gpio_bank3_oen_outP"),
                OP_NET_CONNECT(gpio_bank3_in_n, "gpio_bank3_inP"),
                OP_NET_CONNECT(irqf2p0_n, "irqf2p0_inP"),
                OP_NET_CONNECT(irqf2p1_n, "irqf2p1_inP"),
                OP_NET_CONNECT(irqf2p2_n, "irqf2p2_inP"),
                OP_NET_CONNECT(irqf2p3_n, "irqf2p3_inP"),
                OP_NET_CONNECT(irqf2p4_n, "irqf2p4_inP"),
                OP_NET_CONNECT(irqf2p5_n, "irqf2p5_inP"),
                OP_NET_CONNECT(irqf2p6_n, "irqf2p6_inP"),
                OP_NET_CONNECT(irqf2p7_n, "irqf2p7_inP"),
                OP_NET_CONNECT(irqf2p8_n, "irqf2p8_inP"),
                OP_NET_CONNECT(irqf2p9_n, "irqf2p9_inP"),
                OP_NET_CONNECT(irqf2p10_n, "irqf2p10_inP"),
                OP_NET_CONNECT(irqf2p11_n, "irqf2p11_inP"),
                OP_NET_CONNECT(irqf2p12_n, "irqf2p12_inP"),
                OP_NET_CONNECT(irqf2p13_n, "irqf2p13_inP"),
                OP_NET_CONNECT(irqf2p14_n, "irqf2p14_inP"),
                OP_NET_CONNECT(irqf2p15_n, "irqf2p15_inP"),
                OP_NET_CONNECT(irqf2p16_n, "irqf2p16_inP"),
                OP_NET_CONNECT(irqf2p17_n, "irqf2p17_inP"),
                OP_NET_CONNECT(irqf2p18_n, "irqf2p18_inP"),
                OP_NET_CONNECT(irqf2p19_n, "irqf2p19_inP"),
                OP_NET_CONNECT(irqp2f0_n, "irqp2f0_outP"),
                OP_NET_CONNECT(irqp2f1_n, "irqp2f1_outP"),
                OP_NET_CONNECT(irqp2f2_n, "irqp2f2_outP"),
                OP_NET_CONNECT(irqp2f3_n, "irqp2f3_outP"),
                OP_NET_CONNECT(irqp2f4_n, "irqp2f4_outP"),
                OP_NET_CONNECT(irqp2f5_n, "irqp2f5_outP"),
                OP_NET_CONNECT(irqp2f6_n, "irqp2f6_outP"),
                OP_NET_CONNECT(irqp2f7_n, "irqp2f7_outP"),
                OP_NET_CONNECT(irqp2f8_n, "irqp2f8_outP"),
                OP_NET_CONNECT(irqp2f9_n, "irqp2f9_outP"),
                OP_NET_CONNECT(irqp2f10_n, "irqp2f10_outP"),
                OP_NET_CONNECT(irqp2f11_n, "irqp2f11_outP"),
                OP_NET_CONNECT(irqp2f12_n, "irqp2f12_outP"),
                OP_NET_CONNECT(irqp2f13_n, "irqp2f13_outP"),
                OP_NET_CONNECT(irqp2f14_n, "irqp2f14_outP"),
                OP_NET_CONNECT(irqp2f15_n, "irqp2f15_outP"),
                OP_NET_CONNECT(irqp2f16_n, "irqp2f16_outP"),
                OP_NET_CONNECT(irqp2f17_n, "irqp2f17_outP"),
                OP_NET_CONNECT(irqp2f18_n, "irqp2f18_outP"),
                OP_NET_CONNECT(irqp2f19_n, "irqp2f19_outP"),
                OP_NET_CONNECT(irqp2f20_n, "irqp2f20_outP"),
                OP_NET_CONNECT(irqp2f21_n, "irqp2f21_outP"),
                OP_NET_CONNECT(irqp2f22_n, "irqp2f22_outP"),
                OP_NET_CONNECT(irqp2f23_n, "irqp2f23_outP"),
                OP_NET_CONNECT(irqp2f24_n, "irqp2f24_outP"),
                OP_NET_CONNECT(irqp2f25_n, "irqp2f25_outP"),
                OP_NET_CONNECT(irqp2f26_n, "irqp2f26_outP"),
                OP_NET_CONNECT(irqp2f27_n, "irqp2f27_outP"),
                OP_NET_CONNECT(irqp2f28_n, "irqp2f28_outP")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("psclock", psclock)
            ,OP_PARAM_UNS32_SET("armmips", armmips)
            ,OP_PARAM_STRING_SET("board", board)
            ,OP_PARAM_STRING_SET("flashtype", flashtype)
        )
    );

    // Module Instance Zynq_PL

    const char *Zynq_PL_path = opVLNVString(
        0, // use the default VLNV path
        plmodulevendor,
        "module",
        plmoduletype,
        "1.0",
        OP_MODULE,
        OP_VLNV_PRINT
    );

    opModuleNew(
        mi,       // parent module
        Zynq_PL_path,       // modelfile
        "Zynq_PL",   // name
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(icBus_b, "extPort")
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(gpio_bank2_out_n, "gpio_bank2_outP"),
                OP_NET_CONNECT(gpio_bank2_oen_out_n, "gpio_bank2_oen_outP"),
                OP_NET_CONNECT(gpio_bank2_in_n, "gpio_bank2_inP"),
                OP_NET_CONNECT(gpio_bank3_out_n, "gpio_bank3_outP"),
                OP_NET_CONNECT(gpio_bank3_oen_out_n, "gpio_bank3_oen_outP"),
                OP_NET_CONNECT(gpio_bank3_in_n, "gpio_bank3_inP"),
                OP_NET_CONNECT(irqf2p0_n, "irqf2p0_outP"),
                OP_NET_CONNECT(irqf2p1_n, "irqf2p1_outP"),
                OP_NET_CONNECT(irqf2p2_n, "irqf2p2_outP"),
                OP_NET_CONNECT(irqf2p3_n, "irqf2p3_outP"),
                OP_NET_CONNECT(irqf2p4_n, "irqf2p4_outP"),
                OP_NET_CONNECT(irqf2p5_n, "irqf2p5_outP"),
                OP_NET_CONNECT(irqf2p6_n, "irqf2p6_outP"),
                OP_NET_CONNECT(irqf2p7_n, "irqf2p7_outP"),
                OP_NET_CONNECT(irqf2p8_n, "irqf2p8_outP"),
                OP_NET_CONNECT(irqf2p9_n, "irqf2p9_outP"),
                OP_NET_CONNECT(irqf2p10_n, "irqf2p10_outP"),
                OP_NET_CONNECT(irqf2p11_n, "irqf2p11_outP"),
                OP_NET_CONNECT(irqf2p12_n, "irqf2p12_outP"),
                OP_NET_CONNECT(irqf2p13_n, "irqf2p13_outP"),
                OP_NET_CONNECT(irqf2p14_n, "irqf2p14_outP"),
                OP_NET_CONNECT(irqf2p15_n, "irqf2p15_outP"),
                OP_NET_CONNECT(irqf2p16_n, "irqf2p16_outP"),
                OP_NET_CONNECT(irqf2p17_n, "irqf2p17_outP"),
                OP_NET_CONNECT(irqf2p18_n, "irqf2p18_outP"),
                OP_NET_CONNECT(irqf2p19_n, "irqf2p19_outP"),
                OP_NET_CONNECT(irqp2f0_n, "irqp2f0_inP"),
                OP_NET_CONNECT(irqp2f1_n, "irqp2f1_inP"),
                OP_NET_CONNECT(irqp2f2_n, "irqp2f2_inP"),
                OP_NET_CONNECT(irqp2f3_n, "irqp2f3_inP"),
                OP_NET_CONNECT(irqp2f4_n, "irqp2f4_inP"),
                OP_NET_CONNECT(irqp2f5_n, "irqp2f5_inP"),
                OP_NET_CONNECT(irqp2f6_n, "irqp2f6_inP"),
                OP_NET_CONNECT(irqp2f7_n, "irqp2f7_inP"),
                OP_NET_CONNECT(irqp2f8_n, "irqp2f8_inP"),
                OP_NET_CONNECT(irqp2f9_n, "irqp2f9_inP"),
                OP_NET_CONNECT(irqp2f10_n, "irqp2f10_inP"),
                OP_NET_CONNECT(irqp2f11_n, "irqp2f11_inP"),
                OP_NET_CONNECT(irqp2f12_n, "irqp2f12_inP"),
                OP_NET_CONNECT(irqp2f13_n, "irqp2f13_inP"),
                OP_NET_CONNECT(irqp2f14_n, "irqp2f14_inP"),
                OP_NET_CONNECT(irqp2f15_n, "irqp2f15_inP"),
                OP_NET_CONNECT(irqp2f16_n, "irqp2f16_inP"),
                OP_NET_CONNECT(irqp2f17_n, "irqp2f17_inP"),
                OP_NET_CONNECT(irqp2f18_n, "irqp2f18_inP"),
                OP_NET_CONNECT(irqp2f19_n, "irqp2f19_inP"),
                OP_NET_CONNECT(irqp2f20_n, "irqp2f20_inP"),
                OP_NET_CONNECT(irqp2f21_n, "irqp2f21_inP"),
                OP_NET_CONNECT(irqp2f22_n, "irqp2f22_inP"),
                OP_NET_CONNECT(irqp2f23_n, "irqp2f23_inP"),
                OP_NET_CONNECT(irqp2f24_n, "irqp2f24_inP"),
                OP_NET_CONNECT(irqp2f25_n, "irqp2f25_inP"),
                OP_NET_CONNECT(irqp2f26_n, "irqp2f26_inP"),
                OP_NET_CONNECT(irqp2f27_n, "irqp2f27_inP"),
                OP_NET_CONNECT(irqp2f28_n, "irqp2f28_inP")
            )
        ),
        0
    );

}

static optParamSpec paramSpecs[] = {
    {
        .name        = "psclock",
        .type        = OP_PARAM_UNS32,
        .description = 0,
        .spec.uns32Spec.defaultValue = 33,
    },
    {
        .name        = "armmips",
        .type        = OP_PARAM_UNS32,
        .description = 0,
        .spec.uns32Spec.defaultValue = 500,
    },
    {
        .name        = "board",
        .type        = OP_PARAM_STRING,
        .description = 0,
    },
    {
        .name        = "flashtype",
        .type        = OP_PARAM_STRING,
        .description = 0,
    },
    {
        .name        = "plmoduletype",
        .type        = OP_PARAM_STRING,
        .description = 0,
        .spec.stringSpec.defaultValue = "Zynq_PL_Default",
    },
    {
        .name        = "plmodulevendor",
        .type        = OP_PARAM_STRING,
        .description = 0,
        .spec.stringSpec.defaultValue = "xilinx.ovpworld.org",
    },
    { 0 }
};

static OP_PARAM_SPEC_FN(moduleParamIterator) {
    prev = prev ? prev + 1 : paramSpecs; 
    return prev->name ? prev : 0;
}

static optBusPortInfo busPortSpecs[] = {
    {
        .name        = "extPortI2C",
        .description = 0,
    },
    { 0 }
};

static OP_BUS_PORT_FN(moduleBusPortIterator) {
    prev = prev ? prev + 1 : busPortSpecs; 
    return prev->name ? prev : 0;
}

static optNetPortInfo netPortSpecs[] = {
    {
        .name        = "extPortXADCMux",
        .description = 0,
    },
    {
        .name        = "gpio_bank0_outP",
        .description = 0,
    },
    {
        .name        = "gpio_bank1_outP",
        .description = 0,
    },
    {
        .name        = "gpio_bank0_inP",
        .description = 0,
    },
    {
        .name        = "gpio_bank1_inP",
        .description = 0,
    },
    { 0 }
};

static OP_NET_PORT_FN(moduleNetPortIterator) {
    prev = prev ? prev + 1 : netPortSpecs; 
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
        .name    = "Zynq",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
    .paramSpecsCB         = moduleParamIterator,
    .busPortSpecsCB       = moduleBusPortIterator,
    .netPortSpecsCB       = moduleNetPortIterator,
};

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
    opDocTextAdd(doc_11_node, "\nFreescale Kinetis K64 platform");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "\nOnly enough functionality modeled to boot MQX. Most peripherals modeled as dummy register ports\n");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "based on document number: K64P144M120SF5RM Rev. 2, Jan 2014");


    // Bus pBus

    optBusP pBus_b = opBusNew(mi, "pBus", 32, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP int45_n = opNetNew(mi, "int45", 0, 0);
    optNetP int47_n = opNetNew(mi, "int47", 0, 0);
    optNetP int49_n = opNetNew(mi, "int49", 0, 0);
    optNetP int51_n = opNetNew(mi, "int51", 0, 0);
    optNetP int53_n = opNetNew(mi, "int53", 0, 0);
    optNetP int55_n = opNetNew(mi, "int55", 0, 0);
    optNetP int59_n = opNetNew(mi, "int59", 0, 0);
    optNetP int60_n = opNetNew(mi, "int60", 0, 0);
    optNetP int61_n = opNetNew(mi, "int61", 0, 0);
    optNetP int62_n = opNetNew(mi, "int62", 0, 0);
    optNetP int63_n = opNetNew(mi, "int63", 0, 0);
    optNetP int64_n = opNetNew(mi, "int64", 0, 0);
    optNetP int68_n = opNetNew(mi, "int68", 0, 0);
    optNetP int69_n = opNetNew(mi, "int69", 0, 0);
    optNetP int70_n = opNetNew(mi, "int70", 0, 0);
    optNetP int71_n = opNetNew(mi, "int71", 0, 0);
    optNetP int98_n = opNetNew(mi, "int98", 0, 0);
    optNetP int101_n = opNetNew(mi, "int101", 0, 0);
    optNetP int0_n = opNetNew(mi, "int0", 0, 0);
    optNetP int1_n = opNetNew(mi, "int1", 0, 0);
    optNetP int2_n = opNetNew(mi, "int2", 0, 0);
    optNetP int3_n = opNetNew(mi, "int3", 0, 0);
    optNetP int4_n = opNetNew(mi, "int4", 0, 0);
    optNetP int5_n = opNetNew(mi, "int5", 0, 0);
    optNetP int6_n = opNetNew(mi, "int6", 0, 0);
    optNetP int7_n = opNetNew(mi, "int7", 0, 0);
    optNetP int8_n = opNetNew(mi, "int8", 0, 0);
    optNetP int9_n = opNetNew(mi, "int9", 0, 0);
    optNetP int10_n = opNetNew(mi, "int10", 0, 0);
    optNetP int11_n = opNetNew(mi, "int11", 0, 0);
    optNetP int12_n = opNetNew(mi, "int12", 0, 0);
    optNetP int13_n = opNetNew(mi, "int13", 0, 0);
    optNetP int14_n = opNetNew(mi, "int14", 0, 0);
    optNetP int15_n = opNetNew(mi, "int15", 0, 0);
    optNetP int16_n = opNetNew(mi, "int16", 0, 0);
    optNetP dma_eDMARequest_n = opNetNew(mi, "dma_eDMARequest", 0, 0);
    optNetP adc0_dmareq_n = opNetNew(mi, "adc0_dmareq", 0, 0);
    optNetP adc1_dmareq_n = opNetNew(mi, "adc1_dmareq", 0, 0);
    optNetP adc2_dmareq_n = opNetNew(mi, "adc2_dmareq", 0, 0);
    optNetP adc3_dmareq_n = opNetNew(mi, "adc3_dmareq", 0, 0);
    optNetP cmp0_dmareq_n = opNetNew(mi, "cmp0_dmareq", 0, 0);
    optNetP cmp1_dmareq_n = opNetNew(mi, "cmp1_dmareq", 0, 0);
    optNetP cmp2_dmareq_n = opNetNew(mi, "cmp2_dmareq", 0, 0);
    optNetP cmp3_dmareq_n = opNetNew(mi, "cmp3_dmareq", 0, 0);
    optNetP ftm0_phaseA_n = opNetNew(mi, "ftm0_phaseA", 0, 0);
    optNetP ftm0_phaseB_n = opNetNew(mi, "ftm0_phaseB", 0, 0);
    optNetP ftm1_phaseA_n = opNetNew(mi, "ftm1_phaseA", 0, 0);
    optNetP ftm1_phaseB_n = opNetNew(mi, "ftm1_phaseB", 0, 0);
    optNetP adc0_altclk_n = opNetNew(mi, "adc0_altclk", 0, 0);
    optNetP adc0_hwtrig_n = opNetNew(mi, "adc0_hwtrig", 0, 0);
    optNetP adc0_adin_n = opNetNew(mi, "adc0_adin", 0, 0);
    optNetP adc0_vrefsh_n = opNetNew(mi, "adc0_vrefsh", 0, 0);
    optNetP adc0_vrefsl_n = opNetNew(mi, "adc0_vrefsl", 0, 0);
    optNetP adc0_adinid_n = opNetNew(mi, "adc0_adinid", 0, 0);
    optNetP adc0_interrupt_n = opNetNew(mi, "adc0_interrupt", 0, 0);
    optNetP adc2_input_n = opNetNew(mi, "adc2_input", "p_adc2_input", 0);
    optNetP adc2_sample_n = opNetNew(mi, "adc2_sample", "p_adc2_sample", 0);
    optNetP adc2_trigger_n = opNetNew(mi, "adc2_trigger", "p_adc2_trigger", 0);
    optNetP uart0_tx_n = opNetNew(mi, "uart0_tx", "p_uart0_tx", 0);
    optNetP uart0_rx_n = opNetNew(mi, "uart0_rx", "p_uart0_rx", 0);
    optNetP uart1_tx_n = opNetNew(mi, "uart1_tx", "p_uart1_tx", 0);
    optNetP uart1_rx_n = opNetNew(mi, "uart1_rx", "p_uart1_rx", 0);
    optNetP uart2_tx_n = opNetNew(mi, "uart2_tx", "p_uart2_tx", 0);
    optNetP uart2_rx_n = opNetNew(mi, "uart2_rx", "p_uart2_rx", 0);
    optNetP uart3_tx_n = opNetNew(mi, "uart3_tx", "p_uart3_tx", 0);
    optNetP uart3_rx_n = opNetNew(mi, "uart3_rx", "p_uart3_rx", 0);
    optNetP cmp_vin1_n = opNetNew(mi, "cmp_vin1", "p_cmp_vin1", 0);
    optNetP cmp_vin2_n = opNetNew(mi, "cmp_vin2", "p_cmp_vin2", 0);
    optNetP cmp0_input0_n = opNetNew(mi, "cmp0_input0", "p_cmp0_input0", 0);
    optNetP cmp0_input1_n = opNetNew(mi, "cmp0_input1", "p_cmp0_input1", 0);
    optNetP cmp0_input2_n = opNetNew(mi, "cmp0_input2", "p_cmp0_input2", 0);
    optNetP cmp0_input3_n = opNetNew(mi, "cmp0_input3", "p_cmp0_input3", 0);
    optNetP cmp0_input4_n = opNetNew(mi, "cmp0_input4", "p_cmp0_input4", 0);
    optNetP cmp0_input5_n = opNetNew(mi, "cmp0_input5", "p_cmp0_input5", 0);
    optNetP cmp0_input6_n = opNetNew(mi, "cmp0_input6", "p_cmp0_input6", 0);
    optNetP cmp0_DacOutput_n = opNetNew(mi, "cmp0_DacOutput", "p_cmp0_DacOutput", 0);
    optNetP cmp0_extsample_n = opNetNew(mi, "cmp0_extsample", 0, 0);
    optNetP cmp0_coutsoc_n = opNetNew(mi, "cmp0_coutsoc", 0, 0);
    optNetP cmp0_cmpopad_n = opNetNew(mi, "cmp0_cmpopad", 0, 0);
    optNetP cmp1_input0_n = opNetNew(mi, "cmp1_input0", "p_cmp1_input0", 0);
    optNetP cmp1_input1_n = opNetNew(mi, "cmp1_input1", 0, 0);
    optNetP cmp1_input2_n = opNetNew(mi, "cmp1_input2", 0, 0);
    optNetP cmp1_input3_n = opNetNew(mi, "cmp1_input3", 0, 0);
    optNetP cmp1_input4_n = opNetNew(mi, "cmp1_input4", 0, 0);
    optNetP cmp1_input5_n = opNetNew(mi, "cmp1_input5", 0, 0);
    optNetP cmp1_input6_n = opNetNew(mi, "cmp1_input6", 0, 0);
    optNetP cmp1_DacOutput_n = opNetNew(mi, "cmp1_DacOutput", "p_cmp1_DacOutput", 0);
    optNetP cmp1_extsample_n = opNetNew(mi, "cmp1_extsample", 0, 0);
    optNetP cmp1_coutsoc_n = opNetNew(mi, "cmp1_coutsoc", 0, 0);
    optNetP cmp1_cmpopad_n = opNetNew(mi, "cmp1_cmpopad", 0, 0);
    optNetP cmp2_input0_n = opNetNew(mi, "cmp2_input0", "p_cmp2_input0", 0);
    optNetP cmp2_input1_n = opNetNew(mi, "cmp2_input1", "p_cmp2_input1", 0);
    optNetP cmp2_input2_n = opNetNew(mi, "cmp2_input2", "p_cmp2_input2", 0);
    optNetP cmp2_input3_n = opNetNew(mi, "cmp2_input3", "p_cmp2_input3", 0);
    optNetP cmp2_input4_n = opNetNew(mi, "cmp2_input4", "p_cmp2_input4", 0);
    optNetP cmp2_input5_n = opNetNew(mi, "cmp2_input5", "p_cmp2_input5", 0);
    optNetP cmp2_input6_n = opNetNew(mi, "cmp2_input6", "p_cmp2_input6", 0);
    optNetP cmp2_DacOutput_n = opNetNew(mi, "cmp2_DacOutput", "p_cmp2_DacOutput", 0);
    optNetP cmp2_extsample_n = opNetNew(mi, "cmp2_extsample", 0, 0);
    optNetP cmp2_coutsoc_n = opNetNew(mi, "cmp2_coutsoc", 0, 0);
    optNetP cmp2_cmpopad_n = opNetNew(mi, "cmp2_cmpopad", 0, 0);
    optNetP cmp3_input0_n = opNetNew(mi, "cmp3_input0", "p_cmp3_input0", 0);
    optNetP cmp3_input1_n = opNetNew(mi, "cmp3_input1", "p_cmp3_input1", 0);
    optNetP cmp3_input2_n = opNetNew(mi, "cmp3_input2", "p_cmp3_input2", 0);
    optNetP cmp3_input3_n = opNetNew(mi, "cmp3_input3", "p_cmp3_input3", 0);
    optNetP cmp3_input4_n = opNetNew(mi, "cmp3_input4", "p_cmp3_input4", 0);
    optNetP cmp3_input5_n = opNetNew(mi, "cmp3_input5", "p_cmp3_input5", 0);
    optNetP cmp3_input6_n = opNetNew(mi, "cmp3_input6", "p_cmp3_input6", 0);
    optNetP cmp3_DacOutput_n = opNetNew(mi, "cmp3_DacOutput", "p_cmp3_DacOutput", 0);
    optNetP cmp3_extsample_n = opNetNew(mi, "cmp3_extsample", 0, 0);
    optNetP cmp3_coutsoc_n = opNetNew(mi, "cmp3_coutsoc", 0, 0);
    optNetP cmp3_cmpopad_n = opNetNew(mi, "cmp3_cmpopad", 0, 0);
    optNetP ftm2_phaseA_n = opNetNew(mi, "ftm2_phaseA", 0, 0);
    optNetP ftm2_phaseB_n = opNetNew(mi, "ftm2_phaseB", 0, 0);
    optNetP ftm3_phaseA_n = opNetNew(mi, "ftm3_phaseA", 0, 0);
    optNetP ftm3_phaseB_n = opNetNew(mi, "ftm3_phaseB", 0, 0);
    optNetP adc1_input_n = opNetNew(mi, "adc1_input", "p_adc1_input", 0);
    optNetP adc1_sample_n = opNetNew(mi, "adc1_sample", "p_adc1_sample", 0);
    optNetP adc1_trigger_n = opNetNew(mi, "adc1_trigger", "p_adc1_trigger", 0);
    optNetP adc3_input_n = opNetNew(mi, "adc3_input", "p_adc3_input", 0);
    optNetP adc3_sample_n = opNetNew(mi, "adc3_sample", "p_adc3_sample", 0);
    optNetP adc3_trigger_n = opNetNew(mi, "adc3_trigger", "p_adc3_trigger", 0);
    optNetP uart4_tx_n = opNetNew(mi, "uart4_tx", "p_uart4_tx", 0);
    optNetP uart4_rx_n = opNetNew(mi, "uart4_rx", "p_uart4_rx", 0);
    optNetP uart5_tx_n = opNetNew(mi, "uart5_tx", "p_uart5_tx", 0);
    optNetP uart5_rx_n = opNetNew(mi, "uart5_rx", "p_uart5_rx", 0);
    optNetP gpioA_in_n = opNetNew(mi, "gpioA_in", "p_gpioA_in", 0);
    optNetP gpioA_out_n = opNetNew(mi, "gpioA_out", "p_gpioA_out", 0);
    optNetP gpioA_mask_n = opNetNew(mi, "gpioA_mask", "p_gpioA_mask", 0);
    optNetP gpioB_in_n = opNetNew(mi, "gpioB_in", "p_gpioB_in", 0);
    optNetP gpioB_out_n = opNetNew(mi, "gpioB_out", "p_gpioB_out", 0);
    optNetP gpioB_mask_n = opNetNew(mi, "gpioB_mask", "p_gpioB_mask", 0);
    optNetP gpioC_in_n = opNetNew(mi, "gpioC_in", "p_gpioC_in", 0);
    optNetP gpioC_out_n = opNetNew(mi, "gpioC_out", "p_gpioC_out", 0);
    optNetP gpioC_mask_n = opNetNew(mi, "gpioC_mask", "p_gpioC_mask", 0);
    optNetP gpioD_in_n = opNetNew(mi, "gpioD_in", "p_gpioD_in", 0);
    optNetP gpioD_out_n = opNetNew(mi, "gpioD_out", "p_gpioD_out", 0);
    optNetP gpioD_mask_n = opNetNew(mi, "gpioD_mask", "p_gpioD_mask", 0);
    optNetP gpioE_in_n = opNetNew(mi, "gpioE_in", "p_gpioE_in", 0);
    optNetP gpioE_out_n = opNetNew(mi, "gpioE_out", "p_gpioE_out", 0);
    optNetP gpioE_mask_n = opNetNew(mi, "gpioE_mask", "p_gpioE_mask", 0);
    optNetP gpioF_in_n = opNetNew(mi, "gpioF_in", "p_gpioF_in", 0);
    optNetP gpioF_out_n = opNetNew(mi, "gpioF_out", "p_gpioF_out", 0);
    optNetP gpioF_mask_n = opNetNew(mi, "gpioF_mask", "p_gpioF_mask", 0);
    opNetNew(mi, "cmp_ext_sample", "p_cmp_ext_sample", 0);
    opNetNew(mi, "cmp_coutSoc", "p_cmp_coutSoc", 0);
    opNetNew(mi, "cmp_OPad", "p_cmp_OPad", 0);
    opNetNew(mi, "cmp1input1", "p_cmp1_input1", 0);
    opNetNew(mi, "cmp1input2", "p_cmp1_input2", 0);
    opNetNew(mi, "cmp1input3", "p_cmp1_input3", 0);
    opNetNew(mi, "cmp1input4", "p_cmp1_input4", 0);
    opNetNew(mi, "cmp1input5", "p_cmp1_input5", 0);
    opNetNew(mi, "cmp1input6", "p_cmp1_input6", 0);
    opNetNew(mi, "adc0_input", "p_adc0_input", 0);
    opNetNew(mi, "adc0_sample", "p_adc0_sample", 0);
    opNetNew(mi, "adc0_trigger", "p_adc0_trigger", 0);
    opNetNew(mi, "dac0_output", "p_dac0_output", 0);
    opNetNew(mi, "dac1_output", "p_dac1_output", 0);
    opNetNew(mi, "ftm_input", "p_ftm_input", 0);
    opNetNew(mi, "ftm_output", "p_ftm_output", 0);
    opNetNew(mi, "ftm_mask", "p_ftm_mask", 0);
    opNetNew(mi, "ftm_fault", "p_ftm_fault", 0);
    opNetNew(mi, "ftm_phaseA", "p_ftm_phaseA", 0);
    opNetNew(mi, "ftm_phaseB", "p_ftm_phaseB", 0);
    opNetNew(mi, "can0_tx", "p_can0_tx", 0);
    opNetNew(mi, "can0_rx", "p_can0_rx", 0);
    opNetNew(mi, "can1_tx", "p_can1_tx", 0);
    opNetNew(mi, "can1_rx", "p_can1_rx", 0);
    opNetNew(mi, "spi0_tx", "p_spi0_tx", 0);
    opNetNew(mi, "spi0_rx", "p_spi0_rx", 0);
    opNetNew(mi, "spi1_tx", "p_spi1_tx", 0);
    opNetNew(mi, "spi1_rx", "p_spi1_rx", 0);
    opNetNew(mi, "spi2_tx", "p_spi2_tx", 0);
    opNetNew(mi, "spi2_rx", "p_spi2_rx", 0);
    opNetNew(mi, "i2c0_tx", "p_i2c0_tx", 0);
    opNetNew(mi, "i2c0_rx", "p_i2c0_rx", 0);
    opNetNew(mi, "i2c1_tx", "p_i2c1_tx", 0);
    opNetNew(mi, "i2c1_rx", "p_i2c1_rx", 0);
    opNetNew(mi, "i2s0_tx", "p_i2s0_tx", 0);
    opNetNew(mi, "i2s0_rx", "p_i2s0_rx", 0);
    opNetNew(mi, "i2s1_tx", "p_i2s1_tx", 0);
    opNetNew(mi, "i2s1_rx", "p_i2s1_rx", 0);

    // Processor cpu

    const char *cpu_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "armm",
        "1.0",
        OP_PROCESSOR,
        OP_VLNV_PRINT
    );

    opProcessorNew(
        mi,
        cpu_path,
        "cpu",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "INSTRUCTION"),
                OP_BUS_CONNECT(pBus_b, "DATA")
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(int45_n, "int45"),
                OP_NET_CONNECT(int47_n, "int47"),
                OP_NET_CONNECT(int49_n, "int49"),
                OP_NET_CONNECT(int51_n, "int51"),
                OP_NET_CONNECT(int53_n, "int53"),
                OP_NET_CONNECT(int55_n, "int55"),
                OP_NET_CONNECT(int59_n, "int59"),
                OP_NET_CONNECT(int60_n, "int60"),
                OP_NET_CONNECT(int61_n, "int61"),
                OP_NET_CONNECT(int62_n, "int62"),
                OP_NET_CONNECT(int63_n, "int63"),
                OP_NET_CONNECT(int64_n, "int64"),
                OP_NET_CONNECT(int68_n, "int68"),
                OP_NET_CONNECT(int69_n, "int69"),
                OP_NET_CONNECT(int70_n, "int70"),
                OP_NET_CONNECT(int71_n, "int71"),
                OP_NET_CONNECT(int98_n, "int98"),
                OP_NET_CONNECT(int101_n, "int101"),
                OP_NET_CONNECT(int0_n, "int0"),
                OP_NET_CONNECT(int1_n, "int1"),
                OP_NET_CONNECT(int2_n, "int2"),
                OP_NET_CONNECT(int3_n, "int3"),
                OP_NET_CONNECT(int4_n, "int4"),
                OP_NET_CONNECT(int5_n, "int5"),
                OP_NET_CONNECT(int6_n, "int6"),
                OP_NET_CONNECT(int7_n, "int7"),
                OP_NET_CONNECT(int8_n, "int8"),
                OP_NET_CONNECT(int9_n, "int9"),
                OP_NET_CONNECT(int10_n, "int10"),
                OP_NET_CONNECT(int11_n, "int11"),
                OP_NET_CONNECT(int12_n, "int12"),
                OP_NET_CONNECT(int13_n, "int13"),
                OP_NET_CONNECT(int14_n, "int14"),
                OP_NET_CONNECT(int15_n, "int15"),
                OP_NET_CONNECT(int16_n, "int16")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_DOUBLE_SET("mips", 120)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_STRING_SET("variant", "Cortex-M4F")
            ,OP_PARAM_BOOL_SET("UAL", 1)
            ,OP_PARAM_UNS32_SET("override_priorityBits", 4)
            ,OP_PARAM_UNS32_SET("override_numInterrupts", 105)
        )
    );


    // Memory flash

    opMemoryNew(
        mi,
        "flash",
        OP_PRIV_RWX,
        (0xffffffULL) - (0x0ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x0ULL, .addrHi=0xffffffULL)
            )
        ),
        0
    );

    // Memory sram

    opMemoryNew(
        mi,
        "sram",
        OP_PRIV_RWX,
        (0x2000ffffULL) - (0x1fff0000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x1fff0000ULL, .addrHi=0x2000ffffULL)
            )
        ),
        0
    );

    // PSE aips0

    const char *aips0_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisAIPS",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        aips0_path,
        "aips0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40000000ULL, .addrHi=0x40000fffULL)
            )
        ),
        0
    );

    // PSE axbs

    const char *axbs_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisAXBS",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        axbs_path,
        "axbs",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40004000ULL, .addrHi=0x40004fffULL)
            )
        ),
        0
    );

    // PSE dmac

    const char *dmac_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisDMA",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        dmac_path,
        "dmac",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "MREAD", .addrLo=0x0ULL, .addrHi=0xffffffffULL),
                OP_BUS_CONNECT(pBus_b, "MWRITE", .addrLo=0x0ULL, .addrHi=0xffffffffULL),
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40008000ULL, .addrHi=0x40009fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(dma_eDMARequest_n, "eDMARequest"),
                OP_NET_CONNECT(int16_n, "errorInterrupt"),
                OP_NET_CONNECT(int0_n, "dmaInterrupt_ch0"),
                OP_NET_CONNECT(int1_n, "dmaInterrupt_ch1"),
                OP_NET_CONNECT(int2_n, "dmaInterrupt_ch2"),
                OP_NET_CONNECT(int3_n, "dmaInterrupt_ch3"),
                OP_NET_CONNECT(int4_n, "dmaInterrupt_ch4"),
                OP_NET_CONNECT(int5_n, "dmaInterrupt_ch5"),
                OP_NET_CONNECT(int6_n, "dmaInterrupt_ch6"),
                OP_NET_CONNECT(int7_n, "dmaInterrupt_ch7"),
                OP_NET_CONNECT(int8_n, "dmaInterrupt_ch8"),
                OP_NET_CONNECT(int9_n, "dmaInterrupt_ch9"),
                OP_NET_CONNECT(int10_n, "dmaInterrupt_ch10"),
                OP_NET_CONNECT(int11_n, "dmaInterrupt_ch11"),
                OP_NET_CONNECT(int12_n, "dmaInterrupt_ch12"),
                OP_NET_CONNECT(int13_n, "dmaInterrupt_ch13"),
                OP_NET_CONNECT(int14_n, "dmaInterrupt_ch14"),
                OP_NET_CONNECT(int15_n, "dmaInterrupt_ch15")
            )
        ),
        0
    );

    // PSE flexbus

    const char *flexbus_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisFB",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        flexbus_path,
        "flexbus",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4000c000ULL, .addrHi=0x4000cfffULL)
            )
        ),
        0
    );

    // PSE mpu

    const char *mpu_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisMPU",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        mpu_path,
        "mpu",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4000d000ULL, .addrHi=0x4000dfffULL)
            )
        ),
        0
    );

    // PSE fmc

    const char *fmc_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisFMC",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        fmc_path,
        "fmc",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4001f000ULL, .addrHi=0x4001ffffULL)
            )
        ),
        0
    );

    // PSE dmamux0

    const char *dmamux0_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisDMAMUX",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        dmamux0_path,
        "dmamux0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40021000ULL, .addrHi=0x40021fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(dma_eDMARequest_n, "eDMARequest"),
                OP_NET_CONNECT(adc0_dmareq_n, "dmaSrc40"),
                OP_NET_CONNECT(adc1_dmareq_n, "dmaSrc41")
            )
        ),
        0
    );

    // PSE dmamux1

    const char *dmamux1_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisDMAMUX",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        dmamux1_path,
        "dmamux1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40022000ULL, .addrHi=0x40022fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(dma_eDMARequest_n, "eDMARequest"),
                OP_NET_CONNECT(adc0_dmareq_n, "dmaSrc40"),
                OP_NET_CONNECT(adc1_dmareq_n, "dmaSrc41"),
                OP_NET_CONNECT(adc2_dmareq_n, "dmaSrc42"),
                OP_NET_CONNECT(adc3_dmareq_n, "dmaSrc43"),
                OP_NET_CONNECT(cmp0_dmareq_n, "dmaSrc47"),
                OP_NET_CONNECT(cmp1_dmareq_n, "dmaSrc48"),
                OP_NET_CONNECT(cmp2_dmareq_n, "dmaSrc49"),
                OP_NET_CONNECT(cmp3_dmareq_n, "dmaSrc50")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("startDMAChannel", 16)
        )
    );

    // PSE can0

    const char *can0_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisCAN",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        can0_path,
        "can0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40024000ULL, .addrHi=0x40024fffULL)
            )
        ),
        0
    );

    // PSE spi0

    const char *spi0_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisSPI",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        spi0_path,
        "spi0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4002c000ULL, .addrHi=0x4002cfffULL)
            )
        ),
        0
    );

    // PSE spi1

    const char *spi1_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisSPI",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        spi1_path,
        "spi1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4002d000ULL, .addrHi=0x4002dfffULL)
            )
        ),
        0
    );

    // PSE i2s0

    const char *i2s0_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisI2S",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        i2s0_path,
        "i2s0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4002f000ULL, .addrHi=0x4002ffffULL)
            )
        ),
        0
    );

    // PSE crc

    const char *crc_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisCRC",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        crc_path,
        "crc",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40032000ULL, .addrHi=0x40032fffULL)
            )
        ),
        0
    );

    // PSE usbhs

    const char *usbhs_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisUSBHS",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        usbhs_path,
        "usbhs",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40034000ULL, .addrHi=0x40034fffULL)
            )
        ),
        0
    );

    // PSE usbdcd

    const char *usbdcd_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisUSBDCD",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        usbdcd_path,
        "usbdcd",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40035000ULL, .addrHi=0x40035fffULL)
            )
        ),
        0
    );

    // PSE pdb

    const char *pdb_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisPDB",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        pdb_path,
        "pdb",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40036000ULL, .addrHi=0x40036fffULL)
            )
        ),
        0
    );

    // PSE pit

    const char *pit_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisPIT",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        pit_path,
        "pit",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40037000ULL, .addrHi=0x40037fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(int68_n, "irq0"),
                OP_NET_CONNECT(int69_n, "irq1"),
                OP_NET_CONNECT(int70_n, "irq2"),
                OP_NET_CONNECT(int71_n, "irq3")
            )
        ),
        0
    );

    // PSE ftm0

    const char *ftm0_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisFTM",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ftm0_path,
        "ftm0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40038000ULL, .addrHi=0x40038fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ftm0_phaseA_n, "PhaseA"),
                OP_NET_CONNECT(ftm0_phaseB_n, "PhaseB"),
                OP_NET_CONNECT(int62_n, "Interrupt")
            )
        ),
        0
    );

    // PSE ftm1

    const char *ftm1_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisFTM",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ftm1_path,
        "ftm1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40039000ULL, .addrHi=0x40039fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ftm1_phaseA_n, "PhaseA"),
                OP_NET_CONNECT(ftm1_phaseB_n, "PhaseB"),
                OP_NET_CONNECT(int63_n, "Interrupt")
            )
        ),
        0
    );

    // PSE adc0

    const char *adc0_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisADC",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        adc0_path,
        "adc0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4003b000ULL, .addrHi=0x4003bfffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(adc0_altclk_n, "AltClk"),
                OP_NET_CONNECT(adc0_hwtrig_n, "HwTrig"),
                OP_NET_CONNECT(adc0_adin_n, "AdIn"),
                OP_NET_CONNECT(adc0_vrefsh_n, "Vrefsh"),
                OP_NET_CONNECT(adc0_vrefsl_n, "Vrefsl"),
                OP_NET_CONNECT(adc0_adinid_n, "AdInId"),
                OP_NET_CONNECT(adc0_interrupt_n, "Interrupt"),
                OP_NET_CONNECT(adc0_dmareq_n, "DmaReq")
            )
        ),
        0
    );

    // PSE adc2

    const char *adc2_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisADC",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        adc2_path,
        "adc2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4003c000ULL, .addrHi=0x4003cfffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(adc2_input_n, "AdIn"),
                OP_NET_CONNECT(adc2_sample_n, "AdInId"),
                OP_NET_CONNECT(adc2_trigger_n, "HwTrig")
            )
        ),
        0
    );

    // PSE rtc

    const char *rtc_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisRTC",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        rtc_path,
        "rtc",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4003d000ULL, .addrHi=0x4003dfffULL)
            )
        ),
        0
    );

    // PSE vbat

    const char *vbat_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisRFVBAT",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        vbat_path,
        "vbat",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4003e000ULL, .addrHi=0x4003efffULL)
            )
        ),
        0
    );

    // PSE lptmr

    const char *lptmr_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisLPTMR",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        lptmr_path,
        "lptmr",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40040000ULL, .addrHi=0x40040fffULL)
            )
        ),
        0
    );

    // PSE rfsys

    const char *rfsys_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisRFSYS",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        rfsys_path,
        "rfsys",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40041000ULL, .addrHi=0x40041fffULL)
            )
        ),
        0
    );

    // PSE tsi

    const char *tsi_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisTSI",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        tsi_path,
        "tsi",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40045000ULL, .addrHi=0x40045fffULL)
            )
        ),
        0
    );

    // PSE sim

    const char *sim_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisSIM",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        sim_path,
        "sim",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40047000ULL, .addrHi=0x40048fffULL)
            )
        ),
        0
    );

    // PSE amux

    const char *amux_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisPORT",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        amux_path,
        "amux",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40049000ULL, .addrHi=0x40049fffULL)
            )
        ),
        0
    );

    // PSE bmux

    const char *bmux_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisPORT",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        bmux_path,
        "bmux",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4004a000ULL, .addrHi=0x4004afffULL)
            )
        ),
        0
    );

    // PSE cmux

    const char *cmux_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisPORT",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        cmux_path,
        "cmux",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4004b000ULL, .addrHi=0x4004bfffULL)
            )
        ),
        0
    );

    // PSE dmux

    const char *dmux_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisPORT",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        dmux_path,
        "dmux",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4004c000ULL, .addrHi=0x4004cfffULL)
            )
        ),
        0
    );

    // PSE emux

    const char *emux_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisPORT",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        emux_path,
        "emux",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4004d000ULL, .addrHi=0x4004dfffULL)
            )
        ),
        0
    );

    // PSE fmux

    const char *fmux_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisPORT",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        fmux_path,
        "fmux",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4004e000ULL, .addrHi=0x4004efffULL)
            )
        ),
        0
    );

    // PSE wdog

    const char *wdog_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisWDOG",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        wdog_path,
        "wdog",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40052000ULL, .addrHi=0x40052fffULL)
            )
        ),
        0
    );

    // PSE ewm

    const char *ewm_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisEWM",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ewm_path,
        "ewm",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40061000ULL, .addrHi=0x40061fffULL)
            )
        ),
        0
    );

    // PSE cmt

    const char *cmt_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisCMT",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        cmt_path,
        "cmt",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40062000ULL, .addrHi=0x40062fffULL)
            )
        ),
        0
    );

    // PSE mcg

    const char *mcg_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisMCG",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        mcg_path,
        "mcg",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40064000ULL, .addrHi=0x40064fffULL)
            )
        ),
        0
    );

    // PSE osc0

    const char *osc0_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisOSC",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        osc0_path,
        "osc0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40065000ULL, .addrHi=0x40065fffULL)
            )
        ),
        0
    );

    // PSE i2c0

    const char *i2c0_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisI2C",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        i2c0_path,
        "i2c0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40066000ULL, .addrHi=0x40066fffULL)
            )
        ),
        0
    );

    // PSE i2c1

    const char *i2c1_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisI2C",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        i2c1_path,
        "i2c1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40067000ULL, .addrHi=0x40067fffULL)
            )
        ),
        0
    );

    // PSE uart0

    const char *uart0_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisUART",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart0_path,
        "uart0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4006a000ULL, .addrHi=0x4006afffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(int45_n, "Interrupt"),
                OP_NET_CONNECT(uart0_tx_n, "DirectWrite"),
                OP_NET_CONNECT(uart0_rx_n, "DirectRead")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("fifoSize", 8)
            ,OP_PARAM_UNS32_SET("moduleClkFreq", 60000000)
            ,OP_PARAM_STRING_SET("outfile", "uart0_outfile.txt")
        )
    );

    // PSE uart1

    const char *uart1_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisUART",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart1_path,
        "uart1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4006b000ULL, .addrHi=0x4006bfffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(int47_n, "Interrupt"),
                OP_NET_CONNECT(uart1_tx_n, "DirectWrite"),
                OP_NET_CONNECT(uart1_rx_n, "DirectRead")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("fifoSize", 8)
            ,OP_PARAM_UNS32_SET("moduleClkFreq", 60000000)
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
            ,OP_PARAM_STRING_SET("outfile", "uart1_outfile.txt")
        )
    );

    // PSE uart2

    const char *uart2_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisUART",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart2_path,
        "uart2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4006c000ULL, .addrHi=0x4006cfffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(int49_n, "Interrupt"),
                OP_NET_CONNECT(uart2_tx_n, "DirectWrite"),
                OP_NET_CONNECT(uart2_rx_n, "DirectRead")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("fifoSize", 1)
            ,OP_PARAM_UNS32_SET("moduleClkFreq", 60000000)
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
            ,OP_PARAM_STRING_SET("outfile", "uart2_outfile.txt")
        )
    );

    // PSE uart3

    const char *uart3_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisUART",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart3_path,
        "uart3",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4006d000ULL, .addrHi=0x4006dfffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(int51_n, "Interrupt"),
                OP_NET_CONNECT(uart3_tx_n, "DirectWrite"),
                OP_NET_CONNECT(uart3_rx_n, "DirectRead")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("fifoSize", 1)
            ,OP_PARAM_UNS32_SET("moduleClkFreq", 60000000)
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
            ,OP_PARAM_STRING_SET("outfile", "uart3_outfile.txt")
        )
    );

    // PSE usb

    const char *usb_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisUSB",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        usb_path,
        "usb",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40072000ULL, .addrHi=0x40072fffULL)
            )
        ),
        0
    );

    // PSE cmp0

    const char *cmp0_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        0,
        "KinetisCMP",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        cmp0_path,
        "cmp0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40073000ULL, .addrHi=0x40073007ULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(cmp0_dmareq_n, "DmaReq"),
                OP_NET_CONNECT(int59_n, "Interrupt"),
                OP_NET_CONNECT(cmp_vin1_n, "Vin1"),
                OP_NET_CONNECT(cmp_vin2_n, "Vin2"),
                OP_NET_CONNECT(cmp0_input0_n, "Input0"),
                OP_NET_CONNECT(cmp0_input1_n, "Input1"),
                OP_NET_CONNECT(cmp0_input2_n, "Input2"),
                OP_NET_CONNECT(cmp0_input3_n, "Input3"),
                OP_NET_CONNECT(cmp0_input4_n, "Input4"),
                OP_NET_CONNECT(cmp0_input5_n, "Input5"),
                OP_NET_CONNECT(cmp0_input6_n, "Input6"),
                OP_NET_CONNECT(cmp0_DacOutput_n, "DacOutput"),
                OP_NET_CONNECT(cmp0_extsample_n, "ExtSample"),
                OP_NET_CONNECT(cmp0_coutsoc_n, "CoutSoc"),
                OP_NET_CONNECT(cmp0_cmpopad_n, "CmpOPad")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("cmpNumber", 0)
        )
    );

    // PSE cmp1

    const char *cmp1_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        0,
        "KinetisCMP",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        cmp1_path,
        "cmp1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40073008ULL, .addrHi=0x4007300fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(int60_n, "Interrupt"),
                OP_NET_CONNECT(cmp1_dmareq_n, "DmaReq"),
                OP_NET_CONNECT(cmp_vin1_n, "Vin1"),
                OP_NET_CONNECT(cmp_vin2_n, "Vin2"),
                OP_NET_CONNECT(cmp1_input0_n, "Input0"),
                OP_NET_CONNECT(cmp1_input1_n, "Input1"),
                OP_NET_CONNECT(cmp1_input2_n, "Input2"),
                OP_NET_CONNECT(cmp1_input3_n, "Input3"),
                OP_NET_CONNECT(cmp1_input4_n, "Input4"),
                OP_NET_CONNECT(cmp1_input5_n, "Input5"),
                OP_NET_CONNECT(cmp1_input6_n, "Input6"),
                OP_NET_CONNECT(cmp1_DacOutput_n, "DacOutput"),
                OP_NET_CONNECT(cmp1_extsample_n, "ExtSample"),
                OP_NET_CONNECT(cmp1_coutsoc_n, "CoutSoc"),
                OP_NET_CONNECT(cmp1_cmpopad_n, "CmpOPad")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("cmpNumber", 1)
        )
    );

    // PSE cmp2

    const char *cmp2_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        0,
        "KinetisCMP",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        cmp2_path,
        "cmp2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40073010ULL, .addrHi=0x40073017ULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(int61_n, "Interrupt"),
                OP_NET_CONNECT(cmp2_dmareq_n, "DmaReq"),
                OP_NET_CONNECT(cmp_vin1_n, "Vin1"),
                OP_NET_CONNECT(cmp_vin2_n, "Vin2"),
                OP_NET_CONNECT(cmp2_input0_n, "Input0"),
                OP_NET_CONNECT(cmp2_input1_n, "Input1"),
                OP_NET_CONNECT(cmp2_input2_n, "Input2"),
                OP_NET_CONNECT(cmp2_input3_n, "Input3"),
                OP_NET_CONNECT(cmp2_input4_n, "Input4"),
                OP_NET_CONNECT(cmp2_input5_n, "Input5"),
                OP_NET_CONNECT(cmp2_input6_n, "Input6"),
                OP_NET_CONNECT(cmp2_DacOutput_n, "DacOutput"),
                OP_NET_CONNECT(cmp2_extsample_n, "ExtSample"),
                OP_NET_CONNECT(cmp2_coutsoc_n, "CoutSoc"),
                OP_NET_CONNECT(cmp2_cmpopad_n, "CmpOPad")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("cmpNumber", 2)
        )
    );

    // PSE cmp3

    const char *cmp3_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        0,
        "KinetisCMP",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        cmp3_path,
        "cmp3",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40073018ULL, .addrHi=0x4007301fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(int98_n, "Interrupt"),
                OP_NET_CONNECT(cmp3_dmareq_n, "DmaReq"),
                OP_NET_CONNECT(cmp_vin1_n, "Vin1"),
                OP_NET_CONNECT(cmp_vin2_n, "Vin2"),
                OP_NET_CONNECT(cmp3_input0_n, "Input0"),
                OP_NET_CONNECT(cmp3_input1_n, "Input1"),
                OP_NET_CONNECT(cmp3_input2_n, "Input2"),
                OP_NET_CONNECT(cmp3_input3_n, "Input3"),
                OP_NET_CONNECT(cmp3_input4_n, "Input4"),
                OP_NET_CONNECT(cmp3_input5_n, "Input5"),
                OP_NET_CONNECT(cmp3_input6_n, "Input6"),
                OP_NET_CONNECT(cmp3_DacOutput_n, "DacOutput"),
                OP_NET_CONNECT(cmp3_extsample_n, "ExtSample"),
                OP_NET_CONNECT(cmp3_coutsoc_n, "CoutSoc"),
                OP_NET_CONNECT(cmp3_cmpopad_n, "CmpOPad")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("cmpNumber", 3)
        )
    );

    // PSE vref

    const char *vref_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisVREF",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        vref_path,
        "vref",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x40074000ULL, .addrHi=0x40074fffULL)
            )
        ),
        0
    );

    // PSE llwu

    const char *llwu_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisLLWU",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        llwu_path,
        "llwu",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4007c000ULL, .addrHi=0x4007cfffULL)
            )
        ),
        0
    );

    // PSE pmc

    const char *pmc_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisPMC",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        pmc_path,
        "pmc",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4007d000ULL, .addrHi=0x4007dfffULL)
            )
        ),
        0
    );

    // PSE smc

    const char *smc_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisSMC",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        smc_path,
        "smc",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4007e000ULL, .addrHi=0x4007efffULL)
            )
        ),
        0
    );

    // PSE rcm

    const char *rcm_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisRCM",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        rcm_path,
        "rcm",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x4007f000ULL, .addrHi=0x4007ffffULL)
            )
        ),
        0
    );

    // PSE rng

    const char *rng_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisRNG",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        rng_path,
        "rng",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400a0000ULL, .addrHi=0x400a0fffULL)
            )
        ),
        0
    );

    // PSE can1

    const char *can1_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisCAN",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        can1_path,
        "can1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400a4000ULL, .addrHi=0x400a4fffULL)
            )
        ),
        0
    );

    // PSE nfc

    const char *nfc_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisNFC",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        nfc_path,
        "nfc",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400a8000ULL, .addrHi=0x400abfffULL)
            )
        ),
        0
    );

    // PSE spi2

    const char *spi2_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisSPI",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        spi2_path,
        "spi2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400ac000ULL, .addrHi=0x400acfffULL)
            )
        ),
        0
    );

    // PSE ddr

    const char *ddr_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisDDR",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ddr_path,
        "ddr",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400ae000ULL, .addrHi=0x400aefffULL)
            )
        ),
        0
    );

    // PSE i2s1

    const char *i2s1_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisI2S",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        i2s1_path,
        "i2s1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400af000ULL, .addrHi=0x400affffULL)
            )
        ),
        0
    );

    // PSE sdhc

    const char *sdhc_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisSDHC",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        sdhc_path,
        "sdhc",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400b1000ULL, .addrHi=0x400b1fffULL)
            )
        ),
        0
    );

    // PSE ftm2

    const char *ftm2_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisFTM",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ftm2_path,
        "ftm2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400b8000ULL, .addrHi=0x400b8fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ftm2_phaseA_n, "PhaseA"),
                OP_NET_CONNECT(ftm2_phaseB_n, "PhaseB"),
                OP_NET_CONNECT(int64_n, "Interrupt")
            )
        ),
        0
    );

    // PSE ftm3

    const char *ftm3_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisFTM",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ftm3_path,
        "ftm3",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400b9000ULL, .addrHi=0x400b9fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(ftm3_phaseA_n, "PhaseA"),
                OP_NET_CONNECT(ftm3_phaseB_n, "PhaseB"),
                OP_NET_CONNECT(int101_n, "Interrupt")
            )
        ),
        0
    );

    // PSE adc1

    const char *adc1_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisADC",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        adc1_path,
        "adc1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400bb000ULL, .addrHi=0x400bbfffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(adc1_input_n, "AdIn"),
                OP_NET_CONNECT(adc1_sample_n, "AdInId"),
                OP_NET_CONNECT(adc1_trigger_n, "HwTrig")
            )
        ),
        0
    );

    // PSE adc3

    const char *adc3_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisADC",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        adc3_path,
        "adc3",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400bc000ULL, .addrHi=0x400bcfffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(adc3_input_n, "AdIn"),
                OP_NET_CONNECT(adc3_sample_n, "AdInId"),
                OP_NET_CONNECT(adc3_trigger_n, "HwTrig")
            )
        ),
        0
    );

    // PSE enet

    const char *enet_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisENET",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        enet_path,
        "enet",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400c0000ULL, .addrHi=0x400c0fffULL)
            )
        ),
        0
    );

    // PSE dac0

    const char *dac0_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisDAC",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        dac0_path,
        "dac0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400cc000ULL, .addrHi=0x400ccfffULL)
            )
        ),
        0
    );

    // PSE dac1

    const char *dac1_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisDAC",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        dac1_path,
        "dac1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400cd000ULL, .addrHi=0x400cdfffULL)
            )
        ),
        0
    );

    // PSE osc1

    const char *osc1_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisOSC",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        osc1_path,
        "osc1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400e5000ULL, .addrHi=0x400e5fffULL)
            )
        ),
        0
    );

    // PSE uart4

    const char *uart4_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisUART",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart4_path,
        "uart4",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400ea000ULL, .addrHi=0x400eafffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(int53_n, "Interrupt"),
                OP_NET_CONNECT(uart4_tx_n, "DirectWrite"),
                OP_NET_CONNECT(uart4_rx_n, "DirectRead")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("fifoSize", 1)
            ,OP_PARAM_UNS32_SET("moduleClkFreq", 60000000)
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
            ,OP_PARAM_STRING_SET("outfile", "uart4_outfile.txt")
        )
    );

    // PSE uart5

    const char *uart5_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        "peripheral",
        "KinetisUART",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uart5_path,
        "uart5",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400eb000ULL, .addrHi=0x400ebfffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(int55_n, "Interrupt"),
                OP_NET_CONNECT(uart5_tx_n, "DirectWrite"),
                OP_NET_CONNECT(uart5_rx_n, "DirectRead")
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("fifoSize", 1)
            ,OP_PARAM_UNS32_SET("moduleClkFreq", 60000000)
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
            ,OP_PARAM_STRING_SET("outfile", "uart5_outfile.txt")
        )
    );

    // PSE gpioA

    const char *gpioA_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        0,
        "KinetisGPIO",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        gpioA_path,
        "gpioA",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400ff000ULL, .addrHi=0x400ff03fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(gpioA_in_n, "Input"),
                OP_NET_CONNECT(gpioA_out_n, "Output"),
                OP_NET_CONNECT(gpioA_mask_n, "OutputMask")
            )
        ),
        0
    );

    // PSE gpioB

    const char *gpioB_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        0,
        "KinetisGPIO",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        gpioB_path,
        "gpioB",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400ff040ULL, .addrHi=0x400ff07fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(gpioB_in_n, "Input"),
                OP_NET_CONNECT(gpioB_out_n, "Output"),
                OP_NET_CONNECT(gpioB_mask_n, "OutputMask")
            )
        ),
        0
    );

    // PSE gpioC

    const char *gpioC_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        0,
        "KinetisGPIO",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        gpioC_path,
        "gpioC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400ff080ULL, .addrHi=0x400ff0bfULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(gpioC_in_n, "Input"),
                OP_NET_CONNECT(gpioC_out_n, "Output"),
                OP_NET_CONNECT(gpioC_mask_n, "OutputMask")
            )
        ),
        0
    );

    // PSE gpioD

    const char *gpioD_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        0,
        "KinetisGPIO",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        gpioD_path,
        "gpioD",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400ff0c0ULL, .addrHi=0x400ff0ffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(gpioD_in_n, "Input"),
                OP_NET_CONNECT(gpioD_out_n, "Output"),
                OP_NET_CONNECT(gpioD_mask_n, "OutputMask")
            )
        ),
        0
    );

    // PSE gpioE

    const char *gpioE_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        0,
        "KinetisGPIO",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        gpioE_path,
        "gpioE",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400ff100ULL, .addrHi=0x400ff13fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(gpioE_in_n, "Input"),
                OP_NET_CONNECT(gpioE_out_n, "Output"),
                OP_NET_CONNECT(gpioE_mask_n, "OutputMask")
            )
        ),
        0
    );

    // PSE gpioF

    const char *gpioF_path = opVLNVString(
        0, // use the default VLNV path
        "freescale.ovpworld.org",
        0,
        "KinetisGPIO",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        gpioF_path,
        "gpioF",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x400ff140ULL, .addrHi=0x400ff17fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(gpioF_in_n, "Input"),
                OP_NET_CONNECT(gpioF_out_n, "Output"),
                OP_NET_CONNECT(gpioF_mask_n, "OutputMask")
            )
        ),
        0
    );

}

static optNetPortInfo netPortSpecs[] = {
    {
        .name        = "p_uart0_tx",
        .description = 0,
    },
    {
        .name        = "p_uart0_rx",
        .description = 0,
    },
    {
        .name        = "p_uart1_tx",
        .description = 0,
    },
    {
        .name        = "p_uart1_rx",
        .description = 0,
    },
    {
        .name        = "p_uart2_tx",
        .description = 0,
    },
    {
        .name        = "p_uart2_rx",
        .description = 0,
    },
    {
        .name        = "p_uart3_tx",
        .description = 0,
    },
    {
        .name        = "p_uart3_rx",
        .description = 0,
    },
    {
        .name        = "p_uart4_tx",
        .description = 0,
    },
    {
        .name        = "p_uart4_rx",
        .description = 0,
    },
    {
        .name        = "p_uart5_tx",
        .description = 0,
    },
    {
        .name        = "p_uart5_rx",
        .description = 0,
    },
    {
        .name        = "p_gpioA_out",
        .description = 0,
    },
    {
        .name        = "p_gpioA_in",
        .description = 0,
    },
    {
        .name        = "p_gpioA_mask",
        .description = 0,
    },
    {
        .name        = "p_gpioB_out",
        .description = 0,
    },
    {
        .name        = "p_gpioB_in",
        .description = 0,
    },
    {
        .name        = "p_gpioB_mask",
        .description = 0,
    },
    {
        .name        = "p_gpioC_out",
        .description = 0,
    },
    {
        .name        = "p_gpioC_in",
        .description = 0,
    },
    {
        .name        = "p_gpioC_mask",
        .description = 0,
    },
    {
        .name        = "p_gpioD_out",
        .description = 0,
    },
    {
        .name        = "p_gpioD_in",
        .description = 0,
    },
    {
        .name        = "p_gpioD_mask",
        .description = 0,
    },
    {
        .name        = "p_gpioE_out",
        .description = 0,
    },
    {
        .name        = "p_gpioE_in",
        .description = 0,
    },
    {
        .name        = "p_gpioE_mask",
        .description = 0,
    },
    {
        .name        = "p_gpioF_out",
        .description = 0,
    },
    {
        .name        = "p_gpioF_in",
        .description = 0,
    },
    {
        .name        = "p_gpioF_mask",
        .description = 0,
    },
    {
        .name        = "p_cmp_ext_sample",
        .description = 0,
    },
    {
        .name        = "p_cmp_vin1",
        .description = 0,
    },
    {
        .name        = "p_cmp_vin2",
        .description = 0,
    },
    {
        .name        = "p_cmp0_input0",
        .description = 0,
    },
    {
        .name        = "p_cmp0_input1",
        .description = 0,
    },
    {
        .name        = "p_cmp0_input2",
        .description = 0,
    },
    {
        .name        = "p_cmp0_input3",
        .description = 0,
    },
    {
        .name        = "p_cmp0_input4",
        .description = 0,
    },
    {
        .name        = "p_cmp0_input5",
        .description = 0,
    },
    {
        .name        = "p_cmp0_input6",
        .description = 0,
    },
    {
        .name        = "p_cmp0_DacOutput",
        .description = 0,
    },
    {
        .name        = "p_cmp_coutSoc",
        .description = 0,
    },
    {
        .name        = "p_cmp_OPad",
        .description = 0,
    },
    {
        .name        = "p_cmp1_input0",
        .description = 0,
    },
    {
        .name        = "p_cmp1_input1",
        .description = 0,
    },
    {
        .name        = "p_cmp1_input2",
        .description = 0,
    },
    {
        .name        = "p_cmp1_input3",
        .description = 0,
    },
    {
        .name        = "p_cmp1_input4",
        .description = 0,
    },
    {
        .name        = "p_cmp1_input5",
        .description = 0,
    },
    {
        .name        = "p_cmp1_input6",
        .description = 0,
    },
    {
        .name        = "p_cmp1_DacOutput",
        .description = 0,
    },
    {
        .name        = "p_cmp2_input0",
        .description = 0,
    },
    {
        .name        = "p_cmp2_input1",
        .description = 0,
    },
    {
        .name        = "p_cmp2_input2",
        .description = 0,
    },
    {
        .name        = "p_cmp2_input3",
        .description = 0,
    },
    {
        .name        = "p_cmp2_input4",
        .description = 0,
    },
    {
        .name        = "p_cmp2_input5",
        .description = 0,
    },
    {
        .name        = "p_cmp2_input6",
        .description = 0,
    },
    {
        .name        = "p_cmp2_DacOutput",
        .description = 0,
    },
    {
        .name        = "p_cmp3_input0",
        .description = 0,
    },
    {
        .name        = "p_cmp3_input1",
        .description = 0,
    },
    {
        .name        = "p_cmp3_input2",
        .description = 0,
    },
    {
        .name        = "p_cmp3_input3",
        .description = 0,
    },
    {
        .name        = "p_cmp3_input4",
        .description = 0,
    },
    {
        .name        = "p_cmp3_input5",
        .description = 0,
    },
    {
        .name        = "p_cmp3_input6",
        .description = 0,
    },
    {
        .name        = "p_cmp3_DacOutput",
        .description = 0,
    },
    {
        .name        = "p_adc0_input",
        .description = 0,
    },
    {
        .name        = "p_adc0_sample",
        .description = 0,
    },
    {
        .name        = "p_adc0_trigger",
        .description = 0,
    },
    {
        .name        = "p_adc1_input",
        .description = 0,
    },
    {
        .name        = "p_adc1_sample",
        .description = 0,
    },
    {
        .name        = "p_adc1_trigger",
        .description = 0,
    },
    {
        .name        = "p_adc2_input",
        .description = 0,
    },
    {
        .name        = "p_adc2_sample",
        .description = 0,
    },
    {
        .name        = "p_adc2_trigger",
        .description = 0,
    },
    {
        .name        = "p_adc3_input",
        .description = 0,
    },
    {
        .name        = "p_adc3_sample",
        .description = 0,
    },
    {
        .name        = "p_adc3_trigger",
        .description = 0,
    },
    {
        .name        = "p_dac0_output",
        .description = 0,
    },
    {
        .name        = "p_dac1_output",
        .description = 0,
    },
    {
        .name        = "p_ftm_input",
        .description = 0,
    },
    {
        .name        = "p_ftm_output",
        .description = 0,
    },
    {
        .name        = "p_ftm_mask",
        .description = 0,
    },
    {
        .name        = "p_ftm_fault",
        .description = 0,
    },
    {
        .name        = "p_ftm_phaseA",
        .description = 0,
    },
    {
        .name        = "p_ftm_phaseB",
        .description = 0,
    },
    {
        .name        = "p_can0_tx",
        .description = 0,
    },
    {
        .name        = "p_can0_rx",
        .description = 0,
    },
    {
        .name        = "p_can1_tx",
        .description = 0,
    },
    {
        .name        = "p_can1_rx",
        .description = 0,
    },
    {
        .name        = "p_spi0_tx",
        .description = 0,
    },
    {
        .name        = "p_spi0_rx",
        .description = 0,
    },
    {
        .name        = "p_spi1_tx",
        .description = 0,
    },
    {
        .name        = "p_spi1_rx",
        .description = 0,
    },
    {
        .name        = "p_spi2_tx",
        .description = 0,
    },
    {
        .name        = "p_spi2_rx",
        .description = 0,
    },
    {
        .name        = "p_i2c0_tx",
        .description = 0,
    },
    {
        .name        = "p_i2c0_rx",
        .description = 0,
    },
    {
        .name        = "p_i2c1_tx",
        .description = 0,
    },
    {
        .name        = "p_i2c1_rx",
        .description = 0,
    },
    {
        .name        = "p_i2s0_tx",
        .description = 0,
    },
    {
        .name        = "p_i2s0_rx",
        .description = 0,
    },
    {
        .name        = "p_i2s1_tx",
        .description = 0,
    },
    {
        .name        = "p_i2s1_rx",
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
    .purpose              = OP_PP_BAREMETAL,
    .visibility           = OP_VISIBLE,
    .vlnv          = {
        .vendor  = "freescale.ovpworld.org",
        .library = "platform",
        .name    = "FreescaleKinetis64",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
    .netPortSpecsCB       = moduleNetPortIterator,
};

static void cmdParserAddUserArgs(optCmdParserP parser) {
    opCmdParserAdd(parser, "uart0console", 0 , 0, 0                   , OP_FT_BOOLVAL       , &options.uart0console, "enable console on UART0", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "uart1console", 0 , 0, 0                   , OP_FT_BOOLVAL       , &options.uart1console, "enable console on UART1", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "uart2console", 0 , 0, 0                   , OP_FT_BOOLVAL       , &options.uart2console, "enable console on UART2", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "uart3console", 0 , 0, 0                   , OP_FT_BOOLVAL       , &options.uart3console, "enable console on UART3", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "uart4console", 0 , 0, 0                   , OP_FT_BOOLVAL       , &options.uart4console, "enable console on UART4", OP_AC_ALL, 0, 0);
    opCmdParserAdd(parser, "uart5console", 0 , 0, 0                   , OP_FT_BOOLVAL       , &options.uart5console, "enable console on UART5", OP_AC_ALL, 0, 0);
}

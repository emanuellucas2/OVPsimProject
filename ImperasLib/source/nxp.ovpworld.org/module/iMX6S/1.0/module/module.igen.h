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
    opDocTextAdd(doc_11_node, "This module implements the NXP i.MX 6 Solo application processor\n          The i.MX6S integrates a single ARM Cortex-A9 MPCore application processor, memories and peripherals.");
    optDocNodeP doc_21_node = opModuleDocSectionAdd(mi, "Limitations");
    opDocTextAdd(doc_21_node, "Some of the peripherals are register-only, non-functional models. See the individual peripheral model documentation for details.");
    optDocNodeP doc_31_node = opModuleDocSectionAdd(mi, "Reference");
    opDocTextAdd(doc_31_node, "i.MX 6Solo/6DualLite Applications Processor Reference Manual (IMX6SDLRM_Ref_Manual.pdf)");
    opDocTextAdd(doc_31_node, "From: https://www.nxp.com/products/microcontrollers-and-processors/arm-based-processors-and-mcus/i.mx-applications-processors/i.mx-6-processors/i.mx-6solo-processors-single-core-multimedia-3d-graphics-arm-cortex-a9-core:i.MX6S");


    // Bus pBus

    optBusP pBus_b = opBusNew(mi, "pBus", 32, 0, 0);


////////////////////////////////////////////////////////////////////////////////
//                                    NETS
////////////////////////////////////////////////////////////////////////////////

    optNetP IOMUXC_spi_n = opNetNew(mi, "IOMUXC_spi", 0, 0);
    optNetP DAP_spi_n = opNetNew(mi, "DAP_spi", 0, 0);
    optNetP SDMA_spi_n = opNetNew(mi, "SDMA_spi", 0, 0);
    optNetP VPU_spi_n = opNetNew(mi, "VPU_spi", 0, 0);
    optNetP SNVS_spi_n = opNetNew(mi, "SNVS_spi", 0, 0);
    optNetP IPU_spi_n = opNetNew(mi, "IPU_spi", 0, 0);
    optNetP IPU1_spi_n = opNetNew(mi, "IPU1_spi", 0, 0);
    optNetP GPU3D_spi_n = opNetNew(mi, "GPU3D_spi", 0, 0);
    optNetP R2D_spi_n = opNetNew(mi, "R2D_spi", 0, 0);
    optNetP VPU_jpeg_spi_n = opNetNew(mi, "VPU_jpeg_spi", 0, 0);
    optNetP APBH_spi_n = opNetNew(mi, "APBH_spi", 0, 0);
    optNetP EIM_spi_n = opNetNew(mi, "EIM_spi", 0, 0);
    optNetP BCH_spi_n = opNetNew(mi, "BCH_spi", 0, 0);
    optNetP GPMI_spi_n = opNetNew(mi, "GPMI_spi", 0, 0);
    optNetP DTCP_spi_n = opNetNew(mi, "DTCP_spi", 0, 0);
    optNetP VDOA_spi_n = opNetNew(mi, "VDOA_spi", 0, 0);
    optNetP SNVS_consolidated_spi_n = opNetNew(mi, "SNVS_consolidated_spi", 0, 0);
    optNetP SNVS_security_spi_n = opNetNew(mi, "SNVS_security_spi", 0, 0);
    optNetP CSU_spi_n = opNetNew(mi, "CSU_spi", 0, 0);
    optNetP UART1_spi_n = opNetNew(mi, "UART1_spi", 0, 0);
    optNetP UART2_spi_n = opNetNew(mi, "UART2_spi", 0, 0);
    optNetP UART3_spi_n = opNetNew(mi, "UART3_spi", 0, 0);
    optNetP UART4_spi_n = opNetNew(mi, "UART4_spi", 0, 0);
    optNetP UART5_spi_n = opNetNew(mi, "UART5_spi", 0, 0);
    optNetP eCSPI1_spi_n = opNetNew(mi, "eCSPI1_spi", 0, 0);
    optNetP eCSPI2_spi_n = opNetNew(mi, "eCSPI2_spi", 0, 0);
    optNetP eCSPI3_spi_n = opNetNew(mi, "eCSPI3_spi", 0, 0);
    optNetP eCSPI4_spi_n = opNetNew(mi, "eCSPI4_spi", 0, 0);
    optNetP I2C4_spi_n = opNetNew(mi, "I2C4_spi", 0, 0);
    optNetP I2C1_spi_n = opNetNew(mi, "I2C1_spi", 0, 0);
    optNetP I2C2_spi_n = opNetNew(mi, "I2C2_spi", 0, 0);
    optNetP I2C3_spi_n = opNetNew(mi, "I2C3_spi", 0, 0);
    optNetP USBHost1_spi_n = opNetNew(mi, "USBHost1_spi", 0, 0);
    optNetP USBHost2_spi_n = opNetNew(mi, "USBHost2_spi", 0, 0);
    optNetP USBHost3_spi_n = opNetNew(mi, "USBHost3_spi", 0, 0);
    optNetP USBOTG_spi_n = opNetNew(mi, "USBOTG_spi", 0, 0);
    optNetP USB_PHYUTMI0_spi_n = opNetNew(mi, "USB_PHYUTMI0_spi", 0, 0);
    optNetP USB_PHYUTMI1_spi_n = opNetNew(mi, "USB_PHYUTMI1_spi", 0, 0);
    optNetP SSI1_spi_n = opNetNew(mi, "SSI1_spi", 0, 0);
    optNetP SSI2_spi_n = opNetNew(mi, "SSI2_spi", 0, 0);
    optNetP SSI3_spi_n = opNetNew(mi, "SSI3_spi", 0, 0);
    optNetP TMTS_spi_n = opNetNew(mi, "TMTS_spi", 0, 0);
    optNetP ASRC_spi_n = opNetNew(mi, "ASRC_spi", 0, 0);
    optNetP ESAI_spi_n = opNetNew(mi, "ESAI_spi", 0, 0);
    optNetP SPDIF_spi_n = opNetNew(mi, "SPDIF_spi", 0, 0);
    optNetP MLB150_err_spi_n = opNetNew(mi, "MLB150_err_spi", 0, 0);
    optNetP PMU_analog_spi_n = opNetNew(mi, "PMU_analog_spi", 0, 0);
    optNetP GPT_spi_n = opNetNew(mi, "GPT_spi", 0, 0);
    optNetP EPIT1_spi_n = opNetNew(mi, "EPIT1_spi", 0, 0);
    optNetP EPIT2_spi_n = opNetNew(mi, "EPIT2_spi", 0, 0);
    optNetP GPIO1_int7_spi_n = opNetNew(mi, "GPIO1_int7_spi", 0, 0);
    optNetP GPIO1_int6_spi_n = opNetNew(mi, "GPIO1_int6_spi", 0, 0);
    optNetP GPIO1_int5_spi_n = opNetNew(mi, "GPIO1_int5_spi", 0, 0);
    optNetP GPIO1_int4_spi_n = opNetNew(mi, "GPIO1_int4_spi", 0, 0);
    optNetP GPIO1_int3_spi_n = opNetNew(mi, "GPIO1_int3_spi", 0, 0);
    optNetP GPIO1_int2_spi_n = opNetNew(mi, "GPIO1_int2_spi", 0, 0);
    optNetP GPIO1_int1_spi_n = opNetNew(mi, "GPIO1_int1_spi", 0, 0);
    optNetP GPIO1_int0_spi_n = opNetNew(mi, "GPIO1_int0_spi", 0, 0);
    optNetP GPIO1_s0_15_spi_n = opNetNew(mi, "GPIO1_s0_15_spi", 0, 0);
    optNetP GPIO1_s16_31_spi_n = opNetNew(mi, "GPIO1_s16_31_spi", 0, 0);
    optNetP GPIO2_s0_15_spi_n = opNetNew(mi, "GPIO2_s0_15_spi", 0, 0);
    optNetP GPIO2_s16_31_spi_n = opNetNew(mi, "GPIO2_s16_31_spi", 0, 0);
    optNetP GPIO3_s0_15_spi_n = opNetNew(mi, "GPIO3_s0_15_spi", 0, 0);
    optNetP GPIO3_s16_31_spi_n = opNetNew(mi, "GPIO3_s16_31_spi", 0, 0);
    optNetP GPIO4_s0_15_spi_n = opNetNew(mi, "GPIO4_s0_15_spi", 0, 0);
    optNetP GPIO4_s16_31_spi_n = opNetNew(mi, "GPIO4_s16_31_spi", 0, 0);
    optNetP GPIO5_s0_15_spi_n = opNetNew(mi, "GPIO5_s0_15_spi", 0, 0);
    optNetP GPIO5_s16_31_spi_n = opNetNew(mi, "GPIO5_s16_31_spi", 0, 0);
    optNetP GPIO6_s0_15_spi_n = opNetNew(mi, "GPIO6_s0_15_spi", 0, 0);
    optNetP GPIO6_s16_31_spi_n = opNetNew(mi, "GPIO6_s16_31_spi", 0, 0);
    optNetP GPIO7_s0_15_spi_n = opNetNew(mi, "GPIO7_s0_15_spi", 0, 0);
    optNetP GPIO7_s16_31_spi_n = opNetNew(mi, "GPIO7_s16_31_spi", 0, 0);
    optNetP WDOG1_spi_n = opNetNew(mi, "WDOG1_spi", 0, 0);
    optNetP WDOG2_spi_n = opNetNew(mi, "WDOG2_spi", 0, 0);
    optNetP KPP_spi_n = opNetNew(mi, "KPP_spi", 0, 0);
    optNetP PWM1_spi_n = opNetNew(mi, "PWM1_spi", 0, 0);
    optNetP PWM2_spi_n = opNetNew(mi, "PWM2_spi", 0, 0);
    optNetP PWM3_spi_n = opNetNew(mi, "PWM3_spi", 0, 0);
    optNetP PWM4_spi_n = opNetNew(mi, "PWM4_spi", 0, 0);
    optNetP CCM1_spi_n = opNetNew(mi, "CCM1_spi", 0, 0);
    optNetP CCM2_spi_n = opNetNew(mi, "CCM2_spi", 0, 0);
    optNetP GPC1_spi_n = opNetNew(mi, "GPC1_spi", 0, 0);
    optNetP SRC_spi_n = opNetNew(mi, "SRC_spi", 0, 0);
    optNetP CPU_L2_spi_n = opNetNew(mi, "CPU_L2_spi", 0, 0);
    optNetP CPU_ParityCheckError_spi_n = opNetNew(mi, "CPU_ParityCheckError_spi", 0, 0);
    optNetP CPU_Performance_Unit_spi_n = opNetNew(mi, "CPU_Performance_Unit_spi", 0, 0);
    optNetP CPU_CTI_spi_n = opNetNew(mi, "CPU_CTI_spi", 0, 0);
    optNetP SRC_wdog_spi_n = opNetNew(mi, "SRC_wdog_spi", 0, 0);
    optNetP EPDC_spi_n = opNetNew(mi, "EPDC_spi", 0, 0);
    optNetP PXP_spi_n = opNetNew(mi, "PXP_spi", 0, 0);
    optNetP MIPI_CSI1_spi_n = opNetNew(mi, "MIPI_CSI1_spi", 0, 0);
    optNetP MIPI_CSI2_spi_n = opNetNew(mi, "MIPI_CSI2_spi", 0, 0);
    optNetP MIPI_DSI_spi_n = opNetNew(mi, "MIPI_DSI_spi", 0, 0);
    optNetP MIPI_HSI_spi_n = opNetNew(mi, "MIPI_HSI_spi", 0, 0);
    optNetP SJC_spi_n = opNetNew(mi, "SJC_spi", 0, 0);
    optNetP CAAM0_spi_n = opNetNew(mi, "CAAM0_spi", 0, 0);
    optNetP CAAM1_spi_n = opNetNew(mi, "CAAM1_spi", 0, 0);
    optNetP TZASC1_spi_n = opNetNew(mi, "TZASC1_spi", 0, 0);
    optNetP TZASC2_spi_n = opNetNew(mi, "TZASC2_spi", 0, 0);
    optNetP FLEXCAN1_spi_n = opNetNew(mi, "FLEXCAN1_spi", 0, 0);
    optNetP FLEXCAN2_spi_n = opNetNew(mi, "FLEXCAN2_spi", 0, 0);
    optNetP HDMI_spi_n = opNetNew(mi, "HDMI_spi", 0, 0);
    optNetP HDMICEC_spi_n = opNetNew(mi, "HDMICEC_spi", 0, 0);
    optNetP MLB150_irq0_31_spi_n = opNetNew(mi, "MLB150_irq0_31_spi", 0, 0);
    optNetP ENET_spi_n = opNetNew(mi, "ENET_spi", 0, 0);
    optNetP ENET_timer_spi_n = opNetNew(mi, "ENET_timer_spi", 0, 0);
    optNetP PCIe1_spi_n = opNetNew(mi, "PCIe1_spi", 0, 0);
    optNetP PCIe2_spi_n = opNetNew(mi, "PCIe2_spi", 0, 0);
    optNetP PCIe3_spi_n = opNetNew(mi, "PCIe3_spi", 0, 0);
    optNetP PCIe4_spi_n = opNetNew(mi, "PCIe4_spi", 0, 0);
    optNetP DCIC1_spi_n = opNetNew(mi, "DCIC1_spi", 0, 0);
    optNetP DCIC2_spi_n = opNetNew(mi, "DCIC2_spi", 0, 0);
    optNetP MLB150_irq32_63_spi_n = opNetNew(mi, "MLB150_irq32_63_spi", 0, 0);
    optNetP PMU_digital_spi_n = opNetNew(mi, "PMU_digital_spi", 0, 0);
    optNetP reset_A9_CPU0_n = opNetNew(mi, "reset_A9_CPU0", 0, 0);
    optNetP reset_A9_CPU1_n = opNetNew(mi, "reset_A9_CPU1", 0, 0);
    optNetP VBD0_spi_n = opNetNew(mi, "VBD0_spi", 0, 0);

    // Processor cpu

    const char *cpu_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "arm",
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
                OP_NET_CONNECT(IOMUXC_spi_n, "SPI32"),
                OP_NET_CONNECT(DAP_spi_n, "SPI33"),
                OP_NET_CONNECT(SDMA_spi_n, "SPI34"),
                OP_NET_CONNECT(VPU_spi_n, "SPI35"),
                OP_NET_CONNECT(SNVS_spi_n, "SPI36"),
                OP_NET_CONNECT(IPU_spi_n, "SPI37"),
                OP_NET_CONNECT(IPU1_spi_n, "SPI38"),
                OP_NET_CONNECT(GPU3D_spi_n, "SPI41"),
                OP_NET_CONNECT(R2D_spi_n, "SPI42"),
                OP_NET_CONNECT(VPU_jpeg_spi_n, "SPI44"),
                OP_NET_CONNECT(APBH_spi_n, "SPI45"),
                OP_NET_CONNECT(EIM_spi_n, "SPI46"),
                OP_NET_CONNECT(BCH_spi_n, "SPI47"),
                OP_NET_CONNECT(GPMI_spi_n, "SPI48"),
                OP_NET_CONNECT(DTCP_spi_n, "SPI49"),
                OP_NET_CONNECT(VDOA_spi_n, "SPI50"),
                OP_NET_CONNECT(SNVS_consolidated_spi_n, "SPI51"),
                OP_NET_CONNECT(SNVS_security_spi_n, "SPI52"),
                OP_NET_CONNECT(CSU_spi_n, "SPI53"),
                OP_NET_CONNECT(UART1_spi_n, "SPI58"),
                OP_NET_CONNECT(UART2_spi_n, "SPI59"),
                OP_NET_CONNECT(UART3_spi_n, "SPI60"),
                OP_NET_CONNECT(UART4_spi_n, "SPI61"),
                OP_NET_CONNECT(UART5_spi_n, "SPI62"),
                OP_NET_CONNECT(eCSPI1_spi_n, "SPI63"),
                OP_NET_CONNECT(eCSPI2_spi_n, "SPI64"),
                OP_NET_CONNECT(eCSPI3_spi_n, "SPI65"),
                OP_NET_CONNECT(eCSPI4_spi_n, "SPI66"),
                OP_NET_CONNECT(I2C4_spi_n, "SPI67"),
                OP_NET_CONNECT(I2C1_spi_n, "SPI68"),
                OP_NET_CONNECT(I2C2_spi_n, "SPI69"),
                OP_NET_CONNECT(I2C3_spi_n, "SPI70"),
                OP_NET_CONNECT(USBHost1_spi_n, "SPI72"),
                OP_NET_CONNECT(USBHost2_spi_n, "SPI73"),
                OP_NET_CONNECT(USBHost3_spi_n, "SPI74"),
                OP_NET_CONNECT(USBOTG_spi_n, "SPI75"),
                OP_NET_CONNECT(USB_PHYUTMI0_spi_n, "SPI76"),
                OP_NET_CONNECT(USB_PHYUTMI1_spi_n, "SPI77"),
                OP_NET_CONNECT(SSI1_spi_n, "SPI78"),
                OP_NET_CONNECT(SSI2_spi_n, "SPI79"),
                OP_NET_CONNECT(SSI3_spi_n, "SPI80"),
                OP_NET_CONNECT(TMTS_spi_n, "SPI81"),
                OP_NET_CONNECT(ASRC_spi_n, "SPI82"),
                OP_NET_CONNECT(ESAI_spi_n, "SPI83"),
                OP_NET_CONNECT(SPDIF_spi_n, "SPI84"),
                OP_NET_CONNECT(MLB150_err_spi_n, "SPI85"),
                OP_NET_CONNECT(PMU_analog_spi_n, "SPI86"),
                OP_NET_CONNECT(GPT_spi_n, "SPI87"),
                OP_NET_CONNECT(EPIT1_spi_n, "SPI88"),
                OP_NET_CONNECT(EPIT2_spi_n, "SPI89"),
                OP_NET_CONNECT(GPIO1_int7_spi_n, "SPI90"),
                OP_NET_CONNECT(GPIO1_int6_spi_n, "SPI91"),
                OP_NET_CONNECT(GPIO1_int5_spi_n, "SPI92"),
                OP_NET_CONNECT(GPIO1_int4_spi_n, "SPI93"),
                OP_NET_CONNECT(GPIO1_int3_spi_n, "SPI94"),
                OP_NET_CONNECT(GPIO1_int2_spi_n, "SPI95"),
                OP_NET_CONNECT(GPIO1_int1_spi_n, "SPI96"),
                OP_NET_CONNECT(GPIO1_int0_spi_n, "SPI97"),
                OP_NET_CONNECT(GPIO1_s0_15_spi_n, "SPI98"),
                OP_NET_CONNECT(GPIO1_s16_31_spi_n, "SPI99"),
                OP_NET_CONNECT(GPIO2_s0_15_spi_n, "SPI100"),
                OP_NET_CONNECT(GPIO2_s16_31_spi_n, "SPI101"),
                OP_NET_CONNECT(GPIO3_s0_15_spi_n, "SPI102"),
                OP_NET_CONNECT(GPIO3_s16_31_spi_n, "SPI103"),
                OP_NET_CONNECT(GPIO4_s0_15_spi_n, "SPI104"),
                OP_NET_CONNECT(GPIO4_s16_31_spi_n, "SPI105"),
                OP_NET_CONNECT(GPIO5_s0_15_spi_n, "SPI106"),
                OP_NET_CONNECT(GPIO5_s16_31_spi_n, "SPI107"),
                OP_NET_CONNECT(GPIO6_s0_15_spi_n, "SPI108"),
                OP_NET_CONNECT(GPIO6_s16_31_spi_n, "SPI109"),
                OP_NET_CONNECT(GPIO7_s0_15_spi_n, "SPI110"),
                OP_NET_CONNECT(GPIO7_s16_31_spi_n, "SPI111"),
                OP_NET_CONNECT(WDOG1_spi_n, "SPI112"),
                OP_NET_CONNECT(WDOG2_spi_n, "SPI113"),
                OP_NET_CONNECT(KPP_spi_n, "SPI114"),
                OP_NET_CONNECT(PWM1_spi_n, "SPI115"),
                OP_NET_CONNECT(PWM2_spi_n, "SPI116"),
                OP_NET_CONNECT(PWM3_spi_n, "SPI117"),
                OP_NET_CONNECT(PWM4_spi_n, "SPI118"),
                OP_NET_CONNECT(CCM1_spi_n, "SPI119"),
                OP_NET_CONNECT(CCM2_spi_n, "SPI120"),
                OP_NET_CONNECT(GPC1_spi_n, "SPI121"),
                OP_NET_CONNECT(SRC_spi_n, "SPI123"),
                OP_NET_CONNECT(CPU_L2_spi_n, "SPI124"),
                OP_NET_CONNECT(CPU_ParityCheckError_spi_n, "SPI125"),
                OP_NET_CONNECT(CPU_Performance_Unit_spi_n, "SPI126"),
                OP_NET_CONNECT(CPU_CTI_spi_n, "SPI127"),
                OP_NET_CONNECT(SRC_wdog_spi_n, "SPI128"),
                OP_NET_CONNECT(EPDC_spi_n, "SPI129"),
                OP_NET_CONNECT(PXP_spi_n, "SPI130"),
                OP_NET_CONNECT(MIPI_CSI1_spi_n, "SPI132"),
                OP_NET_CONNECT(MIPI_CSI2_spi_n, "SPI133"),
                OP_NET_CONNECT(MIPI_DSI_spi_n, "SPI134"),
                OP_NET_CONNECT(MIPI_HSI_spi_n, "SPI135"),
                OP_NET_CONNECT(SJC_spi_n, "SPI136"),
                OP_NET_CONNECT(CAAM0_spi_n, "SPI137"),
                OP_NET_CONNECT(CAAM1_spi_n, "SPI138"),
                OP_NET_CONNECT(TZASC1_spi_n, "SPI140"),
                OP_NET_CONNECT(TZASC2_spi_n, "SPI141"),
                OP_NET_CONNECT(FLEXCAN1_spi_n, "SPI142"),
                OP_NET_CONNECT(FLEXCAN2_spi_n, "SPI143"),
                OP_NET_CONNECT(HDMI_spi_n, "SPI147"),
                OP_NET_CONNECT(HDMICEC_spi_n, "SPI148"),
                OP_NET_CONNECT(MLB150_irq0_31_spi_n, "SPI149"),
                OP_NET_CONNECT(ENET_spi_n, "SPI150"),
                OP_NET_CONNECT(ENET_timer_spi_n, "SPI151"),
                OP_NET_CONNECT(PCIe1_spi_n, "SPI152"),
                OP_NET_CONNECT(PCIe2_spi_n, "SPI153"),
                OP_NET_CONNECT(PCIe3_spi_n, "SPI154"),
                OP_NET_CONNECT(PCIe4_spi_n, "SPI155"),
                OP_NET_CONNECT(DCIC1_spi_n, "SPI156"),
                OP_NET_CONNECT(DCIC2_spi_n, "SPI157"),
                OP_NET_CONNECT(MLB150_irq32_63_spi_n, "SPI158"),
                OP_NET_CONNECT(PMU_digital_spi_n, "SPI159"),
                OP_NET_CONNECT(reset_A9_CPU0_n, "reset_CPU0"),
                OP_NET_CONNECT(VBD0_spi_n, "SPI39")
            )
        ),
        OP_PARAMS(
             OP_PARAM_BOOL_SET("simulateexceptions", 1)
            ,OP_PARAM_DOUBLE_SET("mips", 800)
            ,OP_PARAM_ENDIAN_SET("endian", OP_ENDIAN_LITTLE)
            ,OP_PARAM_ENUM_SET("variant", "Cortex-A9MPx1")
            ,OP_PARAM_ENUM_SET("compatibility", "ISA")
            ,OP_PARAM_BOOL_SET("UAL", 1)
            ,OP_PARAM_UNS32_SET("override_CBAR", 0x00a00000)
            ,OP_PARAM_UNS32_SET("override_MIDR", 0x411fc090)
            ,OP_PARAM_UNS32_SET("override_GICD_TYPER_ITLines", 4)
        )
    );


    // Memory OCRAM

    opMemoryNew(
        mi,
        "OCRAM",
        OP_PRIV_RWX,
        (0x91ffffULL) - (0x900000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x900000ULL, .addrHi=0x91ffffULL)
            )
        ),
        0
    );

    // Memory EIM-RAM

    opMemoryNew(
        mi,
        "EIM-RAM",
        OP_PRIV_RWX,
        (0xfffffffULL) - (0x8000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x8000000ULL, .addrHi=0xfffffffULL)
            )
        ),
        0
    );

    // Memory DRAM

    opMemoryNew(
        mi,
        "DRAM",
        OP_PRIV_RWX,
        (0x2fffffffULL) - (0x10000000ULL),
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "sp1", .slave=1, .addrLo=0x10000000ULL, .addrHi=0x2fffffffULL)
            )
        ),
        0
    );

    // PSE GPC

    const char *GPC_path = opVLNVString(
        0, // use the default VLNV path
        "nxp.ovpworld.org",
        0,
        "iMX6_GPC",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        GPC_path,
        "GPC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x20dc000ULL, .addrHi=0x20dc25fULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(IOMUXC_spi_n, "irq32"),
                OP_NET_CONNECT(DAP_spi_n, "irq33"),
                OP_NET_CONNECT(SDMA_spi_n, "irq34"),
                OP_NET_CONNECT(VPU_spi_n, "irq35"),
                OP_NET_CONNECT(SNVS_spi_n, "irq36"),
                OP_NET_CONNECT(IPU_spi_n, "irq37"),
                OP_NET_CONNECT(IPU1_spi_n, "irq38"),
                OP_NET_CONNECT(GPU3D_spi_n, "irq41"),
                OP_NET_CONNECT(R2D_spi_n, "irq42"),
                OP_NET_CONNECT(VPU_jpeg_spi_n, "irq44"),
                OP_NET_CONNECT(APBH_spi_n, "irq45"),
                OP_NET_CONNECT(EIM_spi_n, "irq46"),
                OP_NET_CONNECT(BCH_spi_n, "irq47"),
                OP_NET_CONNECT(GPMI_spi_n, "irq48"),
                OP_NET_CONNECT(DTCP_spi_n, "irq49"),
                OP_NET_CONNECT(VDOA_spi_n, "irq50"),
                OP_NET_CONNECT(SNVS_consolidated_spi_n, "irq51"),
                OP_NET_CONNECT(SNVS_security_spi_n, "irq52"),
                OP_NET_CONNECT(CSU_spi_n, "irq53"),
                OP_NET_CONNECT(UART1_spi_n, "irq58"),
                OP_NET_CONNECT(UART2_spi_n, "irq59"),
                OP_NET_CONNECT(UART3_spi_n, "irq60"),
                OP_NET_CONNECT(UART4_spi_n, "irq61"),
                OP_NET_CONNECT(UART5_spi_n, "irq62"),
                OP_NET_CONNECT(eCSPI1_spi_n, "irq63"),
                OP_NET_CONNECT(eCSPI2_spi_n, "irq64"),
                OP_NET_CONNECT(eCSPI3_spi_n, "irq65"),
                OP_NET_CONNECT(eCSPI4_spi_n, "irq66"),
                OP_NET_CONNECT(I2C4_spi_n, "irq67"),
                OP_NET_CONNECT(I2C1_spi_n, "irq68"),
                OP_NET_CONNECT(I2C2_spi_n, "irq69"),
                OP_NET_CONNECT(I2C3_spi_n, "irq70"),
                OP_NET_CONNECT(USBHost1_spi_n, "irq72"),
                OP_NET_CONNECT(USBHost2_spi_n, "irq73"),
                OP_NET_CONNECT(USBHost3_spi_n, "irq74"),
                OP_NET_CONNECT(USBOTG_spi_n, "irq75"),
                OP_NET_CONNECT(USB_PHYUTMI0_spi_n, "irq76"),
                OP_NET_CONNECT(USB_PHYUTMI1_spi_n, "irq77"),
                OP_NET_CONNECT(SSI1_spi_n, "irq78"),
                OP_NET_CONNECT(SSI2_spi_n, "irq79"),
                OP_NET_CONNECT(SSI3_spi_n, "irq80"),
                OP_NET_CONNECT(TMTS_spi_n, "irq81"),
                OP_NET_CONNECT(ASRC_spi_n, "irq82"),
                OP_NET_CONNECT(ESAI_spi_n, "irq83"),
                OP_NET_CONNECT(SPDIF_spi_n, "irq84"),
                OP_NET_CONNECT(MLB150_err_spi_n, "irq85"),
                OP_NET_CONNECT(PMU_analog_spi_n, "irq86"),
                OP_NET_CONNECT(GPT_spi_n, "irq87"),
                OP_NET_CONNECT(EPIT1_spi_n, "irq88"),
                OP_NET_CONNECT(EPIT2_spi_n, "irq89"),
                OP_NET_CONNECT(GPIO1_int7_spi_n, "irq90"),
                OP_NET_CONNECT(GPIO1_int6_spi_n, "irq91"),
                OP_NET_CONNECT(GPIO1_int5_spi_n, "irq92"),
                OP_NET_CONNECT(GPIO1_int4_spi_n, "irq93"),
                OP_NET_CONNECT(GPIO1_int3_spi_n, "irq94"),
                OP_NET_CONNECT(GPIO1_int2_spi_n, "irq95"),
                OP_NET_CONNECT(GPIO1_int1_spi_n, "irq96"),
                OP_NET_CONNECT(GPIO1_int0_spi_n, "irq97"),
                OP_NET_CONNECT(GPIO1_s0_15_spi_n, "irq98"),
                OP_NET_CONNECT(GPIO1_s16_31_spi_n, "irq99"),
                OP_NET_CONNECT(GPIO2_s0_15_spi_n, "irq100"),
                OP_NET_CONNECT(GPIO2_s16_31_spi_n, "irq101"),
                OP_NET_CONNECT(GPIO3_s0_15_spi_n, "irq102"),
                OP_NET_CONNECT(GPIO3_s16_31_spi_n, "irq103"),
                OP_NET_CONNECT(GPIO4_s0_15_spi_n, "irq104"),
                OP_NET_CONNECT(GPIO4_s16_31_spi_n, "irq105"),
                OP_NET_CONNECT(GPIO5_s0_15_spi_n, "irq106"),
                OP_NET_CONNECT(GPIO5_s16_31_spi_n, "irq107"),
                OP_NET_CONNECT(GPIO6_s0_15_spi_n, "irq108"),
                OP_NET_CONNECT(GPIO6_s16_31_spi_n, "irq109"),
                OP_NET_CONNECT(GPIO7_s0_15_spi_n, "irq110"),
                OP_NET_CONNECT(GPIO7_s16_31_spi_n, "irq111"),
                OP_NET_CONNECT(WDOG1_spi_n, "irq112"),
                OP_NET_CONNECT(WDOG2_spi_n, "irq113"),
                OP_NET_CONNECT(KPP_spi_n, "irq114"),
                OP_NET_CONNECT(PWM1_spi_n, "irq115"),
                OP_NET_CONNECT(PWM2_spi_n, "irq116"),
                OP_NET_CONNECT(PWM3_spi_n, "irq117"),
                OP_NET_CONNECT(PWM4_spi_n, "irq118"),
                OP_NET_CONNECT(CCM1_spi_n, "irq119"),
                OP_NET_CONNECT(CCM2_spi_n, "irq120"),
                OP_NET_CONNECT(GPC1_spi_n, "irq121"),
                OP_NET_CONNECT(SRC_spi_n, "irq123"),
                OP_NET_CONNECT(CPU_L2_spi_n, "irq124"),
                OP_NET_CONNECT(CPU_ParityCheckError_spi_n, "irq125"),
                OP_NET_CONNECT(CPU_Performance_Unit_spi_n, "irq126"),
                OP_NET_CONNECT(CPU_CTI_spi_n, "irq127"),
                OP_NET_CONNECT(SRC_wdog_spi_n, "irq128"),
                OP_NET_CONNECT(EPDC_spi_n, "irq129"),
                OP_NET_CONNECT(PXP_spi_n, "irq130"),
                OP_NET_CONNECT(MIPI_CSI1_spi_n, "irq132"),
                OP_NET_CONNECT(MIPI_CSI2_spi_n, "irq133"),
                OP_NET_CONNECT(MIPI_DSI_spi_n, "irq134"),
                OP_NET_CONNECT(MIPI_HSI_spi_n, "irq135"),
                OP_NET_CONNECT(SJC_spi_n, "irq136"),
                OP_NET_CONNECT(CAAM0_spi_n, "irq137"),
                OP_NET_CONNECT(CAAM1_spi_n, "irq138"),
                OP_NET_CONNECT(TZASC1_spi_n, "irq140"),
                OP_NET_CONNECT(TZASC2_spi_n, "irq141"),
                OP_NET_CONNECT(FLEXCAN1_spi_n, "irq142"),
                OP_NET_CONNECT(FLEXCAN2_spi_n, "irq143"),
                OP_NET_CONNECT(HDMI_spi_n, "irq147"),
                OP_NET_CONNECT(HDMICEC_spi_n, "irq148"),
                OP_NET_CONNECT(MLB150_irq0_31_spi_n, "irq149"),
                OP_NET_CONNECT(ENET_spi_n, "irq150"),
                OP_NET_CONNECT(ENET_timer_spi_n, "irq151"),
                OP_NET_CONNECT(PCIe1_spi_n, "irq152"),
                OP_NET_CONNECT(PCIe2_spi_n, "irq153"),
                OP_NET_CONNECT(PCIe3_spi_n, "irq154"),
                OP_NET_CONNECT(PCIe4_spi_n, "irq155"),
                OP_NET_CONNECT(DCIC1_spi_n, "irq156"),
                OP_NET_CONNECT(DCIC2_spi_n, "irq157"),
                OP_NET_CONNECT(MLB150_irq32_63_spi_n, "irq158"),
                OP_NET_CONNECT(PMU_digital_spi_n, "irq159")
            )
        ),
        0
    );

    // PSE PL310

    const char *PL310_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "L2CachePL310",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        PL310_path,
        "PL310",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0xa02000ULL, .addrHi=0xa02fffULL)
            )
        ),
        0
    );

    // PSE GPT

    const char *GPT_path = opVLNVString(
        0, // use the default VLNV path
        "nxp.ovpworld.org",
        0,
        "iMX6_GPT",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        GPT_path,
        "GPT",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x2098000ULL, .addrHi=0x2098fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(GPT_spi_n, "interrupt")
            )
        ),
        0
    );

    // PSE UART1

    const char *UART1_path = opVLNVString(
        0, // use the default VLNV path
        "nxp.ovpworld.org",
        0,
        "iMX6_UART",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        UART1_path,
        "UART1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x2020000ULL, .addrHi=0x2023fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(UART1_spi_n, "irq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_STRING_SET("outfile", "UART1.log")
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
            ,OP_PARAM_BOOL_SET("console", 1)
        )
    );

    // PSE UART2

    const char *UART2_path = opVLNVString(
        0, // use the default VLNV path
        "nxp.ovpworld.org",
        0,
        "iMX6_UART",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        UART2_path,
        "UART2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x21e8000ULL, .addrHi=0x21ebfffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(UART2_spi_n, "irq")
            )
        ),
        OP_PARAMS(
             OP_PARAM_STRING_SET("outfile", "UART2.log")
            ,OP_PARAM_BOOL_SET("finishOnDisconnect", 1)
            ,OP_PARAM_BOOL_SET("console", 0)
        )
    );

    // PSE CCM

    const char *CCM_path = opVLNVString(
        0, // use the default VLNV path
        "nxp.ovpworld.org",
        0,
        "iMX6_CCM",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        CCM_path,
        "CCM",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x20c4000ULL, .addrHi=0x20c4fffULL)
            )
        ),
        0
    );

    // PSE ANALOG

    const char *ANALOG_path = opVLNVString(
        0, // use the default VLNV path
        "nxp.ovpworld.org",
        0,
        "iMX6_Analog",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ANALOG_path,
        "ANALOG",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x20c8000ULL, .addrHi=0x20c8fffULL)
            )
        ),
        0
    );

    // PSE SRC

    const char *SRC_path = opVLNVString(
        0, // use the default VLNV path
        "nxp.ovpworld.org",
        0,
        "iMX6_SRC",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        SRC_path,
        "SRC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x20d8000ULL, .addrHi=0x20dbfffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(reset_A9_CPU0_n, "resetCore0"),
                OP_NET_CONNECT(reset_A9_CPU1_n, "resetCore1")
            )
        ),
        0
    );

    // PSE MMDC

    const char *MMDC_path = opVLNVString(
        0, // use the default VLNV path
        "nxp.ovpworld.org",
        0,
        "iMX6_MMDC",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        MMDC_path,
        "MMDC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x21b0000ULL, .addrHi=0x21b3fffULL)
            )
        ),
        0
    );

    // PSE GPIO1

    const char *GPIO1_path = opVLNVString(
        0, // use the default VLNV path
        "nxp.ovpworld.org",
        0,
        "iMX6_GPIO",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        GPIO1_path,
        "GPIO1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x209c000ULL, .addrHi=0x209ffffULL)
            )
        ),
        0
    );

    // PSE GPIO2

    const char *GPIO2_path = opVLNVString(
        0, // use the default VLNV path
        "nxp.ovpworld.org",
        0,
        "iMX6_GPIO",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        GPIO2_path,
        "GPIO2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x20a0000ULL, .addrHi=0x20a3fffULL)
            )
        ),
        0
    );

    // PSE GPIO3

    const char *GPIO3_path = opVLNVString(
        0, // use the default VLNV path
        "nxp.ovpworld.org",
        0,
        "iMX6_GPIO",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        GPIO3_path,
        "GPIO3",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x20a4000ULL, .addrHi=0x20a7fffULL)
            )
        ),
        0
    );

    // PSE GPIO4

    const char *GPIO4_path = opVLNVString(
        0, // use the default VLNV path
        "nxp.ovpworld.org",
        0,
        "iMX6_GPIO",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        GPIO4_path,
        "GPIO4",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x20a8000ULL, .addrHi=0x20abfffULL)
            )
        ),
        0
    );

    // PSE GPIO5

    const char *GPIO5_path = opVLNVString(
        0, // use the default VLNV path
        "nxp.ovpworld.org",
        0,
        "iMX6_GPIO",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        GPIO5_path,
        "GPIO5",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x20ac000ULL, .addrHi=0x20affffULL)
            )
        ),
        0
    );

    // PSE GPIO6

    const char *GPIO6_path = opVLNVString(
        0, // use the default VLNV path
        "nxp.ovpworld.org",
        0,
        "iMX6_GPIO",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        GPIO6_path,
        "GPIO6",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x20b0000ULL, .addrHi=0x20b3fffULL)
            )
        ),
        0
    );

    // PSE GPIO7

    const char *GPIO7_path = opVLNVString(
        0, // use the default VLNV path
        "nxp.ovpworld.org",
        0,
        "iMX6_GPIO",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        GPIO7_path,
        "GPIO7",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x20b4000ULL, .addrHi=0x20b7fffULL)
            )
        ),
        0
    );

    // PSE uSDHC1

    const char *uSDHC1_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uSDHC1_path,
        "uSDHC1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x02190000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE uSDHC2

    const char *uSDHC2_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uSDHC2_path,
        "uSDHC2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x02194000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE uSDHC3

    const char *uSDHC3_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uSDHC3_path,
        "uSDHC3",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x02198000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE uSDHC4

    const char *uSDHC4_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        uSDHC4_path,
        "uSDHC4",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x0219C000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE WDOG1

    const char *WDOG1_path = opVLNVString(
        0, // use the default VLNV path
        "nxp.ovpworld.org",
        0,
        "iMX6_WDOG",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        WDOG1_path,
        "WDOG1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x20bc000ULL, .addrHi=0x20bffffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(WDOG1_spi_n, "interrupt")
            )
        ),
        0
    );

    // PSE WDOG2

    const char *WDOG2_path = opVLNVString(
        0, // use the default VLNV path
        "nxp.ovpworld.org",
        0,
        "iMX6_WDOG",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        WDOG2_path,
        "WDOG2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x20c0000ULL, .addrHi=0x20c3fffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(WDOG2_spi_n, "interrupt")
            )
        ),
        0
    );

    // PSE EPDC

    const char *EPDC_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        EPDC_path,
        "EPDC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x020F4000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE PXP

    const char *PXP_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        PXP_path,
        "PXP",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x020F0000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE SDMA

    const char *SDMA_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        SDMA_path,
        "SDMA",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x020EC000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE DCIC2

    const char *DCIC2_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        DCIC2_path,
        "DCIC2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x020E8000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE DCIC1

    const char *DCIC1_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        DCIC1_path,
        "DCIC1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x020E4000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE IOMUXC

    const char *IOMUXC_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        IOMUXC_path,
        "IOMUXC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x020E0000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE PGC_ARM

    const char *PGC_ARM_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        PGC_ARM_path,
        "PGC_ARM",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x020DC2A0)
            ,OP_PARAM_UNS32_SET("portSize", 32)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE PGC_PU

    const char *PGC_PU_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        PGC_PU_path,
        "PGC_PU",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x020DC260)
            ,OP_PARAM_UNS32_SET("portSize", 32)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE EPIT2

    const char *EPIT2_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        EPIT2_path,
        "EPIT2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x020D4000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE EPIT1

    const char *EPIT1_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        EPIT1_path,
        "EPIT1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x020D0000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE SNVS_HP

    const char *SNVS_HP_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        SNVS_HP_path,
        "SNVS_HP",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x020CC000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE USBPHY2

    const char *USBPHY2_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        USBPHY2_path,
        "USBPHY2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x020CA000)
            ,OP_PARAM_UNS32_SET("portSize", 4096)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE USBPHY1

    const char *USBPHY1_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        USBPHY1_path,
        "USBPHY1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x020C9000)
            ,OP_PARAM_UNS32_SET("portSize", 4096)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE KPP

    const char *KPP_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        KPP_path,
        "KPP",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x020B8000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE CAN2

    const char *CAN2_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        CAN2_path,
        "CAN2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x02094000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE CAN1

    const char *CAN1_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        CAN1_path,
        "CAN1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x02090000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE PWM4

    const char *PWM4_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        PWM4_path,
        "PWM4",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x0208C000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE PWM3

    const char *PWM3_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        PWM3_path,
        "PWM3",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x02088000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE PWM2

    const char *PWM2_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        PWM2_path,
        "PWM2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x02084000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE PWM1

    const char *PWM1_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        PWM1_path,
        "PWM1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x02080000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE AIPS1_Cfg

    const char *AIPS1_Cfg_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        AIPS1_Cfg_path,
        "AIPS1_Cfg",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x0207C000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE SPBA

    const char *SPBA_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        SPBA_path,
        "SPBA",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x0203C000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE ASRC

    const char *ASRC_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ASRC_path,
        "ASRC",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x02034000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE SSI3

    const char *SSI3_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        SSI3_path,
        "SSI3",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x02030000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE SSI2

    const char *SSI2_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        SSI2_path,
        "SSI2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x0202C000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE SSI1

    const char *SSI1_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        SSI1_path,
        "SSI1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x02028000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE ESAI

    const char *ESAI_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ESAI_path,
        "ESAI",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x02024000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE eCSPI4

    const char *eCSPI4_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        eCSPI4_path,
        "eCSPI4",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x02014000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE eCSPI3

    const char *eCSPI3_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        eCSPI3_path,
        "eCSPI3",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x02010000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE eCSPI2

    const char *eCSPI2_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        eCSPI2_path,
        "eCSPI2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x0200C000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE eCSPI1

    const char *eCSPI1_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        eCSPI1_path,
        "eCSPI1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x02008000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE SPDIF

    const char *SPDIF_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        SPDIF_path,
        "SPDIF",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x02004000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE I2C4

    const char *I2C4_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        I2C4_path,
        "I2C4",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x021F8000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE UART5

    const char *UART5_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        UART5_path,
        "UART5",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x021F4000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE UART4

    const char *UART4_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        UART4_path,
        "UART4",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x021F0000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE UART3

    const char *UART3_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        UART3_path,
        "UART3",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x021EC000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE VDOA

    const char *VDOA_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        VDOA_path,
        "VDOA",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x021E4000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE MIPI_DSI

    const char *MIPI_DSI_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        MIPI_DSI_path,
        "MIPI_DSI",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x021E0000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE MIPI_CSI

    const char *MIPI_CSI_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        MIPI_CSI_path,
        "MIPI_CSI",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x021DC000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE AUDMUX

    const char *AUDMUX_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        AUDMUX_path,
        "AUDMUX",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x021D8000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE TZASC2

    const char *TZASC2_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        TZASC2_path,
        "TZASC2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x021D4000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE TZASC1

    const char *TZASC1_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        TZASC1_path,
        "TZASC1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x021D0000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE CSU

    const char *CSU_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        CSU_path,
        "CSU",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x021C0000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE OCOTP_CTRL

    const char *OCOTP_CTRL_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        OCOTP_CTRL_path,
        "OCOTP_CTRL",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x021BC000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE EIM

    const char *EIM_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        EIM_path,
        "EIM",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x021B8000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE MMDCp1

    const char *MMDCp1_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        MMDCp1_path,
        "MMDCp1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x021B4000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE ROMCP

    const char *ROMCP_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ROMCP_path,
        "ROMCP",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x021AC000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE I2C3

    const char *I2C3_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        I2C3_path,
        "I2C3",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x021A8000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE I2C2

    const char *I2C2_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        I2C2_path,
        "I2C2",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x021A4000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE I2C1

    const char *I2C1_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        I2C1_path,
        "I2C1",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x021A0000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE MLB150

    const char *MLB150_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        MLB150_path,
        "MLB150",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x0218C000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE ENET

    const char *ENET_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        ENET_path,
        "ENET",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x02188000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE USBOH3_USB

    const char *USBOH3_USB_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        USBOH3_USB_path,
        "USBOH3_USB",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x02184000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE USBOH3_PL301

    const char *USBOH3_PL301_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        USBOH3_PL301_path,
        "USBOH3_PL301",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x02180000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE AIPS2_Cfg

    const char *AIPS2_Cfg_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        AIPS2_Cfg_path,
        "AIPS2_Cfg",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x0217C000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE CAAM

    const char *CAAM_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        CAAM_path,
        "CAAM",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x02100000)
            ,OP_PARAM_UNS32_SET("portSize", 65536)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE IPU

    const char *IPU_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        IPU_path,
        "IPU",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x02600000)
            ,OP_PARAM_UNS32_SET("portSize", 4194304)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE GPU2D

    const char *GPU2D_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        GPU2D_path,
        "GPU2D",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x00134000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE GPU3D

    const char *GPU3D_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        GPU3D_path,
        "GPU3D",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x00130000)
            ,OP_PARAM_UNS32_SET("portSize", 16384)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE HDMI

    const char *HDMI_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        HDMI_path,
        "HDMI",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x00120000)
            ,OP_PARAM_UNS32_SET("portSize", 36864)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE APBH_DMA

    const char *APBH_DMA_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "trap",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        APBH_DMA_path,
        "APBH_DMA",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .dynamic=1)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("portAddress", 0x00110000)
            ,OP_PARAM_UNS32_SET("portSize", 8192)
            ,OP_PARAM_BOOL_SET("cbEnable", True)
        )
    );

    // PSE smartLoader

    const char *smartLoader_path = opVLNVString(
        0, // use the default VLNV path
        "arm.ovpworld.org",
        0,
        "SmartLoaderArmLinux",
        "1.0",
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        smartLoader_path,
        "smartLoader",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "mport", .addrLo=0x0ULL, .addrHi=0xffffffffULL)
            )
        ),
        OP_PARAMS(
             OP_PARAM_UNS32_SET("physicalbase", 0x10000000)
            ,OP_PARAM_UNS32_SET("memsize", 0x20000000)
            ,OP_PARAM_UNS32_SET("kerneladdr", 0x11000000)
        )
    );

    // PSE VBD0

    const char *VBD0_path = opVLNVString(
        0, // use the default VLNV path
        "ovpworld.org",
        0,
        "VirtioBlkMMIO",
        0,
        OP_PERIPHERAL,
        OP_VLNV_PRINT
    );

    opPeripheralNew(
        mi,
        VBD0_path,
        "VBD0",
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(pBus_b, "dma", .addrLo=0x0ULL, .addrHi=0xffffffffULL),
                OP_BUS_CONNECT(pBus_b, "bport1", .slave=1, .addrLo=0x21ff000ULL, .addrHi=0x21ff1ffULL)
            ),
            OP_NET_CONNECTIONS(
                OP_NET_CONNECT(VBD0_spi_n, "Interrupt")
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
        .vendor  = "nxp.ovpworld.org",
        .library = "module",
        .name    = "iMX6S",
        .version = "1.0"
    },
    .constructCB          = moduleConstructor,
    .preSimulateCB        = modulePreSimulate,
    .simulateCB           = moduleSimulateStart,
    .postSimulateCB       = modulePostSimulate,
    .destructCB           = moduleDestruct,
};

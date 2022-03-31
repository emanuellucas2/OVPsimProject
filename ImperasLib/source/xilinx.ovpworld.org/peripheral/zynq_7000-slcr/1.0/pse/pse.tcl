#
# Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
#
# The contents of this file are provided under the Software License
# Agreement that you accepted before downloading this file.
#
# This source forms part of the Software and can be used for educational,
# training, and demonstration purposes but cannot be used for derivative
# works except in cases where the derivative works require OVP technology
# to run.
#
# For open source models released under licenses that you can use for
# derivative works, please visit www.OVPworld.org or www.imperas.com
# for the location of the open source models.
#

set vendor  xilinx.ovpworld.org
set library peripheral
set name    zynq_7000-slcr
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor 

iadddocumentation  \
    -name Description  \
    -text "Zynq 7000 Platform System Level Control Registers (SLCR)"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "This model implements the full set of registers. Only behavior required for processor reset control is included."

iadddocumentation \
    -name Reference \
    -text "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)"

set port  bport1
set block ab
set size  0x0c00

imodeladdbusslaveport  -name ${port} -mustbeconnected -size ${size}
imodeladdaddressblock  -name ${block} -port ${port} -size ${size} -offset 0 -width 32

imodeladdlocalmemory -name buffer -addressblock ${port}/${block} -size ${size} \
                     -writefunction regNoDefinitionWrite -readfunction regNoDefinitionRead

set registers {
    SCL                         0x00000000 32 rw 0x00000000 -    auto 1      {LOCK 0 1} "Secure Configuration Lock"
    SLCR_LOCK                   0x00000004 32 rw 0x00000000 auto auto 0xffff - "SLCR Write Protection Lock"
    SLCR_UNLOCK                 0x00000008 32 rw 0x00000000 auto auto 0xffff - "SLCR Write Protection Unlock"
    SLCR_LOCKSTA                0x0000000C 32 r  0x00000001 auto  -   - - "SLCR Write Protection Status"
    ARM_PLL_CTRL                0x00000100 32 rw 0x0001A008 auto auto 0x007f01b {PLL_FDIV 12 7 PLL_BYPASS_FORCE 4 1 PLL_BYPASS_QUAL 3 1 PLL_PWRDWN 1 1 PLL_RESET 0 1} "ARM PLL Control"
    DDR_PLL_CTRL                0x00000104 32 rw 0x0001A008 -     -   - - "DDR PLL Control"
    IO_PLL_CTRL                 0x00000108 32 rw 0x0001A008 -     -   - - "IO PLL Control"
    PLL_STATUS                  0x0000010C 32 r  0x0000003F -     -   - - "PLL Status"
    ARM_PLL_CFG                 0x00000110 32 rw 0x00177EA0 auto auto 0x003ffff0 {LOC_CNT 12 10 PLL_CP 8 4 PLL_RES 4 4} "ARM PLL Configuration"
    DDR_PLL_CFG                 0x00000114 32 rw 0x00177EA0 -     -   - - "DDR PLL Configuration"
    IO_PLL_CFG                  0x00000118 32 rw 0x00177EA0 -     -   - - "IO PLL Configuration"
    ARM_CLK_CTRL                0x00000120 32 rw 0x1F000400 auto auto 0x1f003f30 {CPU_PERICLKACT 28 1  CPU_1XCLKACT 27 1 CPU_2XCLKACT 26 1 CPU_6OR3XCLKACT 25 1 CPU_4OR4XCLKACT 24 1 DIVISOR 8 6 SRCSEL 4 2 } "CPU Clock Control"
    DDR_CLK_CTRL                0x00000124 32 rw 0x18400003 -     -   - - "DDR Clock Control"
    DCI_CLK_CTRL                0x00000128 32 rw 0x01E03201 -     -   - - "DCI clock control"
    APER_CLK_CTRL               0x0000012C 32 rw 0x01FFCCCD -     -   - - "AMBA Peripheral Clock Control"
    USB0_CLK_CTRL               0x00000130 32 rw 0x00101941 -     -   - - "USB 0 ULPI Clock Control"
    USB1_CLK_CTRL               0x00000134 32 rw 0x00101941 -     -   - - "USB 1 ULPI Clock Control"
    GEM0_RCLK_CTRL              0x00000138 32 rw 0x00000001 -     -   - - "GigE 0 Rx Clock and Rx Signals Select"
    GEM1_RCLK_CTRL              0x0000013C 32 rw 0x00000001 -     -   - - "GigE 1 Rx Clock and Rx Signals Select"
    GEM0_CLK_CTRL               0x00000140 32 rw 0x00003C01 -     -   - - "GigE 0 Ref Clock Control"
    GEM1_CLK_CTRL               0x00000144 32 rw 0x00003C01 -     -   - - "GigE 1 Ref Clock Control"
    SMC_CLK_CTRL                0x00000148 32 rw 0x00003C21 -     -   - - "SMC Ref Clock Control"
    LQSPI_CLK_CTRL              0x0000014C 32 rw 0x00002821 -     -   - - "Quad SPI Ref Clock Control"
    SDIO_CLK_CTRL               0x00000150 32 rw 0x00001E03 -     -   - - "SDIO Ref Clock Control"
    UART_CLK_CTRL               0x00000154 32 rw 0x00003F03 -     -   - - "UART Ref Clock Control"
    SPI_CLK_CTRL                0x00000158 32 rw 0x00003F03 -     -   - - "SPI Ref Clock Control"
    CAN_CLK_CTRL                0x0000015C 32 rw 0x00501903 -     -   - - "CAN Ref Clock Control"
    CAN_MIOCLK_CTRL             0x00000160 32 rw 0x00000000 -     -   - - "CAN MIO Clock Control"
    DBG_CLK_CTRL                0x00000164 32 rw 0x00000F03 -     -   - - "SoC Debug Clock Control"
    PCAP_CLK_CTRL               0x00000168 32 rw 0x00000F01 -     -   - - "PCAP Clock Control"
    TOPSW_CLK_CTRL              0x0000016C 32 rw 0x00000000 -     -   - - "Central Interconnect Clock Control"
    FPGA0_CLK_CTRL              0x00000170 32 rw 0x00101800 -     -   - - "PL Clock 0 Output control"
    FPGA0_THR_CTRL              0x00000174 32 rw 0x00000000 -     -   - - "PL Clock 0 Throttle control"
    FPGA0_THR_CNT               0x00000178 32 rw 0x00000000 -     -   - - "PL Clock 0 Throttle Count control"
    FPGA0_THR_STA               0x0000017C 32 r  0x00010000 -     -   - - "PL Clock 0 Throttle Status read"
    FPGA1_CLK_CTRL              0x00000180 32 rw 0x00101800 -     -   - - "PL Clock 1 Output control"
    FPGA1_THR_CTRL              0x00000184 32 rw 0x00000000 -     -   - - "PL Clock 1 Throttle control"
    FPGA1_THR_CNT               0x00000188 32 rw 0x00000000 -     -   - - "PL Clock 1 Throttle Count"
    FPGA1_THR_STA               0x0000018C 32 r  0x00010000 -     -   - - "PL Clock 1 Throttle Status control"
    FPGA2_CLK_CTRL              0x00000190 32 rw 0x00101800 -     -   - - "PL Clock 2 output control"
    FPGA2_THR_CTRL              0x00000194 32 rw 0x00000000 -     -   - - "PL Clock 2 Throttle Control"
    FPGA2_THR_CNT               0x00000198 32 rw 0x00000000 -     -   - - "PL Clock 2 Throttle Count"
    FPGA2_THR_STA               0x0000019C 32 r  0x00010000 -     -   - - "PL Clock 2 Throttle Status"
    FPGA3_CLK_CTRL              0x000001A0 32 rw 0x00101800 -     -   - - "PL Clock 3 output control"
    FPGA3_THR_CTRL              0x000001A4 32 rw 0x00000000 -     -   - - "PL Clock 3 Throttle Control"
    FPGA3_THR_CNT               0x000001A8 32 rw 0x00000000 -     -   - - "PL Clock 3 Throttle Count"
    FPGA3_THR_STA               0x000001AC 32 r  0x00010000 -     -   - - "PL Clock 3 Throttle Status"
    CLK_621_TRUE                0x000001C4 32 rw 0x00000001 -    auto 0x00000001 {CLK_621 0 1} "CPU Clock Ratio Mode select"
    PSS_RST_CTRL                0x00000200 32 rw 0x00000000 -    auto  - - "PS Software Reset Control"
    DDR_RST_CTRL                0x00000204 32 rw 0x00000000 -     -   - - "DDR Software Reset Control"
    TOPSW_RST_CTRL              0x00000208 32 rw 0x00000000 -     -   - - "Central Interconnect Reset Control"
    DMAC_RST_CTRL               0x0000020C 32 rw 0x00000000 -     -   - - "DMAC Software Reset Control"
    USB_RST_CTRL                0x00000210 32 rw 0x00000000 -     -   - - "USB Software Reset Control"
    GEM_RST_CTRL                0x00000214 32 rw 0x00000000 -     -   - - "Gigabit Ethernet SW Reset Control"
    SDIO_RST_CTRL               0x00000218 32 rw 0x00000000 -     -   - - "SDIO Software Reset Control"
    SPI_RST_CTRL                0x0000021C 32 rw 0x00000000 -     -   - - "SPI Software Reset Control"
    CAN_RST_CTRL                0x00000220 32 rw 0x00000000 -     -   - - "CAN Software Reset Control"
    I2C_RST_CTRL                0x00000224 32 rw 0x00000000 -     -   - - "I2C Software Reset Control"
    UART_RST_CTRL               0x00000228 32 rw 0x00000000 -     -   - - "UART Software Reset Control"
    GPIO_RST_CTRL               0x0000022C 32 rw 0x00000000 -     -   - - "GPIO Software Reset Control"
    LQSPI_RST_CTRL              0x00000230 32 rw 0x00000000 -     -   - - "Quad SPI Software Reset Control"
    SMC_RST_CTRL                0x00000234 32 rw 0x00000000 -     -   - - "SMC Software Reset Control"
    OCM_RST_CTRL                0x00000238 32 rw 0x00000000 -     -   - - "OCM Software Reset Control"
    FPGA_RST_CTRL               0x00000240 32 rw 0x01F33F0F -     -   - - "FPGA Software Reset Control"
    A9_CPU_RST_CTRL             0x00000244 32 rw 0x00000000 auto auto - {PERI_RST 8 1 A9_CLKSTOP1 5 1 A9_CLKSTOP0 4 1 A9_RST1 1 1 A9_RST0 0 1} "CPU Reset and Clock control"
    RS_AWDT_CTRL                0x0000024C 32 rw 0x00000000 -     -   - - "Watchdog Timer Reset Control"
    REBOOT_STATUS               0x00000258 32 rw 0x00400000 -     -   - - "Reboot Status, persistent"
    BOOT_MODE                   0x0000025C 32 rw 0x00000000 -     -   - - "Boot Mode Strapping Pins"
    APU_CTRL                    0x00000300 32 rw 0x00000000 -    auto - - "APU Control"
    WDT_CLK_SEL                 0x00000304 32 rw 0x00000000 -    auto - - "SWDT clock source select"
    TZ_OCM_RAM0                 0x00000400 32 rw 0x00000000 -     -   -      - "OCM RAM TrustZone Config 0"
    TZ_OCM_RAM1                 0x00000404 32 rw 0x00000000 -     -   -      - "OCM RAM TrustZone Config 1"
    TZ_OCM                      0x00000408 32 rw 0x00000000 -     -   -      - "OCM ROM TrustZone Config"
    TZ_DDR_RAM                  0x00000430 32 rw 0x00000000 -     -   0x0001 - "DDR RAM TrustZone Config"
    TZ_DMA_NS                   0x00000440 32 rw 0x00000000 -     -   0xffff - "DMAC TrustZone Config"
    TZ_DMA_IRQ_NS               0x00000444 32 rw 0x00000000 -     -   0xffff - "DMAC TrustZone Config for Interrupts"
    TZ_DMA_PERIPH_NS            0x00000448 32 rw 0x00000000 -     -   0x0001 - "DMAC TrustZone Config for Peripherals"
    TZ_GEM                      0x00000450 32 rw 0x00000000 -     -   0x0003 - "Ethernet TrustZone Config"
    TZ_SDIO                     0x00000454 32 rw 0x00000000 -     -   0x0003 - "SDIO TrustZone Config"
    TZ_USB                      0x00000458 32 rw 0x00000000 -     -   0x0003 - "USB TrustZone Config"
    TZ_FPGA_M                   0x00000484 32 rw 0x00000000 -     -   0x0003 - "FPGA master ports TrustZone Disable"
    TZ_FPGA_AFI                 0x00000488 32 rw 0x00000000 -     -   0x000f - "FPGA AFI AXI ports TrustZone Disable"	
    PSS_IDCODE                  0x00000530 32 r  0x13747093 -     -   - {REV 28 4 FAM 21 7 SUB 17 4 DEV 12 5 MAN 1 11} "PS IDCODE (REVISION=1 FAMILY=0x1b SUBFAMILY=0x9 DEVICE=0x11 (7z045) MANUFACTURE_ID=0x49"
    DDR_URGENT                  0x00000600 32 rw 0x00000000 -     -   - - "DDR Urgent Control"
    DDR_CAL_START               0x0000060C 32 rw 0x00000000 -     -   - - "DDR Calibration Start Triggers"
    DDR_REF_START               0x00000614 32 rw 0x00000000 -     -   - - "DDR Refresh Start Triggers"
    DDR_CMD_STA                 0x00000618 32 rw 0x00000000 -     -   - - "DDR Command Store Status"
    DDR_URGENT_SEL              0x0000061C 32 rw 0x00000000 -     -   - - "DDR Urgent Select"
    DDR_DFI_STATUS              0x00000620 32 rw 0x00000000 -     -   - - "DDR DFI status"
    MIO_PIN_00                  0x00000700 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 0 Control"
    MIO_PIN_01                  0x00000704 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 1 Control"
    MIO_PIN_02                  0x00000708 32 rw 0x00000601 -     -   0x3fff - "MIO Pin 2 Control"
    MIO_PIN_03                  0x0000070C 32 rw 0x00000601 -     -   0x3fff - "MIO Pin 3 Control"
    MIO_PIN_04                  0x00000710 32 rw 0x00000601 -     -   0x3fff - "MIO Pin 4 Control"
    MIO_PIN_05                  0x00000714 32 rw 0x00000601 -     -   0x3fff - "MIO Pin 5 Control"
    MIO_PIN_06                  0x00000718 32 rw 0x00000601 -     -   0x3fff - "MIO Pin 6 Control"
    MIO_PIN_07                  0x0000071C 32 rw 0x00000601 -     -   0x3fff - "MIO Pin 7 Control"
    MIO_PIN_08                  0x00000720 32 rw 0x00000601 -     -   0x3fff - "MIO Pin 8 Control"
    MIO_PIN_09                  0x00000724 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 9 Control"
    MIO_PIN_10                  0x00000728 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 10 Control"
    MIO_PIN_11                  0x0000072C 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 11 Control"
    MIO_PIN_12                  0x00000730 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 12 Control"
    MIO_PIN_13                  0x00000734 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 13 Control"
    MIO_PIN_14                  0x00000738 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 14 Control"
    MIO_PIN_15                  0x0000073C 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 15 Control"
    MIO_PIN_16                  0x00000740 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 16 Control"
    MIO_PIN_17                  0x00000744 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 17 Control"
    MIO_PIN_18                  0x00000748 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 18 Control"
    MIO_PIN_19                  0x0000074C 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 19 Control"
    MIO_PIN_20                  0x00000750 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 20 Control"
    MIO_PIN_21                  0x00000754 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 21 Control"
    MIO_PIN_22                  0x00000758 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 22 Control"
    MIO_PIN_23                  0x0000075C 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 23 Control"
    MIO_PIN_24                  0x00000760 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 24 Control"
    MIO_PIN_25                  0x00000764 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 25 Control"
    MIO_PIN_26                  0x00000768 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 26 Control"
    MIO_PIN_27                  0x0000076C 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 27 Control"
    MIO_PIN_28                  0x00000770 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 28 Control"
    MIO_PIN_29                  0x00000774 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 29 Control"
    MIO_PIN_30                  0x00000778 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 30 Control"
    MIO_PIN_31                  0x0000077C 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 31 Control"
    MIO_PIN_32                  0x00000780 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 32 Control"
    MIO_PIN_33                  0x00000784 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 33 Control"
    MIO_PIN_34                  0x00000788 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 34 Control"
    MIO_PIN_35                  0x0000078C 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 35 Control"
    MIO_PIN_36                  0x00000790 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 36 Control"
    MIO_PIN_37                  0x00000794 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 37 Control"
    MIO_PIN_38                  0x00000798 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 38 Control"
    MIO_PIN_39                  0x0000079C 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 39 Control"
    MIO_PIN_40                  0x000007A0 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 40 Control"
    MIO_PIN_41                  0x000007A4 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 41 Control"
    MIO_PIN_42                  0x000007A8 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 42 Control"
    MIO_PIN_43                  0x000007AC 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 43 Control"
    MIO_PIN_44                  0x000007B0 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 44 Control"
    MIO_PIN_45                  0x000007B4 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 45 Control"
    MIO_PIN_46                  0x000007B8 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 46 Control"
    MIO_PIN_47                  0x000007BC 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 47 Control"
    MIO_PIN_48                  0x000007C0 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 48 Control"
    MIO_PIN_49                  0x000007C4 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 49 Control"
    MIO_PIN_50                  0x000007C8 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 50 Control"
    MIO_PIN_51                  0x000007CC 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 51 Control"
    MIO_PIN_52                  0x000007D0 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 52 Control"
    MIO_PIN_53                  0x000007D4 32 rw 0x00001601 -     -   0x3fff - "MIO Pin 53 Control"
    MIO_LOOPBACK                0x00000804 32 rw 0x00000000 -     -   - - "Loopback function within MIO"
    MIO_MST_TRI0                0x0000080C 32 rw 0xFFFFFFFF -     -   - - "MIO pin Tri-state Enables, 31:0"
    MIO_MST_TRI1                0x00000810 32 rw 0x003FFFFF -     -   - - "MIO pin Tri-state Enables, 53:32"
    SD0_WP_CD_SEL               0x00000830 32 rw 0x00000000 -     -   - - "SDIO 0 WP CD select"
    SD1_WP_CD_SEL               0x00000834 32 rw 0x00000000 -     -   - - "SDIO 1 WP CD select"
    LVL_SHFTR_EN                0x00000900 32 rw 0x00000000 -     -   - - "Level Shifters Enable"
    OCM_CFG                     0x00000910 32 rw 0x0000000f -    auto - {OCM3 3 1 OCM2 2 1 OCM1 1 1 OCM0 0 1} "OCM Address Mapping (user mode reset config)"
    Reserved                    0x00000A1C 32 rw 0x00010101 -     -   - - "Reserved"
    GPIOB_CTRL                  0x00000B00 32 rw 0x00000000 -     -   - - "PS IO Buffer Control"
    GPIOB_CFG_CMOS18            0x00000B04 32 rw 0x00000000 -     -   - - "MIO GPIOB CMOS 1.8V config"
    GPIOB_CFG_CMOS25            0x00000B08 32 rw 0x00000000 -     -   - - "MIO GPIOB CMOS 2.5V config"
    GPIOB_CFG_CMOS33            0x00000B0C 32 rw 0x00000000 -     -   - - "MIO GPIOB CMOS 3.3V config"
    GPIOB_CFG_HSTL              0x00000B14 32 rw 0x00000000 -     -   - - "MIO GPIOB HSTL config"
    GPIOB_DRVR_BIAS_CTRL        0x00000B18 32 rw 0x00000000 -     -   - - "MIO GPIOB Driver Bias Control"
    DDRIOB_ADDR0                0x00000B40 32 rw 0x00000800 -     -   - - "DDR IOB Config for A[14:0], CKE and DRST_B"
    DDRIOB_ADDR1                0x00000B44 32 rw 0x00000800 -     -   - - "DDR IOB Config for BA[2:0], ODT, CS_B, WE_B, RAS_B and CAS_B"
    DDRIOB_DATA0                0x00000B48 32 rw 0x00000800 -     -   - - "DDR IOB Config for Data 15:0"
    DDRIOB_DATA1                0x00000B4C 32 rw 0x00000800 -     -   - - "DDR IOB Config for Data 31:16"
    DDRIOB_DIFF0                0x00000B50 32 rw 0x00000800 -     -   - - "DDR IOB Config for DQS 1:0"
    DDRIOB_DIFF1                0x00000B54 32 rw 0x00000800 -     -   - - "DDR IOB Config for DQS 3:2"
    DDRIOB_CLOCK                0x00000B58 32 rw 0x00000800 -     -   - - "DDR IOB Config for Clock Output"
    DDRIOB_DRIVE_SLEW_ADDR      0x00000B5C 32 rw 0x00000000 -     -   - - "Drive and Slew controls for Address and Command pins of the DDR Interface" 
    DDRIOB_DRIVE_SLEW_DATA      0x00000B60 32 rw 0x00000000 -     -   - - "Drive and Slew controls for DQ pins of the DDR Interface"
    DDRIOB_DRIVE_SLEW_DIFF      0x00000B64 32 rw 0x00000000 -     -   - - "Drive and Slew controls for DQS pins of the DDR Interface"
    DDRIOB_DRIVE_SLEW_CLOCK     0x00000B68 32 rw 0x00000000 -     -   - - "Drive and Slew controls for Clock pins of the DDR Interface"
    DDRIOB_DDR_CTRL             0x00000B6C 32 rw 0x00000000 -     -   - - "DDR IOB Buffer Control"
    DDRIOB_DCI_CTRL             0x00000B70 32 rw 0x00000020 -     -   - - "DDR IOB DCI Config"
    DDRIOB_DCI_STATUS           0x00000B74 32 rw 0x00000000 -     -   - - "DDR IO Buffer DCI Status"
}

foreach {rname roffset rsize raccess reset readFunc writeFunc writeMask bits description} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}
  if {$rsize != "32"} {
      set rsize 32
#      puts "Register $rname is not 32-bits ignored"
#      continue
  }

  set command "imodeladdmmregister -addressblock ${port}/${block} -name $rname -width 32 -offset $roffset -access $raccess"
  if { $readFunc == "-" } {
    set defaultcb 1
  } elseif { $readFunc == "auto" } {
    set command "${command} -readfunction Read${rname}"
  } else {
    set command "${command} -readfunction $readFunc"
  }
  
  if { $writeFunc == "-" } {
    set defaultcb 1
  } elseif { $writeFunc == "auto" } {
    set command "${command} -writefunction Write${rname}"
  } else {
    set command "${command} -writefunction $writeFunc"
  }

  if { $writeMask != "-" } {
    set command "${command} -writemask $writeMask"
  }

  eval $command
  
  if { $description != "-" } {
      iadddocumentation  -handle ${port}/${block}/$rname \
                         -name Description  \
                         -text $description
  }

  if { $bits != "-" } {
    foreach { n o w } $bits {
        imodeladdfield -mmregister $port/$block/$rname -bitoffset $o -width $w -name $n
    }
  }
  
  imodeladdreset -mmregister ${port}/${block}/$rname -name resetNet -value $reset
}

# reset signals to A9 CPU0 and CPU1
imodeladdnetport -type output -name A9_RST0
imodeladdnetport -type output -name A9_RST1

# Define bus slave input port
imodeladdbusslaveport  -name spOCMDDR -remappable -mustbeconnected -addresswidth 32

# Define bus master output ports OCM and DDR
imodeladdbusmasterport -name mpOCM -addresswidth 32 -mustbeconnected
imodeladdbusmasterport -name mpDDR -addresswidth 32 -mustbeconnected

# the SLCR registers are unlocked by writing this code (default in spec P1587)
imodeladdformal -name lockcode   -type Uns32 -defaultvalue 0x767b
imodeladdformal -name unlockcode -type Uns32 -defaultvalue 0xdf0d

# the device code (default 7z010 = 0x02) 
imodeladdformal -name deviceid  -type Uns32 -defaultvalue 2
# the device revision (default 1) 
imodeladdformal -name devicerev -type Uns32 -defaultvalue 1

# the Master clock (PS_CLK) frequency (default 33 MHz)
set defaultPSClock 33
imodeladdformal -name psclock -type Uns32 -defaultvalue ${defaultPSClock}
iadddocumentation -name Description -text "Define the master clock (PS_CLK) frequency in MHz (default ${defaultPSClock})"

# the Master clock (PS_CLK) frequency (default 33 MHz)
set defaultCPUMIPSRATE 500
imodeladdformal -name armmips -type Uns32 -defaultvalue ${defaultCPUMIPSRATE}
iadddocumentation -name Description -text "Define ARM CPU MIPS Rate in MIPS (default ${defaultCPUMIPSRATE})"

# define the deration to apply to the ARM Processor
imodeladdnetport -type output -name ARM1Deration
imodeladdnetport -type output -name ARM0Deration

# the BOOT_MODE setting (default 
# 0-2 : Boot Device : 4 => NAND
# 3   : JTAG chain  : 0 => cascade mode
# 4   : PLL         : 0 => enabled

set defaultBOOTMODE 0x04
imodeladdformal -name bootmode -type Uns32 -defaultvalue ${defaultBOOTMODE}
iadddocumentation -name Description -text "Define BOOT_MODE value (default ${defaultBOOTMODE})"

imodeladdformal -name clockcontroldisable -type Boolean
iadddocumentation -name Description -text "Disable change to ARM processor operating frequency when ARM PLL or clock control registers are modified."

 

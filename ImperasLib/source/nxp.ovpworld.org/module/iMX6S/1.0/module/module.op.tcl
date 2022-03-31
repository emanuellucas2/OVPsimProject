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

set desc "This module implements the NXP i.MX 6 Solo application processor
          The i.MX6S integrates a single ARM Cortex-A9 MPCore application processor, memories and peripherals."

set limitations1 "Some of the peripherals are register-only, non-functional models. See the individual peripheral model documentation for details."

set reference1 "i.MX 6Solo/6DualLite Applications Processor Reference Manual (IMX6SDLRM_Ref_Manual.pdf)"
set reference2 "From: https://www.nxp.com/products/microcontrollers-and-processors/arm-based-processors-and-mcus/i.mx-applications-processors/i.mx-6-processors/i.mx-6solo-processors-single-core-multimedia-3d-graphics-arm-cortex-a9-core:i.MX6S"

set license "Open Source Apache 2.0"

# Setup variables for platform info
set vendor  nxp.ovpworld.org
set library module
set name    iMX6S
set version 1.0

#
# Start new platform creation
#
ihwnew -name $name -vendor $vendor -library $library -version $version -stoponctrlc -purpose module -releasestatus ovp
iadddocumentation -name Licensing   -text $license
iadddocumentation -name Description -text $desc
iadddocumentation -name Limitations -text $limitations1
iadddocumentation -name Reference   -text $reference1
iadddocumentation -name Reference   -text $reference2

#
# pBus
#
ihwaddbus -instancename pBus  -addresswidth 32

#
# Processor
#
ihwaddprocessor -instancename cpu -type arm -vendor arm.ovpworld.org -version 1.0 \
                -endian little \
                -simulateexceptions \
                -mips 800

ihwconnect      -instancename cpu -bus pBus -busmasterport INSTRUCTION
ihwconnect      -instancename cpu -bus pBus -busmasterport DATA

ihwsetparameter -handle       cpu -name variant        -value Cortex-A9MPx1 -type enum
#ihwsetparameter -handle       cpu -name variant        -value Cortex-A9MPx2 -type enum
ihwsetparameter -handle       cpu -name compatibility  -value ISA           -type enum
ihwsetparameter -handle       cpu -name UAL            -value 1             -type boolean
ihwsetparameter -handle       cpu -name override_CBAR  -value 0x00a00000    -type Uns32
ihwsetparameter -handle       cpu -name override_MIDR  -value 0x411fc090    -type Uns32
# GIC requires 128 interrupt lines
ihwsetparameter -handle       cpu -name override_GICD_TYPER_ITLines -value 4 -type uns32

# 0x020DC000 0x020DC25F        GPC - power on behaviour and interrupt monitor
ihwaddperipheral -instancename GPC -type iMX6_GPC -vendor nxp.ovpworld.org
ihwconnect       -instancename GPC -bus pBus  -busslaveport bport1 -loaddress 0x020DC000 -hiaddress 0x020DC25F

# Connect processor interrupts
set spiInterruptList "
  32 IOMUXC 33 DAP 34 SDMA 35 VPU 36 SNVS 37 IPU 38 IPU1
  41 GPU3D 42 R2D 44 VPU_jpeg 45 APBH 46 EIM 47 BCH 48 GPMI 49 DTCP
  50 VDOA 51 SNVS_consolidated 52 SNVS_security 53 CSU
  58 UART1 59 UART2 60 UART3 61 UART4 62 UART5
  63 eCSPI1 64 eCSPI2 65 eCSPI3 66 eCSPI4
  67 I2C4 68 I2C1 69 I2C2 70 I2C3
  72 USBHost1 73 USBHost2 74 USBHost3 75 USBOTG 76 USB_PHYUTMI0 77 USB_PHYUTMI1
  78 SSI1 79 SSI2 80 SSI3 81 TMTS
  82 ASRC 83 ESAI 84 SPDIF 85 MLB150_err 86 PMU_analog 87 GPT 88 EPIT1 89 EPIT2
  90 GPIO1_int7 91 GPIO1_int6 92 GPIO1_int5 93 GPIO1_int4 94 GPIO1_int3 95 GPIO1_int2
  96 GPIO1_int1 97 GPIO1_int0 98 GPIO1_s0_15 99 GPIO1_s16_31 100 GPIO2_s0_15 101 GPIO2_s16_31
 102 GPIO3_s0_15 103 GPIO3_s16_31 104 GPIO4_s0_15 105 GPIO4_s16_31 106 GPIO5_s0_15 107 GPIO5_s16_31
 108 GPIO6_s0_15 109 GPIO6_s16_31 110 GPIO7_s0_15 111 GPIO7_s16_31 112 WDOG1 113 WDOG2
 114 KPP 115 PWM1 116 PWM2 117 PWM3 118 PWM4 119 CCM1 120 CCM2 121 GPC1 123 SRC
 124 CPU_L2 125 CPU_ParityCheckError 126 CPU_Performance_Unit 127 CPU_CTI 128 SRC_wdog
 129 EPDC 130 PXP 132 MIPI_CSI1 133 MIPI_CSI2 134 MIPI_DSI 135 MIPI_HSI 136 SJC
 137 CAAM0 138 CAAM1 140 TZASC1 141 TZASC2 142 FLEXCAN1 143 FLEXCAN2 147 HDMI 148 HDMICEC
 149 MLB150_irq0_31 150 ENET 151 ENET_timer
 152 PCIe1 153 PCIe2 154 PCIe3 155 PCIe4 156 DCIC1 157 DCIC2 158 MLB150_irq32_63 159 PMU_digital"
# SDHC device replaced with Virtio block device
#54 uSDHC1 55 uSDHC2 56 uSDHC3 57 uSDHC4
foreach {spi name} ${spiInterruptList} {
    ihwaddnet -instancename ${name}_spi
    ihwconnect -instancename cpu  -netport SPI${spi} -net ${name}_spi
    # the connections also go to GPC for wake-up generation and monitor
    ihwconnect -instancename GPC  -netport irq${spi} -net ${name}_spi
}

#
# Reset connections
#
ihwaddnet  -instancename reset_A9_CPU0
ihwaddnet  -instancename reset_A9_CPU1
ihwconnect -instancename cpu -netport reset_CPU0 -net reset_A9_CPU0
# When a Cortex-A9MPx2 this should be connected
#ihwconnect -instancename cpu -netport reset_CPU1 -net reset_A9_CPU1

#
# Memory
#

# 0x00900000    0x0091ffff      OCRAM - 0.125 MB
ihwaddmemory -instancename OCRAM      -type ram
ihwconnect   -instancename OCRAM      -bus pBus -busslaveport  sp1 -loaddress 0x00900000 -hiaddress 0x0091ffff

# 0x08000000    0x0fffffff      EIM NOR/SRAM - 128 MB
ihwaddmemory -instancename EIM-RAM    -type ram
ihwconnect   -instancename EIM-RAM    -bus pBus -busslaveport  sp1 -loaddress 0x08000000 -hiaddress 0x0fffffff

# 0x10000000    0x2fffffff      DRAM - 512 MB
ihwaddmemory -instancename DRAM       -type ram
ihwconnect   -instancename DRAM       -bus pBus -busslaveport  sp1 -loaddress 0x10000000 -hiaddress 0x2fffffff

#
# System 
#

# 0x00a02000    0x00a02fff     PL310 L2 Cache Controller
ihwaddperipheral -instancename PL310 -type L2CachePL310 -vendor arm.ovpworld.org
ihwconnect       -instancename PL310 -bus pBus  -busslaveport bport1 -loaddress 0x00a02000 -hiaddress 0x00a02fff

#
# AIPS-1 ARM IP Bus Memory Mapped Devices
#

# 0x02098000    0x02098fff     GPT General Purpose Timer
ihwaddperipheral -instancename GPT -type iMX6_GPT -vendor nxp.ovpworld.org
ihwconnect       -instancename GPT -netport interrupt -net GPT_spi
ihwconnect       -instancename GPT -bus pBus  -busslaveport bport1 -loaddress 0x02098000 -hiaddress 0x02098fff

# Add the 2 UART devices (only these are accessed)
set uartList "UART1  0x02020000 0x02023FFF 1
              UART2  0x021E8000 0x021EBFFF 0"
foreach {name low high cnsl} ${uartList} {
    ihwaddperipheral -instancename $name -type iMX6_UART -vendor nxp.ovpworld.org
    ihwconnect       -instancename $name -bus pBus -busslaveport bport1 -loaddress $low -hiaddress $high
    ihwconnect       -instancename $name  -netport irq -net ${name}_spi
    ihwsetparameter  -handle       $name  -name outfile            -value ${name}.log -type string
    ihwsetparameter  -handle       $name  -name finishOnDisconnect -value 1           -type boolean
    ihwsetparameter  -handle       $name  -name console            -value ${cnsl}     -type boolean
}

# 0x020c4000    0x020c4fff     CCM Clock Controller Module
ihwaddperipheral -instancename CCM -type iMX6_CCM -vendor nxp.ovpworld.org
ihwconnect       -instancename CCM -bus pBus  -busslaveport bport1 -loaddress 0x020c4000 -hiaddress 0x020c4fff

# 0x020c8000    0x020c8fff     ANALOG (PLLs, PFDs, Regulators, LDOs, Temp Sensor) Registers
ihwaddperipheral -instancename ANALOG -type iMX6_Analog -vendor nxp.ovpworld.org
ihwconnect       -instancename ANALOG -bus pBus  -busslaveport bport1 -loaddress 0x020c8000 -hiaddress 0x020c8fff

# 0x020d8000    0x020d8fff     SRC System Reset Control - power on reset behaviour
ihwaddperipheral -instancename SRC -type iMX6_SRC -vendor nxp.ovpworld.org
ihwconnect       -instancename SRC -bus pBus  -busslaveport bport1 -loaddress 0x020d8000 -hiaddress 0x020dbfff
ihwconnect       -instancename SRC -netport resetCore0 -net reset_A9_CPU0
ihwconnect       -instancename SRC -netport resetCore1 -net reset_A9_CPU1


# 0x021B0000 0x021B3FFF        MMDC - power saving enable behaviour
ihwaddperipheral -instancename MMDC -type iMX6_MMDC -vendor nxp.ovpworld.org
ihwconnect       -instancename MMDC -bus pBus  -busslaveport bport1 -loaddress 0x021B0000 -hiaddress 0x021B3FFF


# Add the 6 GPIO devices
set gpioList "GPIO1 0x0209C000 0x0209FFFF
              GPIO2 0x020A0000 0x020A3FFF
              GPIO3 0x020A4000 0x020A7FFF
              GPIO4 0x020A8000 0x020ABFFF
              GPIO5 0x020AC000 0x020AFFFF
              GPIO6 0x020B0000 0x020B3FFF
              GPIO7 0x020B4000 0x020B7FFF"
foreach {name low high} ${gpioList} {
    ihwaddperipheral -instancename $name -type iMX6_GPIO -vendor nxp.ovpworld.org
    ihwconnect       -instancename $name -bus pBus -busslaveport bport1 -loaddress $low -hiaddress $high
}

# Add the 4 SDHC devices
set sdhcList "uSDHC1 0x02190000 0x02193FFF
              uSDHC2 0x02194000 0x02197FFF
              uSDHC3 0x02198000 0x0219BFFF
              uSDHC4 0x0219C000 0x0219FFFF"
foreach {name low high} ${sdhcList} {
    # this model is not working - replaced with Virtio block device
    #ihwaddperipheral -instancename $name -type iMX6_SDHC -vendor nxp.ovpworld.org
    #ihwconnect       -instancename $name -bus pBus -busslaveport bport1 -loaddress $low -hiaddress $high
    #ihwconnect       -instancename $name -netport interrupt -net ${name}_spi
    #ihwconnect       -instancename $name -bus pBus -busmasterport mport
    set size [ expr $high -$low + 1 ]
    ihwaddperipheral -instancename $name -type trap -vendor ovpworld.org
    ihwsetparameter  -handle       $name -name portAddress -value $low  -type uns32
    ihwsetparameter  -handle       $name -name portSize    -value $size -type uns32
    ihwconnect       -instancename $name -bus pBus  -busslaveport bport1
    # enables callbacks that report accesses
    ihwsetparameter  -handle       $name -name cbEnable    -value True  -type boolean
}

# Add the 2 WDOG devices
set wdogList "WDOG1 0x020BC000 0x020BFFFF
              WDOG2 0x020C0000 0x020C3FFF"
foreach {name low high} ${wdogList} {
    ihwaddperipheral -instancename $name -type iMX6_WDOG -vendor nxp.ovpworld.org
    ihwconnect       -instancename $name -bus pBus -busslaveport bport1 -loaddress $low -hiaddress $high
    ihwconnect       -instancename $name -netport interrupt -net ${name}_spi
}


# procedure to add a dummy device
proc addDummyDevice { name base end } {
    set size [ expr $end -$base + 1 ]
    ihwaddperipheral -instancename $name -type trap -vendor ovpworld.org
    ihwsetparameter  -handle       $name -name portAddress -value $base  -type uns32
    ihwsetparameter  -handle       $name -name portSize    -value $size  -type uns32
    ihwconnect       -instancename $name -bus pBus  -busslaveport bport1
    # enables callbacks that report accesses
    ihwsetparameter  -handle       $name -name cbEnable    -value True  -type boolean
                        
}
# NOTE: required for Boot are
#   IOMUXC
#   GPC
#   eCSPI2
#   OCOTP_CTRL
#   MMDC

# AIPS=1 Memory Map
# Reserved                   0x020FC000 0x020FCFFF
# Reserved                   0x020F8000 0x020FBFFF
addDummyDevice  EPDC         0x020F4000 0x020F7FFF
addDummyDevice  PXP          0x020F0000 0x020F3FFF
addDummyDevice  SDMA         0x020EC000 0x020EFFFF
addDummyDevice  DCIC2        0x020E8000 0x020EBFFF
addDummyDevice  DCIC1        0x020E4000 0x020E7FFF
addDummyDevice  IOMUXC       0x020E0000 0x020E3FFF
# Reserved                   0x020DC2C0 0x020DFFFF
addDummyDevice  PGC_ARM      0x020DC2A0 0x020DC2BF
# Reserved                   0x020DC280 0x020DC29F
addDummyDevice  PGC_PU       0x020DC260 0x020DC27F
#               GPC          0x020DC000 0x020DC25F
#               SRC          0x020D8000 0x020DBFFF
addDummyDevice  EPIT2        0x020D4000 0x020D7FFF
addDummyDevice  EPIT1        0x020D0000 0x020D3FFF
addDummyDevice  SNVS_HP      0x020CC000 0x020CFFFF
# Reserved                   0x020CB000 0x020CBFFF
addDummyDevice  USBPHY2      0x020CA000 0x020CAFFF
addDummyDevice  USBPHY1      0x020C9000 0x020C9FFF
#               ANALOG       0x020C8000 0x020C8FFF
#               CCM          0x020C4000 0x020C7FFF
#               WDOG2        0x020C0000 0x020C3FFF
#               WDOG1        0x020BC000 0x020BFFFF
addDummyDevice  KPP          0x020B8000 0x020BBFFF
#               GPIO7        0x020B4000 0x020B7FFF
#               GPIO6        0x020B0000 0x020B3FFF
#               GPIO5        0x020AC000 0x020AFFFF
#               GPIO4        0x020A8000 0x020ABFFF
#               GPIO3        0x020A4000 0x020A7FFF
#               GPIO2        0x020A0000 0x020A3FFF
#               GPIO1        0x0209C000 0x0209FFFF
#               GPT          0x02098000 0x0209BFFF
addDummyDevice  CAN2         0x02094000 0x02097FFF
addDummyDevice  CAN1         0x02090000 0x02093FFF
addDummyDevice  PWM4         0x0208C000 0x0208FFFF
addDummyDevice  PWM3         0x02088000 0x0208BFFF
addDummyDevice  PWM2         0x02084000 0x02087FFF
addDummyDevice  PWM1         0x02080000 0x02083FFF
addDummyDevice  AIPS1_Cfg    0x0207C000 0x0207FFFF 
# NOTE: With the VPU added the code accesses addresses 
#       that are not specifically defined in the datasheet, so keep out
#addDummyDevice  VPU         0x02040000 0x0207BFFF
addDummyDevice  SPBA         0x0203C000 0x0203FFFF
# Reserved for SDMA internal registers  0x02038000 0x0203BFFF
addDummyDevice  ASRC         0x02034000 0x02037FFF
addDummyDevice  SSI3         0x02030000 0x02033FFF
addDummyDevice  SSI2         0x0202C000 0x0202FFFF
addDummyDevice  SSI1         0x02028000 0x0202BFFF
addDummyDevice  ESAI         0x02024000 0x02027FFF
#               UART1        0x02020000 0x02023FFF
# Reserved for SDMA internal registers  0x0201C000 0x0201FFFF
# Reserved                   0x02018000 0x0201BFFF
addDummyDevice  eCSPI4       0x02014000 0x02017FFF
addDummyDevice  eCSPI3       0x02010000 0x02013FFF
addDummyDevice  eCSPI2       0x0200C000 0x0200FFFF
addDummyDevice  eCSPI1       0x02008000 0x0200BFFF
addDummyDevice  SPDIF        0x02004000 0x02007FFF
# Reserved for SDMA internal registers  0x02000000 0x02003FFF
# AIPS-2
# Reserved                   0x021FC000 0x021FFFFF
addDummyDevice  I2C4         0x021F8000 0x021FBFFF
addDummyDevice  UART5        0x021F4000 0x021F7FFF
# No Device in spec but appears to be UART4
addDummyDevice  UART4        0x021F0000 0x021F3FFF
addDummyDevice  UART3        0x021EC000 0x021EFFFF
# No Device in spec but appears to be UART2
#               UART2        0x021E8000 0x021EBFFF
addDummyDevice  VDOA         0x021E4000 0x021E7FFF
addDummyDevice  MIPI_DSI     0x021E0000 0x021E3FFF
addDummyDevice  MIPI_CSI     0x021DC000 0x021DFFFF
addDummyDevice  AUDMUX       0x021D8000 0x021DBFFF
addDummyDevice  TZASC2       0x021D4000 0x021D7FFF
addDummyDevice  TZASC1       0x021D0000 0x021D3FFF
# Reserved                   0x021CC000 0x021CFFFF
# Reserved                   0x021C8000 0x021CBFFF
# Reserved                   0x021C4000 0x021C7FFF
addDummyDevice  CSU          0x021C0000 0x021C3FFF
addDummyDevice  OCOTP_CTRL   0x021BC000 0x021BFFFF
addDummyDevice  EIM          0x021B8000 0x021BBFFF
addDummyDevice  MMDCp1       0x021B4000 0x021B7FFF
#               MMDC         0x021B0000 0x021B3FFF
addDummyDevice  ROMCP        0x021AC000 0x021AFFFF
addDummyDevice  I2C3         0x021A8000 0x021ABFFF
addDummyDevice  I2C2         0x021A4000 0x021A7FFF
addDummyDevice  I2C1         0x021A0000 0x021A3FFF
#               uSDHC4       0x0219C000 0x0219FFFF
#               uSDHC3       0x02198000 0x0219BFFF
#               uSDHC2       0x02194000 0x02197FFF
#               uSDHC1       0x02190000 0x02193FFF
addDummyDevice  MLB150       0x0218C000 0x0218FFFF
addDummyDevice  ENET         0x02188000 0x0218BFFF
addDummyDevice  USBOH3_USB   0x02184000 0x02187FFF
addDummyDevice  USBOH3_PL301 0x02180000 0x02183FFF
addDummyDevice  AIPS2_Cfg    0x0217C000 0x0217FFFF
# ARM Cortex A9 MPCore Platform Reserved  0x02161000 0x0217BFFF
# ARM Cortex A9 MPCore platform/DAP       0x02140000 0x02160FFF
# Reserved 192 KB                         0x02110000 0x0213FFFF
addDummyDevice  CAAM         0x02100000 0x0210FFFF

# System Memory Map
# MMDC-DDR                   0x10000000 0xFFFFFFFF 
# EIM-SRAM                   0x08000000 0x0FFFFFFF 
# Reserved                   0x02A00000 0x02DFFFFF 
addDummyDevice  IPU          0x02600000 0x029FFFFF 
# Reserved                   0x0220C000 0x023FFFFF 
# MIPI_HSI                   0x02208000 0x0220BFFF 
# Reserved                   0x02204000 0x02207FFF 
# Reserved                   0x02200000 0x02203FFF 
# Peripheral IPs via AIPS-2. 0x02100000 0x021FFFFF 
# Peripheral IPs via AIPS-1. 0x02000000 0x020FFFFF 
# PCIe registers             0x01FFC000 0x01FFFFFF 
# PCIe                       0x01000000 0x01FFBFFF 
# Reserved                   0x00D00000 0x00FFFFFF 
# PL301 (fast1)              0x00C00000 0x00CFFFFF 
# PL301 (fast2) cfg pt       0x00B00000 0x00BFFFFF 
# Reserved                   0x00A03000 0x00AFFFFF 
# PL310 (L2 cache cntrl)     0x00A02000 0x00A02FFF 
# ARM MP                     0x00A00000 0x00A01FFF
# OCRAM aliased              0x00920000 0x009FFFFF 
# OCRAM 128 KB               0x00900000 0x0091FFFF 
# GPV_4 PL301 (fast3) cfg prt  0x00800000 0x008FFFFF 
# Reserved                   0x00400000 0x007FFFFF 
# GPV_3 PL301 (per2) cfg prt 0x00300000 0x003FFFFF 
# GPV_2 PL301 (per1) cfg prt 0x00200000 0x002FFFFF 
# Reserved                   0x0013C000 0x001FFFFF 
# DTCP                       0x00138000 0x0013BFFF 
addDummyDevice  GPU2D        0x00134000 0x00137FFF 
addDummyDevice  GPU3D        0x00130000 0x00133FFF 
# Reserved                   0x00129000 0x0012FFFF 
addDummyDevice  HDMI         0x00120000 0x00128FFF 
# Reserved                   0x00118000 0x0011FFFF 
# BCH                        0x00114000 0x00117FFF 
# GPMI                       0x00112000 0x00113FFF 
addDummyDevice  APBH_DMA     0x00110000 0x00111FFF 
# Reserved                   0x00104000 0x0010FFFF 
# CAAM (16 KB secure RAM)    0x00100000 0x00103FFF 
# Reserved                   0x00018000 0x000FFFFF 
# Boot ROM (ROMCP)           0x00000000 0x00017FFF 


#
# OVPworld Linux BootLoader
#
ihwaddperipheral -instancename smartLoader  -type SmartLoaderArmLinux -vendor arm.ovpworld.org -version 1.0
ihwconnect       -instancename smartLoader  -bus pBus -busmasterport mport -loaddress 0 -hiaddress 0xffffffff
ihwsetparameter  -handle       smartLoader  -name physicalbase -value 0x10000000   -type uns32
ihwsetparameter  -handle       smartLoader  -name memsize      -value 0x20000000   -type uns32
# Set default address to load zImage outside of area where inflated kernel will be located (starts at 0x10008000)
ihwsetparameter  -handle       smartLoader  -name kerneladdr  -value 0x11000000   -type uns32

# Add Virtio block device at unused address and interrupt until working MMC model is available
# 0x021ff000    0x021ff1ff      Virtio block device 
ihwaddperipheral -instancename VBD0 -type VirtioBlkMMIO -vendor ovpworld.org 
ihwconnect       -instancename VBD0 -bus pBus -busmasterport dma    -loaddress 0 -hiaddress 0xffffffff
ihwconnect       -instancename VBD0 -bus pBus -busslaveport  bport1 -loaddress 0x021ff000 -hiaddress 0x021ff1ff
ihwaddnet        -instancename VBD0_spi
ihwconnect       -net VBD0_spi -instancename cpu  -netport SPI39
ihwconnect       -net VBD0_spi -instancename VBD0 -netport Interrupt

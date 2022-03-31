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

set desc "
Freescale Vybrid VFxx platform
"

set limitations "
Only enough functionality modeled to boot MQX. Most peripherals modeled as dummy register ports.
"

set reference "Development based on document number: VYBRIDRM Rev. 5, 07/2013"

# Setup variables for platform info
set vendor  freescale.ovpworld.org
set library platform
set name    FreescaleVybridVFxx
set version 1.0

#
# Start new platform creation
#
ihwnew -name $name -vendor $vendor -library $library -version $version -stoponctrlc -purpose epk -releasestatus ovp
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text $desc
iadddocumentation -name Limitations -text $limitations
iadddocumentation -name Reference   -text $reference

ihwaddnet -instancename SPI93
ihwaddnet -instancename SPI94
ihwaddnet -instancename SPI95
ihwaddnet -instancename SPI96
ihwaddnet -instancename SPI97
ihwaddnet -instancename SPI98
ihwaddnet -instancename dma_eDMARequest0
ihwaddnet -instancename int16
ihwaddnet -instancename int0
ihwaddnet -instancename int1
ihwaddnet -instancename int2
ihwaddnet -instancename int3
ihwaddnet -instancename int4
ihwaddnet -instancename int5
ihwaddnet -instancename int6
ihwaddnet -instancename int7
ihwaddnet -instancename int8
ihwaddnet -instancename int9
ihwaddnet -instancename int10
ihwaddnet -instancename int11
ihwaddnet -instancename int12
ihwaddnet -instancename int13
ihwaddnet -instancename int14
ihwaddnet -instancename int15
ihwaddnet -instancename uart0_tx
ihwaddnet -instancename uart0_rx
ihwaddnet -instancename uart2_tx
ihwaddnet -instancename uart2_rx
ihwaddnet -instancename uart3_tx
ihwaddnet -instancename uart3_rx
ihwaddnet -instancename ftm0_phaseA
ihwaddnet -instancename ftm0_phaseB
ihwaddnet -instancename int62
ihwaddnet -instancename ftm1_phaseA
ihwaddnet -instancename ftm1_phaseB
ihwaddnet -instancename int63
ihwaddnet -instancename dma_eDMARequest1
ihwaddnet -instancename uart4_tx
ihwaddnet -instancename uart4_rx
ihwaddnet -instancename uart5_tx
ihwaddnet -instancename uart5_rx
ihwaddnet -instancename ftm2_phaseA
ihwaddnet -instancename ftm2_phaseB
ihwaddnet -instancename int64
ihwaddnet -instancename ftm3_phaseA
ihwaddnet -instancename ftm3_phaseB
ihwaddnet -instancename int101
ihwaddnet -instancename uart1_tx
ihwaddnet -instancename uart1_rx
ihwaddnet -instancename gpio0_out
ihwaddnet -instancename gpio0_in
ihwaddnet -instancename gpio0_mask
ihwaddnet -instancename gpio1_out
ihwaddnet -instancename gpio1_in
ihwaddnet -instancename gpio1_mask
ihwaddnet -instancename gpio2_out
ihwaddnet -instancename gpio2_in
ihwaddnet -instancename gpio2_mask
ihwaddnet -instancename gpio3_out
ihwaddnet -instancename gpio3_in
ihwaddnet -instancename gpio3_mask
ihwaddnet -instancename gpio4_out
ihwaddnet -instancename gpio4_in
ihwaddnet -instancename gpio4_mask

#
# pBus  - 32 bits of address
#
ihwaddbus -instancename pBus  -addresswidth 32

#
# Processor
#
ihwaddprocessor -instancename cpu -type arm -vendor arm.ovpworld.org -version 1.0 \
                -endian little \
                -simulateexceptions \
                -mips 396
ihwconnect    -instancename cpu -bus pBus -busmasterport INSTRUCTION
ihwconnect    -instancename cpu -bus pBus -busmasterport DATA
ihwsetparameter -handle       cpu -name variant                      -type string -value Cortex-A5MPx1
ihwsetparameter -handle       cpu -name UAL                          -type bool  -value 1
ihwsetparameter -handle       cpu -name override_CBAR                -type uns32 -value 0x40002000
ihwsetparameter -handle       cpu -name override_GICD_TYPER_ITLines  -type uns32 -value 4
ihwsetparameter -handle       cpu -name override_timerScaleFactor    -type uns32 -value 3

#
# Connect the supported interrupt nets to the processor's SPI interrupt ports
#
foreach i { 93 94 95 96 97 98 } {
    ihwconnect -net SPI${i} -instancename cpu -netport SPI${i}
}

# UART Module clock frequency is assumed by MQX to be 66 MHz (used for baud rate calculations)
set uartClkFreq 66000000

#
# Memories
#
# 0x00000000    0x00017fff  Boot Rom 96KB 
ihwaddmemory -instancename bootrom -type rom
ihwconnect   -instancename bootrom -bus pBus -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0x00017fff

# 0x3f000000    0x3f0fffff  On Chip System Ram 1MB 
ihwaddmemory -instancename sysram  -type ram
ihwconnect   -instancename sysram  -bus pBus -busslaveport sp1 -loaddress 0x3f000000 -hiaddress 0x3f0fffff

#
# Peripheral Bridge 0
#
# 0x40001000	0x40001fff	Peripheral Bridge 0 slot   1 - MCSM: Miscellaneous System Control Module (dummy)
ihwaddperipheral -instancename mcsm    -vendor ovpworld.org -type trap
ihwconnect       -instancename mcsm -busslaveport bport1 -bus pBus
ihwsetparameter  -handle       mcsm -name portAddress -value 0x40001000 -type uns32

# 0x40018000    0x40018fff  Peripheral Bridge 0 slot  24 - DMA0: Direct Memory Access Controller
ihwaddperipheral -instancename dma0    -type VybridDMA -vendor $vendor
ihwconnect       -instancename dma0    -bus  pBus -busslaveport  bport1 -loaddress 0x40018000 -hiaddress 0x40019fff
ihwconnect       -instancename dma0 -bus pBus -busmasterport MREAD -loaddress 0x00000000 -hiaddress 0xffffffff
ihwconnect       -instancename dma0 -bus pBus -busmasterport MWRITE -loaddress 0x00000000 -hiaddress 0xffffffff
ihwconnect       -instancename dma0 -net dma_eDMARequest0 -netport eDMARequest
ihwconnect -net int16 -instancename dma0 -netport errorInterrupt
for {set ii 0} {$ii < 16} {incr ii} {
    ihwconnect -net int${ii} -instancename dma0 -netport dmaInterrupt_ch${ii}
}

# 0x40024000    0x40024fff  Peripheral Bridge 0 slot  36 - DMAMUX0: Direct Memory Access Multiplexer (dummy)
ihwaddperipheral -instancename dmamux0 -vendor $vendor -library peripheral -type KinetisDMAMUX
ihwconnect       -instancename dmamux0 -bus  pBus -busslaveport  bport1 -loaddress 0x40024000 -hiaddress 0x40024fff
ihwconnect       -instancename dmamux0 -net dma_eDMARequest0 -netport eDMARequest

# 0x40025000    0x40025fff  Peripheral Bridge 0 slot  37 - DMAMUX1: Direct Memory Access Multiplexer (dummy)
ihwaddperipheral -instancename dmamux1 -vendor $vendor -library peripheral -type KinetisDMAMUX
ihwconnect       -instancename dmamux1 -bus  pBus -busslaveport  bport1 -loaddress 0x40025000 -hiaddress 0x40025fff
ihwsetparameter    -handle dmamux1 -name startDMAChannel  -type uns32 -value 16
ihwconnect       -instancename dmamux1 -net dma_eDMARequest0 -netport eDMARequest

# 0x40027000    0x40027fff  Peripheral Bridge 0 slot  39 - UART0 - Universal Asynchronous Receiver/Transmitter
ihwaddperipheral -instancename uart0  -vendor $vendor -library peripheral -type VybridUART
ihwconnect       -instancename uart0   -bus  pBus -busslaveport  bport1 -loaddress 0x40027000 -hiaddress 0x40027fff
ihwconnect       -instancename uart0   -net SPI93 -netport Interrupt
ihwsetparameter    -handle       uart0   -name fifoSize       -type uns32 -value 16
ihwsetparameter    -handle       uart0   -name moduleClkFreq  -type uns32 -value $uartClkFreq
ihwconnect       -instancename uart0  -net  uart0_tx -netport DirectWrite
ihwconnect       -instancename uart0  -net  uart0_rx -netport DirectRead

# 0x40028000    0x40028fff  Peripheral Bridge 0 slot  40 - UART1 - Universal Asynchronous Receiver/Transmitter
ihwaddperipheral -instancename uart1  -vendor $vendor -library peripheral -type VybridUART
ihwconnect       -instancename uart1   -bus  pBus -busslaveport  bport1 -loaddress 0x40028000 -hiaddress 0x40028fff
ihwconnect       -instancename uart1   -net SPI94 -netport Interrupt
ihwsetparameter    -handle       uart1   -name fifoSize    -type uns32 -value 16
ihwsetparameter    -handle       uart1   -name moduleClkFreq  -type uns32  -value $uartClkFreq
#ihwconnect       -instancename uart1  -net  uart1_tx -netport DirectWrite
#ihwconnect       -instancename uart1  -net  uart1_rx -netport DirectRead

# 0x40029000    0x40029fff  Peripheral Bridge 0 slot  41 - UART2 - Universal Asynchronous Receiver/Transmitter
ihwaddperipheral -instancename uart2  -vendor $vendor -library peripheral -type VybridUART
ihwconnect       -instancename uart2   -bus  pBus -busslaveport  bport1 -loaddress 0x40029000 -hiaddress 0x40029fff
ihwconnect       -instancename uart2   -net SPI95 -netport Interrupt
ihwsetparameter    -handle       uart2   -name fifoSize       -type uns32  -value 8
ihwsetparameter    -handle       uart2   -name moduleClkFreq  -type uns32  -value $uartClkFreq
ihwconnect       -instancename uart2  -net  uart2_tx -netport DirectWrite
ihwconnect       -instancename uart2  -net  uart2_rx -netport DirectRead

# 0x4002a000    0x4002afff  Peripheral Bridge 0 slot  42 - UART3 - Universal Asynchronous Receiver/Transmitter
ihwaddperipheral -instancename uart3  -vendor $vendor -library peripheral -type VybridUART
ihwconnect       -instancename uart3   -bus  pBus -busslaveport  bport1 -loaddress 0x4002a000 -hiaddress 0x4002afff
ihwconnect       -instancename uart3   -net SPI96 -netport Interrupt
ihwsetparameter    -handle       uart3   -name fifoSize       -type uns32  -value 8
ihwsetparameter    -handle       uart3   -name moduleClkFreq  -type uns32  -value $uartClkFreq
ihwconnect       -instancename uart3  -net  uart3_tx -netport DirectWrite
ihwconnect       -instancename uart3  -net  uart3_rx -netport DirectRead

#0x4002C000   0x4002Cfff  Peripheral Bridge 0 slot 44 - SPI0 - SPI Controller
ihwaddperipheral -instancename spi0 -vendor $vendor -library peripheral -type VybridSPI
ihwconnect       -instancename spi0 -bus pBus -busslaveport bport1 -loaddress 0x4002C000 -hiaddress 0x4002Cfff

#0x4002D000   0x4002Dfff  Peripheral Bridge 0 slot 45 - SPI1 - SPI Controller
ihwaddperipheral -instancename spi1 -vendor $vendor -library peripheral -type VybridSPI
ihwconnect       -instancename spi1 -bus pBus -busslaveport bport1 -loaddress 0x4002D000 -hiaddress 0x4002Dfff

#0x40034000   0x40034fff  Peripheral Bridge 0 slot 52 - USBC0 - USB Controller
ihwaddperipheral -instancename usbc0 -vendor $vendor -library peripheral -type VybridUSB
ihwconnect       -instancename usbc0 -bus pBus -busslaveport bport1 -loaddress 0x40034000 -hiaddress 0x40034fff

# 0x40038000	0x40038fff	Peripheral Bridge 0 slot  56 - FTM: FlexTimer 0
ihwaddperipheral -instancename ftm0 -vendor $vendor -type KinetisFTM
ihwconnect       -instancename ftm0 -bus  pBus -busslaveport  bport1 -loaddress 0x40038000 -hiaddress 0x40038fff
ihwconnect       -instancename ftm0 -net ftm0_phaseA -netport PhaseA
ihwconnect       -instancename ftm0 -net ftm0_phaseB -netport PhaseB
ihwconnect       -instancename ftm0 -net int62 -netport Interrupt

# 0x40039000	0x40039fff	Peripheral Bridge 0 slot  57 - FTM: FlexTimer 1
ihwaddperipheral -instancename ftm1 -vendor $vendor -type KinetisFTM
ihwconnect       -instancename ftm1 -bus  pBus -busslaveport  bport1 -loaddress 0x40039000 -hiaddress 0x40039fff
ihwconnect       -instancename ftm1 -net ftm1_phaseA -netport PhaseA
ihwconnect       -instancename ftm1 -net ftm1_phaseB -netport PhaseB
ihwconnect       -instancename ftm1 -net int63 -netport Interrupt

#0x4003B000   0x4003B034  Peripheral Bridge 0 slot 59 - ADC0 - Analog to digital converter.
ihwaddperipheral -instancename adc0 -vendor $vendor -library peripheral -type VybridADC
ihwconnect       -instancename adc0 -bus pBus -busslaveport bport1 -loaddress 0x4003B000 -hiaddress 0x4003Bfff

#0x40044000   0x40044fff  Peripheral Bridge 0 slot 68 - QUADSPI0 - Quad SPI
ihwaddperipheral -instancename quadspi0 -vendor $vendor -library peripheral -type VybridQUADSPI
ihwconnect       -instancename quadspi0 -bus pBus -busslaveport bport1 -loaddress 0x40044000 -hiaddress 0x40044fff

# 0x40048000    0x40048fff  Peripheral Bridge 0 slot  72 - IOMUXC: Input/Output Multiplexer Controller (dummy)
ihwaddperipheral -instancename iomuxc  -vendor ovpworld.org -type trap
ihwconnect       -instancename iomuxc -busslaveport bport1 -bus pBus
ihwsetparameter  -handle       iomuxc -name portAddress -value 0x40048000 -type uns32

# 0x40050000    0x40050fff  Peripheral Bridge 0 slot  80 - ANADIG: Analog components control digital interfac
ihwaddperipheral -instancename anadig  -type VybridANADIG -vendor $vendor
ihwconnect       -instancename anadig  -bus  pBus -busslaveport  bport1 -loaddress 0x40050000 -hiaddress 0x40050fff

#0x40066000   0x40066007  Peripheral Bridge 0 slot 102 - i2c0 - i2c module
ihwaddperipheral -instancename i2c0 -vendor $vendor -library peripheral -type VybridI2C
ihwconnect       -instancename i2c0 -bus pBus -busslaveport bport1 -loaddress 0x40066000 -hiaddress 0x40066fff

#0x40067000   0x40067007  Peripheral Bridge 0 slot 103 - i2c1 - i2c module
ihwaddperipheral -instancename i2c1 -vendor $vendor -library peripheral -type VybridI2C
ihwconnect       -instancename i2c1 -bus pBus -busslaveport bport1 -loaddress 0x40067000 -hiaddress 0x40067fff

# 0x4006b000    0x4006bfff  Peripheral Bridge 0 slot 107 - CCM: Clock Controller Module
ihwaddperipheral -instancename ccm     -type VybridCCM -vendor $vendor
ihwconnect       -instancename ccm     -bus  pBus -busslaveport  bport1 -loaddress 0x4006b000 -hiaddress 0x4006bfff

#
# Peripheral Bridge 1
#
# 0x40098000    0x40098fff  Peripheral Bridge 1 slot  24 - DMA1: Direct Memory Access Controller
ihwaddperipheral -instancename dma1    -vendor $vendor -library peripheral -type VybridDMA 
ihwconnect       -instancename dma1    -bus  pBus -busslaveport  bport1 -loaddress 0x40098000 -hiaddress 0x40099fff
ihwconnect       -instancename dma1 -bus pBus -busmasterport MREAD -loaddress 0x00000000 -hiaddress 0xffffffff
ihwconnect       -instancename dma1 -bus pBus -busmasterport MWRITE -loaddress 0x00000000 -hiaddress 0xffffffff
ihwconnect       -instancename dma1 -net dma_eDMARequest1 -netport eDMARequest
ihwconnect -net int16 -instancename dma1 -netport errorInterrupt
for {set ii 0} {$ii < 16} {incr ii} {
    ihwconnect -net int${ii} -instancename dma1 -netport dmaInterrupt_ch${ii}
}

# 0x400a1000    0x400a1fff  Peripheral Bridge 1 slot  33 - DMAMUX2: Direct Memory Access Multiplexer (dummy)
ihwaddperipheral -instancename dmamux2 -vendor $vendor -library peripheral -type KinetisDMAMUX
ihwconnect       -instancename dmamux2 -bus  pBus -busslaveport  bport1 -loaddress 0x400a1000 -hiaddress 0x400a1fff
ihwconnect       -instancename dmamux2 -net dma_eDMARequest1 -netport eDMARequest

# 0x400a2000    0x400a2fff  Peripheral Bridge 1 slot  34 - DMAMUX3: Direct Memory Access Multiplexer (dummy)
ihwaddperipheral -instancename dmamux3 -vendor $vendor -library peripheral -type KinetisDMAMUX
ihwconnect       -instancename dmamux3 -bus  pBus -busslaveport  bport1 -loaddress 0x400a2000 -hiaddress 0x400a2fff
ihwsetparameter    -handle dmamux3 -name startDMAChannel  -type uns32  -value 16
ihwconnect       -instancename dmamux3 -net dma_eDMARequest1 -netport eDMARequest

# 0x400a9000    0x400a9fff  Peripheral Bridge 1 slot  41 - UART4 - Universal Asynchronous Receiver/Transmitter
ihwaddperipheral -instancename uart4  -vendor $vendor -library peripheral -type VybridUART
ihwconnect       -instancename uart4   -bus  pBus -busslaveport  bport1 -loaddress 0x400a9000 -hiaddress 0x400a9fff
ihwconnect       -instancename uart4   -net SPI95 -netport Interrupt
ihwsetparameter    -handle       uart4   -name fifoSize       -type uns32  -value 8
ihwsetparameter    -handle       uart4   -name moduleClkFreq  -type uns32  -value $uartClkFreq
ihwconnect       -instancename uart4  -net  uart4_tx -netport DirectWrite
ihwconnect       -instancename uart4  -net  uart4_rx -netport DirectRead

# 0x400aa000    0x400aafff  Peripheral Bridge 1 slot  42 - UART5 - Universal Asynchronous Receiver/Transmitter
ihwaddperipheral -instancename uart5  -vendor $vendor -library peripheral -type VybridUART
ihwconnect       -instancename uart5   -bus  pBus -busslaveport  bport1 -loaddress 0x400aa000 -hiaddress 0x400aafff
ihwconnect       -instancename uart5   -net SPI96 -netport Interrupt
ihwsetparameter    -handle       uart5   -name fifoSize       -type uns32  -value 8
ihwsetparameter    -handle       uart5   -name moduleClkFreq  -type uns32  -value $uartClkFreq
ihwconnect       -instancename uart5  -net  uart5_tx -netport DirectWrite
ihwconnect       -instancename uart5  -net  uart5_rx -netport DirectRead

#0x400AC000   0x400ACfff  Peripheral Bridge 1 slot 44 - SPI3 - SPI Controller
ihwaddperipheral -instancename spi3 -vendor $vendor -library peripheral -type VybridSPI
ihwconnect       -instancename spi3 -bus pBus -busslaveport bport1 -loaddress 0x400AC000 -hiaddress 0x400ACfff

#0x400AD000   0x400ADfff  Peripheral Bridge 1 slot 45 - SPI4 - SPI Controller
ihwaddperipheral -instancename spi4 -vendor $vendor -library peripheral -type VybridSPI
ihwconnect       -instancename spi4 -bus pBus -busslaveport bport1 -loaddress 0x400AD000 -hiaddress 0x400ADfff

# 0x400ae000    0x400aefff  Peripheral Bridge 1 slot  46 - DDRMC: SDRAM Memory Controller (dummy)
ihwaddperipheral -instancename ddrmc   -vendor ovpworld.org -type trap
ihwconnect       -instancename ddrmc -busslaveport bport1 -bus pBus
ihwsetparameter  -handle       ddrmc -name portAddress -value 0x400ae000 -type uns32

#0x400B1000   0x400B1fff  Peripheral Bridge 1 slot 49 - SDHC0 - SDHC Controller
ihwaddperipheral -instancename sdhc0 -vendor $vendor -library peripheral -type VybridSDHC
ihwconnect       -instancename sdhc0 -bus pBus -busslaveport bport1 -loaddress 0x400B1000 -hiaddress 0x400B1fff

#0x400B2000   0x400B2fff  Peripheral Bridge 1 slot 50 - SDHC1 - SDHC Controller
ihwaddperipheral -instancename sdhc1 -vendor $vendor -library peripheral -type VybridSDHC
ihwconnect       -instancename sdhc1 -bus pBus -busslaveport bport1 -loaddress 0x400B2000 -hiaddress 0x400B2fff

#0x400B4000   0x400B4fff  Peripheral Bridge 1 slot 52 - USBC1 - USB Controller
ihwaddperipheral -instancename usbc1 -vendor $vendor -library peripheral -type VybridUSB
ihwconnect       -instancename usbc1 -bus pBus -busslaveport bport1 -loaddress 0x400B4000 -hiaddress 0x400B4fff

# 0x400b8000	0x400b8fff	Peripheral Bridge 1 slot 56 - FTM: FlexTimer 2
ihwaddperipheral -instancename ftm2  -vendor $vendor -type KinetisFTM
ihwconnect       -instancename ftm2  -bus  pBus -busslaveport  bport1 -loaddress 0x400b8000 -hiaddress 0x400b8fff
ihwconnect       -instancename ftm2 -net ftm2_phaseA -netport PhaseA
ihwconnect       -instancename ftm2 -net ftm2_phaseB -netport PhaseB
ihwconnect       -instancename ftm2 -net int64 -netport Interrupt

# 0x400b9000	0x400b9fff	Peripheral Bridge 1 slot 57 - FTM: FlexTimer 3
ihwaddperipheral -instancename ftm3  -vendor $vendor -type KinetisFTM
ihwconnect       -instancename ftm3  -bus  pBus -busslaveport  bport1 -loaddress 0x400b9000 -hiaddress 0x400b9fff
ihwconnect       -instancename ftm3 -net ftm3_phaseA -netport PhaseA
ihwconnect       -instancename ftm3 -net ftm3_phaseB -netport PhaseB
ihwconnect       -instancename ftm3 -net int101 -netport Interrupt

#0x400BB000   0x400BB034  Peripheral Bridge 1 slot 59 - ADC1 - Analog to digital converter.
ihwaddperipheral -instancename adc1 -vendor $vendor -library peripheral -type VybridADC
ihwconnect       -instancename adc1 -bus pBus -busslaveport bport1 -loaddress 0x400BB000 -hiaddress 0x400BBfff

#0x400BE000   0x400BE034  Peripheral Bridge 1 slot 62 - LCD0 - LCD Controller
ihwaddperipheral -instancename lcd0 -vendor $vendor -library peripheral -type VybridLCD
ihwconnect       -instancename lcd0 -bus pBus -busslaveport bport1 -loaddress 0x400BE000 -hiaddress 0x400BEfff

#0x400C4000   0x400C4fff  Peripheral Bridge 1 slot 68 - QUADSPI0 - Quad SPI
ihwaddperipheral -instancename quadspi1 -vendor $vendor -library peripheral -type VybridQUADSPI
ihwconnect       -instancename quadspi1 -bus pBus -busslaveport bport1 -loaddress 0x400C4000 -hiaddress 0x400C4fff

#0x400E6000   0x400E6007  Peripheral Bridge 1 slot 102 - i2c2 - i2c module
ihwaddperipheral -instancename i2c2 -vendor $vendor -library peripheral -type VybridI2C
ihwconnect       -instancename i2c2 -bus pBus -busslaveport bport1 -loaddress 0x400E6000 -hiaddress 0x400E6fff

#0x400E7000   0x400E7007  Peripheral Bridge 1 slot 103 - i2c3 - i2c module
ihwaddperipheral -instancename i2c3 -vendor $vendor -library peripheral -type VybridI2C
ihwconnect       -instancename i2c3 -bus pBus -busslaveport bport1 -loaddress 0x400E7000 -hiaddress 0x400E7fff

#0x400FF000   0x400FF03f  GPIO0 - GPIO4
ihwaddperipheral -instancename gpio0 -vendor $vendor -library peripheral -type VybridGPIO
ihwconnect       -instancename gpio0 -bus pBus -busslaveport bport1 -loaddress 0x400FF000 -hiaddress 0x400FF03f

ihwaddperipheral -instancename gpio1 -vendor $vendor -library peripheral -type VybridGPIO
ihwconnect       -instancename gpio1 -bus pBus -busslaveport bport1 -loaddress 0x400FF040 -hiaddress 0x400FF07f

ihwaddperipheral -instancename gpio2 -vendor $vendor -library peripheral -type VybridGPIO
ihwconnect       -instancename gpio2 -bus pBus -busslaveport bport1 -loaddress 0x400FF080 -hiaddress 0x400FF0bf

ihwaddperipheral -instancename gpio3 -vendor $vendor -library peripheral -type VybridGPIO
ihwconnect       -instancename gpio3 -bus pBus -busslaveport bport1 -loaddress 0x400FF0C0 -hiaddress 0x400FF0ff

ihwaddperipheral -instancename gpio4 -vendor $vendor -library peripheral -type VybridGPIO
ihwconnect       -instancename gpio4 -bus pBus -busslaveport bport1 -loaddress 0x400FF100 -hiaddress 0x400FF13f

#####################################################################################
# Command line arguments
#####################################################################################
ihwaddclp -allargs

#####################################################################################
#
# Module connections
#

ihwaddnetport -instancename p_uart0_tx
ihwaddnetport -instancename p_uart0_rx
ihwaddnetport -instancename p_uart1_tx
ihwaddnetport -instancename p_uart1_rx
ihwaddnetport -instancename p_uart2_tx
ihwaddnetport -instancename p_uart2_rx
ihwaddnetport -instancename p_uart3_tx
ihwaddnetport -instancename p_uart3_rx
ihwaddnetport -instancename p_uart4_tx
ihwaddnetport -instancename p_uart4_rx
ihwaddnetport -instancename p_uart5_tx
ihwaddnetport -instancename p_uart5_rx

ihwaddnetport -instancename p_gpio0_out
ihwaddnetport -instancename p_gpio0_in
ihwaddnetport -instancename p_gpio0_mask
ihwaddnetport -instancename p_gpio1_out
ihwaddnetport -instancename p_gpio1_in
ihwaddnetport -instancename p_gpio1_mask
ihwaddnetport -instancename p_gpio2_out
ihwaddnetport -instancename p_gpio2_in
ihwaddnetport -instancename p_gpio2_mask
ihwaddnetport -instancename p_gpio3_out
ihwaddnetport -instancename p_gpio3_in
ihwaddnetport -instancename p_gpio3_mask
ihwaddnetport -instancename p_gpio4_out
ihwaddnetport -instancename p_gpio4_in
ihwaddnetport -instancename p_gpio4_mask

ihwconnect -netport p_uart0_tx  -net uart0_tx
ihwconnect -netport p_uart0_rx  -net uart0_rx
ihwconnect -netport p_uart1_tx  -net uart1_tx
ihwconnect -netport p_uart1_rx  -net uart1_rx
ihwconnect -netport p_uart2_tx  -net uart2_tx
ihwconnect -netport p_uart2_rx  -net uart2_rx
ihwconnect -netport p_uart3_tx  -net uart3_tx
ihwconnect -netport p_uart3_rx  -net uart3_rx
ihwconnect -netport p_uart4_tx  -net uart4_tx
ihwconnect -netport p_uart4_rx  -net uart4_rx
ihwconnect -netport p_uart5_tx  -net uart5_tx
ihwconnect -netport p_uart5_rx  -net uart5_rx

ihwconnect -netport p_gpio0_out   -net gpio0_out
ihwconnect -netport p_gpio0_in    -net gpio0_in
ihwconnect -netport p_gpio0_mask  -net gpio0_mask
ihwconnect -netport p_gpio1_out   -net gpio1_out
ihwconnect -netport p_gpio1_in    -net gpio1_in
ihwconnect -netport p_gpio1_mask  -net gpio1_mask
ihwconnect -netport p_gpio2_out   -net gpio2_out
ihwconnect -netport p_gpio2_in    -net gpio2_in
ihwconnect -netport p_gpio2_mask  -net gpio2_mask
ihwconnect -netport p_gpio3_out   -net gpio3_out
ihwconnect -netport p_gpio3_in    -net gpio3_in
ihwconnect -netport p_gpio3_mask  -net gpio3_mask
ihwconnect -netport p_gpio4_out   -net gpio4_out
ihwconnect -netport p_gpio4_in    -net gpio4_in
ihwconnect -netport p_gpio4_mask  -net gpio4_mask

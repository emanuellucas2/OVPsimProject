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
Freescale Kinetis K60 Platform
"

set limitations "
Only enough functionality modeled to boot MQX. Most peripherals modeled as dummy register ports
"
set reference "Development based on document number: K60P144M100SF2RM Rev. 6, Nov 2011"

# Setup variables for platform info
set vendor  freescale.ovpworld.org
set library platform
set name    FreescaleKinetis60
set version 1.0

#
# Start new platform creation
#
ihwnew -name $name -vendor $vendor -library $library -version $version -stoponctrlc -purpose epk -releasestatus ovp
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text $desc
iadddocumentation -name Limitations -text $limitations
iadddocumentation -name Reference   -text $reference

#nets
foreach net { 
    int45 int47 int49 int51 int53 int55 int59 int60 int61 int62
    int63 int64 int68 int69 int70 int71 int98 int101
    int0  int1  int2  int3  int4  int5  int6  int7  int8  int9
    int10 int11 int12 int13 int14 int15 int16
    dma_eDMARequest
    adc0_dmareq adc1_dmareq adc2_dmareq adc3_dmareq
    cmp0_dmareq cmp1_dmareq cmp2_dmareq cmp3_dmareq
    ftm0_phaseA ftm0_phaseB ftm1_phaseA ftm1_phaseB
    adc0_altclk adc0_hwtrig adc0_adin adc0_vrefsh adc0_vrefsl adc0_adinid adc0_interrupt
    adc2_input adc2_sample adc2_trigger
    uart0_tx uart0_rx uart1_tx uart1_rx uart2_tx uart2_rx uart3_tx uart3_rx
    cmp_vin1 cmp_vin2
    cmp0_input0 cmp0_input1 cmp0_input2 cmp0_input3 cmp0_input4 cmp0_input5 cmp0_input6 
    cmp0_DacOutput cmp0_extsample cmp0_coutsoc cmp0_cmpopad
    cmp1_input0 cmp1_input1 cmp1_input2 cmp1_input3 cmp1_input4 cmp1_input5 cmp1_input6
    cmp1_DacOutput cmp1_extsample cmp1_coutsoc cmp1_cmpopad
    cmp2_input0 cmp2_input1 cmp2_input2 cmp2_input3 cmp2_input4 cmp2_input5 cmp2_input6
    cmp2_DacOutput cmp2_extsample cmp2_coutsoc cmp2_cmpopad
    cmp3_input0 cmp3_input1 cmp3_input2 cmp3_input3 cmp3_input4 cmp3_input5 cmp3_input6
    cmp3_DacOutput cmp3_extsample cmp3_coutsoc cmp3_cmpopad
    ftm2_phaseA ftm2_phaseB ftm3_phaseA ftm3_phaseB
    adc1_input adc1_sample adc1_trigger
    adc3_input adc3_sample adc3_trigger
    uart4_tx uart4_rx uart5_tx uart5_rx
    gpioA_in gpioA_out gpioA_mask gpioB_in gpioB_out gpioB_mask
    gpioC_in gpioC_out gpioC_mask gpioD_in gpioD_out gpioD_mask
    gpioE_in gpioE_out gpioE_mask gpioF_in gpioF_out gpioF_mask
    cmp_ext_sample cmp_coutSoc cmp_OPad
    cmp1input1 cmp1input2 cmp1input3 cmp1input4 cmp1input5 cmp1input6
    adc0_input adc0_sample adc0_trigger
    dac0_output dac1_output
    ftm_input ftm_output ftm_mask ftm_fault ftm_phaseA ftm_phaseB
    can0_tx  can0_rx can1_tx can1_rx
    spi0_tx spi0_rx spi1_tx spi1_rx spi2_tx spi2_rx
    i2c0_tx i2c0_rx i2c1_tx i2c1_rx i2s0_tx i2s0_rx i2s1_tx i2s1_rx
} {
    ihwaddnet -instancename ${net}
}

#
# pBus  - 32 bits of address
#
ihwaddbus -instancename pBus  -addresswidth 32

#
# Memory
#

# Flash memory 1MB at 0x0
ihwaddmemory -instancename flash -type ram
ihwconnect   -instancename flash -bus pBus -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0x00ffffff

# SRAM 128KB - half is below 0x2000000, half is above
set sramSize 0x20000
set sramLo   [expr 0x20000000 - (${sramSize}/2)]
set sramHi   [expr 0x20000000 + (${sramSize}/2) -1]
ihwaddmemory -instancename sram -type ram
ihwconnect   -instancename sram -bus pBus -busslaveport sp1 -loaddress ${sramLo} -hiaddress ${sramHi}

#
# Processor
#
ihwaddprocessor -instancename cpu -type armm -vendor arm.ovpworld.org -version 1.0 \
                -endian little \
                -mips 120 \
                -simulateexceptions 
ihwconnect    -instancename cpu -bus pBus -busmasterport INSTRUCTION
ihwconnect    -instancename cpu -bus pBus -busmasterport DATA
ihwsetparameter -handle       cpu -name variant                -type string -value Cortex-M4F
ihwsetparameter -handle       cpu -name UAL                    -type bool   -value 1
ihwsetparameter -handle       cpu -name override_priorityBits  -type uns32  -value 4
# 10-11-14 PRE: Changed to support all 105 interrupts.
ihwsetparameter -handle       cpu -name override_numInterrupts -type uns32 -value 105
# TODO: systick Calibration.noref should be forced to 1

#
# Connect the supported interrupt request nets 
# to the processor's interrupt ports
#
foreach i {45 47 49 51 53 55 59 60 61 62 63 64 68 69 70 71 98 101} {
    ihwconnect -net int${i} -instancename cpu -netport int${i}
}

# The following are for the DMA channel complete and error interupts.
for {set ii 0} {$ii <=16} {incr ii} {
    ihwconnect -net int${ii} -instancename cpu -netport int${ii}
}
# UART Module clock frequency is assumed by MQX to be 60 MHz (used for baud rate calculations)
set uartClkFreq 60000000

# 0x40000000    0x40000fff  Peripheral Bridge 0 slot   0 - AIPS: Peripheral Bridge 0
ihwaddperipheral -instancename aips0 -vendor $vendor -library peripheral -type KinetisAIPS
ihwconnect       -instancename aips0 -bus  pBus -busslaveport  bport1 -loaddress 0x40000000 -hiaddress 0x40000fff

# 0x40004000    0x40004fff  Peripheral Bridge 0 slot   4 - AXBS: Crossbar switch
ihwaddperipheral -instancename axbs -vendor $vendor -library peripheral -type KinetisAXBS
ihwconnect       -instancename axbs -bus  pBus -busslaveport  bport1 -loaddress 0x40004000 -hiaddress 0x40004fff

# 0x40008000    0x40009fff  Peripheral Bridge 0 slot   8-9 - DMAC: DMA Controller
ihwaddperipheral -instancename dmac -vendor $vendor -library peripheral -type KinetisDMA
ihwconnect       -instancename dmac -bus  pBus -busslaveport  bport1 -loaddress 0x40008000 -hiaddress 0x40009fff
ihwconnect       -instancename dmac -bus pBus -busmasterport MREAD -loaddress 0x00000000 -hiaddress 0xffffffff
ihwconnect       -instancename dmac -bus pBus -busmasterport MWRITE -loaddress 0x00000000 -hiaddress 0xffffffff
ihwconnect       -instancename dmac -net dma_eDMARequest -netport eDMARequest
ihwconnect -net int16 -instancename dmac -netport errorInterrupt
for {set ii 0} {$ii < 16} {incr ii} {
    ihwconnect -net int${ii} -instancename dmac -netport dmaInterrupt_ch${ii}
}

# 0x4000c000    0x4000cfff  Peripheral Bridge 0 slot  12 - FlexBus
ihwaddperipheral -instancename flexbus -vendor $vendor -library peripheral -type KinetisFB
ihwconnect       -instancename flexbus -bus  pBus -busslaveport  bport1 -loaddress 0x4000c000 -hiaddress 0x4000cfff

# 0x4000d000    0x4000dfff  Peripheral Bridge 0 slot  13 - MPU: Memory Protection Unit
ihwaddperipheral -instancename mpu -vendor $vendor -library peripheral -type KinetisMPU
ihwconnect       -instancename mpu -bus  pBus -busslaveport  bport1 -loaddress 0x4000d000 -hiaddress 0x4000dfff

# 0x4001f000    0x4001ffff  Peripheral Bridge 0 slot  31 - FMC: System Integration Module
ihwaddperipheral -instancename fmc -vendor $vendor -library peripheral -type KinetisFMC
ihwconnect       -instancename fmc -bus  pBus -busslaveport  bport1 -loaddress 0x4001f000 -hiaddress 0x4001ffff

# 0x40021000    0x40021fff  Peripheral Bridge 0 slot  33 - DMAMUX0: DMA Channel Multiplexer 0 
ihwaddperipheral -instancename dmamux0 -vendor $vendor -library peripheral -type KinetisDMAMUX
ihwconnect       -instancename dmamux0 -bus  pBus -busslaveport  bport1 -loaddress 0x40021000 -hiaddress 0x40021fff
ihwconnect       -instancename dmamux0 -net dma_eDMARequest -netport eDMARequest
ihwconnect       -instancename dmamux0 -net adc0_dmareq -netport dmaSrc40 
ihwconnect       -instancename dmamux0 -net adc1_dmareq -netport dmaSrc41 

# 0x40022000    0x40022fff  Peripheral Bridge 0 slot  34 - DMAMUX1: DMA Channel Multiplexer 1 (Not in RM but used by MQX)
ihwaddperipheral -instancename dmamux1 -vendor $vendor -library peripheral -type KinetisDMAMUX
ihwconnect       -instancename dmamux1 -bus  pBus -busslaveport  bport1 -loaddress 0x40022000 -hiaddress 0x40022fff
ihwsetparameter    -handle dmamux1 -name startDMAChannel -type uns32 -value 16
ihwconnect       -instancename dmamux1 -net dma_eDMARequest -netport eDMARequest
ihwconnect       -instancename dmamux1 -net adc0_dmareq -netport dmaSrc40 
ihwconnect       -instancename dmamux1 -net adc1_dmareq -netport dmaSrc41 
ihwconnect       -instancename dmamux1 -net adc2_dmareq -netport dmaSrc42 
ihwconnect       -instancename dmamux1 -net adc3_dmareq -netport dmaSrc43 
ihwconnect       -instancename dmamux1 -net cmp0_dmareq -netport dmaSrc47 
ihwconnect       -instancename dmamux1 -net cmp1_dmareq -netport dmaSrc48 
ihwconnect       -instancename dmamux1 -net cmp2_dmareq -netport dmaSrc49 
ihwconnect       -instancename dmamux1 -net cmp3_dmareq -netport dmaSrc50 

# 0x40024000    0x40024fff  Peripheral Bridge 0 slot  36 - CAN0: FlexCAN 0
ihwaddperipheral -instancename can0 -vendor $vendor -library peripheral -type KinetisCAN
ihwconnect       -instancename can0 -bus  pBus -busslaveport  bport1 -loaddress 0x40024000 -hiaddress 0x40024fff

# 0x4002C000    0x4002Cfff  Peripheral Bridge 0 slot  44 - SPI 0
ihwaddperipheral -instancename spi0 -vendor $vendor -library peripheral -type KinetisSPI
ihwconnect       -instancename spi0 -bus  pBus -busslaveport  bport1 -loaddress 0x4002c000 -hiaddress 0x4002cfff

# 0x4002D000    0x4002dfff  Peripheral Bridge 0 slot  45 - SPI 1
ihwaddperipheral -instancename spi1 -vendor $vendor -library peripheral -type KinetisSPI
ihwconnect       -instancename spi1 -bus  pBus -busslaveport  bport1 -loaddress 0x4002d000 -hiaddress 0x4002dfff

# 0x4002f000    0x4002ffff  Peripheral Bridge 0 slot  47 - I2S 0
ihwaddperipheral -instancename i2s0 -vendor $vendor -library peripheral -type KinetisI2S
ihwconnect       -instancename i2s0 -bus  pBus -busslaveport  bport1 -loaddress 0x4002f000 -hiaddress 0x4002ffff

# 0x40032000    0x40032fff  Peripheral Bridge 0 slot  50 - CRC
ihwaddperipheral -instancename crc -vendor $vendor -library peripheral -type KinetisCRC
ihwconnect       -instancename crc -bus  pBus -busslaveport  bport1 -loaddress 0x40032000 -hiaddress 0x40032fff

# 0x40034000    0x40034fff  Peripheral Bridge 0 slot  52 - USBHS: USB OTG HS/FS/LS
ihwaddperipheral -instancename usbhs -vendor $vendor -library peripheral -type KinetisUSBHS
ihwconnect       -instancename usbhs -bus  pBus -busslaveport  bport1 -loaddress 0x40034000 -hiaddress 0x40034fff

# 0x40035000    0x40035fff  Peripheral Bridge 0 slot  53 - USBCD: USB DCD
ihwaddperipheral -instancename usbdcd -vendor $vendor -library peripheral -type KinetisUSBDCD
ihwconnect       -instancename usbdcd -bus  pBus -busslaveport  bport1 -loaddress 0x40035000 -hiaddress 0x40035fff

# 0x40036000    0x40036fff  Peripheral Bridge 0 slot  54 - PDB: Programmable delay block (PDB)
ihwaddperipheral -instancename pdb -vendor $vendor -library peripheral -type KinetisPDB
ihwconnect       -instancename pdb -bus  pBus -busslaveport  bport1 -loaddress 0x40036000 -hiaddress 0x40036fff

# 0x40037000    0x40037fff  Peripheral Bridge 0 slot  55 - PIT: Periodic Interrupt Timer
ihwaddperipheral -instancename pit -vendor $vendor -library peripheral -type KinetisPIT
ihwconnect       -instancename pit -bus  pBus -busslaveport  bport1 -loaddress 0x40037000 -hiaddress 0x40037fff
ihwconnect       -instancename pit -net  int68 -netport irq0
ihwconnect       -instancename pit -net  int69 -netport irq1
ihwconnect       -instancename pit -net  int70 -netport irq2
ihwconnect       -instancename pit -net  int71 -netport irq3

# 0x40038000    0x40038fff  Peripheral Bridge 0 slot  56 - FTM: FlexTimer 0
ihwaddperipheral -instancename ftm0 -vendor $vendor -library peripheral -type KinetisFTM
ihwconnect       -instancename ftm0 -bus  pBus -busslaveport  bport1 -loaddress 0x40038000 -hiaddress 0x40038fff
ihwconnect       -instancename ftm0 -net ftm0_phaseA -netport PhaseA
ihwconnect       -instancename ftm0 -net ftm0_phaseB -netport PhaseB
ihwconnect       -instancename ftm0 -net int62 -netport Interrupt

# 0x40039000    0x40039fff  Peripheral Bridge 0 slot  57 - FTM: FlexTimer 1
ihwaddperipheral -instancename ftm1 -vendor $vendor -library peripheral -type KinetisFTM
ihwconnect       -instancename ftm1 -bus  pBus -busslaveport  bport1 -loaddress 0x40039000 -hiaddress 0x40039fff
ihwconnect       -instancename ftm1 -net ftm1_phaseA -netport PhaseA
ihwconnect       -instancename ftm1 -net ftm1_phaseB -netport PhaseB
ihwconnect       -instancename ftm1 -net int63 -netport Interrupt

# 0x4003b000    0x4003bfff  Peripheral Bridge 0 slot  59 - ADC: Analog-to-digital converter ADC 0
ihwaddperipheral -instancename adc0 -vendor $vendor -library peripheral -type KinetisADC
ihwconnect       -instancename adc0 -bus  pBus -busslaveport  bport1 -loaddress 0x4003b000 -hiaddress 0x4003bfff
ihwconnect       -instancename adc0 -net adc0_altclk    -netport AltClk
ihwconnect       -instancename adc0 -net adc0_hwtrig    -netport HwTrig
ihwconnect       -instancename adc0 -net adc0_adin      -netport AdIn
ihwconnect       -instancename adc0 -net adc0_vrefsh    -netport Vrefsh
ihwconnect       -instancename adc0 -net adc0_vrefsl    -netport Vrefsl
ihwconnect       -instancename adc0 -net adc0_adinid    -netport AdInId
ihwconnect       -instancename adc0 -net adc0_interrupt -netport Interrupt
ihwconnect       -instancename adc0 -net adc0_dmareq    -netport DmaReq

# 0x4003c000    0x4003cfff  Peripheral Bridge 0 slot  60 - ADC: Analog-to-digital converter ADC 2
ihwaddperipheral -instancename adc2 -vendor $vendor -library peripheral -type KinetisADC
ihwconnect       -instancename adc2 -bus  pBus -busslaveport  bport1 -loaddress 0x4003c000 -hiaddress 0x4003cfff
ihwconnect       -instancename adc2 -netport AdIn       -net adc2_input
ihwconnect       -instancename adc2 -netport AdInId      -net adc2_sample
ihwconnect       -instancename adc2 -netport HwTrig     -net adc2_trigger

# 0x4003d000    0x4003dfff  Peripheral Bridge 0 slot  61 - RTC: Real-Time Clock
ihwaddperipheral -instancename rtc -vendor $vendor -library peripheral -type KinetisRTC
ihwconnect       -instancename rtc -bus  pBus -busslaveport  bport1 -loaddress 0x4003d000 -hiaddress 0x4003dfff

# 0x4003e000    0x4003efff  Peripheral Bridge 0 slot  62 - VBAT: VBAT register file
ihwaddperipheral -instancename vbat -vendor $vendor -library peripheral -type KinetisRFVBAT 
ihwconnect       -instancename vbat -bus  pBus -busslaveport  bport1 -loaddress 0x4003e000 -hiaddress 0x4003efff

# 0x40040000    0x40040fff  Peripheral Bridge 0 slot  64 - LPTMR: Low-power timer
ihwaddperipheral -instancename lptmr -vendor $vendor -library peripheral -type KinetisLPTMR
ihwconnect       -instancename lptmr -bus  pBus -busslaveport  bport1 -loaddress 0x40040000 -hiaddress 0x40040fff

# 0x40041000    0x40041fff  Peripheral Bridge 0 slot  66 - RFSYS: System Register File
ihwaddperipheral -instancename rfsys -vendor $vendor -library peripheral -type KinetisRFSYS  
ihwconnect       -instancename rfsys -bus  pBus -busslaveport  bport1 -loaddress 0x40041000 -hiaddress 0x40041fff

# 0x40045000    0x40045fff  Peripheral Bridge 0 slot  69 - TSI: Touch sense interface
ihwaddperipheral -instancename tsi -vendor $vendor -library peripheral -type KinetisTSI
ihwconnect       -instancename tsi -bus  pBus -busslaveport  bport1 -loaddress 0x40045000 -hiaddress 0x40045fff

# 0x40047000    0x40047fff  Peripheral Bridge 0 slot  71 - SIMLPL: System Integration Module Low-Power Logic (dummy)
#ihwaddperipheral -instancename simlpl -vendor ovpworld.org -type trap  
#ihwconnect       -instancename simlpl -busslaveport bport1 -bus pBus
#ihwsetparameter  -handle       simlpl -name portAddress -value 0x40047000 -type uns32

# 0x40048000    0x40048fff  Peripheral Bridge 0 slot  71-72 - SIM: System Integration Module
ihwaddperipheral -instancename sim -vendor $vendor -library peripheral -type KinetisSIM
ihwconnect       -instancename sim -bus  pBus -busslaveport  bport1 -loaddress 0x40047000 -hiaddress 0x40048fff

# 0x40049000    0x40049fff  Peripheral Bridge 0 slot  73 - Port A multiplexing control
ihwaddperipheral -instancename amux -vendor $vendor -library peripheral -type KinetisPORT
ihwconnect       -instancename amux -bus  pBus -busslaveport  bport1 -loaddress 0x40049000 -hiaddress 0x40049fff

# 0x4004a000    0x4004afff  Peripheral Bridge 0 slot  74 - Port B multiplexing control
ihwaddperipheral -instancename bmux -vendor $vendor -library peripheral -type KinetisPORT
ihwconnect       -instancename bmux -bus  pBus -busslaveport  bport1 -loaddress 0x4004a000 -hiaddress 0x4004afff

# 0x4004b000    0x4004bfff  Peripheral Bridge 0 slot  75 - Port C multiplexing control
ihwaddperipheral -instancename cmux -vendor $vendor -library peripheral -type KinetisPORT
ihwconnect       -instancename cmux -bus  pBus -busslaveport  bport1 -loaddress 0x4004b000 -hiaddress 0x4004bfff

# 0x4004c000    0x4004cfff  Peripheral Bridge 0 slot  76 - Port D multiplexing control
ihwaddperipheral -instancename dmux -vendor $vendor -library peripheral -type KinetisPORT
ihwconnect       -instancename dmux -bus  pBus -busslaveport  bport1 -loaddress 0x4004c000 -hiaddress 0x4004cfff

# 0x4004d000    0x4004dfff  Peripheral Bridge 0 slot  77 - Port E multiplexing control 
ihwaddperipheral -instancename emux -vendor $vendor -library peripheral -type KinetisPORT
ihwconnect       -instancename emux -bus  pBus -busslaveport  bport1 -loaddress 0x4004d000 -hiaddress 0x4004dfff

# 0x4004e000    0x4004efff  Peripheral Bridge 0 slot  78 - Port F multiplexing control 
ihwaddperipheral -instancename fmux -vendor $vendor -library peripheral -type KinetisPORT
ihwconnect       -instancename fmux -bus  pBus -busslaveport  bport1 -loaddress 0x4004e000 -hiaddress 0x4004efff

# 0x40052000    0x40052fff  Peripheral Bridge 0 slot  82 - WDOG: Software Watchdog 
ihwaddperipheral -instancename wdog -vendor $vendor -library peripheral -type KinetisWDOG
ihwconnect       -instancename wdog -bus  pBus -busslaveport  bport1 -loaddress 0x40052000 -hiaddress 0x40052fff

# 0x40061000    0x40061fff  Peripheral Bridge 0 slot  97 - EWM: External Watchdog 
ihwaddperipheral -instancename ewm -vendor $vendor -library peripheral -type KinetisEWM
ihwconnect       -instancename ewm -bus  pBus -busslaveport  bport1 -loaddress 0x40061000 -hiaddress 0x40061fff

# 0x40062000    0x40062fff  Peripheral Bridge 0 slot  98 - CMT: Carrier modulator timer 
ihwaddperipheral -instancename cmt -vendor $vendor -library peripheral -type KinetisCMT
ihwconnect       -instancename cmt -bus  pBus -busslaveport  bport1 -loaddress 0x40062000 -hiaddress 0x40062fff

# 0x40064000    0x40064fff  Peripheral Bridge 0 slot 100 - MCG: Multi-purpose Clock Generator
ihwaddperipheral -instancename mcg -vendor $vendor -library peripheral -type KinetisMCG
ihwconnect       -instancename mcg -bus  pBus -busslaveport  bport1 -loaddress 0x40064000 -hiaddress 0x40064fff

# 0x40065000    0x40065fff  Peripheral Bridge 0 slot 101 - OSC0: System Oscillator 0
ihwaddperipheral -instancename osc0  -vendor $vendor -library peripheral -type KinetisOSC
ihwconnect       -instancename osc0  -bus  pBus -busslaveport  bport1 -loaddress 0x40065000 -hiaddress 0x40065fff

# 0x40066000    0x40066fff  Peripheral Bridge 0 slot  102 - I2C0 
ihwaddperipheral -instancename i2c0 -vendor $vendor -library peripheral -type KinetisI2C
ihwconnect       -instancename i2c0 -bus  pBus -busslaveport  bport1 -loaddress 0x40066000 -hiaddress 0x40066fff

# 0x40067000    0x40067fff  Peripheral Bridge 0 slot  103 - I2C1 
ihwaddperipheral -instancename i2c1 -vendor $vendor -library peripheral -type KinetisI2C
ihwconnect       -instancename i2c1 -bus  pBus -busslaveport  bport1 -loaddress 0x40067000 -hiaddress 0x40067fff

# 0x4006a000    0x4006afff  Peripheral Bridge 0 slot 106 - UART0
ihwaddperipheral -instancename uart0  -type KinetisUART -vendor $vendor -library peripheral
ihwconnect       -instancename uart0  -bus  pBus -busslaveport  bport1 -loaddress 0x4006a000 -hiaddress 0x4006afff
ihwconnect       -instancename uart0  -net  int45 -netport Interrupt
ihwsetparameter    -handle       uart0  -name fifoSize      -type uns32 -value 8
ihwsetparameter    -handle       uart0  -name moduleClkFreq -type uns32 -value $uartClkFreq
ihwsetparameter    -handle       uart0  -name outfile       -type string -value uart0_outfile.txt
ihwconnect       -instancename uart0  -net  uart0_tx -netport DirectWrite
ihwconnect       -instancename uart0  -net  uart0_rx -netport DirectRead

# 0x4006b000    0x4006bfff  Peripheral Bridge 0 slot 107 - UART1
ihwaddperipheral -instancename uart1  -type KinetisUART -vendor $vendor -library peripheral
ihwconnect       -instancename uart1  -bus  pBus -busslaveport  bport1 -loaddress 0x4006b000 -hiaddress 0x4006bfff
ihwconnect       -instancename uart1  -net  int47 -netport Interrupt
ihwsetparameter    -handle       uart1  -name fifoSize      -type uns32 -value 8
ihwsetparameter    -handle       uart1  -name moduleClkFreq -type uns32 -value $uartClkFreq
ihwsetparameter    -handle       uart1  -name finishOnDisconnect   -type bool -value 1
ihwsetparameter    -handle       uart1  -name outfile       -type string -value uart1_outfile.txt
ihwconnect       -instancename uart1  -net  uart1_tx -netport DirectWrite
ihwconnect       -instancename uart1  -net  uart1_rx -netport DirectRead

# 0x4006c000    0x4006cfff  Peripheral Bridge 0 slot 108 - UART2
ihwaddperipheral -instancename uart2  -type KinetisUART -vendor $vendor -library peripheral
ihwconnect       -instancename uart2  -bus  pBus -busslaveport  bport1 -loaddress 0x4006c000 -hiaddress 0x4006cfff
ihwconnect       -instancename uart2  -net  int49 -netport Interrupt
ihwsetparameter    -handle       uart2  -name fifoSize   -type uns32 -value 1
ihwsetparameter    -handle       uart2  -name moduleClkFreq -type uns32 -value $uartClkFreq
ihwsetparameter    -handle       uart2  -name finishOnDisconnect   -type bool -value 1
ihwsetparameter    -handle       uart2  -name outfile   -type string -value uart2_outfile.txt
ihwconnect       -instancename uart2  -net  uart2_tx -netport DirectWrite
ihwconnect       -instancename uart2  -net  uart2_rx -netport DirectRead

# 0x4006d000    0x4006dfff  Peripheral Bridge 0 slot 109 - UART3
ihwaddperipheral -instancename uart3  -type KinetisUART -vendor $vendor -library peripheral
ihwconnect       -instancename uart3  -bus  pBus -busslaveport  bport1 -loaddress 0x4006d000 -hiaddress 0x4006dfff
ihwconnect       -instancename uart3  -net  int51 -netport Interrupt
ihwsetparameter    -handle       uart3  -name fifoSize   -type uns32 -value 1
ihwsetparameter    -handle       uart3  -name moduleClkFreq -type uns32 -value $uartClkFreq
ihwsetparameter    -handle       uart3  -name finishOnDisconnect   -type bool -value 1
ihwsetparameter    -handle       uart3  -name outfile   -type string -value uart3_outfile.txt
ihwconnect       -instancename uart3  -net  uart3_tx -netport DirectWrite
ihwconnect       -instancename uart3  -net  uart3_rx -netport DirectRead

# 0x40072000    0x40072fff  Peripheral Bridge 0 slot  114 - USB: USB OTG FS/LS 
ihwaddperipheral -instancename usb -vendor $vendor -library peripheral -type KinetisUSB
ihwconnect       -instancename usb -bus  pBus -busslaveport  bport1 -loaddress 0x40072000 -hiaddress 0x40072fff

# 0x40073000    0x40073fff  Peripheral Bridge 0 slot  115 - CMP: Analog Comparator / 6-bit DAC
# The actually device is all one peripheral, we only model one channel (that I am aware of), so need to 
# instatiate this four times.
# PRE: 10-11-14 Moved interrupt initalization up to were other interrupts are being setup.
ihwaddperipheral -instancename cmp0 -vendor $vendor -type KinetisCMP
ihwconnect       -instancename cmp0 -bus  pBus -busslaveport  bport1 -loaddress 0x40073000 -hiaddress 0x40073007
ihwsetparameter    -handle       cmp0 -name cmpNumber    -type uns32 -value 0
ihwconnect       -instancename cmp0 -net cmp0_dmareq    -netport DmaReq
ihwconnect       -instancename cmp0 -net int59          -netport Interrupt
ihwconnect       -instancename cmp0 -net cmp_vin1       -netport Vin1
ihwconnect       -instancename cmp0 -net cmp_vin2       -netport Vin2
ihwconnect       -instancename cmp0 -net cmp0_input0    -netport Input0
ihwconnect       -instancename cmp0 -net cmp0_input1    -netport Input1
ihwconnect       -instancename cmp0 -net cmp0_input2    -netport Input2
ihwconnect       -instancename cmp0 -net cmp0_input3    -netport Input3
ihwconnect       -instancename cmp0 -net cmp0_input4    -netport Input4
ihwconnect       -instancename cmp0 -net cmp0_input5    -netport Input5
ihwconnect       -instancename cmp0 -net cmp0_input6    -netport Input6
ihwconnect       -instancename cmp0 -net cmp0_DacOutput -netport DacOutput
ihwconnect       -instancename cmp0 -net cmp0_extsample -netport ExtSample
ihwconnect       -instancename cmp0 -net cmp0_coutsoc   -netport CoutSoc
ihwconnect       -instancename cmp0 -net cmp0_cmpopad   -netport CmpOPad

ihwaddperipheral -instancename cmp1 -vendor $vendor -type KinetisCMP
ihwconnect       -instancename cmp1 -bus  pBus -busslaveport  bport1 -loaddress 0x40073008 -hiaddress 0x4007300f
ihwsetparameter    -handle       cmp1 -name cmpNumber     -type uns32 -value 1
ihwconnect       -instancename cmp1 -net int60          -netport Interrupt
ihwconnect       -instancename cmp1 -net cmp1_dmareq    -netport DmaReq
ihwconnect       -instancename cmp1 -net cmp_vin1       -netport Vin1
ihwconnect       -instancename cmp1 -net cmp_vin2       -netport Vin2
ihwconnect       -instancename cmp1 -net cmp1_input0    -netport Input0
ihwconnect       -instancename cmp1 -net cmp1_input1    -netport Input1
ihwconnect       -instancename cmp1 -net cmp1_input2    -netport Input2
ihwconnect       -instancename cmp1 -net cmp1_input3    -netport Input3
ihwconnect       -instancename cmp1 -net cmp1_input4    -netport Input4
ihwconnect       -instancename cmp1 -net cmp1_input5    -netport Input5
ihwconnect       -instancename cmp1 -net cmp1_input6    -netport Input6
ihwconnect       -instancename cmp1 -net cmp1_DacOutput -netport DacOutput
ihwconnect       -instancename cmp1 -net cmp1_extsample -netport ExtSample
ihwconnect       -instancename cmp1 -net cmp1_coutsoc   -netport CoutSoc
ihwconnect       -instancename cmp1 -net cmp1_cmpopad   -netport CmpOPad

ihwaddperipheral -instancename cmp2 -vendor $vendor -type KinetisCMP
ihwconnect       -instancename cmp2 -bus  pBus -busslaveport  bport1 -loaddress 0x40073010 -hiaddress 0x40073017
ihwsetparameter    -handle       cmp2 -name cmpNumber    -type uns32 -value 2
ihwconnect       -instancename cmp2 -net int61          -netport Interrupt
ihwconnect       -instancename cmp2 -net cmp2_dmareq    -netport DmaReq
ihwconnect       -instancename cmp2 -net cmp_vin1       -netport Vin1
ihwconnect       -instancename cmp2 -net cmp_vin2       -netport Vin2
ihwconnect       -instancename cmp2 -net cmp2_input0    -netport Input0
ihwconnect       -instancename cmp2 -net cmp2_input1    -netport Input1
ihwconnect       -instancename cmp2 -net cmp2_input2    -netport Input2
ihwconnect       -instancename cmp2 -net cmp2_input3    -netport Input3
ihwconnect       -instancename cmp2 -net cmp2_input4    -netport Input4
ihwconnect       -instancename cmp2 -net cmp2_input5    -netport Input5
ihwconnect       -instancename cmp2 -net cmp2_input6    -netport Input6
ihwconnect       -instancename cmp2 -net cmp2_DacOutput -netport DacOutput
ihwconnect       -instancename cmp2 -net cmp2_extsample -netport ExtSample
ihwconnect       -instancename cmp2 -net cmp2_coutsoc   -netport CoutSoc
ihwconnect       -instancename cmp2 -net cmp2_cmpopad   -netport CmpOPad

ihwaddperipheral -instancename cmp3 -vendor $vendor -type KinetisCMP
ihwconnect       -instancename cmp3 -bus  pBus -busslaveport  bport1 -loaddress 0x40073018 -hiaddress 0x4007301f
ihwsetparameter    -handle       cmp3 -name cmpNumber     -type uns32 -value 3
ihwconnect       -instancename cmp3 -net int98          -netport Interrupt
ihwconnect       -instancename cmp3 -net cmp3_dmareq    -netport DmaReq
ihwconnect       -instancename cmp3 -net cmp_vin1       -netport Vin1
ihwconnect       -instancename cmp3 -net cmp_vin2       -netport Vin2
ihwconnect       -instancename cmp3 -net cmp3_input0    -netport Input0
ihwconnect       -instancename cmp3 -net cmp3_input1    -netport Input1
ihwconnect       -instancename cmp3 -net cmp3_input2    -netport Input2
ihwconnect       -instancename cmp3 -net cmp3_input3    -netport Input3
ihwconnect       -instancename cmp3 -net cmp3_input4    -netport Input4
ihwconnect       -instancename cmp3 -net cmp3_input5    -netport Input5
ihwconnect       -instancename cmp3 -net cmp3_input6    -netport Input6
ihwconnect       -instancename cmp3 -net cmp3_DacOutput -netport DacOutput
ihwconnect       -instancename cmp3 -net cmp3_extsample -netport ExtSample
ihwconnect       -instancename cmp3 -net cmp3_coutsoc   -netport CoutSoc
ihwconnect       -instancename cmp3 -net cmp3_cmpopad   -netport CmpOPad

# 0x40074000    0x40074fff  Peripheral Bridge 0 slot  116 - VREF: Voltage Reference
ihwaddperipheral -instancename vref -vendor $vendor -library peripheral -type KinetisVREF
ihwconnect       -instancename vref -bus  pBus -busslaveport  bport1 -loaddress 0x40074000 -hiaddress 0x40074fff

# 0x4007c000    0x4007cfff  Peripheral Bridge 0 slot 124 - LLWU: Low-leakage wakeup unit 
ihwaddperipheral -instancename llwu -vendor $vendor -library peripheral -type KinetisLLWU
ihwconnect       -instancename llwu -bus  pBus -busslaveport  bport1 -loaddress 0x4007c000 -hiaddress 0x4007cfff

# 0x4007d000    0x4007dfff  Peripheral Bridge 0 slot 125 - PMC: Power Management Controller 
ihwaddperipheral -instancename pmc -vendor $vendor -library peripheral -type KinetisPMC
ihwconnect       -instancename pmc -bus  pBus -busslaveport  bport1 -loaddress 0x4007d000 -hiaddress 0x4007dfff

# 0x4007e000    0x4007efff  Peripheral Bridge 0 slot 126 - SMC: System Mode Controller
ihwaddperipheral -instancename smc -vendor $vendor -library peripheral -type KinetisSMC
ihwconnect       -instancename smc -bus  pBus -busslaveport  bport1 -loaddress 0x4007e000 -hiaddress 0x4007efff

# 0x4007f000    0x4007ffff  Peripheral Bridge 0 slot 127 - RCM: Reset Control Module
ihwaddperipheral -instancename rcm -vendor $vendor -library peripheral -type KinetisRCM
ihwconnect       -instancename rcm -bus  pBus -busslaveport  bport1 -loaddress 0x4007f000 -hiaddress 0x4007ffff

#AIPS1

# 0x400a0000    0x400a0fff  Peripheral Bridge 1 slot 32 - RNG: Random number generator
ihwaddperipheral -instancename rng  -vendor $vendor -library peripheral -type KinetisRNG
ihwconnect       -instancename rng  -bus  pBus -busslaveport  bport1 -loaddress 0x400a0000 -hiaddress 0x400a0fff

# 0x400a4000    0x400a4fff  Peripheral Bridge 1 slot 36 - CAN: FlexCAN 1
ihwaddperipheral -instancename can1  -vendor $vendor -library peripheral -type KinetisCAN
ihwconnect       -instancename can1  -bus  pBus -busslaveport  bport1 -loaddress 0x400a4000 -hiaddress 0x400a4fff

# 0x400a8000    0x400abfff  Peripheral Bridge 1 slot 40-43 - NFC: NAND flash controller
ihwaddperipheral -instancename nfc  -vendor $vendor -library peripheral -type KinetisNFC
ihwconnect       -instancename nfc  -bus  pBus -busslaveport  bport1 -loaddress 0x400a8000 -hiaddress 0x400abfff

# 0x400ac000    0x400acfff  Peripheral Bridge 1 slot 44 - SPI2
ihwaddperipheral -instancename spi2  -vendor $vendor -library peripheral -type KinetisSPI
ihwconnect       -instancename spi2  -bus  pBus -busslaveport  bport1 -loaddress 0x400ac000 -hiaddress 0x400acfff

# 0x400ae000    0x400aefff  Peripheral Bridge 1 slot 46 - DDR
ihwaddperipheral -instancename ddr  -vendor $vendor -library peripheral -type KinetisDDR
ihwconnect       -instancename ddr  -bus  pBus -busslaveport  bport1 -loaddress 0x400ae000 -hiaddress 0x400aefff

# 0x400af000    0x400affff  Peripheral Bridge 1 slot 47 - I2S1
ihwaddperipheral -instancename i2s1  -vendor $vendor -library peripheral -type KinetisI2S
ihwconnect       -instancename i2s1  -bus  pBus -busslaveport  bport1 -loaddress 0x400af000 -hiaddress 0x400affff

# 0x400b1000    0x400b1fff  Peripheral Bridge 1 slot 49 - SDHC
ihwaddperipheral -instancename sdhc  -vendor $vendor -library peripheral -type KinetisSDHC
ihwconnect       -instancename sdhc  -bus  pBus -busslaveport  bport1 -loaddress 0x400b1000 -hiaddress 0x400b1fff

# 0x400b8000    0x400b8fff  Peripheral Bridge 1 slot 56 - FTM: FlexTimer 2
ihwaddperipheral -instancename ftm2  -vendor $vendor -library peripheral -type KinetisFTM
ihwconnect       -instancename ftm2  -bus  pBus -busslaveport  bport1 -loaddress 0x400b8000 -hiaddress 0x400b8fff
ihwconnect       -instancename ftm2 -net ftm2_phaseA -netport PhaseA
ihwconnect       -instancename ftm2 -net ftm2_phaseB -netport PhaseB
ihwconnect       -instancename ftm2 -net int64 -netport Interrupt

# 0x400b9000    0x400b9fff  Peripheral Bridge 1 slot 57 - FTM: FlexTimer 3
ihwaddperipheral -instancename ftm3  -vendor $vendor -library peripheral -type KinetisFTM
ihwconnect       -instancename ftm3  -bus  pBus -busslaveport  bport1 -loaddress 0x400b9000 -hiaddress 0x400b9fff
ihwconnect       -instancename ftm3 -net ftm3_phaseA -netport PhaseA
ihwconnect       -instancename ftm3 -net ftm3_phaseB -netport PhaseB
ihwconnect       -instancename ftm3 -net int101 -netport Interrupt

# 0x400bb000    0x400bbfff  Peripheral Bridge 1 slot 59 - ADC: Analog-to-digital converter 1
ihwaddperipheral -instancename adc1  -vendor $vendor -library peripheral -type KinetisADC
ihwconnect       -instancename adc1  -bus  pBus -busslaveport  bport1 -loaddress 0x400bb000 -hiaddress 0x400bbfff
ihwconnect       -instancename adc1 -netport AdIn       -net adc1_input
ihwconnect       -instancename adc1 -netport AdInId      -net adc1_sample
ihwconnect       -instancename adc1 -netport HwTrig     -net adc1_trigger

# 0x400bc000    0x400bcfff  Peripheral Bridge 1 slot 60 - ADC: Analog-to-digital converter 3
ihwaddperipheral -instancename adc3  -vendor $vendor -library peripheral -type KinetisADC
ihwconnect       -instancename adc3  -bus  pBus -busslaveport  bport1 -loaddress 0x400bc000 -hiaddress 0x400bcfff
ihwconnect       -instancename adc3 -netport AdIn       -net adc3_input
ihwconnect       -instancename adc3 -netport AdInId      -net adc3_sample
ihwconnect       -instancename adc3 -netport HwTrig     -net adc3_trigger

# 0x400c0000    0x400c0fff  Peripheral Bridge 1 slot 64 - ENET: Ethernet MAC and IEEE 1588 timers
ihwaddperipheral -instancename enet  -vendor $vendor -library peripheral -type KinetisENET
ihwconnect       -instancename enet  -bus  pBus -busslaveport  bport1 -loaddress 0x400c0000 -hiaddress 0x400c0fff

# 0x400cc000    0x400ccfff  Peripheral Bridge 1 slot 76 - DAC: 12-bit digital-to-analog convert 0
ihwaddperipheral -instancename dac0  -vendor $vendor -library peripheral -type KinetisDAC
ihwconnect       -instancename dac0  -bus  pBus -busslaveport  bport1 -loaddress 0x400cc000 -hiaddress 0x400ccfff

# 0x400cd000    0x400cdfff  Peripheral Bridge 1 slot 77 - DAC: 12-bit digital-to-analog convert 1
ihwaddperipheral -instancename dac1  -vendor $vendor -library peripheral -type KinetisDAC
ihwconnect       -instancename dac1  -bus  pBus -busslaveport  bport1 -loaddress 0x400cd000 -hiaddress 0x400cdfff

# 0x400e5000    0x400e5fff  Peripheral Bridge 1 slot 101 - OSC1: System Oscillator 1
ihwaddperipheral -instancename osc1  -vendor $vendor -library peripheral -type KinetisOSC
ihwconnect       -instancename osc1  -bus  pBus -busslaveport  bport1 -loaddress 0x400e5000 -hiaddress 0x400e5fff

# 0x400ea000    0x400eafff  Peripheral Bridge 1 slot 106 - UART4
ihwaddperipheral -instancename uart4  -type KinetisUART -vendor $vendor -library peripheral
ihwconnect       -instancename uart4  -bus  pBus -busslaveport  bport1 -loaddress 0x400ea000 -hiaddress 0x400eafff
ihwconnect       -instancename uart4  -net  int53 -netport Interrupt
ihwsetparameter    -handle       uart4  -name fifoSize           -type uns32  -value 1
ihwsetparameter    -handle       uart4  -name moduleClkFreq      -type uns32  -value $uartClkFreq
ihwsetparameter    -handle       uart4  -name finishOnDisconnect -type bool   -value 1
ihwsetparameter    -handle       uart4  -name outfile            -type string -value uart4_outfile.txt
ihwconnect       -instancename uart4  -net  uart4_tx -netport DirectWrite
ihwconnect       -instancename uart4  -net  uart4_rx -netport DirectRead

# 0x400eb000    0x400ebfff  Peripheral Bridge 1 slot 107 - UART5
ihwaddperipheral -instancename uart5  -type KinetisUART -vendor $vendor -library peripheral
ihwconnect       -instancename uart5  -bus  pBus -busslaveport  bport1 -loaddress 0x400eb000 -hiaddress 0x400ebfff
ihwconnect       -instancename uart5  -net  int55 -netport Interrupt
ihwsetparameter    -handle       uart5  -name fifoSize           -type uns32  -value 1
ihwsetparameter    -handle       uart5  -name moduleClkFreq      -type uns32  -value $uartClkFreq
ihwsetparameter    -handle       uart5  -name finishOnDisconnect -type bool   -value 1
ihwsetparameter    -handle       uart5  -name outfile            -type string -value uart5_outfile.txt
ihwconnect       -instancename uart5  -net  uart5_tx -netport DirectWrite
ihwconnect       -instancename uart5  -net  uart5_rx -netport DirectRead



ihwaddperipheral -instancename gpioA  -type KinetisGPIO -vendor $vendor
ihwconnect       -instancename gpioA  -bus  pBus -busslaveport  bport1 -loaddress 0x400ff000 -hiaddress 0x400ff03f
ihwconnect       -instancename gpioA  -net gpioA_in -netport Input
ihwconnect       -instancename gpioA  -net gpioA_out -netport Output
ihwconnect       -instancename gpioA  -net gpioA_mask -netport OutputMask

ihwaddperipheral -instancename gpioB  -type KinetisGPIO -vendor $vendor
ihwconnect       -instancename gpioB  -bus  pBus -busslaveport  bport1 -loaddress 0x400ff040 -hiaddress 0x400ff07f
ihwconnect       -instancename gpioB  -net gpioB_in -netport Input
ihwconnect       -instancename gpioB  -net gpioB_out -netport Output
ihwconnect       -instancename gpioB  -net gpioB_mask -netport OutputMask

ihwaddperipheral -instancename gpioC  -type KinetisGPIO -vendor $vendor
ihwconnect       -instancename gpioC  -bus  pBus -busslaveport  bport1 -loaddress 0x400ff080 -hiaddress 0x400ff0bf
ihwconnect       -instancename gpioC  -net gpioC_in -netport Input
ihwconnect       -instancename gpioC  -net gpioC_out -netport Output
ihwconnect       -instancename gpioC  -net gpioC_mask -netport OutputMask

ihwaddperipheral -instancename gpioD  -type KinetisGPIO -vendor $vendor
ihwconnect       -instancename gpioD  -bus  pBus -busslaveport  bport1 -loaddress 0x400ff0c0 -hiaddress 0x400ff0ff
ihwconnect       -instancename gpioD  -net gpioD_in -netport Input
ihwconnect       -instancename gpioD  -net gpioD_out -netport Output
ihwconnect       -instancename gpioD  -net gpioD_mask -netport OutputMask

ihwaddperipheral -instancename gpioE  -type KinetisGPIO -vendor $vendor
ihwconnect       -instancename gpioE  -bus  pBus -busslaveport  bport1 -loaddress 0x400ff100 -hiaddress 0x400ff13f
ihwconnect       -instancename gpioE  -net gpioE_in -netport Input
ihwconnect       -instancename gpioE  -net gpioE_out -netport Output
ihwconnect       -instancename gpioE  -net gpioE_mask -netport OutputMask

ihwaddperipheral -instancename gpioF  -type KinetisGPIO -vendor $vendor
ihwconnect       -instancename gpioF  -bus  pBus -busslaveport  bport1 -loaddress 0x400ff140 -hiaddress 0x400ff17f
ihwconnect       -instancename gpioF  -net gpioF_in -netport Input
ihwconnect       -instancename gpioF  -net gpioF_out -netport Output
ihwconnect       -instancename gpioF  -net gpioF_mask -netport OutputMask


#####################################################################################
# Command line arguments
#####################################################################################
ihwaddclp -allargs

# Turn on a console for a UART
ihwaddclparg -name  uart0console   -type boolvar -description "enable console on UART0"
ihwaddclparg -name  uart1console   -type boolvar -description "enable console on UART1"
ihwaddclparg -name  uart2console   -type boolvar -description "enable console on UART2"
ihwaddclparg -name  uart3console   -type boolvar -description "enable console on UART3"
ihwaddclparg -name  uart4console   -type boolvar -description "enable console on UART4"
ihwaddclparg -name  uart5console   -type boolvar -description "enable console on UART5"




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

ihwaddnetport -instancename p_gpioA_out
ihwaddnetport -instancename p_gpioA_in
ihwaddnetport -instancename p_gpioA_mask
                            
ihwaddnetport -instancename p_gpioB_out
ihwaddnetport -instancename p_gpioB_in
ihwaddnetport -instancename p_gpioB_mask
                            
ihwaddnetport -instancename p_gpioC_out
ihwaddnetport -instancename p_gpioC_in
ihwaddnetport -instancename p_gpioC_mask
                            
ihwaddnetport -instancename p_gpioD_out
ihwaddnetport -instancename p_gpioD_in
ihwaddnetport -instancename p_gpioD_mask
                            
ihwaddnetport -instancename p_gpioE_out
ihwaddnetport -instancename p_gpioE_in
ihwaddnetport -instancename p_gpioE_mask
                            
ihwaddnetport -instancename p_gpioF_out
ihwaddnetport -instancename p_gpioF_in
ihwaddnetport -instancename p_gpioF_mask
                            
ihwaddnetport -instancename p_cmp_ext_sample
ihwaddnetport -instancename p_cmp_vin1  
ihwaddnetport -instancename p_cmp_vin2   

ihwaddnetport -instancename p_cmp0_input0
ihwaddnetport -instancename p_cmp0_input1
ihwaddnetport -instancename p_cmp0_input2
ihwaddnetport -instancename p_cmp0_input3
ihwaddnetport -instancename p_cmp0_input4
ihwaddnetport -instancename p_cmp0_input5
ihwaddnetport -instancename p_cmp0_input6
ihwaddnetport -instancename p_cmp0_DacOutput
ihwaddnetport -instancename p_cmp_coutSoc
ihwaddnetport -instancename p_cmp_OPad 

ihwaddnetport -instancename p_cmp1_input0
ihwaddnetport -instancename p_cmp1_input1
ihwaddnetport -instancename p_cmp1_input2
ihwaddnetport -instancename p_cmp1_input3
ihwaddnetport -instancename p_cmp1_input4
ihwaddnetport -instancename p_cmp1_input5
ihwaddnetport -instancename p_cmp1_input6
ihwaddnetport -instancename p_cmp1_DacOutput
ihwaddnetport -instancename p_cmp2_input0
ihwaddnetport -instancename p_cmp2_input1
ihwaddnetport -instancename p_cmp2_input2
ihwaddnetport -instancename p_cmp2_input3
ihwaddnetport -instancename p_cmp2_input4
ihwaddnetport -instancename p_cmp2_input5
ihwaddnetport -instancename p_cmp2_input6
ihwaddnetport -instancename p_cmp2_DacOutput
ihwaddnetport -instancename p_cmp3_input0
ihwaddnetport -instancename p_cmp3_input1
ihwaddnetport -instancename p_cmp3_input2
ihwaddnetport -instancename p_cmp3_input3
ihwaddnetport -instancename p_cmp3_input4
ihwaddnetport -instancename p_cmp3_input5
ihwaddnetport -instancename p_cmp3_input6
ihwaddnetport -instancename p_cmp3_DacOutput
                            
ihwaddnetport -instancename p_adc0_input
ihwaddnetport -instancename p_adc0_sample
ihwaddnetport -instancename p_adc0_trigger
ihwaddnetport -instancename p_adc1_input
ihwaddnetport -instancename p_adc1_sample
ihwaddnetport -instancename p_adc1_trigger
ihwaddnetport -instancename p_adc2_input
ihwaddnetport -instancename p_adc2_sample
ihwaddnetport -instancename p_adc2_trigger
ihwaddnetport -instancename p_adc3_input
ihwaddnetport -instancename p_adc3_sample
ihwaddnetport -instancename p_adc3_trigger

ihwaddnetport -instancename p_dac0_output
ihwaddnetport -instancename p_dac1_output

ihwaddnetport -instancename p_ftm_input
ihwaddnetport -instancename p_ftm_output
ihwaddnetport -instancename p_ftm_mask
ihwaddnetport -instancename p_ftm_fault
ihwaddnetport -instancename p_ftm_phaseA
ihwaddnetport -instancename p_ftm_phaseB

ihwaddnetport -instancename p_can0_tx
ihwaddnetport -instancename p_can0_rx
ihwaddnetport -instancename p_can1_tx
ihwaddnetport -instancename p_can1_rx

ihwaddnetport -instancename p_spi0_tx
ihwaddnetport -instancename p_spi0_rx
ihwaddnetport -instancename p_spi1_tx
ihwaddnetport -instancename p_spi1_rx
ihwaddnetport -instancename p_spi2_tx
ihwaddnetport -instancename p_spi2_rx

ihwaddnetport -instancename p_i2c0_tx
ihwaddnetport -instancename p_i2c0_rx
ihwaddnetport -instancename p_i2c1_tx
ihwaddnetport -instancename p_i2c1_rx

ihwaddnetport -instancename p_i2s0_tx
ihwaddnetport -instancename p_i2s0_rx
ihwaddnetport -instancename p_i2s1_tx
ihwaddnetport -instancename p_i2s1_rx

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

ihwconnect -netport p_gpioA_out        -net gpioA_out
ihwconnect -netport p_gpioA_in         -net gpioA_in
ihwconnect -netport p_gpioA_mask       -net gpioA_mask

ihwconnect -netport p_gpioB_out        -net gpioB_out
ihwconnect -netport p_gpioB_in         -net gpioB_in
ihwconnect -netport p_gpioB_mask       -net gpioB_mask

ihwconnect -netport p_gpioC_out        -net gpioC_out
ihwconnect -netport p_gpioC_in         -net gpioC_in
ihwconnect -netport p_gpioC_mask       -net gpioC_mask

ihwconnect -netport p_gpioD_out        -net gpioD_out
ihwconnect -netport p_gpioD_in         -net gpioD_in
ihwconnect -netport p_gpioD_mask       -net gpioD_mask

ihwconnect -netport p_gpioE_out        -net gpioE_out
ihwconnect -netport p_gpioE_in         -net gpioE_in
ihwconnect -netport p_gpioE_mask       -net gpioE_mask

ihwconnect -netport p_gpioF_out        -net gpioF_out
ihwconnect -netport p_gpioF_in         -net gpioF_in
ihwconnect -netport p_gpioF_mask       -net gpioF_mask

ihwconnect -netport p_cmp_ext_sample   -net cmp_ext_sample
ihwconnect -netport p_cmp_vin1         -net cmp_vin1  
ihwconnect -netport p_cmp_vin2         -net cmp_vin2   
ihwconnect -netport p_cmp0_input0       -net cmp0_input0
ihwconnect -netport p_cmp0_input1       -net cmp0_input1
ihwconnect -netport p_cmp0_input2       -net cmp0_input2
ihwconnect -netport p_cmp0_input3       -net cmp0_input3
ihwconnect -netport p_cmp0_input4       -net cmp0_input4
ihwconnect -netport p_cmp0_input5       -net cmp0_input5
ihwconnect -netport p_cmp0_input6       -net cmp0_input6
ihwconnect -netport p_cmp0_DacOutput    -net cmp0_DacOutput
ihwconnect -netport p_cmp_coutSoc      -net cmp_coutSoc
ihwconnect -netport p_cmp_OPad         -net cmp_OPad 

ihwconnect -netport p_cmp1_input0       -net cmp1_input0
ihwconnect -netport p_cmp1_input1       -net cmp1input1
ihwconnect -netport p_cmp1_input2       -net cmp1input2
ihwconnect -netport p_cmp1_input3       -net cmp1input3
ihwconnect -netport p_cmp1_input4       -net cmp1input4
ihwconnect -netport p_cmp1_input5       -net cmp1input5
ihwconnect -netport p_cmp1_input6       -net cmp1input6
ihwconnect -netport p_cmp1_DacOutput    -net cmp1_DacOutput
ihwconnect -netport p_cmp2_input0       -net cmp2_input0
ihwconnect -netport p_cmp2_input1       -net cmp2_input1
ihwconnect -netport p_cmp2_input2       -net cmp2_input2
ihwconnect -netport p_cmp2_input3       -net cmp2_input3
ihwconnect -netport p_cmp2_input4       -net cmp2_input4
ihwconnect -netport p_cmp2_input5       -net cmp2_input5
ihwconnect -netport p_cmp2_input6       -net cmp2_input6
ihwconnect -netport p_cmp2_DacOutput    -net cmp2_DacOutput
ihwconnect -netport p_cmp3_input0       -net cmp3_input0
ihwconnect -netport p_cmp3_input1       -net cmp3_input1
ihwconnect -netport p_cmp3_input2       -net cmp3_input2
ihwconnect -netport p_cmp3_input3       -net cmp3_input3
ihwconnect -netport p_cmp3_input4       -net cmp3_input4
ihwconnect -netport p_cmp3_input5       -net cmp3_input5
ihwconnect -netport p_cmp3_input6       -net cmp3_input6
ihwconnect -netport p_cmp3_DacOutput    -net cmp3_DacOutput

ihwconnect -netport p_adc0_input       -net adc0_input
ihwconnect -netport p_adc0_sample      -net adc0_sample
ihwconnect -netport p_adc0_trigger     -net adc0_trigger
ihwconnect -netport p_adc1_input       -net adc1_input
ihwconnect -netport p_adc1_sample      -net adc1_sample
ihwconnect -netport p_adc1_trigger     -net adc1_trigger
ihwconnect -netport p_adc2_input       -net adc2_input
ihwconnect -netport p_adc2_sample      -net adc2_sample
ihwconnect -netport p_adc2_trigger     -net adc2_trigger
ihwconnect -netport p_adc3_input       -net adc3_input
ihwconnect -netport p_adc3_sample      -net adc3_sample
ihwconnect -netport p_adc3_trigger     -net adc3_trigger

ihwconnect -netport p_dac0_output      -net dac0_output
ihwconnect -netport p_dac1_output      -net dac1_output

ihwconnect -netport p_ftm_input        -net ftm_input
ihwconnect -netport p_ftm_output       -net ftm_output
ihwconnect -netport p_ftm_mask         -net ftm_mask
ihwconnect -netport p_ftm_fault        -net ftm_fault
ihwconnect -netport p_ftm_phaseA       -net ftm_phaseA
ihwconnect -netport p_ftm_phaseB       -net ftm_phaseB

ihwconnect -netport p_can0_tx          -net can0_tx
ihwconnect -netport p_can0_rx          -net can0_rx
ihwconnect -netport p_can1_tx          -net can1_tx
ihwconnect -netport p_can1_rx          -net can1_rx

ihwconnect -netport p_spi0_tx          -net spi0_tx
ihwconnect -netport p_spi0_rx          -net spi0_rx
ihwconnect -netport p_spi1_tx          -net spi1_tx
ihwconnect -netport p_spi1_rx          -net spi1_rx
ihwconnect -netport p_spi2_tx          -net spi2_tx
ihwconnect -netport p_spi2_rx          -net spi2_rx

ihwconnect -netport p_i2c0_tx          -net i2c0_tx
ihwconnect -netport p_i2c0_rx          -net i2c0_rx
ihwconnect -netport p_i2c1_tx          -net i2c1_tx
ihwconnect -netport p_i2c1_rx          -net i2c1_rx

ihwconnect -netport p_i2s0_tx          -net i2s0_tx
ihwconnect -netport p_i2s0_rx          -net i2s0_rx
ihwconnect -netport p_i2s1_tx          -net i2s1_tx
ihwconnect -netport p_i2s1_rx          -net i2s1_rx

#####################################################################################

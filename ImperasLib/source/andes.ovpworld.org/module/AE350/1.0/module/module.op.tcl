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


ihwnew -name AE350  \
  -vendor   andes.ovpworld.org  \
  -library  module  \
  -version  1.0 \
  \
  -stoponctrlc \
  -purpose module -releasestatus ovp


iadddocumentation -name Licensing    -text "Open Source Apache 2.0"

iadddocumentation -name Description  -text "Andes AE350 module (skeleton)"

iadddocumentation -name Reference    -text "Andes BSP v5.0 ae350 BSP Definition"
# Definition from BSPv501/x86/amsi/bsp/v5/ae350/ae350.h

iadddocumentation -name Limitations  -text "This is a skeleton platform that contains only those peripherals required to boot FreeRTOS demo."
iadddocumentation -name Limitations  -text "The following peripherals are register only models that do not provide any behavior:"
iadddocumentation -name Limitations  -text "  - BMC"
iadddocumentation -name Limitations  -text "  - AHBDEC"
iadddocumentation -name Limitations  -text "  - MAC"
iadddocumentation -name Limitations  -text "  - LCDC"
iadddocumentation -name Limitations  -text "  - SMC"
iadddocumentation -name Limitations  -text "  - PLIC_SW"
iadddocumentation -name Limitations  -text "  - PLDM"
iadddocumentation -name Limitations  -text "  - APBBRG"
iadddocumentation -name Limitations  -text "  - SMU"
iadddocumentation -name Limitations  -text "  - PIT"
iadddocumentation -name Limitations  -text "  - WDT"
iadddocumentation -name Limitations  -text "  - RTC"
iadddocumentation -name Limitations  -text "  - GPIO"
iadddocumentation -name Limitations  -text "  - I2C"
iadddocumentation -name Limitations  -text "  - SPI1"
iadddocumentation -name Limitations  -text "  - DMAC"
iadddocumentation -name Limitations  -text "  - AC97"
iadddocumentation -name Limitations  -text "  - SDC"
iadddocumentation -name Limitations  -text "  - SPI2"
iadddocumentation -name Limitations  -text "The UART does not support dma mode, so if using the Andes AMSI BSP you should set RTE_UART*_DMA_*X_EN=0 in RTE_Device.h"

#################### module formal parameters #####################

ihwaddformalparameter -name buswidth -type uns32 -defaultvalue 37
ihwaddbus -instancename bus0  -addresswidth {buswidth}

############################ processor ############################

ihwaddprocessor  \
  -instancename cpu0  \
  -type         riscv \
  -vendor       andes.ovpworld.org \
  -library      processor \
  -version      1.0 \
  -endian       little \
  -mips         60 \
  -simulateexceptions

ihwsetparameter -handle cpu0 -name variant -value NX25 -type enum

ihwconnect -instancename cpu0  -busmasterport INSTRUCTION -bus bus0
ihwconnect -instancename cpu0  -busmasterport DATA        -bus bus0

############################## memory #############################

ihwaddmemory -instancename eilm -type ram
ihwconnect   -instancename eilm -busslaveport sp1 -bus bus0 -loaddress 0x00000000 -hiaddress 0x001FFFFF

ihwaddmemory -instancename edlm -type ram
ihwconnect   -instancename edlm -busslaveport sp1 -bus bus0 -loaddress 0x00200000 -hiaddress 0x002FFFFF

ihwaddmemory -instancename spimem -type ram
ihwconnect   -instancename spimem -busslaveport sp1 -bus bus0 -loaddress 0x80000000 -hiaddress 0x801FFFFF

ihwaddmemory -instancename stack -type ram
ihwconnect   -instancename stack -busslaveport sp1 -bus bus0 -loaddress 0x07ff0000 -hiaddress 0x07FFFFFF

########################### peripherals ###########################

proc addDummy {name address} {
#    puts "Add DUMMY $name $address"
    ihwaddperipheral -instancename ${name} -vendor ovpworld.org -library peripheral -type trap -version 1.0
# remove as this will mess up the module documentation
#    iadddocumentation -name Description  -text "This device is a dummy and provides a memory region only"
    ihwconnect       -instancename ${name} -bus bus0 -busslaveport bport1 
    ihwsetparameter -handle ${name} -name portAddress -type uns32 -value $address
    ihwsetparameter -handle ${name} -name portSize    -type uns32 -value 0x1000
    ihwsetparameter -handle ${name} -name cbEnable    -type bool  -value 1
}

proc addPeripheral {name vendor type loaddress hiaddress} {
#    puts "Add $name $vendor $type $loaddress $hiaddress"
    ihwaddperipheral -instancename $name -vendor $vendor -library peripheral -type $type -version 1.0
    ihwconnect       -instancename $name -bus bus0 -busslaveport bport1 -loaddress $loaddress -hiaddress $hiaddress
}

addDummy BMC      0xC0000000
addDummy AHBDEC   0xE0000000
addDummy MAC      0xE0100000
addDummy LCDC     0xE0200000
addDummy SMC      0xE0400000

ihwaddperipheral -instancename PLIC -vendor andes.ovpworld.org -library peripheral -type NCEPLIC100 -version 1.0
ihwconnect -instancename PLIC -bus bus0 -busslaveport port0 -loaddress 0xE4000000 -hiaddress 0xE43FFFFF
ihwaddnet  -instancename MExternalInterrupt
ihwconnect -instancename PLIC -netport irqT0                 -net MExternalInterrupt
ihwconnect -instancename cpu0 -netport MExternalInterrupt    -net MExternalInterrupt
ihwaddnet  -instancename MExternalInterruptID
ihwconnect -instancename PLIC -netport t0_eiid               -net MExternalInterruptID
ihwconnect -instancename cpu0 -netport MExternalInterruptID  -net MExternalInterruptID
ihwaddnet  -instancename MExternalInterruptACK
ihwconnect -instancename PLIC -netport t0_eiack              -net MExternalInterruptACK
ihwconnect -instancename cpu0 -netport MExternalInterruptACK -net MExternalInterruptACK

addPeripheral PLMT  andes.ovpworld.org NCEPLMT100   0xE6000000 0xE60000FF
ihwsetparameter -handle PLMT -name numharts            -type uns32  -value 1
ihwsetparameter -handle PLMT -name clockMHz            -type double -value 60
ihwaddnet  -instancename mtip
ihwconnect -instancename cpu0 -netport MTimerInterrupt -net mtip
ihwconnect -instancename PLMT -netport intOut_0        -net mtip

addDummy PLIC_SW  0xE6400000
addDummy PLDM     0xE6800000
addDummy APBBRG   0xF0000000
addDummy SMU      0xF0100000

addPeripheral UART1  andes.ovpworld.org ATCUART100  0xF0200000 0xF020003F
ihwsetparameter -handle UART1 -name console            -type bool -value 1
ihwsetparameter -handle UART1 -name finishOnDisconnect -type bool -value 1
ihwaddnet  -instancename uart1Irq
ihwconnect -instancename PLIC  -netport irqS8  -net uart1Irq
ihwconnect -instancename UART1 -netport intOut -net uart1Irq

addPeripheral UART2  andes.ovpworld.org ATCUART100  0xF0300000 0xF030003F
ihwsetparameter -handle UART2 -name console            -type bool -value 1
ihwsetparameter -handle UART2 -name finishOnDisconnect -type bool -value 1
ihwaddnet  -instancename uart2Irq
ihwconnect -instancename PLIC  -netport irqS9  -net uart2Irq
ihwconnect -instancename UART2 -netport intOut -net uart2Irq

addDummy PIT      0xF0400000
addDummy WDT      0xF0500000
addDummy RTC      0xF0600000
addDummy GPIO     0xF0700000
addDummy I2C      0xF0A00000
addDummy SPI1     0xF0B00000
addDummy DMAC     0xF0C00000
addDummy AC97     0xF0D00000
addDummy SDC      0xF0E00000
addDummy SPI2     0xF0F00000

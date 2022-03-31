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

#
# Generic AT91SAM7 platform
#
set vendor   atmel.ovpworld.org
set library  module
set name     AtmelAT91SAM7
set version  1.0

ihwnew -name $name -vendor $vendor -library $library -version $version -releasestatus ovp -purpose module

iadddocumentation -name Description -text "\
Simple platform of Atmel AT91 ARM7TDMI based system
"
iadddocumentation -name Limitations -text "This platform is sufficient to boot Linux"
iadddocumentation -name Reference   -text "Rev. 1354D ARM08/02"

iadddocumentation  \
  -name Licensing  \
  -text "Open Source Apache 2.0"

ihwaddbus -instancename mainbus -addresswidth 32

ihwaddprocessor -instancename ARM7TDMICore -type arm -vendor arm.ovpworld.org -endian little -simulateexceptions \
                -semihostname loader -semihostlibrary intercept -semihostvendor atmel.ovpworld.org 
#
# This need setting when supported in the XML
#
ihwsetparameter -handle ARM7TDMICore -name variant -value ARM7TDMI             -type enum
ihwconnect -instancename ARM7TDMICore -bus mainbus -busmasterport INSTRUCTION
ihwconnect -instancename ARM7TDMICore -bus mainbus -busmasterport DATA
ihwaddnet -instancename NFIQ
ihwconnect -instancename ARM7TDMICore -net NFIQ -netport fiq
ihwaddnet -instancename NIRQ
ihwconnect -instancename ARM7TDMICore -net NIRQ -netport irq

#
# External Devices - map as memory
#
ihwaddmemory -instancename extDev -type ram
ihwconnect   -instancename extDev -bus mainbus -busslaveport sp1 -loaddress 0x00400000 -hiaddress 0xFFBFFFFF

#
# On Chip Primary RAM bank0 1Mbyte
# Before Remap 0x00300000 - 0x003FFFFF
# After  Remap 0x00000000 - 0x000FFFFF
#
ihwaddmemory -instancename ram0 -type ram
ihwconnect   -instancename ram0 -bus mainbus -busslaveport sp1 -loaddress 0x0000000 -hiaddress 0x000FFFFF

#
# Advanced Interrupt Controller
#
ihwaddperipheral -instancename AIC -type AdvancedInterruptController -vendor atmel.ovpworld.org
ihwconnect       -instancename AIC -bus mainbus -busslaveport bp1 -loaddress 0xfffff000 -hiaddress 0xffffffff
foreach net {US0IRQ US1IRQ TC0IRQ TC1IRQ TC2IRQ WDIRQ PIOIRQ} {
    ihwaddnet  -instancename ${net}
    ihwconnect -instancename AIC -net ${net} -netport ${net}
}
ihwconnect -instancename AIC -net NFIQ -netport NFIQ
ihwconnect -instancename AIC -net NIRQ -netport NIRQ

#
# Watchdog Timer
#
ihwaddperipheral -instancename WD -type WatchdogTimer -vendor atmel.ovpworld.org
ihwconnect       -instancename WD -bus mainbus -busslaveport bp1 -loaddress 0xffff8000 -hiaddress 0xffffbfff
ihwconnect       -instancename WD -net WDIRQ -netport IRQ

#
# Power Saving
#
ihwaddperipheral -instancename PS -type PowerSaving -vendor atmel.ovpworld.org
ihwconnect       -instancename PS -bus mainbus -busslaveport bp1 -loaddress 0xffff4000 -hiaddress 0xffff7fff

#
# Parallel I/O Controller
#
ihwaddperipheral -instancename PIO -type ParallelIOController -vendor atmel.ovpworld.org
ihwconnect       -instancename PIO -bus mainbus -busslaveport bp1 -loaddress 0xffff0000 -hiaddress 0xffff3fff
ihwconnect       -instancename PIO -net PIOIRQ -netport IRQ

#
# Timer Counter
#
ihwaddperipheral -instancename TC -type TimerCounter -vendor atmel.ovpworld.org
ihwconnect       -instancename TC -bus mainbus -busslaveport bp1 -loaddress 0xfffe0000 -hiaddress 0xfffe3fff
ihwconnect       -instancename TC -net TC0IRQ -netport IRQ0
ihwconnect       -instancename TC -net TC1IRQ -netport IRQ1
ihwconnect       -instancename TC -net TC2IRQ -netport IRQ2

#
# Usart0
#
ihwaddperipheral -instancename USART0 -type UsartInterface -vendor atmel.ovpworld.org
ihwconnect       -instancename USART0 -bus mainbus -busslaveport apb -loaddress 0xfffd0000 -hiaddress 0xfffd3fff
ihwconnect       -instancename USART0 -bus mainbus -busmasterport asb
ihwconnect       -instancename USART0 -net US0IRQ -netport IRQ
ihwsetparameter    -handle       USART0 -name finishOnDisconnect -value 1              -type bool

#
# Usart1
#
ihwaddperipheral -instancename USART1 -type UsartInterface -vendor atmel.ovpworld.org
ihwconnect       -instancename USART1 -bus mainbus -busslaveport apb -loaddress 0xfffcc000 -hiaddress 0xfffcffff
ihwconnect       -instancename USART1 -bus mainbus -busmasterport asb
ihwconnect       -instancename USART1 -net US1IRQ -netport IRQ

#
# Special Function Registers
#
ihwaddperipheral -instancename SF -type SpecialFunction -vendor atmel.ovpworld.org
ihwconnect       -instancename SF -bus mainbus -busslaveport bp1 -loaddress 0xfff00000 -hiaddress 0xfff03fff

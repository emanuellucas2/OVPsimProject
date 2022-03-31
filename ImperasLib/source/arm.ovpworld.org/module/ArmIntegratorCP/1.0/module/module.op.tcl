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

set desc "This platform models the ARM INTEGRATOR CP development board.
It provides the peripherals required to boot and run Operating Systems such as Linux or Nucleus.
The main processor is an ARM, by default this is an ARM926EJ-S (Linux) but can be overriden; for example ARM920T (Nucleus)."

#
# Platform
#
ihwnew -name ArmIntegratorCP  -vendor arm.ovpworld.org -library module -version 1.0 \
       -stoponctrlc \
       -purpose module -releasestatus ovp

iadddocumentation -name Licensing -text "Open Source Apache 2.0"

iadddocumentation -name Description -text $desc

iadddocumentation -name Limitations -text "No known limitations for executing Linux and Nucleus operating systems."

iadddocumentation -name Reference   -text "ARM Development Boards Integrator CP BaseBoard and Integrator Core Modules ARM9x6"

# Logical      Physical        What
# f1000000     10000000        Core module registers
# f1100000     11000000        System controller registers
# f1200000     12000000        EBI registers
# f1300000     13000000        Counter/Timer
# f1400000     14000000        Interrupt controller
# f1600000     16000000        UART 0
# f1700000     17000000        UART 1
# f1a00000     1a000000        Debug LEDs  (what device is this in?)
# f1b00000     1b000000        GPIO

# Physical     Size            What
# 0            0x8000000       ram
# 80000000     0x8000000       ram remapped
# 10000000     0x0800000       CoreModule9x6 controller
# 0            0x0100000       Flash (pre-remap)
# 14000000     0x0800000       PIC
# C8000000     0x0000fff       SMC9118 Ethernet Lan
# CA000000     0x0800000       ICP PIC
# CB000000     0x0800000       ICP control


#
# main bus
#
ihwaddbus -instancename bus1 -addresswidth 32

#
# Processor
#
ihwaddprocessor -instancename cpu \
                -type arm \
                -vendor arm.ovpworld.org \
                 -endian little \
                -simulateexceptions \
                -mips 200.0 \
                -enableintercepts

ihwsetparameter -handle cpu -name variant            -value Cortex-A9UP  -type enum
ihwsetparameter -handle cpu -name compatibility      -value ISA          -type enum
ihwsetparameter -handle cpu -name showHiddenRegs     -value 0            -type bool

#
# Connect processor to bus
#
ihwconnect -bus bus1 -instancename cpu -busmasterport INSTRUCTION
ihwconnect -bus bus1 -instancename cpu -busmasterport DATA

# processor to interrupt
ihwaddnet -instancename irq 
ihwaddnet -instancename fiq 
ihwconnect -net irq -instancename cpu -netport irq
ihwconnect -net fiq -instancename cpu -netport fiq

#
# Integrator Core Module
#
set cmSize 0x1000
set cmBase 0x10000000

ihwaddperipheral -instancename cm -type CoreModule9x6 -vendor arm.ovpworld.org
ihwconnect       -instancename cm -bus bus1 -busslaveport  bport1 -loaddress $cmBase -hiaddress [expr $cmBase + $cmSize - 1]

#
# PIC1
#
set picSize    0x1000
set pic1Base   0x14000000

ihwaddperipheral -instancename pic1 -type IntICP -vendor arm.ovpworld.org
ihwconnect       -instancename pic1 -bus bus1  -busslaveport  bport1 -loaddress $pic1Base -hiaddress [expr $pic1Base + $picSize - 1]
ihwconnect -net irq -instancename pic1 -netport irq
ihwconnect -net fiq -instancename pic1 -netport fiq

foreach i { 1 2 3 4 5 6 7 8 23 24 } {
    ihwaddnet -instancename ir${i}  
    ihwconnect -net ir${i} -instancename pic1 -netport ir${i}
}

#
# PIC2
#
set pic2Base   0xCA000000

ihwaddperipheral -instancename pic2 -type IntICP -vendor arm.ovpworld.org
ihwconnect       -instancename pic2 -bus bus1  -busslaveport  bport1 -loaddress $pic2Base -hiaddress [expr $pic2Base + $picSize - 1]

#
# SMC9118 Eth Lan
#
set ethBase   0xC8000000
set ethSize   0x00001000

ihwaddperipheral -instancename ethlan -vendor smsc.ovpworld.org -type LAN9118
ihwconnect       -instancename ethlan -bus bus1  -busslaveport  bport1 -loaddress $ethBase -hiaddress [expr $ethBase + $ethSize - 1]

#                                                                                                    #
# PIT
#
set pitBase   0x13000000
set pitSize   0x1000

ihwaddperipheral -instancename pit -type IcpCounterTimer -vendor arm.ovpworld.org
ihwconnect       -instancename pit -bus bus1  -busslaveport  bport1 -loaddress $pitBase -hiaddress [expr $pitBase + $pitSize - 1]

foreach i { 0 1 2 } {
       ihwconnect -net ir[expr ${i} + 5] -instancename pit -netport irq${i}
}

#
# ICP Controller (Does nothing)
#
set icpBase    0xcb000000
set icpSize    0x10

ihwaddperipheral -instancename icp -type IcpControl -vendor arm.ovpworld.org
ihwconnect       -instancename icp -bus bus1  -busslaveport  bport1 -loaddress $icpBase -hiaddress [expr $icpBase + $icpSize - 1]

#
# RAM (128M)
#
set ramSize   0x08000000
set ramBase   0x80000000
set ramShadow 0x0

ihwaddbus -instancename membus -addresswidth 32

ihwaddmemory -instancename ram1  -type ram
ihwconnect -bus membus -instancename ram1 -busslaveport sp1 -loaddress 0 -hiaddress [expr $ramSize -1]

#
# Bridge shadows the RAM
#
ihwaddbridge -instancename ram1Bridge
ihwaddbridge -instancename ram2Bridge
ihwconnect -bus bus1   -instancename ram1Bridge -busslaveport  sp -loaddress $ramShadow -hiaddress [expr $ramShadow + $ramSize -1]
ihwconnect -bus membus -instancename ram1Bridge -busmasterport mp -loaddress 0 -hiaddress [expr $ramSize -1]
ihwconnect -bus bus1   -instancename ram2Bridge -busslaveport sp1 -loaddress $ramBase -hiaddress [expr $ramBase + $ramSize -1]
ihwconnect -bus membus -instancename ram2Bridge -busmasterport mp -loaddress 0 -hiaddress [expr $ramSize -1]

#
# AMBA dummy device
#
set ambaBase  0x1D000000
set ambaSize  0x1000

ihwaddmemory -instancename ambaDummy  -type ram
ihwconnect -bus bus1 -instancename ambaDummy -busslaveport sp1 -loaddress $ambaBase -hiaddress [expr $ambaBase + $ambaSize -1]

#
# LED device
#
set ledBase  0x1a000000
set ledSize  0x1000
ihwaddperipheral -instancename ld1  -type DebugLedAndDipSwitch -vendor arm.ovpworld.org
ihwconnect -bus bus1 -instancename ld1 -busslaveport bport1 -loaddress $ledBase -hiaddress [expr $ledBase + $ledSize -1]
#
# Keyboard / Mouse
#
set kbSize  0x1000
set kb1Base 0x18000000
set kb1Ir  ir3
set kb2Base 0x19000000
set kb2Ir  ir4
set kbSize 0x1000

ihwaddperipheral -instancename kb1 -type KbPL050 -vendor arm.ovpworld.org
ihwconnect       -instancename kb1 -bus bus1  -busslaveport  bport1 -loaddress $kb1Base -hiaddress [expr $kb1Base + $kbSize - 1]
ihwconnect       -instancename kb1 -net $kb1Ir -netport irq
ihwsetparameter    -handle       kb1 -name isMouse     -value 0   -type bool
ihwsetparameter    -handle       kb1 -name grabDisable -value 0   -type bool

ihwaddperipheral -instancename ms1 -type KbPL050 -vendor arm.ovpworld.org
ihwconnect       -instancename ms1 -bus bus1  -busslaveport  bport1 -loaddress $kb2Base -hiaddress [expr $kb2Base + $kbSize - 1]
ihwconnect       -instancename ms1 -net $kb2Ir -netport irq
ihwsetparameter    -handle       ms1 -name isMouse     -value 1   -type bool
ihwsetparameter    -handle       ms1 -name grabDisable -value 1   -type bool

#
# RTC
#
set rtcSize  0x1000
set rtcBase  0x15000000
set rtcIr    ir8
ihwaddperipheral -instancename rtc -type RtcPL031 -vendor arm.ovpworld.org
ihwconnect       -instancename rtc -bus bus1   -busslaveport  bport1  -loaddress $rtcBase -hiaddress [expr $rtcBase + $rtcSize -1]
ihwconnect       -instancename rtc -net $rtcIr -netport irq

#
# Uart
#
set uartSize  0x1000
set uart1Base 0x16000000
set uart2Base 0x17000000

ihwaddperipheral -instancename uart1  -type UartPL011  -vendor arm.ovpworld.org
ihwsetparameter    -handle       uart1  -name variant            -value ARM          -type enum
ihwsetparameter    -handle       uart1  -name outfile            -value uart1.log    -type string
ihwsetparameter    -handle       uart1  -name finishOnDisconnect -value 1            -type bool
ihwconnect       -instancename uart1  -bus bus1 -busslaveport bport1 -loaddress $uart1Base -hiaddress [expr $uart1Base + $uartSize - 1]
ihwconnect       -instancename uart1  -net ir1 -netport irq


ihwaddperipheral -instancename uart2  -type UartPL011 -vendor arm.ovpworld.org
ihwsetparameter    -handle       uart2  -name variant            -value ARM        -type enum
ihwsetparameter    -handle       uart2  -name outfile            -value uart2.log  -type string
ihwsetparameter    -handle       uart2  -name finishOnDisconnect -value 1          -type bool
ihwconnect       -instancename uart2  -bus bus1 -busslaveport bport1 -loaddress $uart2Base -hiaddress [expr $uart2Base + $uartSize - 1]
ihwconnect       -instancename uart2  -net ir2 -netport irq

#
# Multimedia card interface
#
set mmciSize 0x1000
set mmciBase 0x1c000000

ihwaddperipheral -instancename mmci  -type MmciPL181 -vendor arm.ovpworld.org
ihwconnect       -instancename mmci  -bus bus1 -busslaveport bport1 -loaddress $mmciBase -hiaddress [expr $mmciBase + $mmciSize - 1]
ihwconnect       -instancename mmci  -net ir23 -netport irq0
ihwconnect       -instancename mmci  -net ir24 -netport irq1

set lcdSize 0x00001000
set lcdBase 0xc0000000

ihwaddperipheral -instancename lcd  -type LcdPL110 -vendor arm.ovpworld.org
ihwconnect       -instancename lcd  -bus bus1   -busslaveport bport1 -loaddress $lcdBase -hiaddress [expr $lcdBase + $lcdSize - 1]
ihwconnect       -instancename lcd  -bus membus -busslaveport memory
ihwsetparameter    -handle       lcd  -name busOffset -value 0x80000000     -type uns32
ihwsetparameter    -handle       lcd  -name scanDelay -value 50000          -type uns32

ihwaddperipheral -instancename smartLoader  -type SmartLoaderArmLinux -vendor arm.ovpworld.org
ihwconnect       -instancename smartLoader  -bus bus1 -busmasterport mport -loaddress 0 -hiaddress 0xffffffff


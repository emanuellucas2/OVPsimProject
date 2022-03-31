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


if {![info exists aSys]} {
	set aSys armMain
}



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
# 10000000     0x0800000       CM9x6 controller
# 0            0x0100000       Flash (pre-remap)
# 14000000     0x0800000       PIC
# CA000000     0x0800000       ICP PIC
# CB000000     0x0800000       ICP control


#
# main bus
#
ihwaddbus -instancename bus${aSys} -addresswidth 32


#
# Processor
#
ihwaddprocessor -instancename ${aSys}arm1 -type arm -vendor arm.ovpworld.org -endian little -simulateexceptions -mips 200.0 -imagefile arm.plus_demo.out
ihwsetparameter -handle ${aSys}arm1 -name variant            -value ARM920T  -type enum
ihwsetparameter -handle ${aSys}arm1 -name compatibility      -value ISA      -type enum
ihwsetparameter -handle ${aSys}arm1 -name showHiddenRegs     -value 0        -type bool

# extension library
# ihwaddextensionlibrary -instancename ${aSys}ext1 -handle ${aSys}arm1 -type unknown
# library attributes

#
# Connect processor to bus
#
ihwconnect -bus bus${aSys} -instancename ${aSys}arm1 -busmasterport INSTRUCTION
ihwconnect -bus bus${aSys} -instancename ${aSys}arm1 -busmasterport DATA

# processor to interrupt
ihwconnect -net ${aSys}irq -instancename ${aSys}arm1 -netport irq
ihwconnect -net ${aSys}fiq -instancename ${aSys}arm1 -netport fiq

#
# Integrator Core Module
#
set cmSize 0x1000
set cmBase 0x10000000

ihwaddperipheral -instancename ${aSys}cm -type CoreModule9x6 -vendor arm.ovpworld.org
ihwconnect       -instancename ${aSys}cm -bus bus${aSys} -busslaveport  bport1 -loaddress $cmBase -hiaddress [expr $cmBase + $cmSize - 1]

#
# PIC1
#
set picSize    0x1000
set pic1Base   0x14000000

ihwaddperipheral -instancename ${aSys}pic1 -type IntICP -vendor arm.ovpworld.org
ihwconnect       -instancename ${aSys}pic1 -bus bus${aSys} -busslaveport  bport1 -loaddress $pic1Base -hiaddress [expr $pic1Base + $picSize - 1]
ihwconnect -net ${aSys}irq -instancename ${aSys}pic1 -netport irq
ihwconnect -net ${aSys}fiq -instancename ${aSys}pic1 -netport fiq

foreach i { 1 2 3 4 5 6 7 8 23 24 } {
    ihwconnect -net ${aSys}ir${i} -instancename ${aSys}pic1 -netport ir${i}
}

#
# PIC2
#
set pic2Base   0xCA000000

ihwaddperipheral -instancename ${aSys}pic2 -type IntICP -vendor arm.ovpworld.org
ihwconnect       -instancename ${aSys}pic2 -bus bus${aSys} -busslaveport  bport1 -loaddress $pic2Base -hiaddress [expr $pic2Base + $picSize - 1]

#                                                                                                    #
# PIT
#
set pitBase   0x13000000
set pitSize   0x1000

ihwaddperipheral -instancename ${aSys}pit -type IcpCounterTimer -vendor arm.ovpworld.org
ihwconnect       -instancename ${aSys}pit -bus bus${aSys} -busslaveport  bport1 -loaddress $pitBase -hiaddress [expr $pitBase + $pitSize - 1]

foreach i { 0 1 2 } {
	ihwconnect -net ${aSys}ir[expr ${i} + 5] -instancename ${aSys}pit -netport irq${i}
}

#
# ICP Controller (Does nothing)
#
set icpBase    0xcb000000
set icpSize    0x10

ihwaddperipheral -instancename ${aSys}icp -type IcpControl -vendor arm.ovpworld.org
ihwconnect       -instancename ${aSys}icp -bus bus${aSys} -busslaveport  bport1 -loaddress $icpBase -hiaddress [expr $icpBase + $icpSize - 1]

#
# RAM (128M)
#
set ramSize   0x08000000
set ramBase   0x80000000
set ramShadow 0x0

ihwaddmemory -instancename ${aSys}ram1  -type ram
ihwconnect -bus bus${aSys} -instancename ${aSys}ram1 -busslaveport sp1 -loaddress $ramBase -hiaddress [expr $ramBase + $ramSize -1]

#
# Bridge shadows the RAM
#
ihwaddbridge -instancename ${aSys}ram1Bridge
ihwconnect -bus bus${aSys} -instancename ${aSys}ram1Bridge -busslaveport  sp -loaddress $ramShadow -hiaddress [expr $ramShadow + $ramSize -1]
ihwconnect -bus bus${aSys} -instancename ${aSys}ram1Bridge -busmasterport mp -loaddress $ramBase   -hiaddress [expr $ramBase   + $ramSize -1]

#
# AMBA dummy device
#
set ambaBase  0x1D000000
set ambaSize  0x1000

ihwaddmemory -instancename ${aSys}ambaDummy  -type ram
ihwconnect -bus bus${aSys} -instancename ${aSys}ambaDummy -busslaveport sp1 -loaddress $ambaBase -hiaddress [expr $ambaBase + $ambaSize -1]

#
# LED device
#
set ledBase  0x1a000000
set ledSize  0x1000
ihwaddperipheral -instancename ${aSys}ld1  -type DebugLedAndDipSwitch -vendor arm.ovpworld.org
ihwconnect -bus bus${aSys} -instancename ${aSys}ld1 -busslaveport bport1 -loaddress $ledBase -hiaddress [expr $ledBase + $ledSize -1]
#
# Keyboard / Mouse
#
set kbSize  0x1000
set kb1Base 0x18000000
set kb1Ir  ir3
set kb2Base 0x19000000
set kb2Ir  ir4
set kbSize 0x1000

ihwaddperipheral -instancename ${aSys}kb1 -type KbPL050 -vendor arm.ovpworld.org
ihwconnect       -instancename ${aSys}kb1 -bus bus${aSys} -busslaveport  bport1 -loaddress $kb1Base -hiaddress [expr $kb1Base + $kbSize - 1]
ihwconnect       -instancename ${aSys}kb1 -net ${aSys}$kb1Ir -netport irq
ihwsetparameter    -handle ${aSys}kb1 -name isMouse      -value 0     -type bool
ihwsetparameter    -handle ${aSys}kb1 -name grabDisable  -value 0     -type bool

ihwaddperipheral -instancename ${aSys}ms1 -type KbPL050 -vendor arm.ovpworld.org
ihwconnect       -instancename ${aSys}ms1 -bus bus${aSys} -busslaveport  bport1 -loaddress $kb2Base -hiaddress [expr $kb2Base + $kbSize - 1]
ihwconnect       -instancename ${aSys}ms1 -net ${aSys}$kb2Ir -netport irq
ihwsetparameter    -handle ${aSys}ms1 -name isMouse      -value 1     -type bool
ihwsetparameter    -handle ${aSys}ms1 -name grabDisable  -value 1     -type bool

#
# RTC
#
set rtcSize  0x1000
set rtcBase  0x15000000
set rtcIr    ir8
ihwaddperipheral -instancename ${aSys}rtc -type RtcPL031 -vendor arm.ovpworld.org
ihwconnect       -instancename ${aSys}rtc -bus bus${aSys} -busslaveport  bport1  -loaddress $rtcBase -hiaddress [expr $rtcBase + $rtcSize -1]
ihwconnect       -instancename ${aSys}rtc -net ${aSys}$rtcIr -netport irq

#
# Uart
#
set uartSize  0x1000
set uart1Base 0x16000000
set uart2Base 0x17000000

ihwaddperipheral -instancename ${aSys}uart1  -type UartPL011 -vendor arm.ovpworld.org
ihwsetparameter    -handle ${aSys}uart1  -name variant  -value ARM         -type enum
ihwsetparameter    -handle ${aSys}uart1  -name outfile  -value uart1.log   -type string
ihwsetparameter    -handle ${aSys}uart1  -name finishOnDisconnect -value 1 -type bool
ihwconnect       -instancename ${aSys}uart1  -bus bus${aSys} -busslaveport bport1 -loaddress $uart1Base -hiaddress [expr $uart1Base + $uartSize - 1]
ihwconnect       -instancename ${aSys}uart1  -net ${aSys}ir1 -netport irq


ihwaddperipheral -instancename ${aSys}uart2  -type UartPL011 -vendor arm.ovpworld.org
ihwsetparameter    -handle ${aSys}uart2  -name variant            -value ARM          -type enum
ihwsetparameter    -handle ${aSys}uart2  -name finishOnDisconnect -value 1            -type bool
ihwconnect       -instancename ${aSys}uart2  -bus bus${aSys} -busslaveport bport1 -loaddress $uart2Base -hiaddress [expr $uart2Base + $uartSize - 1]
ihwconnect       -instancename ${aSys}uart2  -net ${aSys}ir2 -netport irq

#
# Multimedia card interface
#
set mmciSize 0x1000
set mmciBase 0x1c000000

ihwaddperipheral -instancename ${aSys}mmci  -type MmciPL181 -vendor arm.ovpworld.org
ihwconnect       -instancename ${aSys}mmci  -bus bus${aSys} -busslaveport bport1 -loaddress $mmciBase -hiaddress [expr $mmciBase + $mmciSize - 1]
ihwconnect       -instancename ${aSys}mmci  -net ${aSys}ir23 -netport irq0
ihwconnect       -instancename ${aSys}mmci  -net ${aSys}ir24 -netport irq1

set lcdSize 0x00001000
set lcdBase 0xc0000000

ihwaddperipheral -instancename ${aSys}lcd  -type LcdPL110 -vendor arm.ovpworld.org
ihwconnect       -instancename ${aSys}lcd  -bus bus${aSys} -busslaveport bport1 -loaddress $lcdBase -hiaddress [expr $lcdBase + $lcdSize - 1]
ihwconnect       -instancename ${aSys}lcd  -bus bus${aSys} -busslaveport memory
ihwsetparameter    -handle ${aSys}lcd  -name noGraphics -value 1     -type bool

ihwaddperipheral -instancename ${aSys}smartLoader  -type SmartLoaderArmLinux -vendor arm.ovpworld.org
ihwconnect       -instancename ${aSys}smartLoader  -bus bus${aSys} -busmasterport mport -loaddress 0 -hiaddress 0xffffffff
ihwsetparameter    -handle ${aSys}smartLoader  -name disable -value 1    -type bool



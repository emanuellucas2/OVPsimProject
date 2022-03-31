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

set desc "This module implements the Zynq 7000 Processing Sub-System (PS).
          The PS integrates two ARM Cortex-A9 MPCore application processors, memories and peripherals."

set limitations1 "This module provides the peripheral behavior required to boot a Linux Kernel or XtratuM hypervisor."
set limitations2 "Some of the peripherals are register-only, non-functional models. See the individual peripheral model documentation for details."
set limitations3 "Snoop Control Unit is not implemented, Trust Zone memory protection is not implemented"

set reference "ZC702 Board user Guide UG850 (v1.5) September 4,2015 (ug850-zc702-eval-bd.pdf) and
               ZC706 Evaluation Board for the Zynq-7000 XC7Z045 All Programmable SoC (v1.6) March 29, 2016 (ug954-zc706-eval-bd-xc7z04-ap-soc.pdf) and
               Zynq-7000 AP SoC Technical Reference Manual UG585 (v1.10) February 23, 2015 (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)"

set license "Open Source Apache 2.0"

# Setup variables for platform info
set vendor  xilinx.ovpworld.org
set library module
set name    Zynq_PS
set version 1.0

#
# Start new platform creation
#
ihwnew -name $name -vendor $vendor -library $library -version $version -diagnostics -stoponctrlc -purpose module -releasestatus ovp
iadddocumentation -name Licensing   -text $license
iadddocumentation -name Description -text $desc
iadddocumentation -name Limitations -text $limitations1
iadddocumentation -name Limitations -text $limitations2
iadddocumentation -name Limitations -text $limitations3
iadddocumentation -name Reference   -text $reference

#
# pBus
#
ihwaddbus -instancename pBus  -addresswidth 32

#
# interrupt connections (not all implemented)
#
set spiInterruptList {34 l2cache 35 ocm 37 pmu0 38 pmu1 39 xadc 40 devc 41 swdt 
                      42 ttc0 43 ttc0 44 ttc0
                      45 dmaca 46 dmac0 47 dmac1 48 dmac2 49 dmac3 50 smc 51 qspi 52 gpio
                      53 usb0 54 eth0 55 eth0wu 56 sdio0 57 i2c0 58 spi0 59 uart0 60 can0 
                      69 ttc1 70 ttc1 71 ttc1
                      72 dmac4 73 dmac5 74 dmac6 75 dmac7
                      76 usb1 77 eth1 78 eth1wu 79 sdio1 80 i2c1 81 spi1 82 uart1 83 can1
                      92 spup}
# connections routed to PL (0-28)
set interruptToPLList {can1 uart1 spi1 i2c1 sdio1 eth1wu eth1 usb1
                       can0 uart0 spi0 i2c0 sdio0 eth0wu eth0 usb0
                       gpio - qspi smc dmac0 dmac1 dmac2 dmac3 dmac4 dmac5 dmac6 dmac7 dmaca}
foreach {spi name} ${spiInterruptList} {
    ihwaddnet -instancename ${name}_spi${spi}
}

#
# reset connections
#

ihwaddnet -instancename reset_A9_CPU0
ihwaddnet -instancename reset_A9_CPU1

#
# Processor
#
ihwaddformalparameter -name armmips -type Uns32
ihwaddprocessor -instancename cpu -type arm -vendor arm.ovpworld.org -version 1.0 \
                -endian little \
                -simulateexceptions \
                -mips {armmips}
ihwconnect    -instancename cpu -bus pBus -busmasterport INSTRUCTION
ihwconnect    -instancename cpu -bus pBus -busmasterport DATA
ihwsetparameter -handle       cpu -name variant        -value Cortex-A9MPx2 -type enum
ihwsetparameter -handle       cpu -name compatibility  -value ISA           -type enum
ihwsetparameter -handle       cpu -name UAL            -value 1             -type boolean
ihwsetparameter -handle       cpu -name override_CBAR  -value 0xf8f00000    -type Uns32
ihwsetparameter -handle       cpu -name override_MIDR  -value 0x413fc090    -type Uns32

# Connect processor interrupts
foreach {spi name} ${spiInterruptList} {
    ihwconnect -instancename cpu  -netport SPI${spi} -net ${name}_spi${spi}
}

# Interrupt connections PL to PS
proc addIntPL2PS {irq net} {
    ihwaddnet     -instancename irqf2p${irq}
    ihwaddnetport -instancename irqf2p${irq}_inP
    ihwconnect    -netport      irqf2p${irq}_inP    -net irqf2p${irq}
    ihwconnect    -instancename cpu -netport ${net} -net irqf2p${irq}
}

# SPI PL -> PS
# irq 0- 7 to SPI 61-68
# irq 8-15 to SPI 84-91
for {set i 0} {$i <= 15} {incr i} {
    set irq $i
    if {$i<8} {
        set spi [ expr 61 + $i     ] 
    } else {
        set spi [ expr 84 + $i - 8 ]
    }
    addIntPL2PS  ${irq} SPI${spi}
}
# IRQ, FIQ
addIntPL2PS  16 irq_CPU0
addIntPL2PS  17 fiq_CPU0
addIntPL2PS  18 irq_CPU1
addIntPL2PS  19 fiq_CPU1

# IOP Interrupt connections PS to PL
proc addIntPS2PL {irq net} {
    ihwaddnetport -instancename irqp2f${irq}_outP
    if { ${net} == "-" } {
        # no net specified so connect to default
        ihwaddnet -instancename irqp2f${irq}
        set net irqp2f${irq}
    }
    ihwconnect -netport irqp2f${irq}_outP -net ${net}
}

for {set i 0} {$i <= 28} {incr i} {
    # get interrupt name from list
    set tofind [lindex ${interruptToPLList} ${i}]
    # find interrupt name in main list
    set indM [ lsearch -exact ${spiInterruptList} ${tofind} ] 
    set net "-"
    if { $indM >= 0 } {
        # get SPI number found at the previous element in list 
        set spi [lindex ${spiInterruptList} [expr $indM - 1]]
        set net "${tofind}_spi${spi}"
    }
    addIntPS2PL  ${i} ${net} 
}

#
# Reset connections
#
ihwconnect     -instancename cpu  -netport reset_CPU0 -net reset_A9_CPU0
ihwconnect     -instancename cpu  -netport reset_CPU1 -net reset_A9_CPU1

#
# ZC706 XADC MUX Control
#
ihwaddnetport -instancename extPortXADCMux
ihwaddnet     -instancename xadcmux
ihwconnect    -netport extPortXADCMux -net xadcmux

#
# ddrBus
#
ihwaddbus -instancename ddrBus  -addresswidth 32

# 0x00000000    0x0003ffff      RAM (CPUs and ACP)
ihwaddmemory -instancename DDR0       -type ram
ihwconnect   -instancename DDR0       -bus ddrBus -busslaveport  sp1 -loaddress 0x00000000 -hiaddress 0x0003ffff

# 0x00040000    0x0007ffff      RAM (CPUs and ACP)
ihwaddmemory -instancename DDR1       -type ram
ihwconnect   -instancename DDR1       -bus ddrBus -busslaveport  sp1 -loaddress 0x00040000 -hiaddress 0x0007ffff

# 0x00080000    0x000fffff      RAM (CPUs and ACP and other Masters)
ihwaddmemory -instancename DDR2       -type ram
ihwconnect   -instancename DDR2       -bus ddrBus -busslaveport  sp1 -loaddress 0x00080000 -hiaddress 0x000fffff


#
# ddrSBus (shared with all other masters)
#
ihwaddbus -instancename ddrSBus  -addresswidth 32

# 0x00100000    0x3fffffff      RAM (CPUs and ACP and other Masters)
ihwaddmemory -instancename DDR3       -type ram
ihwconnect   -instancename DDR3       -bus ddrSBus -busslaveport  sp1 -loaddress 0x00100000 -hiaddress 0x3fffffff

#
# Processor Access to DDR
#
ihwaddbridge -instancename brPtoDDR
ihwconnect   -instancename brPtoDDR -busslaveport  sp1 -bus pBus      -loaddress 0x00000000 -hiaddress 0x000fffff
ihwconnect   -instancename brPtoDDR -busmasterport mp1 -bus ddrBus    -loaddress 0x00000000 -hiaddress 0x000fffff
ihwaddbridge -instancename brPtoDDRS
ihwconnect   -instancename brPtoDDRS -busslaveport  sp1 -bus pBus     -loaddress 0x00100000 -hiaddress 0x3fffffff
ihwconnect   -instancename brPtoDDRS -busmasterport mp1 -bus ddrSBus  -loaddress 0x00100000 -hiaddress 0x3fffffff

#
# External access to DDR areas (from PL)
#
ihwaddbusport -instancename extPort
ihwaddbus     -instancename extPortBus -addresswidth 32
ihwconnect    -busport extPort -bus extPortBus

# Map port to DDR
ihwaddbridge  -instancename extPorttoDDRS
ihwconnect    -instancename extPorttoDDRS -busslaveport  sp1 -bus extPortBus -loaddress 0x00100000 -hiaddress 0x3fffffff
ihwconnect    -instancename extPorttoDDRS -busmasterport mp1 -bus ddrSBus    -loaddress 0x00100000 -hiaddress 0x3fffffff

#
# apbBus
#
ihwaddbus -instancename apbBus  -addresswidth 32

# Map port to APB Peripherals
ihwaddbridge  -instancename extPorttoAPB
ihwconnect    -instancename extPorttoAPB -busslaveport  sp1 -bus extPortBus -loaddress 0xe0000000 -hiaddress 0xe0101fff
ihwconnect    -instancename extPorttoAPB -busmasterport mp1 -bus apbBus     -loaddress 0xe0000000 -hiaddress 0xe0101fff

# Map pBus to APB Peripherals
ihwaddbridge  -instancename pBustoAPB
ihwconnect    -instancename pBustoAPB -busslaveport  sp1 -bus pBus    -loaddress 0xe0000000 -hiaddress 0xe0101fff
ihwconnect    -instancename pBustoAPB -busmasterport mp1 -bus apbBus  -loaddress 0xe0000000 -hiaddress 0xe0101fff

#
# ocmBus contains the OCM RAM
#
ihwaddbus -instancename ocmBus  -addresswidth 32

# 0x00000000    0x0003ffff      RAM
ihwaddmemory -instancename ocm -type ram
ihwconnect   -instancename ocm -bus ocmBus -busslaveport  sp1 -loaddress 0x00000000 -hiaddress 0x0003ffff

#
# Access to External Programmable Logic
#
# General Purpose Port #0 to the Programmable Logic
# 0x40000000   0x7fffffff
# General Purpose Port #1 to the Programmable Logic
# 0x80000000   0xbfffffff
ihwaddbridge  -instancename pBustoExtPort
ihwconnect    -instancename pBustoExtPort -busslaveport  sp1 -bus pBus       -loaddress 0x40000000 -hiaddress 0xbfffffff
ihwconnect    -instancename pBustoExtPort -busmasterport mp1 -bus extPortBus -loaddress 0x40000000 -hiaddress 0xbfffffff


#
# I/O Peripherals
#

# 0xe0000000    0xe0000fff      UART
ihwaddperipheral -instancename uart0  -type uart -vendor cadence.ovpworld.org
ihwconnect       -instancename uart0  -bus apbBus -busslaveport  bport1 -loaddress 0xe0000000 -hiaddress 0xe0000fff
ihwsetparameter    -handle     uart0  -name outfile            -value uart0.log -type string
ihwsetparameter    -handle     uart0  -name finishOnDisconnect -value 1         -type boolean
ihwsetparameter    -handle     uart0  -name console            -value 1         -type boolean
ihwsetparameter    -handle     uart0  -name xchars             -value 130       -type uns32
ihwsetparameter    -handle     uart0  -name ychars             -value  30       -type uns32
ihwconnect       -instancename uart0  -netport irq -net uart0_spi59

# 0xe0001000    0xe0001fff      UART
ihwaddperipheral -instancename uart1  -type uart -vendor cadence.ovpworld.org
ihwconnect       -instancename uart1  -bus apbBus -busslaveport  bport1 -loaddress 0xe0001000 -hiaddress 0xe0001fff
ihwsetparameter    -handle     uart1  -name outfile            -value uart1.log -type string
ihwsetparameter    -handle     uart1  -name finishOnDisconnect -value 1         -type boolean
ihwsetparameter    -handle     uart1  -name console            -value 1         -type boolean
ihwsetparameter    -handle     uart1  -name xchars             -value 130       -type uns32
ihwsetparameter    -handle     uart1  -name ychars             -value  30       -type uns32
ihwconnect       -instancename uart1  -netport irq -net uart1_spi82

set size 0x1000
set base 0xe0002000

# 0xe0002000    0xe0002fff     USB0
ihwaddperipheral -instancename usb0 -type zynq_7000-usb -vendor xilinx.ovpworld.org -library peripheral
ihwconnect   -instancename usb0 -bus apbBus -busslaveport bport1 -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
#ihwconnect  -instancename usb0 -netport irq -net usb0_spi53
set base [ expr $base + $size]

# 0xe0003000    0xe0003fff     USB1
ihwaddperipheral -instancename usb1 -type zynq_7000-usb -vendor xilinx.ovpworld.org -library peripheral
ihwconnect   -instancename usb1 -bus apbBus -busslaveport bport1 -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
#ihwconnect  -instancename usb1 -netport irq -net usb1_spi76
set base [ expr $base + $size]

#
# I2C connection (external Port)
#
ihwaddbusport -instancename extPortI2C
ihwaddbus     -instancename i2cBus -addresswidth 16
ihwconnect    -busport extPortI2C -bus i2cBus


# 0xe0004000    0xe0004fff     I2C0
ihwaddperipheral -instancename i2c0 -type zynq_7000-iic -vendor xilinx.ovpworld.org -library peripheral
ihwconnect       -instancename i2c0 -bus apbBus -busslaveport bport1 -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
ihwconnect       -instancename i2c0 -bus i2cBus -busmasterport I2C_Master 
ihwconnect       -instancename i2c0 -netport intOut -net i2c0_spi57
set base [ expr $base + $size]

# 0xe0005000    0xe0005fff     I2C1
ihwaddperipheral -instancename i2c1 -type zynq_7000-iic -vendor xilinx.ovpworld.org -library peripheral
ihwconnect       -instancename i2c1 -bus apbBus -busslaveport bport1 -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
ihwconnect       -instancename i2c1 -netport intOut -net i2c1_spi80
set base [ expr $base + $size]

# 0xe0006000    0xe0006fff     SPI0
ihwaddperipheral -instancename spi0 -type zynq_7000-spi -vendor xilinx.ovpworld.org -library peripheral
ihwconnect       -instancename spi0 -bus apbBus -busslaveport bport1 -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
ihwconnect       -instancename spi0 -netport intOut -net spi0_spi58
set base [ expr $base + $size]

# 0xe0007000    0xe0007fff     SPI1
ihwaddperipheral -instancename spi1 -type zynq_7000-spi -vendor xilinx.ovpworld.org -library peripheral
ihwconnect       -instancename spi1 -bus apbBus -busslaveport bport1 -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
ihwconnect       -instancename spi1 -netport intOut -net spi1_spi81
set base [ expr $base + $size]

# 0xe0008000    0xe0008fff     CAN0
ihwaddperipheral -instancename can0 -type zynq_7000-can -vendor xilinx.ovpworld.org -library peripheral
ihwconnect   -instancename can0 -bus apbBus -busslaveport bport1 -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
iadddocumentation -name Description -text "Peripheral can0 (xilinx.ovpworld.org/peripheral/zynq_7000-can/1.0) is a dummy peripheral that implements register set only"
ihwconnect   -instancename can0 -netport intOut -net can0_spi60
set base [ expr $base + $size]

# 0xe0009000    0xe0009fff     CAN1
ihwaddperipheral -instancename can1 -type zynq_7000-can -vendor xilinx.ovpworld.org -library peripheral
ihwconnect   -instancename can1 -bus apbBus -busslaveport bport1 -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
iadddocumentation -name Description -text "Peripheral can1 (xilinx.ovpworld.org/peripheral/zynq_7000-can/1.0) is a dummy peripheral that implements register set only"
ihwconnect   -instancename can1 -netport intOut -net can1_spi83
set base [ expr $base + $size]

# 0xe000a000    0xe000afff     GPIO
ihwaddperipheral -instancename GPIO -type zynq_7000-gpio -vendor xilinx.ovpworld.org -library peripheral
ihwconnect   -instancename GPIO -bus apbBus -busslaveport bport1 -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
ihwconnect   -instancename GPIO -netport intOut -net gpio_spi52


# Common procedure to add GPIO connection
proc addGPIOConnection {bank} {
    ihwaddnet     -instancename gpio_bank${bank}_out
    ihwconnect    -instancename GPIO -netport gpio_bank${bank}_out -net gpio_bank${bank}_out
    ihwaddnetport -instancename gpio_bank${bank}_outP
    ihwconnect    -netport gpio_bank${bank}_outP -net gpio_bank${bank}_out

    if { $bank == 2 || $bank == 3 } {
        ihwaddnet     -instancename gpio_bank${bank}_oen_out
        ihwconnect    -instancename GPIO -netport gpio_bank${bank}_oen_out -net gpio_bank${bank}_oen_out
        ihwaddnetport -instancename gpio_bank${bank}_oen_outP
        ihwconnect    -netport gpio_bank${bank}_oen_outP -net gpio_bank${bank}_oen_out
    }

    ihwaddnet     -instancename gpio_bank${bank}_in
    ihwconnect    -instancename GPIO -netport gpio_bank${bank}_in  -net gpio_bank${bank}_in
    ihwaddnetport -instancename gpio_bank${bank}_inP
    ihwconnect    -netport gpio_bank${bank}_inP -net gpio_bank${bank}_in
}
# MIO
addGPIOConnection 0
addGPIOConnection 1
# EMIO (PL)
addGPIOConnection 2
addGPIOConnection 3


set base [ expr $base + $size]

# 0xe000b000    0xe000bfff     ETH0
ihwaddperipheral -instancename eth0 -type gem -vendor cadence.ovpworld.org -library peripheral
ihwconnect   -instancename eth0 -bus apbBus -busslaveport bport1 -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
ihwconnect   -instancename eth0 -bus pBus   -busmasterport bport2
ihwconnect   -instancename eth0 -netport irq -net eth0_spi54

set base [ expr $base + $size]

# 0xe000c000    0xe000cfff     ETH1
ihwaddperipheral -instancename eth1 -type gem -vendor cadence.ovpworld.org -library peripheral
ihwconnect   -instancename eth1 -bus apbBus -busslaveport bport1 -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
ihwconnect   -instancename eth1 -bus pBus   -busmasterport bport2
ihwconnect   -instancename eth1 -netport irq -net eth1_spi77
set base [ expr $base + $size]

# 0xe000d000    0xe000dfff     Quad-SPI
ihwaddperipheral -instancename qspi -type zynq_7000-qspi -vendor xilinx.ovpworld.org -library peripheral
ihwconnect   -instancename qspi -bus apbBus -busslaveport bpAPB -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
set base [ expr $base + $size]
ihwconnect   -instancename qspi -bus apbBus -busslaveport bpAXI -loaddress 0xfc000000 -hiaddress 0xfdffffff
ihwconnect   -instancename qspi -netport interrupt -net qspi_spi51
# formal to configure the flash type
ihwaddformalparameter -name flashtype -type string -defaultvalue "micron"
ihwsetparameter -handle    qspi -name flash -value {flashtype} -type string


# 0xe000e000    0xe000efff     Static Memory Controller (SMC)
set dummy "dummySMC"
ihwaddperipheral -instancename ${dummy} -type trap -vendor ovpworld.org -library peripheral
ihwconnect       -instancename ${dummy} -busslaveport bport1 -bus apbBus
ihwsetparameter  -handle       ${dummy} -name portAddress -value 0x[format %x ${base}] -type uns32
ihwsetparameter  -handle       ${dummy} -name portSize    -value ${size} -type uns32
iadddocumentation -name Description -text "Peripheral ${dummy} is a dummy which traps accesses at address 0x[format %x ${base}] size ${size}"
#ihwconnect   -instancename ${dummy} -netport intOut -net smc_spi50
set base [ expr $base + $size]

# 0xe000f000    0xe000ffff     ??
set dummy "dummyUnknown1"
ihwaddperipheral -instancename ${dummy} -type trap -vendor ovpworld.org -library peripheral
ihwconnect       -instancename ${dummy} -busslaveport bport1 -bus apbBus
ihwsetparameter  -handle       ${dummy} -name portAddress -value 0x[format %x ${base}] -type uns32
ihwsetparameter  -handle       ${dummy} -name portSize    -value ${size} -type uns32
iadddocumentation -name Description -text "Peripheral ${dummy} is a dummy which traps accesses at address 0x[format %x ${base}] size ${size}"
set base [ expr $base + $size]


#
# SDIO
#
set base 0xe0100000

# 0xe0100000    0xe0100fff     SDIO0
ihwaddperipheral -instancename sdio0 -type zynq_7000-sdio -vendor xilinx.ovpworld.org -library peripheral
ihwconnect   -instancename sdio0 -bus apbBus -busslaveport bport1 -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
iadddocumentation -name Description -text "Peripheral sdio0 (xilinx.ovpworld.org/peripheral/zynq_7000-sdio/1.0) is a dummy peripheral that implements register set only"
ihwconnect   -instancename sdio0 -netport intOut -net sdio0_spi56
set base [ expr $base + $size]
# 0xe0101000    0xe0101fff     SDIO1
ihwaddperipheral -instancename sdio1 -type zynq_7000-sdio -vendor xilinx.ovpworld.org -library peripheral
ihwconnect   -instancename sdio1 -bus apbBus -busslaveport bport1 -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
iadddocumentation -name Description -text "Peripheral sdio1 (xilinx.ovpworld.org/peripheral/zynq_7000-sdio/1.0) is a dummy peripheral that implements register set only"
ihwconnect   -instancename sdio1 -netport intOut -net sdio1_spi79
set base [ expr $base + $size]

# 0xe0200000    0xe020001f     Trust Zone control registers
set base 0xe0200000
set tzSize 0x0020
ihwaddperipheral -instancename trustzone_security -type zynq_7000-tz_security -vendor xilinx.ovpworld.org -library peripheral
ihwconnect       -instancename trustzone_security -bus pBus -busslaveport bport1 -loaddress ${base} -hiaddress [ expr $base + $tzSize -1 ]
iadddocumentation -name Description -text "Peripheral trustzone_security (xilinx.ovpworld.org/peripheral/zone_security/1.0) is a dummy peripheral that implements register set only"

#
# SMC Memory
#

# 0xe1000000    0xe1ffffff      SMC NAND
# 0xe2000000    0xe2ffffff      SMC SRAM/NOR CS 0
# 0xe3000000    0xe3ffffff      SMC SRAM/NOR CS 0

#
# System-Level Control registers (SLCR)
#

# 0xf8000000    0xf8000bff     System-Level Control registers (SLCR) 4.3 pg 115
ihwaddperipheral -instancename slcr  -type zynq_7000-slcr -vendor xilinx.ovpworld.org
ihwconnect       -instancename slcr  -bus pBus -busslaveport bport1 -loaddress 0xf8000000 -hiaddress 0xf8000bff
ihwconnect       -instancename slcr  -netport A9_RST0 -net reset_A9_CPU0
ihwconnect       -instancename slcr  -netport A9_RST1 -net reset_A9_CPU1
# ports allow OCM/DDR selection and re-mapping
ihwconnect       -instancename slcr  -bus pBus   -busslaveport  spOCMDDR
ihwconnect       -instancename slcr  -bus ocmBus -busmasterport mpOCM
ihwconnect       -instancename slcr  -bus ddrBus -busmasterport mpDDR
# ARM clock deration
ihwaddnet        -instancename ARM0Deration
ihwconnect       -instancename slcr  -netport ARM0Deration -net ARM0Deration
ihwaddnet        -instancename ARM1Deration
ihwconnect       -instancename slcr  -netport ARM1Deration -net ARM1Deration

# configure device id (0x11:7z045, 0x07:7z020)
ihwsetparameter -handle slcr -name deviceid -value 0x11 -type Uns32

# formal to allow configuration by instancing module
ihwaddformalparameter -name psclock -type Uns32
# configure clock
ihwsetparameter -handle slcr -name psclock -value {psclock} -type Uns32
# configure Processor MIPS
ihwsetparameter -handle slcr -name armmips -value {armmips} -type Uns32

#
# Miscellaneous Registers
#
set base 0xf8001000

# 0xf8001000    0xf8000fff     triple Timer Counter0 (TTC)
ihwaddperipheral -instancename ttc0 -type zynq_7000-ttc -vendor xilinx.ovpworld.org -library peripheral
ihwconnect       -instancename ttc0 -bus pBus -busslaveport bport1 -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
ihwconnect       -instancename ttc0 -netport int1 -net ttc0_spi42
ihwconnect       -instancename ttc0 -netport int2 -net ttc0_spi43
ihwconnect       -instancename ttc0 -netport int3 -net ttc0_spi44
set base [ expr $base + $size]

# 0xf8002000    0xf8001fff     triple Timer Counter1 (TTC)
ihwaddperipheral -instancename ttc1 -type zynq_7000-ttc -vendor xilinx.ovpworld.org -library peripheral
ihwconnect       -instancename ttc1 -bus pBus -busslaveport bport1 -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
ihwconnect       -instancename ttc1 -netport int1 -net ttc1_spi69
ihwconnect       -instancename ttc1 -netport int2 -net ttc1_spi70
ihwconnect       -instancename ttc1 -netport int3 -net ttc1_spi71
set base [ expr $base + $size]

# 0xf8003000    0xf8003fff     DMAC secure (DMAC S) (DMAC)
# 0xf8004000    0xf8004fff     DMAC non secure (DMAC NS) (DMAC)
ihwaddperipheral -instancename DMAC -type zynq_7000-dmac -vendor xilinx.ovpworld.org -library peripheral
iadddocumentation -name Description -text "Peripheral DMAC (xilinx.ovpworld.org/peripheral/zynq_7000-dmac) is a dummy peripheral that implements register set only"
ihwconnect   -instancename DMAC -bus pBus -busslaveport bportS  -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
set base [ expr $base + $size]
ihwconnect   -instancename DMAC -bus pBus -busslaveport bportNS -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
ihwconnect   -instancename DMAC -netport inta -net dmaca_spi45
for {set i 0} {$irq <= 7} {incr i} {
    if {$i < 4} { set base 46 } else { set base 72 }
    set spi [ expr $base + $i ]
    ihwconnect   -instancename DMAC -netport int${i} -net dmac${i}_spi${spi}
}
set base [ expr $base + $size]

# 0xf8005000    0xf8005fff     System Watchdog Timer (SWDT)
ihwaddperipheral -instancename swdt -type zynq_7000-swdt -vendor xilinx.ovpworld.org -library peripheral
ihwconnect       -instancename swdt -bus pBus -busslaveport bport1 -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
ihwconnect       -instancename swdt -netport wdo -net swdt_spi41
set base [ expr $base + $size]

# 0xf8006000    0xf8006fff     DDR Memory Controller (DDRC)
ihwaddperipheral -instancename DDRC -type zynq_7000-ddrc -vendor xilinx.ovpworld.org -library peripheral
ihwconnect   -instancename DDRC -bus pBus -busslaveport bport1 -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
iadddocumentation -name Description -text "Peripheral DDRC (xilinx.ovpworld.org/peripheral/zynq_7000-ddrc) is a dummy peripheral that implements register set only"
set base [ expr $base + $size]

# 0xf8007000    0xf8007fff     Device Configuration Interface (DEVCFG)
# define the board type
ihwaddformalparameter -name board -type String
ihwaddperipheral -instancename devcfg  -type zynq_7000-devcfg -vendor xilinx.ovpworld.org
ihwconnect       -instancename devcfg  -bus pBus -busslaveport bport1 -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
iadddocumentation -name Description -text "Peripheral devcfg (xilinx.ovpworld.org/peripheral/zynq_7000-devcfg/1.0) provides XADC access for power monitoring. Connected memory contains the temperature, voltage and current values provided by the XADC"
# configure for the board we are instanced in
ihwsetparameter   -handle devcfg  -name board -value {board} -type String
# Bus connects to the XADC channels
ihwaddbus        -instancename xadcBus -addresswidth 16
ihwconnect       -instancename devcfg  -bus xadcBus -busmasterport xadc
# Memory
ihwaddmemory     -instancename xadcMem -type ram
ihwconnect       -instancename xadcMem -bus xadcBus -busslaveport sp1 -loaddress 0x000 -hiaddress 0x3ff
# XADC Mux select
ihwconnect       -instancename devcfg -netport xadcmux -net xadcmux
set base [ expr $base + $size]

# 0xf8008000    0xf8008fff     AXI HP0 (AFI)
set dummy "dummyAXI_HP0"
ihwaddperipheral -instancename ${dummy} -type trap -vendor ovpworld.org -library peripheral
ihwconnect       -instancename ${dummy} -busslaveport bport1 -bus pBus
ihwsetparameter  -handle       ${dummy} -name portAddress -value 0x[format %x ${base}] -type uns32
ihwsetparameter  -handle       ${dummy} -name portSize    -value ${size} -type uns32
iadddocumentation -name Description -text "Peripheral ${dummy} is a dummy which traps accesses at address 0x[format %x ${base}] size ${size}"
set base [ expr $base + $size]

# 0xf8009000    0xf8009fff     AXI HP1 (AFI)
set dummy "dummyAXI_HP1"
ihwaddperipheral -instancename ${dummy} -type trap -vendor ovpworld.org -library peripheral
ihwconnect       -instancename ${dummy} -busslaveport bport1 -bus pBus
ihwsetparameter  -handle       ${dummy} -name portAddress -value 0x[format %x ${base}] -type uns32
ihwsetparameter  -handle       ${dummy} -name portSize    -value ${size} -type uns32
iadddocumentation -name Description -text "Peripheral ${dummy} is a dummy which traps accesses at address 0x[format %x ${base}] size ${size}"
set base [ expr $base + $size]

# 0xf800a000    0xf800afff     AXI HP2 (AFI)
set dummy "dummyAXI_HP2"
ihwaddperipheral -instancename ${dummy} -type trap -vendor ovpworld.org -library peripheral
ihwconnect       -instancename ${dummy} -busslaveport bport1 -bus pBus
ihwsetparameter  -handle       ${dummy} -name portAddress -value 0x[format %x ${base}] -type uns32
ihwsetparameter  -handle       ${dummy} -name portSize    -value ${size} -type uns32
iadddocumentation -name Description -text "Peripheral ${dummy} is a dummy which traps accesses at address 0x[format %x ${base}] size ${size}"
set base [ expr $base + $size]

# 0xf800b000    0xf800bfff     AXI HP3 (AFI)
set dummy "dummyAXI_HP3"
ihwaddperipheral -instancename ${dummy} -type trap -vendor ovpworld.org -library peripheral
ihwconnect       -instancename ${dummy} -busslaveport bport1 -bus pBus
ihwsetparameter  -handle       ${dummy} -name portAddress -value 0x[format %x ${base}] -type uns32
ihwsetparameter  -handle       ${dummy} -name portSize    -value ${size} -type uns32
iadddocumentation -name Description -text "Peripheral ${dummy} is a dummy which traps accesses at address 0x[format %x ${base}] size ${size}"
set base [ expr $base + $size]

# 0xf800c000    0xf800cfff     On-chip Memory (OCM) Registers
ihwaddperipheral -instancename OCM -type zynq_7000-ocm -vendor xilinx.ovpworld.org -library peripheral
ihwconnect   -instancename OCM -bus pBus -busslaveport bport1 -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
set base [ expr $base + $size]

# 0xf800d000    0xf800dfff     eFuse
set dummy "dummyeFuse"
ihwaddperipheral -instancename ${dummy} -type trap -vendor ovpworld.org -library peripheral
ihwconnect       -instancename ${dummy} -busslaveport bport1 -bus pBus
ihwsetparameter  -handle       ${dummy} -name portAddress -value 0x[format %x ${base}] -type uns32
ihwsetparameter  -handle       ${dummy} -name portSize    -value ${size} -type uns32
iadddocumentation -name Description -text "Peripheral ${dummy} is a dummy which traps accesses at address 0x[format %x ${base}] size ${size}"
set base [ expr $base + $size]

# 0xf800e000    0xf800efff     ??
set dummy "dummyUnknown2"
ihwaddperipheral -instancename ${dummy} -type trap -vendor ovpworld.org -library peripheral
ihwconnect       -instancename ${dummy} -busslaveport bport1 -bus pBus
ihwsetparameter  -handle       ${dummy} -name portAddress -value 0x[format %x ${base}] -type uns32
ihwsetparameter  -handle       ${dummy} -name portSize    -value ${size} -type uns32
iadddocumentation -name Description -text "Peripheral ${dummy} is a dummy which traps accesses at address 0x[format %x ${base}] size ${size}"
set base [ expr $base + $size]

#
# CoreSight debug Control (CTI)
#

# 0xf8800000    0xf889ffff     CoreSight debug Control (CTI)

#   dap           0xF8800000 Debug Access Port ROM Table
#   etb           0xF8801000 Embedded Trace Buffer
#   cti           0xF8802000 Cross Trigger Interface, ETB and TPIU
#   tpiu          0xF8803000 Trace Port Interface Unit
#   funnel        0xF8804000 CoreSight Trace Funnel
#   itm           0xF8805000 Instrumentation Trace Macrocell
#   cti           0xF8809000 Cross Trigger Interface, FTM
#   ftm           0xF880B000 Fabric Trace Macrocell
#   cortexa9_pmu  0xF8891000 Cortex A9 Performance Monitoring Unit, CPU 0
#   cortexa9_pmu  0xF8893000 Cortex A9 Performance Monitoring Unit, CPU 1
#   cti           0xF8898000 Cross Trigger Interface, CPU 0
#   cti           0xF8899000 Cross Trigger Interface, CPU 1
#   ptm           0xF889C000 CoreSight PTM-A9, CPU 0
#   ptm           0xF889D000 CoreSight PTM-A9, CPU 1

#
# CPU Private Bus Registers (registers not defined within the OVP ARM processor model)
#

# 0xf8900000    0xf89fffff     Top level interconnect and Global Programmers View (GPV)
set base 0xf8900000
set tzSize 0x0040
ihwaddperipheral -instancename trustzone_GPVsecurity -type zynq_7000-tz_GPVsecurity -vendor xilinx.ovpworld.org -library peripheral
ihwconnect       -instancename trustzone_GPVsecurity -bus pBus -busslaveport bport1 -loaddress ${base} -hiaddress [ expr $base + $tzSize -1 ]
iadddocumentation -name Description -text "Peripheral trustzone_GPVsecurity (xilinx.ovpworld.org/peripheral/zynq_7000-tz_GPVsecurity/1.0) is a dummy peripheral that implements register set only"

set base 0xf8946000
ihwaddperipheral -instancename GPV_qos301_cpu -type zynq_7000-qos301 -vendor xilinx.ovpworld.org -library peripheral
ihwconnect   -instancename GPV_qos301_cpu -bus pBus -busslaveport bport1 -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
iadddocumentation -name Description -text "Peripheral GPV_qos301_cpu (xilinx.ovpworld.org/peripheral/zynq_7000-qos301/1.0) is a dummy peripheral that implements register set only"

set base 0xf8947000
ihwaddperipheral -instancename GPV_qos301_dmac -type zynq_7000-qos301 -vendor xilinx.ovpworld.org -library peripheral
ihwconnect   -instancename GPV_qos301_dmac -bus pBus -busslaveport bport1 -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
iadddocumentation -name Description -text "Peripheral GPV_qos301_dmac (xilinx.ovpworld.org/peripheral/zynq_7000-qos301/1.0) is a dummy peripheral that implements register set only"

set base 0xf8948000
ihwaddperipheral -instancename GPV_qos301_iou -type zynq_7000-qos301 -vendor xilinx.ovpworld.org -library peripheral
ihwconnect   -instancename GPV_qos301_iou -bus pBus -busslaveport bport1 -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
iadddocumentation -name Description -text "Peripheral GPV_qos301_iou (xilinx.ovpworld.org/peripheral/zynq_7000-qos301/1.0) is a dummy peripheral that implements register set only"

#  CBAR set to base of CPU Model internal register address mappings 0xf8f00000
# 0xf8f00000    0xf8f000fc     SCU Control and Status (CPU Core Model)
# 0xf8f00100    0xf8f001ff     Interrupt Controller CPU (CPU Core Model)
# 0xf8f00200    0xf8f002ff     Global Timer (CPU Core Model)
# 0xf8f00600    0xf8f006ff     Private Timers and Private Watchdog Timers (CPU Core Model)
# 0xf8f01000    0xf8f01fff     Interrupt Controller Distributor (CPU Core Model)
# 0xf8f02000    0xf8f02fff     ARM L2 Cache Controller (PL310)
set base 0xf8f02000
ihwaddperipheral -instancename l2cache  -type L2CachePL310 -vendor arm.ovpworld.org
ihwconnect       -instancename l2cache  -bus pBus -busslaveport bport1 -loaddress ${base} -hiaddress [ expr $base + $size -1 ]
ihwconnect       -instancename l2cache  -netport irq -net l2cache_spi34



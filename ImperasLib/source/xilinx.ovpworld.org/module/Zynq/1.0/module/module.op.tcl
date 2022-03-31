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

set desc "This module implements the Zynq 7000"

set limitations "This module provides the instantiation of a Processing Sub-system (Zynq_PS) module and a Programmable Logic (Zynq_PL) module."

set reference "Zynq-7000 AP SoC Technical Reference Manual UG585 (v1.10) February 23, 2015 (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)"

set license "Open Source Apache 2.0"

# Setup variables for platform info 
set vendor  xilinx.ovpworld.org
set library module
set name    Zynq
set version 1.0

#
# Start new platform creation 
#
ihwnew -name $name -vendor $vendor -library $library -version $version -stoponctrlc -purpose module -releasestatus ovp
iadddocumentation -name Licensing   -text $license
iadddocumentation -name Description -text $desc
iadddocumentation -name Limitations -text $limitations
iadddocumentation -name Reference   -text $reference


#
# Processing Sub_System
#
ihwaddmodule -instancename Zynq_PS -vendor xilinx.ovpworld.org -library module -type Zynq_PS -version 1.0

# formal to allow configuration by instancing module
ihwaddformalparameter -name psclock -type Uns32 -defaultvalue 33
ihwsetparameter -handle Zynq_PS -name psclock -value {psclock} -type Uns32
ihwaddformalparameter -name armmips -type Uns32 -defaultvalue 500
ihwsetparameter -handle Zynq_PS -name armmips -value {armmips} -type Uns32

# need the board info to configure devcfg that includes power info
ihwaddformalparameter -name board -type String
ihwsetparameter -handle Zynq_PS -name board -value {board} -type String

# configure flash type
ihwaddformalparameter -name flashtype -type String
ihwsetparameter -handle Zynq_PS -name flashtype -value {flashtype} -type String

#
# DDR connection (external Port)
#
#ihwaddbusport -instancename extPortDDR
#ihwaddbus     -instancename ddrBus -addresswidth 32
#ihwconnect    -busport extDDRPortDDR -bus ddrBus
#ihwconnect    -instancename Zynq_PS -busport extPortDDR -bus ddrBus

#
# I2C connection (external Port)
#
ihwaddbusport -instancename extPortI2C
ihwaddbus     -instancename i2cBus -addresswidth 16
ihwconnect    -busport extPortI2C -bus i2cBus
ihwconnect    -instancename Zynq_PS -busport extPortI2C -bus i2cBus

#
# ZC706 XADC MUX
#
ihwaddnetport -instancename extPortXADCMux
ihwaddnet     -instancename xadcmux
ihwconnect    -netport extPortXADCMux -net xadcmux
ihwconnect    -instancename Zynq_PS -netport extPortXADCMux -net xadcmux

#
# Programmable Logic (default: Zynq_PL_Default has no behaviour)
#
ihwaddformalparameter  -name plmoduletype   -defaultvalue Zynq_PL_Default     -type string
ihwaddformalparameter  -name plmodulevendor -defaultvalue xilinx.ovpworld.org -type string
ihwaddmodule -instancename Zynq_PL -vendor plmodulevendor -library module -type plmoduletype -version 1.0

#
# PS to PL interconnect
#
ihwaddbus     -instancename icBus -addresswidth 32
ihwconnect    -instancename Zynq_PS -busport extPort -bus icBus
ihwconnect    -instancename Zynq_PL -busport extPort -bus icBus

#
# GPIO
#
ihwaddnet -instancename gpio_bank0_in
ihwaddnet -instancename gpio_bank0_out
ihwaddnet -instancename gpio_bank1_in
ihwaddnet -instancename gpio_bank1_out
ihwaddnet -instancename gpio_bank2_in
ihwaddnet -instancename gpio_bank2_out
ihwaddnet -instancename gpio_bank2_oen_out
ihwaddnet -instancename gpio_bank3_in
ihwaddnet -instancename gpio_bank3_out
ihwaddnet -instancename gpio_bank3_oen_out

# Zync_PS net connections
ihwconnect -instancename Zynq_PS -netport gpio_bank0_outP -net gpio_bank0_out
ihwconnect -instancename Zynq_PS -netport gpio_bank0_inP  -net gpio_bank0_in
ihwconnect -instancename Zynq_PS -netport gpio_bank1_outP -net gpio_bank1_out
ihwconnect -instancename Zynq_PS -netport gpio_bank1_inP  -net gpio_bank1_in
ihwconnect -instancename Zynq_PS -netport gpio_bank2_outP -net gpio_bank2_out
ihwconnect -instancename Zynq_PS -netport gpio_bank2_oen_outP -net gpio_bank2_oen_out
ihwconnect -instancename Zynq_PS -netport gpio_bank2_inP  -net gpio_bank2_in
ihwconnect -instancename Zynq_PS -netport gpio_bank3_outP -net gpio_bank3_out
ihwconnect -instancename Zynq_PS -netport gpio_bank3_oen_outP -net gpio_bank3_oen_out
ihwconnect -instancename Zynq_PS -netport gpio_bank3_inP  -net gpio_bank3_in

# GPIO external connections (banks 0/1)
ihwaddnetport -instancename gpio_bank0_outP
ihwconnect    -netport gpio_bank0_outP -net gpio_bank0_out
ihwaddnetport -instancename gpio_bank1_outP
ihwconnect    -netport gpio_bank1_outP -net gpio_bank1_out
ihwaddnetport -instancename gpio_bank0_inP
ihwconnect    -netport gpio_bank0_inP -net gpio_bank0_in
ihwaddnetport -instancename gpio_bank1_inP
ihwconnect    -netport gpio_bank1_inP -net gpio_bank1_in

# GPIO to PL (banks 2/3)
ihwconnect    -instancename Zynq_PL -netport gpio_bank2_outP -net gpio_bank2_out
ihwconnect    -instancename Zynq_PL -netport gpio_bank2_oen_outP -net gpio_bank2_oen_out
ihwconnect    -instancename Zynq_PL -netport gpio_bank2_inP -net gpio_bank2_in
ihwconnect    -instancename Zynq_PL -netport gpio_bank3_outP -net gpio_bank3_out
ihwconnect    -instancename Zynq_PL -netport gpio_bank3_oen_outP -net gpio_bank3_oen_out
ihwconnect    -instancename Zynq_PL -netport gpio_bank3_inP -net gpio_bank3_in


#
# Interrupts PL to PS
#

# Interrupt connections PL to PS
proc addIntPL2PS {irq} {
    ihwaddnet     -instancename irqf2p${irq}
    ihwconnect    -instancename Zynq_PS -netport irqf2p${irq}_inP  -net irqf2p${irq}
    ihwconnect    -instancename Zynq_PL -netport irqf2p${irq}_outP -net irqf2p${irq}
}
# SPI (0-15)
# IRQ and FIQ interrupts to cpu_CPU0 and cpu_CPU1 (16-19)
for {set irq 0} {$irq <= 19} {incr irq} {
    addIntPL2PS  ${irq}
}

#
# Interrupts PS to PL
#

# Interrupt connections PS to PL
proc addIntPS2PL {irq} {
    ihwaddnet     -instancename irqp2f${irq}
    ihwconnect    -instancename Zynq_PS -netport irqp2f${irq}_outP -net irqp2f${irq}
    ihwconnect    -instancename Zynq_PL -netport irqp2f${irq}_inP  -net irqp2f${irq}
}
for {set irq 0} {$irq <= 28} {incr irq} {
    addIntPS2PL  ${irq}
}

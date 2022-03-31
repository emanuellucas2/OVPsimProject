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
# This file defines the common interconnet signals to a PL module
#

#
# Bus connections
#
ihwaddbusport -instancename extPort
ihwaddbus     -instancename extPortBus -addresswidth 32
ihwconnect    -busport extPort -bus extPortBus

#
# GPIO connections
#

# Common procedure to add GPIO connection
proc addGPIOConnection {bank} {
    ihwaddnet     -instancename gpio_bank${bank}_out
    ihwaddnetport -instancename gpio_bank${bank}_outP
    ihwconnect    -netport gpio_bank${bank}_outP -net gpio_bank${bank}_out

    ihwaddnet     -instancename gpio_bank${bank}_oen_out
    ihwaddnetport -instancename gpio_bank${bank}_oen_outP
    ihwconnect    -netport gpio_bank${bank}_oen_outP -net gpio_bank${bank}_oen_out

    ihwaddnet     -instancename gpio_bank${bank}_in
    ihwaddnetport -instancename gpio_bank${bank}_inP
    ihwconnect    -netport gpio_bank${bank}_inP -net gpio_bank${bank}_in
}
addGPIOConnection 2
addGPIOConnection 3

#
# Interrupt connections
#

# Interrupt connections PL to PS
proc addIntPL2PS {irq} {
    ihwaddnet     -instancename irqf2p${irq}
    ihwaddnetport -instancename irqf2p${irq}_outP
    ihwconnect    -netport      irqf2p${irq}_outP -net irqf2p${irq}
}
# SPI (0-15)
# IRQ and FIQ interrupts to cpu_CPU0 and cpu_CPU1 (16-19)
for {set irq 0} {$irq <= 19} {incr irq} {
    addIntPL2PS  ${irq}
}

# Interrupt connections PS to PL
proc addIntPS2PL {irq} {
    ihwaddnet     -instancename irqp2f${irq}
    ihwaddnetport -instancename irqp2f${irq}_inP
    ihwconnect    -netport      irqp2f${irq}_inP -net irqp2f${irq}
}

for {set irq 0} {$irq <= 28} {incr irq} {
    addIntPS2PL  ${irq}
}

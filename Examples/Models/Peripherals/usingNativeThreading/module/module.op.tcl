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

# This is a simple OVP platform using an OR1K processor to stimulate
# a peripheral model that drives a packetnet interconnect.
#
ihwnew -name peripheralNativeThreadTest -vendor ovpworld.org -library module -version 1.0

# bus
ihwaddbus -instancename bus -addresswidth 32

# net (interrupt)
ihwaddnet -instancename int0

#
# processor
#
ihwaddprocessor -instancename cpu1 \
                -type arm -vendor arm.ovpworld.org \
                -semihostname armNewlib -semihostvendor arm.ovpworld.org \
		-endian little 
# Configure processor
ihwsetparameter -handle cpu1 -name variant -value Cortex-A9UP -type string
# Connect processor to bus
ihwconnect -instancename cpu1 -busmasterport INSTRUCTION -bus bus 
ihwconnect -instancename cpu1 -busmasterport DATA        -bus bus 
# Connect processor to interrupt
ihwconnect -instancename cpu1 -netport fiq -net int0 

#
# memory
#
ihwaddmemory -instancename mem1 -type ram
ihwconnect   -instancename mem1 -busslaveport sp1 -bus bus -loaddress 0x00000000 -hiaddress 0x3fffffff

ihwaddmemory -instancename mem2 -type ram
ihwconnect   -instancename mem2 -busslaveport sp1 -bus bus -loaddress 0xc0000000 -hiaddress 0xffffffff

#
# peripherals
#
set percount  2
set spbase    0x80000000
set spstride  0x1000
set spsize    0x013f
if { [ info exists env(PERIPHERALS) ]} { 
    set percount $env(PERIPHERALS)
    puts "MODULE: Set Peripheral Count to $percount"
}
if { [ info exists env(DATASORTSPBASE) ]} {
    set spbase $env(DATASORTSPBASE)
    puts "MODULE: Set Peripheral Slave Port Base to 0x[format %08x $spbase]"
}
if { [ info exists env(DATASORTSPSIZE) ]} {
    set spstride $env(DATASORTSPSIZE)
    puts "MODULE: Set Peripheral Slave Port Stride to 0x[format %04x $spstride]"
}

ihwaddformalparameter -name registeronly -type bool
ihwaddformalparameter -name quantumdelay -type bool

proc addPeripheral {id} {
    global spbase
    global spsize
    global spstride
    set abase [expr $spbase + ($spstride * $id)]
    set atop  [expr $abase  +  $spsize]
    # instance peripheral
    ihwaddperipheral -instancename sort${id} -modelfile peripheral/pse/pse.pse
    # connect slave and master ports to bus
    ihwconnect -instancename sort${id} -busslaveport  DATASORTSP -bus bus -loaddress $abase -hiaddress $atop
    ihwconnect -instancename sort${id} -busmasterport DATASORTMP -bus bus
    # connect interrupt
    ihwconnect -instancename sort${id} -netport INT -net int0
    # configuration
    ihwsetparameter -handle sort${id} -name registeronly -expression registeronly -type bool
    ihwsetparameter -handle sort${id} -name quantumdelay -expression quantumdelay -type bool
}

# Add the peripherals
for {set i 0} {$i < $percount} {incr i} {
    addPeripheral $i
}
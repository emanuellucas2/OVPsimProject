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

ihwnew \
  -name    virtio  \
  -vendor  riscv.ovpworld.org  \
  -library module  \
  -version 1.0 \
  -stoponctrlc \
  -purpose module -releasestatus ovp

iadddocumentation -name Licensing    -text "Open Source Apache 2.0"
iadddocumentation -name Description  -text "Virtio System Platform to boot BusyBear-Linux Kernel"
iadddocumentation -name Reference    -text "Virtio System Platform"
iadddocumentation -name Limitations  -text "Sufficient functionality to boot BusyBear-Linux Kernel using the Virtio platform"

############################ Memory Map ###########################
# clint@2000000                reg = <0x0 0x02000000 0x0 0x00010000>;
# interrupt-controller@c000000 reg = <0x0 0x0c000000 0x0 0x04000000>;
# uart@10000000                reg = <0x0 0x10000000 0x0 0x00000100>;
# virtio_mmio@10001000         reg = <0x0 0x10001000 0x0 0x00001000>;
# virtio_mmio@10002000         reg = <0x0 0x10002000 0x0 0x00001000>;
# virtio_mmio@10003000         reg = <0x0 0x10003000 0x0 0x00001000>;
# virtio_mmio@10004000         reg = <0x0 0x10004000 0x0 0x00001000>;
# virtio_mmio@10005000         reg = <0x0 0x10005000 0x0 0x00001000>;
# virtio_mmio@10006000         reg = <0x0 0x10006000 0x0 0x00001000>;
# virtio_mmio@10007000         reg = <0x0 0x10007000 0x0 0x00001000>;
# virtio_mmio@10008000         reg = <0x0 0x10008000 0x0 0x00001000>;
# memory@80000000              reg = <0x0 0x80000000 0x0 0x08000000>;
############################ Memory Map ###########################


############################ processor ############################

ihwaddprocessor  \
  -instancename hart0  \
  -type         riscv \
  -vendor       riscv.ovpworld.org \
  -library      processor \
  -version      1.0 \
  -mips         50 \
  -simulateexceptions

ihwsetparameter -handle hart0 -name variant        -type enum   -value RVB64I
ihwsetparameter -handle hart0 -name add_Extensions -type string -value MAFDCSU
ihwsetparameter -handle hart0 -name reset_address  -type Uns64 -value 0x1000
# when using CLINT the mtime/mtimecmp registers are external so disable
ihwsetparameter -handle hart0 -name time_undefined -type bool -value True

ihwaddbus \
  -instancename bus0  -addresswidth 48

ihwconnect \
  -instancename hart0  -busmasterport INSTRUCTION -bus bus0

ihwconnect \
  -instancename hart0  -busmasterport DATA        -bus bus0

ihwaddnet  -instancename irqT0
ihwaddnet  -instancename irqT1
ihwconnect -net irqT0 -instancename hart0  -netport MExternalInterrupt
ihwconnect -net irqT1 -instancename hart0  -netport SExternalInterrupt

ihwaddnet  -instancename irqS1
ihwaddnet  -instancename irqS2
ihwaddnet  -instancename irqS10

############################## memory #############################

set reset_mem_start 0x1000
set reset_mem_size  0x3000
ihwaddmemory -instancename bootram -type ram
ihwconnect \
  -instancename bootram -busslaveport sp1 -bus bus0 \
  -loaddress ${reset_mem_start} -hiaddress [expr ${reset_mem_start} + ${reset_mem_size} - 1]
  
set mem_start 0x80000000
set mem_size  0x08000000
ihwaddmemory -instancename main -type ram
ihwconnect \
  -instancename main -busslaveport sp1 -bus bus0 \
  -loaddress ${mem_start} -hiaddress [expr ${mem_start} + ${mem_size} - 1]

############################## Virtio #############################

# Virtio Block Device
ihwaddperipheral -instancename VBD0 -type VirtioBlkMMIO -vendor ovpworld.org 
ihwconnect       -instancename VBD0 -bus bus0 -busmasterport dma    -loaddress 0 -hiaddress 0xffffffff
ihwconnect       -instancename VBD0 -bus bus0 -busslaveport  bport1 -loaddress 0x10001000 -hiaddress 0x100011ff
ihwconnect       -net irqS1 -instancename VBD0 -netport Interrupt

# Add Virtio net device at unused address and interrupt 
ihwaddperipheral -instancename VND0 -type VirtioNetMMIO -vendor ovpworld.org 
ihwconnect       -instancename VND0 -bus bus0 -busmasterport dma    -loaddress 0 -hiaddress 0xffffffff
ihwconnect       -instancename VND0 -bus bus0 -busslaveport  bport1 -loaddress 0x10002000 -hiaddress 0x100021ff
ihwconnect       -net irqS2 -instancename VND0 -netport Interrupt

# Add the Dummy MMIO devices
set mmio_list "
    virtio_mmio3 0x10003000 0x10003FFF
    virtio_mmio4 0x10004000 0x10004FFF
    virtio_mmio5 0x10005000 0x10005FFF
    virtio_mmio6 0x10006000 0x10006FFF
    virtio_mmio7 0x10007000 0x10007FFF
    virtio_mmio8 0x10008000 0x10008FFF
"
foreach {name low high} ${mmio_list} {
    set size [ expr $high -$low + 1 ]
    ihwaddperipheral -instancename $name -type trap -vendor ovpworld.org
    ihwconnect       -instancename $name -bus bus0  -busslaveport bport1
    ihwsetparameter  -handle       $name -name portAddress -value $low  -type uns32
    ihwsetparameter  -handle       $name -name portSize    -value $size -type uns32
    # enables callbacks that report accesses
    ihwsetparameter  -handle       $name -name cbEnable    -value True  -type boolean
}


########################### peripherals ###########################

#
# clint
#
ihwaddperipheral \
  -instancename clint -vendor riscv.ovpworld.org -library peripheral -type CLINT -version 1.0
ihwconnect \
  -instancename clint -bus bus0 -busslaveport port0 -loaddress 0x02000000 -hiaddress 0x0200BFFF
ihwsetparameter -name num_harts -handle clint -type Uns32  -value 1
ihwsetparameter -name clockMHz  -handle clint -type double -value 25.0
ihwaddnet  -instancename MTimerInterrupt0
ihwconnect -instancename clint -netport MTimerInterrupt0 -net MTimerInterrupt0
ihwconnect -instancename hart0 -netport MTimerInterrupt  -net MTimerInterrupt0
ihwaddnet  -instancename MSWInterrupt0
ihwconnect -instancename clint -netport MSWInterrupt0 -net MSWInterrupt0
ihwconnect -instancename hart0 -netport MSWInterrupt  -net MSWInterrupt0

#
# plic
#
ihwaddperipheral \
  -instancename plic -vendor riscv.ovpworld.org -library peripheral -type PLIC -version 1.0
ihwconnect \
  -instancename plic -bus bus0 -busslaveport port0 -loaddress 0x0C000000 -hiaddress 0x0FFFFFFF
ihwsetparameter -name num_sources -handle plic -type Uns32 -value 10
ihwsetparameter -name num_targets -handle plic -type Uns32 -value 2
ihwconnect -net irqT0  -instancename plic -netport irqT0
ihwconnect -net irqT1  -instancename plic -netport irqT1
ihwconnect -net irqS1  -instancename plic -netport irqS1
ihwconnect -net irqS2  -instancename plic -netport irqS2
ihwconnect -net irqS10 -instancename plic -netport irqS10

#
# uart0
#
ihwaddperipheral -instancename uartTTY0 -vendor national.ovpworld.org -library peripheral -version 1.0 -type 16550
ihwconnect -instancename uartTTY0 -bus bus0 -busslaveport bport1 -loaddress 0x10000000 -hiaddress 0x10000007
ihwconnect -instancename uartTTY0 -net irqS10 -netport intOut


#
# OVPworld Linux BootLoader
#
ihwaddperipheral -instancename smartLoader  -type SmartLoaderRV64Linux -vendor riscv.ovpworld.org -version 1.0
ihwconnect       -instancename smartLoader  -bus bus0 -busmasterport mport -loaddress 0 -hiaddress 0xffffffff
ihwsetparameter  -handle       smartLoader  -name bootaddr   -value ${mem_start}       -type address
ihwsetparameter  -handle       smartLoader  -name slbootaddr -value ${reset_mem_start} -type address
# Pass memory info to device tree
ihwsetparameter  -handle       smartLoader  -name membase -value ${mem_start} -type address
ihwsetparameter  -handle       smartLoader  -name memsize -value ${mem_size}  -type address

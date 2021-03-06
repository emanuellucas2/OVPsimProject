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
    -name    FU540  \
    -vendor  sifive.ovpworld.org  \
    -library module  \
    -version 1.0 \
    -stoponctrlc \
    -purpose module -releasestatus ovp

iadddocumentation -name Licensing    -text "Open Source Apache 2.0"

iadddocumentation -name Description  -text "SiFive FU540-C000 SoC module."
iadddocumentation -name Description  -text "On start up or reset, the reset code at 0x1004 will jump to a jump table entry indexed by the MSEL register at address 0x1000 (default initial MSEL value is 0xf which will cause a jump to address 0x10000). Use the msel peripheral's MSEL parameter to change the initial value of this register."
iadddocumentation -name Description  -text "To run a bare metal application use the --program command line option to specify an elf file to be loaded. It must be linked to use addresses corresponding to the implemented memory regions. The --program option will override the initial pc with the ELF file's start address."
iadddocumentation -name Description  -text "To facilitate booting Linux an OVP SmartLoader psuedo-peripheral has been included that provides the functionality of the ZSBL/FSBL. The SmartLoader's dtb parameter should be used to specify the device tree blob file to load, and the bbl elf file should be loaded using the --objfilenoentry command line option."

iadddocumentation -name Reference    -text "SiFive Freedom U540-C000 Manual FU540-C000-v1.0.pdf (https://www.sifive.com/documentation/chips/freedom-u540-c000-manual)"
iadddocumentation -name Limitations  -text "Caches and the Cache Controller are not modeled."
iadddocumentation -name Limitations  -text "The Instruction Tightly Integrated Memory (ITIM) is implemented simply as RAM. Deallocation by writing to the byte immediately following the memory is a NOP."
iadddocumentation -name Limitations  -text "The L2 Loosely Integrated Memory (L2-LIM) is implemented simply as RAM. It is always available, since the Cache Controller is not modeled."
iadddocumentation -name Limitations  -text "The L2 Scratchpad memory is not modeled."
iadddocumentation -name Limitations  -text "The Platform DMA Engine (PDMA) is not modeled."
iadddocumentation -name Limitations  -text "The Pulse Width Modulator (PWM) is not modeled."
iadddocumentation -name Limitations  -text "The Inter-Integrated Circuit (I2C) Master Interface is not modeled."
iadddocumentation -name Limitations  -text "The Serial Peripheral Interfaces (SPI) are not modeled. Instead a Virtio Block MMIO device has been added at reserved address 0x1f000000, using interrupt 54."
iadddocumentation -name Limitations  -text "The General Purpose Input/Output Controller (GPIO) is modeled with register stubs only."
iadddocumentation -name Limitations  -text "The One-Time Programmable Memory Interface (OTP) is not modeled."
iadddocumentation -name Limitations  -text "DDR controller is modeled with register stubs only. DDR memory is modeled as RAM."
iadddocumentation -name Limitations  -text "The Debug Interface is not modeled."

############################ processor ############################

# Name for E51
set e51_name E51

# Name and number of harts for U54 cluster
set u54_name U54
set u54_numharts 4

# Total number of harts connected to the clint
set clint_numharts [expr { $u54_numharts + 1}]

# Number of global interrupts supported
set num_globalints 53

# physical address space is 38 bits (Note: U54 virtual address space is 39 bits)
ihwaddbus  -instancename bus0 -addresswidth 38

# Reset address in the Mode Select reset module
set reset_address 0x1004 

# Counter for consecutively assigning irtqT signals from plic
set irq 0 

proc instance_riscv { name variant id numharts } {

    global reset_address
    
    ihwaddprocessor  \
      -instancename ${name}  \
      -type         riscv \
      -vendor       sifive.ovpworld.org \
      -library      processor \
      -version      1.0 \
      -mips         1000 \
      -simulateexceptions
      
    ihwconnect -instancename ${name} -busmasterport INSTRUCTION -bus bus0
    ihwconnect -instancename ${name} -busmasterport DATA        -bus bus0
    
    ihwsetparameter -handle ${name} -name mhartid       -type Uns64 -value ${id} 
    ihwsetparameter -handle ${name} -name local_int_num -type Uns32 -value 48
    ihwsetparameter -handle ${name} -name reset_address -type Uns64 -value $reset_address
    
    if { $numharts != 0 } {
        ihwsetparameter -handle ${name} -name numHarts -type Uns32 -value ${numharts} 
    }
    
    ihwsetparameter -handle ${name} -name variant -type enum -value ${variant}
    
}

# Connect local Timer and SWInterrupt ports 
proc connect_local_int { name id prefix } {
    ihwconnect -instancename ${name} -netport ${prefix}MTimerInterrupt -net MTimerInterrupt${id}
    ihwconnect -instancename ${name} -netport ${prefix}MSWInterrupt    -net MSWInterrupt${id}
}

# Connect external interrupt, incrementing irqT number
proc connect_external_int { name prefix } {
    global irq
    ihwaddnet  -instancename irqT${irq}
    ihwconnect -net irqT${irq} -instancename $name -netport ${prefix}ExternalInterrupt
    incr irq
}

# E51 core (hart0)
instance_riscv       $e51_name E51 0 0
connect_local_int    $e51_name 0 hart0_
connect_external_int $e51_name   hart0_M

# U54 cores (hart1:n)
instance_riscv ${u54_name} U54 1 ${u54_numharts}
for {set id 1} {$id <= $u54_numharts} {incr id} {
    connect_local_int    $u54_name $id hart${id}_ 
    connect_external_int $u54_name     hart${id}_M
    connect_external_int $u54_name     hart${id}_S    
}

############################## memory #############################
  
# ZSBL Mask ROM (32 Kib) 
# Note: Defined as ram to allow SmartLoader peripheral to write boot code here
ihwaddmemory  -instancename maskROM -type ram
ihwconnect    -instancename maskROM -busslaveport sp1 -bus bus0 \
  -loaddress 0x10000 -hiaddress 0x17FFF

# DDR memory (8GB)
set ddr_start  0x80000000
set ddr_size   0x40000000
ihwaddmemory  -instancename ddr1 -type ram
ihwconnect \
 -instancename ddr1 -busslaveport sp1 -bus bus0 \
 -loaddress ${ddr_start} -hiaddress [expr ${ddr_start} + ${ddr_size} - 1]
 
# Place ram at address 0x0 to model Safe Zero Address area implemented by the Debug module
# (bug in bbl causes error if this is not present)
ihwaddmemory  -instancename safe0addr -type ram
ihwconnect    -instancename safe0addr -busslaveport sp1 -bus bus0 -loaddress 0 -hiaddress 0xff
 
############# ITIM/DTIM Tightly Integrated memories ###############

# Note: ITIM address ranges intentionally include one extra byte at the
#       end to allow writes to deallocate the memory, although these are
#       a NOP in the simulation

# E51 DTIM (8 Kib) 
ihwaddmemory  -instancename hart0DTIM -type ram
ihwconnect    -instancename hart0DTIM -busslaveport sp1 -bus bus0 \
  -loaddress 0x01000000 -hiaddress 0x01001fff
  
# E51 Hart 0 ITIM (8 Kib) 
ihwaddmemory  -instancename hart0ITIM -type ram
ihwconnect    -instancename hart0ITIM -busslaveport sp1 -bus bus0 \
  -loaddress 0x01800000 -hiaddress 0x01802000
  
# U54 Hart 1 ITIM (28 Kib) 
ihwaddmemory  -instancename hart1ITIM -type ram
ihwconnect    -instancename hart1ITIM -busslaveport sp1 -bus bus0 \
  -loaddress 0x01808000 -hiaddress 0x0180F000
  
# U54 Hart 2 ITIM (28 Kib) 
ihwaddmemory  -instancename hart2ITIM -type ram
ihwconnect    -instancename hart2ITIM -busslaveport sp1 -bus bus0 \
  -loaddress 0x01810000 -hiaddress 0x01817000
  
# U54 Hart 3 ITIM (28 Kib) 
ihwaddmemory  -instancename hart3ITIM -type ram
ihwconnect    -instancename hart3ITIM -busslaveport sp1 -bus bus0 \
  -loaddress 0x01818000 -hiaddress 0x0181F000
  
# U54 Hart 4 ITIM (28 Kib) 
ihwaddmemory  -instancename hart4ITIM -type ram
ihwconnect    -instancename hart4ITIM -busslaveport sp1 -bus bus0 \
  -loaddress 0x01820000 -hiaddress 0x01827000

############# L2 LIM  Loosely Integrated memory ###############

# L2 LTIM (32 Mib) 
ihwaddmemory  -instancename l2LIM -type ram
ihwconnect    -instancename l2LIM -busslaveport sp1 -bus bus0 \
  -loaddress 0x08000000 -hiaddress 0x09FFFFFF
  
######################## peripherals ###########################

# Mode Select reset module
ihwaddperipheral -instancename msel -vendor sifive.ovpworld.org -library peripheral -type MSEL -version 1.0
ihwconnect -instancename msel -bus bus0 -busslaveport bport1 -loaddress 0x1000 -hiaddress 0x1FFF
  
# CLINT
ihwaddperipheral -instancename clint -vendor riscv.ovpworld.org -library peripheral -type CLINT -version 1.0
ihwconnect -instancename clint -bus bus0 -busslaveport port0 -loaddress 0x02000000 -hiaddress 0x0200BFFF
ihwsetparameter -name num_harts -handle clint -type Uns32  -value $clint_numharts
ihwsetparameter -name clockMHz  -handle clint -type double -value 1.0
  
# Create nets for the CLINT output ports 
for {set id 0} {$id < $clint_numharts} {incr id} {
    ihwaddnet  -instancename MTimerInterrupt${id}
    ihwconnect -instancename clint -netport MTimerInterrupt${id} -net MTimerInterrupt${id}
    
    ihwaddnet  -instancename MSWInterrupt${id}
    ihwconnect -instancename clint -netport MSWInterrupt${id}    -net MSWInterrupt${id}
}

# PLIC
ihwaddperipheral -instancename plic -vendor sifive.ovpworld.org -library peripheral -type PLIC -version 1.0
ihwsetparameter -name num_targets -handle plic -type Uns32 -value 9
ihwsetparameter -name num_sources -handle plic -type Uns32 -value $num_globalints
ihwconnect -instancename plic -bus bus0 -busslaveport port0 -loaddress 0x0C000000 -hiaddress 0x0C3FFFFF

# Connect irq lines (Supervisor and user mode)
for {set i 0} {$i < 9} {incr i} {
    ihwconnect -net irqT${i}  -instancename plic -netport irqT${i}
}

# Connect global interrupts
for {set i 1} {$i <=  $num_globalints} {incr i} {
    set name gi${i}
    ihwaddnet     -instancename $name 
    ihwconnect    -instancename plic -netport irqS${i} -net $name
    ihwaddnetport -instancename $name
    ihwconnect    -netport $name -net $name
}

# prci 
ihwaddperipheral -instancename prci -vendor sifive.ovpworld.org -library peripheral -version 1.0 -type PRCI
ihwconnect -instancename prci -bus bus0 -busslaveport bport1 -loaddress 0x10000000 -hiaddress 0x10000fff

# uart0 
ihwaddperipheral -instancename uart0 -vendor sifive.ovpworld.org -library peripheral -version 1.0 -type UART
ihwconnect       -instancename uart0 -bus bus0 -busslaveport bport1 -loaddress 0x10010000 -hiaddress 0x1001001b
ihwconnect       -instancename uart0 -net gi4 -netport intOut
# Configure UART reference clock frequency to post-ZSBL value of 500MHZ 
ihwsetparameter  -handle uart0  -name refClkFreq   -value 500000000 -type uns32

# uart1 
ihwaddperipheral -instancename uart1 -vendor sifive.ovpworld.org -library peripheral -version 1.0 -type UART
ihwconnect       -instancename uart1 -bus bus0 -busslaveport bport1 -loaddress 0x10011000 -hiaddress 0x1001101b
ihwconnect       -instancename uart1 -net gi5 -netport intOut
# Configure UART reference clock frequency to post-ZSBL value of 500MHZ 
ihwsetparameter  -handle uart1  -name refClkFreq   -value 500000000 -type uns32

# GPIO (register stubs only)
ihwaddperipheral -instancename gpio -vendor sifive.ovpworld.org -library peripheral -version 1.0 -type gpio  
ihwconnect       -instancename gpio -busslaveport bport1 -bus bus0 -loaddress 0x10060000 -hiaddress 0x10060fff

# Ethernet MAC 
ihwaddperipheral -instancename emac -vendor cadence.ovpworld.org -library peripheral -version 1.0 -type gem
ihwconnect       -instancename emac -bus bus0 -busmasterport bport2
ihwconnect       -instancename emac -bus bus0 -busslaveport  bport1 -loaddress 0x10090000 -hiaddress 0x10090fff
ihwconnect       -instancename emac -net gi53 -netport irq

# Ethernet Management (register stubs only)
ihwaddperipheral -instancename emgmt -vendor ovpworld.org -library peripheral -version 1.0 -type trap  
ihwconnect       -instancename emgmt -busslaveport bport1 -bus bus0
ihwsetparameter  -handle       emgmt -name portAddress -value 0x100a0000 -type uns32
ihwsetparameter  -handle       emgmt -name portSize    -value 0x1000     -type uns32

# DDR Control (register stubs only)
ihwaddperipheral -instancename ddrctl -vendor sifive.ovpworld.org -library peripheral -version 1.0 -type DDRCTL
ihwconnect       -instancename ddrctl -bus bus0 -busslaveport CONTROL -loaddress 0x100b0000 -hiaddress 0x100b3fff
ihwconnect       -instancename ddrctl -bus bus0 -busslaveport BLOCKER -loaddress 0x100b8000 -hiaddress 0x100b8007

# Virtio Block Device (Not in FU540 - uses SPI2 interrupt)
ihwaddperipheral -instancename vbd0 -type VirtioBlkMMIO -vendor ovpworld.org 
ihwconnect       -instancename vbd0 -bus bus0 -busmasterport dma 
ihwconnect       -instancename vbd0 -bus bus0 -busslaveport  bport1 -loaddress 0x1f000000 -hiaddress 0x1f0001ff
ihwconnect       -net gi6 -instancename vbd0 -netport Interrupt

# OVPworld Linux BootLoader
# Implements equivalent of the ZSBL/FSBL (Zeroth/First Stage Boot Loaders)
ihwaddperipheral -instancename smartLoader  -type SmartLoaderRV64Linux -vendor riscv.ovpworld.org -version 1.0
ihwconnect       -instancename smartLoader  -bus bus0 -busmasterport mport
# Pass memory info to device tree
ihwsetparameter  -handle       smartLoader  -name membase -value ${ddr_start} -type address
ihwsetparameter  -handle       smartLoader  -name memsize -value ${ddr_size}  -type address



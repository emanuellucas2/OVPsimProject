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
    -name    S51CC  \
    -vendor  sifive.ovpworld.org  \
    -library module  \
    -version 1.0 \
    -stoponctrlc \
    -purpose module -releasestatus ovp

    
iadddocumentation -name Licensing    -text "Open Source Apache 2.0"

iadddocumentation -name Description  -text "SiFive S51 (aka E51) Core Complex module."
iadddocumentation -name Description  -text "To run a bare metal application use the --program command line option to specify an elf file to be loaded. It must be linked to use addresses corresponding to the implemented memory regions. The --program option will override the initial pc with the ELF file's start address."

iadddocumentation -name Reference    -text "SiFive S51 Core Complex Manual v19.02 (Downloaded from: https://www.sifive.com/documentation)"

iadddocumentation -name Limitations  -text "Caches are not modeled."
iadddocumentation -name Limitations  -text "The Instruction Tightly Integrated Memory (ITIM) is implemented simply as RAM. Deallocation by writing to the byte immediately following the memory is a NOP."
iadddocumentation -name Limitations  -text "The Safe Zero Address area at address 0x0 is implemented as normal RAM, so is not guaranteed to always read as 0."

# Number of global interrupts supported
set num_globalints 127

# Number of PLIC/CLINT targets supported
set clint_numharts   1

# Number of local interrupts supported
set num_localints   16

############################ processor ############################


# physical address space is 40 bits
ihwaddbus -instancename bus0 -addresswidth 40

ihwaddprocessor  \
  -instancename S51  \
  -type         riscv \
  -vendor       sifive.ovpworld.org \
  -library      processor \
  -version      1.0 \
  -mips         1000 \
  -simulateexceptions
  
ihwconnect -instancename S51 -busmasterport INSTRUCTION -bus bus0
ihwconnect -instancename S51 -busmasterport DATA        -bus bus0

ihwsetparameter -handle S51 -name variant -type enum -value S51
ihwsetparameter -handle S51 -name local_int_num -type uns32 -value $num_localints

# Connect local Timer and SWInterrupt ports 
ihwconnect -instancename S51 -netport hart0_MTimerInterrupt    -net MTimerInterrupt0
ihwconnect -instancename S51 -netport hart0_MSWInterrupt       -net MSWInterrupt0
ihwconnect -instancename S51 -netport hart0_MExternalInterrupt -net MExternalInterrupt0 

# Create nets for the Local Interrupt ports 
for {set id 0} {$id < $num_localints} {incr id} {
    ihwaddnet  -instancename LocalInterrupt${id}
    ihwconnect -net          LocalInterrupt${id} -instancename S51 -netport hart0_LocalInterrupt${id} 
}

# connect reset netport
ihwaddnet  -instancename resetNet
ihwconnect -net          resetNet -instancename S51 -netport hart0_reset


############################## memory #############################
 
# Place ram at address 0x0 to model Safe Zero Address area implemented by the Debug module
ihwaddmemory  -instancename safe0addr -type ram
ihwconnect    -instancename safe0addr -busslaveport sp1 -bus bus0 \
              -loaddress 0 -hiaddress 0x7
  
# Debug RAM (64 bytes) 
ihwaddmemory  -instancename debugRAM -type ram
ihwconnect    -instancename debugRAM -busslaveport sp1 -bus bus0 \
              -loaddress 0x300 -hiaddress 0x3FF
  
# Debug ROM (2KB) 
ihwaddmemory  -instancename debugROM -type rom
ihwconnect    -instancename debugROM -busslaveport sp1 -bus bus0 \
              -loaddress 0x800 -hiaddress 0xFFF
 
############# ITIM/DTIM Tightly Integrated memories ###############

# Note: ITIM address range intentionally includes one extra byte at the
#       end to allow writes to deallocate the memory, although these are
#       a NOP in the simulation
  
# E51 Hart 0 ITIM (8 Kib) 
# (model one byte of memory past the end that is used to deallocate ITIM)
ihwaddmemory  -instancename hart0ITIM -type ram
ihwconnect    -instancename hart0ITIM -busslaveport sp1 -bus bus0 \
              -loaddress 0x08000000 -hiaddress 0x08002000

# E51 DTIM (64 Kib) 
ihwaddmemory  -instancename hart0DTIM -type ram
ihwconnect    -instancename hart0DTIM -busslaveport sp1 -bus bus0 \
              -loaddress 0x80000000 -hiaddress 0x8000ffff
  
######################## CLINT ###########################
  
ihwaddperipheral -instancename clint -vendor riscv.ovpworld.org -library peripheral -type CLINT -version 1.0
ihwconnect       -instancename clint -bus bus0 -busslaveport port0 -loaddress 0x02000000 -hiaddress 0x0200BFFF

# Create nets for the CLINT output ports 
for {set id 0} {$id < $clint_numharts} {incr id} {
    ihwaddnet  -instancename MTimerInterrupt${id}
    ihwconnect -net          MTimerInterrupt${id} -instancename clint -netport MTimerInterrupt${id} 
    
    ihwaddnet  -instancename MSWInterrupt${id}
    ihwconnect -net          MSWInterrupt${id} -instancename clint -netport MSWInterrupt${id}   
}
  
######################## PLIC ###########################

ihwaddperipheral -instancename plic -vendor sifive.ovpworld.org -library peripheral -type PLIC -version 1.0
ihwconnect       -instancename plic -busslaveport port0  -bus bus0 -loaddress 0x0C000000 -hiaddress 0x0C3FFFFF
ihwsetparameter  -handle       plic -name num_targets -type Uns32 -value $clint_numharts
ihwsetparameter  -handle       plic -name num_sources -type Uns32 -value $num_globalints

# Connect targets
for {set i 0} {$i < $clint_numharts} {incr i} {
    ihwaddnet  -instancename MExternalInterrupt${i}
    ihwconnect -net          MExternalInterrupt${i}  -instancename plic -netport irqT${i}
}

# Connect global interrupt ports
for {set i 1} {$i <=  $num_globalints} {incr i} {
    set name gi${i}
    ihwaddnet  -instancename $name 
    ihwconnect -net          $name -instancename plic -netport irqS${i}
}

######################## external connections ###########################

# Connect module's global interrupt net ports
for {set i 1} {$i <=  $num_globalints} {incr i} {
    set name gi${i}
    ihwaddnetport -instancename $name
    ihwconnect    -netport      $name -net $name
}

# Connect module's local interrupt net ports
for {set i 0} {$i <  $num_localints} {incr i} {
    set name li${i}
    ihwaddnetport -instancename $name
    ihwconnect    -netport      $name -net LocalInterrupt${i}
}

# Connect module's resetPort net port to resetNet
ihwaddnetport -instancename resetPort
ihwconnect    -netport      resetPort -net resetNet

# Connect module's systemPort bus port to bus0
ihwaddbusport -instancename systemPort
ihwconnect    -busport      systemPort -bus bus0

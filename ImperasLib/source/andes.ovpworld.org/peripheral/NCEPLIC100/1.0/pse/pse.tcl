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

set vendor  andes.ovpworld.org
set library peripheral
set name    NCEPLIC100
set version 1.0

#
# PLIC
# Maximum 1023 external interrupt sources
#            = priority register
#            = interrupt pending (bits 2^^32) 32x32
# Maximum 16 hart contexts
#            = enables
#            = threshold
#            = claim 
#
# Sources are 1 - 1023
# Targets are 0 - 15
#

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version \
                    -constructor constructor -releasestatus ovp -netportuserfunction nextNetPortUser

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

iadddocumentation -name Description -text "PLIC Interrupt Controller"
iadddocumentation -name Description -text "Base riscv.ovpworld.org PLIC model plus these Andes extension features:"
iadddocumentation -name Description -text " - Software-programmable interrupt generation (writable pending registers)"
iadddocumentation -name Description -text " - Configurable interrupt trigger types"
iadddocumentation -name Description -text " - Preemptive priority interrupts"
iadddocumentation -name Description -text " - Vectored Interrupts"

iadddocumentation -name Description -text "If vectored interrupts are to be used then additional connections between the plic and processor are required. For an interrupt target port t<x>_eip connected to one of the M/S/UExternalInterrupt ports of a processor, the corresponding ports must be connected as follows:"
iadddocumentation -name Description -text " - The PLIC output port t<x>_eiid must be connected to the M/S/UExternalInterruptID processor port"
iadddocumentation -name Description -text " - The PLIC output port t<x>_eiack must be connected to the M/S/UExternalInterruptACK processor port"

iadddocumentation -name Limitations -text "The ASYNC_INT configuration option is not configurable since the difference between asynch/synch behavior is not modeled by the simulator"

iadddocumentation -name Reference   -text "Various AndesCore Processor Data Sheets, e.g. AndesCore AX45MP Data Sheet V1.1 (DS185-11)"
iadddocumentation -name Reference   -text "AndeStar V5 Platform-Level Interrupt Controller Specification - UM166-13"

imodeladdformal   -name num_sources -type Uns32    -min 1    -max 1023  -defaultvalue 63
iadddocumentation -name num_sources -text "Number of Input Interrupt Sources"

imodeladdformal   -name num_targets -type Uns32    -min 1    -max 16 -defaultvalue 1
iadddocumentation -name num_targets -text "Number of Output Interrupt Targets"

imodeladdformal   -name num_priorities -type Uns32 -min 1    -max 255  -defaultvalue 15
iadddocumentation -name num_priorities -text "Number of Priority levels"

imodeladdformal   -name priority_base -type Uns32  -defaultvalue 0x0
iadddocumentation -name priority_base -text "Base Address offset for Priority Registers"

imodeladdformal   -name pending_base -type Uns32   -defaultvalue 0x1000
iadddocumentation -name pending_base -text "Base Address offset for Pending Registers"

imodeladdformal   -name enable_base -type Uns32    -defaultvalue 0x2000
iadddocumentation -name enable_base -text "Base Address offset for Enable Registers"

imodeladdformal   -name enable_stride -type Uns32 -defaultvalue 0x80
iadddocumentation -name enable_stride -text "Stride size for Enable Register Block"

imodeladdformal   -name context_base -type Uns32  -defaultvalue 0x200000
iadddocumentation -name context_base -text "Base Address offset for Context Registers, Threshold and Claim/Complete"

imodeladdformal   -name context_stride -type Uns32 -defaultvalue 0x1000
iadddocumentation -name context_stride -text "Stride size for Context Register Block"

imodeladdnetport -name reset -type input -updatefunction resetCB
iadddocumentation -name Description -text "Reset signal"


# Interrupt Signal Block source : 1 -> n (Only define irqS1 in igen)
imodeladdnetport -name irqS1 -type input -updatefunction irqUpdate -updatefunctionargument 1

# Interrupt Signal Block target : 0 -> (n-1) (Only define irqT0 in igen)
imodeladdnetport -name irqT0 -type output

set window 0x00400000

imodeladdbusslaveport -name port0 -size ${window}

imodeladdaddressblock -name reg -port port0 -size ${window} -offset 0x0 -width 32
imodeladdlocalmemory  -name regMem -addressblock port0/reg -size ${window} -nbyte \
                      -writefunction reservedWR -readfunction reservedRD
#
# Add Andes PLIC extension-specific parameters
#
imodeladdformal   -name andes_version -type Uns32 -defaultvalue 0 -max 0xffff
iadddocumentation -name andes_version -text "Andes PLIC design version (value for VersionMaxPriority.VERSION field)"

imodeladdformal   -name vector_plic_support -type Bool -defaultvalue 1
iadddocumentation -name vector_plic_support -text "Andes Vectored PLIC support - adds t<x>_eiid and t<x>_eack ports when enabled"

for {set num 0} {$num < 32} {incr num} {
    imodeladdformal   -name trigger_type${num} -type Uns32 -defaultvalue 0
    iadddocumentation -name trigger_type${num} -text "Trigger type register ${num} value"
}

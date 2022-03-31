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

set vendor  sifive.ovpworld.org
set library peripheral
set name    PLIC
set version 1.0

#
# PLIC
# Maximum 511 external interrupt sources
#            = priority register
#            = interrupt pending (bits 2^^32) 32x32
# Maximum 15872 hart contexts
#            = enables
#            = threshold
#            = claim 
#
# Sources are 1 - 511
# Targets are 0 - 511
#

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version \
                    -constructor constructor -releasestatus ovp -netportuserfunction nextNetPortUser

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

iadddocumentation -name Description -text "SiFive PLIC Interrupt Controller"
iadddocumentation -name Description -text "Use parameters to configure specific implementation."

iadddocumentation -name Limitations -text "None"

iadddocumentation -name Reference   -text "Various SiFive Core Complex manuals, e.g. SiFive E31 Core Complex Manual 31G2.01.00 (https://sifive.cdn.prismic.io/sifive/c29f9c69-5254-4f9a-9e18-24ea73f34e81_e31_core_complex_manual_21G2.pdf)"

imodeladdformal   -name num_sources -type Uns32    -min 1    -max 511  -defaultvalue 1
iadddocumentation -name num_sources -text "Number of Input Interrupt Sources"

imodeladdformal   -name num_targets -type Uns32    -min 1    -max 512 -defaultvalue 1
iadddocumentation -name num_targets -text "Number of Output Interrupt Targets, Hart/Context"

imodeladdformal   -name num_priorities -type Uns32 -min 1    -max 7  -defaultvalue 7
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
iadddocumentation -name context_base -text "Base Address offset for Context Registers, Threshold/Claim"

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


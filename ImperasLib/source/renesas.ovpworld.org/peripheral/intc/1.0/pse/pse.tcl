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

set vendor  renesas.ovpworld.org
set library peripheral
set name    intc
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version -constructor constructor

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "Renesas INTC Interrupt Controller"
iadddocumentation -name Limitations -text "Register View Model Only"
iadddocumentation -name Reference   -text "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010"

set intrange 117
set nmirange 64

#
# Signal outputs to CPU
#
foreach output {RESET NMI0 NMI1 NMI2 INTP} {
	imodeladdnetport -name ${output} -type output
}

#
# Signal inputs from CPU
#
foreach input {INTACK MIRETI IRESET} {
    imodeladdnetport -name ${input} -type input -updatefunction P_${input}
}

#
# Signal inputs from External & Internal
# An array of NMI and INT signals pass the value as an argument
#
for {set i 0} {$i < ${nmirange}} {incr i} {
    set name [format "NMI_%02d" ${i}]
    imodeladdnetport -name ${name} -type input -updatefunction P_NMI -updatefunctionargument ${i}
}

#
# Slave port
#
imodeladdbusslaveport -name INTCP0 -size 252

#
# Registers
#
imodeladdaddressblock -name reg0 -port INTCP0 -size  16 -offset  0 -width 16
imodeladdaddressblock -name reg1 -port INTCP0 -size 236 -offset 16 -width 8

#
# Interrupt Mask Control Registers
#
for {set i 0} {$i < ${intrange}} {incr i 16} {
    # The 16 bit register index address
    set reg16 [expr $i / 16]
    
    # The byte offset into the memory block
    set offset [expr $i / 8]
    
    # instance the register, callback and reset value
    imodeladdmmregister -addressblock INTCP0/reg0 -name IMR${reg16} \
        -width 16 -offset ${offset} -access rw \
        -writefunction writeIMR -readfunction readIMR

    if {$reg16 == 7} {
        imodeladdreset -mmregister INTCP0/reg0/IMR${reg16} -name IRESET -value 0x001f
    } else {
        imodeladdreset -mmregister INTCP0/reg0/IMR${reg16} -name IRESET -value 0xffff
    }
}

#
# Interrupt Control Registers
#
for {set i 0} {$i < ${intrange}} {incr i} {
    set name [format "INT_%02d" ${i}]

    imodeladdnetport -name ${name} -type input -updatefunction P_INT -updatefunctionargument ${i}
    set offset [expr $i * 2]
    
    set name [format "IC%03d" ${i}]
    imodeladdmmregister -addressblock INTCP0/reg1 -name ${name} \
        -width 8 -offset $offset -access rw \
        -writefunction writeIC -readfunction readIC
    imodeladdreset -mmregister INTCP0/reg1/${name} -name IRESET -value 0x47

    imodeladdfield -mmregister INTCP0/reg1/${name} -name IF -bitoffset 7 -width 1
    imodeladdfield -mmregister INTCP0/reg1/${name} -name MK -bitoffset 6 -width 1
    imodeladdfield -mmregister INTCP0/reg1/${name} -name PR -bitoffset 0 -width 3
}

#
# In Service Priority Register
#
imodeladdmmregister -addressblock INTCP0/reg1 -name ISPR -width 8 -offset 234 -access r
for {set i 0} {$i < 8} {incr i} {
    imodeladdfield -mmregister INTCP0/reg1/ISPR -name ISPR${i} -bitoffset ${i} -width 1
}

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


set vendor  intel.ovpworld.org
set library peripheral
set name    8259A
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version -constructor constructor -releasestatus ovp

iadddocumentation -name Licensing -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Description  \
    -text "Intel 8259A Programmable Interrupt Controller (PIT)."

iadddocumentation  \
    -name Limitations  \
    -text "This model has sufficient functionality to allow a Linux Kernel to Boot on the MIPS:MALTA platform."

iadddocumentation  \
    -name Reference \
    -text "Intel 8259A Datasheet. MIPS Malta Platform Reference Guide."

imodeladdbusmasterport -name cascade -addresswidth 3
imodeladdbusslaveport  -name io -size 2 -mustbeconnected
imodeladdbusslaveport  -name PCIackS -size 1

#
# This is bogus and needs throwing away
#
imodeladdbusslaveport -name elcr -size 1 -mustbeconnected

for {set i 0} {$i<=7} {incr i} {
    imodeladdnetport -name ir${i} -type input
}

imodeladdnetport -name cas -type inout
imodeladdnetport -name intp -type output -mustbeconnected

imodeladdformal -name spen -type string
iadddocumentation  \
    -name Description  \
    -text "Configure the PIC as a \"master\" or \"slave\""

#
# Define 2 read/writable addresses
#
imodeladdaddressblock -port io -name reg -width 8 -size 2 -offset 0
imodeladdmmregister -addressblock io/reg -name io0 -width 8 -offset 0 -access rw -writefunction CB_iow0 -readfunction CB_ior0
imodeladdmmregister -addressblock io/reg -name io1 -width 8 -offset 1 -access rw -writefunction CB_iow1 -readfunction CB_ior1

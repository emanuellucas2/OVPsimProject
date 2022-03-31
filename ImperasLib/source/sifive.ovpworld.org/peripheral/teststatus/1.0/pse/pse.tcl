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
set name    teststatus
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor 


iadddocumentation -name Description -text "SiFive coreip-s51-arty Test Status Memory region."
iadddocumentation -name Description -text "Provides the test status region on the platform defintion that is used to terminate the execution of a test."

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

iadddocumentation -name Limitations -text "None."

iadddocumentation -name Reference   -text "SiFive Freedom E SDK coreip-s51-arty Board Support Package details."

set PORT    bport1
set AB      mem
set AB_SIZE 0x1000
set width   32

imodeladdbusslaveport  -name $PORT -mustbeconnected -size $AB_SIZE
imodeladdaddressblock  -name $AB -port $PORT -size $AB_SIZE -offset 0 -width ${width}
imodeladdlocalmemory   -name status -addressblock $PORT/$AB -size $AB_SIZE -offset 0 -readfunction readStatus -writefunction writeStatus


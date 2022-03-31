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

set vendor  ovpworld.org
set library peripheral
set name    PER
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor \
    -nbyteregisters

iadddocumentation  \
    -name Description  \
    -text "Test Peripheral."

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

set PORT    bport1
set AB      REG
set AB_SIZE 0x100

imodeladdbusslaveport  -name $PORT -mustbeconnected -size $AB_SIZE
imodeladdaddressblock  -name $AB -port $PORT -size $AB_SIZE -offset 0 -width 32

imodeladdlocalmemory -name buffer0 -addressblock $PORT/$AB -size 60 -offset 0 \
                     -writefunction regNoDefinitionWrite -readfunction regNoDefinitionRead

imodeladdmmregister \
    -addressblock  $PORT/$AB \
    -name          CONTROL \
    -offset        0 \
    -access        rw \
    -readfunction  rCONTROL \
    -writefunction wCONTROL
    
imodeladdreset -mmregister $PORT/$AB/CONTROL -name resetNet -value 0

 

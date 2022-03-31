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
# NAME : ledRegisters


# Setup variables for model info
set vendor  ovpworld.org
set library peripheral
set name    switchRegister
set version 1.0

#puts "Creating Tuner Register Block model xml"

imodelnewperipheral  \
    -name ${name} \
    -library ${library} \
    -vendor ${vendor} \
    -version ${version} \
    -constructor config \
    -releasestatus ovp        \
    -visibility    visible

iadddocumentation  -name Description  \
                   -text "Simple test peripheral providing a register that contains the values from switch inputs."
iadddocumentation  -name Licensing  \
                   -text "Open Source Apache 2.0"
iadddocumentation  -name Limitations  -text "None"
iadddocumentation  -name Reference    -text "This is not based upon a real device"

set regWidth 8
set portBytes 8

imodeladdbusslaveport -name busPort -mustbeconnected -size $portBytes

imodeladdaddressblock -name A -port busPort -size $portBytes -offset 0 -width $regWidth

set registers { switch_data  0x00  rw  0 readSwitch 0
}

foreach {rname roffset raccess reset readFunc writeFunc} $registers {
    #puts "create $rname $roffset $raccess $readFunc $writeFunc"
    switch -glob "$readFunc $writeFunc" {
        "0 0"   { imodeladdmmregister -addressblock busPort/A -name $rname -width $regWidth -offset $roffset -access $raccess }
        "* 0"   { imodeladdmmregister -addressblock busPort/A -name $rname -width $regWidth -offset $roffset -access $raccess -readfunction $readFunc                           }
        "0 *"   { imodeladdmmregister -addressblock busPort/A -name $rname -width $regWidth -offset $roffset -access $raccess                         -writefunction $writeFunc }
        "* *"   { imodeladdmmregister -addressblock busPort/A -name $rname -width $regWidth -offset $roffset -access $raccess -readfunction $readFunc -writefunction $writeFunc }
    }
    imodeladdreset -mmregister busPort/A/$rname -name reset -value $reset
}

set defaultSWITCHES 4
imodeladdformal   -name availableSwitches -type uns32  -min 0 -defaultvalue ${defaultSWITCHES} -max 8
iadddocumentation -name Description -text "How many switches to display (default ${defaultSWITCHES})"

# Visualization
imodeladdformalmacro -name BHM_HTTP_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS

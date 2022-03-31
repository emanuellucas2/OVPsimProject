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
set name    temperatureSensor
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
                   -text "Simple test peripheral to illustrate the way in which test data can be used, in this case to display a temperature value."
iadddocumentation  -name Description  \
                   -text "A single read-only register provides a temperature value in a format in which bit 31 when set indicates a negative temperature and the value represents temperature x100."
iadddocumentation  -name Licensing  \
                   -text "Open Source Apache 2.0"
iadddocumentation  -name Limitations  -text "None"
iadddocumentation  -name Reference    -text "This is not based upon a real device"

set regWidth  32
set portBytes  4

imodeladdbusslaveport -name busPort -mustbeconnected -size $portBytes

imodeladdaddressblock -name A -port busPort -size $portBytes -offset 0 -width $regWidth
set addBlock "busPort/A"

set registers {
    data  0x00  r  0 readData - "Temperature value data register" {sBit 31 1 r data 0 31 r}
}

foreach { name roffset raccess reset readFn writeFn desc bits } $registers {
    set rname ${name}

    if { $readFn != "-" } {
        set r "-readfunction $readFn"
    } elseif { $raccess == "rw" || $raccess == "r" } {
        set r "-readfunction defaultRegRdCB"
    } else {
        set r ""
    }
    if { $writeFn != "-" } {
        set w "-writefunction $writeFn"
    } elseif { $raccess == "rw" || $raccess == "w" } {
        set w "-writefunction defaultRegWrCB"
    } else {
        set w ""
    }

    set cmd "imodeladdmmregister -name $rname -addressblock $addBlock -offset $roffset -access $raccess $r $w"

    eval $cmd
    if { $desc != 0 } {
        iadddocumentation -name Description -text $desc -handle "$addBlock/$rname"
    }

    if { $bits != "-" } {
        foreach { n o w a } $bits {
            imodeladdfield -mmregister "$addBlock/$rname" -bitoffset $o -name $n -width $w -access $a
        }
    }

    if { $reset != "-" } {
        imodeladdreset -mmregister "$addBlock/$rname" -name reset -value $reset
    }
}

imodeladdnetport -name reset -type input
iadddocumentation -name Description -text "Reset signal"

set defaultInitTemp 30
imodeladdformal   -name inittemp -type double -min -40 -max 80 -defaultvalue $defaultInitTemp
iadddocumentation -name Description -text "used to set the initial temperature reading (default $defaultInitTemp)"

set defaultMaxTemp 60
imodeladdformal   -name maxtemp -type double -min 40 -max 100 -defaultvalue $defaultMaxTemp
iadddocumentation -name Description -text "used to set the maximum temperature reached when using rate increase (default $defaultMaxTemp)"

set defaultRateChange 1
imodeladdformal   -name ratechange -type double -min -10 -max 10 -defaultvalue $defaultRateChange
iadddocumentation -name Description -text "The temperature will change at a rate of degree Centigrade per second according to this parameter (default $defaultRateChange)"

imodeladdformal   -name datafile -type string
iadddocumentation -name Description -text "The temperature change over time can be defined by a set of values in a file."
iadddocumentation -name Description -text "The file format contains a simulation time and a temperature on each line in readable ascii format e.g. 10.1 27.45 indicates at time 10.1 seconds set temperature to 27.45 oC."

# Visualization
imodeladdformalmacro -name BHM_HTTP_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS

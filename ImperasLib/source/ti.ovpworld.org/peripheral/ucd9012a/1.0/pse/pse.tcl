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


set vendor  ti.ovpworld.org
set library peripheral
set name    ucd9012a
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor  \
    -extensionfile model

iadddocumentation  \
    -name Description  \
    -text "Texas Instruments UCD9248 peripheral"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "This model was created to satisfy the requirement of the European SafePower Project"
iadddocumentation  \
    -name Limitations  \
    -text "This model implements a basic interface allowing temperature monitor values on the SafePower projects utilization of zc702 boards."

iadddocumentation -name Reference -text "Device information from http://www.ti.com/lit/ds/symlink/ucd9012a.pdf with PMBUS Command Information from http://www.ti.com/lit/ug/sluu337/sluu337.pdf"

#
# Registers
#
set port     "iic"
set portsize  1
set portwidth 8
imodeladdbusslaveport  -name ${port} -size ${portsize} -mustbeconnected

# Control/Status
set abrsize ${portsize}
set abr     "reg"
imodeladdaddressblock  -name ${abr} -port ${port} -size ${abrsize} -offset 0 -width ${portwidth}

imodeladdmmregister -addressblock ${port}/${abr} -name reg -width ${portwidth} -offset  0 -access rw -writefunction writeI2C -readfunction readI2C


# Add initialisation file
imodeladdformal -name config -type string
iadddocumentation -name Description -text "The configuration file defining default values and Voltage Monitor names"

# include common formals
source $env(IMPERAS_HOME)/ImperasLib/source/pmbus.ovpworld.org/modelSupport/pmbus/1.0/pse/pmbus.pse.tcl

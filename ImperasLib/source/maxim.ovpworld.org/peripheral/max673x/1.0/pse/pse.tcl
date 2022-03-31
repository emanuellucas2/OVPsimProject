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

set vendor  maxim.ovpworld.org
set library peripheral
set name    max673x
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor 

iadddocumentation  \
    -name Description  \
    -text "Maxim Watchdog Timer"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "This model implements a watchdog period, it does not implement initial reset."

iadddocumentation -name Reference -text "MAX6730-MAX6735 uP Supervisory Circuit with Independent Watchdog Output"

imodeladdnetport  -name wdi -type input -updatefunction wdReset
iadddocumentation -name Description  -text "Watchdog input signal"
imodeladdnetport  -name wdo -type output
iadddocumentation -name Description  -text "Watchdog output signal"

imodeladdformal   -name TimeoutPeriod -type double -defaultvalue 140 -min 1.1 -max 2240
iadddocumentation -name Description   -text "Watchdog Timeout Period (milliSeconds)"

imodeladdformal   -name InitialPeriod -type double -defaultvalue 35 -min 35 -max 55
iadddocumentation -name Description   -text "Initial Watchdog Timeout Period (Seconds)"

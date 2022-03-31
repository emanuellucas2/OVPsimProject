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
set name    artyIO
set version 1.0

imodelnewperipheral -imagefile pse.pse \
    -vendor  $vendor \
    -library $library \
    -name    $name \
    -version $version \
    -constructor constructor \
    -destructor destructor

iadddocumentation  \
    -name Description  \
    -text "SiFive coreip-s51-arty IO"

iadddocumentation  \
    -name Description  \
    -text "Visualization of LED, Switch and Button connectivity."

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "This model implements only the SIFive ARTY Platform Switches and LEDs."

iadddocumentation -name Reference    -text "SiFive Freedom E SDK coreip-s51-arty Board Support Package details."


# Simulation artifact (LED, Switch and Button connections from/to visualisation)
for {set i 0} {$i < 4} {incr i} {
  imodeladdnetport -type output -name SW${i}
}
for {set i 0} {$i < 4} {incr i} {
  imodeladdnetport -type output -name BTN${i}
}
imodeladdnetport -type input -name LD0red   -updatefunction ledCB -updatefunctionargument 0
imodeladdnetport -type input -name LD0green -updatefunction ledCB -updatefunctionargument 1
imodeladdnetport -type input -name LD0blue  -updatefunction ledCB -updatefunctionargument 2

imodeladdnetport -name reset  -type input  -updatefunction resetCB

#
# Formal attributes (visualization)
#
imodeladdformalmacro -name BHM_HTTP_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS

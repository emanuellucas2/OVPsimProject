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
set name    clkgen
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version -constructor constructor

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "Renesas Clock Generator"
iadddocumentation -name Limitations -text "Register View Model Only"
iadddocumentation -name Reference   -text "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010"

#
# Output Signals
#
# imodeladdnetport -name ${output} -type output

#
# Input Signals
#
# imodeladdnetport -name ${input} -type input -updatefunction ${inputCB}

#
# Slave port
#
imodeladdbusslaveport -name CLKGENP0 -size 1
imodeladdbusslaveport -name CLKGENP1 -size 1

#
# Registers
#
imodeladdaddressblock -name reg0 -port CLKGENP0 -size 1 -offset  0 -width 8
imodeladdmmregister -addressblock CLKGENP0/reg0 -name CANCKSEL -width 8 -offset 0 -access rw -writefunction writeCANCKSEL -writemask 0x01
imodeladdreset -mmregister CLKGENP0/reg0/CANCKSEL -name IRESET -value 0x00
imodeladdfield -mmregister CLKGENP0/reg0/CANCKSEL -name CANCK0 -bitoffset 0 -width 1

imodeladdaddressblock -name reg0 -port CLKGENP1 -size 1 -offset  0 -width 8
imodeladdmmregister -addressblock CLKGENP1/reg0 -name CLM -width 8 -offset 0 -access rw -writefunction writeCLM -writemask 0x03
imodeladdreset -mmregister CLKGENP1/reg0/CLM -name IRESET -value 0x00
imodeladdfield -mmregister CLKGENP1/reg0/CLM -name CLME -bitoffset 0 -width 1
imodeladdfield -mmregister CLKGENP1/reg0/CLM -name CLMD -bitoffset 1 -width 1

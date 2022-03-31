#
# Copyright (c) 2011-2016 Posedge Software, Inc., www.posedgesoft.com
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


set vendor  freescale.ovpworld.org
set library peripheral
set name    KinetisDMAMUX
set version 1.0
set desc "Model of the DMAMUX peripheral used on the Freescale Kinetis platform"
set limitations "Provides the base behaviour for the OVP Freescale Kinetis platforms"

set range 0x1000

imodelnewperipheral           \
    -imagefile   pse.pse      \
    -name        $name        \
    -vendor      $vendor      \
    -library     $library     \
    -version     $version     \
    -constructor constructor  \
    -releasestatus ovp

iadddocumentation -name Description -text $desc
iadddocumentation -name Limitations -text $limitations
iadddocumentation -name Reference -text "www.freescale.com/Kinetis"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab     -size 0x10 -port bport1 -width 8

imodeladdmmregister -name CHCFG%u -width 8 -access rw -writefunction dmamuxWrite -loarray 0 -hiarray 15
  imodeladdreset  -name Reset -value 0
  imodeladdfield  -name ENBL   -bitoffset 7  -width 1
  imodeladdfield  -name SOURCE -bitoffset 0  -width 6
  imodeladdfield  -name TRIG   -bitoffset 6  -width 1   

#
# Net Ports
#
imodeladdnetport -name Reset       -type input
imodeladdnetport -name eDMARequest -type output
imodeladdnetport -name dmaSrc%u    -type input -updatefunction dmaSrcRequest -updatefunctionargument _index -loarray 0 -hiarray 63
imodeladdnetport -name trg%u       -type input -updatefunction dmaTrgRequest -updatefunctionargument _index -loarray 1 -hiarray 4
   
#
# Formals
#
imodeladdformal -name startDMAChannel -type uns32
iadddocumentation -name Description -text "Starting channel number, 0, 16, 32.. (default 0)"

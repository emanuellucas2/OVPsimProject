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


set vendor  andes.ovpworld.org
set library peripheral
set name    NCEPLMT100
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version -constructor constructor

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "NCEPLMT100 Platform-Level Machine Timer"
iadddocumentation -name Limitations -text "A max of 31 timers, rather then the hardware max of 32 is supported by the model. This has not been changed in order to preserve backward compatability of the model's port size, but may be changed locally if needed."
iadddocumentation -name Reference   -text "AndeStar_V5_Timer_UM167_v1.1.pdf 2018-03-07"

set port  bport1
set block ab
set size  0x100
set width 64

imodeladdbusslaveport  -name ${port} -mustbeconnected -size ${size} -defaultfunctions
imodeladdaddressblock  -name ${block} -port ${port} -size ${size} -offset 0 -width ${width}

imodeladdformal   -name clockMHz -type double -defaultvalue 1.0
iadddocumentation -name clockMHz -text "Clock rate used in timer calculations (in MHz)"

imodeladdformal  -name numharts -type uns32 -defaultvalue 4 -min 1 -max 31
iadddocumentation -name Description -text "Number of harts supported (1-31)"

imodeladdnetport -name reset -type input -updatefunction resetCB
iadddocumentation -name Description -text "Reset signal"

imodeladdmmregister -addressblock ${port}/${block} -name mtime  \
                    -width ${width} -offset 0 -access rw \
                    -readfunction rdMTIME -writefunction wrMTIME -viewfunction viewMTIME
iadddocumentation -name Description -text "Constant frequency real-time counter"

imodeladdreset -mmregister ${port}/${block}/mtime -name reset
# 64-bit resets must be performed on a field (dummy in this case)
imodeladdfield -mmregister ${port}/${block}/mtime -name d \
               -bitoffset 0 -width ${width} -reset 0x0LL

imodeladdmmregister -loarray 0 -hiarray 30 \
                    -addressblock ${port}/${block} -name mtimecmp%u  \
                    -width ${width} -offset 8 -access rw \
                    -readfunction rdMTIMECMP -writefunction wrMTIMECMP -userdata _index
iadddocumentation -name Description -text "Compare Register MTIMECMP"

imodeladdreset -mmregister ${port}/${block}/mtimecmp%u -name reset
# 64-bit resets must be performed on a field (dummy in this case)
imodeladdfield -mmregister ${port}/${block}/mtimecmp%u -name d \
               -bitoffset 0 -width ${width} -reset 0xFFFFFFFFFFFFFFFFLL

imodeladdnetport -name intOut_%u -type output -loarray 0 -hiarray 30
iadddocumentation -name Description -text "Interupt Outputs"


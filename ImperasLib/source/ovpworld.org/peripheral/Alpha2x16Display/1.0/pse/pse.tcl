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
# NAME : Alpha2x16Display

imodelnewperipheral  \
    -name Alpha2x16Display  \
    -vendor ovpworld.org  \
    -library peripheral  \
    -version 1.0  \
    -constructor userStart  \
    -releasestatus ovp        \
    -visibility    visible

iadddocumentation  \
                -name Description  \
                -text "This is a simple test peripheral creating a 2x16 alphanumeric display."

iadddocumentation  \
  -name Licensing  \
  -text "Open Source Apache 2.0"

iadddocumentation  \
                -name Limitations  \
                -text "This is not representing a real device and provides simple operations as an example."

iadddocumentation  \
		-name Reference  \
		-text "This is not based upon a real device"

imodeladdbusslaveport -name busPort -mustbeconnected -size 4

imodeladdaddressblock -name A -port busPort -size 4 -offset 0 -width 8

imodeladdmmregister -addressblock busPort/A -name control -width 8 -offset 0 -access rw -writefunction controlWrite
imodeladdreset -mmregister busPort/A/control -name resetNet -value 0

imodeladdmmregister -addressblock busPort/A -name address -width 8 -offset 1 -access rw
imodeladdreset -mmregister busPort/A/address -name resetNet -value 0

imodeladdmmregister -addressblock busPort/A -name status  -width 8 -offset 2 -access rw -writefunction statusWriteError
imodeladdreset -mmregister busPort/A/status -name resetNet -value 0

imodeladdmmregister -addressblock busPort/A -name data    -width 8 -offset 3 -access rw -writefunction dataWrite    -readfunction dataRead

# bit fields
# Control register bits
imodeladdfield -mmregister busPort/A/control -name invert -bitoffset 3  -width 1
imodeladdfield -mmregister busPort/A/control -name set    -bitoffset 2  -width 1
imodeladdfield -mmregister busPort/A/control -name clear  -bitoffset 1  -width 1
imodeladdfield -mmregister busPort/A/control -name enable -bitoffset 0  -width 1

# Status register bits
imodeladdfield -mmregister busPort/A/status  -name enable -bitoffset 1  -width 1
imodeladdfield -mmregister busPort/A/status  -name busy   -bitoffset 0  -width 1

imodeladdnetport -name interrupt -type output

#
# Formal attributes
#
imodeladdformalmacro -name BHM_HTTP_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS

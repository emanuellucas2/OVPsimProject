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
set name    lcd_7segment
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor

iadddocumentation  \
    -name Description  \
    -text "Simple 7 segment LCD"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

imodeladdbusslaveport -name bport -mustbeconnected -size 0x4
imodeladdaddressblock -name reg -port bport -size 0x4 -offset 0 -width 32

imodeladdmmregister -addressblock bport/reg -name lcd -width 32 \
    -offset 0 -access w -writefunction Write7Seg

#
# Formal attributes
#
imodeladdformalmacro -name BHM_HTTP_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS

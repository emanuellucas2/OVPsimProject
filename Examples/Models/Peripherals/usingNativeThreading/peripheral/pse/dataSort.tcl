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


imodelnewperipheral  \
    -name        dataSort \
    -vendor      ovpworld.org  \
    -library     peripheral \
    -version     1.0 \
    -constructor constructor \
    -destructor  destructor  \
    -extensionfile ../model/model

iadddocumentation -name Description -text "DATASORT peripheral model"
    
# Master read / write port
imodeladdbusmasterport -name "DATASORTMP" -addresswidth 32 -mustbeconnected

# Slave port
imodeladdbusslaveport -name DATASORTSP  -size 0x140 -mustbeconnected
iadddocumentation     -name Description -text "DATASORT Registers Slave Port"

# Address block for 8 bit registers
imodeladdaddressblock -name ab8 -width 8  -offset 0 -size 0x40

# 8 bit register
imodeladdmmregister -name start  -offset 0x00 -access rw -readfunction regRdStart -writefunction regWrStart

# Address block for 32 bit registers. CH0
imodeladdaddressblock -name ab32ch0  -width 32  -offset 0x100 -size 0x20

# 32 bit registers
imodeladdmmregister -name srcAddr  -offset 0x0 -access rw -readfunction regRdSrcAddr  -writefunction regWrSrcAddr
imodeladdmmregister -name dataSize -offset 0x4 -access rw -readfunction regRdDataSize -writefunction regWrDataSize

# Interrupt line
imodeladdnetport -name INT -type output
iadddocumentation -name Description -text "Interrupt Request"

# Formal parameters
imodeladdformal -name registeronly -type bool
imodeladdformal -name quantumdelay -type bool

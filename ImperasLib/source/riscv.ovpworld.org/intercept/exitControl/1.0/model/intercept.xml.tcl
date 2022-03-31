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

imodelnewsemihostlibrary  \
                -name exitControl  \
                -vendor riscv.ovpworld.org  \
                -library intercept  \
                -version 1.0  \
                -imagefile model  \

iadddocumentation  \
                -name Licensing  \
                -text "Open Source Apache 2.0"

iadddocumentation  \
                -name Description  \
                -text "Allows the specification of mechanisms that will cause the simulation to exit"

                                
imodeladdformal -name symbol -type String
iadddocumentation  -name Description  \
                -text "symbol on which to exit simulation"
imodeladdformal -name address -type Uns64
iadddocumentation  -name Description  \
                -text "address on which to exit simulation"
imodeladdformal -name onWriteToHost -type bool
iadddocumentation  -name Description  \
                -text "if function write_to_host() is executed exit simulation"

imodeladdformal -name onTerminate -type bool
iadddocumentation  -name Description  \
                -text "if function terminate() is executed exit simulation"
imodeladdformal -name onOpcode -type Uns64
iadddocumentation  -name Description  \
                -text "if opcode is executed exit simulation"
imodeladdformal -name ecallResultReg -type Uns64
iadddocumentation  -name Description  \
                -text "Result Register, read on ecall, for RISCV.org Conformance Test reporting. 3=GP, 10=A0 or 28=T3"

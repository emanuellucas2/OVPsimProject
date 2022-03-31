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
                -name customControl  \
                -vendor riscv.ovpworld.org  \
                -library intercept  \
                -version 1.0  \
                -imagefile model  \

iadddocumentation  \
                -name Licensing  \
                -text "Open Source Apache 2.0"

iadddocumentation  \
                -name Description  \
                -text "Interception of custom0 instruction for character output and simulation termination"
iadddocumentation  \
                -name Description  \
                -text "Interception of _test_stdout for character output and simulation termination"
iadddocumentation  \
                -name Description  \
                -text "Pseudo UART at address range 0x10010000 to 0x1001000f (default, relocate using uartbase) "

imodeladdformal -name logfile -type String
iadddocumentation  \
                -name Description  \
                -text "Logfile for custom0 character stream"

imodeladdformal -name nouart -type String
iadddocumentation \
                -name Description  \
                -text "Remove instance of UART between 0x10010000 and 0x1001000f (default)"
imodeladdformal -name uartbase -type String
iadddocumentation \
                -name Description  \
                -text "Change the UART base address from 0x10010000 (default)"

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
# NAME : signatureDump

imodelnewsemihostlibrary  \
                -name signatureDump  \
                -vendor riscv.ovpworld.org  \
                -library intercept  \
                -version 1.0  \
                -imagefile model  \

iadddocumentation  \
                -name Licensing  \
                -text "Open Source Apache 2.0"

iadddocumentation  \
                -name Description  \
                -text "Generate a signature file from memory contents and control test termination"


imodeladdformal -name ResultReg -type string
iadddocumentation  -name Description  \
                   -text "Result Register for RISCV.org Conformance Test. 3=GP, 10=A0 or 28=T3 (default)"
imodeladdformal -name SignatureFile -type string
iadddocumentation  -name Description  \
                   -text "Name of the signature file"
imodeladdformal -name SignatureAtEnd -type bool
iadddocumentation  -name Description  \
                   -text "Generate a Signature file at the end of simulation (default to generate on detection of call to write_tohost())"
imodeladdformal -name SignatureGranularity -type uns32
iadddocumentation  -name Description  \
                   -text "Granularity of signature file (supports default 16 or 4 bytes)"
imodeladdformal -name StartAddress -type uns32
iadddocumentation  -name Description  \
                   -text "Address of the Start Symbol"
imodeladdformal -name StartSymbol -type string
iadddocumentation  -name Description  \
                   -text "begin_signature, Name of the Start Symbol"
imodeladdformal -name EndAddress -type uns32
iadddocumentation  -name Description  \
                   -text "Address of the End Symbol"
imodeladdformal -name EndSymbol -type string
iadddocumentation  -name Description  \
                   -text "end_signature,  Name of the End Symbol"
imodeladdformal -name ByteCount -type uns32
iadddocumentation  -name Description  \
                   -text "Size of region in bytes (must be granularity sizebyte blocks)"

                   

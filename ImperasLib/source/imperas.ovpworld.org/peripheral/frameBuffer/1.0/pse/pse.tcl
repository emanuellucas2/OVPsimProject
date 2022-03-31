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

set vendor  imperas.ovpworld.org
set library peripheral
set name    frameBuffer
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version \
                    -constructor constructor -destructor destructor \
                    -extensionfile model 

iadddocumentation -name Licensing -text "Open Source Apache 2.0"

iadddocumentation -name Description -text "Provides Frame Buffer output."
iadddocumentation -name Description -text "Supports frame buffer formats used in Neural Network demo application i.e. RGB565 16-bit float for Alexnet application."

#
# Signal inputs
#
imodeladdnetport -name reset -type input

#
# Ports 
#
set regWidth 32
imodeladdbusslaveport -name mp -mustbeconnected -remappable -addresswidth 32
imodeladdbusslaveport -name sp -mustbeconnected -size 0x1000
imodeladdaddressblock -name A -port sp -size 0x1000 -offset 0 -width $regWidth

set registers {
                FB_SET_BASE         0x00  w  0  0              writeBASE
                FB_SET_BLANK        0x10  w  0  0              writeBLANK
                FB_SET_TITLE        0x20  w  0  0              writeTITLE
}

foreach {rname roffset raccess reset readFunc writeFunc} $registers {
    switch -glob "$raccess $readFunc $writeFunc" {
        "* 0 0"   { imodeladdmmregister -addressblock sp/A -name $rname -width $regWidth -offset $roffset -access $raccess }
        "* * 0"   { imodeladdmmregister -addressblock sp/A -name $rname -width $regWidth -offset $roffset -access $raccess -readfunction $readFunc                            }
        "* 0 *"   { imodeladdmmregister -addressblock sp/A -name $rname -width $regWidth -offset $roffset -access $raccess                          -writefunction $writeFunc }
        "rw *"    { imodeladdmmregister -addressblock sp/A -name $rname -width $regWidth -offset $roffset -access $raccess -readfunction $readFunc -writefunction $writeFunc  }
    }
    imodeladdreset -mmregister sp/A/$rname -name reset -value $reset
}

#
# Configuration Attributes
#
imodeladdformal -name noGraphics    -type bool
imodeladdformal -name pixelChecksum -type bool			  
imodeladdformal -name period        -type uns32 -defaultvalue 20000
imodeladdformal -name title         -type string
imodeladdformal -name statsOutput   -type uns32
imodeladdformal -name frameType     -type uns32

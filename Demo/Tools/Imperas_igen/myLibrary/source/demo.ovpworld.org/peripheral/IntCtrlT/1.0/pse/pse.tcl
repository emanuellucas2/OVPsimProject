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


# This file generates a skelton for a simple interrupt controller.
# The insterrupt controller has 16 inputs that can generate an output interrupt.
# Each input interrupt can be enabled/disabled using the IEN port and the level
# generated can be set using the LEVEL port.
# The curent active interrupt is determined using the SCAN port

# Define new model
imodelnewperipheral -vendor    demo.ovpworld.org \
                    -library   peripheral        \
                    -name      IntCtrlT          \
                    -version   1.0               \
                    -imagefile pse.pse  

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Description  \
    -text "This is a simple peripheral defintion. It provides the port and register definitions to generate a template."

iadddocumentation  \
    -name Limitations  \
    -text "There is no behaviour defined for this peripheral."


# Add ports to model
imodeladdbusslaveport -name bportscan  -mustbeconnected -size 4
imodeladdbusslaveport -name bportien   -mustbeconnected -size 16
imodeladdbusslaveport -name bportlevel -mustbeconnected -size 64

# Add attributes that can be specified
imodeladdformal -name interrupts -type integer
imodeladdformal -name endian     -type string

# Add an interrupt line output
imodeladdnetport -name intOut -type output

# Add interrupt line inputs
for { set count 0 } { $count < 16 } { incr count } {
  imodeladdnetport -name int$count -type input
}

# Add register accessed through the SCAN port
imodeladdaddressblock -name A -port bportscan -size 4 -offset 0 -width 32
imodeladdmmregister -addressblock bportscan/A -name scan -width 32 -offset 0 -access r -readfunction readScan

# Add registers accessed through the IEN port
imodeladdaddressblock -name A -port bportien -size 16 -offset 0 -width 32

for { set outer 0 } { $outer < 4 } { incr outer } {
    imodeladdmmregister -addressblock bportien/A -name "Ien_Int_$outer" -width 32 -offset [expr 4 * $outer] -access rw -writefunction writeIen -readfunction readIen
}

# Add registers accessed though the LEVEL port
imodeladdaddressblock -name A -port bportlevel -size 64 -offset 0 -width 32

for { set outer 0 } { $outer < 4 } { incr outer } {
    for { set inner 0 } { $inner < 4 } { incr inner } {
        set offset [expr 60 - (16 * $outer) - (4 * $inner) ]
        imodeladdmmregister \
            -addressblock bportlevel/A \
            -name "Int_Level_${outer}_${inner}" \
            -width 32 \
            -offset $offset \
            -access w \
            -writefunction writeLevel
    }
}

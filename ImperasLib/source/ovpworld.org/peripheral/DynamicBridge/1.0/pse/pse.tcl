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

#
set desc "DynamicBridge - Dynamically enable/disable a bus bridge from the input slave port to the output master port.
The bridge is enabled when the input net is high, disabled when it is low.
The size of the port is defined with the portSize parameter.
The address on the input slave port is defined by the spLoAddress parameter.
The address on the output master port is defined by the mpLoAddress parameter.
All three parameters must be specified.
The input and output ports may be connected to the same bus."

set limitations "The range of the input slave port must not conflict with any exiting port connected to the bus.
The output bus width is hard coded to be 32 bits." 
#

imodelnewperipheral  \
    -name        DynamicBridge \
    -vendor      ovpworld.org  \
    -library     peripheral \
    -version     1.0 \
    -constructor constructor\
    -releasestatus ovp        \
    -visibility    visible 

# Output bus size is 32 bits
set outputBusWidth  32

iadddocumentation -name Description -text $desc
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Limitations -text $limitations
iadddocumentation -name Reference   -text "This is not based upon the operation of a real device"

# Define bus slave input port
imodeladdbusslaveport  -name sp -remappable -mustbeconnected -addresswidth 63

# Define bus master output port
imodeladdbusmasterport -name mp -addresswidth 32 -addresswidthmin 16 -addresswidthmax 63 -mustbeconnected

# Define enable net input port
imodeladdnetport -name enable -type input -updatefunction updateEnable

# Define formals for specifying the output master and slave bus port location and size
imodeladdformal -name mpLoAddress -type uns64
imodeladdformal -name spLoAddress -type uns64
imodeladdformal -name portSize    -type uns64

imodeladdformal -name enableBridge -type bool

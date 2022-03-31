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
    -name          trap \
    -vendor        ovpworld.org  \
    -library       peripheral \
    -version       1.0 \
    -constructor   constructor \
    -releasestatus ovp        \
    -visibility    visible 

iadddocumentation -name Description -text "Open a port and allocate a region that is defined by parameters."
iadddocumentation -name Description -text "The region can be configured to act as standard memory or can report read/write accesses."
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Limitations -text "This peripheral cannot be used in a hardware description used to generate a TLM platform."
iadddocumentation -name Reference   -text "This is not based upon the operation of a real device but is intended to be used for bring up and development of new virtual platforms."

# Define bus slave input port
imodeladdbusslaveport  -name bport1 -remappable -mustbeconnected  -addresswidth 32

# Define formals for specifying the slave bus port location and size
imodeladdformal -name portAddress -type uns32
iadddocumentation -name Description -text "Defines the memory address at which the port is connected."
set portsize 0x1000
imodeladdformal -name portSize    -type uns32 -defaultvalue $portsize
iadddocumentation -name Description -text "Defines the size, in bytes, of the port (Default $portsize)."

imodeladdformal -name cbEnable    -type bool  -defaultvalue False
iadddocumentation -name Description -text "Defines the behaviour on an access. The default operation provides a memory area. If this parameter is set all accesses are reported."

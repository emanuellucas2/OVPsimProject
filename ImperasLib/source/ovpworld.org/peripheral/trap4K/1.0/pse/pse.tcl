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
    -name          trap4K \
    -vendor        ovpworld.org  \
    -library       peripheral \
    -version       1.0 \
    -constructor   constructor \
    -releasestatus ovp        \
    -visibility    visible 

set portsize 0x1000
    
iadddocumentation -name Description -text "Open a port and allocate a $portsize Byte region of memory."
iadddocumentation -name Description -text "The region will act as standard memory with reports of read/write accesses."
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Limitations -text "None"
iadddocumentation -name Reference   -text "This is not based upon the operation of a real device but is intended to be used for bring up and development of new virtual platforms."

# Define bus slave input port
imodeladdbusslaveport -name bport1 -size $portsize -mustbeconnected
imodeladdaddressblock -name MEM -port bport1 -size $portsize -offset 0 -width 32
imodeladdlocalmemory  -name buffer -addressblock bport1/MEM -size $portsize \
                      -readfunction readMemCB -writefunction writeMemCB


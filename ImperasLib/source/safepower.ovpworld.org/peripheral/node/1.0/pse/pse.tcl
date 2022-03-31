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


set vendor  safepower.ovpworld.org
set library peripheral
set name    node
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor 

iadddocumentation  \
    -name Description  \
    -text "Example Network on Chip (NoC) node peripheral for SafePower Project"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "This model implements a data and control interface to allow a processor to receive or transmit data across a packetnet interface. This is used to illustrate the use as part of a NoC."

iadddocumentation -name Reference -text "No Reference, created as an example"

#
# Registers
#
set port "hostif"
imodeladdbusslaveport  -name ${port} -size 0x400 -mustbeconnected

# Control/Status
set abrsize 0x10
set abr  "reg"
imodeladdaddressblock  -name ${abr}  -port ${port} -size $abrsize -offset 0 -width 32

imodeladdmmregister -addressblock ${port}/${abr} -name control -width 32 -offset  0 -access rw -writefunction writeControl
imodeladdmmregister -addressblock ${port}/${abr} -name status  -width 32 -offset  4 -access rw

# Tx Message Buffer
set abdtxsize 0x100
set abdtx  "msgtx"

imodeladdaddressblock  -name ${abdtx}  -port ${port} -size $abdtxsize -offset 0x100 -width 32

imodeladdmmregister  -addressblock ${port}/${abdtx} -name id     -width 32   -offset 0x00 -access rw
imodeladdmmregister  -addressblock ${port}/${abdtx} -name from   -width 32   -offset 0x04 -access rw
imodeladdmmregister  -addressblock ${port}/${abdtx} -name nid    -width 32   -offset 0x08 -access rw
imodeladdmmregister  -addressblock ${port}/${abdtx} -name msgLen -width 32   -offset 0x0c -access rw
imodeladdlocalmemory -addressblock ${port}/${abdtx} -name msgBuf -size  0xf0 -offset 0x10 -access rw

# Rx Message Buffer
set abdrxsize 0x100
set abdrx  "msgrx"

imodeladdaddressblock  -name ${abdrx}  -port ${port} -size $abdrxsize -offset 0x200 -width 32

imodeladdmmregister  -addressblock ${port}/${abdrx} -name id     -width 32   -offset 0x00 -access rw
imodeladdmmregister  -addressblock ${port}/${abdrx} -name from   -width 32   -offset 0x04 -access rw
imodeladdmmregister  -addressblock ${port}/${abdrx} -name nid    -width 32   -offset 0x08 -access rw
imodeladdmmregister  -addressblock ${port}/${abdrx} -name msgLen -width 32   -offset 0x0c -access rw
imodeladdlocalmemory -addressblock ${port}/${abdrx} -name msgBuf -size  0xf0 -offset 0x10 -access rw


imodeladdpacketnetport -name network -updatefunction networkrx -maxbytes 0xf0

imodeladdformal -name id -type uns32 -defaultvalue 1 -min 1 -max 16
imodeladdformal -name endian -type string 

iadddocumentation \
    -handle id -name Description \
    -text "Defines the id for the node (must all be unique in design)"

# Regsiter descriptions
iadddocumentation \
  -handle ${port}/${abr}/control -name Description \
  -text "Control register"
iadddocumentation \
  -handle ${port}/${abr}/status -name Description \
  -text "Transfer status register"
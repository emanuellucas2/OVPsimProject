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
set name    TTELNode
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor 

iadddocumentation  \
    -name Description  \
    -text "The TTEL Network on Chip (NoC) node peripheral for SafePower Project"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "This model implements the TTEL NoC node processor interface. It does not model any timing in the transfer of messages between nodes."

iadddocumentation \
    -name Reference \
    -text "Generated using document TTEL Software Extensions ver 1.0 and D1.2.1 architectural style of dreams r1-0."

#
# Registers
#

set port     "hostif"
set portSize 0x01000000
imodeladdbusslaveport  -name ${port} -size ${portSize} -mustbeconnected

proc printfInfo {regs offset size} {
    global name
#    puts "# ${name}: ${regs} [ format 0x%08x $offset] - [ format 0x%08x [expr $offset + $size - 1]]"
}

# Data Port - Reconfiguration Registers
set abr    "rec"
set abrsize 0x00010000
set abroff  0x00000000
printfInfo ${abr} $abroff $abrsize
imodeladdaddressblock  -name ${abr}  -port ${port} -size $abrsize -offset $abroff -width 32
imodeladdlocalmemory   -nbyte -name port  -addressblock ${port}/${abr} -offset 0 -size $abrsize  -access rw -readfunction readData -writefunction writeData -userdata 0
imodeladdlocalmemory   -nbyte -name term  -addressblock ${port}/${abr} -offset 0x8000 -size 0x1fff -access  w -writefunction writePortTerminate -userdata 0

# Data Ports
set abp      "port"
set abpsize  0x00010000
set abpbase  0x00010000
set portmax  254

# 0x00id0000-0x00id1fff : Data (read or write)
# 0x00id4000-0x00id5fff : length (read)
# 0x00id8000-0x00id9fff : terminate (write)

imodeladdaddressblock  -name ${abp}%u  -port ${port} -size $abpsize -offset $abpbase -width 32 -loarray 1 -hiarray  [expr $portmax-1]
  imodeladdlocalmemory   -name data   -addressblock ${port}/${abp}%u -offset 0x0000 -size 0x1fff -access rw -readfunction readData -writefunction writeData -userdata _index
  imodeladdlocalmemory   -name length -addressblock ${port}/${abp}%u -offset 0x4000 -size 0x1fff -access r  -readfunction readPortLength      -userdata _index
  imodeladdlocalmemory   -name term   -addressblock ${port}/${abp}%u -offset 0x8000 -size 0x1fff -access  w -writefunction writePortTerminate -userdata _index

# Port Error
set abe    "err"
set abesize 0x00010000
set abeoff  0x00fe0000
printfInfo ${abe} $abeoff $abesize
imodeladdaddressblock  -name ${abe}  -port ${port} -size $abesize -offset $abeoff -width 32
imodeladdlocalmemory   -name err  -addressblock ${port}/${abe} -offset 0 -size $abesize -access rw

# Port Status
set abs    "mon"
set abssize 0x00010000
set absoff  0x00ff0000
printfInfo ${abs} $absoff $abssize
imodeladdaddressblock  -name ${abs}  -port ${port} -size $abssize -offset $absoff -width 32
imodeladdlocalmemory   -name empty   -addressblock ${port}/${abs} -offset 0x0000 -size    32 -access r
imodeladdlocalmemory   -name full    -addressblock ${port}/${abs} -offset 0x0020 -size    32 -access r
imodeladdlocalmemory   -name status  -addressblock ${port}/${abs} -offset 0x0040 -size 0x400 -access r
imodeladdlocalmemory   -name gbltim0 -addressblock ${port}/${abs} -offset 0x0440 -size     4 -access r -readfunction readGlobalTime -userdata 0
imodeladdlocalmemory   -name gbltim1 -addressblock ${port}/${abs} -offset 0x0444 -size     4 -access r -readfunction readGlobalTime -userdata 1

# Status Word Contents
# 31-22 reserved
#    21 port full
#    20 port empty
#    19 buffer full
#    18 buffer empty
# 17-10 number of queued messages
#  9- 0 message length (words)

# Defines the unique node physical identifier (cluster << 16) | (node << 8) | tile
imodeladdformal -name cluster -type uns32 -defaultvalue 0 -min 0 -max 255
imodeladdformal -name node    -type uns32 -defaultvalue 0 -min 0 -max 255
imodeladdformal -name tile    -type uns32 -defaultvalue 1 -min 0 -max 255

# there must be a configuration file defining in the channel information for the system
# format of a line is '<enable> <TSD=Target Source/Destination?> <Buffer Size> <Queue Length> <MINT>'
imodeladdformal -name configfile -type string
iadddocumentation -name Description -text "Configure the TTEL Node ports and NoC connections"

# Packetnet network interface
imodeladdpacketnetport -name network -updatefunction networkReceiveMsg -maxbytes 0x256

# periodic interrupt
imodeladdnetport -name  PeriodInterrupt -type output
iadddocumentation -name Description -text "Fixed rate periodic interrupt. Interrupts are configured per period"
imodeladdformal -name scheduledperiod -type uns32 -defaultvalue 10 -min 10 -max 10000
iadddocumentation -name Description -text "Configuration period for the PeriodInterrupt generation (allowed range 10uS to 10000uS)"

# scheduled core interrupt
imodeladdnetport -name  CoreInterrupt -type output
iadddocumentation -name Description -text "Scheduled interrupt. A schedule for interupts to be sent per period (defined by scheduleperiod that generates PeriodInterrupt)"
imodeladdformal -name coreintconfigfile -type string
iadddocumentation -name Description -text "Configure the CoreInterrupt generation schedule"

# packet received interrupt
imodeladdnetport -name  pIntToCore -type output
iadddocumentation -name Description -text "Interrupt indicates that a message has been received in a port"

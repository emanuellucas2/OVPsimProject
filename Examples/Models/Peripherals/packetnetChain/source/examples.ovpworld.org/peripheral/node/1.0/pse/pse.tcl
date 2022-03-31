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

# Setup variables for model info
set vendor  examples.ovpworld.org
set library peripheral
set name    node
set version 1.0

imodelnewperipheral  \
    -name ${name} \
    -library ${library} \
    -vendor ${vendor} \
    -version ${version} \
    -constructor constructor \
    -releasestatus ovp        \
    -visibility    visible

iadddocumentation  -name Description  \
                   -text "Simple test peripheral that receives data either from a processor interface or from packetnet input, processes the data and then either transmits it to the next node or holds it to be read by the processor."
iadddocumentation  -name Licensing  \
                   -text "Open Source Apache 2.0"
iadddocumentation  -name Limitations  -text "None"
iadddocumentation  -name Reference    -text "This is not based upon a real device"

# Port and address block names
set PORT     bp
set RB       regs
set MB       mem


# Size of registers address block
set regsSize 0x100

# width of registers
set regWidth 32

# Size of data buffers 
set bufSize  0x100

# Maximum size of packet: 1 word to hold data length + 1 data buffer
set pktSize [expr $bufSize + 4]

# Define MMIO port
imodeladdbusslaveport -name $PORT -size 0x1000

# Address blocks - one for registers, one for internal data buffers
imodeladdaddressblock -name $RB -port $PORT -size $regsSize           -offset 0x0       -width $regWidth
imodeladdaddressblock -name $MB -port $PORT -size [expr 2 * $bufSize] -offset $regsSize -width 8

# control register
imodeladdmmregister -addressblock $PORT/$RB -name control -width $regWidth -offset 0 -access rw -writefunction writeControl
    iadddocumentation  -handle $PORT/$RB/control -name Description -text "Control register"
    imodeladdreset -mmregister $PORT/$RB/control -name reset -value 0
    imodeladdfield -mmregister $PORT/$RB/control -bitoffset 0 -width 1 -name start
        iadddocumentation  -handle $PORT/$RB/control/start -name Description -text "Write 1 to start the transfer of data in TX buffer"
    imodeladdfield -mmregister $PORT/$RB/control -bitoffset 16 -width 9 -name length
        iadddocumentation  -handle $PORT/$RB/control/length -name Description -text "Number of bytes in the data buffer"

# status register
imodeladdmmregister -addressblock $PORT/$RB -name status -width $regWidth -offset 4 -access rw -writefunction clearStatus
	iadddocumentation  -handle $PORT/$RB/status -name Description -text "Status register"
	imodeladdreset -mmregister $PORT/$RB/status -name reset -value 0
	imodeladdfield -mmregister $PORT/$RB/status -bitoffset 0 -width 1 -name datainready
		iadddocumentation  -handle $PORT/$RB/status/datainready -name Description -text "Ready to accept data"
	imodeladdfield -mmregister $PORT/$RB/status -bitoffset 1 -width 1 -name waitingtosend
		iadddocumentation  -handle $PORT/$RB/status/waitingtosend -name Description -text "Waiting to send data"
	imodeladdfield -mmregister $PORT/$RB/status -bitoffset 2 -width 1 -name overflow
			iadddocumentation  -handle $PORT/$RB/status/overflow  -name Description -text "Overflow has occurred - message was written when not ready to accept data"
    
# tx/rx data buffers
imodeladdlocalmemory -addressblock $PORT/$MB -name txBuffer -access rw  -offset 0x0      -size $bufSize
imodeladdlocalmemory -addressblock $PORT/$MB -name rxBuffer -access rw  -offset $bufSize -size $bufSize

# data packetnet ports to/from adjacent nodes
imodeladdpacketnetport -name pin  -maxbytes $pktSize -updatefunction packetReceived
imodeladdpacketnetport -name pout -maxbytes $pktSize

# ready netports to/from adjacent nodes
imodeladdnetport -name readyOut -type output
imodeladdnetport -name readyIn  -type input   -updatefunction readyInCB

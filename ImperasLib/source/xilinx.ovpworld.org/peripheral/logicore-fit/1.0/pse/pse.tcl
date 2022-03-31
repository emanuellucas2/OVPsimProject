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
# Fixed Interval Timer (FIT)
# The FIT generates an interrupt every C_NO_CLOCKS.
# The interrupt signal is held High for one clock cycle. 
#

imodelnewperipheral \
     -name          logicore-fit \
     -version       1.0 \
     -library       peripheral \
     -vendor        xilinx.ovpworld.org \
     -constructor   constructor

iadddocumentation -name Description -text "logiCore Fixed Interval Timer (PG110)"
iadddocumentation -name Limitations -text "Initial verion. Not clock accurate"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Reference   -text "pg110-fixed-interval-timer November 18, 2015"

# Input port Rst - Reset
imodeladdnetport -name Rst -type input -updatefunction Reset_Reset

# Output port Interrupt
imodeladdnetport -name Interrupt -type output

# Delay duration - number of clocks
imodeladdformal -name C_NO_CLOCKS -type uns32 -defaultvalue 100000
# Delay inaccuracy - Default to zero
imodeladdformal -name C_INACCURACY -type uns32 -defaultvalue 0

# The input clock rate for the timer
set defaultClock 100
imodeladdformal -name CLOCK_RATE -type uns32 -defaultvalue $defaultClock
iadddocumentation -name Description -text "The clock rate at which to count (default $defaultClock)"
 

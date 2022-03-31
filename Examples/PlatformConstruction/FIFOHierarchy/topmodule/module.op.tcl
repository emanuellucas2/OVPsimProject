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

# This is a simple OVP platform using an OR1K processor to stimulate
# a peripheral model that drives a fifo interconnect.

ihwnew -name topmodule

# Create two modules that will communicate via the FIFO
ihwaddmodule  -instancename mod0 -modelfile submodule/model
ihwaddmodule  -instancename mod1 -modelfile submodule/model

ihwaddfifo -instancename fifo0 -width 32 
ihwaddfifo -instancename fifo1 -width 32 

ihwconnect  -fifo fifo0 -instancename mod0 -fifoport f0
ihwconnect  -fifo fifo0 -instancename mod1 -fifoport f1

ihwconnect  -fifo fifo1 -instancename mod1 -fifoport f0
ihwconnect  -fifo fifo1 -instancename mod0 -fifoport f1


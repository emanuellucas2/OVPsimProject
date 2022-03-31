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

ihwnew -name fifoTest -vendor ovpworld.org -library module -version 1.0

#
# Two identical peripheral models connected by a FIFO
#
ihwaddperipheral -instancename fifoModel1 -modelfile peripheral/pse.pse
ihwaddperipheral -instancename fifoModel2 -modelfile peripheral/pse.pse

#
# The fifo interconnect
#
ihwaddfifo -instancename fifo1 -depth 16

#
# connect the peripherals to the FIFO
#
ihwconnect -instancename fifoModel1 -fifoport fifoPortIn  -fifo fifo1 
ihwconnect -instancename fifoModel2 -fifoport fifoPortOut -fifo fifo1 

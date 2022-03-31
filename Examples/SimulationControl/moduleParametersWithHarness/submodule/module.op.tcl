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

ihwnew -name subUart
iadddocumentation -name Description -text "This a sub module that includes one UART"

#
# Add formal parameters that can be set when module instanced
#
ihwaddformalparameter -name baseAddress -type address
iadddocumentation -name Description -text "Set base address of UART"

# local bus
ihwaddbus -instancename localBus -addresswidth 32

# connect peripheral to local bus
ihwaddperipheral -instancename uart0 \
                 -vendor national.ovpworld.org -library peripheral -type 16550 -version 1.0
ihwconnect       -instancename uart0 -bus localBus -busslaveport  bport1 \
                 -loaddress {baseAddress} -hiaddress {baseAddress+7}

# connect bus to bus port
ihwaddbusport -instancename mainBusPort
ihwconnect -busport mainBusPort -bus localBus

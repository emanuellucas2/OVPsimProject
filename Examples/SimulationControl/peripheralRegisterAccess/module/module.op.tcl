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

ihwnew -name simpleUart

ihwaddbus -instancename mainBus -addresswidth 32

ihwaddperipheral -instancename uart1 \
                -vendor national.ovpworld.org -library peripheral -type 16550 -version 1.0

ihwconnect -bus mainBus -instancename uart1 -busslaveport bport1 -loaddress 0 -hiaddress 0x7

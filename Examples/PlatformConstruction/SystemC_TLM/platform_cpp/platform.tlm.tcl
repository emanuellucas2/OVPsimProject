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

# This TCL script is used by IGEN to create the
# TLM platform 'simple'

ihwnew -name simple -vendor imperas.com -library platform -version 1.0 \
       -stoponctrlc
       
ihwaddclp -stdargs

ihwaddprocessor -instancename cpu1 -type or1k \
         -semihostvendor ovpworld.org -semihostname or1kNewlib \
         -enableintercepts

ihwaddbus -instancename bus1 -addresswidth 32

ihwconnect -instancename cpu1 -busmasterport INSTRUCTION  -bus bus1 
ihwconnect -instancename cpu1 -busmasterport DATA         -bus bus1 

ihwaddperipheral -instancename uart1 -type 16550
ihwconnect       -instancename uart1 -bus bus1 -busslaveport bport1 \
                 -loaddress 0x90000000  \
                 -hiaddress 0x90000007
ihwsetparameter  -handle uart1 -name outfile -value uart1.log -type string

ihwaddmemory     -instancename ram1 -type ram
ihwconnect       -instancename ram1 -bus bus1 -busslaveport sp1 \
                 -loaddress 0x00000000  \
                 -hiaddress 0x000FFFFF

ihwaddmemory     -instancename ram2 -type ram
ihwconnect       -instancename ram2 -bus bus1 -busslaveport sp1 \
                 -loaddress 0xFFFF0000  \
                 -hiaddress 0xFFFFFFFF

ihwaddnet    -instancename int1
ihwconnect	 -net int1 -instancename uart1 -netport intOut
ihwconnect	 -net int1 -instancename cpu1  -netport intr0

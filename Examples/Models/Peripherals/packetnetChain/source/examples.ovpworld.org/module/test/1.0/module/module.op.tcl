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

ihwnew -name test  \
       -vendor examples.ovpworld.org  \
       -library module  \
       -version 1.0 \
       -stoponctrlc \
       -purpose module -releasestatus ovp

iadddocumentation  \
       -name Description  \
       -text "Platform for demonstrating packetNet"

iadddocumentation  \
  -name Licensing  \
  -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "BareMetal example hardware definition"

iadddocumentation  \
    -name Reference  \
    -text "Not based on any current hardware"


ihwaddbus -instancename bus -addresswidth 32

ihwaddprocessor  \
       -instancename cpu -vendor riscv.ovpworld.org -type riscv -defaultsemihost

ihwsetparameter  -handle cpu -name variant        -value RVB32I -type enum
ihwsetparameter  -handle cpu -name add_Extensions -value MACSU  -type string

ihwconnect -instancename cpu -busmasterport INSTRUCTION -bus bus
ihwconnect -instancename cpu -busmasterport DATA        -bus bus
   
ihwaddmemory -instancename memory1 -type ram
ihwconnect -instancename memory1   -busslaveport sp1 -bus bus  \
                                     -loaddress 0x00000000 -hiaddress 0x3fffffff

ihwaddmemory -instancename memory2 -type ram
ihwconnect -instancename memory2   -busslaveport sp1 -bus bus  \
                                     -loaddress 0x41000000 -hiaddress 0xffffffff

# Declare nodeN_ready nets
ihwaddnet -instancename block_ready
ihwaddnet -instancename node1_ready 
ihwaddnet -instancename node2_ready 
ihwaddnet -instancename node3_ready 
ihwaddnet -instancename next_block_ready 

# Daisy changed nodes connected by packetnet 
ihwaddpacketnet -instancename       _to_node0
ihwaddpacketnet -instancename  node0_to_node1
ihwaddpacketnet -instancename  node1_to_node2
ihwaddpacketnet -instancename  node2_to_node3
ihwaddpacketnet -instancename  node3_to_
                                  
# Daisy chained nodes
ihwaddperipheral -instancename node0 -vendor examples.ovpworld.org -type node
ihwconnect -instancename node0 -busslaveport bp -bus bus  \
                                 -loaddress 0x40000000 -hiaddress 0x40000fff
ihwconnect -instancename node0 -packetnetport pin  -packetnet      _to_node0
ihwconnect -instancename node0 -packetnetport pout -packetnet node0_to_node1
ihwconnect -instancename node0 -netport readyOut -net block_ready
ihwconnect -instancename node0 -netport readyIn  -net node1_ready


ihwaddperipheral -instancename node1 -vendor examples.ovpworld.org -type node
ihwconnect -instancename node1 -busslaveport bp -bus bus  \
                                 -loaddress 0x40001000 -hiaddress 0x40001fff
ihwconnect -instancename node1 -packetnetport pin  -packetnet node0_to_node1
ihwconnect -instancename node1 -packetnetport pout -packetnet node1_to_node2
ihwconnect -instancename node1 -netport readyOut -net node1_ready
ihwconnect -instancename node1 -netport readyIn  -net node2_ready

ihwaddperipheral -instancename node2 -vendor examples.ovpworld.org -type node
ihwconnect -instancename node2 -busslaveport bp -bus bus  \
                                 -loaddress 0x40002000 -hiaddress 0x40002fff
ihwconnect -instancename node2 -packetnetport pin  -packetnet node1_to_node2
ihwconnect -instancename node2 -packetnetport pout -packetnet node2_to_node3
ihwconnect -instancename node2 -netport readyOut -net node2_ready
ihwconnect -instancename node2 -netport readyIn  -net node3_ready

ihwaddperipheral -instancename node3 -vendor examples.ovpworld.org -type node
ihwconnect -instancename node3 -busslaveport bp -bus bus  \
                                 -loaddress 0x40003000 -hiaddress 0x40003fff
ihwconnect -instancename node3 -packetnetport pin  -packetnet node2_to_node3
ihwconnect -instancename node3 -packetnetport pout -packetnet node3_to_
ihwconnect -instancename node3 -netport readyOut -net node3_ready
ihwconnect -instancename node3 -netport readyIn  -net next_block_ready

# Block Ready ports
ihwaddnetport -instancename block_ready
ihwconnect -netport block_ready  -net block_ready

ihwaddnetport -instancename next_block_ready
ihwconnect -netport next_block_ready -net next_block_ready


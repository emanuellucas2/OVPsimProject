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
       -vendor imperas.ovpworld.org  \
       -library module  \
       -version 1.0 \
       -stoponctrlc \
       -purpose module \
       -releasestatus ovp

iadddocumentation  \
       -name Description  \
       -text "Platform for demonstrating socket communication example"

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


ihwaddperipheral -instancename sktIf -vendor imperas.ovpworld.org -type socketInterface
ihwconnect -instancename sktIf -busslaveport sp -bus bus -loaddress 0x40000000 -hiaddress 0x4000000f
ihwconnect -instancename sktIf -busmasterport mp -bus bus

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


set desc "
This platform implements an Arm Cortex-A9UP processor with some memory and a UART.

Address bits 40:0 are used in the platform, so TrustZone security information is 
included in bus transactions. A bridge is added to map the non-secure address 
for the UART so it is always accessible from non-secure mode.
"

ihwnew -name alwaysNonSecure
iadddocumentation -name Description -text $desc

#
# tzBus - 41 bits of address - implements secure and non-secure address spaces
#
ihwaddbus -instancename tzBus -addresswidth 41

#
# pBus  - 32 bits of address - physical bus connected to devices and memory
#
ihwaddbus -instancename pBus  -addresswidth 32

#
# Bridge - Secure space of tzBus always mapped to pBus
#
ihwaddbridge -instancename secure
ihwconnect   -instancename secure -busslaveport  sp -bus tzBus \
             -loaddress 0x00000000 -hiaddress 0xffffffff
ihwconnect   -instancename secure -busmasterport mp -bus pBus  \
             -loaddress 0x00000000 -hiaddress 0xffffffff

#
# Processor
#
ihwaddprocessor -instancename cpu -type arm -vendor arm.ovpworld.org -endian little -semihostname armNewlib -semihostvendor arm.ovpworld.org 
ihwconnect      -instancename cpu -busmasterport INSTRUCTION -bus tzBus
ihwconnect      -instancename cpu -busmasterport DATA        -bus tzBus
ihwsetparameter   -handle       cpu -name variant       -value Cortex-A9UP   -type enum
ihwsetparameter   -handle       cpu -name compatibility -value nopSVC        -type enum

#
# Memory: 0x00000000    0x001fffff  RAM
#
ihwaddmemory -instancename ram0 -type ram
ihwconnect   -instancename ram0 -busslaveport sp1 -bus pBus \
             -loaddress 0x00000000 -hiaddress 0x001fffff

#
# Bridge - Memory always accessible from non-secure mode
#
ihwaddbridge -instancename ram0NS
ihwconnect   -instancename ram0NS -busslaveport  sp -bus tzBus \
             -loaddress 0x10000000000 -hiaddress 0x100001fffff
ihwconnect   -instancename ram0NS -busmasterport mp -bus pBus \
             -loaddress 0x00000000 -hiaddress 0x001fffff

#
# UART:   0x10000000    0x10000fff  UartPL011
# 
ihwaddperipheral -instancename uart0   -type UartPL011 -vendor arm.ovpworld.org
ihwconnect       -instancename uart0   -busslaveport  bport1 -bus pBus \
                 -loaddress 0x10000000 -hiaddress 0x10000fff
ihwsetparameter    -handle       uart0   -name outfile -value uart0.log    -type string

#
# Bridge - UART always accessible from non-secure mode
#
ihwaddbridge     -instancename uart0NS
ihwconnect       -instancename uart0NS -busslaveport  sp -bus tzBus \
                 -loaddress 0x10010000000 -hiaddress 0x10010000fff
ihwconnect       -instancename uart0NS -busmasterport mp -bus pBus  \
                 -loaddress    0x10000000 -hiaddress    0x10000fff

#
# Add command line arguments to platform
#
ihwaddclp -allargs

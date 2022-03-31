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

Only address bits 31:0 are used in the platform, so no TrustZone security 
information is included in bus transactions and all addresses are accessible in 
both secure and non-secure modes.
"

ihwnew -name ignoreTrustZone
iadddocumentation -name Description -text $desc

#
# Bus - 32 bits of address (Secure bit ignored)
#
ihwaddbus -instancename pBus -addresswidth 32

#
# Processor
#
ihwaddprocessor -instancename cpu -type arm -vendor arm.ovpworld.org -endian little -semihostname armNewlib -semihostvendor arm.ovpworld.org
ihwconnect      -instancename cpu -busmasterport INSTRUCTION -bus pBus
ihwconnect      -instancename cpu -busmasterport DATA        -bus pBus
ihwsetparameter   -handle       cpu -name variant       -value Cortex-A9UP  -type enum
ihwsetparameter   -handle       cpu -name compatibility -value nopSVC       -type enum

#
# Memory: 0x00000000    0x001fffff  RAM
#
ihwaddmemory -instancename ram0 -type ram
ihwconnect   -instancename ram0 -busslaveport sp1 -bus pBus \
             -loaddress 0x00000000 -hiaddress 0x001fffff

#
# UART:   0x10000000    0x10000fff  UartPL011
# 
ihwaddperipheral -instancename uart0   -type UartPL011 -vendor arm.ovpworld.org
ihwconnect       -instancename uart0   -busslaveport  bport1 -bus pBus \
                 -loaddress 0x10000000 -hiaddress 0x10000fff
ihwsetparameter    -handle       uart0   -name outfile -value uart0.log   -type string

#
# Add command line arguments to platform
#
ihwaddclp -allargs

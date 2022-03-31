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


set desc "This platform instances an ARM IntegratorCP with a Xilinx Microbalzed based sub-system"

set limit "Peripherals are modeled only to the extent required to boot and run Operating Systems such as Linux."

set ref "ARM Development Boards Integrator CP BaseBoard and Integrator Core Modules ARM9x6 and Cortex-A9"

# Setup variables for platform info
set vendor  imperas.ovpworld.org
set library module
set name    Hetero_ArmIntegratorCP_XilinxMicroBlaze
set version 1.0

#
# Start new platform creation
#
ihwnew -name $name -vendor $vendor -library $library -version $version -stoponctrlc -purpose module -releasestatus imperas

iadddocumentation -name Licensing -text "Open Source Apache 2.0"

iadddocumentation -name Description -text $desc
iadddocumentation -name Limitations -text $limit
iadddocumentation -name Reference -text $ref

###############################################################################################################################
# Arm IntegratorCP system
###############################################################################################################################

ihwaddmodule -instancename integratorcp  \
             -vendor arm.ovpworld.org \
             -library module \
             -type ArmIntegratorCP \
             -version 1.0

###############################################################################################################################
# Xilinx MicroBlaze system 
###############################################################################################################################


ihwaddbus -instancename busX1 -addresswidth 32

#
# Processor
#
ihwaddprocessor -instancename xilinx1 -type microblaze -vendor xilinx.ovpworld.org -version 1.0

#
# Connect processor to bus
#
ihwconnect -bus busX1 -instancename xilinx1 -busmasterport INSTRUCTION
ihwconnect -bus busX1 -instancename xilinx1 -busmasterport DATA

ihwaddmemory -instancename ramX1  -type ram
ihwconnect -bus busX1 -instancename ramX1 -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0x2fffffff

ihwaddperipheral -instancename uartX -type 16550 -vendor national.ovpworld.org
ihwconnect       -instancename uartX -bus busX1  -busslaveport  bport1 -loaddress 0x40000000 -hiaddress 0x40000007
ihwsetparameter  -handle       uartX  -name outfile -value uartX.log -type string

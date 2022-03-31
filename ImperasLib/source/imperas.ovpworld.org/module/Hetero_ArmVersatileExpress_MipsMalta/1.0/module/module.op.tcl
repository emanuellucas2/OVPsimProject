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


set desc "This platform instances an ARM VersatileExpress with a MIPS Malta"

set limit "Peripherals are modeled to the extent required to boot and run Operating Systems such as Linux."

set ref "ARM Development Boards Versatile Express BaseBoard and ARM CoreTile Express A15x2 
	 MIPS Malta User's Manual MD00048-2B-MALTA-USM-1.07.pdf
	 MIPS Malta-R Development Platform User's Manual MD00627-2B-MALTA_R-USM-01.01.pdf    
	 CoreFPGA User's Manual MD00116-2B-COREFPGA-USM-01.00.pdf
	 Linux for the MIPS Malta Development Platform User's Guide MD00646-2B-LINUXMALTA-USM-01.03.pdf"

# Setup variables for platform info
set vendor  imperas.ovpworld.org
set library module
set name    Hetero_ArmVersatileExpress_MipsMalta
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

ihwaddmodule -instancename versatileexpress  \
             -vendor arm.ovpworld.org \
             -library module \
             -type ArmVersatileExpress-CA15 \
             -version 1.0

###############################################################################################################################
# Xilinx MicroBlaze system 
###############################################################################################################################

ihwaddmodule -instancename malta  \
             -vendor mips.ovpworld.org \
             -library module \
             -type MipsMalta \
             -version 1.0

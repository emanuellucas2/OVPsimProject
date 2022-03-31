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


set desc "This platform instances both the Altera Cyclone V (ARM) and Cyclone III (Nios_II) processor systems"

set limit "Peripherals are modeled only to the extent required to boot and run Operating Systems such as Linux."

set ref "Altera Cyclone III 3c120 Reference Guide and Cyclone V Handbook Volume 3: Hard Processor System Technical Reference Manual cv_5v4 2013.12.30"

# Setup variables for platform info
set vendor  imperas.ovpworld.org
set library module
set name    Hetero_AlteraCycloneV_HPS_AlteraCycloneIII_3c120
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
# CycloneV HPS system
###############################################################################################################################

ihwaddmodule -instancename CycloneV_HPS  \
             -vendor altera.ovpworld.org \
             -library module \
             -type AlteraCycloneV_HPS \
             -version 1.0

###############################################################################################################################
# CycloneIII system 
###############################################################################################################################

ihwaddmodule -instancename CycloneIII \
	     -vendor altera.ovpworld.org \
	     -library module \
	     -type AlteraCycloneIII_3c120 \
	     -version 1.0


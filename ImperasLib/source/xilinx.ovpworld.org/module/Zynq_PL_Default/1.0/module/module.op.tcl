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

set desc "This module implements a default of the Xilinx Zynq Programmable Logic (PL).
This PL configuration instances no devices or memory."

set limitations "The is baremetal only."

set reference "No Reference"

set license "Open Source Apache 2.0"

# Setup variables for platform info 
set vendor  xilinx.ovpworld.org
set library module
set name    Zynq_PL_Default
set version 1.0

#
# Start new platform creation 
#
ihwnew -name $name -vendor $vendor -library $library -version $version -stoponctrlc -purpose module -releasestatus ovp
iadddocumentation -name Licensing   -text $license
iadddocumentation -name Description -text $desc
iadddocumentation -name Limitations -text $limitations
iadddocumentation -name Reference   -text $reference

# Include the default interconnect ports and signals for the PL to PS
source "$env(IMPERAS_HOME)/ImperasLib/source/xilinx.ovpworld.org/module/Zynq_PL_Default/1.0/module/PS_PL_interconnect.tcl"

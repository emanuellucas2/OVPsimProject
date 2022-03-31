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


# Allow configuration of VOUT_MODE value
set defaultVoutMode -12
imodeladdformal -name voutmode -type int32 -defaultvalue $defaultVoutMode
iadddocumentation -name Description -text "Set the value to read for VOUT_MODE (default $defaultVoutMode)"

# Allow configuration of STATUS_MFR_SPECIFIC value
set defaultStatusMfrSpecific 0
imodeladdformal -name statusmfrspecific -type uns32 -defaultvalue $defaultStatusMfrSpecific
iadddocumentation -name Description -text "Set the value to read for STATUS_MFR_SPECIFIC (default $defaultStatusMfrSpecific)"

# NOTE
# If you change this file please ensure you touch other dependent files
#   ti.ovpworld.org/peripheral/ucd9012a/1.0/pse/pse.tcl
#   ti.ovpworld.org/peripheral/ucd9248/1.0/pse/pse.tcl
#   xilinx.ovpworld.org/peripheral/zynq_7000-devcfg/1.0/pse/pse.tcl
# as dependencies are not supported in the tcl build
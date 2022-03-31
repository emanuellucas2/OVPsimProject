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

# Setup variables for platform info 
set vendor  sifive.ovpworld.org
set library module
set name    coreip-s51-rtl
set version 1.0

#
# Start new platform creation 
#
ihwnew -name $name -vendor $vendor -library $library -version $version -stoponctrlc -purpose module -releasestatus ovp

iadddocumentation -name Licensing    -text "Open Source Apache 2.0"

iadddocumentation -name Description  -text "SiFive coreip-s51-rtl module."

iadddocumentation -name Reference    -text "SiFive Freedom E SDK coreip-s51-rtl Board Support Package details."

iadddocumentation -name Limitations  -text "The IO peripherals are provided as register only models."

# Create local bus
ihwaddbus  -instancename bus -addresswidth 40

# Instance S51 Core Complex module
ihwaddmodule -instancename S51CC -vendor sifive.ovpworld.org -library module -type S51CC -version 1.0
ihwconnect -instancename S51CC -busport systemPort -bus bus

# Instance Memory region
ihwaddmemory  -instancename mem -type ram
ihwconnect    -instancename mem -busslaveport sp1 -bus bus  -loaddress 0x20000000 -hiaddress 0x23ffffff


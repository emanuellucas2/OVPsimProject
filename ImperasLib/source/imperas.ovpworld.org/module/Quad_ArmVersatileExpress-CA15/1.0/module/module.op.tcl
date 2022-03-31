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
This defines the hardware that includes four instantiations of the ARM Versatile Express development board with a CoreTile Express A15x2 (V2P-CA15) Daughterboard.
See the ARM documents DUI0447G_v2m_p1_trm.pdf and DUI0604E_v2p_ca15_tc1_trm.pdf for details of the hardware being modeled. 
Note this platform implements the motherboard's 'Cortex-A Series' memory map.

The default processor is an ARM Cortex-A15MPx2, which may be changed.
"

set limitations "
This platform provides the peripherals required to boot and run Operating Systems such as Linux or Android.
Some of the peripherals are register-only, non-functional models. See the individual peripheral model documentation for details.

CoreSight software debug and trace ports are not modeled.

Remap option not modeled.

The CLCD does not work in Linux
"

# Setup variables for platform info
set vendor  imperas.ovpworld.org
set library module
set name    Quad_ArmVersatileExpress-CA15
set version 1.0

#
# Start new platform creation
#
ihwnew -name $name -vendor $vendor -library $library -version $version -purpose module -releasestatus ovp 
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text $desc
iadddocumentation -name Limitations -text $limitations
iadddocumentation -name Reference   -text "ARM Development Boards Versatile Express BaseBoard and ARM CoreTile Express A15x2"

ihwaddmodule -instancename sys0 -vendor arm.ovpworld.org -library module -type ArmVersatileExpress-CA15 -version 1.0

ihwaddmodule -instancename sys1 -vendor arm.ovpworld.org -library module -type ArmVersatileExpress-CA15 -version 1.0

ihwaddmodule -instancename sys2 -vendor arm.ovpworld.org -library module -type ArmVersatileExpress-CA15 -version 1.0

ihwaddmodule -instancename sys3 -vendor arm.ovpworld.org -library module -type ArmVersatileExpress-CA15 -version 1.0

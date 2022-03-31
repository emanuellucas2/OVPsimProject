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
set vendor  imperas.ovpworld.org
set library module
set name    Dual_ARMv8-A-FMv1_VLAN
set version 1.0

#
# Start new platform creation 
#
ihwnew -name $name -vendor $vendor -library $library -version $version -stoponctrlc -purpose module -releasestatus ovp
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "This module implements a platform containing dual ARMv8-A-FMv1 modules connected using a Virtual LAN."
iadddocumentation -name Limitations -text "none known"
iadddocumentation -name Reference   -text "none"

# ethernet VLAN
ihwaddpacketnet -instancename phyEthernet

#
# ARMv8-A-FMv1 Instance 1
#
ihwaddmodule -instancename Sys1 -vendor arm.ovpworld.org -library module -type ARMv8-A-FMv1 -version 1.0
ihwconnect -instancename Sys1 -packetnetport phyEthernetPort -packetnet phyEthernet

#
# ARMv8-A-FMv1 Instance 2
#
ihwaddmodule -instancename Sys2 -vendor arm.ovpworld.org -library module -type ARMv8-A-FMv1 -version 1.0
ihwconnect -instancename Sys2 -packetnetport phyEthernetPort -packetnet phyEthernet

# Virtual Ethernet LAN to WLAN Bridge
ihwaddperipheral -instancename lanBridge -vendor ovpworld.org -library peripheral -type vEthernet_Bridge -version 1.0
ihwconnect -instancename lanBridge -packetnetport phyBridge  -packetnet phyEthernet

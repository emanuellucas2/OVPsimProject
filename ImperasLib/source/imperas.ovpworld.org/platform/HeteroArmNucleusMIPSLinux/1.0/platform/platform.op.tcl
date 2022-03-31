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

ihwnew -name HeteroArmNucleusMIPSLinux -vendor imperas.ovpworld.org -version 1.0 -library platform  -purpose fixed -releasestatus ovp

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

iadddocumentation -name Description -text "This heterogeneous platform combines MIPS Malta and ARM Integrator platforms."
iadddocumentation -name Description -text "MIPS Malta executes a Linux Kernel Operating System."
iadddocumentation -name Description -text "ARM Integrator executes the Nucleus Operating System."
iadddocumentation -name Limitations -text "Peripherals are modeled only to the extent required to boot and run Operating Systems."
iadddocumentation -name Reference   -text "OVP Heterogeneous platforms. MIPS Malta and ARM IntgratorCP reference guides."

set platform MipsMaltaLinux
set mSys mipsMain
source [file dirname [info script]]/MipsMaltaMulti.tcl

set aSys armSub1
source [file dirname [info script]]/ArmIntegratorMulti.tcl

#
# nets
#
ihwaddnet -instancename i8259Int
ihwaddnet -instancename armSub1irq
ihwaddnet -instancename armSub1fiq
ihwaddnet -instancename intCtl_ir14
ihwaddnet -instancename intCtl_ir15
ihwaddnet -instancename intCtl_ir10
ihwaddnet -instancename intCtl_ir1
ihwaddnet -instancename intCtl_ir3
ihwaddnet -instancename intCtl_ir4
ihwaddnet -instancename i8259Cascade
ihwaddnet -instancename intCtl_ir8
ihwaddnet -instancename intCtl_ir12
ihwaddnet -instancename armSub1ir1
ihwaddnet -instancename armSub1ir2
ihwaddnet -instancename armSub1ir3
ihwaddnet -instancename armSub1ir4
ihwaddnet -instancename armSub1ir5
ihwaddnet -instancename armSub1ir6
ihwaddnet -instancename armSub1ir7
ihwaddnet -instancename armSub1ir8
ihwaddnet -instancename armSub1ir23
ihwaddnet -instancename armSub1ir24

#
# shared bus
#
ihwaddbus -instancename busShared -addresswidth 32
#
# Shared memory
#
ihwaddmemory -instancename sharedRAM  -type ram
ihwconnect -bus busShared -instancename sharedRAM -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0x0000ffff

#
# Bridge 
#
ihwaddbridge -instancename busBridgeM1
ihwconnect -bus busmipsMain -instancename busBridgeM1 -busslaveport  sp1 -loaddress  0x08000000 -hiaddress 0x0800ffff
ihwconnect -bus busShared  -instancename busBridgeM1 -busmasterport mp1 -loaddress  0x00000000 -hiaddress 0x0000ffff

ihwaddbridge -instancename busBridgeA1
ihwconnect -bus busarmSub1 -instancename busBridgeA1 -busslaveport  sp1 -loaddress  0x0a000000 -hiaddress 0x0a00ffff 
ihwconnect -bus busShared  -instancename busBridgeA1 -busmasterport mp1 -loaddress  0x00000000 -hiaddress 0x0000ffff

############################## Command Line Parser ##################################################

ihwaddclp -allargs 
ihwaddclparg -name uartconsole -type boolvar   -group "user platform config" -description "open a console terminal on the ARM IntegratorCP UART"
ihwaddclparg -name uartport    -type uns32var  -group "user platform config" -description "set the base port number to open on the ARM IntegratorCP UART"
ihwaddclparg -name nographics  -type boolvar   -group "user platform config" -description "disable the MIPS Malta graphics window"

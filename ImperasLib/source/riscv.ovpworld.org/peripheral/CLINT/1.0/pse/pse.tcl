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

set vendor  riscv.ovpworld.org
set library peripheral
set name    CLINT
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version \
                    -constructor constructor \
                    -releasestatus ovp \
                    -netportuserfunction nextNetPortUser -nbyteregisters

set defaultHarts 1
set defaultMHz 10.0

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "SiFive-compatabile Risc-V Core Local Interruptor (CLINT)."
iadddocumentation -name Description -text "Use the num_harts parameter to specify the number of harts suported (default ${defaultHarts})."
iadddocumentation -name Description -text "For each supported hart there will be an MTimerInterruptN and MSWInterruptN net port, plus msipN and mtimecmpN registers implemented, where N is a value from 0..num_harts-1."
iadddocumentation -name Description -text "There is also a single mtime register."

iadddocumentation -name Reference   -text "Various SiFive Core Complex manuals, e.g. SiFive U54 Core Complex Manual (https://sifive.cdn.prismic.io/sifive/a07d1a9a-2cb8-4cf5-bb75-5351888ea2e1_u54_core_complex_manual_21G2.pdf)"

imodeladdformal   -name num_harts -type Uns32 -defaultvalue ${defaultHarts} -min 1 -max 4095
iadddocumentation -name num_harts -text "Number of harts implemented"

imodeladdformal   -name clockMHz -type double -defaultvalue ${defaultMHz} -min 0.001 -max 1000.0
iadddocumentation -name clockMHz -text "Clock rate in MHz used in timer calculations (default ${defaultMHz}"

#
# Net ports (Only port 0 is defined here - ports 1 thru numharts-1 are instantiated in the constructor)
#
imodeladdnetport -name MSWInterrupt0    -type output
imodeladdnetport -name MTimerInterrupt0 -type output

imodeladdnetport -name reset -type input -updatefunction resetCB
iadddocumentation -name Description -text "Reset signal"

#
# Slave ports
#
imodeladdbusslaveport -name port0 -size 0xC000 -defaultfunctions

#
# msip address block
#
imodeladdaddressblock -name msip -port port0 -size 0x4000 -offset 0x0 -width 32

# msip0 register (Only register 0 is defined here - registers 1 thru numharts-1 are instantiated in the constructor)
imodeladdmmregister   -name msip0 -addressblock port0/msip -offset 0x0 -width 32 -access rw -writemask 0x1 -nonvolatile \
                      -readfunction msipRead -writefunction msipWrite -viewfunction msipView -userdata 0
  iadddocumentation   -name msip0 -text "Hart 0 Machine-Mode Software Interrupt"

#
# mtime address block
#
imodeladdaddressblock -name mtime -port port0 -size 0x8000 -offset 0x4000 -width 64

# mtimecmp0 register (Only register 0 is defined here - registers 1 thru numharts-1 are instantiated in the constructor)
imodeladdmmregister   -name mtimecmp0 -addressblock port0/mtime -offset 0x0 -width 64 -access rw \
                      -readfunction mtimecmpRead -writefunction mtimecmpWrite -viewfunction mtimecmpView -userdata 0
  iadddocumentation   -name mtimecmp0 -text "Hart 0 Machine-Mode Timer Compare"
  
imodeladdmmregister   -name mtime     -addressblock port0/mtime -offset 0x7ff8 -width 64 -access rw \
                      -readfunction mtimeRead -writefunction mtimeWrite   -viewfunction mtimeView
  iadddocumentation   -name mtime -text "Machine-Mode mtime"

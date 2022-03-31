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

set vendor  altera.ovpworld.org
set library peripheral
set name    PerformanceCounterCore
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version -constructor constructor

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "Altera Avalon Performance Counter Core"
iadddocumentation -name Limitations -text "No Support for pin level transitions"
iadddocumentation -name Reference   -text "Embedded Peripherals IP User Guide, UG-01085-11.0 11.0 June 2011"

imodeladdformal -name Counters      -type uns64

#
# Slave port
#
imodeladdbusslaveport -name sp1 -size 128

#
# Registers
#
imodeladdaddressblock -name reg0 -port sp1 -offset 0 -size 128 -width 32

#
# Registers
#
for {set i 0} {$i < 6} {incr i} {
    set off [expr $i * 12]
    imodeladdmmregister -addressblock sp1/reg0 -name t${i}lo -width 32 -offset [expr $off + 0] -access rw -writefunction write_lo -readfunction read_lo -userdata ${i}
    imodeladdmmregister -addressblock sp1/reg0 -name t${i}hi -width 32 -offset [expr $off + 4] -access rw -writefunction write_hi -readfunction read_hi -userdata ${i}
    imodeladdmmregister -addressblock sp1/reg0 -name t${i}ev -width 32 -offset [expr $off + 8] -access rw -writefunction write_ev -readfunction read_ev -userdata ${i}
    
    #
    # Resets
    #
    imodeladdreset -mmregister sp1/reg0/t${i}lo -name IRESET -value 0x00000000
    imodeladdreset -mmregister sp1/reg0/t${i}hi -name IRESET -value 0x00000000
    imodeladdreset -mmregister sp1/reg0/t${i}ev -name IRESET -value 0x00000000
}

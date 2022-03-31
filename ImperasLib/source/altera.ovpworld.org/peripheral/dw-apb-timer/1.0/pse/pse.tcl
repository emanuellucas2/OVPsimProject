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
set name    dw-apb-timer
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor \
    -releasestatus ovp

iadddocumentation -name Description -text "Model of dw-apb-timer for CycloneV platform."
              
iadddocumentation -name Limitations -text "Only functionality required for Altera Cyclone-V is implemented: single timer, 32 bits, little endian only" 
iadddocumentation -name Limitations -text "Resolution of this timer is limited to the simulation time slice (aka quantum) size"      

iadddocumentation -name Reference   -text "Cyclone V Device Handbook Volume 3: Hard Processor System Technical Reference Manual cv_5v4 2013.12.30"

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

set defaultFrequency 200
imodeladdformal   -name frequency   -type uns32 -defaultvalue ${defaultFrequency}
iadddocumentation -name Description -text "Specify frequency of the counters in MHz (default is ${defaultFrequency}MHz)"

imodeladdbusslaveport  -name bport1 -mustbeconnected -size 0x1000
imodeladdaddressblock  -name timer1 -port bport1 -size 0x14 -offset 0    -width 32
imodeladdaddressblock  -name timers -port bport1 -size 0x10 -offset 0xa0 -width 32

#
# Interrupt Signal Block output
#
imodeladdnetport -name irq -type output

set registers {
  loadcount   timer1 0x00 rw  0x00000000  -    auto
  currentval  timer1 0x04 r   0x00000000  auto -   
  controlreg  timer1 0x08 rw  0x00000000  -    auto  
  eoi         timer1 0x0c r   0x00000000  auto -   
  intstat     timer1 0x10 r   0x00000000  auto -   
  intstat     timers 0x00 r   -           auto -   
  eoi         timers 0x04 r   -           auto -   
  rawintstat  timers 0x08 r   -           auto -   
  compversion timers 0x0c r   0x3230352a  -    -   
}

foreach {rname bname roffset raccess reset readFunc writeFunc} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}

  set command "imodeladdmmregister -addressblock bport1/${bname} -name $rname -width 32 -offset $roffset -access $raccess"
  if { $readFunc == "-" } {
    set defaultcb 1
  } elseif { $readFunc == "auto" } {
    set command "${command} -readfunction Read${rname}"
  } else {
    set command "${command} -readfunction $readFunc"
  }
  
  if { $writeFunc == "-" } {
    set defaultcb 1
  } elseif { $writeFunc == "auto" } {
    set command "${command} -writefunction Write${rname}"
  } else {
    set command "${command} -writefunction $writeFunc"
  }
  
  eval $command

  if { $reset != "-" } {
  	imodeladdreset -mmregister bport1/${bname}/$rname -name resetNet -value $reset
  }
  
}

#
# timer1controlreg
#
imodeladdfield -mmregister bport1/timer1/controlreg -name enable         -bitoffset  0 -width 1
imodeladdfield -mmregister bport1/timer1/controlreg -name mode           -bitoffset  1 -width 1
imodeladdfield -mmregister bport1/timer1/controlreg -name interrupt_mask -bitoffset  2 -width 1

#
# timer1eoi
#
imodeladdfield -mmregister bport1/timer1/eoi -name eoi -bitoffset  0 -width 1

#
# timer1intstat
#
imodeladdfield -mmregister bport1/timer1/intstat -name intstat -bitoffset  0 -width 1

#
# timersintstat
#
imodeladdfield -mmregister bport1/timers/intstat -name intstat -bitoffset  0 -width 1

#
# timerseoi
#
imodeladdfield -mmregister bport1/timers/eoi -name eoi -bitoffset  0 -width 1

#
# timersrawintstat
#
imodeladdfield -mmregister bport1/timers/rawintstat -name intstat -bitoffset  0 -width 1
 

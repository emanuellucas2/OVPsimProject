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
set name    RSTMGR
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor \
    -releasestatus ovp

iadddocumentation -name Description -text "Altera Cyclone V Reset Manager"
              
iadddocumentation -name Limitations -text "Only register mpumodrst cpu0 and cpu1 reset functionality is implemented"

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

iadddocumentation -name Reference   -text "Cyclone V Device Handbook Volume 3: Hard Processor System Technical Reference Manual cv_5v4 2013.12.30"

imodeladdbusslaveport  -name bport1 -mustbeconnected -size 0x1000
imodeladdaddressblock  -name REGS -port bport1 -size 0x24 -offset 0    -width 32

#
# CPU resets
#
imodeladdnetport -name cpu0Reset -type output
imodeladdnetport -name cpu1Reset -type output

set registers {
  stat        REGS 0x00 rw    0x00000000  -    -
  ctrl        REGS 0x04 rw    0x00100000  -    -
  counts      REGS 0x08 rw    0x00080080  -    -
  mpumodrst   REGS 0x10 rw    0x00000002  -    auto
  permodrst   REGS 0x14 rw    0x3fffffff  -    -
  per2modrst  REGS 0x18 rw    0x000000ff  -    -
  brgmodrst   REGS 0x1c rw    0x00000007  -    -
  miscmodrst  REGS 0x20 rw    0x00000000  -    - 
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
# mpumodrst bit fields
#
imodeladdfield -mmregister bport1/REGS/mpumodrst -name cpu0         -bitoffset  0 -width 1
imodeladdfield -mmregister bport1/REGS/mpumodrst -name cpu1         -bitoffset  1 -width 1




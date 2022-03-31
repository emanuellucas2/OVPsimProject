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

set vendor  safepower.ovpworld.org
set library peripheral
set name    ring_oscillator
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor 

iadddocumentation  \
    -name Description  \
    -text "Ring Oscillator"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "This model is a register only model that returns the COUNT value from a memory location."

# default count value and its actual temperature
set countValue       2097152
set countValueTemp   25

iadddocumentation  \
    -name Limitations  \
    -text "No behavior is currently included in the model, the COUNT register value is provided by a memory location, initialized to ($countValue = ${countValueTemp}oC)."

iadddocumentation \
    -name Reference  \
    -text "Ikerlan"

imodeladdformal -name countinit -type uns32 -defaultvalue $countValue
iadddocumentation  \
    -name Description  \
    -text "Modify the Ring Oscillator count register initialization (default $countValue = ${countValueTemp}oC)"
    
imodeladdbusmasterport -name rocount -addresswidth 2
iadddocumentation  \
    -name Description  \
    -text "Master connection to memory holding count value (allows external update)"
    
set PORT    bport1
set AB      REG
set AB_SIZE 0x1000

imodeladdbusslaveport  -name $PORT -mustbeconnected -size $AB_SIZE
imodeladdaddressblock  -name $AB -port $PORT -size $AB_SIZE -offset 0 -width 32

imodeladdlocalmemory -name buffer0 -addressblock $PORT/$AB -size $AB_SIZE -offset 0 \
                     -writefunction regNoDefinitionWrite -readfunction regNoDefinitionRead

# add default value variables into list
set registers "
    COUNT         0x00000000 32 r  ${countValue} - auto -    -                    \"Count Value (default ${countValue} = ${countValueTemp}oC)\"
    INIT_TIME     0x00000004 32 rw 0x00000000    - auto auto {INIT 8 24 CTRL 0 8} \"Init Time and Control\"
    CAPTURE_TIME  0x00000008 32 rw 0x0010ff00    - auto auto -                    \"Capture Time\"
"

foreach {rname roffset rsize raccess reset mask readFunc writeFunc bits description} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}
  if {$rsize != "32"} {
      set rsize 32
#      puts "Register $rname is not 32-bits ignored"
#      continue
  }

  set command "imodeladdmmregister -addressblock ${PORT}/${AB} -name $rname -width 32 -offset $roffset -access $raccess"
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

  if { $mask != "-" } {
    set command "${command} -writemask $mask"
  }

  eval $command
  
  if { $description != "-" } {
      iadddocumentation  -handle ${PORT}/${AB}/$rname \
                         -name Description  \
                         -text $description
  }

  if { $bits != "-" } {
    foreach { n o w } $bits {
        imodeladdfield -mmregister ${PORT}/${AB}/$rname -bitoffset $o -width $w -name $n
    }
  }
  
  imodeladdreset -mmregister ${PORT}/${AB}/$rname -name resetNet -value $reset
}

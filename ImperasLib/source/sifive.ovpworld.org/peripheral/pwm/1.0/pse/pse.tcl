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

set vendor  sifive.ovpworld.org
set library peripheral
set name    pwm
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor 

iadddocumentation -name Description -text "SiFive coreip-s51-arty PWM Registers (pwm)"

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

iadddocumentation -name Limitations -text "This model implements only the registers and contains no behaviour."

iadddocumentation -name Reference   -text "SiFive Freedom E SDK coreip-s51-arty Board Support Package details."

set PORT    bport1
set AB      REG
set AB_SIZE 0x1000
set width   32

imodeladdbusslaveport  -name $PORT -mustbeconnected -size $AB_SIZE -defaultfunctions
imodeladdaddressblock  -name $AB -port $PORT -size $AB_SIZE -offset 0 -width ${width}

#   name       offset size access reset       readFunc writeFunc  writeMask  description bits
set registers {
     pwmcfg    0x00   32   rw     0x00000000  -        wrCfg      0xff0ff70f "PWM Configuration Register"     
     {
        pwmscale       0 4 "PWM Counter scale"
        pwmsticky      8 1 "PWM Sticky - disallow clearing pwmcmpXip bits"
        pwmzerocmp     9 1 "PWM Zero - counter resets to zero after match"
        pwmdeglitch   10 1 "PWM Deglitch - latch pwmcmpXip within same cycle"
        pwmenalways   12 1 "PWM enable always - run continuously"
        pwmenoneshot  13 1 "PWM enable one shot - run one cycle"
        pwmcmp0center 16 1 "PWM0 Compare Center"
        pwmcmp1center 17 1 "PWM1 Compare Center"
        pwmcmp2center 18 1 "PWM2 Compare Center"
        pwmcmp3center 19 1 "PWM3 Compare Center"
        pwmcmp0gang   24 1 "PWM0/PWM1 Compare Gang"
        pwmcmp1gang   25 1 "PWM1/PWM2 Compare Gang"
        pwmcmp2gang   26 1 "PWM2/PWM3 Compare Gang"
        pwmcmp3gang   27 1 "PWM3/PWM0 Compare Gang"
        pwmcmp0ip     28 1 "PWM0 Interrupt Pending"
        pwmcmp1ip     29 1 "PWM1 Interrupt Pending"
        pwmcmp2ip     30 1 "PWM2 Interrupt Pending"
        pwmcmp3ip     31 1 "PWM3 Interrupt Pending"
     } 
     pwmcount  0x08   32   rw     0x00000000  rdCnt    wrCnt      -          ""     -
     pwms      0x10   32   rw     0x00000000  rdPwms   wrPwms     -          ""     -
     pwmcmp0   0x20   32   rw     0x00000000  -        wrCmp      0x0000ffff "PWM Compare Register"     
     {
         cmp 0 16 "PWM 0 Compare Value"        
     }
     pwmcmp1   0x24   32   rw     0x00000000  -        wrCmp      0x0000ffff "PWM Compare Register"     
     {
         cmp 0 16 "PWM 1 Compare Value"        
     }
     pwmcmp2   0x28   32   rw     0x00000000  -        wrCmp      0x0000ffff "PWM Compare Register"     
         {
             cmp 0 16 "PWM 2 Compare Value"        
         }
     pwmcmp3   0x2C   32   rw     0x00000000  -        wrCmp      0x0000ffff "PWM Compare Register"     
         {
             cmp 0 16 "PWM 3 Compare Value"        
         }
}

foreach {rname roffset rsize raccess reset readFunc writeFunc writeMask description bits} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}
  if {$rsize != "${width}"} {
      set rsize ${width}
  }

  #  puts "# $rname $roffset $rsize $raccess $reset $readFunc $writeFunc $writeMask $description $bits"
    
  set command "imodeladdmmregister -addressblock $PORT/$AB -name $rname -width ${width} -offset $roffset -access $raccess"
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

  if { $writeMask == "-" } {
    set defaultcb 1
  } else {
    set command "${command} -writemask $writeMask"
  }
  
  eval $command
  
  if { $description != "-" } {
      iadddocumentation  -handle $PORT/$AB/$rname \
                         -name Description  \
                         -text $description
  }

  if { $bits != "-" } {
    foreach { n o w d } $bits {
      imodeladdfield -mmregister $PORT/$AB/$rname -bitoffset $o -width $w -name $n
      if { $d != "-" } {
          iadddocumentation  -handle $PORT/$AB/$rname \
                             -name Description  \
                             -text $d
      }
    }
  }
  
  imodeladdreset -mmregister $PORT/$AB/$rname -name resetNet -value $reset
}

# reset input
imodeladdnetport -type input -name resetNet -updatefunction resetCB

# interrupt outputs
imodeladdnetport -type output -name int0 
imodeladdnetport -type output -name int1
imodeladdnetport -type output -name int2
imodeladdnetport -type output -name int3 

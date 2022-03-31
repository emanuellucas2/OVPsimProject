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

set vendor  nxp.ovpworld.org
set library peripheral
set name    iMX6_GPT
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor

iadddocumentation -name Description -text "NXP i.MX6 GPT General Purpose Timer"

iadddocumentation -name Licensing -text "Open Source Apache 2.0"

iadddocumentation -name Limitations \
                  -text "Resolution of this timer is limited to the simulation time slice (aka quantum) size"

iadddocumentation -name Reference \
    -text "i.MX 6Solo/6DualLite Applications Processor Reference Manual (IMX6SDLRM_Ref_Manual.pdf"

#
# slave port
#
set port  bport1
set block ab
set size  0x1000

imodeladdbusslaveport  -name ${port} -mustbeconnected -size ${size}
imodeladdaddressblock  -name ${block} -port ${port} -size ${size} -offset 0 -width 32

# define a general function if an access to an area in which there is no register defined
imodeladdlocalmemory -name buffer -addressblock ${port}/${block} -size ${size} \
                     -writefunction regNoDefinitionWrite -readfunction regNoDefinitionRead

#
# Registers
#
set registers {
  GPT_CR    0x00 rw  0x00000000 0xffff87ff  -    auto "GPT Control Register"
        {   FO3    31 1 "Force Output Compare Channel 3"
            FO2    30 1 "Force Output Compare Channel 2"
            FO1    29 1 "Force Output Compare Channel 1"
            OM3    26 3 "Output Compare Channel 3 operating mode"
            OM2    23 3 "Output Compare Channel 2 operating mode"
            OM1    20 3 "Output Compare Channel 1 operating mode"
            IM2    18 2 "Input Capture Channel 2 operating mode"
            IM1    16 2 "Input Capture Channel 1 operating mode"
            SWR    15 1 "Software reset."
            EN_24M 10 1 "Enable 24 MHz clock input from crystal"
            FRR     9 1 "Free-Run or Restart mode."
            CLKSRC  6 3 "Clock Source select"
            STOPEN  5 1 "GPT Stop Mode enable"
            DOZEEN  4 1 "GPT Doze Mode Enable"
            QAITEN  3 1 "GPT Wait Mode enable."
            DBGEN   2 1 "GPT debug mode enable"
            ENMOD   1 1 "GPT Enable mode"
            EN      0 1 "GPT Enable"
        } 
  GPT_PR    0x04 rw  0x00000000 0x0000ffff  -    auto "GPT Prescaler Register"
        {   PRESCALER24M 12  4 "24M crystal clock Prescaler bits"
            PRESCALER     0 12 "CLKSRC Prescaler bits"
        } 
  GPT_SR    0x08 rw  0x00000000 0x0000003f  -    auto "GPT Status Register"
        {   ROV 5 1 "Rollover Flag."
            IF2 4 1 "IF2 Input capture 2 Flag"
            IF1 3 1 "IF1 Input capture 1 Flag"
            OF3 2 1 "OF3 Output Compare 3 Flag"
            OF2 1 1 "OF2 Output Compare 2 Flag"
            OF1 0 1 "OF1 Output Compare 1 Flag"
        } 
  GPT_IR    0x0c rw  0x00000000 0x0000003f  -    auto "GPT Interrupt Register"
        {   ROVIE 5 1 "Rollover Interrupt Enable"
            IF2IE 4 1 "Input capture 2 Interrupt Enable"
            IF1IE 3 1 "Input capture 1 Interrupt Enable"
            OF3IE 2 1 "Output Compare 3 Interrupt Enable"
            OF2IE 1 1 "Output Compare 2 Interrupt Enable"
            OF1IE 0 1 "Output Compare 1 Interrupt Enable"
        } 
  GPT_OCR1  0x10 rw  0xffffffff -           -    auto "GPT Output Compare Register 1" -
  GPT_OCR2  0x14 rw  0xffffffff -           -    auto "GPT Output Compare Register 2" -
  GPT_OCR3  0x18 rw  0xffffffff -           -    auto "GPT Output Compare Register 3" -
  GPT_ICR1  0x1c r   0x00000000 -           -    -    "GPT Input Capture Register 1"  -
  GPT_ICR2  0x20 r   0x00000000 -           -    -    "GPT Input Capture Register 2"  -
  GPT_CNT   0x24 r   0x00000000 -           auto -    "GPT Counter Register"          -
}

foreach {rname roffset raccess reset writeMask readFunc writeFunc description bits} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}

  set command "imodeladdmmregister -addressblock $port/$block -name $rname -width 32 -offset $roffset -access $raccess"
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

  if { $writeMask != "-" } {
    set command "${command} -writemask $writeMask"
  }

  eval $command
  
  if { $description != "-" } {
      iadddocumentation  -handle ${port}/${block}/$rname \
                         -name Description  \
                         -text $description
  }

  if { $bits != "-" } {
    foreach { n o w d } $bits {
        imodeladdfield -mmregister $port/$block/$rname -bitoffset $o -width $w -name $n
        if { $d != "-" } {
            iadddocumentation  -handle ${port}/${block}/$rname -name Description -text $d
        }
    }
  }

  imodeladdreset -mmregister $port/$block/$rname -name resetNet -value $reset
}

#
# net ports
#
imodeladdnetport  -name interrupt -type output
iadddocumentation -name Description  -text "Interrupt Output"

imodeladdnetport  -name capture1 -type input -updatefunction inputCapure -updatefunctionargument 1
iadddocumentation -name Description  -text "Input Capture 1"
imodeladdnetport  -name capture2 -type input -updatefunction inputCapure -updatefunctionargument 2
iadddocumentation -name Description  -text "Input Capture 2"

# default clk (Hz)
set pclk 66000000
imodeladdformal   -name clk -type uns32 -defaultvalue ${pclk}
iadddocumentation -name Description   -text "Clock frequency Hz (default ${pclk}Hz)"

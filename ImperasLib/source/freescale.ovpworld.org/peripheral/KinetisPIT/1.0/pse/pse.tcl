#
# Copyright (c) 2011-2016 Posedge Software, Inc., www.posedgesoft.com
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


set vendor  freescale.ovpworld.org
set library peripheral
set name    KinetisPIT
set version 1.0
set desc "Model of the PIT peripheral used on the Freescale Kinetis platform"
set limitations "Provides the base behaviour for the OVP Freescale Kinetis platforms"


imodelnewperipheral           \
    -imagefile   pse.pse      \
    -name        $name        \
    -vendor      $vendor      \
    -library     $library     \
    -version     $version     \
    -constructor constructor  \
    -releasestatus ovp        \
    -nbyteregisters

iadddocumentation -name Description -text $desc
iadddocumentation -name Limitations -text $limitations
iadddocumentation -name Reference -text "www.freescale.com/Kinetis"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

imodeladdnetport -name Reset     -type input

imodeladdnetport -name irq%u -type output  -loarray 0  -hiarray 3
  iadddocumentation -name Description -text "IRQ port"
    
imodeladdnetport -name trg%u -type output  -loarray 0  -hiarray 3
  iadddocumentation -name Description -text "Trigger port"

# Core Clock = 100 MIPS (default) / 1.25 MIPS/MHz (ARM Cortex-M4F) = 80 MHz
# assume Bus Clock = Core Clock;  usually true after reset
set DEFAULT_FREQ_MHZ 80
imodeladdformal  -name frequency -type uns64 -defaultvalue ${DEFAULT_FREQ_MHZ}
iadddocumentation -name Description -text "Frequency of the clock input in MHz (default is ${DEFAULT_FREQ_MHZ}MHz)"

imodeladdbusslaveport -name bport1 -size 0x1000
imodeladdaddressblock -name ab     -offset     0  -size 0x100  -width 32

  imodeladdmmregister -name MCR  -offset 0 -access rw -writefunction writeMCR -writemask 0x00000003
    imodeladdreset -name Reset -value 0x00000002
    imodeladdfield -name FRZ  -bitoffset 0  -width 1
    imodeladdfield -name MDIS -bitoffset 1  -width 1  

imodeladdaddressblock -name ab2    -offset 0x100  -size 0x10  -width 32  -loarray 0 -hiarray 3

    imodeladdmmregister -name LDVAL  -offset 0x00 -access rw
      iadddocumentation -name Description -text  "Timer Load Value Register"
      imodeladdreset -name Reset -value 0x00000000
      imodeladdfield -name TSV -bitoffset 0  -width 32   

    imodeladdmmregister -name CVAL   -offset 0x04 -access rw -readfunction readCVAL -viewfunction viewCVAL
      iadddocumentation -name Description -text  "Current Timer Value Register"
      imodeladdreset -name Reset -value 0x00000000
      imodeladdfield -name TVL -bitoffset 0  -width 32    

    imodeladdmmregister -name TCTRL   -offset 0x08 -access rw -writefunction writeTCTRL -writemask 0x00000003
      iadddocumentation -name Description -text  "Timer Control Register"
      imodeladdreset -name Reset -value 0x00000000
      imodeladdfield -name TEN -bitoffset 0  -width 1
      imodeladdfield -name TIE -bitoffset 1  -width 1    

    imodeladdmmregister -name TFLG   -offset 0x0c -access rw -writefunction writeTFLG -writemask 0x00000001
      iadddocumentation -name Description -text  "Timer Flag Register"
      imodeladdreset -name Reset -value 0x00000000
      imodeladdfield -name TIF -bitoffset 0  -width 1 


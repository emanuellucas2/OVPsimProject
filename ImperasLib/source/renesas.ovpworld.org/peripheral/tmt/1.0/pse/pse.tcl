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

set vendor  renesas.ovpworld.org
set library peripheral
set name    tmt
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version -constructor constructor

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "Renesas TMT Timer/Event Counter T"
iadddocumentation -name Limitations -text "Status of Modes
- Interval Timer Mode                  - Supported
- External Event Count Mode            - Unsupported
- External Trigger Pulse Output Mode   - Unsupported
- One-Shot Pulse Mode                  - Unsupported
- PWM Mode                             - Unsupported
- Free-Running Mode                    - Supported
- Pulse Width Measurement Mode         - Unsupported
- Triangular Wave PWM Mode             - Unsupported
- Encoder Compare Mode                 - Unsupported
- Encoder Capture Mode                 - Unsupported
- Encoder Capture Compare Mode         - Unsupported
- Offset Trigger Generation Mode       - Unsupported
"
iadddocumentation -name Reference   -text "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010"

#
# PCLKx formal container
#
foreach i {0 1 2 3 4 5 7 9} {
    imodeladdformal -name PCLK${i} -type uns32
}

#
# Signal outputs
#
for {set i 0} {$i <= 1} {incr i} {
    imodeladdnetport -name TOT${i} -type output
}
foreach output {TO0 T01 ICC0 ICC1 EQC0 EQC1} {
    imodeladdnetport -name TTT${output} -type output
}
foreach interrupt {CC0 CC1 OV EC} {
    imodeladdnetport -name INTTT${interrupt} -type output
}

#
# Signal inputs
#
foreach input {TIT0 TIT1 TEVTT TTRGT TENCT0 TENCT1 TECRT} {
    imodeladdnetport -name ${input} -type input -updatefunction P_${input}
}
foreach input {TI0 TI1 ENC0 ENC1 TRG EVT ECR} {
    imodeladdnetport -name TTT${input} -type input -updatefunction P_TTT${input}
}

#
# Slave port
#
imodeladdbusslaveport -name TMTP0 -size 16
imodeladdbusslaveport -name TMTP1 -size 2

#
# Registers
#
imodeladdaddressblock -name reg0 -port TMTP0 -size 10 -offset  0 -width  8
imodeladdaddressblock -name reg1 -port TMTP0 -size  6 -offset 10 -width 16
imodeladdaddressblock -name reg0 -port TMTP1 -size  2 -offset  0 -width 16

#
# TMTP0
#
imodeladdmmregister -addressblock TMTP0/reg0 -name CTL0 -width 8  -offset 0 -access rw -writefunction writeCTL0 -writemask 0x87
imodeladdmmregister -addressblock TMTP0/reg0 -name CTL1 -width 8  -offset 1 -access rw -writefunction writeCTL1 -writemask 0x6f
imodeladdmmregister -addressblock TMTP0/reg0 -name CTL2 -width 8  -offset 2 -access rw -writefunction writeCTL2 -writemask 0x9f
imodeladdmmregister -addressblock TMTP0/reg0 -name IOC0 -width 8  -offset 3 -access rw -writefunction writeIOC0 -writemask 0x0f
imodeladdmmregister -addressblock TMTP0/reg0 -name IOC1 -width 8  -offset 4 -access rw -writefunction writeIOC1 -writemask 0x0f
imodeladdmmregister -addressblock TMTP0/reg0 -name IOC2 -width 8  -offset 5 -access rw -writefunction writeIOC2 -writemask 0x0f
imodeladdmmregister -addressblock TMTP0/reg0 -name IOC3 -width 8  -offset 6 -access rw -writefunction writeIOC3 -writemask 0xff
imodeladdmmregister -addressblock TMTP0/reg0 -name OPT0 -width 8  -offset 7 -access rw -writefunction writeOPT0 -writemask 0x31
imodeladdmmregister -addressblock TMTP0/reg0 -name OPT1 -width 8  -offset 8 -access rw -writefunction writeOPT1 -writemask 0x07
imodeladdmmregister -addressblock TMTP0/reg0 -name OPT2 -width 8  -offset 9 -access rw -writefunction writeOPT2 -writemask 0x01

imodeladdmmregister -addressblock TMTP0/reg1 -name CCR0 -width 16 -offset 0 -access rw -writefunction writeCCR0 -writemask 0xffff
imodeladdmmregister -addressblock TMTP0/reg1 -name CCR1 -width 16 -offset 2 -access rw -writefunction writeCCR1 -writemask 0xffff
imodeladdmmregister -addressblock TMTP0/reg1 -name CNT  -width 16 -offset 4 -access r  -readfunction  readCNT

#
# TMTP1
#
imodeladdmmregister -addressblock TMTP1/reg0 -name TCW -width 16  -offset 0 -access rw -writefunction writeTCW -writemask 0xffff

#
# Resets
#
imodeladdreset -mmregister TMTP0/reg0/CTL0 -name IRESET -value 0x00
imodeladdreset -mmregister TMTP0/reg0/CTL1 -name IRESET -value 0x00
imodeladdreset -mmregister TMTP0/reg0/CTL2 -name IRESET -value 0x00
imodeladdreset -mmregister TMTP0/reg0/IOC0 -name IRESET -value 0x00
imodeladdreset -mmregister TMTP0/reg0/IOC1 -name IRESET -value 0x00
imodeladdreset -mmregister TMTP0/reg0/IOC2 -name IRESET -value 0x00
imodeladdreset -mmregister TMTP0/reg0/IOC3 -name IRESET -value 0x00
imodeladdreset -mmregister TMTP0/reg0/OPT0 -name IRESET -value 0x00
imodeladdreset -mmregister TMTP0/reg0/OPT1 -name IRESET -value 0x00
imodeladdreset -mmregister TMTP0/reg0/OPT2 -name IRESET -value 0x00
imodeladdreset -mmregister TMTP0/reg1/CCR0 -name IRESET -value 0x0000
imodeladdreset -mmregister TMTP0/reg1/CCR1 -name IRESET -value 0x0000
imodeladdreset -mmregister TMTP0/reg1/CNT  -name IRESET -value 0x0000
imodeladdreset -mmregister TMTP1/reg0/TCW  -name IRESET -value 0x00

#
# Bit Fields
#
imodeladdfield -mmregister TMTP0/reg0/CTL0 -name CKS -bitoffset 0 -width 3
imodeladdfield -mmregister TMTP0/reg0/CTL0 -name CE  -bitoffset 7 -width 1

imodeladdfield -mmregister TMTP0/reg0/CTL1 -name MD  -bitoffset 0 -width 4
imodeladdfield -mmregister TMTP0/reg0/CTL1 -name EEE -bitoffset 5 -width 1
imodeladdfield -mmregister TMTP0/reg0/CTL1 -name EST -bitoffset 6 -width 1

imodeladdfield -mmregister TMTP0/reg0/CTL2 -name UDS -bitoffset 0 -width 2
imodeladdfield -mmregister TMTP0/reg0/CTL2 -name ECM -bitoffset 2 -width 2
imodeladdfield -mmregister TMTP0/reg0/CTL2 -name LDE -bitoffset 4 -width 1
imodeladdfield -mmregister TMTP0/reg0/CTL2 -name ECC -bitoffset 7 -width 1

imodeladdfield -mmregister TMTP0/reg0/IOC0 -name OE0 -bitoffset  0 -width 1
imodeladdfield -mmregister TMTP0/reg0/IOC0 -name OL0 -bitoffset  1 -width 1
imodeladdfield -mmregister TMTP0/reg0/IOC0 -name OE1 -bitoffset  2 -width 1
imodeladdfield -mmregister TMTP0/reg0/IOC0 -name OL1 -bitoffset  3 -width 1

imodeladdfield -mmregister TMTP0/reg0/IOC1 -name IS  -bitoffset  0 -width 4

imodeladdfield -mmregister TMTP0/reg0/IOC2 -name ETS -bitoffset  0 -width 2
imodeladdfield -mmregister TMTP0/reg0/IOC2 -name EES -bitoffset  2 -width 2

imodeladdfield -mmregister TMTP0/reg0/IOC3 -name EIS -bitoffset  0 -width 2
imodeladdfield -mmregister TMTP0/reg0/IOC3 -name ECS -bitoffset  2 -width 2
imodeladdfield -mmregister TMTP0/reg0/IOC3 -name ACL -bitoffset  4 -width 1
imodeladdfield -mmregister TMTP0/reg0/IOC3 -name BCL -bitoffset  5 -width 1
imodeladdfield -mmregister TMTP0/reg0/IOC3 -name ZCL -bitoffset  6 -width 1
imodeladdfield -mmregister TMTP0/reg0/IOC3 -name SCE -bitoffset  7 -width 1

imodeladdfield -mmregister TMTP0/reg0/OPT0 -name OVF -bitoffset  0 -width 1
imodeladdfield -mmregister TMTP0/reg0/OPT0 -name CCS -bitoffset  4 -width 2

imodeladdfield -mmregister TMTP0/reg0/OPT1 -name ESF -bitoffset  0 -width 1
imodeladdfield -mmregister TMTP0/reg0/OPT1 -name EOF -bitoffset  1 -width 1
imodeladdfield -mmregister TMTP0/reg0/OPT1 -name EUF -bitoffset  2 -width 1

imodeladdfield -mmregister TMTP0/reg0/OPT2 -name RSF -bitoffset  0 -width 1

#
# Enables the generation of a function to be intercepted by a plant model
# This is used to indicate a change in the PWM rate
#
imodeladdformal -name PlantModelPWMMode -defaultvalue False -type bool

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
set name    taa
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version -constructor constructor

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "Renesas TAA Timer/Event Counter AA"
iadddocumentation -name Limitations -text "Status of Modes
- Interval Timer Mode                  - Supported
- External Event Count Mode            - Unsupported
- External Trigger Pulse Output Mode   - Unsupported
- One-Shot Pulse Mode                  - Unsupported
- PWM Mode                             - Unsupported
- Free-Running Mode                    - Supported
- Pulse Width Measurement Mode         - Unsupported
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
imodeladdnetport -name TOAA0 -type output
imodeladdnetport -name TOAA1 -type output
foreach interrupt {OV CC0 CC1} {
    imodeladdnetport -name INTTAA${interrupt} -type output
}

#
# Signal inputs
#
imodeladdnetport -name TIAA0  -type input -updatefunction P_TIAA0
imodeladdnetport -name TIAA1  -type input -updatefunction P_TIAA1
imodeladdnetport -name TTRGAA -type input -updatefunction P_TTRGAA
imodeladdnetport -name TEVTAA -type input -updatefunction P_TEVTAA

#
# Slave port
#
imodeladdbusslaveport -name TAAP0 -size 16

#
# Registers
#
imodeladdaddressblock -name reg0 -port TAAP0 -size  6 -offset  0 -width  8
imodeladdaddressblock -name reg1 -port TAAP0 -size  6 -offset  6 -width 16
imodeladdaddressblock -name reg2 -port TAAP0 -size  4 -offset 12 -width  8

#
# TAAP0
#
imodeladdmmregister -addressblock TAAP0/reg0 -name CTL0 -width 8 -offset 0 -access rw -writefunction writeCTL0 -writemask 0x87
imodeladdmmregister -addressblock TAAP0/reg0 -name CTL1 -width 8 -offset 1 -access rw -writefunction writeCTL1 -writemask 0xe7
imodeladdmmregister -addressblock TAAP0/reg0 -name IOC0 -width 8 -offset 2 -access rw -writefunction writeIOC0 -writemask 0x0f
imodeladdmmregister -addressblock TAAP0/reg0 -name IOC1 -width 8 -offset 3 -access rw -writefunction writeIOC1 -writemask 0x0f
imodeladdmmregister -addressblock TAAP0/reg0 -name IOC2 -width 8 -offset 4 -access rw -writefunction writeIOC2 -writemask 0x0f
imodeladdmmregister -addressblock TAAP0/reg0 -name OPT0 -width 8 -offset 5 -access rw -writefunction writeOPT0 -writemask 0x31

imodeladdmmregister -addressblock TAAP0/reg1 -name CCR0 -width 16 -offset 0 -access rw -writefunction writeCCR0
imodeladdmmregister -addressblock TAAP0/reg1 -name CCR1 -width 16 -offset 2 -access rw -writefunction writeCCR1
imodeladdmmregister -addressblock TAAP0/reg1 -name CNT  -width 16 -offset 4 -access r  -readfunction  readCNT

imodeladdmmregister -addressblock TAAP0/reg2 -name IOC4 -width 8 -offset 0 -access rw -writefunction writeIOC4 -writemask 0x0f
imodeladdmmregister -addressblock TAAP0/reg2 -name SVC  -width 8 -offset 2 -access rw -writefunction writeSVC

#
# Resets
#
imodeladdreset -mmregister TAAP0/reg0/CTL0 -name IRESET -value 0x00
imodeladdreset -mmregister TAAP0/reg0/CTL1 -name IRESET -value 0x00
imodeladdreset -mmregister TAAP0/reg0/IOC0 -name IRESET -value 0x00
imodeladdreset -mmregister TAAP0/reg0/IOC1 -name IRESET -value 0x00
imodeladdreset -mmregister TAAP0/reg0/IOC2 -name IRESET -value 0x00
imodeladdreset -mmregister TAAP0/reg0/OPT0 -name IRESET -value 0x00
imodeladdreset -mmregister TAAP0/reg1/CCR0 -name IRESET -value 0x0000
imodeladdreset -mmregister TAAP0/reg1/CCR1 -name IRESET -value 0x0000
imodeladdreset -mmregister TAAP0/reg1/CNT  -name IRESET -value 0x0000
imodeladdreset -mmregister TAAP0/reg2/IOC4 -name IRESET -value 0x00
imodeladdreset -mmregister TAAP0/reg2/SVC  -name IRESET -value 0x00

#
# Bit Fields
#
imodeladdfield -mmregister TAAP0/reg0/CTL0 -name CKS -bitoffset 0 -width 3
imodeladdfield -mmregister TAAP0/reg0/CTL0 -name CE  -bitoffset 7 -width 1

imodeladdfield -mmregister TAAP0/reg0/CTL1 -name MD  -bitoffset 0 -width 3
imodeladdfield -mmregister TAAP0/reg0/CTL1 -name EEE -bitoffset 5 -width 1
imodeladdfield -mmregister TAAP0/reg0/CTL1 -name EST -bitoffset 6 -width 1
imodeladdfield -mmregister TAAP0/reg0/CTL1 -name SYE -bitoffset 7 -width 1

imodeladdfield -mmregister TAAP0/reg0/IOC0 -name OE0 -bitoffset 0 -width 1
imodeladdfield -mmregister TAAP0/reg0/IOC0 -name OL0 -bitoffset 1 -width 1
imodeladdfield -mmregister TAAP0/reg0/IOC0 -name OE1 -bitoffset 2 -width 1
imodeladdfield -mmregister TAAP0/reg0/IOC0 -name OL1 -bitoffset 3 -width 1

imodeladdfield -mmregister TAAP0/reg0/IOC1 -name IS  -bitoffset 0 -width 4

imodeladdfield -mmregister TAAP0/reg0/IOC2 -name ETS -bitoffset 0 -width 2
imodeladdfield -mmregister TAAP0/reg0/IOC2 -name EES -bitoffset 2 -width 2

imodeladdfield -mmregister TAAP0/reg0/OPT0 -name OVF -bitoffset 0 -width 1
imodeladdfield -mmregister TAAP0/reg0/OPT0 -name CCS -bitoffset 4 -width 2

imodeladdfield -mmregister TAAP0/reg2/IOC4 -name OR0 -bitoffset 0 -width 1
imodeladdfield -mmregister TAAP0/reg2/IOC4 -name OS0 -bitoffset 1 -width 1
imodeladdfield -mmregister TAAP0/reg2/IOC4 -name OR1 -bitoffset 2 -width 1
imodeladdfield -mmregister TAAP0/reg2/IOC4 -name OS1 -bitoffset 3 -width 1

imodeladdfield -mmregister TAAP0/reg2/SVC  -name CSR0 -bitoffset 0 -width 1
imodeladdfield -mmregister TAAP0/reg2/SVC  -name CSD0 -bitoffset 1 -width 1
imodeladdfield -mmregister TAAP0/reg2/SVC  -name CSE0 -bitoffset 2 -width 1
imodeladdfield -mmregister TAAP0/reg2/SVC  -name ENC0 -bitoffset 3 -width 1
imodeladdfield -mmregister TAAP0/reg2/SVC  -name CSR1 -bitoffset 4 -width 1
imodeladdfield -mmregister TAAP0/reg2/SVC  -name CSD1 -bitoffset 5 -width 1
imodeladdfield -mmregister TAAP0/reg2/SVC  -name CSE1 -bitoffset 6 -width 1
imodeladdfield -mmregister TAAP0/reg2/SVC  -name ENC1 -bitoffset 7 -width 1

#
# Enables the generation of a function to be intercepted by a plant model
# This is used to indicate a change in the PWM rate
#
imodeladdformal -name PlantModelPWM -defaultvalue False -type bool

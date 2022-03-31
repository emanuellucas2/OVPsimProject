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
set name    UPD70F3441Logic
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version -constructor constructor

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "Renesas V850PHO3 / UPD70F3441 Glue Logic"
iadddocumentation -name Limitations -text "No known limitations"
iadddocumentation -name Reference   -text "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010"

#
# Interrupt Sharing Logic
#
foreach input {NMIIN INTDEDF INTDEDR INTDEDFR INTOSD INTP4 INTUC0R INTP5 INTUC1R 
        INTBRG0 INTBRG1 INTCB0T INTUC2T INTCB0R INTUC2R INTP13 INTCB0RE INTUC2RE
        INTDMA3 INTFL} {
    imodeladdnetport -name ${input} -type input -updatefunction P_${input}
}
foreach output {NMIOUT INT0 INT1 INT6 INT7 INT75 INT99 INT100 INT101 INT116} {
    imodeladdnetport -name ${output} -type output
}

#
# Slave port
#
imodeladdbusslaveport -name LOGICP0 -size 4
imodeladdbusslaveport -name LOGICP1 -size 118
imodeladdbusslaveport -name LOGICP2 -size 12
imodeladdbusslaveport -name LOGICP3 -size 1

#
# Registers
#
imodeladdaddressblock -name reg0 -port LOGICP0 -size 4 -offset 0 -width 8
imodeladdmmregister -addressblock LOGICP0/reg0 -name INTSEL  -width 8  -offset 0 -access rw -writefunction writeSEL -writemask 0x9d
imodeladdmmregister -addressblock LOGICP0/reg0 -name INTERRF -width 8  -offset 2 -access rw -writefunction writeERR -writemask 0x87

imodeladdaddressblock -name reg0 -port LOGICP1 -size 118 -offset 0 -width 8
imodeladdmmregister -addressblock LOGICP1/reg0 -name LOGICP0 -width 8 -offset 0 -access r
set off1 0x02
set off2 0x22
set off3 0x42
for {set i 1} {$i <= 11} {incr i} {
  imodeladdmmregister -addressblock LOGICP1/reg0 -name P${i}   -width 8 -offset ${off1} -access rw -writefunction writeP
  imodeladdmmregister -addressblock LOGICP1/reg0 -name PM${i}  -width 8 -offset ${off2} -access rw -writefunction writePM 
  imodeladdmmregister -addressblock LOGICP1/reg0 -name PMC${i} -width 8 -offset ${off3} -access rw -writefunction writePMC

  incr off1 2
  incr off2 2
  incr off3 2
}
imodeladdmmregister -addressblock LOGICP1/reg0 -name PFC1  -width 8 -offset 0x62 -access rw -writefunction writePFC
imodeladdmmregister -addressblock LOGICP1/reg0 -name PFC2  -width 8 -offset 0x64 -access rw -writefunction writePFC
imodeladdmmregister -addressblock LOGICP1/reg0 -name PFC4  -width 8 -offset 0x68 -access rw -writefunction writePFC
imodeladdmmregister -addressblock LOGICP1/reg0 -name PFC7  -width 8 -offset 0x6e -access rw -writefunction writePFC
imodeladdmmregister -addressblock LOGICP1/reg0 -name PFC8  -width 8 -offset 0x70 -access rw -writefunction writePFC
imodeladdmmregister -addressblock LOGICP1/reg0 -name PFC9  -width 8 -offset 0x72 -access rw -writefunction writePFC
imodeladdmmregister -addressblock LOGICP1/reg0 -name PFC10 -width 8 -offset 0x74 -access rw -writefunction writePFC

imodeladdaddressblock -name reg0 -port LOGICP2 -size 12 -offset 0 -width 8
imodeladdmmregister -addressblock LOGICP2/reg0 -name PESC5  -width 8 -offset 0x0 -access rw -writefunction writePESC5
imodeladdmmregister -addressblock LOGICP2/reg0 -name ESOST5 -width 8 -offset 0x2 -access rw -writefunction writeESOST5
imodeladdmmregister -addressblock LOGICP2/reg0 -name PESC6  -width 8 -offset 0x4 -access rw -writefunction writePESC6
imodeladdmmregister -addressblock LOGICP2/reg0 -name ESOST6 -width 8 -offset 0x6 -access rw -writefunction writeESOST6
imodeladdmmregister -addressblock LOGICP2/reg0 -name PESMK5 -width 8 -offset 0x8 -access rw -writefunction writePESMK5
imodeladdmmregister -addressblock LOGICP2/reg0 -name PESMK6 -width 8 -offset 0xa -access rw -writefunction writePESMK6

imodeladdaddressblock -name reg0 -port LOGICP3 -size 1 -offset 0 -width 8
imodeladdmmregister -addressblock LOGICP3/reg0 -name PRCMD  -width 8 -offset 0x0 -access w  -writefunction writePRCMD

#
# Resets
#
imodeladdreset -mmregister LOGICP0/reg0/INTSEL  -name IRESET -value 0x00
imodeladdreset -mmregister LOGICP0/reg0/INTERRF -name IRESET -value 0x00
imodeladdreset -mmregister LOGICP2/reg0/PESC5   -name IRESET -value 0x00
imodeladdreset -mmregister LOGICP2/reg0/ESOST5  -name IRESET -value 0x00
imodeladdreset -mmregister LOGICP2/reg0/PESC6   -name IRESET -value 0x00
imodeladdreset -mmregister LOGICP2/reg0/ESOST6  -name IRESET -value 0x00
imodeladdreset -mmregister LOGICP2/reg0/PESMK5  -name IRESET -value 0x00
imodeladdreset -mmregister LOGICP2/reg0/PESMK6  -name IRESET -value 0x00

#
# Bit Fields
#
imodeladdfield -mmregister LOGICP0/reg0/INTSEL  -name BRGSSR  -bitoffset 0 -width 1
imodeladdfield -mmregister LOGICP0/reg0/INTSEL  -name INTSEL4 -bitoffset 4 -width 1
imodeladdfield -mmregister LOGICP0/reg0/INTSEL  -name ISR     -bitoffset 7 -width 1

imodeladdfield -mmregister LOGICP0/reg0/INTERRF -name INTERR0 -bitoffset 0 -width 1
imodeladdfield -mmregister LOGICP0/reg0/INTERRF -name INTERR1 -bitoffset 1 -width 1
imodeladdfield -mmregister LOGICP0/reg0/INTERRF -name INTERR2 -bitoffset 2 -width 1
imodeladdfield -mmregister LOGICP0/reg0/INTERRF -name INTERR7 -bitoffset 7 -width 1

imodeladdfield -mmregister LOGICP1/reg0/PFC4    -name PFC40   -bitoffset 0 -width 1
imodeladdfield -mmregister LOGICP1/reg0/PFC4    -name PFC41   -bitoffset 1 -width 1


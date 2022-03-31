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
set name    adc
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version -constructor constructor -destructor destructor

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "Renesas ADC A/D Converter"
iadddocumentation -name Limitations -text "Model supports Modes Select, Scan, 1xBuffer, 4xBuffer - no support for external trigger"
iadddocumentation -name Reference   -text "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010"

for {set i 0} {$i < 10} {incr i} {
    imodeladdformal -type string -name stimfile${i}
}
imodeladdformal -name PCLK1  -type uns32
imodeladdformal -name sample -type double -defaultvalue 100.0

#
# Signal outputs
#
foreach output {INTAD ADDMARQ} {
	imodeladdnetport -name ${output} -type output
}
# Indicates if DMA channel is enabled and DMAC will generate Interrupt
imodeladdnetport -name INTADEN -type input -updatefunction P_INTADEN

#
# Signal inputs
#
foreach input {ADTRG TS0ADT0 TS0ADT1 INTTS0OD INTTS0CD TS1ADT0 TS1ADT1 INTTS1OD INTTS1CD} {
    imodeladdnetport -name ${input} -type input -updatefunction P_${input}
}

#
# Slave port
#
imodeladdbusslaveport -name ADCP0 -size 48
imodeladdbusslaveport -name ADCP1 -size 1

#
# Registers
#
imodeladdaddressblock -name reg0 -port ADCP0 -size    3 -offset    0 -width  8
imodeladdaddressblock -name reg1 -port ADCP0 -size 0x14 -offset 0x10 -width 16
imodeladdaddressblock -name reg2 -port ADCP0 -size    2 -offset 0x2e -width 16
imodeladdaddressblock -name reg0 -port ADCP1 -size    1 -offset    0 -width  8

#
# ADCP0 reg0/reg1/reg2
#
imodeladdmmregister -addressblock ADCP0/reg0 -name ADM0 -width 8 -offset 0 -access rw -writefunction writeADM0 -writemask 0xf0
imodeladdmmregister -addressblock ADCP0/reg0 -name ADM1 -width 8 -offset 1 -access rw -writefunction writeADM1 -writemask 0xf3
imodeladdmmregister -addressblock ADCP0/reg0 -name ADM2 -width 8 -offset 2 -access rw -writefunction writeADM2 -writemask 0x0f
for {set i 0} {$i <= 9} {incr i} {
  set off [expr 2 * $i]
  imodeladdmmregister -addressblock ADCP0/reg1 -name ADCR${i} -width 16 -offset $off -access r -readfunction readADCR -userdata ${i}
}
imodeladdmmregister -addressblock ADCP0/reg2 -name ADDMA -width 16 -offset 0 -access r -readfunction readADDMA

#
# ADCP1 reg0
#
imodeladdmmregister -addressblock ADCP1/reg0 -name ADTRSEL -width 8 -offset 0 -access rw -writefunction writeADTRSEL -writemask 0x0f

#
# Resets
#
imodeladdreset -mmregister ADCP0/reg0/ADM0 -name IRESET -value 0x00
imodeladdreset -mmregister ADCP0/reg0/ADM1 -name IRESET -value 0x00
imodeladdreset -mmregister ADCP0/reg0/ADM2 -name IRESET -value 0x00
for {set i 0} {$i <= 9} {incr i} {
  imodeladdreset -mmregister ADCP0/reg1/ADCR${i} -name IRESET -value 0x00
}
imodeladdreset -mmregister ADCP0/reg2/ADDMA -name IRESET -value 0x00
imodeladdreset -mmregister ADCP1/reg0/ADTRSEL -name IRESET -value 0x00

#
# Bit Fields
#
imodeladdfield -mmregister ADCP0/reg0/ADM0 -name MS   -bitoffset 4 -width 1
imodeladdfield -mmregister ADCP0/reg0/ADM0 -name BS   -bitoffset 5 -width 1
imodeladdfield -mmregister ADCP0/reg0/ADM0 -name ADCS -bitoffset 6 -width 1
imodeladdfield -mmregister ADCP0/reg0/ADM0 -name ADCE -bitoffset 7 -width 1

imodeladdfield -mmregister ADCP0/reg0/ADM1 -name FR   -bitoffset 0 -width 2
imodeladdfield -mmregister ADCP0/reg0/ADM1 -name TRG  -bitoffset 4 -width 2
imodeladdfield -mmregister ADCP0/reg0/ADM1 -name EGA  -bitoffset 6 -width 2

imodeladdfield -mmregister ADCP0/reg0/ADM2 -name ANI  -bitoffset 0 -width 4

for {set i 0} {$i <= 9} {incr i} {
  imodeladdfield -mmregister ADCP0/reg1/ADCR${i} -name AD -bitoffset 6 -width 10
}

imodeladdfield -mmregister ADCP0/reg2/ADDMA -name ODF   -bitoffset 0 -width 1
imodeladdfield -mmregister ADCP0/reg2/ADDMA -name ADDMA -bitoffset 6 -width 10

imodeladdfield -mmregister ADCP1/reg0/ADTRSEL -name TSEL -bitoffset 0 -width 4

# The ADC may use a native intercepted plant model to provide data to channels 
for {set i 0} {$i < 10} {incr i} {
    imodeladdformal -type string -name plantmode${i}
}

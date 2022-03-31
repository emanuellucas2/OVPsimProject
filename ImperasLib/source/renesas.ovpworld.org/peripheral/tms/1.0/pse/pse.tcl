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
set name    tms
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse -library $library -vendor $vendor -version $version -constructor constructor

iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Description -text "Renesas TMS Timer/Event Counter S"
iadddocumentation -name Limitations -text "Status of Modes
- Interval Timer Mode                  - Supported
- External Event Count Mode            - Untested
- External Trigger Pulse Output Mode   - Unsupported
- One-Shot Pulse Mode                  - Unsupported
- PWM Mode                             - Unsupported
- Free-Running Mode                    - Supported
- Triangular-Wave PWM Mode             - Unsupported
- High Accuracy T-PWM Mode             - Unsupported
- PWM Mode with Dead Time              - Unsupported
- 120Deg Excitation Mode               - Unsupported
- Special 120Deg Excitation Mode       - Unsupported
- Special Pattern Output Mode          - Unsupported
"
iadddocumentation -name Reference   -text "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010"

#
# PCLKx formal container
#
foreach i {0 1 2 3 4 5 7 9} {
    imodeladdformal -name PCLK${i} -type uns32
}
imodeladdformal -name PCLK_DEF -defaultvalue 0 -max 9 -min 0 -type uns32
imodeladdformal -name PARAM_01 -defaultvalue 0 -type uns32
#
# Signal outputs
#
for {set i 0} {$i <= 7} {incr i} {
    imodeladdnetport -name TOS${i} -type output
}
foreach output {ADTRG0 ADTRG1 AEDO ESG TSF} {
    imodeladdnetport -name TS${output} -type output
}
foreach interrupt {CC0 CC1 CC2 CC3 CC4 CC5 CD0 OD OV ER WN} {
    imodeladdnetport -name INTTS${interrupt} -type output
}

#
# Signal inputs
#
foreach input {TTRGS TEVTS TAPTS0 TAPTS1 TAPTS2 ESO} {
    imodeladdnetport -name ${input} -type input -updatefunction P_${input}
}

#
# Slave port
#
imodeladdbusslaveport -name TMSP0 -size 42

#
# Registers
#
imodeladdaddressblock -name reg0 -port TMSP0 -size  2 -offset  0 -width  8
imodeladdaddressblock -name reg1 -port TMSP0 -size  2 -offset  2 -width 16
imodeladdaddressblock -name reg2 -port TMSP0 -size  6 -offset  4 -width  8
imodeladdaddressblock -name reg3 -port TMSP0 -size 32 -offset 10 -width 16

#
# TMSP0
#
imodeladdmmregister -addressblock TMSP0/reg0 -name CTL0 -width 8  -offset 0 -access rw -writefunction writeCTL0 -writemask 0x87
imodeladdmmregister -addressblock TMSP0/reg0 -name CTL1 -width 8  -offset 1 -access rw -writefunction writeCTL1 -writemask 0x6f

imodeladdmmregister -addressblock TMSP0/reg1 -name IOC0 -width 16 -offset 0 -access rw -writefunction writeIOC0 -readfunction readIOC0 -writemask 0xffff

imodeladdmmregister -addressblock TMSP0/reg2 -name IOC2 -width 8  -offset 0 -access rw -writefunction writeIOC2 -writemask 0x0f
imodeladdmmregister -addressblock TMSP0/reg2 -name IOC4 -width 8  -offset 1 -access rw -writefunction writeIOC4 -writemask 0x75
imodeladdmmregister -addressblock TMSP0/reg2 -name OPT0 -width 8  -offset 2 -access rw -writefunction writeOPT0 -writemask 0x0f
imodeladdmmregister -addressblock TMSP0/reg2 -name OPT4 -width 8  -offset 4 -access rw -writefunction writeOPT4 -writemask 0x8f
imodeladdmmregister -addressblock TMSP0/reg2 -name OPT5 -width 8  -offset 5 -access rw -writefunction writeOPT5 -writemask 0xff
imodeladdmmregister -addressblock TMSP0/reg2 -name OPT7 -width 8  -offset 3 -access rw -writefunction writeOPT7 -writemask 0x3f

imodeladdmmregister -addressblock TMSP0/reg3 -name OPT1 -width 16 -offset  0 -access rw -writefunction writeOPT1 -readfunction readOPT1 -writemask 0x1fff
imodeladdmmregister -addressblock TMSP0/reg3 -name OPT2 -width 16 -offset 22 -access rw -writefunction writeOPT2 -readfunction readOPT2 -writemask 0xffff
imodeladdmmregister -addressblock TMSP0/reg3 -name OPT3 -width 16 -offset 24 -access rw -writefunction writeOPT3 -readfunction readOPT3 -writemask 0x03ff
imodeladdmmregister -addressblock TMSP0/reg3 -name OPT6 -width 16 -offset 26 -access rw -writefunction writeOPT6 -readfunction readOPT6 -writemask 0x01ff
imodeladdmmregister -addressblock TMSP0/reg3 -name DTC0 -width 16 -offset  4 -access rw -writefunction writeDTC0 -writemask 0x03fe
imodeladdmmregister -addressblock TMSP0/reg3 -name DTC1 -width 16 -offset  2 -access rw -writefunction writeDTC1 -writemask 0x03fe
imodeladdmmregister -addressblock TMSP0/reg3 -name PAT0 -width 16 -offset 12 -access rw -writefunction writePAT0 -writemask 0xffff
imodeladdmmregister -addressblock TMSP0/reg3 -name PAT1 -width 16 -offset 10 -access rw -writefunction writePAT1 -writemask 0xffff
imodeladdmmregister -addressblock TMSP0/reg3 -name CCR0 -width 16 -offset 14 -access rw -writefunction writeCCR0 -writemask 0xffff
imodeladdmmregister -addressblock TMSP0/reg3 -name CCR1 -width 16 -offset 20 -access rw -writefunction writeCCR1 -writemask 0xffff
imodeladdmmregister -addressblock TMSP0/reg3 -name CCR2 -width 16 -offset 18 -access rw -writefunction writeCCR2 -writemask 0xffff
imodeladdmmregister -addressblock TMSP0/reg3 -name CCR3 -width 16 -offset 16 -access rw -writefunction writeCCR3 -writemask 0xffff
imodeladdmmregister -addressblock TMSP0/reg3 -name CCR4 -width 16 -offset  8 -access rw -writefunction writeCCR4 -writemask 0xffff
imodeladdmmregister -addressblock TMSP0/reg3 -name CCR5 -width 16 -offset  6 -access rw -writefunction writeCCR5 -writemask 0xffff
imodeladdmmregister -addressblock TMSP0/reg3 -name CNT  -width 16 -offset 28 -access r  -readfunction readCNT
imodeladdmmregister -addressblock TMSP0/reg3 -name SBC  -width 16 -offset 30 -access r  -readfunction readSBC

#
# Resets
#
imodeladdreset -mmregister TMSP0/reg0/CTL0 -name IRESET -value 0x00
imodeladdreset -mmregister TMSP0/reg0/CTL1 -name IRESET -value 0x00
imodeladdreset -mmregister TMSP0/reg1/IOC0 -name IRESET -value 0x0000
imodeladdreset -mmregister TMSP0/reg2/IOC2 -name IRESET -value 0x00
imodeladdreset -mmregister TMSP0/reg2/IOC4 -name IRESET -value 0x00
imodeladdreset -mmregister TMSP0/reg2/OPT0 -name IRESET -value 0x00
imodeladdreset -mmregister TMSP0/reg2/OPT7 -name IRESET -value 0x00
imodeladdreset -mmregister TMSP0/reg2/OPT4 -name IRESET -value 0x00
imodeladdreset -mmregister TMSP0/reg2/OPT5 -name IRESET -value 0x00

imodeladdreset -mmregister TMSP0/reg3/DTC1 -name IRESET -value 0x0000
imodeladdreset -mmregister TMSP0/reg3/DTC0 -name IRESET -value 0x0000
imodeladdreset -mmregister TMSP0/reg3/CCR5 -name IRESET -value 0x0000
imodeladdreset -mmregister TMSP0/reg3/CCR4 -name IRESET -value 0x0000
imodeladdreset -mmregister TMSP0/reg3/PAT1 -name IRESET -value 0x0000
imodeladdreset -mmregister TMSP0/reg3/PAT0 -name IRESET -value 0x0000
imodeladdreset -mmregister TMSP0/reg3/CCR0 -name IRESET -value 0x0000
imodeladdreset -mmregister TMSP0/reg3/CCR3 -name IRESET -value 0x0000
imodeladdreset -mmregister TMSP0/reg3/CCR2 -name IRESET -value 0x0000
imodeladdreset -mmregister TMSP0/reg3/CCR1 -name IRESET -value 0x0000
imodeladdreset -mmregister TMSP0/reg3/OPT2 -name IRESET -value 0x0000
imodeladdreset -mmregister TMSP0/reg3/OPT3 -name IRESET -value 0x0000
imodeladdreset -mmregister TMSP0/reg3/OPT6 -name IRESET -value 0x0000
imodeladdreset -mmregister TMSP0/reg3/CNT  -name IRESET -value 0x0000
imodeladdreset -mmregister TMSP0/reg3/SBC  -name IRESET -value 0x0000

#
# Bit Fields
#
imodeladdfield -mmregister TMSP0/reg0/CTL0 -name CKS -bitoffset 0 -width 3
imodeladdfield -mmregister TMSP0/reg0/CTL0 -name CE  -bitoffset 7 -width 1

imodeladdfield -mmregister TMSP0/reg0/CTL1 -name MD  -bitoffset 0 -width 4
imodeladdfield -mmregister TMSP0/reg0/CTL1 -name EEE -bitoffset 5 -width 1
imodeladdfield -mmregister TMSP0/reg0/CTL1 -name EST -bitoffset 6 -width 1

imodeladdfield -mmregister TMSP0/reg1/IOC0 -name OE0 -bitoffset  0 -width 1
imodeladdfield -mmregister TMSP0/reg1/IOC0 -name OL0 -bitoffset  1 -width 1
imodeladdfield -mmregister TMSP0/reg1/IOC0 -name OE1 -bitoffset  2 -width 1
imodeladdfield -mmregister TMSP0/reg1/IOC0 -name OL1 -bitoffset  3 -width 1
imodeladdfield -mmregister TMSP0/reg1/IOC0 -name OE2 -bitoffset  4 -width 1
imodeladdfield -mmregister TMSP0/reg1/IOC0 -name OL2 -bitoffset  5 -width 1
imodeladdfield -mmregister TMSP0/reg1/IOC0 -name OE3 -bitoffset  6 -width 1
imodeladdfield -mmregister TMSP0/reg1/IOC0 -name OL3 -bitoffset  7 -width 1
imodeladdfield -mmregister TMSP0/reg1/IOC0 -name OE4 -bitoffset  8 -width 1
imodeladdfield -mmregister TMSP0/reg1/IOC0 -name OL4 -bitoffset  9 -width 1
imodeladdfield -mmregister TMSP0/reg1/IOC0 -name OE5 -bitoffset 10 -width 1
imodeladdfield -mmregister TMSP0/reg1/IOC0 -name OL5 -bitoffset 11 -width 1
imodeladdfield -mmregister TMSP0/reg1/IOC0 -name OE6 -bitoffset 12 -width 1
imodeladdfield -mmregister TMSP0/reg1/IOC0 -name OL6 -bitoffset 13 -width 1
imodeladdfield -mmregister TMSP0/reg1/IOC0 -name OE7 -bitoffset 14 -width 1
imodeladdfield -mmregister TMSP0/reg1/IOC0 -name OL7 -bitoffset 15 -width 1

imodeladdfield -mmregister TMSP0/reg2/IOC2 -name ETS -bitoffset  0 -width 2
imodeladdfield -mmregister TMSP0/reg2/IOC2 -name EES -bitoffset  2 -width 2

imodeladdfield -mmregister TMSP0/reg2/IOC4 -name EOC -bitoffset  0 -width 1
imodeladdfield -mmregister TMSP0/reg2/IOC4 -name WOC -bitoffset  2 -width 1
imodeladdfield -mmregister TMSP0/reg2/IOC4 -name BA  -bitoffset  4 -width 3

imodeladdfield -mmregister TMSP0/reg2/OPT0 -name OVF -bitoffset  0 -width 1
imodeladdfield -mmregister TMSP0/reg2/OPT0 -name CUF -bitoffset  1 -width 1
imodeladdfield -mmregister TMSP0/reg2/OPT0 -name CMS -bitoffset  2 -width 1
imodeladdfield -mmregister TMSP0/reg2/OPT0 -name DSE -bitoffset  3 -width 1

imodeladdfield -mmregister TMSP0/reg2/OPT7 -name TOS -bitoffset  0 -width 1
imodeladdfield -mmregister TMSP0/reg2/OPT7 -name PTC -bitoffset  1 -width 2
imodeladdfield -mmregister TMSP0/reg2/OPT7 -name TDC -bitoffset  3 -width 1
imodeladdfield -mmregister TMSP0/reg2/OPT7 -name PPC -bitoffset  4 -width 1
imodeladdfield -mmregister TMSP0/reg2/OPT7 -name IDC -bitoffset  5 -width 1

imodeladdfield -mmregister TMSP0/reg2/OPT4 -name IPC -bitoffset  0 -width 3
imodeladdfield -mmregister TMSP0/reg2/OPT4 -name PSC -bitoffset  3 -width 1
imodeladdfield -mmregister TMSP0/reg2/OPT4 -name SOC -bitoffset  7 -width 1

imodeladdfield -mmregister TMSP0/reg2/OPT5 -name OPF -bitoffset  0 -width 3
imodeladdfield -mmregister TMSP0/reg2/OPT5 -name TSF -bitoffset  3 -width 1
imodeladdfield -mmregister TMSP0/reg2/OPT5 -name PTS -bitoffset  4 -width 1
imodeladdfield -mmregister TMSP0/reg2/OPT5 -name PSS -bitoffset  5 -width 1
imodeladdfield -mmregister TMSP0/reg2/OPT5 -name POT -bitoffset  6 -width 1
imodeladdfield -mmregister TMSP0/reg2/OPT5 -name ADC -bitoffset  7 -width 1

imodeladdfield -mmregister TMSP0/reg3/OPT1 -name ID  -bitoffset  0 -width 5
imodeladdfield -mmregister TMSP0/reg3/OPT1 -name RDE -bitoffset  5 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT1 -name IOE -bitoffset  6 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT1 -name ICE -bitoffset  7 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT1 -name RBE -bitoffset  8 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT1 -name RTE -bitoffset  9 -width 1

imodeladdfield -mmregister TMSP0/reg3/DTC1 -name DTV -bitoffset  1 -width 9
imodeladdfield -mmregister TMSP0/reg3/DTC0 -name DTV -bitoffset  1 -width 9

imodeladdfield -mmregister TMSP0/reg3/PAT1 -name SP4 -bitoffset  0 -width 4
imodeladdfield -mmregister TMSP0/reg3/PAT1 -name SP5 -bitoffset  4 -width 4
imodeladdfield -mmregister TMSP0/reg3/PAT1 -name SP6 -bitoffset  8 -width 4
imodeladdfield -mmregister TMSP0/reg3/PAT1 -name SP7 -bitoffset 12 -width 4

imodeladdfield -mmregister TMSP0/reg3/PAT0 -name SP0 -bitoffset  0 -width 4
imodeladdfield -mmregister TMSP0/reg3/PAT0 -name SP1 -bitoffset  4 -width 4
imodeladdfield -mmregister TMSP0/reg3/PAT0 -name SP2 -bitoffset  8 -width 4
imodeladdfield -mmregister TMSP0/reg3/PAT0 -name SP3 -bitoffset 12 -width 4

imodeladdfield -mmregister TMSP0/reg3/OPT2 -name AT00 -bitoffset  0 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT2 -name AT01 -bitoffset  1 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT2 -name AT02 -bitoffset  2 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT2 -name AT03 -bitoffset  3 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT2 -name AT04 -bitoffset  4 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT2 -name AT05 -bitoffset  5 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT2 -name AT06 -bitoffset  6 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT2 -name AT07 -bitoffset  7 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT2 -name ACC0 -bitoffset  8 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT2 -name ACC1 -bitoffset  9 -width 1

imodeladdfield -mmregister TMSP0/reg3/OPT3 -name AT00 -bitoffset  0 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT3 -name AT01 -bitoffset  1 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT3 -name AT02 -bitoffset  2 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT3 -name AT03 -bitoffset  3 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT3 -name AT04 -bitoffset  4 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT3 -name AT05 -bitoffset  5 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT3 -name AT06 -bitoffset  6 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT3 -name AT07 -bitoffset  7 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT3 -name ACC2 -bitoffset  8 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT3 -name ACC3 -bitoffset  9 -width 1

imodeladdfield -mmregister TMSP0/reg3/OPT6 -name RSF  -bitoffset  0 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT6 -name SUF  -bitoffset  1 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT6 -name TBF  -bitoffset  2 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT6 -name PEF  -bitoffset  3 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT6 -name PRF  -bitoffset  4 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT6 -name NDF  -bitoffset  5 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT6 -name TDF  -bitoffset  6 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT6 -name PTF  -bitoffset  7 -width 1
imodeladdfield -mmregister TMSP0/reg3/OPT6 -name PPF  -bitoffset  8 -width 1

imodeladdfield -mmregister TMSP0/reg3/CNT  -name MODE -bitoffset  0 -width 1
imodeladdfield -mmregister TMSP0/reg3/CNT  -name VAL  -bitoffset  1 -width 15

imodeladdfield -mmregister TMSP0/reg3/SBC  -name MODE -bitoffset  0 -width 1
imodeladdfield -mmregister TMSP0/reg3/SBC  -name SVAL -bitoffset  1 -width 15

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

set vendor  atmel.ovpworld.org
set library peripheral
set name    AdvancedInterruptController
set version 1.0

imodelnewperipheral \
    -name $name \
    -imagefile pse.pse \
    -library $library \
    -vendor $vendor \
    -version $version \
    -constructor constructor

iadddocumentation -name Description -text "AIC: Advanced Interrupt Controller
This model contains an accurate Register set interface.
The functionality has only been implemented to sufficiently boot uClinux
The Advanced Interrupt Controller has an 8-level priority, individually maskable, vectored interrupt
controller, and drives the NIRQ and NFIQ pins of the ARM7TDMI from:
 The external fast interrupt line (FIQ)
 The three external interrupt request lines (IRQ0 - IRQ2)
 The interrupt signals from the on-chip peripherals
The AIC is extensively programmable offering maximum flexibility, and its vectoring features
reduce the real-time overhead in handling interrupts.
The AIC also features a spurious vector detection feature, which reduces spurious interrupt handling
to a minimum, and a protect mode that facilitates the debug capabilities.
"
iadddocumentation  \
-name Licensing  \
-text "Open Source Apache 2.0"

iadddocumentation -name Limitations -text "This model is sufficient to boot Linux"
iadddocumentation -name Reference   -text "Rev. 1354D ARM08/02"

#
# Interrupt Signal Block output
#
imodeladdnetport -name NFIQ -type output
imodeladdnetport -name NIRQ -type output

#
# Interrupt Signal Block input
# FIQ results in NFIQ
# all others result in NIRQ
#
set interruptSources { FIQ SWIRQ US0IRQ US1IRQ TC0IRQ TC1IRQ TC2IRQ WDIRQ PIOIRQ IRQ0 IRQ1 IRQ2 }
foreach i $interruptSources {
  imodeladdnetport -name $i -type input -updatefunction ${i}_wcb
}

#
# Register Block
#
imodeladdbusslaveport -name bp1 -mustbeconnected -size 0x1000
imodeladdaddressblock -name REG -port bp1 -size 0x1000 -offset 0 -width 32

#
# AIC_SMR0-31
#

imodeladdmmregister -addressblock bp1/REG -name AIC_SMR%u -width 32 -offset 0 -access rw -writefunction AIC_SMR_wcb -loarray 0 -hiarray 31 -userdata _index
  #
  # AIC_SMRx
  #
  imodeladdfield -mmregister bp1/REG/AIC_SMR%u -name PRIOR   -bitoffset 0 -width 2
  imodeladdfield -mmregister bp1/REG/AIC_SMR%u -name SRCTYPE -bitoffset 5 -width 2


#
# AIC_SVR0-31
#
imodeladdmmregister -addressblock bp1/REG -name AIC_SVR%u -width 32 -offset 0x80 -access rw -writefunction AIC_SVR_wcb -loarray 0 -hiarray 31 -userdata _index
  #
  # AIC_SVRx
  #
  imodeladdfield -mmregister bp1/REG/AIC_SVR%u -name VECTOR -bitoffset 0 -width 32

set registers {
  AIC_IVR   0x100 r  0x0 AIC_IVR_rcb -
  AIC_FVR   0x104 r  0x0 - -
  AIC_ISR   0x108 r  0x0 - -
  AIC_IPR   0x10c r  0x0 - -
  AIC_IMR   0x110 r  0x0 - -
  AIC_CISR  0x114 r  0x0 - -
  AIC_RSV0  0x118 -    - - -
  AIC_RSV1  0x11c -    - - -
  AIC_IECR  0x120 w  0x0 - AIC_IECR_wcb
  AIC_IDCR  0x124 w  0x0 - AIC_IDCR_wcb
  AIC_ICCR  0x128 w  0x0 - AIC_ICCR_wcb
  AIC_ISCR  0x12c w  0x0 - AIC_ISCR_wcb
  AIC_EOICR 0x130 w  0x0 - AIC_EOICR_wcb
  AIC_SPU   0x134 rw 0x0 - AIC_SPU_wcb
}

foreach {rname roffset raccess reset readFunc writeFunc} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}

  set command "imodeladdmmregister -addressblock bp1/REG -name $rname -width 32 -offset $roffset -access $raccess"
  if { $readFunc != "-" } {
    set command "${command} -readfunction $readFunc"
  }
  if { $writeFunc != "-" } {
    set command "${command} -writefunction $writeFunc"
  }
  
  eval $command

  imodeladdreset -mmregister bp1/REG/$rname -name resetNet -value $reset
}

#
# AIC_ISR
#
imodeladdfield -mmregister bp1/REG/AIC_ISR -name IRQID -bitoffset 0 -width 5

#
# AIC_IPR
#
imodeladdfield -mmregister bp1/REG/AIC_IPR -name IRQ2   -bitoffset 18 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IPR -name IRQ1   -bitoffset 17 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IPR -name IRQ0   -bitoffset 16 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IPR -name PIOIRQ -bitoffset  8 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IPR -name WDIRQ  -bitoffset  7 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IPR -name TC2IRQ -bitoffset  6 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IPR -name TC1IRQ -bitoffset  5 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IPR -name TC0IRQ -bitoffset  4 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IPR -name US1IRQ -bitoffset  3 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IPR -name US0IRQ -bitoffset  2 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IPR -name SWIRQ  -bitoffset  1 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IPR -name FIQ    -bitoffset  0 -width 1

#
# AIC_IMR
#
imodeladdfield -mmregister bp1/REG/AIC_IMR -name IRQ2   -bitoffset 18 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IMR -name IRQ1   -bitoffset 17 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IMR -name IRQ0   -bitoffset 16 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IMR -name PIOIRQ -bitoffset  8 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IMR -name WDIRQ  -bitoffset  7 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IMR -name TC2IRQ -bitoffset  6 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IMR -name TC1IRQ -bitoffset  5 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IMR -name TC0IRQ -bitoffset  4 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IMR -name US1IRQ -bitoffset  3 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IMR -name US0IRQ -bitoffset  2 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IMR -name SWIRQ  -bitoffset  1 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IMR -name FIQ    -bitoffset  0 -width 1

#
# AIC_CISR
#
imodeladdfield -mmregister bp1/REG/AIC_CISR -name NIRQ -bitoffset 1 -width 1
imodeladdfield -mmregister bp1/REG/AIC_CISR -name NFIQ -bitoffset 0 -width 1

#
# AIC_IECR
#
imodeladdfield -mmregister bp1/REG/AIC_IECR -name IRQ2   -bitoffset 18 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IECR -name IRQ1   -bitoffset 17 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IECR -name IRQ0   -bitoffset 16 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IECR -name PIOIRQ -bitoffset  8 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IECR -name WDIRQ  -bitoffset  7 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IECR -name TC2IRQ -bitoffset  6 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IECR -name TC1IRQ -bitoffset  5 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IECR -name TC0IRQ -bitoffset  4 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IECR -name US1IRQ -bitoffset  3 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IECR -name US0IRQ -bitoffset  2 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IECR -name SWIRQ  -bitoffset  1 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IECR -name FIQ    -bitoffset  0 -width 1

#
# AIC_IDCR
#
imodeladdfield -mmregister bp1/REG/AIC_IDCR -name IRQ2   -bitoffset 18 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IDCR -name IRQ1   -bitoffset 17 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IDCR -name IRQ0   -bitoffset 16 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IDCR -name PIOIRQ -bitoffset  8 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IDCR -name WDIRQ  -bitoffset  7 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IDCR -name TC2IRQ -bitoffset  6 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IDCR -name TC1IRQ -bitoffset  5 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IDCR -name TC0IRQ -bitoffset  4 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IDCR -name US1IRQ -bitoffset  3 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IDCR -name US0IRQ -bitoffset  2 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IDCR -name SWIRQ  -bitoffset  1 -width 1
imodeladdfield -mmregister bp1/REG/AIC_IDCR -name FIQ    -bitoffset  0 -width 1

#
# AIC_ICCR
#
imodeladdfield -mmregister bp1/REG/AIC_ICCR -name IRQ2   -bitoffset 18 -width 1
imodeladdfield -mmregister bp1/REG/AIC_ICCR -name IRQ1   -bitoffset 17 -width 1
imodeladdfield -mmregister bp1/REG/AIC_ICCR -name IRQ0   -bitoffset 16 -width 1
imodeladdfield -mmregister bp1/REG/AIC_ICCR -name PIOIRQ -bitoffset  8 -width 1
imodeladdfield -mmregister bp1/REG/AIC_ICCR -name WDIRQ  -bitoffset  7 -width 1
imodeladdfield -mmregister bp1/REG/AIC_ICCR -name TC2IRQ -bitoffset  6 -width 1
imodeladdfield -mmregister bp1/REG/AIC_ICCR -name TC1IRQ -bitoffset  5 -width 1
imodeladdfield -mmregister bp1/REG/AIC_ICCR -name TC0IRQ -bitoffset  4 -width 1
imodeladdfield -mmregister bp1/REG/AIC_ICCR -name US1IRQ -bitoffset  3 -width 1
imodeladdfield -mmregister bp1/REG/AIC_ICCR -name US0IRQ -bitoffset  2 -width 1
imodeladdfield -mmregister bp1/REG/AIC_ICCR -name SWIRQ  -bitoffset  1 -width 1
imodeladdfield -mmregister bp1/REG/AIC_ICCR -name FIQ    -bitoffset  0 -width 1

#
# AIC_ISCR
#
imodeladdfield -mmregister bp1/REG/AIC_ISCR -name IRQ2   -bitoffset 18 -width 1
imodeladdfield -mmregister bp1/REG/AIC_ISCR -name IRQ1   -bitoffset 17 -width 1
imodeladdfield -mmregister bp1/REG/AIC_ISCR -name IRQ0   -bitoffset 16 -width 1
imodeladdfield -mmregister bp1/REG/AIC_ISCR -name PIOIRQ -bitoffset  8 -width 1
imodeladdfield -mmregister bp1/REG/AIC_ISCR -name WDIRQ  -bitoffset  7 -width 1
imodeladdfield -mmregister bp1/REG/AIC_ISCR -name TC2IRQ -bitoffset  6 -width 1
imodeladdfield -mmregister bp1/REG/AIC_ISCR -name TC1IRQ -bitoffset  5 -width 1
imodeladdfield -mmregister bp1/REG/AIC_ISCR -name TC0IRQ -bitoffset  4 -width 1
imodeladdfield -mmregister bp1/REG/AIC_ISCR -name US1IRQ -bitoffset  3 -width 1
imodeladdfield -mmregister bp1/REG/AIC_ISCR -name US0IRQ -bitoffset  2 -width 1
imodeladdfield -mmregister bp1/REG/AIC_ISCR -name SWIRQ  -bitoffset  1 -width 1
imodeladdfield -mmregister bp1/REG/AIC_ISCR -name FIQ    -bitoffset  0 -width 1


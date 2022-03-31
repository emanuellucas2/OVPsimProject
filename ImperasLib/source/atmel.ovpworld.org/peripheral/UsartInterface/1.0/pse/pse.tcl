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
set name    UsartInterface
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor

iadddocumentation -name Description -text "USART: Universal Synchronous/Asynchronous Receiver Transmitter
This model contains an accurate Register set interface.
The functionality has only been implemented to sufficiently boot uClinux.
The USART has its own baud rate generator, and two dedicated Peripheral Data Controller.
channels. The data format includes a start bit, up to 8 data bits, an optional programmable parity bit and up to 2 stop bits.
The USART also features a Receiver Timeout register, facilitating variable length frame support
when it is working with the PDC, and a Time-guard register, used when interfacing with slow remote equipment.
for more information visit http://www.atmel.com/products/at91"

iadddocumentation  \
-name Licensing  \
-text "Open Source Apache 2.0"

iadddocumentation -name Limitations -text "This model is sufficient to boot Linux"
iadddocumentation -name Reference   -text "Rev. 1354D ARM08/02"

imodeladdbusslaveport -name apb -mustbeconnected -size 0x4000
imodeladdbusmasterport -name asb -mustbeconnected -addresswidth 32
imodeladdaddressblock -name REG -port apb -size 0x4000 -offset 0 -width 32

imodeladdformalmacro -name BHM_SER_OPEN_AUTO_FORMALS
imodeladdformalmacro -name BHM_RECORD_REPLAY_FORMALS

#
# Interrupt Signal Block output
#
imodeladdnetport -name IRQ -type output

set registers {
  US_CR   0x00 w  0x0  - US_CR_wcb
  US_MR   0x04 rw 0x0  - US_MR_wcb
  US_IER  0x08 w  0x0  - US_IER_wcb
  US_IDR  0x0c w  0x0  - US_IDR_wcb
  US_IMR  0x10 r  0x0  - -
  US_CSR  0x14 r  0x18 US_RHR_rcb -
  US_RHR  0x18 r  0x0  - -
  US_THR  0x1c w  0x0  - US_THR_wcb
  US_BRGR 0x20 rw 0x0  - US_BRGR_wcb
  US_RTOR 0x24 rw 0x0  - US_RTOR_wcb
  US_TTGR 0x28 rw 0x0  - US_TTGR_wcb
  US_RSV0 0x2c -  0x0  - -
  US_RPR  0x30 rw 0x0  - US_RPR_wcb
  US_RCR  0x34 rw 0x0  - US_RCR_wcb
  US_TPR  0x38 rw 0x0  - US_TPR_wcb
  US_TCR  0x3c rw 0x0  - US_TCR_wcb
}

foreach {rname roffset raccess reset readFunc writeFunc} $registers {
  # Ignore reserved registers
  if {$raccess == "-"} {continue}

  set command "imodeladdmmregister -addressblock apb/REG -name $rname -width 32 -offset $roffset -access $raccess"
  if { $readFunc != "-" } {
    set command "${command} -readfunction $readFunc"
  }
  if { $writeFunc != "-" } {
    set command "${command} -writefunction $writeFunc"
  }
  
  eval $command

  imodeladdreset -mmregister apb/REG/$rname -name resetNet -value $reset
}


#
# US_CR
#
imodeladdfield -mmregister apb/REG/US_CR -name SENDA  -bitoffset 12 -width 1
imodeladdfield -mmregister apb/REG/US_CR -name STTTO  -bitoffset 11 -width 1
imodeladdfield -mmregister apb/REG/US_CR -name STPBRK -bitoffset 10 -width 1
imodeladdfield -mmregister apb/REG/US_CR -name STTBRK -bitoffset  9 -width 1
imodeladdfield -mmregister apb/REG/US_CR -name RSTSTA -bitoffset  8 -width 1
imodeladdfield -mmregister apb/REG/US_CR -name TXDIS  -bitoffset  7 -width 1
imodeladdfield -mmregister apb/REG/US_CR -name TXEN   -bitoffset  6 -width 1
imodeladdfield -mmregister apb/REG/US_CR -name RXDIS  -bitoffset  5 -width 1
imodeladdfield -mmregister apb/REG/US_CR -name RXEN   -bitoffset  4 -width 1
imodeladdfield -mmregister apb/REG/US_CR -name RSTTX  -bitoffset  3 -width 1
imodeladdfield -mmregister apb/REG/US_CR -name RSTRX  -bitoffset  2 -width 1

#
# US_MR
#
imodeladdfield -mmregister apb/REG/US_MR -name CLKO   -bitoffset 18 -width 1
imodeladdfield -mmregister apb/REG/US_MR -name MODE9  -bitoffset 17 -width 1
imodeladdfield -mmregister apb/REG/US_MR -name CHMODE -bitoffset 14 -width 2
imodeladdfield -mmregister apb/REG/US_MR -name NBSTOP -bitoffset 12 -width 2
imodeladdfield -mmregister apb/REG/US_MR -name PAR    -bitoffset 9 -width 3
imodeladdfield -mmregister apb/REG/US_MR -name SYNC   -bitoffset 8 -width 1
imodeladdfield -mmregister apb/REG/US_MR -name CHRL   -bitoffset 6 -width 2
imodeladdfield -mmregister apb/REG/US_MR -name HSCLKS -bitoffset 4 -width 2

#
# US_IER
#
imodeladdfield -mmregister apb/REG/US_IER -name TXEMPTY -bitoffset 9 -width 1
imodeladdfield -mmregister apb/REG/US_IER -name TIMEOUT -bitoffset 8 -width 1
imodeladdfield -mmregister apb/REG/US_IER -name PARE    -bitoffset 7 -width 1
imodeladdfield -mmregister apb/REG/US_IER -name FRAME   -bitoffset 6 -width 1
imodeladdfield -mmregister apb/REG/US_IER -name OVRE    -bitoffset 5 -width 1
imodeladdfield -mmregister apb/REG/US_IER -name ENDTX   -bitoffset 4 -width 1
imodeladdfield -mmregister apb/REG/US_IER -name ENDRX   -bitoffset 3 -width 1
imodeladdfield -mmregister apb/REG/US_IER -name RXBRK   -bitoffset 2 -width 1
imodeladdfield -mmregister apb/REG/US_IER -name TXRDY   -bitoffset 1 -width 1
imodeladdfield -mmregister apb/REG/US_IER -name RXRDY   -bitoffset 0 -width 1

#
# US_IDR
#
imodeladdfield -mmregister apb/REG/US_IDR -name TXEMPTY -bitoffset 9 -width 1
imodeladdfield -mmregister apb/REG/US_IDR -name TIMEOUT -bitoffset 8 -width 1
imodeladdfield -mmregister apb/REG/US_IDR -name PARE    -bitoffset 7 -width 1
imodeladdfield -mmregister apb/REG/US_IDR -name FRAME   -bitoffset 6 -width 1
imodeladdfield -mmregister apb/REG/US_IDR -name OVRE    -bitoffset 5 -width 1
imodeladdfield -mmregister apb/REG/US_IDR -name ENDTX   -bitoffset 4 -width 1
imodeladdfield -mmregister apb/REG/US_IDR -name ENDRX   -bitoffset 3 -width 1
imodeladdfield -mmregister apb/REG/US_IDR -name RXBRK   -bitoffset 2 -width 1
imodeladdfield -mmregister apb/REG/US_IDR -name TXRDY   -bitoffset 1 -width 1
imodeladdfield -mmregister apb/REG/US_IDR -name RXRDY   -bitoffset 0 -width 1

#
# US_IMR
#
imodeladdfield -mmregister apb/REG/US_IMR -name TXEMPTY -bitoffset 9 -width 1
imodeladdfield -mmregister apb/REG/US_IMR -name TIMEOUT -bitoffset 8 -width 1
imodeladdfield -mmregister apb/REG/US_IMR -name PARE    -bitoffset 7 -width 1
imodeladdfield -mmregister apb/REG/US_IMR -name FRAME   -bitoffset 6 -width 1
imodeladdfield -mmregister apb/REG/US_IMR -name OVRE    -bitoffset 5 -width 1
imodeladdfield -mmregister apb/REG/US_IMR -name ENDTX   -bitoffset 4 -width 1
imodeladdfield -mmregister apb/REG/US_IMR -name ENDRX   -bitoffset 3 -width 1
imodeladdfield -mmregister apb/REG/US_IMR -name RXBRK   -bitoffset 2 -width 1
imodeladdfield -mmregister apb/REG/US_IMR -name TXRDY   -bitoffset 1 -width 1
imodeladdfield -mmregister apb/REG/US_IMR -name RXRDY   -bitoffset 0 -width 1

#
# US_CSR
#
imodeladdfield -mmregister apb/REG/US_CSR -name TXEMPTY -bitoffset 9 -width 1
imodeladdfield -mmregister apb/REG/US_CSR -name TIMEOUT -bitoffset 8 -width 1
imodeladdfield -mmregister apb/REG/US_CSR -name PARE    -bitoffset 7 -width 1
imodeladdfield -mmregister apb/REG/US_CSR -name FRAME   -bitoffset 6 -width 1
imodeladdfield -mmregister apb/REG/US_CSR -name OVRE    -bitoffset 5 -width 1
imodeladdfield -mmregister apb/REG/US_CSR -name ENDTX   -bitoffset 4 -width 1
imodeladdfield -mmregister apb/REG/US_CSR -name ENDRX   -bitoffset 3 -width 1
imodeladdfield -mmregister apb/REG/US_CSR -name RXBRK   -bitoffset 2 -width 1
imodeladdfield -mmregister apb/REG/US_CSR -name TXRDY   -bitoffset 1 -width 1
imodeladdfield -mmregister apb/REG/US_CSR -name RXRDY   -bitoffset 0 -width 1

#
# US_RHR
#
imodeladdfield -mmregister apb/REG/US_RHR -name RXCHR -bitoffset 0 -width 8

#
# US_THR
#
imodeladdfield -mmregister apb/REG/US_THR -name TXCHR -bitoffset 0 -width 8

#
# US_BRGR
#
imodeladdfield -mmregister apb/REG/US_BRGR -name CD -bitoffset 0 -width 16

#
# US_RTOR
#
imodeladdfield -mmregister apb/REG/US_RTOR -name TO -bitoffset 0 -width 8

#
# US_TTGR
#
imodeladdfield -mmregister apb/REG/US_TTGR -name TG -bitoffset 0 -width 8

#
# US_RPR
#
imodeladdfield -mmregister apb/REG/US_RPR -name RXPTR -bitoffset 0 -width 32

#
# US_RCR
#
imodeladdfield -mmregister apb/REG/US_RCR -name RXCTR -bitoffset 0 -width 16

#
# US_TPR
#
imodeladdfield -mmregister apb/REG/US_TPR -name TXPTR -bitoffset 0 -width 32

#
# US_TCR
#
imodeladdfield -mmregister apb/REG/US_TCR -name TXCTR -bitoffset 0 -width 16


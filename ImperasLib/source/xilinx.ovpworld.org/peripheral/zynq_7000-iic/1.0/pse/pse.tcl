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

set vendor  xilinx.ovpworld.org
set library peripheral
set name    zynq_7000-iic
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor

iadddocumentation  \
    -name Description  \
    -text "Zynq 7000 I2C Registers. This model also includes the behaviour for PCA9548 I2C Bus Switch"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "This model implements the full set of registers and behaviour to read and write the I2C address space."

iadddocumentation -name Reference -text "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)."
iadddocumentation -name Reference -text "Evaluation Board ZC706 (ug954-zc706-eval-board-xc7z045-ap-soc.pdf)"
iadddocumentation -name Reference -text "Evaluation Board ZC702 (ug850-zc702-eval-board.pdf)"

# I2C interface connections
# I2C Master port
imodeladdbusmasterport  -name I2C_Master -addresswidthmin 10 -addresswidthmax 32
# I2C Slave port
imodeladdbusslaveport   -name I2C_Slave  -size 4
imodeladdaddressblock   -name dr -port I2C_Slave -size 4 -offset 0 -width 32
imodeladdlocalmemory    -name buff -addressblock I2C_Slave/dr -size 4 -writefunction i2cSlaveWrite -readfunction i2cSlaveRead

set port  bport1
set block ab
set size  0x1000

imodeladdbusslaveport  -name ${port} -mustbeconnected -size ${size}
imodeladdaddressblock  -name ${block} -port ${port} -size ${size} -offset 0 -width 32

set registers {
    REG  Control                0x00000000 16 rw 0x00000000 -       wrControl  0xff7f {DIV_A 14 2 DIV_B 8 6 CLR_FIFO 6 1 SLVMON 5 1 HOLD 4 1 ACKEN 3 1 NEA 2 1 MS 1 1 RW 0 1 } "Control register"
    MEM  Status                 0x00000004 16 rw 0x00000000 -       wrStatus   -      {BA 8 1 RXOVF 7 1 TXDV 6 1 RXDV 5 1 RXRW 3 1} "Status register"
    REG  I2CAddress             0x00000008 16 rw 0x00000000 -       wrAddress  0x03ff {ADD  0 9} "I2C Address register"
    REG  I2CData                0x0000000c 16 rw 0x00000000 rdData  wrData     0x00ff {DATA 0 8} "I2C Data register"
    MEM  InterruptStatus        0x00000010 16 rw 0x00000000 -       intClear   0x02ff {ARB_LOST 9 1 RX_UNF 7 1 TX_OVF 6 1 RX_OVF 5 1 SLV_RDY 4 1 TO 3 1 NACK 2 1 DATA 1 1 COMP 0 1} "I2C Interrupt Status register"
    REG  TransferSize           0x00000014  8 rw 0x00000000 rdXSz   wrXSz      0x00ff {XFERSZ 0 8} "Transfer Size register"
    REG  SlaveMonPause          0x00000018  8 rw 0x00000000 -       -          0x000f {PAUSE 0 8} "Slave Monitor Pause register"
    REG  TimeOut                0x0000001c  8 rw 0x0000001f -       -          0x00ff {TO 0 8} 	"Time Out register"
    REG  InterruptMask          0x00000020 16 r  0x000002ff -       -          -      {ARB_LOST 9 1 RX_UNF 7 1 TX_OVF 6 1 RX_OVF 5 1 SLV_RDY 4 1 TO 3 1 NACK 2 1 DATA 1 1 COMP 0 1} "Interrupt Mask register"
    REG  InterruptEnable        0x00000024 16 rw 0x00000000 rdZero  intEnable  0x02ff {ARB_LOST 9 1 RX_UNF 7 1 TX_OVF 6 1 RX_OVF 5 1 SLV_RDY 4 1 TO 3 1 NACK 2 1 DATA 1 1 COMP 0 1} "Interrupt Enable register"
    REG  InterruptDisable       0x00000028 16 rw 0x00000000 rdZero  intDisable 0x02ff {ARB_LOST 9 1 RX_UNF 7 1 TX_OVF 6 1 RX_OVF 5 1 SLV_RDY 4 1 TO 3 1 NACK 2 1 DATA 1 1 COMP 0 1} "Interrupt Disable register"
}

# Add undefined callback across rest of register space
set LASTREGOFFSET 0x28
imodeladdlocalmemory -name buffer1 -addressblock ${port}/${block} \
                     -offset [expr         ($LASTREGOFFSET+4)] \
                     -size   [expr ${size}-($LASTREGOFFSET+4)] \
                     -writefunction regNoDefinitionWrite -readfunction regNoDefinitionRead

foreach {it rname roffset rsize raccess reset readFunc writeFunc writeMask bits description} $registers {

    if { $it == "MEM" } {

        # optimize with memory so polling has zero overhead (remove NO readfunction callback)
        set command "imodeladdlocalmemory -addressblock ${port}/${block} -name $rname -size $rsize -offset $roffset -access $raccess"
        if { $writeFunc == "-" } {
          set defaultcb 1
        } elseif { $writeFunc == "auto" } {
          set command "${command} -writefunction Write${rname}"
        } else {
          set command "${command} -writefunction $writeFunc"
        }

        eval $command
        
    } else {
      # Ignore reserved registers
      if {$raccess == "-"} {continue}
      # All registers accessed as 32-bit
      if {$rsize != 32} {set rsize 32}
    
      set command "imodeladdmmregister -addressblock ${port}/${block} -name $rname -width $rsize -offset $roffset -access $raccess"
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
      
      if { $bits != "-" } {
        foreach { n o w } $bits {
            imodeladdfield -mmregister $port/$block/$rname -bitoffset $o -width $w -name $n
        }
      }
      
      imodeladdreset -mmregister ${port}/${block}/$rname -name resetNet -value $reset
    }

    if { $description != "-" } {
        iadddocumentation  -handle ${port}/${block}/$rname \
                           -name Description  \
                           -text $description
    }
}

imodeladdnetport -name intOut -type output

set defaultPCLK 133
imodeladdformal -defaultvalue $defaultPCLK -name PCLK -type uns32
iadddocumentation  -handle PCLK -name Description -text "The Peripheral clock frequency in MHz (default $defaultPCLK MHz)"
 

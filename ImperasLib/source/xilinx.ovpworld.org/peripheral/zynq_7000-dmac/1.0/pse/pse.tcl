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
set name    zynq_7000-dmac
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor 

iadddocumentation  \
    -name Description  \
    -text "Zynq 7000 Platform DMA Controller (DMAC)"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "This model implements the full set of registers. There is no behavior included."

iadddocumentation \
    -name Reference \
    -text "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)"


#   rname roffset rsize raccess resetN resetS readFunc writeFunc writeMask bits description
set registers {
    DSR           0x00000000 32 rw 0x00000000 -          -    -    0x000001ff    -    "DMA Manager Status"
    DPC           0x00000004 32 rw 0x00000000 -          -    -    0xffffffff    -    "DMA Program Counter"
    INTEN         0x00000020 32 rw 0x00000000 -          -    -    0xffffffff    -    "DMASEV Instruction Response Control"
    INT_EVENT_RIS 0x00000024 32 rw 0x00000000 -          -    -    0xffffffff    -    "Event Interrupt Raw Status"
    INTMIS        0x00000028 32 rw 0x00000000 -          -    -    0xffffffff    -    "Interrupt Status"
    INTCLR        0x0000002C 32 rw 0x00000000 -          -    -    0xffffffff    -    "Interrupt Clear"
    FSRD          0x00000030 32 rw 0x00000000 -          -    -    0xffffffff    -    "Fault Status DMA Manager"
    FSRC          0x00000034 32 rw 0x00000000 -          -    -    0xffffffff    -    "Fault Status DMA Channel"
    FTRD          0x00000038 32 rw 0x00000000 -          -    -    0xffffffff    -    "Fault Type DMA Manager"
    FTR0          0x00000040 32 rw 0x00000000 -          -    -    0xffffffff    -    "Default Type DMA Channel 0"
    FTR1          0x00000044 32 rw 0x00000000 -          -    -    0xffffffff    -    "Default Type DMA Channel 1"
    FTR2          0x00000048 32 rw 0x00000000 -          -    -    0xffffffff    -    "Default Type DMA Channel 2"
    FTR3          0x0000004C 32 rw 0x00000000 -          -    -    0xffffffff    -    "Default Type DMA Channel 3"
    FTR4          0x00000050 32 rw 0x00000000 -          -    -    0xffffffff    -    "Default Type DMA Channel 4"
    FTR5          0x00000054 32 rw 0x00000000 -          -    -    0xffffffff    -    "Default Type DMA Channel 5"
    FTR6          0x00000058 32 rw 0x00000000 -          -    -    0xffffffff    -    "Default Type DMA Channel 6"
    FTR7          0x0000005C 32 rw 0x00000000 -          -    -    0xffffffff    -    "Default Type DMA Channel 7"
    CSR0          0x00000100 32 rw 0x00000000 -          -    -    0xffffffff    -    "Channel Status DMA Channel 0"
    CPC0          0x00000104 32 rw 0x00000000 -          -    -    0xffffffff    -    "Channel PC for DMA Channel 0"
    CSR1          0x00000108 32 rw 0x00000000 -          -    -    0xffffffff    -    "Channel Status DMA Channel 1"
    CPC1          0x0000010C 32 rw 0x00000000 -          -    -    0xffffffff    -    "Channel PC for DMA Channel 1"
    CSR2          0x00000110 32 rw 0x00000000 -          -    -    0xffffffff    -    "Channel Status DMA Channel 2"
    CPC2          0x00000114 32 rw 0x00000000 -          -    -    0xffffffff    -    "Channel PC for DMA Channel 2"
    CSR3          0x00000118 32 rw 0x00000000 -          -    -    0xffffffff    -    "Channel Status DMA Channel 3"
    CPC3          0x0000011C 32 rw 0x00000000 -          -    -    0xffffffff    -    "Channel PC for DMA Channel 3"
    CSR4          0x00000120 32 rw 0x00000000 -          -    -    0xffffffff    -    "Channel Status DMA Channel 4"
    CPC4          0x00000124 32 rw 0x00000000 -          -    -    0xffffffff    -    "Channel PC for DMA Channel 4"
    CSR5          0x00000128 32 rw 0x00000000 -          -    -    0xffffffff    -    "Channel Status DMA Channel 5"
    CPC5          0x0000012C 32 rw 0x00000000 -          -    -    0xffffffff    -    "Channel PC for DMA Channel 5"
    CSR6          0x00000130 32 rw 0x00000000 -          -    -    0xffffffff    -    "Channel Status DMA Channel 6"
    CPC6          0x00000134 32 rw 0x00000000 -          -    -    0xffffffff    -    "Channel PC for DMA Channel 6"
    CSR7          0x00000138 32 rw 0x00000000 -          -    -    0xffffffff    -    "Channel Status DMA Channel 7"
    CPC7          0x0000013C 32 rw 0x00000000 -          -    -    0xffffffff    -    "Channel PC for DMA Channel 7"
    SAR0          0x00000400 32 rw 0x00000000 -          -    -    0xffffffff    -    "Source Address DMA Channel 0"
    DAR0          0x00000404 32 rw 0x00000000 -          -    -    0xffffffff    -    "Destination Addr DMA Channel 0"
    CCR0          0x00000408 32 rw 0x00000000 0x00800200 -    -    0xffffffff    -    "Channel Control DMA Channel 0 (dmac0_ns: 0x00000000 dmac0_s: 0x00800200)"
    LC0_0         0x0000040C 32 rw 0x00000000 -          -    -    0xffffffff    -    "Loop Counter 0 DMA Channel 0"
    LC1_0         0x00000410 32 rw 0x00000000 -          -    -    0xffffffff    -    "Loop Counter 1 DMA Channel 0"
    SAR1          0x00000420 32 rw 0x00000000 -          -    -    0xffffffff    -    "Source address DMA Channel 1"
    DAR1          0x00000424 32 rw 0x00000000 -          -    -    0xffffffff    -    "Destination Addr DMA Channel 1"
    CCR1          0x00000428 32 rw 0x00000000 0x00800200 -    -    0xffffffff    -    "Channel Control DMA Channel 1 (dmac0_ns: 0x00000000 dmac0_s: 0x00800200 )"
    LC0_1         0x0000042C 32 rw 0x00000000 -          -    -    0xffffffff    -    "Loop Counter 0 DMA Channel 1"
    LC1_1         0x00000430 32 rw 0x00000000 -          -    -    0xffffffff    -    "Loop Counter 1 DMA Channel 1"
    SAR2          0x00000440 32 rw 0x00000000 -          -    -    0xffffffff    -    "Source Address DMA Channel 2"
    DAR2          0x00000444 32 rw 0x00000000 -          -    -    0xffffffff    -    "Destination Addr DMA Channel 2"
    CCR2          0x00000448 32 rw 0x00000000 0x00800200 -    -    0xffffffff    -    "Channel Control DMA Channel 2 (dmac0_ns: 0x00000000 dmac0_s: 0x00800200 )"
    LC0_2         0x0000044C 32 rw 0x00000000 -          -    -    0xffffffff    -    "Loop Counter 0 DMA Channel 2"
    LC1_2         0x00000450 32 rw 0x00000000 -          -    -    0xffffffff    -    "Loop Counter 1 DMA Channel 2"
    SAR3          0x00000460 32 rw 0x00000000 -          -    -    0xffffffff    -    "Source Address DMA Channel 3"
    DAR3          0x00000464 32 rw 0x00000000 -          -    -    0xffffffff    -    "Destination Addr DMA Channel 3"
    CCR3          0x00000468 32 rw 0x00000000 0x00800200 -    -    0xffffffff    -    "Channel Control DMA Channel 3 (dmac0_ns: 0x00000000 dmac0_s: 0x00800200)"
    LC0_3         0x0000046C 32 rw 0x00000000 -          -    -    0xffffffff    -    "Loop Counter 0 DMA Channel 3"
    LC1_3         0x00000470 32 rw 0x00000000 -          -    -    0xffffffff    -    "Loop Counter 1 DMA Channel 3"
    SAR4          0x00000480 32 rw 0x00000000 -          -    -    0xffffffff    -    "Source Address DMA Channel 4"
    DAR4          0x00000484 32 rw 0x00000000 -          -    -    0xffffffff    -    "Destination Addr DMA Channel 4"
    CCR4          0x00000488 32 rw 0x00000000 0x00800200 -    -    0xffffffff    -    "Channel Control DMA Channel 4 (dmac0_ns: 0x00000000 dmac0_s: 0x00800200 )"
    LC0_4         0x0000048C 32 rw 0x00000000 -          -    -    0xffffffff    -    "Loop Counter 0 DMA Channel 4"
    LC1_4         0x00000490 32 rw 0x00000000 -          -    -    0xffffffff    -    "Loop Counter 1 DMA Channel 4"
    SAR5          0x000004A0 32 rw 0x00000000 -          -    -    0xffffffff    -    "Source Address DMA Channel 5"
    DAR5          0x000004A4 32 rw 0x00000000 -          -    -    0xffffffff    -    "Destination Addr DMA Channel 5"
    CCR5          0x000004A8 32 rw 0x00000000 0x00800200 -    -    0xffffffff    -    "Channel Control DMA Channel 5 (dmac0_ns: 0x00000000 dmac0_s: 0x00800200 )"
    LC0_5         0x000004AC 32 rw 0x00000000 -          -    -    0xffffffff    -    "Loop Counter 0 DMA Channel 5"
    LC1_5         0x000004B0 32 rw 0x00000000 -          -    -    0xffffffff    -    "Loop Counter 1 DMA Channel 5"
    SAR6          0x000004C0 32 rw 0x00000000 -          -    -    0xffffffff    -    "Source Address DMA Channel 6"
    DAR6          0x000004C4 32 rw 0x00000000 -          -    -    0xffffffff    -    "Destination Addr DMA Channel 6"
    CCR6          0x000004C8 32 rw 0x00000000 0x00800200 -    -    0xffffffff    -    "Channel Control DMA Channel 6 (dmac0_ns: 0x00000000 dmac0_s: 0x00800200 )"
    LC0_6         0x000004CC 32 rw 0x00000000 -          -    -    0xffffffff    -    "Loop Counter 0 DMA Channel 6"
    LC1_6         0x000004D0 32 rw 0x00000000 -          -    -    0xffffffff    -    "Loop Counter 1 DMA Channel 6"
    SAR7          0x000004E0 32 rw 0x00000000 -          -    -    0xffffffff    -    "Source Address DMA Channel 7"
    DAR7          0x000004E4 32 rw 0x00000000 -          -    -    0xffffffff    -    "Destination Addr DMA Channel 7"
    CCR7          0x000004E8 32 rw 0x00000000 0x00800200 -    -    0xffffffff    -    "Channel Control DMA Channel 7 (dmac0_ns: 0x00000000 dmac0_s: 0x00800200 )"
    LC0_7         0x000004EC 32 rw 0x00000000 -          -    -    0xffffffff    -    "Loop Counter 0 DMA Channel 7"
    LC1_7         0x000004F0 32 rw 0x00000000 -          -    -    0xffffffff    -    "Loop Counter 1 DMA Channel 7"
    DBGSTATUS     0x00000D00 32 rw 0x00000000 -          -    -    0xffffffff    -    "DMA Manager Execution Status"
    DBGCMD        0x00000D04 32 rw 0x00000000 -          -    -    0xffffffff    -    "DMA Manager Instr. command "
    DBGINST0      0x00000D08 32 rw 0x00000000 -          -    -    0xffffffff    -    "DMA Manager Instruction Part A"
    DBGINST1      0x00000D0C 32 rw 0x00000000 -          -    -    0xffffffff    -    "DMA Manager Instruction Part B"
    CR0           0x00000E00 32 rw 0x00000000 0x001E3071 -    -    0xffffffff    -    "Config. 0: Events, Peripheral Interfaces, PC, Mode (dmac0_ns: 0x00000000 dmac0_s: 0x001E3071 )"
    CR1           0x00000E04 32 rw 0x00000000 0x00000074 -    -    0xffffffff    -    "Config. 1: Instruction Cache (dmac0_ns: 0x00000000 dmac0_s: 0x00000074 )"
    CR2           0x00000E08 32 rw 0x00000000 -          -    -    0xffffffff    -    "Config. 2: DMA Mgr Boot Addr"
    CR3           0x00000E0C 32 rw 0x00000000 -          -    -    0xffffffff    -    "Config. 3: Security state of IRQs"
    CR4           0x00000E10 32 rw 0x00000000 -          -    -    0xffffffff    -    "Config 4, Security of Periph Interfaces"
    CRD           0x00000E14 32 rw 0x00000000 0x07FF7F73 -    -    0xffffffff    -    "DMA configuration (dmac0_ns: 0x00000000 dmac0_s: 0x07FF7F73 )"
    WD            0x00000E80 32 rw 0x00000000 -          -    -    0xffffffff    -    "Watchdog Timer"
    periph_id_0   0x00000FE0 32 rw 0x00000000 0x00000030 -    -    0xffffffff    -    "Peripheral Identification register 0 (dmac0_ns: 0x00000000 dmac0_s: 0x00000030 )"
    periph_id_1   0x00000FE4 32 rw 0x00000000 0x00000013 -    -    0xffffffff    -    "Peripheral Identification register 1 (dmac0_ns: 0x00000000 dmac0_s: 0x00000013 )"
    periph_id_2   0x00000FE8 32 rw 0x00000000 0x00000024 -    -    0xffffffff    -    "Peripheral Identification register 2 (dmac0_ns: 0x00000000 dmac0_s: 0x00000024 )"
    periph_id_3   0x00000FEC 32 rw 0x00000000 -          -    -    0xffffffff    -    "Peripheral Identification register 3"
    pcell_id_0    0x00000FF0 32 rw 0x00000000 0x0000000D -    -    0xffffffff    -    "Component Identification register 0 (dmac0_ns: 0x00000000 dmac0_s: 0x0000000D)"
    pcell_id_1    0x00000FF4 32 rw 0x00000000 0x000000F0 -    -    0xffffffff    -    "Component Identification register 1 (dmac0_ns: 0x00000000 dmac0_s: 0x000000F0)"
    pcell_id_2    0x00000FF8 32 rw 0x00000000 0x00000005 -    -    0xffffffff    -    "Component Identification register 2 (dmac0_ns: 0x00000000 dmac0_s: 0x00000005)"
    pcell_id_3    0x00000FFC 32 rw 0x00000000 0x000000B1 -    -    0xffffffff    -    "Component Identification register 3 (dmac0_ns: 0x00000000 dmac0_s: 0x000000B1)"
}

set size  0x1000

# Two ports (secure and non-secure)
foreach type {"S" "NS"} {
    set port "bport${type}"
    set block "ab${type}"

    imodeladdbusslaveport  -name ${port} -mustbeconnected -size ${size}
    imodeladdaddressblock  -name ${block} -port ${port} -size ${size} -offset 0 -width 32
    
    imodeladdlocalmemory -name buffer -addressblock ${port}/${block} -size ${size} \
                         -writefunction regNoDefinitionWrite${type} -readfunction regNoDefinitionRead${type}
                         
    
    foreach {rname roffset rsize raccess resetNS resetS readFunc writeFunc writeMask bits description} $registers {
      # Ignore reserved registers
      if {$raccess == "-"} {continue}
      if {$rsize != "32"} {
          set rsize 32
    #      puts"Register $rname is not 32-bits ignored"
    #      continue
      }
    
      set command "imodeladdmmregister -addressblock ${port}/${block} -name $rname -width 32 -offset $roffset -access $raccess"
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
        foreach { n o w } $bits {
            imodeladdfield -mmregister $port/$block/$rname -bitoffset $o -width $w -name $n
        }
      }
      
      # there are two possible reset values but only one can be assigned here
      if { ($type == "S") && ($resetS != "-") } {
          imodeladdreset -mmregister ${port}/${block}/$rname -name resetNet -value $resetS
      } else {
          imodeladdreset -mmregister ${port}/${block}/$rname -name resetNet -value $resetNS
      }
    }
}

imodeladdnetport -name Int%u -type output -loarray 0 -hiarray 7
iadddocumentation -name Description -text " DMAC Interrupt"

imodeladdnetport -name inta -type output
iadddocumentation -name Description -text "Interrupt DMAC Transfer Abort"
 

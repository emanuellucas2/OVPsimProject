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

set range    0x1000
set regWidth 32

imodelnewperipheral \
    -imagefile pse.pse \
    -name MmciPL181 \
    -vendor  arm.ovpworld.org  \
    -library peripheral \
    -version 1.0 \
    -constructor constructor \
    -destructor  destructor    \
    -extensionfile model \
    -releasestatus ovp

iadddocumentation -name Description -text "ARM PrimeCell Multimedia Card Interface (MMCI)"
iadddocumentation -name Limitations -text "None"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
# Cannot find "PL181" manual!
iadddocumentation -name Reference   -text "ARM PrimeCell Multimedia Card Interface (Pl180) Technical Reference Manual (ARM DDI 0172)"

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab -port bport1 -width $regWidth -size $range

set addBlock     "bport1/ab"

#   name       offset ac  description         readFn     writeFn    reset bits
set registers {
    power      0x00   rw  "Power Control"     -          write8     -    -
    clock      0x04   rw  "Clock Control"     -          writeClock -    -
    cmdarg     0x08   rw  "Command Arguments" -          writeArg   -    -
    cmd        0x0c   rw  "Command"           -          writeCmd   -  
    {
        C_INDEX     0
        C_RESPONSE  6
        C_LONGRESP  7
        C_INTERRUPT 8
        C_PENDING   9
        C_ENABLE    10
    }
    respcmd    0x10   r   "RESP Command"      -          -          -     -
    response0  0x14   r   "Response 0"        -          -          -     -
    response1  0x18   r   "Response 1"        -          -          -     -
    response2  0x1c   r   "Response 2"        -          -          -     -
    response3  0x20   r   "Response 3"        -          -          -     -
    datatimer  0x24   rw  "Data Timer"        -          -          -     -
    datalength 0x28   rw  "Data Length"       -          writeDL    -     -
    datactrl   0x2c   rw  "Data Control"      -          writeDC    -     
    {
        D_ENABLE       0
        D_DIRECTION    1
        D_MODE         2
        D_DMAENABLE    3
    }
    datacnt    0x30   r  "Data Count"         -          -          -    -
    status     0x34   r  "Data Count"         readStatus -          -    
    {
        S_CMDCRCFAIL      0
        S_DATACRCFAIL     1
        S_CMDTIMEOUT      2
        S_DATATIMEOUT     3
        S_TXUNDERRUN      4
        S_RXOVERRUN       5
        S_CMDRESPEND      6
        S_CMDSENT         7
        S_DATAEND         8
        S_DATABLOCKEND    10
        S_CMDACTIVE       11
        S_TXACTIVE        12
        S_RXACTIVE        13
        S_TXFIFOHALFEMPTY 14
        S_RXFIFOHALFFULL  15
        S_TXFIFOFULL      16
        S_RXFIFOFULL      17
        S_TXFIFOEMPTY     18
        S_RXFIFOEMPTY     19
        S_TXDATAAVLBL     20
        S_RXDATAAVLBL     21
    }
    clear      0x38   w  "Clear"              -           writeClear -      -
    mask0      0x3c   rw "Mask 0"             -           writeMask0 -      -
    mask1      0x40   rw "Mask 1"             -           writeMask1 -      -
    fifoCnt    0x48   r  "FIFO Count"         readFifoCnt -          -      -
    periphID0  0xFE0  r  "ID Register 0"      -           -          0x81   -
    periphID1  0XFE4  r  "ID Register 1"      -           -          0x11   -
    periphID2  0XFE8  r  "ID Register 2"      -           -          0x04   -
    periphID3  0XFEC  r  "ID Register 3"      -           -          0x00   -
    pCellID0   0XFF0  r  "Cell ID 0"          -           -          0x0d   -
    pCellID1   0XFF4  r  "Cell ID 1"          -           -          0xf0   -
    pCellID2   0XFF8  r  "Cell ID 2"          -           -          0x05   -
    pCellID3   0XFFC  r  "Cell ID 3"          -           -          0xb1   -
}

foreach { rname offset raccess  desc readFn writeFn reset bits } $registers {
    if { $readFn != "-" } {
        set r "-readfunction $readFn"
    } else {
        set r ""
    }
    if { $writeFn != "-" } {
        set w "-writefunction $writeFn"
    } else {
        set w ""
    }
    set cmd "imodeladdmmregister -name $rname -addressblock $addBlock -offset $offset -access $raccess $r $w"

    eval $cmd
    if { $desc != "-" } {
        iadddocumentation -name Description -text $desc -handle "$addBlock/$rname"
    }

    if { $reset != "-" } {
        imodeladdreset -mmregister "$addBlock/$rname" -name reset -value $reset
    }
    
    if { $bits != "-" } {
        foreach { name offset } $bits {
            if { $name == "C_INDEX"  } { set width 6 } else { set width 1 }
            imodeladdfield -mmregister "$addBlock/$rname" \
                -bitoffset $offset \
                -name      $name \
                -width     $width
        }
    }
}

imodeladdlocalmemory -name RESERVED1 -addressblock $addBlock \
                        -offset 0x4c -size 0x34 \
                        -readfunction reservedRead -writefunction reservedWrite
imodeladdlocalmemory -name RESERVED2 -addressblock $addBlock \
                        -offset 0xc0 -size 0xf20 \
                        -readfunction reservedRead -writefunction reservedWrite
                                                
set fifoBase 0x80
set fifoSize 64
imodeladdlocalmemory -name FIFO -addressblock $addBlock \
                     -offset $fifoBase -size $fifoSize

imodeladdformal    -name SD_DRIVE       -type string
iadddocumentation  -name Description    -text "The name of the Image file used for the SD Drive"
imodeladdformal    -name SD_DRIVE_DELTA -type bool
iadddocumentation  -name Description    -text "If present the SD Drive uses delta writes"
                     
                         
imodeladdnetport -name irq0 -type output
imodeladdnetport -name irq1 -type output

imodeladdnetport -name cardin -type output
imodeladdnetport -name wprot -type output


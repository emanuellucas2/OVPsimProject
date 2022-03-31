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

imodelnewperipheral  \
    -imagefile pse.pse  \
    -name    VexpressSysRegs \
    -vendor  arm.ovpworld.org  \
    -library peripheral \
    -version 1.0 \
    -constructor constructor \
    -releasestatus ovp

iadddocumentation -name Description -text "ARM Versatile Express System Registers"
iadddocumentation -name Limitations -text "Only select registers are modeled. See user.c for details."
iadddocumentation -name Reference   -text "ARM Motherboard Express ATX V2M-P1 Technical Reference Manual(ARM DUI 0447G), Section 4.3 Register Summary"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab -port bport1 -width $regWidth -size $range

set addBlock     "bport1/ab"


#   name     offset ac description             readFn     writeFn      bits
set registers {
    ID         0x00 rw "System Identifier"                      readId - -
    SW         0x04 rw "Soft user switches"                     readSw - -
    LED        0x08 rw "User LEDs"                              - writeLed -
    CNT100HZ   0x24 r  "100Hz counter"                          read100Hz - -
    FLAGSSET   0x30 rw  "Flag Set Register"                     readFlags writeFlags -
    FLAGSCLR   0x34 w  "Flag Clear Register"                    - - -
    NVFLAGSSET 0x38 rw  "NV Flag Set Registers"                 - - -
    NVFLAGSCLR 0x3C w  "NV Flag Clear Registers"                - - -
    MCI        0x48 r  "MCI status and control register"        readMci - -
    FLASH      0x4C rw "Flash write protection"                 - - -
    CFGSW      0x58 rw "Soft configuration switches"            - - -
    CNT24MHZ   0x5C r  "32-bit counter clocked at 24MHz"        read24MHz - -
    MISC       0x60 rw "Miscellaneous control flags"            readMisc - -
    DMA        0x64 rw "DMA Channel Selection Register"         - - -
    PROCID0    0x84 rw ""                                       readProcId0 - -
    PROCID1    0x88 rw ""                                       readProcId1 - -
    CFGDATA    0xA0 rw "System Configuration register"          - - -
    CFGCTRL    0xA4 rw "Configuration Control Register"         readCfgCtrl - -
    CFGSTAT    0xA8 rw "Configuration Status Register"          readCfgStat - -
}


foreach { name roffset raccess desc readFn writeFn bits } $registers {
    set rname ${name}

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


    set cmd "imodeladdmmregister -name $rname -addressblock $addBlock -offset $roffset -access $raccess $r $w"

    eval $cmd
    if { $desc != 0 } {
        iadddocumentation -name Description -text $desc -handle "$addBlock/$rname"
    }

    if { $bits != "-" } {
        foreach { n o } $bits {
            imodeladdfield -mmregister "$addBlock/$rname" -bitoffset $o -name $n
        }
    }
}

imodeladdnetport -name cardin -type input
imodeladdnetport -name wprot -type input

imodeladdformal   -name SYS_PROCID0 -type uns32
iadddocumentation -name Description -handle SYS_PROCID0 -text "Specify value returned when SYS_PROCID0 register is read (default=0x0c000191)"

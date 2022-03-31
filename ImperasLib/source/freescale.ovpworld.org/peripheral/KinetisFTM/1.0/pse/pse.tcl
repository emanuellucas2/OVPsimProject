#
# Copyright (c) 2011-2016 Posedge Software, Inc., www.posedgesoft.com
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


set vendor  freescale.ovpworld.org
set library peripheral
set name    KinetisFTM
set version 1.0
set desc "Model of the FTM peripheral used on the Freescale Kinetis platform"
set limitations "Provides the base behaviour for the OVP Freescale Kinetis platforms"

set range 0x1000

imodelnewperipheral           \
    -imagefile   pse.pse      \
    -name        $name        \
    -vendor      $vendor      \
    -library     $library     \
    -version     $version     \
    -constructor constructor  \
    -releasestatus ovp

iadddocumentation -name Description -text $desc
iadddocumentation -name Limitations -text $limitations
iadddocumentation -name Reference -text "www.freescale.com/Kinetis"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"

imodeladdbusslaveport -name bport1 -size $range
imodeladdaddressblock -name ab     -size 0x9c -port bport1 -width 32

set addBlock     "bport1/ab"



#   name      offset ac readFn    writeFn   viewFn   user reset   mask description   
set registers { 
SC              0x00 rw readSC writeSC - - 0x00000000 0x0000007f "Status and Control, offset: 0x0 " 
CNT             0x04 rw - - - - 0x00000000 0x0000ffff "Counter, offset: 0x4 "   
MOD             0x08 rw - - - - 0x00000000 0xffffffff "Modulo, offset: 0x8 "    
C0SC            0x0c rw - - - - 0x00000000 0x0000007d "Channel (n) Status and Control, array offset: 0xC, array step: 0x8 " 
C0V             0x10 rw - - - - 0x00000000 0x0000ffff "Channel (n) Value, array offset: 0x10, array step: 0x8 " 
C1SC            0x14 rw - - - - 0x00000000 0x0000007d "Channel (n) Status and Control, array offset: 0xC, array step: 0x8 " 
C1V             0x18 rw - - - - 0x00000000 0x0000ffff "Channel (n) Value, array offset: 0x10, array step: 0x8 " 
C2SC            0x1c rw - - - - 0x00000000 0x0000007d "Channel (n) Status and Control, array offset: 0xC, array step: 0x8 " 
C2V             0x20 rw - - - - 0x00000000 0x0000ffff "Channel (n) Value, array offset: 0x10, array step: 0x8 " 
C3SC            0x24 rw - - - - 0x00000000 0x0000007d "Channel (n) Status and Control, array offset: 0xC, array step: 0x8 " 
C3V             0x28 rw - - - - 0x00000000 0x0000ffff "Channel (n) Value, array offset: 0x10, array step: 0x8 " 
C4SC            0x2c rw - - - - 0x00000000 0x0000007d "Channel (n) Status and Control, array offset: 0xC, array step: 0x8 " 
C4V             0x30 rw - - - - 0x00000000 0x0000ffff "Channel (n) Value, array offset: 0x10, array step: 0x8 " 
C5SC            0x34 rw - - - - 0x00000000 0x0000007d "Channel (n) Status and Control, array offset: 0xC, array step: 0x8 " 
C5V             0x38 rw - - - - 0x00000000 0x0000ffff "Channel (n) Value, array offset: 0x10, array step: 0x8 " 
C6SC            0x3c rw - - - - 0x00000000 0x0000007d "Channel (n) Status and Control, array offset: 0xC, array step: 0x8 " 
C6V             0x40 rw - - - - 0x00000000 0x0000ffff "Channel (n) Value, array offset: 0x10, array step: 0x8 " 
C7SC            0x44 rw - - - - 0x00000000 0x0000007d "Channel (n) Status and Control, array offset: 0xC, array step: 0x8 " 
C7V             0x48 rw - - - - 0x00000000 0x0000ffff "Channel (n) Value, array offset: 0x10, array step: 0x8 " 
CNTIN           0x4c rw - - - - 0x00000000 0x0000ffff "Counter Initial Value, offset: 0x4C "    
STATUS          0x50 rw - - - - 0x00000000 0x00000000 "Capture and Compare Status, offset: 0x50 "   
MODE            0x54 rw - - - - 0x00000004 0x000000ff "Features Mode Selection, offset: 0x54 "  
SYNC            0x58 rw - - - - 0x00000000 0x000000ff "Synchronization, offset: 0x58 "  
OUTINIT         0x5c rw - - - - 0x00000000 0x000000ff "Initial State for Channels Output, offset: 0x5C "    
OUTMASK         0x60 rw - - - - 0x00000000 0x000000ff "Output Mask, offset: 0x60 "  
COMBINE         0x64 rw - - - - 0x00000000 0x7f7f7f7f "Function for Linked Channels, offset: 0x64 " 
DEADTIME        0x68 rw - - - - 0x00000000 0x000000ff "Deadtime Insertion Control, offset: 0x68 "   
EXTTRIG         0x6c rw - - - - 0x00000000 0x000000ff "FTM External Trigger, offset: 0x6C " 
POL             0x70 rw - - - - 0x00000000 0x000000ff "Channels Polarity, offset: 0x70 "    
FMS             0x74 rw - - - - 0x00000000 0x00000040 "Fault Mode Status, offset: 0x74 "    
FILTER          0x78 rw - - - - 0x00000000 0x0000ffff "Input Capture Filter Control, offset: 0x78 " 
FLTCTRL         0x7c rw - - - - 0x00000000 0x00000fff "Fault Control, offset: 0x7C "    
QDCTRL          0x80 rw - - - - 0x00000000 0x000000f9 "Quadrature Decoder Control and Status, offset: 0x80 "    
CONF            0x84 rw - - - - 0x00000000 0x000006df "Configuration, offset: 0x84 "    
FLTPOL          0x88 rw - - - - 0x00000000 0x0000000f "FTM Fault Input Polarity, offset: 0x88 " 
SYNCONF         0x8c rw - - - - 0x00000000 0x001f1fb5 "Synchronization Configuration, offset: 0x8C "    
INVCTRL         0x90 rw - - - - 0x00000000 0x0000000f "FTM Inverting Control, offset: 0x90 "    
SWOCTRL         0x94 rw - - - - 0x00000000 0x0000ffff "FTM Software Output Control, offset: 0x94 "  
PWMLOAD         0x98 rw - - - - 0x00000000 0x000002ff "FTM PWM Load, offset: 0x98 "
}

foreach { rname offset raccess readFn writeFn viewFn user reset mask desc } $registers {
    set r ""
    set w ""
    set v ""
    set u ""
    set m ""
    if { $readFn  != "-" } { set r "-readfunction  $readFn"   }
    if { $writeFn != "-" } { set w "-writefunction $writeFn"  }
    if { $viewFn  != "-" } { set v "-viewfunction  $viewFn"   }
    if { $user    != "-" } { set u "-userdata      $user"     }
    if { $mask    != "-" } { set m "-writemask     $mask"     }

    set cmd "imodeladdmmregister -name $rname -addressblock $addBlock -offset $offset -access $raccess $r $w $v $u $m"
    eval $cmd

    if { $reset != "-" } {
        imodeladdreset -mmregister $addBlock/$rname -name Reset -value $reset
    }

    iadddocumentation -name Description -text $desc -handle "$addBlock/$rname"
}

imodeladdnetport -name PhaseA    -type input -updatefunction phaseACB
imodeladdnetport -name PhaseB    -type input -updatefunction phaseBCB
imodeladdnetport -name Interrupt -type output

for {set i 0} {$i < 10} {incr i} {
    imodeladdformal -type string -name stimfile${i}
    }
 
imodeladdfield -mmregister $addBlock/SC -name CLKS -bitoffset 3  -width 2
imodeladdfield -mmregister $addBlock/SC -name CPWMS -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/SC -name PS -bitoffset 0  -width 3
imodeladdfield -mmregister $addBlock/SC -name TOF -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/SC -name TOIE -bitoffset 6  -width 1   
 
imodeladdfield -mmregister $addBlock/CNT -name COUNT -bitoffset 0  -width 16    
 
imodeladdfield -mmregister $addBlock/MOD -name MOD -bitoffset 0  -width 16  
 
imodeladdfield -mmregister $addBlock/C0SC -name CHF -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/C0SC -name CHIE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/C0SC -name DMA -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/C0SC -name ELSA -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/C0SC -name ELSB -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/C0SC -name MSA -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/C0SC -name MSB -bitoffset 5  -width 1  

imodeladdfield -mmregister $addBlock/C1SC -name CHF -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/C1SC -name CHIE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/C1SC -name DMA -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/C1SC -name ELSA -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/C1SC -name ELSB -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/C1SC -name MSA -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/C1SC -name MSB -bitoffset 5  -width 1  
 
imodeladdfield -mmregister $addBlock/C2SC -name CHF -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/C2SC -name CHIE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/C2SC -name DMA -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/C2SC -name ELSA -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/C2SC -name ELSB -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/C2SC -name MSA -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/C2SC -name MSB -bitoffset 5  -width 1  
 
imodeladdfield -mmregister $addBlock/C3SC -name CHF -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/C3SC -name CHIE -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/C3SC -name DMA -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/C3SC -name ELSA -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/C3SC -name ELSB -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/C3SC -name MSA -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/C3SC -name MSB -bitoffset 5  -width 1  
 
imodeladdfield -mmregister $addBlock/C0V -name VAL -bitoffset 0  -width 16  
imodeladdfield -mmregister $addBlock/C1V -name VAL -bitoffset 0  -width 16  
imodeladdfield -mmregister $addBlock/C2V -name VAL -bitoffset 0  -width 16  
imodeladdfield -mmregister $addBlock/C3V -name VAL -bitoffset 0  -width 16  
imodeladdfield -mmregister $addBlock/C4V -name VAL -bitoffset 0  -width 16  
imodeladdfield -mmregister $addBlock/C5V -name VAL -bitoffset 0  -width 16  
imodeladdfield -mmregister $addBlock/C6V -name VAL -bitoffset 0  -width 16  
imodeladdfield -mmregister $addBlock/C7V -name VAL -bitoffset 0  -width 16  
 
imodeladdfield -mmregister $addBlock/CNTIN -name INIT -bitoffset 0  -width 16   
 
imodeladdfield -mmregister $addBlock/STATUS -name CH0F -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/STATUS -name CH1F -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/STATUS -name CH2F -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/STATUS -name CH3F -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/STATUS -name CH4F -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/STATUS -name CH5F -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/STATUS -name CH6F -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/STATUS -name CH7F -bitoffset 7  -width 1   
 
imodeladdfield -mmregister $addBlock/MODE -name CAPTEST -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/MODE -name FAULTIE -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/MODE -name FAULTM -bitoffset 5  -width 2
imodeladdfield -mmregister $addBlock/MODE -name FTMEN -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/MODE -name INIT -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/MODE -name PWMSYNC -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/MODE -name WPDIS -bitoffset 2  -width 1    
 
imodeladdfield -mmregister $addBlock/SYNC -name CNTMAX -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/SYNC -name CNTMIN -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/SYNC -name REINIT -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/SYNC -name SWSYNC -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/SYNC -name SYNCHOM -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/SYNC -name TRIG0 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/SYNC -name TRIG1 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/SYNC -name TRIG2 -bitoffset 6  -width 1    
 
imodeladdfield -mmregister $addBlock/OUTINIT -name CH0OI -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/OUTINIT -name CH1OI -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/OUTINIT -name CH2OI -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/OUTINIT -name CH3OI -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/OUTINIT -name CH4OI -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/OUTINIT -name CH5OI -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/OUTINIT -name CH6OI -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/OUTINIT -name CH7OI -bitoffset 7  -width 1 
 
imodeladdfield -mmregister $addBlock/OUTMASK -name CH0OM -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/OUTMASK -name CH1OM -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/OUTMASK -name CH2OM -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/OUTMASK -name CH3OM -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/OUTMASK -name CH4OM -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/OUTMASK -name CH5OM -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/OUTMASK -name CH6OM -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/OUTMASK -name CH7OM -bitoffset 7  -width 1 
 
imodeladdfield -mmregister $addBlock/COMBINE -name COMBINE0 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name COMBINE1 -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name COMBINE2 -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name COMBINE3 -bitoffset 24  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name COMP0 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name COMP1 -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name COMP2 -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name COMP3 -bitoffset 25  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name DECAP0 -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name DECAP1 -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name DECAP2 -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name DECAP3 -bitoffset 27  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name DECAPEN0 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name DECAPEN1 -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name DECAPEN2 -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name DECAPEN3 -bitoffset 26  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name DTEN0 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name DTEN1 -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name DTEN2 -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name DTEN3 -bitoffset 28  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name FAULTEN0 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name FAULTEN1 -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name FAULTEN2 -bitoffset 22  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name FAULTEN3 -bitoffset 30  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name SYNCEN0 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name SYNCEN1 -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name SYNCEN2 -bitoffset 21  -width 1
imodeladdfield -mmregister $addBlock/COMBINE -name SYNCEN3 -bitoffset 29  -width 1  
 
imodeladdfield -mmregister $addBlock/DEADTIME -name DTPS -bitoffset 6  -width 2
imodeladdfield -mmregister $addBlock/DEADTIME -name DTVAL -bitoffset 0  -width 6    
 
imodeladdfield -mmregister $addBlock/EXTTRIG -name CH0TRIG -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/EXTTRIG -name CH1TRIG -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/EXTTRIG -name CH2TRIG -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/EXTTRIG -name CH3TRIG -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/EXTTRIG -name CH4TRIG -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/EXTTRIG -name CH5TRIG -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/EXTTRIG -name INITTRIGEN -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/EXTTRIG -name TRIGF -bitoffset 7  -width 1 
 
imodeladdfield -mmregister $addBlock/POL -name POL0 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/POL -name POL1 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/POL -name POL2 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/POL -name POL3 -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/POL -name POL4 -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/POL -name POL5 -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/POL -name POL6 -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/POL -name POL7 -bitoffset 7  -width 1  
 
imodeladdfield -mmregister $addBlock/FMS -name FAULTF -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/FMS -name FAULTF0 -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/FMS -name FAULTF1 -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/FMS -name FAULTF2 -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/FMS -name FAULTF3 -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/FMS -name FAULTIN -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/FMS -name WPEN -bitoffset 6  -width 1  
 
imodeladdfield -mmregister $addBlock/FILTER -name CH0FVAL -bitoffset 0  -width 4
imodeladdfield -mmregister $addBlock/FILTER -name CH1FVAL -bitoffset 4  -width 4
imodeladdfield -mmregister $addBlock/FILTER -name CH2FVAL -bitoffset 8  -width 4
imodeladdfield -mmregister $addBlock/FILTER -name CH3FVAL -bitoffset 12  -width 4   
 
imodeladdfield -mmregister $addBlock/FLTCTRL -name FAULT0EN -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/FLTCTRL -name FAULT1EN -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/FLTCTRL -name FAULT2EN -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/FLTCTRL -name FAULT3EN -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/FLTCTRL -name FFLTR0EN -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/FLTCTRL -name FFLTR1EN -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/FLTCTRL -name FFLTR2EN -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/FLTCTRL -name FFLTR3EN -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/FLTCTRL -name FFVAL -bitoffset 8  -width 4 
 
imodeladdfield -mmregister $addBlock/QDCTRL -name PHAFLTREN -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/QDCTRL -name PHAPOL -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/QDCTRL -name PHBFLTREN -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/QDCTRL -name PHBPOL -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/QDCTRL -name QUADEN -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/QDCTRL -name QUADIR -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/QDCTRL -name QUADMODE -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/QDCTRL -name TOFDIR -bitoffset 1  -width 1 
 
imodeladdfield -mmregister $addBlock/CONF -name BDMMODE -bitoffset 6  -width 2
imodeladdfield -mmregister $addBlock/CONF -name GTBEEN -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/CONF -name GTBEOUT -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/CONF -name NUMTOF -bitoffset 0  -width 5   
 
imodeladdfield -mmregister $addBlock/FLTPOL -name FLT0POL -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/FLTPOL -name FLT1POL -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/FLTPOL -name FLT2POL -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/FLTPOL -name FLT3POL -bitoffset 3  -width 1    
 
imodeladdfield -mmregister $addBlock/SYNCONF -name CNTINC -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/SYNCONF -name HWINVC -bitoffset 19  -width 1
imodeladdfield -mmregister $addBlock/SYNCONF -name HWOM -bitoffset 18  -width 1
imodeladdfield -mmregister $addBlock/SYNCONF -name HWRSTCNT -bitoffset 16  -width 1
imodeladdfield -mmregister $addBlock/SYNCONF -name HWSOC -bitoffset 20  -width 1
imodeladdfield -mmregister $addBlock/SYNCONF -name HWTRIGMODE -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/SYNCONF -name HWWRBUF -bitoffset 17  -width 1
imodeladdfield -mmregister $addBlock/SYNCONF -name INVC -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/SYNCONF -name SWINVC -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/SYNCONF -name SWOC -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/SYNCONF -name SWOM -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/SYNCONF -name SWRSTCNT -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/SYNCONF -name SWSOC -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/SYNCONF -name SWWRBUF -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/SYNCONF -name SYNCMODE -bitoffset 7  -width 1  
 
imodeladdfield -mmregister $addBlock/INVCTRL -name INV0EN -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/INVCTRL -name INV1EN -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/INVCTRL -name INV2EN -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/INVCTRL -name INV3EN -bitoffset 3  -width 1    
 
imodeladdfield -mmregister $addBlock/SWOCTRL -name CH0OC -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/SWOCTRL -name CH0OCV -bitoffset 8  -width 1
imodeladdfield -mmregister $addBlock/SWOCTRL -name CH1OC -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/SWOCTRL -name CH1OCV -bitoffset 9  -width 1
imodeladdfield -mmregister $addBlock/SWOCTRL -name CH2OC -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/SWOCTRL -name CH2OCV -bitoffset 10  -width 1
imodeladdfield -mmregister $addBlock/SWOCTRL -name CH3OC -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/SWOCTRL -name CH3OCV -bitoffset 11  -width 1
imodeladdfield -mmregister $addBlock/SWOCTRL -name CH4OC -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/SWOCTRL -name CH4OCV -bitoffset 12  -width 1
imodeladdfield -mmregister $addBlock/SWOCTRL -name CH5OC -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/SWOCTRL -name CH5OCV -bitoffset 13  -width 1
imodeladdfield -mmregister $addBlock/SWOCTRL -name CH6OC -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/SWOCTRL -name CH6OCV -bitoffset 14  -width 1
imodeladdfield -mmregister $addBlock/SWOCTRL -name CH7OC -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/SWOCTRL -name CH7OCV -bitoffset 15  -width 1   
 
imodeladdfield -mmregister $addBlock/PWMLOAD -name CH0SEL -bitoffset 0  -width 1
imodeladdfield -mmregister $addBlock/PWMLOAD -name CH1SEL -bitoffset 1  -width 1
imodeladdfield -mmregister $addBlock/PWMLOAD -name CH2SEL -bitoffset 2  -width 1
imodeladdfield -mmregister $addBlock/PWMLOAD -name CH3SEL -bitoffset 3  -width 1
imodeladdfield -mmregister $addBlock/PWMLOAD -name CH4SEL -bitoffset 4  -width 1
imodeladdfield -mmregister $addBlock/PWMLOAD -name CH5SEL -bitoffset 5  -width 1
imodeladdfield -mmregister $addBlock/PWMLOAD -name CH6SEL -bitoffset 6  -width 1
imodeladdfield -mmregister $addBlock/PWMLOAD -name CH7SEL -bitoffset 7  -width 1
imodeladdfield -mmregister $addBlock/PWMLOAD -name LDOK -bitoffset 9  -width 1


imodeladdformal -name stimFile0 -type string
imodeladdformal -name configure -type uns32

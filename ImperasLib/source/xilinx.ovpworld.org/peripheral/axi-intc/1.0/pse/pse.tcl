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
set name    axi-intc
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor 

iadddocumentation -name Description  \
    -text "Microblaze LogiCORE IP AXI Interrupt Controller"

iadddocumentation -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation -name Limitations  \
    -text "Implements the basic interrupt processing behavior"
iadddocumentation -name Limitations  \
    -text "Does not implement interrupt cascade"

iadddocumentation -name Reference \
    -text "PG099 October 4, 2017 v4.1"

#
# Registers
#

set PORT    bport1
set AB      ab
set AB_SIZE 0x200

imodeladdbusslaveport  -name $PORT -mustbeconnected -size $AB_SIZE
imodeladdaddressblock  -name $AB -port $PORT -size $AB_SIZE -offset 0 -width 32

imodeladdlocalmemory -name buffer -addressblock $PORT/$AB -size $AB_SIZE -offset 0x0 \
                     -writefunction regNoDefinitionWrite -readfunction regNoDefinitionRead
                     

#   name offset num  sz access reset  wMask   rdF    wrF  description                                      bits
set registers  {
    ISR    0x0000  1  32 rw 0x00000000 -        -     auto "Interrupt Status Register (ISR)"                -
    IPR    0x0004  1  32 rw 0x00000000 -        auto  auto "Interrupt Pending Register (IPR)"               -
    IER    0x0008  1  32 rw 0x00000000 -        -     auto "Interrupt Enable Register (IER)"                -
    IAR    0x000C  1  32 rw 0x00000000 -        -     auto "Interrupt Acknowledge Register (IAR)"           -
    SIE    0x0010  1  32 rw 0x00000000 -        -     auto "Set Interrupt Enables (SIE)"                    -
    CIE    0x0014  1  32 rw 0x00000000 -        -     auto "Clear Interrupt Enables (CIE)"                  -
    IVR    0x0018  1  32 r  0x00000000 -        -     -    "Interrupt Vector Register (IVR)"                -
    MER    0x001C  1  32 rw 0x00000000 3        -     auto "Master Enable Register (MER)"                   {ME 0 1 "" HIE 1 1 ""}
    IMR    0x0020  1  32 rw 0x00000000 -        -     auto "Interrupt Mode Register (IMR)"                  -
    ILR    0x0024  1  32 rw 0xffffffff -        -     -    "Interrupt Level Register (ILR)"                 -
    IVAR   0x0100 32  32 rw 0x00000000 -        auto  auto "IVAR Interrupt Vector Address Register (IVAR)"  -
}

foreach {rname roffset num rsize raccess reset writeMask readFunc writeFunc description bits} $registers {

    # Ignore reserved registers
    if {$raccess == "-" } {continue}
    if {$rsize   != "32"} {set rsize 32}
    
    set regName $rname
    if { $num > 1 } {
        set regName ${rname}%u
    }

#    puts "# $rname ($regName) [format 0x%x $roffset] ($roffset $num) $rsize $raccess $reset $writeMask $readFunc $writeFunc $description $bits"

    set command "imodeladdmmregister -addressblock $PORT/$AB -name $regName -width 32 -offset $roffset -access $raccess"
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
    
    if { $writeMask == "-" } {
        set defaultcb 1
    } else {
        set command "${command} -writemask $writeMask"
    }
    
    if { $num > 1 } {
        set command "${command} -userdata _index -loarray 0 -hiarray [expr $num - 1]"
    }
      
#      puts "command $command"
    eval $command
  
    if { $description != "-" } {
      iadddocumentation  -handle $PORT/$AB/$regName \
                         -name Description  \
                         -text $description
    }
    
    if { $bits != "-" } {
        foreach { n o w d } $bits {
#            puts "#     $n $o $w $d"
            imodeladdfield -mmregister $PORT/$AB/$regName -bitoffset $o -width $w -name $n
            if { $d != "-" } {
                iadddocumentation -handle $PORT/$AB/$regName \
                                  -name Description  \
                                  -text $d
            }
        }
    }
    
    imodeladdreset -mmregister $PORT/$AB/$regName -name resetNet -value $reset

}

#
# Signals
#

# interrupt inputs







imodeladdnetport -type input -name intr%u -updatefunction intrInput -updatefunctionargument _index -loarray 0 -hiarray 31

# interrupt cascade input
imodeladdnetport -type input  -name irq_in      -updatefunction intrInput -updatefunctionargument 256
imodeladdnetport -type input  -name irq_addr_in
imodeladdnetport -type output -name irq_ack_out


# interrupt output
imodeladdnetport -type output -name irq

# fast interrupt mode
imodeladdnetport -type input  -name irq_ack      -updatefunction ackInput
imodeladdnetport -type output -name irq_addr_out

#
# Parameters
#

# Vivado Design Suite customization
imodeladdformal   -name   C_HAS_IPR  -type boolean -defaultvalue 1
iadddocumentation -handle C_HAS_IPR  -name Description  -text "The Interrupt Pending Register exists"
imodeladdformal   -name   C_HAS_SIE  -type boolean -defaultvalue 1
iadddocumentation -handle C_HAS_SIE  -name Description  -text "The Set Interrupt Enables Register exists"
imodeladdformal   -name   C_HAS_CIE  -type boolean -defaultvalue 1
iadddocumentation -handle C_HAS_CIE  -name Description  -text "The Clear Interrupt Enables Register exists"
imodeladdformal   -name   C_HAS_IMR  -type boolean -defaultvalue 1
iadddocumentation -handle C_HAS_IMR  -name Description  -text "The Interrupt Mode Register exists"
imodeladdformal   -name   C_HAS_FAST -type boolean -defaultvalue 1
iadddocumentation -handle C_HAS_FAST -name Description  -text "The Fast Interrupt Logic is enabled"
# enable the cascade input
imodeladdformal   -name   C_EN_CASCADE_MODE -type boolean   
iadddocumentation -handle C_EN_CASCADE_MODE -name Description -text "Set to enable the cascading of interrupts"
imodeladdformal   -name   C_CASCADE_MASTER -type boolean   
iadddocumentation -handle C_CASCADE_MASTER -name Description -text "Set when the cascade master"

# define number of configured interrupts and software interrupts (combined max 32)
set defaultINTR   16
set defaultSWINTR  4
imodeladdformal    -name   C_NUM_INTR_INPUTS -type uns32 -min 1 -max 32 -defaultvalue 16
iadddocumentation  -handle C_NUM_INTR_INPUTS -name Description  -text "Set the number of active hardware interrupt inputs (default 16)"
imodeladdformal    -name   C_NUM_SW_INTR -type uns32 -min 0 -max 32 -defaultvalue 4
iadddocumentation  -handle C_NUM_SW_INTR -name Description  -text "Set the number of software interrupts (default 4)"




 

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
set name    axi-gpio
set version 1.0

imodelnewperipheral -name $name -imagefile pse.pse \
    -library $library -vendor $vendor -version $version \
    -constructor constructor \
    -destructor destructor

iadddocumentation  \
    -name Description  \
    -text "Xilinx AXI General Purpose IO"

iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

iadddocumentation  \
    -name Limitations  \
    -text "This model implements the AXI GPIO"

iadddocumentation -name Reference -text "pg144-axi-gpio Vivado Design Suite October 5, 2016"

#
# Registers
#

set port "sp1"
set portSize 0x200
imodeladdbusslaveport  -name ${port} -size ${portSize} -mustbeconnected

set abrsize 0x200
set abr  "reg"
imodeladdaddressblock  -name ${abr}  -port ${port} -size $abrsize -offset 0 -width 32

# no callback on read data for performance when polling
#imodeladdmmregister  -addressblock ${port}/${abr} -name gpio_data  -width 32 -offset 0x000 -access rw -writefunction writeData
imodeladdlocalmemory -addressblock ${port}/${abr} -name gpio_data  -size   4 -offset 0x000 -access rw -changefunction writeData
imodeladdmmregister  -addressblock ${port}/${abr} -name gpio_tri   -width 32 -offset 0x004 -access rw -writefunction writeTri

# no callback on read data for performance when polling
#imodeladdmmregister  -addressblock ${port}/${abr} -name gpio2_data -width 32 -offset 0x008 -access rw -writefunction writeData2
imodeladdlocalmemory -addressblock ${port}/${abr} -name gpio2_data  -size   4 -offset 0x008 -access rw -changefunction writeData2
imodeladdmmregister  -addressblock ${port}/${abr} -name gpio2_tri  -width 32 -offset 0x00c -access rw -writefunction writeTri2

imodeladdmmregister  -addressblock ${port}/${abr} -name gier       -width 32 -offset 0x11c -access rw -readfunction readGier -writefunction writeGier
imodeladdmmregister  -addressblock ${port}/${abr} -name ip_ier     -width 32 -offset 0x128 -access rw -readfunction readIer  -writefunction writeIer
imodeladdmmregister  -addressblock ${port}/${abr} -name ip_isr     -width 32 -offset 0x120 -access rw -readfunction readIsr  -writefunction writeIsr


# define the endian for the processor interface (default little)
imodeladdformal -name endian -type string -defaultvalue "little"

imodeladdnetport -name gpio_out  -type output
imodeladdnetport -name gpio_in   -type input -updatefunction gpioInput
imodeladdnetport -name gpio2_out -type output
imodeladdnetport -name gpio2_in  -type input -updatefunction gpio2Input

# define the significant bits in the gpio data
imodeladdformal -name gpiowidth  -type uns32 -defaultvalue 32 -min 1 -max 32
imodeladdformal -name gpio2width -type uns32 -defaultvalue 32 -min 1 -max 32
# default TRI value - all bits to input
imodeladdformal -name initgpiotri  -type uns32  -defaultvalue 0xffffffff -min 0 -max 0xffffffff
imodeladdformal -name initgpio2tri -type uns32  -defaultvalue 0xffffffff -min 0 -max 0xffffffff
# default DATA value - 0
imodeladdformal -name initgpiodata  -type uns32  -defaultvalue 0
imodeladdformal -name initgpio2data -type uns32  -defaultvalue 0
# enable for dual channel
imodeladdformal -name dualchannel -type boolean  -defaultvalue 1
 

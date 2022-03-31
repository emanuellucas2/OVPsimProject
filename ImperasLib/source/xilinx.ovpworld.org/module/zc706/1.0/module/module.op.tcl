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

set desc "This module implements the Zynq zc706 Evaluation Board.
          This module provides the board level definition and the instantiation of a Zynq and memory."

set limitations "Currently this module is not used. It instances the Zynq module only."

set reference "ZC706 Evaluation Board for the Zynq-7000 XC7Z045 All Programmable SoC UG945 v1.5 September 10, 2014 (ug954-zc706-eval-board-xc7z045-ap-soc) and 
Zynq-7000 AP SoC Technical Reference Manual UG585 (v1.10) February 23, 2015 (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)"

set license "Open Source Apache 2.0"

# Setup variables for platform info 
set vendor  xilinx.ovpworld.org
set library module
set name    zc706
set version 1.0

#
# Start new platform creation 
#
ihwnew -name $name -vendor $vendor -library $library -version $version -stoponctrlc -purpose module -releasestatus ovp -diagnostics
iadddocumentation -name Licensing   -text $license
iadddocumentation -name Description -text $desc
iadddocumentation -name Limitations -text $limitations
iadddocumentation -name Reference   -text $reference


#
# Zync-7000
#
ihwaddmodule -instancename Zynq -vendor xilinx.ovpworld.org -library module -type Zynq -version 1.0
# Set the board PS clock
ihwsetparameter -handle Zynq -name psclock -value 33  -type Uns32
# Set the board PS clock
ihwsetparameter -handle Zynq -name armmips -value 500 -type Uns32

# need the board info to configure devcfg that includes power info
ihwsetparameter -handle Zynq -name board -value $name -type String

#
# DDR connection (external Port)
#
#ihwaddbus     -instancename ddrBus -addresswidth 32
#ihwconnect    -instancename Zynq -busport extPortDDR -bus ddrBus
#
#ihwaddmemory -instancename DDR -type ram
#ihwconnect   -instancename DDR -bus ddrBus -busslaveport sp1 -loaddress 0x00000000 -hiaddress 0x3fffffff

#
# I2C board connection (external Port)
#
ihwaddbus     -instancename i2cBus -addresswidth 16
ihwconnect    -instancename Zynq -busport extPortI2C -bus i2cBus

# I2C Devices
# Address Channel Description
# 0x74    -       PCA9548 8 channel I2C bus switch
# 0x5e    0       Si570 clock
# 0x50    0       SFP+ Conn P2
# 0x39    1       ADV7511 HDMI
# 0x54    2       I2C EEPROM (M24C08)
# 0x21    3       I2C Port Expander (P14-P16 XADC_MUX_ADDR0)
# 0x50    3       DDR3 SODIMM
# 0x18    3       DDR3 SODIMM
# 0x51    4       I2C Real Time Clock (RTC8564)
# 0x68    4       Si5324 Clock
# 0xX0    5       FMC HPC J3 (word aligned 0 to 0x7c)
# 0xX0    6       FMC LPC J4 (word aligned 0 to 0x7c)
# 0x65    7       UCD9012A controller PMBUS
# Access is offset at 0x100 x channel number

ihwaddperipheral -instancename pmbus -vendor ti.ovpworld.org -type ucd9012a
set pmbusAdd [expr (7*0x100)+0x65]
ihwconnect       -instancename pmbus -bus i2cBus -busslaveport iic -loaddress $pmbusAdd -hiaddress $pmbusAdd

ihwaddperipheral -instancename i2cmux -vendor ti.ovpworld.org -type tca6416a
set i2cmuxAdd [expr (3*0x100)+0x21]
ihwconnect       -instancename i2cmux -bus i2cBus -busslaveport iic -loaddress $i2cmuxAdd -hiaddress $i2cmuxAdd

ihwaddnet  -instancename xadcmux
ihwconnect -instancename Zynq   -netport extPortXADCMux -net xadcmux
ihwconnect -instancename i2cmux -netport xadcmux -net xadcmux

ihwaddformalparameter -name configfile -type string
iadddocumentation -name Description -text "Formal parameter configfile provides the configuration file for LED and Switch usage"

# Visualization
ihwaddformalmacro -name OP_HTTP_VIS_PORT_FORMALS

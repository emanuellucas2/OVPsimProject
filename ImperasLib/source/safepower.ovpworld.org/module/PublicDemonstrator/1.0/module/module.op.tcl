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

set desc "This module implements the Safepower Public Demonstrator.
          This is very close to teh Xilinx zc702 board defintion. It adds some additional I/O devices.
          This module provides the board level definition and the instantiation of a Zynq and memory."

set limitations "Currently this module is not used. It instances the Zynq module only."

set reference "SafePower project Public Demonstrator"

set license "Open Source Apache 2.0"

# Setup variables for platform info 
set vendor  safepower.ovpworld.org
set library module
set name    PublicDemonstrator
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
# 0x58    0       Si570 clock
# 0x39    1       ADV7511 HDMI
# 0x54    2       I2C EEPROM
# 0x21    3       I2C Port Expander
# 0x51    4       I2C Real Time Clock (RTC8564)
# 0xX0    5       FMC LPC J3 (word aligned 0 to 0x7c)
# 0xX0    6       FMC LPC J4 (word aligned 0 to 0x7c)
# 0x34    7       UCD9248 controller PMBUS (52)
# 0x35    7       UCD9248 controller PMBUS (53)
# 0x36    7       UCD9248 controller PMBUS (54)
# Access is offset at 0x100 x channel number

ihwaddperipheral -instancename pmbus1 -vendor ti.ovpworld.org -type ucd9248
set pmbus1Add [expr (7*0x100)+0x34]
ihwconnect       -instancename pmbus1 -bus i2cBus -busslaveport iic -loaddress $pmbus1Add -hiaddress $pmbus1Add

ihwaddperipheral -instancename pmbus2 -vendor ti.ovpworld.org -type ucd9248
set pmbus2Add [expr (7*0x100)+0x35]
ihwconnect       -instancename pmbus2 -bus i2cBus -busslaveport iic -loaddress $pmbus2Add -hiaddress $pmbus2Add

ihwaddperipheral -instancename pmbus3 -vendor ti.ovpworld.org -type ucd9248
set pmbus3Add [expr (7*0x100)+0x36]
ihwconnect       -instancename pmbus3 -bus i2cBus -busslaveport iic -loaddress $pmbus3Add -hiaddress $pmbus3Add

ihwaddformalparameter -name configfile -type string
iadddocumentation -name Description -text "Formal parameter configfile provides the configuration file for LED and Switch usage"

# Visualization
ihwaddformalmacro -name OP_HTTP_VIS_PORT_FORMALS

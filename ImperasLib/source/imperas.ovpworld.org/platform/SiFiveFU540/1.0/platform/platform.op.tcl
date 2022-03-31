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

ihwnew -name SiFiveFU540  \
  -vendor imperas.ovpworld.org \
  -library platform \
  -version 1.0 \
  -stoponctrlc \
  -releasestatus ovp \
  -purpose fixed \
  -wallclock 10

iadddocumentation -name Licensing    -text "Open Source Apache 2.0"

iadddocumentation -name Description  -text "
    SiFive FU540-C000 SoC module.
    On start up or reset, the reset code at 0x1004 will jump to a jump table entry indexed by the MSEL register at address 0x1000 (default initial MSEL value is 0xf which will cause a jump to address 0x10000). Use the msel peripheral's MSEL parameter to change the initial value of this register. 
    To run a bare metal application use the --program command line option to specify an elf file to be loaded. It must be linked to use addresses corresponding to the implemented memory regions. The --program option will override the initial pc with the ELF file's start address. 
    To facilitate booting Linux an OVP SmartLoader psuedo-peripheral has been included that provides the functionality of the ZSBL/FSBL. The SmartLoader's dtb parameter should be used to specify the device tree blob file to load, and the bbl elf file should be loaded using the --objfilenoentry command line option. 
    "

iadddocumentation -name Reference    -text "SiFive Freedom U540-C000 Manual FU540-C000-v1.0.pdf (https://www.sifive.com/documentation/chips/freedom-u540-c000-manual)"

iadddocumentation -name Limitations  -text "
    Caches and the Cache Controller are not modeled.
    The Instruction Tightly Integrated Memory (ITIM) is implemented simply as RAM. Deallocation by writing to the byte immediately following the memory is a NOP.
    The L2 Loosely Integrated Memory (L2-LIM) is implemented simply as RAM. It is always available, since the Cache Controller is not modeled.
    The L2 Scratchpad memory is not modeled.
    The Platform DMA Engine (PDMA) is not modeled.
    The Pulse Width Modulator (PWM) is not modeled.
    The Inter-Integrated Circuit (I2C) Master Interface is not modeled.
    The Serial Peripheral Interface (SPI) is not modeled. Instead a Virtio Block MMIO device has been added at reserved address 0x1f000000, using interrupt 54.
    The General Purpose Input/Output Controller (GPIO) is not modeled.
    The One-Time Programmable Memory Interface (OTP) is not modeled.
    DDR controller is not modeled. DDR memory is modeled as RAM.
    The Debug Interface is not modeled."

ihwaddclp -extendedargs

ihwaddmodule -instancename  SiFiveFU540 -type FU540 -vendor sifive.ovpworld.org  -library module -version 1.0

ihwsetparameter -handle SiFiveFU540/uart0 -type boolean -name console            -value 1 
ihwsetparameter -handle SiFiveFU540/uart0 -type boolean -name finishOnDisconnect -value 1 
ihwsetparameter -handle SiFiveFU540/uart0 -type string  -name outfile            -value uart0.log 

  
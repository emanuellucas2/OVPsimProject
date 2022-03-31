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
# NAME : MaltaFPGA

imodelnewperipheral  \
                -name MaltaFPGA  \
                -vendor mips.ovpworld.org  \
                -library peripheral  \
                -version 1.0  \
                -releasestatus ovp \
                -constructor constructor \
                -destructor  destructor

iadddocumentation  \
                -name Licensing  \
                -text "Open Source Apache 2.0"

iadddocumentation  \
                -name Description  \
                -text "MIPS MALTA FPGA. Drives Development board functions."

iadddocumentation  \
                -name Limitations  \
                -text "This model has sufficient functionality to allow a Linux Kernel to Boot on the MIPS:MALTA platform."

iadddocumentation  \
		-name Reference  \
		-text "MIPS Malta User Manual."

  imodeladdbusslaveport  \
                -name busPort1  \
                -size 0x0900

  imodeladdbusslaveport  \
                -name busPort2  \
                -size 0x0600

  imodeladdformal  \
                -name stoponsoftreset  \
                -type bool
  iadddocumentation  \
                -name Description  \
                -text "If non:zero, when the software reset register is written the simulation will terminate. By Default the software reset register has no effect."

  imodeladdformal  \
                -name switches  \
                -type uns32
  iadddocumentation  \
                -name Description  \
                -text "This value is used to initialise the set on input switches to the Malta FPGA."



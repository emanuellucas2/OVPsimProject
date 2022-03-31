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
# NAME : MC146818

imodelnewperipheral  \
                -name    MC146818  \
                -vendor  motorola.ovpworld.org  \
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
                -text "MC146818 Real:time clock."

iadddocumentation  \
                -name Limitations  \
                -text "This model has sufficient functionality to allow a Linux Kernel to Boot on the MIPS:MALTA platform."

iadddocumentation  \
		-name Reference  \
		-text "Motorola MC146818AS Datasheet"

  imodeladdformal -name timefromhost -type bool
  iadddocumentation  \
                -name Description  \
                -text "If set, fetch the time from the host. Note that in this mode, simulation results will vary from run to run."


  imodeladdbusslaveport  \
                -name busPort  \
                -size 2  \
                -mustbeconnected

  imodeladdnetport  \
                -name timerInt   \
                -type output


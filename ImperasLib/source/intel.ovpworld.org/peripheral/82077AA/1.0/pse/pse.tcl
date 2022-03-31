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
# NAME : FloppyDrive

imodelnewperipheral  \
                -name 82077AA  \
                -vendor intel.ovpworld.org  \
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
                -text "Dummy Floppy Disc Controller."

iadddocumentation  \
                -name Limitations  \
                -text "Register stubs only."

iadddocumentation  \
		-name Reference  \
		-text "http://www.buchty.net/casio/files/82077.pdf http://www.alldatasheet.com/datesheet-pdf/pdf/167793/INTEL/82077AA.html"

imodeladdbusslaveport  \
                -name bport1  \
                -size 8  \
                -mustbeconnected

iadddocumentation  \
                -name Description  \
                -text "Byte:wide access to control and status registers."


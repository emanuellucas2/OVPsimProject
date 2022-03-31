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
# NAME : wb_1way_32byteline_2048tags

imodelnewmmc -name wb_1way_32byteline_2048tags  \
    -vendor ovpworld.org  \
    -library mmc          \
    -version 1.0          \
    -releasestatus ovp    \
    -visibility    visible
 
iadddocumentation  \
                -name Licensing  \
                -text "Open Source Apache 2.0"

iadddocumentation  \
                -name Description  \
                -text "This is an MMC cache model.
	It is configured as write back, 1 way, 32 byte line length with 2048 tags."

  imodeladdbusslaveport  \
                -name sp1  \
                -mustbeconnected

  imodeladdbusmasterport  \
                -name mp1  \
                -addresswidth 32  \
                -mustbeconnected


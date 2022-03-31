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
# NAME : FlashDevice

imodelnewperipheral  \
    -vendor  ovpworld.org  \
    -library peripheral  \
    -name    FlashDevice  \
    -version 1.0  \
    -extensionfile model  \
    -releasestatus ovp        \
    -visibility    visible \
    -constructor constructor \
    -destructor  destructor
                
  iadddocumentation  \
                -name Description  \
                -text "Model of AMD Am29 Flash memory device."

  iadddocumentation  \
		-name Limitations  \
		-text "Only basic erase and programming commands are supported."

  iadddocumentation  \
    -name Licensing  \
    -text "Open Source Apache 2.0"

  iadddocumentation  \
    -name Reference \
    -text "AMD Am29 datasheet"

  imodeladdformal -name endian -type string -defaultValue "little"

  iadddocumentation  \
                -name Description  \
                -text "Set the endian of the peripheral (default little endian)"
         
  imodeladdformal -name init -type string

  iadddocumentation  \
                -name Description  \
                -text "Specify an initialisation file for the Flash Memory (Intel Hex Format)"

  imodeladdbusslaveport  \
                -name flash  \
                -mustbeconnected


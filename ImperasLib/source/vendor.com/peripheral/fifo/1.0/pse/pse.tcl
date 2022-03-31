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

imodelnewperipheral -name fifo \
                    -constructor constructor \
                    -destructor  destructor \
                    -vendor vendor.com \
                    -library peripheral \
                    -version 1.0 \
                    -releasestatus imperas

iadddocumentation -name Description -text "Example FIFO"
iadddocumentation -name Licensing   -text "Open Source Apache 2.0"
iadddocumentation -name Limitations -text "none."
iadddocumentation -name Reference   -text "No Reference, created as an example"
              
imodeladdfifoport -name fifoPortIn  -type input  -width 32
imodeladdfifoport -name fifoPortOut -type output -width 32

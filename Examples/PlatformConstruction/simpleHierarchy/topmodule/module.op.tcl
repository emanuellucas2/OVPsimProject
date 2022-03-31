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

# TOP MODULE definition

ihwnew -name simpleHierarchy

# nets will be how sub modules communicate
ihwaddnet -instancename write0to1
ihwaddnet -instancename write1to0

# Create an instance 0 of the submodule
ihwaddmodule  -instancename sub0 -modelfile submodule/model
ihwconnect -net write0to1 -instancename sub0 -netport directWritePort
ihwconnect -net write1to0 -instancename sub0 -netport directReadPort

# Create an instance 1 of the submodule
ihwaddmodule  -instancename sub1 -modelfile submodule/model
ihwconnect -net write0to1 -instancename sub1 -netport directReadPort
ihwconnect -net write1to0 -instancename sub1 -netport directWritePort

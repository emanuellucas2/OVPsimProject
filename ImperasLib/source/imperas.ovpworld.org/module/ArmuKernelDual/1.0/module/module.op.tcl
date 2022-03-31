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
# NAME : ArmuKernelDual

set name "ArmuKernelDual"
ihwnew -name   $name \
       -vendor imperas.ovpworld.org  \
       -library module  \
       -version 1.0  -purpose module -releasestatus ovp

iadddocumentation  \
        -name Licensing  \
        -text "Open Source Apache 2.0"

iadddocumentation  \
        -name Description  \
        -text "
        This platform instantiates two modules for an ARM Cortex-A9MPx4 to execute the SMP UKernel
        (ARM MPCore Boot and Synchronization Example Code)"

iadddocumentation  \
        -name Limitations  \
        -text "BareMetal platform for execution of ARM binary uKernel file"

iadddocumentation  \
        -name Reference  \
        -text "http://www.arm.com/products/processors/cortex-a/arm-mpcore-sample-code.php"

ihwaddmodule -instancename sys0 -vendor imperas.ovpworld.org -library module -type ArmuKernel -version 1.0
# set logfile so unique
ihwsetparameter  -handle sys0 -name uart1logname -value "uart0_1.log" -type string

ihwaddmodule -instancename sys1 -vendor imperas.ovpworld.org -library module -type ArmuKernel -version 1.0
# set logfile so unique
ihwsetparameter  -handle sys1 -name uart1logname -value "uart1_1.log" -type string

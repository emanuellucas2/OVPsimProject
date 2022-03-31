
 Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com

 The contents of this file are provided under the Software License
 Agreement that you accepted before downloading this file.

 This source forms part of the Software and can be used for educational,
 training, and demonstration purposes but cannot be used for derivative
 works except in cases where the derivative works require OVP technology
 to run.

 For open source models released under licenses that you can use for
 derivative works, please visit www.ovpworld.org or www.imperas.com
 for the location of the open source models.



File:README.txt

INTRODUCTION -------------------------------------------------------

This directory contains an example of using client-specific callbacks
to save and restore processor and memory state.

The platform source may be found in platform/platform.c. The
included Makefile will compile and link the platform.

The sample application does a variety of secure and non-secure 
memory accesses with and without TLB mapping. The included Makefile
will compile and link the application. It requires that the arm 
toolchain package has been installed.

To compile and run the example use the command:
    make run


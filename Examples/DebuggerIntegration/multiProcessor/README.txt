 
  Copyright (c) 2005-2021 Imperas Software Ltd. All Rights Reserved.

  The contents of this file are provided under the Software License
  Agreement that you accepted before downloading this file.

  This source forms part of the Software and can be used for educational,
  training, and demonstration purposes but cannot be used for derivative
  works except in cases where the derivative works require OVP technology
  to run.

  For open source models released under licenses that you can use for
  derivative works, please visit www.ovpworld.org or www.imperas.com
  for the location of the open source models.


FILE:Imperas/Examples/DebuggerIntegration/multiProcessor/README.txt


INTRODUCTION -------------------------------------------------------
This directory contains one of the examples from the Advanced Simulation 
Control of Platforms and Modules User Guide.

It should be used in conjunction with the user guide but is briefly 
described here.

This example shows the use of the OP debug interface available in the 
Imperas professional simulator. This is not available in OVPsim.

FILES --------------------------------------------------------------
There are three parts to the example
1. The applications; these are found as application/*.[ch]
2. An OP module; this is found as module/module.op.tcl
3. A harness that loads the OP module and implements the
   example of debugger integration; this is found as harness/harness.c
   
Each of these directories includes a Makefile with these targets:

all - this will build all the files in the directory
clean - this will remove all files created by a build 


BUILDING THE SIMULATION --------------------------------------------
To build the application

> make -C application

To build the OP module

> make -C module

To build the harness

> make -C harness

RUNNING THE EXAMPLE ------------------------------------------------

> harness/harness.<IMPERAS_ARCH>.exe --argv application/constitution.txt


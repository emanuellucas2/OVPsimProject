 
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


FILE:Imperas/Examples/Models/Peripherals/blockingCallback/README.txt


INTRODUCTION -------------------------------------------------------
This directory contains examples to be used in conjunction with the 
OVP Peripheral Modeling Guide

This directory contains an example which shows how to model a peripheral
register that blocks the application processor when it is read or written


FILES --------------------------------------------------------------

Peripheral Model:

    pse.tcl
        Defines a peripheral with one register.
   
    peripheral.user.c 
        Code for the behaviour of the register when read or written.

Test Application:

    application.c
        Reads and writes the register in the peripheral

Virtual Platform Hardware Definition:

    module.op.tcl
        A module containing a processor, memory and the peripheral.


RUNNING THE EXAMPLE -----------------------------------------------

example.sh  (Linux)
example.bat (Windows)


    
    

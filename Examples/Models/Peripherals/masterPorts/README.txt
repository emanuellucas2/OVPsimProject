 
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


FILE:Imperas/Examples/Models/Peripherals/masterPorts/README.txt

DESCRIPTION --------------------------------------------------------

This example shows the creation and use of master ports in a
peripheral model.

The example contains
1) A peripheral model with multiple master ports, defined in iGen
2) A module hardware definition, instantiating the peripheral and a memory.
 
RUNNING THE EXAMPLES -----------------------------------------------

Creating the Peripheral Model
     The peripheral model is generated using the iGen tool and then compiled,
     including the user behavioral code with the PSE toolchain.

    To build the module and peripheral model:

    > make all 
    
Running the example
    To run the example the default harness is used to load the hardware module 
    and the application using the command line (shown for Linux):
    
    > harness.exe \
         --modulefile module/model.so

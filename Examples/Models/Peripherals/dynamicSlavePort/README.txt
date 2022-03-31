 
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


FILE:Imperas/Examples/Models/Peripherals/dynamicSlavePort/README.txt

DESCRIPTION --------------------------------------------------------

This example shows the creation and use of a dynamic slave port in a
peripheral model. The initial address of the slave register interface 
is fixed at 0x10000000 but can be modified by writing to the 'remap'
register defined at the base of the slave port.
The example contains
1) A peripheral model with a dynamic slave port, defined in iGen
2) A module hardware definition, instantiating the peripheral, a processor and
   memory.
3) A test application to execute on the processor to access the slave registers, 
   cause a remapping to an address 0x10000100 and further access at the new
   address. It finally attempts an access to the 'old' base address of the 
   registers that will fail.
 
RUNNING THE EXAMPLES -----------------------------------------------

Creating the Peripheral Model
     The peripheral model is generated using the iGen tool and then compiled,
     including the user behavioral code with the PSE toolchain.

Building Application Executable
    A Makefile is included that uses the Imperas cross compiler installation to
    build test application code for the ARM7TDMI processor. Makefiles are also 
    included to build the hardware module definition and the peripheral model. A 
    top level Makefile is also provided that calls each of these.

    To build the application, module and peripheral model:

    > make all 
    
Running the example
    To run the example the default harness is used to load the hardware module 
    and the application using the command line (shown for Linux):
    
    > harness.exe \
         --modulefile module/model.so \
         --program application/application.ARM7TDMI.elf

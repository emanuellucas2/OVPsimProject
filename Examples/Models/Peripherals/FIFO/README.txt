 
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

DESCRIPTION --------------------------------------------------------

This example shows two peripheral models communicating using FIFOs

RUNNING THE EXAMPLES -----------------------------------------------

Creating the Peripheral Model Template
     The peripheral model template is created using the iGen tool.


    To build the module or peripheral model:

    > make -C module       NOVLNV=1 
    > make -C peripheral   NOVLNV=1 
    
Running the example
    To run the example use the command :
    
    > harness.exe --modulefile module/model

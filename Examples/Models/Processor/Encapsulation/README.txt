 
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

FILES ---------------------------------------------------------------

risc32.c        Shows an example encapsulation layer for an ISS

DIRECTORIES ---------------------------------------------------------

'application' contains a simple assembler testcase to run on the
              dummy "risc32" processor.
'platform'    contains a platform that instantiates a processor
'externalISS' contains code to interpret instructions and provide
              behavior for the dummy processor "risc32". Used as 
              a non-OVP ISS encapsulated and used in OVP.

BUILDING ------------------------------------------------------------
   The processor model, platform executable and the assembler and/or 
   application source files are built using the Makefile
   
   > make
   
RUNNING --------------------------------------------------------------
    The example is executed by running the platform executable
    The processor executable file is hardcoded to the model in externalISS
    The file it will load is called 'testcase.risc32'
    
    > ./platform.exe -program testcase.risc32

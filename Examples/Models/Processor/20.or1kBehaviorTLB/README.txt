 
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


BUILDING ------------------------------------------------------------
   The processor model, platform executable and the assembler and/or 
   application source files are built using the Makefile
   
   > make
   
RUNNING --------------------------------------------------------------
    The example is executed by running the platform or harness executable
    and passing the elf file using the --program argument
    
    > ./platform/harness.${IMPERAS_ARCH}.exe \
        --program application/asmtest.OR1K.elf
    
    NOTE: Each example may have both or either an assembler or C based
    application file. 

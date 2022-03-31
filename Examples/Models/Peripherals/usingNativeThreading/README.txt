 
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


RUNNING THE EXAMPLES -----------------------------------------------

Creating the Peripheral Model Template
     The peripheral model C code template is generated using the Model Generator
     tool, igen.exe.

Building Executables
    Makefiles are included that use the standard imperas build environment 
    and a cross compiler installation.
    These build the application, the OVP virtual platform and the peripheral
    pse behavioral executable. 
    To build all parts of the example use the following commands and set the
    number of peripherals to be included between 2 and 6 or more dependent upon
    host machine processors available (Host Os, Simulator core + peripherals).
    On an 8 core machine the maximum is 6 peripherals.

> export PERIPHERALS=6
 
> make -C application               clean all
> make -C module           NOVLNV=1

> make -C peripheral/pse   NOVLNV=1 
> make -C peripheral/model NOVLNV=1 
    
Running the example
    The example is run from the command line using the following
    
> harness.<OS>.exe --modulefile module/model.so \
                   --program application/dataSortTest.ARM7TDMI.elf

To run the example using the Multi-Core Host Interface for peripheral
models, that will use native threading to utilize multiple processors 
of the host machine, add '--parallelperipherals' to the command

> harness.<OS>.exe --modulefile module/model.so \
                   --program application/dataSortTest.ARM7TDMI.elf \
                   --parallelperipherals

There are a number of peripherals running a sort algorithm on pseudo randomly
seeded memory buffers. All peripheral models will be enabled for threaded 
operation. If your host machine has less than 8 processor cores available
(Host Os, Simulator core + peripherals)

The peripheral models can also be executed in a register interface only
mode to show the application simulation performance when not limited by 
the peripheral engine processing. The parameter 'registeronly' on the 'sort' 
peripherals can be overridden by adding
    --override peripheralNativeThreadTest/sort*/registeronly=T

> harness.exe \
    --modulefile module/model.${IMPERAS_SHRSUF} \
    --program application/dataSortTest.ARM7TDMI.elf \
    --override peripheralNativeThreadTest/sort*/registeronly=T
    
The peripheral model native execution is invoked from within the PSE behavioral
code. The PSE code will always wait for the native portion to complete execution
before proceeding. However, the minimum can be controlled in two ways
1) By simulation time, or
2) By quantum boundary    

If by simulation time the peripheral will appear to always take a fixed period
of simulation time to complete the operation, this maintains a deterministic 
simulation.
If by quantum delay the peripheral will continue on the next quantum boundary 
after the peripheral native behaviour has complete. this has the effect that the
simulation will no longer me deterministic i.e. depending upon the host machine
loading the native behaviour may take different numbers of quantum to complete.  

By default, the peripheral will operate with a 30mS simulation time delay. To 
select the quantum boundary approach the parameter 'quantumdelay' on the 'sort'
peripherals can be overridden by adding
    --override peripheralNativeThreadTest/sort*/quantumdelay=T

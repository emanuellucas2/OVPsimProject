 
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


FILE:Imperas/Examples/SimulationControl/processorResetControlPeripheral/README.txt

INTRODUCTION -------------------------------------------------------
This example shows that a 'reset' net can be used to reset a 
processor. the 'reset' net is driven active by a peripheral model that
can be commanded using a standard socket interface.


FILES --------------------------------------------------------------
There are three parts to the example
1. An application; this is found as application/fibonacci.c
2. A module; module/module.op.tcl defines the hardware.
3. A peripheral; the user code is found as peripheral/user.c

BUILDING THE SIMULATION --------------------------------------------
To build the application

> make -C application CROSS=ARM7TDMI

To build the platform

> make -C platform NOVLNV=1

To build the peripheral

> make -C peripheral NOVLNV=1

RUNNING THE EXAMPLE ------------------------------------------------
Below shows the command line for Linux that is contained in example.sh.
See the corresponding script in example.bat for the Windows command line.

> platform/platform.${IMPERAS_ARCH}.exe \
        --program application/fibonacci.${CROSS}.elf \
        --override systemReset/resetGeneration/console=1 \
        --override systemReset/resetGeneration/finishOnDisconnect=1  \
        --output imperas.log

This will open a console window connected to the peripheral socket.

In the socket type 
  'r' to force a reset
      the peripheral will toggle the reset line connected to its reset port 
  'q' to finish/terminate the simulation 
      the peripheral will call the bhmFinish() API function which will stop
      the simulation. 

PERIPHERAL SOCKET PARAMETERS -----------------------------------------
Standard options on peripherals using BHM sockets
   console : when set to 1 a port will automatically be opened and 
             a terminal will be started and attached
   portnum : A TCP/IP port will be opened on port 'portnum' and wait for
             a connection. If 0 is used the next available port in the system
             is used. 
             a terminal will be started and attached
   finishOnDisconnect : when set to 1 the simulation is terminated when the 
             socket is disconnected. 
 

 
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


FILE:Imperas/Examples/Models/Peripherals/connectTwoPlatformsWithUarts/README.txt


INTRODUCTION -------------------------------------------------------

This example shows how a peripheral model (A UART) can use a socket to 
communicate with a model in another simulation. 

FILES --------------------------------------------------------------
1. An application; application/application.c
2. A Module; 
    module/module.op.tcl       the module description for input to iGen

BUILDING and EXECUTING ---------------------------------------------

> ./example.sh (or example.bat)

In this script, the first simulation creates a listening socket (a server).
The second simulation (a client) then connects to the first and data is exchanged.

Note that data although data is sent one way, it could be sent in either direction.

This example can demonstrate the use of non-blocking connections, but not in a script:

You will need two terminals to work in with the same environment and in the
same working directory.

First start the server simulator, non blocking:

harness.exe    \
    --modulefile module/model  \
    --program    applicationSendForever/application.OR1K.elf  \
    --override   simpleCpuMemoryUart/periph0/client=0    \
    --override   simpleCpuMemoryUart/periph0/portnum=4444   \
    --override   simpleCpuMemoryUart/periph0/connectnonblocking=1
    
Note that the application is now running - it printed:

applicationSend: Initializing KinetisUART
applicationSend: Writing to uart [Hello UART0 world]

Now in the other terminal, start another simulator in client mode.

harness.exe    \
    --modulefile module/model  \
    --program    applicationReceive/application.OR1K.elf  \
    --override   simpleCpuMemoryUart/periph0/client=1    \
    --override   simpleCpuMemoryUart/periph0/portnum=4444   \
    --override   simpleCpuMemoryUart/periph0/connectnonblocking=1
    
Note that the simulators are now exchanging data.
You can now kill (interrupt) either simulator. The other will continue to execute,
but the application will wait until more data can be sent or received.
Restarting the other simulator will resume communication.

You can run either application in either simulator.





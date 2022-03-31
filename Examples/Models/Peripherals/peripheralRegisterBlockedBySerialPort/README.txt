
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

This is an example of using the blocking BHM socket interface to block an
application processor. 

** platform
The platform contains a module with
   A RISCV processor (RV32I)
   Memory
   A peripheral with a socket interface
   
** Peripheral
The peripheral automatically connects a bi-directional serial port to a socket.
It has a transmit and a receive register, each triggering a callback.
Each callback will block if the serial interface is unable to complete the transaction.

**Application
Two instances of the platform are created:
 one runs a simple transmit program that sends characters to the serial interface.
 one runs a simple receive program that reads characters from the serial interface.
 In each case, if the interface is not ready, the processor running the application will
 be blocked until it is.

RUNNING ------------------------------------------------------------

run example.sh or example.bat


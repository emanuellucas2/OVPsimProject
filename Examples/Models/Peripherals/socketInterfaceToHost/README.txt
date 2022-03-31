
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

This is an example of using the BHM socket interface to exchange data 
with a host application. 

The test platform contains
   RISCV processor (RV32I)
   memory
   peripheral with socket interface
   
** Peripheral
The peripheral named "socketInterface" provides an interface to the processor
to provide control and a socket interface. The socket interface passes a 
fixed size message defined by a structure in common/exchangeData.h which is
used by both the peripheral, the host application and the RISCV application.

Note:
The same little endian data ordering and same variable types are used in all
three so this does not need to be taken into account when transferring data
between the different domains.

The peripheral processor interface provides DMA control for both a transmit and
receive message buffer. When enabled a message written into the transmit buffer
will be sent over the socket interface to the host application and a message
from the host application will be written into the receive buffer.

** Host Application
The host application is a simple socket interface that expects to receive a 
message and then respond with a message. the sent messages are defined in an
input data file as text.

When the host application has sent all its messages the it will set an end 
simulation bit on the next message which propagates through the system and 
stops the simulation.

RUNNING ------------------------------------------------------------

To run this example you will need to compile using the Makefiles in the
directories: 
  riscvApplication : application program to execute on RISC-V processor
  hostApplication  : host native application
  source           : VLNV library

This can also be done using the provided script BUILD.sh(.bat)

The virtual platform simulation and the native application must be started
in separate shells/terminals

** Start the virtual platform simulation

 $ ./RUN.sh
 
This will start the simulation and wait for a socket connection. The socket
number can be set to a specific value by changing the port specified on the
line 

  --override test/sktIf/portnum=<port number>

By default this is set to 0, which allows the host machine to allocate the 
next available port.
The port number will be written to the file 'sktport.txt' or can be obtained
from the displayed startup message

  Info (PSE_SER) 'test/sktIf' Waiting for connection on port <port number>

** Start the host application in another shell

The host application requires that the host, port and a data file (containing 
messages to send) are specified.

 $ cd hostApplication
 $ ./hostApp.exe localhost <port number> test.data.txt

The two applications will exchange several messages over the socket interface

The simulation will terminate when all messages in the data file have been sent.

** host application data message content format

The data file messages are of the form
  TIME <time in microseconds> [us]
  DATA <length> <data0> <data1> <data2> ... <dataN>

The time messages are sent to the peripheral but are unused in this example. They
could be used to provide a mechanism to synchronize the time between the host and
the simulation.


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
    This is an example of packetnet usage in a realistic peripheral model that
    includes a buffer allowing a processor to read/write a packet plus status
    and control registers and nets supporting the flow of data through a chain
    of nodes.
    
    A peripheral named "node" is defined. This peripheral has one input and
    one output packetnet port for connecting to adjacent peripheral instances,
    plus control and status registers and Tx/Rx message buffers accessible
    by a processor.
    
    A data packet can be both:
        - written by a processor into the TX buffer and then triggered
          by writing to the control register
        - received from the previous node in the chain on the packetnet
          port "pin"
    When a packet of data is received by a node it will:
        - perform processing, with a simulated delay
        - write the processed data to the next node, if it is ready to
          receive data, otherwise set the status.waitingtosend bit and
          wait for either the next node to become available or for the
          processor to clear the status.waitingtosend bit
    
    An example module named "test" is defined where the node peripheral is
    instanced 4 times in a daisy chain, with the packetnet output of each node
    connected to the packetnet input of the next node.
    
    There is a RISCV processor and application that writes some data into the
    first node's transmit buffer and then writes to its control register to
    start the processing. The application reports all of the nodes status
    registers periodically and when a node's status indicates it is waiting
    to send a packet, the application reads the packet from the node's RX buffer
    and displays the packet data.
    
    New data is written by the application three times, with different data on
    each iteration. A node's waiting flag is only cleared in the first loop,
    which eventually results in a stall, at which point the data in all waiting
    nodes is reported.
    
    A VLNV tree is used to organize the peripheral model and the module
    definition source and executable files.

RUNNING THE EXAMPLES -----------------------------------------------

Creating the Peripheral Model Template
    The peripheral model template is created using the iGen tool.

Building and Running the Example
    Makefiles are included that use the Imperas cross compiler installation to
    build the peripheral model and the test application code for the RISCV
    processor and the host compiler to build the module definition. The module
    is run under the Imperas standard test harness, harness.exe.
    
    To build and run the example on Linux or in a Windows Msys shell:
    
    > ./example.sh
    
    Or in a Windows command shell:
    
    > .\example.bat
    
    Similarly, the CLEAN.sh or CLEAN.bat script may be used to remove the
    generated files.


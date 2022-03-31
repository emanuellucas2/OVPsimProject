Copyright (c) 2005-2021 Imperas Ltd. All Rights Reserved.

Name
----
    altera.ovpworld.org/peripheral/Uart/1.0


Bus interfaces
--------------
    Slave Port:        sp1

Net connections
---------------
    output: irq
    output: endofpacket
    output: dataavailable
    output: readyfordata
    input : RXD
    input : CTS
    output: TXD
    output: RTS

Formal attributes
-----------------
    uns64        : baud
    uns64        : dataBits
    uns64        : fixedBaud
    enumeration  : parity
        Options: None, Even, Odd
    uns64        : stopBits
    uns64        : syncRegDepth
    uns64        : useCtsRts
    uns64        : useEopRegister



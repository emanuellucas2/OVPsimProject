Copyright (c) 2005-2021 Imperas Ltd. All Rights Reserved.

Name
----
    riscv.ovpworld.org/peripheral/PLIC/1.0


Bus interfaces
--------------
    Slave Port:      port0

Net connections
---------------
    input : reset
    input : irqS1
    output: irqT0

Formal attributes
-----------------
    Uns32        : num_sources
    Uns32        : num_targets
    Uns32        : num_priorities
    Uns32        : priority_base
    Uns32        : pending_base
    Uns32        : enable_base
    Uns32        : enable_stride
    Uns32        : context_base
    Uns32        : context_stride



Copyright (c) 2005-2021 Imperas Ltd. All Rights Reserved.

Name
----
    xilinx.ovpworld.org/peripheral/axi-intc/1.0


Bus interfaces
--------------
    Slave Port:     bport1

Net connections
---------------
    input : intr%u
    input : irq_in
    input : irq_addr_in
    output: irq_ack_out
    output: irq
    input : irq_ack
    output: irq_addr_out

Formal attributes
-----------------
    boolean      : C_HAS_IPR
    boolean      : C_HAS_SIE
    boolean      : C_HAS_CIE
    boolean      : C_HAS_IMR
    boolean      : C_HAS_FAST
    boolean      : C_EN_CASCADE_MODE
    boolean      : C_CASCADE_MASTER
    uns32        : C_NUM_INTR_INPUTS
    uns32        : C_NUM_SW_INTR



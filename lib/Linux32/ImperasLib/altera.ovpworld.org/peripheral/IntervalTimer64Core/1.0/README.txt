Copyright (c) 2005-2021 Imperas Ltd. All Rights Reserved.

Name
----
    altera.ovpworld.org/peripheral/IntervalTimer64Core/1.0


Bus interfaces
--------------
    Slave Port:        sp1

Net connections
---------------
    output: irq
    output: resetrequest
    output: timeout_pulse

Formal attributes
-----------------
    uns64        : timeoutPeriod
    double       : timerFrequency
    enumeration  : timeoutConfig
        Options: Simple, Full, Watchdog
    bool         : writeablePeriod
    bool         : readableSnapshot
    bool         : startStopControlBits
    bool         : timeoutPulse
    bool         : systemResetOnTimeout



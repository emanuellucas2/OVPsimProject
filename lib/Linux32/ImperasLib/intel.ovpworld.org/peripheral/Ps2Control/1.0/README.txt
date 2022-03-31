Copyright (c) 2005-2021 Imperas Ltd. All Rights Reserved.

Name
----
    intel.ovpworld.org/peripheral/Ps2Control/1.0


Bus interfaces
--------------
    Slave Port:     config

Net connections
---------------
    output: kbdInterrupt
    output: mouseInterrupt
    input : reset

Formal attributes
-----------------
    bool         : disableInput
    uns32        : pollPeriod
    bool         : grabDisable
    bool         : cursorEnable
    bool         : isMouse
    bool         : isKeyboard



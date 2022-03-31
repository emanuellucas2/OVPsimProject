Copyright (c) 2005-2021 Imperas Ltd. All Rights Reserved.

Name
----
    riscv.ovpworld.org/peripheral/SmartLoaderRV64Linux/1.0


Bus interfaces
--------------
    Master Port:      mport

Net connections
---------------
    (none)

Formal attributes
-----------------
    string       : dtb
    string       : command
    string       : append
    address      : membase
    address      : memsize
    address      : slbootaddr
    string       : bootimage
    address      : bootaddr
    enumeration  : bootconvention
        Options: bbl, fsbl
    bool         : disable



#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

# set the number of peripherals to be used for module and application
# If this is changed please ensure you perform a clean
export PERIPHERALS=2

make -C application
make -C module           NOVLNV=1

make -C peripheral/pse   NOVLNV=1
make -C peripheral/model NOVLNV=1

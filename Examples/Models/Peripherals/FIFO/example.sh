#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

# compile the design
make -C module     NOVLNV=1

# compile the peripheral (used in design)
make -C peripheral NOVLNV=1

# run the module
make simulate \
         $@

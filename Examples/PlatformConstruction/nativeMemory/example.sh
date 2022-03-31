#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K

# compile the application
make -C application CROSS=${CROSS}

# generate and compile the iGen created module
make -C module 

# run the module using the harness
harness.exe --modulefile module/model.${IMPERAS_SHRSUF} --program application/application.OR1K.elf $*

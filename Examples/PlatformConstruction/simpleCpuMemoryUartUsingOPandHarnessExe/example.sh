#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K

# compile the application
make -C application CROSS=${CROSS}

# generate and compile the module
make -C module

# run the platform
harness.exe \
    --modulefile module/model.${IMPERAS_SHRSUF} \
    --program application/application.${CROSS}.elf \
    $*

echo "-- uartTTY0.log contents --"
cat uartTTY0.log


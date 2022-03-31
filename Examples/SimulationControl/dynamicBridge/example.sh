#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K

# compile the application
make -C application CROSS=${CROSS}

# generate and compile the iGen created platform
make -C module
make -C harness

# run the testbench harness
harness/harness.${IMPERAS_ARCH}.exe \
         --program application/asmtest.${CROSS}.elf \
         --trace --tracechange $*

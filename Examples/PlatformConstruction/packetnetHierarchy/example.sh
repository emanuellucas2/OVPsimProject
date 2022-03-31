#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K

# compile the testbench
make -C harness

# compile the design
make -C module

# compile the peripheral (used in design)
make -C peripheral

# compile the app
make -C application CROSS=${CROSS}


# run the platform
harness/harness.${IMPERAS_ARCH}.exe \
         --program application/pktModelTest.${CROSS}.elf $*


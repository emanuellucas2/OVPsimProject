#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

# compile the test application
CROSS=OR1K
make -C application CROSS=${CROSS}

# compile the harness
make -C harness

# compile the module design
make -C module

# run the platform
harness/harness.${IMPERAS_ARCH}.exe --program top/uut/cpu1=application/application.${CROSS}.elf $*



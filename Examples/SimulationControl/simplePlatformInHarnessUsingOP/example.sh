#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K

make -C application CROSS=${CROSS}

make -C harness

# run the platform
./harness/harness.${IMPERAS_ARCH}.exe \
    --program application/application.${CROSS}.elf $*

echo "-- uartTTY0.log contents --"
cat uartTTY0.log


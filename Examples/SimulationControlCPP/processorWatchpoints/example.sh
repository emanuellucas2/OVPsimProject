#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K

#  compile the application
make -C application CROSS=${CROSS}

make -C platform

# IMPERAS_OP_TRACE=1 \

./platform/platform.${IMPERAS_ARCH}.exe \
    -program application/asmtest.${CROSS}.elf \
    -output simulate.log -trace \
    $*




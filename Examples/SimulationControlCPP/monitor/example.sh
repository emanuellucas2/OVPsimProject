#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K

make -C application CROSS=${CROSS}

make -C platform

./platform/platform.${IMPERAS_ARCH}.exe \
    -program application/application.${CROSS}.elf \
    -output simulate.log \
    $*




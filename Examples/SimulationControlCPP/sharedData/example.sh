#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K

#  compile the application
make -C application CROSS=${CROSS}

make -C platform NOVLNV=1

make -C plugin NOVLNV=1

./platform/platform.${IMPERAS_ARCH}.exe \
    -program application/application.${CROSS}.elf \
    -output simulate.log \
    $*

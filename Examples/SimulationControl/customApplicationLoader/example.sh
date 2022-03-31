#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K
make -C application CROSS=${CROSS}

make -C loader

make -C harness
make -C module


harness/harness.${IMPERAS_ARCH}.exe --program application/hello.${CROSS}.s19 $*

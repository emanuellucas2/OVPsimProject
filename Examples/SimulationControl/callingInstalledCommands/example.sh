#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit


CROSS=IMG_MIPS32R2

make -C application CROSS=${CROSS}
make -C harness
make -C module

harness/harness.${IMPERAS_ARCH}.exe \
            --program application/application.${CROSS}.elf \
            $*

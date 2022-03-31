#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit


CROSS=OR1K

make -C application CROSS=${CROSS}

make -C peripheral

make -C module
make -C harness


harness/harness.${IMPERAS_ARCH}.exe \
            --program top/u1/cpu1=application/application1.${CROSS}.elf \
            --program top/u1/cpu2=application/application2.${CROSS}.elf \
            $*

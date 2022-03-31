#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit


CROSS=OR1K

make -C application CROSS=${CROSS}
make -C module
make -C harness

./harness/harness.${IMPERAS_ARCH}.exe \
            --program application/asmtest.${CROSS}.elf \
            --trace --tracechange --traceshowicount    \
            $*

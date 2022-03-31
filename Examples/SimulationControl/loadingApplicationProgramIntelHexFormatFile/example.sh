#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit


CROSS=RISCV32

make -C application CROSS=${CROSS}

make -C harness

make -C module

harness/harness.${IMPERAS_ARCH}.exe \
           --intelhexfile application/asmtest.${CROSS}.hex \
           --diagnostics 1 \
           --finishafter 100 \
           --trace $*

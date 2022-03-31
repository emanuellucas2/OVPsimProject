#!/bin/bash

# stop on error
set -e

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

make -C harness          NOVLNV=1
make -C module           NOVLNV=1
make -C intc/pse         NOVLNV=1
make -C application

./harness/harness.${IMPERAS_ARCH}.exe \
            --program application/interruptTest.RISCV32.elf \
            "$@"

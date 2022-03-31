#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

harness.exe \
    --output imperas.log \
    --verbose \
    \
    --vlnvroot     lib/${IMPERAS_ARCH} \
    --modulevendor imperas.ovpworld.org --modulename test \
    \
    --program  test/cpu=riscvApplication/application.RISCV32.elf \
    \
    --override test/sktIf/portnum=0 \
    --override test/sktIf/portFile=sktport.txt \
    \
    "$@"


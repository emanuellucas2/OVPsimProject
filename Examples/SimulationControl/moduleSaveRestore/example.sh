#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K

make -C application CROSS=${CROSS}

make -C module

make -C harness

# run from start to end 
./harness/harness.${IMPERAS_ARCH}.exe \
    --program application/application.${CROSS}.elf \
    --output run.log \
    $*

# run for 100 instructions, then save the state and finish
./harness/harness.${IMPERAS_ARCH}.exe \
    --program application/application.${CROSS}.elf \
    --save save.dat   \
    --output save.log \
    $*

# restore from state save file then run to end
./harness/harness.${IMPERAS_ARCH}.exe \
    --program application/application.${CROSS}.elf \
    --restore save.dat   \
    --output restore.log \
    $*

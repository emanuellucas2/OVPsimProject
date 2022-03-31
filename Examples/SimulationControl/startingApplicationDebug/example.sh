#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K

# compile the fibonacci application
make -C application CROSS=${CROSS}

# generate and compile the iGen created module
make -C module 

# compile the hand coded C harness
make -C harness

# run the module using the local C harness

# start debug of cpu1 with GDB
harness/harness.${IMPERAS_ARCH}.exe \
     --program application/fibonacci.${CROSS}.elf \
     --gdbconsole --debugprocessor u1/cpu1 \
     $*

# start debug of cpu1 with GDB using harness
harness/harness.${IMPERAS_ARCH}.exe \
     --program application/fibonacci.${CROSS}.elf \
     --configurecpuinstance \
     $*
     
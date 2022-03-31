#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K

# compile the application
make -C application CROSS=${CROSS}

# generate and compile the iGen created module
make -C platform

# run the module using the harness

IMPERAS_TLM_MEMORY_TRACE=1 \
IMPERAS_TLM_DECODE_TRACE=1 \
IMPERAS_TLM_CPU_TRACE=1 \
    platform/platform.${IMPERAS_ARCH}.exe -program application/hello.OR1K.elf


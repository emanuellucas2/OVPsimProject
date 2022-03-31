#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit


CROSS=OR1K

# build application
make -C application CROSS=${CROSS}

# build module and harness
make -C module
make -C harness

# run with custom scheduler
harness/harness.${IMPERAS_ARCH}.exe \
           --program application/application.${CROSS}.elf \
           --override u1/uartTTY0/diagnosticlevel=3 \
           --output custom.log \
           --custom \
           $*

# run with standard scheduler
harness/harness.${IMPERAS_ARCH}.exe \
           --program application/application.${CROSS}.elf \
           --override u1/uartTTY0/diagnosticlevel=3 \
           --output standard.log \
           $*

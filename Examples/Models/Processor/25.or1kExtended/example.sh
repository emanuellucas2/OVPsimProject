#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

# Make all targets required for this example
make all
    
platform/harness.${IMPERAS_ARCH}.exe \
    -vlnvroot vlnv \
    -program application/asmtest.OR1K.elf \
    -trace \
    -output simulate.log


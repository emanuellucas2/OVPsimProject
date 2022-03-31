#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K

# compile the application
make -C application CROSS=${CROSS}

# generate and compile the iGen created module
make -C module 

# run the module using the standard harness
# run without simulating exceptions
echo "Processor not simulating exceptions"
harness.exe --modulefile module/model.${IMPERAS_SHRSUF} \
            --program application/asmtest.${CROSS}.elf \
            --trace \
            $*

# run with simulating exceptions
echo "Processor simulating exceptions"
harness.exe --modulefile module/model.${IMPERAS_SHRSUF} \
            --program application/asmtest.${CROSS}.elf \
            --trace \
            --override simpleCpuMemory/cpu1/simulateexceptions=1 \
            $*

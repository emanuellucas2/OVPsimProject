#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K

make -C application CROSS=${CROSS}

# generate and compile the iGen created module
make -C processorSubSystem
make -C sharedMemorySubSystem
make -C topLevel

# run the module using the harness
harness.exe --modulefile topLevel/model.${IMPERAS_SHRSUF} \
            --program topLevel/sys0/cpu=application/appSys0.${CROSS}.elf \
            --program topLevel/sys1/cpu=application/appSys1.${CROSS}.elf \
            --output imperas.log \
            $*

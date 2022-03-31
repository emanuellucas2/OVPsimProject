#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit


CROSS=OR1K

make -C application CROSS=${CROSS}

make -C peripheral

make -C module

# load application without changing the start PC from the reset vector
harness.exe --modulefile module \
            --objfilenoentry application/asmtest.${CROSS}.elf \
            --override processorExternalInterrupt/timerPeripheral/diagnosticlevel=3 \
            $*

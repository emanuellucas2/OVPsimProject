#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K

make -C application CROSS=${CROSS}

make -C module

# run the platform
harness.exe --modulefile module/model.${IMPERAS_SHRSUF} \
            --program application/application.${CROSS}.elf \
            $*

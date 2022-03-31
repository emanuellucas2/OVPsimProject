#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K

make -C application CROSS=${CROSS}

# generate and compile the iGen created module
make -C module 

# run the module using the harness
harness.exe --modulefile module/model.${IMPERAS_SHRSUF} \
            --program twoProcessorShared/P0=application/encrypt.${CROSS}.elf \
            --program twoProcessorShared/P1=application/decrypt.${CROSS}.elf \
            $* \
            --argv application/constitution.txt

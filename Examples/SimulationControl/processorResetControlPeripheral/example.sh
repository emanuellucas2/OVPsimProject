#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit


CROSS=ARM7TDMI

make -C application CROSS=${CROSS}

make -C module     NOVLNV=1
make -C peripheral NOVLNV=1

harness.exe \
        --modulefile module/model.${IMPERAS_SHRSUF} \
        --program application/fibonacci.${CROSS}.elf \
        --override systemReset/resetGeneration/console=1 \
        --override systemReset/resetGeneration/finishOnDisconnect=1  \
        --output imperas.log \
        $*
      

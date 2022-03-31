#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=OR1K
make -C application CROSS=${CROSS}
make -C module NOVLNV=1

harness.exe --modulefile module/model.${IMPERAS_SHRSUF} \
            --gdbconsole \
            --program application/application.${CROSS}.elf \
            $*


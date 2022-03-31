#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

make -C application
make -C module           NOVLNV=1 
make -C peripheral/pse   NOVLNV=1
make -C peripheral/model NOVLNV=1

# set channel 1 to execute as native code and native diagnostics to high
harness.exe --modulefile module/model.${IMPERAS_SHRSUF} \
            --program application/dmaTest.RISCV32.elf \
            --override rv32WithDMACPeripheral/dmac/readNativeDataChannel=1 \
            --override rv32WithDMACPeripheral/dmac/diagnosticlevel=0xe \
            "$@"

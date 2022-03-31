#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

make -C application
make -C module       NOVLNV=1 
make -C peripheral   NOVLNV=1
 
harness.exe \
    -modulefile module \
    -program application/application.RISCV32.elf \
    -output imperas.log
 

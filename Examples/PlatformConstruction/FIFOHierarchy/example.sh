#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit


# compile the top module
make -C topmodule

# compile the sub module
make -C submodule

# compile the app
make -C application

harness.exe \
    -modulefile topmodule/model.${IMPERAS_SHRSUF} \
    -program topmodule/mod0/cpu1=application/messageIn.elf \
    -program topmodule/mod1/cpu1=application/messageOut.elf \
    -override topmodule/mod*/cpu1/debugflags=2  \
    $*
    


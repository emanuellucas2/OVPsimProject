#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

VLNVSRC=$(pwd)/source
VLNVROOT=$(pwd)/lib/${IMPERAS_ARCH}

mkdir -p $VLNVROOT

make -C $VLNVSRC \
     -f ${IMPERAS_HOME}/ImperasLib/buildutils/Makefile.library \
        VLNVSRC=$VLNVSRC VLNVROOT=$VLNVROOT $@

make -C riscvApplication $@

make -C hostApplication $@



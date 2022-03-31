#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit


# Define location ov VLNV source and target directories
VLNVSRC=${PWD}/source
VLNVROOT=${PWD}/lib/${IMPERAS_ARCH}

# Must exist
mkdir -p ${VLNVROOT}

# Build peripheral and module in VLNV tree
make -C $PWD/source \
     -f ${IMPERAS_HOME}/ImperasLib/buildutils/Makefile.library \
        VLNVSRC=${VLNVSRC} VLNVROOT=${VLNVROOT}

# Build application
make -C application

# Run simulation
harness.exe \
    --output imperas.log --verbose \
    \
    --vlnvroot     ${VLNVROOT} \
    --modulevendor examples.ovpworld.org --modulename test \
    \
    --program  test/cpu=application/application.RISCV32.elf \
    \
    "$@"
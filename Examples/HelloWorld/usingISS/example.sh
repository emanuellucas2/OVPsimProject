#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

# Select CrossCompiler/Processor Type
CROSS=RISCV32
VENDOR=riscv.ovpworld.org
MODEL=riscv
VARIANT=RV32I

# Build Application
make -C application CROSS=${CROSS}

# Run ISS
${IMPERAS_ISS} \
    --program application/application.${CROSS}.elf \
    --processorvendor ${VENDOR} --processorname ${MODEL} --variant ${VARIANT} \
    --verbose $*
#
        
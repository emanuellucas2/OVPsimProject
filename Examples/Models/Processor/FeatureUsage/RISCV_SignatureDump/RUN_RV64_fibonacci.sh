#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=RISCV64
make -C application CROSS=${CROSS}

${IMPERAS_ISS} \
    --program application/fibonacci.RISCV64.elf \
    --processorvendor riscv.ovpworld.org --processorname riscv \
    --variant RVB64I --override iss/cpu0/add_Extensions=MACSU \
    --logfile fib.run.log \
    "$@"


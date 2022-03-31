#!/bin/bash

# Check Installation supports this example
checkinstall.exe -p install.pkg --nobanner || exit

CROSS=RISCV64
make -C application CROSS=${CROSS}

${IMPERAS_ISS} \
    --program application/fibonacci.RISCV64.elf \
    --processorvendor riscv.ovpworld.org --processorname riscv \
    --variant RVB64I --override iss/cpu0/add_Extensions=MACSU \
    --extlib iss/cpu0/sigdump=$IMPERAS_VLNV/riscv.ovpworld.org/intercept/signatureDump/1.0 \
    --override iss/cpu0/sigdump/SignatureFile=fib.sig.dat.txt \
    --override iss/cpu0/sigdump/StartSymbol="resultArray" \
    --override iss/cpu0/sigdump/ByteCount=48 \
    --override iss/cpu0/sigdump/SignatureAtEnd=T \
    --logfile fib.sig.run.log \
    "$@"
 

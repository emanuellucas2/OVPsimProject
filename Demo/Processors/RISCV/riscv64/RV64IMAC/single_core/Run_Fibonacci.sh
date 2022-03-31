#!/bin/bash
# Run_Fibonacci.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/fibonacci/fibonacci.RISCV64-O0-g.elf \
    --processorvendor riscv.ovpworld.org --processorname riscv --variant RV64IMAC \
    --numprocessors 1 --addressbits 37    \
    --override iss/cpu0/verbose=1    \
    "$@" \
    -argv 39


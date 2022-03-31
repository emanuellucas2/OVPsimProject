#!/bin/bash
# Run_Fibonacci.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/fibonacci/fibonacci.RISCV32GC-O0-g.elf \
    --processorvendor riscv.ovpworld.org --processorname riscv --variant RV32GCZfinx \
    --numprocessors 1     \
    --override iss/cpu0/verbose=1 --override iss/cpu0/mstatus_FS=1    \
    "$@" \
    -argv 39


#!/bin/bash
# Run_Linpack.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/linpack/linpack.RISCV32-O0-g.elf \
    --processorvendor openhwgroup.ovpworld.org --processorname riscv --variant CV32E40P \
    --numprocessors 1     \
    --override iss/cpu0/verbose=1    \
    "$@"



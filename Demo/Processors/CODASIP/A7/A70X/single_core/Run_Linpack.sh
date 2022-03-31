#!/bin/bash
# Run_Linpack.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/linpack/linpack.RISCV64-O0-g.elf \
    --processorvendor codasip.ovpworld.org --processorname riscv --variant A70X \
    --numprocessors 1     \
    --override iss/cpu0/verbose=1    \
    "$@"



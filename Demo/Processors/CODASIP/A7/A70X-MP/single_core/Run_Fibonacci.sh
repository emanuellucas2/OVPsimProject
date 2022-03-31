#!/bin/bash
# Run_Fibonacci.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/fibonacci/fibonacci.RISCV64-O0-g.elf \
    --processorvendor codasip.ovpworld.org --processorname riscv --variant A70X-MP \
    --numprocessors 1     \
    --override iss/cpu0/verbose=1    \
    "$@"



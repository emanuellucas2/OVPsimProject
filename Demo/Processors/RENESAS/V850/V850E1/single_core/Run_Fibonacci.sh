#!/bin/bash
# Run_Fibonacci.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/fibonacci/fibonacci.V850-O3-g.elf \
    --processorvendor renesas.ovpworld.org --processorname v850 --variant V850E1 \
    --numprocessors 1     \
    "$@" \
    -argv 39


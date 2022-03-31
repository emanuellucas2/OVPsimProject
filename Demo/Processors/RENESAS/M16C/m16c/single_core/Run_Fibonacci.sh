#!/bin/bash
# Run_Fibonacci.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/fibonacci_m16c/fibonacci_m16c.M16C-O2-g.elf \
    --processorvendor posedgesoft.ovpworld.org --processorname m16c --variant m16c \
    --numprocessors 1     \
    "$@" \
    -argv 30


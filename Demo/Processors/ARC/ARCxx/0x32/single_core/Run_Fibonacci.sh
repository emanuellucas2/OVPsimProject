#!/bin/bash
# Run_Fibonacci.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/fibonacci/fibonacci.ARC600-O3-g.elf \
    --processorvendor arc.ovpworld.org --processorname arc --variant 0x32 \
    --numprocessors 1     \
    "$@" \
    -argv 39


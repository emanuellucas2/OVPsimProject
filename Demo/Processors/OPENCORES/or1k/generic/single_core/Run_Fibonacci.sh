#!/bin/bash
# Run_Fibonacci.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/fibonacci/fibonacci.OR1K-O3-g.elf \
    --processorvendor ovpworld.org --processorname or1k --variant generic \
    --numprocessors 1     \
    "$@" \
    -argv 36


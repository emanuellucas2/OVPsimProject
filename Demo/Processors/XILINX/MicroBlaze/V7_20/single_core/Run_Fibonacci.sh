#!/bin/bash
# Run_Fibonacci.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/fibonacci_microblaze/fibonacci_microblaze.MICROBLAZE-O3-g.elf \
    --processorvendor xilinx.ovpworld.org --processorname microblaze --variant V7_20 \
    --numprocessors 1     \
    --parameter endian=big    \
    "$@" \
    -argv 39


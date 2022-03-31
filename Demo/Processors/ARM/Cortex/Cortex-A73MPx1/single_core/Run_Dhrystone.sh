#!/bin/bash
# Run_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.AARCH64-O3-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant Cortex-A73MPx1 \
    --numprocessors 1     \
    --parameter endian=little    \
    "$@" \
    -argv 10000000


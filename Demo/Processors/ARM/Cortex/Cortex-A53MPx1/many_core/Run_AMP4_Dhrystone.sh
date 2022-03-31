#!/bin/bash
# Run_AMP4_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.AARCH64-O3-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant Cortex-A53MPx1 \
    --numprocessors 4     \
    --parameter endian=little    \
    "$@" \
    -argv 4000000


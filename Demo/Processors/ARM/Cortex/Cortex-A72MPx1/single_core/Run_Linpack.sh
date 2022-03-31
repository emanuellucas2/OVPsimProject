#!/bin/bash
# Run_Linpack.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/linpack/linpack.AARCH64-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant Cortex-A72MPx1 \
    --numprocessors 1     \
    --parameter endian=little    \
    "$@" \
    -argv 180


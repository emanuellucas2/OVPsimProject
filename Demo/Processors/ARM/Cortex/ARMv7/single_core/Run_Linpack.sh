#!/bin/bash
# Run_Linpack.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/linpack/linpack.ARM_CORTEX_A-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant ARMv7 \
    --numprocessors 1     \
    --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little  \
    "$@" \
    -argv 8


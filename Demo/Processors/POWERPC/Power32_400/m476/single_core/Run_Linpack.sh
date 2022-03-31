#!/bin/bash
# Run_Linpack.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/linpack/linpack.POWERPC32-O0-g.elf \
    --processorvendor power.ovpworld.org --processorname powerpc32_400 --variant m476 \
    --numprocessors 1     \
    --parameter endian=big    \
    "$@" \
    -argv 8


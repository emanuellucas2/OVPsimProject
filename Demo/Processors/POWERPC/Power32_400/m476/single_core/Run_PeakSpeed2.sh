#!/bin/bash
# Run_PeakSpeed2.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/peakSpeed2/peakSpeed2.POWERPC32-O0-g.elf \
    --processorvendor power.ovpworld.org --processorname powerpc32_400 --variant m476 \
    --numprocessors 1     \
    --parameter endian=big    \
    "$@" \
    -argv 500000000


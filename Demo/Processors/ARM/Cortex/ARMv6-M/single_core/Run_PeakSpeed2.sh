#!/bin/bash
# Run_PeakSpeed2.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/peakSpeed2/peakSpeed2.ARM_CORTEX_M0-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname armm --variant ARMv6-M \
    --numprocessors 1     \
    --parameter UAL=1 --parameter endian=little   \
    "$@" \
    -argv 500000000


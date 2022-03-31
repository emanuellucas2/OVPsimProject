#!/bin/bash
# Run_PeakSpeed2.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/peakSpeed2/peakSpeed2.ARM_CORTEX_R4F-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant Cortex-R4F \
    --numprocessors 1     \
    --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little --override iss/cpu*/enableVFPAtReset=T  \
    "$@" \
    -argv 500000000


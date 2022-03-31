#!/bin/bash
# Run_PeakSpeed2.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/peakSpeed2/peakSpeed2.CS_NIOS2-O0-g.elf \
    --processorvendor altera.ovpworld.org --processorname nios_ii --variant Nios_II_S \
    --numprocessors 1     \
    --parameter HW_DIVIDE=1 --parameter HW_MULTIPLY=1   \
    "$@" \
    -argv 500000000


#!/bin/bash
# Run_PeakSpeed2.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/peakSpeed2/peakSpeed2.RH850-O0-g.elf \
    --processorvendor renesas.ovpworld.org --processorname rh850 --variant RH850G3M \
    --numprocessors 1     \
    "$@" \
    -argv 300000000


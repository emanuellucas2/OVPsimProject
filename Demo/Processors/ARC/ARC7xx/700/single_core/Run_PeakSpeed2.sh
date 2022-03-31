#!/bin/bash
# Run_PeakSpeed2.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/peakSpeed2/peakSpeed2.ARC700-O0-g.elf \
    --processorvendor arc.ovpworld.org --processorname arc --variant 700 \
    --numprocessors 1     \
    "$@" \
    -argv 500000000


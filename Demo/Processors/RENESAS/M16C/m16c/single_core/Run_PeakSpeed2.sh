#!/bin/bash
# Run_PeakSpeed2.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/peakSpeed1_m16c/peakSpeed1_m16c.M16C-O0-g.elf \
    --processorvendor posedgesoft.ovpworld.org --processorname m16c --variant m16c \
    --numprocessors 1     \
    "$@" \
    -argv 10000000


#!/bin/bash
# Run_PeakSpeed2.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/peakSpeed2_microblaze/peakSpeed2_microblaze.MICROBLAZE-O0-g.elf \
    --processorvendor xilinx.ovpworld.org --processorname microblaze --variant V7_00 \
    --numprocessors 1     \
    --parameter endian=big    \
    "$@" \
    -argv 300000000


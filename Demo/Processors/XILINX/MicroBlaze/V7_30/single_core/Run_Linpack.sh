#!/bin/bash
# Run_Linpack.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/linpack_microblaze/linpack_microblaze.MICROBLAZE-O0-g.elf \
    --processorvendor xilinx.ovpworld.org --processorname microblaze --variant V7_30 \
    --numprocessors 1     \
    --parameter endian=big    \
    "$@" \
    -argv 8


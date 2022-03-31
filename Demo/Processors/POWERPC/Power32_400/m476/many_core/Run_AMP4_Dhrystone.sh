#!/bin/bash
# Run_AMP4_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.POWERPC32-O0-g.elf \
    --processorvendor power.ovpworld.org --processorname powerpc32_400 --variant m476 \
    --numprocessors 4     \
    --parameter endian=big    \
    "$@" \
    -argv 1000000


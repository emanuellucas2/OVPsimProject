#!/bin/bash
# Run_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.ARM7TDMI-O3-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant ARM7EJ-S \
    --numprocessors 1     \
    --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little  \
    "$@" \
    -argv 3000000


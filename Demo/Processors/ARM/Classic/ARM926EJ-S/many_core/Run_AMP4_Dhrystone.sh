#!/bin/bash
# Run_AMP4_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.ARM9E-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant ARM926EJ-S \
    --numprocessors 4     \
    --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little  \
    "$@" \
    -argv 1000000


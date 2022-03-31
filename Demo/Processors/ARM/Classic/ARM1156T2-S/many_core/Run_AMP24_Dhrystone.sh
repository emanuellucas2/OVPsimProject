#!/bin/bash
# Run_AMP24_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.ARM11-O0-g.elf \
    --processorvendor arm.ovpworld.org --processorname arm --variant ARM1156T2-S \
    --numprocessors 24     \
    --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little  \
    "$@" \
    -argv 500000


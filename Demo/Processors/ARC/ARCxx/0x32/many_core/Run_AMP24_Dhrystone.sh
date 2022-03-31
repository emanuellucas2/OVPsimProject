#!/bin/bash
# Run_AMP24_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.ARC600-O2-g.elf \
    --processorvendor arc.ovpworld.org --processorname arc --variant 0x32 \
    --numprocessors 24     \
    "$@" \
    -argv 800000


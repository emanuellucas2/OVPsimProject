#!/bin/bash
# Run_AMP24_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.ARC600-O0-g.elf \
    --processorvendor arc.ovpworld.org --processorname arc --variant 600 \
    --numprocessors 24     \
    --parameter opt-rf16=0    \
    "$@" \
    -argv 500000


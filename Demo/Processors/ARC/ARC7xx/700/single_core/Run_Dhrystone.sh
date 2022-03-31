#!/bin/bash
# Run_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.ARC700-O2-g.elf \
    --processorvendor arc.ovpworld.org --processorname arc --variant 700 \
    --numprocessors 1     \
    "$@" \
    -argv 10000000


#!/bin/bash
# Run_Linpack.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/linpack/linpack.ARC600-O1-g.elf \
    --processorvendor arc.ovpworld.org --processorname arc --variant 0x32 \
    --numprocessors 1     \
    "$@" \
    -argv 6


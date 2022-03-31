#!/bin/bash
# Run_Linpack.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/linpack/linpack.V850-O2-g.elf \
    --processorvendor renesas.ovpworld.org --processorname v850 --variant V850E2 \
    --numprocessors 1     \
    "$@" \
    -argv 10


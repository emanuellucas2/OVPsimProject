#!/bin/bash
# Run_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.V850-O2-g.elf \
    --processorvendor renesas.ovpworld.org --processorname v850 --variant V850E2M \
    --numprocessors 1     \
    "$@" \
    -argv 2000000


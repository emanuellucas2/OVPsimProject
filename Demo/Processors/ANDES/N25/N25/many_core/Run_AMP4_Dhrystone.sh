#!/bin/bash
# Run_AMP4_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.RISCV32-O0-g.elf \
    --processorvendor andes.ovpworld.org --processorname riscv --variant N25 \
    --numprocessors 4     \
    --override iss/cpu0/verbose=1    \
    "$@" \
    -argv 3000000


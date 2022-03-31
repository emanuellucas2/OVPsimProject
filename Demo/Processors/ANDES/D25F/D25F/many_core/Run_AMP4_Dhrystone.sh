#!/bin/bash
# Run_AMP4_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.RISCV64-O0-g.elf \
    --processorvendor andes.ovpworld.org --processorname riscv --variant D25F \
    --numprocessors 4 --addressbits 37    \
    --override iss/cpu0/verbose=1    \
    "$@" \
    -argv 4000000


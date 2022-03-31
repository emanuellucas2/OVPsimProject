#!/bin/bash
# Run_AMP24_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.RISCV32-O0-g.elf \
    --processorvendor riscv.ovpworld.org --processorname riscv --variant RV32GCP \
    --numprocessors 24     \
    --override iss/cpu0/verbose=1    \
    "$@" \
    -argv 500000


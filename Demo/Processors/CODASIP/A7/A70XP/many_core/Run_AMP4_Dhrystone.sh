#!/bin/bash
# Run_AMP4_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.RISCV64-O0-g.elf \
    --processorvendor codasip.ovpworld.org --processorname riscv --variant A70XP \
    --numprocessors 4     \
    --override iss/cpu0/verbose=1    \
    "$@" \
    -argv 3000000

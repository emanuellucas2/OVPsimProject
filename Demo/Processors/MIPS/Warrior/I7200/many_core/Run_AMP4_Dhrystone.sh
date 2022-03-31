#!/bin/bash
# Run_AMP4_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.NANOMIPS32R6LE-O1-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant I7200 \
    --numprocessors 4     \
    "$@" \
    -argv 4000000


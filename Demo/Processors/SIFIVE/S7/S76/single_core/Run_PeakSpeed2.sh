#!/bin/bash
# Run_PeakSpeed2.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/peakSpeed2/peakSpeed2.RISCV64-O0-g.elf \
    --processorvendor sifive.ovpworld.org --processorname riscv --variant S76 \
    --numprocessors 1 --addressbits 37    \
    --override iss/cpu0/verbose=1    \
    "$@" \
    -argv 500000000


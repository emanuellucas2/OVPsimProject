#!/bin/bash
# Debug_eGui_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.RISCV32-O0-g.elf \
    --processorvendor lowrisc.ovpworld.org --processorname riscv --variant Ibex_RV32IC \
    --numprocessors 1     \
    --override iss/cpu0/verbose=1    \
    --gdbegui  --eguicommands "--breakonstartup main --continueonstartup" \
    "$@"



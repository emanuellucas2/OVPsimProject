#!/bin/bash
# Debug_GDB_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.IMG_UMIPS32R2LE-O1-g.elf \
    --processorvendor mips.ovpworld.org --processorname mips32 --variant M5100 \
    --numprocessors 1     \
    --parameter endian=little --semihostname mips32Newlib --semihostvendor mips.ovpworld.org  \
    --gdbconsole --gdbinit dhrystone.gdb \
    "$@"



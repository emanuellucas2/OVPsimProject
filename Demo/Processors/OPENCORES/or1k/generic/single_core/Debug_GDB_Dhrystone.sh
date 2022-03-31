#!/bin/bash
# Debug_GDB_Dhrystone.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/dhrystone/dhrystone.OR1K-O1-g.elf \
    --processorvendor ovpworld.org --processorname or1k --variant generic \
    --numprocessors 1     \
    --gdbconsole --gdbinit dhrystone.gdb \
    "$@"



#!/bin/bash
# Run_Linpack.sh

# Check Environment
if [ -z ${IMPERAS_HOME} ]; then
  echo "IMPERAS_HOME not set. Please check environment setup."
  exit
fi

${IMPERAS_ISS} --verbose --output imperas.log \
    --program ../../../Applications/linpack/linpack.OR1K-O0-g.elf \
    --processorvendor ovpworld.org --processorname or1k --variant generic \
    --numprocessors 1     \
    "$@" \
    -argv 8


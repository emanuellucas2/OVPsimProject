#!/bin/sh

#
# Setup file for Bourne Shell
#
#

# File must be sourced
if [ "$(basename $0 .sh)" == "switchRuntime" ]; then
  echo "This file should be sourced in a Bourne Shell"
  exit 1
fi

#
# Select from Runtime Libraries
#
function switchRuntimeImperas () {
  libs=$(find ${IMPERAS_HOME}/bin/${IMPERAS_ARCH} -name "libOVPsim*.${IMPERAS_SHRSUF}" -or -name "libCpuManager*.${IMPERAS_SHRSUF}" | sed -e "s#.*lib\(.*\).${IMPERAS_SHRSUF}#\1#" | sort -d)
  PS3='Please Choose Runtime: '
  select runtime in $libs
  do
      break
  done
  echo "Selected Runtime '$runtime' updating environment ..."
  export IMPERAS_RUNTIME=$runtime
}

echo "Function switchRuntimeImperas added"


#!/bin/sh

#
# Setup file for Bourne Shell
#
#

# File must be sourced
if [ "$(basename $0 .sh)" == "switchISS" ]; then
  echo "This file should be sourced in a Bourne Shell"
  exit 1
fi

#
# Select from Runtime Libraries
#
function switchISSImperas () {
  issexe=$(find ${IMPERAS_HOME}/bin/${IMPERAS_ARCH} -name "iss*.exe" | sed -e "s#\(.*\).exe#\1#" | sort -d)
  PS3='Please Choose ISS: '
  select iss in $issexe
  do
      break
  done
  echo "Selected ISS '$iss' updating environment ..."
  export IMPERAS_ISS=${iss}.exe
}

echo "Function switchISSImperas added"


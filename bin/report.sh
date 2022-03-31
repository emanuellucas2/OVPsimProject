#!/bin/bash

#
# Report Info for Bourne Shell
#

function banner () {
    msg=$1
    echo ""
    echo "#"
    echo "# ${msg}"
    echo "#"
}

#
# Firstly Get all the IMPERAS_* Environment variables
#
(
    banner "Environment"
    uname -a

    banner "Test IMPERAS_HOME"
    if [ -n "${IMPERAS_HOME}" ]; then
        echo "IMPERAS_HOME = ${IMPERAS_HOME}"
    else
        echo "IMPERAS_HOME is unset"
    fi
    
    banner "Test IMPERAS* Environment variables"
    env | grep "^IMPERAS"

    banner "Test LM_LICENSE_FILE Environment variable"
    env | grep "^LM_LICENSE_FILE"

    banner "Test IMPERASD_LICENSE_FILE Environment variable"
    env | grep "^IMPERASD_LICENSE_FILE"
    
    banner "Test PATH Environment variable"
    env | grep "^PATH"
    
    banner "Test LD_LIBRARY_PATH Environment variable"
    env | grep "^LD_LIBRARY_PATH"
    
    banner "Test ${IMPERAS_HOME}/InstallLog.txt"
    if [ -f ${IMPERAS_HOME}/InstallLog.txt ]; then
        cat ${IMPERAS_HOME}/InstallLog.txt
    else
        echo "${IMPERAS_HOME}/InstallLog.txt does not exist"
    fi
    
    # Get the version of make, gcc
    banner "Test make"
    make --version
    
    # test if we are on Windows in a MinGW/MSys shell
    if [ -d /c/Program\ Files ]; then
        banner "Test mingw32-make"
        mingw32-make --version
    fi

    banner "Test gcc"
    gcc --version

) | tee ImperasReport.log

#!/bin/sh
#
# Setup file for Bourne Shell
#

# File must be sourced
if [ "$(basename -- $0 .sh)" == "setup" ]; then
    echo "This file should be sourced in a Bourne Shell"
    exit 1
fi

#
# Valid Runtime Libraries
# OVPsim CpuManager
#
function setupImperas {
    #
    # Command Line Parse
    #
    local IMPERAS_HOME_IN=''
    local M32=0
    local MSYS=0
    while [ $# -gt 0 ]
    do
        case "$1" in
            -m32)
                M32=1;
                echo "Info: Emulate 32Bit setup"
                shift;;
              
            -help)
                echo "Usage: setupImperas [-help] [-m32] <Installation Directory>"
                echo "           -help, Print this help"
                echo "           -m32,  Run 32bit product under a 64bit OS"
                return 1
                shift;;
            
            *)
                IMPERAS_HOME_IN=$1;
                shift;;
        esac
    done

    if [ -n "$IMPERAS_HOME_IN" ] && [ -d ${IMPERAS_HOME_IN} ]; then
        export IMPERAS_HOME=${IMPERAS_HOME_IN}
        
        #
        # test if we are on Windows in a MinGW/MSys shell
        #
        if [ -n "${MSYSTEM}" ]; then
            echo "Windows env IMPERAS_HOME=${IMPERAS_HOME}"
            export IMPERAS_UNAME=Windows
            export IMPERAS_SHRSUF=dll
            MSYS=1
            if [ ! -d "/c/Program Files (x86)" ] || [ ${M32} = 1 ]; then
                export IMPERAS_M32=1
                ARCHSIZE=32
            else
                export IMPERAS_M32=0
                ARCHSIZE=64
            fi
            
            #
            # Adjust path drive letter
            #
            if [ "${IMPERAS_HOME:0:1}" != "/" ]; then
                echo "Error: use msys style path ${IMPERAS_HOME}"
                setupImperas -help
                return 1
            else
                export IMPERAS_HOME=$(cd ${IMPERAS_HOME} && pwd -W)
            fi

        else

            export IMPERAS_UNAME=Linux
            export IMPERAS_SHRSUF=so
            if [ "$(uname -m)" = "i686" ] || [ ${M32} = 1 ]; then
                export IMPERAS_M32=1
                ARCHSIZE=32
            elif [ "$(uname -m)" = "x86_64" ]; then
                export IMPERAS_M32=0
                ARCHSIZE=64
            else
                echo "Error: Unsupported architecture $(uname -m)"
                setupImperas -help
                return 1
            fi
            
        fi
        
        export IMPERAS_ARCH=${IMPERAS_UNAME}${ARCHSIZE}
        if [ -d ${IMPERAS_HOME}/lib/${IMPERAS_ARCH}/ImperasLib ]; then
            export IMPERAS_VLNV=${IMPERAS_HOME}/lib/${IMPERAS_ARCH}/ImperasLib
        fi
        
        if [ $MSYS -eq 1 ]; then
            export PATH=${PATH}:${IMPERAS_HOME_IN}/bin/${IMPERAS_ARCH}
        else
            export PATH=${PATH}:${IMPERAS_HOME}/bin/${IMPERAS_ARCH}
        fi
        
        if [ "${IMPERAS_UNAME}" = "Linux" ]; then
            export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${IMPERAS_HOME}/bin/${IMPERAS_ARCH}
        fi
        
        if [ ! -d ${IMPERAS_HOME}/bin/${IMPERAS_ARCH} ]; then
            echo "Error: Installation Directory ${IMPERAS_HOME}/bin/${IMPERAS_ARCH} does not exist"
            setupImperas -help
            return 1
        fi

        #
        # If the runtime is not set, attempt to determine what product I am
        #
        if [ -z ${IMPERAS_RUNTIME} ]; then
            if [ -f ${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/libCpuManager.${IMPERAS_SHRSUF} ]; then
                export IMPERAS_RUNTIME=CpuManager
                echo "Info: IMPERAS_RUNTIME is undefined, defaulting to ${IMPERAS_RUNTIME}"
            else
                echo "Info: IMPERAS_RUNTIME is undefined, default is OVPsim, please use switchRuntime.sh to define"
            fi
        fi

        #
        # If the runtime is CpuManager and personality not set, set to M*DEV/M*SDK default
        #
        if [ "${IMPERAS_RUNTIME}" = "CpuManager" ]; then
            if [ -z "${IMPERAS_PERSONALITY}" ]; then
                export IMPERAS_PERSONALITY=CPUMAN_MULTI
                echo "Info: IMPERAS_PERSONALITY is undefined, defaulting to ${IMPERAS_PERSONALITY}"
            fi
        fi
        
        #
        # Determine ISS to use
        #
        if [ -z ${IMPERAS_ISS} ]; then
            if [ -f ${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/iss.exe ]; then
                export IMPERAS_ISS=iss.exe
            elif [ -f ${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/issdemo.exe ]; then
                export IMPERAS_ISS=issdemo.exe
            fi
            if [ ! -z ${IMPERAS_ISS} ]; then
                echo "Info: IMPERAS_ISS is undefined, defaulting to ${IMPERAS_ISS}"
            fi
        fi
        
    else
        echo "Error: No such <Installation Directory>=\"${IMPERAS_HOME}\""
        setupImperas -help
        return 1
    fi

    echo "Info: Setup Complete"

}

echo "Function 'setupImperas' successfully added to shell:"
echo -n "   "
setupImperas -help


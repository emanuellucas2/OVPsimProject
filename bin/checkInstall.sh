#!/bin/sh

#
# Run install check program to check environment and show installed components
#

$(dirname $0)/${IMPERAS_ARCH}/checkinstall.exe --install $(dirname $0)/../InstallLog.txt -env -show -build

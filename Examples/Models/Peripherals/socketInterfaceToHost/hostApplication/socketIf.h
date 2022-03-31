/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */

#ifndef SOCKETIF_H
#define SOCKETIF_H

#include "hostapi/impTypes.h"

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>

#if (IMPERAS_WINDOWS==1)
#    include <winsock2.h>
#    include <windows.h>
#    include <winbase.h>
#else
#    include <sys/types.h>
#    include <sys/socket.h>
#    include <errno.h>
#    include <fcntl.h>
#    include <termio.h>
#    include <netdb.h>
#    include <netinet/in.h>
#    include <netinet/tcp.h>
#    include <arpa/inet.h>
#endif

Int32 connectSocket(const char *hostname, Uns32 port);
void errorExit(char *format, ...);

#endif

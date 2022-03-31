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


#include "socketIf.h"
#include "stimulus.h"

void errorExit(char *format, ...)
{
    char buf[1024];
    va_list va;

    va_start(va, format);
    vsprintf(buf,format, va);
    va_end(va);

    fprintf(stderr, "Terminal error. %s\n\n", buf);
    exit(1);
}


static Int32 getErrno(void) {
#if (IMPERAS_WINDOWS==1)
    return GetLastError();
#else
    return errno;
#endif
}

static void initializeSockets(void) {
#if (IMPERAS_WINDOWS==1)
    WSADATA info;
    if ( WSAStartup(MAKEWORD(2,2), &info) != 0 ) {
        errorExit("Error initializing Windows networking\n");
    }
#endif
}

Int32 tosGetSocketError(void) {
#if (IMPERAS_WINDOWS==1)
    return WSAGetLastError();
#else
    return errno;
#endif
}

Int32 staticSocket = -1;

Int32 connectSocket(const char *hostname, Uns32 port) {

    initializeSockets();

    Int32 id = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (id == -1) {
        errorExit("Failed to create a socket (%d)\n", getErrno());
    }

    if (!hostname) {
        hostname = "localhost";
    }
    struct hostent *server = gethostbyname(hostname);
    if(!server) {
        errorExit("Cannot find host called '%s'",hostname );
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port   = htons(port);
    memcpy(&serverAddr.sin_addr.s_addr, server->h_addr, server->h_length);

    if (connect(id, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {

        errorExit(
            "Failed to connect to %s:%d (errno:%d)\n",
            hostname,
            port,
            getErrno()
        );
    }

    Int32 flag = 1;
    if ( setsockopt(id, IPPROTO_TCP, TCP_NODELAY, (char*) &flag, sizeof(flag)) != 0) {
        errorExit(
            "Failed to set TCP options on socket (%d)\n",
            getErrno()
        );
    }
    return id;
}

#include "stimulus.h"

#include "exchangeData.h"

static void socketSend(Int32 socket, const char *transferBuffer, Int32 transferSize)
{
    Int32 completeSize = 0;
    Int32 returnSize   = 0;

    Int32 i;
    printf("Message Out (to Simulator) size %d:\n", transferSize);
    for (i=0; i<transferSize;i++) {
        printf("0x%02x ", transferBuffer[i]);
    }
    printf("\n");

    if (NULL == transferBuffer)
    {
        return;
    }
    if (0 > transferSize)
    {
        return;
    }

    while (completeSize < transferSize)
    {
        returnSize = send(socket, &transferBuffer[completeSize], transferSize - completeSize, 0);
        if (0 < returnSize)
        {
            completeSize += returnSize;
        }
    }
}

static void socketRecv(Int32 socket, char *transferBuffer, Int32 transferSize)
{
    Int32 completeSize = 0;
    Int32 returnSize   = 0;

    if (NULL == transferBuffer)
    {
        return;
    }
    if (0 > transferSize)
    {
        return;
    }

    while (completeSize < transferSize)
    {
        returnSize = recv(socket, &transferBuffer[completeSize], transferSize - completeSize, 0);
        if (0 < returnSize)
        {
            completeSize += returnSize;
        }
    }
    Int32 i;
    printf("Message In (from Simulator) size %d:\n", transferSize);
    for (i=0; i<transferSize;i++) {
        printf("0x%02x ", transferBuffer[i]);
    }
    printf("\n");
}


Int32 synch(Int32 sock) {

    char  *transferBuffer;
    Int32  transferSize;

    transferBuffer = NULL;
    transferSize   = INT_MAX;

    if (sock < 0) {
        printf("Socket Gone...\n");
        return 1;
    }

    printf("\n------------------------\nxchngDataIn\n------------------------\n");
    transferBuffer = (char *)&xchngDataIn;
    transferSize = (Int32)sizeof(tExchangeDataStruct);
    socketRecv(sock, transferBuffer, transferSize);

    printf("Info uS %d, end sim %d, Rx %d, Size %d\n"
                , xchngDataIn.time
                , xchngDataIn.endSimulation
                , xchngDataIn.num
                , xchngDataIn.fd.length);

    if (0 != xchngDataIn.endSimulation) {
        printf("Ending Simulation\n");
        return 1;
    }

    // setup time for next message Out
    xchngDataOut.time = xchngDataIn.time + (1024000 / STEP);

    printf("Info : RX Length %d, Num %d\n", xchngDataIn.fd.length, xchngDataIn.num);

    unsigned int index;
    for (index = 0; xchngDataIn.fd.length > index; ++index)
    {
        printf("RX Data[%d] 0x%08x\n", index, xchngDataIn.fd.data[index]);
    }

    printf("\n------------------------\nxchngDataOut\n------------------------\n");
    printf("Info next uS %d, end sim %d, Tx %d, Size %d\n"
                , xchngDataOut.time
                , xchngDataOut.endSimulation
                , xchngDataOut.num
                , xchngDataOut.fd.length);

    transferBuffer = (char *)&xchngDataOut;
    transferSize = (Int32)sizeof(tExchangeDataStruct);
    socketSend(sock, transferBuffer, transferSize);

    xchngDataOut.num++;

    return 0;
}

void transferLoop(Int32 sock, char * file) {

    memset(&xchngDataOut, 0, sizeof(xchngDataOut));
    memset(&xchngDataIn, 0, sizeof(xchngDataIn));

    if (initStim(file)) {
        exit(1);
    }


    while(1) {

    	setNextStimLine();

        if (synch(sock)) {
            // end simulation
            break;
        }
    }

    closeStim();
}

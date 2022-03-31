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

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "stimulus.h"

#define PREFIX "IF_STIM"

char buffer[BUFFSIZE];

inT in;

//
// Read a line from the file and write into the channel structure
// at EOF in the file, reset to 0
//
// File Format
//        TIME, 0 [us]
//        DATA, <length>, data bytes...

typedef enum {
    NONE,
    TIME_MSG,
    DATA_MSG,
    LAST_MSG
} msgTypeE;

#define TIMESTATE(_st)  (_st == NOW ? "NOW" : _st == NEXT ? "NEXT" : "NEVER")

int setNextStimLine() {

    if (in.fp != NULL) {

    	int txDataIndex = 0;
    	int rxDataIndex = 0;

        msgTypeE msgType = NONE;
        static enum {NEVER, NOW, NEXT } timeFound = NEVER;   // 0 not found, 1 found now, 2 found next
        unsigned int msgTime;

        // We read the next timestamp previously

        printf("\n----------------\nInfo "PREFIX"_GET (%d) %s\n----------------\n", in.now, TIMESTATE(timeFound));

        char *rc;
        Bool foundLine = False;
        do {
            if(timeFound == NEXT)
                in.now = in.next;
            do {
                rc = fgets(buffer, BUFFSIZE, in.fp);
                if (rc==NULL) {
                    if(!xchngDataOut.endSimulation) {
                        printf("Warning "PREFIX"_PARSE : Stimulus Reader End of File\n");
                        xchngDataOut.endSimulation = 1;
                    }
                    return 2;
                }
                msgType = NONE;

                if (!strncmp(buffer, "TIME", 4)) {
                    msgType = TIME_MSG;
                } else if  (!strncmp(buffer, "DATA", 4)) {
                    msgType = DATA_MSG;
                }

            } while (msgType == NONE);
            printf("Info "PREFIX"_LINE : msgType %d '%s'\n", msgType, buffer);

            switch (msgType) {
                case TIME_MSG:
                {
                    sscanf(buffer, "TIME %d [us]", &msgTime);
                    if(timeFound == NEVER) {
                        in.now = msgTime;
                        timeFound=NOW;
                    } else if(timeFound == NOW) {
                        in.next = msgTime;
                        timeFound=NEXT;
                    }
                    xchngDataOut.time = in.now;
                    printf("Info "PREFIX"_TIM_MSG : now %d next %d (%s)\n", in.now, in.next, TIMESTATE(timeFound));
                    break;
                }
                case DATA_MSG:
                {
                    char lengthS[256];
                    sscanf(buffer, "DATA %s", lengthS);
					xchngDataOut.fd.length=atoi(lengthS);
                    printf("Info "PREFIX"_DATA_MSG : Sim %d Tx %d\n", xchngDataOut.endSimulation, xchngDataOut.num);
                    unsigned int index;
                    char *bufferP = &buffer[0];
                    bufferP += strlen(lengthS) + 5;
                    for(index = 0; index < xchngDataOut.fd.length; index++){
                        char inputS[16];
                        sscanf(bufferP, "%s ", inputS);
                        xchngDataOut.fd.data[index]=atoi(inputS);
                        bufferP += strlen(inputS) + 1;
                        printf("Info "PREFIX"_DATA_MSG : data %02d: %d\n", index, xchngDataOut.fd.data[index]);
                    }
                    xchngDataOut.num++;
                    break;
                }
                default:
                    printf("Error "PREFIX"_ERRMSGTYPE : Not recognised message type (%d)\n", msgType);
                    return -1;
                    break;
            }

        } while (timeFound != NEXT);
        timeFound=NOW;
    }
    return 0;
}


int initStim(const char *file) {
    in.fp = fopen(file, "r");
    if (in.fp == NULL) {
        printf("Failure: Cannot open stimfile=%s", file);
        return 1;
    } else {
        printf("Opened stimfile=%s", file);
    }
    return 0;
}

int closeStim() {
    fclose(in.fp);
    return 0;
}


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

void delay (unsigned int delay) {
    unsigned int i, j;
    for(i=0;i<delay;i++) {
        for(j=0;j<1000000;j++) {
            ;   // wait
        }
    }

}


int main () {
    unsigned int c;
    char stringToSend[] = {"Hello"};

    // Print to semihosted stdout
    printf("%s\n", stringToSend);

    delay(100);

    // print to UART
    for (c=0;c<sizeof(stringToSend);c++) {

        // Print to semihosted stdout
        printf("Write '%c'\n", stringToSend[c]);

        // write character to data register
        *(unsigned char *) 0x90000000 = stringToSend[c];

        // write character to memory
        *(unsigned char *) 0x02000000 = stringToSend[c];

        delay(10);
    }

    delay(100);

    return 0;
}

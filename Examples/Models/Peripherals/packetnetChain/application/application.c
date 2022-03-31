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
#include <stdlib.h>

#define BASE                   0x40000000
#define PORTSIZE               0x1000
#define NODE(_N)               (BASE+((_N)*PORTSIZE))

#define CONTROLOFFSET          0
#define STATUSOFFSET           4
#define CONTROLREG(_I)         (*(unsigned int *)(NODE(_I)+CONTROLOFFSET))
#define STATUSREG(_I)          (*(unsigned int *)(NODE(_I)+STATUSOFFSET))

#define CONTROL_START          (1<<0)
#define CONTROL_LENGTH(_L)     (_L<<16)
#define GETCONTROL_LENGTH(_R)  ((_R>>16) & 0xffff)

#define STATUS_WAITINGTOSEND   (1<<1)
#define GETDATAINREADY(_R)     ((_R>>0) & 1)
#define GETWAITINGTOSEND(_R)   ((_R>>1) & 1)
#define GETOVERFLOW(_R)        ((_R>>2) & 1)

#define TXBUFFEROFFSET   0x100
#define RXBUFFEROFFSET   0x200

#define PACKET_SIZE      80

void delay(unsigned int delay) {
    unsigned int i, j;
    for (i=delay;i;i--) {
        for (j=5000;j;j--) {
            ; // delay
        }
    }
}

int main () {
	int loop;
	int node;
	int status[4];

	printf("CPU: Starting...\n");

	for (loop = 1; loop <= 3; loop++) {

		// Write data to Node 0 Tx Buffer
		unsigned int i;
		for (i=0;i<PACKET_SIZE;i++) {
			*(unsigned char *)(NODE(0)+TXBUFFEROFFSET+i) = i * loop;
		}
		printf("\nNode 0 Message in Tx buffer");
		for (i=0;i<PACKET_SIZE;i++) {
			if((i%10)==0) printf("\n loop %d  %2d: ", loop, i);
			printf(" %3d", *(unsigned char *)(NODE(0)+TXBUFFEROFFSET+i));
		}
		printf("\n");

		// Tell first node to start processing data in TX buffer
		CONTROLREG(0) = CONTROL_LENGTH(PACKET_SIZE) | CONTROL_START;

		// Report status periodically and poll for waiting to send on any node
		int nodeWaiting = 0;
		do {

			delay(100);

			for (node = 0; node < 4; node++) {
				status[node] = STATUSREG(node);
			}
			printf("Status loop %d:\n", loop);
			printf("Node            0 1 2 3\n");
			printf("Data in ready  ");
			for (node = 0; node < 4; node++) {
				printf (" %c", GETDATAINREADY(status[node]) ? 'r' : '-');
			}
			printf("\nWaiting to send");
			for (node = 0; node < 4; node++) {
				int waiting = GETWAITINGTOSEND(status[node]);
				printf (" %c", waiting ? 'w' : '-');
				// Ignore node3 waiting flag on loop 3
				if (node != 3 || loop != 3) {
					nodeWaiting |= waiting;
				}
			}
			printf("\nOverflow       ");
			for (node = 0; node < 4; node++) {
				printf (" %c", GETOVERFLOW(status[node]) ? 'o' : '-');
			}
			printf("\n\n");

		} while (!nodeWaiting);

		for (node = 0; node < 4; node++) {
			if (GETWAITINGTOSEND(status[node])) {
				printf("\nNode %d Message ready", node);
				unsigned int length = GETCONTROL_LENGTH(CONTROLREG(node));
				for (i=0;i<length;i++) {
					if((i%10)==0) printf("\n loop %d  %2d: ", loop, i);
					printf(" %3d", *(unsigned char *)(NODE(node)+RXBUFFEROFFSET+i));
				}
				printf("\n");
			}
			// On loop 1 only, clear the waiting state on waiting nodes.
			// This will cause a stall in loop 3 because loop 2 data
			// not been read from node 3
			if (loop == 1) {
				STATUSREG(node) = STATUS_WAITINGTOSEND;
			}
		}
	}

    printf("CPU: finished\n");

}

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
#include <string.h>
#include <sys/time.h>

#include "radar.h"

#define MAXLINE 1024

void delay (unsigned int delay) {
    struct timeval tv;
    struct timezone tz;
    unsigned int i,j;
    for (i=0;i<delay;i++) {
        for (j=0;j<5000;j++) {
            gettimeofday(&tv, &tz);
        }
    }
}

int x[] = {0, 1, 2, 3};
int y[] = {0, 1, 2, 3};
int z[] = {0, 1, 2, 3};

void initPlane (aircraftP p, int icao, int x, int y, int z, int kns, int trk, int climb) {
    p->icao =    icao;
    p->xy =      1;
    p->x =       x;
    p->y =       y;
    p->z =       z;
    p->kns =     kns;
    p->trk =     trk;
    p->climb =   climb;
}

char line[MAXLINE];
int main(int argc, char **argv) {
    sharedDataP data = (sharedDataP) RADAR_DATA;
    char *ptr;

    FILE *traffic = fopen("data/data.traffic", "r");

    data->numAircraft = 0;
    //
    // OWNSHIP TIMESTAMP=1 TRACK=0 KNS=0
    // AIRCRAFT ICAO=406CB1!406CB1 X=-414 Y=2616 Z=526 KNS=20 TRACK=170 CLIMB=0
    //
    while (1) {
        while (fgets(line, MAXLINE, traffic) && data->reset==0) {

            if (strncmp(line, "OWNSHIP", strlen("OWNSHIP"))==0) {
                sscanf(line, "OWNSHIP TIMESTAMP=%d TRACK=%d KNS=%d",
                    &data->timestamp, &data->track, &data->kns);

                delay(500);
                printf ("Application: time(%d) track(%d) knots(%d) numAirCraft(%d)\n",
                        data->timestamp, data->track, data->kns, data->numAircraft);
                data->numAircraft = 0;
            } else {
                int id = data->numAircraft;
                char reg[32];
                sscanf(line, "AIRCRAFT ICAO=%06X!%s X=%d Y=%d Z=%d KNS=%d TRACK=%d CLIMB=%d",
                    &data->p[id].icao, reg,
                    &data->p[id].x,   &data->p[id].y,   &data->p[id].z,
                    &data->p[id].kns, &data->p[id].trk, &data->p[id].climb);
                data->p[id].xy = 1;

                data->numAircraft++;
            }
        }
        if (data->reset == 1) {
            data->reset = 0;
        } else {
            printf("Application: <EOF> rewind\n");
        }
        rewind(traffic);
    }

    fclose(traffic);




//    int i,j;
//    pp->numPlanes = 4; // <= MAX_PLANES
//    pp->reset = 1;
//
//
//    for (i=0; i< 100;i++) {
//
//        if (pp->reset != 0) {
//            pp->reset = 0;
//            initPlane (&pp->p[0],  0x40000, x[0], y[0], z[0], 200, 30, 10);
//            initPlane (&pp->p[1],  0x20000, 1000, 1000, 0, 200, 340, 5);
//            initPlane (&pp->p[2],  0x60000, 1000, 1000, 0, 100, 140, 5);
//            initPlane (&pp->p[3],  0x80000, 1000, 1000, 0, 400, 240, 5);
//            printf("Appplication: Resetting planes\n");
//        }
//
//        pp->p[0].x += 1500;
//        pp->p[0].y += 2000;
//        pp->p[0].z += 30;
//
//        pp->p[1].x -= (3000+pp->p[1].trk);
//        pp->p[1].y += (4000-pp->p[1].trk);
//        pp->p[1].z += 2;
//        pp->p[1].trk = 340; // (pp->p[1].trk +15)% 360;
//
//        pp->p[2].x += 700;
//        pp->p[2].y += 7000;
//        pp->p[2].z += 30;
//
//        pp->p[3].x += 400;
//        pp->p[3].y += 4000;
//        pp->p[3].z += 50;
//
//        int j;
//        printf("Appplication:  planes (%d) : ", pp->numPlanes);
//        for (j=0; j<pp->numPlanes; j++) {
//            printf("[%d]{%d %d %d} ", j, pp->p[j].x, pp->p[j].y, pp->p[j].z);
//        }
//        printf("\n");
//
//        delay(500);
//    }
    return 0;
}




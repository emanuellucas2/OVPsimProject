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

#define MAX_AIRCRAFT 128
#define RADAR_DATA 0x10000000

typedef struct aircraftS {
    int icao;       // 24 bits
    int xy;         // 1;
    int x;          // metres 0-70000
    int y;          // metres 0-70000
    int z;          // metres - 0-15000
    int kns;        // speed knots
    int trk;        // degress 0-359
    int climb;      // climb signed in metres;
} aircraftT, *aircraftP;

typedef struct sharedDataS {
    int       reset;
    int       timestamp;
    int       track;
    int       kns;
    int       numAircraft;
    aircraftT p[MAX_AIRCRAFT];
} sharedDataT, *sharedDataP;


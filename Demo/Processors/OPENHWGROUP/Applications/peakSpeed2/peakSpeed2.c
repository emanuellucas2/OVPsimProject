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

#define NOINLINE __attribute__((noinline))

#ifndef ITERATIONS
#define ITERATIONS 400000000
#endif

int main(int argc, char *argv[])
{
    int a=0, b=0, c=0, d=0, e=0, f=0, g=0, h=0,
        i=0, j=0, k=0, l=0, m=0, n=0, o=0, p=0;
    int count, result;
    int num = (argc >= 2) ? atoi(argv[1]) : ITERATIONS;

    for(count=0; count<num; count++) {

        a = i+1;
        b = j+2;
        c = k+3;
        d = l+4;
        e = m+5;
        f = n+6;
        g = o+7;
        h = p+8;

        i = a-1;
        j = e-2;
        k = b-3;
        l = f-4;
        m = c-5;
        n = g-6;
        o = d-7;
        p = h-9;
    }

    result = a+b+c+d+e+f+g+h+i+j+k+l+m+n+o+p;

    printf("result=%d\n", result);

#ifdef MICROBLAZE
    void exit(int);
    exit(0);
#endif
    return result;
}

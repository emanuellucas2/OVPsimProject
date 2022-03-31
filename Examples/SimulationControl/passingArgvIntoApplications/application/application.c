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

int main(int argc, char **argv) {
    char *str = (argc >= 2) ? "(Got an Arg)" : "(no args)" ;
    int num = (argc >= 2) ? atoi(argv[1]) : 10; // assume one numerical argument 
                                          // and a default of 10 if not set.
    printf("Passing argument into application. %s num(%d)\n", str, num);
    return 0;
}

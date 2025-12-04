//
// Created by rasmk on 20-11-2025.
//

#ifndef TRUCKINGNAVIGATION_GETDESTINATIONFUNC_H
#define TRUCKINGNAVIGATION_GETDESTINATIONFUNC_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//# define MAPSIZE 30

typedef struct {
    int startX;
    int startY;
    int endX;
    int endY;
}Destination;

void GetDestination (Destination *destination, int acceptInput, int mapSize);

void TestConGetDestinationFunc();
#endif //TRUCKINGNAVIGATION_GETDESTINATIONFUNC_H
//
// Created by rasmk on 20-11-2025.
//

#ifndef TRUCKINGNAVIGATION_GETDESTINATIONFUNC_H
#define TRUCKINGNAVIGATION_GETDESTINATIONFUNC_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "DefineStruct.h"

void GetDestinationManual(Destination *destination, int mapSize);

void GetDestinationRandom(Destination *destination, int mapSize);

void RunDestination(Destination *destination, int mapSize);

void TestConGetDestinationFunc();
#endif //TRUCKINGNAVIGATION_GETDESTINATIONFUNC_H
//
// Created by rasmk on 11-12-2025.
//

#ifndef TRUCKINGNAVIGATION_NAVIGATION_H
#define TRUCKINGNAVIGATION_NAVIGATION_H
#include "DefineStruct.h"
#include <stdlib.h>

int *Navigate(int *map, const int mapSize, const Destination destination,
    int *fullPathLength, int *numSections, int *stops);
#endif //TRUCKINGNAVIGATION_NAVIGATION_H
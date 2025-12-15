#ifndef TRUCKINGNAVIGATION_NAVIGATION_H
#define TRUCKINGNAVIGATION_NAVIGATION_H
#include "DefineStruct.h"

int *Navigate(int *map, int mapSize, Destination destination,
    int *fullPathLength, int *numSections, int *stops);
int* OriginalPath(int *map, int mapSize, Destination destination,
    int *outPathLength);
void NavigateWrapper(int *map, int mapSize, int *path, int pathLength, int *stops, int numOfStops);
#endif //TRUCKINGNAVIGATION_NAVIGATION_H
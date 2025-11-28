//
// Created by rasmk on 20-11-2025.
//

#ifndef TRUCKINGNAVIGATION_INTERSTATE_H
#define TRUCKINGNAVIGATION_INTERSTATE_H
#define ERROR_PATH 10
#include "DefineStruct.h"
#include "DefineConst.h"


int *DefineHighwayPath(int *map, unsigned int mapSize, InterStateRoad interStateRoad, int *outPathLength);
void SetInterStateRoad(int *map, unsigned int mapSize, InterStateRoad interStateRoad);
void GenInterStates(int *map, unsigned int mapSize);
void SetInterstateRestStops(int *map, unsigned int mapSize,
    int frequencyOfStops, int *path, int pathLength,
    int startIndex, int goalIndex, int *outNumStops, Stops *restStops);
#endif //TRUCKINGNAVIGATION_INTERSTATE_H
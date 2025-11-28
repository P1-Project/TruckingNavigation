//
// Created by rasmk on 20-11-2025.
//

#ifndef TRUCKINGNAVIGATION_INTERSTATE_H
#define TRUCKINGNAVIGATION_INTERSTATE_H
#define ERROR_PATH 10
#include "DefineStruct.h"
#include "DefineConst.h"


int *DefineHighwayPath(int *map, signed int mapSize, InterStateRoad interStateRoad, int *outPathLength);
void SetInterStateRoad(int *map, signed int mapSize, InterStateRoad interStateRoad);
void GenInterStates(int *map, signed int mapSize);
#endif //TRUCKINGNAVIGATION_INTERSTATE_H
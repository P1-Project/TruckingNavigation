//
// Created by rasmk on 20-11-2025.
//

#ifndef TRUCKINGNAVIGATION_INTERSTATE_H
#define TRUCKINGNAVIGATION_INTERSTATE_H
#define ERROR_PATH 10
#include "DefineStruct.h"
#include "DefineConst.h"


int *DefineHighwayPath(int *map, int mapSize,
    InterStateRoad interStateRoad, int *outPathLength);
void SetInterStateRoad(int *map, int mapSize,
     InterStateRoad interStateRoad,
    Stops *restStops,
    StopType stopTypesArray[3]);
void GenInterStates(int *map,  int mapSize,
    Stops *restStops,
    StopType stopTypesArray[3]);
void SetInterstateRestStops(int *map, int mapSize,
    int frequencyOfStops, int *path, int pathLength,
    int startIndex, int goalIndex, int *outNumStops,
    Stops *restStops,
    StopType stopTypesArray[3]
    );
#endif //TRUCKINGNAVIGATION_INTERSTATE_H
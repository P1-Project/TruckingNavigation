//
// Created by rasmk on 19-11-2025.
//

#ifndef TRUCKINGNAVIGATION_MAPGEN_H
#define TRUCKINGNAVIGATION_MAPGEN_H
#include "DefineStruct.h"


void TestMapGenConnection(void);
void runMapGen(int *map, int mapSize, Stops *restStops);
void PrintMap(int *map, int mapSize);
void PrintMapWPath(int *map, int mapSize, int *path, int pathLength);
void printPath(int *path, int pathLength);
void InitMap(int *map, int mapSize);

#endif //TRUCKINGNAVIGATION_MAPGEN_H
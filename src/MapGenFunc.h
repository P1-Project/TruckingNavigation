//
// Created by rasmk on 19-11-2025.
//

#ifndef TRUCKINGNAVIGATION_MAPGEN_H
#define TRUCKINGNAVIGATION_MAPGEN_H
#include <stdbool.h>

#include "DefineStruct.h"


void TestMapGenConnection(void);
void RunMapGen(int *map, int mapSize, Stops *restStops);
void PrintMap(int *map, int mapSize, int *path, int pathLength);
void PrintMapExPath(int *map, int mapSize);
int IsOnPath(int i, const int *path, int pathLength);
void PrintPath(int mapSize, int *path, int pathLength, int *stops);
void InitMap(int *map, int mapSize);

#endif //TRUCKINGNAVIGATION_MAPGEN_H
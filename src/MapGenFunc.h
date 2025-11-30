//
// Created by rasmk on 19-11-2025.
//

#ifndef TRUCKINGNAVIGATION_MAPGEN_H
#define TRUCKINGNAVIGATION_MAPGEN_H
#include "DefineStruct.h"


void TestMapGenConnection(void);
void runMapGen(int *map, unsigned int mapSize, Stops *restStops);
void PrintMap(int *map, int mapSize);
void InitMap(int *map, unsigned int mapSize);

#endif //TRUCKINGNAVIGATION_MAPGEN_H
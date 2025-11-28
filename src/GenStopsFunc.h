//
// Created by rasmk on 20-11-2025.
//

#ifndef TRUCKINGNAVIGATION_GENSTOPSFUNC_H
#define TRUCKINGNAVIGATION_GENSTOPSFUNC_H
#include "DefineStruct.h"
#include "DefineConst.h"

void TestConGenStopsFunc();

void InitializeTypes(StopType stopTypesArray[3]);
void InitializeStops(int *map, int mapSize, Stops restStops[NUMBEROFSTOPS], StopType stopTypesArray[3]);
int SpotOccupied(int *map, int mapSize, int X, int Y);
void GenStops(int *map, unsigned int mapSize, Stops restStops[NUMBEROFSTOPS]);

#endif //TRUCKINGNAVIGATION_GENSTOPSFUNC_H
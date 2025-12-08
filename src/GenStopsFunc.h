//
// Created by rasmk on 20-11-2025.
//

#ifndef TRUCKINGNAVIGATION_GENSTOPSFUNC_H
#define TRUCKINGNAVIGATION_GENSTOPSFUNC_H
#include "DefineStruct.h"
#include "DefineConst.h"

void TestConGenStopsFunc();

void InitializeTypes(StopType stopTypesArray[3]);
void InitializeStopsType(Stops restStops[], StopType stopTypesArray[3]);
void InitializeStopsLocation(int *map, Stops restStops[]);
int SpotOccupied(int *map, int X, int Y);
void GenStop(int *map, Stops restStops[], int i);

#endif //TRUCKINGNAVIGATION_GENSTOPSFUNC_H
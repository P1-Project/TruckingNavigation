//
// Created by rasmk on 20-11-2025.
//

#ifndef TRUCKINGNAVIGATION_GENSTOPSFUNC_H
#define TRUCKINGNAVIGATION_GENSTOPSFUNC_H
#include "DefineStruct.h"
#include "DefineConst.h"

void TestConGenStopsFunc();

void InitializeTypes(StopType stopTypesArray[3]);
void InitializeStopsType(Stops restStops[NUMBEROFSTOPS], StopType stopTypesArray[3]);
void InitializeStopsLocation(int *map, Stops restStops[NUMBEROFSTOPS]);
int SpotOccupied(int *map, int X, int Y);
void GenStops(int *map, Stops restStops[NUMBEROFSTOPS]);

#endif //TRUCKINGNAVIGATION_GENSTOPSFUNC_H
//
// Created by rasmk on 20-11-2025.
//

#ifndef TRUCKINGNAVIGATION_GENSTOPSFUNC_H
#define TRUCKINGNAVIGATION_GENSTOPSFUNC_H

#define NUMBEROFSTOPS 80

typedef struct {
    int Type;
    int Toilet;
    int Fuel;
    int Hotel;
    int Food;
    int Parking;
} StopType ;

typedef struct {
    StopType Type;
    unsigned int locationX;
    unsigned int locationY;
} Stops ;

void TestConGenStopsFunc();

void InitializeTypes(StopType stopTypesArray[3]);
void InitializeStops(int *map, int mapSize, Stops restStops[NUMBEROFSTOPS], StopType stopTypesArray[3]);
int SpotOccupied(int *map, int mapSize, int X, int Y);
void GenStops(int *map, unsigned int mapSize, Stops restStops[NUMBEROFSTOPS]);

#endif //TRUCKINGNAVIGATION_GENSTOPSFUNC_H
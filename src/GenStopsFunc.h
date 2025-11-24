//
// Created by rasmk on 20-11-2025.
//

#ifndef TRUCKINGNAVIGATION_GENSTOPSFUNC_H
#define TRUCKINGNAVIGATION_GENSTOPSFUNC_H

#define NUMBEROFSTOPS 100

typedef struct {
    char Type;
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
void InitializeStops(int mapSize, Stops restStops[NUMBEROFSTOPS], StopType stopTypesArray[3]);
int StopExists(int X, int Y, Stops restStops[NUMBEROFSTOPS], int stopsPlaced);
void GenStops(int *map, unsigned int mapSize, Stops restStops[NUMBEROFSTOPS]);

#endif //TRUCKINGNAVIGATION_GENSTOPSFUNC_H
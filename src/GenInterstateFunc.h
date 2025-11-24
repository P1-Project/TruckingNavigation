//
// Created by rasmk on 20-11-2025.
//

#ifndef TRUCKINGNAVIGATION_INTERSTATE_H
#define TRUCKINGNAVIGATION_INTERSTATE_H
#define ERROR_PATH 10


typedef struct {
    int startX, startY, endX, endY;
} InterStateRoad;

typedef struct {
    int type;
    int locationX, locationY;
} TruckStopInterstate;


int *DefineHighwayPath(int *map, signed int mapSize, InterStateRoad interStateRoad, int *outPathLength);
void SetInterStateRoad(int *map, signed int mapSize, InterStateRoad interStateRoad);
void SetInterStates(int *map, const signed int mapSize);
#endif //TRUCKINGNAVIGATION_INTERSTATE_H
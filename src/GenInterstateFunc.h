//
// Created by rasmk on 20-11-2025.
//

#ifndef TRUCKINGNAVIGATION_INTERSTATE_H
#define TRUCKINGNAVIGATION_INTERSTATE_H

typedef struct {
    int startX, startY, endX, endY;
} InterStateRoad;

int *DefineHighwayPath(int *map, signed int mapSize, InterStateRoad interStateRoad, int *outPathLength);
void SetInterStateRoad(int *map, signed int mapSize, InterStateRoad interStateRoad);
#endif //TRUCKINGNAVIGATION_INTERSTATE_H
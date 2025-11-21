//
// Created by rasmk on 20-11-2025.
//

#ifndef TRUCKINGNAVIGATION_INTERSTATE_H
#define TRUCKINGNAVIGATION_INTERSTATE_H
typedef struct {
    int startX, startY, endX, endY;
} InterStateRoad;

void SetInterStateRoad(int *map, unsigned int mapSize, InterStateRoad interStateRoad);
#endif //TRUCKINGNAVIGATION_INTERSTATE_H
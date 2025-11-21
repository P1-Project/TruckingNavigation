//
// Created by rasmk on 20-11-2025.
//

#include "GenInterstateFunc.h"

#include <stdio.h>


void SetInterStateRoad(int *map, unsigned int mapSize, InterStateRoad interStateRoad) {
    //from point (x,y) on map, to (x,y)
    //calculate index from map
    //map[y*mapSize+x]
    //start point
    map[interStateRoad.startY*mapSize + interStateRoad.startX] = 120;
    printf("%d\n", interStateRoad.startY*mapSize + interStateRoad.startX);
    //endpoint
    int coordinateToIndex = interStateRoad.endX*mapSize + interStateRoad.endY;
    if (coordinateToIndex > mapSize*mapSize-1) {coordinateToIndex = mapSize*mapSize-1;}
    map[coordinateToIndex] = 120;
    printf("%d\n",coordinateToIndex);

    //using dijkstra algorithm to calculate the shortest path between to points


}





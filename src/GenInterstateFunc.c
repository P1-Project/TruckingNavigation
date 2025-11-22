//
// Created by rasmk on 20-11-2025.
//

#include "GenInterstateFunc.h"
#include "DijkstraAlgorithm.h"
#include "ConverterFunc.h"

#include <stdio.h>
#include <stdlib.h>


int *DefineHighwayPath(int *map, signed int mapSize, InterStateRoad interStateRoad, int *outPathLength) {
    //calculate distance absolute distance from startX to endX
    int absDx = abs( interStateRoad.startX - interStateRoad.endX);
    //calculate distance absolute distance from startY to endY
    int absDy = abs(interStateRoad.startY - interStateRoad.endY);

    //these intgers below are assigned as an oneline if-statement with return either 1 or -1
    int stepX = (interStateRoad.endX > interStateRoad.startX) ? 1 : -1;
    int stepY = (interStateRoad.endY > interStateRoad.startY) ? 1 : -1;


    int x = interStateRoad.startX;
    int y = interStateRoad.startY;
    int D; //decision var
    int pathLength = 0;
    int *path = malloc(sizeof(int)* mapSize * mapSize);
    int tempIndex = y*mapSize + x;
    printf("tempIndex = %d\n", tempIndex);
    map[tempIndex] = 2;

    //if the highway is going North to South or East to West, do this else do East West,
    if (absDx >= absDy) { //North to South
        D = 2*absDy - absDx;
        for (int i = 0; i <= absDx; i++) {
            tempIndex = y*mapSize + x;
            map[tempIndex] = 2; //sets mapIdx as highway
            pathLength++;
            path[i] = tempIndex;

            if (D > 0) {
                y += stepY; //adds or subtracts depending on the absDy above
                D -= 2*absDx;
            }
            x += stepX; //adds or subtracts depending on the absDx above
            D += 2*absDy;
        }
    }
    else { //East to West
        D = 2*absDy- absDx;
        for (int i = 0; i <= absDy; i++) {
            tempIndex = y*mapSize + x;
            map[tempIndex] = 2; //sets mapIdx as highway
            pathLength++;
            path[i] = tempIndex;
            if (D > 0) {
                x += stepX;
                D -= 2*absDy;
            }
            y += stepY;
            D += 2*absDx;
        }
    }

    *outPathLength = pathLength;
    return path;

}

void SetInterStateRoad(int *map, signed int mapSize, InterStateRoad interStateRoad) {
    //from point (x,y) on map, to (x,y)
    //start point
    const int startIndex = XYToIdx(interStateRoad.startX,interStateRoad.startY, mapSize);
    map[startIndex] = 2; //value for map start index
    printf("%d\n", startIndex);
    //endpoint
    const int goalIndex = XYToIdx(interStateRoad.endX, interStateRoad.endY, mapSize);
    map[goalIndex] = 2; //value for map end index
    printf("%d\n", goalIndex);

    //using dijkstra algorithm to calculate the shortest path between to points
    //TestDijkstraAlgorithmCon();
    //runDijstraks(map, mapSize, startIndex, goalIndex);

    //defines highway with the use of rules,
    int pathLength;
    int *path = DefineHighwayPath(map, mapSize, interStateRoad, &pathLength);

    printf("PathLength : %d\n", pathLength);

    for (int i = 0; i < pathLength; i++) {
        printf("%d, ", path[i]);
    }


    free(path);


}





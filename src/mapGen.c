//
// Created by rasmk on 19-11-2025.
//

#include "mapGen.h"
#include "GenInterstateFunc.h"

#include <stdio.h>
#include <stdlib.h>


int XYToIndex(int x, int y, int mapSize) {
    return y * mapSize + x;
}


void TestMapGenConcetion(void) {
    printf("Testing con from mapGen\n");
}

void PrintMap(int *map, int mapSize) {
    for (int i = 0; i < mapSize; i++) {
        if (i % 30 == 0) printf("\n %d |", i/30);
        printf("%c ", map[i]);
    }
}

void GenRandomMap(int *map, const unsigned int mapSize) {
    for (int i = 0; i < mapSize; i++) {
        int num = rand() % (0-6+1)+0;
        num = 0;
        if (num == 0) map[i] = 48;
        if (num == 1) map[i] = 49;
        if (num == 2) map[i] = 50;
        if (num == 3) map[i] = 52;
        if (num == 4) map[i] = 53;
        if (num == 5) map[i] = 54;
        if (num == 6) map[i] = 55;
    }
}





void runMapGen(void) {
    const unsigned int mapSize = 30;
    int map[mapSize*mapSize];
    GenRandomMap(map,mapSize*mapSize);
    InterStateRoad interStateRoad;
    interStateRoad.startX = 0, interStateRoad.startY = 0;
    interStateRoad.endX = 29, interStateRoad.endY = 29;

    SetInterStateRoad(map, mapSize, interStateRoad);
    PrintMap(map, mapSize*mapSize);

}

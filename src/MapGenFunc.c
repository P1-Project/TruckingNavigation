//
// Created by rasmk on 19-11-2025.
//

#include "MapGenFunc.h"
#include "GenInterstateFunc.h"


#include <stdio.h>
#include <stdlib.h>



void TestMapGenConcetion(void) {
    printf("Testing con from mapGen\n");
}



void PrintMap(int *map, int mapSize) {
    int total = mapSize * mapSize;
    for (int i = 0; i < total; i++) {
        //new row:
        if (i % mapSize == 0) {
            if (i != 0) printf("\n");
            printf("%2d |", i / mapSize);
        }

        //printsMap
        char c;
        switch (map[i]) {
            case 0: c = '.'; break; // empty
            case 1: c = '#'; break; // blockade
            case 2: c = 'H'; break; // highway
            case 3: c = '.'; break;
            case 4: c = '.'; break;
            //add more cases for rest stops and more
            default: c = '?'; break; // unknown
        }
        //printf("%d ", map[i]);
        printf("%c ", c);
    }
    printf("\n");
}



void GenRandomMap(int *map, const signed int mapSize) {
    for (int i = 0; i < mapSize*mapSize; i++) {
        int num = rand() % (0-6+1)+0;
        num = 0;
        map[i] = num;
    }
}





void runMapGen(void) {
    const signed int mapSize = 30;
    int map[mapSize*mapSize];
    GenRandomMap(map,mapSize);
    InterStateRoad interStateRoad;
    interStateRoad.startX = 29, interStateRoad.startY = 29;
    interStateRoad.endX = 0, interStateRoad.endY = 0;

    SetInterStateRoad(map, mapSize, interStateRoad);
    printf("\n");
    PrintMap(map, mapSize);

    printf("\n map index = %d \n", map[1]);
}

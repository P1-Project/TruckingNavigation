//
// Created by rasmk on 19-11-2025.
//

#include "MapGenFunc.h"
#include "GenInterstateFunc.h"
#include "CheckCoordinateSetFunc.c"
#include "ConverterFunc.h"

#include <stdio.h>
#include <stdlib.h>



void TestMapGenConcetion(void) {
    printf("Testing con from mapGen\n");
}



void PrintMap(int *map, int mapSize) {
    int total = mapSize * mapSize;
    for (int i = -1; i < mapSize; i++) {
        if (i == -1 ) {printf("   |"); continue;}
        if (i <= 9) printf(" ");
        printf("%d ", i);
    }
    printf("\n");


    for (int i = 0; i < total; i++) {
        //new row:

        if (i % mapSize == 0) {
            if (i != 0) printf("\n");
            printf("%2d |", i / mapSize);
        }

        //printsMap
        char c;
        switch (map[i]) {
            case NORMALROAD: c = '.'; break; // Road
            case INTERSTATEROAD: c = 'H'; break; // Interstate
            case INTERSTATESTOP: c = '1'; break; // InterstateTruckStop
            case TYPE2STOP: c = '2'; break; // Type 2 stop
            case TYPE3STOP: c = '3'; break; // Type 3 Stop
            case BLOCKADE: c = '#'; break; // Blockade
            //add more cases for rest stops and more
            default: c = '?'; break; // unknown
        }
        //printf("%d ", map[i]);
        printf(" %c ", c);
        //if (i % mapSize >= 9) printf(" ");
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
    interStateRoad.startX = 10, interStateRoad.startY = 0;
    interStateRoad.endX = 25, interStateRoad.endY = 30;

    SetInterStateRoad(map, mapSize, interStateRoad);
    printf("\n");

    map[XYToIdx(10, 10, mapSize)] = 5;
    int indexValue = CheckCoordinateSet(map, 10, 10, mapSize);
    printf("map[%d]\n", indexValue);

    PrintMap(map, mapSize);




    //printf("\n map index = %d \n", map[155]);
}

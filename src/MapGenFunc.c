//
// Created by rasmk on 19-11-2025.
//

#include "MapGenFunc.h"
#include "GenInterstateFunc.h"
#include "CheckCoordinateSetFunc.c"
#include "ConverterFunc.h"
#include "AnsiColorCodes.h"
#include "GenBlockadeFunc.h"


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>



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
        if (i % mapSize == 0) {
            if (i != 0) printf("\n");
            printf("%2d |", i / mapSize);
        }

        const char *color = COLOR_RESET;
        char c = '?';

        switch (map[i]) {
            case NORMALROAD: c = '.'; color = WHT; break;
            case INTERSTATEROAD: c = 'H'; color = MAG; break;
            case INTERSTATESTOP: c = '1'; color = BLU; break;
            case TYPE2STOP: c = '2'; color = YEL; break;
            case TYPE3STOP: c = '3'; color = GRN; break;
            case BLOCKADE: c = '#'; color = RED; break;
            default: c = '?'; color = WHT; break;
        }

        printf("%s %c %s", color, c, WHT);
    }
    printf("\n");
}



void InitMap(int *map, const signed int mapSize) {
    for (int i = 0; i < mapSize*mapSize; i++) {
        int num = 0;
        map[i] = num;
    }
}

void EnableANSI() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, mode);
}




void runMapGen(void) {
    const signed int mapSize = 30;
    const int numBlockades = 80;
    srand(time(NULL));
    int map[mapSize*mapSize];
    InitMap(map,mapSize);

    GenBlockadeFunc(map,mapSize,numBlockades);
    GenerateClusterBlockades(map,mapSize,numBlockades/4,1);

    InterStateRoad interStateRoad;
    interStateRoad.startX = 10, interStateRoad.startY = 0;
    interStateRoad.endX = 25, interStateRoad.endY = 30;


    SetInterStates(map,mapSize);

    map[XYToIdx(29, 29, mapSize)] = 5;
    //int indexValue = CheckCoordinateSet(map, 29, 29, mapSize); //this function needs fixing if index goes out of bounds
    //printf("%d\n", indexValue);

    EnableANSI();
    PrintMap(map, mapSize);


    printf(RED"This text is red!\n"RESET);
    printf("\033[32mThis text is green!\033[0m\n");
    printf("\033[33mThis text is yellow!\033[0m\n");
    printf("\033[34mThis text is blue!\033[0m\n");
    //printf("\n map index = %d \n", map[155]);
}
//
// Created by rasmk on 19-11-2025.
//

#include "MapGenFunc.h"
#include "GenInterstateFunc.h"
#include "CheckCoordinateSetFunc.c"
#include "GenStopsFunc.h"
#include "ConverterFunc.h"
#include "AnsiColorCodes.h"
#include "GenBlockadeFunc.h"
#include "DefineConst.h"
#include "DefineStruct.h"


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>



void TestMapGenConnection(void) {
    printf("Testing con from mapGen\n");
}

void InitMap(int *map, signed int mapSize){
    for (int i = 0; i < mapSize*mapSize; i++) {
        map[i] = 0;
    }
}

void EnableANSI() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, mode);
}


void PrintMap(int *map, int mapSize) {
    EnableANSI();
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


void runMapGen(int *map, int mapSize)
{
    //Stops *restStops[]
    const int numBlockades = 80;
    srand(time(NULL)); //used to gen a random seed using the time.h libary

    InitMap(map, mapSize); //inits the map and sets all values equal 0

    GenBlockadeFunc(map,mapSize,numBlockades); //gen blockades for the map
    GenerateClusterBlockades(map,mapSize,numBlockades/4,1); //gen cluster blockades for the map

    GenInterStates(map,mapSize); //defines and setes the interstates

    //inits the stops types array
    //StopType stopTypesArray[3];
    //InitializeTypes(stopTypesArray);

    //inits the restStops array for storrage of the reststops
    //*restStops[NUMBEROFSTOPS];
    //InitializeStops(*map, mapSize, &restStops, stopTypesArray);
    //GenStops(*map, mapSize, &restStops);


    //map[XYToIdx(29, 29, mapSize)] = 5;
    //int indexValue = CheckCoordinateSet(map, 29, 29, mapSize); //this function needs fixing if index goes out of bounds
    //printf("%d\n", indexValue);
}
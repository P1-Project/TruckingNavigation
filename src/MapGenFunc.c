//
// Created by rasmk on 19-11-2025.
//

#include "MapGenFunc.h"

#include <stdbool.h>

#include "GenInterstateFunc.h"
#include "CheckCoordinateSetFunc.h"
#include "GenStopsFunc.h"
#include "ConverterFunc.h"
#include "AnsiColorCodes.h"
#include "GenBlockadeFunc.h"
#include "DefineConst.h"
#include "DefineStruct.h"


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#endif



void TestMapGenConnection(void) {
    printf("Testing con from mapGen\n");
}

void InitMap(int *map, int mapSize){
    for (int i = 0; i < mapSize*mapSize; i++) {
        map[i] = 0;
    }
}

void EnableANSI() {
#ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD mode = 0;
        GetConsoleMode(hOut, &mode);
        mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, mode);
#else
        // macOS and Linux already support ANSI natively
#endif
    }

//in this case mapSize can be unsigned since it cant be compared to minus 1 in while loop
void PrintMap(int *map, int mapSize) {
    EnableANSI();
    const int total = mapSize * mapSize;
    printf("Map size is: %d\n", mapSize);
    int j = -1;
    while (j < mapSize) {
        if (j == -1 ) {
            printf("   |");
        }
        else if (j <= 9){ printf(" %d ", j);}
        else {
            printf("%d ", j);
        }
        j++;
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
                case ROUTE: c = 'X'; color = CYN; break;
                default: c = '?'; color = WHT; break;
            }
        //}
        printf("%s %c %s", color, c, WHT);
    }
    printf("\n");
}
bool isOnPath(int i, int *path, int pathLength) {
    for (int p = 0; p < pathLength; p++) {
        if (path[p] == i) return true;
    }
    return false;
}



void PrintMapWPath(int *map, int mapSize, int *path, int pathLength) {
    EnableANSI();
    const int total = mapSize * mapSize;
    printf("Map size is: %d\n", mapSize);
    int j = -1;
    while (j < mapSize) {
        if (j == -1 ) {
            printf("   |");
        }
        else if (j <= 9){ printf(" %d ", j);}
        else {
            printf("%d ", j);
        }
        j++;
    }
    printf("\n");

    for (int i = 0; i < total; i++) {
        if (i % mapSize == 0) {
            if (i != 0) printf("\n");
            printf("%2d |", i / mapSize);
        }

        const char *color = COLOR_RESET;
        char c = '?';
        if (path) {
            switch (map[i]) {
                case NORMALROAD: c = '.'; color = WHT; break;
                case INTERSTATEROAD: c = 'H'; color = MAG; break;
                case INTERSTATESTOP: c = '1'; color = BLU; break;
                case TYPE2STOP: c = '2'; color = YEL; break;
                case TYPE3STOP: c = '3'; color = GRN; break;
                case BLOCKADE: c = '#'; color = RED; break;
                case ROUTE: c = 'X'; color = CYN; break;
                default: c = '?'; color = WHT; break;
            }
        }
        if (isOnPath(i, path, pathLength)) {
            color = CYNHB;
        }

        printf("%s %c %s", color, c, WHT);
    }
    printf("\n");
}

void printPath(int *path, int pathLength) {
    printf("Path length : %d\n", pathLength);
    for (int i = 0; i <pathLength; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");
}




void runMapGen(int *map, int mapSize, Stops *restStops)
{
    srand(time(NULL)); //used to gen a random seed using the time.h libary

    InitMap(map, mapSize); //inits the map and sets all values equal 0
    //Gen Blockaed can be swaped around depending on what needs to be generated first,
    //clusters before normal equals more blockades
    GenClusterBlockadeFunc(map,mapSize,NUMBEROFBLOCKADES/5,1); //gen cluster blockades for the map
    GenBlockadeFunc(map,mapSize,NUMBEROFBLOCKADES); //gen blockades for the map

    StopType stopTypesArray[3];
    InitializeTypes(stopTypesArray);
    GenInterStates(map, mapSize, restStops, stopTypesArray); //defines and setes the interstates


    //int indexValue = CheckCoordinateSet(map, 10, 10, mapSize);

    InitializeStopsType(restStops, stopTypesArray);
    InitializeStopsLocation(map, restStops);

    //map[XYToIdx(29, 29, mapSize)] = 5;
    //int indexValue = CheckCoordinateSet(map, 29, 29, mapSize); //this function needs fixing if index goes out of bounds
    //printf("%d\n", indexValue);
}
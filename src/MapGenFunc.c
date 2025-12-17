#include "MapGenFunc.h"
#include "GenInterstateFunc.h"
#include "GenStopsFunc.h"
#include "AnsiColorCodes.h"
#include "GenBlockadeFunc.h"
#include "DefineConst.h"
#include "DefineStruct.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "HelperFunc.h"
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

int IsOnPath(const int i, const int *path, const int pathLength) {
    for (int p = 0; p < pathLength; p++) {
        if (path[p] == i) return 1;
    }
    return 0;
}

void PrintPath(int mapSize, int *path, int pathLength, int *stops) {
    int x, y, counter = 0;
    printf("Path length: %d\n", pathLength);
    printf("Path:\n");
    for (int i = 0; i <pathLength; i++) {
        IdxToCoords(path[i], mapSize, &x, &y);
        const char *color;

        if (stops[counter] == path[i]) {
            // print color
            color = RED;
            counter++;
        } else {
            // print normal
            color = WHT;
        }

        printf("%s (%s%d,%s%d)%s%s", color,
        x <= 9 ? "0" : "", x,
        y <= 9 ? "0" : "", y,
        WHT,
        (i == pathLength - 1) ? "" : " -> ");

        if ((i+1) % 5 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

//in this case mapSize can be unsigned since it cant be compared to minus 1 in while loop
void PrintMap(int *map, int mapSize, int *path, int pathLength){
    EnableANSI();
    const int total = mapSize * mapSize;

    //printf("Map size is: %d\n", mapSize);

    // Column header
    for (int j = -1; j < mapSize; j++) {
        if (j == -1) printf("   |");
        else if (j <= 9) printf(" %d ", j);
        else printf("%d ", j);
    }
    printf("\n");

    for (int i = 0; i < total; i++) {
        if (i % mapSize == 0) {
            if (i != 0) printf("\n");
            printf("%2d |", i / mapSize);
        }

        const char *color = WHT;
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

        // Highlight path if provided
        if (path && pathLength > 0 && IsOnPath(i, path, pathLength)) {
            color = CYNHB;
        }

        printf("%s %c %s", color, c, WHT);
    }
    printf("\n");
}

void RunMapGen(int *map, int mapSize, Stops *restStops)
{
    InitMap(map, mapSize); //inits the map and sets all values equal 0
    //Gen Blockaed can be swaped around depending on what needs to be generated first,
    //clusters before normal equals more blockades
    GenClusterBlockadeFunc(map,mapSize,NUMBEROFBLOCKADES/5,1); //gen cluster blockades for the map
    GenBlockadeFunc(map,mapSize,NUMBEROFBLOCKADES); //gen blockades for the map

    //Initializes the array of StopTypes
    StopType stopTypesArray[3];
    //assigns the indexes values
    InitializeTypes(stopTypesArray);
    //initializes the stops array
    InitializeStopsType(restStops, stopTypesArray);
    //defines and sets the interstates
    GenInterStates(map, mapSize, restStops, stopTypesArray);
    //initialized rest stops and locates them on the map
    InitializeStopsLocation(map, restStops);
    //Returns the map through its memory address as a pointer.
}
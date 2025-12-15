#include <stdio.h>

#include "AStarPathFinding.h"
#include "CheckCoordinateSetFunc.h"
#include "HelperFunc.h"
#include "MapGenFunc.h"
#include "GenStopsFunc.h"
#include "GenBlockadeFunc.h"
#include "GetDestinationFunc.h"
#include "GenInterstateFunc.h"
#include "GenStopsFunc.h"
#include "DefineConst.h"
#include "DefineStruct.h"
#include "DivideRouteFunc.h"
#include "Navigation.h"


int main(void) {
    printf("Hello, World!\n");
    //connection testing
    /*
    TestConGenStopsFunc(); TestConGetDestinationFunc(); TestConCheckCoordinateSetFunc(); TestConGenBlockadeFunc();
    TestMapGenConnection(); TestAstarPathFindingConnection();
    */

    int map[MAPSIZE*MAPSIZE];
    Stops restStops[NUMBEROFSTOPS];
    int *path = malloc(sizeof(int) * MAPSIZE * MAPSIZE);
    srand(time(NULL));
    // Find optimal route between start and end points
    Destination destination;
    GetDestination(&destination,0,MAPSIZE);

    //runMapGen()
    RunMapGen(map, MAPSIZE, restStops);

    // Find optimal route between found stops of type 3 and display to user
    int pathLength = 0;
    int numSections = 0;
    int *stops = malloc(sizeof(int) * MAPSIZE);
    path = Navigate(map, MAPSIZE, destination, &pathLength, &numSections, stops);


    //print map with full complete path
    PrintMap(map, MAPSIZE, path, pathLength);
    PrintPath(path, pathLength);
    printf("\n");
    printf("number of stops : %d\n", numSections);
    for (int i = 0; i < numSections; i++) {
        printf("stop at index : %d of type %d ", stops[i], map[stops[i]]);
        int tempX, tempY;
        IdxToCoords(stops[i], MAPSIZE, &tempX, &tempY);
        printf("coordinates: (%d, %d)\n", tempX, tempY);
    }
    int time = CalculatePathTime(map, path, pathLength);
    printf("New path time in minutes : %d\n", time);

    //free memory
    free(path);
    free(stops);

    return 0; //End program
}
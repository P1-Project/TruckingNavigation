#include <stdio.h>

#include "HelperFunc.h"
#include "MapGenFunc.h"
#include "GetDestinationFunc.h"
#include "DefineConst.h"
#include "DefineStruct.h"
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
    srand(time(NULL)); // NOLINT(*-msc51-cpp)
    // Find optimal route between start and end points
    Destination destination;
    GetDestination(&destination,0,MAPSIZE);

    //runMapGen()
    RunMapGen(map, MAPSIZE, restStops);

    int originalPathLength = 0;
    int *originalPath = OriginalPath(map, MAPSIZE, destination, &originalPathLength);

    // Find optimal route between found stops of type 2+3 and display to user
    int pathLength = 0;
    int numSections = 0;
    int *stops = malloc(sizeof(int) * MAPSIZE);
    int *path = Navigate(map, MAPSIZE, destination, &pathLength, &numSections, stops);

    //call NavigateWrapper for printing of map with stops
    NavigateWrapper(map , MAPSIZE, path, pathLength, stops, numSections);


    free(originalPath);
    free(path);
    free(stops);
    return 0; //End program
}